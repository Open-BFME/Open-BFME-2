"""obstacle_ids.py: a change that makes a second obstacle-register entry head a LINK ID is
refused with both files and the next free ID; new IDs, edits and the pairs that already
existed pass. pre-commit runs it on the index, pre-push on the outgoing range."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
TOOL = TOOLS / "obstacle_ids.py"
HOOKS = TOOLS.parent / ".githooks"


class Repo:
    def __init__(self, root):
        self.root = root
        (root / "docs/linking_obstacles").mkdir(parents=True)
        self.git("init", "-q")
        self.git("checkout", "-q", "-b", "master")

    def git(self, *args):
        env = dict(os.environ, GIT_AUTHOR_NAME="seat", GIT_COMMITTER_NAME="seat",
                   GIT_AUTHOR_EMAIL="seat@example.com", GIT_COMMITTER_EMAIL="seat@example.com")
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        assert got.returncode == 0, got.stderr
        return got.stdout.strip()

    def write(self, **entries):
        for name, text in entries.items():
            (self.root / f"docs/linking_obstacles/{name}.md").write_text(text, newline="\n")
        self.git("add", "-A")

    def commit(self, **entries):
        self.write(**entries)
        self.git("commit", "-q", "-m", "entries")
        return self.git("rev-parse", "HEAD")

    def check(self, *args):
        return subprocess.run([sys.executable, str(TOOL), *args], cwd=self.root, capture_output=True, text=True)


@pytest.fixture
def repo(tmp_path):
    r = Repo(tmp_path / "seat")
    (r.root / "docs/linking_obstacles.md").write_text("# Linking obstacle register\n", newline="\n")
    r.base = r.commit(**{"link-001-a": "### LINK-001: a\n", "link-002-b": "### LINK-002: b\nSee LINK-007.\n"})
    return r


def test_a_new_id_and_an_edit_pass(repo):
    tip = repo.commit(**{"link-003-c": "### LINK-003: c\n", "link-001-a": "### LINK-001: a\nStatus: Open\n"})
    got = repo.check("--range", repo.base, tip)
    assert (got.returncode, got.stdout, got.stderr) == (0, "", "")


def test_a_second_entry_on_one_id_is_refused_with_the_next_free_id(repo):
    tip = repo.commit(**{"link-002-other-cause": "### LINK-002: another cause\n"})
    got = repo.check("--range", repo.base, tip)
    assert got.returncode == 1
    assert "LINK-002 heads 2 entries" in got.stderr
    assert "docs/linking_obstacles/link-002-b.md" in got.stderr
    assert "docs/linking_obstacles/link-002-other-cause.md" in got.stderr
    assert "next free ID, LINK-008" in got.stderr                    # LINK-007 is already cited


def test_the_staged_check_reads_the_index(repo):
    repo.write(**{"link-001-again": "## LINK-001: again\n"})
    got = repo.check("--staged")
    assert got.returncode == 1 and "LINK-001 heads 2 entries" in got.stderr
    repo.git("reset", "-q")
    (repo.root / "docs/linking_obstacles/link-001-again.md").unlink()
    assert repo.check("--staged").returncode == 0


def test_an_old_pair_passes_but_a_third_entry_does_not(repo):
    pair = repo.commit(**{"link-001-twin": "### LINK-001: twin\n"})
    tip = repo.commit(**{"link-001-twin": "### LINK-001: twin\nStatus: Blocked\n"})
    assert repo.check("--range", pair, tip).returncode == 0
    third = repo.commit(**{"link-001-third": "### LINK-001: third\n"})
    assert repo.check("--range", pair, third).returncode == 1


def test_only_the_first_line_names_the_entry(repo):
    tip = repo.commit(**{"notes": "### Consolidation note\n\n#### LINK-001 follow-up\n"})
    assert repo.check("--range", repo.base, tip).returncode == 0


def test_a_base_before_the_register_split_passes(repo):
    root = repo.git("commit-tree", "-m", "before", "4b825dc642cb6eb9a060e54bf8d69288fbee4904")   # empty tree
    assert repo.check("--range", root, repo.base).returncode == 0


def test_old_pairs_on_master_are_not_new_to_a_branch_from_before_the_split(repo):
    # codex review 03.11.: a branch whose remote tip predates the split takes master's old pairs over.
    before = repo.git("commit-tree", "-m", "before", "4b825dc642cb6eb9a060e54bf8d69288fbee4904")   # empty tree
    pair = repo.commit(**{"link-001-twin": "### LINK-001: twin\n"})
    repo.git("update-ref", "refs/remotes/origin/master", pair)
    assert repo.check("--range", before, pair).returncode == 0
    third = repo.commit(**{"link-001-third": "### LINK-001: third\n"})
    assert repo.check("--range", before, third).returncode == 1


def test_the_base_counts_first_and_master_only_stands_in_for_a_base_from_before_the_split(repo):
    # codex re-check 03.11.: a stale origin/master still holding a pair the base repaired let a new duplicate pass.
    pair = repo.commit(**{"link-001-twin": "### LINK-001: twin\n"})
    repo.git("update-ref", "refs/remotes/origin/master", pair)
    repaired = repo.commit(**{"link-001-twin": "### LINK-009: twin, renumbered\n"})
    again = repo.commit(**{"link-001-again": "### LINK-001: again\n"})
    assert repo.check("--range", repaired, again).returncode == 1


def test_without_entries_at_the_base_or_on_master_there_is_nothing_to_judge(repo):
    before = repo.git("commit-tree", "-m", "before", "4b825dc642cb6eb9a060e54bf8d69288fbee4904")   # empty tree
    pair = repo.commit(**{"link-001-twin": "### LINK-001: twin\n"})
    assert repo.check("--range", before, pair).returncode == 0                     # no origin/master here


def test_both_hooks_run_it():
    assert "python3 tools/obstacle_ids.py --staged" in (HOOKS / "pre-commit").read_text()
    assert 'tools/obstacle_ids.py --range "$base" "$local_sha"' in (HOOKS / "pre-push").read_text()
