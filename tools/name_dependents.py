#!/usr/bin/env python3
"""Sources whose objects reference a callee name a ledger change took away.

A unit's REL32 call sites resolve through the NAME its object binds them to
(build.load_symbol_map: every functions.csv row plus every symbols.csv pin).
Rename or delete a row, drop a pin, or move a row to another address, and
every OTHER unit that calls that name stops reproducing retail -- yet the
delta verify only rebuilds the units whose own rows changed. In a fork of this
repository, a7a39472e7 retracted `?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ`
and broke 38 rows in 40 units that still called it, with every hook green.

This lists those units so the hooks byte-verify them too:

  1. lost names: for each name, the call-target addresses the old ledger gave
     it (row target_rva, pin addresses) that the new one no longer does. A
     purely additive change loses nothing and costs nothing: the resolver
     tries candidates in order and keeps the first that reproduces retail,
     so a new candidate cannot break a call that already matched.
  2. dependents: every matched source in the NEW ledger whose cached object
     carries a lost name in its COFF symbol table. A raw bytes scan of the
     object cache narrows, and the symbol table of each hit confirms the exact
     name, so a longer mangled name containing the lost one is not a dependent.
  3. doubt widens: a source is judged on its text -- listed when it mentions
     the lost function's bare identifier -- whenever its object is no evidence
     for the source being checked: no cached object; an object whose build
     sidecar records other source text (the build re-checks currency the same
     way, by that hash); or a working copy that is not the state being checked
     (unstaged edits for --staged, a difference from B for --range), whose
     object was compiled from the wrong text. That text is then read from the
     index or from B, not from the working copy.

The object cache is the index: it is what the build compiles and verifies
against, keyed per source, so it never needs a second cache to go stale.

Data rows (reverse/data_rows.csv, tools/data_rows.py) are consumers too: a
data initializer's relocation (`int *dp = &g;`) resolves its target through
the same rows and pins, plus the data rows themselves and a function row's
object symbol (data_rows.Resolver). So a lost call target is also looked for in
every source that owns a matched data row, and a lost data home -- a data row
deleted or re-addressed, a function row's object symbol or matched status gone
-- is looked for in those sources. When only data_rows.csv changes, no call
target can be lost and functions.csv is not read.

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed A vs committed B (pre-push)
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import csv
import io
import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

LEDGER = "reverse/functions.csv"
PINS = "reverse/symbols.csv"
DATA_ROWS = "reverse/data_rows.csv"


def git_bytes(spec, root=ROOT):
    out = subprocess.run(["git", "-C", str(root), "show", spec], capture_output=True)
    return out.stdout if out.returncode == 0 else None


def csv_dicts(text):
    return list(csv.DictReader(io.StringIO(text))) if text else []


def _admitted(row):
    """Mirror load_symbol_map: an unreviewed alias row gives its name no address."""
    import build
    return not (build.is_alias_row(row) and not build.gate_baselined("alias-row", row))


def call_targets(rows, pins, admitted=_admitted):
    """name -> set of addresses the build's resolver offers for it."""
    targets = {}
    for row in rows:
        try:
            address = int(row["target_rva"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        if admitted(row):
            targets.setdefault(row["name"], set()).add(address)
    for pin in pins:
        try:
            address = int(pin["address"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        targets.setdefault(pin["name"], set()).add(address)
    return targets


def data_targets(rows, data_rows):
    """name -> the homes tools/data_rows.Resolver gives a relocation target from
    the ledger rows: a matched function row under its name and its object symbol,
    a data row at its VA. Tagged, so they never compare equal to call_targets'
    plain addresses; pins are call_targets' already. A function row's address is
    compared as written (73,000 int() calls are half this function's cost): a
    respelled address can only list more dependents, never fewer."""
    import build
    import data_rows as data_ledger
    targets = {}
    for row in rows:
        if row.get("status") != "matched":
            continue
        home = ("row", row.get("target_rva"))
        targets.setdefault(row["name"], set()).add(home)
        if "object-symbol=" in (row.get("notes") or ""):
            targets.setdefault(build.ledger_object_symbol(row), set()).add(home)
    for row in data_rows:
        try:
            address = data_ledger.va_of(row)
        except (KeyError, TypeError, ValueError):
            continue
        targets.setdefault(row["name"], set()).add(("data", address))
    return targets


def lost_names(old_targets, new_targets):
    """{name: addresses the old state resolved it to and the new one does not}."""
    lost = {}
    for name, addresses in old_targets.items():
        gone = addresses - new_targets.get(name, set())
        if gone:
            lost[name] = gone
    return lost


def _u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def coff_symbol_names(data):
    """Every symbol name in a COFF object's symbol table (aux records skipped)."""
    names = set()
    if len(data) < 20:
        return names
    table, count = _u32(data, 8), _u32(data, 12)
    strings = table + count * 18
    index = 0
    while index < count:
        entry = table + index * 18
        if entry + 18 > len(data):
            break
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + _u32(raw, 4)
            end = data.find(b"\0", start)
            name = data[start:end if end >= 0 else len(data)]
        else:
            name = raw.rstrip(b"\0")
        names.add(name.decode("latin-1"))
        index += 1 + data[entry + 17]
    return names


def bare_identifier(name):
    """The unqualified function identifier of a mangled or C name, or None."""
    match = re.match(r"\?([A-Za-z_][A-Za-z0-9_]*)@", name)
    if match:
        return match.group(1)
    if name.startswith("??"):
        # A function template (??$name@...) names itself; special members
        # (??0 ctor, ??1 dtor, ??_G ...) are named by their class, which may
        # be a template (??0?$vector@...).
        match = (re.match(r"\?\?\$([A-Za-z_][A-Za-z0-9_]*)@", name)
                 or re.match(r"\?\?(?:_[0-9A-Z]|[0-9A-Z])(?:\?\$)?([A-Za-z_][A-Za-z0-9_]*)@", name))
        return match.group(1) if match else None
    match = re.fullmatch(r"[_@]?([A-Za-z_][A-Za-z0-9_]*)(?:@\d+)?", name)
    return match.group(1) if match else None


def _row_objects(rows):
    """{source: [object paths]} for matched rows, via the build's own mapping."""
    import build
    objects = {}
    for row in rows:
        if row.get("status") != "matched" or not row.get("source"):
            continue
        # One object per compiled source; a static library has one per member.
        if row["source"] in objects and not row["source"].lower().endswith(build.LIB_SUFFIX):
            continue
        try:
            path = build.row_object(row)
        except (SystemExit, ValueError, OSError):
            path = None
        paths = objects.setdefault(row["source"], [])
        if path is not None and path not in paths:
            paths.append(path)
    return objects


def _data_row_objects(data_rows):
    """{source: [object path]} for matched data rows: data_rows.verify_row reads
    the source's own compiled object."""
    return _row_objects([{"source": row.get("source"), "status": row.get("status"), "notes": ""}
                         for row in data_rows])


def compiled_from(obj, digest):
    """True when the build's sidecar says `obj` was compiled from source text
    hashing to `digest` (build.compile_is_current's own source test)."""
    import build
    if digest is None:
        return False
    try:
        meta = json.loads(build._deps_sidecar(obj).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return False
    return isinstance(meta, dict) and meta.get("source") == digest


def dependents(lost, source_objects, root=ROOT, *, unsettled=frozenset(), committed=None,
               workers=8):
    """Sources whose objects (or, failing those, whose text) reference a lost name.

    `unsettled` names sources whose working copy is not the state being
    checked; `committed(source)` returns that state's bytes for one (None when
    the state has no such file). Both default to "the working copy is it"."""
    if not lost:
        return set()
    import build
    needles = [(name, name.encode("latin-1")) for name in lost]
    words = {bare_identifier(name) for name in lost}
    # A name with no identifier to look for (an operator template, say) can
    # be called from any text: then every source without a usable object is listed.
    word_re = (None if None in words
               else re.compile(r"\b(?:%s)\b" % "|".join(map(re.escape, sorted(words)))))
    def references_lost_name(item):
        source, objects = item
        settled = source not in unsettled
        present = [p for p in objects if p.exists()] if settled else []
        if present and not source.lower().endswith(build.LIB_SUFFIX):
            # A compiled TU's object speaks only for the text it was built from.
            digest = build._hash_file(str(root / source))
            present = [p for p in present if compiled_from(p, digest)]
        if not present:
            # No object to trust: widen on doubt rather than skip.
            if word_re is None:
                return True
            if settled or committed is None:
                try:
                    data = (root / source).read_bytes()
                except OSError:
                    data = None
            else:
                data = committed(source)
            if data is None:
                return False  # build/check_csv report a missing source on their own
            return bool(word_re.search(data.decode("utf-8", errors="replace")))
        for path in present:
            data = path.read_bytes()
            hits = [name for name, needle in needles if needle in data]
            if hits and set(hits) & coff_symbol_names(data):
                return True
        return False

    # Each source keeps the same currency and exact COFF-name checks. Overlap
    # only their file reads: opening tens of thousands of files serially is
    # expensive on Windows. map propagates read failures rather than dropping
    # a source, and the context waits for every submitted read before returning.
    items = list(source_objects.items())
    if workers == 1 or len(items) < 2:
        results = map(references_lost_name, items)
        return {source for (source, _), hit in zip(items, results) if hit}
    with ThreadPoolExecutor(max_workers=workers) as executor:
        results = executor.map(references_lost_name, items)
        return {source for (source, _), hit in zip(items, results) if hit}


def ledger_dicts(spec, root=ROOT):
    """A ledger's rows at one state; unreadable is an error, never "no rows":
    an empty old state loses nothing and an empty new one scans nothing."""
    data = git_bytes(spec, root)
    if data is None:
        raise SystemExit(f"name_dependents: cannot read {spec}")
    return csv_dicts(data.decode("utf-8", errors="replace"))


def changed_ledgers(args, root=ROOT):
    """The ledgers (functions.csv, symbols.csv, data_rows.csv) that differ
    between the two states, from one `git diff` that reads no blob."""
    against = ["--cached", "HEAD"] if args.staged else list(args.range)
    out = subprocess.run(["git", "-C", str(root), "diff", "--name-only", "-z", *against, "--",
                          LEDGER, PINS, DATA_ROWS], capture_output=True)
    if out.returncode:
        raise SystemExit("name_dependents: cannot compare the ledgers")
    return {p.decode("utf-8", errors="surrogateescape") for p in out.stdout.split(b"\0") if p}


def ledgers_differ(args, root=ROOT):
    """False when no ledger changes: every name keeps exactly its targets."""
    return bool(changed_ledgers(args, root))


def states(args, root=ROOT):
    if args.staged:
        old, new = "HEAD:", ":"
    else:
        old, new = f"{args.range[0]}:", f"{args.range[1]}:"
    return ((ledger_dicts(old + LEDGER, root), ledger_dicts(old + PINS, root)),
            (ledger_dicts(new + LEDGER, root), ledger_dicts(new + PINS, root)))


def data_dicts(state, root=ROOT):
    """data_rows.csv's rows at `state` ("HEAD:", ":" or "<ref>:"). It is younger
    than the other ledgers, so a state may lack it: no rows only where git lists
    no such path there; unreadable is an error."""
    listing = (["ls-files", "-z", "--", DATA_ROWS] if state == ":"
               else ["ls-tree", "-z", "--name-only", state[:-1], "--", DATA_ROWS])
    out = subprocess.run(["git", "-C", str(root), *listing], capture_output=True)
    if out.returncode:
        raise SystemExit(f"name_dependents: cannot list {state}{DATA_ROWS}")
    return ledger_dicts(state + DATA_ROWS, root) if out.stdout.strip(b"\0") else []


def data_loaders(args, changed, root=ROOT):
    """(old, new) loaders of data_rows.csv for dependent_sources; old is None when
    the ledger is the same in both states, so its rows are read only for a scan."""
    old, new = ("HEAD:", ":") if args.staged else (f"{args.range[0]}:", f"{args.range[1]}:")
    return ((lambda: data_dicts(old, root)) if DATA_ROWS in changed else None,
            lambda: data_dicts(new, root))


def working_copy(args, root=ROOT):
    """(paths whose working copy differs from the checked state, reader of that state)."""
    against = [] if args.staged else [args.range[1]]
    out = subprocess.run(["git", "-C", str(root), "diff", "--name-only", "-z", *against, "--"],
                         capture_output=True, check=True).stdout
    unsettled = {p.decode("utf-8", errors="surrogateescape") for p in out.split(b"\0") if p}
    prefix = ":" if args.staged else f"{args.range[1]}:"
    return unsettled, lambda source: git_bytes(prefix + source, root)


def dependent_sources(old_rows, old_pins, new_rows, new_pins, *, admitted=_admitted,
                      objects_of=_row_objects, root=ROOT, report=None, working=None,
                      old_data=(), new_data=(), data_objects_of=_data_row_objects):
    """Sources to re-verify. old_data/new_data are data rows or zero-argument
    loaders of them; old_data None means data_rows.csv did not change, and its
    rows (tagged apart from a function row's) then lose nothing."""
    def load(data):
        return data() if callable(data) else data
    lost = lost_names(call_targets(old_rows, old_pins, admitted),
                      call_targets(new_rows, new_pins, admitted))
    if old_data is None:
        lost_data = lost_names(data_targets(old_rows, ()), data_targets(new_rows, ()))
    else:
        old_data, new_data = load(old_data), load(new_data)
        lost_data = lost_names(data_targets(old_rows, old_data), data_targets(new_rows, new_data))
    if not lost and not lost_data:
        return set()
    new_data = load(new_data)
    started = time.monotonic()
    data_objects = data_objects_of(new_data)
    unsettled, committed = working() if working is not None else (frozenset(), None)
    found = set()
    scanned = set(data_objects)
    if lost:
        # a call target is a data initializer's relocation target too
        objects = {source: list(paths) for source, paths in objects_of(new_rows).items()}
        for source, paths in data_objects.items():
            objects.setdefault(source, []).extend(p for p in paths if p not in objects[source])
        scanned |= set(objects)
        found |= dependents(lost, objects, root, unsettled=unsettled, committed=committed)
    if lost_data:
        found |= dependents(lost_data, data_objects, root, unsettled=unsettled, committed=committed)
    if report is not None:
        names = sorted(set(lost) | set(lost_data))
        print(f"name_dependents: {len(lost)} call target(s) and {len(lost_data)} data-row "
              f"target(s) lost ({', '.join(names[:3])}{', ...' if len(names) > 3 else ''}); "
              f"{len(found)} referencing unit(s) of {len(scanned)} scanned in "
              f"{time.monotonic() - started:.1f}s", file=report)
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    args = parser.parse_args()
    changed = changed_ledgers(args)
    if not changed:
        return
    if changed - {DATA_ROWS}:
        (old_rows, old_pins), (new_rows, new_pins) = states(args)
    else:
        # only data rows moved: no call target and no function row's home can be lost
        old_rows, old_pins, new_rows, new_pins = [], [], [], []
    old_data, new_data = data_loaders(args, changed)
    found = dependent_sources(old_rows, old_pins, new_rows, new_pins, report=sys.stderr,
                              working=lambda: working_copy(args),
                              old_data=old_data, new_data=new_data)
    sys.stdout.reconfigure(newline="\n")
    for source in sorted(found):
        print(source)


if __name__ == "__main__":
    main()
