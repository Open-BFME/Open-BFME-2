"""empty_commits.py: an outgoing commit with one parent and that parent's tree is refused,
with the command that removes it; real work, a revert pair, merges and root commits are
not. The pre-push hook runs it on the outgoing range before anything is built."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
TOOL = TOOLS / "empty_commits.py"
HOOK = TOOLS.parent / ".githooks" / "pre-push"
sys.path.insert(0, str(TOOLS))
import empty_commits  # noqa: E402


class Repo:
    def __init__(self, root):
        self.root = root
        root.mkdir(parents=True, exist_ok=True)
        self.git("init", "-q")
        self.git("checkout", "-q", "-b", "master")

    def git(self, *args, ok=(0,)):
        env = dict(os.environ, GIT_AUTHOR_NAME="seat", GIT_COMMITTER_NAME="seat",
                   GIT_AUTHOR_EMAIL="seat@example.com", GIT_COMMITTER_EMAIL="seat@example.com")
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        if got.returncode not in ok:
            raise AssertionError(got.stderr)
        return got.stdout.strip()

    def commit(self, subject, **files):
        for rel, text in files.items():
            (self.root / rel).write_text(text, newline="\n")
        self.git("add", "-A")
        self.git("commit", "-q", "--allow-empty", "-m", subject)
        return self.git("rev-parse", "HEAD")

    def check(self, base, tip):
        return subprocess.run([sys.executable, str(TOOL), "--range", base, tip],
                              cwd=self.root, capture_output=True, text=True)


@pytest.fixture
def repo(tmp_path):
    r = Repo(tmp_path / "seat")
    r.base = r.commit("base", a="1\n")
    return r


def test_real_work_passes_and_prints_nothing(repo):
    tip = repo.commit("work", a="2\n")
    got = repo.check(repo.base, tip)
    assert (got.returncode, got.stdout, got.stderr) == (0, "", "")
    assert repo.check(tip, tip).returncode == 0                      # nothing outgoing


def test_an_empty_commit_is_refused_wherever_it_sits_in_the_range(repo):
    first = repo.commit("Link MetaEvent (819B)")                      # its parent is the remote tip
    repo.commit("work", a="2\n")
    second = repo.commit("Link MetaEvent (819B) again")               # its parent is in the range
    tip = repo.commit("more work", b="1\n")
    got = repo.check(repo.base, tip)
    assert got.returncode == 1 and got.stdout == ""
    lines = got.stderr.splitlines()
    assert lines[0] == "empty_commits: 2 outgoing commit(s) change no file:"
    assert lines[1:3] == [f"  {second[:10]} Link MetaEvent (819B) again", f"  {first[:10]} Link MetaEvent (819B)"]
    assert f"  {empty_commits.REMEDY}" in lines
    assert [sha for sha, _ in empty_commits_in(repo, repo.base, tip)] == [second, first]


def empty_commits_in(repo, base, tip):
    here = os.getcwd()
    os.chdir(repo.root)
    try:
        return empty_commits.empty_commits(empty_commits.outgoing(base, tip))
    finally:
        os.chdir(here)


def test_the_printed_command_removes_them_and_keeps_the_work(repo):
    """The command is what a seat will run: it must work when the branch already sits on
    origin/master, where a plain rebase says 'up to date' and keeps the empty commits."""
    repo.git("update-ref", "refs/remotes/origin/master", repo.base)
    repo.commit("empty one")
    repo.commit("work", a="2\n")
    repo.commit("empty two")
    assert repo.check(repo.base, "HEAD").returncode == 1
    repo.git(*empty_commits.REMEDY.split()[1:])
    assert repo.git("log", "--format=%s", f"{repo.base}..HEAD") == "work"
    assert (repo.root / "a").read_text() == "2\n"
    assert repo.check(repo.base, "HEAD").returncode == 0


def test_a_change_and_its_revert_are_two_commits_that_each_change_something(repo):
    repo.commit("change", a="2\n")
    tip = repo.commit("put it back", a="1\n")
    assert repo.check(repo.base, tip).returncode == 0


def test_merges_and_root_commits_are_not_judged(repo):
    repo.git("checkout", "-q", "-b", "side")
    repo.commit("side work", b="1\n")
    repo.git("checkout", "-q", "master")
    repo.commit("main work", a="2\n")
    repo.git("merge", "-q", "--no-ff", "-m", "merge side", "side")
    merged = repo.git("rev-parse", "HEAD")
    # a merge that keeps its first parent's tree is a merge: still not judged
    repo.git("checkout", "-q", "-b", "other-side", repo.base)
    repo.commit("discarded work", c="1\n")
    repo.git("checkout", "-q", "master")
    repo.git("merge", "-q", "-s", "ours", "-m", "merge that takes nothing", "other-side")
    assert repo.git("rev-parse", "HEAD^{tree}") == repo.git("rev-parse", "HEAD^1^{tree}")
    assert repo.check(repo.base, "HEAD").returncode == 0
    assert repo.check(repo.base, merged).returncode == 0
    other = Repo(repo.root.parent / "other")
    root = other.commit("an empty root commit")
    tip = other.commit("work", a="1\n")
    empty_tree = other.git("hash-object", "-t", "tree", "/dev/null")
    assert other.git("rev-parse", f"{root}^{{tree}}") == empty_tree
    assert other.check(f"{tip}~1", tip).returncode == 0
    assert empty_commits_in(other, tip, tip) == []


def test_a_range_with_merges_is_given_the_command_that_keeps_them(repo):
    """Final review 2: a plain rebase flattens local merges."""
    repo.git("update-ref", "refs/remotes/origin/master", repo.base)
    repo.git("checkout", "-q", "-b", "side")
    repo.commit("side work", b="1\n")
    repo.git("checkout", "-q", "master")
    repo.commit("main work", a="2\n")
    repo.git("merge", "-q", "--no-ff", "-m", "merge side", "side")
    repo.commit("empty")
    got = repo.check(repo.base, "HEAD")
    lines = got.stderr.splitlines()
    assert got.returncode == 1 and lines[0] == "empty_commits: 1 outgoing commit(s) change no file:"
    assert f"  {empty_commits.REMEDY_MERGES}" in lines and f"  {empty_commits.REMEDY}" not in lines
    repo.git(*empty_commits.REMEDY_MERGES.split()[1:])
    assert sorted(repo.git("log", "--format=%s", f"{repo.base}..HEAD").splitlines()) == [
        "main work", "merge side", "side work"]
    assert len(repo.git("rev-list", "--merges", f"{repo.base}..HEAD").splitlines()) == 1
    assert repo.check(repo.base, "HEAD").returncode == 0


def test_empty_commits_origin_master_already_has_are_not_this_pushs(repo):
    """Final review 3: a branch brought up to master carries master's old empty commits,
    which the printed command cannot remove."""
    repo.commit("an old empty commit, published long ago")
    published = repo.commit("published work", a="2\n")
    repo.git("update-ref", "refs/remotes/origin/master", published)
    assert repo.check(repo.base, published).returncode == 0          # an old branch fast-forwarded to master
    tip = repo.commit("a new empty commit")
    got = repo.check(repo.base, tip)
    assert got.returncode == 1 and got.stderr.splitlines()[0] == "empty_commits: 1 outgoing commit(s) change no file:"
    assert "a new empty commit" in got.stderr and "published long ago" not in got.stderr


def test_odd_subjects_and_a_signature_setting_do_not_break_the_reading(repo):
    """Final review 1: U+2028 in a subject split the record, and log.showSignature adds lines."""
    repo.git("config", "log.showSignature", "true")
    repo.commit("work with a line separator   in the subject", a="2\n")
    repo.commit("empty with   and café")
    tip = repo.commit("more \x85 work", b="1\n")
    env = dict(os.environ, PYTHONIOENCODING="ascii")                  # a console that cannot print them
    got = subprocess.run([sys.executable, str(TOOL), "--range", repo.base, tip], cwd=repo.root, capture_output=True,
                         env=env)
    err = got.stderr.decode("ascii")
    assert got.returncode == 1, err
    assert err.splitlines()[0] == "empty_commits: 1 outgoing commit(s) change no file:"
    assert "empty with \\u2028 and caf\\xe9" in err


def test_a_range_git_cannot_read_fails_closed(repo):
    got = repo.check("0123456789012345678901234567890123456789", "HEAD")
    assert got.returncode == 2 and got.stderr.startswith("empty_commits: git log")


def test_the_push_hook_runs_it_on_the_outgoing_range_before_any_gate_that_builds():
    hook = HOOK.read_text(encoding="utf-8")
    # one of the concurrent static checks: join_jobs fails the push on its failure
    call = ('spawn "empty commit(s) in the outgoing range" python3 tools/empty_commits.py '
            '--range "$base" "$local_sha"')
    assert hook.count(call) == 1
    assert hook.index(call) < hook.index("python3 tools/conversion_gate.py")
    assert hook.index(call) < hook.index("    join_jobs\n", hook.index(call))
    assert hook.index('if [ -z "$base" ]; then') < hook.index(call)
