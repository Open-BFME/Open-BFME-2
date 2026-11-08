"""Scratch, read-only: could one object order make the link keep every row's verified COMDAT copy? Offline, from an image's linked objects and its map. Links nothing.
Tests the rule first: the map's kept copy against the first definer in manifest order. Then builds constraints, solves one order, and reports what it would flip.
usage: order_sim.py IMAGE_DIR FUNCTIONS_CSV GAME_DAT OUT_PREFIX"""
import collections
import csv
import hashlib
import heapq
import json
import multiprocessing
import pickle
import re
import struct
import sys
from pathlib import Path

import pefile

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
FIELD = {0xA: 2}
G = {}


def init(rows, game_dat):
    G["rows"] = rows
    G["retail"] = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()


def tname(r):
    return r[2]["name"] if isinstance(r[2], dict) else str(r[2])


def read(job):
    path, idx = job
    data = Path(path).read_bytes()
    out, crt = [], 0
    nsec = struct.unpack_from("<H", data, 2)[0]
    opt = struct.unpack_from("<H", data, 16)[0]
    symptr, nsym = struct.unpack_from("<II", data, 8)
    strtab = symptr + nsym * 18
    for i in range(nsec):
        h = 20 + opt + 40 * i
        nm = data[h:h + 8].rstrip(b"\0").decode("latin-1")
        if nm.startswith("/"):
            off = int(nm[1:])
            nm = data[strtab + off:data.index(b"\0", strtab + off)].decode("latin-1")
        if nm.startswith(".CRT$XC"):
            crt += 1
    for symbol, body, relocs, digest, size in lc._comdat_sections(data):
        name = symbol["name"]
        if body is None:
            continue
        b = bytearray(body)
        for r in relocs:
            for k in range(r[0], min(r[0] + FIELD.get(r[1], 4), len(b))):
                b[k] = 0
        m = bytes(b).rstrip(b"\xcc\x90")
        h1 = hashlib.sha1(m).hexdigest()[:14]
        targets = sorted({tname(r) for r in relocs if not tname(r).startswith(("$", "__ehhandler", "_$", "??_C@", "__real@"))})
        h2 = hashlib.sha1((h1 + "|".join(targets)).encode("latin-1", "replace")).hexdigest()[:14]
        row = G["rows"].get(name)
        match = None
        if row:
            rva, rsize = row[0], row[1]
            t = bytearray(G["retail"][rva:rva + max(rsize, 1)])
            for r in relocs:
                for k in range(r[0], min(r[0] + FIELD.get(r[1], 4), len(t))):
                    t[k] = 0
            n = min(len(b), rsize)
            match = bytes(b[:n]) == bytes(t[:n]) and bytes(b[n:]).strip(b"\xcc\x90") == b""
        out.append((name, h1, h2, match))
    return idx, out, crt


def main():
    image_dir, functions_csv, game_dat, prefix = sys.argv[1:5]
    image = Path(image_dir) / "image"
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    rows = {}
    owner = {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        try:
            v = (int(r["target_rva"], 16), int(r["target_size"], 0))
        except ValueError:
            continue
        rows.setdefault(r["name"], v)
        owner.setdefault(r["name"], r["source"])
        m = re.search(r"object-symbol=(\S+?)(;|\s|$)", r.get("notes") or "")
        if m:
            rows.setdefault(m.group(1), v)
            owner.setdefault(m.group(1), r["source"])
    kept = {}
    for line in open(image / "exit.map", errors="replace"):
        m = re.match(r"\s*([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$", line)
        if m and int(m.group(1), 16) > 0:
            kept.setdefault(m.group(3), m.group(5))
    prov = {e["provider"]: i for i, e in enumerate(manifest)}
    by_source = {e.get("source"): i for i, e in enumerate(manifest)}
    jobs = [(str(image / e["path"].replace("\\", "/")), i) for i, e in enumerate(manifest)]
    with multiprocessing.Pool(4, init, (rows, game_dat)) as pool:
        res = pool.map(read, jobs, chunksize=48)
    copies = collections.defaultdict(list)
    crt = {}
    for idx, out, c in res:
        crt[idx] = c
        for name, h1, h2, match in out:
            copies[name].append((idx, h1, h2, match))
    pickle.dump(dict(copies=dict(copies), crt=crt, manifest=manifest, kept=kept, rows=rows, owner=owner), open(prefix + ".pkl", "wb"))
    print("objects", len(jobs), "with .CRT$XC sections", sum(1 for v in crt.values() if v), "COMDAT names", len(copies), "with 2+ copies", sum(len(v) > 1 for v in copies.values()))

    # 1. Is the manifest the link's order, and does the first definer win?
    tested = wrong_first = 0
    misses = []
    for name, cs in copies.items():
        k = kept.get(name)
        if k is None or len(cs) < 2:
            continue
        tested += 1
        first = min(c[0] for c in cs)
        if manifest[first]["provider"] != k:
            wrong_first += 1
            if len(misses) < 8:
                misses.append((name[:60], manifest[first]["provider"][-34:], k[-34:]))
    print(f"RULE names with 2+ copies in the map {tested}: kept is first in manifest order for {tested - wrong_first}, not for {wrong_first}")
    for m in misses:
        print("   ", m)

    # 2. The rowed names that keep a non-retail copy today, and whether the owner could supply it.
    state = collections.Counter()
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
        cat = "owner's copy is retail's" if own and own[3] else ("owner defines it, not retail's" if own else ("another unit has retail's, owner no copy" if good else "no copy is retail's"))
        state[cat] += 1
        targets.append((name, cat, kc[0], own_idx, good[0][0] if good else None))
    print("rowed names keeping a non-retail COMDAT:", len(targets), state.most_common())
    pickle.dump(targets, open(prefix + ".targets.pkl", "wb"))

    # 3. Hard constraints: every rowed name with a retail copy must keep one.
    def constraints(freeze_all):
        edges = collections.defaultdict(set)
        why = collections.defaultdict(set)
        n_names = 0
        for name, cs in copies.items():
            if len({c[2] for c in cs}) < 2:
                continue
            if name in rows and any(c[3] for c in cs):
                own_idx = by_source.get(owner.get(name))
                good = [c for c in cs if c[3]]
                rep = next((c[0] for c in good if c[0] == own_idx), min(c[0] for c in good))
                bad_hash = {c[2] for c in good}
                diff = [c[0] for c in cs if c[2] not in bad_hash]
            elif freeze_all and name in kept:
                k = kept[name]
                keeper = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
                if keeper is None:
                    continue
                rep = keeper[0]
                diff = [c[0] for c in cs if c[2] != keeper[2]]
            else:
                continue
            if diff:
                n_names += 1
            for d in diff:
                if d != rep:
                    edges[rep].add(d)
                    why[(rep, d)].add(name)
        return edges, why, n_names

    def solve(edges):
        n = len(manifest)
        # Tarjan, iterative: cycles are conflicts no order can satisfy.
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
        sizes = collections.Counter(comp.values())
        scc = {k: v for k, v in sizes.items() if v > 1}
        # Kahn over the condensation, smallest current position first, so objects move as little as possible.
        members = collections.defaultdict(list)
        for v, k in comp.items():
            members[k].append(v)
        indeg = collections.Counter()
        out = collections.defaultdict(set)
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
        return order, scc, comp

    def lis_len(seq):
        import bisect
        tails = []
        for x in seq:
            i = bisect.bisect_left(tails, x)
            if i == len(tails):
                tails.append(x)
            else:
                tails[i] = x
        return len(tails)

    def evaluate(order, label, why, comp):
        pos = {v: i for i, v in enumerate(order)}
        fixed = still = broke = 0
        broke_list, still_list = [], []
        flips_norow_code = flips_norow_data = flips_same_hash = 0
        norow_list, data_list = [], []
        for name, cs in copies.items():
            if len(cs) < 2:
                continue
            today = min(cs, key=lambda c: c[0])
            then = min(cs, key=lambda c: pos[c[0]])
            k = kept.get(name)
            if k is not None:
                t = next((c for c in cs if manifest[c[0]]["provider"] == k), None)
                today = t or today
            if name in rows and any(c[3] for c in cs):
                if not today[3] and then[3]:
                    fixed += 1
                elif not today[3] and not then[3]:
                    still += 1
                    still_list.append(name)
                elif today[3] and not then[3]:
                    broke += 1
                    broke_list.append(name)
                continue
            if today[2] != then[2]:
                data = bool(re.search(r"^\?\?_[78]|@@[0-9][A-Z_]|@@3|^\?\?_R|^__real|^\?\?_C", name))
                if data:
                    flips_norow_data += 1
                    data_list.append(name)
                else:
                    flips_norow_code += 1
                    norow_list.append(name)
        moved = len(order) - lis_len(order)
        moved_set = set(order)
        # Objects whose relative order changed: everything outside a longest increasing run.
        print(f"[{label}] fixed {fixed}; still wrong {still}; newly wrong rowed {broke}; no-row code copies that flip {flips_norow_code}; data copies that flip {flips_norow_data}; objects moved at least {moved}")
        # Initializer order among objects holding .CRT$XC sections.
        seq = [v for v in order if crt.get(v)]
        print(f"   objects with .CRT$XC sections {len(seq)}; moved relative to each other at least {len(seq) - lis_len(seq)}")
        for n in still_list[:8]:
            print("     still", n[:90])
        for n in broke_list[:8]:
            print("     broke", n[:90])
        for n in data_list[:10]:
            print("     data flip", n[:90])
        for n in norow_list[:10]:
            print("     no-row flip", n[:90])
        return dict(fixed=fixed, still=still_list, broke=broke_list, norow=norow_list, data=data_list, moved=moved)

    result = {}
    for label, freeze in (("rowed names only", False), ("rowed names, and every other name frozen as kept today", True)):
        edges, why, n_names = constraints(freeze)
        nedges = sum(len(v) for v in edges.values())
        order, scc, comp = solve(edges)
        print(f"== {label}: names constrained {n_names}, edges {nedges}, objects in cycles {sum(scc.values())} across {len(scc)} conflicts; largest {max(scc.values()) if scc else 0}")
        conflict = sorted(scc, key=lambda k: -scc[k])[:5]
        for k in conflict:
            mem = [v for v, c in comp.items() if c == k]
            names = {n for (a, b), ns in why.items() if comp[a] == k and comp[b] == k for n in ns}
            print(f"   conflict of {scc[k]} objects, {len(names)} names; e.g. {[manifest[v].get('source', '')[-34:] for v in mem[:3]]} {[n[:44] for n in list(names)[:2]]}")
        result[label] = evaluate(order, label, why, comp)
        result[label]["order"] = order
    pickle.dump(result, open(prefix + ".result.pkl", "wb"))
    with open(prefix + ".out.tsv", "w", encoding="utf-8", newline="") as f:
        w = csv.writer(f, delimiter="\t")
        for label, r in result.items():
            for key in ("still", "broke", "norow", "data"):
                for n in r[key]:
                    w.writerow([label, key, n])


if __name__ == "__main__":
    main()
