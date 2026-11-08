"""tools/git_trust.py: local git state that rewrites history refuses every history check.

A shallow clone, info/grafts, refs under refs/replace/, GIT_GRAFT_FILE and
GIT_REPLACE_REF_BASE each change what git reports as history without changing a commit
(round 9's probes: grafts flipped the prepared baseline and the pre-push vote check, a
shallow boundary hid a vote rewrite from the root-history check, replace objects hid
staged sources from class_gate's diffs). Each is refused by the shared preflight, by
repair_queue's inline copy of it, at every history-dependent entry point, and by both
hooks."""
import importlib
import os
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

TESTS = Path(__file__).resolve().parent
sys.path[:0] = [str(TESTS.parent), str(TESTS)]
import class_gate  # noqa: E402
import git_trust  # noqa: E402
import rename  # noqa: E402
from test_hook_fail_closed import _bash, repo, run as run_hook  # noqa: E402,F401  (the fixture)

# the last four point git at another repository (a donor): the review's GIT_DIR probe
CONDITIONS = ["shallow", "grafts", "replace", "GIT_GRAFT_FILE", "GIT_REPLACE_REF_BASE",
              "GIT_DIR", "GIT_WORK_TREE", "GIT_COMMON_DIR", "GIT_INDEX_FILE"]
EXPECTED = {"shallow": "shallow", "grafts": "grafts exists", "replace": "refs/replace/ holds 1 ref",
            "GIT_GRAFT_FILE": "GIT_GRAFT_FILE is set", "GIT_REPLACE_REF_BASE": "GIT_REPLACE_REF_BASE is set",
            "GIT_DIR": "GIT_DIR names", "GIT_WORK_TREE": "GIT_WORK_TREE names",
            "GIT_COMMON_DIR": "GIT_COMMON_DIR names", "GIT_INDEX_FILE": "GIT_INDEX_FILE names"}


def git(root, *args, **kwargs):
    return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, check=True,
                          **kwargs).stdout.strip()


def commit(root, rel, text, message):
    (root / rel).parent.mkdir(parents=True, exist_ok=True)
    (root / rel).write_bytes(text.encode())          # byte-stable: write_text gives CRLF on Windows
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@example.invalid", "commit", "-qm", message)
    return git(root, "rev-parse", "HEAD")


def history(tmp_path):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "core.autocrlf", "false")
    first = commit(root, "a.txt", "one\n", "first")
    second = commit(root, "a.txt", "two\n", "second")
    return root, first, second


def untrust(root, condition, monkeypatch, tmp_path):
    """Put `condition` in place for `root` (a two-commit repository); returns the root to judge."""
    first = git(root, "rev-list", "--max-parents=0", "HEAD")
    head = git(root, "rev-parse", "HEAD")
    if condition == "shallow":
        clone = tmp_path / "shallow"
        subprocess.run(["git", "clone", "-q", "--depth", "1", f"file://{root.as_posix()}", str(clone)],
                       check=True, capture_output=True)
        return clone
    if condition == "grafts":
        info = root / git(root, "rev-parse", "--git-common-dir") / "info"
        info.mkdir(parents=True, exist_ok=True)
        (info / "grafts").write_text(f"{head}\n")              # HEAD loses its parent
    elif condition == "replace":
        git(root, "replace", first, head)
    elif condition == "GIT_GRAFT_FILE":
        (tmp_path / "grafts").write_text(f"{head}\n")
        monkeypatch.setenv("GIT_GRAFT_FILE", str(tmp_path / "grafts"))
    elif condition == "GIT_REPLACE_REF_BASE":
        monkeypatch.setenv("GIT_REPLACE_REF_BASE", "refs/elsewhere/")
    else:                                                       # a donor repository named by the environment
        donor = tmp_path / "donor"
        if not donor.exists():
            subprocess.run(["git", "init", "-q", str(donor)], check=True, capture_output=True)
        commit(donor, "d.txt", "donor\n", "donor")
        monkeypatch.setenv(condition, str({"GIT_DIR": donor / ".git", "GIT_WORK_TREE": donor,
                                           "GIT_COMMON_DIR": donor / ".git",
                                           "GIT_INDEX_FILE": donor / ".git" / "index"}[condition]))
    return root


def test_a_clean_repository_is_trusted(tmp_path):
    root, _first, _second = history(tmp_path)
    assert git_trust.untrusted_history(root) == []
    git_trust.preflight(root, "x")
    assert git_trust.main(["--root", str(root)]) == 0


@pytest.mark.parametrize("condition", CONDITIONS)
def test_each_condition_refuses(tmp_path, monkeypatch, condition, capsys):
    root = untrust(history(tmp_path)[0], condition, monkeypatch, tmp_path)
    problems = git_trust.untrusted_history(root)
    assert len(problems) == 1, problems
    assert EXPECTED[condition] in problems[0]
    with pytest.raises(git_trust.UntrustedHistory, match="verify-record: local git state rewrites history"):
        git_trust.preflight(root, "verify-record")
    assert git_trust.main(["--root", str(root), "pre-push"]) == 1
    assert "pre-push: local git state rewrites history" in capsys.readouterr().err


def test_not_a_repository_refuses(tmp_path):
    assert git_trust.untrusted_history(tmp_path) == [f"cannot find {tmp_path}'s own repository"]


@pytest.mark.parametrize("knob,value", [
    ("GIT_DIR", ".git"), ("GIT_DIR", "{root}/.git"), ("GIT_WORK_TREE", "{root}"),
    ("GIT_COMMON_DIR", "{root}/.git"),
    ("GIT_INDEX_FILE", ".git/index"),                                  # what git exports to a plain commit
    ("GIT_INDEX_FILE", "{root}/.git/index.lock"),                      # commit -a
    ("GIT_INDEX_FILE", "{root}/.git/next-index-123.lock"),             # a partial commit
])
def test_a_variable_naming_this_checkout_is_accepted(tmp_path, monkeypatch, rq_at, knob, value):
    root = history(tmp_path)[0]
    monkeypatch.chdir(root)                                            # a hook runs from the top
    monkeypatch.setenv(knob, value.format(root=root))
    assert git_trust.untrusted_history(root) == []
    assert rq_at(root).untrusted_history() == []


def test_trusted_calls_drop_the_callers_repository_selection(tmp_path, monkeypatch):
    root = history(tmp_path)[0]
    monkeypatch.chdir(root)
    for knob in git_trust.REPO_SELECTION:
        monkeypatch.setenv(knob, "/elsewhere")
    monkeypatch.setenv("GIT_INDEX_FILE", ".git/index")
    env = git_trust.trusted_env()
    assert not set(git_trust.REPO_SELECTION) & set(env)
    assert env["GIT_INDEX_FILE"] == os.path.abspath(".git/index") and env["GIT_NO_REPLACE_OBJECTS"] == "1"
    assert rename.trusted_env() == env and class_gate.trusted_env() == env


def test_a_failing_staged_diff_stops_the_gate(tmp_path, monkeypatch):
    """class_gate never reads a failed `git diff --cached` as nothing staged."""
    monkeypatch.setattr(class_gate, "ROOT", tmp_path)                  # no repository: git diff fails
    with pytest.raises(SystemExit, match="(?s)git diff --cached failed .*nothing staged was checked"):
        class_gate.staged_sources()


def test_a_repository_git_cannot_read_stops_the_gate(tmp_path, monkeypatch):
    """The review's extension probe: the repository's own git reads it (the preflight passes),
    but its objects no longer match the format, so `git diff --cached` fails; that never
    reads as nothing staged."""
    root = history(tmp_path)[0]
    (root / "Code").mkdir()
    (root / "Code/View.cpp").write_text("class Widget { int m; };\n")
    git(root, "add", "-A")
    git(root, "config", "core.repositoryformatversion", "1")
    git(root, "config", "extensions.objectFormat", "sha256")
    monkeypatch.setattr(class_gate, "ROOT", root)
    monkeypatch.setattr(class_gate.class_views, "canonical_classes", lambda: {"Widget": "Code/Game/Widget.h"})
    with pytest.raises(SystemExit, match="(?s)git diff --cached failed .*nothing staged was checked"):
        class_gate.main(["--staged"])


@pytest.fixture
def rq_at(monkeypatch):
    def load(root):
        monkeypatch.setenv("REPAIR_ROOT", str(root))
        import repair_queue
        module = importlib.reload(repair_queue)
        monkeypatch.delenv("REPAIR_ROOT")
        return module
    yield load
    import repair_queue
    importlib.reload(repair_queue)


@pytest.mark.parametrize("condition", CONDITIONS + ["clean"])
def test_repair_queue_keeps_the_rule_inline(tmp_path, monkeypatch, rq_at, condition):
    """The hooks run repair_queue from a base copy on stdin, so it carries the rule itself."""
    root = history(tmp_path)[0]
    if condition != "clean":
        root = untrust(root, condition, monkeypatch, tmp_path)
    rq = rq_at(root)
    assert rq.untrusted_history() == git_trust.untrusted_history(root)
    if condition != "clean":
        for argv in (["verify-removed"], ["verify-missing"], ["retired"]):
            with pytest.raises(SystemExit, match="local git state rewrites history"):
                rq.main(argv)
        with pytest.raises(SystemExit, match="header queue: local git state rewrites history"):
            rq.removed_header_rows()


@pytest.mark.parametrize("condition", CONDITIONS)
def test_every_history_entry_point_refuses(tmp_path, monkeypatch, condition, capsys):
    root = untrust(history(tmp_path)[0], condition, monkeypatch, tmp_path)
    with pytest.raises(rename.Refusal, match="verify-record: local git state rewrites history"):
        rename.verify_record(root, "HEAD", "", "Rva00401000Base", "FXNugget")
    ctx = rename.Context(root, object_scan=False)
    with pytest.raises(rename.Refusal, match="--prepared: local git state rewrites history"):
        rename.prepared_baseline(ctx, {"contract": "reverse/class_contracts/Rva00401000Base.json"}, [])
    with pytest.raises(rename.Refusal, match="revert of a registered class: local git state"):
        rename.plan_registered_revert(ctx, "FXNugget", "Rva00401000Base", "revert:x", {}, 25)
    plan = SimpleNamespace(registered={"old": "A", "new": "B", "header": "h.h", "prepared": ["u.cpp"]})
    assert "local git state rewrites history" in rename.prepared_attribution_problems(ctx, plan)[0]
    monkeypatch.setattr(class_gate, "ROOT", root)
    capsys.readouterr()
    assert class_gate.main(["--staged"]) == 1
    assert class_gate.main(["--vote-sources-range", "", "HEAD"]) == 1
    assert capsys.readouterr().err.count("class_gate: local git state rewrites history") == 2
    # round 9's probe called the range check directly: each vote check refuses on its own
    for problems in (class_gate.vote_sources_range_problems("", "HEAD"), class_gate.vote_sources_problems()):
        assert len(problems) == 1 and "local git state rewrites history" in problems[0], problems


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
@pytest.mark.parametrize("condition", CONDITIONS)
def test_both_hooks_refuse_before_any_check(repo, tmp_path, monkeypatch, hook, condition):
    """The hooks' shell copy of the rule agrees with the tool on every condition."""
    (repo / "note.txt").write_text("x\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "a second commit")
    judged = untrust(repo, condition, monkeypatch, tmp_path)
    assert git_trust.untrusted_history(judged)
    if condition == "GIT_WORK_TREE":                 # as git runs the hook: GIT_DIR names the checkout's own
        monkeypatch.setenv("GIT_DIR", str(repo / ".git"))
    head = git(judged, "rev-parse", "HEAD")
    result = run_hook(judged, hook, f"refs/heads/main {head} refs/heads/main {'0' * 40}\n"
                      if hook == "pre-push" else "")
    assert result.returncode == 1, (result.stdout, result.stderr)
    assert "local git state rewrites history" in result.stderr


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
@pytest.mark.parametrize("env", [{"GIT_INDEX_FILE": ".git/index"}, {"GIT_DIR": ".git"}])
def test_the_hooks_accept_what_git_itself_exports(repo, hook, env):
    head = git(repo, "rev-parse", "HEAD")
    result = run_hook(repo, hook, f"refs/heads/main {head} refs/heads/main {head}\n" if hook == "pre-push" else "",
                      env=env)
    assert "local git state rewrites history" not in result.stderr, result.stderr


def hook_guard(name):
    """Everything a hook runs before its first check: the guard, as `git commit` will run it."""
    text = (TESTS.parents[1] / ".githooks" / name).read_text()
    return text.split("\n# shadow_cap" if name == "pre-commit" else "\n# stage NAME")[0]


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
@pytest.mark.parametrize("linked", [False, True])
@pytest.mark.parametrize("mode", ["plain", "all", "partial", "gitdir"])
def test_a_real_commit_passes_the_guard(tmp_path, hook, linked, mode):
    """git's own exported environment, on whatever paths this host spells: a plain commit in a
    Windows checkout was refused when git printed C:/x and realpath /c/x."""
    base, _first, _second = history(tmp_path)
    git(base, "config", "user.name", "t")
    git(base, "config", "user.email", "t@example.invalid")
    root = base
    if linked:
        root = tmp_path / "linked"
        git(base, "worktree", "add", "-q", "-b", "linked", str(root))
    hooks = tmp_path / "hooks"
    hooks.mkdir()
    (hooks / "pre-commit").write_text(hook_guard(hook) + "\n" + 'echo GUARD-PASSED >&2\n')
    (hooks / "pre-commit").chmod(0o755)                # git skips a hook that is not executable
    (root / "a.txt").write_text("three\n")
    (root / "b.txt").write_text("three\n")
    git(root, "add", "b.txt")
    args = ["commit", "-m", mode]
    if mode == "plain":
        git(root, "add", "a.txt")
    elif mode == "all":
        args.append("-a")
    elif mode == "partial":
        args += ["--", "a.txt"]
    else:
        git(root, "add", "a.txt")
        args = [f"--git-dir={git(root, 'rev-parse', '--git-dir')}", *args]
    got = subprocess.run(["git", "-c", f"core.hooksPath={hooks.as_posix()}", *args], cwd=root,
                         capture_output=True, text=True)
    assert got.returncode == 0 and "GUARD-PASSED" in got.stderr, got.stderr


@pytest.mark.skipif(os.name == "nt", reason="the real cygpath and realpath run in the real-commit test there")
def test_the_hooks_compare_one_spelling_of_a_path(tmp_path):
    """Git Bash's tools, stubbed for a host without them: git prints C:/x and realpath /c/x."""
    stubs = tmp_path / "stubs"
    stubs.mkdir()
    (stubs / "cygpath").write_text('#!/bin/sh\nmode=$1; p=$3\n'
                                   'case "$mode" in\n'
                                   '  -u) case "$p" in [Cc]:/*) echo "/c/${p#??/}" ;; *) echo "$p" ;; esac ;;\n'
                                   '  -m) case "$p" in /c/*) echo "C:/${p#/c/}" ;; *) echo "$p" ;; esac ;;\n'
                                   'esac\n')
    (stubs / "realpath").write_text('#!/bin/sh\necho "$3"\n')
    for stub in stubs.iterdir():
        stub.chmod(0o755)
    text = hook_copy("pre-push")
    function = text[:text.index("git_history_trusted() {")]
    spelled = {}
    for path in ("C:/Repo/.git", "/c/Repo/.git", "c:/Repo/.git", "C:/repo/.git"):
        got = subprocess.run([_bash(), "-c", f'{function}\ngit_path_form "{path}"'], capture_output=True, text=True,
                             env=dict(os.environ, PATH=f"{stubs}{os.pathsep}{os.environ['PATH']}"))
        assert got.returncode == 0, got.stderr
        spelled[path] = got.stdout.strip()
    # the drive letter is one spelling; a directory's case is not, because it can be another directory
    assert spelled == {"C:/Repo/.git": "C:/Repo/.git", "/c/Repo/.git": "C:/Repo/.git",
                       "c:/Repo/.git": "C:/Repo/.git", "C:/repo/.git": "C:/repo/.git"}, spelled


def case_sensitive_dir(tmp_path):
    """A directory where `x` and `X` are two names (fsutil on Windows), or skip the test."""
    folder = tmp_path / "cased"
    folder.mkdir()
    if os.name == "nt":
        got = subprocess.run(["fsutil", "file", "setCaseSensitiveInfo", str(folder), "enable"],
                             capture_output=True, text=True)
        if got.returncode:
            pytest.skip(f"fsutil cannot enable case sensitivity here: {got.stdout.strip()[:120]}")
    (folder / "probe").write_bytes(b"x")
    if (folder / "PROBE").exists():
        pytest.skip("this file system folds case")
    (folder / "probe").unlink()
    return folder


def run_guard(hook, cwd, tail="", **env):
    return subprocess.run([_bash(), "-c", hook_guard(hook) + "\n" + tail], cwd=cwd, capture_output=True, text=True,
                          env=dict(os.environ, **env))


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_a_case_twin_index_never_reads_as_this_checkouts(tmp_path, monkeypatch, rq_at, hook):
    """The review's probe: safe contents in .git/index and others staged through .GIT/index. With
    the path folded the guard read `safe` while the real commit recorded the other."""
    root = history(case_sensitive_dir(tmp_path))[0]
    twin = root / ".GIT"
    twin.mkdir()
    (twin / "index").write_bytes((root / ".git/index").read_bytes())
    (root / "a.txt").write_bytes(b"unverified\n")
    env = dict(os.environ, GIT_INDEX_FILE=str(twin / "index"))
    git(root, "add", "a.txt", env=env)
    hooks = tmp_path / "hooks"
    hooks.mkdir()
    (hooks / "pre-commit").write_text(hook_guard(hook) + "\n")
    (hooks / "pre-commit").chmod(0o755)
    got = subprocess.run(["git", "-c", f"core.hooksPath={hooks.as_posix()}", "-c", "user.name=t",
                          "-c", "user.email=t@example.invalid", "commit", "-qm", "probe"],
                         cwd=root, capture_output=True, text=True, env=env)
    assert got.returncode != 0 and "GIT_INDEX_FILE names" in got.stderr, (got.stdout, got.stderr)
    assert git(root, "show", "HEAD:a.txt") == "two"
    monkeypatch.setenv("GIT_INDEX_FILE", str(twin / "index"))
    problems = git_trust.untrusted_history(root)
    assert len(problems) == 1 and "GIT_INDEX_FILE names" in problems[0]
    assert rq_at(root).untrusted_history() == problems


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_a_case_twin_repository_is_another_repository(tmp_path, monkeypatch, rq_at, hook):
    """The review's probe: siblings Repo and repo, run from Repo with GIT_DIR naming repo/.git."""
    folder = case_sensitive_dir(tmp_path)
    here, twin = folder / "Repo", folder / "repo"
    for root in (here, twin):
        root.mkdir()
        git(root, "init", "-q")
    got = run_guard(hook, here, 'echo ACCEPTED', GIT_DIR=str(twin / ".git"))
    assert got.returncode != 0 and "GIT_DIR names" in got.stderr, (got.stdout, got.stderr)
    monkeypatch.setenv("GIT_DIR", str(twin / ".git"))
    problems = git_trust.untrusted_history(here)
    assert len(problems) == 1 and "GIT_DIR names" in problems[0]
    assert rq_at(here).untrusted_history() == problems


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_a_harmless_case_difference_still_passes(tmp_path, monkeypatch, rq_at, hook):
    """In an ordinary Windows directory .GIT is .git: the file system, not folding, says so."""
    root = history(tmp_path)[0]
    if not (root / ".GIT").exists():
        pytest.skip("this file system tells case apart")
    got = run_guard(hook, root, 'echo "INDEX=$GIT_INDEX_FILE"', GIT_DIR=str(root / ".GIT"),
                    GIT_INDEX_FILE=str(root / ".GIT" / "index"))
    assert got.returncode == 0, got.stderr
    monkeypatch.setenv("GIT_DIR", str(root / ".GIT"))
    monkeypatch.setenv("GIT_INDEX_FILE", str(root / ".GIT" / "index"))
    assert git_trust.untrusted_history(root) == []
    assert rq_at(root).untrusted_history() == []


@pytest.mark.skipif(os.name != "nt", reason="only Windows has drive letters")
@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_a_drive_letter_in_either_case_is_one_path(tmp_path, monkeypatch, hook):
    root = history(tmp_path)[0]
    index = str(root / ".git" / "index")
    other = index[0].swapcase() + index[1:]
    got = run_guard(hook, root, 'echo "INDEX=$GIT_INDEX_FILE"', GIT_INDEX_FILE=other)
    assert got.returncode == 0, got.stderr
    monkeypatch.setenv("GIT_INDEX_FILE", other)
    assert git_trust.untrusted_history(root) == []


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_the_exported_index_keeps_its_real_spelling(tmp_path, hook):
    """What every later git reads must be the actual path, never a folded spelling of it."""
    folder = tmp_path / "MixedCase"
    folder.mkdir()
    root = history(folder)[0]
    got = run_guard(hook, root, 'echo "INDEX=$GIT_INDEX_FILE"; git rev-parse --verify -q :a.txt', GIT_INDEX_FILE=".git/index")
    assert got.returncode == 0, got.stderr
    assert "MixedCase" in got.stdout and "/.git/index" in got.stdout, got.stdout
    assert git(root, "rev-parse", ":a.txt") in got.stdout


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_a_first_commit_with_no_index_yet_passes(tmp_path, monkeypatch, hook):
    root = tmp_path / "fresh"
    root.mkdir()
    git(root, "init", "-q")
    assert not (root / ".git/index").exists()
    hooks = tmp_path / "hooks"
    hooks.mkdir()
    (hooks / "pre-commit").write_text(hook_guard(hook) + "\necho GUARD-PASSED >&2\n")
    (hooks / "pre-commit").chmod(0o755)
    got = subprocess.run(["git", "-c", f"core.hooksPath={hooks.as_posix()}", "-c", "user.name=t",
                          "-c", "user.email=t@example.invalid", "commit", "--allow-empty", "-m", "first"],
                         cwd=root, capture_output=True, text=True)
    assert got.returncode == 0 and "GUARD-PASSED" in got.stderr, got.stderr


def test_an_index_that_does_not_exist_is_judged_by_where_it_would_be(tmp_path, monkeypatch):
    root = history(tmp_path)[0]
    monkeypatch.setenv("GIT_INDEX_FILE", str(root / ".git" / "absent-index"))
    assert git_trust.untrusted_history(root) == []
    for outside in (root / "absent-index", root.parent / "absent-index", root / ".git" / ".." / "absent-index"):
        monkeypatch.setenv("GIT_INDEX_FILE", str(outside))
        assert "outside this checkout's git directory" in git_trust.untrusted_history(root)[0]


def test_an_absent_case_twin_of_the_git_directory_is_outside_it(tmp_path, monkeypatch):
    root = history(case_sensitive_dir(tmp_path))[0]
    monkeypatch.setenv("GIT_INDEX_FILE", str(root / ".GIT" / "index"))
    assert "outside this checkout's git directory" in git_trust.untrusted_history(root)[0]


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_both_variables_naming_a_donor_refuse_a_hook_started_here(repo, tmp_path, hook):
    """The review's probe: GIT_DIR and GIT_WORK_TREE together move $ROOT before the guard runs."""
    donor = tmp_path / "other"
    donor.mkdir()
    git(donor, "init", "-q")
    got = subprocess.run([_bash(), "-c", hook_guard(hook) + '\necho "ACCEPTED $ROOT"\n'], cwd=repo,
                         capture_output=True, text=True,
                         env=dict(os.environ, GIT_DIR=str(donor / ".git"), GIT_WORK_TREE=str(donor)))
    assert got.returncode != 0 and "local git state rewrites history" in got.stderr, (got.stdout, got.stderr)


def test_rename_s_private_index_is_one_the_gates_accept(tmp_path, monkeypatch):
    """rename's staged index lives in the git directory: under %TEMP% it was refused as another
    repository's, which blocked rename's own gate checks. The trust rule stays as it is."""
    root = history(tmp_path)[0]
    commit(root, "Code/Plain.cpp", "int plain;\n", "a unit")
    (root / "Code/Plain.cpp").write_text("int plain2;\n")
    index_before = (root / ".git/index").read_bytes()
    monkeypatch.setattr(class_gate, "ROOT", root)
    monkeypatch.setattr(class_gate.class_views, "canonical_classes", lambda: {"Widget": "Code/Game/Widget.h"})
    with rename.staged_index(SimpleNamespace(root=root), ["Code/Plain.cpp"]) as env:
        private = Path(env["GIT_INDEX_FILE"])
        assert private.parent.parent == root / ".git" and private.parent.name.startswith("rename-index-")
        assert env["RENAME_SCRATCH"] == str(private.parent)
        monkeypatch.setenv("GIT_INDEX_FILE", env["GIT_INDEX_FILE"])
        assert git_trust.untrusted_history(root) == []
        assert class_gate.staged_sources() == ["Code/Plain.cpp"]             # the private index, not the real one
        assert class_gate.main(["--staged"]) == 0
        monkeypatch.delenv("GIT_INDEX_FILE")
    assert not private.parent.exists()
    assert (root / ".git/index").read_bytes() == index_before


def test_a_temp_index_stays_refused(tmp_path, monkeypatch):
    root = history(tmp_path)[0]
    monkeypatch.setenv("GIT_INDEX_FILE", str(tmp_path / "elsewhere" / "index"))
    assert "outside this checkout's git directory" in git_trust.untrusted_history(root)[0]


def test_rename_s_other_reads_ignore_the_callers_repository(tmp_path, monkeypatch):
    root = history(tmp_path)[0]
    donor = tmp_path / "donor"
    subprocess.run(["git", "init", "-q", str(donor)], check=True, capture_output=True)
    commit(donor, "a.txt", "donor\n", "donor")
    monkeypatch.setenv("GIT_DIR", str(donor / ".git"))
    assert rename._rev_lines(root, "HEAD", "a.txt") == ["two"]
    assert rename._git_bytes(root, "show", "HEAD:a.txt") == b"two\n"


def hook_copy(name):
    text = (TESTS.parents[1] / ".githooks" / name).read_text()
    start = text.index("git_path_form() {")
    end = text.index("\n}\n", text.index("git_history_trusted() {"))
    return text[start:end]


def test_both_hooks_carry_the_same_preflight():
    assert hook_copy("pre-commit") == hook_copy("pre-push")
    for knob in git_trust.ENV_KNOBS:
        assert knob in hook_copy("pre-push")
    hook = (TESTS.parents[1] / ".githooks/pre-commit").read_text()
    assert "export GIT_NO_REPLACE_OBJECTS=1" in hook
    for name in ("pre-commit", "pre-push"):
        text = (TESTS.parents[1] / ".githooks" / name).read_text()
        assert "\ngit_history_trusted\n" in text
        assert text.index("\ngit_history_trusted\n") < text.index("spawn") if "spawn" in text else True
