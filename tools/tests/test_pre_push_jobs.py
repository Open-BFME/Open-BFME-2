"""pre-push runs its independent checks concurrently (spawn/join_jobs): every
check still runs, prints in launch order, and the first failure in that order
fails the push with its own message."""
import os
import re
import shutil
import subprocess
from pathlib import Path

import pytest

HOOK = Path(__file__).resolve().parents[2] / ".githooks" / "pre-push"


def _bash():
    """Git-for-Windows Bash, not the WindowsApps/WSL shim a bare `bash` finds."""
    candidates = []
    if os.name == "nt":
        git = shutil.which("git")
        if git:
            git_root = Path(git).resolve().parent.parent
            candidates += [git_root / "bin/bash.exe", git_root / "usr/bin/bash.exe"]
        program_files = Path(os.environ.get("ProgramFiles", r"C:\Program Files"))
        candidates += [program_files / "Git/bin/bash.exe", program_files / "Git/usr/bin/bash.exe"]
    if shutil.which("bash"):
        candidates.append(Path(shutil.which("bash")))
    for candidate in candidates:
        if Path(candidate).is_file():
            return str(candidate)
    pytest.skip("Bash is required to exercise the hook")


def run(tmp_path, body):
    text = HOOK.read_text(encoding="utf-8")
    helpers = text[text.index("_job_pids=()"):text.index("# fast_forward_or_fail REV:")]
    script = tmp_path / "jobs.sh"
    script.write_text("set -euo pipefail\nfail() { echo \"PRE-PUSH FAILED: $*\" >&2; exit 1; }\n"
                      + helpers + body, newline="\n")
    return subprocess.run([_bash(), "--noprofile", "--norc", script.as_posix()], cwd=tmp_path,
                          capture_output=True, text=True)


def test_every_check_runs_and_prints_in_launch_order(tmp_path):
    done = run(tmp_path, 'spawn "first" sh -c "sleep 1; echo one; echo e1 >&2"\n'
                         'spawn "second" sh -c "echo two; echo e2 >&2"\n'
                         'join_jobs\necho joined\n')
    assert done.returncode == 0, done.stderr
    assert done.stdout.split() == ["one", "two", "joined"]
    assert done.stderr.split() == ["e1", "e2"]


def test_the_first_failure_in_launch_order_fails_the_push(tmp_path):
    done = run(tmp_path, 'spawn "slow refusal" sh -c "sleep 1; echo refused >&2; exit 3"\n'
                         'spawn "fast refusal" sh -c "exit 1"\n'
                         'spawn "passing" sh -c "echo still-ran"\n'
                         'join_jobs\necho not-reached\n')
    assert done.returncode == 1
    assert "still-ran" in done.stdout and "not-reached" not in done.stdout
    assert "refused" in done.stderr
    assert re.search(r"PRE-PUSH FAILED: slow refusal \(see above\)", done.stderr)


def test_a_producer_writes_its_data_and_a_status_producer_records_its_exit(tmp_path):
    done = run(tmp_path, 'spawn_data out.txt "producer" sh -c "echo data"\n'
                         'spawn_status st.txt sh -c "echo partial; exit 2"\n'
                         'join_jobs\ncat out.txt st.txt; echo; cat st.txt.status\n')
    assert done.returncode == 0, done.stderr
    assert done.stdout.split() == ["data", "partial", "2"]


def test_a_failing_producer_fails_the_push(tmp_path):
    done = run(tmp_path, 'spawn_data out.txt "delta_sources" sh -c "echo x; exit 1"\njoin_jobs\n')
    assert done.returncode == 1
    assert "PRE-PUSH FAILED: delta_sources (see above)" in done.stderr
