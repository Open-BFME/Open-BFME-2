import sys,csv
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as census,eh_verify
source="Code/Libraries/Source/WWVegas/WWMath/tcbspline.cpp"
obj=build.obj_path(build.ROOT/source)
old=Path("build/tcb-native-link-20261102/original.obj")
newparts={s["name"]:(body,relocs,digest,size) for s,body,relocs,digest,size in census._comdat_sections(obj.read_bytes())}
oldparts={s["name"]:(body,relocs,digest,size) for s,body,relocs,digest,size in census._comdat_sections(old.read_bytes())}
retained=[n for n in oldparts if n in newparts and oldparts[n][2:]==newparts[n][2:]]
changed=[n for n in oldparts if n in newparts and oldparts[n][2:]!=newparts[n][2:]]
removed=set(oldparts)-set(newparts)
print("COMDAT unchanged",len(retained),"changed",len(changed),"removed",len(removed),"new",len(set(newparts)-set(oldparts)))
for n in changed: print("CHANGED",n,oldparts[n][3],"->",newparts[n][3])
assert not removed
for n in retained:
 if n.startswith("??_7"): print("TABLE unchanged",n,newparts[n][2:])
def defs(p):
 return {s["name"] for s in census._coff_symbols(p.read_bytes()) if s["storage"]==2 and s["section"]>0}
olddefs,newdefs=defs(old),defs(obj)
print("external definitions",len(olddefs),"->",len(newdefs),"removed",sorted(olddefs-newdefs),"added",sorted(newdefs-olddefs))
assert not olddefs-newdefs
m=build.load_symbol_map()
with open("reverse/functions.csv",newline="") as f: rows=[r for r in csv.DictReader(f) if r["source"]==source]
for r in rows:
 p=build.compile_function(r,m,obj)
 assert p["bytes"]==p["target"] and not p["unresolved"]
 print("existing row EXACT",r["target_rva"],r["target_size"])
image=eh_verify.Image(); parsed=eh_verify.Obj(obj)
for name,rva,size in [("?Resize@?$VectorClass@VTCBClass@TCBSpline3DClass@@@@UAE_NHPBVTCBClass@TCBSpline3DClass@@@Z",0xF0BF1,227),("??0?$VectorClass@VTCBClass@TCBSpline3DClass@@@@QAE@HPBVTCBClass@TCBSpline3DClass@@@Z",0xF0D2F,150),("??0TCBClass@TCBSpline3DClass@@QAE@XZ",0x47A6A9,3)]:
 r={"name":name,"target_rva":hex(rva),"target_size":str(size),"source":source,"notes":"","export_rva":""}
 p=build.compile_function(r,m,obj)
 print("native helper",hex(rva),size,"exact",p["bytes"]==p["target"],"unresolved",p["unresolved"])
 assert p["bytes"]==p["target"] and not p["unresolved"]
 verdict=eh_verify.verify_row(image,parsed,name,rva)
 print("native EH",hex(rva),verdict)
 assert verdict is None or verdict[0]=="EXACT"
