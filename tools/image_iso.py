#!/usr/bin/env python3
"""Bounded static comparison of the actual linked PE32 against retail.

Called by image_report.py --image IMAGE. No compilation or execution.
An optional --objects JSON is a list of {path, sha256, source}; paths are
relative to that manifest. MAP object basenames must uniquely select an entry.
Objects are evidence for extents, never substitutes for the linked bytes.
write_object_manifest(rsp, mapfile, out, cwd=link_worktree) writes immutable
content-named snapshots and a MAP-bound manifest for --objects.
The Wave 0 receipt format is unchanged. Exit 1 means defects OR incomplete
analysis, 2 invalid inputs. This is not a G2 census or a runtime receipt.
"""
import argparse
import bisect
import collections
import csv
import hashlib
import json
import os
import re
import struct
from pathlib import Path

import build
import image_report
import link_cycle


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


class Image:
    def __init__(self, path):
        import pefile
        self.pe = pefile.PE(str(path), fast_load=False)
        if self.pe.OPTIONAL_HEADER.Magic != 0x10b:
            raise ValueError("only PE32 is supported")
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.sections = self.pe.sections
        self.relocations = set()
        for block in getattr(self.pe, "DIRECTORY_ENTRY_BASERELOC", []):
            for entry in block.entries:
                if entry.type == 3:
                    self.relocations.add(entry.rva)
                elif entry.type:
                    raise ValueError("unsupported PE relocation type")
        self.data = Path(path).read_bytes()
        self._initializers = None

    def read(self, rva, size):
        for sec in self.sections:
            start = sec.VirtualAddress
            end = start + max(sec.Misc_VirtualSize, sec.SizeOfRawData)
            if start <= rva and rva + size <= end:
                offset = rva - start
                raw = self.data[sec.PointerToRawData + offset:
                                sec.PointerToRawData + min(offset + size, sec.SizeOfRawData)]                     if offset < sec.SizeOfRawData else b""
                return raw + bytes(size - len(raw))
        return None

    def in_text(self, value):
        return any(s.Characteristics & 0x20000000 and
                   s.VirtualAddress <= value - self.base <
                   s.VirtualAddress + s.Misc_VirtualSize for s in self.sections)

    def initializers(self):
        # Existing retail heuristic, explicitly reported as static table discovery.
        if self._initializers is None:
            self._initializers = image_report.Retail(self.data).initializers()
        return self._initializers


def read_map(path, base):
    """Read publics and statics; Correspondence qualifies repeated/local names."""
    out = []
    for line in Path(path).read_text(encoding="latin-1").splitlines():
        f = line.split()
        if len(f) < 4 or not re.fullmatch(r"[0-9a-fA-F]{4}:[0-9a-fA-F]{8}", f[0]):
            continue
        try:
            rva = int(f[2], 16) - base
        except ValueError:
            continue
        if rva >= 0:
            out.append(dict(name=f[1], rva=rva, object=f[-1], source="", extent=None))
    return out


def object_name(value):
    return value.replace("\\", "/").rsplit("/", 1)[-1].rsplit(":", 1)[-1]


def source_key(value):
    return value.replace("\\", "/").removeprefix("./")


def attach_objects(publics, manifest, mapfile=None):
    """Only unambiguous exact MAP provider plus symbol selects an extent."""
    counts = collections.Counter()
    if manifest is None:
        counts["manifest_absent"] = 1
        return counts
    receipt = manifest.with_suffix(manifest.suffix + ".receipt.json")
    if receipt.exists() and mapfile is not None:
        if json.loads(receipt.read_text())["map_sha256"] != digest(mapfile):
            raise ValueError("manifest MAP hash mismatch")
    else:
        counts["manifest_not_bound_to_map"] = 1
    entries = json.loads(manifest.read_text())
    by_name = collections.defaultdict(list)
    for entry in entries:
        path = manifest.parent / entry["path"]
        if digest(path) != entry["sha256"]:
            raise ValueError("object hash mismatch: " + str(path))
        by_name[entry.get("provider", object_name(str(path)))].append((path, entry))
    parsed = {}
    for public in publics:
        choices = by_name.get(public["object"], by_name.get(object_name(public["object"]), []))
        if len(choices) != 1:
            counts["provider_unresolved"] += 1
            continue
        path, entry = choices[0]
        if path not in parsed:
            raw = path.read_bytes()
            try:
                sections, symbols = link_cycle.parse_coff(raw)
            except (ValueError, struct.error, IndexError):
                parsed[path] = {}
                counts["coff_objects_unanalyzed"] += 1
                continue
            definitions = collections.defaultdict(list)
            starts = collections.defaultdict(set)
            for sym in symbols.values():
                if sym.sec > 0:
                    starts[sym.sec].add(sym.value)
            starts = {sec: sorted(values) for sec, values in starts.items()}
            for sym in symbols.values():
                if sym.sec <= 0:
                    continue
                sec = sections[sym.sec - 1]
                values = starts[sym.sec]
                following = bisect.bisect_right(values, sym.value)
                end = values[following] if following < len(values) else sec.size
                definitions[sym.name].append(end - sym.value)
            parsed[path] = definitions
        lengths = set(parsed[path].get(public["name"], []))
        if len(lengths) == 1:
            public.update(extent=next(iter(lengths)), source=entry["source"])
            counts["extents_attached"] += 1
        else:
            counts["symbol_unresolved"] += 1
    return counts



def response_inputs(response, cwd):
    """Read explicit object/archive inputs, recursively, using link's cwd.
    Z: is Wine's Unix root. Other drive mappings must be supplied as Unix paths.
    No compiler, linker, archive writer or shared match-cache mutation.
    """
    seen, inputs = set(), []
    def unix_path(value):
        value = value.strip('"').replace("\\", "/")
        if value[:3].lower() == "z:/":
            return Path("/" + value[3:])
        if re.match(r"^[A-Za-z]:", value):
            raise ValueError("unsupported Wine drive in response: " + value)
        return (cwd / value).resolve()
    def visit(path):
        path = path.resolve()
        if path in seen:
            raise ValueError("recursive response file: " + str(path))
        seen.add(path)
        raw = path.read_bytes()
        text = raw.decode("utf-16") if raw.startswith((b"\xff\xfe", b"\xfe\xff")) else raw.decode("utf-8-sig")
        for token in re.findall(r'(?:[^\s"]|"[^"]*")+', text):
            if token.startswith("@"):
                visit(unix_path(token[1:]))
            else:
                value = token.replace('"', "")
                if value.lower().startswith(("/defaultlib:", "-defaultlib:")):
                    value = value.split(":", 1)[1].strip('"')
                elif re.match(r"^[-/][A-Za-z][A-Za-z0-9_]*:", value):
                    continue
                if value.lower().endswith((".obj", ".lib")):
                    inputs.append(unix_path(value))
        seen.remove(path)
    visit(Path(response))
    return list(dict.fromkeys(inputs))


def write_object_manifest(response, mapfile, out, *, cwd=None):
    """Snapshot explicit RSP objects and MAP-selected library members.
    Call immediately after linking, before objects can change:
      write_object_manifest(rsp, mapfile, out, cwd=link_worktree)
    Writes out (JSON list accepted by --objects), out.receipt.json and private
    objects/. Sidecar source path is accepted only when its object MD5 agrees.
    Unknown source stays empty; local-name mapping then fails closed.
    Implicit/default search-path libraries absent from RSP are counted unresolved.
    """
    import coffar
    response, mapfile, out = Path(response), Path(mapfile), Path(out)
    cwd = Path(cwd or Path.cwd()).resolve()
    response_hash, map_hash = digest(response), digest(mapfile)
    text = mapfile.read_text(encoding="latin-1")
    match = re.search(r"Preferred load address is\s+([0-9a-fA-F]+)", text)
    if not match:
        raise ValueError("MAP has no preferred load address")
    publics = read_map(mapfile, int(match[1], 16))
    inputs = response_inputs(response, cwd)
    by_basename = collections.defaultdict(list)
    for path in inputs:
        by_basename[object_name(str(path))].append(path)
    entries, counts = [], collections.Counter()
    snapshot = out.parent / (out.stem + "-objects")
    snapshot.mkdir(parents=True, exist_ok=True)
    archives = {}
    for provider in sorted({p["object"] for p in publics}):
        member_name = object_name(provider)
        archive_name = provider.replace("\\", "/")
        # A drive colon is not an archive/member separator.
        if re.match(r"^[A-Za-z]:/", archive_name):
            archive_name = archive_name[2:]
        library, colon, member = archive_name.partition(":")
        library = library.rsplit("/", 1)[-1]
        is_member = bool(colon)
        if is_member:
            choices = by_basename.get(library, []) or by_basename.get(library + ".lib", [])
        else:
            choices = by_basename.get(member_name, [])
        if len(choices) != 1:
            counts["providers_unresolved"] += 1
            continue
        path = choices[0]
        source = ""
        if is_member:
            if path not in archives:
                archives[path] = coffar.read_archive(path)
            candidates = [raw for name, raw in archives[path] if object_name(name) == object_name(member)]
            if len(candidates) != 1:
                counts["archive_members_unresolved"] += 1
                continue
            raw = candidates[0]
        else:
            raw = path.read_bytes()
            sidecar = path.with_suffix(".deps.json")
            if sidecar.exists():
                deps = json.loads(sidecar.read_text())
                if deps.get("object") == hashlib.md5(raw).hexdigest():
                    source = deps.get("path", "")
        target = snapshot / (hashlib.sha256(provider.encode() + raw).hexdigest() + ".obj")
        target.write_bytes(raw)
        entries.append(dict(path=os.path.relpath(target, out.parent),
                            sha256=hashlib.sha256(raw).hexdigest(),
                            source=source, provider=provider))
        counts["objects_snapshotted"] += 1
        counts["objects_source_unknown"] += not bool(source)
    if digest(response) != response_hash or digest(mapfile) != map_hash:
        raise ValueError("response/MAP changed during snapshot")
    out.write_text(json.dumps(entries, indent=2) + "\n")
    metadata = dict(response=str(response), response_sha256=response_hash,
                    map_sha256=map_hash, counts=dict(counts),
                    limitation="Snapshot immediately after linking; cannot prove earlier linker consumption.")
    out.with_suffix(out.suffix + ".receipt.json").write_text(json.dumps(metadata, indent=2) + "\n")
    return metadata


class Correspondence:
    """Interior offsets require a COFF extent, not a gap to the next ledger name."""
    def __init__(self, publics, addresses, qualified=None):
        self.exact = collections.defaultdict(set)
        self.spans = []
        self.proven_folds = set()
        self.ambiguous = set()
        self.targets = {}
        locations = collections.defaultdict(set)
        for p in publics:
            locations[p["name"]].add(p["rva"])
        for p in publics:
            repeated = len(locations[p["name"]]) > 1
            local = bool(re.fullmatch(r"_?\$E\d+", p["name"]))
            # Source must come from the hash-verified manifest, not a MAP guess.
            key = (p["name"], source_key(p.get("source", "")))
            if repeated or local:
                targets = (qualified or {}).get(key, set()) if key[1] else set()
                if not targets:
                    self.ambiguous.add(p["rva"])
            else:
                targets = addresses.get(p["name"], set())
            self.targets[id(p)] = set(targets)
            self.exact[p["rva"]].update(targets)
            if p["extent"]:
                if not targets and (repeated or local):
                    self.spans.append((p["rva"], p["extent"], None))
                elif len(targets) == 1:
                    self.spans.append((p["rva"], p["extent"], next(iter(targets))))
        # Sweep once; disjoint intervals make each query one binary search.
        events = collections.defaultdict(collections.Counter)
        for start, size, target in self.spans:
            if size <= 1:
                continue
            delta = None if target is None else target - start
            events[start + 1][delta] += 1
            events[start + size][delta] -= 1
        self.interval_starts, self.intervals = [], []
        active = collections.Counter()
        positions = sorted(events)
        for index, position in enumerate(positions):
            active.update(events[position])
            active = +active
            if active and index + 1 < len(positions):
                self.interval_starts.append(position)
                self.intervals.append((positions[index + 1], tuple(active)))

    def targets_for(self, public):
        return self.targets.get(id(public), set())

    def candidates(self, rva):
        if rva in self.ambiguous:
            return set()
        hits = set(self.exact.get(rva, ()))
        index = bisect.bisect_right(self.interval_starts, rva) - 1
        if index >= 0:
            end, deltas = self.intervals[index]
            if rva < end:
                if None in deltas:
                    return set()
                hits.update(rva + delta for delta in deltas)
        return hits

    def prove_folds(self, retail, sizes):
        # Whole retail row bytes must be identical, including address operands.
        # A masked shape, name match or ledger alias alone never admits a fold.
        for hits in self.exact.values():
            lengths = {sizes.get(rva) for rva in hits}
            if len(hits) > 1 and len(lengths) == 1 and None not in lengths and 0 not in lengths:
                bodies = [retail.read(rva, sizes[rva]) for rva in hits]
                if None not in bodies and len(set(bodies)) == 1:
                    self.proven_folds.add(frozenset(hits))

    def resolve(self, rva, expected=None):
        hits = self.candidates(rva)
        if len(hits) == 1:
            return next(iter(hits))
        if hits and frozenset(hits) in self.proven_folds:
            return expected if expected in hits else min(hits)
        return None


class Checker:
    def __init__(self, ours, retail, publics, addresses, qualified=None):
        self.ours, self.retail, self.publics = ours, retail, publics
        self.addresses = addresses
        self.mapping = Correspondence(publics, addresses, qualified)
        self.counts = collections.Counter({key: 0 for key in (
            "pointers_equal", "wrong_pointers", "pointers_unchecked", "globals_compared",
            "globals_extent_unanalyzed", "globals_retail_extent_unanalyzed",
            "vtable_slots_equal", "vtable_slots_wrong", "vtable_slots_unanalyzed",
            "no_object_retail_nonzero", "storage_undersized", "storage_split",
            "storage_unanalyzed", "initializers_unanalyzed")})
        self.counts["ambiguous_map_locations"] = len(self.mapping.ambiguous)
        self.defects = []
        self.by_name = collections.defaultdict(list)
        self.literal_widths = collections.defaultdict(set)
        self.literal_cache = {}
        for p in publics:
            literal = re.match(r"\?\?_C@_([01])", p["name"])
            if literal:
                self.literal_widths[p["rva"]].add(2 if literal[1] == "1" else 1)
            self.by_name[p["name"]].append(p)
        self.by_retail = collections.defaultdict(list)
        for p in publics:
            for target in self.mapping.targets_for(p):
                self.by_retail[target].append(p)
        self.retail_addresses = sorted(self.by_retail)

    def defect(self, family, rva, p, evidence):
        self.counts[family] += 1
        self.defects.append(dict(family=family, retail_rva=hex(rva),
                                 name=p.get("name", ""), object=p.get("object", ""),
                                 source=p.get("source", ""), evidence=evidence))

    def winner(self, names, retail_rva=None):
        found = [p for n in names for p in self.by_name.get(n, [])
                 if retail_rva is None or retail_rva in self.mapping.targets_for(p)]
        locations = {p["rva"] for p in found}
        if len(locations) == 1:
            return max(found, key=lambda p: p["extent"] or 0)
        return None

    def pointer(self, actual, expected):
        if actual == expected == 0:
            return "equal"
        got = self.mapping.resolve(actual - self.ours.base, expected - self.retail.base)
        if got is None:
            return "unchecked"
        if got == expected - self.retail.base:
            return "equal"
        if self.literal_alias(actual - self.ours.base, got, expected - self.retail.base):
            self.counts["pointers_literal_aliases"] += 1
            return "equal"
        return "wrong"

    def literal_alias(self, actual, mapped, expected):
        """Only a uniquely mapped MSVC literal can prove a pooled-copy alias.
        Compare complete NUL-terminated values in ours and BOTH retail copies;
        never equate arbitrary globals, code, prefixes or ambiguous mappings.
        """
        key = (actual, mapped, expected)
        if key in self.literal_cache:
            return self.literal_cache[key]
        widths = self.literal_widths.get(actual, set())
        same = False
        if len(widths) == 1 and not self.retail.in_text(self.retail.base + expected):
            width = next(iter(widths))
            for offset in range(0, 4096, width):
                parts = (self.ours.read(actual + offset, width),
                         self.retail.read(mapped + offset, width),
                         self.retail.read(expected + offset, width))
                if parts[0] is None or len(set(parts)) != 1:
                    break
                if parts[0] == bytes(width):
                    same = True
                    break
        self.literal_cache[key] = same
        return same

    def code_equal(self, actual, expected, size):
        """Whole row instruction comparison preserves ret immediates and ECX adjustment.
        Address operands are translated only with unique correspondence. Unrowed
        forwarders are followed only for a single direct JMP with identical ECX
        add/sub prefixes; other shapes remain unchecked.
        """
        import capstone
        from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        a, b = self.ours.read(actual, size), self.retail.read(expected, size)
        if a is None or b is None:
            return None
        aa, bb = list(md.disasm(a, actual)), list(md.disasm(b, expected))
        if not aa or sum(i.size for i in aa) != size or sum(i.size for i in bb) != size:
            return None
        if len(aa) != len(bb):
            return False
        for x, y in zip(aa, bb):
            if x.id != y.id or x.size != y.size or len(x.operands) != len(y.operands):
                return False
            masked = set()
            for xo, yo in zip(x.operands, y.operands):
                if xo.type != yo.type:
                    return False
                if xo.type == X86_OP_IMM and (x.group(capstone.CS_GRP_JUMP) or x.group(capstone.CS_GRP_CALL)):
                    # capstone reports RVA for relative branches.
                    want = yo.imm
                    got = self.mapping.resolve(xo.imm, want)
                    if actual <= xo.imm < actual + size:
                        got = expected + xo.imm - actual
                    if got is None:
                        return None
                    if got != want:
                        return False
                    masked.update(range(x.imm_offset, x.imm_offset + x.imm_size))
                elif xo.type == X86_OP_IMM and x.address + x.imm_offset in self.ours.relocations:
                    verdict = self.pointer(xo.imm & 0xffffffff, yo.imm & 0xffffffff)
                    if verdict == "unchecked":
                        return None
                    if verdict == "wrong":
                        return False
                    masked.update(range(x.imm_offset, x.imm_offset + x.imm_size))
                elif xo.type == X86_OP_MEM and x.address + x.disp_offset in self.ours.relocations:
                    verdict = self.pointer(xo.mem.disp & 0xffffffff, yo.mem.disp & 0xffffffff)
                    if verdict == "unchecked":
                        return None
                    if verdict == "wrong":
                        return False
                    masked.update(range(x.disp_offset, x.disp_offset + x.disp_size))
            if any(x.bytes[k] != y.bytes[k] for k in range(x.size) if k not in masked):
                return False
        return True

    def forwarder(self, image, rva):
        """Strict x86 this-adjustor: optional add/sub ecx, imm; direct jmp rel32."""
        raw = image.read(rva, 11)
        if raw is None:
            return None
        offset, adjustment = 0, 0
        if raw[:2] in (b"\x83\xc1", b"\x83\xe9"):
            adjustment = struct.unpack("b", raw[2:3])[0] * (1 if raw[1] == 0xc1 else -1)
            offset = 3
        elif raw[:2] in (b"\x81\xc1", b"\x81\xe9"):
            adjustment = struct.unpack("<i", raw[2:6])[0] * (1 if raw[1] == 0xc1 else -1)
            offset = 6
        if raw[offset] != 0xe9:
            return None
        return rva + offset + 5 + struct.unpack_from("<i", raw, offset + 1)[0], adjustment

    def slot(self, actual, expected, sizes):
        a, b = actual - self.ours.base, expected - self.retail.base
        af, bf = self.forwarder(self.ours, a), self.forwarder(self.retail, b)
        if af or bf:
            at, adjust_a = af if af else (a, 0)
            bt, adjust_b = bf if bf else (b, 0)
            mapped = self.mapping.resolve(at, bt)
            if mapped is None:
                return None
            if mapped != bt or adjust_a != adjust_b:
                return False
            a, b = at, bt
        mapped = self.mapping.resolve(a, b)
        if mapped is None:
            return None
        if mapped != b:
            return False
        size = sizes.get(b)
        return self.code_equal(a, b, size) if size else None

    def ledger(self, rows, sizes):
        self.mapping.prove_folds(self.retail, sizes)
        self.counts["proven_exact_byte_fold_groups"] = len(self.mapping.proven_folds)
        for row in rows:
            rva, size = int(row["address"], 16), int(row["size"] or 0)
            names = {row["name"], *(row.get("names") or "").split(";")} - {""}
            kind = row["kind"]
            self.counts[kind + "_ledger_entries"] += 1
            if kind not in ("vtable", "global", "string", "wstring", "float"):
                self.counts[kind + "_unanalyzed"] += 1
                continue
            p = self.winner(names, rva)
            retail = self.retail.read(rva, size)
            if p is None:
                family = "mapping_ambiguous" if any(self.by_name.get(n) for n in names) else "no_object_retail_nonzero"
                if retail and any(retail) or family == "mapping_ambiguous":
                    self.defect(family, rva, row, "No unique linked MAP location for ledger names")
                else:
                    self.counts["absent_zero_globals_unanalyzed"] += 1
                continue
            if row["kind"] == "vtable":
                words = image_report.Retail.vtable_words(self.retail, rva, size)
                self.counts["vtable_slots_expected"] += words
                if p["extent"] is None:
                    self.counts["vtable_extent_unanalyzed"] += 1
                elif p["extent"] < words * 4:
                    self.defect("vtable_short", rva, p, f"Winning extent {p['extent']} < retail code-pointer run {words * 4}; run is bounded by ledger extent")
                for offset in range(0, words * 4, 4):
                    a, b = self.ours.read(p["rva"] + offset, 4), self.retail.read(rva + offset, 4)
                    if a is None or b is None or p["extent"] is not None and offset + 4 > p["extent"]:
                        self.counts["vtable_slots_unanalyzed"] += 1
                        continue
                    result = self.slot(struct.unpack("<I", a)[0], struct.unpack("<I", b)[0], sizes)
                    self.counts["vtable_slots_" + ("equal" if result is True else "wrong" if result is False else "unanalyzed")] += 1
                    if result is False:
                        self.defect("vtable_slot", rva + offset, p, f"slot +{offset}: target/body/this-adjustment differs")
                continue
            if not size or retail is None or p["extent"] is None:
                self.counts["globals_extent_unanalyzed"] += 1
                continue
            if p["extent"] < size:
                # Data ledger extents can be gaps. Do not diagnose storage from this.
                self.counts["globals_retail_extent_unanalyzed"] += 1
                continue
            ours = self.ours.read(p["rva"], size)
            if ours is None:
                self.counts["globals_bytes_unanalyzed"] += 1
                continue
            if kind in ("string", "wstring", "float"):
                self.counts[kind + "_compared"] += 1
                if ours != retail:
                    self.defect(kind + "_contents", rva, p, f"Bytes differ over retail ledger extent {size}")
                continue
            masked = set()
            for offset in range(size - 3):
                ar, br = p["rva"] + offset, rva + offset
                if ar not in self.ours.relocations and br not in self.retail.relocations:
                    continue
                masked.update(range(offset, offset + 4))
                actual, expected = struct.unpack_from("<I", ours, offset)[0], struct.unpack_from("<I", retail, offset)[0]
                result = self.pointer(actual, expected)
                self.counts[{"equal": "pointers_equal", "wrong": "wrong_pointers", "unchecked": "pointers_unchecked"}[result]] += 1
                if result == "wrong":
                    self.defect("global_pointer", rva + offset, p, f"+{offset}: {hex(actual)} versus retail {hex(expected)}")
            for offset in range(0, size - 3, 4):
                if any(k in masked for k in range(offset, offset + 4)):
                    continue
                value = struct.unpack_from("<I", retail, offset)[0]
                if self.retail.read(value - self.retail.base, 1) is not None:
                    self.counts["pointers_unchecked"] += 1
                    self.counts["untyped_pointer_candidates"] += 1
            differing = [k for k in range(size) if k not in masked and ours[k] != retail[k]]
            self.counts["globals_compared"] += 1
            if differing:
                self.defect("global_contents", rva, p, f"{len(differing)} non-pointer bytes differ over retail extent {size}; first +{differing[0]}")

        for kind in ("global", "string", "wstring", "float"):
            self.counts[kind + "_unanalyzed"] = (
                self.counts[kind + "_ledger_entries"] -
                self.counts["globals_compared" if kind == "global" else kind + "_compared"])

    def initializers(self):
        expected, actual = self.retail.initializers(), self.ours.initializers()
        self.counts.update(initializers_retail=len(expected), initializers_image=len(actual))
        mapped = [self.mapping.resolve(rva) for rva in actual]
        self.counts["initializers_unanalyzed"] = mapped.count(None)
        counts = collections.Counter(mapped)
        for rva in set(mapped) - set(expected) - {None}:
            self.defect("initializer_extra", rva, {}, f"{counts[rva]} static registrations absent from retail table")
        for rva in expected:
            if counts[rva] > 1 or counts[rva] == 0 and None not in mapped:
                self.defect("initializer_count", rva, {}, f"static registrations resolved: {counts[rva]}; unresolved table entries: {mapped.count(None)}")
        self.counts["initializers_missing_or_unresolved"] = sum(counts[rva] == 0 for rva in expected)
        sequence = [rva for rva in mapped if rva in set(expected)]
        wanted = [rva for rva in expected if rva in set(sequence)]
        if sequence != wanted:
            self.defect("initializer_order", 0, {}, "Resolved static initializer sequence differs from retail")
        self.counts["initializers_runtime_execution_unanalyzed"] = len(expected)
        # The bridge has no public symbols. A MAP public count cannot count it.
        self.counts["initializer_bridge_public_symbols_seen"] = sum("retail_initializers" in p["object"] for p in self.publics)
        self.counts["initializer_bridge_entries_unanalyzed"] = len(expected)

    def storage(self, evidence):
        """Evidence is a proven base+offset store/access, never a ledger gap."""
        for e in evidence:
            self.counts["storage_accesses_proven"] += 1
            p = self.winner({e["name"]}, e["rva"])
            if p is None or p["extent"] is None:
                self.counts["storage_unanalyzed"] += 1
                continue
            end = e["offset"] + e["width"]
            if end > p["extent"]:
                self.defect("storage_undersized", e["rva"], p,
                            f"{e['evidence']}; access ends +{end}, winning extent {p['extent']}")
            first = bisect.bisect_right(self.retail_addresses, e["rva"])
            last = bisect.bisect_left(self.retail_addresses, e["rva"] + end)
            for target in self.retail_addresses[first:last]:
                offset = target - e["rva"]
                for q in self.by_retail[target]:
                    if q["rva"] != p["rva"] + offset:
                        self.defect("storage_split", target, q,
                                    f"{e['evidence']}; field of {e['name']} +{offset} at separate linked address")

    def report(self):
        return dict(schema_version=1, complete=False, g2_pass=False, counts=dict(self.counts),
                    defects=self.defects,
                    defect_attribution_missing=dict(
                        object=sum(not d["object"] for d in self.defects),
                        source=sum(not d["source"] for d in self.defects)) ,
                    limitations=["Static tables do not prove initializer execution.",
                                 "Retail data extents and vtable runs are ledger-bounded, not recovered layouts.",
                                 "Unknown pointer correspondence fails analysis; no shape-only alias credit.",
                                 "Storage scan proves only straight-line ECX stores before first control transfer.",
                                 "No reachability census, indirect calls, inherited constructors or shared-field ownership proof."])


def storage_evidence(retail, rows):
    """Direct mov ecx, global; call ctor; straight-line ctor stores through ECX.
    Stop at control transfers or an ECX write. These are lower bounds only.
    """
    import capstone
    from capstone.x86_const import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_ECX
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    names = {int(r["address"], 16): r["name"] for r in rows if r["kind"] == "global"}
    result = []
    for init in retail.initializers():
        raw = retail.read(init, 256)
        if raw is None:
            continue
        base = None
        for ins in md.disasm(raw, init):
            ops = ins.operands
            if ins.mnemonic == "mov" and len(ops) == 2 and ops[0].type == X86_OP_REG and ops[0].reg == X86_REG_ECX:
                base = ops[1].imm - retail.base if ops[1].type == X86_OP_IMM else None
            elif ins.mnemonic == "call":
                if base in names and ops[0].type == X86_OP_IMM:
                    ctor = ops[0].imm
                    body = retail.read(ctor, 256)
                    for store in md.disasm(body or b"", ctor):
                        if store.group(capstone.CS_GRP_JUMP) or store.group(capstone.CS_GRP_CALL) or store.group(capstone.CS_GRP_RET):
                            break
                        operands = store.operands
                        if operands and operands[0].type == X86_OP_MEM and operands[0].access & capstone.CS_AC_WRITE:
                            mem = operands[0].mem
                            if mem.base == X86_REG_ECX and not mem.index and mem.disp >= 0:
                                result.append(dict(name=names[base], rva=base, offset=mem.disp,
                                                   width=operands[0].size,
                                                   evidence=f"retail initializer {hex(init)} calls {hex(ctor)}; store at {hex(store.address)}"))
                        if X86_REG_ECX in store.regs_access()[1]:
                            break
                base = None
            elif ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_RET):
                break
            elif X86_REG_ECX in ins.regs_access()[1]:
                base = None
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--image", required=True, type=Path)
    parser.add_argument("--map", required=True, type=Path)
    parser.add_argument("--retail", type=Path, default=build.EXE)
    parser.add_argument("--objects", type=Path)
    parser.add_argument("--out", type=Path, default=Path("build/image_iso"))
    args = parser.parse_args(argv)
    receipt_path = args.image.with_name("image_receipt.json")
    receipt = json.loads(receipt_path.read_text())
    for key, path in (("image_sha256", args.image), ("map_sha256", args.map)):
        if receipt[key] != digest(path):
            parser.error(key + " mismatch")
    ours, retail = Image(args.image), Image(args.retail)
    if int(receipt["base"], 16) != ours.base or receipt["kind"] not in ("real", "diagnostic"):
        parser.error("receipt base/kind mismatch")
    if receipt["kind"] == "real" and receipt["stubbed"]:
        parser.error("real receipt has stubs")
    publics = read_map(args.map, ours.base)
    object_counts = attach_objects(publics, args.objects, args.map)
    with (build.ROOT / "reverse/data_ledger.csv").open(newline="") as f:
        rows = list(csv.DictReader(f))
    addresses = collections.defaultdict(set)
    sizes = {}
    qualified = collections.defaultdict(set)
    names = {p["name"] for p in publics}
    for row in rows:
        for name in {row["name"], *(row.get("names") or "").split(";")} - {""}:
            addresses[name].add(int(row["address"], 16))
            if row.get("source"):
                qualified[(name, source_key(row["source"]))].add(int(row["address"], 16))
    # Stream the code ledger; retain only symbols present in this MAP.
    with (build.ROOT / "reverse/functions.csv").open(newline="") as f:
        for row in csv.DictReader(f):
            symbol = build.ledger_object_symbol(row) or row["name"]
            if symbol not in names and row["name"] not in names:
                continue
            try:
                rva, size = int(row["target_rva"], 16), int(row["target_size"])
            except ValueError:
                continue
            addresses[symbol].add(rva)
            addresses[row["name"]].add(rva)
            sizes[rva] = size
            if row.get("source"):
                for name in (symbol, row["name"]):
                    qualified[(name, source_key(row["source"]))].add(rva)
    checker = Checker(ours, retail, publics, addresses, qualified)
    checker.ledger(rows, sizes)
    checker.initializers()
    evidence = storage_evidence(retail, rows)
    checker.counts["storage_initializers_considered"] = len(retail.initializers())
    proven = {e["rva"] for e in evidence}
    checker.counts["storage_objects_with_proven_access"] = len(proven)
    checker.counts["storage_globals_without_proven_access"] = sum(
        r["kind"] == "global" and int(r["address"], 16) not in proven for r in rows)
    checker.storage(evidence)
    report = checker.report()
    report.update(inputs=dict(image=str(args.image), map=str(args.map), retail=str(args.retail),
                              image_sha256=digest(args.image), map_sha256=digest(args.map),
                              retail_sha256=digest(args.retail), receipt=receipt,
                              objects_sha256=digest(args.objects) if args.objects else None),
                  object_analysis=dict(object_counts), map_symbols=len(publics))
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    with (args.out / "defects.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["family", "retail_rva", "name", "object", "source", "evidence"], delimiter="\t")
        writer.writeheader()
        writer.writerows(report["defects"])
    print(json.dumps({"counts": report["counts"], "complete": False}, indent=2))
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
