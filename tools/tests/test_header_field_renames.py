"""header_adopt_lane field renames: a unit adopting a canonical header speaks its field names."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

UNIT = """// cl: /O2
class Team;
class Object
{
public:
    int m_flags;
    char m_pad04[4];
    float m_speed;
    int getFlags() const { return m_flags; }
};
int flags(Object *o) { return o->m_flags + (int)o->m_speed; }
"""

HEADER = """#pragma once
class Thing { public: int m_status; int m_extra; };
class Object : public Thing { public: float m_moveSpeed; int getFlags() const; };
"""


def layout(fields, bases=(), size=12):
    return {"fwd": False, "key": "class", "size": size, "bases": [list(b) for b in bases],
            "fields": [list(f) for f in fields], "statics": [], "methods": [], "virtual": [], "vslots": {},
            "vfptr": False}


UNIT_LAYOUTS = {"Object": layout([(0, "m_flags", "int", 4), (4, "m_pad04", "char[4]", 4),
                                  (8, "m_speed", "float", 4)])}
HEADER_LAYOUTS = {"Thing": layout([(0, "m_status", "int", 4), (4, "m_extra", "int", 4)], size=8),
                  "Object": layout([(8, "m_moveSpeed", "float", 4)], bases=[("Thing", 0)])}


def compiler(unit=UNIT_LAYOUTS, header=HEADER_LAYOUTS, seen=None):
    def compile(source, text):
        if seen is not None:
            seen.append(text)
        if text is None:
            return unit
        assert lane.PROBE_FN in text
        return header
    return compile


def test_private_fields_take_the_canonical_names_through_bases():
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler())
    assert why is None
    assert mapping == {"m_flags": "m_status", "m_speed": "m_moveSpeed"}   # padding needs no counterpart


def test_the_probe_compiles_the_unit_only_up_to_its_view():
    seen = []
    lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(seen=seen))
    probe = seen[1]
    assert '#include "Object.h"' in probe and "class Team;" in probe
    assert "o->m_flags" not in probe and "m_speed" not in probe
    assert f"int {lane.PROBE_FN}(Object *p0)" in probe


def test_a_field_with_no_canonical_counterpart_is_refused():
    unit = dict(UNIT_LAYOUTS, Object=layout([(0, "m_flags", "short", 2), (8, "m_speed", "float", 4)]))
    text = UNIT.replace("int m_flags;", "short m_flags;").replace("char m_pad04[4];\n", "")
    mapping, why = lane.field_renames("u.cpp", text, ["Object"], "Object.h", compiler(unit=unit))
    assert mapping is None and "m_flags (+0x0, 2 bytes) has no canonical field" in why


def test_a_field_the_header_types_differently_is_refused():
    header = dict(HEADER_LAYOUTS, Object=layout([(8, "m_moveSpeed", "int", 4)], bases=[("Thing", 0)]))
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "is float; the canonical m_moveSpeed is int" in why


def test_a_rename_that_would_reach_another_class_is_refused():
    text = UNIT.replace("class Team;", "class Team { public: int m_flags; };")
    unit = dict(UNIT_LAYOUTS, Team=layout([(0, "m_flags", "int", 4)], size=4))
    mapping, why = lane.field_renames("u.cpp", text, ["Object"], "Object.h", compiler(unit=unit))
    assert mapping is None and "also a member of Team" in why


def test_a_view_nothing_lays_out_needs_no_probe():
    seen = []
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(unit={}, seen=seen))
    assert (mapping, why) == ({}, None) and seen == [None]


def test_a_failed_probe_is_the_units_verdict():
    def compile(source, text):
        if text is None:
            return UNIT_LAYOUTS
        raise RuntimeError("u.cpp: compile failed: C2011")
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compile)
    assert mapping is None and why.startswith("the header's layout: ") and "C2011" in why


def test_flat_fields_skip_virtual_bases():
    layouts = {"V": layout([(0, "m_v", "int", 4)], size=4),
               "D": layout([(4, "m_d", "int", 4)], bases=[("virtual V", -1)])}
    assert lane.flat_fields("D", layouts) == {(4, 4): ("m_d", "int")}


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "u.cpp").write_text(UNIT, encoding="latin-1", newline="")
    (tmp_path / "Code" / "Object.h").write_text(HEADER, encoding="latin-1", newline="")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "compile_text", compiler())
    monkeypatch.setattr(lane, "registered", lambda: {})
    gated = {}
    monkeypatch.setattr(lane, "gate_one", lambda s: gated.setdefault(s, (tmp_path / s).read_text()) and None)
    return tmp_path, gated


def test_swap_rewrites_the_units_field_references(tree):
    root, gated = tree
    source, why, text, renames = lane.try_unit("Code/u.cpp", ["Object", "Thing"], "Code/Object.h", "class")
    assert why is None and renames == []
    assert "return o->m_status + (int)o->m_moveSpeed;" in text and '#include "Object.h"' in text
    assert "class Object" not in text
    assert gated["Code/u.cpp"] == text                    # the gate judged the renamed unit
    assert (root / "Code" / "u.cpp").read_text() == UNIT    # and the unit was restored


def test_adopt_writes_passing_units_and_registers_nothing(tree, monkeypatch, capsys):
    root, _ = tree
    monkeypatch.setattr(lane, "register", lambda *a: pytest.fail("adopt must not register"))
    monkeypatch.setattr(lane, "write_queue", lambda *a: pytest.fail("adopt must not queue"))
    assert lane.adopt("Object", "Code/Object.h", ["Code/u.cpp"]) == 0
    assert (root / "Code" / "u.cpp").read_text() == UNIT
    assert "PASS Code/u.cpp (fields: m_flags -> m_status, m_speed -> m_moveSpeed)" in capsys.readouterr().out
    assert lane.adopt("Object", "Code/Object.h", ["Code/u.cpp"], apply=True) == 0
    assert "o->m_status" in (root / "Code" / "u.cpp").read_text()


def test_adopt_leaves_a_failing_unit_alone(tree, monkeypatch, capsys):
    root, _ = tree
    monkeypatch.setattr(lane, "gate_one", lambda s: "error C2039: 'getFlags'")
    assert lane.adopt("Object", "Code/Object.h", ["Code/u.cpp"], apply=True) == 1
    assert (root / "Code" / "u.cpp").read_text() == UNIT
    assert "FAIL Code/u.cpp: error C2039" in capsys.readouterr().out
