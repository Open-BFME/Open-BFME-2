#!/usr/bin/env python3
"""Report outgoing commits that replay work already upstream (pre-push, SHADOW).

WHY. On 2026-10-06..08 automated seats re-pushed old commits 3,541 times. One
subject, "Recover counted allocator lock wrapper" (authored 2026-10-05 15:45
+0200), reached master about 80 times under different committer dates
(f12fbff21b, ace579e0f2, 9be13c8c09, ...), each copy appending one
reverse/functions.csv line that was already there; 686 "Clean up after ...:
drop N exact duplicate ledger row(s)" commits then removed 56,708 duplicate
rows. Every hook stayed green: a duplicate of a verified row is still verified.
Open-BFME-1 has no equivalent check (its seat_replay.py replays a seat's delta
onto master; it does not look for replays), so this one is new.

SIGNATURES, per outgoing (non-merge) commit:
  identity  its (author email, author date, subject) equals that of a commit
            already reachable from the remote tip. A rebase or cherry-pick
            keeps all three -- and so do an intentional re-land after an
            upstream revert and an amended commit, so identity alone is only a
            POSSIBLE replay and gets no "drop it" advice.
  patch     its patch-id (`git patch-id --stable` of its -U0 diff) equals its
            identity twin's: the same change, so a REPLAY -- unless upstream
            holds a `Revert "<subject>"` commit, which makes it a re-land.
  ledger    lines it adds to reverse/functions.csv or reverse/symbols.csv (net
            of lines it removes, so a moved row is not counted) that already
            exist verbatim in the remote tip's copy of that file: a REPLAY.

COST. A hard wall-clock budget (tools/shadow_budget.py: $BFME_SHADOW_BUDGET_S,
default 10 s) bounds the run; when it runs out the tool kills its git children,
prints what it finished ("partial: budget ... exceeded after N of M commit(s)")
and exits 0. Within it, cheapest first: one `git log` of the outgoing commits;
an upstream walk of only the commits COMMITTED since the oldest outgoing author
date less --slack-hours, and never more than --max-days before the newest
outgoing commit (outgoing commits authored before that window are counted, not
matched); one diff of the whole range's ledgers, checked against one read of
each remote ledger. Per-commit diffs (~0.2 s each with a 16 MB ledger, four at
a time) only where they decide something: when that net diff finds a line, the
first --attribute ledger-touching commits (identity twins first) to say which
added it; and the first --attribute identity twins without such lines, with
their upstream twins, for patch-ids. Measured on real ranges: 500 commits in
~4 s (was 112-114 s), 2,000 in ~4 s (was over 240 s), 1-20 commits ~1 s. What this leaves
unchecked is reported as a count: ledger commits seen only through the net
diff (which hides a row added and dropped again within the push), twins whose
patch-id was not compared, commits authored before the walk window.

REPORT ONLY. With --shadow (the hook) it always exits 0. Without it, it exits 1
when it finds a replay or possible replay, so scripts and tests can branch on it.

  python3 tools/replay_check.py --range REMOTE_SHA LOCAL_SHA [--shadow]
"""
import argparse
import collections
import concurrent.futures
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from shadow_budget import Budget, BudgetExceeded, exit_on_signals, seconds  # noqa: E402

LEDGERS = ("reverse/functions.csv", "reverse/symbols.csv",                         # Open-BFME-2
           "targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv")  # Open-BFME-1
SEP = "\x1f"
DIFF = ("--no-color", "--no-ext-diff", "--no-textconv", "--no-renames", "-U0")
GIT = ("git", "-c", "core.quotePath=false")
WORKERS = 4                  # concurrent per-commit diffs
TWINS_COMPARED = 1           # upstream twins (newest first) one outgoing commit is compared with
REVERT = re.compile(r'^Revert "(.*)"$')


class Git:
    def __init__(self, budget):
        self.budget = budget

    def __call__(self, *args, ok=(0,), input=None):
        code, out, err = self.budget.run([*GIT, *args], input=None if input is None else input.encode("utf-8"))
        if code not in ok:
            raise RuntimeError("git %s: %s" % (" ".join(args[:3]), err.decode("utf-8", "replace").strip()))
        return out.decode("utf-8", "replace")

    def lines(self, *args, input=None):
        for raw in self.budget.lines([*GIT, *args], input=input):
            yield raw.decode("utf-8", "replace")


def commits(git, *rev_args):
    """[(sha, author email, author ts, author tz, committer ts, subject)], newest first."""
    fmt = SEP.join(("%H", "%ae", "%ad", "%ct", "%s"))
    out = []
    for line in git("log", "--no-merges", "--date=raw", "--format=" + fmt, *rev_args).splitlines():
        cells = line.split(SEP)
        if len(cells) != 5:
            continue
        sha, email, adate, cts, subject = cells
        ats, _, atz = adate.partition(" ")
        out.append((sha, email.lower(), int(ats), atz, int(cts), subject))
    return out


def additions(text):
    """{sha or None: {path: [net added line, ...]}} from `git diff/log -U0` output,
    commits introduced by a SEP<sha> line."""
    out = {}
    sha = path = None
    header = False
    plus, minus = collections.defaultdict(collections.Counter), collections.defaultdict(collections.Counter)

    def flush():
        got = {}
        for p in plus:
            net = plus[p] - minus.get(p, collections.Counter())
            if net:
                got[p] = sorted(net.elements())
        if got:
            out[sha] = got

    for line in text.splitlines():
        if line.startswith(SEP):
            flush()
            sha, path, header = line[1:].strip(), None, False
            plus.clear()
            minus.clear()
        elif line.startswith("diff --git "):
            path, header = None, True
        elif header:
            if line.startswith("+++ "):
                # "+++ /dev/null" is a deletion: it adds nothing
                path = line[6:] if line.startswith("+++ b/") else None
            elif line.startswith("@@"):
                header = False
        elif path and line.startswith("+"):
            plus[path][line[1:].rstrip("\r")] += 1
        elif path and line.startswith("-"):
            minus[path][line[1:].rstrip("\r")] += 1
    flush()
    return out


def ledger_lines(text):
    """{ledger path: [net added line]} of one commit's diff."""
    got = additions(text).get(None, {})
    return {p: v for p, v in got.items() if p in LEDGERS}


def upstream_lines(git, base, path):
    """Every line of `path` at `base` (empty when it has no such file). One blob read and a
    set beat `git grep -F -f`, which tries each of thousands of patterns on every line
    (56 s for a 500-commit push's lines)."""
    code, out, _err = git.budget.run([*GIT, "cat-file", "blob", f"{base}:{path}"])
    if code:
        return set()
    return {line.rstrip("\r") for line in out.decode("utf-8", "replace").split("\n")}


def diff_texts(git, shas, into):
    """into[sha] = that commit's full -U0 diff, for each sha whose diff completed."""
    current, buf = None, []
    for line in git.lines("diff-tree", "--stdin", "-r", "-p", "--root", "--always", *DIFF,
                          "--format=" + SEP + "%H", input="".join(s + "\n" for s in shas).encode()):
        if line.startswith(SEP):
            if current:
                into[current] = "".join(buf)
            current, buf = line[1:].strip(), []
        else:
            buf.append(line)
    if current:
        into[current] = "".join(buf)


class Result:
    """What the check established so far; a budget overrun reports it as it stands."""

    def __init__(self):
        self.outgoing = []          # metadata of every outgoing commit, newest first
        self.walked = 0
        self.indexed = False        # the upstream identity index is complete
        self.index = collections.defaultdict(list)
        self.reverts = {}           # subject -> upstream sha of `Revert "subject"`
        self.unchecked = 0          # outgoing commits authored before the walk window
        self.ledger_commits = None  # outgoing commits touching a ledger, oldest first
        self.touched = set()
        self.net = None             # {path: [line]}: the range's net ledger additions
        self.need_diff = set()
        self.diffs = {}             # sha -> its -U0 diff
        self.attributed = set()     # ledger commits whose own additions were read
        self.added = {}             # sha -> {path: [line]}
        self.present = None         # {path: lines already upstream}, once grepped
        self.pairs = {}             # outgoing sha -> [upstream twins compared by patch-id]
        self.patch_ids = None       # sha -> patch-id, once computed
        self.attribute = 0
        self.max_days = 0.0

    def twins(self, commit):
        sha, email, ats, atz, _cts, subject = commit
        return self.index.get((email, ats, atz, subject), [])

    def hits(self, sha):
        """How many lines this commit adds that the remote tip's ledger already holds."""
        if self.present is None:
            return 0
        return sum(1 for p, v in self.added.get(sha, {}).items() for line in v if line in self.present.get(p, ()))

    def complete(self, commit):
        """Every check planned for this commit finished."""
        sha = commit[0]
        if not self.indexed:
            return False
        if sha in self.need_diff and sha not in self.diffs:
            return False
        if self.present is None and sha in self.touched:
            return False
        if self.twins(commit) and not self.hits(sha) and self.patch_ids is None:
            return False                            # its patch-id comparison was still to come
        return True


def diff_all(git, shas, into):
    """Per-commit diffs of `shas` into `into`, WORKERS at a time (each ~0.2 s with a 16 MB ledger)."""
    shas = [s for s in dict.fromkeys(shas) if s not in into]
    if not shas:
        return
    workers = min(WORKERS, len(shas))
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as pool:
        jobs = [pool.submit(diff_texts, git, shas[i::workers], into) for i in range(workers)]
        for job in jobs:
            job.result()


def check(git, base, tip, result, slack_hours=6.0, max_days=30.0, attribute=20):
    """Fill `result` for base..tip, cheapest and most telling checks first (raises
    BudgetExceeded midway, leaving what it finished)."""
    r = result
    r.attribute = attribute
    with concurrent.futures.ThreadPoolExecutor(max_workers=2 + len(LEDGERS)) as pool:
        # the whole range's ledger diff and the remote tip's ledgers (16 MB blobs) are read
        # beside the commit walk
        net = pool.submit(lambda: additions(git("diff", *DIFF, base, tip, "--", *LEDGERS)).get(None, {}))
        tips = {p: pool.submit(upstream_lines, git, base, p) for p in LEDGERS}
        touched = pool.submit(lambda: git("log", "--no-merges", "--reverse", "--format=%H",
                                          f"{base}..{tip}", "--", *LEDGERS).split())
        r.outgoing = commits(git, f"{base}..{tip}")
        if not r.outgoing:
            net.result(), touched.result()
            r.indexed = True
            return r
        newest = max(c[4] for c in r.outgoing)
        since = max(min(c[2] for c in r.outgoing) - int(slack_hours * 3600), newest - int(max_days * 86400))
        r.unchecked = sum(1 for c in r.outgoing if c[2] - slack_hours * 3600 < since)
        upstream = commits(git, f"--max-age={since}", base)
        for sha, email, ats, atz, _cts, subject in upstream:
            r.index[(email, ats, atz, subject)].append(sha)
            reverted = REVERT.match(subject)
            if reverted:
                r.reverts.setdefault(reverted.group(1), sha)
        r.walked, r.indexed = len(upstream), True
        r.net, r.ledger_commits = net.result(), touched.result()
        r.touched = set(r.ledger_commits)
        upstream_of = {p: job.result() for p, job in tips.items()}

    # the range's net ledger additions against the remote tip's ledgers
    r.present = {p: {line for line in v if line in upstream_of[p]} for p, v in r.net.items()}

    # which commit added them: one ledger commit is the net diff itself; else read the
    # own diffs of `attribute` ledger commits, identity twins first (the likeliest
    # replays), then in push order -- only when the net diff found a line
    if len(r.ledger_commits) == 1:
        r.added[r.ledger_commits[0]] = r.net
        r.attributed.add(r.ledger_commits[0])
    elif any(r.present.values()):
        twinned = {c[0] for c in r.outgoing if r.twins(c)}
        first = sorted(r.ledger_commits, key=lambda s: s not in twinned)[:attribute]
        r.need_diff.update(first)
        try:
            diff_all(git, first, r.diffs)
        finally:                                   # past the budget, keep the diffs that finished
            for sha in first:
                if sha in r.diffs:
                    r.added[sha] = ledger_lines(r.diffs[sha])
                    r.attributed.add(sha)
        extra = collections.defaultdict(set)      # lines a commit adds that the net diff cancels
        net = {p: set(v) for p, v in r.net.items()}
        for sha in first:
            for p, v in r.added[sha].items():
                extra[p].update(line for line in v if line not in net.get(p, ()))
        for p, v in extra.items():
            r.present.setdefault(p, set()).update(line for line in v if line in upstream_of.get(p, ()))

    # identity twins whose content is not already shown upstream: compare patch-ids
    oldest_first = list(reversed(r.outgoing))
    for commit in [c for c in oldest_first if r.twins(c) and not r.hits(c[0])][:attribute]:
        r.pairs[commit[0]] = r.twins(commit)[:TWINS_COMPARED]
    r.need_diff.update(r.pairs)
    diff_all(git, [s for sha, twins in r.pairs.items() for s in (sha, *twins)], r.diffs)
    texts = [f"commit {sha}\n{r.diffs[sha]}" for sha in
             dict.fromkeys([*r.pairs, *(u for v in r.pairs.values() for u in v)]) if sha in r.diffs]
    ids = {}
    if texts:
        for line in git("patch-id", "--stable", input="".join(texts)).splitlines():
            pid, _, sha = line.partition(" ")
            ids[sha.strip()] = pid
    r.patch_ids = ids
    return r


# ---------------------------------------------------------------- the report

Verdict = collections.namedtuple("Verdict", "commit replay hits total why")


def same_patch(r, a, b):
    if a not in r.diffs or b not in r.diffs or r.patch_ids is None:
        return None                                   # not compared
    if not r.diffs[a].strip() and not r.diffs[b].strip():
        return True                                   # two empty commits
    return r.patch_ids.get(a) is not None and r.patch_ids.get(a) == r.patch_ids.get(b)


def verdicts(r):
    """[Verdict] newest first: `replay` when the content is shown to be upstream already (ledger
    lines verbatim, or the identity twin's patch-id with no upstream revert); otherwise a
    possible replay on identity alone."""
    out = []
    for commit in r.outgoing:
        sha, subject = commit[0], commit[5]
        same = r.twins(commit)
        lines = r.added.get(sha, {})
        total = sum(len(v) for v in lines.values())
        hits = r.hits(sha)
        if not (same or hits):
            continue
        why, replay = [], bool(hits)
        if same:
            twin = "same as " + same[0][:10] + (f" (+{len(same) - 1} more)" if len(same) > 1 else "")
            compared = [same_patch(r, sha, u) for u in r.pairs.get(sha, ())]
            revert = r.reverts.get(subject)
            if True in compared and not revert:
                replay = True
                why.append(f"{twin}, same patch-id")
            elif True in compared:
                why.append(f"{twin}, same patch-id, but upstream reverted it in {revert[:10]}: a re-land?")
            elif hits:
                why.append(twin)
            elif False in compared:
                why.append(f"{twin}, patch differs")
            else:
                why.append(f"{twin}, patch not compared")
        if hits:
            why.append(f"{hits}/{total} ledger line(s) already upstream")
        out.append(Verdict(commit, replay, hits, total, why))
    return out


def unattributed_hits(r):
    """Ledger lines the push as a whole adds that are already upstream, outside the commits
    whose own additions were read."""
    if r.present is None or not r.net:
        return 0
    net = collections.Counter((p, line) for p, v in r.net.items() for line in v if line in r.present.get(p, ()))
    seen = collections.Counter((p, line) for sha in r.attributed for p, v in r.added.get(sha, {}).items()
                               for line in v)
    return sum((net - seen).values())


def gaps(r):
    """What this run did not check, as counts."""
    out = []
    if r.unchecked:
        out.append(f"{r.unchecked} outgoing commit(s) authored more than {r.max_days:g} days before the "
                   "push: identity not checked")
    touched = r.ledger_commits or []
    skipped = sum(1 for s in touched if s not in r.attributed)
    if len(touched) > 1 and skipped:
        out.append(f"{skipped} of {len(touched)} ledger-touching commit(s) were checked only through the "
                   "push's net ledger diff, not one by one, which hides a row added and dropped again "
                   "within the push")
    unpaired = sum(1 for c in r.outgoing if r.twins(c) and c[0] not in r.pairs and not r.hits(c[0]))
    if unpaired:
        out.append(f"{unpaired} identity twin(s) past --attribute {r.attribute}: patch-id not compared")
    return out


def report(git, base, tip, shadow, examples=10, slack_hours=6.0, max_days=30.0, attribute=20):
    budget = git.budget
    r = Result()
    r.max_days = max_days
    partial = None
    try:
        check(git, base, tip, r, slack_hours, max_days, attribute)
    except BudgetExceeded:
        done = sum(1 for c in r.outgoing if r.complete(c))
        partial = (f"partial: budget of {budget.limit:g}s exceeded after {done} of "
                   f"{len(r.outgoing) if r.outgoing else '?'} commit(s)")
    found = verdicts(r)
    loose = unattributed_hits(r)
    holes = gaps(r) if r.indexed else []
    if not (found or loose or holes or partial):
        return 0
    tag = "replay_check (shadow, never refuses)" if shadow else "replay_check"
    say = lambda text: print(text, file=sys.stderr)  # noqa: E731
    if partial:
        say(f"{tag}: {partial}")
    replays = [v for v in found if v.replay]
    found = replays + [v for v in found if not v.replay]          # actionable first
    if found or loose:
        say(f"{tag}: {len(found)} of {len(r.outgoing)} outgoing commit(s) may replay work already upstream "
            f"({r.walked} upstream commit(s) searched, {budget.elapsed():.2f}s)")
        ledger = [v for v in found if v.hits]
        patch = sum(1 for v in replays if not v.hits)
        say(f"  replay, content already upstream: {len(replays)} commit(s) (ledger lines already upstream "
            f"verbatim: {len(ledger)} commit(s), {sum(v.hits for v in ledger)} line(s); the identity twin's "
            f"patch-id: {patch} commit(s))")
        say(f"  possible replay, same author, author date and subject only: {len(found) - len(replays)} "
            "commit(s)")
        for v in found[:examples]:
            label = "replay" if v.replay else "possible replay"
            say(f"  {v.commit[0][:10]} {v.commit[5][:72]}  [{label}: {'; '.join(v.why)}]")
        if len(found) > examples:
            say(f"  ... and {len(found) - examples} more")
        if loose:
            say(f"  the push also adds {loose} ledger line(s) already upstream verbatim in commits not "
                f"attributed one by one (past --attribute {r.attribute}): remove the duplicates before pushing")
    elif not partial:
        say(f"{tag}: no replay found in {len(r.outgoing)} outgoing commit(s), but not all of it was checked "
            f"({budget.elapsed():.2f}s)")
    for hole in holes:
        say(f"  not checked: {hole}")
    if replays:
        say("  A replay adds content already upstream (rows that are already verified): drop it "
            "(git rebase --onto) instead of pushing it again.")
    if len(replays) < len(found):
        say("  A possible replay matches an upstream commit's author, date and subject only. An intentional "
            "re-land after a revert and an amended commit look the same: compare them (git range-diff, or "
            "git diff UPSTREAM_SHA SHA) before dropping anything.")
    return 0 if (shadow or partial) else int(bool(found or loose))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--range", nargs=2, metavar=("REMOTE_SHA", "LOCAL_SHA"), required=True)
    ap.add_argument("--shadow", action="store_true", help="report, never refuse (exit 0)")
    ap.add_argument("--examples", type=int, default=10)
    ap.add_argument("--slack-hours", type=float, default=6.0,
                    help="clock skew allowed between an original's author and committer dates")
    ap.add_argument("--max-days", type=float, default=30.0,
                    help="never walk upstream further back than this before the newest outgoing commit")
    ap.add_argument("--attribute", type=int, default=20,
                    help="per-commit diffs for at most this many ledger-touching commits and identity twins")
    ap.add_argument("--budget", type=float, default=None,
                    help="wall-clock seconds (default $BFME_SHADOW_BUDGET_S or 10; 0 = none)")
    a = ap.parse_args(argv)
    with Budget(seconds(a.budget)) as budget:
        try:
            return report(Git(budget), a.range[0], a.range[1], a.shadow, a.examples, a.slack_hours,
                          a.max_days, max(0, a.attribute))
        except (RuntimeError, ValueError, KeyError) as exc:
            print(f"replay_check: {exc}", file=sys.stderr)
            return 0 if a.shadow else 2


if __name__ == "__main__":
    exit_on_signals()
    sys.exit(main())
