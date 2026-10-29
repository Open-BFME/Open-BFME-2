"""tu_skeleton's merge lane: verified flags, redefinition repair, repointing and claims."""
import contextlib
import re
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


class RedefinitionTests(unittest.TestCase):
    def test_reads_type_typedef_and_enum_redefinitions(self):
        errors = [
            "a.cpp(7) : error C2011: 'Coord3D' : 'struct' type redefinition",
            "a.cpp(9) : error C2371: 'Real' : redefinition; different basic types",
            "a.cpp(11) : error C2365: 'BODY_PRISTINE' : redefinition; previous definition was 'enumerator'",
            "a.cpp(12) : error C2065: 'm_4' : undeclared identifier",
        ]
        self.assertEqual(T.redefined(errors), {"Coord3D", "Real", "BODY_PRISTINE"})

    def compose(self, drop=frozenset(), drop_all=frozenset()):
        texts = {"Seed.cpp": "struct Coord3D { float x, y, z; };\nint seed() { return 1; }\n",
                 "Donor.cpp": "struct Coord3D { float x, y, z; };\nint donor() { return 2; }\n"}
        return T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first",
                         drop=drop, drop_all=drop_all)

    def test_drop_keeps_the_seed_copy_and_drop_all_removes_every_copy(self):
        # identical spellings are emitted once already
        self.assertEqual(self.compose().count("struct Coord3D"), 1)
        texts = {"Seed.cpp": "struct Coord3D { float x, y, z; };\n",
                 "Donor.cpp": "struct Coord3D { float x; float y; float z; float w; };\n"}
        both = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        self.assertEqual(both.count("struct Coord3D"), 1)   # first spelling chosen
        kept = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "longest",
                         drop=frozenset({"Coord3D"}))
        self.assertIn("float x, y, z;", kept)             # the seed's copy survives a drop
        gone = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "longest",
                         drop_all=frozenset({"Coord3D"}))
        self.assertNotIn("struct Coord3D", gone)          # a header owns it


class DirectiveCompositionTests(unittest.TestCase):
    def compose(self, text, skeleton=True):
        sk = [({"rva": "0x1000", "size": "8"},
               {"source": "Seed.cpp", "status": "matched"})] if skeleton else []
        return T.compose("Seed.cpp", sk, ["Seed.cpp"], {"Seed.cpp": text}, [], "first")

    def test_separate_conditional_includes_keep_both_closing_directives(self):
        first = '#ifdef FIRST\n#include "first.h"\n#endif'
        second = '#if SECOND\n#if NESTED\n#include "nested.h"\n#else\n#include "second.h"\n#endif\n#endif'
        out = self.compose(first + "\n" + second + "\nint f() { return 1; }\n")
        self.assertIn(first, out)
        self.assertIn(second, out)
        self.assertEqual(out.count("#endif"), 3)

    def test_a_conditional_definition_keeps_its_branch_and_nested_contents(self):
        guarded = ('#if DEBUG\nint debug() { return 1; }\n'
                   '#elif INTERNAL\n#if EXTRA\nint extra() { return 2; }\n#endif\n'
                   'int internal() { return 3; }\n#else\nint release;\n#endif')
        out = self.compose(guarded + "\nint f() { return 4; }\n")
        self.assertIn(guarded, out)
        self.assertEqual(out.count("int debug()"), 1)
        self.assertEqual(out.count("#endif"), 2)

    def test_optimization_scopes_and_repeated_resets_stay_in_body_order(self):
        text = ('#pragma optimize("s", on)\nint f() { return 1; }\n'
                '#pragma optimize("", on)\n#pragma optimize("t", off)\n'
                '#pragma optimize("s", on)\nint g() { return 2; }\n'
                '#pragma optimize("", on)\n')
        for skeleton in (True, False):
            out = self.compose(text, skeleton)
            self.assertEqual(out.count('#pragma optimize("", on)'), 2)
            self.assertEqual(out.count('#pragma optimize("s", on)'), 2)
            self.assertIn(text.replace("\n", "\n\n").rstrip(), out)

    def test_a_seeds_trailing_optimization_state_ends_the_unit(self):
        # hrawanim.cpp ends in optimize("gsy", on) for the ??_E it emits at the end
        # of the unit; a donor body composed after the seed must not take that state
        sk = [({"rva": "0x1000", "size": "8"}, {"source": "Seed.cpp", "status": "matched"}),
              ({"rva": "0x1010", "size": "8"}, {"source": "Donor.cpp", "status": "matched"})]
        texts = {"Seed.cpp": 'int f() { return 1; }\n// the unit ends size-optimised\n'
                             '#pragma optimize("gsy", on)\n',
                 "Donor.cpp": "int g() { return 2; }\n"}
        out = T.compose("Seed.cpp", sk, ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        self.assertEqual(out.count('#pragma optimize("gsy", on)'), 1)
        self.assertLess(out.index("int g()"), out.index("// the unit ends size-optimised"))
        self.assertLess(out.index("// the unit ends size-optimised"), out.index('#pragma optimize("gsy", on)'))
        self.assertLess(out.index("int f()"), out.index("int g()"))

    def test_unterminated_region_is_not_silently_closed(self):
        out = self.compose("#ifdef DEBUG\nint f() { return 1; }\n")
        self.assertIn("#ifdef DEBUG\n", out)
        self.assertNotIn("#endif", out)
class ComposeRegenerationTests(unittest.TestCase):
    def test_a_seeds_old_placeholders_and_header_are_not_copied(self):
        sk = [({"rva": "0x00001000", "size": "8", "by": "-"}, None),
              ({"rva": "0x00001010", "size": "8", "by": "-"}, None)]
        texts = {"Seed.cpp": "// TU Seed.cpp: generated by tools/tu_skeleton.py from tu_map.csv\n"
                             "// tu-skeleton: 0x00001000 8B ?a@@YAXXZ -- unmatched, no code, never credited\n"
                             "int seed() { return 1; }\n"}
        out = T.compose("Seed.cpp", sk, ["Seed.cpp"], texts, [], "first")
        self.assertEqual(out.count("// tu-skeleton:"), 2)          # one fresh line per approved row, none copied
        self.assertEqual(out.count("generated by tools/tu_skeleton.py"), 1)

    def test_a_macro_invocation_line_is_its_own_chunk(self):
        text = "BFME_FLAG_BIT_SETTER(Rva1, 0x4)\nclass Foo { public: int f(); };\nint Foo::f() { return 0; }\n"
        kinds = [(k, c.strip()[:28]) for k, c in T.chunks(text)]
        self.assertEqual(kinds[0][0], "decl"); self.assertTrue(kinds[0][1].startswith("BFME_FLAG_BIT_SETTER(Rva1"))
        self.assertEqual(kinds[1][0], "decl")
        self.assertTrue(kinds[1][1].startswith("class Foo"))
        self.assertEqual(kinds[2][0], "def")


class IncludeOrderTests(unittest.TestCase):
    def test_seed_includes_come_first_and_spellings_dedupe(self):
        # the include-list rule lives inline in _merge; exercise it the way _merge does
        texts = {"Code/Zed/Seed.cpp": "// cl: /MD /Ireference/shims/seed /Ireference/shims/common\n",
                 "Code/Alpha/Donor.cpp": "// cl: /MD -Ireference/shims/common/ /Ireference/open-bfme-1/game/WWLib\n"}
        good = sorted(texts)                       # alphabetical puts the donor first
        tu = "Code/Zed/Seed.cpp"
        incs, seen = [], set()
        for f in ([tu] if tu in good else []) + [f for f in good if f != tu]:
            for x in T.flags_of(texts[f]):
                if x.lower().startswith(("/i", "-i")):
                    d = x[2:].replace("\\", "/").rstrip("/")
                    if d not in seen:
                        seen.add(d)
                        incs.append(x)
        self.assertEqual(incs, ["/Ireference/shims/seed", "/Ireference/shims/common",
                                "/Ireference/open-bfme-1/game/WWLib"])


class PreludeOrderTests(unittest.TestCase):
    def test_a_declaration_between_includes_stays_between_them(self):
        # CrateSystem.cpp declares KindOfMaskType between two includes; the second header needs it
        tu = "Code/T.cpp"
        seed = ('// cl: /MD\n#include "A.h"\ntypedef int Mask;\n#include "B.h"\n'
                'typedef int AfterAll;\nint f() { return 1; }\n')
        out = T.compose(tu, [], [tu], {tu: seed}, ["/MD"], "first")
        at = {name: out.index(name) for name in ('"A.h"', "typedef int Mask;", '"B.h"', "typedef int AfterAll;")}
        self.assertLess(at['"A.h"'], at["typedef int Mask;"])
        self.assertLess(at["typedef int Mask;"], at['"B.h"'])
        self.assertLess(at['"B.h"'], at["typedef int AfterAll;"])

    def test_pragmas_and_a_body_between_includes_stay_between_them(self):
        # mapper.cpp: the pragmas around refcount.h/vector2.h scope those headers' inlines and
        # its ??_H anchor body sits between them; moved below every include, the seed lost bytes
        tu = "Code/T.cpp"
        seed = ('// cl: /MD\n#pragma optimize("s", on)\n#include "A.h"\n#pragma optimize("", on)\n'
                'static void anchor() { }\n#include "B.h"\n#pragma optimize("y", on)\n'
                'int f() { return 1; }\n')
        out = T.compose(tu, [], [tu], {tu: seed}, ["/MD"], "first")
        names = ('#pragma optimize("s", on)', '"A.h"', '#pragma optimize("", on)',
                 "static void anchor()", '"B.h"', '#pragma optimize("y", on)', "int f()")
        at = [out.index(name) for name in names]
        self.assertEqual(at, sorted(at))
        self.assertEqual(out.count("static void anchor()"), 1)
        self.assertEqual(out.count('#pragma optimize("s", on)'), 1)


class DirectiveContinuationTests(unittest.TestCase):
    def test_a_continuation_onto_a_blank_line_does_not_swallow_the_next_line(self):
        # particle_emitter_convert_version.cpp: SAFE_DELETE_ARRAY ends `}\` and a blank line; with
        # the blank line dropped the macro continued onto `#endif` (C2162 in the composed TU)
        text = "#ifndef M\n#define M(p)\t\\\n\tif (p) { p = 0; }\t\\\n\n#endif\nvoid f() { }\n"
        out = T.compose("Seed.cpp", [], ["Seed.cpp"], {"Seed.cpp": text}, [], "first")
        self.assertIn("#endif", out)
        line = next(l for l in out.splitlines() if "p = 0;" in l)
        self.assertFalse(line.rstrip().endswith("\\"))


class BraceInitialisedDataTests(unittest.TestCase):
    def test_operator_equals_and_default_arguments_are_still_bodies(self):
        text = ("Transition &Transition::operator=(const Transition &o) { return *this; }\n"
                "bool Foo::operator==(const Foo &o) const { return true; }\n"
                "void f(int x = 0) { }\n"
                "int t[] = { 1 };\n")
        self.assertEqual([k for k, _ in T.chunks(text)], ["def", "def", "def", "decl"])
        self.assertTrue(T.initialised("int t[] = "))
        self.assertFalse(T.initialised("void f(int x = 0) "))
        self.assertFalse(T.initialised("Transition &Transition::operator=(const Transition &o) "))

    def test_an_initialised_array_is_one_declaration_item(self):
        text = 'const char *TheDrawableIconNames[] = {\n\t"a",\n\t"b",\n};\nenum DrawableIconType { X = 0 };\nint f() { return 0; }\n'
        items = T.chunks(text)
        self.assertEqual([k for k, _ in items], ["decl", "decl", "def"])
        self.assertTrue(items[0][1].strip().endswith("};"))
        out = T.compose("Seed.cpp", [], ["Seed.cpp"], {"Seed.cpp": text}, [], "first")
        self.assertNotIn("\n;\n", out)
        self.assertIn("TheDrawableIconNames[] = {", out)


class StorageSpecifiedAggregateTests(unittest.TestCase):
    def test_a_static_enum_ends_at_its_semicolon(self):
        # BuddyThread.cpp: `static enum CallbackType { ... };` lost its `;` (C2628 in the composed TU)
        text = "static enum CallbackType\n{\n\tCALLBACK_CONNECT,\n\tCALLBACK_MAX\n};\nvoid f() { }\n"
        items = T.chunks(text)
        self.assertEqual([k for k, _ in items], ["decl", "def"])
        self.assertTrue(items[0][1].strip().endswith("};"))
        out = T.compose("Seed.cpp", [], ["Seed.cpp"], {"Seed.cpp": text}, [], "first")
        self.assertNotIn("\n;\n", out)
        self.assertIn("CALLBACK_MAX\n};", out)

    def test_a_static_class_object_is_one_data_definition(self):
        text = "static class InitClass { public: InitClass() { } } Instance;\nint g() { return 0; }\n"
        self.assertEqual([k for k, _ in T.chunks(text)], ["decl", "def"])
        self.assertEqual([(d[3], d[4]) for d in T.data_decls(text)], [("Instance", True)])

    def test_functions_returning_a_static_struct_pointer_stay_bodies(self):
        text = "static struct Foo *find(int n) { return 0; }\nstatic const struct Bar *get() const { return 0; }\n"
        self.assertEqual([k for k, _ in T.chunks(text)], ["def", "def"])


class CommentReadingTests(unittest.TestCase):
    def test_a_line_comment_banner_before_a_block_comment_leaves_no_slash(self):
        # dx8caps.cpp: `//*****` then `/*! ... */` left a `/` before the struct head,
        # which then split at its `}` and orphaned the `;`
        text = "//********\n/*! doc */\nstruct S { int a; };\nint f() { return 1; }\n"
        self.assertEqual([(k, T.strip(c).strip()) for k, c in T.chunks(text)],
                         [("decl", "struct S { int a; };"), ("def", "int f() { return 1; }")])

    def test_a_comment_opener_in_a_string_is_text(self):
        self.assertEqual(T.norm('const char *p = "/* x */ //y";'), 'const char *p = "/* x */ //y";')

    def test_a_block_comment_opened_on_a_directive_line_ends_with_the_directive(self):
        # W3DView.cpp: `#include "WinMain.h" /** ...` leaked the comment's braces into the next item
        text = '#include "WinMain.h" /** start\n * more } {\n */\nclass V { int x; };\nint g() { return 2; }\n'
        items = T.chunks(text)
        self.assertEqual([k for k, _ in items], ["pp", "decl", "def"])
        self.assertEqual(T.strip(items[0][1]).strip(), '#include "WinMain.h"')
        self.assertEqual(T.strip(items[1][1]).strip(), "class V { int x; };")


class HeaderQueueTests(unittest.TestCase):
    def test_donors_with_a_queued_private_copy_are_named_before_the_merge(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "reverse/header_queue.tsv").write_text(
                "class\tsource\tretail_rvas\theader\tfailure\tretry_budget\tacceptance\n"
                "AsciiString\tCode/A.cpp\t0x1\treference/shims/x.h\t\t3\t\n"
                "Rva0007DF07\tCode/A.cpp\t0x2\treference/shims/y.h\t\t3\t\n")
            q = T.header_queue_rows(root=root)
            self.assertEqual(dict(q), {"Code/A.cpp": ["AsciiString", "Rva0007DF07"]})


class DonorTests(unittest.TestCase):
    TU = "Code/T.cpp"

    def donors(self, ledger, placed):
        """donors() over `ledger` [(name, rva, source)] with `placed` {rva: tu} approved."""
        T._CACHE.clear()
        T._CACHE["ledger"] = [{"name": n, "export_rva": "", "target_rva": f"0x{rva:08X}", "target_size": "8",
                               "source": s, "status": "matched", "notes": ""} for n, rva, s in ledger]
        T._CACHE["map"] = [{"rva": f"0x{rva:08X}", "size": "8", "kind": "code", "tu": tu, "confidence": "approved",
                            "by": "-", "evidence": "", "source": ""} for rva, tu in placed.items()]
        T._CACHE["stale"] = False
        try:
            with patch.object(T, "refusal", return_value=None):
                return T.donors(self.TU, T.skeleton(self.TU))
        finally:
            T._CACHE.clear()

    def test_the_tu_file_keeps_rows_the_map_places_nowhere(self):
        # The seed moves none of its rows and the merge re-verifies them, so an
        # unplaced row of the TU file itself is no reason to call it mixed.
        don, mixed, _ = self.donors([("?t@@YAXXZ", 0x1000, self.TU), ("?u@@YAXXZ", 0x1100, self.TU),
                                     ("?a@@YAXXZ", 0x1010, "Code/A.cpp")],
                                    {0x1000: self.TU, 0x1010: self.TU})
        self.assertEqual(mixed, {})
        self.assertEqual(sorted(don), ["Code/A.cpp", self.TU])
        self.assertEqual(len(don[self.TU]), 2)

    def test_a_tu_file_row_placed_in_another_tu_still_makes_it_mixed(self):
        don, mixed, _ = self.donors([("?t@@YAXXZ", 0x1000, self.TU), ("?o@@YAXXZ", 0x1200, self.TU),
                                     ("?a@@YAXXZ", 0x1010, "Code/A.cpp")],
                                    {0x1000: self.TU, 0x1010: self.TU, 0x1200: "Code/Other.cpp"})
        self.assertEqual(mixed, {self.TU: 1})
        self.assertNotIn(self.TU, don)

    def test_a_donor_with_unplaced_rows_is_still_not_absorbed(self):
        # Absorbing it would move a row the map does not put in this TU.
        don, mixed, _ = self.donors([("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                                     ("?v@@YAXXZ", 0x1300, "Code/B.cpp")],
                                    {0x1000: self.TU, 0x1020: self.TU})
        self.assertEqual(mixed, {"Code/B.cpp": 1})
        self.assertEqual(sorted(don), [self.TU])


class ComposePreprocessorTests(unittest.TestCase):
    def test_conditionals_are_not_deduplicated_across_donors(self):
        texts = {"Seed.cpp": "#ifndef FALSE\n#define FALSE 0\n#endif\nint seed() { return 1; }\n",
                 "Donor.cpp": "#ifndef NULL\n#define NULL 0\n#endif\nint donor() { return 2; }\n"}
        out = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        self.assertEqual(out.count("#endif"), 2)
        self.assertEqual(out.count("#ifndef"), 2)

    def test_repeated_includes_are_emitted_once(self):
        texts = {"Seed.cpp": '#include "a.h"\nint seed() { return 1; }\n',
                 "Donor.cpp": '#include "a.h"\n#include "b.h"\nint donor() { return 2; }\n'}
        out = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        self.assertEqual(out.count('#include "a.h"'), 1)
        self.assertEqual(out.count('#include "b.h"'), 1)


class EffectiveFlagsTests(unittest.TestCase):
    def verifier(self, overridden=False):
        v = T.Verifier.__new__(T.Verifier)
        fd = SimpleNamespace(
            MANAGED=re.compile(r"[-/](?:O[12xstdg]|arch:SSE2?|G[567B])$"),
            overrides=lambda: {"Code/T.cpp": {}} if overridden else {},
            region_at=lambda rva: {"opt": "O1", "arch": "SSE", "tune": "G7", "vote": "1"},
            _flag_set=lambda region: (region["opt"], region["arch"], region["tune"]),
            region_tokens=lambda region: ["-O1", "-arch:SSE", "-G7"])
        v.fd, v.tu_rel = fd, "Code/T.cpp"
        return v

    def test_region_codegen_replaces_the_line_and_keeps_other_tokens(self):
        text = "// cl: /O2 /MD /EHsc\nint f() { return 0; }\n"
        out = self.verifier().effective(text, [{"target_rva": "0x1000", "target_size": "8"}])
        self.assertTrue(out.startswith("// cl: /O1 /arch:SSE /G7 /MD /EHsc\n"))

    def test_an_overridden_tu_keeps_its_own_flags(self):
        text = "// cl: /O2 /MD\nint f() { return 0; }\n"
        self.assertEqual(self.verifier(True).effective(text, [{"target_rva": "0x1000", "target_size": "8"}]), text)

    def test_a_file_without_a_cl_line_gets_one(self):
        out = self.verifier().effective("int f() { return 0; }\n", [{"target_rva": "0x1000", "target_size": "8"}])
        self.assertTrue(out.startswith("// cl: /O1 /arch:SSE /G7\n"))


class MemberKeyTests(unittest.TestCase):
    def test_a_declspec_does_not_hide_the_function_name(self):
        plain = T.member_key("int getInt() const;")
        self.assertEqual(plain, (("fn", "getInt", True), "safe"))
        self.assertEqual(T.member_key("__declspec(dllimport) __forceinline int getInt() const { return m_int; }"), plain)
        self.assertEqual(T.member_key("__declspec(noinline) bool f(Parameter *a);")[0], ("fn", "f", False))

    def test_union_view_does_not_redeclare_a_declspec_member(self):
        base = "class P\n{\npublic:\n\t__declspec(dllimport) __forceinline int getInt() const { return m_int; }\n\tint m_int;\n};"
        other = "class P\n{\npublic:\n\tint getInt() const;\n\tint m_int;\n};"
        self.assertEqual(T.union_view(base, [other]).count("getInt"), 1)


class StlStaticFlagTests(unittest.TestCase):
    def test_an_md_set_with_the_alloc_shim_gets_the_define_before_its_includes(self):
        self.assertEqual(T.stl_static(["/MD", "/EHsc", "/Ireference/shims/bfmealloc", "/ICode"]),
                         ["/MD", "/EHsc", "/D_STLP_USE_STATIC_LIB", "/Ireference/shims/bfmealloc", "/ICode"])
        self.assertIn("/D_STLP_USE_STATIC_LIB", T.stl_static(["-MD", "-Ireference\\shims\\bfmealloc_alloconly\\"]))

    def test_other_sets_are_left_alone(self):
        for flags in (["/MD", "/D_STLP_USE_STATIC_LIB", "/Ireference/shims/bfmealloc"],
                      ["/MT", "/Ireference/shims/bfmealloc"],
                      ["/MD", "/Ireference/shims/bfmelist"],
                      ["/MD", "/Ireference/shims/notbfmealloc"]):
            self.assertEqual(T.stl_static(flags), flags)


class VerifierCacheTests(unittest.TestCase):
    ERRORS = {
        "type-A": ["a.cpp(1) : error C2011: 'A' : 'class' type redefinition"],
        "member-B": ["b.cpp(1) : error C2039: 'memberB' : is not a member of 'B'"],
    }
    ROWS = [{"target_rva": "0x1000"}]

    def verifier(self, root):
        v = T.Verifier.__new__(T.Verifier)
        v.tu, v.tmp = root / "T.cpp", root
        v.cache, v.errors, v.all_errors, v.sm = {}, [], [], {}
        v.effective = lambda text, rows: text
        v.fd = SimpleNamespace(forced_mode=lambda mode: contextlib.nullcontext())
        compiled = {}
        calls = []

        def compile_source(src, obj):
            text = src.read_text()
            calls.append(text)
            compiled[obj] = text
            errors = self.ERRORS.get(text, [])
            return not errors, "\n".join(errors), None

        def compile_function(row, sm, obj):
            return {"bytes": b"wrong" if compiled[obj] == "mismatch" else b"exact",
                    "target": b"exact"}

        v.B = SimpleNamespace(try_compile_source=compile_source,
                              compile_function=compile_function)
        return v, calls

    def test_cached_failure_restores_its_own_redefinition_diagnostics(self):
        with tempfile.TemporaryDirectory() as tmp:
            v, compiled = self.verifier(Path(tmp))
            self.assertIsNone(v.matched("type-A", self.ROWS))
            self.assertIsNone(v.matched("member-B", self.ROWS))
            self.assertEqual(T.redefined(v.all_errors), set())
            self.assertIsNone(v.matched("type-A", self.ROWS))
            self.assertEqual(v.all_errors, self.ERRORS["type-A"])
            self.assertEqual(v.errors, self.ERRORS["type-A"])
            self.assertEqual(T.redefined(v.all_errors), {"A"})
            self.assertEqual(len(compiled), 2)

    def test_success_clears_old_errors_on_compile_and_cache_hit(self):
        with tempfile.TemporaryDirectory() as tmp:
            v, compiled = self.verifier(Path(tmp))
            self.assertIsNone(v.matched("type-A", self.ROWS))
            self.assertEqual(v.matched("exact", self.ROWS), {"0x1000"})
            self.assertEqual((v.all_errors, v.errors), ([], []))
            self.assertIsNone(v.matched("member-B", self.ROWS))
            self.assertEqual(v.matched("exact", self.ROWS), {"0x1000"})
            self.assertEqual((v.all_errors, v.errors), ([], []))
            self.assertEqual(len(compiled), 3)

    def test_cached_byte_mismatch_remains_rejected_without_stale_errors(self):
        with tempfile.TemporaryDirectory() as tmp:
            v, compiled = self.verifier(Path(tmp))
            self.assertEqual(v.matched("mismatch", self.ROWS), set())
            self.assertIsNone(v.matched("type-A", self.ROWS))
            self.assertEqual(v.matched("mismatch", self.ROWS), set())
            self.assertEqual((v.all_errors, v.errors), ([], []))
            self.assertEqual(len(compiled), 2)

    def test_tu_in_a_missing_directory_compiles_and_leaves_no_directory(self):
        # a merge into a TU whose directory no file has yet (Fesl/util.cpp)
        with tempfile.TemporaryDirectory() as tmp:
            v, compiled = self.verifier(Path(tmp))
            v.tu = Path(tmp) / "Fesl" / "sub" / "util.cpp"
            self.assertEqual(v.matched("exact", self.ROWS), {"0x1000"})
            self.assertEqual(compiled, ["exact"])
            self.assertFalse((Path(tmp) / "Fesl").exists())

    def test_candidate_keeps_the_tu_suffix(self):
        # a C TU compiled through a .cpp scratch file gets C++ linkage and misses every row
        with tempfile.TemporaryDirectory() as tmp:
            v, _ = self.verifier(Path(tmp))
            v.tu = Path(tmp) / "lapi.c"
            seen = []
            compile_source = v.B.try_compile_source
            v.B.try_compile_source = lambda src, obj: (seen.append(src.suffix), compile_source(src, obj))[1]
            self.assertEqual(v.matched("exact", self.ROWS), {"0x1000"})
            self.assertEqual(seen, [".c"])


class RepointTests(unittest.TestCase):
    def test_fold_proof_moves_only_exact_source_tokens_in_notes(self):
        raw = (b'name,address,notes\n'
               b'"?a@@YAXXZ",0x1000,"fold-proof=Code/A.cpp; from Code/A.cpp, ""EA"""\n'
               b'?b@@YAXXZ,0x1001,ICF;fold-proof=Code/B.cpp\n'
               b'?c@@YAXXZ,0x1002,fold-proof=Code/A.cpp.extra\n'
               b'?d@@YAXXZ,0x1003,not-fold-proof=Code/A.cpp\n'
               b'?e@@YAXXZ,0x1004,from Code/A.cpp\n'
               b'fold-proof=Code/A.cpp,0x1005,\n'
               b'?f@@YAXXZ,0x1006\n')
        out, count = T.repoint_fold_proofs(raw, ["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp")
        expected = raw.replace(b'"fold-proof=Code/A.cpp;', b'"fold-proof=Code/T.cpp;')
        expected = expected.replace(b';fold-proof=Code/B.cpp', b';fold-proof=Code/T.cpp')
        self.assertEqual((out, count), (expected, 2))

    def test_repoint_all_registers_changed_fold_proofs_without_changing_pins(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            path = root / "reverse/symbols.csv"
            path.write_bytes(b'name,address,notes\n?a@@YAXXZ,0x1000,fold-proof=Code/A.cpp\n')
            moved = T.repoint_all(root, ["Code/A.cpp"], "Code/T.cpp")
            self.assertEqual(moved, {"reverse/symbols.csv": 1})
            self.assertEqual(path.read_bytes(),
                             b'name,address,notes\n?a@@YAXXZ,0x1000,fold-proof=Code/T.cpp\n')
            self.assertEqual(T.repoint_all(root, ["Code/A.cpp"], "Code/T.cpp"), {})

    def test_apply_stages_transferred_adoption_debt_without_a_microsoft_queue(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code").mkdir()
            with patch("header_adopt_lane.transfer_sources", return_value=2) as transfer, \
                    patch.object(T.subprocess, "run") as run:
                moved = T.apply("Code/T.cpp", ["Code/A.cpp"], "int x;\n", root=root)
            transfer.assert_called_once_with(
                ["Code/A.cpp"], "Code/T.cpp", queue=root / "reverse/header_queue.tsv")
            self.assertEqual(moved, {"reverse/header_queue.tsv": 2})
            self.assertEqual(run.call_args.args[0],
                             ["git", "add", "--", "Code/T.cpp", "reverse/header_queue.tsv"])

    def test_apply_writes_a_tu_in_a_missing_directory(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code").mkdir()
            with patch("header_adopt_lane.transfer_sources", return_value=0), \
                    patch.object(T.subprocess, "run"):
                T.apply("Code/Fesl/util.cpp", ["Code/A.cpp"], "int x;\n", root=root)
            self.assertEqual((root / "Code/Fesl/util.cpp").read_text(), "int x;\n")

    def test_apply_stages_the_refreshed_header_queue(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code").mkdir()
            (root / "reverse").mkdir()
            (root / "reverse/ms_header_queue.tsv").write_text("fixture\n")
            with patch("ms_header_audit.load_index", return_value={}) as index, \
                    patch("ms_header_audit.scan_text", return_value={"occ": []}) as scan, \
                    patch("ms_header_audit.refresh_queue", return_value=True) as refresh, \
                    patch.object(T.subprocess, "run") as run:
                moved = T.apply("Code/T.cpp", ["Code/A.cpp"], "int x;\n", root=root)
            index.assert_called_once()
            scan.assert_called_once_with("Code/T.cpp", "int x;\n", {})
            self.assertEqual(refresh.call_args.kwargs["removed"], ["Code/A.cpp"])
            self.assertEqual(refresh.call_args.kwargs["queue"], root / "reverse/ms_header_queue.tsv")
            self.assertEqual(moved, {"reverse/ms_header_queue.tsv": 1})
            self.assertEqual(run.call_args.args[0],
                             ["git", "add", "--", "Code/T.cpp", "reverse/ms_header_queue.tsv"])

    def test_every_path_keyed_column_and_the_doxygen_list_move_to_the_tu(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "docs/doxygen").mkdir(parents=True)
            # Union-merged ledgers require LF on Windows as well as Unix.
            (root / "reverse/functions.csv").write_text(
                HEADER + "?a@@YAXXZ,,0x00001000,8,Code/A.cpp,matched,\n"
                "?b@@YAXXZ,,0x00001010,8,Code/B.cpp,matched,keeps Code/A.cpp in notes\n"
                "?c@@YAXXZ,,0x00001020,8,Code/C.cpp,matched,\n", encoding="utf-8", newline="\n")
            (root / "reverse/data_rows.csv").write_text(
                "name,address,address_kind,size,section,source,status,evidence,model\n"
                "?g@@3HA,0x00002000,rva,4,.data,Code/B.cpp,matched,,\n", encoding="utf-8", newline="\n")
            (root / "docs/doxygen/sources.cfg").write_text(
                "# list\nINPUT += Code/A.cpp\nINPUT += Code/B.cpp\nINPUT += Code/C.cpp\n")
            moved = T.repoint_all(root, ["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp")
            self.assertEqual(moved, {"reverse/functions.csv": 2, "reverse/data_rows.csv": 1,
                                     "docs/doxygen/sources.cfg": 2})
            fn = (root / "reverse/functions.csv").read_text()
            self.assertIn("0x00001000,8,Code/T.cpp,", fn)
            self.assertIn("0x00001010,8,Code/T.cpp,matched,keeps Code/A.cpp in notes", fn)
            self.assertIn("Code/C.cpp", fn)
            self.assertIn(",Code/T.cpp,matched", (root / "reverse/data_rows.csv").read_text())
            self.assertEqual((root / "docs/doxygen/sources.cfg").read_text(),
                             "# list\nINPUT += Code/T.cpp\nINPUT += Code/C.cpp\n")

    def test_an_existing_tu_input_line_is_not_duplicated(self):
        raw = b"INPUT += Code/T.cpp\nINPUT += Code/A.cpp\n"
        out, n = T.repoint_sources_cfg(raw, {"Code/A.cpp"}, "Code/T.cpp")
        self.assertEqual((out, n), (b"INPUT += Code/T.cpp\n", 1))


class MergeDiagnosticsTests(unittest.TestCase):
    def test_rejected_seed_keeps_trial_errors_without_applying_a_merge(self):
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}],
               donor: [{"target_rva": "0x1010"}]}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors = ["fixture.cpp(1) : error C2065: 'missing' : undeclared identifier"]
            all_errors = errors

            def matched(self, text, rows):
                if text in texts.values():
                    return {r["target_rva"] for r in rows}
                return None

        report = {"accepted": [], "rejected": {}}
        with patch.object(T, "Verifier", return_value=Verifier()), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, report, False, texts=texts)
        self.assertTrue(out["blocked"].startswith("no verified merge of two or more donors"))
        self.assertEqual(out["accepted"], [])
        self.assertEqual(set(out["rejected"]), {tu, donor})
        self.assertTrue(all("C2065" in reason for reason in out["rejected"].values()))
        apply.assert_not_called()

    def test_a_seed_that_fails_under_its_donors_flags_is_retried_with_its_own(self):
        # CrateSystem.cpp, RiderChangeContain.cpp: the donor majority's flags plus a donor's
        # /I shim (bfmealloc without /D_STLP_USE_STATIC_LIB) broke the seed, which verifies
        # under its own `// cl:` line; the seed's own flags are now tried when nothing else works.
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "// cl: /DSEED /Ireference/shims/own\nseed",
                 donor: "// cl: /DDONOR /Ireference/shims/donor\ndonor"}
        don = {tu: [{"target_rva": "0x1000"}],
               donor: [{"target_rva": "0x1010"}, {"target_rva": "0x1020"}]}
        tried = []

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            flags = None
            errors = ["fixture.cpp(1) : error C2950: allocator<char>"]
            all_errors = errors

            def matched(self, text, rows):
                if text in texts.values():
                    return {r["target_rva"] for r in rows}
                tried.append(text)
                # the seed verifies only without the donor's include directory
                return {r["target_rva"] for r in rows} if "/DSEED" in text and "donor" not in text else None

        def fake_compose(tu_, sk, files, texts_, flags, *a, **k):
            return " ".join(flags) + " " + " ".join(files)

        with patch.object(T, "Verifier", return_value=Verifier()),                 patch.object(T, "compose", side_effect=fake_compose),                 patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts=texts)
        self.assertTrue(any("/DSEED" in t and "/Ireference/shims/donor" in t for t in tried))
        self.assertTrue(any("/DSEED" in t and "/Ireference/shims/donor" not in t for t in tried))
        self.assertNotIn("blocked", out)
        self.assertEqual(out["accepted"], [tu, donor])
        apply.assert_not_called()

    def test_a_final_reverify_failure_blocks_instead_of_writing_the_token(self):
        # A PlayerList.cpp merge accepted its donors, but the final re-composition failed to
        # compile; attempt() then returned "compile", and apply() wrote that word as the TU.
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}], donor: [{"target_rva": "0x1010"}]}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors = ["fixture.cpp(1) : fatal error C1001: internal compiler error"]
            all_errors = []
            flags = []

            def __init__(self, fail_from=None):
                self.calls, self.fail_from = 0, fail_from

            def matched(self, text, rows):
                self.calls += 1
                if self.fail_from is not None and self.calls >= self.fail_from:
                    return None
                return {r["target_rva"] for r in rows}

        carry = SimpleNamespace(report=lambda: {}, problems=[])
        probe = Verifier()
        with patch.object(T, "Verifier", return_value=probe), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "Carry", return_value=carry), \
                patch.object(T, "apply", return_value=set()) as apply:
            T._merge(tu, [], don, {"accepted": [], "rejected": {}}, False, texts=texts)
        apply.assert_called_once()
        self.assertEqual(apply.call_args[0][2], "composed")

        flaky = Verifier(fail_from=probe.calls)   # every call from the final re-verification on fails
        with patch.object(T, "Verifier", return_value=flaky), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "Carry", return_value=carry), \
                patch.object(T, "apply", return_value=set()) as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, False, texts=texts)
        apply.assert_not_called()
        self.assertTrue(out["blocked"].startswith("the accepted donors did not re-verify (compile"))
        self.assertIn("C1001", out["blocked"])


class StrategySkipTests(unittest.TestCase):
    """attempt() skips a spelling strategy only when its text repeats one already tried."""

    def test_identical_texts_are_tried_once(self):
        texts = {"union-first": "A", "union-longest": "A", "first": "B", "longest": "B"}
        self.assertEqual(T.distinct_strategies(texts.get), [("union-first", "A"), ("first", "B")])

    def test_a_respelled_typedef_is_tried_even_when_the_errors_name_only_its_caller(self):
        # review 2026-10-28: C2668 names only `choose`; the longest spelling of Arg cures it
        first = "typedef int Arg;\nvoid choose(long); void choose(double);\nvoid g(Arg x) { choose(x); }"
        longest = first.replace("typedef int Arg;", "typedef long Arg;")
        texts = {"union-first": first, "union-longest": longest, "first": first, "longest": longest}
        self.assertEqual([st for st, _ in T.distinct_strategies(texts.get)], ["union-first", "union-longest"])


class AccretionTests(unittest.TestCase):
    """greedy() accretes donors in chunks and bisects a failing chunk."""
    TU = "Code/T.cpp"

    def merge(self, names, fails, dry_run=True):
        """_merge of TU + names; `fails(files)` says whether that composed set loses bytes
        (truthy) or does not compile ("compile").
        Returns (report, compiled donor lists, apply mock)."""
        files = [self.TU] + [f"Code/{n}.cpp" for n in names]
        texts = {f: f"solo {f}" for f in files}
        don = {f: [{"target_rva": f"0x{0x1000 + 16 * i:x}"}] for i, f in enumerate(files)}
        compiled = []

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors, all_errors, flags = [], [], None

            def matched(self, text, rows):
                if text.startswith("solo "):
                    return {r["target_rva"] for r in rows}
                group = text.split("+")
                compiled.append(group)
                why = fails(group)
                if why == "compile":
                    return None
                if why:
                    return set()
                return {r["target_rva"] for r in rows}

        probe = Verifier()

        def compose(tu_, sk, files_, texts_, flags, *a, **k):
            return "+".join(Path(f).stem for f in files_)

        carry = SimpleNamespace(report=lambda: {}, problems=[])
        with patch.object(T, "Verifier", return_value=probe),                 patch.object(T, "compose", side_effect=compose),                 patch.object(T, "Carry", return_value=carry),                 patch.object(T, "apply", return_value=set()) as apply:
            out = T._merge(self.TU, [], don, {"accepted": [], "rejected": {}}, dry_run, texts=texts)
        return out, compiled, apply

    @staticmethod
    def greedy(names, fails):
        acc = ["T"]
        for n in names:
            if not fails(acc + [n]):
                acc.append(n)
        return acc

    def test_a_chunk_that_verifies_is_accepted_in_one_compile(self):
        names = [f"D{i:02}" for i in range(30)]
        out, compiled, _ = self.merge(names, fails=lambda g: False)
        self.assertEqual(len(out["accepted"]), 31)
        # beside the seed screen (one compile per donor, seed + donor), the seed, then chunks
        # of 2, 4, 8, 16 (one trial: it took everything), then the final re-verify
        self.assertLessEqual(len([g for g in compiled if len(g) != 2]), 6)
        self.assertEqual(compiled[-1], ["T"] + names)

    def test_a_failing_chunk_is_bisected_down_to_the_one_bad_donor(self):
        names = [f"D{i:02}" for i in range(30)]
        out, compiled, _ = self.merge(names, fails=lambda g: "D11" in g)
        self.assertNotIn("blocked", out)
        self.assertEqual(sorted(out["accepted"]), sorted([self.TU] + [f"Code/{n}.cpp" for n in names if n != "D11"]))
        self.assertEqual(set(out["rejected"]), {"Code/D11.cpp"})
        self.assertTrue(out["rejected"]["Code/D11.cpp"].startswith("bytes"))
        self.assertLess(len(compiled), 3 * 31)        # well under one compile per donor per order

    def test_the_result_equals_one_by_one_greedy_on_a_small_case(self):
        names = ["A", "B", "C", "D", "E", "F", "G", "H"]
        # C conflicts with A; G conflicts with E; H fails with anything
        def fails(g):
            return ("A" in g and "C" in g) or ("E" in g and "G" in g) or ("H" in g and len(g) > 1)
        out, _, _ = self.merge(names, fails)
        want = self.greedy(names, fails)
        self.assertEqual(sorted(Path(f).stem for f in out["accepted"]), sorted(want))
        self.assertEqual({Path(f).stem for f in out["rejected"]}, {"C", "G", "H"})

    def test_a_compile_reject_that_fails_beside_the_seed_alone_is_screened_out_of_later_orders(self):
        names = [f"D{i:02}" for i in range(12)]
        out, compiled, _ = self.merge(names, fails=lambda g: "compile" if "D03" in g and len(g) > 1 else False)
        self.assertEqual(set(out["rejected"]), {"Code/D03.cpp"})
        self.assertTrue(out["rejected"]["Code/D03.cpp"].startswith("compile"))
        # rejected by the first trial, then screened beside the seed: never in a larger set again
        screened = compiled.index(["T", "D03"])
        self.assertTrue(any("D03" in g and len(g) > 2 for g in compiled[:screened]))
        self.assertFalse(any("D03" in g and len(g) > 2 for g in compiled[screened:]))

    def test_a_byte_reject_beside_the_seed_is_not_screened(self):
        # bytes can depend on another donor's spelling: it stays in the matrix
        names = ["A", "B", "C"]
        out, compiled, _ = self.merge(names, fails=lambda g: "B" in g and "C" not in g)
        self.assertTrue(out["rejected"]["Code/B.cpp"].startswith("bytes"))
        self.assertNotIn(["T", "B"], compiled)

    def test_the_accepted_set_is_still_reverified_before_it_is_applied(self):
        names = [f"D{i}" for i in range(6)]
        out, compiled, apply = self.merge(names, fails=lambda g: False, dry_run=False)
        apply.assert_called_once()
        accepted = ["T"] + names
        # accretion verified it once, and the final re-verify composed it again
        self.assertGreaterEqual(sum(1 for g in compiled if g == accepted), 2)


class LinkGuardTests(unittest.TestCase):
    # LINK-042: GameFont.cpp, statistics.cpp, CrateSystem.cpp, MultiplayerSettings.cpp and
    # htree.cpp linked in the census, then a merge chosen by matched rows alone made them stop.
    TU, A, B = "Code/T.cpp", "Code/A.cpp", "Code/B.cpp"

    @staticmethod
    def context_object(storage=2, section=0, value=0, referent="callee", alias=False):
        import struct
        from test_gate_exploits import coff, TEXT
        sections = [(".text", TEXT | 0x1000, b"\xe8\0\0\0\0\xc3", [(1, 3, 0x14)]),
                    (".data", 0xC0000040, b"data", [])]
        if alias:
            sections.append((".drectve", 0x00100A00, b" /alternatename:callee=other", []))
        data = bytearray(coff(sections, [(".text", 0, 1, 0, 3, 1),
                                       ("f", 0, 1, 0x20, 2, 0),
                                       (referent, value, section, 0x20, storage, 0)]))
        table = struct.unpack_from("<I", data, 8)[0]
        data[table + 18 + 14] = 2  # IMAGE_COMDAT_SELECT_ANY
        return bytes(data)

    def test_portable_context_requires_ordinary_undefined_external_relocations(self):
        self.assertEqual(len(T.portable_comdat_contexts(self.context_object())), 1)
        for options in ({"storage": 3, "section": 2}, {"storage": 105}, {"section": 2},
                        {"value": 4}, {"referent": "?f@?A0x12345678@@"}, {"alias": True}):
            with self.subTest(options=options):
                self.assertEqual(T.portable_comdat_contexts(self.context_object(**options)), {})
        self.assertEqual(T.portable_comdat_contexts(b"truncated"), {})

    def test_identical_digests_cannot_hide_changed_local_referents(self):
        import link_census as LCe
        old = self.context_object(storage=3, section=2, referent="$S1")
        new = old.replace(b"data", b"diff")
        self.assertNotEqual(old, new)
        self.assertEqual(list(LCe._comdat_sections(old))[0][3], list(LCe._comdat_sections(new))[0][3])
        self.assertEqual(T.portable_comdat_contexts(old), {})
        self.assertEqual(T.portable_comdat_contexts(new), {})

    def test_census_context_is_bound_to_the_complete_old_object_hash(self):
        import hashlib
        data = self.context_object()
        digest = hashlib.sha256(data).hexdigest()
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.guard(tmp)
            guard.index["digests"] = {"t.obj": digest}
            path = Path(tmp) / "build/link_census/guard_objects" / (digest + ".obj")
            path.parent.mkdir(parents=True)
            self.assertEqual(guard.census_contexts({0}), {})
            path.write_bytes(data)
            self.assertEqual(guard.census_contexts({0}), {0: T.portable_comdat_contexts(data)})
            path.write_bytes(data + b"changed")
            self.assertEqual(guard.census_contexts({0}), {})

    def index(self):
        import link_check as LC
        return {"meta": {}, "objects": ["t.obj", "a.obj", "b.obj", "x.obj"],
                "blockers": {self.TU: {"object": "t.obj", "linked": True},
                             self.A: {"object": "a.obj", "linked": True},
                             self.B: {"object": "b.obj", "linked": False}},
                "strong": {"?t@@YAXXZ": [0], "?a@@YAXXZ": [1], "?b@@YAXXZ": [2], "?x@@YAXXZ": [3]},
                "comdat": {"?inl@@YAXXZ": [(0, "d1", "retail"), (1, "d1", "retail"), (3, "d1", "retail")]},
                "common": {}, "common_schema": LC.COMMON_SCHEMA, "alternates": {"?al@@YAXXZ": [(1, "?a@@YAXXZ")]},
                "selection": {"exceptions": {}, "owners": {}},
                "excuses": {"runtime": set(), "imported": set(), "stubs": set()},
                "references": {"schema": LC.REFERENCES_SCHEMA, "edges": {"?t@@YAXXZ": frozenset({"?a@@YAXXZ"})},
                               "referenced": {"?t@@YAXXZ", "?a@@YAXXZ"}}}

    def guard(self, tmp, index=None):
        return T.LinkGuard(self.TU, root=tmp, index=index if index is not None else self.index(), truth=object(),
                           rank={"t.obj": 0, "a.obj": 1, "b.obj": 2, "x.obj": 3})

    def reference_proof(self, guard):
        guard.index["digests"] = {name: str(p) * 64 for p, name in enumerate(guard.index["objects"])}
        records = {name: {"digest": guard.index["digests"][name], "roots": set(), "edges": {}, "weaks": ()}
                   for name in guard.index["objects"]}
        records["t.obj"].update(roots={"private"}, edges={"dead_inline": frozenset({"private"})})
        guard.index["references"].update(objects=records, referenced={"private"},
                                         edges={"dead_inline": frozenset({"private"})})
        return records

    def test_replacement_removes_only_proven_old_roots_and_edges(self):
        import link_check as LC
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.guard(tmp)
            self.reference_proof(guard)
            self.assertIsNone(guard.prepare([self.TU]))
            view = guard.view(Path("merged.obj"), {0})
            self.assertFalse(LC.is_referenced(view, "private"))
            self.assertNotIn("dead_inline", view["references"]["edges"])
            self.assertEqual(guard.index["references"]["referenced"], {"private"})
            # The replacement itself can make the dropped definition live.
            LC.add_references(view, [({"private"}, {})])
            self.assertTrue(LC.is_referenced(view, "private"))

    def test_outside_roots_edges_weak_defaults_and_aliases_survive_replacement(self):
        import link_check as LC
        for kind in ("root", "edge", "weak", "alias", "retail", "owner"):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as tmp:
                guard = self.guard(tmp)
                records = self.reference_proof(guard)
                outside = records["x.obj"]
                if kind == "root":
                    outside["roots"] = {"private"}
                elif kind == "edge":
                    outside.update(roots={"dead_inline"}, edges={"dead_inline": frozenset({"private"})})
                elif kind in ("weak", "alias"):
                    outside["roots"] = {"route"}
                    if kind == "weak":
                        outside["weaks"] = (("route", "private"),)
                    else:
                        guard.index["alternates"]["route"] = [(3, "private")]
                else:
                    outside["edges"] = {"kept": frozenset({"private"})}
                    if kind == "retail":
                        guard.index["comdat"]["kept"] = [(3, "digest", "retail")]
                    else:
                        guard.index["selection"]["owners"]["kept"] = {"x.obj"}
                self.assertIsNone(guard.prepare([self.TU]))
                self.assertTrue(LC.is_referenced(guard.view(Path("merged.obj"), {0}), "private"))

    def test_missing_or_unbound_reference_proof_keeps_the_census_reference(self):
        import link_check as LC
        for kind in ("missing", "partial", "digest", "unknown_object", "roots", "edges", "weaks"):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as tmp:
                guard = self.guard(tmp)
                records = self.reference_proof(guard)
                if kind == "missing":
                    del guard.index["references"]["objects"]
                elif kind == "partial":
                    del records["x.obj"]
                elif kind == "digest":
                    records["x.obj"]["digest"] = "f" * 64
                elif kind == "unknown_object":
                    records["unknown.obj"] = records["x.obj"]
                else:
                    records["x.obj"][kind] = "malformed"
                self.assertIsNone(guard.prepare([self.TU]))
                view = guard.view(Path("merged.obj"), {0})
                self.assertTrue(LC.is_referenced(view, "private"))
                self.assertNotIn("objects", view["references"])

    def test_lost_definition_requires_an_outside_or_replacement_reference(self):
        for outside in (False, True):
            with self.subTest(outside=outside), tempfile.TemporaryDirectory() as tmp:
                guard = self.guard(tmp)
                records = self.reference_proof(guard)
                guard.index["strong"]["private"] = [0]
                if outside:
                    records["x.obj"]["roots"] = {"private"}
                why, _ = self.judge(guard, [self.TU], defined=("?t@@YAXXZ",))
                self.assertEqual("no longer defines private, which the census still references" in why, outside)

    def test_gone_objects_and_absorbed_aliases_do_not_retain_old_references(self):
        import link_check as LC
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.guard(tmp)
            records = self.reference_proof(guard)
            records["a.obj"]["roots"] = {"route"}
            guard.index["alternates"]["route"] = [(0, "private")]
            records["b.obj"]["roots"] = {"private"}
            del guard.rank["b.obj"]
            self.assertIsNone(guard.prepare([self.TU]))
            self.assertFalse(LC.is_referenced(guard.view(Path("merged.obj"), {0}), "private"))

    def test_the_merged_object_replaces_every_absorbed_unit_at_the_first_place(self):
        with tempfile.TemporaryDirectory() as tmp:
            g = self.guard(tmp)
            self.assertIsNone(g.prepare([self.TU, self.A, self.B]))
            index = g.index
            view = g.view(Path("merged.obj"), {0, 1})
        self.assertEqual(view["objects"], ["merged.obj", "a.obj", "b.obj", "x.obj"])
        self.assertEqual(set(view["strong"]), {"?b@@YAXXZ", "?x@@YAXXZ"})
        self.assertEqual(view["comdat"]["?inl@@YAXXZ"], [(3, "d1", "retail")])
        self.assertEqual(view["alternates"], {})
        view["references"]["referenced"].add("?new@@YAXXZ")
        # the census index itself is untouched: every trial gets its own view
        self.assertEqual(index["objects"][0], "t.obj")
        self.assertIn("?t@@YAXXZ", index["strong"])
        self.assertNotIn("?new@@YAXXZ", index["references"]["referenced"])

    def test_a_unit_merged_since_the_census_defines_nothing(self):
        # GameWindow.cpp absorbed GameWindowRva0031468CDtor.cpp after the census; that
        # unit's census object still defined ??1Rva0031468C and read as a duplicate.
        index = self.index()
        with tempfile.TemporaryDirectory() as tmp:
            g = T.LinkGuard(self.TU, root=tmp, index=index, truth=object(),
                            rank={"t.obj": 0, "a.obj": 1, "b.obj": 2})   # the next census links no x.obj
            self.assertIsNone(g.prepare([self.TU, self.B]))
            view = g.view(Path("merged.obj"), {0})
        self.assertEqual(set(view["strong"]), {"?a@@YAXXZ", "?b@@YAXXZ"})
        self.assertEqual(view["comdat"]["?inl@@YAXXZ"], [(1, "d1", "retail")])
        self.assertEqual(view["objects"][0], "merged.obj")

    def merge(self, guard, links):
        """_merge of T + A + B with every text matching; `links(files)` says
        whether the merged object of those files links."""
        texts = {self.TU: "seed", self.A: "a", self.B: "b"}
        don = {self.TU: [{"target_rva": "0x1000"}], self.A: [{"target_rva": "0x1010"}],
               self.B: [{"target_rva": "0x1020"}, {"target_rva": "0x1030"}]}
        judged = []

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors, all_errors, flags = [], [], None
            obj = None

            def matched(self, text, rows):
                self.obj = Path(f"build/{text}.obj")
                return {r["target_rva"] for r in rows}

        def check_object(obj, view, truth, source=None):
            files = obj.stem.split("+")
            judged.append((files, view["objects"]))
            bad = [] if links(files) else ["?b_needs@@YAXXZ"]
            return {"unresolved": bad, "duplicates": [], "comdat": [], "addresses": [], "selected": [],
                    "unreferenced_differs": []}

        def compose(tu_, sk, files, texts_, flags, *a, **k):
            return "+".join(Path(f).stem for f in files)

        import link_check as LC
        import link_census as LCe
        every = ([], ["?t@@YAXXZ", "?a@@YAXXZ", "?b@@YAXXZ"], [], [])   # the merge keeps every definition
        with patch.object(T, "Verifier", return_value=Verifier()), \
                patch.object(T, "compose", side_effect=compose), \
                patch.object(LC, "check_object", side_effect=check_object), \
                patch.object(LC, "new_variants", return_value=[]), \
                patch.object(LCe, "object_facts", return_value=every), \
                patch.object(LCe, "common_definitions", return_value=set()), \
                patch.object(T, "apply") as apply:
            out = T._merge(self.TU, [], don, {"accepted": [], "rejected": {}}, True, texts=texts, guard=guard)
        apply.assert_not_called()
        return out, judged

    def test_a_never_linked_donor_that_breaks_a_linked_target_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            out, judged = self.merge(self.guard(tmp), links=lambda files: "B" not in files)
        self.assertNotIn("blocked", out)
        self.assertEqual(sorted(out["accepted"]), [self.A, self.TU])
        self.assertTrue(out["rejected"][self.B].startswith(
            f"link: {self.B} never linked at the census and {self.A}, {self.TU} link; "
            "the merged object would not: unresolved ?b_needs@@YAXXZ"))
        # the merged object sits where the target linked, beside every unit it does not absorb
        self.assertTrue(all(objects[0] == "+".join(files) + ".obj" and objects[3] == "x.obj"
                            for files, objects in judged))

    def test_a_never_linked_donor_is_accepted_when_the_merged_object_still_links(self):
        with tempfile.TemporaryDirectory() as tmp:
            out, judged = self.merge(self.guard(tmp), links=lambda files: True)
        self.assertNotIn("blocked", out)
        self.assertEqual(sorted(out["accepted"]), [self.A, self.B, self.TU])
        self.assertTrue(any(sorted(files) == ["A", "B", "T"] for files, _ in judged))
        self.assertTrue(out["link_guard"].startswith("census-linked: "))

    def test_a_target_that_no_longer_links_with_any_donor_blocks_the_merge(self):
        with tempfile.TemporaryDirectory() as tmp:
            out, _ = self.merge(self.guard(tmp), links=lambda files: files == ["T"])
        self.assertTrue(out["blocked"].startswith("no verified merge of two or more donors"))
        self.assertTrue(out["rejected"][self.A].startswith(f"link: {self.A} links at the census"))

    def test_without_the_census_index_a_merge_touching_a_linked_unit_is_blocked(self):
        import link_check as LC
        with tempfile.TemporaryDirectory() as tmp:
            (Path(tmp) / "reverse").mkdir()
            (Path(tmp) / "reverse/link_status.csv").write_text(
                "source,linked,unresolved,duplicates,comdat_losers,addresses,wrong_selected\n"
                f"{self.TU},yes,0,0,0,0,0\n{self.B},no,1,0,0,0,0\n")
            guard = T.LinkGuard(self.TU, root=tmp)
            fetched = []
            offline = lambda objects=True: fetched.append(objects) or (_ for _ in ()).throw(SystemExit("offline"))
            with patch.object(LC, "INDEX", Path(tmp) / "build/link_census/link_index.pkl"), \
                    patch.object(LC, "ROOT", Path(tmp)), patch.object(LC, "fetch_index", side_effect=offline):
                out, judged = self.merge(guard, links=lambda files: True)
        self.assertEqual(fetched, [False])                     # one index-only download was tried
        self.assertTrue(out["blocked"].startswith("link guard: no census index at build/link_census/link_index.pkl"))
        self.assertIn("the download failed: offline", out["blocked"])
        self.assertIn(f"census-linked: {self.TU}", out["blocked"])
        self.assertEqual((out["accepted"], judged), ([], []))

    def test_a_missing_index_is_downloaded_once_and_used(self):
        import link_check as LC
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "link_index.pkl"
            fetched = []

            def fetch(objects=True):
                fetched.append(objects)
                path.write_bytes(b"index")
            guard = T.LinkGuard(self.TU, root=tmp)
            with patch.object(LC, "INDEX", path), patch.object(LC, "fetch_index", side_effect=fetch), \
                    patch.object(LC, "load_index", return_value=self.index()):
                self.assertIsNotNone(guard.load())
                self.assertIsNotNone(guard.load())
        self.assertEqual(fetched, [False])

    def judge(self, guard, files, defined=("?t@@YAXXZ", "?a@@YAXXZ", "?b@@YAXXZ")):
        """guard.judge of a merged object that links by itself and defines `defined`;
        returns (why, the `previous` new_variants was given)."""
        import link_check as LC
        import link_census as LCe
        import link_debt
        given = {}

        def new_variants(obj, view, truth, previous=None, rank=None):
            given["previous"] = previous
            return []
        clean = {"unresolved": [], "duplicates": [], "comdat": [], "addresses": [], "selected": [],
                 "unreferenced_differs": []}
        with patch.object(LC, "check_object", return_value=clean), \
                patch.object(LC, "new_variants", side_effect=new_variants), \
                patch.object(LCe, "object_facts", return_value=([], list(defined), [], [])), \
                patch.object(LCe, "common_definitions", return_value=set()), \
                patch.object(link_debt, "addresses", return_value=[]):
            self.assertIsNone(guard.prepare(files))
            why = guard.judge(Path("m.obj"), files, "text")
        return why, given.get("previous")

    def ranked_guard(self, tmp, extra=None):
        """A guard whose rank uses link_rank's real object names (build.obj_path)."""
        import build
        name = lambda f: build.obj_path(build.ROOT / f).name
        index = self.index()
        index["objects"] = [name(self.TU), name(self.A), name(self.B), "x.obj"]
        for f in (self.TU, self.A, self.B):
            index["blockers"][f]["object"] = name(f)
        rank = {name(self.TU): 10, name(self.A): 11, name(self.B): 12, "x.obj": 13}
        rank.update({name(f): r for f, r in (extra or {}).items()})
        return T.LinkGuard(self.TU, root=tmp, index=index, truth=object(), rank=rank)

    def test_a_new_donor_that_moves_the_merged_unit_earlier_is_refused(self):
        new = "Code/New.cpp"    # no census object; its rows sit before the target's
        with tempfile.TemporaryDirectory() as tmp:
            why, _ = self.judge(self.ranked_guard(tmp, {new: 5}), [self.TU, new])
            self.assertTrue(any("earlier in link order" in w for w in why))
            why, _ = self.judge(self.ranked_guard(tmp, {new: 20}), [self.TU, new])
            self.assertEqual(why, [])

    def test_a_donor_moved_earlier_loses_its_copy_exemption(self):
        with tempfile.TemporaryDirectory() as tmp:
            g = self.ranked_guard(tmp)
            g.prepare([self.TU, self.A])
            g.previous = {0: {"?inl@@YAXXZ": {"dt"}}, 1: {"?inl@@YAXXZ": {"da"}}}
            _, previous = self.judge(g, [self.TU, self.A])
        # A's copy moves from its own place (11) to the target's (10): breaks_others judges it
        self.assertIn("dt", previous["?inl@@YAXXZ"])          # the target keeps its place: exempt
        self.assertNotIn("da", previous["?inl@@YAXXZ"])       # the moved donor's copy is judged

    def test_a_dropped_definition_the_census_references_is_refused(self):
        with tempfile.TemporaryDirectory() as tmp:
            why, _ = self.judge(self.ranked_guard(tmp), [self.TU, self.A], defined=("?t@@YAXXZ",))
            self.assertIn("no longer defines ?a@@YAXXZ, which the census still references", why)
            why, _ = self.judge(self.ranked_guard(tmp), [self.TU, self.A], defined=("?t@@YAXXZ", "?a@@YAXXZ"))
            self.assertEqual(why, [])

    def test_a_provider_merged_into_a_live_unit_since_the_census_is_not_this_merges_loss(self):
        # Recorder.cpp's unchanged seed read "unresolved ??0Rva0060C5FA": the census's only
        # definer, Rva0060C5FACtor.cpp, was merged into Xfer.cpp after the census.
        import link_check as LC
        import link_census as LCe
        import link_debt
        import build
        donor = build.obj_path(build.ROOT / self.A).name

        def why(owners, rank_extra=(), unresolved="?x@@YAXXZ"):
            rank = {"t.obj": 0, "a.obj": 1, "b.obj": 2, donor: 1}   # the next census links no x.obj
            rank.update(dict.fromkeys(rank_extra, 4))
            found = {"unresolved": [unresolved], "duplicates": [], "comdat": [], "addresses": [],
                     "selected": [], "unreferenced_differs": []}
            with tempfile.TemporaryDirectory() as tmp:
                g = T.LinkGuard(self.TU, root=tmp, index=self.index(), truth=object(), rank=rank, owners=owners)
                with patch.object(LC, "check_object", return_value=found), \
                        patch.object(LC, "new_variants", return_value=[]), \
                        patch.object(LCe, "object_facts", return_value=([], ["?t@@YAXXZ", "?a@@YAXXZ"], [], [])), \
                        patch.object(LCe, "common_definitions", return_value=set()), \
                        patch.object(link_debt, "addresses", return_value=[]):
                    self.assertIsNone(g.prepare([self.TU, self.A]))
                    return g.judge(Path("m.obj"), [self.TU, self.A], "text")
        self.assertEqual(why({"?x@@YAXXZ": {"live.obj"}}, ["live.obj"]), [])
        refused = ["unresolved ?x@@YAXXZ"]
        self.assertEqual(why({}), refused)                                       # no live row holds it
        self.assertEqual(why({"?x@@YAXXZ": {"live.obj"}}), refused)              # its holder will not link
        self.assertEqual(why({"?x@@YAXXZ": {donor}}), refused)                   # this merge should define it
        self.assertEqual(why({"?n@@YAXXZ": {"live.obj"}}, ["live.obj"], "?n@@YAXXZ"),
                         ["unresolved ?n@@YAXXZ"])                               # no census definer moved

    def judge_moved_copy(self, copies, emitted="old", *, outside_rank=13, strong=False, exception=False,
                         unknown_holder=False, portable=True, old_proof=True, cohort_route=None,
                         missing_cohort_proof=False, becomes_referenced=False, alias_only=False):
        """Exercise real variant and keep rules around a two-file merge."""
        import link_check as LC
        import link_census as LCe
        import link_debt
        name = "?inl@@YAXXZ"
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp)
            guard.index["comdat"][name] = copies
            guard.index["strong"]["callee"] = [2]
            if not becomes_referenced:
                guard.index["references"]["referenced"].add(name)
            if alias_only:
                del guard.index["strong"]["callee"]
                guard.index["alternates"]["callee"] = [(3, "target")]
                guard.index["strong"]["target"] = [0]
            outsider = guard.index["objects"][3]
            guard.rank[outsider] = outside_rank
            if strong:
                guard.index["strong"][name] = [3]
                guard.index["selection"]["owners"][name] = {outsider}
            if exception:
                guard.index["selection"]["exceptions"][name] = 3
            if unknown_holder:
                guard.index["selection"]["exceptions"][name] = None
            fact = ([(name, emitted, 21, None)], ["?t@@YAXXZ", "?a@@YAXXZ"], [], [])
            context = lambda digest: (0, digest.encode(), ((1, 0x14, "callee"),))
            contexts = {p: {(name, digest): context(digest)} for p, digest, _ in copies if p in (0, 1)} if old_proof else {}
            guard.before_weaks = {0: set(), 1: set()}
            if missing_cohort_proof:
                del guard.before_weaks[0]
            if cohort_route == "weak":
                guard.before_weaks[0].add("callee")
            elif cohort_route:
                entries = {"strong": [0, 2], "comdat": [(0, "provider", None)],
                           "common": [(0, 4)], "alternates": [(0, "oldTarget")]}
                guard.index[cohort_route]["callee"] = entries[cohort_route]
            obj = Path(tmp) / "merged.obj"
            obj.write_bytes(b"synthetic object facts supplied below")
            clean = {"unresolved": [], "duplicates": [], "comdat": [], "addresses": [],
                     "selected": [], "unreferenced_differs": []}
            def check_object(obj, view, truth):
                if becomes_referenced:
                    view["references"]["referenced"].add(name)
                return clean
            with patch.object(LC, "check_object", side_effect=check_object), \
                    patch.object(LCe, "object_facts", return_value=fact), \
                    patch.object(LCe, "common_definitions", return_value=set()), \
                    patch.object(guard, "census_contexts", return_value=contexts), \
                    patch.object(T, "portable_comdat_contexts", return_value={(name, emitted): context(emitted)} if portable else {}), \
                    patch.object(link_debt, "addresses", return_value=[]):
                self.assertIsNone(guard.prepare([self.TU, self.A]))
                return guard.judge(obj, [self.TU, self.A], "text")

    def test_moving_an_existing_winner_keeps_an_already_losing_outside_copy(self):
        # INI's unchanged functor moves 575 -> 566; ThingFactory at 4304 already lost.
        self.assertEqual(self.judge_moved_copy([(1, "old", None), (3, "other", None)]), [])

    def test_moving_a_copy_across_the_previous_outside_winner_is_refused(self):
        why = self.judge_moved_copy([(1, "old", None), (3, "other", None)], outside_rank=10.5)
        self.assertIn("breaks another unit's copy of ?inl@@YAXXZ", why)

    def test_a_changed_copy_cannot_use_the_moved_donors_old_exemption(self):
        why = self.judge_moved_copy([(1, "old", None), (3, "old", None)], emitted="changed")
        self.assertIn("breaks another unit's copy of ?inl@@YAXXZ", why)

    def test_a_different_absorbed_copy_cannot_replace_the_original_selected_body(self):
        # Both outside losses and selected verdict 'unknown' stay the same, but
        # the chosen implementation changes from the target's old body to A's.
        why = self.judge_moved_copy([(0, "target", None), (1, "old", None), (3, "other", None)])
        self.assertIn("breaks another unit's copy of ?inl@@YAXXZ", why)

    def test_a_moved_old_copy_cannot_displace_the_selected_exclusive_owner(self):
        # The proven copy prevents keep_rule losses; selected-provider identity
        # must independently catch an unproven COMDAT moving before its owner.
        why = self.judge_moved_copy([(1, "old", None), (2, "proven", "retail")],
                                   outside_rank=10.5, strong=True)
        self.assertIn("breaks another unit's copy of ?inl@@YAXXZ", why)

    def test_an_existing_map_selection_and_outside_loss_survive_a_moved_copy(self):
        self.assertEqual(self.judge_moved_copy([(1, "old", None), (3, "other", None)], exception=True), [])

    def test_an_unknown_map_holder_cannot_prove_the_selected_body_unchanged(self):
        self.assertTrue(self.judge_moved_copy([(1, "old", None), (3, "other", None)], unknown_holder=True))

    def test_an_ambiguous_relocation_or_missing_old_object_keeps_the_refusal(self):
        copies = [(1, "old", None), (3, "other", None)]
        self.assertTrue(self.judge_moved_copy(copies, portable=False))
        self.assertTrue(self.judge_moved_copy(copies, old_proof=False))

    def test_another_absorbed_objects_provider_or_route_cannot_be_exempted(self):
        copies = [(1, "old", None), (3, "other", None)]
        for table in ("strong", "comdat", "common", "alternates", "weak"):
            with self.subTest(table=table):
                self.assertTrue(self.judge_moved_copy(copies, cohort_route=table))
        self.assertTrue(self.judge_moved_copy(copies, missing_cohort_proof=True))

    def test_a_previously_unused_copy_cannot_start_charging_an_outside_unit(self):
        self.assertTrue(self.judge_moved_copy([(1, "old", None), (3, "other", None)], becomes_referenced=True))

    def test_an_external_alias_cannot_hide_a_target_in_the_absorbed_cohort(self):
        self.assertTrue(self.judge_moved_copy([(1, "old", None), (3, "other", None)], alias_only=True))

    def test_a_merge_of_units_that_never_linked_needs_no_index(self):
        import link_check as LC
        with tempfile.TemporaryDirectory() as tmp:
            guard = T.LinkGuard(self.TU, root=tmp)    # no link_status.csv: nothing links
            with patch.object(LC, "INDEX", Path(tmp) / "missing.pkl"), \
                    patch.object(LC, "fetch_index", side_effect=SystemExit("offline")):
                out, judged = self.merge(guard, links=lambda files: False)
        self.assertNotIn("blocked", out)
        self.assertEqual(judged, [])
        self.assertEqual(out["link_guard"], "no file of this merge links at the census")


class SplitLinkGuardTests(unittest.TestCase):
    """Real COFF objects and the real census rules; compilation is the fixture."""
    SOURCE, TU, OUTSIDE = "Code/Mixed.cpp", "Code/T.cpp", "Code/Outside.cpp"

    def setUp(self):
        import build
        import link_census as LCe
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        self.stack = contextlib.ExitStack()
        self.addCleanup(self.stack.close)
        self.stack.enter_context(patch.object(build, "ROOT", self.root))
        self.stack.enter_context(patch.object(LCe, "ROOT", self.root))
        self.stack.enter_context(patch.object(T, "ROOT", self.root))
        (self.root / "Code").mkdir()
        (self.root / "reverse").mkdir()
        self.truth = SimpleNamespace(verdict=lambda *args: None)

    def obj(self, stem, defined=(), refs=(), copies=(), aliases=(), common=()):
        import struct
        from test_gate_exploits import coff, TEXT
        sections, symbols, aux_at = [], [], []
        for name in defined:
            sections.append((".text", TEXT, b"\xc3", []))
            symbols.append((name, 0, len(sections), 0x20, 2, 0))
        for name, body in copies:
            sections.append((".text", TEXT | 0x1000, body, []))
            aux_at.append(sum(1 + s[-1] for s in symbols) + 1)
            symbols.extend([(".text", 0, len(sections), 0, 3, 1),
                            (name, 0, len(sections), 0x20, 2, 0)])
        first = sum(1 + s[-1] for s in symbols)
        symbols.extend((name, 0, 0, 0x20, 2, 0) for name in refs)
        if refs:
            name, flags, body, _ = sections[0]
            sections[0] = (name, flags, b"\0" * (4 * len(refs)) + body,
                           [(4 * i, first + i, 6) for i in range(len(refs))])
        symbols.extend((name, size, 0, 0, 2, 0) for name, size in common)
        if aliases:
            sections.append((".drectve", 0x00100A00,
                             " ".join(f"/alternatename:{a}={b}" for a, b in aliases).encode(), []))
        raw = bytearray(coff(sections, symbols))
        table = struct.unpack_from("<I", raw, 8)[0]
        for at in aux_at:
            raw[table + 18 * at + 14] = 2
        path = self.root / "objects" / (stem + ".obj")
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(raw)
        return path

    def setup_guard(self, source_options=None, target_options=None, outside_options=None, existing=True):
        import build
        import link_check as LC
        import link_census as LCe
        source_options, target_options, outside_options = source_options or {}, target_options or {}, outside_options or {}
        (self.root / self.SOURCE).write_text("void move(){}\nvoid stay(){}\n")
        if existing:
            (self.root / self.TU).write_text("void target(){}\n")
        row = lambda n, r, s: dict(name=n, target_rva=r, target_size="1", source=s, status="matched", notes="")
        self.rows = [row("_move", "0x1000", self.SOURCE), row("_stay", "0x3000", self.SOURCE),
                     row("_outside", "0x2000", self.OUTSIDE)]
        if existing:
            self.rows.append(row("_target", "0x4000", self.TU))
        objects = {self.SOURCE: self.obj("original", defined=("_move", "_stay", *source_options.pop("extra", ())), **source_options),
                   self.OUTSIDE: self.obj("outside", defined=("_outside",), **outside_options)}
        if existing:
            objects[self.TU] = self.obj("target", defined=("_target",), **target_options)
        # Give the original objects the names the actual linker inventory uses.
        logical = {}
        for source, obj in objects.items():
            path = obj.parent / build.obj_path(self.root / source).name
            path.write_bytes(obj.read_bytes())
            logical[source] = path
        order = sorted(logical.values(), key=lambda p: next(i for i, o in enumerate(LCe.link_order(self.rows, [])) if o.name == p.name))
        facts = [LCe.object_facts(obj, self.truth) for obj in order]
        owners = LCe.ledger_owners(self.rows, [])
        edges, referenced = LCe.link_references(order, facts, owners)
        index = LC.index_tables(order, facts, dict(owners=owners, exceptions={}), dict(edges=edges, referenced=referenced))
        index.update(blockers={f: dict(object=o.name, linked=True) for f, o in logical.items()},
                     excuses=dict(runtime=set(), imported={}, stubs={}))
        g = T.SplitLinkGuard(self.TU, self.SOURCE, "residual", None, ["0x1000"], root=self.root)
        g.guard.index, g.guard.truth = index, self.truth
        g.guard.rank = {p.name: i for i, p in enumerate(LCe.link_order(self.rows, []))}
        def verifier(source):
            return SimpleNamespace(obj=logical[source], matched=lambda text, rows: {r["target_rva"] for r in rows})
        with patch.object(LCe, "ledger", return_value=self.rows), patch.object(LCe, "data_ledger", return_value=[]), \
                patch.object(T, "Verifier", side_effect=verifier):
            self.assertIsNone(g.prepare([self.SOURCE, self.TU] if existing else [self.SOURCE]))
        self.guard = g
        return g

    def judge(self, residual_options=None, destination_options=None, existing=True):
        residual_options, destination_options = residual_options or {}, destination_options or {}
        self.guard.residual_obj = self.obj("residual", defined=("_stay", *residual_options.pop("extra", ())), **residual_options)
        obj = self.obj("destination", defined=("_move", *(("_target",) if existing else ()),
                                              *destination_options.pop("extra", ())), **destination_options)
        return self.guard.judge(obj, [self.SOURCE, self.TU] if existing else [self.SOURCE], "destination")

    def test_both_split_objects_resolve_each_others_definitions(self):
        import copy
        g = self.setup_guard()
        untouched = copy.deepcopy(g.guard.index)
        self.assertEqual(self.judge(dict(refs=("_move",)), dict(refs=("_stay",))), [])
        self.assertEqual(g.guard.index, untouched)

    def test_residual_and_destination_use_the_post_split_link_order(self):
        import build
        g = self.setup_guard(existing=False)
        rows = [dict(r, source=self.TU) if r["name"] == "_move" else r for r in self.rows]
        records = {self.SOURCE: g.record(self.SOURCE, self.obj("r", defined=("_stay",)), "residual"),
                   self.TU: g.record(self.TU, self.obj("d", defined=("_move",)), "destination")}
        view = g.view(records, rows, [])
        self.assertEqual(view["objects"], [build.obj_path(self.root / f).name for f in (self.TU, self.OUTSIDE, self.SOURCE)])
        self.assertEqual(view["selection"]["owners"]["_move"], {build.obj_path(self.root / self.TU).name})

    def test_new_unresolved_on_either_side_is_refused(self):
        for side in ("residual", "destination"):
            with self.subTest(side=side):
                self.setup_guard()
                args = {side + "_options": dict(refs=("_missing",))}
                self.assertTrue(any("new unresolved: _missing" in why for why in self.judge(**args)))

    def test_new_implicit_definition_duplicate_between_the_sides_is_refused(self):
        self.setup_guard()
        why = self.judge(dict(extra=("_implicit",)), dict(extra=("_implicit",)))
        self.assertTrue(any("new duplicates: _implicit" in item for item in why))

    def test_unchanged_unrelated_debt_is_retained_and_does_not_block(self):
        self.setup_guard(source_options=dict(refs=("_old_missing",)))
        self.assertEqual(self.judge(dict(refs=("_old_missing",))), [])

    def test_old_donor_debt_cannot_break_a_previously_clean_destination(self):
        self.setup_guard(source_options=dict(refs=("_old_missing",)))
        why = self.judge(destination_options=dict(refs=("_old_missing",)))
        self.assertTrue(any(self.TU in item and "link-clean original" in item for item in why))

    def test_an_unrowed_provider_needed_by_an_outside_consumer_cannot_disappear(self):
        self.setup_guard(source_options=dict(extra=("_helper",)), outside_options=dict(refs=("_helper",)))
        self.assertIn("outside consumers lose provider _helper", self.judge())

    def test_moving_the_same_provider_to_the_destination_preserves_outside_consumers(self):
        self.setup_guard(source_options=dict(extra=("_helper",)), outside_options=dict(refs=("_helper",)))
        self.assertEqual(self.judge(destination_options=dict(extra=("_helper",))), [])

    def test_a_removed_alias_cannot_unresolve_an_outside_consumer(self):
        self.setup_guard(source_options=dict(aliases=(("_alias", "_outside"),)), outside_options=dict(refs=("_alias",)))
        self.assertIn("outside consumers lose provider _alias", self.judge())

    def test_an_alias_cannot_silently_retarget_an_outside_consumer(self):
        self.setup_guard(source_options=dict(aliases=(("_alias", "_outside"),)), outside_options=dict(refs=("_alias",)))
        why = self.judge(destination_options=dict(aliases=(("_alias", "_move"),)))
        self.assertIn("outside alias route changes for _alias", why)

    def test_duplicate_identical_alias_directives_keep_the_same_route(self):
        alias = dict(aliases=(("_alias", "_outside"),))
        self.setup_guard(source_options=alias, outside_options=dict(refs=("_alias",)))
        self.assertEqual(self.judge(dict(alias), dict(alias)), [])

    def test_a_new_earlier_copy_cannot_make_an_outside_comdat_lose(self):
        self.setup_guard(source_options=dict(copies=(("_fold", b"\xc3"),)),
                         outside_options=dict(copies=(("_fold", b"\xc3"),), refs=("_fold",)))
        why = self.judge(destination_options=dict(copies=(("_fold", b"\x90\xc3"),)))
        self.assertIn("new outside COMDAT losers for _fold", why)

    def test_an_unchanged_moved_copy_does_not_hide_or_increase_existing_outside_losses(self):
        self.setup_guard(source_options=dict(copies=(("_fold", b"\xc3"),)),
                         outside_options=dict(copies=(("_fold", b"\x90\xc3"),), refs=("_fold",)))
        self.assertEqual(self.judge(destination_options=dict(copies=(("_fold", b"\xc3"),))), [])

    def test_moved_unknown_copy_needs_raw_relocation_context_as_well_as_a_digest(self):
        with patch.object(T, "portable_comdat_contexts", return_value={}):
            self.setup_guard(source_options=dict(copies=(("_fold", b"\xc3"),)),
                             outside_options=dict(refs=("_fold",)))
            why = self.judge(destination_options=dict(copies=(("_fold", b"\xc3"),)))
        self.assertTrue(any("lacks matching private/weak-free context" in item for item in why))

    def test_common_provider_can_move_and_resolve_a_cross_file_reference(self):
        self.setup_guard(source_options=dict(common=(("_data", 4),)), outside_options=dict(refs=("_data",)))
        self.assertEqual(self.judge(dict(refs=("_data",)), dict(common=(("_data", 4),))), [])

    def test_changed_map_selection_is_inconclusive_and_refused(self):
        g = self.setup_guard(source_options=dict(copies=(("_fold", b"\xc3"),)))
        g.guard.index["selection"]["exceptions"]["_fold"] = 0
        g.before["selection"]["exceptions"]["_fold"] = 0
        self.assertTrue(any("changed /MAP selection" in why for why in
                            self.judge(destination_options=dict(copies=(("_fold", b"\xc3"),)))))

    def test_missing_candidate_object_fails_closed(self):
        self.setup_guard()
        self.guard.residual_obj = self.root / "missing.obj"
        self.assertTrue(any("evidence unavailable" in why for why in self.guard.judge(
            self.root / "also-missing.obj", [self.SOURCE], "text")))

    def test_truncated_candidate_object_fails_closed(self):
        self.setup_guard()
        bad = self.root / "truncated.obj"
        bad.write_bytes(b"bad coff")
        self.guard.residual_obj = bad
        self.assertTrue(any("unreadable split object" in why for why in self.guard.judge(bad, [self.SOURCE], "text")))

    def test_ledger_change_invalidates_a_cached_success(self):
        self.setup_guard()
        self.assertEqual(self.judge(), [])
        (self.root / "reverse/functions.csv").write_bytes(b"changed\n")
        self.assertEqual(self.judge(), ["split compiler/ledger inputs changed during verification; retry"])

    def test_original_source_must_still_equal_the_text_that_was_carved(self):
        g = self.setup_guard()
        g.expected_source = b"earlier source revision"
        self.assertEqual(g.prepare([self.SOURCE]), "mixed source changed while planning the split; retry")

    def test_a_concurrent_source_edit_invalidates_cached_success(self):
        self.setup_guard()
        self.assertEqual(self.judge(), [])
        (self.root / self.SOURCE).write_text("changed")
        self.assertEqual(self.judge(), ["split source changed during verification; retry"])

    def split(self, broken_residual=False, dry_run=False):
        import link_census as LCe
        guard = self.setup_guard()
        owner = self
        class Verifier:
            flags, errors, all_errors = None, [], []
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            def __init__(self, source):
                self.source, self.obj = source, None
            def matched(self, text, rows):
                names = tuple("_" + n for n in re.findall(r"void\s+(\w+)\s*\(", text))
                bad = broken_residual and names == ("_stay",)
                self.obj = owner.obj("compiled-" + str(len(text)) + "-" + "-".join(names),
                                     defined=names, refs=("_missing",) if bad else ())
                return {r["target_rva"] for r in rows}
        assigned = {int(r["target_rva"], 16): self.TU.lower() for r in self.rows}
        with patch.dict(T._CACHE, {"assigned": assigned}), \
                patch.object(T, "file_rows", side_effect=lambda p: [r for r in self.rows if r["source"] == p]), \
                patch.object(T, "breakdown", return_value={self.TU: [self.rows[0]], "Other": [self.rows[1]]}), \
                patch.object(T, "refusal", return_value=None), patch.object(T, "included_by", return_value=[]), \
                patch.object(T, "skeleton", return_value=[]), patch.object(T, "Verifier", Verifier), \
                patch.object(T, "LinkGuard", return_value=guard.guard), \
                patch.object(T, "compose", side_effect=lambda tu, sk, files, texts, *args: "\n".join(texts[f] for f in files)), \
                patch.object(LCe, "ledger", return_value=self.rows), patch.object(LCe, "data_ledger", return_value=[]), \
                patch.object(T, "apply_split", return_value={}) as apply:
            report = T.split(self.SOURCE, self.TU, dry_run=dry_run, claim=False)
        return report, apply

    def test_split_runs_the_guard_before_writing_either_file(self):
        report, apply = self.split(broken_residual=True)
        self.assertIn("blocked", report)
        self.assertIn("link:", report["rejected"][self.SOURCE])
        apply.assert_not_called()

    def test_verified_split_is_applied_and_dry_run_is_read_only(self):
        for dry_run in (False, True):
            with self.subTest(dry_run=dry_run):
                report, apply = self.split(dry_run=dry_run)
                self.assertNotIn("blocked", report)
                if dry_run:
                    apply.assert_not_called()
                else:
                    apply.assert_called_once()


class ClaimTests(unittest.TestCase):
    def test_the_scope_is_the_tu_every_donor_and_every_moved_row(self):
        don = {"Code/T.cpp": [{"target_rva": "0x00001000"}],
               "Code/A.cpp": [{"target_rva": "0x00001010"}, {"target_rva": "0x00001020"}]}
        self.assertEqual(T.claim_keys("Code/T.cpp", don),
                         ["file:Code/T.cpp", "file:Code/A.cpp", "0x00001000", "0x00001010", "0x00001020"])

    def test_a_held_key_blocks_the_merge_before_anything_is_written(self):
        don = {"Code/A.cpp": [{"target_rva": "0x00001010"}]}
        calls = []

        def claim(keys, note="", root=None):
            calls.append(keys)
            return SimpleNamespace(refused=[T.claims.key_of("file:Code/A.cpp")], claimed=[])

        original = T.claims.claim
        T.claims.claim = claim
        try:
            held = T.claim_scope("Code/T.cpp", don)
        finally:
            T.claims.claim = original
        self.assertEqual(held, ["file:Code/A.cpp"])
        self.assertEqual(len(calls), 1)

    def test_a_refused_claim_push_is_not_reported_as_another_workers_hold(self):
        don = {"Code/A.cpp": [{"target_rva": "0x00001010"}]}
        keys = T.claim_keys("Code/T.cpp", don)
        everything = [T.claims.key_of(k) for k in keys]
        original = T.claims.claim
        T.claims.claim = lambda keys, note="", root=None: SimpleNamespace(
            refused=everything, unconfirmed=everything, claimed=[])
        try:
            held = T.claim_scope("Code/T.cpp", don)
        finally:
            T.claims.claim = original
        self.assertEqual(list(held), keys)
        message = T.held_message(held)
        self.assertTrue(message.startswith("claim push failed"), message)
        self.assertNotIn("another worker", message.split("(")[0])
        # a key a peer really holds still reads as held, even beside unconfirmed ones
        T.claims.claim = lambda keys, note="", root=None: SimpleNamespace(
            refused=everything, unconfirmed=everything[1:], claimed=[])
        try:
            held = T.claim_scope("Code/T.cpp", don)
        finally:
            T.claims.claim = original
        self.assertEqual(T.held_message(held), "held by another worker: file:Code/T.cpp")
        unavailable = T.Held(["(claims unavailable: x)"])
        unavailable.unavailable = "x"
        self.assertTrue(T.held_message(unavailable).startswith("claims unavailable"))

    def test_a_partly_won_scope_is_released_when_another_worker_holds_the_rest(self):
        T._CACHE.clear()
        T._CACHE["ledger"] = [{"name": "?a@@YAXXZ", "export_rva": "", "target_rva": "0x00001000", "target_size": "8",
                               "source": "Code/A.cpp", "status": "matched", "notes": ""},
                              {"name": "?b@@YAXXZ", "export_rva": "", "target_rva": "0x00001010", "target_size": "8",
                               "source": "Code/B.cpp", "status": "matched", "notes": ""}]
        T._CACHE["map"] = [{"rva": "0x00001000", "size": "8", "kind": "code", "tu": "Code/T.cpp", "confidence": "approved",
                            "by": "-", "evidence": "", "source": "Code/A.cpp"},
                           {"rva": "0x00001010", "size": "8", "kind": "code", "tu": "Code/T.cpp", "confidence": "approved",
                            "by": "-", "evidence": "", "source": "Code/B.cpp"}]
        T._CACHE["stale"] = False
        released = []
        original_claim, original_release = T.claims.claim, T.claims.release
        T.claims.claim = lambda keys, note="", root=None: SimpleNamespace(
            refused=[T.claims.key_of("file:Code/A.cpp")], claimed=[k for k in keys if k != "file:Code/A.cpp"])
        T.claims.release = lambda keys, **kw: released.append(list(keys))
        original_refusal, T.refusal = T.refusal, lambda f, rows: None
        try:
            rep = T.merge("Code/T.cpp", dry_run=False, claim=True)
        finally:
            T.claims.claim, T.claims.release = original_claim, original_release
            T.refusal = original_refusal
            T._CACHE.clear()
        self.assertTrue(rep["blocked"].startswith("held by another worker"))
        self.assertEqual(released, [["file:Code/T.cpp", "file:Code/A.cpp", "file:Code/B.cpp", "0x00001000", "0x00001010"]])

    def test_a_merge_blocked_after_claiming_releases_its_scope(self):
        don = {"Code/T.cpp": [{"target_rva": "0x00001000", "status": "matched"}],
               "Code/A.cpp": [{"target_rva": "0x00001010", "status": "matched"}]}
        released = []
        saved = (T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release)
        T.skeleton = lambda tu: []
        T.donors = lambda tu, sk: (don, {}, {})
        T.claim_scope = lambda tu, d: []
        T._merge = lambda tu, sk, d, report, dry_run: dict(report, blocked="no verified merge")
        T.claims.release = lambda keys, **kw: released.append(keys)
        try:
            report = T.merge("Code/T.cpp")
        finally:
            T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release = saved
        self.assertEqual(report["blocked"], "no verified merge")
        self.assertEqual(released, [T.claim_keys("Code/T.cpp", don)])


if __name__ == "__main__":
    unittest.main()


class LinkGuardPlacementTests(unittest.TestCase):
    def test_the_guard_ranks_objects_in_the_census_link_order_skipping_fold_rows(self):
        # LINK-133: a fold row (an address another object's row claims) places
        # no object, in the census, link_check and the merge guard alike.
        import link_check as LC
        import link_census as LCe
        rows = [{"name": "a", "source": "Code/Owner.cpp", "target_rva": "0x100", "notes": ""},
                {"name": "b", "source": "Code/Owner.cpp", "target_rva": "0x110", "notes": ""},
                {"name": "c", "source": "Code/Mid.cpp", "target_rva": "0x500", "notes": ""},
                {"name": "d", "source": "Code/Mover.cpp", "target_rva": "0x100", "notes": "ICF twin"},
                {"name": "e", "source": "Code/Mover.cpp", "target_rva": "0x900", "notes": ""}]
        index = {"blockers": {}, "objects": [], **{table: {} for table, _ in T.LINK_TABLES}}
        guard = T.LinkGuard("Code/Owner.cpp", index=index)
        with patch.object(LCe, "ledger", return_value=rows), patch.object(LCe, "data_ledger", return_value=[]), \
                patch.object(LCe, "RetailTruth", side_effect=lambda rows: object()), \
                patch.object(LC, "require_common_index", return_value=None), \
                patch.object(T.LinkGuard, "census_contexts", return_value={}):
            self.assertIsNone(guard.prepare([]))
            order = [p.name for p in LCe.link_order(rows, [])]
        self.assertEqual(sorted(guard.rank, key=guard.rank.get), order)
        import build
        self.assertEqual(order, [build.obj_path(build.ROOT / f"Code/{s}.cpp").name for s in ("Owner", "Mid", "Mover")])
