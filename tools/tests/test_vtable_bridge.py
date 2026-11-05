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


def plan(code, tables, rows, data, omitted=(), retail=None, object_for=None, archives=()):
    return V.plan(rows, tables + [code], omitted, retail or Retail(), data,
                  archives=archives, object_for=object_for or (lambda row: code),
                  symbol_for=lambda row: row["name"])


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


def test_strong_definition_under_another_ledger_name_also_refuses(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_other"
    strong = table_object(tmp_path / "other.obj", name="_other", selection=0)
    assert plan(code, [table, strong], rows, data)["refusals"][0]["reason"] == "strong-definition"


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


def test_multiple_kept_vtable_names_are_not_merged_or_aliased(tmp_path):
    code, table, rows, data = inputs(tmp_path)
    data[0]["names"] = "_other"
    other = table_object(tmp_path / "other.obj", name="_other")
    assert plan(code, [table, other], rows, data)["refusals"][0]["reason"] == "multiple-kept-names"


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


def test_build_bridge_writes_counted_plan_and_refusal_queue(tmp_path, monkeypatch):
    code, table, rows, data = inputs(tmp_path)
    data.append({"address": "0x3004", "size": "4", "name": "_missing", "kind": "vtable"})
    monkeypatch.setattr(V.build, "row_object", lambda row: code)
    monkeypatch.setattr(V.build, "ledger_object_symbol", lambda row: row["name"])
    path, metadata = V.build_bridge(rows, [table, code], [], [], tmp_path, Retail(), tables=data)
    assert path.name == "retail_vtables.obj"
    assert (metadata["tables"], metadata["slots"], metadata["refused_tables"]) == (1, 2, 1)
    disk = json.loads((tmp_path / "vtable_bridge.json").read_text())
    assert disk["tables"] == 1 and disk["slots"] == 2
    assert "no-kept-definition" in (tmp_path / "vtable_bridge_queue.tsv").read_text()
    path, empty = V.build_bridge(rows, [code], [], [], tmp_path, Retail(), tables=data)
    assert path is None and empty["tables"] == 0
    assert not (tmp_path / "retail_vtables.obj").exists()


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
