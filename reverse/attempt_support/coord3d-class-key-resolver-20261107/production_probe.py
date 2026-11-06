import csv,json,sys
from pathlib import Path
sys.path.insert(0,'tools')
import header_adopt_lane as H
base=Path(__file__).resolve().parent
pairs=json.loads((base/'prototype-results.json').read_text())
compared=[]
for p in pairs:
    try:
        actual=H.rekey_symbol(p['old'],'Coord3D','U')
        compared.append({'old':p['old'],'expected':p.get('new'),'actual':actual,'pass':actual==p.get('new')})
    except ValueError as exc:
        compared.append({'old':p['old'],'error':str(exc),'pass':False})
Path('build/coord3d-key-production-comparison-20261107.json').write_text(json.dumps(compared,indent=2))
print('Independent mapping comparisons:',sum(p['pass'] for p in compared),'/',len(compared))
summary={}
renames={}
refused=[]
for filename,column in [('functions.csv','name'),('symbols.csv','name'),('data_rows.csv','name'),('data_converged.csv','name')]:
    records=[]
    with (Path('reverse')/filename).open(newline='',encoding='utf-8-sig') as stream:
        for row in csv.DictReader(stream):
            name=row.get(column,'')
            if 'Coord3D@' not in name: continue
            try: new=H.rekey_symbol(name,'Coord3D','U')
            except ValueError as exc:
                refused.append({'ledger':filename,'name':name,'source':row.get('source'),'reason':str(exc)})
                continue
            if new!=name:
                records.append({'old':name,'new':new,'source':row.get('source'),'rva':row.get('target_rva',row.get('address'))})
                renames[name]=new
    summary[filename]=records
names=set()
with Path('reverse/functions.csv').open(newline='',encoding='utf-8-sig') as stream:
    for row in csv.DictReader(stream):
        if row['name'] in set(renames.values()): names.add(row['name'])
result={'counts':{k:len(v) for k,v in summary.items()},'rows':summary,'refused':refused,
        'target_names_already_in_ledger':sorted(names),
        'generated_sources':sorted({r['source'] for v in summary.values() for r in v if r['source'] and r['source'].startswith('Code/gen_')})}
Path('build/coord3d-key-ledger-closure-20261107.json').write_text(json.dumps(result,indent=2))
print(json.dumps({k:v for k,v in result.items() if k!='rows'},indent=2))
