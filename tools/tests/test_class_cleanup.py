"""Content-cache invalidation and safe application of unused-class batches."""
import copy
import json
import os
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_cleanup as C
import class_views
import picker_cache


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    (tmp_path / "reverse").mkdir()
    files = ["Code/a.cpp", "Code/b.cpp"]
    for i, source in enumerate(files):
        (tmp_path / source).write_text(f"struct Unused{i} {{ int x; }};\nint f{i}() {{ return {i}; }}\n")
    (tmp_path / "reverse/functions.csv").write_text("status,source\n" + "".join(f"matched,{s}\n" for s in files))
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    monkeypatch.setattr(C, "RESULTS", picker_cache.FileMemo("test-unused", [C.__file__, C.tu_skeleton.__file__]))
    monkeypatch.setattr(C, "POTENTIAL", picker_cache.FileMemo("test-unused-potential", C.RESULTS.code))
    return tmp_path, files


def test_positive_and_negative_results_survive_a_new_process_cache_instance(tree, monkeypatch):
    root, files = tree
    first = C.discover(files=files, root=root)
    assert first["computed"] == 2 and len(first["candidates"]) == 2
    monkeypatch.setattr(C, "RESULTS", picker_cache.FileMemo("test-unused", [C.__file__, C.tu_skeleton.__file__]))
    second = C.discover(files=files, root=root)
    assert second["cache_hits"] == 2 and second["computed"] == 0
    for p in first["candidates"]:
        (root / p["source"]).write_bytes(p["_after"])
    empty = C.discover(files=files, root=root)
    assert not empty["candidates"] and empty["computed"] == 2
    monkeypatch.setattr(C, "RESULTS", picker_cache.FileMemo("test-unused", [C.__file__, C.tu_skeleton.__file__]))
    empty = C.discover(files=files, root=root)
    assert not empty["candidates"] and empty["cache_hits"] == 2


def test_same_size_same_mtime_edit_invalidates_the_proposal(tree):
    root, files = tree
    one = C.prepare(files[0], root)[0]
    path = root / files[0]
    stat = path.stat()
    path.write_bytes(path.read_bytes().replace(b"Unused0", b"Unused9"))
    os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
    two, computed = C.prepare(files[0], root)
    assert computed and two["sha256"] != one["sha256"]
    assert two["removed"] == ["Unused9"]


def test_header_macro_change_invalidates_an_unchanged_source(tree):
    root, files = tree
    source = root / files[0]
    source.write_text('#include "shared.h"\n' + source.read_text())
    header = root / "Code/shared.h"
    header.write_text("// no macros\n")
    assert C.prepare(files[0], root)[0]
    header.write_text("#define NEED sizeof(Unused0)\n")
    assert C.prepare(files[0], root)[0] is None
    header.unlink()
    assert C.prepare(files[0], root)[0] is None
    header.write_text("// resolvable again\n")
    assert C.prepare(files[0], root)[0]


def test_a_source_with_no_possible_removal_needs_no_header_scan(tree, monkeypatch):
    root, files = tree
    (root / files[0]).write_text("struct Used { int x; };\nint f(Used *p) { return p->x; }\n")
    monkeypatch.setattr(C.tu_skeleton, "extern_macro_tokens", lambda *a: pytest.fail("unnecessary include traversal"))
    assert C.prepare(files[0], root)[0] is None
    assert C.prepare(files[0], root) == (None, False)


def test_header_member_change_invalidates_an_unchanged_source(tree):
    root, files = tree
    source = root / files[0]
    source.write_text('#include "shared.h"\n' + source.read_text())
    header = root / "Code/shared.h"
    header.write_text("// no references\n")
    assert C.prepare(files[0], root)[0]
    header.write_text("struct Unused0;\nstruct Owner { Unused0 *member; };\n")
    assert C.prepare(files[0], root)[0] is None
    header.write_text("// references removed\n")
    assert C.prepare(files[0], root)[0]


def test_source_paths_and_ledger_membership_are_required(tree):
    root, files = tree
    with pytest.raises(ValueError):
        C.source_path("../outside.cpp", root)
    with pytest.raises(ValueError):
        C.ranked_sources(files=["Code/unmatched.cpp"], root=root)
    with pytest.raises(ValueError):
        C.ranked_sources("../Code", root=root)


def test_git_ranking_does_not_run_a_class_inventory(tree, monkeypatch):
    root, files = tree
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **kw: SimpleNamespace(
        returncode=0, stdout=b"Code/a.cpp\x001\nCode/b.cpp\x009\nCode/unmatched.cpp\x00999\n", stderr=b""))
    monkeypatch.setattr(class_views, "survey", lambda *a: pytest.fail("full survey invoked"))
    assert C.ranked_sources(root=root) == [files[1], files[0]]


@pytest.fixture
def application(tree, monkeypatch):
    root, files = tree
    plan = C.discover(files=files, root=root)["candidates"]
    released, builds = [], []
    monkeypatch.setattr(C.claims, "claimable", lambda keys, **kw: {C.claims.key_of(k): {} for k in keys})
    monkeypatch.setattr(C.claims, "acquire", lambda keys, **kw: SimpleNamespace(
        claimed=[C.claims.key_of(k) for k in keys], refused=[], prior=[]))
    monkeypatch.setattr(C.claims, "release", lambda keys, **kw: released.extend(keys) or keys)
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **kw: SimpleNamespace(stdout="", returncode=0))
    monkeypatch.setattr(C, "frozen", lambda *a: {})
    def verify(sources):
        builds.append({s: (root / s).read_bytes() for s in sources})
        return dict.fromkeys(sources)
    monkeypatch.setattr(C, "verify", verify)
    monkeypatch.setattr(C, "snapshot", lambda source: {"same": source})
    monkeypatch.setattr(C, "same_runtime", lambda before, after: before == after)
    return root, files, plan, released, builds


def test_apply_claims_and_verifies_a_whole_batch_without_committing(application):
    root, files, plan, released, builds = application
    report = C.apply(plan, root=root)
    assert set(report["applied"]) == set(files)
    assert len(builds) == 2 and not released
    assert all(b"struct Unused" in value for value in builds[0].values())
    assert all(b"struct Unused" not in value for value in builds[1].values())


def test_held_file_is_skipped_before_limiting_the_batch(application, monkeypatch):
    root, files, plan, released, builds = application
    held = plan[0]["source"]
    monkeypatch.setattr(C.claims, "claimable", lambda keys, **kw: {
        C.claims.key_of(k): {"other": {}} if k == "file:" + held else {} for k in keys})
    report = C.apply(plan, limit=1, root=root)
    assert held in report["rejected"] and report["applied"] == [plan[1]["source"]]
    assert b"struct Unused" in (root / held).read_bytes()


@pytest.mark.parametrize("failure", ["byte", "runtime", "declaration", "missing"])
def test_failure_restores_only_the_failed_unit_and_rechecks_its_original(application, monkeypatch, failure):
    root, files, plan, released, builds = application
    bad = files[0]
    original = (root / bad).read_bytes()
    if failure in ("byte", "missing"):
        original_verify = C.verify
        def verify(sources):
            result = original_verify(sources)
            if bad in sources and b"struct Unused" not in (root / bad).read_bytes():
                if failure == "byte": result[bad] = "byte failure"
                else: del result[bad]
            return result
        monkeypatch.setattr(C, "verify", verify)
    elif failure == "runtime":
        monkeypatch.setattr(C, "snapshot", lambda s: {"same": s, "bad": s == bad and b"struct Unused" not in (root / s).read_bytes()})
    else:
        monkeypatch.setattr(C, "frozen", lambda sources, _: {bad: "unmatched body"}
                            if bad in sources and b"struct Unused" not in (root / bad).read_bytes() else {})
    report = C.apply(plan, root=root)
    assert report["applied"] == [files[1]] and bad in report["rejected"]
    assert (root / bad).read_bytes() == original
    assert released == [C.claims.key_of("file:" + bad)]
    assert builds[-1] == {bad: original}


def test_unknown_object_restores_all_edits(application, monkeypatch):
    root, files, plan, released, builds = application
    old = {s: (root / s).read_bytes() for s in files}
    original_snapshot = C.snapshot
    def snapshot(source):
        if b"struct Unused" not in (root / source).read_bytes():
            raise ValueError("unreadable object")
        return original_snapshot(source)
    monkeypatch.setattr(C, "snapshot", snapshot)
    with pytest.raises(ValueError, match="unreadable object"):
        C.apply(plan, root=root)
    assert {s: (root / s).read_bytes() for s in files} == old
    assert set(released) == {C.claims.key_of("file:" + s) for s in files}


def test_macro_dependency_changes_are_rejected_before_any_write(application):
    root, files, plan, released, builds = application
    source = root / files[0]
    source.write_bytes(source.read_bytes() + b"\n#define CHANGED 1\n")
    before = source.read_bytes()
    report = C.apply(plan, root=root)
    assert files[0] in report["rejected"] and source.read_bytes() == before
    assert report["applied"] == [files[1]]


def test_apply_rechecks_header_macros_even_with_unchanged_source_bytes(application):
    root, files, _, released, builds = application
    path = root / files[0]
    path.write_text('#include "shared.h"\n' + path.read_text())
    header = root / "Code/shared.h"
    header.write_text("// original\n")
    plan = C.discover(files=files, root=root)["candidates"]
    before = path.read_bytes()
    header.write_text("#define USE sizeof(Unused0)\n")
    report = C.apply(plan, root=root)
    assert files[0] in report["rejected"] and path.read_bytes() == before
    assert report["applied"] == [files[1]]


def test_apply_recomputes_instead_of_trusting_a_cached_transformation(application):
    root, files, plan, released, builds = application
    target = plan[0]
    before = (root / target["source"]).read_bytes()
    target["_after"] = target["_after"].replace(b"return 0", b"return 9") + b"\n// corrupt cache\n"
    report = C.apply(plan, root=root)
    assert target["source"] in report["rejected"]
    assert (root / target["source"]).read_bytes() == before


def test_existing_dirty_or_untracked_source_is_skipped(application, monkeypatch):
    root, files, plan, released, builds = application
    before = (root / files[0]).read_bytes()
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **kw: SimpleNamespace(stdout="?? " + files[0] + "\0"))
    report = C.apply(plan, root=root)
    assert files[0] in report["rejected"] and report["applied"] == [files[1]]
    assert (root / files[0]).read_bytes() == before


def test_original_byte_failure_never_writes_the_failing_source(application, monkeypatch):
    root, files, plan, released, builds = application
    original_verify = C.verify
    def verify(sources):
        result = original_verify(sources)
        if files[0] in sources:
            result[files[0]] = "original does not match"
        return result
    monkeypatch.setattr(C, "verify", verify)
    before = (root / files[0]).read_bytes()
    report = C.apply(plan, root=root)
    assert report["applied"] == [files[1]] and files[0] in report["rejected"]
    assert (root / files[0]).read_bytes() == before


def graph_fixture():
    sections = [dict(name=".text", size=1, sha256=str(i), characteristics=1,
                     comdat=[2, None], relocs=[]) for i in range(2)]
    sections[0]["relocs"] = [[0, 20, ["defined", 1, 0, "callee"]]]
    return dict(sections=sections, extern_definitions={"caller": [0, 0, 32], "callee": [1, 0, 32]},
                weak={"weak": ["default", 3]})


def test_named_comdat_reordering_is_equal_but_semantic_changes_are_not():
    before = graph_fixture()
    after = copy.deepcopy(before)
    after["sections"].reverse()
    after["sections"][1]["relocs"][0][2][1] = 0
    after["extern_definitions"]["caller"][0] = 1
    after["extern_definitions"]["callee"][0] = 0
    assert C.same_runtime(before, after)
    assert before != after  # exact section-number comparison would falsely refuse
    for change in ("bytes", "relocation", "weak", "selection", "provider"):
        broken = copy.deepcopy(after)
        if change == "bytes": broken["sections"][0]["sha256"] = "different"
        elif change == "relocation": broken["sections"][1]["relocs"][0][2][-1] = "wrong"
        elif change == "weak": broken["weak"]["weak"][1] = 2
        elif change == "selection": broken["sections"][0]["comdat"][0] = 1
        else: del broken["extern_definitions"]["callee"]
        assert not C.same_runtime(before, broken), change


def test_existing_cli_dispatches_the_cleanup_command(monkeypatch):
    monkeypatch.setattr(C, "run", lambda args: 17 if args.unused and args.scan_limit == 11 else 1)
    assert class_views.main(["--unused", "--scan-limit", "11"]) == 17
    with pytest.raises(SystemExit):
        class_views.main(["--apply"])
