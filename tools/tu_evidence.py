#!/usr/bin/env python3
"""Retail-structural TU evidence: where the image's own layout places a body.

tools/tu_map.py places a row by its names and strings (F/Z/S/L/N/U) and by address
contiguity (C). Most code rows have neither: no `__FILE__` string, no Zero Hour
definition, no usable name, no bracketing anchors. The linker lays out more than
.text in object order, and this module reads those layouts out of the retail image
(and the committed xref tables), never out of a hand entry:

  R  .rdata order: each object's constants and literals sit together in .rdata. An
     .rdata item (data_xrefs.tsv) bracketed by items of one TU belongs to it, and so
     does every function that references it.
  V  vftable layout: a vftable (an .rdata item that opens a run of function-start
     pointers; RTTI is mostly off) sits in its emitting object's .rdata. A slot
     function that appears in exactly one vftable takes the TU of the anchored slots
     around it (within the vftable or in its neighbours).
  I  initializer order: the `.CRT$XCU` table between `__xc_a` and `__xc_z` (located
     by the CRT's `push __xc_z; push __xc_a; call _initterm`) lists each object's
     dynamic initializers in object order.
  E  funclet order: `.text$x` holds each object's EH handlers and funclets after all
     of .text, in object order. Parents come from the image's own EH tables (an
     `mov eax, FuncInfo; jmp` handler whose FuncInfo carries the 0x1993052x magic,
     referenced by `mov eax, handler` / `push handler` in exactly one function), never
     from adjacency alone. A parent bracketed by handlers and funclets of one TU takes it.
  P  funclet parentage: a handler or funclet takes its parent's TU (the parent read
     from the same EH tables). Its parent is scored against the ledger's eh_verify
     `parent=` notes.

R, V, I and E share one rule: a function's entries in the layout, the nearest
anchored entries below and above each of them (an anchor is an approved F/Z/S/L/N/U
map row; never C, so a bracket does not lean on contiguity), both naming one TU
within the signal's gap. A function whose entries name two TUs gets nothing.

Gate. Every signal starts proposal-only: its rows are evidence for the lane
(`next_work.py --tier tu-evidence`), not tu_map approvals. A signal counts toward
approval only once it is listed in PROMOTED, which takes a Verifier-Change commit
recording `--validate` numbers at or above GATE (0.99) precision: leave-one-out
over the approved F/Z/S rows (each scored with its own entries removed from the
anchors), recall the share of those rows predicted correctly; P is scored against
the ledger's `parent=` notes. `--validate` exits 1 when a promoted signal has fallen
below the gate. Approval of a promoted signal's row is still computed by tu_map: its
TU must be anchored and contiguous and the row must not sit inside another approved
TU's span.

Validation when this tool landed (2026-10-25, the map rebuilt in memory at 4d2094622a
with the ZH tree; 6,858 approved F/Z/S rows held out one at a time; P against 18,731
`parent=` notes). None is promoted yet:
  E  precision 1.0000 (700/700)      recall 0.102  passes; alone approves 32 rows
  V  precision 0.9935 (459/462)      recall 0.067  passes; alone approves 39 rows
  P  precision 0.9999 (17454/17455)  recall 0.932  passes; alone approves 7,493 rows
  R  precision 0.8612 (521/605)      recall 0.076  proposal-only (shared literals fold)
  I  no prediction: 1,164 of the 1,166 initializers have no TU, so nothing anchors I
  E+V+P together would approve 7,680 rows in 1,501 sources.
`--validate` prints the current numbers; a promotion commit records them here.

Promoted 2026-10-26 (E and P; V stays proposal-only: 3 of its 462 predictions
were wrong). `--validate` at ed0e06e23f, 6,860 held-out rows, P against 19,649
`parent=` notes:
  E  precision 1.0000 (701/701)      recall 0.102  alone approves 32 rows in 32 sources
  P  precision 0.9999 (18255/18256)  recall 0.929  alone approves 7,495 rows in 1,433 sources

Every evidence row names its own `ref` (the bracketing entries' positions and anchor
functions, or the FuncInfo address) and `--check` re-derives the file from the
committed inputs and the image, so a row nothing re-derives is reported, never used.

Usage:
  python3 tools/tu_evidence.py --validate           precision/recall per signal; rows a gate-passing
                                                    signal would approve
  python3 tools/tu_evidence.py --source FILE        evidence for one source's rows
  python3 tools/tu_evidence.py --write [PATH]       every evidence row (default build/tu_evidence.csv)
  python3 tools/tu_evidence.py --check [PATH]       re-derive PATH; exit 1 on a row that does not re-check
  --zh DIR                                          ZH GeneralsMD/Code tree for a map rebuilt in memory
"""
import argparse
import bisect
import collections
import csv
import io
import itertools
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402

SIGNALS = ("E", "I", "V", "R", "P")            # order of preference when several agree
PROMOTED = frozenset("EP")                    # approval-capable signals (Verifier-Change commit)
GATE = 0.99
# P groups (owner decision pending; `tu_map.py --holdout p-groups`): a funclet whose parent the map
# does not approve is approved with its parent's TU anyway, evidence token P_GROUP_TOKEN (plus
# tu_map.PROV_TOKEN when that TU has no anchor, so its name stays unproven). Held-out purity
# 5,984/5,991 (99.88%) at a136856afb: every funclet joins a group whose other rows share its TU.
P_GROUPS = True
P_GROUP_TOKEN = "p-group"
ANCHOR_BY = frozenset("FZSLNU")
TEST_BY = frozenset("FZS")
# Max distance (bytes in the signal's own layout) between the two bracketing anchors.
GAPS = {"R": 0x100, "V": 0x400, "I": 0x40, "E": 0x2000}
EH_MAGIC = (0x19930520, 0x19930521, 0x19930522)
MAX_STATES = 4096
COLUMNS = ["rva", "source", "signal", "tu", "ref", "status"]


# ---------------------------------------------------------------- the image
class Retail:
    """The retail PE: sections by name and bytes by RVA."""

    def __init__(self, data):
        self.data = data
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        self.base = struct.unpack_from("<I", data, pe + 52)[0]
        table = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
        self.secs = []
        for i in range(struct.unpack_from("<H", data, pe + 6)[0]):
            name = data[table + 40 * i:table + 40 * i + 8].rstrip(b"\0").decode("latin-1")
            vsize, va, rsize, raw = struct.unpack_from("<IIII", data, table + 40 * i + 8)
            self.secs.append((name, va, min(vsize, rsize), raw))

    @classmethod
    def open(cls, path):
        return cls(Path(path).read_bytes()) if path is not None and Path(path).is_file() else None

    def section(self, name):
        """(rva, bytes) of the first section called `name`, or (0, b"")."""
        for n, va, size, raw in self.secs:
            if n == name:
                return va, self.data[raw:raw + size]
        return 0, b""

    def read(self, rva, n):
        for _, va, size, raw in self.secs:
            if va <= rva and rva + n <= va + size:
                return self.data[raw + rva - va:raw + rva - va + n]
        return None

    def dword(self, rva):
        b = self.read(rva, 4)
        return struct.unpack("<I", b)[0] if b else None


class Code:
    """Known code bodies (rva, size) and their owner lookup."""

    def __init__(self, extents):
        got = sorted(set(extents))
        self.starts = [a for a, _ in got]
        self.ends = [a + max(n, 1) for a, n in got]
        self.set = set(self.starts)

    def owner(self, rva):
        i = bisect.bisect_right(self.starts, rva) - 1
        return self.starts[i] if i >= 0 and rva < self.ends[i] else None


def eh_records(img, code):
    """{handler rva: (parent rva, funcinfo rva, [funclet rvas])} from the image's EH tables:
    a handler is `mov eax, FuncInfo; jmp` with the FuncInfo magic; its parent is the one
    known body whose `mov eax, handler` or `push handler` references it; its funclets are
    the FuncInfo's unwind actions and catch handlers. A handler referenced from two bodies
    (folded parents) or from none is left out."""
    tva, text = img.section(".text")
    if not text:
        return {}
    handlers = {}
    for m in re.finditer(rb"(?=\xB8(.{4})\xE9)", text, re.S):
        fi = struct.unpack("<I", m.group(1))[0] - img.base
        if img.dword(fi) in EH_MAGIC:
            handlers[tva + m.start()] = fi
    if not handlers:
        return {}
    first = min(handlers)
    by_va = {struct.pack("<I", h + img.base): h for h in handlers}
    owners = collections.defaultdict(set)
    for m in re.finditer(rb"(?=[\x68\xB8](.{4}))", text[:first - tva], re.S):
        h = by_va.get(m.group(1))
        if h is not None:
            owners[h].add(code.owner(tva + m.start()))
    out = {}
    for h, fi in sorted(handlers.items()):
        parents = owners.get(h, set())
        if len(parents) != 1 or None in parents:
            continue
        funclets = []
        head = img.read(fi, 20)
        _, states, unwind, ntry, trymap = struct.unpack("<IIIII", head)
        if 0 < states <= MAX_STATES and unwind:
            for i in range(states):
                act = img.dword(unwind - img.base + 8 * i + 4)
                if act:
                    funclets.append(act - img.base)
        if 0 < ntry <= MAX_STATES and trymap:
            for i in range(ntry):
                block = img.read(trymap - img.base + 20 * i, 20)
                if not block:
                    break
                ncatch, harr = struct.unpack_from("<II", block, 12)
                for j in range(min(ncatch, MAX_STATES)):
                    a = img.dword(harr - img.base + 16 * j + 12) if harr else None
                    if a:
                        funclets.append(a - img.base)
        out[h] = (next(iter(parents)), fi, sorted({f for f in funclets if f >= first}))
    return out


def initializers(img, code):
    """[(slot rva, function rva)] of the `.CRT$XCU` table, or [] when the image shows no
    single best `push __xc_z; push __xc_a; call _initterm` table."""
    tva, text = img.section(".text")
    best = []
    for m in re.finditer(rb"(?=\x68(.{4})\x68(.{4})\xE8)", text, re.S):
        z, a = (struct.unpack("<I", g)[0] - img.base for g in m.groups())
        if not (0 < a < z and z - a <= 0x10000 and (z - a) % 4 == 0):
            continue
        raw = img.read(a, z - a)
        if not raw:
            continue
        slots = struct.unpack(f"<{(z - a) // 4}I", raw)
        if not all(v == 0 or (v - img.base) in code.set for v in slots):
            continue
        got = [(a + 4 * i, v - img.base) for i, v in enumerate(slots) if v]
        if len(got) > len(best):              # a tie keeps the first call's table
            best = got
    return best


def vftables(img, code, items):
    """[(vftable rva, [slot function rvas])]: each referenced .rdata item that opens a run
    of known function-start pointers."""
    out = []
    for rva in items:
        slots, p = [], rva
        while True:
            v = img.dword(p)
            if v is None or (v - img.base) not in code.set:
                break
            slots.append(v - img.base)
            p += 4
        if slots:
            out.append((rva, slots))
    return out


def rdata_items(layout, code):
    """{.rdata item rva: [referencing function rvas]} from data_xrefs.tsv."""
    path = layout.path("data_xrefs.tsv")
    out = {}
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines()[1:]:
        f = line.split("\t")
        if len(f) < 8 or f[1] != ".rdata" or not f[0].startswith("0x"):
            continue
        refs = []
        for c in filter(None, f[7].split(",")):
            o = code.owner(int(c, 16))
            if o is not None and o not in refs:
                refs.append(o)
        if refs:
            out[int(f[0], 16)] = sorted(refs)
    return out


class Structures:
    """Every layout the signals read, from the image, data_xrefs.tsv and the code extents of
    a map. A pure function of those inputs."""

    def __init__(self, layout, out, img=None):
        self.code = Code((int(r["rva"], 16), tu_map._int(r["size"])) for r in out if r["kind"].startswith("code"))
        img = img if img is not None else Retail.open(layout.image)
        self.img = img
        items = rdata_items(layout, self.code)
        if img is None:
            self.eh, self.inits, self.vfts = {}, [], []
        else:
            self.eh = eh_records(img, self.code)
            self.inits = initializers(img, self.code)
            self.vfts = vftables(img, self.code, sorted(items))
        vstart = {v for v, _ in self.vfts}
        self.items = {a: r for a, r in items.items() if a not in vstart}
        # funclet -> parent; a funclet two FuncInfos claim for different parents is left out
        par = collections.defaultdict(set)
        for h, (p, fi, funclets) in self.eh.items():
            par[h].add((p, fi))
            for f in funclets:
                par[f].add((p, fi))
        self.parent = {f: next(iter(v)) for f, v in par.items() if len({p for p, _ in v}) == 1}

    def entries(self, signal):
        """Sorted [(position, function rva)] of one ordered layout."""
        if signal == "R":
            got = [(a, f) for a, refs in self.items.items() for f in refs]
        elif signal == "V":
            count = collections.Counter(s for _, slots in self.vfts for s in set(slots))
            got = [(v + 4 * i, s) for v, slots in self.vfts for i, s in enumerate(slots) if count[s] == 1]
        elif signal == "I":
            got = list(self.inits)
        elif signal == "E":
            got = [(f, p) for f, (p, _) in self.parent.items()]
        else:
            raise ValueError(signal)
        return sorted(set(got))


# ---------------------------------------------------------------- the rule
class Layout1:
    """One ordered layout and its bracketing rule."""

    def __init__(self, signal, entries, anchor):
        self.signal, self.gap = signal, GAPS[signal]
        self.pos = [p for p, _ in entries]
        self.fn = [f for _, f in entries]
        self.anchor = anchor                    # function rva -> TU key (lowercase) or None
        self.at = collections.defaultdict(list)
        for i, f in enumerate(self.fn):
            self.at[f].append(i)

    def _side(self, i, step, fn):
        """(index, TU) of the nearest anchored entry of another function from entry i."""
        j = i + step
        while 0 <= j < len(self.fn) and abs(self.pos[j] - self.pos[i]) <= self.gap:
            t = self.anchor.get(self.fn[j]) if self.fn[j] != fn else None
            if t:
                return j, t
            j += step
        return None

    def predict(self, fn):
        """(tu key, ref) for function `fn`, or None. Its own entries never anchor it, so
        scoring an anchor row is leave-one-out."""
        votes = {}
        for i in self.at.get(fn, ()):
            lo, hi = self._side(i, -1, fn), self._side(i, 1, fn)
            if not lo or not hi or lo[1] != hi[1] or self.pos[hi[0]] - self.pos[lo[0]] > self.gap:
                continue
            votes.setdefault(lo[1], (f"{self.signal}=0x{self.pos[lo[0]]:08X}..0x{self.pos[hi[0]]:08X}"
                                     f"@0x{self.fn[lo[0]]:08X},0x{self.fn[hi[0]]:08X}"))
        if len(votes) != 1:
            return None
        return next(iter(votes.items()))


def anchors_of(out, by=ANCHOR_BY):
    """function rva -> TU key of approved map rows assigned by `by`, and TU key -> spelling."""
    anchor, spelled = {}, {}
    for r in out:
        if r["kind"].startswith("code") and r["confidence"] == "approved" and r["by"] in by and r["tu"]:
            anchor[int(r["rva"], 16)] = r["tu"].lower()
        if r["tu"]:
            spelled.setdefault(r["tu"].lower(), r["tu"])
    return anchor, spelled


def layouts(st, anchor):
    return {s: Layout1(s, st.entries(s), anchor) for s in SIGNALS if s != "P"}


def gather(out, st, signals=SIGNALS):
    """{rva: {signal: (tu key, ref)}} for every code row with no TU in `out`."""
    anchor, _ = anchors_of(out)
    lay = layouts(st, anchor)
    by_rva = {int(r["rva"], 16): r for r in out if r["kind"].startswith("code")}
    got = collections.defaultdict(dict)
    for rva, r in sorted(by_rva.items()):
        if r["tu"]:
            continue
        for s in signals:
            if s == "P":
                continue
            p = lay[s].predict(rva)
            if p:
                got[rva][s] = p
    if "P" in signals:
        for rva, r in sorted(by_rva.items()):
            if r["tu"] or rva not in st.parent:
                continue
            parent, fi = st.parent[rva]
            pr = by_rva.get(parent)
            tu = pr["tu"].lower() if pr is not None and pr["tu"] else (
                choose(got.get(parent, {}))[1][0] if choose(got.get(parent, {})) else None)
            if tu:
                got[rva]["P"] = (tu, f"P=0x{parent:08X}@FuncInfo0x{fi:08X}")
    return dict(got)


def choose(sig):
    """(signal, (tu, ref)) when every signal that reaches a row names one TU, else None."""
    if not sig or len({t for t, _ in sig.values()}) != 1:
        return None
    s = next(x for x in SIGNALS if x in sig)
    return s, sig[s]


def approvable(out):
    """(anchored TU keys, broken TU keys, sorted approved spans [(lo, hi, key)]) of a map."""
    roots, broken, span = set(), set(), {}
    for r in out:
        if not r["kind"].startswith("code") or not r["tu"]:
            continue
        k = r["tu"].lower()
        if "noncontiguous" in r["evidence"]:
            broken.add(k)
        if r["confidence"] == "approved":
            roots.add(k)
            a = int(r["rva"], 16)
            lo, hi = span.get(k, (a, a))
            span[k] = (min(lo, a), max(hi, a))
    return roots, broken, sorted((lo, hi, k) for k, (lo, hi) in span.items())


def inside_other(spans, rva, key):
    """The key of the first span in SPANS (sorted, as approvable() returns them) strictly
    containing `rva` under another key, else None. apply() asks it of every row, so the
    span list's SpanIndex is kept between calls (the list must not change in place)."""
    if _SPANS[0] is not spans:
        _SPANS[:] = [spans, SpanIndex(spans) if all(a <= b for a, b in zip(spans, spans[1:])) else None]
    if _SPANS[1] is not None:
        return _SPANS[1].other(rva, key)
    for lo, hi, k in spans:
        if lo > rva:
            break
        if k != key and lo < rva < hi:
            return k
    return None


_SPANS = [None, None]       # the last span list inside_other saw, and its SpanIndex


class SpanIndex:
    """inside_other over one sorted span list, asked for many rows: a span ending at or before
    `rva` cannot contain it, and the running maximum of the ends finds the first that may."""

    def __init__(self, spans):
        self.spans = spans
        self.los = [lo for lo, _, _ in spans]
        self.reach = list(itertools.accumulate((hi for _, hi, _ in spans), max))

    def other(self, rva, key):
        end = bisect.bisect_right(self.los, rva)                 # inside_other stops at lo > rva
        for j in range(bisect.bisect_right(self.reach, rva, 0, end), end):
            lo, hi, k = self.spans[j]
            if k != key and lo < rva < hi:
                return k
        return None


def apply(layout, out, signals=None, st=None):
    """`out` (tu_map rows) with every row no other signal reaches assigned by `signals`
    where they agree. A row is approved only when its TU is anchored, contiguous and the
    row is inside no other approved TU's span (a P row: when its parent is approved, or
    always under P_GROUPS, tokened P_GROUP_TOKEN); else proposed. `signals` defaults to PROMOTED; unchanged (and the image unread) when
    it is empty."""
    signals = PROMOTED if signals is None else signals
    if not signals:
        return out
    st = st or Structures(layout, out)
    got = gather(out, st, tuple(s for s in SIGNALS if s in signals))
    roots, broken, spans = approvable(out)
    _, spelled = anchors_of(out)
    new, conf = list(out), {}
    prov = set()                              # TUs tu_map approved under a provisional name
    for i, r in enumerate(out):
        if r["kind"].startswith("code"):
            conf[int(r["rva"], 16)] = r["confidence"]
            if tu_map.provisional_name(r):
                prov.add(r["tu"].lower())
    for funclets in (False, True):            # parents first: a P row follows its parent's confidence
        for i, r in enumerate(out):
            rva = int(r["rva"], 16) if r["kind"].startswith("code") else None
            pick = choose(got.get(rva)) if rva is not None and not r["tu"] and r["confidence"] == "" else None
            if not pick or (pick[0] == "P") != funclets:
                continue
            s, (key, ref) = pick
            other = inside_other(spans, rva, key)
            ok = key in roots and key not in broken and not other
            group = False
            if s == "P":
                ok = ok and conf.get(st.parent[rva][0]) == "approved"
                # a proposed parent's group only: an approved parent's funclet keeps the usual checks
                group = P_GROUPS and not ok and conf.get(st.parent[rva][0]) == "proposed"
            unproven = ok and key in prov or group and (key not in roots or key in prov)
            ev = " ".join(x for x in (r["evidence"], ref, f"inside={spelled.get(other, other)}" if other else "",
                                      P_GROUP_TOKEN if group else "", tu_map.PROV_TOKEN if unproven else "") if x)
            ok = ok or group
            new[i] = dict(r, tu=spelled.get(key, key), confidence="approved" if ok else "proposed", by=s,
                          evidence=ev)
            conf[rva] = new[i]["confidence"]
    return new


# ---------------------------------------------------------------- the lane
RUN_SOURCES = 16                              # sources per served run (one claim footprint)
LANE_SKIP = re.compile(r"/gen_small/uw_gen_")  # tools/gen_uw.py owns these


def runs(out, st=None, layout=None, exists=None):
    """Unmapped address runs: maximal runs of code rows with no TU between two assigned
    rows, keeping those holding a source no row of which has a TU (`unevidenced`), split
    into pieces of at most RUN_SOURCES such sources. Each: dict(lo, hi, rows, sources,
    below, above, gap, signals), where below/above are the bracketing assigned rows,
    `gap` the bytes between them and `signals` {signal: Counter(tu)} over the run's
    rows (from `gather`; re-derived, so every one re-checks). Runs some signal reaches
    first, then the most sources."""
    bare = unevidenced(out)
    _, spelled = anchors_of(out)
    exists = exists or (lambda s: True)
    code = sorted((r for r in out if r["kind"].startswith("code")), key=lambda r: int(r["rva"], 16))
    got = gather(out, st) if st is not None else {}
    spans, cur, last = [], [], None
    for r in code:
        if r["tu"]:
            if cur:
                spans.append((last, cur, r))
            cur, last = [], r
        else:
            cur.append(r)
    if cur:
        spans.append((last, cur, None))
    items = []
    for below, rows, above in spans:
        srcs = []
        for r in rows:
            s = r["source"]
            if s in bare and s not in srcs and not LANE_SKIP.search(s) and exists(s):
                srcs.append(s)
        for k in range(0, len(srcs), RUN_SOURCES):
            part = set(srcs[k:k + RUN_SOURCES])
            mine = [r for r in rows if r["source"] in part]
            sig = collections.defaultdict(collections.Counter)
            for r in mine:
                for s, (key, _) in got.get(int(r["rva"], 16), {}).items():
                    sig[s][spelled.get(key, key)] += 1
            lo, hi = int(mine[0]["rva"], 16), int(mine[-1]["rva"], 16)
            items.append(dict(lo=lo, hi=hi, rows=len(mine), sources=srcs[k:k + RUN_SOURCES], below=below,
                              above=above, signals=dict(sig),
                              gap=(int(above["rva"], 16) - int(below["rva"], 16)) if below and above else None))
    items.sort(key=lambda i: (not i["signals"], -len(i["sources"]), -i["rows"], i["lo"]))
    return items, len(bare)


# ---------------------------------------------------------------- validation
def _ledger_parents(layout):
    """{funclet rva: parent rva} from the ledger's `parent=` notes (eh_verify's binding),
    the parent resolved by its ledger name."""
    rows = tu_map.read_csv(layout.path("functions.csv"))
    by_name = {}
    for r in rows:
        if (r.get("target_rva") or "").startswith("0x"):
            by_name.setdefault(r["name"], int(r["target_rva"], 16))
    out = {}
    for r in rows:
        m = re.search(r"parent=([^;\s]+)", r.get("notes") or "")
        if m and m.group(1) in by_name and (r.get("target_rva") or "").startswith("0x"):
            out.setdefault(int(r["target_rva"], 16), by_name[m.group(1)])
    return out


def validate(layout, out, st=None):
    """{signal: dict(test, predicted, correct, precision, recall)}: R/V/I/E by leave-one-out
    over the approved F/Z/S rows, P against the ledger's parent= notes."""
    st = st or Structures(layout, out)
    anchor, _ = anchors_of(out)
    test = {int(r["rva"], 16): r["tu"].lower() for r in out
            if r["kind"].startswith("code") and r["confidence"] == "approved" and r["by"] in TEST_BY and r["tu"]}
    res = {}
    for s, lay in layouts(st, anchor).items():
        pred = ok = 0
        for rva, want in test.items():
            p = lay.predict(rva)
            if p:
                pred += 1
                ok += p[0] == want
        res[s] = dict(test=len(test), predicted=pred, correct=ok)
    led = _ledger_parents(layout)

    def root(a):                          # a parent= naming another funclet names its parent
        seen = set()
        while a in led and a not in seen:
            seen.add(a)
            a = led[a]
        return a
    pred = ok = 0
    for f, (p, _) in st.parent.items():
        if f in led:
            pred += 1
            ok += root(f) == p or st.parent.get(root(f), (None,))[0] == p
    res["P"] = dict(test=len(led), predicted=pred, correct=ok)
    for v in res.values():
        v["precision"] = v["correct"] / v["predicted"] if v["predicted"] else 0.0
        v["recall"] = v["correct"] / v["test"] if v["test"] else 0.0
        v["passes"] = v["predicted"] > 0 and v["precision"] >= GATE
    return res


def would_approve(layout, out, signals, st=None):
    """(rows, sources): rows with no TU that `signals` would approve, and the sources they span."""
    new = apply(layout, out, frozenset(signals), st)
    rows = [n for o, n in zip(out, new) if o is not n and n["confidence"] == "approved"]
    return len(rows), len({n["source"] for n in rows if n["source"]})


# ---------------------------------------------------------------- evidence rows
def evidence_rows(layout, out, st=None):
    """Every evidence row: one per (row with no TU, signal reaching it), sorted. `status`
    says whether the signal may count toward approval (`gated`) or only proposes."""
    st = st or Structures(layout, out)
    src = {int(r["rva"], 16): r["source"] for r in out if r["kind"].startswith("code")}
    _, spelled = anchors_of(out)
    rows = []
    for rva, sig in sorted(gather(out, st).items()):
        conflict = len({t for t, _ in sig.values()}) > 1
        for s in SIGNALS:
            if s in sig:
                key, ref = sig[s]
                rows.append({"rva": f"0x{rva:08X}", "source": src.get(rva, ""), "signal": s,
                             "tu": spelled.get(key, key), "ref": ref,
                             "status": "conflict" if conflict else "gated" if s in PROMOTED else "proposal"})
    return rows


def render(rows):
    buf = io.StringIO()
    w = csv.DictWriter(buf, COLUMNS, lineterminator="\n")
    w.writeheader()
    w.writerows(rows)
    return buf.getvalue()


def check(layout, out, path, st=None):
    """Rows of the evidence file at `path` that the current inputs do not re-derive."""
    have = {tuple(r[c] for c in COLUMNS) for r in evidence_rows(layout, out, st)}
    return [r for r in tu_map.read_csv(Path(path)) if tuple(r.get(c, "") for c in COLUMNS) not in have]


def map_rows(layout):
    """tu_map rows from current inputs: the committed map when fresh, else rebuilt in memory."""
    if not tu_map.check_fresh(layout):
        return [{k: str(v) for k, v in r.items()} for r in tu_map.read_csv(layout.out)]
    return [{k: str(v) for k, v in r.items()} for r in tu_map.build(layout)]


def unevidenced(out):
    """Sources none of whose code rows has a TU (approved or proposed): the lane's work."""
    has = collections.defaultdict(bool)
    for r in out:
        if r["kind"].startswith("code") and r["source"]:
            has[r["source"]] |= bool(r["tu"])
    return {s for s, v in has.items() if not v}


def reach(out, st):
    """{signal: (rows with no TU it reaches, sources without evidence it reaches)}."""
    bare = unevidenced(out)
    src = {int(r["rva"], 16): r["source"] for r in out if r["kind"].startswith("code")}
    got = collections.defaultdict(lambda: [0, set()])
    for rva, sig in gather(out, st).items():
        for s in sig:
            got[s][0] += 1
            if src.get(rva) in bare:
                got[s][1].add(src[rva])
    return {s: (got[s][0], len(got[s][1])) for s in SIGNALS}, len(bare)


def report(res, layout, out, st):
    hits, bare = reach(out, st)
    print(f"signal  test   predicted  correct  precision  recall  reach(rows/of {bare} bare sources)  gate")
    for s in SIGNALS:
        v = res[s]
        gate = "promoted" if s in PROMOTED else "passes (promotable)" if v["passes"] else "proposal-only"
        print(f"  {s}    {v['test']:6d} {v['predicted']:9d} {v['correct']:8d}   {v['precision']:.4f}   "
              f"{v['recall']:.3f}  {hits[s][0]:6d}/{hits[s][1]:<6d}                  {gate}")
    passing = [s for s in SIGNALS if res[s]["passes"]]
    for s in passing:
        n, files = would_approve(layout, out, {s}, st)
        print(f"  {s} alone would approve {n} row(s) with no TU today, in {files} source(s)")
    if passing:
        n, files = would_approve(layout, out, set(passing), st)
        print(f"  all passing ({''.join(passing)}) would approve {n} row(s) in {files} source(s); "
              "promotion is a Verifier-Change commit listing them in PROMOTED")
    bad = [s for s in PROMOTED if not res[s]["passes"]]
    if bad:
        print(f"tu_evidence: promoted signal(s) {', '.join(bad)} below the {GATE:.0%} gate", file=sys.stderr)
        return 1
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--validate", action="store_true")
    g.add_argument("--source")
    g.add_argument("--write", nargs="?", const="build/tu_evidence.csv")
    g.add_argument("--check", nargs="?", const="build/tu_evidence.csv")
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--zh", type=Path)
    a = ap.parse_args(argv)
    layout = tu_map.Layout(a.root, a.zh)
    out = map_rows(layout)
    st = Structures(layout, out)
    if st.img is None:
        print(f"tu_evidence: no retail image at {layout.image}", file=sys.stderr)
        return 2
    if a.validate:
        return report(validate(layout, out, st), layout, out, st)
    if a.source:
        rows = [r for r in evidence_rows(layout, out, st) if r["source"].lower() == a.source.lower()]
        sys.stdout.write(render(rows))
        return 0
    if a.write:
        path = layout.root / a.write
        path.parent.mkdir(parents=True, exist_ok=True)
        rows = evidence_rows(layout, out, st)
        path.write_text(render(rows), encoding="utf-8", newline="")
        print(f"{len(rows)} evidence row(s) -> {a.write}")
        return 0
    bad = check(layout, out, layout.root / a.check, st)
    for r in bad[:20]:
        print(f"  not re-derived: {r.get('rva')} {r.get('signal')} {r.get('tu')} {r.get('ref')}")
    print(f"tu_evidence: {len(bad)} row(s) of {a.check} do not re-check")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
