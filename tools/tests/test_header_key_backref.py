"""Class-key changes resolve name references without changing their digits.

The operator and pointer-return cases were independently compiled with MSVC;
retail-ledger template mappings were independently decoded with DbgHelp. These
checks need neither compiler nor DbgHelp. Unknown grammar still refuses a unit.
"""
import csv
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as hal

COLUMNS = ["name", "demangled", "target_rva", "target_size", "source", "status", "notes"]


def rows(*names, source="Code/Unit.cpp"):
    return [dict(zip(COLUMNS, [n, "", "0x1000", "4", source, "matched", ""])) for n in names]


def ledger(tmp_path, monkeypatch, records):
    path = tmp_path / "functions.csv"
    with path.open("w", newline="", encoding="utf-8") as handle:
        out = csv.DictWriter(handle, COLUMNS)
        out.writeheader()
        out.writerows(records)
    monkeypatch.setattr(hal, "LEDGER", path)
    return path


CHANGES = [
    ("?CoordKeyProbe@@YAPAUCoord3D@@PAU1@@Z",
     "?CoordKeyProbe@@YAPAVCoord3D@@PAV1@@Z"),
    ("??8Coord3D@@QAE_NABU0@@Z", "??8Coord3D@@QAE_NABV0@@Z"),
    ("??0Coord3D@@QAE@ABU0@@Z", "??0Coord3D@@QAE@ABV0@@Z"),
    ("?equals@Coord3D@@QBE_NABU1@@Z", "?equals@Coord3D@@QBE_NABV1@@Z"),
    ("?Rva003AFA64FillUnitVector@@YAPAUCoord3D@@PAU1@@Z",
     "?Rva003AFA64FillUnitVector@@YAPAVCoord3D@@PAV1@@Z"),
    ("?getPlanarDirectionTo@Object@@QBEPAUCoord3D@@PAU2@PBV1@@Z",
     "?getPlanarDirectionTo@Object@@QBEPAVCoord3D@@PAV2@PBV1@@Z"),
    ("??$fill@PAUCoord3D@@U1@@_STL@@YAXPAUCoord3D@@0ABU1@@Z",
     "??$fill@PAVCoord3D@@V1@@_STL@@YAXPAVCoord3D@@0ABV1@@Z"),
    ("??$uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@@Z",
     "??$uninitialized_fill_n@PAVCoord3D@@IV1@@_STL@@YAPAVCoord3D@@PAV1@IABV1@@Z"),
    ("?rva002EBC34@Rva002EBC34@@QAEPAUICoord2D@@PAU2@PAXPBUCoord3D@@@Z",
     "?rva002EBC34@Rva002EBC34@@QAEPAUICoord2D@@PAU2@PAXPBVCoord3D@@@Z"),
    ("?f@@YAXV?$Box@UCoord3D@@@@PAUCoord3D@@PAU2@@Z",
     "?f@@YAXV?$Box@VCoord3D@@@@PAVCoord3D@@PAV2@@Z"),
    # A different qualified class supplies the identifier for a global U1@.
    ("?f@@YAXPAUCoord3D@Other@@PAU1@@Z",
     "?f@@YAXPAUCoord3D@Other@@PAV1@@Z"),
    # Even the function identifier can supply the global type's name entry.
    ("?Coord3D@@YAXPAU0@@Z", "?Coord3D@@YAXPAV0@@Z"),
    ("?expandBy@Region3D@@QAEXABUCoord3D@@@Z",
     "?expandBy@Region3D@@QAEXABVCoord3D@@@Z"),
    # Nested callbacks share the argument table. Return types themselves are
    # not memorized, but the callback parameters within them are.
    ("?f@@YAXP6AXPAUCoord3D@@0@Z0@Z", "?f@@YAXP6AXPAVCoord3D@@0@Z0@Z"),
    ("?f@@YAXPAUCoord3D@@P6AX0@Z0@Z", "?f@@YAXPAVCoord3D@@P6AX0@Z0@Z"),
    ("?f@@YAP6AXPAUCoord3D@@0@Z0@Z", "?f@@YAP6AXPAVCoord3D@@0@Z0@Z"),
    # Repeated literal long types consume distinct slots; scalar H does not.
    ("?f@@YAXPAUCoord3D@@PAUCoord3D@@PAJ2@Z", "?f@@YAXPAVCoord3D@@PAVCoord3D@@PAJ2@Z"),
    ("?f@@YAX_N0PAUCoord3D@@1@Z", "?f@@YAX_N0PAVCoord3D@@1@Z"),
]


@pytest.mark.parametrize("before,after", CHANGES)
@pytest.mark.parametrize("prefix,suffix", [("", ""), ("__ehhandler$", ""),
                                            ("__unwindfunclet$", "$12")])
def test_exact_rewrite_and_inverse(before, after, prefix, suffix):
    before, after = prefix + before + suffix, prefix + after + suffix
    assert hal.rekey_symbol(before, "Coord3D", "U") == after
    assert hal.rekey_symbol(after, "Coord3D", "V") == before
    assert hal.key_backref_names(rows(before), "Coord3D", "U") == []


@pytest.mark.parametrize("name", [
    "?length@Coord3D@@QBEMXZ",
    # Ordinary member name occupies entry 0; Coord3D occupies entry 1.
    "?equals@Coord3D@@QBE_NABU0@@Z",
    "??4ICoord3D@@QAEAAU0@ABU0@@Z",
    "??6@YAAAVDebug@@AAV0@ABUICoord3D@@@Z",
    "?f@@YAXPAUICoord3D@@PAU1@@Z",
    "?f@@YAXPAUCoord3D@Other@@PAU12@@Z",
    "?GetXVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z",
    # A union is a distinct key and may not be silently rekeyed.
    "?f@@YAXPATCoord3D@@@Z",
    "_Coord3D@4",
])
def test_other_types_and_keys_are_preserved(name):
    assert hal.rekey_symbol(name, "Coord3D", "U") == name


def test_qualified_target_is_exact():
    name = "?f@@YAXPAUCoord3D@Other@@PAU12@PAU1@@Z"
    expected = "?f@@YAXPAVCoord3D@Other@@PAV12@PAU1@@Z"
    assert hal.rekey_symbol(name, "Coord3D@Other", "U") == expected
    assert hal.rekey_symbol(expected, "Coord3D@Other", "V") == name


BAD = [
    "?f@@YAXPAUCoord3D@@PAU9@@Z",  # name reference outside the table
    "?f@@YAXPAUCoord3D@@9@Z",  # argument-type reference outside the table
    "?f@@YAXH0PAUCoord3D@@@Z",  # single-character scalars are not memorized
    "?f@@YAP6AXPAUCoord3D@@0@Z1@Z",  # return itself supplies no argument slot
    "?f@@YAXPAUCoord3D@@PAVCoord3D@@@Z",  # mixed target keys
    "?f@@YAXPAUCoord3D@@PAT1@@Z",  # same target under struct and union keys
    "?f@@YAXPAUCoord3D@@@Zjunk",
    "?f@@YAXPAUCoord3D@@@",
    # Unknown local scopes and adjustor headers remain conservative refusals.
    "?f@?1??g@@YAXXZ@YAXPAUCoord3D@@@Z",
    "?f@Host@@W3AEXPAUCoord3D@@@Z",
    # Rekeying these template instances would collapse two name-table entries.
    "?f@@YAXV?$Box@UCoord3D@@@@V?$Box@VCoord3D@@@@@Z",
]


@pytest.mark.parametrize("name", BAD)
def test_unknown_or_ambiguous_name_refuses_instead_of_guessing(name):
    with pytest.raises(ValueError):
        hal.rekey_symbol(name, "Coord3D", "U")
    assert hal.key_backref_names(rows(name), "Coord3D", "U") == [name]


def test_all_planning_sites_include_resolved_backreferences(tmp_path, monkeypatch):
    source = "Code/Unit.cpp"
    (tmp_path / "Code").mkdir()
    (tmp_path / source).write_text("struct Coord3D { float x, y, z; };\n")
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    records = rows(*(before for before, _ in CHANGES), source=source)
    ledger(tmp_path, monkeypatch, records)
    assert hal.ledger_renames(source, "Coord3D", "class") == (CHANGES, None)
    assert hal.prospective_renames([source], "Coord3D", "class") == [(source, None, None, CHANGES)]
    assert hal.key_backref_blockers([source], "Coord3D", "class") == {}


def test_one_unsupported_row_refuses_the_whole_unit(tmp_path, monkeypatch):
    bad, good = "Code/Bad.cpp", "Code/Good.cpp"
    (tmp_path / "Code").mkdir()
    for source in (bad, good):
        (tmp_path / source).write_text("struct Coord3D { float x, y, z; };\n")
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    ledger(tmp_path, monkeypatch, rows(CHANGES[0][0], BAD[0], source=bad) + rows(CHANGES[0][0], source=good))
    renames, why = hal.ledger_renames(bad, "Coord3D", "class")
    assert renames == [] and BAD[0] in why
    assert hal.prospective_renames([bad, good], "Coord3D", "class") == [(good, None, None, [CHANGES[0]])]
    blockers = hal.key_backref_blockers([bad, good], "Coord3D", "class")
    assert set(blockers) == {bad} and BAD[0] in blockers[bad]


@pytest.mark.parametrize("failure", ["none", "caller", "exception"])
def test_coordinated_backreference_trial_restores_all_inputs(tmp_path, monkeypatch, failure):
    sources = ["Code/Provider.cpp", "Code/Caller.cpp"]
    (tmp_path / "Code").mkdir()
    originals = {}
    for source in sources:
        originals[source] = b"struct Coord3D { float x, y, z; };\n"
        (tmp_path / source).write_bytes(originals[source])
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    path = ledger(tmp_path, monkeypatch, rows(CHANGES[0][0], source=sources[0]) +
                  rows(CHANGES[1][0], source=sources[1]))
    original_ledger = path.read_bytes()
    monkeypatch.setattr(hal, "field_renames", lambda *args, **kw: ({}, None))
    monkeypatch.setattr(hal, "adoption_dependencies",
                        lambda items: {sources[0]: {CHANGES[0][0]: [sources[1]]}})

    def gate(current):
        assert current == sources
        with path.open(newline="", encoding="utf-8") as handle:
            names = [r["name"] for r in csv.DictReader(handle)]
        assert names == [CHANGES[0][1], CHANGES[1][1]]
        assert all(b"struct Coord3D" not in (tmp_path / s).read_bytes() for s in sources)
        if failure == "exception":
            raise RuntimeError("gate interrupted")
        return {s: "caller mismatch" if failure == "caller" and s == sources[1] else None for s in current}

    monkeypatch.setattr(hal, "gate_many", gate)
    if failure == "exception":
        with pytest.raises(RuntimeError, match="gate interrupted"):
            hal.try_units(sources, ["Coord3D"], "Coord3D.h", "class")
    else:
        got = hal.try_units(sources, ["Coord3D"], "Coord3D.h", "class")
        if failure == "caller":
            assert "symbol dependencies" in got[0][1]
            assert got[1][1] == "caller mismatch"
        else:
            assert all(why is None for _, why, _, _ in got)
    assert path.read_bytes() == original_ledger
    assert all((tmp_path / s).read_bytes() == originals[s] for s in sources)


@pytest.mark.parametrize("metadata", ["parent", "family", "pin", "data", "owner", "baseline",
                                      "tombstone", "collision"])
def test_metadata_refusal_precedes_every_source_or_ledger_write(tmp_path, monkeypatch, metadata):
    source = "Code/Unit.cpp"
    (tmp_path / "Code").mkdir()
    (tmp_path / "reverse").mkdir()
    original = b"struct Coord3D { float x, y, z; };\n"
    (tmp_path / source).write_bytes(original)
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    before, after = CHANGES[0]
    records = rows(before, source=source)
    if metadata == "parent":
        # A metadata-only row outside the trial is still part of the family.
        parent = rows("uw_other", source="Code/Other.cpp")[0]
        parent["notes"] = "kind=funclet;parent=" + before
        records.append(parent)
    elif metadata == "collision":
        records += rows(after, source="Code/Other.cpp")
    elif metadata == "family":
        records += rows("__ehhandler$" + before, source="Code/Other.cpp")
    elif metadata == "baseline":
        (tmp_path / "reverse/code_identity_baseline.tsv").write_text(source + "\t" + before + "\n")
    else:
        filename = {"pin": "symbols.csv", "data": "data_rows.csv", "owner": "body_owners.csv",
                    "tombstone": "deleted_rows.csv"}[metadata]
        name = after if metadata == "tombstone" else before
        (tmp_path / "reverse" / filename).write_text("name,address,notes\n" + name + ",0x1000,existing\n")
    path = ledger(tmp_path, monkeypatch, records)
    original_ledger = path.read_bytes()
    monkeypatch.setattr(hal, "adoption_dependencies", lambda items: {})
    monkeypatch.setattr(hal, "prepare_unit", lambda *args: pytest.fail("blocked metadata reached preparation"))
    monkeypatch.setattr(hal, "gate_many", lambda *args: pytest.fail("blocked metadata reached byte gate"))
    got = hal.try_units([source], ["Coord3D"], "Coord3D.h", "class")
    assert "class-key metadata" in got[0][1]
    assert hal.ledger_renames(source, "Coord3D", "class")[0] == []
    with pytest.raises(ValueError, match="class-key metadata"):
        hal.rewrite_ledger([(before, after)])
    assert path.read_bytes() == original_ledger
    assert (tmp_path / source).read_bytes() == original


@pytest.mark.parametrize("quoted", [False, True])
def test_ledger_rewrite_preserves_other_fields_quotes_and_terminators(tmp_path, monkeypatch, quoted):
    before, after = CHANGES[0]
    path = ledger(tmp_path, monkeypatch, [])
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    first = '"' + before + '"' if quoted else before
    wanted = '"' + after + '"' if quoted else after
    tail = ',,0x1000,4,Code/Unit.cpp,matched,"comma, double ""quote"""\r\n'
    unchanged = b'?unrelated@@YAXXZ,,0x2000,4,Code/Other.cpp,matched,plain\n'
    prefix = (','.join(COLUMNS) + '\r\n').encode()
    path.write_bytes(prefix + (first + tail).encode() + unchanged)
    hal.rewrite_ledger([(before, after)])
    assert path.read_bytes() == prefix + (wanted + tail).encode() + unchanged
