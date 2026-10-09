#!/usr/bin/env python3
"""Rank link_cycle data-back failures by the retail data address behind them.

link_cycle fails a reference `data-back:<symbol>` when the retail address it
reaches is reached through more than one linked address: the tree links two
globals (two names, or two copies of one) where retail has one. One bad
reference fails every row touching that address, so this tool counts the
failures per retail address, not per symbol. Symbols map to addresses through
reverse/data_ledger.csv (`name`, `names`), each binding (one name at one
address) scoped on its own evidence, never by another binding's spelling:
  static   name@source in `names` (tools/data_ledger.py read it as a TU-local
           symbol of that object), or a single-name `owned` row whose name has
           storage class STATIC in its owner's object: matched only for rows
           of that source
  global   a bare name in `names` (read as non-local), a single-name
           `provisional` or `unowned` row (data_ledger binds a local only as
           `owned`), a compiler-emitted literal no object defines STATIC, or an
           `owned` row whose owner's object defines it EXTERNAL
  unknown  an `owned` row whose owner object is missing (--no-objects, not
           built) or does not define it: matched only for its owner's rows; a
           row of another source reports it as `scope unknown`, never mapped.

With link_cycle's per-row output (`--status link_status.csv`, plain or .gz,
e.g. the link_status-<sha10>.csv.gz asset of the link-cycle-artifacts
release; its header is checked, so the census's reverse/link_status.csv is
refused), each address is ranked by the distinct retail bytes of placed rows
(kind `real` unless --kind all) failing data-back through any of its names.
`sole` is the part whose only failures are data-back through this address: the
rows a fix here alone would make self-strict. A row failing through several
proven addresses counts under each. A data-back symbol that resolves to
several addresses, whose `xN` repeat suffix reads two ways that both resolve
(`_gx2`: `_gx2` once or `_g` twice), or whose only bindings for this row are
of unknown scope, is QUARANTINED: listed apart (`ambiguous`, with a reason and
its candidate addresses) and counted at none. --disambiguate settles the
first two kinds from the row's compiled object: every DIR32 reference to the
symbol in the row's body, its retail target less the reference's in-place
addend (so an interior reference B+4 is the datum at B), must name the same
single candidate. row_unresolved(flags_of[i]) is true for a row with any
unmapped or quarantined data-back symbol.

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
  scope? a binding of unknown scope (no owner object read)
  var    one qualified name spelled with several type encodings: `base` is the
         ledger's name (else the most used), the others are labelled by how
         they differ from it: struct/class (U vs V), const (cv or
         pointer-const only), type (anything else)
Object symbol scans are cached in build/data_back_rank_objects.pkl.

`fold` marks the addresses link_cycle's shadow rule data-fold-1 excuses:
read-only data retail's /OPT:ICF folded, which the /OPT:NOICF link keeps as
several datums whatever the tree does. Without --folds it is `exp?` where
retail's export table (reverse/exports.csv) names the address twice or more:
export-proven, the linked datums unverified. With --folds (link_cycle's
data_fold_list.csv) it is the measured verdict: `export` when excused (at a
datum start: when every reference inside it is), `exp!` for an export-proven
address the rule refused (a mutable, unequal or unfoldable datum, a stub; the
verdict says which), `icf?` for an ICF candidate (counted, never excused). The
data-fold summary counts the referenced addresses excused (one per CSV row) and
the rows failing only data-back at them: what the shadow series
placed_self_strict_data_fold can gain over placed_self_strict, at most.

  python3 tools/data_back_rank.py --status build/link_status-<sha10>.csv.gz [--disambiguate]
          [--folds build/link_cycle/data_fold_list.csv]
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
EXPORTS = ROOT / "reverse" / "exports.csv"
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
# link_cycle writes a repeated token once with `x<count>`, count >= 2, no leading zero
REPEAT = re.compile(r"x([2-9]|[1-9]\d+)$")
LOCAL = re.compile(r"^(.+)@([^@]*/[^@]*\.(?:c|cpp|asm|lib))$", re.I)   # name@source
# tools/link_cycle.py's per-row link_status.csv header (not link_census's reverse/link_status.csv)
STATUS_COLUMNS = ("name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason",
                  "self_strict", "closed_strict", "closed_strict_pilot_rule", "pinned_strict", "byte_equal",
                  "hardcoded", "failure_count", "failures")
GEN_KINDS = ("gen-funclet", "gen-import", "gen-alias")
EXTERNAL, STATIC, COMDAT = 2, 3, 0x1000      # COFF storage classes; section flag
DIR32 = 0x0006
OBJECT_SCAN = "v2: ref, defined, comdat, static"   # object_symbols cache layout
# flags_of[i]: why a row's data-back symbol is counted at no address
UNMAPPED, AMBIGUOUS, SCOPE_UNKNOWN = "unmapped", "ambiguous", "scope unknown"


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
    """{address: row}; row['bound'] = [(symbol, local source or None)] as written,
    row['unknown'] = {symbol: owner source} of bindings whose scope is unproven (set
    by scope_bindings; until then every single-name `owned` binding is unknown)."""
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
    return scope_bindings(out, None)


def scope_bindings(ledger, objsyms):
    """Scope each binding on its own evidence (module doc): a single-name `owned`
    row's name by its storage class in its owner's object (`objsyms` from
    object_symbols; None: no objects read); a compiler-emitted literal is global
    unless some object defines that name STATIC. Every other binding is scoped as
    tools/data_ledger.py wrote it."""
    statics = set()
    for parts in (objsyms or {}).values():
        statics |= parts[3]
    for row in ledger.values():
        row["unknown"] = {}
        if row["names"]:
            continue
        name = row["name"]
        if row["status"] == "literal":
            row["bound"] = [(name, None)]
            if name in statics:
                row["unknown"][name] = None
            continue
        if row["status"] != "owned" or not row["source"]:
            row["bound"] = [(name, None)]            # data_ledger binds a TU-local only as `owned`
            continue
        parts = (objsyms or {}).get(row["source"])
        if parts is not None and name in parts[3]:
            row["bound"] = [(name, row["source"])]
        elif parts is not None and name in parts[1] | parts[2]:
            row["bound"] = [(name, None)]
        else:
            row["bound"] = [(name, None)]
            row["unknown"][name] = row["source"]
    return ledger


def name_index(ledger):
    """({symbol: {address}}, {(symbol, source): {address}}, {symbol: {address}}):
    a global binding answers every row, a static only rows of its own source, an
    unknown-scope binding only its owner's rows (and is listed in the third map)."""
    glob, local, unknown = (collections.defaultdict(set) for _ in range(3))
    for address, row in ledger.items():
        for symbol, source in row["bound"]:
            if symbol in row["unknown"]:
                unknown[symbol].add(address)
                if row["unknown"][symbol]:
                    local[(symbol, row["unknown"][symbol])].add(address)
            elif source is None:
                glob[symbol].add(address)
            else:
                local[(symbol, source)].add(address)
    return glob, local, unknown


def resolve(symbol, source, index):
    """(addresses, unsure) `symbol` can mean in a row of `source`: the source's own
    binding first, else every global one; `unsure` when a binding of unknown scope
    owned elsewhere could also be it (its addresses are then among the candidates)."""
    glob, local, unknown = index
    mine = local.get((symbol, source))
    if mine:
        return set(mine), False
    others = unknown.get(symbol, set())
    return set(glob.get(symbol, ())) | others, bool(others)


def row_unresolved(flags):
    """True when a row (its flags_of entry) has a data-back symbol counted at no
    address: UNMAPPED (no ledger binding), AMBIGUOUS (several candidates, or a repeat
    suffix that reads two ways) or SCOPE_UNKNOWN (only bindings of unproven scope
    owned by another source). Such a row is never clear and never `sole`."""
    return bool(flags)


def load_export_folds(path=EXPORTS):
    """{rva: names} of the data addresses retail's export table names twice or more:
    read-only data retail's /OPT:ICF folded (link_cycle data-fold-1's export rule)."""
    names = collections.defaultdict(list)
    if not Path(path).exists():
        return {}
    with open_text(path) as handle:
        for row in csv.DictReader(handle):
            if row.get("kind") == "data" and (row.get("rva") or "").startswith("0x"):
                names[int(row["rva"], 16)].append(row["name"])
    return {a: sorted(n) for a, n in names.items() if len(n) > 1}


def load_fold_list(path):
    """link_cycle's data_fold_list.csv: {"exact": {referenced retail address: (rule
    or "", verdict)}, "starts": {datum start: [referenced addresses inside it]}}.
    The referenced addresses (one CSV row each) are the canonical set; a datum start
    only points at them."""
    exact, starts = {}, collections.defaultdict(set)
    with open_text(path) as handle:
        for row in csv.DictReader(handle):
            address = int(row["retail_rva"], 16)
            exact[address] = (row["rule"], row["verdict"])
            for start in filter(None, row["retail_start"].split(";")):
                starts[int(start, 16)].add(address)
    return {"exact": exact, "starts": {s: sorted(a) for s, a in starts.items()}}


def fold_verdict(address, folds):
    """(rule or "", verdict) at a ledger address: over its own row and the rows of
    the references inside the datum starting there; excused only when all are."""
    refs = sorted(({address} if address in folds["exact"] else set()) | set(folds["starts"].get(address, ())))
    if not refs:
        return "", "not a data-back address"
    verdicts = [folds["exact"][a] for a in refs]
    refused = [w for r, w in verdicts if r != "export"]
    return ("", refused[0]) if refused else ("export", verdicts[0][1])


def fold_of(address, export_folds, fold_list):
    """data-fold-1 facts of one ranked address (see the module doc's `fold`)."""
    names = len(export_folds.get(address, ()))
    if fold_list is None:
        return {"export_names": names, "rule": None, "verdict": None, "label": "exp?" if names else ""}
    rule, verdict = fold_verdict(address, fold_list)
    label = rule or ("icf?" if verdict == "icf candidate" else "exp!" if names else "")
    return {"export_names": names, "rule": rule or None, "verdict": verdict, "label": label}


def fold_report(entries, export_folds, fold_list, *, rows=None, back_of=None, other_of=None, flags_of=None):
    """The data-fold summary: the addresses data-fold-1 excuses (measured: the
    referenced addresses, one per data_fold_list.csv row; else the export-proven
    candidates), the ledger addresses ranked here they cover, their rows and the
    rows failing only data-back at them (status mode: rows, back_of and other_of
    are refs_from_status's, by row index; keyword-only, so a per-row argument
    can join them)."""
    if fold_list is None:
        canonical = covered = set(export_folds)
        source = "reverse/exports.csv: export-proven, linked datums unverified"
    else:
        canonical = {a for a, (r, _) in fold_list["exact"].items() if r == "export"}
        covered = {a for a in set(fold_list["exact"]) | set(fold_list["starts"])
                   if fold_verdict(a, fold_list)[0] == "export"}
        source = "link_cycle data_fold_list.csv"
    out = {"rule": "data-fold-1", "source": source, "export_fold_addresses": len(export_folds)}
    if fold_list is not None:
        out["icf_candidates"] = sum(1 for _, w in fold_list["exact"].values() if w == "icf candidate")
    part = {"addresses": len(canonical),
            "ranked": [e["address"] for e in entries if int(e["address"], 16) in covered]}
    if rows is not None:
        hit = {i for i, b in enumerate(back_of) if b & covered}
        # A row with a data-back symbol counted at no address (unmapped, ambiguous, scope
        # unknown) may fail somewhere unproven: never clear (row_unresolved).
        unresolved = (lambda i: row_unresolved(flags_of[i])) if flags_of is not None else (lambda i: False)
        clear = {i for i in hit if None not in back_of[i] and back_of[i] <= covered and not other_of[i]
                 and not unresolved(i)}
        part.update(rows=len(hit), bytes=span_bytes(rows, hit), clear_rows=len(clear),
                    clear_bytes=span_bytes(rows, clear))
    out["export"] = part
    return out


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
    """[(class, readings)] of one link_status `failures` cell; readings is
    ((symbol or None, count), ...). link_cycle writes a token seen N > 1 times as
    `<token>x<N>`, which a symbol ending in x<digits> can also spell: `_gx2` is
    `_gx2` once or `_g` twice. `known` (a container or a predicate: does this symbol
    resolve?) picks the reading; when both resolve the token keeps both readings,
    the literal spelling first, and is ambiguous. When neither does, the repeat
    reading is taken (link_cycle's own convention)."""
    test = known if callable(known) else known.__contains__
    out = []
    for token in filter(None, (text or "").split(";")):
        cls, sep, symbol = token.partition(":")
        if sep:
            found = REPEAT.search(symbol)
            if found and found.start() > 0:
                whole, short = (symbol, 1), (symbol[:found.start()], int(found.group(1)))
                as_whole, as_short = test(whole[0]), test(short[0])
                readings = (whole, short) if as_whole and as_short else (whole,) if as_whole else (short,)
            else:
                readings = ((symbol, 1),)
            out.append((cls, readings))
        else:
            found = REPEAT.search(cls)
            if found and found.start() > 0:
                out.append((cls[:found.start()], ((None, int(found.group(1))),)))
            else:
                out.append((cls, ((None, 1),)))
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
def object_name(source, member=None):
    """tools/build.py obj_path's file name for a repo-relative source (and a .lib's
    archive member)."""
    stem = "_".join(Path(source).with_suffix("").parts)
    if member is not None:
        stem += "_" + re.split(r"[\\/]", member)[-1].removesuffix(".obj")
    return "".join(("^" + c.lower()) if c.isupper() else c for c in stem) + ".obj"


def coff_symbols(path):
    """(referenced, defined non-COMDAT, defined COMDAT, defined with storage class
    STATIC and never EXTERNAL) symbol names of a COFF object."""
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
    ref, defined, comdat, static, external = set(), set(), set(), set(), set()
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
            (external if storage == EXTERNAL else static).add(name)
            if section <= 0:
                ref.add(name)
            elif 0 < section <= len(flags) and flags[section - 1] & COMDAT:
                comdat.add(name)
            else:
                defined.add(name)
        i += 1 + entry[17]
    return ref, defined, comdat, static - external


def object_symbols(objects, sources, wanted, cache=CACHE):
    """{source: (referenced, defined, comdat, static)} restricted to `wanted`, for
    every source with an object under `objects`; cached against (mtime, size)."""
    digest = hashlib.sha256("\n".join([OBJECT_SCAN] + sorted(wanted)).encode("utf-8", "replace")).hexdigest()
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
def check_status_header(fields, path):
    """Refuse a file that is not link_cycle's per-row link_status.csv."""
    missing = [c for c in STATUS_COLUMNS if c not in (fields or ())]
    if missing:
        raise SystemExit(
            f"data_back_rank: {path} is not link_cycle's per-row link_status.csv: missing column(s) "
            f"{', '.join(missing)} (header: {', '.join(fields or ()) or 'none'}). reverse/link_status.csv is "
            f"link_census's per-file table; pass the link_status.csv a tools/link_cycle.py run writes, or its "
            f"link_status-<sha10>.csv.gz release asset.")


def refs_from_status(path, ledger, kind, references_of=None):
    """Placed rows failing data-back, read from link_cycle's link_status.csv:
    (hits {address: {"rows": {i}, "names": {symbol or (symbol, source): {i}}}},
     rows [(rva, size, name, source)], back_of [{proven address}],
     flags_of [{UNMAPPED, AMBIGUOUS, SCOPE_UNKNOWN}] (row_unresolved),
     other_of [{other failure class}], unmapped Counter{symbol: rows},
     ambiguous {(symbol, reason, candidates): {i}}, totals). A symbol counts at an
    address only when it resolves to that one address. `references_of(rec)` ->
    [(symbol, retail datum start)] of the row's DIR32 references, or None
    (--disambiguate, object_references) settles a symbol with several candidates
    or a two-way repeat suffix only when every reference to it names the same
    single candidate; a binding of unknown scope is never settled."""
    index = name_index(ledger)
    hits = collections.defaultdict(lambda: {"rows": set(), "names": collections.defaultdict(set)})
    rows, back_of, flags_of, other_of = [], [], [], []
    unmapped = collections.Counter()
    ambiguous = collections.defaultdict(set)
    settled = 0
    with open_text(path) as handle:
        reader = csv.DictReader(handle)
        check_status_header(reader.fieldnames, path)
        for rec in reader:
            if kind != "all" and rec["kind"] != kind:
                continue
            if rec["placed"].strip().lower() not in ("1", "true"):
                continue
            source = rec["source"]
            fails = parse_failures(rec["failures"], lambda s: bool(resolve(s, source, index)[0]))
            backs = [readings for c, readings in fails if c == "data-back" and readings[0][0]]
            if not backs:
                continue
            i = len(rows)
            rva, size = int(rec["retail_rva"], 16), int(rec["size"])
            rows.append((rva, size, rec["name"], source))
            proven, flags = set(), set()
            refs = None
            for readings in sorted(backs):
                label = readings[0][0]               # the token's literal spelling when it reads two ways
                found, unsure = collections.defaultdict(list), False
                for symbol, _n in readings:
                    addresses, doubt = resolve(symbol, source, index)
                    unsure |= doubt
                    for address in addresses:
                        found[address].append(symbol)
                if not found:
                    unmapped[label] += 1
                    flags.add(UNMAPPED)
                    continue
                reason = ("scope unknown" if unsure else "repeat suffix" if len(readings) > 1
                          else "several addresses" if len(found) > 1 else None)
                if reason and not unsure and references_of is not None:
                    if refs is None:
                        refs = references_of(rec) or []
                    names = {symbol for symbol, _n in readings}
                    starts = {start for symbol, start in refs if symbol in names}
                    if len(starts) == 1 and starts <= set(found):
                        found = {a: found[a] for a in starts}
                        reason = None
                        settled += 1
                if reason:
                    ambiguous[(label, reason, tuple(sorted(found)))].add(i)
                    flags.add(SCOPE_UNKNOWN if unsure else AMBIGUOUS)
                    continue
                for address, symbols in found.items():
                    hits[address]["rows"].add(i)
                    for symbol in symbols:
                        key = (symbol, source) if (symbol, source) in ledger[address]["bound"] else symbol
                        hits[address]["names"][key].add(i)
                    proven.add(address)
            back_of.append(proven)
            flags_of.append(flags)
            other_of.append({c for c, _r in fails if c != "data-back"})
    totals = {"rows": len(rows), "bytes": unique_bytes([(r[0], r[0] + r[1]) for r in rows]),
              "ambiguous_rows": sum(1 for f in flags_of if AMBIGUOUS in f),
              "scope_unknown_rows": sum(1 for f in flags_of if SCOPE_UNKNOWN in f),
              "unmapped_rows": sum(1 for f in flags_of if UNMAPPED in f), "disambiguated": settled}
    return hits, rows, back_of, flags_of, other_of, unmapped, ambiguous, totals


def datum_starts(body, target, relocs, size):
    """[(symbol, retail datum start)] per DIR32 reference inside a row's first `size`
    bytes: the retail dword less the object's in-place addend, so a reference to
    symbol+4 names the datum at symbol (tools/data_ledger.py's derivation)."""
    out = []
    for offset, kind, symbol in relocs:
        if kind != DIR32 or offset + 4 > min(size, len(body), len(target)):
            continue
        out.append((symbol, (struct.unpack_from("<I", target, offset)[0] - struct.unpack_from("<I", body, offset)[0]
                             - IMAGE_BASE) & 0xFFFFFFFF))
    return out


def object_references(functions, objects):
    """references_of(rec) for refs_from_status: datum_starts of a link_status row's
    body in its compiled object under `objects` (its functions.csv row gives the
    object symbol and a .lib member) against retail's bytes; None when the row,
    object or symbol is unavailable."""
    sys.path.insert(0, str(ROOT / "tools"))
    import build  # noqa: E402  (retail game.dat, COFF reader)
    ledger_rows = {}
    with open_text(functions) as handle:
        for row in csv.DictReader(handle):
            if row.get("status") == "matched" and (row.get("target_rva") or "").startswith("0x"):
                ledger_rows.setdefault((row["name"], int(row["target_rva"], 16)), row)

    def references_of(rec):
        rva, size = int(rec["retail_rva"], 16), int(rec["size"])
        row = ledger_rows.get((rec["name"], rva))
        if row is None:
            return None
        try:
            member = build.ledger_member(row) if row["source"].lower().endswith(".lib") else None
            path = Path(objects) / object_name(row["source"], member)
            body, relocs = build.read_object_symbol_bytes(path, build.ledger_object_symbol(row), size)
            target = build.read_target_bytes(rva, size)
        except (OSError, ValueError, SystemExit):
            return None
        if len(body) < size or len(target) < size:
            return None  # partial evidence never settles a symbol: keep it quarantined
        return datum_starts(body, target, relocs, size)
    return references_of


def text_relocations():
    """[(site, target rva)] of retail's base relocations in .text, by site (lost
    pages recovered, tools/boot_image.py)."""
    sys.path.insert(0, str(ROOT / "tools"))
    import boot_image  # noqa: E402  (capstone, pefile, retail game.dat)
    retail = boot_image.Retail()
    sites, _info = boot_image.all_sites(retail)
    tstart, tsize, _raw = retail.secs[".text"]
    return [(site, retail.u32(site) - IMAGE_BASE) for site in sites if tstart <= site < tstart + tsize]


def refs_from_relocs(ledger, rows, candidates):
    """{address: {row index}} from retail's base relocations in .text."""
    return attribute(ledger, rows, candidates, text_relocations())


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


def interval_index(rows):
    """(bounds, covers): every row start and end, sorted, and per elementary span
    [bounds[k], bounds[k + 1]) the indices of the rows holding it, however deeply
    rows nest or overlap."""
    opens, closes = collections.defaultdict(list), collections.defaultdict(list)
    for i, (start, size, *_rest) in enumerate(rows):
        if size > 0:
            opens[start].append(i)
            closes[start + size].append(i)
    bounds = sorted(set(opens) | set(closes))
    covers, live = [], set()
    for b in bounds:
        live.difference_update(closes.get(b, ()))
        live.update(opens.get(b, ()))
        covers.append(frozenset(live))
    return bounds, covers


def containing(index, at):
    """Indices of the rows whose [start, start + size) holds `at`."""
    bounds, covers = index
    k = bisect.bisect_right(bounds, at) - 1
    return covers[k] if k >= 0 else frozenset()


def attribute(ledger, rows, candidates, pairs):
    """{address: {row index}} for (site, target rva) pairs: a target owned by a
    candidate address, a site inside a row."""
    bases = sorted(ledger)
    index = interval_index(rows)
    out = collections.defaultdict(set)
    for site, target in pairs:
        address = owner(ledger, bases, candidates, target)
        held = containing(index, site) if address is not None else ()
        if held:
            out[address].update(held)
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
    for ref, defined, comdat, _static in (objsyms or {}).values():
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
                 "scope": "unknown" if symbol in row["unknown"] else "static" if source else "global",
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
              f"({report['status']}); {t['ambiguous_rows']:,} rows with an ambiguous symbol, "
              f"{t['scope_unknown_rows']:,} with one of unknown scope, {t['unmapped_rows']:,} with an unmapped one"
              + (f"; {t['disambiguated']:,} symbols settled by their references" if report.get("disambiguate")
                 else ""), file=out)
    if report.get("objects") is None:
        print("files: no objects read (--objects DIR)", file=out)
    if report["mode"] == "status" and report.get("scope_unknown"):
        print(f"scope: {report['scope_unknown']:,} single-name bindings of unknown scope (no owner object), "
              f"matched only for their owner's rows", file=out)
    fold = report.get("data_fold") or {}
    for name, part in ((k, v) for k, v in fold.items() if isinstance(v, dict)):
        line = (f"data-fold-1 {name}: {part['addresses']} addresses ({fold['source']}), "
                f"{len(part['ranked'])} ranked here")
        if "clear_rows" in part:
            line += (f"; {part['rows']:,} rows {part['bytes']:,} bytes fail data-back there, "
                     f"{part['clear_rows']:,} rows {part['clear_bytes']:,} bytes nowhere else")
        print(line, file=out)
    if "icf_candidates" in fold:
        print(f"data-fold-1: {fold['icf_candidates']} ICF candidates (no export proof: counted, never excused)",
              file=out)
    print(f"{'#':>3} {'address':10} {'sec':6} {'kind':7} {'names':>5} {'defs':>4} {'refs':>5} {'rows':>5} "
          f"{'bytes':>9} {'sole':>8} {'inv':>3} {'var':>3} {'fold':6} canonical [other blockers]", file=out)
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
        label = (a.get("fold") or {}).get("label", "")
        print(f"{n:>3} {a['address']:10} {a['section']:6} {a['kind']:7} {len(a['names']):>5} {a['defs']:>4} "
              f"{a['refs']:>5} {a['rows']:>5} {a['bytes']:>9,} {sole} {inv:>3} {var:>3} {label:6} {tail}", file=out)
    for a in (a for a in report["addresses"] if a.get("detail")):
        sole = f", sole {a['sole_rows']} rows {a['sole_bytes']:,} bytes" if "sole_bytes" in a else ""
        print(f"\n{a['address']} {a['section']} {a['kind']} ({a['status']}) defs {a['defs']} refs {a['refs']}: "
              f"{a['rows']} rows {a['bytes']:,} bytes{sole}", file=out)
        print(f"  {'files':>5} {'defs':>4} {'rows':>5} {'bytes':>9}  {'flags':18} name", file=out)
        for x in sorted(a["names"], key=lambda x: (-x["bytes"], -(x["files"] or 0), x["symbol"])):
            flags = " ".join(f for f in ("inv" if x["invented"] else "", x["variant"] and "var:" + x["variant"],
                                         {"static": "static", "unknown": "scope?"}.get(x["scope"], "")) if f)
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
        fold = a.get("fold") or {}
        if fold.get("export_names") or fold.get("rule"):
            print(f"  data-fold-1: {fold['export_names']} export names; "
                  + (f"{fold['rule'] or 'not excused'} ({fold['verdict']})" if fold.get("verdict")
                     else "export-proven, linked datums unverified (--folds)"), file=out)
    if report.get("ambiguous"):
        print(f"\nquarantined data-back symbols, counted at no address ({len(report['ambiguous'])}; "
              f"--disambiguate tries each row's own references):", file=out)
        print(f"  {'rows':>5} {'bytes':>9}  {'reason':17} symbol: candidates", file=out)
        for x in report["ambiguous"][:top]:
            more = len(x["candidates"]) - 6
            print(f"  {x['rows']:>5} {x['bytes']:>9,}  {x['reason']:17} {short(x['symbol'], 60)}: "
                  + " ".join(x["candidates"][:6]) + (f" (+{more})" if more > 0 else ""), file=out)
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
        sources |= {row["source"] for row in ledger.values() if row["source"]}
        objsyms = object_symbols(args.objects, sources, wanted, None if args.no_cache else args.cache)
    scope_bindings(ledger, objsyms)
    usage = name_usage(objsyms) if objsyms is not None else (None, None)
    entries = []
    if args.status:
        references_of = object_references(args.functions, args.objects) if args.disambiguate else None
        hits, rows, back_of, flags_of, other_of, unmapped, ambiguous, totals = refs_from_status(
            args.status, ledger, args.kind, references_of)
        for address, hit in hits.items():
            ids = hit["rows"]
            other = collections.Counter()
            for i in ids:
                other.update(other_of[i])
                if back_of[i] - {address}:
                    other["data-back elsewhere"] += 1
                other.update("data-back " + f for f in flags_of[i])
            sole = {i for i in ids if back_of[i] == {address} and not row_unresolved(flags_of[i]) and not other_of[i]}
            entries.append(describe(address, ledger[address], rows, ids, hit["names"], usage, other, sole))
        quarantined = [{"symbol": symbol, "reason": reason, "candidates": [f"0x{a:08X}" for a in candidates],
                        "rows": len(ids), "bytes": span_bytes(rows, ids)}
                       for (symbol, reason, candidates), ids in ambiguous.items()]
        quarantined.sort(key=lambda x: (-x["bytes"], -x["rows"], x["symbol"], x["candidates"]))
        report = {"mode": "status", "status": str(args.status), "kind": args.kind, "totals": totals,
                  "disambiguate": bool(args.disambiguate), "ambiguous": quarantined,
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
    export_folds = load_export_folds(args.exports)
    fold_list = load_fold_list(args.folds) if args.folds else None
    for e in entries:
        e["fold"] = fold_of(int(e["address"], 16), export_folds, fold_list)
    per_row = {"rows": rows, "back_of": back_of, "other_of": other_of, "flags_of": flags_of} if args.status else {}
    report["data_fold"] = fold_report(entries, export_folds, fold_list, **per_row)
    if want:
        entries = [e for e in entries if int(e["address"], 16) in want]
    for n, e in enumerate(entries):
        e["detail"] = bool(want) or n < args.detail
        if e["detail"] and objsyms is not None:     # the sources behind each name
            for x in e["names"]:
                x["sources"] = [x["local_source"]] if x["local_source"] else sorted(
                    src for src, parts in objsyms.items() if any(x["symbol"] in part for part in parts))
    report["objects"] = None if objsyms is None else {"dir": str(args.objects), "sources": len(objsyms)}
    report["scope_unknown"] = sum(len(row["unknown"]) for row in ledger.values())
    report["addresses"] = entries
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--status", help="link_cycle link_status.csv (plain or .gz); omit for the PROVISIONAL ranking")
    ap.add_argument("--disambiguate", action="store_true",
                    help="with --status: count an ambiguous symbol at a candidate address when every reference "
                         "to it in the row's compiled object (retail target less addend) names that one address")
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
    ap.add_argument("--exports", default=str(EXPORTS), help="retail's export table (export-proven folds)")
    ap.add_argument("--folds", help="link_cycle's data_fold_list.csv: data-fold-1's measured verdicts")
    ap.add_argument("--objects", default=str(OBJECTS), help="compiled objects, tools/build.py naming")
    ap.add_argument("--no-objects", action="store_true",
                    help="skip the object scan: no per-name file counts, and every single-name `owned` binding "
                         "is of unknown scope")
    ap.add_argument("--cache", default=str(CACHE))
    ap.add_argument("--no-cache", action="store_true")
    args = ap.parse_args(argv)
    if args.disambiguate and (not args.status or args.no_objects):
        ap.error("--disambiguate needs --status and reads the rows' objects (not with --no-objects)")
    report = build_report(args)
    render(report, len(report["addresses"]) if args.address else args.top, args.list_files)
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())


