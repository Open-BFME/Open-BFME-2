import csv,json,sys,re
from pathlib import Path
sys.path.insert(0,'tools')
import build
scratch=Path('build/fireweapon-primary-link-20261030')
paths={'ctor':'Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp','dtor':'Code/GameEngine/Source/Common/Rva00589079Derived.cpp'}
old='?Rva00482E4BGet@@YAHXZ';new='?GetSnapshotName@FireWeaponWhenDeadBehavior@@UBEPBDXZ'
def read(row,obj):
    name=build.ledger_object_symbol(row);target=build.read_target_bytes(int(row['target_rva'],16),int(row['target_size']))
    if build.is_funclet_row(row,name):body,refs,note=build.read_funclet(row,name,obj,target)
    else:body,refs=build.read_object_symbol_bytes(obj,name,code_only=True)
    size=int(row['target_size'])
    return body[:size],[r for r in refs if 0<=r[0]<size]
with Path('reverse/functions.csv').open(newline='') as f:rows=[r for r in csv.DictReader(f) if r['source'] in paths.values()]
assert len(rows)==12
proof=[]
symbols=build.load_symbol_map()
old_update='?xfer@UpdateModule@@QAEXPAVXfer@@@Z'
new_update='?xfer@UpdateModule@@UAEXPAVXfer@@@Z'
assert symbols[old_update]==symbols[new_update]==[0x44DF9F]
for row in rows:
    group=next(k for k,v in paths.items() if v==row['source'])
    before={**row,'name':old} if row['name']==new else row
    a,ar=read(row,build.obj_path(Path(row['source'])))
    b,br=read(before,scratch/('before-'+group+'.obj'))
    assert a==b,(row['name'],a.hex(),b.hex())
    expected=[(o,k,new_update if n==old_update else n) for o,k,n in br]
    if row['name'].startswith('__ehhandler$'):
        assert len(br)==len(ar)==2 and br[0][:2]==ar[0][:2]==(1,6)
        assert re.fullmatch(r'\$T[0-9]+',br[0][2]) and re.fullmatch(r'\$T[0-9]+',ar[0][2])
        expected[0]=ar[0]  # FuncInfo label spelling; full graph checked by eh_verify.
    assert ar==expected,(row['name'],br,ar)
    proof.append({'name':row['name'],'old_name':before['name'],'rva':row['target_rva'],'size':row['target_size'],'raw_bytes_preserved':True,'relocations_preserved_except_existing_update_xfer_twin':True,'relocation_changes':[(b,a) for b,a in zip(br,ar) if b!=a]})
(scratch/'row-proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print('All 12 original bodies preserve raw bytes; only row relocation spelling changes QAE->existing UAE UpdateModule xfer at 0044DF9F plus FuncInfo label renumbering; sole identity correction is the six-byte getter; funclet read from exact parent EH graph.')
