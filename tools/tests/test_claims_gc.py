"""Stage 2 item 4: claim GC, paced retries and fewer pushes per task.

Every fixture is a local bare repository (test_claims.hosts): no test reaches a
network, this checkout's origin or this machine's real pacer file.
"""
import random
import json
import subprocess
import sys
import threading
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(Path(__file__).resolve().parent))

import claims  # noqa: E402
from test_claims import _commit_ledger, _git, _verified, hosts, own_sleep  # noqa: E402,F401


def _remote_refs(origin, prefix="refs/"):
    out = subprocess.run(["git", "for-each-ref", "--format=%(refname) %(objectname)", prefix],
                         cwd=origin, check=True, capture_output=True, text=True).stdout
    return dict(line.split() for line in out.splitlines())


def _pushes(monkeypatch, root=None, before=None):
    """Record every claims push from `root`; `before(args)` runs just ahead of one."""
    real = claims._git
    seen = []

    def git(*args, **kwargs):
        if args[:1] == ("push",) and kwargs.get("cwd") in (None, root):
            seen.append(args)
            if before:
                before(args)
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    return seen


def _stale(keys, hours=3, who=None):
    """Claim `keys` with a record that expired `hours` ago (well past the grace)."""
    result = claims.claim(keys, ttl_hours=-hours, who=who)
    assert result.claimed == claims._ints(keys)
    return result


# ---- (a) gc -----------------------------------------------------------------

@pytest.mark.parametrize("namespace", ["refs/claims/", "refs/heads/claims/"])
def test_gc_deletes_only_refs_expired_past_the_grace(hosts, monkeypatch, namespace):
    hosts("a")
    monkeypatch.setattr(claims, "NS", namespace)
    _stale([0x100, 0x200, "file:Code/Old.cpp"])
    claims.claim([0x300], ttl_hours=-0.5)                     # expired 30 min ago: inside the grace
    claims.claim([0x400, "file:Code/Live.cpp"])               # live
    deleted, kept = claims.gc(max_per_minute=0)
    assert deleted == [0x100, 0x200, claims.key_of("file:Code/Old.cpp")] and kept == []
    left = _remote_refs(hosts.origin, namespace)
    assert sorted(left) == sorted(claims.ref_of(k) for k in (0x300, 0x400, claims.key_of("file:Code/Live.cpp")))


def test_gc_grace_has_a_floor_against_clock_skew(hosts):
    hosts("a")
    claims.claim([0x300], ttl_hours=-0.75)                    # 45 min ago
    assert claims.gc(grace_minutes=0, max_per_minute=0) == ([], [])
    assert claims.ref_of(0x300) in _remote_refs(hosts.origin)


def test_gc_keeps_a_claim_renewed_during_the_collection(hosts, monkeypatch):
    root = hosts("a")
    stale = _stale([0x100, 0x200])
    renewed = {}

    def renew_first(args):
        if "--atomic" in args and any(a.startswith(":") for a in args) and not renewed:
            # the owner's heartbeat lands between gc's read and its push
            got, lost = claims.renew({0x100: stale.tokens[0x100]}, root=root)
            assert not lost
            renewed.update(got)
    pushes = _pushes(monkeypatch, root, renew_first)
    deleted, kept = claims.gc(max_per_minute=0)
    assert deleted == [0x200] and kept == [0x100]
    refs = _remote_refs(hosts.origin, "refs/claims/")
    assert refs == {claims.ref_of(0x100): renewed[0x100]}      # the renewal, untouched
    assert claims.active()[0x100]["expires"] > time.time()
    gc_pushes = [p for p in pushes if any(a.startswith(":") for a in p)]
    assert len(gc_pushes) == 2                                 # refused whole, retried without it


def test_gc_keeps_a_claim_taken_over_during_the_collection(hosts, monkeypatch):
    peer = hosts("b")
    root = hosts("a")
    _stale([0x100, 0x200])
    taken = []

    def take_over(args):
        if "--atomic" in args and any(a.startswith(":") for a in args) and not taken:
            taken.append(claims.claim([0x200], root=peer, who="b").claimed)
    _pushes(monkeypatch, root, take_over)
    assert claims.gc(max_per_minute=0) == ([0x100], [0x200])
    assert taken == [[0x200]]
    assert claims.active()[0x200]["owner"] == "b"


def test_gc_never_touches_another_namespace(hosts, monkeypatch):
    hosts("a")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/")
    _stale([0x100])
    claims.claim([0x200])
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    _stale([0x300])
    before = _remote_refs(hosts.origin, "refs/heads/claims/")
    assert claims.gc(max_per_minute=0) == ([0x300], [])
    assert _remote_refs(hosts.origin, "refs/heads/claims/") == before
    assert len(before) == 2


def test_gc_batches_rate_limits_and_respects_max(hosts, monkeypatch):
    root = hosts("a")
    _stale([0x100 + i for i in range(7)])
    pushes = _pushes(monkeypatch, root)
    sleeps = []
    own_sleep(monkeypatch, sleeps.append)
    deleted, kept = claims.gc(limit=5, batch=2, max_per_minute=60)
    assert deleted == [0x100 + i for i in range(5)] and not kept
    assert len(pushes) == 3                                    # 2 + 2 + 1, one atomic push each
    assert all("--atomic" in p for p in pushes)
    assert all(1.0 < s <= 2.0 for s in sleeps) and len(sleeps) == 2     # 2 refs at 60/min
    assert len(_remote_refs(hosts.origin, "refs/claims/")) == 2


def test_gc_opportunistic_takes_a_random_slice_once_per_interval(hosts, monkeypatch):
    root = hosts("a")
    _stale([0x100 + i for i in range(6)])
    monkeypatch.setenv("BFME_CLAIM_GC", "on")
    monkeypatch.setattr(claims, "GC_SLICE", 2)
    pushes = _pushes(monkeypatch, root)
    first = claims.gc_opportunistic(rng=random.Random(1))
    assert len(first) == 2 and len(pushes) == 1
    assert claims.gc_opportunistic() == []                     # this host collected recently
    assert len(pushes) == 1
    monkeypatch.setattr(claims, "GC_EVERY_SECONDS", 0)
    second = claims.gc_opportunistic(rng=random.Random(2))
    assert len(second) == 2 and not set(first) & set(second)
    assert len(_remote_refs(hosts.origin, "refs/claims/")) == 2


def test_gc_command(hosts, capsys):
    hosts("a")
    _stale([0x100])
    claims.claim([0x200])
    assert claims.main(["gc", "--dry-run"]) == 0
    output = capsys.readouterr().out
    assert "would delete 1" in output and "0x00000100" in output
    assert claims.main(["gc", "--max-per-minute", "0"]) == 0
    assert "deleted 1" in capsys.readouterr().out
    assert list(claims.active()) == [0x200]


@pytest.mark.parametrize("options", [
    {"grace_minutes": float("nan")}, {"grace_minutes": float("inf")},
    {"max_per_minute": float("nan")}, {"max_per_minute": -1},
    {"batch": 0}, {"limit": -1}, {"sample": -1},
])
def test_gc_rejects_invalid_options_before_writes(hosts, options):
    hosts("a")
    with pytest.raises(ValueError):
        claims.gc(**options)
    assert _remote_refs(hosts.origin, "refs/claims/") == {}


def test_gc_keeps_unreadable_and_nonfinite_expiries(hosts):
    root = hosts("a")
    tree = claims._git("mktree", input_text="", cwd=root).stdout.strip()
    for i, record in enumerate(({}, [], {"expires": "old"}, {"expires": True},
                                {"expires": float("nan")}, {"expires": -float("inf")})):
        sha = _git(root, "commit-tree", tree, "-m", json.dumps(record)).strip()
        _git(root, "push", "-q", "origin", f"{sha}:{claims.ref_of(0x100 + i)}")
    before = _remote_refs(hosts.origin)
    assert claims.gc(max_per_minute=0) == ([], [])
    assert _remote_refs(hosts.origin) == before


def test_gc_can_be_run_by_a_different_seat(hosts):
    hosts("b")
    _stale([0x100, "file:Code/old.cpp"])
    claims.claim([0x200])
    hosts("a")
    assert claims.gc(max_per_minute=0) == ([0x100, claims.file_key("Code/old.cpp")], [])
    assert claims.active()[0x200]["owner"] == "b"


def test_gc_long_scopes_stay_within_windows_command_line_budget():
    keys = ["class/" + "C" * 180 + str(i) for i in range(150)]
    found = dict.fromkeys(keys, "a" * 40)
    chunks = list(claims._gc_batches(keys, found, batch=150))
    assert len(chunks) > 1 and sum(map(len, chunks)) == len(keys)
    for chunk in chunks:
        args = ["git", "push", "--atomic", "origin"]
        for key, sha in chunk.items():
            ref = claims.ref_of(key)
            args.extend([f"--force-with-lease={ref}:{sha}", f":{ref}"])
        assert len(subprocess.list2cmdline(args).encode("utf-16-le")) // 2 < 24500


# ---- (b) backoff and the host pacer ----------------------------------------

def test_backoff_is_jittered_exponential_and_capped(monkeypatch):
    monkeypatch.setattr(claims, "BACKOFF_BASE", 0.5)
    rng = random.Random(7)
    for attempt in range(12):
        ceiling = min(30.0, 0.5 * 2 ** attempt)
        draws = [claims._backoff(attempt, rng) for _ in range(200)]
        assert all(0 <= d <= ceiling for d in draws)
        assert max(draws) > 0.8 * ceiling and min(draws) < 0.2 * ceiling   # full jitter
    assert claims._backoff(40, random.Random(1)) <= 30.0
    a = [claims._backoff(3, random.Random(5)) for _ in range(3)]
    assert a == [claims._backoff(3, random.Random(5))] * 3                 # seeded: reproducible


def test_pacer_allows_a_burst_then_spaces_pushes(hosts, monkeypatch):
    root = hosts("a")
    monkeypatch.setenv("BFME_CLAIM_PUSHES_PER_MINUTE", "60")
    monkeypatch.setattr(claims, "PUSH_BURST", 3)
    monkeypatch.setattr(claims.time, "time", lambda: 1000.0)
    monkeypatch.setattr(claims.time, "sleep", lambda s: None)
    waits = [claims._pace(root) for _ in range(6)]
    assert waits == [0.0, 0.0, 0.0, 1.0, 2.0, 3.0]


def test_pacer_serializes_concurrent_pushers(hosts, monkeypatch):
    root = hosts("a")
    monkeypatch.setenv("BFME_CLAIM_PUSHES_PER_MINUTE", "60")
    monkeypatch.setattr(claims, "PUSH_BURST", 1)
    monkeypatch.setattr(claims.time, "time", lambda: 1000.0)
    monkeypatch.setattr(claims.time, "sleep", lambda s: None)
    waits = []
    jobs = [threading.Thread(target=lambda: waits.extend(claims._pace(root) for _ in range(5)))
            for _ in range(4)]
    for job in jobs:
        job.start()
    for job in jobs:
        job.join()
    assert sorted(waits) == [float(i) for i in range(20)]     # no slot lost or shared


def test_pacer_is_shared_across_processes(hosts, tmp_path):
    roots = [hosts("a"), hosts("b")]
    script = (
        "import sys, os; sys.path.insert(0, sys.argv[1]); import claims; from pathlib import Path;"
        "claims.HOST_DIR = Path(sys.argv[2]); claims.PUSH_BURST = 1;"
        "claims.time.sleep = lambda s: None;"
        "print(sum(claims._pace(sys.argv[3]) > 0 for _ in range(5)))")
    env = dict(__import__("os").environ, BFME_CLAIM_PUSHES_PER_MINUTE="6")
    outs = [subprocess.run([sys.executable, "-c", script, str(TOOLS), str(claims.HOST_DIR), str(root)],
                           env=env, capture_output=True, text=True, check=True).stdout.strip()
            for root in roots]
    assert outs == ["4", "5"]          # the second process inherits the first one's queue


def test_renew_retries_transient_contention_with_exponential_jitter(hosts, monkeypatch):
    root = hosts("a")
    old = claims.claim([0x100])
    real = claims._git
    pushes, delays = [], []

    def git(*args, **kwargs):
        if args[:1] == ("push",):
            pushes.append(args)
            if len(pushes) <= 2:
                return subprocess.CompletedProcess(args, 1, "", "cannot lock ref")
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    own_sleep(monkeypatch, delays.append)
    renewed, lost = claims.renew(old.tokens, root=root)
    assert not lost and len(pushes) == 3
    assert len(delays) == 2 and all(0 <= d <= claims.BACKOFF_BASE * 2 ** i for i, d in enumerate(delays))
    assert _remote_refs(hosts.origin)[claims.ref_of(0x100)] == renewed[0x100]


# ---- (c) pushes per task ----------------------------------------------------

def _task_fixture(a):
    rows = ["?d_00000100@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,gen-dump",
            "?d_00000200@@YAXXZ,,0x00000200,16,Code/y.cpp,matched,gen-dump"]
    _commit_ledger(a, rows, "base", {"Code/x.cpp": "// x\n", "Code/y.cpp": "// y\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    return rows


def test_a_task_costs_one_claim_push_in_steady_state(hosts, monkeypatch):
    a = hosts("a")
    rows = _task_fixture(a)
    claims.settle(defer=True)
    assert claims.acquire([0x100]).claimed == [0x100, claims.file_key("Code/x.cpp")]
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row, rows[1]], "land", {"Code/x.cpp": "void f() {}\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")         # the landing (not a claim push)
    pushes = _pushes(monkeypatch, a)
    # the next pick: settle the landed body and its file lock, then claim the next body
    with claims.pick_snapshot():
        assert claims.settle(defer=True) == [0x100, claims.file_key("Code/x.cpp")]
        assert claims.acquire([0x200]).claimed == [0x200, claims.file_key("Code/y.cpp")]
    assert len(pushes) == 1, pushes                  # was 3: body release, orphan lock, acquire
    assert set(claims.active()) == {0x200, claims.file_key("Code/y.cpp")}
    assert set(_remote_refs(hosts.origin, "refs/claims/")) == {
        claims.ref_of(0x200), claims.ref_of(claims.file_key("Code/y.cpp"))}
    assert claims.pending() == []                    # the push that released it settled it
    assert claims.flush_outbox() == []


def test_releasing_a_body_and_its_file_lock_is_one_push(hosts, monkeypatch):
    a = hosts("a")
    _task_fixture(a)
    claims.acquire([0x100])
    pushes = _pushes(monkeypatch, a)
    assert claims.release_work([0x100]) == [0x100, claims.file_key("Code/x.cpp")]
    assert len(pushes) == 1 and claims.active() == {}
    claims.acquire([0x200])
    assert claims.settle([0x200]) == [0x200, claims.file_key("Code/y.cpp")]   # undeferred: one push
    assert len(pushes) == 3 and claims.active() == {}


def test_forced_cli_release_also_deletes_its_body_and_lock_atomically(hosts, monkeypatch):
    root = hosts("a")
    _task_fixture(root)
    claims.acquire([0x100])
    pushes = _pushes(monkeypatch, root)
    assert claims.main(["release", "0x100", "--force"]) == 0
    assert len(pushes) == 1 and "--atomic" in pushes[0]
    assert claims.active() == {}


def test_landed_cli_release_deletes_its_body_and_lock_atomically(hosts, monkeypatch):
    root = hosts("a")
    rows = _task_fixture(root)
    claims.acquire([0x100])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(root, [row, rows[1]], "land", {"Code/x.cpp": "void f() {}\n"})
    _verified(root, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    _git(root, "push", "-q", "origin", "HEAD:refs/heads/master")
    pushes = _pushes(monkeypatch, root)
    assert claims.main(["release", "--landed"]) == 0
    assert len(pushes) == 1 and "--atomic" in pushes[0]
    assert claims.active() == {} and claims.pending() == []


def test_deferred_releases_flush_when_no_claim_push_follows(hosts, monkeypatch):
    a = hosts("a")
    _task_fixture(a)
    claims.acquire([0x100])
    claims.release([0x100])                                   # leaves the file lock orphaned
    assert claims.settle(defer=True) == [claims.file_key("Code/x.cpp")]
    assert claims.file_key("Code/x.cpp") in claims.active()  # nothing pushed yet
    assert claims.flush_outbox() == [claims.file_key("Code/x.cpp")]
    assert claims.active() == {}


def test_picker_exit_flushes_deferred_releases_without_background_jobs(hosts):
    root = hosts("a")
    _task_fixture(root)
    claims.acquire([0x100])
    script = (
        "import sys; from pathlib import Path; sys.path.insert(0, sys.argv[1]); import claims;"
        "claims.ROOT = Path(sys.argv[2]); claims.settle([0x100], defer=True);"
        "assert claims._OUTBOX")
    subprocess.run([sys.executable, "-c", script, str(TOOLS), str(root)],
                   check=True, capture_output=True, text=True, timeout=60)
    claims.active.cache_clear()
    assert claims.active() == {}


def test_a_reclaimed_file_lock_is_not_deleted_by_the_deferred_release(hosts, monkeypatch):
    a = hosts("a")
    _task_fixture(a)
    _commit_ledger(a, ["?d_00000100@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,gen-dump",
                       "?d_00000200@@YAXXZ,,0x00000200,16,Code/x.cpp,matched,gen-dump"], "same file")
    claims.acquire([0x100])
    claims.release([0x100])
    claims.settle(defer=True)                                 # queues deleting x.cpp's lock
    pushes = _pushes(monkeypatch, a)
    assert claims.acquire([0x200]).claimed == [0x200, claims.file_key("Code/x.cpp")]
    assert len(pushes) == 1
    assert set(claims.active()) == {0x200, claims.file_key("Code/x.cpp")}
    assert claims.flush_outbox() == []


def test_a_stale_deferred_release_never_costs_the_claim(hosts, monkeypatch):
    a = hosts("a")
    _task_fixture(a)
    claims.acquire([0x100])
    claims.release([0x100])
    claims.settle(defer=True)                                 # queues x.cpp's lock at its sha
    renewed, _ = claims.renew_held(["file:Code/x.cpp"])       # ... which then moves
    pushes = _pushes(monkeypatch, a)
    assert claims.acquire([0x200]).claimed == [0x200, claims.file_key("Code/y.cpp")]
    assert len(pushes) == 1              # the fresh snapshot drops the stale deletion before pushing
    held = claims._read_local(a)[claims.file_key("Code/x.cpp")]
    assert held[0] == renewed[claims.file_key("Code/x.cpp")]  # the moved ref survives
    assert claims.flush_outbox() == []


@pytest.mark.parametrize("renew_lock", [False, True])
def test_release_racing_a_partial_renewal_keeps_body_and_file_lock(hosts, monkeypatch, renew_lock):
    root = hosts("a")
    _task_fixture(root)
    held = claims.acquire([0x100])
    moved = []

    fkey = claims.file_key("Code/x.cpp")

    def renew_one_ref(args):
        if any(a.startswith(":") for a in args) and not moved:
            moved.append(claims.claim([fkey], locks=[fkey]) if renew_lock else claims.claim([0x100]))
    pushes = _pushes(monkeypatch, root, renew_one_ref)
    assert claims.release_work([0x100], tokens=held.tokens) == []
    refs = _remote_refs(hosts.origin)
    expected = dict(held.tokens)
    expected.update(moved[0].tokens)
    assert refs[claims.ref_of(0x100)] == expected[0x100]
    assert refs[claims.ref_of(fkey)] == expected[fkey]
    assert len([p for p in pushes if any(a.startswith(":") for a in p)]) == 1


@pytest.mark.parametrize("claim_next", [False, True])
def test_landing_queued_after_deferred_settlement_keeps_body_and_lock(hosts, claim_next):
    root = hosts("a")
    rows = _task_fixture(root)
    claims.acquire([0x100])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(root, [row, rows[1]], "land", {"Code/x.cpp": "void f() {}\n"})
    _verified(root, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    _git(root, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.settle(defer=True) == [0x100, claims.file_key("Code/x.cpp")]
    # Same lease, newer verified work: it has not been published or evaluated.
    (root / "Code/x.cpp").write_text("void f() { /* newer */ }\n", encoding="utf-8")
    _verified(root, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    if claim_next:
        assert claims.acquire([0x200]).claimed
    else:
        assert claims.flush_outbox() == []
    assert {0x100, claims.file_key("Code/x.cpp")} <= set(claims.active())
    assert any(e["deps"] for e in claims.pending())
    assert claims.flush_outbox() == []


def test_atomic_release_never_falls_back_to_separate_body_and_lock_pushes(hosts, monkeypatch):
    root = hosts("a")
    _task_fixture(root)
    claims.acquire([0x100])
    real = claims._git
    pushes = []

    def reject(*args, **kwargs):
        if args[:1] == ("push",):
            pushes.append(args)
            return subprocess.CompletedProcess(args, 1, "", "temporarily refused")
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", reject)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    assert claims.release_work([0x100]) == []
    assert len(pushes) == 5
    expected = {":" + claims.ref_of(k) for k in (0x100, claims.file_key("Code/x.cpp"))}
    assert all("--atomic" in p and expected <= set(p) for p in pushes)
    assert {0x100, claims.file_key("Code/x.cpp")} <= set(claims.active())


def test_gc_retry_keeps_the_file_lock_of_a_body_renewed_mid_collection(hosts, monkeypatch):
    root = hosts("a")
    _task_fixture(root)
    held = claims.acquire([0x100], ttl_hours=-3)
    fkey = claims.file_key("Code/x.cpp")
    assert set(held.tokens) == {0x100, fkey}
    moved = []

    def renew_body_only(args):
        # the heartbeat has pushed the body but not yet its lock when gc pushes
        if "--atomic" in args and any(a.startswith(":") for a in args) and not moved:
            moved.append(claims.claim([0x100]))
    _pushes(monkeypatch, root, renew_body_only)
    deleted, kept = claims.gc(max_per_minute=0)
    assert deleted == [] and set(kept) == {0x100, fkey}
    refs = _remote_refs(hosts.origin)
    assert refs[claims.ref_of(0x100)] == moved[0].tokens[0x100]
    assert refs[claims.ref_of(fkey)] == held.tokens[fkey]       # the live body's lock survives


def test_gc_opportunistic_makes_one_short_push_attempt(hosts, monkeypatch):
    root = hosts("a")
    _stale([0x100])
    monkeypatch.setenv("BFME_CLAIM_GC", "on")
    real = claims._git
    pushes = []

    def refuse(*args, **kwargs):
        if args[:1] == ("push",) and any(a.startswith(":") for a in args):
            pushes.append(kwargs.get("timeout"))
            return subprocess.CompletedProcess(args, 1, "", "refused")
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", refuse)
    monkeypatch.setattr(claims, "_backoff", lambda attempt: pytest.fail("no retry expected"))
    assert claims.gc_opportunistic() == []
    assert pushes == [20]
