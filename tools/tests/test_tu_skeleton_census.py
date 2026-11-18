"""`--queue --blockers`: the `headers` label, its include heuristic, and the census ranking."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import flag_defaults
import header_adopt_lane
import tu_skeleton as T


@pytest.mark.parametrize("text,expected", [
    ('#include "PreRTS.h"\n', True),
    ('#include "prerts.h"\n', True),
    ('#include "Common/Foo.h"\n', True),
    ('#include <GameLogic/Object.h>\n', True),
    ('#include "gameclient/x.h"\n', True),
    ('  #  include "WWMath/vector3.h"\n', True),
    ('#include "../../Include/Common/Foo.h"\n', False),
    ('#include "../Include/GameClient/x.h"\n', False),
    ('#include "ascii_string.h"\n#include "Bfme2Thing.h"\n', False),
    ('#include <vector>\n', False),
    ('int x;\n', False),
    ('// #include "PreRTS.h"\n', False),
])
def test_uses_zh_headers(text, expected):
    assert T.uses_zh_headers(text) is expected


ZH = '#include "PreRTS.h"\n'
OWN = '#include "../Include/a.h"\n'
TU, MIX, CLEAN, HDR, CLS, CLSHDR, GONE = ("Code/T.cpp", "Code/Mixed.cpp", "Code/Clean.cpp", "Code/Hdr.cpp",
                                          "Code/Cls.cpp", "Code/ClsHdr.cpp", "Code/Gone.cpp")


@pytest.fixture
def census(monkeypatch, tmp_path):
    texts = {TU: OWN, MIX: ZH, CLEAN: OWN, HDR: ZH, CLS: OWN, CLSHDR: ZH}
    for f, t in texts.items():
        (tmp_path / f).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / f).write_text(t)
    don = {f: [] for f in (TU, CLEAN, HDR, CLS, CLSHDR, GONE)}
    monkeypatch.setattr(T, "map_rows", lambda: [])
    monkeypatch.setattr(T, "skeleton", lambda tu: None)
    monkeypatch.setattr(T, "donors", lambda tu, sk: (don, {MIX: []}, {}))
    monkeypatch.setattr(header_adopt_lane, "registered", lambda: set())
    monkeypatch.setattr(header_adopt_lane, "view_signatures", lambda text: {})
    monkeypatch.setattr(header_adopt_lane, "tu_blockers",
                        lambda files, sigs, canon: {"Widget": ({}, [CLS, CLSHDR])})
    monkeypatch.setattr(flag_defaults, "overrides", lambda: {})
    return T.blocker_census(root=tmp_path, entries=[{"tu": TU}])


def test_labels(census):
    files = census["tus"][0]["files"]
    assert files[MIX] == ["mixed", "headers"]   # additive on mixed
    assert files[CLEAN] == ["clean"]
    assert files[HDR] == ["headers"]          # clean except for headers: never "clean"
    assert files[CLS] == ["class:Widget"]
    assert files[CLSHDR] == ["class:Widget", "headers"]   # additive
    assert files[GONE] == ["clean"]           # unreadable donor: no header verdict
    assert files[TU] == ["clean"]             # the TU file is not compared with itself


def test_histogram_and_counts(census):
    assert census["histogram"] == {"mixed": 1, "clean": 3, "class": 2, "headers": 3}
    assert census["tus"][0]["headers_donors"] == 3


def test_ranking_stable(census):
    assert census["classes"] == [{"class": "Widget", "tus": 1, "donors": 2, "exclusive_donors": 1,
                                  "tus_unblocked_alone": 0, "registered": False}]


def test_no_tu_file_means_no_headers(monkeypatch, tmp_path, census):
    (tmp_path / TU).unlink() if (tmp_path / TU).exists() else None
    cen = T.blocker_census(root=tmp_path, entries=[{"tu": TU}])
    assert all("headers" not in v for v in cen["tus"][0]["files"].values())


def test_report_mentions_headers(census, capsys):
    T.report_census(census)
    out = capsys.readouterr().out
    assert "headers" in out and "headers    3 donors  " + TU in out
