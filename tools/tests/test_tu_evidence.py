"""tools/tu_evidence.py on a synthetic retail image: EH handlers and funclets in a
`.text$x` tail, a `.CRT$XCU` initializer table, a vftable and .rdata items, with a
hand-written map of anchored rows. Each signal brackets an unplaced row between one
TU's anchors and abstains at a TU boundary; leave-one-out never lets a row anchor
itself; a funclet follows its parent's TU and confidence; nothing changes while no
signal is promoted; evidence rows re-check deterministically; the picker serves the
unplaced sources' runs with their evidence."""
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import tu_evidence as te  # noqa: E402
import tu_map  # noqa: E402

BASE = 0x400000
TEXT, RDATA, DATA = 0x1000, 0x4000, 0x5000
# (name, rva, tu, by): A1 A2 [X] A3 | B1 B2 in .text, each with an EH prologue
FUNCS = [("A1", 0x1000, "Code/A.cpp", "Z"), ("A2", 0x1100, "Code/A.cpp", "Z"), ("X", 0x1200, "", ""),
         ("A3", 0x1300, "Code/A.cpp", "Z"), ("B1", 0x1400, "Code/B.cpp", "Z"), ("B2", 0x1500, "Code/B.cpp", "Z")]
HANDLER = 0x3000            # .text$x: handlers, then funclets
FUNCLET = 0x3800
FUNCINFO = RDATA + 0x100
UNWIND = RDATA + 0x400
VFT = RDATA + 0x600
ITEMS = RDATA + 0x800
XC_A, XC_Z = DATA, DATA + 0x14


def va(rva):
    return struct.pack("<I", BASE + rva)


def image():
    text = bytearray(b"\xCC" * 0x3000)
    rdata = bytearray(0x1000)
    data = bytearray(0x100)
    for i, (_, rva, _, _) in enumerate(FUNCS):
        text[rva - TEXT:rva - TEXT + 10] = b"\xB8" + va(HANDLER + 0x10 * i) + b"\xE8\0\0\0\0"   # mov eax, H; call
        h = HANDLER + 0x10 * i - TEXT
        text[h:h + 10] = b"\xB8" + va(FUNCINFO + 0x20 * i) + b"\xE9\0\0\0\0"                    # mov eax, FI; jmp
        f = FUNCLET + 0x10 * i - TEXT
        text[f:f + 1] = b"\xC3"
        fi = FUNCINFO + 0x20 * i - RDATA
        rdata[fi:fi + 20] = struct.pack("<IIIII", 0x19930520, 1, BASE + UNWIND + 8 * i, 0, 0)
        u = UNWIND + 8 * i - RDATA
        rdata[u:u + 8] = struct.pack("<i", -1) + va(FUNCLET + 0x10 * i)
    # push __xc_z; push __xc_a; call _initterm, and the table: A1, X, A3
    text[0x2000 - TEXT:0x2000 - TEXT + 15] = b"\x68" + va(XC_Z) + b"\x68" + va(XC_A) + b"\xE8\0\0\0\0"
    data[0:0x14] = struct.pack("<I", 0) + va(0x1000) + va(0x1200) + va(0x1300) + struct.pack("<I", 0)
    rdata[VFT - RDATA:VFT - RDATA + 12] = va(0x1000) + va(0x1200) + va(0x1100)                 # A1, X, A2
    secs = [(".text", TEXT, bytes(text)), (".rdata", RDATA, bytes(rdata)), (".data", DATA, bytes(data))]
    pe = 0x40
    head = bytearray(0x400)
    head[0:2] = b"MZ"
    struct.pack_into("<I", head, 0x3C, pe)
    head[pe:pe + 4] = b"PE\0\0"
    struct.pack_into("<HH", head, pe + 4, 0x14C, len(secs))
    struct.pack_into("<H", head, pe + 20, 0xE0)
    struct.pack_into("<I", head, pe + 52, BASE)
    body, raw = b"", len(head)
    for k, (name, rva, blob) in enumerate(secs):
        at = pe + 24 + 0xE0 + 40 * k
        head[at:at + 8] = name.encode().ljust(8, b"\0")
        struct.pack_into("<IIII", head, at + 8, len(blob), rva, len(blob), raw + len(body))
        body += blob
    return bytes(head) + body


def code_row(rva, size, tu="", conf="", by="-", source="", evidence=""):
    return {"rva": f"0x{rva:08X}", "size": str(size), "kind": "code", "tu": tu, "confidence": conf,
            "by": by, "evidence": evidence, "source": source}


def map_rows(parents_approved=True):
    out = []
    for name, rva, tu, by in FUNCS:
        conf = ("approved" if parents_approved else "proposed") if tu else ""
        out.append(code_row(rva, 0x80, tu, conf, by if tu else "-", f"Code/{name}.cpp" if not tu else tu))
    for i in range(len(FUNCS)):
        out.append(code_row(HANDLER + 0x10 * i, 10, source="Code/gen_small/uw_gen_1.cpp"))
        out.append(code_row(FUNCLET + 0x10 * i, 1, source="Code/gen_small/uw_gen_1.cpp"))
    return sorted(out, key=lambda r: int(r["rva"], 16))


@pytest.fixture
def tree(tmp_path):
    (tmp_path / "reverse").mkdir()
    xrefs = ["rva\tsection\tsize_bound\twidths\tfloat\tkinds\tref_count\tcallers",
             f"0x{VFT:08X}\t.rdata\t12\t4\t0\taddress\t1\t0x00001004",
             f"0x{ITEMS:08X}\t.rdata\t4\t4\t0\tread\t1\t0x00001010",
             f"0x{ITEMS + 4:08X}\t.rdata\t4\t4\t0\tread\t1\t0x00001210",
             f"0x{ITEMS + 8:08X}\t.rdata\t4\t4\t0\tread\t1\t0x00001310"]
    (tmp_path / "reverse/data_xrefs.tsv").write_text("\n".join(xrefs) + "\n")
    names = ["name,export_rva,target_rva,target_size,source,status,notes"]
    for name, rva, tu, _ in FUNCS:
        names.append(f"{name},,0x{rva:08X},128,{tu or 'Code/X.cpp'},matched,")
    for i, (name, _, _, _) in enumerate(FUNCS):
        parent = "B2" if name == "B1" else name           # one ledger parent= the image disagrees with
        names.append(f"$L{i},,0x{FUNCLET + 0x10 * i:08X},1,Code/gen_small/uw_gen_1.cpp,matched,"
                     f"gen-funclet;parent={parent}")
    (tmp_path / "reverse/functions.csv").write_text("\n".join(names) + "\n")
    layout = tu_map.Layout(tmp_path)
    return layout, te.Retail(image())


def structures(tree, out=None):
    layout, img = tree
    return te.Structures(layout, out or map_rows(), img)


def replace_rva(blob, rva, value):
    """Change one synthetic image field without guessing its raw file offset."""
    for _, start, size, raw in te.Retail(blob).secs:
        if start <= rva and rva + len(value) <= start + size:
            blob[raw + rva - start:raw + rva - start + len(value)] = value
            return
    raise AssertionError(f"unmapped test address {rva:#x}")


def shared_image():
    blob = bytearray(image())
    replace_rva(blob, UNWIND + 8 + 4, va(FUNCLET))  # A1 and A2 share the first action
    return blob


def shared_structures(tree, out=None, blob=None):
    return te.Structures(tree[0], out or map_rows(), te.Retail(blob or shared_image()))


def test_shared_p_requires_all_explicit_approved_parents_and_records_every_witness(tree):
    out = map_rows()
    st = shared_structures(tree, out)
    assert FUNCLET not in st.parent  # the ordered-layout unique-parent view is unchanged
    assert st.shared_parents[FUNCLET] == frozenset(((0x1000, FUNCINFO), (0x1100, FUNCINFO + 0x20)))
    expected = ("code/a.cpp", "P=parents(0x00001000@FuncInfo0x00004100,0x00001100@FuncInfo0x00004120)")
    assert te.gather(out, st, {"P"})[FUNCLET]["P"] == expected
    got = {r["rva"]: r for r in te.apply(tree[0], out, {"P"}, st)}
    assert (got[f"0x{FUNCLET:08X}"]["tu"], got[f"0x{FUNCLET:08X}"]["confidence"]) == ("Code/A.cpp", "approved")
    assert te.P_GROUP_TOKEN not in got[f"0x{FUNCLET:08X}"]["evidence"].split()
    reverse = list(reversed(out))
    assert te.gather(reverse, shared_structures(tree, reverse), {"P"})[FUNCLET]["P"] == expected


@pytest.mark.parametrize("tu,confidence", [
    ("Code/B.cpp", "approved"), ("Code/A.cpp", "proposed"),
    ("Code/A.cpp", "displaced"), ("", ""), ("", "approved"),
])
def test_shared_p_vetoes_conflicting_or_unapproved_parent_even_with_p_groups(tree, monkeypatch, tu, confidence):
    monkeypatch.setattr(te, "P_GROUPS", True)
    out = [dict(r, tu=tu, confidence=confidence) if r["rva"] == "0x00001100" else r for r in map_rows()]
    st = shared_structures(tree, out)
    assert "P" not in te.gather(out, st, {"P"}).get(FUNCLET, {})
    got = {r["rva"]: r for r in te.apply(tree[0], out, {"P"}, st)}
    assert got[f"0x{FUNCLET:08X}"]["tu"] == ""


def test_shared_p_vetoes_a_missing_native_parent_row(tree):
    out = [r for r in map_rows() if r["rva"] != "0x00001100"]
    st = shared_structures(tree, out)
    assert any(parent is None for parent, _ in st.shared_parents[FUNCLET])
    assert "P" not in te.gather(out, st, {"P"}).get(FUNCLET, {})


def test_shared_p_does_not_use_a_parent_approved_during_this_apply(tree):
    out = [dict(r, tu="", confidence="", by="-") if r["rva"] == "0x00001100" else r for r in map_rows()]
    st = shared_structures(tree, out)
    got = {r["rva"]: r for r in te.apply(tree[0], out, {"E", "P"}, st)}
    assert got["0x00001100"]["confidence"] == "approved"  # E can place the parent first
    assert got[f"0x{FUNCLET:08X}"]["tu"] == ""  # consensus still needs explicit input approval


def test_shared_p_keeps_unknown_handler_owners_as_a_veto(tree):
    blob = shared_image()
    replace_rva(blob, 0x1A00, b"\xB8" + va(HANDLER + 0x10))  # reference outside every known body
    st = shared_structures(tree, blob=blob)
    assert FUNCLET in st.parent  # legacy inventory drops the ambiguous A2 handler
    assert any(parent is None for parent, _ in st.shared_parents[FUNCLET])
    assert "P" not in te.gather(map_rows(), st, {"P"}).get(FUNCLET, {})


def test_shared_p_keeps_an_unowned_handler_referencing_the_action_as_a_veto(tree):
    blob = shared_image()
    replace_rva(blob, 0x1100 + 1, va(HANDLER))  # A2 joins A1; its old handler now has no owner
    st = shared_structures(tree, blob=blob)
    assert (None, FUNCINFO + 0x20) in st.shared_parents[FUNCLET]
    assert "P" not in te.gather(map_rows(), st, {"P"}).get(FUNCLET, {})


def test_shared_p_can_use_all_known_owners_of_one_folded_handler(tree):
    blob = bytearray(image())
    replace_rva(blob, 0x1100 + 1, va(HANDLER))  # both approved A parents use A1's entire graph
    st = shared_structures(tree, blob=blob)
    assert st.shared_parents[FUNCLET] == frozenset(((0x1000, FUNCINFO), (0x1100, FUNCINFO)))
    assert te.gather(map_rows(), st, {"P"})[FUNCLET]["P"][0] == "code/a.cpp"


@pytest.mark.parametrize("field,value", [(FUNCINFO + 0x40 + 8, BASE + 0x9000),
                                          (FUNCINFO + 0x40 + 4, te.MAX_STATES + 1)])
def test_shared_p_abstains_when_a_native_action_map_cannot_be_read_completely(tree, field, value):
    blob = shared_image()
    replace_rva(blob, field, struct.pack("<I", value))
    st = shared_structures(tree, blob=blob)
    assert not st.parentage_complete
    assert "P" not in te.gather(map_rows(), st, {"P"}).get(FUNCLET, {})


@pytest.mark.parametrize("missing", ["try-map", "catch-array"])
def test_shared_p_requires_complete_native_catch_maps_too(tree, missing):
    blob = shared_image()
    trymap = RDATA + 0xA00
    replace_rva(blob, FUNCINFO + 0x40 + 12, struct.pack("<II", 1, BASE + (0x9000 if missing == "try-map" else trymap)))
    if missing == "catch-array":
        replace_rva(blob, trymap, struct.pack("<IIIII", 0, 0, 0, 1, BASE + 0x9000))
    st = shared_structures(tree, blob=blob)
    assert not st.parentage_complete
    assert "P" not in te.gather(map_rows(), st, {"P"}).get(FUNCLET, {})


def test_shared_p_accounts_for_native_catch_handler_references(tree):
    blob = bytearray(image())
    trymap, handlers = RDATA + 0xA00, RDATA + 0xA20
    replace_rva(blob, FUNCINFO + 0x20 + 12, struct.pack("<II", 1, BASE + trymap))
    replace_rva(blob, trymap, struct.pack("<IIIII", 0, 0, 0, 1, BASE + handlers))
    replace_rva(blob, handlers, struct.pack("<IIII", 0, 0, 0, BASE + FUNCLET))
    st = shared_structures(tree, blob=blob)
    assert st.shared_parents[FUNCLET] == frozenset(((0x1000, FUNCINFO), (0x1100, FUNCINFO + 0x20)))
    assert te.gather(map_rows(), st, {"P"})[FUNCLET]["P"][0] == "code/a.cpp"


def test_multiple_funcinfos_for_one_parent_preserve_unique_parent_behavior(tree):
    blob = shared_image()
    replace_rva(blob, 0x1100, b"\x90" * 5)
    replace_rva(blob, 0x1010, b"\xB8" + va(HANDLER + 0x10))
    st = shared_structures(tree, blob=blob)
    assert FUNCLET in st.parent and FUNCLET not in st.shared_parents
    assert te.gather(map_rows(), st, {"P"})[FUNCLET]["P"][0] == "code/a.cpp"


@pytest.mark.parametrize("veto", ["inside", "broken", "unrooted"])
def test_shared_p_preserves_span_and_anchoring_vetoes_without_group_rescue(tree, monkeypatch, veto):
    monkeypatch.setattr(te, "P_GROUPS", True)
    out = map_rows()
    st = shared_structures(tree, out)
    if veto == "inside":
        real = te.inside_other
        monkeypatch.setattr(te, "inside_other", lambda spans, rva, key: "code/b.cpp" if rva == FUNCLET else real(spans, rva, key))
    else:
        real = te.approvable
        def denied(rows):
            roots, broken, spans = real(rows)
            return (roots - {"code/a.cpp"}, broken, spans) if veto == "unrooted" else (roots, broken | {"code/a.cpp"}, spans)
        monkeypatch.setattr(te, "approvable", denied)
    got = {r["rva"]: r for r in te.apply(tree[0], out, {"P"}, st)}
    child = got[f"0x{FUNCLET:08X}"]
    assert child["confidence"] == "proposed"
    assert te.P_GROUP_TOKEN not in child["evidence"].split()


def test_shared_p_validation_scores_new_predictions_against_native_parent_membership(tree):
    st = shared_structures(tree)
    res = te.validate(tree[0], map_rows(), st)["P"]
    assert res["shared_predicted"] == res["shared_correct"] == 1
    path = tree[0].path("functions.csv")
    path.write_text(path.read_text().replace("gen-funclet;parent=A1\n", "gen-funclet;parent=B1\n"))
    res = te.validate(tree[0], map_rows(), st)["P"]
    assert res["shared_predicted"] == 1 and res["shared_correct"] == 0


def test_shared_p_validation_never_follows_an_ambiguous_intermediate_cleanup(tree):
    blob = shared_image()
    # X's graph is now referenced from A1, while A3's graph also names X's
    # action and has an unknown owner. The old filtered view sees only A1.
    replace_rva(blob, 0x1200, b"\x90" * 5)
    replace_rva(blob, 0x1010, b"\xB8" + va(HANDLER + 0x20))
    replace_rva(blob, UNWIND + 3 * 8 + 4, va(FUNCLET + 0x20))
    replace_rva(blob, 0x1A00, b"\xB8" + va(HANDLER + 0x30))
    st = shared_structures(tree, blob=blob)
    assert st.parent[FUNCLET + 0x20][0] == 0x1000
    assert FUNCLET + 0x20 in st.shared_parents
    path = tree[0].path("functions.csv")
    text = path.read_text().replace("gen-funclet;parent=X\n", "gen-funclet\n")
    path.write_text(text.replace("gen-funclet;parent=A1\n", "gen-funclet;parent=$L2\n"))
    result = te.validate(tree[0], map_rows(), st)["P"]
    assert result["shared_predicted"] == 1 and result["shared_correct"] == 0


def test_the_image_layouts_are_read(tree):
    st = structures(tree)
    assert {h: p for h, (p, _, _) in st.eh.items()} == {HANDLER + 0x10 * i: f[1] for i, f in enumerate(FUNCS)}
    assert st.parent[FUNCLET + 0x20] == (0x1200, FUNCINFO + 0x40)
    assert st.inits == [(XC_A + 4, 0x1000), (XC_A + 8, 0x1200), (XC_A + 12, 0x1300)]
    assert st.vfts == [(VFT, [0x1000, 0x1200, 0x1100])]
    assert VFT not in st.items and st.items[ITEMS + 4] == [0x1200]


def test_every_ordered_signal_brackets_the_unplaced_row_inside_one_tu(tree):
    got = te.gather(map_rows(), structures(tree))
    assert {s: tu for s, (tu, _) in got[0x1200].items()} == dict.fromkeys("EIVTR", "code/a.cpp")
    assert got[0x1200]["E"][1].startswith("E=0x")                     # the ref names the bracket
    assert te.choose(got[0x1200])[0] == "E"


def test_a_tu_boundary_and_leave_one_out_predict_nothing(tree):
    out = map_rows()
    anchor, _ = te.anchors_of(out)
    lay = te.layouts(structures(tree), anchor)["E"]
    assert lay.predict(0x1400) is None                                # B1: A3 below, B2 above
    assert lay.predict(0x1100)[0] == "code/a.cpp"                     # A2: A1 and A3, never itself
    solo = {0x1000: "code/a.cpp"}                                     # only A1 anchored
    assert te.layouts(structures(tree), solo)["E"].predict(0x1000) is None


def test_signals_that_disagree_place_nothing():
    assert te.choose({"E": ("code/a.cpp", "e"), "R": ("code/b.cpp", "r")}) is None
    assert te.choose({"E": ("code/a.cpp", "e"), "R": ("code/a.cpp", "r")}) == ("E", ("code/a.cpp", "e"))


def test_nothing_changes_until_a_signal_is_promoted(tree, monkeypatch):
    layout, _ = tree
    out = map_rows()
    monkeypatch.setattr(te, "PROMOTED", frozenset())
    monkeypatch.setattr(te, "Structures", lambda *a, **k: pytest.fail("the image was read"))
    assert te.apply(layout, out) is out


def test_a_funclet_follows_its_parents_tu_and_confidence(tree):
    layout, _ = tree
    st = structures(tree)
    new = {r["rva"]: r for r in te.apply(layout, map_rows(), {"E", "P"}, st)}
    x = new["0x00001200"]
    assert (x["tu"], x["confidence"], x["by"]) == ("Code/A.cpp", "approved", "E")
    assert (new[f"0x{FUNCLET:08X}"]["tu"], new[f"0x{FUNCLET:08X}"]["confidence"]) == ("Code/A.cpp", "approved")
    assert new[f"0x{FUNCLET + 0x20:08X}"]["confidence"] == "approved"   # X's funclet, after X


def test_p_groups_approve_a_funclet_of_an_unapproved_parent_with_its_token(tree, monkeypatch):
    layout, _ = tree
    monkeypatch.setattr(te, "P_GROUPS", False)
    weak = te.apply(layout, map_rows(parents_approved=False), {"P"}, structures(tree, map_rows(False)))
    assert {r["confidence"] for r in weak if r["by"] == "P"} == {"proposed"}      # the gate off: proposed
    monkeypatch.setattr(te, "P_GROUPS", True)
    grouped = te.apply(layout, map_rows(parents_approved=False), {"P"}, structures(tree, map_rows(False)))
    p_rows = [r for r in grouped if r["by"] == "P"]
    assert p_rows and {r["confidence"] for r in p_rows} == {"approved"}
    for r in p_rows:                     # the parent's TU, its name unproven (no anchor approves it)
        tokens = r["evidence"].split()
        assert te.P_GROUP_TOKEN in tokens and tu_map.PROV_TOKEN in tokens and r["tu"] in ("Code/A.cpp", "Code/B.cpp")
    anchored = {r["rva"]: r for r in te.apply(layout, map_rows(), {"P"}, structures(tree))}
    assert all(te.P_GROUP_TOKEN not in r["evidence"] for r in anchored.values())   # parents approved: no token


def test_p_groups_leave_an_approved_parents_funclet_to_the_usual_checks(tree, monkeypatch):
    """Near miss: the parent is approved but its funclet sits inside another approved TU's span."""
    layout, _ = tree
    monkeypatch.setattr(te, "P_GROUPS", True)
    real = te.inside_other
    monkeypatch.setattr(te, "inside_other",
                        lambda spans, rva, key: "code/c.cpp" if rva == FUNCLET else real(spans, rva, key))
    got = {r["rva"]: r for r in te.apply(layout, map_rows(), {"P"}, structures(tree))}
    funclet = got[f"0x{FUNCLET:08X}"]
    assert funclet["confidence"] == "proposed" and te.P_GROUP_TOKEN not in funclet["evidence"].split()


def test_p_groups_place_nothing_a_parent_without_a_tu_does_not(tree, monkeypatch):
    """Near miss: a funclet whose parent the map gives no TU (and no signal places) gets none."""
    layout, _ = tree
    monkeypatch.setattr(te, "P_GROUPS", True)
    out = [dict(r, tu="", confidence="", by="-") if r["rva"] == "0x00001000" else r for r in map_rows(False)]
    got = {r["rva"]: r for r in te.apply(layout, out, {"P"}, structures(tree, out))}
    assert got[f"0x{FUNCLET:08X}"]["tu"] == "" and got[f"0x{FUNCLET:08X}"]["confidence"] == ""


def t_layout(tree, out):
    st = structures(tree, out)
    return te.layouts(st, te.anchors_of(out)[0])["T"]


def test_t_brackets_a_row_between_one_tus_hard_anchors(tree):
    lay = t_layout(tree, map_rows())
    tu, ref = lay.predict(0x1200)                                     # X: A2 (Z) below, A3 (Z) above
    assert tu == "code/a.cpp" and ref == "T=0x00001100..0x00001300@0x00001100,0x00001300"
    assert lay.predict(0x1400) is None                                # B1: A3 below, B2 above


def test_t_never_anchors_on_a_naming_hint_or_class_site(tree):
    """Near miss: S (a class site) and N/U place header inlines of a class beside another TU's
    code (WWMath aabox.cpp inlines inside gridcull.cpp); T takes F/Z/L anchors only."""
    for by in "SNU":
        out = [dict(r, by=by) if r["rva"] in ("0x00001100", "0x00001300") else r for r in map_rows()]
        assert t_layout(tree, out).predict(0x1200) is None, by
        assert te.layouts(structures(tree, out), te.anchors_of(out)[0])["V"].predict(0x1200), by   # V still may


def test_t_is_vetoed_by_a_row_firmly_naming_another_tu_between_its_anchors(tree):
    extra = code_row(0x1280, 0x10, "Code/B.cpp", "proposed", "Z", "Code/B.cpp", "Z=Code/B.cpp")
    assert t_layout(tree, map_rows() + [extra]).predict(0x1200) is None
    hard_x = code_row(0x1280, 0x10, "", "", "-", "Code/Y.cpp", "F=Code/B.cpp")          # no TU, its own F names B
    assert t_layout(tree, map_rows() + [hard_x]).predict(0x1200) is None
    soft = code_row(0x1280, 0x10, "Code/Guess.cpp", "proposed", "N", "Code/G.cpp", "N=Code/Guess.cpp")
    assert t_layout(tree, map_rows() + [soft]).predict(0x1200)[0] == "code/a.cpp"      # a guess does not veto


def test_t_is_promoted_and_approves_inside_an_anchored_tu(tree):
    layout, _ = tree
    assert "T" in te.PROMOTED
    out = map_rows()
    new = {r["rva"]: r for r in te.apply(layout, out, {"T"}, structures(tree, out))}
    x = new["0x00001200"]
    assert (x["tu"], x["confidence"], x["by"]) == ("Code/A.cpp", "approved", "T")
    assert "T=0x00001100..0x00001300" in x["evidence"]


def test_a_row_inside_another_approved_tus_span_is_only_proposed(tree):
    out = map_rows() + [code_row(0x1480, 0x10, source="Code/Y.cpp")]
    roots, broken, spans = te.approvable(out)
    assert te.inside_other(spans, 0x1480, "code/a.cpp") == "code/b.cpp"
    assert te.inside_other(spans, 0x1200, "code/a.cpp") is None


def test_validation_scores_leave_one_out_and_parent_notes(tree):
    layout, _ = tree
    res = te.validate(layout, map_rows(), structures(tree))
    assert res["E"]["test"] == 5 and res["E"]["precision"] == 1.0 and 0 < res["E"]["recall"] < 1
    assert res["P"]["predicted"] == 6 and res["P"]["correct"] == 5 and not res["P"]["passes"]


def test_a_promoted_signal_below_the_gate_fails_validate(tree, monkeypatch, capsys):
    layout, _ = tree
    st = structures(tree)
    monkeypatch.setattr(te, "PROMOTED", frozenset("P"))
    assert te.report(te.validate(layout, map_rows(), st), layout, map_rows(), st) == 1
    assert "below the 99% gate" in capsys.readouterr().err


def test_evidence_rows_are_deterministic_and_re_checked(tree, tmp_path, monkeypatch):
    monkeypatch.setattr(te, "PROMOTED", frozenset())   # every row a proposal
    layout, _ = tree
    st = structures(tree)
    rows = te.evidence_rows(layout, map_rows(), st)
    assert te.render(rows) == te.render(te.evidence_rows(layout, map_rows(), structures(tree)))
    assert {r["signal"] for r in rows if r["rva"] == "0x00001200"} == set("EIVTR")
    assert all(r["status"] == "proposal" for r in rows)
    path = tmp_path / "ev.csv"
    path.write_text(te.render(rows))
    assert te.check(layout, map_rows(), path, st) == []
    path.write_text(te.render(rows).replace("Code/A.cpp", "Code/B.cpp", 1))   # a hand edit
    assert len(te.check(layout, map_rows(), path, st)) == 1


def test_the_lane_serves_unplaced_sources_with_their_evidence(tree, monkeypatch, tmp_path):
    monkeypatch.setattr(te, "PROMOTED", frozenset())   # the lane serves proposals
    out = map_rows()
    runs, bare = te.runs(out, structures(tree))
    assert bare == 2 and len(runs) == 1             # X.cpp and uw_gen_1.cpp; uw_gen is gen_uw's, never served
    (run,) = runs
    assert run["sources"] == ["Code/X.cpp"] and run["below"]["rva"] == "0x00001100"
    assert run["gap"] == 0x200 and run["signals"]["E"] == {"Code/A.cpp": 1}

    import repair_queue as rq
    import tu_skeleton
    root = tree[0].root
    (root / rq.TU_MAP).write_text("")
    (root / "Code").mkdir()
    (root / "Code/X.cpp").write_text("")
    monkeypatch.setattr(rq, "ROOT", root)
    monkeypatch.setattr(tu_skeleton, "map_rows", lambda: out)
    real, img = te.Structures, tree[1]
    monkeypatch.setattr(te, "Structures", lambda layout, o: real(layout, o, img))
    (root / "baselines/bfme2/workshop-vanilla-1.06/files").mkdir(parents=True)
    tu_map.Layout(root).image.write_bytes(b"")
    items, note = rq.tu_evidence_items()
    (item,) = items
    assert item["tier"] == "tu-evidence" and item["claim"] == ["file:Code/X.cpp"] and item["count"] == 1
    assert "E Code/A.cpp x1 (proposal)" in item["why"] and "tu_evidence.py --source Code/X.cpp" in item["start"]
    assert "1 of 2 source(s)" in note


def test_tu_map_build_passes_its_rows_through_the_promoted_signals(monkeypatch, tmp_path):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text("name,export_rva,target_rva,target_size,source,status,notes\n")
    seen = []
    monkeypatch.setattr(te, "apply", lambda layout, out: seen.append(out) or out)
    tu_map.build(tu_map.Layout(tmp_path, zh=tmp_path / "zh"))
    assert seen == [[]]
