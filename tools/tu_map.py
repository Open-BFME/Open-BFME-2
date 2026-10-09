#!/usr/bin/env python3
"""Which original source file (TU) each retail function and data range came from.

The ledger records where a body sits in THIS tree, which is mostly one file per
function. Retail was linked from real translation units, and a TU's functions
sit next to each other in .text in the order the linker took the objects. This
tool recovers that structure from evidence and writes it to `tu_map.csv` next to
the ledger, so the skeleton generator (tools/tu_skeleton.py) and the ownership
invariant (tools/tu_ownership.py) work from one table instead of a guess each.

Signals, strongest first (one letter each in the `by` and `evidence` columns):

  F  the function references a `__FILE__` string naming a .cpp (assert/debug
     paths survive in retail); the string IS the TU.
  Z  `Class::method(` is defined in that file of the Zero Hour reference (an
     out-of-line definition at file scope: balanced parameters, then a body
     `{`; a call such as `Base::f(x);` or a data initializer is not one).
  S  every ZH definition of `Class::` sits in one .cpp: the class's site.
  N  naming convention `<dir>/<Class>.cpp` (ModuleData suffix stripped); used
     only inside the address cluster an F/Z/S anchor or a run of N rows forms.
  U  the row's own naming hint (N, never F/Z/S) names a small TU whose rows
     interleave with an anchored TU's, so the two are one file (several
     classes in one .cpp) and the row takes the anchored TU's name.
  C  address contiguity: the nearest assigned rows on both sides agree and are
     within 0x3000 bytes (retail object order keeps a TU contiguous).
  K  placeholder-class propagation (`??1Rva...` follows its `??_GRva...`).
  X  data: every function that references the item is assigned to one TU.

The `evidence` column keeps each row's own pre-clustering F/Z/S/N values, so a
row's TU can always be checked against what its own name and strings say.

Class name alone is not a TU key: repo-wide only 42% of rows agree between Z and
N, and header-inline bodies (??_G, friend_new*, *ModuleData ctors) are emitted as
COMDATs in whichever TU used them first. A naming hint outside its TU's main
address cluster is therefore `displaced`, never assigned.

Clusters are merged (U) only when at most one of them is anchored by F/Z/S. Two
TUs that F/Z/S name differently are two files; when their rows interleave, both
are noncontiguous and nothing in them is approved. A row's own F/Z/S anchor is
never renamed by a merge, and a row whose TU contradicts its own F (or, without
F, both its Z and S) is never approved: it is marked `contradicted`.

Unconverted functions are mapped too. Every function start in
ghidra_functions.csv without a ledger row is a `code-unledgered` row with an
empty `source`; generated placeholder rows (gen_small, gen_asm) keep their
ledger source but carry no usable name. Neither has a name to read, so only the
name-free signals reach them: F (the body pushes a `__FILE__` path) and C (it
sits in a run bracketed by one TU). That is the routing table for new work:
tools/tu_ownership.py (A2/A3) and `tools/repair_queue.py dest` read the TU of
an address through `tu_at()` before anything is converted there. The EH
funclets linked after all of .text (`.text$x`, about a third of Ghidra's
functions) have neither signal and stay unmapped.

Every known code body is written, with or without a TU (`confidence` empty for
a body no signal reaches), so the map carries the extents `tu_at()` needs:

  * an address with a row gets that row, whatever its confidence;
  * an address inside a known body inherits that body's TU and confidence (a
    displaced or unassigned body stays so: nothing approves its interior);
  * an address in no known body is padding or an undiscovered body. Padding
    (retail 0xCC) gets no answer. Otherwise C from its brackets applies, and is
    approved only on boundary evidence: the retail image shows the address is
    the first non-padding byte after the body below it, i.e. where an
    unsplit function would start. Without the image it is at most proposed.

Confidence:
  approved  the TU's main cluster holds at least one F/Z/S anchor, the row is
            assigned by F/Z/S/N/U or bracketed (C) by approved rows, its own
            F/Z/S do not contradict the TU, and no row that could be approved
            for a different TU sits inside the TU's address span (a TU that is
            not contiguous in retail is not trusted). A row "could be approved"
            when its TU is anchored and it is assigned by F/Z/S/N/U/C; a K row,
            or a row of a TU no F/Z/S anchors (a naming hint for a class this
            repo named, alone), never can, so it does not break its host's
            span. A run of C rows is approved exactly when the two rows that
            bracket the whole run are.
  proposed  assigned, but by N/K only, by brackets that are not approved, in a
            non-contiguous span, or contradicted. The queue for investigation.
  displaced a naming hint sat outside its TU's cluster (COMDAT pile).
  (empty)   a known body no signal reaches; it has no TU.

The output is a pure function of the ledger, ghidra_functions.csv,
string_xrefs.tsv, data_xrefs.tsv and the ZH tree: rerunning on unchanged inputs
writes the same bytes. Never edit tu_map.csv by hand; regenerate it. Writing it
also writes `tu_map.inputs.sha256` (sha256sum-like, line endings normalised):
the hashes of those inputs, of this tool and of the map, and the ZH tree's
identity -- its git tree id (and commit) in a clean default checkout, else a
hash of its .cpp files -- which `--check-fresh` compares in about a second.

Usage:
  python3 tools/tu_map.py                write tu_map.csv (+ fingerprint), print a summary
  python3 tools/tu_map.py --check        exit 1 when tu_map.csv differs from a rebuild
  python3 tools/tu_map.py --check-fresh  exit 1 when an input changed since tu_map.csv was written
  python3 tools/tu_map.py --validate REV score approved predictions against independent evidence:
                                         each approved row's own F/Z/S, and the F/Z/S of rows
                                         landed since REV at addresses a map built from REV's
                                         ledger routed
  python3 tools/tu_map.py --dir PREFIX   summary for one directory's rows
  --zh DIR                               the ZH GeneralsMD/Code tree (default: the Open-BFME-1
                                         submodule's); must hold GameEngine/
"""
import argparse
import bisect
import collections
import csv
import hashlib
import io
import itertools
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAP = 0x3000          # max distance between bracketing anchors (C)
UNION_SPAN = 0x2000   # clusters this small that interleave are one TU
PAD = 0xCC            # MSVC fills between functions with int3
COLUMNS = ["rva", "size", "kind", "tu", "confidence", "by", "evidence", "source"]
APPROVABLE = {"F", "Z", "S", "N", "U"}
SPAN_BREAKERS = APPROVABLE | {"C"}
FINGERPRINTED = ("functions.csv", "ghidra_functions.csv", "string_xrefs.tsv", "data_xrefs.tsv")


class Layout:
    """Where this repo keeps its ledger, sources, reference tree and retail image."""

    def __init__(self, root, zh=None):
        self.root = Path(root)
        if (self.root / "targets/game/reverse/functions.csv").exists():
            self.reverse = "targets/game/reverse"   # Open-BFME-1
            self.src = "game/"
            self.zh = self.root / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
            self.image = self.root / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
        else:
            self.reverse = "reverse"                # Open-BFME-2
            self.src = "Code/"
            self.zh = self.root / ("reference/open-bfme-1/inputs/reference/"
                                   "CnC_Generals_Zero_Hour/GeneralsMD/Code")
            self.image = self.root / "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
        self.zh_custom = bool(zh)
        if zh:
            self.zh = Path(zh)

    def zh_problem(self):
        """Why self.zh is not a ZH GeneralsMD/Code tree, or None."""
        if not self.zh.is_dir():
            return f"no ZH tree at {self.zh} (initialise the submodule or pass --zh GeneralsMD/Code)"
        if not (self.zh / "GameEngine").is_dir():
            return f"{self.zh} is not a ZH GeneralsMD/Code tree (no GameEngine/ in it)"
        return None

    def path(self, name):
        return self.root / self.reverse / name

    @property
    def out(self):
        return self.path("tu_map.csv")

    @property
    def fingerprint(self):
        return self.path("tu_map.inputs.sha256")


def read_csv(path):
    if not path.exists():
        return []
    return list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8", errors="replace"), newline="")))


CTOR = re.compile(r"^\?\?(_G|_E|0|1)([A-Za-z_]\w*)@@")
METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
PLACEHOLDER = re.compile(r"^(Rva|rva|Gen|gen|Sub|sub|FUN_)[0-9A-Fa-f_]")
COMDAT = re.compile(r"^\?\?_[GE]|^\?friend_new|^\?\?[01]\w*ModuleData@@")
# Comments and literals, so a commented-out or quoted `X::y(` is never read as code.
CPP_NOISE = re.compile(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.S)
# An out-of-line definition opens at file scope: column 0, no statement keyword, no
# assignment or call before `Class::method`, then its `(` (on that line or a later one).
ZH_HEAD = re.compile(r"^(?!(?:return|else|if|while|for|do|switch|case|delete|new|throw|goto)\b)(?=[A-Za-z_])"
                     r"[^;(){}=\n]*?\b([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*)(?=\s*(?:\(|$))")
PUNCT = re.compile(r"[(){};]")


def demangle(name):
    m = CTOR.match(name)
    if m:
        return m.group(2), {"0": m.group(2), "1": "~" + m.group(2)}.get(m.group(1), "?" + m.group(1))
    m = METHOD.match(name)
    if m:
        return m.group(2), m.group(1)
    return None, name


def _blank(m):
    """A comment becomes spaces (its line breaks kept); a literal keeps its quotes, not its text."""
    text = m.group(0)
    if text[0] in "\"'":
        return text[0] + " " * (len(text) - 2) + text[-1]
    return re.sub(r"[^\n]", " ", text)


def zh_definitions(text):
    """(class, method) of each out-of-line definition in one ZH .cpp, in file order.

    A definition is a ZH_HEAD head, a balanced parameter list and then -- past `const`,
    `throw(...)` or a constructor's initializer list -- a body `{`. A `;` first makes it
    a call (`Base::f(` over several lines), a declaration or a data initializer
    (`BezierSegment::s_bezBasisMatrix( ... );`); a `}` first, a fragment."""
    code = CPP_NOISE.sub(_blank, text)     # same length and line breaks as `text`
    at = 0
    for raw, line in zip(text.split("\n"), code.split("\n")):
        start, at = at, at + len(line) + 1
        lead = len(line) - len(line.lstrip()) if raw.startswith("/") else 0   # `/*static*/ void X::f(`
        m = ZH_HEAD.match(line[lead:])
        if not m:
            continue
        i = start + lead + m.end()
        while i < len(code) and code[i].isspace():
            i += 1
        if i >= len(code) or code[i] != "(":
            continue
        depth = 0
        for tok in PUNCT.finditer(code, i):
            c = tok.group()
            if c in "()":
                depth += 1 if c == "(" else -1
            else:                          # the first brace or `;` decides, inside parentheses or not
                if c == "{" and depth == 0:
                    yield m.group(1), m.group(2)
                break


class Paths:
    """Map a reference path onto this tree's spelling (case-insensitive)."""

    def __init__(self, layout, sources):
        self.layout = layout
        self.dirs = {}
        for s in sorted(sources):
            parts = s.split("/")
            for i in range(1, len(parts)):
                self.dirs.setdefault("/".join(parts[:i]).lower(), "/".join(parts[:i]))
        self.files = {s.lower(): s for s in sorted(sources)}

    def repo(self, code_rel):
        """`GameEngine/Source/X/Y.cpp` (relative to a Code/ root) -> repo path."""
        rel = (self.layout.src + code_rel.replace("\\", "/").lstrip("/"))
        if rel.lower() in self.files:
            return self.files[rel.lower()]
        parts = rel.split("/")
        for i in range(len(parts) - 1, 0, -1):
            hit = self.dirs.get("/".join(parts[:i]).lower())
            if hit:
                return hit + "/" + "/".join(parts[i:])
        return rel


def zh_index(layout, paths):
    meth, sites = {}, collections.defaultdict(set)
    if not layout.zh.exists():
        return meth, {}
    for dp, dn, fn in sorted(os.walk(layout.zh)):
        dn.sort()
        for f in sorted(fn):
            if not f.lower().endswith(".cpp"):
                continue
            p = Path(dp) / f
            rel = paths.repo(p.relative_to(layout.zh).as_posix())
            try:
                text = p.read_text(encoding="latin-1")
            except OSError:
                continue
            for c, m in zh_definitions(text):
                meth.setdefault((c, m), rel)
                sites[c].add(rel)
    return meth, {c: next(iter(v)) for c, v in sites.items() if len(v) == 1}


def file_strings(layout, paths, owner):
    out = {}
    path = layout.path("string_xrefs.tsv")
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        text, _, refs = line.rpartition("\t")
        m = re.search(r"[\\/]Code[\\/](.+\.(?:cpp|c))$", text, re.I)
        if not m or not refs.startswith("0x"):
            continue
        tu = paths.repo(m.group(1))
        for ref in refs.split(","):
            try:
                o = owner(int(ref, 16))
            except ValueError:
                continue
            if o is not None:
                out.setdefault(o, tu)
    return out


def same(a, b):
    return bool(a and b and a.lower() == b.lower())


def contradicts(tu, f=None, z=None, s=None):
    """Does a row's own pre-clustering evidence name a TU other than `tu`? F is the TU
    itself; without F, a row is contradicted only when neither its Z nor its S is `tu`."""
    if not tu:
        return False
    if f:
        return not same(f, tu)
    hard = [x for x in (z, s) if x]
    return bool(hard) and not any(same(x, tu) for x in hard)


def anchors(evidence):
    """{"F": tu, "Z": tu, "S": tu, "N": tu} from a tu_map.csv `evidence` cell."""
    out = {}
    for token in (evidence or "").split():
        k, eq, v = token.partition("=")
        if eq and k in ("F", "Z", "S", "N") and k not in out:
            out[k] = v
    return out


C_SPAN = re.compile(r"\bC=0x([0-9A-Fa-f]+)\.\.0x([0-9A-Fa-f]+)")


def disputed(m, t):
    """The F/Z/S anchor that contradicts the TU of `t` (a tu_at answer from load() map `m`):
    its own (its host body's, for an interior address) or that of any row its C evidence
    brackets on, followed through a run. None when no anchor does. A map built by these
    rules approves nothing disputed; an older map can."""
    seen, todo = set(), [t]
    while todo:
        r = todo.pop()
        ev = anchors(r["evidence"])
        if contradicts(t["tu"], ev.get("F"), ev.get("Z"), ev.get("S")):
            return f"{r['rva']} " + " ".join(f"{k}={ev[k]}" for k in "FZS" if ev.get(k))
        for span in C_SPAN.finditer(r["evidence"]):
            for x in span.groups():
                if int(x, 16) not in seen:
                    seen.add(int(x, 16))
                    todo.extend(q for q in m.get(int(x, 16), ()) if q["kind"].startswith("code"))
    return None


def approved_tu(m, t):
    """The file a row at the address of `t` (a tu_at answer from load() map `m`) belongs in,
    or None: t's TU when t is approved and no F/Z/S anchor disputes it. The one predicate
    tu_ownership (A2/A3) holds a row to and repair_queue dest routes a new row by."""
    if t and t["confidence"] == "approved" and t["tu"] and not disputed(m, t):
        return t["tu"]
    return None


def evidence_rows(layout, ledger=None):
    """Every known code body -- ledger rows, then Ghidra function starts the ledger lacks --
    with its own pre-clustering evidence (F, Z, S, N). `ledger` (rows of a functions.csv)
    defaults to the working tree's."""
    ledger = read_csv(layout.path("functions.csv")) if ledger is None else ledger
    rows, seen = [], set()
    for r in ledger:
        if "gen-alias" in (r.get("notes") or "") or not (r.get("target_rva") or "").startswith("0x"):
            continue
        try:
            rva = int(r["target_rva"], 16)
        except ValueError:
            continue
        if rva in seen:
            continue                       # one identity per address; first row wins
        seen.add(rva)
        try:
            size = int(r["target_size"])
        except (TypeError, ValueError):
            size = 0
        rows.append(dict(rva=rva, size=size, kind="code", name=r["name"], source=r["source"]))
    for g in read_csv(layout.path("ghidra_functions.csv")):
        try:
            rva = int(g["rva"], 16)
        except (KeyError, ValueError):
            continue
        if rva not in seen and rva >= 0x1000:
            seen.add(rva)
            rows.append(dict(rva=rva, size=int(g.get("size") or 0), kind="code-unledgered", name="", source=""))
    rows.sort(key=lambda r: r["rva"])
    starts = [r["rva"] for r in rows]

    def owner(rva):
        i = bisect.bisect_right(starts, rva) - 1
        if i >= 0 and rva < starts[i] + max(rows[i]["size"], 1):
            return starts[i]
        return None

    paths = Paths(layout, {r["source"] for r in rows if r["source"]})
    zmeth, zsite = zh_index(layout, paths)
    F = file_strings(layout, paths, owner)
    for r in rows:
        r["cls"], r["meth"] = demangle(r["name"]) if r["name"] else (None, None)
        cls = r["cls"]
        r["F"] = F.get(r["rva"])
        r["Z"] = zmeth.get((cls, r["meth"])) if cls else None
        r["S"] = zsite.get(cls) if cls and not COMDAT.match(r["name"]) else None
        base = re.sub(r"ModuleData$", "", cls or "")
        r["N"] = (os.path.dirname(r["source"]) + "/" + base + ".cpp") if base and r["source"] \
            and not PLACEHOLDER.match(base) else None
        r["hard"] = r["F"] or r["Z"] or r["S"]
        r["hint"] = r["hard"] or r["N"]
        r["C"] = r["K"] = None
    return rows


def build(layout, ledger=None):
    rows = evidence_rows(layout, ledger)

    # Main address cluster per hinted TU; hints outside it are displaced COMDATs.
    by_hint = collections.defaultdict(list)
    for r in rows:
        if r["hint"]:
            by_hint[r["hint"].lower()].append(r)
    main, anchored = {}, set()
    for key, members in by_hint.items():
        clusters = [[members[0]]]
        for a, b in zip(members, members[1:]):
            if b["rva"] - a["rva"] > GAP:
                clusters.append([])
            clusters[-1].append(b)
        best = max(clusters, key=lambda c: (sum(1 for x in c if x["hard"]),
                                            sum(1 for x in c if not COMDAT.match(x["name"])), len(c)))
        if not any(x["hard"] or not COMDAT.match(x["name"]) for x in best):
            continue
        if any(x["hard"] and x["hard"].lower() == key for x in best):
            anchored.add(key)
        for x in best:
            main[id(x)] = key
    for r in rows:
        key = r["hint"].lower() if r["hint"] else None
        r["A"] = r["hint"] if (r["F"] or (key and main.get(id(r)) == key)) else None
        r["disp"] = bool(r["hint"] and not r["A"])

    # TUs whose small clusters interleave are one TU (one file, several classes) --
    # unless both are anchored: two TUs F/Z/S name differently are two files, and
    # interleaving makes both noncontiguous instead of renaming one into the other.
    span = {}
    for r in rows:
        if r["A"]:
            k = r["A"].lower()
            lo, hi = span.get(k, (r["rva"], r["rva"]))
            span[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    parent = {k: k for k in span}

    def find(k):
        while parent[k] != k:
            k = parent[k]
        return k
    order = sorted(span, key=lambda k: (span[k][0], k))
    for i, a in enumerate(order):
        for b in order[i + 1:]:
            if span[b][0] > span[a][1]:
                break
            if span[a][1] - span[a][0] > UNION_SPAN or span[b][1] - span[b][0] > UNION_SPAN:
                continue
            ra, rb = find(a), find(b)
            if ra == rb or (ra in anchored and rb in anchored):
                continue
            keep, drop = (ra, rb) if (ra in anchored or rb not in anchored) else (rb, ra)
            parent[drop] = keep
    for r in rows:
        if r["A"] and not r["hard"]:        # a row's own F/Z/S anchor is never renamed by a merge
            r["A"] = spelled[find(r["A"].lower())]

    # Contiguity (C) and placeholder-class propagation (K), iterated.
    for _ in range(3):
        last = None
        prev = {}
        for r in rows:
            prev[id(r)] = last
            if r["A"]:
                last = r
        nxt = None
        for r in reversed(rows):
            a = prev[id(r)]
            if not r["A"] and not r["disp"] and a and nxt and a["A"] == nxt["A"] \
                    and nxt["rva"] - a["rva"] <= GAP:
                r["A"] = r["C"] = a["A"]
                r["Cvia"] = (a, nxt)
            if r["A"]:
                nxt = r
        votes = collections.defaultdict(collections.Counter)
        for r in rows:
            if r["A"] and r["cls"]:
                votes[r["cls"]][r["A"]] += 1
        for r in rows:
            if not r["A"] and not r["disp"] and r["cls"] and PLACEHOLDER.match(r["cls"]) \
                    and len(votes.get(r["cls"], ())) == 1:
                r["A"] = r["K"] = next(iter(votes[r["cls"]]))

    # Classification from the row's own evidence; U when its naming hint was merged.
    for r in rows:
        a = r["A"]
        r["by"] = ("F" if same(r["F"], a) else "Z" if same(r["Z"], a) else "S" if same(r["S"], a) else
                   "C" if r["C"] else "K" if r["K"] else "N" if same(r["N"], a) else "U" if a else "")
        r["contra"] = contradicts(a, r["F"], r["Z"], r["S"])

    # Confidence. Retail object order: a TU must be contiguous in .text.
    assigned = [r for r in rows if r["A"]]
    lo_hi = {}
    for r in assigned:
        k = r["A"].lower()
        lo, hi = lo_hi.get(k, (r["rva"], r["rva"]))
        lo_hi[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    idx = [r["rva"] for r in assigned]
    roots = {find(k) for k in anchored if k in parent}
    # Only a row that could be approved contradicts a span: one of an anchored TU,
    # assigned by F/Z/S/N/U/C. A K row or an unanchored TU's naming hint never can.
    broken = set()
    for k, (lo, hi) in lo_hi.items():
        i, j = bisect.bisect_left(idx, lo), bisect.bisect_right(idx, hi)
        if any(x["A"].lower() != k and x["A"].lower() in roots and x["by"] in SPAN_BREAKERS
               for x in assigned[i:j]):
            broken.add(k)
    for r in rows:
        k = r["A"].lower() if r["A"] else None
        if not k:
            r["conf"] = "displaced" if r["disp"] else ""
            continue
        ok = k in roots and k not in broken and r["by"] in APPROVABLE and not r["contra"]
        r["conf"] = "approved" if ok else "proposed"
    # C rows inherit approval only from two approved brackets. Within a run the
    # upper bracket is the next C row up, so walk down from the top until the
    # whole run resolves to its two ends (a fixed pass count left long runs
    # half-approved).
    changed = True
    while changed:
        changed = False
        for r in reversed(rows):
            if r["by"] == "C" and r["conf"] == "proposed":
                a, b = r["Cvia"]
                if a["conf"] == b["conf"] == "approved" and r["A"].lower() not in broken:
                    r["conf"] = "approved"
                    changed = True

    out = []
    for r in rows:
        ev = []
        for s in "FZSN":
            if r[s]:
                ev.append(f"{s}={r[s]}")
        if r["C"]:
            a, b = r["Cvia"]
            ev.append(f"C=0x{a['rva']:08X}..0x{b['rva']:08X}")
        if r["K"]:
            ev.append(f"K={r['cls']}")
        if r["A"] and r["A"].lower() in broken:
            ev.append("noncontiguous")
        if r["contra"]:
            ev.append("contradicted")
        out.append({"rva": f"0x{r['rva']:08X}", "size": r["size"], "kind": r["kind"],
                    "tu": r["A"] or "", "confidence": r["conf"], "by": r["by"] or "-",
                    "evidence": " ".join(ev), "source": r["source"]})
    out.extend(data_rows(layout, rows))
    out.sort(key=lambda d: (int(d["rva"], 16), d["kind"]))
    return out


def data_rows(layout, rows):
    """A data item belongs to the TU every one of its referencing functions is in."""
    path = layout.path("data_xrefs.tsv")
    if not path.exists():
        return []
    starts = [r["rva"] for r in rows]
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    out = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines()[1:]:
        f = line.split("\t")
        if len(f) < 8 or not f[0].startswith("0x"):
            continue
        tus, confs = set(), set()
        for c in filter(None, f[7].split(",")):
            i = bisect.bisect_right(starts, int(c, 16)) - 1
            r = rows[i] if i >= 0 else None
            if not r or not r["A"] or int(c, 16) >= r["rva"] + max(r["size"], 1):
                tus.add(None)
                continue
            tus.add(r["A"].lower())
            confs.add(r["conf"])
        if len(tus) != 1 or None in tus:
            continue
        tu = spelled[next(iter(tus))]
        out.append({"rva": f[0], "size": f[2], "kind": "data:" + f[1], "tu": tu,
                    "confidence": "approved" if confs == {"approved"} else "proposed",
                    "by": "X", "evidence": f"X={len(f[7].split(','))}refs", "source": ""})
    return out


def render(out):
    buf = io.StringIO()
    w = csv.DictWriter(buf, COLUMNS, lineterminator="\n")
    w.writeheader()
    w.writerows(out)
    return buf.getvalue()


def load(root=ROOT):
    """rva -> list of tu_map rows (code first). Empty when no map exists."""
    m = collections.defaultdict(list)
    for r in read_csv(Layout(root).out):
        m[int(r["rva"], 16)].append(r)
    return m


# ---------------------------------------------------------------- routing an address
class Image:
    """Retail bytes by RVA through the PE section table, read on first use."""

    def __init__(self, path):
        self.path, self._data, self._secs = Path(path), None, []

    @classmethod
    def open(cls, path):
        """An Image, or None when the file is absent (tu_at then never claims a boundary)."""
        return cls(path) if path is not None and Path(path).is_file() else None

    def read(self, rva, n):
        if self._data is None:
            data = self.path.read_bytes()
            pe = struct.unpack_from("<I", data, 0x3C)[0]
            table = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
            for i in range(struct.unpack_from("<H", data, pe + 6)[0]):
                vsize, va, rsize, raw = struct.unpack_from("<IIII", data, table + 40 * i + 8)
                self._secs.append((va, min(vsize, rsize), raw))
            self._data = data
        for va, size, raw in self._secs:
            if va <= rva and rva + n <= va + size:
                return self._data[raw + rva - va:raw + rva - va + n]
        return None


def _int(value):
    try:
        return int(value or 0)
    except ValueError:
        return 0


class Index:
    """tu_at's view of a load() map: the assigned code rows (C brackets) and the extent of
    every known body (code rows of any confidence, a body with no TU included)."""

    def __init__(self, m, image=None):
        got = sorted(((rva, r) for rva, rs in m.items() for r in rs
                      if r["kind"].startswith("code") and r["tu"] and r["confidence"] in ("approved", "proposed")),
                     key=lambda x: x[0])
        self.starts, self.rows = [x[0] for x in got], [x[1] for x in got]
        size = {}
        for rva, rs in m.items():
            for r in rs:
                if r["kind"].startswith("code"):
                    size[rva] = max(size.get(rva, 1), _int(r.get("size")))
        self.lo = sorted(size)
        self.hi = [s + size[s] for s in self.lo]
        self.reach = list(itertools.accumulate(self.hi, max))   # furthest end of any body starting at or before
        self.image = image

    def host(self, rva):
        """Start of the latest-starting known body that contains RVA, or None."""
        i = bisect.bisect_right(self.lo, rva) - 1
        while i >= 0 and self.reach[i] > rva:
            if self.hi[i] > rva:
                return self.lo[i]
            i -= 1
        return None

    def gap(self, rva):
        """For an RVA in no known body: "padding", "start" (the first non-padding byte after the
        body below it, where an unsplit function begins), "inside" (past such a start), or None
        when the image cannot say."""
        i = bisect.bisect_right(self.lo, rva) - 1
        if self.image is None or i < 0 or self.reach[i] > rva:
            return None
        floor = self.reach[i]
        got = self.image.read(floor, rva - floor + 1)
        if not got:
            return None
        if got[-1] == PAD:
            return "padding"
        return "start" if all(b == PAD for b in got[:-1]) else "inside"


def code_index(m, image=None):
    """tu_at's index of a load() map; pass Image.open(Layout(root).image) for boundary evidence."""
    return Index(m, image)


def tu_at(m, rva, index=None):
    """The code row of `m` (a load() map) for RVA, or None.

    An address the map has a code row for gets that row, whatever its confidence
    (empty for a known body no signal reaches). An address inside a known body
    inherits that body's TU and confidence: nothing approves the interior of a
    displaced, proposed or unassigned body. An address in no known body gets no
    answer when the retail image shows padding; otherwise C on the same terms as
    an unledgered function (the nearest assigned code rows below and above name
    one TU and start within GAP of each other), approved only when both brackets
    are and the image shows the address starts right after the body below it.
    """
    for r in m.get(rva, ()):
        if r["kind"].startswith("code"):
            return r
    index = code_index(m) if index is None else index
    host = index.host(rva)
    if host is not None:
        r = next(r for r in m[host] if r["kind"].startswith("code"))
        return {"rva": f"0x{rva:08X}", "size": "", "kind": "code-interior", "tu": r["tu"],
                "confidence": r["confidence"], "by": r["by"],
                "evidence": f"inside 0x{host:08X} {r['evidence']}".rstrip(), "source": ""}
    starts, rows = index.starts, index.rows
    i = bisect.bisect_left(starts, rva)
    if i == 0 or i >= len(starts):
        return None
    lo, hi, a, b = starts[i - 1], starts[i], rows[i - 1], rows[i]
    if a["tu"].lower() != b["tu"].lower() or hi - lo > GAP:
        return None
    gap = index.gap(rva)
    if gap == "padding":
        return None
    conf = "approved" if gap == "start" and a["confidence"] == b["confidence"] == "approved" else "proposed"
    return {"rva": f"0x{rva:08X}", "size": "", "kind": "code-inferred", "tu": a["tu"], "confidence": conf,
            "by": "C", "evidence": f"C=0x{lo:08X}..0x{hi:08X} gap={gap or 'unread'}", "source": ""}


# ---------------------------------------------------------------- freshness
def _digest(path):
    try:
        return hashlib.sha256(path.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
    except OSError:
        return "missing"


ZH_KEY = "zh:GeneralsMD/Code"


def _git(cwd, *args):
    # a hook's GIT_DIR/GIT_INDEX_FILE would point every call at the outer repository
    env = {k: v for k, v in os.environ.items()
           if k not in ("GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR", "GIT_PREFIX")}
    try:
        got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, env=env)
    except OSError:
        return None
    return got.stdout.strip() if got.returncode == 0 else None


def zh_identity(layout, kind=None):
    """(digest, note) of the ZH tree the map reads. `git:<tree id>` -- content-addressed, so
    equal wherever the same files are checked out -- for the default tree in a clean checkout
    (untracked files count as dirt), noting the commit; else, or for a custom --zh, or when
    `kind` is "sha256", `sha256:` over the relative path and CRLF-normalised bytes of every
    .cpp zh_index reads. `kind` "git" tries the tree id for a custom --zh too."""
    zh = layout.zh
    if not zh.is_dir():
        return "missing", "no ZH tree"
    commit = _git(zh, "rev-parse", "HEAD")
    if commit and kind != "sha256" and (kind == "git" or not layout.zh_custom):
        tree = _git(zh, "rev-parse", "HEAD:./")
        if tree and _git(zh, "--no-optional-locks", "status", "--porcelain", "--untracked-files=all", "--", ".") == "":
            return f"git:{tree}", f"commit {commit}"
    h = hashlib.sha256()
    for dp, dn, fn in sorted(os.walk(zh)):
        dn.sort()
        for f in sorted(fn):
            if f.lower().endswith(".cpp"):
                p = Path(dp) / f
                h.update(p.relative_to(zh).as_posix().encode() + b"\0")
                h.update(p.read_bytes().replace(b"\r\n", b"\n") + b"\0")
    why = "custom --zh" if layout.zh_custom else "dirty or untracked checkout"
    return f"sha256:{h.hexdigest()}", (f"commit {commit}, " if commit else "") + why


def fingerprint(layout, zh_kind=None):
    """sha256sum-like lines for the map's inputs (the ZH tree's as zh_identity), this tool
    and the map itself; `#` lines are notes, never compared."""
    out = ["# inputs of tu_map.csv as tools/tu_map.py wrote it; `tu_map.py --check-fresh` compares them"]
    for p in [layout.path(n) for n in FINGERPRINTED]:
        out.append(f"{_digest(p)}  {p.resolve().relative_to(layout.root.resolve()).as_posix()}")
    digest, note = zh_identity(layout, zh_kind)
    out.append(f"{digest}  {ZH_KEY}")
    out.append(f"# {ZH_KEY}: {note}")
    for p in (Path(__file__).resolve(), layout.out):
        try:
            name = p.resolve().relative_to(layout.root.resolve()).as_posix()
        except ValueError:
            name = "tools/" + p.name
        out.append(f"{_digest(p)}  {name}")
    return "\n".join(out) + "\n"


def _parse_fingerprint(text):
    return {name: digest for digest, _, name in (line.partition("  ") for line in text.splitlines()
                                                 if not line.startswith("#")) if name}


def check_fresh(layout):
    """[] when tu_map.csv was written from the current inputs, else the inputs that changed
    (or the missing fingerprint's own name). The ZH tree is identified the way it was
    recorded (git tree id or content hash), so a worktree's --zh copy and the submodule
    compare equal when their files are."""
    have = layout.fingerprint.read_text(encoding="utf-8") if layout.fingerprint.exists() else ""
    if not have.strip():
        return [layout.fingerprint.relative_to(layout.root).as_posix()]
    old = _parse_fingerprint(have)
    new = _parse_fingerprint(fingerprint(layout, old.get(ZH_KEY, "").partition(":")[0] or None))
    return [name for name in new if old.get(name) != new[name]]


# ---------------------------------------------------------------- validation
def _ledger_at(layout, rev):
    text = subprocess.run(["git", "show", f"{rev}:{layout.reverse}/functions.csv"], cwd=layout.root,
                          capture_output=True, check=True).stdout.decode("utf-8", "replace")
    return list(csv.DictReader(io.StringIO(text, newline="")))


def _named(row):
    return bool(row["name"] and row["cls"] and not PLACEHOLDER.match(row["cls"])
                and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", row["source"]))


def self_check(out):
    """(approved code rows, those whose own pre-clustering F/Z/S name another TU) of a map."""
    n = bad = 0
    for r in out:
        if r["kind"].startswith("code") and r["confidence"] == "approved":
            n += 1
            ev = anchors(r["evidence"])
            bad += contradicts(r["tu"], ev.get("F"), ev.get("Z"), ev.get("S"))
    return n, bad


def validate(layout, rev, predict=None, lookup=None):
    """Score routing predictions made from REV's ledger against independent evidence: the
    F/Z/S of rows that landed since REV (a real name at an address REV's ledger had no row
    for). `predict(ledger) -> rows` and `lookup(map, rva, index)` default to this module's
    build and tu_at; a caller can pass another revision's to score it the same way."""
    predict = predict or (lambda led: build(layout, led))
    lookup = lookup or (lambda m, rva, ix: tu_at(m, rva, ix))
    then = _ledger_at(layout, rev)
    had = {int(r["target_rva"], 16) for r in then if (r.get("target_rva") or "").startswith("0x")}
    now = [r for r in evidence_rows(layout) if r["kind"] == "code" and r["rva"] not in had and _named(r)
           and (r["F"] or r["Z"] or r["S"])]
    m = collections.defaultdict(list)
    for r in predict(then):
        m[int(r["rva"], 16)].append(r)
    index = code_index(m, Image.open(layout.image))
    tally = collections.defaultdict(lambda: [0, 0])
    misses = []
    for r in now:
        t = lookup(m, r["rva"], index)
        if not t or t["confidence"] not in ("approved", "proposed") or not t["tu"]:
            continue
        bad = contradicts(t["tu"], r["F"], r["Z"], r["S"])
        key = (t["confidence"], t["by"], {"code-inferred": "gap", "code-interior": "interior"}.get(t["kind"], "row"))
        tally[key][0] += 1
        tally[key][1] += bad
        if bad and t["confidence"] == "approved":
            misses.append((r["rva"], r["name"], t["tu"], r["F"] or r["Z"] or r["S"]))
    return len(now), dict(tally), misses


def report_validation(layout, rev, out=None):
    n, bad = self_check(read_csv(layout.out) if out is None else out)
    print(f"self-check: {bad} of {n} approved code rows in {layout.out.name} have their own F/Z/S "
          f"naming another TU")
    landed, tally, misses = validate(layout, rev)
    print(f"landed since {rev}: {landed} named rows with F/Z/S evidence at addresses its ledger had no row for")
    for conf in ("approved", "proposed"):
        rows = {k: v for k, v in tally.items() if k[0] == conf}
        tot = sum(v[0] for v in rows.values())
        dis = sum(v[1] for v in rows.values())
        rate = f"{100 * dis / tot:.1f}%" if tot else "-"
        print(f"  {conf}: {dis}/{tot} disagree ({rate})  " +
              "  ".join(f"{b}/{via}={v[1]}/{v[0]}" for (_, b, via), v in sorted(rows.items())))
    for rva, name, tu, want in misses[:20]:
        print(f"    0x{rva:08X} {name[:60]}: routed {tu}, evidence {want}")
    return 0


def summary(out, prefix=None):
    rows = [r for r in out if not prefix or r["source"].startswith(prefix)]
    conf = collections.Counter((r["kind"].split(":")[0], r["confidence"] or "none") for r in rows)
    by = collections.Counter(r["by"] for r in rows if r["confidence"] == "approved")
    tus = collections.Counter(r["tu"] for r in rows if r["confidence"] == "approved")
    print(f"rows {len(rows)}  " + "  ".join(f"{k[0]}/{k[1]}={v}" for k, v in sorted(conf.items())))
    print("approved by " + " ".join(f"{k}={v}" for k, v in sorted(by.items())))
    print(f"approved TUs {len(tus)} (with >=2 rows: {sum(1 for v in tus.values() if v > 1)})")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--check", action="store_true", help="exit 1 when tu_map.csv differs from a rebuild")
    g.add_argument("--check-fresh", action="store_true",
                   help="exit 1 when an input changed since tu_map.csv was written (hashes only)")
    g.add_argument("--validate", metavar="REV", help="score predictions from REV's ledger against landed rows")
    g.add_argument("--dir", help="summarise rows whose current source starts with this prefix")
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--zh", type=Path, help="ZH GeneralsMD/Code tree (default: the Open-BFME-1 submodule's)")
    a = ap.parse_args(argv)
    layout = Layout(a.root, a.zh)
    if a.check_fresh:
        stale = check_fresh(layout)
        if stale:
            print(f"tu_map: {layout.out.relative_to(layout.root).as_posix()} is stale (changed or missing: "
                  f"{', '.join(stale)}); run python3 tools/tu_map.py", file=sys.stderr)
            return 1
        return 0
    problem = layout.zh_problem()
    if problem:
        print(f"tu_map: {problem}; Z and S evidence would be empty", file=sys.stderr)
        return 2
    if a.validate:
        return report_validation(layout, a.validate)
    out = build(layout)
    text = render(out)
    if a.check:
        cur = layout.out.read_text(encoding="utf-8") if layout.out.exists() else ""
        if cur != text:
            print(f"tu_map: {layout.out.relative_to(layout.root).as_posix()} is stale; "
                  "run python3 tools/tu_map.py", file=sys.stderr)
            return 1
        return 0
    if not a.dir:
        layout.out.write_text(text, encoding="utf-8", newline="")
        layout.fingerprint.write_text(fingerprint(layout), encoding="utf-8", newline="")
    summary(out, a.dir)
    return 0


if __name__ == "__main__":
    sys.exit(main())
