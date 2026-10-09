"""replay_check.py: an outgoing commit that replays one already upstream is reported -- a
replay (its patch-id or ledger lines are already there, "drop it") or, on author, author
date and subject alone, a possible replay with neutral advice; fresh work, a moved row
and a clean push are not. What it does not check is counted, and a hard wall-clock
budget ends it with a partial report and no live children. Report only: --shadow always
exits 0."""
import os
import subprocess
import sys
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

    def commit(self, subject, **who):
        self.git("add", "-A")
        self.git("commit", "-q", "--allow-empty", "-m", subject, **who)
        return self.git("rev-parse", "HEAD")

    def check(self, base, tip, *extra):
        return subprocess.run([sys.executable, str(TOOL), "--range", base, tip, *extra],
                              cwd=self.root, capture_output=True, text=True)


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
    # subject, and the union merge appends row B a second time
    repo.ledger(ROW_A, ROW_B, ROW_B)
    replay = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 2 * DAY)
    repo.ledger(ROW_A, ROW_B, ROW_B, ROW_C)
    fresh = repo.commit("Recover c", author=T0 + 2 * DAY, committer=T0 + 2 * DAY)
    got = repo.check(repo.upstream, fresh)
    assert got.returncode == 1, got.stderr
    assert "1 of 2 outgoing commit(s)" in got.stderr
    assert replay[:10] in got.stderr and "same as " + repo.original[:10] in got.stderr
    assert "1/1 ledger line(s) already upstream" in got.stderr
    assert "[replay: " in got.stderr and "drop it" in got.stderr
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


def test_identity_alone_is_reported(repo):
    # an amended copy of a pushed commit keeps its author date and subject
    (repo.root / "Code").mkdir()
    (repo.root / "Code" / "b.cpp").write_text("void b() {}\n")
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 1 and "same as " + repo.original[:10] in got.stderr
    assert "ledger line" not in got.stderr.split(tip[:10], 1)[1].splitlines()[0]
    # an amended copy is the same author, date and subject with other content: only a
    # possible replay, and the advice is to compare, never to drop
    assert "[possible replay: same as " + repo.original[:10] + ", patch differs]" in got.stderr
    assert "drop it" not in got.stderr and "before dropping anything" in got.stderr


def test_other_author_or_date_is_not_identity(repo):
    (repo.root / "x.txt").write_text("x\n")
    repo.commit("Recover counted allocator lock wrapper", author=T0 + 3601, committer=T0 + DAY)
    (repo.root / "y.txt").write_text("y\n")
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + DAY,
                      email="other@example.com")
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 0, got.stderr


def test_ledger_line_already_upstream_is_reported(repo):
    # different author date and subject, but row B is already on master
    repo.ledger(ROW_A, ROW_B, ROW_C, ROW_B)
    tip = repo.commit("Recover c", author=T0 + DAY, committer=T0 + DAY)
    got = repo.check(repo.upstream, tip)
    assert got.returncode == 1
    assert "1/2 ledger line(s) already upstream" in got.stderr
    assert "same as" not in got.stderr


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


# ---------------------------------------------------------------- review fixes (2026-10-09)

def test_reland_after_upstream_revert_is_only_possible(repo):
    # upstream reverted the original; the seat re-lands it on purpose: same author, date,
    # subject and patch-id, no duplicate ledger line -- never "drop it"
    repo.ledger(ROW_A)
    base = repo.commit('Revert "Recover counted allocator lock wrapper"', author=T0 + DAY, committer=T0 + DAY)
    repo.ledger(ROW_A, ROW_B)
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 2 * DAY)
    got = repo.check(base, tip)
    assert got.returncode == 1, got.stderr
    assert f"[possible replay: same as {repo.original[:10]}, same patch-id, but upstream reverted it in " \
           f"{base[:10]}: a re-land?]" in got.stderr
    assert "replay, content already upstream: 0 commit(s)" in got.stderr
    assert "drop it" not in got.stderr and "before dropping anything" in got.stderr


def test_same_patch_id_is_a_replay(repo):
    # no ledger line duplicated (the row was edited upstream since), but the patch is
    # the identity twin's: content evidence, so "drop it"
    row_b2 = ROW_B.replace("counted lock wrapper", "counted lock wrapper, renamed")
    repo.ledger(ROW_A, row_b2)
    base = repo.commit("Rename b", author=T0 + DAY, committer=T0 + DAY)
    repo.ledger(ROW_A)
    repo.commit("Drop b for a moment", author=T0 + DAY + 60, committer=T0 + DAY + 60)
    repo.ledger(ROW_A, ROW_B)
    tip = repo.commit("Recover counted allocator lock wrapper", author=T0 + 3600, committer=T0 + 2 * DAY)
    got = repo.check(base, tip)
    assert f"[replay: same as {repo.original[:10]}, same patch-id]" in got.stderr, got.stderr
    assert "drop it" in got.stderr


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


# a stand-in for git that hangs, with a child of its own that hangs too
HANG = """\
import os, subprocess, sys, time
child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(120)"])
with open(os.path.join(sys.argv[1], "pids-%d.txt" % os.getpid()), "w") as out:
    out.write("%d %d" % (os.getpid(), child.pid))
time.sleep(120)
"""


def hanging_git(tmp_path):
    script = tmp_path / "hang.py"
    script.write_text(HANG)
    return (sys.executable, str(script), str(tmp_path))


def assert_all_dead(tmp_path):
    pids = [int(p) for f in tmp_path.glob("pids-*.txt") for p in f.read_text().split()]
    assert pids, "the stand-in git never started"
    deadline = time.monotonic() + 15
    while time.monotonic() < deadline and any(_alive(p) for p in pids):
        time.sleep(0.2)
    assert not [p for p in pids if _alive(p)], "git children outlived the budget"


def test_budget_expiry_exits_0_and_kills_git_children(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(replay_check, "GIT", hanging_git(tmp_path))
    t0 = time.monotonic()
    code = replay_check.main(["--range", "A" * 40, "B" * 40, "--budget", "2"])   # not --shadow
    elapsed = time.monotonic() - t0
    assert code == 0
    assert elapsed < 20, elapsed
    err = capsys.readouterr().err
    assert "partial: budget of 2s exceeded after 0 of ? commit(s)" in err
    assert_all_dead(tmp_path)


def test_budget_from_the_environment(repo):
    env = dict(os.environ, BFME_SHADOW_BUDGET_S="0.000001")
    got = subprocess.run([sys.executable, str(TOOL), "--range", repo.upstream, repo.upstream],
                         cwd=repo.root, capture_output=True, text=True, env=env)
    assert got.returncode == 0
    assert "partial: budget of 1e-06s exceeded" in got.stderr


def test_budget_kills_a_process_tree(tmp_path):
    with shadow_budget.Budget(1.5) as budget:
        with pytest.raises(shadow_budget.BudgetExceeded):
            budget.run([*hanging_git(tmp_path)])
        assert budget.elapsed() < 15
    assert_all_dead(tmp_path)
