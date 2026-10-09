"""TU map, skeleton composition and the ownership invariants, on throwaway trees.

Positive controls are commits the old hooks let through and these rules must
refuse (a second row for an owned address, a row moved into the wrong file, a
second body of an owned function, a private copy of a registered class).
Negative controls are the edits the fleet makes every hour and that must keep
passing (an edit in place, a move into the approved TU, an inline helper, a
copy the author allowed explicitly).
"""
import importlib.util
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


tu_map = _load("tu_map")
tu_skeleton = _load("tu_skeleton")
tu_ownership = _load("tu_ownership")


def row(name, rva, size, source, status="matched", notes=""):
    return f"{name},,0x{rva:08X},{size},{source},{status},{notes}\n"


# ---------------------------------------------------------------- tu_map
@pytest.fixture
def mapped(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    (zh / "GameEngine/Source/Die").mkdir(parents=True)
    (zh / "GameEngine/Source/Die/FooDie.cpp").write_text(
        "void FooDie::onDie(int)\n{\n}\nFooDie::FooDie(Thing *t)\n{\n}\n")
    (zh / "GameEngine/Source/Die/BarDie.cpp").write_text("void BarDie::onDie(int)\n{\n}\n")
    rev = tmp_path / "reverse"
    rev.mkdir()
    d = "Code/GameEngine/Source/Die"
    (rev / "functions.csv").write_text(HEADER + "".join([
        row("??0FooDie@@QAE@PAVThing@@@Z", 0x1000, 16, f"{d}/FooDieCtor.cpp"),        # S/Z anchor
        row("?rva00001010@Rva00001010@@QAEXXZ", 0x1010, 16, f"{d}/Rva1010.cpp"),     # bracketed (C)
        row("?onDie@FooDie@@UAEXH@Z", 0x1020, 16, f"{d}/FooDieOnDie.cpp"),           # Z anchor
        row("??_GFooDie@@UAEPAXI@Z", 0x9000, 16, f"{d}/FooDieDel.cpp"),             # COMDAT far away
        row("?onDie@BarDie@@UAEXH@Z", 0x20000, 16, f"{d}/BarDieOnDie.cpp"),
        row("?helper@Lone@@QAEXXZ", 0x40000, 16, f"{d}/Lone.cpp"),                  # N only
        row("?other@Lone@@QAEXXZ", 0x40010, 16, f"{d}/LoneOther.cpp"),
    ]))
    (rev / "ghidra_functions.csv").write_text("rva,size,name\n0x1030,8,FUN_1030\n0x1040,8,FUN_1040\n")
    (rev / "string_xrefs.tsv").write_text("C:\\bfme2\\Code\\GameEngine\\Source\\Die\\BarDie.cpp\t0x20004\n")
    out = tu_map.build(tu_map.Layout(tmp_path))
    return {int(r["rva"], 16): r for r in out}


def test_anchored_and_contiguous_rows_are_approved(mapped):
    foo = "Code/GameEngine/Source/Die/FooDie.cpp"
    assert mapped[0x1000]["tu"] == foo and mapped[0x1000]["confidence"] == "approved"
    assert mapped[0x1020]["by"] == "Z" and mapped[0x1020]["confidence"] == "approved"
    assert mapped[0x1010]["by"] == "C" and mapped[0x1010]["confidence"] == "approved"
    assert mapped[0x20000]["by"] == "F" and mapped[0x20000]["tu"].endswith("Die/BarDie.cpp")


def test_header_inline_comdat_far_from_its_class_is_displaced(mapped):
    assert mapped[0x9000]["confidence"] == "displaced" and mapped[0x9000]["tu"] == ""


def test_naming_convention_alone_is_only_proposed(mapped):
    assert mapped[0x40000]["confidence"] == "proposed"
    assert mapped[0x40000]["tu"] == "Code/GameEngine/Source/Die/Lone.cpp"


def test_unledgered_retail_function_between_anchors_gets_no_ledger_source(mapped):
    assert 0x1030 not in mapped or mapped[0x1030]["kind"] == "code-unledgered"


def test_map_is_deterministic(tmp_path, mapped):
    layout = tu_map.Layout(tmp_path)
    assert tu_map.render(tu_map.build(layout)) == tu_map.render(tu_map.build(layout))


def test_noncontiguous_tu_is_not_approved(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("void A::f()\n{\n}\nvoid A::g()\n{\n}\n")
    (zh / "B.cpp").write_text("void B::f()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/Af.cpp"),
        row("?f@B@@QAEXXZ", 0x2000, 16, "Code/X/Bf.cpp"),     # B's anchor inside A's span
        row("?g@A@@QAEXXZ", 0x3800, 16, "Code/X/Ag.cpp"),
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert out[0x1000]["confidence"] == "proposed" and "noncontiguous" in out[0x1000]["evidence"]


# ---------------------------------------------------------------- unconverted functions
@pytest.fixture
def unconverted(tmp_path):
    """Retail functions with no ledger row, between and beside named anchors."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Foo.cpp").write_text("void Foo::a()\n{\n}\nvoid Foo::b()\n{\n}\n")
    (zh / "Host.cpp").write_text("void Host::f()\n{\n}\nvoid Host::g()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?a@Foo@@QAEXXZ", 0x1000, 16, "Code/X/FooA.cpp"),
        row("?b@Foo@@QAEXXZ", 0x1100, 16, "Code/X/FooB.cpp"),
        row("?f@Host@@QAEXXZ", 0x8000, 16, "Code/X/HostF.cpp"),
        row("?bfmeGo@BfmeThingQQ@@QAEXXZ", 0x9000, 16, "Code/X/BfmeThingQQ.cpp"),  # N only, no anchor
        row("?g@Host@@QAEXXZ", 0xA800, 16, "Code/X/HostG.cpp"),        # host span > UNION_SPAN
    ]))
    ghidra = [0x1020, 0x1040, 0x1060, 0x1080, 0x10A0, 0x5000, 0x8040, 0x9800]
    (tmp_path / "reverse/ghidra_functions.csv").write_text(
        "rva,size,name\n" + "".join(f"0x{g:X},16,FUN_{g:X}\n" for g in ghidra))
    (tmp_path / "reverse/string_xrefs.tsv").write_text("C:\\bfme2\\Code\\X\\Bar.cpp\t0x5004\n")
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_unledgered_run_between_approved_anchors_is_approved_whole(unconverted):
    for rva in (0x1020, 0x1040, 0x1060, 0x1080, 0x10A0):   # five, more than the old three passes reached
        r = unconverted[rva]
        assert (r["kind"], r["source"], r["by"], r["tu"], r["confidence"]) == \
            ("code-unledgered", "", "C", "Code/X/Foo.cpp", "approved"), hex(rva)
        assert r["evidence"].startswith("C=0x00001000..")


def test_unledgered_function_with_a_file_string_is_its_tu(unconverted):
    r = unconverted[0x5000]
    assert (r["kind"], r["source"], r["by"], r["tu"]) == ("code-unledgered", "", "F", "Code/X/Bar.cpp")
    assert r["confidence"] == "approved"


def test_unanchored_naming_hint_does_not_break_its_host_span(unconverted):
    assert unconverted[0x8000]["confidence"] == "approved"
    assert "noncontiguous" not in unconverted[0x8000]["evidence"]
    hint = unconverted[0x9000]
    assert hint["tu"] == "Code/X/BfmeThingQQ.cpp" and hint["confidence"] == "proposed"
    # the unledgered functions either side of it are bracketed by different TUs: no TU,
    # but their extents are written (tu_at needs every known body)
    for rva in (0x8040, 0x9800):
        assert (unconverted[rva]["tu"], unconverted[rva]["confidence"], unconverted[rva]["size"]) == ("", "", 16)


def test_map_with_unconverted_rows_is_deterministic(tmp_path, unconverted):
    layout = tu_map.Layout(tmp_path)
    assert tu_map.render(tu_map.build(layout)) == tu_map.render(tu_map.build(layout))


def _code(tu, conf, size=16, by="Z", evidence=""):
    return {"kind": "code", "size": str(size), "tu": tu, "confidence": conf, "by": by, "evidence": evidence,
            "source": ""}


class FakeImage:
    """Retail bytes: 0x90 (code) everywhere except the padding runs given."""

    def __init__(self, *pads):
        self.pads = pads

    def read(self, rva, n):
        return bytes(tu_map.PAD if any(lo <= a < hi for lo, hi in self.pads) else 0x90 for a in range(rva, rva + n))


def test_tu_at_infers_c_only_between_one_tus_brackets():
    m = {0x1000: [_code("Code/A.cpp", "approved")], 0x2000: [_code("Code/A.cpp", "approved")],
         0x2100: [_code("Code/B.cpp", "approved")], 0x9000: [_code("Code/B.cpp", "approved")],
         0xA000: [_code("Code/C.cpp", "approved")], 0xA100: [_code("Code/C.cpp", "proposed")]}
    # 0x1010..0x1800 is padding; 0x1800 is where an unsplit body starts
    index = tu_map.code_index(m, FakeImage((0x1010, 0x1800)))
    got = tu_map.tu_at(m, 0x1800, index)
    assert (got["tu"], got["confidence"], got["by"], got["kind"], got["source"]) == \
        ("Code/A.cpp", "approved", "C", "code-inferred", "")
    assert tu_map.tu_at(m, 0x1000, index) is m[0x1000][0]     # a row wins as it stands
    assert tu_map.tu_at(m, 0x2050, index) is None             # A below, B above
    assert tu_map.tu_at(m, 0x5000, index) is None             # B..B but further apart than GAP
    assert tu_map.tu_at(m, 0x0800, index) is None             # nothing below
    assert tu_map.tu_at(m, 0xA080, index)["confidence"] == "proposed"
    assert tu_map.tu_at({}, 0x1800) is None
    # without the image nothing shows a boundary: bracketed, but only proposed
    assert tu_map.tu_at(m, 0x1800)["confidence"] == "proposed"


# ---------------------------------------------------------------- review regressions (2026-10-09)
def test_tu_at_inside_a_displaced_body_inherits_displaced():
    # 0x00040780 (a displaced 33-byte DebugIOFlat deleting-dtor thunk) between approved rows
    m = {0x40720: [_code("Code/D/ods.cpp", "approved", 92)],
         0x40780: [_code("", "displaced", 33, by="-", evidence="N=Code/D/DebugIOFlat.cpp")],
         0x407B0: [_code("Code/D/ods.cpp", "approved", 126)]}
    index = tu_map.code_index(m, FakeImage((0x4077C, 0x40780), (0x407A1, 0x407B0)))
    got = tu_map.tu_at(m, 0x40781, index)
    assert (got["kind"], got["tu"], got["confidence"]) == ("code-interior", "", "displaced")
    assert got["evidence"].startswith("inside 0x00040780")
    got = tu_map.tu_at(m, 0x40730, index)                     # inside an approved body: its answer
    assert (got["kind"], got["tu"], got["confidence"]) == ("code-interior", "Code/D/ods.cpp", "approved")
    # a body with no TU stays without one
    m[0x40780] = [_code("", "", 33, by="-")]
    assert tu_map.tu_at(m, 0x40790, tu_map.code_index(m))["confidence"] == ""


def test_tu_at_gives_padding_no_answer_and_needs_boundary_evidence():
    m = {0x40720: [_code("Code/D/ods.cpp", "approved", 92)],       # ends 0x4077C
         0x40800: [_code("Code/D/ods.cpp", "approved", 16)]}
    index = tu_map.code_index(m, FakeImage((0x4077C, 0x40780), (0x407C0, 0x40800)))
    assert tu_map.tu_at(m, 0x4077C, index) is None                 # retail CC padding
    assert tu_map.tu_at(m, 0x407C4, index) is None
    got = tu_map.tu_at(m, 0x40780, index)                          # first byte after the padding
    assert (got["confidence"], got["evidence"]) == ("approved", "C=0x00040720..0x00040800 gap=start")
    got = tu_map.tu_at(m, 0x40790, index)                          # inside undiscovered bytes
    assert (got["confidence"], got["evidence"]) == ("proposed", "C=0x00040720..0x00040800 gap=inside")


@pytest.fixture
def turret(tmp_path):
    """StateMachine.cpp and TurretAI.cpp interleave in retail; one TurretAI body pushes its __FILE__."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source"
    (zh / "Common").mkdir(parents=True)
    (zh / "GameLogic/AI").mkdir(parents=True)
    (zh / "Common/StateMachine.cpp").write_text("void StateMachine::a()\n{\n}\nvoid StateMachine::b()\n{\n}\n")
    (zh / "GameLogic/AI/TurretAI.cpp").write_text("void TurretAI::x()\n{\n}\nvoid TurretAI::y()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    ai = "Code/GameEngine/Source/GameLogic/AI"
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?a@StateMachine@@QAEXXZ", 0x1000, 16, "Code/GameEngine/Source/Common/StateMachineA.cpp"),
        row("?x@TurretAI@@QAEXXZ", 0x1040, 16, f"{ai}/TurretAI.cpp"),
        row("?b@StateMachine@@QAEXXZ", 0x1080, 16, "Code/GameEngine/Source/Common/StateMachineB.cpp"),
        row("?rva000010C0@Rva000010C0@@QAEXXZ", 0x10C0, 16, "Code/GameEngine/Source/Common/Rva000010C0.cpp"),
        row("?y@TurretAI@@QAEXXZ", 0x1100, 16, f"{ai}/TurretAIY.cpp"),
    ]))
    (tmp_path / "reverse/string_xrefs.tsv").write_text(
        "C:\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\TurretAI.cpp\t0x10C4\n")
    return tmp_path


def test_interleaved_anchored_tus_are_not_merged_and_contradicted_approval_is_demoted(turret):
    out = tu_map.build(tu_map.Layout(turret))
    got = {int(r["rva"], 16): r for r in out}
    ai = "Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp"
    # retail's own __FILE__ string says TurretAI.cpp; a merge into StateMachine.cpp is refused
    assert (got[0x10C0]["tu"], got[0x10C0]["by"]) == (ai, "F")
    assert got[0x1040]["tu"] == got[0x1100]["tu"] == ai
    assert got[0x1000]["tu"].endswith("Common/StateMachine.cpp")
    # the two TUs interleave: neither is contiguous, nothing in them is approved
    assert {r["confidence"] for r in out if r["tu"]} == {"proposed"}
    assert all("noncontiguous" in r["evidence"] for r in out if r["tu"])
    assert tu_map.self_check(out) == (0, 0)
    # the safety net itself: a row whose TU contradicts its own evidence
    assert tu_map.contradicts("Code/S.cpp", f="Code/T.cpp", z="Code/S.cpp")
    assert tu_map.contradicts("Code/S.cpp", z="Code/T.cpp", s="Code/U.cpp")
    assert not tu_map.contradicts("Code/S.cpp", z="Code/T.cpp", s="Code/s.cpp")
    assert not tu_map.contradicts("Code/S.cpp")


def test_naming_hints_still_merge_into_one_anchored_tu(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Host.cpp").write_text("void Host::f()\n{\n}\nvoid Host::g()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?f@Host@@QAEXXZ", 0x1000, 16, "Code/X/HostF.cpp"),
        row("?go@HostHelper@@QAEXXZ", 0x1040, 16, "Code/X/HostHelper.cpp"),    # N only: one file, two classes
        row("?g@Host@@QAEXXZ", 0x1080, 16, "Code/X/HostG.cpp"),
    ]))
    got = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert (got[0x1040]["tu"], got[0x1040]["by"], got[0x1040]["confidence"]) == ("Code/X/Host.cpp", "U", "approved")
    assert "N=Code/X/HostHelper.cpp" in got[0x1040]["evidence"]       # its own hint is kept


def test_zh_call_expressions_and_comments_are_not_definitions():
    text = ("void CaveContain::onRemoving( Object *obj ) \n{\n\tOpenContain::onRemoving(obj);\n}\n"
            "void INI::parseWeaponTemplateDefinition( INI* ini )\n{\n"
            "\tWeaponStore::parseWeaponTemplateDefinition(ini);\n}\n"
            "OpenContain::onRemoving(obj);\n"                              # a call at column 0
            "/*static*/ void WeaponStore::parseWeaponTemplateDefinition(INI* ini)\n{\n}\n"
            "/*\nvoid Gone::commentedOut( void )\n{\n}\n*/\n"
            "// void Gone::lineComment()\n"
            "const char *s = \"Gone::inString(\";\n"
            "Foo::Foo( Thing *t ) : Base( t )\n{\n}\n"
            "Foo::~Foo()\n{\n}\n"
            "void Matrix3D::Transform_Min_Max_AABox\n(\n\tint a\n)\n{\n}\n"
            "return Gone::kw(1);\n")
    assert list(tu_map.zh_definitions(text)) == [
        ("CaveContain", "onRemoving"), ("INI", "parseWeaponTemplateDefinition"),
        ("WeaponStore", "parseWeaponTemplateDefinition"), ("Foo", "Foo"), ("Foo", "~Foo"),
        ("Matrix3D", "Transform_Min_Max_AABox")]


def test_validate_scores_rows_landed_since_a_revision(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Foo.cpp").write_text("void Foo::a()\n{\n}\nvoid Foo::b()\n{\n}\nvoid Foo::c()\n{\n}\n")
    (zh / "Bar.cpp").write_text("void Bar::z()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    led = tmp_path / "reverse/functions.csv"
    led.write_text(HEADER + row("?a@Foo@@QAEXXZ", 0x1000, 16, "Code/X/FooA.cpp")
                   + row("?b@Foo@@QAEXXZ", 0x1100, 16, "Code/X/FooB.cpp"))
    (tmp_path / "reverse/ghidra_functions.csv").write_text("rva,size,name\n0x1040,16,FUN_1040\n0x1080,16,FUN_1080\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "t")
    git(tmp_path, "config", "user.email", "t@t")
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "cutoff")
    # since the cutoff: one landed body agrees with the approved C prediction, one does not
    led.write_text(led.read_text() + row("?c@Foo@@QAEXXZ", 0x1040, 16, "Code/X/FooC.cpp")
                   + row("?z@Bar@@QAEXXZ", 0x1080, 16, "Code/X/BarZ.cpp"))
    landed, tally, misses = tu_map.validate(tu_map.Layout(tmp_path), "HEAD")
    assert landed == 2
    assert tally == {("approved", "C", "row"): [2, 1]}
    assert [(m[0], m[2], m[3]) for m in misses] == [(0x1080, "Code/X/Foo.cpp", "Code/X/Bar.cpp")]


def test_fingerprint_detects_a_changed_input(tmp_path):
    (tmp_path / "reverse").mkdir()
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    zh.mkdir(parents=True)
    (tmp_path / "reverse/functions.csv").write_text(HEADER + row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/A.cpp"),
                                                    newline="\n")
    assert tu_map.main(["--root", str(tmp_path), "--check-fresh"]) == 1      # never written
    assert tu_map.main(["--root", str(tmp_path)]) == 0
    assert tu_map.main(["--root", str(tmp_path), "--check-fresh"]) == 0
    p = tmp_path / "reverse/functions.csv"
    p.write_bytes(p.read_bytes().replace(b"\n", b"\r\n"))                    # line endings only: still fresh
    assert tu_map.main(["--root", str(tmp_path), "--check-fresh"]) == 0
    p.write_text(p.read_text() + row("?g@A@@QAEXXZ", 0x1010, 16, "Code/X/A.cpp"))
    assert tu_map.main(["--root", str(tmp_path), "--check-fresh"]) == 1
    assert tu_map.check_fresh(tu_map.Layout(tmp_path)) == ["reverse/functions.csv"]


# ---------------------------------------------------------------- skeleton
def test_chunks_keep_comments_and_ignore_braces_in_literals():
    text = ('#include "a.h"\n// lead comment\nstruct S { int a; };\n'
            'const char *s = "}{";\nint f()\n{\n    return \'}\';  // }\n}\n')
    got = tu_skeleton.chunks(text)
    kinds = [k for k, _ in got]
    assert kinds == ["pp", "decl", "decl", "def"]
    assert "// lead comment" in got[1][1]
    assert got[3][1].strip().endswith("}") and "return '}'" in got[3][1]


def test_compose_dedupes_declarations_and_marks_placeholders():
    sk = [({"rva": "0x00001000", "size": "16", "by": "Z"},
           {"name": "?f@A@@", "source": "a.cpp", "status": "matched"}),
          ({"rva": "0x00001010", "size": "8", "by": "C"}, None),
          ({"rva": "0x00001020", "size": "16", "by": "Z"},
           {"name": "?g@A@@", "source": "b.cpp", "status": "matched"})]
    texts = {"a.cpp": "// cl: /O1\n#include \"x.h\"\nclass A { public: void f(); void g(); };\nvoid A::f() {}\n",
             "b.cpp": "// cl: /O1\n#include \"x.h\"\nclass A { public: void f(); void g(); };\nvoid A::g() {}\n"}
    out = tu_skeleton.compose("T.cpp", sk, ["a.cpp", "b.cpp"], texts, ["/O1"], "first")
    assert out.startswith("// cl: /O1\n")
    assert out.count('#include "x.h"') == 1 and out.count("class A") == 1
    assert out.index("void A::f()") < out.index("0x00001010") < out.index("void A::g()")
    assert "tu-skeleton: 0x00001010 8B (unledgered) -- unmatched, no code, never credited" in out


def test_generated_placeholder_file_is_never_a_donor(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/Af.cpp")
                                                    + row("uw_00001010", 0x1010, 11, "Code/gen_small/uw_gen_001.cpp"))
    (tmp_path / "reverse/tu_map.csv").write_text(
        "rva,size,kind,tu,confidence,by,evidence,source\n"
        "0x00001000,16,code,Code/X/A.cpp,approved,Z,,Code/X/Af.cpp\n"
        "0x00001010,11,code,Code/X/A.cpp,approved,C,,Code/gen_small/uw_gen_001.cpp\n")
    monkeypatch.setattr(tu_skeleton, "LAYOUT", tu_map.Layout(tmp_path))
    monkeypatch.setattr(tu_skeleton, "LEDGER", tmp_path / "reverse/functions.csv")
    sk = tu_skeleton.skeleton("Code/X/A.cpp")
    assert len(sk) == 2
    don, mixed = tu_skeleton.donors("Code/X/A.cpp", sk)
    assert set(don) == {"Code/X/Af.cpp"} and not mixed


def test_repoint_moves_only_absorbed_donor_rows_and_keeps_terminators():
    raw = HEADER + row("a", 0x10, 4, "Code/x/A.cpp").replace("\n", "\r\n") + row("b", 0x20, 4, "Code/x/B.cpp")
    new, moved = tu_skeleton.repoint(raw, {"Code/x/A.cpp"}, "Code/x/T.cpp")
    assert moved == 1 and ",Code/x/T.cpp," in new and ",Code/x/B.cpp," in new
    assert new.count("\r\n") == 1 and len(new) == len(raw)


# ---------------------------------------------------------------- ownership
def git(repo, *args):
    subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "t")
    git(tmp_path, "config", "user.email", "t@t")
    rev = tmp_path / "reverse"
    rev.mkdir()
    d = tmp_path / "Code/X"
    d.mkdir(parents=True)
    (d / "Foo.cpp").write_text("void Foo::f()\n{\n}\n")
    (d / "Shared.h").write_text("class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    (rev / "functions.csv").write_text(HEADER + row("?f@Foo@@QAEXXZ", 0x1000, 16, "Code/X/Foo.cpp")
                                       + row("?g@Foo@@QAEXXZ", 0x1010, 16, "Code/X/FooG.cpp"))
    (rev / "tu_map.csv").write_text(
        "rva,size,kind,tu,confidence,by,evidence,source\n"
        "0x00001000,16,code,Code/X/Foo.cpp,approved,Z,,Code/X/Foo.cpp\n"
        "0x00001010,16,code,Code/X/Foo.cpp,approved,C,,Code/X/FooG.cpp\n"
        "0x00001020,16,code-unledgered,Code/X/Foo.cpp,approved,C,,\n")
    (rev / "canonical_classes.csv").write_text("class,header,notes\nReg,Code/X/Shared.h,test\n")
    (d / "FooG.cpp").write_text("void Foo::g()\n{\n}\n")
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "base")
    monkeypatch.setattr(tu_ownership, "ROOT", tmp_path)
    monkeypatch.setattr(tu_ownership, "LAYOUT", tu_map.Layout(tmp_path))
    monkeypatch.setattr(tu_ownership, "_FP", None)
    return tmp_path


def staged(repo):
    git(repo, "add", "-A")
    return {rule for rule, _ in tu_ownership.check("HEAD", None)}


def ledger_add(repo, text):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text() + text)


def test_a1_second_row_for_owned_address_is_refused(repo):
    ledger_add(repo, row("?f2@Foo@@QAEXXZ", 0x1000, 16, "Code/X/Other.cpp"))
    assert "A1" in staged(repo)


def test_a2_move_to_wrong_file_is_refused_and_move_into_tu_passes(repo):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text().replace(",Code/X/FooG.cpp,", ",Code/X/Elsewhere.cpp,"))
    assert staged(repo) == {"A2"}
    p.write_text(p.read_text().replace(",Code/X/Elsewhere.cpp,", ",Code/X/Foo.cpp,"))
    assert staged(repo) == set()


def test_a3_new_row_outside_approved_tu(repo):
    ledger_add(repo, row("?h@Foo@@QAEXXZ", 0x1020, 16, "Code/X/FooH.cpp"))
    assert staged(repo) == {"A3"}


def test_a3_new_row_in_its_tu_passes(repo):
    ledger_add(repo, row("?h@Foo@@QAEXXZ", 0x1020, 16, "Code/X/Foo.cpp"))
    assert staged(repo) == set()


def test_a3_covers_an_address_with_no_map_row_by_its_brackets(repo):
    # 0x1008 has no tu_map row; 0x1000 and 0x1010 are both approved for Foo.cpp
    ledger_add(repo, row("?k@Foo@@QAEXXZ", 0x1008, 8, "Code/X/FooK.cpp"))
    assert staged(repo) == {"A3"}
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text().replace(",Code/X/FooK.cpp,", ",Code/X/Foo.cpp,"))
    assert staged(repo) == set()


def test_edit_in_place_passes(repo):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text().replace("FooG.cpp,matched,", "FooG.cpp,matched,note"))
    assert staged(repo) == set()


def test_a4_second_body_is_refused_but_inline_helper_passes(repo):
    (repo / "Code/X/Bar.cpp").write_text("inline void Foo::f()\n{\n}\n")
    assert staged(repo) == set()
    (repo / "Code/X/Bar.cpp").write_text("void Foo::f()\n{\n}\n")
    assert staged(repo) == {"A4"}


def test_b1_private_copy_of_registered_class(repo):
    (repo / "Code/X/Baz.cpp").write_text("class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    assert staged(repo) == {"B1"}
    (repo / "Code/X/Baz.cpp").write_text("// class-gate: allow Reg byte-proved view\n"
                                         "class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    assert staged(repo) == set()


def test_b2_fingerprint_is_diagnostic_only(repo):
    (repo / "Code/X/Qux.cpp").write_text("class Rva00001234\n{\npublic:\n    int x;\n    float y;\n};\n")
    git(repo, "add", "-A")
    found = tu_ownership.check("HEAD", None)
    assert [r for r, _ in found] == ["B2"]
    assert tu_ownership.report(found, shadow=False) == 0
