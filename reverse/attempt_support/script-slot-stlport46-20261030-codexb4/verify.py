#!/usr/bin/env python3
"""Read-only native allocator/caller proof; build the cohort and AptTimeLineStats.cpp first."""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build

SOURCES = [
    'Code/GameEngine/Source/Common/BfmeOwnerZKRelink.cpp',
    'Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptListSubrecordRemove.cpp',
    'Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptListTakeGroups.cpp',
    'Code/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_fastAssignAllUniqueIDs.cpp',
]
ALLOC = '?allocate@?$allocator@PAUBfmeScriptSlotAddress@@@_STL@@QAEPAPAUBfmeScriptSlotAddress@@IPBX@Z'
BYTE_ALLOC = '?allocate@?$allocator@D@_STL@@SAPADIPBX@Z'
PEER = '?allocate@?$allocator@H@_STL@@QBEPAHIPBX@Z'
PEER_SOURCE = 'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineStats.cpp'
CALLERS = [
    ('?_M_initialize_map@?$_Deque_base@UBfmeScriptSlotAddress@@V?$allocator@UBfmeScriptSlotAddress@@@_STL@@@_STL@@IAEXI@Z', 0x0030D96F, 156, 58),
    ('?_M_reallocate_map@?$deque@UBfmeScriptSlotAddress@@V?$allocator@UBfmeScriptSlotAddress@@@_STL@@@_STL@@IAEXI_N@Z', 0x003B57E5, 250, 133),
]
EXPECTED = bytes.fromhex('8b44240485c0740fc1e0026a0050e8000000005959eb0233c0c20800')
EXPECTED_RELOCS = [(15, 20, BYTE_ALLOC)]


def native_rel32(rva, size, at, target):
    native = build.read_target_bytes(rva, size)
    assert native[at - 1] == 0xE8, (hex(rva), at, 'not CALL REL32')
    actual = rva + at + 4 + struct.unpack_from('<i', native, at)[0]
    assert actual == target, (hex(rva), hex(actual), hex(target))
    return native


def main():
    native = bytearray(native_rel32(0x00068E15, 28, 15, 0x000307F0))
    native[15:19] = bytes(4)
    assert bytes(native) == EXPECTED, 'native allocator bytes differ'
    peer_body, peer_relocs = build.read_object_symbol_bytes(build.obj_path(ROOT / PEER_SOURCE), PEER)
    assert peer_body == EXPECTED and peer_relocs == EXPECTED_RELOCS
    for source in SOURCES:
        obj = build.obj_path(ROOT / source)
        body, relocs = build.read_object_symbol_bytes(obj, ALLOC)
        assert body == EXPECTED and relocs == EXPECTED_RELOCS, source
        for name, rva, size, at in CALLERS:
            body, relocs = build.read_object_symbol_bytes(obj, name)
            assert len(body) == size and (at, 20, ALLOC) in relocs, (source, name)
            native_rel32(rva, size, at, 0x00068E15)
        print(f'PASS allocator body/relocation and two native caller edges: {source}')
    print('PASS complete native 28-byte allocator equals existing integer ICF owner; no new unique bytes')


if __name__ == '__main__':
    main()
