"""The shared inventory is a content cache, never an mtime-based declaration gate."""
import os
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_inventory as inventory
import class_views
import picker_cache


@pytest.fixture
def cached(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    monkeypatch.setattr(inventory, "HEADS", picker_cache.FileMemo("test-heads", inventory.CODE))
    monkeypatch.setattr(inventory, "VIEWS", picker_cache.FileMemo("test-views", inventory.CODE))
    calls = []
    parse = inventory.parse
    monkeypatch.setattr(inventory, "parse", lambda text: calls.append(text) or parse(text))
    return calls


def test_shared_cache_reuses_bodies_and_only_reparses_changed_contents(tmp_path, cached):
    source = tmp_path / "a.cpp"
    source.write_text("class Alpha { int x; };\n")
    first = inventory.inventory(["a.cpp"], tmp_path)
    assert list(first) == ["Alpha"]
    assert inventory.inventory(["a.cpp"], tmp_path, {"Alpha"}) == first
    assert len(cached) == 1
    old_stat = source.stat()
    source.write_text("class Bravo { int y; };\n")  # Same size and timestamps must still invalidate.
    os.utime(source, ns=(old_stat.st_atime_ns, old_stat.st_mtime_ns))
    assert set(inventory.inventory(["a.cpp"], tmp_path)) == {"Bravo"}
    assert len(cached) == 2
    source.unlink()
    assert inventory.inventory(["a.cpp"], tmp_path) == {}
    source.write_text("class Alpha { int x; };\n")
    assert inventory.inventory(["a.cpp"], tmp_path) == first
    assert len(cached) == 2


def test_single_class_prefilter_does_not_parse_unrelated_files(tmp_path, cached):
    for name in ["Alpha", "Bravo"]:
        (tmp_path / (name + ".cpp")).write_text(f"class {name} {{ int x; }};\n")
    assert set(inventory.inventory(["Alpha.cpp", "Bravo.cpp"], tmp_path, {"Alpha"})) == {"Alpha"}
    assert len(cached) == 1
    assert "Alpha" in cached[0]


def test_scope_template_and_normalized_layout_identity_match_the_existing_survey(tmp_path, cached):
    text = '''// class Comment { int x; };
class A::B { class Nested { int a; }; int x; };
void f() { class Local { int x; }; }
template<class T> class Generic { T x; };
struct Other { /* ignored */ int y; };
'''
    (tmp_path / "a.cpp").write_text(text)
    full = inventory.inventory(["a.cpp"], tmp_path)
    import hashlib
    expected = {name: {"a.cpp": hashlib.sha1(body.encode("latin-1")).hexdigest()[:10]}
                for name, body in class_views.class_bodies(text).items()}
    assert full == expected
    assert set(full) == {"A::B", "Other"}
    assert inventory.inventory(["a.cpp"], tmp_path, {"Comment", "Local", "Generic"}) == {}


def test_saved_content_cache_survives_new_instance_and_another_worktree(tmp_path, cached, monkeypatch):
    (tmp_path / "a.cpp").write_text("class Alpha { int x; };\n")
    expected = inventory.inventory(["a.cpp"], tmp_path)
    inventory.save()
    monkeypatch.setattr(inventory, "VIEWS", picker_cache.FileMemo("test-views", inventory.CODE))
    other = tmp_path / "other"
    other.mkdir()
    (other / "renamed.cpp").write_text("class Alpha { int x; };\n")
    assert inventory.inventory(["renamed.cpp"], other)["Alpha"]["renamed.cpp"] == expected["Alpha"]["a.cpp"]
    assert len(cached) == 1


def test_parser_version_change_invalidates_saved_entries(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    code = tmp_path / "parser.py"
    code.write_text("v1")
    memo = picker_cache.FileMemo("parser-version-test", [code])
    assert memo.get("same-content", lambda: 1) == 1
    memo.save()
    code.write_text("v2")
    memo = picker_cache.FileMemo("parser-version-test", [code])
    assert memo.get("same-content", lambda: 2) == 2


def test_a_class_template_copy_counts_only_when_asked(tmp_path, monkeypatch):
    # BitFlags: a registered class template's private copies are its template bodies and explicit
    # specializations, which the plain inventory (namespace-scope class bodies) never sees
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    for memo in ("HEADS", "VIEWS", "TEMPLATE_VIEWS"):
        monkeypatch.setattr(inventory, memo, picker_cache.FileMemo("test-" + memo.lower(), inventory.CODE))
    (tmp_path / "t.cpp").write_text("template <int N> class BitFlags { unsigned m_bits[(N + 31) / 32]; };\n")
    (tmp_path / "s.cpp").write_text("template <int N> class BitFlags;\n"
                                    "template <> class BitFlags<11> { unsigned m_bits[1]; };\n")
    (tmp_path / "u.cpp").write_text("template <int N> class BitFlags;\nvoid f(BitFlags<11> *);\n")
    sources = ["t.cpp", "s.cpp", "u.cpp"]
    assert inventory.inventory(sources, tmp_path, {"BitFlags"}) == {}
    found = inventory.inventory(sources, tmp_path, {"BitFlags"}, templates=True)
    assert set(found["BitFlags"]) == {"t.cpp", "s.cpp"}
