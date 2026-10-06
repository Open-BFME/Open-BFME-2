#!/usr/bin/env python3
"""Print the source files whose functions.csv claims change between two states.

Row-set semantics: a row counts as delta only if its exact tuple is absent from
the old state — new claims and edited claims need byte-proof; deletions and
reorders (dedup_csv re-sorts the whole file) cannot break byte-truth and are
ignored. Used by the git hooks to byte-verify exactly what a commit or push
adds, instead of running the full multi-minute gate.

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed state A vs committed state B (pre-push)

Output: one repo-relative source path per line (empty output = no new claims).
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = "reverse/functions.csv"


HEADER = ("name", "export_rva", "target_rva", "target_size", "source", "status", "notes")


class LedgerReadError(RuntimeError):
    pass


def git_bytes(*args):
    out = subprocess.run(["git", "-C", str(ROOT), *args], capture_output=True)
    if out.returncode:
        detail = out.stderr.decode("utf-8", errors="backslashreplace").strip()
        raise LedgerReadError(f"git {' '.join(args)} failed: {detail}")
    return out.stdout


def unborn_head():
    """Prove HEAD names an absent branch; corrupt/detached HEAD is not unborn."""
    ref = git_bytes("symbolic-ref", "--quiet", "HEAD").strip().decode("ascii")
    if not ref.startswith("refs/heads/"):
        raise LedgerReadError("HEAD does not name a branch")
    out = subprocess.run(["git", "-C", str(ROOT), "show-ref", "--verify", "--quiet", ref],
                         capture_output=True)
    if out.returncode == 1:
        return True
    if out.returncode != 0:
        raise LedgerReadError("cannot determine whether HEAD branch exists")
    return False


def rows_at(spec):
    """Read a validated ledger blob; only proven path absence means no rows."""
    if spec == f":{LEDGER}":
        entries = git_bytes("ls-files", "--stage", "-z", "--", LEDGER).split(b"\0")
        entries = [entry for entry in entries if entry]
        if not entries:
            return set()
        if len(entries) != 1:
            raise LedgerReadError("functions.csv has unresolved index stages")
        metadata, path = entries[0].split(b"\t", 1)
        mode, oid, stage = metadata.split()
        if path != LEDGER.encode() or stage != b"0" or mode not in (b"100644", b"100755"):
            raise LedgerReadError("functions.csv is not a regular stage-0 index blob")
    else:
        suffix = f":{LEDGER}"
        if not spec.endswith(suffix):
            raise LedgerReadError(f"unsupported ledger spec: {spec}")
        ref = spec[:-len(suffix)]
        tree = git_bytes("rev-parse", "--verify", "--end-of-options", ref + "^{tree}").strip()
        entries = git_bytes("ls-tree", "-z", tree.decode("ascii"), "--", LEDGER).split(b"\0")
        entries = [entry for entry in entries if entry]
        if not entries:
            return set()
        if len(entries) != 1:
            raise LedgerReadError("ambiguous functions.csv tree entry")
        metadata, path = entries[0].split(b"\t", 1)
        mode, kind, oid = metadata.split()
        if path != LEDGER.encode() or kind != b"blob" or mode not in (b"100644", b"100755"):
            raise LedgerReadError("functions.csv is not a regular tree blob")
    raw = git_bytes("cat-file", "blob", oid.decode("ascii"))
    try:
        text = raw.decode("utf-8")
        # Keep the same CSV dialect as check_csv and the byte gate. Historical
        # notes contain tolerated quote spellings; structural validation below
        # must not turn them into an unreadable state or change row semantics.
        rows = list(csv.reader(io.StringIO(text)))
    except (UnicodeDecodeError, csv.Error) as exc:
        raise LedgerReadError(f"invalid functions.csv: {exc}") from exc
    if not rows or tuple(rows[0]) != HEADER:
        raise LedgerReadError("functions.csv has missing or invalid header")
    result = set()
    for line, row in enumerate(rows[1:], 2):
        if not row or row == [""]:
            continue
        if len(row) != len(HEADER) or tuple(row) == HEADER or not row[0]:
            raise LedgerReadError(f"malformed functions.csv row {line}")
        if any("\n" in value or "\r" in value or "\0" in value for value in row):
            raise LedgerReadError(f"multiline or NUL functions.csv row {line}")
        result.add(tuple(row))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true",
                      help="delta between HEAD and the staged ledger")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"),
                      help="delta between two committed refs/SHAs")
    args = parser.parse_args()

    if args.staged:
        try:
            old = rows_at(f"HEAD:{LEDGER}")
        except LedgerReadError:
            if not unborn_head():
                raise
            old = set()
        new = rows_at(f":{LEDGER}")
    else:
        old_ref, new_ref = args.range
        old, new = rows_at(f"{old_ref}:{LEDGER}"), rows_at(f"{new_ref}:{LEDGER}")

    sources = {r[4] for r in (new - old) if len(r) >= 5 and r[4]}
    # Hooks consume this via mapfile/<(...) - force LF-only output or
    # Windows text-mode stdout appends CR to every path and -f "$s" fails.
    sys.stdout.reconfigure(newline="\n")
    for s in sorted(sources):
        print(s)


if __name__ == "__main__":
    try:
        main()
    except (LedgerReadError, OSError, ValueError) as exc:
        print(f"delta_sources: {exc}", file=sys.stderr)
        sys.exit(1)
