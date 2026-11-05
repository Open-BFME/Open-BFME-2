"""Whole-function parameter/local naming; proposal by a child, review by its parent.

This module deliberately has no model runner or vote/approval writer. Review is
one acknowledgement of the complete mapping/diff, with decisions only for
questionable names. All edits use rename's ordinary journal and verifier.
"""
import base64
import collections
import csv
import difflib
import hashlib
import io
import json
import posixpath
import re
import shlex
import subprocess
import sys
import time
from pathlib import Path, PurePosixPath

import claims
import name_metric
import rename

DIRECTORY = "build/name_lane/scoped"
COMPLETED = f"{DIRECTORY}/completed.json"


# Off until the rebuilt game reaches the menu (docs/verifier_upgrade_plan.md, step 12): link
# repairs and merges take the time first. `name_lane.py scoped next` itself stays available.
RELATED_WORK_HANDOFF = False


def related_work(sources, work, function=None):
    """A cheap, file-local handoff for an already selected repair or merge.

    No inventory, claims, model or verifier runs when another lane emits this.
    The worker takes a fresh scoped snapshot after its primary source edits.
    """
    if sources is None or not RELATED_WORK_HANDOFF:
        return None
    files = []
    for source in [sources] if isinstance(sources, str) else sources:
        if not isinstance(source, str):
            continue
        try:
            source_path(source)
        except (ValueError, TypeError):
            continue
        if source not in files and not rename.is_generated(source):
            files.append(source)
    if not files:
        return None
    argv = ["python3", "tools/name_lane.py", "scoped", "next", "--session",
            f"{work}-names-SESSION", "--model", "MODEL", "--files", *files,
            "--max-files", str(len(files)), "--max-chars", "2000000"]
    scope = (rename.scope_of(function) if function.startswith("?") else function) \
        if isinstance(function, str) else None
    if scope and re.fullmatch(r"(?:[A-Za-z_]\w*::)*~?[A-Za-z_]\w*(?:#\d+)?", scope):
        argv += ["--functions", scope]
    return dict(work=work, files=files, argv=argv, command=shlex.join(argv),
        instructions="Reuse the code context from this work to clarify locals/parameters in the functions "
                     "you inspected. Replace SESSION/MODEL; use --functions for exact scopes when needed. "
                     "Keep clear names and uncertain roles; do not add unrelated files to meet a naming quota. "
                     "A native child proposes; the parent reviews and resolves questions, then scoped apply "
                     "verifies the names together. Keep the same worker identity and its existing claims; "
                     "respect other workers' claims. Take the packet after primary edits, using final TU paths "
                     "after consolidation; update --functions if a link fix changed the function's name. "
                     "Publish verified moves promptly; naming does not replace or delay "
                     "the primary repair/merge pass test. Shared names retain their existing workflow.")


def proposer_of(answers, answer, worker):
    """One actual proposer per binding, including merged multi-child packets."""
    proposer = answer.get("proposed_by", answers.get("proposed_by"))
    if not isinstance(proposer, str) or not re.fullmatch(r"[A-Za-z0-9_./:@+-]{1,160}", proposer):
        raise ValueError("proposed_by must identify one proposing sub-agent; "
                         "use names[KEY].proposed_by or scoped merge for multiple children")
    if proposer == worker:
        raise ValueError("parent must review proposals from a different agent")
    return proposer


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


def inventory(lane, rel, functions=None):
    """Read complete functions, including meaningful and donor-spelled names.

    The current C++ binding engine remains conservative. Repeated declarations
    and constructs it cannot prove are visible as coverage warnings, not silently
    counted as renamed. No weak-name filter or donor lookup runs here.
    """
    raw = lane.ctx.read(rel)
    text = raw.decode("utf-8", "surrogateescape")
    code = name_metric.strip(text)
    selected = set(functions or ())
    functions, targets, warnings = [], [], []
    spans = name_metric.functions_in(code)
    overloads = collections.Counter(scope.split("#")[0] for scope, *_ in spans)
    for scope, start, end, params in spans:
        if "#" not in scope and overloads[scope] > 1:
            scope += "#1"
        if selected and scope not in selected and scope.split("#")[0] not in selected:
            continue
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
    functions = getattr(args, "functions", None)
    if functions and not args.files:
        raise ValueError("--functions requires explicit --files from the related work")
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
                    "Return one proposed_by identity and names keyed by each target key: {name: descriptiveName}, "
                    "or {keep: reason}. Mark uncertain proposals with question: reason. "
                    f"For unclear roles, request bounded declarations with python3 tools/name_lane.py "
                    f"scoped context --session {args.session} --key KEY. These are hints, not canonical proof. "
                    "When combining children, use scoped merge --session S --parts PART.json ...; "
                    "it preserves each binding's actual proposer. Do not list several children on every name. "
                    "Resolve coverage warnings and report unsupported bindings; never invent coverage. "
                    "The parent scans the full mapping/diff, investigates only questionable names, "
                    "then edits the generated review form, preserving proposal_sha256 and plan_sha256. "
                    "No votes or external reviewer CLI."))
    if functions:
        packet["related_functions"] = list(functions)
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
        data = inventory(lane, rel, functions=functions)
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
        proposer = proposer_of(answers, answer, lane.worker())
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
            retained.append(dict(key=key, reason=decision["keep"], proposed_by=proposer,
                                 reviewed_by=lane.worker() if review else None,
                                 proposed_name=answer.get("name")))
            continue
        new = decision.get("name")
        if new == target["old"]:
            raise ValueError(f"{key}: unchanged name requires an explicit keep reason")
        if not isinstance(new, str) or not rename.IDENT.fullmatch(new):
            raise ValueError(f"{key}: invalid proposed identifier")
        evidence_id = digest(f"{key}|{new}|{packet['sources'][rel]['sha256']}".encode())[:24]
        attribution = dict(proposed_by=proposer, proposed_name=answer.get("name"),
                           reviewed_by=lane.worker() if review else None)
        correction = ""
        if key in decisions:
            detail = dict(proposed=answer.get("name"), reason=decision["reason"])
            if "keep" in answer:
                detail["proposed_keep"] = answer["keep"]
            attribution["parent_decision"] = detail
            correction = " parent-decision " + json.dumps(detail, ensure_ascii=True, separators=(",", ":"))
        entry = dict(kind=target["kind"], function=target["function"],
                     name=target["old"], new=new,
                     evidence=f"direct:nd-{evidence_id} parent-reviewed-by {lane.worker()} "
                              f"{packet['model']} proposed-by {proposer}{correction}")
        groups[rel].append(entry)
        mapping.append(dict(key=key, old=target["old"], new=new, **attribution))
    requests = [("scoped-set", dict(source=rel, entries=entries,
        expected_source_sha=packet["sources"][rel]["sha256"])) for rel, entries in groups.items()]
    return requests, dict(inventoried=len(targets), proposed=len(mapping), retained=retained,
                          questioned=questioned, mapping=mapping)


def merge(lane, args):
    """Combine disjoint native-child answers without inventing joint attribution."""
    path = session_path(lane, args.session)
    output = path.with_suffix(".answers.json")
    answers = dict(names={}, coverage_notes=[])
    for part_path in args.parts:
        part_path = lane.path(part_path)
        if part_path.resolve() == output.resolve():
            raise ValueError("keep original parts separate from the merged answers output")
        part = load(part_path)
        if not isinstance(part.get("names"), dict):
            raise ValueError("each part must contain a names mapping")
        for key, value in part["names"].items():
            if key in answers["names"]:
                raise ValueError(f"duplicate binding across proposal parts: {key}")
            if not isinstance(value, (str, dict)):
                raise ValueError(f"{key}: provide a name or explicit keep reason")
            answer = dict(name=value) if isinstance(value, str) else dict(value)
            answer["proposed_by"] = proposer_of(part, answer, lane.worker())
            answers["names"][key] = answer
        if part.get("coverage_notes"):
            answers["coverage_notes"].append(dict(part=part_path.name, notes=part["coverage_notes"]))
    prepare(lane, load(path), answers)  # Coverage, source freshness and ordinary answer validation.
    save(output, answers)
    print(f"scoped: merged {len(answers['names'])} bindings with per-binding attribution; {output}")
    return 0


def context_documents(lane, rel, source, extra=()):
    """Bounded include lookup on demand; no global scan, build or reference refresh."""
    if len(extra) > 8:
        raise ValueError("request at most eight extra context files")
    documents = {rel: source}
    omitted = []
    flags = " ".join(line for line in source.splitlines()[:8] if re.match(r"\s*//\s*cl:", line))
    include_dirs = re.findall(r'(?:/I|-I)\s*(?:"([^"]+)"|(\S+))', flags)
    include_dirs = [a or b for a, b in include_dirs]
    queue = [(path, 0) for path in extra]
    queue.insert(0, (rel, 0))
    total = 0
    seen = set()
    while queue:
        current, depth = queue.pop(0)
        if current in seen:
            continue
        seen.add(current)
        if current != rel:
            if (not current.startswith(("Code/", "reference/"))
                    or PurePosixPath(current).suffix.lower() not in (".h", ".hpp", ".inl", ".cpp", ".c")
                    or ".." in PurePosixPath(current).parts or "\\" in current):
                raise ValueError(f"not a repository code context path: {current}")
            path = rename._safe_component_path(lane.root, current)
            if path is None or not path.is_file():
                omitted.append(dict(source=current, reason="missing or unsafe context path"))
                continue
            size = path.stat().st_size
            if len(documents) >= 13 or size > 96000 or total + size > 256000:
                omitted.append(dict(source=current, reason="context file/byte budget"))
                continue
            documents[current] = path.read_bytes().decode("utf-8", "surrogateescape")
            total += size
        if depth >= 2:
            continue
        for name in re.findall(r'^[ \t]*#[ \t]*include\s*[<"]([^>"]+)[>"]', documents[current], re.M):
            candidates = [posixpath.join(posixpath.dirname(current), name), name]
            candidates += [posixpath.join(directory, name) for directory in include_dirs]
            found = None
            for candidate in candidates:
                candidate = posixpath.normpath(candidate)
                if not candidate.startswith(("Code/", "reference/")):
                    continue
                path = rename._safe_component_path(lane.root, candidate)
                if path is not None and path.is_file():
                    found = candidate
                    break
            if found:
                queue.append((found, depth + 1))
            else:
                omitted.append(dict(source=current, include=name, reason="include not resolved locally"))
    return documents, omitted[:40] + ([dict(reason="more omitted includes", count=len(omitted) - 40)]
                                      if len(omitted) > 40 else [])


def declaration_hints(documents, callees, members):
    """Syntax-limited candidate declarations; never assert overload/type resolution."""
    signatures, fields = collections.defaultdict(list), collections.defaultdict(list)
    head = name_metric.FUNC.pattern.removesuffix(r"\{").replace(
        r"^[ \t]*", r"(?:^|(?<=[;{}]))[ \t]*", 1)
    pattern = re.compile(head + r"(?:(?:override|final|noexcept)\s*)*(?:=\s*0\s*)?(?:\{|;)", re.M)
    for rel, text in documents.items():
        code = name_metric.strip(text)
        types = list(rename.type_bodies(code))
        sha = digest(text.encode("utf-8", "surrogateescape"))
        def hint(at, declaration, **extra):
            return dict(source=rel, line=code.count("\n", 0, at) + 1 if at is not None else None,
                        declaration=" ".join(declaration.split())[:384], sha256=sha,
                        basis="declaration candidate; not canonical naming proof", **extra)
        parsed = re.sub(r"\b(?:public|private|protected)\s*:", lambda m: " " * len(m[0]), code)
        for match in pattern.finditer(parsed):
            method = match[2]
            if method not in callees:
                continue
            prefix = code[match.start():match.start(1)].strip()
            containers = [(name, begin, end) for name, begin, end in types
                          if begin <= match.start() < end]
            owner = min(containers, key=lambda t: t[2] - t[1])[0] if containers else ""
            qualified_owner = match[1].rstrip(":").split("::")[-1]
            if ((not prefix and method not in (owner, qualified_owner))
                    or prefix.split()[:1] in (["return"], ["throw"], ["delete"])):
                continue  # An invocation is not a declaration.
            if len(signatures[method]) < 4:
                signatures[method].append(hint(match.start(), text[match.start():match.end() - 1],
                                               owner=match[1].rstrip(":") or owner))
        for owner, begin, end in types:
            for member in members:
                if len(fields[member]) >= 4:
                    continue
                for statement in rename.member_statements(code[begin:end], member):
                    declaration = re.search(r"\s+".join(re.escape(token) for token in statement.split()),
                                            code[begin:end])
                    at = begin + declaration.start() if declaration else None
                    fields[member].append(hint(at, statement, owner=owner))
                    if len(fields[member]) >= 4:
                        break
    return signatures, fields


def context(lane, args):
    packet = load(session_path(lane, args.session))
    keys = list(dict.fromkeys(args.key))
    if not 1 <= len(keys) <= 4:
        raise ValueError("request context for one to four unclear binding keys at a time")
    targets = {t["key"]: (rel, t) for rel, s in packet["sources"].items() for t in s["targets"]}
    if set(keys) - targets.keys():
        raise ValueError("context keys must belong to this scoped session")
    result = dict(session=args.session, bindings={}, omitted=[],
        notice="Bounded context hints only. Declarations may be inferred, overloaded or from an inactive "
               "preprocessor branch; inspect candidate owners. Donor declarations are not BFME 2 naming proof. "
               "Missing snippets do not establish absence; no canonical tier is assigned.")
    cached = {}
    for key in keys:
        rel, target = targets[key]
        source = packet["sources"][rel]
        if lane.ctx.resolution_source_sha(rel) != source["sha256"]:
            raise ValueError(f"{rel} changed; prepare a fresh batch")
        function = next(f for f in source["functions"] if key in f["keys"])
        text = function["code"]
        code = name_metric.strip(text)
        body_at = code.find("{") + 1
        word = rename.word_re(target["old"])
        pairs = dict(rename._bracket_pairs(code, "(", ")"))
        calls, members = [], set()
        for match in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", code[body_at:]):
            name = match[1]
            begin = body_at + match.end() - 1
            end = pairs.get(begin, len(code))
            if name in name_metric.KEYWORDS or not word.search(code[begin + 1:end]):
                continue
            calls.append(dict(callee=name, expression=" ".join(text[body_at + match.start():end + 1].split())[:384]))
            if len(calls) >= 6:
                break
        uses = []
        lines = text.splitlines()
        for index, line in enumerate(code.splitlines()):
            if word.search(line):
                uses.append(lines[index].strip()[:240])
                members.update(re.findall(r"(?:->|\.)\s*([A-Za-z_]\w*)", line))
                members.update(re.findall(r"\bm_[A-Za-z_]\w*", line))
        members = set(sorted(members)[:8])
        if rel not in cached:
            cached[rel] = context_documents(lane, rel, source["text"], getattr(args, "context_files", ()) or ())
        documents, omitted = cached[rel]
        signatures, fields = declaration_hints(documents, {c["callee"] for c in calls}, members)
        result["bindings"][key] = dict(function=target["function"], old=target["old"], uses=uses[:6],
            calls=[dict(c, declarations=signatures[c["callee"]]) for c in calls],
            members=[dict(name=name, declarations=fields[name]) for name in sorted(members)])
        result["omitted"].extend(item for item in omitted if item not in result["omitted"])
    print(json.dumps(result, indent=2, ensure_ascii=True))
    return 0


def planner_state():
    """Fence saved decisions against changes to any planner/helper implementation."""
    tools = Path(__file__).resolve().parent
    state = hashlib.sha256(sys.version.encode())
    try:
        for path in sorted(tools.rglob("*.py")):
            state.update(path.relative_to(tools).as_posix().encode() + b"\0")
            state.update(hashlib.sha256(path.read_bytes()).digest())
    except OSError:
        return None
    return state.hexdigest()


def fingerprint(raw):
    return digest(raw) if raw is not None else None


class PreviewContext(rename.Context):
    """Fresh caches ensure every dependency used by a preview is recorded."""
    def __init__(self, base, tables=None):
        super().__init__(base.root, object_scan=base.object_scan, sweep_dirs=base.sweep_dirs)
        self.base, self.reads, self.queries = base, {}, {}
        self.tables = tables if tables is not None else {}

    def read(self, rel):
        raw = self.base.read(rel)
        self.reads[rel] = fingerprint(raw)
        return raw

    def git(self, *args):
        output = self.base.git(*args)
        self.queries[args] = digest(output.encode("utf-8", "surrogateescape"))
        return output

    def dicts(self, rel):
        # Retain preview's existing shared ledger parsing without losing the
        # per-source read footprint. Key by content so mid-preview changes
        # never pair an old table with a new dependency fingerprint.
        if rel not in self._cache:
            raw = self.read(rel)
            key = (rel, fingerprint(raw))
            if key not in self.tables:
                self.tables[key] = list(csv.DictReader(io.StringIO(raw.decode("utf-8")))) if raw else []
            self._cache[rel] = self.tables[key]
        return self._cache[rel]


HISTORY = {rename.NAME_BASIS: rename.NAME_BASIS_HEADER,
           rename.NAME_BINDINGS: rename.NAME_BINDINGS_HEADER}


def saved_candidate(plan):
    """Store only a scoped identifier edit and append-only evidence, never a pickle."""
    if plan.kind not in ("param", "local") or set(plan.after) - {plan.source, *HISTORY}:
        raise ValueError("not a scoped candidate")
    metadata = {key: getattr(plan, key) for key in (
        "kind", "old", "new", "basis", "evidence", "source", "rva", "old_word", "new_word",
        "source_counts", "claims")}
    rows = {}
    for rel, header in HISTORY.items():
        if rel not in plan.after:
            continue
        initial = plan.before[rel]
        initial = (header + "\n").encode() if initial is None else initial
        if not plan.after[rel].startswith(initial):
            raise ValueError("saved scoped history is not append-only")
        rows[rel] = base64.b64encode(plan.after[rel][len(initial):]).decode("ascii")
    return dict(metadata=metadata, source_after=base64.b64encode(plan.after[plan.source]).decode("ascii"), rows=rows)


def restored_candidate(ctx, rel, item):
    metadata = item["metadata"]
    if metadata["source"] != rel or metadata["kind"] not in ("param", "local") or metadata["basis"] != "inferred":
        raise ValueError("wrong scoped candidate")
    plan = rename.Plan(**metadata)
    plan.edit(ctx, rel, base64.b64decode(item["source_after"], validate=True))
    for path, encoded in item["rows"].items():
        if path not in HISTORY:
            raise ValueError("saved scoped plan edits another ledger")
        plan.edit(ctx, path, rename.appended(ctx.read(path),
            [base64.b64decode(encoded, validate=True)], header=HISTORY[path]))
    plan.verify = [rel]
    return plan


class PreviewPlans:
    """One session's reviewed candidates; validated inside each transaction's lock."""
    def __init__(self, lane, path, review):
        self.base, self.cache = lane.ctx, {}
        self.reused_sources, self.reused_names = set(), 0
        try:
            raw = path.read_bytes()
            if review.get("plan_sha256") != digest(raw):
                return
            cache = json.loads(raw)
            if isinstance(cache, dict) and cache.get("version") == 1 and cache.get("root") == str(lane.root):
                self.cache = cache
        except (OSError, ValueError, TypeError):
            pass  # Older sessions and damaged/missing artifacts use ordinary planning.

    def begin(self):
        # A restored retry takes a new lock interval and must see intervening changes.
        self.reads, self.queries = {}, {}
        rules = planner_state()
        self.current = bool(self.cache) and rules is not None and self.cache.get("rules") == rules

    def get(self, ctx, request):
        if not self.current:
            return None
        rel = request["source"]
        try:
            record = self.cache["sources"][rel]
            if record["source_sha256"] != request["expected_source_sha"]:
                return None
            for path, expected in record["reads"].items():
                if path in HISTORY:
                    # Earlier requests append only inferred scoped history. Validate
                    # against the disk baseline, then append to the current view.
                    # Foreign history changes (including canonical approvals) invalidate.
                    if path not in self.reads:
                        self.reads[path] = fingerprint(self.base.read(path))
                    actual = self.reads[path]
                else:
                    actual = fingerprint(ctx.read(path))
                if actual != expected:
                    return None
            for args, expected in record["queries"]:
                args = tuple(args)
                if args not in self.queries:
                    self.queries[args] = digest(ctx.git(*args).encode("utf-8", "surrogateescape"))
                if self.queries[args] != expected:
                    return None
            if sorted(rename.header_closure(ctx, rel)) != record["headers"]:
                return None  # Also recheck donor header trust and pin/worktree state.
            if rename.compile_flags(ctx, rel) != record["flags"]:
                return None
            found = {}
            for entry in request["entries"]:
                key = rename.scoped_entry_key(entry)
                if key in record["candidates"]:
                    found[key] = restored_candidate(ctx, rel, record["candidates"][key])
                elif key in record["refused"]:
                    found[key] = record["refused"][key]
            self.reused_names += sum(isinstance(p, rename.Plan) for p in found.values())
            if found:
                self.reused_sources.add(rel)
            return found
        except (KeyError, ValueError, TypeError, OSError, rename.Refusal):
            return None


def preview(lane, args):
    path = session_path(lane, args.session)
    raw = lane.path(args.answer).read_bytes()
    packet, answers = load(path), json.loads(raw)
    requests, report = prepare(lane, packet, answers)
    report.update(proposal_sha256=digest(raw), sources={}, refused={})
    cache = dict(version=1, root=str(lane.root), rules=planner_state(), sources={})
    tables = {}
    for _, request in requests:
        context = PreviewContext(lane.ctx, tables)
        try:
            plan = rename.plan_scoped_set(context, **request)
        except rename.Refusal as exc:
            report["refused"][request["source"]] = str(exc)
            continue
        rel = request["source"]
        headers = sorted(rename.header_closure(context, rel))
        flags = rename.compile_flags(context, rel)
        # build.py reads these directly when using the real repository root.
        context.read(rename.FLAG_OVERRIDES)
        context.read("reverse/retail_inventory/flag_regions.csv")
        cache["sources"][rel] = dict(source_sha256=request["expected_source_sha"],
            reads=context.reads, queries=list(context.queries.items()), headers=headers, flags=flags,
            candidates={rename.scoped_entry_key(request["entries"][index]): saved_candidate(candidate)
                        for index, candidate in plan.scoped_plans},
            refused={rename.scoped_entry_key(request["entries"][int(index)]): reason
                     for index, reason in plan.scoped_refused.items()})
        report["sources"][rel] = dict(diff="".join(difflib.unified_diff(
            packet["sources"][rel]["text"].splitlines(True),
            plan.after[rel].decode("utf-8", "surrogateescape").splitlines(True),
            fromfile=rel, tofile=rel)), refused=getattr(plan, "scoped_refused", {}))
    save(path.with_suffix(".preview.json"), report)
    form = dict(proposal_sha256=digest(raw), scan_complete=False, decisions={}, coverage_checked=False)
    if cache["rules"] is not None and cache["rules"] == planner_state():
        saved = path.with_suffix(".plans.json")
        save(saved, cache)
        form["plan_sha256"] = digest(saved.read_bytes())
    save(path.with_suffix(".review.json"), form)
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
    saved = PreviewPlans(lane, path.with_suffix(".plans.json"), review)
    if requests:
        # Existing run transaction provides one claim, journal, build and ledger
        # verification. A failed combined build restores all sources; do not
        # blindly retry the same batch or degrade to per-name compilation.
        def counted_verify(ctx, sources):
            report["verification_runs"] += 1
            return verify(ctx, sources)
        result = rename.run_batch(lane.ctx, requests, verify=counted_verify, checks=checks, scoped_plans=saved)
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
                result = rename.run_batch(lane.ctx, survivors, verify=counted_verify, checks=checks, scoped_plans=saved)
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
    report.update(reused_sources=len(saved.reused_sources), reused_names=saved.reused_names)
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
    if complete and not packet.get("related_functions"):
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
    n.add_argument("--functions", nargs="+", help="complete inspected function scopes; requires --files")
    n.add_argument("--under", help="source directory prefix")
    n.add_argument("--target", type=int, default=200, help="soft binding target; never cut a function")
    n.add_argument("--max-files", type=int, default=32)
    n.add_argument("--max-chars", type=int, default=250000)
    c = sub.add_parser("context", help="show bounded declaration hints for unclear scoped bindings")
    c.add_argument("--session", required=True)
    c.add_argument("--key", action="append", required=True, help="one served binding key; repeat for up to four")
    c.add_argument("--context-files", nargs="+", help="up to eight explicitly relevant code/header paths")
    m = sub.add_parser("merge", help="combine native-child parts with exact per-binding attribution")
    m.add_argument("--session", required=True)
    m.add_argument("--parts", nargs="+", required=True)
    for command in ("preview", "apply"):
        p = sub.add_parser(command)
        p.add_argument("--session", required=True)
        p.add_argument("--answer", required=True)
        if command == "apply":
            p.add_argument("--review", required=True)


def run(lane, args):
    return {"next": next_batch, "context": context, "merge": merge,
            "preview": preview, "apply": apply}[args.scoped_cmd](lane, args)
