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

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed A vs committed B (pre-push)
"""
import argparse
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


def dependents(lost, source_objects, root=ROOT, *, unsettled=frozenset(), committed=None):
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
    found = set()
    for source, objects in source_objects.items():
        settled = source not in unsettled
        present = [p for p in objects if p.exists()] if settled else []
        if present and not source.lower().endswith(build.LIB_SUFFIX):
            # A compiled TU's object speaks only for the text it was built from.
            digest = build._hash_file(str(root / source))
            present = [p for p in present if compiled_from(p, digest)]
        if not present:
            # No object to trust: widen on doubt rather than skip.
            if word_re is None:
                found.add(source)
                continue
            if settled or committed is None:
                try:
                    data = (root / source).read_bytes()
                except OSError:
                    data = None
            else:
                data = committed(source)
            if data is None:
                continue  # build/check_csv report a missing source on their own
            if word_re.search(data.decode("utf-8", errors="replace")):
                found.add(source)
            continue
        for path in present:
            data = path.read_bytes()
            hits = [name for name, needle in needles if needle in data]
            if hits and set(hits) & coff_symbol_names(data):
                found.add(source)
                break
    return found


def ledger_dicts(spec, root=ROOT):
    """A ledger's rows at one state; unreadable is an error, never "no rows":
    an empty old state loses nothing and an empty new one scans nothing."""
    data = git_bytes(spec, root)
    if data is None:
        raise SystemExit(f"name_dependents: cannot read {spec}")
    return csv_dicts(data.decode("utf-8", errors="replace"))


def ledgers_differ(args, root=ROOT):
    """False when neither ledger changes: every name keeps exactly its targets."""
    against = ["--cached", "HEAD"] if args.staged else list(args.range)
    out = subprocess.run(["git", "-C", str(root), "diff", "--quiet", *against, "--", LEDGER, PINS])
    if out.returncode not in (0, 1):
        raise SystemExit("name_dependents: cannot compare the ledgers")
    return out.returncode == 1


def states(args, root=ROOT):
    if args.staged:
        old, new = "HEAD:", ":"
    else:
        old, new = f"{args.range[0]}:", f"{args.range[1]}:"
    return ((ledger_dicts(old + LEDGER, root), ledger_dicts(old + PINS, root)),
            (ledger_dicts(new + LEDGER, root), ledger_dicts(new + PINS, root)))


def working_copy(args, root=ROOT):
    """(paths whose working copy differs from the checked state, reader of that state)."""
    against = [] if args.staged else [args.range[1]]
    out = subprocess.run(["git", "-C", str(root), "diff", "--name-only", "-z", *against, "--"],
                         capture_output=True, check=True).stdout
    unsettled = {p.decode("utf-8", errors="surrogateescape") for p in out.split(b"\0") if p}
    prefix = ":" if args.staged else f"{args.range[1]}:"
    return unsettled, lambda source: git_bytes(prefix + source, root)


def dependent_sources(old_rows, old_pins, new_rows, new_pins, *, admitted=_admitted,
                      objects_of=_row_objects, root=ROOT, report=None, working=None):
    lost = lost_names(call_targets(old_rows, old_pins, admitted),
                      call_targets(new_rows, new_pins, admitted))
    if not lost:
        return set()
    started = time.monotonic()
    objects = objects_of(new_rows)
    unsettled, committed = working() if working is not None else (frozenset(), None)
    found = dependents(lost, objects, root, unsettled=unsettled, committed=committed)
    if report is not None:
        print(f"name_dependents: {len(lost)} call target(s) lost "
              f"({', '.join(sorted(lost)[:3])}{', ...' if len(lost) > 3 else ''}); "
              f"{len(found)} referencing unit(s) of {len(objects)} scanned in "
              f"{time.monotonic() - started:.1f}s", file=report)
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    args = parser.parse_args()
    if not ledgers_differ(args):
        return
    (old_rows, old_pins), (new_rows, new_pins) = states(args)
    found = dependent_sources(old_rows, old_pins, new_rows, new_pins, report=sys.stderr,
                              working=lambda: working_copy(args))
    sys.stdout.reconfigure(newline="\n")
    for source in sorted(found):
        print(source)


if __name__ == "__main__":
    main()
