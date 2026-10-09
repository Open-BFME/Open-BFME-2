#!/usr/bin/env python3
"""Refuse a byte gate that would read ledgers or compiler inputs from another state.

WHY. The build reads reverse/functions.csv, reverse/symbols.csv and
reverse/data_rows.csv from the WORKING TREE. A row rename left unstaged (the
header lane's U->V class-key renames, 2026-10-06) let units commit green that
only match under the unstaged names: the commit's own ledger still had the old
names, so HEAD was inconsistent and nothing said so. The old guard only fired when a ledger was
both staged and edited again; an unstaged-only edit slipped through.

The six compiler-decision files (driver, launchers, region resolver and its
region/override tables) likewise must be the verified state, including optional
files absent in that state: an untracked shadow override is still an input.

So before any source is verified:
  --staged      (pre-commit) every verification ledger and compiler input must be identical in
                the working tree and the index;
  --commit SHA  (pre-push)  every verification ledger and compiler input in the working tree must
                be the pushed commit's (nothing unstaged, nothing staged-only).

    python3 tools/ledger_guard.py --staged
    python3 tools/ledger_guard.py --commit <sha>
exit 0 = the gate will read the ledgers it is proving; 1 = refused (paths on stderr).
"""
import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# data_rows.csv too: build.py byte-verifies a source's data rows from the
# working-tree file (tools/data_rows.py), so an unstaged row would be proven
# in place of the committed one.
if (ROOT / "targets" / "game" / "reverse" / "functions.csv").exists():      # Open-BFME-1
    LEDGERS = ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv",
               "targets/game/reverse/data_rows.csv")
else:                                                                         # Open-BFME-2
    LEDGERS = ("reverse/functions.csv", "reverse/symbols.csv", "reverse/data_rows.csv")


# Compiler decisions read these working-tree files too. Flag defaults imports
# only standard-library modules; build.py's other local dependencies are a
# separate dependency-coverage lane, not silently claimed covered here.
COMPILER_INPUTS = ("tools/build.py", "tools/flag_defaults.py", "build.sh", "build.cmd",
                   "reverse/retail_inventory/flag_regions.csv", "reverse/flag_overrides.csv")


class InputReadError(ValueError):
    pass


def git_bytes(*args):
    done = subprocess.run(["git", *args], cwd=ROOT, capture_output=True)
    if done.returncode:
        raise InputReadError("git input read failed: " +
                             done.stderr.decode("utf-8", errors="backslashreplace").strip())
    return done.stdout


def compiler_inputs_differing(commit=None):
    """Byte-bind optional compiler inputs, including untracked shadow files.

    Only proven path absence is optional. Index conflicts, symlinks, missing
    objects and unreadable files refuse. Never import historical Python.
    """
    tree = None
    if commit is not None:
        tree = git_bytes("rev-parse", "--verify", "--end-of-options",
                         commit + "^{tree}").strip().decode("ascii")
    bad = []
    for path in COMPILER_INPUTS:
        if tree is None:
            entries = git_bytes("ls-files", "--stage", "-z", "--", path)
        else:
            entries = git_bytes("ls-tree", "-z", tree, "--", path)
        entries = [entry for entry in entries.split(b"\0") if entry]
        expected = None
        if entries:
            if len(entries) != 1:
                raise InputReadError(f"{path}: ambiguous or unmerged input")
            meta, entry_path = entries[0].split(b"\t", 1)
            mode, identity, extra = meta.split()
            # Index: mode oid stage; tree: mode type oid.
            oid = identity if tree is None else extra
            if (entry_path != path.encode() or mode not in (b"100644", b"100755") or
                    (tree is None and extra != b"0") or
                    (tree is not None and identity != b"blob")):
                raise InputReadError(f"{path}: input is not a regular blob")
            expected = git_bytes("cat-file", "blob", oid.decode("ascii"))
        disk = ROOT / path
        if disk.is_symlink():
            bad.append(path)
            continue
        try:
            actual = disk.read_bytes()
        except FileNotFoundError:
            actual = None
        except OSError as exc:
            raise InputReadError(f"{path}: cannot read working input: {exc}") from exc
        if actual != expected:
            bad.append(path)
    return bad


def differing(*spec):
    """Ledgers whose working-tree bytes differ from the index (no spec) or a commit."""
    done = subprocess.run(["git", "diff", "--name-only", *spec, "--", *LEDGERS], cwd=ROOT,
                          capture_output=True, text=True)
    if done.returncode:
        raise SystemExit(f"ledger_guard: git diff failed: {done.stderr.strip()}")
    return [p for p in done.stdout.split() if p]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--staged", action="store_true")
    group.add_argument("--commit", metavar="SHA")
    args = parser.parse_args(argv)
    bad = differing() if args.staged else differing(args.commit)
    try:
        bad += compiler_inputs_differing(None if args.staged else args.commit)
    except (InputReadError, OSError, ValueError) as exc:
        print(f"ledger_guard: {exc}", file=sys.stderr)
        return 1
    if not bad:
        return 0
    against = "the index" if args.staged else f"the pushed commit {args.commit[:10]}"
    for path in bad:
        print(f"  {path}: the working tree differs from {against}", file=sys.stderr)
    print("ledger_guard: the byte gate reads the working-tree ledgers and compiler inputs, so it would verify rows this "
          "commit does not contain. Stage (and commit) the input edit, or stash it.", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
