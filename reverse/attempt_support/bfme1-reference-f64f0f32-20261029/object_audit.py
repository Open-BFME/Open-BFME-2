import json, pathlib, sys, hashlib
sys.path.insert(0, 'tools')
import build, link_census
out = pathlib.Path('build/bfme1-refresh-f64f0f32')
audit = json.loads(pathlib.Path(__file__).with_name('input-audit.json').read_text())
records = {}
sources = set(audit['existing_affected_sources'])
sources.update(json.loads(pathlib.Path(__file__).with_name('final-current-dependencies.json').read_text()))
for source in sorted(sources):
    obj = build.obj_path(source)
    if not obj.exists():
        records[source] = {'missing': True}
        continue
    data = obj.read_bytes()
    symbols = list(link_census._coff_symbols(data))
    records[source] = {
        'sha256': hashlib.sha256(data).hexdigest(),
        'comdats': {name: [digest, size] for name, digest, size in link_census.comdat_bodies(obj)},
        'definitions': sorted(s['name'] for s in symbols if s['storage'] == 2 and s['section'] > 0),
        'undefined': sorted(s['name'] for s in symbols if s['storage'] == 2 and s['section'] == 0 and s['value'] == 0),
        'weak': link_census._weak_externals(data)
    }
(out/(sys.argv[1]+'-bindings.json')).write_text(json.dumps(records, indent=2)+'\n')
print('Captured', len(records), 'sources', 'missing', sum('missing' in r for r in records.values()))
