"""class_contract: a derived class's contract declares its own members and names its bases."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract  # noqa: E402
import header_adopt_lane as lane  # noqa: E402

# Base: a vfptr, two introducing slots and one field (sizeof 8).
BASE = {"fwd": False, "key": "class", "size": 8, "bases": [], "vfptr": True,
        "fields": [[4, "m_moduleData", "ModuleData*", 4]],
        "vslots": {"0": "__vecDelDtor(uint)", "1": "getKey()"}}
# Derived spelling the base: adds m_object at +8 and one slot of its own.
DERIVED = {"fwd": False, "key": "class", "size": 12, "bases": [["Base", 0]], "vfptr": False,
           "fields": [[8, "m_object", "Object*", 4]], "vslots": {"2": "onCapture()"}}
# The same class flattened: no base clause, the base's vfptr, field and slots copied in.
FLAT = {"fwd": False, "key": "class", "size": 12, "bases": [], "vfptr": True,
        "fields": [[4, "m_moduleData", "ModuleData*", 4], [8, "m_object", "Object*", 4]],
        "vslots": {"0": "s00()", "1": "s01()", "2": "onCapture()"}}
# A plain value type with no base: its contract must not change.
COORD = {"fwd": False, "key": "struct", "size": 12, "bases": [], "vfptr": False,
         "fields": [[0, "x", "float", 4], [4, "y", "float", 4], [8, "z", "float", 4]], "vslots": {}}


def decide(monkeypatch, name, views):
    """decide() over in-memory views: every retail and ZH evidence source empty."""
    got = {source: layout[name] for source, layout in views.items()}
    monkeypatch.setattr(contract.class_layouts, "build_module", lambda: object())
    monkeypatch.setattr(contract, "ledger_rows", lambda: [])
    monkeypatch.setattr(contract, "views", lambda n, sources, jobs=8: (got, dict(views)))
    monkeypatch.setattr(contract, "zh_layout", lambda n, builder: None)
    monkeypatch.setattr(contract, "retail_access", lambda n, rows, builder: {})
    monkeypatch.setattr(contract, "retail_vtable", lambda n, rows, builder: {})
    monkeypatch.setattr(contract, "witnesses", lambda n: {})
    return contract.decide(name, sources=sorted(views))


def test_derived_contract_names_its_base_and_declares_only_its_own_members(monkeypatch):
    views = {f"a{i}.cpp": {"Derived": DERIVED, "Base": BASE} for i in range(2)}
    views["flat.cpp"] = {"Derived": FLAT}
    got = decide(monkeypatch, "Derived", views)
    assert got["bases"] == ["Base"] and got["size"] == 12
    assert [(f["offset"], f["name"]) for f in got["fields"]] == [(8, "m_object")]
    assert got["vslots"] == {"2": {"member": "onCapture()", "decided_by": "bytes"}}
    assert got["queue"] == []
    assert got["evidence"]["inherited"] == {"inherited_spans": [[0, 8]], "inherited_slots": 2, "base_views": 2}


def test_flattened_view_no_longer_contests_the_inherited_slots(monkeypatch):
    # Before the fix the flattened view's s00/s01 tied the base's slots and queued them.
    views = {"a.cpp": {"Derived": DERIVED, "Base": BASE}, "flat.cpp": {"Derived": FLAT}}
    got = decide(monkeypatch, "Derived", views)
    assert not [q for q in got["queue"] if q["attribute"].startswith("slot")]
    assert all(f["kind"] != "VPTR" for f in got["fields"])


def test_class_without_bases_keeps_its_contract(monkeypatch):
    views = {f"c{i}.cpp": {"Coord3D": COORD} for i in range(3)}
    got = decide(monkeypatch, "Coord3D", views)
    assert got["bases"] == [] and got["size"] == 12
    assert [(f["offset"], f["size"], f["type"], f["name"]) for f in got["fields"]] == \
        [(0, 4, "float", "x"), (4, 4, "float", "y"), (8, 4, "float", "z")]
    assert got["evidence"]["inherited"] == {"inherited_spans": [], "inherited_slots": 0, "base_views": 0}
    flat = {"Base": [(0, 4, "VPTR", "__vfptr", "void*"), (4, 4, "P", "m_moduleData", "ModuleData*")]}
    own, slots, _, queue = contract.own_members("Base", [], {"Base": BASE}, flat, {"Base": {"Base": BASE}})
    assert queue == []
    assert own == flat and slots == {"Base": {0: "__vecDelDtor(uint)", 1: "getKey()"}}


def test_empty_base_occupies_nothing():
    empty = {"fwd": False, "key": "class", "size": 1, "bases": [], "vfptr": False, "fields": [], "vslots": {}}
    derived = {"bases": [["Empty", 0]], "fields": [[0, "m_x", "int", 4]]}
    assert contract.inherited_spans(derived, {"Empty": empty}) == []
    assert contract.inherited_spans({"bases": [["Base", 0], ["Empty", 8]]}, {"Base": BASE, "Empty": empty}) == [(0, 8)]


def test_secondary_base_vfptr_is_inherited():
    iface = {"fwd": False, "key": "class", "size": 4, "bases": [], "vfptr": True, "fields": [], "vslots": {"0": "f()"}}
    layout = {"bases": [["Base", 0], ["Iface", 8]]}
    assert contract.inherited_spans(layout, {"Base": BASE, "Iface": iface}) == [(0, 8), (8, 12)]
    assert contract.slot_count({"bases": [["Base", 0]], "vslots": {"2": "g()"}}, {"Base": BASE}) == 3


def test_lane_refuses_a_base_without_a_header_and_includes_registered_bases(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {"Base": "Code/Include/Base.h"})
    derived = {"class": "Derived", "key": "class", "key_by": "bytes", "size": 12, "size_by": "majority",
               "bases": ["Base"], "fields": [{"offset": 8, "size": 4, "kind": "P", "type": "Object*",
                                              "name": "m_object"}]}
    assert lane.unheadered_bases(derived) == []
    assert lane.unheadered_bases(dict(derived, bases=["Base", "Iface"])) == ["Iface"]
    text = lane.generate(derived, "data", {}, "Code/Include/Derived.h")
    assert '#include "Base.h"' in text and "class Derived : public Base {" in text
    assert "m_moduleData" not in text and "Object *m_object;" in text


def layout(size, fields=(), bases=(), slots=None, vfptr=False):
    return {"fwd": False, "key": "class", "size": size, "bases": [list(b) for b in bases], "fields": list(fields),
            "vslots": slots or {}, "vfptr": vfptr}


def decide_with(monkeypatch, views, tables=None, access=None):
    monkeypatch.setattr(contract, "retail_access", lambda n, rows, builder: access or {})
    got = decide(monkeypatch, "D", views)
    if tables is None:
        return got
    monkeypatch.setattr(contract, "retail_vtable", lambda n, rows, builder: tables)
    return contract.decide("D", sources=sorted(views))


@pytest.mark.parametrize("reverse", [False, True])
def test_disagreeing_base_extents_queue_in_either_order(monkeypatch, reverse):
    # One view's base ends at +12 with a float at +8; the other's base ends at +4
    # and the class's own int sits at +8. Neither may silently win by source order.
    big = layout(12, [(0, "b", "int", 4), (8, "base_extra", "float", 4)])
    small = layout(8, [(0, "b", "int", 4)])
    views = [("a.cpp", {"D": layout(12, bases=[("B", 0)]), "B": big}),
             ("b.cpp", {"D": layout(12, [(8, "own", "int", 4)], bases=[("B", 0)]), "B": small})]
    got = decide_with(monkeypatch, dict(reversed(views) if reverse else views), access={8: {4: 2}})
    attributes = [q["attribute"] for q in got["queue"]]
    assert "base-extent" in attributes and "field@0x8" in attributes
    assert got["evidence"]["inherited"]["inherited_spans"] == []


def test_flattened_leaf_the_base_does_not_declare_is_queued(monkeypatch):
    flat = dict(FLAT, fields=[[4, "m_other", "float", 4], [8, "m_object", "Object*", 4]])
    views = {"a.cpp": {"Derived": DERIVED, "Base": BASE}, "flat.cpp": {"Derived": flat}}
    got = decide(monkeypatch, "Derived", views)
    assert "inherited@0x4" in [q["attribute"] for q in got["queue"]]


def test_inherited_slots_are_judged_against_the_retail_vftable(monkeypatch):
    base = layout(4, slots={"0": "f()", "1": "g()", "2": "invented()"}, vfptr=True)
    views = {"a.cpp": {"D": layout(4, bases=[("B", 0)]), "B": base},
             "flat.cpp": {"D": layout(4, slots={"0": "f()", "1": "g()", "2": "invented()"}, vfptr=True)}}
    got = decide_with(monkeypatch, views, tables={"0x123": {"stores": 1, "slots": {"0": "f", "1": "g"}}})
    attributes = [q["attribute"] for q in got["queue"]]
    assert "slot2" in attributes and "base-slots" in attributes


def test_virtual_base_is_looked_up_and_included_by_its_class_name(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {"B": "Code/B.h"})
    derived = {"class": "D", "key": "class", "key_by": "bytes", "size": 8, "size_by": "majority",
               "bases": ["virtual B"], "fields": []}
    assert lane.unheadered_bases(derived) == []
    assert lane.nested_includes(derived, "Code/D.h") == ['#include "B.h"', ""]
    assert "class D : public virtual B {" in lane.generate(derived, "data", {}, "Code/D.h")


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
