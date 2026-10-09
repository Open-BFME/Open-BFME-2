"""tools/legacy_va_pins.py rewrites a VA-written function pin only on a matched row's evidence."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import legacy_va_pins as tool  # noqa: E402

BASE = 0x400000
CODE, DATA = 0x60000020, 0xC0000040
# .text RVA 0x1000-0x10000, .rdata RVA 0x400000-0x402000
SECTIONS = [(".text", BASE + 0x1000, BASE + 0x10000, CODE), (".rdata", BASE + 0x400000, BASE + 0x402000, DATA)]


def rows(*specs):
    return [{"name": name, "target_rva": rva, "notes": notes} for name, rva, notes in specs]


def test_only_a_function_pin_whose_va_starts_its_own_matched_row_is_rewritten():
    pins = [("??1X@@QAE@XZ", "0x00401010"),   # (a) row, (b) .rdata, (c) its row starts at 0x1010
            ("?alias@@YAXXZ", "0x00401020"),  # (c) through the row's object symbol
            ("??1Y@@QAE@XZ", "0x00401030"),   # (a) decorated, (b), but another name's row is there
            ("?z@@YAXXZ", "0x00401040"),      # (a) has a row, elsewhere
            ("_bfmeVftSF", "0x00401050"),     # not a function: a C name with no row
            ("?d@@3HA", "0x00401060"),        # data decoration
            ("?f@@YAXXZ", "0x00001070")]      # (b) fails: the RVA reading is code
    matched = rows(("??1X@@QAE@XZ", "0x00001010", ""), ("?owner@@YAXXZ", "0x00001020", "object-symbol=?alias@@YAXXZ"),
                   ("?other@@YAXXZ", "0x00001030", ""), ("?z@@YAXXZ", "0x00002000", ""),
                   ("?f@@YAXXZ", "0x00001070", ""))
    symbol = {"?owner@@YAXXZ": "?alias@@YAXXZ"}
    rewrites, unresolved = tool.plan(pins, matched, SECTIONS, lambda r: symbol.get(r["name"], r["name"]))
    assert [(name, old, new) for name, old, new, _ in rewrites] == [
        ("??1X@@QAE@XZ", "0x00401010", "0x00001010"), ("?alias@@YAXXZ", "0x00401020", "0x00001020")]
    assert [name for name, _, _ in unresolved] == ["??1Y@@QAE@XZ", "?z@@YAXXZ"]
    reasons = dict((name, why) for name, _, why in unresolved)
    assert "0x00001030 is the matched start of ?other@@YAXXZ" in reasons["??1Y@@QAE@XZ"]
    assert "its rows start at 0x00002000" in reasons["?z@@YAXXZ"]


def test_decorated_functions():
    assert tool.decorated_function("??1Rva0033DDA1E4@@QAE@XZ")
    assert tool.decorated_function("?rva00A00062@@YIXPAURva00A00062Sub@@HHH@Z")
    assert tool.decorated_function("_DirectInputCreateA@16")
    assert not tool.decorated_function("?TheGameLogic@@3PAVGameLogic@@A")
    assert not tool.decorated_function("??_7AptError@@6B@")
    assert not tool.decorated_function("_bfmeVftSF")
    assert not tool.decorated_function("?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB")


def test_apply_changes_only_the_address_and_refuses_a_missing_line():
    text = "name,address,notes\n??1X@@QAE@XZ,0x00401010,a, b\n?y@@YAXXZ,0x00401010,c\n"
    rewrite = [("??1X@@QAE@XZ", "0x00401010", "0x00001010", "row")]
    assert tool.apply(text, rewrite) == text.replace("0x00401010,a", "0x00001010,a")
    with pytest.raises(SystemExit, match="not found"):
        tool.apply(text, [("?gone@@YAXXZ", "0x00401010", "0x00001010", "row")])
