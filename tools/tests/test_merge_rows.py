"""The ledger merge driver registered as git's `union` (tools/merge_rows.py)."""
import os
import re
import shutil
import stat
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
sys.path.insert(0, str(TOOLS))

import merge_rows as M  # noqa: E402

H = b"name,target_rva\n"


def sides(tmp_path, base, ours, theirs):
    paths = [tmp_path / n for n in ("base", "ours", "theirs")]
    for path, data in zip(paths, (base, ours, theirs)):
        path.write_bytes(data)
    return [str(p) for p in paths]


def plain_union(tmp_path, *three):
    base, ours, theirs = sides(tmp_path, *three)
    return subprocess.run(["git", "merge-file", "-p", "--union", ours, base, theirs],
                          check=True, capture_output=True).stdout


def driver(tmp_path, *three):
    base, ours, theirs = sides(tmp_path, *three)
    assert M.main([base, ours, theirs, "functions.csv"]) == 0
    return Path(ours).read_bytes()


def test_a_row_upstream_retracted_stays_gone_beside_your_edit(tmp_path):
    three = (H + b"R,1\nS,2\n", H + b"S,2\n", H + b"R,1\nS,3\n")
    assert plain_union(tmp_path, *three) == H + b"S,2\nR,1\nS,3\n"
    assert driver(tmp_path, *three) == H + b"S,3\n"


def test_a_row_you_retracted_stays_gone_beside_an_upstream_append(tmp_path):
    three = (H + b"R,1\nS,2\n", H + b"R,1\nS,2\nT,3\n", H + b"R,1\n")
    assert plain_union(tmp_path, *three) == H + b"R,1\nS,2\nT,3\n"
    assert driver(tmp_path, *three) == H + b"R,1\nT,3\n"


def test_neighbouring_edits_keep_only_the_new_rows(tmp_path):
    three = (H + b"X,1\nY,2\n", H + b"X,9\nY,2\n", H + b"X,1\nY,8\n")
    assert plain_union(tmp_path, *three) == H + b"X,9\nY,2\nX,1\nY,8\n"
    assert driver(tmp_path, *three) == H + b"X,9\nY,8\n"


def test_a_row_both_sides_added_is_kept_once(tmp_path):
    three = (H, H + b"N,5\nP,6\n", H + b"Q,7\nN,5\n")
    assert plain_union(tmp_path, *three) == H + b"N,5\nP,6\nQ,7\nN,5\n"
    assert driver(tmp_path, *three) == H + b"N,5\nP,6\nQ,7\n"


def test_a_row_both_sides_edited_keeps_both_versions_for_check_csv(tmp_path):
    three = (H + b"S,2\n", H + b"S,3\n", H + b"S,4\n")
    assert driver(tmp_path, *three) == plain_union(tmp_path, *three) == H + b"S,3\nS,4\n"


def test_check_csv_names_a_row_both_sides_edited(tmp_path):
    """The driver never picks a side: both versions stay, and check_csv refuses the pair."""
    import check_csv

    def ledger(note):
        return (check_csv.FUNCTIONS_HEADER + "\n"
                f"?f@@YAXXZ,,0x00401000,16,Code/a.cpp,matched,{note}\n").encode()
    merged = driver(tmp_path, ledger(""), ledger("ours"), ledger("theirs"))
    assert merged.count(b"?f@@YAXXZ,") == 2
    assert b"matched,ours\n" in merged and b"matched,theirs\n" in merged
    problems = []
    check_csv.check_functions(merged, problems, {"Code/a.cpp"})
    assert any("exact duplicate row for ?f@@YAXXZ @ 0x00401000" in p for p in problems), problems


def test_terminators_survive_and_an_lf_copy_is_not_a_second_row(tmp_path):
    c = b"name,target_rva\r\n"
    three = (c + b"A,1\r\r\nB,2\r\n",
             c + b"A,1\r\r\nB,2\r\nC,3\r\n",
             c + b"A,1\r\r\nB,2\nD,4\n")
    assert plain_union(tmp_path, *three) == c + b"A,1\r\r\nB,2\r\nC,3\r\nB,2\nD,4\n"
    assert driver(tmp_path, *three) == c + b"A,1\r\r\nB,2\r\nC,3\r\nD,4\n"


def test_appends_after_a_last_row_without_a_newline_stay_separate_rows(tmp_path):
    three = (H + b"A,1", H + b"A,1\nB,2", H + b"A,1\nC,3")
    assert driver(tmp_path, *three) == plain_union(tmp_path, *three) == H + b"A,1\nB,2\nC,3"


def test_a_dropped_final_newline_does_not_duplicate_the_last_row(tmp_path):
    three = (H + b"A,1\n", H + b"A,1", H + b"A,1\nC,3\n")
    assert plain_union(tmp_path, *three) == H + b"A,1\nA,1\nC,3\n"
    assert driver(tmp_path, *three) == H + b"A,1\nC,3\n"


def test_an_edit_to_a_last_row_without_a_newline_replaces_it(tmp_path):
    three = (H + b"A,1\nB,2", H + b"A,1\nB,2\nC,3\n", H + b"A,1\nB,9")
    assert plain_union(tmp_path, *three) == H + b"A,1\nB,2\nC,3\nB,9"
    assert driver(tmp_path, *three) == H + b"A,1\nC,3\nB,9"


def test_the_header_is_kept_once_when_both_sides_append(tmp_path):
    merged = driver(tmp_path, H + b"A,1\n", H + b"A,1\nB,2\n", H + b"A,1\nC,3\n")
    assert merged == H + b"A,1\nB,2\nC,3\n"


def test_a_replaced_header_does_not_come_back(tmp_path):
    wide = b"name,target_rva,notes\n"
    three = (H + b"A,1\n", wide + b"A,1,\n", H + b"A,1\nB,2\n")
    assert plain_union(tmp_path, *three) == wide + b"A,1,\n" + H + b"A,1\nB,2\n"
    assert driver(tmp_path, *three) == wide + b"A,1,\nB,2\n"


def test_headers_both_sides_changed_are_both_kept(tmp_path):
    notes, size = b"name,target_rva,notes\n", b"name,target_rva,size\n"
    three = (H + b"A,1\n", notes + b"A,1\n", size + b"A,1\n")
    assert driver(tmp_path, *three) == plain_union(tmp_path, *three) == notes + size + b"A,1\n"


def test_a_failed_union_leaves_a_conflict(tmp_path):
    base, ours, theirs = sides(tmp_path, H, H, H)
    Path(base).unlink()
    assert M.main([base, ours, theirs, "functions.csv"]) == 1


def test_a_rebase_uses_the_driver_registered_as_union(tmp_path):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    # The ledger's bytes, not the host's: Git for Windows ships core.autocrlf=true.
    git("config", "core.autocrlf", "false")
    git("config", "merge.union.driver", f'"{sys.executable}" "{TOOLS / "merge_rows.py"}" %O %A %B %P')
    (tmp_path / ".gitattributes").write_text("functions.csv merge=union\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(H + b"R,1\nS,2\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "mine")
    ledger.write_bytes(H + b"R,1\nS,3\n")
    git("commit", "-qam", "edit S")
    git("checkout", "-q", "master")
    ledger.write_bytes(H + b"S,2\n")
    git("commit", "-qam", "retract R")
    git("checkout", "-q", "mine")
    rebase = git("rebase", "master")
    assert ledger.read_bytes() == H + b"S,3\n"
    assert "dropped 2 line(s)" in rebase.stderr


# ---- rows the base holds more than once -------------------------------------
# Each side's change to a row's count is an addition or a removal. Two additions
# overlap, two removals overlap (the larger applies once), and an addition
# beside a removal both apply. The driver first summed two removals, so two
# sides that each cleaned up the same duplicate deleted the row they both kept.
# It only removes lines, so where git's own merge leaves fewer copies of a row
# than both sides hold, it stops instead of writing.

def count(data, key=b"R,1"):
    return [M.row(line) for line in M.lines(data)].count(key)


def model(o, a, b):
    """The same rule, written from the changes instead of the cases."""
    return o + max(a - o, b - o, 0) - max(o - a, o - b, 0)


def test_both_sides_removing_the_same_duplicate_keep_the_copy_they_both_kept(tmp_path):
    three = (H + b"R,1\nR,1\nS,2\n", H + b"R,1\nS,2\nA,3\n", H + b"R,1\nS,2\nB,4\n")
    assert plain_union(tmp_path, *three) == H + b"R,1\nS,2\nA,3\nB,4\n"
    assert driver(tmp_path, *three) == H + b"R,1\nS,2\nA,3\nB,4\n"


def test_a_duplicate_both_sides_removed_survives_beside_an_edit(tmp_path):
    three = (H + b"R,1\nR,1\nS,2\n", H + b"R,1\nS,2\nM,3\n", H + b"R,1\nS,3\n")
    assert plain_union(tmp_path, *three) == H + b"R,1\nS,2\nM,3\nS,3\n"
    assert driver(tmp_path, *three) == H + b"R,1\nM,3\nS,3\n"


@pytest.mark.parametrize("o,a,b,want", [
    (2, 1, 1, 1),   # both removed one of two
    (3, 2, 1, 1),   # unequal removals: the larger one, once
    (3, 1, 2, 1),
    (3, 2, 2, 2),
    (4, 2, 3, 2),
    (2, 1, 0, 0),   # one side removed a duplicate, the other retracted the row
    (2, 0, 1, 0),
    (2, 0, 0, 0),   # both retracted it
    (1, 0, 0, 0),
    (2, 0, 2, 0),   # one side retracted it, the other left it alone
    (2, 1, 2, 1),   # one side removed a duplicate, the other left it alone
    (2, 2, 1, 1),
    (1, 2, 2, 2),   # both added the same copy
    (0, 2, 1, 2),
    (1, 0, 2, 1),   # one retracted the row, the other added a copy
    (2, 1, 3, 2),
])
def test_how_many_copies_of_a_repeated_row_survive(tmp_path, o, a, b, want):
    assert model(o, a, b) == want
    three = tuple(H + b"R,1\n" * n + b"S,2\n" + tail for n, tail in ((o, b""), (a, b"A,3\n"), (b, b"B,4\n")))
    merged = driver(tmp_path, *three)
    assert count(merged) == want
    assert merged.replace(b"R,1\n", b"") == H + b"S,2\nA,3\nB,4\n"


def test_removals_of_different_copies_stop_instead_of_deleting_the_row(tmp_path):
    """Far enough apart, git merges both removals cleanly and no copy is left to keep."""
    middle = b"X,7\nY,8\nZ,9\n"
    three = (H + b"R,1\n" + middle + b"R,1\n", H + middle + b"R,1\n", H + b"R,1\n" + middle)
    assert plain_union(tmp_path, *three) == H + middle
    base, ours, theirs = sides(tmp_path, *three)
    assert M.main([base, ours, theirs, "functions.csv"]) == 1
    assert Path(ours).read_bytes() == three[1]


def test_the_stop_names_the_row(tmp_path, capsys):
    middle = b"X,7\nY,8\nZ,9\n"
    base, ours, theirs = sides(tmp_path, H + b"R,1\n" + middle + b"R,1\n", H + middle + b"R,1\n",
                               H + b"R,1\n" + middle)
    assert M.main([base, ours, theirs, "functions.csv"]) == 1
    err = capsys.readouterr().err
    assert "functions.csv" in err and "R,1" in err and "conflict" in err


def history(tmp_path, base, ours, theirs):
    """master holds `ours`, `side` holds `theirs`, both grown from `base`, this driver registered."""
    def git(*args, check=True):
        return subprocess.run(["git", *args], cwd=tmp_path, check=check, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    git("config", "core.autocrlf", "false")
    git("config", "merge.union.driver", f'"{sys.executable}" "{TOOLS / "merge_rows.py"}" %O %A %B %P')
    (tmp_path / ".gitattributes").write_text("functions.csv merge=union\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(base)
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(theirs)
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(ours)
    git("commit", "-qam", "ours")
    return git, ledger


@pytest.mark.parametrize("how", ["merge", "rebase"])
def test_a_real_merge_and_rebase_keep_the_copy_both_branches_kept(tmp_path, how):
    git, ledger = history(tmp_path, H + b"R,1\nR,1\nS,2\n", H + b"R,1\nS,2\nA,3\n", H + b"R,1\nS,2\nB,4\n")
    if how == "merge":
        done = git("merge", "-q", "--no-edit", "side", check=False)
    else:
        git("checkout", "-q", "side")
        done = git("rebase", "master", check=False)
    assert done.returncode == 0, done.stdout + done.stderr
    assert ledger.read_bytes() == H + b"R,1\nS,2\nA,3\nB,4\n"


def test_a_real_merge_of_different_copies_removed_stops_on_a_conflict(tmp_path):
    middle = b"X,7\nY,8\nZ,9\n"
    ours = H + middle + b"R,1\n"
    git, ledger = history(tmp_path, H + b"R,1\n" + middle + b"R,1\n", ours, H + b"R,1\n" + middle)
    done = git("merge", "-q", "--no-edit", "side", check=False)
    assert done.returncode != 0 and "merge_rows: functions.csv" in done.stderr, done.stdout + done.stderr
    assert ledger.read_bytes() == ours
    assert git("status", "--porcelain").stdout.startswith("UU functions.csv")


def test_random_ledgers_follow_the_rule_and_never_lose_a_row_both_sides_kept(tmp_path):
    """Seeded: few distinct rows, so repeats, moves, shared additions and shared removals are common."""
    import collections
    import random
    rng = random.Random(20261011)
    alphabet = [b"%c,%d" % (65 + i, i) for i in range(7)]

    def ledger(source=None):
        if source is None:
            rows = [rng.choice(alphabet) for _ in range(rng.randrange(0, 9))]
        else:
            rows = [r for r in source if rng.random() > 0.25]
            for _ in range(rng.randrange(0, 3)):
                rows.insert(rng.randrange(0, len(rows) + 1), rng.choice(alphabet))
        return rows

    def data(rows):
        return H + b"".join(r + b"\n" for r in rows)

    stopped = 0
    for trial in range(300):
        base = ledger()
        if trial % 3 == 0:
            base = list(dict.fromkeys(base))          # a clean ledger: every row once
        ours, theirs = ledger(base), ledger(base)
        three = (data(base), data(ours), data(theirs))
        union = plain_union(tmp_path, *three)
        merged, dropped, short = M.merge(union, *three)
        o, a, b, u = (collections.Counter(map(M.row, M.lines(d))) for d in (*three, union))
        want = {key: model(o[key], a[key], b[key]) for key in u | a | b}
        assert sorted(short) == sorted(key for key in a if u[key] < min(a[key], b[key])), (three, short)
        if short:
            stopped += 1
            assert all(o[key] > 1 for key in short), (three, short)        # never from a clean base
            continue
        got = collections.Counter(map(M.row, M.lines(merged)))
        assert got == +collections.Counter({key: min(u[key], n) for key, n in want.items()}), (three, merged)
        assert all(got[key] >= min(a[key], b[key]) for key in a), (three, merged)   # what both hold stays
        rest = iter(M.lines(union))
        assert all(line in rest for line in M.lines(merged)), (three, merged)   # union's order
        assert dropped == len(M.lines(union)) - len(M.lines(merged))
    assert stopped < 100, stopped


# ---- the registration a clone actually carries ------------------------------

def registered_driver():
    """The merge.union.driver command tools/setup_hooks.sh writes."""
    setup = (TOOLS / "setup_hooks.sh").read_text(encoding="utf-8")
    found = re.findall(r'^git config merge\.union\.driver "([^"]+)"$', setup, re.MULTILINE)
    assert len(found) == 1, found
    return found[0]


def pre_commit_registration():
    """The block .githooks/pre-commit runs to register the driver in older clones."""
    lines = (ROOT / ".githooks" / "pre-commit").read_text(encoding="utf-8").splitlines()
    start = next(i for i, line in enumerate(lines) if line.startswith("union_driver="))
    end = lines.index("fi", start)
    return "\n".join(lines[start:end + 1]) + "\n"


def posix_shell(name):
    """Git for Windows' own shell before anything on PATH (C:\\Windows\\System32\\bash.exe is WSL)."""
    candidates = []
    if os.name == "nt":
        git = shutil.which("git")
        if git:
            git_root = Path(git).resolve().parent.parent
            candidates += [git_root / "usr/bin" / f"{name}.exe", git_root / "bin" / f"{name}.exe"]
    found = shutil.which(name)
    if found:
        candidates.append(Path(found))
    for candidate in candidates:
        if Path(candidate).is_file():
            return str(candidate)
    pytest.skip(f"{name} is required to run the hook's registration")


@pytest.mark.parametrize("stale", [None, "python3 tools/merge_rows.py %O %A %B %P",
                                   "sh .githooks/run-python3 tools/merge_rows.py %O %A %B %P"],
                         ids=["unset", "bare-python3", "unguarded"])
def test_pre_commit_registers_what_setup_hooks_registers(tmp_path, stale):
    def git(*args, check=True):
        return subprocess.run(["git", *args], cwd=tmp_path, check=check, capture_output=True, text=True)
    git("init", "-q")
    bash = posix_shell("bash")
    if stale:
        git("config", "merge.union.driver", stale)
    first = subprocess.run([bash, "-c", pre_commit_registration()], cwd=tmp_path,
                           capture_output=True, text=True)
    assert first.returncode == 0, first.stderr
    assert "tools/merge_rows.py" in first.stderr
    assert git("config", "--get", "merge.union.driver").stdout.strip() == registered_driver()
    again = subprocess.run([bash, "-c", pre_commit_registration()], cwd=tmp_path,
                           capture_output=True, text=True)
    assert again.returncode == 0 and again.stderr == "", again.stderr


def test_a_rebase_from_a_subdirectory_runs_the_registered_command(tmp_path):
    """The command setup_hooks.sh registers, relative paths and all, through run-python3."""
    def git(*args, cwd=tmp_path):
        return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    git("config", "core.autocrlf", "false")
    git("config", "merge.union.driver", registered_driver())
    for rel in ("tools/merge_rows.py", ".githooks/run-python3"):
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / rel, tmp_path / rel)
    (tmp_path / ".gitattributes").write_bytes(b"ledgers/functions.csv merge=union\n")
    (tmp_path / "ledgers").mkdir()
    (tmp_path / "sub").mkdir()
    (tmp_path / "sub/keep").write_bytes(b"")
    ledger = tmp_path / "ledgers/functions.csv"
    ledger.write_bytes(H + b"R,1\nS,2\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "mine")
    ledger.write_bytes(H + b"R,1\nS,3\nM,4\n")
    git("commit", "-qam", "edit S, add M")
    git("checkout", "-q", "master")
    ledger.write_bytes(H + b"S,2\nU,5\n")
    git("commit", "-qam", "retract R, add U")
    git("checkout", "-q", "mine")
    rebase = git("rebase", "master", cwd=tmp_path / "sub")
    assert ledger.read_bytes() == H + b"U,5\nS,3\nM,4\n"   # union's order, without R,1 and S,2
    assert "merge_rows: ledgers/functions.csv: dropped" in rebase.stderr
    assert git("status", "--porcelain").stdout == ""


def fake_bin(tmp_path, python3_works, py_works):
    """A PATH with only `python3` and `py`, each a real Python 3 or a Store-style stub."""
    real = Path(sys.executable).as_posix()
    stub = '#!/bin/sh\necho "Python was not found" >&2\nexit 9009\n'
    scripts = {
        "python3": f'#!/bin/sh\nexec "{real}" "$@"\n' if python3_works else stub,
        "py": f'#!/bin/sh\n[ "$1" = -3 ] || exit 2\nshift\nexec "{real}" "$@"\n' if py_works else stub,
    }
    folder = tmp_path / "bin"
    folder.mkdir()
    for name, text in scripts.items():
        (folder / name).write_bytes(text.encode())
        (folder / name).chmod((folder / name).stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    return folder


def run_python3(tmp_path, python3_works, py_works):
    (tmp_path / "show.py").write_text("import sys\nprint(sys.version_info[0], *sys.argv[1:])\n")
    env = dict(os.environ, PATH=str(fake_bin(tmp_path, python3_works, py_works)))
    return subprocess.run([posix_shell("sh"), str(ROOT / ".githooks" / "run-python3"), "show.py", "a b", "%P"],
                          cwd=tmp_path, env=env, capture_output=True, text=True)


@pytest.mark.parametrize("python3_works,py_works", [(True, False), (False, True)],
                         ids=["python3", "store-stub-python3-then-py-3"])
def test_run_python3_finds_python_3_with_or_without_python3(tmp_path, python3_works, py_works):
    got = run_python3(tmp_path, python3_works, py_works)
    assert got.returncode == 0, got.stderr
    assert got.stdout.strip() == "3 a b %P"


def test_run_python3_without_any_python_leaves_the_merge_conflicted(tmp_path):
    got = run_python3(tmp_path, python3_works=False, py_works=False)
    assert got.returncode == 1 and got.stdout == ""
    assert "no working Python 3" in got.stderr and "show.py" in got.stderr


def test_run_python3_names_no_file_this_repository_lacks():
    """BFME1's launcher points at .githooks/python3.sh, which this repository does not have."""
    text = (ROOT / ".githooks" / "run-python3").read_text(encoding="utf-8")
    for path in set(re.findall(r"(?:\.githooks|tools)/[\w.\-]+", text)):
        assert path == "tools/x.py" or (ROOT / path).is_file(), path


# ---- two real branches, merged and rebased, through a clone's own setup ------

BASE = H + b"R,1\nS,2\n"


def clone(tmp_path, registered=True, driver_files=True):
    """A repo whose ledger is merge=union: the driver registered as setup_hooks.sh does, or not at all."""
    def git(*args, check=True):
        return subprocess.run(["git", *args], cwd=tmp_path, check=check, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    git("config", "core.autocrlf", "false")
    if registered:
        git("config", "merge.union.driver", registered_driver())
    if driver_files:
        for rel in ("tools/merge_rows.py", ".githooks/run-python3"):
            (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(ROOT / rel, tmp_path / rel)
    (tmp_path / ".gitattributes").write_bytes(b"reverse/functions.csv text eol=lf merge=union\n")
    (tmp_path / "reverse").mkdir()
    return git, tmp_path / "reverse/functions.csv"


def two_branches(git, ledger, ours, theirs):
    """master holds `ours`, branch `side` holds `theirs`, both grown from BASE; master is checked out."""
    ledger.write_bytes(BASE)
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(theirs)
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(ours)
    git("commit", "-qam", "ours")


def integrate(git, how):
    """Bring `side` and master together; either way master's rows come first."""
    if how == "merge":
        return git("merge", "-q", "--no-edit", "side", check=False)
    git("checkout", "-q", "side")
    return git("rebase", "master", check=False)


BOTH = pytest.mark.parametrize("how", ["merge", "rebase"])


@BOTH
def test_two_branches_appending_different_rows_keep_every_row_once(tmp_path, how):
    git, ledger = clone(tmp_path)
    two_branches(git, ledger, BASE + b"M,3\nN,4\n", BASE + b"T,5\n")
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    assert ledger.read_bytes() == BASE + b"M,3\nN,4\nT,5\n"
    assert git("status", "--porcelain").stdout == ""


@BOTH
def test_two_branches_adding_the_same_row_keep_it_once(tmp_path, how):
    git, ledger = clone(tmp_path)
    two_branches(git, ledger, BASE + b"N,5\nP,6\n", BASE + b"Q,7\nN,5\n")
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    assert ledger.read_bytes() == BASE + b"N,5\nP,6\nQ,7\n"
    assert "dropped 1 line(s)" in done.stderr


@BOTH
def test_a_row_one_branch_deleted_and_the_other_edited_keeps_the_edit_alone(tmp_path, how):
    """Not a conflict: the old row stays deleted on both accounts, and the edit is a row only one side has."""
    git, ledger = clone(tmp_path)
    two_branches(git, ledger, H + b"S,2\n", H + b"R,9\nS,2\n")
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    assert ledger.read_bytes() == H + b"R,9\nS,2\n"
    assert git("status", "--porcelain").stdout == ""


@BOTH
def test_a_clone_that_never_registered_the_driver_gets_plain_union_not_a_conflict(tmp_path, how):
    """`union` is git's own name: with no merge.union.driver the built-in runs, resurrected rows and all."""
    git, ledger = clone(tmp_path, registered=False, driver_files=False)
    two_branches(git, ledger, H + b"S,2\nM,3\n", H + b"R,1\nS,3\n")   # ours retracts R; theirs edits S
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    merged = ledger.read_bytes()
    assert b"<<<<<<<" not in merged and b">>>>>>>" not in merged
    assert sorted(merged.splitlines()) == sorted((H + b"R,1\nS,2\nS,3\nM,3\n").splitlines())
    assert "merge_rows" not in done.stderr


def test_the_registered_driver_removes_what_the_unregistered_clone_resurrected(tmp_path):
    git, ledger = clone(tmp_path)
    two_branches(git, ledger, H + b"S,2\nM,3\n", H + b"R,1\nS,3\n")
    done = integrate(git, "merge")
    assert done.returncode == 0, done.stdout + done.stderr
    assert sorted(ledger.read_bytes().splitlines()) == sorted((H + b"S,3\nM,3\n").splitlines())


# ---- checkouts older than the driver, in a repository whose config names it --
# Worktrees share one .git/config, and the first commit attempted through the
# new pre-commit registers the driver for all of them. The registered command
# checks for its own two files; without both it says so and runs the merge
# git's built-in union ran before.

NOTICE = "is not in this checkout; using git merge-file --union for"
# The fallback's `git merge-file --diff-algorithm` is git 2.44's; an older git leaves a conflict and says so (plain
# merge-file would lay rows out with myers and lose one: test_a_fallback_that_cannot_run_histogram_merge_file_is_a_conflict).
_HELP = subprocess.run(["git", "merge-file", "-h"], capture_output=True, text=True)
HISTOGRAM = "--diff-algorithm" in _HELP.stdout + _HELP.stderr
NEEDS_HISTOGRAM = pytest.mark.skipif(not HISTOGRAM, reason="git merge-file has no --diff-algorithm before git 2.44: "
                                     "the fallback conflicts instead (test_an_old_git_s_fallback_is_a_conflict_that_says_why)")
RETRACT_AND_EDIT = (H + b"S,2\nM,3\n", H + b"R,1\nS,3\n")      # ours retracts R; theirs edits S
MISSING = pytest.mark.parametrize("missing", [("tools/merge_rows.py",), (".githooks/run-python3",),
                                              ("tools/merge_rows.py", ".githooks/run-python3")],
                                  ids=["no-driver", "no-launcher", "neither"])


def spaced(tmp_path, name="a clone with spaces"):
    """This repository's own path has spaces; so does every clone here."""
    (tmp_path / name).mkdir()
    return tmp_path / name


def unregistered_result(tmp_path, how, ours, theirs):
    """What a clone with no merge.union.driver makes of the same two branches."""
    git, ledger = clone(spaced(tmp_path, "never registered"), registered=False, driver_files=False)
    two_branches(git, ledger, ours, theirs)
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    return ledger.read_bytes()


@MISSING
@BOTH
@NEEDS_HISTOGRAM
def test_a_checkout_missing_a_driver_file_merges_as_built_in_union_and_says_so(tmp_path, how, missing):
    git, ledger = clone(spaced(tmp_path))
    for rel in missing:
        (ledger.parent.parent / rel).unlink()
    two_branches(git, ledger, *RETRACT_AND_EDIT)
    done = integrate(git, how)
    assert done.returncode == 0, done.stdout + done.stderr
    assert done.stderr.count(NOTICE) == 1 and "reverse/functions.csv" in done.stderr, done.stderr
    assert "merge_rows:" not in done.stderr
    assert ledger.read_bytes() == unregistered_result(tmp_path, how, *RETRACT_AND_EDIT)
    assert b"R,1\n" in ledger.read_bytes()                     # built-in union's resurrected row, as before


@NEEDS_HISTOGRAM
def test_the_fallback_lays_rows_out_as_built_in_union_does_where_plain_merge_file_would_not(tmp_path):
    """git's merge diffs with histogram, `git merge-file` with myers unless told; here they disagree."""
    base, ours, theirs = (H + b"A,0\nA,0\nB,1\nG,6\n", H + b"A,0\nA,0\nG,6\n",
                          H + b"A,0\nG,6\nB,1\nA,0\nG,6\nC,2\n")
    assert plain_union(tmp_path, base, ours, theirs) == H + b"A,0\nG,6\nB,1\nA,0\nG,6\nC,2\n"
    results = []
    for name, registered in (("registered without the files", True), ("never registered", False)):
        git, ledger = clone(spaced(tmp_path, name), registered=registered, driver_files=False)
        ledger.write_bytes(base)
        git("add", ".")
        git("commit", "-qm", "base")
        git("checkout", "-qb", "side")
        ledger.write_bytes(theirs)
        git("commit", "-qam", "theirs")
        git("checkout", "-q", "master")
        ledger.write_bytes(ours)
        git("commit", "-qam", "ours")
        done = git("merge", "-q", "--no-edit", "side", check=False)
        assert done.returncode == 0 and (NOTICE in done.stderr) == registered, done.stdout + done.stderr
        results.append(ledger.read_bytes())
    assert results[0] == results[1] == H + b"A,0\nA,0\nG,6\nB,1\nA,0\nG,6\nC,2\n"


@NEEDS_HISTOGRAM
def test_edits_far_apart_merge_cleanly_in_a_checkout_without_the_driver(tmp_path):
    """Rows a plain text merge joins without a conflict must not start conflicting."""
    git, ledger = clone(spaced(tmp_path), driver_files=False)
    rows = [b"row%d,%d\n" % (i, i) for i in range(12)]
    ledger.write_bytes(H + b"".join(rows))
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(H + b"".join(rows[:10] + [b"row10,99\n"] + rows[11:]))
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(H + b"".join([b"row0,77\n"] + rows[1:]))
    git("commit", "-qam", "ours")
    done = git("merge", "-q", "--no-edit", "side", check=False)
    assert done.returncode == 0 and NOTICE in done.stderr, done.stdout + done.stderr
    assert ledger.read_bytes() == H + b"".join([b"row0,77\n"] + rows[1:10] + [b"row10,99\n"] + rows[11:])


def linked_worktrees(tmp_path):
    """`new` is at a commit holding the driver files and has run pre-commit's registration;
    `old` is a linked worktree of the same repository at the commit before them."""
    new = spaced(tmp_path, "new worktree")

    def git(*args, cwd=new, check=True):
        return subprocess.run(["git", *args], cwd=cwd, check=check, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    for key, value in (("user.email", "t@example.com"), ("user.name", "t"), ("core.autocrlf", "false")):
        git("config", key, value)
    (new / ".gitattributes").write_bytes(b"reverse/functions.csv text eol=lf merge=union\n")
    (new / "reverse").mkdir()
    (new / "reverse/functions.csv").write_bytes(BASE)
    git("add", ".")
    git("commit", "-qm", "before the driver")
    git("branch", "pre-port")
    for rel in ("tools/merge_rows.py", ".githooks/run-python3"):
        (new / rel).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / rel, new / rel)
    git("add", ".")
    git("commit", "-qm", "the driver")
    old = tmp_path / "old worktree"
    git("worktree", "add", "-q", str(old), "pre-port")
    hook = subprocess.run([posix_shell("bash"), "-c", pre_commit_registration()], cwd=new,
                          capture_output=True, text=True)
    assert hook.returncode == 0 and "registered" in hook.stderr, hook.stderr
    for tree in (new, old):
        assert git("config", "--get", "merge.union.driver", cwd=tree).stdout.strip() == registered_driver()
    assert not (old / "tools").exists() and not (old / ".githooks").exists()
    return git, new, old


def old_branches(git, old):
    """In the old worktree: pre-port holds `ours`, old-side holds `theirs`."""
    ledger = old / "reverse/functions.csv"
    git("checkout", "-qb", "old-side", cwd=old)
    ledger.write_bytes(RETRACT_AND_EDIT[1])
    git("commit", "-qam", "theirs", cwd=old)
    git("checkout", "-q", "pre-port", cwd=old)
    ledger.write_bytes(RETRACT_AND_EDIT[0])
    git("commit", "-qam", "ours", cwd=old)
    return ledger


@pytest.mark.parametrize("operation", ["merge", "cherry-pick", "rebase", "stash-pop"])
@NEEDS_HISTOGRAM
def test_an_old_worktree_keeps_merging_after_a_sibling_registers_the_driver(tmp_path, operation):
    git, new, old = linked_worktrees(tmp_path)
    ledger = old_branches(git, old)
    if operation == "merge":
        done = git("merge", "-q", "--no-edit", "old-side", cwd=old, check=False)
    elif operation == "cherry-pick":
        done = git("cherry-pick", "old-side", cwd=old, check=False)
    elif operation == "rebase":
        git("checkout", "-q", "old-side", cwd=old)
        done = git("rebase", "pre-port", cwd=old, check=False)
    else:
        git("checkout", "-q", "old-side", cwd=old)
        ledger.write_bytes(RETRACT_AND_EDIT[1] + b"W,6\n")       # uncommitted work on top of theirs
        git("stash", cwd=old)
        git("checkout", "-q", "pre-port", cwd=old)
        done = git("stash", "pop", cwd=old, check=False)
    assert done.returncode == 0, done.stdout + done.stderr
    assert NOTICE in done.stderr, done.stderr
    merged = ledger.read_bytes()
    assert b"<<<<<<<" not in merged
    if operation == "stash-pop":
        assert {b"S,2", b"M,3", b"W,6"} <= set(merged.splitlines())
    else:
        assert sorted(merged.splitlines()) == sorted((H + b"R,1\nS,2\nS,3\nM,3\n").splitlines())
    assert "UU" not in git("status", "--porcelain", cwd=old).stdout


def test_the_new_worktree_beside_it_runs_the_driver(tmp_path):
    git, new, old = linked_worktrees(tmp_path)
    ledger = new / "reverse/functions.csv"
    git("checkout", "-qb", "side")
    ledger.write_bytes(RETRACT_AND_EDIT[1])
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(RETRACT_AND_EDIT[0])
    git("commit", "-qam", "ours")
    done = git("merge", "-q", "--no-edit", "side", check=False)
    assert done.returncode == 0 and NOTICE not in done.stderr, done.stdout + done.stderr
    assert "merge_rows: reverse/functions.csv: dropped" in done.stderr
    assert sorted(ledger.read_bytes().splitlines()) == sorted((H + b"S,3\nM,3\n").splitlines())


def test_the_first_rebase_of_a_branch_from_before_the_driver_onto_one_with_it_uses_the_driver(tmp_path):
    """The rebase checks out its destination first, so the files are there when the ledger merges."""
    git, new, old = linked_worktrees(tmp_path)
    ledger = old / "reverse/functions.csv"
    git("checkout", "-qb", "mine", cwd=old)
    ledger.write_bytes(RETRACT_AND_EDIT[1])
    git("commit", "-qam", "edit S", cwd=old)
    (new / "reverse/functions.csv").write_bytes(RETRACT_AND_EDIT[0])
    git("commit", "-qam", "retract R, add M")
    done = git("rebase", "master", cwd=old, check=False)
    assert done.returncode == 0 and NOTICE not in done.stderr, done.stdout + done.stderr
    assert "merge_rows: reverse/functions.csv: dropped" in done.stderr
    assert sorted(ledger.read_bytes().splitlines()) == sorted((H + b"S,3\nM,3\n").splitlines())
    assert (old / "tools/merge_rows.py").is_file()


@pytest.mark.parametrize("autostash", [False, True], ids=["clean", "autostash"])
@NEEDS_HISTOGRAM
def test_pull_rebase_onto_an_upstream_without_the_driver_files(tmp_path, autostash):
    """A registered clone whose upstream branch predates the files (Sol's pull-rebase-old cases)."""
    upstream = spaced(tmp_path, "upstream repo")
    git_up, ledger_up = clone(upstream, registered=False, driver_files=False)
    ledger_up.write_bytes(BASE)
    git_up("add", ".")
    git_up("commit", "-qm", "base")
    local = tmp_path / "local clone"
    subprocess.run(["git", "clone", "-q", str(upstream), str(local)], check=True, capture_output=True)

    def git(*args, check=True):
        return subprocess.run(["git", *args], cwd=local, check=check, capture_output=True, text=True)
    for key, value in (("user.email", "t@example.com"), ("user.name", "t"), ("core.autocrlf", "false"),
                       ("merge.union.driver", registered_driver())):
        git("config", key, value)
    ledger = local / "reverse/functions.csv"
    git("checkout", "-q", "-f", "master")                       # the ledger's bytes under autocrlf=false
    ledger.write_bytes(RETRACT_AND_EDIT[1])
    git("commit", "-qam", "edit S")
    ledger_up.write_bytes(RETRACT_AND_EDIT[0])
    git_up("commit", "-qam", "retract R, add M")
    if autostash:
        (local / "notes.txt").write_bytes(b"uncommitted\n")
        git("add", "notes.txt")
    done = git("pull", "--rebase", *(["--autostash"] if autostash else []), "origin", "master", check=False)
    assert done.returncode == 0, done.stdout + done.stderr
    assert NOTICE in done.stderr, done.stderr
    assert sorted(ledger.read_bytes().splitlines()) == sorted((H + b"R,1\nS,2\nS,3\nM,3\n").splitlines())
    assert not autostash or (local / "notes.txt").read_bytes() == b"uncommitted\n"


# ---- with both files present, a failure is still a conflict ------------------

def conflicted(git, ledger, done, ours):
    assert done.returncode != 0, done.stdout + done.stderr
    assert NOTICE not in done.stderr, done.stderr
    assert "CONFLICT" in done.stdout, done.stdout + done.stderr
    assert ledger.read_bytes() == ours
    assert git("status", "--porcelain").stdout.startswith("UU reverse/functions.csv")


def test_no_python_is_a_conflict_not_a_plain_union(tmp_path):
    git, ledger = clone(spaced(tmp_path))
    two_branches(git, ledger, *RETRACT_AND_EDIT)
    env = dict(os.environ, PATH=str(fake_bin(tmp_path, False, False)) + os.pathsep + os.environ["PATH"])
    done = subprocess.run(["git", "merge", "-q", "--no-edit", "side"], cwd=ledger.parent.parent, env=env,
                          capture_output=True, text=True)
    assert "no working Python 3" in done.stderr, done.stdout + done.stderr
    conflicted(git, ledger, done, RETRACT_AND_EDIT[0])


@pytest.mark.parametrize("body", ["raise RuntimeError('broken driver')\n", "import sys\nsys.exit(1)\n",
                                  "def broken(:\n"], ids=["raises", "exits-1", "syntax-error"])
def test_a_driver_that_fails_is_a_conflict_not_a_plain_union(tmp_path, body):
    git, ledger = clone(spaced(tmp_path))
    (ledger.parent.parent / "tools/merge_rows.py").write_text(body)
    two_branches(git, ledger, *RETRACT_AND_EDIT)
    conflicted(git, ledger, integrate(git, "merge"), RETRACT_AND_EDIT[0])


def test_a_failed_merge_file_inside_the_driver_is_a_conflict_not_a_plain_union(tmp_path):
    """The driver's own `git merge-file` refuses a binary ledger (a NUL byte)."""
    git, ledger = clone(spaced(tmp_path))
    ours = H + b"S,2\x00\nM,3\n"
    two_branches(git, ledger, ours, RETRACT_AND_EDIT[1])
    done = integrate(git, "merge")
    assert "merge_rows: git merge-file failed on reverse/functions.csv" in done.stderr, done.stdout + done.stderr
    conflicted(git, ledger, done, ours)


def test_copies_removed_on_both_sides_stop_the_registered_driver_too(tmp_path):
    git, ledger = clone(spaced(tmp_path))
    middle = b"X,7\nY,8\nZ,9\n"
    ours = H + middle + b"R,1\n"
    ledger.write_bytes(H + b"R,1\n" + middle + b"R,1\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(H + b"R,1\n" + middle)
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(ours)
    git("commit", "-qam", "ours")
    done = integrate(git, "merge")
    assert "merge_rows: reverse/functions.csv: leaving a conflict" in done.stderr, done.stdout + done.stderr
    conflicted(git, ledger, done, ours)


def test_check_csv_accepts_the_ledger_after_both_branches_removed_a_duplicate(tmp_path):
    """Sol's case on real rows: R survives once, and nothing about the result needs repair."""
    import check_csv

    def rows(*names):
        return (check_csv.FUNCTIONS_HEADER + "\n" + "".join(
            f"?{n}@@YAXXZ,,0x0040{i}000,16,Code/a.cpp,matched,\n" for n, i in names)).encode()
    r, s, a, b = ("r", 1), ("s", 2), ("a", 3), ("b", 4)
    git, ledger = clone(spaced(tmp_path))
    ledger.write_bytes(rows(r, r, s))
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(rows(r, s, b))
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(rows(r, s, a))
    git("commit", "-qam", "ours")
    done = integrate(git, "merge")
    assert done.returncode == 0, done.stdout + done.stderr
    assert ledger.read_bytes() == rows(r, s, a, b)
    problems = []
    check_csv.check_functions(ledger.read_bytes(), problems, {"Code/a.cpp"})
    assert problems == []


def test_check_csv_accepts_two_addresses_both_sides_gave_one_symbol(tmp_path):
    """Both versions of a row both sides edited are kept; not every ledger's checks refuse the pair."""
    import check_csv
    merged = driver(tmp_path, b"name,address,notes\n?f@@YAXXZ,0x00401000,\n",
                    b"name,address,notes\n?f@@YAXXZ,0x00402000,\n", b"name,address,notes\n?f@@YAXXZ,0x00403000,\n")
    assert merged == b"name,address,notes\n?f@@YAXXZ,0x00402000,\n?f@@YAXXZ,0x00403000,\n"
    problems = []
    check_csv.check_symbols(merged, problems)
    assert problems == []


# ---- the fallback's own failures are conflicts too ---------------------------
# Plain `git merge-file --union` is not built-in union (myers against histogram),
# so nothing stands in when the histogram call fails: the merge stops and says
# which git feature the fallback needs.

LAYOUT = (H + b"A,0\nA,0\nB,1\nG,6\n", H + b"A,0\nA,0\nG,6\n", H + b"A,0\nG,6\nB,1\nA,0\nG,6\nC,2\n")


def git_shim(tmp_path, refuse):
    """An environment whose merge driver finds a `git` that fails `merge-file` as an older git
    would (`refuse` = "option": only --diff-algorithm, with git's exit 129) or outright
    ("always"), and passes everything else to the real git. git puts GIT_EXEC_PATH first on the
    PATH of the commands it runs, which is how the driver's `git` becomes this one."""
    real = Path(shutil.which("git")).as_posix()
    folder = tmp_path / "git shim"
    folder.mkdir()
    test = 'case "$*" in *--diff-algorithm*) refuse=1 ;; esac' if refuse == "option" else "refuse=1"
    (folder / "git").write_bytes(f'''#!/bin/sh
unset GIT_EXEC_PATH
refuse=
if [ "$1" = merge-file ]; then
    echo "$*" >> "$SHIM_LOG"
    {test}
fi
if [ -n "$refuse" ]; then
    echo "error: unknown option \\`diff-algorithm=histogram'" >&2
    echo "usage: git merge-file [<options>] [-L <name1> [-L <orig> [-L <name2>]]] <file1> <orig-file> <file2>" >&2
    exit 129
fi
exec "{real}" "$@"
'''.encode())
    (folder / "git").chmod(0o755)
    log = tmp_path / "shim.log"
    log.write_bytes(b"")
    return dict(os.environ, GIT_EXEC_PATH=str(folder), SHIM_LOG=log.as_posix()), log


def layout_branches(tmp_path):
    git, ledger = clone(spaced(tmp_path), driver_files=False)
    base, ours, theirs = LAYOUT
    ledger.write_bytes(base)
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_bytes(theirs)
    git("commit", "-qam", "theirs")
    git("checkout", "-q", "master")
    ledger.write_bytes(ours)
    git("commit", "-qam", "ours")
    return git, ledger


@pytest.mark.parametrize("refuse", ["option", "always"], ids=["git-without-diff-algorithm", "merge-file-fails"])
def test_a_fallback_that_cannot_run_histogram_merge_file_is_a_conflict(tmp_path, refuse):
    """With the plain --union retry this exited 0 and wrote H A G B A G C: one A fewer than built-in union."""
    git, ledger = layout_branches(tmp_path)
    env, log = git_shim(tmp_path, refuse)
    done = subprocess.run(["git", "merge", "-q", "--no-edit", "side"], cwd=ledger.parent.parent, env=env,
                          capture_output=True, text=True)
    calls = log.read_text().splitlines()
    assert len(calls) == 1 and "--diff-algorithm=histogram" in calls[0], calls   # the shim ran; no second try
    assert done.returncode != 0, done.stdout + done.stderr
    assert "CONFLICT" in done.stdout, done.stdout + done.stderr
    assert ("git merge-file --union --diff-algorithm=histogram failed (it needs git 2.44 or newer); "
            "leaving a conflict in reverse/functions.csv") in done.stderr, done.stderr
    assert "unknown option" in done.stderr                    # git's own error is not hidden
    assert ledger.read_bytes() == LAYOUT[1]
    assert git("status", "--porcelain").stdout.startswith("UU reverse/functions.csv")


@pytest.mark.skipif(HISTOGRAM, reason="this git's merge-file has --diff-algorithm")
def test_an_old_git_s_fallback_is_a_conflict_that_says_why(tmp_path):
    """What the shim above stands in for, on a git that really is older than 2.44 (srv1's 2.43)."""
    git, ledger = layout_branches(tmp_path)
    done = subprocess.run(["git", "merge", "-q", "--no-edit", "side"], cwd=ledger.parent.parent,
                          capture_output=True, text=True)
    assert done.returncode != 0 and "CONFLICT" in done.stdout, done.stdout + done.stderr
    assert ("git merge-file --union --diff-algorithm=histogram failed (it needs git 2.44 or newer); "
            "leaving a conflict in reverse/functions.csv") in done.stderr, done.stderr
    assert ledger.read_bytes() == LAYOUT[1]
    assert git("status", "--porcelain").stdout.startswith("UU reverse/functions.csv")


@NEEDS_HISTOGRAM
def test_the_shim_itself_changes_nothing_when_it_refuses_nothing(tmp_path):
    """The same environment, shim on the driver's PATH, with a git that has the option."""
    git, ledger = layout_branches(tmp_path)
    env, log = git_shim(tmp_path, "option")
    shim = tmp_path / "git shim" / "git"
    shim.write_bytes(shim.read_bytes().replace(b"refuse=1 ;;", b"refuse= ;;"))
    done = subprocess.run(["git", "merge", "-q", "--no-edit", "side"], cwd=ledger.parent.parent, env=env,
                          capture_output=True, text=True)
    assert done.returncode == 0 and NOTICE in done.stderr, done.stdout + done.stderr
    assert len(log.read_text().splitlines()) == 1
    assert ledger.read_bytes() == H + b"A,0\nA,0\nG,6\nB,1\nA,0\nG,6\nC,2\n"


# ---- the cap: the driver keeps at most what union's layout holds --------------

def test_a_moved_row_beside_a_second_copy_keeps_what_both_sides_hold(tmp_path):
    """Sol's case, from a base with every row once. The rule alone would keep two A (ours none
    added, theirs one); union's layout holds one, which is what both sides hold, so that stands."""
    three = (H + b"A,0\nB,1\n", H + b"B,1\nA,0\n", H + b"A,0\nB,1\nA,0\n")
    assert M.copies(1, 1, 2) == 2
    assert plain_union(tmp_path, *three) == H + b"B,1\nA,0\n"
    assert driver(tmp_path, *three) == H + b"B,1\nA,0\n"


# ---- pre-commit's registration is no gate -----------------------------------

def test_a_config_that_stays_locked_gets_exactly_three_attempts(tmp_path):
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    counting = ('git() { if [ "$1" = config ] && [ "$2" = merge.union.driver ] && [ $# = 3 ]; then '
                'echo attempt >> attempts.log; return 255; fi; command git "$@"; }\n')
    done = subprocess.run([posix_shell("bash"), "-c", "set -euo pipefail\n" + counting + pre_commit_registration()
                           + "echo NEXT_GATE\n"], cwd=tmp_path, capture_output=True, text=True)
    assert done.returncode == 0 and done.stdout == "NEXT_GATE\n", done.stdout + done.stderr
    assert (tmp_path / "attempts.log").read_text().splitlines() == ["attempt"] * 3
    assert "could not write merge.union.driver in three attempts" in done.stderr

def run_registration(tmp_path):
    return subprocess.run([posix_shell("bash"), "-c", "set -euo pipefail\n" + pre_commit_registration()
                           + "echo NEXT_GATE\n"], cwd=tmp_path, capture_output=True, text=True)


def test_a_locked_config_does_not_stop_the_hook_before_its_gates(tmp_path):
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    (tmp_path / ".git/config.lock").write_bytes(b"")
    done = run_registration(tmp_path)
    assert done.returncode == 0 and done.stdout == "NEXT_GATE\n", done.stdout + done.stderr
    assert "could not write merge.union.driver" in done.stderr and "registered tools" not in done.stderr
    (tmp_path / ".git/config.lock").unlink()
    assert subprocess.run(["git", "config", "--get", "merge.union.driver"], cwd=tmp_path).returncode == 1


def test_a_config_lock_released_in_time_is_retried(tmp_path):
    import threading
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    lock = tmp_path / ".git/config.lock"
    lock.write_bytes(b"")
    timer = threading.Timer(0.5, lock.unlink)
    timer.start()
    done = run_registration(tmp_path)
    timer.join()
    assert done.returncode == 0 and done.stdout == "NEXT_GATE\n", done.stdout + done.stderr
    assert "registered tools/merge_rows.py" in done.stderr
    got = subprocess.run(["git", "config", "--get", "merge.union.driver"], cwd=tmp_path,
                         capture_output=True, text=True)
    assert got.stdout.strip() == registered_driver()


# ---- what this repository itself declares -----------------------------------

def test_every_union_ledger_in_gitattributes_is_a_tracked_line_ledger():
    """A merge=<name> nothing registers is a plain text merge; only `union` has git's fallback."""
    drivers = {}
    for line in (ROOT / ".gitattributes").read_text(encoding="utf-8").splitlines():
        fields = line.split()
        if fields and not line.startswith("#"):
            drivers.update({fields[0]: f.split("=", 1)[1] for f in fields[1:] if f.startswith("merge=")})
    assert set(drivers.values()) == {"union"}, drivers
    assert {"reverse/functions.csv", "reverse/symbols.csv", "reverse/deleted_rows.csv",
            "reverse/re_attempts.log", "reverse/data_rows.csv"} <= set(drivers)
    for path in drivers:
        assert (ROOT / path).is_file(), path
        assert path.endswith((".csv", ".log")), path


def test_the_fleet_setup_registers_the_same_driver():
    import setup_local_fleet
    assert setup_local_fleet.UNION_DRIVER == registered_driver()
    fleet = (TOOLS / "setup_local_fleet.py").read_text(encoding="utf-8")
    assert '"merge.union.driver", UNION_DRIVER)' in fleet


def test_the_registered_command_guards_itself_before_it_needs_either_file():
    """The check cannot live in the launcher: the launcher is one of the files that may be missing."""
    command = registered_driver()
    assert command.startswith("if [ -f tools/merge_rows.py ] && [ -f .githooks/run-python3 ]; then "
                              "sh .githooks/run-python3 tools/merge_rows.py %O %A %B %P; else ")
    # current, base, other; histogram is the diff git's own merge uses, and nothing else stands in for it
    assert command.endswith("else echo 'merge.union.driver: tools/merge_rows.py or .githooks/run-python3 is "
                            "not in this checkout; using git merge-file --union for' %P >&2; "
                            "git merge-file --union --diff-algorithm=histogram '%A' '%O' '%B' || "
                            "{ echo 'merge.union.driver: git merge-file --union --diff-algorithm=histogram "
                            "failed (it needs git 2.44 or newer); leaving a conflict in' %P >&2; exit 1; }; fi")
    assert command.count("git merge-file") == 3              # one call; the other two are inside messages
    assert '"' not in command and "$" not in command and "`" not in command


def test_setup_hooks_registers_the_driver_a_merge_then_uses(tmp_path):
    """Run tools/setup_hooks.sh itself in a fresh clone, then merge through what it configured."""
    git, ledger = clone(tmp_path, registered=False)
    (tmp_path / "tools/setup_hooks.sh").write_bytes(
        (TOOLS / "setup_hooks.sh").read_bytes().replace(b"\r\n", b"\n"))
    assert git("config", "--get", "merge.union.driver", check=False).stdout == ""
    # The clone has no reference/open-bfme-1 submodule, so the script's later
    # `git submodule update` stops it; the registration comes before that.
    subprocess.run([posix_shell("bash"), "tools/setup_hooks.sh"], cwd=tmp_path, capture_output=True, text=True)
    assert git("config", "--local", "--get", "merge.union.driver").stdout.strip() == registered_driver()
    two_branches(git, ledger, H + b"S,2\nM,3\n", H + b"R,1\nS,3\n")
    done = integrate(git, "merge")
    assert done.returncode == 0, done.stdout + done.stderr
    assert sorted(ledger.read_bytes().splitlines()) == sorted((H + b"S,3\nM,3\n").splitlines())
    assert "merge_rows: reverse/functions.csv: dropped" in done.stderr
