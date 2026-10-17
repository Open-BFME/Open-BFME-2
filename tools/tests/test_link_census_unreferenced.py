"""retail-truth-2: a COMDAT with no retail address that nothing the link keeps
references loses no copy; a referenced one, or one retail truth can judge,
keeps retail-truth-1's rules (link_census.keep_rule, object_references,
referenced_names; link_check's per-file preview of the same)."""
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L  # noqa: E402
import link_check as C  # noqa: E402
# Synthetic census fixtures never inherit the repository's live data providers.
from test_link_census_currency import isolated_data_ledger  # noqa: E402,F401

TEXT, DATA = 0x60000020, 0xC0000040
COMDAT, INFO, REMOVE = 0x1000, 0x200, 0x800


def coff(path, sections, defined=(), weak=()):
    """Write a COFF object. `sections`: [(name, flags, selection or None,
    associated section number, relocations [symbol name])]; `defined`:
    [(name, section number)] external definitions; every other relocation
    name is an undefined external, except "$sN", section N's own symbol (a
    TU-local reference). `weak`: [(name, default)] weak externals."""
    headers, sym, strings = [], b"", bytearray(4)
    index = {}
    externals = [name for name, _ in defined]
    for _, _, _, _, relocs in sections:
        externals += [name for name in relocs if not name.startswith("$s") and name not in externals]
    externals += [name for pair in weak for name in pair if name not in externals]

    def entry(name, value, section, storage, aux=b""):
        nonlocal sym
        encoded = name.encode()
        if len(encoded) <= 8:
            field = encoded.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        index[name] = len(sym) // 18
        sym += field + struct.pack("<IhHBB", value, section, 0, storage, len(aux) // 18) + aux

    for number, (name, flags, selection, parent, relocs) in enumerate(sections, 1):
        aux = struct.pack("<IHHIHB3x", 4, len(relocs), 0, 0, parent, selection or 0)
        entry(f"$s{number}", 0, number, 3, aux)
    sections_of = dict(defined)
    weak_default = dict(weak)
    for name in externals:
        if name in weak_default:
            continue
        entry(name, 0, sections_of.get(name, 0), 2)
    for name, default in weak:
        entry(name, 0, 0, 105, struct.pack("<II10x", index[default], 3))
    data_start = 20 + 40 * len(sections)
    body = b""
    for number, (name, flags, selection, parent, relocs) in enumerate(sections, 1):
        content = b"/INCLUDE:_forced " if name == ".drectve" else b"\x90" * 4
        pointer = data_start + len(body)
        body += content
        reloc_pointer = data_start + len(body)
        for at, target in enumerate(relocs):
            body += struct.pack("<IIH", at, index[target], 0x14)
        headers.append(name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(content), pointer, reloc_pointer if relocs else 0, 0, len(relocs), 0,
            flags | (COMDAT if selection else 0)))
    table = data_start + len(body)
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, table, len(sym) // 18, 0, 0)
    path.write_bytes(header + b"".join(headers) + body + sym + bytes(strings))
    return path


def test_unreferenced_no_address_copies_lose_nothing():
    copies = [("a.obj", "x", None), ("b.obj", "y", None), ("c.obj", "y", None)]
    assert L.keep_rule(copies) == ({"a.obj": False, "b.obj": True, "c.obj": True}, "first")
    assert L.keep_rule(copies, referenced=True) == ({"a.obj": False, "b.obj": True, "c.obj": True}, "first")
    assert L.keep_rule(copies, referenced=False) == ({"a.obj": False, "b.obj": False, "c.obj": False},
                                                     "unreferenced")


def test_referenced_no_address_copy_still_loses_to_the_first_never_the_majority():
    # b and c agree, a is first: a referenced name keeps link order, not majority
    copies = [("a.obj", "x", None), ("b.obj", "y", None), ("c.obj", "y", None)]
    loses, rule = L.keep_rule(copies, referenced=True)
    assert rule == "first" and not loses["a.obj"] and loses["b.obj"] and loses["c.obj"]


@pytest.mark.parametrize("referenced", [True, False])
def test_a_wrong_body_cannot_hide_by_being_unreferenced(referenced):
    # retail truth judges every name with a retail address, referenced or not
    copies = [("a.obj", "x", "wrong"), ("b.obj", "y", "retail"), ("c.obj", "z", "unknown")]
    loses, rule = L.keep_rule(copies, referenced=referenced)
    assert rule == "retail" and loses == {"a.obj": True, "b.obj": False, "c.obj": True}


def test_comdat_losers_charges_only_referenced_no_address_names():
    objs = [SimpleNamespace(name=n) for n in ("a.obj", "b.obj")]
    facts = [([("used", "x", 1, None), ("dead", "x", 1, None)], [], [], []),
             ([("used", "y", 1, None), ("dead", "y", 1, None)], [], [], [])]
    stats = {}
    assert L.comdat_losers(objs, [], {}, facts) == {"b.obj": {"used", "dead"}}  # retail-truth-1
    assert L.comdat_losers(objs, [], stats, facts, referenced={"used"}) == {"b.obj": {"used"}}
    assert stats == {"symbols_first": 1, "losers_first": 1, "symbols_unreferenced": 1}


def test_object_references_reads_roots_edges_and_skips_debug(tmp_path):
    obj = coff(tmp_path / "a.obj", [
        (".text", TEXT, None, 0, ["_root_callee"]),                     # 1: always kept
        (".text", TEXT, 2, 0, ["_inline_callee", "$s4"]),               # 2: ANY COMDAT ?inl
        (".xdata", DATA, 5, 2, ["_eh_handler"]),                        # 3: associative child of 2
        (".rdata", DATA, 2, 0, ["_static_target"]),                     # 4: a TU-local COMDAT target of 2
        (".debug$F", DATA | REMOVE, None, 0, ["?dead"]),                # 5: FPO record names everything
        (".text", TEXT, 1, 0, ["_gy_callee"]),                          # 6: NODUPLICATES (/Gy)
        (".text", TEXT, 2, 0, ["_dead_callee"]),                        # 7: ANY COMDAT ?dead
        (".drectve", INFO, None, 0, []),                                # 8: /INCLUDE:_forced
    ], defined=[("?inl", 2), ("?dead", 7), ("_gy", 6), ("_main", 1)])
    roots, edges = L.object_references(obj)
    assert roots == {"_root_callee", "_gy_callee", "_forced"}
    assert edges == {"?inl": {"_inline_callee", "_eh_handler", "_static_target"}, "?dead": {"_dead_callee"}}


def test_referenced_names_follows_edges_kept_names_and_links():
    edges = {"?a": {"?b"}, "?b": {"?c"}, "?k": {"?d"}, "?x": {"?y"}, "?w": {"?v"}}
    found = L.referenced_names({"?a", "_weak", "_alias"}, edges, kept={"?k"},
                               links=[("_weak", "?w"), ("_alias", "?z")])
    assert {"?a", "?b", "?c", "?k", "?d", "?w", "?v", "?z"} <= found
    assert "?x" not in found and "?y" not in found
    # an incremental walk returns only the newly reached names
    assert L.referenced_names({"?x"}, edges, known=found) == {"?x", "?y"}


def test_weak_and_alias_references_reach_their_targets_in_a_link(tmp_path, monkeypatch):
    a = coff(tmp_path / "a.obj", [(".text", TEXT, None, 0, ["_weak"])], weak=[("_weak", "?dflt")])
    facts = [([], [], [], [("_weak", "?dflt")])]
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    _, found = L.link_references([a], facts, owners={})
    assert {"_weak", "?dflt"} <= found


def index(comdat, references=None):
    ix = {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj", "b.obj", "c.obj"], "strong": {},
          "comdat": comdat, "blockers": {}, "bytes": {}, "common_schema": C.COMMON_SCHEMA, "common": {},
          "alternates": {}, "selection": {"exceptions": {}, "owners": {}},
          "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    if references is not None:
        ix["references"] = {"schema": C.REFERENCES_SCHEMA, "edges": references[0], "referenced": references[1]}
    return ix


@pytest.fixture
def facts_of(monkeypatch):
    facts, refs = {}, {}
    monkeypatch.setattr(L, "object_facts", lambda obj, truth=None: facts[obj.name])
    monkeypatch.setattr(L, "object_references", lambda obj: refs.get(obj.name, (set(), {})))
    monkeypatch.setattr(L, "common_definitions", lambda obj: {})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    return facts, refs


def test_link_check_exempts_an_unreferenced_differing_copy(facts_of):
    facts, _ = facts_of
    facts["b.obj"] = ([("?dead", "y", 4, None)], [], [], [])
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]}, ({}, set()))
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == []


def test_link_check_charges_a_differing_copy_that_a_kept_definition_references(facts_of):
    facts, _ = facts_of
    facts["b.obj"] = ([("?used", "y", 4, None)], [], [], [])
    ix = index({"?used": [(0, "x", None), (1, "y", None)]}, ({}, {"?used"}))
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?used", "first", None)]


def test_exploit_the_checked_unit_cannot_unreference_what_it_calls(facts_of):
    # b.obj's own always-kept code calls ?dead's differing copy, which the
    # census saw referenced by nothing: its copy is executed, so it loses
    facts, refs = facts_of
    facts["b.obj"] = ([("?dead", "y", 4, None)], ["_f"], ["?dead"], [])
    refs["b.obj"] = ({"?dead"}, {})
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]}, ({}, set()))
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?dead", "first", None)]


def test_exploit_a_reference_through_another_unreferenced_inline_counts_once_reached(facts_of):
    # ?outer (unreferenced so far) calls ?dead; once b.obj's kept code calls
    # ?outer, ?dead is reached through the census's edges and loses too
    facts, refs = facts_of
    facts["b.obj"] = ([("?dead", "y", 4, None)], ["_f"], ["?outer"], [])
    refs["b.obj"] = ({"?outer"}, {})
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]}, ({"?outer": frozenset({"?dead"})}, set()))
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?dead", "first", None)]


def test_refresh_merges_a_refreshed_objects_references(facts_of):
    # c.obj changed since the census and now calls ?dead: b.obj's differing
    # copy is executed in the link the preview stands for
    facts, refs = facts_of
    facts["b.obj"] = ([("?dead", "y", 4, None)], [], [], [])
    facts["c.obj"] = ([], ["_g"], ["?dead"], [])
    refs["c.obj"] = ({"?dead"}, {})
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]}, ({}, set()))
    C.refresh(ix, [SimpleNamespace(name="c.obj")], None)
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?dead", "first", None)]


def test_an_index_without_references_judges_under_the_previous_rules(facts_of, capsys):
    facts, _ = facts_of
    facts["b.obj"] = ([("?dead", "y", 4, None)], [], [], [])
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]})
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?dead", "first", None)]
    assert L.PREVIOUS_RULES in capsys.readouterr().err


def test_index_tables_carry_the_reference_graph():
    tables = C.index_tables([], [], {}, {"edges": {"?a": frozenset({"?b"})}, "referenced": {"?a", "?b"}})
    assert tables["references"] == {"schema": C.REFERENCES_SCHEMA, "edges": {"?a": frozenset({"?b"})},
                                    "referenced": {"?a", "?b"}}
    assert "references" not in C.index_tables([], [], {})


def test_rules_ids_and_rebaseline_order():
    assert (L.RULES, L.PREVIOUS_RULES) == ("retail-truth-2", "retail-truth-1")
    assert {L.PREVIOUS_RULES, L.PREVIOUS_RULES_NO_WRONG_SELECTED, L.RULES_NO_WRONG_SELECTED} <= set(L.KNOWN_RULES)
    previous = [{"date": "2026-10-17 19:27", "commit": "a", "rules": L.PREVIOUS_RULES}]
    census = {"when": "2026-10-18 00:00", "rules": L.RULES}
    with pytest.raises(SystemExit, match="must be the re-baseline"):
        L.check_history_rules(previous, census)
    L.check_history_rules(previous, census, rebaseline={"rules": L.PREVIOUS_RULES})
    with pytest.raises(SystemExit, match="previous figures"):
        L.check_history_rules(previous, census, rebaseline={"rules": L.LEGACY_RULES})
    done = previous + [{"date": "2026-10-18 00:00", "commit": "b", "rules": L.RULES}]
    L.check_history_rules(done, census)
    with pytest.raises(SystemExit, match="already records"):
        L.check_history_rules(done, census, rebaseline={"rules": L.PREVIOUS_RULES})


def test_in_process_rebaseline_records_previous_rules_from_the_same_judgment(tmp_path, monkeypatch):
    from test_link_census_currency import _record_harness, linked
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(L, "read_history", lambda: [{"date": "2026-10-01 00:00", "commit": "x",
                                                     "rules": L.PREVIOUS_RULES}])
    monkeypatch.setattr(L, "write_status", lambda *a, **k: (
        {"a.cpp", "b.cpp"}, 3, 0, {"a.cpp", "b.cpp"},
        {"accept": lambda: accepted.append(True), "clean_previous_rules": {"a.cpp"}}))
    monkeypatch.setattr(L, "linked_figures", lambda clean: {"linked_bytes": 10 * len(clean),
                                                            "linked_authored": 5 * len(clean), "game_code": 10})
    figure = L.record(linked(obj), [], rebaseline=L.REBASELINE_IN_PROCESS)
    assert accepted == [True]
    assert (figure["rules"], figure["prev_rules"]) == (L.RULES, L.PREVIOUS_RULES)
    assert (figure["files_linked"], figure["files_linked_prev_rule"]) == (2, 1)
    assert (figure["linked_bytes"], figure["linked_bytes_prev_rule"]) == (20, 10)
    assert L.HISTORY.read_text().splitlines()[-1].endswith(f",{L.RULES},{L.PREVIOUS_RULES}")
    # once recorded, an ordinary census continues it and a second re-baseline refuses
    monkeypatch.setattr(L, "read_history", lambda: [{"date": "2026-10-02 00:00", "commit": "abc", "rules": L.RULES}])
    with pytest.raises(SystemExit, match="already records"):
        L.record(linked(obj, when="2026-10-03 00:00"), [], rebaseline=L.REBASELINE_IN_PROCESS)


def test_exploit_a_new_retail_addressed_copy_seeds_what_it_calls(facts_of):
    # b.obj adds a copy of ?rowed (a retail address: verdict "retail") that
    # calls ?dead; ?rowed is in the image whoever calls it, so ?dead is
    # executed and b.obj's differing copy of it loses
    facts, refs = facts_of
    facts["b.obj"] = ([("?rowed", "r", 4, "retail"), ("?dead", "y", 4, None)], [], [], [])
    refs["b.obj"] = (set(), {"?rowed": frozenset({"?dead"})})
    ix = index({"?dead": [(0, "x", None), (1, "y", None)]}, ({}, set()))
    assert C.check_object(SimpleNamespace(name="b.obj"), ix, None)["comdat"] == [("?dead", "first", None)]
