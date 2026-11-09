"""tu_skeleton's merge lane: verified flags, redefinition repair, repointing and claims."""
import contextlib
import csv
import hashlib
import io
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

REAL_MAP_REGRESSIONS = T.map_regressions
REAL_APPLY = T.apply


def setUpModule():
    """A merge rebuilds the map in memory to judge its approvals (tu_map.build, about 40 s on the
    real tree): stubbed to pass here; MergeMapRegressionTests drives the real one."""
    patcher = patch.object(T, "map_regressions", return_value=None)
    patcher.start()
    unittest.addModuleCleanup(patcher.stop)

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

    @staticmethod
    def held(refused=(), acquired=()):
        """A claim_scope answer: `refused` keys (truthy when any), and the keys it `acquired` with tokens."""
        held = T.Held(refused)
        held.acquired = [T.claims.key_of(k) for k in acquired]
        held.tokens = {k: f"token-{k}" for k in held.acquired}
        return held

    def test_held_accepted_donor_blocks_before_plan_checks(self):
        # review of 9459886c66: the refusal released the whole requested scope without tokens; it gives
        # back only what the claim acquired, fenced (and nothing when it acquired nothing)
        for acquired in (["file:Code/T.cpp"], []):
            with self.subTest(acquired=acquired), self.saved_cohort() as (donors, plan, release, search), \
                    patch.object(T, "claim_scope", return_value=self.held(["file:Code/A.cpp"], acquired)), \
                    patch.object(T, "reuse_merge_plan") as reuse:
                result = T.merge("Code/T.cpp")
                self.assertIn("Code/A.cpp", result["blocked"])
                reuse.assert_not_called()
                search.assert_not_called()
                if acquired:
                    key = T.claims.key_of("file:Code/T.cpp")
                    release.assert_called_once_with([key], tokens={key: f"token-{key}"})
                else:
                    release.assert_not_called()

    def test_failed_plan_cannot_search_until_full_scope_is_claimed(self):
        first_keys = ["file:Code/T.cpp", "file:Code/A.cpp"]
        for held in ([], ["file:Code/Rejected.cpp"]):
            with self.subTest(held=held), self.saved_cohort() as (donors, plan, release, search), \
                    patch.object(T, "claim_scope", side_effect=[self.held((), first_keys), self.held(held)]) as claimed, \
                    patch.object(T, "reuse_merge_plan", return_value=None):
                def fallback(tu, sk, scope, report, dry_run):
                    self.assertEqual(claimed.call_count, 2)
                    self.assertEqual(claimed.call_args.args[1], donors)
                    return dict(report, accepted=plan["accepted"])

                search.side_effect = fallback
                result = T.merge("Code/T.cpp")
                accepted = {f: donors[f] for f in plan["accepted"]}
                self.assertEqual(set(claimed.call_args_list[0].args[1]), set(plan["accepted"]))
                self.assertEqual(claimed.call_args_list[1].args[1], donors)
                # the wider claim leaves what the first holds alone: a renewal would rotate its tokens
                self.assertEqual(claimed.call_args_list[1].kwargs["skip"], T.claim_keys("Code/T.cpp", accepted))
                if held:
                    self.assertIn("Code/Rejected.cpp", result["blocked"])
                    search.assert_not_called()
                    keys = [T.claims.key_of(k) for k in first_keys]
                    release.assert_called_once_with(keys, tokens={k: f"token-{k}" for k in keys})
                else:
                    self.assertNotIn("blocked", result)
                    search.assert_called_once()
                    release.assert_not_called()

    def test_malformed_saved_cohort_requires_full_claim_scope(self):
        key = T.claims.key_of("file:Code/T.cpp")
        for accepted in ([], ["Code/T.cpp", "Code/Unknown.cpp"],
                         ["Code/T.cpp", "Code/T.cpp"], ["Code/T.cpp", None], ["Code/A.cpp"]):
            with self.subTest(accepted=accepted), self.saved_cohort() as (donors, plan, release, search), \
                    patch.object(T, "claim_scope", return_value=self.held(["file:Code/Rejected.cpp"],
                                                                          ["file:Code/T.cpp"])) as claimed, \
                    patch.object(T, "reuse_merge_plan") as reuse:
                plan["accepted"] = accepted
                result = T.merge("Code/T.cpp")
                self.assertIn("blocked", result)
                claimed.assert_called_once_with("Code/T.cpp", donors)
                reuse.assert_not_called()
                search.assert_not_called()
                release.assert_called_once_with([key], tokens={key: f"token-{key}"})

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

    COPY = "??0Rec@@QAE@ABV0@@Z"

    def test_a_special_member_placed_by_contiguity_alone_is_never_held(self):
        # review of bfb856bfbf: `Rec(Rec const (((&r)))) : a(r.a) {}` is hand-written yet compiles to
        # the implicit copy ctor's COMDAT; rule (a) is dropped and only template instances are held
        clean = "struct Rec { int a; };\n"
        for name in (self.COPY, "??1Rec@@QAE@XZ", "??4Rec@@QAEAAU0@ABU0@@Z", "??_GRec@@UAEPAXI@Z"):
            for text in (clean, "class Rec { public: Rec(Rec const (((&r)))):a(r.a){} int a; };\n"):
                with self.subTest(name=name, text=text):
                    cache = {"map_by_rva": {0x1200: {"tu": "Code/XferSave.cpp", "by": "C",
                                                     "evidence": "C=0x00001100..0x00001300"}}}
                    with patch.dict(T._CACHE, cache, clear=True):
                        self.assertFalse(T.emission_held({"name": name, "target_rva": "0x00001200", "source": self.TU}))
        ledger = [("?t@@YAXXZ", 0x1000, self.TU), (self.COPY, 0x1200, self.TU), ("?a@@YAXXZ", 0x1010, "Code/A.cpp")]
        with patch.object(T, "spells_definition", return_value=False):
            _don, mixed, _ = self.donors(ledger, {0x1000: self.TU, 0x1010: self.TU, 0x1200: self.C})
        self.assertEqual(mixed, {self.TU: 1})                # it makes the TU file mixed, as before rule (a)

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
    """--emit-move: a deleting-destructor row (`??_G`/`??_E`, by its decorated name) moves from a
    mixed file to its approved TU only when the TU's own code emits it byte-exact (P16)."""
    SOURCE, TU, OTHER = "Code/Mixed.cpp", "Code/Campaign.cpp", "Code/Other.cpp"
    INSTANCE = "??$_Construct@VRec@@V1@@_STL@@YAXPAVRec@@ABV1@@Z"    # a template instance: never moves by emission
    VDTOR = "??_ERec@@UAEPAXI@Z"                                       # a vector deleting destructor
    COPY = "??0Rec@@QAE@ABV0@@Z"                                       # a copy ctor: never moves by emission
    DTOR = "??_GRec@@UAEPAXI@Z"                                        # a deleting destructor: always the compiler's
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
             rows=None, dry_run=True, file_defined=(), file_comdat=(), final_lost=(),
             built=True, copies=None, pp_fail=(), built_defined=None, built_comdat=None, build_effect=None, claim=False):
        """emit_move over a file holding VDTOR (0x2000), DTOR (0x2100) and STAY (0x3000). `approved`
        {rva: tu}; the TU's scratch object `defined`/`comdat` names and the rvas it matches `exact`
        (`final_lost` lost when judged with only the rows that finally move); the file's object
        `file_defined`/`file_comdat`; for the apply, ./build.sh passing (`built`) and the real TU object's
        `built_defined`/`built_comdat`; `copies` {object file name: why its copy is not the compiler's};
        `pp_fail` the units cl -E refuses."""
        rows = rows if rows is not None else [self.row(self.VDTOR, "0x00002000"), self.row(self.DTOR, "0x00002100"),
                                              self.row(self.STAY, "0x00003000")]
        approved = approved if approved is not None else {"0x00002000": self.TU, "0x00002100": self.TU,
                                                          "0x00003000": self.OTHER}
        defined = {self.VDTOR, self.DTOR} if defined is None else defined
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

            def preprocessed(self, text, judged):
                return (None, "cl -E failed") if self.tu in pp_fail else (text, None)

        import build
        import name_dependents
        own = lambda p: rows if p == self.SOURCE else []
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, {}, clear=True), \
                patch.object(T, "file_rows", side_effect=own), patch.object(T, "breakdown", return_value=groups), \
                patch.object(T, "fold_alias", return_value=False), patch.object(T, "Verifier", Verifier), \
                patch.object(T.rename, "preprocess_unit", side_effect=AssertionError("no text is read")), \
                patch.object(T, "comdat_symbols", side_effect=lambda obj: comdats.get(Path(obj), set())), \
                patch.object(T, "deleting_copy_problem", side_effect=lambda obj, name: (copies or {}).get(Path(obj).name)), \
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
        held.acquired = [T.claims.key_of(f"file:{self.TU}")]
        held.tokens = {T.claims.key_of(f"file:{self.TU}"): self.TOKEN}
        return held

    def obj_path(self, source):
        """build.obj_path in the fixture: the two files' real build/match objects."""
        rel = Path(source).relative_to(self.root).as_posix()
        return self.root / "build" / {self.TU: "real_t.obj", self.SOURCE: "real_x.obj"}[rel]

    def test_emitted_deleting_destructors_move(self):
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

    def test_a_template_instance_never_moves_by_emission(self):
        # review of 0c8c510c89: a project `#line` naming an STLport header, or `namespace _STL` reopened
        # with a template of STLport's name, defeats every text proof of provenance; the name refuses
        for name in (self.INSTANCE, self.LIST_CLEAR, self.HASH_CLEAR, self.HASH_DELETE, "?f@?$C@H@@QAEXXZ",
                     "?clear@?$list@H@_STL@@QAEXXZ", "??1?$list@HV?$allocator@H@_STL@@@_STL@@QAE@XZ",
                     "??_G?$Box@H@@UAEPAXI@Z"):
            with self.subTest(name=name):
                self.assertIn("a template instance", T.emission_problem({"name": name}))
        report = self.move(rows=[self.row("?f@Rec@@QAEXXZ", "0x00002000"), self.row(self.STAY, "0x00003000")])
        self.assertIn("not a deleting destructor", report["refused_rows"]["0x00002000"])


    def test_a_constructor_destructor_or_assignment_never_moves_by_emission(self):
        # review of 9459886c66: `typedef Rec Alias; Alias(Rec const&r)` and `(Rec)(Rec const&r)` compile in
        # VC7.1 to the implicit copy ctor's exact name, bytes and relocations; the name alone refuses
        for name in (self.COPY, "??0Rec@@QAE@XZ", "??1Rec@@QAE@XZ", "??1Rec@@UAE@XZ", "??4Rec@@QAEAAU0@ABU0@@Z"):
            with self.subTest(name=name):
                self.assertIn("not a deleting destructor", T.emission_problem({"name": name}))

    def test_a_deleting_destructor_is_decided_by_its_name(self):
        for name in (self.DTOR, self.VDTOR, "??_GRec@@QAEPAXI@Z", "??_GParticleSystemFXNugget@@UAEPAXI@Z"):
            with self.subTest(name=name):
                self.assertIsNone(T.emission_problem({"name": name}))
        for name in ("??_GRec@@UAEPAXH@Z", "??_FRec@@QAEXXZ", "??_DRec@@QAEXXZ", "??_GRec@@UAEPAXI@Z?"):
            with self.subTest(name=name):                   # not a deleting destructor's shape
                self.assertIsNotNone(T.emission_problem({"name": name}))

    LIST_CLEAR = "?clear@?$_List_base@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAEXXZ"
    HASH_CLEAR = ("?clear@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@"
                  "rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$"
                  "allocator@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@@2@@_STL@@QAEXXZ")
    HASH_DELETE = ("?_M_delete_node@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$hash@W4Name"
                   "KeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@@2@U?$equal_to@W4NameKeyType"
                   "@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@@2@@_STL@@AAEXPAU?$_Hashtable_node@U?$p"
                   "air@$$CBW4NameKeyType@@VFXList@@@_STL@@@2@@Z")

    def test_a_template_member_never_moves_through_the_apply(self):
        # reviews of 3bc60f1272 and 0c8c510c89, each native case: none moves, whatever its spelling
        before = self.ledger()
        for name, text in (("?f@?$C@H@@QAEXXZ", "template<class T> struct C { void f(); }; "
                                                 "typedef C<int> Alias; void Alias::f() {}\n"),
                           ("?clear@?$list@H@_STL@@QAEXXZ", "namespace _STL { template<class T> struct list "
                                                             "{ __declspec(noinline) void clear() {} }; }\n"),
                           ("?clear@?$list@H@_STL@@QAEXXZ", '#line 1 "vendor/stlport/stl/_list.h"\n'
                                                             "void Alias::clear() {}\n")):
            with self.subTest(name=name, text=text):
                self.write(self.TU, text)
                rows = [self.row(name, "0x00002000"), self.row(self.STAY, "0x00003000")]
                report = self.move(rows=rows, rvas=["0x00002000"], dry_run=False, defined={name}, comdat={name},
                                   exact={"0x00002000"})
                self.assertEqual(report["blocked"], "a requested row cannot move by emission")
                self.assertIn("a template instance", report["refused_rows"]["0x00002000"])
                self.exact.assert_not_called()
                self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)

    def test_of_the_minimal_b_rows_only_the_deleting_dtor_moves_by_emission(self):
        # P16 minimal B: the ??_G rides (rule (b)); its STL list and hashtable rows stay where they are
        self.assertIsNone(T.emission_problem({"name": "??_GParticleSystemFXNugget@@UAEPAXI@Z"}))
        for name in (self.LIST_CLEAR, self.HASH_CLEAR, self.HASH_DELETE):
            with self.subTest(name=name):
                self.assertIn("a template instance", T.emission_problem({"name": name}))

    def test_no_text_is_read(self):
        # the fixture fails any cl -E: the files' text, readable or not, decides nothing
        self.write(self.TU, 'template<> void _Construct(Rec *, const Rec &) {} const char *s = "open;\n')
        report = self.move()
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])

    def test_a_row_bound_to_another_object_symbol_refuses(self):
        # review of 3db7ced4b4: the byte check would follow object-symbol=, the COMDAT checks the name
        rows = [self.row(self.VDTOR, "0x00002000", notes="object-symbol=_standin"), self.row(self.STAY, "0x00003000")]
        report = self.move(rows=rows, rvas=["0x00002000"])
        self.assertIn("object-symbol=", report["refused_rows"]["0x00002000"])

    def test_the_files_stand_in_copy_moves(self):
        # FamilyDeletingDtors' shape: the file hosts the row through a stand-in that compiles to a COMDAT
        self.write(self.SOURCE, "struct Rec { virtual ~Rec() {} int a; };\nvoid stay() { delete new Rec; }\n")
        report = self.move(file_defined={self.VDTOR, self.DTOR}, file_comdat={self.VDTOR, self.DTOR})
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])

    def test_a_strong_definition_in_the_file_refuses(self):
        report = self.move(rvas=["0x00002100"], file_defined={self.DTOR}, file_comdat=set())
        self.assertIn("the file defines it outside a COMDAT", report["refused_rows"]["0x00002100"])

    def test_a_destination_not_emitting_it_refuses(self):
        report = self.move(rvas=["0x00002000"], defined={self.DTOR})
        self.assertIn("does not emit it", report["refused_rows"]["0x00002000"])
        report = self.move(defined={self.DTOR})          # without --rva the rest still moves
        self.assertEqual(report["moved"], ["0x00002100"])

    def test_the_final_row_set_is_judged_again(self):
        # review of 3db7ced4b4: with 0x2000 refused, the TU's flags follow 0x2100 alone and lose it
        report = self.move(defined={self.DTOR}, final_lost={"0x00002100"})
        self.assertIn("re-judged with exactly the rows that move", report["blocked"])

    def test_a_byte_mismatch_refuses(self):
        report = self.move(rvas=["0x00002000"], exact={"0x00002100"})
        self.assertIn("not byte-exact", report["refused_rows"]["0x00002000"])
        self.assertIn("blocked", report)

    def test_a_strong_definition_in_the_tu_refuses(self):
        report = self.move(rvas=["0x00002100"], comdat={self.VDTOR})
        self.assertIn("outside a COMDAT", report["refused_rows"]["0x00002100"])

    def test_the_residual_keeping_its_matches_and_a_row_are_required(self):
        report = self.move(residual_lost=["0x00003000"])
        self.assertIn("remaining rows lose matches", report["blocked"])
        report = self.move(rows=[self.row(self.VDTOR, "0x00002000")], approved={"0x00002000": self.TU})
        self.assertIn("whole donor", report["blocked"])

    def test_a_missing_destination_refuses(self):
        (self.root / self.TU).unlink()
        self.assertIn("does not exist", self.move()["blocked"])

    def ledger(self):
        reverse = self.root / "reverse"
        reverse.mkdir(exist_ok=True)
        self.write("reverse/functions.csv",
                   "name,export_rva,target_rva,target_size,source,status,notes\n"
                   f"{self.VDTOR},,0x00002000,8,{self.SOURCE},matched,\n{self.DTOR},,0x00002100,8,{self.SOURCE},matched,\n"
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
        self.assertIn(f"{self.VDTOR},,0x00002000,8,{self.TU},matched", funcs)
        self.assertIn(f"{self.DTOR},,0x00002100,8,{self.SOURCE},matched", funcs)       # not requested: stays
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

    def test_an_exception_before_the_journal_gives_back_the_claims(self):
        # review of dee0813e84's question for every claim site: with no journal, undo_emit never runs
        before = self.ledger()
        with patch.object(T, "repoint_rows", side_effect=T.rename.Refusal("no such column")), self.assertRaises(T.rename.Refusal):
            self.move(rvas=["0x00002000"], dry_run=False, claim=True)
        key = T.claims.key_of(f"file:{self.TU}")
        self.released.assert_called_once_with([key], tokens={key: self.TOKEN})
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
        self.assertEqual(list((self.root / T.EMIT_JOURNAL).glob("*.json")), [])

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
        self.assertEqual(release.call_args[0][0], [T.claims.key_of("file:Code/Campaign.cpp")])

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
                 "M.T.map_regressions = lambda *a, **k: None\n"     # as setUpModule: no real map rebuild here
                 "t = M.EmitMoveTests('test_emitted_deleting_destructors_move')\n"
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


    def test_the_hand_written_copy_ctor_repros_are_refused_through_the_apply(self):
        # review of 9459886c66 (byte_repro.py): both bodies match the implicit ctor byte for byte
        before = self.ledger()
        rows = [self.row(self.VDTOR, "0x00002000"), self.row(self.COPY, "0x00002100"), self.row(self.STAY, "0x00003000")]
        for body in ("typedef Rec Alias; Alias(Rec const&r):a(r.a){}", "(Rec)(Rec const&r):a(r.a){}",
                     "Rec(Rec const (((&r)))):a(r.a){}", ""):
            with self.subTest(body=body):
                self.write(self.TU, "class Inner { public: Inner(Inner const&r):a(r.a){} int a; }; class Rec { public: "
                                    + body + " Inner a; }; Rec copy(Rec const&r){return Rec(r);}\n")
                report = self.move(rows=rows, rvas=["0x00002100"], dry_run=False,
                                   defined={self.VDTOR, self.COPY}, exact={"0x00002000", "0x00002100"})
                self.assertEqual(report["blocked"], "a requested row cannot move by emission")
                self.assertIn("not a deleting destructor", report["refused_rows"]["0x00002100"])
                self.exact.assert_not_called()
                self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)

    def test_a_partly_refused_claim_gives_back_exactly_what_it_acquired(self):
        # review of bfb856bfbf: a refusal dropped the fencing tokens and released every key with
        # tokens=None, a successor's claim and a key this worker already held among them
        self.ledger()
        tu_key, mixed_key, row_key = (T.claims.key_of(k) for k in (f"file:{self.TU}", f"file:{self.SOURCE}", "0x00002100"))
        # 0x2000 came back claimed with no token: it cannot be given back fenced, so it is left to expire
        result = T.claims.ClaimResult([tu_key, row_key, 0x2000], [mixed_key], tokens={tu_key: "MINE", row_key: "RENEWED"},
                                      prior=[row_key])
        with patch.object(T.claims, "claim", return_value=result):
            held = T.claim_scope(self.TU, {self.SOURCE: [self.row(self.DTOR, "0x00002100")]})
        self.assertTrue(held)
        self.assertEqual((list(held.acquired), held.tokens), ([tu_key], {tu_key: "MINE"}))
        self.claimed = lambda: held
        before = {rel: (self.root / rel).read_bytes() for rel in ("reverse/functions.csv", "reverse/tu_map.csv")}
        report = self.move(rvas=["0x00002100"], dry_run=False, claim=True)
        self.assertIn("held by another worker", report["blocked"])
        self.released.assert_called_once_with([tu_key], tokens={tu_key: "MINE"})
        self.exact.assert_not_called()                                    # aborted before touching anything
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
        self.assertEqual(list((self.root / T.EMIT_JOURNAL).glob("*.json")), [])
        with patch.object(T.claims, "owner", return_value="seat"), patch.object(T.claims, "_names", return_value={"seat"}):
            self.assertEqual(T.claims._eligible([f"file:{self.TU}"], tokens={tu_key: "MINE"},
                                                current={tu_key: ("SUCCESSOR", {"owner": "seat"})}), {})

    def test_a_move_journals_and_releases_only_the_keys_it_acquired(self):
        self.ledger()
        tu_key, row_key = T.claims.key_of(f"file:{self.TU}"), T.claims.key_of("0x00002000")
        held = T.Held()
        held.acquired, held.tokens = [tu_key], {tu_key: self.TOKEN}       # row_key was ours already
        self.claimed = lambda: held
        with self.assertRaises(KeyboardInterrupt):
            self.move(rvas=["0x00002000"], dry_run=False, build_effect=KeyboardInterrupt, claim=True)
        self.assertEqual(self.released.call_args[0][0], [tu_key])
        self.assertNotIn(T.key_text(row_key), self.released.call_args[0][0])

    def test_journal_keys_round_trip_as_the_claim_service_names_them(self):
        # review of 9459886c66 (rva_claim_repro.py): 0x2000 was journaled as "8192" and released as 0x8192
        self.ledger()
        tu_key = T.claims.key_of(f"file:{self.TU}")
        held = T.Held()
        held.acquired, held.tokens = [0x2000, tu_key], {0x2000: "TOKEN", tu_key: self.TOKEN}
        self.claimed = lambda: held
        seen = []
        real = T.write_emit_journal
        with patch.object(T, "write_emit_journal", side_effect=lambda record: seen.append(record) or real(record)), \
                self.assertRaises(KeyboardInterrupt):
            self.move(rvas=["0x00002000"], dry_run=False, build_effect=KeyboardInterrupt, claim=True)
        self.assertEqual(seen[0]["claims"], ["0x00002000", tu_key])
        self.assertEqual(seen[0]["tokens"], {"0x00002000": "TOKEN", tu_key: self.TOKEN})
        keys, tokens = self.released.call_args[0][0], self.released.call_args.kwargs["tokens"]
        self.assertEqual([T.claims.key_of(k) for k in keys], [0x2000, tu_key])
        self.assertEqual(tokens, {0x2000: "TOKEN", tu_key: self.TOKEN})
        for key in (0x2000, 0x8192, 0x0052BD3A, tu_key, "0x00002000"):
            self.assertEqual(T.claims.key_of(T.key_text(key)), T.claims.key_of(key))

    def test_recovery_retries_after_a_locked_object(self):
        # review of bfb856bfbf: the first recovery restored the rows but failed on a locked .obj;
        # the retry read the restored rows as "changed since the move"
        before = self.ledger()
        self.kill_mid_verify()
        funcs = self.root / "reverse/functions.csv"
        funcs.write_bytes(funcs.read_bytes().replace(b"?stay@@YAXXZ", b"?renamed@@YAXXZ"))
        locked, real_unlink = self.root / "build" / "real_t.obj", Path.unlink

        def unlink(path, *a, **k):
            if Path(path) == locked:
                raise PermissionError("locked")
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink):
            (restored, _busy, errors), _ = self.recover()
        self.assertEqual(restored, [])
        self.assertTrue(any("could not remove real_t.obj" in e for e in errors), errors)
        self.assertEqual(len(list((self.root / T.EMIT_JOURNAL).glob("*.json"))), 1)
        (restored, _busy, errors), _ = self.recover()                     # the lock gone: done
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual(funcs.read_bytes(), before["reverse/functions.csv"].replace(b"?stay@@YAXXZ", b"?renamed@@YAXXZ"))
        self.assertEqual(self.objects_left(), [])
        self.assertEqual(list((self.root / T.EMIT_JOURNAL).glob("*.json")), [])

    def test_undo_lines_is_idempotent_and_refuses_any_other_state(self):
        # per moved key: exactly its after-state rows go back, exactly its before-state rows are done,
        # anything else refuses (review of 9459886c66: both states present, or an edited row beside
        # an appended original, passed); the key is a number (review of 3bc60f1272)
        hdr = b"name,target_rva,target_size,source\n"
        before = hdr + b"a,0x1,8,X\nb,0x2,8,X\nc,0x3,8,X\n"
        after = hdr + b"a,0x1,8,X\nb,0x2,8,Y\nc,0x3,8,X\n"
        undo = lambda current: T.undo_lines(current, before, after, "target_rva")
        self.assertEqual(undo(after), before)
        self.assertEqual(undo(before), before)                                         # already back: done
        self.assertEqual(undo(hdr + b"z,0x1,8,X\nb,0x2,8,Y\nc,0x3,8,X\n"), hdr + b"z,0x1,8,X\nb,0x2,8,X\nc,0x3,8,X\n")
        self.assertEqual(undo(hdr + b"b,0x2,8,Y\nc,0x3,8,X\nn,0x9,8,X\n"), hdr + b"b,0x2,8,X\nc,0x3,8,X\nn,0x9,8,X\n")
        self.assertEqual(undo(hdr + b"a,0x0001,8,X\nb,0x2,8,Y\nc,0x3,8,X\n"),          # another row respelled: kept
                         hdr + b"a,0x0001,8,X\nb,0x2,8,X\nc,0x3,8,X\n")
        for third in (b"a,0x1,8,X\nb,0x2,8,Z\nc,0x3,8,X\n",                     # edited since
                      b"a,0x1,8,X\nc,0x3,8,X\n",                                # gone
                      b"a,0x1,8,X\nb,0x2,8,Y\nb,0x2,8,Y\nc,0x3,8,X\n",          # after-state twice
                      b"a,0x1,8,X\nb,0x2,8,X\nb,0x2,8,X\nc,0x3,8,X\n",          # before-state twice
                      b"a,0x1,8,X\nb,0x2,8,X\nb,0x2,8,Y\nc,0x3,8,X\n",          # both states
                      b"a,0x1,8,X\nb,0x2,9,Y\nc,0x3,8,X\nb,0x2,8,X\n",          # an edited extent beside the original
                      b"a,0x1,8,X\nb,0x2,8,X\nc,0x3,8,X\nb2,0x2,8,Q\n",         # another row at the moved key
                      b"a,0x1,8,X\nb,0x00000002,9,Y\nc,0x3,8,X\nb,0x2,8,X\n",   # the same, the key respelled
                      b"a,0x1,8,X\nb,0x2,8,X\nc,0x3,8,X\nb,0X02,8,Y\n",         # both states, the key respelled
                      b"a,0x1,8,X\nb,0x00000002,8,X\nc,0x3,8,X\n",              # the before-state, respelled
                      b"a,0x1,8,X\nb,0x2,8,Y\nc,0x3,8,X\nq,0xZZ,8,X\n"):        # an RVA no number reads
            with self.subTest(third=third):
                self.assertIsNone(undo(hdr + third))
        self.assertIsNone(T.undo_lines(after, before, after, "rva"))                  # no such key column
        twins_before, twins_after = hdr + b"b,0x2,8,X\nb,0x2,8,Y\n", hdr + b"b,0x2,8,Y\nb,0x2,8,Y\n"
        self.assertIsNone(T.undo_lines(twins_after, twins_before, twins_after, "target_rva"))   # which goes back?

    def test_recovery_refuses_a_respelled_rva_beside_the_original(self):
        # review of 3bc60f1272 (r7_probes.py): an edited row spelled `0x2000` beside the original `0x00002000`
        before = self.ledger()
        self.kill_mid_verify()
        funcs = self.root / "reverse/functions.csv"
        old = next(line for line in before["reverse/functions.csv"].splitlines() if b"0x00002000" in line)
        crafted = funcs.read_bytes().replace(b"0x00002000,8,", b"0x2000,9,") + old + b"\n"
        funcs.write_bytes(crafted)
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual(restored, [])
        self.assertTrue(any("changed since the move" in e for e in errors), errors)
        self.assertEqual(funcs.read_bytes(), crafted)
        self.assertEqual(len(list((self.root / T.EMIT_JOURNAL).glob("*.json"))), 1)

    def test_recovery_refuses_an_edited_row_beside_its_original(self):
        # review of 9459886c66 (recovery_extra.py)
        before = self.ledger()
        self.kill_mid_verify()
        funcs = self.root / "reverse/functions.csv"
        old = next(line for line in before["reverse/functions.csv"].splitlines() if b"0x00002000" in line)
        crafted = funcs.read_bytes().replace(b"0x00002000,8,", b"0x00002000,9,") + old + b"\n"
        funcs.write_bytes(crafted)
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual(restored, [])
        self.assertTrue(any("changed since the move" in e for e in errors), errors)
        self.assertEqual(funcs.read_bytes(), crafted)
        self.assertEqual(len(list((self.root / T.EMIT_JOURNAL).glob("*.json"))), 1)

    def test_an_interrupt_after_staging_an_untracked_ledger_unstages_it(self):
        # review of e2e59872d8: with no commit the ledger was untracked; `git rm --cached` refused
        # once the working file was restored, leaving the moved rows staged
        before = self.ledger()
        real_unlink = Path.unlink

        def unlink(path, *a, **k):
            if Path(path).suffix == ".json" and Path(path).parent.name == "emit-journal":
                raise KeyboardInterrupt
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink), self.assertRaises(KeyboardInterrupt):
            self.move(rvas=["0x00002000"], dry_run=False)
        listed = lambda: subprocess.run(["git", "ls-files", "-s", "--", "reverse"], cwd=self.root,
                                        capture_output=True, text=True, check=True).stdout
        self.assertIn("reverse/functions.csv", listed())                   # the move was staged
        (restored, _busy, errors), _ = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual(listed(), "")
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)

    SPOOF = 'extern "C" void __identifier("??_GRec@@UAEPAXI@Z")() {}\n'

    def test_a_hand_written_deleting_dtor_never_moves(self):
        # review of 87417c8f9f: `extern "C" void __identifier("??_GRec@@UAEPAXI@Z")() {}` compiles to a
        # COMDAT of exactly that name; a definition through `__identifier` in either unit refuses
        refused = (self.SPOOF,
                   'extern "C" inline void __identifier("??_GRec@@UAEPAXI@Z")() {}\n',
                   'void *__identifier("??_GRec@@UAEPAXI@Z")(unsigned int f) throw() { return 0; }\n',
                   'extern "C" void __identifier("??_G" "Rec@@UAEPAXI@Z")() {}\n',          # adjacent literals
                   'extern "C" void __identifier("\\x3f?_GRec@@UAEPAXI@Z")() {}\n',          # an escape
                   'extern "C" void __identifier(L"??_GRec@@UAEPAXI@Z")() {}\n',             # a prefix
                   'extern "C" void __identifier("??_GRec@@UAEPAXI@Z"() {}\n',               # unbalanced
                   # review of f458166062: a parenthesized declarator
                   'extern "C" inline void\n(__identifier("??_GRec@@UAEPAXI@Z"))() {}\n',
                   'extern "C" inline void ((__identifier("??_GRec@@UAEPAXI@Z")))() {}\n',
                   'extern "C" __declspec(naked) inline void (__identifier("??_GRec@@UAEPAXI@Z"))() { }\n',
                   # review of f11be8ac37: a bracket inside a default argument's literal
                   'extern "C" inline void __identifier("??_GRec@@UAEPAXI@Z")(const char *p = ")") {}\n',
                   "extern \"C\" inline void __identifier(\"??_GRec@@UAEPAXI@Z\")(char p = ')') {}\n",
                   # review of 329404caeb: `??/` is a backslash, so `"??/""` holds a quote
                   'const char *s="??/""; extern "C" __declspec(dllexport) inline void '
                   '__identifier("??_GRec@@UAEPAXI@Z")() {} const char *t="??/"";\n')
        for text in refused:
            for unit in (self.TU, self.SOURCE):
                with self.subTest(text=text, unit=unit):
                    self.write(unit, text + "struct Rec { int a; };\nvoid stay() {}\n")
                    report = self.move(rvas=["0x00002100"])
                    self.assertIn("may define it by hand", report["refused_rows"]["0x00002100"])
                    self.setUp()
        passed = ('extern "C" void __identifier("??_GRec@@UAEPAXI@Z")();\n',                   # a declaration
                  'extern "C" void __identifier("??_GRec@@UAEPAXI@Z")();\n'
                  'void (*p)() = &__identifier("??_GRec@@UAEPAXI@Z");\n',                      # its address
                  'extern "C" void __identifier("??_GRec@@UAEPAXI@Z")();\n'
                  'void g() { __identifier("??_GRec@@UAEPAXI@Z")(); }\n',                      # a call
                  'extern "C" void (__identifier("??_GRec@@UAEPAXI@Z"))();\n'                  # parenthesized
                  'const void *q = (const void *)&(__identifier("??_GRec@@UAEPAXI@Z"));\n',
                  'extern "C" void __identifier("??_GOther@@UAEPAXI@Z")() {}\n')               # another name
        for text in passed:
            with self.subTest(text=text):
                self.write(self.TU, text + "struct Rec { int a; };\n")
                report = self.move(rvas=["0x00002100"])
                self.assertNotIn("blocked", report)
                self.assertEqual(report["moved"], ["0x00002100"])
        report = self.move(rvas=["0x00002100"], pp_fail={self.SOURCE})
        self.assertIn("cannot be preprocessed", report["refused_rows"]["0x00002100"])

    def test_a_copy_the_compiler_did_not_select_any_never_moves(self):
        # the scratch objects of either unit, then the committed ones after ./build.sh
        for obj in ("t.obj", "x.obj"):
            with self.subTest(obj=obj):
                report = self.move(rvas=["0x00002100"], copies={obj: "selects its COMDAT NODUPLICATES"})
                self.assertIn("NODUPLICATES", report["refused_rows"]["0x00002100"])
        for obj in ("real_t.obj", "real_x.obj"):
            with self.subTest(obj=obj):
                before = self.ledger()
                report = self.move(rvas=["0x00002100"], dry_run=False, copies={obj: "selects its COMDAT NODUPLICATES"})
                self.assertIn("0x00002100: selects its COMDAT NODUPLICATES", report["blocked"])
                self.assertIn("the ledger was put back", report["blocked"])
                self.assertEqual({rel: (self.root / rel).read_bytes() for rel in before}, before)
                self.setUp()

    def test_identifier_definition_admits_only_the_allowed_shapes(self):
        # review of f11be8ac37: a positive allowlist on the masked text; after any `)`, only `;`, `,`, `}`,
        # `()`/`(void)` then `;`/`,`, or `[]` then `;`/`,`/`=`
        n = "??_GRec@@UAEPAXI@Z"
        admitted = ['void __identifier("{n}")();', 'void __identifier("{n}")(void);', 'void __identifier("{n}")(),',
                    'void (__identifier("{n}"))();', '(const void *)&__identifier("{n}"),', '(const void *)&(__identifier("{n}")),',
                    'reinterpret_cast<const void *>(__identifier("{n}")),', 'f(&__identifier("{n}"));',
                    'const void *t[] = {{ &__identifier("{n}") }};', 'extern "C" const void *__identifier("{n}")[];',
                    'extern "C" const void *__identifier("{n}")[] = {{0}};', 'void g() {{ __identifier("{n}")(); }}',
                    'void __identifier("{n}")\n#line 3 "x.h"\n();', 'void __identifier("{n}") /* a ) */ ();',
                    'void __identifier("??_GOther@@UAEPAXI@Z")(const char *p = ")") {{}}',     # another name
                    'void f() {{}}', 'const char *s = "__identifier(\\"{n}\\")() {{}}";',      # inside a literal
                    # review of 329404caeb: trigraphs read as the compiler reads them
                    'const char *s="??/""; void __identifier("{n}")(); const char *t="??/"";',
                    'extern "C" const void *__identifier("{n}")??(??);',                       # `[]`
                    'const char *s = "a??/"__identifier(\\"{n}\\")() {{}}";',                  # still inside it
                    'void __identifier("{n}")(); const char *s = "??/\n";']                    # a spliced literal
        refused = ['void __identifier("{n}")() {{}}', 'void __identifier("{n}")(void) {{}}',
                   'extern "C" inline void __identifier("{n}")(const char *p = ")") {{}}',     # the review's default
                   "extern \"C\" inline void __identifier(\"{n}\")(char p = ')') {{}}",
                   'void __identifier("{n}")(int);', 'void __identifier("{n}")() throw();',
                   'void __identifier("{n}")() const;', 'int __identifier("{n}") = 1;', 'int __identifier("{n}")[2];',
                   'void (__identifier("{n}"))() {{}}', 'void ((__identifier("{n}")))() {{}}',
                   'void __identifier("{n}")()\n#line 3 "x.h"\n{{}}', 'void __identifier("{n}")() try {{ }} catch (...) {{ }}',
                   'int x = __identifier("{n}")() + 1;', 'void f() {{ if (__identifier("{n}")()) {{ }} }}',
                   'void __identifier("{n}")()', 'void __identifier("{n}")(', 'void __identifier("{n}"',
                   'void __identifier("??_G" "Rec@@UAEPAXI@Z")();' + ' void __identifier("??_G" "Rec@@UAEPAXI@Z")() {{}}',
                   'void __identifier("\\x3f?_GRec@@UAEPAXI@Z")() {{}}', 'void __identifier(L"{n}")() {{}}',
                   'void __identifier("{n}")(); const char *s = "open;',                       # unterminated
                   'void __identifier("{n}")(); /* open',
                   # review of 329404caeb: `"??/""` holds a quote; the definition between two of them is code
                   'const char *s="??/""; extern "C" __declspec(dllexport) inline void __identifier("{n}")() {{}} '
                   'const char *t="??/"";',
                   'void __identifier("{n}")() ??< ??>', 'void __identifier("{n}")??(2??);',
                   'void __identi\\\nfier("{n}")() {{}}']                                      # a spliced name
        for code in admitted + refused:
            with self.subTest(code=code):
                self.assertEqual(bool(T.identifier_definition(code.format(n=n), n)), code in refused)

    def test_mask_code_keeps_every_index_and_blanks_what_could_read_as_code(self):
        text = 'f("a)b", \'(\', "x\\"y");\n#line 1 "c:\\\\a(b.h"\n/* ( */ g(); // )\n'
        masked = T.mask_code(text)
        self.assertEqual(len(masked), len(text))
        self.assertEqual(masked.count("("), 2)
        self.assertEqual(masked.count(")"), 2)
        self.assertIn('f("xxx", \'x\', "xxxx");', masked)
        self.assertIsNone(T.mask_code('f("open);\n'))
        self.assertIsNone(T.mask_code('f("open);\ng(");\n'))            # a quote on a later line closes nothing
        self.assertIsNone(T.mask_code("f(); /* open"))
        self.assertIsNone(T.mask_code("char c = 'x;\n"))

    def test_translation_phases_read_trigraphs_and_splices_as_the_compiler_does(self):
        # review of 329404caeb: cl -E leaves trigraphs; decorated names are none
        for tri, char in (("??=", "#"), ("??/", "\\"), ("??'", "^"), ("??(", "["), ("??)", "]"), ("??!", "|"),
                          ("??<", "{"), ("??>", "}"), ("??-", "~")):
            with self.subTest(tri=tri):
                self.assertEqual(T.translation_phases(f"a{tri}b"), f"a{char}b")
        for name in ("??_GRec@@UAEPAXI@Z", "??_ERec@@UAEPAXI@Z", "??4Rec@@QAEAAV0@ABV0@@Z", "??0Rec@@QAE@XZ",
                     "??1Rec@@UAE@XZ", "??$f@H@@YAXXZ", "??RBox@@QBEHXZ", "??B?$C@H@@QAEHXZ", "??_7Rec@@6B@",
                     "??_R0?AVRec@@@8", "???"):
            with self.subTest(name=name):
                self.assertEqual(T.translation_phases(name), name)
        self.assertEqual(T.translation_phases("???/"), "?\\")                 # the leftmost trigraph
        self.assertEqual(T.translation_phases('"??/""'), '"\\""')
        self.assertEqual(T.translation_phases("a\\\nb\\\r\nc??/\nd"), "abcd")   # splices, one made by `??/`


class EmitTransactionTests(unittest.TestCase):
    """--emit-move over several files and prepared texts as one transaction (P16 v2: G7, G8, G5). A unit's
    text says what its object defines: `//comdat NAME`, `//strong NAME`; `//wrong NAME` emits it, not
    byte-exact; `//nocompile` fails; `//noduplicates NAME` is a COMDAT not selected ANY. Scratch objects, the
    real objects and the build all read the text being judged."""
    TU, A, B, OTHER = "Code/Campaign.cpp", "Code/Mixed.cpp", "Code/Second.cpp", "Code/Elsewhere.cpp"
    GA, EB, GB = "??_GA@@UAEPAXI@Z", "??_EB@@UAEPAXI@Z", "??_GB@@UAEPAXI@Z"
    STAY_A, STAY_B, OWN = "?stayA@@YAXXZ", "?stayB@@YAXXZ", "?own@@YAXXZ"

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        self.write(self.A, f"//comdat {self.GA}\n//comdat {self.STAY_A}\n")
        self.write(self.B, f"//comdat {self.EB}\n//comdat {self.STAY_B}\n")
        self.write(self.TU, f"//comdat {self.OWN}\n//comdat {self.GA}\n//comdat {self.EB}\n")
        self.rows = {self.A: [self.row(self.GA, "0x00002000", self.A), self.row(self.STAY_A, "0x00003000", self.A)],
                     self.B: [self.row(self.EB, "0x00002100", self.B), self.row(self.STAY_B, "0x00003100", self.B)],
                     self.TU: [self.row(self.OWN, "0x00001000", self.TU)]}
        self.approved = {"0x00002000": self.TU, "0x00002100": self.TU, "0x00003000": self.OTHER, "0x00003100": self.OTHER}
        self.confidence = {}
        self.ledger()

    def write(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))

    def read(self, rel):
        return (self.root / rel).read_bytes().decode("utf-8")

    @staticmethod
    def row(name, rva, source):
        return {"name": name, "export_rva": "", "target_rva": rva, "target_size": "8", "source": source,
                "status": "matched", "notes": ""}

    def ledger(self):
        lines = "".join(f"{r['name']},,{r['target_rva']},8,{r['source']},matched,\n" for rows in self.rows.values() for r in rows)
        self.write("reverse/functions.csv", "name,export_rva,target_rva,target_size,source,status,notes\n" + lines)
        self.write("reverse/tu_map.csv", "rva,size,kind,tu,confidence,by,evidence,source\n"
                   + "".join(f"{r['target_rva']},8,code,{self.approved.get(r['target_rva'], self.TU)},approved,C,C=0x1..0x3,{r['source']}\n"
                             for rows in self.rows.values() for r in rows))
        subprocess.run(["git", "init", "-q", str(self.root)], check=True)
        self.base = {rel: (self.root / rel).read_bytes() for rel in ("reverse/functions.csv", "reverse/tu_map.csv", self.A, self.B, self.TU)}

    def unchanged(self):
        self.assertEqual({rel: (self.root / rel).read_bytes() for rel in self.base}, self.base)

    @staticmethod
    def names(text, *kinds):
        return {line.split(" ", 1)[1].strip() for line in text.splitlines()
                if line.split(" ", 1)[0] in {f"//{k}" for k in kinds} and " " in line}

    RETAIL = "c3"

    @classmethod
    def emitted(cls, text, name):
        """The byte the unit emits for `name`: retail's, unless a `//byte NAME xx` line says otherwise."""
        for line in text.splitlines():
            parts = line.split()
            if len(parts) == 3 and parts[0] == "//byte" and parts[1] == name:
                return parts[2]
        return cls.RETAIL

    def definitions(self, obj):
        """coff_definitions as the unit's text says: None when the object is gone or `//garbage`."""
        try:
            text = Path(obj).read_text(encoding="utf-8")
        except (OSError, TypeError):
            return None
        if "//garbage" in text:
            return None
        out = {n: (True, True, 2) for n in self.names(text, "comdat")}
        out.update({n: (True, True, 1) for n in self.names(text, "noduplicates")})
        out.update({n: (False, True, None) for n in self.names(text, "strong")})
        out.update({n: (True, False, 2) for n in self.names(text, "data")})
        out.update({n: (False, False, None) for n in self.names(text, "weak")})
        return out

    def identity(self, obj, name):
        """section_identity as the unit's text says: the unit's `//reloc NAME TARGET` lines; None when the
        object is gone or `//garbage`, the unit defines no such row, or it says `//incomparable NAME`."""
        try:
            text = Path(obj).read_text(encoding="utf-8")
        except (OSError, TypeError):
            return None
        if "//garbage" in text or f"//incomparable {name}" in text or name not in self.names(text, "comdat", "strong", "noduplicates", "data"):
            return None
        return tuple(line for line in text.splitlines() if line.startswith(f"//reloc {name} "))

    def transact(self, files=None, *, rvas=None, prepared=None, dry_run=True, claim=False, build_effect=None, undo=None,
                 definitions=None):
        """emit_move over `files` (default both donors) in the fixture's tree."""
        files = files if files is not None else [self.A, self.B]
        root, this = self.root, self
        (root / "build").mkdir(exist_ok=True)

        class Verifier:
            errors, all_errors = [], []

            def __init__(self, tu):
                self.tu, self.obj = tu, None

            def matched(self, text, judged):
                digest = hashlib.sha1((self.tu + text).encode()).hexdigest()[:10]
                self.obj = root / "build" / f"scratch-{digest}.obj"
                self.obj.write_text(text, encoding="utf-8")
                if "//nocompile" in text:
                    self.errors = self.all_errors = ["u.cpp(1) : error C2065: undeclared"]
                    return None
                self.errors = self.all_errors = []
                good = this.names(text, "comdat", "strong", "noduplicates", "data") - this.names(text, "wrong")
                return {r["target_rva"] for r in judged if r["name"] in good and this.emitted(text, r["name"]) == this.RETAIL}

            def preprocessed(self, text, judged):
                return (None, "cl -E failed") if "//nopp" in text else (text, None)

        real = {f: root / "build" / f"real-{Path(f).stem}.obj" for f in [self.TU, self.A, self.B]}

        def built(sources):
            """./build.sh's stand-in: every ledger row at these sources must be defined by its text as it stands."""
            for source in sources:
                text = (root / source).read_text(encoding="utf-8")
                real[source].write_text(text, encoding="utf-8")
                import build
                build._deps_sidecar(real[source]).write_text("{}")
                if "//nocompile" in text:
                    return False, "boom"
            for line in (root / "reverse/functions.csv").read_text().splitlines()[1:]:
                name, _, _, _, source, *_ = line.split(",")
                if source in sources and name not in this.names((root / source).read_text(encoding="utf-8"), "comdat", "strong", "noduplicates"):
                    return False, f"{name} is not in {source}"
            return True, "Functions: OK"

        def text_of(obj):
            try:
                return Path(obj).read_text(encoding="utf-8")
            except OSError:             # as defined_symbols and comdat_symbols read a missing object
                return ""

        groups = lambda f: {t: [r for r in self.rows[f] if self.approved.get(r["target_rva"], "") == t]
                            for t in {self.approved.get(r["target_rva"], "") for r in self.rows[f]}}
        import build
        extra = [patch.object(T, "undo_emit", side_effect=undo)] if undo else []
        with patch.object(T, "ROOT", root), patch.dict(T._CACHE, {}, clear=True), \
                patch.object(T, "file_rows", side_effect=lambda p: self.rows.get(p, [])), \
                patch.object(T, "breakdown", side_effect=groups), patch.object(T, "fold_alias", return_value=False), \
                patch.object(T, "identity_debt", return_value=False), patch.object(T, "Verifier", Verifier), \
                patch.object(T, "defined_symbols", side_effect=lambda obj: this.names(text_of(obj), "comdat", "strong", "noduplicates", "data")), \
                patch.object(T, "comdat_symbols", side_effect=lambda obj: this.names(text_of(obj), "comdat", "noduplicates", "data")), \
                patch.object(T, "coff_definitions", side_effect=definitions or self.definitions), \
                patch.object(T, "section_identity", side_effect=self.identity), \
                patch.object(T, "map_rows", side_effect=self.map_of), \
                patch.object(T, "deleting_copy_problem", side_effect=lambda obj, name: "selects its COMDAT NODUPLICATES"
                             if name in this.names(text_of(obj), "noduplicates") else None), \
                patch.object(T, "exact_build", side_effect=build_effect or built) as self.exact, \
                patch.object(T, "claim_scope", side_effect=self.held) as self.claimed_scope, \
                patch.object(T.claims, "release") as self.released, \
                patch.object(build, "obj_path", side_effect=lambda s: real[Path(s).relative_to(root).as_posix()]):
            for p in extra:
                p.start()
            try:
                return T.emit_move(files if len(files) > 1 else files[0], self.TU, rvas, dry_run=dry_run, claim=claim,
                                   prepared=prepared)
            finally:
                for p in extra:
                    p.stop()

    def map_of(self):
        return [{"rva": r["target_rva"], "kind": "code", "tu": self.approved.get(r["target_rva"], self.TU),
                 "confidence": self.confidence.get(r["target_rva"], "approved")}
                for rows in self.rows.values() for r in rows]

    def held(self, *a, **k):
        held = T.Held()
        held.acquired = [T.claims.key_of(f"file:{self.TU}")]
        held.tokens = {held.acquired[0]: "TOKEN"}
        return held

    def recover(self):
        import build
        real = {f: self.root / "build" / f"real-{Path(f).stem}.obj" for f in [self.TU, self.A, self.B]}
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, {}, clear=True), \
                patch.object(build, "obj_path", side_effect=lambda s: real[Path(s).relative_to(self.root).as_posix()]), \
                patch.object(T.claims, "release"):
            return T.recover_emit()

    def journals(self):
        return list((self.root / T.EMIT_JOURNAL).glob("*.json"))

    def test_two_files_move_as_one_transaction(self):
        report = self.transact()
        self.assertNotIn("blocked", report)
        self.assertEqual(report["files"], [self.A, self.B])
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])
        self.unchanged()
        report = self.transact(dry_run=False)
        self.assertNotIn("blocked", report)
        self.exact.assert_called_once_with([self.A, self.B, self.TU])            # one build over exactly these
        funcs = self.read("reverse/functions.csv")
        self.assertIn(f"{self.GA},,0x00002000,8,{self.TU},", funcs)
        self.assertIn(f"{self.EB},,0x00002100,8,{self.TU},", funcs)
        self.assertIn(f"{self.STAY_A},,0x00003000,8,{self.A},", funcs)
        self.assertIn(f"{self.STAY_B},,0x00003100,8,{self.B},", funcs)
        self.assertEqual(self.journals(), [])
        self.assertIn("2 files", report["subject"])
        staged = subprocess.run(["git", "ls-files", "--", "reverse"], cwd=self.root, capture_output=True, text=True).stdout
        self.assertIn("reverse/functions.csv", staged)

    def test_a_subset_of_each_mixed_file_moves_and_the_rest_stays(self):
        # G8: each file's other rows, placed elsewhere or not requested, stay
        self.rows[self.A].append(self.row(self.GB, "0x00002200", self.A))
        self.approved["0x00002200"] = self.TU
        self.write(self.A, self.read(self.A) + f"//comdat {self.GB}\n")
        self.write(self.TU, self.read(self.TU) + f"//comdat {self.GB}\n")
        self.ledger()
        report = self.transact(rvas=["0x00002000", "0x00002100"], dry_run=False)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])
        funcs = self.read("reverse/functions.csv")
        self.assertIn(f"{self.GB},,0x00002200,8,{self.A},", funcs)               # requested no: stays
        self.assertIn(f"{self.STAY_A},,0x00003000,8,{self.A},", funcs)           # placed elsewhere: stays

    def test_every_listed_file_must_contribute_a_requested_row(self):
        report = self.transact(rvas=["0x00002000"])
        self.assertIn(f"no row of {self.B} is approved", report["blocked"])
        self.assertIn("among those requested", report["blocked"])
        self.assertIn("not approved", self.transact(rvas=["0x00002000", "0x00003100"])["blocked"])
        self.assertIn("not a matched row", self.transact(rvas=["0x00009000"])["blocked"])
        self.approved["0x00002100"] = self.OTHER
        self.assertIn(f"no row of {self.B} is approved", self.transact()["blocked"])

    def test_one_files_failure_blocks_the_requested_transaction(self):
        self.write(self.TU, f"//comdat {self.OWN}\n//comdat {self.GA}\n//wrong {self.EB}\n//comdat {self.EB}\n")
        report = self.transact(rvas=["0x00002000", "0x00002100"], dry_run=False)
        self.assertEqual(report["blocked"], "a requested row cannot move by emission")
        self.assertIn("not byte-exact", report["refused_rows"]["0x00002100"])
        self.exact.assert_not_called()
        self.assertIn(f"{self.GA},,0x00002000,8,{self.A},", self.read("reverse/functions.csv"))
        report = self.transact()                                                  # without --rva the rest still moves
        self.assertEqual(report["moved"], ["0x00002000"])

    def test_each_files_problems_name_it(self):
        self.write(self.B, f"//nocompile\n//comdat {self.EB}\n//comdat {self.STAY_B}\n")
        self.assertIn(f"{self.B} does not compile", self.transact()["blocked"])
        self.setUp()
        self.write(self.B, f"//strong {self.EB}\n//comdat {self.STAY_B}\n")
        report = self.transact(rvas=["0x00002000", "0x00002100"])
        self.assertIn(f"{self.B} defines it outside a COMDAT", report["refused_rows"]["0x00002100"])
        self.setUp()
        del self.rows[self.B][1]                                                   # a whole donor
        report = self.transact()
        self.assertIn(f"no row would remain in {self.B}", report["blocked"])
        self.setUp()
        self.rows[self.B].append(self.row(self.GB, "0x00002000", self.B))          # two rows at one address
        self.approved["0x00002000"] = self.TU
        report = self.transact()
        self.assertIn("shares its address", report["refused_rows"]["0x00002000"])

    def test_a_move_that_costs_the_map_an_approval_is_refused(self):
        # moving rows shifts N hints as a partial split does (review of dee0813e84)
        for dry_run in (True, False):
            with self.subTest(dry_run=dry_run), patch.object(T, "map_regressions", return_value="lost approval") as check:
                report = self.transact(dry_run=dry_run)
                self.assertEqual(report["blocked"], "lost approval")
                check.assert_called_once_with(self.TU, moved_rows={self.A: ["0x00002000"], self.B: ["0x00002100"]})
                self.exact.assert_not_called()
                self.unchanged()

    def test_the_claim_covers_every_file_and_a_refusal_touches_nothing(self):
        report = self.transact(dry_run=False, claim=True)
        self.assertNotIn("blocked", report)
        scope = self.claimed_scope.call_args[0][1]
        self.assertEqual(sorted(scope), [self.A, self.B])
        self.setUp()
        refused = T.Held(["file:" + self.B])
        refused.acquired, refused.tokens = ["k"], {"k": "T"}
        self.held = lambda *a, **k: refused
        report = self.transact(dry_run=False, claim=True)
        self.assertIn("held by another worker", report["blocked"])
        self.released.assert_called_once_with(["k"], tokens={"k": "T"})
        self.unchanged()

    # ------------------------------------------------------------------ prepared texts (G5)
    def stand_in_removed(self):
        """The P16 shape: the TU emits nothing yet, each donor hosts a stand-in; the prepared texts swap them."""
        self.write(self.TU, f"//comdat {self.OWN}\n")
        self.ledger()
        return {self.TU: f"//comdat {self.OWN}\n//comdat {self.GA}\n//comdat {self.EB}\n",
                self.A: f"//comdat {self.STAY_A}\n", self.B: f"//comdat {self.STAY_B}\n"}

    def test_prepared_texts_land_with_the_rows(self):
        prepared = self.stand_in_removed()
        self.assertIn("does not emit it", self.transact(rvas=["0x00002000", "0x00002100"])["refused_rows"]["0x00002000"])
        report = self.transact(prepared=prepared)
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])
        self.unchanged()                                                           # a dry run writes nothing
        report = self.transact(prepared=prepared, dry_run=False)
        self.assertNotIn("blocked", report)
        for rel, text in prepared.items():
            self.assertEqual(self.read(rel), text)
        self.assertIn("prepared texts", report["subject"])
        staged = subprocess.run(["git", "ls-files", "--", "Code"], cwd=self.root, capture_output=True, text=True).stdout
        self.assertEqual(sorted(staged.split()), sorted(prepared))
        self.assertEqual(self.journals(), [])

    def test_only_the_tu_and_the_listed_files_may_be_prepared(self):
        report = self.transact(prepared={self.OTHER: "x"})
        self.assertIn("may only replace the TU or a listed file: " + self.OTHER, report["blocked"])
        self.unchanged()
        prepared = self.stand_in_removed()
        prepared = {self.TU.upper(): prepared[self.TU], self.A: prepared[self.A], self.B: prepared[self.B]}
        report = self.transact(prepared=prepared)                                  # the --for spelling names the TU
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], ["0x00002000", "0x00002100"])

    def test_a_prepared_text_cannot_stand_in_for_a_baseline(self):
        # what a unit matches today is the baseline: one that does not compile now has none to keep
        prepared = self.stand_in_removed()
        self.write(self.B, "//nocompile\n" + self.read(self.B))
        self.assertIn(f"{self.B} does not compile", self.transact(prepared=prepared)["blocked"])
        self.setUp()
        prepared = self.stand_in_removed()
        self.write(self.TU, "//nocompile\n" + self.read(self.TU))
        self.assertIn("the TU does not compile", self.transact(prepared=prepared)["blocked"])

    def test_a_strong_definition_only_a_prepared_file_has_refuses(self):
        prepared = self.stand_in_removed()
        prepared[self.B] = f"//strong {self.EB}\n" + prepared[self.B]
        report = self.transact(rvas=["0x00002000", "0x00002100"], prepared=prepared)
        self.assertIn(f"{self.B} defines it outside a COMDAT", report["refused_rows"]["0x00002100"])

    def test_a_prepared_text_is_judged_as_given(self):
        for rel, change, why in ((self.TU, f"//comdat {self.GA}\n//comdat {self.EB}\n", "lose matches"),      # loses ?own
                                 (self.A, "", "remaining rows lose matches"),                                   # loses stay
                                 (self.A, "//nocompile\n", "does not compile"),
                                 (self.TU, "//nocompile\n", "does not compile")):
            with self.subTest(rel=rel, change=change):
                self.setUp()
                prepared = self.stand_in_removed()
                prepared[rel] = change
                before = {r: (self.root / r).read_bytes() for r in self.base}
                report = self.transact(prepared=prepared, dry_run=False)
                self.assertIn(why, report["blocked"])
                self.exact.assert_not_called()
                self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)

    def test_a_prepared_text_cannot_hide_a_hand_written_row(self):
        spoof = f'extern "C" inline void __identifier("{self.GA}")() {{}}\n'
        for rel in (self.TU, self.A):
            with self.subTest(rel=rel):
                self.setUp()
                prepared = self.stand_in_removed()
                prepared[rel] = spoof + prepared[rel]
                report = self.transact(rvas=["0x00002000", "0x00002100"], prepared=prepared)
                self.assertIn("may define it by hand", report["refused_rows"]["0x00002000"])
        for rel, why in ((self.TU, "NODUPLICATES"), (self.A, "NODUPLICATES")):
            with self.subTest(rel=rel, why=why):
                self.setUp()
                prepared = self.stand_in_removed()
                prepared[rel] = prepared[rel] + f"//noduplicates {self.GA}\n"
                report = self.transact(rvas=["0x00002000", "0x00002100"], prepared=prepared)
                self.assertIn(why, report["refused_rows"]["0x00002000"])
        self.setUp()
        prepared = self.stand_in_removed()
        prepared[self.B] = "//nopp\n" + prepared[self.B]
        report = self.transact(rvas=["0x00002000", "0x00002100"], prepared=prepared)
        self.assertIn("cannot be preprocessed", report["refused_rows"]["0x00002000"])

    def test_a_prepared_text_may_not_lose_a_strong_symbol_and_reports_a_dropped_comdat(self):
        self.write(self.A, self.read(self.A) + "//strong _helper\n//comdat _inlined\n")
        self.ledger()
        prepared = self.stand_in_removed()
        report = self.transact(prepared=prepared)
        self.assertIn("stops defining what no object of this move defines: _helper", report["blocked"])
        prepared[self.TU] += "//strong _helper\n"                                  # now the TU defines it
        report = self.transact(prepared=prepared)
        self.assertNotIn("blocked", report)
        self.assertEqual(report["comdats_dropped"], ["_inlined"])
        prepared[self.TU] = prepared[self.TU].replace("//strong _helper\n", "")
        prepared[self.A] += "//strong _helper\n"                                   # or the file keeps it
        self.assertNotIn("blocked", self.transact(prepared=prepared))
        no_text = self.transact()                                                  # no prepared text: nothing is judged
        self.assertNotIn("comdats_dropped", no_text)

    def test_hatch_totals_may_move_not_grow(self):
        hatch = '#pragma optimize("", off)\n'
        now = {self.TU: "int a;\n", self.A: hatch}
        self.assertFalse(T.emit_hatches_grow(now, {self.A: "int a;\n", self.TU: hatch}))       # it moved
        self.assertFalse(T.emit_hatches_grow(now, {self.A: "int a;\n"}))                       # it went
        self.assertTrue(T.emit_hatches_grow(now, {self.TU: hatch}))                            # two now
        prepared = self.stand_in_removed()
        prepared[self.TU] = hatch + prepared[self.TU]
        report = self.transact(prepared=prepared, dry_run=False)
        self.assertIn("escape-hatch total", report["blocked"])
        self.exact.assert_not_called()

    # ------------------------------------------------------------------ undo and recovery
    def test_a_failing_build_puts_every_file_and_text_back(self):
        prepared = self.stand_in_removed()
        before = {r: (self.root / r).read_bytes() for r in self.base}
        report = self.transact(prepared=prepared, dry_run=False, build_effect=lambda sources: (False, "boom"))
        self.assertIn("the build did not pass", report["blocked"])
        self.assertIn("the ledger was put back", report["blocked"])
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)
        self.assertEqual(self.journals(), [])

    def test_a_committed_object_failing_any_file_puts_everything_back(self):
        # the committed TU object must define each file's rows; the scratch one said so
        prepared = self.stand_in_removed()
        before = {r: (self.root / r).read_bytes() for r in self.base}

        def strong_in_b(sources):
            real_b = self.root / "build" / "real-Second.obj"
            real_t = self.root / "build" / "real-Campaign.obj"
            real_a = self.root / "build" / "real-Mixed.obj"
            import build
            for obj, text in ((real_t, prepared[self.TU]), (real_a, prepared[self.A]),
                              (real_b, prepared[self.B] + f"//strong {self.EB}\n")):
                obj.write_text(text, encoding="utf-8")
                build._deps_sidecar(obj).write_text("{}")
            return True, "OK"
        report = self.transact(prepared=prepared, dry_run=False, build_effect=strong_in_b)
        self.assertIn("the file still defines 0x00002100 outside a COMDAT", report["blocked"])
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)

    def test_an_interrupt_puts_every_text_back(self):
        prepared = self.stand_in_removed()
        before = {r: (self.root / r).read_bytes() for r in self.base}

        def interrupted(sources):
            raise KeyboardInterrupt
        with self.assertRaises(KeyboardInterrupt):
            self.transact(prepared=prepared, dry_run=False, build_effect=interrupted)
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)
        self.assertEqual(self.journals(), [])

    def killed(self, prepared):
        """A run that dies inside the build: the journal and the written files are all that is left."""
        def dead(sources):
            raise KeyboardInterrupt
        with self.assertRaises(KeyboardInterrupt):
            self.transact(prepared=prepared, dry_run=False, build_effect=dead, undo=lambda record: ["killed"])
        self.assertEqual(len(self.journals()), 1)
        for rel, text in prepared.items():
            self.assertEqual(self.read(rel), text)

    def test_a_killed_transaction_is_recovered_with_its_texts(self):
        prepared = self.stand_in_removed()
        before = {r: (self.root / r).read_bytes() for r in self.base}
        self.killed(prepared)
        self.assertIn("did not finish", self.transact(prepared=prepared)["blocked"])
        restored, _busy, errors = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)
        self.assertEqual(self.journals(), [])

    def test_recovery_refuses_a_text_edited_since_and_retries(self):
        prepared = self.stand_in_removed()
        before = {r: (self.root / r).read_bytes() for r in self.base}
        self.killed(prepared)
        edited = prepared[self.A] + "// edited since\n"
        self.write(self.A, edited)
        restored, _busy, errors = self.recover()
        self.assertEqual(restored, [])
        self.assertTrue(any(self.A in e and "changed since" in e for e in errors), errors)
        self.assertEqual(self.read(self.A), edited)                                # nothing guessed
        self.assertEqual(self.read(self.TU), before[self.TU].decode())             # the rest went back
        self.assertEqual(len(self.journals()), 1)
        self.write(self.A, prepared[self.A])                                       # the edit undone: it completes
        restored, _busy, errors = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)

    def test_a_staged_text_goes_back_out_of_the_index(self):
        prepared = self.stand_in_removed()
        subprocess.run(["git", "add", "--", "Code", "reverse"], cwd=self.root, check=True)
        subprocess.run(["git", "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "base"], cwd=self.root, check=True)
        real_unlink = Path.unlink

        def unlink(path, *a, **k):
            if Path(path).suffix == ".json" and Path(path).parent.name == "emit-journal":
                raise KeyboardInterrupt                # dies after git add, before the journal goes
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink), self.assertRaises(KeyboardInterrupt):
            self.transact(prepared=prepared, dry_run=False)
        show = lambda rel: subprocess.run(["git", "show", f":{rel}"], cwd=self.root, capture_output=True).stdout
        self.assertEqual(show(self.A).decode(), prepared[self.A])                  # the move was staged
        restored, _busy, errors = self.recover()
        self.assertEqual((len(restored), errors), (1, []))
        for rel in (self.A, self.B, self.TU):
            self.assertEqual(show(rel), self.base[rel] if rel != self.TU else f"//comdat {self.OWN}\n".encode())

    # ------------------------------------------------------------------ the command line
    def run_main(self, *argv):
        with patch.object(sys, "argv", ["tu_skeleton.py", *argv]), patch.object(T, "emit_move", return_value={"subject": "x"}) as emit, \
                patch.object(T, "split", return_value={"subject": "x"}) as split, contextlib.redirect_stdout(io.StringIO()):
            code = T.main()
        return code, emit, split

    def test_the_command_line(self):
        text = self.root / "t.txt"
        text.write_bytes(b"line\r\n")
        code, emit, _ = self.run_main("--emit-move", f"{self.A},{self.B}", "--for", self.TU, "--rva", "0x1,0x2",
                                      "--prepared", f"{self.TU}={text}", "--prepared", f"{self.A}={text}", "--dry-run")
        self.assertEqual(code, 0)
        args, kw = emit.call_args
        self.assertEqual(args[:2], ([self.A, self.B], self.TU))
        self.assertEqual(args[2], ["0x1", "0x2"])
        self.assertEqual(kw["prepared"], {self.TU: "line\n", self.A: "line\n"})
        _, emit, _ = self.run_main("--emit-move", self.A, "--for", self.TU)
        self.assertEqual(emit.call_args[0][0], self.A)                             # one file: as before
        self.assertEqual(emit.call_args[1]["prepared"], {})
        with self.assertRaises(SystemExit):
            self.run_main("--emit-move", self.A, "--for", self.TU, "--prepared", "no-equals")
        _, _, split = self.run_main("--split", self.A, "--for", self.TU, "--prepared", f"{self.TU}={text}")
        self.assertEqual(split.call_args[1]["prepared"], "line\n")
        for bad in (["--prepared", f"{self.TU}={text}", "--prepared", f"{self.TU}={text}"], ["--prepared", f"{self.A}={text}"]):
            with self.subTest(bad=bad), self.assertRaises(SystemExit):
                self.run_main("--split", self.A, "--for", self.TU, *bad)

    # ------------------------------------------------------------------ the transfer proof
    INST, COPY = "??$f@H@@YAXXZ", "??0R@@QAE@ABV0@@Z"          # a template instance, a copy ctor: no name admits them

    def proof_case(self):
        """Each donor hosts a stand-in the prepared texts remove, and the prepared TU emits it."""
        self.rows = {self.A: [self.row(self.INST, "0x00002000", self.A), self.row(self.STAY_A, "0x00003000", self.A)],
                     self.B: [self.row(self.COPY, "0x00002100", self.B), self.row(self.STAY_B, "0x00003100", self.B)],
                     self.TU: [self.row(self.OWN, "0x00001000", self.TU)]}
        self.write(self.A, f"//comdat {self.INST}\n//comdat {self.STAY_A}\n")
        self.write(self.B, f"//comdat {self.COPY}\n//comdat {self.STAY_B}\n")
        self.write(self.TU, f"//comdat {self.OWN}\n")
        self.ledger()
        return {self.TU: f"//comdat {self.OWN}\n//comdat {self.INST}\n//comdat {self.COPY}\n",
                self.A: f"//comdat {self.STAY_A}\n", self.B: f"//comdat {self.STAY_B}\n"}

    RVAS = ["0x00002000", "0x00002100"]

    def proof_refuses(self, prepared, rva, why, **kw):
        report = self.transact(rvas=self.RVAS, prepared=prepared, **kw)
        self.assertEqual(report["blocked"], "a requested row cannot move by emission")
        self.assertIn(why, report["refused_rows"][rva])
        self.assertNotIn("transfer_proof", report)

    def test_a_prepared_handover_moves_rows_no_name_admits(self):
        prepared = self.proof_case()
        report = self.transact(prepared=prepared)
        self.assertNotIn("blocked", report)
        self.assertEqual(report["transfer_proof"], self.RVAS)
        self.unchanged()
        report = self.transact(prepared=prepared, dry_run=False)
        self.assertNotIn("blocked", report)
        self.assertEqual(report["moved"], self.RVAS)
        funcs = self.read("reverse/functions.csv")
        self.assertIn(f"{self.INST},,0x00002000,8,{self.TU},", funcs)
        self.assertIn(f"{self.COPY},,0x00002100,8,{self.TU},", funcs)
        for rel, text in prepared.items():
            self.assertEqual(self.read(rel), text)

    def test_the_proof_compares_the_body_not_only_its_bytes(self):
        prepared = self.proof_case()
        prepared[self.TU] += f"//reloc {self.INST} ?h@@3HA\n"
        self.proof_refuses(prepared, "0x00002000", "differs from")
        prepared = self.proof_case()                                                 # moved word for word: the same
        self.write(self.A, self.read(self.A) + f"//reloc {self.INST} ?g@@3HA\n")
        self.ledger()
        prepared[self.TU] += f"//reloc {self.INST} ?g@@3HA\n"
        self.assertNotIn("blocked", self.transact(prepared=prepared))
        prepared[self.TU] = prepared[self.TU].replace("?g@@3HA", "?h@@3HA")
        self.proof_refuses(prepared, "0x00002000", "differs from")

    def test_a_body_that_cannot_be_compared_refuses(self):
        prepared = self.proof_case()
        prepared[self.TU] += f"//incomparable {self.INST}\n"
        self.proof_refuses(prepared, "0x00002000", "cannot be compared")
        prepared = self.proof_case()
        self.write(self.A, self.read(self.A) + f"//incomparable {self.INST}\n")     # today's object, the old side
        self.ledger()
        self.proof_refuses(prepared, "0x00002000", "cannot be compared")

    def test_the_rebuilt_objects_must_hold_the_same_body(self):
        prepared = self.proof_case()

        def built(sources):
            for source in sources:
                text = self.read(source) + (f"//reloc {self.INST} ?h@@3HA\n" if source == self.TU else "")
                (self.root / "build" / f"real-{Path(source).stem}.obj").write_text(text, encoding="utf-8")
            return True, "Functions: OK"
        report = self.transact(prepared=prepared, dry_run=False, build_effect=built)
        self.assertIn("fail the transfer proof", report["blocked"])
        self.assertIn("differs from", report["blocked"])
        self.unchanged()

    def changed_after_the_build(self, rel, text):
        prepared = self.proof_case()

        def built(sources):
            for source in sources:
                (self.root / "build" / f"real-{Path(source).stem}.obj").write_text(self.read(source), encoding="utf-8")
            self.write(rel, self.read(rel) + text)
            return True, "Functions: OK"
        report = self.transact(prepared=prepared, dry_run=False, build_effect=built)
        self.assertIn("changed after the build read them", report["blocked"])
        self.assertIn(rel, report["blocked"])
        staged = subprocess.run(["git", "ls-files", "-s", "--", rel], cwd=self.root, capture_output=True, text=True).stdout
        return staged, prepared

    def test_a_prepared_text_edited_after_the_build_is_not_staged(self):
        staged, _ = self.changed_after_the_build(self.TU, "#error UNCHECKED EDIT AFTER COMPILE\n")
        self.assertEqual(staged, "")                                                 # nothing reached the index

    def test_a_built_file_edited_after_the_build_is_not_staged(self):
        self.changed_after_the_build(self.A, "//comdat ?extra@@YAXXZ\n")

    def test_an_unprepared_source_edited_after_the_build_is_refused(self):
        prepared = self.proof_case()
        self.write(self.TU, prepared.pop(self.TU))                                   # the TU already emits both
        self.ledger()

        def built(sources):
            for source in sources:
                (self.root / "build" / f"real-{Path(source).stem}.obj").write_text(self.read(source), encoding="utf-8")
            self.write(self.TU, self.read(self.TU) + "//edited\n")
            return True, "Functions: OK"
        report = self.transact(prepared=prepared, dry_run=False, build_effect=built)
        self.assertIn("changed after the build read them", report["blocked"])
        self.assertIn(self.TU, report["blocked"])

    def test_a_ledger_edited_after_the_build_is_not_staged(self):
        self.changed_after_the_build("reverse/functions.csv", "# edited\n")

    def test_a_missing_hatch_checker_refuses(self):
        prepared = self.proof_case()
        with patch.dict(sys.modules, {"hatch_counters": None}):
            self.assertIn("checker is unavailable", T.emit_hatches_grow({self.A: ""}, {self.A: "__declspec(selectany) int g;\n"}))
            report = self.transact(prepared=prepared)
        self.assertIn("checker is unavailable", report["blocked"])
        self.unchanged()

    def test_the_proof_is_only_for_a_prepared_file(self):
        prepared = self.proof_case()
        report = self.transact(rvas=self.RVAS)                                       # no prepared text at all
        self.assertIn("a template instance", report["refused_rows"]["0x00002000"])
        self.assertIn("not a deleting destructor", report["refused_rows"]["0x00002100"])
        report = self.transact(rvas=self.RVAS, prepared={self.TU: prepared[self.TU], self.A: prepared[self.A]})
        self.assertIn("not a deleting destructor", report["refused_rows"]["0x00002100"])    # B's text is not prepared
        self.assertNotIn("0x00002000", report["refused_rows"])

    def test_a_deleting_destructor_stays_on_its_own_route(self):
        # its name admits it, so the hand-written check judges it and the proof does not
        prepared = self.stand_in_removed()
        report = self.transact(prepared=prepared)
        self.assertNotIn("blocked", report)
        self.assertNotIn("transfer_proof", report)

    def test_the_donor_still_defining_it_refuses(self):
        for kind in ("comdat", "strong", "weak", "noduplicates"):
            with self.subTest(kind=kind):
                self.setUp()
                prepared = self.proof_case()
                prepared[self.A] += f"//{kind} {self.INST}\n"
                report = self.transact(rvas=self.RVAS, prepared=prepared)
                self.assertEqual(report["blocked"], "a requested row cannot move by emission")
                # a strong copy is refused earlier, for what it would collide with
                self.assertIn("outside a COMDAT" if kind == "strong" else "still defines", report["refused_rows"]["0x00002000"])

    def test_the_destination_bytes_differing_by_one_refuse(self):
        prepared = self.proof_case()
        prepared[self.TU] += f"//byte {self.INST} c4\n"                              # retail's is c3
        self.proof_refuses(prepared, "0x00002000", "not byte-exact")
        prepared[self.TU] = prepared[self.TU].replace("c4", "c3")                    # the same byte: it moves
        self.assertNotIn("blocked", self.transact(rvas=self.RVAS, prepared=prepared))

    def test_the_destination_must_define_it_as_a_code_comdat_selected_any(self):
        for kind, why in (("strong", "outside a COMDAT"), ("noduplicates", "selected NODUPLICATES"),
                          ("data", "outside a code section")):
            with self.subTest(kind=kind):
                self.setUp()
                prepared = self.proof_case()
                prepared[self.TU] = prepared[self.TU].replace(f"//comdat {self.INST}", f"//{kind} {self.INST}")
                self.proof_refuses(prepared, "0x00002000", why)
        self.setUp()
        prepared = self.proof_case()
        prepared[self.TU] = prepared[self.TU].replace(f"//comdat {self.INST}\n", "")
        self.proof_refuses(prepared, "0x00002000", "does not emit it")

    def test_exactly_one_object_may_define_it_afterwards(self):
        prepared = self.proof_case()
        prepared[self.B] += f"//comdat {self.INST}\n"                                # another unit of the transaction
        self.proof_refuses(prepared, "0x00002000", f"exactly one object must define it afterwards: {self.B}")

    def test_the_map_must_approve_the_destination_for_the_address(self):
        for change in ("proposed", "elsewhere"):
            with self.subTest(change=change):
                self.setUp()
                prepared = self.proof_case()

                def changed():
                    rows = type(self).map_of(self)
                    for m in rows:
                        if m["rva"] == "0x00002000":
                            m["confidence" if change == "proposed" else "tu"] = "proposed" if change == "proposed" else self.OTHER
                    return rows
                self.map_of = changed
                self.proof_refuses(prepared, "0x00002000", "does not approve")

    def test_anything_inconclusive_refuses(self):
        for rel in (self.TU, self.A, self.B):
            with self.subTest(rel=rel):
                self.setUp()
                prepared = self.proof_case()
                prepared[rel] += "//garbage\n"
                self.proof_refuses(prepared, "0x00002000", "cannot be read: inconclusive")

    def test_the_final_compiles_are_judged_again(self):
        prepared = self.proof_case()
        calls = []

        def second_look(obj):
            calls.append(obj)
            found = self.definitions(obj)
            return None if len(calls) > 6 else found                                 # the byte gate read 3 units, twice
        report = self.transact(rvas=self.RVAS, prepared=prepared, definitions=second_look)
        self.assertIn("re-judged on the final compiles", report["blocked"])
        self.assertIn("inconclusive", report["blocked"])

    def after_the_build(self, prepared, change):
        """The apply over a build whose real objects are the prepared texts, then `change`d."""
        real = {f: self.root / "build" / f"real-{Path(f).stem}.obj" for f in [self.TU, self.A, self.B]}
        import build

        def built(sources):
            for source in sources:
                real[source].write_text(self.read(source), encoding="utf-8")
                build._deps_sidecar(real[source]).write_text("{}")
            change(real)
            return True, "OK"
        before = {r: (self.root / r).read_bytes() for r in self.base}
        report = self.transact(rvas=self.RVAS, prepared=prepared, dry_run=False, build_effect=built)
        self.assertEqual({r: (self.root / r).read_bytes() for r in self.base}, before)
        return report

    def test_the_rebuilt_objects_are_judged_too(self):
        prepared = self.proof_case()

        def donor_defines(real):
            real[self.A].write_text(prepared[self.A] + f"//comdat {self.INST}\n", encoding="utf-8")
        report = self.after_the_build(prepared, donor_defines)
        self.assertIn("the rebuilt objects fail the transfer proof", report["blocked"])
        self.assertIn("still defines it", report["blocked"])
        self.assertIn("the ledger was put back", report["blocked"])

        def donor_gone(real):
            real[self.B].unlink()
        report = self.after_the_build(prepared, donor_gone)
        self.assertIn("inconclusive", report["blocked"])

    def test_the_apply_compiles_from_nothing(self):
        # objects and receipts deleted, the object store off, so the build cannot reuse a thing
        prepared = self.proof_case()
        import build
        real = {f: self.root / "build" / f"real-{Path(f).stem}.obj" for f in [self.TU, self.A, self.B]}
        (self.root / "build").mkdir(exist_ok=True)
        for obj in real.values():
            obj.write_text("stale", encoding="utf-8")
            build._deps_sidecar(obj).write_text("{}")
        saw = []

        def built(sources):
            saw.append(([p.name for p in real.values() if p.exists() or build._deps_sidecar(p).exists()],
                        os.environ.get("BFME_OBJSTORE")))
            for source in sources:
                real[source].write_text(self.read(source), encoding="utf-8")
            return True, "OK"
        report = self.transact(rvas=self.RVAS, prepared=prepared, dry_run=False, build_effect=built)
        self.assertNotIn("blocked", report)
        self.assertEqual(saw, [([], "off")])
        self.assertNotEqual(os.environ.get("BFME_OBJSTORE"), "off")                  # only for the transaction

    def test_an_object_that_cannot_be_deleted_stops_the_build(self):
        prepared = self.proof_case()
        (self.root / "build").mkdir(exist_ok=True)
        locked = self.root / "build" / "real-Mixed.obj"
        locked.write_text("stale", encoding="utf-8")
        real_unlink, attempts = Path.unlink, []

        def unlink(path, *a, **k):
            if Path(path) == locked and not attempts:
                attempts.append(path)
                raise PermissionError("locked")
            return real_unlink(path, *a, **k)
        with patch.object(Path, "unlink", unlink):
            report = self.transact(rvas=self.RVAS, prepared=prepared, dry_run=False)
        self.assertIn("could not delete an object", report["blocked"])
        self.exact.assert_not_called()

    def test_without_a_proof_the_objects_are_left_alone(self):
        # a deleting destructor's move keeps its store and its objects, as before
        prepared = self.stand_in_removed()
        saw = []

        def built(sources):
            saw.append(os.environ.get("BFME_OBJSTORE"))
            for source in sources:
                (self.root / "build" / f"real-{Path(source).stem}.obj").write_text(self.read(source), encoding="utf-8")
            return True, "OK"
        self.assertNotIn("blocked", self.transact(prepared=prepared, dry_run=False, build_effect=built))
        self.assertEqual(saw, ["off"])                                               # prepared: compiled fresh all the same
        self.setUp()
        saw.clear()
        self.assertNotIn("blocked", self.transact(dry_run=False, build_effect=built))
        self.assertNotEqual(saw, ["off"])                                            # no text changed

    def test_a_refused_row_stays_and_its_prepared_file_then_loses_it(self):
        # without --rva a refused row stays in its file, whose prepared text no longer emits it
        prepared = self.proof_case()
        prepared[self.TU] = prepared[self.TU].replace(f"//comdat {self.INST}\n", "")
        report = self.transact(prepared=prepared, dry_run=False)
        self.assertIn("remaining rows lose matches", report["blocked"])
        self.exact.assert_not_called()

    def test_a_companion_follows_its_parents_proof(self):
        funclet = f"__ehhandler${self.INST}"
        prepared = self.proof_case()
        self.rows[self.A].insert(1, self.row(funclet, "0x00002010", self.A))
        self.approved["0x00002010"] = self.TU
        prepared[self.TU] += f"//comdat {funclet}\n"
        self.write(self.A, self.read(self.A) + f"//comdat {funclet}\n")
        self.ledger()
        report = self.transact(rvas=self.RVAS, prepared=prepared)
        self.assertNotIn("blocked", report)
        self.assertIn("0x00002010", report["moved"])
        self.confidence["0x00002010"] = "proposed"                                   # its own address, not its parent's
        report = self.transact(rvas=self.RVAS, prepared=prepared)
        self.assertIn("does not approve", report["refused_rows"]["0x00002010"])
        self.confidence.clear()
        prepared[self.B] += f"//comdat {funclet}\n"
        report = self.transact(rvas=self.RVAS, prepared=prepared)
        self.assertIn("exactly one object", report["refused_rows"]["0x00002010"])

    @staticmethod
    def coff(symbols, machine=0x14C):
        """A minimal COFF object: one section, COMDAT in code, selected ANY, and `symbols`, each
        (name, section, storage, aux records' bytes or None)."""
        import struct
        table = 20 + 40
        records, count = b"", 0
        for name, section, storage, aux in [(".text", 1, 3, b"\0" * 14 + bytes([2]) + b"\0" * 3)] + symbols:
            records += struct.pack("<8sIhHBB", name.encode(), 0, section, 0, storage, 1 if aux else 0) + (aux or b"")
            count += 2 if aux else 1
        header = struct.pack("<HHIIIHH", machine, 1, 0, table, count, 0, 0)
        section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 0, 0, 0, 0, 0, 0, 0x20 | 0x1000)
        return header + section + records + struct.pack("<I", 4)

    def test_coff_definitions_reads_strictly(self):
        with tempfile.TemporaryDirectory() as tmp:
            def read(data):
                path = Path(tmp) / "o.obj"
                path.write_bytes(data)
                return T.coff_definitions(path)
            external, weak = 2, 105
            self.assertEqual(read(self.coff([("_f", 1, external, None)])), {"_f": (True, True, 2)})
            self.assertIsNone(read(self.coff([("_f", 9, external, None)])))             # a section out of range
            self.assertEqual(read(self.coff([("_f", 1, 3, None)])), {})                  # a local symbol is no definition
            # a weak external can satisfy the name, so it counts: the donor may not keep one
            tag = (1).to_bytes(4, "little") + b"\0" * 14
            found = read(self.coff([("_g", 1, external, None), ("_x", 0, weak, tag)]))
            self.assertEqual(found["_x"], (False, False, None))
            self.assertIn("still defines", self.handover(found))
            self.assertEqual(read(self.coff([("_f", 1, external, None)]) + b"/alternatename:_y=_f\0")["_y"], (False, False, None))
            self.assertIsNone(read(self.coff([("_f", 1, external, None)], machine=0x8664)))   # not i386

    @staticmethod
    def handover(donor_defs):
        with patch.object(T, "coff_definitions", side_effect=lambda obj: donor_defs if obj == "d" else {"_x": (True, True, 2)}):
            with patch.object(T, "section_identity", return_value=("body",)):
                return T.transfer_problem("_x", "d", "t", {"d": "d", "t": "t"}, {"_x": ("body",)})

    def test_what_a_transfer_requires_of_the_destination(self):
        # read directly: the byte gate refuses most of these first, on a less strict reading
        cases = {"comdat any": ((True, True, 2), None), "strong": ((False, True, None), "outside a COMDAT"),
                 "no duplicates": ((True, True, 1), "selected NODUPLICATES"), "same size": ((True, True, 3), "selected SAME_SIZE"),
                 "data": ((True, False, 2), "outside a code section"), "weak": ((False, False, None), "outside a code section")}
        for label, (found, why) in cases.items():
            with self.subTest(label=label), patch.object(T, "coff_definitions", side_effect=lambda obj: {"t": {"n": found}}.get(obj, {})), \
                    patch.object(T, "section_identity", return_value=("body",)):
                got = T.transfer_problem("n", "d", "t", {"d": "d", "t": "t"}, {"n": ("body",)})
                self.assertIsNone(got) if why is None else self.assertIn(why, got)
        with patch.object(T, "coff_definitions", return_value={}):
            self.assertIn("does not define it", T.transfer_problem("n", "d", "t", {"d": "d", "t": "t"}, {}))
            # a funclet is usually a local symbol: its absence among the externals is no refusal
            self.assertIsNone(T.transfer_problem("n", "d", "t", {"d": "d", "t": "t"}, {}, companion=True))

    def test_the_old_body_is_required_and_compared(self):
        with patch.object(T, "coff_definitions", side_effect=lambda obj: {"t": {"n": (True, True, 2)}}.get(obj, {})):
            for old, new, why in ((None, ("body",), "cannot be compared"), (("body",), None, "cannot be compared"),
                                  (("body",), ("other",), "differs from")):
                with self.subTest(old=old, new=new), patch.object(T, "section_identity", return_value=new):
                    self.assertIn(why, T.transfer_problem("n", "d", "t", {"d": "d", "t": "t"}, {"n": old}))
            with patch.object(T, "section_identity", return_value=("body",)):
                self.assertIn("cannot be compared", T.transfer_problem("n", "d", "t", {"d": "d", "t": "t"}, {}))

    @staticmethod
    def built_coff(sections, symbols, strings=b""):
        """A COFF object: `sections` [(name, flags, raw, [(offset, symbol index, type)])], `symbols`
        [(name, value, section, storage, aux bytes or None)]; a name over 8 bytes goes to the string table."""
        import struct
        at = 20 + 40 * len(sections)
        raws, headers = b"", b""
        table = sum(18 * (2 if s[4] else 1) for s in symbols)
        offset = at + table
        strs = strings
        records = b""
        for name, value, section, storage, aux in symbols:
            spelled = name.encode()
            if len(spelled) > 8:
                spelled = struct.pack("<II", 0, 4 + len(strs))
                strs += name.encode() + b"\0"
            records += struct.pack("<8sIhHBB", spelled, value, section, 0, storage, 1 if aux else 0) + (aux or b"")
        tail = struct.pack("<I", 4 + len(strs)) + strs
        offset += len(tail)
        for name, flags, raw, relocs in sections:
            packed = b"".join(struct.pack("<IIH", *r) for r in relocs)
            headers += struct.pack("<8sIIIIIIHHI", name.encode(), 0, 0, len(raw), offset if raw else 0,
                                   offset + len(raw) if relocs else 0, 0, len(relocs), 0, flags)
            raws += raw + packed
            offset += len(raw) + len(packed)
        return struct.pack("<HHIIIHH", 0x14C, len(sections), 0, at, sum(2 if s[4] else 1 for s in symbols), 0, 0) + headers + records + tail + raws

    COMDAT_AUX = b"\0" * 14 + bytes([2]) + b"\0" * 3

    @staticmethod
    def associative_aux(number):
        return b"\0" * 12 + number.to_bytes(2, "little") + bytes([5]) + b"\0" * 3

    def body(self, tmp, target="_g", child="_a", label="$L12", label_value=0, storage=2, raw=b"\xb8\0\0\0\0\xc3", extra=b""):
        """`_f` in a COMDAT, one DIR32 to `target`, an associated `.xdata$x` with one to `child` and one to a local `label`."""
        symbols = [(".text", 0, 1, 3, self.COMDAT_AUX), ("_f", 0, 1, 2, None), (".xdata$x", 0, 2, 3, self.associative_aux(1)),
                   (label, label_value, 1, 6, None), (target, 0, 0, storage, None), (child, 0, 0, 2, None)]
        path = Path(tmp) / f"o{len(list(Path(tmp).iterdir()))}.obj"
        path.write_bytes(self.built_coff([(".text", 0x60001020, raw, [(1, 6, 6)]),
                                          (".xdata$x", 0x40001040, b"\0" * 8, [(0, 7, 6), (4, 5, 6)])], symbols) + extra)
        return path

    def test_section_identity_sees_what_a_byte_mask_does_not(self):
        with tempfile.TemporaryDirectory() as tmp:
            same = T.section_identity(self.body(tmp), "_f")
            self.assertIsNotNone(same)
            self.assertEqual(T.section_identity(self.body(tmp), "_f"), same)
            self.assertEqual(T.section_identity(self.body(tmp, label="$L99"), "_f"), same)     # the compiler's own numbering
            for label, kw in (("main target", {"target": "_h"}), ("associated target", {"child": "_b"}),
                              ("where a label lands", {"label_value": 1}), ("a named local", {"label": "_named"}),
                              ("bytes", {"raw": b"\xb8\0\0\0\0\x90"}),
                              ("an alternate of the target", {"extra": b"/alternatename:_g=_other\0"})):
                with self.subTest(label=label):
                    self.assertNotEqual(T.section_identity(self.body(tmp, **kw), "_f"), same)

    def test_section_identity_refuses_what_it_cannot_compare(self):
        with tempfile.TemporaryDirectory() as tmp:
            self.assertIsNone(T.section_identity(self.body(tmp), "_missing"))
            self.assertIsNone(T.section_identity(self.body(tmp, storage=105), "_f"))           # a weak target
            self.assertIsNone(T.section_identity(Path(tmp) / "gone.obj", "_f"))
            self.assertIsNone(T.section_identity(None, "_f"))
            for index in (1, 99):                       # a relocation naming an aux record, or past the table
                symbols = [(".text", 0, 1, 3, self.COMDAT_AUX), ("_f", 0, 1, 2, None)]
                bad = Path(tmp) / f"bad{index}.obj"
                bad.write_bytes(self.built_coff([(".text", 0x60001020, b"\xc3\0\0\0\0", [(1, index, 6)])], symbols))
                self.assertIsNone(T.section_identity(bad, "_f"))

    def test_a_malformed_object_is_not_an_empty_one(self):
        import struct
        with tempfile.TemporaryDirectory() as tmp:
            good = self.body(tmp).read_bytes()
            header = lambda sections, at, count, optional=0: struct.pack("<HHIIIHH", 0x14C, sections, 0, at, count, optional, 0)
            cases = {"no section table": header(1, 20, 0), "no sections": header(0, 20, 1) + b"\0" * 22,
                     "no symbols": header(1, 60, 0) + b"\0" * 44, "symbols past the end": header(1, 60, 999) + b"\0" * 60,
                     "optional header past the end": good[:16] + struct.pack("<H", 0xFFFF) + good[18:],
                     "no string table": good[:20 + 80 + 18 * 8],
                     "cut in a section's data": good[:-3]}
            for label, data in cases.items():
                with self.subTest(label=label):
                    bad = Path(tmp) / "bad.obj"
                    bad.write_bytes(data)
                    self.assertIsNone(T.coff_definitions(bad))
                    self.assertIsNone(T.section_identity(bad, "_f"))
                    self.assertEqual(T.transfer_problem("_f", "d", "t", {"d": bad, "t": self.body(tmp)}, {"_f": ("x",)}),
                                     "d's object cannot be read: inconclusive")
            # well formed in every table, and still no compile's output
            symbols = [(".text", 0, 1, 3, self.COMDAT_AUX), ("_f", 0, 1, 2, None)]
            text = (".text", 0x60001020, b"\xc3", [])
            for label, data in (("no sections", self.built_coff([], [("_f", 0, 0, 2, None)])), ("no symbols", self.built_coff([text], [])),
                                ("a local symbol past the sections", self.built_coff([text], symbols + [("$L1", 0, 9, 6, None)])),
                                ("a string table past the end", self.built_coff([text], symbols)[:-5] + struct.pack("<I", 0xFFFF) + b"\xc3")):
                with self.subTest(label=label):
                    bad = Path(tmp) / "bad.obj"
                    bad.write_bytes(data)
                    self.assertIsNone(T.coff_definitions(bad))
            good_small = Path(tmp) / "small.obj"
            good_small.write_bytes(self.built_coff([text], symbols))
            self.assertIn("_f", T.coff_definitions(good_small))                          # the cases above fail for their own reason
            for label, offset in (("raw data", 20 + 20), ("relocations", 20 + 24), ("line numbers", 20 + 28)):
                with self.subTest(label=label):
                    bad = Path(tmp) / "bad.obj"
                    data = bytearray(good)
                    struct.pack_into("<I", data, offset, 0x7FFFFFF0)
                    if label == "line numbers":
                        struct.pack_into("<H", data, 20 + 34, 1)
                    bad.write_bytes(data)
                    self.assertIsNone(T.coff_definitions(bad))

    def test_fresh_compiles_turns_the_store_off_and_back(self):
        import build
        before = os.environ.get("BFME_OBJSTORE")
        build._objstore_root.cache_clear()
        with T.fresh_compiles():
            self.assertEqual(os.environ["BFME_OBJSTORE"], "off")
            self.assertIsNone(build._objstore_root())
        self.assertEqual(os.environ.get("BFME_OBJSTORE"), before)
        with self.assertRaises(RuntimeError), T.fresh_compiles():
            raise RuntimeError
        self.assertEqual(os.environ.get("BFME_OBJSTORE"), before)
        with patch.dict(os.environ, {"BFME_OBJSTORE": "on"}):
            with T.fresh_compiles():
                pass
            self.assertEqual(os.environ["BFME_OBJSTORE"], "on")


class VtableRiderPreparedSplitTests(unittest.TestCase):
    """P16 minimal B, rules (b) and (c): ParticleSystemFXNuggetCtor.cpp's ctor moves into FXList.cpp
    with a prepared TU text, and its displaced `??_G` rides with the body that emits the vtable."""
    SOURCE, TU = "Code/Ctor.cpp", "Code/FXList.cpp"
    DTOR = "??_GRec@@UAEPAXI@Z"
    PREPARED = "struct Rec { Rec(); virtual ~Rec(); };\nvoid move() {}\n"

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "Code").mkdir()
        (self.root / "reverse").mkdir()
        (self.root / self.SOURCE).write_bytes(b"void move(){}\nvoid stay(){}\n")
        (self.root / self.TU).write_bytes(b"struct Rec { };\n")

    def split(self, *, prepared=PREPARED, stay=False, tu_vtable=True, residual_vtable=False, map_tu="",
              second_row=False, prepared_misses=False, dtor=True, held=None, merge_blocked=False, copies=None,
              donor_pp="", merge_raises=None):
        row = lambda n, r, s=self.SOURCE: dict(name=n, export_rva="", target_rva=r, target_size="1", source=s,
                                               status="matched", notes="")
        mine = ([row("_move", "0x1000")] + ([row(self.DTOR, "0x7000")] if dtor else [])
                + ([row("_stay", "0x3000")] if stay else []))
        ledger = list(mine) + ([row("??_GOther@@UAEPAXI@Z", "0x7000", "Code/Other.cpp")] if second_row else [])
        seen = {}
        objs = {self.TU: self.root / "t.obj", self.SOURCE: self.root / "x.obj"}

        class Verifier:
            errors, all_errors = [], []

            def __init__(self, source):
                self.source, self.obj = source, objs[source]

            def matched(self, text, rows):
                names = set(re.findall(r"void\s+(\w+)\s*\(", text))
                out = {r["target_rva"] for r in rows if r["name"].lstrip("_") in names}
                if "move" in names:                       # the ctor's unit emits the vtable, so the ??_G
                    out.add("0x7000")
                if prepared_misses and text == prepared:
                    out.discard("0x1000")
                return out & {r["target_rva"] for r in rows}

            def preprocessed(self, text, rows):
                return text, None

        def merge(tu, sk, don, report, dry_run, **kw):
            seen.update(don=don, **kw)
            if merge_raises:
                raise merge_raises
            return dict(report, blocked="no verified merge") if merge_blocked else dict(report, accepted=list(don))

        def vtables(obj, cls):
            return ({"??_7Rec@@6B@"} if (obj == objs[self.TU] and tu_vtable) or (obj == objs[self.SOURCE] and residual_vtable)
                    else set())
        cache = {"ledger": ledger, "by_file": {self.SOURCE: mine},
                 "approved_at": {0x1000: self.TU, 0x3000: "Code/Other.cpp"},
                 "assigned": {0x1000: self.TU.lower(), 0x3000: "code/other.cpp"},
                 "map_by_rva": {0x7000: {"rva": "0x7000", "kind": "code", "tu": map_tu, "confidence": "displaced",
                                         "by": "-", "evidence": "N=Code/Ctor.cpp"}}}
        with patch.object(T, "ROOT", self.root), patch.dict(T._CACHE, cache, clear=True), \
                patch.object(T, "refusal", return_value=None), patch.object(T, "included_by", return_value=[]), \
                patch.object(T, "data_rowed_idents", return_value=set()), patch.object(T, "debt_keys", return_value=set()), \
                patch.object(T, "hatch_move", return_value={}), patch.object(T, "prepared_hatches", return_value={}), \
                patch.object(T, "skeleton", return_value=[]), patch.object(T, "Verifier", Verifier), \
                patch.object(T, "SplitLinkGuard"), patch.object(T, "LinkGuard"), \
                patch.object(T, "vtable_symbols", side_effect=vtables), patch.object(T, "_merge", side_effect=merge), \
                patch.object(T, "claim_scope", return_value=held), patch.object(T.claims, "release") as self.release, \
                patch.object(T, "deleting_copy_problem", side_effect=lambda obj, name: (copies or {}).get(Path(obj).name)), \
                patch.object(T.rename, "preprocess_unit", return_value=(None, "cl -E failed") if donor_pp is None
                             else ((self.root / self.SOURCE).read_text() + donor_pp, None)):
            report = T.split(self.SOURCE, self.TU, dry_run=held is None, claim=held is not None, prepared=prepared)
        return report, seen

    def test_a_whole_donor_with_a_prepared_text_moves_its_rider_and_is_absorbed(self):
        report, seen = self.split()
        self.assertNotIn("blocked", report)
        self.assertEqual(report["riders"], ["0x7000"])                 # (b): the ??_G rides with the ctor
        self.assertEqual(sorted(r["target_rva"] for r in seen["don"][self.SOURCE]), ["0x1000", "0x7000"])
        self.assertEqual(seen["fixed_text"], self.PREPARED)            # (c): judged in the prepared text
        self.assertEqual(seen["applier"].__name__, "absorb")           # nothing stays: the donor goes
        self.assertIs(seen["deletes_donor"], True)                     # so the map is judged as for a merge
        self.assertIsNone(seen["moved_rows"])

    def test_without_a_prepared_text_a_whole_donor_still_refuses(self):
        report, _ = self.split(prepared=None)
        self.assertIn("use --merge", report["blocked"])
        report, _ = self.split(prepared=None, dtor=False)               # every row approved: nothing rides
        self.assertIn("use --merge", report["blocked"])

    def test_a_donor_with_only_approved_rows_is_absorbed_with_a_prepared_text(self):
        report, seen = self.split(dtor=False)
        self.assertNotIn("blocked", report)
        self.assertEqual(seen["applier"].__name__, "absorb")

    def test_a_partial_split_with_a_prepared_text_keeps_the_split_applier(self):
        report, seen = self.split(stay=True)
        self.assertNotIn("blocked", report)
        self.assertEqual(seen["applier"].__name__, "applier")
        self.assertEqual(seen["fixed_text"], self.PREPARED)
        self.assertIs(seen["deletes_donor"], False)
        self.assertEqual(seen["moved_rows"], {self.SOURCE: sorted(r["target_rva"] for r in seen["don"][self.SOURCE])})

    def test_the_rider_needs_the_destination_to_emit_the_vtable_and_the_residual_not(self):
        report, _ = self.split(tu_vtable=False, stay=True)
        self.assertIn("rides only with the body that emits Rec's vtable", report["blocked"])
        report, _ = self.split(residual_vtable=True, stay=True)
        self.assertIn("rides only with the body that emits Rec's vtable", report["blocked"])

    def test_a_row_another_emitter_or_the_map_can_claim_never_rides(self):
        # the map placing the ??_G elsewhere, or a second ledger row at its address: no rider, and the
        # residual's loss stops the split
        for kw in ({"map_tu": "Code/Other.cpp"}, {"second_row": True}):
            with self.subTest(kw=kw):
                report, _ = self.split(stay=True, **kw)
                self.assertIn("residual loses matched rows", report["blocked"])

    def test_every_moved_row_must_match_in_the_prepared_text(self):
        report, _ = self.split(stay=True, prepared_misses=True)
        self.assertIn("every moved row must match in it", report["blocked"])

    def test_vtable_rider_is_only_a_deleting_dtor_the_map_leaves_homeless(self):
        # review of 9459886c66: rule (b) rests on the decorated name alone; no text is read
        rows = [{"name": self.DTOR, "target_rva": "0x7000", "source": self.SOURCE},
                {"name": "?f@Rec@@QAEXXZ", "target_rva": "0x7100", "source": self.SOURCE},
                {"name": "??1Rec@@UAE@XZ", "target_rva": "0x7200", "source": self.SOURCE},
                {"name": "??_ERec@@UAEPAXI@Z", "target_rva": "0x7300", "source": self.SOURCE},
                {"name": "??0Rec@@QAE@ABV0@@Z", "target_rva": "0x7400", "source": self.SOURCE},
                {"name": "??4Rec@@QAEAAV0@ABV0@@Z", "target_rva": "0x7500", "source": self.SOURCE}]
        cache = {"ledger": rows, "map_by_rva": {int(r["target_rva"], 16): {
            "rva": r["target_rva"], "kind": "code", "tu": "", "confidence": "displaced", "by": "-", "evidence": ""}
            for r in rows}}
        with patch.dict(T._CACHE, cache, clear=True), \
                patch.object(T.rename, "preprocess_unit", side_effect=AssertionError("no text is read")):
            self.assertEqual([T.vtable_rider(r) for r in rows], [True, False, False, True, False, False])

    def test_a_split_tells_a_saved_plan_what_it_moves(self):
        # review of dee0813e84: without its rows a reused plan would skip the map check
        with patch.object(T, "load_verified_plan", return_value={"accepted": []}), \
                patch.object(T, "reuse_split_plan", side_effect=lambda tu, don, report, *a, **k: dict(report, accepted=list(don))) as reuse:
            report, _ = self.split(prepared=None, stay=True)
        self.assertNotIn("blocked", report)
        self.assertEqual(reuse.call_args.kwargs["moved_rows"], {self.SOURCE: ["0x1000", "0x7000"]})

    def test_a_refused_or_blocked_split_gives_back_only_what_it_acquired(self):
        # review of 9459886c66: --split (and so --prepared) released the whole scope without tokens
        key = T.claims.key_of(f"file:{self.TU}")
        refused = T.Held(["file:Code/Ctor.cpp"])
        refused.acquired, refused.tokens = [key], {key: "MINE"}
        report, _ = self.split(held=refused)
        self.assertIn("held by another worker", report["blocked"])
        self.release.assert_called_once_with([key], tokens={key: "MINE"})
        won = T.Held()
        won.acquired, won.tokens = [key], {key: "MINE"}
        report, _ = self.split(held=won, merge_blocked=True)                     # claimed, then blocked
        self.assertEqual(report["blocked"], "no verified merge")
        self.release.assert_called_once_with([key], tokens={key: "MINE"})
        report, _ = self.split(held=T.Held(["file:Code/Ctor.cpp"]))            # nothing acquired: nothing released
        self.release.assert_not_called()

    def test_a_split_raising_gives_back_only_before_its_first_write(self):
        # review of dee0813e84: both a whole donor's absorb and a partial split run through here
        key = T.claims.key_of(f"file:{self.TU}")
        won = T.Held()
        won.acquired, won.tokens = [key], {key: "MINE"}
        for stay in (False, True):
            with self.subTest(stay=stay):
                with self.assertRaises(OSError):
                    self.split(held=won, stay=stay, merge_raises=OSError("before the write"))
                self.release.assert_called_once_with([key], tokens={key: "MINE"})
                during = OSError("during the write")
                during.half_applied = True
                with self.assertRaises(OSError), contextlib.redirect_stderr(io.StringIO()):
                    self.split(held=won, stay=stay, merge_raises=during)
                self.release.assert_not_called()

    def test_a_hand_written_rider_never_rides(self):
        # review of 87417c8f9f: the destination's or the residual's copy must be the compiler's, and neither
        # the destination's text nor the file's may define it through `__identifier`
        spoof = 'extern "C" void __identifier("??_GRec@@UAEPAXI@Z")() {}\n'
        for kw, why in (({"copies": {"t.obj": "selects its COMDAT NODUPLICATES"}}, "NODUPLICATES"),
                        ({"copies": {"x.obj": "selects its COMDAT NODUPLICATES"}}, "NODUPLICATES"),
                        ({"prepared": self.PREPARED + spoof}, "may define it by hand"),
                        ({"donor_pp": spoof}, "may define it by hand"),
                        ({"donor_pp": None}, "cannot be preprocessed")):
            with self.subTest(kw=kw):
                report, _ = self.split(stay=True, **kw)
                self.assertIn("0x7000 may not ride", report["blocked"])
                self.assertIn(why, report["blocked"])
        report, _ = self.split(stay=True, donor_pp='extern "C" void __identifier("??_GRec@@UAEPAXI@Z")();\n')
        self.assertNotIn("blocked", report)                    # a declaration defines nothing


class NativeCompilerCase(unittest.TestCase):
    """MSVC 7.1 itself (under Wine off Windows), skipped where there is none."""

    def setUp(self):
        import build
        self.build = build
        try:
            build.vc71_root()
        except (Exception, SystemExit) as error:            # noqa: BLE001 - no compiler here
            self.skipTest(f"no MSVC 7.1: {error}")
        if os.name != "nt" and shutil.which("wine") is None:
            self.skipTest("no wine")
        self.folder = Path(build.ROOT) / "build" / "tu_skeleton" / f"native_selection_{os.getpid()}"
        self.folder.mkdir(parents=True, exist_ok=True)
        self.addCleanup(shutil.rmtree, self.folder, True)

    def run_cl(self, stem, text, preprocess=False):
        src = self.folder / f"{stem}.cpp"
        src.write_text(text)
        obj = src.with_suffix(".obj")
        command, env = self.build.compiler_command(src, obj)
        if preprocess:
            command = [c for c in command if not c.startswith(("-Fo", "/Fo")) and c not in ("-c", "/c")]
            command.insert(len(command) - 1, "-E")
        p = subprocess.run(command, env=env, capture_output=True, cwd=self.build.ROOT, timeout=600)
        self.assertEqual(p.returncode, 0, (p.stdout + p.stderr)[-400:])
        return p.stdout.decode("latin-1") if preprocess else obj


class NativeDeletingDtorSelectionTests(NativeCompilerCase):
    """The compiler selects its `??_G`/`??_E` ANY in a code section; a hand-written `__identifier`
    definition gets NODUPLICATES, an inline one ANY (left to identifier_definition on the preprocessed
    text), selectany data ANY in a data section."""
    NAME = "??_GRec@@UAEPAXI@Z"

    def test_the_compiler_selects_its_deleting_dtors_any_and_a_hand_written_one_not(self):
        cases = {"implicit": ("struct Rec { virtual ~Rec(); int a; }; Rec::~Rec() {} void f() { delete new Rec; }\n",
                              self.NAME, None),
                 "implicit_vector": ("struct Rec { virtual ~Rec(); int a; }; Rec::~Rec() {} "
                                     "void f() { delete[] new Rec[2]; }\n", "??_ERec@@UAEPAXI@Z", None),
                 "spoof_g": (f'extern "C" void __identifier("{self.NAME}")() {{}}\n', self.NAME, "NODUPLICATES"),
                 "spoof_e": ('extern "C" void __identifier("??_ERec@@UAEPAXI@Z")() {}\n', "??_ERec@@UAEPAXI@Z",
                             "NODUPLICATES"),
                 "spoof_inline": (f'extern "C" inline void __identifier("{self.NAME}")() {{}} '
                                  f'void g() {{ __identifier("{self.NAME}")(); }}\n', self.NAME, None),
                 "spoof_data": (f'extern "C" __declspec(selectany) int __identifier("{self.NAME}") = 1;\n',
                                self.NAME, "outside a code section")}
        for stem, (text, name, why) in cases.items():
            with self.subTest(stem=stem):
                obj = self.run_cl(stem, text)
                self.assertIn(name, T.comdat_symbols(obj))
                got = T.deleting_copy_problem(obj, name)
                self.assertEqual(got is None, why is None, got)
                if why:
                    self.assertIn(why, got)
        # the inline spoof the object check cannot see: the preprocessed text shows its definition
        self.assertTrue(T.identifier_definition(self.run_cl("spoof_inline_pp", cases["spoof_inline"][0], True), self.NAME))

    def test_a_macro_built_definition_is_read_after_preprocessing(self):
        text = ('#define SPOOF(n) extern "C" void __identifier(n)() {}\n'
                '#define NAME(k) "??_" #k "Rec@@UAEPAXI@Z"\n'
                f'SPOOF("{self.NAME}")\nSPOOF(NAME(E))\n')
        code = self.run_cl("macro_pp", text, preprocess=True)
        self.assertTrue(T.identifier_definition(code, self.NAME))
        self.assertTrue(T.identifier_definition(code, "??_ERec@@UAEPAXI@Z"))   # adjacent literals: unreadable

    def test_a_parenthesized_declarator_is_read(self):
        # review of f458166062: each compiles to exactly the name, selected ANY in code (the object check
        # passes it), so the preprocessed text must show the definition
        e = "??_ERec@@UAEPAXI@Z"
        cases = {"paren_g": (f'extern "C" inline void\n(__identifier("{self.NAME}"))() {{}}\n', self.NAME),
                 "paren_e": (f'extern "C" inline void (__identifier("{e}"))() {{}}\n', e),
                 "paren_many": (f'extern "C" inline void (((__identifier("{self.NAME}"))))() {{}}\n', self.NAME),
                 "paren_naked": (f'extern "C" __declspec(naked) inline void (__identifier("{self.NAME}"))() '
                                 '{ __asm ret }\n', self.NAME)}
        for stem, (text, name) in cases.items():
            with self.subTest(stem=stem):
                obj = self.run_cl(stem, text + f'void (*use)() = &__identifier("{name}");\n')
                self.assertIn(name, T.comdat_symbols(obj))
                self.assertIsNone(T.deleting_copy_problem(obj, name))          # ANY, in code: (a) cannot see it
                code = self.run_cl(stem + "_pp", text, preprocess=True)
                self.assertTrue(T.identifier_definition(code, name))
                self.assertTrue(T.hand_written_problem(name, [obj], {"u.cpp": (code, None)}))
        decl = f'extern "C" void (__identifier("{self.NAME}"))();\nvoid (*use)() = &(__identifier("{self.NAME}"));\n'
        self.assertIsNone(T.identifier_definition(self.run_cl("paren_decl_pp", decl, preprocess=True), self.NAME))

    def test_a_default_argument_literal_hides_no_body(self):
        # review of f11be8ac37: `(const char *p = ")") {}` compiled to the exact name, selected ANY in code,
        # and the bracket counting read no body; the allowlist on the masked text refuses each
        e = "??_ERec@@UAEPAXI@Z"
        cases = {"default_paren_g": (f'extern "C" inline void __identifier("{self.NAME}")(const char *p = ")") {{}}\n',
                                     self.NAME),
                 "default_char_g": (f"extern \"C\" inline void __identifier(\"{self.NAME}\")(char p = ')') {{}}\n",
                                    self.NAME),
                 "default_paren_e": (f'extern "C" inline void __identifier("{e}")(const char *p = ")") {{}}\n', e),
                 "default_char_e": (f"extern \"C\" inline void __identifier(\"{e}\")(char p = ')') {{}}\n", e)}
        for stem, (text, name) in cases.items():
            with self.subTest(stem=stem):
                obj = self.run_cl(stem, text + f'void g() {{ __identifier("{name}")(); }}\n')   # the default, used
                self.assertIn(name, T.comdat_symbols(obj))
                self.assertIsNone(T.deleting_copy_problem(obj, name))          # ANY, in code: (a) cannot see it
                code = self.run_cl(stem + "_pp", text, preprocess=True)
                self.assertTrue(T.identifier_definition(code, name))
                self.assertTrue(T.hand_written_problem(name, [obj], {"u.cpp": (code, None)}))

    def test_a_trigraph_escaped_quote_hides_no_body(self):
        # review of 329404caeb: `??/` is a backslash to the compiler, so `"??/""` holds a quote; masking the raw
        # text lost quote sync and hid the definition between two of them
        for name in (self.NAME, "??_ERec@@UAEPAXI@Z"):
            with self.subTest(name=name):
                text = (f'const char *s="??/""; extern "C" __declspec(dllexport) inline void '
                        f'__identifier("{name}")() {{}} const char *t="??/"";\n')
                stem = "trigraph_" + name[3]
                obj = self.run_cl(stem, text)
                self.assertIn(name, T.comdat_symbols(obj))
                self.assertIsNone(T.deleting_copy_problem(obj, name))          # ANY, in code: (a) cannot see it
                code = self.run_cl(stem + "_pp", text, preprocess=True)
                self.assertIn("??/", code)                                      # cl -E leaves the trigraph
                self.assertTrue(T.identifier_definition(code, name))
                self.assertTrue(T.hand_written_problem(name, [obj], {"u.cpp": (code, None)}))


class NativeTransferProofTests(NativeCompilerCase):
    """The transfer proof on objects MSVC 7.1 really wrote: a template instance, a plain function under
    /Gy, data under a function's name, and objects that cannot be read."""
    INST = "??$f@H@@YAHH@Z"
    TEMPLATE = "template<class T> T f(T a) { return a + 1; }\n"
    USE = "int use(int a) { return f<int>(a); }\n"

    def obj(self, stem, text):
        return self.run_cl(stem, "#pragma optimize(\"\", on)\n" + text)

    def definitions(self, stem, text):
        found = T.coff_definitions(self.obj(stem, text))
        self.assertIsNotNone(found)
        return found

    def test_it_reads_what_the_compiler_wrote(self):
        found = self.definitions("instance", "#pragma inline_depth(0)\n" + self.TEMPLATE + self.USE)
        self.assertEqual(found[self.INST], (True, True, 2))                          # an instance: ANY, in code
        self.assertEqual(found["?use@@YAHH@Z"], (True, True, 1))                     # a plain function under /Gy
        found = self.definitions("data", '__declspec(selectany) int g = 1;\nint h = 2;\n')
        self.assertEqual(found["?g@@3HA"], (True, False, 2))
        self.assertEqual(found["?h@@3HA"][1], False)

    def test_a_weak_name_counts_as_defined(self):
        found = self.definitions("alternate", '#pragma comment(linker, "/alternatename:?x@@YAXXZ=?use@@YAHH@Z")\n' + self.TEMPLATE + self.USE)
        self.assertIn("?x@@YAXXZ", found)

    def test_an_object_it_cannot_read_is_not_an_empty_one(self):
        good = self.obj("readable", self.TEMPLATE + self.USE)
        self.assertIsNone(T.coff_definitions(good.with_name("missing.obj")))
        self.assertIsNone(T.coff_definitions(None))
        for stem, data in (("empty", b""), ("text", b"not an object at all"), ("cut", good.read_bytes()[:64]),
                           ("other_machine", b"\x64\x86" + good.read_bytes()[2:])):
            with self.subTest(stem=stem):
                bad = good.with_name(stem + ".obj")
                bad.write_bytes(data)
                self.assertIsNone(T.coff_definitions(bad))
                self.assertEqual(T.transfer_problem(self.INST, "d", "t", {"d": bad, "t": good}, {}),
                                 "d's object cannot be read: inconclusive")

    def test_a_real_vftable_is_portable_through_its_weak_slot(self):
        """What MSVC 7.1 writes for a class with an out-of-line virtual destructor and a ctor here."""
        text = "class V { public: V(); virtual ~V(); int m; };\nV::V() : m(0) {}\n"
        data = self.obj("real_table", "#pragma inline_depth(0)\n" + text).read_bytes()
        found = {k[0]: v for k, v in T.portable_comdat_contexts(data).items()}
        table = found["??_7V@@6B@"]
        self.assertEqual(table[2], ((0, 6, "??_EV@@UAEPAXI@Z"),))
        self.assertEqual(table[3][0][0], "??_EV@@UAEPAXI@Z")
        self.assertEqual(table[3][0][1][0], "??_GV@@UAEPAXI@Z")
        same = self.obj("real_table_again", "int other() { return 1; }\n#pragma inline_depth(0)\n" + text).read_bytes()
        self.assertEqual({k[0]: v for k, v in T.portable_comdat_contexts(same).items()}["??_7V@@6B@"], table)

    def test_the_handover_on_real_objects(self):
        with_use = self.obj("dest", "#pragma inline_depth(0)\n" + self.TEMPLATE + self.USE)
        without = self.obj("donor_after", "int other() { return 1; }\n")
        explicit = self.obj("donor_before", self.TEMPLATE + "template int f<int>(int);\n")
        plain = self.obj("plain", "int use(int a) { return a; }\n")
        self.assertIn(self.INST, T.coff_definitions(explicit))
        before = {self.INST: T.section_identity(with_use, self.INST)}
        self.assertIsNone(T.transfer_problem(self.INST, "d", "t", {"d": without, "t": with_use}, before))
        self.assertIn("still defines", T.transfer_problem(self.INST, "d", "t", {"d": explicit, "t": with_use}, before))
        self.assertIn("exactly one object", T.transfer_problem(self.INST, "d", "t", {"d": without, "x": explicit, "t": with_use}, before))
        self.assertIn("does not define", T.transfer_problem(self.INST, "d", "t", {"d": without, "t": plain}, before))
        self.assertIn("selected NODUPLICATES", T.transfer_problem("?use@@YAHH@Z", "d", "t", {"d": without, "t": plain}, before))

    ADDRESS = "??$a@H@@YAPAHXZ"

    def address_of(self, stem, name, before=""):
        return self.obj(stem, before + f"#pragma inline_depth(0)\nextern int {name};\ntemplate<class T> int *a() {{ return &{name}; }}\n"
                                       "int *use() { return a<int>(); }\n")

    def test_the_same_bytes_binding_another_global_refuse(self):
        """The review's repro: both objects hold b8 00000000 c3; only the relocation names g or h."""
        old, new = self.address_of("reloc_old", "g"), self.address_of("reloc_new", "h")
        self.assertEqual(self.build.read_object_symbol_bytes(old, self.ADDRESS, code_only=True)[0],
                         self.build.read_object_symbol_bytes(new, self.ADDRESS, code_only=True)[0])
        donor = self.obj("reloc_donor", "int stay() { return 1; }\n")
        before = {self.ADDRESS: T.section_identity(old, self.ADDRESS)}
        self.assertIn("differs from", T.transfer_problem(self.ADDRESS, "d", "t", {"d": donor, "t": new}, before))
        self.assertIsNone(T.transfer_problem(self.ADDRESS, "d", "t", {"d": donor, "t": old}, before))

    EH = ("struct D { ~D(); };\nvoid g();\n"
          "template<class T> T e(T a) { D d; g(); return a; }\n")
    INSTANCE = "??$e@H@@YAHH@Z"

    def test_a_moved_body_with_unwind_data_keeps_its_identity(self):
        """A real funclet: the compiler renumbers $L labels with the unit, and the identity holds across that."""
        use = "#pragma inline_depth(0)\n" + self.EH + "int use(int a) { return e<int>(a); }\n"
        old = self.run_cl("eh_old", use)
        new = self.run_cl("eh_new", "struct E { ~E(); };\nvoid g2();\nvoid other() { E a; g2(); E b; g2(); }\n" + use)
        self.assertIn(self.INSTANCE, T.coff_definitions(old))
        self.assertIsNotNone(T.section_identity(old, self.INSTANCE))
        self.assertEqual(T.section_identity(old, self.INSTANCE), T.section_identity(new, self.INSTANCE))


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


class MergeMapRegressionTests(unittest.TestCase):
    """Merge lane 2 (2026-11-07, re_attempts 68ced52f6d): a merge must not cost the map an
    approval or leave a row placed in a path it deletes; the map is rebuilt in memory after the move."""
    TU, MOVED, SIBLING = "Code/Behavior/BaseUpgrade.cpp", "Code/Upgrade/BaseUpgrade.cpp", "Code/Upgrade/Impl.cpp"

    def judge(self, before, after, accepted=None):
        """REAL_MAP_REGRESSIONS over map rows `before`, with tu_map.build returning `after`; (why, ledger built)."""
        ledger = [{"name": "?a@@YAXXZ", "target_rva": "0x00001000", "source": self.MOVED},
                  {"name": "?b@@YAXXZ", "target_rva": "0x00002000", "source": self.SIBLING},
                  {"name": "?c@@YAXXZ", "target_rva": "0x00003000", "source": "Code/Other.cpp"}]
        built = []
        row = lambda rva, conf, tu, kind="code": {"rva": rva, "size": "8", "kind": kind, "tu": tu, "confidence": conf,
                                                  "by": "N", "evidence": "", "source": ""}
        with patch.object(T, "map_rows", return_value=[row(*b) for b in before]), \
                patch.object(T.tu_map, "read_csv", return_value=ledger), \
                patch.object(T.tu_map, "build", side_effect=lambda layout, led: built.append(led) or [row(*a) for a in after]):
            why = REAL_MAP_REGRESSIONS(self.TU, accepted or [self.MOVED])
        return why, built[0]

    def test_an_unchanged_map_passes_and_the_ledger_is_repointed_for_the_accepted_files_only(self):
        rows = [("0x00001000", "approved", self.TU), ("0x00002000", "approved", self.TU)]
        why, ledger = self.judge(rows, rows)
        self.assertIsNone(why)
        self.assertEqual([r["source"] for r in ledger], [self.TU, self.SIBLING, "Code/Other.cpp"])

    def test_the_baseupgrade_repro_refuses(self):
        # the sibling 0x004B37CA drops from approved to proposed for the path the move leaves; its funclets
        # stay approved for the deleted path
        before = [("0x00001000", "approved", self.TU), ("0x00002000", "approved", self.TU),
                  ("0x00002100", "approved", self.TU, "code-interior")]
        after = [("0x00001000", "approved", self.TU), ("0x00002000", "proposed", self.MOVED),
                 ("0x00002100", "approved", self.MOVED, "code-interior")]
        why, _ = self.judge(before, after)
        self.assertIn("1 lowered: 0x00002000 approved", why)
        self.assertIn("2 placed in a path it deletes", why)

    def test_each_kind_of_loss_refuses(self):
        cases = [([("0x00002000", "approved", self.TU)], [("0x00002000", "displaced", "")], "lowered"),
                 ([("0x00002000", "proposed", self.TU)], [("0x00002000", "displaced", "")], "lowered"),
                 ([("0x00002000", "displaced", "")], [("0x00002000", "", "")], "lowered"),
                 ([("0x00002000", "approved", self.TU)], [], "lowered"),                    # gone from the map
                 ([("0x00002000", "approved", self.TU)], [("0x00002000", "approved", self.MOVED)], "deletes"),
                 ([("0x00002000", "proposed", self.SIBLING)], [("0x00002000", "proposed", self.MOVED.upper())],
                  "deletes")]
        for before, after, word in cases:
            with self.subTest(before=before, after=after):
                why, _ = self.judge(before, after)
                self.assertIn(word, why)

    def test_gains_and_untouched_paths_pass(self):
        for before, after in (([("0x00002000", "proposed", self.SIBLING)], [("0x00002000", "approved", self.TU)]),
                              ([("0x00002000", "", "")], [("0x00002000", "proposed", self.SIBLING)]),
                              ([("0x00002000", "approved", self.SIBLING)], [("0x00002000", "approved", self.SIBLING)]),
                              ([("0x00002000", "displaced", "")], [("0x00002000", "displaced", self.MOVED)])):
            with self.subTest(before=before, after=after):
                self.assertIsNone(self.judge(before, after)[0])

    def test_a_merge_and_a_reused_plan_refuse_before_writing(self):
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}], donor: [{"target_rva": "0x1010"}]}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors, all_errors, flags = [], [], None

            def __init__(self, *a, **k):
                self.obj = "compiled.obj"

            def matched(self, text, rows):
                return {r["target_rva"] for r in rows}

            def effective(self, text, rows):
                return text

        class Guard:
            def __init__(self, *a):
                pass

            def load(self):
                pass

            def linked(self, files):
                return []

            def prepare(self, files):
                return None

            def judge(self, obj, files, text):
                return []

        carry = SimpleNamespace(report=lambda: {}, problems=[])
        asked = []
        for dry_run in (True, False):
            with self.subTest(dry_run=dry_run), patch.object(T, "Verifier", Verifier), patch.object(T, "LinkGuard", Guard), \
                    patch.object(T, "compose", return_value="composed"), patch.object(T, "Carry", return_value=carry), \
                    patch.object(T, "map_regressions", side_effect=lambda t, acc: asked.append((t, list(acc))) or "lost"), \
                    patch.object(T, "apply") as apply:
                out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, dry_run, texts=texts)
                self.assertEqual(out["blocked"], "lost")
                self.assertNotIn("_plan", out)                    # nothing saved to reuse
                apply.assert_not_called()
        self.assertEqual(asked[-1], (tu, [tu, donor]))
        plan = {"accepted": [donor], "text": "merged", "baseline": ["0x1010"], "rows": 1, "rejected": {},
                "flags": [], "verifier_flags": None}
        with tempfile.TemporaryDirectory() as folder, patch.object(T, "ROOT", Path(folder)):
            (Path(folder) / donor).parent.mkdir(parents=True)
            (Path(folder) / donor).write_text("int a;\n")
            with patch.object(T, "Verifier", Verifier), patch.object(T, "LinkGuard", Guard), \
                    patch.object(T, "Carry", return_value=carry), \
                    patch.object(T, "map_regressions", return_value="lost"), patch.object(T, "apply") as apply:
                out = T.reuse_merge_plan(tu, {donor: don[donor]}, {}, plan, False)
            self.assertEqual(out["blocked"], "lost")
            apply.assert_not_called()


class MergeDiagnosticReasonTests(unittest.TestCase):
    """Merge lane 2 (2026-11-07): a reused or failed candidate reported `compile: ` with nothing after it."""

    def test_the_reason_quotes_the_compile_that_failed_not_the_last_one(self):
        # two composition strategies: the first fails to compile (C2011), the second compiles but loses bytes;
        # the reason was read after the second, with no errors left
        tu, donor = "Code/T.cpp", "Code/A.cpp"
        texts = {tu: "seed", donor: "donor"}
        don = {tu: [{"target_rva": "0x1000"}], donor: [{"target_rva": "0x1010"}]}

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors, all_errors, flags = [], [], None

            def matched(self, text, rows):
                rvas = {r["target_rva"] for r in rows}
                if "A.cpp" not in text:
                    self.errors = self.all_errors = []
                    return rvas
                if text.endswith("FAIL"):
                    self.errors = self.all_errors = ["t.cpp(3) : error C2011: 'BaseUpgrade' : 'class' type redefinition"]
                    return None
                self.errors = self.all_errors = []
                return rvas - {"0x1010"}

        def compose(tu_, sk, files, texts_, flags, st, *a):
            return " ".join(files) + (" FAIL" if st == T.STRATEGIES[0] else f" {st}")

        with patch.object(T, "Verifier", return_value=Verifier()), patch.object(T, "compose", side_effect=compose), \
                patch.object(T, "apply") as apply:
            out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts=texts)
        self.assertIn("C2011", out["rejected"][donor])
        apply.assert_not_called()

    def plan_file(self, folder, rejected, version=None):
        path = Path(folder) / "plan.json"
        path.write_text(json.dumps({"version": T.PLAN_VERSION if version is None else version, "state": "s",
                                    "inputs": "i", "accepted": ["Code/A.cpp"], "rejected": rejected}))
        return path

    def test_a_plan_with_an_empty_reason_is_dropped(self):
        with tempfile.TemporaryDirectory() as folder:
            for reason in ("compile: ", "compile:", "link:  ", " compile : "):
                with self.subTest(reason=reason):
                    path = self.plan_file(folder, {"Code/B.cpp": reason})
                    self.assertIsNone(T.load_verified_plan(path, "s", "i"))
                    self.assertFalse(path.exists())
            for rejected in ({"Code/B.cpp": "compile: b.cpp(1) : error C2065"}, {"Code/B.cpp": "bytes"}, {}, ["odd"]):
                with self.subTest(rejected=rejected):
                    path = self.plan_file(folder, rejected)
                    self.assertIsNotNone(T.load_verified_plan(path, "s", "i"))
                    self.assertTrue(path.exists())

    def test_a_plan_saved_before_the_fix_is_searched_again(self):
        with tempfile.TemporaryDirectory() as folder:
            self.assertIsNone(T.load_verified_plan(self.plan_file(folder, {}, version=1), "s", "i"))
            path = Path(folder) / "saved.json"
            with patch.object(T, "merge_plan_state", return_value="s"):
                T.save_verified_plan(path, "s", "i", {"accepted": ["Code/A.cpp"], "rejected": {}})
            self.assertEqual(json.loads(path.read_text())["version"], T.PLAN_VERSION)
            self.assertIsNotNone(T.load_verified_plan(path, "s", "i"))


class MapGuardOnEveryDeletingPathTests(unittest.TestCase):
    """Review of 0c96be95a9: a prepared whole-donor split reached apply() with no map check, and a reused
    plan the check blocked kept its claims."""
    TU, DONOR = "Code/New/A.cpp", "Code/Old/B.cpp"

    class Verifier:
        errors, all_errors, flags, obj = [], [], None, "fake.obj"
        fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})

        def __init__(self, *a, **k):
            pass

        def matched(self, text, rows):
            return {r["target_rva"] for r in rows}

        def effective(self, text, rows):
            return text

    class Guard:
        def __init__(self, *a, **k):
            pass

        def load(self):
            pass

        def linked(self, *a):
            return []

        def prepare(self, *a):
            return None

        def judge(self, *a):
            return []

    def real_tree(self, root):
        """The review's fixture: the two classes interleave, A's files under Code/New/, B's under Code/Old/;
        all four rows approve Code/New/A.cpp until B.cpp alone moves."""
        specs = [("A", "f", "0x00001000", self.TU), ("B", "f", "0x00001010", self.DONOR),
                 ("A", "g", "0x00001018", "Code/New/A2.cpp"), ("B", "g", "0x00001020", "Code/Old/B2.cpp")]
        rows = [dict(name=f"?{m}@{c}@@QAEXXZ", target_rva=r, target_size="8", source=s, notes="", status="matched",
                     export_rva="") for c, m, r, s in specs]
        (root / "reverse").mkdir()
        (root / "zh/GameEngine").mkdir(parents=True)
        for c, m, _r, s in specs:
            (root / s).parent.mkdir(parents=True, exist_ok=True)
            (root / s).write_text(f"void {c}::{m}() {{}}\n")
        with (root / "reverse/functions.csv").open("w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(rows[0]))
            w.writeheader()
            w.writerows(rows)
        return rows

    def test_absorbing_a_whole_donor_is_refused_on_the_real_map_logic(self):
        import tu_evidence
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            rows = self.real_tree(root)
            layout = T.tu_map.Layout(root, root / "zh")
            prepared = "void A::f() {}\nvoid B::f() {}\n"
            carry = SimpleNamespace(problems=[], report=lambda: {})
            for dry_run in (True, False):
                with self.subTest(dry_run=dry_run), patch.object(T, "ROOT", root), \
                        patch.object(T, "LEDGER", root / "reverse/functions.csv"), patch.object(T, "LAYOUT", layout), \
                        patch.dict(T._CACHE, {}, clear=True), patch.object(tu_evidence, "PROMOTED", set()), \
                        patch.object(T, "merge_plan_state", return_value=None), patch.object(T, "refusal", return_value=None), \
                        patch.object(T, "included_by", return_value=[]), \
                        patch.object(T, "map_rows", return_value=[{k: str(v) for k, v in r.items()} for r in T.tu_map.build(layout, rows)]), \
                        patch.object(T, "Verifier", self.Verifier), patch.object(T, "LinkGuard", self.Guard), \
                        patch.object(T, "Carry", return_value=carry), patch.object(T, "apply", return_value={}) as write, \
                        patch.object(T, "map_regressions", side_effect=REAL_MAP_REGRESSIONS) as check:
                    report = T.split(self.DONOR, self.TU, dry_run=dry_run, prepared=prepared, claim=False)
                    self.assertEqual(check.call_count, 1)
                    self.assertIn("0x00001020", report["blocked"])
                    self.assertIn("this move would cost the map approvals", report["blocked"])
                    write.assert_not_called()

    def merge_with_applier(self, deletes_donor, why="lost approval", dry_run=False):
        don = {self.TU: [{"target_rva": "0x00001000"}], self.DONOR: [{"target_rva": "0x00001010"}]}
        applied = []
        with patch.object(T, "Verifier", self.Verifier), \
                patch.object(T, "map_regressions", return_value=why) as check:
            out = T._merge(self.TU, [], don, {"accepted": [], "rejected": {}}, dry_run, texts={f: "x" for f in don},
                           applier=lambda tu, acc, text: applied.append(acc) or {}, guard=self.Guard(),
                           fixed_text="prepared", deletes_donor=deletes_donor)
        return out, check, applied

    def test_only_an_applier_that_deletes_its_donors_is_judged(self):
        for dry_run in (True, False):
            with self.subTest(dry_run=dry_run):
                out, check, applied = self.merge_with_applier(True, dry_run=dry_run)
                self.assertEqual(out["blocked"], "lost approval")
                check.assert_called_once_with(self.TU, [self.TU, self.DONOR])
                self.assertEqual(applied, [])
        out, check, applied = self.merge_with_applier(True, why=None)
        self.assertNotIn("blocked", out)
        self.assertEqual(applied, [[self.TU, self.DONOR]])                          # an unchanged map: it applies
        out, check, applied = self.merge_with_applier(False)                        # told nothing it moves
        self.assertNotIn("blocked", out)
        check.assert_not_called()
        self.assertEqual(len(applied), 1)

    # ------------------------------------------------------------------ a move that leaves its file in place
    def partial_tree(self, root):
        """The review's fixture and C::h, kept in Code/Old/B.cpp, so moving B::f leaves its file in place."""
        rows = self.real_tree(root)
        for c, m, rva, source in (("C", "h", "0x00009000", self.DONOR), ("C", "i", "0x00009010", "Code/Else/C.cpp")):
            rows.append(dict(name=f"?{m}@{c}@@QAEXXZ", target_rva=rva, target_size="8", source=source, notes="",
                             status="matched", export_rva=""))
            (root / source).parent.mkdir(parents=True, exist_ok=True)
            with (root / source).open("a") as f:
                f.write(f"void {c}::{m}() {{}}\n")
        with (root / "reverse/functions.csv").open("w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(rows[0]))
            w.writeheader()
            w.writerows(rows)
        return rows

    def partial_split(self, root, rows, dry_run, plan=None):
        import tu_evidence
        layout = T.tu_map.Layout(root, root / "zh")
        carry = SimpleNamespace(problems=[], raws={}, moved={}, report=lambda: {})
        current = [{k: str(v) for k, v in r.items()} for r in T.tu_map.build(layout, rows)]
        with patch.multiple(T, ROOT=root, LEDGER=root / "reverse/functions.csv", LAYOUT=layout, Verifier=self.Verifier,
                            LinkGuard=self.Guard, SplitLinkGuard=self.Guard), \
                patch.dict(T._CACHE, {}, clear=True), patch.object(tu_evidence, "PROMOTED", set()), \
                patch.multiple(T, refusal=lambda *a: None, included_by=lambda *a: [], map_rows=lambda: current,
                               carry_unit_keys=lambda *a, **k: carry, merge_plan_state=lambda: "s" if plan else None,
                               load_verified_plan=lambda *a: plan), \
                patch.object(T, "apply_split", return_value={}) as write, \
                patch.object(T, "map_regressions", side_effect=REAL_MAP_REGRESSIONS) as check:
            report = T.split(self.DONOR, self.TU, dry_run=dry_run, prepared="void A::f() {}\nvoid B::f() {}\n" if not plan else None,
                             claim=False)
            return report, check, write

    def test_a_partial_split_that_costs_a_sibling_its_approval_is_refused(self):
        # review of dee0813e84, on the real map logic: splitting B::f out drops B::g to proposed
        for dry_run in (True, False):
            with self.subTest(dry_run=dry_run), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                report, check, write = self.partial_split(root, self.partial_tree(root), dry_run)
                self.assertEqual(check.call_count, 1)
                self.assertEqual(check.call_args.kwargs["moved_rows"], {self.DONOR: ["0x00001010"]})
                self.assertIn("this move would cost the map approvals", report["blocked"])
                self.assertIn("0x00001020 approved", report["blocked"].lower())
                write.assert_not_called()

    def row_level(self, before, after, moved_rows):
        ledger = [{"name": "a", "target_rva": "0x00001000", "source": self.DONOR},
                  {"name": "b", "target_rva": "0x00001010", "source": self.DONOR},
                  {"name": "alias", "target_rva": "0x00001000", "source": "Code/Other.cpp"},
                  {"name": "no-address", "target_rva": "", "source": self.DONOR}]
        built = []
        row = lambda rva, conf, tu: {"rva": rva, "size": "8", "kind": "code", "tu": tu, "confidence": conf, "by": "N",
                                     "evidence": "", "source": ""}
        with patch.object(T, "map_rows", return_value=[row(*b) for b in before]), patch.object(T.tu_map, "read_csv", return_value=ledger), \
                patch.object(T.tu_map, "build", side_effect=lambda layout, led: built.append(led) or [row(*a) for a in after]):
            return REAL_MAP_REGRESSIONS(self.TU, moved_rows=moved_rows), built[0]

    def test_row_level_moves_repoint_only_those_rows_of_that_file(self):
        rows = [("0x00001000", "approved", self.TU)]
        why, ledger = self.row_level(rows, rows, {self.DONOR: ["0X00001000"]})     # any spelling of the address
        self.assertIsNone(why)
        self.assertEqual([r["source"] for r in ledger], [self.TU, self.DONOR, "Code/Other.cpp", self.DONOR])

    def test_a_row_level_move_deletes_no_path(self):
        # its file stays, so a row the map still places there is no orphan; only a lower confidence refuses
        why, _ = self.row_level([("0x00001010", "approved", self.DONOR)], [("0x00001010", "approved", self.DONOR)],
                                {self.DONOR: ["0x00001000"]})
        self.assertIsNone(why)
        why, _ = self.row_level([("0x00001010", "approved", self.TU)], [("0x00001010", "proposed", self.DONOR)],
                                {self.DONOR: ["0x00001000"]})
        self.assertIn("1 lowered: 0x00001010 approved", why)
        self.assertNotIn("deletes", why)

    def test_a_saved_split_plan_is_judged_too(self):
        guard = SimpleNamespace(load=lambda: None, prepare=lambda d: None, judge=lambda *a: [])
        plan = {"tu_file": self.TU, "accepted": [self.DONOR], "text": "t", "baseline": ["0x00001010"], "rows": 1,
                "flags": [], "rejected": {}}
        don = {self.DONOR: [{"target_rva": "0x00001010"}]}
        applied = []
        with patch.object(T, "Verifier", self.Verifier), patch.object(T, "merge_plan_state", return_value="s"), \
                patch.object(T, "map_regressions", return_value="lost approval") as check:
            out = T.reuse_split_plan(self.TU, don, {}, plan, False, guard, lambda *a: applied.append(a) or {}, "s",
                                     moved_rows={self.DONOR: ["0x00001010"]})
        self.assertEqual(out["blocked"], "lost approval")
        check.assert_called_once_with(self.TU, moved_rows={self.DONOR: ["0x00001010"]})
        self.assertEqual(applied, [])

    def held(self):
        held = T.Held()
        held.acquired = [T.claims.key_of(f"file:{self.TU}"), T.claims.key_of("0x00001010")]
        held.tokens = {k: f"token-{k}" for k in held.acquired}
        return held

    @contextlib.contextmanager
    def saved_plan(self):
        don = {self.TU: [{"target_rva": "0x00001000"}], self.DONOR: [{"target_rva": "0x00001010"}]}
        plan = {"tu_file": self.TU, "accepted": list(don), "text": "merged", "baseline": ["0x00001000", "0x00001010"],
                "rows": 2, "rejected": {}, "flags": [], "verifier_flags": None}
        with tempfile.TemporaryDirectory() as tmp, patch.object(T, "ROOT", Path(tmp)), \
                patch.object(T, "merge_plan_state", return_value="s"), patch.object(T, "skeleton", return_value=[]), \
                patch.object(T, "donors", return_value=(don, {}, {})), patch.object(T, "tu_path", side_effect=lambda x: x), \
                patch.object(T, "header_queue_rows", return_value={}), patch.object(T, "load_merge_plan", return_value=plan), \
                patch.object(T, "view_hint", side_effect=lambda r, *a: r), patch.object(T, "claim_scope", side_effect=lambda *a, **k: self.held()), \
                patch.object(T, "Verifier", self.Verifier), patch.object(T, "LinkGuard", self.Guard), \
                patch.object(T, "Carry", return_value=SimpleNamespace(problems=[], report=lambda: {})), \
                patch.object(T, "apply", return_value={}) as write, patch.object(T.claims, "release") as release:
            for f in don:
                (Path(tmp) / f).parent.mkdir(parents=True, exist_ok=True)
                (Path(tmp) / f).write_text("int a;\n")
            yield release, write

    def test_a_reused_plan_the_map_blocks_gives_back_its_claims(self):
        held = self.held()
        with self.saved_plan() as (release, write), patch.object(T, "map_regressions", return_value="lost approval"):
            out = T.merge(self.TU)
            self.assertEqual(out["blocked"], "lost approval")
            release.assert_called_once_with(list(held.acquired), tokens=dict(held.tokens))
            write.assert_not_called()

    def test_a_reused_plan_that_applies_or_a_dry_run_keeps_its_claims(self):
        with self.saved_plan() as (release, write), patch.object(T, "map_regressions", return_value=None):
            out = T.merge(self.TU)
            self.assertNotIn("blocked", out)
            self.assertTrue(out["plan_reused"])
            write.assert_called_once()
            release.assert_not_called()                                             # a landed merge settles them
        with self.saved_plan() as (release, write), patch.object(T, "map_regressions", return_value="lost approval"):
            out = T.merge(self.TU, dry_run=True)
            self.assertEqual(out["blocked"], "lost approval")
            release.assert_not_called()                                             # a dry run claimed nothing

    def test_a_fresh_search_the_map_blocks_gives_back_its_claims(self):
        # the other return the guard reaches: no saved plan, so _merge itself is blocked
        held = self.held()
        with self.saved_plan() as (release, write), patch.object(T, "load_merge_plan", return_value=None), \
                patch.object(T, "compose", return_value="composed"), \
                patch.object(T, "map_regressions", return_value="lost approval"):
            out = T.merge(self.TU)
            self.assertEqual(out["blocked"], "lost approval")
            release.assert_called_once_with(list(held.acquired), tokens=dict(held.tokens))
            write.assert_not_called()
    # ------------------------------------------------------------------ an exception after the claim
    def released_once(self, release):
        held = self.held()
        release.assert_called_once_with(list(held.acquired), tokens=dict(held.tokens))

    def test_a_reused_plan_raising_gives_back_its_claims(self):
        # review of dee0813e84: only what this call took, fenced, and the exception goes on
        with self.saved_plan() as (release, write), patch.object(T, "reuse_merge_plan", side_effect=OSError("read failed")):
            with self.assertRaises(OSError):
                T.merge(self.TU)
            self.released_once(release)
            write.assert_not_called()

    def test_a_fresh_search_raising_gives_back_its_claims(self):
        with self.saved_plan() as (release, write), patch.object(T, "load_merge_plan", return_value=None), \
                patch.object(T, "_merge", side_effect=KeyboardInterrupt):
            with self.assertRaises(KeyboardInterrupt):
                T.merge(self.TU)
            self.released_once(release)

    def test_the_wider_claim_is_given_back_with_the_first(self):
        first, second = self.held(), T.Held()
        key = T.claims.key_of(f"file:{self.DONOR}")
        second.acquired, second.tokens = [key], {key: "SECOND"}
        with self.saved_plan() as (release, write), \
                patch.object(T, "load_merge_plan", return_value={"tu_file": self.TU, "accepted": [self.TU]}), \
                patch.object(T, "reuse_merge_plan", return_value=None), patch.object(T, "claim_scope", side_effect=[first, second]), \
                patch.object(T, "_merge", side_effect=OSError("disk")):
            with self.assertRaises(OSError):
                T.merge(self.TU)
            release.assert_called_once_with(first.acquired + [key], tokens={**first.tokens, key: "SECOND"})

    def test_a_claim_held_before_this_call_survives_an_exception(self):
        nothing_new = T.Held()                                  # every key was this worker's already (prior)
        with self.saved_plan() as (release, write), patch.object(T, "claim_scope", return_value=nothing_new), \
                patch.object(T, "reuse_merge_plan", side_effect=OSError("read failed")):
            with self.assertRaises(OSError):
                T.merge(self.TU)
            release.assert_not_called()

    def test_a_failing_release_never_masks_the_exception(self):
        with self.saved_plan() as (release, write), patch.object(T, "reuse_merge_plan", side_effect=OSError("read failed")), \
                contextlib.redirect_stderr(io.StringIO()) as err:
            release.side_effect = RuntimeError("origin down")
            with self.assertRaises(OSError):
                T.merge(self.TU)
            self.assertIn("were not given back", err.getvalue())

    def test_a_write_that_started_keeps_its_claims(self):
        # no journal for a merge: the half-written tree is restored by hand, and its files stay claimed meanwhile
        carry = SimpleNamespace(problems=[], report=lambda: {}, hatch=False)
        with self.saved_plan() as (release, write), patch.object(T, "apply", REAL_APPLY), patch.object(T, "Carry", return_value=carry), \
                patch.object(T, "map_regressions", return_value=None), patch.object(T, "repoint_all", side_effect=OSError("disk full")), \
                contextlib.redirect_stderr(io.StringIO()) as err:
            with self.assertRaises(OSError) as caught:
                T.merge(self.TU)
            self.assertTrue(caught.exception.half_applied)
            release.assert_not_called()
            self.assertIn("the claims stay held", err.getvalue())
            self.assertIn("git restore", err.getvalue())

    def test_a_refusal_before_the_first_write_gives_back(self):
        carry = SimpleNamespace(problems=[], report=lambda: {}, hatch=True)
        with self.saved_plan() as (release, write), patch.object(T, "apply", REAL_APPLY), patch.object(T, "Carry", return_value=carry), \
                patch.object(T, "map_regressions", return_value=None), patch.object(T, "dirty_others", return_value=["Code/Other.cpp"]), \
                patch.object(T, "repoint_all") as repoint:
            with self.assertRaises(SystemExit) as caught:
                T.merge(self.TU)
            self.assertFalse(getattr(caught.exception, "half_applied", False))
            repoint.assert_not_called()
            self.released_once(release)

    def test_an_applied_merge_keeps_its_claims_whatever_follows(self):
        with self.saved_plan() as (release, write), patch.object(T, "map_regressions", return_value=None), \
                patch.object(T, "view_hint", side_effect=RuntimeError("after the write")):
            with self.assertRaises(RuntimeError):
                T.merge(self.TU)
            write.assert_called_once()
            release.assert_not_called()

    def test_each_writer_marks_what_escapes_it(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            with self.assertRaises(FileNotFoundError) as caught:
                T.apply_shatter("Code/M.cpp", {}, {"reverse/missing.csv": b"x"}, False, root=root)
            self.assertTrue(caught.exception.half_applied)
            with patch.object(T.subprocess, "run", side_effect=OSError("no git")), self.assertRaises(OSError) as caught:
                T.apply_split(self.TU, "text", self.DONOR, "residual", [], False, root=root)
            self.assertTrue(caught.exception.half_applied)
            with patch.object(T, "dirty_others", return_value=["x"]), self.assertRaises(T.NothingWritten) as caught:
                T.apply_shatter("Code/M.cpp", {}, {}, True, root=root)
            self.assertFalse(hasattr(caught.exception, "half_applied"))
            dirty = SimpleNamespace(stdout=" M Code/Other.cpp\n")
            with patch.object(T.subprocess, "run", return_value=dirty), self.assertRaises(T.NothingWritten):
                T.apply_split(self.TU, "text", self.DONOR, "residual", [], True, root=root)

    def test_a_shatter_gives_back_before_its_first_write_and_not_after(self):
        args = ("Code/M.cpp", [self.TU], [{"target_rva": "0x00001000"}], {}, {}, False)
        cases = ((OSError("before"), False, True), (OSError("during"), True, False))
        for error, started, released in cases:
            with self.subTest(error=error):
                if started:
                    error.half_applied = True
                with patch.object(T, "claim_scope", return_value=self.held()), patch.object(T, "apply_shatter", side_effect=error), \
                        patch.object(T.claims, "release") as release, contextlib.redirect_stderr(io.StringIO()), self.assertRaises(OSError):
                    T.write_shatter({}, *args, claim=True)
                self.assertEqual(release.called, released)
        refused = T.Held(["file:Code/M.cpp"])
        refused.acquired, refused.tokens = ["k"], {"k": "T"}
        report = {}
        with patch.object(T, "claim_scope", return_value=refused), patch.object(T, "apply_shatter") as write, \
                patch.object(T.claims, "release") as release:
            self.assertFalse(T.write_shatter(report, *args, claim=True))
        self.assertIn("held by another worker", report["blocked"])
        write.assert_not_called()
        release.assert_called_once_with(["k"], tokens={"k": "T"})
        with patch.object(T, "claim_scope") as claimed, patch.object(T, "apply_shatter", return_value=["x"]):
            report = {}
            self.assertTrue(T.write_shatter(report, *args, claim=False))
            self.assertEqual(report["staged"], ["x"])
            claimed.assert_not_called()


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

    def test_a_compile_failing_without_an_error_line_still_says_why(self):
        # Merge lane 2 (2026-11-07): only ` error ` lines were kept, so such a failure read `compile: `
        with tempfile.TemporaryDirectory() as tmp:
            v, _ = self.verifier(Path(tmp))
            v.B.try_compile_source = lambda src, obj, timeout=None: (False, "cl.exe\nwine: Unhandled page fault\n", 3)
            self.assertIsNone(v.matched("crash", self.ROWS))
            self.assertEqual(v.errors, ["cl.exe", "wine: Unhandled page fault"])
            v.B.try_compile_source = lambda src, obj, timeout=None: (False, "", 3)
            self.assertIsNone(v.matched("silent", self.ROWS))
            self.assertEqual(v.errors, ["the compiler exited 3 with no output"])
            v.B.try_compile_source = lambda src, obj, timeout=None: (False, "noise\nb.cpp(1) : error C2065: x\n", 2)
            self.assertIsNone(v.matched("real", self.ROWS))
            self.assertEqual(v.errors, ["b.cpp(1) : error C2065: x"])

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
        self.assertIn("C2065", out["rejected"][tu])
        self.assertEqual(out["rejected"][donor], T.SEED_NOT_TRIED)
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
        self.assertEqual(out["rejected"], {tu: "compile timeout", donor: T.SEED_NOT_TRIED})
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

    @staticmethod
    def weak_table(default="??_Gx@@", selection=2, tag_at=None, alias=None, another_weak=False, characteristics=2,
                   slot="??_Ex@@"):
        """A vftable's shape: a data COMDAT with one DIR32 to weak `slot`, whose default is `default`,
        a code COMDAT here selected `selection`."""
        import struct
        from test_gate_exploits import coff, TEXT
        sections = [(".rdata", 0x40001040, b"\0\0\0\0", [(0, 6, 6)]),
                    (".text", TEXT | 0x1000, b"\xc3", [])]
        if alias:
            sections.append((".drectve", 0x00100A00, f" /alternatename:{alias}=other".encode(), []))
        symbols = [(".rdata", 0, 1, 0, 3, 1), ("??_7x@@", 0, 1, 0, 2, 0),
                   (".text", 0, 2, 0, 3, 1), (default, 0, 2, 0x20, 2, 0),
                   (slot, 0, 0, 0x20, 105, 1)]
        if another_weak:
            symbols.append((slot, 0, 0, 0x20, 105, 1))
        data = bytearray(coff(sections, symbols))
        table = struct.unpack_from("<I", data, 8)[0]
        data[table + 18 + 14] = 2
        data[table + 18 * 4 + 14] = selection
        struct.pack_into("<II", data, table + 18 * 7, 5 if tag_at is None else tag_at, characteristics)
        if another_weak:
            struct.pack_into("<II", data, table + 18 * 9, 5, characteristics)
        return bytes(data)

    def test_portable_context_names_a_compilers_weak_slot_and_its_default(self):
        import link_census as LCe
        data = self.weak_table()
        found = T.portable_comdat_contexts(data)
        table = [v for k, v in found.items() if k[0] == "??_7x@@"]
        self.assertEqual(len(table), 1)
        digest = next(d for s, _b, _r, d, _ in LCe._comdat_sections(data) if s["name"] == "??_Gx@@")
        self.assertEqual(table[0][2], ((0, 6, "??_Ex@@"),))
        self.assertEqual(table[0][3], (("??_Ex@@", ("??_Gx@@", digest)),))

    def test_portable_context_refuses_a_weak_slot_it_cannot_follow(self):
        for label, options in (("default selected otherwise", {"selection": 1}), ("default not a body here", {"tag_at": 0}),
                               ("the slot redirected", {"alias": "??_Ex@@"}), ("the default redirected", {"alias": "??_Gx@@"}),
                               ("two weak records of the slot", {"another_weak": True}),
                               ("Characteristics 0", {"characteristics": 0}), ("Characteristics 1", {"characteristics": 1}),
                               ("Characteristics 3", {"characteristics": 3}), ("Characteristics 4", {"characteristics": 4}),
                               ("Characteristics of all ones", {"characteristics": 0xFFFFFFFF}),
                               ("another class's default", {"default": "??_Gy@@"}),
                               ("a slot that is not ??_E", {"slot": "_slot", "default": "_del"}),
                               ("??_E defaulting elsewhere", {"default": "_del"}),
                               ("??_G as the slot", {"slot": "??_Gx@@", "default": "??_Ex@@"})):
            with self.subTest(label=label):
                found = T.portable_comdat_contexts(self.weak_table(**options))
                self.assertEqual([k for k in found if k[0] == "??_7x@@"], [])

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

    def obj(self, stem, defined=(), refs=(), copies=(), aliases=(), common=(), tables=(), characteristics=2):
        """`tables`: (table, weak slot, its default, the default's body), a vftable's shape, each a COMDAT selected ANY."""
        import struct
        from test_gate_exploits import coff, TEXT
        sections, symbols, aux_at, tags = [], [], [], []
        for name in defined:
            sections.append((".text", TEXT, b"\xc3", []))
            symbols.append((name, 0, len(sections), 0x20, 2, 0))
        for name, body in copies:
            sections.append((".text", TEXT | 0x1000, body, []))
            aux_at.append(sum(1 + s[-1] for s in symbols) + 1)
            symbols.extend([(".text", 0, len(sections), 0, 3, 1),
                            (name, 0, len(sections), 0x20, 2, 0)])
        for table, slot, default, body in tables:
            sections.append((".text", TEXT | 0x1000, body, []))
            aux_at.append(sum(1 + s[-1] for s in symbols) + 1)
            symbols.append((".text", 0, len(sections), 0, 3, 1))
            target = sum(1 + s[-1] for s in symbols)
            symbols.append((default, 0, len(sections), 0x20, 2, 0))
            sections.append((".rdata", 0x40001040, b"\0\0\0\0", [(0, target + 4, 6)]))
            aux_at.append(sum(1 + s[-1] for s in symbols) + 1)
            symbols.extend([(".rdata", 0, len(sections), 0, 3, 1), (table, 0, len(sections), 0, 2, 0),
                            (slot, 0, 0, 0x20, 105, 1)])
            tags.append((target + 4, target))
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
        for weak, tag in tags:
            struct.pack_into("<II", raw, table + 18 * (weak + 1), tag, characteristics)
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

    SLOT, DEFAULT = "??_Ex@@", "??_Gx@@"
    TABLE = ("_tab", SLOT, DEFAULT, b"\xc3")
    REFUSED = "lacks matching private/weak-free context"

    def table_guard(self, verdict="retail"):
        self.truth.verdict = lambda symbol, *rest: verdict if symbol["name"] == self.DEFAULT else None
        return self.setup_guard(source_options=dict(tables=(self.TABLE,)), outside_options=dict(refs=("_tab",)))

    def test_a_moved_table_is_proven_through_its_weak_slot(self):
        # The false reject on ??_7Rva0056616B@@6B@: one table, one default, its body proven retail.
        self.table_guard()
        self.assertEqual(self.judge(destination_options=dict(tables=(self.TABLE,))), [])

    def test_a_moved_table_whose_default_is_not_proven_retail_refuses(self):
        for verdict, label in ((None, "the default is not proven"), ("wrong", "the default is proven wrong")):
            with self.subTest(label=label):
                self.table_guard(verdict)
                why = self.judge(destination_options=dict(tables=(self.TABLE,)))
                self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_a_moved_table_may_not_change_its_slots_route(self):
        for label, table in (("another default", ("_tab", self.SLOT, "??_Gy@@", b"\xc3")),
                             ("another body of the default", ("_tab", self.SLOT, self.DEFAULT, b"\x90\xc3"))):
            with self.subTest(label=label):
                self.table_guard()
                why = self.judge(destination_options=dict(tables=(table,)))
                self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_weak_characteristics_the_linker_would_not_resolve_refuse(self):
        # The review's repro: 0xFFFFFFFF, 0 and 4 passed the guard and fail LINK (LNK2001/LNK1120).
        for characteristics in (0, 1, 3, 4, 0xFFFFFFFF):
            with self.subTest(characteristics=characteristics):
                self.table_guard()
                why = self.judge(destination_options=dict(tables=(self.TABLE,), characteristics=characteristics))
                self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_a_slot_that_is_not_the_compilers_refuses_though_it_moved_unchanged(self):
        self.truth.verdict = lambda symbol, *rest: "retail" if symbol["name"] == "_del" else None
        table = ("_tab", "_slot", "_del", b"\xc3")
        self.setup_guard(source_options=dict(tables=(table,)), outside_options=dict(refs=("_tab",)))
        why = self.judge(destination_options=dict(tables=(table,)))
        self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_a_changed_object_may_not_give_the_slot_another_default(self):
        self.table_guard()
        why = self.judge(residual_options=dict(tables=(("_tab2", self.SLOT, "_other", b"\xc3"),)),
                         destination_options=dict(tables=(self.TABLE,)))
        self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_nothing_may_define_or_redirect_the_slot_or_its_default(self):
        cases = {"strong": ("strong", self.SLOT, [1]), "comdat": ("comdat", self.SLOT, [(1, "s", None)]),
                 "common": ("common", self.SLOT, [(1, 4)]), "an alias of the slot": ("alternates", self.SLOT, [(1, "_x")]),
                 "an alias of the default": ("alternates", self.DEFAULT, [(1, "_x")])}
        for label, (table, name, entry) in cases.items():
            with self.subTest(label=label):
                g = self.table_guard()
                g.guard.index[table][name] = entry
                why = self.judge(destination_options=dict(tables=(self.TABLE,)))
                self.assertTrue(any(self.REFUSED in item for item in why), why)

    def test_an_object_the_context_cannot_read_refuses(self):
        real = T.portable_comdat_contexts
        for label, read in (("no context at all", lambda data: {}),
                            ("a context with no weak record", lambda data: {k: v[:3] for k, v in real(data).items()})):
            with self.subTest(label=label), patch.object(T, "portable_comdat_contexts", side_effect=read):
                self.table_guard()
                why = self.judge(destination_options=dict(tables=(self.TABLE,)))
                self.assertTrue(any(self.REFUSED in item for item in why), why)

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
        # review of 9459886c66: only what the claim acquired goes back, each key with its token; the
        # refused key and one this worker already held (prior) stay
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
        key = T.claims.key_of
        refused, prior = key("file:Code/A.cpp"), key("0x00001010")

        def claim(keys, note="", root=None):
            won = [key(k) for k in keys if key(k) != refused]
            return T.claims.ClaimResult(won, [refused], tokens={k: f"token-{k}" for k in won}, prior=[prior])
        released = []
        original_claim, original_release = T.claims.claim, T.claims.release
        T.claims.claim = claim
        T.claims.release = lambda keys, **kw: released.append((list(keys), kw.get("tokens")))
        original_refusal, T.refusal = T.refusal, lambda f, rows: None
        try:
            rep = T.merge("Code/T.cpp", dry_run=False, claim=True)
        finally:
            T.claims.claim, T.claims.release = original_claim, original_release
            T.refusal = original_refusal
            T._CACHE.clear()
        self.assertTrue(rep["blocked"].startswith("held by another worker"))
        won = [key("file:Code/T.cpp"), key("file:Code/B.cpp"), 0x1000]
        self.assertEqual(released, [(won, {k: f"token-{k}" for k in won})])

    def test_a_merge_blocked_after_claiming_releases_its_scope(self):
        don = {"Code/T.cpp": [{"target_rva": "0x00001000", "status": "matched"}],
               "Code/A.cpp": [{"target_rva": "0x00001010", "status": "matched"}]}
        released = []
        held = T.Held()
        held.acquired = [T.claims.key_of(k) for k in T.claim_keys("Code/T.cpp", don)][:-1]   # the last was ours already
        held.tokens = {k: f"token-{k}" for k in held.acquired}
        saved = (T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release)
        T.skeleton = lambda tu: []
        T.donors = lambda tu, sk: (don, {}, {})
        T.claim_scope = lambda tu, d, **kw: held
        T._merge = lambda tu, sk, d, report, dry_run: dict(report, blocked="no verified merge")
        T.claims.release = lambda keys, **kw: released.append((list(keys), kw.get("tokens")))
        try:
            report = T.merge("Code/T.cpp")
        finally:
            T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release = saved
        self.assertEqual(report["blocked"], "no verified merge")
        self.assertEqual(released, [(held.acquired, held.tokens)])


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

class SeedFlagSearchTests(unittest.TestCase):
    """_merge's flag search: a set whose seed is rejected tries no donor, the seed's own set is tried as well as
    the popular ones, and the byte and link checks still decide (Player.cpp, Weapon.cpp, MilesAudioManager.cpp)."""
    TU, A, B, C = "Code/T.cpp", "Code/A.cpp", "Code/B.cpp", "Code/C.cpp"

    def search(self, passes, spec=None, guard=None):
        """`spec` {file: (flag, rows)}; `passes(flags, files)` gives the files whose rows miss, or None for a compile error."""
        spec = spec or {self.TU: ("/DSEED", 1), self.A: ("/DDONOR", 2), self.B: ("/DDONOR", 2)}
        texts = {f: "// cl: " + flag + chr(10) + f for f, (flag, _) in spec.items()}
        don = {f: [{"target_rva": hex(0x1000 + 0x10 * i + j)} for j in range(rows)]
               for i, (f, (_, rows)) in enumerate(spec.items())}
        compiled = []

        class Verifier:
            fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
            errors = ["fixture.cpp(1) : error C2065: 'missing' : undeclared identifier"]
            all_errors = errors
            flags = None

            def matched(self, text, rows):
                if text in texts.values():
                    return {r["target_rva"] for r in rows}
                flags, files = json.loads(text)
                compiled.append((flags, files))
                missing = passes(flags, files)
                if missing is None:
                    return None
                return {r["target_rva"] for f in files if f not in missing for r in don[f]}

        def compose(_tu, _sk, files, _texts, flags, _strategy, drop=frozenset(), drop_all=frozenset()):
            return json.dumps([list(flags), list(files)])

        with patch.object(T, "Verifier", return_value=Verifier()):
            with patch.object(T, "compose", side_effect=compose):
                with patch.object(T, "apply") as apply:
                    out = T._merge(self.TU, [], don, {"accepted": [], "rejected": {}}, True, texts=texts, guard=guard)
        apply.assert_not_called()
        return out, compiled

    def weighted(self):
        return {self.TU: ("/DSEED", 1), self.A: ("/DF1", 4), self.B: ("/DF2", 3), self.C: ("/DF3", 2)}

    def test_a_set_whose_seed_is_rejected_tries_no_donor(self):
        out, compiled = self.search(lambda flags, files: None if "/DDONOR" in flags else ())
        self.assertEqual([f for f in compiled if "/DDONOR" in f[0] and f[1] != [self.TU]], [])
        self.assertEqual(set(out["accepted"]), {self.TU, self.A, self.B})

    def test_the_seeds_own_set_is_tried_first(self):
        # the donors carry more rows, so the popular order alone tries their flags first
        out, compiled = self.search(lambda flags, files: ())
        self.assertIn("/DSEED", compiled[0][0])
        self.assertEqual(out["accepted"][0], self.TU)

    def test_the_seeds_set_displaces_no_popular_set(self):
        # F3 is the third most popular and the only set that keeps every donor; the others keep the seed and A
        def passes(flags, files):
            if "/DF3" in flags:
                return ()
            return None if set(files) - {self.TU, self.A} else ()
        out, compiled = self.search(passes, self.weighted())
        self.assertEqual(set(out["accepted"]), set(self.weighted()))
        self.assertEqual(out["rows"], 10)
        self.assertIn("/DF3", out["flags"])

    def test_a_merge_only_the_seeds_set_finds_is_reached_past_a_seed_only_best(self):
        # the three popular sets accept the seed alone, so `best` is set and the fallback below them never runs
        def passes(flags, files):
            if "/DSEED" in flags:
                return ()
            return None if set(files) - {self.TU} else ()
        out, _ = self.search(passes, self.weighted())
        self.assertNotIn("blocked", out)
        self.assertEqual(set(out["accepted"]), set(self.weighted()))
        self.assertEqual(out["rows"], 10)
        self.assertIn("/DSEED", out["flags"])

    def test_a_donor_the_seeds_flags_break_stays_out_and_loses_no_row(self):
        def passes(flags, files):
            if "/DDONOR" in flags:
                return None
            return (self.B,) if self.B in files else ()
        out, _ = self.search(passes)
        self.assertEqual(set(out["accepted"]), {self.TU, self.A})
        self.assertEqual(out["rejected"][self.B], "bytes")
        self.assertEqual(out["rows"], 3)

    def test_nothing_is_accepted_when_the_seed_passes_under_no_set(self):
        out, compiled = self.search(lambda flags, files: None)
        self.assertEqual(out["accepted"], [])
        self.assertTrue(out["blocked"].startswith("no verified merge"))
        self.assertTrue(all(f[1] == [self.TU] for f in compiled))
        self.assertEqual(out["rejected"][self.A], T.SEED_NOT_TRIED)

    def test_a_link_guard_refusal_of_the_seed_stops_that_set(self):
        # Player.cpp: 12/12 rows under the popular flags, and the guard refuses the seed there
        tu = self.TU

        class Guard:
            text = None

            def load(self):
                pass

            def linked(self, files):
                return list(files)

            def prepare(self, files):
                return None

            def judge(self, obj, files, text):
                return ["unresolved ?x@@YAXXZ"] if "/DDONOR" in json.loads(text)[0] else []

        out, compiled = self.search(lambda flags, files: (), guard=Guard())
        self.assertEqual([f for f in compiled if "/DDONOR" in f[0] and f[1] != [tu]], [])
        self.assertEqual(set(out["accepted"]), {tu, self.A, self.B})
        self.assertIn("/DSEED", out["flags"])

    def test_a_link_guard_refusal_under_every_set_blocks_and_names_the_seed(self):
        class Guard:
            def load(self):
                pass

            def linked(self, files):
                return list(files)

            def prepare(self, files):
                return None

            def judge(self, obj, files, text):
                return ["unresolved ?x@@YAXXZ"]

        out, compiled = self.search(lambda flags, files: (), guard=Guard())
        self.assertEqual(out["accepted"], [])
        self.assertIn("the seed itself fails", out["blocked"])
        self.assertTrue(out["rejected"][self.TU].startswith("link:"))
        self.assertTrue(all(f[1] == [self.TU] for f in compiled))

class ComposeNamedFunctionTests(unittest.TestCase):
    """A file-scope object initialized with a function this file defines must not be hoisted above it."""
    NL = chr(10)
    FN = NL.join(["static int helper(int value)", "{", "    return value;", "}"])
    ANCHOR = NL.join(["int (*helper_anchor)(int) =", "    &helper;"])

    def compose(self, *parts):
        text = self.NL.join(parts) + self.NL
        return T.compose("Seed.cpp", [], ["Seed.cpp"], {"Seed.cpp": text}, [], "first")

    def test_an_anchor_stays_after_the_function_it_names(self):
        out = self.compose("int other;", self.FN, self.ANCHOR)
        self.assertLess(out.index("static int helper(int value)"), out.index("helper_anchor"))
        self.assertEqual(out.count("helper_anchor"), 1)

    def test_a_prototype_above_keeps_the_anchor_among_the_declarations(self):
        proto = "static int helper(int value);"
        out = self.compose(proto, self.FN, self.ANCHOR)
        self.assertLess(out.index(proto), out.index("helper_anchor"))
        self.assertLess(out.index("helper_anchor"), out.index("return value"))

    def test_other_objects_are_still_hoisted(self):
        out = self.compose(self.FN, "int value_after = 3;", "int later()", "{", "    return 5;", "}")
        self.assertLess(out.index("value_after"), out.index("return value"))

    def test_a_qualified_name_is_left_alone(self):
        chunks = T.composition_chunks(self.NL.join([
            "class C { public: int get(); };", "int C::get()", "{", "    return 1;", "}",
            "int (C::*get_anchor)() = &C::get;"]) + self.NL)
        self.assertTrue(any(kind == "decl" and "get_anchor" in text for kind, text in chunks))

    def test_an_object_above_the_function_is_left_alone(self):
        chunks = T.composition_chunks(self.NL.join(["int (*early)(int) = helper;", self.FN]) + self.NL)
        self.assertTrue(any(kind == "decl" and "early" in text for kind, text in chunks))
