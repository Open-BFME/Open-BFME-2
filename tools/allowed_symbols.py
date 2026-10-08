#!/usr/bin/env python3
"""Which symbols may bind at each retail code address (code identity).

The byte gate resolves a call by name: symbols.csv is an additive candidate
list, so a call to `X` passes when any address pinned for `X` reproduces
retail's displacement. It never asks what `X` IS in a link. When some other
object defines `X` with different code, the linked image calls that code
instead (research 29: 1,896 "copy under another name" callees, 641 of them
with different bytes, 349 wrong callees). Renaming the reference does not fix
this: about half of all calls are spelled by the compiler (ctors, dtors,
operators, templates) and binding them by rewrite changes the caller's bytes
(research 20, attack 2). So identity is checked, not rewritten.

For every retail .text target T that a matched row references, the allowed
set is derived from retail and the ledger of the tree being checked, never
from the reference itself:

  owner     a ledger row starting at T (its name or object-symbol=); the gate
            byte-verifies every row at its address, so several rows at one T
            are all retail's body (an ICF fold the ledger already proves)
  label     a symbol in the referencing function's own section: (owner, offset)
  eh        __ehhandler$X / __unwindfunclet$X$n / __catch$X$n / __tryend$X$n
            referenced from X itself: (owner, eh); its tables are judged by the
            link cycle's EH verdict, not here
  fold      a symbol with no row at T whose definition in the tree (the copy
            link.exe keeps: the first in link order) has T's retail extent and
            equals retail at T in bytes AND resolved relocations
            (link_census.RetailTruth). A masked compare is not enough
            (research 31: 25 of 803 masked twins differ)
  alias     a name nothing in the tree defines, at a T a row owns: the link
            binds it with a generated /ALTERNATENAME:name=owner, the only
            source of that directive (alternatenames())

Every other reference is a wrong binding, keyed for a shrink-only baseline:

  wrong     defined in the tree, not T's owner, its kept copy not retail at T
  interior  an external name whose T lies inside a row, not at its start
  unowned   T has no row; auto_rows.py mints one when a definition here has
            T's retail extent and bytes (the `match` sub-class)
  divergent the name's copies differ and the kept one is not certified

BFME2 was linked without incremental linking (no ILT), so a target is the
body itself; the build.py thunk scan is not consulted.

  python3 tools/allowed_symbols.py                 full shadow: counts + build/allowed_symbols/refs.tsv
  python3 tools/allowed_symbols.py --source F ...  only rows in these sources
  python3 tools/allowed_symbols.py --alternatenames   write build/allowed_symbols/alternatename.txt
  python3 tools/allowed_symbols.py --tiers         write reverse/name_tiers.csv (tool-only file:
                                                   evidence / address rows; any row not listed
                                                   is an unverified label)
"""
import argparse
import bisect
import collections
import copy
import concurrent.futures
import csv
import hashlib
import io
import os
import pickle
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as census  # noqa: E402

OUT = ROOT / "build" / "allowed_symbols"
TIERS = ROOT / "reverse" / "name_tiers.csv"
BASE = 0x400000
REL32, DIR32 = 0x14, 0x6
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
COMDAT, CODE = 0x1000, 0x20
EH_PREFIX = ("__ehhandler$", "__unwindfunclet$", "__catch$", "__tryend$")
WRONG = ("wrong", "interior", "unowned", "divergent")
ALTERNATENAME = re.compile(r'/alternatename:([^=\s"]+)=([^\s"]+)', re.I)


# ---------------------------------------------------------------- COFF
class Obj:
    """One object's sections, symbols (raw index) and per-section relocations."""

    def __init__(self, path):
        data = Path(path).read_bytes()
        self.path, self.data = Path(path), data
        count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
        self.sections = []
        for i in range(count):
            o = 20 + optional + i * 40
            size, ptr, rptr = struct.unpack_from("<III", data, o + 16)
            nrel = struct.unpack_from("<H", data, o + 32)[0]
            flags = struct.unpack_from("<I", data, o + 36)[0]
            self.sections.append((size, ptr, rptr, nrel, flags))
        table, nsym = struct.unpack_from("<II", data, 8)
        strings = table + 18 * nsym
        self.symbols, i = {}, 0
        while i < nsym:
            rec = data[table + 18 * i:table + 18 * i + 18]
            if rec[:4] == b"\0\0\0\0":
                off = struct.unpack_from("<I", rec, 4)[0]
                name = data[strings + off:data.index(b"\0", strings + off)]
            else:
                name = rec[:8].rstrip(b"\0")
            value, sec, typ, storage, aux = struct.unpack_from("<IhHBB", rec, 8)
            self.symbols[i] = {"index": i, "name": name.decode("latin-1"), "section": sec, "storage": storage,
                               "value": value, "type": typ}
            i += 1 + aux
        self.by_name = {}
        for s in self.symbols.values():
            if s["section"] > 0:
                self.by_name.setdefault(s["name"], s)

    def is_code(self, sym):
        return 0 < sym["section"] <= len(self.sections) and self.sections[sym["section"] - 1][4] & CODE

    def functions(self):
        """Defined code symbols that are functions (COFF type 0x20) or external."""
        return [s for s in self.symbols.values() if self.is_code(s) and s["storage"] in (EXTERNAL, STATIC)
                and (s["type"] & 0x30) == 0x20]

    def body(self, sym):
        """(bytes, size, relocs [(offset, type, referent)]) of a function symbol: to
        the next function symbol of its section, else the section end."""
        size, ptr, rptr, nrel, _ = self.sections[sym["section"] - 1]
        ends = sorted(s["value"] for s in self.symbols.values()
                      if s["section"] == sym["section"] and s["value"] > sym["value"] and (s["type"] & 0x30) == 0x20)
        end = ends[0] if ends else size
        start = sym["value"]
        raw = self.data[ptr + start:ptr + end] if ptr else None
        relocs = []
        for at in range(rptr, rptr + 10 * nrel, 10):
            where, target, kind = struct.unpack_from("<IIH", self.data, at)
            if start <= where < end:
                ref = self.symbols.get(target, {"name": "?", "storage": 0, "section": 0, "value": 0, "type": 0})
                if ref["name"].startswith(census.RetailTruth.CONSTANT) and 0 < ref["section"] <= len(self.sections):
                    length, p = self.sections[ref["section"] - 1][:2]
                    ref = {**ref, "content": self.data[p + ref["value"]:p + length] if p else None}
                relocs.append((where - start, kind, ref))
        return raw, end - start, relocs

    def exclusive(self, sym):
        """A definition link.exe refuses twice (ordinary section, or NODUPLICATES COMDAT)."""
        flags = self.sections[sym["section"] - 1][4]
        return not flags & COMDAT or census._comdat_selections(self.data).get(sym["section"]) == 1


def digest(raw, size, relocs):
    h = hashlib.sha1(raw if raw is not None else b"uninitialized %d" % size)
    for where, kind, ref in relocs:
        label = census._normal(ref["name"]) if ref["storage"] in (EXTERNAL, WEAK_EXTERNAL) else "local"
        h.update(b"%d:%d:" % (where, kind) + label.encode("latin-1") + b";")
    return h.hexdigest()[:12]


def _object_defs(path):
    """{name: (digest, size, exclusive)} for every EXTERNAL code definition of one object."""
    try:
        o = Obj(path)
    except (OSError, struct.error, ValueError, IndexError):
        return str(path), None
    out = {}
    for s in o.functions():
        if s["storage"] == EXTERNAL and s["name"] not in out:
            raw, size, relocs = o.body(s)
            out[s["name"]] = (digest(raw, size, relocs), size, o.exclusive(s))
    refs = frozenset(s["name"] for s in o.symbols.values() if s["storage"] == EXTERNAL and s["section"] == 0)
    return str(path), (out, refs)


class _Defs(collections.defaultdict):
    referrers = None


def definitions(objs):
    """{name: [(object path, digest, size, exclusive)]} in link order, cached per
    object by (mtime, size) in build/allowed_symbols/defs.pickle; `.referrers`
    is {name: {object path}} of the objects referencing it undefined."""
    cache_file = OUT / "defs.pickle"
    cache = {}
    if cache_file.exists():
        try:
            cache = pickle.loads(cache_file.read_bytes())
        except Exception:
            cache = {}
    stamp = {}
    for p in objs:
        st = p.stat()
        stamp[str(p)] = (st.st_mtime_ns, st.st_size)
    todo = [p for p in objs if cache.get(str(p), (None,))[0] != stamp[str(p)]
            or not isinstance(cache[str(p)][1], tuple)]
    if todo:
        workers = build._pool_size()
        if workers > 1 and len(todo) > 64:
            with concurrent.futures.ProcessPoolExecutor(workers) as pool:
                found = list(pool.map(_object_defs, todo, chunksize=64))
        else:
            found = [_object_defs(p) for p in todo]
        for path, facts in found:
            cache[path] = (stamp[path], facts or ({}, frozenset()))
        OUT.mkdir(parents=True, exist_ok=True)
        cache_file.write_bytes(pickle.dumps(cache))
    out = _Defs(list)
    referrers = collections.defaultdict(set)
    for p in objs:
        defs, refs = cache[str(p)][1]
        for name, (dg, size, excl) in defs.items():
            out[name].append((str(p), dg, size, excl))
        for name in refs:
            referrers[name].add(str(p))
    out.referrers = referrers
    return out


_OBJECTS = {}


def row_object(row):
    """build.row_object without Path.resolve(): ledger sources are already
    repo-relative, and resolving 64k of them costs ~30 s on Windows."""
    src = row["source"]
    member = build.ledger_member(row) if src.lower().endswith(build.LIB_SUFFIX) else None
    key = (src, member)
    if key not in _OBJECTS:
        stem = "_".join(Path(src).with_suffix("").parts)
        if member is not None:
            stem += "_" + build.member_stem(member)
        _OBJECTS[key] = build.BUILD_DIR / ("".join(("^" + c.lower()) if c.isupper() else c for c in stem) + ".obj")
    return _OBJECTS[key]


def link_order(rows):
    """Existing objects of the rows, in link_census.link_order's order (lowest
    retail RVA of the object's rows, then path)."""
    first = {}
    for row in rows:
        obj, rva = row_object(row), int(row["target_rva"], 16)
        first[obj] = min(first.get(obj, rva), rva)
    return [p for p in sorted(first, key=lambda o: (first[o], o.as_posix())) if p.exists()]


# ---------------------------------------------------------------- identity
class Identity:
    """Retail address identities for one tree (its ledger, its objects)."""

    def __init__(self, rows=None, objs=None, defs=None):
        self.rows = census.ledger() if rows is None else rows
        self.image, self.secs = build.exe_image()
        text = next(s for s in self.secs if s["name"] == ".text")
        self.text = (text["rva"], text["rva"] + text["size"])
        self.at = collections.defaultdict(list)          # start -> rows
        for row in self.rows:
            if "icf-owner=" not in (row.get("notes") or ""):
                self.at[int(row["target_rva"], 16)].append(row)
        spans = sorted(((a, a + max(int(r["target_size"]), 1), r) for a, rs in self.at.items() for r in rs),
                       key=lambda s: (s[0], s[1]))
        self.spans, self.span_starts = spans, [s[0] for s in spans]
        self.ghidra = {}
        with build.GHIDRA_FUNCTIONS.open(encoding="utf-8", newline="") as fh:
            for g in csv.DictReader(fh):
                self.ghidra.setdefault(int(g["rva"], 16), int(g["size"]))
        self.objs = objs
        self.defs = defs
        self.truth = census.RetailTruth(self.rows)
        self._objcache, self._certified, self._extents, self._gstarts = {}, {}, {}, None
        self._local_data_cache = {}
        self._rows_by_object = collections.defaultdict(list)
        for row in self.rows:
            self._rows_by_object[str(row_object(row))].append(row)

    # retail
    def read(self, rva, size):
        try:
            off = build.rva_to_file_offset(self.secs, rva)
        except ValueError:
            return None
        chunk = self.image[off:off + size]
        return chunk if len(chunk) == size else None

    def in_text(self, t):
        return self.text[0] <= t < self.text[1]

    def owner_names(self, t):
        return {n for r in self.at.get(t, ()) for n in (r["name"], build.ledger_object_symbol(r))}

    def container(self, t):
        """(row, offset) of a row whose extent holds t (start excluded), else (None, None)."""
        i = bisect.bisect_right(self.span_starts, t) - 1
        while i >= 0 and self.spans[i][0] > t - 0x10000:
            a, b, r = self.spans[i]
            if a < t < b:
                return r, t - a
            i -= 1
        return None, None

    def extent(self, t, size=None):
        """Retail extent of the function starting at t: its row, else Ghidra's
        boundary. Where neither starts a function at t, a candidate `size` is the
        extent only when t lies in no Ghidra function and retail has nothing but
        padding (CC/90) from t+size to the next function start."""
        rows = self.at.get(t)
        if rows:
            return int(rows[0]["target_size"])
        if t in self.ghidra or size is None:
            return self.ghidra.get(t)
        if self._gstarts is None:
            self._gstarts = sorted(self.ghidra)
        i = bisect.bisect_right(self._gstarts, t)
        if i and self._gstarts[i - 1] + self.ghidra[self._gstarts[i - 1]] > t:
            return None
        nxt = min(x for x in (self._gstarts[i] if i < len(self._gstarts) else None,
                              self.span_starts[bisect.bisect_right(self.span_starts, t)]
                              if bisect.bisect_right(self.span_starts, t) < len(self.span_starts) else None)
                  if x is not None)
        gap = self.read(t + size, nxt - t - size) if nxt >= t + size else None
        return size if gap is not None and not gap.strip(b"\xcc\x90") else None

    def obj(self, path):
        o = self._objcache.get(path)
        if o is None:
            if len(self._objcache) > 256:
                self._objcache.clear()
            o = self._objcache[path] = Obj(path)
        return o

    def local_data_addresses(self, path):
        """Per-object writable-static addresses proved by complete matched callers.

        A local name has no global linker address. An independent caller can
        still establish it: its entire masked body must reproduce its ledger
        extent, and a DIR32 operand binds that local data symbol to retail data.
        Conflicting placements provide no receipt. Read-only literals and
        external names continue through RetailTruth's existing checks.
        """
        if path in self._local_data_cache:
            return self._local_data_cache[path]
        o = self.obj(path)
        found = collections.defaultdict(set)
        for row in self._rows_by_object.get(path, ()):
            sym = o.by_name.get(build.ledger_object_symbol(row))
            if sym is None or not o.is_code(sym):
                continue
            raw, size, relocs = o.body(sym)
            rva, extent = int(row["target_rva"], 16), int(row["target_size"])
            retail = self.read(rva, extent)
            if raw is None or retail is None:
                continue
            if size > extent and not raw[extent:].strip(b"\xcc\x90"):
                raw, size = raw[:extent], extent
            if size != extent:
                continue
            mask, valid = bytearray(raw), True
            for where, kind, _ in relocs:
                width = 2 if kind == 0x000A else 4
                if where < 0 or where + width > extent:
                    valid = False
                    break
                mask[where:where + width] = retail[where:where + width]
            if not valid or bytes(mask) != retail:
                continue
            for where, kind, ref in relocs:
                sec = ref["section"]
                if (kind != DIR32 or ref["storage"] != STATIC
                        or not 0 < sec <= len(o.sections)):
                    continue
                flags = o.sections[sec - 1][4]
                if flags & CODE or not flags & 0x80000000:  # writable data only
                    continue
                target = (struct.unpack_from("<I", retail, where)[0]
                          - struct.unpack_from("<I", raw, where)[0] - BASE) & 0xFFFFFFFF
                if not any(s["name"] in (".data", ".bss") and s["rva"] <= target < s["rva"] + s["size"]
                           for s in self.secs):
                    continue
                found[ref["name"]].add(target)
        out = {name: next(iter(targets)) for name, targets in found.items() if len(targets) == 1}
        self._local_data_cache[path] = out
        return out

    def certify(self, path, name, t):
        """'retail' when object `path`'s definition of `name`, placed at t, has t's
        retail extent and equals retail in bytes and resolved relocations;
        'extent' / 'bytes' / 'unknown' otherwise."""
        key = (path, name, t)
        if key not in self._certified:
            o = self.obj(path)
            sym = o.by_name.get(name)
            raw, size, relocs = o.body(sym) if sym is not None else (None, 0, [])
            ext = self.extent(t, len(raw.rstrip(b"\xcc\x90")) if raw else None)
            self._extents[key] = ext
            if sym is None or ext is None:
                self._certified[key] = "unknown"
            else:
                if raw is not None and size > ext and not raw[ext:].strip(b"\xcc\x90"):
                    size, raw = ext, raw[:ext]         # alignment padding in a non-/Gy section
                if size != ext:
                    self._certified[key] = "extent"
                else:
                    # _judge reads retail from `start` and places own-section labels at
                    # start + their section value: rebase both onto the symbol.
                    base = sym["value"]
                    relocs = [(w, k, {**r, "value": r["value"] - base} if r["section"] == sym["section"] else r)
                              for w, k, r in relocs]
                    # Scoped receipts resolve local data only in this object. NUL
                    # keys cannot collide with any actual COFF external name.
                    local = self.local_data_addresses(path)
                    bindings, resolved = {}, []
                    for w, k, ref in relocs:
                        if k == DIR32 and ref["storage"] == STATIC and ref["name"] in local:
                            local_key = "\0local-data:" + ref["name"]
                            bindings[local_key] = {local[ref["name"]]}
                            ref = {**ref, "name": local_key, "storage": EXTERNAL}
                        resolved.append((w, k, ref))
                    truth = self.truth
                    if bindings:
                        truth = copy.copy(truth)
                        truth.ledger = {**truth.ledger, **bindings}
                    v = truth._judge(t, {**sym, "value": 0}, raw, resolved, size)
                    self._certified[key] = {"retail": "retail", "wrong": "bytes"}.get(v, "unknown")
        return self._certified[key]

    def kept(self, name):
        """The definition link.exe keeps for `name`: the first exclusive one, else
        the first COMDAT copy in link order. (path, distinct digests) or (None, 0)."""
        copies = self.defs.get(name, ())
        if not copies:
            return None, 0
        excl = [c for c in copies if c[3]]
        first = (excl or copies)[0]
        return first[0], len({c[1] for c in copies})

    # classification
    def classify(self, row, o, sym, where, kind, ref, t):
        """(class, detail) for one code reference of `row` (object o, symbol sym) to retail t."""
        name = ref["name"]
        own = build.ledger_object_symbol(row)
        if ref["storage"] not in (EXTERNAL, WEAK_EXTERNAL):
            if name.startswith(EH_PREFIX):
                return ("eh", "") if own in name else ("wrong", "foreign-eh")
            if ref["section"] == sym["section"]:
                return "label", ""
            if name in self.owner_names(t):
                return "owner", ""
            if name.startswith("$") or name.startswith(".text"):
                return "label", "section"   # a section symbol: the COMDAT itself or a $L table
            if not self.at.get(t):
                r, off = self.container(t)
                if r is not None:
                    return "interior", f"{r['name']}+0x{off:x}"
                st = self.certify(str(o.path), name, t) if o.by_name.get(name) else "unknown"
                return "unowned", "match" if st == "retail" else st
            st = self.certify(str(o.path), name, t)
            return ("fold", "static") if st == "retail" else ("wrong", "static-" + st)
        if name in self.owner_names(t):
            return "owner", ""
        if not self.at.get(t):
            r, off = self.container(t)
            if r is not None:
                return "interior", f"{r['name']}+0x{off:x}"
        path, variants = self.kept(name)
        if path is None:
            if self.at.get(t):
                # bind to the symbol the owner's object defines, not a ledger label
                return "alias", min(build.ledger_object_symbol(r) for r in self.at[t])
            return "unowned", "undefined"
        st = self.certify(path, name, t)
        if not self.at.get(t):
            return "unowned", "match" if st == "retail" else st
        if st == "retail":
            return "fold", ""
        return ("divergent" if variants > 1 else "wrong"), st

    def row_refs(self, row):
        """[(offset, kind, symbol, retail target, class, detail)] for a matched row's
        code references (REL32 and DIR32 into retail .text)."""
        src = row["source"]
        if src.lower().endswith((".asm", build.LIB_SUFFIX)):
            return []
        path = row_object(row)
        if not path.exists():
            return []
        o = self.obj(str(path))
        name = build.ledger_object_symbol(row)
        sym = o.by_name.get(name)
        if sym is None or not o.is_code(sym):
            return []
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        raw, _, relocs = o.body(sym)
        retail = self.read(rva, size)
        if retail is None:
            return []
        out = []
        for where, kind, ref in relocs:
            if kind not in (REL32, DIR32) or where + 4 > size:
                continue
            v = struct.unpack_from("<I", retail, where)[0]
            t = (rva + where + 4 + v) & 0xFFFFFFFF if kind == REL32 else (v - BASE) & 0xFFFFFFFF
            if not self.in_text(t):
                continue
            cls, detail = self.classify(row, o, sym, where, kind, ref, t)
            out.append((where, kind, ref["name"], t, cls, detail))
        return out


def load(sources=None):
    """(Identity, rows to check). Definitions cover every object of the tree;
    the rows checked are all matched rows, or those in `sources`."""
    rows = census.ledger()
    # link_census.objects() also extracts library members; a member not
    # extracted yet defines nothing here, as in the link that needs it
    objs = link_order(rows)
    ident = Identity(rows, objs, definitions(objs))
    if sources:
        want = {s.replace("\\", "/") for s in sources}
        rows = [r for r in rows if r["source"] in want]
    return ident, rows


def scan(ident, rows):
    """[(row, offset, kind, symbol, target, class, detail)] over `rows`."""
    out = []
    for row in rows:
        try:
            refs = ident.row_refs(row)
        except (OSError, ValueError, struct.error, IndexError):
            continue
        for ref in refs:
            out.append((row,) + ref)
    return out


def key(rec):
    """Baseline key of a wrong binding: stable across offsets and line moves."""
    row, _, _, name, t, cls, _ = rec
    return "\t".join((row["source"], row["name"], name, "0x%08X" % t, cls))


def alternatenames(found):
    """{alias: owner} for every `alias` reference: the only /ALTERNATENAME lines a
    link may use. A name referenced at two addresses gets none (not a function)."""
    seen = collections.defaultdict(set)
    for row, _, _, name, t, cls, detail in found:
        if cls == "alias":
            seen[name].add(detail)
    return {name: next(iter(d)) for name, d in seen.items() if len(d) == 1}


def pragma_alternatenames(paths):
    """[(path, alias, target)] for every `/alternatename` pragma in these sources."""
    out = []
    for p in paths:
        try:
            text = (ROOT / p).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for m in ALTERNATENAME.finditer(text):
            out.append((p, m.group(1), m.group(2)))
    return out


def judge_alternatename(ident, alias, target, targets):
    """'ok' when target is a symbol allowed at the one retail address the alias is
    referenced at; 'unreferenced' when no matched row references it; else 'wrong'."""
    ts = targets.get(alias, set())
    if not ts:
        return "unreferenced"
    if len(ts) > 1:
        return "wrong"
    t = next(iter(ts))
    return "ok" if target in ident.owner_names(t) else "wrong"


# ---------------------------------------------------------------- name tiers
PLACEHOLDER = (build.GEN_PLACEHOLDER_RE, build.DUP_ALIAS_RE, re.compile(r"\bsub_[0-9A-Fa-f]{8}|\?d_[0-9a-f]{8}@"))


def name_tier(row, exports):
    """evidence / unverified / address for one row's name, from facts the tool can
    check: vendored library code, prebuilt library members and retail's export
    table name a function independently of any agent; an address-derived or
    generator name claims no identity; everything else is an unverified label."""
    name, notes = row["name"], row.get("notes") or ""
    if any(p.search(name) for p in PLACEHOLDER) or build.is_scaffold_row(row) \
            or build.is_ghidra_autoname(name, int(row["target_rva"], 16)):
        return "address", "placeholder"
    if "vendored=" in notes:
        return "evidence", "vendored"
    if row["source"].lower().endswith(build.LIB_SUFFIX):
        return "evidence", "lib-member"
    if {name, name[1:] if name.startswith("_") else name} & exports.get(int(row["target_rva"], 16), set()):
        return "evidence", "export"
    return "unverified", ""


def tiers_text(rows):
    exports = collections.defaultdict(set)
    path = ROOT / "reverse" / "exports.csv"
    if path.exists():
        with path.open(encoding="utf-8", newline="") as fh:
            for e in csv.DictReader(fh):
                for rva in {e.get("rva"), e.get("target_rva")} - {None, ""}:
                    exports[int(rva, 16)].add(e.get("name") or "")
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(["name", "target_rva", "name_tier", "evidence"])
    for row in sorted(rows, key=lambda r: (int(r["target_rva"], 16), r["name"])):
        tier = name_tier(row, exports)
        if tier[0] != "unverified":          # a row not listed is `unverified`
            w.writerow([row["name"], row["target_rva"], *tier])
    return out.getvalue()


# ---------------------------------------------------------------- CLI
def report(found):
    by = collections.Counter(rec[5] for rec in found)
    detail = collections.Counter((rec[5], rec[6]) for rec in found if rec[5] in WRONG + ("alias",))
    rows_wrong = {id(rec[0]) for rec in found if rec[5] in WRONG}
    print("references:", sum(by.values()))
    for cls, n in by.most_common():
        print(f"  {cls:10} {n}")
    print("rows with a wrong binding:", len(rows_wrong))
    for (cls, d), n in detail.most_common(25):
        if cls != "alias":
            print(f"  {cls}/{d or '-'}: {n}")


def write_refs(found, path):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as fh:
        w = csv.writer(fh, delimiter="\t", lineterminator="\n")
        w.writerow(["source", "row", "row_rva", "offset", "kind", "symbol", "target", "class", "detail"])
        for row, where, kind, name, t, cls, detail in found:
            if cls not in ("owner", "label", "eh"):
                w.writerow([row["source"], row["name"], row["target_rva"], where, "REL32" if kind == REL32 else "DIR32",
                            name, "0x%08X" % t, cls, detail])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--source", nargs="*", help="only rows in these sources")
    ap.add_argument("--alternatenames", action="store_true", help="write build/allowed_symbols/alternatename.txt")
    ap.add_argument("--tiers", action="store_true", help="write reverse/name_tiers.csv")
    args = ap.parse_args(argv)
    if args.tiers:
        TIERS.write_text(tiers_text(census.ledger()), encoding="utf-8", newline="\n")
        print("wrote", TIERS.relative_to(ROOT))
        return 0
    ident, rows = load(args.source)
    found = scan(ident, rows)
    report(found)
    write_refs(found, OUT / "refs.tsv")
    if args.alternatenames:
        alt = alternatenames(found)
        (OUT / "alternatename.txt").write_text("".join(f"/ALTERNATENAME:{a}={b}\n" for a, b in sorted(alt.items())))
        print("alternatenames:", len(alt))
    return 0


if __name__ == "__main__":
    sys.exit(main())
