"""next_work's Phase 2 structural tiers: stubs, consolidate, tu-approval, tu-evidence,
ms-headers, dx and stlport are default tiers with stated shares, built lazily, claimed through claim_choice and fallen
through like the debt queues; each builder reads only its owning tool's evidence."""
import argparse
import collections
import hashlib
import json
import random
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402
import next_work  # noqa: E402
import repair_queue as rq  # noqa: E402

STRUCTURAL = ("stubs", "consolidate", "tu-approval", "tu-evidence", "ms-headers", "dx", "stlport")


# ---- weights and order

def test_every_structural_tier_is_a_default_tier_with_a_share():
    assert next_work.STRUCTURAL_TIERS == STRUCTURAL
    assert set(STRUCTURAL) <= set(next_work.DEBT_TIERS) and next_work.DEBT_TIERS[0] == "repair"
    assert set(next_work.TIER_WEIGHTS) == set(next_work.DEBT_TIERS[1:])
    assert sum(next_work.TIER_WEIGHTS.values()) == 100
    assert all(next_work.TIER_WEIGHTS[name] > 0 for name in next_work.DEBT_TIERS[1:])
    assert next_work.TIER_WEIGHTS["link"] == max(next_work.TIER_WEIGHTS.values())      # still the largest share
    for naming in ("wb", "named", "similar"):                                           # on request only
        assert naming not in next_work.TIER_WEIGHTS and naming not in next_work.DEBT_TIERS
    assert set(rq.STRUCTURAL_QUEUES) == set(STRUCTURAL)
    assert len(next_work.DEBT_LABELS) == len(next_work.DEBT_TIERS)


def test_first_draw_shares_follow_the_weights(monkeypatch):
    monkeypatch.delenv("BFME_TIER_WEIGHTS", raising=False)
    monkeypatch.setenv("BFME_TIER_TUNING", "off")          # the priors; tools/tests/test_tier_tuning.py tunes
    rng = random.Random(20261025)
    firsts = collections.Counter()
    draws = 20000
    for _ in range(draws):
        order = next_work.debt_order(rng)
        assert order[0] == "repair" and sorted(order) == sorted(next_work.DEBT_TIERS)
        firsts[order[1]] += 1
    for name, weight in next_work.TIER_WEIGHTS.items():
        assert abs(firsts[name] / draws - weight / 100) < 0.015, (name, firsts[name])


def test_the_environment_overrides_any_subset(monkeypatch):
    monkeypatch.setenv("BFME_TIER_WEIGHTS", "consolidate=7,tu-approval=0,bogus=9,link=x")
    weights = next_work.tier_weights()
    assert weights["consolidate"] == 7 and weights["tu-approval"] == 0 and "bogus" not in weights
    assert weights["link"] == next_work.TIER_WEIGHTS["link"]                       # a malformed value is ignored
    only = ",".join(f"{name}=0" for name in next_work.DEBT_TIERS[1:] if name != "stubs") + ",stubs=1"
    monkeypatch.setenv("BFME_TIER_WEIGHTS", only)
    order = next_work.debt_order(random.Random(1))
    assert order[:2] == ["repair", "stubs"]                                       # weight 0: still tried, last
    assert order[2:] == [name for name in next_work.DEBT_TIERS[1:] if name != "stubs"]


# ---- lazy build, fallthrough and claims through the shared picker

class Queues:
    """repair_queue for next_work: every builder records itself."""

    def __init__(self, tmp_path, **queues):
        self.ROOT, self.queues = tmp_path, queues
        self.DEBT_QUEUES = {n: (f"{n}.txt", lambda n=n: (list(queues.get(n, [])), n))
                            for n in ("data", "header", "identity")}
        for n in self.DEBT_QUEUES:
            (tmp_path / f"{n}.txt").write_text("")
        self.STRUCTURAL_QUEUES = {n: (lambda n=n: (list(queues[n]), n) if n in queues
                                      else ([], f"{n} input absent: queue skipped")) for n in STRUCTURAL}

    def all_repair_items(self):
        return list(self.queues.get("repair", []))

    def link_items(self):
        return list(self.queues.get("link", [])), "link"


def item(tier, name, **kw):
    return dict({"tier": tier, "function": name, "source": f"Code/{name}.cpp", "target_rva": "", "size": 0,
                 "count": 3, "credit_note": "3 things", "why": "w", "pass_test": "t",
                 "claim": [f"file:Code/{name}.cpp"]}, **kw)


@pytest.fixture
def picker(tmp_path, monkeypatch):
    monkeypatch.setattr(next_work, "BUILT", [])
    monkeypatch.setattr(next_work, "_DEBT", {})
    monkeypatch.setattr(next_work, "SKIPPED", [])
    monkeypatch.setattr(next_work, "annotate_attempts", lambda pool: pool)
    monkeypatch.setattr(next_work.re_log, "is_dead_end", lambda *a, **k: False)
    monkeypatch.setattr(next_work.re_log, "is_deferred", lambda *a, **k: False)
    monkeypatch.setattr(claims, "work_keys", lambda rva=None, source=None, cls=None, root=None:
                        {claims.file_key(source)} if source else set())
    monkeypatch.setattr(claims, "lock_keys", lambda keys, root=None, records=None: set(keys))
    args = argparse.Namespace(shard=None, include_logged=False, claim=False)

    def run(order, busy=frozenset(), **queues):
        next_work.repair_queue = Queues(tmp_path, **queues)
        next_work.BUILT.clear()
        next_work._DEBT.clear()
        return next_work.pick_debt(order, args, set(busy))
    run.args = args
    return run


def test_structural_tiers_are_built_lazily_and_serve_their_items(picker):
    got = picker(["repair", "stubs", "consolidate"], stubs=[item("stubs", "S")], consolidate=[item("consolidate", "C")])
    assert got["name"] == "stubs" and got["label"] == "link-stub closure"
    assert next_work.BUILT == ["repair", "stubs"]                                   # consolidate never built


def test_an_absent_input_skips_with_a_note_and_falls_through(picker):
    got = picker(["repair", "tu-approval", "dx"], dx=[item("dx", "D")])
    assert got["name"] == "dx" and got["tried"] == ["repair", "tu-approval"]
    assert any(line.startswith("tu-approval:") and "skipped" in line for line in next_work.SKIPPED)


def test_a_claimed_out_structural_queue_falls_through(picker, monkeypatch):
    merges = [item("consolidate", "T1"), item("consolidate", "T2")]
    busy = {claims.file_key("Code/T1.cpp"), claims.file_key("Code/T2.cpp")}
    got = picker(["repair", "consolidate", "ms-headers"], busy=busy, consolidate=merges,
                 **{"ms-headers": [item("ms-headers", "M")]})
    assert got["name"] == "ms-headers" and got["tried"] == ["repair", "consolidate"]
    picker.args.claim = True                                                       # every claim lost to a peer
    monkeypatch.setattr(next_work, "claim_choice", lambda pool, label: (None, []) if label == "TU consolidation"
                        else (pool[0], ["x"]))
    got = picker(["repair", "consolidate", "ms-headers"], consolidate=merges, **{"ms-headers": [item("ms-headers", "M")]})
    picker.args.claim = False
    assert got["name"] == "ms-headers" and got["acquired"] == ["x"]


def test_claim_choice_takes_the_items_scopes(monkeypatch):
    calls = []

    def acquire(targets, work=(), note=""):
        calls.append((list(targets), note))
        return claims.ClaimResult([claims.key_of(t) for t in targets], [])
    monkeypatch.setattr(claims, "acquire", acquire)
    monkeypatch.setattr(claims, "lock_keys", lambda keys, root=None, records=None: set(keys))
    monkeypatch.setattr(claims, "work_keys", lambda *a, **k: set())
    merge = item("consolidate", "T", claim=["file:Code/T.cpp", "file:Code/D1.cpp", "file:Code/D2.cpp"])
    got, acquired = next_work.claim_choice.__wrapped__([merge], "TU consolidation") \
        if hasattr(next_work.claim_choice, "__wrapped__") else next_work.claim_choice([merge], "TU consolidation")
    assert got is merge and calls == [(merge["claim"], "next_work TU consolidation")]
    assert len(acquired) == 3


def test_a_structural_pick_prints_its_own_credit_not_bytes(capsys):
    meta = {"pool": 1}
    next_work.print_candidate("TU approval", item("tu-approval", "T", credit_note="5 proposed row(s) in 2 file(s)",
                                                  start="python3 tools/name_lane.py consolidate --under Code/"), meta)
    out = capsys.readouterr().out
    assert "start: python3 tools/name_lane.py consolidate --under Code/; done when" in out
    assert "fix it in" not in out                                                # the TU file may not exist yet
    assert "credit: 5 proposed row(s) in 2 file(s) (structural work" in out and "bytes" not in out
    assert "pass test: t" in out


def test_the_stlport_tier_claims_its_file_and_falls_through_when_a_peer_holds_it(picker, monkeypatch):
    files = [item("stlport", "S1"), item("stlport", "S2")]
    got = picker(["repair", "stlport"], stlport=files)
    assert got["name"] == "stlport" and got["label"] == "STLport 4.6 migration"
    busy = {claims.file_key("Code/S1.cpp"), claims.file_key("Code/S2.cpp")}
    got = picker(["repair", "stlport", "dx"], busy=busy, stlport=files, dx=[item("dx", "D")])
    assert got["name"] == "dx" and got["tried"] == ["repair", "stlport"]
    picker.args.claim = True
    taken = []

    def claim_choice(pool, label):
        taken.append((label, next_work.claim_targets(pool[0])))
        return pool[0], ["held"]
    monkeypatch.setattr(next_work, "claim_choice", claim_choice)
    got = picker(["repair", "stlport"], stlport=[item("stlport", "S1")])
    picker.args.claim = False
    assert got["acquired"] == ["held"] and taken == [("STLport 4.6 migration", ["file:Code/S1.cpp"])]


def test_draw_weight_follows_the_queue_s_own_ranking():
    small = next_work.candidate_weight({"tier": "consolidate", "count": 1})
    big = next_work.candidate_weight({"tier": "consolidate", "count": 12})
    capped = next_work.candidate_weight({"tier": "stubs", "count": 400})
    assert big == 12 * small and capped == 16 * small


def test_stlport_draw_weighs_rows_only_for_a_clean_unit_trial():
    unit = {"tier": "stlport", "count": 12, "lead": "unit", "trial_fails": 0}
    one = next_work.candidate_weight(dict(unit, count=1))
    assert next_work.candidate_weight(unit) == 12 * one
    assert next_work.candidate_weight(dict(unit, count=40)) == 16 * one
    assert next_work.candidate_weight(dict(unit, lead="library")) == one     # never compiled under 4.6
    assert next_work.candidate_weight(dict(unit, trial_fails=3)) == one      # a row of it failed the trial


# ---- the builders

def git(cwd, *a):
    return subprocess.run(["git", *a], cwd=cwd, capture_output=True, text=True, check=True).stdout.strip()


def obj_name(source):
    stem = "_".join(Path(source).with_suffix("").parts)
    return "".join(("^" + c.lower()) if c.isupper() else c for c in stem).lower() + ".obj"


@pytest.fixture
def cycle(tmp_path, monkeypatch):
    """A repository with a ledger, and a link-cycle output measured at its HEAD."""
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    (root / "Code").mkdir()
    for name in ("A", "B"):
        (root / "Code" / f"{name}.cpp").write_text("")
    (root / "reverse" / "functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "?a@@YAXXZ,,0x00001000,4,Code/A.cpp,matched,\n?b@@YAXXZ,,0x00001010,4,Code/B.cpp,matched,\n")
    (root / "reverse" / "symbols.csv").write_text("name,address,notes\n?pinned@@3HA,0x00002000,\n")
    git(root, "init", "-q", "-b", "master")
    git(root, "add", ".")
    git(root, "-c", "user.name=t", "-c", "user.email=t@example.invalid", "commit", "-qm", "x")
    out = tmp_path / "cycle"
    (out / "zzobj").mkdir(parents=True)
    stubs = ["?draw@Widget@@QAEXXZ", "?size@Widget@@QBEHXZ", "?free@@YAXXZ", "?pinned@@3HA", "?orphan@@YAXXZ"]
    objects_digest = "d" * 64
    (out / "stubs.json").write_text(json.dumps({"objects_digest": objects_digest, "value": stubs}))
    (out / "receipt.json").write_text(json.dumps({
        "commit": git(root, "rev-parse", "HEAD"), "date_utc": "2026-10-25 16:00:00", "dirty": False,
        "objects_digest": objects_digest,
        "stubs_sha256": hashlib.sha256(json.dumps(stubs, sort_keys=True).encode()).hexdigest()}))
    (out / "zzobj" / "names.json").write_text(json.dumps({"names": {"o00000.obj": obj_name("Code/A.cpp"),
                                                                    "o00001.obj": obj_name("Code/B.cpp")}}))
    (out / "pass1.log").write_text(
        'o00000.obj : error LNK2019: unresolved external symbol "public: void __thiscall Widget::draw(void)" '
        '(?draw@Widget@@QAEXXZ) referenced in function _x\n'
        'o00001.obj : error LNK2001: unresolved external symbol "public: int __thiscall Widget::size(void)const " '
        '(?size@Widget@@QBEHXZ)\n'
        'o00001.obj : error LNK2001: unresolved external symbol "void __cdecl free(void)" (?free@@YAXXZ)\n'
        'o00001.obj : error LNK2001: unresolved external symbol "?notastub@@YAXXZ" (?notastub@@YAXXZ)\n')
    monkeypatch.setattr(rq, "ROOT", root)
    return root, out


def test_stub_items_group_members_by_class_and_claim_what_the_fix_touches(cycle):
    root, out = cycle
    items, note = rq.stub_items(out)
    by = {i["function"]: i for i in items}
    widget = by["Widget (2 stub(s))"]
    assert widget["claim"] == ["class:Widget", "file:Code/A.cpp", "file:Code/B.cpp"] and widget["count"] == 2 and "credit" not in widget and widget["tier"] == "stubs"
    assert widget["stubs"] == ["?draw@Widget@@QAEXXZ", "?size@Widget@@QBEHXZ"]
    assert by["?free@@YAXXZ"]["claim"] == ["file:Code/B.cpp"] and by["?free@@YAXXZ"]["source"] == "Code/B.cpp"
    assert by["?pinned@@3HA"]["claim"] == ["0x00002000"] and by["?pinned@@3HA"]["target_rva"] == "0x00002000"
    assert "?orphan@@YAXXZ" not in by and "1 free symbol(s) with no referencing unit or pin not served" in note
    assert "5 stubbed symbol(s)" in note and "2026-10-25" in note
    assert all(next_work.claim_targets(i) for i in items)                         # every item is claimable


def test_a_class_stub_group_locks_every_referencing_file_against_a_second_owner(cycle, tmp_path, monkeypatch):
    """Against a local bare origin: the Widget group (members referenced from A.cpp and B.cpp)
    and the free symbol referenced from B.cpp share B.cpp, so two owners never hold both,
    whichever acquires first."""
    root, out = cycle
    items, _ = rq.stub_items(out)
    by = {i["function"]: i for i in items}
    widget, free = by["Widget (2 stub(s))"], by["?free@@YAXXZ"]
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({}, {}, {}))   # Widget has no ledger member
    for name in ("BFME_RUN_ID", "BFME_CLAIMS"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])

    def seat(origin, name):
        clone = origin.parent / name
        if not clone.exists():
            git(origin.parent, "init", "-q", str(clone))
            git(clone, "remote", "add", "origin", str(origin))
        monkeypatch.setattr(claims, "ROOT", clone)
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()

    for order, (one, two) in enumerate(((widget, free), (free, widget))):
        (tmp_path / f"o{order}").mkdir()
        origin = tmp_path / f"o{order}" / "origin.git"
        git(tmp_path, "init", "-q", "--bare", str(origin))
        seat(origin, "a")
        got, held = next_work.claim_choice([one], "stubs")
        assert got is one and held
        seat(origin, "b")
        got, held = next_work.claim_choice([two], "stubs")
        assert got is None and not held                                           # B.cpp is a's


def test_an_stlport_file_claim_locks_the_file_against_a_second_owner(tmp_path, monkeypatch):
    """Against a local bare origin: the first seat's --claim holds file:SOURCE; a second
    seat drawing the same file is refused, and the tier then has nothing to give it."""
    move = item("stlport", "Move")
    monkeypatch.setattr(claims, "scope_index", lambda root=None: ({}, {}, {}))
    for name in ("BFME_RUN_ID", "BFME_CLAIMS"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    for name in ("a", "b"):
        clone = tmp_path / name
        git(tmp_path, "init", "-q", str(clone))
        git(clone, "remote", "add", "origin", str(origin))
        monkeypatch.setattr(claims, "ROOT", clone)
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        got, held = next_work.claim_choice([move], "STLport 4.6 migration")
        if name == "a":
            assert got is move and held
        else:
            assert got is None and not held


def test_stub_items_refuse_a_list_that_is_not_the_receipts(cycle):
    root, out = cycle
    stubs = json.loads((out / "stubs.json").read_text())
    stubs["value"].append("?extra@@YAXXZ")
    (out / "stubs.json").write_text(json.dumps(stubs))
    items, note = rq.stub_items(out)
    assert items == [] and "not the one receipt.json names" in note and "skipped" in note


def test_stub_items_refuse_a_cycle_measured_off_this_history(cycle):
    root, out = cycle
    receipt = json.loads((out / "receipt.json").read_text())
    receipt["commit"] = "0123456789abcdef0123456789abcdef01234567"
    (out / "receipt.json").write_text(json.dumps(receipt))
    items, note = rq.stub_items(out)
    assert items == [] and "not HEAD or an ancestor" in note


def test_stub_items_skip_without_a_cycle(tmp_path):
    items, note = rq.stub_items(tmp_path / "none")
    assert items == [] and "stub-closure queue skipped" in note


def test_consolidation_items_claim_the_merges_file_footprint(tmp_path, monkeypatch):
    import tu_skeleton
    (tmp_path / "reverse").mkdir()
    (tmp_path / rq.TU_MAP).write_text("")
    monkeypatch.setattr(rq, "ROOT", tmp_path)
    monkeypatch.setattr(tu_skeleton, "queue_entries", lambda under="", root=None: [
        {"tu": "Code/T.cpp", "removes": 2, "rows": 5, "mixed": 1, "refused": 0, "keys": []}])
    monkeypatch.setattr(tu_skeleton.claims, "_blocking_records", lambda root=None: iter(()))
    monkeypatch.setattr(tu_skeleton, "skeleton", lambda tu: [])
    monkeypatch.setattr(tu_skeleton, "donors", lambda tu, sk: ({"Code/T.cpp": [], "Code/D1.cpp": [],
                                                                "Code/D2.cpp": []}, {}, {}))
    items, note = rq.consolidation_items()
    (merge,) = items
    assert merge["claim"] == ["file:Code/D1.cpp", "file:Code/D2.cpp", "file:Code/T.cpp"]
    assert merge["count"] == 2 and "tu_skeleton.py --merge Code/T.cpp" in merge["pass_test"]
    assert merge["start"].startswith("python3 tools/name_lane.py consolidate --under Code/")


def test_tu_approval_items_name_what_blocks_approval_and_claim_the_tu(tmp_path, monkeypatch):
    import tu_skeleton
    (tmp_path / "reverse").mkdir()
    (tmp_path / rq.TU_MAP).write_text("")
    for name in ("A", "B", "C"):
        (tmp_path / f"Code/{name}.cpp").parent.mkdir(exist_ok=True)
        (tmp_path / f"Code/{name}.cpp").write_text("")
    monkeypatch.setattr(rq, "ROOT", tmp_path)
    row = lambda tu, src, by="N", ev="", conf="proposed": {"tu": tu, "source": src, "by": by, "evidence": ev,  # noqa: E731
                                                          "confidence": conf, "kind": "code"}
    monkeypatch.setattr(tu_skeleton, "map_rows", lambda: [
        row("Code/X.cpp", "Code/A.cpp", "Z", "Z=Code/X.cpp noncontiguous"),
        row("Code/X.cpp", "Code/B.cpp", "C", "noncontiguous"),
        row("Code/Y.cpp", "Code/C.cpp"),
        row("Code/Y.cpp", "Code/C.cpp", "C"),
        row("Code/Z.cpp", "Code/A.cpp", "F", "", "approved")])
    items, note = rq.tu_approval_items()
    by = {i["function"]: i for i in items}
    assert set(by) == {"Code/X.cpp", "Code/Y.cpp"}                                # approved TUs are not served
    assert by["Code/X.cpp"]["check"] == "noncontiguous" and by["Code/X.cpp"]["count"] == 2
    assert by["Code/Y.cpp"]["check"] in ("unanchored", "brackets") and by["Code/Y.cpp"]["rows"] == 2
    assert by["Code/X.cpp"]["claim"] == ["file:Code/X.cpp"]
    assert "tu_skeleton.py --plan Code/X.cpp" in by["Code/X.cpp"]["pass_test"]
    assert items[0]["function"] == "Code/X.cpp"                                   # more files first


def test_ms_header_and_dx_items_carry_a_file_claim_and_a_reason(tmp_path, monkeypatch):
    import dx_migration
    import ms_header_audit
    (tmp_path / "reverse").mkdir()
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/A.cpp").write_text("")
    (tmp_path / rq.MS_HEADER_QUEUE).write_text("")
    (tmp_path / rq.DX_QUEUE).write_text("")
    monkeypatch.setattr(rq, "ROOT", tmp_path)
    monkeypatch.setattr(ms_header_audit, "read_queue", lambda path: [
        {"file": "Code/A.cpp", "class": "adapt", "defs": "4", "headers": "<windows.h>", "names": "x",
         "platformsdk": "no", "closure": "", "note": ""}])
    monkeypatch.setattr(dx_migration, "servable", lambda: [
        {"source": "Code/A.cpp", "class": "mechanical", "matched_rows": "7", "edits": "d3d8.h->d3d9.h"},
        {"source": "Code/Gone.cpp", "class": "mechanical", "matched_rows": "1", "edits": ""}])
    (ms,), _ = rq.ms_header_queue_items()
    assert ms["claim"] == ["file:Code/A.cpp"] and ms["count"] == 4 and "<windows.h>" in ms["why"]
    (dx,), _ = rq.dx_items()                                                      # a vanished unit is not served
    assert dx["claim"] == ["file:Code/A.cpp"] and dx["count"] == 7 and "d3d8.h->d3d9.h" in dx["why"]
    for item in (ms, dx):                         # the start names the claimed file, never another picker
        assert "in Code/A.cpp only" in item["start"] and "./build.sh Code/A.cpp" in item["start"]
        assert " next" not in item["start"] and "--class" not in item["start"]


def test_stlport_items_serve_the_trial_queue_with_the_move_and_a_file_claim(tmp_path, monkeypatch):
    import stlport_trial
    (tmp_path / "reverse").mkdir()
    (tmp_path / "Code").mkdir()
    (tmp_path / rq.STLPORT_TRIAL).write_text("")
    (tmp_path / "Code/A.cpp").write_text("// cl: /O2 /Ireference/shims/bfmealloc /DX\n// stlport\n")
    (tmp_path / "Code/B.cpp").write_text("// stlport\n")
    monkeypatch.setattr(rq, "ROOT", tmp_path)
    alloc = "?allocate@?$allocator@PAUX@@@_STL@@QBEPAPAUX@@IPBX@Z"
    monkeypatch.setattr(stlport_trial, "queue_files", lambda: [
        {"source": "Code/B.cpp", "rows": [{"name": alloc}], "bytes": 60, "knobs": ["adapt"], "fails": 2,
         "lead": "library"},
        {"source": "Code/Gone.cpp", "rows": [{"name": "g"}], "bytes": 50, "knobs": [], "fails": 0, "lead": "unit"},
        {"source": "Code/A.cpp", "rows": [{"name": "f"}, {"name": "h"}], "bytes": 40, "knobs": ["-shim"],
         "fails": 0, "lead": "unit"}])
    items, note = rq.stlport_items()
    assert [i["source"] for i in items] == ["Code/A.cpp", "Code/B.cpp"]          # vanished not served; clean first
    a, b = items
    assert a["tier"] == "stlport" and a["claim"] == ["file:Code/A.cpp"] and a["count"] == 2
    assert a["check"] == "unit trial +-shim" and "2 row(s) (40 B)" in a["why"] and "40 B" in a["credit_note"]
    for got, source in ((a, "Code/A.cpp"), (b, "Code/B.cpp")):  # the lane's own move, on the claimed file only
        assert got["start"].startswith(f"in {source} only: change its `// stlport` line to `// stlport46`")
        assert f"./build.sh {source} (every row in the file" in got["start"]
        assert (f"python3 tools/add_match.py <name> <rva> <size> {source} --replace-existing --notes "
                '"<its notes>; migrated=stlport-4.6"') in got["start"]
        assert " next" not in got["start"] and f"./build.sh {source}" in got["pass_test"]
    assert ("only if that fails, apply the trial's knob and rebuild: delete /Ireference/shims/bfmealloc from "
            "its `// cl:` line") in a["start"]
    assert a["start"].index("./build.sh") < a["start"].index("delete /I") < a["start"].index("add_match")
    assert b["start"].index("drop the 4.5.3-only `const`") < b["start"].index("./build.sh")   # adapt always applies
    assert f"rename {alloc} to the non-const 4.6 mangling" in b["start"] and "only if" not in b["start"]
    assert b["check"] == "library lead +adapt" and "2 other row(s) of the file failed the trial" in b["why"]
    assert "2 file(s), 3 trial row(s)" in note


def test_stlport_items_skip_without_the_trial_report(tmp_path, monkeypatch):
    monkeypatch.setattr(rq, "ROOT", tmp_path)
    assert rq.stlport_items() == ([], f"{rq.STLPORT_TRIAL} absent: STLport 4.6 queue skipped")
