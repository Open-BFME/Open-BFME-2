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
    (undefined externals, weak externals and `.drectve` /INCLUDE entries);
  * every omitted `gen-funclet` row is an associative `.text$x` COMDAT whose
    parent section lives in the same object and whose parent EH data names it
    (the parent emits it, so dropping the object drops the parent too);
  * `eh_verify --all` on fresh objects reports no row outside
    `reverse/eh_baseline.csv`, so every kept parent's EH data (funclets
    included) is retail's.

Link setup is the census's own inputs, without the scaffolds: every matched
row's object (code and data), import libraries generated from retail's import
table for the `__imp_` names the objects reference, the /MD runtime libraries,
and the CRT's own absolute `__except_list` (exsup.asm defines it 0; it is not a
stub). No `/FORCE`, no `stubs.obj`, no `alias.obj`, no filler objects.

Objects are the tree's matched objects. `--link --build` restores the
published census's objects from the object store (`link_check --fetch-index`)
and compiles only what the store does not hold; every object is then re-checked
with `build.compile_is_current` (source and every recorded header), and
result.json records that rule and the index's date and commit.

  python3 tools/exit_link.py --plan              # dry run: population + proof, no link
  python3 tools/exit_link.py --plan --objects    # also prove omission from build/match objects
  python3 tools/exit_link.py --plan --index      # also cross-check the published census index
  python3 tools/exit_link.py --eh-proof          # eh_verify --all on the current objects
  python3 tools/exit_link.py --link --build      # BOAT ONLY: compile stale objects, prove, link
  python3 tools/exit_link.py --report            # summarise the last run

Outputs live in `build/exit_link/`: result.json, errors.tsv, link.log (the raw
linker output), exit.rsp and the generated import libraries. Nothing here is
authoritative for LINKING or recovery credit; only the census records those.
"""
import argparse
import collections
import csv
import functools
import hashlib
import json
import os
import re
import subprocess
import sys
import time
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
TOOL_FILES = ("exit_link.py", "link_census.py", "link_cycle.py", "build.py", "eh_verify.py")


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
    return {name: digest(ROOT / "tools" / name) for name in TOOL_FILES}


# ---------------------------------------------------------------- COFF proof
def coff_view(path):
    """(sections, symbols, raw bytes) through link_cycle's COFF reader."""
    data = Path(path).read_bytes()
    sections, symbols = link_cycle.parse_coff(data)
    return sections, symbols, data


def coff_references(symbols, sections, data):
    """Names an object references: undefined/weak externals and .drectve /INCLUDE."""
    names = {symbol.name for symbol in symbols.values()
             if symbol.sec == 0 and symbol.cls in (link_cycle.EXTERNAL, link_cycle.WEAK)}
    for section in sections:
        if section.name == ".drectve" and section.size:
            text = data[section.ptr:section.ptr + section.size].decode("latin-1", errors="replace")
            names |= set(re.findall(r"/INCLUDE:(\S+)", text))
    return names


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
    except OSError as exc:
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


def omission_proof(rows, present=None):
    """Prove the 17 placement-only objects can be left out.

    `present` is the link's object list; without it only the ledger population
    is reported. A missing object is not a proof failure here (plan mode has no
    objects); `--link` requires the full set separately.
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
        "unproven": [],
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
    omitted_paths = set(omitted)
    kept = [path for path in present if path not in omitted_paths]
    defined = {}
    for path in omitted_paths:
        if not path.exists():
            result["missing_objects"].append(path.name)
            defined[path] = set()
            continue
        try:
            sections, symbols, data = coff_view(path)
        except (OSError, ValueError, IndexError) as exc:
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
        try:
            sections, symbols, data = coff_view(path)
        except (OSError, ValueError, IndexError):
            continue
        kept_definitions |= external_definitions(symbols)
        for name in coff_references(symbols, sections, data) & by_name.keys():
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
    result["missing_objects"] = sorted(result["missing_objects"])
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
def link_arguments(image, rsp):
    """The exit link's options: no /FORCE, no scaffold, a non-retail base."""
    return ["/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
            "/SUBSYSTEM:WINDOWS", f"/ENTRY:{ENTRY}", f"/BASE:0x{BASE:X}",
            f"/OUT:{census._arg(image)}", f"@{census._arg(rsp)}"]


def link_command(inputs, image, outdir):
    """The exit link's argv, with the objects in a response file."""
    rsp = Path(outdir) / "exit.rsp"
    rsp.write_text("\n".join(f'"{census._arg(path)}"' for path in inputs) + "\n", encoding="utf-8")
    root = build.vc71_root()
    command = [str(root / "Vc7" / "bin" / "link.exe"), *link_arguments(image, rsp)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    return command, rsp


ERROR_LINE = re.compile(r"^(?P<object>\S+\.obj|LINK) : (?:fatal )?(?P<severity>error|warning) "
                        r"(?P<code>LNK\d+): (?P<text>.*)$")
UNRESOLVED = census.UNRESOLVED
DUPLICATE = census.DUPLICATE


def parse_errors(log, sources_of=None):
    """Every linker error/warning with its referrer's source, in log order."""
    sources_of = sources_of or {}
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
        errors.append(entry)
    return errors


def object_sources(rows):
    """{object basename: source} for provenance in the linker's own spelling."""
    out = collections.defaultdict(list)
    for path, source in census._object_sources(rows).items():
        out[path.name].append(source)
    return {name: values[0] if len(values) == 1 else ", ".join(sorted(values))
            for name, values in out.items()}


SCAFFOLD_OBJECT = re.compile(r"^(?:stubs?\.obj|alias(?:es)?\.obj|fill\d+\.obj)$", re.IGNORECASE)


def scaffold_free(inputs, omitted):
    """(scaffold-named inputs, omitted objects that leaked into the link)."""
    bad = [path.name for path in inputs if SCAFFOLD_OBJECT.match(path.name)]
    leaked = sorted(path.name for path in inputs if path in set(omitted))
    return bad, leaked


def link_setup(rows, present):
    """(inputs, metadata) for the exit link, with every scaffold left out."""
    omitted = set(placement_objects(rows))
    inputs = [path for path in present if path not in omitted]
    bad, leaked = scaffold_free(inputs, omitted)
    if bad or leaked:
        raise SystemExit(f"exit_link: the link set is not scaffold-free (scaffolds {bad}, "
                         f"omitted objects {leaked}); nothing linked")
    objects = link_cycle.Objects(inputs)
    entries, missing = link_cycle.import_def_entries(
        link_cycle.undefined_imports(objects), census.retail_imports())
    imports = OUT / "imports"
    imports.mkdir(parents=True, exist_ok=True)
    libs = link_cycle.make_import_libs(entries, imports, link_cycle.defined_externals(objects))
    libs += link_cycle.runtime_libraries()
    absolute = link_cycle.write_coff(
        OUT / "absolute.obj", [],
        [(name, -1, value, link_cycle.EXTERNAL) for name, value in link_cycle.ABSOLUTE.items()])
    metadata = {
        "omitted_objects": sorted(path.name for path in omitted),
        "import_libraries": sorted(path.name for path in libs),
        "import_entries": sum(len(names) for names in entries.values()),
        "import_dlls": sorted(entries),
        "imports_retail_does_not_import": sorted(missing),
        "crt_absolute_symbols": {name: value for name, value in link_cycle.ABSOLUTE.items()},
    }
    return inputs + libs + [absolute], metadata


def stale_objects(present, sources):
    """Objects not current by build.compile_is_current (source + recorded headers).

    The exit mode is a measurement, not the census: it does not demand a
    census-grade witnessed compile per TU. It demands that each object was
    compiled from this source and these headers, which the dep cache re-checks.
    """
    return [obj for obj in present if obj in sources and not build.compile_is_current(sources[obj], obj)]


def verify_data_objects():
    """The data byte gate, then non-strict currency for the data objects."""
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
                         f"e.g. {stale[0].relative_to(ROOT)}; rerun with --build")
    data_rows.verify(compile=False)


def compile_rows(rows):
    """Make every object current, restoring the published census's where held.

    `build.compile_rows` with the dep cache restores an object the published
    census compiled for this exact tree (`link_check --fetch-index` imports
    them, verifying each source hash and compile command) and compiles only
    what the store does not hold. `stale_objects` below re-checks every result.
    """
    os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
    os.environ.pop("BUILD_RECOMPILE_ONLY", None)
    build.ensure_case_shims()
    build.ensure_reference_current()
    started = time.time()
    build.compile_rows(rows, census.compile_sources(rows))
    census._INPUT_RECEIPTS = None
    print(f"exit_link: compile {time.time() - started:.0f}s", flush=True)


def run_link(rows, args):
    if sys.platform.startswith("win"):
        raise SystemExit("exit_link: --link runs on the boat sandbox only (Wine + MSVC 7.1); "
                         "use --plan on Windows")
    OUT.mkdir(parents=True, exist_ok=True)
    if args.build:
        compile_rows(rows)
    verify_data_objects()
    present, missing = census.objects(rows)
    if missing and not args.allow_missing:
        raise SystemExit(f"exit_link: {len(missing):,} objects are missing, e.g. "
                         f"{missing[0].relative_to(ROOT)}; the measurement would be dishonest. "
                         "Run --build, or pass --allow-missing to record them")
    sources = census._object_sources(rows)
    stale = stale_objects(present, sources)
    if stale:
        raise SystemExit(f"exit_link: {len(stale):,} objects are not current, e.g. "
                         f"{stale[0].name}; run --build")
    proof = omission_proof(rows, present)
    if proof["population_problem"]:
        raise SystemExit(f"exit_link: {proof['population_problem']}")
    if proof["unproven"] or proof["outside_referrers"]:
        raise SystemExit(f"exit_link: omission is not proved ({len(proof['unproven'])} unproven funclet(s), "
                         f"{len(proof['outside_referrers'])} name(s) referenced outside); nothing linked")
    eh = None
    if not args.skip_eh_proof:
        eh = eh_proof(rows)
        if eh["unproven"] or eh["missing_objects"]:
            raise SystemExit(f"exit_link: EH proof failed ({len(eh['unproven'])} row(s) not exact and not "
                             f"baselined, {eh['missing_objects']} without an object); nothing linked")
    inputs, setup = link_setup(rows, present)
    image = OUT / "exit.exe"
    command, rsp = link_command(inputs, image, OUT)
    state, tools = census.census_state(present), tool_digests()
    census.fresh_outputs(image)
    started = time.time()
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, errors="replace",
                            env=build.compiler_environment(build.vc71_root()))
    seconds = time.time() - started
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
    errors = parse_errors(log, sources_of)
    classes, detail, duplicate_classes, duplicates = census.classify(log, rows)
    omitted = set(placement_objects(rows))
    exclusive = set(proof["exclusive_names"])
    still_wanted = sorted(name for name in detail if name in exclusive)
    image_written = image.exists()
    record = {
        "mode": "exit-link",
        "records": False,
        "when": census.utc_now(),
        "commit": census.head(),
        "base": f"0x{BASE:X}",
        "entry": ENTRY,
        "force": False,
        "stubs": False,
        "aliases": False,
        "fillers": False,
        "tools": tool_digests(),
        "currency": {"rule": "build.compile_is_current (source + recorded headers)",
                     "published_index": published_index_meta()},
        "objects": {
            "linked": len(inputs) - len(setup["import_libraries"]) - 1,
            "present": len(present),
            "omitted": proof["objects"],
            "omitted_count": len(omitted),
            "missing": [str(path.relative_to(ROOT)) for path in missing],
        },
        "omission_proof": proof,
        "eh_proof": eh,
        "link": {
            "seconds": round(seconds, 1),
            "exit": code,
            "command": command,
            "response": rsp.name,
            "log": "build/exit_link/link.log",
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
    (OUT / "result.json").write_text(json.dumps(record, indent=1), encoding="utf-8")
    with (OUT / "errors.tsv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, delimiter="\t", lineterminator="\n")
        writer.writerow(["severity", "code", "symbol", "object", "source", "text"])
        for entry in errors:
            writer.writerow([entry["severity"], entry["code"], entry["symbol"],
                             entry["object"], entry["source"], entry["text"]])
    print(f"exit_link: base 0x{BASE:X}, {record['objects']['linked']:,} objects "
          f"({len(omitted)} placement-only left out), exit {code}")
    print(f"exit_link: {len(detail):,} unresolved name(s), {len(duplicates):,} duplicate name(s), "
          f"{len(errors):,} error/warning line(s); {len(still_wanted)} name(s) still wanted from an "
          "omitted object")
    print(f"exit_link: {OUT.relative_to(ROOT).as_posix()}/result.json")
    return 0


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
    present = None
    if args.objects:
        present, missing = census.objects(rows)
        proof = omission_proof(rows, present)
        print(f"exit_link plan: omission proof over {len(present):,} object(s) "
              f"({len(missing):,} missing)")
        print(f"  funclets proved emitted by a parent in the same object: "
              f"{proof['funclet_proven']:,}/{proof['funclet_rows']:,}")
        print(f"  unproven funclets: {len(proof['unproven'])}; outside referrers: "
              f"{len(proof['outside_referrers'])}")
        for entry in proof["unproven"][:20]:
            print(f"    UNPROVEN {entry['symbol']} in {entry['object']}: {entry['why']}")
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
        failed = failed or bool(proof["unproven"] or proof["outside_referrers"]
                                or proof["missing_objects"])
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
    mode.add_argument("--link", action="store_true", help="BOAT ONLY: prove and run the exit link")
    mode.add_argument("--report", action="store_true", help="summarise build/exit_link/result.json")
    parser.add_argument("--objects", action="store_true",
                        help="with --plan: prove the omission from build/match objects")
    parser.add_argument("--index", action="store_true",
                        help="with --plan: cross-check the published census index (--fetch-index first)")
    parser.add_argument("--build", action="store_true", help="with --link: compile stale objects first")
    parser.add_argument("--skip-eh-proof", action="store_true",
                        help="with --link: do not run the whole-ledger EH proof (iteration only)")
    parser.add_argument("--allow-missing", action="store_true",
                        help="with --link: link and record even when objects are missing")
    args = parser.parse_args(argv)
    if (args.objects or args.index) and not args.plan:
        parser.error("--objects and --index go with --plan")
    if (args.build or args.skip_eh_proof or args.allow_missing) and not args.link:
        parser.error("--build, --skip-eh-proof and --allow-missing go with --link")
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
    return run_link(rows, args)


if __name__ == "__main__":
    sys.exit(main())
