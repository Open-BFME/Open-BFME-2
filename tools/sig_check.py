#!/usr/bin/env python3
"""Check a C++ declaration against what the retail bytes say about its signature.

Before spending compiles on a body, compare the declaration a seat wrote (or
wb_draft.py produced) with the retail evidence for the same address:

  conv       `ret N` in the callee: N > 0 means the callee pops its arguments
             (stdcall / thiscall), a plain `ret` means cdecl (or no arguments)
  args       N against the declared argument bytes; for cdecl, the `add esp, N`
             / `pop ecx` cleanup at every retail call site (a merged cleanup is
             larger, never smaller, so a smaller one is a hard mismatch); the
             highest incoming stack slot the callee reads
  this       ecx read before written in the callee (thiscall / member) vs a
             free or static declaration; a member whose callers never load ecx
  fastcall   edx read before written as well
  return     callers reading eax/al right after the call (a value comes back),
             consuming st0 (float/double), or neither (void)
  sign       jl/jg/jle/jge/js vs jb/ja/jbe/jae on a compare of an incoming
             parameter, against the declared parameter's signedness
  bool       sete vs setne against `return a == b` / `return a != b` in the
             source body (--source only)

The declaration comes from --source (the function's definition in that file,
found by the row's or --name's Class::method), else from the ledger row's
mangled name. Each finding is a lead for the draft, never a gate; calibration
over matched rows (`--calibrate N`) reports how often each check fires on
bodies that already byte-match, which is its false-positive rate.

    python3 tools/sig_check.py <rva|ledger name> [--source FILE] [--name Class::method] [--json]
    python3 tools/sig_check.py --calibrate 400 [--seed 7]
"""
import argparse
import json
import random
import re
import sys
from collections import Counter, namedtuple
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import retail_body as rb
import wb_gold

Param = namedtuple("Param", "kind size signed text")   # kind: int ptr float bool char class void unknown
Decl = namedtuple("Decl", "conv member params ret variadic origin name")

SIGNED_JCC = {"jl", "jg", "jle", "jge", "js", "jns"}
UNSIGNED_JCC = {"jb", "ja", "jbe", "jae"}
EH_PROLOG = 0x00629188
X87_CONSUMERS = re.compile(r"^f(?!ld|ild|ldz|ld1|nstsw|nstcw|ldcw|wait|init|clex)")


# ------------------------------------------------------- mangled names

_MANGLED_SIMPLE = {
    "X": Param("void", 0, None, "void"), "C": Param("char", 1, True, "signed char"),
    "D": Param("char", 1, True, "char"), "E": Param("char", 1, False, "unsigned char"),
    "F": Param("int", 2, True, "short"), "G": Param("int", 2, False, "unsigned short"),
    "H": Param("int", 4, True, "int"), "I": Param("int", 4, False, "unsigned int"),
    "J": Param("int", 4, True, "long"), "K": Param("int", 4, False, "unsigned long"),
    "M": Param("float", 4, True, "float"), "N": Param("float", 8, True, "double"),
    "O": Param("float", 8, True, "long double"),
    "_N": Param("bool", 1, False, "bool"), "_J": Param("int", 8, True, "__int64"),
    "_K": Param("int", 8, False, "unsigned __int64"), "_W": Param("int", 2, False, "wchar_t"),
}
MEMBER_CODES = set("ABEFIJMNQRUV")
STATIC_CODES = set("CDKLST")
ADJUSTOR_CODES = set("GHOPWX")
CONVENTIONS = {"A": "cdecl", "C": "pascal", "E": "thiscall", "G": "stdcall", "I": "fastcall"}


def mangled_param(text):
    if text.startswith(("?A", "?B")):
        text = text[2:]
    if text in _MANGLED_SIMPLE:
        return _MANGLED_SIMPLE[text]
    head = text[:1]
    if head in "PQRS":
        return Param("ptr", 4, False, text)
    if head in "AB":
        return Param("ptr", 4, False, text)
    if text.startswith("W4"):
        return Param("int", 4, True, text)
    if head in "TUV":
        return Param("class", None, None, text)
    return Param("unknown", None, None, text)


def decl_from_mangled(symbol):
    """Decl for a mangled MSVC function symbol, or None when not parseable."""
    if not symbol or not symbol.startswith("?"):
        return None
    p = wb_gold._Parser(symbol)
    try:
        p.expect("?")
        if p.peek(2) == "?$":
            key, name = p.template_name()
            p.memorize(key, name)
        elif p.peek() == "?":
            name = p.special_name()
        else:
            name = p.simple_name()
            p.memorize(name, name)
        p.scopes()
        code = p.take()
        if code in ADJUSTOR_CODES or code == "$":
            return None
        if code in MEMBER_CODES:
            p.storage_cv()
            member = True
        elif code in STATIC_CODES or code in "YZ":
            member = False
        else:
            return None
        conv = CONVENTIONS.get(p.take())
        if conv is None:
            return None
        if p.peek() == "@":
            p.i += 1
            ret = Param("ctor", 4, None, "(ctor/dtor)")
        else:
            start = p.i
            p.type()
            ret = mangled_param(p.s[start:p.i])
        params, table, variadic = [], [], False
        if p.peek() == "X":
            p.i += 1
        else:
            while p.peek() not in ("@", "Z", ""):
                start = p.i
                if p.peek().isdigit():
                    index = int(p.take())
                    text = table[index] if index < len(table) else "?"
                else:
                    p.type()
                    text = p.s[start:p.i]
                    if len(text) > 1 and len(table) < 10:
                        table.append(text)
                params.append(mangled_param(text))
            if p.peek() == "Z":
                variadic = True
    except (wb_gold.DemangleError, IndexError):
        return None
    if ret.kind == "class":
        ret = ret._replace(kind="hidden")
    return Decl(conv, member, params, ret, variadic, "mangled", symbol)


# --------------------------------------------------------- source text

_UNSIGNED_WORDS = re.compile(
    r"\b(?:unsigned|Unsigned\w*|UINT\w*|DWORD|WORD|BYTE|UCHAR|USHORT|ULONG|size_t|"
    r"uint\w*|UnsignedInt|Bool|BOOL)\b")
_SIGNED_WORDS = re.compile(r"\b(?:int|Int\w*|long|short|Short|char|Char|signed|LONG|INT|Real)\b")


GHIDRA_TYPES = {"undefined1": Param("char", 1, None, "undefined1"),
                "undefined2": Param("int", 2, None, "undefined2"),
                "undefined4": Param("int", 4, None, "undefined4"),
                "undefined8": Param("int", 8, None, "undefined8"),
                "undefined": Param("char", 1, None, "undefined"),
                "byte": Param("char", 1, False, "byte"), "ushort": Param("int", 2, False, "ushort"),
                "uint": Param("int", 4, False, "uint"), "ulong": Param("int", 4, False, "ulong"),
                "float10": Param("float", 10, True, "float10")}


def text_param(text):
    t = re.sub(r"\s+", " ", re.sub(r"=.*$", "", text)).strip()
    t = re.sub(r"/\*.*?\*/", "", t).strip()
    if not t or t == "void":
        return Param("void", 0, None, t)
    if "*" in t or "&" in t:
        return Param("ptr", 4, False, t)
    head = t.split()[0]
    if head in GHIDRA_TYPES:
        return GHIDRA_TYPES[head]._replace(text=t)
    words = re.sub(r"\b(?:const|volatile|struct|class|enum|register)\b", " ", t).split()
    base = " ".join(words[:-1]) if len(words) > 1 else " ".join(words)
    if re.search(r"\b(?:double)\b", base):
        return Param("float", 8, True, t)
    if re.search(r"\b(?:float|Real)\b", base):
        return Param("float", 4, True, t)
    if re.search(r"\b(?:bool|Bool)\b", base):
        return Param("bool", 1, False, t)
    if re.search(r"__int64|Int64|long long", base):
        return Param("int", 8, "unsigned" not in base.lower(), t)
    if _UNSIGNED_WORDS.search(base):
        size = 1 if re.search(r"char|Byte|BYTE|UCHAR", base) else 2 if re.search(r"short|Short|WORD\b|USHORT", base) else 4
        return Param("char" if size == 1 else "int", size, False, t)
    if _SIGNED_WORDS.search(base):
        size = 1 if re.search(r"char|Char", base) else 2 if re.search(r"short|Short", base) else 4
        return Param("char" if size == 1 else "int", size, True, t)
    return Param("unknown", None, None, t)


def split_params(text):
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur))
    return [p.strip() for p in out]


def find_definition(text, qualified, arity=None):
    """(prefix, params text, body text) of `qualified(...)` defined in text;
    with arity, the first overload taking that many parameters."""
    found = list(definitions(text, qualified))
    if arity is not None:
        for item in found:
            params = [p for p in split_params(item[1]) if p.strip() not in ("", "void")]
            if len(params) == arity:
                return item
    return found[0] if found else None


def definitions(text, qualified):
    parts = qualified.split("::")
    pattern = r"\s*::\s*".join(re.escape(p) for p in parts)
    for match in re.finditer(r"(^|[\s\*&])" + pattern + r"\s*\(", text, re.M):
        start = match.end()
        depth, i = 1, start
        while i < len(text) and depth:
            depth += {"(": 1, ")": -1}.get(text[i], 0)
            i += 1
        params = text[start:i - 1]
        rest = text[i:i + 200]
        brace = re.match(r"\s*(?:const\s*)?(?:throw\s*\([^)]*\)\s*)?(?::[^{;]*)?\{", rest)
        if not brace:
            continue
        line_start = text.rfind("\n", 0, match.start() + len(match.group(1))) + 1
        prefix = text[line_start:match.start() + len(match.group(1))]
        body_start = i + brace.end()
        depth, j = 1, body_start
        while j < len(text) and depth:
            depth += {"{": 1, "}": -1}.get(text[j], 0)
            j += 1
        yield prefix, params, text[body_start:j - 1]


def decl_from_source(path, qualified, mangled=None):
    """Decl from the definition of `qualified` in path; member-ness and
    static-ness fall back to the mangled row name when the text cannot say."""
    try:
        text = Path(path).read_text(encoding="utf-8-sig", errors="replace")
    except OSError:
        return None, None
    try:
        shown = Path(path).resolve().relative_to(rb.ROOT)
    except ValueError:
        shown = path
    return decl_from_text(text, qualified, mangled, f"source {shown}")


def decl_from_text(text, qualified, mangled=None, origin="text", assume_member=None):
    """(Decl, body) from a definition in text; see decl_from_source.
    assume_member decides member-ness when neither a mangled name nor a
    class declaration in the text can (wb_draft drafts: WB names are members)."""
    known = decl_from_mangled(mangled) if mangled else None
    arity = len(known.params) + (1 if known.variadic else 0) if known else None
    found = find_definition(text, qualified, arity)
    if not found:
        return None, None
    prefix, params_text, body = found
    conv = None
    for word, name in (("__stdcall", "stdcall"), ("WINAPI", "stdcall"), ("__fastcall", "fastcall"),
                       ("__cdecl", "cdecl"), ("__thiscall", "thiscall")):
        if word in prefix:
            conv = name
    scoped = "::" in qualified
    static = bool(re.search(r"\bstatic\b", prefix))
    if known is not None:
        member = known.member and not static
    elif assume_member is not None:
        member = assume_member and scoped and not static
    else:
        cls = qualified.split("::")[-2] if scoped else None
        member = scoped and not static and bool(
            cls and re.search(r"\b(?:class|struct)\s+" + re.escape(cls) + r"\b", text))
    if conv is None:
        conv = "thiscall" if member else (known.conv if known and not known.member else "cdecl")
    params = [text_param(p) for p in split_params(params_text)]
    variadic = any(p.text == "..." for p in params)
    params = [p for p in params if p.kind != "void" and p.text != "..."]
    ret_text = re.sub(r"\b(?:static|inline|virtual|__forceinline|__inline|extern|__\w+call|WINAPI)\b",
                      " ", prefix).strip()
    name = qualified.split("::")[-1]
    if not ret_text or name == qualified.split("::")[-2:][0] and scoped or name.startswith("~"):
        ret = Param("ctor", 4, None, "(ctor/dtor)") if not ret_text else \
            text_param(ret_text + " r")._replace(text=ret_text)
    else:
        ret = text_param(ret_text + " r")._replace(text=ret_text)
        if ret.kind == "unknown" and known is not None and known.ret.kind == "hidden":
            ret = known.ret
    return Decl(conv, member, params, ret, variadic, origin, qualified), body


def arg_bytes(decl):
    """Stack bytes the declaration passes, or None when a size is unknown."""
    total = 0
    params = list(decl.params)
    if decl.conv == "fastcall":
        regs = 2
        kept = []
        for p in params:
            if regs and p.size is not None and p.size <= 4 and p.kind != "float":
                regs -= 1
                continue
            kept.append(p)
        params = kept
    for p in params:
        if p.size is None:
            return None
        total += (p.size + 3) // 4 * 4
    if decl.ret.kind == "hidden":
        total += 4
    return total


# ------------------------------------------------------ retail evidence

Evidence = namedtuple("Evidence", "rets live stack_max sites compares setcc x87 st0_tail")
Site = namedtuple("Site", "caller at sets_ecx cleanup ret_use")


def _esp_delta(insn):
    m, ops = insn.mnem, insn.ops
    if m == "push":
        return 4
    if m == "pop":
        return -4
    if m in ("sub", "add") and ops.startswith("esp, ") and insn.imm is not None:
        return insn.imm if m == "sub" else -insn.imm
    if m == "pushal":
        return 32
    if m == "popal":
        return -32
    return 0


SLOT_RE = re.compile(r"\[(esp|ebp)(?: \+ (0x[0-9a-f]+|\d+))?\]")


def param_slot(ops, depth, ebp_frame):
    """Index of the incoming stack parameter an operand addresses, or None."""
    match = SLOT_RE.search(ops)
    if not match:
        return None
    base, off = match.group(1), int(match.group(2) or "0", 0)
    if base == "esp":
        if depth is None:
            return None
        rel = off - depth - 4
    elif ebp_frame:
        rel = off - 8
    else:
        return None
    return rel // 4 if rel >= 0 and rel % 4 == 0 else None


def callee_pops(target, cache={}, depth=0):
    """ret N of a direct callee (0 for plain ret), None if unknown. A body
    with no ret that ends in a tail jump answers for its jump target."""
    if target in cache:
        return cache[target]
    size = rb.function_size(target)
    value = None
    if size and size < 20000 and depth < 4:
        insns = rb.disasm(target, size)
        rets = {insn.imm or 0 for insn in insns if insn.mnem == "ret"}
        if len(rets) == 1:
            value = rets.pop()
        elif not rets and insns and insns[-1].mnem == "jmp" and insns[-1].target is not None \
                and not target <= insns[-1].target < target + size:
            value = callee_pops(insns[-1].target, cache, depth + 1)
    cache[target] = value
    return value


def walk_stack(insns, on_insn):
    """Linear walk with an ESP depth (bytes below the return address), restored
    at branch targets; calls on_insn(index, insn, depth before, ebp_frame)."""
    depth, ebp_frame = 0, False
    at_target = {}
    pending = 0
    written = set()   # callee-saved registers this body has written
    for i, insn in enumerate(insns):
        if insn.rva in at_target and (depth is None or i and insns[i - 1].mnem in ("jmp", "ret")):
            depth = at_target[insn.rva]
        on_insn(i, insn, depth, ebp_frame)
        if i == 1 and insns[0].mnem == "push" and insns[0].ops == "ebp" and insn.ops == "ebp, esp":
            ebp_frame = True
        if depth is None:
            continue
        if insn.mnem == "call" and insn.target == EH_PROLOG:
            # __EH_prolog builds an ebp frame and moves esp under it.
            ebp_frame, depth, pending = True, None, 0
            continue
        if insn.mnem == "call":
            nxt = insns[i + 1] if i + 1 < len(insns) else None
            pops = callee_pops(insn.target) if insn.target is not None else None
            if pops is None:
                cleaned = nxt is not None and nxt.mnem == "add" and nxt.ops.startswith("esp, ")
                pops = 0 if cleaned else pending
            depth -= pops
            pending = 0
            continue
        delta = _esp_delta(insn)
        depth += delta
        if insn.mnem == "push" and not (insn.ops in rb.CALLEE_SAVED and insn.ops not in written):
            pending += 4  # an argument push; a save of an untouched callee-saved reg is not
        written.update(reg for reg in insn.writes if reg in rb.CALLEE_SAVED)
        if insn.mnem in ("jmp",) or insn.mnem in rb.JCC:
            if insn.target is not None:
                at_target.setdefault(insn.target, depth)
        if insn.mnem in ("jmp", "ret"):
            depth = None
        if "esp" in insn.writes and delta == 0 and insn.mnem not in ("push", "pop", "call", "ret") \
                and not insn.ops.startswith("esp, ebp") and insn.mnem != "mov":
            depth = None


def callee_evidence(rva, size, data=None):
    insns = rb.disasm(rva, size, data=data)
    tables = rb.table_targets(insns, rva, size, data=data) if data is None else {}
    rets = sorted({insn.imm or 0 for insn in insns if insn.mnem == "ret"})
    live = rb.live_in(insns, tables)
    stack_max = [None]
    reg_param = {}
    compares = {}      # param index -> Counter(signed/unsigned)
    pending_cmp = [None]

    straight = [True]   # still before the first call or branch: depth is exact

    def visit(i, insn, depth, ebp_frame):
        slot = param_slot(insn.ops, depth, ebp_frame) if "ptr [" in insn.ops else None
        if slot is not None and insn.mnem != "lea" and straight[0]:
            stack_max[0] = max(stack_max[0] or 0, (slot + 1) * 4)
        if insn.mnem == "call" or insn.mnem == "jmp" or insn.mnem in rb.JCC:
            straight[0] = False
        if insn.mnem in rb.JCC and pending_cmp[0] is not None:
            kind = "signed" if insn.mnem in SIGNED_JCC else "unsigned" if insn.mnem in UNSIGNED_JCC else None
            if kind:
                compares.setdefault(pending_cmp[0], Counter())[kind] += 1
        if insn.mnem in ("cmp", "test"):
            first = insn.ops.split(", ")[0]
            target = slot if slot is not None and insn.ops.find("[") < insn.ops.find(",") else reg_param.get(first)
            pending_cmp[0] = target
        elif insn.mnem not in rb.JCC:
            pending_cmp[0] = None
        written = list(insn.writes)
        for reg in written:
            reg_param.pop(reg, None)
        if insn.mnem == "mov" and slot is not None and insn.ops.split(", ")[0] in rb.GPRS:
            reg_param[insn.ops.split(", ")[0]] = slot

    walk_stack(insns, visit)
    setcc = Counter(insn.mnem for insn in insns if insn.mnem.startswith("set"))
    return insns, rets, live, stack_max[0], compares, setcc


EPILOGUE = {"pop", "leave", "add", "mov"}
# x87 instructions that do not leave a fresh value in st0
X87_NO_RESULT = {"fstp", "fistp", "fisttp", "fcomp", "fucomp", "fcompp", "fucompp", "fnstsw",
                 "fnstcw", "fstsw", "fstcw", "fldcw", "fnclex", "fwait", "ffree", "fninit"}


def x87_shape(insns):
    """(touches x87 at all or calls out, every ret is preceded by an st0-leaving
    x87 instruction) for the callee-side float-return checks."""
    x87 = any(insn.mnem.startswith("f") for insn in insns) or any(insn.mnem == "call" for insn in insns)
    tails = []
    for i, insn in enumerate(insns):
        if insn.mnem != "ret":
            continue
        j = i - 1
        while j >= 0 and insns[j].mnem in EPILOGUE and not insns[j].mnem.startswith("f") \
                and (insns[j].mnem != "mov" or "fs:" in insns[j].ops or insns[j].ops.startswith("ecx")):
            j -= 1
        prev = insns[j] if j >= 0 else None
        tails.append(prev is not None and prev.mnem.startswith("f") and prev.mnem not in X87_NO_RESULT)
    return x87, bool(tails) and all(tails)


def site_evidence(caller, target):
    """Site records for every direct call from caller to target."""
    size = rb.function_size(caller)
    if not size or size > 40000:
        return []
    insns = rb.disasm(caller, size)
    out = []
    for i, insn in enumerate(insns):
        if insn.mnem != "call" or rb.follow_jumps(insn.target or -1) != target and insn.target != target:
            continue
        sets_ecx = False
        for back in reversed(insns[max(0, i - 12):i]):
            if back.mnem == "call":
                break
            if "ecx" in back.writes and not (back.mnem == "pop" and back.ops == "ecx"):
                sets_ecx = True
                break
        # Only an `add esp, N` right after the call is a trusted cleanup size;
        # pops and later adds can be split or merged with other calls'.
        nxt = insns[i + 1] if i + 1 < len(insns) else None
        cleanup = (nxt.imm if nxt is not None and nxt.mnem == "add"
                   and nxt.ops.startswith("esp, ") and nxt.imm is not None else None)
        out.append(Site(caller, insn.rva, sets_ecx, cleanup, return_use(insns, i)))
    return out


def return_use(insns, i):
    """'eax' / 'al' / 'st0' / None: how the code after a call uses its result."""
    for nxt in insns[i + 1:i + 9]:
        if X87_CONSUMERS.match(nxt.mnem):
            return "st0"
        if nxt.mnem.startswith("fld") or nxt.mnem.startswith("fild"):
            return None
        mask = nxt.reads.get("eax", 0)
        if mask:
            return "al" if mask == 1 else "eax"
        if "eax" in nxt.writes or nxt.mnem in ("call", "ret", "jmp"):
            return None
    return None


def retail_evidence(rva, size, max_callers=24):
    insns, rets, live, stack_max, compares, setcc = callee_evidence(rva, size)
    sites = []
    for caller in rb.callers(rva)[:max_callers]:
        sites.extend(site_evidence(caller, rva))
    x87, st0_tail = x87_shape(insns)
    return Evidence(rets, live, stack_max, sites, compares, setcc, x87, st0_tail)


# --------------------------------------------------------------- checks

def check(decl, ev, body=None):
    """[(check, message)] where the retail evidence disagrees with decl."""
    out = []
    want = arg_bytes(decl)
    pops = [r for r in ev.rets]
    callee_pops_args = decl.conv in ("stdcall", "thiscall", "fastcall") and not decl.variadic
    if pops:
        allowed = {want, want + 4} if decl.ret.kind == "ctor" and want is not None else {want}
        # (+4: a constructor of a class with virtual bases takes a hidden flag)
        if callee_pops_args and want is not None and any(r not in allowed for r in pops):
            out.append(("args", f"retail `ret {'/'.join(map(str, pops))}` but the declaration "
                                f"passes {want} stack bytes ({decl.conv})"))
        if not callee_pops_args and any(pops):
            out.append(("conv", f"retail `ret {max(pops)}` pops its arguments: stdcall/thiscall, "
                                f"not {decl.conv}{' variadic' if decl.variadic else ''}"))
    if decl.conv == "cdecl" and want is not None and ev.sites:
        cleanups = [s.cleanup for s in ev.sites]
        if all(c is not None and c < want for c in cleanups) and not decl.variadic:
            out.append(("args", f"every call site cleans at most {max(cleanups)} bytes "
                                f"(`add esp` right after the call); the declaration passes {want}"))
    if ev.stack_max is not None and want is not None and not decl.variadic \
            and ev.stack_max > want + (4 if decl.ret.kind == "ctor" else 0):
        out.append(("args", f"retail reads incoming stack slot +{ev.stack_max - 4:#x} "
                            f"({ev.stack_max} bytes) beyond the declared {want}"))
    reads_ecx = "ecx" in ev.live
    if reads_ecx and decl.conv not in ("thiscall", "fastcall"):
        out.append(("this", f"ecx is read before written at 0x{ev.live['ecx']:08X}: "
                            f"thiscall member (or fastcall), not {decl.conv}"
                            f"{' member' if decl.member else ' free/static function'}"
                            f"{'' if decl.member else ' (or a file-static with a private register convention: see wpo_detect.py)'}"))
    if decl.conv == "thiscall" and not reads_ecx and len(ev.sites) >= 2 \
            and not any(s.sets_ecx for s in ev.sites):
        out.append(("this", "declared a member, but retail never reads ecx and no call site loads it"))
    if "edx" in ev.live and reads_ecx and decl.conv != "fastcall":
        out.append(("fastcall", f"ecx and edx both live on entry (edx at 0x{ev.live['edx']:08X}): __fastcall?"))
    uses = Counter(s.ret_use for s in ev.sites)
    used = uses["eax"] + uses["al"]
    kind = decl.ret.kind
    if kind == "void" and used:
        out.append(("return", f"declared void, but {used}/{len(ev.sites)} call sites read "
                              f"{'al' if uses['al'] >= uses['eax'] else 'eax'} after the call"))
    if kind in ("void", "int", "ptr", "bool", "char") and uses["st0"]:
        out.append(("return", f"{uses['st0']} call site(s) consume st0 after the call: "
                              f"returns float/double, not {decl.ret.text}"))
    if kind == "float" and len(ev.sites) >= 2 and not uses["st0"]:
        out.append(("return", f"declared {decl.ret.text}, but no call site touches st0"))
    elif kind == "float" and not ev.x87:
        out.append(("return", f"declared {decl.ret.text}, but the body has no x87 code and calls "
                              f"nothing: it cannot leave a result in st0"))
    if kind in ("int", "ptr", "bool", "char", "void") and ev.st0_tail and not uses["st0"]:
        out.append(("return", f"every ret follows an x87 load/arithmetic leaving st0: returns "
                              f"float/double, not {decl.ret.text}"))
    if kind in ("int", "ptr") and decl.ret.size == 4 and uses["al"] >= 2 and not uses["eax"]:
        out.append(("return", f"declared {decl.ret.text}, but call sites only test al: bool/char?"))
    for index, counts in sorted(ev.compares.items()):
        if index >= len(decl.params):
            continue
        param = decl.params[index]
        if param.kind not in ("int", "char", "ptr") or param.signed is None and param.kind != "ptr":
            continue
        signed = param.signed if param.kind != "ptr" else False
        if signed and counts["unsigned"] and not counts["signed"]:
            out.append(("sign", f"parameter {index + 1} ({param.text}) is compared unsigned "
                                f"(jb/ja) in retail but declared signed (or a folded 0 <= i < n check)"))
        if not signed and counts["signed"] and not counts["unsigned"] and param.size and param.size >= 4:
            out.append(("sign", f"parameter {index + 1} ({param.text}) is compared signed "
                                f"(jl/jg/js) in retail but declared unsigned"))
    if body is not None:
        out.extend(bool_check(body, ev.setcc))
    return out


def bool_check(body, setcc):
    returns = re.findall(r"\breturn\b([^;]*);", body)
    if len(returns) != 1:
        return []
    expr = returns[0].strip()
    top = re.sub(r"\([^()]*\)", "()", expr)
    eq, ne = "==" in top, "!=" in top
    if eq == ne or not (setcc["sete"] or setcc["setne"]):
        return []
    if eq and setcc["setne"] and not setcc["sete"]:
        return [("bool", f"source returns `{expr}` (==) but retail materialises it with setne: inverted?")]
    if ne and setcc["sete"] and not setcc["setne"]:
        return [("bool", f"source returns `{expr}` (!=) but retail materialises it with sete: inverted?")]
    return []


# ------------------------------------------------------------- driver

def qualified_from_row(row):
    try:
        d = wb_gold.demangle(row["name"])
    except (wb_gold.DemangleError, KeyError, TypeError):
        return None
    return wb_gold.qualified(d.scopes, d.name) if d.is_function else None


def build_decl(row, source=None, name=None):
    mangled = (row or {}).get("name")
    qualified = name or (qualified_from_row(row) if row else None)
    source = source or (row or {}).get("source")
    if source and qualified and str(source).endswith((".cpp", ".c", ".h", ".inl")):
        path = Path(source) if Path(source).is_absolute() else rb.ROOT / source
        decl, body = decl_from_source(path, qualified, mangled)
        if decl is not None:
            return decl, body
    return decl_from_mangled(mangled), None


SIGNATURE_RE = re.compile(r"^(?!\s*(?://|#|/\*))[^;(]*?([~\w]+(?:::[~\w]+)*)\s*\(", re.M)


def report_text(rva, text, mangled=None):
    """sig_check report for a draft's own definition (the first in text)."""
    match = SIGNATURE_RE.search(text)
    if not match:
        return f"sig_check 0x{rva:08X}: no definition found in the draft"
    decl, body = decl_from_text(text, match.group(1), mangled, "draft", assume_member=True)
    if decl is None:
        return f"sig_check 0x{rva:08X}: cannot parse the draft's signature {match.group(1)}"
    return render(rva, rb.body_bounds(rva)[1], {"name": mangled} if mangled else None, decl, body)


def describe_decl(decl):
    params = ", ".join(p.text for p in decl.params) + (", ..." if decl.variadic else "")
    return (f"{decl.ret.text} {decl.conv} {decl.name}({params})"
            f"{'  [member]' if decl.member else ''}  <- {decl.origin}")


def report(target, source=None, name=None, as_json=False):
    rva, row = rb.resolve_target(target)
    rva, size = rb.body_bounds(rva, row)
    decl, body = build_decl(row, source, name)
    return render(rva, size, row, decl, body, as_json)


def render(rva, size, row, decl, body, as_json=False):
    ev = retail_evidence(rva, size)
    findings = check(decl, ev, body) if decl else []
    if as_json:
        return json.dumps({"rva": f"0x{rva:08X}", "size": size,
                           "decl": describe_decl(decl) if decl else None,
                           "rets": ev.rets, "live_in": sorted(ev.live),
                           "sites": len(ev.sites),
                           "findings": [{"check": c, "message": m} for c, m in findings]}, indent=2)
    out = [f"sig_check 0x{rva:08X} ({size} bytes) {(row or {}).get('name', '(no ledger row)')}"]
    out.append(f"  decl:   {describe_decl(decl) if decl else '(none: pass --source and --name)'}")
    uses = Counter(s.ret_use or "-" for s in ev.sites)
    out.append(f"  retail: ret {'/'.join(map(str, ev.rets)) or '(none)'}; live on entry: "
               f"{', '.join(sorted(ev.live)) or 'nothing'}; stack slots read: "
               f"{ev.stack_max if ev.stack_max is not None else 0} bytes; "
               f"{len(ev.sites)} call site(s), result use {dict(uses) or '-'}, "
               f"ecx loaded at {sum(s.sets_ecx for s in ev.sites)}")
    odd = sorted(set(ev.live) - {"ecx", "edx"})
    if odd:
        out.append(f"  note:   {', '.join(odd)} live on entry: a private register convention "
                   f"(tools/wpo_detect.py), not expressible as a plain declaration")
    if decl is None:
        return "\n".join(out)
    if not findings:
        out.append("  no mismatches (advice only; a clean report is not a match)")
    for check_name, message in findings:
        out.append(f"  ! {check_name:<8} {message}")
    return "\n".join(out)


def row_is_real(row):
    """True when the row's demangled name is a real identity, not a placeholder."""
    try:
        info = wb_gold.describe(row["name"], row["source"])
    except wb_gold.DemangleError:
        return False
    return bool(info) and info["kind"] == "REAL"


def calibrate(n, seed, out=sys.stdout, use_source=False):
    rows = []
    for row in rb.stream_matched():
        if not row["name"].startswith("?") or row["source"].startswith(("Code/gen_", "Code/masm")):
            continue
        if not row["source"].endswith((".cpp", ".c")):
            continue
        rows.append(row)
    rng = random.Random(seed)
    rng.shuffle(rows)
    checked = 0
    fired = Counter()
    fired_real = Counter()
    real_rows = real_any = 0
    any_fire = 0
    examples = {}
    for row in rows:
        if checked >= n:
            break
        decl, body = (build_decl(row) if use_source else (decl_from_mangled(row["name"]), None))
        if decl is None:
            continue
        rva = int(row["target_rva"], 16)
        try:
            ev = retail_evidence(rva, int(row["target_size"]), max_callers=8)
        except Exception as exc:
            print(f"skip {row['target_rva']}: {exc}", file=sys.stderr)
            continue
        checked += 1
        found = check(decl, ev, body)
        real = row_is_real(row)
        real_rows += real
        if found:
            any_fire += 1
            real_any += real
        for name in {c for c, _ in found}:
            fired[name] += 1
            fired_real[name] += real
            examples.setdefault(name, []).append((row["target_rva"], row["name"][:60],
                                                  [m for c, m in found if c == name][0][:110]))
    origin = "source text (mangled fallback)" if use_source else "mangled names"
    print(f"calibration over {checked} matched rows, declarations from {origin} (seed {seed})", file=out)
    print(f"  rows with any finding: {any_fire} ({any_fire / max(checked, 1):.1%}); "
          f"real-named rows: {real_any}/{real_rows} ({real_any / max(real_rows, 1):.1%})", file=out)
    print("  (a placeholder row's mangled signature is often itself a guess, so its"
          " findings are frequently true)", file=out)
    for name in ("conv", "args", "this", "fastcall", "return", "sign", "bool"):
        print(f"  {name:<9}{fired[name]:>4} ({fired[name] / max(checked, 1):.1%})"
              f"   real-named {fired_real[name]:>3} ({fired_real[name] / max(real_rows, 1):.1%})", file=out)
        for example in examples.get(name, [])[:3]:
            print(f"      {example[0]} {example[1]}: {example[2]}", file=out)
    return fired, checked


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", nargs="?", help="game.dat rva or ledger name")
    parser.add_argument("--source", help="read the declaration from this file's definition")
    parser.add_argument("--name", help="Class::method to find in --source (default: the row's name)")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--calibrate", type=int, metavar="N")
    parser.add_argument("--from-source", action="store_true",
                        help="with --calibrate: parse declarations from source text, not mangled names")
    parser.add_argument("--seed", type=int, default=7)
    args = parser.parse_args(argv)
    if args.calibrate:
        calibrate(args.calibrate, args.seed, use_source=args.from_source)
        return
    if not args.target:
        parser.error("target required")
    print(report(args.target, args.source, args.name, args.json))


if __name__ == "__main__":
    main()
