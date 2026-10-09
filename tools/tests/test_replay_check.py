"""replay_check.py: an outgoing commit that replays one already upstream -- same author,
author date and subject, or ledger lines already there verbatim -- is reported; fresh
work, a moved row and a clean push are not. Report only: --shadow always exits 0."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOL = Path(__file__).resolve().parents[1] / "replay_check.py"
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
