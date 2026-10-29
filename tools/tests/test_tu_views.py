"""tu_views: one shared spelling of each private class view across a TU's sources.

The compiler is replaced by a small sequential layout of the source (int/float/
pointers 4 bytes, char arrays by length, a vfptr for the first virtual), the
build by a callable, so every rule is checked without MSVC.
"""
import re
import sys
import tempfile
import unittest
import unittest.mock
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_layouts  # noqa: E402
import tu_views as V  # noqa: E402

SIZES = {"int": 4, "float": 4, "unsigned int": 4, "short": 2, "char": 1, "bool": 1, "unsigned char": 1}


def fake_layouts(root):
    """{class: layout} the way class_layouts reports it, computed from the source."""
    def read(path):
        text = (Path(root) / path).read_text(encoding="latin-1")
        out = {}
        for cls in class_layouts.class_bodies(text):
            span = V.class_span(text, cls)
            if not span:
                continue
            src = V.no_comments(text)[span[0]:span[1]]
            body = src[src.index("{") + 1:src.rindex("}")]
            try:
                ms = V.members(body, cls, V.file_typedefs(text))
            except V.Refused:        # CodeView still lays it out; the reader is what refuses
                out[cls] = {"fwd": False, "key": "class", "size": 8, "bases": [], "statics": [], "methods": [],
                            "fields": [[0, "m_x", "bitfield", 0]], "virtual": [], "vslots": {}, "vfptr": False}
                continue
            virt = [m for m in ms if m.kind == "fn" and m.virtual]
            based = re.search(r":\s*public\s+(\w+)\s*\{", src)
            parent = out.get(based.group(1)) if based else None
            at = parent["size"] if parent and parent["fields"] else 4 if virt else 0
            fields = []
            for m in ms:
                if m.kind != "data":
                    continue
                arr = re.search(r"\[(0x[0-9A-Fa-f]+|\d+)\]", m.decl)
                size = 4 if "*" in m.decl else SIZES.get(m.base, 4)
                count = int(arr.group(1), 0) if arr else 1
                align = 4 if "*" in m.decl else min(size, 4)
                at = (at + align - 1) // align * align
                base = "enum" if re.search(r"\benum\s+" + re.escape(m.base) + r"\b", text) else m.base
                cv = base.replace("unsigned ", "u") + (f"[{count}]" if arr else "") + ("*" if "*" in m.decl else "")
                fields.append([at, m.name, cv, size * count])
                at += size * count
            size = (at + 3) // 4 * 4 if fields and any(f[3] >= 4 for f in fields) else max(at, 1)
            out[cls] = {"fwd": False, "key": "class", "size": size, "fields": fields, "statics": [],
                        "bases": [[based.group(1), 0]] if parent else [],
                        "methods": sorted({m.name for m in ms if m.kind == "fn"}),
                        "virtual": sorted({m.name for m in virt}),
                        "vslots": {str(i): m.name + "()" for i, m in enumerate(virt)}, "vfptr": bool(virt)}
        return out
    return read


class Fixture:
    def __init__(self, files, build_ok=True, ledger=(), canon=None):
        self.dir = tempfile.TemporaryDirectory()
        self.root = Path(self.dir.name)
        for name, text in files.items():
            (self.root / name).write_text(text, encoding="latin-1", newline="")
        self.builds = []

        def build(changed):
            self.builds.append(list(changed))
            return build_ok, "Functions: OK" if build_ok else "Functions: FAIL 1/2"

        self.tool = V.Tool("Seed.cpp", root=self.root, layouts=fake_layouts(self.root), build=build,
                           unmatched=lambda files: [], ledger=list(ledger), held=lambda files: [],
                           canon=canon or {})
        self.files = list(files)

    def run(self, dry_run=False):
        return self.tool.run(dry_run=dry_run, files=self.files, seed=self.files[0])

    def text(self, name):
        return (self.root / name).read_text(encoding="latin-1")

    def close(self):
        self.dir.cleanup()


SEED = """// cl: /DNDEBUG /MD
class Foo
{
public:
	void a();
	int m_x;
	float m_y;
};

void Foo::a() { m_x = 1; m_y = 2.0f; }
"""

DONOR = """// cl: /DNDEBUG /MD
class Foo
{
public:
	int b(); // the donor's own method
	int m_first;
	char m_pad04[4];
};

int Foo::b() { return m_first + 1; /* m_first stays in comments */ }
const char *s = "m_first";
"""


class Superset(unittest.TestCase):
    def setUp(self):
        self.fx = Fixture({"Seed.cpp": SEED, "Donor.cpp": DONOR})

    def tearDown(self):
        self.fx.close()

    def test_one_block_with_the_seeds_names_and_every_method(self):
        rep = self.fx.run()
        self.assertEqual(rep["applied"], ["Foo"])
        blocks = []
        for f in ("Seed.cpp", "Donor.cpp"):
            text = self.fx.text(f)
            span = V.class_span(text, "Foo")
            blocks.append(text[span[0]:span[1]])
        self.assertEqual(blocks[0], blocks[1])
        self.assertIn("void a();", blocks[0])
        self.assertIn("int b();", blocks[0])
        self.assertIn("int m_x; // +0x00", blocks[0])
        self.assertIn("float m_y; // +0x04", blocks[0])
        self.assertNotIn("m_first", blocks[0])

    def test_the_donor_body_is_renamed_token_by_token(self):
        self.fx.run()
        donor = self.fx.text("Donor.cpp")
        self.assertIn("return m_x + 1;", donor)
        self.assertIn("/* m_first stays in comments */", donor)
        self.assertIn('"m_first"', donor)
        self.assertEqual(self.fx.builds, [["Donor.cpp", "Seed.cpp"]])

    def test_dry_run_writes_nothing(self):
        rep = self.fx.run(dry_run=True)
        self.assertEqual(rep["classes"]["Foo"]["status"], "plan")
        self.assertEqual(rep["classes"]["Foo"]["renames"], {"Donor.cpp": {"m_first": "m_x"}})
        self.assertEqual(self.fx.text("Donor.cpp"), DONOR)
        self.assertEqual(self.fx.text("Seed.cpp"), SEED)
        self.assertEqual(self.fx.builds, [])


class Rollback(unittest.TestCase):
    def test_a_build_that_is_not_exact_restores_every_file(self):
        fx = Fixture({"Seed.cpp": SEED, "Donor.cpp": DONOR}, build_ok=False)
        try:
            rep = fx.run()
            self.assertEqual(rep["applied"], [])
            self.assertEqual(rep["classes"]["Foo"]["status"], "reverted")
            self.assertIn("not exact", rep["failed"]["Foo"])
            self.assertEqual(fx.text("Seed.cpp"), SEED)
            self.assertEqual(fx.text("Donor.cpp"), DONOR)
        finally:
            fx.close()


class LineEndings(unittest.TestCase):
    def test_crlf_files_keep_their_bytes_on_revert_and_their_endings_on_apply(self):
        seed, donor = SEED.replace("\n", "\r\n"), DONOR.replace("\n", "\r\n")
        for ok in (False, True):
            fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor}, build_ok=ok)
            try:
                fx.run()
                raw = (fx.root / "Donor.cpp").read_bytes()
                if not ok:
                    self.assertEqual(raw, donor.encode("latin-1"))
                else:
                    self.assertNotIn(b"\n", raw.replace(b"\r\n", b""))
                    self.assertIn(b"return m_x + 1;", raw)
            finally:
                fx.close()


class Spelling(unittest.TestCase):
    def test_comments_ride_with_their_member_and_donor_bodies_use_superset_names(self):
        seed = ("class Foo\n{\npublic:\n\t// why a() stays out of line\n\tvoid a();\n"
                "\tint m_x; // retail +0x00\n\tfloat m_y;\n};\n")
        donor = ("class Foo\n{\npublic:\n\tint get()\n\t{\n\t\treturn m_first; // the count\n\t}\n"
                 "\tint m_first;\n\tchar m_pad04[4];\n};\nint g(Foo *f) { return f->get(); }\n")
        fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor})
        try:
            rep = fx.run(dry_run=True)
            block = rep["classes"]["Foo"]["block"]
            self.assertIn("\t// why a() stays out of line\n\tvoid a();", block)
            self.assertIn("int m_x; // +0x00 retail +0x00", block)
            self.assertIn("return m_x; // the count", block)
            self.assertNotIn("m_first", block)
        finally:
            fx.close()


class Dependencies(unittest.TestCase):
    def test_the_block_carries_an_enum_and_forward_declares_a_class_the_donor_lacks(self):
        seed = ("class Label\n{\npublic:\n\tint m_p;\n};\n"
                "enum Kind\n{\n\tKIND_A,\n\tKIND_B\n};\n"
                "typedef unsigned char UnsignedByte;\n"
                "class Foo\n{\npublic:\n\tLabel name();\n\tKind m_kind;\n\tUnsignedByte m_flag;\n};\n"
                "Label Foo::name() { Label l; l.m_p = m_kind; return l; }\n").replace("\n", "\r\n")
        donor = "class Foo\n{\npublic:\n\tvoid set();\n\tint m_k;\n};\nvoid Foo::set() { m_k = 0; }\n" \
            .replace("\n", "\r\n")
        fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor})
        try:
            rep = fx.run()
            self.assertEqual(rep["applied"], ["Foo"])
            raw = (fx.root / "Donor.cpp").read_bytes().decode("latin-1")
            self.assertNotIn("\r\r", raw)
            self.assertIn("enum Kind\r\n{\r\n\tKIND_A,", raw)
            self.assertIn("class Label;\r\nclass Foo\r\n", raw)
            self.assertIn("unsigned char m_flag;", raw)          # the donor has no UnsignedByte
            self.assertIn("void Foo::set() { m_kind = 0; }", raw)
        finally:
            fx.close()


class Conflicts(unittest.TestCase):
    def plan(self, seed, donor, **kw):
        fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor}, **kw)
        try:
            rep = fx.run(dry_run=True)
            return rep, fx.text("Donor.cpp") == donor
        finally:
            fx.close()

    def test_fields_partitioning_bytes_differently(self):
        donor = "class Foo\n{\npublic:\n\tshort m_lo;\n\tshort m_hi;\n\tfloat m_y;\n};\nvoid g(Foo *f) { f->m_lo = f->m_hi; }\n"
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "conflict")
        self.assertIn("fields overlap", rep["classes"]["Foo"]["evidence"])

    def test_padding_named_like_another_classes_padding_is_still_a_gap(self):
        donor = ("class Bar\n{\npublic:\n\tunsigned char m_pad[8];\n\tint m_z;\n};\n"
                 "class Foo\n{\npublic:\n\tunsigned char m_pad[4];\n\tfloat m_y;\n};\n"
                 "float g(Foo *f, Bar *b) { return f->m_y + b->m_z; }\n")
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "plan")
        used = "class Foo\n{\npublic:\n\tunsigned char m_pad[4];\n\tfloat m_y;\n};\n" \
               "unsigned char *g(Foo *f) { return f->m_pad; }\n"
        rep, _ = self.plan(SEED, used)
        self.assertEqual(rep["classes"]["Foo"]["status"], "conflict")

    def test_a_before_field_block_is_padding(self):
        donor = ("class Foo\n{\npublic:\n\tunsigned char m_beforeY[4];\n\tfloat m_y;\n};\n"
                 "float g(Foo *f) { return f->m_y; }\n")
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "plan")

    def test_one_offset_typed_as_different_things(self):
        donor = "class Foo\n{\npublic:\n\tint m_x;\n\tint m_count;\n};\nvoid g(Foo *f) { f->m_count = 0; }\n"
        rep, _ = self.plan(SEED, donor)
        self.assertIn("disagree on what the field is (float vs int", rep["classes"]["Foo"]["evidence"])
        self.assertTrue(V.cv_compatible("Thing*", "int") and V.cv_compatible("enum", "int"))
        self.assertFalse(V.cv_compatible("EAStringC", "int") or V.cv_compatible("uchar[4]", "int"))

    def test_two_views_spelling_out_different_sizes(self):
        seed = "class Foo\n{\npublic:\n\tint m_x;\n\tchar m_pad04[0xC];\n};\n"
        donor = "class Foo\n{\npublic:\n\tint m_x;\n\tchar m_pad04[0x8];\n};\n"
        rep, _ = self.plan(seed, donor)
        self.assertIn("sizeof differs", rep["classes"]["Foo"]["evidence"])

    def test_a_view_stopping_at_its_last_field_takes_the_larger_size(self):
        donor = "class Foo\n{\npublic:\n\tint m_x;\n\tfloat m_y;\n\tint m_z;\n};\nvoid g(Foo *f) { f->m_z = 0; }\n"
        rep, _ = self.plan(SEED, donor)
        entry = rep["classes"]["Foo"]
        self.assertEqual(entry["status"], "plan")
        self.assertIn("int m_z; // +0x08", entry["block"])
        self.assertTrue(any("stop at their last field" in n for n in entry["notes"]))

    def test_an_empty_view_claims_no_size(self):
        donor = "class Foo\n{\npublic:\n\tint b();\n};\nint Foo::b() { return 1; }\n"
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "plan")

    def test_a_view_declaring_no_base_or_virtual_takes_the_agreed_base(self):
        base = "class Base\n{\npublic:\n\tint m_b;\n};\n"
        seed = base + "class Foo : public Base\n{\npublic:\n\tvoid a();\n\tint m_x;\n};\n"
        donor = base + "class Foo\n{\npublic:\n\tint b();\n};\nint Foo::b() { return 1; }\n"
        rep, _ = self.plan(seed, donor)
        entry = rep["classes"]["Foo"]
        self.assertEqual(entry["status"], "plan")
        self.assertTrue(entry["block"].startswith("class Foo : public Base\n"))
        self.assertIn("int b();", entry["block"])
        donor_fields = base + "class Foo\n{\npublic:\n\tint m_early;\n};\nvoid g(Foo *f) { f->m_early = 0; }\n"
        rep, _ = self.plan(seed, donor_fields)
        self.assertIn("lies under the bases", rep["classes"]["Foo"]["evidence"])

    def test_a_view_nothing_uses_takes_the_block_without_voting(self):
        unused = "class Foo\n{\npublic:\n\tshort m_lo, m_hi;\n};\n"
        fx = Fixture({"Seed.cpp": SEED, "Donor.cpp": DONOR, "Unused.cpp": unused})
        real = fx.tool._layouts
        fx.tool._layouts = lambda f: {} if f == "Unused.cpp" else real(f)
        try:
            rep = fx.run()
            self.assertEqual(rep["applied"], ["Foo"])
            text = fx.text("Unused.cpp")
            span = V.class_span(text, "Foo")
            self.assertIn("int m_x; // +0x00", text[span[0]:span[1]])
        finally:
            fx.close()

    def test_a_rename_onto_a_name_the_donor_already_uses(self):
        donor = DONOR + "int m_x;\n"
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "conflict")
        self.assertIn("collides", rep["classes"]["Foo"]["evidence"])

    def test_method_access_disagreement_needs_the_ledger(self):
        seed = "class Foo\n{\npublic:\n\tvoid f();\n\tint m_x;\n};\n"
        donor = "class Foo\n{\nprotected:\n\tvoid f();\npublic:\n\tint m_x;\n};\nvoid Foo::f() { m_x = 0; }\n"
        rep, _ = self.plan(seed, donor)
        self.assertIn("access differs", rep["classes"]["Foo"]["evidence"])
        rep, _ = self.plan(seed, donor, ledger=[{"name": "?f@Foo@@IAEXXZ"}])
        self.assertEqual(rep["classes"]["Foo"]["status"], "plan")
        self.assertIn("protected:\n\tvoid f();", rep["classes"]["Foo"]["block"])

    def test_virtual_slots_filled_differently(self):
        seed = "class Foo\n{\npublic:\n\tvirtual void f();\n\tint m_x;\n};\n"
        donor = "class Foo\n{\npublic:\n\tvirtual void g();\n\tint m_x;\n};\n"
        rep, _ = self.plan(seed, donor)
        self.assertIn("virtual slot 0 differs", rep["classes"]["Foo"]["evidence"])

    def test_two_inline_bodies_of_one_method(self):
        seed = "class Foo\n{\npublic:\n\tint get() { return m_x; }\n\tint m_x;\n};\n"
        donor = "class Foo\n{\npublic:\n\tint get() { return m_x + 1; }\n\tint m_x;\n};\n"
        rep, _ = self.plan(seed, donor)
        self.assertIn("two different inline bodies", rep["classes"]["Foo"]["evidence"])

    def test_a_bitfield_is_not_modelled(self):
        donor = "class Foo\n{\npublic:\n\tint m_x : 3;\n\tfloat m_y;\n};\n"
        rep, _ = self.plan(SEED, donor)
        self.assertEqual(rep["classes"]["Foo"]["status"], "conflict")


class Canonical(unittest.TestCase):
    def test_a_registered_class_is_header_lane_work_and_never_written(self):
        seed = SEED + "struct Coord3D { float x, y, z; };\n"
        donor = DONOR + "struct Coord3D { float x, y; float z; };\n"
        fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor}, canon={"Coord3D": "Code/Coord3D.h"})
        try:
            rep = fx.run()
            self.assertIn("Coord3D", rep["canonical"])
            self.assertNotIn("Coord3D", rep["classes"])
            self.assertIn("header_adopt_lane.py", rep["canonical"]["Coord3D"]["action"])
            self.assertIn("struct Coord3D { float x, y; float z; };", fx.text("Donor.cpp"))
        finally:
            fx.close()


class Reader(unittest.TestCase):
    def test_members_split_access_methods_and_declarators(self):
        body = ("public:\n\tFoo();\n\tvirtual ~Foo();\n\tbool operator==(const Foo &o) const;\n"
                "private:\n\tfloat a, *b;\n\tstruct Thing *m_thing;\n\tenum Kind { K0, K1 };\n")
        ms = V.members(body, "Foo", {})
        kinds = [(m.kind, m.access, m.name) for m in ms]
        self.assertEqual(kinds, [("fn", "public", "Foo"), ("fn", "public", "~Foo"),
                                 ("fn", "public", "operator=="), ("data", "private", "a"),
                                 ("data", "private", "b"), ("data", "private", "m_thing"),
                                 ("nested", "private", "Kind")])
        self.assertEqual(ms[2].params, ("const Foo&",))
        self.assertTrue(ms[2].const)

    def test_parameter_types_resolve_typedefs_and_drop_names(self):
        self.assertEqual(V.param_types("Real r, const Coord3D &pos, unsigned idx", {"Real": "float"}),
                         ("float", "const Coord3D&", "unsigned int"))
        self.assertEqual(V.param_types("void", {}), ())

    def test_rename_skips_comments_strings_and_the_kept_span(self):
        text = 'int f() { return m_a; } // m_a\nconst char *s = "m_a";\nint g() { return m_a; }\n'
        keep = (text.index("int g"), len(text))
        out = V.rename(text, {"m_a": "m_b"}, keep)
        self.assertEqual(out, 'int f() { return m_b; } // m_a\nconst char *s = "m_a";\nint g() { return m_a; }\n')

    def test_ledger_settles_member_attributes(self):
        rows = [{"name": "?f@Foo@@IBEXXZ"}, {"name": "??0Foo@@QAE@XZ"}, {"name": "?h@Foo@@SGXXZ"}]
        self.assertEqual(V.ledger_member_attrs("Foo", "f", rows), {("protected", "plain", True, False, "__thiscall")})
        self.assertEqual(V.ledger_member_attrs("Foo", "Foo", rows), {("public", "plain", False, False, "__thiscall")})
        self.assertEqual(V.ledger_member_attrs("Foo", "h", rows), {("public", "static", False, False, "__stdcall")})
        self.assertEqual(V.ledger_member_attrs("Foo", "v", [{"name": "?v@Foo@@QCEXXZ"}]),
                         {("public", "plain", False, True, "__thiscall")})
        self.assertEqual(V.ledger_class_key("Foo", [{"name": "?x@@YAXPAVFoo@@@Z"}]), "class")
        self.assertEqual(V.ledger_class_key("Foo", [{"name": "?x@@YAXPAUFoo@@@Z"}]), "struct")


class Wiring(unittest.TestCase):
    """tu_skeleton's dry run and the consolidate queue send view rejections here."""

    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.root = Path(self.dir.name)
        (self.root / "Code").mkdir()
        (self.root / "reverse").mkdir()
        (self.root / "Code/T.cpp").write_text(SEED)
        (self.root / "Code/D.cpp").write_text(DONOR)
        self.don = {"Code/T.cpp": [], "Code/D.cpp": []}

    def tearDown(self):
        self.dir.cleanup()

    def test_shared_private_names_classes_two_files_declare(self):
        self.assertEqual(V.shared_private(["Code/T.cpp", "Code/D.cpp", "Code/Missing.cpp"], self.root), ["Foo"])
        self.assertEqual(V.shared_private(["Code/T.cpp", "Code/D.cpp"], self.root, canon={"Foo": "h"}), [])

    def test_a_compile_rejection_points_at_tu_views(self):
        import tu_skeleton as T
        with unittest.mock.patch.object(T, "ROOT", self.root):
            out = T.view_hint({"rejected": {"Code/D.cpp": "compile: error C2039: 'b' : is not a member of 'Foo'"}},
                              "Code/T.cpp", self.don)
            self.assertIn("python3 tools/tu_views.py Code/T.cpp", out["reconcile"])
            self.assertIn("Foo", out["reconcile"])
            self.assertNotIn("reconcile", T.view_hint({"rejected": {"Code/D.cpp": "bytes"}}, "Code/T.cpp", self.don))
            unrelated = {"rejected": {"Code/D.cpp": "compile: error C3861: 'ResumeThread': identifier not found"}}
            self.assertNotIn("reconcile", T.view_hint(unrelated, "Code/T.cpp", self.don))

    def test_the_consolidate_queue_serves_tu_views_first(self):
        import repair_queue as rq
        import tu_skeleton as T
        (self.root / rq.TU_MAP).write_text("")
        with unittest.mock.patch.object(rq, "ROOT", self.root), \
                unittest.mock.patch.object(T, "queue_entries", lambda under="", root=None: [
                    {"tu": "Code/T.cpp", "removes": 1, "rows": 2, "mixed": 0, "refused": 0, "keys": []}]), \
                unittest.mock.patch.object(T.claims, "_blocking_records", lambda root=None: iter(())), \
                unittest.mock.patch.object(T, "skeleton", lambda tu: []), \
                unittest.mock.patch.object(T, "donors", lambda tu, sk: (self.don, {}, {})):
            (item,), _ = rq.consolidation_items()
        self.assertIn("then python3 tools/tu_views.py Code/T.cpp (its donors declare their own views of Foo)",
                      item["start"])
        self.assertTrue(item["start"].endswith("python3 tools/tu_skeleton.py --merge Code/T.cpp --dry-run"))


class ReviewDefects(unittest.TestCase):
    """The 2026-10-28 review's cases: each would otherwise apply."""

    def run_fx(self, seed, donor, ledger=(), dry_run=False, build=None, symbols=None):
        fx = Fixture({"Seed.cpp": seed, "Donor.cpp": donor}, ledger=ledger)
        if build is not None:
            fx.tool.build = build
        if symbols is not None:
            fx.tool.symbols = symbols
        try:
            rep = fx.run(dry_run=dry_run)
            return rep, fx.text("Seed.cpp"), fx.text("Donor.cpp")
        finally:
            fx.close()

    def test_an_interrupt_during_verification_restores_every_file(self):
        def interrupted(changed):
            raise KeyboardInterrupt
        fx = Fixture({"Seed.cpp": SEED, "Donor.cpp": DONOR})
        fx.tool.build = interrupted
        try:
            with self.assertRaises(KeyboardInterrupt):
                fx.run()
            self.assertEqual((fx.text("Seed.cpp"), fx.text("Donor.cpp")), (SEED, DONOR))
        finally:
            fx.close()

    def test_a_changed_external_symbol_reverts_the_class(self):
        calls = []

        def symbols(f):            # before: one name; after the rewrite: another
            calls.append(f)
            return frozenset({("?m_first@@3HA", False)}) if len(calls) <= 2 else frozenset({("?m_x@@3HA", False)})
        rep, seed, donor = self.run_fx(SEED, DONOR, symbols=symbols)
        self.assertEqual(rep["applied"], [])
        self.assertIn("external symbols", rep["failed"]["Foo"])
        self.assertEqual((seed, donor), (SEED, DONOR))

    def test_a_plain_global_with_the_fields_name_refuses_the_rename(self):
        donor = DONOR + "int m_first;\nint get() { return m_first; }\n"
        rep, _, text = self.run_fx(SEED, donor)
        self.assertEqual(rep["applied"], [])
        self.assertEqual(text, donor)

    def test_a_volatile_difference_without_ledger_evidence_is_refused(self):
        seed = SEED.replace("void a();", "void a() volatile;")
        rep, _, text = self.run_fx(seed, DONOR.replace("int b();", "int b();\n\tvoid a();"), dry_run=True)
        self.assertNotEqual(rep["classes"]["Foo"]["status"], "plan")
        self.assertIn("volatile", str(rep["classes"]["Foo"]))

    def test_inline_bodies_differing_only_in_literals_are_refused(self):
        seed = SEED.replace("void a();", "char c() { return 'A'; }\n\tvoid a();")
        donor = DONOR.replace("int b();", "int b();\n\tchar c() { return 'B'; }")
        rep, _, _ = self.run_fx(seed, donor, dry_run=True)
        self.assertNotEqual(rep["classes"]["Foo"]["status"], "plan")
        self.assertIn("two different inline bodies", str(rep["classes"]["Foo"]))

    def test_another_overloads_ledger_name_settles_nothing(self):
        seed = SEED.replace("void a();", "void a();\n\tstatic void f(int);\n\tstatic void f(float);")
        donor = DONOR.replace("int b();", "int b();\nprivate:\n\tstatic void f(float);\npublic:")
        rep, _, _ = self.run_fx(seed, donor, ledger=[{"name": "?f@Foo@@SAXH@Z", "source": "Seed.cpp"}],
                                dry_run=True)
        self.assertNotEqual(rep["classes"]["Foo"]["status"], "plan")
        self.assertIn("overloaded", str(rep["classes"]["Foo"]))


if __name__ == "__main__":
    unittest.main()
