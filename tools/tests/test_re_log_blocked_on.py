#!/usr/bin/env python3
"""Tests for the landing side of re_log: blocked-on=, is_unblocked, cites, append.

ChunkLoadClass::Seek (0x006150C0) landed with five `blocked` rows as the log's
last word, and two motion-channel constructors stayed parked behind every
untried candidate citing "unresolved ChunkLoadClass::Seek 6150C0" -- nothing
told the queue their wall was gone. A deferral that names its blocker with
`blocked-on=` is released once that RVA is matched; free-text mentions are only
ever reported, never acted on.
"""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import re_log  # noqa: E402

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


@pytest.fixture
def log(tmp_path, monkeypatch):
    path = tmp_path / "reverse" / "re_attempts.log"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("", encoding="utf-8")
    (path.parent / "functions.csv").write_text(HEADER, encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    re_log._reset()
    try:
        yield path
    finally:
        re_log._reset()


def write(log, *rows):
    log.write_bytes(
        "".join("\t".join(row) + "\n" for row in rows).encode("utf-8"))
    re_log._reset()


def match(log, *rvas):
    (log.parent / "functions.csv").write_text(
        HEADER + "".join(f"?f{rva:x}@@YAXXZ,,0x{rva:08X},8,Code/a.cpp,matched,\n"
                         for rva in rvas), encoding="utf-8")
    re_log._reset()


def test_blocked_on_reads_one_or_several_rvas():
    assert re_log.blocked_on("wall blocked-on=0x006150C0 t=7") == [0x6150C0]
    assert re_log.blocked_on("blocked-on=0x10,0x20") == [0x10, 0x20]
    assert re_log.blocked_on("unresolved Seek 6150C0") == []


def test_a_deferral_stays_deferred_while_its_blocker_is_unmatched(log):
    write(log, ("??0Enc1@@QAE@XZ", "0x001A4673", "18", "blocked",
                "factory exact; blocked-on=0x006150C0"))
    assert re_log.is_deferred("??0Enc1@@QAE@XZ", 0x1A4673)
    assert not re_log.is_unblocked("??0Enc1@@QAE@XZ", 0x1A4673)


def test_a_deferral_is_released_once_its_blocker_is_matched(log):
    write(log, ("??0Enc1@@QAE@XZ", "0x001A4673", "18", "blocked",
                "factory exact; blocked-on=0x006150C0"))
    match(log, 0x6150C0)
    assert re_log.is_unblocked("??0Enc1@@QAE@XZ", 0x1A4673)
    assert not re_log.is_deferred("??0Enc1@@QAE@XZ", 0x1A4673)


def test_every_named_blocker_must_be_matched(log):
    write(log, ("?f@@YAXXZ", "0x00001000", "8", "blocked",
                "blocked-on=0x00002000,0x00003000"))
    match(log, 0x2000)
    assert re_log.is_deferred("?f@@YAXXZ", 0x1000)


def test_free_text_mention_never_releases(log):
    write(log, ("??0Enc1@@QAE@XZ", "0x001A4673", "18", "blocked",
                "unresolved ChunkLoadClass::Seek 6150C0"))
    match(log, 0x6150C0)
    assert re_log.is_deferred("??0Enc1@@QAE@XZ", 0x1A4673)


def test_cites_reports_free_text_and_symbol_mentions_but_not_lookalikes(log):
    write(log,
          ("??0Enc1@@QAE@XZ", "0x001A4673", "18", "blocked",
           "unresolved ChunkLoadClass::Seek 6150C0"),
          ("?a@@YAXXZ", "0x00002000", "8", "partial",
           "calls ?Seek@ChunkLoadClass@@QAEKK@Z score=0.5 stash=x"),
          ("?b@@YAXXZ", "0x00003000", "8", "blocked", "jump to 0x16150C0"),
          ("?c@@YAXXZ", "0x00004000", "8", "converted", "used 0x006150C0"),
          ("?Seek@ChunkLoadClass@@QAEKK@Z", "0x006150C0", "221", "blocked",
           "own wall at 6150C0"))
    found = re_log.cites(0x6150C0, "?Seek@ChunkLoadClass@@QAEKK@Z")
    assert [(name, at) for name, at, _status, _text in found] == [
        ("?a@@YAXXZ", 0x2000), ("??0Enc1@@QAE@XZ", 0x1A4673)]


def test_append_writes_one_canonical_row_and_refreshes_the_index(log):
    write(log, ("?f@@YAXXZ", "0x00001000", "8", "blocked", "wall"))
    assert re_log.standing_status("?f@@YAXXZ", 0x1000) == "blocked"
    re_log.append("?f@@YAXXZ", "0x00001000", "8", "landed",
                  "add_match verified\tCode/a.cpp\n8B")
    assert log.read_bytes().endswith(
        b"?f@@YAXXZ\t0x00001000\t8\tlanded\tadd_match verified Code/a.cpp 8B\n")
    assert re_log.standing_status("?f@@YAXXZ", 0x1000) == "landed"
    assert not re_log.is_deferred("?f@@YAXXZ", 0x1000)


def test_a_gen_placeholder_is_not_the_blocker_landing(log):
    write(log, ("?f@@YAXXZ", "0x00001000", "8", "blocked", "blocked-on=0x00002000"))
    (log.parent / "functions.csv").write_text(
        HEADER + "?d_00002000@@YAXXZ,,0x00002000,8,Code/gen_asm/d.asm,matched,gen-dump\n",
        encoding="utf-8")
    re_log._reset()
    assert re_log.is_deferred("?f@@YAXXZ", 0x1000)
