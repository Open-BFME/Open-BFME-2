"""DIR32 diagnostics must inspect the funclet selected by the byte gate."""
import csv
import importlib
import runpy
import struct
import sys
from pathlib import Path


def test_report_uses_reidentified_funclet(monkeypatch, tmp_path, capsys):
    tools = Path(__file__).resolve().parents[1]
    monkeypatch.syspath_prepend(str(tools))
    build = importlib.import_module("build")
    (tmp_path / "reverse").mkdir()
    obj = tmp_path / "body.obj"
    obj.write_bytes(b"fixture")
    with (tmp_path / "reverse/functions.csv").open("w", newline="") as fh:
        writer = csv.writer(fh)
        writer.writerow(["name", "export", "target_rva", "target_size", "source", "status", "notes"])
        writer.writerow(["uw_fixture", "", "0x1000", "7", "Code/body.cpp", "matched",
                         "gen-funclet;object-symbol=$L123;parent=parent"])
    target = b"\x8b\x0d" + struct.pack("<I", 0xDFE78C) + b"\xc3"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "obj_path", lambda source: obj)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: target[rva-0x1000:rva-0x1000+size])
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))

    def resolve(row, symbol, output, retail):
        assert symbol == "$L123" and output == obj and retail == target
        return b"\x8b\x0d\x00\x00\x00\x00\xc3", [(2, 6, "_global")], "renumbered"

    monkeypatch.setattr(build, "read_funclet", resolve)
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args: (_ for _ in ()).throw(
        AssertionError("stale label must not be read directly")))
    monkeypatch.setattr(sys, "argv", ["dir32.py", "_global"])
    runpy.run_path(str(tools / "dir32.py"), run_name="__main__")
    assert "base 0x00dfe78c" in capsys.readouterr().out
