"""header_adopt_lane field renames: a unit adopting a canonical header speaks its field names."""
import re
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
    assert mapping == {"Object": {"m_flags": "m_status", "m_speed": "m_moveSpeed"}}   # padding needs no counterpart


def test_the_probe_compiles_the_unit_only_up_to_its_view():
    seen = []
    lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(seen=seen))
    probe = seen[1]
    assert '#include "Object.h"' in probe and "class Team;" in probe
    assert "o->m_flags" not in probe and "m_speed" not in probe
    assert f"int {lane.PROBE_FN}(Object *p0)" in probe


def test_the_probe_carries_a_toolchain_marker_the_cut_dropped():
    # build.py reads `// platformsdk` from anywhere in the file; below the view it is cut away
    # with the body and the probe then compiles without <windows.h> (C1083).
    text = UNIT + "// platformsdk\n"
    probe = lane.probe_text(text, ["Object"], "Object.h")
    assert "// platformsdk" in probe and "o->m_flags" not in probe
    assert lane.lost_markers(text, UNIT) == ["// platformsdk"]


def test_a_marker_above_the_view_is_not_repeated():
    text = UNIT.replace("// cl: /O2\n", "// cl: /O2\n// platformsdk\n")
    probe = lane.probe_text(text, ["Object"], "Object.h")
    assert probe.count("// platformsdk") == 1
    assert lane.lost_markers(text, probe) == []


def test_the_stlport46_marker_is_carried_without_inventing_a_plain_one():
    text = UNIT + "// stlport46\n"
    probe = lane.probe_text(text, ["Object"], "Object.h")
    assert "// stlport46" in probe
    assert not re.search(r"(?m)^// stlport[ \t]*$", probe)


def test_a_unit_whose_markers_all_survive_the_cut_gains_nothing():
    assert lane.lost_markers(UNIT, UNIT) == []
    assert lane.probe_text(UNIT, ["Object"], "Object.h").count("//") == UNIT.count("//")


def test_a_field_with_no_canonical_counterpart_is_refused():
    unit = dict(UNIT_LAYOUTS, Object=layout([(0, "m_flags", "short", 2), (8, "m_speed", "float", 4)]))
    text = UNIT.replace("int m_flags;", "short m_flags;").replace("char m_pad04[4];\n", "")
    mapping, why = lane.field_renames("u.cpp", text, ["Object"], "Object.h", compiler(unit=unit))
    assert mapping is None and "m_flags (+0x0, 2 bytes) has no canonical field" in why


def test_a_field_the_header_types_differently_is_refused():
    header = dict(HEADER_LAYOUTS, Object=layout([(8, "m_moveSpeed", "int", 4)], bases=[("Thing", 0)]))
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "is float; the canonical Object::m_moveSpeed is int" in why


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
    assert lane.flat_fields("D", layouts) == {(4, 4): [("m_d", "int", "D")]}


# -- the vftable pointers a flat private view spells out and the canonical header does not

def test_vptr_offsets_finds_the_classs_own_pointer():
    layouts = {"C": dict(layout([(4, "m_a", "int", 4)], size=8), vfptr=True)}
    assert lane.vptr_offsets("C", layouts) == {0}


def test_vptr_offsets_finds_one_per_polymorphic_base():
    layouts = {"P": dict(layout([(4, "m_p", "int", 4)], size=8), vfptr=True),
               "I": dict(layout([], size=4), vfptr=True),
               "D": layout([(0x14, "m_d", "int", 4)], bases=[("P", 0), ("I", 0x10)], size=0x18)}
    assert lane.vptr_offsets("D", layouts) == {0, 0x10}


def test_vptr_offsets_skip_a_plain_base_and_a_virtual_one():
    layouts = {"V": dict(layout([], size=4), vfptr=True),
               "B": layout([(0, "m_b", "int", 4)], size=4),
               "D": layout([(4, "m_d", "int", 4)], bases=[("B", 0), ("virtual V", -1)], size=8)}
    assert lane.vptr_offsets("D", layouts) == set()


FLAT_UNIT = """// cl: /O2
class Object
{
public:
    const void *m_vtable;
    int m_flags;
};
int flags(Object *o) { return o->m_flags; }
"""

FLAT_UNIT_LAYOUTS = {"Object": layout([(0, "m_vtable", "const void *", 4),
                                       (4, "m_flags", "int", 4)], size=8)}
POLY_HEADER_LAYOUTS = {"Object": dict(layout([(4, "m_status", "int", 4)], size=8), vfptr=True)}


def test_a_view_spelling_out_the_compilers_vptr_adopts_a_polymorphic_header():
    mapping, why = lane.field_renames("u.cpp", FLAT_UNIT, ["Object"], "Object.h",
                                      compiler(unit=FLAT_UNIT_LAYOUTS, header=POLY_HEADER_LAYOUTS))
    assert why is None
    assert mapping == {"Object": {"m_flags": "m_status"}}   # the vptr member has no counterpart


def test_a_leading_pointer_is_still_refused_when_the_canonical_class_has_no_vptr():
    header = {"Object": layout([(4, "m_status", "int", 4)], size=8)}
    mapping, why = lane.field_renames("u.cpp", FLAT_UNIT, ["Object"], "Object.h",
                                      compiler(unit=FLAT_UNIT_LAYOUTS, header=header))
    assert mapping is None and "m_vtable (+0x0, 4 bytes) has no canonical field" in why


def test_a_field_too_small_for_a_pointer_at_a_vptr_offset_is_still_refused():
    unit = {"Object": layout([(0, "m_tag", "short", 2), (4, "m_flags", "int", 4)], size=8)}
    text = FLAT_UNIT.replace("const void *m_vtable;", "short m_tag;")
    mapping, why = lane.field_renames("u.cpp", text, ["Object"], "Object.h",
                                      compiler(unit=unit, header=POLY_HEADER_LAYOUTS))
    assert mapping is None and "m_tag (+0x0, 2 bytes) has no canonical field" in why


MULTI_UNIT = """// cl: /O2
class UpdateModule
{
public:
    const void *m_vtable;
    const void *m_data;
    int m_object;
    const void *m_p0C;
    const void *m_p10;
    int m_frame;
};
int frame(UpdateModule *u) { return u->m_frame; }
"""

MULTI_UNIT_LAYOUTS = {"UpdateModule": layout(
    [(0, "m_vtable", "const void *", 4), (4, "m_data", "const void *", 4),
     (8, "m_object", "int", 4), (0xC, "m_p0C", "const void *", 4),
     (0x10, "m_p10", "const void *", 4), (0x14, "m_frame", "int", 4)], size=0x18)}

MULTI_HEADER_LAYOUTS = {
    "BehaviorModuleInterface": dict(layout([], size=4), vfptr=True),
    "BehaviorModule": dict(layout([(4, "m_moduleData", "const void *", 4), (8, "m_object", "int", 4)],
                                  bases=[("BehaviorModuleInterface", 0xC)], size=0x10), vfptr=True),
    "UpdateModuleInterface": dict(layout([], size=4), vfptr=True),
    "UpdateModule": layout([(0x14, "m_nextCallFrameAndPhase", "int", 4)],
                           bases=[("BehaviorModule", 0), ("UpdateModuleInterface", 0x10)], size=0x18),
}


def test_the_three_vptrs_of_a_multiply_derived_view_need_no_counterpart():
    assert lane.vptr_offsets("UpdateModule", MULTI_HEADER_LAYOUTS) == {0, 0xC, 0x10}
    mapping, why = lane.field_renames("u.cpp", MULTI_UNIT, ["UpdateModule"], "UpdateModule.h",
                                      compiler(unit=MULTI_UNIT_LAYOUTS, header=MULTI_HEADER_LAYOUTS))
    assert why is None
    assert mapping == {"UpdateModule": {"m_data": "m_moduleData",
                                        "m_frame": "m_nextCallFrameAndPhase"}}


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
    assert "PASS Code/u.cpp (fields: Object::m_flags -> m_status, Object::m_speed -> m_moveSpeed)" in capsys.readouterr().out
    assert lane.adopt("Object", "Code/Object.h", ["Code/u.cpp"], apply=True) == 0
    assert "o->m_status" in (root / "Code" / "u.cpp").read_text()


def test_adopt_leaves_a_failing_unit_alone(tree, monkeypatch, capsys):
    root, _ = tree
    monkeypatch.setattr(lane, "gate_one", lambda s: "error C2039: 'getFlags'")
    assert lane.adopt("Object", "Code/Object.h", ["Code/u.cpp"], apply=True) == 1
    assert (root / "Code" / "u.cpp").read_text() == UNIT
    assert "FAIL Code/u.cpp: error C2039" in capsys.readouterr().out


# -- R1 regressions: each was a silent wrong rename that no byte check catches in inactive #if code

def test_s1_a_union_offset_with_several_candidates_is_refused():
    header = dict(HEADER_LAYOUTS, Thing=layout([(0, "first", "int", 4), (0, "last", "int", 4),
                                                (4, "m_extra", "int", 4)], size=8))
    assert lane.flat_fields("Object", header)[(0, 4)] == [("first", "int", "Thing"), ("last", "int", "Thing")]
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "could be any of Thing::first, Thing::last (a union)" in why


def test_s1_a_union_candidate_carrying_the_private_name_resolves():
    unit = dict(UNIT_LAYOUTS, Object=layout([(0, "last", "int", 4), (8, "m_speed", "float", 4)]))
    text = UNIT.replace("m_flags", "last").replace("    char m_pad04[4];\n", "")
    header = dict(HEADER_LAYOUTS, Thing=layout([(0, "first", "int", 4), (0, "last", "int", 4)], size=8))
    mapping, why = lane.field_renames("u.cpp", text, ["Object"], "Object.h", compiler(unit=unit, header=header))
    assert why is None and mapping == {"Object": {"m_speed": "m_moveSpeed"}}


def test_s2_a_name_two_classes_of_the_hierarchy_declare_is_refused():
    header = {"Thing": layout([(0, "value", "int", 4), (4, "m_extra", "int", 4)], size=8),
              "Object": layout([(8, "value", "float", 4)], bases=[("Thing", 0)])}
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "value is declared by Object, Thing" in why and "shadowed" in why


RENAMES = {"Object": {"m_flags": "m_status"}}

PROVEN = """class Object;
Object *find();
int a(Object *o) { return o->m_flags; }
int b(Object &r) { return r.m_flags; }
int c() { return find()->m_flags; }
int Object::d() { return m_flags + this->m_flags; }
int e() { return Object::m_flags; }
"""


def test_s3_members_reached_through_the_class_are_renamed():
    out, why = lane.scoped_rename(PROVEN, RENAMES)
    assert why is None and "m_flags" not in out and out.count("m_status") == 6


def test_s3_a_member_of_an_unrelated_class_is_left_alone():
    text = "class Other;\nint f(Other *x) { return x->m_flags + Other::m_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert why is None and out == text


@pytest.mark.parametrize("text, what", [
    ("int f() { int m_flags = 0; return m_flags; }\n", "a local in a free function"),
    ("#if 0\nint f() { int m_flags = 1; return m_flags; }\n#endif\n", "a local in inactive code"),
    ("int Object::f() { int m_flags = 0; return m_flags; }\n", "a local that hides the member"),
    ("int f(Object *o) { return g()->m_flags; }\n", "an object of no declared type"),
    ("int f(Object *p) { return p->m_flags; }\nint g(Team *p) { return p->m_flags; }\n", "two types for p"),
    ("int f(Object **v) { return v[0]->m_flags; }\n", "an indexed object"),
    ("#define FLAGS(o) ((o)->m_flags)\n", "a macro body"),
    ("class Derived : public Object {};\nint f(Derived *d) { return d->m_flags; }\n", "a derived class"),
])
def test_s3_an_occurrence_not_proven_a_member_refuses_the_unit(text, what):
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and why, what


def test_s3_try_unit_refuses_a_unit_with_an_unproven_occurrence(tree):
    root, _ = tree
    (root / "Code" / "u.cpp").write_text(UNIT + "#if 0\nint g() { int m_flags = 2; return m_flags; }\n#endif\n",
                                         encoding="latin-1", newline="")
    source, why, text, _ = lane.try_unit("Code/u.cpp", ["Object", "Thing"], "Code/Object.h", "class")
    assert text is None and why.startswith("field renames: m_flags at line")


# -- R2 regressions: every example Sol's second review named, each a silent wrong rename or
#    a rename of a token that is not the adopting class's field.

def test_s2_a_static_of_the_same_name_in_the_hierarchy_is_refused():
    header = dict(HEADER_LAYOUTS, Object=layout([(8, "m_moveSpeed", "float", 4)], bases=[("Thing", 0)]))
    header["Object"]["statics"] = ["m_status"]
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "m_status is a static member of Object" in why


def test_s2_a_method_of_the_same_name_in_the_hierarchy_is_refused():
    header = dict(HEADER_LAYOUTS, Object=layout([(8, "m_moveSpeed", "float", 4)], bases=[("Thing", 0)]))
    header["Object"]["methods"] = ["m_status"]
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(header=header))
    assert mapping is None and "m_status is a method of Object" in why


def test_s2_a_nested_type_of_the_same_name_in_the_header_is_refused(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Object.h").write_text(
        "class Thing { public: int m_status; int m_extra; };\n"
        "class Object : public Thing { public: float m_moveSpeed; class m_status; };\n",
        encoding="latin-1", newline="")
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(), header="Object.h")
    assert mapping is None and "m_status is a nested type of Object" in why


def test_s2_an_enumerator_of_the_same_name_in_the_header_is_refused(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Object.h").write_text(
        "class Thing { public: int m_status; int m_extra; };\n"
        "class Object : public Thing { public: float m_moveSpeed; enum { m_status }; };\n",
        encoding="latin-1", newline="")
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(), header="Object.h")
    assert mapping is None and "m_status is an enumerator of Object" in why


def test_s3_a_template_type_for_the_receiver_refuses_the_rename():
    text = ("class Other;\nclass Object;\ntemplate <class T> class Box;\n"
            "int f(Object *p) { return p->m_flags; }\n"
            "#if 0\nint g(Box<Other> *p) { return p->m_flags; }\n#endif\n")
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "not proven a member" in why


def test_s3_a_receiver_declared_only_with_a_template_is_refused():
    text = "class Other;\ntemplate <class T> class Box;\nint f(Box<Other> *p) { return p->m_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None


def test_s3_direct_initialisation_of_another_type_refuses_the_rename():
    text = ("class Other;\nclass Object;\nint f(Object *p) { return p->m_flags; }\n"
            "int g() { Other p(1); return 0; }\n")
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "not proven a member" in why


def test_s3_direct_initialisation_of_the_class_is_recognised():
    text = "class Object;\nint f() { Object p(1); return p.m_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert why is None and out.endswith("return p.m_status; }\n")


def test_s4_a_nested_struct_in_a_member_function_refuses_the_rename():
    text = ("class Other;\n"
            "int Object::g() { struct Local : Other { int f() { return this->m_flags; } }; return 0; }\n")
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "nested class or lambda" in why


def test_s4_a_lambda_capture_in_a_member_function_refuses_the_rename():
    text = "class Object;\nint Object::g() { return [&m_flags]() { return m_flags; }; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "capture list" in why


def test_s4_a_call_is_not_a_member_definition():
    text = ("class Object { public: static bool test(); };\n"
            "int f() { if (Object::test()) { return m_flags; } return 0; }\n")
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "not proven a member" in why


def test_s5_a_qualified_type_is_not_the_adopting_class():
    text = "namespace OtherNS { class Object; }\nint f(OtherNS::Object *p) { return p->m_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None


def test_s5_a_qualified_class_member_access_is_not_the_adopting_class():
    text = "namespace OtherNS { class Object; }\nint g() { return OtherNS::Object::m_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None


def test_s5_a_typedef_of_the_class_name_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    mapping, why = lane.field_renames("u.cpp", UNIT + "typedef Team Object;\n", ["Object"], "Object.h", compiler())
    assert mapping is None and "a typedef declares `Object`" in why


def test_s5_a_using_alias_of_the_class_name_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    mapping, why = lane.field_renames("u.cpp", UNIT + "using Object = Team;\n", ["Object"], "Object.h", compiler())
    assert mapping is None and "a using-alias declares `Object`" in why


def test_s5_a_typedef_in_an_include_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "u.cpp").write_text(UNIT + '#include "alias.h"\n', encoding="latin-1", newline="")
    (tmp_path / "Code" / "alias.h").write_text("typedef Team Object;\n", encoding="latin-1", newline="")
    text = (tmp_path / "Code" / "u.cpp").read_text(encoding="latin-1")
    mapping, why = lane.field_renames("Code/u.cpp", text, ["Object"], "Object.h", compiler())
    assert mapping is None and "alias.h: a typedef declares `Object`" in why


def test_s6_a_macro_naming_a_receiver_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    mapping, why = lane.field_renames("u.cpp", UNIT + "#define o q\n", ["Object"], "Object.h", compiler())
    assert mapping is None and "`#define o`" in why


def test_s6_a_macro_naming_the_new_field_refuses_the_unit(tmp_path, monkeypatch):
    # rename_problem's collision check fires first on this spelling; either refusal is safe.
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    mapping, why = lane.field_renames("u.cpp", UNIT + "#define m_status other\n", ["Object"], "Object.h", compiler())
    assert mapping is None and why


def test_s6_a_macro_naming_the_class_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    mapping, why = lane.field_renames("u.cpp", UNIT + "#define Object X\n", ["Object"], "Object.h", compiler())
    assert mapping is None and "`#define Object`" in why


def test_s6_a_macro_in_an_include_refuses_the_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "u.cpp").write_text(UNIT + '#include "macros.h"\n', encoding="latin-1", newline="")
    (tmp_path / "Code" / "macros.h").write_text("#define o q\n", encoding="latin-1", newline="")
    text = (tmp_path / "Code" / "u.cpp").read_text(encoding="latin-1")
    mapping, why = lane.field_renames("Code/u.cpp", text, ["Object"], "Object.h", compiler())
    assert mapping is None and "macros.h: `#define o`" in why


def test_s7_a_spliced_identifier_is_not_half_rewritten():
    text = "class Object;\nint Object::g() { return other_\\\nm_flags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "line splice" in why


def test_s7_a_spliced_old_name_is_refused():
    text = "class Object;\nint f(Object *o) { return o->m_fl\\\nags; }\n"
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "line splice" in why


def test_s7_a_continued_comment_is_not_code():
    text = ("class Object;\nint f(Object *o) { return o->m_flags; }\n"
            "// the member \\\no->m_flags is documented here\n")
    out, why = lane.scoped_rename(text, RENAMES)
    assert out is None and "line splice" in why


def test_s7_a_raw_string_is_not_code():
    text = ('class Object;\nint f(Object *o) { return o->m_flags; }\n'
            'const char *s = R"(say "o->m_flags")";\n')
    out, why = lane.scoped_rename(text, RENAMES)
    assert why is None and out.count("m_status") == 1


def test_r4_conditional_header_is_refused():
    assert lane.conditional_hierarchy([("h", "#if 0\nclass Object { static int m_status; };\n#endif")], {"Object"}, {"m_status"})


def test_r4_comma_declarator_receiver_is_refused():
    text = "class Object; class Other; Other *q, *p; Object *p; int f() { return p->m_flags; }"
    assert lane.scoped_rename(text, RENAMES)[0] is None


def test_r4_qualified_member_definition_is_refused():
    text = "class Object; int N::Object::g() { return m_flags; }"
    assert lane.scoped_rename(text, RENAMES)[0] is None


def test_r4_include_scan_refuses_unresolved_and_angle_code(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "Code" / "b.h").write_text('#include "c.h"\n')
    (tmp_path / "Code" / "c.h").write_text('')
    assert "unresolved" in lane.include_problem("u.cpp", '#include "missing.h"\n')
    assert lane.include_problem("u.cpp", '#include <a.h>\n') is None
    assert lane.include_problem("u.cpp", '#include "a.h"\n') is None


OLE2_SHAPE = """#if !defined( _OLE2_H_ )
#define _OLE2_H_
#ifndef _MAC
#include <pshpack8.h>
#else //_MAC
#ifdef _WIN32
#include "macname1.h"
#endif // _WIN32
#endif //_MAC
#endif
"""


def test_an_include_only_a_never_defined_platform_compiles_is_no_unresolved_include(tmp_path, monkeypatch):
    # sweep-header's debug-stackwalk packet: the Platform SDK's Ole2.h reaches `#include "macname1.h"` only when
    # _MAC is defined, which this x86 Win32 target never does; adopt refused DebugConstructor.cpp over it
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Ole2.h").write_text(OLE2_SHAPE)
    (tmp_path / "pshpack8.h").write_text("")
    assert lane.include_problem("u.cpp", '#include "Ole2.h"\n') is None
    for text in ("#ifdef _MAC\n#include \"mac.h\"\n#endif\n",
                 "#if defined(_WIN64)\n#include \"wide.h\"\n#endif\n",
                 "#if !defined _MAC\n#else\n#include \"mac.h\"\n#endif\n",
                 "#ifndef _MAC\n#elif X\n#include \"mac.h\"\n#endif\n",
                 "#if defined(_MAC) && defined(X)\n#include \"mac.h\"\n#endif\n",          # needs _MAC too
                 "#if !defined(_X86_) && defined(_M_M68K)\n#include \"m68k.h\"\n#endif\n"):  # Windows.h's shape
        assert lane.include_problem("u.cpp", text) is None, text


@pytest.mark.parametrize("text", [
    '#include "missing.h"\n',                                          # no condition at all
    '#ifndef _MAC\n#include "missing.h"\n#endif\n',                   # the branch that is compiled
    '#ifdef _MAC\n#else\n#include "missing.h"\n#endif\n',
    '#if defined(_MAC) || X\n#include "missing.h"\n#endif\n',          # a condition read as unknown
    '#if !defined(_MAC) && defined(X)\n#else\n#include "missing.h"\n#endif\n',  # the opposite of a conjunction
    '#ifdef SOME_PROJECT_FLAG\n#include "missing.h"\n#endif\n',        # not a platform macro
    '#if defined(_MAC) \\\n  || 1\n#include "missing.h"\n#endif\n',   # a continued directive
    '#endif\n#ifdef _MAC\n#endif\n#include "missing.h"\n',           # unbalanced nesting
    '#define _MAC 1\n#ifdef _MAC\n#include "missing.h"\n#endif\n',     # the closure defines the macro
])
def test_an_include_a_compiled_or_unknown_branch_names_stays_unresolved(tmp_path, monkeypatch, text):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    assert "unresolved include missing.h" in lane.include_problem("u.cpp", text)


def test_a_platform_macro_another_header_defines_keeps_the_include_unresolved(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Ole2.h").write_text(OLE2_SHAPE)
    (tmp_path / "pshpack8.h").write_text("")
    (tmp_path / "plat.h").write_text("#define _MAC\n")
    assert "macname1.h" in lane.include_problem("u.cpp", '#include "plat.h"\n#include "Ole2.h"\n')


def test_a_define_in_a_branch_never_compiled_does_not_count(tmp_path, monkeypatch):
    # the SDK's Windows.h: `#ifndef _MAC` / `#if defined(_68K_) || defined(_MPPC_)` / `#define _MAC`
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Ole2.h").write_text(OLE2_SHAPE)
    (tmp_path / "pshpack8.h").write_text("")
    (tmp_path / "Windows.h").write_text("#ifndef _MAC\n#if defined(_68K_) || defined(_MPPC_)\n#define _MAC\n#endif\n#endif\n")
    assert lane.include_problem("u.cpp", '#include "Windows.h"\n#include "Ole2.h"\n') is None
    (tmp_path / "Windows.h").write_text("#if defined(_68K_) || defined(PROJECT_FLAG)\n#define _MAC\n#endif\n")
    assert "macname1.h" in lane.include_problem("u.cpp", '#include "Windows.h"\n#include "Ole2.h"\n')


@pytest.mark.parametrize("guard,cycle", [
    ("#ifndef {m}\n#define {m}\n", False),
    ("#if !defined( {m} )\n#define {m}\n", False),               # the Platform SDK's Ole2.h
    ("#if !defined {m}\n#define {m}\n", False),
    ("#if !defined({m}) && FLAG\n#define {m}\n", True),          # not a guard
    ("#if defined({m})\n#define {m}\n", True),
])
def test_an_include_guard_spelled_with_defined_is_a_barrier(tmp_path, monkeypatch, guard, cycle):
    # Ole2.h guards itself with `#if !defined( _OLE2_H_ )`: unread, the SDK's mutual includes were a cycle
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text(guard.format(m="A_H") + '#include "b.h"\n#endif\n')
    (tmp_path / "b.h").write_text(guard.format(m="B_H") + '#include "a.h"\n#endif\n')
    problem = lane.include_problem("u.cpp", '#include "a.h"\n')
    assert ("cycle" in problem) if cycle else problem is None, problem
    assert lane.include_guard(lane.masked(guard.format(m="X") + "int x;\n#endif\n")) == (None if cycle else "X")


@pytest.mark.parametrize("text", [
    # review r1 (2): a define a never-defined macro enables can define another
    "#define _68K_\n#ifdef _68K_\n#define _MAC\n#endif\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    # review r1 (3): the digraph and a spliced directive name
    "%:define _MAC\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    "#def\\\nine _MAC\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    "#define _MAC(x) x\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    # review r1 (4): the unit's compiler flags define it
    "// cl: /O2 /D_MAC\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    "// cl: /D _MAC=1\n#ifdef _MAC\n#include \"missing.h\"\n#endif\n",
    "// cl: -D_WIN64\n#if defined(_WIN64)\n#include \"missing.h\"\n#endif\n",
    # a missing include spelled with the digraph is still read
    "%:include \"missing.h\"\n",
])
def test_review_r1_a_macro_the_closure_or_the_compiler_can_define_keeps_the_include(tmp_path, monkeypatch, text):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    assert "missing.h" in lane.include_problem("u.cpp", text)


def test_review_r1_a_define_under_a_dead_branch_still_does_not_count(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    text = ("// cl: /O2 /DPROJECT\n#ifdef _68K_\n#define _MAC\n#endif\n"
            "#ifdef _MAC\n#include \"missing.h\"\n#endif\n")
    assert lane.include_problem("u.cpp", text) is None


def test_review_r1_a_continued_guard_condition_is_no_barrier(tmp_path, monkeypatch):
    # `#if !defined(A_H) \` + `|| 1` stays true after `#define A_H`: no guard, so the mutual include is a cycle
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#if !defined(A_H) \\\n|| 1\n#define A_H\n#include "b.h"\n#endif\n')
    (tmp_path / "b.h").write_text('#if !defined(B_H) \\\n|| 1\n#define B_H\n#include "a.h"\n#endif\n')
    assert "cycle" in lane.include_problem("u.cpp", '#include "a.h"\n')


def test_review_r2_the_canonical_header_is_judged_with_its_units_macros(tmp_path, monkeypatch):
    # the header was walked alone: a unit's /D_MAC or #define _MAC never reached its Mac branch
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Object.h").write_text(HEADER + '#ifdef _MAC\n#include "missing.h"\n#endif\n')
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(), header="Object.h")
    assert why is None and mapping                       # nothing defines _MAC: never compiled
    for unit in ("// cl: /O2 /D_MAC\n" + UNIT, "#define _MAC\n" + UNIT):
        mapping, why = lane.field_renames("u.cpp", unit, ["Object"], "Object.h", compiler(), header="Object.h")
        assert mapping is None and "missing.h" in why, why


@pytest.mark.parametrize("unit", ["// cl: /O2 /D__RPC_MAC__\n" + UNIT, "#define __RPC_MAC__\n" + UNIT])
def test_review_r3_the_canonical_header_sees_every_macro_its_unit_defines(tmp_path, monkeypatch, unit):
    # review r3: the header was given the unit's absent platform macros only; a unit defining __RPC_MAC__ left
    # the header taking it for absent, dismissing the unread <outside.h> under it, and so _MAC for absent
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Object.h").write_text(HEADER + "#ifdef _MAC\n#define __RPC_MAC__\n#endif\n"
                                       '#ifdef __RPC_MAC__\n#include <outside.h>\n#endif\n'
                                       '#ifdef _MAC\n#include "missing.h"\n#endif\n')
    mapping, why = lane.field_renames("u.cpp", UNIT, ["Object"], "Object.h", compiler(), header="Object.h")
    assert why is None and mapping                       # nothing defines __RPC_MAC__ or _MAC: never compiled
    mapping, why = lane.field_renames("u.cpp", unit, ["Object"], "Object.h", compiler(), header="Object.h")
    assert mapping is None and "missing.h" in why and "<outside.h> resolves nowhere" in why, why


def test_review_r4_the_canonical_header_is_its_own_seed(tmp_path, monkeypatch):
    # review r4: an appended `#include "<header>"` resolved a same-named file under the unit's directory first,
    # and an unterminated comment at the unit's end swallowed it; both hid the canonical header's missing include
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code/Obj").mkdir(parents=True)
    (tmp_path / "sub/Code/Obj").mkdir(parents=True)
    (tmp_path / "Code/Obj/Object.h").write_text(HEADER + '#include "missing.h"\n')
    (tmp_path / "sub/Code/Obj/Object.h").write_text(HEADER)
    assert "missing.h" in lane.include_problem("sub/u.cpp", UNIT, seeds=("Code/Obj/Object.h",))
    mapping, why = lane.field_renames("sub/u.cpp", UNIT, ["Object"], "Object.h", compiler(), header="Code/Obj/Object.h")
    assert mapping is None and "Code/Obj/Object.h" in why.replace("\\", "/") and "missing.h" in why, why
    mapping, why = lane.field_renames("u.cpp", UNIT + "/*", ["Object"], "Object.h", compiler(),
                                      header="Code/Obj/Object.h")
    assert mapping is None and "missing.h" in why, why
    assert "cannot be read" in lane.include_problem("u.cpp", UNIT, seeds=("Code/Obj/Nowhere.h",))


def test_review_r2_a_digraph_else_spoils_the_guard(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#ifndef A_H\n#define A_H\n#include "b.h"\n%:else\n#include "b.h"\n#endif\n')
    (tmp_path / "b.h").write_text('#include "a.h"\n')
    assert "cycle" in lane.include_problem("u.cpp", '#include "a.h"\n')


RPC_SHAPE = ('#if defined(MAC) || defined(_MAC)\n#define __RPC_MAC__\n#endif\n'
             '#ifdef __RPC_MAC__\n#include <rpcerr.h>\n#endif\n')


@pytest.mark.parametrize("text,unresolved", [
    # review r2: a header the walk cannot read may define _MAC
    ('#include <outside.h>\n#ifdef _MAC\n#include "missing.h"\n#endif\n', "<outside.h> resolves nowhere"),
    # ... unless only a branch never compiled names it, directly or through a macro defined only in one (Rpc.h)
    ('#ifdef _MAC\n#include <macpub.h>\n#include "missing.h"\n#endif\n', None),
    (RPC_SHAPE + '#ifdef _MAC\n#include "missing.h"\n#endif\n', None),
    # the unit's flags define the derived macro, or it is one the compiler itself defines
    ('// cl: /D__RPC_MAC__\n' + RPC_SHAPE + '#ifdef _MAC\n#include "missing.h"\n#endif\n', "<rpcerr.h> resolves nowhere"),
    ('#ifdef _MAC\n#define _WIN32\n#endif\n#ifndef _WIN32\n#include <x.h>\n#endif\n'
     '#ifdef _MAC\n#include "missing.h"\n#endif\n', "<x.h> resolves nowhere"),
])
def test_review_r2_an_angle_include_found_nowhere_leaves_the_closure_incomplete(tmp_path, monkeypatch, text,
                                                                               unresolved):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    problem = lane.include_problem("u.cpp", text)
    assert problem is None if unresolved is None else (unresolved in problem and "missing.h" in problem), problem
    assert lane.include_problem("u.cpp", "#include <outside.h>\n") is None             # alone it proves nothing


def test_r4d_transitive_include_chain_and_cycles(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    for i in range(4):
        (tmp_path / f"{i}.h").write_text(f'#include "{i + 1}.h"\n')
    (tmp_path / "4.h").write_text("class Deep { int field; };\n")
    text = '#include "0.h"\n'
    assert lane.include_problem("u.cpp", text) is None
    assert any("class Deep" in body for _, body in lane.include_sources("u.cpp", text))
    (tmp_path / "4.h").write_text('#include "0.h"\n')
    assert "cycle" in lane.include_problem("u.cpp", text)
    (tmp_path / "0.h").write_text('#ifndef H0\n#define H0\n#include "1.h"\n#endif\n')
    assert lane.include_problem("u.cpp", text) is None


def test_include_cycle_can_be_cut_by_a_guarded_intermediate(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text('#ifndef B_H\n#define B_H\n#include "a.h"\n#endif\n')
    assert lane.include_problem("u.cpp", '#include "a.h"\n') is None


def test_guarded_ancestor_does_not_hide_an_unguarded_inner_cycle(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "g.h").write_text('#ifndef G_H\n#define G_H\n#include "a.h"\n#endif\n')
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text('#include "a.h"\n')
    assert "cycle" in lane.include_problem("u.cpp", '#include "g.h"\n')


def test_seen_header_does_not_hide_an_unguarded_alternate_cycle(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n#include "c.h"\n')
    (tmp_path / "b.h").write_text('#ifndef B_H\n#define B_H\n#include "c.h"\n#endif\n')
    (tmp_path / "c.h").write_text('#include "a.h"\n')
    assert "cycle" in lane.include_problem("u.cpp", '#include "a.h"\n')


@pytest.mark.parametrize("reset", [
    '#undef B_H\n', '#undef ' + '\\' + '\nB_H\n',
    '#un' + '\\' + '\ndef B_H\n',
    '%:undef B_H\n', '\v#\fundef\vB_H\n', '\f%:\vundef\fB_H\n',
    '#pragma pop_macro("B_H")\n', '__pragma(pop_macro("B_H"))\n',
    '#define SAVED_GUARD "B_H"\n#pragma pop_macro(SAVED_GUARD)\n',
    '#define RESTORE __pragma(pop_macro("B_H"))\nRESTORE\n',
    '#define RESTORE pop_macro\n__pragma(RESTORE("B_H"))\n__pragma(push_macro("B_H"))\n',
    '#pragma po' + '\\' + '\np_macro("B_H")\n',
])
def test_reset_guard_cannot_cut_an_include_cycle(tmp_path, monkeypatch, reset):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text('#ifndef B_H\n#define B_H\n#include "c.h"\n#endif\n')
    (tmp_path / "c.h").write_text(reset + '#include "a.h"\n')
    assert "cycle" in lane.include_problem("u.cpp", '#pragma push_macro("B_H")\n#include "a.h"\n')


def test_unrelated_macro_stack_does_not_invalidate_an_include_guard(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text('#ifndef B_H\n#define B_H\n#include "c.h"\n#endif\n')
    (tmp_path / "c.h").write_text('#pragma pop_macro("OTHER")\n#include "a.h"\n')
    assert lane.include_problem("u.cpp", '#include "a.h"\n') is None


def test_saving_an_include_guard_without_resetting_it_keeps_the_barrier(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text('#ifndef B_H\n#define B_H\n#include "a.h"\n#endif\n')
    assert lane.include_problem("u.cpp", '#pragma push_macro("B_H")\n#include "a.h"\n') is None


@pytest.mark.parametrize("body", [
    '#ifndef B_H\n#define B_H\n#endif\n#include "a.h"\n',
    '#ifndef B_H\n#define B_H\n#include "a.h"\n#else\n#include "a.h"\n#endif\n',
    '#ifndef B_H\n#define B_H\n#undef B_H\n#include "a.h"\n#endif\n',
])
def test_partial_else_or_self_reset_guard_cannot_cut_a_cycle(tmp_path, monkeypatch, body):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text(body)
    assert "cycle" in lane.include_problem("u.cpp", '#include "a.h"\n')


def test_guarded_cycle_still_exposes_watched_macros(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text('#include "b.h"\n')
    (tmp_path / "b.h").write_text(
        '#ifndef B_H\n#define B_H\n#define m_flags hidden\n#include "a.h"\n#endif\n')
    text = '#include "a.h"\nint flags(Object *o) { return o->m_flags; }\n'
    assert lane.include_problem("u.cpp", text) is None
    assert "m_flags" in lane.macro_shadow(lane.include_sources("u.cpp", text), RENAMES, text)


def test_r4_trigraph_is_refused():
    for char in "=/'()!<>-":
        assert lane.scoped_rename("int f(Object *o) { return o->m_flags; } // ??" + char, RENAMES)[0] is None
    assert lane.scoped_rename("int f(Object *o) { return o->m_flags; } // ??0Thing", RENAMES)[0] is not None
    assert lane.scoped_rename("int f(Object *o) { return o->m_flags; } // comment\\\n", RENAMES)[0] is None


def test_r4c_header_continuations(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    header = tmp_path / "h.h"
    header.write_text("#define X \\\n  1\n// ??0Object is a mangled name\n")
    assert lane.include_problem("u.cpp", '#include "h.h"\n') is None
    header.write_text("#define X \\\n  1\n// comment\\\nint hidden;\n")
    assert "h.h:3: trigraph or continued line comment" in lane.include_problem("u.cpp", '#include "h.h"\n')
    assert lane.header_comment_splice('const char *s = "// text\\\nmore";\n') is None
    assert lane.header_comment_splice('/\\\n/ comment\\\nint hidden;\n') == 0
    header.write_text("// ??/\n")
    assert "trigraph" in lane.include_problem("u.cpp", '#include "h.h"\n')


@pytest.mark.parametrize("newline", ["\n", "\r\n"])
def test_header_continued_comments_already_comment_every_physical_line(tmp_path, monkeypatch, newline):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    # STLport's stl_dec_vms.h comments out a multi-line preprocessor condition.
    body = newline.join([
        "// #if !defined(NEW_IOSTREAMS) " + "\\",
        "  // && !defined(REDEFINE_STD) " + "\\",
        "\t// && !defined(OTHER)",
        "class Object;",
        "",
    ])
    (tmp_path / "h.h").write_bytes(body.encode())
    assert lane.header_comment_splice(body) is None
    assert lane.include_problem("u.cpp", '#include "h.h"\n') is None


@pytest.mark.parametrize("body", [
    "// comment\\\n// second\\\n#define m_flags hidden\n",
    "// comment\\\n/* not an independent line comment */ int hidden;\n",
    "/\\\n/ comment\\\n// second\n",
    "// comment\\\n// second\\\n/\\\n/ hidden\n",
])
def test_header_comment_chain_still_refuses_changed_visible_tokens(tmp_path, monkeypatch, body):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "h.h").write_text(body)
    assert lane.header_comment_splice(body) == 0
    assert "continued line comment" in lane.include_problem("u.cpp", '#include "h.h"\n')


def test_r4b_guard_and_unrelated_conditional_do_not_hide_hierarchy():
    header = "#ifndef GUARD\n#define GUARD\n#if 0\nint unrelated;\n#endif\nclass Object { int x; };\n#endif\n"
    assert lane.conditional_hierarchy([("h", header)], {"Object"}, {"m_status"}) is None
    assert lane.conditional_hierarchy([("h", "#pragma once\n" + header)], {"Object"}, {"x"}) is None
    inside = header.replace("int x;", "\n#if 0\nstatic int m_status;\n#endif\nint x;")
    assert lane.conditional_hierarchy([("h", inside)], {"Object"}, {"m_status"})


def test_r4e_conditional_members_only_refuse_rename_names():
    text = "class Object {\n#if 0\nvirtual void unrelated();\n#else\nint other;\n#endif\n};\n"
    assert lane.conditional_hierarchy([("h", text)], {"Object"}, {"m_flags", "m_status"}) is None
    assert lane.conditional_hierarchy([("h", text.replace("other", "m_status"))], {"Object"}, {"m_flags", "m_status"})


def test_r4b_system_angles_are_allowed_but_code_include_root_is_refused(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    include = tmp_path / "Code" / "includes"
    include.mkdir(parents=True)
    (include / "local.h").write_text("")
    assert lane.include_problem("u.cpp", "#include <windows.h>\n#include <vector>\n", include_roots=[include]) is None
    assert lane.include_problem("u.cpp", "#include <local.h>\n", include_roots=[include]) is None


def test_r5_guard_else_is_conditional():
    text = '#ifndef H\n#define H\nclass Object { int other; };\n#else\nclass Object { int m_status; };\n#endif\n'
    assert lane.conditional_hierarchy([("h", text)], {"Object"}, {"m_status"})


def test_r5_angle_macro_shadow_all_candidates(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    a, b = tmp_path / "first", tmp_path / "second"
    a.mkdir()
    b.mkdir()
    (a / "shadow.h").write_text("// harmless\n")
    (b / "shadow.h").write_text("#define o q\n")
    unit = '#include <shadow.h>\nint f(Object *o) { return o->m_flags; }\n'
    headers = lane.include_sources("u.cpp", unit, [a, b])
    assert len(headers) == 2
    assert "#define o" in lane.macro_shadow(headers, RENAMES, unit)


OPAQUE_UNIT = """class Setter
{
public:
    char m_lead[419];
    unsigned char m_enabled;
    void enable();
};
void Setter::enable()
{
    reinterpret_cast<unsigned char *>(this)[419] = 1;
}
"""
OPAQUE_HEADER = "class Setter { public: void enable(); };\n"


def opaque_layouts():
    private = layout([(0, "m_lead", "char[419]", 419),
                      (419, "m_enabled", "unsigned char", 1)], size=420)
    canonical = dict(layout([], size=1), methods=["enable"])
    return {"Setter": private}, {"Setter": canonical}


@pytest.fixture
def opaque_tree(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/u.cpp").write_text(OPAQUE_UNIT)
    (tmp_path / "Code/Setter.h").write_text(OPAQUE_HEADER)
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    unit, header = opaque_layouts()
    monkeypatch.setattr(lane, "compile_text", compiler(unit, header))
    return tmp_path, unit, header


def test_method_only_header_needs_no_field_mapping(opaque_tree):
    _root, unit, header = opaque_tree
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert (mapping, why) == ({}, None)


@pytest.mark.parametrize("pragma", ["", "#pragma once\n"])
@pytest.mark.parametrize("opening", ["#ifndef SETTER_H", "#if !defined(SETTER_H)", "#if !defined SETTER_H"])
def test_method_only_header_with_a_complete_include_guard(opaque_tree, pragma, opening):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text(
        "// Registered method-only view.\n" + pragma + opening + "\n#define SETTER_H\n" + OPAQUE_HEADER + "#endif\n")
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert (mapping, why) == ({}, None)


@pytest.mark.parametrize("body", [
    "#ifdef FEATURE\n" + OPAQUE_HEADER + "#endif\n",
    "#ifndef SETTER_H\n" + OPAQUE_HEADER + "#endif\n",  # no matching define
    "#ifndef SETTER_H\n#define SETTER_H\n" + OPAQUE_HEADER + "#else\nint unrelated;\n#endif\n",
    "#ifndef SETTER_H\n#define SETTER_H\n#ifdef FEATURE\n" + OPAQUE_HEADER + "#endif\n#endif\n",
    "%:ifdef FEATURE\n" + OPAQUE_HEADER + "%:endif\n",
])
def test_method_only_header_does_not_elide_other_conditionals(opaque_tree, body):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text(body)
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


@pytest.mark.parametrize("bad", [
    None, {}, {"fwd": True}, {"unparsed": "conflicting complete records"},
    {"unparsed": 0}, {"unparsed": ""}, {"unparsed": None},
    {"fields": None}, {"bases": None}, {"statics": ["value"]},
    {"bases": [["Base", 0]]}, {"vfptr": True}, {"virtual": ["enable"]},
    {"vslots": {"0": "enable"}}, {"size": 4}, {"size": True}, {"methods": []},
])
def test_method_only_mapping_requires_a_complete_matching_probe(opaque_tree, bad):
    _root, unit, header = opaque_tree
    if bad is None:
        header = {}
    elif bad == {}:
        header = {"Setter": {}}
    else:
        header = {"Setter": dict(header["Setter"], **bad)}
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


@pytest.mark.parametrize("body", [
    "char value; void enable();",            # a lost char field can also report size one
    "static int value; void enable();",
    "void enable() {}",                     # an opaque declaration must not synthesize a body
    "static void enable();",
    "virtual void enable();",
    "UNKNOWN_MEMBER; void enable();",
])
def test_method_only_mapping_also_requires_the_header_source(opaque_tree, body):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text("class Setter { public: " + body + " };\n")
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


def test_method_only_mapping_requires_a_readable_selected_definition(opaque_tree):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text("class Setter;\n")
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


@pytest.mark.parametrize("base", ["Base", "public Base", "virtual Base"])
def test_method_only_mapping_refuses_a_lost_base_record(opaque_tree, base):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text(
        "class Base { char value; };\nclass Setter : " + base + " { public: void enable(); };\n")
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


@pytest.mark.parametrize("attribute", ["novtable", "dllexport"])
def test_method_only_mapping_refuses_unrepresented_class_attributes(opaque_tree, attribute):
    root, unit, header = opaque_tree
    (root / "Code/Setter.h").write_text(
        "class __declspec(" + attribute + ") Setter { public: void enable(); };\n")
    mapping, why = lane.field_renames("Code/u.cpp", OPAQUE_UNIT, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "laid out no field" in why


def test_method_only_mapping_does_not_skip_other_stripped_classes(opaque_tree):
    root, unit, header = opaque_tree
    text = OPAQUE_UNIT + UNIT.replace("int m_flags;", "short m_flags;")
    unit = dict(unit, Object=layout([(0, "m_flags", "short", 2), (8, "m_speed", "float", 4)]))
    header = dict(header, **HEADER_LAYOUTS)
    (root / "Code/Setter.h").write_text(OPAQUE_HEADER + HEADER)
    mapping, why = lane.field_renames("Code/u.cpp", text, ["Setter", "Object"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and "m_flags (+0x0, 2 bytes) has no canonical field" in why


@pytest.mark.parametrize("macro", ["m_enabled", "Setter"])
def test_method_only_mapping_keeps_macro_shadow_checks(opaque_tree, macro):
    _root, unit, header = opaque_tree
    text = f"#define {macro} hidden\n" + OPAQUE_UNIT
    mapping, why = lane.field_renames("Code/u.cpp", text, ["Setter"], "Setter.h",
                                     compiler(unit, header), header="Code/Setter.h")
    assert mapping is None and f"#define {macro}" in why


def test_method_only_preparation_still_runs_the_full_source_gate_and_restores(opaque_tree, monkeypatch):
    root, _unit, _header = opaque_tree
    original = OPAQUE_UNIT.replace("reinterpret_cast<unsigned char *>(this)[419]", "m_enabled")
    (root / "Code/u.cpp").write_text(original)
    seen = []

    def gate(source):
        candidate = (root / source).read_text()
        seen.append(candidate)
        assert '#include "Setter.h"' in candidate and "class Setter" not in candidate
        assert "m_enabled = 1;" in candidate
        return "error C2039: m_enabled is not a member of Setter"

    monkeypatch.setattr(lane, "gate_one", gate)
    _source, why, _text, _renames = lane.try_unit("Code/u.cpp", ["Setter"], "Code/Setter.h", "class")
    assert seen and "C2039" in why
    assert (root / "Code/u.cpp").read_text() == original


# stage-2 trial item 1: the VS2003 standard headers (typeinfo, xstddef, exception) guard themselves with
# `#pragma once` above their #ifndef, which include_guard does not read; STLport's typeinfo.h closes the cycle
VS2003_ONCE = "#if _MSC_VER > 1000\n#pragma once\n#endif\n\n#ifndef _TYPEINFO_\n#define _TYPEINFO_\n#include <b.h>\n#endif\n"


@pytest.mark.parametrize("head,cycle", [
    (VS2003_ONCE, False),
    ("#pragma once\n#include <b.h>\n", False),
    ("#if _MSC_VER >= 1310\n#pragma once\n#endif\n#include <b.h>\n", False),
    ("#ifdef _MSC_VER\n#pragma once\n#endif\n#include <b.h>\n", False),
    ("#if defined(_MSC_VER)\n#pragma once\n#endif\n#include <b.h>\n", False),
    # ... but not after the include that closes the cycle, nor in a branch the compiler may skip
    ("#include <b.h>\n#pragma once\n", True),
    ("#if _MSC_VER > 1400\n#pragma once\n#endif\n#include <b.h>\n", True),
    ("#if _MSC_VER >= 1311\n#pragma once\n#endif\n#include <b.h>\n", True),
    ("#ifdef ONCE\n#pragma once\n#endif\n#include <b.h>\n", True),
    ("#if _MSC_VER > 1000\n#else\n#pragma once\n#endif\n#include <b.h>\n", True),
    ("#ifndef _MSC_VER\n#pragma once\n#endif\n#include <b.h>\n", True),
    ("// #pragma once\n#include <b.h>\n", True),
    ("#pragma onceler\n#include <b.h>\n", True),
])
def test_a_pragma_once_ahead_of_every_include_is_a_barrier(tmp_path, monkeypatch, head, cycle):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text(head)
    (tmp_path / "b.h").write_text("#include <a.h>\n")
    problem = lane.include_problem("u.cpp", '#include "a.h"\n')
    assert ("cycle" in problem) if cycle else problem is None, problem


def test_a_pragma_once_header_does_not_hide_a_cycle_beside_it(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text("#pragma once\n#include <b.h>\n")
    (tmp_path / "b.h").write_text("#include <c.h>\n")
    (tmp_path / "c.h").write_text("#include <b.h>\n")
    assert "cycle" in lane.include_problem("u.cpp", '#include "a.h"\n')


@pytest.mark.parametrize("compiler_has,unresolved", [
    # the compiler searches no directory holding <outside.h>: reaching it stops the compile (C1083), so it
    # defines nothing in any compile that succeeds, and the _MAC branch stays never compiled
    (False, None),
    # the compiler finds it where the walk did not look: unread, it may define _MAC
    (True, "<outside.h> resolves nowhere"),
])
def test_with_the_compiler_roots_an_angle_include_found_nowhere_reads_nothing(tmp_path, monkeypatch, compiler_has,
                                                                             unresolved):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    compiler = tmp_path / "compiler-include"
    compiler.mkdir()
    if compiler_has:
        (compiler / "outside.h").write_text("#define _MAC\n")
    text = '#include <outside.h>\n#ifdef _MAC\n#include "missing.h"\n#endif\n'
    problem = lane.include_problem("u.cpp", text, compiler_roots=[tmp_path, compiler])
    assert problem is None if unresolved is None else (unresolved in problem and "missing.h" in problem), problem
    assert "<outside.h> resolves nowhere" in lane.include_problem("u.cpp", text)          # no roots: as before


def test_compiler_search_roots_are_none_when_the_command_cannot_be_built(monkeypatch):
    import build

    def fail(source, output):
        raise SystemExit("wine not found")
    monkeypatch.setattr(build, "compiler_command", fail)
    assert lane.compiler_search_roots("Code/u.cpp") is None


def test_field_renames_walks_with_the_compilers_search_roots(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    marker = [tmp_path / "compiler-include"]
    monkeypatch.setattr(lane, "compiler_search_roots", lambda source: marker)
    seen, walk = [], lane.include_problem

    def spy(*args, **kwargs):
        seen.append((kwargs.get("compiler_roots"), list(kwargs.get("include_roots", ()))))
        return walk(*args, **kwargs)
    monkeypatch.setattr(lane, "include_problem", spy)
    lane.field_renames("u.cpp", UNIT + "#define o q\n", ["Object"], "Object.h", compiler())
    # the compiler's roots decide what resolves nowhere, and the walk searches them too (a legacy /I path build
    # maps to the restructured Open-BFME-1 tree resolves only there)
    assert seen and all(roots is marker and marker[0] in searched for roots, searched in seen), seen


@pytest.mark.parametrize("text,unresolved", [
    # stage-2 trial: WWLib's thread.h names osdep.h only for Unix, which this x86 Win32 target never is
    ('#if defined(_MSC_VER)\n#pragma once\n#endif\n#ifdef _UNIX\n#include "osdep.h"\n#endif\n', False),
    ('#if defined(__unix__) || defined(__linux__)\n#include "osdep.h"\n#endif\n', False),
    # ... unless the unit's flags or the closure define it
    ('// cl: /D_UNIX\n#ifdef _UNIX\n#include "osdep.h"\n#endif\n', True),
    ('#define _UNIX 1\n#ifdef _UNIX\n#include "osdep.h"\n#endif\n', True),
])
def test_an_include_only_unix_compiles_is_no_unresolved_include(tmp_path, monkeypatch, text, unresolved):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    problem = lane.include_problem("u.cpp", text)
    assert ("unresolved include osdep.h" in problem) if unresolved else problem is None, problem


def test_review_r1_a_backslash_include_is_read_as_the_compiler_reads_it(tmp_path, monkeypatch):
    # include resolver review r1: `<sub\outside.h>` named no file on POSIX, so with the compiler's roots it read as
    # found nowhere (C1083) though MSVC under Wine reads it, and its `#define _UNIX` went unseen
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "sub").mkdir()
    (tmp_path / "sub" / "outside.h").write_text("#define _UNIX 1\n#define m_flags m_speed\n")
    (tmp_path / "sub" / "hidden.h").write_text("int hidden;\n")
    text = '#include <sub\\outside.h>\n#ifdef _UNIX\n#include "sub\\missing.h"\n#endif\n'
    problem = lane.include_problem("u.cpp", text, [tmp_path], compiler_roots=[tmp_path])
    assert problem and "unresolved include sub/missing.h" in problem, problem
    sources = lane.include_sources("u.cpp", '#include <sub\\outside.h>\n#include "sub\\hidden.h"\n', [tmp_path])
    assert {Path(p).name for p, _ in sources} == {"outside.h", "hidden.h"}


def test_review_r1_a_quoted_include_not_beside_its_includer_reads_every_candidate(tmp_path, monkeypatch):
    # include resolver review r1: the compiler's roots come sorted, not in search order, so the walk read a/config.h
    # where MSVC reads b/config.h, and missed the macro in it
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    for d, body in (("a", "// nothing\n"), ("b", "#define m_flags m_speed\n")):
        (tmp_path / d).mkdir()
        (tmp_path / d / "config.h").write_text(body)
    sources = lane.include_sources("Code/u.cpp", '#include "config.h"\n', [tmp_path / "a", tmp_path / "b"])
    assert sorted(Path(p).parent.name for p, _ in sources) == ["a", "b"]
    # beside its includer, it is that one file
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code" / "config.h").write_text("// local\n")
    sources = lane.include_sources("Code/u.cpp", '#include "config.h"\n', [tmp_path / "a", tmp_path / "b"])
    assert [Path(p).parent.name for p, _ in sources] == ["Code"]


def test_review_r1_a_quoted_include_may_come_from_an_outer_includers_directory(tmp_path, monkeypatch):
    # MSVC searches every includer's directory: inner.h's "config.h" is found beside outer.h
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "outer").mkdir()
    (tmp_path / "outer" / "deeper").mkdir()
    (tmp_path / "outer" / "outer.h").write_text('#include "deeper/inner.h"\n')
    (tmp_path / "outer" / "deeper" / "inner.h").write_text('#include "config.h"\n')
    (tmp_path / "outer" / "config.h").write_text("#define m_flags m_speed\n")
    sources = lane.include_sources("u.cpp", '#include "outer/outer.h"\n')
    assert "config.h" in {Path(p).name for p, _ in sources}


@pytest.mark.parametrize("a_h,flags,cycle", [
    # include resolver review r1: `#undef _MSC_VER` ahead of the condition: the pragma never runs
    ("#undef _MSC_VER\n#ifdef _MSC_VER\n#pragma once\n#endif\n#include \"b.h\"\n", "", True),
    ("#ifdef _MSC_VER\n#pragma once\n#endif\n#include \"b.h\"\n", "", False),
    ("#ifdef _MSC_VER\n#pragma once\n#endif\n#include \"b.h\"\n", "// cl: /U_MSC_VER\n", True),
    ("#ifdef _MSC_VER\n#pragma once\n#endif\n#include \"b.h\"\n", "// cl: /u\n", True),
    ("#if _MSC_VER > 1000\n#pragma once\n#endif\n#include \"b.h\"\n", "// cl: /D_MSC_VER=900\n", True),
    # ... b.h touching it counts too, wherever it sits in the closure
    ("#if _MSC_VER > 1000\n#pragma once\n#endif\n#include \"b.h\"\n", "", None),
    # an unconditional `#pragma once` holds whatever _MSC_VER holds
    ("#undef _MSC_VER\n#pragma once\n#include \"b.h\"\n", "", False),
])
def test_review_r1_a_conditional_pragma_once_needs_msc_ver_untouched(tmp_path, monkeypatch, a_h, flags, cycle):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.h").write_text(a_h)
    (tmp_path / "b.h").write_text(('#define _MSC_VER 900\n' if cycle is None else "") + '#include "a.h"\n')
    problem = lane.include_problem("u.cpp", flags + '#include "a.h"\n')
    assert ("cycle" in problem) if cycle in (True, None) else problem is None, problem


def test_review_r2_a_header_reached_through_another_includer_may_read_another_quoted_target(tmp_path, monkeypatch):
    # include resolver review r2: dispatch.h was walked once, through a/outer.h, so its "config.h" read a/config.h;
    # MSVC enters it again through b/outer.h and reads b/config.h, which defines a macro the rename must see
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    for d in ("a", "b", "common"):
        (tmp_path / d).mkdir()
    (tmp_path / "a" / "outer.h").write_text('#include "../common/dispatch.h"\n')
    (tmp_path / "b" / "outer.h").write_text('#include "../common/dispatch.h"\n')
    (tmp_path / "common" / "dispatch.h").write_text('#include "config.h"\n')
    (tmp_path / "a" / "config.h").write_text("")
    (tmp_path / "b" / "config.h").write_text("#define m_flags m_speed\n")
    problem = lane.include_problem("u.cpp", '#include "a/outer.h"\n#include "b/outer.h"\n')
    assert problem and "may resolve to" in problem and "b/config.h" in problem.replace("\\", "/"), problem
    # one chain alone: only a/config.h can be read, and it is
    assert lane.include_problem("u.cpp", '#include "a/outer.h"\n') is None
