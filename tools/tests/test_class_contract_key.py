"""The class-key comes from retail's export table before the ledger's own vote.

The ledger rule is a majority of names we wrote, so it cannot settle a key our
canonical header already decided: a struct-keyed header makes every including
unit emit `U` rows, which outvote the few `V` rows and re-decide the key as
struct. Retail's exports are outside that loop. Coord3D is the live case - 15
`V` exports against 461 `U` ledger rows - and it blocked the real link while
the vote kept choosing struct.
"""
import csv
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract


@pytest.fixture
def exports(tmp_path, monkeypatch):
    """Write an export table and point the module at it."""
    def write(names):
        path = tmp_path / "exports.csv"
        with path.open("w", newline="", encoding="utf-8") as handle:
            out = csv.writer(handle)
            out.writerow(["ordinal", "rva", "target_rva", "section", "kind", "name"])
            for i, name in enumerate(names, 1):
                out.writerow([i, f"0x{i:08X}", "", ".text", "code", name])
        monkeypatch.setattr(contract, "EXPORTS", path)
        return path
    return write


def test_export_spellings_are_counted_per_key(exports):
    exports(["??0Coord3D@@QAE@ABVCoord3D@@@Z", "?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z",
             "??0Thing@@QAE@ABUOther@@@Z"])
    assert contract.export_key("Coord3D") == {"class": 2}
    assert contract.export_key("Other") == {"struct": 1}


def test_a_name_retail_never_exports_has_no_export_evidence(exports):
    exports(["??0Coord3D@@QAE@ABVCoord3D@@@Z"])
    assert contract.export_key("Unexported") == {}


def test_a_missing_export_table_costs_only_this_rule(tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "EXPORTS", tmp_path / "absent.csv")
    assert contract.export_key("Coord3D") == {}


def test_the_scope_is_matched_innermost_first_and_not_as_a_prefix(exports):
    exports(["?f@@YAXABVInner@Outer@@@Z", "?g@@YAXABVInnerExtra@@@Z"])
    assert contract.export_key("Outer::Inner") == {"class": 1}
    assert contract.export_key("Inner") == {}, "Inner@Outer@@ is not a bare Inner@@"


def test_exports_outrank_the_ledger_vote(exports):
    """The Coord3D shape: a large U-keyed ledger majority, V-keyed exports."""
    exports(["??0Coord3D@@QAE@ABVCoord3D@@M@Z"] * 15)
    rows = [{"name": "?f@@YAXPBUCoord3D@@@Z"}] * 461 + [{"name": "?g@@YAXPBVCoord3D@@@Z"}] * 29
    assert contract.ledger_key("Coord3D", rows) == {"struct": 461, "class": 29}
    assert contract.export_key("Coord3D") == {"class": 15}


def test_an_export_table_that_spells_both_keys_is_queued_not_silently_voted(exports):
    exports(["?f@@YAXABVAmbi@@@Z", "?g@@YAXABUAmbi@@@Z", "?h@@YAXABUAmbi@@@Z"])
    got = contract.export_key("Ambi")
    assert got == {"class": 1, "struct": 2}
    assert len(got) > 1, "decide() must queue this rather than treat it as settled"
