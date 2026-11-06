"""A class-key change refuses rows that spell the key on a name back-reference.

The lane rewrites the spelled type, `U<scope>@@` -> `V<scope>@@`. MSVC also puts
a class-key letter in front of a *name* back-reference, so a name can carry the
old key in a place that substitution never reaches: `PAU1@` beside a spelled
`PAUCoord3D@@`, or `ABU0@` in a member of the class itself with no spelled
Coord3D anywhere. Rewriting only the spelled type leaves a name that is half
struct-keyed and half class-keyed, which no compiler emits and nothing in the
image carries - so the unit is refused and its rows named.

Every mangled name here is a real row from reverse/functions.csv.
"""
import csv
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as hal

COLUMNS = ["name", "demangled", "retail_rva", "size", "source", "status", "evidence"]


def rows(*names, source="Code/Unit.cpp"):
    return [dict(zip(COLUMNS, [n, "", "0x1000", "4", source, "matched", ""])) for n in names]


@pytest.mark.parametrize("name", [
    # a spelled Coord3D plus a back-reference to it
    "?Rva003AFA64FillUnitVector@@YAPAUCoord3D@@PAU1@@Z",
    "??$fill@PAUCoord3D@@U1@@_STL@@YAXPAUCoord3D@@0ABU1@@Z",
    "??$uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@@Z",
    "?getPlanarDirectionTo@Object@@QBEPAUCoord3D@@PAU2@PBV1@@Z",
    # Coord3D only as the enclosing scope: no spelled type for the pattern to find
    "?equals@Coord3D@@QBE_NABU0@@Z",
])
def test_a_back_referenced_key_is_refused(name):
    assert hal.key_backref_names(rows(name), "Coord3D", "U") == [name]


@pytest.mark.parametrize("name", [
    "?length@Coord3D@@QBEMXZ",                              # no key letter at all
    "?expandBy@Region3D@@QAEXABUCoord3D@@@Z",               # spelled once, no back-reference
    "??0Coord3D@@QAE@ABUCoord3D@@@Z",                       # spelled twice, still no back-reference
])
def test_a_plainly_spelled_row_is_renameable(name):
    assert hal.key_backref_names(rows(name), "Coord3D", "U") == []


def test_the_other_keys_back_references_are_not_our_problem():
    """Flipping struct->class looks only for `U<digit>@`; a `V<digit>@` is already right."""
    name = "?GetXVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z"
    assert hal.key_backref_names(rows(name), "Coord3D", "U") == []
    assert hal.key_backref_names(rows(name), "Coord3D", "V") == [name]


def test_a_similarly_named_class_is_not_matched():
    """`UICoord3D@@` is ICoord3D, a different class; neither form may match Coord3D."""
    for name in ["??4ICoord3D@@QAEAAU0@ABU0@@Z", "??6@YAAAVDebug@@AAV0@ABUICoord3D@@@Z"]:
        assert hal.key_backref_names(rows(name), "Coord3D", "U") == []


def test_ledger_renames_refuses_instead_of_half_flipping(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    with ledger.open("w", newline="", encoding="utf-8") as handle:
        out = csv.DictWriter(handle, COLUMNS)
        out.writeheader()
        out.writerows(rows("?Rva003AFA64FillUnitVector@@YAPAUCoord3D@@PAU1@@Z",
                           "?expandBy@Region3D@@QAEXABUCoord3D@@@Z"))
    monkeypatch.setattr(hal, "LEDGER", ledger)
    renames, why = hal.ledger_renames("Code/Unit.cpp", "Coord3D", "class")
    assert renames == [], "nothing may be renamed while one row cannot be"
    assert "back-reference" in why and "FillUnitVector" in why


def test_a_unit_with_only_spelled_rows_still_renames(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    with ledger.open("w", newline="", encoding="utf-8") as handle:
        out = csv.DictWriter(handle, COLUMNS)
        out.writeheader()
        out.writerows(rows("?expandBy@Region3D@@QAEXABUCoord3D@@@Z",
                           "?isInRegionNoZ@Region3D@@QBE_NPBUCoord3D@@@Z"))
    monkeypatch.setattr(hal, "LEDGER", ledger)
    renames, why = hal.ledger_renames("Code/Unit.cpp", "Coord3D", "class")
    assert why is None
    assert renames == [("?expandBy@Region3D@@QAEXABUCoord3D@@@Z",
                        "?expandBy@Region3D@@QAEXABVCoord3D@@@Z"),
                       ("?isInRegionNoZ@Region3D@@QBE_NPBUCoord3D@@@Z",
                        "?isInRegionNoZ@Region3D@@QBE_NPBVCoord3D@@@Z")]


def test_blockers_name_the_unit_and_are_keyed_by_source(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    with ledger.open("w", newline="", encoding="utf-8") as handle:
        out = csv.DictWriter(handle, COLUMNS)
        out.writeheader()
        out.writerows(rows("?Rva003AFA64FillUnitVector@@YAPAUCoord3D@@PAU1@@Z", source="Code/Bad.cpp"))
        out.writerows(rows("?expandBy@Region3D@@QAEXABUCoord3D@@@Z", source="Code/Good.cpp"))
    monkeypatch.setattr(hal, "LEDGER", ledger)
    got = hal.key_backref_blockers(["Code/Bad.cpp", "Code/Good.cpp"], "Coord3D", "class")
    assert set(got) == {"Code/Bad.cpp"}
    assert "back-reference" in got["Code/Bad.cpp"]
