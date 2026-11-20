"""Checks for the modernizer loader blob format and its relocation rules."""
import hashlib
import sys
from pathlib import Path
import struct

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import modern_blob as mb  # noqa: E402

BASE = 0x00EDA000


def make_blob(memory, *, abs_sites=(), rel_sites=(), secrel_sites=(), hooks=()):
    runs = [(0, bytes(memory))]
    return (b"BFME2MDL" + struct.pack("<I", mb.BLOB_VERSION) + hashlib.sha256(b"game").digest()
            + struct.pack("<13I", BASE, len(memory), len(runs), 0, 0, 0, 0, 0, 0,
                          len(hooks), len(abs_sites), len(rel_sites), len(secrel_sites))
            + b"".join(struct.pack("<II5s3x", va, target, orig) for va, target, orig in hooks)
            + struct.pack(f"<{len(abs_sites)}I", *abs_sites)
            + struct.pack(f"<{len(rel_sites)}I", *rel_sites)
            + struct.pack(f"<{len(secrel_sites)}I", *secrel_sites)
            + b"".join(struct.pack("<II", o, len(b)) + b for o, b in runs))


def test_loader_moves_internal_addresses_and_keeps_external_calls():
    memory = bytearray(0x40)
    struct.pack_into("<I", memory, 0x00, BASE + 0x20)              # DIR32 to the blob
    struct.pack_into("<I", memory, 0x04, (0x401000 - (BASE + 4 + 4)) & 0xFFFFFFFF)  # REL32 to retail
    struct.pack_into("<I", memory, 0x08, 0x20 - (0x08 + 4))        # REL32 inside the blob
    struct.pack_into("<I", memory, 0x0C, 4)                        # SECREL
    blob = make_blob(memory, abs_sites=[BASE], rel_sites=[BASE + 4], secrel_sites=[BASE + 0x0C])
    moved = 0x10000000
    _, mapped = mb.load_at(blob, BASE + moved, tls_bias=8)
    assert struct.unpack_from("<I", mapped, 0x00)[0] == BASE + moved + 0x20
    assert (struct.unpack_from("<I", mapped, 0x04)[0] + BASE + moved + 8) & 0xFFFFFFFF == 0x401000
    assert struct.unpack_from("<I", mapped, 0x08)[0] == 0x20 - 0x0C
    assert struct.unpack_from("<I", mapped, 0x0C)[0] == 12
    sites = [(BASE, mb.REL_DIR32, BASE + 0x20), (BASE + 4, mb.REL_REL32, 0x401000),
             (BASE + 8, mb.REL_REL32, BASE + 0x20), (BASE + 0x0C, mb.REL_SECREL, 0)]
    assert mb.check_relocation(blob, sites, moved) == 4


def test_misclassified_call_into_the_blob_is_refused():
    # A call to a thunk at the blob's start listed as a call to retail: after a
    # move it would still reach the old address (the first loader prototype's crash).
    memory = bytearray(0x10)
    struct.pack_into("<I", memory, 0x04, (BASE - (BASE + 4 + 4)) & 0xFFFFFFFF)
    blob = make_blob(memory, rel_sites=[BASE + 4])
    with pytest.raises(ValueError, match="after a move"):
        mb.check_relocation(blob, [(BASE + 4, mb.REL_REL32, BASE)])


def test_parse_rejects_other_formats_and_trailing_bytes():
    blob = make_blob(bytearray(8))
    with pytest.raises(ValueError):
        mb.parse_blob(b"BFME2MOD" + blob[8:])
    with pytest.raises(ValueError, match="trailing"):
        mb.parse_blob(blob + b"\0")


def test_hook_records_round_trip():
    blob = make_blob(bytearray(8), hooks=[(0x401000, BASE + 4, b"\x55\x8b\xec\x83\xec")])
    head, _ = mb.parse_blob(blob)
    assert head["hook_list"] == [(0x401000, BASE + 4, b"\x55\x8b\xec\x83\xec")]


def test_modern_sources_are_the_files_that_name_the_variant():
    sources = mb.modern_sources()
    assert "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp" in sources
    assert sources == sorted(sources)
    for name in sources:
        assert "BFME2_MODERN" in (mb.ROOT / name).read_text(encoding="utf-8", errors="replace")
