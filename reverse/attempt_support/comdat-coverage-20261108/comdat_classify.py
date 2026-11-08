"""Scratch, read-only: classify the kept copies comdat_groups.py found differ from retail or the majority. Causes are classified, never treated as clearances.
usage: comdat_classify.py IMAGE_DIR FUNCTIONS_CSV GAME_DAT GROUPS_TSV KEPT_WRONG_TSV OUT_TSV"""
import collections
import csv
import json
import multiprocessing
import re
import sys
from pathlib import Path

import capstone
import pefile

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
image_dir, functions_csv, game_dat, groups_tsv, wrong_tsv, out = sys.argv[1:7]
image = Path(image_dir) / "image"
FIELD = {0xA: 2}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def masked(body, relocs):
    b = bytearray(body)
    for r in relocs:
        for k in range(r[0], min(r[0] + FIELD.get(r[1], 4), len(b))):
            b[k] = 0
    return bytes(b)


def strip_pad(b):
    return b.rstrip(b"\xcc\x90")


NAMES = None


def _init(n):
    global NAMES
    NAMES = n


def read(job):
    path, idx = job
    found = []
    data = Path(path).read_bytes()
    if not any(n in data for n in NAMES_B):
        return found
    for symbol, body, relocs, digest, size in lc._comdat_sections(data):
        if symbol["name"] in NAMES and body is not None:
            found.append((symbol["name"], idx, bytes(body), [(r[0], r[1], r[2]["name"] if isinstance(r[2], dict) else str(r[2])) for r in relocs]))
    return found


FRAME = re.compile(r"(__EH_prolog|fs:\[0\]|dword ptr \[ebp - 4\], |ebp, esp|push ebp|pop ebp|^leave|__ehhandler)")
FIELD_RE = re.compile(r"\[(eax|ebx|ecx|edx|esi|edi)\s*\+\s*(0x[0-9a-f]+|\d+)\]")


ADD_IMM = re.compile(r"^(eax|ebx|ecx|edx|esi|edi), (0x[0-9a-f]+|\d+)$")


def norm(body):
    out_n, fields = [], set()
    for i in md.disasm(bytes(body), 0):
        text = f"{i.mnemonic} {i.op_str}"
        for m in FIELD_RE.finditer(i.op_str):
            fields.add(int(m.group(2), 0))
        # A member's address taken by arithmetic: isKindOf's `add ecx, 0x68` is this form.
        m = ADD_IMM.match(i.op_str)
        if i.mnemonic == "add" and m and int(m.group(2), 0) >= 0x10:
            fields.add(int(m.group(2), 0))
        out_n.append((i.mnemonic, FRAME.search(text) is not None))
    return out_n, fields


def count_refs(job):
    """(code relocations, data relocations) naming each wanted symbol, across every section of one object."""
    import struct
    path, _ = job
    code, data_r = collections.Counter(), collections.Counter()
    data = Path(path).read_bytes()
    if not any(n in data for n in NAMES_B):
        return code, data_r
    nsec = struct.unpack_from("<H", data, 2)[0]
    opt = struct.unpack_from("<H", data, 16)[0]
    by_index = {s["index"]: s["name"] for s in lc._coff_symbols(data)}
    for i in range(nsec):
        h = 20 + opt + 40 * i
        rptr, nrel = struct.unpack_from("<I", data, h + 24)[0], struct.unpack_from("<H", data, h + 32)[0]
        chars = struct.unpack_from("<I", data, h + 36)[0]
        if not nrel:
            continue
        first = 0
        if chars & 0x01000000 and nrel == 0xFFFF:
            nrel = struct.unpack_from("<I", data, rptr)[0]
            first = 1
        for k in range(first, nrel):
            n = by_index.get(struct.unpack_from("<I", data, rptr + 10 * k + 4)[0])
            if n in NAMES:
                (code if chars & 0x20 else data_r)[n] += 1
    return code, data_r


def classify(kb, kr, rb, rr):
    km, rm = strip_pad(masked(kb, kr)), strip_pad(masked(rb, rr))
    kn, kf = norm(km)
    rn, rf = norm(rm)
    only_k, only_r = kf - rf, rf - kf
    kind, differ = lc.copy_kind(km, rm)
    kseq = [m for m, fr in kn if not fr]
    rseq = [m for m, fr in rn if not fr]
    if only_k and only_r:
        cls = "field offsets disagree"
    elif kseq == rseq and not only_k and not only_r:
        cls = "frame or EH only"
    elif only_k:
        cls = "kept touches extra fields"
    elif only_r:
        cls = "kept touches fewer fields"
    elif kind == "register":
        cls = "registers only"
    else:
        cls = "codegen, same fields"
    return cls, kind, differ, sorted(only_r), sorted(only_k)


def flags(source):
    try:
        first = open(source, "rb").readline().decode("latin-1")
    except OSError:
        return None
    return " ".join(sorted(f for f in first.split() if re.match(r"/(O[a-z0-9-]*|G[0-9A-Za-z-]*|Ob[0-9]|EH[a-z]*|arch:\w+|D_STLP_USE_STATIC_LIB|FI\S+)$", f)))


CANON = {}
for r in csv.reader(open("reverse/canonical_classes.csv", encoding="utf-8", errors="replace")):
    if len(r) >= 2:
        CANON[r[0]] = r[1]


def canon_of(name):
    for m in re.finditer(r"@([A-Za-z_][A-Za-z0-9_]*)@@", name):
        if m.group(1) in CANON:
            return m.group(1)
    return None


def includes(source, cls):
    try:
        t = open(source, "rb").read().decode("latin-1")
    except OSError:
        return None
    base = CANON[cls].rsplit("/", 1)[-1]
    return bool(re.search(r'#include\s+"[^"]*\.\./[^"]*Include/[^"]*' + re.escape(base) + '"', t))


if __name__ == "__main__":
    groups = [r for r in csv.DictReader(open(groups_tsv, encoding="utf-8"), delimiter="\t")]
    bad = {r["name"]: r for r in groups if r["kept_vs"] not in ("retail", "majority", "not in map", "kept object not matched")}
    print("groups", len(groups), "kept copy differs", len(bad))
    for probe in ("?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z", "?isKindOfMulti@ThingTemplate@@QBE_NABV?$BitFlags@$0HE@@@0@Z"):
        hit = [r for r in groups if r["name"] == probe]
        print("probe", probe[:32], {k: hit[0][k] for k in ("kind", "kept_vs", "refs", "only_ref", "only_kept", "kept_src")} if hit else "absent")
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    NAMES_B = [n.encode() for n in bad]
    NAMES = frozenset(bad)
    jobs = [(str(image / e["path"].replace("\\", "/")), i) for i, e in enumerate(manifest)]
    with multiprocessing.Pool(4) as pool:
        res = pool.map(read, jobs, chunksize=64)
        counted = pool.map(count_refs, jobs, chunksize=64)
    code_refs, data_refs = collections.Counter(), collections.Counter()
    for c, d in counted:
        code_refs.update(c)
        data_refs.update(d)
    copies = collections.defaultdict(list)
    for rows in res:
        for name, idx, body, relocs in rows:
            copies[name].append((idx, body, relocs))
    frows = {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        frows.setdefault(r["name"], r)
    retail = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()
    wrong = {r["name"]: r for r in csv.DictReader(open(wrong_tsv, encoding="utf-8"), delimiter="\t")}
    out_rows = []
    for name, g in bad.items():
        cs = copies[name]
        src = lambda i: manifest[i].get("source") or ""
        kept = next((c for c in cs if src(c[0]).endswith(g["kept_src"].lstrip("^"))) or [], None) if False else None
        for c in cs:
            if src(c[0]).endswith(g["kept_src"]):
                kept = c
                break
        if kept is None:
            continue
        row = frows.get(name)
        ref = None
        target_note = ""
        if g["rva"]:
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = bytes(retail[rva:rva + size])
            rb, rr = target, []
            matches = []
            for c in cs:
                t = masked(target[:len(c[1])], [x for x in c[2] if x[0] < len(target)])
                if strip_pad(masked(c[1], c[2])) == strip_pad(t):
                    matches.append(c)
            ref = matches[0] if matches else None
            if ref is None:
                refbody, refrel, refsrc = target, kept[2], "(retail bytes)"
            else:
                refbody, refrel, refsrc = ref[1], ref[2], src(ref[0])
        else:
            maj = collections.Counter(strip_pad(masked(c[1], c[2])) for c in cs).most_common(1)[0][0]
            ref = next(c for c in cs if strip_pad(masked(c[1], c[2])) == maj)
            refbody, refrel, refsrc = ref[1], ref[2], src(ref[0])
        cls, kind, differ, only_r, only_k = classify(kept[1], kept[2], refbody, refrel)
        fk, fr = flags(src(kept[0])), flags(refsrc) if refsrc != "(retail bytes)" else None
        fl = "unknown" if fk is None or fr is None else ("same" if fk == fr else "differ")
        cn = canon_of(name)
        ck = includes(src(kept[0]), cn) if cn else None
        cr = includes(refsrc, cn) if cn and refsrc != "(retail bytes)" else None
        cands = [c for c in cs if cn and includes(src(c[0]), cn)]
        canon_agree = ""
        if cn and cands:
            canon_agree = "kept" if any(strip_pad(masked(c[1], c[2])) == strip_pad(masked(kept[1], kept[2])) for c in cands) else "other"
        family = sorted({x[2][:34] for x in kept[2] if re.search(r"__new_alloc|__node_alloc|__sgi_alloc|_Node_alloc|__malloc_alloc", x[2])})
        out_rows.append(dict(name=name, refs=code_refs[name], data_refs=data_refs[name], family=";".join(family), kept_vs=g["kept_vs"], cls=cls, shape=kind, differ=differ, flags=fl, rva=g["rva"], order=g["order"], tier=g["tier"],
                             census_wrong=name in wrong, canon=cn or "", kept_canon=ck, ref_canon=cr, canon_agree=canon_agree, only_ref=",".join(hex(x) for x in only_r[:5]), only_kept=",".join(hex(x) for x in only_k[:5]),
                             kept_src=src(kept[0])[-60:], ref_src=refsrc[-60:], copies=g["copies"], distinct=g["distinct"]))
    out_rows.sort(key=lambda r: -r["refs"])
    with open(out, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, list(out_rows[0]), delimiter="\t")
        w.writeheader()
        w.writerows(out_rows)
    print("classified", len(out_rows))
    ctl = [r for r in out_rows if r["name"].startswith(("?isKindOf@ThingTemplate", "?isKindOfMulti@ThingTemplate"))]
    print("control, must read field offsets disagree:", [(r["name"][:24], r["cls"], r["only_ref"], r["only_kept"], r["refs"]) for r in ctl])
    print("zero references in code and data:", sum(not r["refs"] and not r["data_refs"] for r in out_rows), "of", len(out_rows))
    print("kept copy reaches the pool or stock allocators:", sum(bool(r["family"]) for r in out_rows))
    for r in [x for x in out_rows if x["family"]][:14]:
        print(f"   {r['refs']:>5} {r['rva']:>9} o{str(r['order'])[:6]:6} {r['family'][:34]:34} {r['name'][:54]:54} {r['kept_src'][-26:]}")
    print("class", collections.Counter(r["cls"] for r in out_rows).most_common())
    print("class by kept_vs", sorted(collections.Counter((re.sub(r"\d+ of \d+", "N", r["kept_vs"]), r["cls"]) for r in out_rows).items()))
    print("flags between kept and reference unit", collections.Counter(r["flags"] for r in out_rows).most_common())
    print("flags by class", sorted(collections.Counter((r["cls"], r["flags"]) for r in out_rows).items()))
    print("census judged wrong too", sum(r["census_wrong"] for r in out_rows), "of", len(out_rows), "; on walk", sum(bool(r["order"]) for r in out_rows))
    miss = set(wrong) - {r["name"] for r in out_rows}
    print("census kept-wrong names not here", len(miss), "code", sum(wrong[n]["kind"] == "code" for n in miss))
    print("no row:", sum(not r["rva"] for r in out_rows), "with a canonical class", sum(bool(r["canon"]) and not r["rva"] for r in out_rows), "canon copy agrees", collections.Counter(r["canon_agree"] for r in out_rows if not r["rva"]).most_common())
    print("== field offsets disagree, by references")
    for r in [x for x in out_rows if x["cls"] == "field offsets disagree"][:45]:
        print(f"{r['refs']:>5} {r['kept_vs'][:16]:16} fl={r['flags'][:6]:6} {r['rva']:>9} o{str(r['order'])[:6]:6} t{r['tier']:<2} ref[{r['only_ref'][:22]}] kept[{r['only_kept'][:22]}] {r['name'][:50]:50} {r['kept_src'][-26:]}")
    print("== kept touches extra fields, by references")
    for r in [x for x in out_rows if x["cls"] == "kept touches extra fields"][:18]:
        print(f"{r['refs']:>5} {r['kept_vs'][:16]:16} fl={r['flags'][:6]:6} {r['rva']:>9} o{str(r['order'])[:6]:6} kept[{r['only_kept'][:22]}] {r['name'][:54]:54} {r['kept_src'][-26:]}")
