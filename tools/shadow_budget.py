#!/usr/bin/env python3
"""A hard wall-clock budget for the shadow detectors the git hooks run synchronously.

WHY. tools/replay_check.py (pre-push) and tools/invented_names.py (pre-commit)
report and never refuse, so their only way to hurt a seat is time. Review
measured 112.65 s for a 500-commit push and more than 120 s for 2,000 commits.

HOW, kept simple and local on purpose. Every git call goes through
Budget.run(): its output goes to a temporary file (no pipe, so no reader
thread and nothing a stray process could hold open), its input comes from one,
and the call waits at most the budget that is left. On expiry it kills that
direct child (proc.kill()), reaps it and raises BudgetExceeded; the caller
reports what it finished ("partial: budget ... exceeded after N of M ...") and
exits 0. No watchdog thread, no job object, no process-tree kill: the children
are kept from starting grandchildren instead -- no pager (-c core.pager=cat,
GIT_PAGER/PAGER=cat), no signature verification, no fsmonitor, no credential
prompt (GIT_TERMINAL_PROMPT=0), stdin from /dev/null or a file, and callers
pass --no-ext-diff/--no-textconv to diffs. The hooks add a GNU `timeout`
backstop where one exists.

  BFME_SHADOW_BUDGET_S   seconds (default 10); 0 or less means no budget
"""
import os
import subprocess
import tempfile
import time

ENV = "BFME_SHADOW_BUDGET_S"
DEFAULT = 10.0
# git, configured not to start anything of its own
GIT = ("git", "--no-pager", "-c", "core.quotePath=false", "-c", "core.pager=cat",
       "-c", "log.showSignature=false", "-c", "core.fsmonitor=false")


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


def child_env():
    env = dict(os.environ, GIT_TERMINAL_PROMPT="0", GIT_PAGER="cat", PAGER="cat")
    env.pop("GIT_EXTERNAL_DIFF", None)
    return env


class Budget:
    def __init__(self, limit=None):
        self.limit = limit
        self.start = time.monotonic()
        self.expired = False
        self.env = child_env()

    def elapsed(self):
        return time.monotonic() - self.start

    def left(self):
        return None if not self.limit else max(0.0, self.limit - self.elapsed())

    def check(self):
        if self.expired or (self.limit and self.elapsed() >= self.limit):
            self.expired = True
            raise BudgetExceeded()

    def run(self, args, input=None):
        """(returncode, stdout bytes, stderr bytes) of one child that may run for the budget
        left; past it the child is killed and BudgetExceeded raised."""
        self.check()
        with tempfile.TemporaryFile() as out, tempfile.TemporaryFile() as err, \
                (tempfile.TemporaryFile() if input is not None else open(os.devnull, "rb")) as source:
            if input is not None:
                source.write(input)
                source.seek(0)
            proc = subprocess.Popen(args, stdin=source, stdout=out, stderr=err, env=self.env)
            try:
                proc.wait(timeout=self.left())
            except subprocess.TimeoutExpired:
                self.expired = True
            finally:
                if proc.poll() is None:          # expired, or interrupted (KeyboardInterrupt)
                    proc.kill()
                    proc.wait()
            if self.expired:
                raise BudgetExceeded()
            out.seek(0)
            err.seek(0)
            return proc.returncode, out.read(), err.read()
