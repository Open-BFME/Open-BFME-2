#!/usr/bin/env python3
"""Rank classes by how many units declare their own private copy of them.

Most BFME2 units are self-contained: each declares the classes it touches,
often as a layout view (padding up to the members it reads). Two views of
one class in two units are harmless while each unit is only byte-matched,
but they block linking: a member one view declares inline is a COMDAT the
other view compiles differently, a member one view never declares is an
unresolved name, and a hand-written vtable store is an absolute address.
Reconciling a class onto one shared header removes all three at once, for
every unit that adopts it.

For each class name this reports:

  units      units in the ledger that declare a body for it
  layouts    distinct declarations (whitespace and comments ignored)
  unlinked   matched bytes in those units that do not link today
             (reverse/link_status.csv, from tools/link_census.py)
  header     a canonical header registered for it in
             reverse/canonical_classes.csv, if any

Sorted by unlinked bytes: the classes whose reconciliation reaches the
most code that is matched but not yet linkable.

--blockers ranks instead by what the last link census (build/link_census/)
holds against each class: the unresolved, duplicate, losing-COMDAT and
wrong_selected names whose scope is the class, each weighted by the matched bytes of the units it
blocks divided among that unit's blocker names. That is the better guide to
which reconciliation pays: a class can have many private views that agree
on everything the linker sees.

--shims NAME lists the shim headers under reference/shims that define NAME
and how many units put each on their include path: competing shared
definitions are the same problem one level up (RenderObjClass has ten).

Usage:
  python3 tools/class_views.py [--top N] [--class NAME] [--min-units N] [--blockers]
  python3 tools/class_views.py --shims NAME

--class NAME lists every unit declaring NAME, grouped by layout, with the
unit's link status and matched bytes: the work list for reconciling it.
"""
import argparse
import collections
import csv
import hashlib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CANONICAL = ROOT / "reverse" / "canonical_classes.csv"

# A class-head at namespace scope: `class Name` / `struct Name`, optionally
# with a base clause, opening a body. Templates and nested types are
# skipped (their name alone does not identify one class).
HEAD = re.compile(r"^(?:class|struct)\s+(?:__declspec\([^)]*\)\s+)?([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)\s*(?::(?!:)[^{;]*)?\{", re.M)
COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def canonical_classes():
    """{class name: header path} from reverse/canonical_classes.csv."""
    if not CANONICAL.exists():
        return {}
    with CANONICAL.open(newline="", encoding="utf-8") as handle:
        return {row["class"]: row["header"] for row in csv.DictReader(handle) if row.get("class")}


def ledger_sources():
    """{source: matched bytes} over authored (non-generated) ledger rows."""
    sizes = collections.Counter()
    seen = set()
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            source = row["source"]
            if row["status"] != "matched" or source.startswith(("Code/gen_asm/", "Code/gen_small/")):
                continue
            if not source.lower().endswith((".cpp", ".c")):
                continue
            key = (source, row["target_rva"])
            if key in seen:
                continue
            seen.add(key)
            try:
                sizes[source] += int(row["target_size"], 0)
            except ValueError:
                pass
    return sizes


def link_status():
    path = ROOT / "reverse" / "link_status.csv"
    if not path.exists():
        return {}
    with path.open(newline="", encoding="utf-8") as handle:
        return {row["source"]: row["linked"] == "yes" for row in csv.DictReader(handle)}


def class_bodies(text):
    """{class name: normalised declaration} for each namespace-scope body."""
    found = {}
    stripped = COMMENT.sub("", text)
    for match in HEAD.finditer(stripped):
        line_start = stripped.rfind("\n", 0, match.start()) + 1
        if stripped[line_start:match.start()].strip():
            continue
        # skip `template <...>` heads: the previous non-blank line ends in '>'
        before = stripped[:line_start].rstrip()
        if before.endswith(">") and re.search(r"template\s*<[^;{}]*>$", before):
            continue
        depth, index = 1, match.end()
        while depth and index < len(stripped):
            char = stripped[index]
            if char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
            index += 1
        body = " ".join(stripped[match.start():index].split())
        found.setdefault(match.group(1), body)
    return found


def survey():
    sizes = ledger_sources()
    status = link_status()
    views = collections.defaultdict(dict)  # class -> {source: digest}
    for source in sizes:
        try:
            text = (ROOT / source).read_text(encoding="latin-1")
        except OSError:
            continue
        for name, body in class_bodies(text).items():
            views[name][source] = hashlib.sha1(body.encode("latin-1")).hexdigest()[:10]
    return views, sizes, status


SCOPE = re.compile(r"^\?{1,2}[^@]*@([A-Za-z_]\w*)@@")


def symbol_class(name):
    """The innermost scope of a decorated member name, e.g. ?str@AsciiString@@.. -> AsciiString."""
    found = SCOPE.match(name)
    return found.group(1) if found else None


def census_blockers():
    """{source: set of blocking names} the last census counted (its index,
    link_check.census_blockers): unresolved names, duplicates, COMDAT losers
    and wrong_selected names."""
    sys.path.insert(0, str(ROOT / "tools"))
    import link_check
    out = collections.defaultdict(set)
    for source, entry in link_check.census_blockers().items():
        out[source] |= (set(entry["unresolved"]) | set(entry["duplicates"]) | set(entry["losers"])
                        | set(entry.get("wrong_selected", ())))
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--top", type=int, default=40)
    parser.add_argument("--min-units", type=int, default=2)
    parser.add_argument("--class", dest="name")
    parser.add_argument("--blockers", action="store_true")
    parser.add_argument("--shims", metavar="NAME")
    args = parser.parse_args(argv)
    if args.shims:
        users = collections.Counter()
        flag = re.compile(r"/I\s*reference/shims/([\w.-]+)")
        for source in ledger_sources():
            try:
                first = (ROOT / source).read_text(encoding="latin-1").split("\n", 1)[0]
            except OSError:
                continue
            for directory in set(flag.findall(first)):
                users[directory] += 1
        head = re.compile(r"^(?:class|struct)\s+" + re.escape(args.shims) + r"\b[^;]*?\{", re.M)
        print(f"{'units':>6}  header defining {args.shims}")
        for header in sorted((ROOT / "reference" / "shims").rglob("*.h")):
            try:
                text = COMMENT.sub("", header.read_text(encoding="latin-1"))
            except OSError:
                continue
            if head.search(text):
                directory = header.relative_to(ROOT / "reference" / "shims").parts[0]
                print(f"{users[directory]:6}  {header.relative_to(ROOT).as_posix()}")
        return 0
    if args.blockers:
        sizes = ledger_sources()
        weight = collections.Counter()
        units = collections.defaultdict(set)
        for source, names in census_blockers().items():
            if not names or source not in sizes:
                continue
            for name in names:
                owner = symbol_class(name)
                if owner:
                    weight[owner] += sizes[source] / len(names)
                    units[owner].add(source)
        canon = canonical_classes()
        print(f"{'bytes':>9} {'units':>6}  class  [canonical header]")
        for owner, value in weight.most_common(args.top):
            print(f"{int(value):9} {len(units[owner]):6}  {owner}  {canon.get(owner, '')}")
        return 0
    views, sizes, status = survey()
    canon = canonical_classes()
    if args.name:
        units = views.get(args.name, {})
        groups = collections.defaultdict(list)
        for source, digest in units.items():
            groups[digest].append(source)
        print(f"{args.name}: {len(units)} units, {len(groups)} layouts, header: {canon.get(args.name, '-')}")
        for digest, sources in sorted(groups.items(), key=lambda kv: -len(kv[1])):
            print(f"\nlayout {digest} ({len(sources)} units)")
            for source in sorted(sources, key=lambda s: -sizes[s]):
                linked = {True: "linked", False: "unlinked"}.get(status.get(source), "?")
                print(f"  {sizes[source]:7} {linked:8} {source}")
        return 0
    rows = []
    for name, units in views.items():
        if len(units) < args.min_units:
            continue
        unlinked = sum(sizes[s] for s in units if status.get(s) is False)
        rows.append((unlinked, len(units), len(set(units.values())), name))
    rows.sort(reverse=True)
    print(f"{'unlinked':>9} {'units':>6} {'layouts':>7}  class  [canonical header]")
    for unlinked, count, layouts, name in rows[:args.top]:
        print(f"{unlinked:9} {count:6} {layouts:7}  {name}  {canon.get(name, '')}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
