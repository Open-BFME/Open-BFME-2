"""The pre-push hook keeps reverse/name_vote_sources.csv append-only and bound.

A vote's fingerprint binds only when its row is added (tools/class_gate.py). The hook
reads every commit of the outgoing range against its parent, and when it knows no remote
base (a new ref, no usable origin/master) it reads the file's whole history instead of
passing on the static ledger check alone. Round 8's probes: the real hook in a throwaway
repository, with the real class_gate behind a stub that points it at that repository."""
import hashlib
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_hook_fail_closed import git, push_refs, repo, run, write  # noqa: E402,F401  (the fixture)

TOOLS = Path(__file__).resolve().parents[1]
HEADER = "Code/Game/Canonical.h"
VOTES = "reverse/name_vote_sources.csv"
COLUMNS = "key,hash,worker,session,source_sha\n"


def real_class_gate(repo):
    write(repo, "tools/class_gate.py",
          f"import pathlib, sys\nsys.path.insert(0, {str(TOOLS)!r})\nimport class_gate\n"
          "class_gate.ROOT = pathlib.Path.cwd()\nraise SystemExit(class_gate.main())\n")
    write(repo, HEADER, "class Canonical {};\n")
    git(repo, "add", "--", HEADER, "tools")
    git(repo, "commit", "-qm", "fixture")
    return git(repo, "rev-parse", "HEAD"), hashlib.sha256((repo / HEADER).read_bytes()).hexdigest()


def commit_votes(repo, text, message):
    write(repo, VOTES, text)
    git(repo, "add", "--", VOTES)
    git(repo, "commit", "-qm", message)


@pytest.mark.parametrize("known", [True, False])
def test_a_fingerprint_added_then_rewritten_is_refused(repo, known):
    base, sha = real_class_gate(repo)
    row = f"{HEADER}|class||Canonical,h,w,s,{sha}\n"
    commit_votes(repo, COLUMNS + row, "append a bound fingerprint")
    commit_votes(repo, COLUMNS + row.replace(sha, "f" * 64), "rewrite it")
    result = run(repo, "pre-push", push_refs(repo, base if known else "0" * 40))
    assert result.returncode == 1, (result.stdout, result.stderr)
    assert "append-only" in result.stderr
    if not known:
        assert "no known remote base" not in result.stderr


def test_bound_appends_pass_with_no_known_base(repo):
    _base, sha = real_class_gate(repo)
    row = f"{HEADER}|class||Canonical,h,w,s,{sha}\n"
    commit_votes(repo, COLUMNS + row, "one vote")
    commit_votes(repo, COLUMNS + row + row.replace(",w,s,", ",w2,s2,"), "another")
    result = run(repo, "pre-push", push_refs(repo, "0" * 40))
    assert result.returncode == 0, (result.stdout, result.stderr)
    assert "no known remote base" in result.stderr


def test_a_local_branch_named_origin_master_is_no_base(repo):
    """The hook's base is refs/remotes/origin/master, never refs/heads/origin/master."""
    base, sha = real_class_gate(repo)
    commit_votes(repo, COLUMNS + f"{HEADER}|class||Canonical,h,w,s,{sha}\n", "a bound fingerprint")
    commit_votes(repo, COLUMNS + f"{HEADER}|class||Canonical,h,w,s,{'f' * 64}\n", "rewrite it")
    git(repo, "branch", "origin/master", "HEAD")
    result = run(repo, "pre-push", push_refs(repo, "0" * 40))
    assert result.returncode == 1 and "append-only" in result.stderr, (result.stdout, result.stderr)
