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


# The opt-in scope-aware reader (class_identities, template_member_definitions).
NS = "namespace FXParticleSystem {{\n{}\n}}\n"
PRIM = "template <int N> class CategoryModuleTemplate : public CategoryModuleTemplateBase<N> { };"
SPEC7 = "template <> class CategoryModuleTemplate<7> : public ModuleTemplate { };"


def ident(text):
    return [(q, a, t, k) for q, _n, a, t, _s, _e, k in class_layouts.class_identities(text)]


def test_identity_of_a_namespaced_template_primary():
    assert ident(NS.format(PRIM)) == [("FXParticleSystem::CategoryModuleTemplate", None, True, "class")]


def test_identity_of_explicit_and_partial_specializations():
    assert ident(NS.format(SPEC7)) == [("FXParticleSystem::CategoryModuleTemplate", "7", True, "class")]
    partial = "template <int N> class CategoryModuleClassBase<N, 0> { };"
    assert ident(partial) == [("CategoryModuleClassBase", "N,0", True, "class")]


def test_specialization_arguments_nest():
    text = "template <> class ConcreteModuleClass<ModuleTag<6, K, N, M, T, B> > { };"
    assert ident(text) == [("ConcreteModuleClass", "ModuleTag<6,K,N,M,T,B>", True, "class")]


def test_multi_line_head_and_base_clause():
    text = "template <int N, int H = (N != 8)>\nclass X\n:\npublic B<N>\n{\n};\n"
    assert ident(text) == [("X", None, True, "class")]


def test_member_template_keeps_its_class_path():
    text = "namespace FXParticleSystem { class Outer { template <int N> class CategoryModuleTemplate {}; }; }"
    assert ident(text) == [("FXParticleSystem::Outer", None, False, "class"),
                           ("FXParticleSystem::Outer::CategoryModuleTemplate", None, True, "class")]


def test_declarations_instantiations_and_uses_define_no_body():
    text = ("template <int N> class X;\ntemplate class X<6>;\nX<6> *p;\nclass Y;\nfriend class Z;\n"
            "struct S *f(struct T *t);\n")
    assert ident(text) == []


def test_ambiguous_text_is_refused_not_guessed():
    assert class_layouts.class_identities("#define S X\n" + NS.format(PRIM)) is None
    assert class_layouts.class_identities('const char *s = R"(x)";\n' + PRIM) is None
    assert class_layouts.class_identities(PRIM + "\n}") is None          # unbalanced
    assert class_layouts.class_identities('#include "a.h"\n' + PRIM) is not None


def test_anonymous_namespace_and_function_local_and_typedef_heads():
    text = ("namespace { struct A { int a; }; }\n"
            "void f() { struct Local { int b; }; }\n"
            "typedef struct Tag { int c; } Tag_t;\n"
            "class __declspec(dllexport) D { };\n")
    assert ident(text) == [("(anonymous)::A", None, False, "struct"), ("Tag", None, False, "struct"),
                           ("D", None, False, "class")]


def test_class_bodies_are_unchanged_by_the_new_reader():
    # The default readers keep their spelling-only, template-free behaviour.
    for text in (NS.format(PRIM), NS.format(SPEC7), "class Outer { template <int N> class X {}; };"):
        assert class_layouts.class_body_spans(text) == [s for s in class_layouts.class_body_spans(text)]
    assert class_layouts.class_bodies(NS.format(PRIM)) == []
    assert class_layouts.class_bodies(NS.format(SPEC7)) == []
    assert class_layouts.class_bodies("class Outer { template <int N> class X {}; };") == ["Outer"]


def test_template_member_definitions_find_functions_and_static_data():
    text = ("template <int N> class CategoryModuleClass { static const CategoryModuleClass *const s_first; };\n"
            "template <int N> const CategoryModuleClass<N> *const CategoryModuleClass<N>::s_first = 0;\n"
            "template <int N> const char *CategoryModuleClass<N>::getKey() const { if (N) { return 0; } return 0; }\n"
            "template <int N> const int Table<N>::s_values[2] = { 1, 2 };\n"
            "const char *Other::getKey() const { return 0; }\n")
    spans = class_layouts.template_member_definitions(text, "CategoryModuleClass")
    defs = [text[s:e] for s, e in spans]
    assert len(defs) == 2
    assert defs[0].endswith("::s_first = 0;")
    assert defs[1].startswith("template <int N> const char *CategoryModuleClass<N>::getKey()") and defs[1].endswith("}")
    table = [text[s:e] for s, e in class_layouts.template_member_definitions(text, "Table")]
    assert table == ["template <int N> const int Table<N>::s_values[2] = { 1, 2 };"]
    assert class_layouts.template_member_definitions(text, "Other") == []
    assert class_layouts.template_member_definitions("#if 1\n" + text, "Table") is None
