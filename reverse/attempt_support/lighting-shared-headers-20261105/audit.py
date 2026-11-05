import sys,struct,csv
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as c,eh_verify
src="Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayLightingScale.cpp"
old=Path("build/shared-classes-20261105/lighting/original.obj");new=build.obj_path(build.ROOT/src)
a={s["name"]:(d,n) for s,b,r,d,n in c._comdat_sections(old.read_bytes())}
b={s["name"]:(d,n) for s,b,r,d,n in c._comdat_sections(new.read_bytes())}
removed=sorted(set(a)-set(b));changed=[n for n in a if n in b and a[n]!=b[n]];added=sorted(set(b)-set(a))
print("old definitions",len(a),"new",len(b),"retained exact",sum(a[n]==b.get(n) for n in a))
print("removed",removed,"changed",changed,"added",[(n,b[n]) for n in added])
assert not removed and not changed
for n in added:
 assert n=="??0Vector3@@QAE@MMM@Z",n
 assert b[n]==a["??0Rva000443BAVec@@QAE@MMM@Z"]
 print("new Vector3 value ctor equals existing RGB value ctor",b[n])
print("emitted vtables",[n for n in b if n.startswith("??_7")]);assert not any(n.startswith("??_7") for n in b)
m=build.load_symbol_map()
with open("reverse/functions.csv",newline="") as f: rows=[r for r in csv.DictReader(f) if r["source"]==src]
for r in rows:
 p=build.compile_function(r,m,new);assert p["bytes"]==p["target"] and not p["unresolved"]
 print("EXACT",r["target_rva"],r["target_size"])
im=eh_verify.Image();target=struct.unpack_from("<I",im.bytes,0x7c63c8+6*4)[0]-0x400000
print("retail RTS3DScene primary slot6",hex(target));assert target==0x6e265
print("canonical infantry ambient +0x144 and native three-float snapshot retained by exact callers")
