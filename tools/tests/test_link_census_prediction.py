"""predicted_unresolved: the selection link's names, predicted from the objects."""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L  # noqa: E402


def coff(path, symbols, drectve=b""):
    """A COFF object: one .text section (and .drectve when given); `symbols`
    are (name, section, value, storage, aux records)."""
    sections = [(b".text", b"\xcc" * 16, 0x60500020)] + ([(b".drectve", drectve, 0xA00)] if drectve else [])
    offset = 20 + 40 * len(sections)
    headers, bodies = b"", b""
    for name, body, flags in sections:
        headers += name.ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, len(body), offset + len(bodies),
                                                      0, 0, 0, 0, flags)
        bodies += body
    table = offset + len(bodies)
    strings, records, count = bytearray(4), b"", 0
    for name, section, value, storage, aux in symbols:
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings += raw + b"\0"
        records += field + struct.pack("<IhHBB", value, section, 0, storage, len(aux)) + b"".join(aux)
        count += 1 + len(aux)
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, table, count, 0, 0)
    path.write_bytes(header + headers + bodies + records + bytes(strings))
    return path


def weak_aux(tag):
    return struct.pack("<II", tag, 3) + b"\0" * 10


def test_prediction_resolves_definitions_weak_defaults_alternates_and_includes(tmp_path):
    a = coff(tmp_path / "a.obj", [
        ("_defined_here", 1, 0, L.EXTERNAL, []),
        ("_used_and_defined", 0, 0, L.EXTERNAL, []),
        ("_missing", 0, 0, L.EXTERNAL, []),
        ("_common", 0, 4, L.EXTERNAL, []),                       # COMMON: a definition
        ("??_Eweak", 0, 0, L.WEAK_EXTERNAL, [weak_aux(6)]),     # default: symbol 6, _default
        ("_default", 1, 8, L.EXTERNAL, []),
        ("_weak_to_nothing", 0, 0, L.WEAK_EXTERNAL, [weak_aux(9)]),  # default: _nowhere
        ("_nowhere", 0, 0, L.EXTERNAL, []),
    ], drectve=b"/alternatename:_aliased=_defined_here /alternatename:_dangling=_also_nowhere /INCLUDE:_forced ")
    b = coff(tmp_path / "b.obj", [
        ("_used_and_defined", 1, 0, L.EXTERNAL, []),
        ("_aliased", 0, 0, L.EXTERNAL, []),
        ("_dangling", 0, 0, L.EXTERNAL, []),
        ("_WinMainCRTStartup", 1, 4, L.EXTERNAL, []),
    ])
    assert L.predicted_unresolved([a, b]) == {"_missing", "_nowhere", "_weak_to_nothing", "_dangling", "_forced"}


def test_prediction_names_the_entry_point_when_nothing_defines_it(tmp_path):
    a = coff(tmp_path / "a.obj", [("_f", 1, 0, L.EXTERNAL, [])])
    assert L.predicted_unresolved([a]) == {L.ENTRY_SYMBOL}


def test_an_unreadable_object_predicts_nothing(tmp_path):
    assert L.predicted_unresolved([tmp_path / "gone.obj"]) == set()
    (tmp_path / "short.obj").write_bytes(b"\x4c\x01")
    assert L.predicted_unresolved([tmp_path / "short.obj"]) == set()


def test_import_names_bind_to_local_definitions_and_image_base_is_the_linkers(tmp_path):
    a = coff(tmp_path / "a.obj", [
        ("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []),
        ("_local", 1, 4, L.EXTERNAL, []),
        ("__imp__local", 0, 0, L.EXTERNAL, []),       # LNK4217: binds to _local
        ("__imp__imported", 0, 0, L.EXTERNAL, []),    # a real DLL import: unresolved under /NODEFAULTLIB
        ("___ImageBase", 0, 0, L.EXTERNAL, []),
    ])
    assert L.predicted_unresolved([a]) == {"__imp__imported"}
