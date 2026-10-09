"""data_back_rank: link_status parsing, address attribution, ranking, name facts,
the PROVISIONAL fallback and the COFF symbol scan, on a tiny fixture."""
import csv
import gzip
import io
import json
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_back_rank as dbr  # noqa: E402

EMPTY = "??_C@_00CNPNBAHC@?$AA@"
NULLCHR = "?TheNullChr@?1??str@AsciiString@@QBEPBDXZ@4DB"
INVENTED_EMPTY = "?g_Rva0107301CEmptyString@@3QBDB"
GD_V = "?TheWritableGlobalData@@3PAVGlobalData@@A"
GD_U = "?TheWritableGlobalData@@3PAUGlobalData@@A"
GD_X = "?g_Va00600000@@3PAXA"

LEDGER = [
    ["address", "size", "section", "kind", "name", "source", "status", "names", "defs", "refs"],
    ["0x00100000", "1", ".rdata", "string", EMPTY, "", "literal", ";".join([EMPTY, NULLCHR, INVENTED_EMPTY]), "1", "10"],
    ["0x00200000", "4", ".data", "global", GD_V, "Code/G.cpp", "provisional",
     ";".join([GD_V, GD_U, GD_X, "_TheGameLogic@Code/A.cpp"]), "2", "6"],
    ["0x00300000", "4", ".data", "global", "?g_one@@3HA", "Code/C.cpp", "owned", "", "1", "3"],
]
STATUS_COLS = ["name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason",
               "self_strict", "closed_strict", "closed_strict_pilot_rule", "pinned_strict", "byte_equal",
               "hardcoded", "failure_count", "failures"]
STATUS = [
    # r1: two data-back hits through the literal (x2) and an unrelated data-fwd
    ("r1", "real", "Code/S1.cpp", 0x1000, 100, "1", f"data-back:{EMPTY}x2;data-fwd:?g_one@@3HA"),
    # r2 overlaps r1 by 0x14 bytes; its only failure is the AsciiString TheNullChr
    ("r2", "real", "Code/S2.cpp", 0x1050, 100, "1", f"data-back:{NULLCHR}"),
    # r3: a TU-local static, matched only for its own source
    ("r3", "real", "Code/A.cpp", 0x2000, 40, "1", "data-back:_TheGameLogic"),
    # r4: the same static name from another TU is not that address
    ("r4", "real", "Code/B.cpp", 0x3000, 8, "1", "data-back:_TheGameLogic"),
    ("r5", "real", "Code/S5.cpp", 0x5000, 64, "0", f"data-back:{EMPTY}"),         # not placed
    ("r6", "gen-alias", "Code/S6.cpp", 0x6000, 64, "1", f"data-back:{EMPTY}"),    # not real
    # r7 fails through two addresses: under both, sole under neither
    ("r7", "real", "Code/S7.cpp", 0x4000, 16, "True", f"data-back:{GD_U};data-back:{EMPTY}"),
    ("r8", "real", "Code/S8.cpp", 0x7000, 32, "1", "data-fwd:?g_one@@3HA"),        # no data-back
]
FUNCTIONS = [
    ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"],
    ["r1", "", "0x00001000", "100", "Code/S1.cpp", "matched", ""],
    ["r7", "", "0x00004000", "16", "Code/S7.cpp", "matched", ""],
    ["alias", "", "0x00004000", "16", "Code/S9.cpp", "matched", "gen-alias"],
    ["r3", "", "0x00002000", "40", "Code/A.cpp", "matched", ""],
]


def write_csv(path, rows, delimiter=","):
    with open(path, "w", newline="", encoding="utf-8") as f:
        csv.writer(f, delimiter=delimiter, lineterminator="\n").writerows(rows)


def coff(symbols):
    """A minimal i386 COFF object: one .rdata COMDAT section, one .data section and
    the given (name, section, storage) symbols; long names go to the string table."""
    nsec = 2
    header_size = 20 + 40 * nsec
    table, strings = b"", b""
    for name, section, storage in symbols:
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, 4 + len(strings))
            strings += raw + b"\0"
        table += field + struct.pack("<IhHBB", 0, section, 0, storage, 0)
    head = struct.pack("<HHIIIHH", 0x14C, nsec, 0, header_size, len(symbols), 0, 0)
    sections = (b".rdata\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 0, 0, 0, 0, 0, 0, 0x40001040)
                + b".data\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 0, 0, 0, 0, 0, 0, 0xC0000040))
    return head + sections + table + struct.pack("<I", 4 + len(strings)) + strings


class Parsing(unittest.TestCase):
    def test_failures_and_repeats(self):
        got = dbr.parse_failures(f"data-back:{EMPTY}x3;data-fwd:_gx2;ehx2;shift:code:hardcoded address", {EMPTY})
        self.assertEqual(got, [("data-back", ((EMPTY, 3),)), ("data-fwd", (("_g", 2),)), ("eh", ((None, 2),)),
                               ("shift", (("code:hardcoded address", 1),))])
        # a known name that itself ends in x<digits> keeps its spelling
        self.assertEqual(dbr.parse_failures("data-back:_boxx2", {"_boxx2"}), [("data-back", (("_boxx2", 1),))])
        # a predicate works as `known`
        self.assertEqual(dbr.parse_failures("data-back:_gx2", lambda s: s == "_g"), [("data-back", (("_g", 2),))])

    def test_unique_bytes(self):
        self.assertEqual(dbr.unique_bytes([(0, 10), (5, 20), (30, 31), (0, 4)]), 21)
        self.assertEqual(dbr.unique_bytes([]), 0)

    def test_name_facts(self):
        self.assertTrue(dbr.invented("?g_Va00BBB8D8@@3MA"))
        self.assertTrue(dbr.invented("?g_00DFE758@@3PAXA"))
        self.assertTrue(dbr.invented("?rva00094B08One@@3MB"))
        self.assertTrue(dbr.invented(INVENTED_EMPTY))
        self.assertTrue(dbr.invented("??_7Rva007F01B0@@6B@"))         # a vtable of an invented class
        self.assertFalse(dbr.invented("__real@3f800000"))              # an emitted literal
        self.assertFalse(dbr.invented(GD_V))
        self.assertEqual(dbr.split_type(GD_U), ("?TheWritableGlobalData@@", "3PAUGlobalData@@A"))
        self.assertEqual(dbr.split_type(NULLCHR)[1], "4DB")
        self.assertEqual(dbr.variant_kind("3PAUGlobalData@@A", "3PAVGlobalData@@A"), "struct/class")
        self.assertEqual(dbr.variant_kind("3MA", "3MB"), "const")
        self.assertEqual(dbr.variant_kind("3HA", "3IA"), "type")
        self.assertEqual(dbr.variant_kind("3PAXA", "3PAURva00DFE758Holder@@A"), "type")

    def test_ledger_statics(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ledger.csv"
            write_csv(path, LEDGER)
            ledger = dbr.load_ledger(path)
        self.assertIn(("_TheGameLogic", "Code/A.cpp"), ledger[0x200000]["bound"])
        index = dbr.name_index(ledger)
        self.assertEqual(dbr.resolve("_TheGameLogic", "Code/A.cpp", index), ({0x200000}, False))
        self.assertEqual(dbr.resolve("_TheGameLogic", "Code/B.cpp", index), (set(), False))
        # a single-name owned row with no object read is of unknown scope: sure only for its owner
        self.assertEqual(dbr.resolve("?g_one@@3HA", "Code/X.cpp", index), ({0x300000}, True))
        self.assertEqual(dbr.resolve("?g_one@@3HA", "Code/C.cpp", index), ({0x300000}, False))
        # its owner's object defines it EXTERNAL: global
        dbr.scope_bindings(ledger, {"Code/C.cpp": (frozenset(), frozenset({"?g_one@@3HA"}), frozenset(),
                                                   frozenset())})
        self.assertEqual(dbr.resolve("?g_one@@3HA", "Code/X.cpp", dbr.name_index(ledger)), ({0x300000}, False))


class Ranking(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        t = Path(self.tmp.name)
        write_csv(t / "ledger.csv", LEDGER)
        write_csv(t / "functions.csv", FUNCTIONS)
        buf = io.StringIO()
        w = csv.writer(buf, lineterminator="\n")
        w.writerow(STATUS_COLS)
        for name, kind, source, rva, size, placed, fails in STATUS:
            w.writerow([name, kind, source, f"0x{rva:08X}", size, "", placed, "", 0, 0, 0, 0, 0, 0,
                        fails.count(";") + 1, fails])
        with gzip.open(t / "link_status-0123456789.csv.gz", "wt", encoding="utf-8", newline="") as f:
            f.write(buf.getvalue())
        write_csv(t / "xrefs.tsv", [["rva", "section", "size_bound", "widths", "float", "kinds", "ref_count",
                                     "callers"],
                                    ["0x00100000", ".rdata", "1", "", "0", "address", "3", "0x00001000,0x00004000"],
                                    ["0x00200000", ".data", "4", "4", "0", "read", "1", "0x00004000"]],
                  delimiter="\t")
        self.t = t

    def tearDown(self):
        self.tmp.cleanup()

    def run_tool(self, *extra):
        t = self.t
        out = io.StringIO()
        with redirect_stdout(out):
            dbr.main(["--ledger", str(t / "ledger.csv"), "--functions", str(t / "functions.csv"),
                      "--xrefs", str(t / "xrefs.tsv"), "--no-objects", "--json", str(t / "out.json"), *extra])
        return out.getvalue(), json.loads((t / "out.json").read_text(encoding="utf-8"))

    def test_status_ranking(self):
        text, report = self.run_tool("--status", str(self.t / "link_status-0123456789.csv.gz"))
        self.assertEqual(report["mode"], "status")
        self.assertNotIn("PROVISIONAL", text)
        self.assertEqual(report["totals"], {"rows": 5, "bytes": 0xB4 + 40 + 8 + 16, "ambiguous_rows": 0,
                                            "scope_unknown_rows": 0, "unmapped_rows": 1, "disambiguated": 0})
        self.assertEqual(report["ambiguous"], [])
        first, second = report["addresses"]
        self.assertEqual(first["address"], "0x00100000")
        self.assertEqual((first["rows"], first["bytes"]), (3, 0xB4 + 16))     # r1+r2 overlap, r7
        self.assertEqual((first["sole_rows"], first["sole_bytes"]), (1, 100))  # only r2
        self.assertEqual(first["other_blockers"], {"data-fwd": 1, "data-back elsewhere": 1})
        by = {x["symbol"]: x for x in first["names"]}
        self.assertEqual((by[EMPTY]["rows"], by[NULLCHR]["rows"], by[INVENTED_EMPTY]["rows"]), (2, 1, 0))
        self.assertTrue(by[INVENTED_EMPTY]["invented"])
        self.assertEqual(second["address"], "0x00200000")
        self.assertEqual((second["rows"], second["bytes"], second["sole_bytes"]), (2, 56, 40))
        by = {(x["symbol"], x["local_source"]): x for x in second["names"]}
        self.assertEqual(by[(GD_U, None)]["variant"], "struct/class")
        self.assertEqual(by[("_TheGameLogic", "Code/A.cpp")]["rows"], 1)
        self.assertEqual(report["unmapped"], {"_TheGameLogic": 1})

    def test_provisional_fallback(self):
        text, report = self.run_tool("--refs", "xrefs")
        self.assertTrue(text.startswith("PROVISIONAL"))
        self.assertEqual(report["mode"], "provisional")
        got = {a["address"]: (a["rows"], a["bytes"]) for a in report["addresses"]}
        # single-name, single-definition 0x300000 is no candidate; the gen-alias row is not counted
        self.assertEqual(got, {"0x00100000": (2, 116), "0x00200000": (1, 16)})

    def test_address_filter(self):
        text, report = self.run_tool("--status", str(self.t / "link_status-0123456789.csv.gz"),
                                     "--address", "0x200000")
        self.assertEqual([a["address"] for a in report["addresses"]], ["0x00200000"])
        self.assertIn("_TheGameLogic @Code/A.cpp", text)


FLOAT = "__real@c7c34ff3"
LEDGER_HEAD = LEDGER[0]


def status_csv(path, rows, cols=STATUS_COLS):
    """A link_cycle link_status.csv of (name, source, rva, size, failures) placed real rows."""
    out = [cols]
    for name, source, rva, size, fails in rows:
        out.append([name, "real", source, f"0x{rva:08X}", size, "", "1", "", 0, 0, 0, 0, 0, 0,
                    fails.count(";") + 1, fails])
    write_csv(path, out)


class ReviewFixes(unittest.TestCase):
    """One regression per finding of the reviews of 514ebfa15b and 2e88417974; each
    fails on the code it was found in."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.t = Path(self.tmp.name)
        write_csv(self.t / "functions.csv", FUNCTIONS)

    def tearDown(self):
        self.tmp.cleanup()

    def run_status(self, ledger, status, *extra, objects=None):
        """main --status over a ledger fixture; `objects` {source: [(name, section,
        storage)]} writes COFF objects to scan (None: --no-objects)."""
        write_csv(self.t / "ledger.csv", [LEDGER_HEAD] + ledger)
        status_csv(self.t / "status.csv", status)
        if objects is None:
            scan = ["--no-objects"]
        else:
            objs = self.t / "match"
            objs.mkdir(exist_ok=True)
            for source, symbols in objects.items():
                (objs / dbr.object_name(source)).write_bytes(coff(symbols))
            scan = ["--objects", str(objs), "--no-cache"]
        with redirect_stdout(io.StringIO()):
            dbr.main(["--ledger", str(self.t / "ledger.csv"), "--functions", str(self.t / "functions.csv"),
                      "--status", str(self.t / "status.csv"), "--json", str(self.t / "out.json"), *scan, *extra])
        return json.loads((self.t / "out.json").read_text(encoding="utf-8"))

    def test_singleton_statics_keep_their_scope(self):
        # P1: a single-name row's static is matched from its own source only
        ledger = [
            ["0x00400000", "52", ".rdata", "global", "_s_vtable", "Code/V1.cpp", "owned", "", "1", "1"],
            ["0x00400100", "52", ".rdata", "global", "_s_vtable", "Code/V2.cpp", "owned", "", "1", "1"],
            ["0x00400200", "52", ".rdata", "vtable", "??_7Foo@@6B@", "", "literal",
             "??_7Foo@@6B@;_s_vtable@Code/V3.cpp", "1", "2"],
            ["0x00400300", "4", ".data", "global", "_s_only", "Code/V4.cpp", "owned", "", "1", "1"],
            ["0x00400400", "4", ".data", "global", "?g_x@@3HA", "Code/V5.cpp", "provisional",
             "?g_x@@3HA;_s_only@Code/V5.cpp", "1", "2"],
            ["0x00400500", "4", ".data", "global", "?g_one@@3HA", "Code/C.cpp", "owned", "", "1", "3"],
        ]
        report = self.run_status(ledger, [
            ("u1", "Code/Unrelated.cpp", 0x8000, 50, "data-back:_s_vtable"),
            ("v1", "Code/V1.cpp", 0x8100, 30, "data-back:_s_vtable"),
            ("u2", "Code/Unrelated.cpp", 0x8200, 20, "data-back:_s_only"),
            ("u3", "Code/Unrelated.cpp", 0x8300, 10, "data-back:?g_one@@3HA"),   # an external: any source
        ], objects={"Code/V1.cpp": [("_s_vtable", 2, dbr.STATIC)], "Code/V2.cpp": [("_s_vtable", 2, dbr.STATIC)],
                    "Code/V4.cpp": [("_s_only", 2, dbr.STATIC)], "Code/C.cpp": [("?g_one@@3HA", 2, dbr.EXTERNAL)]})
        got = {a["address"]: (a["rows"], a["bytes"]) for a in report["addresses"]}
        self.assertEqual(got, {"0x00400000": (1, 30), "0x00400500": (1, 10)})
        self.assertEqual(report["unmapped"], {"_s_vtable": 1, "_s_only": 1})
        first = next(a for a in report["addresses"] if a["address"] == "0x00400000")
        self.assertEqual([(x["symbol"], x["local_source"]) for x in first["names"]], [("_s_vtable", "Code/V1.cpp")])

    def test_unique_singleton_static_is_not_global(self):
        # round 2, P1: a static named once in the ledger, so no other row's spelling
        # proves it; its owner's object (storage class STATIC) does
        ledger = [["0x007C4F10", "476", ".rdata", "global", "_s_environmentNames", "Code/Env.cpp", "owned", "",
                   "1", "3"]]
        report = self.run_status(ledger, [
            ("u", "Code/Unrelated.cpp", 0x8000, 50, "data-back:_s_environmentNames"),
            ("e", "Code/Env.cpp", 0x8100, 30, "data-back:_s_environmentNames"),
        ], objects={"Code/Env.cpp": [("_s_environmentNames", 2, dbr.STATIC)]})
        got = {a["address"]: (a["rows"], a["bytes"]) for a in report["addresses"]}
        self.assertEqual(got, {"0x007C4F10": (1, 30)})
        self.assertEqual(report["unmapped"], {"_s_environmentNames": 1})
        self.assertEqual(report["addresses"][0]["names"][0]["scope"], "static")

    def test_external_is_not_lost_to_a_same_named_static(self):
        # round 2, P1: another TU's static spelled `_shared` does not make the
        # external `_shared` (EXTERNAL in its owner's object) TU-local
        ledger = [["0x00400000", "4", ".data", "global", "_shared", "Code/Def.cpp", "owned", "", "1", "2"],
                  ["0x00400100", "4", ".data", "global", "?g_y@@3HA", "Code/Other.cpp", "provisional",
                   "?g_y@@3HA;_shared@Code/Other.cpp", "1", "2"]]
        report = self.run_status(ledger, [
            ("u", "Code/User.cpp", 0x8000, 40, "data-back:_shared"),
            ("o", "Code/Other.cpp", 0x8100, 20, "data-back:_shared"),
        ], objects={"Code/Def.cpp": [("_shared", 2, dbr.EXTERNAL)], "Code/Other.cpp": [("_shared", 2, dbr.STATIC)]})
        got = {a["address"]: (a["rows"], a["bytes"]) for a in report["addresses"]}
        self.assertEqual(got, {"0x00400000": (1, 40), "0x00400100": (1, 20)})
        self.assertEqual(report["unmapped"], {})

    def test_binding_without_an_object_is_of_unknown_scope(self):
        # round 2, P1: no owner object, no proof either way: its owner's rows map, others are quarantined
        ledger = [["0x00400000", "4", ".data", "global", "_s_maybe", "Code/NoObj.cpp", "owned", "", "1", "2"]]
        report = self.run_status(ledger, [
            ("u", "Code/Unrelated.cpp", 0x8000, 40, "data-back:_s_maybe"),
            ("n", "Code/NoObj.cpp", 0x8100, 20, "data-back:_s_maybe"),
        ], objects={})
        got = {a["address"]: (a["rows"], a["bytes"]) for a in report["addresses"]}
        self.assertEqual(got, {"0x00400000": (1, 20)})
        self.assertEqual(report["ambiguous"], [{"symbol": "_s_maybe", "reason": "scope unknown",
                                                "candidates": ["0x00400000"], "rows": 1, "bytes": 40}])
        self.assertEqual((report["totals"]["scope_unknown_rows"], report["unmapped"]), (1, {}))
        self.assertEqual(report["addresses"][0]["names"][0]["scope"], "unknown")

    def test_ambiguous_symbol_is_quarantined(self):
        # P1: a symbol with several ledger addresses counts at none of them
        floats = [f"0x{0x7F9000 + 0x100 * k:08X}" for k in range(3)]
        ledger = [[a, "8", ".rdata", "float", FLOAT, "", "literal", "", "0", "1"] for a in floats]
        ledger.append(["0x00400500", "4", ".data", "global", "?g_one@@3HA", "Code/C.cpp", "owned", "", "1", "3"])
        report = self.run_status(ledger, [
            ("r", "Code/S.cpp", 0x8000, 100, f"data-back:{FLOAT};data-back:?g_one@@3HA"),
            ("q", "Code/Q.cpp", 0x9000, 40, f"data-back:{FLOAT}"),
        ], objects={"Code/C.cpp": [("?g_one@@3HA", 2, dbr.EXTERNAL)]})
        self.assertEqual([a["address"] for a in report["addresses"]], ["0x00400500"])
        one = report["addresses"][0]
        self.assertEqual((one["rows"], one["bytes"], one["sole_rows"]), (1, 100, 0))
        self.assertEqual(one["other_blockers"], {"data-back ambiguous": 1})
        self.assertEqual(report["ambiguous"], [{"symbol": FLOAT, "reason": "several addresses",
                                                "candidates": floats, "rows": 2, "bytes": 140}])
        self.assertEqual(report["totals"]["ambiguous_rows"], 2)

    def test_references_settle_an_ambiguous_symbol(self):
        # ... unless every reference to it in the row's object names one candidate
        floats = [0x7F9000 + 0x100 * k for k in range(3)]
        ledger = {a: {"bound": [(FLOAT, None)], "names": "", "size": 8, "kind": "float", "status": "literal",
                      "source": "", "name": FLOAT, "unknown": {}} for a in floats}
        path = self.t / "status.csv"
        status_csv(path, [("r", "Code/S.cpp", 0x8000, 100, f"data-back:{FLOAT}"),
                          ("q", "Code/Q.cpp", 0x9000, 40, f"data-back:{FLOAT}")])
        refs = {"r": [(FLOAT, floats[1]), ("?other@@3MA", floats[0])],   # another symbol's reference is not its
                "q": [(FLOAT, floats[0]), (FLOAT, floats[2])]}           # two references, two candidates
        hits, _rows, back_of, flags_of, *_rest, ambiguous, totals = dbr.refs_from_status(
            path, ledger, "real", lambda rec: refs[rec["name"]])
        self.assertEqual({a: h["rows"] for a, h in hits.items()}, {floats[1]: {0}})
        self.assertEqual((back_of, flags_of), ([{floats[1]}, set()], [set(), {dbr.AMBIGUOUS}]))
        self.assertEqual(dict(ambiguous), {(FLOAT, "several addresses", tuple(floats)): {1}})
        self.assertEqual(totals["disambiguated"], 1)
        self.assertEqual([dbr.row_unresolved(f) for f in flags_of], [False, True])

    def test_disambiguation_needs_every_reference_at_its_datum(self):
        # round 2, P1: references at A and B+4 (an interior reference to the datum at B)
        # leave the symbol ambiguous; A and A+4 settle it at A. The retail target alone
        # cannot tell B+4 from a neighbour of B, the reference's addend can.
        vtable, a, b, base = "??_7Foo@@6B@", 0x7F0000, 0x7F0100, dbr.IMAGE_BASE
        ledger = {x: {"bound": [(vtable, None)], "names": "", "size": 52, "kind": "vtable", "status": "literal",
                      "source": "", "name": vtable, "unknown": {}} for x in (a, b)}
        path = self.t / "status.csv"
        status_csv(path, [("r", "Code/R.cpp", 0x8000, 100, f"data-back:{vtable}"),
                          ("p", "Code/P.cpp", 0x9000, 100, f"data-back:{vtable}")])
        relocs = [(0x10, 6, vtable), (0x20, 6, vtable)]                  # IMAGE_REL_I386_DIR32
        body = bytearray(100)
        struct.pack_into("<I", body, 0x20, 4)                             # in-place addend: vtable+4
        target = {"r": bytearray(100), "p": bytearray(100)}
        for name, second in (("r", b), ("p", a)):
            struct.pack_into("<I", target[name], 0x10, a + base)
            struct.pack_into("<I", target[name], 0x20, second + 4 + base)

        def references(*args):
            if len(args) == 2:          # 2e88417974's targets_of(rva, size): retail targets alone
                return {a, b + 4} if args[0] == 0x8000 else {a, a + 4}
            name = args[0]["name"]
            return dbr.datum_starts(bytes(body), bytes(target[name]), relocs, 100)

        hits, _rows, back_of, flags_of, *_rest, ambiguous, totals = dbr.refs_from_status(
            path, ledger, "real", references)
        self.assertEqual({x: h["rows"] for x, h in hits.items()}, {a: {1}})
        self.assertEqual((back_of, flags_of), ([set(), {a}], [{"ambiguous"}, set()]))
        self.assertEqual(dict(ambiguous), {(vtable, "several addresses", (a, b)): {0}})
        self.assertEqual(totals["disambiguated"], 1)
        self.assertEqual(dbr.datum_starts(bytes(body), bytes(target["r"]), relocs, 100), [(vtable, a), (vtable, b)])
        self.assertTrue(dbr.row_unresolved(flags_of[0]))

    def test_wrong_input_schema_is_refused(self):
        # P2: the census's reverse/link_status.csv (per file) is not link_cycle's per-row table
        write_csv(self.t / "ledger.csv", LEDGER)
        census = self.t / "link_status.csv"
        write_csv(census, [["source", "linked", "unresolved", "duplicates", "comdat_losers", "addresses",
                            "wrong_selected"], ["Code/A.cpp", "1", "0", "0", "0", "0", "0"]])
        for path in (census, self.t / "trimmed.csv"):
            if path != census:          # link_cycle's header less one column
                status_csv(path, [("r", "Code/S.cpp", 0x8000, 100, "data-back:_x")], STATUS_COLS[:-1])
            with self.assertRaises(SystemExit) as caught, redirect_stdout(io.StringIO()):
                dbr.main(["--ledger", str(self.t / "ledger.csv"), "--functions", str(self.t / "functions.csv"),
                          "--status", str(path), "--no-objects"])
            self.assertIn("not link_cycle's per-row link_status.csv", str(caught.exception.code))
            self.assertIn("failures", str(caught.exception.code))

    def test_repeat_suffix_that_reads_two_ways(self):
        # P3: `_gx2` is `_gx2` once or `_g` twice; both resolving is flagged, not guessed
        both = {"_g", "_gx2"}
        self.assertEqual(dbr.parse_failures("data-back:_gx2", both), [("data-back", (("_gx2", 1), ("_g", 2)))])
        self.assertEqual(dbr.parse_failures("data-back:_gx2", {"_gx2"}), [("data-back", (("_gx2", 1),))])
        self.assertEqual(dbr.parse_failures("data-back:_gx2", {"_g"}), [("data-back", (("_g", 2),))])
        # link_cycle writes a repeat only for a count of two or more
        self.assertEqual(dbr.parse_failures("data-back:_ax1;data-back:_bx02", ()),
                         [("data-back", (("_ax1", 1),)), ("data-back", (("_bx02", 1),))])
        ledger = [["0x00400000", "4", ".data", "global", "_g", "", "unowned", "", "0", "1"],
                  ["0x00400100", "4", ".data", "global", "_gx2", "", "unowned", "", "0", "1"]]
        report = self.run_status(ledger, [("r", "Code/S.cpp", 0x8000, 64, "data-back:_gx2")])
        self.assertEqual(report["addresses"], [])
        self.assertEqual(report["ambiguous"], [{"symbol": "_gx2", "reason": "repeat suffix",
                                                "candidates": ["0x00400000", "0x00400100"], "rows": 1,
                                                "bytes": 64}])

    def test_site_in_a_long_row_after_nine_shorter_ones(self):
        # P3: the containing row is found however many rows start between it and the site
        ledger = {0x500000: {"size": 4, "kind": "global"}, 0x600000: {"size": 4, "kind": "global"}}
        rows = [(0x1000, 0x1000, "long", "Code/L.cpp")]
        rows += [(0x1010 + 0x10 * k, 8, f"s{k}", "Code/S.cpp") for k in range(9)]
        got = dbr.attribute(ledger, rows, {0x500000, 0x600000},
                            [(0x1800, 0x500000), (0x1014, 0x600002), (0x3000, 0x500000)])
        self.assertEqual(dict(got), {0x500000: {0}, 0x600000: {0, 1}})
        self.assertEqual(dbr.containing(dbr.interval_index(rows), 0x1800), {0})
        self.assertEqual(dbr.containing(dbr.interval_index(rows), 0x0FFF), set())


class Objects(unittest.TestCase):
    def test_symbol_scan_and_cache(self):
        with tempfile.TemporaryDirectory() as tmp:
            t = Path(tmp)
            objs = t / "match"
            objs.mkdir()
            (objs / dbr.object_name("Code/A.cpp")).write_bytes(coff([
                (EMPTY, 1, dbr.EXTERNAL),               # a COMDAT literal definition
                (GD_V, 2, dbr.EXTERNAL),                # defined
                ("_TheGameLogic", 2, dbr.STATIC),       # a TU-local static
                ("?unrelated@@3HA", 0, dbr.EXTERNAL)]))
            (objs / dbr.object_name("Code/B.cpp")).write_bytes(coff([(GD_V, 0, dbr.EXTERNAL),
                                                                      (GD_U, 0, dbr.EXTERNAL)]))
            wanted = frozenset({EMPTY, GD_V, GD_U, "_TheGameLogic"})
            cache = t / "cache.pkl"
            got = dbr.object_symbols(objs, {"Code/A.cpp", "Code/B.cpp", "Code/Missing.cpp"}, wanted, cache)
            self.assertEqual(set(got), {"Code/A.cpp", "Code/B.cpp"})
            ref, defined, comdat, static = got["Code/A.cpp"]
            self.assertEqual((ref, defined, comdat, static), (frozenset(), frozenset({GD_V, "_TheGameLogic"}),
                                                              frozenset({EMPTY}), frozenset({"_TheGameLogic"})))
            self.assertEqual(got["Code/B.cpp"][0], frozenset({GD_V, GD_U}))
            users, defs = dbr.name_usage(got)
            self.assertEqual((users[GD_V], defs[GD_V], users[EMPTY], defs[EMPTY]), (2, 1, 1, 0))
            self.assertTrue(cache.exists())
            self.assertEqual(dbr.object_symbols(objs, {"Code/A.cpp", "Code/B.cpp"}, wanted, cache), got)


if __name__ == "__main__":
    unittest.main()
