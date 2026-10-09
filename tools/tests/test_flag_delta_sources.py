import importlib.util
import os
import subprocess
from pathlib import Path
import pytest
ROOT = Path(os.environ.get('BFME_REVIEW_ROOT', str(Path(__file__).resolve().parents[2])))
CANDIDATE = Path(os.environ.get('BFME_FLAG_REVIEW_CANDIDATE', str(ROOT / 'tools/flag_delta_sources.py')))
spec = importlib.util.spec_from_file_location('flag_review', CANDIDATE)
fd = importlib.util.module_from_spec(spec); spec.loader.exec_module(fd)
HEADER = 'name,export_rva,target_rva,target_size,source,status,notes\n'
A='Code/Engine/A.cpp'; B='Code/Engine/B.c'; ASM='Code/Engine/X.asm'; FOREIGN='reference/Donor.cpp'
REGION='rva_start,rva_end,opt,arch,tune,n_funcs,n_opt_evidence\n0x1000,0x2000,O1,SSE,G7,100,10\n'
OVERRIDE='source,flags,rows,default_lost,reason\n'
def row(source,rva=0x1100,size=20): return f'f,,0x{rva:x},{size},{source},matched,\n'
def git(root,*args):
    got=subprocess.run(['git',*args],cwd=root,capture_output=True,text=True)
    assert got.returncode==0,got.stderr
    return got.stdout.strip()
def write(root,path,text):
    p=root/path;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(text)
def commit(root):
    git(root,'add','-A');git(root,'commit','-qm','Fixture');return git(root,'rev-parse','HEAD')
@pytest.fixture
def repo(tmp_path,monkeypatch):
    monkeypatch.setenv('GIT_CONFIG_GLOBAL',os.devnull);monkeypatch.setenv('GIT_CONFIG_NOSYSTEM','1')
    git(tmp_path,'init','-q');git(tmp_path,'config','user.name','Fixture');git(tmp_path,'config','user.email','fixture@example.invalid')
    write(tmp_path,'reverse/functions.csv',HEADER+row(A)+row(B)+row(ASM)+row(FOREIGN))
    write(tmp_path,fd.REGIONS,REGION);write(tmp_path,fd.OVERRIDES,OVERRIDE)
    write(tmp_path,'tools/build.py','original\n');write(tmp_path,'tools/flag_defaults.py','original\n')
    base=commit(tmp_path);monkeypatch.setattr(fd,'ROOT',tmp_path);return tmp_path,base
@pytest.mark.parametrize('path', ['tools/flag_defaults.py',fd.REGIONS])
def test_global_codegen_change_selects_untouched_managed_only(repo,path):
    root,base=repo
    write(root,path,'changed\n' if path.endswith('.py') else REGION.replace('O1','O2'))
    assert fd.select(base,commit(root))==[A,B]
def test_build_driver_selects_all_supported_compiled_sources(repo):
    root,base=repo;write(root,'tools/build.py','changed\n');assert fd.select(base,commit(root))==sorted([A,B,ASM,FOREIGN])
@pytest.mark.parametrize('remove',[False,True])
def test_override_add_or_remove_selects_only_its_source(repo,remove):
    root,base=repo;entry=f'{A},-O2,1,1,lost\n'
    write(root,fd.OVERRIDES,OVERRIDE+entry)
    if remove:base=commit(root);write(root,fd.OVERRIDES,OVERRIDE)
    assert fd.select(base,commit(root))==[A]
@pytest.mark.parametrize('kind',['size','rva','delete-sibling'])
def test_vote_change_even_removed_row_selects_remaining_source(repo,kind):
    root,base=repo
    if kind=='delete-sibling':
        write(root,fd.LEDGER,HEADER+row(A)+row(A,0x1200)+row(B)+row(ASM));base=commit(root)
    changed=row(A,size=99) if kind=='size' else row(A,rva=0x1400) if kind=='rva' else row(A)
    write(root,fd.LEDGER,HEADER+changed+row(B)+row(ASM));assert fd.select(base,commit(root))==[A]
def test_semantically_equal_region_and_ledger_reorder_excludes(repo):
    root,base=repo;write(root,fd.LEDGER,HEADER+row(FOREIGN)+row(ASM)+row(B)+row(A));write(root,fd.REGIONS,REGION.replace('\n','\r\n'))
    assert fd.select(base,commit(root))==[]
@pytest.mark.parametrize('path',[fd.LEDGER,fd.REGIONS,fd.OVERRIDES])
def test_malformed_snapshot_refuses(repo,path):
    root,base=repo;write(root,path,'broken\n');tip=commit(root)
    with pytest.raises(fd.SnapshotError):fd.select(base,tip)
def test_invalid_git_revision_refuses(repo):
    with pytest.raises(fd.SnapshotError,match='Git failed'):fd.select('absent-review-ref',repo[1])
def test_large_global_selection_is_complete_sorted_and_unique(repo):
    root,base=repo;names=[f'Code/Engine/Unit{i:04}.cpp' for i in range(1500)]
    write(root,fd.LEDGER,HEADER+''.join(row(n) for n in names));base=commit(root)
    write(root,'tools/flag_defaults.py','changed\n');assert fd.select(base,commit(root))==sorted(names)

sys_path = str(ROOT / 'tools/tests')
import sys
sys.path.insert(0, sys_path)
from test_hook_fail_closed import repo as hook_repo, SOURCE
HOOK = Path(os.environ.get('BFME_FLAG_REVIEW_HOOK', str(ROOT / '.githooks/pre-push')))
@pytest.fixture
def hooked(hook_repo):
    write(hook_repo,'tools/flag_delta_sources.py',CANDIDATE.read_text())
    git(hook_repo,'add','tools/flag_delta_sources.py');git(hook_repo,'commit','-qm','Seed selector')
    return hook_repo

def push(root,base,tip):
    return subprocess.run(['bash',str(HOOK)],cwd=root,input=f'refs/heads/master {tip} refs/heads/master {base}\n',text=True,capture_output=True,timeout=60)

def test_real_hook_verifies_untouched_source_for_global_flag_change(hooked):
    base=git(hooked,'rev-parse','HEAD');write(hooked,'tools/flag_defaults.py','raise SystemExit(0) # change\n')
    tip=commit(hooked);got=push(hooked,base,tip)
    assert got.returncode==0,got.stderr
    import json
    calls=[json.loads(x) for x in (hooked/'build-calls.jsonl').read_text().splitlines()]
    assert calls==[[SOURCE]]

def test_real_hook_refuses_selector_producer_failure(hooked):
    base=git(hooked,'rev-parse','HEAD');write(hooked,'tools/flag_delta_sources.py','raise SystemExit(9)\n')
    got=push(hooked,base,commit(hooked))
    assert got.returncode==1 and 'flag_delta_sources' in got.stderr
    assert not (hooked/'build-calls.jsonl').exists()

def test_real_hook_large_global_selection_uses_bounded_chunks(hooked):
    names=[f'Code/GameEngine/Source/Common/LongDirectoryName/Unit{i:04}.cpp' for i in range(1500)]
    for source in names:write(hooked,source,'// fixture\n')
    write(hooked,'reverse/functions.csv',HEADER+''.join(row(n) for n in names));base=commit(hooked)
    write(hooked,'tools/flag_defaults.py','raise SystemExit(0) # changed flags\n')
    got=push(hooked,base,commit(hooked));assert got.returncode==0,got.stderr
    import json
    calls=[json.loads(x) for x in (hooked/'build-calls.jsonl').read_text().splitlines()]
    assert len(calls)>1 and sorted(s for call in calls for s in call)==sorted(names)
    assert all(sum(2*len(s.encode())+3 for s in call)<=24000 for call in calls)

def test_legacy_note_quotes_and_empty_unmatched_source_are_accepted(repo):
    root,base=repo
    # Same permissive quote behavior as the authoritative ledger reader.
    text=HEADER+row(A).rstrip('\n')+'legacy "quoted" prose\n'+'unused,,,,,unmatched,\n'
    write(root,fd.LEDGER,text);base=commit(root)
    write(root,'notes.txt','Evidence\n')
    assert fd.select(base,commit(root))==[]

@pytest.mark.parametrize('source',['Code/Bad\x00.cpp','Code/Bad\n.cpp'])
def test_nul_and_multiline_matched_paths_refuse(repo,source):
    root,base=repo
    import io,csv
    out=io.StringIO();writer=csv.writer(out);writer.writerow(['name','export_rva','target_rva','target_size','source','status','notes']);writer.writerow(['f','','0x1100','10',source,'matched',''])
    write(root,fd.LEDGER,out.getvalue());rev=commit(root)
    with pytest.raises(fd.SnapshotError):fd.select(base,rev)

def test_symlink_flag_snapshot_refuses(repo):
    root,base=repo
    (root/fd.OVERRIDES).unlink();(root/fd.OVERRIDES).symlink_to('other.csv')
    with pytest.raises(fd.SnapshotError,match='regular file'):fd.select(base,commit(root))
