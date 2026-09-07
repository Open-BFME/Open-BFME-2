"""Mapped BSS must never read the unrelated bytes following a raw PE section."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def image():
    data = bytearray(b"X" * 0x800)
    struct.pack_into("<I", data, 0x3C, 0x80)
    struct.pack_into("<H", data, 0x86, 2)
    struct.pack_into("<H", data, 0x94, 0xE0)
    for index, (name, rva, virtual, raw, file_offset) in enumerate([
            (b".data", 0x1000, 0x20, 8, 0x400),
            (b".next", 0x1020, 8, 8, 0x600)]):
        section = 0x178 + index * 40
        data[section:section + 8] = name.ljust(8, b"\0")
        struct.pack_into("<IIII", data, section + 8, virtual, rva, raw, file_offset)
    data[0x400:0x408] = b"abcdefgh"
    data[0x600:0x608] = b"NEXTDATA"
    return bytes(data), build.pe_sections(data)


def test_raw_and_virtual_extents_are_preserved():
    _, sections = image()
    assert (sections[0]["raw_size"], sections[0]["virtual_size"], sections[0]["size"]) == (8, 32, 32)


def test_raw_to_bss_boundary_uses_loader_zeros():
    data, sections = image()
    assert build.read_pe_bytes(data, sections, 0x1004, 8) == b"efgh\0\0\0\0"
    assert build.read_pe_bytes(data, sections, 0x1010, 4) == b"\0" * 4


def test_adjacent_virtual_sections_need_not_be_adjacent_in_file():
    data, sections = image()
    assert build.read_pe_bytes(data, sections, 0x101E, 6) == b"\0\0NEXT"


def test_file_offset_api_rejects_bss():
    _, sections = image()
    assert build.rva_to_file_offset(sections, 0x1007) == 0x407
    with pytest.raises(ValueError, match="zero-filled"):
        build.rva_to_file_offset(sections, 0x1008)


def test_uninitialized_section_never_reads_file_header():
    data, sections = image()
    sections[0].update(raw_size=0, raw_pointer=0)
    assert build.read_pe_bytes(data, sections, 0x1000, 0x20) == bytes(0x20)


def test_raw_alignment_larger_than_virtual_extent_remains_readable():
    data, sections = image()
    sections[0].update(virtual_size=4, size=8)
    assert build.read_pe_bytes(data, sections, 0x1004, 4) == b"efgh"


@pytest.mark.parametrize("rva,size", [(0x1027, 2), (0xFFF, 2), (-1, 1), (0x1000, -1), (0xFFFFFFFF, 2)])
def test_unmapped_or_invalid_ranges_fail(rva, size):
    data, sections = image()
    with pytest.raises(ValueError):
        build.read_pe_bytes(data, sections, rva, size)


def test_truncated_file_backing_is_not_silently_zero_filled():
    data, sections = image()
    with pytest.raises(ValueError, match="truncated"):
        build.read_pe_bytes(data[:0x405], sections, 0x1000, 8)


def test_read_target_bytes_uses_mapped_image(monkeypatch):
    data, sections = image()
    monkeypatch.setattr(build, "exe_image", lambda: (data, sections))
    assert build.read_target_bytes(0x1010, 4) == bytes(4)


@pytest.mark.parametrize("literal,passes", [(b"\0", True), (b"XXXX\0", False)])
def test_string_verifier_checks_mapped_bss(monkeypatch, tmp_path, literal, passes):
    data, sections = image()
    data = bytearray(data)
    struct.pack_into("<I", data, 0x400, 0x401010)
    data = bytes(data)
    exe = tmp_path / "fixture.exe"
    exe.write_bytes(data)
    monkeypatch.setattr(build, "EXE", exe)
    monkeypatch.setattr(build, "exe_image", lambda: (data, sections))
    monkeypatch.setattr(build, "require_row_object", lambda row: Path("fixture.obj"))
    name = "??_C@test"
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda path, symbol, size=None:
                        (literal, []) if symbol == name else (bytes(4), [(0, 6, name)]))
    rows = [{"name": "function", "source": "Code/fixture.cpp", "notes": "",
             "target_rva": "0x1000", "target_size": "4"}]
    if passes:
        build.verify_string_refs(rows)
    else:
        with pytest.raises(SystemExit):
            build.verify_string_refs(rows)
