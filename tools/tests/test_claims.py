"""Shared claims as refs on origin (tools/claims.py), two hosts against a bare repo.

Ported from Open-BFME-1's tools/tests/test_claims.py (fail-closed claims,
fencing, release only once origin/master holds the landing) and merged with
the BFME2-only cases: scope claims, the branch namespace, batched release and
the pickers. Every fixture is a local bare repository: no test reaches a
network or this checkout's origin.
"""
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


def _listing(args):
    """A claims snapshot's listing: the one network read every snapshot makes
    (claim commits it lacks are then fetched by sha)."""
    return args[:1] == ("ls-remote",) and any(arg.endswith("*") for arg in args)


def own_sleep(monkeypatch, sleep):
    """Replace only claims' sleep. Patching the shared time.sleep also counts
    subprocess's wait loop for a git child that has closed its pipes."""
    monkeypatch.setattr(claims, "time", type("Clock", (), {
        "sleep": staticmethod(sleep), "__getattr__": lambda self, name: getattr(time, name)})())


@pytest.fixture
def hosts(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    clones = {}
    for name in ("a", "b"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        clones[name] = clone

    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    # never this machine's real pacer or gc stamp; fast retries; gc only where a test asks
    monkeypatch.setattr(claims, "HOST_DIR", tmp_path / "host")
    monkeypatch.setattr(claims, "BACKOFF_BASE", 0.02)
    monkeypatch.setenv("BFME_CLAIM_PUSHES_PER_MINUTE", "0")
    monkeypatch.setenv("BFME_CLAIM_GC", "off")
    monkeypatch.setattr(claims, "_OUTBOX", {})

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        # never the real origin: every claim these tests push lands in the fixture
        assert Path(claims._git("remote", "get-url", "origin").stdout.strip()) == origin
        return clones[name]
    act.origin = origin
    return act


def test_claim_fetch_defers_maintenance_without_changing_config_or_pruning(hosts, monkeypatch):
    peer = hosts("b")
    assert claims.claim([0x100]).claimed == [0x100]
    root = hosts("a")
    _git(root, "config", "gc.auto", "1")
    _git(root, "config", "maintenance.auto", "true")
    real = claims._git
    calls = []

    def git(*args, **kwargs):
        if args[:1] == ("fetch",):
            calls.append(args)
        return real(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", git)
    assert claims.fetch(root)
    assert claims._read_local(root)[0x100][1]["owner"] == "b"
    assert len(calls) == 1                      # b's claim commit, fetched by sha
    assert claims.fetch(root)
    assert len(calls) == 1                      # nothing new: the listing alone
    assert claims.release([0x100], who="b", root=peer) == [0x100]
    assert claims.fetch(root)
    assert 0x100 not in claims._read_local(root)
    assert len(calls) == 1
    assert all("--no-auto-maintenance" in args and "--stdin" in args and "--no-write-fetch-head" in args and
               "--recurse-submodules=no" in args for args in calls)
    assert _git(root, "config", "gc.auto").strip() == "1"
    assert _git(root, "config", "maintenance.auto").strip() == "true"


def test_claim_snapshot_keeps_this_repository_refs_free_of_claims(hosts):
    # ~2,000 claim commits among a clone's refs made `git fetch origin master`
    # download the whole history: the snapshot lives in a side repository and
    # mirrors older clients left here are deleted.
    peer = hosts("b")
    assert claims.claim([0x100]).claimed == [0x100]
    root = hosts("a")
    _git(root, "commit", "-q", "--allow-empty", "-m", "base")
    head = _git(root, "rev-parse", "HEAD").strip()
    for legacy in ("refs/worktree/claims-seen/0x00000200", "refs/worktree/claims-seen-other/1/0x00000300",
                   "refs/worktree/claims-mirror-seen/0x00000400"):
        _git(root, "update-ref", legacy, head)
    assert claims.fetch(root)
    assert set(claims._read_local(root)) == {0x100}
    assert claims.claim([0x500]).claimed == [0x500]
    assert set(claims._read_local(root)) == {0x100, 0x500}
    assert claims.release([0x100], who="b", root=peer) == [0x100]
    claims.active.cache_clear()
    assert set(claims.active(root)) == {0x500}
    refs = _git(root, "for-each-ref", "--format=%(refname)").split()
    assert refs and not [name for name in refs if "claims" in name]
    assert not (Path(_git(root, "rev-parse", "--absolute-git-dir").strip()) / "FETCH_HEAD").exists()


def test_the_claim_mirror_survives_a_prune_and_otherwise_fails_closed(hosts):
    # Nothing in this repository's refs reaches the claim commits, so its gc may
    # drop them: the mirror keeps its own copies, and an unreadable mirror raises
    # instead of serving a partial view that could hide a live claim.
    peer = hosts("b")
    held = claims.claim([0x100]).tokens[0x100]
    root = hosts("a")
    mine = claims.claim([0x200]).tokens[0x200]
    assert claims.fetch(root)
    _git(root, "-c", "gc.reflogExpire=now", "-c", "gc.reflogExpireUnreachable=now", "gc", "-q", "--prune=now")
    for sha in (held, mine):
        assert subprocess.run(["git", "cat-file", "-e", sha], cwd=root).returncode != 0
    assert {k: v[1]["owner"] for k, v in claims._read_local(root).items()} == {0x100: "b", 0x200: "a"}
    assert claims.mirror_sha(0x100, root) == held
    claims.active.cache_clear()
    assert claims.claim([0x100]).refused == [0x100]
    renewed, lost = claims.renew({0x200: mine}, root=root)    # reads the token's lease from the mirror
    assert set(renewed) == {0x200} and lost == []
    assert claims.release([0x200], root=root) == [0x200]
    assert claims.release([0x100], who="b", root=peer) == [0x100]

    assert claims.claim([0x300]).claimed == [0x300]
    objects = Path(claims._seen_repo(root)) / "objects"
    shutil.rmtree(objects, onerror=lambda f, p, e: (os.chmod(p, 0o700), f(p)))  # git objects are read-only on Windows
    (objects / "pack").mkdir(parents=True)
    (objects / "info").mkdir()
    with pytest.raises(claims.ClaimsUnavailable, match="cannot read the claim mirror"):
        claims._read_local(root)


def test_a_claim_commit_with_history_is_mirrored_without_it(hosts):
    # Some clients' branch-namespace claim commits have parents deep in master's
    # history (one had 74,856 ancestors): the mirror copies the commit alone.
    import json

    root = hosts("a")
    for i in range(3):
        _git(root, "commit", "-q", "--allow-empty", "-m", f"history {i}")
    tip = _git(root, "rev-parse", "HEAD").strip()
    body = json.dumps({"owner": "peer", "created": int(time.time()), "expires": int(time.time()) + 3600})
    tree = subprocess.run(["git", "mktree"], cwd=root, input="", check=True, capture_output=True,
                          text=True).stdout.strip()
    made = subprocess.run(["git", "-c", "user.name=c", "-c", "user.email=c@l", "commit-tree", tree, "-p", tip,
                           "-m", body], cwd=root, check=True, capture_output=True, text=True).stdout.strip()
    _git(root, "push", "-q", "origin", f"{made}:refs/heads/claims/0x00000700")
    clone = hosts("b")
    assert claims.fetch(clone)
    assert claims._read_visible(clone)[0x700][1]["owner"] == "peer"
    side = claims._seen_repo(clone)
    assert _git(clone, f"--git-dir={side}", "rev-list", "--all", "--count").strip() == "1"
    _git(clone, f"--git-dir={side}", "gc", "-q", "--prune=now")
    assert claims._read_visible(clone)[0x700][1]["owner"] == "peer"


def test_a_claim_commit_gone_between_listing_and_fetch_is_retried(hosts, monkeypatch):
    hosts("b")
    assert claims.claim([0x100]).claimed == [0x100]
    root = hosts("a")
    real = claims._git
    failed = []

    def git(*args, **kwargs):
        if args[:1] == ("fetch",) and "--stdin" in args and not failed:
            failed.append(args)
            return subprocess.CompletedProcess(args, 128, "", "fatal: remote error: upload-pack: not our ref "
                                               + kwargs["input_text"].split()[0])
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    own_sleep(monkeypatch, lambda seconds: None)
    assert claims.fetch(root)
    assert failed and claims._read_local(root)[0x100][1]["owner"] == "b"


def test_a_claim_is_exclusive_across_hosts(hosts):
    hosts("a")
    assert claims.claim([0x100, 0x200]) == ([0x100, 0x200], [])
    hosts("b")
    assert set(claims.active()) == {0x100, 0x200}
    assert claims.claim([0x200, 0x300]) == ([0x300], [0x200])     # partial batch
    assert claims.active()[0x300]["owner"] == "b"


def test_rename_claims_reuses_acquisition_snapshot_and_preserves_owned_lease(hosts, monkeypatch):
    import rename

    root = hosts("a")
    previous = claims.claim([0x100])
    real = claims._git
    fetches, pushes = [], []

    def git(*args, **kwargs):
        if _listing(args):
            fetches.append(args)
        elif args[:1] == ("push",):
            pushes.append(args)
        return real(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", git)
    taken = rename.take_claims([0x100, 0x200], True, root)
    assert len(fetches) == 1
    assert len(pushes) == 1 and "--atomic" in pushes[0]
    assert f"--force-with-lease={claims.ref_of(0x100)}:{previous.tokens[0x100]}" in pushes[0]
    assert taken.new == [0x200] and set(taken.tokens) == {0x200}
    assert claims.current_lease(0x100, root=root) == previous.leases[0x100]
    assert taken.release(root) == [0x200]
    remaining = claims.live(claims._read_local(root))
    assert 0x100 in remaining and 0x200 not in remaining


@pytest.mark.parametrize("upstream", [False, True])
def test_fetch_snapshots_are_private_to_each_worktree(hosts, tmp_path, upstream):
    primary = hosts("a")
    _git(primary, "commit", "-q", "--allow-empty", "-m", "worktree fixture")
    sibling = tmp_path / "sibling"
    _git(primary, "worktree", "add", "-q", "--detach", str(sibling), "HEAD")
    hosts("b")
    assert claims.claim([0x100]) == ([0x100], [])

    seen = claims.MIRROR_SEEN if upstream else claims.SEEN
    if upstream:
        _git(primary, "config", "bfme.claimMirror", "origin")

    def refresh(root):
        if upstream:
            claims.mirrored.cache_clear()
            return claims.mirrored(root)
        assert claims.fetch(root)
        return claims._read_local(root)

    assert set(refresh(primary)) == {0x100}
    assert set(refresh(sibling)) == {0x100}
    before = claims._read_local(sibling, seen)
    assert claims.claim([0x200]) == ([0x200], [])
    assert set(refresh(primary)) == {0x100, 0x200}
    # The old shared refs/claims-seen mirror changed the sibling's refs here.
    # Concurrent fetches could then fail their expected-old-SHA ref update.
    assert claims._read_local(sibling, seen) == before
    assert set(refresh(sibling)) == {0x100, 0x200}

    assert claims.release([0x100]) == [0x100]
    assert set(refresh(primary)) == {0x200}
    assert set(claims._read_local(sibling, seen)) == {0x100, 0x200}
    assert set(refresh(sibling)) == {0x200}


def test_worktrees_still_contend_for_the_same_remote_claim(hosts, tmp_path):
    primary = hosts("a")
    _git(primary, "commit", "-q", "--allow-empty", "-m", "worktree fixture")
    sibling = tmp_path / "sibling"
    _git(primary, "worktree", "add", "-q", "--detach", str(sibling), "HEAD")
    assert claims.claim([0x100], root=primary, who="primary") == ([0x100], [])
    assert claims.claim([0x100], root=sibling, who="sibling") == ([], [0x100])
    assert claims.active(sibling)[0x100]["owner"] == "primary"


@pytest.mark.parametrize("upstream", [False, True])
def test_claim_fetch_does_not_fetch_submodules(hosts, tmp_path, upstream):
    primary = hosts("a")
    dependency = tmp_path / "dependency"
    dependency.mkdir()
    _git(dependency, "init", "-q")
    _git(dependency, "-c", "user.name=fixture", "-c", "user.email=fixture@example.com",
         "commit", "-q", "--allow-empty", "-m", "dependency fixture")
    _git(primary, "-c", "protocol.file.allow=always", "submodule", "add", "-q",
         str(dependency), "dependency")
    _git(primary, "commit", "-q", "-m", "submodule fixture")
    assert claims.claim([0x100]) == ([0x100], [])
    _git(primary, "config", "submodule.recurse", "true")
    _git(primary / "dependency", "remote", "set-url", "origin", str(tmp_path / "missing.git"))
    # A claim fetch must not depend on an unrelated vendored source remote.
    if upstream:
        _git(primary, "config", "bfme.claimMirror", "origin")
        claims.mirrored.cache_clear()
        assert set(claims.mirrored(primary)) == {0x100}
    else:
        assert claims.fetch(primary)
        assert set(claims._read_local(primary)) == {0x100}


def test_only_the_owner_releases(hosts):
    hosts("a")
    claims.claim([0x100])
    hosts("b")
    assert claims.release([0x100]) == []
    assert 0x100 in claims.active()
    hosts("a")
    assert claims.release([0x100]) == [0x100]
    assert claims.active() == {}


def test_an_expired_claim_can_be_taken_over(hosts):
    hosts("a")
    claims.claim([0x100], ttl_hours=-1)                            # already expired
    hosts("b")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([0x100], [])
    assert claims.active()[0x100]["owner"] == "b"


def _count_git(monkeypatch):
    calls = []
    real = claims._git

    def git(*args, **kwargs):
        calls.append(args[0] if args else "")
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    return calls


def test_a_batch_renew_is_one_push(hosts, monkeypatch):
    # a 20-key heartbeat made 20 paced pushes (54 s on a quiet host): one push now,
    # each ref still compare-and-swapped against its own generation
    hosts("a")
    got = claims.claim([0x300, 0x310, 0x320])
    assert got.claimed == [0x300, 0x310, 0x320]
    calls = _count_git(monkeypatch)
    renewed, lost = claims.renew(got.tokens)
    assert sorted(renewed) == [0x300, 0x310, 0x320] and lost == []
    assert calls.count("push") == 1
    assert {k: e[0] for k, e in claims._read_local().items() if k in renewed} == renewed


def test_a_batch_renew_still_reports_a_claim_taken_over(hosts, monkeypatch):
    # b takes an expired key over after a's renew fetched but before its batch
    # push: a forced ("+") refspec overrode the stale lease and erased b's claim
    peer = hosts("b")
    hosts("a")
    got = claims.claim([0x400, 0x410], ttl_hours=-1)      # already expired
    real, taken = claims._git, {}

    def git(*args, **kwargs):
        if args[:2] == ("push", "--porcelain") and not taken:
            taken["b"] = None
            taken["b"] = claims.claim([0x410], who="b", root=peer).tokens[0x410]
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    renewed, lost = claims.renew(got.tokens)
    assert taken["b"] and list(renewed) == [0x400] and lost == [0x410]
    assert _git(hosts.origin, "rev-parse", claims.ref_of(0x410)).strip() == taken["b"]


def test_a_failed_mirror_transaction_restarts_the_snapshot(hosts, monkeypatch):
    # a retry that re-read the mirror but kept the old listing deleted a claim
    # origin accepted meanwhile (here 0x200, claimed while the transaction failed)
    peer = hosts("b")
    root = hosts("a")
    assert claims.claim([0x100], who="b", root=peer).claimed == [0x100]
    real, raced = claims._git, {}

    def git(*args, **kwargs):
        if args[:2] == ("update-ref", "--stdin") and not raced:
            raced["a"] = None
            raced["a"] = claims.claim([0x200], root=root).tokens[0x200]
            return subprocess.CompletedProcess(args, 1, "", "fatal: injected lock failure")
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    claims._invalidate_snapshot(root)
    assert claims.fetch(root) is True
    assert raced["a"] and claims.mirror_sha(0x200, root) == raced["a"]
    assert claims.mirror_sha(0x100, root)


def test_a_batch_claim_mirrors_in_one_transaction(hosts, monkeypatch):
    hosts("a")
    calls = _count_git(monkeypatch)
    got = claims.claim([0x500 + i for i in range(5)])
    assert len(got.claimed) == 5
    assert calls.count("update-ref") <= 2            # the snapshot's, then the claims' one
    assert {k for k in claims._read_local() if isinstance(k, int)} >= set(got.claimed)


def test_a_mirror_ref_blocking_a_new_key_directory_is_replaced(hosts):
    # the mirror holds refs/claims-seen/lease as a plain ref (an old shape) while origin
    # now has refs/claims/lease/landing: one transaction cannot delete X and create
    # X/Y, so every snapshot failed ("directory conflict") until the mirror was rebuilt
    root = hosts("a")
    assert claims.claim(["lease:landing"]).claimed == ["lease/landing"]
    hosts("b")
    assert claims.fetch() is True
    side = claims._seen_repo()
    sha = claims.mirror_sha("lease/landing")
    claims._git("update-ref", "-d", claims.SEEN + "lease/landing", git_dir=side)
    claims._git("update-ref", claims.SEEN + "lease", sha, git_dir=side)
    claims._invalidate_snapshot()
    assert claims.fetch() is True
    assert claims.mirror_sha("lease/landing") == sha
    assert claims._git("rev-parse", "-q", "--verify", claims.SEEN + "lease", git_dir=side).returncode != 0


def test_renewing_your_own_claim_succeeds(hosts):
    hosts("a")
    claims.claim([0x100])
    assert claims.claim([0x100]) == ([0x100], [])


def test_an_unreachable_origin_fails_closed(hosts, monkeypatch):
    # Readers still serve (a picker only proposes), but claim() may no longer
    # answer ([], []) -- "nothing claimed" and "nothing to claim" looked alike.
    hosts("a")
    monkeypatch.setattr(claims, "REMOTE", "no-such-remote")
    assert claims.active() == {}
    with pytest.raises(claims.ClaimsUnavailable):
        claims.claim([0x100])
    assert claims.main(["claim", "0x100"]) == 2


def test_active_reads_the_origin_of_the_given_root_not_this_checkout(hosts, tmp_path):
    # A root is fetched through its own origin, so a fixture repository
    # without a remote sees no claims (Open-BFME-1 checks this through
    # eligibility.busy_rvas; BFME2's pickers ask claims.busy_rvas).
    hosts("a")
    assert claims.claim([0x300]) == ([0x300], [])
    hosts("b")
    assert set(claims.active(claims.ROOT)) == {0x300}
    lonely = tmp_path / "lonely"
    _git(tmp_path, "init", "-q", str(lonely))
    assert claims.active(lonely) == {}
    assert 0x300 not in claims.busy_rvas(lonely)
    assert claims.busy_rvas(claims.ROOT) == {0x300}


def test_a_claim_result_carries_tokens_and_still_unpacks(hosts):
    hosts("a")
    result = claims.claim([0x100, 0x200])
    got, refused = result
    assert (got, refused) == ([0x100, 0x200], [])
    assert result.worker == "a" and result.unconfirmed == []
    token = result.tokens[0x100]
    assert claims.holds(0x100, token)
    assert result.tokens[0x200] == token          # one claim commit per call


def test_a_push_origin_refuses_without_a_holder_is_unconfirmed(hosts, monkeypatch):
    hosts("a")
    real = claims._git

    def flaky(*args, **kw):
        if args[:1] == ("push",):
            return claims.subprocess.CompletedProcess(args, 1, "", "connection reset")
        return real(*args, **kw)
    monkeypatch.setattr(claims, "_git", flaky)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    result = claims.claim([0x100], atomic_only=True)
    assert not result.claimed and result.refused == [0x100] and result.unconfirmed == [0x100]


def test_atomic_claim_retries_transient_failure_when_origin_is_reachable(hosts, monkeypatch):
    hosts("a")
    real = claims._git
    pushes = []
    def flaky(*args, **kw):
        if args[:1] == ("push",):
            pushes.append(args)
            if len(pushes) < 3:
                return subprocess.CompletedProcess(args, 1, "", "ref transaction contention")
        return real(*args, **kw)
    monkeypatch.setattr(claims, "_git", flaky)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    result = claims.acquire([0x100])
    assert result.claimed == [0x100] and not result.refused and len(pushes) == 3


def test_reachable_push_refusals_never_serve_unclaimed_work(hosts, monkeypatch):
    import next_work
    hosts("a")
    real = claims._git
    pushes = []
    def refused(*args, **kw):
        if args[:1] == ("push",):
            pushes.append(args)
            return subprocess.CompletedProcess(args, 1, "", "transaction refused")
        return real(*args, **kw)
    monkeypatch.setattr(claims, "_git", refused)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    item = {"target_rva": "0x100", "function": "?f@@YAXXZ"}
    assert next_work.claim_choice([item], "test") == (None, [])
    assert 2 <= len(pushes) <= 5


def test_a_race_lost_after_fetch_is_refused_not_unconfirmed(hosts, monkeypatch):
    hosts("a")
    real_fetch = claims.fetch
    calls = []

    def fetch_then_race(root=None):
        ok = real_fetch(root)
        if not calls:                  # b claims between a's fetch and a's push
            calls.append(1)
            monkeypatch.setenv("BFME_CLAIM_OWNER", "b")
            claims.claim([0x100], root=hosts.b_root)
            monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
        return ok
    hosts.b_root = hosts("b")
    hosts("a")
    monkeypatch.setattr(claims, "fetch", fetch_then_race)
    result = claims.claim([0x100])
    assert result == ([], [0x100]) and result.unconfirmed == []


def test_the_default_owner_is_per_checkout_not_per_host(hosts, monkeypatch):
    a = hosts("a")
    b = hosts("b")
    monkeypatch.delenv("BFME_CLAIM_OWNER")
    assert claims.owner(a) != claims.owner(b)
    assert claims.owner(a) == claims.owner(a)
    _git(a, "checkout", "-q", "-b", "work-seat7")                 # BFME2: the agent's branch
    assert claims.owner(a) == "seat7"
    monkeypatch.setenv("BFME_RUN_ID", "20260929T000000Z-abc")
    assert claims.owner(a) == "fleet:20260929T000000Z-abc"


def test_heartbeat_renews_and_fencing_detects_a_takeover(hosts):
    hosts("a")
    result = claims.claim([0x100, 0x200], ttl_hours=-1)            # both already expired
    renewed, lost = claims.renew({0x100: result.tokens[0x100]})
    assert lost == [] and claims.holds(0x100, renewed[0x100])
    assert not claims.holds(0x100, result.tokens[0x100])           # old token is dead
    hosts("b")
    taken = claims.claim([0x200])                                  # expired: b takes it over
    assert taken.claimed == [0x200]
    hosts("a")
    renewed, lost = claims.renew({0x200: result.tokens[0x200]})
    assert renewed == {} and lost == [0x200]
    # a stale release (even forced) never deletes the successor's claim
    assert claims.release([0x200], force=True, tokens={0x200: result.tokens[0x200]}) == []
    assert claims.active()[0x200]["owner"] == "b"


def _commit_ledger(clone, rows, message, files=None):
    ledger = clone / claims.LEDGER
    ledger.parent.mkdir(parents=True, exist_ok=True)
    ledger.write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                      + "".join(r + "\n" for r in rows), encoding="utf-8")
    for path, text in (files or {}).items():
        (clone / path).parent.mkdir(parents=True, exist_ok=True)
        (clone / path).write_text(text, encoding="utf-8")
        _git(clone, "add", path)
    _git(clone, "add", claims.LEDGER)
    _git(clone, "commit", "-q", "-m", message)
    return _git(clone, "rev-parse", "HEAD").strip()


def _verified(clone, source, headers=()):
    """Write the object and receipt tools/build.py leaves when it compiles
    `source` (build/match/<obj> and <obj>.deps.json: the md5 of the source and
    of each header /showIncludes reported, keyed relative to the checkout, the
    source's path and the object's md5), as a verified add_match would have."""
    import hashlib
    import json

    def md5(path):
        return hashlib.md5((clone / path).read_bytes()).hexdigest()
    obj = claims.object_path(source, clone)
    obj.parent.mkdir(parents=True, exist_ok=True)
    obj.write_bytes(b"object of " + source.encode())
    claims.receipt_path(source, clone).write_text(json.dumps({
        "cmd": "fixture", "source": md5(source), "deps": {h: md5(h) for h in headers},
        "path": source, "object": hashlib.md5(obj.read_bytes()).hexdigest()}), encoding="utf-8")


def test_a_landing_releases_only_once_origin_master_holds_the_row(hosts):
    a = hosts("a")
    base = _commit_ledger(a, ["?d_00000100@@YAXXZ,,0x00000100,16,Code/gen_asm/x.asm,matched,gen-dump"], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    sha = _commit_ledger(a, [row], "land", {"Code/x.cpp": "void f() {}\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    # verified and committed locally, not pushed: the claim must hold
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()
    with pytest.raises(ValueError):
        claims.landed_rvas(sha)
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])
    assert claims.active() == {} and claims.pending() == []
    assert base != sha


def test_release_landed_sha_releases_the_leases_the_commit_names(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    got = claims.claim([0x300, 0x400])
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,Code/y.cpp,matched,",
                             "?h@@YAXXZ,,0x00000400,8,Code/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={got.leases[0x300]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.landed_rvas(sha) == [0x300, 0x400]
    assert claims.lease_trailers(sha) == {0x300: got.leases[0x300]}
    assert claims.main(["release", "--landed", sha]) == 0
    assert set(claims.active()) == {0x400}          # no trailer, no evidence: untouched


def test_an_old_published_row_does_not_release_an_unpublished_source_change(hosts):
    # review 2026-09-29: the same row key was already on origin (an earlier
    # lift); the new source existed only locally, and release_landed released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,gen-dump"
    _commit_ledger(a, [row], "existing lift", {"Code/x.cpp": "__asm { emit }\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    (a / "Code/x.cpp").write_text("void f() { real(); }\n", encoding="utf-8")
    (a / "Code/x.h").write_text("struct X;\n", encoding="utf-8")          # a new dependency
    _git(a, "add", "Code/x.h")              # an untracked header is unproven (review round 2)
    _verified(a, "Code/x.cpp", ["Code/x.h"])
    claims.queue_landed(0x100, row.replace("gen-dump", "model=m"))
    _git(a, "reset", "-q", "--", "Code/x.h")    # unstaged: the commits below leave it local
    entry = claims.pending()[0]
    assert set(entry["deps"]) == {"Code/x.cpp", "Code/x.h"}
    assert claims.release_landed() == ([], [0x100])
    _commit_ledger(a, [row.replace("gen-dump", "model=m")], "real body",
                   {"Code/x.cpp": "void f() { real(); }\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([], [0x100])        # the header is still local
    _commit_ledger(a, [row.replace("gen-dump", "model=m")], "header",
                   {"Code/x.h": "struct X;\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])


def test_a_missing_source_never_releases(hosts):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "row only")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    claims.queue_landed(0x100, row)
    assert claims.release_landed() == ([], [0x100])


def test_concurrent_queue_appends_all_survive(tmp_path):
    import threading
    jobs = [threading.Thread(target=claims.queue_landed,
                             args=(r, f"f,,0x{r:08X},1,Code/x.cpp,matched,"),
                             kwargs={"who": "t", "root": tmp_path,
                                     "evidence": {"deps": {"Code/x.cpp": "b"}}})
            for r in range(0x100, 0x100 + 24)]
    for job in jobs:
        job.start()
    for job in jobs:
        job.join(timeout=30)
    assert sorted(int(e["rva"], 16) for e in claims.pending(tmp_path)) == list(range(0x100, 0x118))


def test_a_directory_inside_a_checkout_never_inherits_its_origin(hosts):
    # review 2026-09-29: pytest's basetemp under a real checkout let a
    # "no origin" fixture discover the enclosing repo and push real claims.
    a = hosts("a")
    inner = a / "build" / "fixture"
    inner.mkdir(parents=True)
    assert not claims.configured(inner)
    with pytest.raises(claims.ClaimsUnavailable):
        claims.claim([0x500], root=inner)
    assert _git(hosts.origin, "for-each-ref", "refs/claims/") == ""


def test_release_landed_sha_cannot_override_a_pending_landing(hosts):
    # review 2026-09-29 (reproduction test_release_bypass.py): settlement kept
    # the claim, but `release --landed <old published sha>` released it while
    # the replacement source was still local.
    a = hosts("a")
    _commit_ledger(a, [], "base")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    sha = _commit_ledger(a, [row], "old published body", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    (a / "Code/x.cpp").write_text("void f() { different(); }\n", encoding="utf-8")
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    assert claims.release_landed() == ([], [0x100])
    assert claims.release_landed(sha) == ([], [0x100])
    assert 0x100 in claims.active()
    assert claims.main(["release", "--landed", sha]) == 0 and 0x100 in claims.active()


def test_an_earlier_settled_landing_does_not_release_a_newer_pending_one(hosts):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)                          # matches origin: settled
    (a / "Code/x.cpp").write_text("void f() { again(); }\n", encoding="utf-8")
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)                          # a second, local-only pass
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()


def test_a_committed_but_unpushed_repair_is_not_released(hosts):
    # 2026-09-29 audit fixture: the row was on origin, the repaired source was
    # committed locally but never pushed, and release_landed released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=old"
    _commit_ledger(a, [row], "old landing", {"Code/x.cpp": "old source\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    _git(a, "fetch", "-q", "origin")
    claims.claim([0x100])
    _commit_ledger(a, [row], "unpublished repair", {"Code/x.cpp": "repaired source\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row.replace("model=old", "model=new"))
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()


def test_a_committed_but_unpushed_header_is_a_dependency(hosts):
    # the source is published already; the header it now reads is only in a
    # local commit, and the build's receipt names it
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    _commit_ledger(a, [row], "local header", {"Code/x.h": "struct X;\n"})
    _verified(a, "Code/x.cpp", ["Code/x.h"])
    claims.queue_landed(0x100, row)
    assert set(claims.pending()[0]["deps"]) == {"Code/x.cpp", "Code/x.h"}
    assert claims.release_landed() == ([], [0x100])
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])


def test_an_upstream_only_change_does_not_hold_a_published_landing(hosts):
    # BFME2 deviation from Open-BFME-1: its two-dot `origin/master HEAD` diff
    # also listed files a PEER changed upstream; their stale local blobs never
    # equal origin's, so the landing could not settle (Open-BFME-1
    # re_attempts.log, 0x008615F0 false-reject claims.release_landed). The
    # receipt lists only what the compile read, which a peer's file is not.
    a = hosts("a")
    _commit_ledger(a, [], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    b = hosts("b")
    _git(b, "pull", "-q", "origin", "master")
    _commit_ledger(b, [], "peer change", {"Code/peer.cpp": "void peer() {}\n"})
    _git(b, "push", "-q", "origin", "HEAD:refs/heads/master")
    a = hosts("a")
    _git(a, "fetch", "-q", "origin")                 # origin/master is now ahead of a
    claims.claim([0x100])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "land", {"Code/x.cpp": "void f() {}\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    assert set(claims.pending()[0]["deps"]) == {"Code/x.cpp"}
    _git(a, "pull", "-q", "--rebase", "origin", "master")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])


def test_a_submodule_dependency_is_its_checked_out_commit(tmp_path):
    # BFME2: reference/open-bfme-1 is a gitlink; origin/master's tree records
    # its commit, not the blobs of the headers a compile read inside it
    _git(tmp_path, "init", "-q")
    sub = tmp_path / "reference" / "sub"
    sub.mkdir(parents=True)
    _git(sub, "init", "-q")
    (sub / "x.h").write_text("#define V 1\n", encoding="utf-8")
    _git(sub, "add", "x.h")
    _git(sub, "-c", "user.name=t", "-c", "user.email=t@example.com", "commit", "-q", "-m", "pin")
    head = _git(sub, "rev-parse", "HEAD").strip()
    _git(tmp_path, "add", "reference/sub")
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "x.cpp").write_text('#include "x.h"\n', encoding="utf-8")
    _verified(tmp_path, "Code/x.cpp", ["reference/sub/x.h"])
    deps, why = claims.landing_deps("Code/x.cpp", tmp_path)
    assert why == "" and set(deps) == {"Code/x.cpp", "reference/sub"}
    assert deps["reference/sub"] == head


def test_a_lease_survives_renewal_and_dies_with_a_takeover(hosts):
    hosts("a")
    got = claims.claim([0x100], ttl_hours=-1)                       # expired at once
    lease = got.leases[0x100]
    assert claims.lease_holder(0x100, lease) is None                # expired: not held
    renewed, _ = claims.renew(got.tokens)
    assert claims.lease_holder(0x100, lease) == renewed[0x100]      # same lease, new token
    assert claims.lease_holder(0x100, got.tokens[0x100]) is None    # the old token alone is dead
    hosts("b")
    claims.release([0x100], force=True)
    claims.claim([0x100])
    hosts("a")
    assert claims.lease_holder(0x100, lease) is None


def test_a_landing_queued_during_settlement_keeps_its_claim(hosts, monkeypatch):
    # review 2026-09-30: the queue was snapshotted before the fetch, so a
    # repair queued meanwhile was never evaluated and its claim was released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)                    # settled on origin
    real_fetch = claims._fetch_master

    def queue_while_on_network(root=None):
        (a / "Code/x.cpp").write_text("void f() { local_repair(); }\n", encoding="utf-8")
        _verified(a, "Code/x.cpp")
        claims.queue_landed(0x100, row)
        return real_fetch(root)
    monkeypatch.setattr(claims, "_fetch_master", queue_while_on_network)
    released, waiting = claims.release_landed()
    assert released == [] and 0x100 in waiting
    assert len(claims.pending()) == 1 and 0x100 in claims.active()


def test_settlement_releases_only_the_claim_generation_it_evaluated(hosts, monkeypatch):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    real_release = claims.release

    def reclaimed_first(rvas, **kwargs):
        # the claim is re-taken (a new generation) between evaluation and release
        claims.claim([0x100], who="a")
        return real_release(rvas, **kwargs)
    monkeypatch.setattr(claims, "release", reclaimed_first)
    assert claims.release_landed()[0] == []
    assert 0x100 in claims.active()


def _published_and_queued(a):
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"Code/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    old = claims.claim([0x100])
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    assert claims.pending()[0]["lease"] == old.leases[0x100]
    return old


def test_a_fresh_claim_during_settlement_survives_the_old_landing(hosts, monkeypatch):
    # review 2026-09-30 (test_review_probes.py): the body was claimed afresh
    # by the same owner while settlement fetched; the old landing deleted the
    # NEW claim. (A re-claim of a LIVE claim keeps its lease since review
    # 2026-10-09, so the fresh claim here follows a release.)
    a = hosts("a")
    old = _published_and_queued(a)
    real_fetch = claims._fetch_master
    fresh = []

    def replace_before_evaluation(root=None):
        claims.release([0x100])
        fresh.append(claims.claim([0x100], who="a"))
        return real_fetch(root)
    monkeypatch.setattr(claims, "_fetch_master", replace_before_evaluation)
    released, _ = claims.release_landed()
    assert fresh[0].leases[0x100] != old.leases[0x100]
    assert released == [] and 0x100 in claims.active()
    assert claims.holds(0x100, fresh[0].tokens[0x100])


def test_a_renewal_keeps_the_lease_so_the_landing_still_releases(hosts):
    a = hosts("a")
    old = _published_and_queued(a)
    renewed, lost = claims.renew(old.tokens)
    assert lost == [] and renewed[0x100] != old.tokens[0x100]
    assert claims.release_landed() == ([0x100], [])
    assert claims.active() == {}


def test_release_landed_sha_never_releases_on_timing(hosts, monkeypatch):
    # review 2026-09-30 (test_ca142ff_review.py): a claim taken 0.9 s AFTER the
    # commit passed the whole-second `since <= commit time` test and was freed.
    a = hosts("a")
    _commit_ledger(a, [], "base")
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,Code/y.cpp,matched,"], "land")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    committed = int(_git(a, "log", "-1", "--format=%ct", sha))
    monkeypatch.setattr(claims.time, "time", lambda: committed + 0.9)
    fresh = claims.claim([0x300])
    released, _ = claims.release_landed(sha)
    assert released == [] and claims.holds(0x300, fresh.tokens[0x300])


def test_a_trailer_naming_an_old_lease_does_not_release_a_fresh_claim(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    old = claims.claim([0x300], ttl_hours=-1)        # lapses at once
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,Code/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={old.leases[0x300]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    fresh = claims.claim([0x300])                    # same owner, new lease after the lapse
    assert fresh.leases[0x300] != old.leases[0x300]
    assert claims.release_landed(sha)[0] == []
    assert claims.holds(0x300, fresh.tokens[0x300])


@pytest.mark.parametrize("failure", [None, "fetch", "head", "head_error_with_output", "empty", "timeout"])
def test_fetch_master_preserves_commands_and_reports_failed_step(
        tmp_path, monkeypatch, capsys, failure):
    # Exercise the real _fetch_master and _git with a mocked subprocess only:
    # no fixture or production Git/network operation is launched.
    import os

    monkeypatch.setattr(claims, "REMOTE", "fixture-origin")
    inherited_env = dict(os.environ)
    calls = []

    def run(command, **kwargs):
        step = ("tip", "fetch", "head")[min(len(calls), 2)]
        calls.append(command)
        assert kwargs == {
            "cwd": tmp_path, "capture_output": True,
            "input": None, "timeout": 300 if step == "fetch" else 60,
            "env": dict(inherited_env, GIT_CEILING_DIRECTORIES=str(tmp_path.resolve().parent)),
        }
        if step == "tip":
            assert command == ["git", "for-each-ref", "--format=--negotiation-tip=%(refname)",
                               "refs/remotes/fixture-origin/master"]
            return subprocess.CompletedProcess(command, 0, "--negotiation-tip=refs/remotes/fixture-origin/master\n", "")
        if step == "fetch":
            assert command == ["git", "fetch", "-q", "--no-tags", "--negotiation-tip=refs/remotes/fixture-origin/master",
                               "fixture-origin", "master"]
            if failure == "timeout":
                raise subprocess.TimeoutExpired(command, 300)
            if failure == "fetch":
                return subprocess.CompletedProcess(command, 128, "", "fatal: fixture fetch failed\n")
            return subprocess.CompletedProcess(command, 0, "", "")
        assert command == ["git", "rev-parse", "FETCH_HEAD"]
        if failure == "head":
            return subprocess.CompletedProcess(command, 128, "", "fatal: fixture FETCH_HEAD failed\n")
        if failure == "head_error_with_output":
            return subprocess.CompletedProcess(command, 128, "abc123\n", "fatal: fixture FETCH_HEAD failed\n")
        if failure == "empty":
            return subprocess.CompletedProcess(command, 0, " \n", "")
        return subprocess.CompletedProcess(command, 0, "abc123\n", "")

    monkeypatch.setattr(claims.subprocess, "run", run)
    result = claims._fetch_master(tmp_path)
    captured = capsys.readouterr()
    assert captured.out == ""
    assert len(calls) == (2 if failure in ("fetch", "timeout") else 3)
    if failure is None:
        assert result == "abc123"
        assert captured.err == ""
    else:
        assert result is None
        expected = {
            "fetch": "claims: git fetch fixture-origin master failed (exit 128): fatal: fixture fetch failed\n",
            "head": "claims: git rev-parse FETCH_HEAD failed (exit 128, empty stdout): fatal: fixture FETCH_HEAD failed\n",
            "head_error_with_output": "claims: git rev-parse FETCH_HEAD failed (exit 128): fatal: fixture FETCH_HEAD failed\n",
            "empty": "claims: git rev-parse FETCH_HEAD failed (exit 0, empty stdout): (no stderr)\n",
            "timeout": "claims: git fetch fixture-origin master failed (exit 124): timed out after 300s\n",
        }
        assert captured.err == expected[failure]


# ---- settle(): BFME2's stand-in for Open-BFME-1's fleet_run.settle_shared ----

def test_settle_keeps_an_unpublished_landing_and_frees_the_rest(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100, 0x200])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "land 0x100 locally", {"Code/x.cpp": "void f() {}\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, row)
    assert claims.settle([0x100, 0x200]) == [0x200]
    assert set(claims.active()) == {0x100}
    # the push lands it; the next settle (any picker in this checkout) frees it
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.settle() == [0x100]
    assert claims.active() == {} and claims.pending() == []


def test_settle_keeps_every_claim_when_origin_master_is_unreadable(hosts, monkeypatch):
    a = hosts("a")
    claims.claim([0x100, 0x200])
    row = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "land", {"Code/x.cpp": "void f() {}\n"})
    claims.queue_landed(0x100, row)
    monkeypatch.setattr(claims, "_fetch_master", lambda root=None: None)
    assert claims.settle([0x100, 0x200]) == []
    assert set(claims.active()) == {0x100, 0x200}


def _lease(rva):
    claims.active.cache_clear()
    return claims.active()[rva].get("lease")


def test_the_claim_command_settles_other_landed_claims(hosts):
    # 2026-10-10: 28% of live RVA claims sat on bodies origin/master already
    # held, because a seat that runs `claims.py claim` never ran a picker
    a = hosts("a")
    _published_and_queued(a)
    assert claims.main(["claim", "0x200"]) == 0
    claims.active.cache_clear()
    assert set(claims.active()) == {0x200} and claims.pending() == []


def test_the_claim_command_renews_a_landed_claim_without_a_gap(hosts, monkeypatch):
    # GPT-6.1-Sol review: settling BEFORE the claim released the claim being
    # renewed and re-took it under a new lease, and a peer could win between
    a = hosts("a")
    old = _published_and_queued(a)
    real_release = claims.release
    attempts = []

    def recorded(keys, *args, **kwargs):
        # record and forward: an assertion raised here would be swallowed by
        # settle() and would itself prevent the release (Sol, round 1)
        attempts.append(claims._ints(keys))
        return real_release(keys, *args, **kwargs)
    monkeypatch.setattr(claims, "release", recorded)
    assert claims.main(["claim", "0x100", "0x200"]) == 0
    assert all(0x100 not in keys for keys in attempts)
    assert _lease(0x100) == old.leases[0x100]
    assert [e["rva"] for e in claims.pending()] == ["0x00000100"]   # its landing still settles it
    hosts("b")
    assert claims.claim([0x100]) == ([], [0x100])
    # a later settlement that does not hold it releases it as usual
    hosts("a")
    lock = claims.lock_keys({0x100}) - {0x100}                    # its row's file, locked by `claim`
    assert lock and claims.settle() == [0x100, *lock]             # and released with it: no claim needs it


def test_settle_never_releases_a_held_claim_it_is_asked_to_release(hosts):
    # Sol round 1: `free` skipped waiting and released bodies, not held ones
    hosts("a")
    got = claims.claim([0x100, 0x200])
    assert claims.settle([0x100, 0x200], hold={0x100}) == [0x200]
    claims.active.cache_clear()
    assert set(claims.active()) == {0x100}
    assert claims.holds(0x100, got.tokens[0x100]) and _lease(0x100) == got.leases[0x100]


def test_a_sha_trailer_never_releases_a_held_claim(hosts):
    # Sol round 1: hold was checked only against queued landings, so a
    # Claim-Lease trailer for an unqueued body released it anyway
    a = hosts("a")
    _commit_ledger(a, [], "base")
    got = claims.claim([0x300, 0x400])
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,Code/y.cpp,matched,",
                             "?h@@YAXXZ,,0x00000400,8,Code/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={got.leases[0x300]}\n"
                         f"Claim-Lease: 0x00000400={got.leases[0x400]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    released, _ = claims.release_landed(sha, hold={0x300})
    assert released == [0x400]
    claims.active.cache_clear()
    assert set(claims.active()) == {0x300} and claims.holds(0x300, got.tokens[0x300])
    released, _ = claims.release_landed(sha)        # not held: the trailer releases it
    assert released == [0x300]


def test_an_iterator_hold_is_read_once_in_settle(hosts):
    # Sol round 2: set(hold) spent the iterator, then `free` tested the empty one
    hosts("a")
    got = claims.claim([0x100, 0x200])
    assert claims.settle([0x100, 0x200], hold=iter([0x100])) == [0x200]
    claims.active.cache_clear()
    assert set(claims.active()) == {0x100}
    assert claims.holds(0x100, got.tokens[0x100]) and _lease(0x100) == got.leases[0x100]


def test_an_iterator_hold_is_read_once_in_release_landed(hosts):
    # Sol round 2: each `in` test consumed the iterator, so held 0x400 released
    a = hosts("a")
    _commit_ledger(a, [], "base")
    got = claims.claim([0x300, 0x400])
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,Code/y.cpp,matched,",
                             "?h@@YAXXZ,,0x00000400,8,Code/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={got.leases[0x300]}\n"
                         f"Claim-Lease: 0x00000400={got.leases[0x400]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed(sha, hold=iter([0x400, 0x300]))[0] == []
    claims.active.cache_clear()
    assert set(claims.active()) == {0x300, 0x400}
    assert claims.release_landed(sha)[0] == [0x300, 0x400]


def test_a_settlement_failure_never_changes_the_claim_result(hosts, monkeypatch, capsys):
    a = hosts("a")
    _published_and_queued(a)

    def broken(*args, **kwargs):
        raise claims.ClaimsUnavailable("claims: cannot fetch origin/master")
    monkeypatch.setattr(claims, "release_landed", broken)
    assert claims.main(["claim", "0x200"]) == 0
    assert "claims kept until published or expired" in capsys.readouterr().err
    claims.active.cache_clear()
    assert set(claims.active()) == {0x100, 0x200}
    hosts("b")
    assert claims.main(["claim", "0x200"]) == 1     # refused stays refused


def test_settle_with_claims_off_touches_nothing(hosts, monkeypatch):
    hosts("a")
    claims.claim([0x100])
    monkeypatch.setenv("BFME_CLAIMS", "off")

    def forbidden(*args, **kwargs):
        raise AssertionError("settle reached origin with BFME_CLAIMS=off")
    monkeypatch.setattr(claims, "release_landed", forbidden)
    monkeypatch.setattr(claims, "release", forbidden)
    assert claims.settle([0x100]) == []


# ---- BFME2-only: batched release, the push hook, scopes, branch namespace ----

def test_batch_release_uses_one_atomic_push(hosts, monkeypatch):
    hosts("a")
    assert claims.claim([0x100, 0x200, 0x300])[0] == [0x100, 0x200, 0x300]
    original_git = claims._git
    pushes = []

    def traced_git(*args, **kwargs):
        if args[0] == "push":
            pushes.append(args)
        return original_git(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", traced_git)
    assert claims.release([0x100, 0x200, 0x300]) == [0x100, 0x200, 0x300]
    assert len(pushes) == 1
    assert "--atomic" in pushes[0]
    assert claims.active() == {}


def test_claim_markers_pass_the_repository_push_hook(hosts):
    hosts("a")
    hooks = claims.ROOT / ".githooks"
    hooks.mkdir()
    shutil.copy2(TOOLS.parent / ".githooks" / "pre-push", hooks / "pre-push")
    assert claims.claim([0x400]) == ([0x400], [])


def test_main_pickers_hide_busy_retail_addresses():
    import next_work
    import list_naked_candidates

    work = [{"target_rva": "0x00000100"}, {"candidate_rva": "0x00000200"},
            {"target_rva": "0x00000300"}]
    assert next_work.without_busy(work, {0x100, 0x200}) == work[2:]
    naked = [{"rva": "0x00000100"}, {"rva": "0x00000300"}]
    assert list_naked_candidates.without_busy(naked, {0x100}) == naked[1:]


def test_main_pickers_retry_when_a_peer_claimed_the_first_draw(monkeypatch):
    import next_work
    import list_naked_candidates as naked_queue

    def claim(rvas, **_kwargs):
        rva = rvas[0]
        return ([], [rva]) if rva == 0x100 else ([rva], [])

    monkeypatch.setattr(claims, "claim", claim)
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    work = [{"target_rva": "0x00000100"}, {"target_rva": "0x00000200"}]
    assert next_work.claim_choice(work, "test") == (work[1], [0x200])

    monkeypatch.setattr(naked_queue, "select_candidate",
                        lambda candidates: (candidates[0], {"pool": len(candidates)}))
    naked = [{"rva": "0x00000100"}, {"rva": "0x00000200"}]
    assert naked_queue.claim_choice(naked) == (naked[1], {"pool": 1}, [0x200])


def test_main_pickers_serve_unclaimed_when_origin_is_unavailable(monkeypatch):
    # claim() fails closed now; the pickers keep AGENTS.md's promise that a
    # network failure warns and leaves the work available.
    import next_work
    import list_naked_candidates as naked_queue

    def offline(rvas, **_kwargs):
        raise claims.ClaimsUnavailable("claims: offline")

    monkeypatch.setattr(claims, "claim", offline)
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    work = [{"target_rva": "0x00000100"}]
    assert next_work.claim_choice(work, "test") == (work[0], [])
    monkeypatch.setattr(naked_queue, "select_candidate",
                        lambda candidates: (candidates[0], {"pool": len(candidates)}))
    naked = [{"rva": "0x00000100"}]
    assert naked_queue.claim_choice(naked) == (naked[0], {"pool": 1}, [])


def test_scope_claims_are_exclusive_and_invisible_to_pickers(hosts):
    hosts("a")
    got, refused = claims.claim(["class:RenderObjClass", "file:Code/A/B.cpp", "0x100"])
    assert refused == [] and len(got) == 3
    hosts("b")
    live = claims.active()
    assert "class/RenderObjClass" in live and live["class/RenderObjClass"]["scope"] == "RenderObjClass"
    assert live[claims.key_of("file:Code/A/B.cpp")]["scope"] == "Code/A/B.cpp"
    assert claims.busy_rvas() == {0x100}                         # pickers see RVAs only
    assert claims.claim(["class:RenderObjClass"]) == ([], ["class/RenderObjClass"])
    hosts("a")
    assert sorted(claims.release(["class:RenderObjClass", "file:Code/A/B.cpp"])) == \
        sorted(["class/RenderObjClass", claims.key_of("file:Code/A/B.cpp")])


def test_a_scope_claim_keeps_its_scope_through_a_renewal(hosts):
    hosts("a")
    got = claims.claim(["class:RenderObjClass"])
    renewed, lost = claims.renew(got.tokens)
    assert lost == [] and set(renewed) == {"class/RenderObjClass"}
    assert claims.active()["class/RenderObjClass"]["scope"] == "RenderObjClass"
    assert claims.release(["class:RenderObjClass"], tokens=renewed) == ["class/RenderObjClass"]


def test_qualified_class_claim_round_trips_and_is_exclusive(hosts):
    scope = "class:StrategicHUD::BattlePromptArmyPanelMovieClip::Impl"
    key = claims.key_of(scope)
    assert ":" not in claims.ref_of(key)
    assert key != claims.key_of("class:StrategicHUD__BattlePromptArmyPanelMovieClip__Impl")
    hosts("a")
    assert claims.claim([scope]) == ([key], [])
    hosts("b")
    live = claims.active()
    assert live[key]["scope"] == scope[6:]
    assert claims.label(key, live[key]) == scope
    assert claims.busy_rvas() == set()
    assert claims.claim([scope]) == ([], [key])
    assert claims.release([scope]) == []
    hosts("a")
    assert claims.claim([scope]) == ([key], [])
    assert claims.release([scope]) == [key]
    assert claims.active() == {}


@pytest.mark.parametrize("name", ["", "::Impl", "HUD::", "HUD:::Impl", "HUD:Impl",
                                  "HUD::A/B", "HUD::A.lock", "HUD::A%3A%3AB"])
def test_invalid_qualified_names_cannot_escape_the_ref_namespace(name):
    with pytest.raises(ValueError):
        claims.key_of("class:" + name)


@pytest.mark.parametrize("scope", ["class:HUD::Impl", "class:RenderObjClass", "file:Code/A/B.cpp"])
def test_a_made_key_round_trips_through_key_of(scope):
    # renew() and release(tokens=...) see ClaimResult keys, not CLI scopes
    key = claims.key_of(scope)
    assert claims.key_of(key) == key


@pytest.mark.parametrize("key", ["class/../x", "class/HUD%3A%3A", "class/A%2FB", "file/xyz",
                                 "file/0123456789abcdef/x"])
def test_a_forged_key_is_refused(key):
    with pytest.raises(ValueError):
        claims.key_of(key)


def test_a_branch_namespace_release_overwrites_with_an_expired_record(hosts, monkeypatch):
    # hosts whose git proxy only accepts branch pushes: a release cannot
    # delete the branch, so it writes a record every reader ignores
    hosts("a")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/")
    assert claims.claim([0x100]) == ([0x100], [])
    hosts("b")
    assert set(claims.active()) == {0x100}
    assert claims.claim([0x100]) == ([], [0x100])
    hosts("a")
    assert claims.release([0x100]) == [0x100]
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname)", "refs/heads/claims/").split() == \
        ["refs/heads/claims/0x00000100"]
    hosts("b")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([0x100], [])          # the expired record is taken over


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
@pytest.mark.parametrize("key", [0x100, "class:RenderObjClass", "file:Code/A/B.cpp"])
def test_other_namespace_claims_are_visible(hosts, monkeypatch, writer_ns, key):
    hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    held = claims.claim([key])
    hosts("b")
    reader_ns = "refs/heads/claims/" if writer_ns == "refs/claims/" else "refs/claims/"
    monkeypatch.setattr(claims, "NS", reader_ns)
    expected = claims.key_of(key)
    assert claims.active()[expected]["owner"] == "a"
    assert claims.busy_rvas() == ({expected} if isinstance(expected, int) else set())
    assert held.claimed == [expected]


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
@pytest.mark.parametrize("same_owner", [False, True])
def test_other_namespace_claims_cannot_be_claimed_or_mutated(hosts, monkeypatch,
                                                           writer_ns, same_owner):
    hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    held = claims.claim([0x100])
    original = _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)")
    hosts("b")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/" if writer_ns == "refs/claims/"
                        else "refs/claims/")
    if same_owner:
        monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
    assert claims.claim([0x100]) == ([], [0x100])
    # A visible foreign-namespace lease must not be mistaken for a writable
    # local-namespace ref, even when its owner string happens to be ours.
    assert claims.current_lease(0x100) is None
    assert claims.renew(held.tokens) == ({}, [0x100])
    assert claims.release([0x100], force=True, tokens=held.tokens) == []
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)") == original


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
def test_fork_mirrors_other_namespace_claims_read_only(hosts, monkeypatch, tmp_path, writer_ns):
    hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    claims.claim([0x100])
    original = _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)")
    reader = hosts("b")
    fork = tmp_path / "fork.git"
    _git(tmp_path, "init", "-q", "--bare", str(fork))
    _git(reader, "remote", "set-url", "origin", str(fork))
    _git(reader, "remote", "add", "upstream", str(hosts.origin))
    _git(reader, "config", "bfme.claimMirror", "upstream")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/" if writer_ns == "refs/claims/"
                        else "refs/claims/")
    assert claims.mirrored()[0x100]["owner"] == "a"
    assert claims.busy_rvas() == {0x100}
    assert claims.claim([0x100]) == ([], [0x100])
    assert _git(fork, "for-each-ref", "--format=%(refname)") == ""
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)") == original


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
def test_expired_primary_cannot_hide_live_other_namespace(hosts, monkeypatch, writer_ns):
    hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    claims.claim([0x100], ttl_hours=-1)
    hosts("b")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/" if writer_ns == "refs/claims/"
                        else "refs/claims/")
    assert claims.claim([0x100]) == ([0x100], [])
    hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    assert claims.active()[0x100]["owner"] == "b"
    assert claims.claim([0x100]) == ([], [0x100])


def test_custom_namespace_keeps_its_own_refs_and_observes_documented_namespaces(hosts, monkeypatch):
    hosts("a")
    claims.claim([0x100])
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/")
    claims.claim([0x200])
    reader = hosts("b")
    monkeypatch.setattr(claims, "NS", "refs/heads/private-claims/")
    assert claims.claim([0x100, 0x200, 0x300]) == ([0x300], [0x100, 0x200])
    assert set(claims.active()) == {0x100, 0x200, 0x300}
    assert set(claims._read_local(reader)) == {0x300}
    refs = _git(hosts.origin, "for-each-ref", "--format=%(refname)").splitlines()
    assert refs == ["refs/claims/0x00000100", "refs/heads/claims/0x00000200",
                    "refs/heads/private-claims/0x00000300"]


def test_failed_push_reread_refuses_a_new_other_namespace_holder(hosts, monkeypatch):
    reader = hosts("a")
    writer = hosts("b")
    hosts("a")
    real_git = claims._git
    raced = []

    def rejected(*args, **kwargs):
        if args[:1] == ("push",) and kwargs.get("cwd") in (None, reader):
            if not raced:
                raced.append(True)
                with monkeypatch.context() as context:
                    context.setattr(claims, "NS", "refs/heads/claims/")
                    assert claims.claim([0x100], who="b", root=writer) == ([0x100], [])
            return subprocess.CompletedProcess(args, 1, "", "fixture transport failure")
        return real_git(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", rejected)
    result = claims.claim([0x100])
    assert result == ([], [0x100]) and result.unconfirmed == []
    assert claims.active()[0x100]["owner"] == "b"


@pytest.mark.parametrize("upstream", [False, True])
def test_other_namespace_snapshots_are_private_to_worktrees(hosts, monkeypatch, tmp_path, upstream):
    primary = hosts("a")
    _git(primary, "commit", "-q", "--allow-empty", "-m", "worktree fixture")
    sibling = tmp_path / "sibling"
    _git(primary, "worktree", "add", "-q", "--detach", str(sibling), "HEAD")
    writer = hosts("b")

    def claim_more(rvas):
        with monkeypatch.context() as context:
            context.setattr(claims, "NS", "refs/heads/claims/")
            return claims.claim(rvas, root=writer)

    assert claim_more([0x100]) == ([0x100], [])
    seen = claims.MIRROR_SEEN if upstream else claims.SEEN
    if upstream:
        _git(primary, "config", "bfme.claimMirror", "origin")

    def refresh(root):
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        return claims.mirrored(root) if upstream else claims.active(root)

    assert set(refresh(primary)) == {0x100}
    assert set(refresh(sibling)) == {0x100}
    before = claims._read_visible(sibling, seen)
    assert claim_more([0x200]) == ([0x200], [])
    assert set(refresh(primary)) == {0x100, 0x200}
    assert claims._read_visible(sibling, seen) == before
    assert set(refresh(sibling)) == {0x100, 0x200}

    with monkeypatch.context() as context:
        context.setattr(claims, "NS", "refs/heads/claims/")
        assert claims.release([0x100], root=writer) == [0x100]
    assert set(refresh(primary)) == {0x200}
    assert set(claims.live(claims._read_visible(sibling, seen))) == {0x100, 0x200}
    assert set(refresh(sibling)) == {0x200}
# Round-3 regressions: all origins are the hosts fixture's local bare repository.
def _review_scope(monkeypatch):
    f = claims.file_key("Code/A.cpp")
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({0x200: (f, "class/C")}, {f: {"class/C"}}, {"class/C": {f}}))
    return f


def test_unrowed_body_keeps_source_lock_through_settlement_and_renewal(hosts, monkeypatch):
    root = hosts("a")
    f = claims.file_key("Code/New.cpp")
    result = claims.acquire([0xDEAD], work={f}, ttl_hours=1)
    assert claims.active()[0xDEAD]["locks"] == [0xDEAD, f]
    assert claims.lock_keys({0xDEAD}) == {0xDEAD, f}
    assert claims.release_orphans() == []
    old = claims.active()[f]["expires"]
    renewed, lost = claims.renew({0xDEAD: result.tokens[0xDEAD]}, ttl_hours=5)
    assert not lost and set(renewed) == {0xDEAD, f}
    assert claims.active()[f]["expires"] > old
    renewed, lost = claims.renew_held([0xDEAD], ttl_hours=6)
    assert not lost and set(renewed) == {0xDEAD, f}
    assert claims.active()[0xDEAD]["locks"] == [0xDEAD, f]
    renewed, lost = claims.renew({0xDEAD: result.tokens[0xDEAD]}, ttl_hours=7)
    assert not lost and set(renewed) == {0xDEAD, f}
    assert set(claims.release_work([0xDEAD])) == {0xDEAD, f}


def test_header_reserves_only_class_but_still_fences_member_files(hosts, monkeypatch):
    _review_scope(monkeypatch)
    hosts("a")
    result = claims.acquire(["class:C"])
    assert result.claimed == ["class/C"]
    assert set(claims.active()) == {"class/C"}
    hosts("b")
    result = claims.acquire([0x200])
    assert not result.claimed and result.refused == ["class/C"]
    assert set(claims.active()) == {"class/C"}


def test_acquire_rechecks_after_push_and_rolls_back_new_refs(hosts, monkeypatch):
    f = _review_scope(monkeypatch)
    peer = hosts("b")
    root = hosts("a")
    real = claims._git
    injected = []

    def git(*args, **kwargs):
        result = real(*args, **kwargs)
        if args[:2] == ("push", "-q") and kwargs.get("cwd") is None and not injected:
            injected.append(True)
            assert claims.claim([0x200], root=peer, who="b").claimed == [0x200]
        return result
    monkeypatch.setattr(claims, "_git", git)
    result = claims.acquire(["file:Code/A.cpp"])
    assert not result.claimed and result.refused == [0x200]
    assert claims.active() == {0x200: claims.active()[0x200]}
    assert claims.active()[0x200]["owner"] == "b"
    assert f not in claims.active()  # kills a missing rollback as well as a missing recheck


def test_acquire_rolls_back_claims_unavailable_partial_result(hosts, monkeypatch):
    hosts("a")
    real_claim = claims.claim

    def partial(targets, **kwargs):
        result = real_claim(list(targets)[:1], **kwargs)
        assert len(result.claimed) == 1  # a failure after only the first ref was accepted
        error = claims.ClaimsUnavailable("readback unavailable", claimed=result.claimed)
        error.tokens = result.tokens
        raise error
    monkeypatch.setattr(claims, "claim", partial)
    with pytest.raises(claims.ClaimsUnavailable) as caught:
        claims.acquire([0x1234], work={claims.file_key("Code/New.cpp")})
    assert caught.value.claimed == [] and not caught.value.unclean
    assert claims.active() == {}


def test_atomic_acquire_lost_race_has_one_push_and_one_readback(hosts, monkeypatch):
    peer = hosts("b")
    root = hosts("a")
    real = claims._git
    pushes, fetches, injected = [], [], []

    def git(*args, **kwargs):
        here = kwargs.get("cwd") in (None, root)
        if here and _listing(args):
            fetches.append(args)
        if here and args[:2] == ("push", "-q"):
            pushes.append(args)
            if not injected:
                injected.append(True)
                assert claims.claim(["file:Code/0.cpp"], root=peer, who="b").claimed
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    with claims.pick_snapshot():
        assert claims.busy_keys() == set()
        result = claims.acquire([f"file:Code/{i}.cpp" for i in range(30)])
    assert not result.claimed and result.refused
    assert len(pushes) == 1 and len(fetches) == 2
    assert set(claims.active()) == {claims.file_key("Code/0.cpp")}


def test_one_initial_fetch_is_shared_by_pick_and_settlement(hosts, monkeypatch):
    root = hosts("a")
    _git(root, "commit", "-q", "--allow-empty", "-m", "master")
    _git(root, "push", "-q", "origin", "HEAD:master")
    real = claims._git
    fetches = []

    def git(*args, **kwargs):
        if args[:1] == ("fetch",) or _listing(args):
            fetches.append(args)
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", git)
    with claims.pick_snapshot():
        assert claims.settle() == []
        assert claims.busy_keys() == set()
        assert claims.acquire([0x1234]).claimed == [0x1234]
    master = [a for a in fetches if "master" in " ".join(a)]
    claim_fetches = [a for a in fetches if _listing(a)]
    assert len(master) == 1
    assert len(claim_fetches) == 2  # one shared initial snapshot plus mandatory post-push recheck


def test_busy_keys_leave_own_file_siblings_available(hosts, monkeypatch):
    f = _review_scope(monkeypatch)
    hosts("a")
    assert claims.acquire([0x200]).claimed
    assert claims.busy_keys() == set() and claims.busy_rvas() == set()
    hosts("b")
    assert f in claims.busy_keys() and 0x200 in claims.busy_rvas()


def test_module_documents_mixed_client_limit():
    assert "Mixed old and new clients provide RVA-level exclusion" in claims.__doc__


def test_unreadable_post_push_snapshot_rolls_back_instead_of_serving(hosts, monkeypatch):
    hosts("a")
    real = claims._git
    pushed = []

    def git(*args, **kwargs):
        if pushed and _listing(args):
            return subprocess.CompletedProcess(args, 1, "", "snapshot unavailable")
        result = real(*args, **kwargs)
        if args[:2] == ("push", "-q"):
            pushed.append(True)
        return result
    monkeypatch.setattr(claims, "_git", git)
    with pytest.raises(claims.ClaimsUnavailable, match="post-push"):
        claims.acquire(["class:C"])
    monkeypatch.setattr(claims, "_git", real)
    assert claims.active() == {}


@pytest.mark.parametrize("phase", ["initial", "post-push", "release"])
@pytest.mark.parametrize("message", ["upload-pack: not our ref " + "0" * 40,
                                    "fatal: couldn't find remote ref refs/claims/0x00000100"])
def test_fetch_retries_deleted_advertisement_race(hosts, monkeypatch, capsys, phase, message):
    hosts("a")
    import next_work
    real = claims._git
    pushed, races, sleeps = [], [], []
    if phase == "release":
        assert claims.claim([0x100]).claimed == [0x100]

    def transport(*args, **kwargs):
        inject = phase != "post-push" or pushed
        if _listing(args) and inject and len(races) < 2:
            races.append(True)
            return subprocess.CompletedProcess(args, 128, "", message)
        result = real(*args, **kwargs)
        if args[:1] == ("push",) and result.returncode == 0:
            pushed.append(True)
        return result

    monkeypatch.setattr(claims, "_git", transport)
    own_sleep(monkeypatch, sleeps.append)
    if phase == "release":
        assert claims.release([0x100]) == [0x100]
    else:
        item = {"target_rva": "0x100", "function": "?f@@YAXXZ"}
        assert next_work.claim_choice([item], "race-test") == (item, [0x100])
        assert claims.release([0x100]) == [0x100]
    assert len(races) == len(sleeps) == 2 and all(delay > 0 for delay in sleeps)
    assert "without a shared claim" not in capsys.readouterr().err
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname)", "refs/claims/") == ""


def test_persistent_ref_race_does_not_enable_offline_pick(hosts, monkeypatch):
    hosts("a")
    import next_work
    real = claims._git
    fetches = []

    def transport(*args, **kwargs):
        if _listing(args):
            fetches.append(True)
            return subprocess.CompletedProcess(args, 128, "", "upload-pack: not our ref " + "0" * 40)
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", transport)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    with pytest.raises(SystemExit, match="origin reachable"):
        next_work.claim_choice([{"target_rva": "0x100", "function": "f"}], "race-test")
    assert len(fetches) == 5


@pytest.mark.parametrize("rollback_fails", [False, True])
@pytest.mark.parametrize("lost_reply", [False, True])
def test_lost_push_reply_and_readback_keep_tokens_or_rollback(hosts, monkeypatch, rollback_fails, lost_reply):
    hosts("a")
    real = claims._git
    accepted = []

    def transport(*args, **kwargs):
        if accepted and _listing(args):
            return subprocess.CompletedProcess(args, 128, "", "snapshot unavailable")
        if args[:1] == ("push",):
            if accepted and rollback_fails:
                return subprocess.CompletedProcess(args, 128, "", "push unavailable")
            result = real(*args, **kwargs)
            if not accepted and result.returncode == 0:
                accepted.append(True)
                if lost_reply:
                    return subprocess.CompletedProcess(args, 128, "", "reply lost after acceptance")
            return result
        return real(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", transport)
    monkeypatch.setattr(claims.time, "sleep", lambda _: None)
    with pytest.raises(claims.ClaimsUnavailable) as caught:
        claims.acquire([0x100])
    error = caught.value
    monkeypatch.setattr(claims, "_git", real)
    if rollback_fails:
        assert error.unclean and error.claimed == [0x100]
        assert claims.holds(0x100, error.tokens[0x100])
        assert claims.release(error.claimed, tokens=error.tokens) == [0x100]
    else:
        assert not error.unclean and error.claimed == []
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname)", "refs/claims/") == ""


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
@pytest.mark.parametrize("same_owner", [False, True])
@pytest.mark.parametrize("persisted_only", [False, True])
def test_foreign_namespace_file_locks_block_acquisition(hosts, monkeypatch, writer_ns,
                                                        same_owner, persisted_only):
    hosts("a")
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({}, {}, {}))
    monkeypatch.setattr(claims, "NS", writer_ns)
    f = claims.file_key("Code/Unrowed.cpp")
    # A persisted-only footprint tests clients that hold a class ref without
    # separate file refs. The other case tests acquire's lock-only file ref.
    targets = ["class:C"] if persisted_only else [0xDEAD]
    result = claims.acquire(targets, work={f})
    assert result.claimed
    original = _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)", writer_ns)
    hosts("b")
    monkeypatch.setattr(claims, "NS", "refs/heads/claims/" if writer_ns == "refs/claims/" else "refs/claims/")
    if same_owner:
        monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
    assert f in claims.busy_keys()
    assert f in claims.lock_keys({claims.key_of(targets[0])})
    assert claims.conflicts({f})
    blocked = claims.acquire([0xBEEF], work={f})
    assert not blocked.claimed and blocked.refused
    assert claims.renew(result.tokens) == ({}, sorted(result.tokens, key=claims._order))
    assert claims.release_orphans() == []
    assert claims.release(result.claimed, force=True, tokens=result.tokens) == []
    assert _git(hosts.origin, "for-each-ref", "--format=%(refname) %(objectname)", writer_ns) == original

    assert not claims.live(claims._read_local())  # branch rollback leaves expired tombstones


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
def test_foreign_namespace_persisted_lock_survives_same_key_shadow(hosts, monkeypatch, writer_ns):
    hosts("a")
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({}, {}, {}))
    monkeypatch.setattr(claims, "NS", writer_ns)
    own_file, foreign_file = claims.file_key("Code/Own.cpp"), claims.file_key("Code/Foreign.cpp")
    assert claims.claim([0x100], work_locks={own_file}, ttl_hours=8).claimed
    # Seed a concurrent foreign-namespace record directly; normal clients refuse
    # a pre-existing cross-namespace holder. Same owner must not authorize it.
    foreign_ns = "refs/heads/claims/" if writer_ns == "refs/claims/" else "refs/claims/"
    token = claims._record("a", 4, locks={foreign_file})
    _git(claims.ROOT, "push", "-q", "origin", f"{token}:{foreign_ns}0x00000100")
    assert claims.fetch()
    claims.active.cache_clear()
    assert foreign_file in claims.busy_keys()
    assert {own_file, foreign_file} <= claims.lock_keys({0x100})
    result = claims.acquire([0x200], work={foreign_file})
    assert not result.claimed
    assert claims.active()[0x100]["owner"] == "a"


@pytest.mark.parametrize("writer_ns", ["refs/claims/", "refs/heads/claims/"])
def test_post_push_foreign_namespace_lock_rolls_back_without_foreign_writes(hosts, monkeypatch, writer_ns):
    peer = hosts("b")
    root = hosts("a")
    monkeypatch.setattr(claims, "NS", writer_ns)
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({}, {}, {}))
    f = claims.file_key("Code/Race.cpp")
    real_git = claims._git
    injected = []
    foreign_ns = "refs/heads/claims/" if writer_ns == "refs/claims/" else "refs/claims/"

    def raced(*args, **kwargs):
        result = real_git(*args, **kwargs)
        if args[:2] == ("push", "-q") and kwargs.get("cwd") in (None, root) and not injected:
            injected.append(True)
            token = claims._record("a", 4, root=peer, locks={f})
            _git(peer, "push", "-q", "origin", f"{token}:{foreign_ns}class/C")
        return result

    monkeypatch.setattr(claims, "_git", raced)
    result = claims.acquire([0x100], work={f})
    assert not result.claimed and result.refused == ["class/C"]
    assert set(claims.active()) == {"class/C"}
    refs = _git(hosts.origin, "for-each-ref", "--format=%(refname) %(contents:subject)")
    assert foreign_ns + "class/C" in refs
    assert not claims.live(claims._read_local())


def test_a_claim_too_big_for_one_command_line_is_pushed_in_chunks(hosts, monkeypatch):
    """A merge scope of ~200 files and their rows overflowed Windows' command line in
    one push (2026-10-28): claims and releases go in budget-sized atomic chunks."""
    hosts("a")
    monkeypatch.setattr(claims, "ARG_BUDGET", 400)
    real, pushes = claims._git, []

    def git(*args, **kwargs):
        if args[:1] == ("push",):
            pushes.append(args)
        return real(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", git)
    keys = list(range(0x1000, 0x1000 + 40))
    assert claims.claim(keys).claimed == keys
    assert len(pushes) > 1
    assert all(len(" ".join(p)) < 1000 for p in pushes)
    pushes.clear()
    assert claims.release(keys) == keys
    assert len(pushes) > 1
    claims.fetch(claims.ROOT)
    assert not set(keys) & set(claims._read_local(claims.ROOT))


def test_an_all_or_nothing_claim_takes_back_its_earlier_chunks(hosts, monkeypatch):
    """A later chunk refused (a peer's push in between): the fresh refs the earlier
    chunks created are deleted again, so nothing of the scope stays claimed."""
    hosts("a")
    monkeypatch.setattr(claims, "ARG_BUDGET", 400)
    real, claim_pushes = claims._git, []
    contested = ":" + claims.ref_of(0x2027)          # in the last chunk; never accepted

    def git(*args, **kwargs):
        if args[:1] == ("push",) and any(a.endswith(contested) and not a.startswith(":") for a in args):
            claim_pushes.append(args)
            return subprocess.CompletedProcess(args, 1, "", "rejected")
        return real(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", git)
    keys = list(range(0x2000, 0x2028))
    result = claims.claim(keys, atomic_only=True)
    assert claim_pushes and result.claimed == []
    claims._invalidate_snapshot(claims.ROOT)
    claims.fetch(claims.ROOT)
    left = claims._read_local(claims.ROOT)
    assert not [k for k in keys if k in left and left[k][1].get("expires", 0) > 0
                and left[k][1].get("owner") == "a" and left[k][1].get("note") != "released"]


def test_git_stdin_is_sent_without_newline_translation(tmp_path):
    # text-mode stdin turned "\n" into "\r\n" on Windows, so `git fetch --stdin`
    # read "sha\r" as an invalid refspec and every claims read failed (2026-10-30)
    import hashlib
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    data = "one\ntwo\n"
    got = claims._git("hash-object", "--stdin", cwd=tmp_path, input_text=data)
    blob = b"blob %d\0" % len(data.encode()) + data.encode()
    assert got.returncode == 0
    assert got.stdout.strip() == hashlib.sha1(blob).hexdigest()
