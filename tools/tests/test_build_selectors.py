"""build.selector_matcher selects exactly as `any(sel in text for sel in only)`, the
substring rule scoped builds have always used, and the scoped selections that use it
(verify_source_claims, _function_scope) keep exactly the sources and rows they did."""
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402


def test_the_matcher_is_the_substring_rule():
    rng = random.Random(20261030)
    alphabet = "ab/c._"
    texts = ["".join(rng.choice(alphabet) for _ in range(rng.randint(0, 12))) for _ in range(400)]
    for _ in range(300):
        only = ["".join(rng.choice(alphabet) for _ in range(rng.randint(0, 5)))
                for _ in range(rng.randint(1, 6))]
        match = build.selector_matcher(only)
        for text in texts:
            assert match(text) == any(sel in text for sel in only), (only, text)


def test_whole_paths_fragments_and_names():
    match = build.selector_matcher(["Code/A/B.cpp", "Thing", "B.c"])
    assert match("Code/A/B.cpp") and match("Code/A/B.cpp.bak")
    assert match("Code/X/B.cpp")                 # "B.c" is a fragment of it
    assert match("?f@Thing@@QAEXXZ")             # a name selector
    assert not match("Code/A/C.cpp") and not match("?g@Other@@QAEXXZ")
    # a path selector cannot be inside a text without "/"; an empty selector matches all
    assert not build.selector_matcher(["Code/A"])("CodeA")
    assert build.selector_matcher([""])("")


def test_function_scope_keeps_the_rows_any_selector_names():
    rows = [{"source": "Code/A/B.cpp", "name": "?a@@YAXXZ"},
            {"source": "Code/A/C.cpp", "name": "?f@Thing@@QAEXXZ"},
            {"source": "Code/A/B.cpp", "name": "?b@@YAXXZ"},
            {"source": "Code/D.cpp", "name": "?d@@YAXXZ"}]
    for only in (["Code/A/B.cpp", "Thing"], ["A/"], ["?d"], ["Code/E.cpp"]):
        assert build._function_scope(rows, only) == [
            r for r in rows if any(s in r["source"] or s in r["name"] for s in only)], only


def test_scoped_source_claims_select_the_same_files(tmp_path, monkeypatch):
    for rel in ("Code/A/B.cpp", "Code/A/C.cpp", "Code/D.cpp"):
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text("// fixture\n")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: [
        {"source": "Code/A/B.cpp", "name": "?a@@YAXXZ"}, {"source": "Code/A/C.cpp", "name": "?c@@YAXXZ"},
        {"source": "Code/D.cpp", "name": "?d@@YAXXZ"}])
    monkeypatch.setattr(build, "load_unclaimed_sources", lambda: set())
    import data_rows
    monkeypatch.setattr(data_rows, "load", lambda: [])
    seen = []
    monkeypatch.setattr("builtins.print", lambda *a, **k: seen.append(" ".join(map(str, a))))
    build.verify_source_claims(["Code/A/"])
    assert seen[-1] == "Source claims: OK (2 sources, scoped byte-verified)"
    build.verify_source_claims(["Code/D.cpp", "Code/A/B.cpp"])
    assert seen[-1] == "Source claims: OK (2 sources, scoped byte-verified)"
