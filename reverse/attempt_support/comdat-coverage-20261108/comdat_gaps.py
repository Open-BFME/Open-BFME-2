"""Scratch, read-only: what the masked comparison misses or mislabels, and the ranked picture. usage: comdat_gaps.py IMAGE_DIR GROUPS_TSV CLASSES_TSV KEPT_WRONG_TSV"""
import collections
import csv
import json
import multiprocessing
import re
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import link_census as lc

csv.field_size_limit(10**8)
image_dir, groups_tsv, classes_tsv, wrong_tsv = sys.argv[1:5]
image = Path(image_dir) / "image"
FAMILY = re.compile(r"__new_alloc|__node_alloc|_Node_alloc|__sgi_alloc|__malloc_alloc")
P63 = "?allocate@?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@QBEPAUPrereqUnitRec@ProductionPrerequisite@@IPBX@Z"


def tname(r):
    return r[2]["name"] if isinstance(r[2], dict) else str(r[2])


def read(job):
    path, idx = job
    rows = []
    data = Path(path).read_bytes()
    for symbol, body, relocs, digest, size in lc._comdat_sections(data):
        if body is None:
            continue
        hits = sorted({tname(r)[:60] for r in relocs if FAMILY.search(tname(r))})
        if hits:
            rows.append((symbol["name"], idx, hits, len(body)))
    return rows


if __name__ == "__main__":
    groups = {r["name"]: r for r in csv.DictReader(open(groups_tsv, encoding="utf-8"), delimiter="\t")}
    classes = list(csv.DictReader(open(classes_tsv, encoding="utf-8"), delimiter="\t"))
    wrong = {r["name"]: r for r in csv.DictReader(open(wrong_tsv, encoding="utf-8"), delimiter="\t")}
    bad = {r["name"] for r in classes}
    print("control P63:", {k: groups[P63][k] for k in ("kind", "copies", "distinct", "maj_n", "kept_vs", "kept_src")} if P63 in groups else "absent")
    ties = [r for r in groups.values() if not r["rva"] and r["kept_vs"] == "majority" and r["kind"] == "bytes" and int(r["maj_n"]) * 2 <= int(r["copies"])]
    print("no row, labelled majority but no copy has more than half:", len(ties), "of", sum(not r["rva"] and r["kept_vs"] == "majority" and r["kind"] == "bytes" for r in groups.values()))
    for r in sorted(ties, key=lambda r: -int(r["refs"]))[:10]:
        print(f"   {r['refs']:>4} c{r['copies']:<3} d{r['distinct']:<2} {r['name'][:66]:66} {r['kept_src'][-30:]}")
    miss = {n: r for n, r in wrong.items() if n not in bad}
    print("census kept-wrong not in the kept-differs set:", len(miss))
    print("   copies per name:", sorted(collections.Counter(min(int(r["copies"]), 3) for r in miss.values()).items()), "(3 = 3 or more)")
    print("   of which in the differ groups at all:", sum(n in groups for n in miss), "; labelled there", collections.Counter(re.sub(r"\d+ of \d+", "N", groups[n]["kept_vs"]) for n in miss if n in groups).most_common())
    print("   retail copy exists:", sum(int(r["retail_copies"]) > 0 for r in miss.values()), "on walk:", sum(r["order"] != "" for r in miss.values()), "code:", sum(r["kind"] == "code" for r in miss.values()))
    for r in sorted(miss.values(), key=lambda r: -int(r["referencing_objects"]))[:12]:
        print(f"   {r['referencing_objects']:>4} c{r['copies']:<3} rc{r['retail_copies']:<2} {r['rva']:>9} o{r['order']:<6} {r['kind']:4} {r['name'][:62]:62} {r['kept_object'][-26:]}")
    manifest = json.load(open(image / "image_objects.json", encoding="utf-8"))
    jobs = [(str(image / e["path"].replace("\\", "/")), i) for i, e in enumerate(manifest)]
    with multiprocessing.Pool(4) as pool:
        res = pool.map(read, jobs, chunksize=64)
    fam = collections.defaultdict(list)
    for rows in res:
        for name, idx, hits, size in rows:
            fam[name].append((manifest[idx].get("source", "")[-44:], hits, size))
    print("COMDATs anywhere whose copy names a pool or stock allocator:", len(fam), "copies", sum(len(v) for v in fam.values()))
    kept_map = {}
    for line in open(image / "exit.map", errors="replace"):
        m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(i\s+)?(\S+)", line)
        if m and m.group(1) in fam:
            kept_map.setdefault(m.group(1), m.group(5))
    print("  of those names in the image's map:", len(kept_map))
    def key(s):
        return re.sub(r"[A-Z]", lambda m: "^" + m.group(0).lower(), s.replace("/", "_"))[-30:]
    kept_fam = []
    for name, obj in kept_map.items():
        for src, hits, size in fam[name]:
            if key(src.rsplit(".", 1)[0]) in obj:
                kept_fam.append((name, src, hits, size))
                break
    print("  kept copy is one of those:", len(kept_fam))
    for name, src, hits, size in sorted(kept_fam, key=lambda x: x[0])[:24]:
        print(f"    {name[:70]:70} {size:>4}B {hits[0][:34]:34} {src[-26:]}")
    print("== by references, excluding frame-or-EH-only")
    live = [r for r in classes if r["cls"] != "frame or EH only"]
    live.sort(key=lambda r: -int(r["refs"]))
    print("class x references>0:", sorted(collections.Counter((r["cls"], int(r["refs"]) > 0) for r in classes).items()))
    print("kept_vs x references>0:", sorted(collections.Counter((re.sub(r"\d+ of \d+", "N", r["kept_vs"]), int(r["refs"]) > 0) for r in classes).items()))
    for r in live[:26]:
        print(f"{r['refs']:>5} {r['cls'][:22]:22} {r['kept_vs'][:16]:16} fl={r['flags'][:6]:6} {r['rva']:>9} o{str(r['order'])[:6]:6} w={r['census_wrong'][:1]} ref[{r['only_ref'][:14]}] kept[{r['only_kept'][:14]}] {r['name'][:44]:44} {r['kept_src'][-22:]}")
