#!/usr/bin/env python3
"""Rank link blockers by the matched bytes they keep from linking.

A matched row whose unit cannot link is half done: the bytes are proved,
but the unit is not yet part of a buildable game. This reads the last link
census (build/link_census/, written by tools/link_census.py) and says where
a fix pays most.

For every ledger unit it collects what holds the unit back:

  U name   an unresolved name the unit references
  D name   a name the unit and another unit both define
  L name   a COMDAT copy the unit compiled that is not retail's body
           (link_census.keep_rule)
  S name   a name the unit defines or references whose definition the link
           keeps is proven not retail's (link_census wrong_selected)
  A        a hard-coded image address in the source (tools/link_debt.py)

and reports:

  sole     blockers that are a unit's ONLY blocker, by that unit's bytes:
           fix one, a unit links
  names    every blocking name by bytes shared out among the blockers of
           the units it blocks: what a fix moves overall
  near     units with at most --near blockers, largest first: the work list

and, never as a blocker, the diagnostic the census keeps for copies its
`unreferenced` rule exempts (link_census.unreferenced_differs):

  V name   a copy of a no-address COMDAT nothing the link keeps references
           that differs from the majority copy; layout-like (same length, a
           few bytes off) is the signature of a stale private class view

Usage:
  python3 tools/link_rank.py [--top N] [--near K] [--kind U|D|L|S|A] [--json PATH]
  python3 tools/link_rank.py --file SOURCE     one unit's blockers (and V diagnostics)
  python3 tools/link_rank.py --stale-views     units by layout-like V copies
  python3 tools/link_rank.py --owner-gaps --near 3   unresolved names with recovered address candidates

Fetch the published index with tools/link_check.py --fetch-index. This reads
the blockers the last measured census recorded, not current link results;
refreshing the provider index does not refresh its recorded blockers. Units
absent from that census have unknown link state. Check a candidate's current
providers and consumers with tools/link_check.py before starting a repair.
"""
import argparse
import collections
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import link_census as lc  # noqa: E402


def blockers(index=None):
    """({source: {(kind, name)}}, {source: matched bytes}), the blockers the
    last census itself counted (link_check.census_blockers: its index), so a
    unit this calls linked is one the census counts as linked."""
    import link_check
    rows = lc.ledger()
    census = link_check.census_blockers() if index is None else index["blockers"]
    sizes, seen = collections.Counter(), set()
    for row in rows:
        source = row["source"]
        if not source.lower().endswith((".c", ".cpp")):
            continue
        key = (source, row["target_rva"])
        if key not in seen:
            seen.add(key)
            sizes[source] += int(row["target_size"] or 0, 0)
    out = {}
    for source, entry in census.items():
        found = {("U", s) for s in entry["unresolved"]}
        found |= {("D", s) for s in entry["duplicates"]}
        found |= {("L", s) for s in entry["losers"]}
        found |= {("S", s) for s in entry.get("wrong_selected", ())}
        if entry["addresses"]:
            found.add(("A", ""))
        out[source] = found
    return out, sizes


def stale_views(index=None):
    """{source: [unreferenced_differs entry]} from the last census's index."""
    import link_check
    census = link_check.census_blockers() if index is None else index["blockers"]
    return {source: entry.get("unreferenced_differs", [])
            for source, entry in census.items() if entry.get("unreferenced_differs")}


def report_snapshot(meta):
    date = meta.get("census_date", meta.get("date", "unknown"))
    commit = meta.get("census_commit", meta.get("commit", "unknown"))
    print(f"Census blockers: {date} at {commit}; current objects have not been checked.")
    if (date, commit) != (meta.get("date"), meta.get("commit")):
        print(f"Provider index updated {meta.get('date', 'unknown')} at "
              f"{meta.get('commit', 'unknown')}; recorded blockers unchanged.")


def generated(source):
    return source.startswith(("Code/gen_asm/", "Code/gen_small/"))


def owner_gaps(found, sizes, rows, symbols):
    """Discovery leads, never identity proof or predicted linked-byte gains.

    Preserve every additive resolver candidate. A pin can be wrong, so an
    address coincidence cannot authorize rebinding a caller to its owner.
    Count each consumer once, even when it has several names for one address.
    """
    users = collections.defaultdict(set)
    for source, blockers in found.items():
        if not generated(source):
            for kind, name in blockers:
                if kind == "U":
                    users[name].add(source)
    addresses = {rva for name in users for rva in symbols.get(name, ())}
    owners = collections.defaultdict(set)
    for row in rows:
        if row.get("status") != "matched":
            continue
        rva = int(row["target_rva"], 0)
        if rva in addresses:
            owners[rva].add((row["name"], row["source"]))
    out = []
    for name, consumers in users.items():
        candidates = []
        for rva in sorted(set(symbols.get(name, ()))):
            for owner, source in sorted(owners[rva]):
                kind = ("recovery" if generated(source) else
                        "provider-refresh" if owner == name else "identity-gap")
                candidates.append(dict(rva=f"0x{rva:08X}", name=owner, source=source, kind=kind))
        if not candidates:
            continue
        out.append(dict(name=name, consumers=sorted(consumers), candidates=candidates,
                        affected_bytes=sum(sizes.get(s, 0) for s in consumers),
                        shared_bytes=sum(sizes.get(s, 0) / len(found[s]) for s in consumers),
                        min_blockers=min(len(found[s]) for s in consumers)))
    return sorted(out, key=lambda item: (-item["shared_bytes"], -item["affected_bytes"], item["name"]))


def report_owner_gaps(args, found, sizes, index=None):
    import build
    import link_check
    meta = (link_check.load_index() if index is None else index)["meta"]
    if args.file:
        found = {args.file: found.get(args.file, set())}
    else:
        found = {s: b for s, b in found.items() if 0 < len(b) <= args.near}
    leads = owner_gaps(found, sizes, lc.ledger(), build.load_symbol_map())
    if args.json:
        Path(args.json).write_text(json.dumps(dict(census=meta, leads=leads), indent=2), encoding="utf-8")
    print(f"{len(leads):,} unresolved names have matched retail-address candidates")
    print("Discovery only: additive pins are hypotheses, not identity or ABI proof.")
    print("provider-refresh: owner already exists; check current provider and consumer together.")
    print("identity-gap: inspect native calls, ABI and ownership before changing declarations.")
    print("recovery: generated owner still needs real source. Byte figures overlap; no gain is claimed.")
    for lead in leads[:args.top]:
        print(f"\n  shared {int(lead['shared_bytes']):,} B; affected {lead['affected_bytes']:,} B; "
              f"{len(lead['consumers'])} units; nearest {lead['min_blockers']} blocker(s)")
        print(f"  U {lead['name']}")
        for candidate in lead["candidates"][:6]:
            print(f"    {candidate['kind']} {candidate['rva']} {candidate['name']}")
            print(f"      {candidate['source']}")
        if len(lead["candidates"]) > 6:
            print(f"    ... {len(lead['candidates']) - 6} more candidates (all retained by --json)")
        for consumer in lead["consumers"]:
            print(f"    consumer {consumer}")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--top", type=int, default=30)
    parser.add_argument("--near", type=int, default=3)
    parser.add_argument("--kind", choices="UDLSA")
    parser.add_argument("--file")
    parser.add_argument("--json", help="write {source: [[kind, name], ...]} here")
    parser.add_argument("--owner-gaps", action="store_true",
                        help="trace unresolved names to recovered address candidates (within --near); --json writes leads")
    parser.add_argument("--stale-views", action="store_true",
                        help="list units by layout-like V copies (diagnostic, not blockers), largest first")
    parser.add_argument("--all-kinds", action="store_true",
                        help="with --stale-views: count every V copy, codegen-like and relocation too")
    args = parser.parse_args(argv)
    if args.owner_gaps and (args.stale_views or args.all_kinds or args.kind):
        parser.error("--owner-gaps cannot combine with --stale-views, --all-kinds or --kind")
    import link_check
    index = link_check.load_index()
    found, sizes = blockers(index)
    report_snapshot(index.get("meta", {}))
    if args.file and args.file not in found:
        print(f"{args.file}: not in census; current link state unknown.")
        print("Check current providers with tools/link_check.py --refresh --current-ledger.")
        return 2
    if args.owner_gaps:
        return report_owner_gaps(args, found, sizes, index)
    if args.stale_views:
        views = stale_views(index)
        names = collections.Counter()
        listed = []
        for source, entries in views.items():
            picked = [e for e in entries if args.all_kinds or e["kind"] == "layout"]
            if picked:
                listed.append((source, picked))
                names.update(e["name"] for e in picked)
        listed.sort(key=lambda item: (-len(item[1]), -sizes[item[0]]))
        linked = {s for s, b in found.items() if not b}
        print(f"{len(listed):,} units hold {sum(len(p) for _, p in listed):,} "
              f"{'differing' if args.all_kinds else 'layout-like'} unreferenced copies "
              f"({sum(sizes[s] for s, _ in listed):,} matched bytes; diagnostic, not blockers)")
        for source, picked in listed[:args.top]:
            print(f"  {len(picked):4} {sizes[source]:8,} {'links' if source in linked else '     '}  {source}  "
                  f"[{'; '.join(e['name'][:60] for e in picked[:3])}{'; ...' if len(picked) > 3 else ''}]")
        print("\nnames:")
        for name, count in names.most_common(args.top):
            print(f"  {count:4} units  {name[:150]}")
        return 0
    if args.json:
        Path(args.json).write_text(json.dumps({s: sorted(b) for s, b in found.items()}), encoding="utf-8")
    if args.file:
        names = sorted(found.get(args.file, ()))
        print(f"{args.file}: {sizes[args.file]} matched bytes, "
              f"{'linked in census' if not names else f'{len(names)} blocker(s)'}")
        for kind, name in names:
            print(f"  {kind} {name}")
        for entry in stale_views(index).get(args.file, ()):
            import link_check
            print(f"  V {entry['name']}  ({link_check.describe_differ(entry)}; not a blocker)")
        import name_scoped
        handoff = name_scoped.related_work(args.file, "link")
        if handoff:
            print("\nName locals/parameters while inspecting this unit: " + handoff["command"])
            print(handoff["instructions"])
        return 0
    authored = {s: b for s, b in found.items() if not generated(s)}
    linked = [s for s, b in authored.items() if not b]
    print(f"{len(linked):,} of {len(authored):,} authored units linked in census "
          f"({sum(sizes[s] for s in linked):,} of {sum(sizes[s] for s in authored):,} matched bytes)")
    absent = sum(not generated(s) and s not in found for s in sizes)
    if absent:
        print(f"{absent:,} current matched unit(s) absent from the census; link state unknown.")

    def wanted(item):
        return args.kind is None or item[0] == args.kind

    sole, sole_units = collections.Counter(), collections.Counter()
    share, share_units = collections.Counter(), collections.Counter()
    for source, items in authored.items():
        if len(items) == 1:
            item = next(iter(items))
            sole[item] += sizes[source]
            sole_units[item] += 1
        for item in items:
            share[item] += sizes[source] / len(items)
            share_units[item] += 1

    def label(item):
        return f"{item[0]} {item[1] or '(source has a hard-coded image address)'}"

    print("\nsole blockers in census (recheck current providers before repair):")
    for item, value in [(i, v) for i, v in sole.most_common() if wanted(i)][:args.top]:
        print(f"  {value:8,} {sole_units[item]:4} units  {label(item)[:150]}")
    print(f"\nblocking names by shared bytes:")
    for item, value in [(i, v) for i, v in share.most_common() if wanted(i)][:args.top]:
        print(f"  {int(value):8,} {share_units[item]:4} units  {label(item)[:150]}")
    print(f"\nunits within {args.near} blocker(s) of linking:")
    near = sorted((s for s, b in authored.items() if 0 < len(b) <= args.near and all(wanted(i) for i in b)),
                  key=lambda s: -sizes[s])
    for source in near[:args.top]:
        names = "; ".join(label(i)[:70] for i in sorted(authored[source]))
        print(f"  {sizes[source]:7,}  {source}  [{names}]")
    return 0


if __name__ == "__main__":
    sys.exit(main())
