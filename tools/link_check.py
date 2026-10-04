#!/usr/bin/env python3
"""Per-file LINKED check in seconds, without link.exe.

The link census (tools/link_census.py) links every object and takes minutes.
This answers the same question for one file against the last census: would
this source's object link cleanly, and what stops it? It compiles the source
(build.py's compile path, skipped when the object is current), reads its COFF
and checks it against the index the census wrote
(build/link_census/link_index.pkl: every object's strong definitions and
COMDAT copies with their retail-truth verdicts, and every file's blockers):

  unresolved  a name the object references that no other object defines and
              the real link would not find in an import library (excused())
  duplicate   a strong definition another object also defines
  comdat      a COMDAT copy that is not retail's body (link_census.keep_rule:
              retail truth where the symbol has a retail address, else the
              first copy in link order)
  addresses   hard-coded image addresses in the source (link_debt.addresses)
  selected    a name the object defines or references whose definition the
              link keeps is proven not retail's (link_census.judge_selected:
              the kept COMDAT copy is wrong, or the kept one of several
              definitions is not the ledger owner's). The holder is the one
              the census's /MAP showed, else the first definer in link order

These are the census's own rules and functions (Open-BFME-1's link_check.py,
ported with them), so a file the census counts as linked is one this calls
LINKS. It prints the file's LINKED bytes (its own authored + vendored bytes,
0xCC out, as progress.real_split counts them) at the census and now. The
census is the record: this is a preview, and its answer is only as fresh as
the index (a blocker another file fixed since then still shows; --refresh
recompiles every stale ledger object and replaces its census definitions).

  python3 tools/link_check.py Code/path/File.cpp [...]   # check files
  python3 tools/link_check.py --staged                  # the units staged for commit
  python3 tools/link_check.py --refresh SOURCE          # recompile stale objects first
"""
import argparse
import collections
import pickle
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402

INDEX = link_census.OUT / "link_index.pkl"
COMMON_SCHEMA = 1


def source_bytes(sources=None):
    """{source: real bytes of its authored + vendored rows}, counted the way
    progress.real_split counts LINKED (0xCC out). Per file: a byte two files
    claim counts in both."""
    import progress
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    naked = set(progress.naked_cpp_rows_at(matched, None))
    image_start, image = progress._text_image()
    intervals = collections.defaultdict(list)
    for key, (length, source) in matched.items():
        if sources is not None and source not in sources:
            continue
        if progress.source_lane(source, notes[key], key in naked) not in progress.DECOMPILED_LANES:
            continue
        low, high = max(int(key[1], 16), start), min(int(key[1], 16) + length, start + size)
        if low < high:
            intervals[source].append((low, high))
    return {source: sum(high - low - image[low - image_start:high - image_start].count(0xCC)
                        for low, high in progress.merge_intervals(found))
            for source, found in intervals.items()}


def write_index(present, facts, blockers, excuses, meta, selection):
    """Called by link_census.write_status: what a per-file check needs from the
    census, in one pickle. `facts` is link_census.read_facts(present);
    `selection` holds link_census.selection_verdicts' results, holder
    exceptions and ledger owners."""
    index = {"meta": meta, **index_tables(present, facts, selection), "blockers": blockers, "excuses": excuses,
             "bytes": source_bytes(set(blockers))}
    link_census.OUT.mkdir(parents=True, exist_ok=True)
    temp = INDEX.with_suffix(".tmp")
    with temp.open("wb") as handle:
        pickle.dump(index, handle, protocol=pickle.HIGHEST_PROTOCOL)
    temp.replace(INDEX)


def index_tables(present, facts, selection):
    """The index's definition tables: every object's exclusive definitions and
    COMDAT copies by name, and the census's selection (holder exceptions,
    ledger owners)."""
    if len(present) != len(facts):
        raise ValueError("index needs facts for every census object")
    strong = collections.defaultdict(list)
    comdat = collections.defaultdict(list)
    common = collections.defaultdict(list)
    alternates = collections.defaultdict(list)
    common_facts = [link_census.common_definitions(obj) for obj in present]
    for index, (copies, defined, _, _) in enumerate(facts):
        for name in defined:
            strong[name].append(index)
        for name, digest, _, verdict in copies:
            comdat[name].append((index, digest, verdict))
        for name, size in common_facts[index].items():
            common[name].append((index, size))
        for alias, target in alternate_names(present[index]).items():
            alternates[alias].append((index, target))
    return {"objects": [obj.name for obj in present], "strong": dict(strong), "comdat": dict(comdat),
            "selection": selection, "common": dict(common), "common_schema": COMMON_SCHEMA,
            "alternates": dict(alternates)}


def require_common_index(index):
    if index.get("common_schema") != COMMON_SCHEMA or not isinstance(index.get("common"), dict):
        raise SystemExit("link_check: census index lacks complete COMMON providers; rebuild it with "
                         "python3 tools/link_census.py --build --history")
    if not isinstance(index.get("alternates"), dict):
        raise SystemExit("link_check: census index lacks the objects' /alternatename directives; rebuild it "
                         "with python3 tools/link_census.py --build --history")


def load_index():
    if not INDEX.exists():
        common = _git("rev-parse", "--path-format=absolute", "--git-common-dir").strip()
        census = Path(common).parent / "build" / "wt_link" / INDEX.relative_to(ROOT)
        raise SystemExit(
            f"link_check: no census index at {INDEX.relative_to(ROOT).as_posix()} (never tracked).\n"
            f"  copy the daily census's:  mkdir -p build/link_census && cp '{census.as_posix()}' build/link_census/\n"
            "  or build one:             python3 tools/link_census.py --build --history")
    with INDEX.open("rb") as handle:
        return pickle.load(handle)


def census_blockers():
    """{source: the census's blockers} ({object, linked, unresolved,
    duplicates, losers, addresses, wrong_selected}) from the last census's
    index: what link_rank.py and class_views.py rank, exactly as the census
    counted them."""
    return load_index()["blockers"]


def duplicate(name, position, exclusive, own, index):
    """Does link.exe report this object's definition of `name` (LNK2005 /
    LNK4006)? It compares every definition with the FIRST one in link order
    and reports the pair when either is exclusive (an ordinary section or a
    NODUPLICATES COMDAT); two SELECT_ANY copies fold silently. The census
    charges both objects of a reported pair. Measured on Open-BFME-1's
    2026-09-29 log: 2,183 of 2,183 sampled ANY/ANY pairs unreported, every
    pair with an exclusive side reported."""
    others = {i: True for i in index["strong"].get(name, ()) if i != own}
    for i, _, _ in index["comdat"].get(name, ()):
        if i != own:
            others.setdefault(i, False)
    if not others:
        return False
    first = min(others)
    if position < first:  # this object is the first definition: every later one is compared with it
        return exclusive or any(others.values())
    return exclusive or others[first]


def refresh(index, objects, truth):
    """Replace the census's definitions of `objects` with their current
    object files', so a fix in one file (a removed duplicate, a new datum) is
    seen when checking the others. Blockers of files not passed stay as the
    census saw them."""
    require_common_index(index)
    positions = {index["objects"].index(obj.name): obj for obj in objects if obj.name in index["objects"]}
    if not positions:
        return
    # Read every replacement before mutating any table. A failed read must
    # preserve the previous index, including its last COMMON provider.
    replacements = {position: (link_census.common_definitions(obj), link_census.object_facts(obj, truth),
                               alternate_names(obj))
                    for position, obj in positions.items()}
    for table, at in (("strong", lambda entry: entry), ("comdat", lambda entry: entry[0]),
                      ("common", lambda entry: entry[0]), ("alternates", lambda entry: entry[0])):
        for name, entries in index[table].items():
            if any(at(entry) in positions for entry in entries):
                index[table][name] = [entry for entry in entries if at(entry) not in positions]
    for position, (common, fact, alternates) in replacements.items():
        for alias, target in alternates.items():
            index["alternates"].setdefault(alias, []).append((position, target))
        copies, defined, _, _ = fact
        for name in defined:
            index["strong"].setdefault(name, []).append(position)
        for name, digest, _, verdict in copies:
            index["comdat"].setdefault(name, []).append((position, digest, verdict))
        for name, size in common.items():
            index["common"].setdefault(name, []).append((position, size))


def alternate_names(obj):
    """{alias: target} from the object's /alternatename linker directives
    (its .drectve section). link.exe applies every object's directives to the
    whole link: an alias nothing defines resolves to its target, so the census
    never sees it unresolved. 460 of this repository's sources use them (and
    601 of Open-BFME-1's, whose link_check does not model them yet)."""
    import struct
    try:
        data = obj.read_bytes()
    except OSError as exc:
        raise link_census.MissingObject(f"{obj}: cannot read the object ({exc})") from exc
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


def check_object(obj, index, truth, source=None):
    """{unresolved, duplicates, comdat, addresses} for one object against the index."""
    import link_debt
    require_common_index(index)
    common = link_census.common_definitions(obj)
    copies, defined, undefined, weaks = link_census.object_facts(obj, truth)
    alternates = alternate_names(obj)
    own = index["objects"].index(obj.name) if obj.name in index["objects"] else None
    position = own if own is not None else len(index["objects"])
    strong, comdat = index["strong"], index["comdat"]

    def elsewhere(name):
        return (any(i != own for i in strong.get(name, ())) or
                any(i != own for i, _, _ in comdat.get(name, ())) or
                any(i != own for i, _ in index["common"].get(name, ())))

    mine = set(defined) | {name for name, _, _, _ in copies}
    excuses = index["excuses"]

    def resolves(name):
        return (name in mine or name in common or elsewhere(name)
                or link_census.excused(name, excuses["runtime"], excuses["imported"], excuses["stubs"]))

    # An undefined alias resolves to an /alternatename target of this object's
    # or any other's when that target resolves, or is itself an alias that
    # does: link.exe follows the chain (census 2026-10-04: ShellTop.cpp links
    # through ?TheGlobalData@@3PAUGlobalData@@A -> its own V spelling ->
    # ScriptEngine_init.cpp's alias of that to TheWritableGlobalData).
    def aliased(name, seen=frozenset()):
        targets = [alternates[name]] if name in alternates else []
        targets += [target for i, target in sorted(index["alternates"].get(name, ())) if i != own]
        seen = seen | {name}
        return any(resolves(target) or (target not in seen and aliased(target, seen)) for target in targets)

    unresolved = sorted(name for name in set(undefined) - mine - set(common)
                        if not resolves(name) and not aliased(name))
    duplicates = sorted(name for name in mine if duplicate(name, position, name in set(defined), own, index))
    losers = []
    for name, digest, _, verdict in copies:
        found = [(i, d, v) for i, d, v in comdat.get(name, ()) if i != own]
        found.append((position, digest, verdict))
        found.sort(key=lambda copy: copy[0])
        loses, rule = link_census.keep_rule(found)
        if loses[position]:
            losers.append((name, rule, verdict))
    addresses = []
    if source is not None:
        try:
            addresses = link_debt.addresses((ROOT / source).read_text(encoding="utf-8", errors="replace"))
        except OSError:
            pass
    return {"unresolved": unresolved, "duplicates": duplicates, "comdat": losers, "addresses": addresses,
            "selected": wrong_selected(obj, (copies, defined, undefined, weaks), own, position, index,
                                       common_names=common)}


def new_variants(obj, index, truth):
    """COMDAT copies `obj` adds that can only hurt the link: a body no census
    object has yet that either splits a name every census object shares one
    copy of, or is proven not retail's (the ledger owns that name elsewhere).
    Copies proven retail's never count. A new file can be judged on this
    without its link position; three donor ports each adding a wrong
    AsciiString::compare(const AsciiString&) re-blocked 56 linking units."""
    copies, _, _, _ = link_census.object_facts(obj, truth)
    found = []
    for name, digest, _, verdict in copies:
        if verdict == "retail":
            continue
        existing = {d for i, d, _ in index["comdat"].get(name, ()) if index["objects"][i] != obj.name}
        if digest in existing:
            continue  # an identical copy is already linked: nothing new
        if len(existing) == 1 or verdict == "wrong":
            found.append(name)
    return found


def wrong_selected(obj, fact, own, position, index, *, common_names=()):
    """Names this object defines or references whose kept definition is proven
    not retail's, judged as the census judges them (link_census.judge_selected)
    with this object's current definitions in place of the census's. The
    holder is the census's /MAP holder while it still defines the name, else
    the first definer in link order."""
    copies, defined, _, _ = fact
    selection = index["selection"]
    exceptions, owners, objects = selection["exceptions"], selection["owners"], index["objects"]
    mine_copies = {name: (digest, verdict) for name, digest, _, verdict in copies}
    mine_strong = set(defined)
    found = []
    # A normal definition can override a TU's own COMMON. Its selected
    # strong/COMDAT body still needs the existing retail-truth check.
    for name in sorted(link_census.touched_names(fact) | set(common_names)):
        found_copies = {i: (d, v) for i, d, v in index["comdat"].get(name, ()) if i != own}
        exclusive = {i for i in index["strong"].get(name, ()) if i != own}
        if name in mine_copies:
            found_copies[position] = mine_copies[name]
        if name in mine_strong:
            exclusive.add(position)
        definers = set(found_copies) | exclusive
        if not definers:
            continue
        if name in exceptions:
            holder = exceptions[name]
            holder = holder if holder in definers else (min(definers) if holder is not None else None)
        else:
            holder = min(definers)
        label = {i: objects[i] if i < len(objects) else obj.name for i in definers}
        result = link_census.judge_selected(
            label[holder] if holder is not None else None,
            {label[i]: copy for i, copy in found_copies.items()}, set(label.values()),
            {label[i] for i in exclusive}, owners.get(name, set()))
        if result == "wrong":
            found.append(name)
    return found


def resolve(argument, index):
    """(source or None, object path) for a source path or an object path. A
    source is compiled when its object is not current (build.compile_rows); an
    object given directly must be current for its source
    (link_census.object_current): a stale object is last week's code, never
    evidence."""
    path = Path(argument)
    if path.suffix.lower() == ".obj":
        obj = path if path.is_absolute() else ROOT / path
        if not obj.is_file():
            raise SystemExit(f"link_check: {argument} does not exist; nothing to check (never LINKS)")
        by_object = {entry["object"]: source for source, entry in index["blockers"].items()}
        source = by_object.get(obj.name)
        if source is not None and not link_census.object_current(ROOT / source, obj):
            raise SystemExit(f"link_check: {obj.name} is not current for {source}; "
                             f"check the source instead (it recompiles)")
        return source, obj
    source = (path if path.is_absolute() else ROOT / path).resolve().relative_to(ROOT.resolve()).as_posix()
    outputs = build.compile_rows([], [ROOT / source])
    return source, outputs[ROOT / source]


def report(source, obj, result, index, now_bytes):
    census = index["blockers"].get(source or "", {})
    before = index["bytes"].get(source, 0) if census.get("linked") else 0
    clean = not any(result[kind] for kind in ("unresolved", "duplicates", "comdat", "addresses", "selected"))
    after = now_bytes if clean else 0
    print(f"{source or obj.name}: {'LINKS' if clean else 'does not link'}  "
          f"LINKED {before:,} -> {after:,} bytes (census {index['meta'].get('date', '?')} at "
          f"{index['meta'].get('commit', '?')}; file's own bytes {now_bytes:,})")
    for name in result["unresolved"]:
        print(f"  unresolved  {name}")
    for name in result["duplicates"]:
        print(f"  duplicate   {name}")
    for name, rule, verdict in result["comdat"]:
        why = {"wrong": "not retail's body", "unknown": "unproven and differs from the kept copy",
               None: "differs from the first copy in link order (no retail address)"}.get(verdict, verdict)
        print(f"  comdat      {name}  ({rule}: {why})")
    for name in result["selected"]:
        print(f"  selected    {name}  (the definition the link keeps is not retail's)")
    if result["addresses"]:
        print(f"  addresses   {len(result['addresses'])} hard-coded image address(es), e.g. {result['addresses'][0]}")
    return clean


def _git(*args, check=False):
    done = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    if check and done.returncode:
        raise SystemExit(f"link_check: `git {' '.join(args)}` failed ({done.stderr.strip()})")
    return done.stdout


def staged():
    """The C/C++ units staged for commit. The check compiles the working
    tree, so a unit whose working copy differs from what is staged (a
    partial `git add -p`, an edit after staging) would preview the wrong
    bytes: refuse it, as the pre-commit hook does."""
    out = _git("diff", "--cached", "--name-only", "--diff-filter=ACMR", "--", "Code/").split()
    units = [p for p in out if p.lower().endswith((".c", ".cpp"))]
    partial = _git("diff", "--name-only", "--", *units).split() if units else []
    if partial:
        raise SystemExit("link_check: --staged checks the working tree, but these staged units also have "
                         f"unstaged edits: {', '.join(partial)}; stage or stash them first")
    return units


def refresh_stale(index, truth):
    """--refresh: recompile every ledger source whose object is not current
    (build.compile_rows, the census's own compile phase) and replace those
    objects' census definitions with their new ones (refresh), so a fix
    another commit made since the census is seen."""
    rows = link_census.ledger()
    sources = [s for s in dict.fromkeys(ROOT / r["source"] for r in rows) if s.suffix.lower() != build.LIB_SUFFIX]
    stale = build.stale_sources(sources, {s: build.obj_path(s) for s in sources}, build._pool_size())
    if not stale:
        return
    outputs = build.compile_rows(rows, stale)
    refresh(index, [outputs[s] for s in stale if s in outputs], truth)
    print(f"link_check: recompiled {len(stale):,} stale ledger object(s) and replaced their census definitions")


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="*", help="sources (compiled when stale) or objects")
    ap.add_argument("--staged", action="store_true", help="check the C/C++ units staged for commit")
    ap.add_argument("--refresh", action="store_true",
                    help="first recompile every stale ledger object and replace its census definitions")
    ap.add_argument("--census-only", action="store_true",
                    help="check against the census's definitions of the given files, not their current objects")
    ap.add_argument("--new-variants", action="store_true",
                    help="with --staged or paths: refuse only a unit adding a second body for a COMDAT "
                         "every census object agrees on (works for units the census has not seen)")
    args = ap.parse_args(argv)
    paths = staged() if args.staged else args.paths
    if args.new_variants:
        if not paths:
            return 0
        if not INDEX.exists():
            print("link_check: no census index; --new-variants skipped", file=sys.stderr)
            return 0
        index, truth = load_index(), link_census.RetailTruth(link_census.ledger())
        bad = 0
        for source, obj in (resolve(path, index) for path in paths):
            for name in new_variants(obj, index, truth):
                print(f"  {source}: emits its own body for {name}, which every census object shares "
                      "one copy of: include the shared header (or keep it out of line)", file=sys.stderr)
                bad = 1
        return bad
    if not paths:
        print("link_check: nothing to check")
        return 0
    started = time.time()
    index = load_index()
    require_common_index(index)
    truth = link_census.RetailTruth(link_census.ledger())
    if args.refresh:
        refresh_stale(index, truth)
    resolved = list({obj.resolve(): (source, obj) for source, obj in
                     (resolve(path, index) for path in paths)}.values())  # a file named twice counts once
    outside = sorted(source or obj.name for source, obj in resolved if obj.name not in index["objects"])
    if outside:
        # Its link position is unknown, so neither its own duplicates nor what
        # it provides to others can be judged: two new objects defining one
        # exclusive symbol both looked clean while link.exe fails LNK2005.
        raise SystemExit(f"link_check: not in census {index['meta'].get('commit', '?')}, so not previewable "
                         f"(the next census measures it): {', '.join(outside)}")
    if not args.census_only:
        refresh(index, [obj for _, obj in resolved], truth)
    now = source_bytes({source for source, _ in resolved if source})
    clean, before, after = [], 0, 0
    for source, obj in resolved:
        try:
            result = check_object(obj, index, truth, source)
        except link_census.MissingObject as exc:
            print(f"{source or obj.name}: UNKNOWN ({exc})")
            clean.append(False)
            continue
        clean.append(report(source, obj, result, index, now.get(source, 0)))
        entry = index["blockers"].get(source or "", {})
        before += index["bytes"].get(source, 0) if entry.get("linked") else 0
        after += now.get(source, 0) if clean[-1] else 0
    print(f"link_check: {sum(clean)} of {len(clean)} link cleanly; LINKED {before:,} -> {after:,} bytes "
          f"({time.time() - started:.1f}s)")
    return 0 if all(clean) else 1


if __name__ == "__main__":
    sys.exit(main())
