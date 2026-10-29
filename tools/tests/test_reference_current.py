"""Reference pins are checked without a shell; Git failures cannot prove them."""
import os
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


GIT_PATH_VARS = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_COMMON_DIR", "GIT_INDEX_FILE",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
    "GIT_GRAFT_FILE", "GIT_SHALLOW_FILE", "GIT_PREFIX",
    "GIT_INTERNAL_SUPER_PREFIX", "GIT_IMPLICIT_WORK_TREE",
    "GIT_CEILING_DIRECTORIES",
)


def git(root, *args, env=None):
    clean = dict(os.environ)
    for name in GIT_PATH_VARS:
        clean.pop(name, None)
    clean.update(env or {})
    return subprocess.run(["git", *args], cwd=root, env=clean, capture_output=True,
                          text=True, check=True).stdout.strip()


def commit(root, message):
    git(root, "-c", "user.name=Reference fixture", "-c", "user.email=fixture@example.invalid",
        "-c", "core.hooksPath=nonexistent-hooks", "commit", "-qm", message)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture(params=["directory", "file"])
def checkout(tmp_path, monkeypatch, request):
    root = tmp_path / "project with spaces"
    root.mkdir()
    reference = root / build.REFERENCE_SUBMODULE
    reference.mkdir(parents=True)
    for path, label in ((root, "parent"), (reference, "reference")):
        extra = (["--separate-git-dir", str(tmp_path / (label + ".git"))]
                 if request.param == "file" else [])
        git(path, "init", "-q", *extra)
    header = reference / "header.h"
    header.write_text("#define VALUE 1\n", encoding="utf-8")
    git(reference, "add", "header.h")
    first = commit(reference, "first reference")
    (root / ".gitmodules").write_text(
        '[submodule "reference/open-bfme-1"]\n'
        '\tpath = reference/open-bfme-1\n\turl = unused-local-fixture\n', encoding="utf-8")
    git(root, "add", ".gitmodules")
    git(root, "update-index", "--add", "--cacheinfo",
        f"160000,{first},{build.REFERENCE_SUBMODULE}")
    commit(root, "pin reference")
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "_REFERENCE_CHECKED", None)
    for name in GIT_PATH_VARS:
        monkeypatch.delenv(name, raising=False)
    return SimpleNamespace(root=root, reference=reference, first=first, header=header)


def advance(checkout):
    checkout.header.write_text("#define VALUE 2\n", encoding="utf-8")
    git(checkout.reference, "add", "header.h")
    return commit(checkout.reference, "second reference")


def test_matching_reference_uses_native_git_and_caches_only_success(checkout, monkeypatch):
    run = build.subprocess.run
    calls = []

    def native(command, **kwargs):
        assert command[1] in ("ls-files", "rev-parse")
        calls.append(command)
        return run(command, **kwargs)

    monkeypatch.setattr(build.subprocess, "run", native)
    build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is not None
    assert len(calls) == 2
    build.ensure_reference_current()
    assert len(calls) == 2
    build._REFERENCE_CHECKED -= build._REFERENCE_RECHECK + 1
    build.ensure_reference_current()
    assert len(calls) == 4


def test_wrong_checkout_is_refused_with_both_commits(checkout):
    second = advance(checkout)
    with pytest.raises(SystemExit) as error:
        build.ensure_reference_current()
    assert checkout.first in str(error.value) and second in str(error.value)
    assert "git submodule update --init" in str(error.value)
    assert build._REFERENCE_CHECKED is None


def test_staged_gitlink_takes_precedence_over_parent_head(checkout):
    second = advance(checkout)
    git(checkout.root, "update-index", "--cacheinfo",
        f"160000,{second},{build.REFERENCE_SUBMODULE}")
    assert checkout.first in git(checkout.root, "ls-tree", "HEAD", build.REFERENCE_SUBMODULE)
    build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is not None


def test_parent_private_index_is_kept_but_hook_paths_do_not_bind_child(checkout, tmp_path, monkeypatch):
    second = advance(checkout)
    private_index = tmp_path / "private staged index"
    env = {"GIT_INDEX_FILE": str(private_index)}
    git(checkout.root, "read-tree", "HEAD", env=env)
    git(checkout.root, "update-index", "--cacheinfo",
        f"160000,{second},{build.REFERENCE_SUBMODULE}", env=env)
    monkeypatch.setenv("GIT_INDEX_FILE", str(private_index))
    monkeypatch.setenv("GIT_DIR", git(checkout.root, "rev-parse", "--absolute-git-dir"))
    monkeypatch.setenv("GIT_COMMON_DIR", git(checkout.root, "rev-parse", "--absolute-git-dir"))
    monkeypatch.setenv("GIT_WORK_TREE", str(checkout.root))
    monkeypatch.setenv("GIT_PREFIX", "reference/")
    build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is not None
    # The actual index still pins the first commit: passing required both
    # preserving the private parent index and reading the real child HEAD.
    assert checkout.first in git(checkout.root, "ls-files", "--stage", build.REFERENCE_SUBMODULE)


def test_unmerged_gitlink_is_refused(checkout):
    second = advance(checkout)
    record = (f"0 {'0' * 40}\t{build.REFERENCE_SUBMODULE}\n"
              f"160000 {checkout.first} 1\t{build.REFERENCE_SUBMODULE}\n"
              f"160000 {checkout.first} 2\t{build.REFERENCE_SUBMODULE}\n"
              f"160000 {second} 3\t{build.REFERENCE_SUBMODULE}\n")
    subprocess.run(["git", "update-index", "--index-info"], cwd=checkout.root,
                   input=record.encode("utf-8"), check=True, capture_output=True)
    with pytest.raises(SystemExit, match="unmerged"):
        build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


@pytest.mark.parametrize("step", ["ls-files", "rev-parse"])
@pytest.mark.parametrize("failure", ["exit66", "exit1", "missing", "timeout"])
def test_git_failure_is_not_a_successful_reference_check(checkout, monkeypatch, step, failure):
    run = build.subprocess.run

    def broken(command, **kwargs):
        if command[1] != step:
            return run(command, **kwargs)
        if failure == "missing":
            raise FileNotFoundError("git unavailable")
        if failure == "timeout":
            raise subprocess.TimeoutExpired(command, 60)
        return SimpleNamespace(returncode=66 if failure == "exit66" else 1, stdout="",
                               stderr="could not create signal pipe" if failure == "exit66"
                               else "fatal: cannot read Git metadata")

    monkeypatch.setattr(build.subprocess, "run", broken)
    with pytest.raises(SystemExit, match="Cannot verify"):
        build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


@pytest.mark.parametrize("step,output", [
    ("ls-files", "not an index record\0"),
    ("ls-files", "160000 " + "a" * 40 + " 0\treference/open-bfme-1"),
    ("ls-files", "160000 not-a-commit 0\treference/open-bfme-1\0"),
    ("ls-files", "100644 " + "a" * 40 + " 0\treference/open-bfme-1\0"),
    ("rev-parse", ""),
    ("rev-parse", "not-a-commit\n"),
])
def test_malformed_git_output_is_refused(checkout, monkeypatch, step, output):
    run = build.subprocess.run

    def malformed(command, **kwargs):
        if command[1] == step:
            return SimpleNamespace(returncode=0, stdout=output, stderr="")
        return run(command, **kwargs)

    monkeypatch.setattr(build.subprocess, "run", malformed)
    with pytest.raises(SystemExit, match="Cannot verify"):
        build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


@pytest.mark.parametrize("populated", [False, True])
def test_uninitialized_reference_distinguishes_empty_directory_from_seat(checkout, monkeypatch, populated):
    lstat = Path.lstat

    def no_child_metadata(path, *args, **kwargs):
        if path == checkout.reference / ".git":
            raise FileNotFoundError(path)
        return lstat(path, *args, **kwargs)

    monkeypatch.setattr(Path, "lstat", no_child_metadata)
    iterdir = Path.iterdir
    monkeypatch.setattr(Path, "iterdir", lambda p: iter([checkout.header] if populated else [])
                        if p == checkout.reference else iterdir(p))
    if populated:
        build.ensure_reference_current()
    else:
        with pytest.raises(SystemExit, match="not checked out"):
            build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


def test_export_inside_another_repository_does_not_use_parent_git(checkout, monkeypatch):
    export = checkout.root / "export"
    export.mkdir()
    monkeypatch.setattr(build, "ROOT", export)
    monkeypatch.setattr(build.subprocess, "run", lambda *a, **k: pytest.fail("export invoked Git"))
    build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


def test_seat_without_gitlink_is_not_cached_as_validated(checkout):
    git(checkout.root, "update-index", "--force-remove", build.REFERENCE_SUBMODULE)
    build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None


def test_broken_child_git_file_is_not_treated_as_export(checkout):
    marker = checkout.reference / ".git"
    # Both forms of existing Git metadata distinguish a corrupted checkout
    # from a populated export; neither may fall through to the parent repo.
    if marker.is_dir():
        (marker / "HEAD").write_text("not-a-reference\n", encoding="utf-8")
    else:
        # Git marks this file hidden on Windows; update it without O_CREAT.
        with marker.open("r+", encoding="utf-8") as stream:
            stream.write("gitdir: nonexistent-repository\n")
            stream.truncate()
    with pytest.raises(SystemExit, match="Cannot verify"):
        build.ensure_reference_current()
    assert build._REFERENCE_CHECKED is None
