"""The EH verifier compares what the function gate never reads: `.text$x` / `.xdata$x`.

The fixture is the case research/16 found 405 times. A function whose static
guard needs an unwind funclet compiles byte-true in `.text`, while its funclet
says `and eax,-2` and retail, built /G7, says `and al,0FEh`. The function gate
is green on it; this check is not.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eh_verify


BASE = 0x400000
FUNC, THUNK, FUNCINFO = 0x1000, 0x2000, 0x3000
GUARD = 0x5000
OURS = bytes.fromhex("83e0fe")      # and eax,-2
G7 = bytes.fromhex("24fe90")         # and al,0FEh (padded to the same length)


def coff(funclet_and):
    """A one-function object: f -> handler thunk (.text$x) -> FuncInfo (.xdata$x)."""
    func = bytes.fromhex("b8") + b"\0" * 4 + bytes.fromhex("c3")
    thunk = bytes.fromhex("b8") + b"\0" * 4 + bytes.fromhex("e9") + b"\0" * 4
    funclet = bytes.fromhex("a1") + b"\0" * 4 + funclet_and + bytes.fromhex("a3") + b"\0" * 4 \
        + bytes.fromhex("c3")
    textx = thunk + funclet
    # FuncInfo: magic, maxState 1, pUnwindMap -> +0x14, nTry 0, pTry 0; unwind: -1, funclet
    xdata = struct.pack("<IIIII", 0x19930520, 1, 0x14, 0, 0) + struct.pack("<iI", -1, 10)
    # symbols: 0 .text$mn(+aux) 2 .text$x(+aux) 4 .xdata$x(+aux) 6 _f 7 handler 8 _guard
    sections = [
        (".text$mn", func, [(1, 2, 6)]),
        (".text$x", textx, [(1, 4, 6), (6, 7, 0x14), (11, 8, 6), (19, 8, 6)]),
        (".xdata$x", xdata, [(8, 4, 6), (24, 2, 6)]),
    ]
    header, raw, offset = b"", b"", 20 + 40 * len(sections)
    layout = []
    for name, data, relocs in sections:
        layout.append((offset, offset + len(data)))
        offset += len(data) + 10 * len(relocs)
    for (name, data, relocs), (data_at, reloc_at) in zip(sections, layout):
        header += name.encode().ljust(8, b"\0") if len(name) <= 8 else b""
        header += struct.pack("<IIIIIIHHI", 0, 0, len(data), data_at, reloc_at, 0,
                              len(relocs), 0, 0x60501020 if name != ".xdata$x" else 0x40301040)
        raw += data + b"".join(struct.pack("<IIH", *r) for r in relocs)
    symtab = 20 + len(header) + len(raw)
    symbols = b""
    for number, (name, data, relocs) in enumerate(sections, 1):
        symbols += name.encode()[:8].ljust(8, b"\0") + struct.pack("<IhHBB", 0, number, 0, 3, 1)
        symbols += struct.pack("<IHHIHB", len(data), len(relocs), 0, 0, 1 if number > 1 else 0,
                               5 if number > 1 else 2) + b"\0" * 3
    symbols += b"_f".ljust(8, b"\0") + struct.pack("<IhHBB", 0, 1, 0x20, 2, 0)
    symbols += b"\0\0\0\0" + struct.pack("<I", 4) + struct.pack("<IhHBB", 0, 0, 0x20, 2, 0)
    symbols += b"_guard".ljust(8, b"\0") + struct.pack("<IhHBB", 0, 0, 0, 2, 0)
    strings = b"___CxxFrameHandler\0"
    head = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, symtab, 9, 0, 0)
    return head + header + raw + symbols + struct.pack("<I", 4 + len(strings)) + strings


class Retail(eh_verify.Image):
    def __init__(self, funclet_and, eh_frame=True):
        image = bytearray(0x6000)
        self.base, self.size = BASE, len(image)
        image[FUNC:FUNC + 6] = (bytes.fromhex("b8") if eh_frame else bytes.fromhex("90")) \
            + struct.pack("<I", BASE + THUNK) + bytes.fromhex("c3")
        image[THUNK:THUNK + 10] = bytes.fromhex("b8") + struct.pack("<I", BASE + FUNCINFO) \
            + bytes.fromhex("e9") + struct.pack("<i", 0x100)
        image[THUNK + 10:THUNK + 24] = bytes.fromhex("a1") + struct.pack("<I", BASE + GUARD) \
            + funclet_and + bytes.fromhex("a3") + struct.pack("<I", BASE + GUARD) + bytes.fromhex("c3")
        image[FUNCINFO:FUNCINFO + 28] = struct.pack("<IIIII", 0x19930520, 1, BASE + FUNCINFO + 0x14, 0, 0) \
            + struct.pack("<iI", -1, BASE + THUNK + 10)
        self.bytes = bytes(image)


def obj(tmp_path, funclet_and):
    path = tmp_path / "t.obj"
    path.write_bytes(coff(funclet_and))
    return eh_verify.Obj(path)


def test_identical_eh_data_is_exact(tmp_path):
    assert eh_verify.verify_row(Retail(OURS), obj(tmp_path, OURS), "_f", FUNC) == ("EXACT", "")


def test_guard_funclet_without_g7_fails(tmp_path):
    verdict, detail = eh_verify.verify_row(Retail(G7), obj(tmp_path, OURS), "_f", FUNC)
    assert verdict == "bytes_differ"
    assert ".text$x guard-and" in detail


def test_g7_object_matches_g7_retail(tmp_path):
    assert eh_verify.verify_row(Retail(G7), obj(tmp_path, G7), "_f", FUNC)[0] == "EXACT"


def test_wrong_max_state_fails(tmp_path):
    data = bytearray(coff(OURS))
    at = data.index(struct.pack("<II", 0x19930520, 1))
    data[at + 4] = 2
    path = tmp_path / "m.obj"
    path.write_bytes(bytes(data))
    verdict, detail = eh_verify.verify_row(Retail(OURS), eh_verify.Obj(path), "_f", FUNC)
    assert verdict == "bytes_differ" and ".xdata$x" in detail


def test_eh_data_retail_does_not_have(tmp_path):
    assert eh_verify.verify_row(Retail(OURS, eh_frame=False), obj(tmp_path, OURS), "_f", FUNC)[0] \
        == "obj_only"


def test_baseline_round_trip(tmp_path, monkeypatch):
    monkeypatch.setattr(eh_verify, "BASELINE", tmp_path / "eh_baseline.csv")
    eh_verify.write_baseline({("?b", "0x2"): "obj_only", ("?a", "0x1"): "bytes_differ"})
    assert eh_verify.load_baseline() == {("?a", "0x1"): "bytes_differ", ("?b", "0x2"): "obj_only"}


def test_frame_whose_fs_load_precedes_the_thunk_push(tmp_path):
    # /O2 schedules `mov eax,fs:[0]` between `push -1` and `push thunk`
    # (MeshMatDescClass::Store_Pass0_State, 0x15D5B0); the frame is still retail's.
    retail = Retail(OURS)
    image = bytearray(retail.bytes)
    image[FUNC:FUNC + 14] = bytes.fromhex("6aff64a100000000") + bytes.fromhex("68") \
        + struct.pack("<I", BASE + THUNK) + bytes.fromhex("50")
    retail.bytes = bytes(image)
    assert retail.frame_funcinfo(FUNC) == (THUNK, FUNCINFO)
    image[FUNC + 9:FUNC + 13] = struct.pack("<I", BASE + GUARD)    # not a handler thunk
    retail.bytes = bytes(image)
    assert retail.frame_funcinfo(FUNC) is None


def test_verified_eh_graph_locates_local_funclet_symbols(tmp_path):
    compiled = obj(tmp_path, OURS)
    compiled.symbols[99] = {"name": "$L123", "section": 2, "value": 10, "storage": 3}
    assert eh_verify.verified_funclet_locations(Retail(OURS), compiled, "_f", FUNC) == {
        "$L123": THUNK + 10}


def test_nonmatching_eh_graph_supplies_no_funclet_identity(tmp_path):
    compiled = obj(tmp_path, OURS)
    compiled.symbols[99] = {"name": "$L123", "section": 2, "value": 10, "storage": 3}
    assert eh_verify.verified_funclet_locations(Retail(G7), compiled, "_f", FUNC) == {}


def test_missing_parent_supplies_no_funclet_identity(tmp_path):
    assert eh_verify.verified_funclet_locations(Retail(OURS), obj(tmp_path, OURS), "absent", FUNC) == {}


def scheduled_stack_frame(retail, load=b"\x8b\x54\x24\x14", install=True):
    image = bytearray(retail.bytes)
    prolog = bytes.fromhex("6aff64a100000000") + load + b"\x68" \
        + struct.pack("<I", BASE + THUNK) + bytes.fromhex("5064892500000000")
    if not install:
        prolog = prolog[:-7] + b"\x90" * 7
    image[FUNC:FUNC + len(prolog)] = prolog
    retail.bytes = bytes(image)
    return retail


def test_stack_load_scheduled_before_handler_push():
    retail = scheduled_stack_frame(Retail(OURS))
    assert retail.frame_funcinfo(FUNC) == (THUNK, FUNCINFO)


def test_scheduled_frame_with_bad_handler_is_rejected():
    retail = scheduled_stack_frame(Retail(OURS))
    image = bytearray(retail.bytes)
    image[FUNC + 13:FUNC + 17] = struct.pack("<I", BASE + GUARD)
    retail.bytes = bytes(image)
    assert retail.frame_funcinfo(FUNC) is None


def test_scheduled_frame_requires_fs_installation():
    assert scheduled_stack_frame(Retail(OURS), install=False).frame_funcinfo(FUNC) is None


def test_scheduled_load_cannot_clobber_fs_value_or_stack():
    for load in (bytes.fromhex("8b442414"), bytes.fromhex("8b642414"),
                 bytes.fromhex("e8542414")):
        assert scheduled_stack_frame(Retail(OURS), load=load).frame_funcinfo(FUNC) is None


def test_scheduled_frame_keeps_eh_bytes_check(tmp_path):
    retail = scheduled_stack_frame(Retail(OURS))
    # Move the fixture's handler relocation to the scheduled push.
    symbol_obj = obj(tmp_path, OURS)
    frame = bytearray(retail.bytes[FUNC:FUNC + 25])
    frame[13:17] = bytes(4)
    symbol_obj.sections[0]["data"] = bytes(frame)
    symbol_obj.sections[0]["relocs"] = [(13, 2, 6)]
    assert eh_verify.verify_row(retail, symbol_obj, "_f", FUNC) == ("EXACT", "")
    changed = bytearray(symbol_obj.sections[2]["data"])
    changed[4] = 2
    symbol_obj.sections[2]["data"] = bytes(changed)
    assert eh_verify.verify_row(retail, symbol_obj, "_f", FUNC)[0] == "bytes_differ"


def test_scheduled_frame_requires_funcinfo_magic():
    retail = scheduled_stack_frame(Retail(OURS))
    image = bytearray(retail.bytes)
    image[FUNCINFO:FUNCINFO + 4] = bytes(4)
    retail.bytes = bytes(image)
    assert retail.frame_funcinfo(FUNC) is None
