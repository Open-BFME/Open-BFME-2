"""A lister that fails must stop the hook, not shrink what it verifies.

Both hooks read their lists through `< <(cmd)` or `mapfile < <(cmd)`, which drop the
producer's exit status: a delta_sources.py that crashed, or a `git diff` that could not
read the index, looked exactly like "nothing to verify" and the commit or push went
through. Each case runs the real hook in a throwaway repository with stub checkers;
tools/build.py records what it was asked to verify.
"""

import json
import os
import shutil
import stat
import subprocess
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
SOURCE = "Code/GameEngine/Source/Common/Unit.cpp"
STUBS = ("check_case_collisions", "conversion_gate", "link_debt", "class_gate", "tu_ownership",
         "hatch_counters", "code_identity_gate", "data_check", "ledger_guard", "check_csv",
         "flag_defaults", "pin_consistency", "pin_admission", "header_dependents")
# These read their list on stdin; drain it as the real tools do.
READERS = ("eh_verify", "find_declared_unmatched", "link_check")
RECORD_BUILD = """import json, sys
with open("build-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps(sys.argv[1:]) + "\\n")
"""
# Prints delta.txt like the real tool (LF only), then exits with delta-exit's code.
DELTA = """import os, sys
sys.stdout.reconfigure(newline="\\n")
if os.path.exists("delta.txt"):
    sys.stdout.write(open("delta.txt", encoding="utf-8").read())
sys.stdout.flush()
sys.exit(int(open("delta-exit").read()) if os.path.exists("delta-exit") else 0)
"""
# name_dependents.py, the same way: prints name-deps.txt, exits with name-deps-exit's code.
NAME_DEPS = DELTA.replace("delta", "name-deps")
LEDGER = ("name,export_rva,target_rva,target_size,source,status,notes\n"
          f"?f@Unit@@QAEXXZ,,0x00001000,16,{SOURCE},matched,{{note}}\n")


def _bash() -> str:
    """Git-for-Windows Bash, not the WindowsApps WSL shim (as in test_hook_build_dispatch)."""
    candidates = []
    if os.name == "nt":
        git = shutil.which("git")
        if git:
            git_root = Path(git).resolve().parent.parent
            candidates.extend((git_root / "bin/bash.exe", git_root / "usr/bin/bash.exe"))
        program_files = Path(os.environ.get("ProgramFiles", r"C:\Program Files"))
        candidates.extend(
            (program_files / "Git/bin/bash.exe", program_files / "Git/usr/bin/bash.exe")
        )
    discovered = shutil.which("bash")
    if discovered:
        candidates.append(Path(discovered))
    for candidate in candidates:
        if Path(candidate).is_file():
            return str(candidate)
    pytest.skip("Bash is required to exercise the tracked hooks")


def git(repo, *args):
    return subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True,
                          text=True).stdout.strip()


def write(repo, path, text):
    target = repo / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8"))


@pytest.fixture
def repo(tmp_path):
    if os.name == "nt" and not shutil.which("py"):
        pytest.skip("the hooks build through the py launcher on Windows")
    repo = tmp_path / "repo"
    repo.mkdir()
    git(repo, "init", "-q")
    git(repo, "config", "user.name", "Fixture")
    git(repo, "config", "user.email", "fixture@example.invalid")
    git(repo, "config", "core.autocrlf", "false")
    for tool in STUBS:
        write(repo, f"tools/{tool}.py", "raise SystemExit(0)\n")
    for tool in READERS:
        write(repo, f"tools/{tool}.py", "import sys\nsys.stdin.buffer.read()\n")
    write(repo, "tools/delta_sources.py", DELTA)
    write(repo, "tools/name_dependents.py", NAME_DEPS)
    write(repo, "tools/build.py", RECORD_BUILD)
    write(repo, "build.sh", '#!/usr/bin/env bash\nexec python3 tools/build.py "$@"\n')
    build_sh = repo / "build.sh"
    build_sh.chmod(build_sh.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    write(repo, "reverse/functions.csv", LEDGER.format(note=""))
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() {}\n")
    write(repo, ".gitignore", "*.jsonl\ndelta.txt\ndelta-exit\nname-deps.txt\nname-deps-exit\nbad-index\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    return repo


def run(repo, hook, refs="", env=None):
    return subprocess.run([_bash(), str(ROOT / ".githooks" / hook)], cwd=repo, input=refs,
                          capture_output=True, text=True, encoding="utf-8", errors="replace",
                          env=dict(os.environ, **(env or {})), timeout=600)


def built(repo):
    path = repo / "build-calls.jsonl"
    if not path.exists():
        return set()
    return {s for line in path.read_text(encoding="utf-8").splitlines() for s in json.loads(line)}


def ledger_only_commit(repo):
    """A row edit with no source change: only delta_sources names the TU to verify."""
    write(repo, "reverse/functions.csv", LEDGER.format(note="re-anchored"))
    git(repo, "add", "reverse/functions.csv")


# ---------------------------------------------------------------- pre-commit

def test_pre_commit_verifies_what_delta_sources_names(repo):
    ledger_only_commit(repo)
    write(repo, "delta.txt", SOURCE + "\n")
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert built(repo) == {SOURCE}


def test_pre_commit_refuses_when_delta_sources_crashes(repo):
    # Positive control: before, the crash read as an empty delta and the commit passed
    # with nothing byte-verified.
    ledger_only_commit(repo)
    write(repo, "delta.txt", SOURCE + "\n")
    write(repo, "delta-exit", "3")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert "PRE-COMMIT FAILED: delta_sources (see above)" in result.stderr
    assert not built(repo)


def test_pre_commit_refuses_when_git_cannot_list_the_index(repo):
    # Before, every `git diff --cached` listing came back empty and the hook took
    # its early exit: a commit with sources passed with nothing checked.
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "add", SOURCE)
    write(repo, "bad-index", "not an index\n")
    result = run(repo, "pre-commit", env={"GIT_INDEX_FILE": str(repo / "bad-index")})
    assert result.returncode == 1
    assert "PRE-COMMIT FAILED: listing staged tools (see above)" in result.stderr
    assert not built(repo)


# ---------------------------------------------------------------- pre-push

def push_refs(repo, base):
    return f"refs/heads/main {git(repo, 'rev-parse', 'HEAD')} refs/heads/main {base}\n"


def test_pre_push_verifies_delta_and_edited_sources(repo):
    base = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "commit", "-qam", "edit")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 0, result.stderr
    assert "PRE-PUSH OK (1 outgoing source(s) byte-verified)" in result.stdout
    assert built(repo) == {SOURCE}


def test_pre_push_refuses_when_delta_sources_crashes(repo):
    # Positive control: before, mapfile read the crash as "nothing to verify" and the
    # ledger-only push went out with 0 sources byte-verified.
    base = git(repo, "rev-parse", "HEAD")
    ledger_only_commit(repo)
    git(repo, "commit", "-qm", "row")
    write(repo, "delta-exit", "3")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert "PRE-PUSH FAILED: delta_sources (see above)" in result.stderr
    assert not built(repo)


def test_pre_push_refuses_when_the_edited_source_list_cannot_be_built(repo):
    # The pushed commit's ledger is unreadable, so the edited-source lister dies;
    # before, that read as "no edited sources" and the edit went out unverified.
    base = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "rm", "-q", "--cached", "reverse/functions.csv")
    git(repo, "commit", "-qam", "edit without a ledger")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert "PRE-PUSH FAILED: listing the edited claimed sources (see above)" in result.stderr
    assert not built(repo)


# ---------------------------------------------------------------- name_dependents

def test_pre_commit_refuses_when_name_dependents_crashes(repo):
    # The units calling a renamed name are listed by tools/name_dependents.py; a crash
    # there must not read as "no unit calls it".
    ledger_only_commit(repo)
    write(repo, "name-deps.txt", SOURCE + "\n")
    write(repo, "name-deps-exit", "3")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert ("PRE-COMMIT FAILED: listing the units that call a renamed or removed name "
            "(see above)") in result.stderr
    assert not built(repo)


def test_pre_push_refuses_when_name_dependents_crashes(repo):
    base = git(repo, "rev-parse", "HEAD")
    ledger_only_commit(repo)
    git(repo, "commit", "-qm", "row")
    write(repo, "name-deps.txt", SOURCE + "\n")
    write(repo, "name-deps-exit", "3")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert ("PRE-PUSH FAILED: listing the units that call a renamed or removed name "
            "(see above)") in result.stderr
    assert not built(repo)
