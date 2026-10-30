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
    with pytest.raises(SystemExit, match="boat sandbox"):
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
