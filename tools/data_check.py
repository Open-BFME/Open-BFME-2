#!/usr/bin/env python3
"""DIR32 data references must bind to the data ledger's global (shadow mode).

reverse/data_ledger.csv (tools/data_ledger.py) names one symbol per retail data
address. For each checked source's matched rows this reads the compiled
object and flags:

  wrong-name     a DIR32 relocation reaches ledger address A through a symbol
                 that is not A's ledger name (an invented second global for
                 retail's one: `g_Va009FE16C` where the ledger has
                 `TheScriptEngine`). Compiler-emitted names (string and float
                 literals, vftables, RTTI, imports) are the compiler's and are
                 not judged.
  duplicate-def  the object defines (non-COMDAT, external or static) a data
                 symbol that reaches a ledger address another TU owns.

Existing violations are keyed in reverse/data_check_baseline.txt
(`source<TAB>check<TAB>symbol<TAB>address`), which may only shrink:
--write-baseline never adds a key unless --init, and --assert-shrink-only REF
fails when the file gained a line against git REF. In shadow mode (the
default) findings are printed and the exit status is 0; --enforce exits 1 on
a finding outside the baseline.

--converged is ENFORCED, after the byte gate built the objects it reads. It
judges only the addresses in reverse/data_converged.csv, each first brought
down to one name the whole tree spells, and refuses any other symbol a checked
row's DIR32 operand binds there -- by the symbol's own address or by the
address the operand reaches (`array+4` onto a protected slot): a second
spelling links as its own datum, and every row reaching the address then
fails link_cycle's data-back. Three such addresses had their aliases back
within five hours of a cleanup while this check ran in shadow mode. Nothing
is exempt: no baseline, no spelling rule. It reads rows of .c, .cpp and .asm
sources, each only from an object build.compile_is_current proves current,
and refuses a row it cannot judge. The list, read from the index or the
pushed commit (--ref), must parse and be non-empty, and only grows
(--converged-base): re-opening an address is a change to this file.

What it trusts is what the byte gate trusts, no more: objects the hook's
build just made or proved current, built from the working tree, which
pre-push binds to the pushed commit for every changed file and every tracked
header or shim; header dependents are byte-verified before their relocations
are read. Not covered (GPT-6.1-Sol, review round 2): an untracked file that
shadows a header (compile_is_current is not run strict -- most units have no
include inventory yet, and strict would refuse them all); a header change the
include graph cannot bound at push, judged on existing current objects; an
object built under a different compiler environment (the hooks clear CL and
_CL_). Client-side hooks are advisory against a seat that edits them.

  python3 tools/data_check.py --staged          # pre-commit: staged C/C++ sources;
                                                # fails (any mode) if the staged baseline grew
  python3 tools/data_check.py SOURCE...
  python3 tools/data_check.py --all [--write-baseline [--init]]
  python3 tools/data_check.py --assert-shrink-only HEAD
  python3 tools/data_check.py --converged --ref : --converged-base HEAD --sources-from -   # pre-commit
  python3 tools/data_check.py --converged --all          # every matched source (full gate)
"""
import argparse
import collections
import csv
import hashlib
import io
import json
import os
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import data_ledger as dl  # noqa: E402

BASELINE = ROOT / "reverse" / "data_check_baseline.txt"
HEADER = "# source\tcheck\tsymbol\taddress -- shrink-only; written by tools/data_check.py\n"
CONVERGED = ROOT / "reverse" / "data_converged.csv"


def listed_at(ref, rel):
    """Whether REF (':' the index, else a commit) holds `rel`, from the listing of
    its directory rather than its blob: only a clean listing without it proves
    absence, so an unreadable list is never taken for a missing one (a failed
    listing raises). The same name in another case raises too: Windows reads it
    as `rel` while git's exact lookup would miss it (GPT-6.1-Sol, round 6)."""
    # the whole snapshot, not one directory: a variant parent (Reverse/) hides from
    # a listing of reverse/ exactly as a variant name hides from an exact lookup
    cmd = ["git", "ls-files", "--stage", "-z"] if ref == ":" else ["git", "ls-tree", "-r", "-z", ref]
    done = subprocess.run(cmd, cwd=ROOT, capture_output=True)
    if done.returncode:
        raise OSError(f"{' '.join(cmd[:3])}: {done.stderr.decode(errors='replace').strip()}")
    names = {entry.split("\t", 1)[1] for entry in done.stdout.decode("utf-8", errors="replace").split("\0")
             if "\t" in entry}
    if rel in names:
        return True
    if any(name.lower() == rel.lower() for name in names):
        raise OSError(f"{rel} is tracked under another case at {ref}; rename it to {rel}")
    return False


def text_at(ref, path):
    """`path`'s text in git REF (':' the index), or the working copy when ref is
    None; None when that snapshot does not hold the file. An unknown REF raises.
    A hook judges what it commits or pushes, so an unstaged edit to the list
    cannot loosen the check."""
    if ref is None:
        return path.read_text(encoding="utf-8") if path.exists() else None
    if ref != ":":
        known = subprocess.run(["git", "rev-parse", "--verify", "--quiet", "--end-of-options",
                                f"{ref}^{{commit}}"], cwd=ROOT, capture_output=True)
        if known.returncode:
            raise OSError(f"unknown revision {ref!r}")
    rel = path.relative_to(ROOT).as_posix()
    spec = f":{rel}" if ref == ":" else f"{ref}:{rel}"
    if not listed_at(ref, rel):
        return None
    done = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if done.returncode:
        raise OSError(f"git show {spec}: {done.stderr.decode(errors='replace').strip()}")
    return done.stdout.decode("utf-8")


def load_converged(path=None, ref=None, required=True):
    """{retail rva: canonical symbol} of reverse/data_converged.csv in REF. Any
    doubt raises ValueError -- a missing (when required) or empty list, a missing
    column, a short row, a bad address, an empty or repeated name: an enforced
    check never runs on a list it misread. None when not required and absent."""
    path = CONVERGED if path is None else Path(path)
    text = text_at(ref, path)
    if text is None:
        if required:
            raise ValueError(f"{path.name} is missing at {ref or 'the working copy'}")
        return None
    out = {}
    try:
        reader = csv.DictReader(io.StringIO(text))
        if not {"address", "name"} <= set(reader.fieldnames or ()):
            raise ValueError("no address,name header")
        for row in reader:
            address, name = row.get("address"), row.get("name")
            if not isinstance(address, str) or not isinstance(name, str) or None in row:
                raise ValueError(f"malformed row {row}")
            rva, name = int(address, 16), name.strip()
            if not name.startswith(("?", "_")) or rva in out:
                raise ValueError(f"empty, unmangled or repeated entry at {address}")
            out[rva] = name
    except (KeyError, TypeError, AttributeError, csv.Error) as error:
        raise ValueError(f"{path.name}: {error}") from error
    if not out and required:
        raise ValueError(f"{path.name} lists no address")
    return out


def lost_addresses(base_ref, converged, path=None):
    """Addresses the list held at BASE_REF that `converged` dropped or renamed.
    The list only grows: dropping an address re-opens it to a second name, which
    is a change to this checker (tools/data_check.py), never a data edit."""
    base = load_converged(path, ref=base_ref, required=False)
    return sorted(a for a, name in (base or {}).items() if converged.get(a) != name)


def source_rows(sources):
    wanted = set(sources)
    return [r for r in dl.matched_rows() if r["source"] in wanted]


def object_facts(rows, unread=None):
    """{source: (bindings {(symbol, base)}, defined data symbols {name})}. A row
    whose object or body cannot be read is skipped, and listed in `unread`
    [(source, row name, why)] when given."""
    sections = dl.retail_sections()
    text = next((s for s in sections if s[0] == ".text"), None)
    out = {}
    for row in rows:
        obj = build.row_object(row)
        if not obj.exists():
            if unread is not None:
                unread.append((row["source"], row["name"], "no object"))
            continue
        binds, defined = out.setdefault(row["source"], (set(), set()))
        if not defined:
            _d, osecs, symbols = dl.layout(obj)
            for s in symbols:
                if s["section"] <= 0 or s.get("storage") not in (dl.EXTERNAL, dl.STATIC) or s["name"].startswith(("$", ".")):
                    continue
                flags = osecs[s["section"] - 1]["characteristics"]
                if not flags & (dl.CODE | dl.COMDAT):
                    defined.add(s["name"])
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = build.read_target_bytes(rva, size)
            symbol = build.ledger_object_symbol(row)
            if build.is_funclet_row(row, symbol):     # a $L label: the body the byte gate reads
                body, relocs, _note = build.read_funclet(row, symbol, obj, target)
            else:
                body, relocs = build.read_object_symbol_bytes(obj, symbol, size)
        except (ValueError, OSError, SystemExit) as error:
            if unread is not None:
                unread.append((row["source"], row["name"], f"unreadable: {error}"))
            continue
        for offset, kind, symbol in relocs:
            if kind != dl.DIR32 or offset + 4 > min(size, len(body), len(target)) or symbol.startswith(("$", "__ehhandler$")):
                continue
            base = (struct.unpack_from("<I", target, offset)[0] - struct.unpack_from("<I", body, offset)[0]
                    - dl.IMAGE_BASE) & 0xFFFFFFFF
            if text and text[1] <= base < text[1] + text[3]:
                continue
            binds.add((symbol, base))
    return out


def findings(facts, ledger):
    """[(source, check, symbol, '0xADDR')] for the given object facts."""
    out = set()
    for source, (binds, defined) in facts.items():
        for symbol, base in binds:
            row = ledger.get(base)
            if row is None or dl.kind_of(symbol) != "global" or row["kind"] != "global":
                continue
            if symbol != row["name"]:
                out.add((source, "wrong-name", symbol, f"0x{base:08X}"))
            if symbol in defined and row["source"] and row["source"] != source:
                out.add((source, "duplicate-def", symbol, f"0x{base:08X}"))
    return sorted(out)


CONVERGED_SUFFIXES = (".c", ".cpp", ".asm")


def converged_rows(sources):
    """Every matched row of `sources` this repository compiles (.c, .cpp, .asm);
    rows of prebuilt .lib members are retail's own objects and name nothing."""
    wanted = set(sources)
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r.get("status") == "matched"
                and (r.get("target_rva") or "").startswith("0x") and r["source"] in wanted
                and r["source"].lower().endswith(CONVERGED_SUFFIXES)]


def converged_facts(rows, unread):
    """[(source, symbol, base, effective)] for every DIR32 relocation in the rows'
    bodies: `base` the symbol's retail address (target less the object's addend),
    `effective` the address the operand reaches. Nothing is exempt by spelling.
    A row is read only from an object build.compile_is_current proves built from
    its source, compile command and headers as they are now; any other row lands
    in `unread` [(source, row name, why)]. Currency is checked once per
    (source, object) during this call, then checked again before returning.
    Source, object, receipt and recorded dependency identities must remain
    unchanged throughout; no verdict is cached between calls."""
    def stamp(path):
        try:
            stat = path.stat()
            identity = (stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns)
            digest = hashlib.md5(path.read_bytes()).hexdigest()
            after = path.stat()
            if identity != (after.st_dev, after.st_ino, after.st_size,
                            after.st_mtime_ns, after.st_ctime_ns):
                raise OSError(f"{path} changed while read")
            # Uncached content matters on Windows: ctime is creation time, and
            # restoring mtime can hide a same-sized write from a stat cache.
            return identity, digest
        except OSError:
            return None

    stamps = {}
    environment = dict(os.environ)
    layouts = collections.OrderedDict()

    def layout_digest(obj):
        stat = obj.stat()
        data = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)[0]
        identity = id(data)
        cached = layouts.get(identity)
        if cached is None:
            cached = (data, hashlib.md5(data).hexdigest())
            layouts[identity] = cached
            if len(layouts) > 256:
                layouts.popitem(last=False)
        else:
            assert cached[0] is data           # retained bytes prevent id reuse
            layouts.move_to_end(identity)
        return cached[1]
    # flag_defaults and retail readers cache these process-wide. Rechecking a
    # command alone cannot see a changed cached region table or ledger vote.
    global_inputs = {
        ROOT / "tools" / name for name in
        ("build.py", "data_check.py", "data_ledger.py", "flag_defaults.py", "eh_verify.py",
         "stlport_folds.py", "coffar.py", "gen_case_shims.py")
    } | {
        ROOT / "reverse" / "functions.csv",
        ROOT / "reverse" / "symbols.csv",
        ROOT / "reverse" / "flag_overrides.csv",
        ROOT / "reverse" / "retail_inventory" / "flag_regions.csv",
        build.EXE,
    }
    for path in global_inputs:
        stamps[path] = stamp(path)
    sections = dl.retail_sections()
    text = next((s for s in sections if s[0] == ".text"), None)

    def in_text(address):
        return bool(text) and text[1] <= address < text[1] + text[3]

    def currency(source, obj, watched=None, proofs=None):
        def watch(path):
            path = Path(path)
            if watched is not None:
                watched.add(path)
                if path not in stamps:
                    stamps[path] = stamp(path)
                return stamps[path]
            if proofs is not None:
                if path not in proofs:
                    proofs[path] = stamp(path)
                return proofs[path]
            return stamp(path)

        watch(source)
        watch(obj)
        watch(build._deps_sidecar(obj))
        try:
            why = "no object" if not obj.exists() else "object not current for its source"
            if not obj.exists():
                return False, why
            meta = json.loads(build._deps_sidecar(obj).read_text())
            if not isinstance(meta, dict) or not isinstance(meta.get("deps", {}), dict):
                return False, why
            recorded = {source: meta["source"]} if "source" in meta else {}
            for dep in meta.get("deps", {}):
                if not build.cache_path_is_valid(dep):
                    return False, why
                recorded[Path(dep) if os.path.isabs(dep) else ROOT / dep] = meta["deps"][dep]
            for path, digest in recorded.items():
                proof = watch(path)
                if proof is None or proof[1] != digest:
                    return False, why
            current = build.compile_is_current(source, obj)
            if current:
                # the receipt names the object it was written for: a swapped .obj is not it
                proof = watch(obj)
                if proof is None or ("object" in meta and meta["object"] != proof[1]):
                    current, why = False, "object is not the one its build receipt recorded"
                if current and watched is not None:
                    if layout_digest(obj) != proof[1]:
                        current, why = False, "cached object layout differs from its build receipt"
        except Exception as error:  # noqa: BLE001 -- not proven current is not current
            current, why = False, f"object currency unknown: {error}"
        return current, why

    objects, out, failed, changed_objects = {}, [], set(), set()
    for index, row in enumerate(rows):
        obj = build.row_object(row)
        key = (row["source"], obj)
        if key not in objects:
            watched = set()
            current, why = currency(ROOT / row["source"], obj, watched)
            objects[key] = (current, why, watched, [])
        current, why, _watched, members = objects[key]
        members.append((index, row["name"]))
        if not current:
            unread.append((row["source"], row["name"], why))
            failed.add(index)
            continue
        try:
            if layout_digest(obj) != stamps[obj][1]:
                changed_objects.add(key)
                raise ValueError("object layout changed during data audit")
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = build.read_target_bytes(rva, size)
            symbol = build.ledger_object_symbol(row)
            if build.is_funclet_row(row, symbol):     # a $L label: the body the byte gate reads
                body, relocs, _note = build.read_funclet(row, symbol, obj, target)
            else:
                body, relocs = build.read_object_symbol_bytes(obj, symbol, size)
            if layout_digest(obj) != stamps[obj][1]:
                changed_objects.add(key)
                raise ValueError("object layout changed during data audit")
        except (ValueError, OSError, SystemExit) as error:
            unread.append((row["source"], row["name"], f"unreadable: {error}"))
            failed.add(index)
            continue
        for offset, kind, name in relocs:
            if kind != dl.DIR32 or offset + 4 > min(size, len(body), len(target)):
                continue
            effective = (struct.unpack_from("<I", target, offset)[0] - dl.IMAGE_BASE) & 0xFFFFFFFF
            base = (effective - struct.unpack_from("<I", body, offset)[0]) & 0xFFFFFFFF
            if in_text(base) and in_text(effective):
                continue
            out.append((key, (row["source"], name, base, effective)))

    rejected = set()
    # A shared header is stamped only once, but every object using it is refused
    # if it moved. Ordinary currency rechecks also judge the current command and
    # configuration; a newly valid replacement receipt cannot hide moved files.
    after = {path: stamp(path) for path in stamps}
    moved = {path for path, before in stamps.items() if after[path] != before}
    for key, (current, _why, watched, members) in objects.items():
        if not current:
            continue
        source, obj = key
        current, why = currency(ROOT / source, obj, proofs=after)
        if key in changed_objects or watched & moved or global_inputs & moved or dict(os.environ) != environment:
            current, why = False, "object or build inputs changed during data audit"
        if not current:
            rejected.add(key)
            for index, name in members:
                if index not in failed:
                    unread.append((source, name, why))
    # Final checks themselves read inputs: detect movement during those checks,
    # too, rather than returning an earlier object's now-stale facts.
    moved = {path for path, before in stamps.items() if stamp(path) != before}
    for key, (current, _why, watched, members) in objects.items():
        if current and key not in rejected and (watched & moved or global_inputs & moved
                                                or dict(os.environ) != environment):
            rejected.add(key)
            for index, name in members:
                if index not in failed:
                    unread.append((key[0], name, "object or build inputs changed during data audit"))
    return [fact for key, fact in out if key not in rejected]


def converged_rows_all():
    """Every matched row this repository compiles (the full-gate case)."""
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r.get("status") == "matched"
                and (r.get("target_rva") or "").startswith("0x")
                and r["source"].lower().endswith(CONVERGED_SUFFIXES)]


def converged_findings(facts, converged):
    """[(source, 'wrong-name', symbol, '0xADDR')]: a symbol other than the canonical
    one whose own address or whose operand's address is a converged address
    (`array+4` reaching a protected slot counts as much as a second spelling)."""
    out = set()
    for source, symbol, base, effective in facts:
        for address in {base, effective}:
            name = converged.get(address)
            if name is not None and symbol != name:
                out.add((source, "wrong-name", symbol, f"0x{address:08X}"))
    return sorted(out)


def check_converged(sources, converged):
    """Exit status of the enforced check over `sources`: 1 on any second name at
    a converged address or on a row it could not judge. No baseline: every
    address on the list was brought down to its one name first."""
    unread = []
    found = converged_findings(converged_facts(converged_rows(sources), unread), converged)
    for source, _check, symbol, address in found:
        print(f"data_check: {source} binds {symbol} at {address}, a converged address whose one name is "
              f"{converged[int(address, 16)]} (reverse/data_converged.csv). Declare that global by its "
              f"name -- `class X; extern X *TheX;`, a class, not a struct -- and cast to a private view "
              f"where it is used: ((View *)TheX)->field.")
    for source, name, why in unread:
        print(f"data_check: {source}: cannot judge {name} ({why}); run ./build.sh {source} and retry")
    print(f"data_check (converged, enforced): {len(sources)} source(s), {len(converged)} address(es), "
          f"{len(found)} second name(s), {len(unread)} unjudged row(s)")
    return 1 if found or unread else 0


def claimed_sources(sources):
    """The `sources` owning a matched function row or a matched data row, in order:
    what the build can byte-verify. A parked draft (no row) makes the build refuse
    `no functions match`, so a header that reaches one must not hand it over."""
    claimed = set()
    for ledger in (ROOT / "reverse" / "functions.csv", ROOT / "reverse" / "data_rows.csv"):
        if ledger.exists():
            with ledger.open(newline="", encoding="utf-8") as handle:
                claimed |= {r["source"] for r in csv.DictReader(handle) if r.get("status") == "matched"}
    return [s for s in sources if s in claimed]


def read_sources_from(spec):
    data = sys.stdin.buffer.read() if spec == "-" else Path(spec).read_bytes()
    return [p.decode("utf-8") for p in data.split(b"\0") if p]


def read_baseline(text=None):
    if text is None:
        text = BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else ""
    return {tuple(line.split("\t")) for line in text.splitlines() if line and not line.startswith("#")}


def write_baseline(keys):
    BASELINE.write_text(HEADER + "".join("\t".join(k) + "\n" for k in sorted(keys)), encoding="utf-8", newline="")


def staged_sources():
    names = subprocess.run(["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR"], cwd=ROOT,
                           capture_output=True, text=True).stdout.split()
    return [n for n in names if n.lower().endswith((".c", ".cpp"))]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("sources", nargs="*")
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--enforce", action="store_true", help="exit 1 on a finding outside the baseline")
    parser.add_argument("--write-baseline", action="store_true")
    parser.add_argument("--init", action="store_true", help="with --write-baseline: allow new keys")
    parser.add_argument("--assert-shrink-only", metavar="REF")
    parser.add_argument("--converged", action="store_true",
                        help="ENFORCED: refuse a second name at a reverse/data_converged.csv address")
    parser.add_argument("--sources-from", metavar="FILE", help="NUL-separated sources ('-': stdin)")
    parser.add_argument("--ref", help="--converged: read the list from git REF (':' the index)")
    parser.add_argument("--converged-base", metavar="REF",
                        help="--converged: refuse when the list lost or renamed an address it held at REF")
    parser.add_argument("--print-claimed", action="store_true",
                        help="print (NUL-separated) the --sources-from sources owning a matched row")
    args = parser.parse_args(argv)
    if args.print_claimed:
        if not args.sources_from:
            parser.error("--print-claimed reads --sources-from")
        for source in claimed_sources(read_sources_from(args.sources_from)):
            sys.stdout.buffer.write(source.encode("utf-8") + b"\0")
        return 0
    if args.assert_shrink_only:
        old = subprocess.run(["git", "show", f"{args.assert_shrink_only}:reverse/data_check_baseline.txt"],
                             cwd=ROOT, capture_output=True, text=True)
        grown = read_baseline() - read_baseline(old.stdout) if old.returncode == 0 else set()
        for key in sorted(grown):
            print("data_check: baseline gained", "\t".join(key))
        return 1 if grown else 0
    started = time.time()
    if args.staged and "reverse/data_check_baseline.txt" in subprocess.run(
            ["git", "diff", "--cached", "--name-only"], cwd=ROOT, capture_output=True, text=True).stdout.split():
        old = subprocess.run(["git", "show", "HEAD:reverse/data_check_baseline.txt"], cwd=ROOT,
                             capture_output=True, text=True)
        staged = subprocess.run(["git", "show", ":reverse/data_check_baseline.txt"], cwd=ROOT,
                                capture_output=True, text=True)
        grown = read_baseline(staged.stdout) - read_baseline(old.stdout) if old.returncode == 0 else set()
        if grown:   # the baseline is shrink-only even in shadow mode
            for key in sorted(grown):
                print("data_check: baseline gained", "	".join(key))
            return 1
    if args.converged:
        if args.write_baseline:
            parser.error("--converged checks sources; it never writes the baseline")
        try:
            converged = load_converged(ref=args.ref)
            lost = lost_addresses(args.converged_base, converged) if args.converged_base else []
        except (OSError, ValueError) as error:
            print(f"data_check: cannot use reverse/data_converged.csv: {error}")
            return 1
        if lost:
            print("data_check: reverse/data_converged.csv dropped or renamed "
                  + ", ".join(f"0x{a:08X}" for a in lost) + f" against {args.converged_base}; "
                  "the list only grows (re-opening an address is a change to tools/data_check.py)")
            return 1
        if args.all:
            sources = sorted({r["source"] for r in converged_rows_all()})
        elif args.sources_from:
            sources = read_sources_from(args.sources_from)
        elif args.staged:
            sources = staged_sources()
        else:
            sources = args.sources
        return check_converged(sources, converged)
    ledger = dl.load()
    if not ledger:
        print("data_check: no reverse/data_ledger.csv; nothing to check")
        return 0
    if args.all:
        sources = sorted({r["source"] for r in dl.matched_rows()})
    elif args.staged:
        sources = staged_sources()
    else:
        sources = args.sources
    found = findings(object_facts(source_rows(sources)), ledger)
    baseline = read_baseline()
    if args.write_baseline:
        keys = set(found) if args.init else set(found) & baseline
        if args.all:
            write_baseline(keys)
        else:   # a partial run only drops keys of the sources it checked
            write_baseline({k for k in baseline if k[0] not in set(sources)} | keys)
        print(f"data_check: baseline {len(keys)} key(s)")
        return 0
    new = [f for f in found if f not in baseline]
    for f in new:
        print("data_check:", "\t".join(f))
    kinds = collections.Counter(f[1] for f in new)
    mode = "enforce" if args.enforce else "shadow"
    print(f"data_check ({mode}): {len(sources)} source(s), {len(found)} finding(s), {len(new)} outside the "
          f"baseline {dict(kinds)}; {time.time() - started:.1f}s")
    return 1 if new and args.enforce else 0


if __name__ == "__main__":
    sys.exit(main())
