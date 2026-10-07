"""Boundary evidence must describe instructions, not opcode-looking operands."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from gen_dump import defensible_end


def accepted(body, rva=0x1001):
    return defensible_end(body, rva, len(body), set(), lambda _: 0x55)


@pytest.mark.parametrize("rva,hex_body", [
    (0x52C72B, "558bec83ec0c53568bf18b46102b460c57bfb8000000998bcff7f98365f80085c076478365fc008b4e0c034dfc8d45f450e891860300ff75088bc8e86ba2adff8bd8f7db1adb8d4df4fec3e8959cb0ff84db751f8b46102b460c8bcf99f7f9ff45f8017dfc3945f872bd32c05f5e5bc9c20400b001ebf5"),
    (0x3F088C, "8b81740100002b81700100005633f6c1f80257742a8b81700100008bd08b3a8b7f183b7c240c741e8bb9740100002bb97001000046c1ff0283c2043bf772de33c05f5ec204008b04b0ebf6"),
    (0x5CD8A5, "568bf18b0df0eddf008b01ff907c01000084c075348b460885c0742f50e87affffff84c05974248b4e08e8ecf2ffff8b4e08e8d4f2ffffff7608e893ffffffff7608e827ffffff59595ec38b0e8b015eff20"),
])
def test_recorded_retail_false_rejections(rva, hex_body):
    # Full recorded bodies: two back-edges to shared RET epilogues and a
    # virtual tail jump after restoring ESI. No next-start/padding shortcut.
    assert accepted(bytes.fromhex(hex_body), rva)


@pytest.mark.parametrize("hex_body", [
    "c3", "c20400", "ebfe", "e9fbffffff", "ff20", "ff6004",
    "ff2500000000", "e800000000", "ff1500000000",
])
def test_complete_terminal_instructions(hex_body):
    assert accepted(bytes.fromhex(hex_body))


@pytest.mark.parametrize("hex_body", [
    "b8000000c3", "b8000000eb", "b8000000e9",  # MOV immediate, not RET/JMP
    "b80000c204", "b8e8000000", "b8ff000000",  # operands resemble old suffix tests
    "eb", "e9000000", "ff150000", "c204",     # truncated instructions
    "e800fdffff5e5d5b5f83", "e8ffffffff5f5e5d5b81", "33d05f5e8bc2c1e8",
    "c390ebfd",                               # unreachable terminal jump
    "7501b8909090c3",                          # branch into MOV's immediate
    "e922000000", "e900000000",              # unproven external continuation
])
def test_false_or_truncated_terminal_evidence(hex_body):
    assert not accepted(bytes.fromhex(hex_body))


def test_existing_independent_next_boundary_evidence():
    body = bytes.fromhex("33c0")
    assert defensible_end(body, 0x1001, 2, {0x1003}, lambda _: 0x55)
    assert defensible_end(body, 0x1001, 2, set(), lambda _: 0xCC)
    assert defensible_end(body, 0x100E, 2, set(), lambda _: 0x55)


def test_switch_cases_after_an_indirect_table_jump():
    # External table: CFG traversal cannot visit the cases, but the complete
    # linear instruction stream still establishes the final RET boundary.
    assert accepted(bytes.fromhex("ff24850020000033c0c3"))
    assert not accepted(bytes.fromhex("ff248500200000b8000000c3"))


def test_external_tail_jump_requires_an_independent_callee_start():
    body = bytes.fromhex("e9fa0f0000")  # 0x1001 -> 0x2000
    assert not accepted(body)
    assert defensible_end(body, 0x1001, len(body), {0x2000}, lambda _: 0x55)
    assert not accepted(bytes.fromhex("ff248500200000e922000000"))
