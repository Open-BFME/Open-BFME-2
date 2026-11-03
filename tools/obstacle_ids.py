#!/usr/bin/env python3
"""Refuse a LINK ID that a second obstacle-register entry takes (pre-commit, pre-push).

WHY. Since b0edac22fa (2026-11-03) the linking obstacle register is one file per entry in
docs/linking_obstacles/. Two agents can now give their new entries the same next free
LINK-NNN without a conflict, and every reference to that ID then names two causes. 14 IDs
already headed two entries at the split. They stay: renumbering would repoint references in
commits and logs. The newer entry gets a new ID when someone next touches it.

An entry's ID is the LINK-NNN that the heading on its first line starts with. The check
fails when a change makes more entries head an ID than before and more than one does, so
the old pairs pass and a third entry on one of them does not.

  python3 tools/obstacle_ids.py --staged          the index against HEAD (pre-commit)
  python3 tools/obstacle_ids.py --range BASE TIP  TIP's tree against BASE's (pre-push)

Exit 1 names the IDs, their files and the next free ID. Exit 2: git could not be read, and
the hook fails closed.
"""
import argparse
import re
import subprocess
import sys

REGISTER = "docs/linking_obstacles/"
PAGE = "docs/linking_obstacles.md"
HEADING = r"^#+ LINK-[0-9]+"


def git(*args):
    got = subprocess.run(["git", *args], capture_output=True, text=True, encoding="utf-8", errors="replace")
    if got.returncode not in (0, 1):                       # git grep exits 1 when nothing matches
        raise RuntimeError(f"git {' '.join(args[:2])}: {got.stderr.strip() or got.returncode}")
    return got.stdout


def grep(rev, *args, paths):
    """git grep over a revision, or over the index for None."""
    index, tree = (["--cached"], []) if rev is None else ([], [rev])
    return git("grep", *index, *args, *tree, "--", *paths)


def heads(rev):
    """{LINK-NNN: [entry files whose first line's heading starts with it]}."""
    out = {}
    for line in grep(rev, "-n", "-E", HEADING, paths=[REGISTER]).splitlines():
        if rev is not None:
            line = line[len(rev) + 1:]
        path, number, text = line.split(":", 2)
        if number == "1":
            out.setdefault(re.match(r"#+ (LINK-[0-9]+)", text).group(1), []).append(path)
    return out


def next_free(rev):
    found = grep(rev, "-h", "-o", "-E", "LINK-[0-9]+", paths=[REGISTER, PAGE]).split()
    return f"LINK-{max((int(f[5:]) for f in found), default=0) + 1:03d}"


def has(rev):
    return subprocess.run(["git", "rev-parse", "-q", "--verify", f"{rev}^{{commit}}"],
                          capture_output=True).returncode == 0


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--staged", action="store_true")
    group.add_argument("--range", nargs=2, metavar=("BASE", "TIP"))
    args = parser.parse_args()
    base, tip = ("HEAD", None) if args.staged else args.range
    try:
        before = heads(base) if has(base) else {}
        after = heads(tip)
        taken = {i: sorted(paths) for i, paths in after.items()
                 if len(paths) > max(1, len(before.get(i, ())))}
        if not taken:
            return 0
        free = next_free(tip)
    except RuntimeError as error:
        print(f"obstacle_ids: {error}", file=sys.stderr)
        return 2
    for i, paths in sorted(taken.items(), key=lambda t: int(t[0][5:])):
        print(f"obstacle_ids: {i} heads {len(paths)} entries ({', '.join(paths)})", file=sys.stderr)
    print(f"obstacle_ids: give the newer entry the next free ID, {free}, and keep the older one's "
          f"({PAGE})", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
