"""replay_check.py: an outgoing commit that replays one already upstream is reported -- a
replay when every change it makes is already upstream ("drop it"), duplicate rows when
only some of its ledger lines are ("remove them"), and on author, author date and
subject alone a possible replay with neutral advice; fresh work, a moved row and a
clean push are not. What it does not check is counted, and a hard wall-clock budget
ends it with a partial report, killing only its direct git children and leaving no
thread behind. Report only: --shadow always exits 0."""
import os
import subprocess
import sys
import threading
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
TOOL = TOOLS / "replay_check.py"
sys.path.insert(0, str(TOOLS))
import replay_check  # noqa: E402
import shadow_budget  # noqa: E402

DAY = 24 * 3600
T0 = 1_900_000_000
HEADER = "name,aliases,target_rva,target_size,source,status,notes\n"
ROW_A = "?a@@YAXXZ,,0x00001000,16,Code/a.cpp,matched,\n"
ROW_B = "?b@@YAXXZ,,0x00002000,16,Code/b.cpp,matched,counted lock wrapper\n"
ROW_C = "?c@@YAXXZ,,0x00003000,16,Code/c.cpp,matched,\n"


class Repo:
    def __init__(self, root):
        self.root = root
        self.git("init", "-q")
        self.git("checkout", "-q", "-b", "master")

    def git(self, *args, author=T0, committer=None, email="seat@example.com"):
        env = dict(os.environ, GIT_AUTHOR_NAME="seat", GIT_COMMITTER_NAME="seat",
                   GIT_AUTHOR_EMAIL=email, GIT_COMMITTER_EMAIL=email,
                   GIT_AUTHOR_DATE="@%d +0200" % author,
                   GIT_COMMITTER_DATE="@%d +0200" % (author if committer is None else committer))
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        if got.returncode:
            raise AssertionError(got.stderr)
        return got.stdout.strip()

    def ledger(self, *rows):
        path = self.root / "reverse" / "functions.csv"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(HEADER + "".join(rows), newline="\n")

    def write(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, newline="\n")

    def commit(self, subject, **who):
        self.git("add", "-A")
        self.git("commit", "-q", "--allow-empty", "-m", subject, **who)
        return self.git("rev-parse", "HEAD")

    def check(self, base, tip, *extra, env=None):
        return subprocess.run([sys.executable, str(TOOL), "--range", base, tip, *extra],
                              cwd=self.root, capture_output=True, text=True, env=env)


@pytest.fixture
def repo(tmp_path):
    r = Repo(tmp_path)
    r.ledger(ROW_A)
    r.commit("base", author=T0)
    r.ledger(ROW_A, ROW_B)
    r.original = r.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 3700)
    r.upstream = r.git("rev-parse", "HEAD")
    return r


def test_replayed_commit_is_reported(repo):
    # a seat replays the original onto master: same author, author date and
    # subject, and the union merge appends row B a second time -- nothing else
    repo.ledger(ROW_A, ROW_B, ROW_B)
    replay = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 2 * DAY)
    repo.ledger(ROW_A, ROW_B, ROW_B, ROW_C)
    fresh = repo.commit("Recover c", author=T0 + 2 * DAY, committer=T0 + 2 * DAY)
    got = repo.check(repo.upstream, fresh)
    assert got.returncode == 1, got.stderr
    assert "1 of 2 outgoing commit(s)" in got.stderr
    assert (f"{replay[:10]} Recover counted allocator lock wrapper  [replay: same as {repo.original[:10]}; "
            "1/1 ledger line(s) already upstream; every change already upstream]") in got.stderr
    assert "drop it" in got.stderr
    assert fresh[:10] not in got.stderr


def test_shadow_never_refuses(repo):
    repo.ledger(ROW_A, ROW_B, ROW_B)
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip, "--shadow")
    assert got.returncode == 0
    assert "shadow" in got.stderr and tip[:10] in got.stderr


def test_clean_push_is_silent(repo):
    repo.ledger(ROW_A, ROW_B, ROW_C)
    tip = repo.commit("Recover c", author=T0 + DAY, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 0 and got.stderr == "" and got.stdout == ""


def test_identity_alone_is_only_possible(repo):
    # an amended copy of a pushed commit keeps its author date and subject
    repo.write("Code/b.cpp", "void b() {}\n")
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 1
    assert (f"[possible replay: same as {repo.original[:10]}; its changes are not all upstream]") in got.stderr
    assert "drop it" not in got.stderr and "before dropping anything" in got.stderr


def test_other_author_or_date_is_not_identity(repo):
    (repo.root / "x.txt").write_text("x\n")
    repo.commit("Recover counted allocator lock wrapper", author=T0 + 3601, committer=T0 + DAY)
    (repo.root / "y.txt").write_text("y\n")
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY,
                      email="other@example.com")
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 0, got.stderr


def test_one_duplicate_row_beside_a_fresh_one_is_not_a_replay(repo):
    # review round 2: one duplicate row plus one fresh row said "drop it"; the commit
    # carries new work, so the advice is to remove the duplicate row
    repo.ledger(ROW_A, ROW_B, ROW_C, ROW_B)
    tip = repo.commit("Recover c", author=T0 + DAY, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 1
    assert "[duplicate rows: 1/2 ledger line(s) already upstream; its other changes are new]" in got.stderr
    assert "remove the ledger lines already upstream" in got.stderr
    assert "drop it" not in got.stderr and "same as" not in got.stderr


def test_twin_with_a_fresh_file_and_a_duplicate_row_is_not_a_replay(repo):
    repo.ledger(ROW_A, ROW_B, ROW_B)
    repo.write("Code/b.cpp", "void b() {}\n")
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert (f"[duplicate rows: same as {repo.original[:10]}; 1/1 ledger line(s) already upstream; its other "
            "changes are new]") in got.stderr
    assert "drop it" not in got.stderr


def test_whole_commit_already_upstream_is_a_replay(repo):
    # a code file ending exactly as upstream has it, plus a duplicate row: nothing new
    repo.write("Code/b.cpp", "void b() {}\n")
    base = repo.commit("Add b.cpp", author=T0 + DAY, committer=T0 + DAY)
    repo.write("Code/b.cpp", "void b() { /* draft */ }\n")
    repo.commit("Draft b", author=T0 + DAY + 60, committer=T0 + DAY + 60)
    repo.write("Code/b.cpp", "void b() {}\n")
    repo.ledger(ROW_A, ROW_B, ROW_B)
    tip = repo.commit("Recover b again", author=T0 + DAY + 120, committer=T0 + DAY + 120)
    got = repo.check(base, tip)
    assert f"{tip[:10]} Recover b again  [replay: 1/1 ledger line(s) already upstream; every change already " \
           "upstream]" in got.stderr, got.stderr
    assert "drop it" in got.stderr


def test_moved_row_is_not_a_replay(repo):
    # removing row B and adding it back elsewhere adds nothing new
    repo.ledger(ROW_B, ROW_A, ROW_C)
    tip = repo.commit("Sort the ledger and recover c", author=T0 + DAY, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 0, got.stderr


def test_window_bounds_the_upstream_walk(repo):
    # replayed 40 days later: the walk stops at --max-days, so identity is not
    # matched and the commit is counted as unchecked; its duplicate row still shows
    repo.ledger(ROW_A, ROW_B, ROW_B)
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 40 * DAY)
    got = repo.check(repo.upstream, tip, "--max-days", "30")
    assert got.returncode == 1
    assert "same as" not in got.stderr
    assert "1 outgoing commit(s) authored more than 30 days" in got.stderr
    assert "1/1 ledger line(s) already upstream" in got.stderr
    wide = repo.check(repo.upstream, tip, "--max-days", "60")
    assert "same as " + repo.original[:10] in wide.stderr


def test_reland_after_upstream_revert_is_only_possible(repo):
    # upstream reverted the original; the seat re-lands it on purpose: same author, date,
    # subject and patch, no duplicate ledger line -- never "drop it"
    repo.ledger(ROW_A)
    base = repo.commit('Revert "Recover counted allocator lock wrapper"', author=T0 + DAY, committer=T0 + DAY)
    repo.ledger(ROW_A, ROW_B)
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 2 * DAY)
    got = repo.check(base, tip)
    assert got.returncode == 1, got.stderr
    assert (f"[possible replay: same as {repo.original[:10]}, which upstream reverted in {base[:10]}; "
            "its changes are not all upstream]") in got.stderr
    assert "drop it" not in got.stderr and "before dropping anything" in got.stderr


def test_cancelled_replay_is_counted_not_hidden(repo):
    # a changed-metadata replay re-adds row B, a cleanup in the same push drops it: the
    # push's net ledger diff is clean, so the report says what it could not see
    repo.ledger(ROW_A, ROW_B, ROW_B)
    repo.commit("Recover counted allocator lock wrapper again", author=T0 + DAY, committer=T0 + DAY)
    repo.ledger(ROW_A, ROW_B)
    tip = repo.commit("Clean up: drop 1 exact duplicate ledger row", author=T0 + DAY + 60,
                      committer=T0 + DAY + 60)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 0, got.stderr
    assert "no replay found in 2 outgoing commit(s), but not all of it was checked" in got.stderr
    assert "not checked: 2 of 2 ledger-touching commit(s) were checked only through the push's net " \
           "ledger diff" in got.stderr


def test_attribution_is_bounded_and_says_so(repo):
    # three commits each re-add row B; only the first --attribute 1 is diffed one by one
    for i in range(3):
        repo.ledger(*([ROW_A, ROW_B] + [ROW_B] * (i + 1) + [ROW_C] * i))
        tip = repo.commit(f"Recover thing {i}", author=T0 + DAY + i, committer=T0 + DAY + i)
    got = repo.check(repo.upstream, tip, "--attribute", "1")
    assert got.returncode == 1
    assert "1 of 3 outgoing commit(s) may replay" in got.stderr
    assert "not checked: 2 of 3 ledger-touching commit(s)" in got.stderr
    assert "the push also adds 2 ledger line(s) already upstream verbatim in commits not attributed" in got.stderr


def test_a_push_without_ledger_changes_reads_no_ledger(repo, monkeypatch):
    repo.write("Code/c.cpp", "void c() {}\n")
    tip = repo.commit("Recover c", author=T0 + DAY, committer=T0 + DAY)
    calls = []
    run = shadow_budget.Budget.run

    def spy(self, args, input=None):
        calls.append(args)
        return run(self, args, input)

    monkeypatch.setattr(shadow_budget.Budget, "run", spy)
    monkeypatch.chdir(repo.root)
    assert replay_check.main(["--range", repo.upstream, tip]) == 0
    assert not [a for a in calls if "cat-file" in a or "grep" in a]


def test_bad_range_never_fails_in_shadow(repo):
    got = repo.check("0" * 40, repo.upstream, "--shadow")
    assert got.returncode == 0
    assert "replay_check:" in got.stderr


def test_pre_push_calls_it_in_shadow():
    hook = (TOOL.parents[1] / ".githooks" / "pre-push").read_text(encoding="utf-8")
    call = [line for line in hook.splitlines() if "tools/replay_check.py" in line]
    assert call and all("--shadow" in line for line in call)
    after = hook.split("tools/replay_check.py", 1)[1].splitlines()
    assert after[1].strip().startswith("|| echo"), "the call must never fail the push"


# ---------------------------------------------------------------- the budget

def _alive(pid):
    if os.name == "nt":
        import ctypes
        from ctypes import wintypes
        k32 = ctypes.WinDLL("kernel32")
        k32.OpenProcess.restype = wintypes.HANDLE
        k32.OpenProcess.argtypes = (wintypes.DWORD, wintypes.BOOL, wintypes.DWORD)
        handle = k32.OpenProcess(0x1000, False, pid)       # PROCESS_QUERY_LIMITED_INFORMATION
        if not handle:
            return False
        code = wintypes.DWORD()
        k32.GetExitCodeProcess(handle, ctypes.byref(code))
        k32.CloseHandle(handle)
        return code.value == 259                            # STILL_ACTIVE
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except PermissionError:
        return True
    try:
        with open(f"/proc/{pid}/stat") as handle:
            return handle.read().rsplit(")", 1)[1].split()[0] != "Z"
    except OSError:
        return True


def _kill(pid):
    if os.name == "nt":
        subprocess.run(["taskkill", "/F", "/PID", str(pid)], capture_output=True)
    else:
        try:
            os.kill(pid, 9)
        except OSError:
            pass


# a stand-in for git that hangs, with a child of its own that hangs too and holds its output
HANG = """\
import os, subprocess, sys, time
child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])
with open(os.path.join(sys.argv[1], "pids-%d.txt" % os.getpid()), "w") as out:
    out.write("%d %d" % (os.getpid(), child.pid))
time.sleep(60)
"""


def hanging_git(tmp_path):
    script = tmp_path / "hang.py"
    script.write_text(HANG)
    return (sys.executable, str(script), str(tmp_path))


def direct_children_dead(tmp_path):
    """Assert each stand-in git was killed, and return its own children -- which the budget
    must not have touched: it kills its direct child only -- for the caller to clean up."""
    pairs = [tuple(map(int, f.read_text().split())) for f in tmp_path.glob("pids-*.txt")]
    assert pairs, "the stand-in git never started"
    assert not [git for git, _child in pairs if _alive(git)], "a direct child outlived the budget"
    return [child for _git, child in pairs]


def test_budget_kills_only_the_direct_child_and_leaves_no_thread(tmp_path):
    threads = threading.active_count()
    budget = shadow_budget.Budget(1.5)
    t0 = time.monotonic()
    with pytest.raises(shadow_budget.BudgetExceeded):
        budget.run(list(hanging_git(tmp_path)))
    assert time.monotonic() - t0 < 10        # the grandchild holding its output does not block
    grandchildren = direct_children_dead(tmp_path)
    try:
        assert all(_alive(p) for p in grandchildren), "no process-tree kill: direct child only"
    finally:
        for pid in grandchildren:
            _kill(pid)
    assert threading.active_count() == threads
    with pytest.raises(shadow_budget.BudgetExceeded):
        budget.run([sys.executable, "-c", "pass"])           # spent: nothing more starts


def test_budget_expiry_exits_0_and_kills_git_children(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(replay_check, "GIT", hanging_git(tmp_path))
    threads = threading.active_count()
    t0 = time.monotonic()
    code = replay_check.main(["--range", "A" * 40, "B" * 40, "--budget", "2"])   # not --shadow
    elapsed = time.monotonic() - t0
    assert code == 0
    assert elapsed < 15, elapsed
    assert "partial: budget of 2s exceeded after 0 of ? commit(s)" in capsys.readouterr().err
    for pid in direct_children_dead(tmp_path):
        _kill(pid)
    assert threading.active_count() == threads


def test_budget_from_the_environment(repo):
    env = dict(os.environ, BFME_SHADOW_BUDGET_S="0.000001")
    got = repo.check(repo.upstream, repo.upstream, env=env)
    assert got.returncode == 0
    assert "partial: budget of 1e-06s exceeded" in got.stderr


def test_children_are_kept_from_starting_others():
    assert "core.pager=cat" in shadow_budget.GIT and "--no-pager" in shadow_budget.GIT
    env = shadow_budget.child_env()
    assert env["GIT_TERMINAL_PROMPT"] == "0" and env["GIT_PAGER"] == "cat"
    assert not [n for n in dir(shadow_budget) if "job" in n.lower() or "tree" in n.lower()]
