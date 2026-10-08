#!/usr/bin/env python3
"""tools/wb_show.py: frame/this naming on synthetic code, macro collapsing on
the real WorldBuilder image (skipped when the baselines or build/wb inputs
are absent)."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import wb_show  # noqa: E402

PROLOGUE = [
    (0x10, 1, "push", "ebp"),
    (0x11, 2, "mov", "ebp, esp"),
    (0x13, 3, "sub", "esp, 0x1c"),
    (0x16, 3, "mov", "dword ptr [ebp - 8], ecx"),
]


def rewrite_all(insns):
    tracker = wb_show.ThisTracker(wb_show.Frame(insns))
    return [tracker.rewrite(m, o) for _, _, m, o in insns]


def test_this_slot_and_members():
    body = PROLOGUE + [
        (0x19, 3, "mov", "eax, dword ptr [ebp - 8]"),
        (0x1c, 3, "fld", "dword ptr [eax + 4]"),
        (0x1f, 2, "fld", "dword ptr [eax]"),
        (0x21, 3, "mov", "eax, dword ptr [ebp + 0xc]"),
        (0x24, 3, "mov", "ecx, dword ptr [eax + 4]"),
    ]
    frame = wb_show.Frame(body)
    assert frame.this_slot == "dword ptr [ebp - 8]"
    assert frame.body_index == 4
    assert rewrite_all(body)[3:] == [
        "this, ecx", "eax, this", "dword ptr [this->+0x4]", "dword ptr [this->+0x0]",
        "eax, dword ptr [arg_1]", "ecx, dword ptr [eax + 4]",
    ]


def test_no_this_when_ecx_clobbered_first():
    body = PROLOGUE[:3] + [(0x16, 5, "mov", "ecx, 1"), (0x1b, 3, "mov", "dword ptr [ebp - 8], ecx")]
    assert wb_show.Frame(body).this_slot is None
    assert rewrite_all(body)[-1] == "dword ptr [local_8], ecx"


def test_call_clobbers_this_registers():
    body = PROLOGUE + [
        (0x19, 3, "mov", "edx, dword ptr [ebp - 8]"),
        (0x1c, 5, "call", "0x1000"),
        (0x21, 3, "mov", "eax, dword ptr [edx + 0x10]"),
    ]
    assert rewrite_all(body)[-1] == "eax, dword ptr [edx + 0x10]"


def test_ignore_check_shapes():
    insns = [
        (0, 2, "push", "0"), (2, 5, "call", "0x712780"), (7, 3, "add", "esp, 4"),
        (10, 3, "movzx", "ecx, al"), (13, 2, "test", "ecx, ecx"), (15, 6, "jne", "0x80"),
        (21, 6, "mov", "edx, dword ptr [0x223c49c]"),
    ]
    assert wb_show.ignore_check(insns, 6, 0x80) == 0
    assert wb_show.ignore_check(insns, 6, 0x90) is None
    always = insns[:3] + insns[6:]          # `push 1; call; add esp` with no skip branch
    assert wb_show.ignore_check(always, 3, None) == 0


# ------------------------------------------------------------- real image

needs_inputs = pytest.mark.skipif(
    not all(p.exists() for p in wb_show.INPUTS), reason="WorldBuilder inputs not built")


class Args:
    gd, raw, max_lines = False, False, 400


def show(target, **flags):
    args = Args()
    for key, value in flags.items():
        setattr(args, key, value)
    index = wb_show.load_index()
    gd_va, wb_va, _ = wb_show.resolve_target(index, target)
    return wb_show.report(index, gd_va, wb_va, args)


@needs_inputs
def test_coord3d_length_collapses_assert():
    text = show("wb:0x4190FC")
    assert "WB va 0x419070 size 293  Coord3D::length" in text
    assert "ASSERT((*this).isInitialized())" in text and "@MathCoord3D.h:374" in text
    assert "dword ptr [this->+0x8]" in text
    assert "import sqrt" in text
    assert "0x223c49c" not in text          # debug-object plumbing hidden
    assert "0x223c49c" in show("wb:0x4190FC", raw=True)


@needs_inputs
def test_execute_action_debug_message_and_callees():
    text = show("ScriptActions::executeAction")
    assert 'DEBUG("Unknown ScriptAction type %d")  @ScriptActions.cpp:12265' in text
    assert "ScriptActions::doBuildBuildingOnFoundation" in text
    assert "truncated at" in text


@needs_inputs
def test_gd_body_names_calls_from_ledger():
    text = show("?length@Coord3D@@QBEMXZ", gd=True)
    assert text.startswith("game.dat rva 0x00003571")
    assert "game.dat body:" in text and "  403571  push ebp" in text
