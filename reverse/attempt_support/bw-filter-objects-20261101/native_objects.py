import sys,struct,json
from pathlib import Path
sys.path.insert(0,'tools')
import build
image,sections=build.exe_image()
def words(rva,n): return [f'0x{x:08X}' for x in struct.unpack('<'+'I'*n,build.read_target_bytes(rva,4*n))]
def refs(va):
 p=struct.pack('<I',va);out=[]
 for s in sections:
  data=image[s['raw_pointer']:s['raw_pointer']+s['raw_size']];start=0
  while True:
   i=data.find(p,start)
   if i<0:break
   out.append({'section':s['name'],'operand_rva':f"0x{s['rva']+i:08X}"});start=i+1
 return out
out={'retail':str(build.EXE),'objects':[
 {'name_lead':'screenBWFilter','rva':'0x009B5B54','candidate_extent':8,'words':words(0x9B5B54,2),'vtable_rva':'0x007CF364','vtable_words':words(0x7CF364,7),'absolute_operand_references':refs(0xDB5B54)},
 {'name_lead':'screenBWFilterDOT3','rva':'0x009B5B5C','candidate_extent':8,'words':words(0x9B5B5C,2),'vtable_rva':'0x007CF380','vtable_words':words(0x7CF380,7),'absolute_operand_references':refs(0xDB5B5C)}],
 'vtable_references':{'0x00BCF364':refs(0xBCF364),'0x00BCF380':refs(0xBCF380)},
 'following_storage_words':words(0x9B5B64,9),
 'scope':'Read-only retail byte/absolute-operand evidence. Candidate extents are corroborated by two 13-byte native ctors zeroing +4 and installing the respective seven-slot table; donor inheritance is a separate naming/layout lead, not target source proof.'}
Path('build/bw-filter-objects-20261101/native.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
