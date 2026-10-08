#!/usr/bin/env python3
"""Draft C++ for a game.dat function from WorldBuilder's decompiled debug body.

Starts from the Ghidra pseudo-C that tools/wb_decompile.py wrote for the WB
function paired with the target (build/wb/decomp/<wb_va>.c) and turns it into
a draft an RE agent can edit toward a byte match:

  * debug macros go entirely: every statement that touches WB's debug object
    (TheDebugObject, DebugObject_* wrappers), any block whose condition does,
    then whatever that leaves empty (assert guards, `if (ignored) {}`) and
    the locals nothing reads any more. Retail compiles all of it out.
  * this-relative accesses (`this->field_0x1c`, `*(int *)(this + 0x1c)`)
    read as the member reverse/wb_members.csv names at that offset of the
    function's class, else `m_unknown1C /* +0x1c */`
  * each callee reads as its game.dat ledger name when its WB function is
    paired with a real ledger identity; any other call line gets a
    `// TODO` naming the game.dat rva (or that retail has no pairing,
    usually because it was inlined)
  * the signature reads `Ret Class::method(args)`, without the calling
    convention and the explicit `this`
  * a header records provenance: game.dat rva and ledger row, WB va, name,
    source file and assert line range, and the match score and evidence.
  * an advice block follows it: tools/flag_hint.py (compiler-flag tells in
    the retail body, diffed against the row's source `// cl:`) and
    tools/sig_check.py (the draft's signature against retail's ret N, ecx
    use, call-site cleanups and result use). --no-advice omits it.

The output is an UNVERIFIED DRAFT: decompiler types, debug-build inlining
and control flow all differ from retail. It is never written under Code/.

    python3 tools/wb_draft.py <game.dat rva|ledger name|WB name> [--out PATH]

Run `tools/wb_decompile.py run --gd --vas <rva>` first if the WB body has
not been decompiled yet.
"""
import argparse
import collections
import csv
import re
import sys
from pathlib import Path

import wb_decompile
import wb_data
import wb_show

try:  # advisory extras; a missing capstone or game.dat must not stop a draft
    import flag_hint
    import sig_check
except ImportError:  # pragma: no cover
    flag_hint = sig_check = None

ROOT = wb_show.ROOT
DECOMP_DIR = wb_decompile.OUT_DIR
MEMBERS_CSV = ROOT / "reverse" / "wb_members.csv"
FORBIDDEN_OUT = ROOT / "Code"
IMAGE_BASE = wb_show.IMAGE_BASE

DEBUG_RE = re.compile(r"\b(?:%s|DebugObject_\w+|Debug::\w+)\b" % wb_decompile.DEBUG_GLOBAL_NAME)
ASSIGN_RE = re.compile(r"^(\w+) = ")
STORE_RE = re.compile(r"^\s*(\w+) = ([^;]*);$")
CALL_RE = re.compile(r"\w\s*\(")
CALLEE_RE = re.compile(r"^// callee (0x[0-9a-f]+) (.+)$")
DECL_RE = re.compile(r"^\s+[\w\s\*:<>,]+?[\s\*](\w+)(?:\s*\[[^\]]*\])?;(?:\s*/\*.*\*/)?$")
LABEL_RE = re.compile(r"^(\w+):$")
GOTO_RE = re.compile(r"\bgoto (\w+);")
CONVENTIONS_RE = re.compile(r"\b__(?:thiscall|cdecl|stdcall|fastcall)\b\s*")
THIS_PARAM_RE = re.compile(r"\(\s*[\w:<>]+\s*\*\s*this\s*(?:,\s*|(?=\)))")
OFFSET = r"(0x[0-9a-f]+|\d+)"
POINTER_CAST = r"\([\w\s:<>,]+?\s*\*+\)\s*"
THIS_PLUS = r"\((?:\(int\))?this \+ " + OFFSET + r"\)"
MEMBER_PATTERNS = (                                   # (pattern, address-of?)
    (re.compile(r"\*" + POINTER_CAST + THIS_PLUS), False),
    (re.compile(POINTER_CAST + THIS_PLUS), True),
    (re.compile(r"this->field_" + OFFSET), False),
    (re.compile(r"\bthis\[" + OFFSET + r"\]"), False),
    (re.compile(THIS_PLUS), True),
)
CLASS_LITERAL_RE = re.compile(r"\([A-Z]\w*\)(0x[0-9a-f]+|\d+)\b")


# ------------------------------------------------------------ decomp file

class Decomp:
    """A tools/wb_decompile.py output: callees and the pseudo-C lines."""

    def __init__(self, path):
        self.callees = {}
        self.lines = []
        for line in path.read_text().splitlines():
            match = CALLEE_RE.match(line)
            if match:
                self.callees[int(match.group(1), 16)] = match.group(2)
            elif not line.startswith("// wb_va "):
                self.lines.append(line)


def decomp_path(wb_va):
    """The decompiled body of wb_va, or exit with how to produce it."""
    wb_data.ensure_decomp()
    path = DECOMP_DIR / f"{wb_va:#x}.c"
    if path.exists():
        return path
    error = DECOMP_DIR / f"{wb_va:#x}.err"
    if error.exists():
        sys.exit(f"Ghidra could not decompile WB {wb_va:#x}: {error.read_text().strip()}")
    sys.exit(f"WB {wb_va:#x} not decompiled yet: tools/wb_decompile.py run --vas {wb_va:#x}")


# ---------------------------------------------------------- block parsing

class Block:
    """A brace block: header lines (ending in `{`), children, closing line."""

    def __init__(self, head, indent):
        self.head, self.indent, self.children, self.close = head, indent, [], None


def indent_of(line):
    return len(line) - len(line.lstrip(" "))


def parse(lines):
    """Statements (lists of lines) and Blocks, nested by Ghidra's brace layout."""
    root = Block([], -1)
    stack, pending = [root], []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("}") and len(stack) > 1 and indent_of(line) == stack[-1].indent:
            stack[-1].close = line
            stack.pop()
            continue
        pending.append(line)
        if stripped.endswith("{"):
            block = Block(pending, indent_of(pending[0]))
            stack[-1].children.append(block)
            stack.append(block)
            pending = []
        elif not stripped or stripped.endswith((";", ":", "*/")) or stripped.startswith(("//", "/*")):
            stack[-1].children.append(pending)
            pending = []
    if pending:
        root.children.append(pending)
    return root


def flatten(block):
    """Lines of a parsed tree, in order."""
    lines = list(block.head)
    for child in block.children:
        lines.extend(flatten(child) if isinstance(child, Block) else child)
    if block.close is not None:
        lines.append(block.close)
    return lines


# ---------------------------------------------------------- debug macros

class DebugStripper:
    """Removes WB's debug macros from a parsed body.

    A statement or block header is debug when it names the debug object, a
    DebugObject_* wrapper or Debug::*, or reads a variable last assigned
    from such an expression (Ghidra spills `cVar1 = DebugObject_flag();
    if (cVar1 != '\\0') {...}` and the message stream pointer this way).
    Debug blocks go with their bodies; debug statements go, tainting what
    they assign. A later ordinary assignment clears the taint, since Ghidra
    reuses register variables.
    """

    def __init__(self):
        self.tainted = set()

    def is_debug(self, lines, target=None):
        """Does the code (minus the `target =` it stores to) touch debug state?"""
        text = " ".join(line.strip() for line in lines)
        if target:
            text = text[text.index("=") + 1:]
        return bool(DEBUG_RE.search(text)) or any(
            re.search(rf"\b{re.escape(name)}\b", text) for name in self.tainted)

    def strip(self, block):
        kept, in_debug_chain = [], False
        for child in block.children:
            if isinstance(child, Block):
                is_else = head_text(child).startswith("else")
                if self.is_debug(child.head) or (is_else and in_debug_chain):
                    in_debug_chain = True
                    continue
                in_debug_chain = False
                self.strip(child)
                kept.append(child)
                continue
            target = assigned(child)
            if self.is_debug(child, target):
                if target:
                    self.tainted.add(target)
                continue
            self.tainted.discard(target)
            kept.append(child)
        block.children = drop_empty_branches(kept)


def assigned(lines):
    """The variable a `name = ...;` statement assigns, else None."""
    match = ASSIGN_RE.match(" ".join(line.strip() for line in lines))
    return match.group(1) if match else None


def drop_dead_stores(tree):
    """Remove stores to locals nothing reads (inlined assert conditions such as
    `bVar1 = false;` left behind once the assert is gone); repeat to a fixpoint."""
    while remove_stores(tree, dead_locals(flatten(tree))):
        pass


def declarations(lines):
    """{line index: local name} for the declarations opening the function body
    (Ghidra lists them right after the first `{`, ending at a blank line)."""
    start = next((i + 1 for i, line in enumerate(lines) if line.strip() == "{"), len(lines))
    found = {}
    for i in range(start, len(lines)):
        match = DECL_RE.match(lines[i])
        if not match:
            break
        found[i] = match.group(1)
    return found


def dead_locals(lines):
    """Declared locals whose every use is the target of a call-free store."""
    decls = declarations(lines)
    uses, stores = collections.Counter(), collections.Counter()
    for i, line in enumerate(lines):
        if i in decls:
            continue
        for word in re.findall(r"\b\w+\b", line):
            uses[word] += 1
        store = pure_store(line)
        if store:
            stores[store] += 1
    return {name for name in decls.values() if stores[name] and uses[name] == stores[name]}


def pure_store(line):
    """The variable a call-free `name = expr;` line stores to, else None."""
    match = STORE_RE.match(line)
    return match.group(1) if match and not CALL_RE.search(match.group(2)) else None


def remove_stores(block, dead):
    """Drop single-line stores to dead locals under block; returns how many."""
    kept, removed = [], 0
    for child in block.children:
        if isinstance(child, Block):
            removed += remove_stores(child, dead)
        elif len(child) == 1 and pure_store(child[0]) in dead:
            removed += 1
            continue
        kept.append(child)
    block.children = drop_empty_branches(kept)
    return removed


def is_empty(block):
    """No statements left (blank lines aside)."""
    return all(not isinstance(c, Block) and not "".join(c).strip() for c in block.children)


def head_text(block):
    return " ".join(line.strip() for line in block.head)


def is_empty_if(child):
    return isinstance(child, Block) and head_text(child).startswith("if ") and is_empty(child)


def drop_empty_branches(children):
    """Drop emptied if/else shells; `if (c) {} else {...}` becomes `if (!(c)) {...}`."""
    result = []
    for child in children:
        is_else = isinstance(child, Block) and head_text(child).startswith("else")
        if is_else and is_empty(child):
            continue
        if is_else and head_text(child) == "else {" and result and is_empty_if(result[-1]):
            result[-1] = invert_if(result[-1], child)
            continue
        result.append(child)
    return [c for c in result if not is_empty_if(c)]


def invert_if(empty_if, else_block):
    """`if (c) {} else {...}` -> `if (!(c)) {...}`."""
    text = head_text(empty_if)
    condition = text[text.index("(") + 1:text.rindex(")")]
    inverted = Block([f"{' ' * empty_if.indent}if (!({condition})) {{"], empty_if.indent)
    inverted.children, inverted.close = else_block.children, else_block.close
    return inverted


def drop_unused(lines):
    """Remove unused local declarations and labels no goto reaches."""
    text = "\n".join(lines)
    gotos = set(GOTO_RE.findall(text))
    words = collections.Counter(re.findall(r"\b\w+\b", text))
    decls = declarations(lines)
    kept = []
    for i, line in enumerate(lines):
        if i in decls and words[decls[i]] == 1:
            continue
        label = LABEL_RE.match(line.strip())
        if label and label.group(1) not in gotos:
            continue
        kept.append(line)
    return kept


# --------------------------------------------------------------- members

def load_members(cls):
    """{offset: (member, note)} for cls from reverse/wb_members.csv."""
    members = {}
    if not cls:
        return members
    with open(MEMBERS_CSV, newline="") as fh:
        for row in csv.DictReader(fh):
            if row["class"] != cls:
                continue
            note = "from accessor" if row["kind"] == "accessor" else ""
            if row["conflict"] not in ("", "n/a"):
                note = (note + ", " if note else "") + "conflicting candidates"
            members[int(row["offset"], 16)] = (row["member"], note)
    return members


def member_text(members, offset, address):
    name, note = members.get(offset, (f"m_unknown{offset:X}", ""))
    comment = f"+{offset:#x}" + (f", {note}" if note else "")
    return f"{'&' if address else ''}{name} /* {comment} */"


def rename_members(line, members):
    """Rewrite this-relative accesses on one line, and the byte literals Ghidra
    casts to the (opaque) class type: `(Foo)0x0` -> `0x0`."""
    for pattern, address in MEMBER_PATTERNS:
        line = pattern.sub(lambda m: member_text(members, int(m.group(1), 0), address), line)
    return CLASS_LITERAL_RE.sub(r"\1", line)


# ----------------------------------------------------------------- calls

Callee = collections.namedtuple("Callee", "short call this_arg new todo")


class Callees:
    """Ledger names, implicit `this` and TODOs for a decompiled body's callees."""

    def __init__(self, index, callees, own_class):
        namer = wb_show.Namer(index)
        self.callees = [self.describe(namer, wb_va, name, own_class)
                        for wb_va, name in callees.items() if not DEBUG_RE.search(name)]

    @staticmethod
    def describe(namer, wb_va, name, own_class):
        """A Callee: how calls to it appear, and what they become."""
        cls, short = wb_decompile.split_qualified(name)
        qualifier = r"(?:%s::)?" % re.escape(cls) if cls else ""
        call = r"(?<![\w:])%s%s(?=\s*\()" % (qualifier, re.escape(short))
        this_arg = re.compile("(" + call + r")\s*\(this(?:,\s*|(?=\)))") if cls else None
        gd_va = wb_decompile.best_gd(namer.index, wb_va)
        rows = namer.ledger(gd_va) if gd_va else []
        new = todo = None
        if rows and rows[0][2] == "REAL":
            new_cls, new_short = wb_decompile.split_qualified(rows[0][1])
            new = new_short if new_cls == own_class else rows[0][1]
        elif gd_va:
            todo = f"TODO {name}: game.dat 0x{gd_va - IMAGE_BASE:08X} {namer.ledger_label(gd_va)}"
        else:
            todo = f"TODO {name}: WB {wb_va:#x} has no game.dat pairing (inlined in retail?)"
        return Callee(short, re.compile(call), this_arg, new, todo)

    def apply(self, line):
        """The line with `this` arguments dropped, ledger names substituted
        and TODO comments appended."""
        notes = []
        for callee in self.callees:
            if callee.short not in line or not callee.call.search(line):
                continue
            if callee.this_arg:
                line = callee.this_arg.sub(r"\1(", line)
            if callee.todo:
                notes.append(callee.todo)
            if callee.new:
                line = callee.call.sub(callee.new, line)
        return line + "  // " + "; ".join(dict.fromkeys(notes)) if notes else line


# --------------------------------------------------------------- drafting

def signature(lines):
    """Join the signature onto one line, without calling convention or `this`."""
    start = next((i for i, line in enumerate(lines) if line.strip() and not line.startswith(" ")), 0)
    end = next((i for i in range(start, len(lines)) if lines[i] == "{"), start)
    joined = " ".join(line.strip() for line in lines[start:end])
    joined = THIS_PARAM_RE.sub("(", CONVENTIONS_RE.sub("", joined)).replace(" (", "(").rstrip()
    return lines[:start] + [joined, ""] + lines[end:]


def class_of(name):
    return wb_decompile.split_qualified(name or "")[0]


def header(index, gd_va, wb_va):
    """Provenance comment lines."""
    namer = wb_show.Namer(index)
    size, names, files, lines = index["wb"][wb_va]
    match = namer.match(gd_va, wb_va) if gd_va else None
    out = ["// DRAFT -- UNVERIFIED. Generated by tools/wb_draft.py from Ghidra's decompilation",
           "// of WorldBuilder's debug build; debug macros stripped. Not a byte match: types,",
           "// inlining and control flow differ from retail. Verify every line."]
    if gd_va:
        out.append(f"// game.dat rva 0x{gd_va - IMAGE_BASE:08X} size {index['gd'].get(gd_va, 0)}"
                   f"  ledger: {namer.ledger_label(gd_va)}")
    out.append(f"// WB va {wb_va:#x} size {size}  {namer.wb_name(wb_va) or '(unnamed)'}")
    if files:
        span = f" lines {min(lines)}..{max(lines)}" if lines else ""
        out.append(f"// WB source {files[0]}{span}")
    if match:
        out.append(f"// match score {match['score']} evidence {','.join(match['evidence'])}")
    return out


def draft(index, gd_va, wb_va):
    """The draft text for the game.dat function gd_va via its WB pairing wb_va."""
    decomp = Decomp(decomp_path(wb_va))
    tree = parse(decomp.lines)
    DebugStripper().strip(tree)
    drop_dead_stores(tree)
    lines = drop_unused(flatten(tree))
    name = wb_show.Namer(index).wb_name(wb_va) or ""
    own_class = class_of(name)
    members = load_members(own_class)
    callees = Callees(index, decomp.callees, own_class)
    body = [callees.apply(rename_members(line, members)) for line in signature(lines)]
    return "\n".join(header(index, gd_va, wb_va) + [""] + squeeze_blank(body)) + "\n"


def squeeze_blank(lines):
    """Collapse runs of blank lines to one."""
    out = []
    for line in lines:
        if line.strip() or (out and out[-1].strip()):
            out.append(line)
    return out


def advice(gd_va, text, row_name=None):
    """flag_hint and sig_check for the draft, as comment lines. Advice only:
    every failure becomes a one-line note, never a failed draft."""
    rva = gd_va - IMAGE_BASE
    out = ["// ---- advice: tools/flag_hint.py and tools/sig_check.py (never a gate) ----"]
    for label, run in (("flag_hint", lambda: flag_hint.report(f"0x{rva:08X}")),
                       ("sig_check", lambda: sig_check.report_text(rva, text, row_name))):
        if flag_hint is None:
            out.append(f"// {label}: unavailable (import failed)")
            continue
        try:
            out.extend("// " + line for line in run().splitlines())
        except (Exception, SystemExit) as exc:  # noqa: BLE001 - advice must not break drafting
            out.append(f"// {label}: unavailable ({exc})")
    return out


def with_advice(text, gd_va, row_name=None):
    """text with the advice block after its provenance header."""
    lines = text.split("\n")
    cut = next((i for i, line in enumerate(lines) if not line.startswith("//")), len(lines))
    return "\n".join(lines[:cut] + advice(gd_va, text, row_name) + lines[cut:])


def write(text, out):
    """Print text, or write it to out (never under Code/)."""
    if out is None:
        sys.stdout.write(text)
        return
    path = Path(out).resolve()
    if path == FORBIDDEN_OUT or FORBIDDEN_OUT in path.parents:
        sys.exit("refusing to write a draft under Code/")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)
    print(f"wrote {path}", file=sys.stderr)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", help="game.dat rva/va, ledger name, WB name or wb:0xVA")
    parser.add_argument("--out", help="write here (e.g. build/wb/drafts/<rva>.cpp) instead of stdout")
    parser.add_argument("--no-advice", action="store_true",
                        help="omit the flag_hint / sig_check comment block")
    args = parser.parse_args(argv)
    index = wb_show.load_index()
    gd_va, wb_va, note = wb_show.resolve_target(index, args.target)
    if wb_va is None:
        sys.exit(f"{args.target}: no WorldBuilder pairing")
    if note:
        print(f"note: {note}", file=sys.stderr)
    text = draft(index, gd_va, wb_va)
    if not args.no_advice and gd_va:
        rows = index["ledger"].get(gd_va - IMAGE_BASE) or []
        text = with_advice(text, gd_va, rows[0][0] if rows else None)
    write(text, args.out)


if __name__ == "__main__":
    main()
