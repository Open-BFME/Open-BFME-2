"""Read-only, tree-wide. Marked present-unmatched definitions with no row or pin that another object references:
retail's address from a rowed consumer's relocation, our body against retail's, ranked by the boot walk."""
import collections
import csv
import glob
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import build as B

BASE = 0x400000
S = "build/scratch_defects/"


def coff(path):
    d = open(path, "rb").read()
    if len(d) < 20 or d[:2] != b"\x4c\x01":
        return None
    nsec = struct.unpack_from("<H", d, 2)[0]
    ptr, n = struct.unpack_from("<II", d, 8)
    strs = ptr + n * 18
    secs = [struct.unpack_from("<IIIIIIHHI", d, 20 + 40 * i + 8) for i in range(nsec)]
    syms = {}
    i = 0
    while i < n:
        e = d[ptr + 18 * i:ptr + 18 * (i + 1)]
        if len(e) < 18:
            break
        nm = e[:8]
        if nm[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", nm, 4)[0]
            name = d[strs + off:d.find(b"\0", strs + off)].decode("latin-1")
        else:
            name = nm.rstrip(b"\0").decode("latin-1")
        syms[i] = (name, struct.unpack_from("<I", e, 8)[0], struct.unpack_from("<h", e, 12)[0], struct.unpack_from("<H", e, 14)[0], e[16])
        i += 1 + e[17]
    return d, secs, syms


# ---- markers
out = subprocess.run(["rg", "-n", "present-unmatched", "Code", "--glob", "*.cpp", "--glob", "*.c", "--no-heading"], capture_output=True, text=True, errors="replace").stdout
marks = collections.defaultdict(list)
total = 0
for line in out.splitlines():
    src, _, rest = line.split(":", 2)
    m = re.search(r"//\s*\?(\S.*?)\s+present-unmatched", rest)
    if m:
        marks[src].append(m.group(1))
        total += 1


def symbol_keys(tok):
    """What a marker can look like in a decorated name."""
    if tok.startswith("?"):
        return ("exact", tok)
    if "::" not in tok:
        return ("prefix", f"?{tok}@@")
    parts = re.sub(r"<[^>]*>", "", tok).split("::")
    if len(parts) < 2:
        return ("prefix", f"?{parts[0]}@@")
    name, scopes = parts[-1], list(reversed(parts[:-1]))
    scope = "@".join(scopes)
    if name.startswith("~"):
        return ("prefix", f"??1{scope}@@")
    if parts[-1] == parts[-2]:
        return ("prefix", f"??0{scope}@@")
    ops = {"operator->": "??C", "operator*": "??D", "operator=": "??4", "operator==": "??8", "operator!=": "??9", "operator[]": "??A", "operator++": "??E", "operator--": "??F", "operator+": "??H", "operator-": "??G", "operator<": "??M", "operator()": "??R"}
    if name in ops:
        return ("prefix", f"{ops[name]}{scope}@@")
    if name.startswith("operator"):
        return ("contains", f"@{scope}@@")
    return ("prefix", f"?{name}@{scope}@@")


# ---- every object's definitions and references
objs = glob.glob("build/match/*.obj")
defs = collections.defaultdict(set)
refs = collections.defaultdict(set)
for f in objs:
    c = coff(f)
    if not c:
        continue
    for name, _, sec, typ, cls in c[2].values():
        if cls != 2:
            continue
        if sec > 0:
            defs[name].add(f)
        elif sec == 0:
            refs[name].add(f)

all_rows = B.load_all_function_rows()
rows = {r["name"] for r in all_rows}
pins = set(B.load_symbol_map())
rownames = collections.defaultdict(list)
for r in all_rows:
    rownames[os.path.basename(str(B.obj_path(r["source"])))].append(r)

mapped = unmatched = norow = absent = 0
loose = []
cand = []
srcobj = {}
for src, toks in marks.items():
    o = "build/match/" + os.path.basename(str(B.obj_path(src)))
    if not os.path.exists(o):
        unmatched += len(toks)
        continue
    c = coff(o)
    if not c:
        unmatched += len(toks)
        continue
    names = {n for n, _, sec, typ, cl in c[2].values() if cl == 2 and sec > 0}
    for tok in toks:
        kind, key = symbol_keys(tok)
        if kind == "exact":
            hit = [key] if key in names else []
        elif kind == "prefix":
            hit = [n for n in names if n.startswith(key)]
        else:
            hit = [n for n in names if key in n and "??" in n]
        if not hit:
            unmatched += 1
            leaf = re.sub(r"<[^>]*>", "", tok).split("::")[-1].lstrip("~")
            # Is the identifier in the object at all, under some other scope or spelling?
            near = [n for n in names if leaf and (f"?{leaf}@" in n or f"@{leaf}@" in n or f"??0{leaf}@" in n or f"??1{leaf}@" in n)]
            if near:
                loose.append((tok, near, src, o))
            else:
                absent += 1
            continue
        mapped += 1
        for n in hit:
            if n in rows or n in pins:
                continue
            norow += 1
            cand.append((n, src, o))

looseadded = 0
for tok, near, src, o in loose:
    for n in near:
        if n not in rows and n not in pins:
            cand.append((n, src, o))
            looseadded += 1
print(f"unmapped markers: {len(loose)} name an identifier present in their object (counted, loosely); {absent} name nothing the object defines")
live = []
for n, src, o in set(cand):
    others = {x for x in refs.get(n, ()) if os.path.basename(x) != os.path.basename(o)}
    provs = {x for x in defs.get(n, ()) if os.path.basename(x) != os.path.basename(o)}
    if others and not provs:
        live.append((n, src, o, others))
print(f"markers in .cpp/.c comments: {total}; mapped to a definition in their object: {mapped}; not emitted or not mapped: {unmatched}")
print(f"definitions with no row or pin: {len(set(cand))}; referenced by another object and the only provider: {len(live)}")

# ---- retail address from a rowed consumer, our bytes against retail's
ledger = {}
with open("reverse/data_ledger.csv", newline="", encoding="utf-8") as h:
    for r in csv.DictReader(h):
        for nm in [r["name"], *(r.get("names") or "").split(";")]:
            if nm:
                ledger[nm] = int(r["address"], 16)
rowname = {r["name"]: r for r in all_rows}


def resolve(sym, consumers):
    votes = collections.Counter()
    via = {}
    for f in consumers:
        c = coff(f)
        if not c:
            continue
        d, secs, syms = c
        idx = {i for i, s in syms.items() if s[0] == sym}
        if not idx:
            continue
        by_sec = collections.defaultdict(list)
        for i, s in syms.items():
            if s[2] > 0 and s[4] in (2, 3):
                by_sec[s[2]].append(s)
        for snum, sec in enumerate(secs, 1):
            # VirtualSize, VirtualAddress, SizeOfRawData, PointerToRawData, PointerToRelocations, PointerToLinenumbers, NumberOfRelocations, ...
            size, raw, rel, nrel = sec[2], sec[3], sec[4], sec[6]
            for k in range(nrel):
                off, si, ty = struct.unpack_from("<IIH", d, rel + 10 * k)
                if si not in idx:
                    continue
                owner = None
                for s in sorted(by_sec[snum], key=lambda s: s[1]):
                    if s[1] <= off and s[4] == 2 and (s[0] in rowname or s[0] in ledger):
                        owner = s
                if owner is None:
                    continue
                try:
                    if owner[0] in rowname:
                        r = rowname[owner[0]]
                        at = int(r["target_rva"], 16) + off - owner[1]
                        if ty == 20:
                            t = at + 4 + struct.unpack("<i", B.read_target_bytes(at, 4))[0]
                        else:
                            t = struct.unpack("<I", B.read_target_bytes(at, 4))[0] - BASE
                    else:
                        at = ledger[owner[0]] + off - owner[1]
                        t = struct.unpack("<I", B.read_target_bytes(at, 4))[0] - BASE
                except Exception:
                    continue
                votes[t] += 1
                via[t] = owner[0]
    return votes, via


order = {}
table_order = {}
with open(os.path.expanduser("~/bfme2-ops/seat4/build/crashprev/scan3.tsv"), newline="", encoding="utf-8", errors="replace") as h:
    for r in csv.DictReader(h, delimiter="\t"):
        try:
            a = int(r["func_rva"], 16)
            order[a] = min(order.get(a, 10 ** 9), int(r["order"]))
            t = int(r["retail_table"], 16) - BASE
            table_order[t] = min(table_order.get(t, 10 ** 9), int(r["order"]))
        except Exception:
            pass
with open(S + "callee.tsv", newline="", encoding="utf-8", errors="replace") as h:
    for r in csv.DictReader(h, delimiter="\t"):
        o = int(r["order"])
        for tok in re.findall(r"0x[0-9a-f]+", r["retail_rva"] + " " + r["chain"]):
            a = int(tok, 16)
            order[a] = min(order.get(a, 10 ** 9), o)

result = []
for n, src, o, others in live:
    votes, via = resolve(n, list(others)[:12])
    ours = None
    try:
        ours, rel = B.read_object_symbol_bytes(Path(o), n, 2048)
    except Exception:
        pass
    verdict, addr = "no rowed consumer", None
    walk = None
    if votes:
        addr = votes.most_common(1)[0][0]
        walk = order.get(addr)
        for t_, owner_ in via.items():
            if owner_ in rowname:
                cand_ = order.get(int(rowname[owner_]["target_rva"], 16))
            else:
                cand_ = table_order.get(ledger.get(owner_))
            if cand_ is not None and (walk is None or cand_ < walk):
                walk = cand_
        if len(votes) > 1:
            verdict = "consumers disagree"
        elif ours is None:
            verdict = "body not read"
        else:
            try:
                t = B.read_target_bytes(addr, len(ours))
                masked = set()
                for r_ in rel or ():
                    at = r_[0] if isinstance(r_, (tuple, list)) else getattr(r_, "offset", None)
                    if at is not None:
                        masked.update(range(at, at + 4))
                same = all(x == y or k in masked for k, (x, y) in enumerate(zip(ours, t)))
                verdict = "same" if same else "DIFFERS"
            except Exception:
                verdict = "address unreadable"
    result.append((walk if walk is not None else 10 ** 9, verdict, n, addr, len(ours) if ours else 0, len(others), src))
result.sort(key=lambda x: (x[0], x[1] != "DIFFERS"))
print(collections.Counter(r[1] for r in result).most_common())
onwalk = [r for r in result if r[0] < 10 ** 9]
print("on the boot walk:", len(onwalk), collections.Counter(r[1] for r in onwalk).most_common())
with open(S + "hatch_rank.tsv", "w", encoding="utf-8") as h:
    h.write("walk_order\tverdict\tsymbol\tretail_rva\tour_size\tconsumers\tsource\n")
    for w, v, n, a, sz, cn, src in result:
        h.write(f"{'' if w == 10**9 else w}\t{v}\t{n}\t{hex(a) if a is not None else ''}\t{sz}\t{cn}\t{src}\n")
print("== DIFFERS by walk")
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
md = Cs(CS_ARCH_X86, CS_MODE_32)
shown = 0
detail = []
for w, v, n, a, sz, cn, src in result:
    if v == "DIFFERS":
        print(f" {'-' if w == 10**9 else w:>6} {hex(a) if a is not None else '':>10} {sz:4d}B {cn:3d} refs {n[:56]:56s} {src.split('/')[-1][:24]}")
        if shown < 14 and w < 10 ** 9:
            detail.append((w, n, a, src))
            shown += 1
print("== bodies")
for w, n, a, src in detail:
    o = "build/match/" + os.path.basename(str(B.obj_path(src)))
    ours, _ = B.read_object_symbol_bytes(Path(o), n, 2048)
    x = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(ours, 0)]
    y = []
    for i in md.disasm(B.read_target_bytes(a, 96), a):
        y.append(f"{i.mnemonic} {i.op_str}")
        if i.mnemonic in ("ret", "jmp") and len(y) > 1 and i.mnemonic == "ret":
            break
    print(f"-- walk {w} {n[:60]} retail {a:#x}: ours {len(x)} instructions, retail {len(y)}")
    for k in range(min(7, max(len(x), len(y)))):
        print(f"   {(x[k] if k < len(x) else '')[:40]:40s} {(y[k] if k < len(y) else '')[:40]}")
