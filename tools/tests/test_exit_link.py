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
        "exports_requested": 1964, "rsrc": True, "fixed_no": True, "opt": "NOREF,NOICF",
        "authoritative": False, "omission_proof": "not-run",
        "vtables_bridged": 0, "vtable_slots_bridged": 0,
        **({"stub_seed": None} if diagnostic else {})}


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
    def run(rows, diagnostic=False, stub_seed=None):
        assert diagnostic is True and stub_seed is None
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
    assert rows[0]["source"] == E.EXPORT_UNOWNED

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
    monkeypatch.setattr(E.census, "ROOT", root)
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
        [root / "retail_vtables.obj", root / "bridge.obj", root / "absolute.obj"],
        {"import_libraries": [], "harness_import_symbols": [],
         "vtable_bridge": {"object": "retail_vtables.obj", "tables": 1, "slots": 4}}))
    monkeypatch.setattr(E, "link_command", lambda inputs, image, out, roots:
                        (["fixture-linker"], out / "exit.rsp"))
    monkeypatch.setattr(E.census, "census_state", lambda *a: {})
    monkeypatch.setattr(E, "tool_digests", lambda: {})
    monkeypatch.setattr(E.build, "vc71_root", lambda: root)
    monkeypatch.setattr(E.build, "compiler_environment", lambda *a: {})
    results = iter([
        types.SimpleNamespace(returncode=96, stdout=(
            "fixture.obj : error LNK2001: unresolved external symbol __imp__Missing@4\n"), stderr=""),
        types.SimpleNamespace(returncode=0, stdout="", stderr="")])
    monkeypatch.setattr(E, "run_native", lambda *a, **k: next(results))
    monkeypatch.setattr(E, "object_sources", lambda rows: {})
    monkeypatch.setattr(E, "export_sources", lambda rows: {})
    monkeypatch.setattr(E.census, "classify", lambda *a: ({}, {}, {}, {}))
    monkeypatch.setattr(E, "placement_objects", lambda rows: [])
    monkeypatch.setattr(E, "published_index_meta", lambda: {})
    monkeypatch.setattr(E.census, "head", lambda: "a" * 40)
    assert E.run_diagnostic([]) == 1  # fake linker wrote no image, so no credit
    diagnostic = root / "build/diagnostic_link"
    result = json.loads((diagnostic / "result.json").read_text())
    assert result["mode"] == "diagnostic-link"
    assert result["objects"]["linked"] == 0  # generated objects never earn source-object credit
    assert result["vtable_bridge"]["tables"] == 1
    assert result["vtable_bridge"]["slots"] == 4
    assert root / result["link"]["log"] == diagnostic / "link.log"
    assert (diagnostic / "link.log").is_file()
    import csv
    with (diagnostic / "stubbed.tsv").open() as handle:
        stub = list(csv.DictReader(handle, delimiter="\t"))
    assert len(stub) == 1
    assert stub[0]["name"] == "__imp__Missing@4"
    assert stub[0]["kind"] == "import-pointer" and stub[0]["section"] == ".text"
    assert stub[0]["trap_symbol"] == "__imp__Missing@4"
    assert E.OUT == measured
    assert board.read_bytes() == before
    assert sorted(p.name for p in measured.iterdir()) == ["scoreboard.json"]


@pytest.mark.skipif(sys.platform == "win32", reason="POSIX descendant lifetime regression")
def test_native_capture_does_not_wait_for_inherited_writer(tmp_path, monkeypatch):
    import os
    import signal
    import subprocess
    import sys
    monkeypatch.setattr(E.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(E.build, "compiler_environment", lambda root: os.environ.copy())
    pidfile = tmp_path / "descendant.pid"
    code = (
        "import os,subprocess,sys; from pathlib import Path; "
        "p=subprocess.Popen([sys.executable,'-c','import time; time.sleep(60)']); "
        f"Path({str(pidfile)!r}).write_text(str(p.pid)); "
        "os.write(1,b'native output\\n'); os.write(2,b'native error\\n')"
    )
    try:
        result = E.run_native([sys.executable, "-c", code], timeout=3)
        assert result.returncode == 0
        assert result.stdout == "native output\nnative error\n"
        assert result.stderr == ""
        os.kill(int(pidfile.read_text()), 0)  # writer is still alive after native parent finished
    finally:
        if pidfile.exists():
            try:
                os.kill(int(pidfile.read_text()), signal.SIGTERM)
            except ProcessLookupError:
                pass


def test_native_capture_preserves_error_exit_and_output(tmp_path, monkeypatch):
    import os
    import subprocess
    import sys
    monkeypatch.setattr(E.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(E.build, "compiler_environment", lambda root: os.environ.copy())
    with pytest.raises(subprocess.CalledProcessError) as error:
        E.run_native([sys.executable, "-c", "print('failed'); raise SystemExit(7)"], check=True)
    assert error.value.returncode == 7
    assert error.value.stdout == "failed\n"


def test_import_archive_retains_census_provider_convention(tmp_path, monkeypatch):
    import subprocess
    monkeypatch.setattr(E.build, "vc71_root", lambda: tmp_path)
    converted = []
    monkeypatch.setattr(E.link_cycle, "undecorate_stdcall_imports",
                        lambda lib, decorated: converted.append((lib.name, decorated)))
    def native(command):
        library = next(arg[5:] for arg in command if arg.startswith("/OUT:"))
        Path(library).write_bytes(b"native archive")
        return subprocess.CompletedProcess(command, 0, "", "")
    monkeypatch.setattr(E, "run_native", native)
    libraries = E.make_import_libs(
        {"kernel32.dll": ["GetVersion", "GetVersion@0"]}, tmp_path, {"_GetVersion@0"})
    assert libraries == [tmp_path / "imp_kernel32.lib"]
    assert (tmp_path / "imp_kernel32.def").read_text() == (
        "LIBRARY kernel32.dll\nEXPORTS\n  GetVersion\n  GetVersion@0 DATA\n")
    assert converted == [("imp_kernel32.lib", False)]


def test_runtime_data_imports_are_the_archive_data_members(tmp_path):
    """msvcrt.lib's DATA imports (`__adjust_fdiv`) must not become CODE thunks that shadow
    its static providers: the first diagnostic image faulted storing into one at entry."""
    def member(name, kind):
        body = struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, 0x14C, 0, len(name) + 13, 0, kind)
        body += name.encode() + b"\0" + b"MSVCR71.dll\0"
        return b"x".ljust(48) + str(len(body)).ljust(10).encode() + b"`\n" + body + b"\n" * (len(body) & 1)
    library = tmp_path / "msvcrt.lib"
    library.write_bytes(b"!<arch>\n" + member("__adjust_fdiv", 1 | 8) + member("_malloc", 0 | 8)
                        + member("__iob", 1 | 4))
    assert E.runtime_data_imports([library]) == {"__adjust_fdiv", "__iob"}


def test_export_errors_reach_blockers_and_picker_without_crashing_unowned(tmp_path, monkeypatch):
    import csv
    import repair_queue
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    (reverse / "exports.csv").write_text(
        "name,rva\n?owned@@,0x1000\n?unowned@@,0x2000\n")
    source = "Code/Owned.cpp"
    rows = [{"target_rva": "0x1000", "source": source}]
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E.census, "ledger", lambda: rows)
    owners = E.export_sources(rows)
    assert owners == {"?owned@@": source, "?unowned@@": E.EXPORT_UNOWNED}
    parsed = E.parse_errors("exit.exp : error LNK2001: unresolved external symbol ?owned@@",
                            exports_of=owners)
    assert parsed[0]["source"] == source
    errors = tmp_path / "errors.tsv"
    # Older artifacts have empty source cells; --blockers must recover them too.
    errors.write_text(
        "severity\tcode\tsymbol\tobject\tsource\ttext\n"
        "error\tLNK2001\t?owned@@\texit.exp\t\tmissing\n"
        "error\tLNK2001\t?unowned@@\texit.exp\t\tmissing\n")
    assert E.main(["--blockers", str(errors), "--blockers-commit", "a" * 40]) == 0
    path = tmp_path / E.BLOCKERS
    with path.open() as handle:
        blocks = list(csv.DictReader((line for line in handle if not line.startswith("#")),
                                     delimiter="\t"))
    assert {r["source"] for r in blocks} == {source, E.EXPORT_UNOWNED}
    assert sum(int(r["missing"]) for r in blocks) == 2
    monkeypatch.setattr(repair_queue, "rows_by_source", lambda: {source: [(0x1000, "?owned@@", 8)]})
    monkeypatch.setattr(repair_queue, "changed_since", lambda commit: set())
    items, note = repair_queue.exit_link_items(path)
    assert [item["source"] for item in items] == [source]
    assert E.EXPORT_UNOWNED in note and "not served" in note


def test_export_owner_uses_export_rva_and_retains_all_owners(tmp_path, monkeypatch):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    (reverse / "exports.csv").write_text("name,rva,target_rva\n?alias@@,0x1000,0x2000\n")
    monkeypatch.setattr(E, "ROOT", tmp_path)
    owners = E.export_sources([
        {"target_rva": "0x1000", "source": "Code/A.cpp"},
        {"target_rva": "0x1000", "source": "Code/B.cpp"},
        {"target_rva": "0x2000", "source": "Code/Other.cpp"}])
    assert owners == {"?alias@@": "Code/A.cpp, Code/B.cpp"}


@pytest.mark.parametrize("diagnostic", [False, True])
@pytest.mark.parametrize("alter,status", [
    ({}, "passed"),
    ({"uncovered_funclets": [{"name": "missing"}]}, "failed"),
    ({"outside_referrers": {"name": ["other.obj"]}}, "failed"),
    ({"uncovered_funclets_recorded": [{"name": "hidden by measurement"}]}, "failed"),
    ({"unproven_recorded": [{"name": "hidden by measurement"}]}, "failed"),
    ({"measurement_note": "past a failed proof"}, "failed"),
])
def test_receipt_authority_cannot_erase_omission_failure(tmp_path, monkeypatch, diagnostic, alter, status):
    import json
    proof = {"population_problem": None, "inspection_failures": [], "uncovered_funclets": [],
             "unproven": [], "outside_referrers": {}}
    proof.update(alter)
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    image.with_suffix(".map").write_bytes(b"map")
    monkeypatch.setattr(E, "image_commit", lambda: "a" * 40)
    E.image_receipt(image, diagnostic, [], proof=proof)
    receipt = json.loads((tmp_path / "image_receipt.json").read_text())
    assert receipt["omission_proof"] == status
    assert receipt["authoritative"] is (not diagnostic and status == "passed")


def test_empty_omission_proof_cannot_authorize_receipt():
    assert E.omission_status({}) == "not-run"


@pytest.mark.parametrize("kind,authority,staged", [
    ("real", True, True), ("real", False, False), ("real", None, False),
    ("diagnostic", True, False)])
def test_workflow_stages_only_authoritative_real_receipts(tmp_path, monkeypatch, kind, authority, staged):
    import json
    import textwrap
    text = (E.ROOT / ".github/workflows/real-link.yml").read_text()
    step = text.split("      - name: Stage real image\n", 1)[1].split(
        "      - name: Publish the result\n", 1)[0]
    code = textwrap.dedent(step.split("        run: |\n", 1)[1])
    out = tmp_path / "build/exit_link"
    out.mkdir(parents=True)
    for name in ("exit.exe", "exit.map"):
        (out / name).write_bytes(name.encode())
    receipt = {"kind": kind}
    if authority is not None:
        receipt["authoritative"] = authority
    (out / "image_receipt.json").write_text(json.dumps(receipt))
    monkeypatch.chdir(tmp_path)
    exec(compile(code, "real-link.yml:Stage real image", "exec"), {})
    assert (out / "image/exit.exe").exists() is staged


def test_diagnostic_step_has_its_own_nonfatal_timeout():
    text = (E.ROOT / ".github/workflows/real-link.yml").read_text()
    step = text.split("      - name: Diagnostic link\n", 1)[1].split("      - name:", 1)[0]
    assert "timeout-minutes: 60" in step
    assert "continue-on-error: true" in step
    assert "if: always()" in step


def test_import_stubs_are_relocated_pointers_to_distinct_traps(tmp_path):
    names = {"__imp__First@4", "__imp__Second@0", "_direct"}
    path = E.diagnostic_stubs(names, tmp_path / "diagnostic_stubs.obj")
    raw = path.read_bytes()
    sections, symbols = E.link_cycle.parse_coff(raw)
    by_name = {sym.name: sym for sym in symbols.values()}
    layout = {entry["name"]: entry for entry in E.diagnostic_stub_layout(names)}
    bodies = []
    for name in names:
        entry, symbol = layout[name], by_name[name]
        assert symbol.value == entry["offset"] and symbol.sec == 1
        assert entry["trap_symbol"] == name
        bodies.append(entry["trap_offset"])
        assert raw[sections[0].ptr + entry["trap_offset"]:
                   sections[0].ptr + entry["trap_offset"] + 16] == b"\xcc" * 16
        if name.startswith("__imp_"):
            assert entry["kind"] == "import-pointer" and entry["section"] == ".text"
            rel = next(rel for rel in sections[0].relocs if rel[0] == symbol.value)
            assert symbols[rel[1]].name == name
            assert rel[2] == E.link_cycle.DIR32
            assert struct.unpack_from("<I", raw, sections[0].ptr + symbol.value)[0] == 4
            assert entry["trap_offset"] == symbol.value + 4
        else:
            assert entry["kind"] == "trap" and entry["trap_offset"] == symbol.value
    assert len(set(bodies)) == len(names)
    assert len(symbols) == len(names)  # no helper aliases hiding the original IAT name
    assert not sections[0].flags & COMDAT


def test_import_stubs_keep_even_helper_like_requested_names(tmp_path):
    names = {"__imp__X", "__diagnostic_trap_for___imp__X"}
    path = E.diagnostic_stubs(names, tmp_path / "stubs.obj")
    _sections, symbols = E.link_cycle.parse_coff(path.read_bytes())
    assert {sym.name for sym in symbols.values()} == names


def test_receipt_counts_vtable_debt_without_changing_measurement_authority(tmp_path, monkeypatch):
    import json
    image = tmp_path / "exit.exe"
    image.write_bytes(b"image")
    image.with_suffix(".map").write_bytes(b"map")
    proof = {"population_problem": None, "inspection_failures": [], "uncovered_funclets": [],
             "unproven": [], "outside_referrers": {}}
    monkeypatch.setattr(E, "image_commit", lambda: "a" * 40)
    E.image_receipt(image, False, [], proof=proof, vtables={"tables": 2, "slots": 9})
    receipt = json.loads((tmp_path / "image_receipt.json").read_text())
    assert receipt["vtables_bridged"] == 2 and receipt["vtable_slots_bridged"] == 9
    assert receipt["authoritative"] is True  # strict-link authority is not a G1 pass


def test_workflow_counts_both_bridges_and_leaves_old_or_refused_results_unknown():
    import ast
    import textwrap
    text = (E.ROOT / ".github/workflows/real-link.yml").read_text()
    step = text.split("      - name: Real link\n", 1)[1].split("      - name:", 1)[0]
    code = textwrap.dedent(step.split("        run: |\n", 1)[1])
    calls = [node for node in ast.walk(ast.parse(code)) if isinstance(node, ast.Call)
             and isinstance(node.func, ast.Attribute) and node.func.attr == "update"
             and isinstance(node.func.value, ast.Name) and node.func.value.id == "board"]
    fields = {kw.arg: kw.value for kw in calls[0].keywords}
    data = {"initializer_bridge": {"entries": 7}, "vtable_bridge": {"tables": 2, "slots": 9}}
    for name, expected in (("initializers_bridged", 7), ("vtables_bridged", 2), ("vtable_slots_bridged", 9)):
        expr = compile(ast.Expression(fields[name]), "real-link.yml", "eval")
        assert eval(expr, {"data": data}) == expected
        assert eval(expr, {"data": {}}) is None
    assert text.count("vtable_bridge_queue.tsv") == 2
    assert text.count("vtable_bridge.json") == 2


def test_link_setup_puts_vtable_bridge_first_without_changing_original_order(tmp_path, monkeypatch):
    import image_report
    import vtable_bridge
    original = [tmp_path / "a.obj", tmp_path / "b.obj"]
    initializer = tmp_path / "retail_initializers.obj"
    vtables = tmp_path / "retail_vtables.obj"
    monkeypatch.setattr(E, "OUT", tmp_path)
    monkeypatch.setattr(E, "placement_objects", lambda rows: {})
    monkeypatch.setattr(E.link_cycle, "Objects", lambda paths: object())
    monkeypatch.setattr(E.census, "retail_imports", lambda: {})
    monkeypatch.setattr(E.link_cycle, "undefined_imports", lambda objects: set())
    monkeypatch.setattr(E.link_cycle, "undefined_plain_imports", lambda objects, imports: set())
    monkeypatch.setattr(E, "harness_import_roots", lambda requests: (set(), set()))
    monkeypatch.setattr(E.link_cycle, "import_def_entries", lambda *args: ({}, set()))
    monkeypatch.setattr(E.link_cycle, "runtime_libraries", lambda: [])
    monkeypatch.setattr(E.link_cycle, "defined_externals", lambda objects: set())
    monkeypatch.setattr(E, "runtime_data_imports", lambda libraries: set())
    monkeypatch.setattr(E, "make_import_libs", lambda *args: [])
    monkeypatch.setattr(E, "initializer_table", lambda rows, inputs: (
        initializer, {"entries": 7, "unreachable": []}))
    retail = tmp_path / "retail.exe"
    retail.write_bytes(b"retail")
    monkeypatch.setattr(E.build, "EXE", retail)
    monkeypatch.setattr(image_report, "Retail", lambda raw: object())
    sources = {original[0]: "Code/A.cpp", original[1]: "Code/B.cpp"}
    monkeypatch.setattr(E.census, "_object_sources", lambda rows: sources)
    def generated(rows, inputs, omitted, libraries, out, retail, objects=None, source_of=None):
        assert inputs == original and omitted == set() and source_of == sources
        return vtables, {"object": vtables.name, "tables": 2, "slots": 9}
    monkeypatch.setattr(vtable_bridge, "build_bridge", generated)
    inputs, metadata = E.link_setup([], original)
    assert inputs[:4] == [vtables, initializer] + original
    assert metadata["initializer_bridge"]["entries"] == 7
    assert metadata["vtable_bridge"]["slots"] == 9


def test_report_shows_generated_vtable_retirement_count(tmp_path, monkeypatch, capsys):
    import json
    monkeypatch.setattr(E, "OUT", tmp_path)
    (tmp_path / "result.json").write_text(json.dumps({
        "when": "now", "commit": "a" * 40, "base": "0x10000000",
        "objects": {"linked": 3, "omitted_count": 17},
        "link": {"exit": 96, "image_written": False},
        "errors": {"unresolved": 7, "duplicates": 0, "total": 8, "unresolved_classes": {},
                   "unresolved_exclusive_to_omitted": []},
        "vtable_bridge": {"tables": 2, "slots": 9, "refused_tables": 4, "already_correct": 5}}))
    assert E.report() == 0
    text = capsys.readouterr().out
    assert "vtable bridge 2 table(s), 9 slot(s)" in text
    assert "must reach 0 for G1" in text


def test_blockers_publish_real_link_bridge_queue_and_preserve_source_evidence(tmp_path, monkeypatch):
    import csv
    import json
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E.census, "ledger", lambda: [])
    monkeypatch.setattr(E, "export_sources", lambda rows: {})
    (tmp_path / "reverse").mkdir()
    errors = tmp_path / "errors.tsv"
    errors.write_text("code\tsource\tsymbol\nLNK2001\tCode/A.cpp\t_missing\n")
    bridge = {"refusals": [{"rva": 0x3000, "name": "_refused", "reason": "omitted-target",
                            "source": "Code/A.cpp", "slots": 2}],
              "entries": [{"rva": 0x4000, "name": "_bridged", "source": "Code/B.cpp", "slots": [],
                           "source_slot_mismatches": [{"name": "_wrong", "ledger_rvas": [0x1111]}]}]}
    record = {"mode": "exit-link", "force": False, "stubs": False,
              "commit": "a" * 40, "vtable_bridge": bridge}
    (tmp_path / "result.json").write_text(json.dumps(record))
    assert E.main(["--blockers", str(errors), "--blockers-commit", "a" * 40]) == 0
    lines = (tmp_path / "reverse/vtable_bridge_queue.tsv").read_text().splitlines()
    queued = list(csv.DictReader(lines[1:], delimiter="\t"))
    assert [row["state"] for row in queued] == ["refused", "bridged"]
    assert "_wrong" in queued[1]["evidence"] and "4369" in queued[1]["evidence"]


@pytest.mark.parametrize("mode,commit,stubs", [
    ("diagnostic-link", "a" * 40, True), ("exit-link", "b" * 40, False)])
def test_blockers_refuse_diagnostic_or_wrong_commit_before_writing(tmp_path, monkeypatch, mode, commit, stubs):
    import json
    monkeypatch.setattr(E, "ROOT", tmp_path)
    (tmp_path / "result.json").write_text(json.dumps(
        {"mode": mode, "commit": commit, "force": False, "stubs": stubs}))
    errors = tmp_path / "errors.tsv"
    errors.write_text("code\tsource\tsymbol\n")
    with pytest.raises(ValueError, match="matching unstubbed real-link"):
        E.write_blockers(errors, "a" * 40)
    assert not (tmp_path / "reverse").exists()

def test_blockers_accept_the_abbreviated_commit_result_json_records(tmp_path, monkeypatch):
    import json
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E.census, "ledger", lambda: [])
    monkeypatch.setattr(E, "export_sources", lambda rows: {})
    (tmp_path / "reverse").mkdir()
    (tmp_path / "result.json").write_text(json.dumps(
        {"mode": "exit-link", "commit": "c63ea1df21", "force": False, "stubs": False}))
    errors = tmp_path / "errors.tsv"
    errors.write_text("code\tsource\tsymbol\n")
    assert E.write_blockers(errors, "c63ea1df21" + "0" * 30) == 0
    with pytest.raises(ValueError, match="matching unstubbed real-link"):
        E.write_blockers(errors, "d" * 40)


def test_old_artifact_without_bridge_metadata_does_not_erase_last_queue(tmp_path, monkeypatch):
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E.census, "ledger", lambda: [])
    monkeypatch.setattr(E, "export_sources", lambda rows: {})
    (tmp_path / "reverse").mkdir()
    queue = tmp_path / "reverse/vtable_bridge_queue.tsv"
    queue.write_text("last measured queue\n")
    errors = tmp_path / "errors.tsv"
    errors.write_text("code\tsource\tsymbol\n")
    assert E.write_blockers(errors, "a" * 40) == 0
    assert queue.read_text() == "last measured queue\n"


def test_parallel_currency_keeps_the_serial_answer_and_order(tmp_path, monkeypatch):
    sources = {tmp_path / f"{i:03}.obj": tmp_path / f"{i:03}.cpp" for i in range(250)}
    present = sorted(sources, reverse=True) + [tmp_path / "member.obj"]   # a library member has no source
    monkeypatch.setenv("BUILD_POOL", "1")
    serial = E.stale_objects(present, sources)
    monkeypatch.setenv("BUILD_POOL", "3")
    assert E.stale_objects(present, sources) == serial == present[:-1]   # no object exists: all stale


def _seed(tmp_path, names):
    seed = tmp_path / "stubbed.tsv"
    seed.write_text("name\toffset\n" + "".join(f"{name}\t0x0\n" for name in names))
    return seed


def test_stub_seed_keeps_only_names_this_link_predicts_unresolved(tmp_path, monkeypatch):
    from test_link_census_prediction import coff
    L = E.census
    kept = coff(tmp_path / "kept.obj", [
        ("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []), ("_e", 1, 4, L.EXTERNAL, []),
        ("_a", 0, 0, L.EXTERNAL, []), ("_b", 0, 0, L.EXTERNAL, []), ("_c", 0, 0, L.EXTERNAL, []),
        ("_common", 0, 4, L.EXTERNAL, [])])
    bridge = coff(tmp_path / "bridge.obj", [("_b", 1, 0, L.EXTERNAL, [])])
    monkeypatch.setattr(E.census, "library_symbols", lambda path: {"_c"})
    seed = _seed(tmp_path, ["_a", "_b", "_c", "_e", "_z", "_common", "?x@@3HA", "?y@@3HA"])
    got = E.seeded_stubs(seed, [kept, bridge], [tmp_path / "imp.lib"], {"?x@@3HA", "_e"})
    # _b a generated object defines, _c a library, _e the object itself; _z and ?y@@3HA nothing
    # references; _common is a COMMON definition; ?x@@3HA only an export references.
    assert got["names"] == ["?x@@3HA", "_a"]
    assert got["offered"] == 8 and got["dropped"] is False


def test_stub_seed_leaves_an_alias_whose_target_this_build_defines(tmp_path, monkeypatch):
    # Codex review of 38b5ca68d6: a name an earlier link stubbed, now reached through
    # /alternatename or a weak external's default, must link to the real code, not a trap.
    from test_link_census_prediction import coff, weak_aux
    L = E.census
    user = coff(tmp_path / "user.obj", [
        ("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []),
        ("_Alias", 0, 0, L.EXTERNAL, []),
        ("_Weak", 0, 0, L.WEAK_EXTERNAL, [weak_aux(4)]),      # default: symbol 4, _Real
        ("_Real", 0, 0, L.EXTERNAL, []),
        ("_ToLib", 0, 0, L.EXTERNAL, []),
        ("_Gone", 0, 0, L.EXTERNAL, [])],
        drectve=b"/alternatename:_Alias=_Real /alternatename:_ToLib=_LibReal ")
    real = coff(tmp_path / "real.obj", [("_Real", 1, 0, L.EXTERNAL, [])])
    monkeypatch.setattr(E.census, "library_symbols", lambda path: {"_LibReal"})
    seed = _seed(tmp_path, ["_Alias", "_Weak", "_ToLib", "_Gone"])
    assert E.seeded_stubs(seed, [user, real], [tmp_path / "msvcrt.lib"])["names"] == ["_Gone"]


def test_stub_seed_leaves_an_import_this_build_defines_locally(tmp_path):
    # Codex review of 38b5ca68d6: __imp__Local binds to a now-local _Local (LNK4217).
    from test_link_census_prediction import coff
    L = E.census
    user = coff(tmp_path / "user.obj", [
        ("_WinMainCRTStartup", 1, 0, L.EXTERNAL, []),
        ("__imp__Local", 0, 0, L.EXTERNAL, []), ("__imp__Remote", 0, 0, L.EXTERNAL, [])])
    local = coff(tmp_path / "local.obj", [("_Local", 1, 0, L.EXTERNAL, [])])
    seed = _seed(tmp_path, ["__imp__Local", "__imp__Remote"])
    assert E.seeded_stubs(seed, [user, local], [])["names"] == ["__imp__Remote"]


def test_an_unreadable_object_seeds_nothing(tmp_path):
    seed = _seed(tmp_path, ["_a"])
    assert E.seeded_stubs(seed, [tmp_path / "gone.obj"], [])["names"] == []


def test_a_seed_that_clashes_is_dropped_and_the_link_iterates_as_without_one(tmp_path, monkeypatch):
    import json
    import types
    root = tmp_path
    measured = root / "build/exit_link"
    measured.mkdir(parents=True)
    monkeypatch.setattr(E, "ROOT", root)
    monkeypatch.setattr(E.census, "ROOT", root)
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

    def setup(rows, present):
        return [root / "absolute.obj"], {"import_libraries": [], "harness_import_symbols": []}
    monkeypatch.setattr(E, "link_setup", setup)
    monkeypatch.setattr(E, "export_names", lambda: set())
    monkeypatch.setattr(E, "seeded_stubs", lambda *a: {"file": "seed.tsv", "offered": 2, "names": ["_Seeded"],
                                                        "dropped": False})
    rsp = root / "build/diagnostic_link/exit.rsp"

    def command(inputs, image, out, roots):
        rsp.write_text('"absolute.obj"\n')
        return ["fixture-linker"], rsp
    monkeypatch.setattr(E, "link_command", command)
    monkeypatch.setattr(E.census, "census_state", lambda *a: {})
    monkeypatch.setattr(E, "tool_digests", lambda: {})
    responses = []
    results = iter([
        types.SimpleNamespace(returncode=96, stdout=(
            "absolute.obj : error LNK2005: _Seeded already defined in diagnostic_stubs.obj\n"), stderr=""),
        types.SimpleNamespace(returncode=96, stdout=(
            "fixture.obj : error LNK2001: unresolved external symbol __imp__Missing@4\n"), stderr=""),
        types.SimpleNamespace(returncode=0, stdout="", stderr="")])

    def link(*a, **k):
        responses.append(rsp.read_text())
        return next(results)
    monkeypatch.setattr(E, "run_native", link)
    monkeypatch.setattr(E, "object_sources", lambda rows: {})
    monkeypatch.setattr(E, "export_sources", lambda rows: {})
    monkeypatch.setattr(E.census, "classify", lambda *a: ({}, {}, {}, {}))
    monkeypatch.setattr(E, "placement_objects", lambda rows: [])
    monkeypatch.setattr(E, "published_index_meta", lambda: {})
    monkeypatch.setattr(E.census, "head", lambda: "a" * 40)
    assert E.run_diagnostic([], root / "seed.tsv") == 1  # fake linker wrote no image
    diagnostic = root / "build/diagnostic_link"
    assert "diagnostic_stubs.obj" in responses[0]              # the seeded first pass
    assert responses[1] == '"absolute.obj"\n'                  # the seed dropped: no stub object
    assert "diagnostic_stubs.obj" in responses[2]              # then the ordinary stubbing pass
    result = json.loads((diagnostic / "result.json").read_text())
    assert result["link"]["passes"] == 3
    assert result["stub_seed"] == {"file": "seed.tsv", "offered": 2, "seeded": 1, "dropped": True}
    assert not (diagnostic / "image_receipt.json").exists()      # no image, no receipt
    assert [row.split("\t")[0] for row in (diagnostic / "stubbed.tsv").read_text().splitlines()[1:]] == [
        "__imp__Missing@4"]
    assert E.OUT == measured


def test_stub_seed_is_for_the_diagnostic_link_only(tmp_path):
    with pytest.raises(SystemExit):
        E.main(["--link", "--stub-seed", str(tmp_path / "stubbed.tsv")])


def test_a_seeded_diagnostic_receipt_says_so_and_a_real_one_has_no_seed_field(tmp_path, monkeypatch):
    import json
    image = tmp_path / "exit.exe"
    image.write_bytes(b"MZ")
    image.with_suffix(".map").write_text("map")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/exports.csv").write_text("name,ordinal,kind\n")
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E, "image_commit", lambda: "c" * 40)
    seed = {"file": "s.tsv", "offered": 198, "seeded": 198, "dropped": False}
    E.image_receipt(image, True, {"_a"}, seed=seed)
    assert json.loads((tmp_path / "image_receipt.json").read_text())["stub_seed"] == seed
    E.image_receipt(image, True, {"_a"})
    assert json.loads((tmp_path / "image_receipt.json").read_text())["stub_seed"] is None
    E.image_receipt(image, False, set())
    assert "stub_seed" not in json.loads((tmp_path / "image_receipt.json").read_text())
