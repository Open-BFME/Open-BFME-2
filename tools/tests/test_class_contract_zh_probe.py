"""The Zero Hour layout probe sets STLport up for its PreRTS.h attempt only.

`zh_layout` tries the ZH header alone, then again behind `PreRTS.h`. The second
attempt reused the same flags, which set no STLport up, so `#include <list>`
resolved to MSVC 7.1's own STL and collided inside the compiler's own headers:
`xhash(179): error C2955: 'std::list': use of class template requires template
argument list`. Every class whose ZH header needs PreRTS.h failed that way - 57
of them, all reporting the same three error codes - so the ZH rule never saw a
layout for them.

The include goes on the fallback attempt only, so a class that already compiles
from its header alone is decided exactly as before. These checks record that
split without needing the toolchain, by watching the flags the probe asks for.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract


class Builder:
    _ZH_FLAGS = ("-DWIN32", "-Ireference/zh/Include")

    def __init__(self, stlport):
        self._stlport = stlport

    def stlport_include_dir(self):
        return self._stlport


@pytest.fixture
def probe(tmp_path, monkeypatch):
    """Drive zh_layout against a fake ZH tree, recording each compile's flags."""
    zh = tmp_path / "zh"
    (zh / "GameLogic").mkdir(parents=True)
    (zh / "GameLogic" / "AI.h").write_text("class AIGroup : public Snapshot {\n int x;\n};\n")
    stlport = tmp_path / "stlport"
    stlport.mkdir()
    monkeypatch.setattr(contract.class_layouts, "CACHE", tmp_path / "cache")
    monkeypatch.setattr(contract, "ROOT", tmp_path)

    def run(results, stlport_dir=stlport):
        calls = []
        def fake_compile(rel, builder, flag, flags):
            calls.append({"source": (tmp_path / rel).read_text(), "flags": list(flags)})
            outcome = results[len(calls) - 1]
            if isinstance(outcome, Exception):
                raise outcome
            return outcome
        monkeypatch.setattr(contract.class_layouts, "compile_layouts", fake_compile)
        builder = Builder(str(stlport_dir) if stlport_dir else None)
        monkeypatch.setattr(builder.__class__, "ZH_REFERENCE_ROOT", str(zh), raising=False)
        got = contract.zh_layout("AIGroup", builder)
        return got, calls
    return run


LAYOUT = {"AIGroup": {"size": 8, "key": "class", "bases": [["Snapshot", 0]], "fields": []}}


def test_the_first_attempt_has_no_stlport_and_no_prelude(probe):
    got, calls = probe([LAYOUT])
    assert len(calls) == 1, "a header that compiles alone must not be retried"
    assert "PreRTS.h" not in calls[0]["source"]
    assert not [f for f in calls[0]["flags"] if "stlport" in f.lower()]
    assert got["layout"]["size"] == 8


def test_the_fallback_adds_prelude_and_the_stlport_include(probe):
    got, calls = probe([RuntimeError("compile failed: C2955"), LAYOUT])
    assert len(calls) == 2
    assert "PreRTS.h" in calls[1]["source"]
    stl = [f for f in calls[1]["flags"] if "stlport" in f.lower()]
    assert len(stl) == 1 and stl[0].startswith("-I"), stl
    assert calls[1]["flags"][:len(Builder._ZH_FLAGS)] == list(Builder._ZH_FLAGS), \
        "the ZH flags must be kept, with the include appended"
    assert got["layout"]["size"] == 8


def test_a_missing_stlport_tree_leaves_the_fallback_as_it_was(probe, tmp_path):
    got, calls = probe([RuntimeError("boom"), LAYOUT], stlport_dir=tmp_path / "absent")
    assert len(calls) == 2
    assert not [f for f in calls[1]["flags"] if "stlport" in f.lower()]


def test_a_builder_without_the_helper_still_works(probe, tmp_path):
    """stlport_include_dir is read defensively; an older builder must not crash the probe."""
    got, calls = probe([RuntimeError("boom"), LAYOUT], stlport_dir=None)
    assert len(calls) == 2 and got["layout"]["size"] == 8


def test_both_attempts_failing_reports_the_last_error(probe):
    got, calls = probe([RuntimeError("first"), RuntimeError("second: C2955")])
    assert len(calls) == 2
    assert "layout" not in got and "second" in got["error"]
