"""Check linking regressions once for an outgoing push, using verified objects.

Exit 1 for proven regressions, 2 for inconclusive evidence. A census index at
the pushed base supplies the before state; the byte gate supplies current objects.
"""

import argparse
import collections
import csv
import re
import struct
import subprocess
import sys
from pathlib import Path

import build
import link_census
import link_check
import exit_link


# A batch that leaves a referenced name with no definition anywhere costs the real link one
# resolved name, whatever the census thought of the copy it removed (LINK-626: four pushes
# removed wrong-but-present destructor bodies from a unit the census marked unlinked, and the
# real link lost 13 names). `report` prints these; `refuse` fails the push. One-way: report first.
REAL_LINK_LOSS_MODE = "report"


def git(*args):
    return subprocess.run(("git", *args), cwd=link_check.ROOT, check=True,
                          capture_output=True, text=True).stdout.strip()


def changed_sources(base, tip):
    names = git("diff", "--name-only", base, tip, "--", "Code").splitlines()
    return {name for name in names if Path(name).suffix.lower() in (".cpp", ".c", ".asm")}


def changed_identities(base, tip):
    """Names whose address/owner may change, including ledger-only edits."""
    diff = git("diff", "--no-ext-diff", "--unified=0", base, tip, "--",
               "reverse/functions.csv", "reverse/symbols.csv",
               "reverse/data_rows.csv", "reverse/dir32_addresses.csv")
    names = set()
    for line in diff.splitlines():
        if line[:1] in ("+", "-") and not line.startswith(("+++", "---")):
            row = next(csv.reader([line[1:]]), [])
            if row and row[0] != "name":
                names.add(row[0])
            for field in row:
                for token in field.split(";"):
                    if token.strip().startswith("object-symbol="):
                        names.add(token.strip().split("=", 1)[1])
    return names


def affected_sources(index, names):
    """Definition owners and direct consumers, including unchanged sources."""
    touches = index.get("touches")
    if touches is None or any(obj not in touches for obj in index["objects"]
                              if obj not in index.get("forgotten", ())):
        raise ValueError("census index lacks per-object consumer names; fetch a current index")
    return {source for source, entry in index["blockers"].items()
            if names.intersection(touches.get(entry.get("object"), ()))}


def definitions(index, name, rank):
    """Link-order definitions of one name, with census retail verdicts."""
    objects = index["objects"]
    copies = {objects[i]: (digest, verdict) for i, digest, verdict in index["comdat"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    strong = {objects[i] for i in index["strong"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    return copies, strong


def selected(index, name, rank):
    copies, strong = definitions(index, name, rank)
    definers = set(copies) | strong
    if not definers:
        return None, None
    holder = min(definers, key=rank.__getitem__)
    exceptions = index["selection"]["exceptions"]
    if name in exceptions:
        position = exceptions[name]
        exception = index["objects"][position] if position is not None else None
        holder = exception if exception is None or exception in definers else holder
    verdict = link_census.judge_selected(holder, copies, definers, strong,
                                         index["selection"]["owners"].get(name, set()))
    return holder, verdict


def definers(index, name, rank):
    """Objects in `rank` that define `name` at all (strong, COMDAT or common), whatever the
    census's verdict on the copy."""
    copies, strong = definitions(index, name, rank)
    common = {index["objects"][i] for i, _ in index["common"].get(name, ())
              if index["objects"][i] in rank and index["objects"][i] not in index.get("forgotten", ())}
    return set(copies) | strong | common


def real_link_losses(index, updated, names, before_rank, after_rank, omitted=frozenset(),
                     weak_defaults=lambda obj: {}, bridged=None, includes=lambda obj: set(),
                     changed=frozenset(), referenced=None, references=lambda obj: None,
                     graph_trusted=True):
    """[(spelling, defined before by, still referenced by, kind)]: every name a kept real-link
    input references (symbol table or /INCLUDE) that resolved before this batch and resolves no
    more after it. Judged from object symbol tables and directives only: no census verdict, no
    symbols.csv pin (the real link reads none). `omitted` names the placement-only objects
    exit_link.py leaves out; they define, declare and reference nothing there.

    A name resolves when a real-link input defines it (strong, COMDAT or common), the toolchain
    supplies it (runtime, import, stub), or an input's /alternatename leads to a name that
    resolves (cycle-safe); a referrer whose own weak external for it has a default that resolves
    is satisfied. Spellings judged: `names` (what this batch's objects define or defined), every
    alias a changed or removed object declares or declared, and every alias a kept input declares
    whose chain leads to one of those.

    Referrers: `touches`, or `references(obj)` for a kept object the index never read (a set,
    None when unreadable). /INCLUDE names (`includes(obj)`, None when unreadable) are roots of the
    census reference graph, so when `graph_trusted` (an index the census itself wrote, at the
    exact base) and `referenced` lacks the name, only changed and unindexed objects' directives
    are read; otherwise every kept object's are. `weak_defaults(obj)` is {name: default}, None
    when unreadable.

    kind: `loss` when some referrer is proven (readable, unsatisfied); `candidate` when the only
    referrers could not be read, or when the vtable bridge could still emit the name: `bridged`
    maps a ledger vtable name with one retail address to the names at that address, and the
    bridge emits a referenced name there only beside another name's kept COMDAT copy."""
    excuses = updated.get("excuses") or index.get("excuses") or {"runtime": set(), "imported": {}, "stubs": {}}
    touches = updated.get("touches", {})
    forgotten = updated.get("forgotten", set())
    real_before = {obj: i for obj, i in before_rank.items() if obj not in omitted}
    real_after = {obj: i for obj, i in after_rank.items() if obj not in omitted and obj not in forgotten}
    removed = set(real_before) - set(after_rank)
    moved = set(changed) | removed

    def alias_map(state, holders, only=None):
        found = collections.defaultdict(set)
        for alias, entries in state.get("alternates", {}).items():
            for i, target in entries:
                holder = state["objects"][i]
                if holder in holders and (only is None or holder in only):
                    found[alias].add(target)
        return found
    before_aliases, after_aliases = alias_map(index, real_before), alias_map(updated, real_after)

    def resolver(state, holders, aliases):
        def resolves(name, seen=frozenset()):
            if name in seen:
                return False                               # an alias cycle resolves nothing
            if definers(state, name, holders):
                return True
            if link_census.excused(name, excuses["runtime"], excuses["imported"], excuses["stubs"]):
                return True
            return any(resolves(target, seen | {name}) for target in aliases.get(name, ()))
        return resolves
    was = resolver(index, real_before, before_aliases)
    now = resolver(updated, real_after, after_aliases)

    spellings = set(names) | set(alias_map(index, real_before, moved)) | set(alias_map(updated, real_after, moved))
    # target -> aliases after the batch. An alias only the before-state holds belongs to a removed
    # or changed object, already a spelling above.
    leading = collections.defaultdict(set)
    for alias, targets in after_aliases.items():
        for target in targets:
            leading[target].add(alias)
    stack = list(spellings)
    while stack:
        for alias in leading.get(stack.pop(), ()):
            if alias not in spellings:
                spellings.add(alias)
                stack.append(alias)

    unindexed = {obj for obj in real_after if obj not in touches}
    known = {obj: (touches[obj] if obj in touches else references(obj)) for obj in real_after}
    unknown_references = any(found is None for found in known.values())

    def bridgeable(name):
        neighbours = bridged.get(name, ()) if isinstance(bridged, dict) else ()  # names alone prove nothing
        return any(other != name and definitions(updated, other, real_after)[0] for other in neighbours)

    losses = []
    for name in sorted(spellings):
        if not was(name) or now(name):
            continue
        proven, uncertain = set(), set()

        def judge(obj):
            weaks = weak_defaults(obj)
            if weaks is None:
                uncertain.add(obj)
            elif not (name in weaks and now(weaks[name], frozenset({name}))):
                proven.add(obj)                            # no default that resolves

        for obj in sorted(obj for obj, found in known.items() if found is not None and name in found):
            judge(obj)
        unread = unknown_references
        if not proven:                                     # look for a directive proof before settling for doubt
            shortcut = graph_trusted and referenced is not None and name not in referenced
            scan = (moved | unindexed) & set(real_after) if shortcut else set(real_after)
            for obj in sorted(scan):
                forced = includes(obj)
                if forced is None:
                    unread = True
                elif name in forced:
                    judge(obj)
        before = sorted(definers(index, name, real_before)) or ["/alternatename"]
        if proven:
            kind = "candidate" if bridgeable(name) else "loss"
            losses.append((name, before, sorted(proven | uncertain), kind))
        elif uncertain:
            losses.append((name, before, sorted(uncertain), "candidate"))
        elif unread:
            losses.append((name, before, ["(an unread object)"], "candidate"))
    return losses


def object_paths(index, replacements, sources=()):
    """{object name: path}: a replaced object's current file, any other the object its census
    source names, or its ledger source does (a unit the index never read)."""
    paths = {obj.name: obj for obj in replacements}
    for source, entry in index.get("blockers", {}).items():
        if entry.get("object") and entry["object"] not in paths:
            paths[entry["object"]] = build.obj_path(link_check.ROOT / source)
    for source in sorted(sources):
        path = build.obj_path(link_check.ROOT / source)
        paths.setdefault(path.name, path)
    return paths


def reference_reader(paths):
    """references for real_link_losses: an object's undefined externals, weak externals and their
    defaults; None when unreadable."""
    cache = {}

    def references(obj):
        if obj not in cache:
            try:
                _defined, found, weaks, _alternates, _includes = link_census.object_symbols(Path(paths[obj]))
                cache[obj] = set(found) | {name for pair in weaks for name in pair}
            except Exception:  # noqa: BLE001 - unreadable: a finding without referrers is a candidate
                cache[obj] = None
        return cache[obj]
    return references


INCLUDE = re.compile(r"/INCLUDE:(\"[^\"]+\"|[^\s,=]+)", re.I)


def directive_includes(data):
    """The /INCLUDE: names in an object's .drectve sections (link_census.object_symbols' reader)."""
    found = set()
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    for number in range(count):
        header = 20 + optional + number * 40
        if data[header:header + 8].rstrip(b"\0") == b".drectve":
            size, pointer = struct.unpack_from("<II", data, header + 16)
            found.update(name.strip('"') for name in INCLUDE.findall(data[pointer:pointer + size].decode("latin-1")))
    return found


def include_reader(index, replacements, sources=()):
    """includes for real_link_losses: an object's /INCLUDE names, None when unreadable."""
    paths = object_paths(index, replacements, sources)
    cache = {}

    def includes(obj):
        if obj not in cache:
            try:
                cache[obj] = directive_includes(Path(paths[obj]).read_bytes())
            except Exception:  # noqa: BLE001 - unreadable: a finding without referrers is a candidate
                cache[obj] = None
        return cache[obj]
    return includes


def weak_reader(index, replacements, sources=()):
    """weak_defaults for real_link_losses: an object's weak externals; None when unreadable."""
    paths = object_paths(index, replacements, sources)
    cache = {}

    def weak_defaults(obj):
        if obj not in cache:
            try:
                cache[obj] = dict(link_census._weak_externals(Path(paths[obj]).read_bytes()))
            except Exception:  # noqa: BLE001 - unreadable: the finding becomes a candidate
                cache[obj] = None
        return cache[obj]
    return weak_defaults


def bridged_names():
    """{name: names at its retail address} for each data-ledger vtable name with one address: the
    only names exit_link.py's vtable bridge may emit. It never invents a table, so it emits a
    referenced name only beside another name's kept COMDAT copy (else no-kept-definition), and
    refuses a name bound at two addresses (ambiguous-table-name). The initializer bridge defines
    no name a kept object can reference."""
    import vtable_bridge
    at, where = collections.defaultdict(set), collections.defaultdict(set)
    for row in vtable_bridge.table_rows(build.ROOT):
        for name in vtable_bridge.row_names(row):
            at[row["address"]].add(name)
            where[name].add(row["address"])
    return {name: at[next(iter(addresses))] for name, addresses in where.items() if len(addresses) == 1}


def report_real_link_losses(losses, exact_base):
    """Print the real-link findings; (exit code or None). Only a `loss` on an exact base refuses,
    and only in refuse mode."""
    certain = [entry for entry in losses if entry[3] == "loss"]
    for name, before, referrers, kind in losses:
        label = "REAL-LINK LOSS" if kind == "loss" else "REAL-LINK LOSS CANDIDATE"
        how = "through /alternatename" if before == ["/alternatename"] else f"by {', '.join(before)}"
        print(f"  {label} {name}: defined before this batch {how}, by no kept object "
              f"after; still referenced by {', '.join(referrers[:3])}"
              f"{f' (+{len(referrers) - 3})' if len(referrers) > 3 else ''}"
              f"{'; the vtable bridge or an unread object may still resolve or reference it' if kind != 'loss' else ''}")
    if not losses:
        return None
    refuses = REAL_LINK_LOSS_MODE == "refuse" and exact_base and bool(certain)
    if REAL_LINK_LOSS_MODE != "refuse":
        verdict = "report mode: not refused"
    elif refuses:
        verdict = "refuse mode: refused"
    elif not exact_base:
        verdict = "refuse mode: provisional baseline, not refused"
    else:
        verdict = "refuse mode: candidates only, not refused"
    print(f"link batch audit: {len(certain)} name(s) the real link would no longer resolve, "
          f"{len(losses) - len(certain)} candidate(s) ({verdict}); "
          "define each in its owner's unit or point the reference at the owner's real symbol")
    return 1 if refuses else None


def overlay(index, replacements, removed, truth):
    """Copy table containers, preserving the saved index for before comparisons."""
    updated = dict(index)
    for key in ("strong", "comdat", "common", "alternates", "blockers", "digests"):
        updated[key] = dict(index[key])
    if "touches" in index:
        updated["touches"] = dict(index["touches"])
    updated["objects"] = list(index["objects"])
    updated["forgotten"] = set(index.get("forgotten", ()))
    if "references" in index:
        graph = index["references"]
        updated["references"] = {**graph, "edges": dict(graph["edges"]),
                                 "referenced": set(graph["referenced"])}
    link_check.forget(updated, removed)
    for obj in replacements:
        if obj.name not in updated["objects"]:
            updated["objects"].append(obj.name)
        updated["forgotten"].discard(obj.name)
    link_check.refresh(updated, replacements, truth)
    return updated


def reorder(index, rank):
    """check_object compares numeric positions; use the new link order."""
    old = index["objects"]
    positions = sorted((i for i, obj in enumerate(old) if obj in rank), key=lambda i: rank[old[i]])
    moved = {old_i: new_i for new_i, old_i in enumerate(positions)}
    for table in ("comdat", "common", "alternates"):
        index[table] = {name: sorted((moved[i], *rest) for i, *rest in entries if i in moved)
                        for name, entries in index[table].items()}
    index["strong"] = {name: sorted(moved[i] for i in entries if i in moved)
                       for name, entries in index["strong"].items()}
    index["selection"] = {**index["selection"], "exceptions": {
        name: moved[i] if i is not None else None
        for name, i in index["selection"]["exceptions"].items() if i is None or i in moved}}
    index["objects"] = [old[i] for i in positions]


def omitted_references(rows, objects):
    """[(object name, symbol)] the objects reference that the real link's omitted objects define.
    exit_link.py's omission proof refuses to link while any kept object does this."""
    omitted = set(exit_link.placement_objects(rows))
    names = {build.ledger_object_symbol(row) for row in exit_link.placement_rows(rows)}
    for path in omitted:
        if path.is_file():
            names |= exit_link.external_definitions(exit_link.coff_view(path)[1])
    if not names:
        return []
    found = []
    for path in objects:
        if path not in omitted:
            found.extend((path.name, name) for name in sorted(exit_link.coff_references(path, exit_link.coff_view(path)[2]) & names))
    return found


def audit(base, tip, verified):
    changes = changed_sources(base, tip)
    identities = changed_identities(base, tip)
    if not changes and not verified and not identities:
        print("link batch audit: no changed source objects")
        return 0
    if git("diff", "--name-only", tip, "--", *link_census.CENSUS_INPUTS):
        raise ValueError("working-tree compiler/identity inputs differ from the pushed commit")
    if not link_check.INDEX.exists():
        print("link batch audit: INCONCLUSIVE: census index missing; fetch with link_check.py --fetch-index")
        return 2
    index = link_check.load_index()
    meta = index.get("meta", {})
    # Census publication changes status/history, not compiler inputs. Accept
    # those commits without requiring a new census of its own publication.
    exact_base = bool(meta.get("commit") and meta.get("clean_tree", True) and not git(
        "diff", "--name-only", meta["commit"], base, "--", *link_census.CENSUS_INPUTS,
        *("tools/" + name for name in link_census.TOOL_FILES)))
    if not exact_base:
        print(f"link batch audit: INCONCLUSIVE baseline: index at {meta.get('commit', '?')}, "
              f"outgoing base {base}; findings below are provisional since-index changes")
    try:
        link_check.require_common_index(index)
    except SystemExit as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
        return 2
    rows = link_census.ledger()
    truth = link_census.RetailTruth(rows)
    sources = {row["source"] for row in rows} | {row["source"] for row in link_census.data_ledger()}
    scope = (changes | set(verified)) & sources
    # Rejudge unchanged copies when a ledger/pin changes their own or a
    # relocation's identity. Their cached census verdict is no longer current.
    if identities:
        scope |= affected_sources(index, identities) & sources
    old_by_source = {source: entry["object"] for source, entry in index["blockers"].items()
                     if "object" in entry}
    removed = {old_by_source[source] for source in changes if source in old_by_source and source not in sources}
    replacements = []
    missing = []
    for source in sorted(scope):
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or not link_census.object_current(link_check.ROOT / source, obj):
            missing.append(source)
        else:
            replacements.append(obj)
    # Before the receipt check, which a byte-verified object can still fail. Only objects known to be
    # current: scope also holds consumers of a changed identity, whose object here may predate a fix.
    built = {build.obj_path(link_check.ROOT / source) for source in sorted(scope & set(verified))} | set(replacements)
    refused = omitted_references(rows, sorted(obj for obj in built if obj.is_file()))
    if refused:
        for obj, name in refused[:20]:
            print(f"  OMITTED {obj} references {name}, defined in a placement object the real link leaves out")
        print(f"link batch audit: FAILED: {len(refused)} reference(s) to omitted objects; "
              "exit_link.py would refuse to link. Reach the row the omitted thunk jumps to instead")
        return 1
    if missing:
        print(f"link batch audit: INCONCLUSIVE: {len(missing)} source object(s) lack current receipts; "
              f"first: {missing[0]}")
        return 2
    # A changed ledger may remove an object without deleting its source path.
    current_objects = {build.obj_path(link_check.ROOT / source).name for source in sources}
    removed |= {obj for source, obj in old_by_source.items() if source not in sources and obj not in current_objects}
    before_rank = {name: i for i, name in enumerate(index["objects"])
                   if name not in index.get("forgotten", ())}
    after_rank = link_check.link_rank(rows)
    updated = overlay(index, replacements, removed, truth)
    updated["selection"] = {**index["selection"], "owners": dict(link_census.ledger_owners(rows))}
    touched = set()
    changed_objects = removed | {obj.name for obj in replacements}
    for name, entries in index["comdat"].items():
        if any(index["objects"][i] in changed_objects for i, _, _ in entries):
            touched.add(name)
    for name, entries in index["strong"].items():
        if any(index["objects"][i] in changed_objects for i in entries):
            touched.add(name)
    for name, entries in index["common"].items():
        if any(index["objects"][i] in changed_objects for i, _ in entries):
            touched.add(name)
    for obj in replacements:
        copies, strong, _, _ = link_census.object_facts(obj, truth)
        touched.update(name for name, _, _, _ in copies)
        touched.update(strong)
        touched.update(link_census.common_definitions(obj))
    # A provider edit can break a caller whose source did not change. Read
    # those current objects too; never treat missing/stale consumers as clean.
    consumers = (affected_sources(index, touched) & sources) - scope if touched else set()
    for source in sorted(consumers):
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or not link_census.object_current(link_check.ROOT / source, obj):
            print(f"link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: {source}")
            return 2
    findings = []
    for name in sorted(touched):
        old_holder, old_verdict = selected(index, name, before_rank)
        new_holder, new_verdict = selected(updated, name, after_rank)
        if old_holder and old_verdict != "wrong" and new_verdict == "wrong":
            findings.append((name, old_holder, new_holder, "wrong selected provider"))
        elif old_holder and not new_holder and old_verdict != "wrong":
            findings.append((name, old_holder, None, "provider disappeared"))
    # Report mode must never block a push: any failure here prints and leaves the exit alone.
    try:
        # The reference graph is the census's own only when no --update-index moved the index
        # past it: that adds and rereads units without regrowing the graph.
        graph_trusted = exact_base and meta.get("census_commit", meta.get("commit")) == meta.get("commit")
        real_losses = real_link_losses(index, updated, touched, before_rank, after_rank,
                                       {path.name for path in exit_link.placement_objects(rows)},
                                       weak_reader(index, replacements, sources), bridged_names(),
                                       include_reader(index, replacements, sources),
                                       {obj.name for obj in replacements},
                                       (index.get("references") or {}).get("referenced"),
                                       reference_reader(object_paths(index, replacements, sources)),
                                       graph_trusted)
        real_error = None
    except Exception as error:  # noqa: BLE001
        real_losses, real_error = [], error
    reorder(updated, after_rank)
    # A new destination must preserve the linked donors it absorbed too.
    retired_clean = {entry["object"]: source for source, entry in index["blockers"].items()
                     if source not in sources and entry.get("linked")}
    inherited = collections.defaultdict(set)
    if retired_clean:
        for row in rows:
            for owner in index["selection"]["owners"].get(row.get("name"), ()):
                if owner in retired_clean:
                    inherited[row["source"]].add(retired_clean[owner])
    lost = collections.Counter()
    for source in sorted(scope | consumers):
        prior = index["blockers"].get(source, {})
        if not prior.get("linked") and not inherited[source]:
            continue
        credited = inherited[source] | ({source} if prior.get("linked") else set())
        obj = build.obj_path(link_check.ROOT / source)
        result = link_check.check_object(obj, updated, truth, source)
        for kind in ("unresolved", "duplicates", "comdat", "selected", "addresses"):
            for entry in result.get(kind, ()):
                name = entry[0] if isinstance(entry, (tuple, list)) else entry
                before, _ = selected(index, name, before_rank)
                after, _ = selected(updated, name, after_rank)
                lost[(name, before, after, kind + " in " + source)] += sum(
                    index["bytes"].get(s, 0) for s in credited)
    print(f"link batch audit: {len(replacements)} current object(s), {len(removed)} retired; "
          f"index {meta.get('date', '?')} at {base}")
    for name, before, after, reason in findings:
        print(f"  REVIEW {reason}: {name}; selected {before or '(none)'} -> {after or '(none)'}; "
              "affected consumer bytes require census confirmation")
    for (name, before, after, reason), byte_count in sorted(lost.items()):
        label = "LOST" if exact_base else "POSSIBLE LOSS"
        print(f"  {label} {byte_count:,} previously linked source bytes: {reason}: {name}; "
              f"provider {before or '(none)'} -> {after or '(none)'}")
    try:
        if real_error is not None:
            raise real_error
        if report_real_link_losses(real_losses, exact_base):
            return 1
    except Exception as error:  # noqa: BLE001 - see above
        print(f"link batch audit: real-link loss check failed: {type(error).__name__}: {error} "
              f"({REAL_LINK_LOSS_MODE} mode: unverified)")
        if REAL_LINK_LOSS_MODE == "refuse" and exact_base:
            return 2
    if lost:
        print("link batch audit: " + ("FAILED" if exact_base else "INCONCLUSIVE") +
              "; verify affected consumers and record repairs")
        return 1 if exact_base else 2
    elif not exact_base:
        print("link batch audit: INCONCLUSIVE: no provisional finding from the older index")
    else:
        print("link batch audit: no linking regression found in the checked scope")
    return 0 if exact_base else 2


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True)
    parser.add_argument("--tip", required=True)
    parser.add_argument("--sources-from", metavar="FILE", required=True,
                        help="NUL-delimited byte-verified source paths")
    args = parser.parse_args()
    try:
        raw = Path(args.sources_from).read_bytes()
        if raw and not raw.endswith(b"\0"):
            raise ValueError("unterminated verified source list")
        verified = [part.decode("utf-8") for part in raw.split(b"\0") if part]
        return audit(args.base, args.tip, verified)
    except (OSError, ValueError, KeyError, csv.Error, SystemExit, subprocess.CalledProcessError,
            link_census.MissingObject) as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
    return 2


if __name__ == "__main__":
    sys.exit(main())
