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


def test_naming_convention_alone_is_approved_only_under_a_provisional_name(mapped):
    for rva in (0x40000, 0x40010):    # two rows, one naming hint, nothing else in their span
        assert mapped[rva]["tu"] == "Code/GameEngine/Source/Die/Lone.cpp"
        assert tu_map.provisional_name(mapped[rva]) and not tu_map.canonical_tu(mapped[rva])
    assert tu_map.canonical_tu(mapped[0x1000])


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


def _islands(tmp_path, ledger, strings="", zh_b="fg"):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("".join(f"void A::{m}()\n{{\n}}\n" for m in "fghi"))
    (zh / "B.cpp").write_text("".join(f"void B::{m}()\n{{\n}}\n" for m in zh_b))
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(
        row(f"?{m}@{c}@@QAEXXZ", rva, 16, f"Code/X/{c}{m}.cpp") for c, m, rva in ledger))
    (tmp_path / "reverse/string_xrefs.tsv").write_text(strings)
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_short_run_of_another_tu_inside_a_span_is_an_island(tmp_path):
    # B::f has no ZH definition of its own: only its class site (S) places it in B.cpp
    out = _islands(tmp_path, [("A", "f", 0x1000), ("A", "g", 0x1100), ("B", "f", 0x1200),
                              ("A", "h", 0x1300), ("A", "i", 0x1400)], zh_b="g")
    assert out[0x1200]["by"] == "S"
    for rva in (0x1000, 0x1100, 0x1300, 0x1400):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/X/A.cpp", "approved"), hex(rva)
    island = out[0x1200]
    assert (island["tu"], island["confidence"]) == ("Code/X/B.cpp", "proposed")
    assert "island" in island["evidence"] and "noncontiguous" not in island["evidence"]


def test_island_needs_longer_runs_of_one_tu_on_both_sides(tmp_path):
    # alternating single rows: neither TU is an island in the other, both are noncontiguous
    out = _islands(tmp_path, [("A", "f", 0x1000), ("B", "f", 0x1100), ("A", "g", 0x1200),
                              ("B", "g", 0x1300), ("A", "h", 0x1400)])
    assert all(r["confidence"] == "proposed" and "island" not in r["evidence"]
               for r in out.values() if r["tu"])


def test_an_out_of_line_definition_is_never_an_island(tmp_path):
    """A(F) A(Z) B(Z) A A: B::f is defined out of line in B.cpp, so B's run is no header
    COMDAT and the A rows after it must not be approved for A on naming around it."""
    out = _islands(tmp_path, [("A", "f", 0x1000), ("A", "g", 0x1100), ("B", "f", 0x1200),
                              ("A", "h", 0x1300), ("A", "i", 0x1400)],
                   strings="C:\\bfme2\\Code\\X\\A.cpp\t0x1004\n")
    assert (out[0x1000]["by"], out[0x1200]["by"]) == ("F", "Z")
    assert "island" not in out[0x1200]["evidence"]
    for rva in (0x1300, 0x1400):
        assert out[rva]["confidence"] == "proposed" and "noncontiguous" in out[rva]["evidence"], hex(rva)


def test_a_file_string_row_is_never_an_island(tmp_path):
    out = _islands(tmp_path, [("A", "f", 0x1000), ("A", "g", 0x1100), ("B", "f", 0x1200),
                              ("A", "h", 0x1300), ("A", "i", 0x1400)],
                   strings="C:\\bfme2\\Code\\X\\B.cpp\t0x1204\n")
    assert out[0x1200]["by"] == "F" and "island" not in out[0x1200]["evidence"]
    assert out[0x1000]["confidence"] == "proposed" and "noncontiguous" in out[0x1000]["evidence"]


def _helper_tu(tmp_path, ledger):
    """A and B anchored (ZH defines their methods); M only hinted (no ZH, N=Code/X/M.cpp)."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("".join(f"void A::{m}()\n{{\n}}\n" for m in "fgh"))
    (zh / "B.cpp").write_text("".join(f"void B::{m}()\n{{\n}}\n" for m in "fghi"))
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(
        row(f"?{m}@{c}@@QAEXXZ", rva, 16, f"Code/X/{c}{m}.cpp") for c, m, rva in ledger))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_hinted_tu_reaching_past_two_anchored_tus_merges_with_neither(tmp_path):
    """Retail 0x004A0E47..0x004A17C1: one MonsterDockUpdate row inside SupplyCenterDockUpdate's
    run, its own run after RepairDockUpdate's. Merged into the first anchored TU it starts in,
    that TU's span covered the second and neither was approved."""
    out = _helper_tu(tmp_path, [("A", "f", 0x1000), ("A", "g", 0x1100), ("M", "s", 0x1180),
                                ("A", "h", 0x1200), ("B", "f", 0x1400), ("B", "g", 0x1500),
                                ("M", "a", 0x1700), ("M", "b", 0x1800), ("M", "c", 0x1900)])
    for rva in (0x1000, 0x1100, 0x1200):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/X/A.cpp", "approved"), hex(rva)
    for rva in (0x1400, 0x1500):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/X/B.cpp", "approved"), hex(rva)
    for rva in (0x1180, 0x1700, 0x1800, 0x1900):
        assert out[rva]["tu"] == "Code/X/M.cpp" and out[rva]["by"] == "N", hex(rva)


def test_hinted_tu_within_its_anchored_neighbours_still_merges(tmp_path):
    """Negative control (header-inline LZBuffer rows between Lz.cpp's and Huff.cpp's): every M
    row lies inside the anchored TUs' extent, so M merges into A (U) and its row inside B's
    run is an island, as before."""
    out = _helper_tu(tmp_path, [("A", "f", 0x1000), ("A", "g", 0x1100), ("M", "s", 0x1180),
                                ("A", "h", 0x1200), ("B", "f", 0x1300), ("B", "g", 0x1400),
                                ("M", "a", 0x1450), ("B", "h", 0x1500), ("B", "i", 0x1600)])
    assert (out[0x1180]["tu"], out[0x1180]["by"], out[0x1180]["confidence"]) == ("Code/X/A.cpp", "U", "approved")
    assert out[0x1450]["tu"] == "Code/X/A.cpp" and "island" in out[0x1450]["evidence"]
    for rva in (0x1300, 0x1400, 0x1500, 0x1600):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/X/B.cpp", "approved"), hex(rva)


@pytest.mark.parametrize("zh_dir, approved", [("Tools/WW3D/pluglib", False), ("Libraries/WWMath", True)])
def test_a_zh_tools_file_anchors_no_game_tu(tmp_path, zh_dir, approved):
    """Retail 0x00715550..0x00715EB0: Matrix4 rows took Z/S from ZH's 3ds Max exporter
    (Tools/WW3D/pluglib/matrix4.cpp) and were approved into that tool path. A Tools/
    program is never linked into the game, so its file anchors nothing; the same file
    under the game's own tree (negative control) still does."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code" / zh_dir
    zh.mkdir(parents=True)
    (zh / "matrix4.cpp").write_text("".join(f"void Matrix4::{m}()\n{{\n}}\n" for m in "fgh"))
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(
        row(f"?{m}@Matrix4@@QAEXXZ", rva, 16, f"Code/W/Matrix4{m}.cpp")
        for m, rva in (("f", 0x1000), ("g", 0x1010), ("h", 0x1020))))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    for rva in (0x1000, 0x1010, 0x1020):
        r = out[rva]
        assert (r["by"], r["tu"]) == ("Z", f"Code/{zh_dir}/matrix4.cpp"), hex(rva)
        assert (r["confidence"] == "approved") is approved, hex(rva)
        assert "provisional" not in r["evidence"]


def _local_class(tmp_path, other_cpp=""):
    """ObjectCreationList.cpp's shape: nugget classes written whole inside the .cpp."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Ocl.cpp").write_text(
        "class Nugget : public Base\n{\npublic:\n\tNugget() : m_a(0) { }\n"
        "\tvirtual void create(int x) const\n\t{\n\t\tdoIt(x);\n\t}\nprivate:\n\tint m_a;\n};\n"
        "void ObjectCreationList::clear()\n{\n}\nvoid ObjectCreationList::addNugget()\n{\n}\n")
    if other_cpp:
        (zh / "Other.cpp").write_text(other_cpp)
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?clear@ObjectCreationList@@QAEXXZ", 0x1000, 16, "Code/X/OclClear.cpp"),
        row("??0Nugget@@QAE@XZ", 0x1010, 16, "Code/W/NuggetCtor.cpp"),
        row("?create@Nugget@@UBEXH@Z", 0x1020, 16, "Code/W/NuggetCreate.cpp"),
        row("?addNugget@ObjectCreationList@@QAEXXZ", 0x1030, 16, "Code/X/OclAdd.cpp"),
    ]))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_member_of_a_class_written_inside_a_zh_cpp_is_defined_there(tmp_path):
    out = _local_class(tmp_path)
    for rva in (0x1010, 0x1020):
        r = out[rva]
        assert (r["by"], r["tu"], r["confidence"]) == ("Z", "Code/X/Ocl.cpp", "approved"), hex(rva)
        assert "S=Code/X/Ocl.cpp" in r["evidence"], hex(rva)


def test_a_local_class_two_zh_cpps_write_anchors_neither(tmp_path):
    # negative control (colmathaabtri.cpp and colmathobbtri.cpp each write a BTCollisionStruct):
    # a member both write names no file, and the class has no single site
    out = _local_class(tmp_path, "class Nugget\n{\npublic:\n\tNugget() { }\n};\n")
    ctor = out[0x1010]
    assert "Z=" not in ctor["evidence"] and "S=" not in ctor["evidence"]
    assert (out[0x1020]["by"], out[0x1020]["tu"]) == ("Z", "Code/X/Ocl.cpp")


def test_a_local_class_sharing_a_header_class_name_anchors_nothing(tmp_path):
    """Retail 0x00615890 ??0Pipe@@QAE@XZ is WWLib's Pipe (pipe.h); netserv.cpp writes an
    unrelated local `class Pipe`. A header class of the same name vetoes the local one."""
    out = _local_class(tmp_path, "")
    assert out[0x1010]["by"] == "Z"                    # control: no header defines Nugget
    hdr = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X/Nugget.h"
    hdr.write_text("class Nugget\n{\npublic:\n\tNugget(void);\n};\n")
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    for rva in (0x1010, 0x1020):
        assert "Z=Code/X/Ocl.cpp" not in out[rva]["evidence"], hex(rva)


def test_a_member_two_zh_game_files_define_names_neither(tmp_path):
    """CollisionMath::Collide has one overload per colmath*.cpp, and BW_Render::Buffer::
    Buffer reads as Buffer::Buffer beside WWLib's buff.cpp: a (class, member) that two
    game .cpp files define names no file, where the first in walk order used to win. One
    game definition beside a Tools/ copy still anchors the game file."""
    root = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    for d, text in (("Libraries/Math/colmathaabox.cpp", "bool CollisionMath::Collide(int a)\n{\n}\n"),
                    ("Libraries/Math/colmathline.cpp", "bool CollisionMath::Collide(float b)\n{\n}\n"),
                    ("Libraries/Math/widget.cpp", "void Widget::draw()\n{\n}\n"),
                    ("Tools/Editor/widget.cpp", "void Widget::draw()\n{\n}\n")):
        (root / d).parent.mkdir(parents=True, exist_ok=True)
        (root / d).write_text(text)
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?Collide@CollisionMath@@SA_NH@Z", 0x1000, 16, "Code/W/CollideA.cpp"),
        row("?draw@Widget@@QAEXXZ", 0x2000, 16, "Code/W/WidgetDraw.cpp"),
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert "Z=" not in out[0x1000]["evidence"]
    assert "Z=Code/Libraries/Math/widget.cpp" in out[0x2000]["evidence"]


WB_HEADER = "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"


def _wb(tmp_path, monkeypatch, foo_lead, bar_lead="Bar.cpp", foo_name="X::f", foo_was="",
        foo_kind="PLACEHOLDER", foo_notes=""):
    """Foo.cpp is a TU only naming proposes (N, no ZH definition); Bar.cpp's row pushes its
    own __FILE__ (F), the test of the WorldBuilder leads (W)."""
    monkeypatch.setattr(tu_map, "W_MIN", 1)
    (tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X").mkdir(parents=True)
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?a@Foo@@QAEXXZ", 0x1000, 16, "Code/X/FooA.cpp", notes=foo_notes),
        row("?b@Foo@@QAEXXZ", 0x1100, 16, "Code/X/FooB.cpp"),
        row("?rva00008000@Rva00008000@@QAEXXZ", 0x8000, 16, "Code/X/Rva00008000.cpp"),
    ]))
    (tmp_path / "reverse/string_xrefs.tsv").write_text("C:\\bfme2\\Code\\X\\Bar.cpp\t0x8004\n")
    (tmp_path / "reverse/wb_name_leads.csv").write_text(WB_HEADER + "".join(
        f"0x{rva:08X},{was},{kind},{name},C:\\Projects\\bfme2\\Code\\X\\{f},3.0,callgraph\n"
        for rva, was, kind, name, f in ((0x1000, foo_was, foo_kind, foo_name, foo_lead),
                                        (0x8000, "", "PLACEHOLDER", "X::f", bar_lead))))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_worldbuilder_lead_naming_the_hinted_path_anchors_the_tu(tmp_path, monkeypatch):
    out = _wb(tmp_path, monkeypatch, "Foo.cpp")
    for rva in (0x1000, 0x1100):
        assert (out[rva]["tu"], out[rva]["by"], out[rva]["confidence"]) == ("Code/X/Foo.cpp", "N", "approved")
        assert tu_map.canonical_tu(out[rva])
    assert "W=Code/X/Foo.cpp" in out[0x1000]["evidence"]


@pytest.mark.parametrize("was,kind,notes", [
    ("Rva00001000::rva00001000", "PLACEHOLDER", ""),   # the row took the lead's class after the lead
    ("", "UNROWED", ""),                               # the row was created from the lead
    ("Foo::rva00001000", "PIN_ONLY", "WB15D2AF0 names Foo::a in Foo.cpp"),   # its notes cite the lead
])
def test_worldbuilder_lead_does_not_corroborate_the_name_it_supplied(tmp_path, monkeypatch, was, kind, notes):
    """BuildPhase::update (0x005DCCFB) took its name and path from its WB lead: that lead
    naming the same path again is no independent anchor for the TU."""
    out = _wb(tmp_path, monkeypatch, "Foo.cpp", foo_name="Foo::a", foo_was=was, foo_kind=kind,
              foo_notes=notes)
    assert "W=Code/X/Foo.cpp" in out[0x1000]["evidence"]
    for rva in (0x1000, 0x1100):     # not anchored: approved only under a provisional name
        assert (out[rva]["tu"], tu_map.provisional_name(out[rva])) == ("Code/X/Foo.cpp", True), hex(rva)


def test_worldbuilder_lead_corroborates_a_class_named_before_it(tmp_path, monkeypatch):
    out = _wb(tmp_path, monkeypatch, "Foo.cpp", foo_name="Foo::a", foo_was="Foo::rva00001000",
              foo_kind="PIN_ONLY")
    assert tu_map.canonical_tu(out[0x1000]) and tu_map.canonical_tu(out[0x1100])


def test_worldbuilder_lead_naming_another_path_anchors_nothing(tmp_path, monkeypatch):
    out = _wb(tmp_path, monkeypatch, "Elsewhere.cpp")
    assert out[0x1000]["tu"] == "Code/X/Foo.cpp" and not tu_map.canonical_tu(out[0x1000])


def test_worldbuilder_leads_that_disagree_with_file_strings_anchor_nothing(tmp_path, monkeypatch):
    out = _wb(tmp_path, monkeypatch, "Foo.cpp", bar_lead="NotBar.cpp")
    assert not tu_map.canonical_tu(out[0x1000])
    rows = tu_map.evidence_rows(tu_map.Layout(tmp_path))
    assert tu_map.w_score(rows) == (1, 0) and not tu_map.w_passes(rows)


def test_far_placeholder_class_row_does_not_stretch_its_tu_span(tmp_path):
    """A K row (placeholder-class propagation) is never approved, so it is not part of its
    TU's span: one emitted past another TU's anchor must not make its TU noncontiguous."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("void A::f()\n{\n}\nvoid A::g()\n{\n}\n")
    (zh / "B.cpp").write_text("void B::f()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/Af.cpp"),
        row("?x@Rva00001080@@QAEXXZ", 0x1080, 16, "Code/X/Rva00001080.cpp"),   # C between A's anchors
        row("?g@A@@QAEXXZ", 0x1100, 16, "Code/X/Ag.cpp"),
        row("?f@B@@QAEXXZ", 0x3000, 16, "Code/X/Bf.cpp"),
        row("??1Rva00001080@@QAE@XZ", 0x5000, 16, "Code/X/Rva00001080Dtor.cpp"),  # K, past B
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert (out[0x5000]["by"], out[0x5000]["tu"], out[0x5000]["confidence"]) == ("K", "Code/X/A.cpp", "proposed")
    for rva, by in ((0x1000, "Z"), (0x1080, "C"), (0x1100, "Z"), (0x3000, "Z")):
        assert (out[rva]["by"], out[rva]["confidence"]) == (by, "approved"), hex(rva)
        assert "noncontiguous" not in out[rva]["evidence"]


def test_header_macros_expand_into_class_inline_members():
    macros = tu_map.header_macros([
        "#define GLUE(cls) \\\n public: virtual int getPool() { return cls##_pool; } \\\n"
        " static const char *name() { return #cls; }\n"
        "#define MODULE(cls) \\\n GLUE(cls) \\\n virtual int getKey() const { return 1; }\n"
        "#define BEGIN_LOOP(x) for (x) {\n"
        "#define LOG(x) printf x\n"])
    assert sorted(macros) == ["GLUE", "MODULE"]       # BEGIN_LOOP is unbalanced, LOG defines nothing
    text = "class Helper : public Module\n{\n\tMODULE( Helper )\npublic:\n\tvoid f();\n};\n"
    assert sorted(tu_map.class_inline_members(tu_map.expand_macros(text, macros))) == \
        [("Helper", "getKey"), ("Helper", "getPool"), ("Helper", "name")]
    assert list(tu_map.class_inline_members(text)) == []


def test_macro_generated_inline_virtual_is_not_placed_by_class_site(tmp_path):
    """A helper's getModuleNameKey comes from MAKE_STANDARD_MODULE_MACRO in its header and is
    emitted as a COMDAT where its vftable is (Object.cpp in retail); the class site S must
    not claim it and so split the host's span."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Module.h").write_text("#define MAKE_MOD( cls ) \\\npublic: \\\n"
                                 "\tvirtual int getModuleNameKey() const { return 1; }\n")
    (zh / "Helper.h").write_text("class Helper : public Module\n{\n\tMAKE_MOD( Helper )\n"
                                 "public:\n\tvoid f();\n};\n")
    (zh / "Helper.cpp").write_text("void Helper::f()\n{\n}\n")
    (zh / "Host.cpp").write_text("void Host::a()\n{\n}\nvoid Host::b()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?a@Host@@QAEXXZ", 0x1000, 16, "Code/X/HostA.cpp"),
        row("?getModuleNameKey@Helper@@UBEHXZ", 0x1080, 16, "Code/X/HelperKey.cpp"),
        row("?b@Host@@QAEXXZ", 0x1100, 16, "Code/X/HostB.cpp"),
        row("?f@Helper@@QAEXXZ", 0x9000, 16, "Code/X/HelperF.cpp"),
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    key = out[0x1080]
    assert "S=" not in key["evidence"]
    assert (key["by"], key["tu"], key["confidence"]) == ("C", "Code/X/Host.cpp", "approved")
    assert out[0x1000]["confidence"] == out[0x1100]["confidence"] == "approved"


# ---------------------------------------------------------------- header-inline COMDATs
@pytest.fixture
def header_inline(tmp_path):
    """The two retail cases: DamageModule's header-inline constructor sits inside
    BoneFXDamage's TU (0x004B9704, between BoneFXDamage rows), and RenderObjClass's
    in-class virtual Set_Additive sits in the inline-virtual block a derived
    constructor's vftable pulls in (0x0006CF8C, after BaseHeightMapRenderObjClass's
    constructor). Neither belongs in its class's .cpp."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    dmg, ww3d = zh / "GameEngine/Source/Damage", zh / "Libraries/WW3D2"
    dmg.mkdir(parents=True)
    ww3d.mkdir(parents=True)
    (dmg / "DamageModule.cpp").write_text("void DamageModule::crc(Xfer *x)\n{\n}\n")
    (dmg / "DamageModule.h").write_text(
        "class DamageModule : public BehaviorModule\n{\npublic:\n"
        "\tDamageModule( Thing *thing, const ModuleData* moduleData );\n"
        "\tint getMask() const { return 1; }\n};\n"
        "inline DamageModule::DamageModule( Thing *thing, const ModuleData* moduleData )"
        " : BehaviorModule( thing, moduleData ) { }\n")
    (dmg / "BoneFXDamage.cpp").write_text(
        "BoneFXDamage::BoneFXDamage(Thing *t, const ModuleData *d) : DamageModule(t, d)\n{\n}\n"
        "void BoneFXDamage::onObjectCreated()\n{\n}\n")
    (ww3d / "rendobj.cpp").write_text("RenderObjClass::RenderObjClass()\n{\n}\n")
    (ww3d / "rendobj.h").write_text(
        "class RenderObjClass\n{\npublic:\n\tRenderObjClass(void);\n"
        "\tvirtual int\t\tIs_Additive(void) const\t\t{ return Bits & IS_ADDITIVE; }\n"
        "\tvirtual void\tSet_Additive(int onoff)\t\t{ if (onoff) { Bits |= IS_ADDITIVE; } else { Bits &= ~IS_ADDITIVE; } }\n"
        "\tint\t\t\t\tGet_Bits(void)\t\t\t{ return Bits; }\n"
        "protected:\n\tint Bits;\n};\n")
    (ww3d / "HeightMap.cpp").write_text(
        "BaseHeightMapRenderObjClass::BaseHeightMapRenderObjClass()\n{\n}\n"
        "void BaseHeightMapRenderObjClass::Render()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    g, w = "Code/GameEngine/Source/Damage", "Code/Libraries/WW3D2"
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("??0BoneFXDamage@@QAE@PAVThing@@PBVModuleData@@@Z", 0x4B9600, 16, f"{g}/BoneFXDamage.cpp"),
        row("??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z", 0x4B9704, 49, f"{g}/DamageModuleCtor.cpp"),
        row("?onObjectCreated@BoneFXDamage@@MAEXXZ", 0x4B97E2, 16, f"{g}/BoneFXDamage.cpp"),
        row("?crc@DamageModule@@MAEXPAVXfer@@@Z", 0x600000, 16, f"{g}/DamageModuleCrc.cpp"),
        row("??0BaseHeightMapRenderObjClass@@QAE@XZ", 0x6C9CF, 16, f"{w}/HeightMap.cpp"),
        row("?Set_Additive@RenderObjClass@@UAEXH@Z", 0x6CF8C, 20, f"{w}/RenderObjAccessors.cpp"),
        row("?Render@BaseHeightMapRenderObjClass@@UAEXXZ", 0x6D100, 16, f"{w}/HeightMap.cpp"),
        row("??0RenderObjClass@@QAE@XZ", 0x13BF00, 16, f"{w}/RenderObjCtor.cpp"),
        row("?Get_Bits@RenderObjClass@@QAEHXZ", 0x13C000, 16, f"{w}/RenderObjBits.cpp"),
    ]))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_header_inline_constructor_is_not_placed_by_class_site(header_inline):
    ctor = header_inline[0x4B9704]
    assert "S=" not in ctor["evidence"] and "N=" not in ctor["evidence"]
    assert ctor["tu"] != "Code/GameEngine/Source/Damage/DamageModule.cpp"


def test_in_class_inline_virtual_is_not_placed_by_class_site(header_inline):
    additive = header_inline[0x6CF8C]
    assert "S=" not in additive["evidence"] and "N=" not in additive["evidence"]
    assert additive["tu"] != "Code/Libraries/WW3D2/rendobj.cpp"


def test_class_site_evidence_kept_for_out_of_line_and_non_virtual_members(header_inline):
    # negative controls (hold with or without the narrowing): only constructors and
    # virtual members whose ZH body is in a header lose S.
    assert "S=Code/GameEngine/Source/Damage/DamageModule.cpp" in header_inline[0x600000]["evidence"]
    assert "Z=Code/Libraries/WW3D2/rendobj.cpp" in header_inline[0x13BF00]["evidence"]
    assert "S=Code/Libraries/WW3D2/rendobj.cpp" in header_inline[0x13C000]["evidence"]


def test_header_inline_anchor_no_longer_splits_its_class_span(header_inline):
    # the ctor's S anchor inside BoneFXDamage's rows made DamageModule.cpp noncontiguous,
    # so the class's real out-of-line member lost its placement too.
    assert header_inline[0x600000]["tu"] == "Code/GameEngine/Source/Damage/DamageModule.cpp"


def _copy_ctor(tmp_path, slot_cpp):
    """Retail 0x0044B27F: LANGameSlot's copy constructor sits among LANAPI's rows (LANAPI's
    RequestGameCreate copies a slot), while ZH's LANGameInfo.cpp defines only the default
    constructor. Both files' rows here are Z anchors, so a Z on the copy breaks both spans."""
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Net"
    zh.mkdir(parents=True)
    (zh / "LANAPI.cpp").write_text("".join(f"void LANAPI::{m}()\n{{\n}}\n" for m in "fghi"))
    (zh / "LANGameInfo.cpp").write_text(slot_cpp + "void LANGameInfo::f()\n{\n}\nvoid LANGameInfo::g()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    d = "Code/Net"
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("??0LANGameSlot@@QAE@XZ", 0x1000, 16, f"{d}/LANGameSlot.cpp"),
        row("?f@LANGameInfo@@QAEXXZ", 0x1010, 16, f"{d}/LANGameInfo.cpp"),
        row("?g@LANGameInfo@@QAEXXZ", 0x1020, 16, f"{d}/LANGameInfo.cpp"),
        row("?f@LANAPI@@QAEXXZ", 0x2000, 16, f"{d}/LANAPI.cpp"),
        row("?g@LANAPI@@QAEXXZ", 0x2010, 16, f"{d}/LANAPI.cpp"),
        row("??0LANGameSlot@@QAE@ABV0@@Z", 0x2020, 16, f"{d}/LANGameSlotCopy.cpp"),
        row("?h@LANAPI@@QAEXXZ", 0x2030, 16, f"{d}/LANAPI.cpp"),
        row("?i@LANAPI@@QAEXXZ", 0x2040, 16, f"{d}/LANAPI.cpp"),
    ]))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_implicit_copy_constructor_takes_no_anchor_from_another_constructor(tmp_path):
    out = _copy_ctor(tmp_path, "LANGameSlot::LANGameSlot()\n{\n}\n")
    copy = out[0x2020]
    assert not any(k in copy["evidence"] for k in ("Z=", "S=", "N="))
    assert (copy["tu"], copy["by"], copy["confidence"]) == ("Code/Net/LANAPI.cpp", "C", "approved")
    for rva in (0x1000, 0x1010, 0x1020):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/Net/LANGameInfo.cpp", "approved"), hex(rva)
    for rva in (0x2000, 0x2010, 0x2030, 0x2040):
        assert (out[rva]["tu"], out[rva]["confidence"]) == ("Code/Net/LANAPI.cpp", "approved"), hex(rva)


def test_copy_constructor_zh_defines_out_of_line_keeps_its_anchor(tmp_path):
    # negative control: ZH's own `X::X( const X &` definition is an out-of-line Z anchor
    out = _copy_ctor(tmp_path, "LANGameSlot::LANGameSlot()\n{\n}\n"
                               "LANGameSlot::LANGameSlot( const LANGameSlot &that )\n{\n}\n")
    copy = out[0x2020]
    assert (copy["by"], copy["tu"]) == ("Z", "Code/Net/LANGameInfo.cpp")
    assert "island" not in copy["evidence"]
    assert out[0x2000]["confidence"] == "proposed" and "noncontiguous" in out[0x2000]["evidence"]


# The W3DGameClient layout in retail: two in-class virtual factories (0x0004C4F9
# createFontLibrary, 0x0004C5F8 createSnowManager) with the class's twelve
# neighbouring rows between and after them, then W3DGameClient's own out-of-line
# members from 0x0004C7A8. The class's code (and so its vftable) is right there.
W3D_TWELVE = [0x4C553, 0x4C585, 0x4C5C6, 0x4C62D, 0x4C662, 0x4C694,
              0x4C6C6, 0x4C6D4, 0x4C709, 0x4C743, 0x4C755, 0x4C75A]


@pytest.fixture
def w3d_client(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/W3D"
    zh.mkdir(parents=True)
    (zh / "W3DGameClient.cpp").write_text(
        "W3DGameClient::W3DGameClient()\n{\n}\n"
        "void W3DGameClient::addScorch(const Coord3D *pos, Real r, Scorches type)\n{\n}\n"
        "void W3DGameClient::createRayEffectByTemplate(const Coord3D *s)\n{\n}\n"
        "void W3DGameClient::setTimeOfDay(TimeOfDay tod)\n{\n}\n"
        "void W3DGameClient::setTeamColor(Int r, Int g, Int b)\n{\n}\n")
    (zh / "W3DGameClient.h").write_text(
        "class W3DGameClient : public GameClient\n{\npublic:\n\tW3DGameClient();\n"
        "protected:\n"
        "\tvirtual FontLibrary *createFontLibrary( void ) { return NEW W3DFontLibrary; }\n"
        "\tvirtual SnowManager *createSnowManager( void ) { return NEW W3DSnowManager; }\n};\n")
    (tmp_path / "reverse").mkdir()
    w = "Code/W3D"
    rows = [row("?createFontLibrary@W3DGameClient@@MAEPAVFontLibrary@@XZ", 0x4C4F9, 16,
                f"{w}/W3DGameClientFontFactory.cpp"),
            row("?createSnowManager@W3DGameClient@@MAEPAVSnowManager@@XZ", 0x4C5F8, 16,
                f"{w}/W3DGameClientSnowFactory.cpp")]
    rows += [row(f"?rva{a:08X}@Rva004C743@@QAEPAXXZ", a, 16, f"{w}/W3DGameClientFactories.cpp")
             for a in W3D_TWELVE]
    rows += [row(n, a, 16, f"{w}/W3DGameClient.cpp") for n, a in [
        ("?addScorch@W3DGameClient@@UAEXPBUCoord3D@@MW4Scorches@@@Z", 0x4C7A8),
        ("?createRayEffectByTemplate@W3DGameClient@@UAEXPBUCoord3D@@@Z", 0x4C7F0),
        ("?setTimeOfDay@W3DGameClient@@UAEXW4TimeOfDay@@@Z", 0x4C884),
        ("?setTeamColor@W3DGameClient@@UAEXHHH@Z", 0x4C8BC)]]
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(sorted(rows, key=lambda r: r.split(",")[2])))
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_inline_virtuals_beside_their_class_code_keep_the_class_site(w3d_client):
    site = "Code/W3D/W3DGameClient.cpp"
    for a in (0x4C4F9, 0x4C5F8):
        assert f"S={site}" in w3d_client[a]["evidence"]
        assert w3d_client[a]["tu"] == site and w3d_client[a]["confidence"] == "approved"


def test_w3dgameclient_neighbouring_rows_stay_approved(w3d_client):
    site = "Code/W3D/W3DGameClient.cpp"
    for a in W3D_TWELVE:
        assert (w3d_client[a]["tu"], w3d_client[a]["confidence"]) == (site, "approved"), hex(a)


def test_inline_virtual_with_another_files_anchor_between_is_contested(tmp_path):
    # adjacent TUs interleaving within GAP: the nearest Z row is another file's, so the
    # same-site anchor beyond it does not give the inline virtual its class site back.
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "Foo.cpp").write_text("void Foo::a()\n{\n}\n")
    (zh / "Bar.cpp").write_text("void Bar::b()\n{\n}\n")
    (zh / "Foo.h").write_text("class Foo\n{\npublic:\n\tvirtual int v(void) { return 1; }\n};\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?a@Foo@@QAEXXZ", 0x9000, 16, "Code/X/FooA.cpp"),
        row("?b@Bar@@QAEXXZ", 0x9400, 16, "Code/X/BarB.cpp"),
        row("?v@Foo@@UAEHXZ", 0x9800, 16, "Code/X/FooV.cpp"),
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert "S=" not in out[0x9800]["evidence"]


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
    (zh / "GameEngine").mkdir(parents=True)
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


# ---------------------------------------------------------------- review round 2 (2026-10-09)
ZH_REL = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"


def test_fingerprint_tracks_the_zh_tree(tmp_path):
    root, sub = tmp_path / "root", tmp_path / "root/reference/open-bfme-1"
    zh = root / ZH_REL
    (zh / "GameEngine").mkdir(parents=True)
    (zh / "GameEngine/A.cpp").write_text("void A::f()\n{\n}\n", newline="\n")
    (root / "reverse").mkdir()
    (root / "reverse/functions.csv").write_text(HEADER + row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/A.cpp"))
    for args in (("init", "-q"), ("config", "user.name", "t"), ("config", "user.email", "t@t"),
                 ("add", "-A"), ("commit", "-qm", "zh")):
        git(sub, *args)                                   # the submodule: a clean checkout
    commit = subprocess.run(["git", "rev-parse", "HEAD"], cwd=sub, capture_output=True, text=True).stdout.strip()
    assert tu_map.main(["--root", str(root)]) == 0
    text = (root / "reverse/tu_map.inputs.sha256").read_text()
    assert f"  {tu_map.ZH_KEY}\n" in text and "\ngit:" in text and f"commit {commit}" in text
    assert tu_map.check_fresh(tu_map.Layout(root)) == []
    (zh / "GameEngine/A.cpp").write_text("void A::f()\n{\n}\nvoid A::g()\n{\n}\n", newline="\n")
    assert tu_map.check_fresh(tu_map.Layout(root)) == [tu_map.ZH_KEY]        # dirty
    git(sub, "commit", "-qam", "zh2")
    assert tu_map.check_fresh(tu_map.Layout(root)) == [tu_map.ZH_KEY]        # another tree
    # a worktree's copy through --zh is hashed, and equals the submodule when its files do
    copy = tmp_path / "copy"
    (copy / "GameEngine").mkdir(parents=True)
    (copy / "GameEngine/A.cpp").write_bytes((zh / "GameEngine/A.cpp").read_bytes().replace(b"\n", b"\r\n"))
    assert tu_map.main(["--root", str(root), "--zh", str(copy)]) == 0
    assert "\nsha256:" in (root / "reverse/tu_map.inputs.sha256").read_text()
    assert tu_map.check_fresh(tu_map.Layout(root)) == []                     # the submodule, same files
    (copy / "GameEngine/B.cpp").write_text("void B::f()\n{\n}\n")
    assert tu_map.check_fresh(tu_map.Layout(root, copy)) == [tu_map.ZH_KEY]


def test_zh_must_be_a_generalsmd_code_tree(tmp_path, capsys):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER)
    assert tu_map.main(["--root", str(tmp_path), "--zh", str(TOOLS / "tu_map.py")]) == 2
    assert tu_map.main(["--root", str(tmp_path), "--zh", str(tmp_path)]) == 2
    assert "not a ZH GeneralsMD/Code tree" in capsys.readouterr().err
    assert not (tmp_path / "reverse/tu_map.csv").exists()


def test_zh_definition_needs_balanced_parameters_and_a_body():
    text = ("void Foo::bar( int a )\n{\n"
            "Base::f(a,\n\tb);\n"                                          # a call at column 0, two lines
            "}\n"
            "BezierSegment BezierSegment::s_bezBasisMatrix( -1, 3, -3, 1,\n\t3, -6, 3, 0 );\n"   # data
            "const Matrix3x3 Matrix3x3::RotateX90\n(\n\t1, 0, 0\n);\n"     # data, `(` on the next line
            "Foo::Foo( int a ) : Base( a ), m_s( \")\" )\n{\n}\n"          # initializer list
            "int Foo::get( void ) const\n{\n}\n"
            "void Foo::risky( void ) throw( int )\n{\n}\n"
            "char Foo::paren( char c = '(' )\n{\n}\n"                      # parentheses in literals
            "void Foo::declared( void );\n")
    assert list(tu_map.zh_definitions(text)) == [
        ("Foo", "bar"), ("Foo", "Foo"), ("Foo", "get"), ("Foo", "risky"), ("Foo", "paren")]


@pytest.fixture
def stale_map(tmp_path, monkeypatch):
    """A map written before contradicted approvals were demoted: 0x1040 approved for
    StateMachine.cpp while retail's __FILE__ string there names TurretAI.cpp."""
    sm, ta = "Code/GameEngine/Source/Common/StateMachine.cpp", "Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp"
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "t")
    git(tmp_path, "config", "user.email", "t@t")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + row("?z@Far@@QAEXXZ", 0x9000, 16, "Code/X/Far.cpp"))
    (tmp_path / "reverse/tu_map.csv").write_text(
        "rva,size,kind,tu,confidence,by,evidence,source\n"
        f"0x00001000,64,code,{sm},approved,Z,Z={sm},\n"
        f"0x00001040,64,code,{sm},approved,N,F={ta},\n"
        f"0x00001080,64,code-unledgered,{sm},approved,C,C=0x00001040..0x000010C0,\n"
        f"0x000010C0,64,code,{sm},approved,Z,Z={sm},\n")
    (tmp_path / ta).parent.mkdir(parents=True)
    (tmp_path / ta).write_text("//\n")
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "base")
    monkeypatch.setattr(tu_ownership, "ROOT", tmp_path)
    monkeypatch.setattr(tu_ownership, "LAYOUT", tu_map.Layout(tmp_path))
    monkeypatch.setattr(tu_ownership, "_FP", None)
    monkeypatch.setenv("REPAIR_ROOT", str(tmp_path))
    import importlib
    import repair_queue
    return tmp_path, importlib.reload(repair_queue)


def test_dest_and_ownership_share_one_approval_verdict(stale_map):
    repo, rq = stale_map
    led = repo / "reverse/functions.csv"
    base = led.read_text()
    for rva in (0x1000, 0x1040, 0x1048, 0x1080, 0x10C0):
        got = rq.dest_tu(rva)
        if got["dest"]:                                   # where dest routes a row, ownership lets it land
            led.write_text(base + row("?n@New@@QAEXXZ", rva, 4, got["dest"]))
            assert staged(repo) == set(), (hex(rva), got)
        led.write_text(base + row("?n@New@@QAEXXZ", rva, 4, "Code/X/Elsewhere.cpp"))
        assert (staged(repo) == {"A3"}) == got["basis"].startswith("approved TU"), (hex(rva), got)
        led.write_text(base)
    assert rq.dest_tu(0x1040)["dest"].endswith("AI/TurretAI.cpp")


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


@pytest.mark.parametrize("declaration", [
    "class Reg::Version",
    "struct Reg::Version",
    "class __declspec(novtable) Reg::Version",
    "class Reg::More::Version",
])
def test_b1_qualified_nested_class_is_not_its_registered_owner(repo, declaration):
    # DetachableRiderUpdate defines Xfer::Version beside the canonical Xfer
    # include. The scope qualifier must not be parsed as an inheritance colon.
    (repo / "Code/X/Baz.cpp").write_text(
        '#include "Shared.h"\n' + declaration + "\n{\npublic:\n"
        "    unsigned char current;\n    unsigned char minimum;\n};\n")
    assert staged(repo) == set()
    name = declaration.rsplit(" ", 1)[-1]
    assert name in tu_ownership.class_bodies(declaration + "\n{\n};\n")


@pytest.mark.parametrize("bases", [": public Base", ":public Scope::Base"])
def test_b1_inherited_private_copy_of_registered_class_is_refused(repo, bases):
    (repo / "Code/X/Baz.cpp").write_text(
        "class Reg" + bases + "\n{\npublic:\n    int a;\n    float b;\n};\n")
    assert staged(repo) == {"B1"}


def test_b2_fingerprint_is_diagnostic_only(repo):
    (repo / "Code/X/Qux.cpp").write_text("class Rva00001234\n{\npublic:\n    int x;\n    float y;\n};\n")
    git(repo, "add", "-A")
    found = tu_ownership.check("HEAD", None)
    assert [r for r, _ in found] == ["B2"]
    assert tu_ownership.report(found, shadow=False) == 0


# ---------------------------------------------------------------- vendored upstream TUs (L)
def _vendored(tmp_path, monkeypatch, files, ledger, l_min=2):
    """A tree holding vendored library files and their ledger rows; L's gate sized for it."""
    monkeypatch.setattr(tu_map, "L_MIN", l_min)
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, newline="\n")
    (tmp_path / "reverse").mkdir(exist_ok=True)
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(
        row(name, rva, 16, src, notes=notes) for name, rva, src, notes in ledger), newline="\n")
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


LUA = "Code/Libraries/Source/Lua"


def _lua(name, body):
    return f"/*\n** $Id: {name},v 1.1 $\n*/\n" + body


def test_whole_upstream_file_anchors_the_functions_it_alone_defines(tmp_path, monkeypatch):
    files = {f"{LUA}/lapi.c": _lua("lapi.c", "int lua_a (lua_State *L) {\n}\nstatic void b (int x)\n{\n}\n"
                                   "int lua_c (lua_State *L) {\n}\nint lua_d (lua_State *L) {\n}\n"),
             f"{LUA}/lauxlib.c": _lua("lauxlib.c", "void luaL_x (void) {\n}\nvoid luaL_y (void) {\n}\n"
                                      "void luaL_z (void) {\n}\nstatic void b (int y)\n{\n}\n")}
    tag = "vendored=lua-4.0.1"
    out = _vendored(tmp_path, monkeypatch, files, [
        ("_lua_a", 0x1000, f"{LUA}/lapi.c", tag), ("_b", 0x1010, f"{LUA}/lapi.c", ""),
        ("_lua_c", 0x1020, f"{LUA}/lapi.c", ""), ("_lua_d", 0x1030, f"{LUA}/lapi.c", ""),
        ("_luaL_x", 0x2000, f"{LUA}/lauxlib.c", tag), ("_luaL_y", 0x2010, f"{LUA}/lauxlib.c", ""),
        ("_luaL_z", 0x2020, f"{LUA}/lauxlib.c", "")])
    for rva in (0x1000, 0x1020, 0x1030, 0x2000, 0x2010, 0x2020):
        assert (out[rva]["by"], out[rva]["confidence"]) == ("L", "approved"), hex(rva)
        assert out[rva]["tu"] == out[rva]["source"] and f"L={out[rva]['source']}" in out[rva]["evidence"]
    # `b` is defined in both files (two statics): no L, but contiguity still places it
    assert "L=" not in out[0x1010]["evidence"]
    assert (out[0x1010]["by"], out[0x1010]["tu"], out[0x1010]["confidence"]) == ("C", f"{LUA}/lapi.c", "approved")


def test_a_carved_file_and_header_inline_libraries_name_no_tu(tmp_path, monkeypatch):
    files = {f"{LUA}/liolib.c": _lua("liolib.c", "int io_a (lua_State *L) {\n}\n"),
             # carved out of liolib.c: its stem extends liolib's and its text never names itself
             f"{LUA}/liolib_bfme1.c": _lua("liolib.c", "int io_b (lua_State *L) {\n}\nint io_c (lua_State *L) {\n}\n"),
             "Code/Libraries/Source/ATL/atlbase.cpp": "/* atlbase.cpp */\nvoid AtlThing (void) {\n}\n"}
    out = _vendored(tmp_path, monkeypatch, files, [
        ("_io_a", 0x1000, f"{LUA}/liolib.c", "vendored=lua-4.0.1"),
        ("_io_b", 0x1010, f"{LUA}/liolib_bfme1.c", "vendored=lua-4.0.1"),
        ("_io_c", 0x1020, f"{LUA}/liolib_bfme1.c", "vendored=lua-4.0.1"),
        ("_AtlThing", 0x5000, "Code/Libraries/Source/ATL/atlbase.cpp", "vendored=atl-7.1")])
    assert set(tu_map.upstream_files(tu_map.Layout(tmp_path), tu_map.read_csv(tmp_path / "reverse/functions.csv"))) \
        == {f"{LUA}/liolib.c"}
    for rva in (0x1010, 0x1020, 0x5000):
        assert "L=" not in out[rva]["evidence"] and out[rva]["confidence"] != "approved", hex(rva)


def test_a_carved_file_stays_carved_when_its_parent_has_no_ledger_rows(tmp_path, monkeypatch):
    """The parent on disk decides, not the ledger's coverage of it (review 2026-10-28)."""
    files = {f"{LUA}/liolib.c": _lua("liolib.c", "int io_a (lua_State *L) {\n}\n"),
             f"{LUA}/liolib_bfme1.c": _lua("liolib.c", "int io_b (lua_State *L) {\n}\nint io_c (lua_State *L) {\n}\n")}
    out = _vendored(tmp_path, monkeypatch, files, [
        ("_io_b", 0x1010, f"{LUA}/liolib_bfme1.c", "vendored=lua-4.0.1"),
        ("_io_c", 0x1020, f"{LUA}/liolib_bfme1.c", "vendored=lua-4.0.1")])
    assert not tu_map.upstream_files(tu_map.Layout(tmp_path), tu_map.read_csv(tmp_path / "reverse/functions.csv"))
    for rva in (0x1010, 0x1020):
        assert "L=" not in out[rva]["evidence"] and out[rva]["confidence"] != "approved", hex(rva)


def test_l_anchors_nothing_while_retail_order_disagrees(tmp_path, monkeypatch):
    files = {f"{LUA}/{n}.c": _lua(f"{n}.c", "".join(f"void {n}_{i} (void) {{\n}}\n" for i in range(3)))
             for n in ("la", "lb")}
    ledger = [(f"_{n}_{i}", 0x1000 + 0x20 * (2 * i + k), f"{LUA}/{n}.c", "vendored=lua-4.0.1")
              for i in range(3) for k, n in enumerate(("la", "lb"))]     # la, lb, la, lb, ... interleaved
    rows = None
    monkeypatch.setattr(tu_map, "L_MIN", 2)
    out = _vendored(tmp_path, monkeypatch, files, ledger)
    rows = tu_map.evidence_rows(tu_map.Layout(tmp_path))
    n, ok = tu_map.l_score(rows)
    assert n >= 2 and ok == 0 and not tu_map.l_passes(rows)
    assert not any(r["L"] for r in rows)
    assert not any(r["confidence"] == "approved" for r in out.values())


def test_c_definitions_read_ansi_k_and_r_and_next_line_heads():
    text = ("local void fill_window OF((deflate_state *s));\n"          # a prototype through a macro
            "int ZEXPORT compress2 (dest, destLen)\n    Bytef *dest;\n    uLongf *destLen;\n{\n}\n"
            "static GPResult gpiNewTransfer\n(\n  GPConnection * connection\n)\n{\n}\n"
            "int lua_gettop (lua_State *L) {\n}\n"
            "int declared_only (int x);\n"
            "void LZHLEncoder::flush (void) {\n}\n"
            "/* void commented_out (void) {\n} */\n")
    assert tu_map.c_definitions(text) == {"compress2", "gpiNewTransfer", "lua_gettop", "LZHLEncoder::flush"}


def test_c_symbol_spells_the_source_name():
    assert [tu_map.c_symbol(s) for s in ("_lua_gettop", "_SetErrorMode@4", "@fast@8", "__tr_init",
                                         "?free@@YAXXZ", "?flush@LZHLEncoder@@QAEXXZ", "$L123")] == \
        ["lua_gettop", "SetErrorMode", "fast", "_tr_init", "free", "LZHLEncoder::flush", None]


def test_fingerprint_tracks_the_vendored_files_l_reads(tmp_path):
    (tmp_path / "reverse").mkdir()
    (tmp_path / ZH_REL / "GameEngine").mkdir(parents=True)
    lapi = tmp_path / LUA / "lapi.c"
    lapi.parent.mkdir(parents=True)
    lapi.write_text(_lua("lapi.c", "int lua_a (void) {\n}\n"), newline="\n")
    (tmp_path / "reverse/functions.csv").write_text(
        HEADER + row("_lua_a", 0x1000, 16, f"{LUA}/lapi.c", notes="vendored=lua-4.0.1"), newline="\n")
    assert tu_map.main(["--root", str(tmp_path)]) == 0
    assert f"  {tu_map.L_KEY}\n" in (tmp_path / "reverse/tu_map.inputs.sha256").read_text()
    assert tu_map.check_fresh(tu_map.Layout(tmp_path)) == []
    lapi.write_text(_lua("lapi.c", "int lua_a (void) {\n}\nint lua_b (void) {\n}\n"), newline="\n")
    assert tu_map.check_fresh(tu_map.Layout(tmp_path)) == [tu_map.L_KEY]


# ---------------------------------------------------------------- provisional names
def _prov(tmp_path, ledger, data=""):
    """A.cpp is anchored by its ZH definitions; every other class is named by this tree alone."""
    zh = tmp_path / ZH_REL / "X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("void A::f()\n{\n}\nvoid A::g()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join(
        row(name, rva, 16, f"Code/X/{src}") for name, rva, src in ledger))
    if data:
        (tmp_path / "reverse/data_xrefs.tsv").write_text(
            "rva\tsection\tsize_bound\twidths\tfloat\tkinds\tref_count\tcallers\n" + data)
    return {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}


def test_unanchored_contiguous_tu_is_approved_under_a_provisional_name(tmp_path):
    out = _prov(tmp_path, [("?f@A@@QAEXXZ", 0x1000, "Af.cpp"), ("?g@A@@QAEXXZ", 0x1100, "Ag.cpp"),
                           ("?a@Foo@@QAEXXZ", 0x5000, "FooA.cpp"),
                           ("?rva00005010@Rva00005010@@QAEXXZ", 0x5010, "Rva00005010.cpp"),
                           ("?b@Foo@@QAEXXZ", 0x5020, "FooB.cpp")],
                data="0x00900000\t.data\t4\t4\t0\tread\t2\t0x5004,0x5024\n")
    for rva, by in ((0x5000, "N"), (0x5010, "C"), (0x5020, "N")):
        r = out[rva]
        assert (r["tu"], r["by"], r["confidence"]) == ("Code/X/Foo.cpp", by, "approved"), hex(rva)
        assert tu_map.provisional_name(r) and not tu_map.canonical_tu(r)
    assert all(tu_map.canonical_tu(out[rva]) for rva in (0x1000, 0x1100))
    data = out[0x900000]                       # referenced only by the provisional TU's rows
    assert data["tu"] == "Code/X/Foo.cpp" and tu_map.provisional_name(data)


def test_a_single_naming_hint_is_never_a_provisional_tu(tmp_path):
    out = _prov(tmp_path, [("?f@A@@QAEXXZ", 0x1000, "Af.cpp"), ("?a@Lone@@QAEXXZ", 0x8000, "LoneA.cpp")])
    assert (out[0x8000]["tu"], out[0x8000]["confidence"]) == ("Code/X/Lone.cpp", "proposed")


def test_unanchored_tu_inside_an_anchored_span_stays_proposed(tmp_path):
    # A's span is wider than UNION_SPAN, so naming does not fold Bar into A (U)
    out = _prov(tmp_path, [("?f@A@@QAEXXZ", 0x1000, "Af.cpp"), ("?a@Bar@@QAEXXZ", 0x2000, "BarA.cpp"),
                           ("?b@Bar@@QAEXXZ", 0x2010, "BarB.cpp"), ("?g@A@@QAEXXZ", 0x3800, "Ag.cpp")])
    assert [(out[rva]["tu"], out[rva]["confidence"]) for rva in (0x2000, 0x2010)] ==         [("Code/X/Bar.cpp", "proposed")] * 2
    assert tu_map.canonical_tu(out[0x1000]) and tu_map.canonical_tu(out[0x3800])


def test_interleaved_unanchored_tus_are_neither_provisional(tmp_path):
    # spans wider than UNION_SPAN, so naming does not merge them into one file
    out = _prov(tmp_path, [("?a@Foo@@QAEXXZ", 0x5000, "FooA.cpp"), ("?a@Bar@@QAEXXZ", 0x6000, "BarA.cpp"),
                           ("?b@Foo@@QAEXXZ", 0x8000, "FooB.cpp"), ("?b@Bar@@QAEXXZ", 0x9000, "BarB.cpp")])
    assert {out[rva]["tu"] for rva in (0x5000, 0x8000)} == {"Code/X/Foo.cpp"}
    assert all(out[rva]["confidence"] == "proposed" for rva in (0x5000, 0x6000, 0x8000, 0x9000))
