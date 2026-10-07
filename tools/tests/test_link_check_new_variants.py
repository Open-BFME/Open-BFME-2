"""Admission distinguishes unchanged census debt from newly introduced bodies."""
import sys
from pathlib import Path
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C


def facts(monkeypatch, digest="old", verdict=None):
    monkeypatch.setattr(C.link_census, "object_facts",
                        lambda obj, truth: ([("f", digest, 10, verdict)], [], [], []))


def census():
    return {"objects": ["a.obj", "b.obj"],
            "comdat": {"f": [(0, "old", None), (1, "kept", None)]},
            "common_schema": C.COMMON_SCHEMA, "common": {}, "alternates": {}}


@pytest.mark.parametrize("verdict", [None, "unknown", "wrong"])
def test_unchanged_self_copy_is_existing_admission_debt(monkeypatch, verdict):
    facts(monkeypatch, verdict=verdict)
    assert C.new_variants(Path("a.obj"), census(), None, {"f": {"old"}}) == []


@pytest.mark.parametrize("verdict", [None, "unknown", "wrong"])
def test_changed_self_copy_is_still_refused(monkeypatch, verdict):
    facts(monkeypatch, "new", verdict)
    assert C.new_variants(Path("a.obj"), census(), None, {"f": {"old"}}) == ["f"]


def test_new_file_has_no_self_debt_exemption(monkeypatch):
    facts(monkeypatch, "new", "wrong")
    assert C.new_variants(Path("new.obj"), census(), None) == ["f"]


def test_wrong_body_is_refused_even_without_an_existing_other_copy(monkeypatch):
    facts(monkeypatch, "new", "wrong")
    ix = census()
    ix["comdat"] = {}
    assert C.new_variants(Path("new.obj"), ix, None) == ["f"]


def test_proven_retail_copy_is_allowed(monkeypatch):
    facts(monkeypatch, "new", "retail")
    assert C.new_variants(Path("new.obj"), census(), None) == []


@pytest.mark.parametrize("digest, expected", [("old", 0), ("new", 1)])
def test_cli_uses_census_self_copy_before_refresh(monkeypatch, tmp_path, digest, expected):
    ix = census()
    marker = tmp_path / "index.pkl"
    marker.touch()
    monkeypatch.setattr(C, "INDEX", marker)
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "resolve", lambda path, index: (path, Path("a.obj")))
    monkeypatch.setattr(C.link_census, "ledger", lambda: None)
    monkeypatch.setattr(C.link_census, "RetailTruth", lambda rows: None)
    def refresh(index, objects, truth):
        index["comdat"]["f"][0] = (0, digest, "wrong")
    monkeypatch.setattr(C, "refresh", refresh)
    facts(monkeypatch, digest, "wrong")
    assert C.main(["--new-variants", "a.cpp"]) == expected
