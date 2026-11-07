#!/usr/bin/env python3
"""EXIT-LINK MODE: link our objects only, at a non-retail base, with no /FORCE.

The census (`link_census.py`) links at retail's base under /FORCE and reports
what would stop a link. This mode answers the exit test's own question: with
nothing forced, no stubs, no retail-byte fillers and no alias scaffold, which
names still stop a real link at a base retail never used? It is a measurement,
never a census: it records nothing in `reverse/`, changes no headline and
credits no row.

It leaves out the 17 placement-only objects the reviewed index proves nothing
outside them references: the 15 `Code/gen_small/uw_gen_NNN.cpp` funclet TUs and
the two generated thunk TUs (`gthunks_000_admitted.cpp`,
`thunks_000_admitted.cpp`). Their bytes place retail funclets and thunks at
retail RVAs; at a non-retail base each kept parent emits its own funclets, and
the omitted definitions have no consumer. Omitting them is proved, not assumed:

  * every omitted external definition has no referrer in any kept object
    (undefined externals, weak externals and `.drectve` /INCLUDE entries,
    parsed as the census parses them: case-insensitive and quote-aware);
  * every omitted `gen-funclet` row is an associative `.text$x` COMDAT whose
    parent section lives in the same object and whose parent EH data names it
    (a structural check, not the proof: that synthetic parent is omitted too);
  * each omitted funclet RVA appears in the verified associative funclet
    locations of a KEPT parent (`eh_verify.verified_funclet_locations` on an
    EXACT parent), so a kept object really emits the funclet the omission
    removes. Uncovered funclets refuse the omission. `eh_verify --all` is
    reported as a global check, but its baselined failures are not accepted as
    this proof.

Link setup is the census's own inputs, without the scaffolds: every matched
row's object (code and data), import libraries generated from retail's import
table for the `__imp_` names the objects reference, the /MD runtime libraries,
and the CRT's own absolute `__except_list` (exsup.asm defines it 0; it is not a
stub). No `/FORCE`, no `stubs.obj`, no `alias.obj`, no filler objects.

Objects must be prepared OUTSIDE this tool. `python3 tools/link_census.py
--build` (or `./build.sh`) writes `build/match`; the published census's objects
can be restored first with `python3 tools/link_check.py --fetch-index` and then
`link_census.py --build`. `--link`, `--plan --objects` and `--eh-proof` consume
those objects READ-ONLY and require the full expected population; they never
compile, extract a library member, generate a shim or write outside
`build/exit_link/`. A missing or stale object refuses with the command to run.
Every object is checked with `build.compile_is_current` (source and every
recorded header), and result.json records that rule and the index's date and
commit.

  python3 tools/exit_link.py --plan              # dry run: population + proof, no link
  python3 tools/exit_link.py --plan --objects    # also prove omission from build/match objects
  python3 tools/exit_link.py --plan --index      # also cross-check the published census index
  python3 tools/exit_link.py --eh-proof          # eh_verify --all on the current objects
  python3 tools/exit_link.py --link              # sandbox or hosted runner: read-only proof + exit link
  python3 tools/exit_link.py --diagnostic        # isolated int3-stub image, never credit
  python3 tools/exit_link.py --report            # summarise the last run

The production entry point is `python3 tools/link_cycle.py --exit-link ...`,
which delegates here (AGENTS.md: a new tools file is called by another tool).
Outputs live in `build/exit_link/`: result.json, errors.tsv, link.log (the raw
linker output), exit.rsp and the generated import libraries. Nothing here is
authoritative for LINKING or recovery credit; only the census records those.
"""
# Both modes request a map, relocations, all retail exports and resources.
# --diagnostic alone adds distinct trap bodies and permits uncovered omitted
# funclets (retained in its proof report). Its outputs never enter exit_link/.
# --stub-seed (diagnostic only) starts from an earlier link's stubbed.tsv: a pass
# costs ~12 minutes on srv1, and each round of new names was another pass.
import argparse
import collections
import concurrent.futures
import csv
import functools
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import time
import tempfile
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as census  # noqa: E402
import link_cycle  # noqa: E402

OUT = ROOT / "build" / "exit_link"
# Retail links at 0x400000. The exit test needs a base retail never used, so a
# stale 0x400000 literal in our code cannot pass as a working image.
BASE = 0x10000000
ENTRY = "WinMainCRTStartup"
# The harness patches these IAT slots before entering the image.
HARNESS_IMPORTS = {"SHGetSpecialFolderPathW": 16, "GetVersion": 0, "GetVersionExA": 4}
PLACEMENT_DIR = "Code/gen_small"
# The reviewed population: the index's 2,395 `uw_gen` names, 69 `gthunks` names
# and 7 `thunks` names come from exactly these files. A new file changes the
# measurement, so the mode refuses rather than silently omitting it.
PLACEMENT_BASENAMES = frozenset(
    [f"uw_gen_{index:03d}.cpp" for index in range(15)]
    + ["gthunks_000_admitted.cpp", "thunks_000_admitted.cpp"])
EXPECTED_PLACEMENT_SOURCES = len(PLACEMENT_BASENAMES)
PLACEMENT_PATTERN = re.compile(
    rf"^{re.escape(PLACEMENT_DIR)}/(uw_gen_\d+\.cpp|gthunks_\d+_admitted\.cpp|thunks_\d+_admitted\.cpp)$")
TOOL_FILES = ("exit_link.py", "link_census.py", "link_cycle.py", "build.py", "eh_verify.py",
              "vtable_bridge.py", "image_report.py", "coffar.py")


def is_placement_source(source):
    """True for a placement-only TU by name; `check_population` judges the set."""
    return bool(PLACEMENT_PATTERN.match(PurePosixPath(str(source).replace("\\", "/")).as_posix()))


def placement_sources(rows):
    return sorted({row["source"] for row in rows if is_placement_source(row["source"])})


def placement_rows(rows):
    return [row for row in rows if is_placement_source(row["source"])]


def placement_objects(rows):
    """{object: source} of the placement-only TUs a matched row names."""
    return {build.row_object(row): row["source"] for row in placement_rows(rows)}


def check_population(sources):
    """Refuse a population the reviewed measurement did not cover."""
    found = {PurePosixPath(str(source).replace("\\", "/")).as_posix() for source in sources}
    expected = {f"{PLACEMENT_DIR}/{name}" for name in PLACEMENT_BASENAMES}
    if found == expected:
        return None
    return (f"the placement population is {len(found)} source(s), not the reviewed "
            f"{EXPECTED_PLACEMENT_SOURCES}: missing {sorted(expected - found)[:5]}, "
            f"unreviewed {sorted(found - expected)[:5]}")


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def tool_digests():
    return {**{name: digest(ROOT / "tools" / name) for name in TOOL_FILES},
            "reverse/exports.csv": digest(ROOT / "reverse/exports.csv"),
            "reverse/data_ledger.csv": digest(ROOT / "reverse/data_ledger.csv"),
            "retail": digest(build.EXE)}


# ---------------------------------------------------------------- COFF proof
def coff_view(path):
    """(sections, symbols, raw bytes) through link_cycle's COFF reader."""
    data = Path(path).read_bytes()
    sections, symbols = link_cycle.parse_coff(data)
    return sections, symbols, data


def coff_references(path, data):
    """Names an object references, through the census's own directive reader.

    `census.object_symbols` matches `.drectve` /INCLUDE case-insensitively and
    strips quotes (`/include:?u`, `/INCLUDE:"?u"`), so a directive spelling
    cannot hide a kept consumer. It also supplies the undefined externals and
    weak externals.
    """
    _defined, referenced, weak, _alternates, includes = census.object_symbols(Path(path), data)
    return referenced | {name for name, _default in weak} | includes


def external_definitions(symbols):
    """Names an object defines with external linkage."""
    return {symbol.name for symbol in symbols.values()
            if symbol.sec > 0 and symbol.cls == link_cycle.EXTERNAL}


@functools.lru_cache(maxsize=64)
def parsed_funclet_object(path_text):
    """eh_verify's COFF view, parsed once per omitted object (hundreds of rows)."""
    import eh_verify
    return eh_verify.Obj(Path(path_text))


def funclet_parent_emits(path, name):
    """(proved, why) that the funclet `name` is emitted by a parent in `path`.

    A compiler-emitted funclet is an ASSOCIATIVE `.text$x` COMDAT: its section
    aux record names the function's section, and the function's EH data (its
    own or an associative `.xdata$x`) relocates to the funclet. Anything else
    (a standalone body, or a parent outside this object) is unproven.
    """
    try:
        obj = parsed_funclet_object(str(path))
    except (OSError, struct.error) as exc:
        return False, f"unreadable object: {exc}"
    symbol = obj.by_name.get(name)
    if symbol is None or not symbol["section"]:
        return False, "the object does not define the funclet symbol"
    section = obj.sections[symbol["section"] - 1]
    parent = section["assoc"]
    if not parent:
        return False, "standalone body, not an associative .text$x funclet"
    if not 1 <= parent <= len(obj.sections):
        return False, "parent section out of range"
    if not any(other["section"] == parent and other["storage"] in (2, 3)
               for other in obj.symbols.values()):
        return False, "parent section holds no function symbol"
    named = False
    for other in obj.sections:
        if other["index"] != parent and other["assoc"] != parent:
            continue
        for _offset, index, _type in other["relocs"]:
            target = obj.symbols.get(index)
            if target is not None and target["section"] == section["index"]:
                named = True
                break
        if named:
            break
    if not named:
        return False, "parent EH data does not name the funclet"
    return True, "associative .text$x funclet of a parent in the same object"


def kept_funclet_locations(rows, omitted_sources, image=None):
    """{retail RVA: [(object, parent, label)]} from EXACT kept parents' funclets.

    `eh_verify.verified_funclet_locations` returns a parent's `$L` funclet
    locations only when its EH data is EXACT; a baselined failure is debt, not
    proof. One object parse per kept TU, then one verdict per row.
    """
    import eh_verify
    image = image or eh_verify.Image()
    groups = collections.defaultdict(list)
    for row in rows:
        if row["source"] in omitted_sources or row["source"].lower().endswith(build.LIB_SUFFIX):
            continue
        groups[build.row_object(row)].append(row)
    found = collections.defaultdict(list)
    for path, group in groups.items():
        try:
            obj = eh_verify.Obj(path)
        except (OSError, ValueError, IndexError, struct.error):
            continue
        for row in group:
            name = build.ledger_object_symbol(row)
            if build.is_funclet_row(row, name):
                continue
            rva = int(row["target_rva"], 16)
            if eh_verify.verify_row(image, obj, name, rva) != ("EXACT", ""):
                continue
            for label, location in eh_verify.verified_funclet_locations(image, obj, name, rva).items():
                found[location].append((path.name, name, label))
    return found


def uncovered_funclets(rows, locations):
    """The omitted funclet rows whose RVA no EXACT kept parent emits."""
    return [{"name": row["name"], "target_rva": row["target_rva"], "source": row["source"]}
            for row in rows if int(row["target_rva"], 16) not in locations]


def omission_proof(rows, present=None, expected=None):
    """Prove the 17 placement-only objects can be left out.

    `present`/`expected` are the prepared object inventory. Without them only
    the ledger population is reported. With them, EVERY kept object must exist
    and parse, or the proof fails: an uninspected consumer cannot leave a clean
    proof. The required funclet proof is `kept_funclet_locations`: each omitted
    funclet RVA must be a verified location of an EXACT kept parent.
    """
    sources = placement_sources(rows)
    problem = check_population(sources)
    omitted = placement_objects(rows)
    result = {
        "sources": sources,
        "source_count": len(sources),
        "population_problem": problem,
        "rows": len(placement_rows(rows)),
        "funclet_rows": 0,
        "funclet_proven": 0,
        "funclet_covered": 0,
        "uncovered_funclets": [],
        "kept_funclet_locations": 0,
        "unproven": [],
        "inspection_failures": [],
        "missing_objects": [],
        "outside_referrers": {},
        "exclusive_count": 0,
        "exclusive_names": [],
        "objects": [{"object": path.name, "source": source,
                     "rows": sum(1 for row in rows if row["source"] == source)}
                    for path, source in sorted(omitted.items(), key=lambda item: item[1])],
    }
    if problem:
        return result
    funclets = [row for row in placement_rows(rows)
                if build.is_funclet_row(row, build.ledger_object_symbol(row))]
    result["funclet_rows"] = len(funclets)
    if present is None:
        return result
    expected = list(present) if expected is None else list(expected)
    omitted_paths = set(omitted)
    kept = [path for path in expected if path not in omitted_paths]
    defined = {}
    for path in omitted_paths:
        if not path.exists():
            result["missing_objects"].append(path.name)
            defined[path] = set()
            continue
        try:
            _sections, symbols, _data = coff_view(path)
        except (OSError, ValueError, IndexError, struct.error) as exc:
            result["unproven"].append({"object": path.name, "source": omitted[path],
                                       "symbol": "", "why": f"unreadable object: {exc}"})
            defined[path] = set()
            continue
        defined[path] = external_definitions(symbols)
    by_name = collections.defaultdict(set)
    for path, names in defined.items():
        for name in names:
            by_name[name].add(path)
    kept_definitions = set()
    outside = collections.defaultdict(set)
    for path in kept:
        if not path.exists():
            result["inspection_failures"].append({"object": path.name, "why": "missing object"})
            continue
        try:
            _sections, symbols, data = coff_view(path)
        except (OSError, ValueError, IndexError, struct.error) as exc:
            result["inspection_failures"].append({"object": path.name, "why": f"unreadable object: {exc}"})
            continue
        kept_definitions |= external_definitions(symbols)
        for name in coff_references(path, data) & by_name.keys():
            outside[name].add(path.name)
    result["outside_referrers"] = {name: sorted(objects) for name, objects in sorted(outside.items())}
    exclusive = sorted(name for name in by_name if name not in kept_definitions)
    result["exclusive_names"] = exclusive
    result["exclusive_count"] = len(exclusive)
    for row in funclets:
        path, name = build.row_object(row), build.ledger_object_symbol(row)
        if not path.exists():
            continue
        proved, why = funclet_parent_emits(path, name)
        if proved:
            result["funclet_proven"] += 1
        else:
            result["unproven"].append({"object": path.name, "source": row["source"],
                                       "symbol": name, "why": why})
    locations = kept_funclet_locations(rows, set(sources))
    result["kept_funclet_locations"] = len(locations)
    result["uncovered_funclets"] = uncovered_funclets(funclets, locations)
    result["funclet_covered"] = len(funclets) - len(result["uncovered_funclets"])
    result["missing_objects"] = sorted(result["missing_objects"])
    result["inspection_failures"] = sorted(result["inspection_failures"], key=lambda item: item["object"])
    return result


# ---------------------------------------------------------------- EH proof
def eh_proof(rows):
    """`eh_verify --all`'s verdict, with the baseline's debt separated out."""
    import eh_verify
    rows = [row for row in rows if not row["source"].lower().endswith(build.LIB_SUFFIX)]
    results, missing = eh_verify.verify(rows)
    counts = collections.Counter(verdict for verdict, _detail, _source in results.values())
    baseline = eh_verify.load_baseline()
    failing = {key: value for key, value in results.items() if value[0] != "EXACT"}
    new = {key: value for key, value in failing.items() if key not in baseline}
    return {
        "rows_with_eh": len(results),
        "verdicts": dict(counts),
        "not_exact": len(failing),
        "baselined": len(failing) - len(new),
        "unproven": [{"name": key[0], "target_rva": key[1], "verdict": value[0],
                      "detail": value[1], "source": value[2]}
                     for key, value in sorted(new.items())],
        "missing_objects": missing,
    }


# ---------------------------------------------------------------- index proof
def index_definers(index):
    """{name: {object position}} from the index's strong and comdat tables."""
    definers = {}
    for table in ("strong", "comdat"):
        for name, entries in (index.get(table) or {}).items():
            found = definers.setdefault(name, set())
            if table == "strong":
                found.update(entries)
            else:
                found.update(entry[0] for entry in entries)
    return definers


def index_positions(index, omitted_names):
    objects = list(index.get("objects") or [])
    positions = {name: position for position, name in enumerate(objects)}
    return positions, {positions[name] for name in omitted_names if name in positions}


def index_proof(index, omitted_names):
    """Cross-check the published census index: exclusive names and outside touches.

    `strong`/`comdat` name definers by object position; `touches` names what
    each object references. A name every definer of which is an omitted object
    is a definition the exit link loses; any non-omitted object touching it
    would be a consumer the omission breaks.
    """
    positions, omitted_positions = index_positions(index, omitted_names)
    definers = index_definers(index)
    exclusive = {name for name, where in definers.items()
                 if where and where <= omitted_positions}
    outside = {}
    for name, touched in (index.get("touches") or {}).items():
        if positions.get(name) in omitted_positions:
            continue
        hit = sorted(set(touched) & exclusive)
        if hit:
            outside[name] = hit
    return {"objects": len(omitted_positions), "defined_names": len(definers),
            "exclusive_names": len(exclusive), "outside_referrers": outside,
            "exclusive_sample": sorted(exclusive)[:10]}


def load_index():
    import link_check
    return link_check.load_index()


def published_index_meta():
    """The census index's date and commit, when this checkout has one."""
    try:
        return load_index().get("meta")
    except (SystemExit, OSError, ValueError):
        return None


def last_census():
    path = census.OUT / "census.json"
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None


def index_measurement(index, omitted_names, previous=None):
    """What the reviewed index predicts the mode removes, labelled a prediction."""
    proof = index_proof(index, omitted_names)
    predicted = None
    if previous and isinstance(previous.get("unresolved"), dict):
        unresolved = set(previous["unresolved"])
        _positions, omitted = index_positions(index, omitted_names)
        exclusive = {name for name, where in index_definers(index).items()
                     if where and where <= omitted}
        gone = exclusive & unresolved
        predicted = {"census": {key: previous.get(key) for key in ("when", "commit", "rules")},
                     "unresolved_in_census": len(unresolved),
                     "exclusive_unresolved_gone": len(gone),
                     "unresolved_left": len(unresolved - gone)}
    return {"proof": proof, "prediction": predicted}


# ---------------------------------------------------------------- link
EXPORT_UNOWNED = "(export unowned)"


def export_sources(rows):
    """Attribute retail export names to the ledger owner of their exported RVA."""
    with (ROOT / "reverse/exports.csv").open(newline="", encoding="utf-8") as handle:
        exported = {row["name"]: int(row["rva"], 16) for row in csv.DictReader(handle)}
    wanted = set(exported.values())
    owners = collections.defaultdict(set)
    for row in rows:
        try:
            rva = int(row["target_rva"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        if rva in wanted and row.get("source"):
            owners[rva].add(row["source"])
    return {name: ", ".join(sorted(owners[rva])) or EXPORT_UNOWNED
            for name, rva in exported.items()}


def blockers_from_errors(lines, exports_of=None):
    """[(source, missing names, sample)] from errors.tsv rows, most missing first."""
    missing = collections.defaultdict(set)
    exports_of = exports_of or {}
    for row in csv.DictReader(lines, delimiter="\t"):
        if row["code"] not in ("LNK2001", "LNK2019"):
            continue
        source = row.get("source", "")
        if row.get("object", "").lower().endswith(".exp") and (not source or source == EXPORT_UNOWNED):
            source = exports_of.get(row["symbol"], EXPORT_UNOWNED)
        if not source:
            continue
        for source in source.split(", "):
            path = source.replace(chr(92), "/")
            at = path.find("/Code/")
            missing[path[at + 1:] if at >= 0 else path].add(row["symbol"])
    return [(source, len(names), sorted(names)[0])
            for source, names in sorted(missing.items(), key=lambda item: (-len(item[1]), item[0]))]


def write_blockers(errors, commit):
    """reverse/exit_link_blockers.tsv: what the fleet's link tier serves first."""
    result_path = Path(errors).with_name("result.json")
    record = json.loads(result_path.read_text()) if result_path.exists() else None
    recorded = str(record.get("commit") or "") if record is not None else ""
    same_commit = len(recorded) >= 7 and (commit.startswith(recorded) or recorded.startswith(commit))
    if record is not None and (record.get("mode") != "exit-link" or record.get("stubs")
                               or record.get("force") or not same_commit):
        raise ValueError("bridge queue requires the matching unstubbed real-link result")
    with open(errors, encoding="utf-8", errors="replace", newline="") as handle:
        blockers = blockers_from_errors(handle, export_sources(census.ledger()))
    with open(ROOT / BLOCKERS, "w", encoding="utf-8", newline="\n") as out:
        out.write(f"# real link at {commit}: tools/exit_link.py --blockers\n")
        out.write("source\tmissing\tsample\n")
        for source, count, sample in blockers:
            out.write(f"{source}\t{count}\t{sample}\n")
    print(f"{BLOCKERS}: {len(blockers)} source(s), {sum(b[1] for b in blockers)} missing name(s) by source")
    if record is not None and record.get("vtable_bridge") is not None:
        import vtable_bridge
        vtable_bridge.write_queue(record["vtable_bridge"], ROOT / "reverse/vtable_bridge_queue.tsv", commit)
        print("reverse/vtable_bridge_queue.tsv: refusals then bridge retirement work")
    else:
        print("bridge queue unchanged: this artifact has no real-link bridge metadata")
    return 0


def run_native(command, *, check=False, timeout=None):
    """Wait for the native tool, without waiting for Wine helpers to close a pipe."""
    with tempfile.TemporaryFile(mode="w+", errors="replace") as output:
        result = subprocess.run(command, cwd=ROOT,
                                env=build.compiler_environment(build.vc71_root()),
                                stdout=output, stderr=subprocess.STDOUT, timeout=timeout)
        output.seek(0)
        completed = subprocess.CompletedProcess(command, result.returncode, output.read(), "")
    if check:
        completed.check_returncode()
    return completed


def runtime_data_imports(libraries):
    """Public names the runtime import libraries declare DATA (msvcrt.lib: `__adjust_fdiv`, `__iob`).

    A generated CODE entry for one of these defines a callable `_X` thunk in .text. For
    `_adjust_fdiv`, msvcrt.lib's own adjustfd.obj defines the variable the startup code
    stores to; the thunk (earlier on the command line) won instead and the first store
    faulted at entry. Retail's import library has no such thunk, so neither do ours.
    """
    names = set()
    for library in libraries:
        data = Path(library).read_bytes()
        at = 8
        while at + 60 <= len(data):
            size = int(data[at + 48:at + 58].decode("ascii").strip())
            start = at + 60
            if size >= 20 and data[start:start + 4] == b"\0\0\xff\xff" and \
                    struct.unpack_from("<H", data, start + 18)[0] & 3 == 1:
                names.add(data[start + 20:data.index(0, start + 20)].decode("latin-1"))
            at = start + size + (size & 1)
    return names


def make_import_libs(entries, outdir, defined=()):
    """The census's import convention, using file capture for native LIB output."""
    root = build.vc71_root()
    libraries = []
    for dll, names in sorted(entries.items()):
        stem = re.sub(r"\W", "_", dll.rsplit(".", 1)[0].lower())
        definition = outdir / f"imp_{stem}.def"
        exports = []
        for name in names:
            symbol = name if name.startswith("?") else "_" + name
            exports.append(f"  {name}" + (" DATA" if symbol in defined else "") + "\n")
        definition.write_text(f"LIBRARY {dll}\nEXPORTS\n" + "".join(exports), encoding="latin-1")
        library = outdir / f"imp_{stem}.lib"
        census.fresh_outputs(library)
        command = [str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86",
                   f"/DEF:{definition}", f"/OUT:{library}"]
        if sys.platform != "win32":
            command.insert(0, "wine")
        result = run_native(command)
        if result.returncode or not library.exists():
            raise SystemExit(f"exit_link: lib.exe failed for {dll}:\n{result.stdout}{result.stderr}")
        link_cycle.undecorate_stdcall_imports(library, dll.lower() in link_cycle.DECORATED_EXPORT_DLLS)
        libraries.append(library)
    return libraries


def link_arguments(image, rsp):
    """The exit link's options: no /FORCE, no scaffold, a non-retail base."""
    return ["/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
            "/SUBSYSTEM:WINDOWS", f"/ENTRY:{ENTRY}", f"/BASE:0x{BASE:X}",
            f"/OUT:{census._arg(image)}", f"/MAP:{census._arg(image.with_suffix('.map'))}",
            "/FIXED:NO", "/OPT:NOREF", "/OPT:NOICF", f"@{census._arg(rsp)}"]


def link_command(inputs, image, outdir, import_roots=()):
    """The exit link's argv, with the objects in a response file."""
    rsp = Path(outdir) / "exit.rsp"
    rsp.write_text("\n".join(f'"{census._arg(path)}"' for path in inputs) + "\n", encoding="utf-8")
    exports = export_definition(Path(outdir) / "retail.def")
    resource = resource_object(Path(outdir))
    with rsp.open("a", encoding="utf-8") as handle:
        handle.write(f'/DEF:"{census._arg(exports)}"\n"{census._arg(resource)}"\n')
        for name in sorted(import_roots):
            handle.write(f"/INCLUDE:{name}\n")
    root = build.vc71_root()
    command = [str(root / "Vc7" / "bin" / "link.exe"), *link_arguments(image, rsp)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    return command, rsp


def export_names():
    with (ROOT / "reverse/exports.csv").open(newline="", encoding="utf-8") as handle:
        return {row["name"] for row in csv.DictReader(handle)}


def export_definition(path):
    """Keep every retail export, including data; exports are linker roots."""
    with (ROOT / "reverse/exports.csv").open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    path.write_text("EXPORTS\n" + "".join(
        f'  {row["name"]} @{row["ordinal"]}' +
        (" DATA" if row["kind"] == "data" else "") + "\n" for row in rows),
        encoding="utf-8")
    return path


def resource_object(outdir):
    """Extract retail resource leaves into Win32 .res, converted by VC7.1."""
    import pefile
    pe = pefile.PE(str(build.EXE))
    def ident(entry):
        if entry.name is not None:
            return str(entry.name).encode("utf-16le") + b"\0\0"
        return struct.pack("<HH", 0xFFFF, entry.id)
    def align(data):
        return data + b"\0" * (-len(data) % 4)
    blob = struct.pack("<IIHHHHIHHII", 0, 32, 0xFFFF, 0, 0xFFFF, 0, 0, 0, 0, 0, 0)
    for typ in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for name in typ.directory.entries:
            for lang in name.directory.entries:
                leaf = lang.data.struct
                data = pe.get_data(leaf.OffsetToData, leaf.Size)
                if len(data) != leaf.Size:
                    raise ValueError("truncated retail resource")
                header = align(ident(typ) + ident(name))
                header += struct.pack("<IHHII", 0, 0x1030, lang.id, 0, 0)
                blob += struct.pack("<II", len(data), 8 + len(header)) + header + align(data)
    pe.close()
    res, obj = outdir / "retail.res", outdir / "retail_resources.obj"
    res.write_bytes(blob)
    census.fresh_outputs(obj)
    root = build.vc71_root()
    command = [str(root / "Vc7/bin/cvtres.exe"), "/NOLOGO", "/MACHINE:IX86",
               f"/OUT:{census._arg(obj)}", census._arg(res)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    run_native(command, check=True)
    if not obj.is_file():
        raise RuntimeError("cvtres did not write a resource object")
    return obj


def diagnostic_stub_layout(names):
    """Keep an IAT pointer immediately before its trap, under the same map name."""
    layout, cursor = [], 0
    for name in sorted(set(names)):
        imported = name.startswith("__imp_")
        layout.append({"name": name, "offset": cursor,
                       "kind": "import-pointer" if imported else "trap", "section": ".text",
                       "trap_symbol": name, "trap_offset": cursor + 4 if imported else cursor})
        cursor += 32 if imported else 16
    return layout


def diagnostic_stubs(names, path):
    """Distinct traps; __imp_ values point four bytes forward into their own trap."""
    layout = diagnostic_stub_layout(names)
    imports = [entry for entry in layout if entry["kind"] == "import-pointer"]
    if len(imports) > 0xFFFF:
        raise ValueError("too many diagnostic import-pointer relocations")
    strings, symbols = bytearray(4), bytearray()
    size = sum(32 if entry["kind"] == "import-pointer" else 16 for entry in layout)
    body, relocs = bytearray(b"\xcc" * size), bytearray()
    for index, entry in enumerate(layout):
        name, imported = entry["name"], entry["kind"] == "import-pointer"
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings.extend(raw + b"\0")
        symbols += field + struct.pack("<IhHBB", entry["offset"], 1, 0 if imported else 0x20, 2, 0)
        if imported:
            # COFF DIR32 adds this addend to the symbol VA and emits a PE base relocation.
            struct.pack_into("<I", body, entry["offset"], 4)
            relocs += struct.pack("<IIH", entry["offset"], index, link_cycle.DIR32)
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 60 + len(body) + len(relocs),
                         len(layout), 0, 0)
    section = b".text".ljust(8, b"\0") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(body), 60 if body else 0,
        60 + len(body) if relocs else 0, 0, len(imports), 0, 0x60500020)
    path.write_bytes(header + section + body + relocs + symbols + strings)
    return path


STUB_CLASH = re.compile(r"\bLNK2005\b.*\bdiagnostic_stubs\.obj\b|\bdiagnostic_stubs\.obj\b.*\bLNK2005\b")


def read_stub_seed(path):
    """The names an earlier diagnostic link stubbed, from its stubbed.tsv."""
    with Path(path).open(newline="", encoding="utf-8") as handle:
        return {row["name"] for row in csv.DictReader(handle, delimiter="\t") if row.get("name")}


def seeded_stubs(path, objects, extra_objects, libraries, exports=()):
    """The seed's names this link is certain to leave unresolved, to stub before its first pass.

    A name qualifies only when the link references it (an undefined EXTERNAL of a linked
    object, not COMMON, or a /DEF export: 193 of master's 198 stubs on 2026-11-07 were
    exports) and no linked object or library defines it: link.exe reports exactly such a name
    unresolved, and the next pass would stub it anyway. A name the seed lacks still costs a
    pass, and a seeded trap that clashes with a definition drops the whole seed (run_link).
    """
    names = read_stub_seed(path)
    referenced, defined = set(exports), set()
    for objs in (objects, link_cycle.Objects(extra_objects)):
        for item in objs.paths:
            parsed = objs.get(item)
            for symbol in (parsed[1].values() if parsed else ()):
                if symbol.cls != link_cycle.EXTERNAL:
                    continue
                if symbol.sec == 0 and not symbol.value:
                    referenced.add(symbol.name)
                else:
                    defined.add(symbol.name)
    for library in libraries:
        defined |= census.library_symbols(library)
    return {"file": str(path), "offered": len(names), "names": sorted(names & referenced - defined),
            "dropped": False}


def image_commit():
    """The cross-lane receipt requires a full object ID, unlike census headlines."""
    return subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()


def omission_status(proof):
    """A measurement cannot erase the failed proof recorded by the workflow."""
    required = {"population_problem", "inspection_failures", "uncovered_funclets",
                "unproven", "outside_referrers"}
    if proof is None or not required <= proof.keys():
        return "not-run"
    failed = any(proof.get(key) for key in (
        "population_problem", "inspection_failures", "uncovered_funclets", "unproven",
        "outside_referrers", "uncovered_funclets_recorded", "unproven_recorded",
        "measurement_note"))
    return "failed" if failed else "passed"


def image_receipt(image, diagnostic, stubbed, proof=None, vtables=None):
    """Only an image and its fresh map can receive a receipt."""
    if stubbed and not diagnostic:
        raise ValueError("a real image cannot contain diagnostic stubs")
    receipt = image.parent / "image_receipt.json"
    receipt.unlink(missing_ok=True)
    if not image.exists():
        return
    mapfile = image.with_suffix(".map")
    if not mapfile.exists() or not mapfile.stat().st_size:
        raise RuntimeError("image exists without a nonempty map")
    with (ROOT / "reverse/exports.csv").open(newline="", encoding="utf-8") as handle:
        exports = sum(1 for _ in csv.DictReader(handle))
    status = omission_status(proof)
    vtables = vtables or {}
    receipt.write_text(json.dumps({
        "authoritative": not diagnostic and status == "passed", "omission_proof": status,
        "vtables_bridged": vtables.get("tables", 0), "vtable_slots_bridged": vtables.get("slots", 0),
        "kind": "diagnostic" if diagnostic else "real", "commit": image_commit(),
        "base": f"0x{BASE:X}", "image_sha256": digest(image), "map_sha256": digest(mapfile),
        "stubbed": sorted(stubbed), "exports_requested": exports, "rsrc": True,
        "fixed_no": True, "opt": "NOREF,NOICF",
    }, indent=1) + "\n", encoding="utf-8")



def snapshot_image_objects(rsp, image):
    """Capture winning inputs immediately; report failure without changing measurement."""
    if not image.exists():
        return None
    try:
        import image_iso
        return image_iso.write_object_manifest(
            rsp, image.with_suffix(".map"), OUT / "image_objects.json", cwd=build.ROOT)
    except Exception as exc:
        message = f"{type(exc).__name__}: {exc}"
        print(f"exit_link: object manifest failed: {message}", file=sys.stderr)
        return {"error": message}


def run_diagnostic(rows, stub_seed=None):
    """Isolate every output, even refusals, from measured files and scoreboard."""
    global OUT
    measured_out = OUT
    OUT = measured_out.parent / "diagnostic_link"
    try:
        return run_link(rows, diagnostic=True, stub_seed=stub_seed)
    finally:
        OUT = measured_out


ERROR_LINE = re.compile(r"^(?P<object>\S+\.(?:obj|exp)|LINK) : (?:fatal )?(?P<severity>error|warning) "
                        r"(?P<code>LNK\d+): (?P<text>.*)$")
UNRESOLVED = census.UNRESOLVED
DUPLICATE = census.DUPLICATE


def parse_errors(log, sources_of=None, exports_of=None):
    """Every linker error/warning with its referrer's source, in log order."""
    sources_of = sources_of or {}
    exports_of = exports_of or {}
    errors = []
    for line in log.splitlines():
        found = ERROR_LINE.match(line)
        if not found:
            continue
        entry = {"severity": found.group("severity"), "code": found.group("code"),
                 "object": "" if found.group("object") == "LINK" else found.group("object"),
                 "source": "", "symbol": "", "text": found.group("text").strip()}
        if entry["object"]:
            entry["source"] = sources_of.get(entry["object"], "")
        unresolved = UNRESOLVED.search(line)
        if unresolved:
            entry["symbol"] = unresolved.group(1) or unresolved.group(2)
        duplicate = DUPLICATE.match(line)
        if duplicate:
            entry["symbol"] = duplicate.group(2) or duplicate.group(3)
        if entry["object"].lower().endswith(".exp") and entry["symbol"]:
            entry["source"] = exports_of.get(entry["symbol"], EXPORT_UNOWNED)
        errors.append(entry)
    return errors


def object_sources(rows):
    """{object basename: source} for provenance in the linker's own spelling."""
    out = collections.defaultdict(list)
    for path, source in census._object_sources(rows).items():
        out[path.name].append(source)
    return {name: values[0] if len(values) == 1 else ", ".join(sorted(values))
            for name, values in out.items()}


BLOCKERS = "reverse/exit_link_blockers.tsv"
INITIALIZER_SECTION = 0xC0300040     # initialized data, read/write, align 4
SCAFFOLD_OBJECT = re.compile(r"^(?:stubs?\.obj|alias(?:es)?\.obj|fill\d+\.obj)$", re.IGNORECASE)


def scaffold_free(inputs, omitted):
    """(scaffold-named inputs, omitted objects that leaked into the link)."""
    bad = [path.name for path in inputs if SCAFFOLD_OBJECT.match(path.name)]
    leaked = sorted(path.name for path in inputs if path in set(omitted))
    return bad, leaked


def initializer_table(rows, inputs):
    """An object registering retail's initializers that no kept object registers, in retail's order.

    A body that exists only as a plain function links and never runs, so its globals are never
    built. The table lets an image start; it is not the source. Its count is published with each
    link and must reach 0 for the exit test, as real statics replace it. It goes first, so these run
    before the initializers objects register themselves; their order against those is not retail's.
    """
    import image_report
    entries, unreachable = image_report.bridge_entries(rows, inputs)
    names = sorted({name for _rva, name in entries})
    number = {name: index for index, name in enumerate(names)}
    path = link_cycle.write_coff(
        OUT / "retail_initializers.obj",
        [(".CRT$XCU", INITIALIZER_SECTION, bytes(4 * len(entries)), 0)],
        [(name, 0, 0, link_cycle.EXTERNAL) for name in names],
        {1: [(4 * slot, name, link_cycle.DIR32) for slot, (_rva, name) in enumerate(entries)]})
    assert len(number) == len(names)
    return path, {"entries": len(entries), "unreachable": unreachable,
                  "note": "generated from retail's table; must reach 0 for the exit test"}


def harness_import_roots(requests):
    """Keep the harness's named IAT slots even without a surviving code referrer.

    Root one spelling per API, preferring its canonical stdcall name. Rooting
    every spelling also retains unused IAT variants from discarded COMDATs.
    Keep all requests/providers: genuinely referenced variants still link
    normally and remain visible to the image checker.
    """
    requests = set(requests)
    roots = set()
    for name, stack_bytes in HARNESS_IMPORTS.items():
        existing = {symbol for symbol in requests
                    if symbol.startswith("__imp__") and
                    re.sub(r"@\d+$", "", symbol[len("__imp__"):]) == name}
        preferred = f"__imp__{name}@{stack_bytes}"
        roots.add(preferred if preferred in existing or not existing else sorted(existing)[0])
    return requests | roots, roots


def link_setup(rows, present, parsed=None):
    """(inputs, metadata) for the exit link, with every scaffold left out; `parsed`, when
    given, receives the parsed kept objects under "objects"."""
    omitted = set(placement_objects(rows))
    inputs = [path for path in present if path not in omitted]
    bad, leaked = scaffold_free(inputs, omitted)
    if bad or leaked:
        raise SystemExit(f"exit_link: the link set is not scaffold-free (scaffolds {bad}, "
                         f"omitted objects {leaked}); nothing linked")
    objects = link_cycle.Objects(inputs)
    if parsed is not None:
        parsed["objects"] = objects
    retail_imports = census.retail_imports()
    requests, import_roots = harness_import_roots(
        link_cycle.undefined_imports(objects) | link_cycle.undefined_plain_imports(objects, retail_imports))
    entries, missing = link_cycle.import_def_entries(requests, retail_imports)
    if import_roots.intersection(missing):
        raise SystemExit("exit_link: retail does not provide the harness imports: " +
                         ", ".join(sorted(import_roots.intersection(missing))))
    imports = OUT / "imports"
    imports.mkdir(parents=True, exist_ok=True)
    runtime = link_cycle.runtime_libraries()
    libs = make_import_libs(entries, imports,
                            link_cycle.defined_externals(objects) | runtime_data_imports(runtime))
    libs += runtime
    absolute = link_cycle.write_coff(
        OUT / "absolute.obj", [],
        [(name, -1, value, link_cycle.EXTERNAL) for name, value in link_cycle.ABSOLUTE.items()])
    metadata = {
        "harness_import_symbols": sorted(import_roots),
        "omitted_objects": sorted(path.name for path in omitted),
        "import_libraries": sorted(path.name for path in libs),
        "import_entries": sum(len(names) for names in entries.values()),
        "import_dlls": sorted(entries),
        "imports_retail_does_not_import": sorted(missing),
        "crt_absolute_symbols": {name: value for name, value in link_cycle.ABSOLUTE.items()},
    }
    table, bridge = initializer_table(rows, inputs)
    metadata["initializer_bridge"] = bridge
    import image_report
    import vtable_bridge
    vtables, vtable_info = vtable_bridge.build_bridge(
        rows, inputs, omitted, libs, OUT,
        image_report.Retail(build.EXE.read_bytes()), objects=objects,
        source_of=census._object_sources(rows))
    metadata["vtable_bridge"] = vtable_info
    return ([vtables] if vtables else []) + [table] + inputs + libs + [absolute], metadata


def expected_objects(rows):
    """Every object the link needs, deduplicated by resolved object path.

    A TU can own both code rows and data rows; keying code providers by their
    relative source and data providers by an absolute one listed such a TU
    twice (1,044 duplicate paths on the 2026-10-30 tree). The object path is
    the identity. No extraction or write happens here.
    """
    found = {}
    for row in rows:
        path = build.row_object(row)
        found.setdefault(path.resolve(), path)
    for source in census.data_sources():
        path = build.obj_path(source)
        found.setdefault(path.resolve(), path)
    return sorted(found.values(), key=lambda path: path.as_posix())


def object_inventory(rows):
    """(expected, present, missing) for every object; existence only, no writes."""
    expected = expected_objects(rows)
    present = [path for path in expected if path.exists()]
    missing = [path for path in expected if not path.exists()]
    return expected, present, missing


def stale_objects(present, sources):
    """Objects not current by build.compile_is_current (source + recorded headers).

    The exit mode is a measurement, not the census: it does not demand a
    census-grade witnessed compile per TU. It demands that each object was
    compiled from this source and these headers, which the dep cache re-checks.
    Split across BUILD_POOL processes as build.stale_sources splits it (5.5 of the
    10.7 minutes before srv1's first link pass were this check on one core).
    """
    pairs = [(obj, sources[obj]) for obj in present if obj in sources]
    workers = build._pool_size()
    if workers <= 1 or len(pairs) < 200:
        return _stale_chunk(pairs)
    with concurrent.futures.ProcessPoolExecutor(workers) as pool:
        stale = {obj for part in pool.map(_stale_chunk, [pairs[i::workers] for i in range(workers)])
                 for obj in part}
    return [obj for obj, _ in pairs if obj in stale]


def _stale_chunk(pairs):
    return [obj for obj, source in pairs if not build.compile_is_current(source, obj)]


def check_data_rows():
    """The data ledger's format and the data objects' currency; no byte probes.

    `data_rows.verify` compiles sizeof probes under build/data_rows; the exit
    mode is read-only, and the data byte gate belongs to the preparation step
    (the census or the build that produced these objects).
    """
    import data_rows
    problems = []
    if data_rows.DATA_ROWS.exists():
        data_rows.check(data_rows.DATA_ROWS.read_bytes(), problems)
    if problems:
        raise SystemExit("exit_link: invalid data rows:\n  " + "\n  ".join(problems))
    sources = {build.obj_path(source): source for source in census.data_sources()}
    stale = stale_objects(list(sources), sources)
    if stale:
        raise SystemExit(f"exit_link: {len(stale):,} data provider object(s) are missing or stale, "
                         f"e.g. {stale[0].relative_to(ROOT)}; prepare with python3 tools/link_census.py --build (or ./build.sh)")


def run_link(rows, diagnostic=False, stub_seed=None):
    if sys.platform.startswith("win") and not os.environ.get("GITHUB_ACTIONS"):
        raise SystemExit("exit_link: --link runs on a sandbox (Wine + MSVC 7.1) or a hosted runner only; "
                         "use --plan on this PC")
    if diagnostic and OUT.name != "diagnostic_link":
        raise SystemExit("exit_link: diagnostic output must be isolated")
    if stub_seed is not None and not diagnostic:
        raise SystemExit("exit_link: --stub-seed is for --diagnostic only")
    OUT.mkdir(parents=True, exist_ok=True)
    census.fresh_outputs(*(OUT / name for name in (
        "exit.exe", "exit.map", "image_receipt.json", "result.json", "errors.tsv", "link.log", "stubbed.tsv",
        "image_objects.json", "image_objects.json.receipt.json")))
    expected, present, missing = object_inventory(rows)
    if missing:
        raise SystemExit(f"exit_link: {len(missing):,} object(s) are missing, e.g. "
                         f"{missing[0].relative_to(ROOT)}; the measurement needs the full population. "
                         "Prepare with python3 tools/link_census.py --build (or ./build.sh) first")
    check_data_rows()
    sources = census._object_sources(rows)
    stale = stale_objects(present, sources)
    if stale:
        raise SystemExit(f"exit_link: {len(stale):,} objects are not current, e.g. "
                         f"{stale[0].name}; prepare with python3 tools/link_census.py --build (or ./build.sh)")
    proof = omission_proof(rows, present, expected)
    if proof["population_problem"]:
        raise SystemExit(f"exit_link: {proof['population_problem']}")
    if proof["inspection_failures"]:
        raise SystemExit(f"exit_link: {len(proof['inspection_failures'])} kept object(s) could not be "
                         f"inspected, e.g. {proof['inspection_failures'][0]['object']}; nothing linked")
    if proof["uncovered_funclets"] and not diagnostic:
        names = ", ".join(entry["name"] for entry in proof["uncovered_funclets"][:8])
        raise SystemExit(f"exit_link: {len(proof['uncovered_funclets'])} omitted funclet(s) are not "
                         f"emitted by any EXACT kept parent ({names}); the omission is not proved")
    uncovered = {entry["name"] for entry in proof["uncovered_funclets"]}
    unproven = [entry for entry in proof["unproven"]
                if not diagnostic or entry.get("name") not in uncovered]
    if unproven or proof["outside_referrers"]:
        raise SystemExit(f"exit_link: omission is not proved ({len(proof['unproven'])} unproven funclet(s), "
                         f"{len(proof['outside_referrers'])} name(s) referenced outside); nothing linked")
    eh = eh_proof(rows)
    if eh["unproven"] or eh["missing_objects"]:
        raise SystemExit(f"exit_link: EH proof failed ({len(eh['unproven'])} row(s) not exact and not "
                         f"baselined, {eh['missing_objects']} without an object); nothing linked")
    parsed = {}
    inputs, setup = link_setup(rows, present, parsed)
    image = OUT / "exit.exe"
    command, rsp = link_command(inputs, image, OUT, setup["harness_import_symbols"])
    state, tools = census.census_state(present), tool_digests()
    census.fresh_outputs(image, image.with_suffix(".map"), OUT / "image_receipt.json",
                         OUT / "result.json", OUT / "errors.tsv")
    started = time.time()
    stubbed, seed = set(), None
    unstubbed = rsp.read_text(encoding="utf-8") if rsp.exists() else ""

    def relink():
        response = unstubbed
        if stubbed:
            stub = diagnostic_stubs(stubbed, OUT / "diagnostic_stubs.obj")
            response += f'"{census._arg(stub)}"\n'
        rsp.write_text(response, encoding="utf-8")
        census.fresh_outputs(image, image.with_suffix(".map"))
        return run_native(command)

    if stub_seed is not None:
        kept = set(parsed["objects"].paths)
        seed = seeded_stubs(stub_seed, parsed["objects"],
                            [path for path in inputs if path.suffix.lower() == ".obj" and path not in kept],
                            [path for path in inputs if path.suffix.lower() == ".lib"], export_names())
        stubbed.update(seed["names"])
    result = relink() if stubbed else run_native(command)
    passes = 1
    if diagnostic:
        while result.returncode:
            text = result.stdout + result.stderr
            if seed and not seed["dropped"] and STUB_CLASH.search(text):
                # The filter missed a definition: link as if no seed had been given.
                seed["dropped"] = True
                stubbed.clear()
                result, passes = relink(), passes + 1
                continue
            wanted = {m.group(1) or m.group(2) for m in UNRESOLVED.finditer(text)}
            fresh = wanted - stubbed
            if not fresh:
                break
            stubbed.update(fresh)
            result, passes = relink(), passes + 1
    seconds = time.time() - started
    manifest = snapshot_image_objects(rsp, image)
    if diagnostic:
        with (OUT / "stubbed.tsv").open("w", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=[
                "name", "offset", "kind", "section", "trap_symbol", "trap_offset"],
                delimiter="\t", lineterminator="\n")
            writer.writeheader()
            for entry in diagnostic_stub_layout(stubbed):
                writer.writerow({**entry, "offset": f"0x{entry['offset']:X}",
                                 "trap_offset": f"0x{entry['trap_offset']:X}"})
    log = result.stdout + result.stderr
    (OUT / "link.log").write_text(log, encoding="utf-8")
    code = result.returncode
    if code < 0 or code > 0xFFFF:
        raise SystemExit(f"exit_link: link.exe terminated abnormally (exit 0x{code & 0xFFFFFFFF:08X}); "
                         "nothing recorded")
    if code and not re.search(r"\b(?:error|warning) LNK\d+", log):
        raise SystemExit(f"exit_link: link.exe exited {code} with no linker diagnostic; nothing recorded")
    if census.census_state(present) != state or tool_digests() != tools:
        raise SystemExit("exit_link: the tree or this mode's tools changed during the link; nothing recorded")
    sources_of = object_sources(rows)
    errors = parse_errors(log, sources_of, export_sources(rows))
    classes, detail, duplicate_classes, duplicates = census.classify(log, rows)
    omitted = set(placement_objects(rows))
    exclusive = set(proof["exclusive_names"])
    still_wanted = sorted(name for name in detail if name in exclusive)
    image_written = image.exists()
    image_receipt(image, diagnostic, stubbed, proof=proof, vtables=setup.get("vtable_bridge"))
    record = {
        "mode": "diagnostic-link" if diagnostic else "exit-link",
        "records": False,
        "when": census.utc_now(),
        "commit": census.head(),
        "base": f"0x{BASE:X}",
        "entry": ENTRY,
        "force": False,
        "stubs": diagnostic,
        "aliases": False,
        "fillers": False,
        "tools": tool_digests(),
        "currency": {"rule": "build.compile_is_current (source + recorded headers)",
                     "published_index": published_index_meta()},
        "objects": {
            "linked": (len(inputs) - len(setup["import_libraries"]) - 2
                       - bool(setup.get("vtable_bridge", {}).get("object"))),
            "present": len(present),
            "omitted": proof["objects"],
            "omitted_count": len(omitted),
            "missing": [str(path.relative_to(ROOT)) for path in missing],
        },
        "omission_proof": proof,
        "image_objects": manifest,
        "eh_proof": eh,
        "link": {
            "seconds": round(seconds, 1),
            "exit": code,
            "command": command,
            "response": rsp.name,
            "log": (OUT / "link.log").relative_to(ROOT).as_posix(),
            "image_written": image_written,
            "pe_defect": census.pe_defect(image) if image_written else None,
        },
        "errors": {
            "total": len(errors),
            "unresolved": len(detail),
            "unresolved_classes": dict(classes),
            "unresolved_detail": {name: {"kind": entry.get("kind"),
                                         "refs": sorted(entry.get("refs") or ()),
                                         "address": entry.get("address"),
                                         "defined_as": entry.get("defined_as")}
                                  for name, entry in detail.items()},
            "duplicates": len(duplicates),
            "duplicate_classes": dict(duplicate_classes),
            "unresolved_exclusive_to_omitted": still_wanted,
        },
        **setup,
    }
    if diagnostic:
        record["link"]["passes"] = passes
        record["stub_seed"] = seed and {"file": seed["file"], "offered": seed["offered"],
                                        "seeded": len(seed["names"]), "dropped": seed["dropped"]}
    (OUT / "result.json").write_text(json.dumps(record, indent=1), encoding="utf-8")
    with (OUT / "errors.tsv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, delimiter="\t", lineterminator="\n")
        writer.writerow(["severity", "code", "symbol", "object", "source", "text"])
        for entry in errors:
            writer.writerow([entry["severity"], entry["code"], entry["symbol"],
                             entry["object"], entry["source"], entry["text"]])
    print(f"exit_link: base 0x{BASE:X}, {record['objects']['linked']:,} objects "
          f"({len(omitted)} placement-only left out), exit {code}")
    print(f"exit_link: omission {proof['funclet_covered']:,}/{proof['funclet_rows']:,} funclets "
          f"covered by an EXACT kept parent; {len(proof['uncovered_funclets'])} uncovered")
    print(f"exit_link: {len(detail):,} unresolved name(s), {len(duplicates):,} duplicate name(s), "
          f"{len(errors):,} error/warning line(s); {len(still_wanted)} name(s) still wanted from an "
          "omitted object")
    print(f"exit_link: {OUT.relative_to(ROOT).as_posix()}/result.json")
    return int(code != 0 or not image_written) if diagnostic else 0


# ---------------------------------------------------------------- plan/report
def plan(rows, args):
    OUT.mkdir(parents=True, exist_ok=True)
    proof = omission_proof(rows, present=None)
    print(f"exit_link plan: {len(rows):,} matched rows; {proof['source_count']} placement-only "
          f"source(s), {proof['rows']:,} row(s), {proof['funclet_rows']:,} funclet row(s)")
    for entry in proof["objects"]:
        print(f"  omit {entry['source']} ({entry['rows']} row(s)) -> {entry['object']}")
    if proof["population_problem"]:
        print(f"exit_link plan: POPULATION PROBLEM: {proof['population_problem']}")
    expected = present = None
    missing = []
    if args.objects:
        expected, present, missing = object_inventory(rows)
        proof = omission_proof(rows, present, expected)
        print(f"exit_link plan: omission proof over {len(present):,} of {len(expected):,} object(s) "
              f"({len(missing):,} missing)")
        print(f"  structural parent check: {proof['funclet_proven']:,}/{proof['funclet_rows']:,}; "
              f"EXACT kept-parent coverage: {proof['funclet_covered']:,}/{proof['funclet_rows']:,}")
        print(f"  uncovered funclets: {len(proof['uncovered_funclets'])}; unproven: "
              f"{len(proof['unproven'])}; inspection failures: {len(proof['inspection_failures'])}; "
              f"outside referrers: {len(proof['outside_referrers'])}")
        for entry in proof["uncovered_funclets"][:20]:
            print(f"    UNCOVERED {entry['name']} {entry['target_rva']} ({entry['source']})")
        for entry in proof["unproven"][:20]:
            print(f"    UNPROVEN {entry['symbol']} in {entry['object']}: {entry['why']}")
        for entry in proof["inspection_failures"][:20]:
            print(f"    UNINSPECTED {entry['object']}: {entry['why']}")
        for name, referrers in sorted(proof["outside_referrers"].items())[:20]:
            print(f"    REFERENCED {name} by {', '.join(referrers)}")
    measurement = None
    if args.index:
        index = load_index()
        omitted_names = {path.name for path in placement_objects(rows)}
        measurement = index_measurement(index, omitted_names, last_census())
        print(f"exit_link plan: index {index.get('meta', {}).get('date', '?')} at "
              f"{index.get('meta', {}).get('commit', '?')}: "
              f"{measurement['proof']['exclusive_names']:,} name(s) only the omitted objects define; "
              f"{len(measurement['proof']['outside_referrers'])} outside referrer(s)")
        prediction = measurement["prediction"]
        if prediction:
            print(f"  prediction (not a measurement): {prediction['unresolved_in_census']:,} unresolved "
                  f"in the last census, {prediction['exclusive_unresolved_gone']:,} exclusive to the "
                  f"omitted objects, {prediction['unresolved_left']:,} left")
    report = {"when": census.utc_now(), "commit": census.head(), "base": f"0x{BASE:X}",
              "rows": len(rows), "omission_proof": proof, "index": measurement}
    (OUT / "plan.json").write_text(json.dumps(report, indent=1), encoding="utf-8")
    print(f"exit_link plan: {OUT.relative_to(ROOT).as_posix()}/plan.json")
    failed = bool(proof["population_problem"])
    if present is not None:
        failed = failed or bool(missing or proof["unproven"] or proof["outside_referrers"]
                                or proof["missing_objects"] or proof["inspection_failures"]
                                or proof["uncovered_funclets"])
    return 1 if failed else 0


def report():
    path = OUT / "result.json"
    if not path.exists():
        print(f"exit_link: no run at {path.relative_to(ROOT).as_posix()}; run --link on boat")
        return 1
    record = json.loads(path.read_text(encoding="utf-8"))
    errors = record["errors"]
    print(f"exit_link: {record['when']} at {record['commit']}, base {record['base']}, "
          f"{record['objects']['linked']:,} object(s), {record['objects']['omitted_count']} omitted")
    print(f"exit_link: exit {record['link']['exit']}, image "
          f"{'written' if record['link']['image_written'] else 'not written'}")
    print(f"exit_link: {errors['unresolved']:,} unresolved name(s) "
          f"({', '.join(f'{k} {v}' for k, v in sorted(errors['unresolved_classes'].items())) or 'none'}), "
          f"{errors['duplicates']:,} duplicate name(s), {errors['total']:,} error/warning line(s)")
    print(f"exit_link: {len(errors['unresolved_exclusive_to_omitted'])} name(s) still wanted from an "
          "omitted object")
    proof = record.get("omission_proof") or {}
    if proof:
        print(f"exit_link: omission {proof.get('funclet_covered', 0):,}/{proof.get('funclet_rows', 0):,} "
              f"funclets covered by an EXACT kept parent; "
              f"{len(proof.get('uncovered_funclets') or ())} uncovered, "
              f"{len(proof.get('inspection_failures') or ())} uninspected, "
              f"{len(proof.get('outside_referrers') or ())} outside referrer(s)")
    vtables = record.get("vtable_bridge")
    if vtables is not None:
        print(f"exit_link: vtable bridge {vtables['tables']:,} table(s), {vtables['slots']:,} slot(s); "
              f"{vtables['refused_tables']:,} refused, {vtables['already_correct']:,} already match; "
              "generated tables and slots must reach 0 for G1")
    eh = record.get("eh_proof")
    if eh:
        print(f"exit_link: EH proof {eh['rows_with_eh']:,} row(s), {eh['not_exact']:,} not exact "
              f"({eh['baselined']:,} baselined), {len(eh['unproven'])} unproven")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--plan", action="store_true",
                      help="dry run: the omitted population, its proof and the index's prediction; no link")
    mode.add_argument("--eh-proof", action="store_true", help="run eh_verify --all and report")
    mode.add_argument("--link", action="store_true", help="sandbox or hosted runner only: read-only proof and exit link")
    mode.add_argument("--diagnostic", action="store_true", help="separate trap-stub image; never a measurement")
    mode.add_argument("--report", action="store_true", help="summarise build/exit_link/result.json")
    parser.add_argument("--blockers-commit", default="", help="the commit --blockers' errors.tsv measured")
    mode.add_argument("--blockers", metavar="ERRORS_TSV",
                      help="write reverse/exit_link_blockers.tsv from a real link's errors.tsv")
    mode.add_argument("--image-report", action="store_true",
                      help="compare the kept objects with retail: tools/image_report.py")
    parser.add_argument("--objects", action="store_true",
                        help="with --plan: prove the omission from build/match objects")
    parser.add_argument("--index", action="store_true",
                        help="with --plan: cross-check the published census index (--fetch-index first)")
    parser.add_argument("--stub-seed", metavar="STUBBED_TSV", type=Path,
                        help="with --diagnostic: stub an earlier diagnostic link's names (its stubbed.tsv) "
                             "before the first pass, where this link certainly leaves them unresolved")
    args = parser.parse_args(argv)
    if args.stub_seed and not args.diagnostic:
        parser.error("--stub-seed goes with --diagnostic")
    if args.blockers:
        return write_blockers(Path(args.blockers), args.blockers_commit)
    if args.image_report:
        import image_report
        return image_report.main([])
    if (args.objects or args.index) and not args.plan:
        parser.error("--objects and --index go with --plan")
    if args.report:
        return report()
    rows = census.ledger()
    if args.plan:
        return plan(rows, args)
    if args.eh_proof:
        result = eh_proof(rows)
        print(f"exit_link: {result['rows_with_eh']:,} row(s) with EH data "
              f"({', '.join(f'{k} {v}' for k, v in sorted(result['verdicts'].items()))}); "
              f"{result['not_exact']:,} not exact, {result['baselined']:,} baselined, "
              f"{len(result['unproven'])} unproven, {result['missing_objects']} without an object")
        for entry in result["unproven"][:20]:
            print(f"  FAIL {entry['name']} {entry['target_rva']} ({entry['source']}): "
                  f"{entry['verdict']} -- {entry['detail']}")
        return 1 if result["unproven"] or result["missing_objects"] else 0
    return run_diagnostic(rows, args.stub_seed) if args.diagnostic else run_link(rows)


if __name__ == "__main__":
    sys.exit(main())
