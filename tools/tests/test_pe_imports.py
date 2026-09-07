"""Named PE import identity is evidence; a masked address or ordinal is not."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import pe_imports
import pin_consistency


def fixture_pe(entries, *, original_lookup=True):
    """Small file-backed PE32 with one separate descriptor/IAT per import."""
    data = bytearray(0x1200)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<H", data, 0x86, 1)
    struct.pack_into("<H", data, 0x94, 0xE0)
    optional = 0x98
    struct.pack_into("<H", data, optional, 0x10B)
    struct.pack_into("<I", data, optional + 28, 0x400000)
    struct.pack_into("<I", data, optional + 60, 0x200)
    struct.pack_into("<I", data, optional + 92, 16)
    struct.pack_into("<II", data, optional + 104,
                     0x1100, (len(entries) + 1) * 20)
    section = optional + 0xE0
    data[section:section + 8] = b".rdata\0\0"
    struct.pack_into("<IIII", data, section + 8, 0x1000, 0x1000, 0x1000, 0x200)

    def write(rva, contents):
        offset = rva - 0x1000 + 0x200
        data[offset:offset + len(contents)] = contents

    slots = []
    for index, (dll, name) in enumerate(entries):
        lookup, first = 0x1400 + index * 16, 0x1480 + index * 16
        dll_rva, name_rva = 0x1500 + index * 64, 0x1700 + index * 64
        write(0x1100 + index * 20, struct.pack(
            "<IIIII", lookup if original_lookup else 0, 0, 0, dll_rva, first))
        write(dll_rva, dll.encode("ascii") + b"\0")
        value = name | 0x80000000 if isinstance(name, int) else name_rva
        write(lookup, struct.pack("<II", value, 0))
        write(first, struct.pack("<II", value, 0))
        if isinstance(name, str):
            write(name_rva, b"\0\0" + name.encode("ascii") + b"\0")
        slots.append(0x400000 + first)
    return bytes(data), slots


def thunk(slot):
    return b"\xff\x25" + struct.pack("<I", slot)


@pytest.mark.parametrize("original_lookup", [True, False])
def test_distinct_iat_slots_for_exact_same_named_import(original_lookup):
    data, slots = fixture_pe([("wsock32.dll", "htonl")] * 2,
                             original_lookup=original_lookup)
    imports = pe_imports.read_imports(data)
    assert slots[0] != slots[1]
    assert imports[slots[0]] == pe_imports.ImportEntry("wsock32.dll", "htonl", None)
    assert pe_imports.same_named_import_thunk(thunk(slots[0]), thunk(slots[1]), imports)


@pytest.mark.parametrize("right", [
    ("wsock32.dll", "ntohl"),
    ("ws2_32.dll", "htonl"),
    ("WSOCK32.DLL", "htonl"),
    ("wsock32.dll", "Htonl"),
    ("wsock32.dll", 8),
])
def test_different_or_ordinal_imports_never_acquire_named_equivalence(right):
    data, slots = fixture_pe([("wsock32.dll", "htonl"), right])
    assert not pe_imports.same_named_import_thunk(
        thunk(slots[0]), thunk(slots[1]), pe_imports.read_imports(data))


def test_even_equal_ordinals_remain_unresolved():
    data, slots = fixture_pe([("wsock32.dll", 8)] * 2)
    imports = pe_imports.read_imports(data)
    assert imports[slots[0]] == pe_imports.ImportEntry("wsock32.dll", None, 8)
    assert not pe_imports.same_named_import_thunk(thunk(slots[0]), thunk(slots[1]), imports)


def test_directory_size_may_exclude_exactly_its_null_terminator():
    raw, slots = fixture_pe([("wsock32.dll", "htonl")])
    data = bytearray(raw)
    struct.pack_into("<I", data, 0x98 + 108, 20)
    assert pe_imports.read_imports(data)[slots[0]].name == "htonl"
    # A live second descriptor beyond that declared extent is still rejected.
    data[0x314:0x328] = data[0x300:0x314]
    with pytest.raises(ValueError, match="unterminated PE import directory"):
        pe_imports.read_imports(data)


def test_unknown_slots_never_acquire_named_equivalence():
    data, slots = fixture_pe([("wsock32.dll", "htonl")])
    imports = pe_imports.read_imports(data)
    assert not pe_imports.same_named_import_thunk(thunk(slots[0]), thunk(0xDEADBEEF), imports)
    assert not pe_imports.same_named_import_thunk(thunk(0xDEADBEEF), thunk(0xDEADBEEF), imports)


@pytest.mark.parametrize("alter", [
    lambda body: body + b"\xc3",
    lambda body: body[:-1],
    lambda body: b"\xff\x15" + body[2:],
    lambda body: b"\xb8" + body[2:] + b"\xc3",
])
def test_only_the_complete_six_byte_jump_qualifies(alter):
    data, slots = fixture_pe([("wsock32.dll", "htonl")] * 2)
    assert not pe_imports.same_named_import_thunk(
        alter(thunk(slots[0])), thunk(slots[1]), pe_imports.read_imports(data))


@pytest.mark.parametrize("mutate", [
    lambda data: data.__setitem__(slice(0, 2), b"NO"),
    lambda data: struct.pack_into("<H", data, 0x98, 0x20B),
    lambda data: struct.pack_into("<I", data, 0x98 + 104, 0x900000),
    # A lookup VA from an already-bound FirstThunk is not an import-name RVA.
    lambda data: struct.pack_into("<I", data, 0x600, 0x70001000),
    lambda data: struct.pack_into("<I", data, 0x98 + 108, 19),
])
def test_malformed_import_metadata_fails_closed(mutate):
    raw, _ = fixture_pe([("wsock32.dll", "htonl")])
    data = bytearray(raw)
    mutate(data)
    with pytest.raises(ValueError):
        pe_imports.read_imports(data)


@pytest.mark.parametrize("size", [0, 0x40, 0x100, 0x750])
def test_truncated_pe_fails_closed(size):
    data, _ = fixture_pe([("wsock32.dll", "htonl")])
    with pytest.raises(ValueError):
        pe_imports.read_imports(data[:size])


@pytest.mark.parametrize("name,addresses", [
    ("_htonl@4", [0x655670, 0x65565E]),
    ("_htons@4", [0x655682, 0x6556B8]),
])
def test_retail_duplicate_named_import_thunks_pass_the_pin_guard(name, addresses):
    scanner = pin_consistency.Scanner()
    left, right = [build.read_target_bytes(address, 6) for address in addresses]
    assert left != right
    assert not pin_consistency.rebased_equal(left, right, *addresses)[0]
    assert pe_imports.same_named_import_thunk(left, right, scanner.image.imports)
    assert scanner.inspect(name, addresses) is None


def test_retail_different_exports_still_fail_the_pin_guard():
    violation = pin_consistency.Scanner().inspect("_htonl@4", [0x655670, 0x655682])
    assert violation is not None
    assert violation["kind"] == "divergent-bodies"
