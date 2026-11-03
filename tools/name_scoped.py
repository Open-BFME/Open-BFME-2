"""Whole-function parameter/local naming; proposal by a child, review by its parent.

This module deliberately has no model runner or vote/approval writer. Review is
one acknowledgement of the complete mapping/diff, with decisions only for
questionable names. All edits use rename's ordinary journal and verifier.
"""
import collections
import difflib
import hashlib
import json
import re
import subprocess
import sys
import time
from pathlib import PurePosixPath

import claims
import name_metric
import rename

DIRECTORY = "build/name_lane/scoped"
COMPLETED = f"{DIRECTORY}/completed.json"


def digest(data):
    return hashlib.sha256(data).hexdigest()


def save(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2, ensure_ascii=True) + "\n", encoding="utf-8")


def load(path):
    return json.loads(path.read_text(encoding="utf-8"))


def session_path(lane, session):
    if not re.fullmatch(r"[A-Za-z0-9_-]{1,100}", session):
        raise ValueError("session must contain 1-100 letters, digits, hyphens or underscores")
    return lane.path(f"{DIRECTORY}/{session}.json")


def source_path(rel):
    path = PurePosixPath(rel)
    if (not rel.startswith("Code/") or not rel.endswith((".cpp", ".c"))
            or ".." in path.parts or path.as_posix() != rel or "\\" in rel):
        raise ValueError(f"not a Code source path: {rel}")
    return rel


def inventory(lane, rel):
    """Read complete functions, including meaningful and donor-spelled names.

    The current C++ binding engine remains conservative. Repeated declarations
    and constructs it cannot prove are visible as coverage warnings, not silently
    counted as renamed. No weak-name filter or donor lookup runs here.
    """
    raw = lane.ctx.read(rel)
    text = raw.decode("utf-8", "surrogateescape")
    code = name_metric.strip(text)
    functions, targets, warnings = [], [], []
    spans = name_metric.functions_in(code)
    overloads = collections.Counter(scope.split("#")[0] for scope, *_ in spans)
    for scope, start, end, params in spans:
        if "#" not in scope and overloads[scope] > 1:
            scope += "#1"
        body = code[code.find("{", start):end]
        names = [("param", n) for n in rename.parameters(params)]
        names += [("local", n) for n in rename.scoped_local_names(body)]
        counts = collections.Counter(names)
        keys = []
        for (kind, old), count in counts.items():
            key = "|".join((rel, kind, scope, old))
            row = dict(key=key, kind=kind, function=scope, old=old)
            if count > 1:
                row["question"] = "Repeated declaration: binding requires closer inspection"
            targets.append(row)
            keys.append(key)
        if re.search(r"\b(?:auto|catch)\b|\[[^\]]*\]\s*\(|\(\s*\*", body + params):
            warnings.append(dict(function=scope, reason="Complex bindings may need manual inventory (auto, catch, lambda or function pointer)"))
        if re.search(r"\b[A-Za-z_]\w*\s+[A-Za-z_]\w*\s*(?:=[^;{}]*)?,\s*[*&]*\s*[A-Za-z_]\w*", body):
            warnings.append(dict(function=scope, reason="Comma declaration: confirm every declarator is inventoried"))
        functions.append(dict(function=scope, keys=keys, code=text[start:end]))
    return dict(sha256=digest(raw), text=text, functions=functions,
                targets=targets, coverage_warnings=warnings)


@claims.pick_snapshot()
def next_batch(lane, args):
    started = time.perf_counter()
    if args.target < 1 or args.max_files < 1 or args.max_chars < 1:
        raise ValueError("target, max-files and max-chars must be positive")
    path = session_path(lane, args.session)
    if path.exists():
        raise ValueError("session already exists; use a fresh label")
    owned = lane.ctx.ledger_sources()
    files = args.files or sorted(owned)
    completed = load(lane.path(COMPLETED)) if lane.path(COMPLETED).exists() else {}
    prefix = (args.under or "Code/").rstrip("/") + "/"
    busy = claims.busy_keys(lane.root)
    packet = dict(version=1, session=args.session, worker=lane.worker(),
                  model=args.model, sources={}, target=args.target,
                  instructions=("Analyze every parameter/local in these complete functions. "
                    "Do not rename members, globals, functions, classes or types. "
                    "Return proposed_by and names keyed by each target key: {name: descriptiveName}, "
                    "or {keep: reason}. Mark uncertain proposals with question: reason. "
                    "Resolve coverage warnings and report unsupported bindings; never invent coverage. "
                    "The parent scans the full mapping/diff, investigates only questionable names, "
                    "then submits one review acknowledgement. No votes or external reviewer CLI."))
    count = chars = 0
    skipped = []
    for rel in files:
        if not args.files and (not rel.startswith("Code/") or not rel.endswith((".cpp", ".c"))):
            continue
        source_path(rel)
        if rel not in owned or rename.is_generated(rel) or not rel.startswith(prefix):
            continue
        if rename.is_vendored_path(lane.ctx, rel):
            continue
        if claims.file_key(rel) in busy:
            skipped.append(dict(source=rel, reason="claimed by another worker"))
            continue
        if not args.files and completed.get(rel) == lane.ctx.resolution_source_sha(rel):
            continue
        data = inventory(lane, rel)
        if not data["targets"]:
            continue
        size = len(json.dumps(data))
        if chars + size > args.max_chars:
            skipped.append(dict(source=rel, reason="complete source exceeds remaining packet budget"))
            continue
        packet["sources"][rel] = data
        chars += size
        count += len(data["targets"])
        if count >= args.target or len(packet["sources"]) >= args.max_files:
            break
    if not packet["sources"]:
        raise ValueError("no available complete functions fit; select files or raise max-chars")
    preflight = lane.path("tools/find_declared_unmatched.py")
    if preflight.exists():
        result = subprocess.run([sys.executable, str(preflight), "--fail", *packet["sources"]],
                                cwd=lane.root, capture_output=True, text=True)
        if result.returncode:
            raise ValueError("source preflight refused this batch: " + (result.stdout + result.stderr).strip())
    packet.update(bindings=count, skipped=skipped,
                  inventory_seconds=round(time.perf_counter() - started, 3))
    save(path, packet)
    save(path.with_suffix(".answers.json"), dict(proposed_by="", names={
        t["key"]: None for s in packet["sources"].values() for t in s["targets"]}))
    print(f"scoped: {count} bindings in {len(packet['sources'])} complete source(s); {path}")
    return 0


def prepare(lane, packet, answers, review=None):
    if packet["worker"] != lane.worker():
        raise ValueError("session belongs to another parent worker")
    proposer = answers.get("proposed_by")
    if not isinstance(proposer, str) or not proposer.strip() or any(c in proposer for c in "\r\n"):
        raise ValueError("proposed_by must identify the proposing sub-agent")
    if proposer == lane.worker():
        raise ValueError("parent must review proposals from a different agent")
    targets = {t["key"]: (rel, t) for rel, source in packet["sources"].items() for t in source["targets"]}
    names = answers.get("names")
    if not isinstance(names, dict) or names.keys() != targets.keys():
        raise ValueError("names must cover every inventoried binding exactly (use keep with a reason)")
    decisions = review.get("decisions", {}) if review else {}
    if not isinstance(decisions, dict) or decisions.keys() - targets.keys():
        raise ValueError("review decisions must name served bindings only")
    for rel, source in packet["sources"].items():
        if lane.ctx.resolution_source_sha(rel) != source["sha256"]:
            raise ValueError(f"{rel} changed; prepare a fresh batch")
    groups, retained, questioned, mapping = collections.defaultdict(list), [], {}, []
    for key, (rel, target) in targets.items():
        answer = names[key]
        if isinstance(answer, str):
            answer = dict(name=answer)
        if not isinstance(answer, dict):
            raise ValueError(f"{key}: provide a name or explicit keep reason")
        question = target.get("question") or answer.get("question")
        if question:
            questioned[key] = question
        decision = decisions.get(key, answer)
        if not isinstance(decision, dict):
            raise ValueError(f"{key}: review decision must be an object")
        if key in decisions and not str(decision.get("reason") or decision.get("keep") or "").strip():
            raise ValueError(f"{key}: explain the final decision for the questionable name")
        if review and question and key not in decisions:
            raise ValueError(f"{key}: resolve this questionable name before application")
        if "keep" in decision:
            if not isinstance(decision["keep"], str) or not decision["keep"].strip():
                raise ValueError(f"{key}: keep requires a reason")
            retained.append(dict(key=key, reason=decision["keep"]))
            continue
        new = decision.get("name")
        if new == target["old"]:
            raise ValueError(f"{key}: unchanged name requires an explicit keep reason")
        if not isinstance(new, str) or not rename.IDENT.fullmatch(new):
            raise ValueError(f"{key}: invalid proposed identifier")
        evidence_id = digest(f"{key}|{new}|{packet['sources'][rel]['sha256']}".encode())[:24]
        entry = dict(kind=target["kind"], function=target["function"],
                     name=target["old"], new=new,
                     evidence=f"direct:nd-{evidence_id} parent-reviewed-by {lane.worker()} "
                              f"{packet['model']} proposed-by {proposer}")
        groups[rel].append(entry)
        mapping.append(dict(key=key, old=target["old"], new=new))
    requests = [("scoped-set", dict(source=rel, entries=entries,
        expected_source_sha=packet["sources"][rel]["sha256"])) for rel, entries in groups.items()]
    return requests, dict(inventoried=len(targets), proposed=len(mapping), retained=retained,
                          questioned=questioned, mapping=mapping)


def preview(lane, args):
    path = session_path(lane, args.session)
    raw = lane.path(args.answer).read_bytes()
    packet, answers = load(path), json.loads(raw)
    requests, report = prepare(lane, packet, answers)
    report.update(proposal_sha256=digest(raw), sources={}, refused={})
    for _, request in requests:
        try:
            plan = rename.plan_scoped_set(lane.ctx, **request)
        except rename.Refusal as exc:
            report["refused"][request["source"]] = str(exc)
            continue
        rel = request["source"]
        report["sources"][rel] = dict(diff="".join(difflib.unified_diff(
            packet["sources"][rel]["text"].splitlines(True),
            plan.after[rel].decode("utf-8", "surrogateescape").splitlines(True),
            fromfile=rel, tofile=rel)), refused=getattr(plan, "scoped_refused", {}))
    save(path.with_suffix(".preview.json"), report)
    save(path.with_suffix(".review.json"), dict(proposal_sha256=digest(raw),
        scan_complete=False, decisions={}, coverage_checked=False))
    print(f"scoped: preview {report['proposed']} proposed, {len(report['retained'])} retained; "
          f"read {path.with_suffix('.preview.json')}; parent scans all, resolves exceptions only")
    return 0


def apply(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    started = time.perf_counter()
    path = session_path(lane, args.session)
    raw = lane.path(args.answer).read_bytes()
    packet, answers = load(path), json.loads(raw)
    review = load(lane.path(args.review))
    if review.get("scan_complete") is not True or review.get("proposal_sha256") != digest(raw):
        raise ValueError("parent must scan the complete proposal/diff and acknowledge its exact hash")
    warnings = [w for s in packet["sources"].values() for w in s["coverage_warnings"]]
    if warnings and review.get("coverage_checked") is not True:
        raise ValueError("parent must check inventory coverage warnings before applying")
    requests, report = prepare(lane, packet, answers, review)
    report.update(sources={}, refused={}, verification_runs=0)
    if requests:
        # Existing run transaction provides one claim, journal, build and ledger
        # verification. A failed combined build restores all sources; do not
        # blindly retry the same batch or degrade to per-name compilation.
        def counted_verify(ctx, sources):
            report["verification_runs"] += 1
            return verify(ctx, sources)
        result = rename.run_batch(lane.ctx, requests, verify=counted_verify, checks=checks)
        # A compiler location identifies a source group, never an individual
        # variable. Retry unaffected groups together once; unknown failures
        # stop after rollback rather than triggering hundreds of rebuilds.
        original_failure = result.failure
        if result.failure:
            from name_lane import _diagnostic_sources
            failed_sources, diagnostic = _diagnostic_sources(result, result.plans)
            eligible = {index for index, _ in result.plans}
            survivors = [request for index, request in enumerate(requests)
                         if index in eligible and request[1]["source"] not in failed_sources]
            if failed_sources and survivors and len(survivors) < len(eligible):
                for rel in failed_sources:
                    report["refused"][rel] = diagnostic
                for index, reason in result.refused.items():
                    report["refused"][requests[index][1]["source"]] = reason
                first = result
                result = rename.run_batch(lane.ctx, survivors, verify=counted_verify, checks=checks)
                requests = survivors
                result.planning_seconds += first.planning_seconds
                result.claims_seconds += first.claims_seconds
                result.apply_verify_seconds += first.apply_verify_seconds
        for index, reason in result.refused.items():
            report["refused"][requests[index][1]["source"]] = reason
        for index, plan in result.plans:
            report["sources"][requests[index][1]["source"]] = dict(
                renamed=getattr(plan, "scoped_count", 0),
                refused=getattr(plan, "scoped_refused", {}))
        report.update(failure=str(result.failure or original_failure) if (result.failure or original_failure) else None,
            planning_seconds=result.planning_seconds, claims_seconds=result.claims_seconds,
            apply_verify_seconds=result.apply_verify_seconds)
        report["landed"] = 0 if result.failure else sum(s["renamed"] for s in report["sources"].values())
    else:
        report["landed"] = 0
    report["total_seconds"] = round(time.perf_counter() - started, 3)
    # Do not repeatedly serve already reviewed files during a continuous run.
    # This is a local picker hint, never evidence or an admission. Explicit
    # --files revisits it; changed source bytes invalidate it automatically.
    renamed_sources = {row["key"].split("|", 1)[0] for row in report["mapping"]}
    complete = set(packet["sources"]) - renamed_sources
    if not report.get("failure"):
        complete.update(rel for rel, value in report["sources"].items()
                        if not value["refused"] and rel not in report["refused"])
    else:
        complete.update(rel for rel, value in report["sources"].items()
                        if report["landed"] and not value["refused"] and rel not in report["refused"])
    if complete:
        from portable_lock import lock, unlock
        cache = lane.path(COMPLETED)
        cache.parent.mkdir(parents=True, exist_ok=True)
        with cache.with_suffix(".lock").open("a") as handle:
            lock(handle, exclusive=True)
            try:
                completed = load(cache) if cache.exists() else {}
                completed.update({rel: lane.ctx.resolution_source_sha(rel) for rel in complete})
                save(cache, completed)
            finally:
                unlock(handle)
    save(path.with_suffix(".result.json"), report)
    print(f"scoped: {report['landed']} landed / {report['inventoried']} inventoried; "
          f"{len(report['retained'])} explicitly retained; {report['total_seconds']}s")
    return int(bool(report.get("failure") or report["refused"] or any(s["refused"] for s in report["sources"].values())))


def configure_parser(parser):
    sub = parser.add_subparsers(dest="scoped_cmd", required=True)
    n = sub.add_parser("next", help="serve complete functions for hundreds of scoped renames")
    n.add_argument("--session", required=True)
    n.add_argument("--model", required=True)
    n.add_argument("--files", nargs="+")
    n.add_argument("--under", help="source directory prefix")
    n.add_argument("--target", type=int, default=200, help="soft binding target; never cut a function")
    n.add_argument("--max-files", type=int, default=32)
    n.add_argument("--max-chars", type=int, default=250000)
    for command in ("preview", "apply"):
        p = sub.add_parser(command)
        p.add_argument("--session", required=True)
        p.add_argument("--answer", required=True)
        if command == "apply":
            p.add_argument("--review", required=True)


def run(lane, args):
    return {"next": next_batch, "preview": preview, "apply": apply}[args.scoped_cmd](lane, args)
