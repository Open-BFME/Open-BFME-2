"""master_verify, the post-push backstop: a green tip is recorded, a red tip is bisected
to its first bad commit and queued for repair_queue (served first), the lock allows one
run, another full gate on the machine defers it, and a gate without a verdict is never
bisected. A fake gate judges a toy history pushed to a bare origin."""
import importlib
import json
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import master_verify as M  # noqa: E402

# The fake gate: red with the full gate's own summary line, one check per `bad*` file
# (its text names the check), while such a file exists.
GATE = """import pathlib, sys
log = pathlib.Path(sys.argv[1])
log.write_text(log.read_text() + "x") if log.exists() else log.write_text("x")
if pathlib.Path("crash").exists() and not log.with_name("crash-off").exists():
    raise RuntimeError("the gate itself broke")
if pathlib.Path("flaky").exists() and not log.with_name("flaky-done").exists():
    log.with_name("flaky-done").write_text("1")       # fails once, as under load
    print("\\nFULL GATE: FAIL \\u2014 1 red: dir32 consistency")
    sys.exit(1)
red = [p.read_text().strip() for p in sorted(pathlib.Path(".").glob("bad*"))]
if red:
    print("  FAIL ?f@@YAXXZ (Code/Game/Thing.cpp)")
    print("    dir32: two addresses")
    print("\\nFULL GATE: FAIL \\u2014 %d red: %s" % (len(red), ", ".join(red)))
    sys.exit(1)
print("\\nFULL GATE: OK \\u2014 every check green")
"""


def git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, check=True).stdout.strip()


@pytest.fixture
def toy(tmp_path, monkeypatch):
    for key, value in (("GIT_AUTHOR_NAME", "Seat"), ("GIT_AUTHOR_EMAIL", "seat@example.invalid"),
                       ("GIT_COMMITTER_NAME", "Seat"), ("GIT_COMMITTER_EMAIL", "seat@example.invalid")):
        monkeypatch.setenv(key, value)
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", "-b", "master", str(origin))
    seat = tmp_path / "seat"
    git(tmp_path, "clone", "-q", str(origin), str(seat))
    git(seat, "checkout", "-q", "-b", "master")
    (seat / "gate.py").write_text(GATE)
    git(seat, "add", "gate.py")
    git(seat, "commit", "-q", "-m", "gate")
    git(seat, "push", "-q", "origin", "master")
    return seat


def commit(seat, name, text=None, message=None):
    path = seat / name
    if text is None:
        path.unlink()
        git(seat, "rm", "-q", name)
    else:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
        git(seat, "add", name)
    git(seat, "commit", "-q", "-m", message or f"edit {name}")
    return git(seat, "rev-parse", "HEAD")


def push(seat):
    git(seat, "push", "-q", "origin", "master")
    return git(seat, "rev-parse", "HEAD")


def prepare(cfg, sha):
    if not (cfg.worktree / ".git").exists():
        git(cfg.root, "worktree", "add", "-q", "--detach", str(cfg.worktree), sha)
    else:
        git(cfg.worktree, "checkout", "-q", "-f", "--detach", sha)


def config(seat, tmp_path, receipts, **kw):
    calls = tmp_path / "gate_calls"

    def stages(cfg, sha, tmp):
        return [M.Stage("full gate", [sys.executable, "gate.py", str(calls)], M.FULL_MARK)]

    def record(cfg, sha, tmp):
        receipts.append(sha)
        return True, ""

    kw.setdefault("busy", lambda: [])
    kw.setdefault("gate_lock", tmp_path / "machine" / "full-gate.lock")    # never this PC's real one
    return M.Config(root=seat, base=tmp_path / "mv", stages=stages, prepare=prepare,
                    record_receipt=record, **kw)


def gate_calls(tmp_path):
    path = tmp_path / "gate_calls"
    return len(path.read_text()) if path.exists() else 0


def origin_queue(seat):
    git(seat, "fetch", "-q", "origin")
    shown = subprocess.run(["git", "show", f"origin/master:{M.QUEUE}"], cwd=seat, capture_output=True, text=True)
    return json.loads(shown.stdout)["items"] if shown.returncode == 0 else []


def test_a_green_tip_is_recorded_once(toy, tmp_path):
    receipts = []
    cfg = config(toy, tmp_path, receipts)
    tip = git(toy, "rev-parse", "HEAD")
    code, message = M.run_once(cfg)
    assert code == 0 and "green" in message
    state = json.loads((cfg.base / "state.json").read_text())
    green = state["last_green"]
    assert (green["sha"], green["green"]) == (tip, True)
    assert isinstance(green["duration"], int) and green["time"].endswith("Z")
    assert receipts == [tip]                      # the receipt store learns the commit
    assert M.run_once(cfg) == (0, f"{tip[:10]} already checked: green")
    assert gate_calls(tmp_path) == 1
    assert origin_queue(toy) == []                # nothing to publish


def test_a_red_tip_bisects_to_its_first_bad_commit_and_a_fix_retires_it(toy, tmp_path):
    receipts = []
    cfg = config(toy, tmp_path, receipts)
    assert M.run_once(cfg)[0] == 0                # the last green commit
    commits = [commit(toy, f"Code/Game/f{n}.cpp", str(n)) for n in range(5)]
    bad = commit(toy, "bad", "dir32 consistency\n", "Break DIR32 across files")
    commits += [bad] + [commit(toy, f"Code/Game/g{n}.cpp", str(n)) for n in range(6)]
    tip = push(toy)
    before = gate_calls(tmp_path)
    code, message = M.run_once(cfg)
    assert code == 1, message
    # the tip, a bisect over 12 commits (not a walk), then the first bad and its parent again
    assert gate_calls(tmp_path) - before <= 7
    (item,) = origin_queue(toy)
    assert item["bad_sha"] == bad and item["exact"] is True
    assert item["checks"] == ["dir32 consistency"]
    assert item["author"] == "Seat <seat@example.invalid>" and "Seat" in item["suggested_owner"]
    assert item["subject"] == "Break DIR32 across files" and item["files"] == ["bad"]
    assert "FULL GATE: FAIL" in item["output"] and item["named_sources"] == ["Code/Game/Thing.cpp"]
    assert item["tip_sha"] == tip and item["good_sha"] == commits[4]
    state = json.loads((cfg.base / "state.json").read_text())
    assert state["last_run"]["sha"] == tip and state["last_run"]["green"] is False
    assert state.get("pending") == {} and receipts == [receipts[0]]   # no receipt for red
    # still red with more commits: the open item covers it, nothing is bisected again
    git(toy, "pull", "-q", "--rebase", "origin", "master")
    commit(toy, "Code/Game/h.cpp", "1")
    push(toy)
    before = gate_calls(tmp_path)
    code, message = M.run_once(cfg)
    assert code == 1 and "already queued" in message and gate_calls(tmp_path) - before == 1
    # the fix lands: the item leaves the queue
    commit(toy, "bad", None, "Fix DIR32")
    fixed = push(toy)
    assert M.run_once(cfg)[0] == 0
    assert origin_queue(toy) == []
    assert json.loads((cfg.base / "state.json").read_text())["last_green"]["sha"] == fixed


def test_without_a_known_green_commit_ancestors_are_probed(toy, tmp_path):
    cfg = config(toy, tmp_path, [])
    for n in range(3):
        commit(toy, f"Code/a{n}.cpp", str(n))
    bad = commit(toy, "bad", "functions\n", "Break a row")
    for n in range(4):
        commit(toy, f"Code/b{n}.cpp", str(n))
    push(toy)
    assert M.run_once(cfg)[0] == 1
    (item,) = origin_queue(toy)
    assert (item["bad_sha"], item["exact"], item["checks"]) == (bad, True, ["functions"])


def test_the_lock_allows_one_run(toy, tmp_path):
    cfg = config(toy, tmp_path, [])
    cfg.base.mkdir(parents=True)
    held = subprocess.Popen(
        [sys.executable, "-c", "import sys; sys.path.insert(0, sys.argv[1]); import master_verify as M; "
         "from pathlib import Path; h = M.try_lock(Path(sys.argv[2])); print('held' if h else 'free', flush=True); "
         "sys.stdin.read()", str(TOOLS), str(cfg.base / "run.lock")],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    try:
        assert held.stdout.readline().strip() == "held"
        code, message = M.run_once(cfg)
        assert code == 0 and "a run is in progress" in message
        assert gate_calls(tmp_path) == 0
    finally:
        held.stdin.close()
        held.wait(timeout=30)
    assert "green" in M.run_once(cfg)[1]


def test_another_full_gate_on_the_machine_defers_the_run(toy, tmp_path):
    cfg = config(toy, tmp_path, [], busy=lambda: [(4242, "py -3 tools/build.py")])
    code, message = M.run_once(cfg)
    assert code == 0 and message.startswith("deferred") and "4242" in message
    assert gate_calls(tmp_path) == 0
    assert M.full_gate_kind(["py", "-3", "tools/build.py"]) == "tools/build.py (full)"
    assert M.full_gate_kind(["C:\\Python\\python.exe", "C:\\wt\\tools\\build.py"]) == "tools/build.py (full)"
    assert M.full_gate_kind(["python3", "tools/build.py", "Code/Game/Thing.cpp"]) is None
    assert M.full_gate_kind(["python3", "tools/full_gate_receipt.py", "cross-checks", "--since", "x"])
    assert M.full_gate_kind(["python3", "tools/full_gate_receipt.py", "find", "x"]) is None


def test_a_gate_without_a_verdict_is_retried_never_bisected(toy, tmp_path):
    cfg = config(toy, tmp_path, [])
    assert M.run_once(cfg)[0] == 0
    commit(toy, "crash", "1")
    push(toy)
    code, message = M.run_once(cfg)
    assert code == 2 and "no verdict" in message
    assert origin_queue(toy) == [] and gate_calls(tmp_path) == 2
    assert M.run_once(cfg)[0] == 2 and gate_calls(tmp_path) == 3     # retried, not cached


def test_an_unpublished_item_stays_pending_and_goes_first_next_time(toy, tmp_path):
    cfg = config(toy, tmp_path, [], publish=False)
    assert M.run_once(cfg)[0] == 0
    bad = commit(toy, "bad", "dir32 consistency\n")
    push(toy)
    assert M.run_once(cfg)[0] == 1
    assert origin_queue(toy) == []
    assert json.loads((cfg.base / "state.json").read_text())["pending"]["add"][0]["bad_sha"] == bad
    cfg.publish = True
    calls = gate_calls(tmp_path)
    code, message = M.run_once(cfg)
    assert code == 1 and "carried from" in message      # its own queue commit is not gated again
    assert [i["bad_sha"] for i in origin_queue(toy)] == [bad] and gate_calls(tmp_path) == calls


def test_repair_queue_serves_master_regressions_first(tmp_path, monkeypatch, capsys):
    import next_work
    rev = tmp_path / "reverse"
    rev.mkdir()
    (rev / "functions.csv").write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                                       "?a@Loco@@QAEXXZ,,0x00001000,64,Code/Loco.cpp,matched,\n", newline="\n")
    (rev / "gate_baseline.txt").write_text("tail 0x00001000 ?a@Loco@@QAEXXZ\n", newline="\n")
    item = {"id": "abc", "bad_sha": "a" * 40, "subject": "Break DIR32", "author": "Seat <s@x>",
            "suggested_owner": "Seat <s@x>, who pushed aaaaaaaaaa", "checks": ["dir32 consistency"],
            "output": "DIR32 consistency: FAIL 1 NEW", "files": ["Code/Loco.cpp", "reverse/functions.csv"],
            "named_sources": [], "found": "2026-10-29T00:00:00Z"}
    M.write_queue(rev / "master_verify_queue.json", [item])
    monkeypatch.setenv("REPAIR_ROOT", str(tmp_path))
    import repair_queue
    rq = importlib.reload(repair_queue)
    monkeypatch.delenv("REPAIR_ROOT")
    try:
        items = rq.all_repair_items()
        assert [i["check"] for i in items] == ["master-red", "tail"]
        assert items[0]["claim"] == ["file:Code/Loco.cpp"] and items[0]["urgent"] is True
        assert "dir32 consistency red on master since aaaaaaaaaa" in items[0]["why"]
        assert rq.main(["repair"]) == 0
        out = capsys.readouterr().out
        assert out.startswith("1 master regression(s)")
        assert out.index("master-red") < out.index("tail 0x00001000")

        class Args:
            claim = False
        monkeypatch.setattr(next_work, "weighted_choice", lambda pool: pool[-1])
        picked = next_work.draw_debt("repair", items[::-1], items, Args, [], 0)
        assert picked["candidate"]["check"] == "master-red"
    finally:
        importlib.reload(repair_queue)


def test_an_already_checked_red_tip_still_exits_red(toy, tmp_path):
    cfg = config(toy, tmp_path, [], publish=False)    # no queue commit: the tip stays put
    assert M.run_once(cfg)[0] == 0
    commit(toy, "bad", "dir32 consistency\n")
    tip = push(toy)
    assert M.run_once(cfg)[0] == 1
    assert M.run_once(cfg) == (1, f"{tip[:10]} already checked: red")


def test_a_bisect_that_hits_a_gate_without_a_verdict_publishes_nothing_and_retries(toy, tmp_path):
    cfg = config(toy, tmp_path, [])
    assert M.run_once(cfg)[0] == 0
    commit(toy, "Code/a.cpp", "1")
    commit(toy, "crash", "1")                     # the bisect's first step crashes the gate
    commit(toy, "crash", None)
    commit(toy, "bad", "dir32 consistency\n")
    tip = push(toy)
    code, message = M.run_once(cfg)
    assert code == 2 and "no verdict" in message, message
    assert origin_queue(toy) == []
    state = json.loads((cfg.base / "state.json").read_text())
    assert state["last_run"]["sha"] == tip and state["last_run"]["complete"] is False
    assert not (state.get("pending") or {}).get("add")
    calls = gate_calls(tmp_path)
    assert M.run_once(cfg)[0] == 2 and gate_calls(tmp_path) > calls       # retried
    assert origin_queue(toy) == []


def test_a_transient_failure_is_never_blamed(toy, tmp_path):
    cfg = config(toy, tmp_path, [])
    assert M.run_once(cfg)[0] == 0
    commit(toy, "Code/a.cpp", "1")
    commit(toy, "flaky", "1")                     # the bisect's first step fails once
    commit(toy, "flaky", None)
    bad = commit(toy, "bad", "dir32 consistency\n", "Break DIR32 for real")
    commit(toy, "Code/b.cpp", "1")
    push(toy)
    code, message = M.run_once(cfg)
    assert code == 2 and "did not reproduce" in message, message
    assert origin_queue(toy) == []                # nothing published on one failure
    assert M.run_once(cfg)[0] == 1
    (item,) = origin_queue(toy)
    assert (item["bad_sha"], item["exact"]) == (bad, True)


def test_a_gate_holding_the_machine_lock_defers_the_run(toy, tmp_path):
    """Another clone's gate the process snapshot missed: the machine lock still keeps
    two full gates from overlapping (tools/full_gate_lock.py)."""
    cfg = config(toy, tmp_path, [], busy_wait=0)
    cfg.gate_lock = tmp_path / "machine" / "full-gate.lock"
    held = subprocess.Popen(
        [sys.executable, "-c", "import sys; sys.path.insert(0, sys.argv[1]); import full_gate_lock as L; "
         "got = L.acquire(0, path=sys.argv[2], note='another clone'); print('held' if got else 'busy', flush=True); "
         "sys.stdin.read(); L.release(got)", str(TOOLS), str(cfg.gate_lock)],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    try:
        assert held.stdout.readline().strip() == "held"
        code, message = M.run_once(cfg)
        assert code == 0 and message.startswith("deferred") and "another clone" in message, message
        assert gate_calls(tmp_path) == 0
    finally:
        held.stdin.close()
        held.wait(timeout=30)
    assert "green" in M.run_once(cfg)[1]


def test_no_item_is_published_until_every_search_for_the_tip_settles(toy, tmp_path):
    """Two checks red at the tip, the second one's search without a verdict: the first
    search's item waits for it, and a later complete run publishes both."""
    cfg = config(toy, tmp_path, [])
    assert M.run_once(cfg)[0] == 0
    first = commit(toy, "bad", "dir32 consistency\n", "Break DIR32")
    for n in range(4):
        commit(toy, f"Code/a{n}.cpp", str(n))
    commit(toy, "crash", "1")                     # only the second search steps here
    commit(toy, "crash", None)
    second = commit(toy, "bad2", "functions\n", "Break a row")
    commit(toy, "Code/z.cpp", "1")
    push(toy)
    for _ in range(2):
        code, message = M.run_once(cfg)
        assert code == 2 and "no verdict" in message, message
        assert origin_queue(toy) == []
        assert not (json.loads((cfg.base / "state.json").read_text()).get("pending") or {}).get("add")
    (tmp_path / "crash-off").write_text("1")
    assert M.run_once(cfg)[0] == 1
    found = {i["bad_sha"]: i["checks"] for i in origin_queue(toy)}
    assert found == {first: ["dir32 consistency"], second: ["functions"]}
