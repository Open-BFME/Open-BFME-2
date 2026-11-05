"""Bulk scoped naming: complete inventories, parent exception review, one transaction."""
import hashlib
import json
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import name_scoped
import rename

SOURCE = "Code/Game/Work.cpp"


@pytest.fixture
def batch(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_CLAIM_OWNER", "parent-seat")
    monkeypatch.setenv("BFME_CLAIMS", "off")
    source = "// cl: /O2\nint globalCount;\nstruct Box { int memberCount; };\nint calculate(int f, int existingCount)\n{\n"
    source += "\n".join(f"    int iVar{i} = existingCount + {i};" for i in range(200))
    source += "\n    return f + iVar199 + globalCount;\n}\n"
    files = {
        SOURCE: source,
        "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
            f"?calculate@@YAHHH@Z,,0x00401000,20,{SOURCE},matched,\n",
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    }
    for rel, data in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(data, encoding="utf-8")
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    subprocess.run(["git", "-C", str(tmp_path), "add", "-A"], check=True)
    lane = name_lane.Lane(tmp_path, rename.Context(tmp_path, object_scan=False))
    args = SimpleNamespace(session="large", model="test-model", files=[SOURCE], under=None,
                           target=200, max_files=32, max_chars=250000)
    assert name_scoped.next_batch(lane, args) == 0
    packet_path = name_scoped.session_path(lane, "large")
    packet = name_scoped.load(packet_path)
    answers = dict(proposed_by="/root/proposer", names={})
    for row in packet["sources"][SOURCE]["targets"]:
        number = int(row["old"][4:]) if row["old"].startswith("iVar") else 0
        readable = "computedValue" + chr(65 + number // 26) + chr(65 + number % 26)
        new = {"f": "inputValue", "existingCount": "inputCount"}.get(row["old"], readable)
        answers["names"][row["key"]] = dict(name=new)
    answer_path = tmp_path / "answers.json"
    name_scoped.save(answer_path, answers)
    review_path = tmp_path / "review.json"
    review = dict(proposal_sha256=hashlib.sha256(answer_path.read_bytes()).hexdigest(),
                  scan_complete=True, decisions={}, coverage_checked=True)
    name_scoped.save(review_path, review)
    args = SimpleNamespace(session="large", answer=str(answer_path), review=str(review_path))
    return lane, args, packet, answers, review


def write_review(args, review):
    name_scoped.save(Path(args.review), review)


def test_inventory_includes_strong_and_single_letter_names_and_whole_function(batch):
    lane, args, packet, answers, review = batch
    source = packet["sources"][SOURCE]
    assert packet["bindings"] == 202  # soft target never cuts the final function
    assert {t["old"] for t in source["targets"]} >= {"f", "existingCount", "iVar199"}
    assert source["functions"][0]["code"].endswith("}")
    assert all(t["kind"] in ("param", "local") for t in source["targets"])


def test_two_hundred_names_one_verified_transaction_no_scoped_votes(batch):
    lane, args, packet, answers, review = batch
    builds = []
    def verify(ctx, sources):
        builds.append(sources)
        text = (ctx.root / SOURCE).read_text()
        assert "computedValueHR" in text and "inputCount" in text
        assert "globalCount" in text and "memberCount" in text and "calculate(" in text
        return True
    assert name_scoped.apply(lane, args, verify=verify, checks=lambda *_: []) == 0
    assert builds == [[SOURCE]]
    report = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert report["landed"] == 202
    for rel in (name_lane.VOTES, name_lane.AGREED, name_lane.MEANINGS, name_lane.RESOLUTIONS):
        assert not (lane.root / rel).exists()


def test_parent_scan_and_exact_proposal_hash_required(batch):
    lane, args, packet, answers, review = batch
    review["scan_complete"] = False
    write_review(args, review)
    with pytest.raises(ValueError, match="parent must scan"):
        name_scoped.apply(lane, args)
    review.update(scan_complete=True, proposal_sha256="wrong")
    write_review(args, review)
    with pytest.raises(ValueError, match="exact hash"):
        name_scoped.apply(lane, args)
    assert not (lane.root / rename.NAME_BASIS).exists()


def test_only_questionable_names_need_individual_parent_decisions(batch):
    lane, args, packet, answers, review = batch
    key = next(iter(answers["names"]))
    answers["names"][key]["question"] = "Could be an element count or a byte count"
    with pytest.raises(ValueError, match="resolve this questionable"):
        name_scoped.prepare(lane, packet, answers, review)
    review["decisions"][key] = dict(name="elementCount", reason="Call sites index elements, never bytes")
    requests, report = name_scoped.prepare(lane, packet, answers, review)
    assert len(report["mapping"]) == 202
    assert len(review["decisions"]) == 1
    assert report["mapping"][0]["new"] == "elementCount"


def test_every_binding_needs_name_or_explicit_retention(batch):
    lane, args, packet, answers, review = batch
    key = next(iter(answers["names"]))
    del answers["names"][key]
    with pytest.raises(ValueError, match="every inventoried binding"):
        name_scoped.prepare(lane, packet, answers)
    answers["names"][key] = dict(keep="already clear")
    _, report = name_scoped.prepare(lane, packet, answers)
    assert report["retained"] == [dict(key=key, reason="already clear", proposed_by="/root/proposer",
                                      reviewed_by=None, proposed_name=None)]


def test_source_race_rejected_before_planning(batch):
    lane, args, packet, answers, review = batch
    path = lane.root / SOURCE
    path.write_bytes(path.read_bytes() + b"\n// another worker\n")
    with pytest.raises(ValueError, match="changed; prepare a fresh"):
        name_scoped.prepare(lane, packet, answers, review)


def test_failed_combined_verification_restores_all_names(batch):
    lane, args, packet, answers, review = batch
    before = (lane.root / SOURCE).read_bytes()
    builds = []
    assert name_scoped.apply(lane, args,
        verify=lambda _ctx, sources: builds.append(sources) or False,
        checks=lambda *_: []) == 1
    assert builds == [[SOURCE]]
    assert (lane.root / SOURCE).read_bytes() == before
    assert not (lane.root / rename.NAME_BASIS).exists()


@pytest.mark.parametrize("kind", ["function", "class", "global", "member"])
def test_direct_evidence_cannot_admit_shared_names(batch, kind):
    lane, *_ = batch
    with pytest.raises(rename.Refusal):
        rename.check_basis(lane.ctx, kind, "inferred", "direct:nd-" + "a" * 24,
                           "iVar1", "iVar1", None, new_name="readableName", new_word="readableName")


def test_preview_is_read_only_and_produces_one_review_form(batch):
    lane, args, packet, answers, review = batch
    before = (lane.root / SOURCE).read_bytes()
    assert name_scoped.preview(lane, args) == 0
    path = name_scoped.session_path(lane, "large")
    preview = name_scoped.load(path.with_suffix(".preview.json"))
    template = name_scoped.load(path.with_suffix(".review.json"))
    assert preview["proposed"] == 202 and preview["sources"][SOURCE]["diff"]
    assert template["scan_complete"] is False and template["decisions"] == {}
    assert (lane.root / SOURCE).read_bytes() == before
    assert not (lane.root / rename.NAME_BASIS).exists()


def acknowledge_preview(lane, args, decisions=None):
    assert name_scoped.preview(lane, args) == 0
    form = name_scoped.load(name_scoped.session_path(lane, args.session).with_suffix(".review.json"))
    form.update(scan_complete=True, coverage_checked=True, decisions=decisions or {})
    write_review(args, form)
    return form


def watch_scoped_planner(monkeypatch):
    calls = []
    original = rename.plan_scoped
    def counted(*args, **kwargs):
        calls.append((args[0], args[3]))
        return original(*args, **kwargs)
    monkeypatch.setattr(rename, "plan_scoped", counted)
    return calls


def test_preview_candidates_reused_in_fresh_process_context_with_one_verification(batch, monkeypatch):
    lane, args, *_ = batch
    acknowledge_preview(lane, args)
    fresh = name_lane.Lane(lane.root, rename.Context(lane.root, object_scan=False))
    calls = watch_scoped_planner(monkeypatch)
    builds = []
    assert name_scoped.apply(fresh, args, verify=lambda _c, paths: builds.append(paths) or True,
                             checks=lambda *_: []) == 0
    result = name_scoped.load(name_scoped.session_path(fresh, "large").with_suffix(".result.json"))
    assert result["landed"] == result["reused_names"] == 202
    assert result["reused_sources"] == 1 and not calls
    assert builds == [[SOURCE]]


@pytest.mark.parametrize("keep", [False, True])
def test_review_changes_replan_only_changed_binding_and_keep_other_candidates(batch, monkeypatch, keep):
    lane, args, packet, answers, _ = batch
    key = next(iter(answers["names"]))
    decision = {"keep": "Parent retained this binding"} if keep else {
        "name": "finalInput", "reason": "Parent resolved the input role"}
    acknowledge_preview(lane, args, {key: decision})
    calls = watch_scoped_planner(monkeypatch)
    assert name_scoped.apply(lane, args, verify=lambda *_: True, checks=lambda *_: []) == 0
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["reused_names"] == 201
    assert len(calls) == (0 if keep else 1)
    assert result["landed"] == (201 if keep else 202)
    text = (lane.root / SOURCE).read_text()
    assert ("int f," in text) if keep else ("int finalInput," in text)


@pytest.mark.parametrize("late_header", [False, True])
def test_changed_header_invalidates_saved_candidates_and_preserves_macro_guard(batch, monkeypatch, late_header):
    lane, args, packet, *_ = batch
    header = lane.root / "Code/Game/Guard.h"
    if not late_header:
        header.write_text("#pragma once\n")
        subprocess.run(["git", "-C", str(lane.root), "add", "Code/Game/Guard.h"], check=True)
    source = lane.root / SOURCE
    source.write_text('#include "Guard.h"\n' + source.read_text())
    packet["sources"][SOURCE] = name_scoped.inventory(lane, SOURCE)
    name_scoped.save(name_scoped.session_path(lane, "large"), packet)
    acknowledge_preview(lane, args)
    header.write_text("#pragma once\n#define inputValue 17\n")
    if late_header:
        subprocess.run(["git", "-C", str(lane.root), "add", "Code/Game/Guard.h"], check=True)
    calls = watch_scoped_planner(monkeypatch)
    assert name_scoped.apply(lane, args, verify=lambda *_: True, checks=lambda *_: []) == 1
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["reused_names"] == 0 and len(calls) == 202
    assert result["landed"] == 201 and "int f," in source.read_text()
    assert any("macro" in reason for reason in result["sources"][SOURCE]["refused"].values())


def test_preview_shared_tables_observe_a_canonical_approval_between_sources(batch):
    lane, *_ = batch
    tables = {}
    first = name_scoped.PreviewContext(lane.ctx, tables)
    assert rename.is_protected(first, "param", "calculate::f") is None
    (lane.root / rename.NAME_BASIS).write_text(rename.NAME_BASIS_HEADER + "\n"
        "param,calculate::old,calculate::f,canonical:export,evidence," + SOURCE + ",\n")
    second = name_scoped.PreviewContext(lane.ctx, tables)
    assert "canonical" in rename.is_protected(second, "param", "calculate::f")


def test_new_canonical_history_invalidates_saved_plan_and_is_not_overwritten(batch, monkeypatch):
    lane, args, *_ = batch
    acknowledge_preview(lane, args)
    canonical = "param,calculate::old,calculate::f,canonical:export,evidence," + SOURCE + ",\n"
    (lane.root / rename.NAME_BASIS).write_text(rename.NAME_BASIS_HEADER + "\n" + canonical)
    calls = watch_scoped_planner(monkeypatch)
    assert name_scoped.apply(lane, args, verify=lambda *_: True, checks=lambda *_: []) == 1
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["reused_names"] == 0 and result["landed"] == 201 and len(calls) == 202
    assert canonical in (lane.root / rename.NAME_BASIS).read_text()


def test_changed_optimization_flags_cannot_reuse_local_plans(batch, monkeypatch):
    lane, args, *_ = batch
    acknowledge_preview(lane, args)
    (lane.root / rename.FLAG_OVERRIDES).write_text("source,flags\n" + SOURCE + ",/Od\n")
    calls = watch_scoped_planner(monkeypatch)
    assert name_scoped.apply(lane, args, verify=lambda *_: True, checks=lambda *_: []) == 1
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["landed"] == 2 and result["reused_names"] == 0 and len(calls) == 202
    assert "int iVar199" in (lane.root / SOURCE).read_text()


@pytest.mark.parametrize("change", ["missing", "damaged", "legacy", "rules"])
def test_missing_stale_or_modified_artifact_falls_back_to_full_planning(batch, monkeypatch, change):
    lane, args, *_ = batch
    form = acknowledge_preview(lane, args)
    path = name_scoped.session_path(lane, "large").with_suffix(".plans.json")
    if change == "missing":
        path.unlink()
    elif change == "damaged":
        path.write_text('{"source_after":"unreviewed"}')
    elif change == "legacy":
        form.pop("plan_sha256")
        write_review(args, form)
    else:
        monkeypatch.setattr(name_scoped, "planner_state", lambda: "changed rules")
    calls = watch_scoped_planner(monkeypatch)
    assert name_scoped.apply(lane, args, verify=lambda *_: True, checks=lambda *_: []) == 0
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["reused_names"] == 0 and len(calls) == result["landed"] == 202


def test_cached_fast_path_keeps_normal_verification_failure_rollback(batch, monkeypatch):
    lane, args, *_ = batch
    acknowledge_preview(lane, args)
    before = (lane.root / SOURCE).read_bytes()
    calls = watch_scoped_planner(monkeypatch)
    builds = []
    assert name_scoped.apply(lane, args, verify=lambda _c, paths: builds.append(paths) or False,
                             checks=lambda *_: []) == 1
    assert not calls and builds == [[SOURCE]]
    assert (lane.root / SOURCE).read_bytes() == before
    assert not (lane.root / rename.NAME_BASIS).exists()


def test_two_cached_sources_append_history_without_losing_earlier_records(batch, monkeypatch):
    lane, args, packet, answers, _ = batch
    second = "Code/Game/Other.cpp"
    (lane.root / second).write_text("// cl: /O2\nint other(int a) { return a; }\n")
    with (lane.root / rename.FUNCTIONS).open("a") as stream:
        stream.write("?other@@YAHH@Z,,0x00402000,20," + second + ",matched,\n")
    subprocess.run(["git", "-C", str(lane.root), "add", second], check=True)
    lane.ctx._cache.clear()
    packet["sources"][second] = name_scoped.inventory(lane, second)
    for target in packet["sources"][second]["targets"]:
        answers["names"][target["key"]] = dict(name="secondInput")
    name_scoped.save(name_scoped.session_path(lane, "large"), packet)
    name_scoped.save(Path(args.answer), answers)
    acknowledge_preview(lane, args)
    calls = watch_scoped_planner(monkeypatch)
    builds = []
    assert name_scoped.apply(lane, args, verify=lambda _c, paths: builds.append(paths) or True,
                             checks=lambda *_: []) == 0
    result = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert result["reused_names"] == result["landed"] == 203 and result["reused_sources"] == 2
    assert not calls and builds == [[second, SOURCE]]
    history = (lane.root / rename.NAME_BASIS).read_text()
    assert history.count(rename.NAME_BASIS_HEADER) == 1
    assert "calculate::f,calculate::inputValue" in history and "other::a,other::secondInput" in history


def test_canonical_parameter_stays_protected(batch):
    lane, args, packet, answers, review = batch
    path = lane.root / rename.NAME_BASIS
    path.write_text(rename.NAME_BASIS_HEADER + "\nparam,calculate::old,calculate::f,canonical:export,evidence,"
                    + SOURCE + ",\n", encoding="utf-8")
    lane.ctx._cache.clear()
    requests, _ = name_scoped.prepare(lane, packet, answers, review)
    plan = rename.plan_scoped_set(lane.ctx, **requests[0][1])
    assert plan.scoped_count == 201
    assert any("canonical" in reason for reason in plan.scoped_refused.values())


def direct_entries(lane, source, names):
    (lane.root / SOURCE).write_text(source, encoding="utf-8")
    lane.ctx._cache.clear()
    return dict(source=SOURCE, expected_source_sha=lane.ctx.resolution_source_sha(SOURCE), entries=[
        dict(kind=kind, function="calculate", name=old, new=new,
             evidence="direct:nd-" + hashlib.sha256(old.encode()).hexdigest()[:24])
        for kind, old, new in names])


def test_comma_declarations_are_inventoried_and_renamed_together(batch):
    lane, *_ = batch
    request = direct_entries(lane, "// cl: /O2\nint calculate(int f)\n{\nint a,b,c;\nreturn f+a+b+c;\n}\n",
        [("local", "a", "firstCount"), ("local", "b", "secondCount"), ("local", "c", "thirdCount")])
    found = name_scoped.inventory(lane, SOURCE)
    assert {t["old"] for t in found["targets"]} == {"f", "a", "b", "c"}
    plan = rename.plan_scoped_set(lane.ctx, **request)
    assert plan.scoped_count == 3 and not plan.scoped_refused
    assert b"int firstCount,secondCount,thirdCount;" in plan.after[SOURCE]


def test_shadowed_parameter_and_repeated_local_bindings_are_refused(batch):
    lane, *_ = batch
    request = direct_entries(lane, "// cl: /O2\nint calculate(int f)\n{\nint a=1; {int f=2; int a=3;} return f+a;\n}\n",
        [("param", "f", "inputCount"), ("local", "a", "itemCount")])
    with pytest.raises(rename.Refusal, match="no scoped-set entries passed"):
        rename.plan_scoped_set(lane.ctx, **request)


def test_optimization_and_source_fingerprint_guards_remain(batch):
    lane, *_ = batch
    request = direct_entries(lane, "// cl: /Od\nint calculate(int f)\n{int a=1; return f+a;}\n",
                             [("local", "a", "itemCount")])
    with pytest.raises(rename.Refusal, match="without optimisation"):
        rename.plan_scoped_set(lane.ctx, **request)
    request["expected_source_sha"] = "f" * 64
    with pytest.raises(rename.Refusal, match="changed since"):
        rename.plan_scoped_set(lane.ctx, **request)


def test_overloaded_first_function_has_explicit_selector(batch):
    lane, *_ = batch
    text = "// cl: /O2\nint calculate(int f)\n{return f;}\nint calculate(float f)\n{return (int)f;}\n"
    (lane.root / SOURCE).write_text(text, encoding="utf-8")
    found = name_scoped.inventory(lane, SOURCE)
    assert {t["function"] for t in found["targets"]} == {"calculate#1", "calculate#2"}


def test_direct_landing_can_be_reversed_without_approval_rows(batch):
    lane, *_ = batch
    request = direct_entries(lane, "// cl: /O2\nint calculate(int f)\n{return f;}\n",
                             [("param", "f", "inputCount")])
    result = rename.run_batch(lane.ctx, [("scoped-set", request)], claim=False,
                              verify=lambda *_: True, checks=lambda *_: [])
    assert result.failure is None
    evidence = request["entries"][0]["evidence"]
    record = rename.inferred_record(evidence)
    inverse = rename.plan_param(lane.ctx, SOURCE, "inputCount", "f", rename.RESTORED,
                                f"revert:{record} test exact inverse", function="calculate")
    assert b"int calculate(int f)" in inverse.after[SOURCE]


def test_known_failed_source_isolated_and_other_sources_retry_together_once(batch):
    lane, args, packet, answers, review = batch
    other = "Code/Game/Other.cpp"
    (lane.root / other).write_text("// cl: /O2\nint second(int a)\n{return a;}\n", encoding="utf-8")
    ledger = lane.root / rename.FUNCTIONS
    ledger.write_bytes(ledger.read_bytes() + f"?second@@YAHH@Z,,0x00402000,20,{other},matched,\n".encode())
    lane.ctx._cache.clear()
    packet["sources"][other] = name_scoped.inventory(lane, other)
    name_scoped.save(name_scoped.session_path(lane, "large"), packet)
    key = packet["sources"][other]["targets"][0]["key"]
    answers["names"][key] = dict(name="inputValue")
    name_scoped.save(Path(args.answer), answers)
    review["proposal_sha256"] = hashlib.sha256(Path(args.answer).read_bytes()).hexdigest()
    write_review(args, review)
    before = (lane.root / SOURCE).read_bytes()
    builds = []
    def verify(ctx, sources):
        builds.append(sources)
        if SOURCE in sources:
            ctx._build_diagnostics = f"{SOURCE}(4): error C1234: deliberate fixture failure\n"
            return False
        return True
    assert name_scoped.apply(lane, args, verify=verify, checks=lambda *_: []) == 1
    assert builds == [[other, SOURCE], [other]]
    assert (lane.root / SOURCE).read_bytes() == before
    assert "int second(int inputValue)" in (lane.root / other).read_text()
    report = name_scoped.load(name_scoped.session_path(lane, "large").with_suffix(".result.json"))
    assert report["landed"] == 1 and report["verification_runs"] == 2
    assert SOURCE in report["refused"]


def test_picker_skips_completed_sources_until_changed_and_skips_asm(batch):
    lane, *_ = batch
    ledger = lane.root / rename.FUNCTIONS
    ledger.write_bytes(ledger.read_bytes() + b"other,,0x00402000,1,Code/Game/Other.asm,matched,\n")
    lane.ctx._cache.clear()
    name_scoped.save(lane.path(name_scoped.COMPLETED), {SOURCE: lane.ctx.resolution_source_sha(SOURCE)})
    args = SimpleNamespace(session="next", model="test-model", files=None, under=None,
                           target=200, max_files=32, max_chars=250000)
    with pytest.raises(ValueError, match="no available complete functions"):
        name_scoped.next_batch(lane, args)
    source = lane.root / SOURCE
    source.write_bytes(source.read_bytes() + b"\n// new work\n")
    assert name_scoped.next_batch(lane, args) == 0


def test_picker_skips_foreign_claim_before_serving_code(batch, monkeypatch):
    lane, *_ = batch
    monkeypatch.setattr(name_scoped.claims, "busy_keys", lambda *_: {name_scoped.claims.file_key(SOURCE)})
    args = SimpleNamespace(session="busy", model="test-model", files=[SOURCE], under=None,
                           target=200, max_files=32, max_chars=250000)
    with pytest.raises(ValueError, match="no available complete functions"):
        name_scoped.next_batch(lane, args)


def test_multi_child_merge_records_actual_proposer_and_parent_correction(batch):
    lane, args, packet, answers, review = batch
    entries = list(answers["names"].items())
    paths = []
    for index, subset in enumerate((entries[:100], entries[100:])):
        path = lane.root / f"part{index}.json"
        name_scoped.save(path, dict(proposed_by=f"/root/child{index}", names=dict(subset),
                                   coverage_notes=[f"checked part {index}"]))
        paths.append(str(path))
    assert name_scoped.merge(lane, SimpleNamespace(session="large", parts=paths)) == 0
    merged = name_scoped.session_path(lane, "large").with_suffix(".answers.json")
    answers = name_scoped.load(merged)
    assert len(answers["coverage_notes"]) == 2
    key = entries[0][0]
    original = entries[0][1]["name"]
    review["decisions"][key] = dict(name="verifiedInput", reason="Body and callers establish the input role")
    review["proposal_sha256"] = hashlib.sha256(merged.read_bytes()).hexdigest()
    write_review(args, review)
    args.answer = str(merged)
    builds = []
    assert name_scoped.apply(lane, args, verify=lambda _c, files: builds.append(files) or True,
                             checks=lambda *_: []) == 0
    assert builds == [[SOURCE]]
    import csv, io
    rows = list(csv.DictReader(io.StringIO((lane.root / rename.NAME_BASIS).read_text())))
    assert len(rows) == 202
    assert sum("proposed-by /root/child0" in row["evidence"] for row in rows) == 100
    assert sum("proposed-by /root/child1" in row["evidence"] for row in rows) == 102
    corrected = next(row for row in rows if row["new"].endswith("::verifiedInput"))
    evidence = corrected["evidence"]
    assert "parent-reviewed-by " + lane.worker() in evidence
    assert json.loads(evidence.split(" parent-decision ", 1)[1]) == dict(
        proposed=original, reason=review["decisions"][key]["reason"])
    assert name_scoped.load(Path(paths[0]))["names"][key]["name"] == original
    # Added attribution must preserve the existing direct-record proof and inverse path.
    record = rename.inferred_record(evidence)
    inverse = rename.plan_param(lane.ctx, SOURCE, "verifiedInput", "f", rename.RESTORED,
                               f"revert:{record} undo the reviewed landing", function="calculate")
    assert b"int calculate(int f" in inverse.after[SOURCE]


@pytest.mark.parametrize("bad", ["/root/a,/root/b", "/root/a /root/b", "", ["a", "b"]])
def test_ambiguous_proposer_is_rejected_before_planning(batch, bad):
    lane, args, packet, answers, review = batch
    answers["proposed_by"] = bad
    with pytest.raises(ValueError, match="one proposing sub-agent"):
        name_scoped.prepare(lane, packet, answers, review)
    assert not (lane.root / rename.NAME_BASIS).exists()


def test_merge_rejects_duplicate_and_missing_bindings_without_overwriting_output(batch):
    lane, args, packet, answers, review = batch
    output = name_scoped.session_path(lane, "large").with_suffix(".answers.json")
    before = output.read_bytes()
    path = lane.root / "part.json"
    name_scoped.save(path, answers)
    with pytest.raises(ValueError, match="duplicate binding"):
        name_scoped.merge(lane, SimpleNamespace(session="large", parts=[str(path), str(path)]))
    answers["names"].pop(next(iter(answers["names"])))
    name_scoped.save(path, answers)
    with pytest.raises(ValueError, match="every inventoried binding"):
        name_scoped.merge(lane, SimpleNamespace(session="large", parts=[str(path)]))
    assert output.read_bytes() == before


def test_parent_cannot_attribute_its_own_proposal_to_a_child(batch):
    lane, args, packet, answers, review = batch
    key = next(iter(answers["names"]))
    answers["names"][key]["proposed_by"] = lane.worker()
    with pytest.raises(ValueError, match="different agent"):
        name_scoped.prepare(lane, packet, answers, review)


def test_parent_rejection_preserves_original_proposal_and_responsibility(batch):
    lane, args, packet, answers, review = batch
    key = next(iter(answers["names"]))
    original = answers["names"][key]["name"]
    review["decisions"][key] = dict(keep="The proposed units are not established")
    _, report = name_scoped.prepare(lane, packet, answers, review)
    assert report["retained"] == [dict(key=key, reason=review["decisions"][key]["keep"],
        proposed_by="/root/proposer", reviewed_by=lane.worker(), proposed_name=original)]


def context_packet(lane, args, source):
    (lane.root / SOURCE).write_bytes(source.encode())
    lane.ctx._cache.clear()
    packet = name_scoped.load(name_scoped.session_path(lane, args.session))
    packet["sources"][SOURCE] = name_scoped.inventory(lane, SOURCE)
    name_scoped.save(name_scoped.session_path(lane, args.session), packet)
    return packet["sources"][SOURCE]["targets"][0]["key"]


def test_targeted_context_resolves_relevant_signatures_members_and_string_keys(batch, capsys, monkeypatch):
    lane, args, *_ = batch
    capsys.readouterr()
    header = lane.root / "Code/Game/Sink.h"
    raw = b"struct Sink {\r\n unsigned getCount() { return byteCount; }\r\n unsigned byteCount;\r\n virtual void send(const void *buffer, unsigned bytes) = 0;\r\n};\r\n"
    header.write_bytes(raw)
    key = context_packet(lane, args, '// cl: /O2\n#include "Sink.h"\nvoid calculate(void *a)\n{\n'
        ' Sink *sink = 0;\n sink->send(a, sink->byteCount);\n label("payload", a);\n}\n')
    # Context must neither build, inspect every source/header nor consult model runtimes.
    monkeypatch.setattr(lane.ctx, "git", lambda *_a, **_k: pytest.fail("no global index"))
    assert name_lane.main(["scoped", "context", "--session", "large", "--key", key], lane=lane) == 0
    result = json.loads(capsys.readouterr().out)
    hints = result["bindings"][key]
    send = next(c for c in hints["calls"] if c["callee"] == "send")
    assert 'send(a, sink->byteCount)' == send["expression"]
    declaration = send["declarations"][0]
    assert "unsigned bytes" in declaration["declaration"]
    assert declaration["source"] == "Code/Game/Sink.h"
    assert declaration["sha256"] == hashlib.sha256(raw).hexdigest()
    assert declaration["line"] == 4
    field = next(m for m in hints["members"] if m["name"] == "byteCount")
    assert "unsigned byteCount" in field["declarations"][0]["declaration"]
    assert field["declarations"][0]["line"] == 3
    assert any('"payload"' in line for line in hints["uses"])
    assert "not canonical" in declaration["basis"]
    assert not (lane.root / rename.NAME_BASIS).exists()


def test_context_preserves_ambiguous_overloads_and_explicit_extra_context(batch, capsys):
    lane, args, *_ = batch
    capsys.readouterr()
    key = context_packet(lane, args, '// cl: /O2\nvoid calculate(int a)\n{\n send(a);\n}\n')
    path = lane.root / "Code/Game/Other.h"
    path.write_text('void send(int index);\nvoid send(const char *text);\n', encoding="utf-8")
    name_scoped.context(lane, SimpleNamespace(session="large", key=[key], context_files=["Code/Game/Other.h"]))
    hints = json.loads(capsys.readouterr().out)["bindings"][key]
    declarations = hints["calls"][0]["declarations"]
    assert len(declarations) == 2
    assert all(d["source"] == "Code/Game/Other.h" for d in declarations)
    assert not any(d["source"] == SOURCE for d in declarations)  # send(a) is a call, not a prototype.


def test_context_is_bounded_and_reports_omitted_headers(batch, capsys):
    lane, args, *_ = batch
    capsys.readouterr()
    includes = ""
    for index in range(20):
        name = f"Header{index}.h"
        (lane.root / "Code/Game" / name).write_text(f"void send(int index{index});\n")
        includes += f'#include "{name}"\n'
    key = context_packet(lane, args, '// cl: /O2\n' + includes + 'void calculate(int a)\n{\n send(a);\n}\n')
    name_scoped.context(lane, SimpleNamespace(session="large", key=[key], context_files=None))
    result = json.loads(capsys.readouterr().out)
    assert any("budget" in row["reason"] for row in result["omitted"])
    assert len(result["bindings"][key]["calls"][0]["declarations"]) <= 4


def test_context_rejects_stale_unknown_and_outside_paths(batch):
    lane, args, packet, *_ = batch
    key = packet["sources"][SOURCE]["targets"][0]["key"]
    with pytest.raises(ValueError, match="belong"):
        name_scoped.context(lane, SimpleNamespace(session="large", key=["not-a-binding"]))
    with pytest.raises(ValueError, match="repository code context"):
        name_scoped.context(lane, SimpleNamespace(session="large", key=[key], context_files=["../private.h"]))
    (lane.root / SOURCE).write_bytes((lane.root / SOURCE).read_bytes() + b"\n")
    with pytest.raises(ValueError, match="changed"):
        name_scoped.context(lane, SimpleNamespace(session="large", key=[key]))


def test_related_handoff_is_off_until_the_game_boots():
    assert name_scoped.related_work("Code/Game/Object.cpp", "link") is None


def test_related_handoff_is_file_local_and_does_not_run_any_work(monkeypatch):
    monkeypatch.setattr(name_scoped, "RELATED_WORK_HANDOFF", True)
    monkeypatch.setattr(name_scoped, "inventory", lambda *_a, **_k: pytest.fail("handoff must not inventory"))
    monkeypatch.setattr(name_scoped.claims, "busy_keys", lambda *_a: pytest.fail("handoff must not claim"))
    handoff = name_scoped.related_work("Code/Game/Object.cpp", "link", function="?update@Object@@QAEXXZ")
    assert handoff["files"] == ["Code/Game/Object.cpp"]
    assert handoff["argv"][-2:] == ["--functions", "Object::update"]
    assert "--files Code/Game/Object.cpp" in handoff["command"]
    assert "same worker identity" in handoff["instructions"]
    assert name_scoped.related_work("Code/gen_small/unit.cpp", "link") is None
    assert name_scoped.related_work("(no unit)", "link") is None
    assert name_scoped.related_work(None, "link") is None


def test_function_filter_selects_complete_overloads_without_unrelated_bindings(batch):
    lane, args, *_ = batch
    context_packet(lane, args, "// cl: /O2\nint calculate(int f)\n{int a=f; return a;}\n"
        "int calculate(float f)\n{int b=(int)f; return b;}\nint unrelated(int g)\n{return g;}\n")
    all_overloads = name_scoped.inventory(lane, SOURCE, functions=["calculate"])
    assert {f["function"] for f in all_overloads["functions"]} == {"calculate#1", "calculate#2"}
    assert {t["old"] for t in all_overloads["targets"]} == {"f", "a", "b"}
    second = name_scoped.inventory(lane, SOURCE, functions=["calculate#2"])
    assert len(second["functions"]) == 1 and second["functions"][0]["code"].endswith("}")
    assert {t["old"] for t in second["targets"]} == {"f", "b"}


def test_related_apply_verifies_once_and_keeps_other_functions_available_to_bulk_work(batch):
    lane, args, *_ = batch
    original_other = "int unrelated(int g)\n{int b=g; return b;}\n"
    context_packet(lane, args, "// cl: /O2\nint calculate(int f, int existingCount)\n"
        "{int a=f+existingCount; return a;}\n" + original_other)
    pick = SimpleNamespace(session="related", model="test-model", files=[SOURCE], functions=["calculate"],
                           under=None, target=200, max_files=1, max_chars=250000)
    name_scoped.next_batch(lane, pick)
    path = name_scoped.session_path(lane, "related")
    packet = name_scoped.load(path)
    assert packet["bindings"] == 3 and packet["related_functions"] == ["calculate"]
    names = {"f": "inputValue", "existingCount": "inputCount", "a": "sumValue"}
    name_scoped.save(path.with_suffix(".answers.json"), dict(proposed_by="/root/child", names={
        t["key"]: dict(name=names[t["old"]]) for t in packet["sources"][SOURCE]["targets"]}))
    name_scoped.save(path.with_suffix(".review.json"), dict(scan_complete=True, coverage_checked=True,
        proposal_sha256=hashlib.sha256(path.with_suffix(".answers.json").read_bytes()).hexdigest(), decisions={}))
    built = []
    assert name_scoped.apply(lane, SimpleNamespace(session="related", answer=str(path.with_suffix(".answers.json")),
        review=str(path.with_suffix(".review.json"))), verify=lambda _c, files: built.append(files) or True,
        checks=lambda *_: []) == 0
    assert built == [[SOURCE]]
    assert original_other in (lane.root / SOURCE).read_text()
    assert not lane.path(name_scoped.COMPLETED).exists()  # Only inspected functions were reviewed.
    pick.session, pick.functions = "bulk-after-related", None
    name_scoped.next_batch(lane, pick)
    bulk = name_scoped.load(name_scoped.session_path(lane, pick.session))
    assert any(t["function"] == "unrelated" for t in bulk["sources"][SOURCE]["targets"])


def test_function_filter_cannot_start_an_unbounded_global_scan(batch, monkeypatch):
    lane, *_ = batch
    monkeypatch.setattr(lane.ctx, "ledger_sources", lambda: pytest.fail("must reject before global scan"))
    with pytest.raises(ValueError, match="requires explicit --files"):
        name_scoped.next_batch(lane, SimpleNamespace(session="bad", model="test-model", files=None,
            functions=["calculate"], under=None, target=200, max_files=32, max_chars=250000))
