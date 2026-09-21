"""The __EH_prolog size repair: rules on a synthetic image, then the real data."""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))

import fix_eh_prolog_sizes as fix  # noqa: E402

HELPER = 0x9000
NEXT = [(0x2000, 5, "next")]


class FakeImage:
    """RVA-addressed blobs; everything else reads as int3."""

    def __init__(self, blobs):
        self.blobs = blobs

    def read(self, rva, count):
        out = bytearray(b"\xCC" * count)
        for start, blob in self.blobs.items():
            for i in range(count):
                if 0 <= rva + i - start < len(blob):
                    out[i] = blob[rva + i - start]
        return bytes(out)


def function(at, body):
    rel = HELPER - (at + fix.PROLOG_CALL)
    return b"\xB8\x11\x22\x33\x00\xE8" + rel.to_bytes(4, "little", signed=True) + body


BODY = (b"\x33\xC0"                    # xor eax, eax
        b"\x74\x02"                    # je +2
        b"\x40\x40"                    # inc eax; inc eax
        b"\xC9"                        # leave
        b"\xC2\x04\x00")               # ret 4
REAL = fix.PROLOG_CALL + len(BODY)


def repair(body, rows, helper=fix.EH_PROLOG):
    return fix.repair(FakeImage({0x1000: function(0x1000, body), HELPER: helper}), rows)


def test_a_truncated_body_gets_its_real_size():
    out, changed, skipped = repair(BODY, [(0x1000, 10, "f")] + NEXT)
    assert out == [(0x1000, REAL, "f")] + NEXT
    assert changed == [(0x1000, 10, REAL)] and skipped == 0


def test_a_call_to_anything_but_eh_prolog_is_left_alone():
    rows = [(0x1000, 10, "f")] + NEXT
    out, changed, _ = repair(BODY, rows, helper=b"\x55" + fix.EH_PROLOG[1:])
    assert out == rows and changed == []


def test_only_size_ten_rows_are_touched():
    rows = [(0x1000, 12, "f")] + NEXT
    out, changed, _ = repair(BODY, rows)
    assert out == rows and changed == []


def test_no_end_before_the_next_function_is_left_alone():
    rows = [(0x1000, 10, "f"), (0x1000 + 30, 5, "next")]
    out, changed, skipped = repair(b"\x40" * 40, rows)
    assert out == rows and changed == [] and skipped == 1


def test_a_backward_jmp_ends_the_body():
    """Nothing falls through a jmp, so an unlisted next function is not swallowed."""
    body = (b"\x33\xC0"                # xor eax, eax
            b"\x40"                    # inc eax
            b"\xEB\xFD"                # jmp -3 (back to inc)
            b"\x55\xC3")               # next, unlisted function
    out, _, _ = repair(body, [(0x1000, 10, "f")] + NEXT)
    assert out[0][1] == fix.PROLOG_CALL + 5


def test_int3_padding_ends_the_body():
    body = (b"\xE8\x00\x00\x00\x00"    # call (e.g. a no-return throw)
            b"\xCC\xCC"                # padding
            b"\x55\xC3")               # next, unlisted function
    out, _, _ = repair(body, [(0x1000, 10, "f")] + NEXT)
    assert out[0][1] == fix.PROLOG_CALL + 5


def test_a_switch_dispatch_is_not_an_end():
    body = (b"\x33\xC0"                                   # xor eax, eax
            b"\xFF\x24\x85\x00\xC2\x40\x00"               # jmp [eax*4+0x40C200]
            b"\xC9\xC3")                                  # leave; ret
    rows = [(0x1000, 10, "f")] + NEXT
    out, changed, skipped = repair(body, rows)
    assert out == rows and changed == [] and skipped == 1


def test_a_switch_table_after_the_body_is_not_counted():
    out, _, _ = repair(BODY + (0x1000).to_bytes(4, "little") * 8, [(0x1000, 10, "f")] + NEXT)
    assert out[0][1] == REAL


@pytest.fixture(scope="module")
def inventory():
    return fix.Image(REPO / fix.BINARY), fix.read_inventory(REPO / fix.INVENTORY)


def test_committed_inventory_needs_no_repair(inventory):
    """Fails if a Ghidra regeneration brings the 10-byte sizes back."""
    image, rows = inventory
    _, changed, _ = fix.repair(image, rows)
    assert changed == [], f"{len(changed)} rows need repair: run tools/fix_eh_prolog_sizes.py"


def test_sizes_agree_with_byte_matched_rows(inventory):
    sizes = {rva: size for rva, size, _name in inventory[1]}
    assert sizes[0x2152] == 117       # ??1Version@@QAE@XZ
    assert sizes[0x240E] == 75        # ??1ParticleSystemInfo@FXParticleSystem@@UAE@XZ


def test_no_repaired_body_overlaps_the_next_function(inventory):
    image, rows = inventory
    assert image.read(0x629188, len(fix.EH_PROLOG)) == fix.EH_PROLOG
    ordered = sorted(rows)
    for (rva, size, name), (after, _size, _name) in zip(ordered, ordered[1:]):
        if size != fix.PROLOG_CALL and fix.eh_prolog_target(image, rva) == 0x629188:
            assert rva + size <= after, f"{name} at {rva:#x} overlaps {after:#x}"


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-v"]))
