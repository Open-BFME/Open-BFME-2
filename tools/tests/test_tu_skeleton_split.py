"""tu_skeleton's split lane: row-to-body identification, carving, row-keyed repointing, claims."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

FILE = """// cl: /MD /O1 /Ireference/shims/x
// stlport
#include "Common/GameWindow.h"
struct GlobalA01E48 { char pad[0x54]; unsigned char flag; };
class Shell; extern Shell *TheShell;
static __forceinline int helper(int x) { return x + 1; }
static int lonely(int x) { return x; }
int plainHelper(int x) { return x * 2; }
// ?update@FadeTransition@@UAEXH@Z @0x0035F43D 97B.
void FadeTransition::update(int frame)
{
\tm_frame = helper(frame);
}
void ReverseSoundTransition::update(int frame) { m_f = frame; }
void __cdecl drawTypeText(GameWindow *w, DisplayString *s) { s->draw(w); }
TextTypeTransition::~TextTypeTransition() { }
Transition &Transition::operator=(const Transition &o) { return *this; }
template <class T> void _STL::_Construct(T *p, const T &v) { new (p) T(v); }
void Other::keepMe(void) { ((GlobalA01E48 *)TheShell)->flag = 1; }
"""


def rows(*pairs):
    return [{"name": n, "target_rva": r, "target_size": "8", "source": "Code/X.cpp", "status": "matched", "notes": ""}
            for n, r in pairs]


class NameTests(unittest.TestCase):
    def test_row_names_cover_the_ledger_shapes(self):
        self.assertEqual(T.row_names("?update@FadeTransition@@UAEXH@Z"), ("FadeTransition", "update"))
        self.assertEqual(T.row_names("??1TextTypeTransition@@UAE@XZ"), ("TextTypeTransition", "~TextTypeTransition"))
        self.assertEqual(T.row_names("??0Foo@@QAE@XZ"), ("Foo", "Foo"))
        self.assertEqual(T.row_names("??4Transition@@QAEAAV0@ABV0@@Z"), ("Transition", "operator="))
        self.assertEqual(T.row_names("?drawTypeText@@YAXPAVGameWindow@@PAVDisplayString@@@Z"), (None, "drawTypeText"))
        self.assertEqual(T.row_names("??$_Construct@VPlayingAudioRef@@V1@@_STL@@YAXPAV0@ABV0@@Z"), (None, "_Construct"))
        self.assertEqual(T.row_names("_strcmpi"), (None, "strcmpi"))
        self.assertEqual(T.row_names("_SomeStdcall@8"), (None, "SomeStdcall"))
        self.assertEqual(T.row_names("__ehhandler$?update@FadeTransition@@UAEXH@Z"), ("FadeTransition", "update"))
        self.assertEqual(T.row_names("?push_back@?$vector@DV?$allocator@D@_STL@@@_STL@@QAEXABD@Z"), ("vector", "push_back"))
        self.assertEqual(T.row_names("?tick@Inner@Outer@@QAEXXZ"), ("Inner", "tick"))
        self.assertEqual(T.row_names("??_GWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z"),
                         ("WeightInfoStruct", "~WeightInfoStruct"))
        self.assertEqual(T.row_names("??0?$vector@D@_STL@@QAE@XZ"), ("vector", "vector"))

    def test_head_names_read_definition_heads(self):
        spans = T.def_spans(FILE)
        heads = [T.head_names(c) for _, _, c, _ in spans]
        self.assertEqual(heads, [(None, "helper"), (None, "lonely"), (None, "plainHelper"),
                                 ("FadeTransition", "update"), ("ReverseSoundTransition", "update"),
                                 (None, "drawTypeText"), ("TextTypeTransition", "~TextTypeTransition"),
                                 ("Transition", "operator="), ("_STL", "_Construct"), ("Other", "keepMe")])

    def test_identify_maps_rows_to_one_body_or_reports_why_not(self):
        spans = T.def_spans(FILE)
        got = T.identify(rows(("?update@FadeTransition@@UAEXH@Z", "0x0035F43D"),
                              ("?update@ReverseSoundTransition@@UAEXH@Z", "0x0035D4E6"),
                              ("?drawTypeText@@YAXPAVGameWindow@@PAVDisplayString@@@Z", "0x0035FB6A"),
                              ("?missing@Nowhere@@UAEXXZ", "0x00000001"),
                              ("??$_Construct@VPlayingAudioRef@@V1@@_STL@@YAXPAV0@ABV0@@Z", "0x00000002")),
                         spans)
        self.assertEqual(got["0x0035F43D"], [3])
        self.assertEqual(got["0x0035D4E6"], [4])
        self.assertEqual(got["0x0035FB6A"], [5])
        self.assertEqual(got["0x00000001"], [])
        self.assertEqual(got["0x00000002"], [8])   # a template row matches by method name alone


class CarveTests(unittest.TestCase):
    def test_carved_bodies_leave_and_the_preamble_stays_on_both_sides(self):
        donor, residual = T.carve(FILE, {3, 5})   # FadeTransition::update and drawTypeText
        for side in (donor, residual):
            self.assertIn("// cl: /MD /O1 /Ireference/shims/x", side)
            self.assertIn("// stlport", side)
            self.assertIn('#include "Common/GameWindow.h"', side)
            self.assertIn("struct GlobalA01E48", side)
        self.assertIn("void FadeTransition::update(int frame)", donor)
        self.assertIn("// ?update@FadeTransition@@UAEXH@Z @0x0035F43D 97B.", donor)   # its evidence comment travels
        self.assertIn("drawTypeText(GameWindow", donor)
        self.assertNotIn("FadeTransition::update", residual)
        self.assertNotIn("drawTypeText(GameWindow", residual)
        self.assertIn("ReverseSoundTransition::update", residual)
        self.assertNotIn("ReverseSoundTransition::update", donor)
        self.assertIn("Other::keepMe", residual)

    def test_a_named_internal_helper_travels_as_a_copy_and_external_ones_never_do(self):
        donor, residual = T.carve(FILE, {3})
        self.assertIn("static __forceinline int helper", donor)      # named by the carved body
        self.assertIn("static __forceinline int helper", residual)   # and kept where it was
        self.assertNotIn("static int lonely", donor)                 # not named: stays
        self.assertNotIn("int plainHelper", donor)                   # external linkage: never copied
        self.assertIn("int plainHelper", residual)

    def test_cutting_spans_round_trips_the_rest_of_the_file(self):
        spans = T.def_spans(FILE)
        every = T.cut(FILE, [(s, e) for s, e, _, _ in spans])
        self.assertNotIn("{", every.replace("{ char pad[0x54]; unsigned char flag; }", ""))
        self.assertIn("class Shell; extern Shell *TheShell;", every)
        self.assertEqual(T.cut(FILE, []), FILE)

    def test_funclets_ride_with_their_parent(self):
        r = rows(("?update@FadeTransition@@UAEXH@Z", "0x0035F43D"),
                 ("__ehhandler$?update@FadeTransition@@UAEXH@Z", "0x0077DFFC"),
                 ("__ehhandler$?init@TextTypeTransition@@UAEXPAVGameWindow@@@Z", "0x0077E000"))
        self.assertEqual([x["target_rva"] for x in T.companions(r, {"?update@FadeTransition@@UAEXH@Z"})],
                         ["0x0077DFFC"])


SWEEP = """// cl: /MD /O1
#define BFME_DISP_BYTE_GETTER(NAME, DISP) \\
\tclass NAME { public: unsigned char get() const; char m_lead[DISP]; unsigned char m_value; }; \\
\tunsigned char NAME::get() const { return m_value; }
BFME_DISP_BYTE_GETTER(Rva0002BAF1ByteField, 0x430)
BFME_DISP_BYTE_GETTER(Rva002C8E6EByteField, 0x82)
class MilesAudioManager { public: virtual unsigned char rva000515A4() const; char m_lead[0x6A3]; unsigned char m_6A6; };
BFME_DISP_BYTE_GETTER(Rva0006520BByteField, 0x15E)
unsigned char MilesAudioManager::rva000515A4() const { return m_6A6; }
BFME_DISP_BYTE_GETTER(Rva00066509ByteField, 0x45C5C)  // trailing comment
"""


class MacroSweepTests(unittest.TestCase):
    def test_macro_invocations_are_their_own_spans_and_never_glued_onto_a_body(self):
        spans = T.def_spans(SWEEP)
        kinds = [(k, (c if k == "macro" else T.head_names(c))) for _, _, c, k in spans]
        self.assertEqual([k for k, _ in kinds], ["macro", "macro", "macro", "def", "macro"])
        self.assertEqual(kinds[3][1], ("MilesAudioManager", "rva000515A4"))
        self.assertTrue(spans[3][2].startswith("unsigned char MilesAudioManager"))   # the glued macro line was split off
        self.assertEqual(spans[2][2].strip(), "BFME_DISP_BYTE_GETTER(Rva0006520BByteField, 0x15E)")
        self.assertNotIn("#define", "".join(c for _, _, c, _ in spans))   # the macro definition is preamble

    def test_a_macro_generated_row_is_identified_by_its_class_name_and_carved_alone(self):
        spans = T.def_spans(SWEEP)
        ids = T.identify(rows(("?get@Rva002C8E6EByteField@@QBEEXZ", "0x002C8E6E"),
                              ("?rva000515A4@MilesAudioManager@@UBEEXZ", "0x000515A4"),
                              ("?get@Rva00000000ByteField@@QBEEXZ", "0x00000000")), spans)
        self.assertEqual(ids["0x002C8E6E"], [1])
        self.assertEqual(ids["0x000515A4"], [3])
        self.assertEqual(ids["0x00000000"], [])
        donor, residual = T.carve(SWEEP, {1})
        self.assertIn("BFME_DISP_BYTE_GETTER(Rva002C8E6EByteField, 0x82)", donor)
        self.assertNotIn("Rva002C8E6EByteField", residual)
        for side in (donor, residual):
            self.assertIn("#define BFME_DISP_BYTE_GETTER", side)
        self.assertIn("Rva0002BAF1ByteField", residual)
        self.assertNotIn("Rva0002BAF1ByteField", donor)
        self.assertIn("MilesAudioManager::rva000515A4", residual)
        self.assertNotIn("MilesAudioManager::rva000515A4", donor)


class IncludeRelocationTests(unittest.TestCase):
    def test_quoted_includes_follow_the_body_to_its_new_directory(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code/A/B").mkdir(parents=True)
            (root / "Code/A/C").mkdir(parents=True)
            (root / "Code/A/B/beside.h").write_text("")
            (root / "Code/A/up.h").write_text("")
            text = ('#include "beside.h"\n#include "../up.h"\n#include "Common/OnThePath.h"\n'
                    '  # include "../up.h" // again\n')
            out = T.relocate_includes(text, "Code/A/B", "Code/A/C", root=root)
            self.assertEqual(out, '#include "../B/beside.h"\n#include "../up.h"\n#include "Common/OnThePath.h"\n'
                                  '  # include "../up.h" // again\n')
            self.assertEqual(T.relocate_includes(text, "Code/A/B", "Code/A/B", root=root), text)


DATA = """// cl: /MD
#include "x.h"
int g_counter = 0;
static int s_calls;
Foo *TheFoo = NULL;
const int kLimit = 4;
static const int table[] = { 1, 2, 3 };
void (*g_hook)(int) = 0;
int plainHelper(int x);
static __forceinline int helper(int x) { return x + 1; }
static int deeper(int x) { return table[x]; }
static int rowedStatic(int x) { return x; }
void A::a() { g_counter++; TheFoo = 0; helper(1); }
void B::b() { g_counter--; rowedStatic(2); deeper(1); }
void C::c() { s_calls++; }
"""


class DataPlacementTests(unittest.TestCase):
    def spans(self):
        sp = T.def_spans(DATA)
        return sp, {T.head_names(c)[1] if k != "macro" and T.head_names(c) else c: i for i, (_, _, c, k) in enumerate(sp)}

    def test_brace_initialised_data_is_data_not_a_body(self):
        sp, _ = self.spans()
        self.assertIn("data", [k for _, _, _, k in sp])
        self.assertTrue(any(k == "data" and "table[]" in c for _, _, c, k in sp))

    def test_an_external_datum_used_on_both_sides_stays_and_the_donor_declares_it_extern(self):
        sp, ix = self.spans()
        cv = T.carve(DATA, {ix["a"]}, rowed={ix["a"], ix["b"], ix["c"], ix["rowedStatic"]})
        self.assertIsNone(cv.refused)
        self.assertIn("extern int g_counter;", cv.donor)          # used by a() and b()
        self.assertNotIn("int g_counter = 0;", cv.donor)
        self.assertIn("int g_counter = 0;", cv.residual)
        self.assertIn("Foo *TheFoo = NULL;", cv.donor)              # used only by the carved body: it moves
        self.assertNotIn("Foo *TheFoo", cv.residual)
        self.assertEqual(cv.data_moved, ["TheFoo"])
        self.assertEqual(cv.externs, ["g_counter"])
        self.assertNotIn("static int s_calls;", cv.donor)           # used only by staying bodies
        self.assertIn("void A::a()", cv.donor)
        self.assertNotIn("void A::a()", cv.residual)

    def test_an_internal_datum_used_on_both_sides_refuses_the_carve(self):
        sp, ix = self.spans()
        text = DATA.replace("void A::a() { g_counter++;", "void A::a() { g_counter++; s_calls++;")
        sp2 = T.def_spans(text)
        i = next(i for i, (_, _, c, k) in enumerate(sp2) if "A::a" in c)
        cv = T.carve(text, {i}, rowed={ix["a"], ix["b"], ix["c"], ix["rowedStatic"]})
        self.assertIsNotNone(cv.refused)
        self.assertIn("s_calls", cv.refused)
        # a copied helper that touches internal data refuses too
        text2 = DATA.replace("return x + 1;", "return x + s_calls;")
        cv2 = T.carve(text2, {i}, rowed={ix["a"], ix["b"], ix["c"], ix["rowedStatic"]})
        self.assertIn("s_calls", cv2.refused or "")

    def test_helper_copies_skip_ledger_rows_need_a_call_and_follow_their_own_calls(self):
        sp, ix = self.spans()
        cv = T.carve(DATA, {ix["b"]}, rowed={ix["a"], ix["b"], ix["c"], ix["rowedStatic"]})
        self.assertIsNone(cv.refused)
        self.assertNotIn("static int rowedStatic", cv.donor)        # a ledger row is never copied
        self.assertIn("static int deeper", cv.donor)                 # called by b(): copied
        self.assertIn("static int deeper", cv.residual)
        self.assertIn("static const int table[]", cv.donor)          # the copied deeper() reads it on both sides:
        self.assertIn("static const int table[]", cv.residual)       # a const internal datum is duplicated
        self.assertNotIn("\n;\n", cv.donor)                         # no stray semicolon left behind
        cv2 = T.carve(DATA, {ix["b"]}, rowed={ix["a"], ix["b"], ix["c"], ix["rowedStatic"]}, data_rowed={"table"})
        self.assertIn("table", cv2.refused or "")                    # unless a data row owns it
        self.assertNotIn("static __forceinline int helper", cv.donor)   # not called by b()

    def test_a_namespace_block_that_defines_anything_refuses(self):
        text = DATA + "namespace Helpers { void bump() { g_counter++; } }\n"
        sp = T.def_spans(text)
        i = next(i for i, (_, _, c, k) in enumerate(sp) if "A::a" in c)
        self.assertIn("namespace", T.carve(text, {i}).refused)
        decls = T.data_decls(DATA)
        self.assertEqual([d[3] for d in decls], ["g_counter", "s_calls", "TheFoo", "kLimit", "g_hook"])
        self.assertEqual([d[4] for d in decls], [False, True, False, True, False])

    def test_header_lines_are_never_part_of_a_span_and_a_macro_takes_its_comment(self):
        text = "// cl: /MD\nvoid F::f() { }\n// ?get@Rva1ByteField@@QBEEXZ @0x1 7B.\nBFME_X(Rva1ByteField, 0x2)\n"
        sp = T.def_spans(text)
        self.assertTrue(sp[0][2].startswith("void F::f()"))
        self.assertEqual(sp[0][0], len("// cl: /MD\n"))
        self.assertTrue(sp[1][2].startswith("// ?get@Rva1ByteField"))
        self.assertEqual(sp[1][3], "macro")


class CompanionTests(unittest.TestCase):
    def test_generated_funclets_and_deleting_destructors_ride_along(self):
        r = rows(("??1Weight@@UAE@XZ", "0x1"), ("??_GWeight@@UAEPAXI@Z", "0x2"), ("??_EWeight@@UAEPAXI@Z", "0x3"),
                 ("$L5782", "0x4"), ("?other@@YAXXZ", "0x5"), ("__ehhandler$??1Weight@@UAE@XZ", "0x6"))
        r[3]["notes"] = "gen-funclet;parent=??1Weight@@UAE@XZ; Matched parent"
        got = [x["target_rva"] for x in T.companions(r, {"??1Weight@@UAE@XZ"})]
        self.assertEqual(got, ["0x2", "0x3", "0x4", "0x6"])


class FuncletDonorTests(unittest.TestCase):
    def test_a_funclet_row_counts_with_its_parent_in_donors(self):
        T._CACHE.clear()
        T._CACHE["ledger"] = rows(("?update@FadeTransition@@UAEXH@Z", "0x0035F43D"),
                                  ("__ehhandler$?update@FadeTransition@@UAEXH@Z", "0x0077DFFC"))
        T._CACHE["map"] = [{"rva": "0x0035F43D", "size": "97", "kind": "code", "tu": "Code/T.cpp",
                            "confidence": "approved", "by": "-", "evidence": "", "source": "Code/X.cpp"}]
        T._CACHE["stale"] = False
        try:
            sk = T.skeleton("Code/T.cpp")
            don, mixed, refused = T.donors("Code/T.cpp", sk)
        finally:
            T._CACHE.clear()
        self.assertEqual(mixed, {})                      # the unplaced funclet does not make the file mixed
        self.assertEqual(sorted(don), ["Code/X.cpp"]) if "Code/X.cpp" in don else self.assertIn("Code/X.cpp", refused)


HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


class RepointTests(unittest.TestCase):
    def test_only_the_keyed_rows_of_the_old_source_move(self):
        raw = (HEADER + "?a@@YAXXZ,,0x00001000,8,Code/Mixed.cpp,matched,\n"
               "?b@@YAXXZ,,0x00001010,8,Code/Mixed.cpp,matched,keeps Code/Mixed.cpp in notes\n"
               "?c@@YAXXZ,,0x00001020,8,Code/Mixed.cpp,matched,\n"
               "?d@@YAXXZ,,0x00001000,8,Code/Other.cpp,matched,\n").encode()
        out, n = T.repoint_rows(raw, "reverse/functions.csv", "target_rva", {"0x00001000", "0X00001010"},
                                "source", "Code/Mixed.cpp", "Code/T.cpp")
        self.assertEqual(n, 2)
        text = out.decode()
        self.assertIn("?a@@YAXXZ,,0x00001000,8,Code/T.cpp,matched,\n", text)
        self.assertIn("0x00001010,8,Code/T.cpp,matched,keeps Code/Mixed.cpp in notes\n", text)   # notes untouched
        self.assertIn("?c@@YAXXZ,,0x00001020,8,Code/Mixed.cpp,matched,\n", text)            # not keyed: stays
        self.assertIn("?d@@YAXXZ,,0x00001000,8,Code/Other.cpp,matched,\n", text)            # keyed, other source: stays

    def test_apply_split_writes_both_files_and_repoints_three_ledgers(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            import subprocess
            subprocess.run(["git", "init", "-q"], cwd=root, check=True)
            (root / "reverse").mkdir()
            (root / "docs/doxygen").mkdir(parents=True)
            (root / "Code").mkdir()
            (root / "Code/Mixed.cpp").write_text("old\n")
            (root / "reverse/functions.csv").write_text(
                HEADER + "?a@@YAXXZ,,0x00001000,8,Code/Mixed.cpp,matched,\n"
                "?c@@YAXXZ,,0x00001020,8,Code/Mixed.cpp,matched,\n")
            (root / "reverse/tu_map.csv").write_text(
                "rva,size,kind,tu,confidence,by,evidence,source\n"
                "0x00001000,8,code,Code/T.cpp,approved,-,,Code/Mixed.cpp\n"
                "0x00001020,8,code,,,-,,Code/Mixed.cpp\n")
            (root / "reverse/body_owners.csv").write_text(
                "target_rva,name,target_size,source,evidence\n0x00001000,?a@@YAXXZ,8,Code/Mixed.cpp,x\n")
            (root / "docs/doxygen/sources.cfg").write_text("INPUT += Code/Mixed.cpp\n")
            moved = T.apply_split("Code/T.cpp", "tu text\n", "Code/Mixed.cpp", "residual\n", ["0x00001000"],
                                  False, root=root)
            self.assertEqual(moved, {"reverse/functions.csv": 1, "reverse/tu_map.csv": 1,
                                     "reverse/body_owners.csv": 1, "docs/doxygen/sources.cfg": 1})
            self.assertEqual((root / "Code/T.cpp").read_text(), "tu text\n")
            self.assertEqual((root / "Code/Mixed.cpp").read_text(), "residual\n")
            self.assertIn("0x00001000,8,Code/T.cpp,matched", (root / "reverse/functions.csv").read_text())
            self.assertIn("0x00001020,8,Code/Mixed.cpp,matched", (root / "reverse/functions.csv").read_text())
            self.assertIn("0x00001000,8,code,Code/T.cpp,approved,-,,Code/T.cpp", (root / "reverse/tu_map.csv").read_text())
            self.assertIn("0x00001020,8,code,,,-,,Code/Mixed.cpp", (root / "reverse/tu_map.csv").read_text())
            self.assertEqual((root / "docs/doxygen/sources.cfg").read_text(),
                             "INPUT += Code/Mixed.cpp\nINPUT += Code/T.cpp\n")
            staged = subprocess.run(["git", "diff", "--cached", "--name-only"], cwd=root,
                                    capture_output=True, text=True).stdout.split()
            self.assertEqual(sorted(staged), ["Code/Mixed.cpp", "Code/T.cpp", "docs/doxygen/sources.cfg",
                                              "reverse/body_owners.csv", "reverse/functions.csv",
                                              "reverse/tu_map.csv"])

    def test_sources_cfg_gains_the_tu_once(self):
        raw = b"INPUT += Code/Mixed.cpp\n"
        out, n = T.ensure_sources_cfg(raw, "Code/T.cpp")
        self.assertEqual((out, n), (b"INPUT += Code/Mixed.cpp\nINPUT += Code/T.cpp\n", 1))
        self.assertEqual(T.ensure_sources_cfg(out, "Code/T.cpp"), (out, 0))


class ClaimTests(unittest.TestCase):
    def test_the_split_scope_is_the_tu_the_mixed_file_and_the_moved_rows(self):
        self.assertEqual(T.claim_keys("Code/T.cpp", {"Code/Mixed.cpp": rows(("?a@@YAXXZ", "0x00001000"))}),
                         ["file:Code/T.cpp", "file:Code/Mixed.cpp", "0x00001000"])


if __name__ == "__main__":
    unittest.main()
