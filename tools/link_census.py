#!/usr/bin/env python3
"""Link every matched object into one image and count what stops it.

Every other gate verifies one function at a time. Nothing had ever linked the
tree, so nobody knew how far "the functions match" is from "the game builds".
This links the object of every matched ledger row (compiled TUs, MASM dumps,
generated C++, prebuilt-library members) and of every matched data row
(data_rows.csv: a data-only TU's globals resolve references like any other
definition), in retail's link order (link_order), with MSVC 7.1's own link.exe under
/FORCE, so it reports every problem instead of stopping at the first, and sorts
them into the classes the integration work has to clear:

  unresolved   a referenced name nothing defines
    data         a global the code reaches by a pinned address
                 (dir32_addresses.csv): needs a definition
    import       __imp__ DLL entry: needs the import libraries
    alias        a pinned call name whose address is matched under another
                 name: collapse onto the defining name
    dump         a pinned call name whose address is still a dump: the dump
                 defines ?d_XXXXXXXX, so it needs the real name
    unpinned     referenced but pinned nowhere (runtime, shims, typos)
    vtable/rtti  ??_7 / ??_R: a class's vftable or type info
  duplicate    a name defined by two objects (private class copies, shims,
               double conversions)

  python3 tools/link_census.py            # link, write build/link_census/census.json
  python3 tools/link_census.py --build --history   # compile what changed first (all cores), then census
  python3 tools/link_census.py --report   # summarise the last census
  python3 tools/link_census.py --status   # redo link_status.csv + LINKED from the last log
  python3 tools/link_census.py --selected # which COMDAT copy the link selected (/MAP), vs retail truth
  python3 tools/link_census.py --build --history --dry   # the whole census, recording nothing (DRY_OUT)

`--history` records the census in link_census_history.csv, with LINKED
(linked_bytes) measured on this tree, and writes
reverse/link_status.csv: one row per C/C++
source, `linked=yes` when, in the plain link (no alias scaffold), its object
has no unresolved reference beyond imports and msvcrt.lib, no duplicate, and
no COMDAT copy that differs from retail's body while no other object supplies
retail's (comdat_losers), no name it
defines or references resolves in the link to a kept definition proven not
retail's (wrong_selected; the /MAP of a second link says which it kept), and
the file holds no hard-coded image address. LINKED is progress.py's DECOMPILED restricted to
those sources; progress.py and the README print the last census's figure. A
data-only source has a status row but no code, so it adds 0 LINKED bytes
itself: its definitions only unblock the files that reference them.

These are Open-BFME-1's rules (its tools/link_census.py), ported function for
function so the two projects measure LINKING the same way; only paths and the
retail-truth inputs this repository lacks differ (no dir32_addresses.csv, no
route= pins: see _dir32_rows and validated_import_routes). Data rows
(data_rows.csv, tools/data_rows.py) are read as Open-BFME-1 reads them, and
must pass its byte gate before their objects are used (verify_data_objects).
Before the port this census kept the COMDAT copy most objects
compiled, exempted STLport and the array helpers, linked in ledger row order
and had no wrong_selected: link_census_history.csv names the rules every row
was measured under (`rules`, `prev_rules`; see HISTORY_FIELDS), and
tools/census_rebaseline.py records the one row where they change.

An object counts only when it is proven current, as Open-BFME-1 proves it:
a census-grade compile receipt (build.compile_is_current(strict=True): the
source, compile command, every included header and the listing of every
include search directory unchanged) or, for a TU whose sidecar cannot carry
that, this run's own witnessed compile (census_receipts.py). The objects, the
compiler inputs and these tools must then hold still from the first check
to the record (census_state); otherwise nothing is recorded.

The census is diagnostic. The image it writes is not expected to run.
"""
import argparse
import collections
import concurrent.futures
import csv
import hashlib
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402


_PROFILE = False  # main() turns the stage profile on; a tool importing this module stays quiet


def _stage_line(name, seconds):
    """`link_census: <stage> <seconds>s` on stderr: the census's stage profile
    (the runner's log keeps it; nothing parses it)."""
    if not _PROFILE:
        return
    print(f"link_census: {name} {seconds:.1f}s", file=sys.stderr, flush=True)


def _timed(name):
    """Report each call's wall time under `name` (_stage_line)."""
    import functools

    def wrap(fn):
        @functools.wraps(fn)
        def run(*args, **kwargs):
            started = time.monotonic()
            try:
                return fn(*args, **kwargs)
            finally:
                _stage_line(name, time.monotonic() - started)
        return run
    return wrap

OUT = ROOT / "build" / "link_census"
# The linker prints `"<demangled>" (<mangled>)` for a C++ name and the bare name for a C one.
UNRESOLVED = re.compile(r'error LNK20(?:01|19): unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))')
DUPLICATE = re.compile(r'^(\S+\.obj) : (?:error LNK2005|warning LNK4006): (?:"[^"]*" \((\S+)\)|(\S+)) '
                       r'already defined in (\S+\.obj)')
FATAL = re.compile(r"fatal error (LNK(?!1120)\d+).*")  # LNK1120 is only the unresolved count
REFERRER = re.compile(r"^(\S+\.obj) : error LNK20(?:01|19)")
# These are compiler inputs, including the headers reached through TU shims
# (reference/ holds the shims and the open-bfme-1 submodule the toolchain and
# BFME 1 headers come from).
CENSUS_INPUTS = ("Code", "reference", "vendor", "reverse/functions.csv", "reverse/symbols.csv",
                 "reverse/dir32_addresses.csv", "reverse/data_rows.csv")
# The census's own code: a checkout updated under a running census would
# judge the rest of the run with other rules (census_state).
TOOL_FILES = ("link_census.py", "link_check.py", "build.py", "census_receipts.py", "progress.py", "link_debt.py",
              "data_rows.py", "reloc_ledger.py")


def ledger():
    with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r.get("status") == "matched"
                and (r.get("target_rva") or "").startswith("0x")]


def data_sources():
    """Sources owned by byte-verified data rows; these are not function rows."""
    import data_rows
    return list(dict.fromkeys(ROOT / row["source"] for row in data_rows.load()))


def compile_sources(rows):
    return list(dict.fromkeys([ROOT / row["source"] for row in rows] + data_sources()))


@_timed('data verification')
def verify_data_objects():
    """Require the existing data byte gate before using these providers."""
    import data_rows
    problems = []
    if data_rows.DATA_ROWS.exists():
        data_rows.check(data_rows.DATA_ROWS.read_bytes(), problems)
    if problems:
        raise SystemExit("link_census: invalid data rows:\n  " + "\n  ".join(problems))
    stale = [source for source in data_sources()
             if not object_current(source, build.obj_path(source))]
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} data provider objects are missing or stale, "
                         f"e.g. {stale[0].relative_to(ROOT)}; rerun with --build")
    data_rows.verify(compile=False)


def data_ledger():
    """The matched rows of data_rows.csv: globals a Code/ source defines,
    byte-verified at their retail address by the gate (tools/data_rows.py)."""
    import data_rows
    return [row for row in data_rows.load() if row.get("status") == "matched"]


def data_rva(row):
    import data_rows
    return data_rows.va_of(row) - BASE


def data_object(row):
    return build.obj_path(ROOT / row["source"])


def _dir32_rows():
    """reverse/dir32_addresses.csv's rows ({name, va}); this repository has no
    such ledger yet, so every unresolved global is reported as unpinned rather
    than as data (a label only), and retail truth has no data address for a
    name no pin places."""
    path = ROOT / "reverse/dir32_addresses.csv"
    if not path.exists():
        return []
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def pins(routes=None):
    """{name: address} from symbols.csv (first pin for diagnostic identity).
    The byte resolver checks additive candidates. `routes`, when given,
    collects {name: target} from `route=0x...` notes."""
    found = {}
    with (ROOT / "reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.reader(handle):
            if len(row) >= 2 and row[1].startswith("0x"):
                found.setdefault(row[0], int(row[1], 16))
                route = re.search(r"route=(0x[0-9A-Fa-f]+)", ",".join(row[2:]))
                if routes is not None and route:
                    routes.setdefault(row[0], int(route.group(1), 16))
    return found


ROUTE_NOTE = re.compile(r"(?:^|;)\s*route=([^;]+)")


def route_claims():
    """{(name, address): claim} for symbols.csv rows whose notes carry a
    `route=` claim (Open-BFME-1's pin_consistency.load_routes)."""
    routes = {}
    with (ROOT / "reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            found = ROUTE_NOTE.search(row.get("notes") or "")
            if found:
                routes[(row["name"], int(row["address"], 16))] = found.group(1).strip()
    return routes


def validated_import_routes(routes=None, scanner=None):
    """Additional REL32 targets that are proven retail import thunks.

    A second symbols.csv pin is not identity evidence. Only an explicit
    `route=` claim re-derived by pin_consistency, at a matched FF 25 import
    thunk, may supplement the first pin when checking a call relocation.
    These addresses never become function-body homes or DIR32 targets.

    Open-BFME-1 re-derives each claim with pin_consistency.route_verdict.
    This repository's pin_consistency has no route verdict and symbols.csv
    carries no route= claim, so there is nothing to add; a claim appearing
    refuses the census (fail closed) until route_verdict is ported, because an
    unverified route would let a pin decide where a call lands.
    """
    routes = route_claims() if routes is None else routes
    if not routes:
        return {}
    raise SystemExit(f"link_census: symbols.csv carries {len(routes):,} route= claim(s) (e.g. "
                     f"{next(iter(routes))[0]}) and this repository cannot verify them yet: port "
                     "Open-BFME-1's pin_consistency.route_verdict before using them as retail truth")


BASE = 0x400000


def _thunk_target(notes):
    """RVA an ILT jump-stub row forwards to (`target=0x...` RVA or `target=FUN_<va>`)."""
    found = re.search(r"target=(?:0x([0-9A-Fa-f]+)|FUN_([0-9A-Fa-f]+))", notes or "")
    if not found:
        return None
    return int(found.group(1), 16) if found.group(1) else int(found.group(2), 16) - BASE


def alias_scaffold(rows, wanted):
    """{called name: defining name} for names the census found unresolved.

    Every byte-matched call already lands on retail's address, so pointing the
    name it spells at the symbol DEFINED at that address reproduces what the
    retail image does. This is a link scaffold, like a dump: the source still
    calls the alias, and each one a header lane fixes leaves this table. An
    address is followed through its ILT jump stub (route= pin note, or the stub
    row's target=). One definition per address is chosen deterministically:
    authored Code/ C++ first, then by name. Addresses with no defining row are
    left unresolved (the census still reports them).
    """
    routes = {}
    pinned = pins(routes)
    by_address = collections.defaultdict(list)
    stubs = {}
    for row in rows:
        address = int(row["target_rva"], 16)
        if row["name"].startswith("?j_"):
            target = _thunk_target(row.get("notes"))
            if target is not None:
                stubs.setdefault(address, target)
        else:
            by_address[address].append(row)

    defined = {}

    def object_name(row):
        """The symbol the row's object really defines for it: the notes'
        object-symbol= alias, else the ledger name, else the one defined
        symbol equal to it up to the per-machine anonymous-namespace hash."""
        obj = build.row_object(row)
        if obj not in defined:
            try:
                defined[obj] = {s["name"] for s in build.read_object_symbols(obj.read_bytes()) if s["section"] > 0}
            except OSError:
                defined[obj] = set()
        wanted_name = build.ledger_object_symbol(row)
        if wanted_name in defined[obj]:
            return wanted_name
        normal = re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", wanted_name)
        found = [n for n in defined[obj] if re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", n) == normal]
        return found[0] if len(found) == 1 else None

    def defining(address, depth=0):
        owners = by_address.get(address)
        if owners:
            ranked = sorted(owners, key=lambda r: (not (r["source"].startswith("Code/") and not r["source"].startswith(
                ("Code/gen_small/", "Code/gen_asm/"))), r["name"]))
            for row in ranked:
                name = object_name(row)
                if name:
                    return name
            return None
        if depth < 2 and address in stubs:
            return defining(stubs[address], depth + 1)
        return None

    table = {}
    for name in wanted:
        address = routes.get(name, pinned.get(name))
        if address is None:
            continue
        target = defining(address)
        if target and target != name:
            table[name] = target
    # A defining name can itself be unresolved and aliased (2 such chains on
    # 2026-09-28): point every alias straight at the end of its chain.
    for name in list(table):
        seen, target = {name}, table[name]
        while target in table and target not in seen:
            seen.add(target)
            target = table[target]
        table[name] = target
    return {name: target for name, target in table.items() if name != target}


def data_names():
    return {row["name"] for row in _dir32_rows()}


def code_places(rows, object_of=None):
    """{object: the retail RVA that places it in link order}, from matched
    functions.csv rows.

    Retail's .text follows its link order and each object's code is
    contiguous there, so an object goes where its own code sits: the lowest
    retail RVA among its rows whose address no other object's row also claims.
    An address several objects claim is an ICF alias (link.exe folded
    identical bodies into one, in whichever object it kept; the ledger marks
    some with fold-proof=, gen-alias or icf-owner=, most only in free text)
    or an over-claim; either way it does not say which object retail placed
    there, and a folded row can sit megabytes before its object's own code
    (0x00001E13 placed Render2DSentenceDrawBFME2.cpp, whose code is at
    0x001540B0, at the front of the link: LINK-133). Such rows are skipped;
    the object that does own the address loses nothing, its other rows lie in
    the same contiguous block. An object every row of which is shared keeps
    the lowest of them (retail-truth-4's rule for every object). `object_of`
    (default build.row_object) maps a row to its object."""
    object_of = object_of or build.row_object
    objects, claims, placed = {}, collections.defaultdict(set), []
    for row in rows:
        source = row["source"]
        obj = objects.get(source)
        if obj is None:
            obj = object_of(row)
            if not source.lower().endswith(build.LIB_SUFFIX):  # a lib's rows name different members
                objects[source] = obj
        rva = int(row["target_rva"], 16)
        claims[rva].add(obj)
        placed.append((obj, rva))
    own, lowest = {}, {}
    for obj, rva in placed:
        lowest[obj] = min(lowest.get(obj, rva), rva)
        if len(claims[rva]) == 1:
            own[obj] = min(own.get(obj, rva), rva)
    return {obj: own.get(obj, rva) for obj, rva in lowest.items()}


def link_order(rows, data=()):
    """Every object of a matched ledger row or a matched data row, in link order.

    Code objects go by code_places (the lowest retail RVA of their own,
    unshared rows). Objects that own only data rows (a data-only TU) follow,
    by the lowest retail RVA of their data. Ties, which only an over-claimed
    address can produce, go by object path. Neither the ledger's row order nor
    a file's name decides a place (before 2026-09-30 the first row naming an
    object did, and functions.csv is not sorted by RVA)."""
    code, data_only = code_places(rows), {}
    for row in data:
        obj = data_object(row)
        if obj not in code:
            data_only[obj] = min(data_only.get(obj, data_rva(row)), data_rva(row))
    key = {obj: (0, rva, obj.as_posix()) for obj, rva in code.items()}
    key.update({obj: (1, rva, obj.as_posix()) for obj, rva in data_only.items()})
    return sorted(key, key=key.__getitem__)


def objects(rows, data=None):
    """Unique object per matched row and per matched data row, in link_order;
    (present, missing). `data` defaults to data_ledger()."""
    build.extract_lib_members([r for r in rows if r["source"].lower().endswith(build.LIB_SUFFIX)])
    present, missing = [], []
    for obj in link_order(rows, data_ledger() if data is None else data):
        (present if obj.exists() else missing).append(obj)
    return present, missing


def alias_object(table, path):
    """Write a COFF object holding one weak external per alias.

    /ALTERNATENAME for all 71,090 aliases crashed link.exe 7.1 (LNK1000) while
    20,000 linked; a weak external with IMAGE_WEAK_EXTERN_SEARCH_ALIAS, the
    record MASM's ALIAS directive emits, is the ordinary object-file way to say
    "if nothing defines this name, use that one".
    """
    import struct
    targets = sorted(set(table.values()))
    strings = bytearray(b"\0\0\0\0")

    def name_field(text):
        raw = text.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, offset)

    symbols = bytearray()
    index = {}
    for target in targets:
        index[target] = len(symbols) // 18
        symbols += name_field(target) + struct.pack("<IhHBB", 0, 0, 0x20, 2, 0)  # UNDEF external
    for alias, target in sorted(table.items()):
        symbols += name_field(alias) + struct.pack("<IhHBB", 0, 0, 0, 105, 1)  # WEAK_EXTERNAL
        symbols += struct.pack("<II", index[target], 3) + b"\0" * 10          # SEARCH_ALIAS
    count = len(symbols) // 18
    strings[0:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, count, 0, 0)
    path.write_bytes(header + bytes(symbols) + bytes(strings))
    return path


def stub_object(names, path):
    """Write a COFF object defining each name at offset 0 of one 16-byte
    section. It only lets link.exe finish: the census's ~95,000 unresolved
    names are fatal (LNK1120, even under /FORCE) and a failed link writes an
    empty /MAP; absolute symbols instead crash link.exe 7.1 (C0000005)."""
    import struct
    strings, symbols = bytearray(4), bytearray()
    for name in sorted(names):
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, bytes(1))
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + bytes(1))
        symbols += field + struct.pack("<IhHBB", 0, 1, 0, EXTERNAL, 0)
    strings[0:4] = struct.pack("<I", len(strings))
    body = bytes([0xCC]) * 16
    table = 20 + 40 + len(body)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, len(symbols) // 18, 0, 0)
    section = b".text".ljust(8, bytes(1)) + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60500020)
    path.write_bytes(header + section + body + bytes(symbols) + bytes(strings))
    return path


def _arg(path):
    """A repo-relative, forward-slash path, as build.py passes cl.exe: under Wine
    an absolute POSIX path (/home/...) would read as a link.exe option."""
    return Path(path).resolve().relative_to(ROOT.resolve()).as_posix()


def _rsp_text(objs):
    return "\n".join(f'"{_arg(o)}"' for o in objs) + "\n"


def link(objs, aliases=None, tag="census", extra=(), options=()):
    OUT.mkdir(parents=True, exist_ok=True)
    rsp = OUT / f"{tag}.rsp"  # per tag: the census and selection links may run at once
    rsp.write_text(_rsp_text(objs), encoding="utf-8")
    extra = [_arg(path) for path in extra] + list(options)
    if aliases:
        extra.append(_arg(alias_object(aliases, OUT / "aliases.obj")))
    root = build.vc71_root()
    linker = root / "Vc7" / "bin" / "link.exe"
    command = [str(linker), "/NOLOGO", "/FORCE", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
               "/SUBSYSTEM:WINDOWS", "/ENTRY:WinMainCRTStartup", f"/OUT:{_arg(OUT / (tag + '.exe'))}", f"@{_arg(rsp)}", *extra]
    if sys.platform != "win32":
        command.insert(0, "wine")
    started = time.time()
    # LNK1104 on the output (a scanner holding the new .exe) failed one run on
    # 2026-09-29 and linked on the next try: retry that one error, nothing else.
    for attempt in range(3):
        result = subprocess.run(command, capture_output=True, text=True, errors="replace",
                                env=build.compiler_environment(root), cwd=ROOT)
        if f"LNK1104: cannot open file '{_arg(OUT / (tag + '.exe'))}'" not in result.stdout + result.stderr:
            break
        if attempt < 2:
            time.sleep(10)
    (OUT / f"{tag}.log").write_text(result.stdout + result.stderr, encoding="utf-8")
    return result.stdout + result.stderr, time.time() - started, result.returncode


def fresh_outputs(*paths):
    """Delete a link's outputs before it runs, so any that exist afterwards
    were written by this invocation (a timestamp window cannot prove that)."""
    for path in paths:
        try:
            path.unlink()
        except FileNotFoundError:
            pass
        except OSError as exc:
            raise SystemExit(f"link_census: cannot remove the previous {path.name} ({exc}); a stale output "
                             "would read as this link's")


def unexplained_exit(code, log, output=None):
    """Refuse a link that did not complete: a termination by exception or
    signal (an NTSTATUS such as 0xC0000005, a negative code) whatever the log
    says before it; a failing exit the linker's own diagnostics do not
    explain (under /FORCE, the LNK errors and warnings the census counts);
    and, given `output` (removed by fresh_outputs before the link), no PE
    image written there by this run. Nothing is ever recorded as a census
    with nothing wrong."""
    if code < 0 or code > 0xFFFF:
        raise SystemExit(f"link_census: link.exe terminated abnormally (exit 0x{code & 0xFFFFFFFF:08X}); "
                         "no counts recorded")
    if code and not re.search(r"\b(?:error|warning) LNK\d+", log):
        raise SystemExit(f"link_census: link.exe exited {code} with no linker diagnostic; no counts recorded")
    if output is not None:
        why = pe_defect(output)
        if why:
            raise SystemExit(f"link_census: link.exe exited {code} but wrote no image at {output.name} ({why}); "
                             "no counts recorded")


def pe_defect(path):
    """Why `path` is not a complete PE image, or None: DOS header and
    e_lfanew, the PE signature, an i386 COFF header, a PE32 optional header
    whose size covers its fixed fields and every data directory it
    declares, SizeOfHeaders inside the file and covering all headers and
    the section table, and every section's raw data inside the file and
    after the headers."""
    import struct
    try:
        data = path.read_bytes()
    except OSError as exc:
        return f"unreadable: {exc}"
    if len(data) < 0x40 or data[:2] != b"MZ":
        return "no DOS header"
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if pe + 24 > len(data) or data[pe:pe + 4] != b"PE\0\0":
        return "no PE signature at e_lfanew"
    machine, sections, _, _, _, optional, _ = struct.unpack_from("<HHIIIHH", data, pe + 4)
    if machine != 0x14C or not sections:
        return f"COFF header: machine 0x{machine:X}, {sections} sections"
    table = pe + 24 + optional
    if optional < 96 or table + 40 * sections > len(data) or struct.unpack_from("<H", data, pe + 24)[0] != 0x10B:
        return "optional header or section table does not fit"
    directories = struct.unpack_from("<I", data, pe + 24 + 92)[0]
    if 96 + 8 * directories > optional:
        return f"the optional header declares {directories} data directories but holds {(optional - 96) // 8}"
    headers = struct.unpack_from("<I", data, pe + 24 + 60)[0]
    if headers > len(data) or headers < table + 40 * sections:
        return f"SizeOfHeaders 0x{headers:X} does not cover the headers and section table inside the file"
    for index in range(sections):
        size, pointer = struct.unpack_from("<II", data, table + 40 * index + 16)
        if size and pointer + size > len(data):
            return f"section {index + 1}'s raw data runs past the end of the file"
        if size and pointer < headers:
            return f"section {index + 1}'s raw data overlaps the headers"
    return None


@_timed('classify')
def classify(log, rows):
    pinned = pins()
    data = data_names()
    naked = naked_rows()
    by_address = collections.defaultdict(list)
    for row in rows:
        by_address[int(row["target_rva"], 16)].append(row)
    unresolved = {}
    duplicates = collections.defaultdict(set)
    for line in log.splitlines():
        found = UNRESOLVED.search(line)
        if found:
            symbol = found.group(1) or found.group(2)
            referrer = REFERRER.match(line)
            entry = unresolved.setdefault(symbol, {"refs": set()})
            if referrer:
                entry["refs"].add(Path(referrer.group(1)).name)
            continue
        found = DUPLICATE.match(line)
        if found:
            duplicates[found.group(2) or found.group(3)].update({Path(found.group(1)).name, Path(found.group(4)).name})
    classes = collections.Counter()
    detail = {}
    for symbol, entry in unresolved.items():
        address = pinned.get(symbol)
        if symbol.startswith("__imp_"):
            kind = "import"
        elif symbol.startswith(("??_7", "??_R")):
            kind = "vtable/rtti"
        elif symbol in data:
            kind = "data"
        elif address is not None:
            owners = [r for r in by_address.get(address, []) if not r["name"].startswith("?j_")]
            if owners and any(not build_dump(r, naked) for r in owners):
                kind = "alias"
                entry["defined_as"] = sorted(r["name"] for r in owners if not build_dump(r, naked))[:3]
            elif owners:
                kind = "dump"
            else:
                kind = "pinned-elsewhere"
            entry["address"] = f"0x{address:08X}"
        else:
            kind = "unpinned"
        classes[kind] += 1
        entry["kind"] = kind
        entry["refs"] = sorted(entry["refs"])[:5]
        detail[symbol] = entry
    dup_kinds = collections.Counter()
    for symbol in duplicates:
        dup_kinds["vtable/rtti" if symbol.startswith(("??_7", "??_R")) else
                  "data" if symbol in data else "function/other"] += 1
    return classes, detail, dup_kinds, {s: sorted(o)[:6] for s, o in duplicates.items()}


COMDAT = 0x1000  # IMAGE_SCN_LNK_COMDAT
EXTERNAL = 2      # IMAGE_SYM_CLASS_EXTERNAL
STATIC = 3        # IMAGE_SYM_CLASS_STATIC
WEAK_EXTERNAL = 105  # IMAGE_SYM_CLASS_WEAK_EXTERNAL: a vftable slot's ??_E deleting destructor


def _coff_symbols(data):
    """[{index, name, section, storage, value}] for every symbol record, by raw
    index (aux records occupy indices too, which relocations count)."""
    import struct
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    out, index = [], 0
    while index < count:
        record = data[table + 18 * index:table + 18 * index + 18]
        if record[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", record, 4)[0]
            name = data[strings + offset:data.index(b"\0", strings + offset)]
        else:
            name = record[:8].rstrip(b"\0")
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", record, 8)
        out.append({"index": index, "name": name.decode("latin-1"), "section": section, "storage": storage,
                    "value": value})
        index += 1 + aux
    return out


def _comdat_sections(data):
    """(symbol, body, relocs, digest, size) for each external COMDAT symbol
    in one COFF object. `body` is the section's raw bytes (None when
    uninitialized); `relocs` is [(offset, type, referent symbol)], a
    content-named referent (RetailTruth.CONSTANT) carrying its bytes.

    The digest covers the section's bytes AND its relocations (offset, type,
    target, weak externals included): two vftables with identical bytes whose
    slots point at different functions are different copies. A TU-local target
    (a string literal, a static) is named per TU, so it counts only as "local";
    an anonymous namespace's per-TU hash is normalised. An uninitialized section
    has no bytes to hash, only a size.
    """
    import hashlib
    import struct
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    symbols = _coff_symbols(data)
    by_index = {symbol["index"]: symbol for symbol in symbols}
    # A COMDAT digest does not include its referents' definitions. Equal
    # vtables/thunks in different objects can therefore require different
    # recursive proofs. Bind those proofs to the complete immutable object.
    proof_context = hashlib.sha256(data).digest()
    entries = []
    sections = []
    for index in range(count):
        offset = 20 + optional + index * 40
        size, pointer, relocs = struct.unpack_from("<III", data, offset + 16)
        nrelocs = struct.unpack_from("<H", data, offset + 32)[0]
        flags = struct.unpack_from("<I", data, offset + 36)[0]
        sections.append((size, pointer, relocs, nrelocs, flags))
    for symbol in symbols:
        section = symbol["section"]
        # A static mangled COMDAT symbol is no copy of its own, only a
        # definition the external ones (or a weak external's default) reach.
        local = symbol["storage"] == STATIC and symbol["name"].startswith("?")
        if (symbol["storage"] != EXTERNAL and not local) or section <= 0 or section > count:
            continue
        size, pointer, relocs, nrelocs, flags = sections[section - 1]
        if not flags & COMDAT:
            continue
        body = data[pointer:pointer + size] if pointer else None
        digest = hashlib.sha1(body if body is not None else b"uninitialized %d" % size)
        found = []
        for at in range(relocs, relocs + 10 * nrelocs, 10):
            where, target, kind = struct.unpack_from("<IIH", data, at)
            referent = by_index.get(target, {"name": "?", "storage": 0, "section": 0, "value": 0})
            if referent["name"].startswith(RetailTruth.CONSTANT) and 0 < referent["section"] <= count:
                length, start = sections[referent["section"] - 1][:2]
                referent = {**referent, "content": data[start + referent["value"]:start + length] if start else None}
            label = (_normal(referent["name"]) if referent["storage"] in (EXTERNAL, WEAK_EXTERNAL) else "local")
            digest.update(b"%d:%d:" % (where, kind) + label.encode("latin-1") + b";")
            found.append((where, kind, referent))
        symbol["proof_context"] = proof_context
        entries.append((symbol, body, found, digest.hexdigest()[:12], size))
    # An external referent this object defines in a COMDAT of its own (a
    # vftable, its ??_E) carries that definition, so RetailTruth can judge it
    # where retail's slot points when no ledger row gives it an address.
    # A weak external (a vftable slot's ??_E) reaches its default's definition.
    defined = {entry[0]["index"]: entry for entry in entries}
    by_name = {entry[0]["name"]: entry for entry in entries}
    for weak, default in _weak_externals(data):
        if default in by_name:
            defined.update({s["index"]: by_name[default] for s in symbols
                            if s["name"] == weak and s["storage"] == WEAK_EXTERNAL})
    for entry in entries:
        for _, _, referent in entry[2]:
            if (referent["storage"] in (EXTERNAL, WEAK_EXTERNAL, STATIC)
                    and referent["section"] != entry[0]["section"] and referent.get("index") in defined):
                referent["definition"] = defined[referent["index"]]
    yield from (entry for entry in entries if entry[0]["storage"] == EXTERNAL)


def _normal(name):
    """A name with its anonymous namespace's per-TU hash normalised."""
    return re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", name)


def comdat_bodies(obj, data=None):
    """[(name, digest, size)] for each external COMDAT symbol an object defines
    (see _comdat_sections for what the digest covers); `data`, when given, is
    the object's bytes, read by the caller."""
    if data is None:
        try:
            data = obj.read_bytes()
        except OSError:
            return []
    return [(symbol["name"], digest, size) for symbol, _, _, digest, size in _comdat_sections(data)]


class RetailTruth:
    """Is a COMDAT copy the body retail shipped?

    A COMDAT symbol whose ledger row (functions.csv, else a symbols.csv pin)
    gives a retail address is judged against retail itself: its bytes must
    equal retail's at that address outside the relocation fields, and every
    relocation must land where retail's instruction lands. A relocation's
    target NAME is resolved the way an identity is, not the way the byte gate
    resolves a call: a ledger row first (never an icf-owner= over-claim:
    __purecall's row sits on one of many `xor eax,eax; ret` bodies), and a
    symbols.csv pin only for a name with no row (plus its numeric route=), because
    symbols.csv is an ADDITIVE candidate list and a pin on the wrong body
    still byte-matches. That is exactly how
    ??1AsciiString@@QAE@XZ's owner copy passed the gate: retail 0x5EE90 is
    `jmp 0x887940` (releaseBuffer), the owner's copy jumps to
    ??1?$StringBase@D@@AAE@XZ, whose row is 0x5E490, and a pin of that name to
    0x887940 hid the difference. Data names resolve through
    dir32_addresses.csv, __imp_ names to retail's import slot, and a label in
    the copy's own section to the same offset in retail. An incremental-link
    stub (a `jmp` packed between other `jmp`s) stands for its target on either
    side; a padded 5-byte `jmp` is a function that tail-jumps (0x5E490 is
    ~StringBase's own body, not a stub) and is never followed. symbols.csv
    holds VAs and RVAs alike, so a pin at or above the image base is read both
    ways. A TU-local referent (a static, `_$E2`, `$S1`) is named per TU, so it
    has no address to check; a string literal or float constant (`??_C@`,
    `__real@`) is named by its content and retail holds several copies of
    some ("" at least twice), so it is checked by content: retail's bytes at
    the target must be the constant's own. Additional FF 25 import routes
    independently verified by pin_consistency may match REL32 calls, but
    never supply body homes or data-pointer targets.

    An address several ledger names claim (0x5E6F0 for ??8 of eight
    VectorClass instances in Open-BFME-1) proves nothing when it disagrees:
    one body has one identity, so most of those claims are wrong (or folded),
    and the mismatch is the ledger's.

    verdict() returns "retail" (every byte and relocation proven), "wrong"
    (a byte or a resolvable relocation differs from a single-claim address),
    "unknown" (nothing disproves it, but a relocation names something with no
    known address, or only a shared claim disagrees) or None (the symbol
    itself has no retail address: retail truth cannot judge it).
    """

    DIR32, DIR32NB, REL32 = 0x0006, 0x0007, 0x0014
    ABSOLUTE = {"__except_list": 0}  # msvcrt.lib's absolute symbols (fs:[0])
    CONSTANT = ("??_C@", "__real@")  # content-named: retail may hold several copies
    FUNCTION_STATICS = ("__ehhandler$",)  # statics named after their function: one per function

    @staticmethod
    def _rvas(address):
        """symbols.csv mixes RVAs and VAs: 0x0044A061 is VA 0x0044A061 of
        RVA 0x4A061. Both readings are candidates; a pin is only a candidate."""
        return {address, address - BASE} if address >= BASE else {address}

    def __init__(self, rows):
        routes = {}
        pinned = pins(routes)
        self.ledger = collections.defaultdict(set)
        names_at = collections.defaultdict(set)
        for row in rows:
            notes = row.get("notes") or ""
            if "icf-owner=" in notes:
                continue  # a second name on an address: an over-claim to retire, not an identity
            address = int(row["target_rva"], 16)
            names = {row["name"]} if "gen-alias" in notes else {row["name"], build.ledger_object_symbol(row)}
            for name in names:  # a gen-alias twin's object symbol names its original, not the twin
                self.ledger[_normal(name)].add(address)
            names_at[address].add(row["name"])
        # Rowed EH handler thunks (mov eax, FuncInfo; jmp __CxxFrameHandler),
        # whatever function names them: /OPT:ICF folds identical ones.
        self.eh_handlers = {int(row["target_rva"], 16) for row in rows
                            if row["name"].startswith(self.FUNCTION_STATICS) and "icf-owner=" not in (row.get("notes") or "")}
        for row in data_ledger():  # a data row is byte-verified at its address, like a function row
            self.ledger[_normal(row["name"])].add(data_rva(row))
        # An address several names claim is an unresolved over-claim (at most
        # one of them is the body's own identity): a mismatch against it
        # proves nothing about the copy, only about the ledger.
        self.shared = {address for address, names in names_at.items() if len(names) > 1}
        self.pinned = collections.defaultdict(set)
        for name, address in pinned.items():
            self.pinned[_normal(name)] |= self._rvas(address)
        for name, address in routes.items():  # where calls ENCODE the name: an ILT or import stub
            key = _normal(name)
            (self.ledger[key] if key in self.ledger else self.pinned[key]).update(self._rvas(address))
        self.import_routes = validated_import_routes()
        for row in _dir32_rows():  # a data name: pin or dir32 entry, either may be right
            self.pinned[_normal(row["name"])].add(int(row["va"], 16) - BASE)
        self.slots = collections.defaultdict(set)
        for name, address in retail_import_slots():
            self.slots[name].add(address)
        self.image, self.sections = build.exe_image()
        self._cache = {}
        self.import_thunks = self._import_thunks(rows)

    def _import_thunks(self, rows):
        """{imported name: {thunk address}} for ledger gen-import rows whose
        retail bytes are `jmp [slot]` (FF 25) through a slot the retail import
        directory gives that name. Retail can hold several thunks for one
        import (htonl and htons have two each); a call to the import through
        any of them is the import's call. Proven from the image, not the
        row's notes, and used for REL32 only, like import_routes."""
        import struct
        names = {}
        for name, addresses in self.slots.items():
            for address in addresses:
                names.setdefault(address, set()).add(name)
        found = collections.defaultdict(set)
        for row in rows:
            if "gen-import" not in (row.get("notes") or ""):
                continue
            address = int(row["target_rva"], 16)
            stub = self._read(address, 6)
            if stub is None or stub[:2] != b"\xff\x25":
                continue
            for imported in names.get(struct.unpack_from("<I", stub, 2)[0] - BASE, ()):
                found[imported].add(address)
        return found

    def addresses(self, name, kind=None):
        """Retail relocation targets, with proven import routes for REL32 only."""
        key = _normal(name)
        if key in self.ledger:
            return self.ledger[key]
        thunks = getattr(self, "import_thunks", {}).get(_undecorate(name), set()) if kind == self.REL32 else set()
        if kind == self.REL32 and (key in self.import_routes or thunks):
            return set(self.pinned.get(key, ())) | self.import_routes.get(key, set()) | thunks
        if key in self.pinned:
            return self.pinned[key]
        if name.startswith("__imp_"):
            bare = name[len("__imp_"):]
            # A C import's symbol carries its decoration underscore
            # (`__imp__exit` is `exit`), so the undecorated name comes first:
            # the bare spelling `_exit` is a different CRT import.
            found = self.slots.get(_undecorate(bare)) or self.slots.get(bare)
            return found or None
        return None

    def _read(self, rva, size):
        try:
            offset = build.rva_to_file_offset(self.sections, rva)
        except ValueError:  # outside every section: nothing there to compare
            return None
        chunk = self.image[offset:offset + size]
        return chunk if len(chunk) == size else None

    def _stub(self, address):
        """Where an incremental-link stub at `address` jumps, else None. A stub
        sits in a packed .text table: another `jmp` right before or after it.
        The same byte pattern in data is not executable and proves no route."""
        import struct
        text = next((section for section in self.sections if section["name"] == ".text"), None)
        if text is None or not text["rva"] <= address < text["rva"] + text["size"]:
            return None
        around = self._read(address - 5, 15)
        if around is None or around[5] != 0xE9 or (around[0] != 0xE9 and around[10] != 0xE9):
            return None
        target = address + 5 + struct.unpack_from("<i", around, 6)[0]
        return target if text["rva"] <= target < text["rva"] + text["size"] else None

    def _lands(self, target, expected):
        if target in expected or self._stub(target) in expected:
            return True
        return any(self._stub(address) == target for address in expected)

    @staticmethod
    def _verdict_fingerprint(symbol, relocs):
        """Parts of one copy that can change relocation judgment.

        The COMDAT digest deliberately normalises a TU-local referent to
        ``local`` so equivalent private labels do not manufacture conflicts.
        That digest is therefore too coarse for the verdict cache: a label in
        the COMDAT's own section is checked at its section-relative value, and
        two copies can have the same digest while those values differ. Keep
        section numbering out of the per-relocation description: only whether
        the referent is in the symbol's own section affects _judge. The object
        context separately binds any recursive proof to all its definitions.
        """
        found = []
        for where, kind, referent in relocs:
            external = referent["storage"] in (EXTERNAL, WEAK_EXTERNAL)
            same_section = referent["section"] == symbol["section"]
            content = referent.get("content")
            # Mirror _judge's branch order exactly.  In particular, absolute
            # symbols are recognized by name regardless of storage class, and
            # a same-section weak external takes the section-relative branch.
            identity = (("absolute", referent["name"]) if
                        kind == RetailTruth.DIR32 and referent["name"] in RetailTruth.ABSOLUTE else
                        ("content", content) if content is not None else
                        ("self", referent["value"]) if same_section and referent["storage"] != EXTERNAL else
                        ("external", _normal(referent["name"]),
                         (referent.get("definition") or (None, None, None, None))[3]) if external or
                        referent["name"].startswith(RetailTruth.FUNCTION_STATICS) else
                        ("local",))
            found.append((where, kind, identity))
        return symbol.get("proof_context"), symbol["value"], tuple(found)

    def verdict(self, symbol, body, relocs, digest, size):
        home = self.ledger.get(_normal(symbol["name"])) or self.pinned.get(_normal(symbol["name"]))
        if not home:
            return None
        home = set(home) | {self._stub(address) for address in home} - {None}  # a row on an ILT stub
        key = (symbol["name"], digest, self._verdict_fingerprint(symbol, relocs))
        # Hand-built definitions have no immutable object context. Their
        # transitive referents cannot be identified by a COMDAT digest alone.
        cacheable = (symbol.get("proof_context") is not None or
                     not any(referent.get("definition") is not None for _, _, referent in relocs))
        if cacheable and key in self._cache:
            return self._cache[key]
        results = [self._judge(address - symbol["value"], symbol, body, relocs, size) for address in sorted(home)]
        if all(address in self.shared for address in home):
            results = ["unknown" if result == "wrong" else result for result in results]
        result = "retail" if "retail" in results else "unknown" if "unknown" in results else "wrong"
        if cacheable:
            self._cache[key] = result
        return result

    DEFINITION_DEPTH = 6

    def _defined_at(self, definition, target):
        """True when this object's own definition of a referent no ledger row
        places (a vftable, its ??_E, an RTTI record) is retail's bytes where
        retail's relocation lands: judged like any copy, at that address,
        through its own referents. It proves what a fold-proof row there
        would, and only proves: a mismatch leaves the site unknown. A cycle
        back to a definition already being judged at the same address holds
        (a dtor storing the vptr of the vftable whose ??_E calls it)."""
        symbol, body, relocs, digest, size = definition
        context = symbol.get("proof_context")
        # Symbol indices identify definitions only inside their originating
        # object. Untagged definitions use identity for this active traversal,
        # whose stack keeps them alive, and never enter the persistent cache.
        key = (context, symbol["index"], target) if context is not None else (id(definition), target)
        if key in self._defining:
            return True
        if len(self._defining) >= self.DEFINITION_DEPTH:
            return False
        cache = self.__dict__.setdefault("_definition_cache", {})
        if context is not None and key in cache:
            return cache[key]
        outermost = not self._defining  # an inner result may rest on a cycle's assumption: not cached
        self._defining.add(key)
        try:
            proven = self._judge(target - symbol["value"], symbol, body, relocs, size) == "retail"
        finally:
            self._defining.discard(key)
        if outermost and context is not None:
            cache[key] = proven
        return proven

    @property
    def _defining(self):
        return self.__dict__.setdefault("_defining_set", set())

    def _judge(self, start, symbol, body, relocs, size):
        import struct
        if body is None:
            return "unknown"
        retail = self._read(start, size)
        if retail is None:
            return "wrong"
        mask = bytearray(body)
        fields = []
        for where, kind, referent in relocs:
            width = 2 if kind == 0x000A else 4  # IMAGE_REL_I386_SECTION is 16-bit
            if where + width > size:
                return "wrong"
            mask[where:where + width] = retail[where:where + width]
            fields.append((where, kind, referent))
        if bytes(mask) != retail:
            return "wrong"
        result = "retail"
        for where, kind, referent in fields:
            addend = struct.unpack_from("<i", body, where)[0] if kind != 0x000A else 0
            value = struct.unpack_from("<i", retail, where)[0] if kind != 0x000A else 0
            if kind == self.DIR32 and referent["name"] in self.ABSOLUTE:
                if (value - addend) & 0xFFFFFFFF != self.ABSOLUTE[referent["name"]]:
                    return "wrong"
                continue
            if kind == self.DIR32:
                target = (value - addend - BASE) & 0xFFFFFFFF
            elif kind == self.DIR32NB:
                target = (value - addend) & 0xFFFFFFFF
            elif kind == self.REL32:
                target = start + where + 4 + value - addend
            else:
                result = "unknown"
                continue
            if referent.get("content") is not None:
                if self._read(target, len(referent["content"])) != referent["content"]:
                    return "wrong"
                continue
            if referent["section"] == symbol["section"] and referent["storage"] != EXTERNAL:
                expected = {start + referent["value"]}  # a label in this very section
            elif referent["storage"] in (EXTERNAL, WEAK_EXTERNAL):
                expected = self.addresses(referent["name"], kind)
            elif referent["name"].startswith(self.FUNCTION_STATICS):
                # A static named after its function (MSVC's __ehhandler$<name>):
                # the same name in every TU's copy and rowed like any body, so
                # landing on its row proves the site. It never disproves one:
                # a handler row can be the one of an ICF twin's home. A copy's
                # own handler with no row of its name is proven where retail's
                # slot lands on a rowed handler: /OPT:ICF folded it into a twin
                # (2 concrete bytes, too few for a fold-proof pin), and a row
                # under its own name would prove no more, the gate copying the
                # FuncInfo DIR32 from retail.
                found = self.addresses(referent["name"], kind)
                if not found and referent["name"] == self.FUNCTION_STATICS[0] + symbol["name"]:
                    found = getattr(self, "eh_handlers", set())
                if not found or not self._lands(target, found):
                    result = "unknown"
                continue
            else:  # a static's name is per TU (_$E2, $SG1234): no address to check
                expected = None
            if not expected and referent.get("definition") is not None:
                if self._defined_at(referent["definition"], target):
                    continue
            if not expected:
                result = "unknown"
            elif not self._lands(target, expected):
                if not all(address in self.shared for address in expected):
                    return "wrong"
                result = "unknown"
        return result


_TRUTH = None


def _truth_init(rows):
    global _TRUTH
    _TRUTH = RetailTruth(rows)


@_timed('comdat_conflicts (COFF parse)')
def comdat_conflicts(objs):
    """{name: [(sha, size, obj), ...]} for COMDAT symbols whose copies differ.

    The linker never reports these: inline functions, template instances and
    vftables are COMDATs, and link.exe keeps one copy and discards the rest
    without a word. When two TUs compiled different private copies of a class,
    that silent pick is a one-definition-rule violation, the failure the
    unresolved/duplicate counts cannot show.
    """
    copies = collections.defaultdict(dict)
    for obj, bodies in zip(objs, memo_map("comdat_bodies", objs)):
        for name, digest, size in bodies:
            copies[name].setdefault(digest, (size, obj.name))
    return {name: [(sha, size, obj) for sha, (size, obj) in found.items()]
            for name, found in copies.items() if len(found) > 1}


def keep_rule(copies, referenced=True, retail_kept=True, retail_first=True):
    """({object: loses?}, rule) for one COMDAT symbol's copies [(object, digest,
    verdict)] in link order.

    `retail` when retail truth can judge the symbol (it has a retail address):
    a copy proven wrong loses; a proven copy never does; a copy whose bytes
    match but whose relocations cannot all be resolved loses only when it
    differs from the kept copy (the first proven one, else the first
    unresolved one), since nothing shows it is right. `first` when it cannot:
    link.exe keeps the first copy in link order, so a copy that differs from
    that one loses. Majority is never used: it would let the most-copied
    private class decide what retail shipped.

    `unreferenced` (since retail-truth-2) when retail truth cannot judge the
    symbol AND `referenced` is false: nothing the link keeps references the
    name (referenced_names), so no copy of it is ever executed and /OPT:REF
    drops every copy; which one the linker would pick decides nothing, and no
    copy loses. A referenced name, or one retail truth can judge, keeps the
    rules above.

    `retail_kept` (since retail-truth-3): a copy proven wrong does not lose
    when another copy of the name is proven retail's. That copy is the one the
    image should run, and whether the link actually keeps it is judged
    separately for every unit touching the name (judge_selected,
    wrong_selected). A discarded copy runs nowhere: the original build
    discarded its units' differing copies the same way (retail's body is one
    unit's copy). False gives retail-truth-2, where every wrong copy loses.

    `retail_first` (since retail-truth-4, with `retail_kept`): an unproven copy
    that differs from the proven one does not lose either when the copy the
    link keeps, the first in link order, is proven retail's. The link then runs
    that copy and discards every other, unproven ones included, so none of them
    runs. Only the first copy decides: when it is not proven, an unproven copy
    that differs from the proven one still loses, since the link may keep an
    unproven body. False gives retail-truth-3.
    """
    verdicts = [verdict for _, _, verdict in copies]
    if all(verdict is None for verdict in verdicts):
        if not referenced:
            return {obj: False for obj, _, _ in copies}, "unreferenced"
        kept = copies[0][1]
        return {obj: digest != kept for obj, digest, _ in copies}, "first"
    proven = [digest for _, digest, verdict in copies if verdict == "retail"]
    unknown = [digest for _, digest, verdict in copies if verdict == "unknown"]
    kept = proven[0] if proven else unknown[0] if unknown else None
    kept_retail = retail_kept and retail_first and copies[0][2] == "retail"
    loses = {}
    for obj, digest, verdict in copies:
        wrong = verdict == "wrong" and not (retail_kept and proven)
        unproven = verdict == "unknown" and digest != kept and digest not in proven and not kept_retail
        loses[obj] = wrong or unproven
    return loses, "retail"


SELECT_NODUPLICATES, SELECT_ASSOCIATIVE = 1, 5
LNK_INFO, LNK_REMOVE = 0x200, 0x800  # .drectve, and sections the linker never places
DIRECTIVE_ROOT = re.compile(r"/(?:INCLUDE|EXPORT):(\"[^\"]+\"|[^\s,=]+)", re.I)


def object_references(obj, data=None):
    """(roots, edges) of one object's relocations, by name, for referenced_names.

    `roots`: the names referenced from what a link always keeps: a section that
    is not a COMDAT, or a NODUPLICATES COMDAT (/Gy gives every non-inline
    function one; /OPT:REF could drop an unreferenced one, so this
    over-approximates), plus /INCLUDE: and /EXPORT: directives. `edges`: for
    each external name a discardable COMDAT (ANY, SAME_SIZE, ...) defines, the
    names that section references. A section's references include those of the
    sections it reaches through TU-local symbols (a static, a $LN label, a
    section symbol) and of its ASSOCIATIVE children (EH tables), which the
    linker keeps or drops with it; a local section defining an external name
    references that name. Debug sections (.debug$*) and LNK_REMOVE/LNK_INFO
    sections reference nothing: /DEBUG's FPO records name every function.
    An unreadable object raises MissingObject. `data`, when given, is the
    object's bytes, read by the caller."""
    import struct
    try:
        data = obj.read_bytes() if data is None else data
        count = struct.unpack_from("<H", data, 2)[0]
        optional = struct.unpack_from("<H", data, 16)[0]
        table, nsyms = struct.unpack_from("<II", data, 8)
        sections = []
        for index in range(count):
            header = 20 + optional + index * 40
            name = data[header:header + 8].rstrip(b"\0")
            size, pointer, relocs = struct.unpack_from("<III", data, header + 16)
            nrelocs = struct.unpack_from("<H", data, header + 32)[0]
            flags = struct.unpack_from("<I", data, header + 36)[0]
            sections.append((name, size, pointer, relocs, nrelocs, flags))
        symbols = {symbol["index"]: symbol for symbol in _coff_symbols(data)}
        selection, parent = {}, {}
        at = 0
        while at < nsyms:
            record = table + 18 * at
            value, section, _, storage, aux = struct.unpack_from("<IhHBB", data, record + 8)
            if storage == 3 and aux and value == 0 and 0 < section <= count and section not in selection:
                selection[section] = data[record + 18 + 14]
                parent[section] = struct.unpack_from("<H", data, record + 18 + 12)[0]
            at += 1 + aux
    except (OSError, ValueError, struct.error, IndexError) as exc:
        raise MissingObject(f"{obj}: cannot read relocations ({exc})") from exc

    def ignored(number):
        name, _, _, _, _, flags = sections[number - 1]
        return bool(flags & (LNK_INFO | LNK_REMOVE)) or name.startswith(b".debug")

    defines = collections.defaultdict(set)
    for symbol in symbols.values():
        if symbol["storage"] == EXTERNAL and 0 < symbol["section"] <= count:
            defines[symbol["section"]].add(symbol["name"])
    names, local = collections.defaultdict(set), collections.defaultdict(set)
    for number in range(1, count + 1):
        if ignored(number):
            continue
        _, _, _, relocs, nrelocs, _ = sections[number - 1]
        for entry in range(relocs, relocs + 10 * nrelocs, 10):
            target = symbols.get(struct.unpack_from("<I", data, entry + 4)[0])
            if target is None:
                raise MissingObject(f"{obj}: a relocation of section {number} names no symbol")
            if target["storage"] in (EXTERNAL, WEAK_EXTERNAL) or target["section"] <= 0:
                names[number].add(target["name"])
            elif target["section"] <= count:
                local[number].add(target["section"])
    for child, owner in parent.items():
        if selection.get(child) == SELECT_ASSOCIATIVE and 0 < owner <= count:
            local[owner].add(child)

    def reach(start):
        seen, stack, found = {start}, [start], set()
        while stack:
            number = stack.pop()
            found |= names[number]
            if number != start:
                found |= defines[number]
            for other in local[number] - seen:
                if not ignored(other):
                    seen.add(other)
                    stack.append(other)
        return found

    roots, edges = set(), {}
    for number in range(1, count + 1):
        if ignored(number) or selection.get(number) == SELECT_ASSOCIATIVE:
            continue
        if not sections[number - 1][5] & COMDAT or selection.get(number) == SELECT_NODUPLICATES:
            roots |= reach(number)
        else:
            for name in defines[number]:
                edges.setdefault(name, set()).update(reach(number))
    for number in range(1, count + 1):
        name, size, pointer = sections[number - 1][:3]
        if name == b".drectve" and pointer:
            text = data[pointer:pointer + size].decode("latin-1")
            roots.update(found.strip('"') for found in DIRECTIVE_ROOT.findall(text))
    return roots, {name: frozenset(found) for name, found in edges.items()}


# Per-object parses the census repeats on every object, every run, memoised by
# the CONTENT they parse: an entry is keyed by the sha256 of the object's bytes
# and lives under a directory named for the digest of the code that computed
# it (MEMO_CODE: the files the parse runs, the Python version, MEMO_VERSION),
# so a changed object or a changed parser never meets an old entry. The value
# stored is the value the parse returned for exactly those bytes (pickle keeps
# sets, frozensets and tuples as they were); a missing, unreadable or corrupt
# entry recomputes, and nothing that raises is stored. LINK_CENSUS_MEMO=off
# computes everything and stores nothing.
MEMO = ROOT / "build" / "link_census_cache"
MEMO_VERSION = 1
MEMO_CODE = {"references": ("link_census.py",), "comdat_bodies": ("link_census.py",),
             "symbols": ("link_census.py",)}
MEMO_CODE_DIR = Path(__file__).resolve().parent
_MEMO_KEYS = {}


def _memo_dir(kind):
    if kind not in _MEMO_KEYS:
        digest = hashlib.sha256(json.dumps([MEMO_VERSION, kind, list(sys.version_info[:2])]).encode())
        for name in MEMO_CODE[kind]:
            digest.update(name.encode() + b"\0" + (MEMO_CODE_DIR / name).read_bytes())
        _MEMO_KEYS[kind] = MEMO / f"{kind}-{digest.hexdigest()[:16]}"
    return _MEMO_KEYS[kind]


def memo_enabled():
    """False with LINK_CENSUS_MEMO=off, and inside pytest unless a test turns
    it on (LINK_CENSUS_MEMO=on): fixture objects never fill the checkout's memo."""
    setting = os.environ.get("LINK_CENSUS_MEMO", "").lower()
    if setting == "off":
        return False
    return setting == "on" or "pytest" not in sys.modules


def _memo_compute(kind, obj, data):
    if kind == "references":
        return object_references(obj, data)
    if kind == "comdat_bodies":
        return comdat_bodies(obj, data)
    return object_symbols(obj, data)


def memo_parse(kind, obj):
    """(value, hit): `kind`'s parse of `obj` (MEMO_CODE), from the memo when
    an entry for these exact bytes exists, else computed and stored. A read
    error is the parse's own: comdat_bodies reads an unreadable object as
    none, object_references raises MissingObject."""
    import pickle
    try:
        data = obj.read_bytes()
    except OSError as exc:
        if kind == "comdat_bodies":
            return [], False
        if kind == "references":
            raise MissingObject(f"{obj}: cannot read relocations ({exc})") from exc
        raise
    if not memo_enabled():
        return _memo_compute(kind, obj, data), False
    key = hashlib.sha256(data).hexdigest()
    path = _memo_dir(kind) / key[:2] / f"{key}.pickle"
    try:
        value = pickle.loads(path.read_bytes())
        try:
            os.utime(path)  # prune_memo keeps what is used
        except OSError:
            pass
        return value, True
    except FileNotFoundError:
        pass
    except Exception:  # noqa: BLE001 -- a torn or foreign entry: recompute and replace it
        pass
    value = _memo_compute(kind, obj, data)
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        temp = path.with_name(f"{path.name}.{os.getpid()}.{id(value)}.tmp")
        temp.write_bytes(pickle.dumps(value, protocol=pickle.HIGHEST_PROTOCOL))
        os.replace(temp, path)
    except OSError:
        pass  # the memo only saves time
    return value, False


def _memo_references(obj):
    return memo_parse("references", obj)


def _memo_comdat_bodies(obj):
    return memo_parse("comdat_bodies", obj)


def _memo_symbols(obj):
    return memo_parse("symbols", obj)


def memo_map(kind, objs, parallel=True):
    """[memo_parse(kind, obj)[0] for obj in objs], in parallel (BUILD_POOL
    processes) for a whole link unless `parallel` is false (a caller in a
    side thread: no fork beside a running link), reporting the hit rate."""
    fn = {"references": _memo_references, "comdat_bodies": _memo_comdat_bodies, "symbols": _memo_symbols}[kind]
    workers = build._pool_size() if parallel else 1
    if workers > 1 and len(objs) >= 200:
        with concurrent.futures.ProcessPoolExecutor(workers) as pool:
            found = list(pool.map(fn, objs, chunksize=64))
    else:
        found = [fn(obj) for obj in objs]
    if _PROFILE:
        print(f"link_census: memo {kind}: {sum(hit for _, hit in found):,} of {len(found):,} objects reused",
              file=sys.stderr, flush=True)
    return [value for value, _ in found]


def prune_memo(days=14):
    """Drop memo entries nothing used for `days`, and every entry of code that
    is no longer this checkout's."""
    import shutil
    if not memo_enabled() or not MEMO.is_dir():
        return
    current = {_memo_dir(kind).name for kind in MEMO_CODE}
    cutoff = time.time() - days * 86400
    for directory in MEMO.iterdir():
        if directory.name not in current:
            shutil.rmtree(directory, ignore_errors=True)
            continue
        for entry in directory.glob("*/*.pickle"):
            try:
                if entry.stat().st_mtime < cutoff:
                    entry.unlink()
            except OSError:
                pass


@_timed('read_references (COFF parse)')
def read_references(objs):
    """object_references for every object (memo_map)."""
    return memo_map("references", objs)


def merge_references(references):
    """(roots, edges) of a whole link from object_references' per-object
    results: the union of every object's roots, and each name's edges from
    every copy of it (a copy the linker discards still counts, so a name is
    never unreferenced because the kept copy happens to call less)."""
    roots, edges = set(), collections.defaultdict(set)
    for found, more in references:
        roots |= found
        for name, targets in more.items():
            edges[name] |= targets
    return roots, edges


def referenced_names(roots, edges, kept=(), links=(), known=frozenset()):
    """Every name the link keeps reachable: `roots` and whatever their names'
    definitions reference, transitively through `edges` (merge_references).
    `kept` are names known to be in the image (a ledger row's name, a name
    with a retail address): their definitions' references count too. `links`
    are (name, target) pairs a reference to `name` also reaches: a weak
    external's default and an /alternatename alias's target. A COMDAT name
    outside the result is referenced by nothing the link keeps. `known` is an
    earlier result, already closed under the same edges: its names are not
    walked again, and only the names newly reached are returned."""
    also = collections.defaultdict(set)
    for name, target in links:
        also[name].add(target)
    found = set(roots) - known
    stack = list(found) + [name for name in kept if name not in found and name not in known]
    found.update(name for name in kept if name not in known)
    while stack:
        name = stack.pop()
        for target in edges.get(name, frozenset()) | also.get(name, set()):
            if target not in found and target not in known:
                found.add(target)
                stack.append(target)
    return found


@_timed('link_references')
def link_references(present, facts, owners, references=None):
    """(merged edges, referenced names) of one census's objects: the names
    referenced_names reaches from every object's roots, every ledger owner's
    name and every name with a retail address (any COMDAT copy retail truth
    can judge), through weak externals and /alternatename aliases."""
    import link_check
    references = read_references(present) if references is None else references
    roots, edges = merge_references(references)
    kept = set(owners)
    links = []
    for obj, (copies, _, _, weaks) in zip(present, facts):
        kept.update(name for name, _, _, verdict in copies if verdict is not None)
        links.extend(weaks)
        links.extend(link_check.alternate_names(obj).items())
    return edges, referenced_names(roots, edges, kept, links)


def _comdat_selections(data):
    """{section number: COMDAT selection} from each section definition's aux
    record (IMAGE_COMDAT_SELECT_NODUPLICATES = 1, _ANY = 2, ...)."""
    import struct
    table, count = struct.unpack_from("<II", data, 8)
    found, index = {}, 0
    while index < count:
        record = table + 18 * index
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", data, record + 8)
        if storage == 3 and aux and value == 0 and section > 0:  # IMAGE_SYM_CLASS_STATIC section symbol
            found.setdefault(section, data[record + 18 + 14])
        index += 1 + aux
    return found


class MissingObject(RuntimeError):
    """An object a check needs cannot be read. Never an empty object: an
    object with no facts has no blockers and would read as linking."""


def common_definitions(obj):
    """COFF COMMON data definitions, kept separate from exclusive definitions.

    An external section-zero record with nonzero value allocates that many
    bytes. Multiple COMMON records merge; a normal definition overrides them.
    Extraction proves a provider exists, not its retail layout or identity.
    """
    import struct
    try:
        data = obj.read_bytes()
        if len(data) < 20:
            raise ValueError("truncated COFF header")
        table, count = struct.unpack_from("<II", data, 8)
        sections, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
        header_end = 20 + optional + sections * 40
        if header_end > len(data):
            raise ValueError("truncated section table")
        if table == 0 and count == 0:
            return {}
        strings = table + count * 18
        if table < header_end or strings + 4 > len(data):
            raise ValueError("truncated symbol table")
        size = struct.unpack_from("<I", data, strings)[0]
        if size < 4 or strings + size > len(data):
            raise ValueError("truncated string table")
        at = 0
        while at < count:
            record = table + at * 18
            aux = data[record + 17]
            if at + aux >= count:
                raise ValueError("truncated auxiliary symbol")
            if data[record:record + 4] == b"\0" * 4:
                offset = struct.unpack_from("<I", data, record + 4)[0]
                if offset < 4 or offset >= size or data.find(b"\0", strings + offset, strings + size) < 0:
                    raise ValueError("invalid symbol name")
            at += 1 + aux
        result = {}
        for symbol in _coff_symbols(data):
            if symbol["storage"] == EXTERNAL and symbol["section"] == 0 and symbol["value"] > 0:
                result[symbol["name"]] = max(result.get(symbol["name"], 0), symbol["value"])
        return result
    except (OSError, ValueError, struct.error, IndexError) as exc:
        raise MissingObject(f"{obj}: cannot read COMMON definitions ({exc})") from exc


def object_facts(obj, truth=None):
    """(COMDAT copies [(name, digest, size, verdict)], exclusive definitions,
    undefined externals, weak externals [(name, default)]) of one object:
    what a link needs to know about it. An unreadable object raises
    MissingObject.
    A definition is exclusive when link.exe refuses a second one (LNK2005):
    in an ordinary section, or in a COMDAT whose selection is NODUPLICATES,
    which /Gy gives every non-inline function."""
    truth = truth or _TRUTH
    try:
        data = obj.read_bytes()
    except OSError as exc:
        raise MissingObject(f"{obj}: cannot read the object ({exc})") from exc
    import struct
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    comdat = {index + 1 for index in range(count)
              if struct.unpack_from("<I", data, 20 + optional + index * 40 + 36)[0] & COMDAT}
    selections = _comdat_selections(data)
    strong, undefined = [], []
    for symbol in _coff_symbols(data):
        if symbol["storage"] != EXTERNAL:
            continue
        if symbol["section"] == 0:
            if symbol["value"] == 0:  # a nonzero value is a common symbol: a definition that merges
                undefined.append(symbol["name"])
        elif symbol["section"] not in comdat or selections.get(symbol["section"]) == 1:
            strong.append(symbol["name"])
    copies = [(symbol["name"], digest, size, truth.verdict(symbol, body, relocs, digest, size))
              for symbol, body, relocs, digest, size in _comdat_sections(data)]
    return copies, strong, undefined, _weak_externals(data)


def _weak_externals(data):
    """[(name, default)] for each weak external: the name resolves to
    `default` when no object defines it (IMAGE_WEAK_EXTERN aux TagIndex)."""
    import struct
    names = {symbol["index"]: symbol["name"] for symbol in _coff_symbols(data)}
    table, count = struct.unpack_from("<II", data, 8)
    found, index = [], 0
    while index < count:
        storage, aux = data[table + 18 * index + 16], data[table + 18 * index + 17]
        if storage == WEAK_EXTERNAL and aux:
            tag = struct.unpack_from("<I", data, table + 18 * (index + 1))[0]
            found.append((names.get(index, "?"), names.get(tag, "?")))
        index += 1 + aux
    return found


@_timed('read_facts (COFF parse + retail truth)')
def read_facts(objs, rows):
    """object_facts for every object, in parallel (BUILD_POOL processes)."""
    workers = build._pool_size()
    if workers > 1:
        import concurrent.futures
        with concurrent.futures.ProcessPoolExecutor(workers, initializer=_truth_init, initargs=(rows,)) as pool:
            return list(pool.map(object_facts, objs, chunksize=64))
    truth = RetailTruth(rows)
    return [object_facts(obj, truth) for obj in objs]


@_timed('comdat_losers')
def comdat_losers(objs, rows=None, stats=None, facts=None, referenced=None, retail_kept=True,
                  retail_first=True):
    """{object name: {symbol}} for COMDAT copies that are not retail's body.

    keep_rule() decides each symbol: by retail truth where the ledger gives it
    a retail address, else by link order (link.exe keeps the first copy, so an
    object whose copy differs from that one runs someone else's code). Before
    2026-09-29 every symbol used link order, so an arbitrary first object
    decided who lost: for ??1AsciiString@@QAE@XZ the first object held a
    minority variant, and the retail-true copies were the ones charged.
    `stats`, when given, collects how many symbols and losing copies each
    rule decided. `facts` is read_facts(objs), read here when not given.
    `referenced` (link_references) is the set of names the link keeps
    reachable; keep_rule exempts the copies of a name with no retail address
    outside it. None judges every name as referenced (retail-truth-1).
    `retail_kept` and `retail_first` are keep_rule's: retail_first=False
    measures retail-truth-3, retail_kept=False retail-truth-2."""
    rows = ledger() if rows is None else rows
    facts = read_facts(objs, rows) if facts is None else facts
    copies = collections.defaultdict(list)
    for obj, (found, _, _, _) in zip(objs, facts):
        for name, digest, _, verdict in found:
            copies[name].append((obj.name, digest, verdict))
    losers = collections.defaultdict(set)
    stats = stats if stats is not None else {}
    for name, found in copies.items():
        loses, rule = keep_rule(found, referenced is None or name in referenced, retail_kept, retail_first)
        stats[f"symbols_{rule}"] = stats.get(f"symbols_{rule}", 0) + 1
        for obj, lost in loses.items():
            if lost:
                losers[obj].add(name)
                stats[f"losers_{rule}"] = stats.get(f"losers_{rule}", 0) + 1
    return losers


# keep_rule's `unreferenced` rule rightly charges no copy of a name the link
# never keeps, but that also hid the commonest sign of a stale private class
# view: a copy of a no-address inline the same length as the other units'
# copy, a few displacement bytes off (Player::getPlayerIndex reading the wrong
# member offset; AsciiString::str with Zero Hour's 4-byte string header). The
# census still records those copies as a diagnostic, never as a blocker: they
# change no LINKED figure, blocker count, history row or rules id.
UNREFERENCED_COPIES = OUT / "unreferenced_copies.json"
LAYOUT_DIFF_BYTES = 4  # at most this many bytes off, same length: layout-like


def instruction_shape(code):
    """[(mnemonic, size, operands)] of x86 code with every register operand
    reduced to "reg": two bodies of one shape differ only in register
    allocation. Immediates and memory displacements stay, so a member
    offset or a sizeof still shows."""
    import capstone
    from capstone import x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    shape = []
    for ins in md.disasm(bytes(code), 0):
        operands = []
        for op in ins.operands:
            if op.type == x86.X86_OP_REG:
                operands.append("reg")
            elif op.type == x86.X86_OP_IMM:
                operands.append(("imm", op.imm))
            elif op.type == x86.X86_OP_MEM:
                operands.append(("mem", op.size, op.mem.disp, op.mem.scale, op.mem.base != 0, op.mem.index != 0))
        shape.append((ins.mnemonic, ins.size, tuple(operands)))
    return shape


def copy_kind(body, majority):
    """(kind, differing bytes) of one COMDAT copy against the majority copy.

    For a copy of the majority's length with differing bytes: "register" when
    both decode to the same instructions, immediates and displacements and
    only the register choice differs (register allocation, not layout);
    else "layout" when at most LAYOUT_DIFF_BYTES bytes differ (a member
    offset, a sizeof or an operand type: a stale class view). "relocation"
    when the bytes are equal and only the relocations differ (a call or a
    vftable slot binding another name); "codegen" otherwise (inlining,
    flags); "unclassified" when a body cannot be read."""
    if body is None or majority is None:
        return "unclassified", None
    if len(body) != len(majority):
        return "codegen", None
    differ = sum(a != b for a, b in zip(body, majority))
    if not differ:
        return "relocation", 0
    if instruction_shape(body) == instruction_shape(majority):
        return "register", differ
    return ("layout" if differ <= LAYOUT_DIFF_BYTES else "codegen"), differ


def majority_digest(digests):
    """The most common digest of a name's copies (in link order); a tie goes
    to the first in link order."""
    counts = collections.Counter(digests)
    best = max(counts.values())
    return next(digest for digest in digests if counts[digest] == best)


def comdat_section_bodies(obj, names, digests=False):
    """{name: section bytes or None} for the COMDAT symbols `names` one object
    defines ({name: (bytes, digest)} with `digests`); an unreadable object
    gives nothing."""
    import struct
    read = getattr(obj, "read_bytes", None)
    if read is None:
        return {}
    try:
        return {symbol["name"]: (body, digest) if digests else body
                for symbol, body, _, digest, _ in _comdat_sections(read()) if symbol["name"] in names}
    except (OSError, struct.error, ValueError, IndexError):
        return {}  # a diagnostic never fails a census or a check


@_timed('unreferenced_differs')
def unreferenced_differs(objs, facts, referenced):
    """{object name: [entry]} for every COMDAT copy keep_rule's `unreferenced`
    rule exempts that differs from the majority copy of its name: a name with
    no retail address that nothing the link keeps references (`referenced`,
    link_references; None, retail-truth-1, exempts nothing). Each entry is
    {name, kind, bytes_differ, size, majority_size, majority_object}, kind by
    copy_kind. Diagnostic only: it decides nothing a link is charged with."""
    if referenced is None:
        return {}
    copies = collections.defaultdict(list)
    for position, (found, _, _, _) in enumerate(facts):
        for name, digest, _, verdict in found:
            copies[name].append((position, digest, verdict))
    wanted, plan = collections.defaultdict(set), []
    for name, found in copies.items():
        if name in referenced or any(verdict is not None for _, _, verdict in found):
            continue
        if len({digest for _, digest, _ in found}) < 2:
            continue
        major = majority_digest([digest for _, digest, _ in found])
        model = next(position for position, digest, _ in found if digest == major)
        wanted[model].add(name)
        for position, digest, _ in found:
            if digest != major:
                wanted[position].add(name)
                plan.append((name, position, model))
    bodies = {}
    for position, names in wanted.items():
        for name, body in comdat_section_bodies(objs[position], names).items():
            bodies[position, name] = body
    out = collections.defaultdict(list)
    for name, position, model in plan:
        body, majority = bodies.get((position, name)), bodies.get((model, name))
        kind, differ = copy_kind(body, majority)
        out[objs[position].name].append({
            "name": name, "kind": kind, "bytes_differ": differ, "size": None if body is None else len(body),
            "majority_size": None if majority is None else len(majority), "majority_object": objs[model].name})
    return {obj: sorted(entries, key=lambda entry: entry["name"]) for obj, entries in out.items()}


def unreferenced_summary(by_source):
    """{kind: copies} and {kind: units} over unreferenced_differs entries
    keyed by source (or object)."""
    copies, units = collections.Counter(), collections.Counter()
    for entries in by_source.values():
        kinds = collections.Counter(entry["kind"] for entry in entries)
        copies.update(kinds)
        units.update(kinds.keys())
    return dict(copies), dict(units)


def read_unreferenced_copies(path=None):
    """{source: [entry]} from the last census's UNREFERENCED_COPIES ({} when
    no census wrote one)."""
    path = UNREFERENCED_COPIES if path is None else path
    try:
        return json.loads(path.read_text(encoding="utf-8")).get("units", {})
    except (OSError, ValueError):
        return {}


def ledger_owners(rows, data=None):
    """{name: {object}}: the object of each ledger row naming it (its object
    symbol too), never an icf-owner over-claim or a scaffold row, and of each
    matched data row (`data`, default data_ledger()). For a name several
    objects define, the owner's is retail's definition."""
    owners = collections.defaultdict(set)
    for row in rows:
        if "icf-owner=" not in (row.get("notes") or "") and not build.is_scaffold_row(row):
            for name in {row["name"], build.ledger_object_symbol(row)}:
                owners[name].add(build.row_object(row).name)
    for row in data_ledger() if data is None else data:
        owners[row["name"]].add(data_object(row).name)
    return owners


def judge_selected(holder, copies, definers, exclusive, owners):
    """Is the definition the link kept for one name retail's?

    `holder` is the object whose definition the link kept (None when the map
    does not say); `copies` {object: (digest, verdict)} the name's COMDAT
    copies with their retail-truth verdicts; `definers` every object defining
    it; `exclusive` those whose definition is exclusive (an ordinary section or
    a NODUPLICATES COMDAT); `owners` the ledger owner objects.

    "wrong" when the kept copy is proven not retail's body, or when two or
    more objects define the name, one exclusively, and the kept definition is
    not a ledger owner's (operator new/delete kept from GameMemory.obj while
    the retail body is mem_ops.obj's). Proven bytes decide before ownership.
    "ok" when it is proven (its bytes, or the owner's matched row); "unknown"
    when the choice matters (copies differ, or a duplicate) and nothing proves
    it either way; None when there is nothing to choose between."""
    if holder is None or holder not in definers:
        return "unknown" if len(definers) > 1 else None
    _, verdict = copies.get(holder, (None, None))
    if verdict == "wrong":
        return "wrong"
    if verdict == "retail":
        return "ok"
    if len(definers) > 1 and exclusive:
        mine = owners & definers
        if mine:
            return "ok" if holder in mine else "wrong"
        return "unknown"
    if len({digest for digest, _ in copies.values()}) > 1:
        return "unknown"
    return None


def touched_names(fact):
    """Every name one object's facts define or reference (weak externals and
    their defaults included)."""
    copies, strong, undefined, weaks = fact
    names = {name for name, _, _, _ in copies} | set(strong) | set(undefined)
    for name, default in weaks:
        names.update((name, default))
    return names


@_timed('selection_verdicts')
def selection_verdicts(present, facts, owners, kept):
    """({name: result}, {name: holder index or None}) for every name the census
    objects define, judged on the definition the link kept (`kept`, from the
    /MAP: selected_definitions). The second map lists only the names whose
    kept definition is NOT the first definer in link order (link.exe keeps the
    first for all but a handful), so link_check can predict the holder the way
    the census saw it."""
    position = {obj.name: index for index, obj in enumerate(present)}
    copies = collections.defaultdict(dict)
    definers = collections.defaultdict(set)
    exclusive = collections.defaultdict(set)
    for obj, (found, strong, _, _) in zip(present, facts):
        for name, digest, _, verdict in found:
            copies[name].setdefault(obj.name, (digest, verdict))
            definers[name].add(obj.name)
        for name in strong:
            definers[name].add(obj.name)
            exclusive[name].add(obj.name)
    results, exceptions = {}, {}
    for name, objs in definers.items():
        holder = kept.get(name)
        holder = holder if holder in objs else None
        first = min(objs, key=position.__getitem__)
        if holder != first:
            exceptions[name] = position[holder] if holder is not None else None
        result = judge_selected(holder, copies[name], objs, exclusive[name], owners.get(name, set()))
        if result is not None:
            results[name] = result
    return results, exceptions


MAP_PUBLIC = re.compile(r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+[0-9A-Fa-f]{8}\s+(?:f\s+)?(?:i\s+)?(.+?)\s*$")


def selected_definitions(map_text):
    """{symbol: object} for the definition link.exe put in the image, from
    the /MAP file's "Publics by Value" (its Lib:Object column)."""
    found = {}
    for line in map_text.splitlines():
        if line.lstrip().startswith("Static symbols"):
            break
        match = MAP_PUBLIC.match(line)
        if match:
            found.setdefault(match.group(1), match.group(2).split(":")[-1])
    return found


SELECTED = OUT / "selected.csv"
DUPLICATES = OUT / "duplicates_selected.csv"
ALIASED = OUT / "aliased.csv"
SELECTION = OUT / "selection.json"


def selection_report(present, facts, rows, clean_objects, map_text, log):
    """What the link actually put in the image, against retail truth.

    The per-file rule asks whether a file's OWN copy is retail's body. The
    image holds one copy per COMDAT symbol, the one link.exe selected, so a
    clean file can still run a wrong copy another object supplied. From the
    /MAP, for every COMDAT symbol whose copies differ: which object's copy was
    selected, its verdict, and whether it was the first in link order.
    `clean_objects` are the objects of files counted as linked; one depends on
    a symbol when it holds a copy of it or references it. Also every name
    that only resolves to a DIFFERENT name: a weak external falling back to
    its default, or an unresolved name the alias scaffold (a pin's address)
    would point at another definition. And every name with more than one
    definition at least one of which is exclusive (an ordinary section or a
    NODUPLICATES COMDAT: LNK2005, a warning LNK4006 under /FORCE): which
    object's definition the link kept, and whether that object is the ledger
    row's own (operator new/delete: mem_ops.cpp holds the retail body,
    GameMemory.cpp another, and link order keeps GameMemory.cpp's). Writes
    selected.csv, duplicates_selected.csv, aliased.csv and selection.json
    under build/link_census/; measures, changes no rule."""
    kept = selected_definitions(map_text)
    position = {obj.name: index for index, obj in enumerate(present)}
    copies = collections.defaultdict(list)
    users = collections.defaultdict(set)
    defined = set()
    weak = collections.defaultdict(set)
    definers, exclusive = collections.defaultdict(set), collections.defaultdict(set)
    for obj, (found, strong, undefined, weaks) in zip(present, facts):
        for name, digest, _, verdict in found:
            copies[name].append((obj.name, digest, verdict))
            users[name].add(obj.name)
            defined.add(name)
            definers[name].add(obj.name)
        defined.update(strong)
        for name in strong:
            definers[name].add(obj.name)
            exclusive[name].add(obj.name)
            users[name].add(obj.name)
        for name in undefined:
            users[name].add(obj.name)
        for name, default in weaks:
            weak[(name, default)].add(obj.name)
    table, counts = [], collections.Counter()
    bad = collections.defaultdict(set)  # clean object -> (symbol, verdict of the selected copy)
    for name, found in copies.items():
        if len({digest for _, digest, _ in found}) < 2:
            continue
        holder = kept.get(name, "")
        verdicts = {obj: verdict for obj, _, verdict in found}
        verdict = verdicts[holder] if holder in verdicts else "not-in-map"
        verdict = verdict or "no-address"
        first = min(found, key=lambda copy: position[copy[0]])[0]
        table.append({"symbol": name, "copies": len(found), "digests": len({d for _, d, _ in found}),
                      "selected_object": holder, "selected_verdict": verdict,
                      "selected_is_first": "yes" if holder == first else "no",
                      "retail_true_copies": sum(1 for _, _, v in found if v == "retail")})
        counts[f"selected_{verdict}"] += 1
        counts["selected_first" if holder == first else "selected_not_first"] += 1
        if verdict != "retail":
            for obj in users[name] & clean_objects:
                bad[obj].add((name, verdict))
    with SELECTED.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["symbol", "copies", "digests", "selected_object", "selected_verdict",
                                         "selected_is_first", "retail_true_copies"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(table, key=lambda row: row["symbol"]))
    owners = ledger_owners(rows)
    duplicates, owner_misses = [], collections.defaultdict(set)
    for name, objs in exclusive.items():
        if len(definers[name]) < 2:
            continue
        holder = kept.get(name, "")
        first = min(definers[name], key=lambda obj: position[obj])
        mine = owners.get(name, set()) & definers[name]
        state = "no-owner" if not mine else "owner" if holder in mine else "not-owner"
        duplicates.append({"symbol": name, "definers": len(definers[name]), "exclusive": len(objs),
                           "selected_object": holder, "selected_is_first": "yes" if holder == first else "no",
                           "owner_objects": " ".join(sorted(mine)), "selected": state})
        counts[f"duplicate_{state}"] += 1
        if state == "not-owner":
            for obj in users[name] & clean_objects:
                owner_misses[obj].add(name)
    with DUPLICATES.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["symbol", "definers", "exclusive", "selected_object", "selected_is_first",
                                         "owner_objects", "selected"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(duplicates, key=lambda row: row["symbol"]))
    aliased = []
    for (name, default), objs in sorted(weak.items()):
        if name not in defined and default != name:
            # ??_E (vector deleting dtor) falling back to ??_G (scalar) is how
            # MSVC emits a class nobody deletes as an array: standard, listed.
            aliased.append({"name": name, "via": "weak-external", "resolves_to": default, "excused": "no",
                            "objects": len(objs), "linked_objects": len(objs & clean_objects)})
    _, detail, _, _ = classify(log, rows)
    wanted = [name for name, entry in detail.items() if entry["kind"] in ("alias", "dump", "pinned-elsewhere")]
    referrers = collections.defaultdict(set)
    for line in log.splitlines():
        found, referrer = UNRESOLVED.search(line), REFERRER.match(line)
        if found and referrer:
            referrers[found.group(1) or found.group(2)].add(Path(referrer.group(1)).name)
    crt = build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib"
    runtime, stubs, imported = library_symbols(crt), import_stubs(), retail_imports()
    for name, target in sorted(alias_scaffold(rows, wanted).items()):
        excuse = excused(name, runtime, imported, stubs)  # the real link finds it in an import library
        aliased.append({"name": name, "via": f"pin ({detail[name]['kind']})", "resolves_to": target,
                        "excused": "yes" if excuse else "no", "objects": len(referrers[name]),
                        "linked_objects": len(referrers[name] & clean_objects)})
    with ALIASED.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["name", "via", "resolves_to", "excused", "objects", "linked_objects"],
                                lineterminator="\n")
        writer.writeheader()
        writer.writerows(aliased)
    wrong = {obj for obj, found in bad.items() if any(v == "wrong" for _, v in found)}
    weak_rows = [row for row in aliased if row["via"] == "weak-external"]
    summary = {"conflicted_symbols": len(table), **dict(counts), "linked_files": len(clean_objects),
               "linked_files_on_wrong_selected_copy": len(wrong),
               "linked_files_on_unproven_selected_copy": len(bad),
               "duplicated_symbols": len(duplicates),
               "linked_files_on_non_owner_duplicate": len(owner_misses),
               "top_non_owner_duplicates": collections.Counter(
                   name for found in owner_misses.values() for name in found).most_common(10),
               "weak_fallbacks": len(weak_rows),
               "weak_fallbacks_not_deleting_dtor": sum(1 for row in weak_rows if not (
                   row["name"].startswith("??_E") and row["resolves_to"].startswith("??_G"))),
               "weak_fallbacks_in_linked_files": sum(1 for row in weak_rows if row["linked_objects"]),
               "pin_aliases": len(aliased) - len(weak_rows),
               "pin_aliases_in_linked_files": sum(1 for row in aliased if row["via"] != "weak-external"
                                                  and row["excused"] == "no" and row["linked_objects"]),
               "top_wrong_selected": collections.Counter(
                   name for found in bad.values() for name, v in found if v == "wrong").most_common(10)}
    return summary, bad, owner_misses


def print_selection(summary):
    print(f"  selected COMDAT copies (the /MAP), {summary['conflicted_symbols']:,} symbols whose copies differ:")
    for key in ("retail", "unknown", "wrong", "no-address", "not-in-map", "first", "not_first"):
        print(f"    {key:18} {summary.get('selected_' + key, 0):8,}")
    print(f"  files counted as linked: {summary['linked_files']:,}; "
          f"{summary['linked_files_on_wrong_selected_copy']:,} use a symbol whose selected copy is proven wrong, "
          f"{summary['linked_files_on_unproven_selected_copy']:,} one whose selected copy is not proven retail")
    print(f"  ... those files' LINKED bytes: {summary.get('linked_bytes_on_wrong_selected_copy', 0):,} "
          f"(wrong), {summary.get('linked_bytes_on_unproven_selected_copy', 0):,} (not proven)")
    print(f"  names defined more than once with an exclusive definition: {summary.get('duplicated_symbols', 0):,}; "
          f"the kept definition is the ledger owner's for {summary.get('duplicate_owner', 0):,}, another object's "
          f"for {summary.get('duplicate_not-owner', 0):,}, no owner {summary.get('duplicate_no-owner', 0):,}")
    print(f"  files counted as linked that use a symbol whose kept definition is not its owner's: "
          f"{summary.get('linked_files_on_non_owner_duplicate', 0):,} "
          f"({summary.get('linked_bytes_on_non_owner_duplicate', 0):,} LINKED bytes)")
    print(f"  names resolved only through another name: {summary['weak_fallbacks']:,} weak-external fallbacks "
          f"({summary['weak_fallbacks_not_deleting_dtor']:,} other than ??_E -> ??_G; "
          f"{summary['weak_fallbacks_in_linked_files']:,} used by linked files), {summary['pin_aliases']:,} "
          f"unresolved names a pin would alias ({summary['pin_aliases_in_linked_files']:,} not excused in "
          "linked files)")


def naked_rows():
    """{(name, target_rva)} of the C/C++ rows whose body is naked or __emit
    assembly, by progress.py's scan of the source itself (the rows it counts
    as dumps)."""
    import progress
    return set(progress.naked_cpp_rows_at(progress.matched_at(None), None))


def build_dump(row, naked=frozenset()):
    """Not a C++ definition: a gen-dump row (349 live in gen_small C++), MASM,
    or a naked/__emit body (`naked`, from naked_rows()). Decided from the
    source, never from the note: "exact C++ __emit thunk converted from MASM
    dump" is the note of real C++ (STLRbGlobalBoolIncrementThunk.cpp)."""
    return (build.is_scaffold_row(row) or row["source"].endswith(".asm")
            or (row["name"], row["target_rva"]) in naked)


def report(census):
    print(f"link census {census['when']}: {census['objects']:,} objects linked, "
          f"{census['missing']:,} missing, link {census['seconds']:.0f}s")
    print(f"  unresolved names: {sum(census['unresolved_classes'].values()):,}")
    for kind, count in sorted(census["unresolved_classes"].items(), key=lambda kv: -kv[1]):
        print(f"    {kind:18} {count:8,}")
    print(f"  duplicate definitions: {sum(census['duplicate_classes'].values()):,}")
    for kind, count in sorted(census["duplicate_classes"].items(), key=lambda kv: -kv[1]):
        print(f"    {kind:18} {count:8,}")
    conflicts = census.get("comdat_conflicts", {})
    vtables = sum(1 for name in conflicts if name.startswith(("??_7", "??_R")))
    print(f"  COMDAT copies that differ (linker keeps one silently): {len(conflicts):,} "
          f"({vtables:,} vftable/RTTI)")
    scaffold = census.get("scaffold")
    if scaffold and scaffold.get("crashed"):
        print(f"  with the alias scaffold ({scaffold['aliases']:,} entries): LINK DIED -- {scaffold['crashed']}; "
              "no counts")
    elif scaffold:
        print(f"  with the alias scaffold ({scaffold['aliases']:,} weak-external aliases): "
              f"{sum(scaffold['unresolved_classes'].values()):,} unresolved, "
              f"{sum(scaffold['duplicate_classes'].values()):,} duplicates")
        for kind, count in sorted(scaffold["unresolved_classes"].items(), key=lambda kv: -kv[1]):
            print(f"    {kind:18} {count:8,}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--report", action="store_true", help="summarise build/link_census/census.json")
    ap.add_argument("--scaffold", action="store_true",
                    help="relink with the alias scaffold (a weak external from each called name to the symbol "
                         "defined at its pinned address) and report what remains")
    ap.add_argument("--history", action="store_true",
                    help="append this census to reverse/link_census_history.csv (the daily trend)")
    ap.add_argument("--scaffold-limit", type=int, default=0,
                    help="use only the first N aliases (bisecting a linker failure)")
    ap.add_argument("--build", action="store_true",
                    help="first compile every matched source whose object is not current (build.compile_rows, "
                         "BUILD_POOL defaults to all cores but two); no byte verification")
    ap.add_argument("--measure", action="store_true",
                    help="after the link, run the selection link (in parallel when the unresolved names held) and "
                         "write link_status.csv and the link index with LINKED figures, without recording history")
    ap.add_argument("--selected", action="store_true",
                    help="relink the last census's objects with /MAP and report which COMDAT copy link.exe selected "
                         "(selected.csv, aliased.csv); on the census's own commit, records nothing")
    ap.add_argument("--status", action="store_true",
                    help="redo link_status.csv and the last history row's LINKED from the last link log, on the census's own commit")
    ap.add_argument("--replay", action="store_true",
                    help="with --dry: reuse the last dry census's own plain-link log and /MAP (refused unless its "
                         "objects, their order and the stub names are this run's) instead of running link.exe; every "
                         "other step runs. Only compares the judgment's runs (caches cold and warm); never a census")
    ap.add_argument("--dry", action="store_true",
                    help="with --history: run the whole census (compile, both links, every check, the judgment) but "
                         "write every output, link_status.csv, the history and the link index included, under "
                         "build/link_census_dry/: nothing recorded, nothing for --publish-index (profiling, "
                         "equality runs)")
    args = ap.parse_args(argv)
    global _INPUT_RECEIPTS, _PROFILE
    if args.dry:
        if not args.history or args.report or args.selected or args.status or args.measure or args.scaffold:
            ap.error("--dry goes with --history (and --build) only")
        use_dry_outputs(DRY_OUT)
    elif args.replay:
        ap.error("--replay goes with --dry only")
    _PROFILE = True
    run_started = time.monotonic()
    path = OUT / "census.json"
    if args.report:
        report(json.loads(path.read_text(encoding="utf-8")))
        if SELECTION.exists():
            print_selection(json.loads(SELECTION.read_text(encoding="utf-8")))
        return 0
    if args.selected:
        return selected_main()
    if args.status:
        record(json.loads(path.read_text(encoding="utf-8")), ledger(), rerun=True)
        return 0
    if not (args.history or args.measure or args.scaffold):
        # The index link_check reads is written by record() and measure() only;
        # a bare --build ran a full census on 2026-10-08 and left nothing to check.
        print("link_census: no --measure/--history -- this run writes no link index "
              "(build/link_census/link_index.pkl) for link_check", file=sys.stderr)
    # census_state() is compared at the end of each link; any move aborts the run
    # with nothing recorded, after the whole compile and link have been paid for.
    print("link_census: keep HEAD, compiler inputs and tools/ still until this exits "
          "-- a pull, commit or tools edit meanwhile aborts it at the end", file=sys.stderr, flush=True)
    rows = ledger()
    if args.build:
        os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
        # BUILD_RECOMPILE_ONLY trusts every object it is not told to rebuild;
        # the full currency check below is what proves them instead.
        os.environ.pop("BUILD_RECOMPILE_ONLY", None)
        started = time.time()
        build.ensure_case_shims()
        build.ensure_reference_current()
        import census_receipts
        _INPUT_RECEIPTS = census_receipts.Receipts(OUT / "compile_inputs.json", collect=True)
        _INPUT_RECEIPTS.path.unlink(missing_ok=True)
        build.compile_rows(rows, compile_sources(rows), input_proof=_INPUT_RECEIPTS, strict=True)
        for name, seconds in getattr(build, "COMPILE_TIMINGS", {}).items():
            _stage_line(f"compile: {name}", seconds)
        _INPUT_RECEIPTS.save()
        if _INPUT_RECEIPTS.failures:
            raise SystemExit(f"link_census: {len(_INPUT_RECEIPTS.failures):,} compiled objects have no census "
                             "proof; nothing linked:\n  " + "\n  ".join(sorted(_INPUT_RECEIPTS.failures)))
        print(f"link_census: compile {time.time() - started:.0f}s", flush=True)
    verify_data_objects()
    present, missing = objects(rows)
    sources = _object_sources(rows)
    # Never trust the compile step: a TU it skipped is only as current as its
    # receipt, and one it compiled may have been replaced since.
    state = census_state(present)
    stale = stale_objects(present, sources)
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} source objects are stale, e.g. {stale[0].name}; rerun with --build")
    if missing:
        print(f"link_census: {len(missing):,} objects missing (run the full ./build.sh first); "
              f"linking the {len(present):,} present", file=sys.stderr)
    # The selection (/MAP) link needs the plain link's unresolved names. Those
    # barely move between censuses, so start it now on the last census's
    # names, in parallel; selection_link() uses this result only when the
    # names turn out identical, and relinks otherwise. Same map either way.
    if args.replay:
        log, seconds = replayed_link(present)
    else:
        # Started on the names the objects predict (predicted_unresolved),
        # else the last census's: a first census has no log and no parallel link.
        last = _unresolved_names(OUT / "census.log")
        if last:
            _start_preselection(present, lambda: predicted_unresolved(present) or last)
        fresh_outputs(OUT / "census.exe")
        log, seconds, code = link(present)
        _stage_line("link (plain)", seconds)
        unexplained_exit(code, log, OUT / "census.exe")
    if census_state(present) != state or stale_objects(present, sources):
        raise SystemExit("link_census: compiler inputs, tools or objects changed during link; nothing recorded"
                         f" ({moved(state, census_state(present))})")
    crashed = FATAL.search(log)
    if crashed:
        # A linker that dies prints no per-symbol errors, which would read as
        # "0 unresolved": never report counts from a crashed link.
        raise SystemExit(f"link_census: the link died ({crashed.group(0).strip()}); no counts recorded")
    classes, detail, dup_kinds, dups = classify(log, rows)
    census = {"when": utc_now(), "objects": len(present), "missing": len(missing),
              "seconds": seconds, "unresolved_classes": dict(classes), "duplicate_classes": dict(dup_kinds),
              "unresolved": detail, "duplicates": dups, "comdat_conflicts": comdat_conflicts(present),
              "missing_objects": [str(p.relative_to(ROOT)) for p in missing[:200]],
              "rules": RULES, "commit": head(), "tools": state["tools"], "objects_digest": objects_digest(present)}
    receipts = input_receipts()
    if receipts is not None:
        census["compile_input_run"] = receipts.run
    if args.scaffold:
        wanted = [name for name, entry in detail.items() if entry["kind"] in ("alias", "dump", "pinned-elsewhere")]
        table = alias_scaffold(rows, wanted)
        if args.scaffold_limit:
            table = dict(sorted(table.items())[:args.scaffold_limit])
        fresh_outputs(OUT / "scaffold.exe")
        log, seconds, code = link(present, table, tag="scaffold")
        unexplained_exit(code, log, OUT / "scaffold.exe")
        crashed = FATAL.search(log)
        after, after_detail, after_dup_kinds, _ = classify(log, rows)
        census["scaffold"] = {"aliases": len(table), "seconds": seconds,
                              "crashed": crashed.group(0).strip() if crashed else None,
                              "unresolved_classes": dict(after), "duplicate_classes": dict(after_dup_kinds),
                              "unresolved": {n: e for n, e in after_detail.items()
                                             if e["kind"] in ("alias", "dump", "pinned-elsewhere")}}
    OUT.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(census, indent=1), encoding="utf-8")
    report(census)
    if census_state(present) != state:
        raise SystemExit("link_census: compiler inputs, tools or objects changed after the link; nothing recorded"
                         f" ({moved(state, census_state(present))})")
    if args.history:
        # record() proves every object current again: the links take minutes.
        record(census, rows)
    elif args.measure:
        measure(census, rows, present, final_log(census), state, sources)
    _stage_line("total", time.monotonic() - run_started)
    prune_memo()
    return 0


DRY_OUT = ROOT / "build" / "link_census_dry"


def use_dry_outputs(directory):
    """Point every output of a --history census under `directory` (census_rebaseline's
    load_old redirects the same names): census.json, the logs, link_status.csv, the
    history (a copy of reverse/'s, which the row is appended to) and the link index.
    The last real census's log seeds the selection link's prediction, as it would
    in a real census."""
    global OUT, STATUS, HISTORY, UNREFERENCED_COPIES, SELECTED, DUPLICATES, ALIASED, SELECTION
    import link_check
    real = OUT
    directory.mkdir(parents=True, exist_ok=True)
    if not (directory / "census.log").exists() and (real / "census.log").exists():
        (directory / "census.log").write_bytes((real / "census.log").read_bytes())
    (directory / HISTORY.name).write_bytes(HISTORY.read_bytes() if HISTORY.exists() else b"")
    OUT, HISTORY, STATUS = directory, directory / HISTORY.name, directory / STATUS.name
    UNREFERENCED_COPIES, SELECTED, DUPLICATES, ALIASED, SELECTION = (
        directory / path.name for path in (UNREFERENCED_COPIES, SELECTED, DUPLICATES, ALIASED, SELECTION))
    link_check.INDEX = directory / link_check.INDEX.name


_REPLAY = {}


def replayed_link(present):
    """--dry --replay: (log, seconds) of the dry census's plain link of these
    very objects (census.json's objects_digest, census.rsp's list and order),
    which a link of them would write again; selection_link then reuses its
    /MAP the same way. Not a census: only DRY_OUT is ever replayed."""
    if OUT != DRY_OUT:
        raise SystemExit("link_census: --replay only reads a --dry census's outputs")
    try:
        previous = json.loads((OUT / "census.json").read_text(encoding="utf-8"))
        log = (OUT / "census.log").read_text(encoding="utf-8")
        rsp = (OUT / "census.rsp").read_text(encoding="utf-8")
    except (OSError, ValueError) as exc:
        raise SystemExit(f"link_census: nothing to replay ({exc}); run --dry first")
    if previous.get("objects_digest") != objects_digest(present) or rsp != _rsp_text(present):
        raise SystemExit("link_census: the last dry census linked other objects; run --dry first")
    _REPLAY["census"] = True
    print("link_census: REPLAY of the last dry census's links (not a census)", file=sys.stderr, flush=True)
    return log, previous.get("seconds", 0)


def _replayed_map(present, missing_names):
    stubs = stub_object(missing_names, OUT / "replay_stubs.obj")
    try:
        same = (stubs.read_bytes() == (OUT / "selected_stubs.obj").read_bytes()
                and (OUT / "selected.rsp").read_text(encoding="utf-8") == _rsp_text(present))
        text = (OUT / "selected.map").read_text(encoding="latin-1")
    except OSError as exc:
        raise SystemExit(f"link_census: no /MAP to replay ({exc}); run --dry first")
    finally:
        stubs.unlink(missing_ok=True)
    if not same or not text:
        raise SystemExit("link_census: the last dry census's /MAP link had other inputs; run --dry first")
    return text


def measure(census, rows, present, log, state, sources):
    """LINKED figures and the link index for this census, history untouched.

    Published under record()'s rule: nothing is written unless the inputs,
    tools and objects the plain link saw still hold after the selection link
    and the judgment. It once published straight away, so a commit landing
    during the selection link stamped the new tree's verdicts with the old
    census commit.
    """
    def guard(when):
        if census_state(present) != state or stale_objects(present, sources):
            raise SystemExit(f"link_census: compiler inputs, tools or objects changed {when}; nothing written"
                             f" ({moved(state, census_state(present))})")
    started = time.time()
    kept = selected_definitions(selection_link(present, log))
    print(f"link_census: selection (/MAP) link {time.time() - started:.0f}s after the plain link", flush=True)
    guard("during the selection link")
    clean, files, blocking, clean_prev, prepared = write_status(
        log, rows, present, {"date": census["when"], "commit": census["commit"]}, kept, publish=False)
    guard("during judgment")
    prepared["accept"]()
    print(json.dumps({"files": files, "files_linked": len(clean), "files_linked_prev_rule": len(clean_prev),
                      "blocking": blocking, **linked_figures(clean)}), flush=True)


def selected_main():
    """--selected: the selection report for the last recorded census, on its
    own tree, from a fresh /MAP link of the same objects."""
    history = read_history()
    changed = subprocess.run(["git", "diff", "--quiet", history[-1]["commit"] if history else "HEAD", "--",
                              *CENSUS_INPUTS],
                             cwd=ROOT).returncode if history else 1
    if changed:
        raise SystemExit("link_census: --selected needs the last census's sources and ledger "
                         f"({history[-1]['commit'] if history else 'no census'}); this tree differs")
    rows = ledger()
    verify_data_objects()
    present, missing = objects(rows)
    if missing:
        raise SystemExit(f"link_census: {len(missing):,} objects missing")
    sources = _object_sources(rows)
    stale = stale_objects(present, sources)
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} objects are not current for their source, "
                         f"e.g. {stale[0].name}")
    log = final_log(None)  # the census's own link says which names nothing defines
    map_text = selection_link(present, log)
    if subprocess.run(["git", "diff", "--quiet", history[-1]["commit"], "--", *CENSUS_INPUTS],
                      cwd=ROOT).returncode or stale_objects(present, sources):
        raise SystemExit("link_census: source inputs or objects changed during the selection link; rerun the census")
    with STATUS.open(newline="", encoding="utf-8") as handle:
        clean = {row["source"] for row in csv.DictReader(handle) if row["linked"] == "yes"}
    clean_objects = {build.row_object(row).name for row in rows if row["source"] in clean}
    summary, bad, owner_misses = selection_report(present, read_facts(present, rows), rows, clean_objects,
                                    map_text, log)
    import link_check
    sizes = link_check.source_bytes(clean)
    by_object = {build.row_object(row).name: row["source"] for row in rows if row["source"] in clean}
    wrong = {obj for obj, found in bad.items() if any(verdict == "wrong" for _, verdict in found)}
    summary["linked_bytes_on_wrong_selected_copy"] = sum(sizes.get(by_object.get(obj), 0) for obj in wrong)
    summary["linked_bytes_on_unproven_selected_copy"] = sum(sizes.get(by_object.get(obj), 0) for obj in bad)
    summary["linked_bytes_on_non_owner_duplicate"] = sum(sizes.get(by_object.get(obj), 0) for obj in owner_misses)
    summary["linked_bytes"] = sum(sizes.values())
    SELECTION.write_text(json.dumps(summary, indent=1), encoding="utf-8")
    print_selection(summary)
    return 0


def _unresolved_names(log):
    """Names a link log reports unresolved; a path reads the log file."""
    if isinstance(log, Path):
        try:
            log = log.read_text(encoding="utf-8", errors="replace")
        except OSError:
            return set()
    return {found.group(1) or found.group(2) for found in map(UNRESOLVED.search, log.splitlines()) if found}


_PRESELECTION = {}


def _start_preselection(present, names):
    """Start the selection link on `names` (a set, or a callable returning
    one: it runs in the link's thread, beside the plain link)."""
    import threading

    def work():
        try:
            found = set(names() if callable(names) else names)
            if not found:
                return  # nothing to stub: selection_link relinks on the plain link's names
            _PRESELECTION["names"] = found
            _PRESELECTION["map"] = _selection_map(present, found)
        except SystemExit as error:
            _PRESELECTION["error"] = error
    _PRESELECTION.clear()
    _PRESELECTION.update(names=None, objects=list(present), thread=threading.Thread(target=work, daemon=True))
    _PRESELECTION["thread"].start()


ENTRY_SYMBOL = "_WinMainCRTStartup"  # link()'s /ENTRY:WinMainCRTStartup, as link.exe decorates it
LINKER_DEFINED = frozenset({"___ImageBase"})  # link.exe defines __ImageBase itself
IMPORT_PREFIX = "__imp_"  # __imp_X binds to a locally defined X (LNK4217/LNK4049), not an error


def object_symbols(obj, data=None):
    """(defined, referenced, weak externals [(name, default)], /alternatename
    {alias: target}, /INCLUDE: names) of one object: what predicted_unresolved
    needs from its symbol table and directives."""
    import link_check
    data = obj.read_bytes() if data is None else data
    defined, referenced = set(), set()
    for symbol in _coff_symbols(data):
        if symbol["storage"] != EXTERNAL:
            continue
        if symbol["section"] == 0 and symbol["value"] == 0:
            referenced.add(symbol["name"])
        else:  # a section's, an absolute or a COMMON definition
            defined.add(symbol["name"])
    import struct
    includes = set()
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    for index in range(count):
        header = 20 + optional + index * 40
        if data[header:header + 8].rstrip(b"\0") == b".drectve":
            size, pointer = struct.unpack_from("<II", data, header + 16)
            text = data[pointer:pointer + size].decode("latin-1")
            includes.update(found.strip('"') for found in re.findall(r"/INCLUDE:(\"[^\"]+\"|[^\s,=]+)", text, re.I))
    return defined, referenced, _weak_externals(data), _alternate_names(data), includes


def _alternate_names(data):
    """link_check.alternate_names of an object's bytes."""
    import struct
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    found = {}
    for i in range(count):
        header = 20 + optional + i * 40
        if data[header:header + 8].rstrip(b"\0") != b".drectve":
            continue
        size, pointer = struct.unpack_from("<II", data, header + 16)
        text = data[pointer:pointer + size].decode("latin-1")
        for alias, target in re.findall(r"/alternatename:([^=\s]+)=(\S+)", text, re.I):
            found.setdefault(alias.strip('"'), target.strip('"'))
    return found


@_timed('unresolved-name prediction')
def predicted_unresolved(present):
    """The names the plain link of `present` should report unresolved: every
    name an object references, includes or declares weak (and the entry
    point) that no object defines, after weak externals' defaults and
    /alternatename targets; __imp_X resolves when X does, and __ImageBase
    always (link.exe defines it). Only a prediction, to start the selection link
    beside the plain link (selection_link uses that map only when the plain
    link's log names exactly these); an unreadable object predicts nothing."""
    defined, referenced, weak, alias = set(), {ENTRY_SYMBOL}, {}, {}
    try:
        for obj, (names, refs, weaks, alternates, includes) in zip(present, memo_map("symbols", present, parallel=False)):
            defined |= names
            referenced |= refs | includes
            for name, default in weaks:
                weak.setdefault(name, default)
            for name, target in alternates.items():
                alias.setdefault(name, target)
    except Exception:  # noqa: BLE001 -- a prediction only: any doubt predicts nothing
        return set()

    def resolves(name, seen=frozenset()):
        if name in defined or name in LINKER_DEFINED:
            return True
        seen = seen | {name}
        local = name[len(IMPORT_PREFIX):] if name.startswith(IMPORT_PREFIX) else None
        return any(target is not None and target not in seen and resolves(target, seen)
                   for target in (weak.get(name), alias.get(name), local))
    return {name for name in referenced | set(weak) if not resolves(name)}


@_timed('selection link (wait or relink)')
def selection_link(present, log):
    """The /MAP text of a relink of `present` in which every name the plain
    link (`log`) left unresolved is defined in one stub section, so the link
    finishes and the map says which definition it kept for every name.
    /OPT:NOREF keeps every selected COMDAT in the map."""
    missing_names = _unresolved_names(log)
    if _REPLAY:
        return _replayed_map(present, missing_names)
    if _PRESELECTION:
        _PRESELECTION["thread"].join()
        if (_PRESELECTION["names"] == missing_names and _PRESELECTION["objects"] == list(present)
                and "map" in _PRESELECTION):
            print("link_census: selection link ran in parallel on the same unresolved names", flush=True)
            return _PRESELECTION["map"]
        print("link_census: unresolved names moved since the last census; relinking for the map", flush=True)
    return _selection_map(present, missing_names)


def _selection_map(present, missing_names):
    stubs = stub_object(missing_names, OUT / "selected_stubs.obj")
    link_map = OUT / "selected.map"
    fresh_outputs(link_map, OUT / "selected.exe")  # a failed link leaves an empty map, never last run's
    relink, _, code = link(present, tag="selected", extra=[stubs],
                           options=["/OPT:NOREF", f"/MAP:{_arg(link_map)}"])
    unexplained_exit(code, relink, OUT / "selected.exe")  # a crash can leave a partial map
    if FATAL.search(relink) or not link_map.exists() or not link_map.stat().st_size:
        raise SystemExit(f"link_census: the /MAP link failed; see {_arg(OUT / 'selected.log')}")
    return link_map.read_text(encoding="latin-1")


def _object_sources(rows):
    """{object: source} for every compiled (C/C++/MASM) row."""
    sources = {build.row_object(row): ROOT / row["source"] for row in rows
               if Path(row["source"]).suffix.lower() in (".c", ".cpp", ".asm")}
    sources.update({build.obj_path(source): source for source in data_sources()})
    return sources


STATUS = ROOT / "reverse/link_status.csv"
STATUS_FIELDS = ["source", "linked", "unresolved", "duplicates", "comdat_losers", "addresses", "wrong_selected"]


def final_log(census):
    """The plain link's log. The alias scaffold's link resolves a call through
    a generated weak alias when the called name and the defining name differ;
    that is a naming defect to fix, not a name that resolves."""
    return (OUT / "census.log").read_text(encoding="utf-8", errors="replace")


def library_symbols(path):
    """Public names a COFF archive defines, from its first linker member."""
    import struct
    data = path.read_bytes()
    size = int(data[56:66].decode("ascii").strip())
    body = data[68:68 + size]
    count = struct.unpack(">I", body[:4])[0]
    return {name.decode("latin-1") for name in body[4 + 4 * count:].split(b"\0")[:count]}


def _retail_import_entries():
    """[(dll, name, slot rva)] from retail's import table (every entry is
    imported by name)."""
    import pefile
    pe = pefile.PE(data=build.EXE.read_bytes(), fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    return [(dll.dll.decode("latin-1"), entry.name.decode("latin-1"), entry.address - pe.OPTIONAL_HEADER.ImageBase)
            for dll in pe.DIRECTORY_ENTRY_IMPORT for entry in dll.imports if entry.name]


def retail_imports():
    """{name: {dll, lower case}} for every function retail's import table
    lists (every entry is imported by name)."""
    found = collections.defaultdict(set)
    for dll, name, _ in _retail_import_entries():
        found[name].add(dll.lower())
    return dict(found)


def retail_import_slots():
    """[(name, IAT slot rva)]: where retail's `call [__imp_name]` reads."""
    return [(name, slot) for _, name, slot in _retail_import_entries()]


def _undecorate(name):
    """`_socket@12` -> `socket`: one decoration underscore and a stdcall @N off."""
    return re.sub(r"@\d+$", "", name[1:] if name.startswith("_") else name)


def library_import_thunks(path):
    """{call stub: {(dll, imported name)}} for the short import objects of CODE
    type an import library holds: `_strcpy` in msvcrt.lib forwards to
    MSVCR71's strcpy, `_socket@12` in WSock32.Lib to WSOCK32's socket. Such a
    name resolves in the real link only if the image imports that function.
    The imported name follows the object's name type (IMPORT_OBJECT_NAME,
    _NO_PREFIX, _UNDECORATE); an import by ordinal names its function by the
    undecorated stub name."""
    import struct
    data, at, thunks = path.read_bytes(), 8, collections.defaultdict(set)
    while at + 60 <= len(data):
        try:
            size = int(data[at + 48:at + 58].decode("ascii").strip())
        except ValueError:
            break
        body = data[at + 60:at + 60 + size]
        if body[:4] == b"\0\0\xff\xff" and len(body) > 20:
            kind = struct.unpack_from("<H", body, 18)[0]
            if kind & 3 == 0:  # IMPORT_OBJECT_CODE
                end = body.index(b"\0", 20)
                symbol = body[20:end].decode("latin-1")
                dll = body[end + 1:body.index(b"\0", end + 1)].decode("latin-1").lower()
                name_type = (kind >> 2) & 7
                if name_type == 1:
                    name = symbol
                elif name_type == 2:
                    name = symbol[1:] if symbol[:1] in "?@_" else symbol
                else:
                    name = _undecorate(symbol).split("@")[0] if name_type == 3 else _undecorate(symbol)
                thunks[symbol].add((dll, name))
        at += 60 + size + (size & 1)
    return thunks


def import_stubs():
    """Every call stub the committed toolchain's import libraries define:
    Vc7/lib (msvcrt.lib, kernel32.lib) and Vc7/PlatformSDK/Lib (WSock32.Lib,
    WS2_32.Lib, User32.Lib, ...). Static libraries in those directories hold
    no short import objects and add nothing."""
    root = build.vc71_root() / "Vc7"
    stubs = collections.defaultdict(set)
    for directory in (root / "lib", root / "PlatformSDK" / "Lib"):
        for path in sorted(directory.glob("*")):
            if path.suffix.lower() == ".lib" and path.read_bytes()[:8] == b"!<arch>\n":
                for symbol, targets in library_import_thunks(path).items():
                    stubs[symbol] |= targets
    return dict(stubs)


def excused(symbol, runtime, imported, thunks=None):
    """True for a name the real link resolves without this tree defining it.

    An __imp_ name only when retail imports that function: strip the prefix,
    one decoration underscore and a stdcall @N (__imp__GetModuleFileNameA@12,
    __imp___iob); MSVCR71 exports a few C++ names mangled, so a ?name must
    match as is (??1exception@@UAE@XZ). An address-named slot or a name
    retail does not import is a declaration defect. A call stub an import
    library in the toolchain defines (`_strcpy` in msvcrt.lib, `_socket@12` in
    WSock32.Lib, import_stubs()) counts only when retail imports that function
    from that DLL: `_htons@4` is a WSock32.Lib stub, but retail imports only
    htonl and ntohs, so a direct htons call stays a defect. Any other name
    only when msvcrt.lib (MSVCR71's import library and CRT statics:
    __except_list, __fltused) defines it. `imported` is retail_imports().
    """
    if thunks and symbol in thunks:  # a call stub: only as good as the import behind it
        return any(dll in imported.get(name, ()) for dll, name in thunks[symbol])
    if symbol.startswith("__imp_"):
        name = symbol[len("__imp_"):]
        if name in imported or name.startswith("?"):
            return name in imported  # Miles exports decorated: _AIL_startup@0
        return re.sub(r"@\d+$", "", name[1:] if name.startswith("_") else name) in imported
    return symbol in runtime


def write_status(log, rows, present, meta, kept, publish=True, previous_rules=None):
    """One row per C/C++ source: does its object link cleanly on its own terms?

    Per file, not per program: a clean file may still call into one that is
    not. Read from the full plain-link log, not census.json, which keeps five
    referrers per name. The census links /NODEFAULTLIB, so two kinds of
    unresolved name are not held against a file: __imp_ entries and call stubs
    (`_socket@12`) retail imports, which want the import libraries, and names msvcrt.lib defines (retail imports
    MSVCR71.dll, and the ledger's CRT rows are msvcrt.lib members), which the
    real link searches by default -- __except_list alone is referenced by 3,088
    objects. See excused() for exactly which names. A duplicate counts against both definers, since the log cannot say
    which copy is wrong. A COMDAT copy that is not retail's body counts against
    its object (comdat_losers: retail truth where the symbol has a retail
    address, except, since retail-truth-3, when another object supplies the
    retail-proven copy and, since retail-truth-4, for an unproven copy when the
    copy the link keeps is proven retail's; else the copy link.exe keeps, the
    first in link order; since
    retail-truth-2 no copy of a name with no retail address that nothing the
    link keeps references loses: keep_rule, though such copies that differ
    from the majority are still listed, as a diagnostic only, in
    UNREFERENCED_COPIES and the index: unreferenced_differs). Any hard-coded image address counts too
    (link_debt.addresses): it links, but only while nothing moves.

    And since 2026-09-29 (wrong_selected), a file is not linked when any name
    it defines or references resolves, in the actual link, to a definition
    proven not retail's: the COMDAT copy link.exe kept is proven wrong, or the
    kept one of several definitions is not the ledger owner's
    (judge_selected). `kept` is the /MAP's {name: object}
    (selected_definitions of selection_link). A name with no retail address or
    owner is not held against anyone; the files that depend on such a choice
    are counted (`unknown_only`).

    Returns (clean, files, blocking names, clean under the rule before
    wrong_selected, stats); stats["clean_previous_rules"] is the clean set
    under retail-truth-3's keep rule (every unproven copy that differs from the proven one charged). It also writes build/link_census/link_index.pkl, which tools/link_check.py
    reads to check one file in seconds (`meta` names the census). With
    publish=False neither file is written until stats["accept"]() is called,
    so record() can refuse a run whose inputs moved without leaving a status
    that no history row describes.
    """
    import link_debt
    started = time.monotonic()
    crt = build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib"
    runtime, thunks = library_symbols(crt), import_stubs()
    imported = retail_imports()
    if present is None:
        present, _ = objects(rows)
    _stage_line("write_status: runtime and imports", time.monotonic() - started)
    stats, previous_stats = {}, {}
    facts = read_facts(present, rows)
    started = time.monotonic()
    owners = ledger_owners(rows)
    _stage_line("write_status: ledger owners", time.monotonic() - started)
    references = read_references(present)
    edges, referenced = link_references(present, facts, owners, references)
    losers = comdat_losers(present, rows, stats, facts, referenced)
    # retail-truth-3's keep rule (unless an in-process re-baseline names
    # another KEEP_RULE_VARIANTS entry) differs from RULES' only in
    # keep_rule's exemptions: the report below, and census_rebaseline.py's
    # in-process figures.
    previous_losers = comdat_losers(present, rows, previous_stats, facts, referenced,
                                    **KEEP_RULE_VARIANTS[previous_rules or RETAIL_TRUTH_3])
    differs = unreferenced_differs(present, facts, referenced)
    results, exceptions = selection_verdicts(present, facts, owners, kept)
    wrong_selected, unknown_selected = {}, {}
    for obj, fact in zip(present, facts):
        touched = touched_names(fact)
        wrong_selected[obj.name] = sorted(name for name in touched if results.get(name) == "wrong")
        unknown_selected[obj.name] = sum(1 for name in touched if results.get(name) == "unknown")
    print(f"link_census: selected definitions: {sum(1 for r in results.values() if r == 'wrong'):,} names proven "
          f"wrong, {sum(1 for r in results.values() if r == 'unknown'):,} unproven, "
          f"{sum(1 for r in results.values() if r == 'ok'):,} proven; {len(exceptions):,} not the first in link order")
    print(f"link_census: COMDAT keeper: {stats.get('symbols_retail', 0):,} symbols judged by retail truth "
          f"({stats.get('losers_retail', 0):,} losing copies), {stats.get('symbols_first', 0):,} with no retail "
          f"address by link order ({stats.get('losers_first', 0):,} losing copies), "
          f"{stats.get('symbols_unreferenced', 0):,} with no retail address that nothing the link keeps references; "
          f"{previous_stats.get('losers_retail', 0) - stats.get('losers_retail', 0):,} unproven copies lose "
          f"nothing because the copy the link keeps is retail's ({RETAIL_TRUTH_3} charged them)")
    unresolved = collections.defaultdict(set)
    duplicates = collections.defaultdict(set)
    # An /alternatename alias whose target is an excused name: /NODEFAULTLIB
    # leaves the target unresolved, so link.exe reports the alias, but the real
    # link resolves the target from the import library and the alias with it
    # (2026-10-04: ten units bind ?_CxxThrowException@@YGXPAX0@Z, the spelling
    # VC7.1's predeclared C-linkage helper forces on a (void *, void *)
    # declaration, to __CxxThrowException@8). Chains are followed, as link.exe does.
    import link_check
    started = time.monotonic()
    aliases = collections.defaultdict(set)
    for obj in present:
        for alias, target in link_check.alternate_names(obj).items():
            aliases[alias].add(target)

    def excused_through(symbol, seen=frozenset()):
        if excused(symbol, runtime, imported, thunks):
            return True
        seen = seen | {symbol}
        return any(target not in seen and excused_through(target, seen) for target in aliases.get(symbol, ()))

    for line in log.splitlines():
        found = UNRESOLVED.search(line)
        if found:
            symbol = found.group(1) or found.group(2)
            referrer = REFERRER.match(line)
            if referrer and not excused_through(symbol):
                unresolved[Path(referrer.group(1)).name].add(symbol)
            continue
        found = DUPLICATE.match(line)
        if found:
            symbol = found.group(2) or found.group(3)
            duplicates[Path(found.group(1)).name].add(symbol)
            duplicates[Path(found.group(4)).name].add(symbol)
    out, blockers, clean_prev, clean_previous_rules, unknown_only = {}, {}, set(), set(), set()
    # A data-only source is a file like any other; it owns no code, so linking
    # it adds no LINKED bytes, only the definitions other files resolve to.
    for row, object_of in [(row, build.row_object) for row in rows] + [(row, data_object) for row in data_ledger()]:
        source = row["source"]
        import progress
        reviewed_asm = (Path(source).suffix.lower() == '.asm'
                        and progress.source_lane(source, row.get('notes', ''), False) == 'assembly')
        if source in out or (Path(source).suffix.lower() not in (".c", ".cpp") and not reviewed_asm):
            continue
        obj = object_of(row).name
        if reviewed_asm and obj not in {p.name for p in present}:
            continue  # no assessment or credit without a current linked object
        try:
            text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        counts = (len(unresolved.get(obj, ())), len(duplicates.get(obj, ())), len(losers.get(obj, ())),
                  len(link_debt.addresses(text, source)), len(wrong_selected.get(obj, ())))
        out[source] = {"source": source, "linked": "no" if any(counts) else "yes",
                       **dict(zip(STATUS_FIELDS[2:], counts))}
        if not any(counts[:4]):
            clean_prev.add(source)
        if not any(counts[:2] + (len(previous_losers.get(obj, ())),) + counts[3:]):
            clean_previous_rules.add(source)
        if not any(counts) and unknown_selected.get(obj):
            unknown_only.add(source)
        blockers[source] = {"object": obj, "linked": not any(counts), "unresolved": sorted(unresolved.get(obj, ())),
                            "duplicates": sorted(duplicates.get(obj, ())), "losers": sorted(losers.get(obj, ())),
                            "addresses": counts[3], "wrong_selected": wrong_selected.get(obj, []),
                            "unreferenced_differs": differs.get(obj, [])}
    _stage_line("write_status: log and per-source rows", time.monotonic() - started)
    clean = {source for source, r in out.items() if r["linked"] == "yes"}
    stale = {source: entry["unreferenced_differs"] for source, entry in blockers.items()
             if entry["unreferenced_differs"]}
    stale_copies, stale_units = unreferenced_summary(stale)
    print(f"link_census: diagnostic (no blocker): differing copies the unreferenced rule exempts, by kind: "
          + ", ".join(f"{kind} {stale_copies[kind]:,} in {stale_units[kind]:,} units" for kind in sorted(stale_copies))
          + (" (layout-like: a stale private class view?)" if stale_copies.get("layout") else ""))

    def accept():
        started = time.monotonic()
        temp = STATUS.with_suffix(".csv.tmp")
        with temp.open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, STATUS_FIELDS, lineterminator="\n")
            writer.writeheader()
            writer.writerows(out[s] for s in sorted(out))
        temp.replace(STATUS)
        UNREFERENCED_COPIES.parent.mkdir(parents=True, exist_ok=True)
        temp = UNREFERENCED_COPIES.with_suffix(".json.tmp")
        temp.write_text(json.dumps({"meta": meta or {}, "rules": RULES, "layout_diff_bytes": LAYOUT_DIFF_BYTES,
                                    "copies": stale_copies, "units_by_kind": stale_units, "units": stale},
                                   indent=1, sort_keys=True), encoding="utf-8")
        temp.replace(UNREFERENCED_COPIES)
        import link_check
        link_check.write_index(present, facts, blockers, {"runtime": runtime, "imported": imported, "stubs": thunks},
                               meta or {}, {"exceptions": exceptions, "owners": dict(owners)},
                               references={"edges": edges, "referenced": referenced})
        _stage_line("write_status: status, copies and link index written", time.monotonic() - started)
        print(f"link_census: wrote {STATUS.relative_to(ROOT).as_posix()} ({len(clean):,} of {len(out):,} sources "
              f"link cleanly; {len(clean_prev):,} before wrong_selected; {len(unknown_only):,} of the clean ones use "
              "a selected definition nothing proves or disproves)")
    if publish:
        accept()
    blocking = set().union(*unresolved.values()) if unresolved else set()
    return clean, len(out), len(blocking), clean_prev, {"unknown_only": unknown_only, "accept": accept,
                                                         "clean_previous_rules": clean_previous_rules}


def linked_split(clean):
    """progress.py's lane split restricted to sources that link cleanly,
    measured on this tree: the one the census just linked."""
    import progress
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    return progress.real_split(matched, notes, start, size, naked, keep=lambda key, source: source in clean)


def linked_figures(clean):
    """Preserve legacy figures and store inclusive executable-game coverage.

    New numerator/denominator fields include generated code and assessed
    reviewed assembly, exclude libraries/data, and share this census tree.
    """
    import progress
    split = linked_split(clean)
    start, size = progress.retail_text()
    _, total = progress.real_code_denominator(start, size)
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    full = progress.real_split(matched, notes, start, size, progress.naked_cpp_rows_at(matched, None))
    return {"linked_bytes": progress.decompiled(split), "linked_authored": split["authored"],
            "game_code": progress.game_code(full, total),
            **progress.linked_game_coverage(matched, notes,
                progress.naked_cpp_rows_at(matched, None), clean, start, size,
                progress.text_data_at(None))}


def head():
    return subprocess.run(["git", "rev-parse", "--short=10", "HEAD"], cwd=ROOT,
                          capture_output=True, text=True, check=True).stdout.strip()


def utc_now():
    """A census's `date`: UTC, minutes, the format every row uses."""
    return time.strftime("%Y-%m-%d %H:%M", time.gmtime())


_INPUT_RECEIPTS = None


def input_receipts():
    """Only the recorded census's fresh proof, never a reusable build cache."""
    global _INPUT_RECEIPTS
    if _INPUT_RECEIPTS is not None:
        return _INPUT_RECEIPTS
    import census_receipts
    try:
        run = json.loads((OUT / "census.json").read_text()).get("compile_input_run")
    except (OSError, ValueError, TypeError, AttributeError):
        return None
    _INPUT_RECEIPTS = census_receipts.Receipts.load(OUT / "compile_inputs.json", run)
    return _INPUT_RECEIPTS


def object_current(source, obj, *, inventory_cache=None, allow_fresh=True):
    """Open-BFME-1's proof: the full gate's receipt including the include
    search inventory (a header newly added to an earlier search directory
    shadows a recorded one without changing a recorded byte), else this
    census's own witnessed compile (census_receipts). An object with no
    receipt is never current, however new it is: its timestamp proves
    nothing about the source and headers it was compiled from."""
    if build.compile_is_current(source, obj, strict=True, inventory_cache=inventory_cache):
        return True
    if not allow_fresh:
        return False
    receipts = input_receipts()
    return receipts is not None and receipts.current(source, obj)


@_timed('currency proof (stale_objects)')
def _receipt_chunk(pairs):
    """([object without a census-grade receipt], include inventory snapshot)
    for one share of stale_objects' [(object, source)]."""
    inventory_cache = {}
    stale = [obj for obj, source in pairs
             if not object_current(source, obj, inventory_cache=inventory_cache, allow_fresh=False)]
    return stale, inventory_cache


def stale_objects(present, sources):
    """The objects in `present` that are not current for their source
    (object_current); objects with no source (library members) are taken
    as extracted. The include inventory is one shared snapshot, which must
    not move while it is used.

    The receipt check is per-object Python (~55 ms each on srv1, mostly
    compiler_command and the include inventory), so with BUILD_POOL > 1 it is
    split across that many processes, as build.stale_sources splits the
    compile's: each share takes its own inventory snapshot, and the shares
    must agree on every directory they both read (one that moved between
    them refuses, as one moving during a single pass does). Same answer,
    same order."""
    pairs = [(obj, sources[obj]) for obj in present if obj in sources]
    workers = build._pool_size()
    if workers <= 1 or len(pairs) < 200:
        uncached, inventory_cache = _receipt_chunk(pairs)
    else:
        with concurrent.futures.ProcessPoolExecutor(workers) as pool:
            parts = list(pool.map(_receipt_chunk, [pairs[i::workers] for i in range(workers)]))
        inventory_cache = {}
        for _, snapshot in parts:
            for root, digest in snapshot.items():
                if inventory_cache.setdefault(root, digest) != digest:
                    raise SystemExit("link_census: include search directories changed while checking objects; retry")
        missing = {obj for stale, _ in parts for obj in stale}
        uncached = [obj for obj, _ in pairs if obj in missing]
    if not build._inventory_cache_still_current(inventory_cache):
        raise SystemExit("link_census: include search directories changed while checking objects; retry")
    receipts = input_receipts()
    if receipts is None or not uncached:
        return uncached

    def check(obj):
        return receipts.current(sources[obj], obj)
    # The fresh proof runs cl /E, so honor BUILD_POOL and bound Wine fanout.
    workers = min(8, build._pool_size(), max(1, len(uncached)))
    with concurrent.futures.ThreadPoolExecutor(workers) as pool:
        stale = [obj for obj, current in zip(uncached, pool.map(check, uncached)) if not current]
    if not build._inventory_cache_still_current(inventory_cache):
        raise SystemExit("link_census: include search directories changed while checking objects; retry")
    return stale


def census_inputs_state():
    """HEAD and the uncommitted diff of every compiler input: equal before
    and after a link when nothing changed the tree under it."""
    commit = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True).stdout
    diff = subprocess.run(["git", "diff", "HEAD", "--", *CENSUS_INPUTS], cwd=ROOT, capture_output=True,
                          text=True, errors="replace").stdout
    return commit, diff


def tools_digest():
    """The census's own code (TOOL_FILES), as run."""
    digest = hashlib.sha256()
    for name in TOOL_FILES:
        digest.update(name.encode() + b"\0")
        digest.update((ROOT / "tools" / name).read_bytes())
    return digest.hexdigest()


def object_stamps(present):
    """Every object's identity: any write, rename over or replacement moves
    its inode, size, mtime or ctime."""
    stamps = {}
    for obj in present:
        try:
            st = os.stat(obj)
        except OSError:
            stamps[str(obj)] = None
            continue
        stamps[str(obj)] = (st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)
    return stamps


@_timed('objects_digest')
def objects_digest(present):
    """The objects' bytes, one digest (census_rebaseline compares two runs)."""
    digest = hashlib.sha256()
    for obj in sorted(present, key=lambda o: Path(o).name):
        digest.update(Path(obj).name.encode() + b"\0")  # build.obj_path names are unique
        digest.update(hashlib.sha256(Path(obj).read_bytes()).digest())
    return digest.hexdigest()


def moved(before, after):
    """Which census_state components differ -- what an abort has to name."""
    return ", ".join(key for key in before if before[key] != after.get(key)) or "objects went stale"


@_timed('census_state')
def census_state(present):
    """What must hold still from the first currency check to the record: HEAD
    and the uncommitted diff of every compiler input, the census tools and
    every object (object_stamps). Currency is proven at both ends of the run
    (stale_objects); this proves nothing moved in between, during the links
    and while object facts were read."""
    return {"inputs": census_inputs_state(), "tools": tools_digest(), "objects": object_stamps(present)}


def record(census, rows, rerun=False, rebaseline=None):
    """Write link_status.csv and the census's history row, LINKED included.

    LINKED is stored, not recomputed later: measured on the tree that was
    linked, it stays fixed until the next census instead of decaying with
    every edit made since. Nothing is recorded when an object is missing (a
    file the link never saw would read as clean) or not proven current (a
    failed compile leaves last week's object; an object with no receipt proves
    nothing), when game sources or the ledger have uncommitted edits, or when
    the objects, compiler inputs or tools moved during the run. --status (rerun)
    only runs on the census's own commit, so a log is never paired with
    another tree's ledger or sources.

    The row carries `rules` (RULES) and `prev_rules`: RULES_NO_WRONG_SELECTED
    for an ordinary row, whose *_prev_rule figures are this census without
    wrong_selected. `rebaseline` (census_rebaseline.py only) is the previous
    rules' figures for the same objects: the one row where the rules change.
    REBASELINE_IN_PROCESS measures the history's last rules in this very
    judgment (the same objects, log and /MAP: write_status'
    clean_previous_rules), which is possible for IN_PROCESS_RULES: they differ
    from RULES only in keep_rule's exemptions.
    """
    in_process = rebaseline is REBASELINE_IN_PROCESS
    previous_rules = None
    if in_process:
        last = read_history()
        previous_rules = row_rules(last[-1]) if last else None
        if previous_rules not in IN_PROCESS_RULES and previous_rules != RULES:  # RULES: check_history_rules says so
            raise SystemExit(f"link_census: the history's last row is {previous_rules}; only "
                             f"{', '.join(IN_PROCESS_RULES)} can be measured in the same judgment")
        rebaseline = {"rules": previous_rules}
    verify_data_objects()
    if census["missing"]:
        raise SystemExit(f"link_census: {census['missing']:,} objects were missing from the link; "
                         "nothing recorded (build everything and rerun)")
    dirty = subprocess.run(["git", "status", "--porcelain", "-uno", "--", *CENSUS_INPUTS],
                           cwd=ROOT, capture_output=True, text=True).stdout
    if dirty.strip():
        raise SystemExit(f"link_census: uncommitted source or ledger edits; the census would not match its commit:\n{dirty}")
    # cl.exe leaves the previous .obj in place when a compile fails, and the
    # full build stops at the first failure: an object that is not current for
    # its source, recorded headers and compile command is last week's code
    # under this week's ledger.
    present, missing = objects(rows)
    if missing:  # census.json's count is the census's; an object gone since then would read as clean
        raise SystemExit(f"link_census: {len(missing):,} objects are missing now, e.g. {missing[0].name}; "
                         "nothing recorded")
    history = read_history()
    commit = head()
    check_history_rules(history, census, rerun=rerun, rebaseline=rebaseline)
    by_object = _object_sources(rows)
    state = census_state(present)
    stale = stale_objects(present, by_object)
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} objects are not current for their source (a failed compile?), "
                         f"e.g. {stale[0].name}; nothing recorded")
    if not rerun:
        # A new row is published only for the commit, tools and objects the
        # census linked, all re-read now (missing provenance refuses).
        if census.get("commit") != commit:
            raise SystemExit(f"link_census: this census linked {census.get('commit')!r} but HEAD is {commit}; "
                             "rerun it")
        if census.get("tools") != state["tools"]:
            raise SystemExit("link_census: the census tools changed since this census linked; rerun it")
        digest = objects_digest(present)
        if census.get("objects_digest") != digest:
            raise SystemExit("link_census: the objects changed since this census linked; rerun it")
        if rebaseline is not None and not in_process and (rebaseline.get("commit") != commit
                                       or rebaseline.get("objects_digest") != digest
                                       or not str(rebaseline.get("game_code") or "").isdigit()):
            raise SystemExit("link_census: the previous rules' figures are not for this commit and these "
                             "objects (commit, objects_digest, game_code); nothing recorded")
    log = final_log(census)
    if rerun:
        if not history or history[-1]["commit"] != commit or history[-1]["date"] != census["when"]:
            raise SystemExit(f"link_census: --status must run on the census's own tree (HEAD {commit}; last census "
                             f"{history[-1]['commit'] + ' ' + history[-1]['date'] if history else 'none'}; "
                             f"census.json {census['when']})")
        # A later link that crashed rewrites census.log without touching
        # census.json: the log must still reproduce the census's own totals
        # (totals, since how a name is classified changes between versions).
        classes, _, dup_kinds, _ = classify(log, rows)
        if (sum(classes.values()) != sum(census["unresolved_classes"].values())
                or sum(dup_kinds.values()) != sum(census["duplicate_classes"].values())):
            raise SystemExit("link_census: census.log no longer reproduces census.json's counts; rerun the census")

    def guard(when):
        if subprocess.run(["git", "diff", "--quiet", commit, "--", *CENSUS_INPUTS], cwd=ROOT).returncode \
                or census_state(present) != state or stale_objects(present, by_object):
            raise SystemExit(f"link_census: source inputs, tools or objects changed {when}; nothing recorded")
    import link_debt
    started = time.time()
    kept = selected_definitions(selection_link(present, log))
    _stage_line("selection link and map parse", time.time() - started)
    print(f"link_census: selection (/MAP) link {time.time() - started:.0f}s, after the plain link's "
          f"{census.get('seconds', 0):.0f}s", flush=True)
    guard("during the selection link")
    clean, files, blocking, clean_prev, prepared = write_status(
        log, rows, present, {"date": census["when"], "commit": commit, "clean_tree": True}, kept, publish=False,
        previous_rules=previous_rules)
    before = linked_figures(clean_prev)
    figure = {"files": files, "files_linked": len(clean), "blocking_names": blocking,
              "addresses": sum(count for count, _ in link_debt.per_file(link_debt.addresses)),
              **linked_figures(clean), "files_linked_prev_rule": len(clean_prev),
              "linked_bytes_prev_rule": before["linked_bytes"], "linked_authored_prev_rule": before["linked_authored"],
              "rules": RULES, "prev_rules": RULES_NO_WRONG_SELECTED}
    if in_process:
        previous = linked_figures(prepared["clean_previous_rules"])
        rebaseline = {"rules": previous_rules, "files_linked": len(prepared["clean_previous_rules"]),
                      "linked_bytes": previous["linked_bytes"], "linked_authored": previous["linked_authored"],
                      "game_code": previous["game_code"]}
    if rebaseline is not None:
        if int(rebaseline["game_code"]) != int(figure["game_code"]):
            raise SystemExit(f"link_census: the previous rules saw game code {rebaseline['game_code']}, these "
                             f"{figure['game_code']}: not the same tree; nothing recorded")
        figure.update({"files_linked_prev_rule": rebaseline["files_linked"],
                       "linked_bytes_prev_rule": rebaseline["linked_bytes"],
                       "linked_authored_prev_rule": rebaseline["linked_authored"],
                       "prev_rules": rebaseline["rules"]})
    if rerun:
        history[-1].update(figure)
    else:
        history.append({**history_row(census, commit), **figure})
    rendered = render_history(history)  # validated before anything is written
    guard("during judgment")
    prepared["accept"]()
    started = time.monotonic()
    write_history(history, rendered)
    _stage_line("history written", time.monotonic() - started)
    print(f"link_census: LINKED {figure['linked_bytes']:,} bytes ({figure['linked_bytes_prev_rule']:,} under "
          f"{figure['prev_rules']}), authored {figure['linked_authored']:,} ({figure['linked_authored_prev_rule']:,}); "
          f"{'updated' if rerun else 'appended'} {HISTORY.name} ({RULES})")
    return figure


HISTORY = ROOT / "reverse/link_census_history.csv"
# Every row names the rules its figures were measured under:
#   rules       the row's own figures (files_linked, linked_bytes, linked_authored)
#   prev_rules  its *_prev_rule figures, measured on the same objects
# A row with no `rules` (all rows before the port) is LEGACY_RULES: the majority
# COMDAT keeper with the STLport and array-helper exemption, ledger row link
# order, SDK stubs excused for any retail DLL, no wrong_selected. An ordinary
# row's prev_rules is RULES_NO_WRONG_SELECTED (the same census without
# wrong_selected); each re-baseline row (tools/census_rebaseline.py) has the
# rules before it as prev_rules: LEGACY_RULES, measured by the previous
# link_census.py on the same objects, retail-truth-1 (every differing copy of
# a name with no retail address loses, referenced or not), retail-truth-2
# (every copy proven wrong loses, even when another object supplies the
# retail copy), retail-truth-3 (an unproven copy that differs from the proven
# one loses, even when the copy the link keeps is retail's), each measured in
# the same judgment as the rules after it (REBASELINE_IN_PROCESS), and
# PREVIOUS_RULES (retail-truth-4: an object's lowest row places it in link
# order even when another object's row claims that address, an ICF fold;
# code_places), measured by the previous link_census.py, which links the same
# objects in its own order. Dates are UTC from retail-truth-4 on (rows before it are mostly UTC; their
# zone is whatever the runner had); rows stay in physical append order, and
# readers take the last physical row as current.
RULES = "retail-truth-5"
RULES_NO_WRONG_SELECTED = "retail-truth-5-no-wrong-selected"
PREVIOUS_RULES = "retail-truth-4"
PREVIOUS_RULES_NO_WRONG_SELECTED = "retail-truth-4-no-wrong-selected"
RETAIL_TRUTH_3 = "retail-truth-3"
RETAIL_TRUTH_3_NO_WRONG_SELECTED = "retail-truth-3-no-wrong-selected"
RETAIL_TRUTH_2 = "retail-truth-2"
RETAIL_TRUTH_2_NO_WRONG_SELECTED = "retail-truth-2-no-wrong-selected"
RETAIL_TRUTH_1 = "retail-truth-1"
RETAIL_TRUTH_1_NO_WRONG_SELECTED = "retail-truth-1-no-wrong-selected"
LEGACY_RULES = "majority-0"
KNOWN_RULES = (LEGACY_RULES, RETAIL_TRUTH_1_NO_WRONG_SELECTED, RETAIL_TRUTH_1,
               RETAIL_TRUTH_2_NO_WRONG_SELECTED, RETAIL_TRUTH_2,
               RETAIL_TRUTH_3_NO_WRONG_SELECTED, RETAIL_TRUTH_3,
               PREVIOUS_RULES_NO_WRONG_SELECTED, PREVIOUS_RULES, RULES_NO_WRONG_SELECTED, RULES)
REBASELINE_IN_PROCESS = object()  # record(rebaseline=...): the last row's rules measured in the same judgment
# keep_rule's arguments for the earlier keep rules (write_status judges
# KEEP_RULE_VARIANTS[RETAIL_TRUTH_3] beside RULES for its report).
KEEP_RULE_VARIANTS = {RETAIL_TRUTH_3: {"retail_first": False},
                      RETAIL_TRUTH_2: {"retail_kept": False, "retail_first": False}}
# Earlier rules that differ from RULES only in keep_rule's exemptions, so a
# re-baseline measures them on the same objects, log and /MAP. None does
# since retail-truth-5: every earlier rule also placed objects by
# retail-truth-4's link order, which changes the link itself, so a
# re-baseline measures them with their own link_census.py
# (census_rebaseline.OLD_TOOL_RULES).
IN_PROCESS_RULES = {}
HISTORY_FIELDS = ["date", "commit", "objects", "unresolved", "alias", "pinned_elsewhere", "dump", "data",
                  "import", "unpinned", "duplicates", "comdat_conflicts", "comdat_vtables",
                  "scaffold_aliases", "scaffold_unresolved", "scaffold_crashed",
                  "files", "files_linked", "blocking_names", "addresses", "linked_bytes",
                  "linked_authored", "game_code", "files_linked_prev_rule", "linked_bytes_prev_rule",
                  "linked_authored_prev_rule", "rules", "prev_rules",
                  "linked_game_executable", "game_executable", "link_coverage_rules"]
# The pre-port header: HISTORY_FIELDS' first 23 columns. A header this tool
# reads must be a prefix of HISTORY_FIELDS at least that long.
_LEGACY_FIELD_COUNT = 23
_HISTORY_INTS = ("objects", "files", "files_linked", "linked_bytes", "linked_authored", "game_code")


class HistoryError(SystemExit):
    pass


def row_rules(row):
    """The rules a history row's own figures were measured under."""
    return (row.get("rules") or "").strip() or LEGACY_RULES


def read_history():
    """The rows, refusing a file this tool cannot rewrite faithfully: an
    unknown column, a row with a missing or extra field, or rules newer than
    this tool's (KNOWN_RULES)."""
    if not HISTORY.exists():
        return []
    with HISTORY.open(newline="", encoding="utf-8") as handle:
        reader = csv.reader(handle)
        header = next(reader, None)
        records = list(reader)
    if header is None:
        return []
    if len(header) < _LEGACY_FIELD_COUNT or header != HISTORY_FIELDS[:len(header)]:
        raise HistoryError(f"link_census: {HISTORY.name} has columns this tool does not know "
                           f"({', '.join(c for c in header if c not in HISTORY_FIELDS) or 'reordered'}); "
                           "update the tools (git pull) before recording")
    rows = []
    for number, record in enumerate(records, start=2):
        if len(record) != len(header):
            raise HistoryError(f"link_census: {HISTORY.name} line {number} has {len(record)} fields where the "
                               f"header has {len(header)}; refusing to rewrite a malformed history")
        row = dict(zip(header, record))
        if row_rules(row) not in KNOWN_RULES or (row.get("prev_rules") or LEGACY_RULES) not in KNOWN_RULES:
            raise HistoryError(f"link_census: {HISTORY.name} line {number} was measured under rules this tool "
                               f"does not know ({row.get('rules')!r}); update the tools (git pull) before recording")
        coverage = ('linked_game_executable', 'game_executable', 'link_coverage_rules')
        if any(row.get(k) for k in coverage):
            import progress
            if (row.get('link_coverage_rules') != progress.LINK_COVERAGE_RULES
                    or not all(str(row.get(k, '')).isdigit() for k in coverage[:2])
                    or not 0 <= int(row['linked_game_executable']) <= int(row['game_executable']) <= int(row['game_code'])):
                raise HistoryError(f'link_census: invalid inclusive coverage at line {number}')
        rows.append(row)
    return rows


def check_history_rules(history, census, *, rerun=False, rebaseline=None):
    """A row may only continue its predecessor's rules. The first RULES row
    is the re-baseline (census_rebaseline.py), which must carry the previous
    rules' figures for the same objects; an ordinary census refuses until it
    exists, and the re-baseline refuses once it does. A missing, empty or
    header-only history refuses both: that is what an old writer's
    truncation leaves, and appending to it would discard every earlier row
    (restore it from git). Dates never go back."""
    last = row_rules(history[-1]) if history else None
    if census.get("rules") not in (None, RULES):
        raise HistoryError(f"link_census: this census was measured under {census.get('rules')!r}, not {RULES}")
    if rerun:
        if last != RULES:
            raise HistoryError(f"link_census: --status would restate a {last} row under {RULES}; rerun the census")
        return
    if not history:
        raise HistoryError(f"link_census: {HISTORY.name} is missing or has no rows (an old writer truncates it); "
                           f"restore it (git checkout -- {HISTORY.relative_to(ROOT).as_posix() if HISTORY.is_relative_to(ROOT) else HISTORY.name}) "
                           "before recording")
    if rebaseline is not None:
        if last == RULES:
            raise HistoryError(f"link_census: the history already records {RULES}; no re-baseline to do")
        if rebaseline.get("rules") != (last or LEGACY_RULES):
            raise HistoryError(f"link_census: the re-baseline's previous figures are {rebaseline.get('rules')!r}, "
                               f"but the last row is {last}")
    elif last != RULES:
        raise HistoryError(f"link_census: the history's last row is {last}; the first {RULES} row must be the "
                           "re-baseline (tools/census_rebaseline.py), which measures both rules on the same objects")
    if census["when"] < history[-1]["date"]:
        raise HistoryError(f"link_census: this census ({census['when']} UTC) is dated before the last row "
                           f"({history[-1]['date']}); check the clock")


def render_history(rows):
    """The whole file as text, validated: every row serializes under
    HISTORY_FIELDS (an unknown key refuses), re-reads to the same values,
    and names known rules."""
    import io
    for number, row in enumerate(rows, start=2):
        unknown = set(row) - set(HISTORY_FIELDS)
        if unknown:
            raise HistoryError(f"link_census: history row {number} has unknown fields {sorted(map(str, unknown))}")
        if row_rules(row) not in KNOWN_RULES:
            raise HistoryError(f"link_census: history row {number} names unknown rules {row.get('rules')!r}")
        prev = (row.get("prev_rules") or "").strip()
        if prev and prev not in KNOWN_RULES:
            raise HistoryError(f"link_census: history row {number} names unknown prev_rules {prev!r}")
        for field in _HISTORY_INTS:
            value = str(row.get(field) or "")
            if value and not value.isdigit():
                raise HistoryError(f"link_census: history row {number} has {field}={value!r}")
    handle = io.StringIO()
    writer = csv.DictWriter(handle, HISTORY_FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    text = handle.getvalue()
    again = list(csv.DictReader(io.StringIO(text)))
    if len(again) != len(rows) or any({k: str(v) for k, v in row.items() if v not in (None, "")}
                                      != {k: v for k, v in back.items() if v} for row, back in zip(rows, again)):
        raise HistoryError("link_census: the history does not survive a round trip; nothing written")
    return text


def write_history(rows, text=None):
    """Replace the history atomically: a temporary file in the same
    directory, renamed over it, so a failure leaves the old file whole."""
    text = render_history(rows) if text is None else text
    temp = HISTORY.with_name(HISTORY.name + ".tmp")
    with temp.open("w", newline="", encoding="utf-8") as handle:
        handle.write(text)
        handle.flush()
        os.fsync(handle.fileno())
    os.replace(temp, HISTORY)


def history_row(census, commit):
    """One row per census: the trend of what stands between the tree and a link."""
    unresolved = census["unresolved_classes"]
    conflicts = census.get("comdat_conflicts", {})
    scaffold = census.get("scaffold") or {}
    return {"date": census["when"], "commit": commit, "objects": census["objects"],
            "unresolved": sum(unresolved.values()), "alias": unresolved.get("alias", 0),
            "pinned_elsewhere": unresolved.get("pinned-elsewhere", 0), "dump": unresolved.get("dump", 0),
            "data": unresolved.get("data", 0), "import": unresolved.get("import", 0),
            "unpinned": unresolved.get("unpinned", 0), "duplicates": sum(census["duplicate_classes"].values()),
            "comdat_conflicts": len(conflicts),
            "comdat_vtables": sum(1 for n in conflicts if n.startswith(("??_7", "??_R"))),
            "scaffold_aliases": scaffold.get("aliases", ""),
            "scaffold_unresolved": "" if not scaffold or scaffold.get("crashed")
            else sum(scaffold["unresolved_classes"].values()),
            "scaffold_crashed": (scaffold.get("crashed") or "")[:60]}


if __name__ == "__main__":
    sys.exit(main())
