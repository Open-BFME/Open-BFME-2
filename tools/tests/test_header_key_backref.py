"""Class-key changes resolve name references without changing their digits.

The operator and pointer-return cases were independently compiled with MSVC;
retail-ledger template mappings were independently decoded with DbgHelp. These
checks need neither compiler nor DbgHelp. Unknown grammar still refuses a unit.
"""
import csv
import re
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
    # A name back-reference after a local scope: whether the local piece enters
    # the outer table is not proven, so it refuses.
    "?f@?1??g@@YAXXZ@YAXPAUCoord3D@@PAU1@@Z",
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



# ---------------------------------------------------------------- local scopes, thunks, the migration

LOCAL_AND_THUNK = [
    # Local scopes: '?<number>?<the enclosing function's own symbol>'.
    ("?f@?1??g@@YAXXZ@YAXPAUCoord3D@@@Z", "?f@?1??g@@YAXXZ@YAXPAVCoord3D@@@Z"),
    ("?color2@?M@??createEvent@Radar@@QAEXPBUCoord3D@@W4RadarEventType@@M@Z@4URGBAColorInt@@A",
     "?color2@?M@??createEvent@Radar@@QAEXPBVCoord3D@@W4RadarEventType@@M@Z@4URGBAColorInt@@A"),
    ("?$S1@?1??getCurrentBonePositions@W3DModelDraw@@UBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z@4IA",
     "?$S1@?1??getCurrentBonePositions@W3DModelDraw@@UBEHPBDHPAVCoord3D@@PAVMatrix3D@@H@Z@4IA"),
    ("??__Fgeometry@?1??Rva009F66F0@@YAMPBUCoord3D@@PAVRva009F66F0Provider@@M@Z@YAXXZ",
     "??__Fgeometry@?1??Rva009F66F0@@YAMPBVCoord3D@@PAVRva009F66F0Provider@@M@Z@YAXXZ"),
    # The nested symbol keeps its own tables: its 1@ is its own Coord3D entry.
    ("?x@?1??f@@YAXPAUCoord3D@@PAU1@@Z@4HA", "?x@?1??f@@YAXPAVCoord3D@@PAV1@@Z@4HA"),
    # Adjustor thunks: W<adjustment>, then a member signature.
    ("?f@Host@@W3AEXPAUCoord3D@@@Z", "?f@Host@@W3AEXPAVCoord3D@@@Z"),
    ("?construct@DozerAIUpdate@@WDOE@AEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@_NH@Z",
     "?construct@DozerAIUpdate@@WDOE@AEPAVObject@@PBVThingTemplate@@PBVCoord3D@@MPAVPlayer@@_NH@Z"),
    # Neighbouring classes keep their own keys.
    ("??4Coord3D@@QAEAAU0@ABUCoord3DBase@@@Z", "??4Coord3D@@QAEAAV0@ABUCoord3DBase@@@Z"),
    ("?f@@YAXPAUICoord3D@@PAUCoord3D@@@Z", "?f@@YAXPAUICoord3D@@PAVCoord3D@@@Z"),
]


@pytest.mark.parametrize("before,after", LOCAL_AND_THUNK)
def test_local_scopes_and_thunks_rewrite_exactly_and_invert(before, after):
    assert hal.rekey_symbol(before, "Coord3D", "U") == after
    assert hal.rekey_symbol(after, "Coord3D", "V") == before


def test_mixed_name_rewrites_only_when_the_migration_allows_it():
    name, whole = "?GetXVector@Matrix4D@@QBEAAUCoord3D@@AAV2@@Z", "?GetXVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z"
    with pytest.raises(ValueError):
        hal.rekey_symbol(name, "Coord3D", "U")
    assert hal.rekey_symbol(name, "Coord3D", "U", allow_mixed=True) == whole
    # Never when the rewrite would merge two name-table entries.
    with pytest.raises(ValueError):
        hal.rekey_symbol("?f@@YAXV?$Box@UCoord3D@@@@V?$Box@VCoord3D@@@@@Z", "Coord3D", "U", allow_mixed=True)


def test_rewrites_change_only_key_letters():
    for before, after in CHANGES + LOCAL_AND_THUNK:
        diff = [(a, b) for a, b in zip(before, after) if a != b]
        assert len(before) == len(after) and diff and set(diff) == {("U", "V")}


import json
import subprocess
from collections import Counter

import dup_defs


def tree(tmp_path, monkeypatch, *, functions="", symbols="", data_rows="", deleted="", hatch="", unit=None,
         dup="", exports=("class",), converged=None, extra=None):
    """A miniature registered-class tree in a git repository."""
    files = {
        "reverse/canonical_classes.csv": "class,header,note\nCoord3D,Code/Lib/Coord3D.h,generated\n",
        "reverse/class_contracts/Coord3D.json":
            '{\n "class": "Coord3D",\n "key": "struct",\n "key_by": "bytes",\n "size": 12\n}\n',
        "Code/Lib/Coord3D.h": ("// Coord3D: generated\n// sizeof 12 (zh); class-key struct (bytes).\n"
                               "#ifndef C\n#define C\nstruct Coord3D {\n    float x, y, z;\n};\nstruct ICoord3D;\n#endif\n"),
        "Code/Unit.cpp": unit if unit is not None else (
            "// ?f@@YAXPAUCoord3D@@@Z absent-from-retail\n// see ?f@@YAXPAUCoord3D@@@ truncated (prose)\n"
            "struct Coord3D;\nstruct Coord3DBase;\nvoid g(const struct Coord3D *p);\n"
            'extern "C" void __identifier("?f@@YAXPAUCoord3D@@@Z")();\n'),
        "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n" + functions,
        "reverse/symbols.csv": "name,address,notes\n" + symbols,
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n" + data_rows,
        "reverse/deleted_rows.csv": "name,target_rva,reason\n" + deleted,
        "reverse/dup_defs_baseline.tsv": dup_defs.HEADER + dup,
        "reverse/hatch_baseline.tsv": "# hatch register\n" + hatch,
    }
    if converged is not None:
        files["reverse/data_converged.csv"] = "name\n" + converged
    files.update(extra or {})
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, encoding="utf-8", newline="")
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    subprocess.run(["git", "-C", str(tmp_path), "add", "-A"], check=True)
    monkeypatch.setattr(hal.class_contract, "export_key", lambda name: Counter({k: 15 for k in exports}))
    return tmp_path


ROW = "?f@@YAXPAUCoord3D@@@Z,,0x00001000,4,Code/Unit.cpp,matched,parent=?f@@YAXPAUCoord3D@@@Z\n"


def test_migration_plan_rewrites_every_spelling_and_nothing_else(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW,
                symbols="?f@@YAXPAVCoord3D@@@Z,0x00001000,same address as the row: dropped\n"
                        "?h@@YAXPAUICoord3D@@@Z,0x00002000,other class: kept\n",
                dup="divergent\t??$_Destroy@PAUCoord3D@@@_STL@@YAXPAUCoord3D@@0@Z\n")
    after, report = hal.plan_class_key("Coord3D", "class", root)
    header = after["Code/Lib/Coord3D.h"].decode()
    assert "class Coord3D {\npublic:\n    float x" in header and "struct ICoord3D;" in header
    assert "class-key class (exports)." in header
    contract = json.loads(after["reverse/class_contracts/Coord3D.json"])
    assert (contract["key"], contract["key_by"], contract["size"]) == ("class", "exports", 12)
    unit = after["Code/Unit.cpp"].decode()
    assert "class Coord3D;\nstruct Coord3DBase;\nvoid g(const class Coord3D *p);" in unit
    assert '__identifier("?f@@YAXPAVCoord3D@@@Z")' in unit and "// ?f@@YAXPAVCoord3D@@@Z absent" in unit
    assert "?f@@YAXPAUCoord3D@@@ truncated (prose)" in unit          # unresolvable prose is left
    assert report["prose_left"]
    ledger = after["reverse/functions.csv"].decode()
    assert "?f@@YAXPAVCoord3D@@@Z,,0x00001000" in ledger and "parent=?f@@YAXPAVCoord3D@@@Z" in ledger
    pins = after["reverse/symbols.csv"].decode()
    assert "?f@@YAXPAVCoord3D" not in pins and "?h@@YAXPAUICoord3D@@@Z" in pins
    assert "??$_Destroy@PAVCoord3D@@@_STL@@YAXPAVCoord3D@@0@Z" in after["reverse/dup_defs_baseline.tsv"].decode()
    assert set(report["mapping"]) >= {"?f@@YAXPAUCoord3D@@@Z"}


@pytest.mark.parametrize("case,want", [
    ("collision", "collision:"), ("tombstone", "tombstone:"), ("identity", "unresolvable identity"),
    ("exports", "retail's exports decide"), ("base", "base clause"), ("collision-old", "collision:"),
    ("converged", "converged names"), ("generated", "generated or vendored"),
    ("namespace-use", "cannot be resolved to the global class"), ("braces", "unbalanced braces"),
])
def test_migration_refuses_whole(tmp_path, monkeypatch, case, want):
    kw = {"functions": ROW}
    if case == "collision":      # a U pin on another address respells to the row's name
        kw["symbols"] = "?f@@YAXPAUCoord3D@@@Z,0x00003000,a habit spelling on a shared body\n"
        kw["functions"] = ROW.replace("PAUCoord3D", "PAVCoord3D").replace("parent=?f@@YAXPAVCoord3D@@@Z", "")
    elif case == "tombstone":
        kw["deleted"] = "?f@@YAXPAVCoord3D@@@Z,0x00001000,misnamed\n"
    elif case == "identity":
        kw["functions"] = ROW + "?f@?1??g@@YAXXZ@YAXPAUCoord3D@@PAU1@@Z,,0x00001010,4,Code/Unit.cpp,matched,\n"
    elif case == "hatch":
        kw["hatch"] = "alternatename\tCode/Unit.cpp\t?f@@YAXPAUCoord3D@@@Z\t1\n"
    elif case == "exports":
        kw["exports"] = ("class", "struct")
    elif case == "base":
        kw["unit"] = "struct Coord3D : A, B {\n};\n"
    elif case == "collision-old":   # the old spelling already names two addresses: still refused
        kw["symbols"] = "?f@@YAXPAUCoord3D@@@Z,0x00003000,a pin on another body\n"
    elif case == "converged":
        kw["converged"] = "?g_c@@3UCoord3D@@A\n"
    elif case == "generated":
        kw["extra"] = {"Code/gen_asm/f.asm": "; Coord3D\n EXTERN ?f@@YAXPAUCoord3D@@@Z:PROC\n"}
    elif case == "namespace-use":
        kw["unit"] = "namespace N { void f(const struct Coord3D *p); }\n"
    elif case == "braces":
        kw["unit"] = "struct Coord3D;\n#if 0\nnamespace N {\n#endif\nvoid f() {}\n"
    root = tree(tmp_path, monkeypatch, **kw)
    snapshot = {p: p.read_bytes() for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    with pytest.raises(hal.RekeyRefused, match=want):
        hal.plan_class_key("Coord3D", "class", root)
    assert snapshot == {p: p.read_bytes() for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def test_migration_is_not_repeated(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    after, _ = hal.plan_class_key("Coord3D", "class", root)
    for rel, data in after.items():
        (root / rel).write_bytes(data)
    with pytest.raises(hal.RekeyRefused, match="already says class"):
        hal.plan_class_key("Coord3D", "class", root)


def test_dup_defs_rekey_keeps_the_total_and_never_merges():
    text = dup_defs.HEADER + "divergent\tA\ndivergent\tB\n"
    assert dup_defs.rekey_baseline_text(text, {"A": "C"}) == dup_defs.HEADER + "divergent\tC\ndivergent\tB\n"
    with pytest.raises(ValueError):
        dup_defs.rekey_baseline_text(text, {"A": "B"})


def test_apply_restores_every_file_when_a_write_fails(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    monkeypatch.setattr(hal, "ROOT", root)
    monkeypatch.setenv("BFME_CLAIMS", "off")
    snapshot = {p: p.read_bytes() for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    real, calls = hal.Path.write_bytes, []

    def failing(self, data):
        calls.append(self)
        if len(calls) == 3:
            raise OSError("disk full")
        return real(self, data)
    monkeypatch.setattr(hal.Path, "write_bytes", failing)
    with pytest.raises(OSError):
        hal.apply_class_key("Coord3D", "class")
    monkeypatch.setattr(hal.Path, "write_bytes", real)
    now = {p: p.read_bytes() for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    assert now == snapshot


def test_apply_refuses_without_the_claims(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    monkeypatch.setattr(hal, "ROOT", root)
    monkeypatch.setenv("BFME_CLAIMS", "on")
    import claims
    monkeypatch.setattr(claims, "owner", lambda root=None: "me")
    monkeypatch.setattr(claims, "active", lambda root=None: {})      # unreachable origin: fail closed
    with pytest.raises(hal.RekeyRefused, match="not held"):
        hal.apply_class_key("Coord3D", "class")



def test_migration_carries_name_basis_records_instead_of_editing_them(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    basis = "kind,old,new,basis,evidence,source,rva\n" \
            "function,?rva1000@@YAXPAUCoord3D@@@Z,?f@@YAXPAUCoord3D@@@Z,canonical:wb,cited,Code/Unit.cpp,0x00001000\n"
    (root / "reverse/name_basis.csv").write_text(basis, encoding="utf-8", newline="")
    after, _ = hal.plan_class_key("Coord3D", "class", root)
    text = after["reverse/name_basis.csv"].decode()
    assert text.startswith(basis)                                    # history untouched, appended only
    assert text[len(basis):].startswith("carry,?f@@YAXPAUCoord3D@@@Z,?f@@YAXPAVCoord3D@@@Z,canonical:wb,")



def test_migration_hands_hatch_tokens_to_hatch_counters(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW, hatch="alternatename\tCode/Unit.cpp\t?f@@YAXPAUCoord3D@@@Z\t1\n")
    after, report = hal.plan_class_key("Coord3D", "class", root)
    assert report["hatch_tokens"] == ["?f@@YAXPAUCoord3D@@@Z"]
    assert "reverse/hatch_baseline.tsv" not in after                 # hatch_counters --update writes it



def test_declaration_scope_is_resolved(tmp_path, monkeypatch):
    unit = ("namespace Other { struct Coord3D { int x; }; }\n"
            "struct Coord3D;\n"
            "void f(const struct Coord3D *p);\n")
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    after, report = hal.plan_class_key("Coord3D", "class", root)
    text = after["Code/Unit.cpp"].decode()
    assert "namespace Other { struct Coord3D { int x; }; }" in text        # another class: untouched
    assert "\nclass Coord3D;\n" in text and "const class Coord3D *p" in text
    assert report["other_scope_declarations"] == ["Code/Unit.cpp: struct Coord3D inside namespace (another class; left)"]


def test_use_beside_another_scope_declaration_refuses(tmp_path, monkeypatch):
    unit = "class Outer { struct Coord3D; void g(struct Coord3D *p); };\n"
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    with pytest.raises(hal.RekeyRefused, match="file declares another Coord3D"):
        hal.plan_class_key("Coord3D", "class", root)


def _snapshot(root):
    return {p: p.read_bytes() for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def test_dry_run_writes_nothing_but_its_report(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    monkeypatch.setattr(hal, "ROOT", root)
    before = _snapshot(root)
    assert hal.apply_class_key("Coord3D", "class", dry_run=True, report=str(root / "build/rekey.json")) == 0
    now = _snapshot(root)
    assert set(now) - set(before) == {root / "build/rekey.json"}
    assert all(now[p] == before[p] for p in before)
    assert json.loads((root / "build/rekey.json").read_text())["key"] == "class"


@pytest.mark.parametrize("where", ["tracked", "outside-build"])
def test_report_never_overwrites_a_repository_input(tmp_path, monkeypatch, where):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    monkeypatch.setattr(hal, "ROOT", root)
    target = root / ("reverse/functions.csv" if where == "tracked" else "notes.json")
    before = _snapshot(root)
    with pytest.raises(hal.RekeyRefused, match="--report"):
        hal.apply_class_key("Coord3D", "class", dry_run=True, report=str(target))
    assert _snapshot(root) == before


def test_claims_cover_the_hatch_register_it_writes(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW, hatch="alternatename\tCode/Unit.cpp\t?f@@YAXPAUCoord3D@@@Z\t1\n")
    monkeypatch.setattr(hal, "ROOT", root)
    monkeypatch.setenv("BFME_CLAIMS", "on")
    import claims
    after, _ = hal.plan_class_key("Coord3D", "class", root)
    held = {claims.file_key(r): {"owner": "me"} for r in after}
    held[claims.class_key("Coord3D")] = {"owner": "me"}
    monkeypatch.setattr(claims, "owner", lambda root=None: "me")
    monkeypatch.setattr(claims, "active", lambda root=None: held)
    before = _snapshot(root)
    with pytest.raises(hal.RekeyRefused, match="file:reverse/hatch_baseline.tsv"):
        hal.apply_class_key("Coord3D", "class")
    assert _snapshot(root) == before


def test_a_refused_hatch_update_restores_every_file(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW, hatch="alternatename\tCode/Unit.cpp\t?f@@YAXPAUCoord3D@@@Z\t1\n")
    monkeypatch.setattr(hal, "ROOT", root)
    monkeypatch.setenv("BFME_CLAIMS", "off")
    import hatch_counters

    def refuse():
        (root / "reverse/hatch_baseline.tsv").write_text("half-written\n")
        raise SystemExit("hatch_counters: 1 occurrence key(s) grew")
    monkeypatch.setattr(hatch_counters, "update", refuse)
    before = _snapshot(root)
    with pytest.raises(SystemExit):
        hal.apply_class_key("Coord3D", "class")
    assert _snapshot(root) == before
    assert not list((root / "build/rename-journal").glob("*.json"))



def test_old_key_scan_reads_symbols_and_directives_and_fails_closed(tmp_path):
    clean, stale, directive = tmp_path / "a.obj", tmp_path / "b.obj", tmp_path / "c.obj"
    clean.write_bytes(b"\0?f@@YAXPAVCoord3D@@@Z\0?g@@YAXPAUICoord3D@@@Z\0")
    stale.write_bytes(b"\0?f@@YAXPAUCoord3D@@@Z\0")
    directive.write_bytes(b' /alternatename:?h@@YAXPAUCoord3D@@@Z=?k@@YAXXZ ')
    found = hal.scan_old_key("Coord3D", "class", [clean, stale, directive, tmp_path / "missing.obj"])
    assert set(found) == {str(stale), str(directive), str(tmp_path / "missing.obj")}
    assert found[str(stale)] == ["?f@@YAXPAUCoord3D@@@Z"]



@pytest.mark.parametrize("unit,why", [
    ("#if N\nnamespace Other {\n#endif\nstruct Coord3D {};\n#if N\n}\n#endif\n", "conditional branch"),
    ("#define BEGIN namespace Other {\n#define END }\nBEGIN struct Coord3D {}; END\n", "macro BEGIN"),
    ("#define DECLARE struct Coord3D;\nDECLARE\n", "preprocessor directive"),
])
def test_scope_changing_preprocessing_refuses(tmp_path, monkeypatch, unit, why):
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    with pytest.raises(hal.RekeyRefused, match=why):
        hal.plan_class_key("Coord3D", "class", root)


def test_an_include_guard_around_a_global_declaration_still_passes(tmp_path, monkeypatch):
    unit = "#ifndef UNIT_H\n#define UNIT_H\n#ifdef _MSC_VER\n#pragma once\n#endif\nstruct Coord3D;\n#endif\n"
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    after, _ = hal.plan_class_key("Coord3D", "class", root)
    assert "\nclass Coord3D;\n" in after["Code/Unit.cpp"].decode()


@pytest.mark.parametrize("where", ["symlink", "tracked-under-build"])
def test_report_path_resolves_links_and_tracked_build_files(tmp_path, monkeypatch, where):
    root = tree(tmp_path, monkeypatch, functions=ROW)
    monkeypatch.setattr(hal, "ROOT", root)
    (root / "build").mkdir(exist_ok=True)
    target = root / "build" / "report.json"
    if where == "symlink":
        target.symlink_to(root / "reverse" / "functions.csv")
    else:
        target.write_text("tracked\n")
        subprocess.run(["git", "-C", str(root), "add", "-f", "build/report.json"], check=True)
    before = _snapshot(root)
    with pytest.raises(hal.RekeyRefused, match="--report"):
        hal.apply_class_key("Coord3D", "class", dry_run=True, report=str(target))
    assert _snapshot(root) == before



def test_present_unmatched_register_tokens_are_read_with_their_question_mark(tmp_path, monkeypatch):
    root = tree(tmp_path, monkeypatch, functions=ROW,
                hatch="present_unmatched\tCode/Unit.cpp\tf@@YAXPAUCoord3D@@@Z\t1\n"
                      "present_unmatched\tCode/Unit.cpp\tg@@YAXPAUICoord3D@@@Z\t1\n")
    _, report = hal.plan_class_key("Coord3D", "class", root)
    assert report["hatch_tokens"] == ["f@@YAXPAUCoord3D@@@Z"]



def test_a_balanced_class_defining_macro_before_a_global_declaration_passes(tmp_path, monkeypatch):
    unit = ("#define BFME_DISP8_BYTE_SETTER(NAME, METHOD, DISP, IMM) \\\n"
            "\tclass NAME \\\n\t{ \\\n\tpublic: \\\n\t\tvoid METHOD(); \\\n\t\tchar m_lead[DISP]; \\\n"
            "\t\tunsigned char m_flag; \\\n\t}; \\\n\tvoid NAME::METHOD() { m_flag = IMM; }\n"
            "BFME_DISP8_BYTE_SETTER(Rva1, set, 4, 1)\n"
            "struct Coord3D;\n")
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    after, _ = hal.plan_class_key("Coord3D", "class", root)
    assert "\nclass Coord3D;\n" in after["Code/Unit.cpp"].decode()


def test_a_block_opened_after_an_unclassified_identifier_is_not_file_scope(tmp_path, monkeypatch):
    unit = "#define OPEN namespace Other\nOPEN { struct Coord3D {}; }\nstruct Coord3D;\n"
    root = tree(tmp_path, monkeypatch, functions=ROW, unit=unit)
    after, report = hal.plan_class_key("Coord3D", "class", root)
    text = after["Code/Unit.cpp"].decode()
    assert "OPEN { struct Coord3D {}; }" in text and "\nclass Coord3D;\n" in text
    assert report["other_scope_declarations"] == ["Code/Unit.cpp: struct Coord3D inside unknown (another class; left)"]
    root2 = tree(tmp_path / "use", monkeypatch, functions=ROW,
                 unit="#define OPEN namespace Other\nOPEN { void f(const struct Coord3D *p); }\n")
    with pytest.raises(hal.RekeyRefused, match="unclassified block"):
        hal.plan_class_key("Coord3D", "class", root2)


# LINK-018 rekey defect (the members trial's F build, 2026-11-11): units that compile Coord3D from a donor
# header, and so keep the old key after the flip, were not found when their own text named no Coord3D or
# reached the donor only through other headers. These three are the trial's own failures.
DONOR = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
DONOR_CASES = [
    # W3DRopeDraw.cpp: a directory-qualified donor include, no Coord3D in the unit's text
    ('#include "Common/Thing.h"', "GameEngine/Include/Common/Thing.h", "?getPosition@Drawable@@QBEPBUCoord3D@@XZ"),
    # W3DRadar.cpp: donor headers that reach Lib/BaseType.h only through another header
    ('#include "GameClient/Color.h"', "GameEngine/Include/GameClient/Color.h",
     "?worldToRadar@Radar@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z"),
    ('#include <Common/Geometry.h>', "GameEngine/Include/Common/Geometry.h",
     "?CollidesWith@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z"),
]


def donor_tree(tmp_path, monkeypatch, include, via, name, basetype="struct Coord3D\n{\n    float x, y, z;\n};\n"):
    callee = f"{name},,0x00002000,8,Code/Callee.cpp,matched,\n"
    return tree(tmp_path, monkeypatch, functions=ROW + callee, extra={
        f"{DONOR}/{via}": '#include "Lib/BaseType.h"\n',
        f"{DONOR}/Libraries/Include/Lib/BaseType.h": basetype,
        "Code/Callee.cpp": '#include "Lib/Coord3D.h"\nstruct Coord3D;\n',
        "Code/Caller.cpp": (f"// cl: /MD /I{DONOR}/GameEngine/Include /I {DONOR}/Libraries/Include\n"
                            f"{include}\nvoid caller();\n"),
    })


@pytest.mark.parametrize("include,via,name", DONOR_CASES)
def test_a_unit_compiling_a_donor_class_is_refused(tmp_path, monkeypatch, include, via, name):
    root = donor_tree(tmp_path, monkeypatch, include, via, name)
    with pytest.raises(hal.RekeyRefused, match=r"donor Coord3D: Code/Caller\.cpp compiles Coord3D from "
                                               + re.escape(f"{DONOR}/Libraries/Include/Lib/BaseType.h")):
        hal.plan_class_key("Coord3D", "class", root)


def test_a_donor_unit_whose_object_spells_no_old_key_is_reported_not_refused(tmp_path, monkeypatch):
    include, via, name = DONOR_CASES[0]
    root = donor_tree(tmp_path, monkeypatch, include, via, name)
    monkeypatch.setattr(hal, "_rekey_unit_object", lambda root, rel, name, key: [])
    after, report = hal.plan_class_key("Coord3D", "class", root)
    assert report["donor_header_units"] == ["Code/Caller.cpp"]
    assert name.replace("UCoord3D", "VCoord3D") in after["reverse/functions.csv"].decode()


def test_a_donor_unit_whose_object_spells_the_old_key_is_refused(tmp_path, monkeypatch):
    include, via, name = DONOR_CASES[0]
    root = donor_tree(tmp_path, monkeypatch, include, via, name)
    monkeypatch.setattr(hal, "_rekey_unit_object", lambda root, rel, name, key: [name])
    with pytest.raises(hal.RekeyRefused, match=r"its object spells the old key \(1 name"):
        hal.plan_class_key("Coord3D", "class", root)


@pytest.mark.parametrize("basetype", ["struct Coord3D;\n", "struct Coord2D { float x, y; };\n"])
def test_a_donor_header_without_the_class_definition_is_ignored(tmp_path, monkeypatch, basetype):
    include, via, name = DONOR_CASES[0]
    root = donor_tree(tmp_path, monkeypatch, include, via, name, basetype=basetype)
    after, report = hal.plan_class_key("Coord3D", "class", root)
    assert report["donor_header_units"] == []
