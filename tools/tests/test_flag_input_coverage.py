"""Real-Git acceptance tests for compiler-input source selection and binding."""
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import pytest
sys.path.insert(0,str(Path(__file__).parent))
from test_flag_delta_sources import repo, hook_repo, hooked, fd, write, commit, git, HEADER, row, A, B, ASM, FOREIGN, SOURCE
ROOT = Path(os.environ.get('BFME_REVIEW_ROOT', str(Path(__file__).resolve().parents[2])))
GUARD = Path(os.environ.get('BFME_GUARD_REVIEW_CANDIDATE', str(ROOT / 'tools/ledger_guard.py')))
spec=importlib.util.spec_from_file_location('binding_review', GUARD)
G=importlib.util.module_from_spec(spec);spec.loader.exec_module(G)
DATA_HEADER='name,address,address_kind,size,section,source,status,evidence,model\n'
DATA_SOURCE='Code/Engine/DataOnly.cpp'
DATA=DATA_HEADER+f'g,0x1100,rva,4,.data,{DATA_SOURCE},matched,fixture,test\n'
HOOK = Path(os.environ.get('BFME_FLAG_REVIEW_HOOK', str(ROOT / '.githooks/pre-push')))

@pytest.fixture
def bound(repo,monkeypatch):
    root,base=repo;monkeypatch.setattr(G,'ROOT',root);return root,base

@pytest.mark.parametrize('driver',['tools/build.py','tools/flag_defaults.py','build.sh','build.cmd'])
def test_global_inputs_select_data_only_unit(repo,driver):
    root,base=repo;write(root,fd.DATA_ROWS,DATA);write(root,DATA_SOURCE,'int g = 1;\n');base=commit(root)
    write(root,driver,'changed\n');selected=fd.select(base,commit(root))
    expected=[A,B,DATA_SOURCE] if driver=='tools/flag_defaults.py' else [A,B,ASM,FOREIGN,DATA_SOURCE]
    assert selected==sorted(expected)

@pytest.mark.parametrize('raw',[b'broken\n',(DATA_HEADER+DATA_HEADER).encode(),DATA_HEADER.encode()+b'x,y\n',DATA_HEADER.encode()+b'g,0,rva,4,.data,Code/Bad\xff.cpp,matched,x,x\n'])
def test_malformed_data_ledger_refuses(repo,raw):
    root,base=repo;p=root/fd.DATA_ROWS;p.write_bytes(raw);tip=commit(root)
    with pytest.raises(fd.SnapshotError):fd.select(base,tip)

def test_data_ledger_symlink_refuses(repo):
    root,base=repo;(root/fd.DATA_ROWS).symlink_to('functions.csv')
    with pytest.raises(fd.SnapshotError,match='regular file'):fd.select(base,commit(root))

@pytest.mark.parametrize('path',G.COMPILER_INPUTS)
@pytest.mark.parametrize('stage',[False,True])
def test_push_refuses_edited_input_even_when_staged(bound,path,stage):
    root,base=bound;write(root,path,'seeded original\n');base=commit(root);write(root,path,'different\n')
    if stage:git(root,'add',path)
    assert G.main(['--commit',base])==1
    if stage: assert G.main(['--staged'])==0
    else: assert G.main(['--staged'])==1

@pytest.mark.parametrize('path',G.COMPILER_INPUTS)
def test_push_refuses_deleted_input(bound,path):
    root,base=bound;write(root,path,'seeded original\n');base=commit(root);(root/path).unlink()
    assert G.main(['--commit',base])==1

@pytest.mark.parametrize('path',['build.cmd','reverse/flag_overrides.csv'])
def test_absent_optional_input_untracked_shadow_refuses(bound,path):
    root,base=bound
    if (root/path).exists():git(root,'rm',path);base=commit(root)
    assert G.main(['--commit',base])==0
    write(root,path,'untracked input\n');assert G.main(['--commit',base])==1
    assert G.main(['--staged'])==1

def test_input_symlink_refuses_even_identical_bytes(bound):
    root,base=bound;path='tools/flag_defaults.py';(root/'same.txt').write_bytes((root/path).read_bytes())
    (root/path).unlink();(root/path).symlink_to('../same.txt')
    assert G.main(['--commit',base])==1

def test_committed_input_symlink_refuses(bound):
    root,base=bound;path='tools/flag_defaults.py';(root/path).unlink();(root/path).symlink_to('build.py');tip=commit(root)
    assert G.main(['--commit',tip])==1

def test_missing_input_blob_refuses(bound):
    root,base=bound;oid=git(root,'rev-parse',base+':tools/flag_defaults.py')
    (root/'.git/objects'/oid[:2]/oid[2:]).unlink()
    assert G.main(['--commit',base])==1

def test_initial_index_without_optional_inputs_is_valid(tmp_path,monkeypatch):
    git(tmp_path,'init','-q');monkeypatch.setattr(G,'ROOT',tmp_path)
    assert G.main(['--staged'])==0

def test_invalid_commit_refuses(bound):
    with pytest.raises(SystemExit):G.main(['--commit','unknown-ref'])

@pytest.fixture
def bound_hooked(hooked):
    write(hooked,'tools/ledger_guard.py',GUARD.read_text())
    commit(hooked);return hooked

def push(root,base,tip,new_branch=False):
    remote='0'*40 if new_branch else base
    if new_branch:git(root,'update-ref','refs/remotes/origin/master',base)
    return subprocess.run(['bash',str(HOOK)],cwd=root,input=f'refs/heads/master {tip} refs/heads/master {remote}\n',capture_output=True,text=True,timeout=60)

def calls(root):
    p=root/'build-calls.jsonl';return [json.loads(s) for s in p.read_text().splitlines()] if p.exists() else []

@pytest.mark.parametrize('new_branch',[False,True])
def test_actual_hook_selects_data_only_global_change(bound_hooked,new_branch):
    root=bound_hooked;write(root,fd.DATA_ROWS,DATA);write(root,DATA_SOURCE,'int g = 1;\n');base=commit(root)
    write(root,'tools/flag_defaults.py','raise SystemExit(0) # changed flags\n');got=push(root,base,commit(root),new_branch)
    assert got.returncode==0,got.stderr
    assert sorted(s for c in calls(root) for s in c)==sorted([SOURCE,DATA_SOURCE])

@pytest.mark.parametrize('path',['tools/flag_defaults.py','reverse/flag_overrides.csv',fd.REGIONS,'build.cmd'])
@pytest.mark.parametrize('stage',[False,True])
def test_actual_hook_refuses_wrong_snapshot_before_compilation(bound_hooked,path,stage):
    root=bound_hooked;write(root,path,'seeded original\n');base=commit(root)
    write(root,'tools/flag_defaults.py','raise SystemExit(0) # committed change\n');tip=commit(root)
    write(root,path,'different uncommitted input\n')
    if stage:git(root,'add',path)
    got=push(root,base,tip)
    assert got.returncode==1 and 'ledger_guard' in got.stderr
    assert calls(root)==[]

def test_actual_hook_refuses_selector_failure(bound_hooked):
    root=bound_hooked;base=git(root,'rev-parse','HEAD');write(root,'tools/flag_delta_sources.py','raise SystemExit(9)\n')
    got=push(root,base,commit(root));assert got.returncode==1 and 'flag_delta_sources' in got.stderr
    assert calls(root)==[]

def test_actual_hook_preserves_name_dependents(bound_hooked):
    root=bound_hooked;base=git(root,'rev-parse','HEAD');write(root,'name-deps.txt',SOURCE+'\n');write(root,'notes.txt','evidence\n')
    got=push(root,base,commit(root));assert got.returncode==0,got.stderr
    assert calls(root)==[[SOURCE]]

def test_actual_hook_committed_override_removal_verifies_owner(bound_hooked):
    root=bound_hooked
    write(root,fd.REGIONS,'rva_start,rva_end,opt,arch,tune,n_funcs,n_opt_evidence\n0x1000,0x2000,O1,SSE,G7,100,10\n')
    write(root,fd.OVERRIDES,'source,flags,rows,default_lost,reason\n'+f'{SOURCE},-O2,1,1,fixture\n')
    base=commit(root);git(root,'rm',fd.OVERRIDES);got=push(root,base,commit(root))
    assert got.returncode==0,got.stderr
    assert calls(root)==[[SOURCE]]

def test_actual_hook_retains_eh_and_replay_after_global_selection(bound_hooked):
    root=bound_hooked;write(root,fd.DATA_ROWS,DATA);write(root,DATA_SOURCE,'int g = 1;\n')
    write(root,'tools/eh_verify.py', 'import sys,pathlib\nif "--sources-from" in sys.argv: pathlib.Path("eh-selected.bin").write_bytes(sys.stdin.buffer.read())\n')
    write(root,'tools/replay_check.py', 'import sys,pathlib\npathlib.Path("replay-called.txt").write_text(" ".join(sys.argv[1:]))\n')
    base=commit(root);write(root,'tools/flag_defaults.py','raise SystemExit(0) # changed flags\n')
    got=push(root,base,commit(root));assert got.returncode==0,got.stderr
    assert sorted(p.decode() for p in (root/'eh-selected.bin').read_bytes().split(b'\0') if p)==sorted([SOURCE,DATA_SOURCE])
    assert (root/'replay-called.txt').read_text().startswith('--shadow --range ')

def test_missing_data_object_refuses_selector(repo):
    root,base=repo;write(root,fd.DATA_ROWS,DATA);tip=commit(root)
    oid=git(root,'rev-parse',tip+':'+fd.DATA_ROWS);(root/'.git/objects'/oid[:2]/oid[2:]).unlink()
    with pytest.raises(fd.SnapshotError,match='Git failed'):fd.select(base,tip)

def test_corrupt_index_refuses_guard(bound):
    root,base=bound;(root/'.git/index').write_bytes(b'corrupt index')
    with pytest.raises(SystemExit):G.main(['--staged'])

def test_unmerged_compiler_input_refuses_guard(bound):
    root,base=bound;path='tools/flag_defaults.py';oid=git(root,'rev-parse',base+':'+path)
    git(root,'update-index','--force-remove',path)
    subprocess.run(['git','-C',str(root),'update-index','--index-info'],check=True,
        input=f'100644 {oid} 1\t{path}\n100644 {oid} 2\t{path}\n'.encode())
    assert G.main(['--staged'])==1

def test_same_start_region_reorder_preserves_actual_resolver_semantics(repo,monkeypatch):
    root,base=repo
    header='rva_start,rva_end,opt,arch,tune,n_funcs,n_opt_evidence\n'
    first='0x1000,0x2000,O1,SSE,G7,100,10\n'
    second='0x1000,0x2000,O2,x87,G6,100,10\n'
    write(root,fd.REGIONS,header+first+second);base=commit(root)
    spec=importlib.util.spec_from_file_location('actual_flag_defaults_ties',ROOT / 'tools/flag_defaults.py')
    resolver=importlib.util.module_from_spec(spec);spec.loader.exec_module(resolver)
    monkeypatch.setattr(resolver,'ROOT',root)
    monkeypatch.setattr(resolver,'REGIONS',root/fd.REGIONS)
    monkeypatch.setattr(resolver,'FUNCTIONS',root/fd.LEDGER)
    monkeypatch.setattr(resolver,'OVERRIDES',root/fd.OVERRIDES)
    monkeypatch.setenv('FLAG_DEFAULTS','on')
    before=resolver.apply(root/A,[])
    assert before==['-O2']
    write(root,fd.REGIONS,header+second+first);tip=commit(root)
    resolver._cache.clear();after=resolver.apply(root/A,[])
    assert after==['-O1','-arch:SSE','-G7']
    assert fd.select(base,tip)==[A,B]

@pytest.mark.parametrize('rowtext',['f,,0x1100,20,Code/Engine/A.cpp,matched\n','f,,0x1100,20,Code/Engine/A.cpp\n'])
def test_missing_any_ledger_field_refuses_even_in_old_snapshot(repo,rowtext):
    root,base=repo;write(root,fd.LEDGER,HEADER+rowtext);bad=commit(root)
    write(root,fd.LEDGER,HEADER+row(A));tip=commit(root)
    with pytest.raises(fd.SnapshotError,match='malformed ledger row'):fd.select(bad,tip)
