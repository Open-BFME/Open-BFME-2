"""Float constants must survive the independent check after DIR32 patching."""
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


def fixture(monkeypatch, literal, retail, *, addend=0):
    build = importlib.import_module("build")
    symbol = "__real@" + literal[::-1].hex()
    rows = [{"name": f"function{i}", "target_rva": hex(0x1000 + i * 0x10),
             "target_size": "7", "source": "Code/example.cpp", "notes": ""}
            for i in range(len(retail))]
    compiled = b"\xd9\x05" + struct.pack("<I", addend & 0xffffffff) + b"\xc3"
    memory = {}
    for i, value in enumerate(retail):
        location = 0x2000 + i * 0x100
        memory[0x1000 + i * 0x10] = (
            b"\xd9\x05" + struct.pack("<I", 0x400000 + location + addend) + b"\xc3")
        memory[location] = value

    monkeypatch.setattr(build, "require_row_object", lambda row: Path("example.obj"))
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: memory[rva][:size])
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda obj, name, size=None: (literal, []) if name == symbol else
                        (compiled, [(2, 0x0006, symbol)]))
    return build, rows


def test_single_wrong_float_fails(monkeypatch):
    build, rows = fixture(monkeypatch, struct.pack("<f", 1.0), [struct.pack("<f", 0.0)])
    with pytest.raises(SystemExit):
        build.verify_float_refs(rows)


def test_equal_constants_at_different_addresses_pass(monkeypatch, tmp_path):
    value = struct.pack("<f", 1.0)
    build, rows = fixture(monkeypatch, value, [value, value])
    build.verify_float_refs(rows)
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    build.verify_dir32_consistency(rows)


def test_double_literal_addend_is_removed(monkeypatch):
    value = struct.pack("<d", 3.25)
    build, rows = fixture(monkeypatch, value, [value], addend=4)
    build.verify_float_refs(rows)


def test_negative_zero_is_not_positive_zero(monkeypatch):
    build, rows = fixture(monkeypatch, struct.pack("<f", -0.0), [struct.pack("<f", 0.0)])
    with pytest.raises(SystemExit):
        build.verify_float_refs(rows)


def test_truncated_compiler_literal_fails(monkeypatch):
    value = struct.pack("<f", 1.0)
    build, rows = fixture(monkeypatch, value, [value])
    read = build.read_object_symbol_bytes
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda obj, name, size=None:
                        (b"\x00", []) if name.startswith("__real@") else read(obj, name, size))
    with pytest.raises(SystemExit):
        build.verify_float_refs(rows)


def test_missing_object_body_cannot_silently_skip_refs(monkeypatch):
    value = struct.pack("<f", 1.0)
    build, rows = fixture(monkeypatch, value, [value])
    def unreadable(*args):
        raise ValueError("symbol not found")
    monkeypatch.setattr(build, "read_object_symbol_bytes", unreadable)
    with pytest.raises(SystemExit):
        build.verify_float_refs(rows)
