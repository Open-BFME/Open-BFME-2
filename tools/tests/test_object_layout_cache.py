"""build._object_layout's memo: keyed on the object's full identity and trusted only once the file had settled a tick
before it was parsed (srv1's coarse mtimes let a same-size rewrite keep (path, mtime, size): test_pin_admission_fold's
receipt test then read the old object's layout)."""
import os
import struct
import sys
import time
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402


def coff(path, symbols, code_size=16):
    """One i386 COFF object: a .text section of `code_size` bytes and external function `symbols` [(name, value)]."""
    head = 20 + 40
    section = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, code_size, head, 0, 0, 0, 0, 0x60000020)
    strings, table = bytearray(4), bytearray()
    for name, value in symbols:
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings += raw + b"\0"
        table += field + struct.pack("<IhHBB", value, 1, 0x20, 2, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, 1, 0, head + code_size, len(symbols), 0, 0)
                     + section + b"\xc3" * code_size + bytes(table) + bytes(strings))


def layout(obj):
    stat = obj.stat()
    return build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)


def names(obj):
    return [symbol["name"] for symbol in layout(obj)[2]]


def starts(obj):
    stat = obj.stat()
    return build._function_starts(str(obj), stat.st_mtime_ns, stat.st_size)


@pytest.fixture(autouse=True)
def fresh_memo():
    build._object_layout.cache_clear()
    yield
    build._object_layout.cache_clear()


def freeze_stat(monkeypatch, obj):
    """The file's identity as it is now, whatever is written later: coarse file times and a file system that keeps
    ctime as well (Windows' restored-mtime same-size rewrite)."""
    frozen, real = os.stat(obj), os.stat
    monkeypatch.setattr(os, "stat", lambda path, *a, **kw: frozen if str(path) == str(obj) else real(path, *a, **kw))
    monkeypatch.setattr(Path, "stat", lambda self, *a, **kw: frozen if str(self) == str(obj) else real(self, *a, **kw))


def test_a_same_size_rewrite_within_a_tick_is_parsed_again(tmp_path, monkeypatch):
    obj = tmp_path / "a.obj"
    coff(obj, [("?alpha@@YAXXZ", 0), ("?beta@@YAXXZ", 4)])
    assert names(obj) == ["?alpha@@YAXXZ", "?beta@@YAXXZ"] and starts(obj) == {1: [0, 4]}
    size = obj.stat().st_size
    freeze_stat(monkeypatch, obj)
    coff(obj, [("?gamma@@YAXXZ", 0), ("?zeta@@YAXXZ", 8)])
    assert len(obj.read_bytes()) == size                              # the same size, the same identity
    assert names(obj) == ["?gamma@@YAXXZ", "?zeta@@YAXXZ"] and starts(obj) == {1: [0, 8]}


def test_a_younger_entry_whose_bytes_are_unchanged_is_reused(tmp_path, monkeypatch):
    obj = tmp_path / "a.obj"
    coff(obj, [("?alpha@@YAXXZ", 0)])
    first = layout(obj)
    assert layout(obj) is first                                     # read again, the same bytes: no new parse


def test_every_hit_reads_the_file_and_unchanged_bytes_are_not_parsed_again(tmp_path, monkeypatch):
    obj = tmp_path / "a.obj"
    coff(obj, [("?alpha@@YAXXZ", 0)])
    parses, reads = [], []
    parse, read = build._read_object_layout, Path.read_bytes
    monkeypatch.setattr(build, "_read_object_layout", lambda *a, **kw: parses.append(1) or parse(*a, **kw))
    monkeypatch.setattr(Path, "read_bytes", lambda self: reads.append(self) or read(self))
    first = layout(obj)
    assert layout(obj) is first and layout(obj) is first
    assert len(parses) == 1 and len(reads) == 3


def test_coarse_times_and_clock_skew_vouch_for_nothing(tmp_path, monkeypatch):
    # Sol r2: whole-second stat times and a clock ahead of the file system made an entry "settled" too early
    monkeypatch.setattr(build, "_hash_clock", lambda: time.time_ns() + 10 * build._HASH_TICK_NS)
    obj = tmp_path / "a.obj"
    coff(obj, [("?alpha@@YAXXZ", 0)])
    assert names(obj) == ["?alpha@@YAXXZ"]
    freeze_stat(monkeypatch, obj)
    coff(obj, [("?gamma@@YAXXZ", 0)])
    assert names(obj) == ["?gamma@@YAXXZ"]


def test_another_file_at_the_path_is_parsed_again_however_settled(tmp_path, monkeypatch):
    # a replacement of the same size and restored mtime is another inode (and ctime): the memo misses
    monkeypatch.setattr(build, "_hash_clock", lambda: time.time_ns() + 10 * build._HASH_TICK_NS)
    obj, other = tmp_path / "a.obj", tmp_path / "b.obj"
    coff(obj, [("?alpha@@YAXXZ", 0)])
    assert names(obj) == ["?alpha@@YAXXZ"]
    before = os.stat(obj)
    coff(other, [("?gamma@@YAXXZ", 0)])
    os.replace(other, obj)
    os.utime(obj, ns=(before.st_atime_ns, before.st_mtime_ns))
    assert (obj.stat().st_size, obj.stat().st_mtime_ns) == (before.st_size, before.st_mtime_ns)
    assert names(obj) == ["?gamma@@YAXXZ"]


def test_the_memo_is_bounded_and_clears(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "_LAYOUT_MEMO_SIZE", 2)
    objs = [tmp_path / f"{n}.obj" for n in "abc"]
    for obj in objs:
        coff(obj, [("?alpha@@YAXXZ", 0)])
        layout(obj)
    assert list(build._LAYOUT_MEMO) == [str(objs[1]), str(objs[2])]
    build._object_layout.cache_clear()
    assert not build._LAYOUT_MEMO


def test_the_uncached_reader_parses_the_file(tmp_path):
    obj = tmp_path / "a.obj"
    coff(obj, [("?alpha@@YAXXZ", 0)])
    stat = obj.stat()
    data, sections, symbols = build._object_layout.__wrapped__(str(obj), stat.st_mtime_ns, stat.st_size)
    assert data == obj.read_bytes() and sections[0]["name"] == ".text" and [s["name"] for s in symbols] == \
        ["?alpha@@YAXXZ"]
    assert not build._LAYOUT_MEMO

