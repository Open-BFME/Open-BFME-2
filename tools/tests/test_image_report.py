"""The retail comparison's verdicts: a masked relocation is not a difference, a short copy counts."""
import collections
import struct
import sys
import types
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import image_report as ir


def test_data_verdict_masks_relocations_and_names_zeroed_data():
    assert ir.data_verdict(b"\x01\x00\x00\x00", b"\x01\x00\x00\x00", set()) == "same"
    assert ir.data_verdict(b"\x00\x00\x00\x00", b"\x10\x20\x30\x40", {0, 1, 2, 3}) == "same"
    assert ir.data_verdict(b"\x00\x00\x00\x00", b"\x10\x00\x00\x00", set()) == "ours_zero_retail_not"
    assert ir.data_verdict(b"\x44\x00", b"\x5c\x00", set()) == "contents_differ"


def test_constructed_names_reads_placement_new_and_cast_and_construct():
    texts = ["new (&g_Placed) Filter;", "( (Widget *)&g_Cast )->Widget::Widget( 1 );", "((Widget *)&g_Called)->render();"]
    assert ir.constructed_names(texts) == {"g_Placed", "g_Cast"}


def test_undersized_needs_a_constructed_name_smaller_than_its_gap():
    constructed = {"g_Placed"}
    assert ir.undersized({"?g_Placed@@3IA"}, 52, 4, constructed)
    assert not ir.undersized({"?g_Placed@@3PAIA"}, 52, 52, constructed)
    assert not ir.undersized({"?g_Other@@3IA"}, 52, 4, constructed)


def test_vtable_verdict_lets_the_shortest_copy_decide():
    assert ir.vtable_verdict(4, [16, 16]) == "same_length"
    assert ir.vtable_verdict(4, [4, 16]) == "ours_shorter"
    assert ir.vtable_verdict(4, [20, 16]) == "ours_longer"


def test_pointer_conflicts_compare_targets_the_ledger_knows():
    class Image:
        base = 0x400000

        def read(self, rva, size):
            if size == 4:
                return (0x400000 + 0x1000 + rva).to_bytes(4, "little")
            return {0x1010: b"same\0", 0x8000: b"same\0", 0x1014: b"this\0", 0x8004: b"that\0"}.get(rva, b"\0")

    class Found:
        pointers = [(0, "_right", 0), (4, "_wrong", 0), (8, "_unknown", 0), (64, "_past_the_extent", 0), (12, "_array", 8),
                    (16, "??_C@_a", 0), (20, "??_C@_b", 0)]

    known = {"_right": {0x1000}, "_wrong": {0x9000}, "_array": {0x1004}, "??_C@_a": {0x8000}, "??_C@_b": {0x8004}}
    conflicts, unknown = ir.pointer_conflicts(Image(), 0, Found(), known, 24)
    assert conflicts == [[4, "_wrong", "0x1004"], [20, "??_C@_b", "0x1014"]]
    assert unknown == 1


def test_retail_reads_zero_past_the_file_extent_and_finds_the_table():
    # Headers, then .text holding `push z; push a; call` and a .rdata table of two functions.
    pe = 0x40
    image = bytearray(0x800)
    image[0x3C:0x40] = pe.to_bytes(4, "little")
    image[pe + 6:pe + 8] = (2).to_bytes(2, "little")
    image[pe + 20:pe + 22] = (0xE0).to_bytes(2, "little")
    image[pe + 52:pe + 56] = (0x400000).to_bytes(4, "little")
    for index, (name, va, vsize, raw, rsize) in enumerate(((b".text", 0x1000, 0x100, 0x200, 0x100),
                                                           (b".rdata", 0x2000, 0x200, 0x300, 0x10))):
        at = pe + 24 + 0xE0 + 40 * index
        image[at:at + len(name)] = name
        for offset, value in enumerate((vsize, va, rsize, raw)):
            image[at + 8 + 4 * offset:at + 12 + 4 * offset] = value.to_bytes(4, "little")
    image[0x200:0x20B] = (b"\x68" + (0x400000 + 0x2008).to_bytes(4, "little")
                          + b"\x68" + (0x400000 + 0x2000).to_bytes(4, "little") + b"\xE8")
    image[0x300:0x304] = (0x400000 + 0x1010).to_bytes(4, "little")
    image[0x304:0x308] = (0x400000 + 0x1020).to_bytes(4, "little")
    retail = ir.Retail(bytes(image))
    assert retail.read(0x2010, 4) == bytes(4)
    assert retail.read(0x9000, 4) is None
    assert retail.initializers() == [0x1010, 0x1020]
    assert retail.vtable_words(0x2000, 16) == 2


def test_initializer_table_is_an_object_of_named_slots(tmp_path, monkeypatch):
    import exit_link
    import link_cycle
    monkeypatch.setattr(exit_link, "OUT", tmp_path)
    monkeypatch.setattr(exit_link, "after_objects_problems", lambda rows, listed: [])
    monkeypatch.setattr(ir, "bridge_entries", lambda rows, inputs: (
        [(0x20, "?b@@YAXXZ"), (0x7AF9D6, "?fill@@YAXXZ"), (0x10, "?a@@YAXXZ")], ["0x30"]))
    path, late, bridge = exit_link.initializer_table([], [])
    assert bridge["entries"] == 3 and bridge["unreachable"] == ["0x30"]
    # VC7.1 native .CRT$XCU slots are read/write, initialized data, aligned to 4.
    # P2: a read-only bridge split off into .data outside __xc_a..__xc_z.
    # Match native attributes so every emitted bridge slot remains in that range.
    for table, size, wanted in ((path, 8, [(0, "?b@@YAXXZ"), (4, "?a@@YAXXZ")]), (late, 4, [(0, "?fill@@YAXXZ")])):
        sections, symbols = link_cycle.parse_coff(table.read_bytes())
        assert sections[0].name == ".CRT$XCU" and sections[0].size == size
        assert sections[0].flags == 0xC0300040
        slots = [(offset, symbols[index].name, kind) for offset, index, kind in sections[0].relocs]
        assert slots == [(offset, name, link_cycle.DIR32) for offset, name in wanted]



def test_initializer_report_reads_a_compiler_local_name_in_its_own_object():
    # Two TUs each register their own `_$E1`; the ledger rows them at 0x10 and 0x20 by
    # object-symbol=. A ledger-wide name lookup credited both to whichever row came first.
    import build

    class Image:
        def initializers(self):
            return [0x10, 0x20, 0x30]

        def read(self, rva, size):
            return bytes(size)

    rows = [{"name": "??__Eg_a@@YAXXZ", "target_rva": "0x10", "source": "Code/A.cpp", "notes": "object-symbol=_$E1"},
            {"name": "??__Eg_b@@YAXXZ", "target_rva": "0x20", "source": "Code/B.cpp", "notes": "object-symbol=_$E1"},
            {"name": "?plain@@YAXXZ", "target_rva": "0x30", "source": "Code/C.cpp", "notes": ""}]
    a, b, c = (build.row_object(row).name for row in rows)
    registered = [(b, "_$E1", b"", set(), []), (a, "_$E1", b"", set(), []), (c, "?plain@@YAXXZ", b"", set(), [])]
    report = ir.initializer_report(Image(), rows, registered)
    assert report["registered_retail_entries"] == 3 and report["not_registered"] == 0
    assert report["registered_not_in_retail"] == 0 and report["unidentified"] == []
    # A `_$E1` from an object with no row of that name is not another object's `_$E1`.
    report = ir.initializer_report(Image(), rows, [(c, "_$E1", b"", set(), [])])
    assert report["registered_retail_entries"] == 0 and report["unidentified"] == [[c, "_$E1"]]


def test_initializer_report_lets_relocation_targets_pick_among_same_shaped_entries():
    # Three retail entries share `mov ecx, g; call ctor; ret`. An unrowed `_$E7` constructing
    # g_two is retail's second one: its DIR32 target is where the ledger puts g_two and its REL32
    # target the ctor. Shape alone would take the first.
    import link_cycle

    base, ctor = 0x400000, 0x5000

    def body(at, global_rva):
        call = (ctor - (at + 10)) & 0xFFFFFFFF
        return (bytes([0xB9]) + (base + global_rva).to_bytes(4, "little") + bytes([0xE8])
                + call.to_bytes(4, "little") + bytes([0xC3]))

    image = {0x100: body(0x100, 0x9000), 0x200: body(0x200, 0x9004), 0x300: body(0x300, 0x9008)}

    class Image:
        def __init__(self):
            self.base = base

        def initializers(self):
            return [0x100, 0x200, 0x300]

        def read(self, rva, size):
            for start, raw in image.items():
                if start <= rva < start + len(raw):
                    return (raw[rva - start:] + bytes(size))[:size]
            return bytes(size)

    ours = bytes([0xB9]) + bytes(4) + bytes([0xE8]) + bytes(4) + bytes([0xC3])
    masked = set(range(1, 5)) | set(range(6, 10))
    relocs = [(1, "?g_two@@3VThing@@A", link_cycle.DIR32, 0), (6, "??0Thing@@QAE@XZ", link_cycle.REL32, 0)]
    addresses = {"?g_two@@3VThing@@A": {0x9004}, "??0Thing@@QAE@XZ": {ctor}}
    report = ir.initializer_report(Image(), [], [("x.obj", "_$E7", ours, masked, relocs)], addresses)
    assert report["not_registered_rvas"] == ["0x100", "0x300"] and report["registered_by_shape_only"] == 0
    # With no target the ledger places, the shape still credits an entry, and says so.
    report = ir.initializer_report(Image(), [], [("x.obj", "_$E7", ours, masked, [])], {})
    assert report["not_registered_rvas"] == ["0x200", "0x300"] and report["by_shape_only"] == [["x.obj", "_$E7", "0x100"]]
    # A target the ledger places elsewhere rules every entry out.
    report = ir.initializer_report(Image(), [], [("x.obj", "_$E7", ours, masked, relocs)], {**addresses, "?g_two@@3VThing@@A": {0x7000}})
    assert report["registered_retail_entries"] == 0 and report["unidentified"] == [["x.obj", "_$E7"]]


def test_initializer_report_needs_a_row_for_a_header_constant_copy():
    # Retail's three `mov eax, [rate]; mov [s], eax; ret` entries each build their own unit's copy
    # of one header constant. An unrowed copy agrees on the rate with all three: that vote picks
    # none, and its static is its own object's, so it is neither credited by shape nor "twice".
    import link_cycle

    base, rate = 0x400000, 0x9000

    def body(static):
        return (bytes([0xA1]) + (base + rate).to_bytes(4, "little") + bytes([0xA3])
                + (base + static).to_bytes(4, "little") + bytes([0xC3]))

    image = {0x100: body(0xA000), 0x200: body(0xA004), 0x300: body(0xA008)}

    class Image:
        def __init__(self):
            self.base = base

        def initializers(self):
            return [0x100, 0x200, 0x300]

        def read(self, rva, size):
            for start, raw in image.items():
                if start <= rva < start + len(raw):
                    return (raw[rva - start:] + bytes(size))[:size]
            return bytes(size)

    ours = bytes([0xA1]) + bytes(4) + bytes([0xA3]) + bytes(4) + bytes([0xC3])
    masked = set(range(1, 5)) | set(range(6, 10))
    relocs = [(1, "?rate@@3HA", link_cycle.DIR32, 0), (6, "?CONSTANT@@3HB", link_cycle.DIR32, 0)]
    addresses = {"?rate@@3HA": {rate}}
    copy = ("u.obj", "_$E1", ours, masked, relocs, frozenset({"?CONSTANT@@3HB"}))
    report = ir.initializer_report(Image(), [], [copy], addresses)
    assert report["registered_retail_entries"] == 0 and report["unidentified"] == [["u.obj", "_$E1"]]
    assert report["by_shape_only"] == [] and report["twice"] == []
    # Its row names the entry.
    import build
    row = {"name": "_$E1", "target_rva": "0x200", "source": "Code/U.cpp", "notes": ""}
    copy = (build.row_object(row).name,) + copy[1:]
    report = ir.initializer_report(Image(), [row], [copy], addresses)
    assert report["not_registered_rvas"] == ["0x100", "0x300"] and report["unidentified"] == []
    # One unit's own statics that use up the tie are credited, as shape credits.
    unit = [("w.obj", f"_$E{n}", ours, masked, [(1, "?rate@@3HA", link_cycle.DIR32, 0), (6, f"_s{n}", link_cycle.DIR32, 0)],
             frozenset({f"_s{n}"})) for n in (1, 4, 7)]
    report = ir.initializer_report(Image(), [], unit, addresses)
    assert report["not_registered"] == 0 and len(report["by_shape_only"]) == 3 and report["unidentified"] == []
    # A shared global the vote cannot single out is a shape credit, listed as one.
    shared = ("v.obj", "_$E2", ours, masked, relocs, frozenset())
    report = ir.initializer_report(Image(), [], [shared], addresses)
    assert report["by_shape_only"] == [["v.obj", "_$E2", "0x100"]]


def test_a_template_static_slot_runs_once_however_many_objects_emit_it(tmp_path):
    # MSVC 7.1 emits `ModuleTag<...>::s_key`'s data as a pick-any COMDAT in every object that
    # instantiates it, and its `.CRT$XCU` slot in a section associative with that data. The link keeps
    # one copy of the data and drops the other objects' associated slots: no second construction.
    import struct
    import link_cycle

    data, slot = 0xC0301040, 0xC0301040
    paths = []
    for name in ("a", "b"):
        path = link_cycle.write_coff(
            tmp_path / f"{name}.obj",
            [(".data", data | link_cycle.COMDAT, bytes(4), 2), (".CRT$XCU", slot | link_cycle.COMDAT, bytes(4), 5),
             (".text$yc", 0x60501020, b"\xC3", 0)],
            [("?s_key@?$Tag@$00@@2HA", 1, 0, link_cycle.EXTERNAL), ("_$E1", 3, 0, link_cycle.STATIC)],
            {2: [(0, "_$E1", link_cycle.DIR32)]})
        raw = bytearray(path.read_bytes())
        table = struct.unpack_from("<I", raw, 8)[0]
        raw[table + 18 * 3 + 12:table + 18 * 3 + 14] = (1).to_bytes(2, "little")   # .CRT$XCU's aux: with section 1
        path.write_bytes(bytes(raw))
        paths.append(path)
    _definitions, registered, _code = ir.scan_objects(paths)
    assert [(obj, symbol, entry[-1]) for obj, symbol, *entry in registered] == [
        ("a.obj", "_$E1", "?s_key@?$Tag@$00@@2HA"), ("b.obj", "_$E1", "?s_key@?$Tag@$00@@2HA")]

    class Image:
        base = 0x400000

        def initializers(self):
            return [0x10]

        def read(self, rva, size):
            return bytes(size)

    report = ir.initializer_report(Image(), [], registered)
    assert report["registered_entries"] == 1 and report["registered_comdat_copies_discarded"] == 1
    assert report["twice"] == [] and len(report["unidentified"]) <= 1
    # The copy a row names is the one counted.
    import build
    row = {"name": "_$E1", "target_rva": "0x10", "source": "Code/B.cpp", "notes": ""}
    rowed = [(build.row_object(row).name if obj == "b.obj" else obj, symbol, *entry) for obj, symbol, *entry in registered]
    report = ir.initializer_report(Image(), [row], rowed)
    assert report["registered_retail_entries"] == 1 and report["unidentified"] == [] and report["twice"] == []


# ------------------------------------------------------------ LINK-634: a credit whose targets differ from retail's

class ConflictImage:
    """Two same-shaped initializers: `mov ecx,global; call ctor; ret`."""
    base = 0x400000
    words = {0x100: (0x900, 0x500), 0x200: (0xA00, 0x600)}

    def initializers(self):
        return [0x100, 0x200]

    def read(self, rva, size):
        out = bytearray()
        for start, (global_rva, ctor) in self.words.items():
            if start <= rva < start + 11:
                body = b"\xB9" + struct.pack("<I", global_rva + self.base) + \
                    b"\xE8" + struct.pack("<i", ctor - (start + 10)) + b"\xC3"
                out = bytearray(body[rva - start:])
        return bytes(out[:size]).ljust(size, b"\xCC")


def conflict_entry(global_name="?g@@3HA", ctor="??0Local@@QAE@XZ"):
    body = b"\xB9\0\0\0\0\xE8\0\0\0\0\xC3"
    masked = {1, 2, 3, 4, 6, 7, 8, 9}
    return ("x.obj", "_$E1", body, masked, [(1, global_name, 6, 0), (6, ctor, 20, 0)])


def conflicts_of(addresses, entry, code_bodies=None):
    addresses = collections.defaultdict(set, addresses)
    return ir.initializer_report(ConflictImage(), [], [entry], addresses, code_bodies)


def test_a_credit_with_another_constructor_is_reported():
    # P36: the global agrees, the ledger cannot place our local ctor, and retail's address is rowed under another name
    report = conflicts_of({"?g@@3HA": {0x900}, "??0Rowed@@QAE@XZ": {0x500}}, conflict_entry())
    assert report["registered_retail_entries"] == 1 and report["credit_conflicts"] == 1
    found = report["conflicts"][0]
    assert (found["entry"], found["kind"], found["ours"], found["retail_rva"], found["retail_name"]) == \
        ("0x100", "call", "??0Local@@QAE@XZ", "0x500", "??0Rowed@@QAE@XZ")
    assert found["how"] == "votes" and found["same_code"] is None


def test_a_shape_credit_with_another_global_is_reported():
    # P39: nothing places our global or ctor, so a shape alone credits an entry that builds something else
    report = conflicts_of({"?retail@@3HA": {0x900}, "??0Rowed@@QAE@XZ": {0x500}}, conflict_entry("?other@@3HA"))
    kinds = {c["kind"]: c for c in report["conflicts"]}
    assert report["credit_conflicts"] == 2 and kinds["address"]["how"] == "shape"
    assert kinds["address"]["ours"] == "?other@@3HA" and kinds["address"]["retail_name"] == "?retail@@3HA"


def test_a_conflict_reports_and_does_not_change_the_credit():
    addresses = {"?g@@3HA": {0x900}, "??0Rowed@@QAE@XZ": {0x500}}
    report = conflicts_of(addresses, conflict_entry())
    assert report["not_registered_rvas"] == ["0x200"]


def test_a_fold_of_the_same_code_says_so():
    report = conflicts_of({"?g@@3HA": {0x900}, "??0Rowed@@QAE@XZ": {0x500}}, conflict_entry(),
                          code_bodies=lambda name, rva: name == "??0Local@@QAE@XZ" and rva == 0x500)
    assert report["conflicts"][0]["same_code"] is True


def test_a_placed_target_agreeing_is_no_conflict():
    report = conflicts_of({"?g@@3HA": {0x900}, "??0Local@@QAE@XZ": {0x500}}, conflict_entry())
    assert report["credit_conflicts"] == 0


def test_a_retail_address_the_ledger_cannot_name_is_no_conflict():
    report = conflicts_of({"?g@@3HA": {0x900}}, conflict_entry())
    assert report["credit_conflicts"] == 0


def test_a_compiler_local_target_says_nothing():
    # every object numbers its own _$E<n>; retail's thunk row has its own name
    report = conflicts_of({"?g@@3HA": {0x900}, "??0Local@@QAE@XZ": {0x500}, "_$E2x": {0x500}}, conflict_entry(ctor="_$E2"))
    assert report["credit_conflicts"] == 0


def test_the_body_reader_compares_outside_relocations(tmp_path, monkeypatch):
    section = types.SimpleNamespace(name=".text$x", ptr=0, size=6, relocs=[(1, 0, 20)], idx=1, flags=0)
    symbol = types.SimpleNamespace(sec=1, name="??0Local@@QAE@XZ", value=0, cls=2)
    (tmp_path / "o.obj").write_bytes(b"\xE8\0\0\0\0\xC3")
    monkeypatch.setattr(ir.link_cycle, "parse_coff", lambda raw: ([section], {0: symbol}))

    class Same:
        def read(self, rva, size):
            return b"\xE8\x11\x22\x33\x44\xC3"[:size]
    rows = [{"target_rva": "0x500", "target_size": "6"}, {"target_rva": "0x600", "target_size": "9"}]
    same = ir.code_body_reader([tmp_path / "o.obj"], Same(), rows, {"??0Local@@QAE@XZ"})
    assert same("??0Local@@QAE@XZ", 0x500) is True
    assert same("??0Local@@QAE@XZ", 0x600) is None     # our body is shorter than retail's row
    assert same("??0Missing@@QAE@XZ", 0x500) is None

