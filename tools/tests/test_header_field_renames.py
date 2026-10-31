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
    assert mapping == {"Object": {"m_flags": "m_status", "m_speed": "m_moveSpeed"}}   # padding needs no counterpart


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
    assert "angle" in lane.include_problem("u.cpp", '#include <a.h>\n')
    assert lane.include_problem("u.cpp", '#include "a.h"\n') is None


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
    assert "angle" in lane.include_problem("u.cpp", "#include <local.h>\n", include_roots=[include])
