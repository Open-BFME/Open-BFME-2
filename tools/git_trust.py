#!/usr/bin/env python3
"""Refuse to judge history that local git state can rewrite.

Every history-dependent check reads commits as they were written: the registered-class
rename's credit (verify-record) and prepared-unit proof, class_gate's staged and range
checks, repair_queue's baseline reads, and both hooks. Local state can change what git
reports as history without changing a commit:
  - a shallow clone hides everything behind its boundary;
  - `info/grafts` rewrites ancestry;
  - refs under refs/replace/ swap one object for another;
  - GIT_GRAFT_FILE and GIT_REPLACE_REF_BASE point git at other grafts or replace refs.
untrusted_history() names each one present (and anything it cannot tell); preflight()
refuses with that. Run as a script (the hooks) it prints the refusal and exits 1.
repair_queue.py keeps the same rule inline, since the hooks run it from stdin.

    python3 tools/git_trust.py [--root DIR] [WHAT]"""
import argparse
import os
import subprocess
import sys
from pathlib import Path

ENV_KNOBS = ("GIT_GRAFT_FILE", "GIT_REPLACE_REF_BASE")


class UntrustedHistory(Exception):
    """Local git state rewrites history; nothing read from it may be trusted."""


def untrusted_history(root):
    """What in `root`'s repository (and this environment) makes its history untrustworthy."""
    problems = [f"{knob} is set" for knob in ENV_KNOBS if knob in os.environ]

    def git(*args):
        return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True)
    shallow = git("rev-parse", "--is-shallow-repository")
    if shallow.returncode or shallow.stdout.strip() not in ("true", "false"):
        problems.append("cannot tell whether the repository is shallow")
    elif shallow.stdout.strip() == "true":
        problems.append("the repository is shallow (git fetch --unshallow)")
    common = git("rev-parse", "--git-common-dir")
    if common.returncode or not common.stdout.strip():
        problems.append("cannot find the git directory")
    else:
        grafts = (Path(root) / common.stdout.strip()) / "info" / "grafts"
        if os.path.lexists(grafts):
            problems.append(f"{grafts} exists")
    replaced = git("for-each-ref", "--format=%(refname)", "refs/replace/")
    if replaced.returncode:
        problems.append("cannot list refs/replace/")
    elif replaced.stdout.split():
        names = replaced.stdout.split()
        problems.append(f"refs/replace/ holds {len(names)} ref(s), e.g. {names[0]} (git replace -d)")
    return problems


def preflight(root, what, error=UntrustedHistory):
    """Raise `error` unless `root`'s history is read exactly as its commits wrote it."""
    problems = untrusted_history(root)
    if problems:
        raise error(f"{what}: local git state rewrites history ({'; '.join(problems)}); "
                    "remove it and retry")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--root", default=".")
    parser.add_argument("what", nargs="?", default="git history")
    args = parser.parse_args(argv)
    try:
        preflight(args.root, args.what)
    except UntrustedHistory as refusal:
        print(f"  {refusal}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
