#!/usr/bin/env python3
"""Refuse to judge history that local git state can rewrite.

Every history-dependent check reads commits as they were written: the registered-class
rename's credit (verify-record) and prepared-unit proof, class_gate's staged and range
checks, repair_queue's baseline reads, and both hooks. Local state can change what git
reports as history without changing a commit:
  - GIT_DIR, GIT_WORK_TREE or GIT_COMMON_DIR can point git at another repository, and
    GIT_INDEX_FILE at another index;
  - a shallow clone hides everything behind its boundary;
  - `info/grafts` rewrites ancestry;
  - refs under refs/replace/ swap one object for another;
  - GIT_GRAFT_FILE and GIT_REPLACE_REF_BASE point git at other grafts or replace refs.
The repository judged is the checkout's own, found from its root with those variables
unset. A variable that is set must name exactly that repository (git itself exports
GIT_INDEX_FILE to hooks, inside the git directory). trusted_env() is the environment for
every trusted git call: the repository-selection variables dropped (each call runs from
the root), GIT_INDEX_FILE absolute, replace objects off. untrusted_history() names each
problem present (and anything it cannot tell); preflight() refuses with that. Run as a
script it prints the refusal and exits 1. repair_queue.py keeps the same rule inline (the
hooks run it from stdin) and both hooks carry it in shell.

Alternates and borrowed objects (objects/info/alternates, as srv1's worktrees use) are
not refused: they add objects, never choose which one a name means, and a corrupt object
store is outside what this guards.

    python3 tools/git_trust.py [--root DIR] [WHAT]"""
import argparse
import os
import subprocess
import sys

ENV_KNOBS = ("GIT_GRAFT_FILE", "GIT_REPLACE_REF_BASE")
REPO_SELECTION = ("GIT_DIR", "GIT_WORK_TREE", "GIT_COMMON_DIR")


class UntrustedHistory(Exception):
    """Local git state rewrites history; nothing read from it may be trusted."""


def trusted_env(extra=None):
    """The environment of every trusted git call, which runs from the checkout's root:
    no repository selection of its own, GIT_INDEX_FILE (git's own, for a hook) absolute,
    and no replace objects."""
    env = {k: v for k, v in os.environ.items() if k not in REPO_SELECTION}
    if "GIT_INDEX_FILE" in env:
        env["GIT_INDEX_FILE"] = os.path.abspath(env["GIT_INDEX_FILE"])
    env["GIT_NO_REPLACE_OBJECTS"] = "1"
    env.update(extra or {})
    return env


def _spelled(path):
    """`path` absolute with symlinks resolved and its drive letter in one case. Nothing else is
    folded: a directory can be case-sensitive (fsutil), so .git and .GIT may be two directories."""
    drive, rest = os.path.splitdrive(os.path.realpath(path))
    return drive.upper() + rest


def _same(a, b):
    """Two spellings are one path only if they are equal, or the file system says both are one file."""
    a, b = _spelled(a), _spelled(b)
    if a == b:
        return True
    try:
        return os.path.samefile(a, b)
    except OSError:
        return False


def _inside(path, directory):
    """Whether `directory` is a parent of `path`, which need not exist yet (a first commit's index)."""
    parent = os.path.dirname(_spelled(path))
    while not _same(parent, directory):
        parent, child = os.path.dirname(parent), parent
        if parent == child:
            return False
    return True


def bound_repository(root):
    """(top, git_dir, common_dir) of `root`'s own repository, found from root with every
    repository-selection variable and GIT_INDEX_FILE unset; None when there is none."""
    env = {k: v for k, v in os.environ.items() if k not in REPO_SELECTION + ("GIT_INDEX_FILE",)}
    got = subprocess.run(["git", "-C", str(root), "rev-parse", "--show-toplevel", "--absolute-git-dir",
                          "--git-common-dir"], capture_output=True, text=True, env=env)
    lines = got.stdout.splitlines()
    if got.returncode or len(lines) != 3:
        return None
    top, git_dir, common = lines
    return top, git_dir, os.path.join(str(root), common)


def binding_problems(root):
    """Why the environment would make git read another repository than `root`'s own."""
    bound = bound_repository(root)
    if bound is None:
        return [f"cannot find {root}'s own repository"]
    top, git_dir, common = bound
    problems = [] if _same(top, root) else [f"{root} is not its repository's top ({top})"]
    for knob, own in (("GIT_DIR", git_dir), ("GIT_WORK_TREE", top), ("GIT_COMMON_DIR", common)):
        if knob in os.environ and not _same(os.environ[knob], own):
            problems.append(f"{knob} names {os.environ[knob]}, not this checkout's {own}")
    if "GIT_INDEX_FILE" in os.environ:
        if not _inside(os.environ["GIT_INDEX_FILE"], git_dir):
            problems.append(f"GIT_INDEX_FILE names {os.environ['GIT_INDEX_FILE']}, outside this checkout's "
                            f"git directory {git_dir}")
    return problems


def untrusted_history(root):
    """What in `root`'s repository (and this environment) makes its history untrustworthy."""
    problems = binding_problems(root)
    if problems and problems[0].startswith("cannot find"):
        return problems
    problems += [f"{knob} is set" for knob in ENV_KNOBS if knob in os.environ]

    def git(*args):
        return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=trusted_env())
    shallow = git("rev-parse", "--is-shallow-repository")
    if shallow.returncode or shallow.stdout.strip() not in ("true", "false"):
        problems.append("cannot tell whether the repository is shallow")
    elif shallow.stdout.strip() == "true":
        problems.append("the repository is shallow (git fetch --unshallow)")
    grafts = os.path.join(bound_repository(root)[2], "info", "grafts")
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
    """Raise `error` unless `root`'s own history is read exactly as its commits wrote it."""
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
