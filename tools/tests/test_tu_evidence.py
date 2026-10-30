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
