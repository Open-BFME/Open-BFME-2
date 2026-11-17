"""class --fold's class-name getter tie (rename.name_getter_tie): a slot of OLD's
own table holding retail's `mov eax, offset "NEW"; ret` ties NEW to the table,
and only that exact shape, literal and ownership does."""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import rename  # noqa: E402

TABLE = 0x00403910                      # an rva; the tie only uses it as a key
GETTER = 0x00002000
OTHER = 0x00001000
LITERAL = 0x00405000


def setup(monkeypatch, literal=b"TerrainVisual\0", rows=None, extra_tables=None):
    image = bytearray(0x6000)
    struct.pack_into("<BIB", image, GETTER, 0xB8, LITERAL + rename.IMAGE_BASE, 0xC3)
    image[0x5000:0x5000 + len(literal)] = literal
    sections = [{"name": ".text", "rva": 0x1000, "size": 0x2000},
                {"name": ".rdata", "rva": LITERAL, "size": 0x1000}]

    def offset(_sections, rva):
        if rva == LITERAL or LITERAL <= rva < LITERAL + 0x1000:
            return 0x5000 + (rva - LITERAL)
        if 0 <= rva < 0x5000:
            return rva
        raise ValueError(rva)

    monkeypatch.setattr(build, "exe_image", lambda: (bytes(image), sections))
    monkeypatch.setattr(build, "rva_to_file_offset", offset)
    spans = [(GETTER, GETTER + 6, {"name": name, "target_rva": f"0x{GETTER:08X}"})
             for name in (rows or ["?name@Rva002DAB5ENamed@@QBEPBDXZ"])]
    monkeypatch.setattr(rename, "_row_spans", lambda ctx: (None, spans))
    tables = {TABLE: ([OTHER, OTHER, GETTER], {})}
    tables.update(extra_tables or {})
    return tables


def tie(tables):
    return rename.name_getter_tie(None, "Rva002DAB18", "TerrainVisual", TABLE, tables)


def test_the_class_name_getter_ties_the_new_name(monkeypatch):
    found = tie(setup(monkeypatch))
    assert found and "slot 2" in found[0] and '"TerrainVisual"' in found[0]


def test_a_different_literal_ties_nothing(monkeypatch):
    assert tie(setup(monkeypatch, literal=b"TerrainLogic\0")) is None


def test_a_longer_literal_is_not_the_name(monkeypatch):
    assert tie(setup(monkeypatch, literal=b"TerrainVisualManager\0")) is None


def test_a_getter_another_table_holds_is_inherited_or_folded(monkeypatch):
    other = 0x00403A00
    assert tie(setup(monkeypatch, extra_tables={other: ([GETTER], {})})) is None


def test_a_getter_rowed_for_a_real_third_class_ties_nothing(monkeypatch):
    assert tie(setup(monkeypatch, rows=["?name@TerrainLogic@@UBEPBDXZ"])) is None


def test_old_and_new_members_at_the_getter_are_accepted(monkeypatch):
    rows = ["?name@Rva002DAB18@@UBEPBDXZ", "?name@TerrainVisual@@UBEPBDXZ"]
    assert tie(setup(monkeypatch, rows=rows))
