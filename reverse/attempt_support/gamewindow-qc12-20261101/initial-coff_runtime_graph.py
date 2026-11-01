from pathlib import Path
import sys,json,struct,hashlib
sys.path.insert(0,'tools')
import class_layouts
b=class_layouts.build_module()
def graph(p):
 st=p.stat();data,secs,sy=b._object_layout(str(p),st.st_mtime_ns,st.st_size)
 keep=[i+1 for i,s in enumerate(secs) if not s['name'].startswith('.debug')];indices={v:i for i,v in enumerate(keep)};selections={};weak={};ext={}
 symptr,num=struct.unpack_from('<II',data,8);i=0
 while i<num:
  off=symptr+i*18;s=sy[i];aux=data[off+17];ix=s['section']
  if s['storage']==105:
   assert aux;tag,kind=struct.unpack_from('<II',data,off+18);weak[s['name']]=[sy[tag]['name'],kind]
  if ix in indices:
   if s['storage']==2:ext[s['name']]=[indices[ix],s['value'],s['type']]
   if s['storage']==3 and s['type']==0 and aux and s['name']==secs[ix-1]['name']:
    sel=data[off+18+14];assoc=struct.unpack_from('<H',data,off+18+12)[0];selections[indices[ix]]=[sel,indices.get(assoc) if sel==5 else None]
  i+=1+aux
 out=[]
 for ix in keep:
  s=secs[ix-1];assert s['reloc_count']!=65535;rs=[]
  for j in range(s['reloc_count']):
   off,idx,kind=struct.unpack_from('<IIH',data,s['reloc_pointer']+j*10);t=sy[idx];si=t['section']
   if si in indices:
    target=['defined',indices[si],t['value']]
    if t['storage']==2:target.append(t['name'])
   elif si==0:target=['external',t['name'],t['storage'],t['type']]
   elif si<0:target=['special',si,t['name'],t['value']]
   else:raise ValueError('runtime relocation into debug section')
   rs.append([off,kind,target])
  raw=data[s['raw_pointer']:s['raw_pointer']+s['raw_size']] if s['raw_pointer'] else b''
  out.append({'name':s['name'],'size':s['raw_size'],'characteristics':s['characteristics'],'sha256':hashlib.sha256(raw).hexdigest(),'relocs':rs,'comdat':selections.get(indices[ix])})
 return {'sections':out,'extern_definitions':ext,'weak':weak}
if __name__=='__main__':
 w=Path('build/qc12-window');manifest=json.loads((w/'coff-before-manifest.json').read_text());before={f:graph(Path(p)) for f,p in manifest.items()};after={f:graph(b.obj_path(f)) for f in manifest};diff=[]
 for f in before:
  if before[f]!=after[f]:diff.append(f)
 report={'unchanged':not diff,'units':len(before),'runtime_sections':sum(len(g['sections']) for g in before.values()),'external_definitions':sum(len(g['extern_definitions']) for g in before.values()),'weak_bindings':sum(len(g['weak']) for g in before.values()),'changed':diff}
 for n,o in [('runtime-before.json',before),('runtime-after.json',after),('runtime-verdict.json',report)]: (w/n).write_text(json.dumps(o,indent=2)+'\n')
 print(json.dumps(report,indent=2));raise SystemExit(bool(diff))
