"""Data that resembles code after relocation masking must never become a body."""
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


def object_fixture(path, section_name, characteristics):
    # One defined symbol, one section; identical bytes regardless of flags.
    payload = b"\xc3\x00\x00\x00"
    symbol_offset = 20 + 40 + len(payload)
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, symbol_offset, 1, 0, 0)
    section = section_name.encode().ljust(8, b"\x00") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(payload), 60, 0, 0, 0, 0, characteristics)
    symbol = b"_body\x00\x00\x00" + struct.pack("<IhHBB", 0, 1, 0x20, 2, 0)
    path.write_bytes(header + section + payload + symbol + struct.pack("<I", 4))
    return payload


@pytest.mark.parametrize("section_name,flags", [(".rdata", 0x40301040),
                                                (".text", 0x40301040)])
def test_noncode_section_is_rejected_even_with_function_type_or_text_name(
        tmp_path, section_name, flags):
    build = importlib.import_module("build")
    obj = tmp_path / "data.obj"
    expected = object_fixture(obj, section_name, flags)
    # Literal readers still need access to data sections.
    assert build.read_object_symbol_bytes(obj, "_body")[0] == expected
    assert "_body" not in build.defined_code_symbols(obj)
    with pytest.raises(SystemExit, match="non-code COFF section"):
        build.read_object_symbol_bytes(obj, "_body", code_only=True)


@pytest.mark.parametrize("section_name", [".text", "CODE1"])
def test_executable_section_is_accepted_by_flags_not_spelling(tmp_path, section_name):
    build = importlib.import_module("build")
    obj = tmp_path / "code.obj"
    expected = object_fixture(obj, section_name, 0x60501020)
    assert "_body" in build.defined_code_symbols(obj)
    assert build.read_object_symbol_bytes(obj, "_body", code_only=True)[0] == expected


def test_function_gate_rejects_byte_identical_data(tmp_path, monkeypatch):
    build = importlib.import_module("build")
    obj = tmp_path / "table.obj"
    expected = object_fixture(obj, ".rdata", 0x40301040)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: expected[:size])
    row = {"name": "_body", "target_rva": "0x1000", "target_size": "4",
           "source": "Code/table.cpp", "notes": ""}
    with pytest.raises(SystemExit, match="non-code COFF section"):
        build.compile_function(row, {}, obj)
