"""The post-merge hook tells a corrupt ledger from a check that could not run.

2026-11-11: master's retail_identity.py imports capstone, which only the venv
had; the hook ran tools/check_csv.py under the system Python, which failed to
import it, and every pull printed "MERGE LEFT THE LEDGER CORRUPT ... dedup_csv"
over a clean ledger. A throwaway repository holds the hook, run-python3 and a
stand-in check_csv.py; PATH holds only stand-ins, so which Python runs is known."""
import os
import shutil
import stat
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
pytestmark = pytest.mark.skipif(os.name == "nt", reason="stand-in executables on PATH are POSIX shell scripts")

# check_csv.py stand-ins: corrupt, clean, or needing a module only the "venv" has
CORRUPT = "import sys\nprint('check_csv: 2 problem(s)')\nsys.exit(1)\n"
CLEAN = "print('check_csv: OK')\n"
VENV_ONLY = "import venv_only_module\nprint('check_csv: OK')\n"
LAZY_VENV_ONLY = "def main():\n    import venv_only_module\n\nif __name__ == '__main__':\n    main()\n"


def executable(path, text):
    path.write_text(text)
    path.chmod(path.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    return path


@pytest.fixture
def repo(tmp_path):
    root = tmp_path / "repo"
    (root / ".githooks").mkdir(parents=True)
    (root / "tools").mkdir()
    for rel in (".githooks/post-merge", ".githooks/run-python3"):
        shutil.copyfile(ROOT / rel, root / rel)
    subprocess.run(["git", "init", "-q"], cwd=root, check=True)
    real = Path(sys.executable).as_posix()
    bin_ = tmp_path / "bin"
    bin_.mkdir()
    for tool in ("git", "cat", "sh", "tail"):                 # what the hook itself calls
        os.symlink(shutil.which(tool), bin_ / tool)
    modules = tmp_path / "venv-site"
    modules.mkdir()
    (modules / "venv_only_module.py").write_text("")
    venv = executable(tmp_path / "venv-python3", f'#!/bin/sh\nPYTHONPATH="{modules}" exec "{real}" "$@"\n')

    def run(check, python3=True, named=None):
        (root / "tools" / "check_csv.py").write_text(check)
        for name in ("python3",):
            target = bin_ / name
            if target.exists():
                target.unlink()
            if python3:
                executable(target, f'#!/bin/sh\nexec "{real}" "$@"\n')   # the system Python: no venv modules
        subprocess.run(["git", "config", "--unset-all", "bfme.python"], cwd=root)
        if named:
            subprocess.run(["git", "config", "bfme.python", str(named)], cwd=root, check=True)
        env = {"PATH": str(bin_), "HOME": str(tmp_path)}
        return subprocess.run([shutil.which("bash"), ".githooks/post-merge"], cwd=root, env=env,
                              capture_output=True, text=True, timeout=60)
    run.venv = venv
    run.tmp = tmp_path
    return run


def test_a_clean_ledger_passes_quietly(repo):
    done = repo(CLEAN)
    assert done.returncode == 0, done.stderr
    assert "CORRUPT" not in done.stderr and "NOT CHECKED" not in done.stderr


def test_a_corrupt_ledger_still_says_so(repo):
    done = repo(CORRUPT)
    assert done.returncode == 1
    assert "MERGE LEFT THE LEDGER CORRUPT" in done.stderr and "dedup_csv" in done.stderr


@pytest.mark.parametrize("check", [VENV_ONLY, LAZY_VENV_ONLY], ids=["import-time", "inside-main"])
def test_a_missing_module_is_no_corruption(repo, check):
    done = repo(check)
    assert done.returncode == 1
    assert "cannot import venv_only_module" in done.stderr
    assert "THE LEDGER WAS NOT CHECKED" in done.stderr
    assert "CORRUPT" not in done.stderr and "do not run dedup_csv" in done.stderr


def test_bfme_python_runs_first(repo):
    # the system python3 on PATH lacks the module; the named venv has it
    done = repo(VENV_ONLY, named=repo.venv)
    assert done.returncode == 0, done.stderr


def test_a_bfme_python_that_does_not_run_is_no_fallback_and_no_corruption(repo):
    done = repo(CLEAN, named=repo.tmp / "no-such-python")
    assert done.returncode == 1
    assert "bfme.python names" in done.stderr and "THE LEDGER WAS NOT CHECKED" in done.stderr
    assert "CORRUPT" not in done.stderr


def test_no_python_at_all_is_no_corruption(repo):
    done = repo(CLEAN, python3=False)
    assert done.returncode == 1
    assert "neither python3 nor py -3 runs" in done.stderr and "THE LEDGER WAS NOT CHECKED" in done.stderr
    assert "CORRUPT" not in done.stderr
