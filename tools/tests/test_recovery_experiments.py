"""Cache reuse must prove the actual object and inputs, never a landing verdict."""
from concurrent.futures import ThreadPoolExecutor
import hashlib
from pathlib import Path
import sys
import threading
import time
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import census_receipts
import recovery_experiments as experiments


@pytest.fixture
def lab(tmp_path, monkeypatch):
    root = tmp_path / "p"
    source = root / "Code" / "trial.cpp"
    early, late = root / "early", root / "late"
    for path in (source.parent, early, late, root / "tools", root / "reverse", root / "bin"):
        path.mkdir(parents=True, exist_ok=True)
    source.write_text('#include "thing.h"\nint f(){return 7;}\n')
    header = late / "thing.h"
    header.write_text("#define VALUE 7\n")
    for path in (root / "tools" / "build.py", root / "reverse" / "functions.csv",
                 root / "reverse" / "symbols.csv", root / "bin" / "cl.exe", root / "bin" / "c2.dll"):
        path.write_bytes(b"fixture")
    retail = root / "game.dat"
    retail.write_bytes(b"\x6a\x07\x58\xc3")
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "BFME1_ROOT", root / "reference")
    monkeypatch.setattr(build, "_CASEDIR_MEMO", {})
    # The compile stub below replaces subprocess.run wholesale, so build.wine_path's
    # own `winepath -w <toolchain root>` lands in it too -- a command with no -Fo,
    # which made the stub raise StopIteration and failed all 22 tests here. Stubbed
    # rather than special-cased in the stub, so the fixture needs no Wine either.
    monkeypatch.setattr(build, "wine_path", lambda path: str(path))
    state = SimpleNamespace(calls=0, body=retail.read_bytes(), flags=[], unresolved=[], masked=False,
                            relocs=[], compile_failure=False, missing_probe=False, delay=0, lock=threading.Lock())

    def command(src, output):
        return ([str(root / "bin" / "cl.exe"), "-c", "-I" + str(early), "-I" + str(late)]
                + state.flags + ["-Fo" + output.relative_to(root).as_posix(), src.relative_to(root).as_posix()],
                {"INCLUDE": ""})

    monkeypatch.setattr(build, "compiler_command", command)
    backend = SimpleNamespace(
        ROOT=root, EXE=retail, FUNCTIONS=root / "reverse" / "functions.csv", SYMBOLS=root / "reverse" / "symbols.csv",
        DIR32=6, REL32=20, compiler_command=command, search_inventory=build.search_inventory,
        _write_deps_sidecar=build._write_deps_sidecar, _cmd_fingerprint=build._cmd_fingerprint,
        compile_is_current=build.compile_is_current, load_symbol_map=lambda: {},
        _function_starts=lambda *_: {1: [0]}, body_extent_problems=lambda *_: [],
    )

    def probe(src, _command, _env):
        if state.missing_probe:
            raise ValueError("unproven dependencies")
        paths = (src, early / "thing.h" if (early / "thing.h").exists() else header)
        return {"files": {str(path.resolve()): experiments.digest(path) for path in paths},
                "generations": {str(path.resolve()): [s.st_dev, s.st_ino, s.st_size, s.st_mtime_ns, s.st_ctime_ns]
                                for path in paths for s in [path.stat()]}}

    monkeypatch.setattr(census_receipts, "snapshot", probe)

    def compile_(command, **_kwargs):
        with state.lock:
            state.calls += 1
        if state.delay:
            time.sleep(state.delay)
        output = root / next(arg[3:] for arg in command if arg.startswith("-Fo"))
        if state.compile_failure:
            return SimpleNamespace(returncode=1, stdout="Cannot open include file\n")
        output.write_bytes(state.body)
        chosen = early / "thing.h" if (early / "thing.h").exists() else header
        return SimpleNamespace(returncode=0, stdout="Note: including file: " + str(chosen) + "\n")

    monkeypatch.setattr(experiments.subprocess, "run", compile_)

    def compare(row, _symbols, output, **_kwargs):
        size = int(row["target_size"])
        return {"bytes": output.read_bytes()[:size], "target": retail.read_bytes()[:size],
                "unresolved": state.unresolved, "masked": state.masked}

    backend.compile_function = compare
    backend.read_object_symbol_bytes = lambda output, *_a, **_kw: (
        output.read_bytes(), state.relocs, {"section": 1, "value": 0, "section_size": output.stat().st_size})
    return SimpleNamespace(root=root, source=source, header=header, early=early, backend=backend, state=state,
                           run=lambda **kwargs: experiments.run_experiment(source, "?f@@YAHXZ", 0x1000, 4,
                                                                          build_module=backend, **kwargs))


def test_hit_reuses_object_but_recomputes_diagnostic(lab):
    first, second = lab.run(), lab.run()
    assert first["candidate_exact"] and not first["cache_hit"]
    assert second["candidate_exact"] and second["cache_hit"]
    assert second["diagnostic_only"] and not second["landing_verified"]
    assert "./build.sh" in second["required_next"]
    assert lab.state.calls == 1
    assert not (lab.root / "build" / "match").exists()


@pytest.mark.parametrize("relative", ["Code/trial.cpp", "bin/cl.exe", "bin/c2.dll", "tools/build.py",
                                     "reverse/functions.csv", "reverse/symbols.csv", "game.dat"])
def test_input_byte_change_invalidates_cache(lab, relative):
    first = lab.run()
    path = lab.root / relative
    path.write_bytes(path.read_bytes() + b" ")
    second = lab.run()
    assert not second["cache_hit"] and first["cache_key"] != second["cache_key"]
    assert lab.state.calls == 2


def test_flags_invalidate_cache(lab):
    first = lab.run()
    lab.state.flags = ["-Ob0"]
    second = lab.run()
    assert not second["cache_hit"] and first["cache_key"] != second["cache_key"]


def test_nested_region_input_invalidates_cache(lab):
    path = lab.root / "reverse/retail_inventory/flag_regions.csv"
    path.parent.mkdir()
    path.write_text("old-region")
    first = lab.run()
    path.write_text("new-region")
    second = lab.run()
    assert not second["cache_hit"] and first["cache_key"] != second["cache_key"]


def test_long_lived_process_refreshes_region_cache(lab):
    path = lab.root / "regions.csv"
    path.write_text("old-region")
    flags = SimpleNamespace(REGIONS=path, OVERRIDES=path, FUNCTIONS=path,
                            _cache_lock=threading.RLock(), _cache={"regions": "stale"})
    lab.backend.flag_defaults = flags
    experiments.current_command(lab.backend, lab.source, lab.root / "a.obj")
    assert not flags._cache
    flags._cache["regions"] = "old-region"
    experiments.current_command(lab.backend, lab.source, lab.root / "a.obj")
    assert flags._cache["regions"] == "old-region"
    path.write_text("new-region")
    experiments.current_command(lab.backend, lab.source, lab.root / "a.obj")
    assert not flags._cache


def test_header_content_and_new_shadow_invalidate_cache(lab):
    lab.run()
    lab.header.write_text("#define VALUE 8\n")
    assert not lab.run()["cache_hit"]
    (lab.early / "thing.h").write_text("#define VALUE 9\n")
    assert not lab.run()["cache_hit"]
    assert lab.run()["cache_hit"]
    assert lab.state.calls == 3


def test_corrupt_object_or_cache_index_is_never_reused(lab):
    result = lab.run()
    Path(result["object"]).write_bytes(b"bad object")
    assert not lab.run()["cache_hit"]
    entry = Path(result["object"]).parent.parent
    (entry / "cache.json").write_text("{broken")
    assert not lab.run()["cache_hit"]


def test_compile_error_is_not_reused_when_missing_header_appears(lab):
    lab.state.compile_failure = True
    assert lab.run()["status"] == "compile-error"
    lab.state.compile_failure = False
    (lab.early / "thing.h").write_text("#define VALUE 7\n")
    result = lab.run()
    assert result["candidate_exact"] and not result["cache_hit"]


def test_unproven_dependency_capture_disables_reuse(lab):
    lab.state.missing_probe = True
    first, second = lab.run(), lab.run()
    assert not first["cacheable"] and not second["cache_hit"]
    assert lab.state.calls == 2


@pytest.mark.parametrize("problem", ["unresolved", "masked", "dir32", "unsupported", "long-body"])
def test_partial_or_masked_comparison_never_becomes_exact(lab, problem):
    if problem == "unresolved":
        lab.state.unresolved = ["?missing@@YAXXZ"]
    elif problem == "masked":
        lab.state.masked = True
    elif problem == "dir32":
        lab.state.relocs = [(0, 6, "_global")]
    elif problem == "unsupported":
        lab.state.relocs = [(0, 7, "_global")]
    else:
        lab.state.body += b"\x90\xc3"
    result = lab.run()
    assert result["bytes_match"] and not result["candidate_exact"]


def test_source_changed_during_compilation_refuses_result(lab, monkeypatch):
    original = experiments.subprocess.run

    def changing(command, **kwargs):
        result = original(command, **kwargs)
        lab.source.write_text(lab.source.read_text() + "// changed during compile\n")
        return result

    monkeypatch.setattr(experiments.subprocess, "run", changing)
    result = lab.run()
    assert result["status"] == "inputs-unproven-or-changed"
    assert not result["candidate_exact"] and not result["cacheable"]


def test_same_key_parallel_requests_compile_once(lab):
    lab.state.delay = 0.1
    with ThreadPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(lambda _: lab.run(), range(2)))
    assert lab.state.calls == 1
    assert sorted(result["cache_hit"] for result in results) == [False, True]
    assert all(result["candidate_exact"] for result in results)


@pytest.mark.parametrize("cache", ["build/match/trial", "build", "Code/cache", "../escape"])
def test_cache_cannot_touch_gate_outputs_or_escape(lab, cache):
    with pytest.raises(ValueError, match="private directory"):
        lab.run(cache=lab.root / cache)


def test_force_uses_another_private_run(lab):
    first = lab.run()
    second = lab.run(force=True)
    assert not second["cache_hit"] and first["object"] != second["object"]
