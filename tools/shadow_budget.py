#!/usr/bin/env python3
"""A hard wall-clock budget for the shadow detectors the git hooks run synchronously.

WHY. tools/replay_check.py (pre-push) and tools/invented_names.py (pre-commit)
report and never refuse, so their only way to hurt a seat is time. Review
measured 112.65 s for a 500-commit push and more than 120 s for 2,000 commits,
and the killed tool left `git grep` children running.

HOW. Budget(seconds) starts a watchdog. Every subprocess goes through it
(budget.run / budget.lines / budget.popen); when the budget runs out the
watchdog kills each live child's whole process tree -- a Windows job object
(which also kills them if this process dies) and `taskkill /T`, or the child's
POSIX process group -- and the next budget call raises BudgetExceeded. The
caller catches it, reports what it finished ("partial: budget exceeded after N
of M ...") and exits 0. Closing the budget (a `with` block) kills anything still
running on every exit path, KeyboardInterrupt and SIGTERM included.

  BFME_SHADOW_BUDGET_S   seconds (default 10); 0 or less means no budget
"""
import os
import signal
import subprocess
import sys
import threading
import time

ENV = "BFME_SHADOW_BUDGET_S"
DEFAULT = 10.0
GRACE = 5.0          # after the watchdog fires, how long a read may still block


class BudgetExceeded(Exception):
    pass


def seconds(value=None):
    """The budget: an explicit value, else $BFME_SHADOW_BUDGET_S, else 10 s; <= 0 is none."""
    if value is None:
        value = os.environ.get(ENV, "").strip() or DEFAULT
    try:
        value = float(value)
    except ValueError:
        value = DEFAULT
    return value if value > 0 else None


def _windows_job():
    """A job object that kills its processes when its last handle closes, or None."""
    if os.name != "nt":
        return None
    try:
        import ctypes
        from ctypes import wintypes

        class Basic(ctypes.Structure):
            _fields_ = [("PerProcessUserTimeLimit", ctypes.c_int64), ("PerJobUserTimeLimit", ctypes.c_int64),
                        ("LimitFlags", wintypes.DWORD), ("MinimumWorkingSetSize", ctypes.c_size_t),
                        ("MaximumWorkingSetSize", ctypes.c_size_t), ("ActiveProcessLimit", wintypes.DWORD),
                        ("Affinity", ctypes.c_size_t), ("PriorityClass", wintypes.DWORD),
                        ("SchedulingClass", wintypes.DWORD)]

        class Extended(ctypes.Structure):
            _fields_ = [("BasicLimitInformation", Basic), ("IoInfo", ctypes.c_uint64 * 6),
                        ("ProcessMemoryLimit", ctypes.c_size_t), ("JobMemoryLimit", ctypes.c_size_t),
                        ("PeakProcessMemoryUsed", ctypes.c_size_t), ("PeakJobMemoryUsed", ctypes.c_size_t)]

        k32 = ctypes.WinDLL("kernel32", use_last_error=True)
        k32.CreateJobObjectW.restype = wintypes.HANDLE
        k32.CreateJobObjectW.argtypes = (ctypes.c_void_p, wintypes.LPCWSTR)
        k32.SetInformationJobObject.argtypes = (wintypes.HANDLE, ctypes.c_int, ctypes.c_void_p, wintypes.DWORD)
        k32.OpenProcess.restype = wintypes.HANDLE
        k32.OpenProcess.argtypes = (wintypes.DWORD, wintypes.BOOL, wintypes.DWORD)
        k32.AssignProcessToJobObject.argtypes = (wintypes.HANDLE, wintypes.HANDLE)
        k32.TerminateJobObject.argtypes = (wintypes.HANDLE, wintypes.UINT)
        k32.CloseHandle.argtypes = (wintypes.HANDLE,)
        job = k32.CreateJobObjectW(None, None)
        if not job:
            return None
        info = Extended()
        info.BasicLimitInformation.LimitFlags = 0x2000          # JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE
        if not k32.SetInformationJobObject(job, 9, ctypes.byref(info), ctypes.sizeof(info)):
            k32.CloseHandle(job)
            return None
        return k32, job
    except (OSError, AttributeError, ImportError):
        return None


class Budget:
    def __init__(self, limit=None):
        self.limit = limit
        self.start = time.monotonic()
        self.expired = False
        self._procs = set()
        self._lock = threading.Lock()
        self._job = _windows_job()
        self._timer = None
        if limit:
            self._timer = threading.Timer(limit, self.expire)
            self._timer.daemon = True
            self._timer.start()

    # ------------------------------------------------------------ state
    def elapsed(self):
        return time.monotonic() - self.start

    def left(self):
        return None if not self.limit else max(0.0, self.limit - self.elapsed())

    def check(self):
        if self.expired or (self.limit and self.elapsed() >= self.limit):
            self.expired = True
            raise BudgetExceeded()

    def expire(self):
        with self._lock:
            self.expired = True
            live = list(self._procs)
        if self._job is not None and live:
            k32, job = self._job
            k32.TerminateJobObject(job, 1)
        for proc in live:
            kill_tree(proc)

    def close(self):
        if self._timer is not None:
            self._timer.cancel()
        with self._lock:
            live = list(self._procs)
            self._procs.clear()
        for proc in live:
            kill_tree(proc)
        if self._job is not None:
            k32, job = self._job
            self._job = None
            k32.CloseHandle(job)

    def __enter__(self):
        return self

    def __exit__(self, *_exc):
        self.close()
        return False

    # ------------------------------------------------------------ processes
    def popen(self, args, **kwargs):
        self.check()
        if os.name != "nt":
            kwargs.setdefault("start_new_session", True)      # its own group: killpg reaches its children
        proc = subprocess.Popen(args, **kwargs)
        if self._job is not None:
            k32, job = self._job
            handle = k32.OpenProcess(0x0101, False, proc.pid)   # PROCESS_SET_QUOTA | PROCESS_TERMINATE
            if handle:
                k32.AssignProcessToJobObject(job, handle)
                k32.CloseHandle(handle)
        with self._lock:
            self._procs.add(proc)
            late = self.expired
        if late:
            kill_tree(proc)
        return proc

    def done(self, proc):
        with self._lock:
            self._procs.discard(proc)
        if proc.poll() is None:
            kill_tree(proc)

    def _timeout(self):
        left = self.left()
        return None if left is None else left + GRACE

    def run(self, args, input=None):
        """(returncode, stdout bytes, stderr bytes); BudgetExceeded when the budget ran out."""
        proc = self.popen(args, stdin=subprocess.PIPE if input is not None else subprocess.DEVNULL,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            out, err = proc.communicate(input, timeout=self._timeout())
        except subprocess.TimeoutExpired:
            self.expired = True
            raise BudgetExceeded() from None
        finally:
            self.done(proc)
        if self.expired:
            raise BudgetExceeded()
        return proc.returncode, out, err

    def lines(self, args, input=None):
        """Yield stdout lines (bytes, newline kept) as they arrive; a non-zero exit raises
        RuntimeError, an exhausted budget BudgetExceeded."""
        proc = self.popen(args, stdin=subprocess.PIPE if input is not None else subprocess.DEVNULL,
                          stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
        writer = None
        if input is not None:
            def feed():
                try:
                    proc.stdin.write(input)
                    proc.stdin.close()
                except OSError:
                    pass
            writer = threading.Thread(target=feed, daemon=True)
            writer.start()
        try:
            for line in proc.stdout:
                if self.expired:
                    break
                yield line
            proc.stdout.close()
            try:
                proc.wait(timeout=self._timeout())
            except subprocess.TimeoutExpired:
                self.expired = True
        finally:
            self.done(proc)
            if writer is not None:
                writer.join(GRACE)
        if self.expired:
            raise BudgetExceeded()
        if proc.returncode:
            raise RuntimeError("%s exited %d" % (" ".join(str(a) for a in args[:4]), proc.returncode))


def kill_tree(proc):
    """Kill a child and everything it started."""
    if proc.poll() is not None and os.name == "nt":
        return
    try:
        if os.name == "nt":
            subprocess.run(["taskkill", "/F", "/T", "/PID", str(proc.pid)], stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL, timeout=GRACE)
        else:
            os.killpg(proc.pid, signal.SIGKILL)
    except (OSError, subprocess.SubprocessError):
        pass
    try:
        proc.kill()
        proc.wait(timeout=GRACE)        # reap it: no zombie outlives the budget
    except (OSError, subprocess.SubprocessError):
        pass


def exit_on_signals():
    """POSIX: turn SIGTERM/SIGHUP into SystemExit so `with Budget()` still kills its children
    (they run in their own process group, out of reach of the terminal's signals)."""
    if os.name == "nt" or threading.current_thread() is not threading.main_thread():
        return

    def leave(signum, _frame):
        sys.exit(128 + signum)

    for name in ("SIGTERM", "SIGHUP"):
        if hasattr(signal, name):
            signal.signal(getattr(signal, name), leave)
