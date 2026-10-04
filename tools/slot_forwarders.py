#!/usr/bin/env python3
"""Size, classify and generate the small vtable-slot forwarders nobody owns.

`tools/vftable_map.py --unclaimed` lists the slot bodies no matched row
covers. Many of the small ones have no Ghidra size, so the pickers that read
sizes from reverse/ghidra_functions.csv never see them. Their bodies are
short straight-line hops, and the bytes alone determine both their extent
and C++ that reproduces them:

    mov eax,[ecx]; jmp [eax+N]                    this->slotN()
    mov ecx,[ecx+K]; mov eax,[ecx]; jmp [eax+N]   m_ptr->slotN()
    add ecx,K; mov eax,[ecx]; jmp [eax+N]         base-at-K->slotN()
    add ecx,K; jmp T                              m_member.T(args)
    mov ecx,[ecx+K]; jmp T                        m_ptr->T(args)

Sizing: decode from the slot address to the first unconditional `ret`/`jmp`
of a branch-free body, then require the next byte to be a known boundary
(int3 padding, a ledger or Ghidra start, or another slot body). A body that
fails that check is reported, never generated. row_extent and the byte gate
still decide every row.

Identity: every class and method generated here is address-derived; the bytes
prove the hop, the slot and (for a direct callee) the argument count read
from the callee's own `ret N`. A tail-jumped slot's argument count is not
provable from the forwarder (the arguments pass through untouched), so those
are declared without arguments and the row notes say so. A direct callee that
already has a ledger row or pin is reused under that name when its decoration
is simple enough to declare here; otherwise it is pinned by address.

    slot_forwarders.py scan  [--below 0x400000]        -> build/slot_forwarders/scan.csv
    slot_forwarders.py gen   --family F --source PATH [--limit N] [--skip RVA,...]
        writes PATH, build/slot_forwarders/rows.csv (add_match_batch manifest)
        and build/slot_forwarders/pins.csv (symbols.csv rows to append)
    slot_forwarders.py land  --family F --source PATH [--limit N]
        gen, append pins, add_match_batch; on a refusal, drop items one at a
        time by bisection until the rest verifies (each dropped RVA is listed)

Commit is left to the caller (stage the source, functions.csv, symbols.csv).
"""
import argparse
import bisect
import csv
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import callers_of  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "build" / "slot_forwarders"
BASE = 0x400000

try:
    from capstone import CS_ARCH_X86, CS_MODE_32, Cs
except ImportError:  # pragma: no cover
    sys.exit("slot_forwarders: needs capstone (pip install capstone)")


# --------------------------------------------------------------------- image

class Image:
    def __init__(self):
        self.data, secs = callers_of.load_image()
        self.off = callers_of.make_off(secs)
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)
        self.md.detail = False

    def insns(self, rva, n=96):
        o = self.off(rva)
        if o is None:
            return []
        return list(self.md.disasm(self.data[o:o + n], BASE + rva))

    def byte(self, rva):
        o = self.off(rva)
        return None if o is None else self.data[o]


def load_ledger():
    rows, starts, names = [], set(), {}
    with open(ROOT / "reverse" / "functions.csv", newline="") as fh:
        for r in csv.DictReader(fh):
            try:
                a = int(r["target_rva"], 16)
                n = int(r["target_size"] or 0)
            except (ValueError, KeyError):
                continue
            rows.append((a, max(n, 1)))
            starts.add(a)
            if r.get("status") == "matched" and "gen-alias" not in (r.get("notes") or ""):
                names.setdefault(a, r["name"])
    rows.sort()
    return rows, starts, names


def load_pins():
    pins = {}
    with open(ROOT / "reverse" / "symbols.csv", newline="") as fh:
        for r in csv.DictReader(fh):
            try:
                pins.setdefault(int(r["address"], 16), []).append(r["name"])
            except (ValueError, KeyError):
                continue
    return pins


def load_ghidra_starts():
    starts = set()
    with open(ROOT / "reverse" / "ghidra_functions.csv", newline="") as fh:
        for r in csv.reader(fh):
            try:
                starts.add(int(r[0], 16))
            except (ValueError, IndexError):
                continue
    return starts


def covered(rows, a):
    starts = [s for s, _ in rows]
    i = bisect.bisect_right(starts, a) - 1
    while i >= 0 and rows[i][0] > a - 0x10000:
        s, n = rows[i]
        if s <= a < s + n:
            return True
        i -= 1
    return False


# -------------------------------------------------------------------- shapes

HEX = r"(0x[0-9a-f]+|\d+)"


def num(text):
    return int(text, 16) if text.startswith(("0x", "-0x")) else int(text)


def straight_body(img, rva):
    """(size, [insn]) of a branch-free body ending in ret/jmp, else None."""
    out = []
    for i in img.insns(rva):
        out.append(i)
        if i.mnemonic in ("ret", "jmp"):
            return i.address - BASE + i.size - rva, out
        if i.mnemonic.startswith("j") or i.mnemonic in ("int3", "call"):
            return None
        if len(out) > 12:
            return None
    return None


def callee_ret(img, rva, budget=0x3000):
    """The `ret N` byte count every path of the callee at `rva` ends with.

    Follows conditional branches inside the callee; a tail `jmp` out of the
    walked region, an indirect jump, or two different `ret` forms give None.
    """
    seen, todo, rets, steps = set(), [rva], set(), 0
    while todo:
        a = todo.pop()
        while True:
            if a in seen or steps > budget:
                break
            seen.add(a)
            steps += 1
            ins = img.insns(a, 16)
            if not ins:
                return None
            i = ins[0]
            a = i.address - BASE + i.size
            m = i.mnemonic
            if m == "ret":
                rets.add(num(i.op_str) if i.op_str else 0)
                break
            if m == "jmp":
                if not i.op_str.startswith("0x"):
                    return None  # switch table or tail vcall: count unknown
                t = int(i.op_str, 16) - BASE
                if not (rva <= t < rva + 0x4000):
                    return None  # tail call to another function
                todo.append(t)
                break
            if m.startswith("j") or m.startswith("loop"):
                if i.op_str.startswith("0x"):
                    todo.append(int(i.op_str, 16) - BASE)
            if m == "int3":
                return None
    return rets.pop() if len(rets) == 1 else None


def resolve_thunks(img, rva, starts_known):
    for _ in range(8):
        if img.byte(rva) != 0xE9 or rva in starts_known:
            break
        o = img.off(rva)
        rva = rva + 5 + struct.unpack_from("<i", img.data, o + 1)[0]
    return rva


def classify(ins):
    """(family, params) for a recognised hop shape, else (None, shape)."""
    text = [f"{i.mnemonic} {i.op_str}".strip() for i in ins]
    shape = " ; ".join(text)
    hop = None
    rest = text
    m = re.fullmatch(r"mov ecx, dword ptr \[ecx \+ " + HEX + r"\]", text[0])
    if m:
        hop, rest = ("ptr", num(m.group(1))), text[1:]
    else:
        m = re.fullmatch(r"add ecx, " + HEX, text[0])
        if m and num(m.group(1)) > 0:
            hop, rest = ("sub", num(m.group(1))), text[1:]
    if len(rest) == 2 and rest[0] == "mov eax, dword ptr [ecx]":
        m = re.fullmatch(r"jmp dword ptr \[eax(?: \+ " + HEX + r")?\]", rest[1])
        if m:
            slot = num(m.group(1)) if m.group(1) else 0
            if slot % 4 == 0:
                return ("vjmp", {"hop": hop, "vslot": slot // 4}), shape
    if hop and len(rest) == 1:
        m = re.fullmatch(r"jmp (0x[0-9a-f]+)", rest[0])
        if m:
            return ("djmp", {"hop": hop, "target": int(m.group(1), 16) - BASE}), shape
    return (None, None), shape


# ------------------------------------------------------------------- scanning

def scan(args):
    img = Image()
    rows, lstarts, _ = load_ledger()
    gstarts = load_ghidra_starts()
    slots = []
    with open(args.vft, newline="") as fh:
        for r in csv.DictReader(fh):
            a = int(r["body_rva"], 16)
            if a < args.below:
                slots.append((a, r["first_table"], r["first_slot"], r["first_table_name"]))
    bodies = {a for a, *_ in slots}
    known = lstarts | gstarts | bodies
    OUT.mkdir(parents=True, exist_ok=True)
    fams = {}
    with open(OUT / "scan.csv", "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        w.writerow(["rva", "size", "boundary", "family", "table", "slot", "table_name", "shape"])
        for a, table, slot, tname in sorted(slots):
            if covered(rows, a):
                continue
            body = straight_body(img, a)
            if body is None:
                continue
            size, ins = body
            nxt = a + size
            boundary = "int3" if img.byte(nxt) == 0xCC else ("start" if nxt in known else "unproven")
            (fam, _), shape = classify(ins)
            fam = fam or "-"
            w.writerow([f"0x{a:08X}", size, boundary, fam, table, slot, tname, shape])
            if boundary != "unproven":
                fams[fam] = fams.get(fam, 0) + 1
    for fam, n in sorted(fams.items(), key=lambda kv: -kv[1]):
        print(f"{n:5d}  {fam}")
    print(f"slot_forwarders: wrote {OUT / 'scan.csv'}")


# ----------------------------------------------------------------- generation

SIMPLE = {"X": "void", "H": "Int", "_N": "Bool", "M": "Real", "PAX": "void *", "I": "UnsignedInt"}
DECL = re.compile(r"^\?(\w+)@(\w+)@@QAE(.+)$")


def parse_type(code):
    """(c type, rest) for one simple decoration at the head of `code`."""
    for k in ("PAX", "_N", "X", "H", "M", "I"):
        if code.startswith(k):
            return SIMPLE[k], code[len(k):], None
    m = re.match(r"(PA|AA|PB|AB)V(\w+)@@", code)
    if m:
        q, cls = m.group(1), m.group(2)
        ct = ("const " if q[1] == "B" else "") + cls + (" *" if q[0] == "P" else " &")
        return ct, code[m.end():], cls
    return None, code, None


def declare_named(name):
    """Declaration pieces for a non-virtual member decoration, or None."""
    m = DECL.match(name)
    if not m:
        return None
    meth, cls, rest = m.groups()
    fwd = set()
    ret, rest, c = parse_type(rest)
    if ret is None:
        return None
    if c:
        fwd.add(c)
    params = []
    if rest == "XZ":
        pass
    else:
        while rest and rest != "@Z":
            t, rest, c = parse_type(rest)
            if t is None:
                return None
            if c:
                fwd.add(c)
            params.append(t)
        if rest != "@Z":
            return None
    return {"cls": cls, "meth": meth, "ret": ret, "params": params, "fwd": fwd}


def mangle_args(n):
    return "XZ" if n == 0 else "H" * n + "@Z"


def gen_items(args):
    img = Image()
    rows, lstarts, names = load_ledger()
    pins = load_pins()
    skip = {int(x, 16) for x in (args.skip or "").split(",") if x}
    items, refused = [], []
    with open(OUT / "scan.csv", newline="") as fh:
        for r in csv.DictReader(fh):
            if r["family"] != args.family or r["boundary"] == "unproven":
                continue
            a = int(r["rva"], 16)
            if a in skip or covered(rows, a):
                continue
            body = straight_body(img, a)
            (fam, p), shape = classify(body[1])
            item = {"rva": a, "size": int(r["size"]), "table": r["table"], "slot": r["slot"],
                    "tname": r["table_name"], "shape": shape, **p}
            if fam == "djmp":
                t = resolve_thunks(img, p["target"], lstarts)
                item["target"] = t
                named = names.get(t) or (pins.get(t) or [None])[0]
                if named:
                    decl = declare_named(named)
                    if decl is None:
                        refused.append((a, f"callee 0x{t:08X} is {named}: not declarable here"))
                        continue
                    item["callee"] = decl
                    item["callee_name"] = named
                    item["pin"] = None
                else:
                    n = callee_ret(img, t)
                    if n is None or n % 4:
                        refused.append((a, f"callee 0x{t:08X}: argument count not provable"))
                        continue
                    cls = f"Rva{t:08X}Target"
                    meth = f"rva{t:08X}"
                    decl = {"cls": cls, "meth": meth, "ret": "void",
                            "params": ["Int"] * (n // 4), "fwd": set()}
                    item["callee"] = decl
                    item["callee_name"] = f"?{meth}@{cls}@@QAEX{mangle_args(n // 4)}"
                    item["pin"] = item["callee_name"]
            items.append(item)
            if args.limit and len(items) >= args.limit:
                break
    return items, refused


def emit(items, family):
    lines = [
        "// cl: /O1 /DNDEBUG /MD",
        "//",
        "// Vtable-slot forwarders with no ledger owner and no Ghidra size, generated",
        f"// by tools/slot_forwarders.py (family {family}). Each body was sized from its",
        "// bytes (a branch-free hop ending in jmp, followed by a known boundary).",
        "// Every class and method here is address-derived: the bytes prove the hop",
        "// and the slot or callee, nothing more. A tail-jumped virtual slot passes",
        "// the caller's arguments through untouched, so its argument count is not",
        "// provable and the slot is declared without arguments (inference).",
        "// A direct callee's argument count comes from its own ret N; an unnamed",
        "// callee is pinned by address in reverse/symbols.csv.",
        "",
        "typedef int Int;",
        "typedef bool Bool;",
        "typedef float Real;",
        "typedef unsigned int UnsignedInt;",
        "",
    ]
    fwd = set()
    for it in items:
        if "callee" in it:
            fwd |= it["callee"]["fwd"]
    for c in sorted(fwd):
        lines.append(f"class {c};")
    if fwd:
        lines.append("")
    if family == "vjmp":
        # One slot table serves every item: only the slot index reaches the bytes.
        lines += ["class SizedForwarderSlots", "{", "public:"]
        lines += [f"\tvirtual void slot{k}();" for k in range(max(i["vslot"] for i in items) + 1)]
        lines += ["};", ""]
    declared = set()
    for it in items:
        a = it["rva"]
        fcls, fmeth = f"Rva{a:08X}Forwarder", f"rva{a:08X}"
        hop = it["hop"]
        where = f"vtable {it['table']}#{it['slot']}" + (f" ({it['tname']})" if it["tname"] else "")
        if family == "vjmp":
            icls = "SizedForwarderSlots"
            slot = it["vslot"]
            if hop is None:
                lines += [f"class {fcls} : public {icls}", "{", "public:",
                          f"\tvoid {fmeth}();", "};", "",
                          f"// {where}: this->slot{slot}()",
                          f"void {fcls}::{fmeth}()", "{", f"\tslot{slot}();", "}", ""]
            elif hop[0] == "ptr":
                lines += [f"class {fcls}", "{", "public:", f"\tvoid {fmeth}();", "private:",
                          f"\tchar m_lead[0x{hop[1]:X}];", f"\t{icls} *m_inner;", "};", "",
                          f"// {where}: (+0x{hop[1]:X})->slot{slot}()",
                          f"void {fcls}::{fmeth}()", "{", f"\tm_inner->slot{slot}();", "}", ""]
            else:
                lead = f"Rva{a:08X}Lead"
                pad = ["private:", f"\tchar m_lead[0x{hop[1] - 4:X}];"] if hop[1] > 4 else []
                lines += [f"class {lead}", "{", "public:", "\tvirtual void lead0();", *pad, "};", "",
                          f"class {fcls} : public {lead}, public {icls}", "{", "public:",
                          f"\tvoid {fmeth}();", "};", "",
                          f"// {where}: base at +0x{hop[1]:X} ->slot{slot}()",
                          f"void {fcls}::{fmeth}()", "{",
                          f"\tslot{slot}();", "}", ""]
            it["name"] = f"?{fmeth}@{fcls}@@QAEXXZ"
            it["note"] = f"{where} slot forwarder to slot {slot} (arguments unproven)"
        else:
            d = it["callee"]
            if d["cls"] not in declared:
                declared.add(d["cls"])
                ps = ", ".join(f"{t} a{k}" for k, t in enumerate(d["params"]))
                lines += [f"class {d['cls']}", "{", "public:",
                          f"\t{d['ret']} {d['meth']}({ps});", "};", ""]
            ps = ", ".join(f"{t} a{k}" for k, t in enumerate(d["params"]))
            av = ", ".join(f"a{k}" for k in range(len(d["params"])))
            member = (f"\t{d['cls']} *m_target;" if hop[0] == "ptr" else f"\t{d['cls']} m_target;")
            call = "m_target->" if hop[0] == "ptr" else "m_target."
            ret = "" if d["ret"] == "void" else "return "
            lines += [f"class {fcls}", "{", "public:", f"\t{d['ret']} {fmeth}({ps});", "private:",
                      f"\tchar m_lead[0x{hop[1]:X}];", member, "};", "",
                      f"// {where}: {'(+0x%X)->' % hop[1] if hop[0] == 'ptr' else '+0x%X.' % hop[1]}"
                      f"{d['meth']}",
                      f"{d['ret']} {fcls}::{fmeth}({ps})", "{",
                      f"\t{ret}{call}{d['meth']}({av});", "}", ""]
            dec = it["callee_name"][len(f"?{d['meth']}@{d['cls']}@@QAE"):]
            it["name"] = f"?{fmeth}@{fcls}@@QAE{dec}"
            it["note"] = f"{where} slot forwarder ({hop[0]} hop +0x{hop[1]:X}) to 0x{it['target']:08X}"
    return "\n".join(lines).rstrip() + "\n"




def generate(args, items):
    src = ROOT / args.source
    src.parent.mkdir(parents=True, exist_ok=True)
    text = emit(items, args.family)
    src.write_text(text, encoding="utf-8", newline="\n")
    OUT.mkdir(parents=True, exist_ok=True)
    with open(OUT / "rows.csv", "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        for it in items:
            w.writerow([it["name"], f"0x{it['rva']:08X}", it["size"], args.source,
                        it["note"].replace(",", ";")])
    with open(OUT / "pins.csv", "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        seen = set()
        for it in items:
            if it.get("pin") and it["pin"] not in seen:
                seen.add(it["pin"])
                w.writerow([it["pin"], f"0x{it['target']:08X}",
                            f"callee of {it['name']} at retail 0x{it['rva']:08X} read from its "
                            f"REL32 displacement; argument count from the callee's ret"])
    return text




def run_batch():
    return subprocess.run([sys.executable, "tools/add_match_batch.py", str(OUT / "rows.csv")],
                          cwd=ROOT, capture_output=True, text=True)


def append_pins(lines):
    path = ROOT / "reverse" / "symbols.csv"
    with open(path, "a", newline="") as fh:
        for line in lines:
            fh.write(line + "\n")


def land(args):
    items, refused = gen_items(args)
    for a, why in refused:
        print(f"refused 0x{a:08X}: {why}")
    symbols = ROOT / "reverse" / "symbols.csv"
    original = symbols.read_bytes()
    good, dropped = list(items), []

    def attempt(batch):
        symbols.write_bytes(original)
        if not batch:
            return True
        generate(args, batch)
        pin_lines = (OUT / "pins.csv").read_text().splitlines()
        append_pins(pin_lines)
        res = run_batch()
        if res.returncode != 0:
            print(res.stdout[-1500:] + res.stderr[-1500:])
        return res.returncode == 0

    if attempt(good):
        print(f"landed {len(good)} rows, {sum(i['size'] for i in good)} bytes")
        return 0
    # Find the failing items one at a time: verify each alone, keep the passing set.
    keep = []
    for it in good:
        if attempt([it]):
            # roll the single landing back before trying the next one
            subprocess.run(["git", "checkout", "--", "reverse/functions.csv"], cwd=ROOT)
            keep.append(it)
        else:
            dropped.append(it)
    if keep and attempt(keep):
        print(f"landed {len(keep)} rows, {sum(i['size'] for i in keep)} bytes")
    else:
        symbols.write_bytes(original)
        (ROOT / args.source).unlink(missing_ok=True)
        keep = []
    for it in dropped:
        print(f"dropped 0x{it['rva']:08X}: does not verify ({it['shape']})")
    return 0 if keep else 1




def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("scan")
    s.add_argument("--below", type=lambda x: int(x, 16), default=0x400000)
    s.add_argument("--vft", default=str(ROOT / "build" / "vft_unclaimed.csv"))
    for name in ("gen", "land"):
        g = sub.add_parser(name)
        g.add_argument("--family", required=True, choices=("vjmp", "djmp"))
        g.add_argument("--source", required=True)
        g.add_argument("--limit", type=int, default=0)
        g.add_argument("--skip", default="")
    args = ap.parse_args()
    if args.cmd == "scan":
        return scan(args)
    if args.cmd == "gen":
        items, refused = gen_items(args)
        generate(args, items)
        for a, why in refused:
            print(f"refused 0x{a:08X}: {why}")
        print(f"generated {len(items)} items, {sum(i['size'] for i in items)} bytes -> {args.source}")
        return 0
    return land(args)


if __name__ == "__main__":
    sys.exit(main())
