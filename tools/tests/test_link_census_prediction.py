"""predicted_unresolved: the selection link's names, predicted from the objects."""
import struct

import pytest
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


def test_extra_references_and_definitions_join_the_objects(tmp_path):
    a = coff(tmp_path / "a.obj", [("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []), ("_lib", 0, 0, L.EXTERNAL, [])],
             drectve=b"/alternatename:_viaLib=_lib2 ")
    assert L.predicted_unresolved([a], references={"?exported@@3HA", "_viaLib"}) == {
        "_lib", "?exported@@3HA", "_viaLib"}
    assert L.predicted_unresolved([a], references={"?exported@@3HA", "_viaLib"},
                                  definitions={"_lib", "_lib2"}) == {"?exported@@3HA"}


@pytest.mark.parametrize("spelling", ["/alternatename", "-alternatename", "/ALTERNATENAME", "-AlternateName"])
def test_every_alternatename_spelling_link_accepts_resolves(tmp_path, spelling):
    # Codex re-check of 6fc2babc76: LINK takes `-alternatename` too, in any case.
    a = coff(tmp_path / "a.obj", [("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []), ("_Real", 1, 4, L.EXTERNAL, []),
                                 ("_Alias", 0, 0, L.EXTERNAL, [])],
             drectve=f"{spelling}:_Alias=_Real ".encode())
    assert L.predicted_unresolved([a]) == set()
    assert L._alternate_names(a.read_bytes()) == {"_Alias": "_Real"}


@pytest.mark.parametrize("spelling", ["/INCLUDE", "-INCLUDE", "/include", "-Include"])
def test_every_include_spelling_link_accepts_is_a_reference(tmp_path, spelling):
    a = coff(tmp_path / "a.obj", [("_WinMainCRTStartup", 1, 0, L.EXTERNAL, [])],
             drectve=f"   {spelling}:_forced\0\0".encode())
    assert L.predicted_unresolved([a]) == {"_forced"}


@pytest.mark.parametrize("spelling", ["/EXPORT", "-EXPORT", "/export", "-Export", "/INCLUDE", "-include"])
def test_every_root_spelling_link_accepts_roots_the_census_graph(spelling):
    assert L.DIRECTIVE_ROOT.findall(f'/DEFAULTLIB:x {spelling}:"_name" /MERGE:a=b') == ['"_name"']


def test_a_directive_spelling_inside_another_option_is_not_a_directive(tmp_path):
    a = coff(tmp_path / "a.obj", [("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []), ("_x", 0, 0, L.EXTERNAL, [])],
             drectve=b'/INCLUDE:"_a-alternatename:_x=_WinMainCRTStartup" /EXPORT:_b-include:_c ')
    assert L._alternate_names(a.read_bytes()) == {}
    assert L.predicted_unresolved([a]) == {"_x", "_a-alternatename:_x=_WinMainCRTStartup"}
