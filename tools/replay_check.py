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
            keeps all three; independent work almost never does.
  ledger    lines it adds to reverse/functions.csv or reverse/symbols.csv (net
            of lines it removes, so a moved row is not counted) that already
            exist verbatim in the remote tip's copy of that file.

COST. The upstream lookup walks only commits COMMITTED since the oldest
outgoing author date less --slack-hours (an original is committed at or after
it was authored), and never more than --max-days before the newest outgoing
commit; outgoing commits authored before that window are counted, not matched.
The ledger test is one diff of the whole range plus one `git grep` of the
remote tip; only when that finds a line does it diff commit by commit to say
which commit added it. A typical push takes well under a second.

REPORT ONLY. With --shadow (the hook) it always exits 0. Without it, it exits 1
when it finds a replay, so scripts and tests can branch on it.

  python3 tools/replay_check.py --range REMOTE_SHA LOCAL_SHA [--shadow]
"""
import argparse
import collections
import concurrent.futures
import os
import subprocess
import sys
import tempfile
import time

LEDGERS = ("reverse/functions.csv", "reverse/symbols.csv",                         # Open-BFME-2
           "targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv")  # Open-BFME-1
SEP = "\x1f"
DIFF = ("--no-color", "--no-ext-diff", "--no-textconv", "--no-renames", "-U0")


def git(*args, binary=False, ok=(0,)):
    got = subprocess.run(["git", "-c", "core.quotePath=false", *args], capture_output=True)
    if got.returncode not in ok:
        raise RuntimeError("git %s: %s" % (" ".join(args[:3]), got.stderr.decode("utf-8", "replace").strip()))
    return got.stdout if binary else got.stdout.decode("utf-8", "replace")


def commits(*rev_args):
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


def already_upstream(base, path, lines):
    """The subset of `lines` that is a whole line of `path` at `base` (one `git grep`)."""
    if not lines:
        return set()
    handle, patterns = tempfile.mkstemp(suffix=".txt")
    try:
        with os.fdopen(handle, "wb") as out:
            out.write("".join(line + "\n" for line in sorted(set(lines))).encode("utf-8"))
        got = git("grep", "-h", "-I", "-F", "-f", patterns, base, "--", path, ok=(0, 1))
    finally:
        os.unlink(patterns)
    wanted = set(lines)
    return {line.rstrip("\r") for line in got.splitlines()} & wanted


def ledger_present(base, tip):
    """{path: lines the range adds that are already lines of path at base}: one diff of the
    whole range, then one `git grep` per ledger it touched, in parallel."""
    net = additions(git("diff", *DIFF, base, tip, "--", *LEDGERS)).get(None, {})
    with concurrent.futures.ThreadPoolExecutor(max_workers=len(LEDGERS)) as pool:
        found = {p: pool.submit(already_upstream, base, p, lines) for p, lines in net.items()}
        return {p: job.result() for p, job in found.items()}


def check(base, tip, slack_hours=6.0, max_days=30.0):
    """(outgoing, findings, unchecked, walked) for base..tip.

    findings: [(sha, subject, [upstream shas with the same identity], ledger hits, ledger added)]"""
    # The ledger test reads two 16 MB blobs; run it beside the commit walk.
    with concurrent.futures.ThreadPoolExecutor(max_workers=1) as pool:
        ledger = pool.submit(ledger_present, base, tip)
        outgoing = commits(f"{base}..{tip}")
        if not outgoing:
            ledger.result()
            return [], [], 0, 0
        newest = max(c[4] for c in outgoing)
        since = max(min(c[2] for c in outgoing) - int(slack_hours * 3600), newest - int(max_days * 86400))
        unchecked = sum(1 for c in outgoing if c[2] - slack_hours * 3600 < since)
        index = collections.defaultdict(list)
        upstream = commits(f"--max-age={since}", base)
        for sha, email, ats, atz, _cts, subject in upstream:
            index[(email, ats, atz, subject)].append(sha)
        present = ledger.result()

    # which commit added each line: per-commit diffs (a 16 MB file each), so only
    # when the range adds a line already upstream
    added = {}
    if any(present.values()):
        added = additions(git("log", "--no-merges", "--full-history", *DIFF, "--format=" + SEP + "%H",
                              f"{base}..{tip}", "--", *LEDGERS))

    findings = []
    for sha, email, ats, atz, _cts, subject in outgoing:
        same = index.get((email, ats, atz, subject), [])
        lines = added.get(sha, {})
        total = sum(len(v) for v in lines.values())
        hits = sum(1 for p, v in lines.items() for line in v if line in present.get(p, ()))
        if same or hits:
            findings.append((sha, subject, same, hits, total))
    return outgoing, findings, unchecked, len(upstream)


def report(base, tip, shadow, examples=10, slack_hours=6.0, max_days=30.0):
    t0 = time.time()
    outgoing, findings, unchecked, walked = check(base, tip, slack_hours, max_days)
    if not findings:
        return 0
    tag = "replay_check (shadow, never refuses)" if shadow else "replay_check"
    identity = sum(1 for f in findings if f[2])
    ledger = [f for f in findings if f[3]]
    print(f"{tag}: {len(findings)} of {len(outgoing)} outgoing commit(s) replay work already upstream "
          f"({walked} upstream commit(s) searched, {time.time() - t0:.2f}s)", file=sys.stderr)
    print(f"  same author, author date and subject as an upstream commit: {identity}", file=sys.stderr)
    print(f"  adding ledger lines already upstream verbatim: {len(ledger)} commit(s), "
          f"{sum(f[3] for f in ledger)} line(s)", file=sys.stderr)
    if unchecked:
        print(f"  ({unchecked} outgoing commit(s) authored more than {max_days:g} days before the push: "
              "identity not checked)", file=sys.stderr)
    for sha, subject, same, hits, total in findings[:examples]:
        why = []
        if same:
            why.append("same as " + same[0][:10] + (f" (+{len(same) - 1} more)" if len(same) > 1 else ""))
        if hits:
            why.append(f"{hits}/{total} ledger line(s) already upstream")
        print(f"  {sha[:10]} {subject[:72]}  [{'; '.join(why)}]", file=sys.stderr)
    if len(findings) > examples:
        print(f"  ... and {len(findings) - examples} more", file=sys.stderr)
    print("  A replayed commit duplicates rows that are already verified; drop it (git rebase --onto) "
          "instead of pushing it again.", file=sys.stderr)
    return 0 if shadow else 1


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--range", nargs=2, metavar=("REMOTE_SHA", "LOCAL_SHA"), required=True)
    ap.add_argument("--shadow", action="store_true", help="report, never refuse (exit 0)")
    ap.add_argument("--examples", type=int, default=10)
    ap.add_argument("--slack-hours", type=float, default=6.0,
                    help="clock skew allowed between an original's author and committer dates")
    ap.add_argument("--max-days", type=float, default=30.0,
                    help="never walk upstream further back than this before the newest outgoing commit")
    a = ap.parse_args(argv)
    try:
        return report(a.range[0], a.range[1], a.shadow, a.examples, a.slack_hours, a.max_days)
    except (RuntimeError, ValueError) as exc:
        print(f"replay_check: {exc}", file=sys.stderr)
        return 0 if a.shadow else 2


if __name__ == "__main__":
    sys.exit(main())
