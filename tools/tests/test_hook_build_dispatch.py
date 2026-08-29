"""Regression coverage for the platform dispatcher in the tracked Git hooks.

Git-for-Windows hooks run under a Bash whose ``uname -s`` identifies the
compatibility layer, but the BFME2 build itself must be launched through the
native Windows Python command.  Other Bash hosts retain the repository's
``build.sh`` entry point.  Exercise the function copied from each real hook so
the test fails if either hook drifts.
"""

import os
import re
import shutil
import stat
import subprocess
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
HOOKS = (ROOT / ".githooks/pre-commit", ROOT / ".githooks/pre-push")


def _bash() -> str:
    """Prefer Git-for-Windows Bash over the unrelated WindowsApps shim."""
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
    pytest.skip("Bash is required to exercise the tracked hook dispatcher")


def _run_build_definition(hook: Path) -> str:
    text = hook.read_text(encoding="utf-8")
    match = re.search(r"(?ms)^run_build\(\) \{\n.*?^\}\n", text)
    assert match, f"{hook.relative_to(ROOT)} has no run_build function"
    return match.group(0)


def _write_executable(path: Path, body: str) -> None:
    # Keep the shebang LF-terminated even when this test runs on Windows.
    path.write_bytes(body.encode("utf-8"))
    path.chmod(path.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)


@pytest.mark.parametrize("hook", HOOKS, ids=lambda path: path.name)
@pytest.mark.parametrize(
    "uname_value",
    (
        "MINGW64_NT-10.0-22631",
        "MSYS_NT-10.0-22631",
        "CYGWIN_NT-10.0-22631",
    ),
)
def test_run_build_dispatches_and_forwards_context(
    tmp_path, hook, uname_value
):
    fake_bin = tmp_path / "bin"
    fake_bin.mkdir()
    recorder = """#!/usr/bin/env bash
RECORDED_COMMAND="$1"
shift
{
    printf 'command=%s\\n' "$RECORDED_COMMAND"
    printf 'build_pool=%s\\n' "${BUILD_POOL-unset}"
    printf 'caller_env=%s\\n' "${CALLER_ENV-unset}"
    printf 'arg=<%s>\\n' "$@"
} > "$TRACE_FILE"
    """
    _write_executable(fake_bin / "record-command", recorder)

    harness = f"""set -euo pipefail
{_run_build_definition(hook)}
uname() {{ printf '%s\\n' '{uname_value}'; }}
py() {{ "$PWD/bin/record-command" py "$@"; }}
export PATH="$PWD/bin:$PATH"
export TRACE_FILE="$PWD/trace.txt"
export CALLER_ENV=preserved
BUILD_POOL=37 run_build first "two words"
"""
    completed = subprocess.run(
        [_bash(), "--noprofile", "--norc"],
        cwd=tmp_path,
        input=harness,
        text=True,
        capture_output=True,
        check=False,
    )
    assert completed.returncode == 0, completed.stderr

    trace = (tmp_path / "trace.txt").read_text(encoding="utf-8").splitlines()
    assert trace == [
        "command=py",
        "build_pool=37",
        "caller_env=preserved",
        "arg=<-3>",
        "arg=<tools/build.py>",
        "arg=<first>",
        "arg=<two words>",
    ]


@pytest.mark.parametrize("hook", HOOKS, ids=lambda path: path.name)
def test_non_windows_fallback_is_retained_without_executing_a_shell_file(hook):
    definition = _run_build_definition(hook)
    assert '*) ./build.sh "$@" ;;' in definition


def test_pre_commit_routes_all_union_ledgers_through_the_staged_gate():
    text = (ROOT / ".githooks/pre-commit").read_text(encoding="utf-8")
    trigger = (
        "reverse/functions.csv|reverse/symbols.csv|reverse/deleted_rows.csv|"
        "reverse/re_attempts.log) ledger_changed=1 ;;"
    )
    assert trigger in text
    dirty_loop = text.split("for ledger in ", 1)[1].split("; do", 1)[0]
    assert "reverse/deleted_rows.csv" in dirty_loop
    assert "reverse/re_attempts.log" in dirty_loop
