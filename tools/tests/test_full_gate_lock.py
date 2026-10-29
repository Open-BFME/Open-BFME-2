"""full_gate_lock: one full gate per machine. Two processes contend and only one holds
the lock; a dead holder's lock is taken over; a holder's child acquires as nested."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import full_gate_lock as L  # noqa: E402

# Acquire once (no wait), say what happened, then hold until stdin closes.
CHILD = ("import sys; sys.path.insert(0, sys.argv[1]); import full_gate_lock as L; "
         "got = L.acquire(0, path=sys.argv[2], note='child'); "
         "print('nested' if got and got.handle is None else 'held' if got else 'busy', flush=True); "
         "sys.stdin.read(); L.release(got)")


def child(path, env=None):
    proc = subprocess.Popen([sys.executable, "-c", CHILD, str(TOOLS), str(path)], stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE, text=True, env={**os.environ, **(env or {})})
    return proc, proc.stdout.readline().strip()


def finish(proc):
    proc.stdin.close()
    proc.wait(timeout=30)


@pytest.fixture
def path(tmp_path, monkeypatch):
    monkeypatch.delenv(L.TOKEN_ENV, raising=False)
    return tmp_path / "home" / "full-gate.lock"


def test_two_processes_contend_and_only_one_holds_it(path):
    first, said = child(path)
    assert said == "held"
    try:
        second, said = child(path)
        assert said == "busy"
        finish(second)
        assert L.acquire(0, path=path) is None
        with pytest.raises(L.Busy, match=f"pid {first.pid}"):
            with L.hold(0.2, path=path, poll=0.05):
                pass
    finally:
        finish(first)
    with L.hold(10, path=path) as got:
        assert L.holder(path)["pid"] == os.getpid() and got.handle is not None
    assert L.holder(path) == {}                    # released: no record left


def test_a_dead_holders_lock_is_reclaimed(path):
    dead, said = child(path)
    assert said == "held"
    dead.kill()                                    # never releases
    dead.wait(timeout=30)
    stale = L.holder(path)
    assert stale["pid"] == dead.pid and stale["alive"] is False
    assert "stale record" in L.describe(stale)
    got = L.acquire(10, path=path, poll=0.05)
    try:
        assert got is not None and L.holder(path)["pid"] == os.getpid()
    finally:
        L.release(got)


def test_a_holders_child_acquires_as_nested(path):
    with L.hold(0, path=path) as got:
        proc, said = child(path, env=got.env())
        finish(proc)
        assert said == "nested"
        proc, said = child(path)                   # an unrelated process still waits
        finish(proc)
        assert said == "busy"
