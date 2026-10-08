"""What the cross-image matcher may explain away, and what it must refuse.

The sweep has no relocation table to consult -- both retail images ship with
the .reloc directory stripped -- so it decides which bytes two different builds
are allowed to disagree on by reading the instruction stream. That judgement is
the whole tool: over-explain and it invents matches out of coincidental byte
runs, under-explain and every real donor is rejected for the call displacement
it was always going to have.

The images are built as real PE32 files rather than mocked, because section
bounds are what `in_image` and `in_text` answer with, and a stub that returned
True would test nothing.
"""
import struct
import sys
from types import SimpleNamespace
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import bfme1_sweep


@pytest.mark.parametrize("raw", [b"name,address,notes\r\n", b"name,address,notes\n?old,0x1000,\r\n"])
def test_land_rejects_non_lf_pins_before_copying_or_staging(tmp_path, monkeypatch, raw):
    source = "game/GameEngine/Source/MockDonor.cpp"
    donor_root = tmp_path / "reference" / "bfme1"
    donor = donor_root / source
    donor.parent.mkdir(parents=True)
    donor.write_text("int donor() { return 1; }\n")
    symbols = tmp_path / "symbols.csv"
    symbols.write_bytes(raw)
    monkeypatch.setattr(bfme1_sweep, "ROOT", tmp_path)
    monkeypatch.setattr(bfme1_sweep, "BFME1", donor_root)
    monkeypatch.setattr(bfme1_sweep, "BFME2_SYMBOLS", symbols)
    monkeypatch.setattr(bfme1_sweep.subprocess, "run",
                        lambda *a, **k: pytest.fail("staged or built before LF preflight"))
    entry = {"source": source, "copy_tier": "A", "copy_note": "clean donor",
             "policy": "available", "bodies": [
                 {"tier": "T1", "name": "?donor@@YAHXZ", "bfme2_rva": 0x1000,
                  "size": 6, "pins": [("?callee@@YAXXZ", 0x2000)]}]}
    args = SimpleNamespace(allow_icf=False, ignore_import_alias=False, dry_run=False)
    with pytest.raises(SystemExit, match="LF|mixed line"):
        bfme1_sweep._do_land(args, entry)
    assert symbols.read_bytes() == raw
    assert not (tmp_path / bfme1_sweep.bfme2_source_path(source)).exists()


IMAGE_BASE = 0x00400000
TEXT_RVA = 0x1000


def make_pe(text, rdata=b"", image_size=0x100000):
    """A PE32 with one code section and one data section, nothing else."""
    headers = bytearray(0x400)
    headers[0:2] = b"MZ"
    pe = 0x80
    struct.pack_into("<I", headers, 0x3C, pe)
    headers[pe : pe + 4] = b"PE\0\0"
    coff = pe + 4
    optional_size = 0xE0
    struct.pack_into("<HHIIIHH", headers, coff, 0x014C, 2, 0, 0, 0, optional_size, 0x0102)
    optional = coff + 20
    struct.pack_into("<H", headers, optional, 0x010B)
    struct.pack_into("<I", headers, optional + 28, IMAGE_BASE)
    struct.pack_into("<I", headers, optional + 56, image_size)

    rdata_rva = TEXT_RVA + max(0x1000, (len(text) + 0xFFF) & ~0xFFF)
    table = coff + 20 + optional_size
    for index, (name, rva, payload, pointer) in enumerate(
            [(b".text", TEXT_RVA, text, 0x400),
             (b".rdata", rdata_rva, rdata, 0x400 + len(text))]):
        offset = table + index * 40
        headers[offset : offset + 8] = name.ljust(8, b"\0")
        struct.pack_into("<IIII", headers, offset + 8, len(payload), rva, len(payload), pointer)
        struct.pack_into("<I", headers, offset + 36, 0x60000020 if index == 0 else 0x40000040)
    return bytes(headers) + text + rdata


def donor_side(donor, size):
    """(body, fields, comparable runs) -- what `explain` derives once per donor."""
    body = donor.text[:size]
    fields = bfme1_sweep.volatile_fields(body, donor)
    return body, fields, bfme1_sweep.clear_runs(bfme1_sweep.mask_from(fields, size))


def image(tmp_path, name, text, rdata=b""):
    path = tmp_path / name
    path.write_bytes(make_pe(text, rdata))
    return bfme1_sweep.Image(path)


# `mov eax, <dir32>` then `call <rel32>` then `ret`, with a two-byte tail so the
# body has an unmasked run long enough to be a needle.
def body(dir32, rel32, tail=b"\x33\xC0\x8B\xFF\x5D\xC3"):
    return b"\xB8" + struct.pack("<I", dir32) + b"\xE8" + struct.pack("<i", rel32) + tail


def test_mask_covers_the_call_displacement_and_the_address_operand(tmp_path):
    donor = image(tmp_path, "a.exe", body(IMAGE_BASE + 0x2000, 0x40).ljust(0x200, b"\xCC"))
    mask = bfme1_sweep.volatile_mask(donor.text[: len(body(0, 0))], donor)
    assert mask[1:5] == b"\1" * 4, "the mov's absolute operand must be masked"
    assert mask[6:10] == b"\1" * 4, "the call's displacement must be masked"
    assert not any(mask[10:]), "the tail holds no relocation and must stay comparable"


def test_mask_does_not_open_a_second_field_inside_a_displacement(tmp_path):
    """A displacement byte that reads as 0xE8 must not start another rel32."""
    text = (b"\xE8" + struct.pack("<i", 0xE8) + b"\x90" * 16).ljust(0x200, b"\xCC")
    donor = image(tmp_path, "a.exe", text)
    mask = bfme1_sweep.volatile_mask(donor.text[:21], donor)
    assert mask[1:5] == b"\1" * 4
    assert not any(mask[5:]), "the walk must step over the field it just claimed"


def test_explain_accepts_a_body_differing_only_in_its_relocations(tmp_path):
    donor_text = body(IMAGE_BASE + 0x2000, 0x40).ljust(0x200, b"\xCC")
    target_text = body(IMAGE_BASE + 0x5000, 0x80).ljust(0x200, b"\xCC")
    donor = image(tmp_path, "a.exe", donor_text)
    target = image(tmp_path, "b.exe", target_text)
    size = len(body(0, 0))
    unexplained, dir32, rel32 = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert unexplained == 0
    assert [slot for slot, _, _ in dir32] == [1]
    assert [slot for slot, _, _ in rel32] == [6]
    assert rel32[0][1] == TEXT_RVA + 10 + 0x40
    assert rel32[0][2] == TEXT_RVA + 10 + 0x80


def test_explain_refuses_a_changed_opcode(tmp_path):
    donor_text = body(IMAGE_BASE + 0x2000, 0x40).ljust(0x200, b"\xCC")
    target_text = bytearray(donor_text)
    target_text[10] = 0x40             # xor eax,eax -> inc eax: a real difference
    donor = image(tmp_path, "a.exe", donor_text)
    target = image(tmp_path, "b.exe", bytes(target_text))
    size = len(body(0, 0))
    unexplained, _, _ = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert unexplained == 1, "one unexplained byte must reject the placement"


def test_explain_refuses_an_absolute_operand_that_leaves_the_image(tmp_path):
    """A dword is only a DIR32 when it addresses BOTH images; a literal that
    happens to look like an address on one side is not a licence to ignore it."""
    donor_text = body(IMAGE_BASE + 0x2000, 0x40).ljust(0x200, b"\xCC")
    target_text = body(0x7FFFFFFF, 0x40).ljust(0x200, b"\xCC")
    donor = image(tmp_path, "a.exe", donor_text)
    target = image(tmp_path, "b.exe", target_text)
    size = len(body(0, 0))
    unexplained, dir32, _ = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert dir32 == []
    assert unexplained > 0


def test_explain_refuses_a_call_leaving_text(tmp_path):
    donor_text = body(IMAGE_BASE + 0x2000, 0x40).ljust(0x200, b"\xCC")
    target_text = body(IMAGE_BASE + 0x2000, 0x7000).ljust(0x200, b"\xCC")
    donor = image(tmp_path, "a.exe", donor_text)
    target = image(tmp_path, "b.exe", target_text)
    size = len(body(0, 0))
    unexplained, _, rel32 = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert rel32 == [], "a displacement landing outside .text is not a call"
    assert unexplained > 0


def test_clear_runs_returns_longest_first():
    mask = bytes([0, 0, 1, 0, 0, 0, 0, 1, 0])
    assert bfme1_sweep.clear_runs(mask) == [(3, 4), (0, 2), (8, 1)]


def test_occurrences_is_uncapped_by_default():
    haystack = b"abab" * 10
    assert len(bfme1_sweep.occurrences(haystack, b"abab")) > 2
    assert len(bfme1_sweep.occurrences(haystack, b"abab", cap=2)) == 2


def test_cstring_refuses_binary_and_short_runs(tmp_path):
    rdata = b"Brightness\0\x01\x02\0ab\0"
    pe = image(tmp_path, "a.exe", b"\x90" * 0x100, rdata)
    base = IMAGE_BASE + pe.sections[1]["rva"]
    assert pe.cstring(base) == b"Brightness"
    assert pe.cstring(base + 11) is None, "non-printable bytes are not a string"
    assert pe.cstring(base + 14) is None, "a two-character run is not evidence"


class FakeClaims:
    def __init__(self, names=(), addresses=None, covering=None):
        self.names = set(names)
        self.addresses = dict(addresses or {})
        self._covering = covering

    def covering(self, rva, size):
        return self._covering


def record(**overrides):
    base = {
        "name": "?fn@@QAEXXZ", "source": "Code/GameEngine/Source/Common/X.cpp",
        "bfme1_rva": 0x900000, "size": 64, "bfme2_rva": 0x500000,
        "fanout": 1, "icf_twins": [],
        "needle": 20, "strings": [], "calls": [],
    }
    base.update(overrides)
    return base


def test_tier_string_conflict_outranks_a_clean_body():
    tier, reasons, _ = bfme1_sweep.body_tier(
        record(strings=[{"offset": 1, "bfme1": "Brightness", "bfme2": "Gamma", "agree": False}]),
        FakeClaims(), {})
    assert tier == "T4"
    assert "DIR32 string differs" in reasons[0]


def test_tier_pins_needed_is_t2_and_hands_back_the_pin_line():
    tier, reasons, pins = bfme1_sweep.body_tier(
        record(calls=[{"offset": 6, "bfme1_target": 1, "bfme2_target": 0x501234,
                       "bfme1_names": ["?callee@@YAXXZ"]}]),
        FakeClaims(), {})
    assert tier == "T2"
    assert "1 symbols.csv pin(s) needed" in reasons
    assert pins == [("?callee@@YAXXZ", 0x501234)]


def test_tier_treats_an_already_pinned_callee_as_resolved():
    """A scan is minutes stale by the time its work is served, so a pin that
    landed in between must count and take the body out of the pin tier."""
    tier, _, pins = bfme1_sweep.body_tier(
        record(calls=[{"offset": 6, "bfme1_target": 1, "bfme2_target": 0x501234,
                       "bfme1_names": ["?callee@@YAXXZ"]}]),
        FakeClaims(), {"?callee@@YAXXZ": 0x501234})
    assert tier == "T1"
    assert pins == []


def test_tier_refuses_a_callee_the_ledger_places_elsewhere():
    """A matched row disagreeing with the call site is the same finding as a
    contradicting pin, and must be caught even though the name resolves."""
    tier, reasons, _ = bfme1_sweep.body_tier(
        record(calls=[{"offset": 6, "bfme1_target": 1, "bfme2_target": 0x501234,
                       "bfme1_names": ["?callee@@YAXXZ"]}]),
        FakeClaims({"?callee@@YAXXZ"}, {"?callee@@YAXXZ": 0x777777}), {})
    assert tier == "T4"
    assert "0x00777777" in reasons[0]


def test_tier_refuses_a_callee_symbols_csv_pins_elsewhere():
    """Two images disagreeing about where a callee lives is evidence against
    the placement, not a pin to paste over the existing one."""
    tier, reasons, _ = bfme1_sweep.body_tier(
        record(calls=[{"offset": 6, "bfme1_target": 1, "bfme2_target": 0x501234,
                       "bfme1_names": ["?callee@@YAXXZ"]}]),
        FakeClaims(), {"?callee@@YAXXZ": 0x999999})
    assert tier == "T4"
    assert "0x00999999" in reasons[0] and "0x00501234" in reasons[0]


def test_tier_icf_fanout_is_t3_even_with_no_pins():
    tier, reasons, pins = bfme1_sweep.body_tier(record(fanout=3), FakeClaims(), {})
    assert pins == []
    assert tier == "T3"
    assert "ICF-folded" in reasons[0]


def test_tier_refuses_a_name_this_repo_already_spends():
    tier, reasons, _ = bfme1_sweep.body_tier(record(), FakeClaims({"?fn@@QAEXXZ"}), {})
    assert tier == "T4"
    assert "already spends that name" in reasons[0]


def test_tier_clean_body_is_t1_and_cites_its_strings():
    tier, reasons, _ = bfme1_sweep.body_tier(
        record(strings=[{"offset": 1, "bfme1": "Brightness", "bfme2": "Brightness", "agree": True}]),
        FakeClaims(), {})
    assert tier == "T1"
    assert "1 DIR32 string literal(s) agree" in reasons


def test_policy_holds_nbench_out():
    verdict, reason = bfme1_sweep.policy("Code/Libraries/Source/Benchmark/nbench1.cpp")
    assert verdict == "refused"
    assert "no permission grant" in reason
    assert bfme1_sweep.policy("Code/GameEngine/Source/Common/X.cpp")[0] == "ok"


def test_packet_names_every_step_a_lander_needs():
    entry = {
        "source": "Code/GameEngine/Source/Common/X.cpp", "copy_tier": "A",
        "copy_note": "self-contained", "cl": "/O2 /Ob0", "stlport": False,
        "policy": "ok", "policy_note": "", "bytes": 64, "best_tier": "T2",
        "bodies": [dict(record(), tier="T2", reasons=["1 symbols.csv pin(s) needed"],
                        pins=[("?callee@@YAXXZ", 0x501234)])],
        "held": [],
    }
    text = bfme1_sweep.packet_text(entry)
    assert "reference/open-bfme-1/Code/GameEngine/Source/Common/X.cpp" in text
    assert "?callee@@YAXXZ,0x00501234" in text
    assert "tools/pin_consistency.py --symbol '?callee@@YAXXZ'" in text
    assert "tools/add_match.py '?fn@@QAEXXZ' 0x00500000 64" in text
    assert "./build.sh Code/GameEngine/Source/Common/X.cpp" in text
    assert "tools/re_log.py record" in text


def test_claims_finds_a_long_body_that_starts_before_a_shorter_one():
    """A short row can sit between the query and the long row that spans it.
    Walking back only to the first non-overlapping row would return None."""
    claims = bfme1_sweep.Claims([
        (0x1000, 0x800, "?long@@YAXXZ", "Code/a.cpp", ""),
        (0x1900, 0x10, "?short@@YAXXZ", "Code/b.cpp", ""),
    ])
    assert claims.covering(0x1700, 8)[2] == "?long@@YAXXZ"
    assert claims.covering(0x1900, 8)[2] == "?short@@YAXXZ"
    assert claims.covering(0x2000, 8) is None
    assert claims.covering(0x0F00, 8) is None


def test_tier_refuses_an_address_the_ledger_already_covers():
    """Claim state is read live, not cached from the scan, so a row that landed
    since must take the address off the queue."""
    tier, reasons, _ = bfme1_sweep.body_tier(
        record(), FakeClaims(covering=(0x500000, 64, "?other@@YAXXZ", "Code/z.cpp", "")), {})
    assert tier == "T4"
    assert "?other@@YAXXZ" in reasons[0]


def test_occurrences_reports_the_cap_so_a_truncated_search_reads_as_ambiguous():
    """The caller distinguishes "all of them" from "at least this many" by the
    count alone, so hitting the cap has to be visible in the return."""
    haystack = b"ab" * 50
    assert len(bfme1_sweep.occurrences(haystack, b"ab", cap=10)) == 10
    assert len(bfme1_sweep.occurrences(haystack, b"ab")) == 50


def test_tier_pins_every_name_bfme1_knows_for_one_callee():
    """A call reached through an ILT thunk in BFME 1 carries both the thunk's
    pinned name and the body's ledger name, and which one the donor object asks
    for depends on how its source declared the callee. Pin both."""
    tier, _, pins = bfme1_sweep.body_tier(
        record(calls=[{"offset": 6, "bfme1_target": 1, "bfme2_target": 0x501234,
                       "bfme1_names": ["?thunk@@YAXXZ", "?body@@YAXXZ"]}]),
        FakeClaims(), {})
    assert tier == "T2"
    assert pins == [("?body@@YAXXZ", 0x501234), ("?thunk@@YAXXZ", 0x501234)]


def test_ledger_note_carries_no_comma():
    """functions.csv is raw comma-joined with no quoting, so add_match refuses a
    note holding one; both the packet and `land` go through this."""
    note = bfme1_sweep.ledger_note(dict(record(
        strings=[{"offset": 1, "bfme1": "x", "bfme2": "x", "agree": True}]), tier="T3"))
    assert "," not in note
    assert "0x00900000" in note and "ICF-folded" in note and "1 DIR32" in note


# ---- commit-gate tiers: found by landing wave 1 into the hooks, not by reading them

def donor_tree(tmp_path, monkeypatch, files):
    """A fake submodule holding `files` {relative path: text}."""
    for relative, text in files.items():
        path = tmp_path / "bfme1" / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    monkeypatch.setattr(bfme1_sweep, "BFME1", tmp_path / "bfme1")
    monkeypatch.setattr(bfme1_sweep, "ROOT", tmp_path / "bfme2")
    (tmp_path / "bfme2").mkdir(exist_ok=True)


def test_copy_tier_holds_a_naked_lift(tmp_path, monkeypatch):
    """AGENTS.md: a lift is not a conversion, and conversion_gate refuses it."""
    donor_tree(tmp_path, monkeypatch, {
        "Code/GameEngine/Source/Common/X.cpp": "void __declspec(naked) f() { __asm { ret } }\n"})
    tier, note, _, _ = bfme1_sweep.copy_tier("Code/GameEngine/Source/Common/X.cpp")
    assert tier == "L" and "naked" in note


def test_copy_tier_holds_a_root_the_hook_does_not_allow(tmp_path, monkeypatch):
    """.githooks/pre-commit refused Code/stlport/ after the file had already built."""
    donor_tree(tmp_path, monkeypatch, {"Code/stlport/X.cpp": "int f() { return 1; }\n"})
    tier, note, _, _ = bfme1_sweep.copy_tier("Code/stlport/X.cpp")
    assert tier == "P" and "stlport" in note


def test_copy_tier_keeps_inline_asm_landable(tmp_path, monkeypatch):
    """Only naked/__emit is a lift; ordinary inline __asm is what the MMX donors use."""
    donor_tree(tmp_path, monkeypatch, {
        "Code/GameEngine/Source/Common/X.cpp": "void f() { __asm { emms } }\n"})
    assert bfme1_sweep.copy_tier("Code/GameEngine/Source/Common/X.cpp")[0] == "A"


def test_group_files_holds_a_donor_that_defines_unplaced_functions(tmp_path, monkeypatch):
    """The hook's find_declared_unmatched refuses a source with any function the
    ledger lacks, so a donor is only landable whole when everything it defines
    was placed -- not just the bodies the sweep found."""
    src = "Code/GameEngine/Source/Common/X.cpp"
    donor_tree(tmp_path, monkeypatch, {src: "int f() { return 1; }\n"})
    (tmp_path / "b1.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"?placed@@YAHXZ,,0x1000,32,{src},matched,\n"
        f"?tiny@@YAHXZ,,0x2000,7,{src},matched,\n")
    (tmp_path / "b2.csv").write_text("name,export_rva,target_rva,target_size,source,status,notes\n")
    (tmp_path / "sym.csv").write_text("name,address,notes\n")
    monkeypatch.setattr(bfme1_sweep, "BFME1_LEDGER", tmp_path / "b1.csv")
    monkeypatch.setattr(bfme1_sweep, "BFME2_LEDGER", tmp_path / "b2.csv")
    monkeypatch.setattr(bfme1_sweep, "BFME2_SYMBOLS", tmp_path / "sym.csv")
    payload = {"records": [record(name="?placed@@YAHXZ", source=src, size=32)]}

    assert bfme1_sweep.group_files(payload) == [], "held by default"
    held = bfme1_sweep.group_files(payload, include_held=True)
    assert [(e["copy_tier"], len(e["bodies"])) for e in held] == [("S", 1)]
    assert "1 function(s)" in held[0]["copy_note"] and "?tiny@@YAHXZ" in held[0]["copy_note"]


def test_remove_rows_drops_only_the_named_source(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(b"name,export_rva,target_rva,target_size,source,status,notes\n"
                       b"?a@@YAXXZ,,0x1,8,Code/x.cpp,matched,\n"
                       b"?b@@YAXXZ,,0x2,8,Code/y.cpp,matched,\n"
                       b"?c@@YAXXZ,,0x3,8,Code/x.cpp,matched,\n")
    monkeypatch.setattr(bfme1_sweep, "BFME2_LEDGER", ledger)
    bfme1_sweep.remove_rows("Code/x.cpp")
    text = ledger.read_bytes().decode()
    assert "?b@@YAXXZ" in text and "?a@@YAXXZ" not in text and "?c@@YAXXZ" not in text
    assert b"\r" not in ledger.read_bytes(), "must keep canonical LF"


# ---- the donor's walk is authoritative about WHERE fields are

# A body whose DIR32 the TARGET's own forward walk never claims, because a
# differing field value made an earlier four-byte window read as an address and
# that window was claimed first. This is the LocaleCodePageQueries.c shape: one
# slot holding KERNEL32!GetLocaleInfoA on the donor side and the very same
# import on the target side, refused at 96-98% because the two walks disagreed
# about the offset. Requiring both sides to agree is what made that a near miss
# instead of the exact match it is.
WIDE_IMAGE = 0x1000000
_PREFIX = b"\x90\x90\x90\x90\xB8"          # nops then `mov eax, <dir32>`
_TAIL = b"\x33\xC0\xC3" + b"\x90" * 8
DIVERGENT_DONOR = _PREFIX + bytes([0x01, 0x10, 0x40, 0x00]) + _TAIL   # 0x00401001
DIVERGENT_TARGET = _PREFIX + bytes([0x01, 0x50, 0x00, 0x01]) + _TAIL  # 0x01005001


def wide_images(tmp_path):
    donor = tmp_path / "a.exe"
    donor.write_bytes(make_pe(DIVERGENT_DONOR.ljust(0x200, b"\xCC"), image_size=WIDE_IMAGE))
    target = tmp_path / "b.exe"
    target.write_bytes(make_pe(DIVERGENT_TARGET.ljust(0x200, b"\xCC"), image_size=WIDE_IMAGE))
    return bfme1_sweep.Image(donor), bfme1_sweep.Image(target)


def test_the_two_walks_really_do_disagree(tmp_path):
    """Guards the fixture: if this stops holding the next test proves nothing."""
    donor, target = wide_images(tmp_path)
    size = len(DIVERGENT_DONOR)
    assert bfme1_sweep.volatile_fields(donor.text[:size], donor) == {5: "dir32"}
    assert bfme1_sweep.volatile_fields(target.text[:size], target) == {4: "dir32"}


def test_explain_forgives_a_dir32_the_target_walk_did_not_claim(tmp_path):
    donor, target = wide_images(tmp_path)
    size = len(DIVERGENT_DONOR)
    unexplained, dir32, _ = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert unexplained == 0, "a DIR32 addressing both images is a relocation, not a difference"
    assert [slot for slot, _, _ in dir32] == [5]
    assert dir32[0][1] == 0x00401001 and dir32[0][2] == 0x01005001


def test_relaxation_does_not_forgive_a_value_outside_the_target_image(tmp_path):
    """The donor still decides where a field is; the target still has to hold
    something relocation-shaped there, or the bytes are ordinary code."""
    donor, _ = wide_images(tmp_path)
    stray = _PREFIX + bytes([0x01, 0x50, 0x00, 0x7F]) + _TAIL      # 0x7F005001: no image
    path = tmp_path / "c.exe"
    path.write_bytes(make_pe(stray.ljust(0x200, b"\xCC"), image_size=WIDE_IMAGE))
    target = bfme1_sweep.Image(path)
    size = len(DIVERGENT_DONOR)
    unexplained, dir32, _ = bfme1_sweep.explain(
        *donor_side(donor, size), target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert dir32 == []
    assert unexplained > 0


# ---- import-name pre-flight

def import_donor(tmp_path, monkeypatch, declaration):
    src = "Code/GameEngine/Source/Common/X.cpp"
    donor_tree(tmp_path, monkeypatch, {src: declaration})
    return src


def entry(name):
    from pe_imports import ImportEntry
    return ImportEntry("msvcr71.dll", name, None)


ALIASED = ('extern "C" __declspec(dllimport) void *__cdecl '
           't2_block_copy(void *dst, const void *src, unsigned int n);\n')


def test_import_alias_is_flagged_when_the_donor_invents_a_name(tmp_path, monkeypatch):
    """verify_import_refs reads the import at the slot the RETAIL body reaches
    and demands the source's COFF name match it, so an invented name can never
    be pinned -- it has to be renamed. Byte comparison cannot see this: each
    image holds a valid DIR32 into its own IAT."""
    src = import_donor(tmp_path, monkeypatch, ALIASED)
    note = bfme1_sweep.import_alias_note(src, [entry("memmove")])
    assert note and "t2_block_copy" in note and "memmove" in note
    assert "no pin can fix this" in note


def test_import_alias_is_silent_when_the_declaration_matches(tmp_path, monkeypatch):
    src = import_donor(tmp_path, monkeypatch, ALIASED)
    assert bfme1_sweep.import_alias_note(src, [entry("t2_block_copy")]) is None


def test_import_alias_accepts_the_underscore_spelling(tmp_path, monkeypatch):
    """An import library may publish the decorated or the undecorated name;
    coff_import_names is what arbitrates, so both must pass."""
    src = import_donor(tmp_path, monkeypatch,
                       'extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned);\n')
    assert bfme1_sweep.import_alias_note(src, [entry("memmove")]) is None


def test_import_alias_is_silent_without_a_dllimport_or_without_imports(tmp_path, monkeypatch):
    plain = import_donor(tmp_path, monkeypatch, "int f() { return 1; }\n")
    assert bfme1_sweep.import_alias_note(plain, [entry("memmove")]) is None
    src = import_donor(tmp_path, monkeypatch, ALIASED)
    assert bfme1_sweep.import_alias_note(src, []) is None


# ---- near misses: scoring, boundary evidence, and which classes are served

def test_alignment_ignores_relocation_slots(tmp_path):
    """A relocation is not a difference, so it must not drag the score down."""
    donor, target = wide_images(tmp_path)
    size = len(DIVERGENT_DONOR)
    body, fields, _ = donor_side(donor, size)
    assert bfme1_sweep.alignment(body, fields, target.text[:size]) == 1.0
    changed = bytearray(target.text[:size])
    changed[0] ^= 0xFF                       # a real difference, outside any field
    assert bfme1_sweep.alignment(body, fields, bytes(changed)) < 1.0


def test_boundaries_refuse_the_interior_of_a_known_function(tmp_path):
    """Positive evidence against: an address inside a known body cannot start one.
    'unknown' is not refused, it just is not corroboration."""
    path = tmp_path / "b.exe"
    path.write_bytes(make_pe(b"\x90" * 0x100 + b"\xcc\xcc\xcc" + b"\x90" * 0x100))
    image = bfme1_sweep.Image(path)
    boundaries = bfme1_sweep.Boundaries({TEXT_RVA: 64}, image)
    assert boundaries.evidence(TEXT_RVA) == "ghidra-start"
    assert boundaries.evidence(TEXT_RVA + 32) is None, "interior must be refused"
    assert boundaries.evidence(TEXT_RVA + 0x103) == "int3-padded"
    assert boundaries.evidence(TEXT_RVA + 0x80) == "unknown"


def test_classify_near_names_a_changed_literal(tmp_path):
    """The mechanical class: same shape, a literal moved. Here a struct field
    offset, which is the commonest real BFME1 -> BFME2 drift."""
    left = b"\xC7\x86\x58\x00\x00\x00\x00\x00\x00\x00\xC3"   # mov [esi+0x58],0
    right = b"\xC7\x86\x7C\x00\x00\x00\x00\x00\x00\x00\xC3"  # mov [esi+0x7c],0
    kind, hint = bfme1_sweep.classify_near(left, right, {}, tmp_path / "d")
    assert kind == "immediate-only", hint
    assert "0x58" in hint and "0x7c" in hint


def test_classify_near_separates_a_register_swap(tmp_path):
    left = b"\x8B\x08\xC3"                                   # mov ecx,[eax]
    right = b"\x8B\x10\xC3"                                  # mov edx,[eax]
    kind, _ = bfme1_sweep.classify_near(left, right, {}, tmp_path / "d")
    assert kind == "register-swap"
    assert kind not in bfme1_sweep.NEAR_SERVED, \
        "drift_classify records this as an MSVC-regalloc wall; it must not be queued"


def test_classify_near_calls_a_different_opcode_structural(tmp_path):
    left = b"\x8B\x08\xC3"                                   # mov ecx,[eax]
    right = b"\x03\x08\xC3"                                  # add ecx,[eax]
    kind, _ = bfme1_sweep.classify_near(left, right, {}, tmp_path / "d")
    assert kind == "structural"
    assert kind not in bfme1_sweep.NEAR_SERVED


def test_classify_near_masks_relocation_slots_before_comparing(tmp_path):
    """Two different addresses in a DIR32 must not read as a changed literal."""
    left = b"\xB8" + struct.pack("<I", 0x00401000) + b"\xC3"
    right = b"\xB8" + struct.pack("<I", 0x00502000) + b"\xC3"
    kind, hint = bfme1_sweep.classify_near(left, right, {1: "dir32"}, tmp_path / "d")
    assert kind != "immediate-only", f"a relocation is not a literal ({hint})"


def test_near_packet_says_it_will_not_byte_match_and_gives_the_diff():
    donor = b"\xC7\x86\x58\x00\x00\x00\x00\x00\x00\x00\xC3"
    window = b"\xC7\x86\x7C\x00\x00\x00\x00\x00\x00\x00\xC3"
    entry = {
        "name": "?fn@@QAEXXZ", "source": "Code/GameEngine/Source/Common/X.cpp",
        "bfme1_rva": 0x900000, "size": len(donor), "bfme2_rva": 0x500000,
        "alignment": 0.97, "boundary": "ghidra-start", "ghidra_size": len(donor),
        "klass": "immediate-only", "hint": "1 literal(s)", "copy_tier": "A",
        "copy_note": "self-contained", "cl": "/O2", "stlport": False,
        "policy": "ok", "policy_note": "", "donor": donor, "window": window, "fields": {},
    }
    text = bfme1_sweep.near_packet(entry)
    assert "WILL NOT BYTE-MATCH AS COPIED" in text
    assert "| +0x002 | 58 | 7C |" in text, "the differing byte must be shown"
    assert "same size" in text
    assert "tools/add_match.py '?fn@@QAEXXZ' 0x00500000" in text
    assert "re_log.py record" in text
    # A repaired near miss still has to resolve its call sites, and the first
    # one landed needed four pins the packet did not mention.
    assert "tools/decode_calls.py '?fn@@QAEXXZ' --rva 0x00500000" in text


def test_a_spurious_dir32_over_an_immediate_does_not_hide_the_difference(tmp_path):
    """`add ecx,0x120` is 81 C1 20 01 00 00, and the four-byte window at the
    modrm byte reads 0x0120C181 -- an address, so the DIR32 pass claims it.
    Masking that field would score this 100% against `add ecx,0x17c` and hide a
    struct offset that moved, which is exactly what the near tier is for."""
    donor_body = b"\x8D\x44\x24\x04\x50\x81\xC1\x20\x01\x00\x00\xC3"
    target_body = b"\x8D\x44\x24\x04\x50\x81\xC1\x7C\x01\x00\x00\xC3"
    # The straddling window is 0x0120C181, so the image has to be big enough to
    # contain it -- as both retail images are.
    (tmp_path / "a.exe").write_bytes(
        make_pe(donor_body.ljust(0x200, b"\xCC"), image_size=WIDE_IMAGE))
    (tmp_path / "b.exe").write_bytes(
        make_pe(target_body.ljust(0x200, b"\xCC"), image_size=WIDE_IMAGE))
    donor = bfme1_sweep.Image(tmp_path / "a.exe")
    target = bfme1_sweep.Image(tmp_path / "b.exe")
    size = len(donor_body)
    raw = bfme1_sweep.volatile_fields(donor.text[:size], donor)
    assert 5 in raw, "fixture guard: the straddling window must be claimed"

    agreed = bfme1_sweep.agreed_fields(
        donor.text[:size], raw, target.text[:size], TEXT_RVA, TEXT_RVA, donor, target)
    assert 5 not in agreed, "the target does not hold an address there, so it is not a field"
    assert bfme1_sweep.alignment(donor.text[:size], agreed, target.text[:size]) < 1.0

    kind, hint = bfme1_sweep.classify_near(
        donor.text[:size], target.text[:size], agreed, tmp_path / "d")
    assert kind == "immediate-only", hint
    assert "0x120" in hint and "0x17c" in hint


def test_classify_near_reports_reloc_value_when_masking_leaves_no_difference(tmp_path):
    """Identical once masked means every difference sat in a relocation slot.
    That is not a code difference and must not be mislabelled imm+reg."""
    left = b"\xB8" + struct.pack("<I", 0x00401000) + b"\xC3"
    right = b"\xB8" + struct.pack("<I", 0x00402000) + b"\xC3"
    kind, _ = bfme1_sweep.classify_near(left, right, {1: "dir32"}, tmp_path / "d")
    assert kind == "reloc-value"
    assert kind not in bfme1_sweep.NEAR_SERVED


# --------------------------------------------- E8 bytes that are not opcodes

# `mov DWORD PTR [eax],0x0040E8B8` -- a vftable store, which is how retail
# starts a constructor. Byte 3 of it reads E8, and the four bytes after that
# read as a displacement going nowhere. This is the shape that cost the sweep
# ??0__Named_exception (0x0082C180): the bogus rel32 claim blocked the DIR32
# window at the immediate, every later field shifted, and a body that is
# byte-identical to game.dat's scored 96.1% and was filed as a near miss.
VFTABLE_STORE = b"\xC7\x00\xB8\xE8\x40\x00" + b"\x90" * 10


def one_section_image(tmp_path, name, text):
    target = tmp_path / name
    target.write_bytes(make_pe(text.ljust(0x100, b"\x90")))
    return bfme1_sweep.Image(target)


def test_an_E8_inside_an_immediate_steals_the_dir32_without_an_rva(tmp_path):
    """Guards the fixture: without the target test the old claim still stands."""
    image = one_section_image(tmp_path, "a.exe", VFTABLE_STORE)
    body = image.text[: len(VFTABLE_STORE)]
    assert bfme1_sweep.volatile_fields(body, image) == {4: "rel32"}


def test_a_displacement_leaving_text_does_not_open_a_rel32(tmp_path):
    """Given the RVA, the walk reads the immediate as the relocation it is."""
    image = one_section_image(tmp_path, "b.exe", VFTABLE_STORE)
    body = image.text[: len(VFTABLE_STORE)]
    fields = bfme1_sweep.volatile_fields(body, image, TEXT_RVA)
    assert fields == {2: "dir32"}, "the vftable pointer is the field, not byte 4"


def test_a_real_call_is_still_claimed(tmp_path):
    """The test refuses displacements, not calls: one reaching .text stands."""
    call = b"\xE8" + struct.pack("<i", 0x10) + b"\x90" * 11
    image = one_section_image(tmp_path, "c.exe", call)
    body = image.text[: len(call)]
    assert bfme1_sweep.volatile_fields(body, image, TEXT_RVA) == {1: "rel32"}


# --------------------------------------------------------------- drain queue

def an_entry(**over):
    """A group_files entry with nothing wrong with it, for one field at a time."""
    entry = {"source": "Code/GameEngine/Source/Common/X.cpp", "copy_tier": "A",
             "policy": "ok", "import_alias": None,
             "bodies": [{"tier": "T1", "size": 120}]}
    entry.update(over)
    return entry


WANTED = ("T1", "T2")


def test_drain_takes_a_plain_served_file():
    assert bfme1_sweep.drainable(an_entry(), WANTED)


@pytest.mark.parametrize("over", [
    {"copy_tier": "S"}, {"copy_tier": "P"}, {"copy_tier": "L"},
    {"copy_tier": "D"}, {"policy": "refused"},
    {"import_alias": "donor declares t2_block_copy but the body reaches memmove"},
])
def test_drain_skips_what_land_would_refuse(over):
    """Every one of these raises SystemExit inside do_land; none should be queued."""
    assert not bfme1_sweep.drainable(an_entry(**over), WANTED)


def test_drain_skips_a_file_whose_only_body_is_an_icf_guess():
    entry = an_entry(bodies=[{"tier": "T3", "size": 120}])
    assert not bfme1_sweep.drainable(entry, WANTED)
    assert bfme1_sweep.drainable(entry, ("T1", "T2", "T3")), "--allow-icf takes it"


# ------------------------------------------------- the BFME1 -> BFME2 map

ANCHORS = [(0x1000, 0x5000), (0x1100, 0x5100), (0x2000, 0x9000), (0x2100, 0x9100)]
KEYS = [b1 for b1, _ in ANCHORS]


def test_the_map_interpolates_inside_a_transferred_region():
    """0x1000..0x1100 spans 0x100 on both sides, so the region moved whole."""
    assert bfme1_sweep.predict_bfme2(0x1080, ANCHORS, KEYS) == 0x5080


def test_the_map_declines_across_a_region_boundary():
    """0x1100..0x2000 spans 0xF00 in BFME 1 and 0x3F00 here: objects were dropped.

    Declining is the whole gate. Leave-one-out error across a boundary runs to
    megabytes, so an answer offered here would be worse than none.
    """
    assert bfme1_sweep.predict_bfme2(0x1800, ANCHORS, KEYS) is None


def test_the_map_declines_outside_its_anchors():
    assert bfme1_sweep.predict_bfme2(0x0500, ANCHORS, KEYS) is None
    assert bfme1_sweep.predict_bfme2(0x9999, ANCHORS, KEYS) is None


def ambiguous_payload(candidates):
    return {"records": [{"bfme1_rva": b1, "bfme2_rva": b2} for b1, b2 in ANCHORS],
            "ambiguous": [{"name": "?f@@YAXXZ", "source": "Code/GameEngine/Source/Common/X.cpp",
                           "bfme1_rva": 0x1080, "size": 48, "candidates": candidates}]}


def test_the_map_picks_the_candidate_it_predicted(monkeypatch):
    monkeypatch.setattr(bfme1_sweep, "Claims", lambda *a, **k: _NoClaims())
    monkeypatch.setattr(bfme1_sweep, "ledger_claims", lambda *a, **k: [])
    out = bfme1_sweep.resolve_ambiguous(ambiguous_payload([0x5080, 0x7000]))
    assert [r["bfme2_rva"] for r in out] == [0x5080]
    assert out[0]["error"] == 0


def test_a_tie_is_not_a_resolution(monkeypatch):
    """Two candidates inside the window is the same question, not an answer."""
    monkeypatch.setattr(bfme1_sweep, "Claims", lambda *a, **k: _NoClaims())
    monkeypatch.setattr(bfme1_sweep, "ledger_claims", lambda *a, **k: [])
    assert bfme1_sweep.resolve_ambiguous(ambiguous_payload([0x5080, 0x5090])) == []


class _NoClaims:
    names = frozenset()
    def covering(self, rva, size):
        return None
