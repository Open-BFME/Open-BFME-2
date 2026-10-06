#!/usr/bin/env python3
"""Derive the data ledger: one row per retail global the matched code reaches.

Every DIR32 relocation in a matched row's object names a symbol, and the retail
bytes under it give that symbol's retail address (retail dword less the
in-place addend), the same derivation tools/name_globals.py uses. Grouping
those bindings by retail address shows every name the tree uses for one retail
global, and the objects' symbol tables show which translation units define
each name. Research 29/31 measured this as the largest link lever: one empty
string reached through several invented globals, `TheScriptEngine` also
defined as `g_Va009FE16C`, and so on.

reverse/data_ledger.csv (tool-written; never edit by hand), one row per retail
address, sorted:

  address   rva of the global (retail base of the bound symbol)
  size      bytes to the next ledger address or the section end (an upper bound)
  section   retail section (.rdata, .data, .bss is .data past its raw size)
  kind      string | wstring | float | vtable | rtti | import | global
  name      the canonical symbol: a compiler-emitted literal/vtable name if one
            is bound here; else an external name over a TU-local static; then
            one that is not address-invented (no 6-8 digit hex token); then a
            defined one; then the most referenced; ties by name
  source    the TU that defines `name` (several: the one whose rows reference
            it most -- provisional, research sol61 round 2); empty if none
  status    literal (compiler-emitted), owned (one name, one definition),
            provisional (several names or definitions), unowned (no TU
            defines the name)
  names     when several names are bound here, all of them, `;`-joined; a
            TU-local (static) name is written name@source
  defs      distinct non-COMDAT definitions of all those names in matched
            objects (a COMDAT literal or selectany copy is one global by design)
  refs      relocation sites in matched rows that reach this address

It is not Open-BFME-1's data_rows.csv (a byte-verified ownership ledger the
census links): tools/link_census.py refuses to run while a data_rows.csv
exists, and nothing here is byte-verified. It is the address index the data
sweep (tools/data_sweep.py) and the DIR32 check (tools/data_check.py) key on.

  python3 tools/data_ledger.py            # rewrite reverse/data_ledger.csv
  python3 tools/data_ledger.py --check    # exit 1 if the file is stale
"""
import argparse
import collections
import csv
import io
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

LEDGER = ROOT / "reverse" / "data_ledger.csv"
FIELDS = ["address", "size", "section", "kind", "name", "source", "status", "names", "defs", "refs"]
IMAGE_BASE = 0x400000
DIR32 = 0x0006
EXTERNAL, STATIC = 2, 3
CODE, UNINIT, COMDAT = 0x20, 0x80, 0x1000
# an address-invented identifier: g_Va009FE16C, g_00DFEEF8, TheRva00222A8BTarget,
# g_bfmeAptBreakOnAssertAtDDC01C -- a 6-8 digit hex run holding a digit
INVENTED = re.compile(r"(?:^|[a-z_]|Va|Rva|At)(?=[0-9A-F]*[0-9])[0-9A-F]{6,8}(?![0-9A-F])")
EMITTED = (("??_C@_1", "wstring"), ("??_C@", "string"), ("__real@", "float"), ("__xmm@", "float"),
           ("??_7", "vtable"), ("??_R", "rtti"), ("__TI", "rtti"), ("__CT", "rtti"), ("__imp_", "import"))


def identifier(symbol):
    """The source identifier of a decorated or C symbol (best effort)."""
    found = re.match(r"^\?(\w+)@", symbol)
    if found:
        return found.group(1)
    return symbol[1:] if symbol.startswith("_") else symbol


def kind_of(symbol):
    for prefix, kind in EMITTED:
        if symbol.startswith(prefix):
            return kind
    return "global"


def invented(symbol):
    return kind_of(symbol) == "global" and bool(INVENTED.search(identifier(symbol)))


def retail_sections():
    """[(name, start rva, raw size, virtual size)] of the retail image."""
    data = build.EXE.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count, optional = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    table = pe + 24 + optional
    out = []
    for i in range(count):
        at = table + 40 * i
        name = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        vsize, rva, rsize = struct.unpack_from("<III", data, at + 8)
        out.append((name, rva, rsize, vsize))
    return out


def section_of(sections, rva):
    for name, start, rsize, vsize in sections:
        if start <= rva < start + max(vsize, rsize):
            return name, start + max(vsize, rsize)
    return None, None


def matched_rows():
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r.get("status") == "matched"
                and (r.get("target_rva") or "").startswith("0x")
                and r["source"].lower().endswith((".c", ".cpp"))]


def layout(obj):
    stat = obj.stat()
    return build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)


CACHE = ROOT / "build" / "data_ledger_collect2.pkl"


def collect(rows=None):
    """collect_uncached, memoised in build/ against every input object's
    (path, mtime, size) and the ledger rows read."""
    import hashlib
    import pickle
    rows = matched_rows() if rows is None else rows
    h = hashlib.sha256()
    for row in rows:
        obj = build.row_object(row)
        st = obj.stat() if obj.exists() else None
        h.update(f"{row['name']}|{row['source']}|{row['target_rva']}|{row['target_size']}|{row.get('notes', '')}|"
                 f"{st and (st.st_mtime_ns, st.st_size)};".encode("utf-8", "replace"))
    key = h.hexdigest()
    if CACHE.exists():
        try:
            cached = pickle.loads(CACHE.read_bytes())
            if cached[0] == key:
                return cached[1]
        except Exception:
            pass
    result = collect_uncached(rows)
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    CACHE.write_bytes(pickle.dumps((key, (dict(result[0]), dict(result[1]), result[2], dict(result[3])))))
    return result


def collect_uncached(rows=None):
    """Bindings and definitions from the matched objects present on disk.

    Returns (bind, defs, missing, refsrc):
      bind  {rva: Counter{(name, source or None): sites}}  -- a TU-local name keeps its source
      defs  {name: [(source, storage, initialized, section name, comdat)]}  -- data symbols only
      missing  count of matched sources without an object
      refsrc  {name: {source}}  -- the TUs whose matched rows reference each name
    """
    rows = matched_rows() if rows is None else rows
    sections = retail_sections()
    text = next((s for s in sections if s[0] == ".text"), None)
    bind = collections.defaultdict(collections.Counter)
    defs = collections.defaultdict(list)
    refsrc = collections.defaultdict(set)
    seen, missing = set(), set()
    for row in rows:
        obj = build.row_object(row)
        if not obj.exists():
            missing.add(row["source"])
            continue
        if row["source"] not in seen:
            seen.add(row["source"])
            _data, osecs, symbols = layout(obj)
            for s in symbols:
                if s["section"] <= 0 or s.get("storage") not in (EXTERNAL, STATIC) or s["name"].startswith(("$", ".")):
                    continue
                sec = osecs[s["section"] - 1]
                if sec["characteristics"] & CODE or s["value"] == 0 and s["storage"] == STATIC and s["name"] == sec["name"]:
                    continue
                defs[s["name"]].append((row["source"], s["storage"], not sec["characteristics"] & UNINIT,
                                        sec["name"], bool(sec["characteristics"] & COMDAT)))
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = build.read_target_bytes(rva, size)
            body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        except (ValueError, OSError, SystemExit):
            continue
        local = local_names(obj)
        for offset, kind, symbol in relocs:
            if kind != DIR32 or offset + 4 > min(size, len(body), len(target)) or symbol.startswith(("$", "__ehhandler$")):
                continue
            base = (struct.unpack_from("<I", target, offset)[0] - struct.unpack_from("<I", body, offset)[0]
                    - IMAGE_BASE) & 0xFFFFFFFF
            if text and text[1] <= base < text[1] + text[3]:
                continue                              # a code address: not data
            bind[base][(symbol, row["source"] if symbol in local else None)] += 1
            refsrc[symbol].add(row["source"])
    # a name defined only as a TU-local static in other TUs is not this TU's
    return bind, defs, len(missing), refsrc


_local_cache = {}


def local_names(obj):
    key = str(obj)
    if key not in _local_cache:
        _d, _s, symbols = layout(obj)
        external = {s["name"] for s in symbols if s.get("storage") == EXTERNAL}
        _local_cache[key] = {s["name"] for s in symbols if s.get("storage") == STATIC and s["section"] > 0} - external
    return _local_cache[key]


def choose(names, defs, refs_by_source):
    """(canonical (name, source), owner source, status) for one address."""
    def score(key):
        name, local = key
        emitted = kind_of(name) != "global"
        defined = bool(local) or any(d[1] == EXTERNAL for d in defs.get(name, ()))
        return (not emitted, local is not None, invented(name), not defined, -names[key], name)
    best = min(names, key=score)
    name, local = best
    if kind_of(name) != "global":
        return best, "", "literal"
    owners = [local] if local else sorted({d[0] for d in defs.get(name, ()) if d[1] == EXTERNAL})
    if not owners:
        return best, "", "unowned"
    owner = max(owners, key=lambda s: (refs_by_source[s], s)) if len(owners) > 1 else owners[0]
    status = "owned" if len(owners) == 1 and len(names) == 1 else "provisional"
    return best, owner, status


def ledger_rows(bind, defs):
    sections = retail_sections()
    bases = sorted(bind)
    out = []
    for i, base in enumerate(bases):
        names = bind[base]
        sec, end = section_of(sections, base)
        nxt = bases[i + 1] if i + 1 < len(bases) else None
        size = (min(nxt, end) if nxt is not None and end is not None else (end or base)) - base
        refs_by_source = collections.Counter()
        for (name, local), n in names.items():
            for src in {d[0] for d in defs.get(name, ())} if local is None else {local}:
                refs_by_source[src] += n
        (name, local), owner, status = choose(names, defs, refs_by_source)
        definitions = set()
        for n, loc in names:
            if loc is not None:
                definitions.add((n, loc))
            else:
                definitions |= {(n, d[0]) for d in defs.get(n, ()) if d[1] == EXTERNAL and not d[4]}
        kinds = [kind_of(n) for n, _ in names if kind_of(n) != "global"]
        out.append({
            "address": f"0x{base:08X}", "size": max(size, 0), "section": sec or "",
            "kind": kinds[0] if kinds else "global", "name": name, "source": owner, "status": status,
            "names": ";".join(sorted(n if loc is None else f"{n}@{loc}" for n, loc in names)) if len(names) > 1 else "",
            "defs": len(definitions), "refs": sum(names.values())})
    return out


def render(rows):
    buffer = io.StringIO()
    writer = csv.DictWriter(buffer, FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    return buffer.getvalue()


def load(path=LEDGER):
    """{rva: row} of the committed ledger."""
    if not path.exists():
        return {}
    with path.open(newline="", encoding="utf-8") as handle:
        return {int(r["address"], 16): r for r in csv.DictReader(handle)}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true", help="exit 1 when the committed ledger is stale")
    parser.add_argument("--out", default=str(LEDGER))
    args = parser.parse_args(argv)
    bind, defs, missing, _refsrc = collect()
    if missing:
        print(f"data_ledger: {missing} matched source(s) have no object; build first", file=sys.stderr)
    text = render(ledger_rows(bind, defs))
    out = Path(args.out)
    if args.check:
        current = out.read_text(encoding="utf-8") if out.exists() else ""
        if current != text:
            print("data_ledger: reverse/data_ledger.csv is stale; run python3 tools/data_ledger.py")
            return 1
        return 0
    out.write_text(text, encoding="utf-8", newline="")
    stats = collections.Counter(r["status"] for r in ledger_rows(bind, defs))
    print(f"data_ledger: {sum(stats.values())} addresses {dict(stats)} -> {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
