"""Receipts of byte-verification (tools/push_receipts.py): what a push may skip,
and what it must verify again."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import full_gate_receipt  # noqa: E402
import push_receipts as P  # noqa: E402


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True).stdout.strip()


def commit(root, path, text):
    (root / path).parent.mkdir(parents=True, exist_ok=True)
    (root / path).write_text(text)
    git(root, "add", path)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", path)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    monkeypatch.setattr(P, "ROOT", root)
    monkeypatch.setattr(full_gate_receipt, "ROOT", root)
    # every unit counts as cleanly verified unless a test says otherwise
    monkeypatch.setattr(P, "clean_units", lambda scope: sorted(scope))
    commit(root, "tools/build.py", "verifier")
    return root


def tree(root, rev):
    return git(root, "rev-parse", f"{rev}^{{tree}}")


def receipt_for(root, rev, scope, loads=None):
    """What pre-commit records for commit `rev` (its tree over its parent's)."""
    P.record_commit(tree(root, rev), tree(root, f"{rev}~1"), loads, sorted(scope))


def test_a_chain_of_receipted_commits_proves_its_units(repo):
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"})
    c2 = commit(repo, "Code/b.cpp", "b")
    receipt_for(repo, c2, {"Code/b.cpp", "Code/c.cpp"})
    assert P.cover(base, c2) == {"Code/a.cpp", "Code/b.cpp", "Code/c.cpp"}


def test_a_commit_without_a_receipt_proves_nothing(repo):
    # --no-verify, an amend, a rebase: no receipt for that tree over that parent
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"})
    commit(repo, "Code/b.cpp", "b")
    assert P.cover(base, "HEAD") == set()


def test_a_receipt_for_another_parent_proves_nothing(repo):
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    P.record_commit(tree(repo, c1), tree(repo, c1), None, ["Code/a.cpp"])  # an amend's view of its parent
    assert P.cover(base, c1) == set()


def test_a_unit_a_later_commit_could_affect_but_did_not_verify_drops_out(repo, monkeypatch):
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"})
    c2 = commit(repo, "Code/a.h", "header")
    monkeypatch.setattr(P, "clean_units", lambda scope: [])      # a.cpp had unstaged edits at c2
    receipt_for(repo, c2, {"Code/a.cpp"})
    assert P.cover(base, c2) == set()


def test_a_verifier_change_voids_the_receipts(repo):
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"})
    c2 = commit(repo, "tools/build.py", "verifier, changed")
    receipt_for(repo, c2, set())
    assert P.cover(base, c2) == set()


def test_a_tool_the_build_never_loaded_does_not_void_them(repo, tmp_path):
    base = git(repo, "rev-parse", "HEAD")
    loads = tmp_path / "loads"
    loads.mkdir()
    (loads / "123").write_text("tools/build.py\n")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"}, loads=loads)
    c2 = commit(repo, "tools/other.py", "unloaded")
    receipt_for(repo, c2, set())
    assert P.cover(base, c2) == {"Code/a.cpp"}


def test_a_push_receipt_carries_to_a_rebased_tip(repo):
    base = git(repo, "rev-parse", "HEAD")
    mine = commit(repo, "Code/a.cpp", "a")
    listing = repo.parent / "units"
    listing.write_bytes(b"Code/a.cpp\0Code/b.cpp\0")
    P.record_push(mine, base, None, P.read_list(listing))
    git(repo, "checkout", "-q", "-b", "master2", base)
    commit(repo, "Code/c.cpp", "master moved")
    rebased = commit(repo, "Code/a.cpp", "a")
    assert P.previous(rebased, hint=mine) == mine
    assert P.previous(rebased) == mine               # found without a hint: its base is an ancestor
    assert P.push_receipt(mine)["units"] == ["Code/a.cpp", "Code/b.cpp"]


def test_a_push_receipt_under_another_verifier_is_not_carried(repo):
    base = git(repo, "rev-parse", "HEAD")
    mine = commit(repo, "Code/a.cpp", "a")
    listing = repo.parent / "units"
    listing.write_bytes(b"Code/a.cpp\0")
    P.record_push(mine, base, None, P.read_list(listing))
    moved = commit(repo, "tools/build.py", "verifier, changed")
    assert P.previous(moved, hint=mine) is None
    assert P.previous(moved) is None


def test_a_stale_or_foreign_receipt_is_ignored(repo):
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    receipt_for(repo, c1, {"Code/a.cpp"})
    path = P.folder() / f"commit-{tree(repo, c1)}-{tree(repo, base)}.json"
    payload = json.loads(path.read_text())
    payload["tree"] = "0" * 40                        # names another tree than its key
    path.write_text(json.dumps(payload))
    assert P.cover(base, c1) == set()
    path.write_text("not json")
    assert P.cover(base, c1) == set()
    receipt_for(repo, c1, {"Code/a.cpp"})
    import os
    import time
    old = time.time() - (P.KEEP_HOURS + 1) * 3600
    os.utime(path, (old, old))
    assert P.cover(base, c1) == set()
