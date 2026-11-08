"""pin_consistency --audit: existing pins re-judged against the row at their address.

pin_admission's one-address-one-identity rule (and its fold proof) runs only
when a pin is added. A pin admitted earlier keeps lending its address to every
caller of its name: 0x000365F0 carried list<FXNugget*>'s copy constructor over
StringBase<char>'s, and FXList's copy constructor matched through it
(LINK-629). These tests pin down what the audit must do:

  * judge only a real name stacked on an address whose rows carry another real
    name (placeholders on either side are not identities);
  * replay a recorded fold-proof= source before guessing one from the census;
  * read a wrong body as DIFFERS, not as an inconclusive proof;
  * report worst first, callers named, and never fail the run (shadow).
"""
import importlib.util
import os
import pickle
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")
pin_consistency = _load("pin_consistency")

OWNER = "??0?$StringBase@D@@AAE@ABV0@@Z"
WRONG = "??0?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAE@ABV01@@Z"
FOLD = "??0AsciiStringWI@@QAE@ABV0@@Z"
CALLER = "??0FXList@@QAE@ABV0@@Z"


def row(name, rva, source="Code/A.cpp", status="matched", notes=""):
    return {"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}", "target_size": "66",
            "source": source, "status": status, "notes": notes}


def pin(name, rva, notes=""):
    return {"name": name, "address": f"0x{rva:08X}", "notes": notes}


class FakeIndex:
    def __init__(self, sources=None, callers=None):
        self._sources, self._callers = sources or {}, callers or {}

    def sources(self, name):
        return list(self._sources.get(name, ()))

    def matched_callers(self, name):
        return sorted(self._callers.get(name, ()))


def test_only_real_names_stacked_on_real_names_are_judged():
    rows = [row(OWNER, 0x365F0), row("?Rva00012345@@YAXXZ", 0x12345), row("?own@@YAXXZ", 0x20000)]
    pins = [pin(WRONG, 0x365F0),                       # real on real: judged
            pin("?Rva000365F0@@YAXXZ", 0x365F0),       # placeholder pin: adds no identity
            pin("?named@@YAXXZ", 0x12345),             # the row there is a placeholder
            pin("?own@@YAXXZ", 0x20000),               # its own row
            pin("?free@@YAXXZ", 0x30000)]              # no row at all
    found = pin_consistency.stacked_pins(pins, rows)
    assert [(p["name"], rva, others) for p, rva, others in found] == [(WRONG, 0x365F0, [OWNER])]


@pytest.mark.parametrize("problems, verdict", [
    ([], "PROVEN"),
    (["Code/A.cpp's X differs from retail 0x000365F0 at +0x1d"], "DIFFERS"),
    (["Code/A.cpp compiles X to 88 bytes; the ledger body at 0x000365F0 is 66"], "DIFFERS"),
    (["X's relocations are not those of the ledger body at 0x000365F0: ..."], "DIFFERS-RELOC"),
    (["X already has its own address 0x00030830; an ICF fold ..."], "IDENTITY-ELSEWHERE"),
    (["X: unresolved callees ['?y@@YAXXZ']"], "INCONCLUSIVE"),
])
def test_verdict_reads_the_first_refusal(problems, verdict):
    assert pin_consistency.audit_verdict(problems) == verdict


def test_a_recorded_fold_proof_source_is_replayed_first():
    seen = []

    def prove(p, rva):
        seen.append(p["notes"])
        return []
    rows = [row(OWNER, 0x365F0)]
    pins = [pin(FOLD, 0x365F0, "folds with the StringBase copy; fold-proof=Code/Recorded.cpp")]
    index = FakeIndex(sources={FOLD: ["Code/Census.cpp"]})
    findings = pin_consistency.audit(pins, rows, index, prove)
    assert seen == ["fold-proof=Code/Recorded.cpp"]
    assert findings[0]["verdict"] == "PROVEN" and findings[0]["fold_proof_noted"]


def test_a_name_no_unit_defines_is_reported_without_a_proof():
    def prove(p, rva):
        raise AssertionError("nothing to compile")
    findings = pin_consistency.audit([pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], FakeIndex(), prove)
    assert findings[0]["verdict"] == "NO-DEFINING-OBJECT"


def test_wrong_bodies_come_first_with_their_matched_callers():
    rows = [row(OWNER, 0x365F0), row("?releaseBuffer@?$StringBase@G@@AAEXXZ", 0x36E70)]
    pins = [pin(FOLD, 0x365F0), pin(WRONG, 0x365F0), pin("??1?$_List_base@X@@QAE@XZ", 0x36E70)]
    index = FakeIndex(sources={FOLD: ["Code/F.cpp"], WRONG: ["Code/FXList.cpp"],
                               "??1?$_List_base@X@@QAE@XZ": ["Code/FXList.cpp"]},
                      callers={WRONG: [CALLER]})
    verdicts = {FOLD: [], WRONG: ["Code/FXList.cpp's W differs from retail 0x000365F0 at +0x10"],
                "??1?$_List_base@X@@QAE@XZ": ["Code/FXList.cpp's L differs from retail 0x00036E70 at +0x2"]}
    findings = pin_consistency.audit(pins, rows, index, lambda p, rva: verdicts[p["name"]])
    assert [(f["name"], f["verdict"]) for f in findings] == [
        (WRONG, "DIFFERS"), ("??1?$_List_base@X@@QAE@XZ", "DIFFERS"), (FOLD, "PROVEN")]
    assert findings[0]["callers"] == [CALLER]


def test_a_proof_that_cannot_run_is_inconclusive_not_a_crash():
    def prove(p, rva):
        raise SystemExit("Code/F.cpp does not compile")
    findings = pin_consistency.audit([pin(FOLD, 0x365F0)], [row(OWNER, 0x365F0)],
                                     FakeIndex(sources={FOLD: ["Code/F.cpp"]}), prove)
    assert findings[0]["verdict"] == "INCONCLUSIVE"


def test_audit_is_shadow(monkeypatch, capsys):
    monkeypatch.setattr(pin_consistency, "audit", lambda limit=None: [
        {"name": WRONG, "address": "0x000365F0", "others": [OWNER], "fold_proof_noted": False,
         "source": "Code/FXList.cpp", "callers": [CALLER], "verdict": "DIFFERS",
         "problems": ["differs from retail"]}])
    assert pin_consistency.main(["--audit"]) == 0
    out = capsys.readouterr().out
    assert "DIFFERS  0x000365F0" in out and CALLER in out


def test_census_index_names_ledger_units_and_matched_callers(tmp_path):
    rows = [row(CALLER, 0x52BD3A, source="Code/FXList.cpp"),
            row("?unmatched@@YAXXZ", 0x1000, source="Code/Other.cpp", status="blocked")]
    fx = build.obj_path(build.ROOT / "Code/FXList.cpp").name
    index = {"objects": [fx, "^stranger.obj"],
             "comdat": {WRONG: [(0, "digest", "retail"), (1, "digest", "retail")]},
             "strong": {},
             "references": {"edges": {CALLER: {WRONG}, "?unmatched@@YAXXZ": {WRONG}}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex(rows, path)
    assert census.sources(WRONG) == ["Code/FXList.cpp"]
    assert census.matched_callers(WRONG) == [CALLER]


def test_a_missing_census_index_names_nothing(tmp_path):
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A)], tmp_path / "absent.pkl")
    assert census.sources(WRONG) == [] and census.matched_callers(WRONG) == []


def test_a_refusal_about_a_callee_is_marked_as_one():
    rows = [row(OWNER, 0x365F0)]
    pins = [pin(WRONG, 0x365F0), pin(FOLD, 0x365F0)]
    index = FakeIndex(sources={WRONG: ["Code/FXList.cpp"], FOLD: ["Code/F.cpp"]})
    verdicts = {WRONG: [f"Code/FXList.cpp compiles {WRONG} to 88 bytes; the ledger body at 0x000365F0 is 66"],
                FOLD: ["Code/F.cpp compiles ?callee@@YAXXZ to 9 bytes; the ledger body at 0x00001000 is 11"]}
    findings = {f["name"]: f for f in pin_consistency.audit(pins, rows, index, lambda p, rva: verdicts[p["name"]])}
    assert not findings[WRONG]["on_callee"] and findings[FOLD]["on_callee"]


def test_an_empty_census_index_leaves_pins_unjudged(tmp_path):
    path = tmp_path / "link_index.pkl"
    path.write_bytes(b"")
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A)], path)
    assert census.problem and census.sources(WRONG) == [] and census.matched_callers(WRONG) == []
    findings = pin_consistency.audit([pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], census,
                                     lambda p, rva: [])
    assert findings[0]["verdict"] == "NO-DEFINING-OBJECT"


def test_an_index_entry_outside_its_object_list_is_skipped(tmp_path):
    fx = build.obj_path(build.ROOT / "Code/FXList.cpp").name
    index = {"objects": [fx], "comdat": {WRONG: [(7, "d", "retail"), (0, "d", "retail")]},
             "strong": {WRONG: [3]}, "references": {"edges": {}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A, source="Code/FXList.cpp")], path)
    assert census.sources(WRONG) == ["Code/FXList.cpp"]


def test_the_proof_compiles_in_isolation_and_cleans_up(monkeypatch, tmp_path):
    real = tmp_path / "match"
    real.mkdir()
    monkeypatch.setattr(build, "BUILD_DIR", real)
    monkeypatch.delenv("BFME_OBJSTORE", raising=False)
    seen = {}

    def fake_proof(p, rva, rows, symbol_map, pins):
        out = build.obj_path(build.ROOT / "Code/F.cpp")
        seen["dir"], seen["store"] = out.parent, os.environ.get("BFME_OBJSTORE")
        out.write_bytes(b"obj")
        build._deps_sidecar(out).write_text("{}")
        return []
    import pin_admission
    monkeypatch.setattr(pin_admission, "fold_proof_problems", fake_proof)
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
    pins = [pin(FOLD, 0x365F0, "fold-proof=Code/F.cpp")]
    findings = pin_consistency.audit(pins, [row(OWNER, 0x365F0)], FakeIndex())
    assert findings[0]["verdict"] == "PROVEN"
    assert seen["dir"] != real and seen["store"] == "off"
    assert seen["dir"].parent == build.ROOT / "build" and seen["dir"].name.startswith("pin-audit-")
    assert not seen["dir"].exists()                     # removed
    assert list(real.iterdir()) == []                   # the shared cache is untouched
    assert build.BUILD_DIR == real and "BFME_OBJSTORE" not in os.environ


def test_isolation_is_undone_when_the_proof_fails(monkeypatch, tmp_path):
    real = tmp_path / "match"
    real.mkdir()
    monkeypatch.setattr(build, "BUILD_DIR", real)
    monkeypatch.setenv("BFME_OBJSTORE", "on")
    seen = {}

    def broken(p, rva, rows, symbol_map, pins):
        seen["dir"] = build.BUILD_DIR
        raise RuntimeError("compiler crashed")
    import pin_admission
    monkeypatch.setattr(pin_admission, "fold_proof_problems", broken)
    with pytest.raises(RuntimeError):
        pin_consistency.audit([pin(FOLD, 0x365F0, "fold-proof=Code/F.cpp")], [row(OWNER, 0x365F0)],
                              FakeIndex())
    assert not seen["dir"].exists() and build.BUILD_DIR == real
    assert os.environ["BFME_OBJSTORE"] == "on"


def test_a_current_object_is_seeded_into_the_scratch_cache(tmp_path):
    real, scratch = tmp_path / "match", tmp_path / "scratch"
    real.mkdir(); scratch.mkdir()
    name = build.obj_path(build.ROOT / "Code/F.cpp").name
    (real / name).write_bytes(b"obj")
    build._deps_sidecar(real / name).write_text("{}")
    pin_consistency.seed_isolated("Code/F.cpp", real, scratch)
    assert (scratch / name).read_bytes() == b"obj" and (real / name).exists()
