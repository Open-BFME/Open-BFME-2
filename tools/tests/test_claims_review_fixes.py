"""Regressions from the 2026-10-09 review of ba6f8d1ebb (the claim lifecycle
port), adapted from its probes (build/claims_review_ba6f8d1ebb/
test_review_claims.py). Every case marked FINDING failed on ba6f8d1ebb.

Local bare repositories only (test_claims.hosts); every compile, gate and
add_match verification is mocked, and a mocked gate writes the dependency
receipt the real tools/build.py leaves (test_claims._verified).
"""
import concurrent.futures
import os
import socket
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

TESTS = Path(__file__).resolve().parent
sys.path[:0] = [str(TESTS.parent), str(TESTS)]
import claims  # noqa: E402
from test_claims import hosts, _git, _commit_ledger, _verified, _published_and_queued  # noqa: E402,F401

ROW = "?f@@YAXXZ,,0x00000100,16,Code/x.cpp,matched,model=m"
ROW2 = "?g@@YAXXZ,,0x00000200,16,Code/x.cpp,matched,model=m"


# ---- FINDING 1 (P1): a donor landing released verified, unpublished bodies ----

def _land_donor(a, monkeypatch, refuse=()):
    """bfme1_sweep land of one donor with bodies 0x100 and 0x200 into
    Code/x.cpp. add_match runs in-process (bfme1_sweep gives it
    BFME_CLAIMS=off); its byte gate passes and leaves a receipt, except for
    the RVAs in `refuse`, whose add_match fails. Returns do_land's code."""
    import add_match
    import bfme1_sweep
    _commit_ledger(a, [], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    ledger = a / claims.LEDGER
    ledger.write_bytes(ledger.read_bytes().replace(b"\r\n", b"\n"))
    donor_root = a / "reference/donor"
    (donor_root / "game").mkdir(parents=True)
    (donor_root / "game/donor.cpp").write_text("void f() {}\nvoid g() {}\n", encoding="utf-8")
    (a / "build.sh").write_text("MOCK ONLY\n", encoding="utf-8")
    entry = {"source": "game/donor.cpp", "copy_tier": "A", "copy_note": "clean",
             "policy": "available", "bodies": [
                 {"tier": "T1", "name": "?f@@YAXXZ", "bfme2_rva": 0x100, "size": 16, "pins": []},
                 {"tier": "T1", "name": "?g@@YAXXZ", "bfme2_rva": 0x200, "size": 16, "pins": []}]}
    monkeypatch.setattr(bfme1_sweep, "ROOT", a)
    monkeypatch.setattr(bfme1_sweep, "BFME1", donor_root)
    monkeypatch.setattr(bfme1_sweep, "BFME2_LEDGER", ledger)
    monkeypatch.setattr(bfme1_sweep, "BFME2_SYMBOLS", a / "symbols.csv")
    monkeypatch.setattr(bfme1_sweep, "load_matches", lambda: {})
    monkeypatch.setattr(bfme1_sweep, "group_files", lambda *x, **k: [entry])
    monkeypatch.setattr(bfme1_sweep, "near_candidates", lambda *x, **k: [])
    monkeypatch.setattr(bfme1_sweep, "find_entry", lambda *x, **k: entry)
    monkeypatch.setattr(bfme1_sweep, "bfme2_source_path", lambda source: "Code/x.cpp")
    monkeypatch.setattr(bfme1_sweep, "ledger_note", lambda body: "model=m")
    monkeypatch.setattr(add_match, "DEFAULT_ROOT", a)
    monkeypatch.setattr(add_match, "record_landing", lambda *x: None)
    real_run = subprocess.run

    def mocked(command, *args, **kwargs):
        if command[0] == "git":
            return real_run(command, *args, **kwargs)
        script = Path(command[1]).name if len(command) > 1 else ""
        if script == "add_match.py":
            if int(command[3], 16) in refuse:
                return subprocess.CompletedProcess(command, 1, "", "")
            with monkeypatch.context() as local:
                local.setattr(sys, "argv", command[1:])
                local.setenv("BFME_CLAIMS", kwargs["env"]["BFME_CLAIMS"])
                add_match.main()
        elif script == "build.py" or Path(command[0]).name == "build.sh":
            _verified(a, command[-1])               # the gate passes and leaves its receipt
        return subprocess.CompletedProcess(command, 0, "", "")   # every other gate: mocked

    monkeypatch.setattr(subprocess, "run", mocked)
    args = SimpleNamespace(dry_run=False, source=entry["source"], include_refused=False,
                           allow_icf=False, ignore_import_alias=False)
    return bfme1_sweep.do_land(args)


def test_donor_keeps_verified_unpublished_claims_until_origin_holds_them(hosts, monkeypatch):
    # FINDING 1: add_match ran with BFME_CLAIMS=off, so nothing was queued and
    # `finally: settle(acquired)` released both verified, unpushed bodies.
    a = hosts("a")
    assert _land_donor(a, monkeypatch) == 0
    text = (a / claims.LEDGER).read_text(encoding="utf-8")
    assert ROW in text and ROW2 in text
    assert {0x100, 0x200} <= set(claims.active()), "verified donor released before publication"
    assert sorted(e["rva"] for e in claims.pending()) == ["0x00000100", "0x00000200"]
    _git(a, "add", "Code/x.cpp", claims.LEDGER)
    _git(a, "commit", "-q", "-m", "land donor")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.settle() == [0x100, 0x200]
    assert claims.active() == {} and claims.pending() == []


def test_donor_releases_a_refused_body_and_keeps_the_landed_one(hosts, monkeypatch):
    a = hosts("a")
    assert _land_donor(a, monkeypatch, refuse={0x200}) == 1
    assert set(claims.active()) == {0x100}
    assert [e["rva"] for e in claims.pending()] == ["0x00000100"]


# ---- FINDING 2 (P1): dependency equality ignored what the compile read ----

def test_a_stale_header_the_compile_read_holds_the_claim(hosts):
    # FINDING 2a: `origin/master...HEAD` (three dots) dropped an upstream-only
    # header change; the landing verified against VERSION 1, origin holds 2.
    a = hosts("a")
    _commit_ledger(a, [ROW], "base", {"Code/x.cpp": '#include "x.h"\nvoid f() {}\n',
                                      "Code/x.h": "#define VERSION 1\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    b = hosts("b")
    _git(b, "pull", "-q", "origin", "master")
    _commit_ledger(b, [ROW], "peer header", {"Code/x.h": "#define VERSION 2\n"})
    _git(b, "push", "-q", "origin", "HEAD:refs/heads/master")
    hosts("a")
    _git(a, "fetch", "-q", "origin")
    claims.claim([0x100])
    _verified(a, "Code/x.cpp", ["Code/x.h"])        # the compile read VERSION 1
    claims.queue_landed(0x100, ROW)
    assert set(claims.pending()[0]["deps"]) == {"Code/x.cpp", "Code/x.h"}
    released, waiting = claims.release_landed()
    assert released == [] and waiting == [0x100], \
        "released although the verified header differs on origin"


def _with_submodule(a):
    sub = a / "reference/open-bfme-1"
    sub.mkdir(parents=True)
    _git(sub, "init", "-q")
    _git(sub, "config", "user.name", "sub")
    _git(sub, "config", "user.email", "sub@example.com")
    (sub / "x.h").write_text("#define VERSION 1\n", encoding="utf-8")
    _git(sub, "add", "x.h")
    _git(sub, "commit", "-q", "-m", "base")
    _git(a, "add", "reference/open-bfme-1")
    _commit_ledger(a, [ROW], "base", {
        "Code/x.cpp": '#include "../reference/open-bfme-1/x.h"\nvoid f() {}\n'})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    return sub


def test_a_dirty_submodule_header_holds_the_claim(hosts):
    # FINDING 2b: a gitlink dependency was reduced to the submodule's
    # unchanged HEAD, ignoring the modified header the compile read.
    a = hosts("a")
    sub = _with_submodule(a)
    (sub / "x.h").write_text("#define VERSION 2\n", encoding="utf-8")
    _verified(a, "Code/x.cpp", ["reference/open-bfme-1/x.h"])
    claims.queue_landed(0x100, ROW)
    entry = claims.pending()[0]
    assert entry["deps_truncated"] and "x.h" in entry["deps_unproven"]
    released, _ = claims.release_landed()
    assert released == [], "dirty header reduced to the unchanged gitlink HEAD"


def test_a_clean_submodule_header_settles_by_the_gitlink(hosts):
    a = hosts("a")
    sub = _with_submodule(a)
    _verified(a, "Code/x.cpp", ["reference/open-bfme-1/x.h"])
    claims.queue_landed(0x100, ROW)
    head = _git(sub, "rev-parse", "HEAD").strip()
    assert claims.pending()[0]["deps"]["reference/open-bfme-1"] == head
    assert claims.release_landed() == ([0x100], [])


def test_receipt_inputs_that_cannot_be_proven_fail_closed(hosts):
    a = hosts("a")
    _commit_ledger(a, [ROW], "base", {"Code/x.cpp": "void f() {}\n", "Code/x.h": "1\n"})
    assert claims.landing_deps("Code/x.cpp", a)[1].startswith("no readable build receipt")
    _verified(a, "Code/x.cpp", ["Code/x.h"])
    (a / "Code/x.h").write_text("2\n", encoding="utf-8")                # edited after the compile
    assert "changed since" in claims.landing_deps("Code/x.cpp", a)[1]
    _verified(a, "Code/x.cpp", ["Code/x.h"])
    (a / "Code/x.cpp").write_text("void f() { 2; }\n", encoding="utf-8")
    assert "another revision" in claims.landing_deps("Code/x.cpp", a)[1]


def test_a_receipt_records_only_repository_content(hosts, tmp_path):
    # an ignored, generated header and a host file outside the checkout are
    # not origin's to hold; on Windows cl reports the spelling #include asked for
    a = hosts("a")
    (a / ".gitignore").write_text("gen/\n", encoding="utf-8")
    _commit_ledger(a, [ROW], "base", {"Code/x.cpp": "void f() {}\n", "Code/Inc/X.h": "1\n",
                                      ".gitignore": "gen/\n"})
    (a / "gen").mkdir()
    (a / "gen/shim.h").write_text("shim\n", encoding="utf-8")
    host = tmp_path / "host.h"
    host.write_text("host\n", encoding="utf-8")
    spelled = os.path.join("code", "inc", "x.h") if os.name == "nt" else "Code/Inc/X.h"
    _verified(a, "Code/x.cpp", [spelled, "gen/shim.h", str(host)])
    deps, why = claims.landing_deps("Code/x.cpp", a)
    assert why == "" and set(deps) == {"Code/x.cpp", "Code/Inc/X.h"}


def test_the_receipt_path_is_the_one_build_writes():
    import build
    source = "Code/GameEngine/Source/Common/INI.cpp"
    assert claims.receipt_path(source, build.ROOT) == \
        build.obj_path(build.ROOT / source).with_suffix(".deps.json")


# ---- FINDING 3 (P1): the offline fallback discarded known peer refusals ----

def _peer_holds_0x200_and_pushes_fail(hosts, monkeypatch):
    hosts("b")
    claims.claim([0x200])
    a = hosts("a")
    real_git = claims._git

    def failing_push(*args, **kwargs):
        if args[0] == "push":
            return subprocess.CompletedProcess(args, 1, "", "claim push unavailable")
        return real_git(*args, **kwargs)
    monkeypatch.setattr(claims, "_git", failing_push)
    return a


def test_an_unavailable_claim_names_the_bodies_a_peer_holds(hosts, monkeypatch):
    _peer_holds_0x200_and_pushes_fail(hosts, monkeypatch)
    with pytest.raises(claims.ClaimsUnavailable) as raised:
        claims.claim([0x100, 0x200])
    assert raised.value.refused == [0x200] and raised.value.claimed == []


def test_the_donor_fallback_never_lands_a_body_a_peer_holds(hosts, monkeypatch):
    import bfme1_sweep
    _peer_holds_0x200_and_pushes_fail(hosts, monkeypatch)
    entry = {"source": "game/donor.cpp", "bodies": [{"tier": "T1", "bfme2_rva": 0x100},
                                                    {"tier": "T1", "bfme2_rva": 0x200}]}
    monkeypatch.setattr(bfme1_sweep, "load_matches", lambda: {})
    monkeypatch.setattr(bfme1_sweep, "group_files", lambda *x, **k: [entry])
    monkeypatch.setattr(bfme1_sweep, "near_candidates", lambda *x, **k: [])
    monkeypatch.setattr(bfme1_sweep, "find_entry", lambda *x, **k: entry)
    attempted = []
    monkeypatch.setattr(bfme1_sweep, "_do_land", lambda *x, **k: attempted.append(1) or 0)
    args = SimpleNamespace(dry_run=False, source=entry["source"], include_refused=False,
                           allow_icf=False)
    with pytest.raises(SystemExit, match="0x00000200"):
        bfme1_sweep.do_land(args)
    assert attempted == [], "fallback discarded a positively known peer refusal"


def _offline_except_known(peer_held):
    def claim(rvas, **_kwargs):
        rva = rvas[0]
        raise claims.ClaimsUnavailable("claims: offline", refused=[rva] if rva in peer_held else [])
    return claim


def test_the_pickers_fallback_skips_a_known_peer_claim(monkeypatch):
    import next_work
    import list_naked_candidates as naked_queue
    monkeypatch.setattr(claims, "claim", _offline_except_known({0x100}))
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    work = [{"target_rva": "0x00000100"}, {"target_rva": "0x00000200"}]
    assert next_work.claim_choice(work, "test") == (work[1], [])
    monkeypatch.setattr(naked_queue, "select_candidate",
                        lambda candidates: (candidates[0], {"pool": len(candidates)}))
    naked = [{"rva": "0x00000100"}, {"rva": "0x00000200"}]
    assert naked_queue.claim_choice(naked) == (naked[1], {"pool": 1}, [])


def test_the_permute_fallback_skips_a_known_peer_claim(tmp_path, monkeypatch):
    import permute
    monkeypatch.setattr(permute, "OUT", tmp_path / "permute")
    monkeypatch.setattr(permute, "queue", lambda min_score=0.9: [
        (0.95, 16, "0x00000100", "?f@@YAXXZ"), (0.95, 16, "0x00000200", "?g@@YAXXZ")])
    monkeypatch.setattr(claims, "busy_rvas", lambda root=None: set())

    def offline(rvas, **_kwargs):
        raise claims.ClaimsUnavailable("claims: offline", refused=[0x200])
    monkeypatch.setattr(claims, "claim", offline)
    monkeypatch.setattr(claims, "release", lambda *a, **k: [])
    ran = []
    monkeypatch.setattr(permute, "permute", lambda rva, minutes: ran.append(rva) or {"rva": rva})
    monkeypatch.setattr(permute, "wb_note", lambda rva: None)
    monkeypatch.setattr(concurrent.futures, "ProcessPoolExecutor", concurrent.futures.ThreadPoolExecutor)
    assert permute.main(["--next", "2"]) == 0
    assert ran == ["0x00000100"]


# ---- FINDING 4 (P2): a failed release destroyed the retry's evidence ----

def test_a_failed_release_keeps_the_landing_for_a_retry(hosts, monkeypatch):
    a = hosts("a")
    _published_and_queued(a)
    real_release = claims.release
    monkeypatch.setattr(claims, "release", lambda *x, **k: [])
    assert claims.release_landed() == ([], [0x100])
    monkeypatch.setattr(claims, "release", real_release)
    assert claims.release_landed()[0] == [0x100], "retry lost its landing evidence"
    assert claims.pending() == []


def test_a_renewal_that_wins_the_release_race_keeps_the_landing(hosts, monkeypatch):
    a = hosts("a")
    old = _published_and_queued(a)
    real_release = claims.release

    def renewed_first(rvas, **kwargs):
        claims.renew(old.tokens)            # the heartbeat rotates the token: the CAS fails
        return real_release(rvas, **kwargs)
    monkeypatch.setattr(claims, "release", renewed_first)
    assert claims.release_landed()[0] == []
    assert len(claims.pending()) == 1
    monkeypatch.setattr(claims, "release", real_release)
    assert claims.release_landed() == ([0x100], [])


def test_a_landing_whose_claim_another_lease_holds_is_dropped(hosts):
    a = hosts("a")
    _published_and_queued(a)
    claims.release([0x100])
    hosts("b")
    claims.claim([0x100])
    hosts("a")
    assert claims.release_landed()[0] == []
    assert claims.pending() == [] and claims.active()[0x100]["owner"] == "b"


# ---- FINDING 5 (P2): a re-claim orphaned the queued landing ----

def test_a_reclaim_keeps_the_lease_of_a_queued_landing(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    old = claims.claim([0x100])
    _commit_ledger(a, [ROW], "local", {"Code/x.cpp": "void f() {}\n"})
    _verified(a, "Code/x.cpp")
    claims.queue_landed(0x100, ROW)
    refreshed = claims.claim([0x100])                # how AGENTS.md said to extend a claim
    assert refreshed.leases == old.leases and refreshed.tokens != old.tokens
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed()[0] == [0x100], "claim renewal changed the landing lease"


def test_renew_cli_extends_only_your_claims_and_keeps_the_lease(hosts):
    a = hosts("a")
    old = _published_and_queued(a)
    hosts("b")
    claims.claim([0x200])
    hosts("a")
    before = claims.active()[0x100]["expires"]
    assert claims.main(["renew", "0x100", "0x200"]) == 1          # 0x200 is b's
    live = claims.active()
    assert live[0x200]["owner"] == "b" and live[0x100]["lease"] == old.leases[0x100]
    assert live[0x100]["expires"] >= before
    assert claims.main(["renew", "0x100"]) == 0
    assert claims.release_landed() == ([0x100], [])


# ---- FINDING 6 (P2): the upgrade stranded legacy default ownership ----

@pytest.fixture
def default_owner(hosts, monkeypatch):
    """Checkout a with no explicit owner: (its root, its pre-upgrade owner)."""
    a = hosts("a")
    monkeypatch.delenv("BFME_CLAIM_OWNER")
    return a, f"a@{socket.gethostname()}"


def test_the_default_owner_releases_its_legacy_claim(default_owner):
    # FINDING 6: the default owner became <user>@<host>/<checkout hash>, and a
    # claim taken under the old <user>@<host> could be neither renewed nor released
    a, legacy = default_owner
    got = claims.claim([0x100], who=legacy)          # taken before the upgrade
    assert claims.claim([0x100]).refused == [0x100]  # claim() does not adopt it
    assert claims.release([0x100]) == [0x100], "upgrade treats its old claim as a peer"
    assert claims.renew(got.tokens) == ({}, [0x100])
    assert claims.claim([0x100]).claimed == [0x100]
    assert claims.legacy_owner(a) == legacy and claims.owner(a) != legacy


def test_renew_migrates_a_legacy_claim_and_keeps_its_lease(default_owner):
    a, legacy = default_owner
    got = claims.claim([0x100], who=legacy)
    assert claims.main(["renew", "0x100"]) == 0
    info = claims.active()[0x100]
    assert info["owner"] == claims.owner(a) and info["lease"] == got.leases[0x100]


def test_the_alias_never_reaches_another_users_or_a_per_checkout_claim(default_owner, monkeypatch):
    a, legacy = default_owner
    claims.claim([0x100], who=f"b@{socket.gethostname()}")          # another user's legacy claim
    claims.claim([0x200])                                            # a's per-checkout claim
    claims.claim([0x300], who=legacy)                                # a's pre-upgrade claim
    b = claims.ROOT.parent / "b"
    _git(b, "config", "user.name", "a")              # a sibling checkout of the same user and host
    monkeypatch.setattr(claims, "ROOT", b)
    claims.active.cache_clear()
    assert claims.legacy_owner(b) == legacy and claims.owner(b) != claims.owner(a)
    assert claims.release([0x100, 0x200]) == []
    assert claims.renew_held([0x100, 0x200])[0] == {}
    # the documented tradeoff: the sibling shares the pre-upgrade name, as it
    # always did, so it can end that claim -- only that one
    assert claims.release([0x300]) == [0x300]
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat")   # an explicit owner has no legacy alias
    assert claims.legacy_owner(b) is None
