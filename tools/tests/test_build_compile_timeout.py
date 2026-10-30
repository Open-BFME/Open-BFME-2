"""build's trial-compile wall-clock limit: a hung compiler is killed, not waited on.

cl.exe under Wine spun 50-115 min at 100% CPU on some composed candidates
(build/fleet/bulk/cl_hang_evidence.txt), so try_compile_source takes a
per-compile timeout. Nothing here runs cl.exe: the "compiler" is a python
process that sleeps.
"""
import os
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]

# A stand-in for a compiler that never finishes.
HANGING_CL = "import time\ntime.sleep(120)\n"
# A stand-in for one that hangs *and* leaves a child behind, as a Wine compile
# leaves its loader and c2 behind. The pid file comes from the environment: the
# command line belongs to the compiler flags.
HANGING_CL_WITH_CHILD = """\
import os, subprocess, sys, time
child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(120)"])
open(os.environ["BFME_TEST_PIDFILE"], "w").write(str(child.pid))
time.sleep(120)
"""
QUICK_CL = "print('unit.cpp')\n"


def fake_compiler(monkeypatch, build, script):
    """Point build's compiler at `script` and cut its cache and receipts out."""
    monkeypatch.setattr(build, "compiler_command",
                        lambda source, output: ([sys.executable, str(script)], dict(os.environ)))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda command, env: "fingerprint")
    monkeypatch.setattr(build, "_restore_object", lambda source, output, fingerprint: False)
    monkeypatch.setattr(build, "_write_deps_sidecar", lambda *a, **k: None)
    monkeypatch.setattr(build, "_store_object", lambda *a, **k: None)


def test_a_hanging_compile_is_killed_at_the_limit(tmp_path, monkeypatch):
    sys.path.insert(0, str(TOOLS))
    import build
    script = tmp_path / "cl.py"
    script.write_text(HANGING_CL)
    fake_compiler(monkeypatch, build, script)
    started = time.monotonic()
    ok, text, code = build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj", timeout=1)
    elapsed = time.monotonic() - started
    assert (ok, code) == (False, build.TIMEOUT_STATUS)
    assert "compile timed out after 1 s" in text
    assert elapsed < 30, f"the limit took {elapsed:.1f} s to bite"


def test_no_limit_means_the_compile_runs_as_before(tmp_path, monkeypatch):
    sys.path.insert(0, str(TOOLS))
    import build
    script = tmp_path / "cl.py"
    script.write_text(QUICK_CL)
    fake_compiler(monkeypatch, build, script)
    assert build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj") == (True, "unit.cpp", 0)
    assert build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj",
                                    timeout=30) == (True, "unit.cpp", 0)


def _alive(pid):
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    return True


@pytest.mark.skipif(os.name != "posix", reason="process groups are POSIX")
def test_the_killed_compiles_own_children_die_with_it(tmp_path, monkeypatch):
    # A killed loader that leaves c2 or its Wine services running would keep
    # spinning: the compile runs in its own session, so the whole group dies.
    sys.path.insert(0, str(TOOLS))
    import build
    script = tmp_path / "cl.py"
    script.write_text(HANGING_CL_WITH_CHILD)
    pids = tmp_path / "child.pid"
    monkeypatch.setenv("BFME_TEST_PIDFILE", str(pids))
    fake_compiler(monkeypatch, build, script)
    ok, text, code = build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj",
                                              timeout=5)
    assert (ok, code) == (False, build.TIMEOUT_STATUS)
    child = int(pids.read_text())
    for _ in range(100):                    # the kill is asynchronous: give it a moment
        if not _alive(child):
            break
        time.sleep(0.1)
    assert not _alive(child), "the compiler's child outlived the timeout"
