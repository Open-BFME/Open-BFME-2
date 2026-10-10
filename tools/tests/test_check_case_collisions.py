"""check_case_collisions: case-only collisions, and control paths (root, reverse/,
tools/, .githooks/, .github/) that are not lowercase -- in the index and in a commit,
whether or not any base holds the file (GPT-6.1-Sol, converged gate rounds 7-9)."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_case_collisions as C  # noqa: E402


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, capture_output=True, text=True).stdout.strip()


def track(root, path, text="x\n"):
    """Stage `path` with its exact spelling, whatever the file system folds."""
    blob = root / "blob.tmp"
    blob.write_text(text, encoding="utf-8")
    sha = git(root, "hash-object", "-w", str(blob))
    git(root, "update-index", "--add", "--cacheinfo", f"100644,{sha},{path}")


def untrack(root, path):
    git(root, "update-index", "--force-remove", path)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "T")
    git(tmp_path, "config", "user.email", "t@example.invalid")
    monkeypatch.chdir(tmp_path)
    return tmp_path


@pytest.mark.parametrize("variant", [
    "reverse/Data_Rows.csv", "Reverse/data_rows.csv", "REVERSE/DATA_ROWS.CSV",   # a ledger
    "reverse/Gate_Baseline.txt", "reverse/retail_inventory/Fold_List.csv",     # registers (round 8)
    "TOOLS/x.py", ".githooks/Pre-Commit", "Build.sh",                          # tools, hooks, root
])
def test_a_control_path_not_in_lowercase_is_refused_with_or_without_a_base(repo, variant, capsys):
    track(repo, variant)                                      # no base holds it (round 9)
    assert C.miscased(C.tracked_paths()) == [variant]
    assert C.main([]) == 1 and f"rename to {variant.lower()}" in capsys.readouterr().err
    git(repo, "commit", "-qm", "variant")
    assert C.main(["--ref", "HEAD"]) == 1                     # the pushed commit's tree


@pytest.mark.parametrize("variant", ["Reverse/attempts/0x0048c16c.cpp", "reverse/Attempts/0x0048c16c.cpp",
                                     "reverse/Attempt_Support/x/manifest.json",
                                     "reverse/Class_Contracts/Coord2D.json"])
def test_an_exempt_tree_spelled_in_another_case_is_control(repo, variant):
    """Round 10: the exemptions matched the lowercased path, so a stash under
    Reverse/attempts/ escaped check_csv's reverse/attempts/ selection."""
    track(repo, variant)
    assert C.main([]) == 1
    git(repo, "commit", "-qm", "variant tree")
    assert C.main(["--ref", "HEAD"]) == 1


def test_a_register_created_deleted_and_recreated_in_another_case_is_refused(repo):
    """Round 9: create the canonical register, delete it, recreate it under another
    case: the tip is what lands, and its spelling is refused whatever came before."""
    track(repo, "reverse/gate_baseline.txt")
    git(repo, "commit", "-qm", "create")
    untrack(repo, "reverse/gate_baseline.txt")
    git(repo, "commit", "-qm", "delete")
    track(repo, "Reverse/Gate_Baseline.txt", "strnul 0x00001000 _f\n")
    git(repo, "commit", "-qm", "recreate")
    assert C.main(["--ref", "HEAD"]) == 1


@pytest.mark.parametrize("path", [
    "reverse/attempts/0x0048C16C.cpp", "reverse/attempts/0x0048c16c.cpp",     # c8128a7fe1's repair, both ways
    "reverse/attempt_support/0x00191c10/README.md", "reverse/attempt_support/coordinator/A-x/manifest.json",
    "reverse/class_contracts/Coord2D.json",                                  # named after C++ classes
    "README.md", "AGENTS.md", "LICENSE", "tools/ghidra/README.md",           # documents
    "Code/GameEngine/Source/Common/Foo.cpp",                                  # not a control tree
    "reverse/data_rows.csv", "tools/check_case_collisions.py",                # control, lowercase
])
def test_lowercase_control_paths_and_non_control_paths_pass(repo, path):
    track(repo, path)
    assert C.main([]) == 0
    git(repo, "commit", "-qm", "ok")
    assert C.main(["--ref", "HEAD"]) == 0


@pytest.mark.parametrize("pair", [("Code/a.cpp", "Code/A.cpp"),
                                  ("reverse/class_contracts/Coord2D.json", "reverse/class_contracts/coord2d.json")])
def test_a_case_only_collision_is_still_refused(repo, pair):
    for path in pair:
        track(repo, path)
    assert C.main([]) == 1
