"""One imported function may have duplicate named PE import-table entries."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
from test_pe_imports import fixture_pe


@pytest.mark.parametrize("entries,symbol,valid", [
    ([("msvcr71.dll", "fgetc")] * 2, "__imp__fgetc", True),
    ([("msvcr71.dll", "fgetc"), ("msvcrt.dll", "fgetc")], "__imp__fgetc", False),
    ([("msvcr71.dll", "fgetc"), ("msvcr71.dll", "getc")], "__imp__fgetc", False),
    ([("msvcr71.dll", "getc")] * 2, "__imp__fgetc", False),
    ([("msvcr71.dll", 17)] * 2, "__imp__fgetc", False),
    ([("msvcr71.dll", "fgetc")] * 2, "ordinary_global", False),
])
@pytest.mark.parametrize("addend", [0, 4])
def test_duplicate_import_requires_same_declared_identity(monkeypatch, tmp_path,
                                                        entries, symbol, valid,
                                                        addend):
    data, slots = fixture_pe(entries)
    exe = tmp_path / "retail.exe"
    exe.write_bytes(data)
    obj = tmp_path / "code.obj"
    obj.write_bytes(b"object metadata is supplied below")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    rows = [{"name": f"function{i}", "target_rva": hex(0x1000 + i * 16),
             "target_size": "7", "source": f"Code/file{i}.cpp", "notes": ""}
            for i in range(2)]
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "EXE", exe)
    monkeypatch.setattr(build, "require_row_object", lambda row: obj)
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        (b"\xff\x15" + struct.pack("<I", addend) + b"\xc3",
                         [(2, 6, symbol)]))
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xff\x15" + struct.pack("<I", slots[(rva - 0x1000) // 16]
                                                 + addend) + b"\xc3")
    if valid:
        build.verify_dir32_consistency(rows)
    else:
        with pytest.raises(SystemExit):
            build.verify_dir32_consistency(rows)
