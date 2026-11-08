"""Scratch, read-only: add objects on the real command line that the image's manifest lacks, from a worker seat's build/match, in response-file order. Writes OUT.pkl for order_sim2.py and reports them.
usage: order_extra.py SIM.pkl SEAT FUNCTIONS_CSV GAME_DAT OUT.pkl"""
import collections
import csv
import multiprocessing
import os
import pickle
import sys
from pathlib import Path

sys.path.insert(0, "tools")
sys.path.insert(0, "build")
import build as B
import order_sim as S

csv.field_size_limit(10**8)
if __name__ == "__main__":
    sim, seat, functions_csv, game_dat, out = sys.argv[1:6]
    seat = Path(seat)
    d = pickle.load(open(sim, "rb"))
    copies, crt, manifest, kept, rows, owner = d["copies"], d["crt"], d["manifest"], d["kept"], d["rows"], d["owner"]
    rsp = [l.strip().strip('"') for l in open(seat / "build/diagnostic_link/exit.rsp", encoding="utf-8")]
    rsp = [x for x in rsp if x.lower().endswith(".obj")]
    prov = {e["provider"]: i for i, e in enumerate(manifest)}
    src_of = {}
    for r in csv.DictReader(open(functions_csv, encoding="utf-8", errors="replace", newline="")):
        src_of.setdefault(B.row_object(r).name, r["source"])
    base = [os.path.basename(x) for x in rsp]
    extras = [(x, os.path.basename(x)) for x in rsp if os.path.basename(x) not in prov]
    print("command-line objects", len(rsp), "; not in the manifest", len(extras), "; with a row's source", sum(b in src_of for _, b in extras))
    jobs, new_entries = [], []
    for x, b in extras:
        p = seat / x
        if p.exists():
            jobs.append((str(p), len(manifest) + len(new_entries)))
            new_entries.append(dict(path="", source=src_of.get(b, ""), provider=b, extra=True))
    print("readable on the seat:", len(jobs))
    with multiprocessing.Pool(4, S.init, (rows, game_dat)) as pool:
        res = pool.map(S.read, jobs, chunksize=16)
    added = collections.Counter()
    for idx, out_rows, c in res:
        crt[idx] = c
        for name, h1, h2, match in out_rows:
            copies.setdefault(name, []).append((idx, h1, h2, match))
            added["copies"] += 1
    full = manifest + new_entries
    index = {e["provider"]: i for i, e in enumerate(full)}
    ordered = [index[b] for b in base if b in index]
    seen = set(ordered)
    ordered += [i for i in range(len(full)) if i not in seen]
    remap = {old: new for new, old in enumerate(ordered)}
    full2 = [full[old] for old in ordered]
    copies2 = {n: [(remap[c[0]], c[1], c[2], c[3]) for c in cs] for n, cs in copies.items()}
    crt2 = {remap[k]: v for k, v in crt.items()}
    pickle.dump(dict(copies=copies2, crt=crt2, manifest=full2, kept=kept, rows=rows, owner=owner), open(out, "wb"))
    prov2 = {e["provider"]: i for i, e in enumerate(full2)}
    # The rule again: on the real order, first kept?
    tested = bad = 0
    miss = []
    for name, cs in copies2.items():
        k = kept.get(name)
        if k is None or len(cs) < 2:
            continue
        tested += 1
        first = min(c[0] for c in cs)
        if full2[first]["provider"] != k:
            bad += 1
            miss.append((name, full2[first]["provider"], k, full2[first].get("extra", False)))
    print(f"RULE on the command-line order, extras in: {tested} names; first kept for {tested - bad}; not for {bad}; of those the first is an added object {sum(m[3] for m in miss)}")
    for m in miss[:10]:
        print("   ", m[0][:56], "first", m[1][-34:], "kept", m[2][-30:])
    extra_names = collections.Counter()
    undercount = []
    for name, cs in copies2.items():
        k = kept.get(name)
        if k is None or name not in rows:
            continue
        kc = next((c for c in cs if full2[c[0]]["provider"] == k), None)
        if kc is None or kc[3]:
            continue
        good = [c for c in cs if c[3]]
        if any(full2[c[0]].get("extra") for c in good):
            undercount.append(name)
    print("rowed names keeping a non-retail copy where only an added object has retail's:", len(undercount))
    for n in undercount[:12]:
        print("   ", n[:80])
    name = "??$_M_range_initialize@PAD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEXPAD0@Z"
    print("0x8D00 copies:", [(full2[c[0]]["provider"][-40:], c[0], c[3]) for c in copies2.get(name, [])])
    owner_prov = [e for e in full2 if e.get("source", "").endswith("range_init_2arg.cpp")]
    print("0x8D00 owner on the command line:", [(e["provider"][-48:], prov2[e["provider"]]) for e in owner_prov], "; money_put at", [prov2[e["provider"]] for e in full2 if e["provider"].endswith("narrow^money^put^string.obj") or "narrow_money_put_string" in e["provider"]])
