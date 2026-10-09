"""link_census: which COMDAT copies lose, judged by retail truth.

Ported from Open-BFME-1's tools/tests/test_link_census.py with the rules; the
cases that need Open-BFME-1's own retail image, its data ledger or its route=
verdicts are replaced by this repository's equivalents (see each test)."""
import collections
import struct
import time
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L  # noqa: E402

TEXT = 0x1000


@pytest.fixture(autouse=True)
def isolated_data_ledger(tmp_path, monkeypatch):
    # Synthetic census/order fixtures must not inherit live repository data
    # providers. Tests of populated/malformed data rows still supply their own
    # rows/path and exercise the unchanged real data loader and byte gate.
    import data_rows
    empty = tmp_path / "data_rows.csv"
    empty.write_bytes((data_rows.HEADER + "\n").encode())
    loader = data_rows.load
    monkeypatch.setattr(data_rows, "DATA_ROWS", empty)
    monkeypatch.setattr(data_rows, "load", lambda path=None: loader(path or data_rows.DATA_ROWS))


def truth(image, ledger=None, pinned=None, shared=(), import_routes=None):
    """A RetailTruth over a synthetic .text at TEXT, without reading the repo."""
    t = object.__new__(L.RetailTruth)
    t.image = bytes(image)
    # raw_size: this repository's build.rva_to_file_offset refuses zero-filled data
    t.sections = [{"name": ".text", "rva": TEXT, "size": len(image), "raw_pointer": 0, "raw_size": len(image)}]
    t.ledger = collections.defaultdict(set, {k: set(v) for k, v in (ledger or {}).items()})
    t.pinned = collections.defaultdict(set, {k: set(v) for k, v in (pinned or {}).items()})
    t.import_routes = {k: set(v) for k, v in (import_routes or {}).items()}
    t.slots = collections.defaultdict(set)
    t.shared = set(shared)
    t._cache = {}
    return t


def jmp(at, to):
    return b"\xe9" + struct.pack("<i", to - (at + 5))


def symbol(name, section=1, value=0):
    return {"name": name, "section": section, "storage": L.EXTERNAL, "value": value}


def referent(name):
    return {"name": name, "section": 0, "storage": L.EXTERNAL, "value": 0}


# retail: 0x1000 `jmp 0x1020` (~AsciiString), 0x1010 `jmp 0x1020` (~StringBase), 0x1020 releaseBuffer
IMAGE = bytearray(0x40)
IMAGE[0x00:0x05] = jmp(0x1000, 0x1020)
IMAGE[0x10:0x15] = jmp(0x1010, 0x1020)
IMAGE[0x20] = 0xC3
LEDGER = {"dtor": {0x1000}, "base_dtor": {0x1010}, "release": {0x1020}}


def test_copy_jumping_to_retail_target_is_retail():
    t = truth(IMAGE, LEDGER)
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("release"))], "a", 5) == "retail"


def test_pin_does_not_hide_a_wrong_target():
    # the byte gate accepts base_dtor -> 0x1020 through a pin; retail truth
    # resolves base_dtor to its own row 0x1010, which is not where retail jumps
    t = truth(IMAGE, LEDGER, pinned={"base_dtor": {0x1020}})
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("base_dtor"))], "b", 5) == "wrong"


def test_ilt_stub_is_followed_but_a_padded_jmp_is_not():
    image = bytearray(IMAGE) + bytearray(0x20)
    image[0x40:0x45] = jmp(0x1040, 0x1020)  # a packed ILT table: stub for releaseBuffer
    image[0x45:0x4A] = jmp(0x1045, 0x1000)
    image[0x08:0x0D] = b"\xe8" + struct.pack("<i", 0x1040 - 0x100D)  # call through the stub
    ledger = {**LEDGER, "caller": {0x1008}}
    body = b"\xe8\0\0\0\0"
    assert truth(image, ledger)._stub(0x1040) == 0x1020
    assert truth(image, ledger)._stub(0x1010) is None
    assert truth(image, ledger).verdict(symbol("caller"), body, [(1, L.RetailTruth.REL32, referent("release"))],
                                        "c", 5) == "retail"
    image[0x08:0x0D] = b"\xe8" + struct.pack("<i", 0x1010 - 0x100D)  # call ~StringBase: padded, a function
    assert truth(image, ledger).verdict(symbol("caller"), body, [(1, L.RetailTruth.REL32, referent("release"))],
                                        "d", 5) == "wrong"


def test_packed_jumps_in_data_are_not_ilt_stubs():
    image = bytearray(IMAGE) + bytearray(0x20)
    raw = len(IMAGE)
    image[raw:raw + 5] = jmp(0x2000, 0x1020)
    image[raw + 5:raw + 10] = jmp(0x2005, 0x1020)
    image[0x08:0x0D] = b"\xe8" + struct.pack("<i", 0x2005 - 0x100D)
    ledger = {**LEDGER, "caller": {0x1008}}
    t = truth(image, ledger)
    t.sections.append({"name": ".rdata", "rva": 0x2000, "size": 0x20, "raw_pointer": raw, "raw_size": 0x20})
    assert t._stub(0x2005) is None
    assert t.verdict(symbol("caller"), b"\xe8\0\0\0\0",
                     [(1, L.RetailTruth.REL32, referent("release"))], "data-jumps", 5) == "wrong"


def test_route_claims_are_refused_until_they_can_be_verified():
    # Open-BFME-1 re-derives each route= claim with pin_consistency.route_verdict;
    # this repository has no such verdict, so no claim adds a target and any
    # claim refuses the census rather than being trusted.
    import pytest
    assert L.validated_import_routes({}) == {}
    with pytest.raises(SystemExit, match="route_verdict"):
        L.validated_import_routes({("_ntohs@4", 0x1040): "WSOCK32.dll!ntohs"})


def test_symbols_csv_carries_no_route_claim_today():
    assert L.route_claims() == {}
    assert L.validated_import_routes() == {}


def test_import_call_route_never_becomes_a_body_home_or_dir32_identity():
    image = bytearray(0x60)
    image[0x30:0x36] = b"\x90" * 6  # first pin is the only function-body home
    route_body = b"\xff\x25" + struct.pack("<I", 0x2000)
    image[0x40:0x46] = route_body
    image[0x08:0x0D] = b"\x68" + struct.pack("<I", L.BASE + 0x1040)
    pinned = {"_ntohs@4": {0x1030}}
    routes = {"_ntohs@4": {0x1040}}
    t = truth(image, {"pointer": {0x1008}}, pinned=pinned, import_routes=routes)
    assert t.addresses("_ntohs@4", L.RetailTruth.REL32) == {0x1030, 0x1040}
    assert t.addresses("_ntohs@4", L.RetailTruth.DIR32) == {0x1030}
    assert t.verdict(symbol("pointer"), b"\x68\0\0\0\0",
                     [(1, L.RetailTruth.DIR32, referent("_ntohs@4"))], "data", 5) == "wrong"
    assert t.verdict(symbol("_ntohs@4"), route_body, [], "home", 6) == "wrong"
    t.ledger["_ntohs@4"].add(0x1030)
    assert t.addresses("_ntohs@4", L.RetailTruth.REL32) == {0x1030}  # canonical ledger wins
    image[0x00:0x05] = b"\xe8" + struct.pack("<i", 0x1040 - 0x1005)
    canonical = truth(image, {"caller": {0x1000}, "_ntohs@4": {0x1030}},
                      pinned=pinned, import_routes=routes)
    assert canonical.verdict(symbol("caller"), b"\xe8\0\0\0\0",
                             [(1, L.RetailTruth.REL32, referent("_ntohs@4"))], "ledger", 5) == "wrong"


def test_static_referent_is_unknown_and_absolute_symbol_is_checked():
    image = bytearray(IMAGE)
    image[0x28:0x2E] = b"\x64\xa1\0\0\0\0"  # mov eax, fs:[__except_list]
    t = truth(image, {**LEDGER, "seh": {0x1028}})
    body = b"\x64\xa1\0\0\0\0"
    local = {"name": "_$E2", "section": 3, "storage": 3, "value": 0}
    assert t.verdict(symbol("seh"), body, [(2, L.RetailTruth.DIR32, referent("__except_list"))], "h", 6) == "retail"
    assert t.verdict(symbol("seh"), body, [(2, L.RetailTruth.DIR32, local)], "i", 6) == "unknown"


def test_verdict_cache_distinguishes_absolute_symbol_from_other_static():
    image = bytearray(IMAGE)
    image[0x28:0x2E] = b"\x64\xa1\0\0\0\0"
    t = truth(image, {**LEDGER, "seh": {0x1028}})
    body = b"\x64\xa1\0\0\0\0"
    absolute = {"name": "__except_list", "section": 3, "storage": 3, "value": 0}
    other = {"name": "_$E2", "section": 3, "storage": 3, "value": 0}

    def relocs(target):
        return [(2, L.RetailTruth.DIR32, target)]

    assert t.verdict(symbol("seh"), body, relocs(absolute), "same-digest", 6) == "retail"
    assert t.verdict(symbol("seh"), body, relocs(other), "same-digest", 6) == "unknown"


def test_verdict_cache_distinguishes_same_section_local_offsets_and_symbol_value():
    image = bytearray(IMAGE)
    # Both pre-link copies contain the same zero addend and receive the same
    # normalised COMDAT digest.  Retail points eight bytes into the COMDAT.
    image[0x24:0x29] = b"\xa1" + struct.pack("<I", L.BASE + 0x102C)
    t = truth(image, {**LEDGER, "local_user": {0x1028}})
    body = b"\xa1\0\0\0\0"
    owner = symbol("local_user", value=4)  # COMDAT begins at 0x1024

    def local(value):
        return {"name": "_$E2", "section": owner["section"], "storage": 3, "value": value}

    assert t.verdict(owner, body, [(1, L.RetailTruth.DIR32, local(8))], "same-digest", 5) == "retail"
    # Before the cache key included the local value, this reused "retail".
    assert t.verdict(owner, body, [(1, L.RetailTruth.DIR32, local(12))], "same-digest", 5) == "wrong"

    # The external symbol's offset changes the retail start and is likewise
    # part of the judgment even when name, body, digest and relocations match.
    shifted = symbol("local_user", value=0)
    assert t.verdict(shifted, body, [(1, L.RetailTruth.DIR32, local(8))], "same-digest", 5) == "wrong"

    # Evaluation order must not decide the result either: a wrong copy cached
    # first cannot poison the retail copy with the same normalised digest.
    reverse = truth(image, {**LEDGER, "local_user": {0x1028}})
    assert reverse.verdict(owner, body, [(1, L.RetailTruth.DIR32, local(12))], "same-digest", 5) == "wrong"
    assert reverse.verdict(owner, body, [(1, L.RetailTruth.DIR32, local(8))], "same-digest", 5) == "retail"


def test_pin_is_read_as_va_and_rva():
    assert L.RetailTruth._rvas(0x0044A061) == {0x0044A061, 0x0004A061}
    assert L.RetailTruth._rvas(0x0003A061) == {0x0003A061}


def test_string_literal_is_checked_by_content():
    image = bytearray(IMAGE)
    image[0x30:0x32] = b"A\0"
    image[0x38:0x3D] = b"h" + struct.pack("<I", L.BASE + 0x1030)  # push offset "A"
    t = truth(image, {**LEDGER, "pusher": {0x1038}})
    body = b"\x68\0\0\0\0"
    literal = {"name": "??_C@_01A@A?$AA@", "section": 2, "storage": L.EXTERNAL, "value": 0, "content": b"A\0"}
    assert t.verdict(symbol("pusher"), body, [(1, L.RetailTruth.DIR32, literal)], "j", 5) == "retail"
    other = {**literal, "content": b"B\0"}
    assert t.verdict(symbol("pusher"), body, [(1, L.RetailTruth.DIR32, other)], "k", 5) == "wrong"


def test_bytes_differ_is_wrong_and_unknown_name_is_unknown():
    t = truth(IMAGE, LEDGER)
    assert t.verdict(symbol("release"), b"\xc2\x04\x00", [], "e", 3) == "wrong"
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("nowhere"))], "f", 5) == "unknown"


def test_no_retail_address_is_none():
    t = truth(IMAGE, LEDGER)
    assert t.verdict(symbol("inline_only"), b"\xc3", [], "g", 1) is None


def test_keep_rule_retail_truth_ignores_link_order():
    copies = [("a.obj", "owner", "wrong"), ("b.obj", "right", "retail"), ("c.obj", "owner", "wrong")]
    loses, rule = L.keep_rule(copies)
    assert rule == "retail"
    assert loses == {"a.obj": True, "b.obj": False, "c.obj": True}


def test_keep_rule_unknown_copies_follow_the_proven_one():
    copies = [("a.obj", "x", "unknown"), ("b.obj", "y", "retail"), ("c.obj", "y", "retail")]
    assert L.keep_rule(copies)[0] == {"a.obj": True, "b.obj": False, "c.obj": False}
    copies = [("a.obj", "x", "unknown"), ("b.obj", "x", "unknown"), ("c.obj", "z", "unknown")]
    assert L.keep_rule(copies)[0] == {"a.obj": False, "b.obj": False, "c.obj": True}


def test_keep_rule_without_retail_address_keeps_first_in_link_order():
    copies = [("a.obj", "x", None), ("b.obj", "y", None), ("c.obj", "y", None)]
    loses, rule = L.keep_rule(copies)
    assert rule == "first"
    assert loses == {"a.obj": False, "b.obj": True, "c.obj": True}


def test_shared_claim_mismatch_is_unknown_not_wrong():
    # base_dtor's only address is claimed by several names: disagreeing with it
    # says the ledger is wrong, not the copy
    t = truth(IMAGE, LEDGER, shared={0x1010})
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("base_dtor"))], "l", 5) == "unknown"


def import_library(tmp_path, entries):
    """A COFF archive of short import objects [(stub, dll, name type)] (CODE)."""
    data = bytearray(b"!<arch>\n")
    for stub, dll, name_type in entries:
        names = stub.encode() + b"\0" + dll.encode() + b"\0"
        body = struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, 0x14C, 0, len(names), 0, name_type << 2) + names
        header = b"stub/".ljust(16) + b"0".ljust(12) + b"0".ljust(6) + b"0".ljust(6) + b"0".ljust(8)
        data += header + str(len(body)).encode().ljust(10) + b"`\n" + body + (b"\n" if len(body) & 1 else b"")
    path = tmp_path / "import.lib"
    path.write_bytes(bytes(data))
    return path


def test_call_stub_is_excused_only_when_retail_imports_it_from_that_dll(tmp_path):
    stubs = L.library_import_thunks(import_library(tmp_path, [
        ("_socket@12", "WSOCK32.dll", 0),        # by ordinal: the undecorated stub names it
        ("_htons@4", "WSOCK32.dll", 0),
        ("_GetCurrentThreadId@0", "KERNEL32.dll", 3),
        ("_strcpy", "MSVCR71.dll", 2),
    ]))
    assert stubs["_socket@12"] == {("wsock32.dll", "socket")}
    assert stubs["_strcpy"] == {("msvcr71.dll", "strcpy")}
    imported = {"socket": {"wsock32.dll"}, "GetCurrentThreadId": {"kernel32.dll"}, "strcpy": {"msvcr71.dll"},
                "htonl": {"wsock32.dll"}, "ntohs": {"wsock32.dll"}}
    assert L.excused("_socket@12", set(), imported, stubs)
    assert L.excused("_GetCurrentThreadId@0", set(), imported, stubs)
    assert L.excused("_strcpy", set(), imported, stubs)
    assert not L.excused("_htons@4", set(), imported, stubs)  # retail imports htonl and ntohs, not htons
    assert not L.excused("_socket@12", set(), {"socket": {"ws2_32.dll"}}, stubs)  # another DLL's socket
    assert L.excused("__imp__socket@12", set(), imported, stubs)
    assert not L.excused("__imp__htons@4", set(), imported, stubs)


def test_build_dump_reads_the_source_not_the_note():
    cpp = {"name": "?f@@YAXXZ", "target_rva": "0x0082B870", "source": "Code/x/Thunk.cpp",
           "notes": "exact C++ __emit thunk converted from MASM dump"}
    assert not L.build_dump(cpp)  # real C++ whose note mentions __emit
    assert L.build_dump(cpp, {("?f@@YAXXZ", "0x0082B870")})  # progress.py's scan found a naked body
    assert L.build_dump({**cpp, "source": "Code/masm_dumps/x.asm", "notes": ""})
    assert L.build_dump({**cpp, "notes": "gen-dump"})


def test_map_names_the_object_whose_copy_was_selected():
    text = "\n".join([
        "  Address         Publics by Value              Rva+Base     Lib:Object",
        "",
        " 0000:00000000       ___safe_se_handler_count   00000000     <absolute>",
        " 0001:00000840       ?__stl_new@_STL@@YAPAXI@Z  00401840 f i game_a.obj",
        " 0001:00000489       ?_RTC_GetSrcLine@@YAHKPADHPAHPAPAD@Z 00401489 f   inputs_^program ^files_x.obj",
        " 0003:00000010       ?g@@3HA                    00c00010     game_b.obj",
        "",
        " Static symbols",
        " 0001:00000900       _local                     00401900 f   game_c.obj",
    ])
    found = L.selected_definitions(text)
    assert found["?__stl_new@_STL@@YAPAXI@Z"] == "game_a.obj"
    assert found["?_RTC_GetSrcLine@@YAHKPADHPAHPAPAD@Z"] == "inputs_^program ^files_x.obj"
    assert found["?g@@3HA"] == "game_b.obj"
    assert "_local" not in found


# wrong_selected: a file does not link when a name it touches resolves, in the
# link, to a kept definition proven not retail's. Facts are object_facts'
# (copies [(name, digest, size, verdict)], strong, undefined, weaks).
def _selection(facts, owners, kept):
    present = [Path(name) for name in facts]
    results, exceptions = L.selection_verdicts(present, list(facts.values()), owners, kept)
    wrong = {obj: sorted(n for n in L.touched_names(fact) if results.get(n) == "wrong") for obj, fact in facts.items()}
    return present, results, exceptions, wrong


def test_wrong_kept_comdat_charges_every_user():
    facts = {"a.obj": ([("f", "x", 5, "wrong")], [], [], []),
             "b.obj": ([("f", "y", 5, "retail")], [], [], []),
             "c.obj": ([], [], ["f"], [])}
    _, results, _, wrong = _selection(facts, {}, {"f": "a.obj"})
    assert results["f"] == "wrong" and wrong == {"a.obj": ["f"], "b.obj": ["f"], "c.obj": ["f"]}
    _, results, _, wrong = _selection(facts, {}, {"f": "b.obj"})  # the link kept retail's copy
    assert results["f"] == "ok" and not any(wrong.values())


def test_wrong_kept_duplicate_is_not_the_owners():
    # operator new: GameMemory.obj first in link order, retail's body is mem_ops.obj's
    facts = {"gm.obj": ([], ["new"], [], []), "mem.obj": ([], ["new"], [], []), "user.obj": ([], [], ["new"], [])}
    owners = {"new": {"mem.obj"}}
    _, results, _, wrong = _selection(facts, owners, {"new": "gm.obj"})
    assert results["new"] == "wrong" and wrong["user.obj"] == ["new"]
    _, results, _, wrong = _selection(facts, owners, {"new": "mem.obj"})
    assert results["new"] == "ok" and not wrong["user.obj"]
    # proven bytes decide before ownership: a kept copy proven retail is fine
    facts["gm.obj"] = ([("new", "x", 5, "retail")], ["new"], [], [])
    _, results, _, _ = _selection(facts, owners, {"new": "gm.obj"})
    assert results["new"] == "ok"


def test_unknown_selection_is_not_penalised():
    facts = {"a.obj": ([("g", "x", 5, None)], [], [], []),        # no retail address, copies differ
             "b.obj": ([("g", "y", 5, None)], ["h"], [], []),      # h: duplicate with no ledger owner
             "c.obj": ([], ["h"], ["g"], []),
             "d.obj": ([("u", "z", 5, "unknown")], [], [], [])}   # one copy, unproven: nothing to choose
    _, results, _, wrong = _selection(facts, {}, {"g": "a.obj", "h": "b.obj", "u": "d.obj"})
    assert results == {"g": "unknown", "h": "unknown"}
    assert not any(wrong.values())
    assert L.judge_selected(None, {}, {"a.obj", "b.obj"}, {"a.obj"}, set()) == "unknown"  # not in the map


def test_link_check_agrees_with_the_census(monkeypatch):
    import link_check as C
    facts = {"gm.obj": ([("new", "x", 5, "wrong")], ["new"], [], []),
             "a.obj": ([("f", "p", 5, "wrong")], [], ["new"], []),
             "mem.obj": ([("new", "y", 5, "retail")], ["new"], [], []),
             "b.obj": ([("f", "q", 5, "retail")], [], ["f"], []),
             "c.obj": ([], [], ["f", "g"], [("??_Ec", "??_Gc")]),
             "d.obj": ([("??_Gc", "r", 5, "wrong")], [], [], [])}
    owners = {"new": {"mem.obj"}}
    kept = {"new": "gm.obj", "f": "b.obj", "??_Gc": "d.obj"}  # f: the map kept the second copy
    present, _, exceptions, wrong = _selection(facts, owners, kept)
    assert exceptions == {"f": 3}
    monkeypatch.setattr(L, "common_definitions", lambda obj: {})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})  # synthetic objects: no .drectve to read
    ix = C.index_tables(present, list(facts.values()), {"exceptions": exceptions, "owners": owners})
    ix["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    monkeypatch.setattr(L, "object_facts", lambda obj, truth=None: facts[obj.name])
    for obj in present:
        assert C.check_object(obj, ix, None)["selected"] == wrong[obj.name], obj
    assert wrong["c.obj"] == ["??_Gc"] and wrong["a.obj"] == ["new"]
    # the file that fixes the kept copy links: its own current copy replaces the census's
    facts["gm.obj"] = ([("new", "y", 5, "retail")], ["new"], [], [])
    assert C.check_object(present[0], ix, None)["selected"] == []


def test_rerun_refuses_an_object_missing_now(tmp_path, monkeypatch):
    # falsifier: census replay (--status) omitted objects that went missing after the census
    import pytest
    census = {"missing": 0, "when": "2026-09-29 00:00", "unresolved_classes": {}, "duplicate_classes": {}}
    monkeypatch.setattr(L.subprocess, "run", lambda *a, **k: SimpleNamespace(stdout=""))
    monkeypatch.setattr(L, "objects", lambda rows: ([], [tmp_path / "gone.obj"]))
    monkeypatch.setattr(L, "write_status", lambda *a, **k: pytest.fail("reached write_status"))
    with pytest.raises(SystemExit, match="missing now"):
        L.record(census, [], rerun=True)


def test_an_unexplained_linker_exit_records_nothing(tmp_path, monkeypatch):
    # falsifier: link.exe exiting 7 with an empty log was recorded as a clean census
    import pytest
    monkeypatch.setattr(L, "OUT", tmp_path)
    monkeypatch.setattr(L, "ledger", lambda: [])
    monkeypatch.setattr(L, "objects", lambda rows: ([], []))
    monkeypatch.setattr(L, "link", lambda *a, **k: ("", 0, 7))
    with pytest.raises(SystemExit, match="no linker diagnostic"):
        L.main([])
    L.unexplained_exit(0, "")  # a clean exit needs no diagnostic
    L.unexplained_exit(1120, "x.obj : error LNK2001: unresolved external symbol _f")  # explained


def test_a_crashed_linker_records_nothing_whatever_it_printed(tmp_path, monkeypatch):
    # gpt-6.1-sol review of 9311a6ada0: LNK4099, then an access violation, was recorded as a clean census
    import pytest
    monkeypatch.setattr(L, "OUT", tmp_path)
    monkeypatch.setattr(L, "ledger", lambda: [])
    monkeypatch.setattr(L, "objects", lambda rows: ([], []))
    monkeypatch.setattr(L, "link", lambda *a, **k: ("x.obj : warning LNK4099: PDB was not found\n", 0, 0xC0000005))
    with pytest.raises(SystemExit, match="abnormally"):
        L.main([])
    assert not (tmp_path / "census.json").exists()
    monkeypatch.setattr(L, "link", lambda *a, **k: ("x.obj : warning LNK4099: PDB was not found\n", 0, -11))
    with pytest.raises(SystemExit, match="abnormally"):
        L.main([])
    # a clean exit with no image written is no completed link either
    monkeypatch.setattr(L, "link", lambda *a, **k: ("", 0, 0))
    with pytest.raises(SystemExit, match="wrote no image"):
        L.main([])
    assert not (tmp_path / "census.json").exists()


def test_a_stale_output_is_never_this_links_image(tmp_path, monkeypatch):
    # review of 7791457f07: a one-second-old non-image census.exe passed a 2 s freshness window
    import os
    import pytest
    monkeypatch.setattr(L, "OUT", tmp_path)
    monkeypatch.setattr(L, "ledger", lambda: [])
    monkeypatch.setattr(L, "objects", lambda rows: ([], []))
    stale = tmp_path / "census.exe"
    stale.write_bytes(b"MZ OLD IMAGE FROM A PREVIOUS LINK")
    os.utime(stale, (time.time() - 1, time.time() - 1))
    monkeypatch.setattr(L, "link", lambda *a, **k: ("", 0, 0))  # writes nothing
    with pytest.raises(SystemExit, match="wrote no image"):
        L.main([])
    assert not stale.exists() and not (tmp_path / "census.json").exists()


def test_the_selection_link_is_checked_like_every_link(tmp_path, monkeypatch):
    # review of 7791457f07: the /MAP link's exit code was discarded; a crash with a partial map passed
    import pytest
    monkeypatch.setattr(L, "OUT", tmp_path)
    monkeypatch.setattr(L, "_arg", str)

    def crash_with_map(*a, **k):
        (tmp_path / "selected.map").write_text("PARTIAL MAP FROM CRASH")
        return "warning LNK4099: PDB was not found\n", 0, 0xC0000005
    monkeypatch.setattr(L, "link", crash_with_map)
    with pytest.raises(SystemExit, match="abnormally"):
        L.selection_link([], "")

    def map_but_no_image(*a, **k):
        (tmp_path / "selected.map").write_text("A MAP")
        return "", 0, 0
    monkeypatch.setattr(L, "link", map_but_no_image)
    with pytest.raises(SystemExit, match="wrote no image"):
        L.selection_link([], "")


def valid_pe(sections=1, raw_end=0x400, signature=b"PE\0\0", machine=0x14C, optional=224, directories=16,
             headers=0x200, pointer=0x200):
    """A structurally valid PE32 image (the control), with each field a negative fixture can break."""
    data = bytearray(0x400)
    data[0:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x40)
    data[0x40:0x44] = signature
    struct.pack_into("<HHIIIHH", data, 0x44, machine, sections, 0, 0, 0, optional, 0x102)
    opt = 0x58
    struct.pack_into("<H", data, opt, 0x10B)
    struct.pack_into("<II", data, opt + 32, 0x1000, 0x200)  # SectionAlignment, FileAlignment
    struct.pack_into("<II", data, opt + 56, 0x2000, headers)  # SizeOfImage, SizeOfHeaders
    struct.pack_into("<I", data, opt + 92, directories)
    table = opt + optional
    for index in range(sections):
        at = table + 40 * index
        data[at:at + 8] = b".text\0\0\0"
        struct.pack_into("<IIII", data, at + 8, 0x100, 0x1000, raw_end - pointer, pointer)
        struct.pack_into("<I", data, at + 36, 0x60000020)
    return bytes(data)


def test_only_a_complete_pe_image_is_a_link_output(tmp_path):
    # reviews of 3897870f3b and 5cae4bdffc: "MZ" alone, a 96-byte optional header declaring 16
    # directories, SizeOfHeaders past the file or short of the section table, and section data over
    # the headers all passed as the link's image
    cases = {"good": valid_pe(), "mz": b"MZ", "signature": valid_pe(signature=b"XX\0\0"),
             "machine": valid_pe(machine=0x8664), "section-past-end": valid_pe(raw_end=0x800),
             "directories": valid_pe(optional=96, directories=16, headers=0x200),
             "headers-past-file": valid_pe(headers=0x800),
             "headers-short": valid_pe(headers=0x100),
             "section-over-headers": valid_pe(pointer=0x100)}
    verdicts = {}
    for name, data in cases.items():
        path = tmp_path / f"{name}.exe"
        path.write_bytes(data)
        verdicts[name] = L.pe_defect(path)
    assert verdicts["good"] is None, verdicts["good"]
    assert all(verdicts[name] for name in cases if name != "good"), verdicts


def test_malformed_link_output_never_records_a_census(tmp_path, monkeypatch):
    import pytest
    monkeypatch.setattr(L, "OUT", tmp_path)
    monkeypatch.setattr(L, "ledger", lambda: [])
    monkeypatch.setattr(L, "objects", lambda rows: ([], []))
    monkeypatch.setattr(L, "comdat_conflicts", lambda objs: {})
    for broken in (valid_pe(optional=96, directories=16), valid_pe(headers=0x800), valid_pe(pointer=0x100), b"MZ"):
        def link(*a, _image=broken, **k):
            (tmp_path / "census.exe").write_bytes(_image)
            return "", 0, 0
        monkeypatch.setattr(L, "link", link)
        with pytest.raises(SystemExit, match="wrote no image"):
            L.main([])
        assert not (tmp_path / "census.json").exists()
    # the control links: a valid image and a clean exit record the census
    monkeypatch.setattr(L, "link", lambda *a, **k: ((tmp_path / "census.exe").write_bytes(valid_pe()), ("", 0, 0))[1])
    assert L.main([]) == 0 and (tmp_path / "census.json").exists()


def _ordered_ledger(monkeypatch):
    """Rows of four sources (one with two rows, lowest RVA not first)."""
    monkeypatch.setattr(L.build, "row_object", lambda row: Path("/o") / (Path(row["source"]).stem + ".obj"))
    monkeypatch.setattr(L.build, "obj_path", lambda source, member=None: Path("/o") / (Path(source).stem + ".obj"))
    return [{"name": "f1", "target_rva": "0x00003000", "source": "Code/z.cpp"},
            {"name": "g", "target_rva": "0x00005000", "source": "Code/a.cpp"},
            {"name": "f0", "target_rva": "0x00001000", "source": "Code/z.cpp"},
            {"name": "h", "target_rva": "0x00002000", "source": "Code/m.cpp"},
            {"name": "h2", "target_rva": "0x00002000", "source": "Code/b.cpp"}]  # an over-claimed address: tie


def test_link_order_is_retail_layout_not_ledger_order(monkeypatch):
    rows = _ordered_ledger(monkeypatch)
    # code by lowest retail RVA (tie by path); this repository has no data rows
    assert [obj.name for obj in L.link_order(rows)] == ["z.obj", "b.obj", "m.obj", "a.obj"]
    assert L.data_ledger() == []


def test_shuffling_the_ledger_changes_no_census_result(monkeypatch):
    import random
    rows = _ordered_ledger(monkeypatch)
    # one symbol with no retail address, whose kept copy link order decides,
    # and one judged by retail truth whose kept copy is the first unproven one
    facts = {"z.obj": ([("inl", "p", 5, None)], [], [], []),
             "b.obj": ([("inl", "q", 5, None), ("t", "u1", 5, "unknown")], [], [], []),
             "m.obj": ([("inl", "p", 5, None), ("t", "u2", 5, "unknown")], [], [], []),
             "a.obj": ([("t", "u1", 5, "unknown")], ["d0"], ["d1"], [])}

    def census(ledger_rows):
        present = L.link_order(ledger_rows)
        found = [facts[obj.name] for obj in present]
        losers = L.comdat_losers(present, ledger_rows, facts=found)
        owners = L.ledger_owners(ledger_rows, [])
        kept = {}  # link.exe keeps the first definition in link order
        for obj, (copies, strong, _, _) in zip(present, found):
            for name in strong + [copy[0] for copy in copies]:
                kept.setdefault(name, obj.name)
        return [obj.name for obj in present], dict(losers), L.selection_verdicts(present, found, owners, kept)

    expected = census(rows)
    assert expected[1] == {"b.obj": {"inl"}, "m.obj": {"t"}}
    generator = random.Random(7)
    for _ in range(20):
        shuffled = rows[:]
        generator.shuffle(shuffled)
        assert census(shuffled) == expected


def test_majority_never_decides_and_stlport_is_judged_like_any_name():
    # The rule this replaced kept the copy most objects compiled and exempted
    # STLport and the array helpers. Three wrong copies outvote one retail copy
    # under majority; under retail truth they lose, whatever the name.
    for name in ("?f@@YAXXZ", "??0?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ", "??_L@YGXPAXIHP6EX0@Z1@Z"):
        copies = [("a.obj", "bad", "wrong"), ("b.obj", "bad", "wrong"), ("c.obj", "bad", "wrong"),
                  ("d.obj", "good", "retail")]
        loses, rule = L.keep_rule(copies)
        assert rule == "retail" and loses == {"a.obj": True, "b.obj": True, "c.obj": True, "d.obj": False}, name
    assert not hasattr(L, "comdat_exempt")


def test_ledger_row_object_owns_its_name(monkeypatch):
    rows = _ordered_ledger(monkeypatch)
    owners = L.ledger_owners(rows, [])
    assert owners["f0"] == {"z.obj"} and owners["h2"] == {"b.obj"}
    scaffold = [{"name": "s", "target_rva": "0x00006000", "source": "Code/gen_asm/s.asm", "notes": "gen-dump"}]
    assert "s" not in L.ledger_owners(scaffold, [])  # a dump row claims no identity


def test_selected_second_definition_over_the_owner_blocks_its_callers():
    # legacy.obj defines d1 too, ahead of glob.obj (the ledger row's owner), and the link kept it
    present = [Path("/o/legacy.obj"), Path("/o/glob.obj"), Path("/o/caller.obj")]
    facts = [([], ["d1"], [], []), ([], ["d1"], [], []), ([], [], ["d1"], [])]
    owners = {"d1": {"glob.obj"}}
    results, _ = L.selection_verdicts(present, facts, owners, {"d1": "legacy.obj"})
    assert results["d1"] == "wrong"  # judge_selected: the kept definition is not the owner's
    results, _ = L.selection_verdicts(present, facts, owners, {"d1": "glob.obj"})
    assert results["d1"] == "ok"


def test_link_check_follows_alternatename_like_link_exe(monkeypatch):
    # 460 sources here alias a spelling onto a defined name with
    # /alternatename; link.exe applies every object's directive to the whole
    # link, so the census never sees the alias unresolved, nor may the preview.
    import link_check as C
    facts = {"def.obj": ([], ["?target@@YAXXZ"], [], []),
             "other.obj": ([], ["?t2@@YAXXZ"], [], []),
             "user.obj": ([], [], ["?alias@@YAXXZ", "?nowhere@@YAXXZ", "?a2@@YAXXZ"], [])}
    directives = {"def.obj": {}, "other.obj": {"?a2@@YAXXZ": "?t2@@YAXXZ"},
                  "user.obj": {"?alias@@YAXXZ": "?target@@YAXXZ", "?nowhere@@YAXXZ": "?missing@@YAXXZ"}}
    present = [Path(name) for name in facts]
    monkeypatch.setattr(L, "common_definitions", lambda obj: {})
    monkeypatch.setattr(C, "alternate_names", lambda obj: directives[obj.name])
    ix = C.index_tables(present, list(facts.values()), {"exceptions": {}, "owners": {}})
    ix["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    monkeypatch.setattr(L, "object_facts", lambda obj, truth=None: facts[obj.name])
    assert C.check_object(present[2], ix, None)["unresolved"] == ["?nowhere@@YAXXZ"]
    directives["other.obj"] = {}  # the other object drops its directive: the alias no longer resolves
    C.refresh(ix, [present[1]], None)
    assert C.check_object(present[2], ix, None)["unresolved"] == ["?a2@@YAXXZ", "?nowhere@@YAXXZ"]


def test_c_import_slot_is_looked_up_undecorated_first():
    # `__imp__exit` names MSVCR71's exit; `_exit` is a different import whose
    # slot the bare spelling would otherwise find first.
    t = truth(b"")
    t.slots["exit"].add(0x7BA608)
    t.slots["_exit"].add(0x7BA59C)
    assert t.addresses("__imp__exit", L.RetailTruth.DIR32) == {0x7BA608}
    assert t.addresses("__imp___exit", L.RetailTruth.DIR32) == {0x7BA59C}


def test_call_through_any_proven_thunk_of_its_import_is_retail():
    # Retail holds two `jmp [slot]` thunks for htonl; a call through the
    # second is the import's call, though symbols.csv's first pin names the other.
    image = bytearray(0x30)
    image[0x00:0x06] = b"\xff\x25" + struct.pack("<I", L.BASE + 0x9000)  # htonl, slot 1
    image[0x10:0x16] = b"\xff\x25" + struct.pack("<I", L.BASE + 0x9004)  # htonl, slot 2
    image[0x20:0x26] = b"\xff\x25" + struct.pack("<I", L.BASE + 0x9008)  # htons
    t = truth(image, pinned={"_htonl@4": {TEXT}})
    t.slots.update({"htonl": {0x9000, 0x9004}, "htons": {0x9008}})
    rows = [{"name": f"?ji_{a:08x}@@YAXXZ", "target_rva": hex(a), "notes": "gen-import;import=x"}
            for a in (TEXT, TEXT + 0x10, TEXT + 0x20)]
    t.import_thunks = t._import_thunks(rows)
    assert t.addresses("_htonl@4", L.RetailTruth.REL32) == {TEXT, TEXT + 0x10}
    assert t.addresses("_htons@4", L.RetailTruth.REL32) == {TEXT + 0x20}
    # never a DIR32 target or a body home
    assert t.addresses("_htonl@4", L.RetailTruth.DIR32) == {TEXT}
