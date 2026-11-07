"""tu_skeleton's merge lane: verified flags, redefinition repair, repointing and claims."""
import contextlib
import csv
import json
import os
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


class SavedMergePlanTests(unittest.TestCase):
    def setUp(self):
        import name_scoped
        handoff = patch.object(name_scoped, "RELATED_WORK_HANDOFF", True)
        handoff.start()
        self.addCleanup(handoff.stop)

    def test_successful_merge_handoff_uses_the_final_tu_not_deleted_donors(self):
        report = T.view_hint(dict(accepted=["Code/A.cpp", "Code/B.cpp"], rejected={}),
                             "Code/Final.cpp", {})
        self.assertEqual(report["scoped_naming"]["files"], ["Code/Final.cpp"])
        self.assertIn("--files Code/Final.cpp", report["follow-up"][0])
        self.assertNotIn("Code/A.cpp", report["scoped_naming"]["command"])

    def test_blocked_merge_does_not_offer_a_naming_task(self):
        report = T.view_hint(dict(accepted=["Code/A.cpp"], rejected={}, blocked="bytes"),
                             "Code/Final.cpp", {})
        self.assertNotIn("scoped_naming", report)

    def test_dry_run_plan_is_selected_after_claim_without_repeating_search(self):
        with tempfile.TemporaryDirectory() as folder, patch.object(T, "ROOT", Path(folder)), \
                patch.object(T, "merge_plan_state", return_value="same-tree"), \
                patch.object(T, "skeleton", return_value=[]), \
                patch.object(T, "donors", return_value=({"Code/T.cpp": [], "Code/A.cpp": []}, {}, {})), \
                patch.object(T, "header_queue_rows", return_value={}), \
                patch.object(T, "claim_scope", return_value=[]):
            calls = []

            def search(tu, sk, don, report, dry_run):
                calls.append(dry_run)
                return dict(report, accepted=["Code/T.cpp", "Code/A.cpp"], text="merged", _plan={
                    "accepted": ["Code/T.cpp", "Code/A.cpp"], "text": "merged", "baseline": [],
                    "rows": 2, "rejected": {}, "flags": [], "verifier_flags": None})

            with patch.object(T, "_merge", side_effect=search), \
                    patch.object(T, "reuse_merge_plan", side_effect=lambda tu, don, report, plan, dry_run:
                                 dict(report, accepted=plan["accepted"], plan_reused=True, subject="merge")) as reuse:
                T.merge("Code/T.cpp", dry_run=True)
                report = T.merge("Code/T.cpp")
            self.assertEqual(calls, [True])
            self.assertEqual(reuse.call_count, 1)
            self.assertTrue(report["plan_reused"])
            self.assertEqual(report["scoped_naming"]["files"], ["Code/T.cpp"])
            self.assertNotIn("Code/A.cpp", report["scoped_naming"]["command"])

    def test_plan_requires_same_tree_and_tu_inputs(self):
        with tempfile.TemporaryDirectory() as folder, patch.object(T, "ROOT", Path(folder)), \
                patch.object(T, "merge_plan_state", return_value="tree-a"):
            plan = {"accepted": ["Code/A.cpp", "Code/B.cpp"], "text": "unit"}
            T.save_merge_plan("Code/T.cpp", "tree-a", "inputs-a", plan)
            self.assertEqual(T.load_merge_plan("Code/T.cpp", "tree-a", "inputs-a")["text"], "unit")
            self.assertIsNone(T.load_merge_plan("Code/T.cpp", "tree-b", "inputs-a"))
            self.assertIsNone(T.load_merge_plan("Code/T.cpp", "tree-a", "inputs-b"))

    @contextlib.contextmanager
    def saved_cohort(self):
        donors = {"Code/T.cpp": [], "Code/A.cpp": [], "Code/Rejected.cpp": []}
        plan = {"tu_file": "Code/T.cpp", "accepted": ["Code/T.cpp", "Code/A.cpp"]}
        with tempfile.TemporaryDirectory() as folder, patch.object(T, "ROOT", Path(folder)), \
                patch.object(T, "merge_plan_state", return_value="same-tree"), \
                patch.object(T, "skeleton", return_value=[]), \
                patch.object(T, "donors", return_value=(donors, {}, {})), \
                patch.object(T, "header_queue_rows", return_value={}), \
                patch.object(T, "load_merge_plan", return_value=plan), \
                patch.object(T.claims, "release") as release, \
                patch.object(T, "_merge") as search:
            yield donors, plan, release, search

    def test_saved_cohort_does_not_claim_rejected_donors(self):
        with self.saved_cohort() as (donors, plan, release, search):
            def claim(tu, scope):
                return ["file:Code/Rejected.cpp"] if "Code/Rejected.cpp" in scope else []

            def reuse(tu, scope, report, saved, dry_run):
                self.assertEqual(claimed.call_count, 1)
                self.assertEqual(scope, donors)  # link checks retain the full input closure
                return dict(report, accepted=saved["accepted"], plan_reused=True)

            with patch.object(T, "claim_scope", side_effect=claim) as claimed, \
                    patch.object(T, "reuse_merge_plan", side_effect=reuse):
                result = T.merge("Code/T.cpp")
            self.assertTrue(result["plan_reused"])
            self.assertEqual(set(claimed.call_args.args[1]), set(plan["accepted"]))
            search.assert_not_called()
            release.assert_not_called()

    def test_held_accepted_donor_blocks_before_plan_checks(self):
        with self.saved_cohort() as (donors, plan, release, search), \
                patch.object(T, "claim_scope", return_value=["file:Code/A.cpp"]), \
                patch.object(T, "reuse_merge_plan") as reuse:
            result = T.merge("Code/T.cpp")
            self.assertIn("Code/A.cpp", result["blocked"])
            reuse.assert_not_called()
            search.assert_not_called()
            accepted = {f: donors[f] for f in plan["accepted"]}
            release.assert_called_once_with(T.claim_keys("Code/T.cpp", accepted))

    def test_failed_plan_cannot_search_until_full_scope_is_claimed(self):
        for held in ([], ["file:Code/Rejected.cpp"]):
            with self.subTest(held=held), self.saved_cohort() as (donors, plan, release, search), \
                    patch.object(T, "claim_scope", side_effect=[[], held]) as claimed, \
                    patch.object(T, "reuse_merge_plan", return_value=None):
                def fallback(tu, sk, scope, report, dry_run):
                    self.assertEqual(claimed.call_count, 2)
                    self.assertEqual(claimed.call_args.args[1], donors)
                    return dict(report, accepted=plan["accepted"])

                search.side_effect = fallback
                result = T.merge("Code/T.cpp")
                self.assertEqual(set(claimed.call_args_list[0].args[1]), set(plan["accepted"]))
                self.assertEqual(claimed.call_args_list[1].args[1], donors)
                if held:
                    self.assertIn("Code/Rejected.cpp", result["blocked"])
                    search.assert_not_called()
                    release.assert_called_once_with(T.claim_keys("Code/T.cpp", donors))
                else:
                    self.assertNotIn("blocked", result)
                    search.assert_called_once()
                    release.assert_not_called()

    def test_malformed_saved_cohort_requires_full_claim_scope(self):
        for accepted in ([], ["Code/T.cpp", "Code/Unknown.cpp"],
                         ["Code/T.cpp", "Code/T.cpp"], ["Code/T.cpp", None], ["Code/A.cpp"]):
            with self.subTest(accepted=accepted), self.saved_cohort() as (donors, plan, release, search), \
                    patch.object(T, "claim_scope", return_value=["file:Code/Rejected.cpp"]) as claimed, \
                    patch.object(T, "reuse_merge_plan") as reuse:
                plan["accepted"] = accepted
                result = T.merge("Code/T.cpp")
                self.assertIn("blocked", result)
                claimed.assert_called_once_with("Code/T.cpp", donors)
                reuse.assert_not_called()
                search.assert_not_called()
                release.assert_called_once_with(T.claim_keys("Code/T.cpp", donors))

    def test_reused_plan_still_verifies_bytes_link_and_carry_before_apply(self):
        with tempfile.TemporaryDirectory() as folder, patch.object(T, "ROOT", Path(folder)):
            source = Path(folder) / "Code/A.cpp"
            source.parent.mkdir()
            source.write_text("int a() { return 1; }\n")
            donor = {"Code/A.cpp": [{"target_rva": "0x1000"}]}
            plan = {"accepted": ["Code/A.cpp"], "text": "merged", "baseline": ["0x1000"],
                    "rows": 1, "rejected": {}, "flags": [], "verifier_flags": None}
            state = {"bytes": {"0x1000"}, "link": [], "carry": []}
            applied = []

            class Verifier:
                def __init__(self, *args, **kw):
                    self.obj = "compiled.obj"

                def matched(self, text, rows):
                    return state["bytes"]

            class Guard:
                def __init__(self, *args):
                    pass

                def load(self):
                    pass

                def linked(self, files):
                    return []

                def judge(self, obj, files, text):
                    return state["link"]

            class Carry:
                def __init__(self, *args):
                    self.problems = state["carry"]

                def report(self):
                    return {}

            with patch.object(T, "Verifier", Verifier), patch.object(T, "LinkGuard", Guard), \
                    patch.object(T, "Carry", Carry), patch.object(T, "apply", side_effect=lambda *a, **kw: applied.append(a) or {}):
                state["bytes"] = set()
                self.assertIsNone(T.reuse_merge_plan("Code/T.cpp", donor, {}, plan, False))
                state["bytes"] = {"0x1000"}
                state["link"] = ["lost"]
                self.assertIsNone(T.reuse_merge_plan("Code/T.cpp", donor, {}, plan, False))
                state["link"] = []
                state["carry"] = ["changed"]
                self.assertIsNone(T.reuse_merge_plan("Code/T.cpp", donor, {}, plan, False))
                state["carry"] = []
                result = T.reuse_merge_plan("Code/T.cpp", donor, {}, plan, False)
                self.assertTrue(result["plan_reused"])
                self.assertEqual(len(applied), 1)


class VerifierFoldedAddressTests(unittest.TestCase):
    """An ICF address two donors' rows share is matched only when every row there
    matches (Science.cpp merge, 0x001FF743: the ScienceType tree dtor matched and
    hid the folded int-tree dtor that ./build.sh failed)."""

    def verifier(self, results):
        import hashlib
        v = T.Verifier.__new__(T.Verifier)
        v.sm, v.cache = {}, {}
        v.effective = lambda text, rows: text
        v.cache[hashlib.sha1(b"tu").hexdigest()[:16]] = (Path("x.obj"), [])

        def compile_function(row, sm, obj):
            if results[row["name"]] is None:
                raise SystemExit("symbol not found in object")
            return {"bytes": results[row["name"]], "target": b"ok"}
        v.B = SimpleNamespace(compile_function=compile_function)
        return v

    def rows(self):
        return [{"name": "fold_a", "target_rva": "0x1000"}, {"name": "fold_b", "target_rva": "0x1000"},
                {"name": "plain", "target_rva": "0x2000"}]

    def test_a_missed_twin_unmatches_the_shared_address(self):
        v = self.verifier({"fold_a": b"ok", "fold_b": b"bad", "plain": b"ok"})
        self.assertEqual(v.matched("tu", self.rows()), {"0x2000"})

    def test_an_absent_twin_unmatches_the_shared_address(self):
        v = self.verifier({"fold_a": b"ok", "fold_b": None, "plain": b"ok"})
        self.assertEqual(v.matched("tu", self.rows()), {"0x2000"})

    def test_every_twin_matching_keeps_the_address(self):
        v = self.verifier({"fold_a": b"ok", "fold_b": b"ok", "plain": b"bad"})
        self.assertEqual(v.matched("tu", self.rows()), {"0x1000"})


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

    def test_inline_depth_scope_stays_around_global_initializers(self):
        # GameWindowManagerScript.cpp's four callback strings must call the
        # out-of-line constructor. Hoisting the reset ahead of them loses rows.
        scope = ('#pragma inline_depth( 0 )\n'
                 'AsciiString systemName;\nAsciiString inputName;\n'
                 'AsciiString tooltipName;\nAsciiString drawName;\n'
                 '#pragma inline_depth()')
        text = 'struct AsciiString { AsciiString(); };\n' + scope + '\nint f() { return 1; }\n'
        for skeleton in (True, False):
            out = self.compose(text, skeleton)
            start = out.index('#pragma inline_depth( 0 )')
            end = out.index('#pragma inline_depth()') + len('#pragma inline_depth()')
            self.assertEqual(T.token_seq(scope), T.token_seq(out[start:end]))
            self.assertLess(out.index('struct AsciiString'), start)

    def test_objects_after_the_last_body_keep_following_every_body(self):
        # INIAudioEventInfo.cpp's BlockParse nodes: hoisted above the bodies their
        # initializers became _$E1.. instead of retail's _$E2.., losing six rows.
        node = 'Node theTrackNode( "Track", parseTrack );'
        text = ('struct Node { Node(const char *, void (*)()); };\n'
                'void parseTrack() {}\n'
                'typedef void (*Parse)();\nextern Node *theList;\nstruct Late;\n'
                'void parseLater();\n' + node + '\nNode plain;\n')
        sk = [({"rva": "0x1000", "size": "8"}, {"source": "Seed.cpp", "status": "matched"}),
              ({"rva": "0x1010", "size": "8"}, {"source": "Donor.cpp", "status": "matched"})]
        texts = {"Seed.cpp": text, "Donor.cpp": "int g() { return 2; }\n"}
        out = T.compose("Seed.cpp", sk, ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        body = out.index("int g()")
        self.assertGreater(out.index(node), body)
        self.assertGreater(out.index("Node plain;"), out.index(node))
        for hoisted in ("typedef void (*Parse)();", "extern Node *theList;",
                        "struct Late;", "void parseLater();"):
            self.assertLess(out.index(hoisted), out.index("void parseTrack()"), hoisted)
        self.assertEqual(out.count(node), 1)

    def test_separate_inline_depth_declaration_scopes_keep_their_resets(self):
        first = '#pragma inline_depth(0)\nA first;\n#pragma inline_depth()'
        second = '#pragma inline_depth(1)\nA second;\n#pragma inline_depth()'
        out = self.compose(first + '\nint between;\n' + second + '\n')
        self.assertIn(first, out)
        self.assertIn(second, out)
        self.assertEqual(out.count('#pragma inline_depth()'), 2)
        self.assertLess(out.index(first), out.index('int between;'))
        self.assertLess(out.index('int between;'), out.index(second))

    def test_unterminated_region_is_not_silently_closed(self):
        out = self.compose("#ifdef DEBUG\nint f() { return 1; }\n")
        self.assertIn("#ifdef DEBUG\n", out)
        self.assertNotIn("#endif", out)
class ExplicitInstantiationCompositionTests(unittest.TestCase):
    definition = "template <class T> T identity(T value) { return value; }"
    instantiation = "template float identity<float>(float value);"

    def compose(self, text, skeleton):
        sk = [({"rva": "0x1000", "size": "8"},
               {"source": "Seed.cpp", "status": "matched"})] if skeleton else []
        return T.compose("Seed.cpp", sk, ["Seed.cpp"], {"Seed.cpp": text}, [], "first")

    def test_function_instantiation_follows_the_primary_template(self):
        for skeleton in (True, False):
            out = self.compose(self.definition + "\n" + self.instantiation + "\n", skeleton)
            self.assertLess(out.index(self.definition), out.index(self.instantiation))
            self.assertEqual(out.count(self.instantiation), 1)

    def test_conditional_instantiation_follows_the_primary_template(self):
        guarded = "#if FLOATS\n#if ENABLED\n" + self.instantiation + "\n#endif\n#endif"
        for skeleton in (True, False):
            out = self.compose(self.definition + "\n" + guarded + "\n", skeleton)
            self.assertIn(guarded, out)
            self.assertLess(out.index(self.definition), out.index(guarded))

    def test_instantiation_keeps_its_optimization_scope(self):
        scoped = '#pragma optimize("s", on)\n' + self.instantiation + '\n#pragma optimize("", on)'
        for skeleton in (True, False):
            out = self.compose(self.definition + "\n" + scoped + "\n", skeleton)
            positions = [out.index(x) for x in (self.definition,
                         '#pragma optimize("s", on)', self.instantiation,
                         '#pragma optimize("", on)')]
            self.assertEqual(positions, sorted(positions))

    def test_instantiation_before_a_later_include_keeps_its_position(self):
        text = self.definition + "\n" + self.instantiation + '\n#include "after.h"\nint f() { return 0; }\n'
        for skeleton in (True, False):
            out = self.compose(text, skeleton)
            positions = [out.index(x) for x in (self.definition, self.instantiation,
                         '#include "after.h"', 'int f()')]
            self.assertEqual(positions, sorted(positions))

    def test_identical_guarded_instantiations_keep_each_donors_scope(self):
        guarded = "#if FLOATS\n" + self.instantiation + "\n#endif"
        sk = [({"rva": "0x1000", "size": "8"}, {"source": "Seed.cpp", "status": "matched"}),
              ({"rva": "0x1010", "size": "8"}, {"source": "Donor.cpp", "status": "matched"})]
        texts = {"Seed.cpp": self.definition + '\n#pragma optimize("s", on)\n' +
                             guarded + '\n#pragma optimize("", on)\n',
                 "Donor.cpp": self.definition + '\n#pragma optimize("t", off)\n' +
                              guarded + '\n#pragma optimize("", on)\n'}
        out = T.compose("Seed.cpp", sk, list(texts), texts, [], "first")
        self.assertEqual(out.count(guarded), 2)
        first = out.index(guarded)
        second = out.index(guarded, first + len(guarded))
        self.assertLess(out.index('#pragma optimize("s", on)'), first)
        self.assertLess(first, out.index('#pragma optimize("", on)'))
        self.assertLess(out.index('#pragma optimize("t", off)'), second)
        self.assertLess(second, out.rindex('#pragma optimize("", on)'))

    def test_class_instantiation_follows_the_class_template(self):
        definition = "template <class T> struct Box { T value; };"
        instantiation = "template struct Box<float>;"
        out = self.compose(definition + "\n" + instantiation + "\n", True)
        self.assertLess(out.index(definition), out.index(instantiation))
        self.assertEqual(out.count(instantiation), 1)

    def test_specialization_and_extern_declarations_still_precede_uses(self):
        declarations = ["template <> int identity<int>(int value);",
                        "extern template float identity<float>(float value);"]
        for declaration in declarations:
            out = self.compose('int f() { return 0; }\n' + declaration + '\n', True)
            self.assertLess(out.index(declaration), out.index('int f()'))


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

    def test_an_intrinsic_pragma_follows_the_declaration_it_names(self):
        # Rva0051730ECtor.cpp: hoisted into the seed's includes, the pragma came before the
        # donor's own declaration, cl ignored it, and _ReadWriteBarrier became a call
        tu = "Code/T.cpp"
        seed = '// cl: /MD\n#include "A.h"\nint f() { return 1; }\n'
        donor = ('extern "C" void _ReadWriteBarrier();\n#pragma intrinsic(_ReadWriteBarrier)\n'
                 '// cl: /MD\nstruct R { int a, b; R(); };\n'
                 'R::R() { a = -1; _ReadWriteBarrier(); b = -1; }\n')
        out = T.compose(tu, [], [tu, "Code/D.cpp"], {tu: seed, "Code/D.cpp": donor}, ["/MD"], "first")
        at = [out.index(name) for name in ('"A.h"', 'extern "C" void _ReadWriteBarrier();',
                                           "#pragma intrinsic(_ReadWriteBarrier)", "R::R()")]
        self.assertEqual(at, sorted(at))
        self.assertEqual(out.count("#pragma intrinsic(_ReadWriteBarrier)"), 1)

    def test_an_intrinsic_pragma_after_an_unrelated_declaration_stays_a_directive(self):
        chunks = T.composition_chunks("int g;\n#pragma intrinsic(memcpy)\nvoid h() { }\n")
        self.assertIn(("pp", "#pragma intrinsic(memcpy)"), chunks)


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

    def donors(self, ledger, placed, unplaced=None):
        """donors() over `ledger` [(name, rva, source)] with `placed` {rva: tu} approved (or
        {rva: (tu, confidence, evidence)}) and `unplaced` {rva: (confidence, evidence)} map
        rows with no TU."""
        T._CACHE.clear()
        T._CACHE["ledger"] = [{"name": n, "export_rva": "", "target_rva": f"0x{rva:08X}", "target_size": "8",
                               "source": s, "status": "matched",
                               "notes": "gen-funclet;parent=?h@@YAXXZ" if n.startswith("$L") else ""}
                              for n, rva, s in ledger]
        placed = {rva: v if isinstance(v, tuple) else (v, "approved", "") for rva, v in placed.items()}
        placed = {rva: v if len(v) == 4 else v + ("-",) for rva, v in placed.items()}     # (tu, conf, ev[, by])
        T._CACHE["map"] = [{"rva": f"0x{rva:08X}", "size": "8", "kind": "code", "tu": tu, "confidence": conf,
                            "by": by, "evidence": ev, "source": ""} for rva, (tu, conf, ev, by) in placed.items()]
        T._CACHE["map"] += [{"rva": f"0x{rva:08X}", "size": "8", "kind": "code", "tu": "", "confidence": conf,
                             "by": "-", "evidence": ev, "source": ""} for rva, (conf, ev) in (unplaced or {}).items()]
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

    def test_an_icf_alias_makes_no_file_mixed(self):
        # 0x2000's identity is W.cpp's row (first row wins, as in tu_map); A.cpp's and
        # the TU file's rows there are aliases that live with the bodies emitting them.
        ledger = [("??1W@@QAE@XZ", 0x2000, "Code/W.cpp"), ("?t@@YAXXZ", 0x1000, self.TU),
                  ("??1T@@QAE@XZ", 0x2000, self.TU), ("?a@@YAXXZ", 0x1010, "Code/A.cpp"),
                  ("??1A@@QAE@XZ", 0x2000, "Code/A.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1010: self.TU, 0x2000: "Code/W.cpp"})
        self.assertEqual(mixed, {})
        self.assertEqual(sorted(don), ["Code/A.cpp", self.TU])
        self.assertEqual(len(don["Code/A.cpp"]), 2)

    def test_the_identity_row_of_a_shared_address_is_still_placed(self):
        ledger = [("??1W@@QAE@XZ", 0x2000, "Code/A.cpp"), ("?t@@YAXXZ", 0x1000, self.TU),
                  ("?a@@YAXXZ", 0x1010, "Code/A.cpp"), ("??1B@@QAE@XZ", 0x2000, "Code/B.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1010: self.TU, 0x2000: "Code/W.cpp"})
        self.assertEqual(mixed, {"Code/A.cpp": 1})

    def test_independently_approved_deleting_dtor_of_an_unplaced_fold_alias(self):
        # FadeInTextRender: the map places the deleting dtor independently by C,
        # while its complete dtor folds into another address identity with no TU.
        for kind in ("G", "E"):
            with self.subTest(kind=kind):
                ledger = [("?apply@Identity@@QAEXXZ", 0x2000, "Code/W.cpp"),
                          ("?t@@YAXXZ", 0x1000, self.TU),
                          ("??1Folded@@UAE@XZ", 0x2000, "Code/A.cpp"),
                          (f"??_{kind}Folded@@UAEPAXI@Z", 0x1010, "Code/A.cpp")]
                don, mixed, refused = self.donors(
                    ledger, {0x1000: self.TU, 0x1010: (self.TU, "approved", "C=0x00001000..0x00001020")},
                    {0x2000: ("", "")})
                self.assertEqual((mixed, refused), ({}, {}))
                self.assertEqual(len(don["Code/A.cpp"]), 2)

    def test_fold_alias_parent_never_approves_a_proposed_or_foreign_child(self):
        ledger = [("?apply@Identity@@QAEXXZ", 0x2000, "Code/W.cpp"),
                  ("?t@@YAXXZ", 0x1000, self.TU), ("?a@@YAXXZ", 0x1008, "Code/A.cpp"),
                  ("??1Folded@@UAE@XZ", 0x2000, "Code/A.cpp"),
                  ("??_GFolded@@UAEPAXI@Z", 0x1010, "Code/A.cpp")]
        for child in ((self.TU, "proposed", "C=0x00001000..0x00001020"), "Code/Other.cpp"):
            with self.subTest(child=child):
                don, mixed, refused = self.donors(
                    ledger, {0x1000: self.TU, 0x1008: self.TU, 0x1010: child}, {0x2000: ("", "")})
                self.assertNotIn("Code/A.cpp", don)
                self.assertTrue(mixed or refused)

    def test_deleting_dtor_does_not_excuse_an_unapproved_primary_parent(self):
        ledger = [("?t@@YAXXZ", 0x1000, self.TU),
                  ("??1Primary@@UAE@XZ", 0x2000, "Code/A.cpp"),
                  ("??_GPrimary@@UAEPAXI@Z", 0x1010, "Code/A.cpp")]
        don, mixed, refused = self.donors(
            ledger, {0x1000: self.TU, 0x1010: self.TU}, {0x2000: ("", "inline")})
        self.assertEqual(mixed, {})
        self.assertNotIn("Code/A.cpp", don)
        self.assertIn("not approved", refused["Code/A.cpp"])

    def test_approved_deleting_dtor_retains_fold_parent_ownership_constraints(self):
        ledger = [("?apply@Identity@@QAEXXZ", 0x2000, "Code/W.cpp"),
                  ("?t@@YAXXZ", 0x1000, self.TU),
                  ("??1Folded@@UAE@XZ", 0x2000, "Code/A.cpp"),
                  ("??_GFolded@@UAEPAXI@Z", 0x1010, "Code/A.cpp")]
        for evidence in ("F", "Z", "S", "L", "W"):
            with self.subTest(evidence=evidence):
                don, mixed, refused = self.donors(
                    ledger, {0x1000: self.TU, 0x1010: self.TU},
                    {0x2000: ("", f"{evidence}=Code/Other.cpp")})
                self.assertNotIn("Code/A.cpp", don)
                self.assertTrue(mixed or refused)
        don, mixed, refused = self.donors(
            ledger, {0x1000: self.TU, 0x1010: self.TU, 0x2000: "Code/Other.cpp"})
        self.assertNotIn("Code/A.cpp", don)
        self.assertTrue(mixed or refused)


    def test_homeless_comdats_follow_their_donor_into_the_merge(self):
        # A displaced template COMDAT, a header inline (the map's `inline` token), a template
        # instantiation and a deleting destructor the map leaves without a TU on purpose
        # do not make the donor mixed; they move with it.
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("?Get@?$Box@H@@QBEHXZ", 0x1300, "Code/B.cpp"), ("?Inl@Bar@@QAEXXZ", 0x1310, "Code/B.cpp"),
                  ("??$max@H@std@@YAABHABH0@Z", 0x1320, "Code/B.cpp"), ("??_GBaz@@UAEPAXI@Z", 0x1330, "Code/B.cpp")]
        unplaced = {0x1300: ("displaced", "N=Code/Box.cpp"), 0x1310: ("", "inline"),
                    0x1320: ("", ""), 0x1330: ("", "")}
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU}, unplaced)
        self.assertEqual(mixed, {})
        self.assertEqual(sorted(don), ["Code/B.cpp", self.TU])
        self.assertEqual(len(don["Code/B.cpp"]), 5)

    def test_a_homeless_rows_funclet_follows_it(self):
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("?h@@YAXXZ", 0x1300, "Code/B.cpp"), ("$L1", 0x1400, "Code/B.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU},
                                    {0x1300: ("", "inline"), 0x1400: ("", "")})
        self.assertEqual(mixed, {})
        self.assertEqual(len(don["Code/B.cpp"]), 3)

    def test_homeless_rows_never_excuse_a_row_of_another_tu_or_one_with_no_evidence(self):
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("??_GBaz@@UAEPAXI@Z", 0x1330, "Code/B.cpp"), ("?o@@YAXXZ", 0x1200, "Code/B.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU, 0x1200: "Code/Other.cpp"},
                                    {0x1330: ("", "")})
        self.assertEqual(mixed, {"Code/B.cpp": 1})                  # the other TU's row still blocks
        ledger[-1] = ("?plain@@YAXXZ", 0x1340, "Code/B.cpp")         # unplaced for want of evidence
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU}, {0x1330: ("", ""), 0x1340: ("", "")})
        self.assertEqual(mixed, {"Code/B.cpp": 1})
        self.assertNotIn("Code/B.cpp", don)

    def test_a_donor_with_a_row_only_proposed_for_the_tu_is_refused(self):
        # Only approved rows move: a proposed row of this TU (9d84b3191f moved 0x00329F83)
        # refuses its file, it is not "mixed" (no other TU claims it).
        don, mixed, refused = self.donors(
            [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"), ("?p@@YAXXZ", 0x1030, "Code/B.cpp")],
            {0x1000: self.TU, 0x1020: self.TU, 0x1030: (self.TU, "proposed", "C=0x00001020..0x00001040")})
        self.assertEqual(mixed, {})
        self.assertNotIn("Code/B.cpp", don)
        self.assertIn("not approved", refused["Code/B.cpp"])

    def test_the_tu_file_may_keep_its_own_proposed_rows(self):
        # the seed moves none of its rows, so a proposed row of the TU there is no refusal
        don, mixed, refused = self.donors(
            [("?t@@YAXXZ", 0x1000, self.TU), ("?q@@YAXXZ", 0x1100, self.TU), ("?a@@YAXXZ", 0x1010, "Code/A.cpp")],
            {0x1000: self.TU, 0x1010: self.TU, 0x1100: (self.TU, "proposed", "")})
        self.assertEqual((mixed, refused), ({}, {}))
        self.assertEqual(sorted(don), ["Code/A.cpp", self.TU])

    def test_a_p_group_funclet_counts_only_with_an_approved_parent(self):
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("?h@@YAXXZ", 0x1030, "Code/B.cpp"), ("$L1", 0x1400, "Code/B.cpp")]
        funclet = (self.TU, "approved", "P=0x00001030@FuncInfo0x00002000 p-group")
        don, mixed, refused = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU,
                                                   0x1030: (self.TU, "proposed", "N=Code/T.cpp"), 0x1400: funclet})
        self.assertNotIn("Code/B.cpp", don)
        self.assertIn("2 row(s) not approved", refused["Code/B.cpp"])    # the parent and its funclet
        don, _, refused = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU, 0x1030: self.TU, 0x1400: funclet})
        self.assertIn("Code/B.cpp", don)

    def test_approved_homes_drops_a_p_group_row_of_an_unapproved_parent(self):
        row = lambda rva, conf="approved", ev="", tu="Code/T.cpp": {"rva": f"0x{rva:08X}", "kind": "code", "tu": tu,
                                                                    "confidence": conf, "evidence": ev}
        rows = [row(0x10, "proposed"), row(0x20, ev="P=0x00000010@FuncInfo0x00000099 p-group"),
                row(0x30), row(0x40, ev="P=0x00000030@FuncInfo0x00000099 p-group"),
                row(0x50, ev="P=0x00000030@FuncInfo0x00000099 p-group", tu="Code/U.cpp"),
                row(0x60, ev="P=0x00000030@FuncInfo0x00000099")]
        self.assertEqual(T.approved_homes(rows), {0x30: "code/t.cpp", 0x40: "code/t.cpp", 0x60: "code/t.cpp"})

    def test_a_displaced_out_of_line_function_never_follows_another_file(self):
        # R1 S1: build() displaces B::f (Z=Code/B.cpp) when B's larger cluster is elsewhere;
        # displacement is no COMDAT evidence and its own Z names B, so A's merge must not take it.
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?a@@YAXXZ", 0x1020, "Code/A.cpp"),
                  ("?f@B@@QAEXXZ", 0x1100, "Code/A.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU},
                                    {0x1100: ("displaced", "Z=Code/B.cpp N=Code/B.cpp")})
        self.assertEqual(mixed, {"Code/A.cpp": 1})
        self.assertNotIn("Code/A.cpp", don)

    def test_a_companion_assigned_elsewhere_blocks_even_under_a_homeless_parent(self):
        # R1 S2: the companion's own assignment comes before its parent's (homeless) None.
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("?h@@YAXXZ", 0x1300, "Code/B.cpp"), ("$L1", 0x1400, "Code/B.cpp")]
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU, 0x1400: "Code/Other.cpp"},
                                    {0x1300: ("", "inline")})
        self.assertEqual(mixed, {"Code/B.cpp": 1})
        self.assertNotIn("Code/B.cpp", don)

    def test_an_unplaced_companion_with_its_own_tu_evidence_never_rides(self):
        # R2 S3: the deleting dtor of a homeless inline dtor carries W=Code/Other.cpp of its own;
        # its parent's homeless status must not exempt it.
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"),
                  ("??1Foo@@UAE@XZ", 0x1300, "Code/B.cpp"), ("??_GFoo@@UAEPAXI@Z", 0x1310, "Code/B.cpp")]
        don, mixed, refused = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU},
                                          {0x1300: ("", "inline"), 0x1310: ("", "W=Code/Other.cpp")})
        self.assertEqual(mixed, {"Code/B.cpp": 1})
        self.assertNotIn("Code/B.cpp", don)
        # the same companion with no evidence of its own still rides
        don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU},
                                    {0x1300: ("", "inline"), 0x1310: ("", "")})
        self.assertEqual(mixed, {})
        self.assertIn("Code/B.cpp", don)

    def test_tu_map_homeless(self):
        import tu_map
        row = lambda tu="", conf="", ev="", kind="code": {"tu": tu, "confidence": conf, "evidence": ev, "kind": kind}
        self.assertFalse(tu_map.homeless(row(conf="displaced", ev="N=Code/F.cpp"), "?f@Foo@@QAEXXZ"))
        self.assertTrue(tu_map.homeless(row(conf="displaced", ev="N=Code/F.cpp"), "??_GFoo@@UAEPAXI@Z"))
        self.assertFalse(tu_map.homeless(row(conf="displaced", ev="Z=Code/F.cpp"), "??_GFoo@@UAEPAXI@Z"))
        self.assertFalse(tu_map.homeless(row(ev="F=Code/F.cpp inline")))
        self.assertTrue(tu_map.homeless(row(ev="inline")))
        self.assertTrue(tu_map.homeless(row(), "?begin@?$vector@H@_STL@@QAEPAHXZ"))
        self.assertTrue(tu_map.homeless(row(), "??_EFoo@@UAEPAXI@Z"))
        self.assertFalse(tu_map.homeless(row(), "?plain@@YAXXZ"))
        self.assertFalse(tu_map.homeless(row(), "Rva00401000Get"))
        self.assertFalse(tu_map.homeless(row(tu="Code/A.cpp", conf="proposed"), "??_GFoo@@UAEPAXI@Z"))
        self.assertFalse(tu_map.homeless(row(ev="inlined"), "?f@@YAXXZ"))     # a whole token only
        self.assertFalse(tu_map.homeless(row(kind="data:.rdata", ev="inline")))

    def test_the_seed_is_found_through_a_case_variant_spelling(self):
        # reverse/tu_map.csv approves Code/T.cpp; the checkout and the ledger spell the
        # same file Code/t.cpp (WW3D2/FXShaderSetup.cpp against fxshadersetup.cpp), and
        # its unplaced row must still mark it the seed, not a mixed donor.
        don, mixed, _ = self.donors([("?t@@YAXXZ", 0x1000, "Code/t.cpp"),
                                     ("?u@@YAXXZ", 0x1100, "Code/t.cpp"),
                                     ("?a@@YAXXZ", 0x1010, "Code/A.cpp")],
                                    {0x1000: self.TU, 0x1010: self.TU})
        self.assertEqual(mixed, {})
        self.assertEqual(sorted(don), ["Code/A.cpp", "Code/t.cpp"])
        self.assertEqual(len(don["Code/t.cpp"]), 2)


class EmissionHeldTests(unittest.TestCase):
    """LINK-629: an implicit template instantiation the map places by contiguity alone
    (FXList.cpp's hashtable<NameKeyType, FXList> clear/_M_delete_node, in XferSave.cpp's
    retail contribution) is kept by the TU file whose code emits it."""
    TU = DonorTests.TU
    donors = DonorTests.donors
    CLEAR = "?clear@?$hashtable@U?$pair@$$CBHVFX@@@_STL@@HU?$hash@H@2@@_STL@@QAEXXZ"
    C = ("Code/XferSave.cpp", "approved", "C=0x00001100..0x00001300", "C")

    def test_template_instance_names(self):
        for name in (self.CLEAR, "?_M_delete_node@?$hashtable@H@_STL@@AAEXPAU?$_Hashtable_node@H@2@@Z",
                     "??0?$vector@H@_STL@@QAE@XZ", "??1?$hash_map@H@_STL@@QAE@XZ", "??_G?$Box@H@@QAEPAXI@Z",
                     "??R?$hash@H@_STL@@QBEIH@Z", "??$max@H@std@@YAABHABH0@Z"):
            self.assertTrue(T.TEMPLATE_INSTANCE.match(name), name)
        for name in ("?f@@YAXV?$vector@H@_STL@@@Z", "?clear@FXList@@QAEXXZ", "??0FXList@@QAE@ABV0@@Z",
                     "?rva0060CD16@Rva0060CD16@@QBEIABV?$basic_string@D@_STL@@@Z", "_memset"):
            self.assertFalse(T.TEMPLATE_INSTANCE.match(name), name)

    def held(self, name=CLEAR, tu="Code/XferSave.cpp", by="C", ev="C=0x00001100..0x00001300", spelled=False):
        T._CACHE.clear()
        T._CACHE["map"] = [{"rva": "0x00001200", "size": "8", "kind": "code", "tu": tu, "confidence": "approved",
                            "by": by, "evidence": ev, "source": ""}]
        row = {"name": name, "target_rva": "0x00001200", "source": self.TU}
        try:
            with patch.object(T, "spells_definition", return_value=spelled):
                return T.emission_held(row)
        finally:
            T._CACHE.clear()

    def test_held_needs_an_instance_placed_by_contiguity_alone_and_spelled_nowhere(self):
        self.assertTrue(self.held())
        self.assertFalse(self.held(name="?clear@FXList@@QAEXXZ"))                   # a spelled member's row
        self.assertFalse(self.held(by="N"))                                          # a naming hint places it
        self.assertFalse(self.held(by="-"))
        for key in "FZSLW":                                                          # evidence naming its TU
            self.assertFalse(self.held(ev=f"C=0x00001100..0x00001300 {key}=Code/XferSave.cpp"), key)
        self.assertTrue(self.held(ev="C=0x00001100..0x00001300 N=Code/hashtable.cpp"))   # N only hints
        self.assertFalse(self.held(tu=""))                                           # homeless(): its own rule
        self.assertFalse(self.held(spelled=True))                                    # an explicit specialization

    def test_spells_definition_reads_what_identify_does_not(self):
        row = {"name": self.CLEAR, "target_rva": "0x00001200"}
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            texts = {"use.cpp": "#include <hash_map>\nvoid f(H &m) { m.clear(); }\n",
                     "decl.cpp": "class hashtable;\nvoid f(hashtable *);\n",
                     "spec.cpp": "template <> void hashtable<pair<const int, FX>, int>::clear() { }\n",
                     "body.cpp": "template <class V, class K> struct hashtable { void clear() { } };\n",
                     "comment.cpp": "// template <class V> struct hashtable { };\nvoid f() { }\n"}
            for name, text in texts.items():
                (root / name).write_text(text)
            with patch.object(T, "ROOT", root), patch.dict(T._CACHE, {}, clear=True):
                got = {name: T.spells_definition(name, row) for name in [*texts, "missing.cpp"]}
        self.assertEqual(got, {"use.cpp": False, "decl.cpp": False, "spec.cpp": True, "body.cpp": True,
                               "comment.cpp": False, "missing.cpp": True})

    def test_instance_owner_reads_every_admitted_shape(self):
        self.assertEqual(T.instance_owner(self.CLEAR), ("hashtable", "clear"))
        self.assertEqual(T.instance_owner("??0?$Box@H@@QAE@XZ"), ("Box", "Box"))
        for op in ("1", "_G", "_E"):
            self.assertEqual(T.instance_owner(f"??{op}?$Box@H@@QAE@XZ"), ("Box", "~Box"), op)
        for op in ("R", "4", "A", "B", "8"):          # operator(), =, [], a conversion, ==
            self.assertEqual(T.instance_owner(f"??{op}?$Box@H@@QBEHXZ"), ("Box", "operator"), op)
        self.assertEqual(T.instance_owner("??$max@H@std@@YAABHABH0@Z"), (None, "max"))
        self.assertIsNone(T.instance_owner("?f@@YAXXZ"))

    def test_explicit_specializations_bodies_and_instantiations_spell_the_row(self):
        # review of 9356f06742: explicit operators and explicit instantiations are not implicit
        op, clear, ctor, fn = "??R?$Box@H@@QBEHXZ", "?clear@?$Box@H@@QAEXXZ", "??0?$Box@H@@QAE@XZ", "??$f@H@@YAXXZ"
        cases = [
            ("template<> int Box<int>::operator()() const { return 7; }\n", op, True),
            ("template <class T> class Box { public: int operator()() const { return 0; } };\n", op, True),
            ("template <class T> struct Box { Box() { } };\n", ctor, True),
            ("template<> Box<int>::Box() { }\n", ctor, True),
            ("#include \"Box.h\"\ntemplate class Box<int>;\nvoid t() {}\n", clear, True),
            ("template struct Box<int>;\n", clear, True),
            ("template struct ns::Box<int>;\n", clear, True),
            ("template void Box<int>::clear();\n", clear, True),
            ("template void f<int>();\n", fn, True),
            ("template<> void f<int>() {}\n", fn, True),
            ("#include \"Box.h\"\nint g(const Box<int> &b) { return b(); }\n", op, False),     # a use emits it
            ("#include \"Box.h\"\nvoid g(Box<int> &b) { b.clear(); }\n", clear, False),
            ("void g() { f<int>(); }\n", fn, False),
            ("void g() { }\n", "?f@@YAXXZ", True),                  # no owner derivable: fail closed
        ]
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for i, (text, name, want) in enumerate(cases):
                (root / f"c{i}.cpp").write_text(text)
                with patch.object(T, "ROOT", root), patch.dict(T._CACHE, {}, clear=True):
                    got = T.spells_definition(f"c{i}.cpp", {"name": name, "target_rva": "0x00001200"})
                self.assertEqual(got, want, (text, name))

    def test_an_explicit_operator_body_makes_the_tu_file_mixed(self):
        # the reviewer's donor probe: Code/T.cpp spells Box<int>::operator() itself
        name = "??R?$Box@H@@QBEHXZ"
        for text in ("template<> int Box<int>::operator()() const {return 7;}\nvoid t() {}\n",
                     '#include "Box.h"\ntemplate class Box<int>;\nvoid t() {}\n'):
            with self.subTest(text=text), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                (root / "Code").mkdir()
                (root / "Code/T.cpp").write_text(text)
                ledger = [("?t@@YAXXZ", 0x1000, self.TU), (name, 0x1200, self.TU), ("?a@@YAXXZ", 0x1010, "Code/A.cpp")]
                with patch.object(T, "ROOT", root):
                    _, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1010: self.TU, 0x1200: self.C})
                self.assertEqual(mixed, {self.TU: 1})

    def test_the_tu_file_keeps_an_instantiation_its_code_emits(self):
        # FXList.cpp: its own rows, plus the instantiation retail kept from XferSave.obj
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), (self.CLEAR, 0x1200, self.TU), ("?a@@YAXXZ", 0x1010, "Code/A.cpp")]
        placed = {0x1000: self.TU, 0x1010: self.TU, 0x1200: self.C}
        with patch.object(T, "spells_definition", return_value=False):
            don, mixed, _ = self.donors(ledger, placed)
        self.assertEqual(mixed, {})
        self.assertEqual(sorted(don), ["Code/A.cpp", self.TU])
        self.assertEqual(len(don[self.TU]), 2)
        with patch.object(T, "spells_definition", return_value=True):                # spelled: it has a home
            _, mixed, _ = self.donors(ledger, placed)
        self.assertEqual(mixed, {self.TU: 1})
        placed[0x1200] = ("Code/XferSave.cpp", "approved", "Z=Code/XferSave.cpp", "Z")   # placed by Z: foreign
        with patch.object(T, "spells_definition", return_value=False):
            _, mixed, _ = self.donors(ledger, placed)
        self.assertEqual(mixed, {self.TU: 1})

    def test_a_donor_never_carries_one_away_from_its_tu(self):
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"), (self.CLEAR, 0x1200, "Code/B.cpp")]
        with patch.object(T, "spells_definition", return_value=False):
            don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU, 0x1200: self.C})
        self.assertEqual(mixed, {"Code/B.cpp": 1})
        self.assertNotIn("Code/B.cpp", don)

    def test_a_donor_still_brings_one_into_its_own_tu(self):
        # the map's contiguity names this TU: the donor moves in with it, as before
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), ("?b@@YAXXZ", 0x1020, "Code/B.cpp"), (self.CLEAR, 0x1200, "Code/B.cpp")]
        here = (self.TU, "approved", "C=0x00001000..0x00001300", "C")
        with patch.object(T, "spells_definition", return_value=False):
            don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1020: self.TU, 0x1200: here})
        self.assertEqual(mixed, {})
        self.assertEqual(len(don["Code/B.cpp"]), 2)

    def test_a_split_destination_holding_one_is_not_mixed(self):
        own = [{"name": "?t@@YAXXZ", "target_rva": "0x00001000", "source": self.TU},
               {"name": self.CLEAR, "target_rva": "0x00001200", "source": self.TU}]
        assigned = {0x1000: self.TU.lower(), 0x1200: "code/xfersave.cpp"}
        with patch.object(T, "fold_alias", return_value=False):
            with patch.object(T, "emission_held", side_effect=lambda r: r["name"] == self.CLEAR):
                self.assertEqual(T.placed_elsewhere(self.TU, own, assigned), {})
            with patch.object(T, "emission_held", return_value=False):
                self.assertEqual(T.placed_elsewhere(self.TU, own, assigned), {"xfersave.cpp": 1})

    def test_a_split_for_the_contiguity_tu_names_the_rows_instead_of_carving(self):
        rows = [{"name": "?t@@YAXXZ", "target_rva": "0x00001000"}, {"name": self.CLEAR, "target_rva": "0x00001200"}]
        groups = {self.TU: [rows[0]], "Code/XferSave.cpp": [rows[1]]}
        with patch.object(T, "file_rows", return_value=rows), patch.object(T, "breakdown", return_value=groups):
            with patch.object(T, "emission_held", side_effect=lambda r: r["name"] == self.CLEAR):
                why, _, tu_rows = T.split_rows(self.TU, "Code/XferSave.cpp")
            self.assertIn("implicit template instantiations placed by contiguity alone", why)
            self.assertEqual(tu_rows, [])
            with patch.object(T, "emission_held", return_value=False):
                why, _, tu_rows = T.split_rows(self.TU, "Code/XferSave.cpp")
            self.assertIsNone(why)
            self.assertEqual(tu_rows, [rows[1]])


class EmitMoveTests(unittest.TestCase):
    """--emit-move: an implicit COMDAT row moves from a mixed file to its approved TU only
    when the TU's own code emits it byte-exact (P16, the LivingWorldCampaign Act chain)."""
    SOURCE, TU, OTHER = "Code/Mixed.cpp", "Code/Campaign.cpp", "Code/Other.cpp"
    CTOR = "??$_Construct@VRec@@V1@@_STL@@YAXPAVRec@@ABV1@@Z"        # a function template instantiation
    COPY = "??0Rec@@QAE@ABV0@@Z"                                       # a compiler-generated copy ctor
    STAY = "?stay@@YAXXZ"

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "Code").mkdir()
        self.write(self.SOURCE, "#include <memory>\nstruct Rec { int a; };\nvoid stay() {}\n")
        self.write(self.TU, "struct Rec { int a; };\nvoid campaign(Rec *p, const Rec &r) { new (p) Rec(r); }\n")

    def write(self, rel, text):
        """LF bytes on every host (a CRLF fixture would test another file)."""
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))

    def row(self, name, rva, source=None, notes=""):
        return {"name": name, "export_rva": "", "target_rva": rva, "target_size": "8",
                "source": source or self.SOURCE, "status": "matched", "notes": notes}

    def move(self, *, rvas=None, approved=None, defined=None, comdat=None, exact=None, residual_lost=(),
             rows=None, dry_run=True, file_defined=(), file_comdat=(), final_lost=(), preprocessed=None,
             built=True, built_defined=None, built_comdat=None, build_effect=None, claim=False):
        """emit_move over a file holding CTOR (0x2000), COPY (0x2100) and STAY (0x3000). `approved`
        {rva: tu}; the TU's scratch object `defined`/`comdat` names and the rvas it matches `exact`
        (`final_lost` lost when judged with only the rows that finally move); the file's object
        `file_defined`/`file_comdat`; `preprocessed` {path: text or None} (default: the file's text);
        for the apply, ./build.sh passing (`built`) and the real TU object's `built_defined`/`built_comdat`."""
        rows = rows if rows is not None else [self.row(self.CTOR, "0x00002000"), self.row(self.COPY, "0x00002100"),
                                              self.row(self.STAY, "0x00003000")]
        approved = approved if approved is not None else {"0x00002000": self.TU, "0x00002100": self.TU,
                                                          "0x00003000": self.OTHER}
        defined = {self.CTOR, self.COPY} if defined is None else defined
        comdat = defined if comdat is None else comdat
        exact = {"0x00002000", "0x00002100"} if exact is None else exact
        groups = {}
        for r in rows:
            groups.setdefault(approved.get(r["target_rva"], ""), []).append(r)
        (self.root / "build").mkdir(exist_ok=True)
        objs = {self.TU: self.root / "build" / "t.obj", self.SOURCE: self.root / "build" / "x.obj"}
        real = {self.TU: self.root / "build" / "real_t.obj", self.SOURCE: self.root / "build" / "real_x.obj"}
        import build
        for key, path in list(objs.items()) + [(k + "#real", p) for k, p in real.items()]:
            path.write_bytes(key.encode())
        for path in real.values():                     # build/match's receipts beside the real objects
            build._deps_sidecar(path).write_text("{}")
        names = {self.TU.encode(): set(defined), self.SOURCE.encode(): set(file_defined),
                 (self.TU + "#real").encode(): set(defined if built_defined is None else built_defined),
                 (self.SOURCE + "#real").encode(): set(file_defined)}
        comdats = {objs[self.TU]: set(comdat), objs[self.SOURCE]: set(file_comdat),
                   real[self.TU]: set(comdat if built_comdat is None else built_comdat), real[self.SOURCE]: set(file_comdat)}
        movers = {r["target_rva"] for r in rows if approved.get(r["target_rva"]) == self.TU}

        class Verifier:
            errors = []

            def __init__(self, tu):
                self.tu = tu
                self.obj = objs[tu]

            def matched(self, text, judged):
                rvas_ = {r["target_rva"] for r in judged}
                if self.tu == EmitMoveTests.TU:
                    lost = set(final_lost) if rvas_ & movers and not movers <= rvas_ else set()
                    return (rvas_ & exact) - lost
                return rvas_ - (set(residual_lost) if len(judged) < len(rows) else set())

        def unit_text(path):        # as the real one: the text flattened (directives, literals masked)
            if preprocessed is not None and path in preprocessed:
                text = preprocessed[path]
                return (T.flatten_preprocessed(text), None) if text is not None else (None, "cl -E failed")
            return T.flatten_preprocessed((self.root / path).read_text(encoding="utf-8")), None

        import build
        import name_dependents
        own = lambda p: rows if p == self.SOURCE else []
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, {}, clear=True), \
                patch.object(T, "file_rows", side_effect=own), patch.object(T, "breakdown", return_value=groups), \
                patch.object(T, "fold_alias", return_value=False), patch.object(T, "Verifier", Verifier), \
                patch.object(T, "unit_text", side_effect=unit_text), \
                patch.object(T, "comdat_symbols", side_effect=lambda obj: comdats.get(Path(obj), set())), \
                patch.object(name_dependents, "coff_symbol_names", side_effect=lambda data, **_: names[data]), \
                patch.object(T, "exact_build", side_effect=build_effect if build_effect is not None
                             else (lambda sources: (built, "Functions: OK 2/2" if built else "boom"))) as exact_build, \
                patch.object(T, "claim_scope", side_effect=lambda *a, **k: self.claimed()), \
                patch.object(T.claims, "release") as release, \
                patch.object(build, "obj_path", side_effect=self.obj_path):
            self.released, self.exact = release, exact_build
            return T.emit_move(self.SOURCE, self.TU, rvas, dry_run=dry_run, claim=claim)

    TOKEN = "claim-sha-of-this-move"

    def claimed(self):
        """claim_scope's answer when every key was claimed: an empty Held with fencing tokens."""
        held = T.Held()
        held.tokens = {T.claims.key_of(f"file:{self.TU}"): self.TOKEN}
        return held

    def obj_path(self, source):
        """build.obj_path in the fixture: the two files' real build/match objects."""
        rel = Path(source).relative_to(self.root).as_posix()
        return self.root / "build" / {self.TU: "real_t.obj", self.SOURCE: "real_x.obj"}[rel]

    def test_an_emitted_instantiation_and_copy_ctor_move(self):
        report = self.move()
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])
        self.assertEqual(report["refused_rows"], {})

    def test_a_row_approved_for_another_tu_refuses(self):
        report = self.move(rvas=["0x00003000"])
        self.assertIn("not approved for Code/Campaign.cpp", report["blocked"])
        report = self.move(rvas=["0x00002000"], approved={"0x00002000": self.OTHER, "0x00002100": self.TU,
                                                          "0x00003000": self.OTHER})
        self.assertIn("0x00002000 not approved", report["blocked"])

    def test_a_row_the_tu_spells_refuses(self):
        # the TU must emit it from its own code: an explicit instantiation or a declared member there is
        # a stand-in or a real body, not an implicit COMDAT
        self.write(self.TU, "#include <memory>\nstruct Rec { int a; };\n"
                            "template void _STL::_Construct<Rec, Rec>(Rec *, const Rec &);\n")
        report = self.move(rvas=["0x00002000"])
        self.assertEqual(report["blocked"], "a requested row cannot move by emission")
        self.assertIn("explicit specialization or instantiation naming", report["refused_rows"]["0x00002000"])
        self.write(self.TU, "struct Rec { Rec(const Rec &o); int a; };\nvoid campaign() {}\n")
        report = self.move(rvas=["0x00002100"])
        self.assertIn("declares a constructor", report["refused_rows"]["0x00002100"])
        report = self.move(rows=[self.row("?f@Rec@@QAEXXZ", "0x00002000"), self.row(self.STAY, "0x00003000")])
        self.assertIn("not an implicit COMDAT", report["refused_rows"]["0x00002000"])

    def test_the_coarse_rules_refuse_whatever_the_spelling(self):
        # review of 692da8fc04: refuse on any explicit specialization or instantiation naming the
        # member or its class, and on any one-parameter constructor, rather than read spellings
        box_clear, box_call = "?clear@?$Box@H@@QAEXXZ", "??R?$Box@H@@QBEHXZ"
        cases = [
            # (a) explicit specializations and instantiations, any arguments, deduced ones included
            ("template<> inline void _Construct(Rec *p, Rec const &v) { }\n", self.CTOR, True),
            ("template <> void _Construct<Other, Other>(Other *, const Other &);\n", self.CTOR, True),  # over-refuses
            ("typedef Rec R2;\ntemplate <> inline void _Construct<R2, R2>(R2 *, const R2 &) { }\n", self.CTOR, True),
            ("template void _STL::_Construct<Rec, Rec>(Rec *, const Rec &);\n", self.CTOR, True),
            ("template<> inline void Box<int>::clear() {}\n", box_clear, True),           # builtin arguments
            ("template class Box<int>;\n", box_clear, True),
            ("template <> class Box<int> { };\n", box_call, True),
            ("template<> int Box<int>::operator()() const { return 7; }\n", box_call, True),
            ("template <class _T1, class _T2> void _Construct(_T1 *, const _T2 &);\n"
             "void g(Rec *p, const Rec &v) { _STL::_Construct(p, v); }\n", self.CTOR, False),   # primary template, a use
            ("template <class T> struct Box { void clear() { } };\nvoid g(Box<int> &b) { b.clear(); }\n", box_clear, False),
            # (b) any one-parameter constructor, whatever its spelling
            ("struct Rec { Rec(Rec const&o); int a; };\n", self.COPY, True),
            ("struct Rec { Rec(::Rec const&o); int a; };\n", self.COPY, True),
            ("struct Rec; typedef Rec const &CopyArg;\nstruct Rec { Rec(CopyArg o); int a; };\n", self.COPY, True),
            ("struct Rec { Rec(int n); int a; };\n", self.COPY, True),                    # over-refuses
            ("struct Rec { Rec(int n, int m); int a; };\n", self.COPY, False),
            ("struct Rec { Rec(); int a; };\n", self.COPY, False),
            ("struct Rec { int a; };\n", self.COPY, False),
            ("struct Other { int a; };\n", self.COPY, True),                              # no body of Rec: refuse
            ("struct Rec { Rec(); int a; };\n", "??0Rec@@QAE@XZ", True),                   # any ctor, for a default one
            ("struct Rec { ~Rec(); int a; };\n", "??1Rec@@QAE@XZ", True),
            ("struct Rec { Rec &operator=(Rec const volatile &o); };\n", "??4Rec@@QAEAAU0@ABU0@@Z", True),
            ("struct Rec { virtual ~Rec(); };\n", "??_GRec@@UAEPAXI@Z", False),             # always the compiler's
            # review of e81c016950: a directive between the pieces, a `;` in a #line file name
            ('struct Rec { Rec\n#line 10 "copy.h"\n(Rec const &r); int a; };\n', self.COPY, True),
            ('template<>\n#line 10 "semi;header.h"\ninline void _Construct(Rec *p, const Rec &v) { }\n', self.CTOR, True),
            ('template <>\n# 12 "a;b.h"\nclass Box<int> { };\n', box_call, True),
            ('struct Rec {\n#pragma pack(push, 4)\nRec(int n);\n#pragma pack(pop)\n};\n', self.COPY, True),
        ]
        for i, (text, name, refused) in enumerate(cases):
            with self.subTest(text=text, name=name):
                rel = f"Code/u{i}.cpp"
                with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, {}, clear=True), \
                        patch.object(T, "unit_text", return_value=(T.flatten_preprocessed(text), None)):
                    why = T.implicit_comdat({"name": name, "target_rva": "0x00001200"}, rel)
                self.assertEqual(bool(why), refused, why)

    def test_flattening_drops_every_directive_and_joins_lines(self):
        text = '#line 1 "a.h"\nstruct Rec\n# 3 "semi;colon.h"\n{\n  #pragma once\n  int a;\n};\n'
        self.assertEqual(T.flatten_preprocessed(text), "struct Rec { int a; };")

    HAND_WRITTEN = "Rec(Rec const &r):a(r.a){} int a; };\n"

    def test_a_literal_or_comment_never_closes_the_class_body(self):
        # review of 90fdd5d03d: `"}"` in a member function closed Rec's body before its hand-written
        # copy ctor; every literal kind, and comments, are masked before braces are matched, and a
        # body holding a masked brace, paren, quote or `;`, or a literal naming the class, refuses
        literals = ['"}"', "'}'", 'L"}"', 'u8"}"', 'R"x(})x"', 'LR"(})"', '"a\\"}"', '"("', '";"',
                    "/* } */", "// }\n"]
        for literal in literals:
            with self.subTest(literal=literal):
                text = "struct Rec { void f() { const char *s = " + literal + "; } " + self.HAND_WRITTEN
                with patch.object(T, "unit_text", return_value=(T.flatten_preprocessed(text), None)):
                    why = T.implicit_comdat({"name": self.COPY, "target_rva": "0x00002100"}, "Code/u.cpp")
                self.assertTrue(why, literal)
        for text, refused in (('struct Rec { void f() { puts("Rec"); } int a; };\n', True),       # names the class
                              ('struct Rec { void f() { puts("ok"); } int a; };\n', False),        # a harmless literal
                              ('struct Rec { void f() { puts("ok); } int a; };\n', True)):         # unbalanced quote
            with self.subTest(text=text), \
                    patch.object(T, "unit_text", return_value=(T.flatten_preprocessed(text), None)):
                why = T.implicit_comdat({"name": self.COPY, "target_rva": "0x00002100"}, "Code/u.cpp")
                self.assertEqual(bool(why), refused, why)

    def test_the_string_brace_repro_is_refused_through_the_apply(self):
        self.ledger()
        self.write(self.TU, 'struct Rec { void f() { const char *s = "}"; } ' + self.HAND_WRITTEN)
        report = self.move(rvas=["0x00002100"], dry_run=False)
        self.assertIn("blocked", report)
        self.assertIn("literal or comment", report["refused_rows"]["0x00002100"])
        self.assertNotIn(self.TU.encode(), subprocess.run(["git", "show", ":reverse/functions.csv"], cwd=self.root,
                                                          capture_output=True).stdout)

    def test_mask_literals_keeps_code_and_blanks_what_could_read_as_code(self):
        self.assertEqual(T.mask_literals('f("a{b", \'(\', R"d(x})d"); /* } */ g();'),
                         'f("a\x02b", \'\x02\', "x\x02");  \x02  g();')
        self.assertTrue(T.mask_literals('f("open);').startswith(T.UNREADABLE))

    def test_the_rules_read_the_preprocessed_unit(self):
        # a header (or a macro) declares the copy ctor; the raw text never shows it
        report = self.move(rvas=["0x00002100"], preprocessed={self.TU: "struct Rec { Rec(const Rec &); int a; };\n"})
        self.assertIn("declares a constructor", report["refused_rows"]["0x00002100"])
        report = self.move(rvas=["0x00002000"], preprocessed={self.TU: "template<> inline void Box<int>::f();\n"
                                                                       "template<> inline void _Construct(Rec *, const Rec &) { }\n"})
        self.assertIn("explicit specialization or instantiation", report["refused_rows"]["0x00002000"])
        report = self.move(rvas=["0x00002000"], preprocessed={self.TU: None})
        self.assertIn("cannot be preprocessed", report["refused_rows"]["0x00002000"])

    def test_a_row_bound_to_another_object_symbol_refuses(self):
        # review of 3db7ced4b4: the byte check would follow object-symbol=, the COMDAT checks the name
        rows = [self.row(self.CTOR, "0x00002000", notes="object-symbol=_standin"), self.row(self.STAY, "0x00003000")]
        report = self.move(rows=rows, rvas=["0x00002000"])
        self.assertIn("object-symbol=", report["refused_rows"]["0x00002000"])

    def test_the_files_explicit_instantiation_stand_in_moves(self):
        # stlport_construct_game_structs.cpp's shape: the file hosts the row through an explicit
        # instantiation and a private view declaring the copy ctor; both compile to COMDATs
        self.write(self.SOURCE, "struct Rec { Rec(const Rec &o) : a(o.a) {} int a; };\n"
                                "template void _STL::_Construct<Rec, Rec>(Rec *, const Rec &);\n"
                                "void stay() {}\n")
        report = self.move(file_defined={self.CTOR, self.COPY}, file_comdat={self.CTOR, self.COPY})
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])

    def test_a_strong_definition_in_the_file_refuses(self):
        report = self.move(rvas=["0x00002100"], file_defined={self.COPY}, file_comdat=set())
        self.assertIn("the file defines it outside a COMDAT", report["refused_rows"]["0x00002100"])

    def test_a_destination_not_emitting_it_refuses(self):
        report = self.move(rvas=["0x00002000"], defined={self.COPY})
        self.assertIn("does not emit it", report["refused_rows"]["0x00002000"])
        report = self.move(defined={self.COPY})          # without --rva the rest still moves
        self.assertEqual(report["moved"], ["0x00002100"])

    def test_the_final_row_set_is_judged_again(self):
        # review of 3db7ced4b4: with 0x2000 refused, the TU's flags follow 0x2100 alone and lose it
        report = self.move(defined={self.COPY}, final_lost={"0x00002100"})
        self.assertIn("re-judged with exactly the rows that move", report["blocked"])

    def test_a_byte_mismatch_refuses(self):
        report = self.move(rvas=["0x00002000"], exact={"0x00002100"})
        self.assertIn("not byte-exact", report["refused_rows"]["0x00002000"])
        self.assertIn("blocked", report)

    def test_a_strong_definition_in_the_tu_refuses(self):
        report = self.move(rvas=["0x00002100"], comdat={self.CTOR})
        self.assertIn("outside a COMDAT", report["refused_rows"]["0x00002100"])

    def test_the_residual_keeping_its_matches_and_a_row_are_required(self):
        report = self.move(residual_lost=["0x00003000"])
        self.assertIn("remaining rows lose matches", report["blocked"])
        report = self.move(rows=[self.row(self.CTOR, "0x00002000")], approved={"0x00002000": self.TU})
        self.assertIn("whole donor", report["blocked"])

    def test_a_missing_destination_refuses(self):
        (self.root / self.TU).unlink()
        self.assertIn("does not exist", self.move()["blocked"])

    def ledger(self):
        reverse = self.root / "reverse"
        reverse.mkdir(exist_ok=True)
        self.write("reverse/functions.csv",
                   "name,export_rva,target_rva,target_size,source,status,notes\n"
                   f"{self.CTOR},,0x00002000,8,{self.SOURCE},matched,\n{self.COPY},,0x00002100,8,{self.SOURCE},matched,\n"
                   f"{self.STAY},,0x00003000,8,{self.SOURCE},matched,\n")
        self.write("reverse/tu_map.csv",
                   "rva,size,kind,tu,confidence,by,evidence,source\n"
                   f"0x00002000,8,code,{self.TU},approved,C,C=0x1..0x3,{self.SOURCE}\n"
                   f"0x00003000,8,code,{self.OTHER},approved,F,F={self.OTHER},{self.SOURCE}\n")
        subprocess.run(["git", "init", "-q", str(self.root)], check=True)
        return {rel: (self.root / rel).read_bytes() for rel in ("reverse/functions.csv", "reverse/tu_map.csv")}

    def test_the_move_repoints_only_the_ledger_after_build_sh_passes(self):
        self.ledger()
        texts = {p: (self.root / p).read_bytes() for p in (self.SOURCE, self.TU)}
        report = self.move(rvas=["0x00002000"], dry_run=False)
        self.assertNotIn("blocked", report)
        self.assertEqual(report["verified"], f"build.py over exactly {self.SOURCE} {self.TU}")
        self.exact.assert_called_once_with([self.SOURCE, self.TU])     # exact selection, no substring
        self.assertEqual(list((self.root / T.EMIT_JOURNAL).glob("*.json")), [])          # journal gone once staged
        funcs = (self.root / "reverse/functions.csv").read_text()
        self.assertIn(f"{self.CTOR},,0x00002000,8,{self.TU},matched", funcs)
        self.assertIn(f"{self.COPY},,0x00002100,8,{self.SOURCE},matched", funcs)       # not requested: stays
        self.assertIn(f"0x00002000,8,code,{self.TU},approved,C,C=0x1..0x3,{self.TU}",
                      (self.root / "reverse/tu_map.csv").read_text())
        self.assertEqual({p: (self.root / p).read_bytes() for p in texts}, texts)        # no text moved

    def test_a_failing_build_or_committed_object_puts_the_ledger_back(self):
        # review of 3db7ced4b4: a scratch sibling proves nothing about the committed paths
        for kw, why in (({"built": False}, "the build did not pass"),
                        ({"built_comdat": set()}, "outside a COMDAT"),
                        ({"built_defined": set()}, "does not define")):
            with self.subTest(kw=kw):
                before = self.ledger()
                report = self.move(rvas=["0x00002000"], dry_run=False, **kw)
                self.assertIn(why, report["blocked"])
                self.assertIn("the ledger was put back", report["blocked"])
                self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
                self.assertEqual(self.objects_left(), [])         # review of 692da8fc04: nothing to revalidate

    def objects_left(self):
        import build
        real = [self.root / "build" / "real_t.obj", self.root / "build" / "real_x.obj"]
        return [p.name for o in real for p in (o, build._deps_sidecar(o)) if p.exists()]

    def test_an_interrupt_puts_everything_back_and_releases_the_claims(self):
        # review of 692da8fc04: KeyboardInterrupt (or any exception) during ./build.sh
        before = self.ledger()
        with self.assertRaises(KeyboardInterrupt):
            self.move(rvas=["0x00002000"], dry_run=False, build_effect=KeyboardInterrupt, claim=True)
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
        self.assertEqual(self.objects_left(), [])
        self.released.assert_called_once()

    def test_a_passing_move_keeps_its_objects_and_claims(self):
        self.ledger()
        report = self.move(rvas=["0x00002000"], dry_run=False, claim=True)
        self.assertNotIn("blocked", report)
        self.assertEqual(len(self.objects_left()), 4)
        self.released.assert_not_called()

    def recover(self):
        """recover_emit in the fixture's tree; (result, claims.release mock)."""
        import build
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, {}, clear=True), \
                patch.object(build, "obj_path", side_effect=self.obj_path), \
                patch.object(T.claims, "release") as release:
            return T.recover_emit(), release

    def test_a_killed_verify_is_recovered_from_its_journal(self):
        # review of e81c016950: os._exit mid-verify skips every finally; the journal on disk is all
        # that is left, and --recover-emit restores from it
        before = self.ledger()
        self.kill_mid_verify()
        journals = list((self.root / T.EMIT_JOURNAL).glob("*.json"))
        self.assertEqual(len(journals), 1)
        self.assertNotEqual((self.root / "reverse/functions.csv").read_bytes(), before["reverse/functions.csv"])
        self.assertIn("did not finish", self.move(rvas=["0x00002000"])["blocked"])     # nothing starts meanwhile
        (restored, busy, errors), release = self.recover()
        self.assertEqual((len(restored), busy, errors), (1, [], []))
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
        self.assertEqual(self.objects_left(), [])
        self.assertEqual(list((self.root / T.EMIT_JOURNAL).glob("*.json")), [])
        release.assert_called_once()
        self.assertIn("file:Code/Campaign.cpp", release.call_args[0][0])

    def test_one_failed_cleanup_step_skips_none_of_the_others(self):
        # review of e81c016950: a locked .obj (Windows) must not stop the receipt, the other object
        # or the claim release; the journal stays so --recover-emit can finish the undo
        before = self.ledger()
        locked = self.root / "build" / "real_t.obj"
        real_unlink = Path.unlink

        def unlink(path, *a, **k):
            if Path(path) == locked:
                raise PermissionError("locked")
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink):
            report = self.move(rvas=["0x00002000"], dry_run=False, claim=True, built=False)
        self.assertIn("undo incomplete", report["blocked"])
        self.assertIn("could not remove real_t.obj", report["blocked"])
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
        self.assertEqual(self.objects_left(), ["real_t.obj"])           # everything else went
        self.released.assert_called_once()
        self.assertEqual(len(list((self.root / T.EMIT_JOURNAL).glob("*.json"))), 1)
        (restored, busy, errors), _ = self.recover()                    # the lock gone: the undo completes
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual(self.objects_left(), [])

    def test_exact_build_names_exactly_its_sources(self):
        # review of e81c016950: build.sh's selectors are substrings (Code/Campaign.cpp would also pick
        # Code/Campaign.cpp.extra.cpp); build.main(exact_sources=...) takes membership
        with patch.object(T, "ROOT", self.root), patch.object(T.subprocess, "run") as run:
            run.return_value = SimpleNamespace(returncode=0, stdout="Functions: OK 2/2 matched\n", stderr="")
            ok, _ = T.exact_build([self.TU, self.SOURCE])
        self.assertTrue(ok)
        code = run.call_args[0][0][2]
        self.assertIn("exact_sources=['Code/Campaign.cpp', 'Code/Mixed.cpp']", code)
        self.assertNotIn("build.sh", " ".join(run.call_args[0][0]))

    def kill_mid_verify(self):
        """A child process moves 0x2000 and dies by os._exit inside the verify: its journal and
        the unverified ledger are all that is left."""
        child = ("import os, sys\nfrom pathlib import Path\n"
                 f"sys.path[:0] = [{str(Path(__file__).resolve().parents[1])!r}, {str(Path(__file__).resolve().parent)!r}]\n"
                 "import test_tu_skeleton as M\n"
                 "t = M.EmitMoveTests('test_an_emitted_instantiation_and_copy_ctor_move')\n"
                 "t.root = Path(sys.argv[1])\n"
                 "t.move(rvas=['0x00002000'], dry_run=False, claim=True, build_effect=lambda sources: os._exit(3))\n")
        result = subprocess.run([sys.executable, "-c", child, str(self.root)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 3, result.stderr[-500:])

    def test_recovery_keeps_a_later_edit_to_another_row(self):
        # review of 90fdd5d03d: recovery restored whole snapshots, erasing a rename made since
        before = self.ledger()
        self.kill_mid_verify()
        funcs = self.root / "reverse/functions.csv"
        funcs.write_bytes(funcs.read_bytes().replace(b"?stay@@YAXXZ", b"?renamed@@YAXXZ"))
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual(funcs.read_bytes(), before["reverse/functions.csv"].replace(b"?stay@@YAXXZ", b"?renamed@@YAXXZ"))

    def test_recovery_refuses_when_a_moved_row_changed_since(self):
        self.ledger()
        self.kill_mid_verify()
        funcs = self.root / "reverse/functions.csv"
        edited = funcs.read_bytes().replace(f"0x00002000,8,{self.TU},matched,".encode(),
                                            f"0x00002000,8,{self.TU},matched,touched".encode())
        funcs.write_bytes(edited)
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual(restored, [])
        self.assertTrue(any("changed since the move" in e for e in errors), errors)
        self.assertEqual(funcs.read_bytes(), edited)                       # nothing guessed
        self.assertEqual(len(list((self.root / T.EMIT_JOURNAL).glob("*.json"))), 1)

    def test_each_tool_sees_the_others_pending_journal(self):
        # review of 90fdd5d03d: rename.py's guard ignored emit journals, and the reverse
        self.ledger()
        self.kill_mid_verify()
        with self.assertRaises(T.rename.Refusal):
            T.rename.refuse_pending_journal(T.rename.Context(self.root))
        self.recover()
        T.rename.refuse_pending_journal(T.rename.Context(self.root))       # gone with the emit journal
        folder = self.root / T.rename.JOURNAL_DIR
        (folder / "a-rename.json").write_text(json.dumps({"subject": "rename x", "pid": 0}))
        report = self.move(rvas=["0x00002000"], dry_run=False)
        self.assertIn("a pending journal: rename a-rename.json", report["blocked"])

    def test_the_pending_check_runs_under_the_ledger_lock(self):
        # two moves cannot both pass the check before either writes its journal
        self.ledger()
        held = []

        @contextlib.contextmanager
        def lock():
            held.append(True)
            yield
            held.pop()
        seen = []
        with patch.object(T, "ledger_locked", lock), \
                patch.object(T, "pending_journal", side_effect=lambda: seen.append(bool(held)) or None):
            self.assertNotIn("blocked", self.move(rvas=["0x00002000"], dry_run=False))
        self.assertEqual(seen, [True])

    def test_recovery_releases_only_with_the_fencing_tokens(self):
        # review of 90fdd5d03d: a release without tokens could delete a successor's claim
        self.ledger()
        self.kill_mid_verify()
        _result, release = self.recover()
        tokens = release.call_args.kwargs["tokens"]
        self.assertEqual(list(tokens.values()), [self.TOKEN])

    def test_an_interrupt_after_staging_restores_the_index(self):
        # review of 90fdd5d03d: the moved rows were staged before the journal went, and recovery
        # restored only the working files
        before = self.ledger()
        subprocess.run(["git", "-C", str(self.root), "add", "reverse"], check=True)
        subprocess.run(["git", "-C", str(self.root), "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "base"],
                       check=True)
        real_unlink = Path.unlink

        def unlink(path, *a, **k):
            if Path(path).suffix == ".json" and Path(path).parent.name == "emit-journal":
                raise KeyboardInterrupt                # dies after git add, before the journal goes
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink), self.assertRaises(KeyboardInterrupt):
            self.move(rvas=["0x00002000"], dry_run=False)
        staged = lambda: subprocess.run(["git", "show", ":reverse/functions.csv"], cwd=self.root,
                                        capture_output=True).stdout
        self.assertIn(self.TU.encode(), staged())                         # the move was staged
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual(staged(), before["reverse/functions.csv"])
        self.assertEqual((self.root / "reverse/functions.csv").read_bytes(), before["reverse/functions.csv"])


class FoldAliasSplitTests(unittest.TestCase):
    """--split: an ICF alias only the carved bodies emitted rides with them."""
    SOURCE, TU = "Code/Mixed.cpp", "Code/T.cpp"

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "Code").mkdir()
        (self.root / "reverse").mkdir()
        (self.root / self.SOURCE).write_text("void move(){}\nvoid stay(){}\n")

    def split(self, alias_identity_here=False, carved_emits_alias=True):
        row = lambda n, r, s: dict(name=n, export_rva="", target_rva=r, target_size="1", source=s,
                                   status="matched", notes="")
        mine = [row("_move", "0x1000", self.SOURCE), row("_stay", "0x3000", self.SOURCE),
                row("??1Alias@@QAE@XZ", "0x7000", self.SOURCE)]
        owner = mine[2] if alias_identity_here else row("??1Owner@@QAE@XZ", "0x7000", "Code/Owner.cpp")
        ledger = [owner] + [r for r in mine if r is not owner]
        seen = {}

        class Verifier:
            obj, errors, all_errors = None, [], []

            def __init__(self, source):
                self.source = source

            def matched(self, text, rows):
                names = set(re.findall(r"void\s+(\w+)\s*\(", text))
                out = {r["target_rva"] for r in rows if r["name"].lstrip("_") in names}
                if "move" in names and carved_emits_alias:     # only the carved body uses the alias
                    out.add("0x7000")
                return out

        def merge(tu, sk, don, report, dry_run, **kw):
            seen["don"] = don
            return dict(report, accepted=list(don))

        cache = {"ledger": ledger, "by_file": {self.SOURCE: mine},
                 "approved_at": {0x1000: self.TU, 0x3000: "Code/Other.cpp", 0x7000: "Code/W.cpp"},
                 "assigned": {0x1000: self.TU.lower(), 0x3000: "code/other.cpp", 0x7000: "code/w.cpp"}}
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, cache, clear=True), \
                patch.object(T, "refusal", return_value=None), patch.object(T, "included_by", return_value=[]), \
                patch.object(T, "data_rowed_idents", return_value=set()), patch.object(T, "debt_keys", return_value=set()), \
                patch.object(T, "hatch_move", return_value={}), patch.object(T, "skeleton", return_value=[]), \
                patch.object(T, "Verifier", Verifier), patch.object(T, "SplitLinkGuard"), \
                patch.object(T, "_merge", side_effect=merge):
            report = T.split(self.SOURCE, self.TU, dry_run=True, claim=False)
        return report, seen.get("don")

    def test_an_alias_only_the_carved_bodies_emitted_rides_with_them(self):
        report, don = self.split()
        self.assertNotIn("blocked", report)
        self.assertEqual(report["riders"], ["0x7000"])
        self.assertEqual(sorted(r["target_rva"] for r in don[self.SOURCE]), ["0x1000", "0x7000"])

    def test_an_alias_neither_side_emits_still_blocks(self):
        report, _ = self.split(carved_emits_alias=False)
        self.assertIn("ICF aliases the carved bodies do not emit", report["blocked"])
        self.assertEqual(report["residual_loses"], ["0x7000"])

    def test_the_address_identity_never_rides(self):
        report, _ = self.split(alias_identity_here=True)
        self.assertEqual(report["blocked"], "the residual loses matched rows (flag region or a shared helper)")
        self.assertEqual(report["residual_loses"], ["0x7000"])

    def test_an_emission_held_identity_rides_only_into_its_own_tu(self):
        # LINK-629: an instantiation only the carved bodies emitted moves with them when the map
        # places it (by contiguity alone) in this TU, and never into another TU
        held = lambda r: r["target_rva"] == "0x7000"
        for placed, rides in ((self.TU.lower(), True), ("code/w.cpp", False)):
            with self.subTest(placed=placed), patch.object(T, "emission_held", side_effect=held), \
                    patch.object(T, "assigned_tu", side_effect=lambda r: placed if held(r) else None):
                report, don = self.split(alias_identity_here=True)
            if rides:
                self.assertNotIn("blocked", report)
                self.assertEqual(report["riders"], ["0x7000"])
                self.assertEqual(sorted(r["target_rva"] for r in don[self.SOURCE]), ["0x1000", "0x7000"])
            else:
                self.assertEqual(report["residual_loses"], ["0x7000"])

    def test_breakdown_files_an_alias_as_unplaced(self):
        owner = dict(name="??1Owner@@QAE@XZ", target_rva="0x7000", source="Code/Owner.cpp", notes="", status="matched")
        alias = dict(owner, name="??1Alias@@QAE@XZ", source=self.SOURCE)
        with patch.dict(T._CACHE, {"ledger": [owner, alias], "approved_at": {0x7000: "Code/W.cpp"},
                                   "by_file": {self.SOURCE: [alias]}}, clear=True):
            self.assertEqual(list(T.breakdown(self.SOURCE)), [""])
        # a row the ledger does not hold is never taken for an alias
        with patch.dict(T._CACHE, {"ledger": [owner], "approved_at": {0x7000: "Code/W.cpp"},
                                   "by_file": {self.SOURCE: [alias]}}, clear=True):
            self.assertEqual(list(T.breakdown(self.SOURCE)), ["Code/W.cpp"])


class CaseVariantTuTests(unittest.TestCase):
    """A TU whose map spelling and checkout spelling differ only in case is one file."""

    def test_the_tree_spelling_wins_and_no_file_is_renamed(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "WW3D2").mkdir()
            (root / "WW3D2/fxshadersetup.cpp").write_text("int t() { return 0; }\n")
            self.assertEqual(T.tu_path("WW3D2/FXShaderSetup.cpp", root), "WW3D2/fxshadersetup.cpp")
            # no file in the tree yet: the map's spelling is what the merge writes
            self.assertEqual(T.tu_path("WW3D2/FXShaderParameter.cpp", root), "WW3D2/FXShaderParameter.cpp")
            self.assertEqual(sorted(p.name for p in (root / "WW3D2").iterdir()), ["fxshadersetup.cpp"])

    def test_the_merge_works_on_the_file_the_tree_has(self):
        tu, file_ = "Code/Lib/T.cpp", "Code/lib/t.cpp"
        ledger = [{"name": "?t@@YAXXZ", "export_rva": "", "target_rva": "0x1000", "target_size": "8",
                   "source": file_, "status": "matched", "notes": ""},
                  {"name": "?a@@YAXXZ", "export_rva": "", "target_rva": "0x1010", "target_size": "8",
                   "source": "Code/A.cpp", "status": "matched", "notes": ""}]
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code/lib").mkdir(parents=True)
            (root / "Code/lib/t.cpp").write_text("int t() { return 0; }\n")
            (root / "Code/A.cpp").write_text("int a() { return 1; }\n")
            T._CACHE.clear()
            T._CACHE["ledger"] = ledger
            T._CACHE["map"] = [{"rva": "0x1000", "size": "8", "kind": "code", "tu": tu,
                                "confidence": "approved", "by": "-", "evidence": "", "source": ""},
                               {"rva": "0x1010", "size": "8", "kind": "code", "tu": tu,
                                "confidence": "approved", "by": "-", "evidence": "", "source": ""}]
            T._CACHE["stale"] = False
            seen = {}

            def fake_merge(tu_, sk, don, report, dry_run, **kw):
                seen.update(tu=tu_, don=don)
                return report
            try:
                with patch.object(T, "ROOT", root), patch.object(T, "refusal", return_value=None), \
                        patch.object(T, "_merge", side_effect=fake_merge):
                    report = T.merge(tu, dry_run=True)
            finally:
                T._CACHE.clear()
            # one spelling on disk: the merge wrote the file the tree has, not a second one
            self.assertEqual(sorted(p.name for p in (root / "Code").iterdir()), ["A.cpp", "lib"])
            self.assertEqual([p.name for p in (root / "Code/lib").iterdir()], ["t.cpp"])
        self.assertEqual(seen["tu"], file_)
        self.assertEqual(sorted(seen["don"]), ["Code/A.cpp", file_])
        self.assertEqual(report["tu"], tu)              # the map's spelling still names the TU
        self.assertEqual(report["tu_file"], file_)


class ComposePreprocessorTests(unittest.TestCase):
    def test_forward_declaration_survives_in_both_output_streams(self):
        # Expansion-base: the seed's forward goes to decls, but the donor
        # needs its identical forward in pps before a filter and last include.
        texts = {"Seed.cpp": "class Player;\nstruct Seed { Player *player; };\n",
                 "Donor.cpp": ('class Player;\n'
                               'struct Filter { Filter(Player *player); };\n'
                               '#include "target.h"\n'
                               'class Player { public: int money; };\n')}
        for strategy in T.STRATEGIES:
            with self.subTest(strategy=strategy):
                out = T.compose("Seed.cpp", [], list(texts), texts, [], strategy)
                self.assertLess(out.index("class Player;"), out.index("struct Filter"))
                self.assertLess(out.index("class Player;"), out.index('#include "target.h"'))
                self.assertIn("class Player { public: int money; };", out)

    def test_forward_declarations_are_still_deduplicated_within_each_stream(self):
        for tag in ("class", "struct", "union"):
            texts = {"Seed.cpp": f"{tag} Node;\n{tag} Node;\n",
                     "Donor.cpp": f'{tag} Node;\n{tag} Node;\n#include "last.h"\n'}
            for strategy in T.STRATEGIES:
                with self.subTest(tag=tag, strategy=strategy):
                    out = T.compose("Seed.cpp", [], list(texts), texts, [], strategy)
                    self.assertEqual(out.count(f"{tag} Node;"), 2)
                    early, late = out.split('#include "last.h"')
                    self.assertEqual(early.count(f"{tag} Node;"), 1)
                    self.assertEqual(late.count(f"{tag} Node;"), 1)

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


class ComposeWhitespaceVariantTests(unittest.TestCase):
    """A type or typedef two donors spell with the same tokens is one spelling, the first, at
    the first position. Compared as collapsed strings, `struct Vec{int *p;};` and
    `struct Vec { int * p; };` were two variants: every strategy but 'first' emitted the
    donor's copy at the donor's position, below the seed's own uses of it (C2065,
    LinearCampaignManager.cpp's donors, cons-o1 2026-10-31)."""

    SEED = ("struct Vec{int *p;};\ntypedef char*PSTR;\n"
            "struct Holder { Vec v; PSTR s; };\nint seed() { return 1; }\n")
    DONOR = "struct Vec { int * p; };\ntypedef char * PSTR;\nint donor() { return 2; }\n"

    def compose(self, strategy, seed=SEED, donor=DONOR):
        return T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"],
                         {"Seed.cpp": seed, "Donor.cpp": donor}, [], strategy)

    def test_a_whitespace_variant_keeps_the_first_spelling_at_its_position(self):
        for st in T.STRATEGIES:
            out = self.compose(st)
            self.assertEqual(out.count("struct Vec"), 1, st)
            self.assertEqual(out.count("PSTR;"), 1, st)
            self.assertIn("struct Vec{int *p;};", out, st)        # the seed's own text
            self.assertIn("typedef char*PSTR;", out, st)
            self.assertLess(out.index("struct Vec"), out.index("struct Holder"), st)
            self.assertLess(out.index("PSTR;"), out.index("struct Holder"), st)
        self.assertEqual(len(T.distinct_strategies(self.compose)), 1)

    def test_spellings_that_differ_in_tokens_stay_variants(self):
        pairs = [("typedef A<B<int>> T;", "typedef A<B<int> > T;"),       # `> >` is not `>>`
                 ("enum E { V = 1--1 };", "enum E { V = 1 - -1 };"),       # `- -` is not `--`
                 ('struct S { S() : s("ab") {} const char *s; };',
                  'struct S { S() : s("a b") {} const char *s; };'),      # literal text is not whitespace
                 ("struct Q { int a; };", "struct Q { int a; int b; };")]
        for a, b in pairs:                                         # (seed's, donor's longer spelling)
            self.assertNotEqual(T.token_seq(a), T.token_seq(b), (a, b))
            seed, donor = a + "\nint seed() { return 1; }\n", b + "\nint donor() { return 2; }\n"
            self.assertIn(a, self.compose("first", seed, donor), (a, b))   # both spellings still on offer
            self.assertIn(b, self.compose("longest", seed, donor), (a, b))
        self.assertNotEqual(T.token_seq('char *s = "a b";'), T.token_seq('char *s = "a  b";'))
        self.assertNotEqual(T.token_seq("struct P {\n#pragma pack(1)\nint a;\n};"),   # a directive ends
                            T.token_seq("struct P {\n#pragma pack(1) int a;\n};"))    # at its line

    def test_comments_and_layout_are_not_tokens(self):
        self.assertEqual(T.token_seq("struct R{int*p;/* x */};"),
                         T.token_seq("struct R\n{\n    int * p;   // y\n};"))
        self.assertEqual(T.token_seq("x = a->b;"), ("x", "=", "a", "->", "b", ";"))


class QualifiedTypeCompositionTests(unittest.TestCase):
    def test_nested_definition_survives_beside_its_enclosing_class(self):
        seed = "class Outer { public: struct Node; void clear(); };\n"
        donor = (seed + "struct Outer::Node { Node *next; int value; };\n"
                 "void Outer::clear() { Node node; node.value = 0; }\n")
        rows = [({}, {"source": "Donor.cpp"})]
        for strategy in T.STRATEGIES:
            with self.subTest(strategy=strategy):
                out = T.compose("Seed.cpp", rows, ["Seed.cpp", "Donor.cpp"],
                                {"Seed.cpp": seed, "Donor.cpp": donor}, [], strategy)
                self.assertEqual(out.count("class Outer {"), 1)
                self.assertEqual(out.count("struct Outer::Node {"), 1)
                self.assertLess(out.index("class Outer {"), out.index("struct Outer::Node {"))
                self.assertLess(out.index("struct Outer::Node {"), out.index("void Outer::clear() {"))

    def test_qualified_names_keep_all_scopes_and_normalize_colon_spacing(self):
        for name in ("Outer::Node", "Other::Node", "ns::Outer::Node"):
            with self.subTest(name=name):
                text = "struct " + name + " : public Base { int value; };"
                self.assertEqual(T.key_of("decl", text), ("type", name))
                self.assertEqual(T.key_of("decl", text.replace("::", " :: ")), ("type", name))


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

    def test_quoted_sdk_include_survives_region_flag_replacement_and_composition(self):
        # ComRaise.cpp and ComInvoke.cpp share this valid /I operand. Splitting
        # it into words treated the path tail as flags and truncated the include.
        include = "reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
        for prefix in ("/I", "-I"):
            text = f'// cl: /O2 /MD {prefix}"{include}"\nint f() {{ return 0; }}\n'
            out = self.verifier().effective(text, [{"target_rva": "0x1000", "target_size": "8"}])
            flags = T.flags_of(out)
            self.assertEqual(flags, ["/O1", "/arch:SSE", "/G7", "/MD", prefix + include])
            composed = T.compose("Code/T.cpp", [], ["Code/A.cpp"],
                                 {"Code/A.cpp": text}, flags, "first")
            self.assertEqual(T.flags_of(composed), flags)

    def test_include_flag_round_trip_keeps_windows_backslashes_and_operand_boundaries(self):
        text = '// cl: /MD /I "reference\\Program Files\\SDK" /EHsc -ICode\n'
        flags = T.flags_of(text)
        self.assertEqual(flags, ["/MD", "/Ireference\\Program Files\\SDK", "/EHsc", "-ICode"])
        self.assertEqual(T.flags_of("// cl: " + T.render_flags(flags)), flags)

    def test_malformed_quoted_include_is_still_refused(self):
        for operand in ('/I"unfinished path', '/I""', '/I"SDK path"trailing'):
            with self.assertRaises(SystemExit):
                T.flags_of("// cl: " + operand)


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
        v.timeout = 30
        v.effective = lambda text, rows: text
        v.fd = SimpleNamespace(forced_mode=lambda mode: contextlib.nullcontext())
        compiled = {}
        calls = []

        def compile_source(src, obj, timeout=None):
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
            v.B.try_compile_source = lambda src, obj, timeout=None: (
                seen.append(src.suffix), compile_source(src, obj))[1]
            self.assertEqual(v.matched("exact", self.ROWS), {"0x1000"})
            self.assertEqual(seen, [".c"])

    def test_a_killed_compile_is_refused_as_a_compile_timeout(self):
        # cl.exe under Wine can spin forever on a composed candidate; build kills the
        # tree at the wall-clock limit and reports TIMEOUT_STATUS, which is a refusal
        # (never an acceptance) and is cached, so the 10-minute wait is paid once.
        with tempfile.TemporaryDirectory() as tmp:
            v, _ = self.verifier(Path(tmp))
            timeouts = []
            v.B.try_compile_source = lambda src, obj, timeout=None: (
                timeouts.append(timeout), (False, "\ncompile timed out after 30 s\n", 124))[1]
            self.assertIsNone(v.matched("hangs", self.ROWS))
            self.assertEqual((v.errors, v.all_errors), (["compile timeout"], ["compile timeout"]))
            self.assertIsNone(v.matched("hangs", self.ROWS))
            self.assertEqual(timeouts, [30])
            self.assertEqual(T.redefined(v.all_errors), set())


class CompileTimeoutTests(unittest.TestCase):
    """The trial-compile limit: default, environment knob and validation."""

    def test_the_limit_has_a_default_and_reads_its_environment_knob(self):
        with patch.dict(os.environ, {}, clear=False):
            os.environ.pop("BFME_COMPILE_TIMEOUT", None)
            self.assertEqual(T.compile_timeout(), T.COMPILE_TIMEOUT)
        with patch.dict(os.environ, {"BFME_COMPILE_TIMEOUT": " 90 "}):
            self.assertEqual(T.compile_timeout(), 90.0)
        for bad in ("0", "-5", "ten"):
            with patch.dict(os.environ, {"BFME_COMPILE_TIMEOUT": bad}):
                with self.assertRaises(ValueError):
                    T.compile_timeout()

    def test_the_default_is_far_past_every_real_compile_and_short_of_the_hangs(self):
        # Measured on the boat toolchain (dd-71, 2026-10-30): 397 trial compiles of
        # FirewallHelper.cpp ran p50 0.37 s, p90 1.62 s, p99 2.74 s, max 3.64 s, and a
        # 10-job box is ~3x slower (~12 s). The shortest observed hang lasted 2,196 s
        # (build/fleet/bulk/cl_hang_evidence.txt).
        self.assertGreaterEqual(T.COMPILE_TIMEOUT, 10 * 12)
        self.assertLess(T.COMPILE_TIMEOUT, 2196)


class RepointTests(unittest.TestCase):
    def test_merge_preserves_naming_revert_binding_and_historical_evidence(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            path = root / T.rename.NAME_BASIS
            path.write_bytes(
                b'kind,old,new,basis,evidence,source,rva\n'
                b'param,Connection::ack::p,Connection::ack::msg,inferred,'
                b'"direct:nd-0123456789abcdef01234567 inspected Code/A.cpp, retail packet",Code/A.cpp,0x1000\n'
                b'param,Other::ack::p,Other::ack::msg,inferred,agree:nl-two,Code/Keep.cpp,0x2000\n')
            before = path.read_bytes()
            votes = root / "reverse/name_votes.csv"
            votes.write_bytes(b'Code/A.cpp|param|Connection::ack|p,original-vote\n')
            moved = T.repoint_all(root, ["Code/A.cpp"], "Code/T.cpp")
            self.assertEqual(moved, {T.rename.NAME_BASIS: 1})
            self.assertEqual(path.read_bytes(), before.replace(b',Code/A.cpp,', b',Code/T.cpp,'))
            self.assertEqual(votes.read_bytes(), b'Code/A.cpp|param|Connection::ack|p,original-vote\n')
            with path.open(newline="") as stream:
                rows = list(csv.DictReader(stream))
            ctx = SimpleNamespace(dicts=lambda rel: rows)
            landed = T.rename.landing(ctx, "nd-0123456789abcdef01234567")
            self.assertEqual((landed.source, landed.target), ("Code/T.cpp", "Connection::ack::p"))
            self.assertEqual(T.repoint_all(root, ["Code/A.cpp"], "Code/T.cpp"), {})

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

    def test_repoint_all_moves_functions_csv_fold_proof_notes(self):
        # fa09ab8ace, 2cb6a36060: a merge repointed the row's source column but left
        # its notes token naming the deleted donor
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            path = root / "reverse/functions.csv"
            path.write_bytes(
                b'name,export_rva,target_rva,target_size,source,status,notes\n'
                b'??1A@@QAE@XZ,,0x1000,12,Code/A.cpp,matched,fold-proof=Code/A.cpp; folded with ??1B@@QAE@XZ\n'
                b'??1C@@QAE@XZ,,0x1000,12,Code/Keep.cpp,matched,"ICF, fold-proof=Code/B.cpp"\n'
                b'?d@@YAXXZ,,0x2000,5,Code/A.cpp,matched,\n'
                b'?e@@YAXXZ,,0x3000,5,Code/Keep.cpp,matched,fold-proof=Code/Keep.cpp\n'
                b'?f@@YAXXZ,,0x4000,5,Code/Keep.cpp,matched,fold-proof=Code/A.cpp.bak\n')
            moved = T.repoint_all(root, ["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp")
            # rows: ??1A (source and notes, counted once), ??1C (notes only), ?d (source only)
            self.assertEqual(moved, {"reverse/functions.csv": 3})
            self.assertEqual(path.read_bytes(),
                b'name,export_rva,target_rva,target_size,source,status,notes\n'
                b'??1A@@QAE@XZ,,0x1000,12,Code/T.cpp,matched,fold-proof=Code/T.cpp; folded with ??1B@@QAE@XZ\n'
                b'??1C@@QAE@XZ,,0x1000,12,Code/Keep.cpp,matched,"ICF, fold-proof=Code/T.cpp"\n'
                b'?d@@YAXXZ,,0x2000,5,Code/T.cpp,matched,\n'
                b'?e@@YAXXZ,,0x3000,5,Code/Keep.cpp,matched,fold-proof=Code/Keep.cpp\n'
                b'?f@@YAXXZ,,0x4000,5,Code/Keep.cpp,matched,fold-proof=Code/A.cpp.bak\n')
            self.assertEqual(T.repoint_all(root, ["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp"), {})

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


class OverrideCarryTests(unittest.TestCase):
    def test_only_the_leading_baseline_o2_is_redundant(self):
        self.assertEqual(T.override_flags_key("-O2"), T.override_flags_key(""))
        self.assertEqual(T.override_flags_key("-O2 -G7"), T.override_flags_key("-G7"))
        for flags in ("-O1", "-Ox", "-G6", "-G7", "-arch:SSE", "-arch:SSE2",
                      "-O1 -O2"):
            with self.subTest(flags=flags):
                self.assertNotEqual(T.override_flags_key(flags), T.override_flags_key(""))

    def test_carry_combines_redundant_o2_without_losing_register_totals(self):
        raw = (b"source,flags,rows,default_lost,reason\n"
               b"Code/A.cpp,-O2,1,1,region default loses rows\n"
               b"Code/T.cpp,,15,13,region default loses rows\n")
        out, moved = T.carry_overrides(raw, {"Code/A.cpp"}, "Code/T.cpp", "")
        self.assertEqual(moved, 1)
        self.assertEqual(out, raw.splitlines(keepends=True)[0] +
                         b"Code/T.cpp,,16,14,region default loses rows\n")
        for flags in (b"-O1", b"-Ox", b"-O2 -G7", b"-O2 -arch:SSE"):
            with self.subTest(flags=flags), self.assertRaises(ValueError):
                T.carry_overrides(raw.replace(b",-O2,", b"," + flags + b","),
                                  {"Code/A.cpp"}, "Code/T.cpp", "")


class MergeDiagnosticsTests(unittest.TestCase):
    def test_redundant_o2_donor_override_reaches_byte_verification(self):
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}], donor: [{"target_rva": "0x1010"}]}
        overrides = {tu: {"flags": "", "rows": "15"},
                     donor: {"flags": "-O2", "rows": "1"}}
        verified = []

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: overrides)
            errors, all_errors = [], []
            flags = None

            def matched(self, text, rows):
                verified.append((text, self.flags, [r["target_rva"] for r in rows]))
                return {r["target_rva"] for r in rows}

            def effective(self, text, rows):
                return text

        carry = SimpleNamespace(report=lambda: {}, problems=[])
        with patch.object(T, "Verifier", return_value=Verifier()), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "Carry", return_value=carry), \
                patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts=texts)
        self.assertNotIn("blocked", out)
        self.assertEqual(out["accepted"], [tu, donor])
        self.assertIn(("composed", "", ["0x1000", "0x1010"]), verified)
        apply.assert_not_called()

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

    def test_a_donor_override_that_costs_the_tu_rows_leaves_the_donor_out(self):
        # Connection.cpp, Mouse.cpp, ScriptActions.cpp: a one-row donor's override was carried
        # (the TU has none), the TU's own rows stopped matching under it and the whole merge
        # blocked; the TU now keeps its region default and only the overridden donor stays out.
        tu, plain, odd = "Code/T.cpp", "Code/A.cpp", "Code/B.cpp"
        texts = {tu: "seed", plain: "plain", odd: "odd"}
        don = {tu: [{"target_rva": "0x1000"}, {"target_rva": "0x1008"}],
               plain: [{"target_rva": "0x1010"}], odd: [{"target_rva": "0x1020"}]}
        overrides = {odd: {"flags": "-O2 -arch:SSE", "rows": "1"}}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: overrides)
            errors, all_errors = [], []

            def __init__(self, tu_=None, flags=None, region=False):
                self.flags, self.region = flags, region

            def matched(self, text, rows):
                if self.flags and text == "seed":   # the TU's rows need the region default
                    return set()
                return {r["target_rva"] for r in rows}

        with patch.object(T, "Verifier", side_effect=Verifier), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts=texts)
        self.assertNotIn("blocked", out)
        self.assertEqual(out["accepted"], [tu, plain])
        self.assertIn("costs the TU file 2 row(s)", out["rejected"][odd])
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

    def test_a_candidate_whose_compile_times_out_is_refused_with_that_reason(self):
        # The trial compile was killed at the limit: there are no diagnostics to quote,
        # so the refusal says why, and nothing is accepted.
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}], donor: [{"target_rva": "0x1010"}]}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors = ["compile timeout"]
            all_errors = errors

            def matched(self, text, rows):
                return {r["target_rva"] for r in rows} if text in texts.values() else None

        with patch.object(T, "Verifier", return_value=Verifier()), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts=texts)
        self.assertEqual(out["rejected"], {tu: "compile timeout", donor: "compile timeout"})
        self.assertEqual(out["accepted"], [])
        apply.assert_not_called()


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

    LOST_PRIVATE = "no longer defines private, which the census still references"

    def aggregate_guard(self, tmp):
        """A guard over an index --update-index refreshed: its reference graph is
        the census's aggregate, with no per-object provenance. t.obj defines
        `private` and references it, a.obj references it too, and the aggregate
        counts both (PartitionManager.cpp, census index 12902e9e1b: the
        getClassMemoryPool guards only the old seed object defined and used)."""
        guard = self.guard(tmp)
        index = guard.index
        index["strong"]["private"] = [0]
        index["references"]["edges"]["?t@@YAXXZ"] = frozenset({"?a@@YAXXZ", "private"})
        index["references"]["referenced"].add("private")
        index["touches"] = {"t.obj": {"?t@@YAXXZ", "?a@@YAXXZ", "?inl@@YAXXZ", "private"},
                            "a.obj": {"?a@@YAXXZ", "?al@@YAXXZ", "?inl@@YAXXZ", "private"},
                            "b.obj": {"?b@@YAXXZ"}, "x.obj": {"?x@@YAXXZ", "?inl@@YAXXZ"}}
        self.assertNotIn("objects", index["references"])
        return guard

    def test_a_definition_only_the_replaced_objects_reference_is_not_lost(self):
        # The seed and its donor are both replaced; their references to `private`,
        # including the seed's to its own definition, leave with them.
        for kind in ("seed and donor", "replaced alias", "forgotten referrer"):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as tmp:
                guard = self.aggregate_guard(tmp)
                if kind == "replaced alias":       # a replaced object's route nobody outside takes
                    guard.index["alternates"]["route"] = [(0, "private")]
                    guard.index["touches"]["a.obj"].add("route")
                elif kind == "forgotten referrer":  # --update-index dropped the unit (and its touches)
                    guard.index["touches"].pop("b.obj")
                    guard.index["forgotten"] = {"b.obj"}
                why, _ = self.judge(guard, [self.TU, self.A], defined=("?t@@YAXXZ", "?a@@YAXXZ"))
                self.assertEqual(why, [])

    def test_a_definition_another_object_references_is_still_lost(self):
        for kind in ("outside reference", "gone referrer", "untracked object", "no touches table",
                     "ledger owner", "outside alias", "replaced alias taken outside", "replacement reference"):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as tmp:
                guard = self.aggregate_guard(tmp)
                index, undefined = guard.index, ()
                if kind == "outside reference":
                    index["touches"]["x.obj"].add("private")
                elif kind == "gone referrer":       # merged away since the census, not by this merge
                    index["touches"]["b.obj"].add("private")
                    del guard.rank["b.obj"]
                elif kind == "untracked object":
                    del index["touches"]["x.obj"]
                elif kind == "no touches table":
                    del index["touches"]
                elif kind == "ledger owner":
                    index["selection"]["owners"]["private"] = {"t.obj"}
                elif kind == "outside alias":
                    index["alternates"]["route"] = [(3, "private")]
                elif kind == "replaced alias taken outside":
                    index["alternates"]["route"] = [(0, "private")]
                    index["touches"]["x.obj"].add("route")
                else:
                    undefined = ("private",)
                why, _ = self.judge(guard, [self.TU, self.A], defined=("?t@@YAXXZ", "?a@@YAXXZ"),
                                    undefined=undefined)
                self.assertIn(self.LOST_PRIVATE, why)

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

    def judge(self, guard, files, defined=("?t@@YAXXZ", "?a@@YAXXZ", "?b@@YAXXZ"), undefined=()):
        """guard.judge of a merged object that links by itself, defines `defined`
        and references `undefined`; returns (why, the `previous` new_variants was given)."""
        import link_check as LC
        import link_census as LCe
        import link_debt
        given = {}

        def new_variants(obj, view, truth, previous=None, rank=None):
            given["previous"] = previous
            self.last_variant_rank = rank
            return []
        clean = {"unresolved": [], "duplicates": [], "comdat": [], "addresses": [], "selected": [],
                 "unreferenced_differs": []}
        with patch.object(LC, "check_object", return_value=clean), \
                patch.object(LC, "new_variants", side_effect=new_variants), \
                patch.object(LCe, "object_facts", return_value=([], list(defined), list(undefined), [])), \
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

    def test_a_known_cohort_can_use_a_stale_slot_without_crossing_an_outsider(self):
        import build
        name = lambda f: build.obj_path(build.ROOT / f).name
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
            guard.prepare([self.TU, self.A])
            guard.previous = {0: {"?inl@@YAXXZ": {"stale"}}, 1: {"?inl@@YAXXZ": {"current"}}}
            why, previous = self.judge(guard, [self.TU, self.A])
        self.assertEqual(why, [])
        self.assertEqual(self.last_variant_rank["m.obj"], 10)
        self.assertEqual(self.last_variant_rank[name(self.TU)], 11)
        self.assertIn("current", previous["?inl@@YAXXZ"])
        self.assertNotIn("stale", previous["?inl@@YAXXZ"])

    def test_a_stale_slot_cannot_cross_a_live_or_unindexed_outsider(self):
        import build
        name = lambda f: build.obj_path(build.ROOT / f).name
        for outsider in (name(self.B), "new.obj"):
            with self.subTest(outsider=outsider), tempfile.TemporaryDirectory() as tmp:
                guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
                guard.rank[outsider] = 10.5
                why, _ = self.judge(guard, [self.TU, self.A])
                self.assertTrue(any("earlier in link order" in w for w in why))

    def test_an_empty_interval_does_not_excuse_a_changed_census_side(self):
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
            guard.rank["x.obj"] = 9       # census-last, currently before both cohort objects
            why, _ = self.judge(guard, [self.TU, self.A])
        self.assertTrue(any("earlier in link order" in w for w in why))

    def test_a_blocker_for_the_wrong_cohort_object_cannot_prove_a_stale_slot(self):
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
            guard.index["blockers"][self.A]["object"] = guard.index["objects"][2]
            why, _ = self.judge(guard, [self.TU, self.A])
        self.assertTrue(any("earlier in link order" in w for w in why))

    def test_a_gone_intermediary_leaves_an_empty_gap_but_a_live_one_does_not(self):
        for live in (False, True):
            with self.subTest(live=live), tempfile.TemporaryDirectory() as tmp:
                guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
                guard.index["objects"].insert(1, "old-render.obj")
                for table, _ in T.LINK_TABLES:
                    for name, entries in guard.index[table].items():
                        guard.index[table][name] = [e + (e >= 1) if table == "strong"
                                                   else (e[0] + (e[0] >= 1), *e[1:]) for e in entries]
                if live:
                    guard.rank["old-render.obj"] = 10.5
                why, _ = self.judge(guard, [self.TU, self.A])
                self.assertEqual(any("earlier in link order" in w for w in why), live)

    def test_an_unknown_surviving_census_rank_keeps_the_stale_slot_refusal(self):
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp, {self.TU: 11, self.A: 10})
            guard.prepare([self.TU, self.A])
            del guard.rank["x.obj"]
            guard.gone = set()            # no proof that the unknown object left the link
            with patch.object(guard, "prepare", return_value=None):
                why, _ = self.judge(guard, [self.TU, self.A])
        self.assertTrue(any("earlier in link order" in w for w in why))

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
                         missing_cohort_proof=False, becomes_referenced=False, alias_only=False,
                         cohort_ranks=None):
        """Exercise real variant and keep rules around a two-file merge."""
        import link_check as LC
        import link_census as LCe
        import link_debt
        name = "?inl@@YAXXZ"
        with tempfile.TemporaryDirectory() as tmp:
            guard = self.ranked_guard(tmp, cohort_ranks)
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

    def test_a_stale_holder_cannot_exempt_its_different_selected_body(self):
        why = self.judge_moved_copy([(0, "stale", None), (1, "current", None), (3, "other", None)],
                                   emitted="stale", cohort_ranks={self.TU: 11, self.A: 10})
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

    def test_an_icf_alias_row_adds_no_address_to_the_scope(self):
        def row(name, rva, source, notes=""):
            return {"name": name, "export_rva": "", "target_rva": rva, "target_size": "14",
                    "source": source, "status": "matched", "notes": notes}
        identity = row("?owner@@YAXXZ", "0x0007FAB3", "Code/Owner.cpp")
        alias = row("?alias@@YAXXZ", "0x0007FAB3", "Code/A.cpp", "fold-proof=Code/A.cpp")
        own = row("?own@@YAXXZ", "0x00001010", "Code/A.cpp")
        T._CACHE.clear()
        T._CACHE["ledger"] = [identity, alias, own]
        try:
            self.assertEqual(T.claim_keys("Code/T.cpp", {"Code/A.cpp": [alias, own]}),
                             ["file:Code/T.cpp", "file:Code/A.cpp", "0x00001010"])
            # the unit that owns the identity row still claims the address
            self.assertEqual(T.claim_keys("Code/T.cpp", {"Code/Owner.cpp": [identity]}),
                             ["file:Code/T.cpp", "file:Code/Owner.cpp", "0x0007FAB3"])
        finally:
            T._CACHE.clear()

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
                patch.object(T, "link_rank", side_effect=LC.link_rank), \
                patch.object(LC, "require_common_index", return_value=None), \
                patch.object(T.LinkGuard, "census_contexts", return_value={}):
            self.assertIsNone(guard.prepare([]))
            order = [p.name for p in LCe.link_order(rows, [])]
        self.assertEqual(sorted(guard.rank, key=guard.rank.get), order)
        import build
        self.assertEqual(order, [build.obj_path(build.ROOT / f"Code/{s}.cpp").name for s in ("Owner", "Mid", "Mover")])
