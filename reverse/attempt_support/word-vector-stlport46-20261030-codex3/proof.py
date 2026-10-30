"""Check the complete word allocator twin and its two retail vector callers.

Run from the repository root after building the four sources in readme.md.
This reads verified objects; it never compiles through build.py.
"""
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import build

root = Path("Code/Libraries/Source/WWVegas/WWLib")
old_name = "?allocate@?$allocator@G@_STL@@QBEPAGIPBX@Z"
new_name = "?allocate@?$allocator@G@_STL@@QAEPAGIPBX@Z"
old_body, old_relocs = build.read_object_symbol_bytes(
    build.obj_path(root / "stlport_wide_string.cpp"), old_name, code_only=True
)
new_body, new_relocs = build.read_object_symbol_bytes(
    build.obj_path(root / "stlport_wide_num_put.cpp"), new_name, code_only=True
)
native = build.read_target_bytes(0x17710, 29)
assert len(old_body) == len(new_body) == len(native) == 29
assert old_relocs == new_relocs == [
    (14, 20, "?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")
]
assert native[13] == 0xE8
assert 0x17710 + 18 + struct.unpack_from("<i", native, 14)[0] == 0x307F0
normalized = bytearray(native)
normalized[14:18] = b"\0" * 4
assert old_body == new_body == normalized

callers = [
    (0x7EAA7, 139, 43,
     "?_M_insert_overflow@?$vector@GV?$allocator@G@_STL@@@_STL@@IAEXPAGABGABU__true_type@2@I_N@Z"),
    (0x513D55, 58, 36,
     "??0?$_Vector_base@GV?$allocator@G@_STL@@@_STL@@QAE@IABV?$allocator@G@1@@Z"),
]
proof = {
    "native_rva": "0x00017710", "size": 29,
    "native_bytes": native.hex(), "normalized_bytes": new_body.hex(),
    "relocations": new_relocs, "byte_allocator_rva": "0x000307F0",
    "existing_owner": old_name, "new_twin": new_name,
    "native_callers": [], "unique_covered_bytes_added": 0, "new_pins": 0,
}
for rva, size, offset, name in callers:
    body = build.read_target_bytes(rva, size)
    assert body[offset - 1] == 0xE8
    target = rva + offset + 4 + struct.unpack_from("<i", body, offset)[0]
    assert target == 0x17710
    _, relocations = build.read_object_symbol_bytes(
        build.obj_path(root / "stlport_vector_word_o1.cpp"), name, code_only=True
    )
    assert (offset, 20, new_name) in relocations
    proof["native_callers"].append({
        "rva": hex(rva), "size": size, "relocation_offset": offset,
        "target": hex(target), "symbol": name,
    })
out = Path("build/word-vector46/allocator-proof.json")
out.parent.mkdir(parents=True, exist_ok=True)
out.write_text(json.dumps(proof, indent=2) + "\n")
print("Complete 29-byte twin, exact relocation, native byte allocator and both retail vector callers verified.")
