import csv, json, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as lc
scratch=Path('build/string-insert-noinline-link-20261030')
sources={'range':'Code/Libraries/Source/STLport/Rva008312E0StringReplace.cpp','owner':'Code/GameEngine/Source/Common/BfmeS1155.cpp'}
insert='?insertRange@Rva008312E0String@@QAEXPAD00ABURva008312E0Tag@@@Z'
old_erase='?bfmeEraseV24@BfmeStrV24@@QAEXPAD0@Z'
new_erase='?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z'
proof={'rows':{},'changed_relocations':[],'insert_selection':{}}
for group,source in sources.items():
    suffix='' if group=='range' else '-owner'
    before=scratch/('before'+suffix+'.obj'); after=scratch/('after'+suffix+'.obj')
    with Path('reverse/functions.csv').open(newline='') as f:
        rows=[r for r in csv.DictReader(f) if r['source']==source]
    assert len(rows)==(2 if group=='range' else 12)
    for row in rows:
        name=row['name']; size=int(row['target_size'])
        b,br=build.read_object_symbol_bytes(before,name,code_only=True)
        a,ar=build.read_object_symbol_bytes(after,name,code_only=True)
        assert b[:size]==a[:size],name
        br=[r for r in br if 0 <= r[0] < size]
        ar=[r for r in ar if 0 <= r[0] < size]
        expected=[(o,k,new_erase if n==old_erase else n) for o,k,n in br]
        assert ar==expected,(name,br,ar)
        proof['rows'][name]={'source':source,'rva':row['target_rva'],'size':size,'raw_bytes_identical':True}
        for old,new in zip(br,ar):
            if old!=new: proof['changed_relocations'].append({'name':name,'old':old,'new':new})
    for stage,path in [('before',before),('after',after)]:
        data=path.read_bytes(); symbol=next((x for x in build.read_object_symbols(data) if x['name']==insert and x['section']>0),None)
        proof['insert_selection'][group+'-'+stage]=lc._comdat_selections(data)[symbol['section']] if symbol else None
assert proof['insert_selection']=={'range-before':0,'range-after':2,'owner-before':None,'owner-after':2},proof['insert_selection']
assert len(proof['changed_relocations'])==1
proof['scope']='14 existing code rows; raw bytes and relocation identities except deliberate erase binding; range insert definition becomes ANY; new owner copy is ANY; no census credit'
(scratch/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print('14 existing rows retain raw bytes; sole relocation change selects the existing real erase owner; range insert changes strong non-COMDAT->ANY; new owner copy is ANY.')
