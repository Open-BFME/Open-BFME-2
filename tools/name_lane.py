#!/usr/bin/env python3
"""The inferred-name lane: one uncontested proposal for parameters/locals;
two independent blind proposals for other names or contested scoped names.

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

    python3 tools/name_lane.py next --session S --model M [--count N] [--subsystem Code/...] [--file F] [--list-only]
    python3 tools/name_lane.py submit ANSWER.json --session S --model M
    python3 tools/name_lane.py apply [--retry-blocked] [--lead 2] [--min-models 1] [--only-labels L,L]
    python3 tools/name_lane.py dispute KEY... --reason TEXT
    python3 tools/name_lane.py status [--only-labels L,L] [--lead 2] [--min-models 1]

`next` serves matched, non-generated Code/ sources from one subsystem, with
shared existing-source context. Each file decides only its own identifiers --
functions it owns rows for, classes only it
defines, their used members, parameters and locals (locals only where the unit
compiles optimised: under /Od a local's name can reorder the frame), and file
globals it owns data rows for -- that are placeholder or weak
(tools/name_metric.py's definition, which tools/rename.py shares), except a
weak parameter spelling (a, b, tmp) that the donor trees' own declaration of
that function uses -- the original programmer's, not a converter's. It writes a
brief to build/name_lane/briefs/<session>.txt: the fixed style rules, the keys
to answer, the file's text, callers spelling its functions, the retail strings
its rows reference and tools/name_evidence.py hints. A skip costs nothing; a
wrong name misleads readers.

`submit` stores each vote only as sha256(key|canon(name))[:24] in
reverse/name_votes.csv (append-only). canon() folds word order, plurals and
common abbreviations, so m_ladderComboBox and m_comboBoxLadder are one vote,
and names requiring blind agreement stay hidden until a second worker matches.
An uncontested parameter/local proposal may enter its approval record at once.
Every vote and every served session
record carries the voter's worker identity (tools/name_agreement.py: hashed
BFME_CLAIM_OWNER / BFME_RUN_ID, else CLAUDE_CODE_SESSION_ID, else
tools/claims.py's owner), read from the environment rather than from
`--session`, which is only a label: `submit` refuses a session `next` served
to another worker, a worker votes once per key whatever label it uses, and
agreement counts distinct workers. An orchestrator running blind seats gives
each its own BFME_CLAIM_OWNER, as it already does for claims. When a vote
makes a name win (one uncontested scoped proposal, otherwise two distinct
workers with a lead of `--lead` votes over every rival spelling, optionally
`--min-models` distinct models under either policy; files another
model voted on are served first), the name is written to
reverse/name_agreed.csv as `agreed`.

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

Eligible parameter/local renames in the same file share one transaction,
claim operation, build and set of ledger checks. A failed batch is restored
and retried individually. `apply --no-batch` retains per-name verification.

`apply` lands every waiting key whose votes win, including agreements that
only other contributors' voters reached. `apply --only-labels seat-a,seat-b`
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
import random
import re
import subprocess
import sys
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
LANE_DIR = "build/name_lane"
EVIDENCE_TSV = "build/name_evidence.tsv"
MAX_CHARS = 15000
KINDS = ("function", "class", "member", "param", "local", "global")
NAMED = ("class", "member", "function", "global")
# rename order inside one file: a member's key names its class and a param's
# key names its function, so those land before the class or function moves
LAND_ORDER = {"member": 0, "param": 1, "local": 1, "global": 2, "function": 3, "class": 4}
FAMILY = re.compile(r"(?:a|d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]+")
GENERIC = {"data", "info", "value", "temp", "tmp", "helper", "thing", "stuff", "foo", "bar", "obj", "var", "func",
           "method", "unknown", "misc", "item", "object", "result", "ret", "field", "member", "param", "arg", "local"}
DIRECTIVE = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
MACRO = re.compile(r"^[ \t]*#[ \t]*(?:define|undef)[ \t]+([A-Za-z_]\w*)", re.M)
STATUS_RANK = {"agreed": 0, "stale": 1, "blocked": 2, "landed": 3, "disputed": 4}


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


def approval_support(tally, refused, row):
    return name_agreement.support(tally, refused, row["key"], row["new"],
                                  name_agreement.record_meaning(row["id"]))


def approval_detail(tally, refused, row):
    mine, rivals, meaning = approval_support(tally, refused, row)
    return ("meaning agreement; " if meaning else "") + name_agreement.review_detail(row["key"], mine, rivals)


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

class Lane:
    """The lane's view of one tree; tests point it at a miniature repository."""

    def __init__(self, root=ROOT, ctx=None):
        self.root = Path(root).resolve()
        self.ctx = ctx or rename.Context(self.root, object_scan=self.root == ROOT.resolve())
        self._types = {}
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
            best = rows[0]
            for row in rows[1:]:
                if STATUS_RANK.get(row["status"], -1) >= STATUS_RANK.get(best["status"], -1):
                    best = row
            out[key] = best
        return out

    def disputed(self):
        """key -> canon spellings refused for it."""
        return name_agreement.disputed(self.agreed_rows())

    def tally(self):
        """key -> hash -> {worker: model}: distinct workers, not session labels."""
        return name_agreement.tally(self.votes(), self.table(MEANINGS, MEANING_COLUMNS))

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
        """RVAs another lane names: a WorldBuilder lead, an evidence-tier name or a
        canonical name_evidence candidate (rename.py refuses an inferred name there)."""
        if "_named_rvas" not in self.ctx._cache:
            out = {rename._rva(r.get("rva") or r.get("target_rva")) for r in self.ctx.dicts(rename.WB_LEADS)}
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
        old = ident
        if kind == "function":
            old = next((r["name"] for r in self.ledger().get(rel, ())
                        if rename._rva(r.get("target_rva")) == rva), ident)
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

    def servable(self, rel):
        """A matched, hand-written Code/ C/C++ unit with no vendored, export or .lib row."""
        rows = self.ledger().get(rel, [])
        if not rows or not rel.startswith("Code/") or not rel.endswith((".cpp", ".c")):
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
        if wanted is None or not wanted <= {"param", "local"}:
            decls = list(name_metric.DECL.finditer(code))
            for t in dict.fromkeys(m.group(1) for m in decls):
                if name_metric.placeholder(t) and self.type_definers(t) in ([], [rel]):
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
                # (Object's 13 private copies) is renamed across all of them, not decided here
                if (len(classes) == 1 and name_metric.placeholder(name) and not name_metric.PAD.match(name)
                        and len(re.findall(rf"\b{re.escape(name)}\b", code)) > 1     # used, so not padding
                        and self.type_definers(next(iter(classes))) in ([], [rel])):
                    items.append(("member", next(iter(classes)), name, None))
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
        seen, out = set(), []
        for kind, scope, ident, rva in items:
            slot = (scope, ident) if kind in ("param", "local") else ident
            if slot not in seen:
                seen.add(slot)
                if wanted is None or kind in wanted:
                    out.append((kind, scope, ident, rva))
        return out

    # ------------------------------------------------------------ refusals

    def problem(self, kind, old, new, file_words):
        """Why `new` may not be voted for `old`, or None (BFME 1's problem())."""
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
        if kind in NAMED and new in file_words:
            return "collides with a name already in the file"
        return None


def base(scope):
    """The function word of a param's or local's scope (Class::method#2 -> method)."""
    return scope.split("#")[0].split("::")[-1]


def key_of(rel, kind, scope, ident):
    return f"{rel}|{kind}|{scope}|{ident}"


def split_key(key):
    rel, kind, scope, ident = key.split("|")
    return rel, kind, scope, ident


def needs_review(key, state, tally, refused):
    """Reopen a pending scoped approval when a late rival removes its quorum."""
    row = state.get(key)
    if row is None or row["status"] == "disputed":
        return True
    if row["status"] != "agreed" or split_key(key)[1] not in ("param", "local"):
        return False
    mine, rivals, _ = approval_support(tally, refused, row)
    return not wins(mine, rivals, key=key)


def answer_key(kind, scope, ident):
    if kind in ("param", "local"):
        return f"{scope}:{ident}"
    if kind == "member":
        return f"{scope}::{ident}"
    return ident


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
        rel = v["key"].split("|")[0]
        voted_sessions[rel].add(v.get("worker") or "")
        voted_models[rel].add(v["model"])
    files = [only] if only else [f for f in lane.ledger() if f.endswith((".cpp", ".c"))]
    reviews = reviews or {}
    clarifications = clarifications or {}
    files = [f for f in files if worker not in voted_sessions[f] or reviews.get(f) or clarifications.get(f)]
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

    listing = "\n".join(f"  {answer_key(k, s, i):44} {k:8} {declared_at(i, s if k in ('param', 'local') else None)}"
                        for k, s, i, _ in items)
    evidence = []
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
    return f"""NAME THE PLACEHOLDERS IN {rel}  (session {session}, model {model})
{"INDEPENDENT SECOND REVIEW: only the shared identifiers awaiting another worker are served; previous proposals remain hidden." if review else ""}
{"MEANING CLARIFICATION: resubmit your original normalized spelling with a justified structured meaning. This annotates your existing vote; it never adds a voter or permits changing that vote." if meaning_review else ""}

This is decompiled BFME 2 (SAGE engine) C++. A converter invented the names
below from addresses, offsets or decompiler slots. Give each the name its
original EA programmer most likely used, judging from what the code does and
the evidence. Style (fixed): types CamelCase, members m_camelCase, params and
locals camelCase, functions and methods camelCase unless the class already
uses CamelCase. Answer "skip" when you cannot justify a name: a skip costs
nothing, a wrong name misleads readers. An uncontested parameter/local name
can land from your one proposal. Other names and competing scoped proposals
need independent blind agreement. Your proposal must be your own: do not take
names from, or show yours to, another model or session.
Write your answer with a file-writing tool, never inline in a shell command
(other sessions can read command lines). If a stand-in type IS a real class
that a game or Zero Hour header declares, answer that class's name.

Write a JSON object mapping each key below to a name or "skip", then run:
  python3 tools/name_lane.py submit <that file> --session {session} --model {model}

For a parameter/local, first identify its role before choosing a spelling.
When that role is justified, prefer {{"name":"destination","meaning":
{{"role":"destination","entity":"buffer","units":"bytes","ownership":"borrowed"}}}}.
Use the code's role, a specific snake_case entity, units and ownership; see
docs/naming.md for allowed values. Classify independently, never from another
worker's proposal. Identical role descriptors can agree despite different
spellings. Conflicting roles/units/ownership remain competing votes. Omit the
structured form or skip if you cannot justify its meaning.

{listing}

--- {rel}
{text}
--- evidence (callers, retail strings, tools/name_evidence.py hints)
""" + ("\n".join(evidence) or "  (none)") + "\n"


@claims.pick_snapshot()
def cmd_next(lane, args):
    session, model = session_id(args.session), model_id(args.model)
    worker = lane.worker()
    state = lane.state()
    tally, refused = lane.tally(), lane.disputed()
    reviews = second_reviews(worker, state, tally, refused)
    clarifications = meaning_reviews(worker, state, tally, refused)
    files, voted = queue(lane, worker, model, args.file, reviews=reviews, clarifications=clarifications)
    only_meaning = getattr(args, "meaning_review_only", False)
    if only_meaning and getattr(args, "review_only", False):
        fail("--review-only and --meaning-review-only cannot be combined")
    served, metadata = [], []
    record = lane.path(f"{LANE_DIR}/sessions/{session}.json")
    current = json.loads(record.read_text()) if record.exists() else {"model": model, "worker": worker, "files": {}}
    if current.get("worker") != worker and not args.list_only:
        fail(f"session {session} belongs to another worker; pick a session label of your own")
    mixed = getattr(args, "mixed", False)
    prefix = subsystem_prefix(args.subsystem) if getattr(args, "subsystem", None) else None
    if mixed and prefix:
        fail("--mixed and --subsystem cannot be combined")
    # One shared snapshot for the whole pick. The standard footprint expands
    # RVA/class claims and persisted locks to files, excluding our own claims
    # but retaining foreign namespaces and mirrors. Do this before choosing a
    # subsystem or scanning bodies so busy files cannot anchor/waste a batch.
    busy = claims.busy_keys(lane.root)
    available = [rel for rel in files if claims.file_key(rel) not in busy]
    skipped = len(files) - len(available)
    if skipped:
        print(f"name_lane: skipped {skipped} source file(s) held by other workers", file=sys.stderr)
    files = available
    sticky = lane.path(f"{LANE_DIR}/subsystems/{worker}.json")
    preferred = current.get("subsystem")
    if not mixed and not prefix and not args.file:
        if not preferred and sticky.exists():
            preferred = subsystem_prefix(json.loads(sticky.read_text())["subsystem"])
        if preferred:
            files.sort(key=lambda f: (not reviews.get(f), not clarifications.get(f),
                                      lane.subsystem(f)[0] != preferred))
    selected = None
    selected_review = None
    selected_meaning = None
    for rel in files:
        group, basis = lane.subsystem(rel) if not mixed else (None, "mixed")
        if prefix and not (under(group, prefix) or under(rel, prefix)):
            if args.file:
                fail(f"{rel} is outside subsystem {prefix}")
            continue
        if not mixed and selected is not None and group != selected:
            continue
        if rel in current["files"] or not lane.servable(rel):
            continue
        text = lane.text(rel)
        if text is None or len(text) > MAX_CHARS:
            continue
        items = [i for i in lane.owned(rel, text)
                 if needs_review(key_of(rel, *i[:3]), state, tally, refused)
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
        if len(items) < (1 if voted[rel] or args.file else 3):      # an asked-for file needs one key
            continue
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
        if len(served) + len(metadata) >= args.count:
            break
    if args.list_only:
        print(json.dumps(metadata, indent=1))
        return 0
    if not served:
        print(f"name_lane: no file is left for session {session} to name.")
        return 0
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
    out.write_text(context + "\n\n" + "\n\n".join(
                       brief_text(lane, rel, text, items, session, model,
                                  review=current["files"][rel].get("second_review", False),
                                  meaning_review=current["files"][rel].get("meaning_review", False))
                       for rel, text, items in served),
                   encoding="utf-8", errors="surrogateescape")
    print(f"name_lane: brief for {len(served)} file(s) ({sum(len(i) for _, _, i in served)} keys): {out}")
    if len(served) > 1:
        print("name_lane: answer {\"<file>\": {<key>: <name>|\"skip\"}, ...} for several files")
    return 0


# ---------------------------------------------------------------- submit

def cmd_submit(lane, args, *, lead=2, min_models=1, verify=rename.build_verify, checks=rename.ledger_checks):
    apply_ready = getattr(args, "apply_ready", None)
    if apply_ready is not None and (apply_ready < 1 or getattr(args, "max_files", 25) < 1):
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
    answers = json.loads(Path(args.answer).read_text(encoding="utf-8"))
    files = served["files"]
    if len(files) == 1 and not any(k in files for k in answers):
        answers = {next(iter(files)): answers}
    unknown = set(answers) - set(files)
    if unknown:
        fail(f"files not served to session {session}: {', '.join(sorted(unknown)[:4])}")
    prior_votes = lane.votes()
    tally, state, refused = lane.tally(), lane.state(), lane.disputed()
    now = datetime.date.today().isoformat()
    votes, meanings, agreed, rejected = [], [], [], []
    for rel, mapping in answers.items():
        entry = files[rel]
        text = lane.text(rel) or ""
        if hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest() != entry["sha"]:
            rejected.append(f"{rel}: changed since `next` served it; run `next` again")
            continue
        items = [tuple(i) for i in entry["items"]]
        unknown = set(mapping) - {answer_key(k, s, i) for k, s, i, _ in items}
        if unknown:
            fail(f"keys not served for {rel}: {', '.join(sorted(unknown)[:8])}")
        file_words, taken = set(name_metric.WORD.findall(name_metric.strip(text))), set()
        for kind, scope, ident, rva in items:
            proposal = mapping.get(answer_key(kind, scope, ident), "skip")
            meaning = None
            if isinstance(proposal, dict):
                try:
                    if set(proposal) != {"name", "meaning"}:
                        raise ValueError("structured answers need exactly name and meaning")
                    meaning = name_agreement.meaning_digest(key_of(rel, kind, scope, ident), proposal["meaning"])
                    proposal = proposal["name"]
                except (ValueError, TypeError) as exc:
                    rejected.append(f"{answer_key(kind, scope, ident)}: {exc}")
                    continue
            answer = str(proposal).strip()
            if answer.lower() == "skip":
                continue
            key = key_of(rel, kind, scope, ident)
            h = digest(key, answer)
            already = worker in {w for v in tally[key].values() for w in v}
            annotate = (already and meaning and worker in tally[key].get(h, {})
                        and not tally.meanings[key].get((h, worker)))
            why = lane.eligibility(rel, kind, scope, ident, rva) or lane.problem(kind, ident, answer, file_words)
            if not why and kind == "class" and lane.ctx.grep_files(answer, word=True):
                why = f"{answer} already exists; reconcile declarations before a class rename"
            if not why and kind in NAMED and canon(answer) in taken:
                why = "the same name as another placeholder in this file"
            if not why and canon(answer) in refused.get(key, ()):
                why = "disputed for this key"
            if not why and already and not annotate:
                why = "this worker already voted on it (under some session label)"
            if why:
                rejected.append(f"{answer_key(kind, scope, ident)} -> {answer}: {why}")
                continue
            if kind in NAMED:
                taken.add(canon(answer))
            if annotate:
                vote = next(v for v in reversed(prior_votes)
                            if v["key"] == key and v["hash"] == h and v["worker"] == worker)
            else:
                vote = {"key": key, "hash": h, "model": model, "session": session, "worker": worker, "date": now}
                votes.append(vote)
                tally[key][h][worker] = model
            if meaning:
                meanings.append({**vote, "meaning": meaning})
                tally.meanings[key][h, worker].add(meaning)
            open_key = needs_review(key, state, tally, refused)
            mine, rivals, role = name_agreement.support(tally, refused, key, answer, meaning)
            promote = (annotate and role and key in state and state[key]["status"] == "agreed"
                       and not name_agreement.record_meaning(state[key]["id"]))
            if (open_key or promote) and wins(mine, rivals, lead=lead, min_models=min_models, key=key):
                agents = ";".join(f"{w}@{m}" for w, m in sorted(mine.items()))
                name = lane_spelling(lane, answer, kind)
                row = {"id": record_id(key, name, role), "kind": kind, "old": ident, "new": name,
                       "rva": f"0x{rva:08X}" if rva is not None else "", "agents": agents, "key": key,
                       "status": "agreed"}
                row["detail"] = approval_detail(tally, refused, row)
                agreed.append(row)
                state[key] = row
    lane.append(VOTES, VOTE_COLUMNS, votes)
    lane.append(MEANINGS, MEANING_COLUMNS, meanings)
    lane.append(AGREED, AGREED_COLUMNS, agreed)
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
          + ("; run `python3 tools/name_lane.py apply` to land them" if agreed and apply_ready is None else ""))
    if meanings:
        print(f"name_lane: stage {VOTES}, {MEANINGS} and {AGREED} together for structured meanings")
    if apply_ready is not None and agreed:
        return cmd_apply(lane, argparse.Namespace(
            key=[row["key"] for row in agreed], retry_blocked=False, only_labels=None,
            lead=lead, min_models=min_models, claim=True, limit=apply_ready,
            max_files=getattr(args, "max_files", 25)), verify=verify, checks=checks)
    return 0


def lane_spelling(lane, name, kind):
    """Zero Hour's or WorldBuilder's own spelling of an agreed name when exactly
    one fits: votes match case- and order-blind, so otherwise the last voter's
    casing would land."""
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

def rename_kwargs(kind, scope, old, new, rva, rel):
    if kind == "function":
        return {"rva": int(scope, 16), "new": new}
    if kind == "class":
        return {"name": old, "new": new}
    if kind == "member":
        return {"cls": scope, "member": old, "new": new}
    if kind in ("param", "local"):
        return {"source": rel, "name": old, "new": new, "function": scope, **({"local_binding": True} if kind == "local" else {})}
    if kind == "global":
        return {"name": old, "new": new}
    raise rename.Refusal(f"unknown lane kind {kind}")


def cmd_apply(lane, args, *, verify=rename.build_verify, checks=rename.ledger_checks):
    limit = getattr(args, "limit", None)
    if limit is not None and limit < 1:
        fail("--limit must be positive")
    max_files = getattr(args, "max_files", 25)
    if max_files < 1:
        fail("--max-files must be positive")
    state, tally, refused = lane.state(), lane.tally(), lane.disputed()
    only = label_list(args.only_labels) if getattr(args, "only_labels", None) else None
    selected_keys = set(getattr(args, "key", None) or ())
    todo = collections.defaultdict(list)
    landed = blocked = stale = outside = selected = deferred = 0
    pending = False
    for key, row in state.items():
        if selected_keys and key not in selected_keys:
            continue
        if row["status"] == "agreed" or (args.retry_blocked and row["status"] == "blocked"):
            pending = True
            mine, rivals, _ = approval_support(tally, refused, row)
            if only and not own_voters(mine, only):
                outside += 1
                continue
            if not wins(mine, rivals, lead=args.lead, min_models=args.min_models, key=key):
                print(f"{key}: votes no longer agree under --lead {args.lead} --min-models {args.min_models}; left")
                continue
            if limit is not None and selected >= limit:
                deferred += 1
                continue
            selected += 1
            agents = ";".join(f"{w}@{m}" for w, m in sorted(mine.items()))
            todo[split_key(key)[0]].append(dict(row, agents=agents))
    if not pending:
        print("name_lane: nothing agreed is waiting to land.")
        return 0
    print(f"name_lane: selected {sum(map(len, todo.values()))} key(s) across {len(todo)} file(s).", flush=True)
    for rel, rows in sorted(todo.items()):
        text = lane.text(rel)
        live = {key_of(rel, k, s, i) for k, s, i, _ in
                lane.owned(rel, text, kinds={r["kind"] for r in rows})} if text is not None \
            and lane.servable(rel) else set()
        ordered = sorted(rows, key=lambda r: LAND_ORDER[r["kind"]])
        scoped = [r for r in ordered if r["kind"] in ("param", "local") and r["key"] in live]
        batched = set()
        batch_attempted = getattr(args, "no_batch", False)
        for row in ordered:
            key = row["key"]
            if key in batched:
                continue
            _, kind, scope, ident = split_key(key)
            if not batch_attempted and kind in ("param", "local") and len(scoped) > 1:
                batch_attempted = True
                requests = []
                for candidate in scoped:
                    _, k, s, old = split_key(candidate["key"])
                    requests.append((k, dict(basis="inferred", evidence=f"agree:{candidate['id']}", max_files=max_files,
                                            **rename_kwargs(k, s, old, candidate["new"], candidate["rva"], rel))))
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
                               **rename_kwargs(kind, scope, ident, row["new"], row["rva"], rel))
                    outcome.update(status="landed", detail=approval_detail(tally, refused, row))
                    landed += 1
                except (rename.Refusal, rename.VerifyFailed) as exc:
                    outcome.update(status="blocked", detail=" ".join(str(exc).split())[:300])
                    blocked += 1
                    print(f"{key}: blocked: {outcome['detail']}")
                lane.ctx._cache.clear()
            lane.append(AGREED, AGREED_COLUMNS, [outcome])
    print(f"name_lane: landed {landed}, blocked {blocked}, stale {stale}. Stage the files rename.py listed "
          f"and {AGREED} (plus {MEANINGS} when structured votes added it); the lander commits.")
    if deferred:
        print(f"name_lane: {deferred} ready key(s) left waiting by --limit {limit}; run apply again to continue.")
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
    if getattr(args, "only_labels", None):
        only, tally, refused = label_list(args.only_labels), lane.tally(), lane.disputed()
        picked = 0
        for key, row in state.items():
            if row["status"] != "agreed":
                continue
            mine, rivals, _ = approval_support(tally, refused, row)
            picked += wins(mine, rivals, lead=args.lead, min_models=args.min_models, key=key) and own_voters(mine, only)
        print(f"--only-labels {','.join(sorted(only))}: apply would select {picked} of {count['agreed']} "
              f"waiting key(s) (--lead {args.lead} --min-models {args.min_models})")
    if args.metric:
        names, bad = name_metric.readable()
        print(f"Readable names: {100 * (1 - bad / names):.2f}% ({names - bad:,} of {names:,}); placeholders {bad:,}")
    return 0


def main(argv=None, lane=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next", help="serve placeholders from one subsystem as a shared brief")
    n.add_argument("--session", required=True, help="a label for this brief; who votes is the worker identity, not this")
    n.add_argument("--model", required=True, help="the label you vote under, e.g. seat-a")
    n.add_argument("--count", type=int, default=1, help="serve this many files")
    n.add_argument("--file", help="serve this file instead of the next in the queue")
    n.add_argument("--subsystem", metavar="CODE_PREFIX",
                   help="restrict to this source/approved-TU directory; one subsystem per batch")
    n.add_argument("--mixed", action="store_true", help="retain the shuffled multi-subsystem queue")
    n.add_argument("--review-only", action="store_true", help="serve only shared names needing a different second voter")
    n.add_argument("--meaning-review-only", action="store_true", help="clarify your own unannotated scoped votes in disputes")
    n.add_argument("--list-only", action="store_true",
                   help="print the queue's file/size/kind metadata as JSON; no session, no brief")
    s = sub.add_parser("submit", help="record a session's answers as hashed votes")
    s.add_argument("answer")
    s.add_argument("--session", required=True)
    s.add_argument("--model", required=True)
    s.add_argument("--apply-ready", type=int, metavar="N", help="verify and apply at most N newly approved keys after recording votes")
    s.add_argument("--max-files", type=int, default=25, help="affected-source bound when --apply-ready is used")
    for p in (s,):
        p.add_argument("--lead", type=int, default=2, help="votes the name must lead every rival by")
        p.add_argument("--min-models", type=int, default=1, help="distinct models among the agreeing workers")
    a = sub.add_parser("apply", help="land agreed names through tools/rename.py")
    a.add_argument("--limit", type=int, metavar="N", help="attempt at most N eligible approvals, leaving the rest waiting")
    a.add_argument("--retry-blocked", action="store_true", help="try blocked names again, e.g. after a fix")
    a.add_argument("--key", action="append", help="apply only this exact source|kind|scope|placeholder key (repeatable)")
    a.add_argument("--max-files", type=int, default=25, help="maximum affected sources; every selected source is still verified")
    a.add_argument("--no-batch", action="store_true", help="verify each parameter/local rename separately")
    a.add_argument("--lead", type=int, default=2)
    a.add_argument("--min-models", type=int, default=1)
    a.add_argument("--only-labels", metavar="L,L",
                   help="land only keys whose winning spelling was voted entirely under these --model labels")
    a.add_argument("--no-claim", dest="claim", action="store_false", help="do not take tools/claims.py claims")
    d = sub.add_parser("dispute", help="put landed names back and refuse them for their keys")
    d.add_argument("keys", nargs="+", help="as name_agreed.csv spells them (source|kind|scope|placeholder)")
    d.add_argument("--reason", required=True, help="what the code shows against the landed name")
    d.add_argument("--no-claim", dest="claim", action="store_false")
    st = sub.add_parser("status", help="votes and agreement counts")
    st.add_argument("--metric", action="store_true", help="also the tree-wide readable-name metric (slow)")
    st.add_argument("--only-labels", metavar="L,L", help="count the waiting keys apply --only-labels would select")
    st.add_argument("--lead", type=int, default=2, help="with --only-labels: the lead apply would use")
    st.add_argument("--min-models", type=int, default=1, help="with --only-labels: the min-models apply would use")
    reconcile = sub.add_parser("reconcile", help="report existing-type collisions for evidence-backed reconciliation; edits nothing")
    reconcile.add_argument("--key", action="append", help="select an exact pending class key (repeatable)")
    placement = sub.add_parser("consolidate", help="build original-file evidence and consolidation packets; applies nothing")
    import source_layout
    source_layout.configure_parser(placement)
    args = ap.parse_args(argv)
    if args.cmd == "consolidate":
        try:
            return source_layout.run(args, root=lane.root if lane else ROOT)
        except (ValueError, OSError) as exc:
            ap.exit(2, f"source-layout: {exc}\n")
    lane = lane or Lane()
    if args.cmd == "next":
        return cmd_next(lane, args)
    if args.cmd == "submit":
        return cmd_submit(lane, args, lead=args.lead, min_models=args.min_models)
    if args.cmd == "apply":
        return cmd_apply(lane, args)
    if args.cmd == "reconcile":
        return cmd_reconcile(lane, args)
    if args.cmd == "dispute":
        return cmd_dispute(lane, args)
    return cmd_status(lane, args)


if __name__ == "__main__":
    sys.exit(main())
