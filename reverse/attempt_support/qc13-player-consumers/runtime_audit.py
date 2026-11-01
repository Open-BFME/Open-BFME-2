import sys,struct,json,hashlib
from pathlib import Path
sys.path.insert(0,str(Path.cwd()/'tools'))
import class_layouts
b=class_layouts.build_module()
def runtime(p):
 d=p.read_bytes(); sy=b.read_object_symbols(d);st=20;result=[]
 count=b.u16(d,2)
 sn={i+1:d[20+40*i:28+40*i].rstrip(bytes([0])).decode() for i in range(count)}
 identities={}
 for sec in sn:
  stable=sorted((x['name'],x['value']) for x in sy if x['section']==sec and x['name'] and x['name']!=sn[sec] and not x['name'].startswith(('$L','$T')))
  if stable:identities[sec]=json.dumps(stable)
 for _ in range(5):
  incoming={}
  for sec in sn:
   if sec not in identities:continue
   z=20+40*(sec-1);rp=b.u32(d,z+24)
   for j in range(b.u16(d,z+32)):
    off,idx,typ=struct.unpack_from('<IIH',d,rp+j*10);target=sy[idx]['section']
    if target>0 and target not in identities:incoming.setdefault(target,[]).append((identities[sec],off,typ,sy[idx]['value']))
  if not incoming:break
  identities.update({sec:json.dumps(sorted(v)) for sec,v in incoming.items()})
 def local(x):
  assert x['section'] in identities,(p,x)
  return 'LOCAL:'+identities[x['section']]+':'+str(x['value'])

 for i in range(b.u16(d,2)):
  z=st+40*i;name=d[z:z+8].rstrip(bytes([0])).decode();flags=b.u32(d,z+36)
  if name.startswith('.debug') or name=='.drectve':continue
  if not flags & 0xE0:continue
  sz=b.u32(d,z+16);ptr=b.u32(d,z+20);raw=bytearray(d[ptr:ptr+sz]) if ptr else bytearray(); rel=[]
  rp=b.u32(d,z+24)
  for j in range(b.u16(d,z+32)):
   off,idx,typ=struct.unpack_from('<IIH',d,rp+j*10)
   rel.append((off,typ,(local(sy[idx]) if sy[idx]['name'].startswith(('$L','$T')) and sy[idx].get('storage')==3 else sy[idx]['name']),sy[idx]['value']))
  defs=sorted(((local(x) if x['name'].startswith(('$L','$T')) and x['storage']==3 else x['name']),x['value'],x['storage'],x['type']) for x in sy if x['section']==i+1 and x['name'] not in [name] and x['name'])
  result.append([name,flags,sz,raw.hex(),rel,defs])
 weak=[];base=b.u32(d,8)
 for i,x in enumerate(sy):
  if x.get('storage')==105:
   ix,kind=struct.unpack_from('<II',d,base+(i+1)*18);weak.append((x['name'],sy[ix]['name'],kind))
 return sorted(result,key=lambda r:json.dumps(r)),sorted(weak)
if __name__=='__main__':
 ss=json.loads(Path('/tmp/qc13-player-trials.json').read_text());out=[]
 for x in ss:
  if x['why'] is not None:continue
  s=x['source'];old=(Path('/tmp/qc13-player-base')/s).with_suffix('.obj');new=b.obj_path(s)
  a,c=runtime(old),runtime(new);out.append({'source':s,'identical':a==c,'sections_before':len(a[0]),'sections_after':len(c[0]),'weak_before':a[1],'weak_after':c[1]})
 print(json.dumps(out,indent=1))
