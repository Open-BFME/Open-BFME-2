"""Scratch, read-only: order_sim.py's data, re-solved with the initializer order frozen and names kept outside the manifest set aside. Links nothing.
usage: order_sim2.py SIM.pkl TARGETS.pkl OUT_PREFIX"""
import bisect
import collections
import csv
import heapq
import pickle
import re
import sys

csv.field_size_limit(10**8)
d = pickle.load(open(sys.argv[1], "rb"))
targets = pickle.load(open(sys.argv[2], "rb"))
prefix = sys.argv[3]
copies, crt, manifest, kept, rows, owner = d["copies"], d["crt"], d["manifest"], d["kept"], d["rows"], d["owner"]
# The real command line: generated bridge objects first, then the manifest's order, stubs and library members last.
FRONT = ("retail_vtables.obj", "retail_initializers.obj")
back_ = [i for i, e in enumerate(manifest) if e["provider"] == "diagnostic_stubs.obj" or ":" in e["provider"]]
front = sorted((i for i, e in enumerate(manifest) if e["provider"] in FRONT), key=lambda i: FRONT.index(manifest[i]["provider"]))
rest = [i for i in range(len(manifest)) if i not in set(front) | set(back_)]
remap = {old: new for new, old in enumerate(front + rest + back_)}
manifest = [manifest[old] for old in front + rest + back_]
copies = {n: [(remap[c[0]], c[1], c[2], c[3]) for c in cs] for n, cs in copies.items()}
crt = {remap[k]: v for k, v in crt.items()}
PINNED = set(range(len(front)))
prov = {e["provider"]: i for i, e in enumerate(manifest)}
by_source = {e.get("source"): i for i, e in enumerate(manifest) if e.get("source")}
ALLOC = re.compile(r"\?(de)?allocate@|_M_create_node|_M_erase|_M_deallocate|_M_allocate|_M_clear|\?\?1\?\$_Vector_base|\?\?1\?\$_Deque_base|_M_put_node|_M_get_node|\?\?1\?\$_List_base|\?\?1\?\$_Rb_tree_base")
DATA = re.compile(r"^\?\?_[78]|@@[0-9][A-Z_]|@@3|^\?\?_R|^__real|^\?\?_C")

outside = collections.Counter()
tested = wrong = 0
miss = []
for name, cs in copies.items():
    k = kept.get(name)
    if k is None or len(cs) < 2:
        continue
    if k not in prov:
        outside[k] += 1
        continue
    tested += 1
    first = min(c[0] for c in cs)
    if manifest[first]["provider"] != k:
        wrong += 1
        miss.append((name, manifest[first]["provider"], k))
print("kept from objects outside the manifest:", outside.most_common(6))
print(f"RULE with those aside: names with 2+ copies {tested}; first in manifest order kept for {tested - wrong}; not for {wrong}")
for m in miss[:6]:
    print("   ", m[0][:60], m[1][-30:], m[2][-30:])


def lis(seq):
    tails = []
    for x in seq:
        i = bisect.bisect_left(tails, x)
        if i == len(tails):
            tails.append(x)
        else:
            tails[i] = x
    return len(tails)


pinned_wins = {}


def build(freeze_alloc, freeze_all_code):
    edges, why = collections.defaultdict(set), collections.defaultdict(set)
    named = 0
    for name, cs in copies.items():
        if len({c[2] for c in cs}) < 2:
            continue
        k = kept.get(name)
        if k is not None and k not in prov:
            continue
        if name in rows and any(c[3] for c in cs):
            own_idx = by_source.get(owner.get(name))
            good = [c for c in cs if c[3]]
            rep = next((c[0] for c in good if c[0] == own_idx), min(c[0] for c in good))
            ok = {c[2] for c in good}
            diff = [c[0] for c in cs if c[2] not in ok]
        elif k is not None and not DATA.search(name) and (freeze_all_code or (freeze_alloc and ALLOC.search(name))):
            keeper = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
            if keeper is None:
                continue
            rep = keeper[0]
            diff = [c[0] for c in cs if c[2] != keeper[2]]
        elif k is not None and DATA.search(name):
            keeper = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
            if keeper is None:
                continue
            rep = keeper[0]
            diff = [c[0] for c in cs if c[2] != keeper[2]]
        else:
            continue
        if diff:
            named += 1
        for x in diff:
            if x != rep and x not in PINNED:
                edges[rep].add(x)
                why[(rep, x)].add(name)
            elif x in PINNED and rep not in PINNED:
                pinned_wins[name] = manifest[x]["provider"]
    # Initializer order stays as it is: a chain through every object with a .CRT$XC section.
    chain = sorted(v for v, c in crt.items() if c)
    for a, b in zip(chain, chain[1:]):
        edges[a].add(b)
        why[(a, b)].add("(initializer order)")
    return edges, why, named


def scc(edges):
    n = len(manifest)
    index, low, on, comp, stack, c, idx = {}, {}, set(), {}, [], 0, 0
    for root in range(n):
        if root in index:
            continue
        work = [(root, iter(edges.get(root, ())))]
        index[root] = low[root] = idx
        idx += 1
        stack.append(root)
        on.add(root)
        while work:
            v, it = work[-1]
            adv = False
            for w in it:
                if w not in index:
                    index[w] = low[w] = idx
                    idx += 1
                    stack.append(w)
                    on.add(w)
                    work.append((w, iter(edges.get(w, ()))))
                    adv = True
                    break
                if w in on:
                    low[v] = min(low[v], index[w])
            if adv:
                continue
            work.pop()
            if work:
                low[work[-1][0]] = min(low[work[-1][0]], low[v])
            if low[v] == index[v]:
                while True:
                    w = stack.pop()
                    on.discard(w)
                    comp[w] = c
                    if w == v:
                        break
                c += 1
    return comp


def order_of(edges, comp):
    members = collections.defaultdict(list)
    for v, k in comp.items():
        members[k].append(v)
    indeg, out = collections.Counter(), collections.defaultdict(set)
    for v, ws in edges.items():
        for w in ws:
            if comp[v] != comp[w] and comp[w] not in out[comp[v]]:
                out[comp[v]].add(comp[w])
                indeg[comp[w]] += 1
    heap = [(min(members[k]), k) for k in members if not indeg[k]]
    heapq.heapify(heap)
    order = []
    while heap:
        _, k = heapq.heappop(heap)
        order.extend(sorted(members[k]))
        for j in out[k]:
            indeg[j] -= 1
            if not indeg[j]:
                heapq.heappush(heap, (min(members[j]), j))
    return order


def evaluate(order, label):
    pos = {v: i for i, v in enumerate(order)}
    fixed, still, broke, flip_code, flip_alloc, flip_data = [], [], [], [], [], []
    for name, cs in copies.items():
        if len(cs) < 2:
            continue
        k = kept.get(name)
        if k is None or k not in prov:
            continue
        today = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
        if today is None:
            continue
        then = min(cs, key=lambda c: pos[c[0]])
        if name in rows and any(c[3] for c in cs):
            if not today[3] and then[3]:
                fixed.append(name)
            elif not today[3]:
                still.append(name)
            elif not then[3]:
                broke.append(name)
        elif today[2] != then[2]:
            (flip_data if DATA.search(name) else flip_alloc if ALLOC.search(name) else flip_code).append(name)
    moved = len(order) - lis(order)
    ini = [v for v in order if crt.get(v)]
    print(f"[{label}] fixed {len(fixed)}; still {len(still)}; broke {len(broke)}; flips: no-row code {len(flip_code)}, no-row allocator-side {len(flip_alloc)}, data {len(flip_data)}; objects moved at least {moved}; initializer objects out of order {len(ini) - lis(ini)}")
    return dict(fixed=fixed, still=still, broke=broke, code=flip_code, alloc=flip_alloc, data=flip_data, moved=moved)


res = {}
for label, a, c in (("rowed + initializers + data frozen", False, False), ("rowed + initializers + data + allocator-side frozen", True, False), ("rowed + initializers + data + all no-row code frozen", False, True)):
    edges, why, named = build(a, c)
    comp = scc(edges)
    sizes = collections.Counter(comp.values())
    big = {k: v for k, v in sizes.items() if v > 1}
    print(f"== {label}: names {named}, edges {sum(len(v) for v in edges.values())}, conflicts {len(big)} covering {sum(big.values())} objects, largest {max(big.values()) if big else 0}")
    for k in sorted(big, key=lambda k: -big[k])[:6]:
        mem = [v for v, x in comp.items() if x == k]
        names = {n for (p, q), ns in why.items() if comp[p] == k and comp[q] == k for n in ns}
        print(f"     {big[k]} objects, {len(names)} names: {[manifest[v].get('source', '')[-30:] for v in mem[:3]]}")
    order = order_of(edges, comp)
    res[label] = evaluate(order, label)
    res[label]["order"] = order
targets = []
for name, cs in copies.items():
    k = kept.get(name)
    if name not in rows or k is None:
        continue
    kc = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
    if kc is None or kc[3]:
        continue
    own_idx = by_source.get(owner.get(name))
    own = next((c for c in cs if c[0] == own_idx), None)
    good = [c for c in cs if c[3]]
    targets.append((name, "owner's copy is retail's" if own and own[3] else ("owner defines it, not retail's" if own else ("another unit has retail's, owner has no copy" if good else "no copy is retail's")), kc[0], own_idx, None))
print("victims on this object set:", len(targets), collections.Counter(x[1] for x in targets).most_common())
target_names = {t[0] for t in targets}
print("names a generated object would beat any owner on:", len(pinned_wins), list(pinned_wins)[:4])
for label, r in res.items():
    print(label, "of the victims: fixed", len(target_names & set(r["fixed"])), "still", len(target_names & set(r["still"])), "out of reach", len(target_names - set(r["fixed"]) - set(r["still"])))
main = res["rowed + initializers + data + allocator-side frozen"]
rd = [n for n in rows if rows[n][0] == 0x8D00]
print("rows at 0x8D00:", [(n[-30:], n in main["fixed"], n in main["still"], n in target_names) for n in rd])
print("wrong-field and allocator controls fixed:", {p[:34]: p in main["fixed"] for p in ("?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z", "?isKindOfMulti@ThingTemplate@@QBE_NABV?$BitFlags@$0HE@@@0@Z") }, "; 0x8D00:", any(rows.get(n, (0,))[0] == 0x8D00 and n in main["fixed"] for n in rows if "_M_range_initialize" in n))
print("still:", [n[:50] for n in main["still"]][:14])
print("no-row code that flips:", [n[:46] for n in main["code"]][:14])
pos = {v: i for i, v in enumerate(main["order"])}
for label, r in res.items():
    seq = r["order"]
    # Objects outside one longest increasing run: the fewest that must change place.
    tails, idxs, prev = [], [], {}
    for x in seq:
        i = bisect.bisect_left(tails, x)
        prev[x] = idxs[i - 1] if i else None
        if i == len(tails):
            tails.append(x)
            idxs.append(x)
        else:
            tails[i] = x
            idxs[i] = x
    keep, cur = set(), idxs[-1]
    while cur is not None:
        keep.add(cur)
        cur = prev[cur]
    mv = [v for v in seq if v not in keep]
    print(f"  {label[:44]:44} must change place: {len(mv)}; of them with initializers {sum(1 for v in mv if crt.get(v))}; one-row-or-few sample {[manifest[v].get('source', '')[-26:] for v in mv[:3]]}")
    r["moved_list"] = [manifest[v].get("source", "") for v in mv]
moved = [v for v in main["order"] if abs(pos[v] - v) > 0]
print("objects at a new index", len(moved), "; rows' objects that genuinely move forward:", sum(pos[v] < v - 0 for v in moved))
back = collections.Counter()
for t in targets:
    back[t[1]] += 1
print("the 258 by what they can supply:", back.most_common())
with open(prefix + ".tsv", "w", encoding="utf-8", newline="") as f:
    w = csv.writer(f, delimiter="\t")
    w.writerow(["scenario", "outcome", "name"])
    for label, r in res.items():
        for key in ("fixed", "still", "broke", "code", "alloc", "data"):
            for n in r[key]:
                w.writerow([label, key, n])
pickle.dump({k: v["order"] for k, v in res.items()}, open(prefix + ".orders.pkl", "wb"))
