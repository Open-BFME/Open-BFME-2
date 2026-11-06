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
    assert result["tables"] == 0
    assert result["refusals"][0]["reason"] == "strong-definition"


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


@pytest.mark.parametrize("earlier,ours", [
    (dict(body=b"\xe8\0\0\0\0\x90"), {}),             # bytes
    (dict(body=b"\xe8\0\0\0\0\xc3\xcc"), {}),         # size: same prefix, longer section
    (dict(flags=0x60301020), {}),                     # flags (alignment)
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
