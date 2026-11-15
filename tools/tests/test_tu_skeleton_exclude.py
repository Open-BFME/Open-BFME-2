"""Excluding candidates never excludes admission checks or reuses a saved plan."""
import hashlib
import json
import re
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

TU,A,X,B = "Code/T.cpp","Code/A.cpp","Code/Excluded.cpp","Code/B.cpp"


@pytest.fixture
def case(monkeypatch,tmp_path):
    files=[TU,A,X,B]
    don={f:[dict(source=f,target_rva=hex(0x1000+i*16+j)) for j in range(2)]
         for i,f in enumerate(files)}
    for f in files+["Code/Other.cpp"]:
        p=tmp_path/f;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(f)
    st=SimpleNamespace(compiled=[],judged=[],carried=[],mapped=[],applied=[],claimed=[],
                       plan_calls=[],failure=None,don=don,root=tmp_path)
    class Verifier:
        fd=SimpleNamespace(MANAGED=re.compile(r"(?!)"),overrides=lambda:{})
        flags=None;errors=["error C2065: fixture"];all_errors=errors
        def matched(self,text,rows):
            self.obj=Path(hashlib.sha256(text.encode()).hexdigest()+".obj")
            members=[text] if text in files else json.loads(text)
            st.compiled.append(members)
            if text not in files:
                if st.failure=="compile":return None
                if st.failure=="bytes":return set()
            return {r["target_rva"] for r in rows}
    class Guard:
        def load(self):pass
        def linked(self,files):return list(files)
        def prepare(self,files):
            st.judged.append(("prepare",list(files)));return None
        def judge(self,obj,files,text):
            st.judged.append(("link",list(files)))
            return ["fixture link refusal"] if st.failure=="link" else []
    class Provider:
        def load(self,index):
            st.judged.append(("provider_load",[]));return None
        def original(self,f):return None
        def judge(self,before,after,continues,moved):
            st.judged.append(("provider",list(before)))
            return [("name","owner","fixture provider refusal")] if st.failure=="provider" else []
    class Carry:
        def __init__(self,root,tu,acc,*args):
            st.carried.append(list(acc))
            self.problems=["fixture register refusal"] if st.failure=="carry" else []
        def report(self):return {}
    def mapping(tu,acc):
        st.mapped.append(list(acc))
        return "fixture map refusal" if st.failure=="map" else None
    def apply(tu,acc,*args,**kw):
        st.applied.append(list(acc));return {f:2 for f in acc if f!=tu}
    def claim(tu,don,**kw):
        st.claimed.append(list(don));return T.Held()
    def plan_call(name,value):
        def called(*args,**kw):
            st.plan_calls.append(name)
            return value
        return called
    monkeypatch.setattr(T,"ROOT",tmp_path)
    monkeypatch.setattr(T,"skeleton",lambda tu:[])
    monkeypatch.setattr(T,"tu_path",lambda tu:tu)
    monkeypatch.setattr(T,"donors",lambda *a:(don,{"Code/Mixed.cpp":[]},{"Code/Refused.cpp":"fixture"}))
    monkeypatch.setattr(T,"header_queue_rows",lambda:{X:["ExcludedClass"]})
    monkeypatch.setattr(T,"view_hint",lambda result,*a:result)
    monkeypatch.setattr(T,"merge_plan_state",plan_call("state","s"))
    monkeypatch.setattr(T,"merge_plan_inputs",plan_call("inputs","i"))
    monkeypatch.setattr(T,"load_merge_plan",plan_call("load",None))
    monkeypatch.setattr(T,"save_merge_plan",plan_call("save",None))
    monkeypatch.setattr(T,"reuse_merge_plan",lambda *a:pytest.fail("unexpected cached plan reuse"))
    monkeypatch.setattr(T,"Verifier",lambda *a:Verifier())
    monkeypatch.setattr(T,"LinkGuard",lambda *a:Guard())
    monkeypatch.setattr(T,"ProviderGuard",Provider)
    monkeypatch.setattr(T,"Carry",Carry)
    monkeypatch.setattr(T,"map_regressions",mapping)
    monkeypatch.setattr(T,"compose",lambda tu,sk,files,*a,**kw:json.dumps(list(files)))
    monkeypatch.setattr(T,"apply",apply)
    monkeypatch.setattr(T,"claim_scope",claim)
    monkeypatch.setattr(T,"give_back",lambda *a:None)
    return st


@pytest.mark.parametrize("dry_run",[True,False])
def test_excluded_donor_never_compiled_accepted_claimed_or_applied(case,dry_run):
    before=(case.root/X).read_bytes()
    out=T.merge(TU,dry_run=dry_run,exclude=[X])
    assert out["accepted"]==[TU,A,B]
    assert out["rows"]==6 and out["excluded"]==[X]
    assert "blocked" not in out and "adopt_first" not in out and "_plan" not in out
    assert X in case.don  # no mutation of a cached donor inventory
    assert all(X not in files for files in case.compiled+case.carried+case.mapped+case.applied+case.claimed)
    assert case.compiled and case.carried and case.mapped
    assert {"link","provider"} <= {kind for kind,_ in case.judged}
    assert case.plan_calls==[]
    assert (case.root/X).read_bytes()==before
    if not dry_run:
        assert case.applied==[[TU,A,B]] and case.claimed==[[TU,A,B]]


def test_excluded_file_is_not_even_read_by_baseline_or_search(case):
    (case.root/X).unlink()
    assert T.merge(TU,dry_run=True,exclude=[X])["accepted"]==[TU,A,B]


@pytest.mark.parametrize("unknown",["Code/Missing.cpp","Code/Other.cpp","Code/Mixed.cpp","Code/Refused.cpp"])
def test_unknown_or_non_candidate_path_refused_before_any_work(case,unknown):
    out=T.merge(TU,dry_run=False,exclude=[X,unknown])
    assert unknown in out["blocked"] and "not donors" in out["blocked"]
    assert not out["accepted"]
    assert not (case.compiled or case.claimed or case.applied or case.plan_calls)


def test_destination_seed_cannot_be_excluded(case):
    out=T.merge(TU,dry_run=False,exclude=[TU])
    assert "destination TU seed" in out["blocked"]
    assert not (case.compiled or case.claimed or case.plan_calls)


def test_too_few_remaining_donors_uses_normal_refusal(case):
    out=T.merge(TU,dry_run=True,exclude=[A,X,B])
    assert out["blocked"]=="fewer than two donors"
    assert not (case.compiled or case.plan_calls)


def test_duplicate_and_windows_spelling_resolve_to_one_named_donor(case):
    out=T.merge(TU,dry_run=True,exclude=["./"+X,X.replace("/","\\")])
    assert out["excluded"]==[X] and out["accepted"]==[TU,A,B]


@pytest.mark.parametrize("exclude",[(),[],None])
def test_default_candidate_set_and_plan_cache_behavior_unchanged(case,exclude):
    out=T.merge(TU,dry_run=True,exclude=exclude)
    assert out["accepted"]==[TU,A,X,B] and out["rows"]==8
    assert "excluded" not in out and out["adopt_first"]=={X:["ExcludedClass"]}
    assert case.plan_calls==["state","inputs","load","save"]
    assert [X] in case.compiled


@pytest.mark.parametrize("failure",["compile","bytes","link","provider","carry","map"])
def test_every_normal_admission_refusal_remains_enforced(case,failure):
    case.failure=failure
    out=T.merge(TU,dry_run=False,exclude=[X])
    assert out.get("blocked") and not case.applied
    assert case.plan_calls==[]
    assert all(X not in files for files in case.compiled)


def test_cli_merge_only_repeatable_and_default_call_compatible(monkeypatch):
    with pytest.raises(SystemExit) as e:T.main(["--queue","--exclude",X])
    assert e.value.code==2
    calls=[]
    def merge(tu,dry_run,claim=True,**kw):
        calls.append((tu,dry_run,claim,kw))
        return {"accepted":[TU,A],"subject":"fixture"}
    monkeypatch.setattr(T,"merge",merge)
    assert T.main(["--merge",TU,"--dry-run","--no-claim","--exclude",X,A,"--exclude",B])==0
    assert calls[-1]==(TU,True,False,{"exclude":[X,A,B]})
    assert T.main(["--merge",TU,"--dry-run"])==0
    assert calls[-1]==(TU,True,True,{})
