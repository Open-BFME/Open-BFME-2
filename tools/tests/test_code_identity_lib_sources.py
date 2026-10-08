"""code_identity_gate.check with a staged library row among its sources.

A vendored .lib row (vendor/comsupp/comsupp.lib) reaches check() through
delta_sources. The archive path names no object by itself (row_object needs the
row's member= note), so check() must scope the extracted member object of each
of its rows: allowed.load() puts that member's definitions in ident.defs under
the same row_object path, and a member duplicating a name one of our objects
defines is a duplicate definition like any other. Compiled sources beside it
are scoped by path as before."""
import sys
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import allowed_symbols as allowed  # noqa: E402
import code_identity_gate as gate  # noqa: E402

CPP = "Code/GameEngine/Source/Common/Example.cpp"
LIB = "vendor/comsupp/comsupp.lib"
NAME = "?f@@YAXXZ"
MEMBER_NAME = "?_com_issue_errorex@@YGXJPAUIUnknown@@ABU_GUID@@@Z"
LIB_ROW = {"name": MEMBER_NAME, "target_rva": "0x00654B30", "target_size": "110", "source": LIB,
           "status": "matched", "notes": "vendored=msvc71-comsupp;member=Release\\comsupp.obj"}


class FakeIdentity:
    truth = None

    def __init__(self, defs):
        self.defs = defs


class LibSourceScope(unittest.TestCase):
    def run_check(self, sources, rows):
        cpp_obj = str(allowed.row_object({"source": CPP}))
        member_obj = str(allowed.row_object(LIB_ROW))
        self.assertNotEqual(member_obj, cpp_obj)
        ident = FakeIdentity({
            NAME: [(cpp_obj, "d1", 5, False)],
            # the member and one of our objects both define the member's name
            MEMBER_NAME: [(member_obj, "d2", 110, True), (cpp_obj, "d3", 110, True)],
            "?g@@YAXXZ": [("other.obj", "d4", 5, False)],
        })
        seen = {}
        real_analyse = gate.dup_defs.analyse

        def analyse(ledger, defs, truth):
            seen["names"] = set(defs)
            return real_analyse(ledger, defs, truth)

        with mock.patch.object(allowed, "load", return_value=(ident, rows)), \
                mock.patch.object(allowed, "scan", return_value=[]), \
                mock.patch.object(allowed.census, "ledger", return_value=rows), \
                mock.patch.object(gate, "added_alternatenames", return_value=[]), \
                mock.patch.object(gate.dup_defs, "analyse", side_effect=analyse), \
                mock.patch.object(gate.dup_defs, "kept_verdict", return_value="unknown"), \
                mock.patch.object(gate.dup_defs, "read_baseline", return_value=set()):
            problems = gate.check(sources, [])[0]
        return problems, seen["names"]

    def test_lib_row_scopes_its_member(self):
        problems, names = self.run_check([LIB], [LIB_ROW])
        self.assertEqual(names, {MEMBER_NAME})   # the member's definitions are in scope
        self.assertEqual(problems, ["definition: duplicate | " + MEMBER_NAME])

    def test_lib_row_beside_a_compiled_source(self):
        problems, names = self.run_check([CPP, LIB], [LIB_ROW])
        self.assertEqual(names, {NAME, MEMBER_NAME})
        self.assertEqual(problems, ["definition: duplicate | " + MEMBER_NAME])

    def test_compiled_source_without_rows_still_scoped_by_path(self):
        problems, names = self.run_check([CPP, LIB], [])
        self.assertEqual(names, {NAME, MEMBER_NAME})   # every name the compiled object defines

    def test_lib_source_without_rows_scopes_nothing(self):
        problems, names = self.run_check([LIB], [])   # no KeyError on the bare archive path
        self.assertEqual(names, set())
        self.assertEqual(problems, [])


if __name__ == "__main__":
    unittest.main()
