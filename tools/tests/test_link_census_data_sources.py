"""Data providers enter the census without becoming function ledger rows
(ported from Open-BFME-1's test_link_census_data_sources.py; its first case
reads two of Open-BFME-1's own data rows, so here it uses synthetic providers)."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows  # noqa: E402
import link_census as census  # noqa: E402


@pytest.fixture(autouse=True)
def isolated_data_ledger(tmp_path, monkeypatch):
    # Synthetic census/order fixtures must not inherit live repository data
    # providers. Tests of populated/malformed data rows still supply their own
    # rows/path and exercise the unchanged real data loader and byte gate.
    import data_rows
    empty = tmp_path / "data_rows.csv"
    empty.write_bytes((data_rows.HEADER + "\n").encode())
    loader = data_rows.load
    monkeypatch.setattr(data_rows, "DATA_ROWS", empty)
    monkeypatch.setattr(data_rows, "load", lambda path=None: loader(path or data_rows.DATA_ROWS))


def test_an_empty_data_ledger_adds_no_compile_input_object_or_owner(monkeypatch):
    """With an explicitly empty ledger, no data providers enter the census."""
    assert data_rows.DATA_ROWS.read_bytes() == (data_rows.HEADER + "\n").encode()
    rows = [{"name": "code", "target_rva": "0x00001000", "source": "Code/GameEngine/Source/Common/A.cpp"},
            {"name": "more", "target_rva": "0x00001010", "source": "Code/GameEngine/Source/Common/A.cpp"}]
    before = [dict(row) for row in rows]
    assert census.data_sources() == []
    assert census.data_ledger() == []
    assert census.compile_sources(rows) == [census.ROOT / rows[0]["source"]]
    assert rows == before
    monkeypatch.setattr(census.build, "row_object", lambda row: Path("/o") / (Path(row["source"]).stem + ".obj"))
    assert census.link_order(rows, census.data_ledger()) == census.link_order(rows)
    monkeypatch.setattr(census, "object_current", lambda *a, **k: pytest.fail("checked a data provider"))
    census.verify_data_objects()  # header-only: nothing to prove, nothing refused


def test_data_objects_are_linked_once_and_checked_for_currency(monkeypatch, tmp_path):
    rows = [{"name": "code", "target_rva": "0x00001000", "source": "Code/shared.cpp"}]
    providers = [{"name": name, "address": address, "address_kind": "rva", "source": source, "status": "matched"}
                 for name, address, source in (("d0", "0x00F00000", "Code/shared.cpp"),
                                               ("d1", "0x00F00010", "Code/data.cpp"),
                                               ("d2", "0x00F00008", "Code/data.cpp"))]
    monkeypatch.setattr(data_rows, "load", lambda: providers)
    monkeypatch.setattr(census.build, "extract_lib_members", lambda rows: None)
    path = lambda source: tmp_path / (Path(source).stem + ".obj")
    monkeypatch.setattr(census.build, "obj_path", path)
    monkeypatch.setattr(census.build, "row_object", lambda row: path(row["source"]))
    path("shared").touch()
    path("data").touch()
    present, missing = census.objects(rows)
    assert present == [path("shared"), path("data")]
    assert missing == []
    assert census._object_sources(rows)[path("data")] == census.ROOT / "Code/data.cpp"
    assert census.compile_sources(rows) == [census.ROOT / "Code/shared.cpp", census.ROOT / "Code/data.cpp"]
    path("data").unlink()
    assert census.objects(rows) == ([path("shared")], [path("data")])


def test_data_provider_byte_failure_is_not_ignored(monkeypatch, tmp_path):
    monkeypatch.setattr(data_rows, "DATA_ROWS", tmp_path / "no_rows.csv")
    monkeypatch.setattr(census, "data_sources", lambda: [])

    def fail(*, compile):
        assert compile is False  # Never rebuild an object after the selected map.
        raise SystemExit("data bytes differ")
    monkeypatch.setattr(data_rows, "verify", fail)
    with pytest.raises(SystemExit, match="data bytes differ"):
        census.verify_data_objects()


def test_stale_data_provider_is_refused_before_byte_verification(monkeypatch, tmp_path):
    monkeypatch.setattr(data_rows, "DATA_ROWS", tmp_path / "no_rows.csv")
    monkeypatch.setattr(census, "data_sources", lambda: [census.ROOT / "Code/data.cpp"])
    monkeypatch.setattr(census.build, "compile_is_current", lambda source, obj, **kwargs: False)
    monkeypatch.setattr(census, "input_receipts", lambda: None)
    monkeypatch.setattr(data_rows, "verify", lambda **kwargs: pytest.fail("reached data byte verification"))
    with pytest.raises(SystemExit, match="data provider objects are missing or stale"):
        census.verify_data_objects()


def test_an_invalid_data_ledger_refuses_the_census(tmp_path, monkeypatch):
    """The census reads data rows only through the gate's integrity check: a
    ledger it cannot trust stops the run and the record, never silently
    links fewer objects."""
    bad = tmp_path / "data_rows.csv"
    bad.write_text("name\n")
    monkeypatch.setattr(data_rows, "DATA_ROWS", bad)
    with pytest.raises(SystemExit, match="invalid data rows"):
        census.verify_data_objects()
    with pytest.raises(SystemExit, match="invalid data rows"):
        census.record({"missing": 0}, [])
