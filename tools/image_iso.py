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
kept_copies in the report and kept_copies.tsv list rowed names whose kept copy differs from
retail: byte-level with masked relocations, so not proof of the callees, and report only.
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
import subprocess
import sys
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

    def readonly(self, rva, size=1):
        # Retail marks even .rdata writable; literal pooling is section-scoped.
        return any(sec.Name.rstrip(b"\0") == b".rdata" and
                   sec.VirtualAddress <= rva and rva + size <= sec.VirtualAddress +
                   max(sec.Misc_VirtualSize, sec.SizeOfRawData) for sec in self.sections)

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
        path = manifest.parent / entry["path"].replace("\\", "/")
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
                parsed[path] = ({}, {}, frozenset())
                counts["coff_objects_unanalyzed"] += 1
                continue
            definitions = collections.defaultdict(list)
            section_evidence = {}
            for sec in sections:
                if sec.name.startswith((".text", ".data", ".rdata")):
                    section_evidence[sec.idx] = dict(
                        body=raw[sec.ptr:sec.ptr + sec.size], size=sec.size, flags=sec.flags,
                        is_code=sec.name.startswith(".text"),
                        relocations=tuple((offset, kind) for offset, _index, kind in sec.relocs),
                        relocation_targets={offset: dict(name=symbols[index].name, cls=symbols[index].cls,
                            section=symbols[index].sec) for offset, index, _kind in sec.relocs if index in symbols})
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
                definitions[sym.name].append((end - sym.value, sym.sec, sym.value))
            external = frozenset(sym.name for sym in symbols.values() if sym.sec > 0 and sym.cls == link_cycle.EXTERNAL)
            parsed[path] = (definitions, section_evidence, external)
        definitions, section_evidence, external = parsed[path]
        public["external"] = public["name"] in external
        records = set(definitions.get(public["name"], []))
        lengths = {record[0] for record in records}
        if len(lengths) == 1:
            public.update(extent=next(iter(lengths)), source=entry["source"])
            counts["extents_attached"] += 1
            if len(records) == 1:
                _length, section, offset = next(iter(records))
                if section in section_evidence:
                    public["coff" if section_evidence[section]["is_code"] else "data_coff"] = dict(
                        section=section_evidence[section], offset=offset)
            else:
                kinds = {section_evidence[section]["is_code"] for _length, section, _offset in records
                         if section in section_evidence}
                if True in kinds:
                    counts["code_symbol_locations_ambiguous"] += 1
                if False in kinds:
                    counts["data_symbol_locations_ambiguous"] += 1
        else:
            counts["symbol_unresolved"] += 1
    return counts



def place_statics(publics, manifest, wanted, image, missed=None, failed=None):
    """{name: [placement]} for data symbols of `wanted` the MAP does not list: MSVC's MAP lists no internal-linkage
    data (a file `static`, a namespace-scope `const`, an anonymous namespace's global), so each is placed through
    its own object. A COFF section is contiguous in the image: its start is fixed by any symbol in it the MAP
    places for that object (an anchor), or by a DIR32 relocation to any symbol in it from a section an anchor
    places (the image's relocated word, less the relocation's in-place addend and the target's value). A section
    with no start, or with two different ones, places nothing. A placement is a public-shaped dict (static=True)
    whose extent runs to the next symbol of its section, with its section's COFF evidence (data_coff)."""
    if manifest is None or not wanted:
        return {}
    placed = collections.defaultdict(lambda: collections.defaultdict(set))   # exact MAP object -> name -> rvas
    map_objects = collections.defaultdict(set)                                # basename -> exact MAP objects
    for p in publics:
        placed[p["object"]][p["name"]].add(p["rva"])
        map_objects[object_name(p["object"])].add(p["object"])
    entries = json.loads(manifest.read_text())
    manifest_basenames = collections.Counter(object_name(e.get("provider", e["path"])) for e in entries)

    def library(value):
        last = value.replace("\\", "/").rsplit("/", 1)[-1]
        return last.rsplit(":", 1)[0] if ":" in last else None

    def anchors(provider):
        """The MAP placements of this object: its exact MAP object, or the one MAP object of its basename when that
        basename is unique among MAP objects and manifest entries alike and the library qualifiers agree."""
        if provider in placed:
            return placed[provider]
        base = object_name(provider)
        candidates = map_objects.get(base, set())
        if len(candidates) == 1 and manifest_basenames[base] == 1:
            only = next(iter(candidates))
            if library(only) == library(provider):
                return placed[only]
        return {}
    found = collections.defaultdict(list)
    for entry in entries:
        path = manifest.parent / entry["path"].replace("\\", "/")
        raw = path.read_bytes()
        if digest(path) != entry["sha256"]:
            raise ValueError("object hash mismatch: " + str(path))
        try:
            sections, symbols = link_cycle.parse_coff(raw)
        except (ValueError, struct.error, IndexError):
            if failed is not None:
                failed.append(entry["path"])  # what it defines is unknown, not absent
            continue
        if missed is not None:                # defined here, absent from the MAP: storage nothing locates
            missed.update(sym.name for sym in symbols.values() if sym.name in wanted and sym.sec > 0
                          and sym.cls == link_cycle.EXTERNAL)
        targets = [sym for sym in symbols.values() if sym.name in wanted and sym.cls == link_cycle.STATIC
                   and sym.sec > 0]
        if not targets:
            continue
        here = anchors(entry.get("provider", object_name(str(path))))
        anchored = collections.defaultdict(set)
        for sym in symbols.values():
            locations = here.get(sym.name, ())
            if sym.sec > 0 and len(locations) == 1:
                anchored[sym.sec].add(next(iter(locations)) - sym.value)
        # Evidence for a section's start: its anchors, and DIR32 relocations read from sections whose start is
        # anchored. A disputed section (two starts) and every section whose relocations spoke to the dispute are
        # distrusted -- either side may be the wrong one -- and lend no evidence; repeat until nothing new is
        # distrusted, so no placement rests on a start the evidence contradicts.
        distrusted = set()
        while True:
            claims = collections.defaultdict(lambda: collections.defaultdict(set))   # sec -> start -> sources
            for sec, values in anchored.items():
                for value in values:
                    claims[sec][value].add(None)
            for sec, values in anchored.items():
                if len(values) != 1 or sec in distrusted:
                    continue
                start = next(iter(values))
                section = sections[sec - 1]
                for offset, index, kind in section.relocs:
                    target = symbols.get(index)
                    if kind != link_cycle.DIR32 or target is None or target.sec <= 0:
                        continue
                    word = image.read(start + offset, 4)
                    if word is None or section.ptr == 0:
                        continue
                    addend = struct.unpack_from("<I", raw, section.ptr + offset)[0]
                    value = (struct.unpack("<I", word)[0] - addend - target.value - image.base) & 0xFFFFFFFF
                    claims[target.sec][value].add(sec)
            disputed = {sec for sec, by in claims.items() if len(by) > 1}
            spoke = {source for sec in disputed for sources in claims[sec].values() for source in sources
                     if source is not None}
            if not (disputed | spoke) - distrusted:
                break
            distrusted |= disputed | spoke
        starts = {sec: set(by) for sec, by in claims.items() if sec not in distrusted}
        values_by_sec = collections.defaultdict(set)
        for sym in symbols.values():
            if sym.sec > 0:
                values_by_sec[sym.sec].add(sym.value)
        for sym in targets:
            begins = starts.get(sym.sec, set())
            if len(begins) != 1:
                if missed is not None:
                    missed.add(sym.name)      # an object defines it, but nothing places it
                continue
            section = sections[sym.sec - 1]
            values = sorted(values_by_sec[sym.sec])
            following = bisect.bisect_right(values, sym.value)
            end = values[following] if following < len(values) else section.size
            evidence = dict(body=raw[section.ptr:section.ptr + section.size] if section.ptr else b"",
                            size=section.size, flags=section.flags, is_code=section.name.startswith(".text"),
                            relocations=tuple((offset, kind) for offset, _index, kind in section.relocs),
                            relocation_targets={offset: dict(name=symbols[index].name, cls=symbols[index].cls,
                                section=symbols[index].sec) for offset, index, _kind in section.relocs
                                if index in symbols})
            found[sym.name].append(dict(name=sym.name, rva=next(iter(begins)) + sym.value, extent=end - sym.value,
                object=entry.get("provider", object_name(str(path))), source=entry["source"], static=True,
                data_coff=dict(section=evidence, offset=sym.value)))
    return dict(found)


POOLED = re.compile(r"\?\?_C@_[01]|__real@[0-9a-fA-F]+|__xmm@[0-9a-fA-F]+")


def unlisted_names(rows, by_name):
    """Every ledger name (a row's own or an alias) the MAP does not list, one by one: those place_statics looks
    for. A row whose pooled alias the MAP lists can still name a static of its own."""
    return {n for row in rows for n in {row["name"], *(row.get("names") or "").split(";")} - {""}
            if not by_name.get(n)}


def literal_length(name):
    """The byte length, terminator and embedded NULs included, that an MSVC string literal's decorated name
    encodes (`??_C@_0` narrow / `_1` wide, then the length: a digit d is d + 1, else hex digits A..P ended by
    `@`); None when the name does not spell one."""
    found = re.match(r"\?\?_C@_[01](?:(\d)|([A-P]+)@)", name)
    if not found:
        return None
    if found.group(1):
        return int(found.group(1)) + 1
    return int("".join("0123456789ABCDEF"[ord(c) - 65] for c in found.group(2)), 16)


def pooled_length(name, retail, rva, size):
    """The length of a pooled constant's own value: a literal's from its decorated name (within `size`), a
    __real@/__xmm@ constant's width from its name; None when it cannot be told."""
    if name.startswith("??_C@_"):
        length = literal_length(name)
        return length if length and (not size or length <= size) else None
    digits = name.split("@", 1)[1]
    return len(digits) // 2 if len(digits) in (8, 16, 32) else None


def kept_copies(ours, retail, publics, ledger):
    """Report only: rowed names whose copy in this image differs from retail, read from the linked image.
    A row is byte-verified in its owner's object, but the linker keeps the first COMDAT definition on its
    command line, so the image can run another unit's copy under the row's name. The census cannot see
    this, because it models another object order than the real link's. Masked by the kept copy's own
    relocation fields, trailing padding aside; equal bytes do not prove the callees. `ledger` is
    {symbol: [rows]}. Only external symbols are shared copies: a label such as $L10008 is named per object.
    A name with rows at several addresses is judged against all of them and recorded, whatever their order. A copy matching
    any of its rows is not in `names`, which does not show it suits every retail occurrence: one matching only some is
    listed in `matches_only_some_rows`.
    What cannot be judged is counted, never passed. Nothing here feeds counts, defects or a gate."""
    shared = [public for public in publics if public.get("external") is not False and public["name"] in ledger]
    seen = collections.Counter(public["name"] for public in shared)
    counts = collections.Counter()
    differ, several, some = [], [], []
    for public in shared:
        rows = sorted({int(row["target_rva"], 16): row for row in ledger[public["name"]]}.items())
        coff = public.get("coff")
        if seen[public["name"]] > 1:
            counts["unanalyzed_repeated_name"] += 1
            continue
        if coff is None:
            counts["unanalyzed_no_object_evidence"] += 1
            continue
        section = coff["section"]
        if not section["flags"] & link_cycle.COMDAT:
            continue
        counts["rowed_comdats_checked"] += 1
        offset = coff["offset"]
        length = section["size"] - offset
        fields = [(where - offset, kind) for where, kind in section["relocations"] if where >= offset]
        if any(kind not in _COFF_WIDTH for _where, kind in fields):
            counts["unanalyzed_relocation_kind"] += 1
            continue
        mine = ours.read(public["rva"], length)
        bodies = [retail.read(rva, int(row["target_size"])) for rva, row in rows]
        if mine is None or any(body is None for body in bodies):
            counts["unanalyzed_unreadable"] += 1
            continue
        verdicts = [same_copy(mine, body, fields) for body in bodies]
        if len(rows) > 1:
            counts["names_with_several_rows"] += 1
            several.append(dict(name=public["name"], retail_rvas=[f"0x{rva:08X}" for rva, _row in rows],
                                verdicts=verdicts, kept_source=public["source"]))
        if True in verdicts:
            if not all(verdict is True for verdict in verdicts):
                counts["kept_copy_matches_only_some_rows"] += 1
                some.append(several[-1])
            continue
        if None in verdicts:
            counts["unanalyzed_padding_unproved"] += 1
            continue
        owners = [source_key(row.get("source") or "") for _rva, row in rows]
        own = bool(public["source"]) and source_key(public["source"]) in owners
        counts["kept_copy_differs"] += 1
        counts["kept_copy_differs_owner_unit" if own else "kept_copy_differs_other_unit"] += 1
        rva, row = rows[0]
        differ.append(dict(retail_rva=f"0x{rva:08X}", size=int(row["target_size"]), name=public["name"],
                           owner_source=row.get("source") or "", kept_source=public["source"],
                           kept_object=public["object"], kept_is_owner=own,
                           other_retail_rvas=" ".join(f"0x{other:08X}" for other, _row in rows[1:])))
    return dict(counts=dict(counts), names=sorted(differ, key=lambda entry: entry["retail_rva"]), several_rows=several,
                matches_only_some_rows=some, scope="report only: not in counts, defects or any gate")


def _masked(body, fields):
    """`body` with these relocation fields zeroed; every kind is in _COFF_WIDTH, the caller checks."""
    out = bytearray(body)
    for where, kind in fields:
        for at in range(where, min(where + _COFF_WIDTH[kind], len(out))):
            out[at] = 0
    return bytes(out)


def same_copy(mine, theirs, fields):
    """True when the two copies are the same code, False when they are not, None when that cannot be shown.
    Bytes past the shorter one's end count as padding only if they are all CC or 90 and nothing can run them:
    stripping them blindly would make the short jumps EB 90 and EB CC equal, and a copy that is only the start of a
    longer row must not pass."""
    a, b = _masked(mine, fields), _masked(theirs, fields)
    shorter, longer = sorted((a, b), key=len)
    if longer[:len(shorter)] != shorter or longer[len(shorter):].strip(b"\xcc\x90"):
        return False
    if len(a) == len(b):
        return True
    return True if tail_cannot_run(shorter, len(longer), fields) else None


def tail_cannot_run(body, end, fields):
    """Whether the bytes from len(body) up to `end` cannot execute: `body` decodes to its last byte and ends in an
    unconditional transfer, and no direct branch in it lands there. A branch with a relocation in its operand goes
    elsewhere: masked to zero, it would only seem to land on the next byte."""
    import capstone
    relocated = {at for where, kind in fields for at in range(where, where + _COFF_WIDTH[kind])}
    reached, last = 0, None
    for address, size, mnemonic, operands in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm_lite(body, 0):
        reached, last = address + size, mnemonic
        if (mnemonic == "call" or mnemonic.startswith(("j", "loop"))) and re.fullmatch(r"0x[0-9a-f]+|[0-9]+", operands) \
                and not relocated.intersection(range(address, reached)) and len(body) <= int(operands, 0) < end:
            return False
    return reached == len(body) and last in ("ret", "retf", "jmp", "ljmp")


def ledger_identity(root, image_commit):
    """Which functions.csv the check read, and whether it is the image's own. A newer ledger read against an older
    image names copies that are no fault of the image's, so a difference is said plainly; it changes nothing else."""
    path = Path(root) / "reverse/functions.csv"
    sha = digest(path)

    def git(*args):
        done = subprocess.run(["git", *args], cwd=root, capture_output=True)
        return done.stdout if done.returncode == 0 else None

    revision = git("rev-parse", "HEAD")
    theirs = git("show", f"{image_commit}:reverse/functions.csv") if image_commit else None
    same = None if theirs is None else hashlib.sha256(theirs).hexdigest() == sha
    warning = None
    if same is False:
        warning = (f"reverse/functions.csv here is not image commit {image_commit}'s: kept copies are judged against the wrong rows, "
                   "so some names listed may be no fault of the image. Use a checkout of that commit")
    elif same is None:
        warning = (f"could not read reverse/functions.csv at image commit {image_commit}: nothing shows this ledger is the image's, "
                   "so some names listed may be no fault of the image")
    return dict(sha256=sha, revision=revision.decode().strip() if revision else None, image_commit=image_commit,
                same_as_image=same, warning=warning)


def write_kept_copies(out, kept):
    with (out / "kept_copies_some_rows.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["name", "retail_rvas", "verdicts", "kept_source"], delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(dict(entry, retail_rvas=" ".join(entry["retail_rvas"]), verdicts=" ".join(map(str, entry["verdicts"])))
                         for entry in kept["matches_only_some_rows"])
    with (out / "kept_copies.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["retail_rva", "size", "name", "owner_source", "kept_source", "kept_object",
                                               "kept_is_owner", "other_retail_rvas"], delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(kept["names"])


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
        self.pointer_words = []
        self.vtable_slots = []
        self.by_name = collections.defaultdict(list)
        self.by_image = collections.defaultdict(list)
        self.literal_widths = collections.defaultdict(set)
        self.literal_cache = {}
        self.retail_literals = {}
        self.ledger_literal_cache = {}
        self.statics = {}                      # place_statics: data the MAP does not list
        self.unplaced = set()                  # place_statics: such data an object defines but nothing places
        self.inventory_failed = []             # place_statics: objects it could not read (their names unknown)
        for p in publics:
            literal = re.match(r"\?\?_C@_([01])", p["name"])
            if literal:
                self.literal_widths[p["rva"]].add(2 if literal[1] == "1" else 1)
            self.by_name[p["name"]].append(p)
            self.by_image[p["rva"]].append(p)
        self.by_retail = collections.defaultdict(list)
        for p in publics:
            for target in self.mapping.targets_for(p):
                self.by_retail[target].append(p)
        self.retail_addresses = sorted(self.by_retail)
        self.end_targets = collections.defaultdict(set)
        for p in publics:
            targets = self.mapping.targets_for(p)
            if (p["extent"] and len(targets) == 1 and
                    not ours.in_text(ours.base + p["rva"]) and
                    self.mapping.resolve(p["rva"]) == next(iter(targets))):
                self.end_targets[p["rva"] + p["extent"]].add(next(iter(targets)) + p["extent"])

    def defect(self, family, rva, p, evidence):
        self.counts[family] += 1
        self.defects.append(dict(family=family, retail_rva=hex(rva) if rva is not None else "",
                                 name=p.get("name", ""), object=p.get("object", ""),
                                 source=p.get("source", ""), evidence=evidence))

    def winner(self, names, retail_rva=None):
        found = [p for n in names for p in self.by_name.get(n, [])
                 if retail_rva is None or retail_rva in self.mapping.targets_for(p)]
        locations = {p["rva"] for p in found}
        if len(locations) == 1:
            return max(found, key=lambda p: p["extent"] or 0)
        return None

    def static_winner(self, names, row):
        """The one placement (place_statics) of the row's names, the row's source selecting among copies several
        objects define (a header `static` gives each including unit its own); None when not exactly one."""
        found = [p for n in names for p in self.statics.get(n, ())]
        if row.get("source"):
            found = [p for p in found if source_key(p["source"]) == source_key(row["source"])]
        locations = {p["rva"] for p in found}
        return found[0] if len(locations) == 1 else None

    def pooled_copies(self, names, rva, size):
        """False when an image copy of a pooled constant the row names (??_C@, __real@, __xmm@) differs from
        retail's value over that name's own length; True when every copy was compared and holds it; None when no
        copy differs but one cannot be told (an unknown value, or a copy whose own extent cannot hold it)."""
        equal, untold = 0, False
        for n in sorted(n for n in names if POOLED.match(n)):
            copies = self.by_name.get(n, [])
            if not copies:
                continue
            length = pooled_length(n, self.retail, rva, size)
            expected = self.retail.read(rva, length) if length else None
            for p in sorted(copies, key=lambda p: p["rva"]):
                if expected is None or p["extent"] is None or p["extent"] < length:
                    untold = True          # a copy whose own extent cannot hold the whole value proves nothing
                elif self.ours.read(p["rva"], length) != expected:
                    return False
                else:
                    equal += 1
        return None if untold or not equal else True

    def end_pointer(self, actual, expected):
        targets = self.end_targets.get(actual - self.ours.base, set())
        if expected - self.retail.base in targets:
            return "equal" if len(targets) == 1 else "unchecked"
        return None

    def pointer(self, actual, expected, *, proven=False, allow_end=True, end_proof=False):
        return self.pointer_result(actual, expected, proven=proven, allow_end=allow_end, end_proof=end_proof)[0]

    def pointer_result(self, actual, expected, *, proven=False, allow_end=True, end_proof=False):
        if actual == expected == 0:
            return "equal", "mapped target identity"
        a, b = actual - self.ours.base, expected - self.retail.base
        got = self.mapping.resolve(a, b)
        # Decide ordinary correspondence before considering any end inference.
        if proven and self.by_retail.get(b) and (actual == 0 or self.ours.read(a, 1) is None):
            result, reason = "wrong", "pointer outside linked image"
        elif got == b:
            return "equal", "mapped target identity"
        elif got is None:
            if self.ledger_literal(a, b):
                self.counts["pointers_ledger_literal_aliases"] += 1
                return "equal", "bounded pooled literal equivalence"
            result, reason = "unchecked", "target correspondence unresolved"
        else:
            if self.literal_alias(a, got, b):
                self.counts["pointers_literal_aliases"] += 1
                return "equal", "bounded pooled literal equivalence"
            result, reason = "wrong", "mapped target mismatch"
        end = self.end_pointer(actual, expected) if allow_end else None
        if end is not None:
            conflict = any(self.mapping.targets_for(p) != {b}
                           for p in self.by_image.get(a, ())) or any(
                           p["rva"] != a for p in self.by_retail.get(b, ()))
            if conflict:
                self.counts["pointers_end_unchecked"] += 1
                return "unchecked", "end-pointer-conflict"
            if result == "unchecked":
                if end == "equal" and end_proof:
                    self.counts["pointers_end_equal"] += 1
                    return "equal", "proven-end-pointer"
                self.counts["pointers_end_unchecked"] += 1
                return "unchecked", "end-pointer-unproven" if not end_proof else "end-pointer-ambiguous"
        return result, reason

    def data_end_proof(self, public, offset, actual, expected):
        """A winning DIR32 field must name the array and encode its exact extent."""
        coff = public.get("data_coff") or public.get("coff")
        if not coff:
            return False
        section, field = coff["section"], coff["offset"] + offset
        target = section.get("relocation_targets", {}).get(field)
        if not target or field < 0 or field + 4 > len(section["body"]):
            return False
        owners = self.by_name.get(target["name"], [])
        if len({p["rva"] for p in owners}) != 1:
            return False
        addend = struct.unpack_from("<I", section["body"], field)[0]
        return any(addend == p["extent"] and addend > 0 and
                   actual == self.ours.base + p["rva"] + addend and
                   self.mapping.resolve(p["rva"]) == expected - self.retail.base - addend
                   for p in owners)

    def code_end_proof(self, row_rva, operand_rva, actual, expected):
        """Only the row's unique .text COFF DIR32 can prove a code operand's end."""
        owners = [p for p in self.by_image.get(row_rva, ()) if p.get("coff")]
        locations = {(id(p["coff"]["section"]), p["coff"]["offset"]) for p in owners}
        if len(locations) != 1:
            return False
        owner = owners[0]
        offset = operand_rva - row_rva
        if not owner["extent"] or offset < 0 or offset + 4 > owner["extent"]:
            return False
        coff = owner["coff"]
        field = coff["offset"] + offset
        if (field, link_cycle.DIR32) not in coff["section"]["relocations"]:
            return False
        return self.data_end_proof(owner, offset, actual, expected)

    def ledger_literal(self, actual, expected):
        """A MAP string literal can select a ledger-typed retail string by value.
        This is pooled string equivalence, never a general data/code alias.
        Both complete terminated values must fit their own bounded extents.
        """
        key = (actual, expected)
        if key in self.ledger_literal_cache:
            return self.ledger_literal_cache[key]
        self.ledger_literal_cache[key] = False
        typed = self.retail_literals.get(expected)
        widths = self.literal_widths.get(actual, set())
        if typed is None or len(widths) != 1:
            return False
        size, width = typed
        if widths != {width} or self.retail.in_text(self.retail.base + expected) or not self.retail.readonly(expected):
            return False
        owners = [p for p in self.by_image.get(actual, ()) if p["name"].startswith("??_C@_")]
        if not owners or any(p["extent"] is None for p in owners):
            return False
        limit = min(size, min(p["extent"] for p in owners), 4096)
        for offset in range(0, limit - width + 1, width):
            a, b = self.ours.read(actual + offset, width), self.retail.read(expected + offset, width)
            if a is None or a != b:
                return False
            if a == bytes(width) and self.retail.readonly(expected, offset + width):
                self.ledger_literal_cache[key] = True
                return True
        return False

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
        return self.code_comparison(actual, expected, size)[0]

    def code_comparison(self, actual, expected, size, *, partial=False, row_size=None):
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
            return None, "code-equal-unreadable"
        # The first opcode byte is never an address operand. It can prove a
        # mismatch even when a short extent truncates the first instruction.
        if partial and a and b and a[0] != b[0]:
            return False, "body-mismatch"
        aa, bb = list(md.disasm(a, actual)), list(md.disasm(b, expected))
        complete = bool(aa and bb) and sum(i.size for i in aa) == size and sum(i.size for i in bb) == size
        if sum(i.size for i in aa) != sum(i.size for i in bb):
            return False, "body-mismatch"
        if complete and len(aa) != len(bb):
            return False, "body-mismatch"
        unresolved = None
        for x, y in zip(aa, bb):
            if x.id != y.id or x.size != y.size or len(x.operands) != len(y.operands):
                return False, "body-mismatch"
            masked = set()
            for xo, yo in zip(x.operands, y.operands):
                if xo.type != yo.type:
                    return False, "body-mismatch"
                if xo.type == X86_OP_IMM and (x.group(capstone.CS_GRP_JUMP) or x.group(capstone.CS_GRP_CALL)):
                    # capstone reports RVA for relative branches.
                    want = yo.imm
                    got = self.mapping.resolve(xo.imm, want)
                    if actual <= xo.imm < actual + (row_size or size):
                        got = expected + xo.imm - actual
                    if got is None:
                        unresolved = unresolved or "code-equal-unresolved-operand"
                    elif got != want:
                        return False, "body-mismatch"
                    masked.update(range(x.imm_offset, x.imm_offset + x.imm_size))
                elif xo.type == X86_OP_IMM and x.address + x.imm_offset in self.ours.relocations:
                    # A named storage operand is not proof of an array bound.
                    verdict = self.pointer(xo.imm & 0xffffffff, yo.imm & 0xffffffff,
                        allow_end=not self.by_retail.get((yo.imm & 0xffffffff) - self.retail.base),
                        end_proof=self.code_end_proof(actual, x.address + x.imm_offset,
                            xo.imm & 0xffffffff, yo.imm & 0xffffffff))
                    if verdict == "unchecked":
                        unresolved = unresolved or "code-equal-unresolved-operand"
                    if verdict == "wrong":
                        return False, "body-mismatch"
                    masked.update(range(x.imm_offset, x.imm_offset + x.imm_size))
                elif xo.type == X86_OP_MEM and x.address + x.disp_offset in self.ours.relocations:
                    verdict = self.pointer(xo.mem.disp & 0xffffffff, yo.mem.disp & 0xffffffff,
                        allow_end=not self.by_retail.get((yo.mem.disp & 0xffffffff) - self.retail.base),
                        end_proof=self.code_end_proof(actual, x.address + x.disp_offset,
                            xo.mem.disp & 0xffffffff, yo.mem.disp & 0xffffffff))
                    if verdict == "unchecked":
                        unresolved = unresolved or "code-equal-unresolved-operand"
                    if verdict == "wrong":
                        return False, "body-mismatch"
                    masked.update(range(x.disp_offset, x.disp_offset + x.disp_size))
            if any(x.bytes[k] != y.bytes[k] for k in range(x.size) if k not in masked):
                return False, "body-mismatch"
        if not complete:
            unresolved = unresolved or "code-equal-decode-incomplete"
        if unresolved:
            return None, unresolved
        return True, "row-identity-and-abi-equal"

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
        if not self.ours.in_text(actual):
            return False, "non-text-target"
        a, b = actual - self.ours.base, expected - self.retail.base
        af, bf = self.forwarder(self.ours, a), self.forwarder(self.retail, b)
        if af or bf:
            at, adjust_a = af if af else (a, 0)
            bt, adjust_b = bf if bf else (b, 0)
            mapped = self.mapping.resolve(at, bt)
            if mapped is None:
                return None, "forwarder-unmapped"
            if mapped != bt:
                return False, "forwarder-target-mismatch"
            if adjust_a != adjust_b:
                return False, "this-adjustment-mismatch"
            a, b = at, bt
        mapped = self.mapping.resolve(a, b)
        if mapped is None:
            return None, "unmapped"
        if mapped != b:
            return False, "target-mismatch"
        size = sizes.get(b)
        if not size:
            return None, "retail-extent-missing"
        owners = self.by_image.get(a, ())
        extents = {p["extent"] for p in owners if p["extent"] is not None}
        # Extents limit positive credit, never suppress an observable mismatch.
        limit = min(size, min(extents)) if extents else size
        result, reason = self.code_comparison(a, b, limit, partial=True, row_size=size)
        if result is not True:
            return result, reason
        if not extents:
            return None, "extent-missing"
        if limit < size:
            return None, "extent-short"
        return result, reason

    def ledger(self, rows, sizes):
        self.retail_literals = {int(r["address"], 16): (int(r["size"] or 0), 2 if r["kind"] == "wstring" else 1)
                                for r in rows if r["kind"] in ("string", "wstring")}
        self.ledger_literal_cache.clear()
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
            owners = names                                  # the names whose storage the winner path checks
            if any(POOLED.match(n) and self.by_name.get(n) for n in names):
                # every image copy of a pooled constant, not only one a winner qualifies; equality of the pooled
                # value never discharges a named global sharing the address (the winner path below checks its
                # own storage over the row's size)
                named = any(not POOLED.match(n) and (self.by_name.get(n) or self.statics.get(n) or n in self.unplaced)
                            for n in names)
                pooled = self.pooled_copies(names, rva, size)
                compared = kind + "_compared" if kind in ("string", "wstring", "float") else "globals_compared"
                if pooled is False:
                    self.counts["pooled_constant_rows_compared"] += 1
                    self.counts[compared] += 1
                    self.defect("pooled_constant_contents", rva, row, "an image copy of the pooled constant "
                                "differs from retail's value")
                    continue
                if pooled is None:
                    self.counts["pooled_constant_copies_unanalyzed"] += 1
                else:
                    self.counts["pooled_constant_rows_compared"] += 1
                    if not named and self.inventory_failed and any(not POOLED.match(n) for n in names):
                        # an unread object may define the row's own storage: no pooled-only credit
                        self.counts["pooled_named_inventory_unknown"] += 1
                        self.counts[kind + "_unanalyzed"] += 1
                        continue
                    if not named:
                        self.counts[compared] += 1
                        continue
                if named:
                    # the row's own storage is located through its own names, whatever the pooled copies showed
                    owners = {n for n in names if not POOLED.match(n)}
            p = self.winner(owners, rva)
            retail = self.retail.read(rva, size)
            split = False
            if p is None and not any(self.by_name.get(n) for n in owners):
                p = self.static_winner(owners, row)         # internal-linkage data the MAP does not list
                if p is not None:
                    self.counts["static_data_placed"] += 1
            elif p is not None and any(self.statics.get(n) for n in owners):
                p, split = None, True  # storage at a MAP location and at a placed static: which is retail's is untold
                self.counts["split_storage_rows"] += 1
            if p is None:
                family = "mapping_ambiguous" if any(self.by_name.get(n) for n in owners) else "no_object_retail_nonzero"
                if retail and any(retail) or family == "mapping_ambiguous":
                    self.defect(family, rva, row, "Split storage: one retail address, a MAP-listed global and a "
                                "placed static in our image" if split else
                                "No unique linked MAP location for ledger names")
                else:
                    self.counts["absent_zero_globals_unanalyzed"] += 1
                continue
            if row["kind"] == "vtable":
                if size < 4 or size % 4:
                    self.counts["vtable_retail_extent_unanalyzed"] += 1
                words = image_report.Retail.vtable_words(self.retail, rva, size)
                self.counts["vtable_slots_expected"] += words
                if p["extent"] is None:
                    self.counts["vtable_extent_unanalyzed"] += 1
                elif p["extent"] < words * 4:
                    self.defect("vtable_short", rva, p, f"Winning extent {p['extent']} < retail code-pointer run {words * 4}; run is bounded by ledger extent")
                for offset in range(0, words * 4, 4):
                    a, b = self.ours.read(p["rva"] + offset, 4), self.retail.read(rva + offset, 4)
                    if a is None or b is None or p["extent"] is None or offset + 4 > p["extent"]:
                        reason = ("table-unreadable" if a is None or b is None else
                                  "table-extent-missing" if p["extent"] is None else "table-extent-short")
                        self.counts["vtable_slots_unanalyzed"] += 1
                        self.vtable_slots.append(dict(name=p["name"], retail_rva=hex(rva + offset),
                            image_rva=hex(p["rva"] + offset), verdict="unanalyzed", reason=reason))
                        continue
                    result, reason = self.slot(struct.unpack("<I", a)[0], struct.unpack("<I", b)[0], sizes)
                    self.counts["vtable_slots_" + ("equal" if result is True else "wrong" if result is False else "unanalyzed")] += 1
                    self.vtable_slots.append(dict(name=p["name"], retail_rva=hex(rva + offset),
                        image_rva=hex(p["rva"] + offset), actual=hex(struct.unpack("<I", a)[0]),
                        expected=hex(struct.unpack("<I", b)[0]),
                        verdict="equal" if result is True else "wrong" if result is False else "unanalyzed",
                        reason=reason))
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
            coff = p.get("data_coff") or p.get("coff")
            fields = set()
            if coff:
                fields = {at - coff["offset"] for at, kind in coff["section"]["relocations"]
                          if kind == link_cycle.DIR32 and 0 <= at - coff["offset"] <= size - 4}
            for offset in range(size - 3):
                ar, br = p["rva"] + offset, rva + offset
                if ar not in self.ours.relocations and br not in self.retail.relocations and offset not in fields:
                    continue
                masked.update(range(offset, offset + 4))
                actual, expected = struct.unpack_from("<I", ours, offset)[0], struct.unpack_from("<I", retail, offset)[0]
                result, reason = self.pointer_result(actual, expected, proven=True,
                    end_proof=offset in fields and self.data_end_proof(p, offset, actual, expected))
                self.pointer_words.append(dict(name=p["name"], retail_rva=hex(br), image_rva=hex(ar),
                    actual=hex(actual), expected=hex(expected), verdict=result,
                    evidence="COFF DIR32" if offset in fields else "PE HIGHLOW",
                    reason=reason))
                if offset in fields and ar not in self.ours.relocations and br not in self.retail.relocations:
                    self.counts["coff_pointer_words_checked"] += 1
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
                    actual = struct.unpack_from("<I", ours, offset)[0]
                    candidate = self.mapping.resolve(actual - self.ours.base, value - self.retail.base)
                    self.pointer_words.append(dict(name=p["name"], retail_rva=hex(rva + offset),
                        image_rva=hex(p["rva"] + offset), actual=hex(actual), expected=hex(value),
                        verdict="unchecked", evidence="untyped aligned word",
                        candidate_correspondence=("unchecked" if candidate is None else
                            "equal" if candidate == value - self.retail.base else "wrong"),
                        reason="image-range value alone does not prove pointer type; raw bytes still compared"))
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
                    defects=self.defects, pointer_words=self.pointer_words, vtable_slots=self.vtable_slots,
                    defect_attribution_missing=dict(
                        object=sum(not d["object"] for d in self.defects),
                        source=sum(not d["source"] for d in self.defects)) ,
                    limitations=["Static tables do not prove initializer execution.",
                                 "Retail data extents and vtable runs are ledger-bounded, not recovered layouts.",
                                 "Unknown pointer correspondence fails analysis; no shape-only alias credit.",
                                 "Unmapped MAP string literals receive pooled-value credit only against ledger-typed retail strings, with both full terminated values bounded by their own extents.",
                                 "Global pointer fields require PE HIGHLOW or winning COFF DIR32 evidence; untyped candidates stay unchecked and unmasked.",
                                 "Vtable slot equality requires complete table and target-code extents; equal length alone earns no credit.",
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


# COFF field widths, not PE fixups: internal REL32 fields can need no PE relocation.
_COFF_WIDTH = {6: 4, 7: 4, 10: 2, 11: 4, 12: 4, 20: 4}


def retail_code_blocks(md, body, address):
    """Decode reachable basic blocks, not embedded switch-table data.
    Indirect successors are not guessed. Unvisited bytes remain explicitly
    unanalyzed (they may be code, tables or padding).
    """
    import capstone
    from capstone.x86_const import X86_OP_IMM
    decoded, occupied, pending = {}, {}, [address]
    indirect = 0
    while pending:
        start = pending.pop()
        if start in decoded or not address <= start < address + len(body):
            continue
        for ins in md.disasm(body[start - address:], start):
            if ins.address in decoded:
                break
            if any(at in occupied for at in range(ins.address, ins.address + ins.size)):
                return None, len(body), indirect
            decoded[ins.address] = ins
            occupied.update((at, ins.address) for at in range(ins.address, ins.address + ins.size))
            if ins.group(capstone.CS_GRP_RET) or ins.mnemonic in ("int3", "ud2", "hlt"):  # CS_GRP_RET
                break
            if ins.group(capstone.CS_GRP_JUMP):  # calls retain fallthrough
                if ins.operands and ins.operands[0].type == X86_OP_IMM:
                    pending.append(ins.operands[0].imm)
                else:
                    indirect += 1
                if ins.mnemonic in ("jmp", "ljmp"):
                    break
    return [decoded[a] for a in sorted(decoded)], len(body) - len(occupied), indirect


def numeric_operand_use(md, instructions, origin, operand_kind):
    """Conservative local numeric witness; unknown call/branch uses do not qualify.
    Memory displacements always have address syntax, even in CMP/ADD instructions.
    """
    import capstone
    from capstone.x86_const import X86_OP_REG, X86_OP_MEM
    if operand_kind != "immediate":
        return False
    ins = instructions[origin]
    arithmetic = {"and", "or", "xor", "test", "shl", "shr"}
    if ins.mnemonic in arithmetic:
        return True
    if not ins.operands or ins.operands[0].type != X86_OP_REG:
        return False
    if ins.mnemonic not in arithmetic | {"mov"}:
        return False

    def root(reg):
        name = md.reg_name(reg)
        aliases = {"al": "ax", "ah": "ax", "eax": "ax", "bl": "bx", "bh": "bx",
                   "ebx": "bx", "cl": "cx", "ch": "cx", "ecx": "cx",
                   "dl": "dx", "dh": "dx", "edx": "dx"}
        return aliases.get(name, name.removeprefix("e") if name in ("esi", "edi", "ebp", "esp") else name)

    tracked = {root(ins.operands[0].reg)}
    numeric = ins.mnemonic in arithmetic
    for following in instructions[origin + 1:]:
        if following.group(capstone.CS_GRP_RET):  # return: arithmetic result is ambiguous, not pointer proof
            return numeric
        if following.group(capstone.CS_GRP_JUMP) or following.group(capstone.CS_GRP_CALL):  # jumps/calls: not a local proof
            return False
        for op in following.operands:
            if op.type == X86_OP_MEM and ({root(op.mem.base), root(op.mem.index)} & tracked):
                return False
        reads, writes = following.regs_access()
        read = {root(r) for r in reads} & tracked
        if read:
            if following.mnemonic in arithmetic:
                numeric = True
            elif following.mnemonic == "mov" and following.operands[0].type == X86_OP_REG:
                tracked.add(root(following.operands[0].reg))
            else:
                return False
        for reg in writes:
            name = root(reg)
            if name in tracked and not read:
                tracked.remove(name)
        if not tracked:
            return numeric
    return numeric



def address_operand_use(md, instructions, origin, operand_kind):
    """Direct local dereference/indirect-call evidence; unknown escapes stay unknown."""
    import capstone
    from capstone.x86_const import X86_OP_REG, X86_OP_MEM
    if operand_kind == "displacement":
        memory = next((op for op in instructions[origin].operands if op.type == X86_OP_MEM), None)
        return memory is not None and not memory.mem.base
    ins = instructions[origin]
    if ins.mnemonic != "mov" or not ins.operands or ins.operands[0].type != X86_OP_REG:
        return False
    tracked = {ins.operands[0].reg}
    for following in instructions[origin + 1:]:
        for op in following.operands:
            if op.type == X86_OP_MEM and ({op.mem.base, op.mem.index} & tracked):
                return True
        if following.group(capstone.CS_GRP_CALL) or following.group(capstone.CS_GRP_JUMP):
            return bool(following.operands and following.operands[0].type == X86_OP_REG
                        and following.operands[0].reg in tracked)
        if following.group(capstone.CS_GRP_RET):
            return False
        reads, writes = following.regs_access()
        if following.mnemonic == "mov" and following.operands[0].type == X86_OP_REG and set(reads) & tracked:
            tracked.add(following.operands[0].reg)
        elif not set(reads) & tracked:
            tracked.difference_update(writes)
        if not tracked:
            return False
    return False


def first_pointer_argument_call(instructions, origin):
    """Only a literal last PUSH before a direct call; no stack/control guessing.
    The callee's restricted MSVC signature is checked after ledger resolution.
    """
    import capstone
    from capstone.x86_const import X86_OP_IMM, X86_OP_REG, X86_REG_ESP
    ins = instructions[origin]
    if ins.mnemonic != "push" or ins.operands[0].type != X86_OP_IMM:
        return None
    for following in instructions[origin + 1:origin + 9]:
        if following.group(capstone.CS_GRP_CALL):
            if following.operands[0].type == X86_OP_IMM:
                return following.operands[0].imm
            return None
        if (following.mnemonic not in ("mov", "lea", "nop")
                or (following.mnemonic != "nop" and following.operands[0].type != X86_OP_REG)
                or X86_REG_ESP in following.regs_access()[1]):
            return None
    return None


# A global's decorated type: `@@3` (or `@@2`, a static member) then its type. MSVC spells an array like a pointer to
# its element ([PQRS][A-D]); only a sizeof proven larger than a pointer (reverse/data_rows.csv: the compiler's sizeof
# in a probe of the defining unit) tells an array from a pointer variable -- an extent to the next symbol may be
# padding.
SCALAR_ARRAY = re.compile(r"@@[23][PQRS][A-D](C|D|E|F|G|H|I|J|K|M|N|O|_J|_K|_N|_W)[A-D]$")
STRUCT_ARRAY = re.compile(r"@@[23][PQRS][A-D][UV]\w")


def word_container(symbol, proven, offset):
    """'nonpointer' when the data symbol holding a word at `offset` cannot hold a pointer there (inside a string
    literal's encoded length; inside an array of integral or floating elements), 'struct' inside an array of
    structs (its fields are not known), else None. `symbol` is a public-shaped dict; `proven` maps a data symbol and
    its defining source to its proven sizeof (reverse/data_rows.csv): without one larger than a pointer, an element-typed name may be a
    pointer variable, and nothing is said; a word past the proven payload is outside the container."""
    name = symbol["name"]
    if name.startswith("??_C@"):
        length = literal_length(name)                 # and only where this copy's own extent holds all of it
        held = length and symbol.get("extent") and length <= symbol["extent"]
        return "nonpointer" if held and offset + 4 <= length else None
    size = proven.get((name, source_key(symbol.get("source") or ""))) if symbol.get("source") else None
    size = size or 0
    if size <= 4 or offset + 4 > size:
        return None
    if SCALAR_ARRAY.search(name):
        return "nonpointer"
    if STRUCT_ARRAY.search(name):
        return "struct"
    return None


def proven_sizes(path):
    """{(name, source): sizeof} of the matched rows of reverse/data_rows.csv at `path` (sizes the build proves for
    the symbol its source defines; internal symbols of one name are not one object); a pair proven two ways is
    left out. {} when absent."""
    path = Path(path)
    if not path.exists():
        return {}
    found = collections.defaultdict(set)
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r.get("status") == "matched" and (r.get("size") or "").isdigit() and r.get("source"):
                found[(r["name"], source_key(r["source"]))].add(int(r["size"]))
    return {key: next(iter(sizes)) for key, sizes in found.items() if len(sizes) == 1}


def data_address_words(checker, limit, counts, proven=None):
    """Raw aligned words in .data/.rdata, independent of MAP/COFF coverage.
    Virtual zero-fill, other sections and PE import/export directory extents
    are explicitly outside this scan. Known terminated strings/floats are
    counted separately, never decoded as pointer words.
    """
    ours, retail = checker.ours, checker.retail
    by_start = collections.defaultdict(list)
    for p in checker.publics:
        by_start[p["rva"]].append(p)
    starts = sorted(by_start)
    # internal-linkage data the MAP does not list, placed through its own object (place_statics)
    placed = sorted((p["rva"], p["rva"] + p["extent"], id(p), p) for found in checker.statics.values() for p in found
                    if p.get("extent"))
    placed_starts = [start for start, _end, _id, _p in placed]
    excluded = []
    pe = getattr(ours, "pe", None)
    directories = getattr(getattr(pe, "OPTIONAL_HEADER", None), "DATA_DIRECTORY", [])
    for index in (0, 1, 12):  # export, import descriptors, IAT
        if index < len(directories):
            d = directories[index]
            if d.VirtualAddress and d.Size:
                excluded.append((d.VirtualAddress, d.VirtualAddress + d.Size))
    counts["data_pe_directory_extents_excluded"] = len(excluded)
    for descriptor in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        length = 4 * (len(descriptor.imports) + 1)
        for start in (descriptor.struct.OriginalFirstThunk, descriptor.struct.FirstThunk):
            if start:
                excluded.append((start, start + length))
        excluded.append((descriptor.struct.Name, descriptor.struct.Name + len(descriptor.dll) + 1))
        for entry in descriptor.imports:
            start = getattr(entry, "hint_name_table_rva", None)
            if start is not None and entry.name is not None:
                excluded.append((start, start + 2 + len(entry.name) + 1))
    counts["data_import_structure_extents_excluded"] = len(excluded) - counts["data_pe_directory_extents_excluded"]
    # The import directory size bounds descriptors, NOT lookup/name tables.
    # Merge the parsed graph's extents so a word costs one binary search.
    merged = []
    for start, end in sorted(excluded):
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(end, merged[-1][1]))
        else:
            merged.append((start, end))
    exclusion_starts = [start for start, _end in merged]
    sections = []
    result = []
    for sec in getattr(ours, "sections", []):
        name = sec.Name.rstrip(b"\0").decode(errors="replace")
        if name not in (".data", ".rdata"):
            continue
        counts["data_sections_scanned"] += 1
        size = sec.SizeOfRawData
        counts["data_raw_bytes_scanned"] += size
        counts["data_virtual_zerofill_bytes_not_scanned"] += max(0, sec.Misc_VirtualSize - size)
        raw = ours.read(sec.VirtualAddress, size)
        if raw is None:
            counts["data_raw_bytes_unavailable"] += size
            continue
        sections.append(dict(name=name, rva=hex(sec.VirtualAddress), raw_bytes=size,
                             virtual_bytes=sec.Misc_VirtualSize))
        for offset in range((-sec.VirtualAddress) % 4, len(raw) - 3, 4):
            image_rva = sec.VirtualAddress + offset
            counts["data_aligned_words_considered"] += 1
            exclusion = bisect.bisect_right(exclusion_starts, image_rva + 3) - 1
            if exclusion >= 0 and merged[exclusion][1] > image_rva:
                counts["data_directory_words_excluded"] += 1
                continue
            if any(at in ours.relocations for at in range(image_rva - 3, image_rva + 4)):
                counts["data_words_with_image_relocation"] += 1
                continue
            value = struct.unpack_from("<I", raw, offset)[0]
            if not retail.base <= value < limit:
                continue
            counts["data_unrelocated_image_range_words"] += 1
            index = bisect.bisect_right(starts, image_rva) - 1
            choices = [] if index < 0 else [p for p in by_start[starts[index]]
                if p.get("extent") and image_rva + 4 <= p["rva"] + p["extent"]]
            # Attribution requires agreement; a nearest symbol alone is no extent proof.
            identities = {(p["rva"], p["object"], p.get("source", "")) for p in choices}
            public = choices[0] if len(identities) == 1 else None
            if not choices:
                at = bisect.bisect_right(placed_starts, image_rva)
                covering = [p for start, end, _id, p in placed[max(0, at - 16):at]
                            if start <= image_rva and image_rva + 4 <= end]
                if len({(p["rva"], p["object"]) for p in covering}) == 1:
                    public = covering[0]
                    counts["data_words_attributed_to_placed_statics"] += 1
            literal = None
            for p in choices:
                if p["name"].startswith("??_C@_"):
                    end = literal_length(p["name"]) or 0          # the payload its name encodes, no further
                    if end > (p["extent"] or 0):
                        end = 0
                elif re.fullmatch(r"__real@(?:[0-9a-fA-F]{8}|[0-9a-fA-F]{16})", p["name"]):
                    end = len(p["name"].split("@", 1)[1]) // 2
                else:
                    continue
                if image_rva + 4 <= p["rva"] + end:
                    literal = p["name"]
            if literal:
                counts["data_literal_payload_candidates_excluded"] += 1
                continue
            container = word_container(public, proven or {}, image_rva - public["rva"]) if public else None
            if container == "nonpointer":
                counts["data_words_in_nonpointer_containers_excluded"] += 1
                continue
            target_rva = value - retail.base
            target_section = next((s.Name.rstrip(b"\0").decode(errors="replace") for s in retail.sections
                if s.VirtualAddress <= target_rva < s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData)), "none")
            mapped = checker.mapping.resolve(public["rva"]) if public else None
            detail = dict(origin="data", family="unrelocated_retail_address", row=public["name"] if public else "",
                symbol=public["name"] if public else "", source=public.get("source", "") if public else "",
                object=public["object"] if public else "", row_rva=hex(mapped) if mapped is not None else None,
                image_rva=hex(image_rva), source_section=name,
                offset=image_rva - public["rva"] if public else None, operand_kind="aligned_data_word",
                retail_address=hex(value), target_rva=hex(target_rva), target_section=target_section,
                target_kind=target_section.removeprefix(".") if target_section in (".data", ".rdata", ".text") else "other")
            if public is None:
                counts["data_candidate_attribution_unresolved"] += 1
            if container == "struct":
                detail["container"] = "struct array; non-pointer fields unproven"
            result.append(detail)
    return result, sections


def unrelocated_retail_addresses(checker, function_ledger, data_rows):
    """Audit matched, MAP-selected row copies against their exact COFF operands.
    Ambiguity is reported, never passed. Neither a raw image-range integer nor
    absence of a retail PE relocation alone is proof of an address.
    """
    import capstone
    from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    retail, ours = checker.retail, checker.ours
    limit = retail.base + max(s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData)
                              for s in retail.sections)
    counts = collections.Counter()
    numeric_data = collections.defaultdict(list)
    # Only typed non-pointer payloads qualify. Untyped global words and pointer
    # tables do NOT become numeric witnesses just because retail has no fixups.
    for row in data_rows:
        if row["kind"] not in ("float", "string", "wstring"):
            continue
        size = int(row["size"] or 0)
        if row["kind"] == "float":
            literal = re.fullmatch(r"__real@([0-9a-fA-F]{8}|[0-9a-fA-F]{16})", row["name"])
            payload = len(literal[1]) // 2 if literal else size if size in (4, 8) else 0
            if not payload or payload > size:
                counts["numeric_payload_extent_unanalyzed"] += 1
                continue
            size = payload
        raw = retail.read(int(row["address"], 16), size) if size else None
        if raw is None:
            continue
        if row["kind"] in ("string", "wstring"):
            width = 2 if row["kind"] == "wstring" else 1
            end = next((at for at in range(0, len(raw) - width + 1, width)
                        if raw[at:at + width] == bytes(width)), None)
            if end is None:
                continue
            raw = raw[:end + width]
        step = 4 if row["kind"] == "float" else 1
        for at in range(0, len(raw) - 3, step):
            value = struct.unpack_from("<I", raw, at)[0]
            if retail.base <= value < limit and len(numeric_data[value]) < 3:
                numeric_data[value].append(dict(name=row["name"], rva=row["address"],
                                                kind=row["kind"], offset=at))

    findings, ambiguous = [], []
    code_names, code_sources, code_locations = (collections.defaultdict(list),
        collections.defaultdict(list), collections.defaultdict(set))
    for public in checker.publics:
        if ours.in_text(ours.base + public["rva"]):
            code_names[public["name"]].append(public)
            code_sources[(public["name"], source_key(public.get("source", "")))].append(public)
            code_locations[public["name"]].add(public["rva"])
    with Path(function_ledger).open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            if row.get("status") != "matched":
                counts["rows_not_matched"] += 1
                continue
            counts["matched_rows_considered"] += 1
            try:
                rva, size = int(row["target_rva"], 16), int(row["target_size"])
            except ValueError:
                counts["rows_bad_extent"] += 1
                continue
            symbol = build.ledger_object_symbol(row) or row["name"]
            candidates = (code_sources.get((symbol, source_key(row["source"])), [])
                          if len(code_locations.get(symbol, ())) > 1
                          else code_names.get(symbol, []))
            if len({p["rva"] for p in candidates}) != 1:
                counts["rows_map_unresolved"] += 1
                continue
            evidence = [p for p in candidates if p.get("coff")]
            if not evidence:
                counts["rows_without_unique_coff_location"] += 1
                continue
            # Multiple aliases at one MAP location must agree on section evidence.
            locations = {(id(p["coff"]["section"]), p["coff"]["offset"]) for p in evidence}
            if len(locations) != 1:
                counts["rows_coff_ambiguous"] += 1
                continue
            public = evidence[0]
            if public["object"].endswith("diagnostic_stubs.obj"):
                counts["rows_stubbed"] += 1
                continue
            section, start = public["coff"]["section"], public["coff"]["offset"]
            target = retail.read(rva, size) if size > 0 else None
            linked = ours.read(public["rva"], size) if size > 0 else None
            if target is None or linked is None or start + size > len(section["body"]):
                counts["rows_extent_unanalyzed"] += 1
                continue
            masked, relocation_fields = set(), {}
            unsupported = False
            for offset, kind in section["relocations"]:
                off = offset - start
                if not -3 <= off < size:
                    continue
                width = _COFF_WIDTH.get(kind)
                if width is None:
                    unsupported = True
                    break
                masked.update(range(max(0, off), min(size, off + width)))
                relocation_fields[off] = (kind, width)
            if unsupported:
                counts["rows_unknown_relocation_kind"] += 1
                continue
            obj = section["body"][start:start + size]
            if any(obj[k] != target[k] or linked[k] != obj[k] for k in range(size) if k not in masked):
                counts["rows_byte_evidence_differs"] += 1
                continue
            instructions, uncovered, indirect = retail_code_blocks(md, target, retail.base + rva)
            if instructions is None:
                counts["rows_decode_overlap"] += 1
                continue
            counts["rows_analyzed"] += 1
            counts["decoded_instructions"] += len(instructions)
            counts["bytes_unvisited_code_or_data"] += uncovered
            counts["rows_with_unvisited_bytes"] += bool(uncovered)
            counts["indirect_jump_successors_unanalyzed"] += indirect
            for ordinal, ins in enumerate(instructions):
                for op in ins.operands:
                    if op.type == X86_OP_IMM:
                        # Capstone expands REL8/REL32 into a target VA. That is not
                        # a literal VA encoding and can be position independent.
                        if ((ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL))
                                and ins.mnemonic not in ("ljmp", "lcall")) or ins.mnemonic == "xbegin":
                            counts["relative_control_operands_excluded"] += 1
                            continue
                        value, field, width, kind = op.imm & 0xffffffff, ins.imm_offset, ins.imm_size, "immediate"
                    elif op.type == X86_OP_MEM:
                        value, field, width, kind = op.mem.disp & 0xffffffff, ins.disp_offset, ins.disp_size, "displacement"
                    else:
                        continue
                    if not retail.base <= value < limit:
                        continue
                    counts["image_range_operands"] += 1
                    offset = ins.address - retail.base - rva + field
                    if width != 4 or not field or target[offset:offset + 4] != struct.pack("<I", value):
                        counts["operand_encoding_unanalyzed"] += 1
                        continue
                    object_relocated = offset in relocation_fields and relocation_fields[offset][1] == 4
                    if object_relocated:
                        counts["operands_with_object_relocation"] += 1
                        if public["rva"] + offset in ours.relocations:
                            counts["operands_with_object_and_image_relocation"] += 1
                            continue
                    if not object_relocated and any(at in masked for at in range(offset, offset + 4)):
                        counts["partial_operand_relocation_unanalyzed"] += 1
                        continue
                    # The linked operand must still contain the literal, rather
                    # than an independently patched/rebased replacement.
                    if not object_relocated and linked[offset:offset + 4] != struct.pack("<I", value):
                        counts["linked_operand_changed_unanalyzed"] += 1
                        continue
                    target_rva = value - retail.base
                    target_section = next((s.Name.rstrip(b"\0").decode(errors="replace") for s in retail.sections
                        if s.VirtualAddress <= target_rva < s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData)), "none")
                    detail = dict(origin="code", family="unrelocated_retail_address",
                        row=row["name"], symbol=symbol, source=row["source"],
                        object_source=public.get("source", ""), row_size=size,
                        row_rva=hex(rva), object=public["object"], image_rva=hex(public["rva"]),
                        offset=offset, instruction_offset=ins.address - retail.base - rva,
                        instruction=ins.mnemonic + " " + ins.op_str, operand_kind=kind,
                        retail_address=hex(value), target_rva=hex(target_rva), target_section=target_section,
                        target_kind=target_section.removeprefix(".") if target_section in (".data", ".rdata", ".text") else "other")
                    if object_relocated:
                        detail.update(family="missing_image_relocation", object_relocation=relocation_fields[offset][0],
                                      linked_operand=hex(struct.unpack_from("<I", linked, offset)[0]))
                        findings.append(detail)
                        counts["operands_object_relocation_missing_from_image"] += 1
                        continue
                    call = first_pointer_argument_call(instructions, ordinal)
                    if call is not None:
                        detail["first_argument_callee_rva"] = hex(call - retail.base)
                    suffix = instructions[ordinal + 1:]
                    literal_return = (kind == "immediate" and ins.mnemonic == "mov"
                        and ins.operands and md.reg_name(ins.operands[0].reg) == "eax"
                        and any(later.group(capstone.CS_GRP_RET) for later in suffix)
                        and all(later.mnemonic in ("ret", "retf", "pop", "leave", "nop") for later in suffix))
                    detail["literal_return"] = bool(literal_return)
                    detail["local_address_use"] = address_operand_use(md, instructions, ordinal, kind)
                    reason = None
                    if value in numeric_data:
                        reason = "typed_nonaddress_data_collision"
                        detail["numeric_data_witnesses"] = numeric_data[value]
                    elif kind == "displacement" and not detail["local_address_use"]:
                        reason = "base_relative_displacement_unresolved"
                    elif numeric_operand_use(md, instructions, ordinal, kind):
                        reason = "arithmetic_or_comparison_context"
                    elif literal_return and re.search(r"(?:^|[?_:])max_size(?:@|\b)", symbol):
                        reason = "capacity_accessor_numeric_interpretation"
                    elif kind == "immediate":
                        tag = value.to_bytes(4, "big").lstrip(b"\0")
                        if len(tag) >= 3 and all(32 <= byte < 127 for byte in tag):
                            reason = "printable_integer_tag_or_address"
                    if reason:
                        detail["ambiguity_reason"] = reason
                        ambiguous.append(detail)
                        counts["ambiguous_" + reason] += 1
                    else:
                        findings.append(detail)

    numeric_witnesses = {}
    for detail in ambiguous:
        if detail["ambiguity_reason"] in ("arithmetic_or_comparison_context", "capacity_accessor_numeric_interpretation"):
            numeric_witnesses.setdefault(detail["retail_address"], dict(
                row=detail["row"], row_rva=detail["row_rva"], offset=detail["offset"],
                instruction=detail["instruction"]))
    definitive = []
    for detail in findings:
        if detail["family"] == "missing_image_relocation":
            definitive.append(detail)
            continue
        reason = None
        if detail["operand_kind"] == "immediate":
            witness = numeric_witnesses.get(detail["retail_address"])
            if witness:
                reason = "numeric_interpretation_elsewhere"
                detail["numeric_use_witness"] = witness
            elif not detail["literal_return"] and not detail["local_address_use"]:
                # PUSH arguments, stored scalars and values escaping local CFG
                # have no recoverable pointer type. They block G2 as ambiguous,
                # rather than becoming claimed address defects.
                reason = "integer_or_pointer_use_unresolved"
        if reason:
            detail["ambiguity_reason"] = reason
            ambiguous.append(detail)
            counts["ambiguous_" + reason] += 1
        else:
            definitive.append(detail)
    findings = definitive

    data_candidates, data_sections = data_address_words(
        checker, limit, counts, proven_sizes(Path(function_ledger).with_name("data_rows.csv")))
    # Resolve only discovered target/callee values, streaming the code ledger.
    values = sorted({int(d["target_rva"], 16) for d in findings + ambiguous + data_candidates} |
                    {int(d["first_argument_callee_rva"], 16) for d in findings + ambiguous
                     if "first_argument_callee_rva" in d})
    owners = collections.defaultdict(list)
    def own(row, start, size, register):
        first, last = bisect.bisect_left(values, start), bisect.bisect_left(values, start + max(size, 1))
        for value in values[first:last]:
            owners[value].append(dict(register=register, kind=row.get("kind", "code"),
                name=row["name"], rva=hex(start), size=size, offset=value - start,
                source=row.get("source", ""), status=row.get("status", ""), exact=value == start))
    for row in data_rows:
        own(row, int(row["address"], 16), int(row["size"] or 0), "data_ledger")
    source_data = Path(function_ledger).with_name("data_rows.csv")
    counts["source_data_rows_available"] = int(source_data.exists())
    if source_data.exists():
        with source_data.open(newline="", encoding="utf-8") as f:
            for row in csv.DictReader(f):
                try:
                    start = int(row["address"], 16)
                    if row["address_kind"] == "va":
                        start -= retail.base
                    elif row["address_kind"] != "rva":
                        counts["source_data_rows_address_kind_unanalyzed"] += 1
                        continue
                    own(dict(row, kind="global"), start, int(row["size"] or 0), "data_rows")
                except ValueError:
                    counts["source_data_rows_extent_unanalyzed"] += 1
    with Path(function_ledger).open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            try:
                own(row, int(row["target_rva"], 16), int(row["target_size"] or 0), "functions")
            except ValueError:
                continue
    for detail in findings + ambiguous + data_candidates:
        value = int(detail["target_rva"], 16)
        detail["retail_owners"] = owners.get(value, []) or "none"
        global_rows = [r for r in owners.get(value, []) if r["kind"] == "global"]
        detail["ledger_global_exists"] = any(r["exact"] for r in global_rows)
        detail["ledger_global_extent_covers"] = bool(global_rows)
        source_globals = [r for r in global_rows if r["register"] == "data_rows" and r["status"] == "matched"]
        detail["source_global_exists"] = (any(r["exact"] for r in source_globals)
                                          if counts["source_data_rows_available"] else None)
    # Exact starts override tag/unknown-scalar heuristics, never an actual
    # bitwise/data-payload numeric witness. A CMP alone is not such a witness.
    def exact_address(detail):
        return any(r["exact"] and (r["register"] == "functions" or r["kind"] != "float")
                   for r in owners.get(int(detail["target_rva"], 16), []))
    def typed_argument(detail):
        callee = detail.get("first_argument_callee_rva")
        rows = [] if callee is None else [r for r in owners.get(int(callee, 16), [])
            if r["register"] == "functions" and r["exact"]]
        # Restricted void cdecl/thiscall signature with class/struct pointer or
        # reference FIRST argument. Unsupported signatures remain ambiguous.
        pointer = re.compile(r"^\?[^?]*@@(?:YAX|[QU][A-D]EX)(?:P[A-D][UV]|A[A-D][UV])")
        if rows and all(pointer.search(r["name"]) for r in rows):
            detail["pointer_argument_callees"] = rows
            return True
        return False
    retained = []
    numeric_reasons = {"typed_nonaddress_data_collision", "arithmetic_or_comparison_context",
                       "capacity_accessor_numeric_interpretation", "numeric_interpretation_elsewhere"}
    for detail in ambiguous:
        reason = detail["ambiguity_reason"]
        numeric = reason in numeric_reasons or detail["retail_address"] in numeric_witnesses
        if (not numeric and reason != "base_relative_displacement_unresolved"
                and (exact_address(detail) or typed_argument(detail))):
            detail["address_evidence"] = "exact_ledger_start" if exact_address(detail) else "typed_first_pointer_argument"
            counts["ambiguous_" + reason] -= 1
            detail.pop("ambiguity_reason")
            findings.append(detail)
            counts["code_exact_or_typed_address_promotions"] += 1
        else:
            retained.append(detail)
    ambiguous = retained
    for detail in data_candidates:
        if detail.get("container"):
            # an array of structs whose fields no registered layout proves: kept out of the defects, marked
            detail["ambiguity_reason"] = "struct_fields_unproven"
            ambiguous.append(detail)
            counts["ambiguous_struct_fields_unproven"] += 1
            continue
        if exact_address(detail):
            detail["address_evidence"] = "exact_ledger_start"
            findings.append(detail)
        else:
            detail["ambiguity_reason"] = "data_word_without_exact_ledger_start"
            ambiguous.append(detail)
            counts["ambiguous_data_word_without_exact_ledger_start"] += 1
    counts["defects"] = len(findings)
    counts["ambiguous"] = len(ambiguous)
    for d in findings:
        checker.defect(d["family"], int(d["row_rva"], 16) if d["row_rva"] is not None else None,
                       dict(name=d["symbol"], object=d["object"], source=d["source"]),
                       json.dumps(d, sort_keys=True, separators=(",", ":")))
    return dict(counts=dict(counts), defects=findings, ambiguous=ambiguous,
        by_kind=dict(collections.Counter(d["target_kind"] for d in findings)),
        by_origin=dict(collections.Counter(d["origin"] for d in findings)),
        by_family=dict(collections.Counter(d["family"] for d in findings)),
        by_source=dict(collections.Counter(d["source"] for d in findings)),
        ambiguous_by_kind=dict(collections.Counter(d["target_kind"] for d in ambiguous)),
        ambiguous_by_origin=dict(collections.Counter(d["origin"] for d in ambiguous)),
        ambiguous_by_source=dict(collections.Counter(d["source"] for d in ambiguous)),
        data_coverage=dict(sections=data_sections, scope="aligned raw words in .data/.rdata; virtual zero-fill, other sections, PE import/export directory extents, parsed import lookup/name tables and known terminated string/float payloads excluded"),
        rule="Matched code bytes: literal IMM32/DISP32 need COFF and image relocations. Exact ledger object/function starts and restricted typed first pointer arguments override unknown scalar/tag heuristics unless a numeric witness exists. Only bitwise/test/shift or typed numeric payload/capacity uses supply numeric witnesses; CMP is not numeric proof. Aligned data words without image relocations: exact ledger starts are defects, other range values ambiguous. Relative control operands excluded. Unknown coverage never passes G2.")


def bound_operand_form(instructions, field_address, addend, size, symbol):
    """Classify only an exactly decoded 32-bit operand, never nearby bytes."""
    from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
    if instructions is None:
        return "ambiguous", "instruction_decode_unresolved", None
    for ins in instructions:
        for op in ins.operands:
            memory = op.type == X86_OP_MEM and ins.disp_size == 4 and ins.address + ins.disp_offset == field_address
            immediate = op.type == X86_OP_IMM and ins.imm_size == 4 and ins.address + ins.imm_offset == field_address
            if not (memory or immediate):
                continue
            text = ins.mnemonic + " " + ins.op_str
            if re.fullmatch(r"___(?:rtc_[it][az][az]|(?:xc|xi|xp|xt)_[az])", symbol):
                return "lead", "crt_section_marker", text
            if memory and (op.mem.base or op.mem.index):
                return "lead", "indexed_displacement", text
            if memory and ins.mnemonic != "lea":
                return "defect", "absolute_dereference", text
            if immediate and ins.mnemonic == "add":
                return "defect", "out_of_bounds_add_base", text
            if immediate and ins.mnemonic == "cmp" and addend > size:
                return "ambiguous", "beyond_end_comparison", text
            if addend > size:
                return "defect", "address_beyond_one_past", text
            if addend == size:
                return "lead", "one_past_address", text
            return "ambiguous", "negative_address_immediate", text
    return "ambiguous", "relocation_not_a_decoded_operand", None


def relocation_bounds(checker, data_rows, function_ledger):
    """Flag DIR32/REL32 S+A outside the selected symbol's COFF upper bound.
    COFF next-symbol/section-end extents are upper bounds, not recovered C++
    sizeof values. Reaching that bound (including one-past) is a flag, not a
    claim of dereference or runtime reachability. Section-relative fixups,
    unknown targets and unresolved aliases remain unanalyzed.
    """
    counts = collections.Counter()
    names = collections.defaultdict(list)
    by_rva = collections.defaultdict(list)
    for p in checker.publics:
        names[p["name"]].append(p)
        by_rva[p["rva"]].append(p)
    starts = sorted(by_rva)
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    findings, seen, relocation_index, decoded = [], set(), {}, {}
    samples = collections.defaultdict(list)
    def unanalyzed(reason, public, field, kind, target=None):
        counts[reason] += 1
        if len(samples[reason]) < 8:
            samples[reason].append(dict(function=public["name"], source=public.get("source", ""),
                function_image_rva=hex(public["rva"]), operand_image_rva=hex(public["rva"] + field),
                relocation_kind=kind, symbol=target["name"] if target else None))
    for p in checker.publics:
        coff = p.get("coff")
        if not coff or not p.get("extent"):
            continue
        counts["code_symbols_with_coff_extent"] += 1
        sec, start = coff["section"], coff["offset"]
        end = start + p["extent"]
        targets = sec.get("relocation_targets", {})
        key = id(sec)
        if key not in relocation_index:
            ordered = sorted(sec["relocations"])
            relocation_index[key] = ([offset for offset, _kind in ordered], ordered)
        offsets, ordered = relocation_index[key]
        for offset, kind in ordered[bisect.bisect_left(offsets, start):bisect.bisect_left(offsets, end)]:
            field = offset - start
            field_rva = p["rva"] + field
            if field_rva in seen:
                continue
            seen.add(field_rva)
            counts["relocations_considered"] += 1
            if kind not in (6, 20):
                unanalyzed("unsupported_relocation_kind_unanalyzed", p, field, kind)
                continue
            target = targets.get(offset)
            if not target or target["name"].startswith(".") or target["section"] < 0:
                unanalyzed("section_absolute_or_unknown_target_unanalyzed", p, field, kind, target)
                continue
            if offset + 4 > len(sec["body"]) or offset + 4 > end:
                unanalyzed("relocation_field_extent_unanalyzed", p, field, kind, target)
                continue
            addend = struct.unpack_from("<i", sec["body"], offset)[0]
            candidates = names.get(target["name"], [])
            if target["cls"] == link_cycle.STATIC:
                candidates = [q for q in candidates if q["object"] == p["object"]]
            locations = {(q["rva"], q.get("extent")) for q in candidates}
            if len(locations) != 1:
                unanalyzed("target_map_ambiguous_or_absent", p, field, kind, target)
                continue
            symbol_rva, size = next(iter(locations))
            if not size or size < 0:
                unanalyzed("target_extent_unanalyzed", p, field, kind, target)
                continue
            linked = checker.ours.read(field_rva, 4)
            intended = (checker.ours.base + symbol_rva + addend) & 0xffffffff
            encoded = intended if kind == 6 else (intended - (checker.ours.base + field_rva + 4)) & 0xffffffff
            if linked is None or struct.unpack("<I", linked)[0] != encoded:
                unanalyzed("linked_target_resolution_differs_unanalyzed", p, field, kind, target)
                continue
            counts["relocations_analyzed"] += 1
            if 0 <= addend < size:
                counts["inside_symbol_upper_bound"] += 1
                continue
            decode_key = (p["rva"], p["extent"])
            if decode_key not in decoded:
                raw = checker.ours.read(p["rva"], p["extent"])
                decoded[decode_key] = retail_code_blocks(md, raw, checker.ours.base + p["rva"])[0] if raw else None
            classification, reason, instruction = bound_operand_form(decoded[decode_key],
                checker.ours.base + field_rva, addend, size, target["name"])
            actual_rva = intended - checker.ours.base
            index = bisect.bisect_right(starts, actual_rva) - 1
            anchor = by_rva[starts[index]] if index >= 0 else []
            image_owners = [dict(name=q["name"], source=q.get("source", ""), object=q["object"],
                rva=hex(q["rva"]), offset=actual_rva - q["rva"], size=q["extent"])
                for q in anchor if q.get("extent") and actual_rva < q["rva"] + q["extent"]]
            mapped = checker.mapping.resolve(symbol_rva)
            reference = checker.mapping.resolve(p["rva"])
            detail = dict(classification=classification, reason=reason, instruction=instruction,
                function=p["name"], function_image_rva=hex(p["rva"]),
                function_retail_rva=hex(reference) if reference is not None else None,
                source=p.get("source", ""), object=p["object"], operand_offset=field,
                operand_image_rva=hex(field_rva), relocation_kind=kind, symbol=target["name"],
                symbol_image_rva=hex(symbol_rva), addend=addend, symbol_size=size,
                extent_basis="COFF next-symbol/section-end upper bound", one_past=addend == size,
                actual_va=hex(intended), actual_rva=hex(actual_rva), actual_owners=image_owners,
                retail_symbol_rva=hex(mapped) if mapped is not None else None,
                retail_va=hex(checker.retail.base + mapped + addend) if mapped is not None else None,
                retail_rva=hex(mapped + addend) if mapped is not None else None)
            if not image_owners:
                counts["flag_actual_owner_unresolved"] += 1
            if mapped is None:
                counts["flag_retail_correspondence_unresolved"] += 1
            findings.append(detail)
    # Stream only rows owning discovered retail pointees.
    values = sorted({int(d["retail_rva"], 16) for d in findings if d["retail_rva"] is not None})
    owners = collections.defaultdict(list)
    def own(name, start, size, source, register):
        for value in values[bisect.bisect_left(values, start):bisect.bisect_left(values, start + max(size, 1))]:
            owners[value].append(dict(name=name, source=source, register=register,
                                      rva=hex(start), offset=value - start))
    for row in data_rows:
        own(row["name"], int(row["address"], 16), int(row["size"] or 0), row.get("source", ""), "data_ledger")
    with Path(function_ledger).open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            own(row["name"], int(row["target_rva"], 16), int(row["target_size"] or 0), row["source"], "functions")
    source_data = Path(function_ledger).with_name("data_rows.csv")
    counts["source_data_rows_available"] = int(source_data.exists())
    if source_data.exists():
        with source_data.open(newline="", encoding="utf-8") as f:
            for row in csv.DictReader(f):
                address = int(row["address"], 16)
                if row["address_kind"] == "va":
                    address -= checker.retail.base
                elif row["address_kind"] != "rva":
                    counts["source_data_address_kind_unanalyzed"] += 1
                    continue
                own(row["name"], address, int(row["size"] or 0), row["source"], "data_rows")
    for d in findings:
        d["retail_owners"] = owners.get(int(d["retail_rva"], 16), []) if d["retail_rva"] is not None else []
        if d["classification"] != "defect":
            continue
        checker.defect("out_of_object_pointer", int(d["function_retail_rva"], 16) if d["function_retail_rva"] is not None else None,
            dict(name=d["function"], object=d["object"], source=d["source"]), json.dumps(d, sort_keys=True))
    defects = [d for d in findings if d["classification"] == "defect"]
    leads = [d for d in findings if d["classification"] == "lead"]
    ambiguous = [d for d in findings if d["classification"] == "ambiguous"]
    counts.update(defects=len(defects), leads=len(leads), ambiguous=len(ambiguous), boundary_flags=len(findings))
    return dict(counts=dict(counts), defects=defects, leads=leads, ambiguous=ambiguous,
        unanalyzed_samples=dict(samples), sample_cap_per_reason=8,
        by_reason=dict(collections.Counter(d["reason"] for d in findings)),
        by_boundary=dict(collections.Counter("negative" if d["addend"] < 0 else
            "one_past" if d["one_past"] else "beyond_end" for d in findings)),
        by_source=dict(collections.Counter(d["source"] for d in defects)),
        leads_by_source=dict(collections.Counter(d["source"] for d in leads)),
        ambiguous_by_source=dict(collections.Counter(d["source"] for d in ambiguous)),
        limitations=["Only MAP-selected text symbols with COFF extents; data-origin relocations not scanned.",
            "Upper bounds can miss overruns into padding; in-bound is not a C++ layout proof.",
            "Leads include legal one-past/indexed/CRT idioms; no execution or reachability proof.",
            "Retail pointees use unique symbol correspondence plus addend, not instruction equivalence."])


def defined_data_pointers(checker, manifest, root):
    """Tiered, report-only evidence; confirm the MAP copy still holds the word."""
    import data_rows, reloc_ledger
    if manifest is None:
        return dict(mode="report-only",counts=dict(manifest_absent=1),findings=[])
    report=data_rows.defined_data_pointer_report(manifest,reloc_ledger.Image(checker.retail.data),root)
    counts=collections.Counter(report["counts"])
    by_name=collections.defaultdict(list)
    for p in checker.publics:
        by_name[(p["name"],source_key(p.get("source","")))].append(p)
    findings=[]
    for d in report["findings"]:
        choices=[p for p in by_name.get((d["row"],source_key(d["source"])),[]) if p["object"]==d["object"]]
        if len({p["rva"] for p in choices}) != 1:
            counts["candidate_map_copy_unresolved"]+=1
            continue
        p=choices[0]; raw=checker.ours.read(p["rva"]+d["offset"],4)
        if raw is None:
            counts["candidate_image_word_unavailable"]+=1
            continue
        value=struct.unpack("<I",raw)[0]
        d.update(image_rva=hex(p["rva"]+d["offset"]),image_value=hex(value))
        if d["reason"]!="object_relocation_to_implausible_retail_va" and value!=int(d["retail_value"],16):
            counts["candidate_image_word_changed"]+=1
            continue
        findings.append(d)
        if d["tier"]=="A":
            checker.defect("defined_data_unrelocated_pointer",int(d["retail_rva"],16),
                dict(name=d["row"],source=d["source"],object=d["object"]),json.dumps(d,sort_keys=True))
    counts["object_tier_a"]=counts["tier_a"];counts["object_tier_b"]=counts["tier_b"]
    counts["tier_a"]=sum(d["tier"]=="A" for d in findings);counts["tier_b"]=sum(d["tier"]=="B" for d in findings)
    counts["rows_tier_a"]=len({d["row"] for d in findings if d["tier"]=="A"})
    counts["rows_tier_b"]=len({d["row"] for d in findings if d["tier"]=="B"})
    counts["report_only"]=1
    report.update(counts=dict(counts),findings=findings)
    return report


def _register_family(md, reg):
    """Full 32-bit register containing reg (so a write to cl clobbers ecx)."""
    from capstone import x86_const as X
    families = {
        X.X86_REG_EAX: (X.X86_REG_AL, X.X86_REG_AH, X.X86_REG_AX, X.X86_REG_EAX),
        X.X86_REG_EBX: (X.X86_REG_BL, X.X86_REG_BH, X.X86_REG_BX, X.X86_REG_EBX),
        X.X86_REG_ECX: (X.X86_REG_CL, X.X86_REG_CH, X.X86_REG_CX, X.X86_REG_ECX),
        X.X86_REG_EDX: (X.X86_REG_DL, X.X86_REG_DH, X.X86_REG_DX, X.X86_REG_EDX),
        X.X86_REG_ESI: (X.X86_REG_SI, X.X86_REG_ESI),
        X.X86_REG_EDI: (X.X86_REG_DI, X.X86_REG_EDI),
        X.X86_REG_EBP: (X.X86_REG_BP, X.X86_REG_EBP),
        X.X86_REG_ESP: (X.X86_REG_SP, X.X86_REG_ESP),
    }
    for full, members in families.items():
        if reg in members:
            return full
    return reg


def _overwritten_in_line(md, instructions, index, memop):
    """Is store `index` provably overwritten by a later store to the same
    operand in the same straight-line run? Any branch, call or return, or any
    write to the operand's base or index register, ends the run first."""
    import capstone
    from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
    _segment, base, index_reg, _scale, _disp = memop
    watched = {_register_family(md, r) for r in (base, index_reg) if r}
    for ins in instructions[index + 1:]:
        if ins.id == 0:
            return False
        ops = ins.operands
        if (len(ops) == 2 and ops[0].type == X86_OP_MEM and ops[0].size == 4 and ops[1].type == X86_OP_IMM
                and (ops[0].mem.segment, ops[0].mem.base, ops[0].mem.index, ops[0].mem.scale,
                     ops[0].mem.disp) == memop and ins.mnemonic == "mov"):
            return True
        if any(ins.group(g) for g in (capstone.CS_GRP_JUMP, capstone.CS_GRP_CALL,
                                       capstone.CS_GRP_RET, capstone.CS_GRP_INT, capstone.CS_GRP_IRET)):
            return False
        try:
            written = ins.regs_access()[1]
        except capstone.CsError:
            return False
        if watched & {_register_family(md, r) for r in written}:
            return False
    return False


def retail_vptr_stores(retail, rows, ledger_starts=(), data_ranges=None, ledger_extents=None):
    """Retail vptr stores found in rowed retail functions, with table lengths.

    rows is [(rva, size)]. A store is `mov dword [m], imm32` whose immediate
    is a non-code address holding a code word, and whose slot 0 is a rowed
    start or a jmp (a pushed string whose bytes look like a code address is
    not a table). This finds the stores of that one pattern in rowed bodies;
    what it cannot see is counted in the returned counts (unreadable rows,
    undecodable bytes, slot-0 words that are unrowed adjustors or other
    unrowed code).

    Retail is /FIXED with no RTTI: tables abut and there are no relocations.
    A ledger vtable extent (ledger_extents, rva -> bytes) bounds a run when
    known (extent "ledger"). Otherwise the run ends at the next referenced
    data address (decoded imm/disp operands, aligned data words, ledger
    starts), which an unrelated reference can shorten (extent "unproven").
    A store is transient only when a later store to the same operand
    follows in the same straight-line run (see _overwritten_in_line).
    Returns (stores, counts).
    """
    import capstone
    from capstone.x86_const import X86_INS_MOV, X86_OP_IMM, X86_OP_MEM
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    md.skipdata = True
    base = retail.base
    ledger_extents = ledger_extents or {}
    counts = collections.Counter()
    if data_ranges is None:
        data_ranges = [(s.VirtualAddress, s.VirtualAddress + s.Misc_VirtualSize)
                       for s in retail.sections if not s.Characteristics & 0x20000000]
    lo = min(a for a, _ in data_ranges) + base
    hi = max(b for _, b in data_ranges) + base
    starts = {rva for rva, _ in rows}
    boundaries, found = set(ledger_starts), []
    for rva, size in rows:
        raw = retail.read(rva, size) if 0 < size < 0x100000 else None
        if not raw:
            counts["discovery_rows_unreadable"] += 1
            continue
        instructions = list(md.disasm(raw, rva))
        for at, ins in enumerate(instructions):
            if ins.id == 0:
                counts["discovery_undecoded_bytes"] += ins.size
                continue
            ops = ins.operands
            for op in ops:
                value = (op.imm if op.type == X86_OP_IMM else
                         op.mem.disp if op.type == X86_OP_MEM else 0) & 0xffffffff
                if lo <= value < hi:
                    boundaries.add(value - base)
            if not (ins.id == X86_INS_MOV and len(ops) == 2 and ops[0].type == X86_OP_MEM
                    and ops[0].size == 4 and ops[1].type == X86_OP_IMM):
                continue
            table = (ops[1].imm & 0xffffffff) - base
            word = retail.read(table, 4) if lo - base <= table < hi - base else None
            if word is None:
                continue
            first = struct.unpack("<I", word)[0]
            if not retail.in_text(first):
                continue
            head = retail.read(first - base, 6) or b""
            if first - base not in starts and head[:1] != b"\xe9":
                if head[:2] in (b"\x83\xe9", b"\x83\xc1") and head[3:4] == b"\xe9":
                    counts["discovery_slot0_unrowed_adjustor"] += 1
                else:
                    counts["discovery_slot0_unrowed"] += 1
                continue
            m = ops[0].mem
            memop = (m.segment, m.base, m.index, m.scale, m.disp)
            found.append(dict(function=rva, offset=ins.address - rva, table=table, memop=memop,
                              transient=_overwritten_in_line(md, instructions, at, memop)))
    for start, end in data_ranges:
        raw = retail.read(start, end - start) or b""
        for at in range(0, len(raw) - 3, 4):
            value = struct.unpack_from("<I", raw, at)[0]
            if lo <= value < hi:
                boundaries.add(value - base)
    boundaries = sorted(boundaries)
    for store in found:
        table, words = store["table"], 0
        if ledger_extents.get(table):
            limit, store["extent"] = ledger_extents[table] // 4, "ledger"
        else:
            following = bisect.bisect_right(boundaries, table)
            limit = (boundaries[following] - table) // 4 if following < len(boundaries) else 1024
            store["extent"] = "unproven"
        while words < limit:
            raw = retail.read(table + 4 * words, 4)
            if raw is None or not retail.in_text(struct.unpack("<I", raw)[0]):
                break
            words += 1
        store["slots"] = words
    counts["discovery_stores"] = len(found)
    return found, counts


def _layout_equal(checker, image_rva, retail_rva, size):
    """Same instruction sequence over the retail row: equal sizes and bytes,
    except relocated image fields and relative branch operands whose
    destinations correspond (the same offset inside the row, or an outside
    target that maps to retail's). True proves that offsets inside the row
    correspond; False or None does not."""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    a, b = checker.ours.read(image_rva, size), checker.retail.read(retail_rva, size)
    if a is None or b is None:
        return None
    aa, bb = list(md.disasm(a, image_rva)), list(md.disasm(b, retail_rva))
    if sum(i.size for i in aa) != size or sum(i.size for i in bb) != size:
        return None
    if len(aa) != len(bb):
        return False
    for x, y in zip(aa, bb):
        if x.id != y.id or x.size != y.size:
            return False
        masked = set()
        for start, width in ((x.imm_offset, x.imm_size), (x.disp_offset, x.disp_size)):
            if width == 4 and x.address + start in checker.ours.relocations:
                masked.update(range(start, start + width))
        if (x.group(capstone.CS_GRP_JUMP) or x.group(capstone.CS_GRP_CALL)) and x.imm_size \
                and x.address + x.imm_offset not in checker.ours.relocations:
            here, there = x.operands[0].imm, y.operands[0].imm
            inside_a = image_rva <= here < image_rva + size
            inside_b = retail_rva <= there < retail_rva + size
            if inside_a or inside_b:
                if not (inside_a and inside_b and here - image_rva == there - retail_rva):
                    return False
            else:
                mapped = checker.mapping.resolve(
                    _chase(checker, checker.ours, here + checker.ours.base) - checker.ours.base,
                    there)
                if mapped is None:
                    return None
                if mapped != _chase(checker, checker.retail, there + checker.retail.base) - checker.retail.base \
                        and mapped != there:
                    return False
            masked.update(range(x.imm_offset, x.imm_offset + x.imm_size))
        if any(x.bytes[k] != y.bytes[k] for k in range(x.size) if k not in masked):
            return False
    return True


def _ret_forms(image, rva, size):
    """The set of return immediates (stack cleanup) in a body, or None when it
    does not decode to exactly its size."""
    import capstone
    raw = image.read(rva, size) if size else None
    if not raw:
        return None
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    insns = list(md.disasm(raw, rva))
    if sum(i.size for i in insns) != size:
        return None
    return frozenset(int(i.op_str, 0) if i.op_str else 0 for i in insns if i.mnemonic in ("ret", "retn"))


def _chase(checker, image, value):
    """Follow a chain of plain (unadjusted) jmp thunks."""
    for _ in range(6):
        f = checker.forwarder(image, value - image.base)
        if not f or f[1]:
            break
        value = f[0] + image.base
    return value


def _vptr_slot(checker, slot_rva, actual, expected, end, sizes, by_rva):
    """One installed slot against retail's: match, equiv, wrong, null, data,
    past-extent, purecall, stub or unk, with the image symbol as evidence.
    A slot at or past the installed table's extent is past-extent whatever
    it holds: the word belongs to another symbol."""
    ours, retail = checker.ours, checker.retail
    if end is None or slot_rva + 4 > end:
        return "past-extent", hex(actual)
    if actual == 0:
        return "null", ""
    if not ours.in_text(actual):
        return "data", hex(actual)
    actual, expected = _chase(checker, ours, actual), _chase(checker, retail, expected)
    a, b = actual - ours.base, expected - retail.base
    here = by_rva.get(a, [])
    name = here[0]["name"] if here else ""
    if here and "diagnostic_stubs" in here[0]["object"]:
        return "stub", name
    if name == "__purecall":
        return "purecall", name
    # Alias names at one image address prove the slot only when every retail
    # address they stand for is the expected one or a proven fold of it.
    targets = set()
    for p in here:
        targets |= set(checker.addresses.get(p["name"], ()))
    nominated = b in targets and (targets == {b} or frozenset(targets) in checker.mapping.proven_folds)
    verdict, _reason = checker.slot(actual, expected, sizes)
    # Whatever names the target, its image body must be the expected retail body:
    # bytes when they decide, else at least the same return/stack-cleanup forms.
    size = sizes.get(b)
    body = checker.code_equal(a, b, size) if size else None
    if body is False:
        return "wrong", name
    if body is None:
        mine, theirs = (_ret_forms(ours, a, size), _ret_forms(retail, b, size)) if size else (None, None)
        if mine is None or theirs is None:
            return "unk", name
        if mine != theirs:
            return "wrong", name
    if nominated or verdict is True:
        return "match", name
    if body is True:
        return "equiv", name
    return ("wrong" if verdict is False else "unk"), name


def vptr_store_report(checker, stores, sizes, order=None):
    """Judge each retail vptr store on the linked image (crash prevention).

    A store is judged only when the image's copy of its row has the retail
    row's layout (_layout_equal), so the instruction at the store's offset is
    the same instruction, and only when that instruction carries an image
    fixup on its immediate. The installed table is compared slot by slot over
    retail's run, bounded by the owning symbol's COFF extent (a slot passes
    only when its four bytes lie inside it), else by the next map symbol with
    the image extent unproven. Verdicts: zero-placeholder (a non-??_7 symbol whose
    every slot is null, data or past-extent: P18), bad (any slot that is not
    match, equiv or unk), unanalyzed-slots (no definite defect, but some
    slot is unk: its body could not be compared), extent-unproven (no defect found, but the retail extent
    is only the next referenced address or the image extent is not a COFF
    size), no-defect-found (both extents proven, every slot match or equiv;
    an advisory lead, not a proof of correctness), and the
    unanalyzed-* verdicts. Transient stores are counted, not judged. Stores
    are not reachability: order is an optional {(function, offset): rank}.

    Known limit, the cost of failing closed: a row whose relative calls do
    not resolve through the correspondence is unanalyzed-layout, even when
    its table is right. On diagnostic image 2bac16a657 that hides 1,064
    stores, among them module data such as SubObjectsUpgrade and
    LargeGroupAudio whose installed 31-slot tables were full and correct.
    """
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ours, retail = checker.ours, checker.retail
    by_rva = collections.defaultdict(list)
    for p in checker.publics:
        by_rva[p["rva"]].append(p)
    starts = sorted(by_rva)
    counts = collections.Counter()
    results = []

    def decode(image, rva):
        raw = image.read(rva, 16)
        return next(md.disasm(raw, rva), None) if raw else None

    def unanalyzed(result, why):
        result["verdict"] = "unanalyzed-" + why
        counts["vptr_stores_unanalyzed_" + why.replace("-", "_")] += 1

    for store in stores:
        if store.get("transient"):
            counts["vptr_stores_transient"] += 1
            continue
        fa, at, table, n = store["function"], store["offset"], store["table"], store["slots"]
        result = dict(function_rva=hex(fa), offset=hex(at), retail_table=hex(table + retail.base),
                      retail_slots=n, retail_extent=store.get("extent", "unproven"),
                      order=(order or {}).get((fa, at), ""))
        results.append(result)
        owners = checker.by_retail.get(fa, [])
        locations = {p["rva"] for p in owners}
        if len(locations) != 1:
            unanalyzed(result, "function")
            continue
        image_fa = next(iter(locations))
        result["function"] = owners[0]["name"]
        size = sizes.get(fa)
        if not size or _layout_equal(checker, image_fa, fa, size) is not True:
            unanalyzed(result, "layout")
            continue
        i = decode(ours, image_fa + at)
        if not i or i.imm_size != 4 or i.address + i.imm_offset not in ours.relocations:
            unanalyzed(result, "fixup")
            continue
        if n == 0:
            unanalyzed(result, "empty-table")
            continue
        installed = struct.unpack("<I", ours.read(i.address + i.imm_offset, 4))[0] - ours.base
        index = bisect.bisect_right(starts, installed) - 1
        owner = by_rva[starts[index]][0] if index >= 0 else {}
        exact = index >= 0 and starts[index] == installed
        if owner.get("extent"):
            end, result["image_extent"] = starts[index] + owner["extent"], "coff"
        else:
            end = starts[index + 1] if index + 1 < len(starts) else None
            result["image_extent"] = "unproven"
        symbol = owner.get("name", "")
        if owner and not exact:
            symbol += "+%#x" % (installed - starts[index])
        slots, bad = collections.Counter(), []
        for k in range(n):
            a = struct.unpack("<I", ours.read(installed + 4 * k, 4) or bytes(4))[0]
            b = struct.unpack("<I", retail.read(table + 4 * k, 4))[0]
            kind, note = _vptr_slot(checker, installed + 4 * k, a, b, end, sizes, by_rva)
            slots[kind] += 1
            if kind not in ("match", "equiv"):
                bad.append("slot %d %s %s retail=%#x" % (k, kind, note, b))
        zero = not symbol.startswith("??_7") and slots["null"] + slots["data"] + slots["past-extent"] == n
        definite = [line for line in bad if " unk " not in line]
        if zero:
            verdict = "zero-placeholder"
        elif definite:
            verdict = "bad"
        elif bad:
            # Only undecided slots: no defect found, but nothing proven either.
            verdict = "unanalyzed-slots"
        elif result["retail_extent"] != "ledger" or result["image_extent"] != "coff":
            verdict = "extent-unproven"
        else:
            verdict = "no-defect-found"
        result.update(image_symbol=symbol, object=owner.get("object", ""), source=owner.get("source", ""),
                      slots=dict(slots), bad=bad, verdict=verdict)
        counts["vptr_stores_" + verdict.replace("-", "_")] += 1
        if zero or definite:
            checker.defect("vptr_store_zero" if zero else "vptr_store_slot", fa, owner,
                           "store +%#x installs %s for retail %#x (%d slots, %s extent): %s" % (
                               at, symbol, table + retail.base, n, result["retail_extent"], "; ".join(bad[:3])))
    checker.counts.update(counts)
    return dict(counts=dict(counts), stores=results)


def vptr_store_main(args, checker, rows, sizes, tool_sha256, receipt, object_counts, map_symbols):
    """--vptr-stores: report.json, defects.tsv and vptr_stores.tsv under --out."""
    function_rows = []
    with (build.ROOT / "reverse/functions.csv").open(newline="") as f:
        for row in csv.DictReader(f):
            try:
                function_rows.append((int(row["target_rva"], 16), int(row["target_size"])))
            except ValueError:
                continue
    checker.mapping.prove_folds(checker.retail, sizes)
    extents = {int(r["address"], 16): int(r["size"] or 0) for r in rows if r["kind"] == "vtable"}
    stores, discovery = retail_vptr_stores(checker.retail, sorted(set(function_rows)),
                                           ledger_starts=[int(r["address"], 16) for r in rows],
                                           ledger_extents=extents)
    order = {}
    if args.boot_order:
        with args.boot_order.open(newline="") as f:
            for r in csv.DictReader(f, delimiter="\t"):
                key = (int(r["func_rva"], 16), int(r["insn_off"], 16))
                order.setdefault(key, int(r["order"]))
    result = vptr_store_report(checker, stores, sizes, order)
    report = checker.report()
    report["vptr_stores"] = dict(result["counts"], **discovery)
    report["analysis_scope"] = ("retail vptr stores against installed image tables only; "
                                "verdicts are advisory leads (complete=false), not proofs")
    report["limitations"] = report["limitations"] + [
        "Vptr stores are the mov [m],imm32 stores found in rowed retail bodies (discovery_* counts what it cannot see), not a trace; --boot-order only ranks them.",
        "Retail tables abut (no RTTI): without a ledger vtable extent a run ends at the next referenced data address (extent-unproven).",
        "no-defect-found is the absence of a found defect, not proof of a correct table."]
    report.update(inputs=dict(tool_sha256=tool_sha256, image=str(args.image), map=str(args.map),
                              retail=str(args.retail), image_sha256=digest(args.image),
                              map_sha256=digest(args.map), retail_sha256=digest(args.retail),
                              receipt=receipt, boot_order=str(args.boot_order or "")),
                  object_analysis=dict(object_counts), map_symbols=map_symbols)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    with (args.out / "defects.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["family", "retail_rva", "name", "object", "source", "evidence"], delimiter="\t")
        writer.writeheader()
        writer.writerows(report["defects"])
    rank = lambda r: (r["order"] == "", r["order"] if r["order"] != "" else 0, r["function_rva"], r["offset"])
    with (args.out / "vptr_stores.tsv").open("w", newline="") as f:
        fields = ["order", "verdict", "function_rva", "offset", "function", "retail_table", "retail_slots",
                  "retail_extent", "image_symbol", "image_extent", "object", "source", "slots", "bad"]
        writer = csv.DictWriter(f, fieldnames=fields, delimiter="\t", extrasaction="ignore")
        writer.writeheader()
        for r in sorted(result["stores"], key=rank):
            writer.writerow(dict(r, slots=json.dumps(r.get("slots", {}), sort_keys=True),
                                 bad="; ".join(r.get("bad", []))))
    print(json.dumps({"vptr_stores": report["vptr_stores"], "complete": False}, indent=2))
    return 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--image", required=True, type=Path)
    parser.add_argument("--map", required=True, type=Path)
    parser.add_argument("--retail", type=Path, default=build.EXE)
    parser.add_argument("--objects", type=Path)
    parser.add_argument("--address-only", action="store_true",
                        help="only audit absolute code operands and aligned data words")
    parser.add_argument("--data-pointers-only",action="store_true",help="report tiered pointer evidence in defined data rows only")
    parser.add_argument("--out", type=Path, default=Path("build/image_iso"))
    parser.add_argument("--relocation-bounds-only", action="store_true",
                        help="only audit object-relative relocation bounds")
    parser.add_argument("--vptr-stores", action="store_true",
                        help="only judge retail vptr stores against the tables the image installs")
    parser.add_argument("--kept-copies-only", action="store_true",
                        help="only report rowed names whose kept copy differs from retail")
    parser.add_argument("--boot-order", type=Path,
                        help="with --vptr-stores: boot walk TSV (func_rva, insn_off, order) to rank stores")
    args = parser.parse_args(argv)
    if sum((args.address_only,args.relocation_bounds_only,args.data_pointers_only,args.vptr_stores,args.kept_copies_only))>1:
        parser.error("analysis-only modes are mutually exclusive")
    if args.boot_order and not args.vptr_stores:
        parser.error("--boot-order needs --vptr-stores")
    tool_sha256 = digest(Path(__file__))
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
    ledger = {}
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
            ledger.setdefault(symbol, []).append(row)
            addresses[symbol].add(rva)
            addresses[row["name"]].add(rva)
            sizes[rva] = size
            if row.get("source"):
                for name in (symbol, row["name"]):
                    qualified[(name, source_key(row["source"]))].add(rva)
    kept = kept_copies(ours, retail, publics, ledger)
    kept["ledger"] = ledger_identity(build.ROOT, receipt.get("commit"))
    if kept["ledger"]["warning"]:
        print(f"image_iso: WARNING: {kept['ledger']['warning']}", file=sys.stderr)
    if args.kept_copies_only:
        args.out.mkdir(parents=True, exist_ok=True)
        (args.out / "report.json").write_text(json.dumps(dict(
            kept_copies=kept, analysis_scope="kept copies only; report mode", complete=False,
            inputs=dict(tool_sha256=tool_sha256, image_sha256=digest(args.image), map_sha256=digest(args.map),
                        retail_sha256=digest(args.retail)), object_analysis=dict(object_counts)), indent=2) + "\n")
        write_kept_copies(args.out, kept)
        print(json.dumps(kept["counts"], indent=2))
        return 1
    checker = Checker(ours, retail, publics, addresses, qualified)
    # internal-linkage data the MAP does not list: placed through its own object (place_statics)
    checker.statics = place_statics(publics, args.objects, unlisted_names(rows, checker.by_name), ours,
                                    missed=checker.unplaced, failed=checker.inventory_failed)
    object_counts["static_inventory_objects_unread"] = len(checker.inventory_failed)
    object_counts["static_data_names_placed"] = len(checker.statics)
    if args.vptr_stores:
        return vptr_store_main(args, checker, rows, sizes, tool_sha256, receipt, object_counts, len(publics))
    if not args.address_only and not args.relocation_bounds_only and not args.data_pointers_only:
        checker.ledger(rows, sizes)
        checker.initializers()
        evidence = storage_evidence(retail, rows)
        checker.counts["storage_initializers_considered"] = len(retail.initializers())
        proven = {e["rva"] for e in evidence}
        checker.counts["storage_objects_with_proven_access"] = len(proven)
        checker.counts["storage_globals_without_proven_access"] = sum(
            r["kind"] == "global" and int(r["address"], 16) not in proven for r in rows)
        checker.storage(evidence)
    bounds = (dict(counts={}, defects=[], leads=[], ambiguous=[]) if args.address_only or args.data_pointers_only else
              relocation_bounds(checker, rows, build.ROOT / "reverse/functions.csv"))
    absolute = (dict(counts={}, by_kind={}, ambiguous=[]) if args.relocation_bounds_only or args.data_pointers_only else
                unrelocated_retail_addresses(checker, build.ROOT / "reverse/functions.csv", rows))
    pointers=defined_data_pointers(checker,args.objects,build.ROOT) if not args.relocation_bounds_only else dict(mode="skipped",counts={},findings=[])
    report = checker.report()
    report["defined_data_pointers"] = pointers
    report["relocation_bounds"] = bounds
    report["unrelocated_retail_addresses"] = absolute
    report["kept_copies"] = kept
    report["analysis_scope"] = "absolute address code/data audit only" if args.address_only else "bounded image comparison"
    if args.data_pointers_only:
        report["analysis_scope"]="defined data pointer evidence only; report mode"
    if args.address_only:
        report["analysis_scope"]="absolute address code/data and defined-data pointer evidence only"
    if args.relocation_bounds_only:
        report["analysis_scope"] = "object-relative relocation bounds only"
    report.update(inputs=dict(tool_sha256=tool_sha256,
                              image=str(args.image), map=str(args.map), retail=str(args.retail),
                              image_sha256=digest(args.image), map_sha256=digest(args.map),
                              retail_sha256=digest(args.retail), receipt=receipt,
                              objects_sha256=digest(args.objects) if args.objects else None,
                              data_rows_sha256=digest(build.ROOT / "reverse/data_rows.csv")
                                  if (build.ROOT / "reverse/data_rows.csv").exists() else None),
                  object_analysis=dict(object_counts), map_symbols=len(publics))
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    write_kept_copies(args.out, kept)
    with (args.out / "defects.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["family", "retail_rva", "name", "object", "source", "evidence"], delimiter="\t")
        writer.writeheader()
        writer.writerows(report["defects"])
    with (args.out / "ambiguous.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["family", "retail_rva", "name", "object", "source", "evidence"], delimiter="\t")
        writer.writeheader()
        for detail in absolute["ambiguous"]:
            writer.writerow(dict(family="unrelocated_retail_address_ambiguous",
                retail_rva=detail["row_rva"], name=detail["symbol"], object=detail["object"],
                source=detail["source"], evidence=json.dumps(detail, sort_keys=True, separators=(",", ":"))))
    with (args.out / "relocation_leads.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["family", "retail_rva", "name", "object", "source", "evidence"], delimiter="\t")
        writer.writeheader()
        for d in bounds["leads"] + bounds["ambiguous"]:
            writer.writerow(dict(family="out_of_object_pointer_" + d["classification"],
                retail_rva=d["function_retail_rva"] or "", name=d["function"], object=d["object"],
                source=d["source"], evidence=json.dumps(d, sort_keys=True)))
    with (args.out / "data_pointer_leads.tsv").open("w",newline="") as f:
        writer=csv.DictWriter(f,fieldnames=["family","retail_rva","name","object","source","evidence"],delimiter="\t")
        writer.writeheader()
        for d in pointers["findings"]:
            if d["tier"]=="B":
                writer.writerow(dict(family="defined_data_pointer_lead",retail_rva=d["retail_rva"],name=d["row"],object=d["object"],source=d["source"],evidence=json.dumps(d,sort_keys=True)))
    print(json.dumps({"counts": report["counts"], "defined_data_pointer_counts":pointers["counts"], "relocation_bounds_counts": bounds["counts"], "absolute_address_counts": absolute["counts"],
                      "absolute_address_by_kind": absolute["by_kind"], "complete": False}, indent=2))
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
