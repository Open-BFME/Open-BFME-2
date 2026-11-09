"""A DIR32 site past a row's first non-relocation difference binds nothing.

Past that byte the object no longer lines up with retail, so the retail dword at
the site is not an address: it gave the ledger rows at addresses like 0xD8058B24.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import build
import data_ledger

SYMBOL = "?g_sample@@3HA"
ADDRESS = 0x00C00000          # a VA; bound at ADDRESS - IMAGE_BASE


class Present:
    def exists(self):
        return True


def bound(monkeypatch, target, body, relocs):
    monkeypatch.setattr(data_ledger, "retail_sections", lambda: [(".text", 0, 0, 0)])
    monkeypatch.setattr(data_ledger, "layout", lambda obj: (b"", [], []))
    monkeypatch.setattr(data_ledger, "local_names", lambda obj: set())
    monkeypatch.setattr(build, "row_object", lambda row: Present())
    monkeypatch.setattr(build, "ledger_object_symbol", lambda row: row["name"])
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: target)
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda obj, symbol, size: (body, relocs))
    row = {"name": "row", "source": "Code/row.cpp", "target_rva": "0x1000", "target_size": str(len(target))}
    bind, _defs, _missing, refsrc = data_ledger.collect_uncached([row])
    return {base: sorted(names) for base, names in bind.items()}, sorted(refsrc)


def site(address=ADDRESS):
    return struct.pack("<I", address)


ALONE = {ADDRESS - data_ledger.IMAGE_BASE: [(SYMBOL, None)]}


def test_identical_bytes_bind(monkeypatch):
    target = b"\xa1" + site() + b"\xc3"
    body = b"\xa1" + site(0) + b"\xc3"
    assert bound(monkeypatch, target, body, [(1, data_ledger.DIR32, SYMBOL)]) == (ALONE, [SYMBOL])


def test_difference_after_the_site_still_binds(monkeypatch):
    target = b"\xa1" + site() + b"\xc3"
    body = b"\xa1" + site(0) + b"\xcc"
    assert bound(monkeypatch, target, body, [(1, data_ledger.DIR32, SYMBOL)]) == (ALONE, [SYMBOL])


def test_difference_before_the_site_binds_nothing(monkeypatch):
    target = b"\xa1" + site() + b"\xc3"
    body = b"\xa0" + site(0) + b"\xc3"
    assert bound(monkeypatch, target, body, [(1, data_ledger.DIR32, SYMBOL)]) == ({}, [])


def test_only_the_sites_past_the_difference_go(monkeypatch):
    later = "?g_later@@3HA"
    target = b"\xa1" + site() + b"\x90" + b"\xa1" + site(0x00D00000)
    body = b"\xa1" + site(0) + b"\xcc" + b"\xa1" + site(0)
    relocs = [(1, data_ledger.DIR32, SYMBOL), (7, data_ledger.DIR32, later)]
    assert bound(monkeypatch, target, body, relocs) == (ALONE, [SYMBOL])


def test_another_relocation_kind_is_not_a_difference(monkeypatch):
    rel32 = 0x14
    target = b"\xe8" + site(0x12345678) + b"\xa1" + site()
    body = b"\xe8" + site(0) + b"\xa1" + site(0)
    relocs = [(1, rel32, "?callee@@YAXXZ"), (6, data_ledger.DIR32, SYMBOL)]
    assert bound(monkeypatch, target, body, relocs) == (ALONE, [SYMBOL])


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
