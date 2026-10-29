"""Run-wide transaction composition, recovery and failed-group isolation."""
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import rename

A = "Code/Game/A.cpp"
B = "Code/Game/B.cpp"
FIRST = "?Rva00401000@@YAHH@Z"
SECOND = "?Rva00402000@@YAHH@Z"


@pytest.fixture
def repo(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_CLAIMS", "off")
    monkeypatch.setattr(rename, "check_agreement", lambda *args, **kwargs: None)
    files = {
        A: "// cl: /O2\nint Rva00401000(int a1) { return a1 + 1; }\n",
        B: "// cl: /O2\nint Rva00401000(int);\n"
           "int Rva00402000(int a2) { return Rva00401000(a2); }\n",
        "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
            f"{FIRST},,0x00401000,20,{A},matched,address-derived\n"
            f"{SECOND},,0x00402000,20,{B},matched,address-derived\n",
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode())
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    subprocess.run(["git", "-C", str(tmp_path), "add", "-A"], check=True)
    return tmp_path


def context(root):
    return rename.Context(root, object_scan=False)


def requests():
    return [("function", dict(rva=rva, new=new, basis="inferred", evidence="agree:test"))
            for rva, new in ((0x00401000, "readFirst"), (0x00402000, "readSecond"))]


def tracked_snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for folder in ("Code", "reverse") for p in (root / folder).rglob("*")
            if p.is_file() and p.relative_to(root).as_posix() != rename.LOCK}


def test_run_batch_composes_overlapping_sources_and_ledgers_once(repo, monkeypatch):
    builds, checks, agreements = [], [], []
    monkeypatch.setattr(rename, "check_agreement", lambda *args, **kwargs: agreements.append(args))
    before = tracked_snapshot(repo)

    def verify(ctx, sources):
        builds.append(sources)
        assert "readFirst(a2)" in (repo / B).read_text()
        assert "int readSecond(int a2)" in (repo / B).read_text()
        assert "?readFirst@@YAHH@Z" in (repo / rename.FUNCTIONS).read_text()
        assert "?readSecond@@YAHH@Z" in (repo / rename.FUNCTIONS).read_text()
        assert len(rename.journals(ctx)) == 1
        return True

    def check(ctx, plan):
        checks.append(set(plan.after))
        if not plan.after:
            assert tracked_snapshot(repo) == before
        return []

    result = rename.run_batch(context(repo), requests(), claim=False, verify=verify, checks=check)
    assert result.failure is None and not result.refused
    assert [i for i, _ in result.plans] == [0, 1]
    assert len(agreements) == 2
    assert builds == [[A, B]]
    assert checks == [set(), {A, B, rename.FUNCTIONS, rename.DELETED, rename.NAME_BASIS}]
    assert not rename.journals(context(repo))


def test_overlay_search_sees_new_words_from_earlier_plans(repo, monkeypatch):
    ordinary = rename.plan_rename

    def planner(kind, *, ctx, **kwargs):
        if kwargs.get("new") == "readSecond":
            assert ctx.grep_files("readFirst", word=True) == [A, B]
            assert ctx.grep_files("Rva00401000", word=True) == []
        return ordinary(kind, ctx=ctx, **kwargs)

    monkeypatch.setattr(rename, "plan_rename", planner)
    result = rename.run_batch(context(repo), requests(), claim=False,
                              verify=lambda *_: True, checks=lambda *_: [])
    assert result.failure is None


@pytest.mark.parametrize("failure", ["build", "checks", "interrupt"])
def test_failed_run_restores_shared_sources_ledgers_and_journal(repo, failure):
    before = tracked_snapshot(repo)
    ctx = context(repo)

    def verify(ctx, sources):
        if failure == "interrupt":
            raise KeyboardInterrupt
        return failure != "build"

    def checks(ctx, plan):
        return ["test: reject final ledger"] if failure == "checks" and plan.after else []

    if failure == "interrupt":
        with pytest.raises(KeyboardInterrupt):
            rename.run_batch(ctx, requests(), claim=False, verify=verify, checks=checks)
    else:
        result = rename.run_batch(ctx, requests(), claim=False, verify=verify, checks=checks)
        assert isinstance(result.failure, rename.VerifyFailed)
    assert tracked_snapshot(repo) == before
    assert not ctx.kept and not rename.journals(ctx)


def test_planning_refusal_does_not_discard_other_valid_requests(repo):
    changes = requests()
    changes[1][1]["new"] = "param_1"  # still a placeholder; ordinary planner refuses it
    builds = []
    result = rename.run_batch(context(repo), changes, claim=False,
        verify=lambda ctx, sources: builds.append(sources) or True, checks=lambda *_: [])
    assert result.failure is None and set(result.refused) == {1}
    assert [i for i, _ in result.plans] == [0]
    assert "readFirst(a2)" in (repo / B).read_text()
    assert "int Rva00402000(int a2)" in (repo / B).read_text()
    assert builds == [[A, B]]


def test_member_then_class_keeps_both_edits_and_carried_provenance(repo):
    cls = "Rva0040A000Box"
    (repo / A).write_bytes((f"// cl: /O2\nclass {cls} {{ public: int m_04; int Rva00401000(); }};\n"
        f"int {cls}::Rva00401000() {{ return m_04; }}\n").encode())
    (repo / B).write_bytes((f"// cl: /O2\nclass {cls} {{ public: int m_04; int Rva00401000(); }};\n"
        f"int Rva00402000({cls} *box) {{ return box->Rva00401000() + box->m_04; }}\n").encode())
    (repo / rename.FUNCTIONS).write_bytes((
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"?Rva00401000@{cls}@@QAEHXZ,,0x00401000,20,{A},matched,address-derived\n"
        f"?Rva00402000@@YAHPAU{cls}@@@Z,,0x00402000,20,{B},matched,address-derived\n").encode())
    builds = []
    result = rename.run_batch(context(repo), [
        ("member", dict(cls=cls, member="m_04", new="m_value", basis="inferred", evidence="agree:member")),
        ("class", dict(name=cls, new="ValueBox", basis="inferred", evidence="agree:class"))],
        claim=False, verify=lambda ctx, sources: builds.append(sources) or True, checks=lambda *_: [])
    assert result.failure is None and not result.refused
    assert builds == [[A, B]]
    assert "class ValueBox" in (repo / A).read_text()
    assert "box->m_value" in (repo / B).read_text()
    assert "?Rva00401000@ValueBox@@QAEHXZ" in (repo / rename.FUNCTIONS).read_text()
    records = rename.name_basis_rows(context(repo))
    assert any(row['kind'] == 'carry' and row['new'] == 'ValueBox::m_value' for row in records)


@pytest.mark.parametrize("success", [True, False])
def test_run_claims_union_once_and_releases_after_failure(repo, monkeypatch, success):
    taken, released = [], []
    keys = [0x00401000, 0x00402000, f"file:{A}", f"file:{B}"]
    def take(wanted, enabled, root):
        taken.append((wanted, enabled, root))
        return rename.Claimed(list(wanted), {k: "fence" for k in wanted})
    monkeypatch.setattr(rename, "take_claims", take)
    monkeypatch.setattr(rename.Claimed, "release", lambda self, root: released.extend(self.new))
    result = rename.run_batch(context(repo), requests(), verify=lambda *_: success, checks=lambda *_: [])
    assert taken == [(keys, True, repo)]
    assert released == ([] if success else keys)
    assert (result.failure is None) == success


def approved_rows():
    result = []
    for rel, rva, old, new in ((A, 0x00401000, "Rva00401000", "readFirst"),
                                (B, 0x00402000, "Rva00402000", "readSecond")):
        result.append(dict(id="test-" + old, kind="function", old=old, new=new,
            key=name_lane.key_of(rel, "function", f"0x{rva:08X}", old), rva=f"0x{rva:08X}",
            agents="test", status="agreed", detail="test"))
    return result


@pytest.mark.parametrize("failure", ["build", "checks"])
def test_failed_group_isolates_one_name_preserving_shared_caller(repo, monkeypatch, failure):
    monkeypatch.setattr(name_lane, "approval_detail", lambda *_: "test agreement")
    lane = name_lane.Lane(repo, context(repo))
    rows = approved_rows()
    todo = {A: [rows[0]], B: [rows[1]]}
    builds = []

    def verify(ctx, sources):
        builds.append(sources)
        return failure != "build" or "int readSecond(" not in (repo / B).read_text()

    def checks(ctx, plan):
        return ["test: second name rejected"] if failure == "checks" and plan.after \
            and "int readSecond(" in (repo / B).read_text() else []

    assert name_lane._apply_run(lane, todo, SimpleNamespace(claim=False), {}, {},
        verify=verify, checks=checks, max_files=25) == (1, 1, 0)
    assert builds == [[A, B], [A, B], [B]]
    assert "int readFirst(" in (repo / A).read_text()
    assert "return readFirst(a2)" in (repo / B).read_text()
    assert "int Rva00402000(" in (repo / B).read_text()
    state = lane.state()
    assert state[rows[0]["key"]]["status"] == "landed"
    assert state[rows[1]["key"]]["status"] == "blocked"
    assert not rename.journals(lane.ctx)


def test_pin_preflight_precedes_native_and_identifies_exact_plan(repo, monkeypatch):
    ordinary = rename.plan_rename
    def planner(kind, **kwargs):
        plan = ordinary(kind, **kwargs)
        if plan.new_word == "readSecond":
            plan.renamed_pins.append((SECOND, "?readSecond@@YAHH@Z", 0x00402000))
        return plan
    monkeypatch.setattr(rename, "plan_rename", planner)
    monkeypatch.setattr(rename, "pin_preflight", lambda *_: [f"reverse/symbols.csv: {SECOND},0x00402000: competing identity"])
    before = tracked_snapshot(repo)
    def forbidden(*_):
        pytest.fail("pin failure must precede claims, native build and transaction writes")
    monkeypatch.setattr(rename, "take_claims", forbidden)
    result = rename.run_batch(context(repo), requests(), verify=forbidden, checks=forbidden)
    assert result.failure and result.suspects == [1]
    assert tracked_snapshot(repo) == before


def test_prepared_prefix_reused_and_claims_retained_across_retries(repo, monkeypatch):
    ctx = context(repo)
    session = rename.RunBatchSession(ctx)
    ordinary = rename.plan_rename
    planned, acquired, released = [], [], []
    def planner(kind, **kwargs):
        planned.append(kwargs["new"])
        return ordinary(kind, **kwargs)
    monkeypatch.setattr(rename, "plan_rename", planner)
    def take(keys, enabled, root):
        acquired.append(list(keys))
        return rename.Claimed(list(keys), {k: "fence" for k in keys})
    monkeypatch.setattr(rename, "take_claims", take)
    monkeypatch.setattr(rename.Claimed, "release", lambda self, root: released.extend(self.new))
    def run(req, success):
        return rename.run_batch(ctx, req, session=session, verify=lambda *_: success, checks=lambda *_: [])
    assert run(requests(), False).failure
    assert run(requests()[:1], True).failure is None
    assert run(requests()[1:], True).failure is None
    session.close()
    assert planned == ["readFirst", "readSecond"]
    assert len([keys for keys in acquired if keys]) == 1
    assert released == []


def test_changed_input_invalidates_prepared_plan(repo, monkeypatch):
    ctx = context(repo)
    session = rename.RunBatchSession(ctx)
    ordinary = rename.plan_rename
    planned = []
    def planner(kind, **kwargs):
        planned.append(kwargs["new"])
        return ordinary(kind, **kwargs)
    monkeypatch.setattr(rename, "plan_rename", planner)
    assert rename.run_batch(ctx, requests()[:1], session=session, claim=False,
                            verify=lambda *_: False, checks=lambda *_: []).failure
    with (repo / A).open("ab") as handle:
        handle.write(b"// concurrent edit\n")
    assert rename.run_batch(ctx, requests()[:1], session=session, claim=False,
                            verify=lambda *_: True, checks=lambda *_: []).failure is None
    session.close()
    assert planned == ["readFirst", "readFirst"]
    assert "// concurrent edit" in (repo / A).read_text()


def test_session_releases_only_unused_new_claims_on_interrupt(repo, monkeypatch):
    session = rename.RunBatchSession(context(repo))
    released = []
    monkeypatch.setattr(rename, "take_claims", lambda keys, *_: rename.Claimed(
        list(keys), {k: "fence-" + str(k) for k in keys}))
    monkeypatch.setattr(rename.Claimed, "release", lambda self, root: released.append((self.new, self.tokens)))
    session.acquire([1, 2], True)
    session.kept.add(1)
    try:
        raise KeyboardInterrupt
    except KeyboardInterrupt:
        session.close()
    assert released == [([2], {2: "fence-2"})]
    assert session.claimed.new == [1]


def test_static_pin_judge_defers_proof_but_rejects_unproved_conflict(monkeypatch):
    import pin_admission
    monkeypatch.setattr(pin_admission, "image_layout", lambda: (0x10000, [(1, 0x10000, True)]))
    monkeypatch.setattr(pin_admission, "fold_prover", lambda *_: pytest.fail("static pass compiled proof"))
    monkeypatch.setattr(pin_admission, "fold_pin_conflicts", lambda *_: pytest.fail("static pass ran fold gate"))
    old = [{"name": "?realOwner@@YAXXZ", "address": "0x1000", "notes": ""}]
    pin = {"name": "?otherOwner@@YAXXZ", "address": "0x1000", "notes": ""}
    assert pin_admission.judge(old, old + [pin], [], [], static_only=True)
    pin["notes"] = "fold-proof=Code/Game/A.cpp"
    assert pin_admission.judge(old, old + [pin], [], [], static_only=True) == []


def test_diagnostics_retry_independent_group_first(repo, monkeypatch):
    monkeypatch.setattr(name_lane, "approval_detail", lambda *_: "test agreement")
    lane = name_lane.Lane(repo, context(repo))
    rows = approved_rows()
    rows.append(dict(rows[0], id="third", key=name_lane.key_of(A, "function", "0x00403000", "Rva00403000"),
                     old="Rva00403000", new="readThird", rva="0x00403000"))
    monkeypatch.setattr(lane, "owned", lambda *args, **kwargs: [
        ("function", f"0x{rva:08X}", old, None)
        for rva, old in [(0x00401000, "Rva00401000"), (0x00402000, "Rva00402000"),
                         (0x00403000, "Rva00403000")]])
    groups = []
    def run(ctx, req, **kwargs):
        names = [kw["new"] for kind, kw in req]
        groups.append(names)
        bad = "readSecond" in names
        return rename.RunBatchResult(
            plans=[(i, SimpleNamespace(verify=[new + ".cpp"])) for i, new in enumerate(names)],
            failure=rename.VerifyFailed("pin collision") if bad else None,
            suspects=[names.index("readSecond")] if bad else [])
    monkeypatch.setattr(rename, "run_batch", run)
    assert name_lane._apply_run(lane, {A: [rows[0], rows[2]], B: [rows[1]]},
        SimpleNamespace(claim=False), {}, {}, verify=None, checks=None, max_files=25) == (2, 1, 0)
    assert groups == [["readFirst", "readThird", "readSecond"], ["readFirst", "readThird"], ["readSecond"]]


def test_recovery_claims_exclude_previously_verified_group(repo, monkeypatch):
    session = rename.RunBatchSession(context(repo))
    monkeypatch.setattr(rename, "take_claims", lambda keys, *_: rename.Claimed(
        list(keys), {key: "fenced" for key in keys}))
    session.acquire([1, "file:shared.cpp"], True)
    session.kept.update([1, "file:shared.cpp"])
    current = session.acquire([2, "file:shared.cpp"], True)
    assert current.new == [2]
    assert current.tokens == {2: "fenced"}


def test_recorded_search_change_invalidates_prepared_plan(repo, monkeypatch):
    ctx = context(repo)
    session = rename.RunBatchSession(ctx)
    ordinary = rename.plan_rename
    planned = []
    def planner(kind, *, ctx, **kwargs):
        planned.append(kwargs["new"])
        ctx.grep_files("cacheMarker", roots=("Code",))
        return ordinary(kind, ctx=ctx, **kwargs)
    monkeypatch.setattr(rename, "plan_rename", planner)
    assert rename.run_batch(ctx, requests()[:1], session=session, claim=False,
        verify=lambda *_: False, checks=lambda *_: []).failure
    extra = repo / "Code/Game/CacheMarker.cpp"
    extra.write_text("// cacheMarker\n")
    subprocess.run(["git", "-C", str(repo), "add", "--", "Code/Game/CacheMarker.cpp"], check=True)
    assert rename.run_batch(ctx, requests()[:1], session=session, claim=False,
        verify=lambda *_: True, checks=lambda *_: []).failure is None
    session.close()
    assert planned == ["readFirst", "readFirst"]


def test_object_stamp_invalidates_cached_consumer_queries(repo, monkeypatch):
    import name_dependents
    ctx = context(repo)
    ctx.object_scan = True
    obj = repo / "build/match/cache.obj"
    obj.parent.mkdir(parents=True)
    obj.write_bytes(b"first")
    monkeypatch.setattr(name_dependents, "_row_objects",
                        lambda _rows: {A: [obj]})
    session = rename.RunBatchSession(ctx)
    session.refresh_object_stamp()
    assert session.object_generation == 0
    obj.write_bytes(b"second")
    session.refresh_object_stamp()
    assert session.object_generation == 1
    (repo / A).write_bytes((repo / A).read_bytes() + b"// new caller without a rebuild\n")
    session.refresh_object_stamp()
    assert session.object_generation == 2


def test_batch_search_candidates_preserve_git_word_binary_and_pathspec_rules(repo, monkeypatch):
    files = {
        "Code/Game/Similar.cpp": b"int Rva00401000Extra; int readFirst;\n",
        "Code/Game/With Space.h": b"int Rva00401000(int);\n",
        "Code/Game/Binary.bin": b"\0Rva00401000 readFirst\n",
        "reverse/test_baseline.txt": b"Rva00401000 readFirst\n",
        "docs/references.md": b"Rva00401000 readFirst\n",
    }
    for rel, data in files.items():
        (repo / rel).parent.mkdir(parents=True, exist_ok=True)
        (repo / rel).write_bytes(data)
    subprocess.run(["git", "-C", str(repo), "add", "--", *files], check=True)
    (repo / "Code/Game/Untracked.cpp").write_text("int Rva00401000;\n")
    ctx = context(repo)
    calls = []
    ordinary = ctx.git

    def git(*args):
        calls.append(args)
        return ordinary(*args)

    monkeypatch.setattr(ctx, "git", git)
    search = rename._PlanningSearches(ctx, {"Rva00401000", "readFirst"})
    for roots in (rename.SEARCH_ROOTS, rename.FROZEN_KEYED, ("docs", "reverse"), ("docs",)):
        for word in (False, True):
            for needle in ("Rva00401000", "readFirst"):
                expected = ctx.grep_files(needle, word=word, roots=roots)
                assert search.grep_files(needle, word=word, roots=roots) == expected
    grouped = [call for call in calls if call.count("-e") > 1]
    assert len(grouped) == 8  # one candidate scan per roots/word pair
    assert any(any(arg.startswith(":(literal)") for arg in call) for call in calls)
    before = len(calls)
    search.grep_files("readFirst", word=True, roots=("docs",))
    assert len(calls) == before


def test_new_tracked_caller_between_retries_invalidates_search_snapshot(repo, monkeypatch):
    ctx = context(repo)
    session = rename.RunBatchSession(ctx)
    calls = []
    ordinary = rename.plan_rename

    def planner(kind, **kwargs):
        calls.append(kwargs["new"])
        return ordinary(kind, **kwargs)

    monkeypatch.setattr(rename, "plan_rename", planner)
    assert rename.run_batch(ctx, requests()[:1], session=session, claim=False,
                            verify=lambda *_: False, checks=lambda *_: []).failure
    rel = "Code/Game/AddedCaller.cpp"
    (repo / rel).write_text("int Rva00401000(int);\nint call() { return Rva00401000(3); }\n")
    subprocess.run(["git", "-C", str(repo), "add", "--", rel], check=True)
    result = rename.run_batch(ctx, requests()[:1], session=session, claim=False,
                              verify=lambda *_: True, checks=lambda *_: [])
    session.close()
    assert result.failure is None and calls == ["readFirst", "readFirst"]
    assert "readFirst(3)" in (repo / rel).read_text()


def test_run_batches_all_known_object_consumer_queries_once(repo, monkeypatch):
    import name_dependents
    monkeypatch.setattr(rename, "ROOT", repo)
    ctx = context(repo)
    ctx.object_scan = True
    scans = []
    monkeypatch.setattr(name_dependents, "_row_objects", lambda _: {A: [], B: []})

    def consumers(symbols, objects, root):
        scans.append(set(symbols))
        return {symbol: set() for symbol in symbols}

    monkeypatch.setattr(name_dependents, "dependents_by_name", consumers)
    monkeypatch.setattr(name_dependents, "dependents", lambda *_: pytest.fail("repeated object scan"))
    result = rename.run_batch(ctx, requests(), claim=False,
                              verify=lambda *_: True, checks=lambda *_: [])
    assert result.failure is None and not result.refused
    assert scans == [{FIRST, SECOND}]


def test_individual_pin_conflict_blocks_one_plan_without_replanning_clean_names(repo, monkeypatch):
    ordinary = rename.plan_rename
    planned, verified = [], []

    def planner(kind, *, ctx, **kwargs):
        planned.append(kwargs["new"])
        plan = ordinary(kind, ctx=ctx, **kwargs)
        if kwargs["new"] == "readSecond":
            plan.edit(ctx, rename.SYMBOLS, b"name,address,notes\n?conflict@@YAXXZ,0x00402000,\n")
        return plan

    monkeypatch.setattr(rename, "plan_rename", planner)
    monkeypatch.setattr(rename, "pin_preflight", lambda ctx, plan:
                        ["conflicting pin"] if rename.SYMBOLS in plan.after else [])
    result = rename.run_batch(context(repo), requests(), claim=False,
        verify=lambda ctx, sources: verified.append(sources) or True, checks=lambda *_: [])
    assert result.failure is None and result.refused == {1: "pin_admission: conflicting pin"}
    assert planned == ["readFirst", "readSecond"] and verified == [[A, B]]
    assert "readFirst(a2)" in (repo / B).read_text()
    assert "int Rva00402000(" in (repo / B).read_text()
    assert "conflict" not in (repo / rename.SYMBOLS).read_text()
