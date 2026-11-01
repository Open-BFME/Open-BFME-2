import csv, json, subprocess, sys
from pathlib import Path
root = Path.cwd()
sys.path.insert(0, str(root / 'tools'))
import build, eh_verify
source = root/'Code/GameEngine/Source/Common/Rva00515Wrappers.cpp'
original = source.read_text(encoding='utf8')
old = '\tRva00211E75Callback(int callback) : Rva00211E75(&callback) {}'
assert original.count(old) == 1
changed = original.replace(old, '\tRva00211E75Callback(int callback);')
anchor = '\nextern int g_00E02EC4;'
assert changed.count(anchor) == 1
changed = changed.replace(anchor, '\nRva00211E75Callback::Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}\n'+anchor)
lab = root/'build/apt-residual-ctor-private-20261101'
lab.mkdir(exist_ok=True)
cpp, obj = lab/'probe.cpp', lab/'probe.obj'
cpp.write_text(changed, encoding='utf8')
cmd, env = build.compiler_command(source, obj)
cmd[-1] = str(cpp)
proc = subprocess.run(cmd, env=env, capture_output=True, text=True)
(lab/'compile.log').write_text(proc.stdout+proc.stderr, encoding='utf8')
assert proc.returncode == 0, proc.stdout+proc.stderr
rows = []
with (root/'reverse/functions.csv').open(encoding='utf8', newline='') as f:
    for row in csv.DictReader(f):
        if row['source'] == source.relative_to(root).as_posix(): rows.append(row)
mapping, image, coff = build.load_symbol_map(), eh_verify.Image(), eh_verify.Obj(obj)
proof = []
for row in rows:
    got = build.compile_function(row, mapping, obj)
    proof.append({'name': row['name'], 'rva': row['target_rva'],
                  'exact': got['bytes'] == got['target'] and not got['masked'] and not got['unresolved'],
                  'eh': eh_verify.verify_row(image, coff, row['name'], int(row['target_rva'],16))})
ctor = '??0Rva00211E75Callback@@QAE@H@Z'
old_b, old_r = build.read_object_symbol_bytes(build.obj_path(source), ctor)
new_b, new_r = build.read_object_symbol_bytes(obj, ctor)
result = {'method':'Private compiler_command with private absolute object; all current source rows checked, shared cache untouched.',
          'rows':proof, 'ctor_whole_raw_and_relocations_unchanged':(old_b,old_r)==(new_b,new_r),
          'ctor_size':len(new_b), 'ctor_hex':new_b.hex(), 'ctor_relocations':new_r}
(lab/'result.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
print(json.dumps(result,indent=2))
assert all(r['exact'] for r in proof) and result['ctor_whole_raw_and_relocations_unchanged']
