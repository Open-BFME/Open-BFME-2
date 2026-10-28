"""Verify native lifetime/EH/table emissions in the ordinary constructor object.
This is not a row admission, TU merge, census or runtime test.
Run from the repository root with its normal Python environment.
"""
import hashlib
import json
import struct
import subprocess
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(root / 'tools'))
import build
import eh_verify
import link_census

# Use the ordinary build.sh entry point. Never compile_source() by hand.
source = root / "Code/GameEngine/Source/Common/MultiplayerSettingsCtor.cpp"
candidate = source.read_bytes()
retail_sha256 = hashlib.sha256(build.exe_image()[0]).hexdigest()
assert retail_sha256 == 'f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640', retail_sha256
subprocess.run([sys.executable, "-B", "-X", "utf8", "tools/build.py",
                source.relative_to(root).as_posix()], cwd=root, check=True)
objpath = build.obj_path(source)
work = root / "build/scratch/multiplayer-settings-lifetime-20261029"
work.mkdir(parents=True, exist_ok=True)

rows = link_census.ledger()
truth = link_census.RetailTruth(rows)
entries = {entry[0]['name']: entry for entry in link_census._comdat_sections(objpath.read_bytes())}
homes = {
    '??0MultiplayerSettings@@QAE@XZ': (0x3811d8, 159),
    '??1MultiplayerSettings@@UAE@XZ': (0x381293, 83),
    '??_GMultiplayerSettings@@UAEPAXI@Z': (0x381277, 28),
    '??_7MultiplayerSettings@@6B@': (0x8191b8, 56),
}
report = {'source_sha256': hashlib.sha256(candidate).hexdigest(),
          'object_sha256': hashlib.sha256(objpath.read_bytes()).hexdigest(),
          'input': source.relative_to(root).as_posix(),
          'bodies': [], 'eh': [], 'funclets': []}
report['retail_sha256'] = retail_sha256
for name, (rva, length) in homes.items():
    symbol, body, relocs, digest, size = entries[name]
    verdict = truth._judge(rva, symbol, body, relocs, size)
    assert size == length and verdict == 'retail', (name, size, verdict)
    report['bodies'].append({'name': name, 'rva': hex(rva), 'size': size, 'digest': digest, 'verdict': verdict})
    print(name, hex(rva), size, verdict)

image = eh_verify.Image()
obj = eh_verify.Obj(objpath)
for name in ['??0MultiplayerSettings@@QAE@XZ', '??1MultiplayerSettings@@UAE@XZ']:
    rva = homes[name][0]
    verdict = eh_verify.verify_row(image, obj, name, rva)
    assert verdict == ('EXACT', ''), (name, verdict)
    locations = eh_verify.verified_funclet_locations(image, obj, name, rva)
    report['eh'].append({'name': name, 'verdict': verdict, 'locations': {n: hex(a) for n, a in locations.items()}})
    print('EH', name, verdict, locations)
    if name.startswith('??1'):
        for address, length in [(0x77f308, 8), (0x77f310, 11), (0x77f31b, 11)]:
            labels = [label for label, place in locations.items() if place == address]
            assert len(labels) == 1, (hex(address), labels)
            label = labels[0]
            body, relocs = build.read_object_symbol_bytes(objpath, label, code_only=True)
            relevant = [(offset, kind, target) for offset, kind, target in relocs if offset < length]
            native = build.read_target_bytes(address, length)
            actual = bytearray(body[:length])
            targets = []
            for offset, kind, target in relevant:
                assert kind == 0x14
                assert struct.unpack_from('<i', body, offset)[0] == 0, (label, target, 'nonzero REL32 addend')
                native_target = address + offset + 4 + struct.unpack_from('<i', native, offset)[0]
                acceptable = truth.addresses(target, kind)
                if acceptable:
                    assert truth._lands(native_target, acceptable), (label, target, hex(native_target), acceptable)
                elif target in entries:
                    s, b, r, _, z = entries[target]
                    assert truth._judge(native_target, s, b, r, z) == 'retail', (label, target, hex(native_target))
                else:
                    raise AssertionError((label, target, 'unresolved external target'))
                actual[offset:offset + 4] = native[offset:offset + 4]
                targets.append({'name': target, 'native_rva': hex(native_target)})
            assert bytes(actual) == native
            report['funclets'].append({'rva': hex(address), 'scratch_label': label, 'size': length,
                                      'parent': name, 'targets': targets, 'verdict': 'EXACT; graph-bound'})
            print('FUNCLET', hex(address), label, targets)

parent_name = '??1MultiplayerSettings@@UAE@XZ'
handler_name = '__ehhandler$' + parent_name
handler_rva, funcinfo_rva = image.frame_funcinfo(0x381293)
assert handler_rva == 0x77f326
parent_symbol = obj.by_name[parent_name]
placements, conflicts = eh_verify.section_placements(image, obj,
    dict(parent_symbol, retail_rva=0x381293), obj.eh_sections(parent_symbol['section']))
assert not conflicts
body, relocs, detail = build.read_object_symbol_bytes(objpath, handler_name, code_only=True, detail=True)
native = build.read_target_bytes(handler_rva, 10)
assert len(body) == 10
resolved = bytearray(body)
for (offset, kind, target), symbol_index in zip(relocs, detail['reloc_symbols']):
    symbol = detail['symbols'][symbol_index]
    assert struct.unpack_from('<I', body, offset)[0] == 0, (target, 'nonzero handler relocation addend')
    if kind == 6:
        target_rva = placements[symbol['section']] + symbol['value']
        assert target_rva == funcinfo_rva
        struct.pack_into('<I', resolved, offset, image.base + target_rva)
    else:
        assert kind == 0x14
        target_rva = handler_rva + offset + 4 + struct.unpack_from('<i', native, offset)[0]
        assert truth._lands(target_rva, truth.addresses(target, kind))
        struct.pack_into('<i', resolved, offset, target_rva - handler_rva - offset - 4)
assert bytes(resolved) == native
report['handler'] = {'name': handler_name, 'rva': hex(handler_rva), 'size': 10,
                     'funcinfo_rva': hex(funcinfo_rva), 'verdict': 'EXACT; graph-bound FuncInfo and verified frame-handler target'}
print('HANDLER', hex(handler_rva), hex(funcinfo_rva), 'EXACT')

path = work / 'proof.json'
path.write_text(json.dumps(report, indent=2), encoding='utf-8')
print(path.relative_to(root))
