"""Read-only PE/scoped-ledger preflight. Writes only this private diagnostic folder."""
from pathlib import Path
import csv
import hashlib
import json
import struct
import capstone

B = Path('W:/OpenBFME/Open-BFME-2')
D = Path(__file__).resolve().parent
SOURCE = 'Code/GameEngine/Source/Common/Rva0055F197Ctor.cpp'
files = [SOURCE,
 'Code/GameEngine/Source/Common/Rva003ABD20Ctor.cpp',
 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003ABD20Dtor.cpp',
 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003ABC0BDtor.cpp',
 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/DefaultModuleTemplateCopyCtors.cpp',
 'Code/GameEngine/Source/Common/Disp8FloatFieldGetters.cpp',
 'Code/GameEngine/Source/Common/Disp8LeaFieldGetters.cpp',
 'Code/GameEngine/Source/Common/Disp8ByteFieldGetters.cpp',
 'Code/GameEngine/Source/Common/VtableSlotBodiesR3F.cpp',
 'Code/GameEngine/Source/Common/ConstIntGetters.cpp',
 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva0055EF39Xfer.cpp',
 'Code/GameEngine/Include/GameClient/DefaultModuleHeadBase.h',
 'Code/GameEngine/Include/GameClient/Rva003AEEB3.h',
 'Code/GameEngine/Include/Common/Rva0055BF21.h',
 'Code/GameEngine/Include/GameClient/DefaultPhysicsModuleInfo.h',
 'Code/GameEngine/Include/GameClient/DefaultModuleTemplate.h',
 'Code/GameEngine/Include/GameClient/GameClientRandomVariable.h',
 'reference/shims/moduledata/Common/Snapshot.h',
 'reverse/attempt_support/default-module-pure-bindings-20261109/README.md',
 'reverse/attempt_support/particle_siblings_20261022.md',
 'tools/rename.py', 'tools/add_match.py']
sha = lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
before = {name:sha(B/name) for name in files}
image_path = B/'baselines/bfme2/workshop-vanilla-1.06/files/game.dat'
image = image_path.read_bytes()
pe = struct.unpack_from('<I', image, 0x3C)[0]
count = struct.unpack_from('<H', image, pe+6)[0]
optional = struct.unpack_from('<H', image, pe+20)[0]
image_base = struct.unpack_from('<I', image, pe+24+28)[0]
sections = []
for index in range(count):
    at = pe+24+optional+40*index
    size, rva, raw_size, raw = struct.unpack_from('<IIII', image, at+8)
    sections.append((rva, max(size, raw_size), raw))
def read(rva, size):
    for start, length, raw in sections:
        if start <= rva and rva+size <= start+length:
            return image[raw+rva-start:raw+rva-start+size]
    raise ValueError(hex(rva))

tables = []
for rva, slots, role in ((0x81D654,9,'served-primary'), (0x81D678,4,'served-snapshot'),
                         (0x81D638,4,'Rva0055BF21-base'), (0x81BCB0,4,'DefaultPhysicsModuleInfo')):
    words = struct.unpack('<'+'I'*slots, read(rva, slots*4))
    tables.append(dict(rva=f'0x{rva:08X}', role=role,
                       slots=[f'0x{value-image_base:08X}' for value in words]))
targets = {int(value,16) for table in tables for value in table['slots']}
targets |= {0x55F197,0x55BF21,0x3ABC0B,0x3AEBC9,0x55EE5E}
common = {0xB3FD0:{'??1Region2D@@QAE@XZ',
                 '?LoadPostProcess@DefaultPhysicsModuleInfo@FXParticleSystem@@UAEXXZ'},
          0x49B47C:{'??1Snapshot@@UAE@XZ',
                    '??1DefaultPhysicsModuleInfo@FXParticleSystem@@UAE@XZ'}}
rows, served = [], []
with (B/'reverse/functions.csv').open(newline='', encoding='utf-8') as handle:
    for row in csv.DictReader(handle):
        if row['source'] == SOURCE:
            served.append({k:row[k] for k in ('name','target_rva','target_size','source','status','notes')})
        try: rva = int(row['target_rva'],16)
        except ValueError: continue
        if rva not in targets or rva in common and row['name'] not in common[rva]: continue
        rows.append({k:row[k] for k in ('name','target_rva','target_size','source','status','notes')})
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
bodies = {}
for row in rows:
    rva = int(row['target_rva'],16)
    if rva in bodies: continue
    size = int(row['target_size']); raw = read(rva,size)
    bodies[rva] = dict(rva=f'0x{rva:08X}', size=size, raw_hex=raw.hex(),
        asm=[f'{ins.address:08X} {ins.mnemonic} {ins.op_str}' for ins in md.disasm(raw,rva)])
label = read(0x81C59C,64).split(b'\0',1)[0].decode('ascii')
after = {name:sha(B/name) for name in files}
assert before == after
receipt = dict(parent_reported_head='fb05fff834 (17de7e integrated)', global_head_snapshot_claim=False,
    image_sha256=hashlib.sha256(image).hexdigest(), tables=tables, selected_rows=rows,
    served_whole_file_rows=served, bodies=list(bodies.values()), snapshot_name_literal=label,
    source_hashes=after, inspected_inputs_stable=True, actual_cpp_pp_calls=0,
    production_writes=False, task_credit=0)
(D/'EVIDENCE.json').write_text(json.dumps(receipt, indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(tables=tables, served_rows=len(served),
                     snapshot_name=label, selected_row_count=len(rows),
                     actual_cpp_pp_calls=0, inspected_inputs_stable=True),indent=2))
