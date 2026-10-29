#!/usr/bin/env python3
"""Turn an approved TU from tu_map.csv into the one source file retail built it from.

The skeleton of a TU is every function tu_map.csv approves for it, in retail
address order. Matched bodies are pulled in from the one-function files that
hold them today; everything else is an explicit placeholder comment:

    // tu-skeleton: 0x004A1230 88B ?foo@Bar@@QAEXXZ -- unmatched, no code, never credited
    // tu-skeleton: 0x004A1290 40B ?baz@Bar@@QAEXXZ -- matched in Die/Baz.cpp (not merged yet)

A placeholder is a comment, so it compiles to nothing and no gate or progress
figure can count it. Retail-byte stubs (`__emit`) are deliberately not emitted:
conversion_gate refuses them outside Code/gen_small/ and they would be the one
kind of placeholder a progress figure could mistake for a match.

Merging is verified, never assumed. Each donor file is compiled alone first and
the rows that match there are the baseline. Donors are then accreted in three
deterministic orders (address, row count, text size); a donor is accepted only
if the TU still compiles and NO baseline row is lost, and the best order wins.
Accretion tries growing chunks of donors in one compile and bisects a chunk
that fails; an order or flag set stops once it cannot beat the best so far, and
a donor rejected for a compile error that also fails beside the seed alone is
not retried in later orders (greedy(), screen()); a spelling strategy whose
composed text equals one already tried is skipped (distinct_strategies()). The accepted
set is composed and verified again before it is written.
Duplicate declarations are emitted once; a type that two donors spell
differently gets one spelling (first, else longest) and the byte check decides
whether that was safe. A donor that also holds rows of another TU is never
split here ("mixed"): it stays a satellite and is reported.

Matched rows are not enough: a merge must not cost any unit its link
(LinkGuard). When the target or a donor links at the last census, every
candidate that keeps its rows is also judged as one object by
tools/link_check.py's census rules (the absorbed units leave the index and the
merged object takes their link-order place), and a donor that would make it
stop linking is rejected like one that loses bytes ("link: ..."). Without the
census index (python3 tools/link_check.py --fetch-index) such a merge is
blocked. Splits judge the residual and destination together against the same
census, preserving existing debt while refusing new failures in either file or
outside consumers.

Applying a merge writes the TU file (`// cl:` line chosen from the donors' own
flag sets by the same verification), repoints every ledger row of each absorbed
donor at it, deletes the absorbed donors and stages the result. The commit hook
then byte-verifies it again; this tool never commits.

The map is the one tu_map.py builds from the current inputs: when the committed
tu_map.csv is stale (tu_map.py --check-fresh) it is rebuilt in memory, never
written, so a merge never carries a regenerated map and two merges never
conflict over it.

A donor is refused, not absorbed, when deleting it is not mechanical: it is
untracked, vendored, #included by another file, or expands __FILE__ (its path
reaches its bytes). These are tools/rename_files.py's refusals, read from the
same tree.

A donor keyed in a protected path-keyed register (rename.PROTECTED_PATH_KEYED)
is absorbed, and its keys travel with its code in the merge commit (carry()):
code_identity_baseline.tsv and data_check_baseline.txt lines are re-keyed to the
TU (a transfer, which repair_queue verify-removed, code_identity_gate, data_check
and protected_paths accept), data_ledger.csv `source` and `name@source` cells
follow, flag_overrides.csv entries become one TU entry with summed counts (the
merge is then verified under those flags, and no donor may lose a row it matches
under its own build), and hatch_baseline.tsv is rewritten by `hatch_counters.py
--update` (a total-keeping move). A merge that would leave any of them keyed to
a deleted donor is refused. The commit needs the `Verifier-Change:` trailer the
merge prints. A key the merged TU no longer produces leaves only by its owner's
fresh verdict, in a later commit (the printed follow-up).

Applying a merge claims `file:` for the TU and every donor plus each moved
row's RVA first (BFME_CLAIM_OWNER; nothing is written when another worker
holds one), and repoints every path-keyed column tools/rename.py repoints
(functions.csv, data_rows.csv, tu_map.csv and body_owners.csv `source`, the
docs/doxygen/sources.cfg INPUT lines).

The queue (--queue) is the consolidation lane's picker: approved TUs ranked by
how many files a merge would remove, skipping TUs another worker holds.

Usage:
  python3 tools/tu_skeleton.py --queue [--under PREFIX] [--limit N] [--json FILE]
  python3 tools/tu_skeleton.py --list PREFIX       approved TUs under PREFIX
  python3 tools/tu_skeleton.py --plan TU           the skeleton, row by row
  python3 tools/tu_skeleton.py --merge TU [--dry-run] [--no-claim]
  python3 tools/tu_skeleton.py --merge-all [--dry-run [--static]] [--jobs N] [--budget-min M] [--under P]
      every queued TU, each verified merge its own commit, the rest a ranked
      decision queue (tools/merge_all.py); --release after pushing
  python3 tools/tu_skeleton.py --split FILE                  which TUs a mixed file's rows belong to
  python3 tools/tu_skeleton.py --split FILE --for TU [--dry-run] [--no-claim]
      carve the rows approved for TU out of a mixed FILE into the TU path (the
      split lane, documented in docs/consolidation.md): the residual keeps every
      other row
"""
import argparse
import collections
import contextlib
import csv
import hashlib
import io
import json
import os
import posixpath
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402
import claims  # noqa: E402
import rename  # noqa: E402
import rename_files  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
LAYOUT = tu_map.Layout(ROOT)
LEDGER = LAYOUT.path("functions.csv")
MARK = "// tu-skeleton:"
# an EH funclet row (`__ehhandler$X`, ...) is emitted with its parent X and lives in X's file
FUNCLET = re.compile(r"^__(?:ehhandler|unwindfunclet|catch|catchsym|tryblocktable|unwindtable)\$(.+)$")
PARENT_NOTE = re.compile(r"parent=([^;\s]+)")          # gen-funclet;parent=X (`$L5782`, `Unwind@00b636b8`)
DELETING = re.compile(r"^\?\?_[GE]((?:\?\$)?[A-Za-z_]\w*@)")   # ??_G / ??_E: the deleting destructors of ??1


def parent_of(row, dtors=None):
    """The symbol a companion row is emitted with (EH funclet by name, generated
    funclet by its `parent=` note, deleting destructor by its class's ??1), or
    None for an ordinary row. `dtors` maps a class prefix to the ??1 name seen."""
    m = FUNCLET.match(row["name"])
    if m:
        return m.group(1)
    m = PARENT_NOTE.search(row.get("notes") or "")
    if m:
        return m.group(1)
    m = DELETING.match(row["name"])
    if m and dtors and m.group(1) in dtors:
        return dtors[m.group(1)]
    return None


# ---------------------------------------------------------------- chunking
def initialised(head):
    """True when `head` (the text before a `{`) is an object's declarator with an
    initialiser: an `=` at parenthesis depth 0 that is not part of `operator=`,
    `==`, `!=`, `<=`, `>=`, and not a default argument inside `(...)`."""
    h = re.sub(r"__declspec\s*\([^)]*\)", " ", head)
    h = re.sub(r"\boperator\s*[^\s(]+", " operator_ ", h)
    depth = 0
    for i, ch in enumerate(h):
        if ch in "([<":
            depth += 1
        elif ch in ")]>":
            depth -= 1
        elif ch == "=" and depth <= 0 and h[i - 1:i] not in "=!<>" and h[i + 1:i + 2] != "=":
            return True
    return False


# a type definition's head: `{...}` ends at its `;`, not at the `}`; storage and
# cv specifiers may lead it (`static enum E { ... };`, `static class C { ... } c;`)
AGGREGATE = re.compile(r"^(?:template\s*<[^>]*>\s*)?(?:typedef\s+)?(?:(?:static|const|volatile)\s+)*"
                       r"(?:class|struct|enum|union)\b")


def chunks(text):
    """Top-level items as (kind, text); comments stay with the item after them.

    kind is 'pp' (a preprocessor line), 'def' (a function body), 'decl'
    (anything ending in ';', class bodies included) or 'tail' (trailing
    comments). Braces inside comments, strings and character literals are
    skipped, which is what the earlier comment-stripping chunker could not do.
    """
    out, n, i, start, depth, code = [], len(text), 0, 0, 0, False
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
            continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i, code = j + 1, True
            continue
        if c == "#" and depth == 0 and not code and text[text.rfind("\n", 0, i) + 1:i].strip() == "":
            j = i
            while True:
                k = text.find("\n", j)
                if k < 0:
                    k = n
                    break
                if text[k - 1:k] != "\\" and not text[j:k].rstrip("\r").endswith("\\"):
                    # a block comment opened on the directive's line ends with the directive
                    o = COMMENT.sub(lambda m: m.group(0) if m.group(0)[0] in "\"'" else " " * len(m.group(0)),
                                    text[i:k]).find("/*")
                    if o < 0 or text.find("*/", i + o + 2) < 0:
                        break
                    j = text.find("*/", i + o + 2) + 2
                    continue
                j = k + 1
            lead = text[start:text.rfind("\n", 0, i) + 1]
            if lead.strip():
                out.append(("tail", lead))
            directive = text[i:k].rstrip()
            if directive.endswith("\\"):
                # a continuation onto the blank line that ends it (part_ldr's SAFE_DELETE_ARRAY):
                # the blank line is dropped here, so the `\` would continue onto the next item
                directive = directive[:-1].rstrip()
            out.append(("pp", directive))
            i = start = min(k + 1, n)
            continue
        if c == "\n" and depth == 0 and code:
            line = strip(text[start:i]).strip()
            if MACRO_LINE.match(line) and "{" not in line and not line.startswith("#"):
                out.append(("decl", text[start:i + 1]))     # NAME(args) generating a body: no `;`, no `{`
                start, code = i + 1, False
                i += 1
                continue
        if not c.isspace():
            code = True
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                body = strip(text[start:i + 1]).strip()
                head = body.split("{")[0]
                aggregate = AGGREGATE.match(body) \
                    and not re.search(r"\)\s*(const)?\s*$", head.strip())
                # a brace-initialised object (`const char *Names[] = {...};`) ends at its `;`,
                # like an aggregate: splitting it at the `}` left a lone `;` as the next item
                data = initialised(head)
                if not aggregate and not data:
                    out.append(("def" if not re.match(r"^(namespace|extern\s+\"C\")", body) else "decl",
                                text[start:i + 1]))
                    start, code = i + 1, False
        elif c == ";" and depth == 0:
            out.append(("decl", text[start:i + 1]))
            start, code = i + 1, False
        i += 1
    if text[start:].strip():
        out.append(("tail" if not strip(text[start:]).strip() else "decl", text[start:]))
    return out


# one left-to-right pass, as the compiler reads it: a `//****` banner before a `/* ... */` block
# is a line comment, and comment openers inside string and character literals are text
COMMENT = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|//[^\n]*|/\*.*?\*/', re.S)


def strip(t):
    return COMMENT.sub(lambda m: m.group(0) if m.group(0)[0] in "\"'" else " ", t)


def norm(t):
    return re.sub(r"\s+", " ", strip(t)).strip()


def key_of(kind, text):
    s = norm(text)
    m = re.match(r"^(?:template\s*<[^>]*>\s*)?(class|struct|enum|union)\s+(?:__declspec\([^)]*\)\s*)?"
                 r"([A-Za-z_]\w*)\s*(?::[^{]*)?\{", s)
    if m:
        return ("type", m.group(2))
    m = re.match(r"^typedef\b.*?\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;$", s)
    if m:
        return ("typedef", m.group(1))
    if kind == "def":
        return ("func", s.split("{")[0].strip())
    return ("decl", s)


ACCESS = re.compile(r"^\s*(public|protected|private)\s*:(?!:)")


def members(text):
    """(head, [(access, member text)], tail) of one class body; comments stripped."""
    text = strip(text)
    i, j = text.index("{"), text.rindex("}")
    head, body, tail = text[:i + 1], text[i + 1:j], text[j:]
    acc = "public" if re.match(r"^\s*(template\s*<[^>]*>\s*)?(struct|union)\b", head) else "private"
    out, buf, depth, par = [], "", 0, 0
    for ch in body:
        buf += ch
        m = ACCESS.match(buf)
        if m and depth == 0 and par == 0:
            acc, buf = m.group(1), buf[m.end():]
            continue
        if ch == "(":
            par += 1
        elif ch == ")":
            par -= 1
        elif ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and par == 0 and "(" in buf.split("{")[0] \
                    and not re.match(r"^\s*(enum|struct|class|union)\b", buf):
                out.append((acc, buf.strip()))
                buf = ""
        elif ch == ";" and depth == 0 and par == 0:
            out.append((acc, buf.strip()))
            buf = ""
    return head, [(a, m) for a, m in out if m and m != ";"], tail


def member_key(m):
    """(key, 'safe'|'layout'): safe members cannot change size, offsets or vtable."""
    s = re.sub(r"\s+", " ", re.sub(r"\{.*\}$", "", m, flags=re.S)).strip().rstrip(";")
    if re.match(r"^(enum|struct|class|union|typedef)\b", s):
        names = re.findall(r"[A-Za-z_]\w*", s)
        return ("type", names[-1] if s.startswith("typedef") else names[1] if len(names) > 1 else s), "safe"
    s = re.sub(r"__declspec\s*\([^()]*\)\s*", "", s)
    f = re.search(r"(~?[A-Za-z_]\w*|operator\s*\S+)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(const)?", s)
    if f and not re.search(r"\(\s*\*", s[:f.start() + 3]):
        return ("fn", f.group(1), bool(f.group(3))), ("layout" if re.search(r"\bvirtual\b", s) else "safe")
    names = re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*$", s)
    return ("data", names[0] if names else s), ("safe" if s.startswith("static ") else "layout")


def union_view(base, others):
    """`base` plus the layout-safe members only the others declare (access kept:
    MSVC mangles it). Virtual functions and data members are never added."""
    try:
        head, mem, tail = members(base)
    except ValueError:
        return base
    have = {member_key(m)[0] for _, m in mem}
    add = []
    for v in others:
        try:
            _, vm, _ = members(v)
        except ValueError:
            continue
        for a, m in vm:
            k, kind = member_key(m)
            if kind == "safe" and k not in have:
                have.add(k)
                add.append((a, m))
    if not add:
        return base
    extra = "".join(f"\n{a}:\n\t{m}{'' if m.endswith(('}', ';')) else ';'}" for a, m in add)
    return head + "".join(f"\n{a}:\n\t{m};" if not m.endswith(("}", ";")) else f"\n{a}:\n\t{m}"
                          for a, m in mem) + extra + "\n" + tail


# ---------------------------------------------------------------- inputs
_CACHE = {}


def ledger_rows():
    if "ledger" not in _CACHE:
        _CACHE["ledger"] = list(csv.DictReader(io.StringIO(
            LEDGER.read_text(encoding="utf-8", errors="replace"), newline="")))
    return _CACHE["ledger"]


def map_rows():
    """tu_map rows from the current inputs: the committed map when it is fresh,
    else a rebuild in memory (tu_map.build is a pure function of the inputs)."""
    if "map" not in _CACHE:             # a rebuild comes from the shared picker cache by its inputs
        _CACHE["map"], _CACHE["stale"] = tu_map.current_rows(LAYOUT)
    return _CACHE["map"]


def tree():
    """rename_files' refusal reader (tracked files, protected keys, includes)."""
    if "tree" not in _CACHE:
        _CACHE["tree"] = rename_files.Tree(rename.Context(ROOT, object_scan=False))
    return _CACHE["tree"]


# rename_files.Tree reasons that do not apply to absorbing a donor: its name is
# not kept either way, and its rows keep theirs.
NOT_REFUSALS = ("an approved retail TU path", "recorded canonical",
                "keyed in a protected path-keyed register")   # carry() moves the keys with the code


def refusal(f, rows):
    """The first reason absorbing `f` is not mechanical. A NOT_REFUSALS reason is only
    excused, never taken as acceptance: every other condition is still checked."""
    return next((why for why in tree().refusals(f, rows) if not why.startswith(NOT_REFUSALS)), None)


def skeleton(tu):
    """Approved rows of `tu` in retail order, each with its ledger row (or None)."""
    if "approved_by_tu" not in _CACHE:      # indexed once: the queue asks for every TU
        by_tu = collections.defaultdict(list)
        for r in map_rows():
            if r["confidence"] == "approved" and r["kind"].startswith("code"):
                by_tu[r["tu"].lower()].append(r)
        _CACHE["approved_by_tu"] = by_tu
    if "led_by_rva" not in _CACHE:
        led = {}
        for r in ledger_rows():
            if "gen-alias" not in (r["notes"] or "") and r["target_rva"].startswith("0x"):
                led.setdefault(int(r["target_rva"], 16), r)
        _CACHE["led_by_rva"] = led
    want, led = _CACHE["approved_by_tu"].get(tu.lower(), []), _CACHE["led_by_rva"]
    return [(r, led.get(int(r["rva"], 16))) for r in sorted(want, key=lambda r: int(r["rva"], 16))]


def donors(tu, sk):
    """(donor file -> its rows, mixed file -> foreign row count, refused file -> why).

    A candidate is the file of an approved row, or the TU path itself. It may be
    absorbed only when every matched row it owns is assigned to this TU (any
    confidence); anything else would move a row the map does not put here. A
    donor other than the TU path is refused when deleting it is not mechanical
    (see refusal()).
    """
    rows = ledger_rows()
    if "assigned" not in _CACHE:
        _CACHE["assigned"] = {int(r["rva"], 16): r["tu"].lower() for r in map_rows()
                              if r["kind"].startswith("code") and r["tu"]}
    assigned = _CACHE["assigned"]
    if "by_file" not in _CACHE:
        _CACHE["by_file"] = collections.defaultdict(list)
        for r in rows:
            _CACHE["by_file"][r["source"]].append(r)
    by_file = _CACHE["by_file"]
    # Unconverted rows are approved too now; a generated or dump file (gen_uw.py owns
    # gen_small end to end) is a placeholder for the address, never a donor to absorb.
    cands = {led["source"] for t, led in sk
             if led and led["status"] == "matched" and led["source"].endswith(".cpp")
             and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", led["source"])}
    if by_file.get(tu):
        cands.add(tu)
    out, mixed, refused = {}, {}, {}
    for f in sorted(cands):
        own = [r for r in by_file[f] if r["status"] == "matched" and "gen-alias" not in (r["notes"] or "")]
        home = {r["name"]: assigned.get(int(r["target_rva"], 16)) for r in own}
        dtors = {m.group(1): r["name"] for r in own if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
        # a companion row (funclet, deleting dtor) is emitted with its parent and lives where it lives
        where = {id(r): home[p] if (p := parent_of(r, dtors)) and p in home
                 else assigned.get(int(r["target_rva"], 16)) for r in own}
        # The TU file itself may keep rows the map has not placed anywhere: the merge
        # seeds from it, moves none of them, and verifies they still match. A row the
        # map puts in another TU still makes it mixed (split it first).
        foreign = [r for r in own if where[id(r)] != tu.lower()
                   and not (f == tu and where[id(r)] is None)]
        if foreign:
            mixed[f] = len(foreign)
        elif own:
            why = refusal(f, by_file[f]) if f != tu else None
            if why:
                refused[f] = why
            else:
                out[f] = own
    return out, mixed, refused


def flags_of(text):
    for line in text.splitlines():
        if line.startswith("// cl:"):
            return line[len("// cl:"):].split()
    return []


def stl_static(flags):
    """`flags` with /D_STLP_USE_STATIC_LIB when they pair /MD with a bfmealloc shim
    and lack it. Without it the shim's _alloc.h exports allocator<char>, its own
    explicit specialization (C2950), so every STL-including donor fails; the /MD
    users of the shim that compile all carry it."""
    if not any(x.upper() in ("/MD", "-MD", "/MDD", "-MDD") for x in flags) \
            or any(re.match(r"[-/]D_STLP_USE_STATIC_LIB(=|$)", x) for x in flags) \
            or not any(x.lower().startswith(("/i", "-i"))
                       and posixpath.basename(x[2:].replace("\\", "/").rstrip("/")).startswith("bfmealloc")
                       for x in flags):
        return flags
    i = next((n for n, x in enumerate(flags) if x.lower().startswith(("/i", "-i"))), len(flags))
    return flags[:i] + ["/D_STLP_USE_STATIC_LIB"] + flags[i:]


# ---------------------------------------------------------------- compose
# Redefinitions cl reports when two donors (or a donor and a header another
# donor includes) both declare one type: the later, donor-local copy is dropped
# and the byte check decides whether the surviving spelling was safe.
REDEFINED = re.compile(r"error C2011: '([A-Za-z_]\w*)' : '(?:struct|class|enum|union)' type redefinition"
                       r"|error C2371: '([A-Za-z_]\w*)' : redefinition; different basic types"
                       r"|error C2365: '([A-Za-z_]\w*)' : redefinition; previous definition was")


def redefined(errors):
    return {next(g for g in m.groups() if g) for e in errors for m in [REDEFINED.search(e)] if m}


STRATEGIES = ("union-first", "union-longest", "first", "longest")


def distinct_strategies(first_text, strategies=STRATEGIES):
    """[(strategy, its first composed text)], one strategy per distinct text.
    Composing and compiling are deterministic, so a strategy whose text equals one
    already tried ends exactly as that one did; attempt() skips only those. (A skip
    judged by which names the compile errors quote lost merges: a respelled typedef
    can cure an error that names only the overloaded function it reaches, review
    2026-10-28.)"""
    seen, out = set(), []
    for st in strategies:
        text = first_text(st)
        if text not in seen:
            seen.add(text)
            out.append((st, text))
    return out


def composition_chunks(text):
    """Keep conditional regions opaque and optimization directives with bodies.

    Hoisting/deduplicating individual #if/#endif lines changes their branches
    and can leave an otherwise valid donor unterminated. A whole region can be
    retained as one declaration (or preprocessor item when it contains only
    directives/comments). Its contents are not candidates for view unioning.
    Optimization pragmas must run in the donor's function order, including
    repeated resets, rather than joining the hoisted include directives.
    """
    out, region, nesting = [], [], 0
    for kind, text in chunks(text):
        directive = re.match(r"#\s*(if|ifdef|ifndef|endif)\b", text) if kind == "pp" else None
        word = directive.group(1) if directive else None
        if word in ("if", "ifdef", "ifndef"):
            nesting += 1
        if nesting:
            region.append((kind, text))
            if word == "endif":
                nesting -= 1
                if not nesting:
                    opaque_kind = "pp" if all(k in ("pp", "tail") for k, _ in region) else "decl"
                    out.append((opaque_kind, "\n".join(c for _, c in region)))
                    region = []
            continue
        if kind == "pp" and re.match(r"#\s*pragma\s+optimize\s*\(", text):
            kind = "body-pp"
        out.append((kind, text))
    if region:  # Preserve malformed input too: the compiler must still refuse it.
        out.append(("decl", "\n".join(c for _, c in region)))
    return out


def compose(tu, sk, files, texts, flags, strategy, drop=frozenset(), drop_all=frozenset()):
    """Declarations first (donor order, one spelling each), then bodies in retail order.

    `files` is in donor order with the seed first. A type two donors spell
    differently is emitted once, from the donor whose spelling is chosen and at
    that donor's own position, so whatever it depends on is already declared.
    """
    parsed = {f: composition_chunks("\n".join(l for l in texts[f].lstrip("\ufeff").splitlines()
                                  if not l.startswith("// cl:") and l.strip() != "// stlport"
                                  and not l.startswith(MARK) and not l.startswith("// TU ")) + "\n")
              for f in files}   # a seed's own placeholders and header are regenerated below
    variants = collections.defaultdict(list)
    for f in files:
        for kind, c in parsed[f]:
            if kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and norm(c) not in [norm(v) for v, _ in variants[k]]:
                    variants[k].append((c, f))
    chosen = {}
    for k, v in variants.items():
        if len(v) > 1:
            pick = v[0] if strategy.endswith("first") else max(v, key=lambda x: len(norm(x[0])))
            if strategy.startswith("union") and k[0] == "type":
                # emitted where the LAST donor declares it: members added from
                # other donors may name types those donors declare first
                pick = (union_view(pick[0], [x[0] for x in v if x is not pick]), v[-1][1])
            chosen[k] = pick
    pps, decls, seen, placed, bodies = [], [], set(), set(), set()
    for f in files:
        # a declaration before the file's last #include (a type an included header
        # needs, e.g. CrateSystem.cpp's KindOfMaskType) stays among the includes;
        # so do an optimize pragma and a body there (mapper.cpp's pragmas around
        # refcount.h and vector2.h scope those headers' inlines, its anchor body
        # sits between them): moved below every include they changed bytes
        last_inc = max((i for i, (kind, c) in enumerate(parsed[f])
                        if kind == "pp" and re.match(r"#\s*include\b", c.strip())), default=-1)
        for at, (kind, c) in enumerate(parsed[f]):
            into = pps if at < last_inc else decls
            if at < last_inc and kind in ("def", "body-pp"):
                placed.add((f, at))
                if kind == "body-pp":
                    pps.append(c.strip())
                elif norm(c) not in bodies:
                    bodies.add(norm(c))
                    pps.append(c.strip("\n"))
                continue
            if kind == "pp":
                line = c.strip()
                # only an #include repeats harmlessly; a conditional or a #define
                # dropped from one donor orphans its #endif or changes a value
                if line not in pps or not re.match(r"#\s*(include|pragma\s+once)\b", line):
                    pps.append(line)
            elif kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and (k[1] in drop_all or (k[1] in drop and f != files[0])):
                    continue   # cl saw it defined earlier: the seed's copy, else a header (includes come first)
                if k[0] in ("type", "typedef") and k[1] in drop and k not in seen:
                    seen.add(k)    # the seed's own spelling, whichever spelling the strategy chose
                    into.append(c.strip("\n"))
                    continue
                if k in seen or (k in chosen and chosen[k][1] != f):
                    continue
                seen.add(k)
                into.append((chosen[k][0] if k in chosen else c).strip("\n"))
    body, done = [], set()
    for t, led in sk:
        f = led["source"] if led else None
        if f in files:
            if f in done:
                continue
            done.add(f)
            body.append(f"// ---- from {f}")
            for at, (kind, c) in enumerate(parsed[f]):
                if (f, at) in placed:
                    continue
                if kind == "def" and norm(c) not in bodies:
                    bodies.add(norm(c))
                    body.append(c.strip("\n"))
                elif kind in ("tail", "body-pp"):
                    body.append(c.strip("\n"))
            continue
        name = (led or {}).get("name") or "(unledgered)"
        why = (f"matched in {f} (not merged yet)" if led and led["status"] == "matched"
               else "unmatched, no code, never credited")
        body.append(f"{MARK} {t['rva']} {t['size']}B {name} -- {why}")
    for f in files:   # a donor none of whose rows is approved here (cannot happen today)
        if f not in done:
            body.extend(c.strip("\n") for at, (kind, c) in enumerate(parsed[f])
                        if kind in ("def", "body-pp") and (f, at) not in placed)
    head = [f"// cl: {' '.join(flags)}"] if flags else []
    if any("// stlport" in texts[f] for f in files):
        head.append("// stlport")
    head.append(f"// TU {tu}: generated by tools/tu_skeleton.py from tu_map.csv (approved rows, retail order)")
    return "\n".join(head + pps) + "\n\n" + "\n\n".join(decls + body) + "\n"


# ---------------------------------------------------------------- verify
class Verifier:
    """Compiles candidate TU texts beside the TU and judges rows as build.sh does.

    The candidate is a temporary file, which tools/flag_defaults.py knows no
    region for, so it would compile with its raw `// cl:` codegen flags while the
    real file gets its region's. The verifier therefore writes the flags the
    build will use: the region holding most bytes of the rows being judged
    (flag_defaults' own rule for a TU), or the TU's own flags when the TU path
    is in flag_overrides.csv, and compiles with region defaults off. A merge that
    carries a flag override (carry()) passes its managed flags as FLAGS: every
    candidate then compiles under them, and the written TU spells them. REGION
    judges under the region default even when the TU path is overridden (a
    donor's own build, which the override must not lose rows against)."""

    def __init__(self, tu, flags=None, region=False):
        import build as B
        self.flags = flags
        self.region = region
        self.B = B
        self.fd = B.flag_defaults
        self.tu_rel = tu
        self.sm = B.load_symbol_map()
        self.tu = ROOT / tu
        self.tmp = ROOT / "build" / "tu_skeleton"   # build.py wants objects inside the tree
        self.tmp.mkdir(parents=True, exist_ok=True)
        self.cache = {}
        self.errors = []
        self.all_errors = []

    def effective(self, text, rows):
        """`text` with the `// cl:` line the build would use for these rows."""
        fd = self.fd
        if getattr(self, "flags", None) is not None:
            return self.with_tokens(text, self.flags.split())
        if self.tu_rel in fd.overrides() and not getattr(self, "region", False):
            return text
        weights = {}
        for r in rows:
            try:
                region = fd.region_at(int(r["target_rva"], 16))
                size = int(r["target_size"])
            except (ValueError, KeyError):
                continue
            if region is None or region.get("vote") != "1":
                continue
            entry = weights.setdefault(fd._flag_set(region), [0, region])
            entry[0] += size
        if not weights:
            return text
        region = max(sorted(weights.items()), key=lambda item: item[1][0])[1][1]
        return self.with_tokens(text, fd.region_tokens(region))

    def with_tokens(self, text, tokens):
        """`text` whose `// cl:` codegen tokens are `tokens`; every other token is kept."""
        fd = self.fd
        lines = text.split("\n")
        at = next((i for i, l in enumerate(lines) if l.startswith("// cl:")), None)
        own = lines[at][len("// cl:"):].split() if at is not None else []
        keep = [t for t in own if not fd.MANAGED.match(t.replace("/", "-", 1) if t.startswith("/") else t)]
        line = "// cl: " + " ".join(["/" + t[1:] for t in tokens] + keep)
        if at is None:
            lines.insert(0, line)
        else:
            lines[at] = line
        return "\n".join(lines)

    def matched(self, text, rows):
        text = self.effective(text, rows)
        key = hashlib.sha1(text.encode()).hexdigest()[:16]
        if key not in self.cache:
            # keep the TU's suffix: cl compiles a .c TU as C, and as C++ every row misses
            src = self.tu.parent / f".{self.tu.stem}.{key}.tu_skeleton{self.tu.suffix}"
            obj = self.tmp / f"{key}.obj"
            # a TU no checkout file lives in yet: make its directory for the
            # scratch file and take back only what was made
            made = [d for d in reversed(src.parents) if not d.exists()]
            src.parent.mkdir(parents=True, exist_ok=True)
            src.write_text(text, encoding="utf-8", newline="")
            try:
                with contextlib.redirect_stdout(io.StringIO()), self.fd.forced_mode("current"):
                    ok, msg, _ = self.B.try_compile_source(src, obj)
            finally:
                src.unlink()
                for d in reversed(made):
                    if not any(d.iterdir()):
                        d.rmdir()
            errors = [] if ok else [l.strip() for l in (msg or "").splitlines() if " error " in l]
            # attempt() uses redefinition diagnostics to choose its next text.
            # A cached failure must restore its own errors, not the last trial's.
            self.cache[key] = (obj if ok else None, errors)
        obj, errors = self.cache[key]
        self.obj = obj          # the candidate's object, for LinkGuard.judge
        self.all_errors = list(errors)
        self.errors = self.all_errors[:3]
        out = set()
        if obj is None:
            return None
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            for r in rows:
                try:
                    res = self.B.compile_function(r, self.sm, obj)
                    if res["bytes"] == res["target"]:
                        out.add(r["target_rva"])
                except BaseException:   # build.py reports misses by SystemExit
                    pass
        return out


# ---------------------------------------------------------------- link guard
# link_check's index tables and where each entry keeps its object's position
LINK_TABLES = (("strong", lambda entry: entry), ("comdat", lambda entry: entry[0]),
               ("common", lambda entry: entry[0]), ("alternates", lambda entry: entry[0]))


def portable_comdat_contexts(data):
    """Exact copies whose relocations need no private or weak object context.

    The census digest normalizes local labels and does not encode weak defaults.
    It is not enough for moving existing debt. Compare raw bodies and ordinary
    undefined external references, from both authenticated old and new objects.
    Other kinds keep the existing refusal; this is deliberately a narrow proof.
    """
    import struct
    import link_census as LCe
    try:
        selections = LCe._comdat_selections(data)
        aliases = {m.group(1).decode("latin-1").strip('"')
                   for m in re.finditer(rb"/alternatename:([^=\s]+)=(\S+)", data, re.I)}
        weaks = {name for name, _ in LCe._weak_externals(data)}
        defined = {s["name"] for s in LCe._coff_symbols(data)
                   if s["storage"] == LCe.EXTERNAL and (s["section"] > 0 or s["value"] != 0)}
        result = {}
        for symbol, body, relocs, digest, _ in LCe._comdat_sections(data):
            if body is None or selections.get(symbol["section"]) != 2:  # IMAGE_COMDAT_SELECT_ANY
                continue
            if any(ref["storage"] != LCe.EXTERNAL or ref["section"] != 0 or ref["value"] != 0
                   or "definition" in ref or ref["name"] in aliases | weaks | defined
                   or LCe._normal(ref["name"]) != ref["name"] for _, _, ref in relocs):
                continue
            result[(symbol["name"], digest)] = (symbol["value"], body,
                tuple((offset, kind, ref["name"]) for offset, kind, ref in relocs))
        return result
    except (ValueError, IndexError, KeyError, struct.error):
        return {}  # no proof from an unreadable object


def link_rank(rows):
    """link_check.link_rank(rows) for ROWS = link_census.ledger(), kept in the shared picker
    cache (tools/picker_cache.py) per content of the ledgers it reads (functions.csv,
    data_rows.csv) and of the code computing it; every merge worker on the same ledger
    reads it back instead of resolving every row's object path (15-19 s). Object names
    follow the ledger's spelling of tracked sources, as a checkout writes them."""
    import link_check as LC
    import link_census as LCe
    import data_rows
    import picker_cache
    here = Path(__file__).resolve()
    inputs = [LCe.ROOT / "reverse/functions.csv", Path(data_rows.DATA_ROWS)]
    code = [here.with_name(n) for n in ("link_check.py", "link_census.py", "build.py", "data_rows.py")]
    key = [picker_cache.file_digest(p) for p in inputs + code]
    if None in key[len(inputs):] or LCe.ROOT != ROOT:
        return LC.link_rank(rows)
    return picker_cache.keyed("tu_skeleton-link-rank", key, lambda: LC.link_rank(rows))


class LinkGuard:
    """No merge leaves a unit that links not linking (LINK-042: GameFont.cpp,
    statistics.cpp, CrateSystem.cpp, MultiplayerSettings.cpp and htree.cpp each
    absorbed a donor that never linked, or lost the flags its donors linked
    under, and stopped linking).

    A unit links when a census says so: reverse/link_status.csv or the census
    index's blockers (they can be different censuses; either is enough). When a merge's files include one, a
    candidate text that keeps every matched row must also link as one object by
    tools/link_check.py's census rules: the Verifier's object of that text takes
    the link-order place of its earliest census unit, every unit it absorbs
    leaves the index (their definitions are its own now) with every census object
    the next census does not link (link_check.link_rank, code and data ledgers:
    a unit merged since the census defines nothing), and it must have no
    unresolved name, duplicate, losing COMDAT copy, wrong selection or
    hard-coded address, nor a new COMDAT copy that breaks another unit's link
    (link_check --new-variants' rule). Without the census index a merge that
    touches a linked unit is blocked, never waved through."""

    def __init__(self, tu, root=ROOT, index=None, truth=None, rank=None, owners=None):
        self.tu, self.root = tu, Path(root)
        self.index, self.truth, self.rank = index, truth, rank
        self.owners = owners    # link_census.ledger_owners, loaded when first needed
        self.gone = set()
        self._status, self.touched, self.previous, self.cache = None, None, {}, {}
        self.fetch_error, self.fetched = None, False
        self.before_contexts = {}
        self.before_weaks = {}

    def census_contexts(self, places):
        """Optional immutable census objects, authenticated by the index SHA256.

        These are evidence, not compiler cache entries. Missing/stale evidence
        never exempts a moved copy. A published object bundle can supply them at
        build/link_census/guard_objects/<index object digest>.obj.
        """
        import link_census as LCe
        result, self.before_weaks = {}, {}
        for position in places - self.gone:
            digest = self.index.get("digests", {}).get(self.index["objects"][position], "")
            if not re.fullmatch(r"[0-9a-f]{64}", digest):
                continue
            path = self.root / "build/link_census/guard_objects" / (digest + ".obj")
            try:
                data = path.read_bytes()
            except OSError:
                continue
            if hashlib.sha256(data).hexdigest() == digest:
                result[position] = portable_comdat_contexts(data)
                self.before_weaks[position] = {name for name, _ in LCe._weak_externals(data)}
        return result

    def preserves_existing_variant(self, name, digest, verdict, context, obj, places, view, rank):
        """Does this proven old copy retain both outside losses and selection?"""
        import link_census as LCe
        import link_check as LC
        if context is None or self.rank is None:
            return False
        # Another absorbed object can change an ordinary external reference's
        # provider without changing the functor's own bytes. The index retains
        # definitions and /alternatename routes, but COFF weak defaults need the
        # authenticated raw object for EVERY member of the cohort.
        absorbed = places - self.gone
        if not absorbed <= self.before_weaks.keys():
            return False
        for _, _, referent in context[2]:
            if any(referent in self.before_weaks[p] for p in absorbed):
                return False
            for table, at in LINK_TABLES:
                if any(at(entry) in absorbed for entry in self.index[table].get(referent, ())):
                    return False
            # Do not infer a surviving alias/runtime chain. Require a direct
            # external provider that the merge neither removes nor changes.
            if not any(at(entry) not in absorbed and self.index["objects"][at(entry)] in self.rank
                       for table, at in LINK_TABLES if table != "alternates"
                       for entry in self.index[table].get(referent, ())):
                return False
        proven = {self.index["objects"][p] for p, d, v in self.index["comdat"].get(name, ())
                  if p in places and p not in self.gone and (d, v) == (digest, verdict)
                  and self.before_contexts.get(p, {}).get((name, digest)) == context}
        if not proven:
            return False

        def state(index, order, replacement=None):
            objects = index["objects"]
            copies = {objects[i]: (d, v) for i, d, v in index["comdat"].get(name, ()) if objects[i] in order}
            exclusive = {objects[i] for i in index["strong"].get(name, ()) if objects[i] in order}
            if replacement is not None:
                copies[obj.name] = replacement
            losses = LCe.keep_rule([(o, *copies[o]) for o in sorted(copies, key=order.__getitem__)],
                                  referenced=LC.is_referenced(index, name))[0] if copies else {}
            definers = set(copies) | exclusive
            holder = min(definers, key=order.__getitem__) if definers else None
            selection = index["selection"]
            if name in selection["exceptions"]:
                place = selection["exceptions"][name]
                holder = None if place is None else objects[place] if objects[place] in definers else holder
            if holder is None:
                return losses, None, None
            selected = LCe.judge_selected(holder, copies, definers, exclusive, selection["owners"].get(name, set()))
            body = ("copy", *copies[holder]) if holder in copies else ("exclusive", holder)
            return losses, (selected, body), holder

        before, before_selected, before_holder = state(self.index, self.rank)
        after, after_selected, after_holder = state(view, rank, (digest, verdict))
        if before_selected is None or before_selected != after_selected:
            return False  # unknown /MAP holder, changed implementation, or changed owner
        cohort = {self.index["objects"][p] for p in places}
        if before_holder in cohort:
            if before_holder not in proven or after_holder != obj.name:
                return False
        elif before_holder != after_holder:
            return False  # an outside selected provider must remain the same object
        return not any(lost and not before.get(other, False) for other, lost in after.items() if other != obj.name)

    def status(self):
        if self._status is None:
            path = self.root / "reverse/link_status.csv"
            text = path.read_text(encoding="utf-8", errors="replace") if path.exists() else ""
            self._status = {r["source"]: r.get("linked") == "yes" for r in csv.DictReader(io.StringIO(text))}
        return self._status

    def load(self):
        """The census index: this checkout's, else the published one, downloaded
        once (index only, link_check.fetch_index(objects=False)). A failed
        download leaves it None, and prepare() blocks the merge."""
        import link_check as LC
        if (self.index is None and not LC.INDEX.exists() and not self.fetched
                and os.environ.get("BFME_LINK_GUARD_FETCH", "on") != "off"):
            self.fetched = True     # one try per merge
            try:
                with contextlib.redirect_stdout(io.StringIO()):
                    LC.fetch_index(objects=False)
            except BaseException as exc:  # noqa: BLE001 -- any failure leaves no index: blocked
                if isinstance(exc, KeyboardInterrupt):
                    raise
                self.fetch_error = str(exc) or type(exc).__name__
        if self.index is None and LC.INDEX.exists():
            self.index = LC.load_index()
        return self.index

    def linked(self, files):
        """The files a census records as linking."""
        blockers = self.index["blockers"] if self.index else {}
        return sorted(f for f in files if self.status().get(f) or (blockers.get(f) or {}).get("linked"))

    def position(self, f):
        import link_check as LC
        entry = self.index["blockers"].get(f)
        if entry and LC.in_census(self.index, entry.get("object")):
            if "places" not in self.cache:
                self.cache["places"] = {name: i for i, name in enumerate(self.index["objects"])}
            return self.cache["places"].get(entry["object"])
        return None

    def prepare(self, files):
        """Load the census index for a merge of `files`: the reason it cannot
        judge them, or None."""
        import link_check as LC
        import link_census as LCe
        if self.load() is None:
            return (f"no census index at {LC.INDEX.relative_to(LC.ROOT).as_posix()} "
                    "(python3 tools/link_check.py --fetch-index)"
                    + (f"; the download failed: {self.fetch_error}" if self.fetch_error else ""))
        try:
            LC.require_common_index(self.index)
        except SystemExit as exc:
            return str(exc)
        if self.truth is None:
            rows = LCe.ledger()
            self.truth, self.rank = LCe.RetailTruth(rows), link_rank(rows)
        outside = [f for f in self.linked(files) if self.position(f) is None]
        if outside:
            return "census-linked unit(s) missing from the census index: " + ", ".join(outside[:5])
        if self.rank is not None:
            self.gone = {p for p, name in enumerate(self.index["objects"])
                         if name not in self.rank and LC.in_census(self.index, name)}
        # one pass over the index: the names each merge file's (and gone unit's) object holds,
        # and the merge files' COMDAT copies
        want = {p for f in files if (p := self.position(f)) is not None} | self.gone
        self.touched = {table: collections.defaultdict(set) for table, _ in LINK_TABLES}
        for table, at in LINK_TABLES:
            for name, entries in self.index[table].items():
                for entry in entries:
                    if at(entry) in want:
                        self.touched[table][at(entry)].add(name)
        for name, copies in self.index["comdat"].items():
            for p, digest, _ in copies:
                if p in want and p not in self.gone:
                    self.previous.setdefault(p, {}).setdefault(name, set()).add(digest)
        self.before_contexts = self.census_contexts(want)
        return None

    def moved_provider(self, name, files):
        """Is `name` defined at the census only by units merged away since,
        and now held by a live unit outside `files`? prepare() drops the gone
        units' definitions and the census object of the unit that absorbed
        them predates the move, so the view has no definer; the ledger row
        does (its byte check found the symbol in that unit's object). The
        merge that moved it answered for it (no longer defines ...), so an
        unresolved reference to it is the census index's age, not this
        merge's: Recorder.cpp's ??0Rva0060C5FA after Rva0060C5FACtor.cpp went
        into Xfer.cpp, ControlBarScheme.cpp's ??0INI after INI_ctor.cpp went
        into INI.cpp."""
        definers = {at(entry) for table, at in LINK_TABLES if table != "alternates"
                    for entry in self.index[table].get(name, ())}
        if self.rank is None or not definers or not definers <= self.gone:
            return False
        if self.owners is None:
            import link_census as LCe
            self.owners = LCe.ledger_owners(LCe.ledger())
        import build
        mine = {build.obj_path(build.ROOT / f).name for f in files}
        return any(o in self.rank and o not in mine for o in self.owners.get(name, ()))

    def view(self, obj, places):
        """The census index with the objects at `places` and every gone unit's
        removed and `obj` at the first of `places`. With complete census
        provenance, rebuild the remaining objects' reference graph; otherwise
        retain the conservative aggregate. check_object adds the replacement."""
        index, out = self.index, dict(self.index)
        first, places = min(places, default=None), set(places) | self.gone
        for table, at in LINK_TABLES:
            names = set().union(*(self.touched[table].get(p, ()) for p in places))
            if names:
                out[table] = dict(index[table])
                for name in names:
                    kept = [entry for entry in index[table][name] if at(entry) not in places]
                    if kept:
                        out[table][name] = kept
                    else:
                        del out[table][name]
        out["objects"] = list(index["objects"])
        if first is not None:
            out["objects"][first] = obj.name
        graph = index.get("references")
        if isinstance(graph, dict) and isinstance(graph.get("edges"), dict):
            out["references"] = dict(graph, edges=dict(graph["edges"]), referenced=set(graph["referenced"]))
            # The aggregate graph alone cannot prove a removed reference dead:
            # an outside object may supply the very same root or COMDAT edge.
            # New census indexes retain every object's contribution, bound to
            # its census digest. Older or incomplete indexes stay conservative.
            import link_check as LC
            import link_census as LCe
            records = graph.get("objects")
            digests = index.get("digests", {})
            def bound(name, record):
                digest = digests.get(name)
                return (isinstance(record, dict) and isinstance(digest, str)
                        and re.fullmatch(r"[0-9a-f]{64}", digest) and record.get("digest") == digest
                        and isinstance(record.get("roots"), (set, frozenset))
                        and all(isinstance(n, str) for n in record["roots"])
                        and isinstance(record.get("edges"), dict)
                        and all(isinstance(n, str) and isinstance(targets, (set, frozenset))
                                and all(isinstance(t, str) for t in targets)
                                for n, targets in record["edges"].items())
                        and isinstance(record.get("weaks"), (tuple, list))
                        and all(isinstance(pair, (tuple, list)) and len(pair) == 2
                                and all(isinstance(n, str) for n in pair) for pair in record["weaks"]))

            if (graph.get("schema") == LC.REFERENCES_SCHEMA and isinstance(records, dict)
                    and len(set(index["objects"])) == len(index["objects"])
                    and set(records) == set(index["objects"])
                    and all(bound(name, record) for name, record in records.items())):
                remaining = [records[name] for p, name in enumerate(index["objects"]) if p not in places]
                roots, edges = LCe.merge_references((r["roots"], r["edges"]) for r in remaining)
                kept = set(out["selection"].get("owners", {}))
                kept.update(name for name, copies in out["comdat"].items()
                            if any(verdict is not None for _, _, verdict in copies))
                links = [pair for r in remaining for pair in r["weaks"]]
                links.extend((alias, target) for alias, entries in out["alternates"].items()
                             for _, target in entries)
                out["references"] = {"schema": LC.REFERENCES_SCHEMA, "edges": edges,
                                     "referenced": LCe.referenced_names(roots, edges, kept, links)}
            # A view has replaced providers and cannot itself serve as census
            # provenance, including when validation above failed.
            out["references"].pop("objects", None)
        return out

    def judge(self, obj, files, text):
        """Why the merged object of `files` (compiled from `text`) would not
        link, [] when it links or when no file of it links at the census."""
        if not self.linked(files):
            return []
        if obj is None:
            return ["no object to judge"]
        key = (str(obj), tuple(sorted(files)))
        if key not in self.cache:
            import link_check as LC
            import link_debt
            import build
            import link_census as LCe
            places = {p for f in files if (p := self.position(f)) is not None}
            view = self.view(Path(obj), places)
            obj = Path(obj)
            why = []
            # The next census places the merged object by the lowest row of ALL its
            # files, census-known or not. The view can only hold it at the census
            # slot of its earliest census unit, so a file that would move it earlier
            # than that slot is a link order this guard cannot model: refuse.
            merged = None
            if self.rank is not None:
                merged = min((r for f in files if (r := self.rank.get(build.obj_path(build.ROOT / f).name)) is not None),
                             default=None)   # link_rank's names (build.row_object)
            holder = self.index["objects"][min(places)] if places else None
            if merged is not None and holder in self.rank and merged < self.rank[holder]:
                why.append("a file without a census object would place the merged unit earlier in link "
                           "order than the guard can judge")
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                found = LC.check_object(obj, view, self.truth)
                rank, previous = None, {}
                if places and self.rank is not None and view["objects"][min(places)] == obj.name:
                    if holder in self.rank:
                        rank = dict(self.rank, **{obj.name: self.rank[holder]})
                # Existing copies are exempt only where they keep their link place: a
                # file absorbed from a later place moves its copies earlier, which can
                # make another unit's copy lose (breaks_others judges those).
                for p in places:
                    if rank is not None and self.rank.get(self.index["objects"][p]) != rank[obj.name]:
                        continue
                    for name, digests in self.previous.get(p, {}).items():
                        previous.setdefault(name, set()).update(digests)
                breaks = LC.new_variants(obj, view, self.truth, previous, rank) if rank else []
                copies, defined, _, _ = LCe.object_facts(obj, self.truth)
                if breaks:
                    contexts = portable_comdat_contexts(obj.read_bytes())
                    facts = {name: (digest, verdict) for name, digest, _, verdict in copies}
                    breaks = [name for name in breaks if name not in facts or not self.preserves_existing_variant(
                        name, *facts[name], contexts.get((name, facts[name][0])), obj, places, view, rank)]
                # A definition an absorbed unit made and the merged object no longer
                # makes must not be one the census still references with no other
                # definer: a linked consumer would go unresolved.
                mine = set(defined) | {n for n, _, _, _ in copies} | set(LCe.common_definitions(obj))
                dropped = set()
                for table in ("strong", "comdat", "common"):
                    for p in places:
                        dropped |= self.touched[table].get(p, set())
                dropped -= mine
                other = lambda n: (view["strong"].get(n) or view["comdat"].get(n) or view["common"].get(n)
                                   or LCe.excused(n, view["excuses"]["runtime"], view["excuses"]["imported"],
                                                  view["excuses"]["stubs"]))
                lost = sorted(n for n in dropped if not other(n) and LC.is_referenced(view, n))
            why += ([f"unresolved {n}" for n in found["unresolved"] if not self.moved_provider(n, files)]
                    + [f"duplicate {n}" for n in found["duplicates"]]
                    + [f"comdat {n} ({rule})" for n, rule, _ in found["comdat"]]
                    + [f"selected {n}" for n in found["selected"]]
                    + [f"breaks another unit's copy of {n}" for n in breaks]
                    + [f"no longer defines {n}, which the census still references" for n in lost])
            addresses = link_debt.addresses(text, self.tu)
            if addresses:
                why.append(f"{len(addresses)} hard-coded image address(es), e.g. {addresses[0]}")
            self.cache[key] = why
        return self.cache[key]


class SplitLinkGuard:
    """Compare the two actual split objects, at their post-carve link places.

    Compile evidence is bounded to the original file and existing destination.
    Other providers remain the census's evidence, as in the merge guard. No
    census/cache publication or whole-tree compilation takes place here.
    """
    KINDS = ("unresolved", "duplicates", "comdat", "addresses", "selected")

    def __init__(self, tu, source, residual, residual_obj, carved, data_moved=(), root=ROOT, expected_source=None):
        self.tu, self.source, self.root = tu, source, Path(root)
        self.residual, self.residual_obj = residual, residual_obj
        self.carved, self.data_moved = set(carved), set(data_moved)
        self.expected_source = expected_source
        self.guard = LinkGuard(tu, root=root)
        self.before, self.cache = None, {}

    def load(self):
        return self.guard.load()

    def linked(self, files):
        return self.guard.linked(files)

    def input_state(self):
        import link_census as LCe
        paths = ("reverse/functions.csv", "reverse/data_rows.csv", "reverse/symbols.csv",
                 "reverse/flag_overrides.csv", "reverse/retail_inventory/flag_regions.csv",
                 "tools/tu_skeleton.py", "tools/flag_defaults.py", *("tools/" + name for name in LCe.TOOL_FILES))
        return (LCe.census_inputs_state(), tuple((name, hashlib.sha256((self.root / name).read_bytes()).hexdigest()
                                                 if (self.root / name).is_file() else None) for name in paths))

    def record(self, source, obj, text):
        """An immutable private copy with the real object's logical name."""
        import build
        import struct
        import link_census as LCe
        import link_check as LC
        if obj is None:
            raise LCe.MissingObject(f"{source}: no compiled split object")
        raw = Path(obj).read_bytes()
        path = self.root / "build/tu_skeleton/link_guard" / hashlib.sha256(raw).hexdigest() / build.obj_path(self.root / source).name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(raw)
        try:
            return dict(source=source, obj=path, text=text, fact=LCe.object_facts(path, self.guard.truth),
                        common=LCe.common_definitions(path), aliases=LC.alternate_names(path),
                        references=LCe.object_references(path), contexts=portable_comdat_contexts(raw))
        except (struct.error, IndexError, ValueError, KeyError) as error:
            raise LCe.MissingObject(f"{source}: unreadable split object: {error}") from error

    def prepare(self, files):
        import link_census as LCe
        try:
            self.inputs = self.input_state()
            why = self.guard.prepare(files)
            if why:
                return why
            self.original = {f: (self.root / f).read_bytes() if (self.root / f).exists() else None
                             for f in (self.source, self.tu)}
            if self.expected_source is not None and self.original[self.source] != self.expected_source:
                return "mixed source changed while planning the split; retry"
            self.rows, self.data = LCe.ledger(), LCe.data_ledger()
            records = {}
            for source, raw in self.original.items():
                if raw is None:
                    continue
                rows = [r for r in self.rows if r["source"] == source]
                v = Verifier(source)
                text = raw.decode("utf-8-sig", errors="replace")
                matched = v.matched(text, rows)
                if matched is None or not {r["target_rva"] for r in rows} <= matched:
                    return f"original {source} does not byte-verify; repair its baseline first"
                records[source] = self.record(source, v.obj, text)
            self.records = records
            self.before = self.view(records, self.rows, self.data)
            self.debt = self.findings(self.before, records)
            if self.input_state() != self.inputs:
                return "split compiler/ledger inputs changed during baseline verification; retry"
            return None
        except (OSError, ValueError, LCe.MissingObject) as error:
            return f"split linking evidence unavailable: {error}"

    def view(self, records, rows, data):
        """Replace both affected objects and remap every index into true order."""
        import link_census as LCe
        import link_check as LC
        index = self.guard.index
        order = [p.name for p in LCe.link_order(rows, data)]
        if len(order) != len(set(order)):
            raise ValueError("split object-name collision")
        replacements = {r["obj"].name: r for r in records.values()}
        affected = {self.guard.position(f) for f in (self.source, self.tu)} - {None}
        visible = {name for i, name in enumerate(index["objects"]) if i not in affected}
        objects = [name for name in order if name in visible or name in replacements]
        if not replacements.keys() <= set(objects):
            raise ValueError("an affected split object has no ledger link position")
        positions = {name: i for i, name in enumerate(objects)}
        remap = {i: positions[name] for i, name in enumerate(index["objects"])
                 if i not in affected and name in positions}
        out = dict(index, objects=objects)
        for table, at in LINK_TABLES:
            out[table] = {}
            for name, entries in index[table].items():
                kept = [remap[e] if table == "strong" else (remap[e[0]], *e[1:])
                        for e in entries if at(e) in remap]
                if kept:
                    out[table][name] = kept
        for name, record in replacements.items():
            position = positions[name]
            copies, defined, _, _ = record["fact"]
            for symbol in defined:
                out["strong"].setdefault(symbol, []).append(position)
            for symbol, digest, _, verdict in copies:
                out["comdat"].setdefault(symbol, []).append((position, digest, verdict))
            for symbol, size in record["common"].items():
                out["common"].setdefault(symbol, []).append((position, size))
            for symbol, target in record["aliases"].items():
                out["alternates"].setdefault(symbol, []).append((position, target))
        for table, _ in LINK_TABLES:
            for entries in out[table].values():
                entries.sort()
        out["selection"] = dict(owners=LCe.ledger_owners(rows, data), exceptions={
            name: None if holder is None else positions.get(index["objects"][holder])
            for name, holder in index["selection"]["exceptions"].items()})
        graph = LC.index_references(index)
        if graph is not None:
            out["references"] = dict(graph, edges=dict(graph["edges"]), referenced=set(graph["referenced"]))
            LC.add_references(out, [r["references"] for r in records.values()],
                              [pair for r in records.values() for pair in r["fact"][3]],
                              set(out["selection"]["owners"]) |
                              set().union(*(LC.kept_copies(out, r["fact"][0]) for r in records.values())))
        return out

    def findings(self, view, records):
        import link_check as LC
        import link_debt
        result = {}
        for source, record in records.items():
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                found = LC.check_object(record["obj"], view, self.guard.truth)
            found["addresses"] = link_debt.addresses(record["text"], source)
            result[source] = collections.Counter((kind, tuple(item) if isinstance(item, (tuple, list)) else item)
                                                 for kind in self.KINDS for item in found[kind])
        return result

    def outside_failures(self, after, records):
        """Judge changed symbol contracts without rebuilding outside consumers."""
        import link_check as LC
        import link_census as LCe
        before = self.before
        cohort = {r["obj"].name for r in (*self.records.values(), *records.values())}
        names = set().union(*(LCe.touched_names(r["fact"]) | set(r["common"]) | set(r["aliases"])
                              for r in (*self.records.values(), *records.values())))
        for view in (before, after):
            graph = LC.index_references(view)
            if graph is not None:
                names |= graph["referenced"] - before.get("references", {}).get("referenced", set())
        while True:
            more = {alias for view in (before, after) for alias, entries in view["alternates"].items()
                    if any(target in names for _, target in entries)} - names
            if not more:
                break
            names |= more

        def resolves(view, name, seen=frozenset()):
            return bool(view["strong"].get(name) or view["comdat"].get(name) or view["common"].get(name)
                        or LCe.excused(name, view["excuses"]["runtime"], view["excuses"]["imported"],
                                       view["excuses"]["stubs"])) or (name not in seen and any(
                            resolves(view, target, seen | {name}) for _, target in view["alternates"].get(name, ())))

        def state(view, name):
            objects = view["objects"]
            copies = {objects[p]: (d, v) for p, d, v in view["comdat"].get(name, ())}
            strong = {objects[p] for p in view["strong"].get(name, ())}
            definers = set(copies) | strong
            losses = LCe.keep_rule(view["comdat"].get(name, ()), LC.is_referenced(view, name))[0] if copies else {}
            losses = {objects[p] for p, lost in losses.items() if lost and objects[p] not in cohort}
            duplicates = {objects[p] for p in set(view["strong"].get(name, ())) |
                          {p for p, _, _ in view["comdat"].get(name, ())}
                          if objects[p] not in cohort and LC.duplicate(name, p, objects[p] in strong, p, view)}
            chosen = min(set(view["strong"].get(name, ())) |
                         {p for p, _, _ in view["comdat"].get(name, ())}, default=None)
            chosen = view["selection"]["exceptions"].get(name, chosen)
            holder = objects[chosen] if chosen is not None and chosen < len(objects) else None
            selected = LCe.judge_selected(holder, copies, definers, strong, view["selection"]["owners"].get(name, set()))
            body = (("copy", *copies[holder]) if holder in copies else
                    ("strong", name if holder in cohort else holder)) if holder in definers else None
            return losses, duplicates, selected, body, holder

        def context(view, state, name, records):
            holder, body = state[4], state[3]
            if body is None or body[0] != "copy":
                return None
            for record in records.values():
                if record["obj"].name == holder:
                    return record["contexts"].get((name, body[1]))
            # An outside copy needs authenticated old bytes, just as a moved
            # merge copy does. Its normalized digest alone omits local context.
            if holder in self.guard.index["objects"]:
                position = self.guard.index["objects"].index(holder)
                return self.guard.census_contexts({position}).get(position, {}).get((name, body[1]))
            return None

        failures = []
        for name in sorted(names):
            old, new = state(before, name), state(after, name)
            if LC.is_referenced(before, name) and resolves(before, name) and not resolves(after, name):
                failures.append(f"outside consumers lose provider {name}")
            if new[0] - old[0]:
                failures.append(f"new outside COMDAT losers for {name}")
            if new[1] - old[1]:
                failures.append(f"new outside duplicate for {name}")
            if new[2] == "wrong" and old[2] != "wrong":
                failures.append(f"outside consumers select a wrong provider for {name}")
            routes = lambda v: list(dict.fromkeys(target for _, target in v["alternates"].get(name, ())))
            direct = lambda v: v["strong"].get(name) or v["comdat"].get(name) or v["common"].get(name)
            if (LC.is_referenced(before, name) and not direct(before) and not direct(after)
                    and routes(before) and routes(before) != routes(after)):
                failures.append(f"outside alias route changes for {name}")
            if (old[3] is not None and old[3][0] == "copy" and old[3] == new[3] and old[4] != new[4]
                    and LC.is_referenced(before, name) and not (old[2] == new[2] == "ok")):
                old_context = context(before, old, name, self.records)
                safe_routes = old_context is not None
                for _, _, referent in old_context[2] if old_context else ():
                    # Raw relocation equality cannot prove a callee's route
                    # when another changed object defines or redirects it.
                    for record in (*self.records.values(), *records.values()):
                        if (referent in set(record["fact"][1]) | {n for n, _, _, _ in record["fact"][0]}
                                | set(record["common"]) | set(record["aliases"])
                                | {n for n, _ in record["fact"][3]}):
                            safe_routes = False
                    if not any(p not in cohort for p in ({before["objects"][i] for i in before["strong"].get(referent, ())}
                               | {before["objects"][i] for i, _, _ in before["comdat"].get(referent, ())}
                               | {before["objects"][i] for i, _ in before["common"].get(referent, ())})):
                        safe_routes = False
                if not safe_routes or old_context != context(after, new, name, records):
                    failures.append(f"moved selected COMDAT {name} lacks matching private/weak-free context")
            if name in self.guard.index["selection"]["exceptions"]:
                signature = lambda v: [(table, v["objects"][at(e)], *(() if table == "strong" else e[1:]))
                                       for table, at in LINK_TABLES[:2] for e in v[table].get(name, ())]
                if signature(before) != signature(after):
                    failures.append(f"changed /MAP selection for {name} needs measured evidence")
            elif old[3] is not None and old[3] != new[3] and LC.is_referenced(before, name) and not (old[2] == new[2] == "ok"):
                failures.append(f"selected implementation changes for {name}")
        return failures

    def judge(self, obj, files, text):
        if self.source not in files:
            return []  # greedy seed trial; judge both objects when the carve joins it
        import link_census as LCe
        try:
            key = (str(obj), tuple(sorted(files)))
            if self.before is None:
                return ["split linking baseline was not prepared"]
            if self.input_state() != self.inputs:
                return ["split compiler/ledger inputs changed during verification; retry"]
            if any(((self.root / f).read_bytes() if (self.root / f).exists() else None) != raw
                   for f, raw in self.original.items()):
                return ["split source changed during verification; retry"]
            if key in self.cache:
                return self.cache[key]
            rows = [dict(r, source=self.tu) if r["source"] == self.source and r["target_rva"] in self.carved else r
                    for r in self.rows]
            moved = data_row_names((self.root / "reverse/data_rows.csv").read_bytes(), self.data_moved) if self.data_moved else set()
            data = [dict(r, source=self.tu) if r["source"] == self.source and r["name"] in moved else r for r in self.data]
            records = {self.source: self.record(self.source, self.residual_obj, self.residual),
                       self.tu: self.record(self.tu, obj, text)}
            after = self.view(records, rows, data)
            found = self.findings(after, records)
            failures = []
            for source, debt in found.items():
                if source in self.debt and not self.debt[source] and debt:
                    failures.append(f"{source}: a link-clean original would stop linking")
            added = sum(found.values(), collections.Counter()) - sum(self.debt.values(), collections.Counter())
            failures += [f"new {kind}: {item}" for kind, item in sorted(added, key=str)]
            failures += self.outside_failures(after, records)
            if self.input_state() != self.inputs:
                failures.append("split compiler/ledger inputs changed during verification; retry")
            self.cache[key] = failures
            return failures
        except (OSError, ValueError, LCe.MissingObject) as error:
            return [f"split linking evidence unavailable: {error}"]


def header_queue_rows(root=ROOT):
    """{source: [class, ...]} of reverse/header_queue.tsv: a donor listed there
    still carries a private copy of a class with a canonical header, and the
    class gate refuses the merged TU at commit; adopt first
    (`tools/header_adopt_lane.py accept`)."""
    path = Path(root) / "reverse/header_queue.tsv"
    out = collections.defaultdict(list)
    if path.exists():
        for row in csv.DictReader(io.StringIO(path.read_text(encoding="utf-8", errors="replace")), delimiter="\t"):
            if row.get("source") and row.get("class"):
                out[row["source"]].append(row["class"])
    return out


# the largest donor chunk accretion tries in one compile (greedy())
ACCRETE_MAX = 64


def merge(tu, dry_run=False, log=print, claim=True):
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    report = {"tu": tu, "approved": len(sk), "mixed": mixed, "refused": refused, "accepted": [], "rejected": {}}
    queued = header_queue_rows()
    adopt = {f: sorted(set(queued[f])) for f in don if f in queued}
    if adopt:
        report["adopt_first"] = adopt     # the class gate will refuse these donors' private copies at commit
    if tu in mixed or ((ROOT / tu).exists() and tu not in don):
        report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
        return report
    if len(don) < 2 and not (len(don) == 1 and tu not in don):
        report["blocked"] = "fewer than two donors"
        return report
    if claim and not dry_run:
        held = claim_scope(tu, don)
        if held:
            claims.release(claim_keys(tu, don))     # the part of the scope we did win goes back
            report["blocked"] = held_message(held)
            return report
        report = _merge(tu, sk, don, report, dry_run)
        if "blocked" in report:   # nothing was written: give the scope back
            claims.release(claim_keys(tu, don))
        return view_hint(report, tu, don)
    return view_hint(_merge(tu, sk, don, report, dry_run), tu, don)


def view_hint(report, tu, don):
    """A donor rejected for a compile error that a differing class view causes
    (a member missing or renamed, an overload or base not found, an access
    refused) or that names a class the TU's files each declare their own view
    of is pointed at tools/tu_views.py: it gives every file the same verified
    view, so the merge emits the class once."""
    errors = [str(why) for why in report.get("rejected", {}).values() if str(why).startswith("compile")]
    if not errors:
        return report
    import tu_views
    shared = tu_views.shared_private(sorted(don), ROOT)
    viewish = any(re.search(r"error (C2039|C2065|C2511|C2248|C2504|C2653|C2660|C2027|C2079)\b", e) for e in errors)
    if not viewish:
        shared = [c for c in shared if any(re.search(r"\b" + re.escape(c) + r"\b", e) for e in errors)]
    if shared:
        report["reconcile"] = (f"python3 tools/tu_views.py {tu} --dry-run, then without --dry-run: the donors "
                               f"declare their own views of {', '.join(shared[:4])}{', ...' if len(shared) > 4 else ''}"
                               " (docs/consolidation.md, \"Workflow per TU\", step 4)")
    return report


def _merge(tu, sk, don, report, dry_run, texts=None, applier=None, guard=None):
    v = Verifier(tu)
    # Splits provide their own two-object guard: their residual stays in the link.
    guard = guard or (None if applier else LinkGuard(tu))
    if guard is not None:
        guard.load()
        linked = guard.linked(don)
        why = guard.prepare(don) if linked or applier else None
        report["link_guard"] = ("split: residual and destination compared together" if applier else
                                f"census-linked: {', '.join(linked)}" if linked
                                else "no file of this merge links at the census")
        if why:
            report["blocked"] = f"link guard: {why}; census-linked: {', '.join(linked)}"
            return report
    texts = dict(texts or {})
    for f in don:
        if f not in texts:
            # a quoted include resolves from the including file's directory: a donor
            # from another directory is read as it will compile beside the TU
            texts[f] = relocate_includes((ROOT / f).read_text(encoding="utf-8-sig", errors="replace"),
                                         posixpath.dirname(f), posixpath.dirname(tu))
    # A flag override travels with its donor (carry()): the merge is verified under its
    # flags, the TU's when the TU has one, else the most rows'; a donor overridden with
    # other flags stays out (split path: the carve keeps its own flag handling).
    ov = {} if applier else {f: e for f in don if (e := v.fd.overrides().get(f))}
    if ov:
        weight = collections.Counter()
        for e in ov.values():
            weight[e["flags"]] += int(e["rows"] or 0)
        v.flags = ov[tu]["flags"] if tu in ov else sorted(weight.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
        for f, e in sorted(ov.items()):
            if e["flags"] != v.flags:
                report["rejected"][f] = f"its flag override '{e['flags']}' is not the carried '{v.flags}'"
        don = {f: r for f, r in don.items() if f not in report["rejected"]}
        ov = {f: e for f, e in ov.items() if f in don}
    base = {}
    for f in don:
        got = v.matched(texts[f], don[f])
        base[f] = got or set()
    if ov:   # nobody may lose a row its own build matches under the region default
        rv = Verifier(tu, region=True)
        for f in [f for f in don if f not in ov and base[f]]:
            lost = (rv.matched(texts[f], don[f]) or set()) - base[f]
            if lost and f == tu:
                report["blocked"] = f"the TU file loses {len(lost)} row(s) under the carried flag override"
                return report
            if lost:
                report["rejected"][f] = f"loses {len(lost)} row(s) under the carried flag override '{v.flags}'"
                base[f] = set()
                don = {g: r for g, r in don.items() if g != f}
    good = [f for f in don if base[f]]
    if tu in don and tu not in good:
        report["rejected"].update({f: "no baseline match" for f in don if f not in good})
        report["blocked"] = "the TU file's own rows do not match under the verifier"
        return report
    weight = collections.Counter()
    cands = {}
    for f in good:
        fl = flags_of(texts[f])
        # region-managed codegen tokens are inert (Verifier.effective writes the
        # region's), so flag sets that differ only in them are one candidate
        k = tuple(x for x in fl if not x.lower().startswith(("/i", "-i"))
                  and not v.fd.MANAGED.match(x.replace("/", "-", 1) if x.startswith("/") else x))
        weight[k] += len(base[f])
        cands.setdefault(k, None)
    # include directories: the seed's first (its shims must shadow a donor's), then
    # each donor's in order, one spelling per directory (`/I` and `-I` are the same)
    incs, seen_dirs = [], set()
    for f in ([tu] if tu in good else []) + [f for f in good if f != tu]:
        for x in flags_of(texts[f]):
            if x.lower().startswith(("/i", "-i")):
                d = x[2:].replace("\\", "/").rstrip("/")
                if d not in seen_dirs:
                    seen_dirs.add(d)
                    incs.append(x)
    flag_sets = []
    for k, _ in weight.most_common():
        fl = stl_static(list(k) + incs)
        if fl not in flag_sets:     # sets that differ only in the define are one
            flag_sets.append(fl)

    link_why = {}

    def attempt(files, flags):
        best = None
        need = set().union(*(base[f] for f in files))
        rows = [r for f in files for r in don[f]]
        for st, _first in distinct_strategies(lambda st: compose(tu, sk, files, texts, flags, st)):
            drop, drop_all = set(), set()
            for _ in range(16):
                text = compose(tu, sk, files, texts, flags, st, frozenset(drop), frozenset(drop_all))
                got = v.matched(text, rows)
                again = redefined(v.all_errors) if got is None else set()
                if not again - drop_all:
                    break
                drop_all |= again & drop   # still redefined with only the seed's copy: a header owns it
                drop |= again
            if got is not None and need <= got:
                why = guard.judge(getattr(v, "obj", None), files, text) if guard else []
                if not why:
                    return text
                link_why[tuple(files)] = why
                best = "link"   # matched, but a unit that links would stop linking
                continue
            best = best or ("compile" if got is None else "bytes")
        return best

    def link_reason(files, f):
        if applier:
            return "link: split residual/destination would regress: " + "; ".join(link_why[tuple(files)][:3])[:300]
        linked = guard.linked(files)
        whose = (f"{f} links at the census" if f in linked
                 else f"{f} never linked at the census and {', '.join(linked)} link")
        return f"link: {whose}; the merged object would not: " + "; ".join(link_why[tuple(files)][:3])[:300]

    def reject_reason(res, errors, files, f):
        return (link_reason(files, f) if res == "link"
                else res + ("" if res == "bytes" else ": " + " | ".join(errors)[:300]))

    tried = {}

    def tried_attempt(files, flags):
        """attempt(), once per (donor list, flags): accretion asks again for a set it
        already compiled (a bisected chunk whose first half was accepted)."""
        key = (tuple(files), tuple(flags))
        if key not in tried:
            tried[key] = (attempt(files, flags), list(v.errors))
        return tried[key]

    def greedy(order, flags, floor=None):
        """Accrete donors in `order`; each accepted group verified by attempt().
        None once the rows still reachable cannot beat `floor` (the best trial's
        score), so a later order or flag set stops as soon as it cannot win.

        Group testing: acc + a chunk is tried as one text; a chunk that verifies is
        accepted whole, one that fails is bisected down to the donors that fail
        alone against the then-accepted set (rejected, with that attempt's reason).
        The chunk doubles after a success and halves after a failure, so a TU of n
        donors with r rejects costs about n/chunk + r*log(chunk) compiles, not n."""
        acc, rej = [], {}

        def settle(group):
            res, errors = tried_attempt(acc + group, flags)
            if res not in ("compile", "bytes", "link"):
                acc.extend(group)
                return True
            if len(group) == 1:
                rej[group[0]] = reject_reason(res, errors, acc + group, group[0])
                return False
            mid = len(group) // 2
            settle(group[:mid])
            settle(group[mid:])     # after an accepted first half: the failing set itself, from the cache
            return False

        at, size = 0, 1             # the seed alone first: everything else is judged against it
        while at < len(order):
            if floor is not None and sum(len(base[f]) for f in acc + order[at:]) <= floor:
                return None
            group = order[at:at + size]
            at += len(group)
            size = min(size * 2, ACCRETE_MAX) if settle(group) else max(1, size // 2)
        return acc, rej

    first = {f: min(int(r["target_rva"], 16) for r in don[f]) for f in good}
    orders = [sorted(good, key=first.get), sorted(good, key=lambda f: (-len(base[f]), first[f])),
              sorted(good, key=lambda f: (-len(texts[f]), first[f]))]
    if tu in good:   # an existing file at the TU path is always the seed
        orders = [[tu] + [f for f in o if f != tu] for o in orders]
    best, seed_error = None, None
    rejected_seed = None
    def screen(flags, cands, out):
        """Add to `out` the donors of `cands` (a trial's compile rejects, then
        under each later flag set the donors screened out so far) that also fail
        to compile beside the seed alone under `flags`.

        Such a donor is left out of the remaining orders under these flags
        instead of failing again at several compiles per order. Only a donor a
        trial already rejected is screened: failing beside the seed alone does
        not prove it fails in every larger set (another donor can supply what
        compose dropped from it; LuaScriptEngine.cpp kept three such donors), so
        the first flag set's first order tries every donor. Byte and link
        rejects stay in,
        and without a seed that verifies by itself nothing is screened.
        Screening only costs rows a reordering might have found; every accepted
        set is still verified by attempt()."""
        if tu not in good or tried_attempt([tu], flags)[0] in ("compile", "bytes", "link"):
            return
        for f in cands:
            if f != tu and f not in out:
                res, errors = tried_attempt([tu, f], flags)
                if res == "compile":
                    out[f] = reject_reason(res, errors, [tu, f], f)

    suspects = []

    def trial(flags_list):
        nonlocal best, seed_error, rejected_seed
        for flags in flags_list:
            out = {}
            screen(flags, suspects, out)
            for o in orders:
                got = greedy([f for f in o if f not in out], flags, best[0] if best is not None else None)
                if got is None:
                    continue    # could not have scored higher than the best trial
                acc, rej = got
                screen(flags, [f for f, why in rej.items() if why.startswith("compile")], out)
                suspects.extend(f for f in out if f not in suspects)
                rej = {**out, **rej}
                score = sum(len(base[f]) for f in acc)
                if (tu in good and tu not in acc):
                    seed_error = seed_error or rej.get(tu) or "the seed does not verify under the merged flags"
                    # Keep the most productive failed trial's diagnostics even
                    # though it cannot be considered for applying a merge.
                    if rejected_seed is None or score > rejected_seed[0]:
                        rejected_seed = (score, rej)
                    continue
                if best is None or score > best[0]:
                    best = (score, acc, rej, flags)

    trial(flag_sets[:3])
    if best is None and tu in good:
        # The popular flag sets are a donor majority's, and a donor's include dir
        # (a shim such as bfmealloc, which needs /D_STLP_USE_STATIC_LIB) can break
        # a seed whose flags lack what that shim expects. Try the seed's own flags
        # with every include dir, then with only its own, so a seed that verifies
        # by itself is never blocked by its donors' spelling.
        own = flags_of(texts[tu])
        own_k = [x for x in own if not x.lower().startswith(("/i", "-i"))
                 and not v.fd.MANAGED.match(x.replace("/", "-", 1) if x.startswith("/") else x)]
        own_incs = [x for x in own if x.lower().startswith(("/i", "-i"))]
        extra = [stl_static(own_k + incs), own_k + own_incs]
        trial([f for i, f in enumerate(extra) if f not in flag_sets[:3] and f not in extra[:i]])
    report["rejected"].update({f: "no baseline match" for f in don if f not in good})
    if not best or len(best[1]) < 2 and not (len(best[1]) == 1 and best[1][0] != tu):
        report["rejected"].update(best[2] if best else rejected_seed[1] if rejected_seed else {})
        report["blocked"] = "no verified merge of two or more donors" + \
            (f"; the seed itself fails under every merged flag set: {seed_error[:300]}" if seed_error and not best else "")
        return report
    score, acc, rej, flags = best
    if ov and not set(acc) & set(ov):   # verified under flags no accepted donor carries: redo without them
        report["rejected"].update({f: "its flag override is not carried by the verified merge" for f in ov})
        return _merge(tu, sk, {f: r for f, r in don.items() if f not in ov}, report, dry_run, texts, applier, guard)
    text = attempt(acc, flags)
    if text in ("compile", "bytes", "link"):   # the accepted set no longer re-verifies (a flaky compile, an ICE):
        report["rejected"].update(rej)          # never write the failure token as the TU's text
        report["blocked"] = (f"the accepted donors did not re-verify ({text}"
                             + (": " + " | ".join(v.errors)[:300] if text == "compile" else "")
                             + (": " + "; ".join(link_why[tuple(acc)][:3])[:300] if text == "link" else "") + ")")
        return report
    if ov:   # the TU spells the override's flags (flag_defaults check)
        text = v.effective(text, [r for f in acc for r in don[f]])
    report.update(accepted=acc, flags=flags, rows=score)
    report["rejected"].update(rej)
    carry = None
    if applier is None:
        carry = Carry(ROOT, tu, acc, texts, text, v.flags)
        report.update(carry.report())
        if carry.problems:
            report["blocked"] = "protected registers: " + "; ".join(carry.problems[:5])
            return report
    if dry_run:
        report["text"] = text
        return report
    moved = applier(tu, acc, text) if applier else apply(tu, acc, text, carry=carry)
    report["repointed"] = moved
    report["stage"] = "staged: " + " ".join([tu] + sorted(moved) + [f for f in acc if f != tu])
    report["subject"] = (f"Merge {len(acc)} files into {posixpath.basename(tu)} "
                         f"({score} rows, tu_map approved TU, retail order)")
    return report


# ---------------------------------------------------------------- split
# A mixed file holds matched rows of several TUs (and rows the map has not
# placed). A merge never splits one; this lane carves the rows approved for ONE
# TU out of it, straight into that TU path (tu_ownership A2: a moved row lands
# only in its approved TU), and leaves everything else where it was. The carved
# bodies travel as an in-memory donor through the same verifier, strategies,
# flag choice and claims as a merge; the residual is re-verified under its own
# path and flags. Nothing is written unless both sides keep every matched row.
TEMPLATE = re.compile(r"^\?\?\$([A-Za-z_]\w*)@")
OPERATORS = {"4": "operator=", "8": "operator==", "9": "operator!=", "A": "operator[]", "C": "operator->",
             "D": "operator*", "E": "operator++", "F": "operator--", "G": "operator-", "H": "operator+",
             "R": "operator()", "Y": "operator+=", "Z": "operator-=", "_0": "operator/=", "_4": "operator&="}
OPERATOR = re.compile(r"^\?\?(_?[0-9A-Z])([A-Za-z_]\w*)@@")
CNAME = re.compile(r"^_?([A-Za-z_]\w*?)(?:@\d+)?$")
# escape hatches whose per-file counts a carve moves (hatch_counters.py rule 3a)
HATCH_IN_BODY = (re.compile(r"(?:^\s*#\s*pragma\s+|\b__pragma\s*\(\s*)optimize\s*\(", re.M), re.compile(r"\b__emit\b"),
                 re.compile(r"__declspec\s*\(\s*selectany\s*\)"), re.compile(r"present-unmatched\b"),
                 re.compile(r"class-gate:\s*allow\s+"), re.compile(r"[/-]alternatename:", re.I),
                 re.compile(r"(?<![A-Za-z0-9_])g_\w*?(?:Va|VA|Rva|RVA|DAT_?)[0-9A-Fa-f]{6,8}\w*"))
INTERNAL = re.compile(r"(?:^|\s)(?:static|inline|__forceinline|__inline)\b")


QUALIFIED = re.compile(r"^\?([A-Za-z_]\w*)@(?:\?\$)?([A-Za-z_]\w*)@")      # ?m@Class@@, ?m@?$vector@D@_STL@@, ?m@Inner@Outer@@
SPECIAL = re.compile(r"^\?\?(_G|_E|0|1)(?:\?\$)?([A-Za-z_]\w*)@")           # ctor, dtor, deleting dtors (ride with the dtor)


def row_names(name):
    """(class or None, method) a ledger symbol's out-of-line definition would spell."""
    m = FUNCLET.match(name)
    if m:
        return row_names(m.group(1))
    m = SPECIAL.match(name)
    if m:
        return m.group(2), (m.group(2) if m.group(1) == "0" else "~" + m.group(2))
    m = QUALIFIED.match(name)
    if m:
        return m.group(2), m.group(1)
    m = OPERATOR.match(name)
    if m and m.group(1) in OPERATORS:
        return m.group(2), OPERATORS[m.group(1)]
    m = TEMPLATE.match(name)
    if m:
        return None, m.group(1)
    if name.startswith("?"):
        m = re.match(r"^\?([A-Za-z_]\w*)@@", name)   # a free function: ?name@@YA...
        return (None, m.group(1)) if m else (None, name)
    m = CNAME.match(name)
    return None, (m.group(1) if m else name)


def head_names(body):
    """(class or None, method) of one definition's head, or None when unreadable."""
    head = norm(body.split("{")[0])
    head = re.sub(r"__declspec\s*\([^)]*\)", " ", head)
    head = re.sub(r"\b(?:throw|__attribute__)\s*\([^)]*\)\s*$", " ", head)
    at = head.find("(")
    if at < 0:
        return None
    left = head[:at].rstrip()
    while left.endswith(">"):   # a template argument list before the parameters
        depth, i = 0, len(left) - 1
        while i >= 0:
            depth += {">": 1, "<": -1}.get(left[i], 0)
            if depth == 0:
                break
            i -= 1
        left = left[:i].rstrip()
    m = re.search(r"(?:([A-Za-z_]\w*)\s*::\s*)?(~?[A-Za-z_]\w*|operator\s*[^\s(]+)$", left)
    if not m:
        return None
    meth = re.sub(r"\s+", "", m.group(2)) if m.group(2).startswith("operator") else m.group(2)
    return m.group(1), meth


def identify(rows, spans):
    """{row rva: [indices of candidate spans]} -- a definition that spells the
    row's name, else a macro invocation naming its class (or its method, for a
    free function) among the arguments; [] = unidentified."""
    heads = [head_names(c) if k == "def" else None for _, _, c, k in spans]
    def macro_args(span):     # the invocation is the span's last line; comment lines above it travel with it
        m = MACRO_LINE.match(span.rstrip("\n").splitlines()[-1])
        return set(re.findall(r"[A-Za-z_]\w*", m.group(2))) if m else set()
    args = [macro_args(c) if k == "macro" else None for _, _, c, k in spans]
    out = {}
    for r in rows:
        cls, meth = row_names(r["name"])
        found = [i for i, h in enumerate(heads) if h and h[1] == meth and (cls is None or h[0] == cls)]
        if not found:
            found = [i for i, a in enumerate(args) if a and ((cls or meth) in a)]
        out[r["target_rva"]] = found
    return out


MACRO_LINE = re.compile(r"^[ \t]*([A-Z_][A-Z0-9_]*)[ \t]*\((.*)\)[ \t]*;?[ \t]*(?://[^\n]*)?$")


def macro_spans(text):
    """[(start, end, line)] of top-level macro invocations (`NAME(args)` on a
    line of its own, no body, at brace depth 0): sweep files generate one row
    per such line, and chunks() cannot see them (no `;`, no `{`), so it glues
    them onto the next item."""
    out, depth, i, n, line_start = [], 0, 0, len(text), 0
    while i < n:
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
            continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j + 1
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        elif c == "\n":
            if depth == 0:
                line = text[line_start:i]
                m = MACRO_LINE.match(line)
                if m and m.group(1) not in ("DEFINE", "IF", "ELSE") and "{" not in line:
                    out.append((line_start, i + 1, line))
            line_start = i + 1
        i += 1
    if depth == 0 and line_start < n:
        line = text[line_start:]
        m = MACRO_LINE.match(line)
        if m and "{" not in line:
            out.append((line_start, n, line))
    return out


def header_end(text):
    """Offset past the leading `// cl:` / `// stlport` lines: never part of a span."""
    at = 0
    for line in text.splitlines(keepends=True):
        if line.startswith(("// cl:", "// stlport")):
            at += len(line)
        else:
            break
    return at


def is_data_head(head):
    """A `{`-initialised object (`static const int t[] = {`), not a function body."""
    h = norm(head)
    return initialised(h) and not AGGREGATE.match(h)


def def_spans(text):
    """[(start, end, text, kind)] of every top-level definition ('def'), brace-
    initialised datum ('data') and macro invocation ('macro'), in file order,
    none overlapping: a macro line the chunker glued onto the head of a
    definition is split off it, and a macro line takes the comment lines
    directly above it (a row's evidence or marker) with it."""
    floor = header_end(text)
    macros = []
    for a, b, l in macro_spans(text):
        while a > floor:      # pull in the comment lines directly above
            prev = text.rfind("\n", 0, a - 1) + 1
            line = text[prev:a]
            if line.strip().startswith("//") and not line.startswith(("// cl:", "// stlport")) \
                    and not line.strip().startswith("// ----"):
                a = prev
            else:
                break
        macros.append((a, b, text[a:b]))
    out, pos = [], 0
    for kind, c in chunks(text):
        if kind != "def":
            continue
        at = text.find(c, pos)
        if at < 0:
            raise ValueError("definition text not found in its own file")
        end = at + len(c)
        pos = end
        at = max(at, floor)
        inside = [m for m in macros if at <= m[0] < end]
        if inside:
            at = max(m[1] for m in inside)     # the glued macro lines precede the body
            rest = norm(text[at:end])
            if not rest or (AGGREGATE.match(rest)
                            and not re.search(r"\)\s*(const)?\s*$", rest.split("{")[0].strip())):
                pos = end          # what the glue hid was an aggregate: a declaration, not a body
                continue
        body = text[at:end]
        if is_data_head(body.split("{")[0]):
            m = re.match(r"\s*;", text[end:])          # the datum's own `;` after the `}`
            if m:
                end += m.end()
            out.append((at, end, text[at:end], "data"))
        else:
            out.append((at, end, body, "def"))
    out.extend((a, b, l, "macro") for a, b, l in macros)
    out.sort()
    return out


# ---- file-scope data and brace blocks: definitions, never duplicated
DATA_PREFIX = re.compile(r"^(?:typedef|using|template|friend|class|struct|enum|union|static_assert|namespace)\b")


def data_decls(text):
    """[(start, end, text, ident, internal)] of file-scope object definitions
    among the `;`-terminated chunks (`int g = 0;`, `static int s;`, `Foo *p;`):
    a definition, so it may live in one file only. An initialized `extern`
    is also a definition. Prototypes, uninitialized externs, typedefs and
    type declarations are declarations and may be repeated."""
    out, pos = [], 0
    for kind, c in chunks(text):
        at = text.find(c, pos)
        if at < 0:
            continue
        pos = at + len(c)
        if kind != "decl":
            continue
        s = re.sub(r"__declspec\s*\([^)]*\)", " ", norm(c)).strip()
        if not s.endswith(";") or DATA_PREFIX.match(s) or s.startswith("#"):
            continue
        depth, eq, paren = 0, -1, False
        for i, ch in enumerate(s):
            if ch in "([{":
                depth += 1
                if ch == "(" and depth == 1 and eq < 0:
                    paren = True
            elif ch in ")]}":
                depth -= 1
            elif ch == "=" and depth == 0 and eq < 0 and s[i + 1:i + 2] != "=":
                eq = i
        external = bool(re.match(r"^extern\b", s))
        if external and eq < 0:
            continue            # an extern without an initializer is only a declaration
        if paren and not re.search(r"\(\s*\*\s*[A-Za-z_]\w*\s*\)", s[:eq if eq >= 0 else len(s)]):
            continue            # a prototype (or a function-pointer declarator, which is data)
        declarator = s[:eq] if eq >= 0 else s[:-1]
        m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", declarator.strip()) \
            or re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", declarator)
        if not m or m.group(1) in ("return", "goto", "break", "continue"):
            continue
        tokens = declarator.split()
        internal = not external and (tokens[0] == "static" or
                                     ("const" in tokens[:-1] and "*" not in declarator and "&" not in declarator))
        out.append((at, at + len(c), c, m.group(1), internal))
    return out


def brace_blocks(text):
    """[(start, end, text)] of `namespace X { ... }` / `extern "C" { ... }` blocks
    that define a function or an object inside: a carve cannot place those."""
    out, pos = [], 0
    for kind, c in chunks(text):
        at = text.find(c, pos)
        if at < 0:
            continue
        pos = at + len(c)
        s = norm(c)
        if kind == "decl" and re.match(r"^(namespace\b|extern\s*\"C\")", s) and "{" in s:
            inner = s[s.index("{") + 1:s.rindex("}")]
            flat, depth = [], 0
            for ch in inner:          # inner text with nested braces blanked
                depth += ch == "{"
                flat.append(ch if depth == 0 else " ")
                depth -= ch == "}"
            flat = "".join(flat)
            if re.search(r"\)\s*(?:const\s*)?\{", inner) or re.search(r"(?<![=!<>])=(?!=)", flat):
                out.append((at, at + len(c), c))
    return out


def code_only(text):
    """Text with comments blanked and string/char literal contents removed."""
    t = strip(text)
    return re.sub(r"\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", "\"\"", t)


def names_used(ident, text):
    return re.search(r"(?<![\w.>])%s\b" % re.escape(ident), code_only(text)) is not None


def cut(text, spans):
    """`text` without the given (start, end) spans."""
    out, pos = [], 0
    for start, end in sorted(spans):
        out.append(text[pos:start])
        pos = end
    out.append(text[pos:])
    return "".join(out)


class Carve:
    """The two texts a carve produces, or why it cannot be made.

    donor/residual: the texts. copies: helper span indices copied to the donor.
    data_moved: identifiers of file-scope objects that left for the donor.
    externs: identifiers the donor now declares `extern` (defined in the residual).
    refused: a reason, else None."""

    def __init__(self, donor=None, residual=None, copies=(), data_moved=(), externs=(), refused=None):
        self.donor, self.residual, self.copies = donor, residual, list(copies)
        self.data_moved, self.externs, self.refused = list(data_moved), list(externs), refused

    def __iter__(self):           # (donor, residual) for callers that only want the texts
        return iter((self.donor, self.residual))


def carve(text, take, rowed=frozenset(), data_rowed=frozenset()):
    """The definitions at span indices `take` leave the file.

    Both texts keep every preprocessor line, declaration and comment, so each
    still compiles against the same view. Definitions are never duplicated:
      * a file-local helper function with internal linkage that is not a ledger
        row (`rowed`: span indices any row of the file identifies) travels as a
        copy when a carved body calls it, transitively; one with external
        linkage never does;
      * a file-scope object definition goes where it is used: with the carved
        bodies when only they use it, else it stays; an external one used on
        both sides stays and the donor declares it `extern`; an internal one
        used on both sides is duplicated when it is `const` and no data row
        (`data_rowed`: identifiers data_rows.csv binds to this file) owns it,
        and otherwise refuses the carve (two objects where retail has one);
      * a `namespace {}` / `extern "C" {}` block defining anything refuses it."""
    spans = def_spans(text)
    take = set(take)
    stay_all = set(range(len(spans))) - take
    carved_text = "\n".join(spans[i][2] for i in sorted(take) if spans[i][3] != "data")
    copies = set()
    changed = True
    while changed:
        changed = False
        for i in sorted(stay_all - copies):
            start, end, body, kind = spans[i]
            if kind != "def" or i in rowed:
                continue
            hn = head_names(body)
            if hn and INTERNAL.search(norm(body.split("{")[0])) \
                    and re.search(r"(?<![\w.>])%s\s*\(" % re.escape(hn[1]), code_only(carved_text)):
                copies.add(i)
                carved_text += "\n" + body
                changed = True
    leaving = take | copies
    stay_text = "\n".join(spans[i][2] for i in sorted(stay_all) if spans[i][3] != "data")   # copies stay too
    blocks = brace_blocks(text)
    if blocks:
        return Carve(refused="a namespace/extern \"C\" block defines something: carve not supported")
    donor_cuts = [(a, b) for i, (a, b, _, _) in enumerate(spans) if i not in leaving]
    residual_cuts = [(a, b) for i, (a, b, _, _) in enumerate(spans) if i in take]
    data_moved, externs, extern_lines = [], [], []
    datums = list(data_decls(text))
    for i, (a, b, c, kind) in enumerate(spans):      # `static const int t[] = {...};` spans
        if kind == "data":
            head = re.sub(r"__declspec\s*\([^)]*\)", " ", norm(c.split("=")[0]))
            m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", head.strip())
            if m:
                toks = head.split()
                datums.append((a, b, c, m.group(1), toks[0] == "static" or ("const" in toks[:-1] and "*" not in head)))
    donor_cuts = [x for x in donor_cuts if not any(x == (a, b) for a, b, _, k in spans if k == "data")]
    for a, b, c, ident, internal in datums:
        used_out = names_used(ident, carved_text)
        used_in = names_used(ident, stay_text)
        if used_out and used_in:
            if internal:
                const = re.search(r"\bconst\b", norm(c).split("=")[0]) and ident not in data_rowed
                if const:
                    continue        # a read-only internal datum: both files keep their own copy
                return Carve(refused=f"file-scope static `{ident}` is used by carved and staying bodies")
            externs.append(ident)
            decl = re.sub(r"\s*=.*$", "", norm(c).rstrip(";"), flags=re.S)
            if not re.match(r"^extern\b", decl):
                decl = "extern " + decl
            extern_lines.append((b, decl + ";"))
            donor_cuts.append((a, b))
        elif used_out:
            data_moved.append(ident)
            residual_cuts.append((a, b))
        else:
            donor_cuts.append((a, b))
    donor = cut(text, donor_cuts)
    if extern_lines:   # the extern declaration stands where the definition stood
        pieces, pos = [], 0
        for a, b in sorted(donor_cuts):
            pieces.append(text[pos:a])
            line = next((l for e, l in extern_lines if e == b), None)
            if line:
                pieces.append(line + "\n")
            pos = b
        pieces.append(text[pos:])
        donor = "".join(pieces)
    residual = cut(text, residual_cuts)
    return Carve(donor, residual, sorted(copies), data_moved, externs)


INCLUDE = re.compile(r'^([ \t]*#[ \t]*include[ \t]*)"([^"\n]+)"', re.M)


def relocate_includes(text, from_dir, to_dir, root=ROOT):
    """`#include "..."` lines that resolve relative to `from_dir` (the compiler
    searches the including file's directory first) rewritten to resolve from
    `to_dir`. A quoted include that does not exist beside the source is found on
    the -I paths and is left alone."""
    if posixpath.normpath(from_dir) == posixpath.normpath(to_dir):
        return text

    def fix(m):
        target = ci_path(root, posixpath.normpath(posixpath.join(from_dir, m.group(2).replace("\\", "/"))))
        if target is None:
            return m.group(0)
        return m.group(1) + '"' + posixpath.relpath(target, to_dir) + '"'
    return INCLUDE.sub(fix, text)


def ci_path(root, rel):
    """`rel` in the tree's own spelling, matched case-insensitively (the Wine
    compiler resolves includes that way); None when nothing matches."""
    cur = Path(root)
    out = []
    for part in rel.split("/"):
        if part in ("", "."):
            continue
        try:
            names = os.listdir(cur)
        except OSError:
            return None
        hit = part if part in names else next((n for n in names if n.lower() == part.lower()), None)
        if hit is None:
            return None
        out.append(hit)
        cur = cur / hit
    return "/".join(out)


def file_rows(path):
    if "by_file" not in _CACHE:
        donors("", [])   # fills by_file / assigned
    return [r for r in _CACHE["by_file"].get(path, [])
            if r["status"] == "matched" and "gen-alias" not in (r["notes"] or "")]


def companions(rows, parents):
    """Rows that are emitted with a parent in `parents` and live where it lives:
    EH funclets by name (`__ehhandler$X`), generated funclets (`gen-funclet;
    parent=X` in notes) and the deleting destructors of a carved destructor."""
    dtors = {m.group(1): p for p in parents if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", p))}
    return [r for r in rows if r["name"] not in parents and (parent_of(r, dtors) in parents)]


def debt_keys(path):
    """Identifiers of data-identity debt keyed to `path` (a carved body naming one would move the debt)."""
    out = set()
    reg = ROOT / "reverse/data_check_baseline.txt"
    if reg.exists():
        for line in reg.read_text(encoding="utf-8", errors="replace").splitlines():
            parts = line.split("\t")
            if len(parts) >= 3 and parts[0] == path:
                m = re.match(r"^\?([A-Za-z_]\w*)@", parts[2])
                out.add(m.group(1) if m else parts[2].lstrip("_"))
    return out


def breakdown(path):
    """{approved TU (the map's spelling): rows} of a file's matched rows, plus
    unplaced ones under ''; an EH funclet counts with its parent."""
    approved = {int(r["rva"], 16): r["tu"] for r in map_rows()
                if r["confidence"] == "approved" and r["kind"].startswith("code") and r["tu"]}
    rows = file_rows(path)
    home = {r["name"]: approved.get(int(r["target_rva"], 16), "") for r in rows}
    dtors = {m.group(1): r["name"] for r in rows if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
    out = collections.defaultdict(list)
    for r in rows:
        p = parent_of(r, dtors)
        out[home[p] if p and p in home else home[r["name"]]].append(r)
    return out


def split(path, tu, dry_run=False, claim=True):
    report = {"file": path, "tu": tu}
    rows = file_rows(path)
    if not rows:
        report["blocked"] = "no matched rows in that file"
        return report
    why = refusal(path, rows)
    if why and not why.startswith("keyed in a protected"):
        report["blocked"] = "file cannot be carved: " + why
        return report
    original_bytes = (ROOT / path).read_bytes()
    text0 = original_bytes.decode("utf-8-sig", errors="replace").replace("\r\n", "\n").replace("\r", "\n")
    if "__FILE__" in strip(text0):          # rename_files reports only its first reason
        report["blocked"] = "file cannot be carved: expands __FILE__ (the path reaches its bytes)"
        return report
    inc = included_by(path)
    if inc:
        report["blocked"] = "file cannot be carved: #included by " + ", ".join(inc[:3])
        return report
    groups = breakdown(path)
    tu = next((k for k in groups if k.lower() == tu.lower()), tu)
    dtors_all = {m.group(1): r["name"] for r in rows if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
    tu_rows = [r for r in groups.get(tu, []) if not parent_of(r, dtors_all)]
    if not tu_rows:
        report["blocked"] = "no row of that file is approved for that TU"
        return report
    if len(groups.get(tu, [])) == len(rows):
        report["blocked"] = "every row is this TU's (funclets included): use --merge"
        return report
    text = text0
    spans = def_spans(text)
    all_ids = identify(rows, spans)                       # every row of the file, not just this TU's
    rowed = {i for v in all_ids.values() for i in v}
    by_span = collections.defaultdict(list)                # span -> rows of the file it defines
    for r in rows:
        if len(all_ids[r["target_rva"]]) == 1:
            by_span[all_ids[r["target_rva"]][0]].append(r)
    ids = {r["target_rva"]: all_ids[r["target_rva"]] for r in tu_rows}
    debt = debt_keys(path)
    want = {r["target_rva"] for r in tu_rows}
    take, carved, refused = set(), [], {}
    for r in tu_rows:
        cands = ids[r["target_rva"]]
        if len(cands) != 1:
            refused[r["target_rva"]] = "no definition spells its name" if not cands else \
                f"{len(cands)} definitions spell its name"
            continue
        body = spans[cands[0]][2]
        others = [x for x in by_span[cands[0]] if x["target_rva"] not in want
                  and not (FUNCLET.match(x["name"]) or DELETING.match(x["name"]))]
        if others:          # one template/macro definition producing rows the map places elsewhere
            refused[r["target_rva"]] = "its definition also produces rows of another TU: " + others[0]["target_rva"]
            continue
        hit = [d for d in debt if names_used(d, body)]
        if hit:
            refused[r["target_rva"]] = "carries data-identity debt keyed to this file: " + ", ".join(sorted(hit)[:3])
            continue
        take.add(cands[0])
        carved.append(r)
    report.update(candidates=len(tu_rows), carved=[r["target_rva"] for r in carved], refused_rows=refused)
    if not carved:
        report["blocked"] = "no row could be carved"
        return report
    carved += companions(rows, {r["name"] for r in carved})
    keep = [r for r in rows if r not in carved]
    if not keep:
        report["blocked"] = "no row would remain in the file: it is a whole donor, use --merge"
        return report
    data_rowed = data_rowed_idents(path)
    cv = carve(text, take, rowed, data_rowed)
    if cv.refused:
        report["blocked"] = cv.refused
        return report
    donor_text, residual = cv.donor, cv.residual
    report.update(copies=[head_names(spans[i][2]) for i in cv.copies], data_moved=cv.data_moved, externs=cv.externs)
    moved_hatches = hatch_move(path, text, residual, tu, donor_text)
    if moved_hatches is None:
        report["blocked"] = "an escape-hatch count would grow (hatch_counters rule 3): a copied helper or datum carries one"
        return report
    report["hatches_move"] = bool(moved_hatches)
    donor_text = relocate_includes(donor_text, posixpath.dirname(path), posixpath.dirname(tu))
    # the residual first: it is the cheaper compile and the commoner failure
    v = Verifier(path)
    got = v.matched(residual, keep) if keep else set()
    lost = sorted({r["target_rva"] for r in keep} - (got or set()))
    report["residual_keeps"] = len(keep) - len(lost)
    if lost:
        report["residual_loses"] = lost
        report["blocked"] = ("the residual no longer compiles: " + " | ".join(v.errors)[:300]) if got is None \
            else "the residual loses matched rows (flag region or a shared helper)"
        return report
    # every carved row must match on its own under the flags the TU will carry;
    # a row that only matches under the mixed file's own flags stays behind
    (ROOT / tu).parent.mkdir(parents=True, exist_ok=True)
    vt = Verifier(tu)
    alone = vt.matched(donor_text, carved)
    if alone is None:
        report["blocked"] = "the carved bodies do not compile beside the TU: " + " | ".join(vt.errors)[:300]
        return report
    behind = [r for r in carved if r["target_rva"] not in alone]
    report["alone"] = f"{len(carved) - len(behind)}/{len(carved)} carved rows match beside the TU under its flags"
    if behind:
        report["flag_bound"] = {r["target_rva"]: "matches only under the file's own flags" for r in behind}
        parents = {r["name"] for r in behind} | {m.group(1) for r in behind if (m := FUNCLET.match(r["name"]))}
        behind = [r for r in carved if r["name"] in parents or (m := FUNCLET.match(r["name"])) and m.group(1) in parents]
        carved = [r for r in carved if r not in behind]
        take = {ids[r["target_rva"]][0] for r in carved if r["target_rva"] in ids and ids[r["target_rva"]]}
        if not take:
            report["blocked"] = "no carved row matches under the TU's flags"
            return report
        keep = [r for r in rows if r not in carved]
        if not keep:
            report["blocked"] = "no row would remain in the file after the flag-bound rows stayed: use --merge"
            return report
        cv = carve(text, take, rowed, data_rowed)
        if cv.refused:
            report["blocked"] = cv.refused
            return report
        donor_text, residual = cv.donor, cv.residual
        report.update(copies=[head_names(spans[i][2]) for i in cv.copies], data_moved=cv.data_moved, externs=cv.externs)
        moved_hatches = hatch_move(path, text, residual, tu, donor_text)
        if moved_hatches is None:
            report["blocked"] = "an escape-hatch count would grow after the flag-bound rows stayed"
            return report
        report["hatches_move"] = bool(moved_hatches)
        donor_text = relocate_includes(donor_text, posixpath.dirname(path), posixpath.dirname(tu))
        report["carved"] = [r["target_rva"] for r in carved]
        v = Verifier(path)
        got = v.matched(residual, keep) if keep else set()
        lost = sorted({r["target_rva"] for r in keep} - (got or set()))
        report["residual_keeps"] = len(keep) - len(lost)
        if lost:
            report["residual_loses"] = lost
            report["blocked"] = "the residual loses matched rows after the flag-bound rows stayed"
            return report
    sk = skeleton(tu)
    don = {path: carved}
    own = file_rows(tu) if (ROOT / tu).exists() else []
    if own:
        assigned = _CACHE["assigned"]
        own_home = {r["name"]: assigned.get(int(r["target_rva"], 16)) for r in own}
        own_dtors = {m.group(1): r["name"] for r in own if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}

        def placed(r):   # a companion row lives where its parent lives
            p = parent_of(r, own_dtors)
            return own_home[p] if p and p in own_home else assigned.get(int(r["target_rva"], 16))
        elsewhere = collections.Counter((placed(r) or "(unplaced)").split("/")[-1]
                                        for r in own if placed(r) != tu.lower())
        if elsewhere:
            report["blocked"] = ("TU path exists and holds rows the map does not place there (split it first): "
                                 + ", ".join(f"{k} {n}" for k, n in elsewhere.most_common()))
            return report
        don[tu] = own
    report.update(approved=len(sk), accepted=[], rejected={})
    texts = {path: donor_text}
    guard = SplitLinkGuard(tu, path, residual, v.obj, [r["target_rva"] for r in carved],
                           data_moved=cv.data_moved, root=ROOT, expected_source=original_bytes)

    def applier(tu_, acc, text_):
        return apply_split(tu_, text_, path, residual, [r["target_rva"] for r in carved], report["hatches_move"],
                           data_moved=cv.data_moved)

    if claim and not dry_run:
        held = claim_scope(tu, {path: carved})
        if held:
            claims.release(claim_keys(tu, {path: carved}))
            report["blocked"] = held_message(held)
            return report
        report = _merge(tu, sk, don, report, dry_run, texts=texts, applier=applier, guard=guard)
        if "blocked" in report:
            claims.release(claim_keys(tu, {path: carved}))
    else:
        report = _merge(tu, sk, don, report, dry_run, texts=texts, applier=applier, guard=guard)
    if path not in report.get("accepted", []):
        report.setdefault("blocked", "the carved bodies do not verify in the TU: "
                          + str(report.get("rejected", {}).get(path, ""))[:300])
    elif not dry_run:
        report["subject"] = (f"Split {len(carved)} rows of {posixpath.basename(path)} into "
                             f"{posixpath.basename(tu)} (tu_map approved TU, retail order)")
        if report["hatches_move"]:
            report["trailer"] = (f"Verifier-Change: tu_skeleton --split moved escape-hatch counts from {path} to {tu}"
                                 " (totals kept; hatch_counters --update)")
    return report


def data_rowed_idents(path):
    """Identifiers of the data rows reverse/data_rows.csv binds to `path`."""
    dr = ROOT / "reverse/data_rows.csv"
    if not dr.exists():
        return frozenset()
    out = set()
    for row in csv.DictReader(io.StringIO(dr.read_text(encoding="utf-8", errors="replace"), newline="")):
        if row.get("source") == path:
            m = re.match(r"^\?([A-Za-z_]\w*)@@", row["name"])
            out.add(m.group(1) if m else row["name"].lstrip("_"))
    return frozenset(out)


def included_by(path):
    """Files that `#include` this source (its bodies would be compiled twice)."""
    base = posixpath.basename(path)
    try:
        out = subprocess.run(["git", "grep", "-l", "-i", "-E", r'^\s*#\s*include\s*"([^"]*/)?' + re.escape(base) + '"',
                              "--", "Code", "reference/shims"], cwd=ROOT, capture_output=True, text=True).stdout.split()
    except OSError:
        return []
    return [f for f in out if f != path]


def hatch_move(path, before, residual, tu, donor):
    """{(hatch, token): count} a carve moves from `path` to `tu`, or None when any
    per-(hatch, token) total over the two files would grow (hatch_counters rule
    3 allows a move, never growth). Empty when nothing moves."""
    try:
        import hatch_counters as H
    except ImportError:
        return {}
    tu_before = (ROOT / tu).read_text(encoding="utf-8", errors="replace") if (ROOT / tu).exists() else ""

    def totals(counter):
        out = collections.Counter()
        for (hatch, _p, token), n in counter.items():
            out[(hatch, token)] += n
        return out
    old = totals(H.scan(path, before)) + totals(H.scan(tu, tu_before))
    new = totals(H.scan(path, residual)) + totals(H.scan(tu, donor))
    if any(new[k] > old.get(k, 0) for k in new):
        return None
    moved = totals(H.scan(tu, donor)) - totals(H.scan(tu, tu_before))
    return dict(moved)


def repoint_rows(raw, label, keycol, keys, column, old, new):
    """`raw` with `column` changed from `old` to `new` on the records whose `keycol`
    is in `keys` (hex, case-insensitive); returns (new_raw, count). Other bytes kept."""
    import ledger_io
    ledger_io.lf_terminator(raw, label)
    records = ledger_io.split_records(raw)
    header = ledger_io.fields(records[0][0]) if records else []
    if keycol not in header or column not in header:
        raise rename.Refusal(f"{label} lacks {keycol!r} or {column!r}")
    ki, ci = header.index(keycol), header.index(column)
    hexkeys = all(k.lower().startswith("0x") for k in keys)
    want = {k.lower() for k in keys} if hexkeys else set(keys)
    out, count = [records[0][0] + records[0][1]], 0
    for payload, term in records[1:]:
        text = payload.decode("utf-8")
        spans = rename.field_spans(text)
        if len(spans) > max(ki, ci):
            key = text[spans[ki][0]:spans[ki][1]].strip('"')
            key = key.lower() if hexkeys else key
            start, end = spans[ci]
            value = text[start:end]
            if key in want and value in (old, f'"{old}"'):
                payload = (text[:start] + value.replace(old, new) + text[end:]).encode("utf-8")
                count += 1
        out.append(payload + term)
    return b"".join(out), count


ROW_KEYED = (("reverse/functions.csv", "target_rva"), ("reverse/tu_map.csv", "rva"),
             ("reverse/body_owners.csv", "target_rva"))


def ensure_sources_cfg(raw, tu):
    lines = raw.decode("utf-8").splitlines(keepends=True)
    entry = re.compile(r"INPUT\s*\+=\s*(\S+)\s*")
    if any((m := entry.fullmatch(l)) and m.group(1) == tu for l in lines):
        return raw, 0
    if lines and not lines[-1].endswith("\n"):
        lines[-1] += "\n"
    return "".join(lines + [f"INPUT += {tu}\n"]).encode("utf-8"), 1


def data_row_names(raw, idents):
    """data_rows.csv `name` values whose identifier is in `idents`."""
    out = set()
    for row in csv.DictReader(io.StringIO(raw.decode("utf-8"), newline="")):
        m = re.match(r"^\?([A-Za-z_]\w*)@@", row["name"])
        ident = m.group(1) if m else row["name"].lstrip("_")
        if ident in idents:
            out.add(row["name"])
    return out


def apply_split(tu, text, path, residual, rvas, hatches, root=ROOT, data_moved=()):
    moved = {}
    if hatches:
        dirty = subprocess.run(["git", "status", "--porcelain", "--untracked-files=no"], cwd=root,
                               capture_output=True, text=True).stdout.splitlines()
        others = [l for l in dirty if l[3:] not in (tu, path)]
        if others:
            raise SystemExit("tu_skeleton: the hatch register is rewritten from the whole tree; commit or stash "
                             "the other modified files first: " + ", ".join(l[3:] for l in others[:5]))
    for rel, keycol in ROW_KEYED:
        p = Path(root) / rel
        if not p.exists():
            continue
        raw, n = repoint_rows(p.read_bytes(), rel, keycol, rvas, "source", path, tu)
        if n:
            p.write_bytes(raw)
            moved[rel] = n
    dr = Path(root) / "reverse/data_rows.csv"
    if data_moved and dr.exists():
        raw = dr.read_bytes()
        names = data_row_names(raw, set(data_moved))
        if names:
            raw, n = repoint_rows(raw, "reverse/data_rows.csv", "name", names, "source", path, tu)
            if n:
                dr.write_bytes(raw)
                moved["reverse/data_rows.csv"] = n
    cfg = Path(root) / rename.SOURCES_CFG
    if cfg.exists():
        raw, n = ensure_sources_cfg(cfg.read_bytes(), tu)
        if n:
            cfg.write_bytes(raw)
            moved[rename.SOURCES_CFG] = n
    (Path(root) / tu).write_text(text, encoding="utf-8", newline="\n")
    (Path(root) / path).write_text(residual, encoding="utf-8", newline="\n")
    subprocess.run(["git", "add", "--", tu, path, *moved], cwd=root, check=True)
    if hatches:   # a body with a hatch moved between units: a total-keeping move
        subprocess.run([sys.executable, "tools/hatch_counters.py", "--update"], cwd=root, check=True)
        subprocess.run(["git", "add", "--", "reverse/hatch_baseline.tsv"], cwd=root, check=True)
        moved["reverse/hatch_baseline.tsv"] = "updated"
    _CACHE.clear()
    return moved


# ---------------------------------------------------------------- protected registers
# How each protected path-keyed register (rename.PROTECTED_PATH_KEYED) names a unit, and
# so how a merge carries an absorbed donor's keys to the TU in the merge commit.
KEYED_LINES = ("reverse/code_identity_baseline.tsv",   # source<TAB>row<TAB>symbol<TAB>target<TAB>class
               "reverse/data_check_baseline.txt")      # source<TAB>check<TAB>symbol<TAB>address
HATCH_REGISTER = "reverse/hatch_baseline.tsv"          # hatch<TAB>path<TAB>token<TAB>count: --update
OVERRIDES = "reverse/flag_overrides.csv"               # source,flags,rows,default_lost,reason
DATA_LEDGER = "reverse/data_ledger.csv"                # source column; names cells name@source
RETIRE = {"reverse/code_identity_baseline.tsv": "identity", "reverse/data_check_baseline.txt": "data"}


def _eol(raw):
    return "\r\n" if b"\r\n" in raw else "\n"


def carry_lines(raw, gone, tu):
    """(raw, moved, collapsed): every source<TAB>key line of a gone donor re-keyed to
    the TU, each key once. `collapsed` lists the donor lines whose key the register
    already held under the TU: no transfer can show for them (verify-removed counts
    a key added under the TU), so each needs the printed per-key Debt-Retired line."""
    eol = _eol(raw)
    lines = raw.decode("utf-8").split(eol)
    held = set(lines)
    out, seen, moved, collapsed = [], set(), 0, []
    for line in lines:
        source, sep, key = line.partition("\t")
        if not sep or line.startswith("#") or source not in gone:
            out.append(line)
            continue
        moved += 1
        new = f"{tu}\t{key}"
        if new in held:
            collapsed.append(line)
        elif new not in seen:
            seen.add(new)
            out.append(new)
    return eol.join(out).encode("utf-8"), moved, collapsed


def carry_overrides(raw, gone, tu, flags):
    """(raw, moved): the absorbed donors' and the TU's flag_overrides.csv entries as
    one TU entry spelling FLAGS, the flags the merge was verified under, with their
    summed row counts (the register's totals are kept)."""
    eol = _eol(raw)
    reader = csv.DictReader(io.StringIO(raw.decode("utf-8"), newline=""))
    rows = list(reader)
    mine = [r for r in rows if r["source"] in gone or r["source"] == tu]
    moved = sum(r["source"] in gone for r in mine)
    if not moved:
        return raw, 0
    if any(r["flags"] != flags for r in mine):
        raise ValueError(f"{OVERRIDES}: carried entries disagree with the verified flags '{flags}'")
    reasons = {r["reason"] for r in mine}
    entry = {"source": tu, "flags": flags,
             "rows": str(sum(int(r["rows"] or 0) for r in mine)),
             "default_lost": str(sum(int(r["default_lost"] or 0) for r in mine)),
             "reason": reasons.pop() if len(reasons) == 1 else "region default loses rows"}
    out = io.StringIO()
    writer = csv.DictWriter(out, fieldnames=reader.fieldnames, lineterminator=eol)
    writer.writeheader()
    writer.writerows(sorted([r for r in rows if r not in mine] + [entry], key=lambda r: r["source"]))
    return out.getvalue().encode("utf-8"), moved


def carry_data_ledger(raw, gone, tu):
    """(raw, moved): data_ledger.csv's `source` cells and `name@source` names of the
    gone donors spell the TU (the definitions now live there); other bytes kept."""
    eol = _eol(raw)
    lines = raw.decode("utf-8").split(eol)
    header = next(csv.reader([lines[0]]))
    at_source, at_names = header.index("source"), header.index("names")
    moved = 0
    for i in range(1, len(lines)):
        if not any(g in lines[i] for g in gone):
            continue
        cells = next(csv.reader([lines[i]]))
        before = list(cells)
        if cells[at_source] in gone:
            cells[at_source] = tu
        names = []
        for n in cells[at_names].split(";") if cells[at_names] else []:
            name, sep, where = n.rpartition("@")
            names.append(f"{name}@{tu}" if sep and where in gone else n)
        cells[at_names] = ";".join(names)
        if cells != before:
            out = io.StringIO()
            csv.writer(out, lineterminator="").writerow(cells)
            lines[i] = out.getvalue()
            moved += 1
    return eol.join(lines).encode("utf-8"), moved


def vanished(raws, gone):
    """[(register, line)] of register lines still naming a deleted donor."""
    out = []
    for rel, raw in sorted(raws.items()):
        for line in raw.decode("utf-8", errors="replace").splitlines():
            if not line.startswith("#") and {t.strip('"') for t in re.split(r"[\t,;@]", line)} & gone:
                out.append((rel, line))
    return out


def hatch_growth(tu, acc, texts, text):
    """(hatch, token) keys whose occurrences in the merged TU exceed the absorbed files'."""
    import hatch_counters as H

    def totals(path, t):
        out = collections.Counter()
        for (hatch, _p, token), n in H.scan(path, t).items():
            out[(hatch, token)] += n
        return out
    before = collections.Counter()
    for f in acc:
        before += totals(f, texts[f])
    after = totals(tu, text)
    return sorted(k for k in after if after[k] > before[k]), bool(before or after)


class Carry:
    """What a merge does to the protected path-keyed registers, decided before
    anything is written: new register bytes, counts, refusals."""

    def __init__(self, root, tu, acc, texts, text, flags=None):
        self.root, self.tu = Path(root), tu
        self.gone = {f for f in acc if f != tu}
        self.raws, self.new, self.moved, self.collapsed, self.problems = {}, {}, {}, [], []
        for rel in rename.PROTECTED_PATH_KEYED:
            p = self.root / rel
            if p.exists():
                self.raws[rel] = p.read_bytes()
        for rel in KEYED_LINES:
            if rel in self.raws:
                raw, n, collapsed = carry_lines(self.raws[rel], self.gone, tu)
                self.record(rel, raw, n)
                self.collapsed += [(rel, line) for line in collapsed]
        if OVERRIDES in self.raws:
            try:
                raw, n = carry_overrides(self.raws[OVERRIDES], self.gone, tu, flags)
                self.record(OVERRIDES, raw, n)
            except ValueError as e:
                self.problems.append(str(e))
        if DATA_LEDGER in self.raws:
            self.record(DATA_LEDGER, *carry_data_ledger(self.raws[DATA_LEDGER], self.gone, tu))
        self.hatch = False
        if HATCH_REGISTER in self.raws:
            grown, scanned = hatch_growth(tu, acc, texts, text)
            if grown:
                self.problems.append("the merged TU holds more escape-hatch occurrences than its donors: "
                                     + ", ".join(f"{h} {t}" for h, t in grown[:5]))
            keyed = {line.split("\t")[1] for line in self.raws[HATCH_REGISTER].decode("utf-8").splitlines()
                     if line.count("\t") >= 3 and not line.startswith("#")}
            self.hatch = scanned or bool(keyed & set(acc))
            if self.hatch:
                self.moved[HATCH_REGISTER] = "hatch_counters --update"
        # hatch_counters --update rescans the staged tree, so a deleted donor's lines go
        left = {rel: raw for rel, raw in self.after().items() if not (rel == HATCH_REGISTER and self.hatch)}
        for rel, line in vanished(left, self.gone):
            self.problems.append(f"{rel} would still key a deleted donor: {line[:160]}")

    def record(self, rel, raw, n):
        if n:
            self.new[rel], self.moved[rel] = raw, n

    def after(self):
        return {rel: self.new.get(rel, raw) for rel, raw in self.raws.items()}

    def trailer(self):
        return (f"Verifier-Change: tu_skeleton --merge carried the protected-register keys of "
                f"{len(self.gone)} absorbed donor(s) to {self.tu} (transfer; totals kept)") if self.moved else None

    def retired(self):
        """The per-key Debt-Retired lines a collapsed key needs (repair_queue's exact form)."""
        return [f"Debt-Retired: {line} {line.split(chr(9), 1)[0]} merged into {self.tu}, which already "
                "holds this key" for _rel, line in self.collapsed]

    def follow_up(self):
        out = [f"after committing the merge and ./build.sh {self.tu}: python3 tools/repair_queue.py retire "
               f"{kind} {self.tu} (retires only keys the owner's fresh verdict no longer finds)"
               for rel, kind in RETIRE.items() if rel in self.moved]
        if OVERRIDES in self.moved:
            out.append(f"python3 tools/flag_defaults.py propose {self.tu} (drops the override when the region "
                       "default keeps every row)")
        return out

    def report(self):
        out = {}
        if self.moved:
            out["carried"] = dict(self.moved)
            out["trailer"] = self.trailer()
        if self.collapsed:
            out["debt-retired"] = self.retired()
        if self.follow_up():
            out["follow-up"] = self.follow_up()
        return out

    def write(self):
        for rel, raw in self.new.items():
            (self.root / rel).write_bytes(raw)
        return sorted(self.new)


def dirty_others(root, allowed):
    lines = subprocess.run(["git", "status", "--porcelain", "--untracked-files=no", "--ignore-submodules"],
                           cwd=root, capture_output=True, text=True).stdout.splitlines()
    return [l[3:] for l in lines if l[3:] not in allowed]


# ---------------------------------------------------------------- apply
def claim_keys(tu, don):
    keys = [f"file:{tu}"] + [f"file:{f}" for f in sorted(don) if f != tu]
    return keys + sorted({r["target_rva"] for rows in don.values() for r in rows})


class Held(list):
    """claim_scope's refused keys. `unconfirmed` names those whose claim push failed while no
    other worker held them (origin refused the push, e.g. no write access, or never confirmed
    it); `unavailable` is set when origin could not be read at all."""
    unconfirmed = ()
    unavailable = ""


def claim_scope(tu, don, root=ROOT):
    """Claim the TU, its donors and their rows; [] or the keys we did not get (a Held list)."""
    keys = claim_keys(tu, don)
    try:
        res = claims.claim(keys, note=f"tu_skeleton {tu}", root=root)
    except claims.ClaimsUnavailable as e:
        held = Held([f"(claims unavailable: {e})"])
        held.unavailable = str(e)
        return held
    if res.refused:
        names = {claims.key_of(k): k for k in keys}
        held = Held(str(names.get(k, k)) for k in res.refused)
        held.unconfirmed = [str(names.get(k, k)) for k in getattr(res, "unconfirmed", ())]
        return held
    return []


def held_message(held):
    """The `blocked` text for a scope claim_scope did not get. Only keys a peer holds are
    "held by another worker"; a claim push origin refused or never confirmed, with nobody
    holding the keys, is reported as such (a token without write access read as a peer's
    claim, 2026-10-29)."""
    if getattr(held, "unavailable", ""):
        return "claims unavailable (origin could not be read): " + held.unavailable
    unconfirmed = set(getattr(held, "unconfirmed", ()))
    others = [k for k in held if k not in unconfirmed]
    if others:
        return "held by another worker: " + ", ".join(others[:5])
    return ("claim push failed (origin refused or did not confirm it; no other worker holds these "
            "keys; check push access to origin): " + ", ".join(list(held)[:5]))


def repoint_sources_cfg(raw, gone, tu):
    """INPUT lines of absorbed donors become one line for the TU."""
    lines = raw.decode("utf-8").splitlines(keepends=True)
    entry = re.compile(r"INPUT\s*\+=\s*(\S+)\s*")
    have = any((m := entry.fullmatch(l)) and m.group(1) == tu for l in lines)
    out, count = [], 0
    for line in lines:
        m = entry.fullmatch(line)
        if m and m.group(1) in gone:
            count += 1
            if not have:
                out.append(line.replace(m.group(1), tu))
                have = True
            continue
        out.append(line)
    return "".join(out).encode("utf-8"), count


def repoint_fold_proofs(raw, gone, tu):
    """Move exact fold-proof source tokens, preserving pin identities and prose.

    Changed notes still go through normal pin admission, which recompiles the
    proof source and checks bytes and relocations at its new path.
    """
    from pin_admission import FOLD_PROOF_RE
    rename.ledger_io.lf_terminator(raw, "reverse/symbols.csv")
    records = rename.ledger_io.split_records(raw)
    header = rename.ledger_io.fields(records[0][0]) if records else []
    if "notes" not in header:
        raise rename.Refusal("reverse/symbols.csv has no 'notes' column")
    index, gone = header.index("notes"), set(gone)
    out, count = [records[0][0] + records[0][1]], 0
    for payload, term in records[1:]:
        text = payload.decode("utf-8")
        spans = rename.field_spans(text)
        if len(spans) > index:
            start, end = spans[index]
            field = text[start:end]
            quoted = field.startswith('"') and field.endswith('"')
            notes = field[1:-1].replace('""', '"') if quoted else field

            def replace(match):
                if match.group(1) not in gone:
                    return match.group(0)
                return match.group(0)[:match.start(1) - match.start()] + tu

            changed = FOLD_PROOF_RE.sub(replace, notes)
            if changed != notes:
                field = '"' + changed.replace('"', '""') + '"' if quoted else changed
                payload = (text[:start] + field + text[end:]).encode("utf-8")
                count += 1
        out.append(payload + term)
    return b"".join(out), count


def repoint_all(root, gone, tu):
    """Point path-keyed columns, fold-proof tokens and doxygen INPUTs at the TU.
    Returns {file: records}; protected registries retain their normal gates."""
    moved = {}
    for rel, column in rename.PATH_COLUMNS:
        path = Path(root) / rel
        if not path.exists():
            continue
        raw = path.read_bytes()
        total = 0
        for f in sorted(gone):
            raw, n = rename.repoint_column(raw, rel, column, f, tu)
            total += n
        if total:
            path.write_bytes(raw)
            moved[rel] = total
    pins = Path(root) / "reverse/symbols.csv"
    if pins.exists():
        raw, n = repoint_fold_proofs(pins.read_bytes(), gone, tu)
        if n:
            pins.write_bytes(raw)
            moved["reverse/symbols.csv"] = n
    cfg = Path(root) / rename.SOURCES_CFG
    if cfg.exists():
        raw, n = repoint_sources_cfg(cfg.read_bytes(), set(gone), tu)
        if n:
            cfg.write_bytes(raw)
            moved[rename.SOURCES_CFG] = n
    return moved


def refresh_reports(root, gone, tu, text):
    """Keep header debt and the Microsoft-header picker attached to the TU."""
    import header_adopt_lane
    moved = {}
    count = header_adopt_lane.transfer_sources(
        gone, tu, queue=Path(root) / "reverse/header_queue.tsv")
    if count:
        moved["reverse/header_queue.tsv"] = count
    queue = Path(root) / "reverse/ms_header_queue.tsv"
    if not queue.exists():
        return moved
    import ms_header_audit
    index = ms_header_audit.load_index()
    result = ms_header_audit.scan_text(tu, text, index)
    changed = ms_header_audit.refresh_queue(
        {tu: result}, index, removed=gone, queue=queue,
        occurrences=Path(root) / "build/ms_header_audit/occurrences.tsv")
    if changed:
        moved["reverse/ms_header_queue.tsv"] = 1
    return moved


def apply(tu, accepted, text, root=ROOT, carry=None):
    gone = [f for f in accepted if f != tu]
    if carry and carry.hatch:
        # hatch_counters --update rewrites the register from the whole tree
        others = dirty_others(root, set(accepted) | {tu})
        if others:
            raise SystemExit("tu_skeleton: the hatch register is rewritten from the whole tree; commit or stash "
                             "the other modified files first: " + ", ".join(others[:5]))
    (Path(root) / tu).parent.mkdir(parents=True, exist_ok=True)   # a TU in a directory nothing lives in yet
    moved = repoint_all(root, gone, tu)
    if carry:
        moved.update({rel: carry.moved[rel] for rel in carry.write()})
    (Path(root) / tu).write_text(text, encoding="utf-8", newline="\n")
    moved.update(refresh_reports(root, gone, tu, text))
    if gone:
        subprocess.run(["git", "rm", "-q", "--", *gone], cwd=root, check=True)
    subprocess.run(["git", "add", "--", tu, *moved], cwd=root, check=True)
    if carry and carry.hatch:   # escape-hatch counts moved between units: a total-keeping move
        subprocess.run([sys.executable, "tools/hatch_counters.py", "--update"], cwd=root, check=True)
        subprocess.run(["git", "add", "--", HATCH_REGISTER], cwd=root, check=True)
        moved[HATCH_REGISTER] = "updated"
    if carry:
        raws = {rel: (Path(root) / rel).read_bytes() for rel in rename.PROTECTED_PATH_KEYED
                if (Path(root) / rel).exists()}
        left = vanished(raws, set(gone))
        if left:
            raise SystemExit("tu_skeleton: the staged merge still keys deleted donors in protected registers "
                             "(unstage it with git restore --staged --worktree): "
                             + "; ".join(f"{rel}: {line[:120]}" for rel, line in left[:5]))
    _CACHE.clear()
    return moved


def plan(tu):
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    for t, led in sk:
        state = ("pull " + led["source"] if led and led["source"] in don else
                 "mixed " + led["source"] if led and led["source"] in mixed else
                 "refused " + led["source"] + " (" + refused[led["source"]] + ")"
                 if led and led["source"] in refused else
                 "placeholder (" + (led["status"] if led else "unledgered") + ")")
        print(f"{t['rva']} {int(t['size']):6d} {t['by']} {(led or {}).get('name', '')[:60]:60s} {state}")
    print(f"{len(sk)} approved rows, {len(don)} donor files, {len(mixed)} mixed files, "
          f"{len(refused)} refused files")


def queue_entries(under="", root=ROOT):
    """queue()'s TUs before the claim-dependent order, each with `keys`, the claim keys of
    its merge scope: a pure function of the tree (no claims read), so the picker caches it
    (tools/picker_cache.py)."""
    by_tu = collections.defaultdict(list)
    for r in map_rows():
        if r["confidence"] == "approved" and r["kind"].startswith("code") and r["tu"]:
            by_tu[r["tu"]].append(r)
    out = []
    for tu in sorted(by_tu):
        if under and not tu.startswith(under):
            continue
        sk = skeleton(tu)
        don, mixed, refused = donors(tu, sk)
        removes = len(don) - 1
        if removes < 1 or tu in mixed or ((Path(root) / tu).exists() and tu not in don):
            continue   # nothing to remove, or the TU path itself must be split first
        keys = {claims.key_of(k) for k in claim_keys(tu, don)}
        out.append({"tu": tu, "removes": removes, "rows": sum(len(v) for v in don.values()),
                    "mixed": len(mixed), "refused": len(refused), "keys": sorted(keys, key=str)})
    return out


def queue(under="", limit=None, root=ROOT, entries=None):
    """Approved TUs a merge can shrink, most files removed first; a TU whose scope another
    worker holds goes last. ENTRIES: queue_entries(under, root), when the caller has them.

    `removes` is an upper bound: the merge verifies every donor and keeps only
    those that compile together without losing a matched row."""
    entries = queue_entries(under, root) if entries is None else entries
    try:
        held = set().union(*(set(rec) for rec in claims._blocking_records(root)))
    except Exception:   # no origin: nothing is known to be held
        held = set()
    out = [{**{k: v for k, v in e.items() if k != "keys"}, "held": bool(set(e["keys"]) & held)} for e in entries]
    out.sort(key=lambda d: (d["held"], -d["removes"], -d["rows"], d["tu"]))
    return out[:limit] if limit else out


def list_tus(prefix):
    c = collections.defaultdict(set)
    for r in map_rows():
        if r["confidence"] == "approved" and r["tu"].startswith(prefix) and r["kind"].startswith("code"):
            c[r["tu"]].add(r["source"])
    for tu, files in sorted(c.items()):
        print(f"{len(files - {''}):3d} files  {tu}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--queue", action="store_true")
    g.add_argument("--list", metavar="PREFIX")
    g.add_argument("--plan", metavar="TU")
    g.add_argument("--merge", metavar="TU")
    g.add_argument("--split", metavar="FILE", help="carve the rows approved for --for TU out of a mixed FILE")
    g.add_argument("--merge-all", action="store_true",
                   help="merge every queued TU (tools/merge_all.py): parallel worktrees, a decision queue")
    ap.add_argument("--for", dest="for_tu", metavar="TU", help="with --split: the destination TU (omit to list)")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--no-claim", action="store_true", help="merge without claiming (fixtures, private trees)")
    ap.add_argument("--under", default="")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--json")
    import merge_all
    merge_all.add_run_args(ap)
    a = ap.parse_args(argv)
    if a.merge_all:
        return merge_all.run_main(a)
    if a.queue:
        q = queue(a.under, a.limit)
        if a.json:
            Path(a.json).write_text(json.dumps(q, indent=2) + "\n")
        if _CACHE.get("stale"):
            print("(tu_map.csv is stale; the queue uses a map rebuilt in memory)")
        for d in q:
            print(f"{d['removes']:4d} files {d['rows']:5d} rows  mixed {d['mixed']:3d}  refused {d['refused']:3d}"
                  f"{'  HELD' if d['held'] else ''}  {d['tu']}")
        return 0
    if a.list is not None:
        list_tus(a.list)
    elif a.plan:
        plan(a.plan)
    elif a.split:
        if not a.for_tu:
            for tu, rows in sorted(breakdown(a.split).items(), key=lambda kv: -len(kv[1])):
                print(f"{len(rows):5d} rows  {tu or '(no approved TU)'}"
                      f"{'' if not tu or (ROOT / tu).exists() else '  (no file yet)'}")
            return 0
        rep = split(a.split, a.for_tu, a.dry_run, claim=not a.no_claim)
        text = rep.pop("text", None)
        for k, val in rep.items():
            print(f"{k}: {val}")
        if text and a.dry_run:
            print(text)
        return 0 if rep.get("subject") or (a.dry_run and a.split in rep.get("accepted", [])) else 2
    else:
        rep = merge(a.merge, a.dry_run, claim=not a.no_claim)
        text = rep.pop("text", None)
        for k, val in rep.items():
            if k in ("debt-retired", "follow-up"):   # lines to paste or run, one per line
                print(f"{k}:" + "".join(f"\n  {line}" for line in val))
            else:
                print(f"{k}: {val}")
        if text and a.dry_run:
            print(text)
        return 0 if rep.get("accepted") and not rep.get("blocked") else 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
