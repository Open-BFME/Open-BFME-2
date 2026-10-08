#!/usr/bin/env python3
"""Unit tests for tools/wb_members.py on hand-written instruction streams; pytest."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import wb_members as wm  # noqa: E402


def insns(*lines):
    """[(address, size, mnemonic, operands)] from 'mnemonic operands' lines."""
    out = []
    for i, line in enumerate(lines):
        mnemonic, _, operands = line.partition(" ")
        out.append((0x1000 + i, 1, mnemonic, operands))
    return out


def pairs_for(condition, *code, slot=-4):
    item = wm.Assert("Foo::bar", condition, 0, len(code), None)
    return [(p.cls, p.member, p.offset, p.size)
            for p in wm.assert_pairs(item, insns(*code), slot, "Foo::bar@0x1000")]


def test_parse_mem():
    mem = wm.parse_mem("dword ptr [eax + ecx*4 + 0x10]")
    assert (mem.size, mem.base, mem.index, mem.disp) == ("dword", "eax", "ecx", 0x10)
    assert wm.parse_mem("byte ptr [ebp - 4]").disp == -4


def test_parse_refs_shapes():
    refs = wm.parse_refs("m_a != NULL && this->m_b.size() > 0 && (*this).isOk()")
    assert refs.members == [("m_a", "plain"), ("m_b", "method")]
    assert not refs.unsafe and not refs.simple
    assert wm.parse_refs("m_pos.x > 0").unsafe
    assert wm.parse_refs("m_owner.m_hWnd").unsafe
    assert wm.parse_refs("m_bits[m_index]").unsafe
    assert wm.parse_refs("obj->m_id == id").foreign == [("obj", "m_id")]
    assert not wm.parse_refs("p < m_a+m_b").simple


def test_single_member_pairs_with_reload():
    assert pairs_for("m_template != NULL",
                     "mov eax, dword ptr [ebp - 4]",
                     "cmp dword ptr [eax + 0x24], 0",
                     "jne 0x2000") == [("Foo", "m_template", 0x24, "dword")]


def test_two_members_pair_in_order():
    assert pairs_for("!m_a || !m_b",
                     "mov eax, dword ptr [ebp - 4]",
                     "movzx ecx, byte ptr [eax + 8]",
                     "test ecx, ecx",
                     "je 0x2000",
                     "mov edx, dword ptr [ebp - 4]",
                     "movzx eax, byte ptr [edx + 9]",
                     "test eax, eax",
                     "je 0x2000") == [("Foo", "m_a", 8, "byte"), ("Foo", "m_b", 9, "byte")]


def test_x87_reordered_operands_are_refused():
    assert pairs_for("m_low != m_high",
                     "mov ecx, dword ptr [ebp - 4]",
                     "mov edx, dword ptr [ebp - 4]",
                     "fld dword ptr [edx + 8]",
                     "fld dword ptr [ecx + 4]",
                     "fucompp ") == []


def test_extra_reload_is_refused():
    # A leaked statement touches another member: two reloads, one name.
    assert pairs_for("m_count < 5",
                     "mov eax, dword ptr [ebp - 4]",
                     "mov ecx, dword ptr [eax + 0x10]",
                     "mov edx, dword ptr [ebp - 4]",
                     "cmp dword ptr [edx + 0x14], 5") == []


def test_vtable_fetch_is_not_a_member():
    assert pairs_for("m_ptr != NULL && isReady()",
                     "mov eax, dword ptr [ebp - 4]",
                     "cmp dword ptr [eax + 0xc], 0",
                     "je 0x2000",
                     "mov ecx, dword ptr [ebp - 4]",
                     "mov edx, dword ptr [ecx]",
                     "mov ecx, dword ptr [ebp - 4]",
                     "call dword ptr [edx + 0x20]") == [("Foo", "m_ptr", 0xc, "dword")]


def test_inlined_method_on_member_is_refused():
    assert pairs_for("m_list.empty()",
                     "mov eax, dword ptr [ebp - 4]",
                     "cmp dword ptr [eax + 0x14], 0") == []
    assert pairs_for("m_list.empty()",
                     "mov ecx, dword ptr [ebp - 4]",
                     "add ecx, 0x10",
                     "call 0x3000") == [("Foo", "m_list", 0x10, "addr")]


def test_vtable_store_disp():
    data = bytes([0xC7, 0x40, 0x20, 0, 0, 0, 0, 0xC7, 0x00, 0, 0, 0, 0])
    assert wm.vtable_store_disp(data, 3) == 0x20
    assert wm.vtable_store_disp(data, 9) == 0


def test_this_delta():
    assert wm.this_delta([], {}) == 0
    assert wm.this_delta([[1, 0]], {1: 0x20}) == 0x20
    assert wm.this_delta([[1, 0], [2, 0]], {1: 0x20, 2: 0}) is None


def test_declaration_order_skips_uses():
    body = "Real getLow() { return m_low; }\nint m_type;\nReal m_low, m_high;\n"
    order = wm.declaration_order(body, ["m_low", "m_high", "m_type"])
    assert order["m_type"] < order["m_low"] < order["m_high"]
