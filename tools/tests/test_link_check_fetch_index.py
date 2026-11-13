"""The published census index and object bundle (link_check.py --fetch-index,
--publish-index, --update-index; build.export_objects / import_objects).

The index replaces a missing or older local one, never a newer one; a
download that is not an index, or one of a commit the checkout lacks,
replaces nothing; only a clean --history census (or a clean update) is
published. A bundled object reaches the object store only for the same
source and the same compile command, and is restored only while every
recorded header still hashes as recorded."""
import io
import json
import pickle
import sys
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import link_check as C


def index(date, commit="abc1234567", **meta):
    return pickle.dumps({"meta": {"date": date, "commit": commit, **meta}, "blockers": {}})


@pytest.fixture
def served(tmp_path, monkeypatch):
    out = tmp_path / "build" / "link_census"
    monkeypatch.setattr(C, "ROOT", tmp_path)
    monkeypatch.setattr(C, "INDEX", out / "link_index.pkl")
    monkeypatch.setattr(C, "OBJECTS", out / "objects.tar.gz")
    monkeypatch.setattr(C.link_census, "OUT", out)
    monkeypatch.setattr(C, "fetch_objects", lambda: 0)
    body = {}
    monkeypatch.setattr("urllib.request.urlopen", lambda url, timeout: io.BytesIO(body["data"]))
    monkeypatch.setattr(C, "contains", lambda commit, ref="HEAD": not commit.startswith("future"))
    return out / "link_index.pkl", body


def leftovers(path):
    return [p.name for p in path.parent.iterdir() if p.suffix == ".download"]


def test_missing_index_is_downloaded(served):
    path, body = served
    body["data"] = index("2026-10-14 15:43")
    assert C.fetch_index() == 0
    assert C.index_meta(path)["date"] == "2026-10-14 15:43"
    assert leftovers(path) == []


def test_older_local_index_is_replaced_and_newer_kept(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = index("2026-10-14 15:43", "new0000000")
    C.fetch_index()
    assert C.index_meta(path)["commit"] == "new0000000"
    body["data"] = index("2026-10-12 08:00", "older00000")
    C.fetch_index()
    assert C.index_meta(path)["commit"] == "new0000000"


@pytest.mark.parametrize("local_meta,published_meta,replace", [
    ({"date": "2026-11-13 00:18", "census_date": "2026-11-12 16:28"},
     {"date": "2026-11-12 23:35", "census_date": "2026-11-12 21:59"}, True),
    ({"date": "2026-11-13 00:18", "census_date": "2026-11-12 21:59"},
     {"date": "2026-11-13 00:35", "census_date": "2026-11-12 16:28"}, False),
    ({"date": "2026-11-13 00:18", "census_date": "2026-11-12 21:59"},
     {"date": "2026-11-13 00:35", "census_date": "2026-11-12 21:59"}, False),
    ({"date": "2026-11-12 16:28"},
     {"date": "2026-11-12 23:35", "census_date": "2026-11-12 21:59"}, True),
    ({"date": "2026-11-12 21:59"},
     {"date": "2026-11-13 00:35", "census_date": "2026-11-12 16:28"}, False),
])
def test_fetch_compares_census_measurements_not_refresh_times(served, local_meta, published_meta, replace):
    path, body = served
    path.parent.mkdir(parents=True)
    old = index(commit="local00000", **local_meta)
    published = index(commit="published0", **published_meta)
    path.write_bytes(old)
    body["data"] = published
    assert C.fetch_index() == 0
    assert path.read_bytes() == (published if replace else old)
    assert leftovers(path) == []


def test_a_rolled_index_cannot_hide_an_unknown_census_commit(served):
    path, body = served
    path.parent.mkdir(parents=True)
    old = index("2026-11-12 16:28", "local00000")
    path.write_bytes(old)
    body["data"] = index("2026-11-13 00:18", "known00000",
                         census_date="2026-11-12 21:59", census_commit="future0000")
    with pytest.raises(SystemExit, match="lacks census commit"):
        C.fetch_index()
    assert path.read_bytes() == old
    assert leftovers(path) == []


def test_a_download_that_is_not_an_index_replaces_nothing(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = b"<html>Not Found</html>"
    with pytest.raises(SystemExit):
        C.fetch_index()
    assert C.index_meta(path)["commit"] == "old0000000"
    assert leftovers(path) == []


def test_an_index_of_a_commit_the_checkout_lacks_replaces_nothing(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = index("2026-10-14 15:43", "future0000")
    with pytest.raises(SystemExit, match="lacks census commit"):
        C.fetch_index()
    assert C.index_meta(path)["commit"] == "old0000000"
    assert leftovers(path) == []


def test_only_a_clean_history_census_is_published(served, monkeypatch):
    path, _ = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-14 15:43"))
    monkeypatch.setattr(C, "_git", lambda *a, **k: "")
    monkeypatch.setattr(C.link_census, "ledger", lambda: [])
    monkeypatch.setattr(C.link_census, "compile_sources", lambda rows: [])
    monkeypatch.setattr(C.build, "export_objects", lambda sources, path: 0)
    calls = []
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **k: calls.append(a) or C.subprocess.CompletedProcess(a, 0))
    with pytest.raises(SystemExit, match="clean tree"):
        C.publish_index()
    assert calls == []
    path.write_bytes(pickle.dumps({"meta": {"date": "2026-10-14 15:43", "commit": "abc1234567",
                                            "clean_tree": True}, "blockers": {}}))
    assert C.publish_index() == 0
    upload = [cmd[0] for cmd in calls if cmd[0][:3] == ["gh", "release", "upload"]]
    assert upload and str(C.INDEX) in upload[0] and str(C.OBJECTS) in upload[0]


def test_forget_drops_a_removed_units_definitions_and_blockers():
    ix = {"objects": ["a.obj", "b.obj"], "strong": {"f": [0], "g": [0, 1]},
          "comdat": {"c": [(0, "d", "retail"), (1, "d", "retail")]}, "common": {"x": [(0, 4)]},
          "alternates": {"al": [(0, "t")]}, "blockers": {"A.cpp": {"object": "a.obj"}, "B.cpp": {"object": "b.obj"}},
          "digests": {"a.obj": "1", "b.obj": "2"}}
    C.forget(ix, ["a.obj"])
    assert ix["objects"] == ["a.obj", "b.obj"]
    assert ix["strong"] == {"g": [1]} and ix["comdat"] == {"c": [(1, "d", "retail")]}
    assert ix["common"] == {} and ix["alternates"] == {}
    assert list(ix["blockers"]) == ["B.cpp"] and ix["digests"] == {"b.obj": "2"}
    assert not C.in_census(ix, "a.obj") and C.in_census(ix, "b.obj")


def test_a_forgotten_units_leftover_object_is_not_previewable(monkeypatch, tmp_path):
    ix = {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj"], "forgotten": {"a.obj"}, "blockers": {},
          "common_schema": C.COMMON_SCHEMA, "common": {}, "alternates": {}}
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C.link_census, "ledger", lambda: [])
    monkeypatch.setattr(C.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(C, "resolve", lambda path, index: (None, tmp_path / "a.obj"))
    with pytest.raises(SystemExit, match="not previewable"):
        C.main(["a.obj"])


@pytest.fixture
def hosts(tmp_path, monkeypatch):
    """One checkout, compiled 'on Wine' (launcher in front, '/' paths) and
    imported 'on Windows' (no launcher, '\\' paths)."""
    root = tmp_path / "repo"
    (root / "Code").mkdir(parents=True)
    (root / "inc").mkdir()
    source, header = root / "Code" / "a.cpp", root / "inc" / "h.h"
    source.write_text("int f() { return 1; }\n")
    header.write_text("#define X 1\n")
    output = root / "build" / "match" / "a.obj"
    output.parent.mkdir(parents=True)
    store = tmp_path / "store"
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "obj_path", lambda s, member=None: output)
    monkeypatch.setattr(build, "_objstore_root", lambda: store)
    monkeypatch.setattr(build, "stale_sources", lambda sources, outputs, workers=1, **k: [])
    host = {"command": ["/usr/bin/wine", "@ROOT@/tc/cl.exe", "-O2", "Code/a.cpp"]}
    monkeypatch.setattr(build, "compiler_command", lambda s, o: (list(host["command"]), {"INCLUDE": "@ROOT@/tc/inc"}))
    fingerprint = build._cmd_fingerprint(host["command"], {"INCLUDE": "@ROOT@/tc/inc"})
    output.write_bytes(b"OBJECT")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": fingerprint, "source": build._hash_file(str(source)), "deps": {"inc/h.h": build._hash_file(str(header))},
        "path": "Code/a.cpp", "object": build._hash_file(str(output))}))
    return source, header, output, host, tmp_path / "objects.tar.gz"


def test_a_bundled_object_is_restored_on_another_host_while_its_headers_hold(hosts):
    source, header, output, host, bundle = hosts
    assert build.export_objects([source], bundle) == 1
    output.unlink()
    build._deps_sidecar(output).unlink()
    host["command"] = ["@ROOT@\\tc\\cl.exe", "-O2", "Code/a.cpp"]
    assert build.import_objects(bundle) == 1
    fingerprint = build._cmd_fingerprint(host["command"], {"INCLUDE": "@ROOT@/tc/inc"})
    assert build._restore_object(source, output, fingerprint)
    assert output.read_bytes() == b"OBJECT"
    output.unlink()
    build._deps_sidecar(output).unlink()
    header.write_text("#define X 2\n")
    assert not build._restore_object(source, output, fingerprint)


def test_an_object_replaced_after_its_receipt_is_not_bundled(hosts):
    source, header, output, host, bundle = hosts
    output.write_bytes(b"ANOTHER")  # a compile replaced the object; the receipt still names OBJECT
    assert build.export_objects([source], bundle) == 0


def test_an_object_newer_than_its_older_format_receipt_is_not_bundled(hosts):
    import os as _os
    source, header, output, host, bundle = hosts
    sidecar = build._deps_sidecar(output)
    meta = json.loads(sidecar.read_text())
    del meta["object"]
    sidecar.write_text(json.dumps(meta))
    stamp = sidecar.stat().st_mtime_ns
    _os.utime(output, ns=(stamp - 10**9, stamp - 10**9))
    assert build.export_objects([source], bundle) == 1  # older receipt, object written first: bundled
    _os.utime(output, ns=(stamp + 10**9, stamp + 10**9))
    assert build.export_objects([source], bundle) == 0  # object rewritten after its receipt


def test_a_bundled_object_whose_bytes_do_not_match_its_receipt_is_not_imported(hosts):
    import io as _io
    import tarfile
    source, header, output, host, bundle = hosts
    build.export_objects([source], bundle)
    with tarfile.open(bundle, "r:gz") as tar:
        files = {m.name: tar.extractfile(m).read() for m in tar.getmembers()}
    with tarfile.open(bundle, "w:gz") as tar:
        for name, data in files.items():
            data = b"FORGED" if name.endswith(".obj") else data
            info = tarfile.TarInfo(name)
            info.size = len(data)
            tar.addfile(info, _io.BytesIO(data))
    assert build.import_objects(bundle) == 0


def test_a_bundled_object_of_another_command_or_source_is_not_imported(hosts):
    source, header, output, host, bundle = hosts
    build.export_objects([source], bundle)
    host["command"] = ["@ROOT@/tc/cl.exe", "-O1", "Code/a.cpp"]
    assert build.import_objects(bundle) == 0
    host["command"] = ["@ROOT@/tc/cl.exe", "-O2", "Code/a.cpp"]
    source.write_text("int f() { return 2; }\n")
    assert build.import_objects(bundle) == 0


def test_restore_stale_returns_only_what_the_store_cannot_restore(hosts):
    source, header, output, host, bundle = hosts
    build.export_objects([source], bundle)
    output.unlink()
    build._deps_sidecar(output).unlink()
    host["command"] = [r"@ROOT@\tc\cl.exe", "-O2", "Code/a.cpp"]
    build.import_objects(bundle)
    assert build._restore_stale([source], {source: output}) == []
    assert output.read_bytes() == b"OBJECT"
    output.unlink()
    build._deps_sidecar(output).unlink()
    header.write_text("#define X 2\n")
    assert build._restore_stale([source], {source: output}) == [source]


@pytest.fixture
def cached_object_variant(hosts):
    source, header, output, host, bundle = hosts
    assert build.export_objects([source], bundle) == 1
    output.unlink()
    build._deps_sidecar(output).unlink()
    host["command"] = [r"@ROOT@\tc\cl.exe", "-O2", "Code/a.cpp"]
    assert build.import_objects(bundle) == 1
    fingerprint = build._cmd_fingerprint(host["command"], {"INCLUDE": "@ROOT@/tc/inc"})
    directory = build._objstore_dir(source, fingerprint)
    cached, = directory.glob("*.obj")
    return source, output, fingerprint, cached


def test_restore_skips_object_pruned_while_ordering(cached_object_variant, monkeypatch):
    source, output, fingerprint, cached = cached_object_variant
    original = Path.glob

    def prune(path, pattern, *args, **kwargs):
        entries = list(original(path, pattern, *args, **kwargs))
        if path == cached.parent and pattern == "*.obj":
            cached.unlink(missing_ok=True)
        return iter(entries)

    monkeypatch.setattr(Path, "glob", prune)
    assert not build._restore_object(source, output, fingerprint)
    assert not output.exists()
    assert not build._deps_sidecar(output).exists()


@pytest.mark.parametrize("part", ["object", "receipt"])
def test_restore_skips_cache_pair_pruned_during_copy(cached_object_variant, monkeypatch, part):
    source, output, fingerprint, cached = cached_object_variant
    victim = cached if part == "object" else cached.with_suffix(".deps.json")
    output.write_bytes(b"PREVIOUS OBJECT")
    sidecar = build._deps_sidecar(output)
    sidecar.write_bytes(b"PREVIOUS RECEIPT")
    original = build.shutil.copyfile

    def prune(src, dst, *args, **kwargs):
        if Path(src) == victim:
            victim.unlink(missing_ok=True)
        return original(src, dst, *args, **kwargs)

    monkeypatch.setattr(build.shutil, "copyfile", prune)
    assert not build._restore_object(source, output, fingerprint)
    assert output.read_bytes() == b"PREVIOUS OBJECT"
    assert sidecar.read_bytes() == b"PREVIOUS RECEIPT"
    assert not list(output.parent.glob("*.restore"))


def test_restore_uses_other_variant_when_one_is_pruned(cached_object_variant, monkeypatch):
    source, output, fingerprint, cached = cached_object_variant
    other = cached.with_name("another-valid-variant.obj")
    other.write_bytes(cached.read_bytes())
    other.with_suffix(".deps.json").write_bytes(cached.with_suffix(".deps.json").read_bytes())
    original = Path.glob

    def prune(path, pattern, *args, **kwargs):
        entries = list(original(path, pattern, *args, **kwargs))
        if path == cached.parent and pattern == "*.obj":
            cached.unlink(missing_ok=True)
        return iter(entries)

    monkeypatch.setattr(Path, "glob", prune)
    assert build._restore_object(source, output, fingerprint)
    assert output.read_bytes() == b"OBJECT"
    assert build.compile_is_current(source, output)


def test_restore_remains_valid_when_cache_is_pruned_before_lru_touch(cached_object_variant, monkeypatch):
    source, output, fingerprint, cached = cached_object_variant
    original = build.os.utime

    def prune(path, *args, **kwargs):
        if Path(path) == cached:
            cached.unlink(missing_ok=True)
        return original(path, *args, **kwargs)

    monkeypatch.setattr(build.os, "utime", prune)
    assert build._restore_object(source, output, fingerprint)
    assert output.read_bytes() == b"OBJECT"
    assert build.compile_is_current(source, output)


def test_restore_still_reports_output_write_errors(cached_object_variant, monkeypatch):
    source, output, fingerprint, cached = cached_object_variant
    original = build.shutil.copyfile

    def denied(src, dst, *args, **kwargs):
        if Path(src) == cached:
            raise PermissionError("restore output denied")
        return original(src, dst, *args, **kwargs)

    monkeypatch.setattr(build.shutil, "copyfile", denied)
    with pytest.raises(PermissionError, match="restore output denied"):
        build._restore_object(source, output, fingerprint)
