"""link_census's per-object parse memo: a hit is what the parse returns; a changed object or parser misses."""
import os
import pickle
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import link_census as L  # noqa: E402
from test_link_census_prediction import coff, weak_aux  # noqa: E402

KINDS = {"references": L.object_references, "comdat_bodies": L.comdat_bodies, "symbols": L.object_symbols}


@pytest.fixture
def memo(tmp_path, monkeypatch):
    monkeypatch.setenv("LINK_CENSUS_MEMO", "on")
    monkeypatch.setattr(L, "MEMO", tmp_path / "memo")
    monkeypatch.setattr(L, "_MEMO_KEYS", {})
    return tmp_path / "memo"


def sample(path):
    return coff(path, [
        ("_f", 1, 0, L.EXTERNAL, []),
        ("_g", 0, 0, L.EXTERNAL, []),
        ("??_Ew", 0, 0, L.WEAK_EXTERNAL, [weak_aux(0)]),
    ], drectve=b"/alternatename:_a=_f /INCLUDE:_g ")


@pytest.mark.parametrize("kind", sorted(KINDS))
def test_a_hit_returns_what_the_parse_returns(memo, tmp_path, kind):
    obj = sample(tmp_path / "a.obj")
    computed = KINDS[kind](obj)
    first, hit = L.memo_parse(kind, obj)
    assert (first, hit) == (computed, False)
    again, hit = L.memo_parse(kind, obj)
    assert hit and again == computed and type(again) is type(computed)


def test_a_changed_object_misses_and_its_old_entry_stays_its_own(memo, tmp_path):
    obj = sample(tmp_path / "a.obj")
    before = L.memo_parse("symbols", obj)[0]
    coff(obj, [("_h", 1, 0, L.EXTERNAL, [])])
    after, hit = L.memo_parse("symbols", obj)
    assert not hit and after == L.object_symbols(obj) and after != before
    sample(obj)
    assert L.memo_parse("symbols", obj) == (before, True)


def test_a_changed_parser_misses(memo, tmp_path, monkeypatch):
    obj = sample(tmp_path / "a.obj")
    code = tmp_path / "code"
    code.mkdir()
    (code / "link_census.py").write_text("one parser\n")
    monkeypatch.setattr(L, "MEMO_CODE_DIR", code)
    assert L.memo_parse("references", obj)[1] is False
    assert L.memo_parse("references", obj)[1] is True
    (code / "link_census.py").write_text("another parser\n")
    monkeypatch.setattr(L, "_MEMO_KEYS", {})
    assert L.memo_parse("references", obj)[1] is False


def test_a_corrupt_entry_recomputes_and_is_replaced(memo, tmp_path):
    obj = sample(tmp_path / "a.obj")
    L.memo_parse("comdat_bodies", obj)
    [entry] = list(memo.rglob("*.pickle"))
    entry.write_bytes(b"torn")
    assert L.memo_parse("comdat_bodies", obj) == (L.comdat_bodies(obj), False)
    assert pickle.loads(entry.read_bytes()) == L.comdat_bodies(obj)


def test_a_failing_parse_is_never_stored(memo, tmp_path):
    bad = tmp_path / "bad.obj"
    bad.write_bytes(b"\x4c\x01\x01\x00")
    with pytest.raises(L.MissingObject):
        L.memo_parse("references", bad)
    with pytest.raises(L.MissingObject):
        L.memo_parse("references", tmp_path / "gone.obj")
    assert L.memo_parse("comdat_bodies", tmp_path / "gone.obj") == ([], False)  # comdat_bodies' own rule
    assert not list(memo.rglob("*.pickle"))


def test_memo_off_stores_nothing(memo, tmp_path, monkeypatch):
    monkeypatch.setenv("LINK_CENSUS_MEMO", "off")
    obj = sample(tmp_path / "a.obj")
    assert L.memo_parse("symbols", obj) == (L.object_symbols(obj), False)
    assert L.memo_parse("symbols", obj)[1] is False and not memo.exists()


def test_prune_drops_other_code_and_unused_entries(memo, tmp_path):
    obj = sample(tmp_path / "a.obj")
    L.memo_parse("symbols", obj)
    stale = memo / "symbols-0000000000000000" / "ab" / "x.pickle"
    stale.parent.mkdir(parents=True)
    stale.write_bytes(b"")
    [entry] = list(L._memo_dir("symbols").rglob("*.pickle"))
    L.prune_memo()
    assert entry.exists() and not stale.parent.parent.exists()
    os.utime(entry, (0, 0))
    L.prune_memo()
    assert not entry.exists()
