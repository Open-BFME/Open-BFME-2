"""family_scan scope: default stays gen_asm-only, --wide adds heuristic leads.

The default pool is hand-cut dump rows (Code/gen_asm/). The opt-in --wide pool
is Ghidra-inventory starts free of ledger overlap -- inventory-derived
heuristic leads carrying no identity. These tests pin both sides: default
never consults the inventory, and --wide never serves raw gaps,
ledger-overlapped extents, pins, Unwind residue, stale extents, undecodable
extents, or byte-lookalike terminals. An abutting next start is same-source
corroboration, not independent proof: it never rescues a bad terminal, and
per-body identity AND extent verification still apply at conversion time.
"""
import csv
import io
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import family_scan


def test_local_static_filter_uses_bfme2_atexit():
    rva = 0x007AC6DD
    def call_to(target):
        return b"\xe8" + (target - rva - 5).to_bytes(4, "little", signed=True) + b"\xc3"
    assert family_scan.registers_a_local_static(call_to(0x006291F8), rva)
    assert not family_scan.registers_a_local_static(call_to(0x009F6E26), rva)

RET = bytes.fromhex("33 c0 c3")                    # xor eax,eax; ret
RET4 = bytes.fromhex("8b 44 24 04 89 01 c2 04 00")  # ends C2 04 00, not a C3 byte
FAKE_RET = bytes.fromhex("b8 00 00 00 c3")          # mov eax,0xC3000000: ends in a C3 byte, no ret
PADDED = RET + b"\xcc\xcc\xcc" + RET                # stale extent spanning padding
# 10-byte fixtures: the scan's default --min-size 8 filters smaller bodies
# before any byte is read, so wide-path tests need in-range extents.
BIGRET = bytes.fromhex("55 8b ec 83 ec 08 33 c0 5d c3")  # frame; xor; pop; ret
FAKE8 = bytes.fromhex("55 8b ec c7 45 fc 00 00 00 c3")   # last INSN mov, last byte C3
PADDED8 = BIGRET + b"\xcc\xcc\xcc" + BIGRET
# mov eax,0xCCCCCC41 ; ret -- raw CC bytes live inside the immediate, so the
# legacy raw scan reads padding where the decoder sees one mov.
IMM_CC = bytes.fromhex("b8 41 cc cc cc c3")


def _md():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


@pytest.mark.parametrize("body", [
    bytes.fromhex("90 c3"),
    RET4,
    bytes.fromhex("90 e9 01 00 00 00"),
    bytes.fromhex("90 eb 01"),
    bytes.fromhex("90 ff e0"),
])
def test_decoded_terminal_accepts_real_returns_and_jumps(body):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    assert family_scan.ends_in_return_or_jump(body, md)


@pytest.mark.parametrize("body", [
    b"",
    FAKE_RET,                                  # last BYTE is C3, last INSN is mov
    bytes.fromhex("90 e8 00 00 00 00"),         # call is not a terminal jump
    bytes.fromhex("90 e9 01 00"),               # truncated near jump
    bytes.fromhex("c3 0f"),                     # ret followed by truncated insn
])
def test_decoded_terminal_rejects_lookalikes_and_truncation(body):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    assert not family_scan.ends_in_return_or_jump(body, md)


def test_interior_pad_run_flags_stale_extents_only():
    assert family_scan.has_interior_pad_run(PADDED, _md())
    assert not family_scan.has_interior_pad_run(RET, _md())          # no padding at all
    assert not family_scan.has_interior_pad_run(RET + b"\xcc", _md())  # trailing pad is the boundary


def test_decode_aware_pad_ignores_cc_inside_immediate():
    # The failure the raw scan owns: CC bytes inside mov's immediate are not
    # int3 instructions. Decode-aware detection must clear this body.
    assert family_scan.has_interior_pad_run(IMM_CC + b"\x90\x90\x90\x90", _md()) is False


def test_decode_aware_pad_keeps_real_int3_run():
    assert family_scan.has_interior_pad_run(PADDED8, _md()) is True
    assert family_scan.has_interior_pad_run(BIGRET + b"\xcc", _md()) is False  # trailing pad is the boundary


def test_undecodable_body_is_not_pad_proved():
    truncated = bytes.fromhex("90 e9 01 00")  # truncated near jump
    assert family_scan.has_interior_pad_run(truncated, _md()) is False
    assert family_scan.ends_in_return_or_jump(truncated, _md()) is False


def _normalize_ledger(ledger):
    """Accept legacy start-sets ({rva}) or interval maps ({rva: size})."""
    if ledger is None:
        return {}
    if isinstance(ledger, dict):
        return dict(ledger)
    return {rva: 1 for rva in ledger}


def _harness(monkeypatch, rows, inventory, argv, bodies, ledger=None):
    """Run main() with a fake ledger pool, fake inventory and fake image.

    ledger is {rva: size} (or a legacy set of starts, size 1): overlap is
    computed with the same whole-extent rule as ledger_overlapped_starts,
    adjacency allowed.
    """
    led = _normalize_ledger(ledger)
    inv = dict(inventory)
    corroborated = {r + s for r, (s, _n) in inv.items() if r + s in inv}
    monkeypatch.setattr(family_scan, "candidates", lambda *a: iter(rows))
    monkeypatch.setattr(family_scan, "load_wide_inventory",
                        lambda *a: (dict(inv), len(inv), set(corroborated)))
    def overlapped(cands):
        out = set()
        for s, (ssize, _n) in cands.items():
            for lva, lsize in led.items():
                if s < lva + lsize and lva < s + ssize:
                    out.add(s)
                    break
        return out
    monkeypatch.setattr(family_scan, "ledger_overlapped_starts", overlapped)
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: set())
    monkeypatch.setattr(family_scan, "load_attempted", lambda: (set(), set()))

    def read(rva, count):
        body = bodies[rva]
        assert count == len(body) + 1
        return body + b"\xcc"
    monkeypatch.setattr(family_scan.build, "read_target_bytes", read)
    monkeypatch.setattr(sys, "argv", ["family_scan.py"] + argv)


def test_default_scan_never_consults_inventory(monkeypatch, capsys):
    rows = [("first", 0x1000, len(RET)), ("second", 0x2000, len(RET))]

    def no_inventory(*a):
        raise AssertionError("default scan must not load the inventory")
    monkeypatch.setattr(family_scan, "candidates", lambda *a: iter(rows))
    monkeypatch.setattr(family_scan, "load_wide_inventory", no_inventory)
    monkeypatch.setattr(family_scan, "ledger_overlapped_starts", no_inventory)
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: set())
    monkeypatch.setattr(family_scan, "load_attempted", lambda: (set(), set()))
    monkeypatch.setattr(family_scan.build, "read_target_bytes",
                        lambda rva, count: RET + b"\xcc")
    monkeypatch.setattr(sys, "argv", ["family_scan.py"])
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 2" in out
    assert "unattempted rows reachable: 2" in out
    assert "wide pool" not in out


def test_wide_discovers_inventory_family(monkeypatch, capsys):
    inventory = {0x1000: (len(BIGRET), "FUN_00401000"),
                 0x2000: (len(BIGRET), "FUN_00402000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: BIGRET, 0x2000: BIGRET})
    family_scan.main()
    out = capsys.readouterr().out
    assert "wide pool: 2 inventory rows scanned, 2 heuristic leads offered" in out
    assert "unattempted rows reachable: 2" in out
    assert "0x00001000" in out


def test_wide_excludes_claimed_pinned_and_unwind(monkeypatch, capsys):
    inventory = {0x1000: (len(BIGRET), "FUN_00401000"),   # ledger-claimed
                 0x2000: (len(BIGRET), "FUN_00402000"),   # real-pinned
                 0x3000: (len(BIGRET), "Unwind_00403000"),  # compiler residue
                 0x4000: (len(BIGRET), "FUN_00404000"),
                 0x5000: (len(BIGRET), "FUN_00405000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x4000: BIGRET, 0x5000: BIGRET}, ledger={0x1000: len(BIGRET)})
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: {0x2000})
    family_scan.main()
    out = capsys.readouterr().out
    assert "wide pool: 5 inventory rows scanned, 2 heuristic leads offered" in out
    assert "unattempted rows reachable: 2" in out


def test_wide_excludes_interior_start_inside_claimed_interval(monkeypatch, capsys):
    # The start-only bug: 0x2005 was servable because no ledger row STARTED
    # there, even though ledger [0x2000, +32) covers it. Whole-extent overlap
    # must exclude it; adjacency (0x2020) stays servable.
    inventory = {0x2005: (len(BIGRET), "FUN_00402005"),
                 0x2020: (len(BIGRET), "FUN_00402020"),
                 0x4000: (len(BIGRET), "FUN_00404000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x2020: BIGRET, 0x4000: BIGRET}, ledger={0x2000: 32})
    family_scan.main()
    out = capsys.readouterr().out
    assert "heuristic leads offered" in out
    assert "2 heuristic leads offered" in out
    assert "unattempted rows reachable: 2" in out
    assert "0x00002005" not in out


def test_wide_excludes_crossing_extent_adjacency_allowed(monkeypatch, capsys):
    # Candidate [0x1000,0x100A) crosses ledger [0x1005,0x100F): excluded.
    # Candidate [0x2000,0x200A) starts exactly where ledger [0x1FF0,0x2000)
    # ends: adjacent, allowed.
    inventory = {0x1000: (len(BIGRET), "FUN_00401000"),
                 0x2000: (len(BIGRET), "FUN_00402000"),
                 0x3000: (len(BIGRET), "FUN_00403000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x2000: BIGRET, 0x3000: BIGRET},
             ledger={0x1005: 10, 0x1FF0: 16})
    family_scan.main()
    out = capsys.readouterr().out
    assert "2 heuristic leads offered" in out
    assert "0x00001000" not in out
    assert "unattempted rows reachable: 2" in out


def test_ledger_overlap_helper_marks_interior_and_crossing(monkeypatch, tmp_path):
    # Helper-level proof the window-filtered pass implements whole-extent
    # overlap (not start equality): interior start, crossing extent excluded;
    # both adjacencies allowed.
    (tmp_path / "reverse").mkdir()
    ghidra = tmp_path / "reverse" / "ghidra_functions.csv"
    ledger = tmp_path / "reverse" / "functions.csv"
    ghidra.write_text("rva,size,name\n")
    rows = ("name,export_rva,target_rva,target_size,source,status,notes\n"
            "hit,,0x00002000,32,Code/gen_asm/x.cpp,matched,\n"
            "cross,,0x00001005,10,Code/gen_asm/y.cpp,matched,\n"
            "before,,0x00001FF0,16,Code/gen_asm/z.cpp,matched,\n")
    ledger.write_text(rows)
    monkeypatch.setattr(family_scan, "ROOT", tmp_path)
    cands = {0x2005: (10, "FUN_1"),   # interior of [0x2000,+32)
             0x1000: (10, "FUN_2"),   # crosses [0x1005,+10)
             0x2020: (10, "FUN_3"),   # adjacent to [0x2000,+32)
             0x2000: (10, "FUN_4")}   # adjacent start is still overlap: shares [0x2000,0x200A)
    got = family_scan.ledger_overlapped_starts(cands)
    assert 0x2005 in got
    assert 0x1000 in got
    assert 0x2020 not in got
    assert 0x2000 in got


def test_inventory_loading_retains_only_eligible(monkeypatch, tmp_path):
    # AGENTS forbids wholesale loads: with size filters only in-range rows
    # are retained, while the total rows offered is still counted.
    (tmp_path / "reverse").mkdir()
    ghidra = tmp_path / "reverse" / "ghidra_functions.csv"
    ghidra.write_text("rva,size,name\n"
                      "0x1000,10,FUN_A\n"
                      "0x2000,3,FUN_TINY\n"
                      "0x3000,500,FUN_HUGE\n"
                      "0x4000,12,FUN_B\n")
    (tmp_path / "reverse" / "functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n")
    monkeypatch.setattr(family_scan, "ROOT", tmp_path)
    cands, total, corroborated = family_scan.load_wide_inventory(8, 160)
    assert total == 4
    assert set(cands) == {0x1000, 0x4000}
    assert corroborated == set()  # no end lands on another start here


def test_wide_rejects_byte_lookalike_terminal(monkeypatch, capsys):
    # The default last-byte test would ACCEPT this (ends in 0xC3); the wide
    # decoded-terminal test must not.
    inventory = {0x1000: (len(FAKE8), "FUN_00401000"),
                 0x2000: (len(FAKE8), "FUN_00402000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: FAKE8, 0x2000: FAKE8})
    family_scan.main()
    assert "bodies scanned: 0" in capsys.readouterr().out


def test_abutment_never_rescues_bad_terminal(monkeypatch, capsys):
    # Same-source corroboration is not proof: an abutting next start must not
    # rescue a body whose final DECODED instruction is not a ret/jmp.
    first, second = 0x1000, 0x1000 + len(FAKE8)
    inventory = {first: (len(FAKE8), "FUN_00401000"),
                 second: (len(BIGRET), "FUN_00401008")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {first: FAKE8, second: BIGRET})
    monkeypatch.setattr(family_scan.build, "read_target_bytes",
                        lambda rva, count: (FAKE8 + BIGRET + b"\xcc")[rva - first:rva - first + count])
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 1" in out  # only the abutting neighbour survives


def test_wide_accepts_ret_cleanup_invisible_to_raw_check(monkeypatch, capsys):
    # `ret 4` ends in 0x00, so the default last-byte test can never see this
    # shape; the wide path must, via the decoded terminal.
    inventory = {0x1000: (len(RET4), "FUN_00401000"),
                 0x2000: (len(RET4), "FUN_00402000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: RET4, 0x2000: RET4})
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 2" in out
    assert "unattempted rows reachable: 2" in out


def test_wide_refuses_extent_spanning_padding(monkeypatch, capsys):
    inventory = {0x1000: (len(PADDED8), "FUN_00401000"),
                 0x2000: (len(PADDED8), "FUN_00402000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: PADDED8, 0x2000: PADDED8})
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 0" in out
    assert "stale (decoded interior int3 run): 2" in out


def test_wide_serves_cc_immediate_body_without_stale_refusal(monkeypatch, capsys):
    # End-to-end regression for the decode-aware fix: a body carrying CC
    # bytes inside an immediate must not be refused as spanning padding.
    body = IMM_CC + b"\x90\x90\x90\x90"  # 10B, ends mid-nops: terminal refuses
    inventory = {0x1000: (len(body), "FUN_00401000"),
                 0x2000: (len(body), "FUN_00402000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: body, 0x2000: body})
    family_scan.main()
    out = capsys.readouterr().out
    assert "stale (decoded interior int3 run): 0" in out


def test_refuted_shape_still_kills_the_family(monkeypatch, capsys):
    rows = [("a", 0x1000, len(RET)), ("b", 0x2000, len(RET)),
            ("c", 0x3000, len(RET))]
    monkeypatch.setattr(family_scan, "candidates", lambda *a: iter(rows))
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: set())
    monkeypatch.setattr(family_scan, "load_attempted",
                        lambda: (set(), {0x1000}))
    monkeypatch.setattr(family_scan.build, "read_target_bytes",
                        lambda rva, count: RET + b"\xcc")
    monkeypatch.setattr(sys, "argv", ["family_scan.py"])
    family_scan.main()
    out = capsys.readouterr().out
    assert "refuted/blocked shapes: 1" in out
    assert "unattempted rows reachable: 0" in out


def test_wide_never_serves_raw_gaps():
    inventory = {0x1000: (3, "FUN_00401000")}
    got = list(family_scan.wide_candidates(8, 160, set(), set(), inventory))
    assert [rva for _, rva, _ in got] == []
    inventory = {0x1000: (len(BIGRET), "FUN_00401000")}
    got = list(family_scan.wide_candidates(8, 160, set(), set(), inventory))
    assert [rva for _, rva, _ in got] == [0x1000]  # the start, never 0x1001+


def test_wide_accepts_abutting_next_start(monkeypatch, capsys):
    # No padding between the bodies: the inventory abuts the next function
    # against this one, which corroborates the extent end (same-source, not
    # independent proof -- the decoded terminal is still required).
    first, second = 0x1000, 0x1000 + len(BIGRET)
    inventory = {first: (len(BIGRET), "FUN_00401000"),
                 second: (len(BIGRET), "FUN_0040100A")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"], {})
    # Retail bytes: the two bodies adjacent, padding only after the second.
    image = BIGRET + BIGRET + b"\xcc"
    monkeypatch.setattr(family_scan.build, "read_target_bytes",
                        lambda rva, count: image[rva - first:rva - first + count])
    monkeypatch.setattr(sys, "argv", ["family_scan.py", "--wide", "--exact"])
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 2" in out
    assert "unattempted rows reachable: 2" in out


def test_wide_refuses_code_after_without_next_start(monkeypatch, capsys):
    # Code follows the extent but nothing says a function starts there: the
    # end is uncorroborated, so the body is refused, not guessed.
    inventory = {0x1000: (len(BIGRET), "FUN_00401000")}
    _harness(monkeypatch, [], inventory, ["--wide", "--exact"],
             {0x1000: BIGRET})
    monkeypatch.setattr(family_scan.build, "read_target_bytes",
                        lambda rva, count: BIGRET + b"\x55")
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 0" in out
    assert "uncorroborated ends: 1" in out
