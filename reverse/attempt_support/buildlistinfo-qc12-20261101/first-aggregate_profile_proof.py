from pathlib import Path
import sys,json,struct,collections
sys.path.insert(0,'tools')
import class_layouts
sys.path.insert(0,'build/qc12-buildlist')
from coff_runtime_graph import graph
b=class_layouts.build_module();w=Path('build/qc12-buildlist')
def directives(p):
 st=p.stat();data,secs,sy=b._object_layout(str(p),st.st_mtime_ns,st.st_size)
 return [t for sec in secs if sec['name']=='.drectve' for t in data[sec['raw_pointer']:sec['raw_pointer']+sec['raw_size']].decode('ascii').split()]
def aliases(ds):return {d for d in ds if d.lower().startswith(('/alternatename:','-alternatename:'))}
m=json.loads((w/'coff-before-manifest.json').read_text());before={f:graph(Path(p)) for f,p in m.items()};after={f:graph(b.obj_path(f)) for f in m}
db={f:directives(Path(p)) for f,p in m.items()};da={f:directives(b.obj_path(f)) for f in m}
all_before=set().union(*(aliases(x) for x in db.values()));all_after=set().union(*(aliases(x) for x in da.values()))
checks=[]
for f in m:
 a=json.loads(json.dumps(before[f]));z=json.loads(json.dumps(after[f]))
 for g in (a,z):
  for sec in g['sections']:
   if sec['name']=='.drectve':sec.pop('size');sec.pop('sha256')
 added=aliases(da[f])-aliases(db[f]);removed=aliases(db[f])-aliases(da[f])
 ok=(a==z and not removed and added<=all_before and sorted(x for x in db[f] if x not in aliases(db[f]))==sorted(x for x in da[f] if x not in aliases(da[f])))
 checks.append({'file':f,'runtime_and_virtual_providers_exact':a==z,'added_duplicate_aliases':sorted(added),'removed_aliases':sorted(removed),'passed':ok})
report={'passed':all(x['passed'] for x in checks) and all_before==all_after,'aggregate_alias_bindings_unchanged':all_before==all_after,'units':len(m),'runtime_sections':sum(len(g['sections']) for g in before.values()),'external_definitions':sum(len(g['extern_definitions']) for g in before.values()),'weak_bindings':sum(len(g['weak']) for g in before.values()),'unit_checks':checks}
(w/'aggregate-profile-verdict.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2));raise SystemExit(not report['passed'])
