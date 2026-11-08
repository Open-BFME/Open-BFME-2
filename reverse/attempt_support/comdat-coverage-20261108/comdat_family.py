"""Scratch, read-only: the kept COMDAT copies that name a pool or stock allocator: by source, allocator, whether anything references them, and whether allocate and free sides disagree per element type. usage: comdat_family.py IMAGE_DIR FUNCTIONS_CSV OUT_TSV"""
import collections
import csv
import json
import multiprocessing
import pickle
import re
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
image_dir, functions_csv, out = sys.argv[1:4]
image = Path(image_dir) / "image"
FAMILY = re.compile(r"\?(de)?allocate@(\?\$__node_alloc|__new_alloc|\?\$__malloc_alloc|__sgi_alloc|_Node_alloc)")


def tname(r):
    return r[2]["name"] if isinstance(r[2], dict) else str(r[2])


def read(job):
    path, idx = job
    rows = []
    data = Path(path).read_bytes()
    for symbol, body, relocs, digest, size in lc._comdat_sections(data):
        if body is None:
            continue
        hits = sorted({tname(r) for r in relocs if FAMILY.search(tname(r))})
        if hits:
            rows.append((symbol["name"], idx, hits, len(body)))
    return rows


if __name__ == "__main__":
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    jobs = [(str(image / e["path"].replace("\\", "/")), i) for i, e in enumerate(manifest)]
    with multiprocessing.Pool(4) as pool:
        res = pool.map(read, jobs, chunksize=64)
    fam = collections.defaultdict(list)
    for rows in res:
        for name, idx, hits, size in rows:
            fam[name].append((manifest[idx].get("source", ""), hits, size))
    kept = {}
    for line in open(image / "exit.map", errors="replace"):
        m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(i\s+)?(\S+)", line)
        if m and m.group(1) in fam:
            kept.setdefault(m.group(1), m.group(5))
    rows = {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        rows.setdefault(r["name"], r)
    idx = pickle.load(open("build/link_census/link_index.pkl", "rb"))
    referenced = idx["references"]["referenced"]
    comdat = idx["comdat"]
    objs = idx["objects"]

    def key(s):
        return re.sub(r"[A-Z]", lambda m: "^" + m.group(0).lower(), s.replace("/", "_").replace("\\", "_")).rsplit(".", 1)[0]

    out_rows = []
    for name, obj in kept.items():
        hit = next((c for c in fam[name] if obj.endswith(key(c[0])[-40:] + ".obj")), None)
        if not hit:
            continue
        sides = {"alloc" if h.startswith("?allocate") else "free" for h in hit[1]}
        which = sorted({re.sub(r"^\?(de)?allocate@(\?\$)?", "", h).split("@")[0] for h in hit[1]})
        verdict = next((e[2] for e in comdat.get(name, []) if objs[e[0]].endswith(key(hit[0])[-40:] + ".obj")), None)
        out_rows.append(dict(name=name, source=hit[0], allocators=",".join(which), sides=",".join(sorted(sides)), referenced=name in referenced,
                             row=(rows[name]["target_rva"] if name in rows else ""), verdict=verdict or "", size=hit[2]))
    with open(out, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, list(out_rows[0]), delimiter="\t")
        w.writeheader()
        w.writerows(out_rows)
    print("kept copies naming a pool or stock allocator:", len(out_rows))
    print("referenced by something the link keeps:", sum(r["referenced"] for r in out_rows), "; with a row:", sum(bool(r["row"]) for r in out_rows))
    print("by allocator:", collections.Counter(r["allocators"] for r in out_rows).most_common(6))
    print("by side:", collections.Counter(r["sides"] for r in out_rows).most_common())
    print("census verdict:", collections.Counter(r["verdict"] or "none" for r in out_rows).most_common())
    print("referenced, by source:", collections.Counter(r["source"].rsplit("/", 1)[-1] for r in out_rows if r["referenced"]).most_common(10))
    for r in sorted([x for x in out_rows if x["referenced"]], key=lambda x: (not x["row"], x["name"]))[:16]:
        print(f"   {r['row'] or '-':>10} {r['verdict'] or '-':8} {r['allocators'][:14]:14} {r['sides']:10} {r['name'][:64]:64} {r['source'].rsplit('/', 1)[-1][:28]}")
