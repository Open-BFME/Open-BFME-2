"""The retail comparison's verdicts: a masked relocation is not a difference, a short copy counts."""
import sys
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
    monkeypatch.setattr(ir, "bridge_entries", lambda rows, inputs: ([(0x20, "?b@@YAXXZ"), (0x10, "?a@@YAXXZ")], ["0x30"]))
    path, bridge = exit_link.initializer_table([], [])
    assert bridge["entries"] == 2 and bridge["unreachable"] == ["0x30"]
    sections, symbols = link_cycle.parse_coff(path.read_bytes())
    assert sections[0].name == ".CRT$XCU" and sections[0].size == 8
    slots = [(offset, symbols[index].name, kind) for offset, index, kind in sections[0].relocs]
    assert slots == [(0, "?b@@YAXXZ", link_cycle.DIR32), (4, "?a@@YAXXZ", link_cycle.DIR32)]

