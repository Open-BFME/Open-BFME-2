"""Decoder preparation policy: vendor tokens plus reviewed native ownership."""
from pathlib import Path

import pytest

from test_link_check import C, preparation  # noqa: F401; shared realistic preparation fixture


@pytest.mark.parametrize("name", [
    "GameEngine/Source/Common/placeObjectAtPosition240EEF.cpp",
    "Completion215930.cpp", "POSITION2.cpp", "Position2.cpp", "completion2.cpp",
])
def test_ordinary_suffix_keeps_explicit_normal_preparation(preparation, name):
    add, rows, _, calls, _ = preparation
    source, _ = add(name)
    assert C.prepare_current([source]) == 0
    assert calls[0] == ("compile", [rows[0]], [source])
    assert calls[1] == ("normal", [source.relative_to(C.ROOT).as_posix()])


@pytest.mark.parametrize("name", [
    "On2/decoder.cpp", "ON2/decoder.cpp", "on2/decoder.cpp", "ON2Driver.cpp",
    "fooOn2Decoder.cpp", "fooON2Decoder.cpp", "foo_on2decode.cpp", "libon2decode.cpp",
    "VP6/decoder.cpp", "vp60decode.cpp", "vp62decode.cpp", "Winamp/decoder.cpp",
    "libvpShared/decoder.cpp", "ffdshow/decoder.cpp", "MFNode/decoder.cpp",
])
def test_real_decoder_paths_refuse_before_any_resolution_or_content(preparation, monkeypatch, name):
    add, rows, _, calls, _ = preparation
    safe, _ = add()
    def forbidden(*args, **kwargs):
        raise AssertionError("protected request must be filtered before any read or resolve")
    monkeypatch.setattr(Path, "resolve", forbidden)
    monkeypatch.setattr(Path, "read_bytes", forbidden)
    with pytest.raises(SystemExit, match="protected decoder"):
        C.preparation_sources([safe, "Code/" + name], rows)
    assert calls == []


@pytest.mark.parametrize("start,size", [
    (0x1B5530, 1), (0x1B5531, 1), (0x1B552F, 2), (0x1B55D5, 2), (0x1B552F, 500),
])
def test_neutral_name_decoder_extent_refuses_before_source_bytes(preparation, monkeypatch, start, size):
    add, rows, _, calls, _ = preparation
    source, _ = add("Position2.cpp")
    # A second row in this unit is enough, even if the first safe row passes.
    rows.append({**rows[0], "target_rva": hex(start), "target_size": str(size)})
    read = Path.read_bytes
    def guarded(path):
        assert path != source, "decoder-owned source content was read"
        return read(path)
    monkeypatch.setattr(Path, "read_bytes", guarded)
    with pytest.raises(SystemExit, match="protected decoder-owned"):
        C.prepare_current([source])
    assert calls == []


@pytest.mark.parametrize("start,size", [(0x1B8E90, 284), (0x1B552F, 1), (0x1D8E7A, 1)])
def test_external_helpers_and_half_open_boundaries_still_require_normal_gates(preparation, start, size):
    add, rows, _, calls, _ = preparation
    source, _ = add()
    rows[0].update(target_rva=hex(start), target_size=str(size))
    assert C.prepare_current([source]) == 0
    assert [call[0] for call in calls] == ["compile", "normal"]


@pytest.mark.parametrize("field,value", [("target_rva", "not-rva"), ("target_size", "0"),
                                         ("target_size", "-1"), ("target_size", None)])
def test_unknown_owned_native_extent_fails_closed(preparation, field, value):
    add, rows, _, calls, _ = preparation
    source, _ = add()
    rows[0][field] = value
    with pytest.raises(SystemExit, match="no valid native extent"):
        C.prepare_current([source])
    assert calls == []


@pytest.mark.parametrize("damage", ["missing", "header", "truncated", "zero", "overlap",
                                    "outside", "rva", "encoding", "extra-column"])
def test_boundary_policy_unavailable_or_malformed_fails_closed(preparation, damage):
    add, _, _, calls, _ = preparation
    source, _ = add()
    queue = C.ROOT / "reverse/vp6_cleanroom/queue.tsv"
    lines = queue.read_text().splitlines()
    if damage == "missing":
        queue.unlink()
    elif damage == "encoding":
        queue.write_bytes(b"\xff")
    else:
        if damage == "header":
            lines[0] = "unknown"
        elif damage == "truncated":
            lines.pop()
        elif damage == "extra-column":
            lines[1] += "\textra"
        else:
            fields = lines[2].split("\t")
            if damage == "zero":
                fields[1] = "0"
            elif damage == "overlap":
                fields[0] = "001b5530"
            elif damage == "outside":
                fields[0] = "00200000"
            else:
                fields[0] = "not-hex!"
            lines[2] = "\t".join(fields)
        queue.write_text("\n".join(lines) + "\n")
    with pytest.raises(SystemExit, match="decoder boundary metadata.*invalid"):
        C.prepare_current([source])
    assert calls == []


def test_boundary_policy_move_during_read_fails_closed(preparation, monkeypatch):
    _, _, _, calls, _ = preparation
    queue = C.ROOT / "reverse/vp6_cleanroom/queue.tsv"
    read = Path.read_bytes
    def moved(path):
        content = read(path)
        if path == queue:
            path.write_bytes(content.replace(b"VP6_DeleteTmpBuffers", b"VP6_ChangeTmpBuffers"))
        return content
    monkeypatch.setattr(Path, "read_bytes", moved)
    with pytest.raises(SystemExit, match="metadata moved while reading"):
        C.decoder_policy()
    assert calls == []


@pytest.mark.parametrize("phase", ["preflight", "compile", "normal"])
def test_changed_policy_generation_cannot_admit_a_witness(preparation, monkeypatch, phase):
    add, _, _, calls, _ = preparation
    source, _ = add()
    queue = C.ROOT / "reverse/vp6_cleanroom/queue.tsv"
    def change():
        content = queue.read_bytes()
        queue.write_bytes(content.replace(b"VP6_DeleteTmpBuffers", b"VP6_ChangeTmpBuffers"))
    if phase == "preflight":
        monkeypatch.setattr(C.build, "ensure_case_shims", change)
    elif phase == "compile":
        compile = C.build.compile_rows
        def changed(*args, **kwargs):
            result = compile(*args, **kwargs)
            change()
            return result
        monkeypatch.setattr(C.build, "compile_rows", changed)
    else:
        normal = C.build.main
        def changed(names):
            normal(names)
            change()
        monkeypatch.setattr(C.build, "main", changed)
    with pytest.raises(SystemExit, match="decoder boundary metadata moved"):
        C.prepare_current([source])
    assert len(calls) == {"preflight": 0, "compile": 1, "normal": 2}[phase]


def test_queue_redirect_cannot_read_foreign_source(preparation, monkeypatch):
    _, _, _, calls, _ = preparation
    queue = C.ROOT / "reverse/vp6_cleanroom/queue.tsv"
    resolve = Path.resolve
    def redirected(path):
        return C.ROOT.parent / "On2/decoder.cpp" if path == queue else resolve(path)
    def forbidden(*args, **kwargs):
        raise AssertionError("redirected queue content was read")
    monkeypatch.setattr(Path, "resolve", redirected)
    monkeypatch.setattr(Path, "read_bytes", forbidden)
    with pytest.raises(SystemExit, match="queue escapes approved metadata path"):
        C.decoder_policy()
    assert calls == []
