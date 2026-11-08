"""Scratch, read-only: a graph of what one image kept, from the objects it was linked from and its map. Writes OUT.pkl; compiles nothing.
A node is a kept symbol: code or data, its size, what it references by name, for rowed code whether the kept bytes equal retail's outside relocation fields,
for unrowed code whether it touches fields. usage: image_graph.py IMAGE_DIR FUNCTIONS_CSV GAME_DAT OUT [--limit N]"""
import collections
import csv
import json
import multiprocessing
import pickle
import re
import struct
import sys
from pathlib import Path

import capstone
import pefile

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
IMAGE_BASE = 0x400000
DIR32, REL32, SECTION = 6, 0x14, 0xA
SKIP_SECTION = re.compile(r"^\.(debug|drectve|sxdata)")
FIELD_RE = re.compile(r"\[(eax|ebx|ecx|edx|esi|edi)\s*\+\s*(0x[0-9a-f]+|\d+)\]")
ADD_IMM = re.compile(r"^(eax|ebx|ecx|edx|esi|edi), (0x[0-9a-f]+|\d+)$")
G = {}


def init(kept, rows, game_dat):
    G["kept"], G["rows"] = kept, rows
    G["retail"] = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()
    G["md"] = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def fields(body):
    out = set()
    for i in G["md"].disasm(bytes(body), 0):
        for m in FIELD_RE.finditer(i.op_str):
            out.add(int(m.group(2), 0))
        m = ADD_IMM.match(i.op_str)
        if i.mnemonic == "add" and m and int(m.group(2), 0) >= 0x10:
            out.add(int(m.group(2), 0))
    return out


def read(job):
    path, provider, idx, source = job
    data = Path(path).read_bytes()
    nsec = struct.unpack_from("<H", data, 2)[0]
    opt = struct.unpack_from("<H", data, 16)[0]
    symptr, nsym = struct.unpack_from("<II", data, 8)
    strtab = symptr + nsym * 18
    syms = lc._coff_symbols(data)
    by_index = {s["index"]: s for s in syms}
    per_section = collections.defaultdict(list)
    for s in syms:
        n = s["name"]
        if s.get("section", 0) > 0 and s.get("storage") in (2, 3) and not n.startswith(("$", ".", "__ehhandler$", "__unwindfunclet$", "__catch$", "__tryend$")):
            per_section[s["section"]].append(s)
    nodes, roots, funclet_bytes, global_sites, calls = [], [], 0, [], []
    for i in range(nsec):
        h = 20 + opt + 40 * i
        raw_name = data[h:h + 8].rstrip(b"\0").decode("latin-1")
        if raw_name.startswith("/"):
            off = int(raw_name[1:])
            raw_name = data[strtab + off:data.index(b"\0", strtab + off)].decode("latin-1")
        size, ptr, rptr = struct.unpack_from("<III", data, h + 16)
        nrel = struct.unpack_from("<H", data, h + 32)[0]
        chars = struct.unpack_from("<I", data, h + 36)[0]
        if SKIP_SECTION.match(raw_name) or chars & 0x800:
            continue
        code = bool(chars & 0x20)
        body = data[ptr:ptr + size] if ptr and not chars & 0x80 else b""
        relocs = []
        first = 0
        if chars & 0x01000000 and nrel == 0xFFFF:
            nrel = struct.unpack_from("<I", data, rptr)[0]
            first = 1
        for k in range(first, nrel):
            va, si, ty = struct.unpack_from("<IIH", data, rptr + 10 * k)
            relocs.append((va, si, ty))
        if raw_name.startswith(".CRT$X"):
            for va, si, ty in relocs:
                t = by_index.get(si)
                if t:
                    roots.append((t["name"], provider if t.get("storage") == 3 else None))
            continue
        owners = sorted(per_section.get(i + 1, []), key=lambda s: s["value"])
        if not owners:
            if code:
                funclet_bytes += size
            continue
        starts = [o["value"] for o in owners]
        for j, o in enumerate(owners):
            key = (o["name"], provider)
            if key not in G["kept"]:
                continue
            start = o["value"]
            end = next((v for v in starts[j + 1:] if v > start), size)
            own = [r for r in relocs if start <= r[0] < end]
            targets = []
            for va, si, ty in own:
                t = by_index.get(si)
                if not t or t["name"].startswith((".", "$SG", "$L")):
                    continue
                targets.append((t["name"], provider if t.get("storage") == 3 else None))
            node = dict(name=o["name"], provider=idx, static=o.get("storage") == 3, code=code, size=end - start, section=raw_name, comdat=bool(chars & 0x1000), targets=sorted(set(targets)))
            if code:
                piece = bytearray(body[start:end])
                for va, si, ty in own:
                    w = 2 if ty == SECTION else 4
                    for x in range(va - start, min(va - start + w, len(piece))):
                        piece[x] = 0
                row = G["rows"].get(o["name"])
                # A static name is numbered per unit, so only its owning unit's copy is that row.
                if row and (o.get("storage") != 3 or row[2] == source):
                    rva, rsize = row[:2]
                    t = bytearray(G["retail"][rva:rva + rsize])
                    for va, si, ty in own:
                        w = 2 if ty == SECTION else 4
                        for x in range(va - start, min(va - start + w, len(t))):
                            t[x] = 0
                    n = min(len(piece), rsize)
                    node["rowed_ok"] = bytes(piece[:n]) == bytes(t[:n]) and bytes(piece[n:]).strip(b"\xcc\x90") == b""
                    node["rowed_short"] = len(piece.rstrip(b"\xcc\x90")) < rsize
                    for va, si, ty in (own if node["rowed_ok"] else []):
                        if ty == REL32 and va - start + 4 <= rsize and va - start >= 1:
                            sym = by_index.get(si)
                            if sym:
                                rel = struct.unpack_from("<i", G["retail"], rva + va - start)[0]
                                calls.append((sym["name"], provider if sym.get("storage") == 3 else None, rva + va - start + 4 + rel))
                        if ty == DIR32 and va - start + 4 <= rsize:
                            sym = by_index.get(si)
                            if sym and not sym["name"].startswith(("$", ".", "??_C@", "__real@")):
                                addend = struct.unpack_from("<I", body, va)[0]
                                dword = struct.unpack_from("<I", G["retail"], rva + va - start)[0]
                                global_sites.append((sym["name"], (dword - addend - IMAGE_BASE) & 0xFFFFFFFF, addend, rva))
                else:
                    node["fields"] = sorted(fields(piece))
                    node["masked"] = bytes(piece)
            nodes.append(node)
    return nodes, roots, funclet_bytes, global_sites, calls


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    image_dir, functions_csv, game_dat, out = args[:4]
    limit = int(sys.argv[sys.argv.index("--limit") + 1]) if "--limit" in sys.argv else None
    image = Path(image_dir) / "image"
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    kept, by_name, va_size, sections_end = set(), {}, {}, {}
    for line in open(image / "exit.map", errors="replace"):
        m = re.match(r"\s*([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$", line)
        if m and int(m.group(1), 16) > 0:
            kept.add((m.group(3), m.group(5)))
            by_name.setdefault((m.group(3), m.group(5)), (int(m.group(1), 16), int(m.group(4), 16)))
    rows, notes = {}, {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        try:
            v = (int(r["target_rva"], 16), int(r["target_size"], 0), r["source"])
        except ValueError:
            continue
        rows.setdefault(r["name"], v)
        notes.setdefault(r["name"], (r.get("notes") or "")[:60])
        m = re.search(r"object-symbol=(\S+?)(;|\s|$)", r.get("notes") or "")
        if m:
            rows.setdefault(m.group(1), v)
            notes.setdefault(m.group(1), (r.get("notes") or "")[:60])
    print("map symbols", len(kept), "rows", len(rows))
    jobs = [(str(image / e["path"].replace("\\", "/")), e["provider"], i, e.get("source") or "") for i, e in enumerate(manifest)]
    if limit:
        jobs = jobs[:limit]
    with multiprocessing.Pool(4, init, (kept, rows, game_dat)) as pool:
        res = pool.map(read, jobs, chunksize=48)
    nodes, roots, funclets, sites, calls = [], [], 0, [], []
    for n, r, f, s, c in res:
        calls.extend(c)
        nodes.extend(n)
        roots.extend(r)
        funclets += f
        sites.extend(s)
    va = {k: v for k, v in by_name.items()}
    for n in nodes:
        n["va"] = va[(n["name"], manifest[n["provider"]]["provider"])][1]
    pickle.dump(dict(nodes=nodes, roots=roots, funclets=funclets, sites=sites, calls=calls, manifest=manifest, rows=rows, notes=notes, kept=len(kept)), open(out, "wb"))
    print("nodes", len(nodes), "code", sum(n["code"] for n in nodes), "roots", len(set(roots)), "label-only code bytes", funclets, "global sites", len(sites))
    print("map symbols with no node", len(kept) - len({(n["name"], manifest[n["provider"]]["provider"]) for n in nodes}))
    print("sample", {k: str(v)[:70] for k, v in nodes[0].items()})


if __name__ == "__main__":
    main()
