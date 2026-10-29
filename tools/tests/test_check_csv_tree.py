"""check_csv judged as a tree (`--ref $(git write-tree)`, what pre-commit runs)
refuses everything `--staged` refuses, and a passing verdict is reused only for
the same tree, retail image and code (tools/ledger_cache.py)."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv  # noqa: E402
import ledger_cache  # noqa: E402

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"
GOOD = HEADER + "?f@@YAXXZ,,0x00001000,4,Code/A.cpp,matched,\n"
BAD = HEADER + "?f@@YAXXZ,,0x00001000,4,Code/A.cpp,maybe,\n"


def git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True,
                          text=True).stdout.strip()


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    (root / "Code").mkdir()
    git(tmp_path, "init", "-q", str(root))
    git(root, "config", "core.autocrlf", "false")
    files = {"reverse/functions.csv": GOOD, "reverse/symbols.csv": "name,address,notes\n",
             "reverse/deleted_rows.csv": "name,target_rva,reason\n", "reverse/re_attempts.log": "",
             "Code/A.cpp": "void f() {}\n"}
    for rel, text in files.items():
        (root / rel).write_bytes(text.encode())
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "base")
    for name, rel in (("FUNCTIONS", "reverse/functions.csv"), ("SYMBOLS", "reverse/symbols.csv"),
                      ("DELETED", "reverse/deleted_rows.csv"), ("RE_ATTEMPTS", "reverse/re_attempts.log"),
                      ("BODY_OWNERS", "reverse/body_owners.csv"), ("DATA_ROWS", "reverse/data_rows.csv")):
        monkeypatch.setattr(check_csv, name, root / rel)
    monkeypatch.setattr(check_csv, "ROOT", root)
    monkeypatch.setattr(ledger_cache, "ROOT", root)
    monkeypatch.setattr(ledger_cache, "folder", lambda: tmp_path / "ledger-cache")
    return root


def verdicts(root):
    """(staged verdict, tree verdict): the OK line, or 'refused'."""
    out = []
    for spec in ("", git(root, "write-tree")):
        try:
            out.append(check_csv.verdict(spec))
        except SystemExit:
            out.append("refused")
    return out


def test_a_bad_staged_row_is_refused_both_ways_though_the_worktree_is_fixed(repo):
    (repo / "reverse/functions.csv").write_bytes((BAD).encode())
    git(repo, "add", "reverse/functions.csv")
    (repo / "reverse/functions.csv").write_bytes((GOOD).encode())            # worktree differs from the index
    assert verdicts(repo) == ["refused", "refused"]


def test_a_good_staged_ledger_passes_both_ways_though_the_worktree_is_broken(repo):
    (repo / "reverse/functions.csv").write_bytes((BAD).encode())             # unstaged: the commit does not carry it
    staged, tree = verdicts(repo)
    assert staged == tree and staged.startswith("check_csv: OK")


def test_a_source_on_disk_but_not_staged_is_refused_both_ways(repo):
    (repo / "Code/B.cpp").write_text("void g() {}\n")           # untracked
    (repo / "reverse/functions.csv").write_bytes((GOOD + "?g@@YAXXZ,,0x00002000,4,Code/B.cpp,matched,\n").encode())
    git(repo, "add", "reverse/functions.csv")
    assert verdicts(repo) == ["refused", "refused"]
    git(repo, "add", "Code/B.cpp")                                # staged with its row: both accept
    staged, tree = verdicts(repo)
    assert staged == tree and staged.startswith("check_csv: OK")


def test_a_passing_verdict_is_reused_only_for_its_tree(repo, monkeypatch, tmp_path):
    import build
    exe = tmp_path / "game.dat"
    exe.write_bytes(b"retail")
    monkeypatch.setattr(build, "EXE", exe)
    tree = git(repo, "write-tree")
    first = check_csv.passing_verdict(tree)
    runs = []
    real = check_csv.verdict
    monkeypatch.setattr(check_csv, "verdict", lambda spec: runs.append(spec) or real(spec))
    assert check_csv.passing_verdict(tree) == first and runs == []            # reused
    exe.write_bytes(b"another retail")
    assert check_csv.passing_verdict(tree) == first and runs == [tree]        # another image: judged again
    (repo / "reverse/functions.csv").write_bytes((BAD).encode())
    git(repo, "add", "reverse/functions.csv")
    bad = git(repo, "write-tree")
    for _ in range(2):                                                         # a refusal is never kept
        with pytest.raises(SystemExit):
            check_csv.passing_verdict(bad)
    assert runs == [tree, bad, bad]
