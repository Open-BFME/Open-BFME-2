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
    assert report["retained"] == [dict(key=key, reason="already clear")]


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
