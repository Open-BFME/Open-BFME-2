"""build.ensure_reference_current judges reference/open-bfme-1 from an index
lookup and one rev-parse (_reference_status_line) instead of `git submodule
status` (~1 s per build.py process on Windows). Every state must get the
verdict the status command gives: each test builds that state in real repos
and compares the two."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402

SUB = build.REFERENCE_SUBMODULE
ENV = dict(os.environ, GIT_ALLOW_PROTOCOL="file", GIT_CONFIG_COUNT="1",
           GIT_CONFIG_KEY_0="protocol.file.allow", GIT_CONFIG_VALUE_0="always")


def git(cwd, *args, check=True):
    return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, env=ENV,
                          check=check).stdout.strip()


def commit(root, path, text):
    (root / path).parent.mkdir(parents=True, exist_ok=True)
    (root / path).write_text(text)
    git(root, "add", path)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", path)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture
def world(tmp_path, monkeypatch):
    """An upstream with commits a and b, and a superproject pinning b at SUB."""
    upstream = tmp_path / "upstream"
    upstream.mkdir()
    git(upstream, "init", "-q")
    a = commit(upstream, "reference.h", "a\n")
    b = commit(upstream, "reference.h", "b\n")
    root = tmp_path / "super"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "submodule", "add", "-q", upstream.as_posix(), SUB)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "pin")
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "_REFERENCE_CHECKED", None)
    return root, upstream, a, b


def status_letter(root):
    """The oracle: what the old ensure_reference_current read from git."""
    done = subprocess.run(["git", "submodule", "status", "--", SUB], cwd=root, capture_output=True,
                          text=True, env=ENV)
    if done.returncode != 0:
        return None
    line = done.stdout.strip()
    return line[:1] if line[:1] in ("+", "-", "U") else ("" if not line else " ")


def fast_letter():
    line = build._reference_status_line()
    if line is None:
        return None
    return line[:1] if line[:1] in ("+", "-", "U") else ("" if not line else " ")


def verdict():
    build._REFERENCE_CHECKED = None
    try:
        build.ensure_reference_current()
    except SystemExit:
        return "refused"
    return "ok"


def same(root, expected_letter, expected_verdict):
    assert status_letter(root) == expected_letter      # the state is what the test means
    assert fast_letter() == expected_letter
    assert verdict() == expected_verdict


def test_at_the_pin(world):
    root, *_ = world
    same(root, " ", "ok")


def test_submodule_absent(tmp_path, monkeypatch):
    root = tmp_path / "plain"
    root.mkdir()
    git(root, "init", "-q")
    commit(root, "README", "x\n")
    monkeypatch.setattr(build, "ROOT", root)
    assert status_letter(root) in ("", None) and fast_letter() in ("", None)
    assert verdict() == "ok"


@pytest.mark.parametrize("populated", [False, True])
def test_uninitialised(world, tmp_path, monkeypatch, populated):
    root, upstream, a, b = world
    clone = tmp_path / "clone"
    git(tmp_path, "clone", "-q", root.as_posix(), clone.as_posix())   # no --recurse-submodules
    if populated:
        (clone / SUB / "reference.h").write_text("copied by hand\n")
    monkeypatch.setattr(build, "ROOT", clone)
    same(clone, "-", "ok" if populated else "refused")


def test_gitlink_commit_missing_locally(world):
    root, *_ = world
    git(root, "update-index", "--cacheinfo", f"160000,{'1' * 40},{SUB}")
    same(root, "+", "refused")


def test_head_at_another_commit(world):
    root, upstream, a, b = world
    git(root / SUB, "checkout", "-q", a)
    same(root, "+", "refused")


def test_dirty_worktree(world):
    root, *_ = world
    (root / SUB / "reference.h").write_text("edited\n")
    same(root, " ", "ok")


def test_detached_at_the_pin(world):
    root, upstream, a, b = world
    git(root / SUB, "checkout", "-q", "--detach", b)
    same(root, " ", "ok")


def test_borrowed_gitdir(world, tmp_path):
    # tools/worktree_setup.py prepare's layout: the submodule's .git is a
    # relative gitfile naming its own gitdir elsewhere, whose objects are
    # borrowed from another store through objects/info/alternates
    root, upstream, a, b = world
    if not (root / SUB / ".git").is_file():
        git(root, "submodule", "absorbgitdirs")
    text = (root / SUB / ".git").read_text()
    assert text.startswith("gitdir:") and not Path(text.split(":", 1)[1].strip()).is_absolute()
    gitdir = Path(git(root / SUB, "rev-parse", "--absolute-git-dir"))
    assert not gitdir.is_relative_to(root / SUB)
    (gitdir / "objects" / "info").mkdir(parents=True, exist_ok=True)
    (gitdir / "objects" / "info" / "alternates").write_text((upstream / ".git" / "objects").as_posix() + "\n")
    same(root, " ", "ok")
    git(root / SUB, "checkout", "-q", a)
    same(root, "+", "refused")


def test_inactive_but_populated(world):
    root, *_ = world
    git(root, "config", f"submodule.{SUB}.active", "false")
    same(root, "-", "ok")


def test_unmerged_gitlink(world):
    root, upstream, a, b = world
    info = "".join(f"160000 {sha} {stage}\t{SUB}\n" for stage, sha in ((1, a), (2, b), (3, a)))
    git(root, "update-index", "--force-remove", SUB)
    subprocess.run(["git", "update-index", "--index-info"], cwd=root, input=info.encode(), check=True)
    same(root, "U", "refused")
