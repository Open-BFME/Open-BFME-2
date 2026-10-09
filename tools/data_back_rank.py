#!/usr/bin/env python3
"""Rank link_cycle data-back failures by the retail data address behind them.

link_cycle fails a reference `data-back:<symbol>` when the retail address it
reaches is reached through more than one linked address: the tree links two
globals (two names, or two copies of one) where retail has one. One bad
reference fails every row touching that address, so this tool counts the
failures per retail address, not per symbol. Symbols map to addresses through
reverse/data_ledger.csv (`name`, `names`; a TU-local static is name@source and
is matched only for rows of that source).

With link_cycle's per-row output (`--status link_status.csv`, plain or .gz,
e.g. the link_status-<sha10>.csv.gz asset of the link-cycle-artifacts
release), each address is ranked by the distinct retail bytes of placed rows
(kind `real` unless --kind all) failing data-back through any of its names.
`sole` is the part whose only failures are data-back through this address: the
rows a fix here alone would make self-strict. A row failing through several
addresses counts under each.

Without one the ranking is PROVISIONAL: every address with several names or
several definitions, by the distinct bytes of matched `real` rows that
reference it in retail. `--refs relocs` (default) reads retail's base
relocations (lost pages recovered, tools/boot_image.py); `--refs xrefs` reads
reverse/data_xrefs.tsv callers matched to row starts, which data_xrefs caps at
twelve functions per address (flagged `capped`). Rows are given to a name when
their source's object references it.

Per address: section (.rdata const; .data/.bss mutable), kind, ledger defs and
refs, the rows' other blocker classes (status mode), and every name with
  files  sources whose object (build/match, or --objects DIR) references or
         defines it; defs counts the non-COMDAT definitions among them
  inv    address-invented (g_Va.., g_00.., g_Rva.., rva.., a Rva<hex> class)
  @src   a TU-local static of that source
  var    one qualified name spelled with several type encodings: `base` is the
         ledger's name (else the most used), the others are labelled by how
         they differ from it: struct/class (U vs V), const (cv or
         pointer-const only), type (anything else)
Object symbol scans are cached in build/data_back_rank_objects.pkl.

  python3 tools/data_back_rank.py --status build/link_status-<sha10>.csv.gz
  python3 tools/data_back_rank.py [--refs relocs|xrefs] [--top 20] [--detail 5]
          [--address 0x7BAC1C ...] [--list-files N] [--json OUT]
          [--objects DIR | --no-objects]
"""
import argparse
import bisect
import collections
import csv
import gzip
import hashlib
import io
import json
import pickle
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "reverse" / "data_ledger.csv"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
XREFS = ROOT / "reverse" / "data_xrefs.tsv"
OBJECTS = ROOT / "build" / "match"
CACHE = ROOT / "build" / "data_back_rank_objects.pkl"
IMAGE_BASE = 0x400000
XREF_CAP = 12                                 # tools/data_xrefs.py keeps most_common(12) callers
# as tools/data_ledger.py: a 6-8 digit hex run holding a digit; plus an 8-digit
# address glued to a capitalised word (g_Rva0107301CEmptyString)
INVENTED = re.compile(r"(?:^|[a-z_]|Va|Rva|At)(?=[0-9A-F]*[0-9])[0-9A-F]{6,8}(?![0-9A-F])"
                      r"|(?:Va|Rva|_)(?=[0-9A-F]{0,7}[0-9])[0-9A-F]{8}(?=[A-Z][a-z])")
EMITTED = (("??_C@_1", "wstring"), ("??_C@", "string"), ("__real@", "float"), ("__xmm@", "float"),
           ("??_7", "vtable"), ("??_R", "rtti"), ("__TI", "rtti"), ("__CT", "rtti"), ("__imp_", "import"))
REPEAT = re.compile(r"x(\d+)$")
LOCAL = re.compile(r"^(.+)@([^@]*/[^@]*\.(?:c|cpp|asm|lib))$", re.I)   # name@source
GEN_KINDS = ("gen-funclet", "gen-import", "gen-alias")
EXTERNAL, STATIC, COMDAT = 2, 3, 0x1000


# ---------------------------------------------------------------- names
def kind_of(symbol):
    for prefix, kind in EMITTED:
        if symbol.startswith(prefix):
            return kind
    return "global"


def identifier(symbol):
    found = re.match(r"^\?(\w+)@", symbol)
    if found:
        return found.group(1)
    return symbol[1:] if symbol.startswith("_") else symbol


def invented(symbol):
    """An address-invented name; a vtable counts when its class name is one."""
    return kind_of(symbol) in ("global", "vtable") and bool(INVENTED.search(identifier(symbol)))


def split_type(symbol):
    """(qualified name, type encoding) of a decorated data symbol; (symbol, '')
    for C names and compiler-emitted ones."""
    if not symbol.startswith("?") or kind_of(symbol) != "global":
        return symbol, ""
    found = re.search(r"@@[0-4]", symbol)
    if found:
        return symbol[:found.start() + 2], symbol[found.start() + 2:]
    last = None
    for last in re.finditer(r"@[0-4]", symbol):
        pass
    if last is not None:                      # a function-local static: ...@4DB
        return symbol[:last.start() + 1], symbol[last.start() + 1:]
    return symbol, ""


def variant_kind(a, b):
    """How two type encodings of one qualified name differ."""
    if len(a) != len(b):
        return "type"
    kinds = set()
    for x, y in zip(a, b):
        if x == y:
            continue
        pair = {x, y}
        if pair == {"U", "V"}:
            kinds.add("struct/class")
        elif pair <= set("ABCD") or pair == {"P", "Q"}:
            kinds.add("const")
        else:
            return "type"
    return "+".join(sorted(kinds)) or "same"


# ---------------------------------------------------------------- inputs
def open_text(path):
    path = Path(path)
    with path.open("rb") as handle:
        gz = handle.read(2) == b"\x1f\x8b"
    if gz:
        return io.TextIOWrapper(gzip.open(path), encoding="utf-8", newline="")
    return path.open(encoding="utf-8", newline="")


def load_ledger(path=LEDGER):
    """{address: row}; row['bound'] = [(symbol, local source or None)]."""
    out = {}
    with open_text(path) as handle:
        for row in csv.DictReader(handle):
            names = []
            for item in (row["names"].split(";") if row["names"] else [row["name"]]):
                found = LOCAL.match(item)
                names.append((found.group(1), found.group(2)) if found else (item, None))
            row["bound"] = names
            row["defs"] = int(row["defs"] or 0)
            row["refs"] = int(row["refs"] or 0)
            row["size"] = int(row["size"] or 0)
            out[int(row["address"], 16)] = row
    return out


def name_index(ledger):
    """({symbol: {address}}, {(symbol, source): {address}}) over every bound name; a
    single-name address also answers (name, owner source) for a static owner."""
    glob, local = collections.defaultdict(set), collections.defaultdict(set)
    for address, row in ledger.items():
        for symbol, source in row["bound"]:
            if source is None:
                glob[symbol].add(address)
                if not row["names"] and row["source"]:
                    local[(symbol, row["source"])].add(address)
            else:
                local[(symbol, source)].add(address)
    return glob, local


def resolve(symbol, source, glob, local):
    return local.get((symbol, source)) or glob.get(symbol) or set()


def row_kind(notes):
    return next((k for k in GEN_KINDS if k in notes), "real")


def load_rows(path=FUNCTIONS, kind="real"):
    """Matched ledger rows: [(rva, size, name, source)] of the kind wanted."""
    out = []
    with open_text(path) as handle:
        for row in csv.DictReader(handle):
            if row.get("status") != "matched" or not (row.get("target_rva") or "").startswith("0x"):
                continue
            if kind != "all" and row_kind(row.get("notes", "")) != kind:
                continue
            try:
                out.append((int(row["target_rva"], 16), int(row["target_size"], 0), row["name"], row["source"]))
            except ValueError:
                continue
    return out


def parse_failures(text, known=()):
    """[(class, symbol or None, count)] of one link_status `failures` cell."""
    out = []
    for token in filter(None, (text or "").split(";")):
        cls, sep, symbol = token.partition(":")
        count = 1
        if sep:
            found = REPEAT.search(symbol)
            if found and symbol not in known and found.start() > 0:
                symbol, count = symbol[:found.start()], int(found.group(1))
            out.append((cls, symbol, count))
        else:
            found = REPEAT.search(cls)
            if found and found.start() > 0:
                cls, count = cls[:found.start()], int(found.group(1))
            out.append((cls, None, count))
    return out


def unique_bytes(spans):
    total, end = 0, None
    for start, stop in sorted(spans):
        if end is None or start >= end:
            total += stop - start
            end = stop
        elif stop > end:
            total += stop - end
            end = stop
    return total


# ---------------------------------------------------------------- objects
def object_name(source):
    """tools/build.py obj_path's file name for a repo-relative source."""
    stem = "_".join(Path(source).with_suffix("").parts)
    return "".join(("^" + c.lower()) if c.isupper() else c for c in stem) + ".obj"


def coff_symbols(path):
    """(referenced, defined non-COMDAT, defined COMDAT) symbol names of a COFF object."""
    with open(path, "rb") as handle:
        head = handle.read(20)
        if len(head) < 20:
            return None
        machine, nsec, _stamp, ptr, nsym, optional = struct.unpack_from("<HHIIIH", head)
        if machine == 0 and nsec == 0xFFFF:
            return None                       # bigobj / import object: not a VC7.1 TU
        handle.seek(20 + optional)
        headers = handle.read(40 * nsec)
        flags = [struct.unpack_from("<I", headers, 40 * i + 36)[0] for i in range(len(headers) // 40)]
        handle.seek(ptr)
        table = handle.read(nsym * 18 + 4)
        if len(table) < nsym * 18 + 4:
            return None
        size = struct.unpack_from("<I", table, nsym * 18)[0]
        strings = table[nsym * 18:] + handle.read(max(0, size - 4))
    ref, defined, comdat = set(), set(), set()
    i = 0
    while i < nsym:
        entry = table[i * 18:i * 18 + 18]
        section, storage = struct.unpack_from("<h", entry, 12)[0], entry[16]
        if storage in (EXTERNAL, STATIC) and (storage == EXTERNAL or section > 0):
            if entry[:4] == b"\0\0\0\0":
                at = struct.unpack_from("<I", entry, 4)[0]
                name = strings[at:strings.index(b"\0", at)]
            else:
                name = entry[:8].rstrip(b"\0")
            name = name.decode("latin-1")
            if section <= 0:
                ref.add(name)
            elif 0 < section <= len(flags) and flags[section - 1] & COMDAT:
                comdat.add(name)
            else:
                defined.add(name)
        i += 1 + entry[17]
    return ref, defined, comdat


def object_symbols(objects, sources, wanted, cache=CACHE):
    """{source: (referenced, defined, comdat)} restricted to `wanted`, for every
    source with an object under `objects`; cached against (mtime, size)."""
    digest = hashlib.sha256("\n".join(sorted(wanted)).encode("utf-8", "replace")).hexdigest()
    store = {}
    if cache and Path(cache).exists():
        try:
            saved = pickle.loads(Path(cache).read_bytes())
            if saved.get("wanted") == digest:
                store = saved["objects"]
        except Exception:
            store = {}
    out, fresh = {}, {}
    for source in sorted(sources):
        if not source.lower().endswith((".c", ".cpp", ".asm")):
            continue
        path = Path(objects) / object_name(source)
        try:
            st = path.stat()
        except OSError:
            continue
        key = str(path)
        hit = store.get(key)
        if hit is None or hit[0] != (st.st_mtime_ns, st.st_size):
            got = coff_symbols(path)
            if got is None:
                continue
            hit = ((st.st_mtime_ns, st.st_size), tuple(frozenset(x & wanted) for x in got))
        fresh[key] = hit
        out[source] = hit[1]
    if cache and fresh != store:
        Path(cache).parent.mkdir(parents=True, exist_ok=True)
        Path(cache).write_bytes(pickle.dumps({"wanted": digest, "objects": fresh}))
    return out


# ---------------------------------------------------------------- references
def refs_from_status(path, ledger, kind):
    """Placed rows failing data-back, read from a link_status.csv:
    (hits {address: {"rows": {i}, "names": {symbol or (symbol, source): {i}}}},
     rows [(rva, size, name, source)], back_of [{address, None if unmapped}],
     other_of [{other failure class}], unmapped Counter{symbol: rows}, totals)."""
    glob, local = name_index(ledger)
    known = set(glob) | {s for s, _ in local}
    hits = collections.defaultdict(lambda: {"rows": set(), "names": collections.defaultdict(set)})
    rows, back_of, other_of = [], [], []
    unmapped = collections.Counter()
    with open_text(path) as handle:
        for rec in csv.DictReader(handle):
            if kind != "all" and rec.get("kind", "real") != kind:
                continue
            if str(rec.get("placed", "")).strip().lower() not in ("1", "true"):
                continue
            fails = parse_failures(rec.get("failures", ""), known)
            backs = {s for c, s, _n in fails if c == "data-back" and s}
            if not backs:
                continue
            i = len(rows)
            source = rec.get("source", "")
            rows.append((int(rec["retail_rva"], 16), int(rec["size"]), rec.get("name", ""), source))
            addresses = set()
            for symbol in sorted(backs):
                found = resolve(symbol, source, glob, local)
                if not found:
                    unmapped[symbol] += 1
                    addresses.add(None)
                for address in found:
                    hits[address]["rows"].add(i)
                    key = (symbol, source) if (symbol, source) in ledger[address]["bound"] else symbol
                    hits[address]["names"][key].add(i)
                    addresses.add(address)
            back_of.append(addresses)
            other_of.append({c for c, _s, _n in fails if c != "data-back"})
    totals = {"rows": len(rows), "bytes": unique_bytes([(r[0], r[0] + r[1]) for r in rows])}
    return hits, rows, back_of, other_of, unmapped, totals


def refs_from_relocs(ledger, rows, candidates):
    """{address: {row index}} from retail's base relocations in .text."""
    sys.path.insert(0, str(ROOT / "tools"))
    import boot_image  # noqa: E402  (capstone, pefile, retail game.dat)
    retail = boot_image.Retail()
    sites, _info = boot_image.all_sites(retail)
    tstart, tsize, _raw = retail.secs[".text"]
    return attribute(ledger, rows, candidates,
                     ((site, retail.u32(site) - IMAGE_BASE) for site in sites if tstart <= site < tstart + tsize))


def owner(ledger, bases, candidates, target):
    """The candidate address whose extent holds `target`, else None. A global's
    extent is the ledger's size bound (fields at offsets); a compiler-emitted
    literal, vtable or import is matched at its own address only, since its bound
    runs over unledgered neighbours."""
    k = bisect.bisect_right(bases, target) - 1
    if k < 0 or bases[k] not in candidates:
        return None
    address = bases[k]
    row = ledger[address]
    extent = max(row["size"], 1) if row["kind"] == "global" else 1
    return address if target < address + extent else None


def attribute(ledger, rows, candidates, pairs):
    """{address: {row index}} for (site, target rva) pairs: a target owned by a
    candidate address, a site inside a row."""
    bases = sorted(ledger)
    order = sorted(range(len(rows)), key=lambda i: rows[i][0])
    starts = [rows[i][0] for i in order]
    out = collections.defaultdict(set)
    for site, target in pairs:
        address = owner(ledger, bases, candidates, target)
        if address is None:
            continue
        j = bisect.bisect_right(starts, site) - 1
        for i in (order[x] for x in range(j, max(j - 8, -1), -1)):    # overlapping rows are rare
            if rows[i][0] <= site < rows[i][0] + rows[i][1]:
                out[address].add(i)
    return out


def refs_from_xrefs(ledger, rows, candidates, path=XREFS):
    """({address: {row index}}, {capped address}) from data_xrefs callers matched to
    row starts."""
    by_start = collections.defaultdict(list)
    for i, row in enumerate(rows):
        by_start[row[0]].append(i)
    bases = sorted(ledger)
    out, capped = collections.defaultdict(set), set()
    with open_text(path) as handle:
        for rec in csv.DictReader(handle, delimiter="\t"):
            address = owner(ledger, bases, candidates, int(rec["rva"], 16))
            if address is None:
                continue
            callers = [int(c, 16) for c in rec["callers"].split(",") if c]
            if len(callers) >= XREF_CAP:
                capped.add(address)
            for c in callers:
                out[address].update(by_start.get(c, ()))
    return out, capped


# ---------------------------------------------------------------- report
def name_usage(objsyms):
    """(Counter{name: sources using it}, Counter{name: sources defining it non-COMDAT})."""
    users, defs = collections.Counter(), collections.Counter()
    for ref, defined, comdat in (objsyms or {}).values():
        users.update(ref | defined | comdat)
        defs.update(defined)
    return users, defs


def span_bytes(rows, ids):
    return unique_bytes([(rows[i][0], rows[i][0] + rows[i][1]) for i in ids])


def variants(bound, weight, canonical=None):
    """{symbol: variant label}: within each qualified name spelled with several type
    encodings, the ledger's canonical spelling (else the most used one) is `base`,
    every other one is labelled by how it differs from that base (variant_kind)."""
    groups = collections.defaultdict(list)
    for symbol, source in bound:
        prefix, encoding = split_type(symbol)
        if encoding and source is None:
            groups[prefix].append((symbol, encoding))
    out = {}
    for members in groups.values():
        if len({e for _s, e in members}) < 2:
            continue
        base, base_enc = max(members, key=lambda m: (m[0] == canonical, weight(m[0]), m[0]))
        for symbol, encoding in members:
            out[symbol] = "base" if symbol == base else variant_kind(base_enc, encoding)
    return out


def describe(address, row, rows, ids, by_name, usage, other=None, sole=None):
    """One ranked address: ledger facts, its rows' bytes, and every bound name."""
    users, defs = usage
    names = []
    picked = {}
    for symbol, source in row["bound"]:
        picked[(symbol, source)] = by_name.get(symbol if source is None else (symbol, source), set())
    label = variants(row["bound"], lambda s: ((users[s] if users is not None else 0), len(picked[(s, None)])),
                     row["name"])
    for symbol, source in row["bound"]:
        mine = picked[(symbol, source)]
        entry = {"symbol": symbol, "local_source": source, "invented": invented(symbol),
                 "variant": label.get(symbol, ""),
                 "files": 1 if source else (users[symbol] if users is not None else None),
                 "defs": None if source or defs is None else defs[symbol],
                 "rows": len(mine), "bytes": span_bytes(rows, mine)}
        names.append(entry)
    out = {"address": f"0x{address:08X}", "section": row["section"], "kind": row["kind"],
           "ledger_name": row["name"], "ledger_source": row["source"], "status": row["status"],
           "defs": row["defs"], "refs": row["refs"], "size_bound": row["size"],
           "rows": len(ids), "bytes": span_bytes(rows, ids), "names": names}
    if sole is not None:
        out["sole_rows"], out["sole_bytes"] = len(sole), span_bytes(rows, sole)
    if other is not None:
        out["other_blockers"] = dict(other.most_common())
    return out


def short(symbol, width=46):
    return symbol if len(symbol) <= width else symbol[:width - 1] + "~"


def render(report, top, list_files=0, out=None):
    out = out or sys.stdout
    if report["mode"] == "provisional":
        print(f"PROVISIONAL (no link_status.csv): addresses with several names or definitions, ranked by the "
              f"distinct bytes of matched {report['kind']} rows referencing them in retail ({report['refs']}). "
              f"These are not measured data-back failures.", file=out)
    else:
        t = report["totals"]
        print(f"data-back: {t['rows']:,} placed {report['kind']} rows, {t['bytes']:,} distinct bytes "
              f"({report['status']})", file=out)
    if report.get("objects") is None:
        print("files: no objects read (--objects DIR)", file=out)
    print(f"{'#':>3} {'address':10} {'sec':6} {'kind':7} {'names':>5} {'defs':>4} {'refs':>5} {'rows':>5} "
          f"{'bytes':>9} {'sole':>8} {'inv':>3} {'var':>3}  canonical [other blockers]", file=out)
    shown = report["addresses"][:top]
    for n, a in enumerate(shown, 1):
        inv = sum(1 for x in a["names"] if x["invented"])
        var = sum(1 for x in a["names"] if x["variant"] not in ("", "base"))
        sole = f"{a['sole_bytes']:>8,}" if "sole_bytes" in a else f"{'-':>8}"
        tail = short(a["ledger_name"])
        if a.get("other_blockers"):
            tail += " [" + ", ".join(f"{k} {v}" for k, v in list(a["other_blockers"].items())[:3]) + "]"
        if a.get("capped"):
            tail += " (callers capped)"
        print(f"{n:>3} {a['address']:10} {a['section']:6} {a['kind']:7} {len(a['names']):>5} {a['defs']:>4} "
              f"{a['refs']:>5} {a['rows']:>5} {a['bytes']:>9,} {sole} {inv:>3} {var:>3}  {tail}", file=out)
    for a in (a for a in report["addresses"] if a.get("detail")):
        sole = f", sole {a['sole_rows']} rows {a['sole_bytes']:,} bytes" if "sole_bytes" in a else ""
        print(f"\n{a['address']} {a['section']} {a['kind']} ({a['status']}) defs {a['defs']} refs {a['refs']}: "
              f"{a['rows']} rows {a['bytes']:,} bytes{sole}", file=out)
        print(f"  {'files':>5} {'defs':>4} {'rows':>5} {'bytes':>9}  {'flags':18} name", file=out)
        for x in sorted(a["names"], key=lambda x: (-x["bytes"], -(x["files"] or 0), x["symbol"])):
            flags = " ".join(f for f in ("inv" if x["invented"] else "", x["variant"] and "var:" + x["variant"],
                                         "static" if x["local_source"] else "") if f)
            name = x["symbol"] + (f" @{x['local_source']}" if x["local_source"] else "")
            files = "-" if x["files"] is None else x["files"]
            defs = "-" if x["defs"] is None else x["defs"]
            print(f"  {files:>5} {defs:>4} {x['rows']:>5} {x['bytes']:>9,}  {flags:18} {name}", file=out)
            if list_files and not x["local_source"] and x.get("sources"):
                more = len(x["sources"]) - list_files
                print("        " + ", ".join(x["sources"][:list_files]) + (f" (+{more})" if more > 0 else ""),
                      file=out)
        if a.get("other_blockers"):
            print("  other blockers (rows): " + ", ".join(f"{k} {v}" for k, v in a["other_blockers"].items()),
                  file=out)
    if report.get("unmapped"):
        print("\nunmapped data-back symbols (rows): " + ", ".join(
            f"{short(k, 60)} {v}" for k, v in list(report["unmapped"].items())[:10]), file=out)


def build_report(args):
    ledger = load_ledger(args.ledger)
    want = {int(a, 16) for a in args.address}
    objsyms = None
    if not args.no_objects and Path(args.objects).is_dir():
        wanted = frozenset(s for row in ledger.values() for s, src in row["bound"] if src is None)
        with open_text(args.functions) as handle:
            sources = {r["source"] for r in csv.DictReader(handle)}
        objsyms = object_symbols(args.objects, sources, wanted, None if args.no_cache else args.cache)
    usage = name_usage(objsyms) if objsyms is not None else (None, None)
    entries = []
    if args.status:
        hits, rows, back_of, other_of, unmapped, totals = refs_from_status(args.status, ledger, args.kind)
        for address, hit in hits.items():
            ids = hit["rows"]
            other = collections.Counter()
            for i in ids:
                other.update(other_of[i])
                if len(back_of[i]) > 1:
                    other["data-back elsewhere"] += 1
            sole = {i for i in ids if back_of[i] == {address} and not other_of[i]}
            entries.append(describe(address, ledger[address], rows, ids, hit["names"], usage, other, sole))
        report = {"mode": "status", "status": str(args.status), "kind": args.kind, "totals": totals,
                  "unmapped": dict(unmapped.most_common())}
    else:
        rows = load_rows(args.functions, args.kind)
        candidates = {a for a, r in ledger.items() if len(r["bound"]) > 1 or r["defs"] > 1}
        capped = set()
        if args.refs == "xrefs":
            hits, capped = refs_from_xrefs(ledger, rows, candidates, args.xrefs)
        else:
            hits = refs_from_relocs(ledger, rows, candidates)
        for address in candidates:
            ids = hits.get(address, set())
            by_name = {}
            for symbol, src in ledger[address]["bound"]:
                if src is not None:
                    by_name[(symbol, src)] = {i for i in ids if rows[i][3] == src}
                elif objsyms is not None:       # rows whose TU's object names the symbol
                    by_name[symbol] = {i for i in ids if any(symbol in part for part in objsyms.get(rows[i][3], ()))}
            entry = describe(address, ledger[address], rows, ids, by_name, usage)
            entry["capped"] = address in capped
            entries.append(entry)
        report = {"mode": "provisional", "refs": args.refs, "kind": args.kind}
    entries.sort(key=lambda e: (-e["bytes"], -e["refs"], e["address"]))
    if want:
        entries = [e for e in entries if int(e["address"], 16) in want]
    for n, e in enumerate(entries):
        e["detail"] = bool(want) or n < args.detail
        if e["detail"] and objsyms is not None:     # the sources behind each name
            for x in e["names"]:
                x["sources"] = [x["local_source"]] if x["local_source"] else sorted(
                    src for src, parts in objsyms.items() if any(x["symbol"] in part for part in parts))
    report["objects"] = None if objsyms is None else {"dir": str(args.objects), "sources": len(objsyms)}
    report["addresses"] = entries
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--status", help="link_cycle link_status.csv (plain or .gz); omit for the PROVISIONAL ranking")
    ap.add_argument("--refs", choices=("relocs", "xrefs"), default="relocs", help="PROVISIONAL reference source")
    ap.add_argument("--kind", default="real", help="row kind counted: real (default), gen-alias, ..., all")
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("--detail", type=int, default=5, help="per-name detail for the first N addresses")
    ap.add_argument("--address", action="append", default=[], help="only this address, in detail (repeatable)")
    ap.add_argument("--list-files", type=int, default=0, metavar="N",
                    help="under each detailed name, list up to N sources using it")
    ap.add_argument("--json", help="write the report (every ranked address) as JSON")
    ap.add_argument("--ledger", default=str(LEDGER))
    ap.add_argument("--functions", default=str(FUNCTIONS))
    ap.add_argument("--xrefs", default=str(XREFS))
    ap.add_argument("--objects", default=str(OBJECTS), help="compiled objects, tools/build.py naming")
    ap.add_argument("--no-objects", action="store_true", help="skip the per-name file counts")
    ap.add_argument("--cache", default=str(CACHE))
    ap.add_argument("--no-cache", action="store_true")
    args = ap.parse_args(argv)
    report = build_report(args)
    render(report, len(report["addresses"]) if args.address else args.top, args.list_files)
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())


