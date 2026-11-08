"""class_layouts: CodeView parsing and the VC7.1 overloaded-virtual slot rule."""
import sys
import struct
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_layouts  # noqa: E402
import class_views  # noqa: E402
import pytest


def cv_class(name, size, forward=False, kind=0x1004):
    text = name.encode("ascii")
    blob = struct.pack("<HHIIIH", 0, 0x80 if forward else 0, 0, 0, 0, size)
    blob += bytes([len(text)]) + text
    return struct.pack("<HH", len(blob) + 2, kind) + blob


def test_forward_member_size_comes_from_complete_definition():
    stream = struct.pack("<I", 4) + cv_class("AsciiString", 0, True) + cv_class("AsciiString", 4)
    types = class_layouts.TypeStream(stream)
    assert types.size(0x1000) == 4
    assert types.size(0x1001) == 4


def test_missing_or_conflicting_definition_stays_unknown():
    prefix = struct.pack("<I", 4) + cv_class("Impl", 0, True)
    assert class_layouts.TypeStream(prefix).size(0x1000) == 0
    stream = prefix + cv_class("Impl", 4) + cv_class("Impl", 8)
    types = class_layouts.TypeStream(stream)
    assert types.size(0x1000) == 0
    assert types.size(0x1001) == 4
    assert types.size(0x1002) == 8


def test_class_key_and_full_scope_are_required_for_forward_resolution():
    stream = struct.pack("<I", 4) + cv_class("HUD::Impl", 0, True)
    stream += cv_class("Other::Impl", 8) + cv_class("HUD::Impl", 12, kind=0x1005)
    assert class_layouts.TypeStream(stream).size(0x1000) == 0


def test_parsed_cache_changes_when_the_reader_changes(monkeypatch, tmp_path):
    monkeypatch.setattr(class_layouts, "CACHE", tmp_path)
    monkeypatch.setattr(class_layouts, "PARSER_HASH", "old")
    stale = class_layouts.parsed_path("stream")
    stale.write_text('{"AsciiString": {"size": 0}}')
    monkeypatch.setattr(class_layouts, "PARSER_HASH", "fixed")
    assert class_layouts.parsed_path("stream") != stale
    assert not class_layouts.parsed_path("stream").exists()


class FakeBuilder:
    def compiler_command(self, source, obj):
        return ["cl", "-Fo" + str(obj), str(source)], {}


def failing_compile(monkeypatch, tmp_path, output, returncode=2):
    """Drive compile_layouts' failure path with `output` as the compiler's console text."""
    monkeypatch.setattr(class_layouts, "CACHE", tmp_path / "cache")
    monkeypatch.setattr(class_layouts, "ROOT", tmp_path)
    source = tmp_path / "u.cpp"
    source.write_text("void f() {}\n")
    done = type("Done", (), {"returncode": returncode, "stdout": output, "stderr": ""})()
    monkeypatch.setattr(class_layouts.subprocess, "run", lambda *a, **k: done)
    with pytest.raises(RuntimeError) as caught:
        class_layouts.compile_layouts("u.cpp", FakeBuilder(), use_cache=False)
    return str(caught.value)


def test_a_failed_compile_names_the_include_it_could_not_open(monkeypatch, tmp_path):
    why = failing_compile(monkeypatch, tmp_path,
                          "u.cpp(3) : fatal error C1083: Cannot open include file: 'Lib/Gone.h'\n")
    assert why.startswith("u.cpp: compile failed: C1083")
    assert "Cannot open include file: 'Lib/Gone.h'" in why   # the code alone names no cause


def test_a_failed_compile_keeps_the_first_three_errors_with_their_text(monkeypatch, tmp_path):
    why = failing_compile(monkeypatch, tmp_path,
                          "a.h(1) : error C2065: 'Foo' : undeclared identifier\n"
                          "a.h(2) : error C2039: 'bar' : is not a member of 'Baz'\n"
                          "a.h(3) : error C2011: 'Qux' : 'class' type redefinition\n"
                          "a.h(4) : error C2143: syntax error\n")
    assert why.count("; ") == 2 and "C2143" not in why
    for code, detail in [("C2065", "undeclared identifier"), ("C2039", "is not a member of 'Baz'"),
                         ("C2011", "'class' type redefinition")]:
        assert code in why and detail in why


def test_a_long_error_is_cut_but_still_says_what_went_wrong(monkeypatch, tmp_path):
    why = failing_compile(monkeypatch, tmp_path,
                          "x.h(9) : error C2955: 'list' : " + "T" * 400 + "\n")
    assert "C2955: 'list' :" in why and len(why) < 260


def test_a_failure_with_no_error_line_still_reports_the_console_text(monkeypatch, tmp_path):
    why = failing_compile(monkeypatch, tmp_path, "LINK : fatal error LNK1104: cannot open file\n")
    assert "LNK1104" in why                                  # the tail fallback, unchanged


@pytest.mark.parametrize("indent", ["", "    ", "\t"])
def test_nested_snapshot_is_not_a_global_private_view(indent):
    text = ("namespace EA { namespace Allocator {\n"
            "class GeneralAllocator {\npublic:\n"
            + indent + "struct Snapshot { unsigned m_magic; };\n"
            "};\n}}\n")
    assert class_layouts.class_bodies(text) == ["GeneralAllocator"]
    assert set(class_views.class_bodies(text)) == {"GeneralAllocator"}


def test_scopes_ignore_literal_braces_and_skip_local_and_template_members():
    text = '''namespace Detail {
    class Owner {
        const char *brace() { return "}"; }
        char open() { return '{'; }
struct Snapshot { int nested; };
    };
    struct Coord3D { float x, y, z; };
}
void local() {
class Snapshot { int local; };
}
template <class T>
class Container {
struct Snapshot { int nested; };
};
class Snapshot { int global; };
'''
    expected = ["Owner", "Coord3D", "Snapshot"]
    assert class_layouts.class_bodies(text) == expected
    assert list(class_views.class_bodies(text)) == expected
    assert "global" in class_views.class_bodies(text)["Snapshot"]


@pytest.mark.parametrize("linkage", ["C", "C++"])
def test_linkage_block_does_not_hide_a_namespace_scope_view(linkage):
    text = 'extern "' + linkage + '" {\n    class Snapshot {};\n}\n'
    assert class_layouts.class_bodies(text) == ["Snapshot"]
    assert list(class_views.class_bodies(text)) == ["Snapshot"]


def test_indented_private_view_is_still_refused_by_class_gate(monkeypatch):
    import class_gate
    monkeypatch.setattr(class_gate, "git_text", lambda _: None)
    text = 'extern "C++" {\n    class Snapshot {};\n}\n'
    assert class_gate.introduced("Code/New.cpp", text, {"Snapshot": "Snapshot.h"}) == ["Snapshot"]


@pytest.mark.parametrize("source", ["Rva00034D10Snapshot.cpp", "Rva000353F0Trace.cpp", "memory_pool.cpp"])
def test_allocator_false_reject_sources_do_not_declare_game_snapshot(source):
    """These units mean EA::Allocator's nested Snapshot record, never the game's class.

    The record reaches them either as their own declaration or, since the
    canonical GeneralAllocator header was adopted in them (9489e5d051d), from
    that header - so requiring the literal text in the .cpp would now fail on
    an adoption that is exactly what the lane is for. What must stay true is
    that neither scanner reads a Snapshot *class body* out of these units.
    """
    allocator_header = "Code/GameEngine/Include/Common/GeneralAllocator.h"
    path = class_layouts.ROOT / "Code/GameEngine/Source/Common/System" / source
    text = path.read_text(encoding="latin-1")
    assert "struct Snapshot" in text or allocator_header.rsplit("/", 1)[1] in text, \
        "the allocator's Snapshot record must be in scope, declared here or by its canonical header"
    assert "struct Snapshot" in (class_layouts.ROOT / allocator_header).read_text(encoding="latin-1")
    assert "Snapshot" not in class_layouts.class_bodies(text)
    assert "Snapshot" not in class_views.class_bodies(text)


def toolchain():
    try:
        class_layouts.build_module().vc71_root()
        return True
    except SystemExit:
        return False


@unittest.skipUnless(toolchain(), "MSVC 7.1 not available")
class SlotOrder(unittest.TestCase):
    def test_probe_agrees_with_vcall_thunks(self):
        rows, ok = class_layouts.run_probe()
        self.assertTrue(ok, rows)
        self.assertEqual(len(rows), 6)

    def test_naive_reading_is_caught(self):
        # Positive control: taking CodeView's shared group offset at face value
        # must disagree with the thunks, or the probe proves nothing.
        class_layouts.REVERSED_GROUPS = False
        try:
            rows, ok = class_layouts.run_probe()
        finally:
            class_layouts.REVERSED_GROUPS = True
        self.assertFalse(ok, rows)


class Bodies(unittest.TestCase):
    def test_private_views_skip_templates_and_comments(self):
        text = ("// class Fake {\nstruct Coord3D { float x, y, z; };\n"
                "template <class T>\nclass StringBase { T *p; };\nclass AsciiString : public StringBase<char> {};\n")
        self.assertEqual(class_layouts.class_bodies(text), ["Coord3D", "AsciiString"])

    def test_mangled_numbers(self):
        self.assertEqual(class_layouts.mangled_number("7AE")[0], 8)
        self.assertEqual(class_layouts.mangled_number("M@AE")[0], 12)
        self.assertEqual(class_layouts.mangled_number("BI@AE")[0], 24)


if __name__ == "__main__":
    unittest.main()


# The opt-in scope-aware reader (class_identities, template_member_definitions). It fails closed.
NS = "namespace FXParticleSystem {{\n{}\n}}\n"
PRIM = "template <int N> class CategoryModuleTemplate : public CategoryModuleTemplateBase<N> { };"
SPEC7 = "template <> class CategoryModuleTemplate<7> : public ModuleTemplate { };"


def ident(text):
    found = class_layouts.class_identities(text)
    assert found is not None, "expected a reading, got ambiguous"
    return [(q, a, t, k) for q, _n, a, t, _s, _e, k in found]


def test_identity_of_a_namespaced_template_primary():
    assert ident(NS.format(PRIM)) == [("FXParticleSystem::CategoryModuleTemplate", None, True, "class")]


def test_identity_of_explicit_and_partial_specializations():
    assert ident(NS.format(SPEC7)) == [("FXParticleSystem::CategoryModuleTemplate", "7", True, "class")]
    assert ident("template <int N> class CategoryModuleClassBase<N, 0> { };") == [
        ("CategoryModuleClassBase", "N,0", True, "class")]


def test_specialization_arguments_nest_and_compact_closers():
    text = "template <> class ConcreteModuleClass<ModuleTag<6, K, N, M, T, B> > { };"
    assert ident(text) == [("ConcreteModuleClass", "ModuleTag<6,K,N,M,T,B>", True, "class")]
    assert ident("template <> class X<A<B<int>>> { };") == [("X", "A<B<int>>", True, "class")]


def test_multi_line_head_and_base_clause():
    text = "template <int N, int H = (N != 8)>\nclass X\n:\npublic B<N>\n{\n};\n"
    assert ident(text) == [("X", None, True, "class")]


def test_a_parenthesised_comparison_in_a_template_parameter_is_not_a_closer():
    # review: `template<bool B = (1 > 0)> class X {}` was read as not a template.
    assert ident("template <bool B = (1 > 0)> class X { };") == [("X", None, True, "class")]


def test_template_template_parameters():
    assert ident("template <template <class> class C, class T> class Holder { C<T> c; };") == [
        ("Holder", None, True, "class")]


def test_member_template_keeps_its_class_path():
    text = "namespace FXParticleSystem { class Outer { template <int N> class CategoryModuleTemplate {}; }; }"
    assert ident(text) == [("FXParticleSystem::Outer", None, False, "class"),
                           ("FXParticleSystem::Outer::CategoryModuleTemplate", None, True, "class")]


def test_a_qualified_nested_template_head_is_kept():
    # review: `template<class T> class X<T>::Y {}` lost Y.
    assert ident("template <class T> class X<T>::Y { };") == [("X<T>::Y", None, True, "class")]


def test_reopened_namespaces_keep_their_path():
    text = "namespace A { class X { }; }\nnamespace B { }\nnamespace A { class Y { }; }\n"
    assert ident(text) == [("A::X", None, False, "class"), ("A::Y", None, False, "class")]


def test_declarations_instantiations_and_uses_define_no_body():
    text = ("template <int N> class X;\ntemplate class X<6>;\nX<6> *p;\nclass Y;\n"
            "struct S *f(struct T *t);\nclass Z { friend class W; };\n")
    assert ident(text) == [("Z", None, False, "class")]


def test_an_anonymous_typedef_recovers_its_name():
    # review: `typedef struct { int a; } X;` returned [].
    assert ident("typedef struct { int a; } X;") == [("X", None, False, "struct")]
    assert ident("typedef struct Tag { int a; } Tag_t;") == [("Tag", None, False, "struct")]
    assert class_layouts.class_identities("typedef struct { int a; } *const Px;") is None


def test_a_templated_function_with_a_return_type_is_still_proven():
    text = "template <class T> T *make(int n) { return 0; }\ntemplate <> int *make<int>(int n) { return 0; }\nclass K { };\n"
    assert ident(text) == [("K", None, False, "class")]


def test_function_bodies_initializers_and_enums_are_proven_scopes():
    text = ("namespace { struct A { int a; }; }\n"
            "void f() { struct Local { int b; }; }\n"
            "int Table[] = { 1, 2 };\n"
            "enum Mode { ON, OFF };\n"
            "class __declspec(dllexport) D { public: D() : m(0) { } ~D() { } virtual int g() const { return 0; } int m; };\n"
            "D::D2 D::make() { return D2(); }\n")
    assert ident(text) == [("(anonymous)::A", None, False, "struct"), ("D", None, False, "class")]


@pytest.mark.parametrize("text", [
    '#include "heads.h"\nDECLARE_CLASS(X) { int x; };\n',        # review: a macro-made class gave []
    "template <class T> DECLARE_CLASS(X) { int x; };\n",            # re-review: a template prefix is no type
    "template <> DECLARE_CLASS(X) { int x; };\n",
    "template <class T> template <class U> DECLARE_CLASS(X) { int x; };\n",
    "BEGIN_SCOPE { class X { }; }\n",
    "#define S X\n" + NS.format(PRIM),
    'const char *s = R"(x)";\n' + PRIM,
    PRIM + "\n}",
    "class X { int a;\n",
])
def test_text_the_reader_cannot_prove_is_ambiguous(text):
    assert class_layouts.class_identities(text) is None


def test_includes_are_not_ambiguous():
    assert ident('#include "a.h"\n' + PRIM) == [("CategoryModuleTemplate", None, True, "class")]


@pytest.mark.parametrize("pragma", [
    "#pragma once", "#pragma pack(push, 1)", "  #  pragma warning(disable: 4100)",
    '#pragma comment(linker, "/alternatename:a=b")', "#pragma message(\"{\")", "#pragma foo {",
])
def test_pragmas_open_no_scope(pragma):
    assert ident(pragma + "\n" + PRIM + "\n#pragma pack(pop)\n") == [
        ("CategoryModuleTemplate", None, True, "class")]
    defs = class_layouts.template_member_definitions(pragma + "\ntemplate <int N> int X<N>::s = 0;\n", "X")
    assert defs is not None and len(defs) == 1


@pytest.mark.parametrize("directive", ["#define X Y", "#if 1", "#ifdef A", "#undef A", "#error no", "%:define X"])
def test_other_directives_stay_ambiguous(directive):
    assert class_layouts.class_identities(directive + "\n" + PRIM + "\n") is None


# Master's readers, frozen: these are origin/master's outputs (tools/class_layouts.py before the
# opt-in reader), so a change to the legacy behaviour fails here.
LEGACY = {
    "namespace FXParticleSystem {\ntemplate <int N> class CategoryModuleTemplate : public B<N> { };\n}\n":
        ([], [("CategoryModuleTemplate", 29, 92, "class")], []),
    "namespace FXParticleSystem {\ntemplate <> class CategoryModuleTemplate<7> : public ModuleTemplate { };\n}\n":
        ([], [], []),
    "class Outer { template <int N> class X {}; struct Inner { int a; }; };\n":
        ([("Outer", 0, 69, "class")], [("Outer", 0, 69, "class")], ["Outer"]),
    "struct A { int a; };\nclass B : public A { };\nvoid f() { struct L { int b; }; }\n":
        ([("A", 0, 19, "struct"), ("B", 21, 43, "class")], [("A", 0, 19, "struct"), ("B", 21, 43, "class")],
         ["A", "B"]),
    "class A::B { };\n": ([("A::B", 0, 14, "class")], [("A::B", 0, 14, "class")], ["A::B"]),
}


@pytest.mark.parametrize("text", list(LEGACY))
def test_legacy_readers_keep_masters_outputs(text):
    spans, with_templates, bodies = LEGACY[text]
    assert class_layouts.class_body_spans(text) == spans
    assert class_layouts.class_body_spans(text, include_templates=True) == with_templates
    assert class_layouts.class_bodies(text) == bodies


def members(text, name):
    found = class_layouts.template_member_definitions(text, name)
    return None if found is None else [text[s:e] for s, e in found]


def test_template_member_definitions_find_functions_and_static_data():
    text = ("template <int N> class CategoryModuleClass { static const CategoryModuleClass *const s_first; };\n"
            "template <int N> const CategoryModuleClass<N> *const CategoryModuleClass<N>::s_first = 0;\n"
            "template <int N> const char *CategoryModuleClass<N>::getKey() const { if (N) { return 0; } return 0; }\n"
            "template <int N> CategoryModuleClass<N>::~CategoryModuleClass() { }\n"
            "template <int N> const int Table<N>::s_values[2] = { 1, 2 };\n"
            "const char *Other::getKey() const { return 0; }\n")
    defs = members(text, "CategoryModuleClass")
    assert len(defs) == 3
    assert defs[0].endswith("::s_first = 0;")
    assert defs[1].startswith("template <int N> const char *CategoryModuleClass<N>::getKey()") and defs[1].endswith("}")
    assert defs[2].endswith("~CategoryModuleClass() { }")
    assert members(text, "Table") == ["template <int N> const int Table<N>::s_values[2] = { 1, 2 };"]
    assert members(text, "Other") == []


def test_a_member_type_in_a_return_type_is_not_a_member_definition():
    # review: `template<class T> typename X<T>::type f() {}` was taken for X's member.
    assert members("template <class T> typename X<T>::type f() { return 0; }", "X") == []
    both = "template <class T> typename X<T>::type X<T>::get() { return 0; }"
    assert members(both, "X") == [both]


@pytest.mark.parametrize("text", [
    "template <int N> void X<N>::f() { }\n}",                       # review: a trailing brace
    "template <int N> void X<N>::f() {\n",                          # review: an unfinished function
    "template <int N> int X<N>::s = 0",                             # a definition that never closes
    "#if 1\ntemplate <int N> int X<N>::s = 0;\n",
])
def test_member_reader_fails_closed(text):
    assert class_layouts.template_member_definitions(text, "X") is None


def test_pragma_cases_the_review_probed():
    # warning push/pop around a class, a quoted `//` in a pragma, an inline __pragma: still read.
    text = ('#pragma warning(push)\n#pragma warning(disable: 4100)\n#pragma comment(lib, "a//b.lib")\n'
            "__pragma(warning(disable: 4512))\n" + PRIM + "\n#pragma warning(pop)\n")
    assert ident(text) == [("CategoryModuleTemplate", None, True, "class")]


@pytest.mark.parametrize("text", [
    "#pragma warning(disable: \\\n4100)\n" + PRIM,              # a backslash continuation splices lines
    "#define NOWARN __pragma(warning(disable: 4100))\n" + PRIM,    # a macro around __pragma is a #define
    "#define NOWARN _Pragma(\"once\")\n" + PRIM,
])
def test_pragma_lookalikes_that_still_refuse(text):
    assert class_layouts.class_identities(text) is None
