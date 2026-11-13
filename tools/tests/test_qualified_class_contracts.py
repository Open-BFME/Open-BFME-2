"""Qualified private views keep their identity through contract/header adoption."""
import json
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract
import class_layouts
import class_views
import header_adopt_lane as lane


@pytest.fixture(autouse=True)
def no_builds(monkeypatch):
    """No test compiles anything: the generator's owner and emission builds (build_units) are recorded only."""
    built = []
    monkeypatch.setattr(lane, "build_units", lambda sources: built.extend(sources))
    return built

NAME = "StrategicHUD::BattlePromptArmyPanelMovieClip::Impl"
VIEW = f"""class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl : public Base {{
public:
    void SetSelected(bool);
private:
    bool selected;
}};
class Independent {{ int x; }};
"""


def test_full_scope_survives_both_view_readers():
    assert set(class_views.class_bodies(VIEW)) == {NAME, "Independent"}
    assert set(class_layouts.class_bodies(VIEW)) == {NAME, "Independent"}
    assert "StrategicHUD" not in class_views.class_bodies(VIEW)
    assert lane.body_span(VIEW, "StrategicHUD") is None
    assert lane.body_span(VIEW, NAME) is not None
    replaced = lane.swap(VIEW, [NAME], "ArmyPanelClip.h")
    assert "bool selected" not in replaced
    assert "class Independent" in replaced
    assert '#include "ArmyPanelClip.h"' in replaced


def test_census_does_not_treat_scope_prefix_as_a_class(tmp_path, monkeypatch):
    (tmp_path / "clip.cpp").write_text(VIEW, encoding="utf-8")
    monkeypatch.setattr(contract, "ROOT", tmp_path)
    rows = [{"source": "clip.cpp"}]
    assert contract.census(NAME, rows) == ["clip.cpp"]
    assert contract.census("StrategicHUD", rows) == []


def test_qualified_ledger_evidence_uses_msvc_scope_order():
    member = {"name": "?SetSelected@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEX_N@Z"}
    ctor = {"name": "??0Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAE@XZ"}
    unrelated = {"name": "?SetSelected@Impl@Other@@QAEX_N@Z"}
    assert contract.thiscall_rows(NAME, [member, ctor, unrelated]) == ([member], [ctor])
    pointer = {"name": "?use@@YAXPAVImpl@BattlePromptArmyPanelMovieClip@StrategicHUD@@@Z"}
    assert contract.ledger_key(NAME, [pointer]) == {"class": 1}
    assert contract.thiscall_rows("Independent", [{"name": "?f@Independent@@QAEXXZ"}])[0]


@pytest.mark.parametrize("name", [NAME, "A::B", "A__B", "A%3A%3AB", "../A", "A/B", "A\\B", "CON", "NUL", "LPT1", "é"])
def test_contract_component_is_portable_and_stays_in_one_directory(name, tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path)
    path = contract.contract_path(name)
    assert path.parent == tmp_path
    assert not set('<>:"/\\|?*.') & set(path.stem)
    path.write_text("{}", encoding="utf-8")
    assert path.read_text(encoding="utf-8") == "{}"


def test_components_do_not_collide_and_simple_paths_stay_compatible():
    names = ["A::B", "A__B", "A%3A%3AB", "CON", "%43ON"]
    assert len({contract.portable_component(n) for n in names}) == len(names)
    assert contract.portable_component("Coord3D") == "Coord3D"
    with pytest.raises(ValueError):
        contract.portable_component("")


def test_adoption_reads_frozen_contract_and_writes_portable_report(tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path / "contracts")
    monkeypatch.setattr(lane, "SCRATCH", tmp_path / "reports")
    monkeypatch.setattr(contract, "census", lambda name: ["clip.cpp"])
    frozen = {"class": NAME, "queue": []}
    path = contract.contract_path(NAME)
    path.parent.mkdir()
    path.write_text(json.dumps(frozen), encoding="utf-8")
    def tournament(name, frozen_input, sources, header, variants, jobs, fixed_header):
        assert frozen_input == frozen
        assert fixed_header
        return {"registered": {"verdicts": {"clip.cpp": None}, "seconds": 0}}
    monkeypatch.setattr(lane, "tournament", tournament)
    args = SimpleNamespace(name=NAME, header="clip.h", generate=False, sample=None,
                           variants="data", jobs=1, apply=False)
    assert lane.run(args) == 0
    report = lane.SCRATCH / path.name
    assert json.loads(report.read_text(encoding="utf-8"))["passed"] == ["clip.cpp"]


def test_contract_command_freezes_qualified_identity_at_portable_path(tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "ROOT", tmp_path)
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path / "contracts")
    evidence = {"views": 1, "view_errors": 0, "zh": {}}
    decided = {"class": NAME, "key": "class", "key_by": "bytes", "size": 64,
               "size_by": "bytes", "bases": [], "bases_by": "bytes", "evidence": evidence,
               "fields": [], "vslots": {}, "queue": [], "sources": ["clip.cpp"]}
    monkeypatch.setattr(contract, "decide", lambda *args, **kwargs: decided)
    assert contract.main(["--class", NAME, "--write"]) == 0
    frozen = json.loads(contract.contract_path(NAME).read_text(encoding="utf-8"))
    assert frozen["class"] == NAME
    assert "sources" not in frozen


def test_qualified_class_key_rewrite_preserves_scope(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    before = "?use@@YAXPAUImpl@BattlePromptArmyPanelMovieClip@StrategicHUD@@@Z"
    ledger.write_text("name,source\n" + before + ",clip.cpp\n", encoding="utf-8")
    monkeypatch.setattr(lane, "LEDGER", ledger)
    # ledger_renames reports ([(old, new)], why): a row it cannot safely rewrite
    # blocks the whole unit rather than being half-flipped, so the refusal
    # travels with the renames.
    assert lane.ledger_renames("clip.cpp", NAME, "class") == (
        [(before, before.replace("PAUImpl", "PAVImpl"))], None)


COORD2D = {"size": 8, "bases": [], "fields": [[0, "x", "float", 4], [4, "y", "float", 4]]}
REGION2D = {"size": 16, "bases": [], "fields": [[0, "lo", "Coord2D", 8], [8, "hi", "Coord2D", 8]]}


def test_member_aggregates_vote_as_leaves_and_fold_back():
    every = {"Coord2D": COORD2D, "Region2D": REGION2D}
    # Without leaves a member aggregate stays one 8-byte field (the old,
    # retail-access-overridden shape: `float lo` at +0 with a 4-byte width).
    assert [f[3] for f in contract.flatten(REGION2D, every)] == ["lo", "hi"]
    flat = contract.flatten(REGION2D, every, leaves=True)
    assert [(o, s, k, n) for o, s, k, n, _ in flat] == [
        (0, 4, "f4", "lo.x"), (4, 4, "f4", "lo.y"), (8, 4, "f4", "hi.x"), (12, 4, "f4", "hi.y")]
    fields = [{"offset": o, "size": s, "kind": k, "type": t, "name": n, "decided_by": "retail-access", "views": 3}
              for o, s, k, n, t in flat]
    nested = [(0, 8, "Coord2D", "lo", "zh", contract.leaf_shape(COORD2D, every, 0)),
              (8, 8, "Coord2D", "hi", "zh", contract.leaf_shape(COORD2D, every, 8))]
    queue = []
    out = contract.regroup("Region2D", fields, nested, queue)
    assert [(f["offset"], f["kind"], f["name"]) for f in out] == [(0, "S:Coord2D", "lo"), (8, "S:Coord2D", "hi")]
    assert [m["name"] for m in out[0]["members"]] == ["x", "y"]
    assert queue == []
    # A dotted leaf no candidate explains is queued, never spelled.
    queue = []
    contract.regroup("Region2D", fields, nested[:1], queue)
    assert [q["attribute"] for q in queue] == ["nested@0x8", "nested@0xc"]


def test_empty_nested_candidate_is_skipped_not_crashed():
    # A view-declared aggregate can survive with no decided leaves; its empty
    # span used to pass the fold equality and crash max() (MilesAudioManager).
    fields = [{"offset": 8, "size": 4, "kind": "f4", "type": "float", "name": "x",
               "decided_by": "retail-access", "views": 1}]
    queue = []
    out = contract.regroup("EmptyNested", fields, [(0, 8, "Empty", "empty", "zh", [])], queue)
    assert out == fields
    assert queue == []


def test_generated_header_includes_nested_canonical_headers(tmp_path, monkeypatch):
    registry = tmp_path / "canonical_classes.csv"
    registry.write_text("class,header,notes\nCoord2D,Code/Lib/Coord2D.h,x\n", encoding="utf-8")
    monkeypatch.setattr(lane, "REGISTRY", registry)
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(contract, "ROOT", tmp_path)
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path / "contracts")
    region = {"class": "Region2D", "key": "struct", "key_by": "bytes", "size": 16, "size_by": "zh", "bases": [],
              "fields": [{"offset": 0, "size": 8, "kind": "S:Coord2D", "type": "Coord2D", "name": "lo"},
                         {"offset": 8, "size": 8, "kind": "S:Coord2D", "type": "Coord2D", "name": "hi"}]}
    text = lane.generate(region, "data", {}, "Code/Lib/Region2D.h")
    assert text.count('#include "Coord2D.h"') == 1
    assert "Coord2D lo;" in text and "Coord2D hi;" in text
    assert '#include "../Lib/Coord2D.h"' in lane.generate(region, "data", {}, "Code/Other/Region2D.h")
    copy = lane.generate(region, "data+ctor+copy", {}, "Code/Lib/Region2D.h")
    assert "Region2D() {}" in copy and "Region2D(const Region2D &that);" in copy
    assert "Region2D(const Region2D &that);" not in text

def decide_virtual_fixture(monkeypatch, tables, *, extra=False, tied=False):
    """Use compiled-view fixtures at the complete contract decision boundary."""
    slots = {"0": "a0()", "1": "a1()", "2": "__vecDelDtor(uint)"}
    if extra:
        slots["3"] = "extra()"
    first = {"size": 12, "key": "class", "bases": [], "vslots": slots}
    second = {**first, "vslots": {**slots}}
    if tied:
        second["vslots"]["0"] = "other()"
    layouts = {"one.cpp": first, "two.cpp": second}
    monkeypatch.setattr(class_layouts, "build_module", lambda: SimpleNamespace())
    monkeypatch.setattr(contract, "ledger_rows", lambda: [])
    monkeypatch.setattr(contract, "views", lambda *args: (layouts, {s: {} for s in layouts}))
    monkeypatch.setattr(contract, "flatten", lambda *args, **kwargs: [])
    monkeypatch.setattr(contract, "zh_layout", lambda *args: None)
    monkeypatch.setattr(contract, "retail_access", lambda *args: {})
    monkeypatch.setattr(contract, "witnesses", lambda *args: {})
    monkeypatch.setattr(contract, "retail_vtable", lambda *args: tables)
    return contract.decide("BaseA", sources=list(layouts), jobs=1)


@pytest.mark.parametrize("tables", [{}, {"0x862888": {"stores": 1, "slots": {}}}])
def test_unknown_vtable_inventory_does_not_invent_zero_slot_bound(monkeypatch, tables):
    # The live BaseA failure: a proven constructor store, but no vtables.tsv rows.
    result = decide_virtual_fixture(monkeypatch, tables)
    assert set(result["vslots"]) == {"0", "1", "2"}
    assert result["queue"] == []
    assert result["evidence"]["retail_vtables"] == tables


def test_known_vtable_bound_still_refuses_extra_source_slot(monkeypatch):
    tables = {"0x862888": {"stores": 1, "slots": {
        0: "__purecall", 1: "__purecall", 2: "scalar deleting destructor"}}}
    result = decide_virtual_fixture(monkeypatch, tables, extra=True)
    assert set(result["vslots"]) == {"0", "1", "2"}
    assert [item["attribute"] for item in result["queue"]] == ["slot3"]
    assert "beyond the retail vftable's 3 slots" in result["queue"][0]["why"]


def test_unknown_vtable_inventory_keeps_ambiguous_source_slots_queued(monkeypatch):
    tables = {"0x862888": {"stores": 1, "slots": {}}}
    result = decide_virtual_fixture(monkeypatch, tables, tied=True)
    assert set(result["vslots"]) == {"1", "2"}
    assert [item["attribute"] for item in result["queue"]] == ["slot0"]
    assert result["queue"][0]["candidates"] == {"a0()": 1, "other()": 1}
    assert "why" not in result["queue"][0]
