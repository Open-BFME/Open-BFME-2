"""data_sweep's text edits and data_check's findings, without a compiler."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_check  # noqa: E402
import data_ledger as dl  # noqa: E402
import data_sweep as ds  # noqa: E402

DECL = "extern class ScriptEngine *TheScriptEngine;"


class RenameEdit(unittest.TestCase):
    def test_user_extern_becomes_canonical(self):
        text = ("// header comment\n#include \"x.h\"\nextern ScriptEngine *g_Va009FE16C;\n"
                "void f() { g_Va009FE16C->run(); /* g_Va009FE16C */ const char *s = \"g_Va009FE16C\"; }\n")
        out = ds.rename_edit("g_Va009FE16C", "TheScriptEngine", DECL, False)(text)
        self.assertIn(DECL + "\n", out)
        self.assertIn("TheScriptEngine->run();", out)
        self.assertIn("/* g_Va009FE16C */", out)          # comments untouched
        self.assertIn('"g_Va009FE16C"', out)              # literals untouched
        self.assertNotIn("extern ScriptEngine *g_Va009FE16C", out)

    def test_comments_before_the_declaration_survive(self):
        text = "// cl: /O1\n//\n// note\nextern ScriptEngine *g_Va009FE16C;\nvoid f() { g_Va009FE16C->run(); }\n"
        out = ds.rename_edit("g_Va009FE16C", "TheScriptEngine", DECL, False)(text)
        self.assertEqual(out, "// cl: /O1\n//\n// note\n" + DECL + "\nvoid f() { TheScriptEngine->run(); }\n")
        lit = "// cl: /O1\n// note\nextern const char g_s[];\nconst char *f() { return g_s; }\n"
        self.assertEqual(ds.literal_edit("g_s", '"."')(lit), '// cl: /O1\n// note\nconst char *f() { return "."; }\n')

    def test_user_definition_is_left_alone(self):
        text = "ScriptEngine *g_Va009FE16C = 0;\nvoid f() { g_Va009FE16C->run(); }\n"
        self.assertEqual(ds.rename_edit("g_Va009FE16C", "TheScriptEngine", DECL, False)(text), text)

    def test_definer_definition_becomes_extern(self):
        text = "ScriptEngine *g_Va009FE16C = 0;\nvoid f() { g_Va009FE16C->run(); }\n"
        out = ds.rename_edit("g_Va009FE16C", "TheScriptEngine", DECL, True)(text)
        self.assertTrue(out.startswith(DECL + "\n"))
        self.assertNotIn("= 0", out)

    def test_function_of_that_name_refuses(self):
        text = "int g_x(int);\nint y = g_x(1);\n"
        self.assertEqual(ds.rename_edit("g_x", "TheX", "extern int TheX;", True)(text), text)

    def test_cast_keeps_the_use_type(self):
        text = "extern Rva002A8F24 *g_00DFEEF8;\nvoid f() { g_00DFEEF8->m(); }\n"
        out = ds.rename_edit("g_00DFEEF8", "TheGameLogic", "extern class GameLogic *TheGameLogic;", False,
                             "(*(Rva002A8F24 **)&TheGameLogic)")(text)
        self.assertIn("(*(Rva002A8F24 **)&TheGameLogic)->m();", out)
        self.assertIn("extern class GameLogic *TheGameLogic;", out)


class LiteralEdit(unittest.TestCase):
    def test_string(self):
        text = "extern const char g_00BBFDDC[];\nconst char *f() { return g_00BBFDDC; }\n"
        out = ds.literal_edit("g_00BBFDDC", ds.c_string(b"\n0"))(text)
        self.assertEqual(out, r'const char *f() { return "\0120"; }' + "\n")

    def test_defined_here_refuses(self):
        text = 'const char g_s[] = "0";\nconst char *f() { return g_s; }\n'
        self.assertEqual(ds.literal_edit("g_s", '"0"')(text), text)

    def test_float_round_trips(self):
        import struct
        for value in (1.0, 0.5, -1.0, 3.4028234663852886e38, 0.01):
            raw = struct.pack("<f", value)
            lit = ds.c_float(raw, False)
            self.assertEqual(struct.pack("<f", float(lit.strip("()").rstrip("f"))), raw, lit)
        self.assertEqual(ds.c_float(struct.pack("<f", -1.0), False), "(-1.0f)")
        self.assertIsNone(ds.c_float(struct.pack("<f", float("inf")), False))


class Ledger(unittest.TestCase):
    def test_invented(self):
        for name in ("?g_Va009FE16C@@3PAVScriptEngine@@A", "?g_00DFEEF8@@3PAVX@@A",
                     "?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A", "?g_bfmeAptBreakOnAssertAtDDC01C@@3HA"):
            self.assertTrue(dl.invented(name), name)
        for name in ("?TheScriptEngine@@3PAVScriptEngine@@A", "?TheAudio@@3PAVAudioManager@@A", "__real@3f800000"):
            self.assertFalse(dl.invented(name), name)

    def test_canonical_prefers_external_real_defined(self):
        names = {("?g_Va009FE16C@@3PAVScriptEngine@@A", None): 50, ("?TheScriptEngine@@3PAVScriptEngine@@A", None): 5,
                 ("_s_engine", "a.cpp"): 90}
        defs = {"?TheScriptEngine@@3PAVScriptEngine@@A": [("ScriptEngine.cpp", dl.EXTERNAL, False, ".bss", False)]}
        import collections
        best, owner, status = dl.choose(names, defs, collections.Counter())
        self.assertEqual(best[0], "?TheScriptEngine@@3PAVScriptEngine@@A")
        self.assertEqual((owner, status), ("ScriptEngine.cpp", "provisional"))


class Check(unittest.TestCase):
    LEDGER = {0x9FE16C: {"kind": "global", "name": "?TheScriptEngine@@3PAVScriptEngine@@A",
                         "source": "ScriptEngine.cpp"},
              0x7BB8D8: {"kind": "float", "name": "__real@3f800000", "source": ""}}

    def test_positive_invented_name(self):
        facts = {"New.cpp": ({("?g_Va009FE16C@@3PAVScriptEngine@@A", 0x9FE16C)}, set())}
        self.assertEqual(data_check.findings(facts, self.LEDGER),
                         [("New.cpp", "wrong-name", "?g_Va009FE16C@@3PAVScriptEngine@@A", "0x009FE16C")])

    def test_positive_duplicate_definition(self):
        sym = "?TheScriptEngine@@3PAVScriptEngine@@A"
        facts = {"New.cpp": ({(sym, 0x9FE16C)}, {sym})}
        self.assertEqual(data_check.findings(facts, self.LEDGER), [("New.cpp", "duplicate-def", sym, "0x009FE16C")])

    def test_negative_controls(self):
        sym = "?TheScriptEngine@@3PAVScriptEngine@@A"
        facts = {"User.cpp": ({(sym, 0x9FE16C), ("__real@3f800000", 0x7BB8D8)}, set()),
                 "ScriptEngine.cpp": ({(sym, 0x9FE16C)}, {sym}),
                 "Unknown.cpp": ({("?g_new@@3HA", 0x123456)}, {"?g_new@@3HA"})}
        self.assertEqual(data_check.findings(facts, self.LEDGER), [])


if __name__ == "__main__":
    unittest.main()
