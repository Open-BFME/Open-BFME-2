"""data_sweep's text edits and data_check's findings, without a compiler."""
import sys
import collections
import csv
import io
import tempfile
from unittest.mock import patch
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
    def test_virtual_base_table_is_compiler_emitted(self):
        self.assertEqual(dl.kind_of("??_8?$basic_ofstream@DV?$char_traits@D@_STL@@@_STL@@7B@"),
                         "vtable")

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


class VerifiedOwnership(unittest.TestCase):
    OWNER = "?g_Va00DDEF08@@3IA"
    ALIAS = "?g_00DDEF08StaticEmpty@@3HA"
    SOURCE = "Code/StringInits.cpp"
    ADDRESS = 0x9DEF08

    def setUp(self):
        import data_rows
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.owned = self.root / "data_rows.csv"
        self.index = self.root / "data_ledger.csv"
        self.row = dict(name=self.OWNER, address="0x009DEF08", address_kind="rva",
                        size="4", section=".data", source=self.SOURCE,
                        status="matched", evidence="verified owner", model="test")
        self.write_owners([self.row])
        self.index.write_text(dl.render([dict(address="0x009DEF08", size=12,
            section=".data", kind="global", name=self.ALIAS, source="",
            status="unowned", names=self.ALIAS + ";" + self.OWNER, defs=0, refs=4)]))
        self.patch = patch.object(data_rows, "DATA_ROWS", self.owned)
        self.patch.start()
        self.addCleanup(self.patch.stop)
        sections = patch.object(data_rows, "retail_sections",
                               return_value=[(".data", 0xD00000, 0xE00000)])
        sections.start()
        self.addCleanup(sections.stop)

    def write_owners(self, rows):
        import data_rows
        output = io.StringIO()
        writer = csv.DictWriter(output, data_rows.FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
        self.owned.write_text(output.getvalue())

    def test_owner_replaces_unowned_alias_in_loaded_index(self):
        ledger = dl.load(self.index)
        facts = {self.SOURCE: ({(self.OWNER, self.ADDRESS)}, {self.OWNER}),
                 "User.cpp": ({(self.OWNER, self.ADDRESS)}, set())}
        self.assertEqual(data_check.findings(facts, ledger), [])
        self.assertEqual(ledger[self.ADDRESS]["size"], "4")

    def test_alias_and_second_definition_still_refused(self):
        ledger = dl.load(self.index)
        facts = {"Alias.cpp": ({(self.ALIAS, self.ADDRESS)}, set()),
                 "Duplicate.cpp": ({(self.OWNER, self.ADDRESS)}, {self.OWNER})}
        self.assertEqual(data_check.findings(facts, ledger), [
            ("Alias.cpp", "wrong-name", self.ALIAS, "0x009DEF08"),
            ("Duplicate.cpp", "duplicate-def", self.OWNER, "0x009DEF08")])

    def test_generated_index_uses_owner_even_without_owner_object(self):
        bind = {self.ADDRESS: collections.Counter({(self.ALIAS, None): 4})}
        with patch.object(dl, "retail_sections", return_value=[(".data", 0x900000, 0x100000, 0x100000)]):
            rows = dl.ledger_rows(bind, {})
        self.assertEqual(rows[0]["name"], self.OWNER)
        self.assertEqual(rows[0]["source"], self.SOURCE)
        self.assertEqual(rows[0]["size"], "4")
        self.assertIn(self.ALIAS, rows[0]["names"])

    def test_data_only_owner_is_checked_without_cached_index_entry(self):
        self.index.write_text(dl.render([]))
        self.row.update(address="0x00DDEF08", address_kind="va")
        self.write_owners([self.row])
        ledger = dl.load(self.index)
        self.assertEqual(ledger[self.ADDRESS]["name"], self.OWNER)

    def test_data_only_owner_splits_upper_bound_on_load_and_generation(self):
        # As with the BigObf contexts, this owner ends at the next known slot
        # and is not yet reached by a relocation in any matched code object.
        preceding, following = self.ADDRESS - 0x194, self.ADDRESS + 0x38
        self.write_owners([dict(self.row, size="56")])
        before = dict(address=f"0x{preceding:08X}", size=following - preceding,
                      section=".data", kind="global", name="_previous", source="",
                      status="unowned", names="", defs=0, refs=2)
        after = dict(before, address=f"0x{following:08X}", size=16, name="_next")
        self.index.write_text(dl.render([before, after]))
        cached = self.index.read_bytes()
        loaded = dl.load(self.index)
        bind = {preceding: collections.Counter({("_previous", None): 2}),
                following: collections.Counter({("_next", None): 2})}
        with patch.object(dl, "retail_sections", return_value=[(".data", 0x900000, 0x100000, 0x100000)]):
            generated = {int(r["address"], 16): r for r in dl.ledger_rows(bind, {})}
        for index in (loaded, generated):
            self.assertEqual(index[preceding]["size"], 0x194)
            self.assertEqual(index[self.ADDRESS]["size"], "56")
            self.assertEqual(index[self.ADDRESS]["name"], self.OWNER)
        self.assertEqual(loaded[following]["size"], "16")
        self.assertEqual(self.index.read_bytes(), cached)

    def test_ambiguous_ownership_is_refused(self):
        self.write_owners([self.row, dict(self.row, name=self.ALIAS)])
        with self.assertRaises(ValueError):
            dl.load(self.index)

    def test_unmatched_ownership_is_refused(self):
        self.write_owners([dict(self.row, status="unmatched")])
        with self.assertRaises(ValueError):
            dl.load(self.index)


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

    def test_folded_vbtable_is_not_a_user_global_alias(self):
        # The real stream constructor case at 007BCD24: both compiler tables
        # contain the same eight bytes; the older index calls them globals.
        table = "??_8?$basic_ofstream@DV?$char_traits@D@_STL@@@_STL@@7B@"
        owner = "??_8?$basic_fstream@DV?$char_traits@D@_STL@@@_STL@@7B?$basic_ostream@DV?$char_traits@D@_STL@@@1@@"
        alias = "?g_streamTable@@3PAHA"
        ledger = {0x7BCD24: {"kind": "global", "name": owner, "source": "Fstream.cpp"}}
        facts = {"Ofstream.cpp": ({(table, 0x7BCD24), (alias, 0x7BCD24)}, set())}
        self.assertEqual(data_check.findings(facts, ledger),
                         [("Ofstream.cpp", "wrong-name", alias, "0x007BCD24")])

    def test_negative_controls(self):
        sym = "?TheScriptEngine@@3PAVScriptEngine@@A"
        facts = {"User.cpp": ({(sym, 0x9FE16C), ("__real@3f800000", 0x7BB8D8)}, set()),
                 "ScriptEngine.cpp": ({(sym, 0x9FE16C)}, {sym}),
                 "Unknown.cpp": ({("?g_new@@3HA", 0x123456)}, {"?g_new@@3HA"})}
        self.assertEqual(data_check.findings(facts, self.LEDGER), [])


if __name__ == "__main__":
    unittest.main()
