"""full_gate_lock: one full gate per machine. Two processes contend and only one holds
the lock; a dead holder's lock is taken over; no token stands in for the OS lock."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import full_gate_lock as L  # noqa: E402

TOKEN = "BFME_FULL_GATE_LOCK"      # the variable a removed nesting rule once honoured

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
    monkeypatch.delenv(TOKEN, raising=False)
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


def test_a_copied_or_stale_token_still_waits_on_the_os_lock(path):
    with L.hold(0, path=path):
        copied = L.holder(path)["token"]
        proc, said = child(path, env={TOKEN: copied})      # the holder record's token, copied
        finish(proc)
        assert said == "busy"
    dead, said = child(path)
    assert said == "held"
    stale = L.holder(path)["token"]
    dead.kill()
    dead.wait(timeout=30)
    first, said = child(path, env={TOKEN: stale})          # a dead holder's token
    try:
        assert said == "held"                              # the real lock, not a bypass
        proc, said = child(path, env={TOKEN: stale})
        finish(proc)
        assert said == "busy"
    finally:
        finish(first)
