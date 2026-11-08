"""Read-only: a random sample from the anchored list, each with its chain and differing instructions.
usage (worktree at the image's commit): cs_sample.py IMAGE_DIR GAME_DAT PREFIX SEED N [FILTER: layout|same|all] [boot|all]"""
import csv
import difflib
import random
import re
import sys

import capstone
import pefile

image_dir, game_dat, prefix, seed, n = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4]), int(sys.argv[5])
filt = sys.argv[6] if len(sys.argv) > 6 else "layout"
scope = sys.argv[7] if len(sys.argv) > 7 else "boot"
ret = pefile.PE(game_dat, fast_load=True).get_memory_mapped_image()
img = pefile.PE(image_dir + "/image/exit.exe", fast_load=True).get_memory_mapped_image()
syms, objs = {}, {}
for line in open(image_dir + "/image/exit.map", errors="replace"):
    m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(.*)", line)
    if m:
        va = int(m.group(2), 16)
        syms.setdefault(va, m.group(1))
        objs.setdefault(va, m.group(3).strip()[-60:])
rrow = {}
for r in csv.DictReader(open("reverse/functions.csv", encoding="utf-8", errors="replace", newline="")):
    try:
        rrow.setdefault(int(r["target_rva"], 16), r["name"])
    except ValueError:
        pass
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def stream(code, va, namer):
    out = []
    for _a, _s, mn, ops in md.disasm_lite(code, va):
        def sub(m):
            nm = namer(int(m.group(0), 16))
            return nm[:40] if nm else "A"
        out.append(f"{mn} L" if mn.startswith("j") else f"{mn} " + re.sub(r"0x[0-9a-f]{6,}", sub, ops))
    return out


R = list(csv.DictReader(open(prefix + ".anchored.tsv", encoding="utf-8", errors="replace"), delimiter="\t"))
if scope == "boot":
    R = [r for r in R if r["anchor"] != "unreached"]
if filt == "layout":
    R = [r for r in R if r["layout"] != "same"]
elif filt == "same":
    R = [r for r in R if r["layout"] == "same"]
elif filt.startswith("0x"):
    R = [r for r in R if r["retail_rva"] in filt.split(",")]
print(len(R), "in scope")
random.seed(seed)
for r in random.sample(R, min(n, len(R))):
    A, S, T, ext = int(r["retail_rva"], 16), int(r["size"]), int(r["image_rva"], 16), int(r["extent"])
    print(f"\n### {r['kind']} retail {A:#x} +{S} {rrow.get(A, '?')[:88]}\n    image {T:#x} +{ext} {syms.get(T + 0x10000000, '?')[:88]}\n    obj {objs.get(T + 0x10000000, '')}")
    print(f"    tags={r['tags']} layout={r['layout']} only_r={r['only_retail']} only_i={r['only_image']} root={r['root_name'][:60]} t{r['tier']}")
    for hop in r["chain"].split(" < ")[:4]:
        if hop:
            print(f"    via {hop} {rrow.get(int(hop.split('+')[0], 16), '?')[:84]}")
    a = stream(ret[A:A + S], A + 0x400000, lambda v: rrow.get(v - 0x400000, ""))
    b = stream(img[T:T + ext], T + 0x10000000, lambda v: syms.get(v, ""))
    while b and b[-1].startswith(("int3", "nop")):
        b.pop()
    shown = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        for k in range(max(i2 - i1, j2 - j1)):
            if shown < 10:
                print(f"    {a[i1 + k] if i1 + k < i2 else '':<50} | {b[j1 + k] if j1 + k < j2 else ''}"[:118])
            shown += 1
    if shown >= 10:
        print(f"    ... {shown} lines, {len(a)} vs {len(b)} instructions")
