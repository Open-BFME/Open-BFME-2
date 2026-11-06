"""Counted, temporary vtable copies generated only by exit_link.py.

This bridges positive virtual slots, not class recovery or RTTI. It never invents
a missing vtable definition or a target name and never changes the code ledger.
"""
import collections
import csv
import json
import struct
from pathlib import Path

import build
import coffar
import link_cycle

COMDAT, EXECUTE, SELECT_ANY = 0x1000, 0x20000000, 2
ASSOCIATIVE, DISCARDABLE = 5, 0x02000000
WEAK_EXTERNAL = 105  # IMAGE_SYM_CLASS_WEAK_EXTERNAL
RDATA = 0x40301040


def row_names(row):
    return {row["name"], *(row.get("names") or "").split(";")} - {""}


def table_rows(root):
    with (Path(root) / "reverse/data_ledger.csv").open(newline="", encoding="utf-8") as handle:
        return [row for row in csv.DictReader(handle) if row["kind"] == "vtable"]


def definitions(objects, names, archives=()):
    """Inspect every supplied definition, including possible strong archive providers."""
    found = collections.defaultdict(list)
    for path in objects.paths:
        obj = objects.get(path)
        if obj is None:
            raise ValueError(f"vtable bridge cannot inspect missing input {path}")
        sections, symbols, raw = obj
        starts = collections.defaultdict(set)
        publics = collections.defaultdict(set)
        for sym in symbols.values():
            if sym.sec > 0:
                starts[sym.sec].add(sym.value)
                if sym.cls == link_cycle.EXTERNAL:
                    publics[sym.sec].add(sym.name)
        for sym in symbols.values():
            if sym.name not in names or sym.cls != link_cycle.EXTERNAL:
                continue
            if sym.sec <= 0:
                if sym.sec == -1 or sym.sec == 0 and sym.value:
                    found[sym.name].append(dict(
                        object=str(path), archive=False, comdat=False, selection=0,
                        absolute=sym.sec == -1, common=sym.sec == 0))
                continue
            section = sections[sym.sec - 1]
            end = min((value for value in starts[sym.sec] if value > sym.value),
                      default=section.size)
            pointers = {}
            for off, target, kind in section.relocs:
                if sym.value <= off and off + 4 <= end:
                    pointers[off - sym.value] = (
                        symbols[target].name, kind,
                        struct.unpack_from("<I", raw, section.ptr + off)[0])
            found[sym.name].append(dict(
                object=str(path), extent=end - sym.value, offset=sym.value,
                comdat=bool(section.flags & COMDAT), selection=section.sel,
                executable=bool(section.flags & EXECUTE), archive=False,
                other_publics=sorted(publics[sym.sec] - {sym.name}), pointers=pointers))
    for archive in archives:
        for member, raw in coffar.read_archive(archive):
            origin = f"{archive}({member})"
            if raw[:4] == b"\0\0\xff\xff":
                symbol = raw[20:].split(b"\0", 1)[0].decode("latin-1")
                # Conservatively exclude possible imported definitions, rather
                # than infer which archive member the native linker will extract.
                for name in {symbol, "__imp_" + symbol} & names:
                    found[name].append(dict(object=origin, archive=True, import_member=True,
                                            comdat=False, selection=0))
                continue
            sections, symbols = link_cycle.parse_coff(raw)
            for sym in symbols.values():
                if sym.name not in names or sym.cls != link_cycle.EXTERNAL:
                    continue
                if sym.sec <= 0:
                    if sym.sec == -1 or sym.sec == 0 and sym.value:
                        found[sym.name].append(dict(
                            object=origin, archive=True, comdat=False, selection=0,
                            absolute=sym.sec == -1, common=sym.sec == 0))
                    continue
                section = sections[sym.sec - 1]
                found[sym.name].append(dict(
                    object=origin, archive=True, import_member=False,
                    comdat=bool(section.flags & COMDAT), selection=section.sel))
    return found


def first_providers(objects, names, archives=()):
    """First external definition in response order; archives follow kept objects.
    Archive candidates are conservative: a possible earlier member is never
    presumed absent just because extraction has not been observed.
    """
    first = {}
    for path in objects.paths:
        obj = objects.get(path)
        if obj is None:
            raise ValueError(f"vtable target cannot inspect missing input {path}")
        for sym in obj[1].values():
            if sym.name in names and sym.cls == link_cycle.EXTERNAL and (
                    sym.sec != 0 or sym.value):
                first.setdefault(sym.name, str(Path(path).resolve()))
    for archive in archives:
        for member, raw in coffar.read_archive(archive):
            origin = f"{Path(archive).resolve()}({member})"
            if raw[:4] == b"\0\0\xff\xff":
                symbol = raw[20:].split(b"\0", 1)[0].decode("latin-1")
                for name in {symbol, "__imp_" + symbol} & names:
                    first.setdefault(name, origin)
                continue
            _sections, symbols = link_cycle.parse_coff(raw)
            for sym in symbols.values():
                if sym.name in names and sym.cls == link_cycle.EXTERNAL and (
                        sym.sec != 0 or sym.value):
                    first.setdefault(sym.name, origin)
    return first


class Targets:
    def __init__(self, rows, objects, omitted, object_for=None, symbol_for=None, archives=()):
        self.objects = objects
        self.kept = {Path(path).resolve() for path in objects.paths}
        self.omitted = {Path(path).resolve() for path in omitted}
        self.object_for = object_for or build.row_object
        self.symbol_for = symbol_for or build.ledger_object_symbol
        self.by_rva = collections.defaultdict(list)
        self.addresses = collections.defaultdict(set)
        self.paths, self.cache, self._selections = {}, {}, None
        for row in rows:
            try:
                rva = int(row["target_rva"], 16)
            except (KeyError, TypeError, ValueError):
                continue
            name = self.symbol_for(row) or row["name"]
            self.by_rva[rva].append((name, row))
            self.addresses[name].add(rva)
        self.first = first_providers(objects, set(self.addresses), archives)

    def path(self, row):
        key = (row["source"], build.ledger_member(row) if row["source"].lower().endswith(".lib") else None)
        if key not in self.paths:
            self.paths[key] = Path(self.object_for(row)).resolve()
        return self.paths[key]

    def resolve(self, rva):
        if rva in self.cache:
            return self.cache[rva]
        candidates = self.by_rva.get(rva, [])
        if not candidates:
            result = (None, "unrowed-target")
        elif any(self.path(row) in self.omitted for _name, row in candidates):
            result = (None, "omitted-target")
        else:
            failures, choices = [], []
            for name, row in candidates:
                if row.get("status") != "matched":
                    failures.append("unverified-target-row")
                    continue
                path = self.path(row)
                if path not in self.kept:
                    failures.append("target-not-kept")
                    continue
                if self.addresses[name] != {rva}:
                    failures.append("ambiguous-target-name")
                    continue
                obj = self.objects.get(path)
                sym = self.objects.defined(obj)[0].get(name) if obj else None
                if sym is None or sym.cls != link_cycle.EXTERNAL or sym.sec <= 0:
                    failures.append("target-not-external")
                    continue
                section = obj[0][sym.sec - 1]
                if not section.flags & EXECUTE or sym.value >= section.size:
                    failures.append("target-not-code")
                    continue
                if section.sel == 5:
                    failures.append("associative-target")
                    continue
                winner = self.first.get(name)
                if winner != str(path):
                    if not self.twin(path, winner, name):
                        failures.append("target-not-winning-provider")
                        continue
                    choices.append(dict(name=name, rva=rva, source=row["source"], object=winner,
                                        twin_of=str(path)))
                    continue
                choices.append(dict(name=name, rva=rva, source=row["source"], object=str(path)))
            result = (min(choices, key=lambda entry: (entry["name"], entry["source"])), None) if choices \
                else (None, sorted(set(failures))[0])
        self.cache[rva] = result
        return result


    def twin(self, ledger, winner, name):
        """The earlier kept COMDAT copy is the ledger body: same loaded bytes,
        selection and relocations, every relocation to an external name or to
        one weak external with the same default (weak_default).
        Only SELECT_ANY keeps the first copy, so every kept definition of the
        name must be SELECT_ANY; LARGEST or another rule could pick a later one."""
        if winner is None or Path(winner) not in self.kept:
            return False
        if self.selections().get(name) != {SELECT_ANY}:
            return False
        ours = comdat_body(self.objects, ledger, name)
        return ours is not None and ours == comdat_body(self.objects, Path(winner), name)

    def selections(self):
        """Target name -> COMDAT selections of its kept definitions (0: not COMDAT)."""
        if self._selections is None:
            self._selections = collections.defaultdict(set)
            for path in self.objects.paths:
                sections, symbols, _raw = self.objects.get(path)
                for sym in symbols.values():
                    if sym.name in self.addresses and sym.cls == link_cycle.EXTERNAL and sym.sec > 0:
                        sec = sections[sym.sec - 1]
                        self._selections[sym.name].add(sec.sel if sec.flags & COMDAT else 0)
        return self._selections


def comdat_body(objects, path, name):
    """A whole-section COMDAT code body, or None when anything loaded beside it
    (a non-discardable associative section, a local relocation) is unproven."""
    obj = objects.get(path)
    if obj is None:
        return None
    sections, symbols, raw = obj
    sym = objects.defined(obj)[0].get(name)
    if sym is None or sym.cls != link_cycle.EXTERNAL or sym.sec <= 0 or sym.value:
        return None
    sec = sections[sym.sec - 1]
    symptr = struct.unpack_from("<I", raw, 8)[0]
    for item in symbols.values():
        if item.cls != link_cycle.STATIC or not 0 < item.sec <= len(sections) or item.value:
            continue
        other = sections[item.sec - 1]
        if other.sel == ASSOCIATIVE and other.name == item.name and not other.flags & DISCARDABLE \
                and struct.unpack_from("<H", raw, symptr + 18 * item.i + 18 + 12)[0] == sym.sec:
            return None
    relocs = []
    for off, index, kind in sec.relocs:
        target = symbols[index]
        if target.cls == link_cycle.EXTERNAL:
            relocs.append((off, target.name, kind))
            continue
        default = weak_default(raw, symbols, target)
        if default is None:
            return None
        relocs.append((off, target.name, kind) + default)
    # The selection is judged once across every provider (Targets.selections);
    # the byte slice carries the section size.
    return sec.flags, raw[sec.ptr:sec.ptr + sec.size], relocs


def weak_default(raw, symbols, target):
    """(default name, characteristics) of an undefined weak external whose
    IMAGE_WEAK_EXTERN aux record names an external default, else None.

    A vftable adjustor thunk `??_EX@@W..` jumps to `??_EX@@UAEPAXI@Z`, a weak
    external defaulting to `??_GX`. The linker resolves a name once for the
    whole image, so two copies relocating to the same weak name reach the same
    code; the default and its search characteristics must agree as well."""
    if target.cls != WEAK_EXTERNAL or target.sec != 0 or target.value:
        return None
    symptr, count = struct.unpack_from("<II", raw, 8)
    if target.i + 1 >= count or raw[symptr + 18 * target.i + 17] < 1:
        return None
    tag, characteristics = struct.unpack_from("<II", raw, symptr + 18 * (target.i + 1))
    default = symbols.get(tag)
    if default is None or default.cls != link_cycle.EXTERNAL:
        return None
    return default.name, characteristics


def retail_slots(retail, row):
    size, rva = int(row["size"] or 0), int(row["address"], 16)
    if size < 4:
        return None, "unbounded-retail-row"
    slots = []
    for offset in range(0, size - 3, 4):
        raw = retail.read(rva + offset, 4)
        if raw is None or len(raw) != 4:
            return None, "unreadable-retail-row"
        value = struct.unpack("<I", raw)[0]
        if not retail.in_text(value):
            break
        slots.append(value - retail.base)
    if not slots:
        return None, "no-retail-slots"
    if len(slots) > 0xFFFF:
        return None, "too-many-slots"
    return slots, None


def matches(found, slots, addresses):
    """Prove only the positive slot pointers, not the implementation or class layout."""
    if found["extent"] < 4 * len(slots):
        return False
    for index, target in enumerate(slots):
        pointer = found["pointers"].get(index * 4)
        if pointer is None:
            return False
        name, kind, addend = pointer
        if kind != link_cycle.DIR32 or addend or addresses.get(name) != {target}:
            return False
    return True


def source_slot_mismatches(found, slots, addresses):
    """Keep the source copy's names and ledger RVAs, even when the bridge hides it."""
    result = []
    for index, expected in enumerate(slots):
        pointer = found["pointers"].get(index * 4)
        if pointer is not None:
            name, kind, addend = pointer
            rvas = sorted(addresses.get(name, ()))
            if kind == link_cycle.DIR32 and not addend and rvas == [expected]:
                continue
            result.append(dict(slot=index, name=name, ledger_rvas=rvas,
                               relocation_kind=kind, addend=addend,
                               retail_target_rva=expected))
        else:
            result.append(dict(slot=index, name="", ledger_rvas=[],
                               retail_target_rva=expected, reason="missing-source-slot"))
    return result


def discover_table_names(rows, objects, retail, object_for, symbol_for):
    """Bind current compiler vftable names at matched-row DIR32 sites.
    The whole row must match outside known relocation fields. No class spelling,
    destructor pin, adjacency, or MAP placement supplies an address.
    """
    kept = {Path(path).resolve() for path in objects.paths}
    bindings, rejected = [], []
    for row in rows:
        if row.get("status") != "matched" or not row.get("target_size"):
            continue
        path = Path(object_for(row)).resolve()
        if path not in kept:
            continue
        obj = objects.get(path)
        if obj is None:
            continue
        sections, symbols, raw = obj
        sym = objects.defined(obj)[0].get(symbol_for(row) or row["name"])
        if sym is None or sym.sec <= 0 or sym.cls != link_cycle.EXTERNAL:
            continue
        sec = sections[sym.sec - 1]
        if not sec.flags & EXECUTE:
            continue
        rva, size = int(row["target_rva"], 16), int(str(row["target_size"]), 0)
        relocs = [(off - sym.value, symbols[index], kind) for off, index, kind in sec.relocs
                  if sym.value <= off < sym.value + size]
        candidates = [(off, target) for off, target, kind in relocs
                      if kind == link_cycle.DIR32 and target.cls == link_cycle.EXTERNAL
                      and target.name.startswith("??_7") and off + 4 <= size]
        if not candidates:
            continue
        evidence = dict(source=row["source"], row_rva=rva, object=str(path),
                        names=sorted({target.name for _off, target in candidates}))
        target_bytes = retail.read(rva, size)
        body = raw[sec.ptr + sym.value:sec.ptr + sym.value + size]
        reason = None
        if sym.value + size > sec.size or target_bytes is None or len(target_bytes) != size:
            reason = "incomplete-matched-row"
        else:
            masked = set()
            for off, _target, kind in relocs:
                width = coffar.RELOC_WIDTH.get(kind)
                if width is None or off + width > size:
                    reason = "unsupported-row-relocation"
                    break
                masked.update(range(off, off + width))
            if reason is None and any(a != b for index, (a, b) in enumerate(zip(body, target_bytes))
                                      if index not in masked):
                reason = "matched-row-bytes-differ"
        if reason:
            rejected.append(dict(evidence, reason=reason))
            continue
        for off, target in candidates:
            addend = struct.unpack_from("<I", body, off)[0]
            if addend:
                rejected.append(dict(evidence, offset=off, name=target.name,
                                     reason="nonzero-vtable-addend", addend=addend))
                continue
            address = struct.unpack_from("<I", target_bytes, off)[0] - retail.base
            bindings.append(dict(evidence, offset=off, name=target.name, rva=address))
    return bindings, rejected


def plan(rows, inputs, omitted, retail, tables, archives=(), objects=None,
         object_for=None, symbol_for=None, source_of=None):
    """Return generated entries and explicit refusal reasons; input order is significant."""
    objects = objects or link_cycle.Objects(inputs)
    ledger_names = set().union(*(row_names(row) for row in tables)) if tables else set()
    targets = Targets(rows, objects, omitted, object_for, symbol_for, archives)
    bindings, rejected_bindings = discover_table_names(
        rows, objects, retail, targets.path, targets.symbol_for)
    by_address = collections.defaultdict(set)
    for binding in bindings:
        by_address[binding["rva"]].add(binding["name"])
    tables = [dict(row, names=";".join(sorted(
        row_names(row) | by_address.get(int(row["address"], 16), set())))) for row in tables]
    names = set().union(*(row_names(row) for row in tables)) if tables else set()
    # A name must have a unique retail address even when several ledger rows
    # describe one table. Never pick one conflicting row or slot extent.
    addresses = collections.defaultdict(set)
    grouped = collections.defaultdict(list)
    for row in tables:
        grouped[int(row["address"], 16)].append(row)
        for name in row_names(row):
            addresses[name].add(int(row["address"], 16))
    merged = []
    for rva, group in grouped.items():
        row = dict(group[0])
        row["names"] = ";".join(sorted(set().union(*(row_names(item) for item in group))))
        sequences = [retail_slots(retail, item) for item in group]
        row["_slot_conflict"] = any(sequence != sequences[0] for sequence in sequences[1:])
        merged.append(row)
    tables = merged
    for binding in bindings:
        addresses[binding["name"]].add(binding["rva"])
    indexed = set(grouped)
    discovery = dict(bindings=bindings, rejected=rejected_bindings,
                     names=len({binding["name"] for binding in bindings}),
                     unindexed=[binding for binding in bindings if binding["rva"] not in indexed])
    referenced = collections.defaultdict(list)
    native_names = set()
    for path in objects.paths:
        for sym in objects.get(path)[1].values():
            if sym.cls == link_cycle.EXTERNAL and sym.name.startswith("??_7"):
                native_names.add(sym.name)
            if sym.name in names and sym.cls == link_cycle.EXTERNAL and sym.sec == 0 and not sym.value:
                referenced[sym.name].append(str(path))
    discovery["native_names_without_address_binding"] = sorted(native_names - addresses.keys())
    discovery["new_name_bindings"] = [binding for binding in bindings if binding["name"] not in ledger_names]
    found = definitions(objects, names, archives)
    sources = {str(Path(path).resolve()): str(source).replace(str(build.ROOT) + "/", "")
               for path, source in (source_of or {}).items()}
    for row in rows:
        sources.setdefault(str(targets.path(row)), row["source"])
    table_addresses = addresses
    generated, refused, correct = [], [], []
    for row in tables:
        rva = int(row["address"], 16)
        names = row_names(row)
        copies = [(name, entry) for name in sorted(names) for entry in found.get(name, [])]
        kept = [(name, entry) for name, entry in copies if not entry["archive"]
                and not entry.get("common") and not entry.get("absolute")]
        active = {name for name, _copy in kept} | (names & referenced.keys())
        entry = dict(rva=rva, name=row["name"], names=sorted(active),
                     name_bindings=[binding for binding in bindings if binding["name"] in names],
                     name_addresses={name: sorted(table_addresses[name]) for name in sorted(active)})
        slots, reason = retail_slots(retail, row)
        entry["slots"] = len(slots or [])
        previous = next((copy for name, copy in kept if name == row["name"]),
                        kept[0][1] if kept else None)
        entry["source"] = sources.get(previous["object"], "") if previous else row.get("source", "")
        if previous and slots:
            entry.update(previous_object=previous["object"], previous_extent=previous["extent"],
                         source_slot_mismatches=source_slot_mismatches(previous, slots, targets.addresses))
        imported = [copy["object"] for _name, copy in copies if copy.get("import_member")]
        common = [copy["object"] for _name, copy in copies if copy.get("common")]
        strong = [copy["object"] for _name, copy in copies
                  if not copy["comdat"] and not copy.get("import_member") and not copy.get("common")]
        if strong:
            reason = "strong-definition"
            entry["providers"] = strong
        elif common:
            reason = "common-definition"
            entry["providers"] = common
        elif imported:
            reason = "archive-import-provider"
            entry["providers"] = imported
        elif not kept:
            reason = "no-kept-definition"
        elif row["_slot_conflict"]:
            reason = "conflicting-retail-slots"
        elif any(table_addresses[name] != {rva} for name in active):
            reason = "ambiguous-table-name"
        elif any(copy["selection"] != SELECT_ANY for _name, copy in copies):
            reason = "unsupported-selection"
        elif any(copy["offset"] or set(copy["other_publics"]) - names or copy["executable"]
                 for _name, copy in kept):
            reason = "shared-or-prefixed-comdat"
        if reason:
            refused.append({**entry, "reason": reason})
            continue
        resolved, blocked = [], []
        for index, target in enumerate(slots):
            selected, reason = targets.resolve(target)
            if reason:
                detail = dict(slot=index, target_rva=target, reason=reason)
                if reason == "target-not-winning-provider":
                    detail["providers"] = [dict(name=name, source=owner["source"],
                                                ledger_object=str(targets.path(owner)),
                                                first_object=targets.first.get(name))
                                           for name, owner in targets.by_rva[target]]
                blocked.append(detail)
            else:
                resolved.append(selected)
        if blocked:
            refused.append({**entry, "reason": blocked[0]["reason"], "blocked": blocked})
            continue
        for name in sorted(active):
            first = next((copy for candidate, copy in kept if candidate == name), None)
            if first is not None and matches(first, slots, targets.addresses):
                correct.append({**entry, "name": name, "object": first["object"]})
                continue
            origin = first["object"] if first else referenced[name][0]
            generated.append(dict(
                rva=rva, name=name, names=sorted(active), slots=resolved,
                source=sources.get(origin, ""), referenced_by=referenced.get(name, []),
                name_bindings=[binding for binding in bindings if binding["name"] == name],
                previous_object=first["object"] if first else None,
                previous_extent=first["extent"] if first else 0,
                source_slot_mismatches=source_slot_mismatches(first, slots, targets.addresses)
                    if first else []))
    return dict(tables=len(generated), retail_tables=len({entry["rva"] for entry in generated}), slots=sum(len(entry["slots"]) for entry in generated),
                twin_target_slots=sum(1 for entry in generated for slot in entry["slots"] if "twin_of" in slot),
                refused_tables=len(refused), refusal_reasons=dict(collections.Counter(
                    entry["reason"] for entry in refused)), already_correct=len(correct),
                entries=generated, refusals=refused, correct=correct, name_discovery=discovery,
                note="Temporary positive-slot copies; tables and slots must reach zero for G1.")


def write_object(entries, path):
    """Emit one independently keyed SELECT_ANY section per existing vtable name."""
    sections, symbols, relocations = [], [], {}
    targets = sorted({slot["name"] for entry in entries for slot in entry["slots"]})
    for number, entry in enumerate(entries, 1):
        sections.append((".rdata", RDATA, bytes(4 * len(entry["slots"])), SELECT_ANY))
        symbols.append((entry["name"], number, 0, link_cycle.EXTERNAL))
        relocations[number] = [(4 * index, slot["name"], link_cycle.DIR32)
                               for index, slot in enumerate(entry["slots"])]
    symbols.extend((name, 0, 0, link_cycle.EXTERNAL) for name in targets)
    return link_cycle.write_coff(path, sections, symbols, relocations)


def build_bridge(rows, inputs, omitted, archives, out, retail, objects=None, tables=None, source_of=None):
    tables = table_rows(build.ROOT) if tables is None else tables
    metadata = plan(rows, inputs, omitted, retail, tables, archives, objects, source_of=source_of)
    path = Path(out) / "retail_vtables.obj"
    path.unlink(missing_ok=True)
    if metadata["entries"]:
        write_object(metadata["entries"], path)
    metadata["object"] = path.name if metadata["entries"] else None
    metadata["queue"] = "vtable_bridge_queue.tsv"
    write_queue(metadata, Path(out) / metadata["queue"])
    (Path(out) / "vtable_bridge.json").write_text(json.dumps(metadata, indent=1) + "\n")
    print("vtable_name_discovery: " + json.dumps(dict(
        names=metadata["name_discovery"]["names"],
        rejected=len(metadata["name_discovery"]["rejected"]),
        unindexed=len(metadata["name_discovery"]["unindexed"]),
        native_names_without_address_binding=len(metadata["name_discovery"]["native_names_without_address_binding"]),
        new_name_bindings=len(metadata["name_discovery"]["new_name_bindings"])),
        sort_keys=True))
    print("vtable_bridge: " + json.dumps({key: metadata[key] for key in
          ("tables", "retail_tables", "slots", "twin_target_slots", "refused_tables", "refusal_reasons",
           "already_correct")},
          sort_keys=True))
    return (path if metadata["entries"] else None), metadata


QUEUE_FIELDS = ["state", "table", "class", "reason", "source", "retail_rva", "slots", "evidence"]


def write_queue(metadata, path, commit=None):
    """All refusals, followed by bridge retirement work; no omission of unowned rows."""
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        if commit is not None:
            handle.write(f"# real link at {commit}: tools/exit_link.py --blockers\n")
        writer = csv.DictWriter(handle, fieldnames=QUEUE_FIELDS, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        for state, entries in (("refused", metadata["refusals"]), ("bridged", metadata["entries"])):
            for entry in entries:
                name = entry["name"]
                # Preserve exact MSVC scope for templates instead of guessing a spelling.
                scope = name[4:].split("@@6", 1)[0] if name.startswith("??_7") else ""
                if scope and not scope.startswith("?$"):
                    scope = "::".join(reversed(scope.split("@")))
                writer.writerow(dict(
                    state=state, table=name, **{"class": scope},
                    reason=entry.get("reason", "bridge-retirement"), source=entry.get("source", ""),
                    retail_rva=f"0x{entry['rva']:08X}",
                    slots=len(entry["slots"]) if isinstance(entry["slots"], list) else entry["slots"],
                    evidence=json.dumps({key: value for key, value in entry.items()
                                         if key not in {"rva", "name", "source", "slots", "reason"}},
                                        sort_keys=True)))
