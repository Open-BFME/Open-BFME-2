#!/usr/bin/env python3
"""The evidence lane's candidate list: names the target or a reference already gives.

tools/rename.py lands one verified rename and records its basis, but it does
not look for work. Most placeholder names (Rva..., rva..., bfme...) sit at
addresses where nothing says what the function is called, and those go to the
inferred lane (two blind agents must agree). A minority already have evidence
on record -- a WorldBuilder body that asserts its own `Class::method`, a Zero
Hour body that compiles to the very same bytes, a retail debug string that
spells its function's name -- and should be named from that evidence instead
of guessed. This tool finds them and grades them, so the daily pass can land
the proven ones as `canonical:<kind>` and hand the rest to the inferred lane
as context.

It writes build/name_evidence.tsv (not committed), one candidate per line:

    kind  key  rva  current  candidate  evidence_kind  strength  detail

  kind      what rename.py would rename: function (key = the row's mangled
            name) or class (key = the class token)
  current   the placeholder word that would go; candidate: the word to come
  strength  `canonical`: the evidence is proof by this tool's rules and
            detail carries `basis=canonical:<k>` and an `evidence=` string
            rename.py's check_canonical accepts; `hint`: context only, for the
            inferred lane -- never a basis on its own

Evidence kinds, and when each counts as proof:

  wb-assert    reverse/wb_name_leads.csv plus build/wb (or reverse/wb/*.xz):
               the paired WorldBuilder body asserts the name itself (it is in
               that body's assert/debug names and no other WB body carries
               it), the pairing scores >= --wb-min-score, the WB body is
               paired with no other game.dat function, the address has one WB
               name, and the row's real scope parts agree. Anything less
               (`wb-lead`) is a hint. WB is an unoptimised internal build
               paired by call graph: a pairing is identity evidence, not
               bytes -- review with `tools/wb_show.py <rva>` before landing.
  zh-body      an exact unique same-body Zero Hour placement from
               tools/zh_sweep.py's cache: proof when the body is specific
               (>= 32 bytes with a relocation), every donor at the address
               agrees on the name, and a Zero Hour line spelling it is found
               to cite. A trivial body (ctors, getters) places anywhere: hint.
  bfme1-body   an exact unique same-body BFME 1 placement from
               tools/bfme1_sweep.py's cache. BFME 1's own ledger names are
               agents' choices (often copied from Zero Hour), so it is proof
               only for a specific, unfolded body where BFME 1's
               ea_evidence.csv (strong/aligned) gives the same name, or where
               a Zero Hour same-body record at this address names the same
               donor (and a Zero Hour line spells it, to cite). A Zero Hour
               line spelling the name on its own only shows the name exists:
               a hint, its citation kept as `zh_spelling`.
  string-self  a retail string `Class::method...` referenced by exactly one
               function, whose real class agrees: proof (canonical:string,
               the function's own debug prefix). With a placeholder or other
               class it is a hint.
  string-hint  an identifier-like retail string (reverse/string_xrefs.tsv)
               referenced only by one placeholder function: a hint, never
               proof -- the candidate column is the string, not a name.
  poolkey      a static `NameKeyType` getter (`?rva...@Class@@SA?AW4NameKeyType@@XZ`)
               (class_confirmed: the pool-name string in string_xrefs, a retail
               module registration, or the row's `pool string <Class>` note);
               Zero Hour spells the
               virtual analogue getModuleNameKey (Module.h), the static form
               has no canonical name: a hint.

  vtable-slot  a placeholder method of class C fills slot i of C's own
               vftable (reverse/data_ledger.csv `??_7C@@6B@`, slots read from
               game.dat, E9 link thunks followed), and slot i of a base class
               B's vftable holds a different body with a real method name m:
               C's slot overrides B::m, so the placeholder is probably `m`. B
               is a base when the Zero Hour headers say so (`class C : public
               B`, transitively) or when C's table carries one of B's own
               bodies unchanged at the same slot (a target fact). Detail cites
               the Zero Hour `virtual ... m(` declaration when there is one.
               A hint only: BFME inserts virtuals, the linker folds identical
               bodies, and the base slot's name is itself a ledger choice.
  vtable-order the same, where B's slot i is a pure-virtual stub and so names
               nothing: the word comes from Zero Hour's declaration order for
               B (primary base's slots first, overrides keep their slot, new
               virtuals appended, overloads grouped). BFME inserts and drops
               virtuals, so the order is used only between the nearest named
               slots a < i < b of one retail table (B's or a table deriving
               from it), whose words must sit exactly b - a apart in the
               computed order. A hint only, like vtable-slot.

tools/rename.py does not take this tool's word for it: its check_canonical
calls proof() here for canonical:wb, canonical:zh and canonical:bfme1, which
re-grades the tree with these same rules and accepts only a `canonical`
candidate for that very address (or class) and spelling.

Sweep caches are read where they are (`--sweep-dir`, default build/); none
is run here, because a sweep takes the toolchain and minutes. A missing cache
is reported and skipped.

Nothing here proposes renaming a protected name: the current word must be a
placeholder or weak name (tools/name_metric.py, through rename.is_placeholder)
or a name reverse/name_basis.csv records as inferred (canonical rows only),
and is never a retail export, a vendored= or .lib row, an evidence-tier name,
a converged global, a retail module or RTTI class, a readable class registered
in reverse/canonical_classes.csv (tools/rename.py class renames a registered
placeholder with its key, contract and views), a word a retail string spells,
or a name name_basis.csv records as canonical. A candidate that is itself a placeholder,
a keyword or not an identifier is dropped. Two sources naming one key
differently demote every canonical row for that key to a hint.

    python3 tools/name_evidence.py [--out build/name_evidence.tsv]
        [--sweep-dir DIR ...] [--wb-min-score 4] [--kinds wb,zh,bfme1,string,poolkey,vtable]
"""
import argparse
import collections
import csv
import io
import json
import lzma
import os
import re
import sys
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import name_metric  # noqa: E402
import rename  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
OUT = "build/name_evidence.tsv"
COLUMNS = ("kind", "key", "rva", "current", "candidate", "evidence_kind", "strength", "detail")
IMAGE_BASE = 0x400000
KINDS = ("wb", "zh", "bfme1", "string", "poolkey", "vtable")
CANONICAL = "canonical"
HINT = "hint"
# Which evidence kinds may ever be proof, and the rename.py basis they map to.
PROOF_BASIS = {"wb-assert": "canonical:wb", "zh-body": "canonical:zh", "bfme1-body": "canonical:bfme1",
               "string-self": "canonical:string"}
HINT_ONLY = ("wb-lead", "string-hint", "poolkey", "vtable-slot", "vtable-order")
ZH_ROOT = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour"
BFME1_ROOT = "reference/open-bfme-1"
BFME1_EA = "reference/open-bfme-1/targets/game/reverse/ea_evidence.csv"
MODULE_H = ZH_ROOT + "/GeneralsMD/Code/GameEngine/Include/Common/Module.h"
SPECIFIC_SIZE = 32
# One function's evidence names its own scope; renaming the whole class needs
# this many addresses proven independently, all agreeing.
CLASS_SUPPORT = 2
POOLKEY = re.compile(r"\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@SA\?AW4NameKeyType@@XZ")
SELF_STRING = re.compile(r"([A-Za-z_]\w*)::(~?[A-Za-z_]\w*)(?![\w:])")
# A debug prefix goes on into a message ("INI::load, cannot open file"); a bare
# `Class::Name` is as often a field or chunk label (MeshMatDescClass::UV).
MESSAGE_TAIL = re.compile(r"\s*(?:\(|:|,|-|\s\w)")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


@dataclass
class Candidate:
    kind: str
    key: str
    rva: int
    current: str
    candidate: str
    evidence_kind: str
    strength: str
    detail: dict

    def line(self):
        detail = "; ".join(f"{k}={v}" for k, v in self.detail.items() if v not in (None, ""))
        values = [self.kind, self.key, f"0x{self.rva:08X}" if self.rva is not None else "", self.current,
                  self.candidate, self.evidence_kind, self.strength, detail]
        return "\t".join(re.sub(r"[\t\r\n]+", " ", str(v)) for v in values)


def parse_rva(text):
    try:
        return int(str(text).strip(), 16)
    except (TypeError, ValueError):
        return None


def split_scope(name):
    """(class or None, method or None, special) for a mangled function name;
    special is True for a ctor/dtor (its method word is the class)."""
    scope = rename.scope_of(name or "")
    if not scope:
        return None, None, False
    parts = scope.split("::")
    if name.startswith(("??0", "??1")):
        return parts[-2], None, True
    return (parts[-2] if len(parts) > 1 else None), parts[-1], False


def donor_parts(text):
    """(class, method) of a donor `A::B::m` / `m` spelling (method None for
    a ctor/dtor, which only names its class)."""
    parts = [p for p in re.split(r"::", text or "") if p]
    if not parts or not all(IDENT.fullmatch(p.lstrip("~")) for p in parts):
        return None, None
    cls = parts[-2] if len(parts) > 1 else None
    method = parts[-1]
    if cls and method.lstrip("~") == cls:
        return cls, None
    return cls, method


def good_word(word, kind):
    return bool(word and IDENT.fullmatch(word) and word not in name_metric.KEYWORDS
                and not rename.is_placeholder(word, kind))


# ---------------------------------------------------------------- the tree

class Tree:
    """Ledger indexes and the protected-name sets, read once."""

    def __init__(self, root=ROOT):
        self.root = Path(root)
        self.notes = []
        self.rows_by_rva = collections.defaultdict(list)
        self.rows_by_class = collections.defaultdict(list)
        self.scoped_rvas = collections.defaultdict(set)
        # every matched name at its start address, protected and generated
        # rows included: a base slot's name is evidence whatever its source
        self.names_by_rva = collections.defaultdict(set)
        protected_names, scoped = set(), set()
        for row in self.dicts("reverse/functions.csv"):
            if row.get("status") != "matched":
                continue
            name, source, notes = row.get("name", ""), row.get("source", ""), row.get("notes", "")
            start = parse_rva(row.get("target_rva"))
            if start is not None:
                self.names_by_rva[start].add(name)
            if "vendored=" in notes or source.lower().endswith(".lib"):
                protected_names.add(name)
                continue
            if rename.is_generated(source) or name.startswith(rename.FUNCLET_PREFIXES):
                continue
            rva = parse_rva(row.get("target_rva"))
            if rva is not None:
                self.rows_by_rva[rva].append(row)
            cls, method, _ = split_scope(name)
            if cls:
                self.rows_by_class[cls].append(row)
            if method:
                self.scoped_rvas[(cls, method)].add(rva)
        protected_names |= {r.get("name", "") for r in self.dicts("reverse/exports.csv")}
        protected_names |= {r.get("name", "") for r in self.dicts("reverse/name_tiers.csv")
                            if r.get("name_tier") == "evidence"}
        protected_names |= {r.get("name", "") for r in self.dicts("reverse/data_converged.csv")}
        self.inferred, canonical = set(), set()
        for row in self.dicts("reverse/name_basis.csv"):
            (canonical if row.get("basis", "").startswith("canonical") else self.inferred).add(row.get("new", ""))
        self.inferred -= canonical
        self.protected_names = protected_names | canonical
        self.protected_words = set(rename.RTTI_CLASSES) | canonical
        self.protected_words |= {r.get("name", "") for r in self.dicts("reverse/module_factory_registrations.csv")}
        self.registered = {r.get("class", "") for r in self.dicts("reverse/canonical_classes.csv")}
        for name in protected_names:
            scoped.update(rename.fragments_text(name) or [])
        self.protected_classes = scoped | self.protected_words | \
            {c for c in self.registered if not rename.is_placeholder(c, "class")}
        self.strings = self.read_strings()
        for text, _ in self.strings:
            self.protected_words.update(w for w in re.findall(r"[A-Za-z_]\w*", text) if len(w) > 2)
        self.protected_words.discard("")

    def path(self, rel):
        return self.root / rel

    def text(self, rel):
        path = self.path(rel)
        return path.read_text(encoding="utf-8", errors="replace") if path.exists() else None

    def dicts(self, rel):
        text = self.text(rel)
        return list(csv.DictReader(io.StringIO(text))) if text else []

    def read_strings(self):
        out = []
        for line in (self.text("reverse/string_xrefs.tsv") or "").splitlines():
            if "\t" not in line:
                continue
            text, refs = line.rsplit("\t", 1)
            rvas = [r for r in (parse_rva(x) for x in refs.split(",")) if r is not None]
            out.append((text, rvas))
        return out

    # ------------------------------------------------------------ protection

    def function_refusal(self, row, word):
        name = row.get("name", "")
        if name in self.protected_names:
            return "protected name"
        if word in self.protected_words:
            return "protected word"
        if rename.is_placeholder(word, "function"):
            return None
        return None if name in self.inferred or word in self.inferred else "real name"

    def real_class(self, word):
        return not rename.is_placeholder(word, "class") and word not in self.inferred

    def class_refusal(self, word):
        if word in self.protected_classes:
            return "protected class"
        if rename.is_placeholder(word, "class"):
            return None
        return None if word in self.inferred else "real name"


# ---------------------------------------------------------------- proposals

class Collector:
    def __init__(self, tree):
        self.tree = tree
        self.out = []
        self.skips = collections.Counter()

    def propose(self, rva, donor, evidence_kind, strength, detail):
        """Candidates for every row at `rva` from a donor `Class::method`."""
        dcls, dmethod = donor_parts(donor)
        if dcls is None and dmethod is None:
            self.skips[f"{evidence_kind}: unreadable donor"] += 1
            return
        rows = self.tree.rows_by_rva.get(rva, [])
        if not rows:
            self.skips[f"{evidence_kind}: no matched row at the address"] += 1
            return
        for row in rows:
            name = row["name"]
            cls, method, special = split_scope(name)
            if cls is None and method is None:
                self.skips[f"{evidence_kind}: unparsed row name"] += 1
                continue
            row_strength, notes = strength, dict(detail)
            if bool(cls) != bool(dcls):
                row_strength = HINT
                notes["caution"] = "member vs free function differ"
            elif cls and dcls and cls != dcls and self.tree.real_class(cls):
                row_strength = HINT
                notes["caution"] = f"real class {cls} differs from donor class {dcls}"
            if method and not special and dmethod and method != dmethod:
                refusal = self.tree.function_refusal(row, method)
                taken = self.tree.scoped_rvas.get((cls, dmethod), set()) - {rva}
                if taken and row_strength == CANONICAL:
                    row_strength = HINT
                    notes["caution"] = (f"{cls + '::' if cls else ''}{dmethod} already names "
                                        f"0x{min(taken):08X}: one body, one name")
                if refusal or not good_word(dmethod, "function"):
                    self.skips[f"{evidence_kind}: function {refusal or 'weak candidate'}"] += 1
                else:
                    self.add("function", name, rva, method, dmethod, evidence_kind, row_strength,
                             notes, inferred_only=method in self.tree.inferred)
            if cls and dcls and cls != dcls:
                refusal = self.tree.class_refusal(cls)
                if refusal or not good_word(dcls, "class"):
                    self.skips[f"{evidence_kind}: class {refusal or 'weak candidate'}"] += 1
                else:
                    nested = {"nested": "yes"} if donor.count("::") > 1 else {}
                    self.add("class", cls, rva, cls, dcls, evidence_kind, row_strength, {**detail, **nested},
                             inferred_only=cls in self.tree.inferred)

    def add(self, kind, key, rva, current, candidate, evidence_kind, strength, detail, inferred_only=False):
        if strength == CANONICAL and evidence_kind not in PROOF_BASIS:
            strength = HINT
        if inferred_only and strength != CANONICAL:
            # only a canonical name may replace a recorded inferred one
            self.skips[f"{evidence_kind}: hint over an inferred name"] += 1
            return
        detail = dict(detail)
        if strength == CANONICAL:
            detail = {"basis": PROOF_BASIS[evidence_kind], **detail}
        self.out.append(Candidate(kind, key, rva, current, candidate, evidence_kind, strength, detail))

    def finish(self):
        """Demote canonical rows whose key another source names differently;
        fold a class's per-address rows into one per (key, candidate, kind)."""
        names = collections.defaultdict(set)
        support = collections.defaultdict(set)
        for c in self.out:
            names[(c.kind, c.key)].add(c.candidate)
            if c.kind == "class" and c.strength == CANONICAL:
                support[(c.key, c.candidate)].add(c.rva)
        for c in self.out:
            if c.kind != "class" or c.strength != CANONICAL:
                continue
            weak = []
            if c.detail.pop("nested", None):
                weak.append("donor class is nested")
            if c.candidate in self.tree.rows_by_class:
                weak.append(f"class {c.candidate} already exists: a merge or rescope, not a rename")
            if len(support[(c.key, c.candidate)]) < CLASS_SUPPORT:
                weak.append(f"{len(support[(c.key, c.candidate)])} proven address(es) < {CLASS_SUPPORT}")
            if weak:
                c.strength = HINT
                c.detail.pop("basis", None)
                c.detail["weak"] = ", ".join(filter(None, [c.detail.get("weak"), *weak]))
        merged = {}
        for c in self.out:
            rivals = names[(c.kind, c.key)] - {c.candidate}
            if rivals:
                c.detail["conflict"] = "/".join(sorted(rivals))
                if c.strength == CANONICAL:
                    c.strength = HINT
                    c.detail.pop("basis", None)
            ident = (c.kind, c.key, c.candidate, c.evidence_kind)
            if c.kind == "class" and ident in merged:
                prior = merged[ident]
                prior.detail["addresses"] = prior.detail.get("addresses", 1) + 1
                if c.strength == CANONICAL and prior.strength != CANONICAL:
                    c.detail["addresses"] = prior.detail["addresses"]
                    merged[ident] = c
                continue
            if c.kind == "function" and ident in merged:
                continue
            merged[ident] = c
        order = {CANONICAL: 0, HINT: 1}
        return sorted(merged.values(), key=lambda c: (order[c.strength], c.evidence_kind, c.kind, c.key,
                                                       c.candidate))


# ---------------------------------------------------------------- WorldBuilder

def jsonl(tree, name):
    """Records of build/wb/<name> (unpacked) or reverse/wb/<name>.xz."""
    plain, packed = tree.path("build/wb") / name, tree.path("reverse/wb") / (name + ".xz")
    if plain.exists():
        handle = plain.open(encoding="utf-8")
    elif packed.exists():
        handle = io.TextIOWrapper(lzma.open(packed), encoding="utf-8")
    else:
        return None
    with handle:
        return [json.loads(line) for line in handle if line.strip()]


def wb_lane(tree, col, min_score):
    leads = [r for r in tree.dicts("reverse/wb_name_leads.csv") if r.get("wb_name")]
    if not leads:
        tree.notes.append("wb: reverse/wb_name_leads.csv has no named leads; skipped")
        return
    matches, functions = jsonl(tree, "matches_full.jsonl"), jsonl(tree, "wb_functions.jsonl")
    if matches is None or functions is None:
        tree.notes.append("wb: build/wb or reverse/wb data missing; leads graded as hints only")
        matches, functions = matches or [], functions or []
    wb = {f["va"]: f for f in functions}
    carriers = collections.Counter()
    for f in functions:
        carriers.update(set(f.get("names") or ()))
    by_gd = collections.defaultdict(list)
    partners = collections.Counter()
    for m in matches:
        by_gd[m["gd_va"]].append(m)
        partners[m["wb_va"]] += 1
    names_at = collections.defaultdict(set)
    for lead in leads:
        names_at[parse_rva(lead["target_rva"])].add(lead["wb_name"])
    for lead in leads:
        rva = parse_rva(lead["target_rva"])
        if rva is None:
            continue
        score = float(lead.get("score") or 0)
        pair = next((m for m in by_gd.get(rva + IMAGE_BASE, []) if m.get("wb_name") == lead["wb_name"]), None)
        rec = wb.get(pair["wb_va"]) if pair else None
        own = dict(rec.get("name_files") or ()) if rec else {}
        asserted = bool(rec and lead["wb_name"] in (rec.get("names") or ()))
        spread = carriers[lead["wb_name"]]
        shared = partners[pair["wb_va"]] if pair else 0
        reasons = []
        if not asserted:
            reasons.append("WB body does not assert the name")
        elif spread != 1:
            reasons.append(f"{spread} WB bodies carry the name")
        if score < min_score:
            reasons.append(f"score {score:g} < {min_score:g}")
        if shared > 1:
            reasons.append(f"WB body paired with {shared} game.dat functions")
        if len(names_at[rva]) > 1:
            reasons.append("several WB names at the address")
        strength = HINT if reasons else CANONICAL
        where = own.get(lead["wb_name"], "")
        detail = {"evidence": f"wb lead 0x{rva:08X}: WB 0x{pair['wb_va']:X} asserts {lead['wb_name']}"
                  if pair and asserted else "", "score": f"{score:g}", "via": lead.get("evidence", ""),
                  "wb_va": f"0x{pair['wb_va']:X}" if pair else "", "assert_path": where,
                  "wb_file": lead.get("wb_file", ""), "weak": ", ".join(reasons),
                  "review": f"python3 tools/wb_show.py 0x{rva:08X}"}
        kind = "wb-assert" if asserted else "wb-lead"
        col.propose(rva, lead["wb_name"], kind, strength, detail)


# ---------------------------------------------------------------- sweeps

def find_cache(tree, dirs, name):
    for base in dirs:
        path = Path(base) / name
        if not path.is_absolute():
            path = tree.path(path)
        if path.exists():
            return path
    return None


DEFINITION = re.compile(r"\b([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*)\s*\(")
SOURCE_SUFFIXES = (".cpp", ".c", ".h", ".inl", ".hpp")


def zh_definitions(tree):
    """{(class, method): '<path>:<line>'} of every `Class::method(` the Zero
    Hour tree spells, read once (the first spelling wins)."""
    if "_zh_defs" in tree.__dict__:
        return tree._zh_defs
    out = {}
    base = tree.path(ZH_ROOT)
    for dirpath, _, files in os.walk(base):
        for name in sorted(files):
            if not name.lower().endswith(SOURCE_SUFFIXES):
                continue
            path = Path(dirpath) / name
            rel = path.relative_to(tree.root).as_posix()
            text = path.read_text(encoding="utf-8", errors="replace")
            for number, line in enumerate(text.splitlines(), 1):
                for match in DEFINITION.finditer(line):
                    out.setdefault((match.group(1), match.group(2)), f"{rel}:{number}")
    tree._zh_defs = out
    return out


def cite_definition(tree, source, cls, method):
    """`<path>:<line>` of a line defining `cls::method`: in the donor
    `source` first, then anywhere in the Zero Hour tree."""
    if not method or not cls:
        return None
    qualified = re.compile(r"\b%s\s*::\s*%s\s*\(" % (re.escape(cls), re.escape(method)))
    text = tree.text(source) if source else None
    if text:
        for number, line in enumerate(text.splitlines(), 1):
            if qualified.search(line):
                return f"{source}:{number}"
    return zh_definitions(tree).get((cls, method))


def zh_lane(tree, col, dirs, extra_names=None):
    path = find_cache(tree, dirs, "zh_sweep/match.json")
    if path is None:
        tree.notes.append("zh: no zh_sweep/match.json under " + ", ".join(map(str, dirs)) +
                          " (run tools/zh_sweep.py match); skipped")
        return {}
    records = json.loads(path.read_text())
    tree.notes.append(f"zh: {path} ({len(records)} records)")
    exact = [r for r in records if r.get("bucket", "").startswith("exact-unique") and r.get("rva") is not None]
    by_rva = collections.defaultdict(set)
    for r in exact:
        by_rva[r["rva"]].add(rename.scope_of(r["sym"]) or r["sym"])
    named = {}
    for r in exact:
        donor = rename.scope_of(r["sym"])
        if not donor:
            continue
        if len(by_rva[r["rva"]]) == 1:
            named[r["rva"]] = donor
        cls, method = donor_parts(donor)
        reasons = []
        if r.get("size", 0) < SPECIFIC_SIZE or not r.get("relocs"):
            reasons.append(f"trivial body ({r.get('size')} bytes, {r.get('relocs', 0)} relocs)")
        if len(by_rva[r["rva"]]) > 1:
            reasons.append("several donors at the address")
        cite = cite_definition(tree, r.get("source"), cls, method) if not reasons else None
        if not reasons and not cite:
            reasons.append("no Zero Hour line spells it")
        detail = {"evidence": f"{cite} same-body {r['sym']}" if cite else "", "donor": r["sym"],
                  "size": r.get("size"), "relocs": r.get("relocs"), "bucket": r.get("bucket"),
                  "cache": path.name if path.parent.name else "", "weak": ", ".join(reasons)}
        col.propose(r["rva"], donor, "zh-body", HINT if reasons else CANONICAL, detail)
    return named


def zh_unique_donors(tree, dirs):
    """{rva: donor} of exact unique same-body Zero Hour placements with one
    donor at the address -- what zh_lane returns, without proposing."""
    path = find_cache(tree, dirs, "zh_sweep/match.json")
    if path is None:
        return {}
    by_rva = collections.defaultdict(set)
    for r in json.loads(path.read_text()):
        if r.get("bucket", "").startswith("exact-unique") and r.get("rva") is not None and rename.scope_of(r["sym"]):
            by_rva[r["rva"]].add(rename.scope_of(r["sym"]))
    return {rva: next(iter(d)) for rva, d in by_rva.items() if len(d) == 1}


def ea_names(tree):
    out = {}
    text = tree.text(BFME1_EA)
    if not text:
        return out
    for number, line in enumerate(text.splitlines(), 1):
        parts = line.split(",")
        if len(parts) >= 5 and parts[1] == "name" and parts[4] in ("strong", "aligned"):
            rva = parse_rva(parts[0])
            if rva is not None:
                out[rva] = (parts[2], f"{BFME1_EA}:{number}", parts[4])
    return out


def bfme1_lane(tree, col, dirs, zh_named):
    path = find_cache(tree, dirs, "bfme1_sweep/match.json")
    if path is None:
        tree.notes.append("bfme1: no bfme1_sweep/match.json under " + ", ".join(map(str, dirs)) +
                          " (run tools/bfme1_sweep.py scan); skipped")
        return
    data = json.loads(path.read_text())
    records = data.get("records", [])
    tree.notes.append(f"bfme1: {path} ({len(records)} unique records)")
    ea = ea_names(tree)
    by_rva = collections.defaultdict(set)
    for r in records:
        by_rva[r["bfme2_rva"]].add(rename.scope_of(r["name"]) or r["name"])
    for r in records:
        donor = rename.scope_of(r["name"])
        if not donor:
            continue
        cls, method = donor_parts(donor)
        twins = {rename.scope_of(t) for t in r.get("icf_twins") or ()} - {donor, None}
        real_twins = {t for t in twins if good_word(t.split("::")[-1].lstrip("~"), "function")}
        reasons, cite = [], None
        if r.get("size", 0) < SPECIFIC_SIZE or not (r.get("calls") or r.get("strings") or r.get("imports")):
            reasons.append(f"trivial body ({r.get('size')} bytes)")
        if real_twins:
            reasons.append(f"folded with {len(real_twins)} other real name(s) in lotrbfme.exe")
        if len(by_rva[r["bfme2_rva"]]) > 1:
            reasons.append("several donors at the address")
        spelling = None
        if not reasons:
            # BFME 1's ledger name is an agent's choice (often copied from Zero
            # Hour): a Zero Hour line spelling it shows the name exists, not
            # that this body is that function. Proof is EA's own evidence for
            # the BFME 1 body, or a Zero Hour body compiling to these bytes.
            ea_row = ea.get(r.get("bfme1_rva"))
            if ea_row and ea_row[0] == donor:
                cite = ea_row[1]
            elif zh_named.get(r["bfme2_rva"]) == donor:
                cite = cite_definition(tree, None, cls, method)
                if not cite:
                    reasons.append("Zero Hour same-body record agrees, but no Zero Hour line spells it")
            else:
                spelling = cite_definition(tree, None, cls, method)
                reasons.append("BFME 1 ledger name without EA evidence or a Zero Hour same-body record"
                               + (" (Zero Hour spells it: a hint)" if spelling else ""))
        detail = {"evidence": f"{cite} same-body BFME 1 0x{r.get('bfme1_rva', 0):X} {r['name']}"
                  if cite and not reasons else "",
                  "donor": r["name"], "donor_source": r.get("source"), "size": r.get("size"),
                  "zh_spelling": spelling or "", "weak": ", ".join(reasons)}
        col.propose(r["bfme2_rva"], donor, "bfme1-body", HINT if reasons else CANONICAL, detail)


# ---------------------------------------------------------------- strings

def identifier_like(text):
    return bool(IDENT.fullmatch(text) and len(text) >= 6 and re.search(r"[a-z]", text)
                and (re.search(r"[A-Z]", text[1:]) or "_" in text.strip("_"))
                and not name_metric.placeholder(text))


def string_lane(tree, col):
    if not tree.strings:
        tree.notes.append("string: reverse/string_xrefs.tsv missing; skipped")
        return
    for text, rvas in tree.strings:
        if len(rvas) != 1:
            continue
        rva = rvas[0]
        rows = tree.rows_by_rva.get(rva, [])
        if not rows:
            continue
        match = SELF_STRING.match(text)
        if match:
            cls, method = match.group(1), match.group(2)
            for row in rows:
                rcls, _, _ = split_scope(row["name"])
                message = bool(MESSAGE_TAIL.match(text[match.end():]))
                agree = rcls == cls and tree.real_class(cls) and message
                weak = [] if agree else (["the row's class does not agree"] if rcls != cls or not
                                         tree.real_class(cls) else []) + ([] if message else ["a bare label"])
                detail = {"evidence": f"retail string 0x{rva:08X} '{text[:60]}'" if agree else "",
                          "string": text[:80], "weak": ", ".join(weak)}
                col.propose(rva, f"{cls}::{method}", "string-self", CANONICAL if agree else HINT, detail)
            continue
        if not identifier_like(text):
            continue
        for row in rows:
            _, method, special = split_scope(row["name"])
            if special or not method or tree.function_refusal(row, method):
                continue
            col.add("function", row["name"], rva, method, text, "string-hint", HINT,
                    {"note": "the only function referencing this retail string; the candidate is the "
                             "string, not a name"})


# ---------------------------------------------------------------- pool keys

def poolkey_lane(tree, col):
    refs = collections.defaultdict(set)
    for text, rvas in tree.strings:
        for rva in rvas:
            refs[rva].add(text)
    modules = {r.get("name", "") for r in tree.dicts("reverse/module_factory_registrations.csv")}
    module = tree.text(MODULE_H) or ""
    line = next((n for n, l in enumerate(module.splitlines(), 1) if "getModuleNameKey()" in l and "NAMEKEY" in l),
                None)
    analogue = f"{MODULE_H}:{line}" if line else "Zero Hour Module.h MAKE_STANDARD_MODULE_MACRO"
    for rva, rows in tree.rows_by_rva.items():
        for row in rows:
            match = POOLKEY.fullmatch(row["name"])
            if not match:
                continue
            method, cls = match.groups()
            if tree.function_refusal(row, method):
                continue
            if cls in refs.get(rva, ()):
                confirmed = "string_xrefs"
            elif cls in modules:
                confirmed = "retail module name"
            elif re.search(r"pool string %s\b" % re.escape(cls), row.get("notes", "")):
                confirmed = "ledger note"
            else:
                confirmed = "no"
            col.add("function", row["name"], rva, method, "getModuleNameKey", "poolkey", HINT,
                    {"class_confirmed": confirmed, "analogue": analogue,
                     "note": "static form of ZH's virtual getModuleNameKey; no canonical static name"})


# ---------------------------------------------------------------- vtable slots

VFTABLE = re.compile(r"\?\?_7((?:[A-Za-z_]\w*@)+)@6B@")
SPECIAL_SLOT = ("??0", "??1", "??_G", "??_E", "??_D")
TEXT_END = 0x7BA000  # the end of .text in game.dat; a slot past it ends the table
CLASS_HEAD = re.compile(r"\b(?:class|struct)\s+(?:\w+\s+)?([A-Za-z_]\w*)\s*(?::\s*([^{;]*))?\{")
BASE_SPEC = re.compile(r"(?:(?:public|protected|private|virtual)\s+)*([A-Za-z_][\w:]*)\s*(?:<|,|$)")
VIRTUAL = re.compile(r"\bvirtual\b[^;{}()]*?\b(~?[A-Za-z_]\w*)\s*\(")
NOISE = re.compile(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.S)


def vftables(tree):
    """{class word: rva} of every unfolded primary vftable the data ledger
    names (`??_7C@@6B@`; nested names key on the innermost class), plus the
    count of tables skipped as folded or templated."""
    out, folded = {}, 0
    for row in tree.dicts("reverse/data_ledger.csv"):
        if row.get("kind") != "vtable":
            continue
        names = {n for n in [row.get("name", ""), *row.get("names", "").split(";")] if n.startswith("??_7")}
        primary = {n for n in names if VFTABLE.fullmatch(n)}
        if not primary:
            continue
        rva = parse_rva(row.get("address"))
        if len(primary) != 1 or rva is None:
            folded += 1
            continue
        word = VFTABLE.fullmatch(next(iter(primary))).group(1).split("@")[0]
        if word in out:
            folded += 1
            out[word] = None
            continue
        out[word] = (rva, int(row.get("size") or 0))
    return {k: v for k, v in out.items() if v}, folded


def image_slots(tree, tables):
    """{class: [body rva per slot]} read from game.dat (None when the image
    is not this tree's). A slot ends the table at the first word outside
    .text; an E9 link thunk is followed to its body."""
    if Path(tree.root).resolve() != ROOT:
        return None
    try:
        import build
        data, secs = build.exe_image()
    except Exception as exc:  # no image: the lane is skipped with a note
        tree.notes.append(f"vtable: game.dat unreadable ({exc}); skipped")
        return None

    def read(rva, size):
        try:
            off = build.rva_to_file_offset(secs, rva)
        except ValueError:
            return None
        chunk = data[off:off + size]
        return chunk if len(chunk) == size else None

    def body(rva):
        for _ in range(4):
            op = read(rva, 5)
            if op is None or op[0] != 0xE9:
                break
            rva = (rva + 5 + int.from_bytes(op[1:5], "little", signed=True)) & 0xFFFFFFFF
        return rva

    out = {}
    for cls, (rva, size) in tables.items():
        slots = []
        for k in range(max(size // 4, 1)):
            word = read(rva + 4 * k, 4)
            target = int.from_bytes(word, "little") - IMAGE_BASE if word else -1
            if not 0x1000 <= target < TEXT_END:
                break
            slots.append(body(target))
        out[cls] = slots
    return out


def zh_classes(tree):
    """({class: first base}, {class: {virtual method: '<path>:<line>'}}) from
    the Zero Hour headers, comments and literals stripped, read once; a
    GeneralsMD definition wins over the older Generals copy. Also leaves
    tree._zh_decls: {class: [(path, [virtual words in declaration order])]}
    for zh_slot_order."""
    if "_zh_classes" in tree.__dict__:
        return tree._zh_classes
    bases, virtuals = {}, collections.defaultdict(dict)
    decls = collections.defaultdict(list)  # class: [(path, [virtual words in order])]

    def md(rel):  # Zero Hour's own copy wins over the older game's
        return "/GeneralsMD/" in rel

    for dirpath, _, files in os.walk(tree.path(ZH_ROOT)):
        for name in sorted(files):
            if not name.lower().endswith((".h", ".hpp", ".inl")):
                continue
            path = Path(dirpath) / name
            rel = path.relative_to(tree.root).as_posix()
            text = NOISE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)),
                             path.read_text(encoding="utf-8", errors="replace"))
            for head in CLASS_HEAD.finditer(text):
                cls = head.group(1)
                if head.group(2):
                    base = BASE_SPEC.match(head.group(2).strip())
                    if base and "<" not in head.group(2).split(",")[0] and (cls not in bases or md(rel)):
                        bases[cls] = base.group(1).split("::")[-1]
                depth, start = 1, head.end()
                end = start
                while end < len(text) and depth:
                    depth += {"{": 1, "}": -1}.get(text[end], 0)
                    end += 1
                body = text[start:end]
                flat = re.sub(r"\{[^{}]*\}", lambda m: re.sub(r"[^\n]", " ", m.group(0)), body)
                order = []
                for v in VIRTUAL.finditer(flat):
                    line = text.count("\n", 0, start + v.start(1)) + 1
                    if v.group(1) not in virtuals[cls] or md(rel) and not md(virtuals[cls][v.group(1)]):
                        virtuals[cls][v.group(1)] = f"{rel}:{line}"
                    # `virtual ~C(` matches as `C` (no word boundary before `~`);
                    # a constructor is never virtual, so the class word is the destructor
                    order.append("~" if v.group(1).lstrip("~") == cls else v.group(1))
                decls[cls].append((rel, order))
    tree._zh_classes = (bases, virtuals)
    tree._zh_decls = decls
    return tree._zh_classes


DERIVED = re.compile(r"\b(?:class|struct)\s+([A-Za-z_]\w*)\s*:\s*(?:(?:public|protected|private|virtual)\s+)*"
                     r"([A-Za-z_][\w:]*)\s*[,{\n]")


def code_bases(tree):
    """{class: first base} that BFME 2's own sources (Code/, generated units
    excluded) declare, where every declaration of the class agrees: a
    reconstruction's structure, recorded as such in the detail."""
    seen = collections.defaultdict(set)
    for dirpath, dirs, files in os.walk(tree.path("Code")):
        dirs[:] = [d for d in dirs if not d.startswith("gen_")]
        for name in files:
            if not name.lower().endswith((".h", ".cpp", ".inl", ".hpp")):
                continue
            text = (Path(dirpath) / name).read_text(encoding="utf-8", errors="replace")
            if ":" not in text:
                continue
            for match in DERIVED.finditer(text):
                seen[match.group(1)].add(match.group(2).split("::")[-1])
    return {cls: next(iter(bases)) for cls, bases in seen.items() if len(bases) == 1}


def zh_slot_order(tree, cls, memo=None):
    """The vftable slot words MSVC would lay out for `cls` from its Zero Hour
    declarations, or None when they cannot be computed: the primary base's
    slots first (an override keeps its base's slot; every destructor is the
    one word `~`), then each new virtual name at its first declaration, its
    overloads grouped there (MSVC reverses an overload group, which leaves the
    words unchanged). GeneralsMD's definition wins over Generals'; differing
    definitions in one game, an unparsed base, or a macro-declared virtual the
    parser cannot see make the order wrong -- the caller only trusts it where
    the retail table's named slots agree word for word."""
    memo = {} if memo is None else memo
    if cls in memo:
        return memo[cls]
    memo[cls] = None  # a cycle stays None
    zh_base, _ = zh_classes(tree)
    defs = tree._zh_decls.get(cls, [])
    md = [d for d in defs if "/GeneralsMD/" in d[0]] or defs
    if not md or any(d[1] != md[0][1] for d in md):
        return None
    parent = []
    if zh_base.get(cls):
        parent = zh_slot_order(tree, zh_base[cls], memo)
        if parent is None:
            return None
    inherited = set(parent)
    groups = collections.OrderedDict()
    for word in md[0][1]:
        if word not in inherited:
            groups[word] = groups.get(word, 0) + 1
    memo[cls] = list(parent) + [w for w, n in groups.items() for _ in range(n)]
    return memo[cls]


def vtable_lane(tree, col, slots=None):
    tables, folded = vftables(tree)
    if not tables:
        tree.notes.append("vtable: no named vftables in reverse/data_ledger.csv; skipped")
        return
    if slots is None:
        slots = image_slots(tree, tables)
        if slots is None:
            if not any("vtable:" in n for n in tree.notes):
                tree.notes.append("vtable: game.dat is not this tree's; skipped")
            return
    slots = {c: s for c, s in slots.items() if c in tables and s}
    tree.notes.append(f"vtable: {len(slots)} named vftables read ({folded} folded or duplicated skipped)")
    zh_base, zh_virtual = zh_classes(tree)
    own_base = code_bases(tree)

    def rows_of(body):
        """(class, method word, mangled name) of each matched name at `body`."""
        out = []
        for name in sorted(tree.names_by_rva.get(body, ())):
            cls, method, special = split_scope(name)
            out.append((cls, None if special or name.startswith(SPECIAL_SLOT) else method, name))
        return out

    # a target fact: C's table carries B's own (unfolded) body at B's slot
    inherits = collections.defaultdict(dict)
    for cls, table in slots.items():
        for i, body in enumerate(table):
            named = rows_of(body)
            if len(named) != 1 or not named[0][0] or named[0][0] == cls:
                continue
            base = named[0][0]
            if base in slots and i < len(slots[base]) and slots[base][i] == body:
                inherits[cls].setdefault(base, f"slot {i} {named[0][2]}")

    def ancestors(cls):
        out, seen, todo = {}, {cls}, [cls]
        while todo:
            cur = todo.pop()
            links = dict(inherits.get(cur, {}))
            if zh_base.get(cur):
                links.setdefault(zh_base[cur], "Zero Hour header")
            if own_base.get(cur):
                links.setdefault(own_base[cur], "BFME 2 source declaration")
            for base, via in links.items():
                if base not in seen:
                    seen.add(base)
                    out[base] = via if cur == cls else f"{via} (via {cur})"
                    todo.append(base)
        return out

    memo, verdicts = {}, {}
    descendants = collections.defaultdict(set)
    for cls in slots:
        for base in ancestors(cls):
            descendants[base].add(cls)

    def slot_word(owner, body):
        """`~` for a destructor slot, the one real method word a member of
        `owner`'s lineage gives the body, else None (unnamed, placeholder,
        pure stub or ambiguous)."""
        named = rows_of(body)
        if named and all(n.startswith(("??_G", "??_E", "??1")) for _, _, n in named):
            return "~"
        lineage = {owner, *ancestors(owner)}
        words = {m for c, m, _ in named if c in lineage and good_word(m, "function")}
        return words.pop() if len(words) == 1 else None

    def order_word(base, i):
        """(word, why) for slot i of `base` from Zero Hour declaration order;
        (None, reason) unless the target brackets it. BFME inserts and drops
        virtuals, so the order is trusted only locally: the nearest named
        slots a < i < b (named in the base's table or any table deriving from
        it; destructors as `~`; the table start counts as a = -1) must carry
        words that occur once in the computed order, at positions exactly
        b - a apart -- no virtual was inserted or dropped between them -- and
        the slot takes the word at a's position plus (i - a). Each table is
        anchored on its own (a mislabelled table then fails its own distance
        check instead of poisoning the rest); tables that anchor different
        words, or name slot i itself otherwise, refuse it."""
        if (base, i) in verdicts:
            return verdicts[base, i]
        verdicts[base, i] = verdict = _order_word(base, i)
        return verdict

    def _order_word(base, i):
        order = zh_slot_order(tree, base, memo)
        if not order:
            return None, "no Zero Hour declaration order for the base"
        words, reasons, at_slot = {}, collections.Counter(), set()
        for owner in sorted({base, *descendants[base]}):
            named = {}
            for j, body in enumerate(slots[owner][:len(slots[base])]):
                word = slot_word(owner, body)
                if word is not None:
                    named[j] = word
            if i in named:
                at_slot.add(named.pop(i))
            word, why = anchor_word(order, named, i)
            if word:
                words.setdefault(word, f"{owner} table: {why}")
            else:
                reasons[why] += 1
        if not words:
            return None, reasons.most_common(1)[0][0]
        if len(words) > 1 or at_slot - {"~", *words}:
            return None, "tables anchor or name the slot differently"
        return next(iter(words.items()))

    def anchor_word(order, named, i):
        lower = max((j for j in named if j < i), default=-1)
        upper = min((j for j in named if j > i), default=None)
        if upper is None:
            return None, "no named slot above it to anchor the Zero Hour order"

        def position(j):
            if j < 0:
                return -1
            hits = [k for k, w in enumerate(order) if w == named[j]]
            return hits[0] if len(hits) == 1 else None

        lo, hi = position(lower), position(upper)
        if lo is None or hi is None:
            return None, "an anchor word is absent from or repeated in the Zero Hour order"
        if hi - lo != upper - lower:
            return None, "a virtual was inserted or dropped between the anchors"
        word = order[lo + (i - lower)]
        if word == "~" or not good_word(word, "function"):
            return None, "Zero Hour order names no usable word for the slot"
        below = "table start" if lower < 0 else f"slot {lower} {named[lower]}"
        return word, (f"anchored by {below} and slot {upper} {named[upper]} "
                      f"(Zero Hour positions {lo}..{hi})")

    for cls, table in sorted(slots.items()):
        bases = {b: via for b, via in ancestors(cls).items() if b in slots}
        for i, body in enumerate(table):
            for rcls, method, name in rows_of(body):
                if rcls != cls or not method or not rename.is_placeholder(method, "function"):
                    continue
                rows = [r for r in tree.rows_by_rva.get(body, []) if r["name"] == name]
                if not rows:
                    col.skips["vtable-slot: generated or protected row"] += 1
                    continue
                if tree.function_refusal(rows[0], method):
                    col.skips[f"vtable-slot: {tree.function_refusal(rows[0], method)}"] += 1
                    continue
                found, pure = {}, set()
                for base, via in sorted(bases.items()):
                    if i >= len(slots[base]) or slots[base][i] == body:
                        continue
                    named = rows_of(slots[base][i])
                    # the base slot's own virtual: a member of the base or one
                    # of its ancestors (a free `_purecall` stub names nothing)
                    lineage = {base, *ancestors(base)}
                    words = {m for c, m, _ in named if c in lineage and good_word(m, "function")}
                    if len(words) == 1 and len({m for _, m, _ in named if m}) == 1:
                        found.setdefault(words.pop(), (base, via, slots[base][i]))
                    elif named and all(c is None for c, _, _ in named):
                        pure.add(base)
                if not found and pure:
                    order_hit = None
                    for base in sorted(pure):
                        word, why = order_word(base, i)
                        if word:
                            order_hit = (base, word, why)
                            break
                        col.skips["vtable-order: " + why] += 1
                    if order_hit:
                        base, word, why = order_hit
                        chain = [base, *ancestors(base)]
                        cite = next((zh_virtual[b][word] for b in chain if word in zh_virtual.get(b, {})), "")
                        detail = {"slot": i, "vftable": f"??_7{cls}@@6B@", "base": f"{base}::{word}",
                                  "base_rva": f"0x{slots[base][i]:08X}", "base_via": bases[base],
                                  "zh_virtual": cite or "none", "zh_order": why,
                                  "note": "base slot is pure; word from Zero Hour declaration order between "
                                          "two named anchor slots; slot order is not a name proof"}
                        col.add("function", name, body, method, word, "vtable-order", HINT, detail,
                                inferred_only=method in tree.inferred)
                        continue
                if not found:
                    reason = ("base slot is a pure-virtual stub" if pure else
                              "no known base class" if not bases else
                              "slot past every base table" if all(i >= len(slots[b]) for b in bases) else
                              "base slot unnamed or the same body")
                    col.skips["vtable-slot: " + reason] += 1
                    continue
                for word, (base, via, base_body) in sorted(found.items()):
                    chain = [base, *[b for b in ancestors(base)]]
                    cite = next((zh_virtual[b][word] for b in chain if word in zh_virtual.get(b, {})), "")
                    detail = {"slot": i, "vftable": f"??_7{cls}@@6B@", "base": f"{base}::{word}",
                              "base_rva": f"0x{base_body:08X}", "base_via": via,
                              "zh_virtual": cite or "none",
                              "note": "overrides the base slot's method; slot order is not a name proof"}
                    col.add("function", name, body, method, word, "vtable-slot", HINT, detail,
                            inferred_only=method in tree.inferred)


# ---------------------------------------------------------------- main

def generate(root=ROOT, kinds=KINDS, sweep_dirs=("build",), min_score=4.0, slots=None):
    tree = Tree(root)
    col = Collector(tree)
    if "wb" in kinds:
        wb_lane(tree, col, min_score)
    zh_found = zh_lane(tree, col, sweep_dirs) if "zh" in kinds else zh_unique_donors(tree, sweep_dirs)
    if "bfme1" in kinds:
        bfme1_lane(tree, col, sweep_dirs, zh_found)
    if "string" in kinds:
        string_lane(tree, col)
    if "poolkey" in kinds:
        poolkey_lane(tree, col)
    if "vtable" in kinds:
        vtable_lane(tree, col, slots)
    return col.finish(), tree.notes, col.skips


# rename.py's canonical evidence kind -> this tool's evidence kind
RENAME_KINDS = {"wb": "wb-assert", "zh": "zh-body", "bfme1": "bfme1-body"}
_GRADED = {}


def graded(root, sweep_dirs=("build",), min_score=4.0):
    """generate() over every lane, cached per process until a ledger it reads changes."""
    root = Path(root)
    stamp = tuple((p, (root / p).stat().st_mtime_ns if (root / p).exists() else None)
                  for p in ("reverse/functions.csv", "reverse/name_basis.csv", "reverse/wb_name_leads.csv",
                            "reverse/string_xrefs.tsv"))
    key = (str(root.resolve()), tuple(map(str, sweep_dirs)), float(min_score))
    if key not in _GRADED or _GRADED[key][0] != stamp:
        _GRADED[key] = (stamp, generate(root, KINDS, sweep_dirs, min_score))
    return _GRADED[key][1]


def proof(root, basis_kind, kind, current, candidate, rva=None, *, sweep_dirs=("build",), min_score=4.0):
    """Why this tool does not grade `current -> candidate` as proof by
    rename.py's `canonical:<basis_kind>` (a list of reasons; empty means
    proven). One grading for the lane that proposes canonical names and for
    tools/rename.py's check_canonical that lands them, so a hint can never be
    landed as a permanent canonical name. `kind` is function (`rva` the
    row's address) or class (`current` the class token)."""
    evidence_kind = RENAME_KINDS.get(basis_kind)
    if evidence_kind is None:
        return [f"canonical:{basis_kind} is not graded by tools/name_evidence.py"]
    if kind not in ("function", "class"):
        return [f"tools/name_evidence.py grades functions and classes, not a {kind}"]
    candidates, notes, _ = graded(root, sweep_dirs, min_score)
    lane = evidence_kind.split("-")[0]
    found = [c for c in candidates if c.kind == kind and c.evidence_kind.split("-")[0] == lane
             and c.current == current and c.candidate == candidate
             and (kind == "class" and c.key == current or kind == "function" and c.rva == rva)]
    if any(c.strength == CANONICAL and c.evidence_kind == evidence_kind for c in found):
        return []
    if found:
        why = [v for c in found for k in ("weak", "caution", "conflict") for v in [c.detail.get(k)] if v]
        return [f"{'/'.join(sorted({c.evidence_kind for c in found}))} grades it a hint"
                + (f": {'; '.join(why)}" if why else "")]
    return [f"tools/name_evidence.py has no {evidence_kind} candidate {current} -> {candidate}"
            + (f" at 0x{rva:08X}" if rva is not None else "")] + [n for n in notes if n.startswith(lane)]


def write(path, candidates):
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text("\t".join(COLUMNS) + "\n" + "".join(c.line() + "\n" for c in candidates), encoding="utf-8")
    os.replace(tmp, path)


def summary(candidates):
    counts = collections.Counter((c.evidence_kind, c.kind, c.strength) for c in candidates)
    return [f"  {ek:<12} {kind:<9} {strength:<9} {n}" for (ek, kind, strength), n in sorted(counts.items())]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n", 1)[0])
    ap.add_argument("--root", default=str(ROOT), help=argparse.SUPPRESS)
    ap.add_argument("--out", default=OUT, help=f"output TSV (default {OUT}, relative to the repo)")
    ap.add_argument("--sweep-dir", action="append", default=None,
                    help="directory holding zh_sweep/ and bfme1_sweep/ caches (default build/; repeatable)")
    ap.add_argument("--wb-min-score", type=float, default=4.0, help="WB pairing score a proof needs (default 4)")
    ap.add_argument("--kinds", default=",".join(KINDS), help=f"lanes to run (default {','.join(KINDS)})")
    args = ap.parse_args(argv)
    kinds = [k for k in args.kinds.split(",") if k]
    unknown = set(kinds) - set(KINDS)
    if unknown:
        ap.error(f"unknown kind(s): {', '.join(sorted(unknown))}")
    candidates, notes, skips = generate(args.root, kinds, args.sweep_dir or ["build"], args.wb_min_score)
    out = Path(args.out)
    if not out.is_absolute():
        out = Path(args.root) / out
    write(out, candidates)
    for note in notes:
        print(f"note: {note}")
    print(f"{len(candidates)} candidate(s) -> {out}")
    print("\n".join(summary(candidates)))
    if skips:
        print("skipped:")
        for reason, n in sorted(skips.items()):
            print(f"  {reason}: {n}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
