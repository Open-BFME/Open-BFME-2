"""Generated vtable bridges: ownership, refusal boundaries, and COFF selection."""
import json
import struct
from pathlib import Path

import pytest

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_cycle as L
import vtable_bridge as V


class Retail:
    base = 0x400000

    def __init__(self, values=(0x1000, 0x1010)):
        self.raw = b"".join(struct.pack("<I", self.base + value) for value in values)

    def read(self, rva, size):
        offset = rva - 0x3000
        return self.raw[offset:offset + size] if 0 <= offset < len(self.raw) else None

    def in_text(self, value):
        return self.base + 0x1000 <= value < self.base + 0x2000


def code_object(path, storage=L.EXTERNAL, flags=0x60500020):
    return L.write_coff(path, [(".text", flags, b"\xc3" * 33, 0)],
                        [("_first", 1, 0, storage), ("_second", 1, 16, L.EXTERNAL)])


def table_object(path, slots=("_first",), name="_vtable", selection=2, prefix=0,
                 other_public=False, reloc_kind=L.DIR32):
    symbols = [(name, 1, prefix, L.EXTERNAL)]
    if other_public:
        symbols.append(("_other_public", 1, prefix, L.EXTERNAL))
    symbols += [(target, 0, 0, L.EXTERNAL) for target in sorted(set(slots))]
    return L.write_coff(path, [(".rdata", 0x40300040 | (V.COMDAT if selection else 0),
                                bytes(prefix + 4 * len(slots)), selection)], symbols,
                        {1: [(prefix + 4 * index, target, reloc_kind)
                             for index, target in enumerate(slots)]})


def inputs(tmp_path, slots=("_first",), **kw):
    code = code_object(tmp_path / "code.obj")
    table = table_object(tmp_path / "table.obj", slots, **kw)
    rows = [
        {"target_rva": "0x1000", "name": "_first", "source": "Code/code.cpp", "status": "matched"},
        {"target_rva": "0x1010", "name": "_second", "source": "Code/code.cpp", "status": "matched"}]
    data = [{"address": "0x3000", "size": "8", "name": "_vtable", "kind": "vtable"}]
    return code, table, rows, data


def plan(code, tables, rows, data, omitted=(), retail=None, object_for=None, archives=(), source_of=None):
    return V.plan(rows, tables + [code], omitted, retail or Retail(), data,
                  archives=archives, object_for=object_for or (lambda row: code),
                  symbol_for=lambda row: row["name"], source_of=source_of)


def test_short_select_any_copy_gets_complete_kept_targets(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    result = plan(code, [table], rows, data)
    assert (result["tables"], result["slots"], result["refused_tables"]) == (1, 2, 0)
    entry = result["entries"][0]
    assert entry["name"] == "_vtable"
    assert [slot["name"] for slot in entry["slots"]] == ["_first", "_second"]
    assert entry["previous_extent"] == 4


def test_correct_first_copy_retires_bridge_even_if_later_copy_short(tmp_path):
    code, short, rows, data = inputs(tmp_path)
    full = table_object(tmp_path / "full.obj", ("_first", "_second"))
    result = plan(code, [full, short], rows, data)
    assert result["tables"] == result["slots"] == 0
    assert result["already_correct"] == 1
    assert result["refused_tables"] == 0
    assert plan(code, [short, full], rows, data)["tables"] == 1


def test_wrong_same_size_copy_is_bridged(tmp_path):
    code, table, rows, data = inputs(tmp_path, ("_second", "_first"))
    assert plan(code, [table], rows, data)["slots"] == 2


@pytest.mark.parametrize("strong_first", [False, True])
def test_any_strong_copy_refuses_bridge_in_both_orders(tmp_path, strong_first):
    code, table, rows, data = inputs(tmp_path)
    strong = table_object(tmp_path / "strong.obj", ("_first", "_second"), selection=0)
    copies = [strong, table] if strong_first else [table, strong]
    result = plan(code, copies, rows, data)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "strong-definition"


@pytest.mark.parametrize("strong_names", [("_other",), ("_other", "_third")])
def test_strong_name_is_refused_alone_and_its_comdat_neighbour_is_bridged(tmp_path, strong_names):
    """A strong definition keeps its own symbol; the COMDAT names bound at the
    same retail address are other symbols and still get the complete copy."""
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = ";".join(strong_names)
    strong = [table_object(tmp_path / f"{name[1:]}.obj", name=name, selection=0) for name in strong_names]
    result = plan(code, [table] + strong, rows, data,
                  source_of={path: f"Code/{path.stem}.cpp" for path in [table] + strong})
    assert [(entry["name"], entry["reason"], entry["source"], entry["providers"])
            for entry in result["refusals"]] == [
        (name, "strong-definition", f"Code/{name[1:]}.cpp", [str(path)])
        for name, path in zip(strong_names, strong)]
    assert all(entry["names"] == [entry["name"]] for entry in result["refusals"])
    assert [(entry["name"], entry["names"], [slot["name"] for slot in entry["slots"]])
            for entry in result["entries"]] == [("_vtable", ["_vtable"], ["_first", "_second"])]
    assert (result["tables"], result["retail_tables"], result["refused_tables"]) == (1, 1, len(strong_names))
    path = V.write_object(result["entries"], tmp_path / "bridge.obj")
    _sections, symbols = L.parse_coff(path.read_bytes())
    assert {sym.name for sym in symbols.values() if sym.sec > 0 and sym.cls == L.EXTERNAL} == {"_vtable"}
    V.write_queue(result, tmp_path / "queue.tsv")
    queued = [line.split("\t")[:5] for line in (tmp_path / "queue.tsv").read_text().splitlines()[1:]]
    assert queued == [["refused", name, "", "strong-definition", f"Code/{name[1:]}.cpp"]
                      for name in strong_names] + [["bridged", "_vtable", "", "bridge-retirement", "Code/table.cpp"]]


def test_strong_ledger_primary_name_does_not_label_its_bridged_neighbour(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0].update(name="_other", names="_vtable")
    strong = table_object(tmp_path / "other.obj", name="_other", selection=0)
    result = plan(code, [table, strong], rows, data)
    assert [(entry["name"], entry["reason"]) for entry in result["refusals"]] == [
        ("_other", "strong-definition")]
    assert [entry["name"] for entry in result["entries"]] == ["_vtable"]
    # A refusal of the remaining names is filed under one of them, not under the strong name.
    result = plan(code, [table, strong], rows[:1], data)
    assert [(entry["name"], entry["names"], entry["reason"]) for entry in result["refusals"]] == [
        ("_other", ["_other"], "strong-definition"), ("_vtable", ["_vtable"], "unrowed-target")]


def test_strong_only_address_is_refused_once(tmp_path):
    code, _table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_stale_unbound_name"
    strong = table_object(tmp_path / "strong.obj", ("_first", "_second"), selection=0)
    result = plan(code, [strong], rows, data)
    assert result["refusal_reasons"] == {"strong-definition": 1}
    assert result["tables"] == 0


def strong_neighbour(tmp_path, data, name="_other", **kw):
    data[0]["names"] = ";".join(filter(None, [data[0].get("names"), name]))
    return table_object(tmp_path / "strong.obj", name=name, selection=0, **kw)


@pytest.mark.parametrize("selection", [1, 3, 4, 5, 6])
def test_strong_neighbour_does_not_admit_an_unsupported_selection(tmp_path, selection):
    code, table, rows, data = inputs(tmp_path, selection=selection)
    result = plan(code, [table, strong_neighbour(tmp_path, data)], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "unsupported-selection": 1}


def test_strong_neighbour_does_not_admit_a_section_shared_with_it(tmp_path):
    # _vtable's COMDAT section also defines _other_public, which has a strong
    # definition elsewhere: the shared section is still never guessed.
    code, table, rows, data = inputs(tmp_path, other_public=True)
    result = plan(code, [table, strong_neighbour(tmp_path, data, "_other_public")], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "shared-or-prefixed-comdat": 1}


def test_strong_neighbour_does_not_admit_a_prefixed_copy(tmp_path):
    code, table, rows, data = inputs(tmp_path, prefix=4)
    result = plan(code, [table, strong_neighbour(tmp_path, data)], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "shared-or-prefixed-comdat": 1}


def test_strong_neighbour_does_not_admit_a_name_bound_elsewhere(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    strong = strong_neighbour(tmp_path, data)
    data.append({**data[0], "address": "0x3004", "names": ""})
    result = plan(code, [table, strong], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "ambiguous-table-name": 2}


def test_strong_neighbour_does_not_admit_a_common_or_absolute_copy(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    strong = strong_neighbour(tmp_path, data)
    common = L.write_coff(tmp_path / "common.obj", [], [("_vtable", 0, 8, L.EXTERNAL)])
    result = plan(code, [table, strong, common], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "common-definition": 1}
    absolute = L.write_coff(tmp_path / "absolute.obj", [], [("_vtable", -1, 8, L.EXTERNAL)])
    result = plan(code, [table, strong, absolute], rows, data)
    assert result["tables"] == 0
    assert sorted((entry["name"], entry["reason"]) for entry in result["refusals"]) == [
        ("_other", "strong-definition"), ("_vtable", "strong-definition")]


def test_strong_neighbour_does_not_admit_an_unresolved_slot(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    result = plan(code, [table, strong_neighbour(tmp_path, data)], rows[:1], data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "unrowed-target": 1}


def test_strong_neighbour_does_not_admit_a_synthesized_definition(tmp_path):
    # _used is referenced but nothing defines it; the strong copy at the same
    # address is not a kept COMDAT copy, so no definition is invented.
    code, _table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_used"
    strong = strong_neighbour(tmp_path, data, slots=("_first", "_second"))
    consumer = L.write_coff(tmp_path / "consumer.obj", [], [("_used", 0, 0, L.EXTERNAL)])
    result = plan(code, [strong, consumer], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"strong-definition": 1, "no-kept-definition": 1}


def test_possible_strong_archive_neighbour_is_refused_alone(tmp_path, monkeypatch):
    code, table, rows, data = inputs(tmp_path)
    strong = strong_neighbour(tmp_path, data)
    monkeypatch.setattr(V.coffar, "read_archive", lambda path: [("member.obj", strong.read_bytes())])
    result = plan(code, [table], rows, data, archives=[tmp_path / "runtime.lib"])
    assert [(entry["name"], entry["reason"]) for entry in result["refusals"]] == [
        ("_other", "strong-definition")]
    assert [entry["name"] for entry in result["entries"]] == ["_vtable"]


def test_possible_strong_archive_definition_refuses(tmp_path, monkeypatch):
    code, table, rows, data = inputs(tmp_path)
    strong = table_object(tmp_path / "strong.obj", selection=0)
    monkeypatch.setattr(V.coffar, "read_archive", lambda path: [("member.obj", strong.read_bytes())])
    result = plan(code, [table], rows, data, archives=[tmp_path / "runtime.lib"])
    assert result["refusals"][0]["reason"] == "strong-definition"


def test_missing_vtable_definition_is_never_synthesized(tmp_path):
    code, _table, rows, data = inputs(tmp_path)
    result = plan(code, [], rows, data)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "no-kept-definition"


def test_unrowed_slot_refuses_entire_table(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    result = plan(code, [table], rows[:1], data)
    assert result["tables"] == result["slots"] == 0
    assert result["refusals"][0]["blocked"] == [
        {"slot": 1, "target_rva": 0x1010, "reason": "unrowed-target"}]


def test_omitted_slot_refuses_even_if_a_kept_row_shares_address(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    omitted = tmp_path / "uw_gen_000.obj"
    rows.append({"target_rva": "0x1010", "name": "_second",
                 "source": "Code/gen_small/uw_gen_000.cpp", "status": "matched"})
    result = plan(code, [table], rows, data, omitted=[omitted],
                  object_for=lambda row: omitted if "uw_gen" in row["source"] else code)
    assert result["refusals"][0]["reason"] == "omitted-target"
    assert result["tables"] == 0


def test_target_in_non_kept_object_refuses(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    result = plan(code, [table], rows, data,
                  object_for=lambda row: tmp_path / "not-kept.obj")
    assert result["refusals"][0]["reason"] == "target-not-kept"


def test_local_target_name_cannot_be_referenced_from_bridge(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    code_object(code, storage=L.STATIC)
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "target-not-external"


def test_target_definition_must_be_executable(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    code_object(code, flags=0x40300040)
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "target-not-code"


def test_one_external_name_cannot_choose_between_retail_addresses(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    rows.append({"target_rva": "0x1100", "name": "_first", "source": "Code/code.cpp", "status": "matched"})
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "ambiguous-target-name"


@pytest.mark.parametrize("selection", [1, 3, 4, 5, 6])
def test_only_select_any_existing_copies_are_supported(tmp_path, selection):
    code, table, rows, data = inputs(tmp_path, selection=selection)
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "unsupported-selection"


@pytest.mark.parametrize("kw", [{"prefix": 4}, {"other_public": True}])
def test_prefix_or_shared_section_is_not_guessed(tmp_path, kw):
    code, table, rows, data = inputs(tmp_path, **kw)
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "shared-or-prefixed-comdat"


def test_multiple_names_at_one_retail_address_each_get_full_counted_copy(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_other"
    other = table_object(tmp_path / "other.obj", name="_other")
    result = plan(code, [table, other], rows, data)
    assert (result["tables"], result["slots"], result["retail_tables"]) == (2, 4, 1)
    assert {entry["name"] for entry in result["entries"]} == {"_vtable", "_other"}
    path = V.write_object(result["entries"], tmp_path / "bridge.obj")
    sections, symbols = L.parse_coff(path.read_bytes())
    assert len(sections) == 2 and all(section.size == 8 for section in sections)
    assert {sym.name for sym in symbols.values() if sym.sec > 0 and sym.cls == L.EXTERNAL} == {"_vtable", "_other"}


def test_one_vtable_name_cannot_pick_between_retail_rows(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data.append({**data[0], "address": "0x3004"})
    result = plan(code, [table], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"]["ambiguous-table-name"] == 2


def test_retail_slots_are_bounded_by_row_extent(tmp_path):
    code, table, rows, data = inputs(tmp_path, ("_second",))
    data[0]["size"] = "4"
    result = plan(code, [table], rows, data)
    assert result["slots"] == 1


def test_unknown_retail_extent_refuses(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["size"] = "0"
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "unbounded-retail-row"


def test_emitted_comdats_are_independent_select_any_with_real_target_relocations(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    entries = plan(code, [table], rows, data)["entries"]
    entries.append({**entries[0], "name": "_second_vtable"})
    path = V.write_object(entries, tmp_path / "retail_vtables.obj")
    sections, symbols = L.parse_coff(path.read_bytes())
    assert len(sections) == 2 and all(sec.sel == 2 and sec.flags == V.RDATA for sec in sections)
    defined = {sym.name for sym in symbols.values() if sym.cls == L.EXTERNAL and sym.sec > 0}
    assert defined == {"_vtable", "_second_vtable"}
    for sec in sections:
        assert sec.size == 8
        assert [(off, symbols[index].name, kind) for off, index, kind in sec.relocs] == [
            (0, "_first", L.DIR32), (4, "_second", L.DIR32)]


def test_build_bridge_writes_counted_plan_and_refusal_queue(tmp_path, monkeypatch, capsys):
    code, table, rows, data = inputs(tmp_path)
    data.append({"address": "0x3004", "size": "4", "name": "_missing", "kind": "vtable"})
    monkeypatch.setattr(V.build, "row_object", lambda row: code)
    monkeypatch.setattr(V.build, "ledger_object_symbol", lambda row: row["name"])
    path, metadata = V.build_bridge(rows, [table, code], [], [], tmp_path, Retail(), tables=data)
    # CI logs lost every later line after one unbounded binding dump: print counts only.
    printed = capsys.readouterr().out.splitlines()
    assert [line.split(":")[0] for line in printed] == ["vtable_name_discovery", "vtable_bridge"]
    assert json.loads(printed[1].split(": ", 1)[1])["tables"] == 1
    assert "new_name_bindings" in json.loads(printed[0].split(": ", 1)[1])
    assert path.name == "retail_vtables.obj"
    assert (metadata["tables"], metadata["slots"], metadata["refused_tables"]) == (1, 2, 1)
    disk = json.loads((tmp_path / "vtable_bridge.json").read_text())
    assert disk["tables"] == 1 and disk["slots"] == 2
    assert "no-kept-definition" in (tmp_path / "vtable_bridge_queue.tsv").read_text()
    path, empty = V.build_bridge(rows, [code], [], [], tmp_path, Retail(), tables=data)
    assert path is None and empty["tables"] == 0
    assert not (tmp_path / "retail_vtables.obj").exists()


def write_ledger(root, rows):
    import csv
    (root / "reverse").mkdir(exist_ok=True)
    fields = ["address", "size", "section", "kind", "name", "source", "status", "names", "defs", "refs"]
    with (root / "reverse/data_ledger.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fields, lineterminator="\n")
        writer.writeheader()
        writer.writerows({"section": ".rdata", "size": "8", **row} for row in rows)


def test_ledger_tables_are_vtable_rows_and_global_owner_rows_binding_a_vftable_name(tmp_path):
    write_ledger(tmp_path, [
        {"address": "0x3000", "kind": "vtable", "name": "??_7A@@6B@"},
        # a verified data_rows owner (a hand-built strong array) is the canonical name here
        {"address": "0x3010", "kind": "global", "name": "_vtbl_00C03010", "names": "??_7B@@6B@;_vtbl_00C03010"},
        {"address": "0x3020", "kind": "global", "name": "?g_plain@@3HA", "names": "?g_plain@@3HA;?g_other@@3HA"},
        {"address": "0x3030", "kind": "string", "name": "??_C@_03X@abc?$AA@", "names": "??_7C@@6B@;??_C@_03X@abc?$AA@"},
        {"address": "0x3040", "kind": "global", "name": "?g_vbtable@@3HA", "names": "??_8D@@7B@;?g_vbtable@@3HA"},
        {"address": "0x3050", "kind": "rtti", "name": "??_R4E@@6B@", "names": "??_7E@@6B@;??_R4E@@6B@"}])
    assert [row["address"] for row in V.table_rows(tmp_path)] == ["0x3000", "0x3010"]


def test_virtual_base_tables_are_not_function_tables_but_mixed_and_legacy_rows_are(tmp_path):
    write_ledger(tmp_path, [
        {"address": "0x3000", "kind": "vtable", "name": "??_8A@@7B@"},
        {"address": "0x3010", "kind": "vtable", "name": "??_8B@@7B@", "names": "??_8B@@7B@;??_8C@@7BB@@@"},
        {"address": "0x3020", "kind": "vtable", "name": "??_8D@@7B@", "names": "??_7D@@6B@;??_8D@@7B@"},
        {"address": "0x3030", "kind": "vtable", "name": "_vtbl_00C03030"},
        {"address": "0x3040", "kind": "vtable", "name": "??_8E@@7B@", "names": "??_8E@@7B@;_vtbl_00C03040"},
        {"address": "0x3050", "kind": "global", "name": "_vbtbl_00C03050", "names": "??_7F@@6B@;??_8F@@7B@;_vbtbl_00C03050"}])
    assert [row["address"] for row in V.table_rows(tmp_path)] == ["0x3020", "0x3030", "0x3040", "0x3050"]


def test_virtual_base_table_is_not_refused_and_its_strong_neighbour_still_is(tmp_path, monkeypatch):
    code, _table, rows, _data = inputs(tmp_path)
    vbtable = L.write_coff(tmp_path / "vbase.obj", [(".rdata", 0x40300040 | V.COMDAT,
                                                     struct.pack("<ii", 0, 36), 2)],
                           [("??_8D@@7B@", 1, 0, L.EXTERNAL)])
    strong = table_object(tmp_path / "owner.obj", ("_first", "_second"), name="_vtbl_00C03000", selection=0)
    write_ledger(tmp_path, [
        {"address": "0x3000", "kind": "global", "name": "_vtbl_00C03000", "names": "??_7T@@6B@;_vtbl_00C03000"},
        {"address": "0x3008", "kind": "vtable", "name": "??_8D@@7B@"}])
    retail = Retail()
    retail.raw += struct.pack("<ii", 0, 36)
    assert V.retail_slots(retail, {"address": "0x3008", "size": "8"}) == (None, "no-retail-slots")
    monkeypatch.setattr(V.build, "ROOT", tmp_path)
    monkeypatch.setattr(V.build, "row_object", lambda row: code)
    monkeypatch.setattr(V.build, "ledger_object_symbol", lambda row: row["name"])
    (tmp_path / "out").mkdir()
    _path, metadata = V.build_bridge(rows, [vbtable, strong, code], [], [], tmp_path / "out", retail)
    assert [(entry["name"], entry["reason"]) for entry in metadata["refusals"]] == [
        ("_vtbl_00C03000", "strong-definition")]
    assert "??_8D@@7B@" not in (tmp_path / "out" / "vtable_bridge_queue.tsv").read_text()


def test_global_owner_row_bridges_its_comdat_vftable_and_refuses_the_strong_owner(tmp_path, monkeypatch):
    code, _table, rows, _data = inputs(tmp_path)
    table = table_object(tmp_path / "class.obj", name="??_7T@@6B@")
    strong = table_object(tmp_path / "owner.obj", ("_first", "_second"), name="_vtbl_00C03000", selection=0)
    write_ledger(tmp_path, [{"address": "0x3000", "kind": "global", "name": "_vtbl_00C03000",
                             "names": "??_7T@@6B@;_vtbl_00C03000"}])
    monkeypatch.setattr(V.build, "ROOT", tmp_path)
    monkeypatch.setattr(V.build, "row_object", lambda row: code)
    monkeypatch.setattr(V.build, "ledger_object_symbol", lambda row: row["name"])
    (tmp_path / "out").mkdir()
    path, metadata = V.build_bridge(rows, [table, strong, code], [], [], tmp_path / "out", Retail())
    assert [(entry["name"], len(entry["slots"])) for entry in metadata["entries"]] == [("??_7T@@6B@", 2)]
    assert [(entry["name"], entry["reason"]) for entry in metadata["refusals"]] == [
        ("_vtbl_00C03000", "strong-definition")]
    _sections, symbols = L.parse_coff(path.read_bytes())
    assert {sym.name for sym in symbols.values() if sym.sec > 0 and sym.cls == L.EXTERNAL} == {"??_7T@@6B@"}


def test_unverified_ledger_target_is_not_generated(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    rows[0]["status"] = "pending"
    assert plan(code, [table], rows, data)["refusals"][0]["reason"] == "unverified-target-row"


@pytest.mark.parametrize("section,reason", [(-1, "strong-definition"), (0, "common-definition")])
def test_absolute_and_common_definitions_are_not_overridden(tmp_path, section, reason):
    code, table, rows, data = inputs(tmp_path)
    provider = L.write_coff(tmp_path / "provider.obj", [],
                            [("_vtable", section, 8, L.EXTERNAL)])
    result = plan(code, [table, provider], rows, data)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == reason


def test_target_must_win_from_ledger_owner_not_just_exist(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    other = code_object(tmp_path / "earlier.obj")
    result = plan(code, [table, other], rows, data)
    refused = result["refusals"][0]
    assert refused["reason"] == "target-not-winning-provider"
    assert refused["blocked"][0]["providers"][0]["first_object"] == str(other.resolve())
    assert refused["blocked"][0]["providers"][0]["ledger_object"] == str(code.resolve())
    result = V.plan(rows, [table, code, other], [], Retail(), data,
                    object_for=lambda row: code, symbol_for=lambda row: row["name"])
    assert result["tables"] == 1


def test_target_provider_index_covers_archive_order_and_kept_objects(tmp_path, monkeypatch):
    a = code_object(tmp_path / "a.obj")
    b = code_object(tmp_path / "b.obj")
    archives = [tmp_path / "a.lib", tmp_path / "b.lib"]
    monkeypatch.setattr(V.coffar, "read_archive",
                        lambda path: [("member.obj", (a if path == archives[0] else b).read_bytes())])
    index = V.first_providers(L.Objects([]), {"_first"}, archives)
    assert index["_first"] == str(archives[0].resolve()) + "(member.obj)"
    index = V.first_providers(L.Objects([b, a]), {"_first"}, archives)
    assert index["_first"] == str(b.resolve())


def test_source_slot_names_and_all_ledger_rvas_survive_bridge_and_queue(tmp_path):
    code, table, rows, data = inputs(tmp_path, ("_second", "_first"))
    rows.append({**rows[0], "target_rva": "0x1100"})
    # _first's ambiguous target prevents generation, but source evidence survives.
    refused = plan(code, [table], rows, data)["refusals"][0]
    assert refused["source_slot_mismatches"] == [
        {"slot": 0, "name": "_second", "ledger_rvas": [0x1010], "relocation_kind": 6,
         "addend": 0, "retail_target_rva": 0x1000},
        {"slot": 1, "name": "_first", "ledger_rvas": [0x1000, 0x1100], "relocation_kind": 6,
         "addend": 0, "retail_target_rva": 0x1010}]
    result = plan(code, [table], rows[:2], data)
    entry = result["entries"][0]
    assert entry["source_slot_mismatches"][0]["name"] == "_second"
    V.write_queue(result, tmp_path / "queue.tsv", "a" * 40)
    text = (tmp_path / "queue.tsv").read_text()
    assert "source_slot_mismatches" in text and "_second" in text and "4112" in text
    assert "bridge-retirement" in text


def test_short_copy_records_missing_source_slots(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    entry = plan(code, [table], rows, data)["entries"][0]
    assert entry["source_slot_mismatches"] == [
        {"slot": 1, "name": "", "ledger_rvas": [], "retail_target_rva": 0x1010,
         "reason": "missing-source-slot"}]


def test_queue_exports_refusals_before_retirement_with_sources(tmp_path):
    import csv
    code, table, rows, data = inputs(tmp_path)
    data.append({"address": "0x3004", "size": "4", "name": "_missing", "kind": "vtable"})
    result = plan(code, [table], rows, data)
    result["entries"][0]["source"] = "Code/table.cpp"
    V.write_queue(result, tmp_path / "queue.tsv")
    with (tmp_path / "queue.tsv").open() as f:
        queued = list(csv.DictReader(f, delimiter="\t"))
    assert [row["state"] for row in queued] == ["refused", "bridged"]
    assert queued[1]["source"] == "Code/table.cpp"
    assert queued[0]["source"] == ""


def test_queue_source_can_come_from_a_data_only_object_mapping(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    result = V.plan(rows, [table, code], [], Retail(), data,
                    object_for=lambda row: code, symbol_for=lambda row: row["name"],
                    source_of={table: "Code/TableOnly.cpp"})
    assert result["entries"][0]["source"] == "Code/TableOnly.cpp"

def test_referenced_only_alias_gets_full_copy_but_unused_alias_does_not(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_used;_unused"
    consumer = L.write_coff(tmp_path / "consumer.obj", [], [("_used", 0, 0, L.EXTERNAL)])
    result = plan(code, [table, consumer], rows, data)
    assert {entry["name"] for entry in result["entries"]} == {"_vtable", "_used"}
    assert result["tables"] == 2 and result["slots"] == 4


def test_alias_that_names_another_retail_address_refuses_entire_group(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_other"
    data.append({**data[0], "address": "0x3010", "name": "_other", "names": ""})
    other = table_object(tmp_path / "other.obj", name="_other")
    result = plan(code, [table, other], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"ambiguous-table-name": 2}


def test_same_address_ledger_rows_with_different_slot_sequences_are_refused(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data.append({**data[0], "name": "_other", "size": "4"})
    other = table_object(tmp_path / "other.obj", name="_other")
    result = plan(code, [table, other], rows, data)
    assert result["tables"] == 0
    assert result["refusal_reasons"] == {"conflicting-retail-slots": 1}


def test_multiple_names_do_not_hide_strong_duplicate(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_other"
    other = table_object(tmp_path / "other.obj", name="_other")
    strong = table_object(tmp_path / "strong.obj", name="_other", selection=0)
    result = plan(code, [table, other, strong], rows, data)
    # _other has a COMDAT and a strong copy: it is never given a generated copy.
    assert [(entry["name"], entry["reason"]) for entry in result["refusals"]] == [
        ("_other", "strong-definition")]
    assert [entry["name"] for entry in result["entries"]] == ["_vtable"]


def test_p8_destructor_only_names_get_all_ten_retail_slots(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    names = ["??_7Win32BIGFileSystem@@6B@", "??_7Rva00604465@@6B@"]
    first = table_object(tmp_path / "win32.obj", name=names[0])
    second = table_object(tmp_path / "opaque.obj", name=names[1])
    data[0].update(name=names[0], names=names[1], size="40")
    result = plan(code, [first, second], rows, data, retail=Retail([0x1000, 0x1010] * 5))
    assert result["tables"] == 2 and result["slots"] == 20
    assert result["refused_tables"] == 0
    assert {entry["name"] for entry in result["entries"]} == set(names)
    for entry in result["entries"]:
        assert entry["previous_extent"] == 4
        assert len(entry["slots"]) == 10
        assert entry["slots"][1]["name"] == "_second"


def renamed_table_inputs(tmp_path, *, addend=0, changed=False, second_address=None):
    name = "??_7SubsystemLegend@@6B@"
    code, _old, rows, data = inputs(tmp_path)
    body = b"\xc7\x01" + struct.pack("<I", addend) + b"\xc3"
    raw = body + b"\xcc" * 9 + body + b"\xcc" * 10
    L.write_coff(code, [(".text", 0x60500020, raw, 0)],
                 [("_first", 1, 0, L.EXTERNAL), ("_second", 1, 16, L.EXTERNAL),
                  (name, 0, 0, L.EXTERNAL)],
                 {1: [(2, name, L.DIR32), (18, name, L.DIR32)]})
    rows[0]["target_size"] = "7"
    if second_address is not None:
        rows[1]["target_size"] = "7"
    table = table_object(tmp_path / "renamed.obj", name=name)
    retail = Retail()
    old_read = retail.read
    def read(rva, size):
        if rva in (0x1000, 0x1010):
            address = 0x3000 if rva == 0x1000 else second_address
            return (b"\xc7" + (b"\x02" if changed else b"\x01") +
                    struct.pack("<I", retail.base + (address or 0x3000)) + b"\xc3")[:size]
        return old_read(rva, size)
    retail.read = read
    return code, table, rows, data, retail, name


def test_stale_ledger_spelling_is_extended_from_matched_row_relocation(tmp_path):
    code, table, rows, data, retail, name = renamed_table_inputs(tmp_path)
    result = plan(code, [table], rows, data, retail=retail)
    assert result["tables"] == 1
    assert result["entries"][0]["name"] == name
    evidence = result["entries"][0]["name_bindings"]
    assert [(b["row_rva"], b["offset"], b["rva"], b["name"]) for b in evidence] == [
        (0x1000, 2, 0x3000, name)]
    assert data[0]["name"] == "_vtable"  # no persistent or caller-owned ledger mutation


@pytest.mark.parametrize("kw,reason", [
    ({"changed": True}, "matched-row-bytes-differ"),
    ({"addend": 4}, "nonzero-vtable-addend")])
def test_current_name_needs_exact_row_bytes_and_zero_table_addend(tmp_path, kw, reason):
    code, table, rows, data, retail, _name = renamed_table_inputs(tmp_path, **kw)
    result = plan(code, [table], rows, data, retail=retail)
    assert result["tables"] == 0
    assert result["name_discovery"]["rejected"][0]["reason"] == reason


def test_current_name_bound_to_two_addresses_refuses_instead_of_picking_one(tmp_path):
    code, table, rows, data, retail, name = renamed_table_inputs(tmp_path, second_address=0x3010)
    result = plan(code, [table], rows, data, retail=retail)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "ambiguous-table-name"
    assert result["name_discovery"]["unindexed"][0]["rva"] == 0x3010


def test_unverified_row_cannot_supply_new_vtable_name(tmp_path):
    code, table, rows, data, retail, _name = renamed_table_inputs(tmp_path)
    rows[0]["status"] = "pending"
    result = plan(code, [table], rows, data, retail=retail)
    assert result["tables"] == 0 and not result["name_discovery"]["bindings"]


def comdat_code(path, body=b"\xe8\0\0\0\0\xc3", callee="_callee", callee_class=L.EXTERNAL,
                associated=None, flags=0x60501020, selection=V.SELECT_ANY, offset=1, kind=L.DIR32):
    """_first and _second as code COMDATs calling one callee; an optional
    (flags) associative section hangs off _first's section."""
    sections = [(".text", flags, body, selection), (".text", flags, body, selection)]
    if associated is not None:
        sections.append((".xdata", associated | V.COMDAT, b"\0" * 4, V.ASSOCIATIVE))
    symbols = [("_first", 1, 0, L.EXTERNAL), ("_second", 2, 0, L.EXTERNAL),
               (callee, 0, 0, callee_class)]
    path = L.write_coff(path, sections, symbols, {1: [(offset, callee, kind)], 2: [(offset, callee, kind)]})
    if associated is not None:  # write_coff leaves the associated section number zero
        raw = bytearray(path.read_bytes())
        _sections, syms = L.parse_coff(bytes(raw))
        symptr = struct.unpack_from("<I", raw, 8)[0]
        aux = next(y for y in syms.values() if y.cls == L.STATIC and y.sec == 3)
        struct.pack_into("<H", raw, symptr + 18 * aux.i + 18 + 12, 1)
        path.write_bytes(bytes(raw))
    return path


def twin_plan(tmp_path, earlier, later=None, **ours):
    code = comdat_code(tmp_path / "code.obj", **ours)
    table = table_object(tmp_path / "table.obj")
    rows = [{"target_rva": hex(rva), "name": name, "source": "Code/code.cpp", "status": "matched"}
            for rva, name in ((0x1000, "_first"), (0x1010, "_second"))]
    data = [{"address": "0x3000", "size": "8", "name": "_vtable", "kind": "vtable"}]
    return V.plan(rows, [table, earlier, code] + ([later] if later else []), [], Retail(), data,
                  object_for=lambda row: code, symbol_for=lambda row: row["name"])


def test_earlier_byte_and_relocation_twin_provides_the_ledger_body(tmp_path):
    # P9: ??_GSubsystemLegend is one inline COMDAT in two TUs; the earlier TU
    # wins the link, and its discardable .debug$F does not load.
    result = twin_plan(tmp_path, comdat_code(tmp_path / "earlier.obj", associated=0x42101040))
    assert (result["tables"], result["refused_tables"], result["twin_target_slots"]) == (1, 0, 2)
    slot = result["entries"][0]["slots"][0]
    assert slot["object"] == str((tmp_path / "earlier.obj").resolve())
    assert slot["twin_of"] == str((tmp_path / "code.obj").resolve())


LOCAL = dict(callee="_local", callee_class=L.STATIC)
# call $+5 / pop eax: the unrelocated call pushes its own address.
SELF_CALL = b"\xe8\x00\x00\x00\x00\x58\x90\x00\x00\x00\x00\xc3"
# fnstenv [esp]: the FPU environment holds the last instruction pointer.
FNSTENV = b"\xd9\x34\x24\x90\x00\x00\x00\x00\xc3"


@pytest.mark.parametrize("flags", [0x60101020, 0x60301020])
def test_alignment_only_twin_without_self_observation_provides_the_ledger_body(tmp_path, flags):
    # LINK-619: RenderObjClass::Get_Bounding_Sphere is one inline body in an /O1
    # unit (ALIGN_1BYTES) and the /O2 owner (ALIGN_16BYTES); bytes, selection and
    # relocations are equal and the body cannot see where it is placed.
    result = twin_plan(tmp_path, comdat_code(tmp_path / "earlier.obj", flags=flags))
    assert (result["tables"], result["refused_tables"], result["twin_target_slots"]) == (1, 0, 2)


def test_position_blind_refuses_unrelocated_calls_and_fpu_environment_stores():
    assert V.position_blind(b"\xe8\x00\x00\x00\x00\xc3", [(1, "_callee", L.REL32)])
    assert not V.position_blind(b"\xe8\x00\x00\x00\x00\x58\xc3", [])
    assert not V.position_blind(b"\xe8\x05\x00\x00\x00\xc3", [])      # forward call, still pushes EIP
    assert not V.position_blind(b"\xd9\x34\x24\xc3", [])          # fnstenv [esp]
    assert not V.position_blind(b"\xdd\x30\xc3", [])               # fnsave [eax]
    assert V.position_blind(b"\xd9\xf6\xc3", [])                   # fdecstp: register form
    assert V.position_blind(b"\xd9\x7c\x24\x04\xc3", [])         # fnstcw: reg 7


@pytest.mark.parametrize("earlier,ours", [
    (dict(body=b"\xe8\0\0\0\0\x90"), {}),             # bytes
    (dict(body=b"\xe8\0\0\0\0\xc3\xcc"), {}),         # size: same prefix, longer section
    (dict(flags=0x60500020), {}),                     # flags other than alignment
    # alignment only, but the body could read its own address (LINK-619):
    (dict(flags=0x60101020, body=SELF_CALL, offset=7), dict(body=SELF_CALL, offset=7)),
    (dict(flags=0x60101020, body=FNSTENV, offset=4), dict(body=FNSTENV, offset=4)),
    (dict(offset=2), {}),                             # relocation offset
    (dict(kind=L.REL32), {}),                         # relocation kind
    (dict(callee="_other"), {}),                      # relocation target
    (LOCAL, LOCAL),  # one spelling, but each object's own static
    (dict(associated=0x40300040), {}),                # loaded associative section
    (dict(selection=4), dict(selection=4)),           # EXACT_MATCH twins: SELECT_ANY only
    (dict(selection=4), {}),                          # selections differ
])
def test_earlier_copy_that_is_not_a_proven_twin_still_refuses(tmp_path, earlier, ours):
    result = twin_plan(tmp_path, comdat_code(tmp_path / "earlier.obj", **earlier), **ours)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "target-not-winning-provider"


def weak_code(path, default="_dflt", characteristics=3, aux=True, default_class=L.EXTERNAL,
              body=b"\xe9\0\0\0\0", callee="_weak", callee_class=V.WEAK_EXTERNAL):
    """_first and _second as adjustor-thunk COMDATs jumping to a weak external
    (`??_EX` defaulting to `??_GX`). The record after the callee always holds
    IMAGE_WEAK_EXTERN aux bytes (TagIndex, Characteristics); aux=False leaves
    the callee's aux count zero, so they are not its aux record."""
    sections = [(".text", 0x60501020, body, V.SELECT_ANY), (".text", 0x60501020, body, V.SELECT_ANY)]
    symbols = [("_first", 1, 0, L.EXTERNAL), ("_second", 2, 0, L.EXTERNAL),
               (callee, 0, 0, callee_class), ("_aux", 0, 0, 0), (default, 0, 0, default_class)]
    path = L.write_coff(path, sections, symbols, {1: [(1, callee, L.REL32)], 2: [(1, callee, L.REL32)]})
    raw = bytearray(path.read_bytes())
    symptr = struct.unpack_from("<I", raw, 8)[0]
    _sections, syms = L.parse_coff(bytes(raw))
    weak = next(y.i for y in syms.values() if y.name == callee)
    raw[symptr + 18 * (weak + 1):symptr + 18 * (weak + 2)] = struct.pack("<II", weak + 2, characteristics) + bytes(10)
    raw[symptr + 18 * weak + 17] = 1 if aux else 0
    path.write_bytes(bytes(raw))
    return path


def weak_twin_plan(tmp_path, earlier, **ours):
    code = weak_code(tmp_path / "code.obj", **ours)
    table = table_object(tmp_path / "table.obj")
    rows = [{"target_rva": hex(rva), "name": name, "source": "Code/code.cpp", "status": "matched"}
            for rva, name in ((0x1000, "_first"), (0x1010, "_second"))]
    data = [{"address": "0x3000", "size": "8", "name": "_vtable", "kind": "vtable"}]
    return V.plan(rows, [table, earlier, code], [], Retail(), data,
                  object_for=lambda row: code, symbol_for=lambda row: row["name"])


def test_earlier_adjustor_thunk_twin_through_the_same_weak_external_provides_the_ledger_body(tmp_path):
    # LINK-619: ??_ETeam@@O3AEPAXI@Z in TeamCtor.cpp (first) and TeamDeleter.cpp
    # (the ledger row) both jump to the weak ??_ETeam@@MAEPAXI@Z -> ??_GTeam.
    result = weak_twin_plan(tmp_path, weak_code(tmp_path / "earlier.obj"))
    assert (result["tables"], result["refused_tables"], result["twin_target_slots"]) == (1, 0, 2)
    slot = result["entries"][0]["slots"][0]
    assert slot["object"] == str((tmp_path / "earlier.obj").resolve())
    assert slot["twin_of"] == str((tmp_path / "code.obj").resolve())


@pytest.mark.parametrize("earlier,ours", [
    (dict(default="_other"), {}),                         # weak default differs
    (dict(characteristics=2), {}),                        # weak search characteristics differ
    (dict(aux=False), {}),                                # one weak record without its aux record
    (dict(aux=False), dict(aux=False)),                   # no aux record: no default to compare
    (dict(default_class=L.STATIC), dict(default_class=L.STATIC)),  # default is not an external name
    (dict(callee_class=L.STATIC), dict(callee_class=L.STATIC)),    # aux bytes on a non-weak target
    (dict(callee="_wother"), {}),                         # another weak name
])
def test_weak_external_relocations_must_agree_to_be_twins(tmp_path, earlier, ours):
    result = weak_twin_plan(tmp_path, weak_code(tmp_path / "earlier.obj", **earlier), **ours)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "target-not-winning-provider"


def test_plain_external_and_weak_external_relocations_are_not_twins(tmp_path):
    earlier = comdat_code(tmp_path / "earlier.obj", body=b"\xe9\0\0\0\0", callee="_weak", kind=L.REL32)
    result = weak_twin_plan(tmp_path, earlier)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "target-not-winning-provider"


@pytest.mark.parametrize("selection", [6, V.SELECT_ANY])
def test_later_largest_copy_can_win_so_an_earlier_twin_is_not_proof(tmp_path, selection):
    # Review of 3f603f990a: [earlier, ledger, later] with identical short
    # earlier/ledger copies; a larger LARGEST later copy would win the link.
    later = comdat_code(tmp_path / "later.obj", body=b"\xe8\0\0\0\0\x90\xc3", selection=6)
    earlier = comdat_code(tmp_path / "earlier.obj", selection=selection)
    result = twin_plan(tmp_path, earlier, later, selection=selection)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "target-not-winning-provider"


def test_later_non_comdat_provider_refuses_even_with_selection_metadata(tmp_path, monkeypatch):
    # Re-review of dc58e0ef6d: [earlier, ledger, later] with identical SELECT_ANY
    # earlier/ledger copies and a later plain (non-COMDAT) definition whose
    # section still carries selection 2. parse_coff reads a selection only for
    # COMDAT sections; report it anyway so the bridge's own COMDAT test is what
    # refuses.
    later = comdat_code(tmp_path / "later.obj", flags=0x60500020)
    raw_later, parse = later.read_bytes(), L.parse_coff

    def parse_with_metadata(data):
        sections, symbols = parse(data)
        if data == raw_later:
            for sec in sections:
                sec.sel = V.SELECT_ANY
        return sections, symbols
    monkeypatch.setattr(L, "parse_coff", parse_with_metadata)
    result = twin_plan(tmp_path, comdat_code(tmp_path / "earlier.obj"), later)
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "target-not-winning-provider"


class ThunkRetail(Retail):
    """Retail with the table at 0x3000 and extra code bytes at given RVAs."""

    def __init__(self, values, code):
        super().__init__(values)
        self.code = code

    def read(self, rva, size):
        for start, raw in self.code.items():
            if start <= rva < start + len(raw):
                return raw[rva - start:rva - start + size]
        return super().read(rva, size)


def jmp(at, target):
    return b"\xe9" + struct.pack("<i", target - (at + 5))


def thunk_plan(tmp_path, thunks, code_bytes, slot=0x1020, edit=None):
    """Slot 1 of a two-slot retail table points at `slot`; `thunks` are (rva, size, notes) rows the
    exit link omits; `code_bytes` are retail's bytes there."""
    code, table, rows, data = inputs(tmp_path)
    omitted = L.write_coff(tmp_path / "gthunks.obj", [(".text", 0x60500020, b"\xcc" * 16, 0)],
                           [(f"_j_{rva:x}", 1, 0, L.EXTERNAL) for rva, _size, _notes in thunks][:1])
    rows += [{"target_rva": hex(rva), "target_size": str(size), "name": f"_j_{rva:x}",
              "source": "Code/gen_small/gthunks.cpp", "status": "matched", "notes": notes}
             for rva, size, notes in thunks]
    paths = {"Code/code.cpp": code, "Code/gen_small/gthunks.cpp": omitted}
    if edit:
        edit(rows)
    return V.plan(rows, [table, code], [omitted], ThunkRetail((0x1000, slot), code_bytes), data,
                  object_for=lambda row: paths[row["source"]], symbol_for=lambda row: row["name"])


def test_a_slot_on_an_omitted_jmp_thunk_takes_the_thunks_target(tmp_path):
    # P11: INI::readLine calls XferMD5CRC slot 9; retail slot 11 is the gen-thunk 0x0052B492, a
    # `jmp 0x0060CE41` in Code/gen_small/gthunks_000_admitted.cpp, which the exit link omits.
    result = thunk_plan(tmp_path, [(0x1020, 5, "gen-thunk;gap;target=0x00001010")], {0x1020: jmp(0x1020, 0x1010)})
    assert (result["tables"], result["refused_tables"], result["thunk_forwarded_slots"]) == (1, 0, 1)
    slot = result["entries"][0]["slots"][1]
    assert (slot["name"], slot["rva"], slot["forwarded_from"]) == ("_second", 0x1010, 0x1020)


@pytest.mark.parametrize("thunks,code_bytes", [
    ([(0x1020, 6, "gen-thunk;gap;target=0x00001010")], {0x1020: jmp(0x1020, 0x1010) + b"\x90"}),  # extra bytes
    # Not jmp rel32: the same four bytes after an FF opcode would land on the target.
    ([(0x1020, 5, "gen-thunk;gap;target=0x00001010")], {0x1020: b"\xff" + jmp(0x1020, 0x1010)[1:]}),
    ([(0x1020, 5, "gen-thunk;gap;target=0x00001000")], {0x1020: jmp(0x1020, 0x1010)}),           # note disagrees
    ([(0x1020, 5, "gap;target=0x00001010")], {0x1020: jmp(0x1020, 0x1010)}),                     # not a gen-thunk row
    ([(0x1020, 5, "gen-thunk;gap;target=0x00001030")], {0x1020: jmp(0x1020, 0x1030)}),           # missing target
    ([(0x1020, 5, "gen-thunk;gap;target=0x00001040"), (0x1040, 16, "gap")],                      # omitted target
     {0x1020: jmp(0x1020, 0x1040)}),
    ([(0x1020, 5, "gen-thunk;gap;target=0x00001040"), (0x1040, 5, "gen-thunk;gap;target=0x00001010")],  # chain
     {0x1020: jmp(0x1020, 0x1040), 0x1040: jmp(0x1040, 0x1010)}),
])
def test_anything_but_one_jmp_to_a_kept_provider_stays_omitted(tmp_path, thunks, code_bytes):
    result = thunk_plan(tmp_path, thunks, code_bytes)
    assert result["tables"] == 0 and result["thunk_forwarded_slots"] == 0
    assert result["refusals"][0]["reason"] == "omitted-target"


def test_a_thunk_address_another_kept_row_also_claims_is_not_forwarded(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    omitted = L.write_coff(tmp_path / "gthunks.obj", [(".text", 0x60500020, b"\xcc" * 16, 0)],
                           [("_j_1020", 1, 0, L.EXTERNAL)])
    rows += [{"target_rva": "0x1020", "target_size": "5", "name": "_j_1020", "source": "Code/gen_small/gthunks.cpp",
              "status": "matched", "notes": "gen-thunk;gap;target=0x00001010"},
             # the same thunk rowed again in a kept object: the omitted copy is not the only row there
             {"target_rva": "0x1020", "target_size": "5", "name": "_j_1020_kept", "source": "Code/code.cpp",
              "status": "matched", "notes": "gen-thunk;gap;target=0x00001010"}]
    paths = {"Code/code.cpp": code, "Code/gen_small/gthunks.cpp": omitted}
    result = V.plan(rows, [table, code], [omitted], ThunkRetail((0x1000, 0x1020), {0x1020: jmp(0x1020, 0x1010)}),
                    data, object_for=lambda row: paths[row["source"]], symbol_for=lambda row: row["name"])
    assert result["tables"] == 0 and result["refusals"][0]["reason"] == "omitted-target"


def test_a_truncated_retail_read_at_the_thunk_stays_omitted(tmp_path):
    result = thunk_plan(tmp_path, [(0x1020, 5, "gen-thunk;gap;target=0x00001010")], {0x1020: b"\xe9\xeb\xff"})
    assert result["tables"] == 0 and result["refusals"][0]["reason"] == "omitted-target"


def test_omitted_thunk_rows_that_disagree_on_the_target_stay_omitted(tmp_path):
    rows = [(0x1020, 5, "gen-thunk;gap;target=0x00001010"), (0x1020, 5, "gen-thunk;gap;target=0x00001000")]
    result = thunk_plan(tmp_path, rows, {0x1020: jmp(0x1020, 0x1010)})
    assert result["tables"] == 0 and result["refusals"][0]["reason"] == "omitted-target"


def test_a_forwarded_target_that_fails_a_provider_check_stays_omitted(tmp_path):
    # The thunk itself is sound, but its destination row is unverified.
    def unverify(rows):
        next(row for row in rows if row["name"] == "_second")["status"] = "pending"
    result = thunk_plan(tmp_path, [(0x1020, 5, "gen-thunk;gap;target=0x00001010")],
                        {0x1020: jmp(0x1020, 0x1010)}, edit=unverify)
    assert result["tables"] == 0 and result["thunk_forwarded_slots"] == 0
    assert result["refusals"][0]["reason"] == "omitted-target"


def weak_table_object(path, weak="_weak", default="_first", characteristics=2, name="_vtable"):
    """A COMDAT table whose slot 0 relocates to an undefined weak external (`??_EX`) with an
    IMAGE_WEAK_EXTERN default (`??_GX`) and slot 1 to `_second`."""
    symbols = [(name, 1, 0, L.EXTERNAL), (weak, 0, 0, V.WEAK_EXTERNAL), ("_aux", 0, 0, 0),
               (default, 0, 0, L.EXTERNAL)]
    symbols += [("_second", 0, 0, L.EXTERNAL)] if default != "_second" else []
    path = L.write_coff(path, [(".rdata", 0x40300040 | V.COMDAT, bytes(8), V.SELECT_ANY)], symbols,
                        {1: [(0, weak, L.DIR32), (4, "_second", L.DIR32)]})
    raw = bytearray(path.read_bytes())
    symptr = struct.unpack_from("<I", raw, 8)[0]
    _sections, syms = L.parse_coff(bytes(raw))
    index = next(y.i for y in syms.values() if y.name == weak)
    raw[symptr + 18 * (index + 1):symptr + 18 * (index + 2)] = \
        struct.pack("<II", index + 2, characteristics) + bytes(10)
    raw[symptr + 18 * index + 17] = 1
    path.write_bytes(bytes(raw))
    return path


def weak_slot_plan(tmp_path, *extra, **kw):
    code = code_object(tmp_path / "code.obj")
    table = weak_table_object(tmp_path / "table.obj", **kw)
    rows = [{"target_rva": hex(rva), "name": name, "source": "Code/code.cpp", "status": "matched"}
            for rva, name in ((0x1000, "_first"), (0x1010, "_second"))]
    data = [{"address": "0x3000", "size": "8", "name": "_vtable", "kind": "vtable"}]
    return plan(code, [table, *extra], rows, data)


def test_weak_destructor_slot_resolving_to_the_retail_default_is_correct(tmp_path):
    # LINK-514 lk64/lk65: slot 0 relocates to the undefined weak ??_EX whose default ??_GX
    # is the ledger row at retail's slot-0 address; nothing defines ??_EX, so the linker
    # resolves the slot to ??_GX and the table is already right.
    result = weak_slot_plan(tmp_path)
    assert (result["tables"], result["already_correct"], result["refused_tables"]) == (0, 1, 0)


@pytest.mark.parametrize("flags,selection", [(0x60500020, 0), (0x60501020, V.SELECT_ANY)])
def test_weak_name_defined_anywhere_is_compared_by_its_own_name(tmp_path, flags, selection):
    # A strong or COMDAT ??_EX in any kept object wins over every weak default.
    strong = L.write_coff(tmp_path / "strong.obj", [(".text", flags, b"\xc3", selection)],
                          [("_weak", 1, 0, L.EXTERNAL)])
    result = weak_slot_plan(tmp_path, strong)
    assert (result["tables"], result["already_correct"]) == (1, 0)
    assert [item["slot"] for item in result["entries"][0]["source_slot_mismatches"]] == [0]


@pytest.mark.parametrize("other", [dict(default="_second"), dict(characteristics=1)])
def test_weak_records_that_disagree_leave_the_default_unproven(tmp_path, other):
    # A later kept copy of the same weak name with another default or search rule.
    disagreeing = weak_table_object(tmp_path / "other.obj", name="_other_vtable", **other)
    result = weak_slot_plan(tmp_path, disagreeing)
    assert (result["tables"], result["already_correct"]) == (1, 0)


def test_weak_default_bound_to_another_retail_address_does_not_match(tmp_path):
    # The default is a ledger row, but at 0x1010, not retail's slot-0 target 0x1000.
    result = weak_slot_plan(tmp_path, default="_second")
    assert (result["tables"], result["already_correct"]) == (1, 0)
    assert result["entries"][0]["source_slot_mismatches"][0]["name"] == "_weak"


def test_retail_slots_stop_at_a_word_inside_a_function_body():
    # 0x0083D7F8: the word past AptSpellStore's 14 slots is the string "dds",
    # which reads as an address inside a retail function, not a function start
    import image_report

    class Spanned(Retail):
        def mid_function(self, value):
            return image_report.Retail.mid_function(self, value)

    retail = Spanned((0x1000, 0x1010, 0x1024))
    retail.function_spans = ([(0x1000, 16), (0x1010, 0x40)], {0x1000, 0x1010})
    assert V.retail_slots(retail, {"address": "0x3000", "size": "12"}) == ([0x1000, 0x1010], None)
    retail.function_spans[1].add(0x1024)
    assert V.retail_slots(retail, {"address": "0x3000", "size": "12"}) == ([0x1000, 0x1010, 0x1024], None)
    retail.function_spans = None
    assert V.retail_slots(retail, {"address": "0x3000", "size": "12"}) == ([0x1000, 0x1010, 0x1024], None)
