"""The exit-link mode: the 17 placement-only objects are proved dead, and the
link itself carries no /FORCE, stub, alias or filler (tools/exit_link.py)."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import exit_link as E  # noqa: E402

TEXT, DATA, COMDAT = 0x60500020, 0xC0301040, 0x1000
EXTERNAL, STATIC = 2, 3


def coff(path, sections, definitions=(), references=()):
    """A minimal i386 COFF object.

    `sections`: [(name, body, relocs [(offset, target, type)], selection, parent)].
    `definitions`: [(name, section, storage)]; `references`: undefined externals.
    Section symbols carry the aux record `eh_verify.Obj` reads its parent from.
    """
    entries = []
    for number, (_name, body, relocs, selection, parent) in enumerate(sections, 1):
        aux = struct.pack("<IHHIHB3x", len(body), len(relocs), 0, 0, parent, selection or 0)
        entries.append((f"$s{number}", 0, number, STATIC, aux))
    entries += [(name, 0, section, storage, b"") for name, section, storage in definitions]
    entries += [(name, 0, 0, EXTERNAL, b"") for name in references]
    index, cursor = {}, 0
    for name, _value, _section, _storage, aux in entries:
        index.setdefault(name, cursor)
        cursor += 1 + len(aux) // 18
    strings, symbol_table = bytearray(4), b""
    for name, value, section, storage, aux in entries:
        raw = name.encode()
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + b"\0")
        symbol_table += field + struct.pack("<IhHBB", value, section, 0x20 if section > 0 else 0,
                                            storage, len(aux) // 18) + aux
    data_start = 20 + 40 * len(sections)
    headers, bodies = b"", b""
    for name, body, relocs, selection, _parent in sections:
        pointer = data_start + len(bodies)
        bodies += body
        reloc_pointer = data_start + len(bodies) if relocs else 0
        bodies += b"".join(struct.pack("<IIH", offset, index[target], kind)
                           for offset, target, kind in relocs)
        flags = (TEXT if name.startswith(".text") else DATA) | (COMDAT if selection else 0)
        headers += name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(body), pointer, reloc_pointer, 0, len(relocs), 0, flags)
    strings[:4] = struct.pack("<I", len(strings))
    records = len(entries) + sum(len(entry[4]) // 18 for entry in entries)
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(sections), 0, data_start + len(bodies),
                                 records, 0, 0)
                     + headers + bodies + symbol_table + bytes(strings))
    return path


def funclet_object(path, name="$L1", parented=True):
    """A function, its `.xdata$x` EH data and (optionally) an associative funclet."""
    if parented:
        return coff(path, [
            (".text$mn", b"\x90" * 4, [], 2, 0),
            (".text$x", b"\x90" * 4, [], 5, 1),
            (".xdata$x", b"\0" * 4, [(0, name, 6)], 5, 1),
        ], definitions=[("_f", 1, EXTERNAL), (name, 2, STATIC)])
    return coff(path, [
        (".text$mn", b"\x90" * 4, [], 2, 0),
        (".xdata$x", b"\0" * 4, [(0, name, 6)], 5, 1),
    ], definitions=[("_f", 1, EXTERNAL), (name, 1, STATIC)])


def placement_rows():
    rows = []
    for name in sorted(E.PLACEMENT_BASENAMES):
        notes = "gen-funclet;object-symbol=$L1" if name.startswith("uw_gen") else "object-symbol=j_1"
        rows.append({"name": f"?row_{name}", "source": f"{E.PLACEMENT_DIR}/{name}",
                     "target_rva": "0x1000", "status": "matched", "notes": notes})
    return rows


def test_the_reviewed_population_is_seventeen_sources():
    rows = placement_rows()
    assert len(E.placement_sources(rows)) == E.EXPECTED_PLACEMENT_SOURCES == 17
    assert E.check_population(E.placement_sources(rows)) is None
    assert len(E.placement_objects(rows)) == 17


@pytest.mark.parametrize("source, placement", [
    ("Code/gen_small/uw_gen_000.cpp", True),
    ("Code/gen_small/uw_gen_014.cpp", True),
    ("Code/gen_small/gthunks_000_admitted.cpp", True),
    ("Code/gen_small/thunks_000_admitted.cpp", True),
    ("Code/gen_small/uw_gen_015.cpp", True),          # a new file is placement-like
    ("Code/gen_small/thunks_001_admitted.cpp", True),
    ("Code/GameEngine/Source/GameLogic/AI/AI.cpp", False),
    ("Code/gen_small/uw_gen_000.cpp.bak", False),
])
def test_placement_sources_are_recognised_by_the_reviewed_pattern(source, placement):
    assert E.is_placement_source(source) is placement


def test_an_unreviewed_placement_file_refuses_the_measurement():
    rows = placement_rows() + [{"name": "?new", "source": "Code/gen_small/uw_gen_015.cpp",
                                "target_rva": "0x1000", "status": "matched", "notes": ""}]
    problem = E.check_population(E.placement_sources(rows))
    assert problem and "unreviewed" in problem and "uw_gen_015.cpp" in problem


def test_a_funclet_is_proved_when_its_parent_emits_it(tmp_path):
    path = funclet_object(tmp_path / "a.obj")
    assert E.funclet_parent_emits(path, "$L1")[0]


def test_a_funclet_without_an_associative_parent_is_unproven(tmp_path):
    path = funclet_object(tmp_path / "a.obj", parented=False)
    proved, why = E.funclet_parent_emits(path, "$L1")
    assert not proved and "standalone" in why


def test_a_parent_that_does_not_name_the_funclet_is_unproven(tmp_path):
    path = coff(tmp_path / "a.obj", [
        (".text$mn", b"\x90" * 4, [], 2, 0),
        (".text$x", b"\x90" * 4, [], 5, 1),
        (".xdata$x", b"\0" * 4, [], 5, 1),
    ], definitions=[("_f", 1, EXTERNAL), ("$L1", 2, STATIC)])
    proved, why = E.funclet_parent_emits(path, "$L1")
    assert not proved and "does not name" in why


def neutral_funclet_proof(monkeypatch, locations=None):
    """Skip the retail image: structural proof true, every RVA covered."""
    monkeypatch.setattr(E, "funclet_parent_emits", lambda path, name: (True, ""))
    monkeypatch.setattr(E, "kept_funclet_locations",
                        lambda *args, **kwargs: {0x1000: []} if locations is None else locations)


def test_omission_proof_finds_an_outside_referrer(tmp_path, monkeypatch):
    omitted = coff(tmp_path / "omitted.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                   definitions=[("?u", 1, EXTERNAL)])
    kept = coff(tmp_path / "kept.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                references=["?u"])
    rows = placement_rows()
    objects = {f"{E.PLACEMENT_DIR}/{name}": tmp_path / f"omit_{index}.obj"
               for index, name in enumerate(sorted(E.PLACEMENT_BASENAMES))}
    objects[f"{E.PLACEMENT_DIR}/{sorted(E.PLACEMENT_BASENAMES)[0]}"] = omitted
    monkeypatch.setattr(E.build, "row_object", lambda row: objects[row["source"]])
    neutral_funclet_proof(monkeypatch)
    proof = E.omission_proof(rows, [omitted, kept], [omitted, kept])
    assert proof["outside_referrers"] == {"?u": ["kept.obj"]}
    assert "?u" in proof["exclusive_names"]
    assert proof["inspection_failures"] == []


def test_omission_proof_is_clean_when_nothing_outside_references_the_definitions(tmp_path, monkeypatch):
    omitted = coff(tmp_path / "omitted.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                   definitions=[("?u", 1, EXTERNAL)])
    kept = coff(tmp_path / "kept.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                references=["?other"])
    rows = placement_rows()
    objects = {f"{E.PLACEMENT_DIR}/{name}": tmp_path / f"omit_{index}.obj"
               for index, name in enumerate(sorted(E.PLACEMENT_BASENAMES))}
    objects[f"{E.PLACEMENT_DIR}/{sorted(E.PLACEMENT_BASENAMES)[0]}"] = omitted
    monkeypatch.setattr(E.build, "row_object", lambda row: objects[row["source"]])
    neutral_funclet_proof(monkeypatch)
    proof = E.omission_proof(rows, [omitted, kept], [omitted, kept])
    assert proof["outside_referrers"] == {}
    assert proof["exclusive_names"] == ["?u"]
    assert proof["missing_objects"] == sorted(path.name for path in objects.values()
                                              if path != omitted and not path.exists())


def test_an_omitted_funclet_no_kept_parent_emits_is_uncovered(tmp_path, monkeypatch):
    omitted = coff(tmp_path / "omitted.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                   definitions=[("?u", 1, EXTERNAL)])
    rows = placement_rows()
    objects = {f"{E.PLACEMENT_DIR}/{name}": tmp_path / f"omit_{index}.obj"
               for index, name in enumerate(sorted(E.PLACEMENT_BASENAMES))}
    objects[f"{E.PLACEMENT_DIR}/{sorted(E.PLACEMENT_BASENAMES)[0]}"] = omitted
    monkeypatch.setattr(E.build, "row_object", lambda row: objects[row["source"]])
    neutral_funclet_proof(monkeypatch, locations={})
    proof = E.omission_proof(rows, [omitted], [omitted])
    assert proof["funclet_covered"] == 0
    assert len(proof["uncovered_funclets"]) == 15       # the 15 uw_gen funclet rows
    assert all(entry["target_rva"] == "0x1000" for entry in proof["uncovered_funclets"])


def test_a_missing_kept_object_fails_the_proof(tmp_path, monkeypatch):
    omitted = coff(tmp_path / "omitted.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                   definitions=[("?u", 1, EXTERNAL)])
    missing = tmp_path / "missing.obj"
    rows = placement_rows()
    objects = {f"{E.PLACEMENT_DIR}/{name}": tmp_path / f"omit_{index}.obj"
               for index, name in enumerate(sorted(E.PLACEMENT_BASENAMES))}
    objects[f"{E.PLACEMENT_DIR}/{sorted(E.PLACEMENT_BASENAMES)[0]}"] = omitted
    monkeypatch.setattr(E.build, "row_object", lambda row: objects[row["source"]])
    neutral_funclet_proof(monkeypatch)
    proof = E.omission_proof(rows, [omitted], [omitted, missing])
    assert proof["inspection_failures"] == [{"object": "missing.obj", "why": "missing object"}]


def test_an_unreadable_kept_object_fails_the_proof(tmp_path, monkeypatch):
    omitted = coff(tmp_path / "omitted.obj", [(".text", b"\x90" * 4, [], 0, 0)],
                   definitions=[("?u", 1, EXTERNAL)])
    broken = tmp_path / "broken.obj"
    broken.write_bytes(b"not a coff object")
    rows = placement_rows()
    objects = {f"{E.PLACEMENT_DIR}/{name}": tmp_path / f"omit_{index}.obj"
               for index, name in enumerate(sorted(E.PLACEMENT_BASENAMES))}
    objects[f"{E.PLACEMENT_DIR}/{sorted(E.PLACEMENT_BASENAMES)[0]}"] = omitted
    monkeypatch.setattr(E.build, "row_object", lambda row: objects[row["source"]])
    neutral_funclet_proof(monkeypatch)
    proof = E.omission_proof(rows, [omitted], [omitted, broken])
    assert len(proof["inspection_failures"]) == 1
    assert "unreadable object" in proof["inspection_failures"][0]["why"]


def test_drectve_includes_are_case_insensitive_and_quoted(tmp_path):
    path = coff(tmp_path / "d.obj", [(".drectve", b'/include:?u /INCLUDE:"?v"', [], 0, 0)],
                references=["?w"])
    references = E.coff_references(path, path.read_bytes())
    assert {"?u", "?v", "?w"} <= references


def test_index_proof_counts_only_omitted_definitions_and_finds_outside_touches():
    index = {"objects": ["o0.obj", "o1.obj", "k.obj"],
             "strong": {"?a": [0], "?b": [1], "?c": [2]},
             "comdat": {"?d": [(0, "x", None)]},
             "touches": {"k.obj": {"?a"}, "o0.obj": {"?b"}}}
    proof = E.index_proof(index, {"o0.obj", "o1.obj"})
    assert proof["exclusive_names"] == 3               # ?a, ?b, ?d
    assert proof["outside_referrers"] == {"k.obj": ["?a"]}


def test_index_prediction_subtracts_the_exclusive_unresolved_names():
    index = {"objects": ["o0.obj", "k.obj"],
             "strong": {"?a": [0], "?c": [1]}, "comdat": {},
             "touches": {}}
    previous = {"unresolved": {"?a": {}, "?c": {}, "?z": {}},
                "when": "2026-10-30 02:53", "commit": "8716fcf38f", "rules": "retail-truth-5"}
    measurement = E.index_measurement(index, {"o0.obj"}, previous)
    assert measurement["prediction"]["exclusive_unresolved_gone"] == 1
    assert measurement["prediction"]["unresolved_left"] == 2
    assert measurement["prediction"]["census"]["commit"] == "8716fcf38f"


def test_link_options_carry_no_force_and_no_scaffold():
    options = E.link_arguments(E.ROOT / "build/exit_link/exit.exe",
                               E.ROOT / "build/exit_link/exit.rsp")
    assert "/FORCE" not in options
    assert f"/BASE:0x{E.BASE:X}" in options
    assert f"/ENTRY:{E.ENTRY}" in options
    assert not [option for option in options if any(word in option.lower()
                                                    for word in ("stub", "alias", "fill"))]


def test_currency_is_the_source_and_every_recorded_header(monkeypatch):
    obj, source = Path("a.obj"), Path("a.cpp")
    monkeypatch.setattr(E.build, "compile_is_current", lambda current, output: current == source)
    assert E.stale_objects([obj], {obj: source}) == []
    assert E.stale_objects([obj], {obj: Path("b.cpp")}) == [obj]
    assert E.stale_objects([obj], {}) == []          # a library member has no source


def test_scaffold_free_refuses_stubs_aliases_fillers_and_omitted_objects(tmp_path):
    omitted = {tmp_path / "o.obj"}
    inputs = [tmp_path / "o.obj", tmp_path / "stubs.obj", tmp_path / "alias.obj",
              tmp_path / "fill03.obj", tmp_path / "real.obj"]
    bad, leaked = E.scaffold_free(inputs, omitted)
    assert bad == ["stubs.obj", "alias.obj", "fill03.obj"]
    assert leaked == ["o.obj"]


def test_parse_errors_keeps_every_line_and_its_referrer():
    log = ('a.obj : error LNK2001: unresolved external symbol "void __cdecl f(void)" (?f@@YAXXZ)\n'
           'b.obj : error LNK2001: unresolved external symbol _g\n'
           'a.obj : error LNK2005: _h already defined in b.obj\n'
           'LINK : fatal error LNK1120: 2 unresolved externals\n')
    errors = E.parse_errors(log, {"a.obj": "Code/a.cpp", "b.obj": "Code/b.cpp"})
    assert [error["symbol"] for error in errors] == ["?f@@YAXXZ", "_g", "_h", ""]
    assert [error["code"] for error in errors] == ["LNK2001", "LNK2001", "LNK2005", "LNK1120"]
    assert errors[0]["source"] == "Code/a.cpp" and errors[1]["source"] == "Code/b.cpp"


def test_link_refuses_on_windows(monkeypatch):
    monkeypatch.setattr(E.sys, "platform", "win32")
    monkeypatch.delenv("GITHUB_ACTIONS", raising=False)
    with pytest.raises(SystemExit, match="sandbox"):
        E.run_link([])


@pytest.mark.parametrize("flag", ["--allow-missing", "--skip-eh-proof", "--build", "--prepare"])
def test_the_escape_flags_are_gone(flag):
    with pytest.raises(SystemExit):
        E.main(["--link", flag])


def test_expected_objects_dedupe_a_shared_code_and_data_provider(tmp_path, monkeypatch):
    shared = tmp_path / "shared.obj"
    monkeypatch.setattr(E.build, "row_object", lambda row: shared)
    monkeypatch.setattr(E.build, "obj_path", lambda source: shared)
    monkeypatch.setattr(E.census, "data_sources", lambda: [Path("Code/Shared.cpp")])
    rows = [{"source": "Code/Shared.cpp", "name": "?f", "target_rva": "0x1000",
             "status": "matched", "notes": ""}]
    assert E.expected_objects(rows) == [shared]


def test_outputs_are_not_the_census_outputs():
    import link_census
    assert E.OUT != link_census.OUT
    assert E.OUT.name == "exit_link"


def test_blockers_from_errors_group_missing_names_by_repo_source():
    import exit_link as module
    lines = ["severity\tcode\tsymbol\tobject\tsource\ttext",
             "error\tLNK2019\t?a@@YAXXZ\tx.obj\tD:\\a\\Open-BFME-2\\Open-BFME-2\\Code\\X.cpp\tt",
             "error\tLNK2001\t?b@@YAXXZ\tx.obj\tD:\\a\\Open-BFME-2\\Open-BFME-2\\Code\\X.cpp\tt",
             "error\tLNK2001\t?a@@YAXXZ\tx.obj\tD:\\a\\Open-BFME-2\\Open-BFME-2\\Code\\X.cpp\tt",
             "error\tLNK2019\t?a@@YAXXZ\ty.obj\tCode/Y.cpp\tt",
             "error\tLNK2005\t?d@@YAXXZ\tz.obj\tCode/Z.cpp\tt",
             "error\tLNK2019\t?c@@YAXXZ\tn.obj\t\tt"]
    assert module.blockers_from_errors(lines) == [("Code/X.cpp", 2, "?a@@YAXXZ"), ("Code/Y.cpp", 1, "?a@@YAXXZ")]


def test_runnable_link_options():
    options = E.link_arguments(E.ROOT / "build/exit_link/exit.exe",
                               E.ROOT / "build/exit_link/exit.rsp")
    assert "/FIXED:NO" in options
    assert {arg for arg in options if arg.startswith("/OPT:")} == {"/OPT:NOREF", "/OPT:NOICF"}
    assert "/MAP:build/exit_link/exit.map" in options
    assert not any(arg.upper().startswith("/FORCE") for arg in options)


def test_every_export_is_a_linker_root(tmp_path):
    import csv
    rows = list(csv.DictReader((E.ROOT / "reverse/exports.csv").open()))
    text = E.export_definition(tmp_path / "retail.def").read_text()
    assert len(rows) == 1964
    assert len(text.splitlines()) == len(rows) + 1
    for row in rows:
        assert f'{row["name"]} @{row["ordinal"]}' in text


def test_diagnostic_traps_have_distinct_offsets(tmp_path):
    path = E.diagnostic_stubs({"_a", "?long_decorated_name@@", "_b"}, tmp_path / "stubs.obj")
    data = path.read_bytes()
    table = struct.unpack_from("<I", data, 8)[0]
    offsets = [struct.unpack_from("<I", data, table + i * 18 + 8)[0] for i in range(3)]
    assert offsets == [0, 16, 32]
    assert data[60:108] == b"\xcc" * 48
    assert not struct.unpack_from("<I", data, 56)[0] & COMDAT


@pytest.mark.parametrize("diagnostic", [False, True])
def test_receipt_hashes_and_kind(tmp_path, monkeypatch, diagnostic):
    import json
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    image.with_suffix(".map").write_bytes(b"map")
    monkeypatch.setattr(E, "image_commit", lambda: "a" * 40)
    names = ["_missing"] if diagnostic else []
    E.image_receipt(image, diagnostic, names)
    receipt = json.loads((tmp_path / "image_receipt.json").read_text())
    assert receipt == {
        "kind": "diagnostic" if diagnostic else "real", "commit": "a" * 40,
        "base": "0x10000000", "image_sha256": E.digest(image),
        "map_sha256": E.digest(image.with_suffix(".map")), "stubbed": names,
        "exports_requested": 1964, "rsrc": True, "fixed_no": True, "opt": "NOREF,NOICF"}


def test_receipt_requires_current_nonempty_map(tmp_path):
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    with pytest.raises(RuntimeError, match="map"):
        E.image_receipt(image, False, [])


def test_diagnostic_cannot_write_measured_outputs(tmp_path, monkeypatch):
    import json
    measured = tmp_path / "exit_link"
    measured.mkdir()
    board = measured / "scoreboard.json"
    board.write_text(json.dumps(
        {"unresolved": 19, "duplicates": 0, "image_written": False, "authoritative": True}))
    before = board.read_bytes()
    monkeypatch.setattr(E, "OUT", measured)
    def run(rows, diagnostic=False):
        assert diagnostic is True
        assert E.OUT == tmp_path / "diagnostic_link"
        E.OUT.mkdir()
        for name in ("result.json", "errors.tsv", "exit.exe", "exit.map", "image_receipt.json"):
            (E.OUT / name).write_text("diagnostic")
        return 0
    monkeypatch.setattr(E, "run_link", run)
    assert E.main(["--diagnostic"]) == 0
    assert E.OUT == measured
    assert board.read_bytes() == before
    assert sorted(p.name for p in measured.iterdir()) == ["scoreboard.json"]


def test_diagnostic_restores_output_scope_on_refusal(tmp_path, monkeypatch):
    monkeypatch.setattr(E, "OUT", tmp_path / "exit_link")
    def refuse(*args, **kwargs):
        raise SystemExit("refused")
    monkeypatch.setattr(E, "run_link", refuse)
    with pytest.raises(SystemExit):
        E.run_diagnostic([])
    assert E.OUT == tmp_path / "exit_link"


def test_workflow_diagnostic_is_separate_and_nonfatal():
    text = (E.ROOT / ".github/workflows/real-link.yml").read_text()
    measured, diagnostic = text.split("      - name: Diagnostic link\n")
    diagnostic = diagnostic.split("\n  report:")[0]
    assert "scoreboard.json" in measured
    assert "scoreboard.json" not in diagnostic
    assert "name: diagnostic-link-" in diagnostic
    assert diagnostic.count("continue-on-error: true") == 4
    assert "image_receipt.json" in diagnostic


def test_real_receipt_refuses_stubs(tmp_path):
    with pytest.raises(ValueError, match="stubs"):
        E.image_receipt(tmp_path / "exit.exe", False, ["_missing"])


def test_direct_diagnostic_refuses_measured_directory(monkeypatch):
    monkeypatch.setattr(E.sys, "platform", "linux")
    with pytest.raises(SystemExit, match="isolated"):
        E.run_link([], diagnostic=True)


def test_manifest_failure_does_not_change_link_result(tmp_path, monkeypatch):
    import types
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    def fail(*args, **kwargs):
        raise ValueError("fixture snapshot failure")
    monkeypatch.setitem(sys.modules, "image_iso", types.SimpleNamespace(write_object_manifest=fail))
    assert E.snapshot_image_objects(tmp_path / "exit.rsp", image) == {
        "error": "ValueError: fixture snapshot failure"}


def test_manifest_uses_final_response_and_map(tmp_path, monkeypatch):
    import types
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    monkeypatch.setattr(E, "OUT", tmp_path)
    called = []
    def snapshot(*args, **kwargs):
        called.append((args, kwargs))
        return {"objects": 1}
    monkeypatch.setitem(sys.modules, "image_iso", types.SimpleNamespace(write_object_manifest=snapshot))
    rsp = tmp_path / "exit.rsp"
    assert E.snapshot_image_objects(rsp, image) == {"objects": 1}
    assert called == [((rsp, image.with_suffix(".map"), tmp_path / "image_objects.json"),
                       {"cwd": E.build.ROOT})]


def test_harness_import_roots_add_required_stdcall_slots():
    requests, roots = E.harness_import_roots({"__imp__Other@4"})
    assert roots == {"__imp__SHGetSpecialFolderPathW@16", "__imp__GetVersion@0",
                     "__imp__GetVersionExA@4"}
    assert requests == roots | {"__imp__Other@4"}


def test_harness_import_roots_reuse_existing_spelling():
    requests, roots = E.harness_import_roots({"__imp__GetVersion", "__imp__GetVersionExA@4"})
    assert "__imp__GetVersion" in roots
    assert "__imp__GetVersion@0" not in requests
    assert "__imp__GetVersionExA@4" in roots


def test_harness_import_roots_keep_providers_but_root_only_canonical_slot():
    requests, roots = E.harness_import_roots({"__imp__GetVersion", "__imp__GetVersion@0"})
    assert {"__imp__GetVersion", "__imp__GetVersion@0"} <= requests
    assert "__imp__GetVersion@0" in roots
    assert "__imp__GetVersion" not in roots
    assert roots <= requests


def test_exception_list_is_an_absolute_zero_coff_symbol(tmp_path):
    obj = E.link_cycle.write_coff(tmp_path / "absolute.obj", [], [
        (name, -1, value, E.link_cycle.EXTERNAL) for name, value in E.link_cycle.ABSOLUTE.items()])
    sections, symbols = E.link_cycle.parse_coff(obj.read_bytes())
    exception = [s for s in symbols.values() if s.name == "__except_list"]
    assert len(exception) == 1
    assert exception[0].sec == -1 and exception[0].value == 0


def test_image_commit_is_a_full_git_object_id():
    import re
    assert re.fullmatch(r"[0-9a-f]{40}", E.image_commit())


def test_unresolved_export_is_not_lost_from_errors_tsv():
    name = "?_Allocate@MemoryPool@@YAPAXIW4AllocType@1@I@Z"
    rows = E.parse_errors(
        'exit.exp : error LNK2001: unresolved external symbol "MemoryPool::_Allocate" (' + name + ')')
    assert len(rows) == 1
    assert rows[0]["object"] == "exit.exp"
    assert rows[0]["code"] == "LNK2001"
    assert rows[0]["symbol"] == name
    assert rows[0]["source"] == ""

def test_diagnostic_pipeline_keeps_results_logs_and_scoreboard_separate(tmp_path, monkeypatch):
    import json
    import types
    root = tmp_path
    measured = root / "build/exit_link"
    measured.mkdir(parents=True)
    board = measured / "scoreboard.json"
    board.write_bytes(b'{"unresolved":393,"duplicates":0,"image_written":false,"authoritative":true}\n')
    before = board.read_bytes()
    monkeypatch.setattr(E, "ROOT", root)
    monkeypatch.setattr(E, "OUT", measured)
    monkeypatch.setattr(E.sys, "platform", "linux")
    monkeypatch.setattr(E, "object_inventory", lambda rows: ([], [], []))
    monkeypatch.setattr(E, "check_data_rows", lambda: None)
    monkeypatch.setattr(E.census, "_object_sources", lambda rows: {})
    monkeypatch.setattr(E, "omission_proof", lambda *a: {
        "population_problem": None, "inspection_failures": [], "uncovered_funclets": [],
        "unproven": [], "outside_referrers": {}, "exclusive_names": [], "objects": [],
        "funclet_covered": 0, "funclet_rows": 0})
    monkeypatch.setattr(E, "eh_proof", lambda rows: {"unproven": [], "missing_objects": 0})
    monkeypatch.setattr(E, "link_setup", lambda *a: (
        [root / "bridge.obj", root / "absolute.obj"],
        {"import_libraries": [], "harness_import_symbols": []}))
    monkeypatch.setattr(E, "link_command", lambda inputs, image, out, roots:
                        (["fixture-linker"], out / "exit.rsp"))
    monkeypatch.setattr(E.census, "census_state", lambda *a: {})
    monkeypatch.setattr(E, "tool_digests", lambda: {})
    monkeypatch.setattr(E.build, "vc71_root", lambda: root)
    monkeypatch.setattr(E.build, "compiler_environment", lambda *a: {})
    monkeypatch.setattr(E.subprocess, "run", lambda *a, **k:
                        types.SimpleNamespace(returncode=0, stdout="", stderr=""))
    monkeypatch.setattr(E, "object_sources", lambda rows: {})
    monkeypatch.setattr(E.census, "classify", lambda *a: ({}, {}, {}, {}))
    monkeypatch.setattr(E, "placement_objects", lambda rows: [])
    monkeypatch.setattr(E, "published_index_meta", lambda: {})
    monkeypatch.setattr(E.census, "head", lambda: "a" * 40)
    assert E.run_diagnostic([]) == 1  # fake linker wrote no image, so no credit
    diagnostic = root / "build/diagnostic_link"
    result = json.loads((diagnostic / "result.json").read_text())
    assert result["mode"] == "diagnostic-link"
    assert root / result["link"]["log"] == diagnostic / "link.log"
    assert (diagnostic / "link.log").is_file()
    assert E.OUT == measured
    assert board.read_bytes() == before
    assert sorted(p.name for p in measured.iterdir()) == ["scoreboard.json"]
