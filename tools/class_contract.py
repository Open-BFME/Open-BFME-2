#!/usr/bin/env python3
"""The ABI contract of one class, decided from evidence in a fixed rule order.

WHY. A canonical header is only as good as the claims it freezes: sizeof,
every field's offset, width and name, the class-key (which the mangled names
of every ledger row spell: `U` struct, `V` class), the bases and the virtual
slots. The private views disagree on spelling almost always and on layout
rarely, so the question is never "which view is right" but "which evidence
settles this one attribute". This tool answers it per attribute, in the
order research 11 fixed, stopping at the first rule that decides:

  0. retail-ctor  bases, virtual bases and sizeof read from retail bytes by
                  tools/retail_layout.py: vftable/vbtable stores and base
                  constructor calls in the class's matched constructors, and
                  `push SIZE; call operator new` at its allocation sites.
                  Retail is /GR-, so these are the only layout facts the image
                  carries; they outrank every view. Retail facts that disagree
                  with each other are queued, never voted;
  1. bytes        what byte-matched code proves: an attribute every compiled
                  view agrees on, and the class-key the ledger's matched names
                  mangle (each row's name is verified by the gate);
  2. retail-access  widths of `this`-relative reads and writes in the retail
                  bodies of the class's own member functions (capstone), and
                  BFME1's ZH<->retail field witnesses (bfme_layouts.json);
  3. retail-vtable  vftable stores in retail constructors and the slots read
                  from the table's words (tools/retail_layout.py);
  4. zh           the Zero Hour header's own layout (compiled, -Z7), names and
                  class-key;
  5. majority     of the views, for names only.

An attribute still tied after all five is a queue item, never a guess. The
contract is written next to the canonical header (reverse/class_contracts/)
so the evidence a header was generated from is reviewable and re-checkable.

    python3 tools/class_contract.py --class Coord3D            summary
    python3 tools/class_contract.py --class Coord3D --write    freeze the contract
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_layouts  # noqa: E402

if (ROOT / "reverse" / "functions.csv").exists():                    # Open-BFME-2
    REVERSE, CODE = ROOT / "reverse", ("Code/",)
else:                                                                 # Open-BFME-1
    REVERSE, CODE = ROOT / "targets" / "game" / "reverse", ("game/",)
LEDGER = REVERSE / "functions.csv"
CONTRACTS = REVERSE / "class_contracts"
GENERATED = ("Code/gen_asm/", "Code/gen_small/", "game/gen_small/", "game/gen_asm/")
PRIMK = {"float": "f4", "double": "f8", "int": "i4", "uint": "i4", "long": "i4", "ulong": "i4", "short": "i2",
         "ushort": "i2", "char": "i1", "uchar": "i1", "bool": "i1", "int64": "i8", "uint64": "i8", "enum": "i4",
         "wchar": "i2", "int8": "i1", "uint8": "i1"}
PAD = re.compile(r"^(m_)?(pad|_pad|unk|gap|reserved)", re.I)


def portable_component(name):
    """One collision-free filename component, preserving ordinary class names."""
    if not name:
        raise ValueError("empty class name")
    encoded = "".join(chr(b) if chr(b) in "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"
                      else f"%{b:02X}" for b in name.encode("utf-8"))
    if encoded.upper() in {"CON", "PRN", "AUX", "NUL", *(f"COM{i}" for i in range(1, 10)),
                          *(f"LPT{i}" for i in range(1, 10))}:
        encoded = f"%{ord(encoded[0]):02X}" + encoded[1:]
    return encoded


def contract_path(name):
    return CONTRACTS / (portable_component(name) + ".json")


def mangled_scope(name):
    """Plain qualified C++ scope in MSVC's innermost-first spelling."""
    return "@".join(reversed(name.split("::")))


# ---------------------------------------------------------------- evidence: views

def ledger_rows():
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r["status"] == "matched"]


def census(name, rows=None):
    """Ledger sources (authored) that declare their own body for `name`."""
    sources = sorted({r["source"] for r in (rows or ledger_rows())
                      if r["source"].lower().endswith((".cpp", ".c")) and not r["source"].startswith(GENERATED)})
    head = re.compile(r"^[ \t]*(?:class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)?" + re.escape(name) + r"\s*(?::(?!:)[^{;]*)?\{", re.M)
    out = []
    for source in sources:
        try:
            text = (ROOT / source).read_text(encoding="latin-1")
        except OSError:
            continue
        if head.search(text) and name in class_layouts.class_bodies(text):
            out.append(source)
    return out


def views(name, sources, jobs=8):
    """{source: layout or {'error': ...}} for the private views of `name`."""
    builder = class_layouts.build_module()

    def one(source):
        try:
            got = class_layouts.private_views(source, builder, {name})
            # The whole type stream (cached by private_views' compile) supplies
            # the member aggregates flatten(leaves=True) expands.
            every = dict(class_layouts.compile_layouts(source, builder)) if got.get(name) else {}
            every.update(got)
            return source, got.get(name) or {"error": "no CodeView record"}, every
        except RuntimeError as exc:
            return source, {"error": str(exc)}, {}
    out, every = {}, {}
    with cf.ThreadPoolExecutor(jobs) as pool:
        for source, layout, got in pool.map(one, sources):
            out[source], every[source] = layout, got
    return out, every


def kind(type_name):
    if type_name.endswith("*"):
        return "P"
    if "[" in type_name:
        return "A"
    return PRIMK.get(type_name, "S:" + type_name)


def aggregate(every, type_name, size):
    """The layout of a plain member aggregate `type_name` (no vftable), else None."""
    layout = every.get(type_name)
    if not layout or layout.get("fwd") or layout.get("vfptr") or layout.get("virtual") or layout.get("size") != size:
        return None
    return layout


def flatten(layout, every, base=0, depth=0, leaves=False, prefix=""):
    """[(offset, size, kind, name, type)] with known bases expanded and pads dropped.

    leaves=True also expands plain member aggregates into their scalars, named
    `member.field`: a view spelling `Coord2D lo` and one spelling `float x_min,
    y_min` then vote on the same offsets (regroup() restores the aggregate)."""
    out = []
    if layout.get("vfptr") and not layout.get("bases"):
        out.append((base, 4, "VPTR", prefix + "__vfptr", "void*"))
    for base_name, offset in layout.get("bases", []):
        if base_name in every and depth < 6:
            out += flatten(every[base_name], every, base + max(offset, 0), depth + 1, leaves, prefix)
    for offset, field, type_name, size in layout.get("fields", []):
        if PAD.match(field) or (type_name.startswith(("char[", "uchar[")) and field.startswith(("pad", "_", "m_pad"))):
            continue
        member = aggregate(every, type_name, size) if leaves and depth < 6 else None
        if member is not None:
            inner = flatten(member, every, base + offset, depth + 1, True, prefix + field + ".")
            if inner:
                out += inner
                continue
        out.append((base + offset, size, kind(type_name), prefix + field, type_name))
    return out


def leaf_shape(layout, every, offset):
    return [(o, size, k) for o, size, k, _, _ in flatten(layout, every, offset, 1, True)]


def inherited_spans(layout, every):
    """[(start, end)] the layout's known bases occupy, from each base's own flattened extent.

    An empty base (no vfptr, field or base of its own) occupies nothing: MSVC lays
    the derived class's first member over it. A base the view never defines gives
    no span either; its fields cannot be told from the class's own."""
    out = []
    for base_name, offset in layout.get("bases", []):
        if base_name not in every or offset < 0:
            continue
        leaves = flatten(every[base_name], every, max(offset, 0), 1, False)
        if leaves:
            out.append((min(o for o, *_ in leaves), max(o + size for o, size, *_ in leaves)))
    return out


def slot_count(layout, every, depth=0):
    """Slots of the layout's primary vftable: the offset-0 base's count, then its own introductions."""
    count = 0
    for base_name, offset in layout.get("bases", []):
        if offset == 0 and base_name in every and depth < 6:
            count = max(count, slot_count(every[base_name], every, depth + 1))
    own = [int(k) for k in layout.get("vslots", {})]
    return max([count] + [k + 1 for k in own])


def own_members(name, bases, good, flat, every):
    """Restrict every view to the members the class declares itself, given its decided `bases`.

    A view that spells the decided bases proves where they end (the union of the
    bases' extents), what lies inside them and how many primary slots they
    bring. Only when every such view agrees does any view drop the leaves inside
    those spans and the introducing slots below that count: a view that copied a
    base's fields or vfptr into the class (no base clause, or a stub base) then
    votes only on the members the class itself adds. Views that disagree on the
    extent or the slot count, or a leaf inside the span that the bases do not
    declare at that offset, width and kind, are queued and nothing is dropped:
    the per-offset votes then see every conflict, as without a base. Returns
    (flat, vslots by view, evidence, queue)."""
    spans, counts, inside_leaves = collections.Counter(), collections.Counter(), set()
    for source, layout in good.items():
        if bases and [b for b, _ in layout.get("bases", [])] == list(bases) \
                and all(b in every[source] for b in bases):
            got = tuple(inherited_spans(layout, every[source]))
            spans[got] += 1
            counts[max((slot_count(every[source][b], every[source]) for b, offset in layout["bases"] if offset == 0),
                       default=0)] += 1
            for base_name, offset in layout["bases"]:
                if offset >= 0:
                    inside_leaves.update((o, size, k) for o, size, k, _, _ in
                                         flatten(every[source][base_name], every[source], offset, 1, True))
    queue, span, inherited = [], [], 0
    if len(spans) > 1:
        queue.append({"class": name, "attribute": "base-extent",
                      "candidates": {repr(list(map(list, k))): n for k, n in spans.items()}})
    elif len(counts) > 1:
        queue.append({"class": name, "attribute": "base-slots", "candidates": {str(k): n for k, n in counts.items()}})
    elif spans:
        span, inherited = list(next(iter(spans))), next(iter(counts))
    inside = lambda offset: any(a <= offset < b for a, b in span)
    for offset in sorted({leaf[0] for items in flat.values() for leaf in items if inside(leaf[0])}):
        shapes = {(o, size, k) for items in flat.values() for o, size, k, _, _ in items if o == offset}
        if shapes - inside_leaves:
            queue.append({"class": name, "attribute": f"inherited@{offset:#x}",
                          "candidates": {f"{size}:{k}": 1 for _, size, k in sorted(shapes)}})
    if queue:
        span, inherited = [], 0
    own_flat = {s: [leaf for leaf in items if not inside(leaf[0])] for s, items in flat.items()}
    vslots = {}
    for source, layout in good.items():
        spelled_bases = bool(layout.get("bases"))
        vslots[source] = {int(k): v for k, v in layout.get("vslots", {}).items()
                          if spelled_bases or int(k) >= inherited}
    return own_flat, vslots, {"inherited_spans": [list(x) for x in span], "inherited_slots": inherited,
                              "base_views": sum(spans.values())}, queue


RULE_STRENGTH = ("bytes", "retail-access", "zh", "majority")


def regroup(name, fields, nested, queue):
    """Fold decided scalar leaves back into the member aggregate that declares them.

    `nested` lists (offset, size, type, label, rule, leaves) candidates, ZH's own
    members first, then the views' by majority. A candidate folds when the
    decided fields in its span are exactly its leaves (offset, width, kind); a
    dotted label left over is a member no candidate explains: queued."""
    out, taken = list(fields), set()
    for offset, size, type_name, label, rule, leaves in nested:
        if any(offset <= t < offset + size for t in taken):
            continue
        inside = [f for f in out if offset <= f["offset"] < offset + size]
        # A candidate with no decided leaf in its span cannot fold.  Without
        # this guard the empty-leaf case passes the equality below and max()
        # then raises on an empty sequence (MilesAudioManager).
        if not inside or [(f["offset"], f["size"], f["kind"]) for f in inside] != leaves:
            continue
        weakest = max((f["decided_by"] for f in inside), key=lambda r: RULE_STRENGTH.index(r)
                      if r in RULE_STRENGTH else len(RULE_STRENGTH))
        folded = {"offset": offset, "size": size, "kind": "S:" + type_name, "type": type_name, "name": label,
                  "decided_by": weakest, "name_by": rule, "views": max(f["views"] for f in inside),
                  "retail_widths": {}, "witness": None,
                  "members": [{"offset": f["offset"] - offset, "size": f["size"], "kind": f["kind"],
                               "type": f["type"], "name": f["name"].split(".")[-1]} for f in inside]}
        index = out.index(inside[0])
        out = [f for f in out if f not in inside]
        out.insert(index, folded)
        taken.update(range(offset, offset + size))
    for f in out:
        if "." in f["name"]:
            queue.append({"class": name, "attribute": f"nested@{f['offset']:#x}", "candidates": {f["name"]: f["views"]}})
    return out


# ---------------------------------------------------------------- evidence: retail

def thiscall_rows(name, rows):
    scope = re.escape(mangled_scope(name))
    member = re.compile(r"^\?(\w+)@" + scope + r"@@[AIQ][AB]E")
    ctor = re.compile(r"^\?\?0" + scope + r"@@[AIQ]AE")
    return ([r for r in rows if member.match(r["name"])], [r for r in rows if ctor.match(r["name"])])


def retail_access(name, rows, builder):
    """{offset: Counter(width)} from `this`-relative operands in retail member bodies."""
    import capstone
    from capstone import x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    members, _ = thiscall_rows(name, rows)
    seen = collections.defaultdict(collections.Counter)
    for row in members[:400]:
        try:
            code = builder.read_target_bytes(int(row["target_rva"], 16), int(row["target_size"], 0))
        except Exception:
            continue
        this = {x86.X86_REG_ECX}
        for insn in md.disasm(code, 0):
            ops = insn.operands
            for op in ops:
                if op.type == x86.X86_OP_MEM and op.mem.base in this and op.mem.index == 0 and 0 <= op.mem.disp < 0x10000:
                    seen[op.mem.disp][op.size] += 1
            if insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and ops[1].type == x86.X86_OP_REG \
                    and ops[1].reg in this:
                this.add(ops[0].reg)
                continue
            written = insn.regs_access()[1]
            this -= set(written)
            if insn.mnemonic == "call":
                this -= {x86.X86_REG_ECX, x86.X86_REG_EAX, x86.X86_REG_EDX}
            if not this or insn.mnemonic in ("ret", "jmp"):
                break
    return {off: dict(c) for off, c in sorted(seen.items())}


def witnesses(name):
    """{offset: votes} from BFME1's ZH<->retail aligned field witnesses."""
    path = REVERSE / "bfme_layouts.json"
    if not path.exists():
        return {}
    out = {}
    for entry in json.loads(path.read_text(encoding="utf-8")):
        if entry.get("owner") == name and entry.get("bfme") is not None and entry.get("confidence", 0) >= 0.9:
            out[int(entry["bfme"])] = entry.get("votes")
    return out


_ENGINE = None


def retail_layout(name, rows, builder):
    """The retail layout of `name` (tools/retail_layout.py); {} when no matched constructor or destructor names it."""
    import retail_layout as engine
    scope = mangled_scope(name)
    if not any(m and m.group(1) == scope for r in rows for m in [engine.CTOR.match(r["name"])
                                                                  or engine.DTOR.match(r["name"])]):
        return {}
    global _ENGINE
    if _ENGINE is None:
        _ENGINE = engine.Engine(engine.Image.retail(), engine.Ledger(rows), cache_dir=ROOT / "build" / "retail_layout")
    return _ENGINE.contract(name)


def retail_vtable(name, rows, builder):
    """vftables retail constructors store at every [this+N], with the slots read from the table's words.

    Offset 0 is the class's primary table. The slot words run to the next table
    any matched body stores (no RTTI separates them), so a count is an upper
    bound; vtables.tsv (Ghidra) runs on into the following table for 57 of its
    160 tables and is no longer read."""
    facts = retail_layout(name, rows, builder).get("facts", {})
    out = {}
    for offset, table in facts.get("vftables", {}).get("value", {}).items():
        entry = out.setdefault(table, {"stores": len(facts["vftables"]["sites"]), "offset": int(offset, 16),
                                       "slots": {}})
        if int(offset, 16) == 0 and "vslots" in facts:
            entry["slots"] = {s["slot"]: s["name"] or s["target"] for s in facts["vslots"]["value"]["slots"]}
            entry["end"] = facts["vslots"]["value"]["end"]
    return out


def retail_bases(name, retail, good, every):
    """(bases, rule, queue) from the retail constructors, or None when they prove no base.

    Retail decides the shape: the offsets of the polymorphic bases and the
    number of virtual bases. A view agrees when its base clause has exactly
    those, plus only bases with no vftable (retail cannot see those). A base
    retail names by a real constructor keeps that name; a base the ledger
    names only by placeholder takes the agreeing views' spelling; a base
    neither names is queued."""
    import retail_layout as engine
    facts = retail.get("facts", {})
    if "bases" not in facts and "virtual_bases" not in facts:
        return None
    nonvirtual = [(b["offset"], b["name"]) for b in facts.get("bases", {}).get("value", [])]
    virtual = [v["name"] for v in facts.get("virtual_bases", {}).get("value", [])]
    offsets = [o for o, _ in nonvirtual]

    def polymorphic(source, base):
        layout = every.get(source, {}).get(base)
        return layout is None or bool(layout.get("vfptr") or layout.get("bases"))

    agreeing = collections.Counter()
    for source, layout in good.items():
        clause = layout.get("bases", [])
        mine = [(b, o) for b, o in clause if o >= 0]
        extra = [b for b, o in mine if o not in offsets]
        if sorted({o for _, o in mine} & set(offsets)) == offsets and len(mine) - len(extra) == len(offsets) \
                and not any(polymorphic(source, b) for b in extra) \
                and sum(1 for _, o in clause if o < 0) == len(virtual):
            agreeing[tuple(b for b, _ in clause)] += 1
    queue = []
    if agreeing:
        top = agreeing.most_common(2)
        if len(top) > 1 and top[0][1] == top[1][1]:
            queue.append({"class": name, "attribute": "bases", "candidates": {repr(list(k)): n for k, n in top},
                          "why": "views that agree with the retail base layout spell it differently"})
        spelled = list(top[0][0])
        at = {o: i for i, (b, o) in enumerate(next(L for L in good.values()
                                                  if tuple(b for b, _ in L.get("bases", [])) == top[0][0])["bases"])}
        for offset, real in nonvirtual:
            if isinstance(real, str) and not engine.placeholder(real):
                spelled[at[offset]] = real
        return spelled, "retail-ctor", queue
    bases = []
    for offset, real in nonvirtual:
        if not isinstance(real, str) or engine.placeholder(real):
            queue.append({"class": name, "attribute": f"base@{offset:#x}", "candidates": {repr(real): 1},
                          "why": "retail proves a base here; no view spells the retail base layout and the ledger "
                                 "names it only by placeholder"})
        bases.append(real if isinstance(real, str) else repr(real))
    for real in virtual:
        if engine.placeholder(real):
            queue.append({"class": name, "attribute": "virtual-base", "candidates": {real: 1},
                          "why": "retail proves a virtual base no matched constructor names"})
        bases.append("virtual " + real)
    return bases, "retail-ctor", queue


def ledger_key(name, rows):
    """Counter of the class-key the matched ledger names mangle: U = struct, V = class."""
    marks = collections.Counter()
    for row in rows:
        for found in re.finditer(r"([UV])" + re.escape(mangled_scope(name)) + r"@@", row["name"]):
            marks["struct" if found.group(1) == "U" else "class"] += 1
    return marks


def zh_layout(name, builder):
    """The Zero Hour header's layout of `name`, compiled with the ZH flags; None if absent."""
    zh_root = getattr(builder, "ZH_REFERENCE_ROOT", None)
    if zh_root is None or not Path(zh_root).exists():
        return None
    head = re.compile(r"^(?:class|struct)\s+" + re.escape(name) + r"\s*(?::(?!:)[^{;]*)?\{", re.M)
    header = None
    for path in sorted(Path(zh_root).rglob("*.h")):
        try:
            if head.search(path.read_text(encoding="latin-1")):
                header = path
                break
        except OSError:
            continue
    if header is None:
        return None
    shown = header.as_posix()
    shown = shown[shown.find("CnC_Generals_Zero_Hour"):]
    probe = class_layouts.CACHE / f"zh_{portable_component(name)}.cpp"
    probe.parent.mkdir(parents=True, exist_ok=True)
    # The header alone first: PreRTS.h drags in STLport, which these flags do not set up.
    every, failure = None, None
    for prelude in ("", '#include "PreRTS.h"\n'):
        probe.write_text(f'{prelude}#include "{header.as_posix()}"\n'
                         f"int zh_probe({name} *p) {{ return sizeof(*p); }}\n", encoding="utf-8")
        try:
            every = class_layouts.compile_layouts(probe.relative_to(ROOT), builder, True, list(builder._ZH_FLAGS))
            break
        except (RuntimeError, AttributeError) as exc:
            failure = str(exc)[:300]
    if every is None:
        return {"header": shown, "error": failure}
    layout = every.get(name)
    if not layout or layout.get("fwd"):
        return {"header": shown, "error": "no CodeView record"}
    return {"header": shown, "layout": layout, "every": every}


# ---------------------------------------------------------------- decision

def decide(name, sources=None, jobs=8, sample=None):
    builder = class_layouts.build_module()
    rows = ledger_rows()
    sources = sources or census(name, rows)
    if sample and len(sources) > sample:
        import random
        sources = sorted(random.Random(20261006).sample(sources, sample))
    got, every = views(name, sources, jobs)
    good = {s: L for s, L in got.items() if "error" not in L}
    flat = {s: flatten(L, every[s], leaves=True) for s, L in good.items()}
    zh = zh_layout(name, builder)
    zh_flat = flatten(zh["layout"], zh["every"], leaves=True) if zh and "layout" in zh else []
    zh_at = {o: (s, k, n, t) for o, s, k, n, t in zh_flat}
    access = retail_access(name, rows, builder)
    witness = witnesses(name)
    vtables = retail_vtable(name, rows, builder)
    retail = retail_layout(name, rows, builder)
    queue, fields = [], []
    for conflict in retail.get("conflicts", []):
        queue.append({"class": name, "attribute": "retail-" + conflict["fact"], "candidates": conflict.get("candidates"),
                      "why": "the class's retail constructors or destructors disagree"})

    # The bases first: a derived class's contract declares only its own members
    # and names its bases, never copies of their fields, vfptrs or slots.
    zh_bases = [b for b, _ in zh["layout"]["bases"]] if zh and "layout" in zh else None
    base_votes = collections.Counter(tuple(b for b, _ in L.get("bases", [])) for L in good.values())
    from_retail = retail_bases(name, retail, good, every)
    overruled = None
    if from_retail is not None:
        bases, base_rule, retail_queue = from_retail
        queue += retail_queue
        if base_votes and list(base_votes.most_common(1)[0][0]) != bases:
            overruled = {"majority": list(base_votes.most_common(1)[0][0]), "zh": zh_bases}
    elif zh_bases is not None and tuple(zh_bases) in base_votes:
        bases, base_rule = zh_bases, "zh"
    else:
        bases, base_rule = (list(base_votes.most_common(1)[0][0]) if base_votes else []), "majority"
    flat, view_slots, inherited, base_queue = own_members(name, bases, good, flat, every)
    queue += base_queue
    if bases and inherited["inherited_spans"]:
        start = max(b for _, b in inherited["inherited_spans"])
        zh_at = {o: v for o, v in zh_at.items() if o >= start}

    candidates = collections.defaultdict(collections.Counter)
    names = collections.defaultdict(collections.Counter)
    types = collections.defaultdict(collections.Counter)
    for source, items in flat.items():
        for offset, size, k, field, type_name in items:
            candidates[offset][(size, k)] += 1
            names[offset][field] += 1
            types[(offset, size, k)][type_name] += 1
    # A field past the majority sizeof that only a minority of views declares is
    # that view's own claim (a pad-as-members view, a different type wearing the
    # name): recorded, never frozen into the contract. The unit's gate decides it.
    major_size = collections.Counter(L["size"] for L in good.values()).most_common(1)[0][0] if good else 0
    outliers = []
    for offset in sorted(candidates):
        votes = candidates[offset]
        if offset >= major_size and 2 * sum(votes.values()) < len(flat):
            outliers.append({"offset": offset, "views": sum(votes.values()),
                             "sources": sorted(s for s, items in flat.items() if any(o == offset for o, *_ in items))})
            continue
        rule, pick = None, None
        if len(votes) == 1:
            rule, pick = "bytes", next(iter(votes))
        else:
            widths = access.get(offset, {})
            fits = [c for c in votes if c[0] in widths and len(widths) == 1]
            if len(fits) == 1:
                rule, pick = "retail-access", fits[0]
            elif offset in zh_at and (zh_at[offset][0], zh_at[offset][1]) in votes:
                rule, pick = "zh", (zh_at[offset][0], zh_at[offset][1])
            else:
                top = votes.most_common(2)
                if top[0][1] > top[1][1]:
                    rule, pick = "majority", top[0][0]
                else:
                    queue.append({"class": name, "attribute": f"field@{offset:#x}", "candidates":
                                  {f"{s}:{k}": n for (s, k), n in votes.items()}})
                    continue
        if offset in zh_at:
            label, label_rule = zh_at[offset][2], "zh"
        else:
            top = names[offset].most_common(2)
            label, label_rule = top[0][0], "majority" if len(top) < 2 or top[0][1] > top[1][1] else "tie"
            if label_rule == "tie":
                queue.append({"class": name, "attribute": f"name@{offset:#x}", "candidates": dict(names[offset])})
        type_name = types[(offset, *pick)].most_common(1)[0][0]
        if offset in zh_at and (zh_at[offset][0], zh_at[offset][1]) == pick:
            type_name = zh_at[offset][3]
        fields.append({"offset": offset, "size": pick[0], "kind": pick[1], "type": type_name, "name": label,
                       "decided_by": rule, "name_by": label_rule, "views": sum(votes.values()),
                       "retail_widths": access.get(offset, {}), "witness": witness.get(offset)})
    nested = []
    if zh and "layout" in zh:
        for offset, field, type_name, size in zh["layout"].get("fields", []):
            member = aggregate(zh["every"], type_name, size)
            if member is not None:
                nested.append((offset, size, type_name, field, "zh", leaf_shape(member, zh["every"], offset)))
    seen, shapes = collections.Counter(), {}
    for source, L in good.items():
        for offset, field, type_name, size in L.get("fields", []):
            member = aggregate(every[source], type_name, size)
            if member is not None:
                seen[(offset, size, type_name, field)] += 1
                shapes.setdefault((offset, size, type_name, field), leaf_shape(member, every[source], offset))
    nested += [(*member, "majority", shapes[member]) for member, _ in seen.most_common()]
    fields = regroup(name, fields, nested, queue)
    # A field that straddles another decided field is a layout conflict, whatever the votes say.
    spans = [(f["offset"], f["offset"] + f["size"]) for f in fields if f["size"]]
    for f in fields:
        if any(a < f["offset"] < b for a, b in spans):
            queue.append({"class": name, "attribute": f"straddle@{f['offset']:#x}", "candidates": {}})

    sizes = collections.Counter(L["size"] for L in good.values())
    end = max((f["offset"] + f["size"] for f in fields), default=0)
    retail_size = retail.get("facts", {}).get("sizeof", {}).get("value")
    if retail_size is not None:
        size, size_rule = retail_size, "retail-new"
        if retail_size < end:
            queue.append({"class": name, "attribute": "size", "candidates": {str(retail_size): "operator new",
                                                                             str(end): "decided fields"},
                          "why": "decided fields run past the size retail allocates"})
    elif zh and "layout" in zh and zh["layout"]["size"] >= end and zh["layout"]["size"] in sizes:
        size, size_rule = zh["layout"]["size"], "zh"
    else:
        fitting = collections.Counter({s: n for s, n in sizes.items() if s >= end})
        top = fitting.most_common(2)
        size, size_rule = (top[0][0], "majority") if top and (len(top) < 2 or top[0][1] > top[1][1]) else (end, "tie")
        if size_rule == "tie":
            queue.append({"class": name, "attribute": "size", "candidates": dict(sizes)})

    keys = ledger_key(name, rows)
    if keys and (len(keys) == 1 or keys.most_common(2)[0][1] > keys.most_common(2)[1][1]):
        key, key_rule = keys.most_common(1)[0][0], "bytes"
    elif zh and "layout" in zh:
        key, key_rule = zh["layout"]["key"], "zh"
    else:
        view_keys = collections.Counter(L["key"] for L in good.values())
        key, key_rule = view_keys.most_common(1)[0][0] if view_keys else "struct", "majority"

    slot_votes, every_vote = collections.defaultdict(collections.Counter), collections.defaultdict(collections.Counter)
    for source in good:
        for slot, member in view_slots[source].items():
            slot_votes[slot][member] += 1
        for slot, member in good[source].get("vslots", {}).items():
            every_vote[int(slot)][member] += 1
    # A constructor may prove the table address before vtables.tsv inventories
    # its entries. Missing slot evidence is unknown, not a zero-slot ABI bound.
    retail_slots = max((len(v["slots"]) for v in vtables.values() if v["slots"] and v.get("offset", 0) == 0),
                       default=None)
    zh_slots = {int(k): v for k, v in zh["layout"].get("vslots", {}).items()} if zh and "layout" in zh else {}
    vslots = {}
    # The retail bound judges every view's slot evidence, including the
    # inherited slots own_members set aside: a base that claims more slots than
    # the retail vftable holds is a conflict, never a reason to stop looking.
    if retail_slots is not None:
        for slot, votes in sorted(every_vote.items()):
            if slot >= retail_slots:
                queue.append({"class": name, "attribute": f"slot{slot}", "candidates": dict(votes),
                              "why": f"beyond the retail vftable's {retail_slots} slots"})
        if inherited["inherited_slots"] > retail_slots:
            queue.append({"class": name, "attribute": "base-slots", "candidates": {str(inherited["inherited_slots"]): 1},
                          "why": f"bases claim more than the retail vftable's {retail_slots} slots"})
    for slot, votes in sorted(slot_votes.items()):
        if retail_slots is not None and slot >= retail_slots:
            continue
        if len(votes) == 1:
            vslots[slot] = (next(iter(votes)), "bytes")
        elif zh_slots.get(slot) in votes:
            vslots[slot] = (zh_slots[slot], "zh")
        else:
            top = votes.most_common(2)
            if top[0][1] > top[1][1]:
                vslots[slot] = (top[0][0], "majority")
            else:
                queue.append({"class": name, "attribute": f"slot{slot}", "candidates": dict(votes)})

    return {
        "class": name, "key": key, "key_by": key_rule, "ledger_keys": dict(keys), "size": size, "size_by": size_rule,
        "bases": bases, "bases_by": base_rule, "fields": fields,
        "vslots": {str(k): {"member": m, "decided_by": r} for k, (m, r) in vslots.items()},
        "evidence": {"views": len(good), "view_errors": len(got) - len(good), "census": len(sources),
                     "view_sizes": dict(sizes), "zh": {k: v for k, v in (zh or {}).items() if k in ("header", "error")},
                     "retail_member_rows": len(thiscall_rows(name, rows)[0]),
                     "retail_access": {"%#x" % k: v for k, v in access.items()},
                     "witness_offsets": sorted(witness), "retail_vtables": vtables, "inherited": inherited,
                     "retail_layout": {k: v for k, v in retail.items() if k in ("facts", "conflicts", "confidence")},
                     "bases_overruled": overruled},
        "queue": queue,
        "outliers": outliers,
        "sources": sorted(good),
    }


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--class", dest="name", required=True)
    parser.add_argument("--sample", type=int, help="decide from a seeded sample of N views")
    parser.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) - 4))
    parser.add_argument("--write", action="store_true", help=f"write {CONTRACTS.relative_to(ROOT).as_posix()}/NAME.json")
    args = parser.parse_args(argv)
    contract = decide(args.name, jobs=args.jobs, sample=args.sample)
    if args.write:
        CONTRACTS.mkdir(parents=True, exist_ok=True)
        frozen = {k: v for k, v in contract.items() if k != "sources"}
        contract_path(args.name).write_text(json.dumps(frozen, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    ev = contract["evidence"]
    print(f"{args.name}: {contract['key']} ({contract['key_by']}), sizeof {contract['size']} ({contract['size_by']}), "
          f"bases {contract['bases']} ({contract['bases_by']}); {ev['views']} views, {ev['view_errors']} uncompiled, "
          f"zh {ev['zh'].get('header', '-')}")
    for f in contract["fields"]:
        print(f"  +{f['offset']:#05x} {f['size']} {f['type']:<12} {f['name']:<16} {f['decided_by']}/{f['name_by']}"
              f"  views={f['views']} retail={f['retail_widths']} witness={f['witness']}")
    for slot, v in contract["vslots"].items():
        print(f"  slot {slot}: {v['member']} ({v['decided_by']})")
    for item in contract["queue"]:
        print(f"  QUEUE {item['attribute']}: {item.get('candidates')} {item.get('why', '')}")
    return 1 if contract["queue"] else 0


if __name__ == "__main__":
    sys.exit(main())
