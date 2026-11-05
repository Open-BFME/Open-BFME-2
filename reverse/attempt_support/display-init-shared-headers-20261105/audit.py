import sys,csv,struct
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as c,eh_verify
src="Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit.cpp"
old=Path("build/shared-classes-20261105/display-init/original.obj");new=build.obj_path(build.ROOT/src)
a={s["name"]:(d,n) for s,b,r,d,n in c._comdat_sections(old.read_bytes())}
b={s["name"]:(d,n) for s,b,r,d,n in c._comdat_sections(new.read_bytes())}
print("old definitions",len(a),"new",len(b),"unchanged",sum(a[n]==b.get(n) for n in a))
for n in sorted(set(a)|set(b)):
 if a.get(n)!=b.get(n):print("CHANGE",n,a.get(n),b.get(n))
print("old vtables",[n for n in a if n.startswith("??_7")],"new vtables",[n for n in b if n.startswith("??_7")])
print("EH",eh_verify.verify_row(eh_verify.Image(),eh_verify.Obj(new),"?init@W3DDisplay@@UAEXXZ",0x46A50))
assert a==b,"non-debug definitions/relocations changed"
print("All previous definitions and relocation fingerprints preserved; no new definition")
im=eh_verify.Image()
for va in [0xbc6310,0xbc6264,0xbc62a0]:
 vals=struct.unpack_from("<"+"I"*(14 if va==0xbc6264 else 28),im.bytes,va-0x400000)
 print("native table",hex(va),[hex(v-0x400000) for v in vals])
