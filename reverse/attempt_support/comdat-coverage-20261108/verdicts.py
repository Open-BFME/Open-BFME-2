"""Read-only: names whose kept copy the census judged wrong. Joins build/link_census/link_index.pkl (verdicts) with one image's map (what was kept). usage: verdicts.py IMAGE_MAP WALK_TSV FUNCTIONS_CSV OUT"""
import collections
import csv
import pickle
import re
import sys

csv.field_size_limit(10**8)
image_map, walk_tsv, functions_csv, out = sys.argv[1:5]
p = pickle.load(open("build/link_census/link_index.pkl", "rb"))
print("index meta", {k: str(v)[:40] for k, v in p["meta"].items()})
objs = p["objects"]
comdat = p["comdat"]
kept = {}
for line in open(image_map, errors="replace"):
    m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(i\s+)?(\S+)", line)
    if m:
        kept.setdefault(m.group(1), (m.group(5), int(m.group(2), 16)))
rows = {}
for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
    rows.setdefault(r["name"], r)
walk = {}
for r in csv.DictReader(open(walk_tsv, encoding="utf-8"), delimiter="\t"):
    try:
        walk[int(r["rva"], 16)] = (int(r["order"]), r["anchor"], r["tier"])
    except (KeyError, ValueError):
        pass
edges = p["references"]["edges"]
print("edges sample", str(list(edges.items())[:1])[:220])
called = collections.Counter()
for src, targets in edges.items():
    for t in targets:
        called[t] += 1
tally = collections.Counter()
listed = []
for name, entries in comdat.items():
    verdicts = [e[2] for e in entries]
    if "wrong" not in verdicts:
        continue
    tally["names with a wrong copy"] += 1
    k = kept.get(name)
    if k is None:
        tally["not in the map"] += 1
        continue
    match = [e for e in entries if objs[e[0]][-44:] == k[0][-44:]]
    if not match:
        tally["kept object not in the index's copies"] += 1
        continue
    v = match[0][2]
    tally[f"kept copy judged {v}"] += 1
    if v != "wrong":
        continue
    retail_copies = [e for e in entries if e[2] == "retail"]
    if retail_copies:
        tally["kept wrong, a retail copy exists"] += 1
    else:
        tally["kept wrong, no copy is retail"] += 1
    row = rows.get(name)
    rva = None
    if row:
        try:
            rva = int(row["target_rva"], 16)
        except ValueError:
            pass
    w = walk.get(rva)
    data = bool(re.search(r"^\?\?_[78]|@@[0-9][A-Z_]|@@3", name))
    listed.append((called[name], name, len(entries), len(retail_copies), f"{rva:#x}" if rva is not None else "", w[0] if w else "", w[2] if w else "", "data" if data else "code", k[0][-48:], (row or {}).get("source", "")[-48:]))
print(dict(tally))
listed.sort(key=lambda r: -r[0])
with open(out, "w", encoding="utf-8", newline="") as f:
    w = csv.writer(f, delimiter="\t")
    w.writerow(["referencing_objects", "name", "copies", "retail_copies", "rva", "order", "tier", "kind", "kept_object", "row_source"])
    w.writerows(listed)
print("kept wrong:", len(listed), "code", sum(r[7] == "code" for r in listed), "data", sum(r[7] == "data" for r in listed), "on the boot walk", sum(r[5] != "" for r in listed))
for r in listed[:40]:
    print(f"{r[0]:>5} c{r[2]:<3} rc{r[3]:<2} {r[4]:>9} o{str(r[5]):6} t{str(r[6]):2} {r[7]:4} {r[1][:64]:64} {r[8][-34:]}")
