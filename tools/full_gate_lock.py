#!/usr/bin/env python3
"""One full gate per machine: an OS-level exclusive lock on one fixed file outside any clone.

WHY. Two full gates on one PC crash it (WinError 1450 and BrokenProcessPool,
2026-10-28). tools/build.py's compile lock covers one object cache, and every
worktree has its own; tools/master_verify.py's run lock covers one clone. A
process-list snapshot cannot stop it either: two callers can both see a quiet
machine and start.

HOW. Whoever launches a full gate holds this lock for the gate's whole run:
tools/master_verify.py (every gate it runs) and the pre-push hook's full gate
(.githooks/pre-push calls `python3 tools/full_gate_lock.py run -- <the gate>`;
that hook's owner adds the call). tools/build.py never takes it itself. The lock
is msvcrt/fcntl on ~/.cache/open-bfme/full-gate.lock, shared by every clone and
worktree of the user, and the OS releases it when the holder exits, however it
exits. A record beside it (full-gate.lock.json) names the holder (pid, host,
started, note) for waiters and `status`; a record whose pid is dead is stale, and
the lock is taken as soon as the OS lets go of it. A holder's children inherit
BFME_FULL_GATE_LOCK (the holder's token) and acquire as nested, so a gate launched
under the lock never waits on its own parent.

  python3 tools/full_gate_lock.py status
  python3 tools/full_gate_lock.py run [--timeout S] [--note TEXT] -- CMD ARG...
          (exit: CMD's own; 75 when the lock stayed held past --timeout)
"""
import argparse
import json
import os
import secrets
import socket
import subprocess
import sys
import time
from contextlib import contextmanager
from dataclasses import dataclass
from pathlib import Path

DEFAULT = Path.home() / ".cache" / "open-bfme" / "full-gate.lock"
TOKEN_ENV = "BFME_FULL_GATE_LOCK"
TIMED_OUT = 75


class Busy(RuntimeError):
    """The lock stayed held past the timeout."""


@dataclass
class Held:
    path: Path
    token: str
    handle: object = None       # None: nested under the holder that launched this process

    def env(self):
        """What a child launched under the lock needs to see it as held by its parent."""
        return {TOKEN_ENV: self.token}


def record_path(path):
    return path.with_name(path.name + ".json")


def pid_alive(pid):
    try:
        import psutil
        return psutil.pid_exists(pid)
    except ImportError:
        pass
    if os.name == "nt":
        import ctypes
        kernel32 = ctypes.windll.kernel32
        handle = kernel32.OpenProcess(0x1000, False, pid)   # PROCESS_QUERY_LIMITED_INFORMATION
        if not handle:
            return kernel32.GetLastError() == 5                # access denied: it exists
        code = ctypes.c_ulong()
        kernel32.GetExitCodeProcess(handle, ctypes.byref(code))
        kernel32.CloseHandle(handle)
        return code.value == 259                               # STILL_ACTIVE
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except PermissionError:
        return True
    return True


def holder(path=None):
    """The holder record ({} when there is none), with `alive`: whether its pid runs."""
    try:
        info = json.loads(record_path(Path(path or DEFAULT)).read_text(encoding="utf-8"))
    except (FileNotFoundError, ValueError):
        return {}
    info["alive"] = isinstance(info.get("pid"), int) and pid_alive(info["pid"])
    return info


def describe(info):
    if not info:
        return "no holder record"
    state = "running" if info.get("alive") else "stale record: that pid is gone"
    return (f"pid {info.get('pid')} on {info.get('host', '?')} since {info.get('started', '?')} "
            f"({info.get('note') or 'no note'}; {state})")


def _try(path):
    path.parent.mkdir(parents=True, exist_ok=True)
    handle = open(path, "a+")
    try:
        if os.name == "nt":
            import msvcrt
            handle.seek(0)
            msvcrt.locking(handle.fileno(), msvcrt.LK_NBLCK, 1)
        else:
            import fcntl
            fcntl.flock(handle, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except OSError:
        handle.close()
        return None
    return handle


def _unlock(handle):
    try:
        if os.name == "nt":
            import msvcrt
            handle.seek(0)
            msvcrt.locking(handle.fileno(), msvcrt.LK_UNLCK, 1)
        else:
            import fcntl
            fcntl.flock(handle, fcntl.LOCK_UN)
    finally:
        handle.close()


def acquire(timeout=0.0, *, path=None, note="", poll=0.5):
    """Held, or None when the lock is still held after TIMEOUT seconds (None: wait
    as long as it takes; 0: one try)."""
    path = Path(path or DEFAULT)
    inherited = os.environ.get(TOKEN_ENV)
    if inherited and holder(path).get("token") == inherited:
        return Held(path, inherited)
    deadline = None if timeout is None else time.monotonic() + timeout
    told = False
    while True:
        handle = _try(path)
        if handle is not None:
            token = f"{os.getpid()}-{secrets.token_hex(6)}"
            record = {"pid": os.getpid(), "host": socket.gethostname(), "token": token, "note": note,
                      "started": time.strftime("%Y-%m-%dT%H:%M:%S%z")}
            temp = record_path(path).with_name(f"{record_path(path).name}.{os.getpid()}.tmp")
            temp.write_text(json.dumps(record), encoding="utf-8")
            os.replace(temp, record_path(path))
            return Held(path, token, handle)
        if deadline is not None and time.monotonic() >= deadline:
            return None
        if not told:
            print(f"full_gate_lock: waiting: {describe(holder(path))}", file=sys.stderr, flush=True)
            told = True
        time.sleep(poll)


def release(held):
    if held is None or held.handle is None:
        return
    try:
        if holder(held.path).get("token") == held.token:
            record_path(held.path).unlink(missing_ok=True)
    finally:
        _unlock(held.handle)
        held.handle = None


@contextmanager
def hold(timeout=None, *, path=None, note="", poll=0.5):
    """The lock for the with-block; Busy when it stays held past TIMEOUT."""
    got = acquire(timeout, path=path, note=note, poll=poll)
    if got is None:
        raise Busy(f"the machine's full-gate lock is held: {describe(holder(path))}")
    try:
        yield got
    finally:
        release(got)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status", help="who holds the lock")
    run = sub.add_parser("run", help="run a command holding the lock")
    run.add_argument("--timeout", type=float, default=None, help="seconds to wait (default: as long as it takes)")
    run.add_argument("--note", default="", help="shown to waiters")
    run.add_argument("command", nargs=argparse.REMAINDER)
    args = ap.parse_args(argv)
    if args.cmd == "status":
        got = acquire(0)
        if got is not None:
            release(got)
            print("full_gate_lock: free")
        else:
            print(f"full_gate_lock: held: {describe(holder())}")
        return 0
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    if not command:
        ap.error("run needs a command after --")
    try:
        with hold(args.timeout, note=args.note or " ".join(command)[:200]) as got:
            return subprocess.run(command, env={**os.environ, **got.env()}).returncode
    except Busy as error:
        print(f"full_gate_lock: {error}", file=sys.stderr)
        return TIMED_OUT


if __name__ == "__main__":
    sys.exit(main())
