#!/usr/bin/env python3
"""Report outgoing commits that repeat work already upstream (pre-push, SHADOW).

WHY. On 2026-10-06..08 automated seats re-pushed old commits 3,541 times. One
subject, "Recover counted allocator lock wrapper" (authored 2026-10-05 15:45
+0200), reached master about 80 times under different committer dates
(f12fbff21b, ace579e0f2, 9be13c8c09, ...), each copy appending one
reverse/functions.csv line that was already there; 686 "Clean up after ...:
drop N exact duplicate ledger row(s)" commits then removed 56,708 duplicate
rows. Every hook stayed green: a duplicate of a verified row is still verified.
Open-BFME-1 has no equivalent check (its seat_replay.py replays a seat's delta
onto master; it does not look for replays), so this one is new.

SIGNATURES, per outgoing (non-merge) commit, both informational:
  identity  its (author email, author date, subject) equals that of a commit
            already reachable from the remote tip: "possible replay of <sha>".
            A rebase or cherry-pick keeps all three -- and so do an intentional
            re-land after an upstream revert and an amended commit, so the
            advice is to compare (git diff <upstream sha> <sha>), nothing more.
  ledger    lines its own diff adds to reverse/functions.csv or
            reverse/symbols.csv (net of lines it removes, so a moved row is
            not counted) that already exist verbatim in the remote tip's copy:
            "check the tip for duplicate rows" (a row deleted and restored
            within the push is not a duplicate, so nothing here says remove).
A shadow detector does not tell anyone to discard a commit: proving that a
whole commit is already upstream (modes, force-pushed parents, files restored
to an earlier state) is more than it can do safely, so it never claims it.

COST. A hard wall-clock budget (tools/shadow_budget.py: $BFME_SHADOW_BUDGET_S,
default 10 s) bounds the run: each git child waits at most the budget left and
is killed past it; the tool then prints what it finished ("partial: budget ...
exceeded after N of M commit(s)") and exits 0. Within it, cheapest first: one
`git log` of the outgoing commits; an upstream walk of only the commits
COMMITTED since the oldest outgoing author date less --slack-hours, and never
more than --max-days before the newest outgoing commit (outgoing commits
authored before that window are counted, not matched); one diff of the whole
range's ledgers, its added lines looked up in the remote tip's copy of each
ledger it touches (nothing is read when it touches none; `git grep` for a few
lines, one read of the file for more). Only when that finds a line: each of
the first --attribute ledger-touching commits' own ledger diff (~0.2 s each with
a 16 MB ledger, four at a time; identity twins first) to say which commit
added it. Measured on real ranges: 500 commits ~2.3 s (was 112-114 s), 2,000
commits ~3 s (was over 240 s). What this leaves unchecked is reported as a
count: ledger commits seen only through the net diff (which hides a row added
and removed again within the push), commits authored before the walk window.

REPORT ONLY. With --shadow (the hook) it always exits 0. Without it, it exits 1
when it finds anything, so scripts and tests can branch on it.

  python3 tools/replay_check.py --range REMOTE_SHA LOCAL_SHA [--shadow]
"""
import argparse
import collections
import concurrent.futures
import os
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from shadow_budget import GIT, Budget, BudgetExceeded, seconds  # noqa: E402

LEDGERS = ("reverse/functions.csv", "reverse/symbols.csv",                         # Open-BFME-2
           "targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv")  # Open-BFME-1
SEP = "\x1f"
DIFF = ("--no-color", "--no-ext-diff", "--no-textconv", "--no-renames", "-U0")
WORKERS = 4                  # concurrent per-commit diffs
CHUNK = 3                    # commits per diff process: what a budget overrun can lose
GREP_MAX = 8                 # `git grep -F -f` tries every pattern on every line: few lines only
REVERT = re.compile(r'^Revert "(.*)"$')


class Git:
    def __init__(self, budget):
        self.budget = budget

    def __call__(self, *args, ok=(0,), input=None):
        code, out, err = self.budget.run([*GIT, *args], input=None if input is None else input.encode("utf-8"))
        if code not in ok:
            raise RuntimeError("git %s: %s" % (" ".join(args[:3]), err.decode("utf-8", "replace").strip()))
        return out.decode("utf-8", "replace")


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


def changes(text):
    """{sha or None: {path: (net added [line], net removed [line])}} from `git diff/log -U0`
    output, commits introduced by a SEP<sha> line."""
    out = {}
    sha = path = None
    header = False
    plus, minus = collections.defaultdict(collections.Counter), collections.defaultdict(collections.Counter)

    def flush():
        got = {}
        for p in set(plus) | set(minus):
            added, removed = plus[p] - minus[p], minus[p] - plus[p]
            if added or removed:
                got[p] = (sorted(added.elements()), sorted(removed.elements()))
        out[sha] = got

    for line in text.splitlines():
        if line.startswith(SEP):
            if sha is not None or plus or minus:
                flush()
            sha, path, header = line[1:].strip(), None, False
            plus.clear()
            minus.clear()
        elif line.startswith("diff --git "):
            path, header = None, True
        elif header:
            if line.startswith("--- "):
                path = line[6:] if line.startswith("--- a/") else path
            elif line.startswith("+++ "):
                path = line[6:] if line.startswith("+++ b/") else path
            elif line.startswith("@@"):
                header = False
        elif path and line.startswith("+"):
            plus[path][line[1:].rstrip("\r")] += 1
        elif path and line.startswith("-"):
            minus[path][line[1:].rstrip("\r")] += 1
    flush()
    return out


def already_upstream(git, base, path, lines, cache):
    """The subset of `lines` that is a whole line of `path` at `base`; `cache` keeps a
    ledger read whole."""
    wanted = {line for line in lines if line.strip()}      # an empty pattern matches every line
    if not wanted:
        return set()
    if path in cache:
        return cache[path] & wanted
    if len(wanted) <= GREP_MAX:
        handle, patterns = tempfile.mkstemp(suffix=".txt")
        try:
            with os.fdopen(handle, "wb") as out:
                out.write("".join(line + "\n" for line in sorted(wanted)).encode("utf-8"))
            got = git("grep", "-h", "-I", "-F", "-f", patterns, base, "--", path, ok=(0, 1))
        finally:
            os.unlink(patterns)
        return {line.rstrip("\r") for line in got.splitlines()} & wanted
    try:
        got = git("cat-file", "blob", f"{base}:{path}")
    except RuntimeError:
        got = ""                                          # no such file upstream
    cache[path] = {line.rstrip("\r") for line in got.split("\n")}
    return cache[path] & wanted


def diff_all(git, shas, into):
    """into[sha] = {ledger path: (added, removed)} of each commit, CHUNK commits per git
    process, WORKERS processes at a time; a budget overrun keeps the chunks that finished."""
    shas = [s for s in dict.fromkeys(shas) if s not in into]
    chunks = [shas[i:i + CHUNK] for i in range(0, len(shas), CHUNK)]

    def one(chunk):
        text = git("diff-tree", "--stdin", "-r", "-p", "--root", "--always", *DIFF, "--format=" + SEP + "%H",
                   "--", *LEDGERS, input="".join(s + "\n" for s in chunk))
        got = changes(text)
        return {s: got.get(s, {}) for s in chunk}

    if not chunks:
        return
    over = False
    with concurrent.futures.ThreadPoolExecutor(max_workers=min(WORKERS, len(chunks))) as pool:
        for job in [pool.submit(one, c) for c in chunks]:
            try:
                into.update(job.result())
            except BudgetExceeded:
                over = True
    if over:
        raise BudgetExceeded()


class Result:
    """What the check established so far; a budget overrun reports it as it stands."""

    def __init__(self):
        self.outgoing = []          # metadata of every outgoing commit, newest first
        self.walked = 0
        self.indexed = False        # the upstream identity index is complete
        self.index = collections.defaultdict(list)
        self.reverts = {}           # subject -> upstream sha of `Revert "subject"`
        self.unchecked = 0          # outgoing commits authored before the walk window
        self.ledger_commits = []    # outgoing commits touching a ledger, oldest first
        self.touched = set()
        self.net = None             # {path: (added, removed)}: the range's net ledger change
        self.present = None         # {path: lines already upstream}, once looked up
        self.read = {}              # ledger path -> all its lines at the remote tip, once read whole
        self.need_diff = set()
        self.ledger = {}            # sha -> {ledger path: (added, removed)}, from its own diff
        self.attribute = 0
        self.max_days = 0.0

    def twins(self, commit):
        sha, email, ats, atz, _cts, subject = commit
        return self.index.get((email, ats, atz, subject), [])

    def added(self, sha):
        return {p: v[0] for p, v in self.ledger.get(sha, {}).items()}

    def hits(self, sha):
        """How many lines this commit's own diff adds that the remote tip's ledger holds."""
        if self.present is None:
            return 0
        return sum(1 for p, v in self.added(sha).items() for line in v if line in self.present.get(p, ()))

    def complete(self, commit):
        """Every check planned for this commit finished."""
        sha = commit[0]
        if not self.indexed or (sha in self.need_diff and sha not in self.ledger):
            return False
        return not (self.present is None and sha in self.touched)


def check(git, base, tip, result, slack_hours=6.0, max_days=30.0, attribute=20):
    """Fill `result` for base..tip, cheapest first (raises BudgetExceeded midway, leaving
    what it finished)."""
    r = result
    r.attribute = attribute

    def net_change():
        net = changes(git("diff", *DIFF, base, tip, "--", *LEDGERS)).get(None, {})
        present = {p: already_upstream(git, base, p, v[0], r.read) for p, v in net.items()}
        return net, present

    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        # the range's ledger diff (two 16 MB blobs) and its lookups run beside the commit walk
        net = pool.submit(net_change)
        touched = pool.submit(lambda: git("log", "--no-merges", "--reverse", "--format=%H",
                                          f"{base}..{tip}", "--", *LEDGERS).split())
        r.outgoing = commits(git, f"{base}..{tip}")
        if r.outgoing:
            newest = max(c[4] for c in r.outgoing)
            since = max(min(c[2] for c in r.outgoing) - int(slack_hours * 3600),
                        newest - int(max_days * 86400))
            r.unchecked = sum(1 for c in r.outgoing if c[2] - slack_hours * 3600 < since)
            upstream = commits(git, f"--max-age={since}", base)
            for sha, email, ats, atz, _cts, subject in upstream:
                r.index[(email, ats, atz, subject)].append(sha)
                reverted = REVERT.match(subject)
                if reverted:
                    r.reverts.setdefault(reverted.group(1), sha)
            r.walked = len(upstream)
        r.indexed = True
        r.ledger_commits = touched.result()
        r.touched = set(r.ledger_commits)
        r.net, r.present = net.result()
    if not r.outgoing or not any(r.present.values()):
        return r

    # the net diff found lines already upstream: which commits added them? Each one's own
    # ledger diff (never the range's: a force-pushed parent makes the two differ), the
    # first `attribute` of them, identity twins first
    twinned = {c[0] for c in r.outgoing if r.twins(c)}
    wanted = sorted(r.ledger_commits, key=lambda s: s not in twinned)[:attribute]
    r.need_diff = set(wanted)
    diff_all(git, wanted, r.ledger)
    # lines a commit adds that the net diff cancels: look those up too
    net = {p: set(v[0]) for p, v in r.net.items()}
    extra = collections.defaultdict(set)
    for sha in wanted:
        for p, v in r.added(sha).items():
            extra[p].update(line for line in v if line not in net.get(p, ()))
    for p, v in extra.items():
        r.present.setdefault(p, set()).update(already_upstream(git, base, p, v, r.read))
    return r


# ---------------------------------------------------------------- the report

Verdict = collections.namedtuple("Verdict", "commit hits total why")


def verdicts(r):
    """[Verdict] newest first, for each commit with an identity twin upstream or ledger
    lines already upstream. Informational: nothing here says to discard a commit."""
    out = []
    for commit in r.outgoing:
        sha, subject = commit[0], commit[5]
        same = r.twins(commit)
        hits = r.hits(sha)
        if not (same or hits):
            continue
        total = sum(len(v) for v in r.added(sha).values())
        why = []
        if same:
            more = f" (+{len(same) - 1} more)" if len(same) > 1 else ""
            revert = r.reverts.get(subject)
            why.append(f"possible replay of {same[0][:10]}{more} (same author/date/subject"
                       + (f"; upstream reverted it in {revert[:10]})" if revert else ")"))
        if hits:
            why.append(f"{hits}/{total} added ledger line(s) already upstream: check the tip for duplicate rows")
        out.append(Verdict(commit, hits, total, why))
    return out


def unattributed_hits(r):
    """Ledger lines the push as a whole adds that are already upstream, outside the commits
    whose own additions were read."""
    if r.present is None or not r.net:
        return 0
    net = collections.Counter((p, line) for p, v in r.net.items() for line in v[0]
                              if line in r.present.get(p, ()))
    seen = collections.Counter((p, line) for sha in r.ledger for p, v in r.added(sha).items() for line in v)
    return sum((net - seen).values())


def gaps(r):
    """What this run did not check, as counts."""
    out = []
    if r.unchecked:
        out.append(f"{r.unchecked} outgoing commit(s) authored more than {r.max_days:g} days before the "
                   "push: identity not checked")
    skipped = sum(1 for s in r.ledger_commits if s not in r.ledger)
    if len(r.ledger_commits) > 1 and skipped:
        out.append(f"{skipped} of {len(r.ledger_commits)} ledger-touching commit(s) were checked only through "
                   "the push's net ledger diff, not one by one, which hides a row added and removed again "
                   "within the push")
    return out


ADVICE = {
    "duplicate": "A line the push adds is already in the upstream ledger. That is a duplicate only if the "
                 "pushed tip holds it twice (a row deleted and restored within the push is not): check with "
                 "git show TIP:reverse/functions.csv | grep -cxF 'LINE' and remove only an extra copy.",
    "possible": "A possible replay matches an upstream commit's author, date and subject. A rebased or "
                "cherry-picked copy keeps those, and so do a re-land after a revert and an amended commit: "
                "compare them (git diff UPSTREAM_SHA SHA) before deciding anything.",
}


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
    duplicates = [v for v in found if v.hits]
    possible = [v for v in found if r.twins(v.commit)]
    found = duplicates + [v for v in found if not v.hits]                 # duplicate rows first
    if found or loose:
        say(f"{tag}: {len(found)} of {len(r.outgoing)} outgoing commit(s) may repeat work already upstream "
            f"({r.walked} upstream commit(s) searched, {budget.elapsed():.2f}s)")
        say(f"  adding ledger lines already upstream: {len(duplicates)} commit(s), "
            f"{sum(v.hits for v in duplicates)} line(s); possible replays (same author/date/subject as an "
            f"upstream commit): {len(possible)} commit(s)")
        for v in found[:examples]:
            say(f"  {v.commit[0][:10]} {v.commit[5][:72]}  [{'; '.join(v.why)}]")
        if len(found) > examples:
            say(f"  ... and {len(found) - examples} more")
        if loose:
            say(f"  the push also adds {loose} ledger line(s) already upstream verbatim in commits not "
                f"attributed one by one (past --attribute {r.attribute}): check the tip for duplicate rows")
    elif not partial:
        say(f"{tag}: no repeated work found in {len(r.outgoing)} outgoing commit(s), but not all of it was "
            f"checked ({budget.elapsed():.2f}s)")
    for hole in holes:
        say(f"  not checked: {hole}")
    if duplicates or loose:
        say("  " + ADVICE["duplicate"])
    if possible:
        say("  " + ADVICE["possible"])
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
                    help="per-commit ledger diffs for at most this many ledger-touching commits")
    ap.add_argument("--budget", type=float, default=None,
                    help="wall-clock seconds (default $BFME_SHADOW_BUDGET_S or 10; 0 = none)")
    a = ap.parse_args(argv)
    budget = Budget(seconds(a.budget))
    try:
        return report(Git(budget), a.range[0], a.range[1], a.shadow, a.examples, a.slack_hours,
                      a.max_days, max(0, a.attribute))
    except (RuntimeError, ValueError, KeyError, OSError) as exc:
        print(f"replay_check: {exc}", file=sys.stderr)
        return 0 if a.shadow else 2


if __name__ == "__main__":
    sys.exit(main())
