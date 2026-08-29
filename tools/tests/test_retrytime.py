#!/usr/bin/env python3
"""Build the retransmit-timer arm and check it changed four bytes and no others.

This feature has no payload and no detour, so the usual cave assertions say
nothing about it. What can go wrong instead is arithmetic: the constant is an
imm32 three bytes into `mov dword ptr [edx+0x1C], 2000`, and an address off by
one writes a value that is still plausible into the middle of an instruction.
So the instruction around the poke is asserted, not just the poke, and the rest
of the retail image is asserted to be untouched -- a spike arm that quietly
moved something else would be credited or blamed for it.
"""
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
pytestmark = pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")

from cave import PE  # noqa: E402
from modbuild import RETRY_MS, RETRY_WAS, TARGET_RETRYTIME  # noqa: E402

FEATURE = "033-retrytime"
STORE = 0x006623DB                        # Connection::init's m_retryTime store
STORE_BYTES = bytes([0xC7, 0x42, 0x1C])   # mov dword ptr [edx+0x1C], imm32


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "retry.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return PE(out)


def test_the_poke_sits_inside_the_store_it_claims_to():
    """Asserted against retail, not against the build: if the opcode is not
    there, every other assertion here is about the wrong bytes."""
    pe = PE(EXE)
    assert pe.read(STORE, 3) == STORE_BYTES, f"0x{STORE:08X} is not the m_retryTime store"
    assert TARGET_RETRYTIME == STORE + 3, "the imm32 is three bytes into the store"
    assert struct.unpack("<I", pe.read(TARGET_RETRYTIME, 4))[0] == RETRY_WAS


def test_the_timer_is_the_new_value(built):
    assert struct.unpack("<I", built.read(TARGET_RETRYTIME, 4))[0] == RETRY_MS
    assert built.read(STORE, 3) == STORE_BYTES, "the poke overwrote the opcode"


def test_a_shorter_timer_is_the_point():
    """An arm that raised the timer would measure the opposite of what the
    feature claims, and the histogram it is judged on would still look moved."""
    assert 0 < RETRY_MS < RETRY_WAS


def test_nothing_else_in_the_retail_image_moved(built):
    retail = PE(EXE).data
    got = built.data[:len(retail)]
    differ = {i for i in range(len(retail)) if retail[i] != got[i]}
    site = set(range(built.rva_to_off(TARGET_RETRYTIME),
                     built.rva_to_off(TARGET_RETRYTIME) + 4))
    # Containment, not equality: 2000 and 400 share their two high bytes, so a
    # correct poke leaves two of its four bytes untouched. Requiring all four to
    # differ would fail on a working feature and pass only by coincidence of
    # which values were chosen.
    body = {i for i in differ if i >= 0x1000}
    assert body <= site, f"{len(body - site)} bytes outside the poke changed"
    assert body, "the build is byte-identical to retail: the poke never landed"


def test_a_dist_build_refuses_to_carry_it():
    """The duplicate-delivery half is still unmeasured: at 40 ms round trip a
    400 ms timer essentially never fires early, so nothing run so far exercises
    a command arriving twice -- and a lockstep command executed twice is a
    desync, not a bandwidth cost."""
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "--dist"],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode != 0, "a --dist build accepted an unmeasured arm"
    assert "refusing --dist" in (r.stderr + r.stdout)
