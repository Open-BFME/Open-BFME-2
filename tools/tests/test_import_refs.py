"""DIR32 copying must not substitute an unrelated named library import."""
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pe_imports import ImportEntry, coff_import_names


@pytest.mark.parametrize("symbol,expected", [
    ("__imp__CreateFileA@28", {"_CreateFileA@28", "CreateFileA"}),
    ("__imp__AIL_get_preference@4", {"_AIL_get_preference@4", "AIL_get_preference"}),
    ("__imp___mbsdup", {"__mbsdup", "_mbsdup"}),
    ("__imp_??1exception@std@@UAE@XZ", {"??1exception@std@@UAE@XZ"}),
    ("__imp_@fast@4", {"@fast@4", "fast"}),
    ("ordinary_symbol", set()),
])
def test_coff_decoration_preserves_export_identity(symbol, expected):
    assert coff_import_names(symbol) == expected


def fixture(monkeypatch, tmp_path, symbol, entry, *, addend=0, slot=0x500000):
    build = importlib.import_module("build")
    pe_imports = importlib.import_module("pe_imports")
    exe = tmp_path / "image.exe"
    exe.write_bytes(b"test image; PE parsing is covered by test_pe_imports")
    monkeypatch.setattr(build, "EXE", exe)
    monkeypatch.setattr(pe_imports, "read_imports", lambda data: {0x500000: entry})
    compiled = b"\xff\x15" + struct.pack("<I", addend & 0xffffffff) + b"\xc3"
    retail = b"\xff\x15" + struct.pack("<I", (slot + addend) & 0xffffffff) + b"\xc3"
    rows = [{"name": "function", "target_rva": "0x1000", "target_size": "7",
             "source": "Code/example.cpp", "notes": ""}]
    monkeypatch.setattr(build, "require_row_object", lambda row: Path("example.obj"))
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: retail[:size])
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        (compiled, [(2, 6, symbol)]))
    return build, rows


def test_reference_increment_cannot_match_global_free(monkeypatch, tmp_path):
    build, rows = fixture(monkeypatch, tmp_path, "__imp__InterlockedIncrement@4",
                          ImportEntry("kernel32.dll", "GlobalFree", None))
    with pytest.raises(SystemExit):
        build.verify_import_refs(rows)


def test_crt_synonyms_are_not_linker_decoration(monkeypatch, tmp_path):
    build, rows = fixture(monkeypatch, tmp_path, "__imp___stricmp",
                          ImportEntry("msvcr71.dll", "_strcmpi", None))
    with pytest.raises(SystemExit):
        build.verify_import_refs(rows)


def test_cpp_namespace_is_not_erased(monkeypatch, tmp_path):
    build, rows = fixture(monkeypatch, tmp_path, "__imp_??1exception@std@@UAE@XZ",
                          ImportEntry("msvcr71.dll", "??1exception@@UAE@XZ", None))
    with pytest.raises(SystemExit):
        build.verify_import_refs(rows)


@pytest.mark.parametrize("entry,slot", [
    (ImportEntry("kernel32.dll", None, 17), 0x500000),
    (ImportEntry("kernel32.dll", "GlobalFree", None), 0x500004),
])
def test_unknown_or_ordinal_only_target_fails(monkeypatch, tmp_path, entry, slot):
    build, rows = fixture(monkeypatch, tmp_path, "__imp__GlobalFree@4", entry, slot=slot)
    with pytest.raises(SystemExit):
        build.verify_import_refs(rows)


@pytest.mark.parametrize("addend", [0, 4, -4])
def test_named_import_with_addend_passes(monkeypatch, tmp_path, addend):
    build, rows = fixture(monkeypatch, tmp_path, "__imp__GlobalFree@4",
                          ImportEntry("kernel32.dll", "GlobalFree", None), addend=addend)
    build.verify_import_refs(rows)


def test_unreadable_body_fails_instead_of_skipping(monkeypatch, tmp_path):
    build, rows = fixture(monkeypatch, tmp_path, "__imp__GlobalFree@4",
                          ImportEntry("kernel32.dll", "GlobalFree", None))
    def missing(*args):
        raise ValueError("symbol not found")
    monkeypatch.setattr(build, "read_object_symbol_bytes", missing)
    with pytest.raises(SystemExit):
        build.verify_import_refs(rows)


def test_funclet_reidentification_is_used(monkeypatch, tmp_path):
    build, rows = fixture(monkeypatch, tmp_path, "__imp__GlobalFree@4",
                          ImportEntry("kernel32.dll", "GlobalFree", None))
    read = build.read_object_symbol_bytes
    monkeypatch.setattr(build, "is_funclet_row", lambda *args: True)
    monkeypatch.setattr(build, "read_funclet", lambda *args:
                        (*read(), "renumbered compiler label"))
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        pytest.fail("must read the reidentified funclet"))
    build.verify_import_refs(rows)
