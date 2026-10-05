#!/usr/bin/env python3
"""Refuse new private copies of classes that have a shared header.

reverse/canonical_classes.csv names the shared header for a class once one
exists. From then on a unit that declares its own body for that class
re-creates the problem the header solved: its inline members are COMDATs
that differ from everyone else's, and members it leaves out are unresolved
when the unit links. This gate stops that at commit time.

Only what the commit introduces is checked: a staged unit that did not
declare a body for the class at HEAD (a new unit, or an edit that adds the
declaration). Units that already carry a private copy are the
reconciliation backlog (tools/class_views.py --class NAME), not a reason to
refuse unrelated edits to them.

A unit that genuinely needs its own layout for a registered class (a
deliberately different codegen view, proved by its bytes) can say so on any
line:

    // class-gate: allow AsciiString <reason>

Usage:
  python3 tools/class_gate.py --staged     the commit gate
  python3 tools/class_gate.py FILE...      check files against HEAD
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_views  # noqa: E402

ALLOW = re.compile(r"//\s*class-gate:\s*allow\s+(\w+)\s+\S")


def git_text(spec):
    result = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return None
    return result.stdout.decode("latin-1")


def staged_sources():
    out = subprocess.run(["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR", "--", "Code/"],
                         cwd=ROOT, capture_output=True, text=True).stdout.split()
    return [p for p in out if p.lower().endswith((".cpp", ".c"))
            and not p.startswith(("Code/gen_asm/", "Code/gen_small/"))]


def introduced(path, text, canon):
    """Registered classes `text` declares a body for that HEAD's copy of `path` did not."""
    now = set(class_views.class_bodies(text)) & set(canon)
    if not now:
        return []
    had = set()
    # In a merge, a body either parent already carried is not introduced by
    # this commit: the other side's files are new to HEAD but not new code.
    for parent in ("HEAD", "MERGE_HEAD"):
        before = git_text(f"{parent}:{path}")
        if before:
            had |= set(class_views.class_bodies(before))
    allowed = set(ALLOW.findall(text))
    return sorted(now - had - allowed)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("files", nargs="*")
    args = parser.parse_args(argv)
    canon = class_views.canonical_classes()
    if not canon:
        return 0
    if args.staged:
        checks = [(p, git_text(f":{p}")) for p in staged_sources()]
    else:
        checks = [(p, (ROOT / p).read_text(encoding="latin-1")) for p in args.files]
    bad = 0
    for path, text in checks:
        if text is None:
            continue
        for name in introduced(path, text, canon):
            print(f"  {path}: declares its own `{name}`; include {canon[name]} instead "
                  f"(or `// class-gate: allow {name} <reason>` for a proved codegen view)", file=sys.stderr)
            bad = 1
    return bad


if __name__ == "__main__":
    sys.exit(main())
