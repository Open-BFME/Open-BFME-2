"""tools/wb_source_paths.py: the extractor cuts a path out of its printable run and strips
binary-adjacent prefixes (flagging an unaligned cut), keeps message context, reads
UTF-16LE; normalization strips each build root and names the producer; the triage
builder serves only non-editor paths the map has no TU for, with every file a paired
WB body pushes, owners, map confidence and same-basename alternatives."""
import csv
import io
import json
import lzma
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import wb_source_paths as wsp  # noqa: E402


def test_normalize_strips_each_build_root_and_names_the_producer():
    assert wsp.normalize(r"C:\Projects\bfme2\Code\GameEngine\Source\Common\crc.cpp") == (
        "Code/GameEngine/Source/Common/crc.cpp", "strip-root:C:\\Projects\\bfme2\\", "bfme2-code")
    assert wsp.normalize(r"C:\projects\bfme2patch103\bfme2\Code\A\B.cpp")[0::2] == ("Code/A/B.cpp", "bfme2-code")
    assert wsp.normalize(r"C:\Projects\bfme2\Code\Tools\WorldBuilder\src\MainFrm.cpp")[2] == "tools-worldbuilder"
    assert wsp.normalize(r"c:\dev\lotr\bfme2\production\code\Libraries\Source\Juice\J.cpp")[0::2] == (
        "Code/Libraries/Source/Juice/J.cpp", "juice")
    assert wsp.normalize(r"\views\feslbuild_main\jabba\fesl\source\hubsingle.cpp") == (
        "views/feslbuild_main/jabba/fesl/source/hubsingle.cpp", "fesl-view", "fesl")
    assert wsp.normalize(r"c:\projects\bfme2\code\libraries\include\rts\../../source/xfer/xfer.cpp")[0] == (
        "Code/libraries/source/xfer/xfer.cpp")
    assert wsp.normalize(r"\8471-.C")[2] == "other"


def test_cut_strips_binary_adjacent_prefixes_and_flags_an_unaligned_cut():
    # "F" before an aligned "\views..." is an adjacent byte, stripped and flagged.
    (path, off, flags), = wsp.cut(r"F\views\feslbuild_main\jabba\fesl\source\hubsingle.cpp", 0x1BE260B)
    assert path.startswith("\\views\\") and off == 0x1BE260C and flags == "prefix=F"
    (path, off, flags), = wsp.cut(r"CC:\Projects\bfme2\Code\X.cpp", 0x1B14A77)
    assert path == r"C:\Projects\bfme2\Code\X.cpp" and flags == "prefix=C"
    (_, _, flags), = wsp.cut(r"4+(ymjd]\8471-.C:7PIFWQK}yy", 0x1E78201)
    assert "unaligned" in flags.split(";")
    (path, _, flags), = wsp.cut(r"Invalid call: C:\Projects\bfme2\Code\R.cpp(194) : ", 0x100)
    assert path.endswith("R.cpp") and flags == "message;suffix=(194) : "
    (path, off, flags), = wsp.cut(r"C:\Projects\bfme2\Code\Y.c", 0x40)
    assert off == 0x40 and flags == "" and path.endswith("Y.c")
    assert wsp.cut(r"C:\Projects\bfme2\Code\Y.cfg", 0) == []


def test_extract_reads_ascii_and_utf16_runs_in_offset_order():
    data = (b"\x00" * 4 + b"C:\\Projects\\bfme2\\Code\\A.cpp\x00\x00\x00\x00"
            + "\\views\\feslbuild_main\\B.cpp".encode("utf-16le") + b"\x00\x00")
    found = wsp.extract(data)
    assert [(f[1], f[2], f[4]) for f in found] == [
        (4, "ascii", "C:\\Projects\\bfme2\\Code\\A.cpp"), (36, "utf-16le", "\\views\\feslbuild_main\\B.cpp")]


def _inv(binary, path, flags="", in_gd="no"):
    normalized, rule, producer = wsp.normalize(path)
    return {"binary": binary, "normalized": normalized, "producer_root": producer, "path": path,
            "present_in_game_dat": in_gd, "flags": flags}


def _map(rva, size, tu, confidence, source):
    return {"rva": f"0x{rva:08X}", "size": str(size), "kind": "code", "tu": tu, "confidence": confidence,
            "by": "F", "evidence": "", "source": source}


def test_triage_serves_non_editor_paths_without_a_tu_with_every_pushed_file():
    root = r"C:\Projects\bfme2\Code"
    inventory = [
        _inv("worldbuilder.exe", root + r"\Common\FCurve.cpp"),
        _inv("worldbuilder.exe", root + r"\Common\Mapped.cpp"),                 # the map has this TU
        _inv("worldbuilder.exe", root + r"\Tools\WorldBuilder\src\Tool.cpp"),   # editor: never served
        _inv("worldbuilder.exe", root + r"\Common\Second.cpp", in_gd="yes"),
        _inv("worldbuilder.exe", r"\8471-.C", flags="prefix=x;unaligned"),     # ambiguous cut: no lead
        _inv("game.dat", root + r"\Common\GameOnly.cpp", in_gd="yes"),          # target fact, not a WB lead
    ]
    rows = [_map(0x1000, 0x10, "Code/Common/Mapped.cpp", "approved", "Code/Common/Mapped.cpp"),
            _map(0x2000, 0x20, "", "", "Code/Common/Rva2000.cpp"),
            _map(0x3000, 0x10, "Code/Common/System/FCurve.cpp", "proposed", "Code/Common/System/FCurve.cpp")]
    lower = lambda p: wsp.normalize(p)[0].lower()  # noqa: E731
    body_files = {0x500000: [lower(root + r"\Common\Mapped.cpp"), lower(root + r"\Common\FCurve.cpp"),
                             lower(root + r"\Common\Second.cpp")]}
    pairs = {0x2004: 0x500000}
    leads = {0x2004: {"wb_name": "FCurve::eval", "score": "4.0"}}
    out = wsp.triage(inventory, rows, body_files, pairs, leads, {0x2004: ["?eval@FCurve@@QAEXXZ"]})
    assert [r["path"] for r in out] == ["Code/Common/FCurve.cpp", "Code/Common/Second.cpp"]
    fcurve, second = out
    # not only the body's first file: both later files carry the same candidate
    assert fcurve["candidates"] == second["candidates"] == [{
        "rva": "0x00002004", "wb_va": "0x00500000", "wb_name": "FCurve::eval", "score": "4.0",
        "owner": "?eval@FCurve@@QAEXXZ", "source": "Code/Common/Rva2000.cpp", "tu": "", "confidence": ""}]
    assert fcurve["alternatives"] == [{"tu": "Code/Common/System/FCurve.cpp", "rows": {"proposed": 1}}]
    assert not fcurve["in_game_dat"] and second["in_game_dat"] and second["alternatives"] == []


def test_triage_items_say_lead_not_proof_and_skip_without_inputs(tmp_path, monkeypatch):
    items, note = wsp.triage_items([], root=tmp_path)
    assert items == [] and "absent" in note and "skipped" not in note
    (tmp_path / "reverse/wb").mkdir(parents=True)
    path = r"C:\Projects\bfme2\Code\Common\FCurve.cpp"
    rows = [_inv("worldbuilder.exe", path)]
    for r in rows:
        r.update({"binary_sha256": "0", "offset": "0x0", "path_offset": "0x0", "encoding": "ascii", "raw": path,
                  "rule": "x"})
    (tmp_path / wsp.OUT).write_text(wsp.render(rows))
    (tmp_path / wsp.LEADS).write_text("target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
                                      "0x00002004,,UNROWED,FCurve::eval,,4.0,callgraph\n")
    (tmp_path / wsp.FUNCTIONS).write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                                          "Fn,,0x00002004,4,Code/Common/Rva2000.cpp,matched,\n")
    with lzma.open(tmp_path / wsp.WB_FUNCTIONS, "wt") as fh:
        fh.write(json.dumps({"va": 0x500000, "files": [path.lower()]}) + "\n")
    with lzma.open(tmp_path / wsp.WB_MATCHES, "wt") as fh:
        fh.write(json.dumps({"gd_va": 0x402004, "wb_va": 0x500000}) + "\n")
    items, note = wsp.triage_items([_map(0x2000, 0x20, "", "", "Code/Common/Rva2000.cpp")], root=tmp_path)
    (item,) = items
    # the claim fences every candidate source and RVA, not only the proposed path
    assert item["tier"] == "tu-evidence" and item["check"] == "wb-path" and item["claim"] == [
        "file:Code/Common/FCurve.cpp", "file:Code/Common/Rva2000.cpp", "0x00002004"]
    assert item["start"].startswith("investigate; this is a lead, not proof; never create an empty TU.")
    assert "0x00002004 WB FCurve::eval" in item["why"] and "owner Fn" in item["why"]
    assert item["target_rva"] == "0x00002004" and "1 with paired game RVAs" in note


def test_claim_fences_a_busy_candidate_beyond_the_first(tmp_path, monkeypatch):
    """A seat busy in a later candidate's source (or on its RVA) must keep the lead from
    being served: the picker fenced only the proposed path and the first RVA."""
    import claims
    import next_work
    for p in (wsp.OUT, wsp.LEADS, wsp.WB_FUNCTIONS, wsp.WB_MATCHES, wsp.FUNCTIONS):
        (tmp_path / p).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / p).touch()
    cand = lambda rva, src: {"rva": rva, "wb_va": "0x00500000", "wb_name": "A::f", "score": "4.0",  # noqa: E731
                             "owner": "", "source": src, "tu": "", "confidence": ""}
    record = {"path": "Code/Common/AreaPolygon.cpp", "producer_root": "bfme2-code", "in_game_dat": False,
              "raw": [], "alternatives": [],
              "candidates": [cand("0x00001000", "Code/Common/AreaPolygon_first.cpp"),
                             cand("0x00002000", "Code/Common/AreaPolygonBase_setPoint.cpp"),
                             cand("0x00003000", "")]}
    for name, value in (("_leads", {}), ("wb_pairs", {}), ("read", []), ("wb_body_files", {}),
                        ("_ledger_names", {})):
        monkeypatch.setattr(wsp, name, lambda *a, _v=value, **k: _v)
    monkeypatch.setattr(wsp, "triage", lambda *a, **k: [record])
    (item,) = wsp.triage_items([], root=tmp_path)[0]
    keys = next_work.claim_keys(item)
    assert claims.file_key("Code/Common/AreaPolygonBase_setPoint.cpp") in keys
    assert {0x2000, 0x3000} <= keys                     # an unrowed candidate is fenced by its RVA
    assert next_work.claim_targets(item)[0] == "file:Code/Common/AreaPolygon.cpp"


def test_render_is_deterministic_csv():
    rows = [dict.fromkeys(wsp.FIELDS, "v")]
    text = wsp.render(rows)
    assert text == wsp.render(rows) and next(csv.DictReader(io.StringIO(text)))["flags"] == "v"
