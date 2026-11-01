import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import allowed_symbols
import build
import permute

root = Path.cwd()
rel = 'Code/Libraries/Source/WWVegas/WW3D2/texturepacker.cpp'
work = root / 'build/weather-reset-owner-20261101/binding-control'
work.mkdir(exist_ok=True)
old = subprocess.check_output(['git', 'show', 'de75f363a4:' + rel]).decode()
old_lines = old.splitlines(keepends=True)
assert old_lines[0].startswith('// cl:')
old_lines[0] = '// cl: ' + ' '.join(build.source_extra_flags(root / rel)) + '\n'
old = ''.join(old_lines)
scratch = work / 't1.cpp'
scratch.write_text(old)
old_command, _ = build.compiler_command(scratch, scratch.with_suffix('.obj'))
real_command, _ = build.compiler_command(root / rel, build.obj_path(root / rel))
def options(command):
    return command[:-2]
assert options(old_command) == options(real_command), (old_command, real_command)
scorer = permute.Scorer('0x001711A6', '?rva001711a6@Rva00171024@@QAEXXZ', 892, work)
score, exact = scorer.score(old)
old_obj = allowed_symbols.Obj(scratch.with_suffix('.obj'))
new_obj = allowed_symbols.Obj(build.obj_path(root / rel))
symbol = '?insert_equal@?$_Rb_tree@IU?$pair@$$CBIVAssetReference@@@_STL@@U?$_Select1st@U?$pair@$$CBIVAssetReference@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIVAssetReference@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIVAssetReference@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIVAssetReference@@@_STL@@@2@@2@ABU?$pair@$$CBIVAssetReference@@@2@@Z'
def body(obj):
    raw, extent, relocs = obj.body(obj.by_name[symbol])
    return dict(raw=raw.hex(), extent=extent,
                relocations=[dict(offset=w, kind=k, symbol=r['name'], storage=r['storage'], value=r['value'])
                             for w, k, r in relocs])
before, after = body(old_obj), body(new_obj)
result = dict(base='de75f363a4', source=rel, same_compiler_options=True,
              original_parent_score=score, original_parent_exact=exact,
              original_parent_unresolved=scorer.unresolved,
              suspect_symbol=symbol, control=before, current=after,
              identical_definition=before == after)
(work / 'result.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
assert exact and not scorer.unresolved and before == after
