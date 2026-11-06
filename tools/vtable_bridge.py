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
        self.paths, self.cache = {}, {}
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
                if self.first.get(name) != str(path):
                    failures.append("target-not-winning-provider")
                    continue
                choices.append(dict(name=name, rva=rva, source=row["source"], object=str(path)))
            result = (min(choices, key=lambda entry: (entry["name"], entry["source"])), None) if choices \
                else (None, sorted(set(failures))[0])
        self.cache[rva] = result
        return result


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


def plan(rows, inputs, omitted, retail, tables, archives=(), objects=None,
         object_for=None, symbol_for=None, source_of=None):
    """Return generated entries and explicit refusal reasons; input order is significant."""
    objects = objects or link_cycle.Objects(inputs)
    names = set().union(*(row_names(row) for row in tables)) if tables else set()
    found = definitions(objects, names, archives)
    targets = Targets(rows, objects, omitted, object_for, symbol_for, archives)
    sources = {str(Path(path).resolve()): str(source).replace(str(build.ROOT) + "/", "")
               for path, source in (source_of or {}).items()}
    for row in rows:
        sources.setdefault(str(targets.path(row)), row["source"])
    table_addresses = collections.defaultdict(set)
    for row in tables:
        for name in row_names(row):
            table_addresses[name].add(int(row["address"], 16))
    generated, refused, correct = [], [], []
    for row in tables:
        rva = int(row["address"], 16)
        names = row_names(row)
        copies = [(name, entry) for name in sorted(names) for entry in found.get(name, [])]
        kept = [(name, entry) for name, entry in copies if not entry["archive"]
                and not entry.get("common") and not entry.get("absolute")]
        entry = dict(rva=rva, name=row["name"], names=sorted({name for name, _copy in kept}))
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
        elif len(entry["names"]) != 1:
            reason = "multiple-kept-names"
        elif table_addresses[entry["names"][0]] != {rva}:
            reason = "ambiguous-table-name"
        elif any(copy["selection"] != SELECT_ANY for _name, copy in copies):
            reason = "unsupported-selection"
        elif any(copy["offset"] or copy["other_publics"] or copy["executable"]
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
        name, first = kept[0]
        if matches(first, slots, targets.addresses):
            correct.append({**entry, "object": first["object"]})
            continue
        generated.append(dict(rva=rva, name=name, slots=resolved,
                              source=sources.get(first["object"], ""),
                              previous_object=first["object"], previous_extent=first["extent"],
                              source_slot_mismatches=source_slot_mismatches(
                                  first, slots, targets.addresses)))
    return dict(tables=len(generated), slots=sum(len(entry["slots"]) for entry in generated),
                refused_tables=len(refused), refusal_reasons=dict(collections.Counter(
                    entry["reason"] for entry in refused)), already_correct=len(correct),
                entries=generated, refusals=refused, correct=correct,
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
