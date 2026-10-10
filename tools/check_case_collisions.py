#!/usr/bin/env python3
"""Fail if any two tracked paths differ only in case, or a control path is not
lowercase.

Such a pair cannot coexist in a Windows/macOS working tree (case-insensitive
filesystems): git checks out one and silently drops the other, breaking the build
and emitting a "paths have collided" warning on clone. This guard runs in the
pre-commit hook so a colliding path can never reach master. Alternate-case sweep
shims are generated at build time (see gen_case_shims.py) and git-ignored, so they
are not tracked and never trip this check.

Control paths are the ones the hooks and tools read by exact spelling: the root,
reverse/ (ledgers, registers, baselines, inventories), tools/, .githooks/ and
.github/. Tracked under another case -- reverse/Data_Rows.csv,
reverse/Gate_Baseline.txt, or a whole Reverse/ directory -- a case-insensitive
file system still serves the file to the build under its canonical name while
every exact git lookup misses it, so each gate that selects through it verifies
nothing and a baseline edited under the variant escapes its shrink-only check
(GPT-6.1-Sol, converged data gate review, rounds 7-9). Every control path is
spelled in lowercase -- the repository's convention, which the tree already
follows -- so a control path with an upper-case letter is refused, whether or not
any base holds the file. Not control: Markdown documents and LICENSE, and the
banked evidence under reverse/attempts/ and reverse/attempt_support/, and the
per-class contracts under reverse/class_contracts/ (named after C++ classes).

  python3 tools/check_case_collisions.py             # the index (pre-commit)
  python3 tools/check_case_collisions.py --ref SHA   # a commit's tree (pre-push)
"""
import argparse
import collections
import subprocess
import sys

CONTROL_TREES = ("reverse/", "tools/", ".githooks/", ".github/")
# banked evidence, and the per-class contracts named after C++ classes (Coord2D.json):
# inputs to a generator, not registers a gate reads; collisions there are still refused
NOT_CONTROL = ("reverse/attempts/", "reverse/attempt_support/", "reverse/class_contracts/")


def tracked_paths(ref=None):
    cmd = ["git", "ls-files", "-z"] if ref is None else ["git", "ls-tree", "-r", "-z", "--name-only", ref]
    out = subprocess.run(cmd, capture_output=True, check=True).stdout.decode("utf-8", errors="surrogateescape")
    return [p for p in out.split("\0") if p]


def find_collisions(paths):
    by_lower = collections.defaultdict(list)
    for p in paths:
        by_lower[p.lower()].append(p)
    return [sorted(group) for group in by_lower.values() if len(group) > 1]


def control(path):
    """Whether the hooks or tools may read `path` by its exact spelling."""
    low = path.lower()
    # the exempt trees by their own (lowercase) spelling only: under Reverse/attempts/
    # or reverse/Attempts/ a tool selecting reverse/attempts/ would skip the file
    # (GPT-6.1-Sol, round 10); mixed-case names inside the real trees stay allowed
    if path.startswith(NOT_CONTROL) or low.endswith(".md") or low == "license":
        return False
    return "/" not in path or low.startswith(CONTROL_TREES)


def miscased(paths):
    """Control paths not spelled in lowercase (a file name or any directory)."""
    return sorted(p for p in paths if control(p) and p != p.lower())


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--ref", help="check this commit's tree instead of the index")
    args = parser.parse_args(argv)
    paths = tracked_paths(args.ref)
    collisions = find_collisions(paths)
    wrong = miscased(paths)
    if collisions:
        print("case-only path collision (breaks Windows/macOS checkout):", file=sys.stderr)
        for group in sorted(collisions):
            print("  " + "  <->  ".join(group), file=sys.stderr)
        print(
            "rename one path so they differ by more than case, or (for a dual-case "
            "include shim) make one canonical and generate the other via "
            "tools/gen_case_shims.py.",
            file=sys.stderr,
        )
    if wrong:
        print("a control path (root, reverse/, tools/, .githooks/, .github/) is not lowercase; the "
              "hooks read those by exact spelling, so they would verify nothing through it:",
              file=sys.stderr)
        for p in wrong:
            print(f"  {p}  ->  rename to {p.lower()}", file=sys.stderr)
    return 1 if collisions or wrong else 0


if __name__ == "__main__":
    sys.exit(main())
