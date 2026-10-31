import sys,json,struct
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_census as c,allowed_symbols as a
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
p=Path(__file__).resolve().parent
source='Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva003609F7.cpp'
entries=list(c._comdat_sections(build.obj_path(Path(source).resolve()).read_bytes()))
node=next(e for e in entries if e[0]['name'].startswith('?_M_new_node@?$hashtable@'))
image,secs=build.exe_image()
def native(rva,n):
    off=build.rva_to_file_offset(secs,rva)
    return image[off:off+n]
assert node[4]==40
actual=native(0x360939,40)
masked=bytearray(actual); objbody=bytearray(node[1]); calls=[]
for at,kind,ref in node[2]:
    assert kind==20
    target=0x360939+at+4+struct.unpack_from('<i',actual,at)[0]
    masked[at:at+4]=objbody[at:at+4]=b'\0'*4
    if at==9:
        assert target==0x307f0 and ref['name']=='?allocate@?$allocator@D@_STL@@SAPADIPBX@Z'
        proof='existing rowed raw-byte allocator'
    else:
        assert at==27 and target==0x360917
        leaf=ref['definition']
        assert leaf[4]==34 and not leaf[2]
        assert leaf[1]==native(target,34)
        proof='whole 34-byte copy leaf equals native, with no relocations'
    calls.append({'offset':at,'target':hex(target),'symbol':ref['name'],'proof':proof})
assert masked==objbody
assert any(ins.mnemonic=='push' and ins.op_str=='0x788'
           for ins in Cs(CS_ARCH_X86,CS_MODE_32).disasm(node[1][:8],0))
truth=c.RetailTruth(c.ledger())
facts=[sorted(x) for x in c.object_facts(build.obj_path(Path(source).resolve()),truth)]
i,rows=a.load([source])
refs=[[r['name'],r['target_rva'],off,kind,name,target,cls,detail] for r,off,kind,name,target,cls,detail in a.scan(i,rows)]
old=json.loads((p/'before.json').read_text())
oldcopies={x[0]:list(x[1:]) for x in old['facts'][0]}; newcopies={x[0]:list(x[1:]) for x in facts[0]}
parent=next(n for n in oldcopies if n.startswith('?_M_insert@?$hashtable@'))
resize=next(n for n in oldcopies if n.startswith('?resize@?$hashtable@'))
assert oldcopies[parent]==newcopies[parent]
assert oldcopies[resize]==newcopies[resize] and newcopies[resize][1]==220
assert [r[:6] for r in refs]==[r[:6] for r in old['refs']]
changed=[n for n in oldcopies.keys() & newcopies.keys() if oldcopies[n]!=newcopies[n]]
extra=[n for n in changed if n.startswith('??0?$pair@') or n.startswith('?allocate@?$allocator@')]
assert len(extra)==2
incoming={n:[{'caller':e[0]['name'],'offset':at} for e in entries for at,kind,ref in e[2] if ref['name']==n] for n in extra}
unreached=set(extra)
while True:
    parents={e[0]['name'] for e in entries if any(ref['name'] in unreached for at,kind,ref in e[2])}
    if parents<=unreached: break
    unreached|=parents
assert parent not in unreached and node[0]['name'] not in unreached
assert not (oldcopies.keys()-newcopies.keys()) and not (newcopies.keys()-oldcopies.keys())
assert old['facts'][1:]==facts[1:]
proof={'parent_bytes':73,'parent_complete_comdat_unchanged':True,'native_node_bytes':40,'native_payload_bytes':0x780,'allocation_bytes':0x788,'native_calls':calls,'original_resize_restored_bytes':220,'changed_copies':sorted(changed),'removed_copies':sorted(oldcopies.keys()-newcopies.keys()),'added_copies':sorted(newcopies.keys()-oldcopies.keys()),'strong_sets_identical':old['facts'][1]==facts[1],'undefined_sets_identical':old['facts'][2]==facts[2],'weak_sets_identical':old['facts'][3]==facts[3],'extra_helper_incoming':incoming,'extra_helper_incoming_component_not_reached_from_insert':sorted(unreached),'binding_qualification':refs}
# Archived receipts are immutable; print the recomputed proof below.

print(json.dumps(proof,indent=2))
