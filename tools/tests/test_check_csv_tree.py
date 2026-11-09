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


LEDGER_HEADER = "address,size,section,kind,name,source,status,names,defs,refs\n"
RETIRED = "?g_old@@3QBEB"


def ledger_line(name, address="0x00001000"):
    return f"{address},4,.data,global,{name},Code/A.cpp,owned,,1,1\n"


def retired_tree(repo, added, *, deleted=(RETIRED,), rowed=()):
    """Commit a base ledger, then stage one that adds `added`; returns the tree pre-commit would judge."""
    root = repo
    (root / "reverse/data_ledger.csv").write_text(LEDGER_HEADER + ledger_line("?g_kept@@3HA"), newline="\n")
    (root / "reverse/deleted_rows.csv").write_text(
        "name,target_rva,reason\n" + "".join(f"{name},0x00001000,Retyped away from the old spelling by tools/rename.py\n" for name in deleted), newline="\n")
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "ledger")
    (root / "reverse/data_ledger.csv").write_text(
        LEDGER_HEADER + ledger_line("?g_kept@@3HA") + "".join(ledger_line(name, f"0x0000{2000 + n:04X}") for n, name in enumerate(added)), newline="\n")
    git(root, "add", "-A")
    return root, git(root, "write-tree")


def test_a_row_a_regeneration_brought_back_is_refused_with_what_to_do(repo, capsys, monkeypatch):
    root, tree = retired_tree(repo, [RETIRED])
    monkeypatch.chdir(root)
    with pytest.raises(SystemExit):
        check_csv.check_retired_ledger_rows(tree)
    err = capsys.readouterr().err
    assert RETIRED in err and "Retyped away" in err
    assert "fresh objects" in err                       # the stale-index case
    assert "git checkout HEAD -- reverse/data_ledger.csv" in err   # the way out that needs nobody
    assert "git checkout refs/remotes/origin/master -- reverse/data_ledger.csv" in err   # and once it is committed
    assert "false-reject" in err                        # the case they cannot clear
    assert "data_rows.csv" in err                       # a retype reversed on purpose


def test_a_retired_name_already_in_the_ledger_is_not_new(repo, monkeypatch):
    root, _tree = retired_tree(repo, [])
    (root / "reverse/data_ledger.csv").write_text(LEDGER_HEADER + ledger_line(RETIRED), newline="\n")
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "already there")
    (root / "reverse/data_ledger.csv").write_text(LEDGER_HEADER + ledger_line(RETIRED) + ledger_line("?g_new@@3HA", "0x00002000"), newline="\n")
    git(root, "add", "-A")
    monkeypatch.chdir(root)
    assert check_csv.check_retired_ledger_rows(git(root, "write-tree")) == []


def test_a_new_name_nothing_retired_passes(repo, monkeypatch):
    root, tree = retired_tree(repo, ["?g_new@@3HA"])
    monkeypatch.chdir(root)
    assert check_csv.check_retired_ledger_rows(tree) == []


def test_a_name_data_rows_rows_again_is_excused(repo, monkeypatch):
    """A retype reversed on purpose: the name is retired in history but rowed today."""
    root, _tree = retired_tree(repo, [RETIRED])
    (root / "reverse/data_rows.csv").write_text(
        f"name,address,address_kind,size,section,source,status,evidence\n{RETIRED},0x00002000,rva,4,.data,Code/A.cpp,matched,back again\n", newline="\n")
    git(root, "add", "-A")
    monkeypatch.chdir(root)
    assert check_csv.check_retired_ledger_rows(git(root, "write-tree")) == []


def test_a_commit_is_judged_against_its_parent(repo, monkeypatch):
    """Pre-push passes a commit, not a tree."""
    root, _tree = retired_tree(repo, [RETIRED])
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "brings it back")
    monkeypatch.chdir(root)
    with pytest.raises(SystemExit):
        check_csv.check_retired_ledger_rows("HEAD")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "--allow-empty", "-m", "later")
    assert check_csv.check_retired_ledger_rows("HEAD") == []     # the row is old by then


def test_a_row_buried_in_the_outgoing_range_is_caught_at_its_tip(repo):
    """Pre-push passes only the tip, and a ledger-only commit can take pre-commit's early exit."""
    root, _tree = retired_tree(repo, [RETIRED])
    git(root, "update-ref", "refs/remotes/origin/master", "HEAD")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "brings it back")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "--allow-empty", "-m", "later")
    with pytest.raises(SystemExit):
        check_csv.check_retired_ledger_rows("HEAD")


def test_restoring_masters_ledger_clears_a_committed_refusal(repo):
    """What the message tells someone refused at push must really clear it, buried commit and all."""
    root, _tree = retired_tree(repo, [RETIRED])
    git(root, "update-ref", "refs/remotes/origin/master", "HEAD")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "brings it back")
    with pytest.raises(SystemExit):
        check_csv.check_retired_ledger_rows("HEAD")
    git(root, "checkout", "refs/remotes/origin/master", "--", "reverse/data_ledger.csv")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "leaves it out")
    assert check_csv.check_retired_ledger_rows("HEAD") == []


def test_a_tree_without_a_ledger_is_nobodys_problem(repo):
    assert check_csv.check_retired_ledger_rows(git(repo, "write-tree")) == []
