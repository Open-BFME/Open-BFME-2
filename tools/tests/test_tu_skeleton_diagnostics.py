"""Complete compiler evidence is reporting only; no real compiler or cache is used."""
import hashlib
import json
import re

import pytest

from test_tu_skeleton_exclude import case, TU, A, X, B, T

REUSE_MERGE_PLAN = T.reuse_merge_plan


def error(i, symbol=None):
    return r"z:\work\Code\LongHeader.h(%d,7) : error C2065: '%s' : undeclared identifier" % (
        i, symbol or ("name_" + str(i)))


def rejected_case(monkeypatch, case, lines, baseline=False):
    make = T.Verifier

    def factory(*args, **kwargs):
        v = make(*args)
        match = v.matched

        def matched(text, rows):
            if (baseline and text == X) or (not baseline and text.startswith("[") and X in json.loads(text)):
                case.compiled.append([text] if text == X else json.loads(text))
                v.all_errors = list(lines)
                v.errors = list(lines[:3])
                return None
            v.all_errors = v.errors = []
            return match(text, rows)
        v.matched = matched
        return v

    monkeypatch.setattr(T, "Verifier", factory)
    return case


def search(case):
    return T._merge(TU, [], case.don, {"accepted": [], "rejected": {}}, True,
                    texts={f: f for f in case.don})


def test_all_errors_survive_three_error_and_300_character_limits(monkeypatch, case):
    lines = [error(i, "long_symbol_" * 10 + str(i)) for i in range(1, 81)]
    rejected_case(monkeypatch, case, lines + [lines[5], lines[0]])
    result = search(case)
    assert result["accepted"] == [TU, A, B]
    assert len(result["rejected"][X]) == 309  # old decision-facing string unchanged
    evidence = result["compiler_diagnostics"]["donors"][X]
    assert [e["raw"] for e in evidence["errors"]] == lines
    assert evidence["duplicates_removed"] == 2 and evidence["complete"]
    assert evidence["context"]["files"] == [TU, A, X]  # selected accretion trial, not the later screening compile
    assert evidence["context"]["text_sha256"] == hashlib.sha256(json.dumps([TU, A, X]).encode()).hexdigest()
    assert result["_plan"]["compiler_diagnostics"] == result["compiler_diagnostics"]


def test_structured_class_symbol_and_location_keep_the_full_message():
    raw = r"C:\tree\Header.h(123,9) : error C2011: 'Coord3D' : 'struct' type redefinition"
    e = T.compiler_error(raw)
    assert e == dict(raw=raw, code="C2011", symbol="Coord3D", **{"class": "Coord3D"},
                    file=r"C:\tree\Header.h", line=123, column=9,
                    message="'Coord3D' : 'struct' type redefinition")
    e = T.compiler_error("Header.h(44) : fatal error C1083: Cannot open include file: 'x.h'")
    assert e["code"] == "C1083" and e["line"] == 44 and e["column"] is None
    assert e["class"] is None
    e = T.compiler_error("cl : command line error D2021: invalid numeric argument")
    assert e["code"] == "D2021" and e["file"] is None and e["line"] is None
    e = T.compiler_error("unrecognized compiler crash text")
    assert e["raw"] == e["message"] and e["code"] is None


def test_receipt_cap_omits_whole_entries_and_announces_exact_omissions():
    reason = T.CompilerRejection("compile: short", [error(1, "a" * 2000)], {"files": [TU, X]})
    report = T.finish_compiler_receipt({"rejected": {X: reason}}, limit=512)
    payload = report["compiler_diagnostics"]
    assert len(json.dumps(payload, ensure_ascii=False, separators=(",", ":")).encode()) <= 512
    assert payload["truncated"] and payload["omitted_donors"] == payload["omitted_errors"] == 1
    assert payload["donors"] == {}
    # A plan round trip must not erase the warning that its evidence was capped.
    again = T.finish_compiler_receipt({"rejected": {X: str(reason)}},
                                     json.loads(json.dumps(payload)), limit=512)
    assert again["compiler_diagnostics"]["truncated"]


def test_baseline_compile_errors_are_not_disguised_as_just_byte_misses(monkeypatch, case):
    lines = [error(i) for i in range(10)]
    rejected_case(monkeypatch, case, lines, baseline=True)
    result = search(case)
    assert result["rejected"][X] == "no baseline match"
    entry = result["compiler_diagnostics"]["donors"][X]
    assert entry["context"]["stage"] == "baseline"
    assert [e["raw"] for e in entry["errors"]] == lines


def test_receipt_does_not_change_search_trace_or_result(monkeypatch, case):
    rejected_case(monkeypatch, case, [error(i) for i in range(20)])
    result = search(case)
    trace = list(case.compiled)
    case.compiled.clear()
    monkeypatch.setattr(T, "finish_compiler_receipt", lambda report, *args, **kw: report)
    without = search(case)
    for key in ("accepted", "rejected", "flags", "rows", "blocked"):
        assert result.get(key) == without.get(key)
    assert trace == case.compiled


def test_selected_strategy_errors_are_not_replaced_by_later_failures(monkeypatch, case):
    make = T.Verifier

    def factory(*args, **kw):
        v = make(*args, **kw)
        original = v.matched

        def matched(text, rows):
            if not text.startswith("{"):
                return original(text, rows)
            d = json.loads(text)
            v.all_errors = [error(i, d["strategy"] + str(i)) for i in range(20)] if X in d["files"] else []
            v.errors = v.all_errors[:3]
            v.obj = "mock.obj"
            return None if v.all_errors else {r["target_rva"] for r in rows}
        v.matched = matched
        return v

    monkeypatch.setattr(T, "Verifier", factory)
    monkeypatch.setattr(T, "distinct_strategies", lambda compose: [("first", None), ("last", None)])
    monkeypatch.setattr(T, "compose", lambda tu, sk, files, texts, flags, strategy, *args:
                        json.dumps({"files": list(files), "strategy": strategy}))
    result = search(case)
    e = result["compiler_diagnostics"]["donors"][X]
    assert all("first" in line["symbol"] for line in e["errors"])
    assert "last" not in result["rejected"][X]


def test_plan_reuse_preserves_full_diagnostics_and_legacy_plan_is_explicit(monkeypatch, case):
    rejected_case(monkeypatch, case, [error(i) for i in range(25)])
    result = search(case)
    plan = json.loads(json.dumps(result["_plan"]))
    reused = REUSE_MERGE_PLAN(TU, case.don, {"accepted": [], "rejected": {}}, plan, True)
    assert reused["accepted"] == result["accepted"]
    assert reused["compiler_diagnostics"] == result["compiler_diagnostics"]
    del plan["compiler_diagnostics"]
    reused = REUSE_MERGE_PLAN(TU, case.don, {"accepted": [], "rejected": {}}, plan, True)
    assert reused["compiler_diagnostics"]["donors"][X]["status"] == "unavailable"
    assert not reused["compiler_diagnostics"]["donors"][X]["complete"]


@pytest.mark.parametrize("inherited", [None, [], "bad", {"donors": []},
    {"donors": {X: {"reason": "compile: x", "errors": None}}}])
def test_bad_optional_plan_diagnostics_cannot_affect_admission(inherited):
    out = T.finish_compiler_receipt({"rejected": {X: "compile: x"}}, inherited)
    assert out["rejected"][X] == "compile: x"
    assert out["compiler_diagnostics"]["donors"][X]["status"] == "unavailable"



def test_r1_long_reason_omission_counts_do_not_double_on_reuse():
    reason = T.CompilerRejection("compile: " + "x" * 300, ["e" * 2000], {})
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, limit=512)
    initial = json.loads(json.dumps(out["compiler_diagnostics"]))
    assert (initial["omitted_donors"], initial["omitted_errors"]) == (1, 1)
    for _ in range(4):
        out = T.finish_compiler_receipt({"rejected": {X: str(reason)}}, initial, limit=512)
        assert out["compiler_diagnostics"] == initial
        initial = json.loads(json.dumps(out["compiler_diagnostics"]))


def test_r1_malformed_optional_unicode_cannot_raise_after_apply():
    reason = "compile: x"
    inherited = {"donors": {X: {"reason": reason, "errors": [],
                               "context": {"flag": "\ud800"}}}}
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    assert out["compiler_diagnostics"]["donors"][X]["status"] == "unavailable"
    assert not out["compiler_diagnostics"]["donors"][X]["complete"]
    json.dumps(out).encode()


def test_smaller_reuse_budget_does_not_recount_previously_omitted_donors():
    first = T.finish_compiler_receipt({"rejected": {
        A: T.CompilerRejection("compile: small", [error(1)], {}),
        X: T.CompilerRejection("compile: huge", ["x" * 10000], {})}}, limit=2000)
    inherited = json.loads(json.dumps(first["compiler_diagnostics"]))
    assert inherited["omitted_donors"] == 1
    out = T.finish_compiler_receipt({"rejected": {A: "compile: small", X: "compile: huge"}},
                                     inherited, limit=512)
    assert out["compiler_diagnostics"]["omitted_donors"] == 2
    assert out["compiler_diagnostics"]["omitted_errors"] == 2



@pytest.mark.parametrize("context", [{"flag": "\ud800"}, {"flag": float("nan")}])
def test_matching_snapshot_with_malformed_metadata_is_unavailable(context):
    reason = "compile: x"
    good = T.finish_compiler_receipt({"rejected": {
        X: T.CompilerRejection(reason, [error(1)], {})}})["compiler_diagnostics"]
    inherited = json.loads(json.dumps(good))
    inherited["donors"][X]["context"] = context
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    assert out["compiler_diagnostics"]["donors"][X]["status"] == "unavailable"
    assert not out["compiler_diagnostics"]["donors"][X]["complete"]


def test_malformed_record_shape_cannot_be_reused_as_complete_evidence():
    reason = "compile: x"
    good = T.finish_compiler_receipt({"rejected": {
        X: T.CompilerRejection(reason, [error(1)], {})}})["compiler_diagnostics"]
    inherited = json.loads(json.dumps(good))
    inherited["donors"][X]["errors"] = ["a raw string without structured fields"]
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    assert out["compiler_diagnostics"]["donors"][X]["status"] == "unavailable"



def test_r2_invalid_baseline_metadata_stays_explicitly_unavailable():
    reason = "no baseline match"
    captured = T.finish_compiler_receipt({"rejected": {
        X: T.CompilerRejection(reason, ["x.h(1) : error C2011: 'X' : redefinition"], {})}})
    inherited = json.loads(json.dumps(captured["compiler_diagnostics"]))
    inherited["donors"][X]["context"] = {"flag": "\ud800"}
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    assert out["rejected"][X] == reason
    entry = out["compiler_diagnostics"]["donors"][X]
    assert entry["status"] == "unavailable" and entry["complete"] is False
    assert entry["errors"] == []
    json.dumps(out).encode()



@pytest.mark.parametrize("reason", ["compile: missing class", "no baseline match"])
def test_r3_missing_donor_in_cached_payload_is_unavailable(reason):
    initial = T.finish_compiler_receipt({"rejected": {
        X: T.CompilerRejection(reason, ["x.h(1) : error C2011: 'X' : redefinition"], {})}})
    inherited = json.loads(json.dumps(initial["compiler_diagnostics"]))
    del inherited["donors"][X]
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    assert out["rejected"][X] == reason
    e = out["compiler_diagnostics"]["donors"][X]
    assert e["status"] == "unavailable" and e["complete"] is False
    assert out["compiler_diagnostics"]["omitted_donors"] == 0


def test_cached_unaccounted_gap_is_not_hidden_by_a_truncated_flag():
    reasons = {A: "compile: a", X: "compile: x"}
    initial = T.finish_compiler_receipt({"rejected": {
        f: T.CompilerRejection(why, [error(1)], {}) for f, why in reasons.items()}})
    inherited = json.loads(json.dumps(initial["compiler_diagnostics"]))
    inherited["donors"].clear()
    inherited.update(truncated=True, omitted_donors=1, omitted_errors=1)
    out = T.finish_compiler_receipt({"rejected": reasons}, inherited)
    assert set(out["compiler_diagnostics"]["donors"]) == {A, X}
    assert all(e["status"] == "unavailable" for e in out["compiler_diagnostics"]["donors"].values())



@pytest.mark.parametrize("damage", ["remove_error", "change_symbol", "wrong_complete"])
def test_cached_donor_entry_must_cover_its_captured_error_list(damage):
    reason = "compile: errors"
    initial = T.finish_compiler_receipt({"rejected": {
        X: T.CompilerRejection(reason, [error(1), error(2)], {})}})
    inherited = json.loads(json.dumps(initial["compiler_diagnostics"]))
    e = inherited["donors"][X]
    if damage == "remove_error":
        e["errors"].pop()
    elif damage == "change_symbol":
        e["errors"][1]["symbol"] = "different"
    else:
        e["complete"] = False
    out = T.finish_compiler_receipt({"rejected": {X: reason}}, inherited)
    result = out["compiler_diagnostics"]["donors"][X]
    assert result["status"] == "unavailable" and result["complete"] is False
