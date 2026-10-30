import json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM

source = Path('Code/GameEngine/Source/Common/VectorObjectIDFillInsert.cpp')
old_source = Path('Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineStats.cpp')
old_name = '?allocate@?$allocator@H@_STL@@QBEPAHIPBX@Z'
names = ['?allocate@?$allocator@W4ObjectID@@@_STL@@QAEPAW4ObjectID@@IPBX@Z',
         '?allocate@?$allocator@H@_STL@@QAEPAHIPBX@Z']
old_body, old_relocs = build.read_object_symbol_bytes(build.obj_path(old_source), old_name, code_only=True)
native = build.read_target_bytes(0x68E15, 28)
assert len(old_body) == len(native) == 28
assert old_relocs == [(15, 20, '?allocate@?$allocator@D@_STL@@SAPADIPBX@Z')]
assert native[14] == 0xE8
assert 0x68E15 + 19 + struct.unpack_from('<i', native, 15)[0] == 0x307F0
normalized = bytearray(native)
normalized[15:19] = b'\0' * 4
assert old_body == normalized
proof = {'native_rva': '0x00068E15', 'native_size': 28,
         'native_bytes': native.hex(), 'native_callee_rva': '0x000307F0',
         'existing_owner': old_name, 'new_twins': {}, 'native_callers': {},
         'unique_covered_bytes_added': 0, 'new_pins': 0}
for name in names:
    body, relocs = build.read_object_symbol_bytes(build.obj_path(source), name, code_only=True)
    assert body == old_body and relocs == old_relocs
    proof['new_twins'][name] = {'bytes': body.hex(), 'relocations': relocs}
decoder = Cs(CS_ARCH_X86, CS_MODE_32)
decoder.detail = True
for rva, size in [(0x4F62A4, 58), (0x148D00, 512)]:
    calls = []
    for instruction in decoder.disasm(build.read_target_bytes(rva, size), rva):
        if instruction.mnemonic == 'call' and instruction.operands[0].type == X86_OP_IMM:
            calls.append([hex(instruction.address), hex(instruction.operands[0].imm)])
        if instruction.mnemonic.startswith('ret'):
            break
    assert any(int(target, 16) == 0x68E15 for _, target in calls)
    proof['native_callers'][hex(rva)] = calls
out = Path('build/objectid-allocator-link-20261030/allocator-proof.json')
out.parent.mkdir(parents=True, exist_ok=True)
out.write_text(json.dumps(proof, indent=2) + '\n')
print('Two complete 28-byte ICF twins, exact relocation identity, native byte-allocator call and two native growth callers verified.')
