#!/usr/bin/env python3
"""Trial the ledger's STLport-derived rows against vendored STLport 4.6.

The tree holds STLport 4.5.3 headers (vendor/stlport, project-patched) and
pasted copies of STLport's compiled library sources (WWLib/stlport_*.cpp,
Code/Libraries/Source/STLport). This tool measures, row by row, whether the
pristine 4.6 release (vendor/stlport-4.6) reproduces retail as well, so the
tree can converge on one vendored STLport and a gate can refuse STLport code
outside vendor/.

Two lanes, both read-only with respect to the ledger and Code/:

  headers   Recompile each `// stlport` TU twice in an isolated object dir:
            once against the current headers (the control) and once with the
            STLport include directory swapped for 4.6, keeping the unit's own
            `// cl:` flags and shims. Every matched row of the unit is compared
            with retail through build.compile_function, the same comparison the
            byte gate uses. Rows that pass the control but fail 4.6 are then
            retried with each config knob (-D<knob>) and without the STLport
            overlay shims (STL_OVERLAYS), and the first knob that restores the
            row is kept. A unit whose own declarations spell 4.5.3's const
            allocator members is compiled as an `adapt` copy (that const
            removed) before the knobs are tried on top of it.
  library   Compile pristine 4.6 src/*.cpp with upstream's VC7 static-library
            flags and each knob variant. Ledger rows the TU emits by name are
            compared with retail; every other emitted body is searched for in
            retail .text by masked bytes (place_bodies.py's method).
  report    Merge both lanes' cached results into reverse/stlport_trial.csv and
            print the summary.
  queue     Print the repoint queue: STLport-derived rows that match 4.6
            as-is (or with one knob), grouped by source file. A picker can read
            it as a queue source with `queue --tsv`.

Results are cached per (source content, tree, variant) under
build/stlport_trial/, so re-runs only compile what changed. Nothing here edits
tools/build.py or the ledger; objects never touch build/match/.

Usage:
  python3 tools/stlport_trial.py headers [--sample N | --all] [--seed S] [SOURCE...]
  python3 tools/stlport_trial.py library [--src-dir DIR --tree-dir DIR --tag T]
  python3 tools/stlport_trial.py report
  python3 tools/stlport_trial.py queue [--tsv]
"""
import argparse
import collections
import concurrent.futures
import csv
import hashlib
import json
import os
import random
import re
import struct
import subprocess
import sys
import threading
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build  # noqa: E402
import place_bodies  # noqa: E402
import stlport_overlay  # noqa: E402

ROOT = build.ROOT
CURRENT_TREE = ROOT / "vendor" / "stlport"
TREE_46 = ROOT / "vendor" / "stlport-4.6" / "stlport"
SRC_46 = ROOT / "vendor" / "stlport-4.6" / "src"
OUT = ROOT / "build" / "stlport_trial"
CACHE = OUT / "results.json"
REPORT = ROOT / "reverse" / "stlport_trial.csv"
SHIMS = ROOT / "reference" / "shims"
# Shim include dirs that overlay STLport headers (`stl/_alloc.h`, `_list.h`,
# `_hashtable.h`, ...): retail-demanded edits of 4.5.3 copies. The `-shim`
# variant drops all of them so a unit sees pristine 4.6 only.
STL_OVERLAYS = sorted("reference/shims/" + d.name for d in SHIMS.iterdir()
                      if (d / "stl").is_dir()) if SHIMS.is_dir() else []
CACHE_VERSION = 3

# The stl_user_config.h / compiler-config switches worth a trial. Each is tried
# alone on top of the unit's own flags; `-shim` drops the bfmealloc shim (a
# 4.5.3-derived copy of three STLport headers) so 4.6's own headers are used.
KNOBS = [
    "_STLP_USE_STATIC_LIB",
    "_STLP_USE_MALLOC",
    "_STLP_USE_NEWALLOC",
    "_STLP_NO_OWN_IOSTREAMS",
    "_STLP_NO_NEW_IOSTREAMS",
    "_STLP_NO_EXCEPTIONS",
    "_STLP_NO_CUSTOM_IO",
    "_STLP_NO_METHOD_SPECIALIZATION",
    "-shim",
]

# Upstream's src/vc_common.mak release-static flags (staticx: /MD, static lib).
LIBRARY_BASE_FLAGS = ["-O2", "-GR", "-EHsc", "-MD", "-DNDEBUG", "-DWIN32", "-D_WINDOWS",
                      "-D_MBCS", "-D_STLP_USE_STATIC_LIB", "-D_STLP_NO_FORCE_INSTANTIATE"]
LIBRARY_VARIANTS = {
    "upstream-staticx": [],
    "MT": ["-MT", "-U_STLP_USE_STATIC_LIB"],
    "GR-": ["-GR-"],
    "noexcept": ["-D_STLP_NO_EXCEPTIONS", "-EHs-c-"],
    "malloc": ["-D_STLP_USE_MALLOC"],
    "newalloc": ["-D_STLP_USE_NEWALLOC"],
    "O1": ["-O1"],
    # Code/Libraries/Source/STLport's hand rows build /Od /Ob1 (string replace
    # at 0x0002AE50, 0x000284D0): part of retail's library was not optimized.
    "Od-Ob1": ["-Od", "-Ob1"],
    "project-base": ["-GR-", "-EHsc-", "-D_STLP_NO_EXCEPTIONS", "-D_STLP_USE_MALLOC"],
}
# The compiled library: iostreams, locale, facets, strings. dll_main.cpp holds
# the explicit instantiations and the static-init objects.
LIBRARY_SOURCES = [
    "codecvt.cpp", "collate.cpp", "complex.cpp", "complex_exp.cpp", "complex_io.cpp",
    "complex_io_w.cpp", "complex_trig.cpp", "ctype.cpp", "dll_main.cpp",
    "facets_byname.cpp", "fstream.cpp", "ios.cpp", "iostream.cpp", "istream.cpp",
    "locale.cpp", "locale_catalog.cpp", "locale_impl.cpp", "messages.cpp",
    "monetary.cpp", "num_get.cpp", "num_get_float.cpp", "num_put.cpp",
    "num_put_float.cpp", "numpunct.cpp", "ostream.cpp", "sstream.cpp",
    "stdio_streambuf.cpp", "streambuf.cpp", "string_w.cpp", "strstream.cpp",
    "time_facets.cpp", "c_locale.c",
]

LIBRARY_COPY = re.compile(r"(^|/)WWLib/stlport_[^/]*\.(cpp|c)$")
LIBRARY_HAND = "Code/Libraries/Source/STLport/"
VENDORED = re.compile(r"(?:^|;)\s*vendored=(stlport[^;]*)")
BFME_EXTENSIONS = re.compile(r"_STLP_BFME_\w+|_BFME_RETAIL_TREE_INSERT_LAYOUT|"
                             r"BFME_PARTICLE_LIST_NODE_TAIL")

# 4.6 dropped `const` from allocator<T>::allocate/deallocate/construct/destroy
# and added it to address(); the bodies are unchanged, the mangled names are
# not (QBE <-> QAE). Callee and row names are translated through this only.
ALLOCATOR_MEMBER = re.compile(
    r"^(\?(?:allocate|deallocate|construct|destroy|address)@\?\$allocator@.*@_STL@@Q)([AB])(E.*)$")

# The tree's own link-control declarations (explicit specializations that
# suppress or force-inline an allocator COMDAT) spell 4.5.3's signatures:
# `allocator<T>::allocate(...) const`. 4.6 dropped that const, so such a unit
# cannot compile against 4.6 at all (C2244). The `adapt` variant compiles a
# copy with the 4.5.3-only const removed; nothing else in the unit changes.
ALLOCATOR_CONST_DECL = re.compile(
    r"(allocator<.*>::(?:allocate|deallocate|construct|destroy)\s*\([^;{]*\))\s*const(\s*[;{])")

_print_lock = threading.Lock()


def log(*args):
    with _print_lock:
        print(*args, file=sys.stderr, flush=True)


def const_twin(name):
    match = ALLOCATOR_MEMBER.match(name)
    if not match:
        return None
    return match.group(1) + ("A" if match.group(2) == "B" else "B") + match.group(3)


class TranslatingSymbolMap(dict):
    """build.load_symbol_map(), plus the allocator const-twin of every name.

    A 4.6 body calls `allocator<T>::allocate` under its non-const mangling;
    the ledger knows the same function under 4.5.3's const mangling."""
    def get(self, name, default=None):
        if dict.__contains__(self, name):
            return dict.__getitem__(self, name)
        twin = const_twin(name)
        if twin is not None and dict.__contains__(self, twin):
            return dict.__getitem__(self, twin)
        return default


def sha1_text(path):
    return hashlib.sha1(Path(path).read_bytes()).hexdigest()[:16]


def tree_fingerprint(tree):
    digest = hashlib.sha1()
    for path in sorted(Path(tree).rglob("*")):
        if path.is_file():
            digest.update(path.relative_to(tree).as_posix().encode())
            digest.update(path.read_bytes())
    return digest.hexdigest()[:16]


# ---------------------------------------------------------------- compiling

def _run_cl(command, env):
    result = subprocess.run(command + ["-showIncludes"], cwd=ROOT, env=env,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                            errors="replace")
    stdout = result.stdout or ""
    includes = [line.split(":", 2)[-1].strip() for line in stdout.splitlines()
                if line.startswith("Note: including file:")]
    text = "\n".join(l for l in stdout.splitlines() if not l.startswith("Note: including file:"))
    return result.returncode, text, includes


def _classify_includes(includes, tree):
    """Which STLport headers the compile actually read: MSVC skips a missing
    include directory silently, so the swap is proven from /showIncludes."""
    def under(path, root):
        try:
            Path(path).resolve().relative_to(Path(root).resolve())
            return True
        except (ValueError, OSError):
            return False
    return {
        "tree": sum(1 for p in includes if under(p, tree)),
        "current": (sum(1 for p in includes if under(p, CURRENT_TREE))
                    if Path(tree).resolve() != CURRENT_TREE.resolve() else 0),
        "shim": sum(1 for p in includes if any(under(p, ROOT / o) for o in STL_OVERLAYS)),
    }


def header_compile(source, tree, variant):
    """Compile a ledger TU with its STLport include dir swapped for `tree`.

    `variant` is "" (as declared), "-D<knob>", or "-shim", optionally after
    "adapt" (the 4.5.3 allocator const removed, see ALLOCATOR_CONST_DECL).
    Returns (ok, obj, message, include_counts)."""
    source = ROOT / source
    adapt = variant.startswith("adapt")
    tag = hashlib.sha1(("%s|%s|%s" % (source, tree, variant)).encode()).hexdigest()[:12]
    out = OUT / "obj" / (build.obj_path(source).stem + "." + tag + ".obj")
    out.parent.mkdir(parents=True, exist_ok=True)
    original_dir = source.parent
    if adapt:
        text = source.read_text(encoding="utf-8", errors="replace")
        copy = OUT / "adapt" / tag / source.name
        copy.parent.mkdir(parents=True, exist_ok=True)
        copy.write_text(ALLOCATOR_CONST_DECL.sub(r"\1\2", text), encoding="utf-8")
        source = copy
    command, env = build.compiler_command(source, out)
    env = dict(env)
    parts = env.get("INCLUDE", "").split(os.pathsep if os.name == "nt" else ";")
    current = {str(CURRENT_TREE), build.wine_path(CURRENT_TREE)}
    swapped = [build.wine_path(tree) if p in current else p for p in parts]
    if not any(p in current for p in parts):
        # An unmarked unit: give it STLport the way the marker would.
        swapped = [build.wine_path(tree)] + parts
    env["INCLUDE"] = (os.pathsep if os.name == "nt" else ";").join(swapped)
    fo = next(i for i, arg in enumerate(command) if arg.startswith("-Fo"))
    if adapt:
        # Quoted includes of the copy still resolve beside the original.
        command = command[:fo] + ["-I" + build.wine_path(original_dir)] + command[fo:]
        fo += 1
        variant = variant[len("adapt"):].strip()
    if variant == "-shim":
        command = [arg for arg in command
                   if not (arg.startswith(("-I", "/I")) and arg[2:].rstrip("/\\").replace("\\", "/")
                           in STL_OVERLAYS)]
    elif variant:
        command = command[:fo] + [variant] + command[fo:]
    if out.exists():
        out.unlink()
    code, text, includes = _run_cl(command, env)
    if code != 0 and "Cannot open include file" in text:
        extra = [d for d in build._SWEEP_INCLUDE_DIRS if d.exists()]
        env["INCLUDE"] += ";" + ";".join(build.wine_path(d) for d in extra)
        fo = next(i for i, arg in enumerate(command) if arg.startswith("-Fo"))
        command = command[:fo] + ["-I" + build.wine_path(d) for d in extra] + command[fo:]
        code, text, includes = _run_cl(command, env)
    counts = _classify_includes(includes, tree)
    if code != 0 or not out.exists():
        errors = [l.strip() for l in text.splitlines() if " error " in l or "fatal error" in l]
        return False, out, (errors[0] if errors else text.strip()[-200:]), counts
    return True, out, "", counts


def library_compile(src_dir, tree, filename, variant):
    source = Path(src_dir) / filename
    tag = hashlib.sha1(("%s|%s|%s" % (source, tree, variant)).encode()).hexdigest()[:12]
    out = OUT / "lib" / ("%s.%s.%s.obj" % (Path(filename).stem, variant, tag))
    out.parent.mkdir(parents=True, exist_ok=True)
    root = build.vc71_root()
    compiler = root / "Vc7" / "bin" / "cl.exe"
    command = (["wine"] if os.name != "nt" else []) + [str(compiler), "-nologo", "-c"]
    flags = list(LIBRARY_BASE_FLAGS)
    for extra in LIBRARY_VARIANTS[variant]:
        if extra.startswith("-U"):
            flags = [f for f in flags if f != "-D" + extra[2:]]
        else:
            flags.append(extra)
    command += flags + ["-FI" + build.wine_path(Path(src_dir) / "vc_warning_disable.h"),
                        "-I" + build.wine_path(src_dir),
                        "-Fo" + build.wine_path(out), build.wine_path(source)]
    env = build.compiler_environment(root, None)
    sep = os.pathsep if os.name == "nt" else ";"
    env["INCLUDE"] = sep.join([build.wine_path(tree), env["INCLUDE"],
                               build.wine_path(root / "Vc7" / "PlatformSDK" / "Include")])
    if out.exists():
        out.unlink()
    code, text, includes = _run_cl(command, env)
    if code != 0 or not out.exists():
        errors = [l.strip() for l in text.splitlines() if " error " in l or "fatal error" in l]
        return False, out, (errors[0] if errors else text.strip()[-200:])
    return True, out, ""


# ---------------------------------------------------------------- comparing

def first_difference(target, compiled):
    for index, (a, b) in enumerate(zip(target, compiled)):
        if a != b:
            return index
    return min(len(target), len(compiled))


def compare_row(row, symbol_map, obj, *, translate=False):
    """(verdict, detail, symbol): verdict is match / mismatch / missing / error."""
    names = [build.ledger_object_symbol(row)]
    if translate and const_twin(names[0]):
        names.append(const_twin(names[0]))
    last = ("missing", "object does not emit %s" % names[0][:80], names[0])
    for symbol in names:
        probe = dict(row)
        if symbol != names[0]:
            probe["name"] = symbol
            probe["notes"] = re.sub(r"(?:^|;)object-symbol=[^;]*", "", probe.get("notes", ""))
        try:
            patch = build.compile_function(probe, symbol_map, obj)
        except ValueError as error:
            last = ("missing", str(error)[:120], symbol)
            continue
        except SystemExit as error:
            return "error", str(error)[:160], symbol
        target, compiled = patch["target"], patch["bytes"]
        thin = patch["masked"] and patch["concrete"] < build.MIN_LIB_CONCRETE
        if compiled == target and not thin:
            return "match", "", symbol
        at = first_difference(target, compiled)
        detail = "first diff +0x%X/%d: retail %s vs %s" % (
            at, len(target), target[at:at + 6].hex(), compiled[at:at + 6].hex())
        if patch["unresolved"]:
            detail += "; unresolved " + ",".join(sorted(set(patch["unresolved"])))[:120]
        return "mismatch", detail, symbol
    return last


# ---------------------------------------------------------------- the ledger

def ledger_rows():
    rows = [r for r in build.load_function_rows()]
    by_source = collections.defaultdict(list)
    for row in rows:
        by_source[row["source"]].append(row)
    return rows, by_source


def has_marker(source, _cache={}):
    if source not in _cache:
        try:
            _cache[source] = build.source_needs_stlport(ROOT / source)
        except OSError:
            _cache[source] = False
    return _cache[source]


def row_kind(row):
    """The STLport-derived class of a row, or None for game code."""
    source = row["source"]
    match = VENDORED.search(row.get("notes", ""))
    if LIBRARY_COPY.search(source):
        return "library-copy"
    if source.startswith(LIBRARY_HAND):
        return "library-hand"
    if match:
        return "vendored"
    if "_STL" in row["name"]:
        return "header" if has_marker(source) else "unmarked"
    return None


def stl_sources(by_source):
    """Every TU holding at least one STLport-derived row."""
    return sorted(source for source, rows in by_source.items()
                  if any(row_kind(r) for r in rows)
                  and Path(source).suffix.lower() in (".cpp", ".c")
                  and (ROOT / source).exists())


def stratified_sample(sources, count, seed):
    groups = collections.defaultdict(list)
    for source in sources:
        groups["/".join(source.split("/")[:5])].append(source)
    rng = random.Random(seed)
    for members in groups.values():
        rng.shuffle(members)
    picked = []
    while len(picked) < count and any(groups.values()):
        for key in sorted(groups):
            if groups[key] and len(picked) < count:
                picked.append(groups[key].pop())
    return sorted(picked)


# ---------------------------------------------------------------- cache

def load_cache():
    if CACHE.exists():
        data = json.loads(CACHE.read_text(encoding="utf-8"))
        if data.get("version") == CACHE_VERSION:
            return data
    return {"version": CACHE_VERSION, "headers": {}, "library": {}}


def save_cache(cache):
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    tmp = CACHE.with_suffix(".tmp")
    tmp.write_text(json.dumps(cache, indent=0, sort_keys=True), encoding="utf-8")
    os.replace(tmp, CACHE)


# ---------------------------------------------------------------- headers lane

def trial_unit(source, rows, symbol_map, trees, knob_retry):
    """All verdicts for one TU: {tree_tag: {variant: {row_key: [verdict, detail]}}}."""
    result = {"compile": {}, "rows": {}}

    def run(tag, tree, variant, translate):
        ok, obj, message, counts = header_compile(source, tree, variant)
        key = tag + ("" if not variant else " " + variant)
        result["compile"][key] = [ok, message[:200], counts]
        verdicts = {}
        for row in rows:
            row_key = row["target_rva"]
            if not ok:
                verdicts[row_key] = ["compile-error", message[:160], ""]
            else:
                verdicts[row_key] = list(compare_row(row, symbol_map, obj, translate=translate))
        result["rows"][key] = verdicts
        try:
            obj.unlink()
        except OSError:
            pass
        return verdicts

    control = run("current", CURRENT_TREE, "", False)
    adaptable = ALLOCATOR_CONST_DECL.search(
        (ROOT / source).read_text(encoding="utf-8", errors="replace"))
    for tag, tree in trees:
        base = run(tag, tree, "", True)
        prefix = ""
        if adaptable and not result["compile"][tag][0]:
            base = run(tag, tree, "adapt", True)
            prefix = "adapt "
        if not knob_retry:
            continue
        lost = [k for k, v in base.items() if v[0] != "match" and control[k][0] == "match"]
        if not lost:
            continue
        for knob in KNOBS:
            variant = knob if knob == "-shim" else "-D" + knob
            if knob == "-shim" and not any(
                    overlay in line for overlay in STL_OVERLAYS for line in
                    (ROOT / source).read_text(encoding="utf-8", errors="replace").splitlines()
                    if line.startswith("// cl:")):
                continue
            run(tag, tree, prefix + variant, True)
    return result


def headers_lane(args):
    rows, by_source = ledger_rows()
    sources = args.sources or stl_sources(by_source)
    if args.sources:
        sources = [Path(s).as_posix() for s in args.sources]
    elif not args.all:
        sources = stratified_sample(sources, args.sample, args.seed)
    trees = [("4.6", TREE_46)]
    if args.tree_dir:
        trees.append((args.tag or Path(args.tree_dir).name, Path(args.tree_dir).resolve()))
    cache = load_cache()
    fingerprints = {tag: tree_fingerprint(tree) for tag, tree in [("current", CURRENT_TREE)] + trees}
    symbol_map = TranslatingSymbolMap(build.load_symbol_map())
    todo = []
    for source in sources:
        key = "%s|%s|%s" % (source, sha1_text(ROOT / source),
                            ",".join("%s=%s" % kv for kv in sorted(fingerprints.items())))
        cached = cache["headers"].get(source)
        if cached and cached.get("key") == key and not args.force:
            continue
        todo.append((source, key))
    log("headers: %d unit(s) selected, %d to compile, pool %d"
        % (len(sources), len(todo), args.pool))
    done = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.pool) as pool:
        futures = {pool.submit(trial_unit, source, by_source[source], symbol_map, trees,
                               not args.no_knobs): (source, key) for source, key in todo}
        for future in concurrent.futures.as_completed(futures):
            source, key = futures[future]
            try:
                result = future.result()
            except Exception as error:  # one broken unit must not lose the pass
                result = {"compile": {"current": [False, "trial crashed: %s" % error, {}]},
                          "rows": {}}
            result["key"] = key
            cache["headers"][source] = result
            done += 1
            if done % 25 == 0 or done == len(todo):
                save_cache(cache)
                log("  %d/%d units" % (done, len(todo)))
    save_cache(cache)


# ---------------------------------------------------------------- library lane

def masked_hits(body, relocs, blob, text_rva):
    fixed = bytearray(b"\x01" * len(body))
    for offset, kind, symbol in relocs:
        for step in range(4):
            if offset + step < len(fixed):
                fixed[offset + step] = 0
    pattern = b"".join(re.escape(bytes([byte])) if fixed[index] else b"."
                       for index, byte in enumerate(body))
    return [m.start() + text_rva for m in re.finditer(pattern, blob, re.DOTALL)]


def library_lane(args):
    src_dir = Path(args.src_dir).resolve() if args.src_dir else SRC_46
    tree = Path(args.tree_dir).resolve() if args.tree_dir else TREE_46
    tag = args.tag or "4.6"
    rows, by_source = ledger_rows()
    by_symbol = collections.defaultdict(list)
    for row in rows:
        by_symbol[build.ledger_object_symbol(row)].append(row)
    starts = sorted(((int(r["target_rva"], 16), int(r["target_rva"], 16) + int(r["target_size"]), r)
                    for r in build.load_all_function_rows()), key=lambda t: (t[0], t[1]))
    import bisect
    keys = [s for s, _, _ in starts]

    def owner(rva):
        index = bisect.bisect_right(keys, rva) - 1
        if index >= 0 and starts[index][0] <= rva < starts[index][1]:
            return starts[index][2]
        return None

    image, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    blob = image[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    symbol_map = TranslatingSymbolMap(build.load_symbol_map())
    cache = load_cache()
    jobs = [(f, v) for f in LIBRARY_SOURCES if (src_dir / f).exists()
            for v in (args.variants or LIBRARY_VARIANTS)]
    log("library: %d compile(s) of %s src, pool %d" % (len(jobs), tag, args.pool))

    def one(job):
        filename, variant = job
        ok, obj, message = library_compile(src_dir, tree, filename, variant)
        entry = {"ok": ok, "message": message[:200], "rows": {}, "placed": []}
        if not ok:
            return job, entry
        for symbol in sorted(build.defined_code_symbols(obj)):
            if not place_bodies.placeable(symbol):
                continue
            ledger_hits = by_symbol.get(symbol) or by_symbol.get(const_twin(symbol) or "", [])
            for row in ledger_hits:
                verdict = compare_row(dict(row, name=symbol, notes=""), symbol_map, obj)
                entry["rows"][row["target_rva"]] = [verdict[0], verdict[1], symbol]
            if ledger_hits:
                continue
            try:
                body, relocs = build.read_object_symbol_bytes(obj, symbol)
            except Exception:
                continue
            body = body.rstrip(b"\xcc")
            if len(body) < 20:
                continue
            hits = masked_hits(body, relocs, blob, text["rva"])
            if len(hits) == 1:
                held = owner(hits[0])
                entry["placed"].append([symbol, "0x%08X" % hits[0], len(body),
                                        held["name"] if held else "",
                                        "0x%s" % held["target_rva"][2:].upper() if held else ""])
            elif hits:
                entry["placed"].append([symbol, "%d hits" % len(hits), len(body), "", ""])
        try:
            obj.unlink()
        except OSError:
            pass
        return job, entry

    results = {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.pool) as pool:
        for job, entry in pool.map(one, jobs):
            results["%s|%s" % job] = entry
            state = "ok" if entry["ok"] else "FAIL " + entry["message"][:100]
            log("  %-22s %-17s %s rows=%d placed=%d" % (
                job[0], job[1], state, len(entry["rows"]),
                sum(1 for p in entry["placed"] if p[1].startswith("0x"))))
    cache["library"][tag] = {"src": str(src_dir), "tree": str(tree), "results": results}
    save_cache(cache)


# ---------------------------------------------------------------- report

def classify(rows_by_rva, cache):
    """Final verdict per row across both lanes."""
    out = {}
    for source, unit in cache["headers"].items():
        control = unit["rows"].get("current", {})
        for rva, verdict in unit["rows"].get("4.6", {}).items():
            row = rows_by_rva.get((source, rva))
            if row is None:
                continue
            ctl = control.get(rva, ["?", "", ""])
            knob = ""
            adapted = unit["rows"].get("4.6 adapt", {}).get(rva)
            if verdict[0] == "compile-error" and adapted:
                verdict = adapted
                knob = "adapt"
            if verdict[0] == "match":
                state = "match-4.6"
            elif ctl[0] != "match":
                state = "control-fail"
            else:
                state = "mismatch"
                for variant, verdicts in unit["rows"].items():
                    if (variant.startswith("4.6 ") and variant != "4.6 adapt"
                            and verdicts.get(rva, [""])[0] == "match"):
                        knob = variant.split(" ", 1)[1].replace("adapt ", "adapt+")
                        state = "match-knob"
                        break
            out[(source, rva)] = {"lane": "headers", "state": state, "knob": knob,
                                  "control": ctl[0], "detail": "" if state.startswith("match")
                                  else (verdict[1] if ctl[0] == "match" else ctl[1]),
                                  "symbol": verdict[2] if len(verdict) > 2 else ""}
    library = cache["library"].get("4.6", {}).get("results", {})
    lib_best = {}
    for job, entry in library.items():
        variant = job.split("|", 1)[1]
        for rva, verdict in entry["rows"].items():
            best = lib_best.get(rva)
            if best is None or (verdict[0] == "match" and best[0] != "match") or (
                    verdict[0] == "match" and variant == "upstream-staticx"):
                lib_best[rva] = (verdict[0], variant, job.split("|", 1)[0], verdict[1])
    return out, lib_best


def report(args):
    rows, by_source = ledger_rows()
    rows_by_rva = {(r["source"], r["target_rva"]): r for r in rows}
    cache = load_cache()
    verdicts, lib_best = classify(rows_by_rva, cache)
    REPORT.parent.mkdir(parents=True, exist_ok=True)
    fields = ["kind", "rva", "size", "name", "source", "header_46", "knob", "library_46",
              "library_variant", "library_src", "detail"]
    out_rows = []
    summary = collections.Counter()
    bytes_by = collections.Counter()
    collateral = collections.Counter()
    for (source, rva), verdict in sorted(verdicts.items(), key=lambda kv: (kv[0][0], kv[0][1])):
        row = rows_by_rva[(source, rva)]
        kind = row_kind(row)
        if kind is None:
            # Game code compiled in the same unit: only a regression is reported.
            collateral[verdict["state"]] += 1
            if verdict["state"] in ("match-4.6", "control-fail"):
                continue
            kind = "collateral"
        lib = lib_best.get(rva)
        size = int(row["target_size"])
        out_rows.append({
            "kind": kind, "rva": rva, "size": size, "name": row["name"], "source": source,
            "header_46": verdict["state"], "knob": verdict["knob"],
            "library_46": lib[0] if lib else "", "library_variant": lib[1] if lib else "",
            "library_src": lib[2] if lib else "",
            "detail": verdict["detail"][:200] if not verdict["state"].startswith("match")
            else ("" if not lib or lib[0] == "match" else lib[3][:200]),
        })
        summary[(kind, verdict["state"])] += 1
        bytes_by[(kind, verdict["state"])] += size
    # Library-lane rows the headers lane did not cover.
    covered = {(r["source"], r["rva"]) for r in out_rows}
    for rva, lib in sorted(lib_best.items()):
        for row in [r for r in rows if r["target_rva"] == rva]:
            if (row["source"], rva) in covered:
                continue
            kind = row_kind(row) or "library-src"
            out_rows.append({"kind": kind, "rva": rva, "size": row["target_size"],
                             "name": row["name"], "source": row["source"],
                             "header_46": "not-sampled", "knob": "",
                             "library_46": lib[0], "library_variant": lib[1],
                             "library_src": lib[2], "detail": "" if lib[0] == "match" else lib[3][:200]})
            summary[(kind, "not-sampled")] += 1
    with REPORT.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, lineterminator="\n")
        writer.writeheader()
        writer.writerows(out_rows)
    print("wrote %s (%d rows)" % (REPORT.relative_to(ROOT).as_posix(), len(out_rows)))
    print("\nheaders lane (%d units):" % len(cache["headers"]))
    for kind in ["header", "library-copy", "library-hand", "vendored", "unmarked", "collateral"]:
        states = {s: c for (k, s), c in summary.items() if k == kind}
        if states:
            print("  %-13s " % kind + "  ".join("%s=%d (%dB)" % (s, c, bytes_by[(kind, s)])
                                                 for s, c in sorted(states.items())))
    print("  game-code rows in the same units: " + "  ".join(
        "%s=%d" % kv for kv in sorted(collateral.items())))
    knobs = collections.Counter(r["knob"] for r in out_rows if r["knob"])
    if knobs:
        print("  rescuing knobs: " + "  ".join("%s=%d" % kv for kv in knobs.most_common()))
    reasons = collections.Counter()
    for unit in cache["headers"].values():
        state = unit["compile"].get("4.6")
        if state and not state[0]:
            reasons[re.sub(r"^.*?(error C\d+|fatal error C\d+)", r"\1", state[1])[:90]] += 1
    if reasons:
        print("  4.6 compile failures: %d units" % sum(reasons.values()))
        for reason, count in reasons.most_common(8):
            print("    %4d  %s" % (count, reason))
    for tag, lib in cache["library"].items():
        print("\nlibrary lane %s:" % tag)
        variants = collections.defaultdict(collections.Counter)
        for job, entry in lib["results"].items():
            variant = job.split("|", 1)[1]
            variants[variant]["compiled" if entry["ok"] else "failed"] += 1
            for verdict in entry["rows"].values():
                variants[variant]["row-" + verdict[0]] += 1
            for placed in entry["placed"]:
                if placed[1].startswith("0x"):
                    variants[variant]["placed-held" if placed[3] else "placed-new"] += 1
        for variant, counts in sorted(variants.items()):
            print("  %-17s " % variant + "  ".join("%s=%d" % kv for kv in sorted(counts.items())))


HEADER_MATCH = ("match-4.6", "match-knob")


def trial_failed(row):
    """A report row the trial saw fail under 4.6 with every knob: the unit's own compile
    (headers lane), or, for a unit never compiled under 4.6, pristine src/ (library
    lane). A control failure is the trial's own artifact, not a 4.6 verdict."""
    if row["header_46"] in HEADER_MATCH + ("control-fail",):
        return False
    if row["kind"] == "collateral" or row["header_46"] != "not-sampled":
        return row.get("library_46") != "match"
    return row.get("library_46") == "mismatch"


STLPORT_LINE = re.compile(r"^// stlport[ \t\r]*$", re.M)


def opted_into_453(source):
    """True when the file carries the `// stlport` line the lane's move rewrites. A
    file without it compiles none of STLport's headers (its STL names, if any, are
    private declarations), so a trial row of it built the same bytes under 4.6 as
    under 4.5.3: it shows nothing about the unit, and the marker move cannot apply."""
    try:
        return STLPORT_LINE.search((ROOT / source).read_text(encoding="utf-8-sig", errors="replace")) is not None
    except OSError:
        return False


def queue_files():
    """The repoint queue as data, most bytes first: one dict per file with the
    `// stlport` line (opted_into_453) but not yet the `// stlport46` opt-in, holding
    report rows that matched under 4.6 and that the ledger still holds matched under
    the same identity and extent. `rows` are those
    leads; `knobs` every knob a live row of the file needed (its game code included);
    `fails` the file's live rows the trial saw fail (trial_failed: a whole-file move
    must fix them); `lead` is "unit" when the headers lane compiled this unit itself
    for every lead, else "library" (pristine 4.6 src/ reproduced the bodies)."""
    if not REPORT.exists():
        raise SystemExit("no %s yet: run `stlport_trial.py headers` and `report`"
                         % REPORT.relative_to(ROOT).as_posix())
    with REPORT.open(encoding="utf-8", newline="") as handle:
        report = list(csv.DictReader(handle))
    rows = [r for r in report if r["kind"] not in ("collateral",)
            and (r["header_46"] in HEADER_MATCH or r["library_46"] == "match")]
    # The report is historical lead evidence. Do not re-serve migrated/deleted
    # rows, changed extents, or names that the current ledger no longer holds.
    candidates = {(r["source"], r["rva"], r["name"], int(r["size"])) for r in rows}
    sources = {r["source"] for r in report}
    live, held = set(), set()
    with build.FUNCTIONS.open(encoding="utf-8", newline="") as handle:
        for r in csv.DictReader(handle):
            if r["status"] == "matched" and r["source"] in sources:
                held.add((r["source"], r["target_rva"]))
                key = (r["source"], r["target_rva"], r["name"], int(r["target_size"]))
                if key in candidates:
                    live.add(key)
    by_source = collections.defaultdict(list)
    for row in rows:
        if ((row["source"], row["rva"], row["name"], int(row["size"])) in live
                and not stlport_overlay.selected(ROOT / row["source"]) and opted_into_453(row["source"])):
            by_source[row["source"]].append(row)
    report_by_source = collections.defaultdict(list)
    for row in report:
        if row["source"] in by_source and (row["source"], row["rva"]) in held:
            report_by_source[row["source"]].append(row)
    files = []
    for source, members in by_source.items():
        others = report_by_source[source]
        files.append({
            "source": source, "rows": members, "bytes": sum(int(r["size"]) for r in members),
            "knobs": sorted({r["knob"] for r in others if r["knob"] and r["header_46"] in HEADER_MATCH}),
            "fails": len({r["rva"] for r in others if trial_failed(r)}),
            "lead": "unit" if all(r["header_46"] in HEADER_MATCH for r in members) else "library"})
    return sorted(files, key=lambda f: -f["bytes"])


def queue(args):
    for entry in queue_files():
        source, members, knobs = entry["source"], entry["rows"], entry["knobs"]
        if args.tsv:
            for r in members:
                print("\t".join([r["rva"], r["size"], source, r["kind"], r["header_46"],
                                 r["knob"], r["library_46"], r["name"]]))
        else:
            print("%6d B %4d rows  %s%s%s" % (entry["bytes"], len(members), source,
                                              ("  knobs " + ",".join(knobs)) if knobs else "",
                                              ("  trial-fails %d" % entry["fails"]) if entry["fails"] else ""))


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="lane", required=True)
    pool = min(2, int(os.environ.get("BUILD_POOL", "1")))
    h = sub.add_parser("headers")
    h.add_argument("sources", nargs="*")
    h.add_argument("--sample", type=int, default=300)
    h.add_argument("--all", action="store_true")
    h.add_argument("--seed", type=int, default=462)
    h.add_argument("--no-knobs", action="store_true")
    h.add_argument("--force", action="store_true")
    h.add_argument("--tree-dir", help="an extra STLport include dir to trial beside 4.6")
    h.add_argument("--tag")
    h.add_argument("--pool", type=int, default=pool)
    lib = sub.add_parser("library")
    lib.add_argument("--src-dir")
    lib.add_argument("--tree-dir")
    lib.add_argument("--tag")
    lib.add_argument("--variants", nargs="*", choices=sorted(LIBRARY_VARIANTS))
    lib.add_argument("--pool", type=int, default=pool)
    sub.add_parser("report")
    q = sub.add_parser("queue")
    q.add_argument("--tsv", action="store_true")
    args = parser.parse_args()
    {"headers": headers_lane, "library": library_lane, "report": report, "queue": queue}[args.lane](args)


if __name__ == "__main__":
    main()
