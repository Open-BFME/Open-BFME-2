#!/usr/bin/env python3
"""Tests for tools/stale_verdicts.py classification.

A generator once wrote a literal backspace where the dependency regex's
word boundary belonged; every `cites` row vanished and the tool reported a
clean backlog. These pin the classification on small fixtures.
"""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import re_log  # noqa: E402
import stale_verdicts  # noqa: E402

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


@pytest.fixture
def tree(tmp_path, monkeypatch):
    log = tmp_path / "reverse" / "re_attempts.log"
    log.parent.mkdir(parents=True)
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()

    def write(log_rows, ledger_rows):
        log.write_bytes("".join("\t".join(r) + "\n" for r in log_rows).encode("utf-8"))
        (log.parent / "functions.csv").write_bytes((HEADER + "".join(ledger_rows)).encode("utf-8"))
        re_log._reset()
    yield write
    re_log._reset()


def kinds(rows):
    return {(row["kind"], row["symbol"]) for row in rows}


def test_each_kind_is_classified(tree):
    tree([("?a@@YAXXZ", "0x00001000", "8", "blocked", "wall"),
          ("?d_00001100@@YAXXZ", "0x00001100", "8", "blocked", "wall"),
          ("?d_0000ABCD@@YAXXZ", "0x0000ABCD", "8", "blocked", "wall"),
          ("?old@@YAXXZ", "0x00001200", "8", "blocked", "wall"),
          ("?c@@YAXXZ", "0x00001300", "8", "blocked", "unresolved Seek 6150C0"),
          ("?e@@YAXXZ", "0x00001400", "8", "blocked", "wallpaper at 0x6150C0")],
         ["?a@@YAXXZ,,0x00001000,8,Code/a.cpp,matched,\n",
          "?real@@YAXXZ,,0x00001100,8,Code/a.cpp,matched,\n",
          "?real2@@YAXXZ,,0x0000ABCD,8,Code/a.cpp,matched,\n",
          "?new@@YAXXZ,,0x00001200,8,Code/a.cpp,matched,\n",
          "?Seek@@YAXXZ,,0x006150C0,221,Code/chunkio.cpp,matched,\n"])
    assert kinds(stale_verdicts.scan()) == {
        ("landed", "?a@@YAXXZ"),
        ("converted", "?d_00001100@@YAXXZ"),
        ("converted", "?d_0000ABCD@@YAXXZ"),
        ("renamed", "?old@@YAXXZ"),
        ("cites", "?c@@YAXXZ"),
    }


def test_the_dependency_regex_has_no_control_characters():
    assert not any(ord(c) < 32 for c in stale_verdicts._DEPENDENCY.pattern)
