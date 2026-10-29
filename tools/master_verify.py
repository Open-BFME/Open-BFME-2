#!/usr/bin/env python3
"""The post-push backstop: run the full gate on origin/master itself, and bisect a red tip.

WHY. A push runs a scoped, incremental check (.githooks/pre-push): it verifies what
the outgoing range can reach, so an effect across files it does not select lands on
master green. On 2026-10-28 a scoped push broke DIR32 consistency and every later
full gate went red for it, with nothing pointing at the commit. This tool checks
master itself, continuously. A scheduled runner calls it; it is no hook and no seat
runs it as part of a push. tools/repair_queue.py reads what it finds.

HOW. --once fetches origin/master. When the tip has no verdict yet, no other run
holds the lock (build/master_verify/run.lock of the main checkout, so one per clone)
and no other full gate is running on this machine (a tools/build.py process with no
selector, or full_gate_receipt.py cross-checks), it checks the tip out in its own
worktree (build/master_verify/wt, made by tools/worktree_setup.py) and runs the
ordinary full gate there, the checks the pre-push hook's full scope runs:
tools/build.py with no selector (BUILD_POOL, default 6), eh_verify.py --all and
data_check.py --converged --all. Each commit is judged by its own tools/. Objects
come from the worktree's build/match and the shared object store, so a step whose
sources did not change compiles nothing.

  green  state.json records {sha, time, duration, green}, and the receipt store
         (tools/full_gate_receipt.py record, in the git common directory) gets the
         commit, so a seat's pre-push in this clone can carry from it. Queue items
         whose first bad commit the tip contains are retired.
  red    the checks red at the tip that no open item covers are bisected over the
         first-parent range from the newest commit where they were green (the last
         green tip, or the last red one when they were green there; with neither,
         first-parent ancestors 1, 3, 7, 15 ... commits back are probed) to the first commit
         where one of them goes red. Each such commit becomes a repair item in
         reverse/master_verify_queue.json: the bad SHA, its author and subject, the
         failing checks' output, the files it changed and the sources the output
         names, and the suggested owner. Before an item is queued the gate runs
         again, fresh, at the first bad commit (red again) and its parent (green
         again); a cached red is never evidence until it reproduced, and an
         attribution that does not hold is retried next run. Items whose checks
         are green at the tip are retired. Nothing is reverted.
  error  a gate that ended without a verdict (a crash, the environment) is recorded
         and retried on the next tick. It is never bisected and never queued; a
         search it interrupts publishes nothing and is retried too.

A step that cannot start because another full gate is running waits for it
(--busy-wait, default 30 minutes), then defers the run; verdicts already reached
are kept in state.json, so the next run resumes the bisect without repeating them.

THE QUEUE. reverse/master_verify_queue.json is tracked, and only this tool writes it:
an item is added by a bisect and leaves only on a later full gate at a tip that
contains its bad commit and passes its checks. Seats never edit it; they fix the
regression and push, and the next run retires the item. The tool commits the file
alone, on top of origin/master, in its worktree, and pushes it through the hooks
(--push-cmd runs a push script instead), honouring --push-clock (five minutes
between pushes of one account). A change that could not be pushed stays pending in
state.json and is retried first on the next run. tools/repair_queue.py repair serves
the items before every other repair, and next_work.py --claim draws them first.

OUTPUT. Only the queue file and build/master_verify/ (state.json, run.lock,
run.json, logs/, the worktree). Commits use the runner's git identity
(GIT_AUTHOR_*/GIT_COMMITTER_* or user.*).

EXIT. --once: 0 green, nothing to do or deferred; 1 red (queued now or before,
an already-checked red tip included); 2 no verdict, at the tip or in the search
for its first bad commit (retried next run).

  python3 tools/master_verify.py --once
  python3 tools/master_verify.py --watch --interval 300
  python3 tools/master_verify.py --status
"""
import argparse
import datetime
import hashlib
import json
import os
import re
import shlex
import shutil
import socket
import subprocess
import sys
import tempfile
import time
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
QUEUE = "reverse/master_verify_queue.json"
POOL = 6
PUSH_SPACING = 300          # seconds between pushes of one account (AGENTS.md)
KEEP_RUNS = 50
KEEP_VERDICTS = 200
EXCERPT_LINES = 80
EXCERPT_CHARS = 6000
FULL_MARK = "FULL GATE: FAIL"
TRACEBACK = "Traceback (most recent call last)"
# The pre-push hook clears these before its full gate: the receipt describes that command.
DROP_ENV = ("BUILD_RECOMPILE_ONLY", "CL", "_CL_")
SOURCE_RE = re.compile(r"\b(Code/[^\s():,;'\"]+\.(?:cpp|c|asm|h|hpp|inl))\b")
FAIL_RE = re.compile(r"\bFAIL\b|^Traceback|FULL GATE")


class GitError(RuntimeError):
    pass


class Deferred(RuntimeError):
    """Another full gate kept the machine busy past --busy-wait."""


class Unsettled(RuntimeError):
    """The search for a first bad commit did not settle: the run stays incomplete,
    publishes nothing for it, and the next run retries."""


def git(cwd, *args, check=True):
    done = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if check and done.returncode:
        raise GitError(f"git {' '.join(args)}: {(done.stderr or done.stdout).strip()}")
    return done.stdout.strip()


def now_iso(when=None):
    return datetime.datetime.fromtimestamp(time.time() if when is None else when,
                                           datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def say(message):
    print(f"[master_verify {time.strftime('%H:%M:%S')}] {message}", flush=True)


def main_checkout(root):
    """The clone's main checkout (the parent of the git common directory)."""
    common = Path(git(root, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    return common.parent if common.name == ".git" else common


@dataclass
class Stage:
    label: str
    argv: list
    # Red only when the output carries the marker; a nonzero exit without it is no verdict.
    marker: str = None
    env: dict = field(default_factory=dict)


@dataclass
class Config:
    root: Path = ROOT
    base: Path = None           # build/master_verify of the main checkout
    worktree: Path = None       # base/wt
    remote: str = "origin"
    branch: str = "master"
    pool: int = POOL
    publish: bool = True
    push_cmd: str = None        # a template with {worktree} and {log}
    push_clock: Path = None
    push_tries: int = 6
    probe_limit: int = 5
    busy_wait: float = 1800
    busy_poll: float = 30
    # Hooks for the tests (a fake gate on a toy history); the CLI never sets them.
    stages: object = None       # (cfg, sha, tmp) -> [Stage]
    prepare: object = None      # (cfg, sha) -> None
    record_receipt: object = None   # (cfg, sha, tmp) -> (ok, text)
    busy: object = None         # () -> [(pid, command line)]

    def __post_init__(self):
        self.root = Path(self.root)
        self.base = Path(self.base) if self.base else main_checkout(self.root) / "build" / "master_verify"
        self.worktree = Path(self.worktree) if self.worktree else self.base / "wt"
        self.stages = self.stages or full_gate
        self.prepare = self.prepare or prepare_worktree
        self.record_receipt = self.record_receipt or record_receipt
        self.busy = self.busy or other_full_gates


# ---------------------------------------------------------------- state and lock

def state_path(cfg):
    return cfg.base / "state.json"


def load_state(cfg):
    try:
        return json.loads(state_path(cfg).read_text(encoding="utf-8"))
    except FileNotFoundError:
        return {}


def save_state(cfg, state):
    cfg.base.mkdir(parents=True, exist_ok=True)
    verdicts = state.get("verdicts", {})
    if len(verdicts) > KEEP_VERDICTS:
        keep = sorted(verdicts, key=lambda sha: verdicts[sha].get("time", ""))[-KEEP_VERDICTS:]
        state["verdicts"] = {sha: verdicts[sha] for sha in keep}
    state["runs"] = state.get("runs", [])[-KEEP_RUNS:]
    temp = state_path(cfg).with_name(f"state.{os.getpid()}.tmp")
    temp.write_text(json.dumps(state, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    os.replace(temp, state_path(cfg))


def try_lock(path):
    """An exclusive lock on PATH without waiting: the open handle, or None when held."""
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


def unlock(handle):
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


def holder(cfg):
    try:
        return json.loads((cfg.base / "run.json").read_text(encoding="utf-8"))
    except (FileNotFoundError, ValueError):
        return {}


def set_phase(cfg, **info):
    (cfg.base / "run.json").write_text(json.dumps({"pid": os.getpid(), "host": socket.gethostname(),
                                                   **info}, sort_keys=True), encoding="utf-8")


# ---------------------------------------------------------------- other full gates

def full_gate_kind(argv):
    """What full gate ARGV runs: tools/build.py with no selector, or the carried
    cross-source checks; None for anything else (a scoped build included)."""
    args = [a.replace("\\", "/") for a in argv]
    for i, arg in enumerate(args):
        if arg == "tools/build.py" or arg.endswith("/tools/build.py"):
            return "tools/build.py (full)" if not any(args[i + 1:]) else None
        if arg.endswith("tools/full_gate_receipt.py") and "cross-checks" in args[i + 1:]:
            return "full_gate_receipt.py cross-checks"
    return None


def _split_windows(line):
    return [a or b for a, b in re.findall(r'"((?:[^"\\]|\\.)*)"|(\S+)', line or "")]


def processes():
    """[(pid, argv)] of the processes on this machine whose command line is readable.
    Raises when none can be listed: an unknown machine is not an idle one."""
    try:
        import psutil
    except ImportError:
        psutil = None
    if psutil is not None:
        found = []
        for proc in psutil.process_iter(["pid", "cmdline"]):
            argv = proc.info.get("cmdline")
            if argv:
                found.append((proc.info["pid"], list(argv)))
        return found
    if os.name == "nt":
        done = subprocess.run(
            ["powershell", "-NoProfile", "-NonInteractive", "-Command",
             "Get-CimInstance Win32_Process | Where-Object CommandLine | "
             "Select-Object ProcessId,CommandLine | ConvertTo-Json -Compress"],
            capture_output=True, text=True, encoding="utf-8", errors="replace", check=True)
        data = json.loads(done.stdout or "[]")
        data = [data] if isinstance(data, dict) else data
        return [(d["ProcessId"], _split_windows(d["CommandLine"])) for d in data]
    done = subprocess.run(["ps", "-eo", "pid=,args="], capture_output=True, text=True, check=True)
    found = []
    for line in done.stdout.splitlines():
        pid, _, args = line.strip().partition(" ")
        if pid.isdigit():
            found.append((int(pid), args.split()))
    return found


def other_full_gates():
    """[(pid, command line)] of full gates running on this machine, other than this
    process and its ancestors."""
    mine = {os.getpid(), os.getppid()}
    try:
        import psutil
        mine |= {p.pid for p in psutil.Process().parents()}
    except ImportError:
        pass
    return [(pid, " ".join(argv)) for pid, argv in processes()
            if pid not in mine and full_gate_kind(argv)]


def wait_until_free(cfg):
    waited = 0.0
    while True:
        others = cfg.busy()
        if not others:
            return
        if waited >= cfg.busy_wait:
            raise Deferred("another full gate is running: "
                           + "; ".join(f"pid {pid} {line[:100]}" for pid, line in others))
        if waited == 0:
            say(f"waiting: another full gate is running (pid {others[0][0]})")
        time.sleep(cfg.busy_poll)
        waited += cfg.busy_poll


# ---------------------------------------------------------------- the gate

def prepare_worktree(cfg, sha):
    """Check SHA out in the tool's own worktree (tools/worktree_setup.py: its own
    reference/open-bfme-1 at SHA's pin, hooks from .githooks)."""
    wt = cfg.worktree
    if not (wt / ".git").exists():
        wt.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run([sys.executable, str(cfg.root / "tools" / "worktree_setup.py"), "create", str(wt),
                        "--base", sha], cwd=cfg.root, check=True)
    else:
        git(wt, "-c", "submodule.recurse=false", "checkout", "-q", "-f", "--detach", sha)
        subprocess.run([sys.executable, str(wt / "tools" / "worktree_setup.py"), "prepare", str(wt)],
                       cwd=wt, check=True, stdout=subprocess.DEVNULL)
    if git(wt, "rev-parse", "HEAD") != sha:
        raise GitError(f"{wt} is not at {sha}")


def full_gate(cfg, sha, tmp):
    """The pre-push hook's full scope: the full build, then the exception-data and
    converged-data audits over every source. The DIR32 index stays outside the
    BFME_GATE_LOADS folder: full_gate_receipt.gate_loads reads every file there as text."""
    py = sys.executable
    loads = tmp / "loads"
    loads.mkdir()
    env = {"BFME_GATE_LOADS": str(loads), "BFME_DIR32_INDEX": str(tmp / "dir32-index.gz")}
    parent = git(cfg.worktree, "rev-parse", "--verify", "--quiet", f"{sha}^", check=False)
    data = [py, "tools/data_check.py", "--converged", "--all", "--ref", sha]
    return [Stage("full gate", [py, "tools/build.py"], FULL_MARK, env),
            Stage("eh verify", [py, "tools/eh_verify.py", "--all"], "EH verify: FAIL"),
            Stage("data identity", data + (["--converged-base", parent] if parent else []))]


def record_receipt(cfg, sha, tmp):
    argv = [sys.executable, "tools/full_gate_receipt.py", "record", sha, "--loads", str(tmp / "loads")]
    if (tmp / "dir32-index.gz").is_file():
        argv += ["--dir32-index", str(tmp / "dir32-index.gz")]
    done = subprocess.run(argv, cwd=cfg.worktree, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    return done.returncode == 0, (done.stdout + done.stderr).strip()


def stage_env(cfg, stage):
    env = {k: v for k, v in os.environ.items() if k not in DROP_ENV}
    env.update({"BUILD_POOL": str(cfg.pool), "PYTHONIOENCODING": "utf-8"})
    env.update(stage.env)
    return env


def classify(stage, code, text):
    """('green'|'red'|'error', red check labels) of one stage."""
    if code == 0:
        return "green", []
    if stage.marker:
        if stage.marker not in text:
            return "error", []
        if stage.marker == FULL_MARK:
            found = re.findall(r"FULL GATE: FAIL\W+\d+ red: (.+)$", text, re.MULTILINE)
            labels = [l.strip() for l in found[-1].split(",") if l.strip()] if found else []
            return "red", labels or [stage.label]
        return "red", [stage.label]
    if TRACEBACK in text:
        return "error", []
    return "red", [stage.label]


def excerpt(text):
    """The failure lines of a gate's output, each with its indented detail."""
    lines = text.splitlines()
    keep, seen = [], set()
    for i, line in enumerate(lines):
        if not FAIL_RE.search(line):
            continue
        block = [line] + [l for l in lines[i + 1:i + 9] if l.startswith(("  ", "\t"))][:8]
        for l in block:
            if l not in seen:
                seen.add(l)
                keep.append(l)
    out, size = [], 0
    for line in keep[:EXCERPT_LINES]:
        size += len(line) + 1
        if size > EXCERPT_CHARS:
            out.append("... (cut; the full log is on the runner)")
            break
        out.append(line)
    return "\n".join(out)


def run_gate(cfg, sha, state, why, keep=False, fresh=False):
    """The gate's verdict at SHA: {verdict, checks, duration, time, excerpt, sources},
    cached in state['verdicts']. A cached red counts only once it reproduced
    (confirm); FRESH ignores the cache. With KEEP, a fresh green verdict also leaves
    `tmp` (the gate's tool list and DIR32 index) for the receipt; the caller removes it."""
    cached = state.setdefault("verdicts", {}).get(sha)
    if not fresh and cached and (cached["verdict"] == "green" or cached.get("reproduced")):
        say(f"{sha[:10]} ({why}): {cached['verdict']} (cached)")
        return dict(cached, cached=True)
    wait_until_free(cfg)
    set_phase(cfg, sha=sha, phase=why, started=now_iso())
    say(f"{sha[:10]} ({why}): preparing the worktree")
    cfg.prepare(cfg, sha)
    (cfg.base / "tmp").mkdir(parents=True, exist_ok=True)
    (cfg.base / "logs").mkdir(parents=True, exist_ok=True)
    tmp = Path(tempfile.mkdtemp(prefix=f"{sha[:10]}-", dir=cfg.base / "tmp"))
    log = cfg.base / "logs" / f"{sha}.log"
    started = time.time()
    verdict, checks, texts = "green", [], []
    with log.open("w", encoding="utf-8", newline="\n") as combined:
        for n, stage in enumerate(cfg.stages(cfg, sha, tmp)):
            say(f"{sha[:10]} ({why}): {stage.label}")
            out = tmp / f"stage{n}.log"
            with out.open("wb") as handle:
                code = subprocess.run(stage.argv, cwd=cfg.worktree, stdout=handle, stderr=subprocess.STDOUT,
                                      env=stage_env(cfg, stage)).returncode
            text = out.read_text(encoding="utf-8", errors="replace")
            combined.write(f"== {stage.label} (exit {code}): {' '.join(stage.argv)}\n{text}\n")
            got, labels = classify(stage, code, text)
            if got != "green":
                texts.append(text)
            if got == "error":
                verdict = "error"
                checks = [f"{stage.label} (no verdict, exit {code})"]
                break
            if got == "red":
                verdict = "red"
                checks += [l for l in labels if l not in checks]
    text = excerpt("\n".join(texts))
    result = {"verdict": verdict, "checks": checks, "duration": round(time.time() - started),
              "time": now_iso(started), "excerpt": text if verdict != "green" else "",
              "sources": sorted(set(SOURCE_RE.findall(text)))[:50], "log": str(log)}
    say(f"{sha[:10]} ({why}): {verdict}" + (f" ({', '.join(checks)})" if checks else "")
        + f" in {result['duration']} s")
    if verdict in ("green", "red"):
        state["verdicts"][sha] = dict(result, reproduced=False) if verdict == "red" else result
    if verdict == "green" and keep:
        return dict(result, tmp=str(tmp))
    shutil.rmtree(tmp, ignore_errors=True)
    return result


# ---------------------------------------------------------------- bisect

def is_ancestor(cfg, old, new):
    return subprocess.run(["git", "merge-base", "--is-ancestor", old, new], cwd=cfg.root,
                          capture_output=True).returncode == 0


def only_queue_changed(cfg, old, new):
    changed = git(cfg.root, "diff", "--name-only", old, new, check=False).split()
    return bool(changed) and set(changed) <= {QUEUE} and is_ancestor(cfg, old, new)


def bad_for(result, labels):
    return result["verdict"] == "red" and bool(set(result["checks"]) & set(labels))


def find_good(cfg, state, bad, labels):
    """Probe first-parent ancestors 1, 3, 7, 15 ... commits behind BAD (the step doubles)
    for a commit where none of LABELS is red: (good or None, nearest known bad, error
    result or None)."""
    step = 1
    for _ in range(cfg.probe_limit):
        probe = git(cfg.root, "rev-parse", "--verify", "--quiet", f"{bad}~{step}^{{commit}}", check=False)
        if not probe:
            break
        result = run_gate(cfg, probe, state, "probe")
        if result["verdict"] == "error":
            return None, bad, result
        if not bad_for(result, labels):
            return probe, bad, None
        bad, step = probe, step * 2
    return None, bad, None


def bisect(cfg, state, good, bad, labels):
    """(first bad, last good, exact, error result or None) over good..bad (first parent)."""
    commits = git(cfg.root, "rev-list", "--first-parent", "--reverse", f"{good}..{bad}").split()
    if not commits or commits[-1] != bad:
        return bad, good, False, None
    lo, hi = -1, len(commits) - 1
    while hi - lo > 1:
        mid = (lo + hi) // 2
        result = run_gate(cfg, commits[mid], state, f"bisect {hi - lo - 1} left")
        if result["verdict"] == "error":
            return commits[hi], commits[lo] if lo >= 0 else good, False, result
        if bad_for(result, labels):
            hi = mid
        else:
            lo = mid
    return commits[hi], commits[lo] if lo >= 0 else good, True, None


def confirm(cfg, state, first, parent, labels):
    """Run the gate again, fresh, before an attribution is queued: FIRST must be red for
    LABELS again and PARENT (when known) green for them. Otherwise Unsettled; the fresh
    verdicts replace the cached ones, so the next run's search starts from them."""
    again = run_gate(cfg, first, state, "confirm first bad", fresh=True)
    if not bad_for(again, labels):
        raise Unsettled(f"{first[:10]} did not reproduce its failure ({again['verdict']} now)")
    state["verdicts"][first]["reproduced"] = True
    if parent:
        before = run_gate(cfg, parent, state, "confirm its parent", fresh=True)
        if before["verdict"] == "error" or bad_for(before, labels):
            raise Unsettled(f"{parent[:10]}, the parent of {first[:10]}, is {before['verdict']} now"
                            + (f" ({', '.join(before['checks'])})" if before["checks"] else ""))


def make_item(cfg, state, tip, bad, good, exact, labels, note=""):
    sha, name, email, authored, subject = git(
        cfg.root, "show", "-s", "--format=%H%x00%an%x00%ae%x00%aI%x00%s", bad).split("\0")
    parent = git(cfg.root, "rev-parse", "--verify", "--quiet", f"{bad}^", check=False)
    files = (git(cfg.root, "diff", "--name-only", parent, bad) if parent
             else git(cfg.root, "show", "--name-only", "--format=", bad)).splitlines()
    at_bad = state["verdicts"].get(bad) or state["verdicts"].get(tip) or {}
    author = f"{name} <{email}>"
    return {
        "id": f"{sha[:12]}-{hashlib.sha1(','.join(sorted(labels)).encode()).hexdigest()[:6]}",
        "bad_sha": sha,
        "subject": subject,
        "author": author,
        "authored": authored,
        "suggested_owner": (f"{author}, who pushed {sha[:10]}" if exact else
                            f"unknown: the first bad commit is in {good[:10] if good else '(no green found)'}.."
                            f"{sha[:10]}; {author} wrote its last commit"),
        "good_sha": good or "",
        "exact": exact,
        "tip_sha": tip,
        "checks": sorted(labels),
        "output": at_bad.get("excerpt", ""),
        "files": files[:200],
        "named_sources": at_bad.get("sources", []),
        "found": now_iso(),
        "note": note,
    }


# ---------------------------------------------------------------- the queue

def read_queue_text(text):
    return json.loads(text).get("items", []) if text.strip() else []


def write_queue(path, items):
    path.parent.mkdir(parents=True, exist_ok=True)
    data = {"tool": "tools/master_verify.py",
            "note": "Regressions of origin/master found by the post-push backstop. Written only by "
                    "tools/master_verify.py; an item leaves when a later full gate at a tip that "
                    "contains its bad commit passes its checks.",
            "items": sorted(items, key=lambda i: (i["found"], i["id"]))}
    path.write_text(json.dumps(data, indent=1, sort_keys=True, ensure_ascii=False) + "\n",
                    encoding="utf-8", newline="\n")


def fetch_tip(cfg):
    ref = f"refs/remotes/{cfg.remote}/{cfg.branch}"
    git(cfg.root, "fetch", "-q", cfg.remote, f"+refs/heads/{cfg.branch}:{ref}")
    return git(cfg.root, "rev-parse", ref)


def remote_queue(cfg):
    """The queue at origin/master (as last fetched)."""
    ref = f"refs/remotes/{cfg.remote}/{cfg.branch}"
    done = subprocess.run(["git", "show", f"{ref}:{QUEUE}"], cwd=cfg.root, capture_output=True,
                          text=True, encoding="utf-8", errors="replace")
    return read_queue_text(done.stdout) if done.returncode == 0 else []


def open_items(cfg, state):
    """Published items plus pending additions, without pending retirements."""
    pending = state.get("pending") or {}
    retiring = set(pending.get("retire", ()))
    items = {i["id"]: i for i in remote_queue(cfg) + pending.get("add", [])}
    return [i for key, i in items.items() if key not in retiring]


def wait_push_clock(cfg):
    if not cfg.push_clock:
        return
    try:
        last = int(Path(cfg.push_clock).read_text().split()[0])
    except (FileNotFoundError, ValueError, IndexError):
        return
    wait = last + PUSH_SPACING - time.time()
    if wait > 0:
        say(f"push clock: waiting {int(wait)} s")
        time.sleep(wait)


def push(cfg, attempt):
    wt = cfg.worktree
    if cfg.push_cmd:
        log = cfg.base / "logs" / f"push-{int(time.time())}-{attempt}.log"
        argv = [a.format(worktree=wt.as_posix(), log=log.as_posix()) for a in shlex.split(cfg.push_cmd)]
        done = subprocess.run(argv, capture_output=True, text=True, encoding="utf-8", errors="replace")
        return (done.stdout + done.stderr).strip()
    done = subprocess.run(["git", "-c", "core.hooksPath=.githooks", "-c", "submodule.recurse=false", "push",
                           cfg.remote, f"HEAD:refs/heads/{cfg.branch}"], cwd=wt, capture_output=True,
                          text=True, encoding="utf-8", errors="replace")
    return (done.stdout + done.stderr).strip()


def publish(cfg, state):
    """Commit the pending queue change alone on top of origin/master and push it;
    True once origin/master holds it. The change stays pending on failure."""
    pending = state.get("pending") or {}
    add, retire = pending.get("add", []), set(pending.get("retire", ()))
    if not add and not retire:
        return True
    if not cfg.publish:
        say("not publishing (--no-publish): the change stays pending in state.json")
        return False
    wt = cfg.worktree
    for attempt in range(1, cfg.push_tries + 1):
        tip = fetch_tip(cfg)
        items = remote_queue(cfg)
        have = {i["id"] for i in items}
        added = [i for i in add if i["id"] not in have]
        retired = [i for i in items if i["id"] in retire]
        if not added and not retired:
            state["pending"] = {}
            say("queue: origin/master already holds the change")
            return True
        cfg.prepare(cfg, tip)
        write_queue(wt / QUEUE, [i for i in items if i["id"] not in retire] + added)
        git(wt, "add", QUEUE)
        if added:
            first = added[0]
            subject = (f"Record a red master: {', '.join(first['checks'])} since {first['bad_sha'][:10]}"
                       + (f" (+{len(added) - 1})" if len(added) > 1 else "") + " (master_verify)")
        else:
            subject = f"Retire {len(retired)} master_verify item(s): their checks pass at {tip[:10]}"
        body = [f"{i['bad_sha'][:10]} {', '.join(i['checks'])}: {i['subject']} ({i['author']})" for i in added]
        body += [f"retired {i['bad_sha'][:10]} {', '.join(i['checks'])}" for i in retired]
        message = subject + "\n\n" + "\n".join(body) + (
            "\n\nWritten by tools/master_verify.py (the post-push backstop); "
            "tools/repair_queue.py repair serves its items first.\n")
        git(wt, "-c", "core.hooksPath=.githooks", "commit", "-q", "-m", message)
        wait_push_clock(cfg)
        say(f"queue: pushing ({len(added)} added, {len(retired)} retired), attempt {attempt}")
        output = push(cfg, attempt)
        fetch_tip(cfg)
        now = {i["id"] for i in remote_queue(cfg)}
        if all(i["id"] in now for i in add) and not now & retire:
            state["pending"] = {}
            if cfg.push_clock:
                Path(cfg.push_clock).write_text(f"{int(time.time())}\n")
            say("queue: published")
            return True
        say(f"queue: not on {cfg.remote}/{cfg.branch} after attempt {attempt}: {output[-400:]}")
    return False


# ---------------------------------------------------------------- one run

def record_run(state, sha, result, complete, note=""):
    entry = {"sha": sha, "time": result.get("time", now_iso()), "duration": result.get("duration", 0),
             "green": result["verdict"] == "green", "verdict": result["verdict"],
             "checks": result.get("checks", []), "complete": complete}
    if note:
        entry["note"] = note
    state["last_run"] = entry
    state.setdefault("runs", []).append(entry)


def retire_settled(cfg, state, tip, red_checks):
    """Queue retirements for items whose bad commit the tip contains and whose
    checks are all green at the tip."""
    pending = state.setdefault("pending", {})
    retire = set(pending.get("retire", ()))
    kept_adds = []
    for item in open_items(cfg, state):
        if set(item["checks"]) & set(red_checks) or not is_ancestor(cfg, item["bad_sha"], tip):
            continue
        if any(a["id"] == item["id"] for a in pending.get("add", [])):
            continue
        retire.add(item["id"])
    for item in pending.get("add", []):
        if set(item["checks"]) & set(red_checks) or not is_ancestor(cfg, item["bad_sha"], tip):
            kept_adds.append(item)
    pending["add"], pending["retire"] = kept_adds, sorted(retire)
    if retire:
        say(f"queue: retiring {', '.join(sorted(retire))} (green at {tip[:10]})")


def handle_red(cfg, state, tip, result):
    """Bisect the checks red at TIP that no open item covers; queue an item per first
    bad commit. Returns the item ids queued."""
    covered = set()
    for item in open_items(cfg, state):
        if is_ancestor(cfg, item["bad_sha"], tip):
            covered |= set(item["checks"])
    remaining = [c for c in result["checks"] if c not in covered]
    if not remaining:
        say(f"still red, already queued: {', '.join(result['checks'])}")
        return []
    green, red = state.get("last_green"), state.get("last_red")
    queued = []
    while remaining:
        good = None
        if red and is_ancestor(cfg, red["sha"], tip) and not set(red["checks"]) & set(remaining):
            good = red["sha"]
        elif green and is_ancestor(cfg, green["sha"], tip):
            good = green["sha"]
        hi, note = tip, ""
        if good is None:
            say(f"no green commit known for {', '.join(remaining)}: probing ancestors")
            good, hi, error = find_good(cfg, state, tip, remaining)
            if error is not None:
                raise Unsettled(f"a probe ended without a verdict ({', '.join(error['checks'])})")
        if good is None:
            first, last_good, exact = hi, "", False
            note = f"no commit within {cfg.probe_limit} first-parent probes passes these checks"
        else:
            say(f"bisecting {good[:10]}..{hi[:10]} for {', '.join(remaining)}")
            first, last_good, exact, error = bisect(cfg, state, good, hi, remaining)
            if error is not None:
                raise Unsettled(f"a bisect step ended without a verdict ({', '.join(error['checks'])})")
        confirm(cfg, state, first, last_good if exact else "", remaining)
        at_first = state["verdicts"].get(first, result)
        labels = [c for c in remaining if c in at_first.get("checks", ())] or list(remaining)
        item = make_item(cfg, state, tip, first, last_good, exact, labels, note)
        state.setdefault("pending", {}).setdefault("add", []).append(item)
        queued.append(item["id"])
        say(f"queued {item['id']}: {', '.join(labels)} red since {first[:10]} ({item['author']}: "
            f"{item['subject'][:60]})" + ("" if exact else " [inexact]"))
        remaining = [c for c in remaining if c not in labels]
    return queued


def run_once(cfg):
    """(exit code, message) of one check of origin/master's tip."""
    cfg.base.mkdir(parents=True, exist_ok=True)
    handle = try_lock(cfg.base / "run.lock")
    if handle is None:
        info = holder(cfg)
        return 0, (f"a run is in progress (pid {info.get('pid', '?')}, {info.get('phase', '?')} "
                   f"{str(info.get('sha', ''))[:10]} since {info.get('started', '?')})")
    state = None
    try:
        set_phase(cfg, phase="starting", started=now_iso())
        state = load_state(cfg)
        return check_tip(cfg, state)
    except Deferred as error:
        return 0, f"deferred: {error}"
    except (GitError, OSError, subprocess.CalledProcessError) as error:
        return 2, f"error: {error}"
    finally:
        if state is not None:
            save_state(cfg, state)
        (cfg.base / "run.json").unlink(missing_ok=True)
        unlock(handle)


def check_tip(cfg, state):
    pending = state.get("pending") or {}
    if pending.get("add") or pending.get("retire"):
        publish(cfg, state)             # a change an earlier run could not push goes first
        save_state(cfg, state)
    tip = fetch_tip(cfg)
    last = state.get("last_run") or {}
    if last.get("sha") == tip and last.get("verdict") in ("green", "red") and last.get("complete"):
        return (1 if last["verdict"] == "red" else 0), f"{tip[:10]} already checked: {last['verdict']}"
    if last.get("complete") and last.get("verdict") in ("green", "red") and only_queue_changed(
            cfg, last["sha"], tip):
        # This tool's own queue commits: the gate reads nothing they change.
        carried = dict(last, sha=tip, time=now_iso(), duration=0, note=f"carried from {last['sha'][:10]}")
        state["last_run"] = carried
        state.setdefault("runs", []).append(carried)
        if carried["green"]:
            state["last_green"] = {"sha": tip, "time": carried["time"], "duration": 0, "green": True,
                                   "receipt": False, "carried_from": last["sha"]}
        return (0 if carried["green"] else 1), (f"{tip[:10]} {last['verdict']} (carried from "
                                                 f"{last['sha'][:10]}: only {QUEUE} changed)")
    others = cfg.busy()
    if others:
        return 0, ("deferred: another full gate is running on this machine: "
                   + "; ".join(f"pid {pid} {line[:100]}" for pid, line in others))
    started = time.time()
    result = run_gate(cfg, tip, state, "tip", keep=True)
    if result["verdict"] == "error":
        record_run(state, tip, result, complete=False)
        return 2, f"{tip[:10]}: no verdict ({', '.join(result['checks'])}); see {result['log']}"
    if result["verdict"] == "green":
        receipt = False
        if result.get("tmp"):           # a cached verdict kept no tool list: no receipt
            receipt, text = cfg.record_receipt(cfg, tip, Path(result["tmp"]))
            shutil.rmtree(result["tmp"], ignore_errors=True)
            if not receipt:
                say(f"receipt not recorded: {text[-300:]}")
        state["last_green"] = {"sha": tip, "time": result["time"], "duration": result["duration"],
                               "green": True, "receipt": receipt}
        state.pop("last_red", None)
        retire_settled(cfg, state, tip, [])
        record_run(state, tip, result, complete=True)
        publish(cfg, state)
        return 0, f"{tip[:10]} green in {result['duration']} s"
    try:
        retire_settled(cfg, state, tip, result["checks"])
        queued = handle_red(cfg, state, tip, result)
    except Deferred:
        record_run(state, tip, result, complete=False, note="bisect deferred")
        raise
    except Unsettled as error:
        record_run(state, tip, result, complete=False, note=str(error))
        return 2, f"{tip[:10]} red ({', '.join(result['checks'])}), no item yet: {error}; retried next run"
    state["last_red"] = {"sha": tip, "time": result["time"], "checks": result["checks"]}
    record_run(state, tip, result, complete=True, note=f"queued {', '.join(queued)}" if queued else "")
    published = publish(cfg, state)
    return 1, (f"{tip[:10]} red ({', '.join(result['checks'])}); "
               + (f"queued {', '.join(queued)}" if queued else "already queued")
               + ("" if published else "; the queue change is pending")
               + f"; {round(time.time() - started)} s")


def status(cfg):
    lines = [f"master_verify: {cfg.base}"]
    handle = try_lock(cfg.base / "run.lock") if cfg.base.is_dir() else None
    if cfg.base.is_dir() and handle is None:
        info = holder(cfg)
        lines.append(f"  running: pid {info.get('pid', '?')} {info.get('phase', '?')} "
                     f"{str(info.get('sha', ''))[:10]} since {info.get('started', '?')}")
    else:
        if handle is not None:
            unlock(handle)
        lines.append("  idle")
    state = load_state(cfg)
    for key in ("last_run", "last_green", "last_red"):
        entry = state.get(key)
        if entry:
            lines.append(f"  {key.replace('_', ' ')}: {entry['sha'][:10]} {entry.get('verdict', '')} "
                         f"{entry.get('time', '')} {entry.get('duration', '')} s "
                         + ", ".join(entry.get("checks", [])))
    items = remote_queue(cfg)
    lines.append(f"  open items on {cfg.remote}/{cfg.branch} ({QUEUE}): {len(items)}")
    for item in items:
        lines.append(f"    {item['id']} {', '.join(item['checks'])}: {item['subject'][:60]} ({item['author']})")
    pending = state.get("pending") or {}
    if pending.get("add") or pending.get("retire"):
        lines.append(f"  pending publish: {len(pending.get('add', []))} added, "
                     f"{len(pending.get('retire', []))} retired")
    try:
        others = cfg.busy()
    except (OSError, subprocess.CalledProcessError) as error:
        others = [("?", f"cannot list processes: {error}")]
    for pid, line in others:
        lines.append(f"  other full gate: pid {pid} {line[:120]}")
    return "\n".join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--once", action="store_true", help="check origin/master's tip once")
    mode.add_argument("--watch", action="store_true", help="check every --interval seconds")
    mode.add_argument("--status", action="store_true", help="the last verdicts, open items and the lock")
    ap.add_argument("--interval", type=float, default=300, help="seconds between --watch checks")
    ap.add_argument("--no-publish", action="store_true", help="keep queue changes pending in state.json")
    ap.add_argument("--push-cmd", help="push with this command instead ({worktree} and {log} are filled in)")
    ap.add_argument("--push-clock", help="a file holding the account's last push time (epoch seconds)")
    ap.add_argument("--busy-wait", type=float, default=1800,
                    help="seconds a bisect step waits for another full gate before deferring")
    ap.add_argument("--probe-limit", type=int, default=5,
                    help="ancestor probes when no green commit is known")
    args = ap.parse_args(argv)
    pool = int(os.environ.get("BUILD_POOL") or POOL)
    cfg = Config(pool=pool, publish=not args.no_publish, push_cmd=args.push_cmd,
                 push_clock=Path(args.push_clock) if args.push_clock else None,
                 busy_wait=args.busy_wait, probe_limit=args.probe_limit)
    if args.status:
        print(status(cfg))
        return 0
    while True:
        started = time.time()
        code, message = run_once(cfg)
        say(f"{message} [{round(time.time() - started)} s]")
        if not args.watch:
            return code
        try:
            time.sleep(max(0.0, args.interval))
        except KeyboardInterrupt:
            return 0


if __name__ == "__main__":
    sys.exit(main())
