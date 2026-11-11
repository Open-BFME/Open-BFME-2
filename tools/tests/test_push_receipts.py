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


def test_a_dirty_verifier_records_no_units(repo):
    # verified with an unstaged tool or baseline edit: a receipt would name the committed verifier
    base = git(repo, "rev-parse", "HEAD")
    c1 = commit(repo, "Code/a.cpp", "a")
    (repo / "tools/build.py").write_text("an unstaged exception")
    receipt_for(repo, c1, {"Code/a.cpp"})
    assert P.cover(base, c1) == set()
    P.record_push(c1, base, None, ["Code/a.cpp"])
    assert P.push_receipt(c1) is None


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


def pushed(repo, rev, base, units, age):
    """A push receipt for `rev` over `base`, written `age` seconds ago."""
    import os
    import time
    P.record_push(rev, base, None, sorted(units))
    when = time.time() - age
    os.utime(P.folder() / f"push-{git(repo, 'rev-parse', rev)}.json", (when, when))


def rebased_batch(repo, contents=(("Code/a.cpp", "a"), ("Code/b.cpp", "b"))):
    """The verifier commit as base; a two-commit batch pushed a minute ago; another
    commit of this clone pushed since; then the batch replayed on a master that moved."""
    base = git(repo, "rev-parse", "HEAD")
    git(repo, "checkout", "-q", "-b", "batch", base)
    first = commit(repo, "Code/a.cpp", "a")
    mine = commit(repo, "Code/b.cpp", "b")
    pushed(repo, mine, base, {"Code/a.cpp", "Code/b.cpp"}, age=60)
    git(repo, "checkout", "-q", "-b", "elsewhere", base)
    other = commit(repo, "Code/z.cpp", "z")
    pushed(repo, other, base, {"Code/z.cpp"}, age=0)
    git(repo, "checkout", "-q", "-b", "master2", base)
    commit(repo, "Code/c.cpp", "master moved")
    for path, text in contents:
        tip = commit(repo, path, text)
    return first, mine, other, tip


def test_the_fallback_prefers_the_same_batchs_earlier_push_over_a_newer_one(repo):
    # C12 (sweep-header, 2026-11-10): with no hint the hook took the newest valid
    # receipt, another commit's, which proved 0 of 165; the batch's own earlier
    # attempt proves them all
    first, mine, other, tip = rebased_batch(repo)
    assert P.previous(tip) == mine
    assert P.previous(tip, hint=other) == other       # a valid hint still decides


def test_a_hint_without_a_valid_receipt_falls_back_to_the_receipts_found(repo):
    # push.py hints the tip before its rebase, which a first attempt never pushed:
    # no receipt there must not stop the search
    first, mine, other, tip = rebased_batch(repo)
    assert P.previous(tip, hint=first) == mine
    assert P.previous(tip, hint="0" * 40) == mine


@pytest.mark.parametrize("contents", [
    (("Code/a.cpp", "a"), ("Code/b.cpp", "b, edited")),                # a line changed in the replay
    (("Code/a.cpp", "a"),),                                            # a commit dropped
    (("Code/a.cpp", "a"), ("Code/b.cpp", "b"), ("Code/d.cpp", "d")),   # a commit added
])
def test_another_patch_is_no_same_batch(repo, contents):
    # no batch matches, so the newest valid receipt, as before
    first, mine, other, tip = rebased_batch(repo, contents)
    assert P.previous(tip) == other
    assert P.previous(tip, hint=first) is None          # a hinted push never takes an unrelated receipt


@pytest.mark.parametrize("replayed, carried", [(b"\0\1a", "mine"), (b"\0\1b", "other")])
def test_binary_contents_count_in_the_patch(repo, replayed, carried):
    base = git(repo, "rev-parse", "HEAD")
    git(repo, "checkout", "-q", "-b", "batch", base)
    (repo / "data.bin").write_bytes(b"\0\1a")
    mine = commit(repo, "Code/a.cpp", "a")
    git(repo, "add", "data.bin")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "--amend", "--no-edit")
    mine = git(repo, "rev-parse", "HEAD")
    pushed(repo, mine, base, {"Code/a.cpp"}, age=60)
    git(repo, "checkout", "-q", "-b", "elsewhere", base)
    other = commit(repo, "Code/z.cpp", "z")
    pushed(repo, other, base, {"Code/z.cpp"}, age=0)
    git(repo, "checkout", "-q", "-b", "master2", base)
    commit(repo, "Code/c.cpp", "master moved")
    (repo / "data.bin").write_bytes(replayed)                  # other bytes: same size, other patch
    git(repo, "add", "data.bin")
    tip = commit(repo, "Code/a.cpp", "a")
    assert P.previous(tip) == {"mine": mine, "other": other}[carried]


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


@pytest.fixture
def header_inputs(repo, monkeypatch):
    import build
    import link_check
    from types import SimpleNamespace
    commit(repo, ".gitignore", "build/\nbaselines/\n")
    for path, text in [("Code/a.cpp", "// matched\n"), ("Code/a.h", "// canonical\n"),
                       ("reverse/functions.csv", "ledger\n")]:
        commit(repo, path, text)
    output = repo / "build/a.obj"
    output.parent.mkdir()
    output.write_bytes(b"verified object")
    output.with_suffix(".deps.json").write_text("compiler receipt")
    retail, index = repo / "baselines/game.dat", repo / "build/link_index.pkl"
    retail.parent.mkdir()
    retail.write_bytes(b"retail")
    index.write_bytes(b"census")
    state = SimpleNamespace(current=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "EXE", retail)
    monkeypatch.setattr(build, "obj_path", lambda source: output)
    monkeypatch.setattr(build, "compile_is_current", lambda *a: state.current)
    monkeypatch.setattr(link_check, "INDEX", index)
    return repo, [("C", "Code/a.cpp")], state


def test_header_debt_receipts_survive_documentation_vote_and_retry_metadata_changes(header_inputs, monkeypatch):
    root, rows, _ = header_inputs
    before = git(root, "rev-parse", "HEAD")
    key = P.header_debt_key(rows, tree(root, before), before)
    assert key
    P.record_header_debt(key, rows)
    commit(root, "docs/status.md", "unrelated documentation")
    after = commit(root, "reverse/name_votes.csv", "raw vote only")
    assert before != after
    monkeypatch.setenv("BFME_PUSH_PREVIOUS", before)
    monkeypatch.setenv("BFME_PUSH_LOST_RACE", "1")
    monkeypatch.setenv("BFME_GATE_LOADS", "different temporary folder")
    monkeypatch.setenv("CODEX_TOOL_CALL_ID", "different command session")
    assert P.header_debt_key(rows, tree(root, after), after) == key
    assert P.header_debt_hit(key, rows)
    assert not P.header_debt_hit(key, [("OtherClass", "Code/a.cpp")])


@pytest.mark.parametrize("change", ["source", "header", "ledger", "verifier", "new-provider",
                                    "object", "sidecar", "retail", "index", "environment"])
def test_header_debt_receipt_invalidates_every_verification_input(header_inputs, monkeypatch, change):
    root, rows, state = header_inputs
    base = git(root, "rev-parse", "HEAD")
    key = P.header_debt_key(rows, tree(root, base), base)
    assert key
    tracked = {"source": "Code/a.cpp", "header": "Code/a.h", "ledger": "reverse/functions.csv",
               "verifier": "tools/build.py", "new-provider": "Code/new.cpp"}
    if change in tracked:
        commit(root, tracked[change], "changed verification input")
    elif change == "environment":
        monkeypatch.setenv("INCLUDE", "different compiler include search")
    else:
        path = {"object": "build/a.obj", "sidecar": "build/a.deps.json", "retail": "baselines/game.dat",
                "index": "build/link_index.pkl"}[change]
        (root / path).write_bytes(b"changed bytes")
    assert P.header_debt_key(rows, tree(root, "HEAD"), "HEAD") != key


@pytest.mark.parametrize("missing", ["stale-object", "object", "index", "dirty-input", "untracked-provider"])
def test_header_debt_receipt_declines_unprovable_inputs(header_inputs, missing):
    root, rows, state = header_inputs
    if missing == "stale-object":
        state.current = False
    elif missing == "dirty-input":
        (root / "Code/a.h").write_text("unstaged header")
    elif missing == "untracked-provider":
        (root / "Code/new.cpp").write_text("untracked provider")
    else:
        (root / ("build/a.obj" if missing == "object" else "build/link_index.pkl")).unlink()
    assert P.header_debt_key(rows, tree(root, "HEAD"), "HEAD") is None


def test_header_debt_receipts_ignore_corruption_expiry_and_write_failure(header_inputs, monkeypatch):
    import os
    import time
    root, rows, _ = header_inputs
    key = P.header_debt_key(rows, tree(root, "HEAD"), "HEAD")
    assert key and not P.header_debt_hit(key, rows)
    P.record_header_debt(key, rows)
    path = P.folder() / f"header-{key}.json"
    path.write_text("invalid json")
    assert not P.header_debt_hit(key, rows)
    P.record_header_debt(key, rows)
    old = time.time() - (P.KEEP_HOURS + 1) * 3600
    os.utime(path, (old, old))
    assert not P.header_debt_hit(key, rows)
    monkeypatch.setattr(P, "_write", lambda *a: (_ for _ in ()).throw(PermissionError("cache denied")))
    P.record_header_debt(key, rows)
    assert not P.header_debt_hit(key, rows)
