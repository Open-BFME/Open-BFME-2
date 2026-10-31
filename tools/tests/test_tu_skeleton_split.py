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
    def test_unused_hatch_extern_is_not_copied_and_evidence_stays(self):
        text = ('// evidence remains\nextern unsigned int g_Va00DD828C;\n'
                'int moved() { return 7; }\nint stays() { return g_Va00DD828C; }\n')
        cv = T.carve(text, {0}, {0, 1})
        self.assertNotIn('extern unsigned int g_Va00DD828C;', cv.donor)
        self.assertIn('// evidence remains', cv.donor)
        self.assertIn('extern unsigned int g_Va00DD828C;', cv.residual)

    def test_used_hatch_extern_is_copied_and_unused_residual_is_pruned(self):
        text = ('extern int g_Va00DD828C;\n'
                'int moved() { return g_Va00DD828C; }\nint stays() { return 0; }\n')
        cv = T.carve(text, {0}, {0, 1})
        self.assertIn('extern int g_Va00DD828C;', cv.donor)
        self.assertNotIn('extern int g_Va00DD828C;', cv.residual)

    def test_extern_reference_detection_uses_whole_identifier_tokens(self):
        text = ('extern int value;\nint moved() { int value_suffix = 0; '
                '/* value */ return value_suffix; }\nint stays() { return value; }\n')
        self.assertNotIn('extern int value;', T.carve(text, {0}, {0, 1}).donor)
        self.assertIn('extern int value;', T.prune_unused_externs(
            'extern int value;\nint moved() { return ns::value + p->value; }\n'))

    def test_extern_uses_in_helpers_initializers_and_macros_are_kept(self):
        for use in ('static int helper() { return value; }', 'int other = value;',
                    '#define GET value', 'struct X { int f() { return value; } };'):
            with self.subTest(use=use):
                text = 'extern int value;\n' + use + '\n'
                self.assertEqual(T.prune_unused_externs(text), text)

    def test_ambiguous_extern_contexts_are_kept(self):
        for text in ('extern int a, b;', 'extern int (*fp)(int);',
                     'extern /* evidence */ int a;',
                     'extern int a = 1;', 'extern TYPE(NAME);',
                     '#if ENABLED\nextern int a;\n#endif',
                     'extern int a;\n#include "inline_users.h"',
                     '#define JOIN(a,b) a ## b\nextern int a;',
                     'extern int a;\nint f() { return a\\\n; }'):
            with self.subTest(text=text):
                self.assertEqual(T.prune_unused_externs(text), text)

    def test_shared_live_hatch_extern_still_refuses_growth(self):
        text = ('extern int g_Va00DD828C;\n'
                'int moved() { return g_Va00DD828C; }\n'
                'int stays() { return g_Va00DD828C; }\n')
        cv = T.carve(text, {0}, {0, 1})
        for side in (cv.donor, cv.residual):
            self.assertIn('extern int g_Va00DD828C;', side)
        self.assertIsNone(T.hatch_move('Code/ExternPruneMixed.cpp', text, cv.residual,
                                      'Code/ExternPruneNew.cpp', cv.donor))

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

    def test_a_macro_with_comment_lines_above_it_still_identifies(self):
        text = ("// cl: /MD\n#define G(NAME, A, B) class NAME { public: int get() const; }; int NAME::get() const { return A; }\n"
                "// 0x004827EF: the getter behind the chase.\n// Evidence: rowed callers.\n"
                "G(Rva004827EFByteChase32Field, 0x1C, 0x114)\n")
        spans = T.def_spans(text)
        self.assertEqual([k for _, _, _, k in spans], ["macro"])
        self.assertTrue(spans[0][2].startswith("// 0x004827EF"))
        ids = T.identify(rows(("?get@Rva004827EFByteChase32Field@@QBEHXZ", "0x004827EF")), spans)
        self.assertEqual(ids["0x004827EF"], [0])

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
    def test_initialized_extern_table_moves_with_its_only_user(self):
        text = ('extern const int table[] = { 1, 0 };\n'
                'void moved() { use(table); }\nvoid stays() {}\n')
        cv = T.carve(text, {0}, data_rowed={"table"})
        self.assertIsNone(cv.refused)
        self.assertEqual(cv.data_moved, ["table"])
        self.assertIn('extern const int table[] = { 1, 0 };', cv.donor)
        self.assertNotIn('table', cv.residual)

    def test_initialized_extern_const_is_external_when_both_sides_use_it(self):
        for definition in ('extern const int table[] = { 1, 0 };',
                           'extern const int table = 1;'):
            with self.subTest(definition=definition):
                text = definition + '\nvoid moved() { use(table); }\nvoid stays() { use(table); }\n'
                cv = T.carve(text, {0}, data_rowed={"table"})
                self.assertIsNone(cv.refused)
                self.assertEqual(cv.externs, ["table"])
                self.assertIn(definition, cv.residual)
                self.assertNotIn(definition, cv.donor)
                self.assertNotIn('extern extern', cv.donor)
                self.assertIn('extern const int table', cv.donor)

    def test_uninitialized_externs_follow_their_users(self):
        text = ('extern const int table[];\nextern int counter;\n'
                'void moved() { use(table); }\nvoid stays() { counter++; }\n')
        cv = T.carve(text, {0})
        self.assertEqual(T.data_decls(text), [])
        self.assertIn('extern const int table[];', cv.donor)
        self.assertNotIn('extern int counter;', cv.donor)
        self.assertNotIn('extern const int table[];', cv.residual)
        self.assertIn('extern int counter;', cv.residual)

    def spans(self):
        sp = T.def_spans(DATA)
        return sp, {T.head_names(c)[1] if k != "macro" and T.head_names(c) else c: i for i, (_, _, c, k) in enumerate(sp)}

    def test_brace_initialised_data_is_a_datum_not_a_body(self):
        sp, _ = self.spans()
        self.assertFalse(any("table[]" in c for _, _, c, _ in sp))          # not a body span at all
        self.assertIn("table", [d[3] for d in T.data_decls(DATA)])          # a file-scope object definition
        kinds = [k for k, _ in T.chunks(DATA)]
        self.assertNotIn(";", [c.strip() for _, c in T.chunks(DATA)])       # no stray semicolon item

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

    def test_a_namespace_block_that_defines_something_no_longer_refuses(self):
        text = DATA + "namespace Helpers { void bump() { g_counter++; } }\n"
        sp = T.def_spans(text)
        i = next(i for i, (_, _, c, k) in enumerate(sp) if "A::a" in c)
        cv = T.carve(text, {i})
        self.assertIsNone(cv.refused)
        self.assertIn("namespace Helpers {", cv.donor)              # the block stays on both sides
        self.assertIn("namespace Helpers {", cv.residual)
        self.assertNotIn("void bump()", cv.donor)                   # its external body stays behind
        self.assertIn("void bump()", cv.residual)
        decls = T.data_decls(DATA)
        self.assertEqual([d[3] for d in decls], ["g_counter", "s_calls", "TheFoo", "kLimit", "table", "g_hook"])
        self.assertEqual([d[4] for d in decls], [False, True, False, True, True, False])

    def test_header_lines_are_never_part_of_a_span_and_a_macro_takes_its_comment(self):
        text = "// cl: /MD\nvoid F::f() { }\n// ?get@Rva1ByteField@@QBEEXZ @0x1 7B.\nBFME_X(Rva1ByteField, 0x2)\n"
        sp = T.def_spans(text)
        self.assertTrue(sp[0][2].startswith("void F::f()"))
        self.assertEqual(sp[0][0], len("// cl: /MD\n"))
        self.assertTrue(sp[1][2].startswith("// ?get@Rva1ByteField"))
        self.assertEqual(sp[1][3], "macro")


BLOCKS = """// cl: /MD
#include "x.h"
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; }
template <class T> class box { public: T *get() { return m_p; } T *m_p; };
template <class T> T *first(box<T> &b) { return b.get(); }
}
namespace Audio {
int g_volume = 3;
static int s_mixes;
void setVolume(int v) { g_volume = v; }
int volume() { return g_volume; }
}
namespace {
int clampIt(int x) { return x < 0 ? 0 : x; }
}
extern "C" {
int __cdecl cmix(int a) { return clampIt(a); }
int __cdecl cpeek(void) { return Audio::s_mixes; }
}
extern "C" void __cdecl lone(void) { }
void Mixer::mix() { Audio::setVolume(1); }
"""


def balanced(text):
    code = T.code_only(text)
    return code.count("{") == code.count("}")


class BlockCarveTests(unittest.TestCase):
    """Definitions inside `namespace {}` / `extern "C" {}` blocks carve like file-scope ones."""

    def spans(self):
        sp = T.def_spans(BLOCKS)
        ix = {T.head_names(c)[1]: i for i, (_, _, c, k) in enumerate(sp) if k == "def" and T.head_names(c)}
        rowed = {ix[n] for n in ("setVolume", "volume", "cmix", "cpeek", "lone", "mix")}
        return sp, ix, rowed

    def test_definitions_inside_blocks_are_spans_with_their_scopes(self):
        sp, ix, _ = self.spans()
        self.assertEqual(sorted(ix), ["clampIt", "cmix", "cpeek", "first", "lone", "max", "mix", "setVolume", "volume"])
        self.assertFalse(any("class box" in c for _, _, c, _ in sp))       # a class stays a declaration
        sc = T.span_scopes(BLOCKS, sp)
        self.assertEqual(sc[ix["max"]], ("_STL",))
        self.assertEqual(sc[ix["setVolume"]], ("Audio",))
        self.assertEqual(sc[ix["clampIt"]], ("",))
        self.assertEqual(sc[ix["cmix"]], (None,))
        self.assertEqual(sc[ix["lone"]], ())                                 # a one-line extern "C" body
        self.assertEqual(sc[ix["mix"]], ())
        data = {d[3]: d[4] for d in T.data_decls(BLOCKS)}
        self.assertEqual(data, {"g_volume": False, "s_mixes": True})
        anon = T.data_decls("namespace { int s_hidden = 1; }\nnamespace N { int g_x; }\n")
        self.assertEqual([(d[3], d[4]) for d in anon], [("s_hidden", True), ("g_x", False)])

    def test_identify_spells_a_free_function_with_its_namespace(self):
        sp, ix, _ = self.spans()
        rs = rows(("?setVolume@Audio@@YAXH@Z", "0x1"), ("_cmix", "0x2"), ("?mix@Mixer@@QAEXXZ", "0x3"))
        got = T.identify(rs, sp, T.span_scopes(BLOCKS, sp))
        self.assertEqual(got, {"0x1": [ix["setVolume"]], "0x2": [ix["cmix"]], "0x3": [ix["mix"]]})
        self.assertEqual(T.identify(rs, sp)["0x1"], [])                      # unqualified, `?f@Audio@@` is unspelled

    def test_a_row_inside_a_namespace_leaves_with_the_block_reopened_around_it(self):
        sp, ix, rowed = self.spans()
        cv = T.carve(BLOCKS, {ix["setVolume"]}, rowed=rowed)
        self.assertIsNone(cv.refused)
        don, res = cv.donor, cv.residual
        self.assertTrue(balanced(don) and balanced(res))
        self.assertLess(don.index("namespace Audio {"), don.index("void setVolume"))
        self.assertNotIn("int volume()", don)
        self.assertIn("int volume()", res)
        self.assertNotIn("void setVolume", res)
        self.assertIn("namespace Audio {", res)
        # used by setVolume() and volume(): it stays, and the donor declares it extern inside the block
        self.assertEqual(cv.externs, ["g_volume"])
        self.assertLess(don.index("namespace Audio {"), don.index("extern int g_volume;"))
        self.assertLess(don.index("extern int g_volume;"), don.index("void setVolume"))
        self.assertIn("int g_volume = 3;", res)
        self.assertNotIn("static int s_mixes;", don)                          # only cpeek() uses it
        # inline bodies and templates in a block are emitted only where used: both sides keep them
        for text in (don, res):
            self.assertIn("static inline const unsigned int &max", text)
            self.assertIn("T *first(box<T> &b)", text)
            self.assertIn("template <class T> class box", text)

    def test_an_anonymous_namespace_helper_is_internal_and_travels_as_a_copy(self):
        sp, ix, rowed = self.spans()
        cv = T.carve(BLOCKS, {ix["cmix"]}, rowed=rowed)
        self.assertIsNone(cv.refused)
        self.assertEqual(cv.copies, [ix["clampIt"]])
        self.assertIn("int clampIt", cv.donor)
        self.assertIn("int clampIt", cv.residual)
        self.assertLess(cv.donor.index('extern "C" {'), cv.donor.index("int __cdecl cmix"))
        self.assertNotIn("cpeek", cv.donor)
        self.assertIn("cpeek", cv.residual)
        self.assertNotIn("int __cdecl cmix", cv.residual)
        self.assertTrue(balanced(cv.donor) and balanced(cv.residual))

    def test_a_one_line_extern_c_body_is_a_definition_not_a_declaration(self):
        sp, ix, rowed = self.spans()
        cv = T.carve(BLOCKS, {ix["mix"]}, rowed=rowed)
        self.assertIsNone(cv.refused)
        self.assertNotIn("lone", cv.donor)                                    # it used to be kept on both sides
        self.assertIn('extern "C" void __cdecl lone(void) { }', cv.residual)
        self.assertNotIn("int clampIt", cv.donor)                             # not called: not copied
        self.assertNotIn("void setVolume", cv.donor)
        self.assertIn("void Mixer::mix()", cv.donor)

    def test_an_internal_datum_in_a_block_used_on_both_sides_still_refuses(self):
        text = BLOCKS.replace("void setVolume(int v) { g_volume = v; }", "void setVolume(int v) { g_volume = v; s_mixes++; }")
        sp = T.def_spans(text)
        ix = {T.head_names(c)[1]: i for i, (_, _, c, k) in enumerate(sp) if k == "def" and T.head_names(c)}
        cv = T.carve(text, {ix["setVolume"]}, rowed={ix["setVolume"], ix["cpeek"]})
        self.assertIn("s_mixes", cv.refused or "")


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
                                  ("__ehhandler$?update@FadeTransition@@UAEXH@Z", "0x0077DFFC"),
                                  ("Unwind@00b636b8", "0x00B636B8"), ("??_GFadeTransition@@UAEPAXI@Z", "0x0035F500"),
                                  ("??1FadeTransition@@UAE@XZ", "0x0035F4F0"))
        T._CACHE["ledger"][2]["notes"] = "gen-funclet;parent=?update@FadeTransition@@UAEXH@Z; Matched parent"
        T._CACHE["map"] = [{"rva": "0x0035F43D", "size": "97", "kind": "code", "tu": "Code/T.cpp",
                            "confidence": "approved", "by": "-", "evidence": "", "source": "Code/X.cpp"},
                           {"rva": "0x0035F4F0", "size": "16", "kind": "code", "tu": "Code/T.cpp",
                            "confidence": "approved", "by": "-", "evidence": "", "source": "Code/X.cpp"}]
        T._CACHE["stale"] = False
        try:
            sk = T.skeleton("Code/T.cpp")
            don, mixed, refused = T.donors("Code/T.cpp", sk)
        finally:
            T._CACHE.clear()
        self.assertEqual(mixed, {})                      # the unplaced funclet does not make the file mixed
        self.assertEqual(sorted(don), ["Code/X.cpp"]) if "Code/X.cpp" in don else self.assertIn("Code/X.cpp", refused)

    def test_the_tu_file_may_keep_unplaced_rows_but_not_another_tus(self):
        # donors()' rule for the TU path in a merge: a row the map places nowhere (a
        # displaced header-inline COMDAT) stays in the seed; only another TU's row blocks.
        own = rows(("?setViewFilterPos@W3DView@@UAEXPBUCoord3D@@@Z", "0x00085F12"),
                   ("?setZoomToPos@ScreenMotionBlurFilter@@SAXPBUCoord3D@@@Z", "0x0008553B"),
                   ("__ehhandler$?setViewFilterPos@W3DView@@UAEXPBUCoord3D@@@Z", "0x0077E000"))
        assigned = {0x85F12: "code/w3dview.cpp"}
        self.assertEqual(T.placed_elsewhere("Code/W3DView.cpp", own, assigned), {})
        assigned[0x8553B] = "code/w3dshadermanager.cpp"
        self.assertEqual(T.placed_elsewhere("Code/W3DView.cpp", own, assigned), {"w3dshadermanager.cpp": 1})


SHATTER = """// cl: /MD
#include "x.h"
int g_shared = 0;
static int s_only;
int unrowedHelper(int x) { return x + g_shared; }
template <class T> T twice(T v) { return v + v; }
static int deep(int x) { return x * 3; }
void A::a() { g_shared++; unrowedHelper(1); deep(2); }
void A::a2() { s_only++; }
void B::b() { g_shared--; deep(4); }
void C::c() { twice(3); }
"""


def shatter_groups(extra_unplaced=()):
    a = rows(("?a@A@@QAEXXZ", "0x10"), ("?a2@A@@QAEXXZ", "0x20"))
    b = rows(("?b@B@@QAEXXZ", "0x30"))
    c = rows(("?c@C@@QAEXXZ", "0x40"))
    un = rows(("??1Inline@@QAE@XZ", "0x50"), ("??$twice@H@@YAHH@Z", "0x60")) + list(extra_unplaced)
    return {"Code/A.cpp": a, "Code/B.cpp": b, "Code/C.cpp": c, "": un}


ALT = """// cl: /MD
#pragma comment(linker, "/alternatename:?go@Mover@@QAEXXZ=?run@Base@@QAEXXZ")
#pragma comment(linker, "/alternatename:?stop@Mover@@QAEXXZ=?run@Base@@QAEXXZ")
#pragma comment(linker, "/alternatename:?both@@YAXXZ=?run@Base@@QAEXXZ")
#pragma comment(linker, "/alternatename:?none@@YAXXZ=?run@Base@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Ring@@UAE@XZ=?run@Base@@QAEXXZ")
void A::a() { m->go(); both(); }
void B::b() { m->stop(); both(); Ring r; }
"""


class AlternatenameRoutingTests(unittest.TestCase):
    """A carved body's /alternatename directive moves with it instead of being counted twice."""

    def carve(self, **kw):
        sp = T.def_spans(ALT)
        i = next(i for i, (_, _, c, _) in enumerate(sp) if "A::a" in c)
        return T.carve(ALT, {i}, rowed=set(range(len(sp))), **kw)

    def test_each_directive_goes_with_the_side_that_uses_its_symbol(self):
        cv = self.carve()
        self.assertIsNone(cv.refused)
        self.assertIn("alternatename:?go@", cv.donor)
        self.assertNotIn("alternatename:?go@", cv.residual)
        self.assertIn("alternatename:?stop@", cv.residual)
        self.assertNotIn("alternatename:?stop@", cv.donor)
        self.assertIn("alternatename:??1Ring@", cv.residual)       # by its class: B::b() builds a Ring
        self.assertNotIn("alternatename:??1Ring@", cv.donor)
        for text in (cv.donor, cv.residual):                        # both use it: the duplication is real
            self.assertIn("alternatename:?both@", text)
        self.assertIn("alternatename:?none@", cv.residual)          # nobody's: it stays where it was
        self.assertNotIn("alternatename:?none@", cv.donor)
        kept = self.carve(altname_keep=True)
        self.assertIn("alternatename:?none@", kept.donor)
        self.assertNotIn("alternatename:?none@", kept.residual)

    def test_only_a_directive_both_sides_use_still_grows_the_hatch_total(self):
        cv = self.carve()
        self.assertIsNone(T.shatter_hatches("Code/M.cpp", ALT, {}, {"Code/A.cpp": cv.donor, "Code/B.cpp": cv.residual}))
        alone = ALT.replace('#pragma comment(linker, "/alternatename:?both@@YAXXZ=?run@Base@@QAEXXZ")\n', "")
        cv2 = T.carve(alone, {next(i for i, (_, _, c, _) in enumerate(T.def_spans(alone)) if "A::a" in c)},
                      rowed=set(range(len(T.def_spans(alone)))))
        self.assertTrue(T.shatter_hatches("Code/M.cpp", alone, {}, {"Code/A.cpp": cv2.donor, "Code/B.cpp": cv2.residual}))


class ShatterPlanTests(unittest.TestCase):
    """--shatter: every row and definition of a mixed file finds one unit; no residual."""

    def plan(self, text=SHATTER, groups=None, data_rowed=frozenset()):
        groups = groups or shatter_groups()
        rs = [r for v in groups.values() for r in v]
        return T.shatter_plan(text, rs, groups, data_rowed)

    def test_every_row_finds_a_unit_and_comdats_ride(self):
        p = self.plan()
        self.assertIsNone(p.refused)
        self.assertEqual({t: [r["target_rva"] for r in u] for t, u in p.units.items()},
                         {"Code/A.cpp": ["0x10", "0x20"], "Code/B.cpp": ["0x30"], "Code/C.cpp": ["0x40"]})
        self.assertEqual([r["target_rva"] for r in p.riders], ["0x50", "0x60"])   # no definition / a template's

    def test_each_unit_text_holds_its_bodies_and_what_they_need(self):
        p = self.plan()
        a, b, c = p.texts["Code/A.cpp"], p.texts["Code/B.cpp"], p.texts["Code/C.cpp"]
        self.assertIn("void A::a()", a)
        self.assertIn("void A::a2()", a)
        self.assertNotIn("void B::b()", a)
        self.assertIn("int unrowedHelper", a)            # its only caller's unit takes the external helper
        self.assertNotIn("int unrowedHelper", b)
        self.assertIn("int g_shared = 0;", a)            # the first user defines the shared object ...
        self.assertIn("extern int g_shared;", b)          # ... the others declare it
        self.assertNotIn("g_shared", c)
        self.assertIn("static int s_only;", a)
        self.assertNotIn("s_only", b)
        self.assertIn("static int deep", a)               # an internal helper is copied to each caller
        self.assertIn("static int deep", b)
        self.assertNotIn("static int deep", c)
        for text in (a, b, c):                             # a primary template is everyone's
            self.assertIn("template <class T> T twice", text)
        self.assertEqual(p.data_moves["Code/A.cpp"], ["g_shared", "s_only"])

    def test_a_row_without_a_unit_refuses(self):
        text = SHATTER + "void zzz() { }\n"
        p = self.plan(text, shatter_groups(rows(("?zzz@@YAXXZ", "0x70"))))
        self.assertIn("map must place it first", p.refused or "")

    def test_an_unplaced_definition_keeps_the_file_as_one_more_unit(self):
        text = SHATTER + "void zzz() { }\n"
        g = shatter_groups(rows(("?zzz@@YAXXZ", "0x70")))
        rs = [r for v in g.values() for r in v]
        p = T.shatter_plan(text, rs, g, here="Code/M.cpp")
        self.assertIsNone(p.refused)
        self.assertEqual(p.residual, "Code/M.cpp")
        self.assertEqual([r["target_rva"] for r in p.units["Code/M.cpp"]], ["0x70"])
        self.assertIn("void zzz()", p.texts["Code/M.cpp"])
        self.assertNotIn("void A::a()", p.texts["Code/M.cpp"])
        self.assertNotIn("void zzz()", p.texts["Code/A.cpp"])
        self.assertIsNone(self.plan().residual)                      # nothing unplaced with a body: no residual

    def test_a_placed_row_no_definition_spells_only_has_to_be_emitted(self):
        g = shatter_groups()
        g["Code/B.cpp"] = g["Code/B.cpp"] + rows(("?clear@?$vector@H@_STL@@QAEXXZ", "0x90"))
        p = self.plan(groups=g)
        self.assertIsNone(p.refused)
        self.assertIn("0x90", [r["target_rva"] for r in p.units["Code/B.cpp"]])

    def test_one_definition_in_two_units_refuses(self):
        g = shatter_groups()
        g["Code/B.cpp"] = g["Code/B.cpp"] + rows(("?a@A@@QAEXH@Z", "0x80"))   # an overload spelled by A::a's body
        self.assertIn("also produces rows of", self.plan(groups=g).refused or "")

    def test_an_external_helper_two_units_call_refuses(self):
        text = SHATTER.replace("void B::b() { g_shared--;", "void B::b() { unrowedHelper(2); g_shared--;")
        self.assertIn("unrowedHelper", self.plan(text).refused or "")

    def test_a_data_row_no_unit_uses_refuses(self):
        text = SHATTER.replace("static int s_only;", "static int s_only;\nint g_orphan = 1;")
        self.assertIn("g_orphan", self.plan(text, data_rowed={"g_orphan"}).refused or "")


class ShatterLedgerTests(unittest.TestCase):
    def test_rows_repoint_per_unit_and_leftovers_are_reported(self):
        raw = (HEADER + "?a@A@@QAEXXZ,,0x00000010,8,Code/M.cpp,matched,\n"
               "?b@B@@QAEXXZ,,0x00000030,8,Code/M.cpp,matched,\n"
               "?x@@YAXXZ,,0x00000090,8,Code/M.cpp,blocked,\n").encode()
        moves = {"Code/A.cpp": ["0x00000010"], "Code/B.cpp": ["0x00000030"]}
        out, left = T.shatter_repoint({"reverse/functions.csv": raw}, "Code/M.cpp", moves, {}, sorted(moves))
        text = out["reverse/functions.csv"].decode()
        self.assertIn("0x00000010,8,Code/A.cpp", text)
        self.assertIn("0x00000030,8,Code/B.cpp", text)
        self.assertEqual(left, [("reverse/functions.csv", 1)])     # the blocked row still names the file
        _, left = T.shatter_repoint({"reverse/functions.csv": raw}, "Code/M.cpp", moves, {}, sorted(moves),
                                    stays={"0x00000090"})
        self.assertEqual(left, [])                                 # unless the residual keeps it

    def test_hatch_totals_may_move_but_not_grow(self):
        before = "int g_Rva00DE2000Flag;\nvoid A::a() { g_Rva00DE2000Flag = 1; }\nvoid B::b() { }\n"
        moved = T.shatter_hatches("Code/M.cpp", before, {}, {
            "Code/A.cpp": "int g_Rva00DE2000Flag;\nvoid A::a() { g_Rva00DE2000Flag = 1; }\n",
            "Code/B.cpp": "void B::b() { }\n"})
        self.assertTrue(moved)
        grown = T.shatter_hatches("Code/M.cpp", before, {}, {
            "Code/A.cpp": "int g_Rva00DE2000Flag;\nvoid A::a() { g_Rva00DE2000Flag = 1; }\n",
            "Code/B.cpp": "extern int g_Rva00DE2000Flag;\nvoid B::b() { }\n"})
        self.assertIsNone(grown)


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


LEDGER_HEADER = "address,size,section,kind,name,source,status,names,defs,refs\n"
PINS_HEADER = "name,address,notes\n"


def unit_defs(code=(), data=(), static=()):
    return {"code": set(code), "data": set(data), "static": set(static)}


def coff(sections, symbols):
    """A minimal COFF object: sections [(name, characteristics)], symbols
    [(name, value, section number, storage class)], names in the string table."""
    import struct
    strings = b""
    symtab = b""
    for name, value, section, storage in symbols:
        offset = 4 + len(strings)
        strings += name.encode() + b"\0"
        symtab += struct.pack("<II I h H B B", 0, offset, value, section, 0, storage, 0)
    table = 20 + 40 * len(sections)
    head = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, table, len(symbols), 0, 0)
    secs = b"".join(struct.pack("<8sIIIIIIHHI", n.encode(), 0, 0, 0, 0, 0, 0, 0, 0, c) for n, c in sections)
    return head + secs + symtab + struct.pack("<I", 4 + len(strings)) + strings


class UnitKeyCarryTests(unittest.TestCase):
    """--shatter / --split carry data_ledger.csv and fold-proof keys to the unit
    whose compiled object defines each symbol, and refuse anything ambiguous."""

    M, A, B = "Code/M.cpp", "Code/A.cpp", "Code/B.cpp"

    def ledger(self, *lines):
        return (LEDGER_HEADER + "".join(l + "\n" for l in lines)).encode()

    def test_ledger_source_and_static_names_follow_the_defining_object(self):
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2",
                          "0x00A00010,4,.rdata,float,__real@3f800000,,literal,"
                          "__real@3f800000;_kOne@Code/M.cpp;_kOne@Code/Z.cpp,1,9",
                          "0x00A00020,4,.data,global,?h@@3HA,Code/Z.cpp,owned,,1,1")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(data=["?g@@3HA"]), self.B: unit_defs(static=["_kOne"])},
                               raw)
        self.assertEqual(out.problems, [])
        text = out.raws[T.DATA_LEDGER].decode()
        self.assertIn("0x00A00000,4,.data,global,?g@@3HA,Code/A.cpp,owned,,1,2\n", text)
        self.assertIn("__real@3f800000;_kOne@Code/B.cpp;_kOne@Code/Z.cpp,1,9\n", text)   # sorted, as generated
        self.assertIn("?h@@3HA,Code/Z.cpp,owned", text)                                 # another file's key: kept
        self.assertNotIn(self.M, text)
        self.assertEqual(out.moved, {T.DATA_LEDGER: 2})
        self.assertEqual(T.carry_trailer("--shatter", self.M, "its TUs", {}, out.moved)[:16], "Verifier-Change:")
        self.assertIsNone(T.carry_trailer("--shatter", self.M, "its TUs", {}, {}))

    def test_refuses_a_global_two_units_define(self):
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(data=["?g@@3HA"]), self.B: unit_defs(data=["?g@@3HA"])},
                               raw)
        self.assertTrue(any("defined by both Code/A.cpp and Code/B.cpp" in p for p in out.problems))

    def test_refuses_a_static_two_units_define(self):
        raw = self.ledger("0x00A00010,4,.rdata,float,__real@3f800000,,literal,__real@3f800000;_kOne@Code/M.cpp,1,9")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(static=["_kOne"]), self.B: unit_defs(static=["_kOne"])},
                               raw)
        self.assertTrue(any("_kOne is defined by both" in p for p in out.problems))

    def test_refuses_a_key_no_unit_defines(self):
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(), self.B: unit_defs()}, raw,
                               original=unit_defs(data=["?g@@3HA"]))
        self.assertTrue(any("no carved unit defines ?g@@3HA" in p for p in out.problems))
        # stale before the carve: still refused when the file is deleted (the key cannot vanish)
        out = T.unit_key_carry(self.M, {self.A: unit_defs(), self.B: unit_defs()}, raw, original=unit_defs())
        self.assertTrue(out.problems)

    def test_a_residual_keeps_what_it_still_defines(self):
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2",
                          "0x00A00010,4,.data,global,?s@@3HA,Code/M.cpp,owned,,1,2",
                          "0x00A00020,4,.data,global,?old@@3HA,Code/M.cpp,owned,,1,2")
        out = T.unit_key_carry(self.M, {self.M: unit_defs(data=["?g@@3HA"]), self.A: unit_defs(data=["?s@@3HA"])},
                               raw, original=unit_defs(data=["?g@@3HA", "?s@@3HA"]))
        self.assertEqual(out.problems, [])
        text = out.raws[T.DATA_LEDGER].decode()
        self.assertIn("?g@@3HA,Code/M.cpp,", text)        # the residual still defines it: no change
        self.assertIn("?s@@3HA,Code/A.cpp,", text)        # only the TU defines it now: carried
        self.assertIn("?old@@3HA,Code/M.cpp,", text)      # stale before the carve, file remains: left alone
        self.assertTrue(any("?old@@3HA" in n for n in out.notes))

    def test_refuses_a_key_the_residual_and_a_destination_both_define(self):
        # Sol R1 S1: the residual is one more definer, never a tie-breaker
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2",
                          "0x00A00010,4,.rdata,float,__real@3f800000,,literal,__real@3f800000;_k@Code/M.cpp,1,9")
        defs = {self.M: unit_defs(data=["?g@@3HA"], static=["_k"]), self.A: unit_defs(data=["?g@@3HA"], static=["_k"])}
        out = T.unit_key_carry(self.M, defs, raw, original=unit_defs(data=["?g@@3HA"], static=["_k"]))
        self.assertTrue(any("?g@@3HA is defined by both Code/A.cpp and Code/M.cpp" in p for p in out.problems))
        self.assertTrue(any("_k is defined by both Code/A.cpp and Code/M.cpp" in p for p in out.problems))

    def test_a_stale_key_stays_even_when_the_destination_defines_the_symbol(self):
        # Sol R1 S3: the stale-key exception comes before any destination is chosen
        raw = self.ledger("0x00A00000,4,.data,global,?old@@3HA,Code/M.cpp,owned,,1,2")
        out = T.unit_key_carry(self.M, {self.M: unit_defs(), self.A: unit_defs(data=["?old@@3HA"])}, raw,
                               original=unit_defs())
        self.assertEqual(out.problems, [])
        self.assertNotIn(T.DATA_LEDGER, out.raws)              # nothing moved to Code/A.cpp
        self.assertTrue(any("?old@@3HA" in n for n in out.notes))

    def test_a_fold_proof_the_residual_keeps_still_checks_its_callees(self):
        # Sol R1 S2: f stays in the residual, its unrowed callee g moves out
        raw = self.pins("??$f@H@@YAXXZ,0x00001000,fold-proof=Code/M.cpp")
        defs = {self.M: unit_defs(code=["??$f@H@@YAXXZ"]), self.A: unit_defs(code=["??$g@H@@YAXXZ"])}
        original = unit_defs(code=["??$f@H@@YAXXZ", "??$g@H@@YAXXZ"])
        calls = lambda unit, name: {"??$g@H@@YAXXZ"} if name == "??$f@H@@YAXXZ" else set()   # noqa: E731
        out = T.unit_key_carry(self.M, defs, pins_raw=raw, original=original, calls=calls)
        self.assertTrue(any("callee ??$g@H@@YAXXZ would leave Code/M.cpp" in p for p in out.problems))
        defs[self.M]["code"].add("??$g@H@@YAXXZ")
        defs[self.A]["code"].clear()
        out = T.unit_key_carry(self.M, defs, pins_raw=raw, original=original, calls=calls)
        self.assertEqual((out.problems, out.raws), ([], {}))  # kept, and the proof is not rewritten

    def test_refuses_disagreeing_with_a_verified_data_owner(self):
        raw = self.ledger("0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(data=["?g@@3HA"]), self.B: unit_defs()}, raw,
                               owners={"?g@@3HA": self.B})
        self.assertTrue(any("data_rows.csv puts it in Code/B.cpp" in p for p in out.problems))
        out = T.unit_key_carry(self.M, {self.A: unit_defs(data=["?g@@3HA"]), self.B: unit_defs()}, raw,
                               owners={"?g@@3HA": self.A})
        self.assertEqual(out.problems, [])

    def test_refuses_collapsing_two_keys(self):
        raw = self.ledger("0x00A00010,4,.rdata,float,__real@3f800000,,literal,_kOne@Code/A.cpp;_kOne@Code/M.cpp,1,9")
        out = T.unit_key_carry(self.M, {self.A: unit_defs(static=["_kOne"]), self.B: unit_defs()}, raw)
        self.assertTrue(any("collapses two keys" in p for p in out.problems))

    def pins(self, *lines):
        return (PINS_HEADER + "".join(l + "\n" for l in lines)).encode()

    def test_fold_proof_follows_the_object_defining_the_pinned_body(self):
        raw = self.pins("??$f@H@@YAXXZ,0x00001000,ICF twin; fold-proof=Code/M.cpp",
                        "??$f@D@@YAXXZ,0x00001010,\"twin, see fold-proof=Code/M.cpp\"",
                        "??$f@F@@YAXXZ,0x00001020,fold-proof=Code/Z.cpp")
        defs = {self.A: unit_defs(code=["??$f@H@@YAXXZ"]), self.B: unit_defs(code=["??$f@D@@YAXXZ"])}
        out = T.unit_key_carry(self.M, defs, pins_raw=raw)
        self.assertEqual(out.problems, [])
        text = out.raws[T.PINS].decode()
        self.assertIn("??$f@H@@YAXXZ,0x00001000,ICF twin; fold-proof=Code/A.cpp\n", text)
        self.assertIn("\"twin, see fold-proof=Code/B.cpp\"", text)
        self.assertIn("fold-proof=Code/Z.cpp", text)
        self.assertEqual(out.moved, {T.PINS: 2})
        self.assertIsNone(T.carry_trailer("--shatter", self.M, "its TUs", {}, out.moved))   # symbols.csv: pin admission

    def test_fold_proof_refusals(self):
        raw = self.pins("??$f@H@@YAXXZ,0x00001000,fold-proof=Code/M.cpp")
        both = {self.A: unit_defs(code=["??$f@H@@YAXXZ"]), self.B: unit_defs(code=["??$f@H@@YAXXZ"])}
        self.assertTrue(T.unit_key_carry(self.M, both, pins_raw=raw).problems)
        none = {self.A: unit_defs(), self.B: unit_defs()}
        self.assertTrue(any("no carved unit defines" in p for p in T.unit_key_carry(self.M, none, pins_raw=raw).problems))

    def test_fold_proof_callees_must_stay_beside_the_pinned_body(self):
        raw = self.pins("??$f@H@@YAXXZ,0x00001000,fold-proof=Code/M.cpp")
        defs = {self.A: unit_defs(code=["??$f@H@@YAXXZ"]), self.B: unit_defs(code=["??$g@H@@YAXXZ"])}
        original = unit_defs(code=["??$f@H@@YAXXZ", "??$g@H@@YAXXZ"])
        calls = lambda unit, name: {"??$g@H@@YAXXZ"} if name == "??$f@H@@YAXXZ" else set()   # noqa: E731
        out = T.unit_key_carry(self.M, defs, pins_raw=raw, original=original, calls=calls)
        self.assertTrue(any("callee ??$g@H@@YAXXZ would leave Code/A.cpp" in p for p in out.problems))
        out = T.unit_key_carry(self.M, defs, pins_raw=raw, original=original, calls=calls,
                               addressed=frozenset({"??$g@H@@YAXXZ"}))     # a rowed callee resolves by address
        self.assertEqual(out.problems, [])
        defs[self.A]["code"].add("??$g@H@@YAXXZ")
        defs[self.B]["code"].clear()
        self.assertEqual(T.unit_key_carry(self.M, defs, pins_raw=raw, original=original, calls=calls).problems, [])

    def test_repoint_fold_proofs_by_pin_name(self):
        raw = self.pins("a,0x1,fold-proof=Code/M.cpp", "b,0x2,fold-proof=Code/M.cpp")
        out, n = T.repoint_fold_proofs(raw, {self.M}, {"a": self.A})
        self.assertEqual(n, 1)
        self.assertEqual(out.decode(), PINS_HEADER + "a,0x1,fold-proof=Code/A.cpp\nb,0x2,fold-proof=Code/M.cpp\n")

    def test_shatter_keyed_leaves_ledger_and_fold_keys_to_the_carry(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "reverse/data_ledger.csv").write_text(
                LEDGER_HEADER + "0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2\n")
            (root / "reverse/symbols.csv").write_text(PINS_HEADER + "a,0x1,fold-proof=Code/M.cpp\n")
            self.assertEqual(T.shatter_keyed(self.M, root=root), [])
            (root / "reverse/code_identity_baseline.tsv").write_text("Code/M.cpp\trow\tsym\ttarget\tclass\n")
            self.assertTrue(T.shatter_keyed(self.M, root=root))

    def test_object_definitions_reads_the_symbol_table(self):
        sections = [(".text", 0x60000020), (".data", 0xC0000040), (".rdata", 0x40000040)]
        symbols = [(".text", 0, 1, 3), (".data", 0, 2, 3),
                   ("?f@@YAXXZ", 0, 1, 2), ("_static_fn", 4, 1, 3),
                   ("?g@@3HA", 0, 2, 2), ("_kOne", 0, 3, 3), ("$SG123", 4, 3, 3),
                   ("?ext@@3HA", 0, 0, 2)]              # referenced, not defined
        with tempfile.TemporaryDirectory() as tmp:
            obj = Path(tmp) / "u.obj"
            obj.write_bytes(coff(sections, symbols))
            got = T.object_definitions(obj)
        self.assertEqual(got, unit_defs(code=["?f@@YAXXZ"], data=["?g@@3HA"], static=["_kOne"]))

    def test_carry_unit_keys_refuses_without_objects(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "reverse/data_ledger.csv").write_text(
                LEDGER_HEADER + "0x00A00000,4,.data,global,?g@@3HA,Code/M.cpp,owned,,1,2\n")
            out = T.carry_unit_keys(self.M, {self.A: None}, None, root=root)
            self.assertTrue(out.problems)
            self.assertEqual(T.carry_unit_keys("Code/Q.cpp", {self.A: None}, None, root=root).problems, [])


if __name__ == "__main__":
    unittest.main()
