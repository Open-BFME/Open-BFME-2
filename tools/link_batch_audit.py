"""Check linking regressions once for an outgoing push, using verified objects.

Exit 1 for proven regressions, 2 for inconclusive evidence. A census index at
the pushed base supplies the before state; the byte gate supplies current objects.
"""

import argparse
import collections
import csv
import os
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

import build
import link_census
import link_cycle
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


def import_supplies(direct, plain, imported, defined):
    """Every symbol the import libraries exit_link.py generates would define. Its requests are the
    `__imp_` names kept objects leave undefined (`direct`: link_cycle.undefined_imports) and
    `__imp_` + each plain `_X@N` they leave undefined that retail imports outside msvcr71
    (`plain`, already `__imp_`-prefixed: undefined_plain_imports), of which only those nothing in
    the link defines; import_def_entries turns them into exports, and each export's import member
    defines `__imp_` + its symbol and, unless the tree defines the symbol (make_import_libs' DATA
    entry), the symbol's own thunk. `defined(name)` is the state's tree definitions."""
    requests = set(direct) | {request for request in plain if not defined(request[len("__imp_"):])}
    supplied = set()
    for entries in link_cycle.import_def_entries(requests, imported)[0].values():
        for entry in entries:
            symbol = entry if entry.startswith("?") else "_" + entry
            supplied.add("__imp_" + symbol)
            if not defined(symbol):
                supplied.add(symbol)
    return supplied


def requests_from_names(undefined, imported):
    """(direct, plain) import requests from one object's undefined external names, by the rules
    link_cycle.undefined_imports and undefined_plain_imports apply to a parsed object."""
    direct = {name for name in undefined if name.startswith("__imp_")}
    plain = set()
    for name in undefined:
        if name.startswith("_") and not name.startswith("__"):
            dlls = imported.get(re.sub(r"@\d+$", "", name[1:]))
            if dlls and "msvcr71.dll" not in dlls:
                plain.add("__imp_" + name)
    return direct, plain


def import_request_reader(paths, imported):
    """import_requests for real_link_losses: an object's (direct, plain) requests from
    link_cycle.undefined_imports and undefined_plain_imports over its file; None when it cannot be
    read. The plain requests still pass the whole link's `defined` filter in import_supplies."""
    cache = {}

    def import_requests(obj):
        if obj not in cache:
            try:
                objects = link_cycle.Objects([Path(paths[obj])])
                if objects.get(objects.paths[0]) is None:
                    raise FileNotFoundError(obj)
                cache[obj] = (link_cycle.undefined_imports(objects),
                              link_cycle.undefined_plain_imports(objects, imported))
            except Exception:  # noqa: BLE001 - unreadable: judged from the index's names instead
                cache[obj] = None
        return cache[obj]
    return import_requests


def unindexed_facts(found):
    """A reference_reader result as {defined, references, weaks, alternates, includes}; None stays
    None (unreadable), and a bare set is references only."""
    if found is None or isinstance(found, dict):
        return found
    return {"defined": set(), "references": set(found), "weaks": {}, "alternates": {}, "includes": set()}


def real_link_losses(index, updated, names, before_rank, after_rank, omitted=frozenset(),
                     weak_defaults=lambda obj: {}, bridged=None, includes=lambda obj: set(),
                     changed=frozenset(), referenced=None, references=lambda obj: None,
                     graph_trusted=True, bridge_copies=None, import_requests=None):
    """[(spelling, defined before by, still referenced by, kind)]: every name a kept real-link
    input references (symbol table or /INCLUDE) that resolved before this batch and resolves no
    more after it. Judged from object symbol tables and directives only: no census verdict, no
    symbols.csv pin (the real link reads none). `omitted` names the placement-only objects
    exit_link.py leaves out; they define, declare and reference nothing there.

    A name resolves when a real-link input defines it (strong, COMDAT or common), the real link's
    own libraries supply it (the runtime libraries, or a member of the import libraries it would
    generate for that state: import_supplies), or an input's /alternatename leads to a name that
    resolves (cycle-safe); a referrer whose own weak external for it has a default that resolves
    is satisfied. Spellings judged: `names` (what this batch's objects define or defined), every
    alias a changed or removed object declares or declared, and every alias a kept input declares
    whose chain leads to one of those.

    A kept object the index never read (a unit --update-index added) is read whole by
    `references(obj)` ({defined, references, weaks, alternates, includes}, None when unreadable)
    and stands in both states. Other referrers come from `touches`. /INCLUDE names
    (`includes(obj)`, None when unreadable) are roots of the census reference graph, so when
    `graph_trusted` (an index the census itself wrote, at the exact base) and `referenced` lacks
    the name, only changed and unindexed objects' directives are read; otherwise every kept
    object's are. `weak_defaults(obj)` is {name: default}, None when unreadable.

    kind: `loss` when some referrer is proven (readable, unsatisfied); `candidate` when the only
    referrers could not be read, or when the vtable bridge could still emit the name: `bridged`
    maps a ledger vtable name with one retail address to {rva, names, addresses}, and
    `bridge_copies(names, holders)` reads the after-state copies with vtable_bridge.definitions (None when
    unreadable); vtable_bridge.copy_refusal, the planner's own rules, decides the copies.

    Import requests come from the objects' own undefined externals: `import_requests(obj)` runs
    link_cycle's request helpers over a kept file ((direct, plain), None when unreadable); a
    changed or removed object's earlier file is gone, so the before-state reads it from the index
    (its names less its own definitions), as it does any unreadable object."""
    import vtable_bridge
    excuses = updated.get("excuses") or index.get("excuses") or {"runtime": set(), "imported": {}, "stubs": {}}
    runtime, imported = excuses["runtime"], excuses["imported"]
    touches = updated.get("touches", {})
    forgotten = updated.get("forgotten", set())
    real_before = {obj: i for obj, i in before_rank.items() if obj not in omitted}
    real_after = {obj: i for obj, i in after_rank.items() if obj not in omitted and obj not in forgotten}
    removed = set(real_before) - set(after_rank)
    moved = set(changed) | removed

    # Kept objects the index never read: unchanged by this batch, so in both states.
    unindexed = {obj for obj in real_after if obj not in touches}
    extra = {obj: unindexed_facts(references(obj)) for obj in sorted(unindexed)}
    readable = {obj: facts for obj, facts in extra.items() if facts is not None}
    extra_defined = set().union(*(facts["defined"] for facts in readable.values())) if readable else set()

    def alias_map(state, holders, only=None):
        found = collections.defaultdict(set)
        for alias, entries in state.get("alternates", {}).items():
            for i, target in entries:
                holder = state["objects"][i]
                if holder in holders and (only is None or holder in only):
                    found[alias].add(target)
        return found
    before_aliases, after_aliases = alias_map(index, real_before), alias_map(updated, real_after)
    for facts in readable.values():
        for alias, target in facts["alternates"].items():
            before_aliases[alias].add(target)
            after_aliases[alias].add(target)

    def referenced_by(state_touches, holders):
        found = set()
        for obj in holders:
            found |= state_touches.get(obj, set())
        for facts in readable.values():
            found |= facts["references"] | set(facts["weaks"]) | set(facts["weaks"].values())
        return found
    requested_after = referenced_by(touches, real_after)

    def own_definitions(state):
        """{object: names it defines in a section} from the state's strong and COMDAT tables. A
        COMMON record has section 0, which link_cycle.undefined_imports reads as a request, so it
        stays a possible request, as in the real helpers."""
        found = collections.defaultdict(set)
        for table in ("strong", "comdat"):
            for name, entries in state.get(table, {}).items():
                for entry in entries:
                    found[state["objects"][entry if table == "strong" else entry[0]]].add(name)
        return found

    def import_capable(name):
        return name.startswith("__imp_") or bool(requests_from_names({name}, imported)[1])

    def plan_requests(state, holders, state_touches, read_files):
        """(direct, plain) requests of a state's kept objects: link_cycle's helpers over each file
        `read_files` allows, else the index's names less the object's own definitions."""
        direct, plain = set(), set()
        defines = None
        for obj in sorted(holders):
            names = state_touches.get(obj)
            if names is None or not any(import_capable(name) for name in names):
                continue
            found = import_requests(obj) if import_requests is not None and obj in read_files else None
            if found is None:
                if defines is None:
                    defines = own_definitions(state)
                found = requests_from_names(names - defines.get(obj, set()), imported)
            direct |= found[0]
            plain |= found[1]
        for facts in readable.values():                    # unindexed units: their own undefined names
            found = requests_from_names(facts["references"], imported)
            direct |= found[0]
            plain |= found[1]
        return direct, plain

    def resolver(state, holders, aliases, state_touches, read_files):
        def defined(name):
            return bool(definers(state, name, holders)) or name in extra_defined

        def in_section(name):
            """link_cycle.defined_externals' rule (section > 0: strong or COMDAT, not COMMON), which
            the plain-request filter and make_import_libs' DATA entry read."""
            copies, strong = definitions(state, name, holders)
            return bool(copies) or bool(strong) or name in extra_defined
        supplied = None

        def imports():
            nonlocal supplied
            if supplied is None:                           # built only when a name needs it
                supplied = import_supplies(*plan_requests(state, holders, state_touches, read_files),
                                           imported, in_section)
            return supplied

        def resolves(name, seen=frozenset()):
            if name in seen:
                return False                               # an alias cycle resolves nothing
            if defined(name) or name in runtime or name in imports():
                return True
            return any(resolves(target, seen | {name}) for target in aliases.get(name, ()))
        return resolves
    # A kept file is the object of both states unless this batch changed or removed it.
    was = resolver(index, real_before, before_aliases, index.get("touches", {}), set(real_before) - moved)
    now = resolver(updated, real_after, after_aliases, touches, set(real_after))

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

    known = {obj: (touches[obj] if obj in touches else
                   (None if extra[obj] is None else
                    extra[obj]["references"] | set(extra[obj]["weaks"]) | set(extra[obj]["weaks"].values())))
             for obj in real_after}

    def weaks_of(obj):
        return readable[obj]["weaks"] if obj in readable else weak_defaults(obj)

    def includes_of(obj):
        if obj in readable:                                # the whole-object read, and the directive reader
            return readable[obj]["includes"] | (includes(obj) or set())
        return None if obj in extra else includes(obj)

    def bridgeable(name):
        """The planner's copy rules (vtable_bridge.copy_refusal) admit a generated copy of `name`
        beside its address's other names; slot targets are not judged here, so a pass is only a
        candidate."""
        info = bridged.get(name) if isinstance(bridged, dict) else None
        if not isinstance(info, dict) or bridge_copies is None:
            return False                                   # nothing shows the bridge could emit it
        at = set(info["names"])
        holders = {obj for other in at for obj in definers(updated, other, real_after)}
        holders |= {obj for obj, facts in readable.items() if at & facts["defined"]}
        found = bridge_copies(at, holders)
        if found is None:
            return True                                    # unreadable copies: the bridge might
        remaining = at - set(vtable_bridge.strong_names(found, at))
        copies = [(other, copy) for other in sorted(remaining) for copy in found.get(other, [])]
        kept = [(other, copy) for other, copy in copies if not copy.get("archive")
                and not copy.get("common") and not copy.get("absolute")]
        active = {other for other, _copy in kept} | (remaining & (requested_after | {name}))
        refusal, _providers = vtable_bridge.copy_refusal(copies, kept, remaining, active,
                                                         info["addresses"], info["rva"])
        return refusal is None

    losses = []
    for name in sorted(spellings):
        if not was(name) or now(name):
            continue
        proven, uncertain = set(), set()

        def judge(obj):
            weaks = weaks_of(obj)
            if weaks is None:
                uncertain.add(obj)
            elif not (name in weaks and now(weaks[name], frozenset({name}))):
                proven.add(obj)                            # no default that resolves

        for obj in sorted(obj for obj, found in known.items() if found is not None and name in found):
            judge(obj)
        unread = False                                     # an unreadable unindexed unit shows in the scan
        if not proven:                                     # look for a directive proof before settling for doubt
            shortcut = graph_trusted and referenced is not None and name not in referenced
            scan = (moved | unindexed) & set(real_after) if shortcut else set(real_after)
            for obj in sorted(scan):
                forced = includes_of(obj)
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
    """references for real_link_losses: a kept object the index never read, whole, through the
    census's own reader (link_census.object_symbols): {defined, references, weaks, alternates,
    includes}; None when unreadable."""
    cache = {}

    def references(obj):
        if obj not in cache:
            try:
                defined, found, weaks, alternates, forced = link_census.object_symbols(Path(paths[obj]))
                cache[obj] = {"defined": set(defined), "references": set(found), "weaks": dict(weaks),
                              "alternates": dict(alternates), "includes": set(forced)}
            except Exception:  # noqa: BLE001 - unreadable: a finding without referrers is a candidate
                cache[obj] = None
        return cache[obj]
    return references


def bridge_copy_reader(paths):
    """bridge_copies for real_link_losses: vtable_bridge.definitions of `names` over `holders`,
    the after-state objects defining any of them; None when one cannot be read."""
    def bridge_copies(names, holders):
        import vtable_bridge
        try:
            objects = link_cycle.Objects([Path(paths[obj]) for obj in sorted(holders)])
            return vtable_bridge.definitions(objects, set(names))
        except Exception:  # noqa: BLE001 - unreadable copies: the bridge might still emit the name
            return None
    return bridge_copies


INCLUDE = link_census.DIRECTIVE_INCLUDE


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
    """{name: {rva, names, addresses}} for each data-ledger vtable name with one retail address:
    the only names exit_link.py's vtable bridge may emit (it refuses a name bound at two,
    ambiguous-table-name). `names` are the names at that address and `addresses` each one's
    addresses, what vtable_bridge.copy_refusal reads. The initializer bridge defines no name a
    kept object can reference."""
    import vtable_bridge
    at, where = collections.defaultdict(set), collections.defaultdict(set)
    for row in vtable_bridge.table_rows(build.ROOT):
        rva = int(row["address"], 16)
        for name in vtable_bridge.row_names(row):
            at[rva].add(name)
            where[name].add(rva)
    found = {}
    for name, addresses in where.items():
        if len(addresses) == 1:
            rva = next(iter(addresses))
            found[name] = {"rva": rva, "names": at[rva], "addresses": {other: where[other] for other in at[rva]}}
    return found


# What this run established, for its log line: exact_base stays None when it returned before comparing the index with
# the base, and judged stays False unless it read the batch's objects through to a verdict.
EVIDENCE = {"exact_base": None, "judged": False}


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
        verdict = "refuse mode: candidates only, unverified"
    print(f"link batch audit: {len(certain)} name(s) the real link would no longer resolve, "
          f"{len(losses) - len(certain)} candidate(s) ({verdict}); "
          "define each in its owner's unit or point the reference at the owner's real symbol")
    if refuses:
        return 1
    # Refuse mode: unproven evidence is inconclusive, never clean (report mode keeps its exit).
    return 2 if REAL_LINK_LOSS_MODE == "refuse" else None


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
    EVIDENCE["exact_base"] = exact_base
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
        EVIDENCE["judged"] = True
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
                                       reference_reader(paths := object_paths(index, replacements, sources)),
                                       graph_trusted, bridge_copy_reader(paths),
                                       import_request_reader(paths, (index.get("excuses") or {}).get("imported", {})))
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
    EVIDENCE["judged"] = True
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
        real_exit = report_real_link_losses(real_losses, exact_base)
        if real_exit:
            return real_exit
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
    elif real_losses:
        print("link batch audit: no census linking regression found; the real-link findings above are reported only")
    else:
        print("link batch audit: no linking regression found in the checked scope")
    return 0 if exact_base else 2


# One JSON line per run, appended to <git common dir>/link_audit_verdicts.jsonl (as class_gate's
# shadow log): the before/after measurement for strict receipts (docs/strict_receipts_design.md,
# step 0). It never changes what the audit prints or returns. A run the hook's time cap kills
# writes no line; one that crashes is logged as "crashed" and still crashes (its traceback gains
# the run() frame, which is harmless: only stdout and the exit code reach the hook's verdict).
VERDICT_LOG = "link_audit_verdicts.jsonl"
VERDICT_REASONS = (("census index missing", "no-index"), ("lack current receipts", "missing-receipts"),
                   ("consumer lacks current receipt", "consumer-receipt"),
                   ("no provisional finding from the older index", "non-exact-base"))


class _Tee:
    """sys.stdout, also keeping the audit's own summary lines."""
    def __init__(self, stream):
        self.stream, self.lines, self._partial = stream, [], ""

    def write(self, text):
        self._partial += text
        *done, self._partial = self._partial.split("\n")
        self.lines += [line for line in done if line.startswith("link batch audit:")]
        return self.stream.write(text)

    def __getattr__(self, name):
        return getattr(self.stream, name)


def verdict_record(code, lines, base, tip, sources):
    """The log line for one run: its exit's verdict and, for an inconclusive one, why."""
    verdict = {0: "clean", 1: "failed", 2: "inconclusive", "crashed": "crashed"}.get(code, f"exit-{code}")
    reason = None
    if verdict == "inconclusive":
        text = " ".join(lines)
        reason = next((name for marker, name in VERDICT_REASONS if marker in text), "other")
    return {"utc": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "base": base, "tip": tip,
            "verdict": verdict, "reason": reason, "exit": code, "sources": sources,
            "exact_base": EVIDENCE["exact_base"], "judged": EVIDENCE["judged"],
            "real_link_findings": any("real link would no longer resolve" in line for line in lines),
            "lines": [line[:300] for line in lines[:12]]}


def log_verdict(record):
    """Append one verdict line. Never raises: a failing git, path or write loses the line, not the push.

    Seats and worktrees share one common dir, so pushes append at once. Windows' O_APPEND is
    not atomic across processes (16 writers corrupted 274 of 4,800 lines in review), so the
    whole line is built first and written by os.write on an O_APPEND binary descriptor while a
    portable_lock is held on the sibling .lock file."""
    import json
    from portable_lock import lock, unlock
    try:
        result = subprocess.run(["git", "rev-parse", "--git-common-dir"], cwd=link_check.ROOT,
                                capture_output=True, text=True)
        if result.returncode != 0:
            return
        common = Path(result.stdout.strip())
        common = common if common.is_absolute() else link_check.ROOT / common
        line = memoryview((json.dumps(record, sort_keys=True) + "\n").encode("utf-8"))
        with open(common / (VERDICT_LOG + ".lock"), "a+b") as guard:
            lock(guard, exclusive=True)
            try:
                fd = os.open(common / VERDICT_LOG, os.O_WRONLY | os.O_APPEND | os.O_CREAT
                             | getattr(os, "O_BINARY", 0), 0o666)
                try:
                    while line:
                        line = line[os.write(fd, line):]
                finally:
                    os.close(fd)
            finally:
                unlock(guard)
    except Exception:  # noqa: BLE001 - a log line must not change the audit
        pass


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True)
    parser.add_argument("--tip", required=True)
    parser.add_argument("--sources-from", metavar="FILE", required=True,
                        help="NUL-delimited byte-verified source paths")
    args = parser.parse_args()
    sources = None
    try:
        sources = len([part for part in Path(args.sources_from).read_bytes().split(b"\0") if part])
    except OSError:
        pass
    EVIDENCE.update(exact_base=None, judged=False)
    tee = _Tee(sys.stdout)
    sys.stdout = tee
    try:
        code = run(args)
    except BaseException:
        sys.stdout = tee.stream
        log_verdict(verdict_record("crashed", tee.lines, args.base, args.tip, sources))
        raise
    sys.stdout = tee.stream
    log_verdict(verdict_record(code, tee.lines, args.base, args.tip, sources))
    return code


def run(args):
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
