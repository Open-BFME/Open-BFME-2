"""Code identity: allowed-symbol classes, duplicate removal spans, alias and
register rules (tools/allowed_symbols.py, dup_defs.py, code_identity_gate.py)."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import allowed_symbols as allowed  # noqa: E402
import code_identity_gate as gate  # noqa: E402
import dup_defs  # noqa: E402

OWNER = 0x1000      # row "?owner@@YAXXZ" at 0x1000, 0x20 bytes
OTHER = 0x2000      # no row, Ghidra function of 0x10 bytes


class FakeObj:
    path = Path("a.obj")
    by_name = {}


class FakeIdentity(allowed.Identity):
    """Identity over a two-row ledger with scripted certification and definitions."""

    def __init__(self, defs, certified):
        self.at = {OWNER: [{"name": "?owner@@YAXXZ", "target_size": "32", "notes": "", "source": "a.cpp"}],
                   0x3000: [{"name": "?big@@YAXXZ", "target_size": "64", "notes": "", "source": "b.cpp"}]}
        self.spans = [(OWNER, OWNER + 32, self.at[OWNER][0]), (0x3000, 0x3040, self.at[0x3000][0])]
        self.span_starts = [OWNER, 0x3000]
        self.ghidra = {OWNER: 32, OTHER: 16, 0x3000: 64}
        self.defs = defs
        self._certified = certified
        self._gstarts = None

    def certify(self, path, name, t):
        return self._certified.get((name, t), "bytes")


ROW = {"name": "?caller@@YAXXZ", "notes": "", "source": "c.cpp"}
SYM = {"section": 1}


def ext(name):
    return {"name": name, "storage": allowed.EXTERNAL, "section": 0, "value": 0}


class ClassifyTests(unittest.TestCase):
    def classify(self, ref, t, defs=None, certified=None):
        ident = FakeIdentity(defs or {}, certified or {})
        return ident.classify(ROW, FakeObj(), SYM, 0, allowed.REL32, ref, t)

    def test_owner_name_is_allowed(self):
        self.assertEqual(self.classify(ext("?owner@@YAXXZ"), OWNER), ("owner", ""))

    def test_undefined_other_name_is_an_alias_to_the_owner(self):
        self.assertEqual(self.classify(ext("?pinned@@YAXXZ"), OWNER), ("alias", "?owner@@YAXXZ"))

    def test_other_name_defined_with_other_code_is_wrong(self):
        # the exploit: a pin makes the call byte-match, the link runs the other copy
        defs = {"?copy@@YAXXZ": [("x.obj", "d1", 20, True)]}
        self.assertEqual(self.classify(ext("?copy@@YAXXZ"), OWNER, defs), ("wrong", "bytes"))

    def test_certified_fold_is_allowed(self):
        defs = {"?twin@@YAXXZ": [("x.obj", "d1", 32, False)]}
        self.assertEqual(self.classify(ext("?twin@@YAXXZ"), OWNER, defs, {("?twin@@YAXXZ", OWNER): "retail"}),
                         ("fold", ""))

    def test_divergent_copies_are_their_own_class(self):
        defs = {"?inl@@YAXXZ": [("x.obj", "d1", 32, False), ("y.obj", "d2", 32, False)]}
        self.assertEqual(self.classify(ext("?inl@@YAXXZ"), OWNER, defs)[0], "divergent")

    def test_interior_target_is_wrong(self):
        self.assertEqual(self.classify(ext("?owner@@YAXXZ"), OWNER + 4), ("interior", "?owner@@YAXXZ+0x4"))

    def test_unowned_target(self):
        self.assertEqual(self.classify(ext("?gone@@YAXXZ"), OTHER), ("unowned", "undefined"))
        defs = {"?here@@YAXXZ": [("x.obj", "d1", 16, True)]}
        self.assertEqual(self.classify(ext("?here@@YAXXZ"), OTHER, defs, {("?here@@YAXXZ", OTHER): "retail"}),
                         ("unowned", "match"))

    def test_own_eh_and_labels(self):
        eh = {"name": "__ehhandler$?caller@@YAXXZ", "storage": allowed.STATIC, "section": 9, "value": 0}
        self.assertEqual(self.classify(eh, OTHER), ("eh", ""))
        foreign = dict(eh, name="__ehhandler$?someone@@YAXXZ")
        self.assertEqual(self.classify(foreign, OTHER), ("wrong", "foreign-eh"))
        label = {"name": "$L123", "storage": allowed.STATIC, "section": 1, "value": 8}
        self.assertEqual(self.classify(label, OWNER + 8)[0], "label")


class AlternatenameTests(unittest.TestCase):
    def test_alias_must_name_the_owner_of_its_one_target(self):
        ident = FakeIdentity({}, {})
        targets = {"?a@@YAXXZ": {OWNER}, "?b@@YAXXZ": {OWNER, 0x3000}}
        self.assertEqual(allowed.judge_alternatename(ident, "?a@@YAXXZ", "?owner@@YAXXZ", targets), "ok")
        self.assertEqual(allowed.judge_alternatename(ident, "?a@@YAXXZ", "?big@@YAXXZ", targets), "wrong")
        self.assertEqual(allowed.judge_alternatename(ident, "?b@@YAXXZ", "?owner@@YAXXZ", targets), "wrong")
        self.assertEqual(allowed.judge_alternatename(ident, "?c@@YAXXZ", "?owner@@YAXXZ", targets), "unreferenced")

    def test_generated_aliases_skip_names_with_two_targets(self):
        found = [(ROW, 0, 0, "?a@@YAXXZ", OWNER, "alias", "?owner@@YAXXZ"),
                 (ROW, 0, 0, "?b@@YAXXZ", OWNER, "alias", "?owner@@YAXXZ"),
                 (ROW, 0, 0, "?b@@YAXXZ", 0x3000, "alias", "?big@@YAXXZ")]
        self.assertEqual(allowed.alternatenames(found), {"?a@@YAXXZ": "?owner@@YAXXZ"})


class DefinitionSpanTests(unittest.TestCase):
    SRC = ("int keep() { return 1; }\n\n"
           "/**\n * doc\n */\n"
           "UnsignedInt FrameData::getCount() {\n\tif (x) { return '}'; }\n\treturn m;\n}\n\n"
           "void FrameData::other() {}\n")

    def test_removes_definition_and_its_comment(self):
        a, b = dup_defs.definition_span(self.SRC, "?getCount@FrameData@@QAEIXZ")
        self.assertEqual(self.SRC[:a] + self.SRC[b:], "int keep() { return 1; }\n\nvoid FrameData::other() {}\n")

    def test_refuses_overloads_templates_and_declarations(self):
        twice = self.SRC + "UnsignedInt FrameData::getCount(int) {}\n"
        self.assertIsNone(dup_defs.definition_span(twice, "?getCount@FrameData@@QAEIXZ"))
        self.assertIsNone(dup_defs.definition_span(self.SRC, "??$f@H@FrameData@@QAEXXZ"))
        self.assertIsNone(dup_defs.definition_span("void FrameData::getCount();\n", "?getCount@FrameData@@QAEIXZ"))


class RegisterTests(unittest.TestCase):
    def test_mode_and_keys(self):
        keys, mode = gate.read_register("# x\n# mode: enforce\na\tb\n\n")
        self.assertEqual((keys, mode), ({"a\tb"}, "enforce"))
        self.assertEqual(gate.read_register("")[1], "shadow")

    def test_dup_debt_keys(self):
        found = [{"class": "duplicate", "name": "a", "kept_verdict": "retail"},
                 {"class": "divergent", "name": "b", "kept_verdict": "retail"},
                 {"class": "divergent", "name": "c", "kept_verdict": "wrong"}]
        self.assertEqual(dup_defs.debt(found), {"duplicate\ta", "divergent\tc"})


class TierTests(unittest.TestCase):
    def tier(self, name, notes="", source="Code/x.cpp"):
        return allowed.name_tier({"name": name, "notes": notes, "source": source, "target_rva": "0x00001000"}, {})[0]

    def test_tiers(self):
        self.assertEqual(self.tier("?Rva00401000Get@@YAXXZ"), "address")
        self.assertEqual(self.tier("?dup_00401000@@YAXXZ"), "address")
        self.assertEqual(self.tier("_compress", "vendored=zlib-1.1.4"), "evidence")
        self.assertEqual(self.tier("?update@Foo@@UAEXXZ"), "unverified")


if __name__ == "__main__":
    unittest.main()
