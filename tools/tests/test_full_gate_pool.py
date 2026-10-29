"""pre-push's full-gate pool scales with the machine: a third of its cores,
between 4 and 8, unless BUILD_POOL says otherwise (.githooks/pre-push
full_gate_pool)."""
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


def pool(tmp_path, cores, build_pool=None):
    function = re.search(r"^full_gate_pool\(\) \{.*?^\}", HOOK.read_text(encoding="utf-8"), re.M | re.S).group(0)
    script = tmp_path / "pool.sh"
    # a function shadows the real nproc wherever it sits on PATH
    script.write_text(f"nproc() {{ echo {cores}; }}\n{function}\nfull_gate_pool\n", newline="\n")
    env = {k: v for k, v in os.environ.items() if k != "BUILD_POOL"}
    if build_pool is not None:
        env["BUILD_POOL"] = build_pool
    done = subprocess.run([_bash(), "--noprofile", "--norc", script.as_posix()], capture_output=True, text=True, env=env, check=True)
    return done.stdout


@pytest.mark.parametrize("cores,expected", [(4, "4"), (12, "4"), (15, "5"), (24, "8"), (64, "8")])
def test_the_full_gate_pool_scales_with_the_machine(tmp_path, cores, expected):
    assert pool(tmp_path, cores) == expected


def test_an_explicit_build_pool_wins(tmp_path):
    assert pool(tmp_path, 24, "2") == "2"
    assert pool(tmp_path, 4, "16") == "16"


def test_scoped_chunks_keep_their_own_default():
    text = HOOK.read_text(encoding="utf-8")
    chunks = text[text.index("build_chunks() {"):text.index("# classify_full_scope")]
    assert 'BUILD_POOL="${BUILD_POOL:-4}"' in chunks and "full_gate_pool" not in chunks
