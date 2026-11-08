"""Scratch, read-only: from image_graph.py's pickle, what kept code no byte-verified row covers; holes in row coverage; allocate against free by element type.
usage (worktree near the image's commit): image_cover.py GRAPH.pkl RANKING_TSV OUT_PREFIX"""
import collections
import csv
import pickle
import re
import sys

csv.field_size_limit(10**8)
graph_pkl, ranking_tsv, prefix = sys.argv[1:4]
g = pickle.load(open(graph_pkl, "rb"))
nodes, rows, notes, manifest = g["nodes"], g["rows"], g["notes"], g["manifest"]
provider_idx = {e["provider"]: i for i, e in enumerate(manifest)}


def key(n):
    return (n["name"], n["provider"] if n["static"] else None)


index = {}
for n in nodes:
    index.setdefault(key(n), n)


def tkey(t):
    return (t[0], provider_idx.get(t[1]) if t[1] else None)


def is_row(n):
    r = rows.get(n["name"])
    return bool(r) and (not n["static"] or r[2] == (manifest[n["provider"]].get("source") or ""))


rowed_va = {n["va"] for n in nodes if n["code"] and is_row(n)}
code = [n for n in nodes if n["code"]]
total = sum(n["size"] for n in code)
for n in code:
    n["state"] = "rowed" if is_row(n) else ("folded onto a row" if n["va"] in rowed_va else "unrowed")
print("kept code nodes", len(code), "bytes", total, "; label-only code bytes outside any named symbol", g["funclets"])
print("  by state:", {k: (sum(1 for n in code if n["state"] == k), sum(n["size"] for n in code if n["state"] == k)) for k in ("rowed", "folded onto a row", "unrowed")})


def reach(starts):
    seen, stack = set(), list(starts)
    while stack:
        k = stack.pop()
        if k in seen or k not in index:
            continue
        seen.add(k)
        stack.extend(tkey(t) for t in index[k]["targets"])
    return seen


rowed_keys = [key(n) for n in code if n["state"] == "rowed"]
from_rows = reach(rowed_keys)
inits = {tkey(t) for t in g["roots"]}
from_all = reach(list(rowed_keys) + list(inits))
direct = set()
for n in code:
    if n["state"] == "rowed":
        direct.update(tkey(t) for t in n["targets"])
un = [n for n in code if n["state"] == "unrowed"]
for n in un:
    k = key(n)
    n["reach"] = "called from a row" if k in direct else ("reached from rows" if k in from_rows else ("initializer only" if k in from_all else "unreached"))
    n["has_fields"] = bool(n.get("fields"))
    n["calls_unrowed"] = any(tkey(t) in index and index[tkey(t)]["code"] and index[tkey(t)].get("state") == "unrowed" for t in n["targets"])
    src = manifest[n["provider"]].get("source") or ""
    nm = n["name"]
    n["kind"] = ("crt" if src.startswith("vendor") else "generated" if src.startswith(("Code/gen", "Code/masm")) else
                 "initializer" if re.match(r"(_\$E|_\$S|\?\?__E|\$E)", nm) else
                 "vector or deleting dtor helper" if nm.startswith(("??_E", "??_G", "??_D", "??_L", "??_M", "??_H", "??_I")) else
                 "STL instantiation" if "@_STL@@" in nm or "_STL@" in nm else "named")
print("unrowed code, by reach (nodes, bytes):")
for r in ("called from a row", "reached from rows", "initializer only", "unreached"):
    s = [n for n in un if n["reach"] == r]
    print(f"  {r:20} {len(s):>6} {sum(n['size'] for n in s):>9}  touch fields {sum(n['has_fields'] for n in s):>6} ({sum(n['size'] for n in s if n['has_fields'])} B)  call unrowed {sum(n['calls_unrowed'] for n in s):>5}")
print("unrowed code, by kind (nodes, bytes, of which reachable from rows):")
for k, c in collections.Counter(n["kind"] for n in un).most_common():
    s = [n for n in un if n["kind"] == k]
    print(f"  {k:32} {c:>6} {sum(n['size'] for n in s):>9} reachable {sum(n['size'] for n in s if n['reach'] in ('called from a row', 'reached from rows')):>9}")

# Hole 1: a row exists, but the image keeps other bytes under its name.
bad = [n for n in code if n["state"] == "rowed" and not n.get("rowed_ok", True)]
print(f"HOLE rowed name, kept bytes differ from retail: {len(bad)} nodes, {sum(n['size'] for n in bad)} B; COMDAT {sum(n['comdat'] for n in bad)}, strong {sum(not n['comdat'] for n in bad)}; reachable {sum(key(n) in from_all for n in bad)}")
kinds = collections.Counter(re.match(r"[a-z-]*", notes.get(n["name"], "")).group(0) or "other" for n in bad)
print("   by note kind:", kinds.most_common(8))
own = {}
for src_row in csv.DictReader(open("build/cs/m43/functions.csv", encoding="utf-8", errors="replace", newline="")):
    own.setdefault(src_row["name"], src_row["source"])
elsewhere = [n for n in bad if own.get(n["name"]) and own[n["name"]] != manifest[n["provider"]].get("source")]
print("   kept from a unit that is not the row's owner:", len(elsewhere), "; from the owner yet still differing:", len(bad) - len(elsewhere))
print("   the owner's own differing rows, first 12:")
for n in [x for x in bad if x not in elsewhere][:12]:
    print(f"     {rows[n['name']][0]:#x} {n['size']:>5}B {notes.get(n['name'], '')[:26]:26} {n['name'][:64]}")

# Hole 2: offsets under a relocation. A field of a global is masked; one name bound to two addresses shows it.
sites = collections.defaultdict(collections.Counter)
addends = collections.Counter()
for name, base, addend, rva in g["sites"]:
    sites[name][base] += 1
    if addend:
        addends[name] += 1
multi = {k: v for k, v in sites.items() if len(v) > 1 and not k.startswith(("___ImageBase", "__except_list", "__imp_"))}
inside = {k: v for k, v in multi.items() if sum(1 for b in v if 0x1000 <= b < 0xADA000) > 1}
print(f"   of those, 2+ addresses inside the image: {len(inside)}; sites {sum(sum(v.values()) for v in inside.values())}")
print(f"HOLE global sites read {len(g['sites'])}, names {len(sites)}, with a non-zero addend {sum(addends.values())}; names bound to 2+ retail addresses {len(multi)}")
spread = sorted(multi.items(), key=lambda kv: -sum(kv[1].values()))
for k, v in spread[:14]:
    print(f"     {sum(v.values()):>5} sites {len(v):>3} addresses {k[:58]:58} {[hex(b) for b, _ in v.most_common(3)]}")
with open(prefix + ".multi.tsv", "w", encoding="utf-8") as f:
    for k, v in spread:
        f.write(k + "\t" + "\t".join(f"{b:#x}:{c}" for b, c in v.most_common()) + "\n")

# Units.
hatches = collections.Counter()
for line in open("reverse/hatch_baseline.tsv", encoding="utf-8", errors="replace"):
    c = line.rstrip("\n").split("\t")
    if len(c) >= 3 and c[0] == "present_unmatched":
        hatches[c[1]] += 1
canon = {}
for r in csv.reader(open("reverse/canonical_classes.csv", encoding="utf-8", errors="replace")):
    if len(r) >= 2:
        canon[r[0]] = r[1]


def view(src):
    try:
        head = open(src, "rb").read(200000).decode("latin-1")
    except OSError:
        return "?", set()
    first = head.split("\n", 1)[0]
    zh = "CnC_Generals_Zero_Hour" in first
    return ("zh" if zh else "-"), {m for m in re.findall(r'#include\s+"Common/(\w+)\.h"|#include\s+"GameLogic/(\w+)\.h"|#include\s+"GameClient/(\w+)\.h"', head) for m in m if m}


units = collections.defaultdict(lambda: dict(n=0, b=0, reach_b=0, dead_b=0, fields=0, names=[]))
for n in un:
    src = manifest[n["provider"]].get("source") or "?"
    u = units[src]
    u["n"] += 1
    u["b"] += n["size"]
    live = n["reach"] in ("called from a row", "reached from rows")
    u["reach_b"] += n["size"] if live else 0
    u["dead_b"] += n["size"] if n["reach"] == "unreached" else 0
    u["fields"] += n["has_fields"] and n["kind"] == "named"
    u["names"].append(n)
out = []
for src, u in units.items():
    v, headers = view(src)
    cls = sorted({c for n in u["names"] if n["kind"] == "named" for c in re.findall(r"@([A-Za-z_]\w*)@@", n["name"]) if c in canon})
    registered_views = sorted(h for h in headers if h in canon)
    out.append(dict(source=src, view=v, nodes=u["n"], bytes=u["b"], reachable=u["reach_b"], dead=u["dead_b"], named_with_fields=u["fields"], markers=hatches.get(src, 0),
                    classes=",".join(cls[:6]), zh_registered=",".join(registered_views[:8])))
out.sort(key=lambda r: -r["reachable"])
with open(prefix + ".units.tsv", "w", encoding="utf-8", newline="") as f:
    w = csv.DictWriter(f, list(out[0]), delimiter="\t")
    w.writeheader()
    w.writerows(out)
with open(prefix + ".bodies.tsv", "w", encoding="utf-8", newline="") as f:
    w = csv.writer(f, delimiter="\t")
    w.writerow(["source", "name", "size", "reach", "kind", "fields", "calls_unrowed"])
    for n in sorted(un, key=lambda n: (manifest[n["provider"]].get("source") or "", -n["size"])):
        w.writerow([manifest[n["provider"]].get("source") or "", n["name"], n["size"], n["reach"], n["kind"], ",".join(hex(x) for x in n.get("fields", [])[:8]), n["calls_unrowed"]])
zh = [r for r in out if r["view"] == "zh" and r["zh_registered"]]
print(f"units with unrowed kept code: {len(out)}; compiled with Zero Hour's headers and including a registered class's header that way: {len(zh)}, {sum(r['bytes'] for r in zh)} B, reachable {sum(r['reachable'] for r in zh)} B, unreached {sum(r['dead'] for r in zh)} B")
print("top units by reachable unrowed bytes:")
for r in out[:16]:
    print(f"  {r['reachable']:>8} of {r['bytes']:>8} n{r['nodes']:<5} {r['view']:2} m{r['markers']:<3} f{r['named_with_fields']:<4} {r['source'][-58:]}")
print("top Zero Hour view units, by reachable named bytes:")
named_reach = collections.Counter()
for n in un:
    if n["kind"] == "named" and n["reach"] in ("called from a row", "reached from rows"):
        named_reach[manifest[n["provider"]].get("source") or ""] += n["size"]
zset = {r["source"]: r for r in zh}
for src, b in [x for x in named_reach.most_common() if x[0] in zset][:22]:
    r = zset[src]
    print(f"  {b:>7} named reachable; unreached {r['dead']:>7} m{r['markers']:<3} f{r['named_with_fields']:<4} {src[-52:]:52} {r['zh_registered'][:46]}")
print("the five accessors' units:")
for acc in ("?getObject@Drawable@@QBEPBVObject@@XZ", "?testDrawableStatus@Drawable", "?isPlayableSide@PlayerTemplate@@QBE_NXZ", "?isSharedNSync@SpecialPowerTemplate@@QBE_NXZ", "?isScoringEnabled@GameLogic@@QBE_NXZ"):
    hit = [n for n in code if n["name"].startswith(acc)]
    for n in hit[:1]:
        src = manifest[n["provider"]].get("source") or ""
        u = next((r for r in out if r["source"] == src), None)
        print(f"  {acc[:34]:34} fields {n.get('fields')} state {n['state']} reach {n.get('reach')} {src[-44:]} :: {u and {k: u[k] for k in ('view', 'nodes', 'bytes', 'reachable', 'dead', 'markers')}}")
# P54 overlap.
p54 = list(csv.DictReader(open(ranking_tsv, encoding="utf-8"), delimiter="\t"))
by_name = {n["name"]: n for n in un}
hit = [r for r in p54 if r["symbol"] in by_name]
print(f"P54 ranking rows {len(p54)}; also in this unrowed list {len(hit)}; by verdict {collections.Counter(r['verdict'] for r in hit).most_common()}; in the image but rowed or folded {sum(r['symbol'] not in by_name and any(n['name'] == r['symbol'] for n in code) for r in p54)}; not kept {sum(not any(n['name'] == r['symbol'] for n in code) for r in p54)}")
print("   P54 units", len({r["source"] for r in p54}), "; units here with reachable named bytes", len(named_reach), "; shared", len({r["source"] for r in p54} & set(named_reach)))

# Allocate against free, per element type, over kept nodes.
ALLOC = [(re.compile(r"\?allocate@(\?\$__node_alloc|__new_alloc)"), "pool"), (re.compile(r"\?allocate@\?\$__malloc_alloc"), "malloc"), (re.compile(r"\?allocate@\?\$allocator@D@_STL@@SA"), "raw"), (re.compile(r"^\?\?2@"), "new")]
FREE = [(re.compile(r"\?deallocate@\?\$__node_alloc"), "pool"), (re.compile(r"\?deallocate@__new_alloc"), "new_alloc free"), (re.compile(r"\?deallocate@\?\$__malloc_alloc"), "malloc"), (re.compile(r"^__imp__free$"), "crt free"), (re.compile(r"^_free$|\?free@_STL@@"), "game free"), (re.compile(r"^\?\?3@"), "delete")]
memo = {}


def families(k, table, want, depth=0):
    if (k, want) in memo:
        return memo[(k, want)]
    memo[(k, want)] = set()
    n = index.get(k)
    out_f = set()
    if n is not None and depth < 6:
        for t in n["targets"]:
            matched = False
            for rx, name in table:
                if rx.search(t[0]):
                    out_f.add(name)
                    matched = True
            if not matched and re.match(rf"\?{want}@\?\$allocator@", t[0]):
                out_f |= families(tkey(t), table, want, depth + 1)
    memo[(k, want)] = out_f
    return out_f


T_RE = re.compile(r"\?\$allocator@(.+?)@@?@_STL@@")
per = collections.defaultdict(lambda: dict(alloc=collections.Counter(), free=collections.Counter(), live=False, names=set()))
for n in code:
    m = T_RE.search(n["name"])
    if not m:
        continue
    T = m.group(1)
    if T == "D" and "allocate@?$allocator@D@_STL@@SA" in n["name"]:
        continue
    k = key(n)
    a, f = families(k, ALLOC, "allocate"), families(k, FREE, "deallocate")
    p = per[T]
    p["alloc"].update(a)
    p["free"].update(f)
    p["live"] = p["live"] or k in from_all
    if a or f:
        p["names"].add(n["name"])
# `new` is left out: a function named for a type can call operator new for something else.
for p in per.values():
    p["alloc"].pop("new", None)
OK = {("pool", "pool"), ("raw", "game free"), ("malloc", "malloc"), ("malloc", "crt free"), ("raw", "delete")}
mixed = []
for T, p in per.items():
    if not p["alloc"] or not p["free"]:
        continue
    pairs = {(a, f) for a in p["alloc"] for f in p["free"]}
    badp = pairs - OK
    if badp:
        mixed.append((T, sorted(badp), dict(p["alloc"]), dict(p["free"]), p["live"], sorted(p["names"])[:3]))
print(f"element types {len(per)}, with an allocate and a free side seen {sum(bool(p['alloc'] and p['free']) for p in per.values())}; with an incompatible pair {len(mixed)}; reachable {sum(m[4] for m in mixed)}")
print("control P72 string:", {k: (dict(v["alloc"]), dict(v["free"])) for k, v in per.items() if k == "D@2"})
ctrl = per.get("UPrereqUnitRec@ProductionPrerequisite") or next((p for t, p in per.items() if "PrereqUnitRec@ProductionPrerequisite" in t), None)
print("control PrereqUnitRec:", ctrl and (dict(ctrl["alloc"]), dict(ctrl["free"])))
print("pairs:", collections.Counter(tuple(m[1]) if len(m[1]) == 1 else "several" for m in mixed).most_common(8))
with open(prefix + ".allocfree.tsv", "w", encoding="utf-8", newline="") as f:
    w = csv.writer(f, delimiter="\t")
    for m in sorted(mixed, key=lambda m: not m[4]):
        w.writerow([m[0], m[1], m[2], m[3], m[4], m[5]])
for m in sorted(mixed, key=lambda m: (not m[4], -sum(m[2].values())))[:24]:
    print(f"   live={str(m[4])[:1]} {m[0][:48]:48} {m[1]} a{m[2]} f{m[3]}")
    T = m[0]
    for n in code:
        h = T_RE.search(n["name"])
        if h and h.group(1) == T:
            k = key(n)
            a, f = families(k, ALLOC, "allocate"), families(k, FREE, "deallocate")
            a.discard("new")
            if a - {"raw"} or f - {"game free"}:
                print(f"        {sorted(a)!s:18} {sorted(f)!s:26} reach={k in from_all} {n['state'][:5]} {n['name'][:52]} {(manifest[n['provider']].get('source') or '')[-30:]}")
