"""Scratch, read-only: reclassify unrowed code over the kept length, then settle the malloc and deque leads. usage: leads2.py GRAPH.pkl GAME_DAT NEW_MAP OUT_TSV"""
import collections
import csv
import pickle
import re
import struct
import sys

import capstone
import pefile

csv.field_size_limit(10**8)
graph_pkl, game_dat, new_map, out = sys.argv[1:5]
g = pickle.load(open(graph_pkl, "rb"))
nodes, rows, manifest = g["nodes"], g["rows"], g["manifest"]
retail = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
FIELD_RE = re.compile(r"\[(eax|ebx|ecx|edx|esi|edi)\s*\+\s*(0x[0-9a-f]+|\d+)\]")
ADD_IMM = re.compile(r"^(eax|ebx|ecx|edx|esi|edi), (0x[0-9a-f]+|\d+)$")
provider_idx = {e["provider"]: i for i, e in enumerate(manifest)}
src = lambda n: manifest[n["provider"]].get("source") or ""


def is_row(n):
    r = rows.get(n["name"])
    return bool(r) and (not n["static"] or r[2] == src(n))


index = {}
rev = collections.defaultdict(list)
for n in nodes:
    index.setdefault((n["name"], n["provider"] if n["static"] else None), n)
    for t in n["targets"]:
        rev[t[0]].append(n)
called = collections.defaultdict(collections.Counter)
for name, prov, target in g["calls"]:
    k = (name, provider_idx.get(prov) if prov else None)
    n = index.get(k)
    if n is not None and n["code"] and not is_row(n):
        called[k][target] += 1


def fields(body):
    out_f, ops = set(), []
    for i in md.disasm(body, 0):
        ops.append(i.mnemonic)
        for m in FIELD_RE.finditer(i.op_str):
            out_f.add(int(m.group(2), 0))
        m = ADD_IMM.match(i.op_str)
        if i.mnemonic == "add" and m and int(m.group(2), 0) >= 0x10:
            out_f.add(int(m.group(2), 0))
    return out_f, ops


rec = []
for k, targets in called.items():
    n = index[k]
    body = n["masked"].rstrip(b"\xcc\x90")
    addr = targets.most_common(1)[0][0]
    rva = addr
    for _ in range(3):
        if retail[rva] == 0xE9:
            rva = rva + 5 + struct.unpack_from("<i", retail, rva + 1)[0]
        else:
            break
    rb = bytes(retail[rva:rva + len(body)])
    same = all(x == y or x == 0 for x, y in zip(body, rb))
    kf, kops = fields(body)
    rf, rops = fields(rb)
    if same:
        cls = "same"
    elif kf - rf and rf - kf:
        cls = "fields disagree"
    elif kops == rops:
        cls = "same instructions, other operands"
    elif kf - rf:
        cls = "kept touches fields retail does not"
    elif rf - kf:
        cls = "retail touches fields kept does not"
    else:
        cls = "codegen, same fields"
    s = src(n)
    try:
        zh = "CnC_Generals_Zero_Hour" in open(s, "rb").readline().decode("latin-1")
    except OSError:
        zh = False
    rec.append(dict(name=n["name"], source=s, zh=zh, cls=cls, size=len(body), retail=f"{rva:#x}", sites=sum(targets.values()), only_retail=",".join(hex(x) for x in sorted(rf - kf)[:6]), only_kept=",".join(hex(x) for x in sorted(kf - rf)[:6]), stl="_STL" in n["name"]))
with open(out, "w", encoding="utf-8", newline="") as f:
    w = csv.DictWriter(f, list(rec[0]), delimiter="\t")
    w.writeheader()
    w.writerows(sorted(rec, key=lambda r: -r["sites"]))
print("over the kept length:", len(rec), "nodes", sum(r["size"] for r in rec), "B")
print("class:", collections.Counter(r["cls"] for r in rec).most_common())
print("bytes:", sorted(((c, sum(r["size"] for r in rec if r["cls"] == c)) for c in {r["cls"] for r in rec}), key=lambda x: -x[1]))
print("named, not same:", sum(not r["stl"] and r["cls"] != "same" for r in rec), "; Zero Hour view:", sum(r["zh"] and r["cls"] != "same" for r in rec))
for probe in ("?allocate@?$allocator@UPrereqUnitRec@ProductionPrerequisite", "?isPlayerActive@Player@@QBE_NXZ"):
    print("control or probe", probe[:44], [(r["cls"], r["retail"], r["sites"], r["only_retail"], r["only_kept"]) for r in rec if r["name"].startswith(probe)])
for c in ("fields disagree", "same instructions, other operands", "kept touches fields retail does not", "retail touches fields kept does not"):
    print("==", c)
    for r in sorted([x for x in rec if x["cls"] == c], key=lambda r: (-r["sites"], -r["size"]))[:16]:
        print(f"{r['sites']:>4} {r['size']:>5}B zh={str(r['zh'])[:1]} ret {r['retail']:>9} r[{r['only_retail'][:18]}] k[{r['only_kept'][:18]}] {r['name'][:48]:48} {r['source'][-28:]}")
print("== everything reaching CRT malloc, with rowed reach")
start = "?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z"
seen, stack, rowed_callers = set(), [start], collections.Counter()
while stack:
    nm = stack.pop()
    for n in rev.get(nm, []):
        if is_row(n):
            rowed_callers[(n["name"], rows[n["name"]][0], n.get("rowed_ok"), src(n))] += 1
        elif n["code"] and n["name"] not in seen:
            seen.add(n["name"])
            stack.append(n["name"])
print("unrowed functions on the path:", len(seen), "; rows that reach them:", len(rowed_callers))
for (nm, rva, ok, s), c in sorted(rowed_callers.items(), key=lambda x: x[0][1])[:24]:
    print(f"   {rva:#9x} ok={ok} {nm[:66]:66} {s[-30:]}")
print("direct allocator<char> member variants, callers:")
for nm in ("?allocate@?$allocator@D@_STL@@QAEPADIPBX@Z", "?allocate@?$allocator@D@_STL@@QBEPADIPBX@Z"):
    print("  ", nm[:44], len(rev.get(nm, [])), "callers; rowed", sum(is_row(n) for n in rev.get(nm, [])), [n["name"][:38] for n in rev.get(nm, [])[:4]])
print("== newer image")
want = ("??$_M_range_initialize@PAD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEXPAD0ABUforward_iterator_tag@1@@Z", start, "?allocate@?$allocator@D@_STL@@QAEPADIPBX@Z")
for line in open(new_map, errors="replace"):
    for w_ in want:
        if w_ in line:
            print("  ", re.sub(r"\s+", " ", line)[:130])
