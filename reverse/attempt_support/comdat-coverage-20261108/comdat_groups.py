"""Scratch, read-only: COMDAT functions whose copies differ once relocation fields are masked, over the exact objects one image was linked from.
Uses tools/link_census.py's section reader. For each differing symbol: the copy the image's map kept, whether it matches retail where a row exists, else the majority,
which copies match, the kept copy's field offsets against retail's or the majority's, and how many relocations name it across all objects.
usage: comdat_groups.py IMAGE_DIR FUNCTIONS_CSV GAME_DAT WALK_TSV OUT_PREFIX [--limit N]. Compiles nothing; writes only OUT_PREFIX.*"""
import collections
import csv
import hashlib
import json
import multiprocessing
import os
import re
import struct
import sys
from pathlib import Path

import capstone
import pefile

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
args = [a for a in sys.argv[1:] if not a.startswith("--")]
image_dir, functions_csv, game_dat, walk_tsv, out = args[:5]
limit = int(sys.argv[sys.argv.index("--limit") + 1]) if "--limit" in sys.argv else None
if limit:
    args = args[:5]
image = Path(image_dir) / "image"
FIELD = {0xA: 2}  # IMAGE_REL_I386_SECTION is 2 bytes; every other relocation here is 4.
DATA = re.compile(r"^(\?\?_[78CBRE]|\?\?_R|__real@|__xmm@|__ymm@|_\$)|@@[0-9][A-Z_]|@@3|@4[A-Z]")
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def is_function(name, body):
    return body is not None and not DATA.search(name)


def masked(body, relocs):
    b = bytearray(body)
    for r in relocs:
        off, typ = r[0], r[1]
        for k in range(off, min(off + FIELD.get(typ, 4), len(b))):
            b[k] = 0
    return bytes(b)


def strip_pad(b):
    return b.rstrip(b"\xcc\x90")


def read_copies(job):
    path, ident = job
    out_rows = []
    try:
        data = Path(path).read_bytes()
        for symbol, body, relocs, digest, size in lc._comdat_sections(data):
            name = symbol["name"]
            if not is_function(name, body):
                continue
            m = strip_pad(masked(body, relocs))
            names = (r[2]["name"] if isinstance(r[2], dict) else str(r[2]) for r in relocs)
            # A label or TU-local name is numbered per object, so it can't tell two copies apart.
            targets = tuple(sorted({n for n in names if not n.startswith(("$", "__ehhandler", "_$", "??_C@", "__real@"))}))
            out_rows.append((name, hashlib.sha1(m).hexdigest()[:16], len(m), ident, targets))
    except Exception as e:  # An unreadable object is counted, never silently dropped.
        return [("!unreadable", str(e)[:60], 0, ident, ())]
    return out_rows


def count_refs(job):
    path, wanted = job
    found = collections.Counter()
    try:
        data = Path(path).read_bytes()
        nsec = struct.unpack_from("<H", data, 2)[0]
        opt = struct.unpack_from("<H", data, 16)[0]
        by_index = {s["index"]: s["name"] for s in lc._coff_symbols(data)}
        for i in range(nsec):
            h = 20 + opt + 40 * i
            rptr, nrel = struct.unpack_from("<I", data, h + 24)[0], struct.unpack_from("<H", data, h + 32)[0]
            chars = struct.unpack_from("<I", data, h + 36)[0]
            if not chars & 0x20 or not nrel:
                continue
            first = 0
            if chars & 0x01000000 and nrel == 0xFFFF:
                nrel = struct.unpack_from("<I", data, rptr)[0]
                first = 1
            for k in range(first, nrel):
                sym = struct.unpack_from("<I", data, rptr + 10 * k + 4)[0]
                n = by_index.get(sym)
                if n in wanted:
                    found[n] += 1
    except Exception:
        found["!unreadable"] += 1
    return found


_wanted = None


def _init(w):
    global _wanted
    _wanted = w


def _count(path):
    return count_refs((path, _wanted))


def disasm(body, base=0):
    return list(md.disasm(bytes(body), base))


def fields(body):
    """Displacements off a register other than the frame, the field offsets this body touches."""
    out_f = set()
    for i in disasm(body):
        for m in re.finditer(r"\[(e[a-ds][xi]|edi|esi)\s*([+-])\s*(0x[0-9a-f]+|\d+)\]", i.op_str):
            v = int(m.group(3), 0)
            if m.group(2) == "+":
                out_f.add(v)
    return out_f


def main():
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    print("manifest keys", list(manifest[0]))
    jobs = []
    ident = {}
    for e in manifest[:limit] if limit else manifest:
        path = image / e["path"].replace("\\", "/")
        name = e.get("object") or e.get("name") or (e.get("source") or "")
        ident[str(path)] = e
        jobs.append((str(path), len(jobs)))
    with multiprocessing.Pool(4) as pool:
        results = pool.map(read_copies, jobs, chunksize=64)
    copies = collections.defaultdict(list)
    unreadable = 0
    for rows in results:
        for name, h, n, idx, targets in rows:
            if name == "!unreadable":
                unreadable += 1
                continue
            copies[name].append((h, n, idx, targets))
    print(f"objects {len(jobs)}, unreadable {unreadable}, function COMDAT symbols {len(copies)}, with 2+ copies {sum(len(v) > 1 for v in copies.values())}")
    byte_diff = {n: v for n, v in copies.items() if len({c[0] for c in v}) > 1}
    target_diff = {n: v for n, v in copies.items() if n not in byte_diff and len({c[3] for c in v}) > 1}
    print(f"copies differ in masked bytes: {len(byte_diff)}; same masked bytes, different relocation targets: {len(target_diff)}")

    # The copy the image kept, from its map.
    kept_obj = {}
    for line in open(image / "exit.map", errors="replace"):
        m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(i\s+)?(\S+)", line)
        if m and m.group(1) in byte_diff or (m and m.group(1) in target_diff):
            kept_obj.setdefault(m.group(1), m.group(5))
    rows = {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        rows.setdefault(r["name"], r)
    walk = {}
    for r in csv.DictReader(open(walk_tsv, encoding="utf-8"), delimiter="\t"):
        try:
            walk[int(r["rva"], 16)] = (int(r["order"]), r["anchor"], r["tier"])
        except (KeyError, ValueError):
            pass
    retail = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()
    wanted = frozenset(byte_diff) | frozenset(target_diff)
    with multiprocessing.Pool(4, _init, (wanted,)) as pool:
        counted = pool.map(_count, [j[0] for j in jobs], chunksize=64)
    refs = collections.Counter()
    for c in counted:
        refs.update(c)
    print("reference pass unreadable objects:", refs.pop("!unreadable", 0))

    def source_of(idx):
        return manifest[idx].get("source") or manifest[idx]["path"]

    def obj_key(idx):
        s = source_of(idx)
        return re.sub(r"[A-Z]", lambda m: "^" + m.group(0).lower(), s.replace("/", "_").replace("\\", "_")).rsplit(".", 1)[0] + ".obj"

    def flags_of(idx):
        try:
            first = open(source_of(idx), "rb").readline().decode("latin-1")
        except OSError:
            return ""
        return " ".join(f for f in first.split() if re.match(r"/(O|G|Ob|EH|GX|arch|D_STLP_USE_STATIC)", f))

    # Re-read bodies only for the objects each differing symbol needs.
    def body_of(idx, name):
        data = Path(jobs[idx][0]).read_bytes()
        for symbol, body, relocs, digest, size in lc._comdat_sections(data):
            if symbol["name"] == name:
                return body, relocs
        return None, None

    records = []
    for name, v in {**byte_diff, **target_diff}.items():
        kind = "bytes" if name in byte_diff else "targets"
        keeper = kept_obj.get(name)
        if keeper is None:
            kept = None
        else:
            kept = next((c for c in v if obj_key(c[2])[-40:] == keeper[-40:]), None)
        hashes = collections.Counter(c[0] for c in v)
        maj_hash, maj_n = hashes.most_common(1)[0]
        row = rows.get(name)
        rva = size = None
        retail_ok_hash = None
        if row:
            try:
                rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            except ValueError:
                rva = None
        rec = dict(name=name, kind=kind, copies=len(v), distinct=len(hashes), refs=refs[name], kept=bool(keeper), kept_found=bool(kept),
                   rva=f"{rva:#x}" if rva is not None else "", status="", order="", tier="", kept_src=source_of(kept[2])[-58:] if kept else (keeper or "")[-58:],
                   kept_vs="", retail_copy="", only_ref="", only_kept="", kept_flags="", other_flags="", maj_n=maj_n)
        if rva is not None and rva in walk:
            rec["order"], _, rec["tier"] = walk[rva]
        if kept is None:
            rec["kept_vs"] = "not in map" if keeper is None else "kept object not matched"
            records.append(rec)
            continue
        kb, kr = body_of(kept[2], name)
        rec["kept_flags"] = flags_of(kept[2])
        other = next((c for c in v if c[0] != kept[0]), None)
        if other:
            rec["other_flags"] = flags_of(other[2])
        if rva is not None:
            target = bytes(retail[rva:rva + size])
            match_hashes = set()
            for h in hashes:
                c = next(x for x in v if x[0] == h)
                b, r = body_of(c[2], name)
                if b is None:
                    continue
                # Mask this copy's own relocation fields in retail's bytes too.
                t = masked(target[:len(b)], [x for x in r if x[0] < len(target)])
                if strip_pad(masked(b, r)) == strip_pad(t):
                    match_hashes.add(h)
            rec["retail_copy"] = len(match_hashes)
            rec["kept_vs"] = "retail" if kept[0] in match_hashes else ("retail copy lost" if match_hashes else "no copy matches retail")
            ref_body = target
        else:
            rec["kept_vs"] = "majority" if kept[0] == maj_hash else f"minority {hashes[kept[0]]} of {len(v)}"
            c = next(x for x in v if x[0] == maj_hash)
            ref_body, _ = body_of(c[2], name)
        if kb is not None and ref_body is not None:
            fk, fr = fields(kb), fields(ref_body)
            rec["only_ref"] = ",".join(hex(x) for x in sorted(fr - fk)[:5])
            rec["only_kept"] = ",".join(hex(x) for x in sorted(fk - fr)[:5])
        records.append(rec)

    keys = list(records[0]) if records else []
    with open(out + ".tsv", "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, keys, delimiter="\t")
        w.writeheader()
        for r in sorted(records, key=lambda r: -r["refs"]):
            w.writerow(r)
    print("kept_vs by kind:")
    tally = collections.Counter((r["kind"], re.sub(r"\d+ of \d+", "N", str(r["kept_vs"]))) for r in records)
    for k, n in sorted(tally.items()):
        print("  ", k, n)
    print("kept copy differs, with different field offsets:", sum(bool(r["only_ref"] or r["only_kept"]) and r["kept_vs"] not in ("retail", "majority", "not in map") for r in records))
    show = [r for r in records if r["kept_vs"] not in ("retail", "majority", "not in map")]
    show.sort(key=lambda r: -r["refs"])
    print(f"top of {len(show)} by references:")
    for r in show[:40]:
        print(f"{r['refs']:>6} {r['kind'][:5]:5} {str(r['kept_vs'])[:22]:22} c{r['copies']:<3} d{r['distinct']:<2} {r['rva']:>9} o{str(r['order'])[:6]:6} t{r['tier']:<2} r[{r['only_ref'][:18]}] k[{r['only_kept'][:18]}] {r['name'][:54]:54} {r['kept_src'][-30:]}")


if __name__ == "__main__":
    main()
