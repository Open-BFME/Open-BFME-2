"""Read-only: compare a diagnostic image's calls with retail's, in step, from every address whose row has one body.
Readme beside this file. usage: python3 callee_scan.py IMAGE_DIR LEDGER_DIR GAME_DAT OUT_PREFIX

OUT_PREFIX.anchored.tsv is the result. The per-address files (.different, .rows, .sites, .identical, .other) compare every name at
an address whether or not a real caller reaches it, so they carry the template-name noise the anchored walk removes.
"""
import bisect
import collections
import csv
import difflib
import json
import re
import struct
import sys
from pathlib import Path

import capstone
import pefile

image_dir, ledger, game_dat, out = Path(sys.argv[1]), Path(sys.argv[2]), sys.argv[3], sys.argv[4]
RBASE = 0x400000
csv.field_size_limit(10**8)


def flat(path):
    pe = pefile.PE(path, fast_load=True)
    text = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".text")
    return (pe.get_memory_mapped_image(), pe.OPTIONAL_HEADER.ImageBase, pe.OPTIONAL_HEADER.SizeOfImage,
            text.VirtualAddress, text.VirtualAddress + text.Misc_VirtualSize)


ret, _, RSIZE, RT0, RT1 = flat(game_dat)
img, IBASE, ISIZE, IT0, IT1 = flat(str(image_dir / "image/exit.exe"))
print(f"retail .text {RT0:#x}-{RT1:#x}; image base {IBASE:#x} .text {IT0:#x}-{IT1:#x}", file=sys.stderr)

# ---- ledger
rows_at = collections.defaultdict(list)
for r in csv.DictReader(open(ledger / "functions.csv", encoding="utf-8", errors="replace", newline="")):
    try:
        a, s = int(r["target_rva"], 16), int(r["target_size"] or 0)
    except ValueError:
        continue
    if s > 0:
        rows_at[a].append(r)
size_at = {a: max(int(r["target_size"]) for r in rs) for a, rs in rows_at.items()}
starts = sorted(size_at)
names_at = {a: {r["name"] for r in rs} for a, rs in rows_at.items()}


def row_containing(rva):
    i = bisect.bisect_right(starts, rva) - 1
    for j in range(i, max(i - 6, -1), -1):
        if starts[j] <= rva < starts[j] + size_at[starts[j]]:
            return starts[j]
    return None


# ---- map
sym_rows = []
MAP = re.compile(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(?:i\s+)?(\S*)")
for line in open(image_dir / "image/exit.map", errors="replace"):
    m = MAP.match(line)
    if m:
        va = int(m.group(2), 16)
        if IBASE + IT0 <= va < IBASE + IT1:
            sym_rows.append((va - IBASE, m.group(1), m.group(4)))
inames = collections.defaultdict(list)
by_name = collections.defaultdict(list)
for rva, n, obj in sym_rows:
    inames[rva].append(n)
    by_name[n].append((rva, obj))
istarts = sorted(inames)


def isym(rva):
    i = bisect.bisect_right(istarts, rva) - 1
    return istarts[i] if i >= 0 else None


def iextent(rva):
    i = bisect.bisect_right(istarts, rva)
    return (istarts[i] if i < len(istarts) else IT1) - rva


stubs = set()
for line in open(image_dir / "stubbed.tsv", errors="replace"):
    stubs.add(line.split("\t")[0])
provider = {}
objs = json.load(open(image_dir / "image/image_objects.json"))
for o in objs:
    provider[o.get("source", "")] = o.get("provider", "")
print(f"rows at {len(starts)} addresses; map {len(sym_rows)} text symbols; stubs {len(stubs)}", file=sys.stderr)

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.skipdata = False


def in_r(v):
    return RBASE <= v < RBASE + RSIZE


def in_i(v):
    return IBASE <= v < IBASE + ISIZE


def rtext(v):
    return RT0 <= v < RT1


def itext(v):
    return IT0 <= v < IT1


def compare(R, T, S):
    """(residual byte differences, first differing offset, [(kind, offset, retail target, image target)]) comparing retail [R,R+S) and image [T,T+S)."""
    rb, ib = ret[R:R + S], img[T:T + S]
    if len(ib) < S:
        return S, 0, []
    masked = bytearray(S)
    pairs = []
    for addr, size, _mn, _ops in md.disasm_lite(rb, R):
        o = addr - R
        at = None
        if rb[o] in (0xE8, 0xE9) and size == 5:
            at = o + 1
        elif rb[o] == 0x0F and 0x80 <= rb[o + 1] <= 0x8F and size == 6:
            at = o + 2
        if at is None or ib[o:at] != rb[o:at]:
            continue
        rt = R + o + size + struct.unpack_from("<i", rb, at)[0]
        it = T + o + size + struct.unpack_from("<i", ib, at)[0]
        if R <= rt < R + S:
            continue  # internal, compared raw
        if rtext(rt) and itext(it):
            for k in range(at, at + 4):
                masked[k] = 1
            pairs.append(("call" if rb[o] == 0xE8 else "jmp", o, rt, it))
    p, diffs, first = 0, 0, None
    while p < S:
        if masked[p] or rb[p] == ib[p]:
            p += 1
            continue
        hit = None
        for w in range(min(p, S - 4), max(p - 3, 0) - 1, -1):
            if any(masked[w:w + 4]):
                continue
            rv = struct.unpack_from("<I", rb, w)[0]
            iv = struct.unpack_from("<I", ib, w)[0]
            if in_r(rv) and in_i(iv):
                hit = (w, rv - RBASE, iv - IBASE)
                break
        if hit:
            w, rv, iv = hit
            for k in range(w, w + 4):
                masked[k] = 1
            if rtext(rv) and itext(iv) and not R <= rv < R + S:
                pairs.append(("addr", w, rv, iv))
            continue
        diffs += 1
        if first is None:
            first = p
        p += 1
    return diffs, first, pairs


# ---- row bodies
row_classes = collections.Counter()
row_problems = []
pair_sites = collections.defaultdict(list)  # (rt, it) -> [(caller retail rva, offset, kind)]
scanned = {}  # (R, T) -> residual differences
queue = []
FUNCLET = re.compile(r"^(Unwind@|uw_|\$L\d|__unwindfunclet|\?j_|__ehhandler|__catch|\?\?__F)")
EH_RVAS = {a for a, ns in names_at.items() if "__EH_prolog" in ns or "___EH_prolog" in ns}
RAW_ALLOC = {0x307F0, 0x30830}
md3 = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
NUM = re.compile(r"0x[0-9a-f]+|\b\d+\b")


def norm(code, va, lo, hi):
    out, calls = [], []
    for a, _s, mn, ops in md3.disasm_lite(code, va):
        if mn in ("call", "jmp") and ops.startswith("0x"):
            calls.append(int(ops, 16))
            out.append((mn, "T"))
            continue
        if mn.startswith("j"):
            out.append((mn, "L"))
            continue
        out.append((mn, re.sub(r"0x[0-9a-f]{6,}", "A", ops)))
    return out, calls


def layout_constants(stream):
    """Numbers a type's layout shows through: member displacements off a non-stack register, shifts, scales, pushed sizes, arithmetic."""
    out = set()
    for mn, ops in stream:
        if mn in ("ret", "retn", "int3", "nop") or mn.startswith("j") or (mn == "call" and ops == "T"):
            continue
        for m in re.finditer(r"\[([^\]]+)\]", ops):
            body = m.group(1)
            if "ebp" in body or "esp" in body:
                continue
            for tok in re.findall(r"(?:\+ |- |\* )(0x[0-9a-f]+|\d+)", body):
                out.add(int(tok, 0))
        rest = re.sub(r"\[[^\]]+\]", "", ops)
        if mn in ("sub", "add", "and") and rest.startswith("esp"):
            continue
        for tok in re.findall(r"\b(0x[0-9a-f]+|\d+)\b", rest):
            out.add(int(tok, 0))
    return out - {0, 1}


retail_home = collections.defaultdict(list)
for _a in starts:
    _st, _ = norm(ret[_a:_a + size_at[_a]], _a + RBASE, 0, 0)
    retail_home[hash(tuple(_st))].append(_a)


def home_of(T, ext):
    """Retail row bodies with the same instructions as image body T, addresses aside: does retail hold this shape anywhere?"""
    st, _ = norm(img[T:T + ext], T + IBASE, 0, 0)
    while st and st[-1][0] in ("int3", "nop"):
        st.pop()
    return retail_home.get(hash(tuple(st)), [])


def signature(R, S, T, ext):
    """Tags for a differing body: which way it differs, read from both instruction streams."""
    rn, rc = norm(ret[R:R + S], R + RBASE, 0, 0)
    inn, ic = norm(img[T:T + min(ext, S + 0x400)], T + IBASE, 0, 0)
    tags = []
    r_eh = any(t - RBASE in EH_RVAS for t in rc)
    i_eh = any(any("EH_prolog" in n for n in inames.get(t - IBASE, ())) for t in ic)
    if r_eh != i_eh:
        tags.append("eh-flavor")
    r_fr = rn[:2] == [("push", "ebp"), ("mov", "ebp, esp")]
    i_fr = inn[:2] == [("push", "ebp"), ("mov", "ebp, esp")]
    if r_fr != i_fr:
        tags.append("frame-flavor")
    r_raw = any(t - RBASE in RAW_ALLOC for t in rc)
    i_node = any(any("__node_alloc" in n for n in inames.get(t - IBASE, ())) for t in ic)
    r_node = any(any("__node_alloc" in n for n in names_at.get(t - RBASE, ())) for t in rc)
    i_raw = any(any(n in ("?allocate@?$allocator@D@_STL@@SAPADIPBX@Z",) or "bfmealloc" in n for n in inames.get(t - IBASE, ())) for t in ic)
    if (r_raw and i_node) or (r_node and i_raw):
        tags.append("alloc-family")
    if len(rn) == len(inn):
        unequal = [(x, y) for x, y in zip(rn, inn) if x != y]
        if all(x[0] == y[0] and NUM.sub("N", x[1]) == NUM.sub("N", y[1]) for x, y in unequal):
            tags.append(f"operands-only:{len(unequal)}")
        elif all(x[0] == y[0] for x, y in unequal):
            tags.append(f"registers-or-operands:{len(unequal)}")
    ratio = difflib.SequenceMatcher(None, [x[0] for x in rn][:400], [x[0] for x in inn][:400], autojunk=False).ratio()
    rl, il = layout_constants(rn), layout_constants(inn)
    only_r, only_i = sorted(rl - il), sorted(il - rl)
    layout = "same" if not only_r and not only_i else ("different" if only_r and only_i else ("retail-more" if only_r else "image-more"))
    if layout == "same" and any(t.startswith(("operands-only", "registers-or-operands")) for t in tags):
        layout = "operands"
    home = home_of(T, ext)
    return ",".join(tags) or "other", round(ratio, 2), len(rn), len(inn), len(rc), len(ic), layout, ",".join(hex(x) for x in only_r), ",".join(hex(x) for x in only_i), len(home), ",".join(hex(x) for x in home[:3])


sizes_of = collections.defaultdict(dict)
for a, rs in rows_at.items():
    for r in rs:
        sizes_of[a][r["name"]] = int(r["target_size"])
seen_bodies = set()
for a in starts:
    want = {provider.get(r["source"], "") for r in rows_at[a]}
    found = False
    for n in sorted(names_at[a]):
        S = sizes_of[a][n]
        cands = by_name.get(n, ())
        if not cands or FUNCLET.match(n):
            continue
        found = True
        own = [c for c in cands if c[1] in want]
        rva, obj = (own or cands)[0]
        if (a, rva) in seen_bodies:
            continue
        seen_bodies.add((a, rva))
        diffs, first, pairs = compare(a, rva, S)
        if diffs:
            cls = "body-differs-other-object" if not own else "body-differs-own-object"
            row_classes[cls] += 1
            row_problems.append((a, cls, obj, n, first, S, rva))
        else:
            row_classes["body-same-other-object" if not own else "body-same-own-object"] += 1
            for kind, o, rt, it in pairs:
                pair_sites[(rt, it)].append((a, o, kind))
    if not found:
        cls = "no-body-funclet-or-label" if all(FUNCLET.match(n) for n in names_at[a]) else "row-not-in-image"
        row_classes[cls] += 1
        if cls == "row-not-in-image":
            row_problems.append((a, cls, "", sorted(names_at[a])[0], 0, size_at[a], 0))

# ---- pairs, following identical bodies under other names
pair_class = {}
pair_info = {}
work = list(pair_sites)
while work:
    rt, it = work.pop()
    if (rt, it) in pair_class:
        continue
    inm = inames.get(it, [])
    if rt in names_at and names_at[rt] & set(inm):
        pair_class[(rt, it)] = "same"
        continue
    base = isym(it)
    if base is not None and any(n in stubs for n in inames.get(base, ())):
        pair_class[(rt, it)] = "stub"
        continue
    rt2, it2 = rt, it
    for _ in range(6):
        if it2 == isym(it2) and iextent(it2) <= 5 + 11 and img[it2] == 0xE9 and all(b in (0xCC, 0x90) for b in img[it2 + 5:it2 + iextent(it2)]):
            it2 = it2 + 5 + struct.unpack_from("<i", img, it2 + 1)[0]
        else:
            break
    for _ in range(6):
        if size_at.get(rt2) == 5 and ret[rt2] == 0xE9:
            rt2 = rt2 + 5 + struct.unpack_from("<i", ret, rt2 + 1)[0]
        else:
            break
    if (rt2, it2) != (rt, it):
        pair_class[(rt, it)] = "thunk"
        pair_sites[(rt2, it2)].extend(pair_sites[(rt, it)])
        work.append((rt2, it2))
        continue
    if rt not in size_at:
        owner = row_containing(rt)
        if owner is not None:
            delta = rt - owner
            if base is not None and it - base == delta and names_at[owner] & set(inames.get(base, ())):
                pair_class[(rt, it)] = "same-interior"
            else:
                pair_class[(rt, it)] = "retail-interior"
        else:
            pair_class[(rt, it)] = "retail-unrowed"
        continue
    S = size_at[rt]
    diffs, first, pairs = compare(rt, it, S)
    longer = iextent(it) > S + 15 and any(b not in (0xCC, 0x90) for b in img[it + S:it + S + 16])
    if diffs or (it != base):
        pair_class[(rt, it)] = "different"
    elif longer:
        pair_class[(rt, it)] = "different"
    else:
        pair_class[(rt, it)] = "identical"
        for kind, o, t2, i2 in pairs:
            pair_sites[(t2, i2)].append((rt, o, kind))
            work.append((t2, i2))
    pair_info[(rt, it)] = (diffs, first, S, iextent(it), it - (base or it), longer)

# ---- boot order: LINK-627's walker, over retail
md2 = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
dl = {}
for d in csv.DictReader(open(ledger / "data_ledger.csv", newline="", encoding="utf-8", errors="replace")):
    try:
        v, s = int(d["address"], 16), int(d["size"] or 0)
    except ValueError:
        continue
    dl[v - RBASE if v >= RBASE else v] = s


def word(rva):
    return struct.unpack_from("<I", ret, rva)[0] if 0 <= rva < RSIZE - 4 else 0


def table_run(t):
    out_, a = [], t
    while rtext(word(a) - RBASE):
        out_.append(word(a) - RBASE)
        a += 4
    return out_


IMMED = re.compile(r"0x[0-9a-f]+")
cache = {}


def analyze(fa):
    if fa in cache:
        return cache[fa]
    S = size_at[fa]
    code = ret[fa:fa + S]
    direct, stores = [], []
    for addr, size, mn, ops in md2.disasm_lite(code, fa + RBASE):
        if mn == "call" and code[addr - RBASE - fa] == 0xE8:
            direct.append(("call", int(ops, 16) - RBASE))
            continue
        if mn == "call" and code[addr - RBASE - fa] == 0xFF:
            m = re.match(r"dword ptr \[e[a-z]+(?: \+ (0x[0-9a-f]+))?\]$", ops)
            if m:
                direct.append(("vcall", int(m.group(1) or "0", 16)))
            continue
        if mn == "jmp" and code[addr - RBASE - fa] == 0xE9:
            t = int(ops, 16) - RBASE
            if not fa <= t < fa + S:
                direct.append(("jmp", t))
            continue
        for tok in IMMED.findall(ops):
            v = int(tok, 16) - RBASE
            if rtext(v) and mn in ("push", "mov"):
                direct.append(("fnptr", v))
            elif RT1 <= v < RSIZE:
                if mn == "mov" and ops.startswith("dword ptr [") and ops.endswith(tok):
                    run = table_run(v)
                    if run:
                        stores.append(v)
                        continue
                direct.append(("data", v))
    cache[fa] = (direct, stores)
    return cache[fa]


def data_fnptrs(v):
    s = dl.get(v, 0)
    if s <= 0 or s > 0x8000:
        return []
    return [word(a) - RBASE for a in range(v, v + s - 3, 4) if (word(a) - RBASE) in size_at]


visited = {}
order = [0]


def walk(anchor, roots, max_tier):
    tiers = [list(roots)]
    tier = 0
    while tier <= max_tier and tier < len(tiers):
        nxt = []
        for root in tiers[tier]:
            stack = [root]
            while stack:
                fa = stack.pop()
                if fa not in size_at:
                    fa = row_containing(fa)
                    if fa is None:
                        continue
                if fa in visited:
                    continue
                visited[fa] = (anchor, tier, order[0])
                order[0] += 1
                direct, stores = analyze(fa)
                kids = []
                for kind, t in direct:
                    if kind == "vcall":
                        continue
                    kids.extend(data_fnptrs(t) if kind == "data" else [t])
                for t in stores:
                    nxt.extend(table_run(t))
                stack.extend(reversed(kids))
        if tier + 1 < len(tiers):
            tiers[tier + 1].extend(nxt)
        else:
            tiers.append(nxt)
        tier += 1


def by_row_name(name):
    return next(a for a, ns in names_at.items() if name in ns)


walk("WinMain", [by_row_name("_WinMain@16")], 0)
ge = by_row_name("?init@GameEngine@@UAEXHQAPAD@Z")
W32 = table_run(0x00BC2530 - RBASE)
seq = []
for kind, t in analyze(ge)[0]:
    if kind in ("call", "jmp", "fnptr"):
        seq.append(t)
    elif kind == "vcall" and t % 4 == 0 and t // 4 < len(W32):
        seq.append(W32[t // 4])
for i, t in enumerate(seq):
    walk(f"GEinit#{i}", [t], 2)
boot_end = order[0]
for label, name in (("skirmish", "?startNewGame@GameLogic@@QAEX_N@Z"),):
    walk(label, [by_row_name(name)], 2)
print(f"boot walker: {boot_end} rows; with skirmish root {order[0]}; of {len(starts)}", file=sys.stderr)

# ---- anchored walk: from each address whose row has one body, follow the image's and retail's calls in step. A template name
# parked on an address no real caller reaches in step never counts; a stand-in reached from a real caller does, even with a good
# sibling name at the same address (P43, P40).
bodies_at = collections.defaultdict(list)
for a, rva in seen_bodies:
    bodies_at[a].append(rva)
compare_memo = {}


def compare_cached(R, T, S):
    key = (R, T, S)
    if key not in compare_memo:
        compare_memo[key] = compare(R, T, S)
    return compare_memo[key]


def resolve_thunks(rt, it):
    for _ in range(6):
        if it == isym(it) and img[it] == 0xE9 and all(b in (0xCC, 0x90) for b in img[it + 5:it + iextent(it)]):
            it = it + 5 + struct.unpack_from("<i", img, it + 1)[0]
        else:
            break
    for _ in range(6):
        if size_at.get(rt) == 5 and ret[rt] == 0xE9:
            rt = rt + 5 + struct.unpack_from("<i", ret, rt + 1)[0]
        else:
            break
    return rt, it


def forwards_to(it, rt):
    """A short image body whose call or jump lands on a symbol the ledger gives retail's target: a wrapper around the real row."""
    ext = iextent(it)
    if ext > 0x60:
        return False
    for addr, size, mn, ops in md3.disasm_lite(img[it:it + ext], it + IBASE):
        if mn in ("call", "jmp") and ops.startswith("0x"):
            t = int(ops, 16) - IBASE
            if names_at[rt] & set(inames.get(t, ())):
                return True
    return False


anchored_seen = {}
anchored_found = []
anchored_classes = collections.Counter()
roots = sorted((a for a, b in bodies_at.items() if len(b) == 1), key=lambda a: visited.get(a, (0, 0, 10**9))[2])
for root in roots:
    stack = [(root, bodies_at[root][0], None)]
    while stack:
        rt, it, parent = stack.pop()
        if (rt, it) in anchored_seen:
            continue
        anchored_seen[(rt, it)] = (parent, root)
        if rt not in size_at:
            anchored_classes["no-retail-extent"] += 1
            continue
        base = isym(it)
        if base is not None and any(n in stubs for n in inames.get(base, ())):
            anchored_classes["stub"] += 1
            continue
        names = set(inames.get(it, ())) & names_at[rt]
        S = max((sizes_of[rt][n] for n in names), default=size_at[rt])
        diffs, first, pairs = compare_cached(rt, it, S)
        longer = iextent(it) > S + 15 and any(b not in (0xCC, 0x90) for b in img[it + S:it + S + 16])
        if diffs or longer or it != base:
            if not names and it == base and forwards_to(it, rt):
                anchored_classes["ok-forwards"] += 1
                continue
            kind = "named-body" if names else "other-body"
            anchored_classes[kind] += 1
            anchored_found.append((kind, rt, it, S, diffs, first, longer, parent, root))
            continue
        anchored_classes["ok-named" if names else "ok-identical"] += 1
        for _kind, o, t2, i2 in reversed(pairs):
            r2, j2 = resolve_thunks(t2, i2)
            stack.append((r2, j2, (rt, it, o)))
print("ANCHORED roots", len(roots), "pairs walked", len(anchored_seen), dict(anchored_classes))


def chain_of(rt, it):
    out = []
    key = (rt, it)
    for _ in range(9):
        parent = anchored_seen.get(key, (None, None))[0]
        if parent is None:
            break
        out.append(f"{parent[0]:#x}+{parent[2]:#x}")
        key = parent[:2]
    return " < ".join(out)


with open(out + ".anchored.tsv", "w", encoding="utf-8") as f:
    print("order\tanchor\ttier\tkind\tretail_rva\tretail_name\tsize\timage_rva\timage_name\textent\tdiffs\tfirst\tlonger\ttags\tratio\tlayout\tonly_retail\tonly_image\thomes\troot\troot_name\tparent\tchain", file=f)
    lines = []
    for kind, rt, it, S, diffs, first, longer, parent, root in anchored_found:
        od, anchor, tier = visited.get(root, (None, None, None))[2], visited.get(root, ("unreached",))[0], visited.get(root, (0, -1))[1]
        ext = iextent(it)
        sg = signature(rt, S, it, ext)
        lines.append((od if od is not None else 10**9, anchor, tier, kind, f"{rt:#x}", sorted(names_at[rt])[0][:110], S, f"{it:#x}", (inames.get(isym(it)) or ["?"])[0][:110], ext, diffs, first, longer,
                      sg[0], sg[1], sg[6], sg[7], sg[8], sg[9], f"{root:#x}", sorted(names_at[root])[0][:90], f"{parent[0]:#x}" if parent else "", chain_of(rt, it)))
    for line in sorted(lines, key=lambda x: x[0]):
        print("\t".join(str(x) for x in line), file=f)

# ---- report
print("ROWS", dict(row_classes))
kinds = collections.Counter()
for (rt, it), cls in pair_class.items():
    kinds[cls] += 1
print("DISTINCT PAIRS", dict(kinds))
sites = collections.Counter()
for key, s in pair_sites.items():
    sites[pair_class.get(key, "?")] += len(s)
print("CALL SITES", dict(sites))


def rank(rva):
    v = visited.get(rva)
    return (v[2] if v else 10**9, v[0] if v else "unreached", v[1] if v else -1)


# A caller's address can carry several template names, each compiled to its own body. A site where one of them binds retail's
# callee says the other names are not retail's body at this address; a site where none does has no such explanation.
site_classes = collections.defaultdict(set)
for key, s in pair_sites.items():
    for caller, o, _kind in s:
        site_classes[(caller, o)].add(pair_class.get(key))
GOOD = {"same", "identical", "same-interior"}
row_of_name = {}
for a, ns in names_at.items():
    for n in ns:
        row_of_name.setdefault(n, a)
body_good = collections.Counter()
for a in starts:
    for n in names_at[a]:
        for rva, _obj in by_name.get(n, ())[:1]:
            if (a, rva) in seen_bodies and not any(p[0] == a and p[6] == rva for p in row_problems):
                body_good[a] += 1
summary = collections.Counter()
tag_count = collections.Counter()
with open(out + ".different.tsv", "w", encoding="utf-8") as f, open(out + ".sites.tsv", "w", encoding="utf-8") as g:
    print("best_order\tanchor\ttier\tcallers\texample_caller\tcaller_name\tkind\toffset\tretail_target\tretail_name\tretail_size\timage_target\timage_name\timage_extent\tinto\tdiffs\tfirst_diff\tlonger\ttags\tratio\tinsns_r\tinsns_i\tcalls_r\tcalls_i\tlayout\tonly_retail\tonly_image\thomes\thome_rvas\talone_sites\tsibling_sites\ttarget_row", file=f)
    lines = []
    for (rt, it), cls in pair_class.items():
        if cls != "different":
            continue
        s = pair_sites[(rt, it)]
        alone = [x for x in s if not site_classes[(x[0], x[1])] & GOOD]
        sibling = len(s) - len(alone)
        best = min(alone or s, key=lambda x: rank(x[0])[0])
        od, anchor, tier = rank(best[0])
        diffs, first, S, ext, into, longer = pair_info[(rt, it)]
        base = isym(it)
        sg = signature(rt, S, it, ext)
        tag_count[sg[0].split(":")[0]] += 1
        target_rows = sorted({row_of_name[n] for n in inames.get(base, ()) if n in row_of_name})
        summary[("pair alone" if alone else "pair sibling-only", "rowed" if target_rows else "unrowed", "boot" if anchor != "unreached" else "unreached")] += 1
        lines.append((od, anchor, tier, len(s), f"{best[0]:#x}", sorted(names_at.get(best[0], {"?"}))[0][:100], best[2], f"{best[1]:#x}",
                      f"{rt:#x}", sorted(names_at[rt])[0][:110], S, f"{it:#x}", (inames.get(base) or ["?"])[0][:110], ext, into, diffs, first, longer) + sg
                     + (len(alone), sibling, ",".join(hex(x) for x in target_rows[:3])))
        for caller, o, kind in s:
            print(f"{rt:#x}", f"{it:#x}", f"{caller:#x}", f"{o:#x}", kind, sorted(names_at.get(caller, {"?"}))[0][:140], sep="\t", file=g)
    for line in sorted(lines, key=lambda x: x[0]):
        print("\t".join(str(x) for x in line), file=f)
print("DIFFERENT PAIR TAGS", dict(tag_count))
row_tags = collections.Counter()
with open(out + ".rows.tsv", "w", encoding="utf-8") as f:
    print("best_order\tanchor\ttier\tretail_rva\tclass\tprovider\tname\tfirst_diff\tsize\timage_rva\ttags\tratio\tinsns_r\tinsns_i\tcalls_r\tcalls_i\tlayout\tonly_retail\tonly_image\thomes\thome_rvas\tgood_names_here", file=f)
    for a, cls, obj, name, first, S, rva in sorted(row_problems, key=lambda x: rank(x[0])[0]):
        od, anchor, tier = rank(a)
        sg = signature(a, S, rva, iextent(rva)) if rva else ("",) * 11
        if rva:
            row_tags[cls + " " + sg[0].split(":")[0]] += 1
            summary[("body alone" if not body_good[a] else "body sibling-only", sg[6] if sg[6] == "same" else "layout-differs", "boot" if anchor != "unreached" else "unreached")] += 1
        print(od, anchor, tier, f"{a:#x}", cls, obj[-70:], name[:120], first, S, f"{rva:#x}", *sg, body_good[a], sep="\t", file=f)
print("BODY TAGS", dict(row_tags))
for k, v in sorted(summary.items()):
    print("SUMMARY", k, v)
with open(out + ".other.tsv", "w", encoding="utf-8") as f:
    print("class\tcallers\tretail_target\timage_target\timage_name\texample_caller\tcaller_name", file=f)
    for (rt, it), cls in pair_class.items():
        if cls in ("same", "identical", "different", "same-interior", "thunk"):
            continue
        s = pair_sites[(rt, it)]
        base = isym(it)
        print(cls, len(s), f"{rt:#x}", f"{it:#x}", (inames.get(base) or ["?"])[0][:90], f"{s[0][0]:#x}", sorted(names_at.get(s[0][0], {"?"}))[0][:80], sep="\t", file=f)
with open(out + ".identical.tsv", "w", encoding="utf-8") as f:
    print("callers\tretail_target\tretail_name\timage_target\timage_name", file=f)
    for (rt, it), cls in pair_class.items():
        if cls == "identical":
            print(len(pair_sites[(rt, it)]), f"{rt:#x}", sorted(names_at[rt])[0][:90], f"{it:#x}", (inames.get(it) or ["?"])[0][:90], sep="\t", file=f)
print("wrote", out)
