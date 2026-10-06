#!/usr/bin/env python3
"""Duplicate definitions and divergent COMDAT copies across the tree's objects.

Two failures a per-function gate cannot see, because each copy verifies on its
own (research 18, 29):

  duplicate   a name several objects define and at least one exclusively (an
              ordinary section, or a NODUPLICATES COMDAT, which /Gy gives every
              non-inline function). A link without /FORCE stops on it
              (LNK2005); with /FORCE link.exe keeps the first in link order.
  divergent   a COMDAT name whose copies differ in bytes or relocation targets.
              link.exe keeps one without a word (the WWMath library trial found
              50), so what runs depends on link order.

For each name the copy that should win is the ledger owner's (the object of a
row naming it: that copy is byte-verified at retail's address); the copy the
link keeps is the first exclusive one, else the first in link order
(link_census.link_order is retail's order). The kept copy is then certified
against retail (link_census.RetailTruth: bytes and resolved relocations at the
name's address): `retail`, `wrong`, `unknown`, or `none` when the name has no
retail address to judge by.

Debt is keyed (class, name) in reverse/dup_defs_baseline.tsv, shrink-only:
`--check` fails on a key that is not in it (a new duplicate, or a divergent
COMDAT whose kept copy is not certified retail), `--write-baseline` refuses to
add keys. Fix by removing the non-owner definition (make it a declaration) or
making the copies agree; `--candidates` lists the duplicates where that is
mechanical: the extra copy is byte-identical to the owner's, so dropping it
changes no linked byte.

  python3 tools/dup_defs.py                 report + build/allowed_symbols/dup_defs.tsv
  python3 tools/dup_defs.py --check         exit 1 on debt not in the baseline
  python3 tools/dup_defs.py --write-baseline   shrink the baseline to today's debt
  python3 tools/dup_defs.py --candidates    mechanical removals (identical non-owner copies)
"""
import argparse
import collections
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import allowed_symbols as allowed  # noqa: E402
import build  # noqa: E402
import link_census as census  # noqa: E402

BASELINE = ROOT / "reverse" / "dup_defs_baseline.tsv"
HEADER = ("# Duplicate definitions and divergent COMDATs, keyed (class, name). Shrink-only:\n"
          "# written by tools/dup_defs.py --write-baseline, which never adds a key.\n")
# Retail bodies the linker supplies from msvcrt/libcmt, or that every TU emits by
# design; their copies are the CRT's, not the tree's.
IGNORE_PREFIX = ("??_C@", "__real@", "??_R", "__CT", "__TI", "__CTA", "_TI", "_CTA")


def owners_by_name(rows):
    """{name: {object path}} of the rows naming it (its object symbol too)."""
    out = collections.defaultdict(set)
    for row in rows:
        if "icf-owner=" in (row.get("notes") or ""):
            continue
        for name in {row["name"], build.ledger_object_symbol(row)}:
            out[name].add(str(build.row_object(row)))
    return out


def analyse(rows, defs, truth):
    """[{class, name, copies, variants, kept, kept_verdict, owner, owner_kept,
    identical_extras}] for every duplicate or divergent name."""
    owners = owners_by_name(rows)
    out = []
    for name, copies in defs.items():
        if len(copies) < 2 or name.startswith(IGNORE_PREFIX):
            continue
        objs = {c[0] for c in copies}
        if len(objs) < 2:
            continue
        excl = [c for c in copies if c[3]]
        variants = len({c[1] for c in copies})
        if len(excl) >= 1 and len(objs) >= 2 and (len(excl) >= 2 or len(excl) < len(copies)):
            cls = "duplicate"
        elif variants > 1:
            cls = "divergent"
        else:
            continue
        kept = (excl or copies)[0]
        mine = owners.get(name, set()) & objs
        owner_copy = next((c for c in copies if c[0] in mine), None)
        verdict = kept_verdict(truth, name, kept)
        extras = [c for c in copies if owner_copy and c[0] != owner_copy[0] and c[1] == owner_copy[1]]
        out.append({"class": cls, "name": name, "copies": len(copies), "variants": variants,
                    "kept": rel(kept[0]), "kept_verdict": verdict,
                    "owner": rel(owner_copy[0]) if owner_copy else "",
                    "owner_kept": bool(owner_copy and owner_copy[0] == kept[0]),
                    "identical_extras": [rel(c[0]) for c in extras]})
    return sorted(out, key=lambda d: (d["class"], d["name"]))


def kept_verdict(truth, name, kept):
    """retail / wrong / unknown / none for the kept copy at the name's retail address."""
    o = allowed.Obj(kept[0])
    sym = o.by_name.get(name)
    if sym is None:
        return "unknown"
    raw, size, relocs = o.body(sym)
    base = sym["value"]
    relocs = [(w, k, {**r, "value": r["value"] - base} if r["section"] == sym["section"] else r)
              for w, k, r in relocs]
    v = truth.verdict({**sym, "value": 0}, raw, relocs, kept[1], size)
    return v or "none"


def debt(found):
    """Keys the baseline holds: every duplicate, and a divergent COMDAT whose kept
    copy is not certified retail."""
    return {f"{d['class']}\t{d['name']}" for d in found
            if d["class"] == "duplicate" or d["kept_verdict"] != "retail"}


def rel(path):
    try:
        return Path(path).resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return str(path)


def read_baseline(path=BASELINE):
    if not path.exists():
        return set()
    return {line.rstrip("\n") for line in path.read_text(encoding="utf-8").splitlines(True)
            if line.strip() and not line.startswith("#")}


def load():
    rows = census.ledger()
    objs, _ = census.objects(rows, data=[])
    defs = allowed.definitions(objs)
    return rows, defs, census.RetailTruth(rows)


def write_report(found, path):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as fh:
        w = csv.writer(fh, delimiter="\t", lineterminator="\n")
        w.writerow(["class", "name", "copies", "variants", "kept", "kept_verdict", "owner", "owner_kept",
                    "identical_extras"])
        for d in found:
            w.writerow([d["class"], d["name"], d["copies"], d["variants"], d["kept"], d["kept_verdict"],
                        d["owner"], int(d["owner_kept"]), ";".join(d["identical_extras"])])


SIMPLE = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@[^@?]*$")


def definition_span(text, name):
    """(start, end) of the one column-0 out-of-line definition of a simple member
    `?method@Class@@...` in `text` (through its closing brace and newline), or
    None when there is not exactly one, or its braces do not balance."""
    m = SIMPLE.match(name)
    if not m:
        return None
    method, cls = m.groups()
    head = re.compile(r"^[^\s#/][^;{}\n]*\b" + re.escape(cls) + r"::" + re.escape(method) + r"\s*\(", re.M)
    hits = list(head.finditer(text))
    if len(hits) != 1:
        return None
    start = hits[0].start()
    # keep a comment block directly above with the definition it describes
    while True:
        prev = text.rfind("\n", 0, max(start - 1, 0))
        line = text[prev + 1:start - 1] if start else ""
        if start and line.lstrip().startswith("//"):
            start = prev + 1
        elif start and line.rstrip().endswith("*/"):
            opened = text.rfind("/*", 0, start)
            if opened < 0:
                break
            start = text.rfind("\n", 0, opened) + 1
        else:
            break
    brace = text.find("{", hits[0].end())
    if brace < 0 or ";" in text[hits[0].end():brace]:
        return None
    depth, i = 0, brace
    while i < len(text):
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                end = text.find("\n", i)
                end = len(text) if end < 0 else end + 1
                if text[end:end + 1] in ("\n", "\r"):
                    end = text.find("\n", end) + 1 or len(text)
                return start, end
        elif c in "\"'":                     # skip a literal so a brace in it does not count
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j
        i += 1
    return None


def remove_identical_extras(found, rows, limit=0):
    """Delete, from the source of each non-owner object, a definition byte-identical
    to the owner's copy (so the link keeps the same bytes either way). Only simple
    member names with exactly one column-0 definition in that source; the caller
    re-verifies every touched source with the gate and reverts on failure.
    {source: [names removed]}."""
    source_of = {}
    for row in rows:
        source_of.setdefault(rel(build.row_object(row)), row["source"])
    plan = collections.defaultdict(list)
    for d in found:
        if d["class"] == "duplicate" and d["owner"]:
            for extra in d["identical_extras"]:
                src = source_of.get(extra)
                if src and src.endswith(".cpp") and src != source_of.get(d["owner"]):
                    plan[src].append(d["name"])
    done = {}
    for src in sorted(plan):
        if limit and len(done) >= limit:
            break
        path = ROOT / src
        with path.open(encoding="utf-8", errors="surrogateescape", newline="") as fh:
            text = fh.read()                 # line endings kept as they are on disk
        spans, names = [], []
        for name in plan[src]:
            span = definition_span(text, name)
            if span:
                spans.append(span)
                names.append(name)
        if not spans:
            continue
        for a, b in sorted(spans, reverse=True):
            text = text[:a] + text[b:]
        path.write_text(text, encoding="utf-8", errors="surrogateescape", newline="")
        done[src] = names
    return done


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--write-baseline", action="store_true")
    ap.add_argument("--candidates", action="store_true")
    ap.add_argument("--remove", action="store_true",
                    help="delete identical non-owner copies from their sources (then run the gate on them)")
    ap.add_argument("--limit", type=int, default=0, help="--remove: at most N sources")
    args = ap.parse_args(argv)
    rows, defs, truth = load()
    found = analyse(rows, defs, truth)
    write_report(found, allowed.OUT / "dup_defs.tsv")
    keys = debt(found)
    by = collections.Counter(d["class"] for d in found)
    kv = collections.Counter((d["class"], d["kept_verdict"]) for d in found)
    print("duplicate names:", by["duplicate"], "divergent COMDATs:", by["divergent"])
    for (cls, v), n in sorted(kv.items()):
        print(f"  {cls:9} kept={v:8} {n}")
    print("duplicates whose kept copy is not the owner's:",
          sum(1 for d in found if d["class"] == "duplicate" and d["owner"] and not d["owner_kept"]))
    if args.candidates:
        for d in found:
            if d["class"] == "duplicate" and d["identical_extras"]:
                print("\t".join((d["name"], d["owner"], ";".join(d["identical_extras"]))))
    if args.remove:
        done = remove_identical_extras(found, rows, args.limit)
        for src, names in sorted(done.items()):
            print("removed %d from %s" % (len(names), src))
        return 0
    base = read_baseline()
    if args.write_baseline:
        if base and keys - base:
            print("refusing to add %d keys to the baseline" % len(keys - base), file=sys.stderr)
            return 1
        BASELINE.write_text(HEADER + "".join(k + "\n" for k in sorted(keys)), encoding="utf-8", newline="\n")
        print("baseline:", len(keys))
    if args.check:
        new = sorted(keys - base)
        for k in new:
            print("  new:", k.replace("\t", " "), file=sys.stderr)
        return 1 if new else 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
