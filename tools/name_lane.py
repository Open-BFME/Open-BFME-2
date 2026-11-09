#!/usr/bin/env python3
"""Shared inferred names use independent blind proposals. Locals and parameters
use `scoped next`, native sub-agent proposals and parent-reviewed batch application.

Most placeholders (Rva..., bfme..., m_2C, param_1, iVar3) sit where no export,
WorldBuilder lead, Zero Hour twin or retail string says what the thing is
called; tools/name_evidence.py serves the few that do. For the rest the owner
rule is BFME 1's: a descriptive name that is not proven canonical still gets a
clean readable identifier under the review policy above, and the ledger --
reverse/name_basis.csv, written by tools/rename.py --
records it as `inferred`, revocable through `dispute`. BFME 1's 2026-09-29
spike measured why: one model alone named about 60% of placeholders right and
2-9% misleadingly; two independent proposals that agreed were about 80% right
and never misleading.

    python3 tools/name_lane.py register-data --source SOURCE --address ADDRESS --address-kind va --size SIZE --type TYPE --users USER --evidence TEXT
    python3 tools/name_lane.py next --session S --model M [--count N] [--subsystem Code/...] [--file F] [--list-only]
    python3 tools/name_lane.py submit ANSWER.json --session S --model M
    python3 tools/name_lane.py submit ANSWER.json --session S --model M --propose-only
    python3 tools/name_lane.py apply [--retry-blocked] [--lead 2] [--min-models 1] [--only-labels L,L]
    python3 tools/name_lane.py dispute KEY... --reason TEXT
    python3 tools/name_lane.py status [--only-labels L,L] [--lead 2] [--min-models 1]
    python3 tools/name_lane.py agree --key KEY --name SPELLING [--lead 2] [--min-models 1]

Blind votes from different checkouts land through separate pushes, so each submit can
tally before the other vote exists and neither records the agreement. `status` and
`apply` derive such keys from the votes as they stand. Votes hold only hashes, so a key's
spelling must come from someone who knows it: `agree`, or a submit of the worker's own
counted vote, records the agreement without adding a vote, and only for a spelling that
hashes to the votes' winning hash and passes today's checks.

Every path that records an agreement (submit, agree, a re-submit, resolve) needs two voters
whose fingerprints in reverse/name_vote_sources.csv match the file as it reads today. A vote
for an older text, or from before fingerprints existed, no longer counts towards one: the key
needs fresh votes from other workers. This is intended. `apply` holds a later record to the
same rule: when its source has changed it lands nothing and reopens the key (source-changed).
A verified landing whose change to the file is exactly its rename carries the fingerprints of the
file's other votes across it (carry_verified_votes); any other difference reopens.
The records older than AGREED_CUTOFF_ROWS stand with no check; status and apply list them.

A compiler-spelled row (an operator, special member or template member whose mangled name
carries a placeholder type) has no identifier of its own, so its key's placeholder is its
whole old spelling and each vote answers with a whole new one, compared exactly. There are
thousands and most need only a class rename, so one is served only by `next --key KEY`. It
lands by tools/rename.py function --respell --identity, not by `apply`.

`next` serves matched, non-generated Code/ sources from one subsystem, with
shared existing-source context. Each file decides only its own identifiers --
functions it owns rows for, classes only it
defines, their used members, and file globals it owns data rows for -- that are
placeholder or weak (tools/name_metric.py's definition, which tools/rename.py
shares). It writes a
brief to build/name_lane/briefs/<session>.txt: the fixed style rules, the keys
to answer, the file's text, callers spelling its functions, the retail strings
its rows reference and tools/name_evidence.py hints. A skip costs nothing; a
wrong name misleads readers.

`submit` stores each vote only as sha256(key|canon(name))[:24] in
reverse/name_votes.csv (append-only). canon() folds word order, plurals and
common abbreviations, so m_ladderComboBox and m_comboBoxLadder are one vote,
and names requiring blind agreement stay hidden until a second worker matches.
New parameter/local votes are refused, including submissions from old sessions.
Use `scoped next` to review those names together in their complete functions.
Every vote and every served session
record carries the voter's worker identity (tools/name_agreement.py: hashed
BFME_CLAIM_OWNER / BFME_RUN_ID, else CLAUDE_CODE_SESSION_ID, else
tools/claims.py's owner), read from the environment rather than from
`--session`, which is only a label: `submit` refuses a session `next` served
to another worker, a worker votes once per key whatever label it uses, and
agreement counts distinct workers. An orchestrator running blind seats gives
each its own BFME_CLAIM_OWNER, as it already does for claims. When a vote
makes a shared name win (two distinct workers with a lead of `--lead` votes
over every rival spelling, optionally
`--min-models` distinct models; files another
model voted on are served first), the name is written to
reverse/name_agreed.csv as `agreed`.

Normal CLI submission applies every newly agreed key in one verified run batch,
then automatically configures an installed independent-review CLI when needed.
The reviewer compares disagreements and applies its newly agreed batches too.
`--propose-only` explicitly records votes without either source application or
automatic reviewer dispatch. Library callers opt into this cycle with
`auto_workflow=True`; reviewer-internal submissions remain proposal-only.

`apply` lands each agreed key through tools/rename.py's library API with
basis `inferred` and evidence `agree:<id>`; rename.py's check_agreement uses
that row only as an index (id,kind,old,new,rva,key) and recomputes the
agreement from the votes, then claims, rewrites every reference,
byte-verifies every touched unit and restores everything on any failure.
Outcomes are appended to name_agreed.csv: landed, blocked (the refusal or
failure), stale (the file changed or the placeholder is gone). `dispute`
puts landed names back through rename.py's own reversal entry point
(rename.revert: the exact inverse of the recorded inferred rename, recorded
append-only as basis `restored`), records the reason, and refuses that
spelling for the key from then on.

Eligible names share one run-wide transaction, claim operation, build and set
of ledger checks. Every name still passes its ordinary planner and agreement
check. A failed transaction is restored and split into smaller groups until
the failing names are isolated. `apply --per-file` retains file grouping;
`apply --no-batch` retains per-name verification.

`apply` lands every waiting key whose votes win, including agreements that
only other contributors' voters reached and historical scoped approvals.
Historical votes and reversal rules are preserved; unfinished scoped tasks
need fresh scoped review, not more votes. `apply --only-labels seat-a,seat-b`
restricts a pass to agreements reached by its own seats: a key is applied only
when EVERY worker that voted the winning spelling voted under one of the listed
`--model` labels (the vote's label is its `model` column; labels are matched
after the same normalisation `--model` gets). A key whose winning spelling has
any voter outside the list -- including one whose lead over a rival rests on
such a voter -- is left untouched: it stays `waiting` for whoever applies it,
is not marked blocked or stale, and nothing is written for it in
name_agreed.csv. Rival spellings count against the lead whoever voted them, as
without the filter. `--retry-blocked` composes with the filter. `status
--only-labels ...` reports how many waiting keys the filter would select (under
the same `--lead`/`--min-models`; it does not look at the source, so a key that
`apply` would find stale is still counted). Without the option nothing changes.

name_agreed.csv columns: id,kind,old,new,rva,agents,key,status,detail -- the
first six are rename.py's agreement record, `new` is the agreed name, `key`
is the lane key (source|kind|scope|placeholder). Both lane files are
append-only and union-merged; the latest row of a key is its state.
"""
import argparse
import collections
import csv
import datetime
import hashlib
import io
import json
import os
import random
import re
import shlex
import subprocess
import sys
import time
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import name_agreement  # noqa: E402
import name_metric  # noqa: E402
import rename  # noqa: E402
import claims  # noqa: E402

VOTES = name_agreement.VOTES
AGREED = name_agreement.AGREED
VOTE_COLUMNS = name_agreement.VOTE_COLUMNS
AGREED_COLUMNS = name_agreement.AGREED_COLUMNS
MEANINGS = name_agreement.MEANINGS
MEANING_COLUMNS = name_agreement.MEANING_COLUMNS
# beside each vote, the sha256 of the source text it was served (append-only): a vote's
# own row names its key and spelling but not the text, and a credit for a registered
# class's rename binds every vote to the text it is applied to (rename.votes_bound_to_text)
VOTE_SOURCES = rename.VOTE_SOURCES
VOTE_SOURCE_COLUMNS = ["key", "hash", "worker", "session", "source_sha"]
RESOLUTIONS = name_agreement.RESOLUTIONS
RESOLUTION_COLUMNS = name_agreement.RESOLUTION_COLUMNS
LANE_DIR = "build/name_lane"
EVIDENCE_TSV = "build/name_evidence.tsv"
MAX_CHARS = 15000
KINDS = ("function", "class", "member", "param", "local", "global")
NAMED = ("class", "member", "function", "global")
SCOPED_KINDS = frozenset(("param", "local"))


def scoped_route(session="names", model="MODEL", sources=()):
    scoped_session = re.sub(r"[^A-Za-z0-9_-]", "_", session[:60]) + "-scoped"
    command = ["python3", "tools/name_lane.py", "scoped", "next",
               "--session", scoped_session, "--model", model]
    if sources:
        command += ["--files", *dict.fromkeys(sources)]
    return ("Locals and parameters require a fresh scoped batch: " + shlex.join(command)
            + ". A native sub-agent proposes complete functions; run scoped preview, "
              "then the parent reviews the mapping and diff, resolves questionable "
              "names and runs scoped apply for the whole batch.")

# rename order inside one file: a member's key names its class and a param's
# key names its function, so those land before the class or function moves
LAND_ORDER = {"member": 0, "param": 1, "local": 1, "global": 2, "function": 3, "class": 4}
FAMILY = re.compile(r"(?:a|d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]+")
GENERIC = {"data", "info", "value", "temp", "tmp", "helper", "thing", "stuff", "foo", "bar", "obj", "var", "func",
           "method", "unknown", "misc", "item", "object", "result", "ret", "field", "member", "param", "arg", "local"}
DIRECTIVE = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
MACRO = re.compile(r"^[ \t]*#[ \t]*(?:define|undef)[ \t]+([A-Za-z_]\w*)", re.M)
STATUS_RANK = {"agreed": 0, "source-changed": 0, "stale": 1, "blocked": 2, "landed": 3, "disputed": 4}
# A key with one of these has no standing record: it is served again and can be agreed again. A
# source-changed record ranks with agreed, so a later agreement of the same id replaces it.
REOPENED = ("disputed", "source-changed")
# The first rows of name_agreed.csv predate vote fingerprints. They stand without a source check
# (grandfathered, docs/naming.md); any later record needs fresh votes when apply lands it. The file
# is append-only, so those rows are pinned by hash: a moved or edited row earns no exemption.
AGREED_CUTOFF_SHA256 = "d4601728085253f5220593b916182bdeb165dd0e35fb9cecc86ee4d243361b46"
AGREED_CUTOFF_ROWS = 19215


def fail(message):
    sys.exit(f"name_lane: {message}")


# ---------------------------------------------------------------- votes

canon = name_agreement.canon
digest = name_agreement.digest
wins = name_agreement.wins


def label_list(text):
    """--only-labels: a comma-separated list of voter labels, normalised like --model."""
    labels = {model_id(part) for part in (text or "").split(",") if part.strip()}
    if not labels:
        fail(f"--only-labels {text!r}: pass the labels your seats vote under, e.g. seat-a,seat-b")
    return labels


def own_voters(mine, labels):
    """True when `mine` ({worker: label}) has voters and every one carries a listed label."""
    return bool(mine) and all(label in labels for label in mine.values())


def refuted(key, canons):
    """The vote hashes of a key's disputed spellings: they no longer count as rivals."""
    return {name_agreement.hash_canon(key, c) for c in canons}


def record_id(key, name, meaning=None):
    return "nl-" + hashlib.sha256(f"{key}|{name}".encode()).hexdigest()[:12] + \
        ("-m" + meaning if meaning else "")


def proposal_path(lane, key, worker):
    token = hashlib.sha256(f"{key}|{worker}".encode()).hexdigest()
    return lane.path(f"{LANE_DIR}/proposals/{token}.json")


def approval_support(tally, refused, row):
    return name_agreement.support(tally, refused, row["key"], row["new"],
                                  name_agreement.record_meaning(row["id"]))


def approval_detail(tally, refused, row):
    if row["id"].startswith("nr-"):
        return "reviewed resolution: original voters accepted the selected name"
    mine, rivals, meaning = approval_support(tally, refused, row)
    return ("meaning agreement; " if meaning else "") + name_agreement.review_detail(row["key"], mine, rivals)


def resolution_support(lane, row):
    key, name = row["key"], row["new"]
    source = lane.ctx.read(split_key(key)[0])
    source_sha = hashlib.sha256(source).hexdigest() if source is not None else ""
    expected = "nr-" + hashlib.sha256(f"{key}|{name}|{source_sha}".encode()).hexdigest()[:24]
    votes, agreed = lane.votes(), lane.agreed_rows()
    resolutions = lane.resolutions()
    voters, _ = name_agreement.resolved_workers(votes, agreed, resolutions, key, name, source_sha)
    valid = row["id"] == expected and not name_agreement.verify_resolution(
        votes, agreed, resolutions, key, name, source_sha)
    return voters, valid


def model_id(text):
    """A normalised model label: lower case, no spaces."""
    model = re.sub(r"\s+", "-", (text or "").strip().lower())
    if not re.fullmatch(r"[a-z0-9][a-z0-9._-]*", model):
        fail(f"--model {text!r}: pass the label you vote under, e.g. seat-a")
    return model


def session_id(text):
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._-]{0,63}", text or ""):
        fail(f"--session {text!r}: letters, digits, '.', '_' or '-' (at most 64)")
    return text


def record_typedef_names(text):
    """Bare by-value aliases of explicitly declared struct/class types.

    This narrow reader does not infer primitive aliases, pointers, arrays,
    functions, alias chains or macros. A header spelling is type-admission
    evidence only, never a target layout or a canonical naming basis.
    """
    # MSVC may continue a define over a blank after its backslash. Remove
    # that longer interpretation too before using text as positive evidence.
    code = rename._DEFINE_BLANK.sub("", name_metric.strip(text))
    code = name_metric.PREPROCESSOR.sub("", code)
    ident = r"[A-Za-z_]\w*"
    aliases = rf"(?P<names>{ident}(?:\s*,\s*{ident})*)\s*;"
    names = set()
    for match in re.finditer(rf"\btypedef\s+(?:struct|class)(?:\s+{ident})?\s*\{{", code):
        end = name_metric.close(code, match.end() - 1)
        if end == len(code):
            continue
        tail = re.match(rf"\s*{aliases}", code[end + 1:])
        if tail:
            names.update(re.findall(ident, tail.group("names")))
    for match in re.finditer(rf"\btypedef\s+(?:struct|class)\s+{ident}\s+{aliases}", code):
        names.update(re.findall(ident, match.group("names")))
    return names


# ---------------------------------------------------------------- the lane


DATA_REQUESTS = 'reverse/name_data_requests.csv'
DATA_REQUEST_COLUMNS = ['source', 'rva', 'size', 'type', 'users', 'evidence', 'registrant']
UNROWED_IDENT = 'unrowedData'


def data_request_key(row):
    payload = json.dumps({c: row[c] for c in DATA_REQUEST_COLUMNS}, sort_keys=True, separators=(',', ':'))
    scope = 'unrowed:' + hashlib.sha256(payload.encode()).hexdigest()
    return key_of(row['source'], 'global', scope, UNROWED_IDENT)


def unrowed_key(key):
    parts = key.split('|')
    return len(parts) == 4 and parts[1] == 'global' and parts[2].startswith('unrowed:') and parts[3] == UNROWED_IDENT


def check_unrowed(lane, row, *, check_users=True, notes=None):
    """One unowned retail data range; this names nothing and admits no bytes."""
    import data_rows
    source = row['source']
    if not name_agreement.WORKER.fullmatch(row.get('registrant', '')):
        raise rename.Refusal('unrowed data needs its original registrant')
    if (not source.startswith('Code/') or Path(source).suffix not in ('.cpp', '.c')
            or any(p in ('', '.', '..') for p in source.split('/')) or '\\' in source
            or rename.is_generated(source) or lane.text(source) is None
            or not lane.git('ls-files', '--error-unmatch', '--', source).strip()):
        raise rename.Refusal('unrowed data needs an existing tracked, non-generated Code/ source')
    rva, size = int(row['rva'], 16), int(row['size'])
    if size <= 0 or not re.fullmatch(r'[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*(?:\s*\*)?', row['type']):
        raise rename.Refusal('provide a positive size and a C++ type/struct name')
    if not row['evidence'].strip():
        raise rename.Refusal('unrowed data needs caller evidence')
    va = data_rows.IMAGE_BASE + rva
    homes = [s for s in data_rows.retail_sections() if s[1] <= va and va + size <= s[2]
             and not s[3] & data_rows.EXECUTABLE]
    if len(homes) != 1:
        raise rename.Refusal('unrowed range must fit one non-executable retail section')
    for owned in lane.ctx.dicts(rename.DATA_ROWS):
        start = data_rows.va_of(owned)
        if start < va + size and va < start + int(owned['size']):
            raise rename.Refusal('address already has an overlapping data_rows.csv owner')
    for owned in lane.ctx.dicts('reverse/data_ledger.csv'):
        start = data_rows.IMAGE_BASE + int(owned['address'], 16)
        if start < va + size and va < start + int(owned['size'], 0):
            # Ledger sizes are next-address upper bounds, not allocation proof.
            # Proven extents live in data_rows and were checked above; an
            # observed source owner still fences its whole current range.
            if owned.get('source', '').strip():
                raise rename.Refusal('address already has an overlapping data_ledger.csv owner')
            if notes is not None:
                notes.append(f"unowned data_ledger.csv upper bound overlaps: {owned['name']} "
                             f"at {owned['address']} + {owned['size']} bytes; not a proven extent")
    for owned in lane.ctx.dicts('reverse/data_converged.csv'):
        if int(owned['address'], 16) == va:
            raise rename.Refusal('address already has a converged global owner')
    users = json.loads(row['users'])
    if not isinstance(users, dict) or not users:
        raise rename.Refusal('unrowed data needs its user source paths')
    for path, sha in users.items():
        text = lane.ctx.read(path)
        if (not path.startswith('Code/') or any(p in ('', '.', '..') for p in path.split('/'))
                or '\\' in path or text is None):
            raise rename.Refusal('invalid or missing user source: ' + path)
        if check_users and path != source and hashlib.sha256(text).hexdigest() != sha:
            raise rename.Refusal('user evidence changed; register a fresh naming key: ' + path)
    rename.inferred_guards(lane.ctx, 'global', UNROWED_IDENT, UNROWED_IDENT, rva)
    return homes[0][0]


def register_data(lane, *, source, address, address_kind, size, type_name, users, evidence):
    """Persist caller facts only, so both blind seats see the identical request."""
    import data_rows
    if address_kind not in ('va', 'rva'):
        raise rename.Refusal('address_kind must be va or rva')
    rva = int(address, 0) - (data_rows.IMAGE_BASE if address_kind == 'va' else 0)
    row = dict(source=source, rva=f'0x{rva:08X}', size=str(size), type=type_name,
               users=json.dumps({p: hashlib.sha256(lane.ctx.read(p) or b'').hexdigest() for p in sorted(set(users))},
                                sort_keys=True, separators=(',', ':')), evidence=evidence, registrant=lane.worker())
    notes = []
    check_unrowed(lane, row, notes=notes)
    for note in notes:
        print('name_lane: note: ' + note, file=sys.stderr)
    existing = lane.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS)
    for other in existing:
        if int(other['rva'], 16) < rva + size and rva < int(other['rva'], 16) + int(other['size']):
            if all(other[c] == row[c] for c in DATA_REQUEST_COLUMNS if c != 'registrant'):
                return data_request_key(other)  # first registrant is immutable

            try:
                check_unrowed(lane, other)
            except (rename.Refusal, ValueError):
                continue  # stale evidence gets a fresh key, never its old votes
            raise rename.Refusal('a different unrowed request already covers this range')
    lane.append(DATA_REQUESTS, DATA_REQUEST_COLUMNS, [row])
    return data_request_key(row)


def request_for_key(lane, key):
    return next((r for r in lane.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS) if data_request_key(r) == key), None)


def evidence_references(lane, evidence):
    """Only validated repository file/line references enter a blind packet."""
    references = []
    for path, number in re.findall(r'\b((?:Code|reference)/[A-Za-z0-9_./-]+):(\d+)\b', evidence):
        text = lane.text(path)
        line = int(number)
        if (any(p in ('', '.', '..') for p in path.split('/')) or text is None
                or not 1 <= line <= len(text.splitlines())):
            continue
        reference = dict(file=path, line=line)
        if reference not in references:
            references.append(reference)
    return references


def evidence_source(lane, path, references):
    """Bounded, line-numbered source context; full source hashes still fence votes."""
    text = lane.text(path) or ''
    if len(text) <= MAX_CHARS:
        return text
    lines = text.splitlines()
    anchors = sorted({r['line'] for r in references if r['file'] == path})
    selected = sorted({i for line in anchors[:12]
                       for i in range(max(0, line - 9), min(len(lines), line + 8))})
    heading = f'// EXCERPTS from {path} ({len(text)} characters; full source omitted)\n'
    if not selected:
        return heading + '// No evidence line references for this file; inspect it before naming or skip.\n'
    return heading + '\n'.join(f'{i + 1}: {lines[i][:400]}' +
                               (' /* line truncated */' if len(lines[i]) > 400 else '') for i in selected)


def packet_source(lane, rel, items):
    requests = [request_for_key(lane, key_of(rel, *item[:3])) for item in items]
    references = [ref for request in requests if request
                  for ref in evidence_references(lane, request['evidence'])]
    text = (evidence_source(lane, rel, references) if requests and all(requests)
            else lane.text(rel) or '')
    return dict(file=rel, source=text)


def request_packet(lane, key):
    request = request_for_key(lane, key)
    if request is None:
        return None
    return {**{c: request[c] for c in ('source', 'rva', 'size', 'type', 'users')},
            'evidence': evidence_references(lane, request['evidence']),
            'user_sources': {p: evidence_source(lane, p, evidence_references(lane, request['evidence']))
                             for p in json.loads(request['users'])}}


def check_unrowed_agreement(lane, approval):
    """Recompute quorum without the registrant, including hand-forged votes."""
    request = request_for_key(lane, approval['key'])
    if request is None or not name_agreement.WORKER.fullmatch(request.get('registrant', '')):
        raise rename.Refusal('unrowed request needs its original registrant')
    votes = [v for v in lane.votes() if v.get('worker') != request['registrant']]
    problems = name_agreement.verify(votes, lane.agreed_rows(), approval['key'], approval['new'])
    if problems:
        raise rename.Refusal('unrowed agreement excludes the registrant: ' + '; '.join(problems))


def packet_target(lane, source, item):
    key = key_of(source, *item[:3])
    target = dict(key=key, kind=item[0], scope=item[1], placeholder=item[2], rva=item[3])
    if unrowed_key(key):
        target['data_request'] = request_packet(lane, key)
    return target


def data_request_items(lane, source):
    items = []
    for row in lane.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS):
        if row['source'] == source and row.get('registrant') != lane.worker():
            try:
                check_unrowed(lane, row)
            except (rename.Refusal, ValueError):
                continue
            _, kind, scope, ident = split_key(data_request_key(row))
            items.append((kind, scope, ident, int(row['rva'], 16)))
    return items

class Lane:
    """The lane's view of one tree; tests point it at a miniature repository."""

    def __init__(self, root=ROOT, ctx=None):
        self.root = Path(root).resolve()
        self.ctx = ctx or rename.Context(self.root, object_scan=self.root == ROOT.resolve())
        self._types = {}
        self._registered = None
        self._donor = {}

    def path(self, rel):
        return self.root / rel

    def text(self, rel):
        data = self.ctx.read(rel)
        return data.decode("utf-8", errors="surrogateescape") if data is not None else None

    def git(self, *args):
        return subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True,
                              encoding="utf-8", errors="replace").stdout

    # ------------------------------------------------------------ tables

    def table(self, rel, columns):
        raw = self.path(rel).read_text(encoding="utf-8") if self.path(rel).exists() else ""
        rows = list(csv.DictReader(io.StringIO(raw)))
        if raw and next(csv.reader(io.StringIO(raw)), []) != columns:
            fail(f"{rel} has columns {next(csv.reader(io.StringIO(raw)))}, expected {columns}")
        return rows

    def append(self, rel, columns, rows):
        """Append under build/name_lane/.lock; the files are append-only."""
        from portable_lock import lock, unlock
        if not rows:
            return
        self.path(LANE_DIR).mkdir(parents=True, exist_ok=True)
        with self.path(f"{LANE_DIR}/.lock").open("a") as handle:
            lock(handle, exclusive=True, wait_notice="name_lane: waiting for the lane lock...")
            try:
                path = self.path(rel)
                raw = path.read_bytes() if path.exists() else b""
                out = io.StringIO()
                writer = csv.DictWriter(out, columns, lineterminator="\n")
                if not raw:
                    writer.writeheader()
                elif not raw.endswith(b"\n"):
                    out.write("\n")
                writer.writerows({c: r.get(c, "") for c in columns} for r in rows)
                with path.open("ab") as f:
                    f.write(out.getvalue().encode("utf-8"))
            finally:
                unlock(handle)
        self.ctx._cache.pop(rel, None)

    def votes(self):
        return self.table(VOTES, VOTE_COLUMNS)

    def agreed_rows(self):
        return self.table(AGREED, AGREED_COLUMNS)

    def resolutions(self):
        return self.table(RESOLUTIONS, RESOLUTION_COLUMNS)

    def state(self):
        """key -> its state row. A key's current record is its latest agreement
        id (a dispute refuses its spelling, so a re-agreement is a new id);
        within one id the highest status wins -- disputed, landed, blocked,
        stale, agreed -- because union merges may interleave concurrent rows.
        A later blocked row of the same rank (--retry-blocked) wins too."""
        by_key = collections.defaultdict(dict)
        for row in self.agreed_rows():
            by_key[row["key"]].setdefault(row["id"], []).append(row)
        out = {}
        for key, ids in by_key.items():
            rows = list(ids.values())[-1]
            # A source-changed row closes the record before it, a blocked attempt included, so the
            # key reopens; a later agreement of the same id then replaces it. Not a landing or dispute.
            closed = [i for i, row in enumerate(rows) if row["status"] == "source-changed"]
            if closed and not any(row["status"] in ("landed", "disputed") for row in rows[:closed[-1]]):
                rows = rows[closed[-1]:]
            best = rows[0]
            for row in rows[1:]:
                if STATUS_RANK.get(row["status"], -1) >= STATUS_RANK.get(best["status"], -1):
                    best = row
            out[key] = best
        return out

    def grandfathered(self):
        """The ids of agreement records from before vote fingerprints (AGREED_CUTOFF_ROWS), or
        none when the file's first rows are no longer the ones pinned (grandfather_fault)."""
        if self.grandfather_fault():
            return set()
        return {row["id"] for row in self.agreed_rows()[:AGREED_CUTOFF_ROWS]}

    def grandfather_fault(self):
        """Why name_agreed.csv's first AGREED_CUTOFF_ROWS rows are not the pinned ones, or None."""
        if not AGREED_CUTOFF_ROWS:
            return None
        rows = self.agreed_rows()[:AGREED_CUTOFF_ROWS]
        if len(rows) == AGREED_CUTOFF_ROWS and agreed_prefix_hash(rows) == AGREED_CUTOFF_SHA256:
            return None
        return (f"{AGREED}'s first {AGREED_CUTOFF_ROWS} rows do not hash to the pinned cutoff: the file is append-only, "
                "so a row was moved, edited or removed; no record is grandfathered until that is put right")

    def disputed(self):
        """key -> canon spellings refused for it."""
        return name_agreement.disputed(self.agreed_rows())

    def tally(self):
        """key -> hash -> {worker: model}: distinct workers, not session labels."""
        registrants = {data_request_key(r): r.get('registrant')
                       for r in self.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS)}
        votes = [v for v in self.votes() if v.get('worker') != registrants.get(v.get('key'), '__not_a_registrant__')]
        return name_agreement.tally(votes, self.table(MEANINGS, MEANING_COLUMNS))

    def worker(self):
        """This environment's worker id (tools/name_agreement.py)."""
        return name_agreement.worker_identity(self.root)

    # ------------------------------------------------------------ evidence

    def ledger(self):
        if "_by_source" not in self.ctx._cache:
            by = collections.defaultdict(list)
            for r in self.ctx.rows():
                if r.get("status") == "matched":
                    by[r.get("source", "")].append(r)
            self.ctx._cache["_by_source"] = by
        return self.ctx._cache["_by_source"]

    def subsystem(self, rel):
        """(directory, basis) for scheduling, never a naming/merge approval.

        A fresh map must approve every owned row under non-provisional TUs in
        one directory to route a fragmented source elsewhere. Other files are
        explicitly grouped by their actual source directory.
        """
        if not hasattr(self, "_subsystems"):
            import tu_map
            self._subsystems = {}
            self.subsystem_map_stale = tu_map.check_fresh(tu_map.Layout(self.root))
            if not self.subsystem_map_stale:
                mapping = tu_map.load(self.root)
                for source, rows in self.ledger().items():
                    directories = set()
                    for row in rows:
                        entries = [r for r in mapping.get(rename._rva(row.get("target_rva")), ())
                                   if r["kind"].startswith("code") and r.get("source") == source]
                        targets = {tu_map.approved_tu(mapping, r) for r in entries
                                   if not tu_map.provisional_name(r)}
                        if len(entries) != 1 or len(targets) != 1 or None in targets:
                            directories.add(None)
                            break
                        target = next(iter(targets))
                        if not target.startswith("Code/"):
                            directories.add(None)
                            break
                        directories.add(PurePosixPath(target).parent.as_posix())
                    if len(directories) == 1 and None not in directories:
                        self._subsystems[source] = (directories.pop(), "approved-tu-directory")
        return self._subsystems.get(rel, (PurePosixPath(rel).parent.as_posix(), "source-directory"))

    def data_rows(self, rel):
        return [r for r in self.ctx.dicts(rename.DATA_ROWS) if r.get("source") == rel and r.get("status") == "matched"]

    def named_rvas(self):
        """RVAs another lane names: a WorldBuilder lead that spells a name (rename.wb_lead_names,
        the rule rename.py's inferred guard applies: a lead row with no wb_name names nothing),
        an evidence-tier name or a canonical name_evidence candidate (rename.py refuses an
        inferred name there)."""
        if "_named_rvas" not in self.ctx._cache:
            out = {rename._rva(r.get("rva") or r.get("target_rva")) for r in self.ctx.dicts(rename.WB_LEADS)
                   if rename.wb_lead_names(r)}
            out |= {rename._rva(r.get("target_rva")) for r in self.ctx.dicts(rename.NAME_TIERS)
                    if r.get("name_tier") == "evidence"}
            out |= {rename._rva(r.get("rva")) for r in self.evidence() if r.get("strength") == "canonical"}
            out.discard(None)
            self.ctx._cache["_named_rvas"] = out
        return self.ctx._cache["_named_rvas"]

    def pin_named(self, rva, old_name):
        """Use the engine's real-pin predicate, excluding the row's own symbol."""
        own = rename.mangled_re(old_name)
        if "_naming_pins" not in self.ctx._cache:
            pins = collections.defaultdict(list)
            for pin in self.ctx.pins():
                pins[rename._rva(pin.get("address"))].append(pin.get("name", ""))
            self.ctx._cache["_naming_pins"] = pins
        for name in self.ctx._cache["_naming_pins"].get(rva, ()):
            if name and not own.search(name):
                ident = rename.leading_fragment(name) or (rename.fragments_text(name) or [name])[0]
                if not rename.is_placeholder(ident, "function"):
                    return True
        return False

    def eligibility(self, rel, kind, scope, ident, rva):
        """Read-only protection preflight; the planner still rechecks at apply."""
        if kind in ("param", "local"):
            return None
        if unrowed_key(key_of(rel, kind, scope, ident)):
            row = request_for_key(self, key_of(rel, kind, scope, ident))
            try:
                if row is None:
                    return 'unknown unrowed data request'
                check_unrowed(self, row)
                if row.get('registrant') == self.worker():
                    return 'the registrant cannot vote on this unrowed key'
            except (rename.Refusal, ValueError) as exc:
                return str(exc)
            return None
        old = ident
        if kind == "function":
            old = next((r["name"] for r in self.ledger().get(rel, ())
                        if rename._rva(r.get("target_rva")) == rva), ident)
            # the guard below permits an evidence-tier row whose name equals the current spelling,
            # which a compiler-spelled key always does; the ordinary inventory excludes these first
            if compiler_spelled(ident):
                if rva in self.named_rvas() or self.pin_named(rva, old):
                    return f"0x{rva:08X} is named by another lane or a real pin"
                current = {r["name"] for r in self.ledger().get(rel, ()) if rename._rva(r.get("target_rva")) == rva}
                if current != {ident}:
                    return f"this key's spelling is no longer the row's at 0x{rva:08X}: its key is obsolete"
        try:
            rename.inferred_guards(self.ctx, kind, old, ident, rva)
        except rename.Refusal as exc:
            return str(exc)
        return None

    def evidence(self):
        if "_evidence" not in self.ctx._cache:
            raw = self.text(EVIDENCE_TSV) or ""
            self.ctx._cache["_evidence"] = list(csv.DictReader(io.StringIO(raw), delimiter="\t"))
        return self.ctx._cache["_evidence"]

    def strings(self):
        """rva -> retail strings it references (reverse/string_xrefs.tsv)."""
        if "_strings" not in self.ctx._cache:
            out = collections.defaultdict(list)
            for line in (self.text(rename.STRING_XREFS) or "").splitlines():
                if "\t" not in line:
                    continue
                text, refs = line.rsplit("\t", 1)
                for ref in refs.split(","):
                    rva = rename._rva(ref.strip())
                    if rva is not None:
                        out[rva].append(text)
            self.ctx._cache["_strings"] = out
        return self.ctx._cache["_strings"]

    def type_definers(self, word):
        """Files under Code/ and reference/shims/ that define `word` as a class or struct."""
        if word not in self._types:
            hits = self.git("grep", "-l", "-I", "-w", "-E", rf"(class|struct)[[:space:]]+{word}", "--",
                            *rename.SEARCH_ROOTS).split()
            self._types[word] = sorted(f for f in hits if not rename.is_generated(f)
                                       and word in name_metric.DECL.findall(name_metric.strip(self.text(f) or "")))
        return self._types[word]

    def header_type(self, word):
        """Some header (game or Zero Hour) declares `word`: a real class a stand-in may take."""
        if any(f.endswith(rename.HEADER_SUFFIXES) for f in self.type_definers(word)):
            return True
        headers = self.reference_matches(re.escape(word), rename.SEARCH_ROOTS,
                                         tuple(s.lstrip(".") for s in rename.HEADER_SUFFIXES),
                                         whole_word=True, filenames=True, tracked=True)
        if any(word in record_typedef_names(self.text(path) or "") for path in headers.split("\0") if path):
            return True
        zh = self.path(rename.BFME1) / rename.ZH_TREE
        if not zh.exists():
            return False
        roots = [f"{rename.BFME1}/{rename.ZH_TREE}"]
        if self.reference_matches(rf"(class|struct)[[:space:]]+{word}", roots, ("h",), whole_word=True):
            return True
        headers = self.reference_matches(re.escape(word), roots, ("h",), whole_word=True, filenames=True)
        return any(word in record_typedef_names(self.text(path) or "") for path in headers.split("\0") if path)

    def reference_matches(self, pattern, roots, extensions, *, ignore_case=False, whole_word=False,
                          filenames=False, tracked=False):
        """Read donor files through the Git dependency already used by the lane.

        --no-index includes untracked donor fixtures and submodule contents;
        tracked=True restricts local-header evidence to tracked files.
        explicit glob pathspecs keep extensions/roots identical on Windows and
        Unix. A failed search is not evidence that a donor name is absent.
        """
        paths = [f":(glob){root}/**/*.{extension}" for root in roots if self.path(root).is_dir()
                 for extension in extensions]
        if not paths:
            return ""
        args = ["git", "-C", str(self.root), "grep", "--no-recurse-submodules",
                "--no-color", "--no-line-number", "--no-column", "--no-heading", "--no-break", "-I", "-E"]
        if not tracked:
            args += ["--no-index", "--no-exclude-standard"]
        args += ["-l", "-z"] if filenames else ["-h", "-o"]
        if ignore_case:
            args.append("-i")
        if whole_word:
            args.append("-w")
        try:
            result = subprocess.run([*args, "-e", pattern, "--", *paths], capture_output=True, text=True,
                                    encoding="utf-8", errors="replace")
        except OSError as error:
            fail(f"reference search could not run Git: {error}")
        if result.returncode not in (0, 1):
            fail(f"reference search failed (git grep exit {result.returncode}): {result.stderr.strip()}")
        return result.stdout

    def donor_params(self, functions):
        """{function word: parameter words} as the donor trees (Open-BFME-1's
        game/ and its Zero Hour reference) spell them in declarations. A weak
        spelling the donor wrote itself -- WWMath's Dot_Product(const Vector3 &a,
        const Vector3 &b) -- is the original programmer's, not a converter's
        invention, so the lane does not ask for a new one."""
        todo = sorted(w for w in set(functions) - set(self._donor) if re.fullmatch(r"[A-Za-z_]\w*", w))
        roots = [f"{rename.BFME1}/{d}" for d in ("game", rename.ZH_TREE)]
        found = {w: set() for w in todo}
        for i in range(0, len(todo), 200):
            chunk = todo[i:i + 200]
            out = self.reference_matches(rf"\b({'|'.join(chunk)})[[:space:]]*\([^()]*\)",
                                         roots, ("h", "inl", "cpp"))
            for line in out.splitlines():
                m = re.match(r"(\w+)\s*\((.*)\)", line)
                if not m or m.group(1) not in found:
                    continue
                for piece in m.group(2).split(","):
                    words = re.findall(r"[A-Za-z_]\w*", piece.split("=")[0])
                    if len(words) >= 2:         # a type and a name: a declaration, not a call
                        found[m.group(1)].add(words[-1])
        # Publish positive and negative cache entries only after every batch
        # succeeded; a caught search error must not authorize a later rename.
        self._donor.update(found)
        return {w: self._donor.get(w, set()) for w in functions}

    # ------------------------------------------------------------ what a file decides

    def registered_placeholders(self):
        """{canonical header: {class}} for the placeholder classes reverse/canonical_classes.csv
        registers. Every unit's view of such a class is its own copy, so no unit alone decides
        its name; the canonical header is where the class and its members are served
        (`next --registered CLASS`), and tools/rename.py class renames key, contract and views."""
        if self._registered is None:
            out = collections.defaultdict(set)
            for row in self.ctx.dicts(rename.CANONICAL_CLASSES):
                cls, header = row.get("class") or "", row.get("header") or ""
                if (rename.IDENT.fullmatch(cls) and name_metric.placeholder(cls) and header.startswith("Code/")
                        and header.endswith(rename.HEADER_SUFFIXES) and self.text(header) is not None
                        and not rename.is_generated(header) and not rename.is_vendored_path(self.ctx, header)):
                    out[header].add(cls)
            self._registered = dict(out)
        return self._registered

    def registered_here(self, rel, cls):
        """`cls` is a registered placeholder class and `rel` its canonical header."""
        return cls in self.registered_placeholders().get(rel, ())

    def merges(self, rel, cls, new):
        """Renaming the registered placeholder `cls` (served from its header `rel`) to `new`
        is a `rename.py class --merge-existing`: the tree already spells `new`, but only as
        a type nothing owns (rename.merge_problems). Such an answer is voted and landed as a
        merge; any other answer the tree already spells is still refused."""
        if not self.registered_here(rel, cls) or not self.ctx.grep_files(new, word=True):
            return False
        if any(r.get("class") == new for r in self.ctx.dicts(rename.CANONICAL_CLASSES)):
            return False                    # two registered classes are a reconciliation, never a merge
        names = [r["name"] for r in self.ctx.rows()] + [p.get("name", "") for p in self.ctx.pins()] + \
            [d.get("name", "") for d in self.ctx.dicts(rename.DATA_ROWS)]
        return not rename.merge_problems(self.ctx, new, names)

    def servable(self, rel):
        """A matched or registered-unrowed Code/ unit with no vendor/export owner, or the
        canonical header of a registered placeholder class (its class and member keys only)."""
        if rel in self.registered_placeholders():
            return True
        rows = self.ledger().get(rel, [])
        if (not rows and not data_request_items(self, rel)) or not rel.startswith("Code/") or not rel.endswith((".cpp", ".c")):
            return False
        if rename.is_generated(rel) or "stlport" in rel.lower() or rename.is_vendored_path(self.ctx, rel):
            return False
        return not any("vendored=" in (r.get("notes") or "") or r.get("export_rva") for r in rows)

    def owned(self, rel, text=None, *, kinds=None):
        """[(kind, scope, ident, rva)] the file alone decides, in reading order.
        scope: a function's RVA (0x...), a member's class, a param's or
        local's function (name_metric.functions_in spelling, #N for overloads).
        Scoped-only requests skip type ownership searches; the scoped planners
        still check captures, headers and optimisation before any edit."""
        wanted = None if kinds is None else frozenset(kinds)
        if wanted == frozenset():
            return []
        text = self.text(rel) if text is None else text
        code = name_metric.strip(text)
        rows = self.ledger().get(rel, [])
        items = []
        registered = self.registered_placeholders().get(rel, set())
        if wanted is None or not wanted <= {"param", "local"}:
            decls = list(name_metric.DECL.finditer(code))
            for t in dict.fromkeys(m.group(1) for m in decls):
                if name_metric.placeholder(t) and (t in registered or self.type_definers(t) in ([], [rel])):
                    items.append(("class", "", t, None))
            holders = collections.defaultdict(set)
            macros = set(MACRO.findall(code))
            for m in decls:
                # a #define/#undef inside a class body is not a declaration (BFME_AI_SLOT(n) slot tables)
                body = DIRECTIVE.sub("", code[m.end():name_metric.close(code, m.end() - 1)])
                for name in name_metric.members(body):
                    if name not in macros:
                        holders[name].add(m.group(1))
            for name, classes in holders.items():
                # only a class this file alone defines: a member of a class with other views
                # (Object's 13 private copies) is renamed across all of them, not decided here;
                # a registered class's canonical header decides for all of its views, which use
                # the member where the header only declares it
                if len(classes) != 1 or not name_metric.placeholder(name) or name_metric.PAD.match(name):
                    continue
                cls = next(iter(classes))
                if cls in registered or (len(re.findall(rf"\b{re.escape(name)}\b", code)) > 1   # used, so not padding
                                         and self.type_definers(cls) in ([], [rel])):
                    items.append(("member", cls, name, None))
        if registered and not rows:
            # a canonical header owns no rows: it decides its registered classes and their members only
            return [i for i in items if (i[2] if i[0] == "class" else i[1]) in registered]
        scopes = collections.defaultdict(set)
        parsed = []
        for r in rows:
            name = r.get("name", "")
            if name.startswith(rename.FUNCLET_PREFIXES + ("$L",)) or "parent=" in (r.get("notes") or ""):
                continue
            try:
                _, word, _ = rename.split_function_name(name)
            except rename.Refusal:
                continue
            scope = rename.scope_of(name) or ""
            scopes[word].add(scope)
            parsed.append((word, rename._rva(r.get("target_rva")), name))
        named = self.named_rvas()
        seen_rvas = collections.Counter(rva for _, rva, _ in parsed)
        for word, rva, name in parsed:
            # one RVA per word in the file: a word shared by several scopes or rows is not this row's alone
            if (rva is not None and rva not in named and seen_rvas[rva] == 1 and len(scopes[word]) == 1
                    and sum(1 for w, _, _ in parsed if w == word) == 1 and name_metric.placeholder(word)
                    and not self.pin_named(rva, name)
                    and not FAMILY.fullmatch(word) and re.search(rf"\b{re.escape(word)}\b", code)):
                items.append(("function", f"0x{rva:08X}", word, rva))
        optimised = None
        spans = list(name_metric.functions_in(code))
        # weak but not placeholder (a, b, tmp): the donor's own spelling stays
        donor = self.donor_params({base(scope) for scope, _, _, params in spans
                                   if any(name_metric.weak("param", n) and not name_metric.placeholder(n)
                                          for n in rename.parameters(params))})
        for scope, start, end, params in spans:
            items += [("param", scope, n, None) for n in rename.parameters(params) if name_metric.weak("param", n)
                      and (name_metric.placeholder(n) or n not in donor.get(base(scope), ()))]
            if optimised is None:
                optimised = rename.optimized(rename.compile_flags(self.ctx, rel)) and not re.search(
                    r'^[ \t]*#[ \t]*pragma[ \t]+optimize[ \t]*\([^)]*\boff\b', text, re.M)
            if optimised:       # /Od orders frame slots by identifier text: renaming a local moves bytes
                body = code[code.find("{", start):end]
                items += [("local", scope, n, None) for n in name_metric.local_names(body)
                          if name_metric.weak("local", n)]
        file_globals = set(name_metric.global_names(code))
        for r in self.data_rows(rel):
            word = rename._identifier(r.get("name", ""))
            if word and word in file_globals and name_metric.placeholder(word):
                items.append(("global", "", word, rename.data_rva(r)))
        items.extend(data_request_items(self, rel))
        seen, out = set(), []
        for kind, scope, ident, rva in items:
            slot = (scope, ident) if kind in ("param", "local") or scope.startswith("unrowed:") else ident
            if slot not in seen:
                seen.add(slot)
                if wanted is None or kind in wanted:
                    out.append((kind, scope, ident, rva))
        return out

    # ------------------------------------------------------------ refusals

    def collision_scope(self, rel, kind, scope, old):
        if kind == "member":
            return scope
        if kind == "function":
            row = next((r for r in self.ledger().get(rel, ())
                        if rename._rva(r.get("target_rva")) == rename._rva(scope)), None)
            function = rename.scope_of(row["name"]) if row else None
            return function.rsplit("::", 1)[0] if function and "::" in function else None
        return None

    def collision_words(self, rel, kind, scope, old, text=None):
        """Conservative words visible in this class, including method bodies.

        Other classes may reuse member names. Same-class uses, globals, macros
        and uncertain class scopes still block; apply performs capture checks.
        """
        code = name_metric.strip(self.text(rel) if text is None else text)
        owner = self.collision_scope(rel, kind, scope, old)
        bodies = rename.class_bodies(code, owner) if owner else []
        if not bodies:
            return set(name_metric.WORD.findall(code))
        words = set(name_metric.global_names(code)) | set(MACRO.findall(code))
        for directive in DIRECTIVE.findall(code):
            words.update(name_metric.WORD.findall(directive))
        for start, end in bodies:
            words.update(name_metric.WORD.findall(code[start:end]))
        for function, start, end, _params in name_metric.functions_in(code):
            if function.split("#")[0].rsplit("::", 1)[0] == owner:
                words.update(name_metric.WORD.findall(code[start:end]))
        return words

    def problem(self, kind, old, new, file_words, *, rel=None, scope="", text=None):
        """Why `new` may not be voted for `old`, or None (BFME 1's problem())."""
        if kind == "function" and compiler_spelled(old):
            return spelled_problem(old, new)
        if not re.fullmatch(r"[A-Za-z_]\w*", new or "") or new in name_metric.KEYWORDS:
            return "not a C++ identifier"
        if new == old or name_metric.weak(kind if kind in ("param", "local") else "function", new):
            return "still a placeholder"
        if canon(new).replace(" ", "") in GENERIC:
            return "too generic to help a reader"
        if kind == "class" and not new[0].isupper():
            return "types are CamelCase"
        if kind == "member" and not re.fullmatch(r"m_[a-z]\w*", new):
            return "members are m_camelCase"
        if kind in ("param", "local") and not new[0].islower():
            return "params and locals are camelCase"
        if kind == "class" and self.type_definers(new) and not self.header_type(new):
            return f"{new} is another file's stand-in, not a class any header declares"
        if rel is not None and kind in ("member", "function"):
            file_words = self.collision_words(rel, kind, scope, old, text)
        # A prepared respell runs no identifier rewrite. Its final declarations
        # and consumers go through rename.py together, so another scope already
        # spelling this word is not a textual-rename collision. Do not expose
        # the manifest's proposed spelling to the independent voter.
        prepared = (kind == "function" and rel is not None and
                    key_of(rel, kind, scope, old) in respell_bindings(self)[1])
        if kind in NAMED and new in file_words and not prepared:
            return "collides with a name already in the file"
        return None


def base(scope):
    """The function word of a param's or local's scope (Class::method#2 -> method)."""
    return scope.split("#")[0].split("::")[-1]


SPELLED_PLACEHOLDER = re.compile(r"Rva[0-9A-Fa-f]{8}\w*")
SPELLED_HEAD = re.compile(r"\?\?_?.|\?[A-Za-z_]\w*")


def compiler_spelled(name):
    """Whether a row's mangled name has no identifier of its own to respell (an operator or
    special member, or a template's member) and spells a placeholder type."""
    if not name.startswith("?") or not SPELLED_PLACEHOLDER.search(name):
        return False
    try:
        rename.split_function_name(name)
    except rename.Refusal:
        return True
    return "?$" in name


def scope_rva(key):
    return key.split("|")[2]


def spelled_key(key):
    parts = key.split("|")
    return len(parts) == 4 and parts[1] == "function" and compiler_spelled(parts[3])


def spelled_items(lane, rel):
    """[(kind, scope, ident, rva)] of `rel`'s compiler-spelled rows, one row to an address. The
    key's placeholder is the row's whole old spelling (rename.py's --identity approval key)."""
    rows = lane.ledger().get(rel, [])
    seen = collections.Counter(rename._rva(r.get("target_rva")) for r in rows)
    named = lane.named_rvas()
    return [("function", f"0x{rva:08X}", r["name"], rva) for r in rows
            for rva in [rename._rva(r.get("target_rva"))]
            if rva is not None and seen[rva] == 1 and compiler_spelled(r["name"])
            and rva not in named and not lane.pin_named(rva, r["name"])
            and not r["name"].startswith(rename.FUNCLET_PREFIXES + ("$L",)) and "parent=" not in (r.get("notes") or "")]


def spelled_problem(old, new):
    """Why `new` cannot answer a compiler-spelled row's key `old`, or None. rename.py's identity
    route decides the shape; here it must read as a respelling of this row and lose a placeholder."""
    if not re.fullmatch(r"\?[!-{}~]+", new or ""):
        return "a compiler-spelled row is answered with its whole new mangled spelling"
    if new == old:
        return "still the same spelling"
    head = SPELLED_HEAD.match(old)
    if head is None or not new.startswith(head.group(0)):
        return "it must stay the same operator or member"
    if set(SPELLED_PLACEHOLDER.findall(new)) >= set(SPELLED_PLACEHOLDER.findall(old)):
        return "still a placeholder"
    return None


def key_of(rel, kind, scope, ident):
    return f"{rel}|{kind}|{scope}|{ident}"


def split_key(key):
    rel, kind, scope, ident = key.split("|")
    return rel, kind, scope, ident


def needs_review(key, state, tally, refused):
    """Reopen a pending scoped approval when a late rival removes its quorum."""
    row = state.get(key)
    if row is None or row["status"] in REOPENED:
        return True
    if row["status"] != "agreed" or split_key(key)[1] not in ("param", "local"):
        return False
    mine, rivals, _ = approval_support(tally, refused, row)
    return not wins(mine, rivals, key=key)


def served_answers(rel, items, mapping):
    """An answer file's `mapping` keyed by served key. A full key names its one item; a bare key
    the one item it spells, and it refuses as ambiguous when two served items share it (a
    compiler-spelled name can stand at two addresses). Keys naming nothing stay, to be refused."""
    bare = collections.defaultdict(list)
    for kind, scope, ident, *_rest in items:
        bare[answer_key(kind, scope, ident)].append(key_of(rel, kind, scope, ident))
    served = {key for keys in bare.values() for key in keys}
    out = {}
    for given, value in mapping.items():
        keys = [given] if given in served else bare.get(given, [given])
        if len(keys) > 1:
            fail(f"{given} is ambiguous in {rel}: answer one of {', '.join(keys)}")
        if keys[0] in out and out[keys[0]] != value:
            fail(f"{keys[0]} has two answers")
        out[keys[0]] = value
    return out


def answer_key(kind, scope, ident):
    if kind in ("param", "local"):
        return f"{scope}:{ident}"
    if kind == "member":
        return f"{scope}::{ident}"
    return scope + ':' + ident if kind == 'global' and scope.startswith('unrowed:') else ident


# ---------------------------------------------------------------- next

def second_reviews(worker, state, tally, refused):
    """Shared keys with one voter that this worker can independently review."""
    out = collections.defaultdict(set)
    for key, proposals in tally.items():
        parts = key.split("|")
        if len(parts) != 4 or parts[1] in ("param", "local"):
            continue
        voters = {w for v in proposals.values() for w in v}
        if len(voters) == 1 and worker not in voters and needs_review(key, state, tally, refused):
            out[parts[0]].add(key)
    return out


def meaning_reviews(worker, state, tally, refused):
    """Let an original scoped voter clarify its existing, unannotated vote."""
    out = collections.defaultdict(set)
    for key, proposals in tally.items():
        if not name_agreement.scoped_key(key) or not needs_review(key, state, tally, refused):
            continue
        banned = refuted(key, (c for c in refused.get(key, ()) if not c.startswith("~meaning:")))
        active = {h: v for h, v in proposals.items() if h not in banned}
        own = [h for h, v in active.items() if worker in v]
        annotations = getattr(tally, "meanings", {}).get(key, {})
        roles = {role for values in annotations.values() for role in values}
        if (len(own) == 1 and not annotations.get((own[0], worker))
                and (len(active) > 1 or len(roles) > 1)):
            out[key.split("|")[0]].add(key)
    return out


def queue(lane, worker, model, only=None, *, reviews=None, clarifications=None):
    """Prioritize shared keys needing an independent second worker, then the
    former other-model/other-worker queue. A worker may revisit a file for an
    unvoted shared key; cmd_next never serves a key that worker already voted."""
    voted_sessions, voted_models = collections.defaultdict(set), collections.defaultdict(set)
    for v in lane.votes():
        if len(parts := v["key"].split("|")) == 4 and parts[1] in SCOPED_KINDS:
            continue
        rel = v["key"].split("|")[0]
        voted_sessions[rel].add(v.get("worker") or "")
        voted_models[rel].add(v["model"])
    files = [only] if only else sorted({f for f in lane.ledger() if f.endswith((".cpp", ".c"))}
                                     | {r['source'] for r in lane.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS)})
    reviews = reviews or {}
    clarifications = clarifications or {}
    state, tally, refused = lane.state(), lane.tally(), lane.disputed()
    pending_data = {r['source'] for r in lane.table(DATA_REQUESTS, DATA_REQUEST_COLUMNS)
                    if r.get('registrant') != worker and needs_review(data_request_key(r), state, tally, refused)
                    and worker not in {w for voters in tally[data_request_key(r)].values() for w in voters}}
    files = [f for f in files if worker not in voted_sessions[f] or reviews.get(f) or clarifications.get(f)
             or f in pending_data]
    random.shuffle(files)
    files.sort(key=lambda f: (not reviews.get(f), not clarifications.get(f),
                              not (voted_models[f] - {model}), not voted_sessions[f]))
    return files, voted_sessions


def subsystem_prefix(value):
    value = (value or "").replace("\\", "/").rstrip("/")
    parts = value.split("/")
    if not value or parts[0] != "Code" or any(p in ("", ".", "..") for p in parts):
        fail("--subsystem must be a directory prefix under Code/ without . or .. components")
    return value


def under(path, prefix):
    return path == prefix or path.startswith(prefix + "/")


def subsystem_brief(lane, served, group):
    """Shared context consists of existing source, never another seat's votes."""
    lines = [f"SUBSYSTEM CONTEXT: {group}",
             "Read these related files together before choosing names. Reuse existing",
             "terminology when the roles match; do not equate private class views or",
             "infer a layout merely because files share this scheduling group.",
             "This packet supplies context, not canonical naming or TU evidence.",
             "Existing source vocabulary (no unlanded proposals or vote answers):"]
    context = [(rel, text, "naming target") for rel, text, _items in served]
    selected = {rel for rel, _text, _items in served}
    for rel in sorted(lane.ledger()):
        if len(context) >= len(served) + 3:
            break
        if rel in selected or lane.subsystem(rel)[0] != group or not lane.servable(rel):
            continue
        text = lane.text(rel)
        if text is not None and len(text) <= MAX_CHARS:
            context.append((rel, text, "read-only related source"))
    for rel, text, role in context:
        code = name_metric.strip(text)
        scopes = [s for s, *_ in name_metric.functions_in(code) if not name_metric.placeholder(s)]
        types = [n for n in re.findall(r"\b(?:class|struct)\s+([A-Za-z_]\w*)", code)
                 if not name_metric.placeholder(n)]
        group_path, basis = lane.subsystem(rel)
        words = ", ".join(dict.fromkeys(types + scopes))[:400] or "no established type/function names"
        lines.append(f"  {rel} [{role}; {basis}: {group_path}]: {words}")
    if getattr(lane, "subsystem_map_stale", []):
        lines.append("TU map is missing/stale; source-directory groups do not assert original TU ownership.")
    return "\n".join(lines)


def callers(lane, rel, word, limit=6):
    lines = []
    for f in lane.git("grep", "-l", "-I", "-w", "-F", "-e", word, "--", "Code").split():
        if f == rel or rename.is_generated(f):
            continue
        hit = next((l.strip() for l in (lane.text(f) or "").splitlines() if re.search(rf"\b{word}\b", l)), "")
        lines.append(f"  {f}: {hit[:110]}")
        if len(lines) == limit:
            break
    return lines


def registered_brief(lane, cls):
    """Context for a registered class's keys: its contract's fields and where its private
    views live. The names those views spell, and the contract's majority among them, are
    other agents' choices: a hint for this vote, never its evidence."""
    lines = [f"## Registered class {cls}",
             f"{cls} has a canonical header ({rename.CANONICAL_CLASSES}) and private views in other units; "
             "the name voted here replaces it in the header, every view, its contract and the ledger "
             "(tools/rename.py class / member). Inspect the views: python3 tools/class_views.py --class " + cls]
    try:
        contract = json.loads(lane.text(f"{rename.CLASS_CONTRACTS}/{cls}.json") or "{}")
    except ValueError:
        contract = {}
    fields = [f for f in contract.get("fields", []) if isinstance(f, dict)]
    if fields:
        lines.append("Contract fields (offset, name the views' majority spells, type, decided by):")
        lines += [f"  +0x{int(f.get('offset', 0)):X} {f.get('name')} {f.get('type')} ({f.get('name_by') or '?'}, "
                  f"{f.get('views') or 0} view(s))" for f in fields]
    return "\n".join(lines)


CALLEE_DEPTH, CALLEE_FUNCTIONS = 6, 40
STL_MEMBER = re.compile(r"\?(_M_[a-z_]+)@\?\$\w+@.*@_STL@@")
STL_FUNCTION = re.compile(r"\?\?\$(_Construct|_Destroy|__uninitialized_[a-z_]+)@")
TYPE_TOKEN = re.compile(r"[A-Za-z_]\w{3,}")
ENDS_FLOW = ("ret", "retn", "retf", "int3", "hlt", "iret")


def reachable_instructions(decoder, code, at):
    """(the instructions control can reach from `at`, in address order; why decoding stopped, if
    it did). Bytes after a return or an unconditional jump are not code until a branch says so."""
    seen, work, stops = {}, [0], []
    while work:
        offset = work.pop()
        while offset not in seen:
            if not 0 <= offset < len(code):
                break
            instruction = next(iter(decoder.disasm(code[offset:offset + 16], at + offset, count=1)), None)
            if instruction is None:
                stops.append(f"0x{at + offset:08X}: bytes that do not decode")
                break
            seen[offset] = instruction
            if instruction.mnemonic in ENDS_FLOW:
                break
            if instruction.mnemonic.startswith(("j", "loop")):
                direct = re.fullmatch(r"0x[0-9a-f]+", instruction.op_str)
                if not direct:
                    stops.append(f"0x{at + offset:08X}: an indirect jump, {instruction.op_str}")
                    break
                target = int(instruction.op_str, 16) - at
                if 0 <= target < len(code):
                    work.append(target)
                if instruction.mnemonic == "jmp":
                    break
            offset += instruction.size
    return [seen[offset] for offset in sorted(seen)], stops


def callee_names(lane, under_vote):
    """{rva: [ledger names]} and the function saying what a voter may read of one name. A ledger
    name can be an earlier vote's inference, so a name is shown whole only when an independent
    record establishes it (reverse/name_tiers.csv's evidence tier) and no vote's record names it,
    and never when it shares a type with the spelling under vote. An STL template member keeps its
    fixed member name without its types. Anything else is an address: when unsure, withhold."""
    by_rva = collections.defaultdict(set)
    for row in lane.ctx.rows():
        at = rename._rva(row.get("target_rva"))
        if at is not None:
            by_rva[at].add(row.get("name", ""))
    for pin in lane.ctx.pins():
        at = rename._rva(pin.get("address"))
        if at is not None:
            by_rva[at].add(pin.get("name", ""))
    voted = {r.get("new") for r in lane.ctx.dicts(rename.NAME_BASIS)
             if (r.get("basis") or "").startswith("inferred") or r.get("kind") == "class"}
    voted_words = {r.get("new") for r in lane.ctx.dicts(rename.NAME_BASIS) if r.get("kind") == "class"}
    evidence = {(r.get("name"), rename._rva(r.get("target_rva"))) for r in lane.ctx.dicts(rename.NAME_TIERS)
                if r.get("name_tier") == "evidence"}

    def shown(name, rva):
        # substrings, because a mangled type carries a prefix (URva00401000Box): a false hit only withholds
        if name in voted or any(word and word in name for word in voted_words):
            return None
        if (name, rva) in evidence and not any(token in under_vote for token in TYPE_TOKEN.findall(name)):
            return name
        for pattern in (STL_MEMBER, STL_FUNCTION):
            match = pattern.match(name)
            if match:
                return f"{match.group(1)} (a template member; its types withheld)"
        return None
    return by_rva, shown


def retail_callee_lines(lane, rva, under_vote=""):
    """What control flow reaches in retail's own bytes from a row, for a voter whose file only
    names a placeholder: each direct call and jump, down the call tree, with the constants and
    memory moves a container's shape shows in. Names follow callee_names, so an address is all a
    voter sees of most callees. What cannot be read or was not followed says so."""
    try:
        import capstone
        sys.path.insert(0, str(lane.root / "tools"))
        import build
    except ImportError as error:
        return [f"  (retail's callees cannot be listed here: {error})"]
    by_rva, shown = callee_names(lane, under_vote)
    sizes = {}
    for row in lane.ctx.rows():
        at = rename._rva(row.get("target_rva"))
        if at is not None:
            sizes[at] = max(sizes.get(at, 0), int(row.get("target_size") or 0))
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def named(target, start):
        if target == start:
            return "(this row)"
        names = sorted(by_rva.get(target, ()))
        if not names:
            return "(no row)"
        visible = sorted({each for each in (shown(name, target) for name in names) if each})
        withheld = len(names) - sum(1 for name in names if shown(name, target))
        if not visible:
            label = "(name withheld)"
        else:
            label = " and ".join(visible)
        if len(names) > 1:
            label += f" ({len(names)} rows name this address" + (f", {withheld} withheld)" if withheld else ")")
        return label
    lines, seen, frontier, expanded, deep = [], {rva}, [(rva, 0)], 0, 0
    while frontier and expanded < CALLEE_FUNCTIONS:
        at, depth = frontier.pop(0)
        indent = "  " * (depth + 1)
        size = sizes.get(at, 0)
        if not size:
            continue
        expanded += 1
        try:
            code = bytes(build.read_target_bytes(at, size))
        except (Exception, SystemExit) as error:     # no retail image here: say so, and list nothing
            lines.append(f"{indent}0x{at:08X}: retail's bytes cannot be read: {error}")
            continue
        instructions, stops = reachable_instructions(decoder, code, at)
        facts = []
        for instruction in instructions:
            mnemonic, operands = instruction.mnemonic, instruction.op_str
            direct = re.fullmatch(r"0x[0-9a-f]+", operands)
            if (mnemonic == "call" or mnemonic.startswith("j")) and direct:
                target = int(operands, 16)
                if mnemonic != "call" and at <= target < at + size:
                    continue                         # a jump inside the body is no callee
                facts.append(f"{'calls' if mnemonic == 'call' else mnemonic + 's'} 0x{target:08X} {named(target, rva)}")
                if target not in seen and target in sizes:
                    if depth + 1 < CALLEE_DEPTH:
                        seen.add(target)
                        frontier.append((target, depth + 1))
                    else:
                        seen.add(target)
                        deep += 1
            elif mnemonic == "call":
                facts.append(f"calls indirectly: {operands}")
            elif mnemonic == "push" and re.fullmatch(r"(0x[0-9a-f]+|\d+)", operands):
                facts.append(f"pushes {operands}")
            elif mnemonic in ("add", "sub") and re.fullmatch(r"e(?:[a-d]x|[sd]i|bp), (0x[0-9a-f]+|\d+)", operands):
                facts.append(f"{mnemonic}s {operands}")
            elif mnemonic == "lea" and "ebp" not in operands.split(",", 1)[-1]:
                facts.append(f"lea {operands}")
            elif mnemonic.startswith(("mov", "rep")) and ("[e" in operands or mnemonic.startswith("rep")) \
                    and "ebp" not in operands and "esp" not in operands:
                facts.append(f"{mnemonic} {operands}".rstrip())
        lines.append(f"{indent}0x{at:08X}" + ("" if at == rva else f" {named(at, rva)}"))
        lines += [f"{indent}  {fact}" for fact in facts]
        lines += [f"{indent}  decoding stops at {stop}" for stop in stops]
    if deep:
        lines.append(f"  ({deep} callee(s) below depth {CALLEE_DEPTH} not expanded)")
    waiting = sum(1 for at, _depth in frontier if sizes.get(at))
    if waiting:
        lines.append(f"  (stopped after expanding {expanded} function(s); {waiting} more found and not expanded)")
    return lines


def brief_text(lane, rel, text, items, session, model, *, review=False, meaning_review=False):
    rows = lane.ledger().get(rel, [])
    lines = text.splitlines()

    code = name_metric.strip(text)
    spans = {scope: text[start:end].splitlines() for scope, start, end, _ in name_metric.functions_in(code)}

    def declared_at(ident, scope=None):
        uses = [l.strip() for l in spans.get(scope, lines) if re.search(rf"\b{re.escape(ident)}\b", l)]
        decl = re.compile(rf"(?:class|struct)\s+{re.escape(ident)}\b|[\w>*&]\s*[*&]?\s*\b{re.escape(ident)}\s*"
                          r"(?:\[[^\]]*\]\s*)*[;,=)(]")
        return next((l for l in uses if decl.search(l)), uses[0] if uses else "")[:90]

    items = [item for item in items if item[0] in NAMED]
    spelled = collections.Counter(answer_key(k, s, i) for k, s, i, _ in items)
    listing = "\n".join(f"  {answer_key(k, s, i) if spelled[answer_key(k, s, i)] == 1 else key_of(rel, k, s, i):44} "
                        f"{k:8} {declared_at(i)}" for k, s, i, _ in items)
    evidence = []
    for kind, scope, ident, rva in items:
        request = request_for_key(lane, key_of(rel, kind, scope, ident)) if scope.startswith('unrowed:') else None
        if request:
            blind = request_packet(lane, key_of(rel, kind, scope, ident))
            evidence.append('UNROWED DATA REQUEST (caller facts, not a proposed name): ' +
                            json.dumps({k: v for k, v in blind.items() if k != 'user_sources'}, sort_keys=True))
            for user in json.loads(request['users']):
                evidence.append('USER ' + user + ':\n' + blind['user_sources'][user])
    if any(compiler_spelled(ident) for kind, _s, ident, _r in items if kind == "function"):
        evidence.append("COMPILER-SPELLED ROWS: a key starting with ? is the row's whole mangled spelling. Answer "
                        "its whole new mangled spelling, the same operator or member with the placeholder type "
                        "replaced by the one the row's retail callees prove; \"skip\" when they do not.")
        evidence.append("The old spelling's container shape is itself unproven: `map<X,int>` and `set<X>` can hold "
                        "the same element type, and two voters must answer byte for byte. Check `_M_create_node`'s "
                        "allocation against the element's size (a node is a 0x10 header plus the element) and the "
                        "element copy's calls and stride. Allocation alone does not settle it: two shapes can "
                        "allocate the same size and differ only in what the element copy does.")
        for kind, _scope, ident, rva in items:
            if kind == "function" and compiler_spelled(ident) and rva is not None:
                evidence.append(f"RETAIL CALLEES of {ident} at 0x{rva:08X}, by control flow from retail's bytes. A "
                                "name appears only where independently established; the rest are addresses. Only "
                                "calls, jumps, pushes, add/sub/lea and memory moves are listed. A constant missing "
                                "here proves nothing:")
                evidence += retail_callee_lines(lane, rva, ident)
    for kind, scope, ident, rva in items:
        if kind == "function":
            found = callers(lane, rel, ident)
            if found:
                evidence.append(f"callers spelling {ident}:")
                evidence += found
    rvas = {rename._rva(r.get("target_rva")) for r in rows}
    for rva in sorted(r for r in rvas if r is not None):
        for s in lane.strings().get(rva, [])[:6]:
            evidence.append(f"  0x{rva:08X} references string {json.dumps(s[:100])}")
    hints = [e for e in lane.evidence() if rename._rva(e.get("rva")) in rvas]
    for e in hints[:10]:
        evidence.append(f"  hint 0x{rename._rva(e['rva']):08X} {e.get('current')} ~ {e.get('candidate')} "
                        f"({e.get('evidence_kind')}, {e.get('strength')}): {(e.get('detail') or '')[:140]}")
    text = packet_source(lane, rel, items)["source"]
    return f"""NAME THE PLACEHOLDERS IN {rel}  (session {session}, model {model})
{"INDEPENDENT SECOND REVIEW: only the shared identifiers awaiting another worker are served; previous proposals remain hidden." if review else ""}

This is decompiled BFME 2 (SAGE engine) C++. A converter invented the names
below from addresses, offsets or decompiler slots. Give each the name its
original EA programmer most likely used, judging from what the code does and
the evidence. Style (fixed): types CamelCase, members m_camelCase,
functions and methods camelCase unless the class already
uses CamelCase. Answer "skip" when you cannot justify a name: a skip costs
nothing, a wrong name misleads readers. These shared names need independent
blind agreement. Your proposal must be your own: do not take
names from, or show yours to, another model or session.
Write your answer with a file-writing tool, never inline in a shell command
(other sessions can read command lines). If a stand-in type IS a real class
that a game or Zero Hour header declares, answer that class's name.

Write a JSON object mapping each key below to a name or "skip", spelled as listed
(a key's full form, as `next --key` takes it, is read as the same key), then check it
before recording votes:
  python3 tools/name_lane.py validate ANSWER.json --session {session} --model {model}
Revise only rejected answers once using the reported reasons and declarations;
use "skip" if still uncertain. Validation records no votes. Then run:
  python3 tools/name_lane.py submit <that file> --session {session} --model {model}

For a function, class, member or global, a structured answer may give the
identifier's role as a short factual sentence, e.g.
{{"name":"writeFieldNamePrefix","role":"Writes the field name and '=' before its value."}}.
The role helps a later reviewer distinguish a wording difference from a
different interpretation. It is context, not proof of a canonical name.

Do not vote on locals or parameters in this packet. {scoped_route(session, model, [rel])}
Existing scoped votes remain historical evidence; already approved names can
still land through apply. Unfinished scoped tasks need fresh scoped review.

{listing}

--- {rel}
{text}
--- evidence (callers, retail strings, tools/name_evidence.py hints)
""" + ("\n".join(evidence) or "  (none)") + "\n"


class PickerCache:
    """Cache expensive ownership discovery, never votes, claims or apply checks."""
    def __init__(self, lane):
        self.lane = lane
        self.path = lane.path(f"{LANE_DIR}/picker-cache.json")
        self.stamp = self.snapshot()
        self.hits = self.misses = 0
        try:
            saved = json.loads(self.path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            saved = {}
        self.entries = saved.get("entries", {}) if isinstance(saved, dict) and self.stamp and saved.get("stamp") == self.stamp else {}
        if not isinstance(self.entries, dict):
            self.entries = {}
        self.updates = {}

    def snapshot(self):
        return _input_fingerprint(self.lane, (), "picker-cache-v1",
                                  exclude=(VOTES, MEANINGS, RESOLUTIONS),
                                  scope_paths=("Code", "reference", "tools", "reverse", "build.sh", ".gitmodules"),
                                  nested_scope=("game", rename.ZH_TREE))

    def items(self, rel, text):
        sha = hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest()
        row = self.entries.get(rel, {})
        if (isinstance(row, dict) and row.get("sha") == sha and isinstance(row.get("items"), list)
                and all(isinstance(item, list) and len(item) == 4 and item[0] in KINDS
                        and all(isinstance(value, str) for value in item[:3])
                        for item in row["items"])):
            self.hits += 1
            return [tuple(item) for item in row["items"] if item[0] in NAMED]
        self.misses += 1
        items = [item for item in self.lane.owned(rel, text, kinds=NAMED) if item[0] in NAMED]
        if self.stamp:
            self.updates[rel] = dict(sha=sha, items=items)
        return items

    def save(self):
        if not self.updates or not self.stamp or self.snapshot() != self.stamp:
            return
        from portable_lock import lock, unlock
        self.path.parent.mkdir(parents=True, exist_ok=True)
        with self.path.with_suffix(".lock").open("a") as handle:
            lock(handle, exclusive=True)
            try:
                try:
                    saved = json.loads(self.path.read_text(encoding="utf-8"))
                except (OSError, ValueError):
                    saved = {}
                entries = saved.get("entries", {}) if isinstance(saved, dict) and saved.get("stamp") == self.stamp else {}
                if not isinstance(entries, dict):
                    entries = {}
                entries.update(self.updates)
                temporary = self.path.with_suffix(f".{os.getpid()}.tmp")
                temporary.write_text(json.dumps(dict(stamp=self.stamp, entries=entries)), encoding="utf-8")
                os.replace(temporary, self.path)
            finally:
                unlock(handle)


@claims.pick_snapshot()
def cmd_next(lane, args, *, _claim_snapshot=None):
    timing_start = time.perf_counter()
    registered = getattr(args, "registered", None)
    if registered:
        if getattr(args, "file", None) or getattr(args, "files", None):
            fail("--registered serves the class's canonical header; it takes no --file or --files")
        header = next((h for h, classes in lane.registered_placeholders().items() if registered in classes), None)
        if header is None:
            fail(f"{registered} is not a placeholder class registered in {rename.CANONICAL_CLASSES} "
                 "with a tracked canonical header")
        args.file = header
    requested_files = list(getattr(args, "files", None) or ())
    if requested_files and getattr(args, "file", None):
        fail("--file and --files cannot be combined")
    if len(requested_files) != len(set(requested_files)) or any(
            not rel.startswith("Code/") or "\\" in rel
            or any(part in ("", ".", "..") for part in rel.split("/"))
            for rel in requested_files):
        fail("--files requires distinct Code/ source paths")
    selected_keys = set(getattr(args, "key", None) or ())
    if getattr(args, "meaning_review_only", False) or any(
            len(parts := key.split("|")) == 4 and parts[1] in SCOPED_KINDS for key in selected_keys):
        fail(scoped_route(args.session, args.model,
                          [key.split("|")[0] for key in selected_keys] or requested_files
                          or ([args.file] if getattr(args, "file", None) else [])))
    max_keys = getattr(args, "max_keys", None)
    if max_keys is not None and max_keys < 1:
        fail("--max-keys must be positive")
    max_chars = getattr(args, "max_chars", None)
    if max_chars is not None and max_chars < 1:
        fail("--max-chars must be positive")
    # A source longer than MAX_CHARS is servable only through a registered data
    # request, so every key in a long unit is otherwise unreachable for voting.
    # An explicit --max-chars raises that bar, never lowers it: a smaller value
    # still only trims the packet below, so no file that was servable before
    # becomes ineligible now.
    source_limit = max(MAX_CHARS, max_chars) if max_chars is not None else MAX_CHARS
    session, model = session_id(args.session), model_id(args.model)
    worker = lane.worker()
    state = lane.state()
    tally, refused = lane.tally(), lane.disputed()
    reviews = second_reviews(worker, state, tally, refused)
    clarifications = {}  # Unfinished scoped votes now need fresh scoped review.
    files, voted = queue(lane, worker, model, args.file, reviews=reviews, clarifications=clarifications)
    if requested_files:
        eligible = set(files)
        files = [rel for rel in requested_files if rel in eligible]
        if not getattr(args, "mixed", False) and len({lane.subsystem(rel)[0] for rel in files}) > 1:
            fail("--files must belong to one subsystem; use --mixed for unrelated files")
    queue_done = time.perf_counter()
    only_meaning = getattr(args, "meaning_review_only", False)
    if only_meaning and getattr(args, "review_only", False):
        fail("--review-only and --meaning-review-only cannot be combined")
    served, metadata = [], []
    record = lane.path(f"{LANE_DIR}/sessions/{session}.json")
    current = json.loads(record.read_text()) if record.exists() else {"model": model, "worker": worker, "files": {}}
    if current.get("worker") != worker and not args.list_only:
        fail(f"session {session} belongs to another worker; pick a session label of your own")
    if any(item[0] in SCOPED_KINDS for entry in current["files"].values() for item in entry["items"]):
        fail("This saved session contains retired scoped voting tasks. "
             + scoped_route(session, model, current["files"]))
    if not args.list_only:
        print("name_lane: shared-name voting only. " + scoped_route(session, model), file=sys.stderr)
    mixed = getattr(args, "mixed", False)
    prefix = subsystem_prefix(args.subsystem) if getattr(args, "subsystem", None) else None
    if mixed and prefix:
        fail("--mixed and --subsystem cannot be combined")
    # One shared snapshot for the whole pick. The standard footprint expands
    # RVA/class claims and persisted locks to files, excluding our own claims
    # but retaining foreign namespaces and mirrors. Do this before choosing a
    # subsystem or scanning bodies so busy files cannot anchor/waste a batch.
    # Independent reviewers keep their own voting identity, while the operator
    # delegates read access to its claimed sources. Only the internal reviewer
    # passes its caller's already-expanded snapshot; this grants no write claim.
    busy = claims.busy_keys(lane.root) if _claim_snapshot is None else _claim_snapshot
    claims_done = time.perf_counter()
    available = [rel for rel in files if claims.file_key(rel) not in busy]
    skipped = len(files) - len(available)
    if skipped:
        held = [rel for rel in files if claims.file_key(rel) in busy]
        print(f"name_lane: skipped {skipped} source file(s) held by other workers: " +
              ', '.join(held[:3]) + (f' (+{skipped - 3} more)' if skipped > 3 else ''), file=sys.stderr)
    files = [rel for rel in available if not selected_keys or any(k.startswith(rel + "|") for k in selected_keys)]
    sticky = lane.path(f"{LANE_DIR}/subsystems/{worker}.json")
    preferred = current.get("subsystem")
    if not mixed and not prefix and not args.file and not requested_files:
        if not preferred and sticky.exists():
            preferred = subsystem_prefix(json.loads(sticky.read_text())["subsystem"])
        if preferred:
            files.sort(key=lambda f: (not reviews.get(f), not clarifications.get(f),
                                      lane.subsystem(f)[0] != preferred))
    selected = None
    selected_review = None
    selected_meaning = None
    cache = PickerCache(lane)
    packet_targets, packet_sources = [], []
    if max_chars is not None:
        for rel, entry in current["files"].items():
            packet_sources.append(packet_source(lane, rel, entry["items"]))
            packet_targets.extend(packet_target(lane, rel, i) for i in entry["items"])
    def key_count():
        return (sum(len(entry["items"]) for entry in current["files"].values())
                + sum(sum(entry["kinds"].values()) for entry in metadata))
    skipped_files = collections.defaultdict(list)
    def skipped(rel, reason):
        skipped_files[reason].append(rel)
    for rel in files:
        if max_keys is not None and key_count() >= max_keys:
            break
        group, basis = lane.subsystem(rel) if not mixed else (None, "mixed")
        if prefix and not (under(group, prefix) or under(rel, prefix)):
            if args.file:
                fail(f"{rel} is outside subsystem {prefix}")
            skipped(rel, 'outside requested subsystem')
            continue
        if not mixed and selected is not None and group != selected:
            skipped(rel, 'outside selected subsystem batch')
            continue
        if rel in current["files"]:
            skipped(rel, 'already in this session')
            continue
        if not lane.servable(rel):
            skipped(rel, 'not an eligible source (ownership, vendor/export or request protections)')
            continue
        text = lane.text(rel)
        if text is None:
            skipped(rel, 'source is missing')
            continue
        if len(text) > source_limit:
            candidates = data_request_items(lane, rel)
            if not candidates:
                skipped(rel, f'exceeds {source_limit} character limit; no eligible registered data request')
                continue
        else:
            candidates = cache.items(rel, text)
        if selected_keys:
            candidates = [*candidates, *(i for i in spelled_items(lane, rel) if key_of(rel, *i[:3]) in selected_keys)]
        items = [i for i in candidates
                 if i[0] in NAMED and (not selected_keys or key_of(rel, *i[:3]) in selected_keys) and needs_review(key_of(rel, *i[:3]), state, tally, refused)
                 and (worker not in {w for v in tally[key_of(rel, *i[:3])].values() for w in v}
                      or key_of(rel, *i[:3]) in clarifications.get(rel, ()))]
        targeted = [i for i in items if key_of(rel, *i[:3]) in reviews.get(rel, ())]
        meanings = [i for i in items if key_of(rel, *i[:3]) in clarifications.get(rel, ())]
        explicit_review = getattr(args, "review_only", False)
        meaning_review = bool(meanings) and (not args.file or only_meaning) and not targeted and not explicit_review
        review = bool(targeted) and (not args.file or explicit_review)
        if only_meaning or selected_meaning is True or meaning_review:
            items = meanings
            meaning_review = bool(items)
            review = False
        elif explicit_review or selected_review is True or review:
            items = targeted
            review = bool(items)
        else:
            items = [i for i in items if key_of(rel, *i[:3]) not in clarifications.get(rel, ())]
        if max_keys is not None:
            remaining = max_keys - key_count()
            items = items[:max(0, remaining)]
        if not items:
            skipped(rel, 'no eligible unvoted keys match the selection')
            continue
        targets = [packet_target(lane, rel, i)
                   for i in items]
        source = packet_source(lane, rel, items)
        if max_chars is not None:
            while targets and len(json.dumps(dict(targets=packet_targets + targets,
                    sources=packet_sources + [source]), ensure_ascii=True)) > max_chars:
                targets.pop()
                items.pop()
                source = packet_source(lane, rel, items)
            if not items:
                print(f"name_lane: {rel}: no target fits --max-chars {max_chars}; left pending", file=sys.stderr)
                continue
        packet_targets.extend(targets)
        packet_sources.append(source)
        if selected_review is None:
            selected_review = review
            selected_meaning = meaning_review
        if not mixed and selected is None:
            selected = group
        if args.list_only:
            metadata.append({"file": rel, "chars": len(text), "subsystem": group, "group_basis": basis,
                             "second_review": review, "meaning_review": meaning_review,
                             "kinds": dict(collections.Counter(i[0] for i in items))})
        else:
            current["files"][rel] = {"sha": hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest(),
                                     "items": [list(i) for i in items], "second_review": review,
                                     "meaning_review": meaning_review}
            served.append((rel, text, items))
        if len(served) + len(metadata) >= (len(requested_files) or args.count):
            break
    for reason, paths in skipped_files.items():
        print(f"name_lane: passed over {len(paths)} file(s): {reason}: " + ', '.join(paths[:3]) +
              (f' (+{len(paths) - 3} more)' if len(paths) > 3 else ''), file=sys.stderr)
    if args.list_only:
        print(json.dumps(metadata, indent=1))
        return 0
    cache.save()
    if not served:
        print(f"name_lane: no shared names are left for session {session}. " + scoped_route(session, model))
        return 0
    selection_done = time.perf_counter()
    record.parent.mkdir(parents=True, exist_ok=True)
    if selected is not None:
        current["subsystem"] = selected
        sticky.parent.mkdir(parents=True, exist_ok=True)
        sticky.write_text(json.dumps({"subsystem": selected}), encoding="utf-8")
    record.write_text(json.dumps(current, indent=1))
    briefs = lane.path(f"{LANE_DIR}/briefs")
    briefs.mkdir(parents=True, exist_ok=True)
    out = briefs / f"{session}.txt"
    context = subsystem_brief(lane, served, selected) if not mixed else ""
    if registered:
        context = registered_brief(lane, registered) + "\n\n" + context
    out.write_text(context + "\n\n" + "\n\n".join(
                       brief_text(lane, rel, text, items, session, model,
                                  review=current["files"][rel].get("second_review", False),
                                  meaning_review=current["files"][rel].get("meaning_review", False))
                       for rel, text, items in served),
                   encoding="utf-8", errors="surrogateescape")
    print(f"name_lane: brief for {len(served)} file(s) ({sum(len(i) for _, _, i in served)} keys): {out}")
    print("name_lane: prepare timing " + json.dumps(dict(
        queue=round(queue_done-timing_start, 3),
        claims=round(claims_done-queue_done, 3),
        selection=round(selection_done-claims_done, 3),
        brief=round(time.perf_counter()-selection_done, 3),
        cache_hits=cache.hits, cache_misses=cache.misses,
        total=round(time.perf_counter()-timing_start, 3))))
    if len(served) > 1:
        print("name_lane: answer {\"<file>\": {<key>: <name>|\"skip\"}, ...} for several files")
    return 0


# ---------------------------------------------------------------- submit

def cmd_validate(lane, args):
    """Check the exact submission path without votes, approvals or session edits."""
    report = cmd_submit(lane, args, validate_only=True)
    path = Path(getattr(args, "report", None) or lane.path(f"{LANE_DIR}/validation/{args.session}.json"))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"name_lane: validation: {len(report['valid'])} valid, {len(report['rejected'])} rejected; {path}")
    for row in report["rejected"]:
        print(f"  {row['key']}: {row['reason']}")
    return 1 if report["rejected"] else 0


def spelling_problem(lane, rel, kind, scope, ident, rva, answer, file_words, text):
    """Why `answer` cannot name this placeholder now, or None."""
    why = lane.eligibility(rel, kind, scope, ident, rva) or lane.problem(
        kind, ident, answer, file_words, rel=rel, scope=scope, text=text)
    if not why and kind == "class" and lane.ctx.grep_files(answer, word=True) \
            and not lane.merges(rel, ident, answer):
        why = f"{answer} already exists; reconcile declarations before a class rename"
    return why


RESPELL_BATCHES = "bfme-name-respell-batches.json"


def respell_registry_path(lane):
    """Intent outlives disposable build inputs and is shared by worktrees."""
    cached = getattr(lane, "_respell_registry_path", None)
    if cached is not None:
        return cached
    common = lane.git("rev-parse", "--git-common-dir").strip()
    if not common:
        raise rename.Refusal("prepared respell registry requires a Git common directory")
    lane._respell_registry_path = (lane.root / common).resolve() / RESPELL_BATCHES
    return lane._respell_registry_path


def respell_bindings(lane):
    """Local operation bindings, shared by submit, fresh reviewers and apply.

    A missing/changed proposal is still registered: it must never fall through
    to the ordinary identifier-only application path.
    """
    path = respell_registry_path(lane)
    try:
        data = json.loads(path.read_text(encoding="utf-8")) if path.exists() else {
            "version": 1, "batches": {}}
        if set(data) != {"version", "batches"} or data["version"] != 1 or not isinstance(data["batches"], dict):
            raise ValueError("invalid registry")
        batches = dict(data["batches"])
        batches.update(getattr(lane, "_respell_preview", {}))
        by_key = {}
        for ident, batch in batches.items():
            digest = hashlib.sha256(json.dumps(batch, sort_keys=True).encode()).hexdigest()
            if ident != digest or set(batch) != {"manifest", "manifest_sha", "requests", "prepared"}:
                raise ValueError("changed operation binding")
            if not isinstance(batch["requests"], dict) or not batch["requests"] or not isinstance(batch["prepared"], dict):
                raise ValueError("invalid operation binding")
            for key in batch["requests"]:
                if key in by_key:
                    raise ValueError("a key belongs to two respell batches")
                by_key[key] = ident
        return batches, by_key
    except (OSError, ValueError, TypeError, AttributeError) as exc:
        raise rename.Refusal(f"prepared respell registry refuses application: {exc}") from exc


def _respell_proposal_path(lane, value):
    path = Path(value)
    path = path if path.is_absolute() else lane.root / path
    if path.is_symlink() or not path.resolve().is_relative_to(lane.path("build").resolve()):
        raise rename.Refusal("respell manifests and proposed sources must be local files under build/")
    return path.resolve()


def _respell_inputs(lane, batch):
    """Read exactly the operation/source snapshots registered before voting."""
    try:
        manifest = _respell_proposal_path(lane, batch["manifest"])
        if hashlib.sha256(manifest.read_bytes()).hexdigest() != batch["manifest_sha"]:
            raise ValueError("manifest changed")
        prepared = {}
        for rel, item in batch["prepared"].items():
            proposed = _respell_proposal_path(lane, item["path"]).read_bytes()
            current = lane.path(rel).read_bytes()
            if (hashlib.sha256(proposed).hexdigest() != item["sha"] or
                    hashlib.sha256(current).hexdigest() != item["source_sha"]):
                raise ValueError(f"source or proposal changed: {rel}")
            prepared[rel] = proposed
        return prepared
    except (OSError, ValueError, KeyError, TypeError) as exc:
        raise rename.Refusal(f"prepared respell inputs are missing or stale: {exc}") from exc


def register_respell_batch(lane, filename, served, *, preview=False):
    """Bind a normal submission to an indivisible ordinary-function operation.

    This records no vote or approval. Naming still uses independent identifier
    proposals; only a complete, current approved group may consume the binding.
    """
    try:
        path = _respell_proposal_path(lane, filename)
        raw = path.read_bytes()
        spec = json.loads(raw)
        if (set(spec) != {"version", "requests", "prepared"} or spec["version"] != 1 or
                not isinstance(spec["requests"], list) or not spec["requests"] or
                not isinstance(spec["prepared"], dict) or not spec["prepared"]):
            raise ValueError("expected version, requests and prepared")
        served_keys = {key_of(rel, *item[:3]) for rel, entry in served["files"].items()
                       for item in entry["items"]}
        batch = dict(manifest=str(path), manifest_sha=hashlib.sha256(raw).hexdigest(), requests={}, prepared={})
        for rel, proposal in spec["prepared"].items():
            parsed = PurePosixPath(rel)
            if (not rel.startswith("Code/") or not rel.endswith(".cpp") or ".." in parsed.parts or
                    parsed.as_posix() != rel or "\\" in rel):
                raise ValueError(f"not an existing Code C++ source: {rel}")
            proposed = _respell_proposal_path(lane, proposal)
            batch["prepared"][rel] = dict(path=str(proposed), sha=hashlib.sha256(proposed.read_bytes()).hexdigest(),
                                            source_sha=hashlib.sha256(lane.path(rel).read_bytes()).hexdigest())
        if len(batch["prepared"]) > getattr(lane.ctx, "max_prepared", rename.PREPARED_DEFAULT):
            raise ValueError("too many prepared sources")
        names, addresses = set(), set()
        for request in spec["requests"]:
            if set(request) != {"key", "new"}:
                raise ValueError("requests take only key and new")
            key, new = request["key"], request["new"]
            rel, kind, scope, old = split_key(key)
            if key not in served_keys or kind != "function" or compiler_spelled(old):
                raise ValueError("each request must be an ordinary function key in this session")
            at = int(scope, 16)
            own = [row for row in lane.ledger().get(rel, ()) if rename._rva(row.get("target_rva")) == at]
            if (len(own) != 1 or own[0].get("status") != "matched" or
                    rename.split_function_name(own[0]["name"])[1] != old):
                raise ValueError("a requested row no longer has its served identity")
            if (rel not in batch["prepared"] or not new.startswith("?") or
                    rename.split_function_name(new)[1] == old or key in batch["requests"] or
                    new in names or at in addresses):
                raise ValueError("each request needs its prepared owner and a distinct renamed full spelling")
            names.add(new)
            addresses.add(at)
            batch["requests"][key] = dict(old=own[0]["name"], new=new)
        _respell_inputs(lane, batch)
        ident = hashlib.sha256(json.dumps(batch, sort_keys=True).encode()).hexdigest()
        from portable_lock import lock, unlock
        target = respell_registry_path(lane)
        with target.with_suffix(".lock").open("a") as handle:
            lock(handle, exclusive=True, wait_notice="name_lane: waiting for the lane lock...")
            try:
                batches, bound = respell_bindings(lane)
                if any(key in bound and bound[key] != ident for key in batch["requests"]):
                    raise ValueError("a key is already bound to a different prepared respell")
                if preview:
                    lane._respell_preview = {ident: batch}
                else:
                    batches[ident] = batch
                    temporary = target.with_suffix(f".{os.getpid()}.{time.time_ns()}.tmp")
                    temporary.write_text(json.dumps(dict(version=1, batches=batches), indent=2), encoding="utf-8")
                    temporary.replace(target)
            finally:
                unlock(handle)
        return ident
    except (OSError, ValueError, TypeError, KeyError, AttributeError, rename.Refusal) as exc:
        raise rename.Refusal(f"prepared respell registration refused: {exc}") from exc


def agreement_row(lane, tally, refused, key, kind, ident, answer, rva, mine, role=""):
    name = lane_spelling(lane, answer, kind)
    row = {"id": record_id(key, name, role), "kind": kind, "old": ident, "new": name,
           "rva": f"0x{rva:08X}" if rva is not None else "",
           "agents": ";".join(f"{w}@{m}" for w, m in sorted(mine.items())), "key": key, "status": "agreed"}
    row["detail"] = approval_detail(tally, refused, row)
    return row


def fresh_voters(lane, key, h, voters, text, pending=()):
    """The `voters` of hash `h` whose recorded fingerprints say the source they were served is
    `text`, the file as it reads now. A placeholder that still exists does not show a voter saw
    its current meaning. A vote with no fingerprint, or any other fingerprint, is not fresh, and
    no agreement is recorded from it: votes cast before fingerprints existed no longer count, by
    design, and are not derived from history. `pending` are rows this submit has yet to write."""
    sha = hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest()
    seen = collections.defaultdict(list)
    for row in [*lane.table(VOTE_SOURCES, VOTE_SOURCE_COLUMNS), *pending]:
        if row.get("key") == key and row.get("hash") == h:
            seen[row.get("worker")].append(row)
    return {worker: model for worker, model in voters.items()
            if name_agreement.current_fingerprint(seen.get(worker, ())) == sha}


def unrecorded_agreements(lane, *, lead=2, min_models=1):
    """[key] whose votes, as they stand, already agree on a spelling while no agreement records
    it. Blind votes submitted in different checkouts each tally before the other exists, and
    land through separate pushes, so neither submit can record the agreement: it can only be
    derived from the votes afterwards. Votes hold hashes, so this finds the key, not the name;
    `agree` takes the spelling from whoever knows it and checks it against these votes."""
    return [key for key, _h, _voters, _rivals in unrecorded_votes(lane, lead=lead, min_models=min_models)]


def unrecorded_votes(lane, *, lead=2, min_models=1):
    """[(key, winning hash, its voters, the rival voter sets)] behind unrecorded_agreements."""
    tally, state, refused = lane.tally(), lane.state(), lane.disputed()
    found = []
    for key in list(tally):
        if name_agreement.scoped_key(key) or (key in state and state[key]["status"] not in REOPENED):
            continue
        barred = {name_agreement.hash_canon(key, spelled) for spelled in refused.get(key, ())}
        standing = {h: voters for h, voters in tally[key].items() if h not in barred}
        for h, voters in standing.items():
            rivals = [v for other, v in standing.items() if other != h]
            if wins(voters, rivals, lead=lead, min_models=min_models, key=key):
                found.append((key, h, voters, rivals))
    return found


def agreed_prefix_hash(rows):
    """The sha256 of agreement rows by column, so line endings do not change it."""
    digest_of = hashlib.sha256()
    for row in rows:
        digest_of.update(("\x1f".join(row.get(c) or "" for c in AGREED_COLUMNS) + "\n").encode("utf-8", "surrogateescape"))
    return digest_of.hexdigest()


def report_grandfathered(lane, state):
    """Say which pending records `apply` lands with no source check, so it is never silent."""
    fault = lane.grandfather_fault()
    if fault:
        print(f"name_lane: {fault}")
        return
    old = lane.grandfathered()
    waiting = sum(row["status"] == "agreed" and row["id"] in old for row in state.values())
    blocked = sum(row["status"] == "blocked" and row["id"] in old for row in state.values())
    if waiting or blocked:
        print(f"name_lane: {waiting} waiting and {blocked} blocked record(s) predate vote fingerprints: grandfathered, "
              "they land with no check that the source still reads as voted (docs/naming.md)")


def report_unsettled(lane, state):
    """The keys no command moves on: voters who accepted different spellings for the source as it
    reads now, and an approval that no longer proves its spelling, which holds its key shut."""
    votes, resolutions = lane.votes(), lane.resolutions()
    crossed = {}
    for key in sorted({row["key"] for row in resolutions}):
        source = lane.ctx.read(split_key(key)[0])
        if source is None:
            continue
        moved = name_agreement.moved_spellings(votes, resolutions, key, hashlib.sha256(source).hexdigest())
        spellings = set().union(*moved.values())
        if len(spellings) > 1:
            crossed[key] = sorted(row["name"] for row in resolutions if row["key"] == key and row["hash"] in spellings)
    for key, names in crossed.items():
        print(f"name_lane: CROSSED, no spelling can land and no command settles it: {key}: "
              f"{' / '.join(dict.fromkeys(names))}")
    held = [row for key, row in sorted(state.items()) if key not in crossed and row["status"] == "agreed"
            and row["id"].startswith("nr-") and not resolution_support(lane, row)[1]]
    if held:
        print(f"name_lane: {len(held)} reviewed approval(s) no longer prove their spelling for this source; "
              "apply leaves them, resolve refuses their keys and no command settles them:")
        for row in held:
            print(f"  {row['key']} -> {row['new']}")


def report_unrecorded(lane, *, lead=2, min_models=1, limit=10):
    """Print the keys `agree` can record. The others are only counted: votes for a source that has
    changed since, or with no fingerprint, need fresh votes; a key whose file or placeholder has
    gone names something that no longer exists."""
    live, stale, gone = [], 0, 0
    for key, h, voters, rivals in unrecorded_votes(lane, lead=lead, min_models=min_models):
        try:
            rel, kind, scope, ident = split_key(key)
            rva = int(scope, 16) if kind == "function" else None
            text = lane.text(rel)
            usable = text is not None and not lane.eligibility(rel, kind, scope, ident, rva)
        except ValueError:
            usable, text = False, None
        if not usable:
            gone += 1
        elif wins(fresh_voters(lane, key, h, voters, text), rivals, lead=lead, min_models=min_models, key=key):
            live.append(key)
        else:
            stale += 1
    if live or stale or gone:
        print(f"name_lane: {len(live)} key(s) have agreeing votes and no agreement record; a voter records one "
              "with `name_lane.py agree --key KEY --name SPELLING`"
              + (f" ({stale} more need fresh votes from other workers: a vote counts only if its fingerprint "
                 "matches the file as it reads today, so older votes with none no longer count; this is "
                 "intended, not a fault)" if stale else "")
              + (f" ({gone} more name a file or placeholder that has gone)" if gone else ""))
    for key in live[:limit]:
        print(f"  {key}")
    if len(live) > limit:
        print(f"  ... and {len(live) - limit} more")


def cmd_agree(lane, args):
    """Record an agreement the votes have already reached (unrecorded_agreements). No vote is
    added. The spelling must hash to the votes' winning hash, so knowing it proves nothing
    beyond what the voters agreed; the agreeing voters must have been served the source as it
    reads now (fresh_voters); and it passes the checks a submit would apply today."""
    key, name = args.key, args.name.strip()
    try:
        rel, kind, scope, ident = split_key(key)
    except ValueError:
        fail("--key needs source|kind|scope|placeholder")
    if kind not in NAMED:
        fail(scoped_route(sources=[rel]))
    state, tally, refused = lane.state(), lane.tally(), lane.disputed()
    if key in state and state[key]["status"] not in REOPENED:
        fail(f"{key} already has agreement {state[key]['id']} ({state[key]['status']})")
    if canon(name) in refused.get(key, ()):
        fail(f"{name} is disputed for {key}")
    mine, rivals, role = name_agreement.support(tally, refused, key, name)
    if not wins(mine, rivals, lead=args.lead, min_models=args.min_models, key=key):
        fail(f"votes do not agree on {name} for {key}: {len(mine)} voter(s), rivals "
             f"{sorted(len(r) for r in rivals)} (--lead {args.lead} --min-models {args.min_models}); "
             "the spelling must be one the voters proposed")
    text = lane.text(rel)
    if text is None:
        fail(f"{rel} no longer exists: its votes name nothing")
    items = {key_of(rel, *item[:3]): item for item in [*lane.owned(rel, text, kinds=NAMED), *spelled_items(lane, rel)]}
    if key not in items:
        fail(f"{rel} no longer owns {ident} as a {kind}: its votes name nothing")
    rva = items[key][3]
    fresh = fresh_voters(lane, key, digest(key, name), mine, text)
    if not wins(fresh, rivals, lead=args.lead, min_models=args.min_models, key=key):
        fail(f"{len(fresh)} of {len(mine)} vote(s) for {name} were served {rel} as it reads now: a vote with no "
             "fingerprint, or for a source that has changed since, needs a fresh vote (`next --key KEY`)")
    file_words = set(name_metric.WORD.findall(name_metric.strip(text)))
    why = spelling_problem(lane, rel, kind, scope, ident, rva, name, file_words, text)
    if why:
        fail(f"{name} cannot name {ident}: {why}")
    row = agreement_row(lane, tally, refused, key, kind, ident, name, rva, fresh, role)
    lane.append(AGREED, AGREED_COLUMNS, [row])
    print(f"  AGREED: {key} -> {row['new']} ({row['agents']})")
    print(f"name_lane: agreement recorded from {len(fresh)} existing vote(s); no vote added; stage {AGREED}")
    return 0


def cmd_submit(lane, args, *, lead=2, min_models=1, verify=rename.build_verify, checks=rename.ledger_checks,
               validate_only=False):
    apply_ready = getattr(args, "apply_ready", None)
    auto_workflow = getattr(args, "auto_workflow", False) and not getattr(args, "propose_only", False)
    if ((apply_ready is not None and apply_ready < 1)
            or ((apply_ready is not None or auto_workflow) and getattr(args, "max_files", 25) < 1)):
        fail("--apply-ready and --max-files must be positive")
    session, model = session_id(args.session), model_id(args.model)
    record = lane.path(f"{LANE_DIR}/sessions/{session}.json")
    if not record.exists():
        fail(f"unknown session {session}: run `next --session {session}` in this checkout first")
    served = json.loads(record.read_text())
    if served.get("model") != model:
        fail(f"session {session} was served to {served.get('model')}, not {model}")
    worker = lane.worker()
    if served.get("worker") != worker:
        fail(f"session {session} was served to another worker; a vote counts only from the worker that "
             "`next` served (BFME_CLAIM_OWNER, BFME_RUN_ID or CLAUDE_CODE_SESSION_ID decide who you are)")
    if getattr(args, "respell_batch", None):
        try:
            register_respell_batch(lane, args.respell_batch, served, preview=validate_only)
        except rename.Refusal as exc:
            fail(str(exc))
    answers = json.loads(Path(args.answer).read_text(encoding="utf-8"))
    files = served["files"]
    if len(files) == 1 and not any(k in files for k in answers):
        answers = {next(iter(files)): answers}
    unknown = set(answers) - set(files)
    if unknown:
        fail(f"files not served to session {session}: {', '.join(sorted(unknown)[:4])}")
    answers = {rel: served_answers(rel, files[rel]["items"], mapping) for rel, mapping in answers.items()}
    retired = []
    for rel, mapping in answers.items():
        for kind, scope, ident, _rva in files[rel]["items"]:
            answer_id = answer_key(kind, scope, ident)
            proposal = mapping.get(key_of(rel, kind, scope, ident), "skip")
            spelling = proposal.get("name", "") if isinstance(proposal, dict) else proposal
            if kind in SCOPED_KINDS and str(spelling).strip().lower() != "skip":
                retired.append(dict(key=key_of(rel, kind, scope, ident), file=rel,
                                    answer_key=answer_id, retryable=False))
    if retired:
        message = "New local/parameter votes are refused, including old sessions. " + scoped_route(
            session, model, [item["file"] for item in retired])
        if validate_only:
            return dict(session=session, valid=[], rejected=[dict(item, reason=message) for item in retired],
                        proposed=len(retired), rejection_messages=[message])
        fail(message)
    prior_votes = lane.votes()
    tally, state, refused = lane.tally(), lane.state(), lane.disputed()
    now = datetime.date.today().isoformat()
    votes, meanings, agreed, rejected, local_proposals = [], [], [], [], []
    vote_sources = []
    invalid = []
    for rel, mapping in answers.items():
        entry = files[rel]
        text = lane.text(rel) or ""
        if hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest() != entry["sha"]:
            rejected.append(f"{rel}: changed since `next` served it; run `next` again")
            invalid.extend(dict(key=key_of(rel, *item[:3]), file=rel,
                                answer_key=answer_key(*item[:3]), reason="source changed; serve it again",
                                retryable=False) for item in entry["items"]
                           if key_of(rel, *item[:3]) in mapping)
            continue
        items = [tuple(i) for i in entry["items"]]
        unknown = set(mapping) - {key_of(rel, k, s, i) for k, s, i, _ in items}
        if unknown:
            fail(f"keys not served for {rel}: {', '.join(sorted(unknown)[:8])}. "
                 + scoped_route(session, model, [rel]))
        file_words, taken = set(name_metric.WORD.findall(name_metric.strip(text))), set()
        for kind, scope, ident, rva in items:
            proposal = mapping.get(key_of(rel, kind, scope, ident), "skip")
            meaning = None
            role = ""
            if isinstance(proposal, dict):
                try:
                    if "name" not in proposal or set(proposal) - {"name", "meaning", "role"} or len(proposal) < 2:
                        raise ValueError("structured answers need a name and role or meaning")
                    if "meaning" in proposal:
                        meaning = name_agreement.meaning_digest(key_of(rel, kind, scope, ident), proposal["meaning"])
                    if "role" in proposal:
                        role = proposal["role"]
                        if (not isinstance(role, str) or not 12 <= len(role.strip()) <= 200
                                or "\n" in role or "\r" in role):
                            raise ValueError("role must be a 12-200 character single-line description")
                        role = role.strip()
                    proposal = proposal["name"]
                except (ValueError, TypeError) as exc:
                    rejected.append(f"{answer_key(kind, scope, ident)}: {exc}")
                    invalid.append(dict(key=key_of(rel, kind, scope, ident), file=rel,
                        answer_key=answer_key(kind, scope, ident), reason=str(exc), retryable=True))
                    continue
            answer = str(proposal).strip()
            if answer.lower() == "skip":
                continue
            key = key_of(rel, kind, scope, ident)
            h = digest(key, answer)
            already = worker in {w for v in tally[key].values() for w in v}
            annotate = (already and meaning and worker in tally[key].get(h, {})
                        and not tally.meanings[key].get((h, worker)))
            why = spelling_problem(lane, rel, kind, scope, ident, rva, answer, file_words, text)
            name_scope = lane.collision_scope(rel, kind, scope, ident) or ""
            if not why and kind in NAMED and (name_scope, canon(answer)) in taken:
                why = "the same name as another placeholder in this file"
            if not why and canon(answer) in refused.get(key, ()):
                why = "disputed for this key"
            if not why and already and not annotate:
                mine, rivals, role = name_agreement.support(tally, refused, key, answer, meaning)
                fresh = fresh_voters(lane, key, h, mine, text)
                if (worker in fresh and needs_review(key, state, tally, refused)
                        and wins(fresh, rivals, lead=lead, min_models=min_models, key=key)):
                    # Its vote is counted; a vote from another checkout completed the agreement
                    # after this worker's submit ran, so neither submit recorded it. No new vote.
                    row = agreement_row(lane, tally, refused, key, kind, ident, answer, rva, fresh, role)
                    agreed.append(row)
                    state[key] = row
                    continue
                why = "this worker already voted on it (under some session label)"
            if why:
                rejected.append(f"{answer_key(kind, scope, ident)} -> {answer}: {why}")
                invalid.append(dict(key=key, file=rel, answer_key=answer_key(kind, scope, ident),
                                    name=answer, reason=why, retryable=not already))
                continue
            if kind in NAMED:
                taken.add((name_scope, canon(answer)))
            if annotate:
                vote = next(v for v in reversed(prior_votes)
                            if v["key"] == key and v["hash"] == h and v["worker"] == worker)
            else:
                vote = {"key": key, "hash": h, "model": model, "session": session, "worker": worker, "date": now}
                votes.append(vote)
                vote_sources.append({"key": key, "hash": h, "worker": worker, "session": session,
                                     "source_sha": entry["sha"]})
                tally[key][h][worker] = model
                local_proposals.append(dict(key=key, name=answer, worker=worker,
                                            source_sha=entry["sha"], role=role))
            if meaning:
                meanings.append({**vote, "meaning": meaning})
                tally.meanings[key][h, worker].add(meaning)
            open_key = needs_review(key, state, tally, refused)
            mine, rivals, role = name_agreement.support(tally, refused, key, answer, meaning)
            promote = (annotate and role and key in state and state[key]["status"] == "agreed"
                       and not name_agreement.record_meaning(state[key]["id"]))
            fresh = fresh_voters(lane, key, h, mine, text, pending=vote_sources)
            if (open_key or promote) and wins(fresh, rivals, lead=lead, min_models=min_models, key=key):
                row = agreement_row(lane, tally, refused, key, kind, ident, answer, rva, fresh, role)
                agreed.append(row)
                state[key] = row
    if validate_only:
        return dict(session=session, valid=[v["key"] for v in votes], rejected=invalid,
                    proposed=len(votes) + len(invalid), rejection_messages=rejected)
    lane.append(VOTES, VOTE_COLUMNS, votes)
    lane.append(VOTE_SOURCES, VOTE_SOURCE_COLUMNS, vote_sources)
    lane.append(MEANINGS, MEANING_COLUMNS, meanings)
    lane.append(AGREED, AGREED_COLUMNS, agreed)
    # Plaintext stays local and is never included in a blind review packet.
    # Once both blind votes exist, the comparison stage can retrieve it.
    for proposal in local_proposals:
        path = proposal_path(lane, proposal["key"], proposal["worker"])
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists():
            temporary = path.with_suffix(f".{session}.tmp")
            temporary.write_text(json.dumps(proposal, indent=2), encoding="utf-8")
            if not path.exists():
                temporary.replace(path)
            else:
                temporary.unlink()
    for rel in answers:
        files.pop(rel, None)
    if files:
        record.write_text(json.dumps(served, indent=1))
    else:
        record.unlink()
    for r in rejected:
        print("  rejected:", r)
    for a in agreed:
        print(f"  AGREED: {a['key']} -> {a['new']} ({a['agents']})")
    print(f"name_lane: {len(votes)} vote(s) recorded as hashes, {len(rejected)} rejected, {len(agreed)} newly agreed"
          + ("; run `python3 tools/name_lane.py apply` to land them"
             if agreed and apply_ready is None and not auto_workflow else ""))
    if meanings:
        print(f"name_lane: stage {VOTES}, {MEANINGS} and {AGREED} together for structured meanings")
    result = 0
    if agreed and (apply_ready is not None or auto_workflow):
        result = cmd_apply(lane, argparse.Namespace(
            key=[row["key"] for row in agreed], retry_blocked=False, only_labels=None,
            lead=lead, min_models=min_models, claim=True, limit=apply_ready,
            max_files=getattr(args, "max_files", 25)), verify=verify, checks=checks)
    if votes and not getattr(args, "no_auto_review", False) and not getattr(args, "propose_only", False):
        import name_review
        try:
            if auto_workflow:
                name_review.maybe_launch(lane, auto_configure=True, apply_new=True)
            else:
                name_review.maybe_launch(lane)
        except (name_review.ReviewError, OSError, ValueError) as exc:
            print(f"name_lane: votes recorded; reviewer dispatch failed: {exc}", file=sys.stderr)
    return result


def lane_spelling(lane, name, kind):
    """Zero Hour's or WorldBuilder's own spelling of an agreed name when exactly
    one fits: votes match case- and order-blind, so otherwise the last voter's
    casing would land. A mangled spelling is exact and is its own."""
    if name.startswith("?"):
        return name
    words = set()
    for row in lane.ctx.dicts(rename.WB_LEADS):
        words |= set(name_metric.WORD.findall(row.get("wb_name", "")))
    zh = lane.path(rename.BFME1) / rename.ZH_TREE
    if zh.exists():
        target = canon(name)
        pattern = "|".join(re.escape(w) for w in re.findall(r"[A-Za-z]{3,}", name)[:1]) or re.escape(name)
        matches = lane.reference_matches(rf"[A-Za-z_]*({pattern})[A-Za-z_0-9]*",
                                         [f"{rename.BFME1}/{rename.ZH_TREE}"], ("h",),
                                         ignore_case=True, whole_word=True)
        words |= {w for w in matches.split() if canon(w) == target}
    fits = {w for w in words if canon(w) == canon(name) and lane.problem(kind, "", w, set()) is None}
    return fits.pop() if len(fits) == 1 else name


# ---------------------------------------------------------------- apply / dispute

def rename_kwargs(kind, scope, old, new, rva, rel, lane=None):
    if kind == "function":
        return {"rva": int(scope, 16), "new": new}
    if kind == "class":
        # a registered placeholder taking a name the tree spells only as a type lands as a merge
        return {"name": old, "new": new, **({"merge": True} if lane is not None and lane.merges(rel, old, new) else {})}
    if kind == "member":
        return {"cls": scope, "member": old, "new": new}
    if kind in ("param", "local"):
        return {"source": rel, "name": old, "new": new, "function": scope, **({"local_binding": True} if kind == "local" else {})}
    if kind == "global":
        return {"name": old, "new": new}
    raise rename.Refusal(f"unknown lane kind {kind}")


def warm_donor_parameters(lane, files):
    """Batch donor lookups that owned() would otherwise issue once per file."""
    functions = set()
    items = files.items() if hasattr(files, "items") else ((rel, lane.text(rel)) for rel in files)
    for rel, text in items:
        if text is None:
            continue
        code = name_metric.strip(text)
        for scope, _start, _end, params in name_metric.functions_in(code):
            if any(name_metric.weak("param", name) and not name_metric.placeholder(name)
                   for name in rename.parameters(params)):
                functions.add(base(scope))
    return lane.donor_params(functions) if functions else {}


def verified_changes(lane, plans):
    """{rel: (bytes before, bytes after)} of the Code sources these verified plans changed, for
    the files that on disk still read as the transaction left them."""
    before, after = {}, {}
    for plan in plans:
        for rel, data in getattr(plan, "before", {}).items():
            if rel.startswith("Code/") and isinstance(data, bytes):
                before.setdefault(rel, data)
        for rel, data in getattr(plan, "after", {}).items():
            if rel.startswith("Code/") and isinstance(data, bytes):
                after[rel] = data
    changed = {}
    for rel, data in after.items():
        try:
            current = lane.path(rel).read_bytes()
        except OSError:
            continue
        if rel not in before or before[rel] == data or current != data:
            continue
        changed[rel] = (before[rel], data)
    return changed


def carry_verified_votes(lane, plans, landed):
    """Keep the file's other votes current across a landing that is exactly its renames.

    Each carry is a new row (VOTE_SOURCES is append-only) running from the text before this
    landing to the text after it, for a vote whose fingerprint stands for that text before. So
    an edit before the landing leaves the vote behind, one during it fails verified_changes, and
    one mixed into the plan's bytes fails rename_only. A class key is left out: its rename binds
    each vote to its own fingerprint (rename.votes_bound_to_text)."""
    pairs = {(row["old"], row["new"]) for row in landed}
    changed = {rel: (hashlib.sha256(old).hexdigest(), hashlib.sha256(new).hexdigest())
               for rel, (old, new) in verified_changes(lane, plans).items()
               if name_agreement.rename_only(old, new, pairs)}
    if not changed:
        return
    gone = {row["key"] for row in landed}
    votes = collections.defaultdict(list)
    for row in lane.table(VOTE_SOURCES, VOTE_SOURCE_COLUMNS):
        votes[row["key"], row["hash"], row["worker"]].append(row)
    carried = []
    for (key, h, worker), rows in votes.items():
        rel, kind = (key.split("|") + [""])[:2]
        if rel not in changed or key in gone or kind == "class":
            continue
        old, new = changed[rel]
        if name_agreement.current_fingerprint(rows) == old:
            session = next(r["session"] for r in rows if name_agreement.carried_from(r["session"]) is None)
            carried.append({"key": key, "hash": h, "worker": worker, "source_sha": new,
                            "session": name_agreement.carried_session(old, session)})
    lane.append(VOTE_SOURCES, VOTE_SOURCE_COLUMNS, carried)


def carry_verified_proposals(lane, plans):
    """Keep this worker's pending plaintext proposals current across verified renames.

    Require the proposal's exact old source, the transaction's final source,
    and the on-disk source to agree. Never refresh a proof over unrelated edits
    or a failed/speculative rename, and never touch another worker's proposal.
    """
    changed = {rel: (hashlib.sha256(old).hexdigest(), hashlib.sha256(new).hexdigest())
               for rel, (old, new) in verified_changes(lane, plans).items()}
    if not changed:
        return
    worker = lane.worker()
    for vote in lane.votes():
        rel = vote["key"].split("|")[0]
        if vote["worker"] != worker or rel not in changed:
            continue
        path = proposal_path(lane, vote["key"], worker)
        if path.is_file():
            try:
                proposal = json.loads(path.read_text(encoding="utf-8"))
                old, new = changed[rel]
                if (not isinstance(proposal, dict) or proposal.get("source_sha") != old or proposal.get("worker") != worker
                        or proposal.get("key") != vote["key"]):
                    continue
                proposal["source_sha"] = new
                proposal["verified_source_carry"] = {"before": old, "after": new}
                temporary = path.with_suffix(f".{os.getpid()}.carry")
                temporary.write_text(json.dumps(proposal, indent=2), encoding="utf-8")
                temporary.replace(path)
            except (OSError, ValueError) as exc:
                print(f"name_lane: could not carry local proposal {vote['key']}: {exc}", file=sys.stderr)


def _apply_run(lane, todo, args, tally, refused, *, verify, checks, max_files):
    """Apply selected live keys together; isolate a restored failure by splitting.

    Every retry is planned against the surviving verified tree, and verifies
    all sources and consumers its changes affect. A restored failed group never
    removes earlier successful groups or leaves their references half-renamed.
    """
    counts = collections.Counter()
    outcomes = []
    blockers = _blockers(lane)
    blockers_changed = False
    session = rename.RunBatchSession(lane.ctx)

    def record(row, status, detail):
        nonlocal blockers_changed
        outcome = dict(row, status=status, detail=" ".join(str(detail).split())[:300])
        if status == "stale":
            outcome["agents"] = ""
        if status in ("landed", "stale") and row["key"] in blockers:
            blockers.pop(row["key"], None)
            blockers_changed = True
        outcomes.append(outcome)
        counts[status] += 1
        if status == "blocked":
            print(f"{row['key']}: blocked: {outcome['detail']}", flush=True)

    ready = []
    texts = {rel: lane.text(rel) for rel in todo}
    eligible = {rel for rel, text in texts.items()
                if text is not None and lane.servable(rel)}
    warm_donor_parameters(lane, {rel: texts[rel] for rel in eligible})
    for rel, rows in sorted(todo.items()):
        text = texts[rel]
        live = {key_of(rel, k, s, i) for k, s, i, _ in
                lane.owned(rel, text, kinds={r["kind"] for r in rows})} if rel in eligible else set()
        for row in rows:
            if row["key"] in live:
                ready.append(row)
            else:
                record(row, "stale", "the file changed or the placeholder is gone")
    # Scoped/member approvals must be consumed before enclosing functions or
    # classes change their qualified names, even across different owner files.
    ready.sort(key=lambda row: (LAND_ORDER[row["kind"]], row["key"]))

    def apply_group(rows):
        nonlocal blockers_changed
        if not rows:
            return
        rows = sorted(rows, key=lambda row: (LAND_ORDER[row["kind"]], row["key"]))
        requests = []
        for row in rows:
            rel, kind, scope, old = split_key(row["key"])
            requests.append((kind, dict(basis="inferred", evidence=f"agree:{row['id']}",
                max_files=max_files, **rename_kwargs(kind, scope, old, row["new"], row["rva"], rel, lane))))
        result = rename.run_batch(lane.ctx, requests, claim=args.claim, verify=verify, checks=checks, session=session)
        planned = [rows[index] for index, _plan in result.plans]
        rejected = [rows[index] for index in result.refused]
        if result.failure is None:
            carry_verified_proposals(lane, [plan for _index, plan in result.plans])
            carry_verified_votes(lane, [plan for _index, plan in result.plans], planned)
            for row in planned:
                record(row, "landed", approval_detail(tally, refused, row))
            for index, reason in result.refused.items():
                record(rows[index], "blocked", reason)
            return
        conflict_keys = _claim_conflicts(result)
        if conflict_keys:
            held_rows = []
            for index, plan in result.plans:
                keys = rename.claim_keys(plan)
                keys = {claims.key_of(key) for key in keys}
                expanded = claims.lock_keys(keys, root=lane.root)
                if conflict_keys.intersection(keys | expanded):
                    held_rows.append(rows[index])
            if held_rows:
                held_keys = {row["key"] for row in held_rows}
                survivors = [row for row in planned if row["key"] not in held_keys]
                print(f"name_lane: claim race identified {len(held_rows)} held approval(s); "
                      "leaving their approvals unchanged and retrying the free names together.", flush=True)
                apply_group(survivors + rejected)
                return
        failed_sources, diagnostic = _diagnostic_sources(result, result.plans)
        missing_header = _unchanged_missing_include(lane, result.plans, failed_sources, diagnostic)
        if failed_sources and missing_header:
            affected = [(index, plan) for index, plan in result.plans
                        if failed_sources.intersection(plan.verify)]
            if affected:
                affected_rows = [rows[index] for index, _plan in affected]
                affected_keys = {row["key"] for row in affected_rows}
                clean = [row for row in planned if row["key"] not in affected_keys]
                detail = f"verification failed in {', '.join(sorted(failed_sources))}: {diagnostic}"
                for row in affected_rows:
                    record(row, "blocked", detail)
                    _remember_blocker(lane, blockers, row,
                                      [plan for index, plan in affected if rows[index]["key"] == row["key"]],
                                      detail, header=missing_header, max_files=max_files,
                                      sources=failed_sources)
                blockers_changed = True
                print(f"name_lane: compiler diagnostic isolated {len(affected_rows)} proposal(s) in "
                      f"{len(failed_sources)} source(s); retrying the remaining names as one batch.", flush=True)
                apply_group(clean + rejected)
                return
        elif failed_sources:
            # A source location narrows the suspect group; it does not prove
            # that every proposal touching that source is invalid.
            result.suspects = [index for index, plan in result.plans
                               if failed_sources.intersection(plan.verify)]
        if len(planned) > 1:
            suspects = {id(rows[index]) for index in result.suspects}
            if suspects and len(suspects) < len(planned):
                # Keep source-sharing dependencies together when removing a plan.
                affected = set()
                for index, plan in result.plans:
                    if id(rows[index]) in suspects:
                        affected.update(plan.verify)
                changed = True
                while changed:
                    changed = False
                    for index, plan in result.plans:
                        if affected.intersection(plan.verify) and id(rows[index]) not in suspects:
                            suspects.add(id(rows[index]))
                            affected.update(plan.verify)
                            changed = True
                clean = [row for row in planned if id(row) not in suspects]
                suspect = [row for row in planned if id(row) in suspects]
                if clean:
                    print("name_lane: diagnostic identified a dependency group; retrying unaffected names first.", flush=True)
                    apply_group(clean)
                    apply_group(suspect)
                    apply_group(rejected)
                    return
            middle = len(planned) // 2
            print(f"name_lane: run batch restored ({result.failure}); isolating "
                  f"{middle} + {len(planned) - middle} names.", flush=True)
            apply_group(planned[:middle])
            apply_group(planned[middle:])
        else:
            for row in planned:
                record(row, "blocked", result.failure)
        # A planning collision may disappear when another name's failed edit is
        # removed. Replan refusals against the final surviving source state.
        apply_group(rejected)

    try:
        apply_group(ready)
    finally:
        try:
            session.close()
        finally:
            if outcomes:
                lane.append(AGREED, AGREED_COLUMNS, outcomes)
            if blockers_changed:
                updates = {key: value for key, value in blockers.items()
                           if key in {row["key"] for row in outcomes if row["status"] == "blocked"}}
                removed = {row["key"] for row in outcomes if row["status"] in ("landed", "stale")}
                _save_blockers(lane, updates, remove=removed)
    return counts["landed"], counts["blocked"], counts["stale"]


def approval_claim_keys(row):
    """Known owner scopes before planning discovers the full consumer footprint."""
    rel, kind, scope, old = split_key(row["key"])
    keys = {claims.file_key(rel)}
    rva = rename._rva(row.get("rva"))
    if rva is not None:
        keys.add(rva)
    cls = old if kind == "class" else scope if kind == "member" else None
    class_key = claims.class_key(cls)
    if class_key is not None:
        keys.add(class_key)
    return keys


APPLY_BLOCKERS = f"{LANE_DIR}/apply_blockers.json"


def _input_fingerprint(lane, paths, new, *, max_files=25, compiler_state=None, exclude=(),
                       scope_paths=None, nested_scope=None):
    """Conservative tracked, untracked and compiler-input snapshot.

    Broader invalidation is preferable to suppressing a retry after a header,
    flag, tool or ledger changed. Git failures make the blocker uncacheable.
    """
    digest = hashlib.sha256()
    def repository(root):
        selected_scope = scope_paths if root == lane.root else nested_scope
        scope = ("--", *(selected_scope if selected_scope is not None else (".",)), ":(exclude)build")
        if root == lane.root:
            scope += (f":(exclude){AGREED}",)
            scope += tuple(f":(exclude){rel}" for rel in exclude)
        index = b""
        for command in (("ls-files", "--stage", "-z"), ("diff", "--binary", "--no-ext-diff", "--no-textconv")):
            result = subprocess.run(["git", "-C", str(root), *command, *scope], capture_output=True)
            if result.returncode:
                return False
            if command[0] == "ls-files":
                index = result.stdout
            digest.update(result.stdout)
        result = subprocess.run(["git", "-C", str(root), "ls-files", "--others", "--exclude-standard", "-z", *scope],
                                capture_output=True)
        if result.returncode:
            return False
        for raw in result.stdout.split(b"\0"):
            if raw:
                path = root / raw.decode("utf-8", errors="surrogateescape")
                try:
                    digest.update(raw + hashlib.sha256(path.read_bytes()).digest())
                except OSError:
                    return False
        # A dirty submodule's diff only says '-dirty'; inspect its own index
        # and worktree as well so edits inside it invalidate the snapshot.
        for item in index.split(b"\0"):
            if item.startswith(b"160000 ") and b"\t" in item:
                path = root / item.split(b"\t", 1)[1].decode("utf-8", errors="surrogateescape")
                if not (path / ".git").exists() or not repository(path):
                    return False
        return True
    if not repository(lane.root):
        return None
    for rel in sorted(set(paths)):
        digest.update(rel.encode("utf-8") + b"\0")
        try:
            data = lane.path(rel).read_bytes()
        except OSError:
            data = None
        digest.update(b"<missing>" if data is None else hashlib.sha256(data).digest())
    digest.update(json.dumps([new, max_files, compiler_state], sort_keys=True).encode("utf-8"))
    return digest.hexdigest()


def _blockers(lane):
    try:
        value = json.loads(lane.path(APPLY_BLOCKERS).read_text(encoding="utf-8"))
        return {key: row for key, row in value.items() if isinstance(row, dict)} if isinstance(value, dict) else {}
    except (OSError, ValueError):
        return {}


def _save_blockers(lane, updates, *, remove=()):
    from portable_lock import lock, unlock
    lane.path(LANE_DIR).mkdir(parents=True, exist_ok=True)
    with lane.path(f"{LANE_DIR}/.lock").open("a") as handle:
        lock(handle, exclusive=True, wait_notice="name_lane: waiting for the lane lock...")
        try:
            path = lane.path(APPLY_BLOCKERS)
            value = _blockers(lane)
            for key in remove:
                value.pop(key, None)
            value.update(updates)
            temp = path.with_suffix(".tmp")
            temp.write_text(json.dumps(value, sort_keys=True, indent=2) + "\n", encoding="utf-8")
            temp.replace(path)
        finally:
            unlock(handle)


def _same_blocker(lane, key, row, blockers, *, max_files=25):
    saved = blockers.get(key)
    if not saved or saved.get("version") != 2 or saved.get("new") != row.get("new"):
        return False
    if (not isinstance(saved.get("inputs"), list) or not saved["inputs"]
            or not all(isinstance(path, str) for path in saved["inputs"])
            or not isinstance(saved.get("header"), str)
            or not isinstance(saved.get("fingerprint"), str)):
        return False
    state = _missing_header_state(lane, saved.get("inputs", ()), saved.get("header", ""))
    if state is None:
        return False
    current = _input_fingerprint(lane, saved.get("inputs", ()), row.get("new"),
                                 max_files=max_files, compiler_state=state)
    return current is not None and saved.get("fingerprint") == current


def _remember_blocker(lane, blockers, row, plans, detail, *, header=None, max_files=25, sources=None):
    inputs = sorted(sources if sources is not None else {source for plan in plans for source in plan.verify})
    state = _missing_header_state(lane, inputs, header) if header else None
    if state is None:
        return
    fingerprint = _input_fingerprint(lane, inputs, row.get("new"),
                                     max_files=max_files, compiler_state=state)
    if fingerprint is None:
        return
    blockers[row["key"]] = {
        "version": 2, "header": header,
        "new": row.get("new", ""), "inputs": inputs,
        "fingerprint": fingerprint,
        "detail": " ".join(str(detail).split())[:300],
    }


def _claim_conflicts(result):
    if hasattr(result.failure, "claim_keys"):
        return set(result.failure.claim_keys)
    match = re.search(r"claimed by another worker:\s*([^\r\n]+)", str(result.failure or ""))
    if not match:
        return set()
    found = set()
    for label in match.group(1).split(","):
        label = label.strip()
        if not label:
            continue
        try:
            found.add(claims.key_of(label))
        except ValueError:
            continue
    return found


def _diagnostic_sources(result, plans):
    """Find verifier translation units named by MSVC diagnostics."""
    output = getattr(result, "diagnostics", "") or ""
    diagnostics = []
    for line in output.splitlines():
        if re.search(r":\s*(?:fatal\s+)?error\s+C\d+\b", line, re.I):
            diagnostics.append(line.strip())
    if not diagnostics:
        return set(), ""
    named = set()
    pattern = re.compile(r"^\s*[\"']?(?P<path>.+?\.(?:cpp|cc|cxx|c))[\"']?\(\d+(?:,\d+)?\)\s*:", re.I)
    for line in diagnostics:
        match = pattern.match(line)
        if match:
            named.add(match.group("path").replace("\\", "/").casefold())
    sources = set()
    for _index, plan in plans:
        for source in plan.verify:
            normal = source.replace("\\", "/").casefold()
            if any(path == normal or path.endswith("/" + normal) for path in named):
                sources.add(source)
    detail = diagnostics[-1]
    return sources, detail


def _unchanged_missing_include(lane, plans, sources, diagnostic):
    """Only an unchanged direct include proves the whole source cannot build."""
    found = re.search(r"\bC1083\s*:.*?Cannot open include file:\s*['\"]([^'\"]+)['\"]", diagnostic, re.I)
    if len(sources) != 1 or not found:
        return None
    header = found.group(1)
    include = re.compile(r"^\s*#\s*include\s*[<\"]" + re.escape(header) + r"[>\"]", re.M)
    def spells_include(data):
        text = data.decode("utf-8", errors="replace")
        text = rename.SEGMENT.sub(lambda match: re.sub(r"[^\n]", " ", match.group(0))
                                  if match.group(0).startswith(("//", "/*")) else match.group(0), text)
        return include.search(text)
    for source in sources:
        before = lane.ctx.read(source) or b""
        if not spells_include(before):
            return None
        for _index, plan in plans:
            after = getattr(plan, "after", {}).get(source, before)
            if not spells_include(after):
                return None
    return header


def _missing_header_state(lane, sources, header):
    """Prove enough compiler inputs to reuse a direct missing-include failure.

    Missing receipts, macro/forced includes or unreadable inventories disable
    persistent suppression. The ordinary diagnostic still isolates this run.
    """
    import build
    if not header or Path(header).is_absolute() or ".." in header.replace("\\", "/").split("/"):
        return None
    if lane.root.resolve() != build.ROOT.resolve():
        return None
    state = []
    try:
        for source in sorted(sources):
            path = lane.path(source)
            command, env = build.compiler_command(path, lane.path("build/match/blocker-probe.obj"))
            if any(arg.lower().startswith(("/fi", "-fi")) for arg in command):
                return None
            inventory = build.search_inventory(path, command, env)
            roots = build._include_search_roots(path, command, env)
            if inventory is None or roots is None:
                return None
            deps = {}
            for row in lane.ctx.rows():
                if row.get("source") == source:
                    output = build.row_object(row)
                    receipt = build._deps_sidecar(output) if output else None
                    if receipt and receipt.is_file():
                        meta = json.loads(receipt.read_text(encoding="utf-8"))
                        if not isinstance(meta, dict):
                            return None
                        if meta.get("source") == build._hash_file(str(path)) and isinstance(meta.get("deps"), dict):
                            deps = meta["deps"]
                    break
            includes = re.findall(r"^\s*#\s*include\s+(.+)$", path.read_text(encoding="utf-8"), re.M)
            if not deps and (len(includes) != 1 or includes[0].strip() not in (f'"{header}"', f'<{header}>')):
                return None
            dependency_hashes = {key: build._hash_file(str(build.ROOT / key)) for key in deps}
            candidates = {}
            for directory in [path.parent, *roots, *build._SWEEP_INCLUDE_DIRS]:
                candidate = Path(directory) / header
                resolved = build._case_resolve(str(candidate))
                candidates[str(candidate)] = build._hash_file(str(resolved)) if resolved else None
            executables = {part: build._hash_file(part) for part in command if part.lower().endswith(".exe")}
            if not executables or any(value is None for value in executables.values()):
                return None
            state.append([source, build._cmd_fingerprint(command, env), inventory, dependency_hashes,
                          candidates, executables, env.get("BFME_COMPILER_INPUTS", "")])
    except (OSError, ValueError, RuntimeError, SystemExit):
        return None
    return state


@claims.pick_snapshot()
def cmd_resolve(lane, args):
    """An original voter accepts a proposed spelling after reviewing the source.

    Votes stay blind and unchanged. This is an explicit, auditable second-stage
    decision by the original voters, not an extra vote under a new identity.
    """
    key, chosen = args.key, args.name.strip()
    try:
        rel, kind, scope, old = split_key(key)
    except ValueError:
        fail("--key needs source|kind|scope|placeholder")
    if kind not in KINDS or not rel.startswith("Code/"):
        fail("resolution needs an eligible Code/ name key")
    if kind in SCOPED_KINDS:
        fail(scoped_route(sources=[rel]))
    text = lane.text(rel)
    if text is None or not lane.servable(rel):
        fail(f"source unavailable or protected: {rel}")
    source_sha = hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest()
    state = lane.state()
    if state.get(key, {}).get("status") in ("agreed", "landed", "disputed"):
        fail("this key is already approved, landed or disputed")
    owned = {key_of(rel, k, s, i): rva for k, s, i, rva in [*lane.owned(rel, text), *spelled_items(lane, rel)]}
    if key not in owned:
        fail("the placeholder is no longer owned by this source")
    rva = owned[key]
    why = lane.eligibility(rel, kind, scope, old, rva) or lane.problem(
        kind, old, chosen, set(name_metric.WORD.findall(name_metric.strip(text))),
        rel=rel, scope=scope, text=text)
    if not why and kind == "class" and lane.ctx.grep_files(chosen, word=True) and not lane.merges(rel, old, chosen):
        why = f"{chosen} already exists; reconcile declarations before a class rename"
    if why:
        fail(f"resolution refused: {why}")
    if canon(chosen) in lane.disputed().get(key, ()):
        fail("chosen spelling was disputed for this key")
    if len(args.reason.strip()) < 12:
        fail("--reason must describe why this spelling fits the source")
    original = [v for v in lane.votes() if v["key"] == key]
    voter = lane.worker()
    own = [v for v in original if v["worker"] == voter]
    if not own:
        fail("only an original voter can accept a resolution")
    if len({v["worker"] for v in original}) < 2 or len({v["hash"] for v in original}) < 2:
        fail("resolution needs two independent, competing proposals")
    previous = [r for r in lane.resolutions() if r["key"] == key and r["worker"] == voter
                and r["source_sha"] == source_sha]
    # a reason for this worker's own blind vote records evidence, and binds it to nothing new
    own_hashes = {v["hash"] for v in own}
    if any(r["hash"] != digest(key, chosen) and r["hash"] not in own_hashes for r in previous):
        fail("this worker already accepted a different spelling for this source")
    chosen_hash = digest(key, chosen)
    blind = {v["worker"]: v["model"] for v in original if v["hash"] == chosen_hash}
    fresh_blind = fresh_voters(lane, key, chosen_hash, blind, text)
    # a fresh blind vote already accepts this spelling; the row still keeps the voter's evidence
    if not any(r["hash"] == chosen_hash for r in previous):
        lane.append(RESOLUTIONS, RESOLUTION_COLUMNS, [dict(key=key, hash=digest(key, chosen),
            name=chosen, source_sha=source_sha, worker=voter, model=own[0]["model"],
            reason=args.reason.strip(), date=datetime.date.today().isoformat())])
    resolutions = lane.resolutions()
    problems = name_agreement.verify_resolution(original, lane.agreed_rows(), resolutions,
                                                 key, chosen, source_sha)
    accepted_now = {r["worker"] for r in resolutions if r["key"] == key and r["hash"] == chosen_hash
                    and r["source_sha"] == source_sha}
    stale = sorted(set(blind) - set(fresh_blind) - accepted_now)
    if stale:
        problems = [*problems, f"{len(stale)} vote(s) for this spelling were not cast on the source as it reads "
                               "now; each of those voters accepts it with `resolve`"]
    if problems:
        print(f"name_lane: resolution pending: {'; '.join(problems)}")
        return 0
    agreed_name = chosen  # The reviewed spelling itself, never a donor respelling.
    rid = "nr-" + hashlib.sha256(f"{key}|{agreed_name}|{source_sha}".encode()).hexdigest()[:24]
    voters, _ = name_agreement.resolved_workers(original, lane.agreed_rows(), resolutions,
                                                 key, chosen, source_sha)
    row = dict(id=rid, kind=kind, old=old, new=agreed_name,
               rva=f"0x{rva:08X}" if rva is not None else "",
               agents=";".join(f"{worker}@{model}" for worker, model in sorted(voters.items())),
               key=key, status="agreed", detail="reviewed resolution: " + "; ".join(dict.fromkeys(
                   [r["reason"].strip() for r in resolutions if r["key"] == key and r["hash"] == chosen_hash
                    and r["source_sha"] == source_sha] or [args.reason.strip()])))
    if not any(r["id"] == rid for r in lane.agreed_rows()):
        lane.append(AGREED, AGREED_COLUMNS, [row])
    print(f"name_lane: RESOLVED {key} -> {agreed_name} ({len(voters)} original voters)")
    return 0


def apply_respell_batches(lane, todo, batches, bound, args, tally, refused, *, verify, checks, max_files):
    """Consume complete prepared groups, withholding every other bound key.

    The ordinary application/splitter never sees a registered key, including
    when its manifest disappeared or only one of its approvals is ready.
    """
    selected = {row["key"]: row for rows in todo.values() for row in rows if row["key"] in bound}
    for rel in list(todo):
        todo[rel] = [row for row in todo[rel] if row["key"] not in bound]
        if not todo[rel]:
            del todo[rel]
    landed = blocked = 0
    changed_sources = set()
    for ident in sorted({bound[key] for key in selected}):
        batch = batches[ident]
        if not set(batch["requests"]) <= set(selected):
            print("name_lane: prepared respell batch waiting for all current approvals and selection constraints.",
                  flush=True)
            continue
        rows = [selected[key] for key in batch["requests"]]
        try:
            prepared = _respell_inputs(lane, batch)
            requests = []
            for row in rows:
                key = row["key"]
                target = batch["requests"][key]
                if row["new"] != rename.split_function_name(target["new"])[1]:
                    raise rename.Refusal("prepared target identifier does not match the independent approval")
                requests.append(("function", dict(
                    rva=int(split_key(key)[2], 16), old=target["old"], new=target["new"], respell=True,
                    prepared=prepared, basis="inferred", evidence=f"agree:{row['id']}", max_files=max_files)))
            # source_edits makes a planner refusal abort the entire group.
            # No partial application or per-key retry is valid for this operation.
            result = rename.run_batch(lane.ctx, requests, claim=args.claim, verify=verify, checks=checks,
                                      source_edits=prepared)
            if result.failure is not None or result.refused or len(result.plans) != len(rows):
                detail = result.failure or "; ".join(str(v) for v in result.refused.values()) or "incomplete plan"
                raise rename.Refusal(str(detail))
            plans = [plan for _index, plan in result.plans]
            carry_verified_proposals(lane, plans)
            carry_verified_votes(lane, plans, rows)
            for row in rows:
                lane.append(AGREED, AGREED_COLUMNS, [dict(
                    row, status="landed", detail=approval_detail(tally, refused, row))])
            landed += len(rows)
            changed_sources.update(prepared)
        except (rename.Refusal, rename.VerifyFailed) as exc:
            # Leave the genuine naming approvals intact. A stale operation or
            # missing input never authorizes an identifier-only fallback.
            print(f"name_lane: prepared respell batch refused: {exc}", flush=True)
            blocked += len(rows)
        finally:
            lane.ctx._cache.clear()
    # Preparations may change more than spelling. Other approvals selected on
    # the old text need their normal fingerprint check in a fresh apply pass.
    for rel in changed_sources.intersection(todo):
        del todo[rel]
        print(f"name_lane: {rel}: other approvals left for a fresh source-fingerprint check.", flush=True)
    return landed, blocked


def cmd_apply(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    apply_started = time.perf_counter()
    limit = getattr(args, "limit", None)
    if limit is not None and limit < 1:
        fail("--limit must be positive")
    max_files = getattr(args, "max_files", 25)
    if max_files < 1:
        fail("--max-files must be positive")
    state, tally, refused = lane.state(), lane.tally(), lane.disputed()
    only = label_list(args.only_labels) if getattr(args, "only_labels", None) else None
    selected_keys = set(getattr(args, "key", None) or ())
    try:
        respells, respell_keys = respell_bindings(lane)
    except rename.Refusal as exc:
        fail(str(exc))
    # A newly approved key can complete a group whose other approvals were
    # waiting already. Selection must include its siblings, even for a fresh
    # reviewer process that was served only this last key.
    if selected_keys:
        for ident in {respell_keys[key] for key in selected_keys if key in respell_keys}:
            selected_keys.update(respells[ident]["requests"])
    fault = lane.grandfather_fault()
    if fault:           # before any write: with no exemption, every old record would be reopened
        print(f"name_lane: apply refused: {fault}")
        return 1
    if not selected_keys:
        report_grandfathered(lane, state)
        report_unrecorded(lane, lead=args.lead, min_models=args.min_models)
    grandfathered = lane.grandfathered()
    todo = collections.defaultdict(list)
    landed = blocked = stale = outside = selected = deferred = 0
    busy = None
    claim_deferred = 0
    blocker_deferred = 0
    blockers = _blockers(lane)
    blocker_removals = set()
    pending = False
    for key, row in state.items():
        if selected_keys and key not in selected_keys:
            continue
        if row["status"] == "agreed" or (args.retry_blocked and row["status"] == "blocked"):
            pending = True
            mine, rivals, _ = approval_support(tally, refused, row)
            if row["id"].startswith("nr-"):
                mine, valid = resolution_support(lane, row)
            else:
                valid = wins(mine, rivals, lead=args.lead, min_models=args.min_models, key=key)
            if only and not own_voters(mine, only):
                outside += 1
                continue
            if not valid:
                if row["id"].startswith("nr-"):
                    print(f"{key}: reviewed approval is no longer valid for this source and voter set; left")
                else:
                    print(f"{key}: votes no longer agree under --lead {args.lead} --min-models {args.min_models}; left")
                continue
            source_text = lane.text(split_key(key)[0])
            # A scoped record has its own route, and a placeholder that has gone is stale as before.
            if (not row["id"].startswith("nr-") and row["id"] not in grandfathered and source_text is not None
                    and not name_agreement.scoped_key(key)
                    and (spelled_key(key) or re.search(rf"\b{re.escape(row['old'])}\b", source_text))
                    and not wins(fresh_voters(lane, key, digest(key, row["new"]), mine, source_text), rivals,
                                 lead=args.lead, min_models=args.min_models, key=key)):
                print(f"{key}: {split_key(key)[0]} no longer reads as it did for the votes on {row['new']}; "
                      "reopened for fresh votes (status source-changed), nothing landed")
                lane.append(AGREED, AGREED_COLUMNS, [dict(row, agents="", status="source-changed",
                                                          detail="the source changed since its votes")])
                continue
            if spelled_key(key):
                print(f"{key}: agreed {row['new']}; land it with tools/rename.py function --rva {scope_rva(key)} "
                      f"--new NEW --respell --identity --prepared ... --basis inferred --evidence agree:{row['id']}")
                continue
            if unrowed_key(key):
                print(f"{key}: agreed {row['new']}; define it in {split_key(key)[0]}, then run "
                      f"python3 tools/data_rows.py --admit-agreed {row['id']} --symbol COFF_SYMBOL --model MODEL")
                continue
            if (row["status"] == "blocked" and args.retry_blocked
                    and not getattr(args, "retry_unchanged", False)
                    and _same_blocker(lane, key, row, blockers, max_files=max_files)):
                blocker_deferred += 1
                saved = blockers[key]
                print(f"{key}: skipped unchanged blocker: {saved.get('detail', 'inputs unchanged')}", flush=True)
                continue
            if key in blockers:
                blockers.pop(key, None)
                blocker_removals.add(key)
            if args.claim:
                if busy is None:
                    busy = claims.busy_keys(lane.root)
                if approval_claim_keys(row) & busy:
                    claim_deferred += 1
                    print(f"{key}: deferred: held by another worker; approval unchanged", flush=True)
                    continue
            if limit is not None and selected >= limit:
                deferred += 1
                continue
            selected += 1
            agents = ";".join(f"{w}@{m}" for w, m in sorted(mine.items()))
            todo[split_key(key)[0]].append(dict(row, agents=agents))
    if blocker_removals:
        _save_blockers(lane, {}, remove=blocker_removals)
    if not pending:
        print("name_lane: nothing agreed is waiting to land.")
        return 0
    prepared_landed, prepared_blocked = apply_respell_batches(
        lane, todo, respells, respell_keys, args, tally, refused,
        verify=verify, checks=checks, max_files=max_files)
    landed += prepared_landed
    blocked += prepared_blocked
    print(f"name_lane: selected {sum(map(len, todo.values()))} key(s) across {len(todo)} file(s).", flush=True)
    print(f"name_lane: apply selection {time.perf_counter() - apply_started:.3f}s", flush=True)
    if not todo:
        file_groups = []
    elif not getattr(args, "no_batch", False) and not getattr(args, "per_file", False):
        ordinary_landed, ordinary_blocked, stale = _apply_run(lane, todo, args, tally, refused,
                                                            verify=verify, checks=checks, max_files=max_files)
        landed += ordinary_landed
        blocked += ordinary_blocked
        file_groups = []
    else:
        file_groups = sorted(todo.items())
    for rel, rows in file_groups:
        text = lane.text(rel)
        live = {key_of(rel, k, s, i) for k, s, i, _ in
                lane.owned(rel, text, kinds={r["kind"] for r in rows})} if text is not None \
            and lane.servable(rel) else set()
        ordered = sorted(rows, key=lambda r: LAND_ORDER[r["kind"]])
        scoped = [r for r in ordered if r["kind"] in ("param", "local") and r["key"] in live]
        members = [r for r in ordered if r["kind"] == "member" and r["key"] in live]
        batched = set()
        batch_attempted = getattr(args, "no_batch", False)
        member_batch_attempted = getattr(args, "no_batch", False)
        for row in ordered:
            key = row["key"]
            if key in batched:
                continue
            _, kind, scope, ident = split_key(key)
            if not member_batch_attempted and kind == "member" and len(members) > 1:
                member_batch_attempted = True
                requests = []
                for candidate in members:
                    _, _kind, candidate_scope, old = split_key(candidate["key"])
                    requests.append(dict(source=rel, cls=candidate_scope, member=old, new=candidate["new"],
                                         basis="inferred", evidence=f"agree:{candidate['id']}",
                                         max_files=max_files))
                try:
                    rename.run_member_batch(lane.ctx, requests, claim=args.claim, verify=verify, checks=checks)
                except (rename.Refusal, rename.VerifyFailed) as exc:
                    print(f"name_lane: member batch refused ({exc}); retrying individually.", flush=True)
                else:
                    for candidate in members:
                        lane.append(AGREED, AGREED_COLUMNS, [dict(
                            candidate, status="landed", detail=approval_detail(tally, refused, candidate))])
                        batched.add(candidate["key"])
                    landed += len(members)
                    if key in batched:
                        continue
            if not batch_attempted and kind in ("param", "local") and len(scoped) > 1:
                batch_attempted = True
                requests = []
                for candidate in scoped:
                    _, k, s, old = split_key(candidate["key"])
                    requests.append((k, dict(basis="inferred", evidence=f"agree:{candidate['id']}", max_files=max_files,
                                            **rename_kwargs(k, s, old, candidate["new"], candidate["rva"], rel, lane))))
                try:
                    rename.run_scoped_batch(lane.ctx, requests, claim=args.claim, verify=verify, checks=checks)
                except (rename.Refusal, rename.VerifyFailed) as exc:
                    print(f"name_lane: scoped batch refused ({exc}); retrying individually.", flush=True)
                else:
                    for candidate in scoped:
                        lane.append(AGREED, AGREED_COLUMNS, [dict(candidate, status="landed",
                                    detail=approval_detail(tally, refused, candidate))])
                        batched.add(candidate["key"])
                    landed += len(scoped)
                    if key in batched:
                        continue
            outcome = dict(row, detail="")
            if key not in live:
                outcome.update(status="stale", agents="", detail="the file changed or the placeholder is gone")
                stale += 1
            else:
                try:
                    rename.run(kind, lane.ctx, claim=args.claim, verify=verify, checks=checks,
                               basis="inferred", evidence=f"agree:{row['id']}", max_files=max_files,
                               **rename_kwargs(kind, scope, ident, row["new"], row["rva"], rel, lane))
                    outcome.update(status="landed", detail=approval_detail(tally, refused, row))
                    landed += 1
                except (rename.Refusal, rename.VerifyFailed) as exc:
                    outcome.update(status="blocked", detail=" ".join(str(exc).split())[:300])
                    blocked += 1
                    print(f"{key}: blocked: {outcome['detail']}")
                lane.ctx._cache.clear()
            lane.append(AGREED, AGREED_COLUMNS, [outcome])
    print(f"name_lane: landed {landed}, blocked {blocked}, stale {stale}. Stage the files rename.py listed "
          f"and {AGREED} and {VOTE_SOURCES} (plus {MEANINGS} when structured votes added it), in one commit; "
          "the lander commits.")
    print(f"name_lane: apply total {time.perf_counter() - apply_started:.3f}s", flush=True)
    if deferred:
        print(f"name_lane: {deferred} ready key(s) left waiting by --limit {limit}; run apply again to continue.")
    if claim_deferred:
        print(f"name_lane: {claim_deferred} ready key(s) deferred for other workers' claims; "
              "run apply again after the claims are released.")
    if blocker_deferred:
        print(f"name_lane: skipped {blocker_deferred} unchanged blocker(s); retry after their source or tools change.")
    if only:
        print(f"name_lane: --only-labels {','.join(sorted(only))}: {outside} key(s) with a voter outside those "
              "labels left untouched.")
    return 0


def cmd_dispute(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    """Put landed names back through rename.revert -- the engine's own exact
    inverse of the recorded inferred rename -- then record the dispute, which
    refuses the spelling for the key from then on."""
    state = lane.state()
    for key in args.keys:
        if key not in state or state[key]["status"] != "landed":
            fail(f"{key}: no landed name to dispute")
    reason = " ".join(args.reason.split())
    if not reason:
        fail("--reason must say what the code shows against the landed name")
    failed = 0
    for key in sorted(args.keys, key=lambda k: -LAND_ORDER[split_key(k)[1]]):
        row = state[key]
        _, kind, scope, ident = split_key(key)
        try:
            rename.revert(lane.ctx, row["id"], reason, claim=args.claim, verify=verify, checks=checks,
                          function=scope if kind in ("param", "local") else None)
        except (rename.Refusal, rename.VerifyFailed) as exc:
            print(f"{key}: could not put {ident} back: {' '.join(str(exc).split())[:300]}")
            failed += 1
            continue
        finally:
            lane.ctx._cache.clear()
        lane.append(AGREED, AGREED_COLUMNS, [dict(row, agents="", status="disputed",
                                                  detail=f"{reason} (was agreed by {row['agents']})")])
        print(f"{key}: {row['new']} put back to {ident}; {row['new']} is refused for it from now on")
    return 1 if failed else 0


# ---------------------------------------------------------- reconciliation handoff

def cmd_reconcile(lane, args):
    """Describe blocked class identity work; never infer identity or edit source."""
    selected = set(getattr(args, "key", None) or ())
    registry = {r.get("class"): r.get("header", "")
                for r in lane.ctx.dicts(rename.CANONICAL_CLASSES)}
    packets = []
    for key, row in sorted(lane.state().items()):
        if selected and key not in selected:
            continue
        if row["kind"] != "class" or row["status"] not in ("blocked", "agreed"):
            continue
        rel, _kind, _scope, old = split_key(key)
        new = row["new"]
        views = lane.type_definers(new)
        header = registry.get(new, "")
        if not views and not header:
            continue
        def snapshot(path, word):
            text = lane.text(path) or ""
            code = name_metric.strip(text)
            declarations = []
            for match in name_metric.DECL.finditer(code):
                if match.group(1) == word:
                    end = name_metric.close(code, match.end() - 1)
                    declarations.append(text[match.start():end + 1])
            return dict(path=path, sha256=hashlib.sha256(text.encode(
                "utf-8", "surrogateescape")).hexdigest(), declarations=declarations)
        contract = f"{rename.CLASS_CONTRACTS}/{new}.json"
        packets.append(dict(key=key, proposed_type=new, status="identity-review-required",
                            blocker=row.get("detail", ""), registered_header=header,
                            contract=contract if lane.path(contract).is_file() else "",
                            private_view=snapshot(rel, old),
                            existing_views=[snapshot(path, new) for path in sorted(set(views + ([header] if header else [])))],
                            next_steps=[
                                "Prove type identity from uses and target evidence; equal fields or a vote do not prove identity.",
                                "Compare layout, bases, ABI, constructors and methods against the registered contract.",
                                f"Inspect competing views: python3 tools/class_views.py --class {new}",
                                "Claim the source and reconcile declarations in a separate source commit.",
                                "Run byte verification and affected-consumer link checks; record inferred naming separately."] ))
    print(json.dumps(packets, indent=2))
    return 0


# ---------------------------------------------------------------- status

def cmd_status(lane, args):
    votes, state = lane.votes(), lane.state()
    count = collections.Counter(r["status"] for r in state.values())
    sessions = {v.get("worker") for v in votes}
    models = collections.Counter(v["model"] for v in votes)
    print(f"votes: {len(votes):,} from {len(sessions)} worker(s) ({', '.join(f'{m} {n}' for m, n in models.most_common())})")
    print(f"keys voted: {len({v['key'] for v in votes}):,}; agreed: {len(state)} (landed {count['landed']}, "
          f"waiting {count['agreed']}, blocked {count['blocked']}, stale {count['stale']}, "
          f"disputed {count['disputed']})")
    if count["source-changed"]:
        print(f"name_lane: {count['source-changed']} record(s) reopened because their source changed since the votes; "
              "each needs fresh votes")
    report_grandfathered(lane, state)
    report_unsettled(lane, state)
    report_unrecorded(lane, lead=args.lead, min_models=args.min_models)
    import name_review
    problem = name_review.runtime_problem(lane)
    if problem:
        print(f"name_lane: {problem}")
    if getattr(args, "only_labels", None):
        only, tally, refused = label_list(args.only_labels), lane.tally(), lane.disputed()
        picked = 0
        for key, row in state.items():
            if row["status"] != "agreed":
                continue
            mine, rivals, _ = approval_support(tally, refused, row)
            if row["id"].startswith("nr-"):
                mine, valid = resolution_support(lane, row)
            else:
                valid = wins(mine, rivals, lead=args.lead, min_models=args.min_models, key=key)
            picked += valid and own_voters(mine, only)
        print(f"--only-labels {','.join(sorted(only))}: apply would select {picked} of {count['agreed']} "
              f"waiting key(s) (--lead {args.lead} --min-models {args.min_models})")
    if args.metric:
        names, bad = name_metric.readable()
        print(f"Readable names: {100 * (1 - bad / names):.2f}% ({names - bad:,} of {names:,}); placeholders {bad:,}")
    return 0


def main(argv=None, lane=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    request = sub.add_parser('register-data', help='register an unrowed retail data range for blind global naming')
    request.add_argument('--source', required=True)
    request.add_argument('--address', required=True)
    request.add_argument('--address-kind', choices=('va', 'rva'), required=True)
    request.add_argument('--size', type=lambda v: int(v, 0), required=True)
    request.add_argument('--type', dest='type_name', required=True)
    request.add_argument('--users', nargs='+', required=True)
    request.add_argument('--evidence', required=True)
    n = sub.add_parser("next", help="serve only function, class, member and global names for voting")
    n.add_argument("--session", required=True, help="a label for this brief; who votes is the worker identity, not this")
    n.add_argument("--model", required=True, help="the label you vote under, e.g. seat-a")
    n.add_argument("--count", type=int, default=1, help="serve this many files")
    n.add_argument("--file", help="serve this file instead of the next in the queue")
    n.add_argument("--registered", metavar="CLASS",
                   help="serve the class and placeholder member keys of this placeholder class "
                        "registered in reverse/canonical_classes.csv, from its canonical header")
    n.add_argument("--files", nargs="+", metavar="SOURCE",
                   help="serve these explicit source files in one packet and one claim snapshot")
    n.add_argument("--subsystem", metavar="CODE_PREFIX",
                   help="restrict to this source/approved-TU directory; one subsystem per batch")
    n.add_argument("--mixed", action="store_true", help="retain the shuffled multi-subsystem queue")
    n.add_argument("--key", action="append", help="serve only this exact source|kind|scope|placeholder key")
    n.add_argument("--max-keys", type=int, help="maximum keys in the entire served batch")
    n.add_argument("--max-chars", type=int, help="maximum JSON review packet size across the served sources")
    n.add_argument("--review-only", action="store_true", help="serve only shared names needing a different second voter")
    n.add_argument("--meaning-review-only", action="store_true", help="retired scoped vote path; redirects to scoped next")
    n.add_argument("--list-only", action="store_true",
                   help="print the queue's file/size/kind metadata as JSON; no session, no brief")
    s = sub.add_parser("submit", help="record shared-name proposals and apply approvals; scoped votes are refused")
    s.add_argument("answer")
    s.add_argument("--session", required=True)
    s.add_argument("--model", required=True)
    s.set_defaults(auto_workflow=True)
    submit_mode = s.add_mutually_exclusive_group()
    submit_mode.add_argument("--apply-ready", type=int, metavar="N",
                             help="cap immediate application at N newly approved keys; default applies all new approvals")
    submit_mode.add_argument("--propose-only", action="store_true",
                             help="record proposals without applying names or dispatching an automatic reviewer")
    s.add_argument("--respell-batch", metavar="MANIFEST",
                   help="bind served ordinary-function keys to an atomic prepared respell manifest under build/")
    s.add_argument("--no-auto-review", action="store_true",
                   help="apply ready names but do not dispatch an automatic reviewer")
    s.add_argument("--max-files", type=int, default=25, help="maximum affected sources per rename plan")
    v = sub.add_parser("validate", help="check proposals before voting; leave the session and ledgers intact")
    v.add_argument("answer")
    v.add_argument("--session", required=True)
    v.add_argument("--model", required=True)
    v.add_argument("--report", help="local JSON rejection report (default build/name_lane/validation/SESSION.json)")
    v.add_argument("--respell-batch", metavar="MANIFEST",
                   help="validate a prepared respell binding without registering it or recording votes")
    for p in (s,):
        p.add_argument("--lead", type=int, default=2, help="votes the name must lead every rival by")
        p.add_argument("--min-models", type=int, default=1, help="distinct models among the agreeing workers")
    a = sub.add_parser("apply", help="land agreed names through tools/rename.py")
    a.add_argument("--limit", type=int, metavar="N", help="attempt at most N eligible approvals, leaving the rest waiting")
    a.add_argument("--retry-blocked", action="store_true", help="try blocked names again, e.g. after a fix")
    a.add_argument("--retry-unchanged", action="store_true", help="ignore saved failure fingerprints with --retry-blocked")
    a.add_argument("--key", action="append", help="apply only this exact source|kind|scope|placeholder key (repeatable)")
    a.add_argument("--max-files", type=int, default=25, help="maximum affected sources; every selected source is still verified")
    a.add_argument("--no-batch", action="store_true",
                   help="verify each rename separately")
    a.add_argument("--per-file", action="store_true",
                   help="batch within each source instead of across the whole run")
    a.add_argument("--lead", type=int, default=2)
    a.add_argument("--min-models", type=int, default=1)
    a.add_argument("--only-labels", metavar="L,L",
                   help="land only keys whose winning spelling was voted entirely under these --model labels")
    a.add_argument("--no-claim", dest="claim", action="store_false", help="do not take tools/claims.py claims")
    resolution = sub.add_parser("resolve", help="an original voter accepts a name after comparing competing proposals")
    resolution.add_argument("--key", required=True, help="exact source|kind|scope|placeholder key")
    resolution.add_argument("--name", required=True, help="selected name (an original proposal or a replacement)")
    resolution.add_argument("--reason", required=True, help="source-based reason for the selected spelling")
    d = sub.add_parser("dispute", help="put landed names back and refuse them for their keys")
    d.add_argument("keys", nargs="+", help="as name_agreed.csv spells them (source|kind|scope|placeholder)")
    d.add_argument("--reason", required=True, help="what the code shows against the landed name")
    d.add_argument("--no-claim", dest="claim", action="store_false")
    concord = sub.add_parser("agree", help="record an agreement the votes have already reached; adds no vote")
    concord.add_argument("--key", required=True, help="source|kind|scope|placeholder, as status prints it")
    concord.add_argument("--name", required=True, help="the spelling the voters proposed")
    concord.add_argument("--lead", type=int, default=2)
    concord.add_argument("--min-models", type=int, default=1)
    st = sub.add_parser("status", help="votes and agreement counts")
    st.add_argument("--metric", action="store_true", help="also the tree-wide readable-name metric (slow)")
    st.add_argument("--only-labels", metavar="L,L", help="count the waiting keys apply --only-labels would select")
    st.add_argument("--lead", type=int, default=2, help="with --only-labels: the lead apply would use")
    st.add_argument("--min-models", type=int, default=1, help="with --only-labels: the min-models apply would use")
    reconcile = sub.add_parser("reconcile", help="report existing-type collisions for evidence-backed reconciliation; edits nothing")
    reconcile.add_argument("--key", action="append", help="select an exact pending class key (repeatable)")
    import name_review
    review = sub.add_parser("review", help="configure or run bounded automatic blind second reviews")
    name_review.configure_parser(review)
    placement = sub.add_parser("consolidate", help="build original-file evidence and consolidation packets; applies nothing")
    import source_layout
    source_layout.configure_parser(placement)
    scoped = sub.add_parser("scoped", help="whole-function locals/parameters: child proposes, parent scans, one verified batch")
    import name_scoped
    name_scoped.configure_parser(scoped)
    args = ap.parse_args(argv)
    if args.cmd == "consolidate":
        try:
            return source_layout.run(args, root=lane.root if lane else ROOT)
        except (ValueError, OSError) as exc:
            ap.exit(2, f"source-layout: {exc}\n")
    lane = lane or Lane()
    if args.cmd == "scoped":
        try:
            return name_scoped.run(lane, args)
        except (ValueError, OSError, rename.Refusal) as exc:
            print(f"name_lane: scoped batch failed: {exc}", file=sys.stderr)
            return 2
    if args.cmd == "review":
        try:
            return name_review.run(lane, args)
        except (name_review.ReviewError, OSError, ValueError) as exc:
            print(f"name_lane: reviewer failed: {exc}", file=sys.stderr)
            return 2
    if args.cmd == 'register-data':
        try:
            key = register_data(lane, source=args.source, address=args.address, address_kind=args.address_kind,
                                size=args.size, type_name=args.type_name, users=args.users, evidence=args.evidence)
        except (rename.Refusal, ValueError) as exc:
            fail(str(exc))
        print(key)
        print(f"Stage {DATA_REQUESTS}; then: python3 tools/name_lane.py next --file {args.source} --key '{key}' --session SESSION --model MODEL")
        return 0
    if args.cmd == "next":
        return cmd_next(lane, args)
    if args.cmd == "submit":
        return cmd_submit(lane, args, lead=args.lead, min_models=args.min_models)
    if args.cmd == "validate":
        return cmd_validate(lane, args)
    if args.cmd == "apply":
        return cmd_apply(lane, args)
    if args.cmd == "resolve":
        return cmd_resolve(lane, args)
    if args.cmd == "agree":
        return cmd_agree(lane, args)
    if args.cmd == "reconcile":
        return cmd_reconcile(lane, args)
    if args.cmd == "dispute":
        return cmd_dispute(lane, args)
    return cmd_status(lane, args)


if __name__ == "__main__":
    sys.exit(main())
