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
from test_hook_fail_closed import repo, run as run_hook  # noqa: E402,F401  (the fixture)

CONDITIONS = ["shallow", "grafts", "replace", "GIT_GRAFT_FILE", "GIT_REPLACE_REF_BASE"]


def git(root, *args, **kwargs):
    return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, check=True,
                          **kwargs).stdout.strip()


def commit(root, rel, text, message):
    (root / rel).parent.mkdir(parents=True, exist_ok=True)
    (root / rel).write_text(text)
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
    else:
        monkeypatch.setenv("GIT_REPLACE_REF_BASE", "refs/elsewhere/")
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
    expected = {"shallow": "shallow", "grafts": "grafts exists", "replace": "refs/replace/ holds 1 ref",
                "GIT_GRAFT_FILE": "GIT_GRAFT_FILE is set",
                "GIT_REPLACE_REF_BASE": "GIT_REPLACE_REF_BASE is set"}[condition]
    assert expected in problems[0]
    with pytest.raises(git_trust.UntrustedHistory, match="verify-record: local git state rewrites history"):
        git_trust.preflight(root, "verify-record")
    assert git_trust.main(["--root", str(root), "pre-push"]) == 1
    assert "pre-push: local git state rewrites history" in capsys.readouterr().err


def test_not_a_repository_refuses(tmp_path):
    assert "cannot tell whether the repository is shallow" in git_trust.untrusted_history(tmp_path)[0]


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
    head = git(judged, "rev-parse", "HEAD")
    result = run_hook(judged, hook, f"refs/heads/main {head} refs/heads/main {'0' * 40}\n"
                      if hook == "pre-push" else "")
    assert result.returncode == 1, (result.stdout, result.stderr)
    assert "local git state rewrites history" in result.stderr


def hook_copy(name):
    text = (TESTS.parents[1] / ".githooks" / name).read_text()
    start = text.index("git_history_trusted() {")
    return text[start:text.index("\n}\n", start)]


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
