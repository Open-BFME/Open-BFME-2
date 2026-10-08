"""The closed accessor lane must reject drift before it writes a claim."""
import importlib.util
import sys
from pathlib import Path

import pytest


TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("gen_small_accessor_test", TOOLS / "gen_small.py")
gen_small = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = gen_small
spec.loader.exec_module(gen_small)


def row(rva, size):
    return {
        "target_rva": f"0x{rva:08X}",
        "target_size": str(size),
        "source": "Code/gen_asm/example.asm",
        "status": "matched",
        "notes": "gen-dump;bounds=high",
    }


def test_population_is_closed_and_exact(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    body = bytes.fromhex("8b 51 38 33 c0 85 d2 0f 95 c0 c3")
    picked = gen_small.accessor_population([row(0x100, len(body))],
                                            lambda rva, size: body)
    assert picked[0][0] == 0x100
    assert picked[0][3].key == "access-pred-ne"
    assert gen_small.render_accessors(picked).count("Gen_00000100") == 2


def test_population_fails_closed_on_shape_drift(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    with pytest.raises(gen_small.FormatError, match="no longer matches"):
        gen_small.accessor_population([row(0x100, 11)],
                                      lambda rva, size: b"\xC3" * size)


def test_batch_is_the_expected_245_bytes():
    assert len(gen_small.ACCESSOR_BATCH) == 21
    # These fixed donor addresses are not guaranteed to be in BFME 2's live
    # ledger. Measure the closed recipes, leaving live eligibility to the gate.
    sizes = {key: sum(1 if isinstance(item, int) else gen_small.FIELD_WIDTH[item[1]]
                     for item in pattern) for key, pattern in gen_small.PATTERNS.items()}
    assert sum(sizes[key] for _, key in gen_small.ACCESSOR_BATCH) == 245


def test_missing_live_batch_row_still_refuses_generation(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    with pytest.raises(gen_small.FormatError, match="is missing"):
        gen_small.accessor_population([], lambda *_: pytest.fail("read before row lookup"))


def test_masm_path_does_not_substitute_for_dump_notes(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    candidate = row(0x100, 11)
    candidate["notes"] = "recovered real source"
    with pytest.raises(gen_small.FormatError, match="not a live gen-dump"):
        gen_small.accessor_population([candidate], lambda *_: pytest.fail("read before classification"))


def test_live_dump_in_another_lane_is_not_the_closed_accessor_batch(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    candidate = row(0x100, 11)
    candidate["source"] = "Code/gen_small/dumps_000.cpp"
    with pytest.raises(gen_small.FormatError, match="moved out of gen_asm"):
        gen_small.accessor_population([candidate], lambda *_: pytest.fail("read before lane check"))
