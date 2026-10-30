"""Opt-in STLport overlay: exact patches, cache integrity, and unit isolation."""
import hashlib
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import stlport_overlay as overlay
import stlport_trial

SHARED = overlay.ROOT / "build/stlport46"


def tree_state(root):
    """Every entry under ROOT (the root itself included) with its mtime: the file set
    and every timestamp a write would move. None when ROOT does not exist."""
    if not root.exists():
        return None
    return {p.relative_to(root).as_posix(): (p.is_dir(), p.stat().st_mtime_ns)
            for p in [root, *root.rglob("*")]}


@pytest.fixture(autouse=True)
def shared_tree_untouched():
    """A live ./build.sh or add_match in this checkout reads build/stlport46: no test
    may create, repair, corrupt or plant anything there (one planted header once failed
    a concurrent add_match). Materializing tests use `isolated` instead."""
    before = tree_state(SHARED)
    yield
    assert tree_state(SHARED) == before, "a test wrote into the shared build/stlport46 tree"


@pytest.fixture
def isolated(tmp_path, monkeypatch):
    """materialize() under tmp_path: its output root is stlport_overlay.ROOT's build/stlport46;
    the pristine release and patches it reads stay the repository's."""
    monkeypatch.setattr(overlay, "ROOT", tmp_path)
    return tmp_path / "build/stlport46"


def test_materialize_writes_only_under_the_injected_root(isolated):
    result = overlay.materialize()
    assert result.parent == isolated and (result / "base/stl/_list.h").is_file()


def test_patch_roundtrip_and_stale_context():
    original = "one\ntwo\nthree\n"
    patch = "--- a/stl/x.h\n+++ b/stl/x.h\n@@ -1,3 +1,3 @@\n one\n-two\n+changed\n three\n"
    assert overlay.apply_patch(original, patch) == ("stl/x.h", "one\nchanged\nthree\n")
    with pytest.raises(ValueError, match="context"):
        overlay.apply_patch(original.replace("two", "stale"), patch)
    with pytest.raises(ValueError, match="path"):
        overlay.apply_patch(original, patch.replace("stl/x.h", "stl/../../x.h"))


def test_locale_source_patch_is_bounded_and_binds_existing_owner(isolated):
    patch = (overlay.PATCHES / "_c_locale_win32.c.patch").read_text(encoding="utf-8")
    original = (overlay.TREE / overlay.LOCALE_SOURCE).read_text(encoding="utf-8")
    rel, transformed = overlay.apply_patch(original, patch)
    assert rel == overlay.LOCALE_SOURCE
    assert transformed.count("((Rva0084E030Buffer *)GroupingBuffer)->squash();") == 2
    assert "__FixGrouping" not in transformed
    assert (overlay.materialize() / "base" / rel).read_text(encoding="utf-8").endswith(transformed)
    with pytest.raises(ValueError, match="path"):
        overlay.apply_patch(original, patch.replace(overlay.LOCALE_SOURCE, "src/other.c"))
    with pytest.raises(ValueError, match="context"):
        overlay.apply_patch(original.replace("static void __FixGrouping", "void __FixGrouping"), patch)


def test_all_committed_patches_materialize_and_repair_cache(isolated):
    result = overlay.materialize()
    header = result / "base/stl/_list.h"
    expected = header.read_bytes()
    assert b"resize(size_type __new_size, const _Tp& __x)" in expected
    assert b"_STLP_BFME_TREE_NODE_BASE_O2" in (result / "base/stl/_tree.h").read_bytes()
    assert b"_BFME_RETAIL_TREE_INSERT_LAYOUT" in (result / "base/stl/_tree.c").read_bytes()
    assert b"static char* allocate" in (result / "bfmealloc/stl/_alloc.h").read_bytes()
    assert b"allocator<char>::allocate" not in (result / "base/stl/_list.h").read_bytes()
    header.write_bytes(b"corrupt generated header")
    assert overlay.materialize() == result
    assert header.read_bytes() == expected


def test_missing_or_changed_upstream_fails_before_cache(tmp_path):
    (tmp_path / "stlport").mkdir()
    (tmp_path / "src").mkdir()
    (tmp_path / "README").write_bytes(b"license")
    (tmp_path / "SHA256SUMS").write_text(hashlib.sha256(b"license").hexdigest()+"  README\n")
    overlay.verify_tree(tmp_path)
    (tmp_path / "README").write_bytes(b"changed")
    with pytest.raises(ValueError, match="missing or changed"):
        overlay.verify_tree(tmp_path)
    (tmp_path / "README").write_bytes(b"license")
    (tmp_path / "stlport/injected.h").write_bytes(b"new header")
    with pytest.raises(ValueError, match="inventory"):
        overlay.verify_tree(tmp_path)


@pytest.mark.parametrize("marker,selected", [("// stlport46", True), ("\ufeff// stlport46", True), ("// stlport", False),
                                               ("// prose // stlport46", False), ("", False)])
def test_marker_changes_only_opted_in_commands(tmp_path, monkeypatch, marker, selected):
    source = tmp_path / "test.cpp"
    source.write_text(marker+"\n// cl: /MD /Ireference/shims/bfmealloc\n", encoding="utf-8")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(overlay, "ROOT", tmp_path)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(build, "source_extra_flags", lambda _: ["-MD", "-Ireference/shims/bfmealloc"])
    monkeypatch.setattr(overlay, "materialize", lambda: tmp_path / "generated")
    command, env = build.compiler_command(source, tmp_path / "x.obj")
    if selected:
        assert "-Igenerated/bfmealloc" in command
        assert "-Igenerated/base" in command
        assert str(overlay.TREE / "stlport") in env["INCLUDE"]
        assert "-Ireference/shims/bfmealloc" not in command
    else:
        assert "-Ireference/shims/bfmealloc" in command
        assert all("generated" not in c for c in command)
        assert str(overlay.TREE / "stlport") not in env["INCLUDE"]


def test_marker_checks_upstream_even_for_cached_command(tmp_path, monkeypatch):
    source = tmp_path / "test.cpp"; source.write_text("// stlport46\n")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(overlay, "ROOT", tmp_path)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "vc71_root", lambda: tmp_path)
    def broken():
        raise ValueError("upstream changed")
    monkeypatch.setattr(overlay, "materialize", broken)
    with pytest.raises(ValueError, match="upstream changed"):
        build.compiler_command(source, tmp_path / "x.obj")


def test_queue_uses_live_identity_and_extent(tmp_path, monkeypatch, capsys):
    report = tmp_path / "report.csv"
    report.write_text("kind,rva,size,name,source,header_46,knob,library_46\n"
                      "library-copy,0x10,30,f,a.cpp,match-4.6,,\n"
                      "library-copy,0x20,40,g,b.cpp,match-4.6,,\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_text("name,target_rva,target_size,source,status\n"
                      "f,0x10,30,a.cpp,matched\n"
                      "g,0x20,41,b.cpp,matched\n")
    for name in ("a.cpp", "b.cpp"):
        (tmp_path / name).write_text("// stlport\n")
    monkeypatch.setattr(stlport_trial, "ROOT", tmp_path)
    monkeypatch.setattr(stlport_trial, "REPORT", report)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    stlport_trial.queue(SimpleNamespace(tsv=True))
    output = capsys.readouterr().out
    assert "a.cpp" in output and "b.cpp" not in output


def test_queue_files_carry_knobs_failures_and_the_lead(tmp_path, monkeypatch):
    report = tmp_path / "report.csv"
    report.write_text("kind,rva,size,name,source,header_46,knob,library_46\n"
                      "header,0x10,30,f,a.cpp,match-4.6,,\n"
                      "collateral,0x11,8,c,a.cpp,match-knob,-shim,\n"       # game code needing a knob
                      "collateral,0x12,8,d,a.cpp,mismatch,,\n"              # a whole-file move breaks it
                      "header,0x13,8,e,a.cpp,control-fail,,\n"              # the trial's own artifact
                      "header,0x14,8,gone,a.cpp,mismatch,,\n"               # no longer in the ledger
                      "library-copy,0x20,40,g,b.cpp,not-sampled,,match\n"
                      "library-copy,0x21,9,h,b.cpp,not-sampled,,mismatch\n"
                      "library-copy,0x22,9,i,b.cpp,not-sampled,,\n")       # no evidence either way
    ledger = tmp_path / "functions.csv"
    ledger.write_text("name,target_rva,target_size,source,status\n"
                      + "".join(f"{n},{rva},{size},{src},matched\n" for n, rva, size, src in (
                          ("f", "0x10", 30, "a.cpp"), ("c", "0x11", 8, "a.cpp"), ("d", "0x12", 8, "a.cpp"),
                          ("e", "0x13", 8, "a.cpp"), ("g", "0x20", 40, "b.cpp"), ("h", "0x21", 9, "b.cpp"),
                          ("i", "0x22", 9, "b.cpp"))))
    for name in ("a.cpp", "b.cpp"):
        (tmp_path / name).write_text("// cl: /MD\r\n// stlport\r\n")
    monkeypatch.setattr(stlport_trial, "ROOT", tmp_path)
    monkeypatch.setattr(stlport_trial, "REPORT", report)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    b, a = stlport_trial.queue_files()                                     # most bytes first
    assert (a["source"], [r["name"] for r in a["rows"]], a["bytes"]) == ("a.cpp", ["f"], 30)
    assert a["knobs"] == ["-shim"] and a["fails"] == 1 and a["lead"] == "unit"
    assert (b["source"], [r["name"] for r in b["rows"]]) == ("b.cpp", ["g"])
    assert b["knobs"] == [] and b["fails"] == 1 and b["lead"] == "library"


def test_queue_skips_a_file_that_never_opted_into_stlport(tmp_path, monkeypatch):
    # No `// stlport` line: the unit compiles no STLport header, so its trial rows
    # built the same bytes under either version and the marker move cannot apply.
    report = tmp_path / "report.csv"
    report.write_text("kind,rva,size,name,source,header_46,knob,library_46\n"
                      "header,0x10,30,f,a.cpp,match-4.6,,\n"
                      "library-copy,0x20,40,g,b.cpp,not-sampled,,match\n"
                      "library-copy,0x30,9,h,c.cpp,not-sampled,,match\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_text("name,target_rva,target_size,source,status\n"
                      "f,0x10,30,a.cpp,matched\ng,0x20,40,b.cpp,matched\nh,0x30,9,c.cpp,matched\n")
    (tmp_path / "a.cpp").write_text("// cl: /MD\nnamespace _STL { template<class T> struct less; }\n")
    (tmp_path / "b.cpp").write_text("// cl: /MD\n// stlport\n#include <vector>\n")
    (tmp_path / "c.cpp").write_text("// cl: /MD\n// stlport_widget.cpp holds the rest\n")
    monkeypatch.setattr(stlport_trial, "ROOT", tmp_path)
    monkeypatch.setattr(stlport_trial, "REPORT", report)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    assert [f["source"] for f in stlport_trial.queue_files()] == ["b.cpp"]


def test_repair_queue_calls_the_stlport_lane(monkeypatch):
    import repair_queue
    calls = []
    monkeypatch.setattr(stlport_trial, "queue", lambda args: calls.append(args.tsv))
    assert repair_queue.main(["stlport", "--tsv"]) == 0
    assert calls == [True]


def test_unlisted_generated_header_cannot_shadow_upstream(isolated):
    result = overlay.materialize()
    injected = result / "base/stl/_alloc.h"
    assert not injected.exists()
    injected.write_bytes(b"wrong allocator")
    with pytest.raises(ValueError, match="unlisted generated"):
        overlay.materialize()


def test_queue_does_not_reserve_an_already_opted_in_file(tmp_path, monkeypatch, capsys):
    report = tmp_path / "report.csv"
    report.write_text("kind,rva,size,name,source,header_46,knob,library_46\n"
                      "library-copy,0x10,30,f,a.cpp,match-4.6,,\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_text("name,target_rva,target_size,source,status\n"
                      "f,0x10,30,a.cpp,matched\n")
    (tmp_path / "a.cpp").write_text("// stlport46\n")
    monkeypatch.setattr(stlport_trial, "ROOT", tmp_path)
    monkeypatch.setattr(stlport_trial, "REPORT", report)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    stlport_trial.queue(SimpleNamespace(tsv=True))
    assert capsys.readouterr().out == ""


@pytest.mark.parametrize("relative", ["vendor/stlport-4.6/stlport/stl/_cwchar.h",
                                     "build/stlport46/hash/base/stl/_cwchar.h"])
def test_46_native_header_macros_use_the_stlport_inventory_rules(tmp_path, monkeypatch, relative):
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(overlay, "TREE", tmp_path / "vendor/stlport-4.6")
    header = tmp_path / relative
    header.parent.mkdir(parents=True)
    header.write_text("#include _STLP_NATIVE_C_HEADER(wchar.h)\n")
    assert not build._include_escapes_search_roots(header, True)
    assert build._include_escapes_search_roots(header, False)


def test_legacy_non_utf8_comments_do_not_opt_in_or_fail(tmp_path):
    source = tmp_path / "legacy.cpp"
    source.write_bytes(b"// legacy comment \xff\x80\nvoid f() {}\n")
    assert not overlay.selected(source)
    flags = ["-MD", "-Ireference/shims/bfmealloc"]
    assert overlay.include_dirs(source, flags) == flags
