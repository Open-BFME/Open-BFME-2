import csv,json,struct,sys
from pathlib import Path
sys.path.insert(0,'tools')
import build
import link_census as lc
scratch=Path('build/fireweapon-primary-link-20261030')
ctor='Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp'
dtor='Code/GameEngine/Source/Common/Rva00589079Derived.cpp'
getter='?GetSnapshotName@FireWeaponWhenDeadBehavior@@UBEPBDXZ'
table='??_7FireWeaponWhenDeadBehavior@@6BObjectModule@@@'
with Path('reverse/functions.csv').open(newline='') as f:
    rows={r['name']:r for r in csv.DictReader(f) if r['source'] in (ctor,dtor)}
old='?Rva00482E4BGet@@YAHXZ'
row=rows.get(getter) or {**rows[old],'name':getter}
obj=build.obj_path(Path(ctor)); symbols=build.load_symbol_map()
patch=build.compile_function(row,symbols,obj)
assert not patch['unresolved'] and not patch.get('masked') and patch['bytes']==patch['target']
native=[x-0x400000 for x in struct.unpack('<13I',build.read_target_bytes(0x8497B4,52))]
proof={'getter':{'name':getter,'rva':'0x00482E4B','size':6,'exact_resolved_bytes':True},'native_table_rva':'0x008497B4','sources':{},'slots':[]}
for source,name,rva,size,offset in [(ctor,'??0FireWeaponWhenDeadBehavior@@QAE@PAVThing@@PBVModuleData@@@Z',0x482D80,203,55),(dtor,'??1FireWeaponWhenDeadBehavior@@UAE@XZ',0x482E96,39,2)]:
    native_body=build.read_target_bytes(rva,size)
    assert int.from_bytes(native_body[offset:offset+4],'little')==0xC497B4
    _,refs=build.read_object_symbol_bytes(build.obj_path(Path(source)),name,code_only=True)
    assert (offset,6,table) in refs
proof['native_vptr_bindings']=[{'rva':'0x00482D80','offset':55},{'rva':'0x00482E96','offset':2}]
all_tables=[]
for source in (ctor,dtor):
    path=build.obj_path(Path(source)); raw=path.read_bytes(); body,relocs=build.read_object_symbol_bytes(path,table)
    assert len(body)==52 and len(relocs)==13 and all(o==4*i and k==6 for i,(o,k,n) in enumerate(relocs))
    all_tables.append((body,relocs)); weak=dict(lc._weak_externals(raw))
    proof['sources'][source]={'size':len(body),'relocations':relocs,'weak_deleting_destructor':weak.get(relocs[0][2])}
assert all_tables[0]==all_tables[1]
path=build.obj_path(Path(dtor)); weak=dict(lc._weak_externals(path.read_bytes()))
for slot,(offset,kind,name) in enumerate(all_tables[0][1]):
    resolved=weak.get(name,name)
    if slot==2:
        mode='getter body independently verified at native address'
    elif slot in (0,1,3,4,12):
        assert symbols.get(resolved)==[native[slot]],(slot,resolved,symbols.get(resolved),native[slot])
        mode='existing ledger/pin binding'
    else:
        emitted,refs=build.read_object_symbol_bytes(path,resolved,code_only=True)
        assert not refs and emitted==build.read_target_bytes(native[slot],len(emitted)),(slot,resolved,emitted.hex())
        assert emitted[-1:] == b'\xc3' or emitted[-3:]==b'\xc2\x08\x00'
        mode='complete inline leaf body equals native slot body'
    proof['slots'].append({'slot':slot,'name':name,'resolved':resolved,'native_rva':hex(native[slot]),'evidence':mode})
(scratch/'table-proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print('Both primary tables have identical 13 slots; all native slot bindings/bodies verified; new getter resolves exactly to native six-byte body.')
