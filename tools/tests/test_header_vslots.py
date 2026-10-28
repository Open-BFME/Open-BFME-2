"""header_adopt_lane: a generated header declares the contract's virtual slots in slot order."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

BASE_HEADER = """class Base {
public:
    virtual ~Base() {}
    virtual void xfer(Xfer *x) = 0;
protected:
    const ModuleData *m_moduleData;
};
"""

DERIVED_VIEW = """class Derived : public Base
{
public:
    virtual ~Derived();
    virtual void onCapture(Player *a, Player *b) {}
    virtual NameKeyType getKey() const = 0;
    virtual void xfer(Xfer *x);
private:
    Object *m_object;
};
"""
# A view that copied the base into the class: its xfer is no override.
FLAT_VIEW = """class Derived
{
public:
    virtual void s00();
    virtual void xfer(Xfer *x) { }
    virtual void onCapture(Player *, Player *) {}
    virtual NameKeyType getKey() const = 0;
    const ModuleData *m_moduleData;
    Object *m_object;
};
"""


def contract(vslots, queue=(), bases=("Base",), inherited=2):
    return {"class": "Derived", "key": "class", "key_by": "bytes", "size": 12, "size_by": "majority",
            "bases": list(bases), "fields": [{"offset": 8, "size": 4, "kind": "P", "type": "Object*",
                                              "name": "m_object"}],
            "vslots": {str(k): {"member": m, "decided_by": "bytes"} for k, m in vslots.items()},
            "evidence": {"inherited": {"inherited_slots": inherited}}, "queue": list(queue)}


@pytest.fixture
def base_header(tmp_path, monkeypatch):
    (tmp_path / "Base.h").write_text(BASE_HEADER, encoding="utf-8")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "CONTRACTS", tmp_path / "contracts")
    return {"Base": "Base.h"}


def declare(c, views, known):
    return lane.slot_declarations(c, sorted(views), read=views.__getitem__, known=known)


def test_derived_class_declares_its_own_slots_in_order_and_overrides_its_bases(base_header, monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: base_header)
    c = contract({2: "onCapture(Player*,Player*)", 3: "getKey()"})
    views = {"a.cpp": DERIVED_VIEW, "b.cpp": DERIVED_VIEW, "flat.cpp": FLAT_VIEW}
    own, overrides, problems = declare(c, views, base_header)
    assert problems == []
    assert own == ["virtual void onCapture(Player *a, Player *b) {}", "virtual NameKeyType getKey() const = 0;"]
    assert overrides == ["virtual void xfer(Xfer *x);", "virtual ~Derived();"]
    text = lane.generate(c, "data", {"m": "virtual void s00();"}, "Derived.h", (own, overrides))
    body = text[text.index("class Derived"):]
    assert body.index("onCapture") < body.index("getKey") < body.index("xfer")
    assert "s00" not in text and '#include "Base.h"' in text


def test_inherited_slot_is_not_re_emitted(base_header):
    # Only the flattened view spells xfer: it copied the base, so it overrides nothing.
    c = contract({2: "onCapture(Player*,Player*)", 3: "getKey()"})
    own, overrides, problems = declare(c, {"flat.cpp": FLAT_VIEW}, base_header)
    assert problems == [] and overrides == []
    assert not any("xfer" in d or "s00" in d for d in own)


def test_pure_slot_keeps_its_purity_by_majority(base_header):
    pure = "class Derived : public Base { public: virtual NameKeyType getKey() const = 0; };\n"
    plain = "class Derived : public Base { public: virtual NameKeyType getKey() const; };\n"
    c = contract({2: "getKey()"})
    own, _, problems = declare(c, {"a.cpp": pure, "b.cpp": pure, "c.cpp": plain}, base_header)
    assert problems == [] and own == ["virtual NameKeyType getKey() const = 0;"]
    _, _, problems = declare(c, {"a.cpp": pure, "c.cpp": plain}, base_header)
    assert problems == ["slot2 getKey(): spellings tie"]


@pytest.mark.parametrize("vslots,queue,expected", [
    ({2: "onCapture(Player*,Player*)", 4: "getKey()"}, [], ["slot3 undecided"]),
    ({2: "onCapture(Player*,Player*)"}, [{"attribute": "slot3", "candidates": {}}], ["slot3 undecided"]),
    ({2: "onCapture(Player*,Player*)", 3: "missing()"}, [], ["slot3 missing(): no view spells it"]),
])
def test_undecided_slot_refuses_generation(base_header, vslots, queue, expected):
    own, _, problems = declare(contract(vslots, queue), {"a.cpp": DERIVED_VIEW}, base_header)
    assert problems == expected


def test_destructor_takes_its_target_slot_and_overloads_reverse():
    view = """class Solo {
public:
    virtual ~Solo() {}
    virtual void f(int a);
    virtual void f(float a);
    virtual int g();
};
"""
    c = contract({0: "__vecDelDtor(uint)", 1: "f(float)", 2: "f(int)", 3: "g()"}, bases=(), inherited=0)
    c["class"] = "Solo"
    own, overrides, problems = lane.slot_declarations(c, ["s.cpp"], read={"s.cpp": view}.__getitem__, known={})
    assert problems == [] and overrides == []
    # slot 1 f(float), slot 2 f(int): MSVC needs the group declared in reverse.
    assert own == ["virtual ~Solo() {}", "virtual void f(int a);", "virtual void f(float a);", "virtual int g();"]


def test_run_refuses_a_contract_with_an_undeclarable_slot(base_header, tmp_path, monkeypatch):
    import json
    import class_contract
    monkeypatch.setattr(class_contract, "CONTRACTS", tmp_path / "contracts")
    monkeypatch.setattr(class_contract, "census", lambda name: ["a.cpp"])
    monkeypatch.setattr(lane, "registered", lambda: base_header)
    (tmp_path / "a.cpp").write_text(DERIVED_VIEW, encoding="utf-8")
    path = class_contract.contract_path("Derived")
    path.parent.mkdir()
    path.write_text(json.dumps(contract({2: "onCapture(Player*,Player*)", 4: "getKey()"})), encoding="utf-8")
    args = type("A", (), {"name": "Derived", "header": "Derived.h", "generate": True, "sample": None, "seed": 1,
                          "jobs": 1, "variants": "data", "apply": False})()
    monkeypatch.setattr(lane, "tournament", lambda *a, **k: pytest.fail("generated despite an undecided slot"))
    assert lane.run(args) == 2


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
