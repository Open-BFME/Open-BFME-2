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

Every merge, split and shatter also keeps its providers (ProviderGuard, P142):
each definition the replaced objects made is still made, with equal bytes and
relocations, by an object that continues it, and the copy the real link keeps
of each COMDAT is the same under exit_link's --order retail and --order path.
A refusal ("provider: ...", the report's `provider` names per donor) is header
or reconciliation work, never a reason to merge differently. It needs the census
index whether or not any file links.

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
  python3 tools/tu_skeleton.py --split FILE --for TU [--prepared TU=TEXT] [--dry-run] [--no-claim]
      carve the rows approved for TU out of a mixed FILE into the TU path (the
      split lane, documented in docs/consolidation.md): the residual keeps every
      other row. --prepared: TEXT (a file) is the TU's whole final text, written
      with the carve in one transaction; a donor left with no row is absorbed
  python3 tools/tu_skeleton.py --emit-move FILE[,FILE...] --for TU [--rva 0xRVA,...]
                               [--prepared PATH=TEXT ...] [--dry-run] [--no-claim]
      repoint the deleting-destructor rows (`??_G`/`??_E`, by decorated name) of
      mixed files that the map approves for TU to the TU file, once its own code
      emits each byte-exact (emit_move), as one transaction: one journal, one build
      over exactly those files, one undo. --rva picks a subset of each file's rows.
      --prepared: TEXT (a file) is the whole final text of the TU or of a listed
      file, written in the same transaction; without it no text moves
"""
import argparse
import collections
import contextlib
import csv
import functools
import hashlib
import io
import json
import os
import posixpath
import re
import subprocess
import sys
import time
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parent))
import git_trust  # noqa: E402
import tu_map  # noqa: E402
import claims  # noqa: E402
import rename  # noqa: E402
import rename_files  # noqa: E402
import picker_cache  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
LAYOUT = tu_map.Layout(ROOT)
LEDGER = LAYOUT.path("functions.csv")
MARK = "// tu-skeleton:"
# an EH funclet row (`__ehhandler$X`, ...) is emitted with its parent X and lives in X's file
FUNCLET = re.compile(r"^__(?:ehhandler|unwindfunclet|catch|catchsym|tryblocktable|unwindtable)\$(.+)$")
PARENT_NOTE = re.compile(r"parent=([^;\s]+)")          # gen-funclet;parent=X (`$L5782`, `Unwind@00b636b8`)
DELETING = re.compile(r"^\?\?_[GE]((?:\?\$)?[A-Za-z_]\w*@)")   # ??_G / ??_E: the deleting destructors of ??1



def _unlink_resilient(path):
    """Delete a scratch file Windows may still hold a handle to.

    cl.exe (or the scanner behind it) can keep the just-compiled .cpp open for
    a moment after the process exits; POSIX unlink-while-open semantics do not
    exist on Win32, so a plain unlink races WinError 32. Retry briefly, then
    give up leaving the scratch behind rather than failing the merge trial.
    """
    for _ in range(10):
        try:
            path.unlink()
            return
        except PermissionError:
            time.sleep(0.2)
        except FileNotFoundError:
            return

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


BLOCK = re.compile(r'^(?:namespace(?:\s+([A-Za-z_]\w*))?|extern\s*"C")\s*\{')
LINKAGE_DEF = re.compile(r'^extern\s*"C"(?!\s*\{)')


def open_brace(c):
    """Offset of the first `{` in `c` outside comments and literals, else -1."""
    i, n = 0, len(c)
    while i < n:
        if c.startswith("//", i):
            j = c.find("\n", i)
            i = n if j < 0 else j
            continue
        if c.startswith("/*", i):
            j = c.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        ch = c[i]
        if ch in "\"'":
            j = i + 1
            while j < n and c[j] != ch:
                j += 2 if c[j] == "\\" else 1
            i = j + 1
            continue
        if ch == "{":
            return i
        i += 1
    return -1


def flat_chunks(text, base=0, scope=(), blocks=None):
    """chunks(text) as (kind, text, offset, scope), descending into `namespace X {}`
    and `extern "C" {}` blocks: their items come out in place of the block, at
    their offsets in `text`, with the enclosing scopes outermost first (a name,
    '' for an anonymous namespace, None for extern "C"). `blocks`, when given,
    collects (open, close, scope) of every block seen. A one-declaration
    `extern "C" T f(...) { ... }` is a 'def', like any other function body."""
    out, pos = [], 0
    for kind, c in chunks(text):
        at = text.find(c, pos)
        if at < 0:
            continue
        pos = at + len(c)
        s = norm(c)
        m = BLOCK.match(s) if kind == "decl" else None
        if m and c.rstrip().endswith("}"):
            ob, cb = open_brace(c), len(c.rstrip()) - 1
            name = None if s.startswith("extern") else (m.group(1) or "")
            if blocks is not None:
                blocks.append((base + at + ob, base + at + cb + 1, scope + (name,)))
            out.extend(flat_chunks(c[ob + 1:cb], base + at + ob + 1, scope + (name,), blocks))
            continue
        if kind == "decl" and LINKAGE_DEF.match(s) and s.endswith("}") \
                and re.search(r"\)\s*(?:const\s*)?\{", s) and not initialised(s.split("{")[0]):
            kind = "def"
        out.append((kind, c, base + at, scope))
    return out


def span_scopes(text, spans):
    """The enclosing block scopes (flat_chunks' spelling) of each span, () at file scope."""
    blocks = []
    flat_chunks(text, blocks=blocks)
    out = []
    for a, _, _, _ in spans:
        inside = [b for b in blocks if b[0] <= a < b[1]]
        out.append(max(inside, key=lambda b: len(b[2]))[2] if inside else ())
    return out


def strip(t):
    return COMMENT.sub(lambda m: m.group(0) if m.group(0)[0] in "\"'" else " ", t)


def norm(t):
    return re.sub(r"\s+", " ", strip(t)).strip()


# C++ preprocessing tokens, longest punctuator first: `>>` is not `> >`, `--` not `- -`
TOKEN = re.compile(r'''[LuU]?"(?:\\.|[^"\\\n])*"|[LuU]?'(?:\\.|[^'\\\n])*'
                       |\.?\d(?:[eEpP][+-]|[\w.])*|[A-Za-z_$]\w*
                       |%:%:|\.\.\.|<<=|>>=|->\*|::|\.\*|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\|
                       |[-+*/%&|^]=|\#\#|<:|:>|<%|%>|%:|\S''', re.X)


def token_seq(t):
    """`t`'s token sequence: comments and layout dropped, literals kept whole, and the end
    of each directive line kept (a directive ends at its newline)."""
    out = []
    for line in strip(t).replace("\\\n", "").splitlines():
        out.extend(TOKEN.findall(line))
        if line.lstrip().startswith("#"):
            out.append("\n")
    return tuple(out)


def key_of(kind, text):
    s = norm(text)
    m = re.match(r"^(?:template\s*<[^>]*>\s*)?(class|struct|enum|union)\s+(?:__declspec\([^)]*\)\s*)?"
                 r"([A-Za-z_]\w*(?:\s*::\s*[A-Za-z_]\w*)*)\s*(?::(?!:)[^{]*)?\{", s)
    if m:
        return ("type", "".join(m.group(2).split()))
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
    want, led = _CACHE["approved_by_tu"].get(tu.lower(), []), address_identities()
    return [(r, led.get(int(r["rva"], 16))) for r in sorted(want, key=lambda r: int(r["rva"], 16))]


def address_identities():
    """{rva: the ledger row tu_map identifies the address by}: its first row that is
    not a gen-alias (tu_map.evidence_rows: one identity per address, first row wins)."""
    if "led_by_rva" not in _CACHE:
        led = {}
        for r in ledger_rows():
            if "gen-alias" not in (r["notes"] or "") and r["target_rva"].startswith("0x"):
                led.setdefault(int(r["target_rva"], 16), r)
        _CACHE["led_by_rva"] = led
    return _CACHE["led_by_rva"]


def fold_alias(row):
    """True for a ledger row that shares its address with another row the map
    identifies the address by: an ICF alias (link.exe kept one of several identical
    bodies, e.g. the 14-byte free-first-pointer destructor at 0x0007FAB3). The map
    places the identity, never an alias, so an alias is no TU's row: like a
    companion it lives where the bodies that emit it live."""
    if "ledger_keys" not in _CACHE:
        _CACHE["ledger_keys"] = {(r["target_rva"].lower(), r["name"], r["source"]) for r in ledger_rows()}
    key = (row["target_rva"].lower(), row["name"], row["source"])
    first = address_identities().get(int(row["target_rva"], 16))
    return first is not None and key in _CACHE["ledger_keys"] and \
        (first["name"], first["source"]) != (row["name"], row["source"])


def donors(tu, sk):
    """(donor file -> its rows, mixed file -> foreign row count, refused file -> why).

    A candidate is the file of an approved row, or the TU path itself. A donor
    other than the TU path may be absorbed only when every matched row it owns is
    approved for this TU (approved_homes: a p-group funclet only when its parent
    is) or is homeless (tu_map.homeless: a displaced or header-inline COMDAT, a
    template instantiation, a compiler-generated COMDAT, which the map leaves
    without a TU on purpose and which follows its file). A row the map puts in
    another TU, or leaves without one for want of evidence, makes it mixed; a row
    only proposed for this TU refuses it: only approved rows move. The TU path
    itself moves none of its rows (the merge seeds from it), so only a row the
    map approves for another TU blocks it: one the map merely proposes for another
    TU stays in the TU file as its own unassigned rows do (a proposal is not an
    approval; if it is approved later, moving the row out is an ordinary repair).
    A donor is also refused when deleting it is not mechanical (see refusal()).
    """
    rows = ledger_rows()
    if "assigned" not in _CACHE:
        _CACHE["assigned"] = {int(r["rva"], 16): r["tu"].lower() for r in map_rows()
                              if r["kind"].startswith("code") and r["tu"]}
        _CACHE["unplaced"] = {int(r["rva"], 16): r for r in map_rows() if r["kind"].startswith("code") and not r["tu"]}
        _CACHE["approved"] = approved_homes(map_rows())
    if "proposed" not in _CACHE:
        _CACHE["proposed"] = {int(r["rva"], 16) for r in map_rows()
                              if r["kind"].startswith("code") and r["tu"] and r["confidence"] == "proposed"}
    assigned, unplaced, approved = _CACHE["assigned"], _CACHE["unplaced"], _CACHE["approved"]
    proposed = _CACHE["proposed"]
    if "by_file" not in _CACHE:
        _CACHE["by_file"] = collections.defaultdict(list)
        for r in rows:
            _CACHE["by_file"][r["source"]].append(r)
    by_file = _CACHE["by_file"]
    # The file the TU's rows are filed under: reverse/tu_map.csv names the TU, but a
    # checkout or the ledger can spell the same path in another case, and the two
    # spellings are one file (never renamed, never written twice).
    if "by_file_ci" not in _CACHE:
        _CACHE["by_file_ci"] = {k.lower(): k for k in by_file}
    # Unconverted rows are approved too now; a generated or dump file (gen_uw.py owns
    # gen_small end to end) is a placeholder for the address, never a donor to absorb.
    cands = {led["source"] for t, led in sk
             if led and led["status"] == "matched" and led["source"].endswith(".cpp")
             and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", led["source"])}
    seed = tu if tu in by_file else _CACHE["by_file_ci"].get(tu.lower())
    if seed:
        cands.add(seed)
    out, mixed, refused = {}, {}, {}
    for f in sorted(cands):
        own = [r for r in by_file[f] if r["status"] == "matched" and "gen-alias" not in (r["notes"] or "")]
        # The TU file's own code emits an implicit template instantiation the map places in
        # another TU by contiguity alone (emission_held): the seed keeps it like an unplaced
        # row. A donor's never: absorbing it would carry the row away from its approved TU.
        # (only a row the map places in another TU can make the file mixed: judge only those)
        # (an ICF alias is never foreign anyway: no need to preprocess for it)
        # So does a row the map only proposes for another TU (not approved): the seed keeps it in
        # place, unmoved and re-verified, exactly like a row the map places nowhere. A donor's
        # never: absorbing the donor would move the row.
        held = ({id(r) for r in own if assigned.get(int(r["target_rva"], 16)) not in (tu.lower(), None)
                 and not fold_alias(r) and (emission_held(r) or int(r["target_rva"], 16) in proposed)}
                if f.lower() == tu.lower() else set())
        mine = {id(r): None if id(r) in held else assigned.get(int(r["target_rva"], 16)) for r in own}
        home = {r["name"]: mine[id(r)] for r in own}
        dtors = {m.group(1): r["name"] for r in own if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
        # a companion row (funclet, deleting dtor) the map does not place itself is emitted
        # with its parent and lives where it lives; its own assignment always comes first
        where = {id(r): mine[id(r)] if mine[id(r)] is not None
                 else home[p] if (p := parent_of(r, dtors)) and p in home else None for r in own}
        # The TU file itself may keep rows the map has not placed anywhere: the merge
        # seeds from it, moves none of them, and verifies they still match. Any file's
        # homeless rows (and their unplaced companions) follow it the same way. A row the
        # map puts in another TU still makes it mixed (split it first).
        free = {r["name"] for r in own if where[id(r)] is None and homeless(r, unplaced)}
        # a companion rides with a homeless parent only when its own evidence names no other TU
        rider = {id(r) for r in own if where[id(r)] is None and (
            r["name"] in free or parent_of(r, dtors) in free and not names_other_tu(r, unplaced, tu))}
        foreign = [r for r in own if where[id(r)] != tu.lower() and not fold_alias(r)
                   and not (where[id(r)] is None and (f.lower() == tu.lower() or id(r) in rider))]
        # what a donor moves must be approved here: the row itself when the map places it,
        # and a companion's parent
        ok = {r["name"]: approved.get(int(r["target_rva"], 16)) for r in own}
        own_by_name = {r["name"]: r for r in own}

        def approved_here(r):
            p = parent_of(r, dtors)
            if mine[id(r)] is not None and ok[r["name"]] != tu.lower():
                return False
            if not (p and p in ok and ok[p] != tu.lower()):
                return True
            # A deleting dtor can have independent approved placement even
            # when its complete dtor folds into an address identity with no TU
            # (FadeInTextRender). The alias already travels with this donor;
            # it cannot veto the child's own approval. Keep every other parent
            # constraint, including foreign evidence and p-group approval.
            parent = own_by_name.get(p)
            return bool(DELETING.match(r["name"])
                        and mine[id(r)] == tu.lower() and ok[r["name"]] == tu.lower()
                        and parent is not None and mine[id(parent)] is None
                        and int(parent["target_rva"], 16) in unplaced
                        and fold_alias(parent) and not names_other_tu(parent, unplaced, tu))
        unapproved = [] if f.lower() == tu.lower() else [r for r in own if where[id(r)] == tu.lower() and not approved_here(r)]
        if foreign:
            mixed[f] = len(foreign)
        elif unapproved:
            refused[f] = f"{len(unapproved)} row(s) not approved for this TU (only approved rows move)"
        elif own:
            why = refusal(f, by_file[f]) if f.lower() != tu.lower() else None
            if why:
                refused[f] = why
            else:
                out[f] = own
    return out, mixed, refused


P_PARENT = re.compile(r"(?<![\w=])P=0x([0-9A-Fa-f]+)@")


def approved_homes(rows):
    """{rva: TU key} of the code rows a merge may move into their TU: approved, and a
    p-group funclet (tu_evidence.P_GROUP_TOKEN) only when its parent is approved for the
    same TU (the token marks a funclet approved because of a parent the map does not
    approve, which would make its approval circular)."""
    code = {int(r["rva"], 16): r for r in rows if r["kind"].startswith("code") and r["tu"]}
    out = {}
    for rva, r in code.items():
        if r["confidence"] != "approved":
            continue
        if "p-group" in r["evidence"].split():
            m = P_PARENT.search(r["evidence"])
            parent = code.get(int(m.group(1), 16)) if m else None
            if not parent or parent["confidence"] != "approved" or parent["tu"].lower() != r["tu"].lower():
                continue
        out[rva] = r["tu"].lower()
    return out


def homeless(r, unplaced):
    """Does ledger row `r` (with no TU) sit at a map row tu_map leaves homeless on purpose?"""
    m = unplaced.get(int(r["target_rva"], 16))
    return m is not None and tu_map.homeless(m, r["name"])


# A member of a class template specialization (`?clear@?$hashtable@...`, `??0?$vector@...`,
# `??_G?$Box@...`) or a function template specialization (`??$max@H@...`): the symbol itself is
# an instantiation, not a function that merely takes a template type (`?f@@YAXV?$vector@...`).
TEMPLATE_INSTANCE = re.compile(r"^\?(?:\?\$|(?:\?_?[0-9A-Z]|[A-Za-z_]\w*@)\?\$)")


def emission_held(r):
    """Is ledger row `r` an implicit template instantiation the map places by retail
    placement alone, so that it follows the file that emits it (LINK-629)?

    MSVC emits an implicit instantiation as a COMDAT in every object that uses it and the
    linker keeps one, inside the contribution of the object it took it from. The map's C
    (contiguity) then names that object's TU, which is a fact about retail's link order,
    not about where the body is written: no source spells it, and any TU instantiating
    the template emits the same bytes. Such a row is held by emission, like a homeless
    one: it makes no file mixed, names no donor, blocks no merge or split, and moves only
    with the bodies that instantiate it (a split's riders), always re-verified where it
    lands. It needs: a TEMPLATE_INSTANCE name, a map row whose TU rests on C alone (no
    F/Z/S/L/W token naming one), and no definition in its own file spelling its name (an
    explicit specialization is a real body with a home). An unreadable file is no proof.
    A compiler-generated special member is never held this way (review of bfb856bfbf: a
    hand-written copy ctor can match the implicit one's bytes exactly)."""
    if "map_by_rva" not in _CACHE:
        _CACHE["map_by_rva"] = {int(m["rva"], 16): m for m in map_rows() if m["kind"].startswith("code")}
    m = _CACHE["map_by_rva"].get(int(r["target_rva"], 16))
    if not m or not m["tu"] or m.get("by") != "C" or not TEMPLATE_INSTANCE.match(r["name"]):
        return False
    if any(k in tu_map.TU_EVIDENCE and eq for k, eq, _ in (t.partition("=") for t in (m["evidence"] or "").split())):
        return False
    return not spells_definition(r["source"], r)


def vtable_rider(r):
    """May ledger row `r` ride with carved bodies to whatever object emits its class's vtable
    (P16: `??_G` 0x001E10CE with the ctor 0x001E0AEF)? The static half: a deleting destructor
    by its decorated name (deleting_class), the map leaving it without a TU on purpose
    (tu_map.homeless: displaced, no F/Z/S/L/W evidence), and the only ledger row at its address
    (no other emitter's row there to claim it). split() adds the dynamic half: the
    destination's object emits the class's vtable and the residual's does not, neither copy is
    hand-written (hand_written_problem: the objects' COMDAT selection, `__identifier`
    definitions in the destination's and the file's preprocessed text), and the row matches
    where it lands."""
    if not deleting_class(r["name"]):
        return False
    if "map_by_rva" not in _CACHE:
        _CACHE["map_by_rva"] = {int(m["rva"], 16): m for m in map_rows() if m["kind"].startswith("code")}
    m = _CACHE["map_by_rva"].get(int(r["target_rva"], 16))
    if m is None or m["tu"]:
        return False
    if any(k in tu_map.TU_EVIDENCE and eq for k, eq, _ in (t.partition("=") for t in (m.get("evidence") or "").split())):
        return False                                  # its own evidence names a TU: not the map's to leave open
    if not (tu_map.homeless(m, r["name"]) or m.get("confidence") == "displaced"):
        return False
    return sum(1 for o in ledger_rows() if o["target_rva"].lower() == r["target_rva"].lower()) == 1


def vtable_symbols(obj, cls):
    """`cls`'s vtable symbols (`??_7Cls@@6B...`) that `obj` defines."""
    return {s for s in defined_symbols(obj) if s.startswith(f"??_7{cls}@@6B")}


def prepared_hatches(path, before, residual, tu, prepared):
    """{(hatch, token): count} the move takes out of `path`, or None when a total over the file
    and the TU would grow: the TU's current text and `path`'s before against the prepared TU
    text and the residual (hatch_counters rule 3; a split's prepared text replaces the TU)."""
    try:
        import hatch_counters as H
    except ImportError:
        return {}

    def totals(rel, text):
        out = collections.Counter()
        for (hatch, _p, token), n in H.scan(rel, text).items():
            out[(hatch, token)] += n
        return out
    tu_text = (ROOT / tu).read_text(encoding="utf-8-sig", errors="replace") if (ROOT / tu).exists() else ""
    old = totals(path, before) + totals(tu, tu_text)
    new = totals(path, residual) + totals(tu, prepared)
    if any(new[k] > old.get(k, 0) for k in new):
        return None
    return {k: n for k, n in totals(path, before).items() if n}


def assigned_tu(r):
    """The TU key (lowercase) the map assigns ledger row `r`'s address to, or None."""
    if "assigned_tu" not in _CACHE:
        _CACHE["assigned_tu"] = {int(m["rva"], 16): m["tu"].lower() for m in map_rows()
                                 if m["kind"].startswith("code") and m["tu"]}
    return _CACHE["assigned_tu"].get(int(r["target_rva"], 16))


def instance_owner(name):
    """(class template or None, what a definition of the member spells) for a TEMPLATE_INSTANCE
    name, or None when it cannot be read. `?clear@?$hashtable@...` -> ("hashtable", "clear");
    `??0?$Box@` -> ("Box", "Box"); `??1?$Box@`, `??_G`/`??_E` -> ("Box", "~Box"); any other
    operator, conversions included (`??R`, `??4`, `??B`) -> ("Box", "operator");
    `??$max@H@...` -> (None, "max"), a function template. row_names() reads none of the
    operators of a class template (review of 9356f06742)."""
    m = re.match(r"^\?\?\$([A-Za-z_]\w*)@", name)
    if m:
        return None, m.group(1)
    m = re.match(r"^\?([A-Za-z_]\w*)@\?\$([A-Za-z_]\w*)@", name)
    if m:
        return m.group(2), m.group(1)
    m = re.match(r"^\?\?(_?[0-9A-Z])\?\$([A-Za-z_]\w*)@", name)
    if m:
        op, cls = m.groups()
        return cls, cls if op == "0" else "~" + cls if op in ("1", "_G", "_E") else "operator"
    return None


def spells_definition(path, r):
    """Does a definition (or a macro invocation naming its class) in `path` spell row `r`'s
    name (identify())? So does, for its class template (instance_owner): a body of the class
    itself (`struct hash<NameKeyType> {`, a file-local template, an operator written inside
    it), a member qualified through template arguments (`hashtable<...>::clear(`,
    `Box<int>::operator()(`, an explicit specialization or an explicit member instantiation)
    or an explicit instantiation of the class (`template class Box<int>;`); for a function
    template, any `f<...>(` after `template`. True when the file cannot be read or the row's
    owner cannot be derived: no proof of absence."""
    texts = _CACHE.setdefault("spell_texts", {})
    if path not in texts:
        try:
            text = (ROOT / path).read_bytes().decode("utf-8-sig", errors="replace").replace("\r\n", "\n")
        except OSError:
            text = None
        spans = def_spans(text) if text is not None else None
        texts[path] = (spans, span_scopes(text, spans), strip(text)) if spans is not None else None
    if texts[path] is None:
        return True
    spans, scopes, code = texts[path]
    if identify([r], spans, scopes)[r["target_rva"]]:
        return True
    owner = instance_owner(r["name"])
    if owner is None:
        return True
    cls, meth = owner
    if cls is None:
        return bool(re.search(r"\btemplate\b[^;{}]*\b" + re.escape(meth) + r"\s*<[^;{}]*>\s*\(", code))
    member = r"operator\b" if meth == "operator" else re.escape(meth) + r"\s*\("
    return bool(
        re.search(r"\b(?:class|struct|union)\s+" + re.escape(cls) + r"\b[^;{}]*\{", code)
        or re.search(r"\btemplate\s+(?:class|struct|union)\s+(?:[A-Za-z_]\w*\s*::\s*)*" + re.escape(cls) + r"\s*<", code)
        or re.search(r"\b" + re.escape(cls) + r"\s*<[^;{}]*>\s*::\s*" + member, code))


def names_other_tu(r, unplaced, tu):
    """Does the map row of ledger row `r` (with no TU) carry F/Z/S/L/W evidence naming a TU
    other than `tu`?"""
    m = unplaced.get(int(r["target_rva"], 16))
    for token in ((m or {}).get("evidence") or "").split():
        k, eq, v = token.partition("=")
        if eq and k in tu_map.TU_EVIDENCE and v.lower() != tu.lower():
            return True
    return False


def flags_of(text):
    import build
    for line in text.splitlines():
        if line.startswith("// cl:"):
            return build._source_flag_tokens(line[len("// cl:"):])
    return []


def render_flags(flags):
    """Write parsed include operands back to a // cl: line without losing spaces."""
    return " ".join(f'{flag[:2]}"{flag[2:]}"'
                    if flag.startswith(("/I", "-I")) and any(c.isspace() for c in flag[2:])
                    else flag for flag in flags)


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


RESET_PRAGMA = re.compile(r'#\s*pragma\s+optimize\s*\(\s*""\s*,\s*on\s*\)')


def after_named_functions(parsed):
    """A file-scope object initialized with a free function this file defines, and declares nowhere
    above it, stays after that function: compose writes declarations first, and hoisted above the
    definition the name is unknown (C2065, then C2365: Player.cpp's bfme_force_ScienceVec_erase_anchor,
    which failed alone though the file builds as written). A prototype above it, or a qualified name
    a class declares, already gives compose the name, and that object is hoisted as before."""
    defined = {}
    for at, (kind, text) in enumerate(parsed):
        if kind == "def":
            head = re.match(r"[^(]*?\b([A-Za-z_]\w*)\s*\(", strip(text))
            if head and "::" not in head.group(0):
                defined.setdefault(head.group(1), at)
    out = list(parsed)
    for at, (kind, text) in enumerate(parsed):
        if kind != "decl" or "=" not in text:
            continue
        code = strip(text)
        if re.match(r"\s*(class|struct|union|enum|typedef|template|namespace)\b", code):
            continue
        named = re.search(r"=\s*&?\s*([A-Za-z_]\w*)\s*;\s*$", code)
        if not named or defined.get(named.group(1), at) >= at:
            continue
        call = re.compile(r"\b%s\s*\(" % re.escape(named.group(1)))
        if not any(k == "decl" and call.search(strip(c)) for k, c in parsed[:at]):
            out[at] = ("body-decl", text)
    return out


def composition_chunks(text):
    """Keep conditional regions opaque and optimization directives with bodies.

    Hoisting/deduplicating individual #if/#endif lines changes their branches
    and can leave an otherwise valid donor unterminated. A whole region can be
    retained as one declaration (or preprocessor item when it contains only
    directives/comments). Its contents are not candidates for view unioning.
    Optimization pragmas must run in the donor's function order, including
    repeated resets, rather than joining the hoisted include directives.
    Explicit instantiation definitions likewise stay in body order, after their
    primary templates and inside their original directive context.
    A closed inline_depth scope around declarations stays opaque too: moving
    its reset ahead of global objects changes their constructor calls.
    """
    out, region, nesting = [], [], 0
    for kind, text in chunks(text):
        # Explicit instantiation definitions need the primary template and the
        # donor's current optimization state. Specialization declarations and
        # extern-template declarations must still precede their callers.
        if kind == "decl" and re.match(r"template\b(?!\s*<)", norm(text)):
            kind = "body-decl"
        directive = re.match(r"#\s*(if|ifdef|ifndef|endif)\b", text) if kind == "pp" else None
        word = directive.group(1) if directive else None
        if word in ("if", "ifdef", "ifndef"):
            nesting += 1
        if nesting:
            region.append((kind, text))
            if word == "endif":
                nesting -= 1
                if not nesting:
                    opaque_kind = ("body-decl" if any(k == "body-decl" for k, _ in region) else
                                   "pp" if all(k in ("pp", "tail") for k, _ in region) else "decl")
                    out.append((opaque_kind, "\n".join(c for _, c in region)))
                    region = []
            continue
        if kind == "pp" and re.match(r"#\s*pragma\s+optimize\s*\(", text):
            kind = "body-pp"
        # `#pragma intrinsic(f)` takes effect only after f is declared: hoisted
        # above a donor's own `extern "C" void _ReadWriteBarrier();` it is
        # ignored and the call becomes an external one (0x0051730E). It stays
        # with the declaration right before it that names one of its functions.
        intrinsic = re.fullmatch(r"#\s*pragma\s+intrinsic\s*\(([^)]*)\)\s*", text) if kind == "pp" else None
        if intrinsic and out and out[-1][0] == "decl" and any(
                re.search(r"\b%s\s*\(" % re.escape(name), strip(out[-1][1]))
                for name in re.findall(r"[A-Za-z_]\w*", intrinsic.group(1))):
            out[-1] = ("decl", out[-1][1].rstrip("\n") + "\n" + text)
            continue
        out.append((kind, text))
    if region:  # Preserve malformed input too: the compiler must still refuse it.
        out.append(("decl", "\n".join(c for _, c in region)))
    scoped, at = [], 0
    while at < len(out):
        kind, text = out[at]
        if kind == "pp" and re.fullmatch(r"#\s*pragma\s+inline_depth\s*\(\s*\d+\s*\)\s*", text):
            end = at + 1
            while end < len(out) and out[end][0] in ("decl", "tail") \
                    and not out[end][1].lstrip().startswith("#"):
                end += 1
            if end > at + 1 and end < len(out) and out[end][0] == "pp" \
                    and re.fullmatch(r"#\s*pragma\s+inline_depth\s*\(\s*\)\s*", out[end][1]):
                scoped.append(("decl", "\n".join(c for _, c in out[at:end + 1])))
                at = end + 1
                continue
        scoped.append(out[at])
        at += 1
    return after_named_functions(scoped)


LITERAL = re.compile(r"\"|'|\b\d")


def trailing_object(text):
    """A namespace-scope object definition that may run a dynamic initializer.

    Typedefs, extern and using declarations, templates and prototypes take no
    _$E/_$S ordinal and may be needed by a hoisted type, so they are not this;
    neither are forward declarations (`struct Node;`). A declarator without a
    parameter list, with an initializer, or whose parenthesised list holds a
    literal (`Node n("Tok", f);`) is an object. `Node n(f);` reads as a
    prototype and stays hoisted, as before.
    """
    s = norm(text)
    if re.match(r"^(typedef|extern|using|template|friend|namespace|static_assert)\b", s) \
            or re.match(r"^(class|struct|union|enum)\s+[\w:]+\s*;$", s) or s == ";":
        return False
    if "(" not in s or "=" in s.split("(")[0]:
        return True    # `Node n;`, `Node *n = make(3);`, `const char *names[] = {...};`
    m = re.search(r"\((.*)\)\s*;$", s)
    return bool(m and LITERAL.search(m.group(1)))


def compose(tu, sk, files, texts, flags, strategy, drop=frozenset(), drop_all=frozenset()):
    """Declarations first (donor order, one spelling each), then bodies in retail order.

    `files` is in donor order with the seed first. A type two donors spell
    differently is emitted once, from the donor whose spelling is chosen and at
    that donor's own position, so whatever it depends on is already declared.
    Spellings are compared as token sequences: one that differs only in layout or
    comments is the first spelling, not a variant a strategy could move below the
    seed's uses of it.
    """
    parsed = {f: composition_chunks("\n".join(l for l in texts[f].lstrip("\ufeff").splitlines()
                                  if not l.startswith("// cl:") and l.strip() != "// stlport"
                                  and not l.startswith(MARK) and not l.startswith("// TU ")) + "\n")
              for f in files}   # a seed's own placeholders and header are regenerated below
    variants, spelled = collections.defaultdict(list), collections.defaultdict(set)
    for f in files:
        for kind, c in parsed[f]:
            if kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and (seq := token_seq(c)) not in spelled[k]:
                    spelled[k].add(seq)
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
    forwards = set()
    trailing, trailing_seen = [], set()
    for f in files:
        # a declaration before the file's last #include (a type an included header
        # needs, e.g. CrateSystem.cpp's KindOfMaskType) stays among the includes;
        # so do an optimize pragma and a body there (mapper.cpp's pragmas around
        # refcount.h and vector2.h scope those headers' inlines, its anchor body
        # sits between them): moved below every include they changed bytes
        last_inc = max((i for i, (kind, c) in enumerate(parsed[f])
                        if kind == "pp" and re.match(r"#\s*include\b", c.strip())), default=-1)
        # A file-scope object defined after the file's last body (an INI unit's
        # `BlockParse node("Token", parse);`) keeps following every body: its
        # dynamic initializer takes the next _$E/_$S ordinal after the ones the
        # bodies' own objects took, so hoisting it above them renames each
        # row it emits. Its types, typedefs, externs and prototypes still come
        # first (trailing_object()); no other file depends on the object, so it
        # is never registered as `seen`.
        last_def = max((i for i, (kind, _) in enumerate(parsed[f]) if kind == "def"), default=-1)
        for at, (kind, c) in enumerate(parsed[f]):
            if kind == "decl" and last_def >= 0 and at > max(last_def, last_inc) \
                    and key_of(kind, c)[0] == "decl" and trailing_object(c):
                placed.add((f, at))
                if (k := key_of(kind, c)) not in trailing_seen:
                    trailing_seen.add(k)
                    trailing.append(c.strip("\n"))
                continue
            into = pps if at < last_inc else decls
            if at < last_inc and kind in ("def", "body-pp", "body-decl"):
                placed.add((f, at))
                if kind in ("body-pp", "body-decl"):
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
                if re.fullmatch(r"(?:class|struct|union)\s+[A-Za-z_]\w*\s*;", norm(c)):
                    # A later donor's pre-include use precedes the seed's
                    # decls in the output. A forward seen only in decls cannot
                    # replace that donor's forward in pps (expansion-base).
                    forward = (into is pps, token_seq(c))
                    if forward not in forwards:
                        forwards.add(forward)
                        into.append(c.strip("\n"))
                    continue
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
    # A file that ends in an optimization state other than the reset (hrawanim.cpp's
    # `#pragma optimize("gsy", on)`: the ??_E it emits at the end of the unit takes
    # that state) sets the end of the unit, not the bodies composed after it: its
    # trailing pragmas, and the comments among them, follow every body, in file
    # order, so the files after it compile in the state they were verified in.
    deferred = []
    for f in files:
        last = max((at for at, (kind, _) in enumerate(parsed[f]) if kind not in ("body-pp", "tail")),
                   default=-1)
        run = [at for at in range(last + 1, len(parsed[f])) if (f, at) not in placed]
        pragmas = [parsed[f][at][1].strip() for at in run if parsed[f][at][0] == "body-pp"]
        if pragmas and not RESET_PRAGMA.match(pragmas[-1]):
            placed.update((f, at) for at in run)
            deferred.extend(parsed[f][at][1].strip("\n") for at in run)
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
                elif kind in ("tail", "body-pp", "body-decl"):
                    body.append(c.strip("\n"))
            continue
        name = (led or {}).get("name") or "(unledgered)"
        why = (f"matched in {f} (not merged yet)" if led and led["status"] == "matched"
               else "unmatched, no code, never credited")
        body.append(f"{MARK} {t['rva']} {t['size']}B {name} -- {why}")
    for f in files:   # a donor none of whose rows is approved here (cannot happen today)
        if f not in done:
            body.extend(c.strip("\n") for at, (kind, c) in enumerate(parsed[f])
                        if kind in ("def", "body-pp", "body-decl") and (f, at) not in placed)
    head = [f"// cl: {render_flags(flags)}"] if flags else []
    if any("// stlport" in texts[f] for f in files):
        head.append("// stlport")
    head.append(f"// TU {tu}: generated by tools/tu_skeleton.py from tu_map.csv (approved rows, retail order)")
    return "\n".join(head + pps) + "\n\n" + "\n\n".join(decls + body + trailing + deferred) + "\n"


# ---------------------------------------------------------------- verify
# A trial compile that spins must be refused, not waited on: cl.exe under Wine
# ran 50-115 min at 100% CPU on some composed candidates with no diagnostic
# (build/fleet/bulk/REPORT.md, 2026-10-30). The limit is far past every real
# compile and well short of the shortest observed hang.
COMPILE_TIMEOUT = 600.0   # seconds; BFME_COMPILE_TIMEOUT overrides it
TIMEOUT_REASON = "compile timeout"   # a candidate whose compile was killed is refused, never accepted
SEED_NOT_TRIED = "not tried: the seed is rejected under every flag set"


def compile_timeout():
    value = os.environ.get("BFME_COMPILE_TIMEOUT", "").strip()
    if not value:
        return COMPILE_TIMEOUT
    try:
        seconds = float(value)
    except ValueError:
        seconds = 0
    if seconds <= 0:
        raise ValueError(f"BFME_COMPILE_TIMEOUT must be a positive number of seconds, not {value!r}")
    return seconds


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
        self.timeout = compile_timeout()
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
        own = flags_of(text)
        keep = [t for t in own if not fd.MANAGED.match(t.replace("/", "-", 1) if t.startswith("/") else t)]
        line = "// cl: " + render_flags(["/" + t[1:] for t in tokens] + keep)
        if at is None:
            lines.insert(0, line)
        else:
            lines[at] = line
        return "\n".join(lines)

    def preprocessed(self, text, rows):
        """(cl -E output of `text` as matched() compiles it, None), or (None, why): the same
        scratch path and flags, -E in place of -c, so no object is written."""
        text = self.effective(text, rows)
        key = hashlib.sha1(text.encode()).hexdigest()[:16]
        src = self.tu.parent / f".{self.tu.stem}.{key}.tu_skeleton_pp{self.tu.suffix}"
        made = [d for d in reversed(src.parents) if not d.exists()]
        src.parent.mkdir(parents=True, exist_ok=True)
        src.write_text(text, encoding="utf-8", newline="")
        try:
            command, env = self.B.compiler_command(src, self.tmp / f"{key}.pp.obj")
            command = [c for c in command if not c.startswith(("-Fo", "/Fo")) and c not in ("-c", "/c")]
            command.insert(len(command) - 1, "-E")
            proc = subprocess.run(command, capture_output=True, env=env, cwd=str(ROOT), timeout=self.timeout)
        except (Exception, SystemExit) as error:          # noqa: BLE001 - no text is no proof
            return None, f"the preprocessor did not run: {error}"
        finally:
            _unlink_resilient(src)
            for d in reversed(made):
                try:
                    if not any(d.iterdir()):
                        d.rmdir()
                except OSError:
                    pass
        if proc.returncode:
            return None, "the preprocessor refused it: " + proc.stderr.decode("latin-1", "replace").strip()[-300:]
        return proc.stdout.decode("latin-1"), None

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
                    ok, msg, code = self.B.try_compile_source(src, obj, timeout=self.timeout)
            finally:
                _unlink_resilient(src)
                for d in reversed(made):
                    try:
                        if not any(d.iterdir()):
                            d.rmdir()
                    except OSError:
                        pass
            if ok:
                errors = []
            elif code == getattr(self.B, "TIMEOUT_STATUS", 124):
                errors = [TIMEOUT_REASON]     # the compile was killed: no diagnostics, and no acceptance
            else:
                errors = [l.strip() for l in (msg or "").splitlines() if " error " in l]
                # no ` error ` line (a crash, a Wine fault, a fatal message): its last lines, never
                # nothing (Merge lane 2, 2026-11-07: an empty `compile:` reason)
                errors = errors or [l.strip() for l in (msg or "").splitlines() if l.strip()][-3:] or [
                    f"the compiler exited {code} with no output"]
            # attempt() uses redefinition diagnostics to choose its next text.
            # A cached failure must restore its own errors, not the last trial's.
            self.cache[key] = (obj if ok else None, errors)
        obj, errors = self.cache[key]
        self.obj = obj          # the candidate's object, for LinkGuard.judge
        self.all_errors = list(errors)
        self.errors = self.all_errors[:3]
        out, missed = set(), set()
        if obj is None:
            return None
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            for r in rows:
                try:
                    res = self.B.compile_function(r, self.sm, obj)
                    (out if res["bytes"] == res["target"] else missed).add(r["target_rva"])
                except BaseException:   # build.py reports misses by SystemExit
                    missed.add(r["target_rva"])
        # An ICF address two rows share (one per donor) counts only when every row
        # there matches: one folded twin must not vouch for the other (./build.sh
        # checks each row).
        return out - missed


# ---------------------------------------------------------------- link guard
# link_check's index tables and where each entry keeps its object's position
LINK_TABLES = (("strong", lambda entry: entry), ("comdat", lambda entry: entry[0]),
               ("common", lambda entry: entry[0]), ("alternates", lambda entry: entry[0]))


COMPILER_WEAK_CHARACTERISTICS = 2       # all 7,300 weak externals in a 22,814-object census: search libraries


def compiler_weak_slots(data):
    """{name: default} of the weak externals in COFF `data` written as MSVC 7.1 writes a vftable slot: one
    aux record, Characteristics 2, `??_E<class>` defaulting to `??_G<class>` of the same class. A name with
    any other record of that name is left out: LINK leaves other Characteristics values unresolved."""
    import struct
    import link_census as LCe
    names = {symbol["index"]: symbol["name"] for symbol in LCe._coff_symbols(data)}
    table, count = struct.unpack_from("<II", data, 8)
    records, index = collections.defaultdict(list), 0
    while index < count:
        storage, aux = data[table + 18 * index + 16], data[table + 18 * index + 17]
        if storage == LCe.WEAK_EXTERNAL:
            tag, characteristics = struct.unpack_from("<II", data, table + 18 * (index + 1)) if aux == 1 else (None, None)
            records[names.get(index, "?")].append((names.get(tag), characteristics))
        index += 1 + aux
    return {name: found[0][0] for name, found in records.items()
            if len(found) == 1 and found[0][1] == COMPILER_WEAK_CHARACTERISTICS
            and name.startswith("??_E") and found[0][0] == "??_G" + name[len("??_E"):]}


def portable_comdat_contexts(data):
    """Exact copies whose relocations need no private or weak object context.

    The census digest normalizes local labels and does not encode weak defaults.
    It is not enough for moving existing debt. Compare raw bodies and ordinary
    undefined external references, from both authenticated old and new objects.
    A weak slot exactly as the compiler writes one (compiler_weak_slots) counts only
    with its default: a body of this object selected ANY. Its context then ends with
    ((weak name, (default, default's digest)), ...), for the guard to prove the
    route. Other kinds keep the existing refusal; this is deliberately a narrow proof.
    """
    import struct
    import link_census as LCe
    try:
        selections = LCe._comdat_selections(data)
        aliases = {m.group(1).decode("latin-1").strip('"')
                   for m in re.finditer(rb"/alternatename:([^=\s]+)=(\S+)", data, re.I)}
        weaks = {name for name, _ in LCe._weak_externals(data)}
        defaults = compiler_weak_slots(data)
        defined = {s["name"] for s in LCe._coff_symbols(data)
                   if s["storage"] == LCe.EXTERNAL and (s["section"] > 0 or s["value"] != 0)}
        sections = list(LCe._comdat_sections(data))
        selected_any = {symbol["name"]: digest for symbol, body, _relocs, digest, _ in sections
                        if body is not None and selections.get(symbol["section"]) == 2}

        def weak_slot(ref):
            """(default, its digest) of a weak relocation target proven by this object, or None."""
            default = defaults.get(ref["name"])
            if (ref["storage"] != LCe.WEAK_EXTERNAL or ref["section"] != 0 or ref["value"] != 0
                    or ref["name"] in aliases | defined or LCe._normal(ref["name"]) != ref["name"]
                    or default not in selected_any or default in aliases or LCe._normal(default) != default):
                return None
            return default, selected_any[default]
        result = {}
        for symbol, body, relocs, digest, _ in sections:
            if body is None or selections.get(symbol["section"]) != 2:  # IMAGE_COMDAT_SELECT_ANY
                continue
            slots = {ref["name"]: weak_slot(ref) for _, _, ref in relocs if ref["storage"] != LCe.EXTERNAL}
            if not all(slots.values()):
                continue
            if any(ref["name"] not in slots and (ref["section"] != 0 or ref["value"] != 0
                   or "definition" in ref or ref["name"] in aliases | weaks | defined
                   or LCe._normal(ref["name"]) != ref["name"]) for _, _, ref in relocs):
                continue
            result[(symbol["name"], digest)] = (symbol["value"], body,
                tuple((offset, kind, ref["name"]) for offset, kind, ref in relocs),
                *((tuple(sorted(slots.items())),) if slots else ()))
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

    def referenced_outside(self, names, places, merged, owned=True):
        """The `names` that an object other than the census objects at `places`
        (the ones this merge replaces) may still reference. `owned` False drops
        the ledger-owner rule: the names an outside object or alias reaches.

        view() drops the replaced objects' references only with per-object
        census provenance. An index --update-index refreshed keeps the
        aggregate graph alone, which still counts every reference a replaced
        object made, its references to its own definitions included:
        PartitionManager.cpp at census index 12902e9e1b refused eight donors
        over getClassMemoryPool guards that only the old seed object defined
        and referenced. A relocation can only name a symbol of its own
        object's table, and the index's touches hold every name an object
        defines, references (undefined and weak externals, their defaults) or
        holds as COMMON. So a name keeps a referrer when a ledger row owns it
        (the census keeps those), when the merged object references it
        (`merged`: its undefined and weak names), when an object outside
        `places` touches it (a unit gone since the census too: this merge does
        not replace it), when such an object has no touches record (a unit
        --update-index forgot refers to nothing; any other proves nothing), or
        when an /alternatename alias leads to it from an outside object's
        directive or from an alias one of those referrers names. Without the
        touches table every name keeps its referrer."""
        index, names = self.index, set(names)
        touches = index.get("touches")
        if not isinstance(touches, dict):
            return names
        owners = index["selection"].get("owners", {}) if owned else {}
        found = {n for n in names if n in owners}
        routes = collections.defaultdict(set)   # target -> aliases of a replaced object's directives
        for alias, entries in index["alternates"].items():
            for p, target in entries:
                if p in places:
                    routes[target].add(alias)
                else:
                    found.add(target)
        want, frontier = set(names), set(names)
        while frontier:
            frontier = set().union(*(routes.get(n, ()) for n in frontier)) - want
            want |= frontier
        found |= want & merged
        forgotten = index.get("forgotten", ())
        for p, name in enumerate(index["objects"]):
            if p in places or name in forgotten:
                continue
            held = touches.get(name)
            if held is None:
                return names
            found |= want & held
        # a referenced alias reaches every target a replaced directive routes it to
        frontier = set(found)
        while frontier:
            frontier = {target for target, aliases in routes.items() if aliases & frontier} - found
            found |= frontier
        return names & found

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
            else:
                # The aggregate still counts the replaced objects' own
                # references; judge() discounts them for dropped definitions.
                out["aggregate_references"] = True
            # A view has replaced providers and cannot itself serve as census
            # provenance, including when validation above failed.
            out["references"].pop("objects", None)
        return out

    def same_outside_order(self, files, places, merged, holder_rank):
        """A stale cohort slot still has exactly the current outside neighbours.

        A previously merged file can now start before its census slot. Moving
        within that empty gap is representable only when every cohort object
        is census-known and all live outsiders remain on the same side. The
        actual current rank still decides existing-copy exemptions.
        """
        import build
        names = {build.obj_path(build.ROOT / f).name for f in files}
        if len(places) != len(names) or any(self.position(f) is None or
                self.index["objects"][self.position(f)] != build.obj_path(build.ROOT / f).name
                for f in files):
            return False
        if any(name not in names and merged <= rank <= holder_rank
               for name, rank in self.rank.items()):
            return False
        first = min(places)
        for position, name in enumerate(self.index["objects"]):
            if position in places or position in self.gone:
                continue
            rank = self.rank.get(name)
            if rank is None or (position < first) != (rank < merged):
                return False
        return True

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
            # slot of its earliest census unit. An earlier current rank needs
            # proof that this slot has exactly the same outside neighbours.
            merged = None
            if self.rank is not None:
                merged = min((r for f in files if (r := self.rank.get(build.obj_path(build.ROOT / f).name)) is not None),
                             default=None)   # link_rank's names (build.row_object)
            holder = self.index["objects"][min(places)] if places else None
            placement_rank = self.rank.get(holder) if self.rank is not None else None
            if merged is not None and placement_rank is not None and merged < placement_rank:
                if self.same_outside_order(files, places, merged, placement_rank):
                    placement_rank = merged
                else:
                    why.append("a file without a census object or a changed outside order would place "
                               "the merged unit earlier in link order than the guard can judge")
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                found = LC.check_object(obj, view, self.truth)
                rank, previous = None, {}
                if places and self.rank is not None and view["objects"][min(places)] == obj.name:
                    if placement_rank is not None:
                        rank = dict(self.rank, **{obj.name: placement_rank})
                # Existing copies are exempt only where they keep their link place: a
                # file absorbed from a later place moves its copies earlier, which can
                # make another unit's copy lose (breaks_others judges those).
                for p in places:
                    if rank is not None and self.rank.get(self.index["objects"][p]) != rank[obj.name]:
                        continue
                    for name, digests in self.previous.get(p, {}).items():
                        previous.setdefault(name, set()).update(digests)
                breaks = LC.new_variants(obj, view, self.truth, previous, rank) if rank else []
                copies, defined, undefined, weaks = LCe.object_facts(obj, self.truth)
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
                lost = {n for n in dropped if not other(n) and LC.is_referenced(view, n)}
                if lost and view.get("aggregate_references"):
                    lost &= self.referenced_outside(lost, places, set(undefined) | {n for pair in weaks for n in pair})
                lost = sorted(lost)
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
        self.files = (source, tu)          # the objects the split replaces at their link places
        self.residual, self.residual_obj = residual, residual_obj
        self.carved, self.data_moved = set(carved), set(data_moved)
        self.expected_source = expected_source
        self.guard = LinkGuard(tu, root=root)
        self.before, self.cache = None, {}
        self.judged = {}                  # merged text -> its object (unit keys read its symbol table)
        self.provider, self.provider_found = None, []
        self.provider_lines = {}          # provider_failures' refusal lines -> the findings behind them

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
                             for f in self.files}
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

    def provider_failures(self, after, continues, moved):
        """ProviderGuard over the objects this split or shatter replaces (the baseline records) and `after`
        {source: object}; `continues` and `moved` as ProviderGuard.judge takes them."""
        if self.provider is None:
            self.provider = ProviderGuard(root=self.root, rows=self.rows)
        why = self.provider.load(self.guard.index)
        if why:
            return [f"provider guard: {why}"]
        before = {f: (self.records.get(f) or {}).get("obj") for f in self.files}
        try:
            self.provider_found = self.provider.judge(before, after, continues, moved)
        except ProviderUnknown as error:
            return [f"provider guard: {error}"]
        lines = provider_reasons(self.provider_found, limit=10)
        if lines:
            self.provider_lines[tuple(lines)] = self.provider_found
        return lines

    def provider_findings(self, lines):
        """The findings behind refusal lines provider_failures returned, else []."""
        return self.provider_lines.get(tuple(lines or ()), [])

    def view(self, records, rows, data):
        """Replace both affected objects and remap every index into true order."""
        import link_census as LCe
        import link_check as LC
        index = self.guard.index
        order = [p.name for p in LCe.link_order(rows, data)]
        if len(order) != len(set(order)):
            raise ValueError("split object-name collision")
        replacements = {r["obj"].name: r for r in records.values()}
        affected = {self.guard.position(f) for f in self.files} - {None}
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

        def weak_slot_proven(slot, default, digest):
            """Does weak `slot` land, before and after alike, on `default` with `digest`, the body the map
            selects and retail truth proves? Nothing may define or redirect the slot or its default, and no
            changed object may give the slot another default. Each read that fails refuses."""
            for view in (before, after):
                if (view["strong"].get(slot) or view["comdat"].get(slot) or view["common"].get(slot)
                        or view["alternates"].get(slot) or view["alternates"].get(default)):
                    return False
                found = state(view, default)
                if found[2] == "wrong" or found[3] != ("copy", digest, "retail"):
                    return False
            return not any(weak == slot and other != default
                           for record in (*self.records.values(), *records.values())
                           for weak, other in record["fact"][3])

        # The split view's reference graph is the census aggregate, which still
        # counts every reference the replaced objects made, the carved bodies'
        # own included: Rva0024A797Derived.cpp's destructors were refused over
        # private tables only they stored. Judge by the referrers the merge
        # guard uses: `consumers` keep a referrer outside the replaced objects,
        # in the split's own objects or among the ledger owners; `outsiders`
        # are reached by an object or alias outside the replaced objects.
        places = {self.guard.position(f) for f in self.files} - {None}
        merged = set().union(*(set(r["fact"][2]) | {n for pair in r["fact"][3] for n in pair}
                               | set(r["aliases"].values()) for r in records.values()))
        consumers = self.guard.referenced_outside(names, places, merged)
        outsiders = self.guard.referenced_outside(names, places, set(), owned=False)

        def own_row(view, name, holder):
            """The name's one definition after the split is its ledger owner's object."""
            definers = {at(e) for table, at in LINK_TABLES[:3] for e in view[table].get(name, ())}
            return (len(definers) == 1 and holder is not None
                    and holder in view["selection"]["owners"].get(name, ()))

        # The moved-copy check proves a moved copy's relocations for the outside objects that select it.
        # A copy with a private context (a referent its own object defines, or a NODUPLICATES function)
        # never has that proof, so a class that moved whole, destructor and tables byte-identical, was
        # always refused (lk83: Rva00493DEFDerived.cpp -> CashHackSpecialPower.cpp, Rva004BC4FCDerived.cpp
        # -> HealCrateCollide.cpp), though nothing else reached it. Such a copy answers to no outside
        # object when none (and no outside alias) reaches it, the destination's object is its only
        # definer after the split, no ledger row places it elsewhere, and it is not proven wrong; the
        # split objects that use it are judged by findings(). Its weak slots keep their route for every
        # other object: none reaches a slot, nothing defines or redirects a slot or its default, and the
        # changed objects give each slot the defaults they gave it before.
        destination = records[self.tu]["obj"].name if self.tu in records else None
        weak_before, weak_after = collections.defaultdict(set), collections.defaultdict(set)
        for weak, group in ((weak_before, self.records.values()), (weak_after, records.values())):
            for record in group:
                for slot, default in record["fact"][3]:
                    weak[slot].add(default)

        def moved_privately(name, new):
            definers = {after["objects"][at(e)] for table, at in LINK_TABLES[:3] for e in after[table].get(name, ())}
            owners = after["selection"]["owners"].get(name, set())
            if (name in outsiders or new[2] == "wrong" or destination is None or new[4] != destination
                    or definers != {destination} or not owners <= {destination}):
                return False
            slots = set()
            for record in (*self.records.values(), *records.values()):
                if name in {n for n, _, _, _ in record["fact"][0]} | set(record["fact"][1]):
                    roots, edges = record["references"]
                    # a kept section is a root: every root's references, a superset
                    slots |= set(edges[name] if name in edges else roots) & (weak_before.keys() | weak_after.keys())
            for slot in slots:
                if slot in outsiders or weak_before.get(slot) != weak_after.get(slot):
                    return False
                routed = {slot} | weak_before.get(slot, set()) | weak_after.get(slot, set())
                for view in (before, after):
                    if (view["strong"].get(slot) or view["comdat"].get(slot) or view["common"].get(slot)
                            or any(view["alternates"].get(n) for n in routed)):
                        return False
            return True

        failures = []
        for name in sorted(names):
            old, new = state(before, name), state(after, name)
            if (LC.is_referenced(before, name) and name in consumers and resolves(before, name)
                    and not resolves(after, name)):
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
                slots = dict(old_context[3]) if old_context and len(old_context) > 3 else {}
                for _, _, referent in old_context[2] if old_context else ():
                    if referent in slots:
                        safe_routes = safe_routes and weak_slot_proven(referent, *slots[referent])
                        continue
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
                if ((not safe_routes or old_context != context(after, new, name, records))
                        and not moved_privately(name, new)):
                    failures.append(f"moved selected COMDAT {name} lacks matching private/weak-free context")
            if name in self.guard.index["selection"]["exceptions"]:
                signature = lambda v: [(table, v["objects"][at(e)], *(() if table == "strong" else e[1:]))
                                       for table, at in LINK_TABLES[:2] for e in v[table].get(name, ())]
                if signature(before) != signature(after):
                    failures.append(f"changed /MAP selection for {name} needs measured evidence")
            elif (old[3] is not None and old[3] != new[3] and LC.is_referenced(before, name)
                  and not (old[2] == new[2] == "ok")
                  # a definition no one is left to reference, or a row whose only
                  # referrers and definers are the split's own objects
                  and not (new[3] is None and name not in consumers)
                  and not (name not in outsiders and new[2] != "wrong" and own_row(after, name, new[4]))):
                failures.append(f"selected implementation changes for {name}")
        return failures

    def judge(self, obj, files, text):
        if self.source not in files:
            return []  # greedy seed trial; judge both objects when the carve joins it
        if obj is not None:
            self.judged[text] = obj
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
            if not failures:
                failures = self.provider_failures(
                    {self.source: records[self.source]["obj"], self.tu: records[self.tu]["obj"]},
                    {self.source: [self.source], self.tu: [self.source, self.tu]},
                    {(self.source, rva): self.tu for rva in self.carved})
            if self.input_state() != self.inputs:
                failures.append("split compiler/ledger inputs changed during verification; retry")
            self.cache[key] = failures
            return failures
        except (OSError, ValueError, LCe.MissingObject) as error:
            return [f"split linking evidence unavailable: {error}"]


class ShatterLinkGuard(SplitLinkGuard):
    """SplitLinkGuard for a shatter: the mixed file leaves the link and every
    destination TU's final object takes its own place; all are judged together,
    so no intermediate residual has to link on its own."""

    def __init__(self, tus, source, moves, data_moves, root=ROOT, expected_source=None):
        super().__init__(tus[0], source, None, None, (), root=root, expected_source=expected_source)
        self.tus, self.moves, self.data_moves = list(tus), dict(moves), dict(data_moves)
        self.files = (source, *self.tus)

    def judge_records(self, records):
        """Why the shattered objects would not link, [] when they would.
        `records`: {tu: self.record(tu, obj, text)} of every destination's final object."""
        import link_census as LCe
        try:
            if self.before is None:
                return ["shatter linking baseline was not prepared"]
            if self.input_state() != self.inputs:
                return ["shatter compiler/ledger inputs changed during verification; retry"]
            if any(((self.root / f).read_bytes() if (self.root / f).exists() else None) != raw
                   for f, raw in self.original.items()):
                return ["shatter source changed during verification; retry"]
            owner = {rva: tu for tu, rvas in self.moves.items() for rva in rvas}
            rows = [dict(r, source=owner[r["target_rva"]]) if r["source"] == self.source and r["target_rva"] in owner
                    else r for r in self.rows]
            raw = (self.root / "reverse/data_rows.csv").read_bytes() if (self.root / "reverse/data_rows.csv").exists() else b""
            names = {n: tu for tu, ids in self.data_moves.items() if ids for n in data_row_names(raw, set(ids))}
            data = [dict(r, source=names[r["name"]]) if r["source"] == self.source and r["name"] in names else r
                    for r in self.data]
            after = self.view(records, rows, data)
            found = self.findings(after, records)
            failures = [f"{source}: a link-clean original would stop linking" for source, debt in found.items()
                        if source in self.debt and not self.debt[source] and debt]
            if self.source in self.debt and not self.debt[self.source] and any(found.values()):
                failures.append(f"{self.source}: a link-clean original's rows would stop linking")
            added = sum(found.values(), collections.Counter()) - sum(self.debt.values(), collections.Counter())
            failures += [f"new {kind}: {item}" for kind, item in sorted(added, key=str)]
            failures += self.outside_failures(after, records)
            if not failures:
                failures = self.provider_failures(
                    {u: r["obj"] for u, r in records.items()},
                    {u: [self.source] + ([u] if u != self.source else []) for u in records},
                    {(self.source, rva): tu for rva, tu in owner.items()})
            if self.input_state() != self.inputs:
                failures.append("shatter compiler/ledger inputs changed during verification; retry")
            return failures
        except (OSError, ValueError, LCe.MissingObject) as error:
            return [f"shatter linking evidence unavailable: {error}"]


# ---------------------------------------------------------------- provider guard
# P142 (round 18, 2026-11-12): merge e3e2807bd83 absorbed FamilyDeletingDtors_Rva006F8460.cpp, whose copy of
# ??_GRva006F8460 (the pool release) was the copy the real link kept. AptDisplayList.cpp, the merged unit,
# defines the same bytes, but the real link orders its inputs by path (exit_link ORDER "path"):
# Code/Libraries/Source/Apt/ comes after Code/GameEngine/Source/Common/Rva006F84C0DeletingDtor.cpp, whose
# private view's copy calls the global delete, and that copy won the image. LinkGuard models census
# (retail) order, where nothing changed. ProviderGuard judges, fail-closed, every symbol the objects a merge,
# split or shatter replaces define:
#   bytes             every definition a replaced object makes is still made by an object that continues
#                     it, and each continuing object's definition of the name equals every replaced
#                     definition it continues;
#   members disagree  the replaced objects' own definitions of a name already differ, so no object can
#                     continue all of them;
#   retail order,     under each order exit_link can link in (--order retail, --order path), the copy the
#   path order        link keeps of each such COMDAT, and of each COMDAT an outside object the change moves
#                     among the others holds, is the same before and after. The path clause is its own
#                     check (path_order_findings), to retire if the real link moves to --order retail.
# Objects outside the change are the census index's evidence, as in LinkGuard: one the index does not hold
# defines nothing here. A replaced object is what its file builds to today: the current build object, else a
# compile at its own path and flags. A refusal is header or reconciliation work, reported per unit with its
# names (provider_report).

PROVIDER_CLAUSES = ("members disagree", "bytes", "retail order", "path order")
ORDER_CLAUSES = ("retail order", "path order")


class ProviderUnknown(Exception):
    """An object the provider guard must read cannot be read or built: nothing is proven."""


# i386 relocation types and their operand widths (IMAGE_REL_I386_*): ABSOLUTE, DIR16, REL16, DIR32, DIR32NB,
# SECTION, SECREL, TOKEN, SECREL7, REL32. Any other type makes an extent unprovable (ProviderUnknown).
RELOCATION_WIDTH = {0x0: 0, 0x1: 2, 0x2: 2, 0x6: 4, 0x7: 4, 0xA: 2, 0xB: 4, 0xC: 4, 0xD: 1, 0x14: 4}


def _extent_definitions(data, sections, symbols):
    """{name: key} of the external definitions outside a COMDAT, by extent: from the symbol's value to the
    next definition of its section (in code, an external or a static function; in data, an external or a
    static: a label inside a function bounds nothing), else the section's end. Initialized: ("section",
    in code, extent, its bytes, every relocation whose operand overlaps it, named as the census digest names
    them, with the whole operand even past the extent's end: its addend); uninitialized:
    ("bss", in code, extent). COFF records no symbol size, so an extent can hold the alignment padding
    before the next definition; same_definition reads it that way."""
    import struct
    import link_census as LCe
    table = struct.unpack_from("<I", data, 8)[0]
    by_index = {s["index"]: s for s in symbols}

    def bounds(s, code):
        if s["storage"] == LCe.EXTERNAL:
            return True
        if s["storage"] != LCe.STATIC:
            return False                                          # a label, a file record, ...
        kind = struct.unpack_from("<H", data, table + 18 * s["index"] + 14)[0]
        return (kind & 0x30) == 0x20 if code else True            # IMAGE_SYM_DTYPE_FUNCTION in code
    starts = collections.defaultdict(set)
    for s in symbols:
        if 0 < s["section"] <= len(sections) and bounds(s, bool(sections[s["section"] - 1][4] & 0x20)):
            starts[s["section"]].add(s["value"])
    out = {}
    for s in symbols:
        number = s["section"]
        if s["storage"] != LCe.EXTERNAL or number <= 0 or number > len(sections):
            continue
        size, pointer, relocs, nrelocs, flags = sections[number - 1]
        if flags & LCe.COMDAT:
            continue
        code = bool(flags & 0x20)
        end = min((v for v in starts[number] if v > s["value"]), default=size)
        if not pointer:
            out[s["name"]] = ("bss", code, end - s["value"])
            continue
        found = []
        for at in range(relocs, relocs + 10 * nrelocs, 10):
            where, target, kind = struct.unpack_from("<IIH", data, at)
            if kind not in RELOCATION_WIDTH:
                raise ValueError(f"relocation type {kind:#x} in {s['name']}'s section: its operand width is unknown")
            width = RELOCATION_WIDTH[kind]
            if where < end and where + width > s["value"]:          # an operand that overlaps the extent
                referent = by_index.get(target, {"name": "?", "storage": 0})
                label = LCe._normal(referent["name"]) if referent["storage"] in (LCe.EXTERNAL, LCe.WEAK_EXTERNAL) \
                    else "local"
                # its whole operand (the addend), even where it runs past the extent's end
                found.append((where - s["value"], kind, label, bytes(data[pointer + where:pointer + where + width])))
        out[s["name"]] = ("section", code, end - s["value"], bytes(data[pointer + s["value"]:pointer + end]),
                          tuple(sorted(found)))
    return out


def same_definition(old, new):
    """Whether `new` continues the definition `old`: equal keys, or for an extent (_extent_definitions) one at
    least as long whose bytes and relocations over `old`'s extent are `old`'s and whose surplus is zero bytes
    with no relocation: the alignment padding a different next definition leaves, never a smaller
    allocation or a changed byte."""
    if old[0] != new[0] or old[0] not in ("section", "bss"):
        return old == new
    if old[1] != new[1] or new[2] < old[2]:
        return False
    if old[0] == "bss":
        return True
    return new[3][:old[2]] == old[3] and not any(new[3][old[2]:]) and new[4] == old[4]


def provider_definitions(obj):
    """{name: key} of every external definition the COFF object at `obj` makes, equal keys meaning one
    definition: a COMDAT by ("comdat", selection, census digest: link_census._comdat_sections, the digest
    the census index holds for every other object's copy), a COMMON by its size, an absolute by its value,
    anything else by _extent_definitions. Weak externals and /alternatename routes define nothing here.
    ProviderUnknown when the object cannot be read."""
    import struct
    import link_census as LCe
    try:
        data = Path(obj).read_bytes()
        count = struct.unpack_from("<H", data, 2)[0]
        optional = struct.unpack_from("<H", data, 16)[0]
        sections = [struct.unpack_from("<III", data, 20 + optional + i * 40 + 16)
                    + (struct.unpack_from("<H", data, 20 + optional + i * 40 + 32)[0],
                       struct.unpack_from("<I", data, 20 + optional + i * 40 + 36)[0]) for i in range(count)]
        symbols = LCe._coff_symbols(data)
        selections = LCe._comdat_selections(data)
        out = _extent_definitions(data, sections, symbols)
        for symbol, _body, _relocs, digest, _size in LCe._comdat_sections(data):
            out[symbol["name"]] = ("comdat", selections.get(symbol["section"]), digest)
        for s in symbols:
            if s["storage"] == LCe.EXTERNAL and s["section"] == 0 and s["value"]:
                out[s["name"]] = ("common", s["value"])
            elif s["storage"] == LCe.EXTERNAL and s["section"] == -1:
                out[s["name"]] = ("absolute", s["value"])
        return out
    except (OSError, TypeError, ValueError, IndexError, KeyError, struct.error) as error:
        raise ProviderUnknown(f"{Path(obj).name}: unreadable object ({error})") from error


class ProviderGuard:
    """See the block comment above. `orders(rows)` gives {clause: [object name, ...]} for each of
    ORDER_CLAUSES (default: the real link's, link_orders); tests pass their own."""

    def __init__(self, root=ROOT, index=None, rows=None, orders=None):
        self.root, self.index, self.rows = Path(root), index, rows
        self.orders = orders
        self.originals, self.cache = {}, {}
        self.before, self.before_paths = None, None
        self._objects, self._resolved = {}, {}
        self._initializers = self._places = self._data_objects = self._held = None

    def load(self, index):
        """The census index LinkGuard loaded: the reason the guard cannot judge, or None."""
        self.index = index
        if index is None:
            return "no census index (python3 tools/link_check.py --fetch-index)"
        if self.rows is None:
            import link_census as LCe
            self.rows = LCe.ledger()
        return None

    # -- the real link's two orders
    def object_of(self, row):
        """build.row_object, memoised per source (per member of a library)."""
        import build
        key = (row["source"], build.ledger_member(row) if row["source"].lower().endswith(build.LIB_SUFFIX) else None)
        if key not in self._objects:
            self._objects[key] = build.row_object(row)
        return self._objects[key]

    def resolved(self, path):
        """Path.resolve, memoised: it costs most of an order's time (2026-11-12: 36 of 51 s)."""
        if path not in self._resolved:
            self._resolved[path] = path.resolve()
        return self._resolved[path]

    def after_paths(self, rows, moved):
        """exit_link.expected_objects of `rows` (the ledger after `moved`) from the paths before: the
        same objects less those of sources left with no row and no data row, plus those of the moved
        rows' new sources, in path order."""
        import build
        import link_census as LCe
        if self._data_objects is None:
            self._data_objects = {self.resolved(build.obj_path(s)) for s in LCe.data_sources()}
        sources = {r["source"] for r in rows}
        gone = {self.resolved(build.obj_path(self.root / old)) for old, _ in moved if old not in sources}
        gone -= self._data_objects
        found = {self.resolved(p): p for p in self.before_paths if self.resolved(p) not in gone}
        for new in set(moved.values()):
            path = build.obj_path(self.root / new)
            found.setdefault(self.resolved(path), path)
        return sorted(found.values(), key=lambda path: path.as_posix())

    def link_orders(self, rows, paths=None):
        """{clause: [object name, ...]}: exit_link's inputs under --order retail and --order path for the
        ledger `rows`. Path order is exit_link.expected_objects (`paths` when the caller has them);
        retail order is exit_link.retail_object_order over the census places link_census.code_places
        computes from these rows."""
        if self.orders is not None:
            return self.orders(rows)
        import build
        import exit_link
        import image_report
        import link_census as LCe
        if paths is None:
            unique = {}
            for row in rows:
                unique.setdefault(self.resolved(self.object_of(row)), row)
            saved, exit_link.ORDER = exit_link.ORDER, "path"
            try:
                paths = exit_link.expected_objects(list(unique.values()))
            finally:
                exit_link.ORDER = saved
            self.before_paths = paths
        if self._initializers is None:
            self._initializers = image_report.Retail(build.EXE.read_bytes()).initializers()
        if self._places is None:
            self._places = {}
            for row in LCe.data_ledger():
                obj, rva = LCe.data_object(row).resolve(), LCe.data_rva(row)
                self._places[obj] = min(self._places.get(obj, (1, rva)), (1, rva))
        places = dict(self._places)
        places.update({self.resolved(obj): (0, rva) for obj, rva in LCe.code_places(rows, self.object_of).items()})
        retail = exit_link.retail_object_order(rows, paths, self._initializers, places)
        return {"retail order": [p.name for p in retail], "path order": [p.name for p in paths]}

    # -- the replaced objects
    def original(self, source):
        """The object `source` builds to today (None: no such file, nothing replaced): its current build
        object, else a compile at its own path and flags (Verifier), as SplitLinkGuard's baseline."""
        if source not in self.originals:
            import build
            path = self.root / source
            obj = None
            if path.exists():
                current = build.obj_path(path)
                if current.exists() and build.compile_is_current(path, current):
                    obj = current
                else:
                    v = Verifier(source)
                    v.matched(path.read_text(encoding="utf-8-sig", errors="replace"),
                              [r for r in self.rows if r["source"] == source])
                    obj = getattr(v, "obj", None)
                    if obj is None:
                        raise ProviderUnknown(f"{source} does not compile at its own path: "
                                              + " | ".join(v.errors)[:200])
            self.originals[source] = obj
        return self.originals[source]

    # -- the judgement
    def judge(self, before, after, continues, moved):
        """[(clause, name, detail)] for replacing the objects `before` {source: object or None} by `after`
        {source: object}; `continues` {after source: [before sources it continues]}; `moved`
        {(source, target_rva): new source} the ledger rows the change repoints."""
        import build
        defs_before = {s: provider_definitions(o) for s, o in before.items() if o is not None}
        defs_after = {s: provider_definitions(o) for s, o in after.items()}
        found = []
        for source, defs in sorted(defs_before.items()):
            heirs = [a for a, olds in continues.items() if source in olds]
            for name in sorted(defs):
                if not any(name in defs_after[a] for a in heirs):
                    found.append(("bytes", name, f"{source} defines it and no object continuing it does"))
        for heir, olds in sorted(continues.items()):
            for name, mine in sorted(defs_after[heir].items()):
                theirs = {s: defs_before[s][name] for s in olds if name in defs_before.get(s, {})}
                if len(set(theirs.values())) > 1:
                    found.append(("members disagree", name, f"{', '.join(sorted(theirs))} define it differently; "
                                                            f"{heir} keeps one"))
                elif theirs and not all(same_definition(old, mine) for old in theirs.values()):
                    found.append(("bytes", name, f"{heir}'s definition differs from {', '.join(sorted(theirs))}'s"))
        if self.before is None:
            self.before = self.link_orders(self.rows)
        key = tuple(sorted(moved.items()))
        if key not in self.cache:
            rows = [dict(r, source=moved[(r["source"], r["target_rva"])]) if (r["source"], r["target_rva"]) in moved
                    else r for r in self.rows]
            self.cache[key] = self.link_orders(rows, None if self.orders else self.after_paths(rows, moved))
        names_of = lambda sources: {s: build.obj_path(self.root / s).name for s in sources}
        objects = (names_of(defs_before), names_of(defs_after))
        names = set().union(*defs_before.values(), *defs_after.values())
        for clause in ORDER_CLAUSES:
            check = self.path_order_findings if clause == "path order" else self.order_findings
            found += check(clause, names, (defs_before, defs_after), objects, (self.before, self.cache[key]))
        return found

    def names_held(self, obj):
        """The COMDAT names the census index records the object named `obj` holding a copy of."""
        if self._held is None:
            self._held = collections.defaultdict(set)
            census = self.index["objects"]
            for name, copies in self.index["comdat"].items():
                for p, _, _ in copies:
                    self._held[census[p]].add(name)
        return self._held.get(obj, set())

    def kept(self, name, ours, objects, rank, replaced):
        """(object, digest) of the copy of COMDAT `name` the link keeps in the order `rank` {object: place},
        or None: the first definer among `ours` {source: definitions} at their objects and the census copies
        of every other object; "exclusive" when any definer is outside a COMDAT (no order decides it)."""
        copies = []
        for source, defs in ours.items():
            d = defs.get(name)
            if d is not None:
                if d[0] != "comdat" or d[1] == 1:       # outside a COMDAT, or NODUPLICATES: one definer
                    return "exclusive"
                copies.append((objects[source], d[2]))
        census = self.index["objects"]
        if any(census[p] not in replaced for p in self.index["strong"].get(name, ())):
            return "exclusive"
        copies += [(census[p], digest) for p, digest, _ in self.index["comdat"].get(name, ()) if census[p] not in replaced]
        linked = [c for c in copies if c[0] in rank]
        return min(linked, key=lambda c: rank[c[0]]) if linked else None

    def order_findings(self, clause, names, defs, objects, orders):
        """`clause` findings: a name whose kept copy (kept) changes from the order before to the order after.
        Besides `names` (the replaced and replacing objects' own), every name an outside object holds whose
        place among the other outside objects moves (retail order's initializer slots can reorder them when
        a merged object takes a slot): of two outside objects that swap, at least one moves. A copy no
        linked object keeps any more is the bytes clause's (a definition no object continues)."""
        replaced = set(objects[0].values()) | set(objects[1].values())
        before = {n: i for i, n in enumerate(orders[0][clause])}
        after = {n: i for i, n in enumerate(orders[1][clause])}
        outside = [n for n in orders[0][clause] if n not in replaced and n in after]
        was_at = {n: i for i, n in enumerate(outside)}
        moved = [n for i, n in enumerate(sorted(outside, key=after.__getitem__)) if was_at[n] != i]
        names = set(names).union(*(self.names_held(n) for n in moved))
        found = []
        for name in sorted(names):
            was = self.kept(name, defs[0], objects[0], before, replaced)
            now = self.kept(name, defs[1], objects[1], after, replaced)
            if was in (None, "exclusive") or now in (None, "exclusive") or now[1] == was[1]:
                continue
            found.append((clause, name, f"the link keeps {was[0]}'s copy {was[1]} today and {now[0]}'s {now[1]} "
                                        "after"))
        return found

    def path_order_findings(self, clause, names, defs, objects, orders):
        """The path-order clause on its own: exit_link's default --order path. Retire it (drop it from
        ORDER_CLAUSES) when the real link moves to --order retail."""
        return self.order_findings(clause, names, defs, objects, orders)


def provider_report(findings):
    """{clause: [names]} of provider findings, for a merge report and the adopt-and-merge queue."""
    out = collections.defaultdict(list)
    for clause, name, _ in findings:
        if name not in out[clause]:
            out[clause].append(name)
    return {clause: out[clause] for clause in PROVIDER_CLAUSES if clause in out}


def provider_reasons(findings, limit=3):
    """Short refusal lines: `provider <clause>: <name> (<detail>)`."""
    return [f"provider {clause}: {name} ({detail})" for clause, name, detail in findings[:limit]] + (
        [f"provider: {len(findings) - limit} more"] if len(findings) > limit else [])


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


def merge_plan_path(tu):
    return ROOT / "build/tu_skeleton/plans" / (hashlib.sha256(tu.encode("utf-8")).hexdigest() + ".json")


def merge_plan_state():
    # tree_state also hashes dirty and untracked source, including submodules. Its
    # per-process memo must be cleared between the dry run and a later merge call.
    picker_cache.reset()
    return picker_cache.tree_state(ROOT)


def merge_plan_inputs(sk, don, mixed, refused):
    raw = json.dumps([sk, don, mixed, refused], sort_keys=True, separators=(",", ":"))
    return hashlib.sha256(raw.encode("utf-8")).hexdigest()


# 2: rejection reasons carry the failing compile's own diagnostics (an earlier plan could hold an
# empty `compile:` reason, Merge lane 2, 2026-11-07); plans saved before are searched again.
PLAN_VERSION = 2
EMPTY_REASON = re.compile(r"\s*(?:compile|bytes|link)\s*:\s*")


def load_merge_plan(tu, state, inputs):
    return load_verified_plan(merge_plan_path(tu), state, inputs)


def load_verified_plan(path, state, inputs):
    if state is None:
        return None
    try:
        plan = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None
    if not isinstance(plan, dict):
        return None
    if (plan.get("version"), plan.get("state"), plan.get("inputs")) != (PLAN_VERSION, state, inputs):
        return None
    rejected = plan.get("rejected")
    if isinstance(rejected, dict) and any(isinstance(why, str) and EMPTY_REASON.fullmatch(why)
                                          for why in rejected.values()):
        try:                 # a reason with no diagnostic: the plan is stale, drop it and search again
            path.unlink()
        except OSError:
            pass
        return None
    return plan


def save_merge_plan(tu, state, inputs, plan):
    save_verified_plan(merge_plan_path(tu), state, inputs, plan)


def save_verified_plan(path, state, inputs, plan):
    if state is None or merge_plan_state() != state:
        return  # inputs changed during verification; a later apply must search again
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + f".{os.getpid()}.tmp")
    temporary.write_text(json.dumps({"version": PLAN_VERSION, "state": state, "inputs": inputs, **plan}),
                         encoding="utf-8")
    temporary.replace(path)


def reuse_merge_plan(tu, don, report, plan, dry_run):
    """Verify the saved winning unit once against today's bytes and link index.

    The search result is a hint, never verification: any failed check falls back
    to the ordinary search, which can choose a different donor set.
    """
    acc, text = plan.get("accepted"), plan.get("text")
    expected = plan.get("baseline")
    if (not isinstance(acc, list) or not acc or not all(isinstance(f, str) for f in acc)
            or len(acc) != len(set(acc))
            or not set(acc) <= set(don) or not isinstance(text, str)
            or not isinstance(expected, list) or not all(isinstance(x, str) for x in expected)
            or not isinstance(plan.get("rows"), int)
            or not isinstance(plan.get("rejected"), dict)
            or plan.get("verifier_flags") is not None and not isinstance(plan["verifier_flags"], str)):
        return None
    v = Verifier(tu, flags=plan.get("verifier_flags"))
    rows = [r for f in acc for r in don[f]]
    got = v.matched(text, rows)
    if got is None or not set(expected) <= got:
        return None
    guard = LinkGuard(tu)
    guard.load()
    linked = guard.linked(don)
    if (linked and guard.prepare(don)) or guard.judge(v.obj, acc, text):
        return None
    provider = ProviderGuard()
    try:
        if provider.load(getattr(guard, "index", None)) or provider.judge(
                {f: provider.original(f) for f in acc}, {tu: v.obj}, {tu: list(acc)},
                {(f, r["target_rva"]): tu for f in acc if f != tu for r in don[f]}):
            return None             # the search reports the provider findings
    except ProviderUnknown:
        return None
    texts = {f: relocate_includes((ROOT / f).read_text(encoding="utf-8-sig", errors="replace"),
                                 posixpath.dirname(f), posixpath.dirname(tu)) for f in acc}
    carry = Carry(ROOT, tu, acc, texts, text, plan.get("verifier_flags"))
    if carry.problems:
        return None
    why = map_regressions(tu, acc)
    if why:                  # not a stale plan: today's map would lose an approval either way
        report.update(accepted=acc, rejected=plan["rejected"], blocked=why)
        return report
    if plan.get("state") and merge_plan_state() != plan["state"]:
        return None  # a source changed during the final check
    report.update(accepted=acc, rejected=plan["rejected"], flags=plan.get("flags", []),
                  rows=plan["rows"], plan_reused=True, link_guard=(
                      f"census-linked: {', '.join(linked)}" if linked else "no file of this merge links at the census"))
    report.update(carry.report())
    if dry_run:
        report["text"] = text
        return report
    moved = apply(tu, acc, text, carry=carry)
    report["repointed"] = moved
    report["stage"] = "staged: " + " ".join([tu] + sorted(moved) + [f for f in acc if f != tu])
    report["subject"] = (f"Merge {len(acc)} files into {posixpath.basename(tu)} "
                         f"({plan['rows']} rows, tu_map approved TU, retail order)")
    return report


class NothingWritten(SystemExit):
    """A writer's refusal before its first write: no half-written tree to protect (marks_half_applied)."""


def marks_half_applied(writer):
    """Mark an exception leaving `writer` as `half_applied`: it may have written (give_back_after)."""
    @functools.wraps(writer)
    def wrapped(*args, **kw):
        try:
            return writer(*args, **kw)
        except NothingWritten:
            raise
        except BaseException as error:
            error.half_applied = True
            raise
    return wrapped


def merge(tu, dry_run=False, log=print, claim=True):
    state = merge_plan_state()
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    # The map's spelling names the TU; the file the tree has is the one to write. A
    # checkout can spell that path in another case (the map's `WW3D2/FXShaderSetup.cpp`
    # against a `WW3D2/fxshadersetup.cpp` holding its rows), and writing the map's
    # spelling beside it would collide with itself, so the merge works on the file's
    # spelling and never renames the file.
    canonical, tu = tu, tu_path(tu)
    if not (ROOT / tu).exists():        # no file in the tree: the ledger's own spelling
        tu = next((f for f in list(don) + list(mixed) if f.lower() == canonical.lower()), canonical)
    report = {"tu": canonical, "approved": len(sk), "mixed": mixed, "refused": refused, "accepted": [], "rejected": {}}
    if tu != canonical:
        report["tu_file"] = tu
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
    inputs = merge_plan_inputs(sk, don, mixed, refused)

    plan = load_merge_plan(canonical, state, inputs)
    if plan and plan.get("tu_file") != tu:
        plan = None
    scope = don
    if plan:
        accepted = plan.get("accepted")
        if (isinstance(accepted, list) and accepted
                and all(isinstance(f, str) for f in accepted)
                and len(accepted) == len(set(accepted)) and set(accepted) <= set(don)
                and (tu not in don or tu in accepted)):
            scope = {f: don[f] for f in accepted}
    taken = []          # each claim_scope result this merge holds: give_back releases exactly those
    try:
        if claim and not dry_run:
            held = claim_scope(tu, scope)
            if held:
                give_back(held)                           # the part of the scope we did win goes back
                report["blocked"] = held_message(held)
                return report
            taken.append(held)
        if plan:
            reused = reuse_merge_plan(tu, don, report, plan, dry_run)
            if reused is not None:
                if claim and not dry_run and "blocked" in reused:   # nothing was written
                    give_back(*taken)
                return view_hint(reused, tu, don)
        # A saved plan can fail its fresh byte, link or carry checks. Searching for
        # another cohort may touch rejected donors, so claim them before widening.
        if claim and not dry_run and scope != don:
            held = claim_scope(tu, don, skip=claim_keys(tu, scope))
            if held:
                give_back(*taken, held)
                report["blocked"] = held_message(held)
                return report
            taken.append(held)
        result = _merge(tu, sk, don, report, dry_run)
        saved = result.pop("_plan", None)
        if dry_run and saved and not result.get("blocked"):
            save_merge_plan(canonical, state, inputs, {"tu_file": tu, **saved})
        if claim and not dry_run and "blocked" in result:   # nothing was written
            give_back(*taken)
        return view_hint(result, tu, don)
    except BaseException as error:
        give_back_after(error, report, *taken)
        raise


def view_hint(report, tu, don):
    """A donor rejected for a compile error that a differing class view causes
    (a member missing or renamed, an overload or base not found, an access
    refused) or that names a class the TU's files each declare their own view
    of is pointed at tools/tu_views.py: it gives every file the same verified
    view, so the merge emits the class once."""
    if report.get("accepted") and not report.get("blocked"):
        import name_scoped
        handoff = name_scoped.related_work(tu, "consolidation")
        if handoff:
            report["scoped_naming"] = handoff
            report.setdefault("follow-up", []).append("Name locals/parameters while the TU context is loaded: "
                + handoff["command"] + ". " + handoff["instructions"])
    errors = [str(why) for why in report.get("rejected", {}).values() if str(why).startswith("compile")]
    if not errors:
        return report
    import tu_views
    shared = tu_views.shared_private(sorted(don), ROOT)
    viewish = any(re.search(r"error (C2039|C2065|C2511|C2248|C2504|C2653|C2660|C2027|C2079)\b", e) for e in errors)
    if not viewish:
        shared = [c for c in shared if any(re.search(r"\b" + re.escape(c) + r"\b", e) for e in errors)]
    if shared:
        report["reconcile_classes"] = shared     # all of them: merge_all charges each to the donors whose errors name it
        report["reconcile"] = (f"python3 tools/tu_views.py {tu} --dry-run, then without --dry-run: the donors "
                               f"declare their own views of {', '.join(shared[:4])}{', ...' if len(shared) > 4 else ''}"
                               " (docs/consolidation.md, \"Workflow per TU\", step 4)")
    return report


def _merge(tu, sk, don, report, dry_run, texts=None, applier=None, guard=None, fixed_text=None, deletes_donor=False,
           moved_rows=None, provider=None):
    """... `fixed_text`: the TU's final text is given (a split's --prepared), never composed:
    every accepted set is judged in it, under the same verifier, guard and applier.
    `deletes_donor`: `applier` deletes the accepted donors as a merge does (a prepared split's
    absorb), so the map is judged as for a merge (map_regressions). `moved_rows` {file: rvas}: what an
    `applier` that leaves its file in place moves, judged row by row."""
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
    # A merge, and a split that absorbs its whole donor, replaces its files' objects by the merged one:
    # ProviderGuard judges that here. A split's SplitLinkGuard and a shatter's run it over their objects.
    if provider is None and guard is not None and not hasattr(type(guard), "provider_failures"):
        provider = ProviderGuard()
    if provider is not None:
        why = provider.load(getattr(guard, "index", None))
        if why:
            report["blocked"] = f"provider guard: {why}"
            return report
    provider_found, provider_last = {}, {}
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
            if override_flags_key(e["flags"]) != override_flags_key(v.flags):
                report["rejected"][f] = f"its flag override '{e['flags']}' is not the carried '{v.flags}'"
        don = {f: r for f, r in don.items() if f not in report["rejected"]}
        ov = {f: e for f, e in ov.items() if f in don}
    base = {}
    for f in don:
        got = v.matched(texts[f], don[f])
        base[f] = got or set()
    if ov:   # nobody may lose a row its own build matches under the region default
        rv = Verifier(tu, region=True)
        if tu in don and tu not in ov:
            # the TU builds under its region default and a donor's override would cost it
            # rows: the TU keeps its default and the overridden donors stay out
            lost = (rv.matched(texts[tu], don[tu]) or set()) - base[tu]
            if lost:
                report["rejected"].update({f: f"its flag override '{e['flags']}' costs the TU file "
                                              f"{len(lost)} row(s) its region default matches"
                                           for f, e in sorted(ov.items())})
                return _merge(tu, sk, {f: r for f, r in don.items() if f not in ov}, report, dry_run,
                              texts, applier, guard, fixed_text, provider=provider)
        for f in [f for f in don if f not in ov and f != tu and base[f]]:
            lost = (rv.matched(texts[f], don[f]) or set()) - base[f]
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
    failed_errors = []      # attempt()'s: the diagnostics of the compile that decided a "compile" result

    def provider_why(files, obj):
        """ProviderGuard's refusal lines for `files` merged into `obj` ([] when it finds nothing)."""
        if provider is None:
            return []
        key = (tuple(files), str(obj))
        if key not in provider_found:
            try:
                provider_found[key] = provider.judge(
                    {f: provider.original(f) for f in files}, {tu: obj}, {tu: list(files)},
                    {(f, r["target_rva"]): tu for f in files if f != tu for r in don[f]})
            except ProviderUnknown as error:
                provider_found[key] = [("bytes", "(not judged)", str(error))]
        if provider_found[key]:
            provider_last[tuple(files)] = provider_found[key]
        return provider_reasons(provider_found[key])

    def attempt(files, flags):
        nonlocal failed_errors
        best = None
        failed_errors = []
        need = set().union(*(base[f] for f in files))
        rows = [r for f in files for r in don[f]]
        if fixed_text is not None:          # a prepared TU text: judged as it is, every baseline row in it
            got = v.matched(fixed_text, rows)
            if got is None:
                failed_errors = list(v.errors)
                return "compile"
            if not need <= got:
                return "bytes"
            why = guard.judge(getattr(v, "obj", None), files, fixed_text) if guard else []
            why = why or provider_why(files, getattr(v, "obj", None))
            if why:
                link_why[tuple(files)] = why
                return "link"
            return fixed_text
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
                why = why or provider_why(files, getattr(v, "obj", None))
                if not why:
                    return text
                link_why[tuple(files)] = why
                best = "link"   # matched, but a unit that links would stop linking
                continue
            if best is None and got is None:
                failed_errors = list(v.errors)  # a later strategy's compile must not stand in for this one's
            best = best or ("compile" if got is None else "bytes")
        return best

    def link_reason(files, f):
        found = provider_last.get(tuple(files))
        if found and link_why[tuple(files)] == provider_reasons(found):
            report.setdefault("provider", {})[f] = provider_report(found)
            return "provider: " + "; ".join(provider_reasons(found))[:300]
        if applier:
            found = guard.provider_findings(link_why[tuple(files)]) if hasattr(guard, "provider_findings") else []
            if found:
                report.setdefault("provider", {})[f] = provider_report(found)
            return "link: split residual/destination would regress: " + "; ".join(link_why[tuple(files)][:3])[:300]
        linked = guard.linked(files)
        whose = (f"{f} links at the census" if f in linked
                 else f"{f} never linked at the census and {', '.join(linked)} link")
        return f"link: {whose}; the merged object would not: " + "; ".join(link_why[tuple(files)][:3])[:300]

    def reject_reason(res, errors, files, f):
        if res == "link":
            return link_reason(files, f)
        if errors == [TIMEOUT_REASON]:      # a killed compile is no diagnostic list to quote
            return TIMEOUT_REASON
        return res + ("" if res == "bytes" else ": " + " | ".join(errors)[:300])

    tried = {}

    def tried_attempt(files, flags):
        """attempt(), once per (donor list, flags): accretion asks again for a set it
        already compiled (a bisected chunk whose first half was accepted)."""
        key = (tuple(files), tuple(flags))
        if key not in tried:
            res = attempt(files, flags)
            tried[key] = (res, list(failed_errors) if res == "compile" else list(v.errors))
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
            if tu in good:
                # a set whose seed is rejected cannot produce a merge (`tu not in acc` below):
                # stop before any donor is tried
                res, errors = tried_attempt([tu], flags)
                if res in ("compile", "bytes", "link"):
                    reason = reject_reason(res, errors, [tu], tu)
                    seed_error = seed_error or reason
                    rejected_seed = rejected_seed or (0, {tu: reason, **{f: SEED_NOT_TRIED for f in good if f != tu}})
                    continue
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

    first_sets = flag_sets[:3]
    if tu in good:      # the seed's own set first, as well as the three most popular: every accepted set holds the seed
        own = flags_of(texts[tu])
        seed_set = stl_static([x for x in own if not x.lower().startswith(("/i", "-i"))
                               and not v.fd.MANAGED.match(x.replace("/", "-", 1) if x.startswith("/") else x)] + incs)
        first_sets = [seed_set] + [f for f in first_sets if f != seed_set]
    trial(first_sets)
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
        return _merge(tu, sk, {f: r for f, r in don.items() if f not in ov}, report, dry_run, texts, applier, guard,
                      fixed_text, provider=provider)
    text = attempt(acc, flags)
    if text in ("compile", "bytes", "link"):   # the accepted set no longer re-verifies (a flaky compile, an ICE):
        report["rejected"].update(rej)          # never write the failure token as the TU's text
        report["blocked"] = (f"the accepted donors did not re-verify ({text}"
                             + (": " + " | ".join(failed_errors)[:300] if text == "compile" else "")
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
    why = (map_regressions(tu, moved_rows=moved_rows) if moved_rows
           else map_regressions(tu, acc) if applier is None or deletes_donor else None)
    if why:
        report["blocked"] = why
        return report
    if dry_run:
        if applier is None:
            report["_plan"] = {"accepted": acc, "text": text, "baseline": sorted(set().union(*(base[f] for f in acc))),
                               "verifier_flags": v.flags, "flags": flags, "rows": score,
                               "rejected": report["rejected"]}
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


def identify(rows, spans, scopes=None):
    """{row rva: [indices of candidate spans]} -- a definition that spells the
    row's name, else a macro invocation naming its class (or its method, for a
    free function) among the arguments; [] = unidentified. `scopes`
    (span_scopes) qualifies a free function inside `namespace X {}` as `X::f`,
    the way its mangled name (`?f@X@@`) spells it."""
    heads = [head_names(c) if k == "def" else None for _, _, c, k in spans]
    for i, h in enumerate(heads):
        q = scopes[i][-1] if scopes and scopes[i] else None
        if h and h[0] is None and q:
            heads[i] = (q, h[1])
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
    directly above it (a row's evidence or marker) with it. Definitions inside
    a `namespace {}` / `extern "C" {}` block are spans of their own (the block
    itself is not one), so a carve cuts them out of the block it leaves intact."""
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
    out = []
    for kind, c, at, _ in flat_chunks(text):
        if kind != "def":
            continue
        end = at + len(c)
        at = max(at, floor)
        inside = [m for m in macros if at <= m[0] < end]
        if inside:
            at = max(m[1] for m in inside)     # the glued macro lines precede the body
            rest = norm(text[at:end])
            if not rest or (AGGREGATE.match(rest)
                            and not re.search(r"\)\s*(const)?\s*$", rest.split("{")[0].strip())):
                continue           # what the glue hid was an aggregate: a declaration, not a body
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
    type declarations are declarations and may be repeated. Objects inside
    `namespace {}` / `extern "C" {}` blocks count, at their own offsets; one in
    an anonymous namespace is internal."""
    out = []
    for kind, c, at, scope in flat_chunks(text):
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
        internal = "" in scope or not external and (tokens[0] == "static" or
                                                    ("const" in tokens[:-1] and "*" not in declarator and "&" not in declarator))
        out.append((at, at + len(c), c, m.group(1), internal))
    return out


# a definition inside a block that the compiler emits only where used (COMDAT) or
# not at all: an inline body, a primary template, a dllimport inline
DUPLICABLE = re.compile(r"(?:^|\s)(?:inline|__forceinline|__inline)\b|^template\s*<\s*[^>\s]"
                        r"|__declspec\s*\(\s*dllimport")


def code_only(text):
    """Text with comments blanked and string/char literal contents removed."""
    t = strip(text)
    return re.sub(r"\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", "\"\"", t)


def names_used(ident, text):
    return re.search(r"(?<![\w.>])%s\b" % re.escape(ident), code_only(text)) is not None


ALTNAME_PRAGMA = re.compile(r'^[ \t]*#[ \t]*pragma[ \t]+comment[ \t]*\([ \t]*linker\b')
ALTNAME_SYMBOL = re.compile(r'[/-]alternatename:([^=\s"]+)=', re.I)


def symbol_used(name, text):
    """`name` spelled in code, member access included (`p->go()`, `x.go()`)."""
    return re.search(r"(?<![\w~])%s\b" % re.escape(name), code_only(text)) is not None


def altname_lines(text, spans=None):
    """[(start, end, symbol)] of the file-scope `#pragma comment(linker,
    "/alternatename:SYMBOL=TARGET")` lines naming one symbol each (a line naming
    several is left on both sides), outside every definition span."""
    spans = def_spans(text) if spans is None else spans
    out, at = [], 0
    for line in text.splitlines(keepends=True):
        start, at = at, at + len(line)
        if not ALTNAME_PRAGMA.match(line):
            continue
        symbols = ALTNAME_SYMBOL.findall(line)
        if len(symbols) == 1 and not any(a <= start < b for a, b, _, _ in spans):
            out.append((start, at, symbols[0]))
    return out


def cut(text, spans):
    """`text` without the given (start, end) spans."""
    out, pos = [], 0
    for start, end in sorted(spans):
        out.append(text[pos:start])
        pos = end
    out.append(text[pos:])
    return "".join(out)


def extern_macro_tokens(text, source=None, root=ROOT):
    """Tokens in reachable macros and header code, or None for an unchecked include.

    Follow quoted includes relative to their includer, then the explicit /I
    paths and Code include roots. Scan every branch; no expansion or macro-use
    inference is needed to conservatively retain a declaration. Header code can
    refer to a local class indirectly through a member or typedef, even when the
    source never spells the class name outside its definition.
    """
    pending = [(text, [posixpath.dirname(source or "")], False)]
    seen, tokens = set(), set()
    try:
        roots = [p.relative_to(root).as_posix() for p in (root / "Code").glob("*/Include")]
        roots = [f[2:].strip('"').replace("\\", "/") for f in flags_of(text)
                 if f.startswith(("/I", "-I")) and len(f) > 2] + roots
        while pending:
            current, parents, header_code = pending.pop()
            current = re.sub(r"\\\r?\n", "", current)
            code = code_only(current)
            if "##" in code:
                return None
            if header_code:
                tokens.update(re.findall(r"\b[A-Za-z_]\w*\b", code))
            for body in re.findall(r"^\s*#\s*define\s+[A-Za-z_]\w*(.*)$", code, re.M):
                tokens.update(re.findall(r"\b[A-Za-z_]\w*\b", body))
            for directive in re.findall(r"^\s*#\s*(?:include|import)\b([^\n]*)", strip(current), re.M):
                m = re.fullmatch(r'\s*(?:"([^"\n]+)"|<([^>\n]+)>)\s*', directive)
                if not m:
                    return None
                header = (m.group(1) or m.group(2)).replace("\\", "/")
                dirs = (parents if m.group(1) else []) + roots
                resolved = next((p for d in dirs
                                 if (p := ci_path(root, posixpath.normpath(posixpath.join(d, header))))
                                 and (root / p).is_file()), None)
                if resolved is None:
                    return None
                if resolved.lower() not in seen:
                    seen.add(resolved.lower())
                    pending.append(((root / resolved).read_text(encoding="utf-8-sig"),
                                    [posixpath.dirname(resolved)] + parents, True))
    except (OSError, UnicodeError):
        return None
    return tokens


def prune_unused_externs(text, source=None, root=ROOT, macros=None):
    """Drop only simple, unused extern-object declarations from a carved text.

    Search the entire remaining output, including helpers, initializers, inline
    bodies and directives. Ambiguous declarators and preprocessing stay intact.
    Includes after a declaration can hide a user; token pasting and line splicing
    can hide an identifier, so those contexts are deliberately left alone.
    """
    code = code_only(text)
    if re.search(r"^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b|##|\b__asm\b", code, re.M) \
            or re.search(r"\\\r?\n|\bR\"", text):
        return text
    macros = extern_macro_tokens(text, source, root) if macros is None else macros
    if macros is None:
        return text
    cuts = []
    for kind, c, at, _ in flat_chunks(text):
        if kind != "decl":
            continue
        # No initializer, function, attributes, templates or multiple declarators.
        m = re.fullmatch(r'extern\s+(?:"C"\s+)?(?:[A-Za-z_]\w*\s+)+'
                         r'(?:[*&]\s*(?:const\s+)?)?([A-Za-z_]\w*)'
                         r'\s*(?:\[\s*[0-9]*\s*\]\s*)*;', norm(c))
        if not m or m.group(1) in macros:
            continue
        end = at + len(c)
        if re.search(r"^\s*#\s*(?:include|import)\b", code_only(text[end:]), re.M):
            continue
        rest = code_only(text[:at] + text[end:])
        if not re.search(r"\b" + re.escape(m.group(1)) + r"\b", rest):
            # Preserve attached comments, including evidence and debt markers.
            blanked = COMMENT.sub(lambda m: " " * len(m.group(0)), c)
            start = re.search(r"\bextern\b", blanked).start()
            if any(m.group(0).startswith(("//", "/*")) for m in COMMENT.finditer(c[start:])):
                continue
            cuts.append((at + start, end))
    return cut(text, cuts)


def prune_unused_classes(text, source=None, root=ROOT, macros=None):
    """Drop namespace-scope class bodies a carved text names nowhere else.

    A carve leaves every shared declaration on both sides, so each unused body is one
    more duplicate definition. The contexts prune_unused_externs leaves alone stay, as
    do templated and declarator-bearing bodies, and bodies with a comment, which may
    be the only record of a retail fact.
    """
    code = code_only(text)
    if re.search(r"^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b|##|\b__asm\b", code, re.M) \
            or re.search(r"\\\r?\n|\bR\"", text):
        return text
    macros = extern_macro_tokens(text, source, root) if macros is None else macros
    if macros is None:
        return text
    while True:
        for kind, c, at, scope in flat_chunks(text):
            if kind != "decl" or scope:
                continue
            blanked = COMMENT.sub(lambda m: " " * len(m.group(0)), c)
            m = re.match(r"\s*(?:class|struct|union)\s+(?:__declspec\([^)]*\)\s*)?([A-Za-z_]\w*)\b[^;{()]*\{", blanked)
            if not m or m.group(1) in macros or not re.search(r"\}\s*;\s*$", blanked):
                continue
            head = len(blanked) - len(blanked.lstrip())
            if any(comment.start() >= head for comment in COMMENT.finditer(c)):
                continue
            end = at + len(c)
            if re.search(r"^\s*#\s*(?:include|import)\b", code_only(text[end:]), re.M):
                continue
            if re.search(r"\b" + re.escape(m.group(1)) + r"\b", code_only(text[:at] + text[end:])):
                continue
            newline = re.compile(r"\r?\n").match(text, end)
            text = cut(text, [(at + head, newline.end() if newline else end)])
            break
        else:
            return text


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


def carve(text, take, rowed=frozenset(), data_rowed=frozenset(), own=frozenset(), keep=frozenset(),
          altname_keep=False, source=None):
    """The definitions at span indices `take` leave the file.

    Both texts keep every preprocessor line and comment, and declarations except
    lexically unused simple extern objects. Definitions are never duplicated:
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
      * inside a `namespace {}` / `extern "C" {}` block the same rules hold per
        definition: both texts keep the block, the donor around the bodies that
        leave, the residual around the rest. A definition there that is not a
        row and that the compiler emits only where used (inline, a primary
        template, dllimport) stays on both sides, as the whole block used to; a
        helper in an anonymous namespace has internal linkage;
      * an external object in `own` that both sides use is defined by the
        carved side instead (--shatter picks one owner per shared object);
        spans in `keep` stay on both sides like the block definitions above;
      * a one-symbol `/alternatename` pragma line goes with the side whose
        bodies use the symbol (its name or its class); one both use stays on
        both (the hatch check refuses that growth), one neither uses stays in
        the residual, or with `altname_keep` in the donor."""
    spans = def_spans(text)
    scopes = span_scopes(text, spans)
    take = set(take)
    stay_all = set(range(len(spans))) - take
    shell = {i for i in stay_all if spans[i][3] == "def" and i not in rowed and scopes[i]
             and DUPLICABLE.search(norm(spans[i][2].split("{")[0]))} | (set(keep) & stay_all)
    carved_text = "\n".join(spans[i][2] for i in sorted(take | shell) if spans[i][3] != "data")
    copies = set()
    changed = True
    while changed:
        changed = False
        for i in sorted(stay_all - copies - shell):
            start, end, body, kind = spans[i]
            if kind != "def" or i in rowed:
                continue
            hn = head_names(body)
            if hn and (INTERNAL.search(norm(body.split("{")[0])) or "" in scopes[i]) \
                    and re.search(r"(?<![\w.>])%s\s*\(" % re.escape(hn[1]), code_only(carved_text)):
                copies.add(i)
                carved_text += "\n" + body
                changed = True
    leaving = take | copies | shell
    stay_text = "\n".join(spans[i][2] for i in sorted(stay_all) if spans[i][3] != "data")   # copies stay too
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
                datums.append((a, b, c, m.group(1), toks[0] == "static" or ("const" in toks[:-1] and "*" not in head)
                               or "" in scopes[i]))
    donor_cuts = [x for x in donor_cuts if not any(x == (a, b) for a, b, _, k in spans if k == "data")]
    for a, b, c, ident, internal in datums:
        used_out = names_used(ident, carved_text)
        used_in = names_used(ident, stay_text)
        if used_out and used_in:
            if ident in own and not internal:
                data_moved.append(ident)        # the carved side defines it (shatter's chosen owner)
                residual_cuts.append((a, b))
                continue
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
    # an /alternatename directive goes with the side whose bodies use its symbol: kept on
    # both it would count twice (hatch_counters rule 3); a wrong guess leaves the symbol
    # unresolved, which the split and shatter link guards report
    for a, b, symbol in altname_lines(text, spans):
        cls, meth = row_names(symbol)
        out_ = symbol_used(meth, carved_text) or bool(cls) and symbol_used(cls, carved_text)
        in_ = symbol_used(meth, stay_text) or bool(cls) and symbol_used(cls, stay_text)
        if out_ and not in_:
            residual_cuts.append((a, b))
        elif in_ and not out_:
            donor_cuts.append((a, b))
        elif not out_ and not in_:           # nobody's: it stays where it was (`altname_keep`: the donor)
            (residual_cuts if altname_keep else donor_cuts).append((a, b))
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
    macros = extern_macro_tokens(text, source)   # even defines in a body cut from this output
    if macros is not None:
        donor = prune_unused_externs(donor, source, macros=macros)
        residual = prune_unused_externs(residual, source, macros=macros)
        donor = prune_unused_classes(donor, source, macros=macros)
        residual = prune_unused_classes(residual, source, macros=macros)
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


def tu_path(tu, root=None):
    """`tu` as the tree spells the file, or `tu` itself when the tree has none.

    reverse/tu_map.csv names a TU, but a checkout can hold the same path in
    another case (`WW3D2/fxshadersetup.cpp` for the map's
    `WW3D2/FXShaderSetup.cpp`); the two spellings are one file, matched
    case-insensitively, and it is never renamed, so the merge seeds from and
    writes the file the tree has."""
    return ci_path(ROOT if root is None else root, tu) or tu


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


def c_ident(symbol):
    """The C identifier of an undecorated-C data symbol: exactly one decorating underscore
    goes (`__VertexBufferCount` is `_VertexBufferCount`, `___rtc_iaa` is `__rtc_iaa`)."""
    return symbol[1:] if symbol.startswith("_") else symbol


def debt_keys(path):
    """Identifiers of data-identity debt keyed to `path` (a carved body naming one would move the debt)."""
    out = set()
    reg = ROOT / "reverse/data_check_baseline.txt"
    if reg.exists():
        for line in reg.read_text(encoding="utf-8", errors="replace").splitlines():
            parts = line.split("\t")
            if len(parts) >= 3 and parts[0] == path:
                m = re.match(r"^\?([A-Za-z_]\w*)@", parts[2])
                out.add(m.group(1) if m else c_ident(parts[2]))
    return out


def breakdown(path):
    """{approved TU (the map's spelling): rows} of a file's matched rows, plus
    unplaced ones (and ICF aliases, fold_alias) under ''; an EH funclet counts with its parent."""
    if "approved_at" not in _CACHE:         # indexed once: the picker asks for every served split
        _CACHE["approved_at"] = {int(r["rva"], 16): r["tu"] for r in map_rows()
                                 if r["confidence"] == "approved" and r["kind"].startswith("code") and r["tu"]}
    approved = _CACHE["approved_at"]
    rows = file_rows(path)
    home = {r["name"]: "" if fold_alias(r) else approved.get(int(r["target_rva"], 16), "") for r in rows}
    dtors = {m.group(1): r["name"] for r in rows if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
    out = collections.defaultdict(list)
    for r in rows:
        p = parent_of(r, dtors)
        out[home[p] if p and p in home else home[r["name"]]].append(r)
    return out


def split_rows(path, tu):
    """(blocked reason or None, TU in the map's spelling, the file's rows approved for it, companions
    excluded) by the current map: --split's own precondition, and the picker's test that a served
    split decision is still alive."""
    rows = file_rows(path)
    if not rows:
        return "no matched rows in that file", tu, []
    groups = breakdown(path)
    tu = next((k for k in groups if k.lower() == tu.lower()), tu)
    dtors_all = {m.group(1): r["name"] for r in rows if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
    tu_rows = [r for r in groups.get(tu, []) if not parent_of(r, dtors_all)]
    # nothing spells an emission-held instantiation, so no carve moves it: it rides only with
    # carved bodies that emit it (split()'s riders)
    held = [r for r in tu_rows if emission_held(r)]
    tu_rows = [r for r in tu_rows if r not in held]
    if not tu_rows and held:
        return (f"no row of that file is approved for that TU: its {len(held)} row(s) there are implicit template "
                "instantiations placed by contiguity alone, which follow the file that emits them and block "
                "nothing (emission_held)"), tu, []
    if not tu_rows:
        return "no row of that file is approved for that TU", tu, []
    if len(groups.get(tu, [])) == len(rows):
        return "every row is this TU's (funclets included): use --merge", tu, tu_rows
    return None, tu, tu_rows


def placed_elsewhere(tu, own, assigned):
    """{basename: count} of the TU file's own rows that the map assigns to another TU.

    The rule donors() applies to the TU path in a merge: a row the map places nowhere
    stays in the seed, is moved by nothing and is re-verified, so only a row assigned
    to a different TU calls for a split first. A companion row lives where its parent lives,
    and an emission-held row where the file emitting it lives."""
    home = {r["name"]: None if assigned.get(int(r["target_rva"], 16)) not in (tu.lower(), None) and emission_held(r)
            else assigned.get(int(r["target_rva"], 16)) for r in own}
    dtors = {m.group(1): r["name"] for r in own if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}

    def placed(r):
        p = parent_of(r, dtors)
        return home[p] if p and p in home else home[r["name"]]
    return collections.Counter(placed(r).split("/")[-1] for r in own
                               if placed(r) not in (tu.lower(), None) and not fold_alias(r))


def split_plan_path(path, tu):
    key = hashlib.sha256(json.dumps([path, tu]).encode("utf-8")).hexdigest()
    return ROOT / "build/tu_skeleton/split_plans" / (key + ".json")


def reuse_split_plan(tu, don, report, plan, dry_run, guard, applier, state, moved_rows=None):
    """Reuse a composition, with fresh bytes and the complete two-object link guard."""
    acc, text = plan.get("accepted"), plan.get("text")
    expected = {r["target_rva"] for rows in don.values() for r in rows}
    baseline = plan.get("baseline")
    if (plan.get("tu_file") != tu or not isinstance(acc, list)
            or not all(isinstance(f, str) for f in acc) or len(acc) != len(set(acc))
            or set(acc) != set(don) or not isinstance(text, str)
            or not isinstance(baseline, list) or not all(isinstance(r, str) for r in baseline)
            or set(baseline) != expected or not isinstance(plan.get("rows"), int)
            or not isinstance(plan.get("flags"), list)
            or not all(isinstance(flag, str) for flag in plan["flags"])
            or not isinstance(plan.get("rejected"), dict)):
        return None
    v = Verifier(tu)
    rows = [r for f in acc for r in don[f]]
    got = v.matched(text, rows)
    if got is None or not expected <= got:
        return None
    guard.load()
    if guard.prepare(don) or guard.judge(v.obj, acc, text):
        return None
    if state is None or merge_plan_state() != state:
        return None
    why = map_regressions(tu, moved_rows=moved_rows) if moved_rows else None
    if why:                  # not a stale plan: today's map would lose an approval either way
        report.update(accepted=acc, rejected=plan["rejected"], blocked=why)
        return report
    report.update(accepted=acc, flags=plan["flags"], rows=plan["rows"],
                  rejected=plan["rejected"], plan_reused=True,
                  link_guard="split: residual and destination compared together")
    if dry_run:
        report["text"] = text
    else:
        moved = applier(tu, acc, text)
        report["repointed"] = moved
        report["stage"] = "staged: " + " ".join([tu] + sorted(moved) + [f for f in acc if f != tu])
    return report


def split(path, tu, dry_run=False, claim=True, prepared=None):
    """--split FILE --for TU [--prepared TU=TEXT]. `prepared`: the TU's whole final text,
    written with the carve in one transaction (as rename.py --prepared): the carved bodies
    are not appended, every moved row and every row the TU matched before must match in
    it, and a donor left with no row is absorbed (deleted, its keys repointed, as a merge
    does) instead of refused."""
    state = merge_plan_state()
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
    why, tu, tu_rows = split_rows(path, tu)
    if why and not (prepared is not None and tu_rows and why.startswith("every row is this TU's")):
        report["blocked"] = why          # (with a prepared text a whole donor is absorbed, as below)
        return report
    report["tu"] = tu                    # the map's spelling names the TU ...
    tu = tu_path(tu)                     # ... and the file the tree has is the one written beside it
    if tu != report["tu"]:
        report["tu_file"] = tu
    text = text0
    spans = def_spans(text)
    all_ids = identify(rows, spans, span_scopes(text, spans))   # every row of the file, not just this TU's
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
    if not keep and prepared is None:
        report["blocked"] = "no row would remain in the file: it is a whole donor, use --merge"
        return report
    data_rowed = data_rowed_idents(path)
    cv = carve(text, take, rowed, data_rowed, source=path)
    if cv.refused:
        report["blocked"] = cv.refused
        return report
    donor_text, residual = cv.donor, cv.residual
    report.update(copies=[head_names(spans[i][2]) for i in cv.copies], data_moved=cv.data_moved, externs=cv.externs)
    moved_hatches = (hatch_move(path, text, residual, tu, donor_text) if prepared is None
                     else prepared_hatches(path, text, residual, tu, prepared))
    if moved_hatches is None:
        report["blocked"] = "an escape-hatch count would grow (hatch_counters rule 3): a copied helper or datum carries one"
        return report
    report["hatches_move"] = bool(moved_hatches)
    donor_text = relocate_includes(donor_text, posixpath.dirname(path), posixpath.dirname(tu))
    # the residual first: it is the cheaper compile and the commoner failure
    v = Verifier(path)
    got = v.matched(residual, keep) if keep else set()
    residual_obj = v.obj if keep else None
    lost = sorted({r["target_rva"] for r in keep} - (got or set()))
    # An ICF alias no definition spells (an STLport COMDAT, an inline member) is
    # emitted by whatever body uses it; one only the carved bodies emitted rides
    # with them, as --shatter's riders do, and must then match beside the TU. So does an
    # emission-held instantiation (emission_held) the map places in this very TU: no carve
    # moves it, only the bodies emitting it.
    # A compiler-generated special member the map leaves homeless rides with the body that
    # emits its class's vtable (vtable_rider; P16's `??_G` 0x001E10CE): checked below
    # against both objects.
    riders = [r for r in keep if got is not None and r["target_rva"] in lost
              and (fold_alias(r) or emission_held(r) and assigned_tu(r) == tu.lower() or vtable_rider(r))
              and not all_ids.get(r["target_rva"]) and not parent_of(r)]
    if riders and {r["target_rva"] for r in riders} == set(lost) and \
            not any(r["target_rva"] in lost for r in keep if r not in riders):
        carved += riders
        keep = [r for r in keep if r not in riders]
        report["riders"] = [r["target_rva"] for r in riders]
        if not keep and prepared is None:
            report["blocked"] = "no row would remain in the file once its ICF aliases ride: use --merge"
            return report
        lost = []
    else:
        riders = []
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
    tu_own = file_rows(tu) if (ROOT / tu).exists() else []
    # with a prepared text the moved rows are judged in it, beside the TU's own rows
    alone = vt.matched(donor_text, carved) if prepared is None else vt.matched(prepared, tu_own + carved)
    if alone is None:
        report["blocked"] = (("the carved bodies do not compile beside the TU: " if prepared is None
                              else "the prepared TU text does not compile: ") + " | ".join(vt.errors)[:300])
        return report
    unemitted = [r["target_rva"] for r in riders if r["target_rva"] not in alone]
    if unemitted:
        report["residual_loses"] = unemitted
        report["blocked"] = "the residual loses ICF aliases the carved bodies do not emit matched either"
        return report
    rider_texts = None
    for r in riders:
        if vtable_rider(r) and not fold_alias(r):
            cls = deleting_class(r["name"])
            if not vtable_symbols(vt.obj, cls) or (residual_obj is not None and vtable_symbols(residual_obj, cls)):
                report["blocked"] = (f"{r['target_rva']} rides only with the body that emits {cls}'s vtable: the "
                                     "destination must emit it and the residual must not")
                return report
            if rider_texts is None:
                rider_texts = {tu: vt.preprocessed(donor_text, carved) if prepared is None
                               else vt.preprocessed(prepared, tu_own + carved),
                               path: rename.preprocess_unit(SimpleNamespace(root=ROOT, path=lambda rel: ROOT / rel), path)}
            why = hand_written_problem(r["name"], [vt.obj, residual_obj], rider_texts)
            if why:
                report["blocked"] = f"{r['target_rva']} may not ride: {why}"
                return report
    behind = [r for r in carved if r["target_rva"] not in alone]
    report["alone"] = f"{len(carved) - len(behind)}/{len(carved)} carved rows match beside the TU under its flags"
    if behind and prepared is not None:
        report["blocked"] = ("with a prepared TU text every moved row must match in it: "
                             + ", ".join(r["target_rva"] for r in behind[:5]))
        return report
    if behind:
        report["flag_bound"] = {r["target_rva"]: "matches only under the file's own flags" for r in behind}
        parents = {r["name"] for r in behind} | {m.group(1) for r in behind if (m := FUNCLET.match(r["name"]))}
        behind = [r for r in carved if r["name"] in parents or (m := FUNCLET.match(r["name"])) and m.group(1) in parents]
        carved = [r for r in carved if r not in behind and r not in riders]   # riders: the residual re-judges them
        take = {ids[r["target_rva"]][0] for r in carved if r["target_rva"] in ids and ids[r["target_rva"]]}
        if not take:
            report["blocked"] = "no carved row matches under the TU's flags"
            return report
        keep = [r for r in rows if r not in carved]
        if not keep:
            report["blocked"] = "no row would remain in the file after the flag-bound rows stayed: use --merge"
            return report
        cv = carve(text, take, rowed, data_rowed, source=path)
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
        elsewhere = placed_elsewhere(tu, own, _CACHE["assigned"])
        if elsewhere:
            report["blocked"] = ("TU path exists and holds rows the map places in another TU (split it first): "
                                 + ", ".join(f"{k} {n}" for k, n in elsewhere.most_common()))
            return report
        don[tu] = own
    report.update(approved=len(sk), accepted=[], rejected={})
    # a prepared text is the TU's final text: the carved rows are judged in it, not appended
    texts = {path: donor_text if prepared is None else prepared}
    whole = prepared is not None and not keep          # nothing stays: the donor is absorbed
    inputs = merge_plan_inputs(sk, don, texts, {"residual": residual,
                              "data_moved": cv.data_moved, "hatches_move": report["hatches_move"]})
    guard = (LinkGuard(tu) if whole else
             SplitLinkGuard(tu, path, residual, v.obj, [r["target_rva"] for r in carved],
                            data_moved=cv.data_moved, root=ROOT, expected_source=original_bytes))
    tu_text = (ROOT / tu).read_text(encoding="utf-8-sig", errors="replace") if (ROOT / tu).exists() else ""

    def absorb(tu_, acc, text_):
        """A whole donor with a prepared TU text: merge's apply, which deletes the donor and
        repoints every path-keyed column and protected register (Carry)."""
        carry = Carry(ROOT, tu_, [tu_, path], {tu_: tu_text, path: text}, text_)
        if carry.problems:
            raise UnitKeyRefusal("; ".join(carry.problems[:3]))
        moved = apply(tu_, [tu_, path], text_, carry=carry)
        report.update(carry.report())
        return moved

    def unit_keys(text_):
        """The residual and the merged TU's objects decide where path's unit keys go."""
        dr = ROOT / "reverse/data_rows.csv"
        raw = dr.read_bytes() if dr.exists() else None
        if raw is not None and cv.data_moved:
            names = data_row_names(raw, set(cv.data_moved))
            raw = repoint_rows(raw, "reverse/data_rows.csv", "name", names, "source", path, tu)[0] if names else raw
        return carry_unit_keys(path, {path: v.obj, tu: guard.judged.get(text_)},
                               (getattr(guard, "records", None) or {}).get(path, {}).get("obj"), raw)

    def applier(tu_, acc, text_):
        keys = unit_keys(text_)
        if keys.problems:
            raise UnitKeyRefusal("; ".join(keys.problems[:3]))
        moved = apply_split(tu_, text_, path, residual, [r["target_rva"] for r in carved], report["hatches_move"],
                            data_moved=cv.data_moved, extra=keys.raws)
        report["carried"] = dict(keys.moved)
        return moved

    def run():
        moved_rows = None if whole else {path: [r["target_rva"] for r in carved]}
        try:
            plan = load_verified_plan(split_plan_path(path, tu), state, inputs) if prepared is None else None
            if plan:
                reused = reuse_split_plan(tu, don, report, plan, dry_run, guard, applier, state, moved_rows=moved_rows)
                if reused is not None:
                    return reused
            return _merge(tu, sk, don, report, dry_run, texts=texts, applier=absorb if whole else applier,
                          guard=guard, fixed_text=prepared, deletes_donor=whole, moved_rows=moved_rows)
        except UnitKeyRefusal as refused_keys:
            report["blocked"] = f"unit keys (data_ledger.csv / fold proofs): {refused_keys}"[:400]
            return report

    if claim and not dry_run:
        held = claim_scope(tu, {path: carved})
        if held:
            give_back(held)
            report["blocked"] = held_message(held)
            return report
        try:
            report = run()
        except BaseException as error:
            give_back_after(error, report, held)
            raise
        if "blocked" in report:
            give_back(held)
    else:
        report = run()
    if dry_run and "blocked" not in report and path in report.get("accepted", []) and whole:
        problems = Carry(ROOT, tu, [tu, path], {tu: tu_text, path: text}, prepared).problems
        if problems:
            report["blocked"] = "protected registers: " + "; ".join(problems[:3])[:300]
    elif dry_run and "blocked" not in report and path in report.get("accepted", []):
        keys = unit_keys(report.get("text", ""))
        if keys.problems:
            report["blocked"] = "unit keys (data_ledger.csv / fold proofs): " + "; ".join(keys.problems[:3])[:300]
        elif keys.moved:
            report["carried"] = dict(keys.moved)
        if state is not None and prepared is None and "blocked" not in report and isinstance(report.get("text"), str):
            save_verified_plan(split_plan_path(path, tu), state, inputs, {
                "tu_file": tu, "accepted": report["accepted"], "text": report["text"],
                "baseline": sorted({r["target_rva"] for f in report["accepted"] for r in don[f]}),
                "rows": report["rows"], "flags": report["flags"], "rejected": report["rejected"]})
    if path not in report.get("accepted", []):
        report.setdefault("blocked", "the carved bodies do not verify in the TU: "
                          + str(report.get("rejected", {}).get(path, ""))[:300])
    elif not dry_run and "blocked" not in report:
        report["subject"] = (f"Move {len(carved)} rows of {posixpath.basename(path)} into {posixpath.basename(tu)}, "
                             "which takes a prepared text (tu_map approved TU; the donor is absorbed)" if whole else
                             f"Split {len(carved)} rows of {posixpath.basename(path)} into "
                             f"{posixpath.basename(tu)} (tu_map approved TU, retail order"
                             + ("; prepared TU text)" if prepared is not None else ")"))
        trailer = carry_trailer("--split", path, tu, report["hatches_move"], report.get("carried", {}))
        if trailer:
            report["trailer"] = trailer
    return report


class UnitKeyRefusal(Exception):
    """A split's unit keys cannot be carried (unit_key_carry problems): nothing was written."""


# ---------------------------------------------------------------- emission move
# The move counterpart of emission_held. A compiler-generated COMDAT has no body a carve could
# move: every object using it emits it. Once its approved TU's own code emits it byte-exact,
# the row's source moves there and no text moves at all. Only a deleting destructor
# (`??_G`/`??_E`) qualifies: its decorated name, and then no sign of a hand-written copy
# (hand_written_problem: `__identifier` can spell the name, review of 87417c8f9f). A
# constructor, destructor or assignment never does: a hand-written one (`typedef Rec Alias;
# Alias(Rec const &r) : a(r.a) {}`) compiles to the implicit one's name, bytes and relocations
# (review of 9459886c66). Nor does a template instance (review of 0c8c510c89): eight rounds
# showed text cannot prove one compiler-instantiated from vendored source (`typedef C<int>
# Alias; void Alias::f() {}`, a project `#line` naming an STLport header, `namespace _STL`
# reopened with a template of STLport's name), and `#line` rewrites the debug line info
# CodeView could anchor on. Either may come back with a provenance proof that does not
# depend on text.

# `??_G` (scalar) / `??_E` (vector) deleting destructor of a plain class
DELETING_DTOR = re.compile(r"^\?\?_[GE]([A-Za-z_]\w*)@@[QU]AEPAXI@Z$")


def deleting_class(name):
    """The class whose compiler-generated deleting destructor `name` is, from the decorated
    name alone, else None."""
    m = DELETING_DTOR.match(name)
    return m.group(1) if m else None


def emission_problem(r):
    """Why row `r` may not move by emission by its name, or None: only a deleting destructor
    may (deleting_class). emit_move then requires that no copy is hand-written
    (hand_written_problem)."""
    name = r["name"]
    if deleting_class(name):
        return None
    if TEMPLATE_INSTANCE.match(name):
        return ("a template instance: whether it was instantiated from vendored source or written by hand "
                "cannot be proved from text, so it does not move by emission")
    return "not a deleting destructor (??_G/??_E) by its name: only those move by emission"


# What the decorated name cannot prove (review of 87417c8f9f): `extern "C" void
# __identifier("??_GRec@@UAEPAXI@Z")() {}` compiles to a COMDAT of exactly that name. Two
# layered checks, both required, fail-closed. Measured under Wine with MSVC 7.1 /O2: the
# compiler selects an implicit `??_G`/`??_E` ANY in a code section; a hand-written
# `__identifier` definition gets NODUPLICATES, but an `inline` or `__forceinline` one gets
# ANY too, and selectany data under the name gets ANY in a data section.
SELECTION = {1: "NODUPLICATES", 2: "ANY", 3: "SAME_SIZE", 4: "EXACT_MATCH", 5: "ASSOCIATIVE", 6: "LARGEST"}


def deleting_copy_problem(obj, name):
    """Why `obj`'s copy of the deleting destructor `name` may be hand-written, or None (also when
    `obj` defines no copy): every definition must sit in a code section's COMDAT selected ANY,
    as the compiler's own does."""
    import struct
    import link_census as LCe
    try:
        data = Path(obj).read_bytes()
        count = struct.unpack_from("<H", data, 2)[0]
        optional = struct.unpack_from("<H", data, 16)[0]
        selections = LCe._comdat_selections(data)
        for s in LCe._coff_symbols(data):
            if s["name"] != name or s["storage"] != LCe.EXTERNAL or not 0 < s["section"] <= count:
                continue
            flags = struct.unpack_from("<I", data, 20 + optional + (s["section"] - 1) * 40 + 36)[0]
            if not flags & 0x20:                                      # IMAGE_SCN_CNT_CODE
                return f"{Path(obj).name} defines it outside a code section"
            if not flags & LCe.COMDAT:
                return f"{Path(obj).name} defines it outside a COMDAT"
            selection = selections.get(s["section"])
            if selection != 2:
                return (f"{Path(obj).name} selects its COMDAT {SELECTION.get(selection, selection)}, not ANY as the "
                        "compiler does: a hand-written definition")
    except (OSError, ValueError, IndexError, KeyError, struct.error):
        return f"{Path(obj).name if obj else 'its object'} cannot be read"
    return None


def _paren_end(text, at):
    """The index after the parenthesis closing the one at `at`, or None."""
    depth = 0
    for i in range(at, len(text)):
        depth += {"(": 1, ")": -1}.get(text[i], 0)
        if depth == 0:
            return i + 1
    return None


TRIGRAPHS = {"=": "#", "/": "\\", "'": "^", "(": "[", ")": "]", "!": "|", "<": "{", ">": "}", "-": "~"}


def translation_phases(text):
    """`text` as the compiler reads it after translation phases 1 and 2: each of the nine
    trigraphs replaced by its character and each backslash-newline spliced away. cl -E leaves
    both (review of 329404caeb: in `"??/""` the `??/` is a backslash, so the literal holds a
    quote, and masking the raw text lost quote sync and hid an `__identifier` definition).
    Decorated names keep their `??_G`, `??4`, `??$`: no trigraph ends in a letter, digit, `_`
    or `$`, and none of the nine characters a trigraph yields can appear in one."""
    text = re.sub(r"\?\?([=/'()!<>-])", lambda m: TRIGRAPHS[m.group(1)], text)
    return re.sub(r"\\\r?\n", "", text)


def mask_code(text):
    """`text` (read as translation_phases leaves it) with every index kept: each directive line and comment blanked, and each string or
    character literal's characters between its quotes replaced by `x`, so no bracket, quote or
    token inside one is read as code (review of f11be8ac37: `(const char *p = ")") {}` hid a
    body); None when a literal or comment does not close, as nothing after it can be read."""
    out, n, i, line_start = list(text), len(text), 0, True
    while i < n:
        c = text[i]
        if c == "\n":
            line_start, i = True, i + 1
            continue
        if c in " \t\r\f\v":
            i += 1
            continue
        if line_start and c == "#":                          # a directive cl -E left (`#line`, `#pragma`)
            j = i
            while j < n and text[j] != "\n":
                j += 2 if text[j] == "\\" and text[j + 1:j + 2] == "\n" else 1
            out[i:j] = [ch if ch == "\n" else " " for ch in text[i:j]]
            i = j
            continue
        line_start = False
        if text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            out[i:j] = " " * (j - i)
            i = j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            if j < 0:
                return None
            out[i:j + 2] = [ch if ch == "\n" else " " for ch in text[i:j + 2]]
            i = j + 2
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                if text[j] == "\n":
                    return None
                j += 2 if text[j] == "\\" else 1
            if j >= n:
                return None
            out[i + 1:j] = "x" * (j - i - 1)
            i = j + 1
        else:
            i += 1
    return "".join(out)


# What may follow an `__identifier(...)` naming a row, once any `)` are skipped: the only shapes
# master's 383 `??_G`/`??_E` spellings take (review of f11be8ac37: `;`/`,` 178, `()` 199,
# `(void)` 3, `)` 2, `[]` 1). Anything else, a parameter list with content, a default, a `{`
# before the terminator, is no proof the name is only declared or referenced.
ALLOWED_AFTER = re.compile(r"\s*(?:[;,}]|\(\s*(?:void\s*)?\)\s*[;,]|\[\s*\]\s*[;,=])")


def identifier_definition(code, name):
    """The `__identifier(...)` in the preprocessed `code` that may define `name`, or None. Every
    one whose argument is `name`'s literal, or is not one plain literal (an escape, adjacent
    literals, a prefix: it cannot be read), must be followed, after any `)`, by exactly one of
    the shapes ALLOWED_AFTER admits, read on the masked text (mask_code) of the text the compiler
    reads (translation_phases); a text that cannot be masked, or an unbalanced argument,
    refuses. A positive allowlist: eleven rounds showed a blocklist of declarator shapes keeps
    leaking."""
    code = translation_phases(code)
    if "__identifier" not in code:
        return None
    masked = mask_code(code)
    if masked is None:
        return "an unterminated literal or comment: the unit cannot be read"
    for m in re.finditer(r"\b__identifier\s*\(", masked):
        spelled = " ".join(code[max(0, m.start() - 30):m.start() + 120].split())
        end = _paren_end(masked, m.end() - 1)
        if end is None:
            return spelled
        literal = re.fullmatch(r'"([^"\\]*)"', code[m.end():end - 1].strip())
        if literal is not None and literal.group(1) != name:
            continue
        i = end
        while i < len(masked) and (masked[i].isspace() or masked[i] == ")"):
            i += 1
        if not ALLOWED_AFTER.match(masked, i):
            return spelled
    return None


def hand_written_problem(name, objs, texts):
    """Why the deleting destructor `name` may be hand-written: a copy in one of `objs` not
    selected as the compiler's (deleting_copy_problem), or a `__identifier` definition in one
    of `texts` ({unit: (preprocessed text or None, why)}), or None."""
    for obj in objs:
        if obj is not None:
            why = deleting_copy_problem(obj, name)
            if why:
                return why
    for unit, (code, why) in texts.items():
        if code is None:
            return f"{unit} cannot be preprocessed ({why}): no proof it does not define it by hand"
        found = identifier_definition(code, name)
        if found:
            return f"{unit} (preprocessed) may define it by hand: `{found[:100]}`"
    return None

# The transfer proof (P16 v2 step 5): a prepared transaction may move a row its name alone does not
# admit, on what the objects show rather than on any reading of the text. The row is no claim about
# who wrote the body: after the move its one emitter among these units is the unit the map approves.
# Every fact comes from a compile of this transaction (fresh_compiles); anything that cannot be read
# refuses. Under /Gy a plain function is a COMDAT section too, but selected NODUPLICATES, so a
# COMDAT here means selected ANY in code: a real body goes through --split or --merge.
@contextlib.contextmanager
def fresh_compiles():
    """No object store for this block's compiles, in this process or a build it starts: every object
    is compiled now, never restored (build._restore_object)."""
    import build
    saved = os.environ.get("BFME_OBJSTORE")
    os.environ["BFME_OBJSTORE"] = "off"
    build._objstore_root.cache_clear()
    try:
        yield
    finally:
        if saved is None:
            os.environ.pop("BFME_OBJSTORE", None)
        else:
            os.environ["BFME_OBJSTORE"] = saved
        build._objstore_root.cache_clear()


def coff_layout(data):
    """(sections, symbols {table index: record}) of the i386 COFF object `data`, every table and each
    section's raw data and relocations held to the file's bounds whether or not anything goes on to
    read them; ValueError or struct.error otherwise (unpack_from holds whatever it reads to the file).
    cl always writes sections and symbols, so an object with none did not come from a compile: it is
    malformed, never an empty object."""
    import struct
    if len(data) < 20 or data[:2] != b"\x4c\x01":
        raise ValueError("not an i386 object")
    _machine, count, _stamp, at, total, optional, _flags = struct.unpack_from("<HHIIIHH", data, 0)
    table, strings = 20 + optional, at + total * 18
    if not count or not total:
        raise ValueError("no sections or no symbols")
    size = struct.unpack_from("<I", data, strings)[0]
    if size < 4 or strings + size > len(data):
        raise ValueError("the string table lies outside the object")
    sections = []
    for i in range(count):
        name, _vsize, _va, raw_size, raw_at, relocs_at, lines_at, relocs, lines, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, table + i * 40)
        if flags & 0x01000000:
            raise ValueError("a relocation count that overflowed its field")
        has_raw = not flags & 0x80                                       # uninitialized data has none
        if (has_raw and raw_size and not raw_at) or (has_raw and raw_at + raw_size > len(data)) \
                or lines_at + lines * 6 > len(data):
            raise ValueError("a section lies outside the object")
        sections.append({"name": name.rstrip(b"\0"), "size": raw_size, "raw": data[raw_at:raw_at + raw_size] if has_raw else b"",
                         "relocs": [struct.unpack_from("<IIH", data, relocs_at + k * 10) for k in range(relocs)], "flags": flags})
    symbols, i = {}, 0
    while i < total:
        raw, value, section, _type, storage, aux = struct.unpack_from("<8sIhHBB", data, at + i * 18)
        if i + 1 + aux > total or section > count:
            raise ValueError("a symbol lies outside the object")
        if raw[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", raw, 4)[0]
            if offset >= size:
                raise ValueError("a symbol name lies outside the string table")
            name = data[strings + offset:data.index(b"\0", strings + offset)]
        else:
            name = raw.rstrip(b"\0")
        symbols[i] = {"name": name.decode("latin-1"), "value": value, "section": section, "storage": storage,
                      "association": None}
        if aux and storage == 3 and not value and section > 0 and name == sections[section - 1]["name"] \
                and data[at + (i + 1) * 18 + 14] == 5:                   # a section record, IMAGE_COMDAT_SELECT_ASSOCIATIVE
            symbols[i]["association"] = struct.unpack_from("<H", data, at + (i + 1) * 18 + 12)[0]
        i += 1 + aux
    return sections, symbols


COMPILER_NUMBERED = re.compile(r"^\$(?:L|SG|T)\d+$")                     # renumbered per unit


def section_identity(obj, name):
    """What the body defining `name` in the object at `obj` is beyond the bytes a mask reads: its
    section's exact bytes, size and flags, each relocation's offset, type and target, and the same for
    each section associated with it or reached through a local symbol, walked in order, so equal values
    mean one body binding the same names. An external target is its name, and an `/alternatename` of
    it; a local one is where it lands, with its name unless the compiler numbered it per unit.
    None when that cannot be compared: an unreadable object, no such symbol, a weak or undefined local
    target. A body in a section the unit shares, such as `.rdata`, compares as that whole section."""
    import struct
    try:
        data = Path(obj).read_bytes()
        sections, symbols = coff_layout(data)
        alternates = {m.group(1).decode("latin-1").strip('"'): m.group(2) for m in
                      re.finditer(rb"/alternatename:([^=\s]+)=(\S+)", data, re.I)}
        associated = collections.defaultdict(list)
        for s in symbols.values():
            if s["association"]:
                associated[s["association"]].append(s["section"])
        order = {}

        def section(number):
            if number in order:
                return ("seen", order[number])
            order[number] = len(order)
            this = sections[number - 1]
            relocs = []
            for offset, index, kind in this["relocs"]:
                target = symbols[index]
                if target["storage"] == 2:
                    relocs.append((offset, kind, "external", target["name"], alternates.get(target["name"]),
                                   0 if target["section"] else target["value"]))
                elif target["section"] > 0 and target["storage"] != 105:
                    relocs.append((offset, kind, "local", None if COMPILER_NUMBERED.match(target["name"]) else target["name"],
                                   target["value"], section(target["section"])))
                else:
                    raise ValueError("a relocation target that cannot be compared")
            return (this["name"], this["size"], this["flags"], this["raw"], tuple(relocs),
                    tuple(section(n) for n in associated[number]))
        found = next(s for s in symbols.values() if s["name"] == name and s["section"] > 0)
        return (found["value"], section(found["section"]))
    except (OSError, TypeError, ValueError, IndexError, KeyError, StopIteration, RecursionError, struct.error):
        return None


def coff_definitions(obj):
    """{symbol: (in a COMDAT, in code, COMDAT selection)} of what the COFF object at `obj` defines, or
    None when it cannot be read: missing, not an i386 object, anything outside its bounds (coff_layout).
    Unlike defined_symbols, which reads a missing object as defining nothing, this never turns "unread"
    into "absent". A weak external and an `/alternatename` count as defining: they can satisfy the name."""
    import struct
    import link_census as LCe
    try:
        data = Path(obj).read_bytes()
        coff_layout(data)
        count = struct.unpack_from("<H", data, 2)[0]
        optional = struct.unpack_from("<H", data, 16)[0]
        selections = LCe._comdat_selections(data)
        out = {}
        for s in LCe._coff_symbols(data):
            if s["storage"] != LCe.EXTERNAL:
                continue
            if s["section"] > count:
                return None
            if s["section"] > 0:
                flags = struct.unpack_from("<I", data, 20 + optional + (s["section"] - 1) * 40 + 36)[0]
                out[s["name"]] = (bool(flags & LCe.COMDAT), bool(flags & 0x20), selections.get(s["section"]))
            elif s["value"]:
                out[s["name"]] = (False, False, None)                 # a common symbol
        for name, _default in LCe._weak_externals(data):
            out.setdefault(name, (False, False, None))
        for m in re.finditer(rb"/alternatename:([^=\s]+)=\S+", data, re.I):
            out.setdefault(m.group(1).decode("latin-1").strip('"'), (False, False, None))
        return out
    except (OSError, TypeError, ValueError, IndexError, KeyError, struct.error):
        return None


def map_approved_problem(r, key):
    """Why the current map does not approve unit `key` for row `r`'s own address, or None. The proof
    never overrides the map: a funclet that rides with its parent answers for its own address too."""
    rva = int(r["target_rva"], 16)
    if "map_approved" not in _CACHE:
        _CACHE["map_approved"] = {int(m["rva"], 16): m for m in map_rows() if m["kind"].startswith("code")}
    m = _CACHE["map_approved"].get(rva)
    if m is None or m["confidence"] != "approved" or not m["tu"] or m["tu"].lower() != key.lower():
        return f"the current map does not approve {key} for {r['target_rva']}"
    return None


def transfer_problem(name, donor, dest, objs, before, companion=False):
    """Why the objects `objs` {unit: object} do not show `name` handed from `donor` to `dest`, or None:
    the donor's object no longer defines it, the destination's defines it in a code COMDAT selected
    ANY, no other object defines it, and the destination's body is the one `before` {name:
    section_identity} read from the donor's object before the move: bytes alone mask every address, so
    `return &g` and `return &h` compare equal without it. An unreadable object or a body that cannot be
    compared refuses. A `companion` (a funclet emitted with its parent, usually a local symbol) need not
    be an external of the destination, its parent's identity reaches it, and no other unit may define it
    either. "No other" means the objects of this transaction only: the whole link is the pre-push batch
    audit's and link_check's to judge."""
    defs = {}
    for unit, obj in objs.items():
        defs[unit] = coff_definitions(obj)
        if defs[unit] is None:
            return f"{unit}'s object cannot be read: inconclusive"
    if name in defs[donor]:
        return f"{donor}'s rebuilt object still defines it"
    others = sorted(u for u in defs if u != dest and name in defs[u])
    if others:
        return "exactly one object must define it afterwards: " + ", ".join(others) + " does too"
    found = defs[dest].get(name)
    if found is None:
        return None if companion else f"{dest}'s object does not define it"
    comdat, code, selection = found
    if not code:
        return f"{dest} defines it outside a code section"
    if not comdat or selection != 2:
        return (f"{dest} defines it {'outside a COMDAT' if not comdat else 'selected ' + str(SELECTION.get(selection, selection))}"
                ": a real body goes through --split or --merge")
    old, new = before.get(name), section_identity(objs[dest], name)
    if old is None or new is None:
        return f"its body in {donor} before the move and in {dest} cannot be compared: inconclusive"
    if old != new:
        return f"{dest}'s body differs from {donor}'s before the move, in its bytes, its relocations or an associated section"
    return None


OBJECT_SYMBOL = re.compile(r"(?:^|;)\s*object-symbol=([^;]+)")


def object_symbol_differs(r):
    """The `object-symbol=` a row's bytes are verified under, when it is not the row's name:
    build.py follows it (ledger_object_symbol), so a check by name would judge another symbol
    (review of 3db7ced4b4)."""
    m = OBJECT_SYMBOL.search(r.get("notes") or "")
    return m.group(1).strip() if m and m.group(1).strip() != r["name"] else None


def comdat_symbols(obj):
    """External symbols `obj` defines in COMDAT sections (link_census._comdat_sections); empty
    when the object cannot be read."""
    import struct
    import link_census as LCe
    try:
        return {symbol["name"] for symbol, *_ in LCe._comdat_sections(Path(obj).read_bytes())}
    except (OSError, ValueError, IndexError, KeyError, struct.error):
        return set()


def identity_debt(path, names):
    """Rows of `names` with a code-identity debt line keyed to `path`: moving the row would
    strand the line (it is retired only along its register's path)."""
    reg = ROOT / "reverse/code_identity_baseline.tsv"
    if not reg.exists():
        return set()
    out = set()
    for line in reg.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = line.split("\t")
        if len(parts) >= 2 and parts[0] == path and parts[1] in names:
            out.add(parts[1])
    return out


def emit_move(path, tu, rvas=None, dry_run=False, claim=True, prepared=None):
    """_emit_move; a prepared transaction's every compile is fresh (fresh_compiles)."""
    if not prepared:
        return _emit_move(path, tu, rvas, dry_run, claim, prepared)
    with fresh_compiles():
        return _emit_move(path, tu, rvas, dry_run, claim, prepared)


def _emit_move(path, tu, rvas, dry_run, claim, prepared):
    """Repoint the deleting-destructor rows of mixed `path` (one file, or several as one
    transaction) the current map approves for `tu` to the TU file, which must emit each of
    them byte-exact. Fail-closed: every row (an explicit `rvas` list, each in exactly one of
    the files, else every approved row) must be approved for `tu`, verified under its own name
    (no `object-symbol=` binding it to another symbol), a `??_G`/`??_E` by its decorated name
    (emission_problem) with no hand-written copy (hand_written_problem: each object's COMDAT
    selected ANY in a code section as the compiler's, no `__identifier` definition of it in any
    unit's preprocessed text), defined by the TU's object in a COMDAT section and byte-exact,
    with no other row of these files at its address and no identity debt keyed to its file. A
    file may keep a copy (the stand-in views that host these rows today) only as a COMDAT, never
    a strong definition. The TU's own rows and each file's remaining rows must keep every match.

    `prepared` {path: text}: the whole final text of the TU or of a listed file, written in the
    same transaction (P16 G5: a donor's stand-in removed, the TU emitting the row). Each is
    judged as given in place of the file; a prepared text outside those paths refuses, hatch
    totals over the files may not grow (emit_hatches_grow), and no strong symbol a prepared unit
    defined may vanish from every object of the transaction (a COMDAT it stops emitting is
    reported as `comdats_dropped`, for the pre-push link audit).

    In a prepared transaction a row of a prepared file that its name does not admit may move on the
    object-level transfer proof instead (transfer_problem, map_approved_problem): today's map approves
    the TU for its address, the file's rebuilt object no longer defines it, the TU's defines it
    byte-exact as a code COMDAT selected ANY, and no other object of the transaction defines it. It
    is judged at the byte gate, again on the final compiles, and on the real objects, rebuilt from
    nothing, after the build. A row it refuses stays in its file, whose prepared text then loses it.

    Two stages. A scratch compile beside each file (Verifier) screens the rows and is
    re-judged with exactly the rows that move, since region flags follow the row set. The
    apply then proves the committed state: the before-state is journalled to disk, the
    ledger and prepared texts are written, build.py verifies exactly these real files at their
    real paths (exact_build), the rebuilt objects are read again (COMDAT in the TU, no strong
    copy in a file), and on any other exit (a refusal, an exception, an interrupt) undo_emit
    puts every file back, deletes the objects and receipts and releases the claims, each step
    on its own. A killed run leaves the journal: --recover-emit undoes it, and no move starts
    while one is pending. Without `rvas` a row that does not qualify stays and is reported;
    with `rvas`, any refusal blocks all."""
    files = [path] if isinstance(path, str) else list(dict.fromkeys(path))
    prepared = dict(prepared or {})
    report = {"file": files[0]} if len(files) == 1 else {"files": files}
    report["tu"] = tu
    the = lambda f: "the file" if len(files) == 1 else f
    pending = emit_journals()
    if pending:
        report["blocked"] = (f"an emit move did not finish (journal {pending[0][0].name}): "
                             "run python3 tools/tu_skeleton.py --recover-emit first")
        return report
    rows = {f: file_rows(f) for f in files}
    for f in files:
        if not rows[f]:
            report["blocked"] = "no matched rows in that file" if len(files) == 1 else f"no matched rows in {f}"
            return report
    groups = {f: breakdown(f) for f in files}
    key = next((k for f in files for k in groups[f] if k and k.lower() == tu.lower()), tu)
    report["tu"] = key
    dest = tu_path(key)
    if dest != key:
        report["tu_file"] = dest
    if not (ROOT / dest).exists():
        report["blocked"] = f"{dest} does not exist: the approved TU must emit the rows from its own code first"
        return report
    if dest.lower() in {f.lower() for f in files}:
        report["blocked"] = "the file is the TU itself"
        return report
    prepared = {(dest if k.lower() == tu.lower() else k): text for k, text in prepared.items()}
    stray = sorted(set(prepared) - set(files) - {dest})
    if stray:
        report["blocked"] = "a prepared text may only replace the TU or a listed file: " + ", ".join(stray)
        return report
    dtors = {f: {m.group(1): r["name"] for r in rows[f] if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
             for f in files}
    approved = {f: [r for k, g in groups[f].items() if k and k.lower() == key.lower() for r in g
                    if not parent_of(r, dtors[f])] for f in files}
    if rvas:
        want = {int(x, 16) for x in rvas}
        missing = sorted(want - {int(r["target_rva"], 16) for f in files for r in rows[f]})
        if missing:
            report["blocked"] = "not a matched row of the file: " + ", ".join(f"0x{x:08X}" for x in missing)
            return report
        outside = sorted(want - {int(r["target_rva"], 16) for f in files for r in approved[f]})
        if outside:
            report["blocked"] = (", ".join(f"0x{x:08X}" for x in outside) + f" not approved for {key} in the "
                                 "current tu_map (only approved rows move)")
            return report
        approved = {f: [r for r in approved[f] if int(r["target_rva"], 16) in want] for f in files}
    for f in files:
        if not approved[f]:
            report["blocked"] = f"no row of {the(f)} is approved for {key}" + (" among those requested" if rvas else "")
            return report
    everywhere = collections.Counter(r["target_rva"].lower() for f in files for r in rows[f])
    refused, on_proof = {}, set()
    for f in files:
        for r in approved[f]:
            other = object_symbol_differs(r)
            why = (f"its bytes are verified as {other} (object-symbol=), not under its name: every check here must "
                   "judge one symbol") if other else None
            if why is None:
                why = emission_problem(r)
                if why is not None and f in prepared:     # no name admits it: the objects must
                    why = map_approved_problem(r, key)
                    if why is None:
                        on_proof.add(r["target_rva"])
            if why is None and fold_alias(r):
                why = "an ICF alias: it lives where the bodies emitting its identity live"
            if why is None and everywhere[r["target_rva"].lower()] > 1:
                why = "another row of the file shares its address"
            if why is None and identity_debt(f, {r["name"]}):
                why = "carries code-identity debt keyed to this file"
            if why:
                refused[r["target_rva"]] = why
    movers = {f: [r for r in approved[f] if r["target_rva"] not in refused] for f in files}
    moved = {f: movers[f] + companions(rows[f], {r["name"] for r in movers[f]}) for f in files}
    for f in files:
        if movers[f] and not [r for r in rows[f] if r not in moved[f]]:
            report["blocked"] = ("no row would remain in the file: it is a whole donor, use --merge" if len(files) == 1
                                 else f"no row would remain in {f}: it is a whole donor, use --merge")
            return report
    now = {f: (ROOT / f).read_bytes().decode("utf-8-sig", errors="replace").replace("\r\n", "\n") for f in files + [dest]}
    hatches = emit_hatches_grow(now, prepared) if prepared else None
    if hatches:
        report["blocked"] = hatches
        return report
    # A file keeps its text, so it may keep a copy: an inline stand-in view compiles to a selectany
    # COMDAT, which links beside the TU's. A strong definition there would collide with the TU's copy:
    # refuse. Judged on the object its build compiles today (every row's flags), or on the prepared text.
    vx, before_x, final_x, strong_was, comdat_was, bodies = {}, {}, {}, set(), set(), {}
    for f in files:
        vx[f] = Verifier(f)
        final_x[f] = prepared.get(f, now[f])
        before_x[f] = vx[f].matched(now[f], rows[f])
        if before_x[f] is None:
            report["blocked"] = f"{the(f)} does not compile: " + " | ".join(vx[f].errors)[:300]
            return report
        if f in prepared:
            strong_was |= strong_symbols(vx[f].obj)
            comdat_was |= comdat_symbols(vx[f].obj)
            bodies.update({r["name"]: section_identity(vx[f].obj, r["name"]) for r in moved[f]})   # today's text
            if vx[f].matched(prepared[f], [r for r in rows[f] if r not in moved[f]]) is None:
                report["blocked"] = f"the prepared text of {f} does not compile: " + " | ".join(vx[f].errors)[:300]
                return report
        for r in movers[f]:
            if r["name"] in strong_symbols(vx[f].obj):
                refused[r["target_rva"]] = f"{the(f)} defines it outside a COMDAT: a strong body has a home (--split)"
    # the byte gate in the destination: the TU as it stands, judged with its own rows as its build will
    vt = Verifier(dest)
    text_t = prepared.get(dest, now[dest])
    own = file_rows(dest)
    before_t = vt.matched(now[dest], own) if own or dest in prepared else set()
    if before_t is None:
        report["blocked"] = "the TU does not compile: " + " | ".join(vt.errors)[:300]
        return report
    if dest in prepared:
        strong_was |= strong_symbols(vt.obj)
        comdat_was |= comdat_symbols(vt.obj)
    all_moved = [r for f in files for r in moved[f]]
    got = vt.matched(text_t, own + all_moved) if all_moved else set()
    if all_moved and got is None:
        report["blocked"] = (("the prepared TU text does not compile: " if dest in prepared else "the TU does not compile: ")
                             + " | ".join(vt.errors)[:300])
        return report
    if all_moved:
        defined, comdats = defined_symbols(vt.obj), comdat_symbols(vt.obj)
        for f in files:
            by_name = {o["name"]: o for o in movers[f]}
            for r in movers[f] + [c for c in moved[f] if c not in movers[f]]:      # parents first
                parent = by_name.get(parent_of(r, dtors[f]) or "")
                if r["target_rva"] in refused or (parent is not None and parent["target_rva"] in refused):
                    continue                                               # a companion rides its parent's refusal
                if r["name"] not in defined and r in movers[f]:
                    refused[r["target_rva"]] = f"{dest}'s object does not emit it (its code instantiates nothing of that name)"
                elif r in movers[f] and r["name"] not in comdats:
                    refused[r["target_rva"]] = f"{dest} defines it outside a COMDAT: a strong body has a home (--split)"
                elif r["target_rva"] not in got:
                    refused[r["target_rva"]] = f"{dest}'s object emits it, but not byte-exact"
        lost = sorted(before_t - got)
        if lost:
            report["blocked"] = f"{dest}'s own rows lose matches judged beside the moved rows: " + ", ".join(lost[:5])
            return report
    # a deleting destructor's name does not prove the compiler wrote it (review of 87417c8f9f)
    judged = [r for f in files for r in movers[f] if r["target_rva"] not in refused and r["target_rva"] not in on_proof]
    if judged:
        texts = {f: vx[f].preprocessed(final_x[f], [r for r in rows[f] if r not in moved[f]] if f in prepared else rows[f])
                 for f in files}
        texts[dest] = vt.preprocessed(text_t, own + all_moved)
        for r in judged:
            why = hand_written_problem(r["name"], [vt.obj] + [vx[f].obj for f in files], texts)
            if why:
                refused[r["target_rva"]] = why
    def proof_rows(f):
        """(row, is a companion) of file `f` on the transfer proof: each mover on it, and what rides with one."""
        parents = {r["name"] for r in movers[f] if r["target_rva"] in on_proof}
        for r in moved[f]:
            if r in movers[f]:
                if r["target_rva"] in on_proof:
                    yield r, False
            elif parent_of(r, dtors[f]) in parents:
                yield r, True

    def proof_problems():
        """{rva: why} of each row on the transfer proof, on the objects as they stand now."""
        units = {f: vx[f].obj for f in files}
        units[dest] = vt.obj
        out = {}
        for f in files:
            for r, is_companion in proof_rows(f):
                if r["target_rva"] not in refused:
                    why = (map_approved_problem(r, key) if is_companion else None) or transfer_problem(
                        r["name"], f, dest, units, bodies, companion=is_companion)
                    if why:
                        out[r["target_rva"]] = why
        return out
    if on_proof:
        refused.update(proof_problems())
    # a refused parent takes its companions with it; a refused companion takes its parent
    for f in files:
        for r in list(moved[f]):
            if r["target_rva"] in refused:
                p = parent_of(r, dtors[f])
                for o in moved[f]:
                    if o["name"] == p or parent_of(o, dtors[f]) == r["name"]:
                        refused.setdefault(o["target_rva"], f"emitted with refused {r['target_rva']}")
    report["refused_rows"] = refused
    if refused and rvas:
        report["blocked"] = "a requested row cannot move by emission"
        return report
    moved = {f: [r for r in moved[f] if r["target_rva"] not in refused] for f in files}
    movers = {f: [r for r in movers[f] if r in moved[f]] for f in files}
    all_moved = [r for f in files for r in moved[f]]
    if not all_moved:
        report["blocked"] = "no row can move by emission"
        return report
    # Region flags follow the bytes of the rows a unit holds, so the TU is judged again with
    # exactly the rows that move (review of 3db7ced4b4), COMDAT properties included.
    final = vt.matched(text_t, own + all_moved)
    if final is None or not {r["target_rva"] for r in all_moved} <= final or before_t - final:
        report["blocked"] = (f"{dest} re-judged with exactly the rows that move loses a match: "
                             + ", ".join(sorted(({r["target_rva"] for r in all_moved} | before_t) - (final or set()))[:5]))
        return report
    for f in files:
        problem = committed_problem(movers[f], dest, vt.obj, vx[f].obj)
        if problem:
            report["blocked"] = problem
            return report
    defined_now = set(defined_symbols(vt.obj))
    for f in files:
        keep = [r for r in rows[f] if r not in moved[f]]
        after_x = vx[f].matched(final_x[f], keep)
        if after_x is None:
            report["blocked"] = f"{the(f)} does not compile: " + " | ".join(vx[f].errors)[:300]
            return report
        lost = sorted((before_x[f] & {r["target_rva"] for r in keep}) - after_x)
        if lost:
            report["blocked"] = f"{the(f)}'s remaining rows lose matches once these rows leave: " + ", ".join(lost[:5])
            return report
        defined_now |= defined_symbols(vx[f].obj)
    on_proof &= {r["target_rva"] for r in all_moved}
    if on_proof:
        again = proof_problems()
        if again:
            rva, why = sorted(again.items())[0]
            report["blocked"] = f"re-judged on the final compiles, the transfer proof of {rva} fails: {why}"
            return report
        report["transfer_proof"] = sorted(on_proof)
    if prepared:
        gone = sorted(strong_was - defined_now)
        if gone:
            report["blocked"] = "a prepared text stops defining what no object of this move defines: " + ", ".join(gone[:5])
            return report
        dropped = sorted(comdat_was - defined_now)
        if dropped:
            report["comdats_dropped"] = dropped[:20]
    report["moved"] = [r["target_rva"] for r in all_moved]
    why = map_regressions(dest, moved_rows={f: [r["target_rva"] for r in moved[f]] for f in files})
    if why:
        report["blocked"] = why
        return report
    if dry_run:
        report["verify"] = ("screened by a scratch compile; the apply proves it by building exactly "
                            + " ".join(files + [dest]))
        return report
    don = {f: moved[f] for f in files}
    with ledger_locked():
        pending = pending_journal()             # under the lock: two moves cannot both pass it
        if pending:
            report["blocked"] = f"a pending journal: {pending}"
            return report
        acquired, tokens = [], {}
        if claim:
            held = claim_scope(dest, don)
            if held:                # refused: abort before touching anything, and give back exactly
                give_back(held)     # what this call took, fenced by its tokens
                report["blocked"] = held_message(held)
                return report
            acquired, tokens = list(held.acquired), dict(held.tokens)
        proofs = {f: [(r["name"], is_companion) for r, is_companion in proof_rows(f)] for f in files}
        try:
            result = _apply_emit(files, dest, movers, {f: [r["target_rva"] for r in moved[f]] for f in files},
                                 acquired, tokens, prepared, proofs, bodies)
        except BaseException as error:
            if claim and not getattr(error, "journalled", False):    # with a journal, undo_emit released them
                give_back_after(error, report, held)
            raise
    if isinstance(result, str):
        report["blocked"] = result
        return report
    repointed = result
    report["repointed"] = repointed
    report["stage"] = "staged: " + " ".join(list(repointed) + sorted(prepared))
    report["verified"] = "build.py over exactly " + " ".join(files + [dest])
    report["subject"] = (f"Move {len(all_moved)} emitted rows of "
                         + (posixpath.basename(files[0]) if len(files) == 1 else f"{len(files)} files")
                         + f" into {posixpath.basename(dest)} (tu_map approved TU, emitted byte-exact"
                         + ("; prepared texts)" if prepared else ")"))
    return report


def emit_hatches_grow(now, prepared):
    """Why the `prepared` texts may not stand against the escape-hatch totals over the files of `now`
    {path: text} (hatch_counters rule 3), or None. Totals are over the whole transaction: a hatch may
    move, not grow. A checker that cannot be imported has judged nothing, so it refuses."""
    try:
        import hatch_counters as H
    except ImportError as error:
        return f"the escape-hatch checker is unavailable ({error}): the prepared texts cannot be judged"

    def totals(texts):
        out = collections.Counter()
        for rel, text in texts.items():
            for (hatch, _p, token), n in H.scan(rel, text).items():
                out[(hatch, token)] += n
        return out
    old, new = totals(now), totals({**now, **prepared})
    if any(new[k] > old.get(k, 0) for k in new):
        return "the prepared texts would raise an escape-hatch total over these files"
    return None


def _apply_emit(files, dest, movers, rvas, acquired, tokens, prepared=None, proofs=None, bodies=None):
    """The write half of emit_move, under the ledger lock: {rel: rows repointed}, or why it
    was undone. The journal (before and after bytes of each ledger file and prepared text,
    their index entries, the claim keys with their fencing tokens) goes to disk, fsynced, before
    anything is touched; a SIGKILL or power loss leaves it for --recover-emit, and any other
    exit short of a verified, staged move undoes it here (undo_emit, row-level for the ledger,
    whole-file for a text), each step on its own. `proofs` {file: [(name, is a companion)]}: rows on the
    transfer proof, judged on the real objects against `bodies` {name: section_identity before the move};
    both are deleted first, so the build must compile them. What is staged is what was compiled: every file
    of the build and every staged file must still hold, after the build, the bytes it held before it."""
    import build
    proofs = {f: rows for f, rows in (proofs or {}).items() if rows}
    prepared = {rel: text.encode("utf-8") for rel, text in (prepared or {}).items()}
    before = {rel: (ROOT / rel).read_bytes() for rel, _ in ROW_KEYED if (ROOT / rel).exists()}
    after, repointed = {}, {}
    for rel, keycol in ROW_KEYED:
        if rel in before:
            raw, count = before[rel], 0
            for f in files:
                raw, n = repoint_rows(raw, rel, keycol, rvas[f], "source", f, dest)
                count += n
            after[rel] = raw
            if count:
                repointed[rel] = count
    texts = {rel: {"before": rename._b64((ROOT / rel).read_bytes()), "after": rename._b64(raw)}
             for rel, raw in prepared.items()}
    keys = [key_text(k) for k in acquired]   # only what this move claimed: never a prior claim
    sources = files + [dest]
    journal = write_emit_journal({"subject": ("emit-move " + " ".join(files) + f" -> {dest}"), "sources": sources,
                                  "before": {rel: rename._b64(raw) for rel, raw in before.items()},
                                  "after": {rel: rename._b64(raw) for rel, raw in after.items()},
                                  "texts": texts,
                                  "index": index_entries(list(before) + list(prepared)),
                                  "claims": keys, "tokens": {key_text(k): v for k, v in tokens.items()}})
    done, problem = False, "interrupted before the build finished"
    try:
        for rel in repointed:
            (ROOT / rel).write_bytes(after[rel])
        for rel, raw in prepared.items():
            (ROOT / rel).write_bytes(raw)
        # the committed state: exactly these real files at their real paths, under the flags
        # their build picks from the repointed ledger (__FILE__, __LINE__ and region flags theirs)
        _CACHE.clear()
        built = {rel: (ROOT / rel).read_bytes() for rel in {*sources, *repointed, *prepared}}
        stale = drop_objects(build, sources) if proofs else []
        ok, output = exact_build(sources) if not stale else (False, "could not delete an object to compile it afresh: " + "; ".join(stale))
        if ok:
            problem = None
            for f in files:
                problem = problem or committed_problem(movers[f], dest, build.obj_path(ROOT / dest), build.obj_path(ROOT / f))
            units = {u: build.obj_path(ROOT / u) for u in sources}
            for f, named in proofs.items():
                for name, is_companion in named:
                    why = transfer_problem(name, f, dest, units, bodies or {}, companion=is_companion)
                    problem = problem or (f"the rebuilt objects fail the transfer proof of {name}: {why}" if why else None)
        else:
            problem = "the build did not pass the repointed rows: " + " | ".join(output.strip().splitlines()[-3:])[:400]
        changed = sorted(rel for rel, raw in built.items() if not (ROOT / rel).is_file() or (ROOT / rel).read_bytes() != raw)
        if changed and problem is None:
            problem = "changed after the build read them, so what would be staged was not what was checked: " + ", ".join(changed)
        if problem is None:
            subprocess.run(["git", "add", "--", *repointed, *prepared], cwd=ROOT, check=True, env=git_trust.trusted_env())
            done = True
    except BaseException as error:
        error.journalled = True
        raise
    finally:
        record = json.loads(journal.read_text(encoding="utf-8"))
        errors = [] if done else undo_emit(record)
        if not errors:
            remove_emit_journal(journal)    # an undo that failed keeps its journal for --recover-emit
    if problem:
        return problem + (" (the ledger was put back, both objects dropped and the claims released)" if not errors else
                          " (undo incomplete, run tu_skeleton.py --recover-emit: " + "; ".join(errors)[:300] + ")")
    return repointed


def drop_objects(build, sources):
    """Delete each source's build/match object and its .deps.json receipt; [errors]. After a
    failed build under a repointed ledger an object may be partly rewritten; with the ledger
    put back its receipt could revalidate it as current (the build cache trap,
    docs/matching.md). With neither file there, the next build compiles the unit afresh. Each
    file is its own step: one that cannot be removed (a locked .obj on Windows) is reported
    and the rest still go."""
    errors = []
    for source in sources:
        try:
            obj = build.obj_path(ROOT / source)
            paths = (obj, build._deps_sidecar(obj))
        except Exception as error:                       # noqa: BLE001 - reported, never skips the rest
            errors.append(f"{source}: no object path ({error})")
            continue
        for path in paths:
            try:
                Path(path).unlink()
            except FileNotFoundError:
                pass
            except OSError as error:
                errors.append(f"could not remove {Path(path).name}: {error}")
    return errors


def exact_build(sources):
    """(ok, output) of build.py's own verification over exactly `sources` (build.main's
    exact_sources, the membership scope its cross-source re-verify uses): ./build.sh's
    selectors are substrings, so `Code/Campaign.cpp` would also rebuild
    `Code/Campaign.cpp.extra.cpp`, whose artefacts no rollback would know (review of
    e81c016950). Same environment defaults as build.sh; ok on exit 0 with `Functions: OK`."""
    code = ("import sys; sys.path.insert(0, 'tools'); import build; "
            f"sys.exit(build.main(exact_sources={sorted(sources)!r}) or 0)")
    env = dict(os.environ, WINEDEBUG=os.environ.get("WINEDEBUG", "-all"), DISPLAY=os.environ.get("DISPLAY", ""))
    print(f"tu_skeleton: verifying exactly {len(sources)} source(s): {' '.join(sources)}", flush=True)
    result = subprocess.run([sys.executable, "-c", code], cwd=ROOT, capture_output=True, text=True, env=env)
    output = result.stdout + result.stderr
    print("\n".join(output.rstrip().splitlines()[-25:]))
    return result.returncode == 0 and re.search(r"^Functions: OK \d+/\d+", output, re.M) is not None, output


# An emit move's before-state, written (fsynced) before the ledger is touched: a SIGKILL or a
# power loss mid-verify leaves an unverified move, and recover_emit() puts it back.
EMIT_JOURNAL = "build/tu_skeleton/emit-journal"
LEDGER_LOCK = "reverse/.add_match.lock"      # rename.py's and add_match's ledger lock (rename.LOCK)


@contextlib.contextmanager
def ledger_locked():
    """Hold the ledger lock rename.py and add_match take, for an emit move and its recovery:
    no rename or append interleaves, and two emit moves cannot both pass the pending check
    (review of 90fdd5d03d)."""
    import portable_lock
    (ROOT / LEDGER_LOCK).parent.mkdir(parents=True, exist_ok=True)
    with (ROOT / LEDGER_LOCK).open("a") as handle:
        portable_lock.lock(handle, exclusive=True, wait_notice="tu_skeleton: waiting for the ledger lock...")
        try:
            yield
        finally:
            portable_lock.unlock(handle)


def emit_journals():
    """[(path, record or None)] of every emit-move journal in this tree."""
    folder = ROOT / EMIT_JOURNAL
    out = []
    for path in sorted(folder.glob("*.json")) if folder.is_dir() else []:
        try:
            out.append((path, json.loads(path.read_text(encoding="utf-8"))))
        except (OSError, ValueError):
            out.append((path, None))
    return out


def pending_journal():
    """The first pending emit-move or rename journal, as `kind name`, or None: neither tool
    starts while the other's journal waits (review of 90fdd5d03d)."""
    for path, _record in emit_journals():
        return f"emit move {path.name} (run python3 tools/tu_skeleton.py --recover-emit)"
    ctx = SimpleNamespace(root=ROOT, path=lambda rel: ROOT / rel)
    for path, record in rename.journals(ctx):
        if (record or {}).get("emit_journal"):
            continue                                     # our own marker, beside its emit journal
        return f"rename {path.name} (run python3 tools/rename.py recover)"
    return None


def _write_atomic(path, record):
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(record), encoding="utf-8")
    with tmp.open("r+b") as handle:
        os.fsync(handle.fileno())
    os.replace(tmp, path)


def write_emit_journal(record):
    """Persist `record` atomically (rename.py's journal discipline: tmp, fsync, replace), and a
    rename-format marker in rename.py's journal folder naming it, with nothing to restore:
    rename.py's pending-journal guard then refuses renames until the move finishes or is
    recovered. The marker is removed with the journal."""
    import socket
    import uuid
    record = dict(record, id=uuid.uuid4().hex, pid=os.getpid(), host=socket.gethostname(), boot=rename._boot_id(),
                  started=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()))
    path = ROOT / EMIT_JOURNAL / f"{record['id']}.json"
    _write_atomic(path, record)
    marker = {k: record[k] for k in ("id", "pid", "host", "boot", "started")}
    marker.update(subject=f"{record.get('subject', 'emit move')} (pending: python3 tools/tu_skeleton.py --recover-emit)",
                  before={}, moves=[], moved_bytes={}, claims=[], tokens={}, emit_journal=str(path.relative_to(ROOT)))
    _write_atomic(ROOT / rename.JOURNAL_DIR / f"emit-{record['id']}.json", marker)
    return path


def remove_emit_journal(path):
    """Remove an emit journal and its rename.py marker."""
    marker = ROOT / rename.JOURNAL_DIR / f"emit-{path.stem}.json"
    for p in (path, marker):
        try:
            p.unlink()
        except FileNotFoundError:
            pass


def index_entries(paths):
    """{path: (mode, blob) or None} of `paths` in the index."""
    out = {p: None for p in paths}
    listed = subprocess.run(["git", "ls-files", "-s", "--", *paths], cwd=ROOT, capture_output=True, text=True,
                            check=True, env=git_trust.trusted_env()).stdout
    for line in listed.splitlines():
        meta, _, rel = line.partition("\t")
        mode, blob, _stage = meta.split()
        out[rel] = (mode, blob)
    return out


def blob_of(data):
    """The blob id git would give `data`."""
    return subprocess.run(["git", "hash-object", "--stdin"], cwd=ROOT, input=data, capture_output=True,
                          check=True, env=git_trust.trusted_env()).stdout.decode().strip()


def undo_lines(current, before, after, keycol):
    """`current` with the rows the move changed (before -> after) put back, or None: row-level,
    so an edit made since to any other row survives (review of 90fdd5d03d). Judged per moved
    key (`keycol`, the RVA the move repointed, read as a number in every state: `0x2000` and
    `0x00002000` are one key, review of 3bc60f1272): its rows now are exactly its after-state rows
    (go back), or exactly its before-state rows (done already: a retry after a partial
    recovery, review of bfb856bfbf); any other combination, both states present, a copy
    duplicated or an edited row beside an original, refuses (review of 9459886c66)."""
    import ledger_io
    split = {name: ledger_io.split_records(raw) for name, raw in (("current", current), ("before", before),
                                                                   ("after", after))}
    header = ledger_io.fields(split["before"][0][0]) if split["before"] else []
    if keycol not in header:
        return None
    ki = header.index(keycol)

    def key(payload):
        """The row's RVA as a number (None when blank); ValueError when it is not one."""
        text = payload.decode("utf-8", "replace")
        spans = rename.field_spans(text)
        value = text[spans[ki][0]:spans[ki][1]].strip().strip('"').strip() if len(spans) > ki else ""
        return int(value, 16) if value else None

    def by_key(records):
        out = {}
        for payload, _term in records[1:]:
            out.setdefault(key(payload), []).append(payload)
        return out
    try:
        b, a, c = by_key(split["before"]), by_key(split["after"]), by_key(split["current"])
    except ValueError:
        return None                             # an RVA no number reads: nothing can be compared
    back = {}
    for k in set(b) | set(a):
        old, new = b.get(k, []), a.get(k, [])
        if old == new:
            continue
        now = sorted(c.get(k, []))
        if now == sorted(old):
            continue
        if now != sorted(new) or len(old) != len(new):
            return None
        for o, n in zip(old, new):
            if back.setdefault(n, o) != o:
                return None                     # one after-state row from two before-state rows
    return b"".join(back.get(payload, payload) + term for payload, term in split["current"])


def undo_emit(record, release=True):
    """Put one emit move back from its journal record; [errors]. Row-level (undo_lines): only
    the lines the move changed go back, and a file whose moved lines changed since is left
    alone and reported. A prepared text goes back whole, only from its before or after state. The index entry of each ledger file goes back to what it was, when it
    still holds what the move staged (or nothing was staged). Then each object and receipt is
    dropped and the claims are released with their fencing tokens (rename.py's recovery
    does the same; review of 90fdd5d03d). Every step is its own (review of e81c016950)."""
    import build
    errors = []
    before = {rel: rename._unb64(data) for rel, data in (record.get("before") or {}).items()}
    after = {rel: rename._unb64(data) for rel, data in (record.get("after") or {}).items()}
    texts = {rel: (rename._unb64(t["before"]), rename._unb64(t["after"])) for rel, t in (record.get("texts") or {}).items()}
    for rel, old in list(before.items()) + [(rel, pair[0]) for rel, pair in texts.items()]:
        try:
            current = (ROOT / rel).read_bytes()
            new = texts[rel][1] if rel in texts else after.get(rel, old)
            if rel in texts:         # a prepared text: whole-file, from a state this move knows
                restored = old if current in (old, new) else None
            else:
                keycol = dict(ROW_KEYED).get(rel)
                restored = current if current == old else keycol and undo_lines(current, old, new, keycol)
            if restored is None:
                errors.append(f"{rel}: the moved rows changed since the move; undo it by hand from the journal")
                continue
            if restored != current:
                (ROOT / rel).write_bytes(restored)
            entry, wrote = (record.get("index") or {}).get(rel), blob_of(new)
            staged = index_entries([rel])[rel]
            if staged is not None and staged[1] == wrote and (entry is None or entry[1] != wrote):
                if entry is None:
                    # (not `git rm --cached`: with the working file already restored, the staged
                    # blob matches neither it nor HEAD, which git rm refuses without -f)
                    subprocess.run(["git", "update-index", "--force-remove", "--", rel], cwd=ROOT, check=True,
                                   env=git_trust.trusted_env())
                else:
                    subprocess.run(["git", "update-index", "--cacheinfo", f"{entry[0]},{entry[1]},{rel}"],
                                   cwd=ROOT, check=True, env=git_trust.trusted_env())
        except (OSError, subprocess.CalledProcessError) as error:
            errors.append(f"could not restore {rel}: {error}")
    errors += drop_objects(build, record.get("sources") or [])
    if release and record.get("claims"):
        try:
            claims.release(record["claims"], root=ROOT,
                           tokens={claims.key_of(k): v for k, v in (record.get("tokens") or {}).items()})
        except Exception as error:                       # noqa: BLE001 - reported, the rest already ran
            errors.append(f"could not release the claims: {error}")
    _CACHE.clear()
    return errors


def recover_emit():
    """Undo every emit move whose process is gone (its journal remains), under the ledger lock;
    (restored, busy, errors). A journal is removed only once its undo had no error."""
    restored, busy, errors = [], [], []
    with ledger_locked():
        for path, record in emit_journals():
            if record is None:
                errors.append(f"{path} is unreadable; inspect it by hand (the before-state is in it)")
                continue
            if rename.journal_alive(record):
                busy.append(record.get("subject", path.name))
                continue
            problems = undo_emit(record)
            if problems:
                errors += problems
                continue
            remove_emit_journal(path)
            restored.append(record.get("subject", path.name))
    return restored, busy, errors


def defined_symbols(obj):
    """External symbols `obj` defines (name_dependents.coff_symbol_names); empty when unreadable."""
    import name_dependents
    try:
        return name_dependents.coff_symbol_names(Path(obj).read_bytes(), include_local=False) if obj else set()
    except OSError:
        return set()


def strong_symbols(obj):
    """External symbols `obj` defines outside COMDAT sections."""
    return defined_symbols(obj) - comdat_symbols(obj)


def committed_problem(movers, dest, obj_t, obj_x):
    """Why the objects `obj_t` (the TU's) and `obj_x` (the file's) do not show each mover as the
    TU's COMDAT with no strong copy left in the file, or None."""
    defined, comdats, strong_x = defined_symbols(obj_t), comdat_symbols(obj_t), strong_symbols(obj_x)
    for r in movers:
        if r["name"] not in defined:
            return f"{dest}'s object does not define {r['target_rva']} {r['name'][:60]}"
        if r["name"] not in comdats:
            return f"{dest} defines {r['target_rva']} outside a COMDAT"
        if r["name"] in strong_x:
            return f"the file still defines {r['target_rva']} outside a COMDAT"
        why = hand_written_problem(r["name"], [obj_t, obj_x], {})
        if why:
            return f"{r['target_rva']}: {why}"
    return None


# ---------------------------------------------------------------- shatter
# A mixed file carved into EVERY TU its rows are approved for at once, and
# deleted: no residual has to stand on its own (a split's commonest refusal is
# the residual losing a COMDAT only a carved body made it emit). Each unit is
# verified alone and through the merge verifier, all final objects are judged
# together by the link guard, and nothing is written until every unit passes.
PRIMARY_TEMPLATE = re.compile(r"^template\s*<\s*[^>\s]")   # not `template <>`


class ShatterPlan:
    """units {tu: [rows]}, take {tu: {span}}, own {tu: {datum}}, riders [rows]
    (unplaced COMDATs no definition spells: the first unit that emits one
    matched takes it), notes [str]; refused: a reason, else None."""

    def __init__(self, refused=None, **kw):
        self.refused = refused
        self.units, self.take, self.own = kw.get("units", {}), kw.get("take", {}), kw.get("own", {})
        self.riders, self.notes, self.texts = kw.get("riders", []), kw.get("notes", []), kw.get("texts", {})
        self.data_moves = kw.get("data_moves", {})
        self.residual = kw.get("residual")       # the file itself, when unplaced definitions keep it


def shatter_plan(text, rows, groups, data_rowed=frozenset(), here=None):
    """Where every matched row and every definition of `text` goes when the file
    `here` is carved into all the TUs of `groups` ({tu: rows}, breakdown(); ''
    holds unplaced rows), and the per-unit texts.

      * a row is carried by the one definition that spells it (identify()); one
        no definition spells (an inline member, an STLport COMDAT) only has to be
        emitted matched by its unit; a definition producing rows of two TUs, or
        a row two definitions spell, refuses;
      * an unplaced row rides with the TU owning its definition; one with no
        definition, or a primary template's (an instantiation), is a rider (the
        first unit that emits it matched takes it); one whose definition no TU
        owns stays in `here`, which then remains as one more unit (the
        residual), verified with the others. Primary templates, and types the
        chunker read as bodies, stay in every unit;
      * a definition that is not a row and has external linkage goes to the one
        unit whose bodies call it, else beside the owned definition before it;
        two calling units refuse. Internal helpers are copied by carve() as usual;
      * an external object used by several units is defined by the first of them
        in file order and declared `extern` by the others; one no unit uses is
        dropped, unless a data row owns it (refuses)."""
    spans = def_spans(text)
    scopes = span_scopes(text, spans)
    ids = identify(rows, spans, scopes)
    rowed = {i for v in ids.values() for i in v}
    dtors = {m.group(1): r["name"] for r in rows if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", r["name"]))}
    tus = sorted(t for t in groups if t)
    # a primary template is every unit's: its instantiations are emitted where used
    templ = {i for i, (_, _, body, kind) in enumerate(spans) if kind == "def" and PRIMARY_TEMPLATE.match(norm(body))}
    owner, units, riders = {}, {t: [] for t in tus}, []
    for t in tus:
        for r in groups[t]:
            units[t].append(r)
            if parent_of(r, dtors):
                continue                      # rides with its parent (breakdown placed it there)
            cands = ids[r["target_rva"]]
            if len(cands) > 1:
                return ShatterPlan(f"{r['target_rva']} {r['name']}: {len(cands)} definitions spell its name")
            if not cands or cands[0] in templ:
                continue                      # the unit must emit it matched: checked when verified
            other = owner.setdefault(cands[0], t)
            if other != t:
                return ShatterPlan(f"{r['target_rva']}: its definition also produces rows of {other}")
    stay = []
    for r in groups.get("", []):
        cands = ids[r["target_rva"]]
        if not cands or (len(cands) == 1 and cands[0] in templ):
            riders.append(r)
        elif len(cands) == 1 and owner.get(cands[0], here) != here:
            units[owner[cands[0]]].append(r)
        elif len(cands) == 1 and here:
            owner[cands[0]] = here            # an unplaced definition keeps the file as the residual unit
            stay.append(r)
        else:
            return ShatterPlan(f"unplaced row {r['target_rva']} {r['name']}: "
                               + ("the map must place it first" if len(cands) == 1 else
                                  f"{len(cands)} definitions spell its name"))
    if stay:
        tus = tus + [here]
        units[here] = stay
    order = sorted(owner, key=lambda i: spans[i][0])
    owned_text = {t: "\n".join(spans[i][2] for i in order if owner[i] == t) for t in tus}
    notes, shared = [], set()
    for i, (a, _, body, kind) in enumerate(spans):
        if i in templ:
            shared.add(i)
            continue
        if i in owner or i in rowed or kind == "data":
            continue
        hn = head_names(body) if kind == "def" else None
        if kind == "def" and hn is None:
            shared.add(i)                     # a type the chunker read as a body, a primary template: everyone's
            continue
        if kind == "def" and (INTERNAL.search(norm(body.split("{")[0])) or "" in scopes[i]
                              or (scopes[i] and DUPLICABLE.search(norm(body.split("{")[0])))):
            continue                          # carve() copies or keeps it where it is needed
        callers = [t for t in tus if hn and re.search(r"(?<![\w.>])%s\s*\(" % re.escape(hn[1]),
                                                       code_only(owned_text[t]))]
        if len(callers) > 1:
            return ShatterPlan(f"external helper {hn[1]} is called by {callers[0]} and {callers[1]}")
        before = [j for j in order if spans[j][0] < a]
        t = callers[0] if callers else owner[before[-1]] if before else owner[order[0]] if order else tus[0]
        owner[i] = t
        owned_text[t] += "\n" + body
        notes.append(f"unrowed {(hn or (None, body.strip()[:40]))[1]} goes with {t}")
    take = {t: {i for i, o in owner.items() if o == t} for t in tus}
    datums = list(data_decls(text))
    for i, (a, b, c, kind) in enumerate(spans):
        if kind == "data":
            m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$",
                          re.sub(r"__declspec\s*\([^)]*\)", " ", norm(c.split("=")[0])).strip())
            if m:
                datums.append((a, b, c, m.group(1), False))
    own = {t: set() for t in tus}
    for a, _, c, ident, internal in sorted(datums):
        users = [t for t in tus if names_used(ident, owned_text[t])]
        if not users and ident in data_rowed:
            return ShatterPlan(f"data row {ident} is used by no unit's bodies")
        if len(users) > 1 and not internal:
            own[users[0]].add(ident)
            notes.append(f"{ident} is defined in {users[0]}, extern in " + ", ".join(users[1:]))
    lost = sorted(rowed - set(owner) - shared)
    if lost:
        return ShatterPlan("a definition no unit takes: " + str(head_names(spans[lost[0]][2]) or spans[lost[0]][2][:40]))
    texts, data_moves = {}, {}
    for t in tus:
        cv = carve(text, take[t], rowed, data_rowed, frozenset(own[t]), frozenset(shared),
                   altname_keep=t == tus[0], source=here)
        if cv.refused:
            return ShatterPlan(f"{t}: {cv.refused}")
        texts[t] = cv.donor
        data_moves[t] = cv.data_moved
    return ShatterPlan(units=units, take=take, own=own, riders=riders, notes=notes, texts=texts,
                       data_moves=data_moves, residual=here if stay else None)


def shatter_keyed(path, root=ROOT):
    """Why `path` cannot simply disappear, [] when nothing but its rows names it:
    protected registers (the hatch register is rewritten by --update) and the
    header queue key a unit, not a row. data_ledger.csv keys and fold proofs are
    carried after the compile, by the objects' symbol tables (unit_key_carry)."""
    raws = {rel: (Path(root) / rel).read_bytes() for rel in rename.PROTECTED_PATH_KEYED
            if rel not in (HATCH_REGISTER, DATA_LEDGER) and (Path(root) / rel).exists()}
    out = [f"{rel}: {line[:100]}" for rel, line in vanished(raws, {path})]
    if header_queue_rows(root).get(path):
        out.append("reverse/header_queue.tsv: " + ", ".join(header_queue_rows(root)[path][:3]))
    return out


def shatter_repoint(raws, path, moves, data_moves, tus, stays=frozenset()):
    """{rel: new raw} with each moved row's path-keyed columns pointed at its TU,
    and [(rel, n)] of references to `path` left over (any leftover refuses).
    `stays`: rvas of rows a residual keeps; with a residual, data rows may stay too."""
    out = {}
    for rel, keycol in ROW_KEYED:
        if rel in raws:
            raw = raws[rel]
            for t in tus:
                raw, _ = repoint_rows(raw, rel, keycol, set(moves[t]), "source", path, t)
            out[rel] = raw
    rel = "reverse/data_rows.csv"
    if rel in raws:
        raw = raws[rel]
        for t in tus:
            names = data_row_names(raw, set(data_moves.get(t, ()))) if data_moves.get(t) else set()
            if names:
                raw, _ = repoint_rows(raw, rel, "name", names, "source", path, t)
        out[rel] = raw
    left = []
    keyed = dict(ROW_KEYED)
    for rel, column in rename.PATH_COLUMNS:
        raw = out.get(rel, raws.get(rel))
        if raw is None or (stays and rel == "reverse/data_rows.csv"):
            continue
        n = rename.repoint_column(raw, rel, column, path, path + ".left")[1]
        if stays and rel in keyed:
            n -= repoint_rows(raw, rel, keyed[rel], set(stays), "source", path, path + ".left")[1]
        if n:
            left.append((rel, n))
    return out, left


def shatter(path, dry_run=False, claim=True):
    report = {"file": path}
    rows = file_rows(path)
    if not rows:
        report["blocked"] = "no matched rows in that file"
        return report
    why = refusal(path, rows)
    if why and not why.startswith("keyed in a protected"):
        report["blocked"] = "file cannot be shattered: " + why
        return report
    original_bytes = (ROOT / path).read_bytes()
    text = original_bytes.decode("utf-8-sig", errors="replace").replace("\r\n", "\n").replace("\r", "\n")
    if "__FILE__" in strip(text):
        report["blocked"] = "file cannot be shattered: expands __FILE__ (the path reaches its bytes)"
        return report
    inc = included_by(path)
    if inc:
        report["blocked"] = "file cannot be shattered: #included by " + ", ".join(inc[:3])
        return report
    keyed = shatter_keyed(path)
    if keyed:
        report["blocked"] = "keyed by unit, not by row (retire or transfer first): " + "; ".join(keyed[:3])
        return report
    groups = breakdown(path)
    tus = sorted(t for t in groups if t)
    report["tus"] = tus
    if not tus:
        report["blocked"] = "no row of that file is approved for a TU"
        return report
    plan_ = shatter_plan(text, rows, groups, data_rowed_idents(path), here=path)
    if plan_.refused:
        report["blocked"] = plan_.refused
        return report
    if len(tus) < 2 and not plan_.residual:
        report["blocked"] = "every placed row is one TU's and nothing stays: use --merge"
        return report
    report["notes"] = plan_.notes
    report["residual"] = bool(plan_.residual)
    units_all = tus + ([path] if plan_.residual else [])   # the residual is one more unit, verified with the rest
    existing = {t: (ROOT / t).read_text(encoding="utf-8", errors="replace") for t in tus if (ROOT / t).exists()}
    for t in existing:
        own = file_rows(t)
        assigned = _CACHE["assigned"]
        wrong = [r for r in own if assigned.get(int(r["target_rva"], 16)) not in (t.lower(), None)
                 and not fold_alias(r) and not emission_held(r)]
        if wrong:
            report["blocked"] = f"{t} holds rows the map places elsewhere (split it first): {wrong[0]['target_rva']}"
            return report
    texts = {t: relocate_includes(plan_.texts[t], posixpath.dirname(path), posixpath.dirname(t)) for t in units_all}
    hatches = shatter_hatches(path, text, existing, texts)
    if hatches is None:
        report["blocked"] = "an escape-hatch count would grow (hatch_counters rule 3): a duplicated line carries one"
        return report
    # every unit alone, under its own TU's flags; riders go to the first unit emitting them matched
    units = {t: list(plan_.units[t]) for t in units_all}
    riders = list(plan_.riders)
    for t in units_all:
        (ROOT / t).parent.mkdir(parents=True, exist_ok=True)
        vt = Verifier(t)
        got = vt.matched(texts[t], units[t] + riders)
        if got is None:
            report["blocked"] = f"{t}: the carved bodies do not compile beside the TU: " + " | ".join(vt.errors)[:300]
            return report
        missing = [r["target_rva"] for r in units[t] if r["target_rva"] not in got]
        if missing:
            report["blocked"] = f"{t}: rows match only under the mixed file's own flags: " + ", ".join(missing[:5])
            return report
        took = [r for r in riders if r["target_rva"] in got]
        units[t] += took
        riders = [r for r in riders if r not in took]
    if riders:
        report["blocked"] = "unplaced COMDATs no unit emits matched: " + ", ".join(r["target_rva"] for r in riders[:5])
        return report
    moves = {t: [r["target_rva"] for r in units[t]] for t in tus}
    stays = {r["target_rva"] for r in units.get(path, [])}
    raws = {rel: (ROOT / rel).read_bytes() for rel, _ in rename.PATH_COLUMNS if (ROOT / rel).exists()}
    new_raws, left = shatter_repoint(raws, path, moves, plan_.data_moves, tus, stays)
    if left:
        report["blocked"] = "rows the shatter does not carry still name the file: " + \
            ", ".join(f"{rel} {n}" for rel, n in left)
        return report
    guard = ShatterLinkGuard(tus, path, moves, {t: plan_.data_moves[t] for t in tus}, root=ROOT,
                             expected_source=original_bytes)
    guard.load()
    why = guard.prepare({path: rows, **{t: file_rows(t) for t in existing}})
    if why:
        report["blocked"] = f"link guard: {why}"
        return report
    finals, records, report["units"] = {}, {}, {}
    if plan_.residual:              # the residual is written as carved: no merge, its own path and flags
        v = Verifier(path)
        got = v.matched(texts[path], units[path])
        if got is None or not stays <= got:
            report["blocked"] = "the residual does not re-verify"
            return report
        finals[path] = texts[path]
        records[path] = guard.record(path, v.obj, texts[path])
        report["units"][path] = len(units[path])
    for t in tus:
        don = {path: units[t]}
        if t in existing:
            don[t] = file_rows(t)
        rep = {"file": path, "tu": t, "accepted": [], "rejected": {}}
        rep = _merge(t, skeleton(t), don, rep, True, texts={path: texts[t]}, applier=lambda *a: {})
        if "blocked" in rep or "text" not in rep:
            report["blocked"] = f"{t}: " + rep.get("blocked", "the carved bodies do not verify in the TU") + \
                (": " + str(rep.get("rejected", {}).get(path, ""))[:200] if rep.get("rejected", {}).get(path) else "")
            return report
        need = [r for f in don for r in don[f]]
        v = Verifier(t)
        got = v.matched(rep["text"], need)
        if got is None or not {r["target_rva"] for r in need} <= got:
            report["blocked"] = f"{t}: the merged unit does not re-verify"
            return report
        finals[t] = rep["text"]
        records[t] = guard.record(t, v.obj, rep["text"])
        report["units"][t] = len(units[t])
    failures = guard.judge_records(records)
    if failures:
        report["blocked"] = "link: the shattered units would regress: " + "; ".join(failures[:3])[:300]
        if guard.provider_findings(failures):
            report["provider"] = {path: provider_report(guard.provider_findings(failures))}
        return report
    keys = carry_unit_keys(path, {u: r["obj"] for u, r in records.items()},
                           guard.records.get(path, {}).get("obj"), new_raws.get("reverse/data_rows.csv"))
    if keys.problems:
        report["blocked"] = "unit keys (data_ledger.csv / fold proofs): " + "; ".join(keys.problems[:3])[:300]
        return report
    new_raws.update(keys.raws)
    if keys.moved:
        report["carried"] = dict(keys.moved)
    if keys.notes:
        report["notes"] = report.get("notes", []) + keys.notes
    report["verified"] = True
    if dry_run:
        return report
    if not write_shatter(report, path, tus, rows, finals, new_raws, bool(hatches), claim=claim):
        return report
    report["subject"] = (f"Shatter {posixpath.basename(path)} into {len(tus)} TUs "
                         f"({sum(len(units[t]) for t in tus)} rows, tu_map approved TUs"
                         + (f"; {len(stays)} unplaced rows stay" if stays else "") + ")")
    report["trailer"] = carry_trailer("--shatter", path, "its TUs", hatches, keys.moved)
    if not report["trailer"]:
        del report["trailer"]
    return report


def carry_trailer(lane, path, where, hatches, keys):
    """The one Verifier-Change line for a carve that moved hatch counts or
    protected unit keys (both are transfers: totals kept), else None."""
    what = (["escape-hatch counts (hatch_counters --update)"] if hatches else []) + \
        (["data_ledger.csv unit keys"] if DATA_LEDGER in keys else [])
    if not what:
        return None
    return (f"Verifier-Change: tu_skeleton {lane} moved " + " and ".join(what) + f" from {path} to {where}, "
            "each to the unit whose object defines it (totals kept)")


def shatter_hatches(path, before, existing, texts):
    """{(hatch, token): count} moved out of `path`, or None when any per-(hatch,
    token) total over the file and its TUs would grow (hatch_counters rule 3)."""
    try:
        import hatch_counters as H
    except ImportError:
        return {}

    def totals(counter):
        out = collections.Counter()
        for (hatch, _p, token), n in counter.items():
            out[(hatch, token)] += n
        return out
    old = totals(H.scan(path, before))
    new = collections.Counter()
    for t, donor in texts.items():
        old += totals(H.scan(t, existing.get(t, "")))
        new += totals(H.scan(t, existing.get(t, "") + "\n" + donor))
    if any(new[k] > old.get(k, 0) for k in new):
        return None
    return {k: n for k, n in totals(H.scan(path, before)).items() if n}


def write_shatter(report, path, tus, rows, finals, raws, hatches, claim=True):
    """Claim the scope and write the shatter; False when another worker holds the scope (`report` says
    so). An exception gives back what this call took, unless the write had started (give_back_after)."""
    held = None
    if claim:
        held = claim_scope(tus[0], {path: rows, **{t: [] for t in tus[1:]}})
        if held:
            give_back(held)
            report["blocked"] = held_message(held)
            return False
    try:
        report["staged"] = apply_shatter(path, finals, raws, hatches)
    except BaseException as error:
        give_back_after(error, report, held)
        raise
    return True


@marks_half_applied
def apply_shatter(path, finals, raws, hatches, root=ROOT):
    """Write every TU, repoint the moved rows, delete the mixed file (or write
    its residual, when `finals` holds one under its own path), stage it all."""
    stays = path in finals
    if hatches:
        others = dirty_others(root, set(finals) | {path})
        if others:
            raise NothingWritten("tu_skeleton: the hatch register is rewritten from the whole tree; commit or stash "
                             "the other modified files first: " + ", ".join(others[:5]))
    moved = []
    for rel, raw in raws.items():
        p = Path(root) / rel
        if p.read_bytes() != raw:
            p.write_bytes(raw)
            moved.append(rel)
    cfg = Path(root) / rename.SOURCES_CFG
    if cfg.exists():
        raw = cfg.read_bytes()
        for t in sorted(finals):
            raw, _ = ensure_sources_cfg(raw, t)
        if not stays:
            raw, _ = repoint_sources_cfg(raw, {path}, sorted(finals)[0])
        if raw != cfg.read_bytes():
            cfg.write_bytes(raw)
            moved.append(rename.SOURCES_CFG)
    for t, text in finals.items():
        (Path(root) / t).parent.mkdir(parents=True, exist_ok=True)
        (Path(root) / t).write_text(text, encoding="utf-8", newline="\n")
    for t, text in finals.items():
        if t != path:
            moved += [rel for rel in refresh_reports(root, [] if stays else [path], t, text) if rel not in moved]
    if not stays:
        subprocess.run(["git", "rm", "-q", "--", path], cwd=root, check=True)
    subprocess.run(["git", "add", "--", *sorted(finals), *moved], cwd=root, check=True)
    if hatches:
        subprocess.run([sys.executable, "tools/hatch_counters.py", "--update"], cwd=root, check=True)
        subprocess.run(["git", "add", "--", HATCH_REGISTER], cwd=root, check=True)
        moved.append(HATCH_REGISTER)
    _CACHE.clear()
    return sorted(finals) + moved + ([] if stays else [path + " (deleted)"])


def data_rowed_idents(path):
    """Identifiers of the data rows reverse/data_rows.csv binds to `path`."""
    dr = ROOT / "reverse/data_rows.csv"
    if not dr.exists():
        return frozenset()
    out = set()
    for row in csv.DictReader(io.StringIO(dr.read_text(encoding="utf-8", errors="replace"), newline="")):
        if row.get("source") == path:
            m = re.match(r"^\?([A-Za-z_]\w*)@@", row["name"])
            out.add(m.group(1) if m else c_ident(row["name"]))
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
        ident = m.group(1) if m else c_ident(row["name"])
        if ident in idents:
            out.add(row["name"])
    return out


@marks_half_applied
def apply_split(tu, text, path, residual, rvas, hatches, root=ROOT, data_moved=(), extra=None):
    """Write the split; `extra` {rel: raw}: carried unit-key registers (unit_key_carry)."""
    moved = {}
    if hatches:
        dirty = subprocess.run(["git", "status", "--porcelain", "--untracked-files=no"], cwd=root,
                               capture_output=True, text=True).stdout.splitlines()
        others = [l for l in dirty if l[3:] not in (tu, path)]
        if others:
            raise NothingWritten("tu_skeleton: the hatch register is rewritten from the whole tree; commit or stash "
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
    for rel, raw in (extra or {}).items():
        if (Path(root) / rel).read_bytes() != raw:
            (Path(root) / rel).write_bytes(raw)
            moved[rel] = "unit keys carried"
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


def override_flags_key(flags):
    """Ignore only a leading duplicate of compiler_command's baseline -O2.

    Keep the remaining tokens in order: later optimization, architecture and
    tuning options can change codegen and must still agree.
    """
    tokens = flags.split()
    return tuple(tokens[1:] if tokens[:1] == ["-O2"] else tokens)


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
    if any(override_flags_key(r["flags"]) != override_flags_key(flags) for r in mine):
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


# ---------------------------------------------------------------- unit keys
# data_ledger.csv names a unit by the object that defines a global (`source`) or
# a TU-local static (`name@source` in `names`); a fold proof names the unit whose
# object compiles the pinned body (`fold-proof=source`). A carve moves definitions
# between objects, so --shatter and --split carry each such key to the one unit
# whose compiled object defines its symbol, read off the objects' symbol tables.
# A key two units define, or none, is refused: nothing is invented or renamed.
PINS = "reverse/symbols.csv"
FUNCTIONS = "reverse/functions.csv"
COFF_EXTERNAL, COFF_STATIC, COFF_CODE = 2, 3, 0x20


def object_definitions(obj):
    """{"code", "data", "static"}: the external code symbols, external data
    symbols and TU-local static data symbols `obj` defines (section symbols and
    `$`/`.` names left out; a static is one data_ledger.py would write name@source)."""
    import build
    obj = Path(obj)
    stat = obj.stat()
    _data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    out = {"code": set(), "data": set(), "static": set()}
    external = {s["name"] for s in symbols if s.get("storage") == COFF_EXTERNAL and s["section"] > 0}
    for s in symbols:
        if s["section"] <= 0 or s.get("storage") not in (COFF_EXTERNAL, COFF_STATIC) \
                or s["name"].startswith(("$", ".")):
            continue
        sec = sections[s["section"] - 1]
        if s["storage"] == COFF_STATIC and s["value"] == 0 and s["name"] == sec["name"]:
            continue                                  # a section symbol
        code = bool(sec["characteristics"] & COFF_CODE)
        if s["storage"] == COFF_EXTERNAL:
            out["code" if code else "data"].add(s["name"])
        elif not code and s["name"] not in external:
            out["static"].add(s["name"])
    return out


def object_calls(obj, name):
    """The REL32 callees of `name`'s body in `obj` (empty when it defines none)."""
    import build
    try:
        _body, relocs = build.read_object_symbol_bytes(Path(obj), name, code_only=True)
    except (OSError, ValueError, SystemExit):
        return set()
    return {symbol for _offset, kind, symbol in relocs if kind == build.REL32}


class UnitKeys:
    """What a carve does to `path`'s unit keys: new register bytes ({rel: raw},
    only those that change), {rel: keys moved}, notes and problems (any problem
    refuses the carve; nothing is written)."""

    def __init__(self):
        self.raws, self.moved, self.notes, self.problems = {}, {}, [], []


def unit_key_carry(path, defs, ledger_raw=None, pins_raw=None, original=None, owners=None,
                   calls=None, addressed=frozenset()):
    """Carry `path`'s data_ledger.csv and fold-proof keys to the units that define
    their symbols (pure: every object fact comes in as an argument).

      defs      {unit: object_definitions()} of every object the carve leaves; a
                unit named `path` is the residual (a key it still defines stays);
      original  object_definitions() of the uncarved file: a key it did not define
                either was stale before the carve, and stays while `path` remains;
      owners    {data name: source} of reverse/data_rows.csv after the carve: a
                verified owner is the ledger's `source`, and the symbol table must
                put the definition there too;
      calls     calls(unit, name): REL32 callees of name's body in unit's object. A
                fold proof proves an unrowed callee from the same object, so every
                callee the original object defined and no row or pin places
                (`addressed`) must still be defined beside the pinned body.

    A symbol two carved units define, one no unit defines, and a move onto a key
    the register already holds (two keys would collapse into one) are problems."""
    out = UnitKeys()

    def home(symbol, kinds):
        # a key stale before the carve stays while the file remains, whoever defines the symbol now
        if path in defs and original is not None and not any(symbol in original[k] for k in kinds):
            out.notes.append(f"{symbol}: {path} did not define it before the carve either (key left as it was)")
            return path
        # every final object, the residual included: two definers are ambiguous wherever they are
        who = sorted(u for u in defs if any(symbol in defs[u][k] for k in kinds))
        if len(who) > 1:
            out.problems.append(f"{symbol} is defined by both {who[0]} and {who[1]}")
            return None
        if who:
            return who[0]
        out.problems.append(f"no carved unit defines {symbol}")
        return None

    if ledger_raw is not None:
        eol = _eol(ledger_raw)
        lines = ledger_raw.decode("utf-8").split(eol)
        header = next(csv.reader([lines[0]]))
        at_name, at_source, at_names = header.index("name"), header.index("source"), header.index("names")
        moved = 0
        for i in range(1, len(lines)):
            if path not in lines[i]:
                continue
            cells = next(csv.reader([lines[i]]))
            if len(cells) != len(header):
                continue
            before = list(cells)
            if cells[at_source] == path:
                to = home(cells[at_name], ("data", "static"))
                owner = (owners or {}).get(cells[at_name])
                if to is not None and owner is not None and owner != to:
                    out.problems.append(f"{cells[at_name]}: data_rows.csv puts it in {owner}, its object in {to}")
                elif to is not None:
                    cells[at_source] = to
            names = cells[at_names].split(";") if cells[at_names] else []
            new = []
            for n in names:
                name, sep, where = n.rpartition("@")
                to = home(name, ("static",)) if sep and where == path else None
                new.append(f"{name}@{to}" if to is not None else n)
            if new != names:
                if len(set(new)) != len(new):
                    out.problems.append(f"data_ledger.csv {cells[0]}: carrying {path}'s static onto a unit "
                                        "already keyed there collapses two keys")
                cells[at_names] = ";".join(sorted(new))
            if cells != before:
                buf = io.StringIO()
                csv.writer(buf, lineterminator="").writerow(cells)
                lines[i] = buf.getvalue()
                moved += 1
        if moved:
            out.raws[DATA_LEDGER] = eol.join(lines).encode("utf-8")
            out.moved[DATA_LEDGER] = moved
    if pins_raw is not None:
        from pin_admission import FOLD_PROOF_RE
        dest = {}
        for row in csv.DictReader(io.StringIO(pins_raw.decode("utf-8"), newline="")):
            found = FOLD_PROOF_RE.search(row.get("notes") or "")
            if not found or found.group(1) != path:
                continue
            to = home(row["name"], ("code",))
            if to is None or row["name"] not in defs[to]["code"]:
                continue                  # refused, or a stale key left as it was
            # the callee chain is checked in the object that keeps the proof, the residual included
            todo, seen = [row["name"]], set()
            while todo and calls is not None:
                n = todo.pop()
                if n in seen:
                    continue
                seen.add(n)
                for c in sorted(calls(to, n)):
                    if c in defs[to]["code"]:
                        todo.append(c)
                    elif original is not None and c in original["code"] and c not in addressed:
                        out.problems.append(f"fold proof {row['name']}: its callee {c} would leave {to}'s object")
            if to != path:
                dest[row["name"]] = to
        if dest:
            raw, n = repoint_fold_proofs(pins_raw, {path}, dest)
            if n:
                out.raws[PINS], out.moved[PINS] = raw, n
    left = {rel: raw for rel, raw in (("ledger", out.raws.get(DATA_LEDGER, ledger_raw)),
                                      ("pins", out.raws.get(PINS, pins_raw))) if raw is not None}
    if path not in defs and not out.problems:
        for rel, line in vanished({k: v for k, v in left.items() if k == "ledger"}, {path}):
            out.problems.append(f"data_ledger.csv still keys the deleted file: {line[:120]}")
        if "pins" in left and repoint_fold_proofs(left["pins"], {path}, "x")[1]:
            out.problems.append("reverse/symbols.csv: a fold proof still names the deleted file")
    return out


def carry_unit_keys(path, objs, original_obj, data_rows_raw=None, root=ROOT):
    """unit_key_carry() over the registers in `root` and the compiled objects
    `objs` ({unit: object}; `path` itself for a residual)."""
    root = Path(root)
    ledger = root / DATA_LEDGER
    pins = root / PINS
    ledger_raw = ledger.read_bytes() if ledger.exists() else None
    pins_raw = pins.read_bytes() if pins.exists() else None
    needed = (ledger_raw is not None and path.encode() in ledger_raw) or \
             (pins_raw is not None and repoint_fold_proofs(pins_raw, {path}, "x")[1])
    if not needed:
        return UnitKeys()
    out = UnitKeys()
    missing = [u for u, o in objs.items() if o is None or not Path(o).exists()]
    if missing or original_obj is None or not Path(original_obj).exists():
        out.problems.append("unit keys: no compiled object for " + ", ".join(missing or [path]))
        return out
    defs = {u: object_definitions(o) for u, o in objs.items()}
    owners = None
    if data_rows_raw is not None:
        owners = {r["name"]: r["source"] for r in csv.DictReader(io.StringIO(data_rows_raw.decode("utf-8"), newline=""))}
    addressed = {r["name"] for r in ledger_rows() if r.get("status") == "matched"}
    if pins_raw is not None:
        addressed |= {r["name"] for r in csv.DictReader(io.StringIO(pins_raw.decode("utf-8"), newline=""))}
    return unit_key_carry(path, defs, ledger_raw, pins_raw, object_definitions(original_obj), owners,
                          lambda u, n: object_calls(objs[u], n), frozenset(addressed))


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
    """The TU, its donors and the addresses of the rows they move. An ICF alias row
    (fold_alias) adds no address: its address is the identity row's, which the unit
    owning that row claims. A shared fold such as 0x0007FAB3 carries hundreds of alias
    rows across the tree, and claiming it serialised every merge that moved one of them
    (re_attempts.log: blocked-on=0x0007FAB3)."""
    keys = [f"file:{tu}"] + [f"file:{f}" for f in sorted(don) if f != tu]
    return keys + sorted({r["target_rva"] for rows in don.values() for r in rows
                          if not (r.get("name") and fold_alias(r))})


class Held(list):
    """claim_scope's refused keys. `unconfirmed` names those whose claim push failed while no
    other worker held them (origin refused the push, e.g. no write access, or never confirmed
    it); `unavailable` is set when origin could not be read at all. Empty (falsy) when every
    key was claimed: `tokens` then holds their fencing tokens, for a release that must not
    take a successor's claim (claims.release(tokens=...))."""
    unconfirmed = ()
    unavailable = ""
    tokens = {}
    acquired = ()


def claim_scope(tu, don, root=ROOT, skip=()):
    """Claim the TU, its donors and their rows (less the keys in `skip`, which this operation
    already holds: claiming them again would renew them and rotate their tokens); [] or the
    keys we did not get (a Held list). Either way `acquired` names the keys this call took
    that this worker did not already hold (ClaimResult.prior) and holds a token for, and
    `tokens` exactly their tokens: only those may be given back (give_back; review of
    bfb856bfbf and 9459886c66)."""
    skip = {claims.key_of(k) for k in skip}
    keys = [k for k in claim_keys(tu, don) if claims.key_of(k) not in skip]
    try:
        res = claims.claim(keys, note=f"tu_skeleton {tu}", root=root)
    except claims.ClaimsUnavailable as e:
        held = Held([f"(claims unavailable: {e})"])
        held.unavailable = str(e)
        return held
    prior = {claims.key_of(k) for k in getattr(res, "prior", ()) or ()}
    tokens = {claims.key_of(k): v for k, v in (getattr(res, "tokens", {}) or {}).items()}
    claimed = getattr(res, "claimed", None)
    acquired = [k for k in (claims.key_of(k) for k in (tokens if claimed is None else claimed))
                if k not in prior and k in tokens]
    if res.refused:
        names = {claims.key_of(k): k for k in keys}
        held = Held(str(names.get(k, k)) for k in res.refused)
        held.unconfirmed = [str(names.get(k, k)) for k in getattr(res, "unconfirmed", ())]
    else:
        held = Held()
    held.acquired = acquired
    held.tokens = {k: tokens[k] for k in acquired}
    return held


def give_back(*helds):
    """Release exactly what each claim_scope result acquired, each key fenced by its token, so
    a key this worker held before the call, or one a successor has taken since, is never
    deleted. A key with no token is left to expire. [] when there was nothing to release."""
    keys, tokens = [], {}
    for held in helds:
        for k in getattr(held, "acquired", ()) or ():
            if k in (getattr(held, "tokens", {}) or {}) and k not in tokens:
                keys.append(k)
                tokens[k] = held.tokens[k]
    return claims.release(keys, tokens=tokens) if keys else []


def give_back_after(error, report, *helds):
    """`error` is leaving a call that claimed `helds`: release what it took (give_back) when nothing was
    written (review of dee0813e84), and never mask `error`. A move that wrote keeps its claims: a merge
    or split has no journal, so a half-written tree is restored by hand, and releasing would hand its
    files to another worker meanwhile; an applied move's claims settle when it lands. They expire by
    themselves, and an operator can release them once the tree is restored."""
    if getattr(error, "half_applied", False):
        print(f"tu_skeleton: {type(error).__name__} during the write: the tree may be half written, so the claims "
              "stay held; restore it (git restore --staged --worktree on the paths git status lists), then "
              "tools/claims.py release the scope", file=sys.stderr)
        return
    if "repointed" in report or "staged" in report:
        return
    try:
        give_back(*helds)
    except Exception as failed:                 # noqa: BLE001 - `error` is what the caller must see
        print(f"tu_skeleton: the claims were not given back ({failed}); they expire by themselves", file=sys.stderr)


def key_text(key):
    """A claim key as the claim service names it (claims.label for an RVA: `0x00002000`; a
    scope key as is), so it round-trips through claims.key_of: a decimal `8192` would be
    read back as 0x8192 (review of 9459886c66)."""
    key = claims.key_of(key)
    return f"0x{key:08X}" if isinstance(key, int) else key


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


def repoint_fold_proofs(raw, gone, tu, label=PINS):
    """Move exact fold-proof source tokens, preserving pin identities and prose.
    `tu`: the new source, or {pin name: new source} (a pin it omits is kept).
    `label`: the register `raw` holds, symbols.csv (pins) or functions.csv
    (code rows whose notes carry the same token).

    Changed pin notes still go through normal pin admission, which recompiles
    the proof source and checks bytes and relocations at its new path.
    """
    from pin_admission import FOLD_PROOF_RE
    rename.ledger_io.lf_terminator(raw, label)
    records = rename.ledger_io.split_records(raw)
    header = rename.ledger_io.fields(records[0][0]) if records else []
    if "notes" not in header:
        raise rename.Refusal(f"{label} has no 'notes' column")
    index, gone = header.index("notes"), set(gone)
    at_name = header.index("name") if "name" in header else 0
    out, count = [records[0][0] + records[0][1]], 0
    for payload, term in records[1:]:
        text = payload.decode("utf-8")
        spans = rename.field_spans(text)
        dest = tu
        if isinstance(tu, dict) and len(spans) > at_name:
            dest = tu.get(text[spans[at_name][0]:spans[at_name][1]].strip('"'))
        if len(spans) > index and dest is not None:
            start, end = spans[index]
            field = text[start:end]
            quoted = field.startswith('"') and field.endswith('"')
            notes = field[1:-1].replace('""', '"') if quoted else field

            def replace(match):
                if match.group(1) not in gone:
                    return match.group(0)
                return match.group(0)[:match.start(1) - match.start()] + dest

            changed = FOLD_PROOF_RE.sub(replace, notes)
            if changed != notes:
                field = '"' + changed.replace('"', '""') + '"' if quoted else changed
                payload = (text[:start] + field + text[end:]).encode("utf-8")
                count += 1
        out.append(payload + term)
    return b"".join(out), count


def repoint_all(root, gone, tu):
    """Point path-keyed columns, fold-proof tokens and doxygen INPUTs at the TU.
    Returns {file: records}; protected registries retain their normal gates.
    A functions.csv row's notes token `fold-proof=<donor>` moves with it: the
    absorbed donor's body now compiles in the TU's object. Naming provenance
    keeps its evidence but follows the source, which rename.revert uses."""
    moved = {}
    for rel, column in (*rename.PATH_COLUMNS, (rename.NAME_BASIS, "source")):
        path = Path(root) / rel
        if not path.exists():
            continue
        before = raw = path.read_bytes()
        total = 0
        for f in sorted(gone):
            raw, n = rename.repoint_column(raw, rel, column, f, tu)
            total += n
        if rel == FUNCTIONS:
            raw, n = repoint_fold_proofs(raw, gone, tu, label=rel)
            if n:   # a row whose source and fold proof both moved counts once
                total = sum(a != b for a, b in zip(rename.ledger_io.split_records(before),
                                                   rename.ledger_io.split_records(raw)))
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


CONFIDENCE_RANK = {"approved": 3, "proposed": 2, "displaced": 1}


def map_regressions(tu, accepted=(), moved_rows=None):
    """Why moving rows into `tu` would cost the map an approval, or None: every row of each
    `accepted` file (a merge, deleting the others), and the rows of `moved_rows` {file: rvas} (a
    move that leaves its file in place, as repoint_rows repoints them: at those addresses, of that
    file; review of dee0813e84: splitting B::f out of Code/Old/B.cpp dropped its sibling B::g from
    approved to proposed). The map is rebuilt in memory (tu_map.build, a pure function of its
    inputs) over the ledger as the move leaves it and compared with the current one (map_rows): N hints follow a file's directory, so moving one file of a
    provisional group can leave a sibling with no interleaving cluster (Merge lane 2,
    2026-11-07: relocating Upgrade/BaseUpgrade.cpp alone dropped 0x004B37CA from approved to
    proposed, and its funclets stayed approved for the deleted path). Refuses when any code
    row's confidence falls (approved > proposed > displaced > none), or when a row the
    rebuilt map approves or proposes names a path the merge deletes."""
    moved = set(accepted)
    gone = {f.lower() for f in accepted if f.lower() != tu.lower()}
    rows = {f: {int(x, 16) for x in rvas} for f, rvas in (moved_rows or {}).items()}

    def moves(r):
        if r.get("source") in moved:
            return True
        rva = r.get("target_rva") or ""
        return r.get("source") in rows and rva.lower().startswith("0x") and int(rva, 16) in rows[r["source"]]
    ledger = [dict(r, source=tu) if moves(r) else r for r in tu_map.read_csv(LAYOUT.path("functions.csv"))]
    before = {r["rva"].lower(): r for r in map_rows() if r["kind"].startswith("code")}
    after = {str(r["rva"]).lower(): {k: str(v) for k, v in r.items()}
             for r in tu_map.build(LAYOUT, ledger) if str(r["kind"]).startswith("code")}
    lowered = []
    for rva, b in sorted(before.items()):
        a = after.get(rva) or {"confidence": "", "tu": ""}
        if CONFIDENCE_RANK.get(a["confidence"], 0) < CONFIDENCE_RANK.get(b["confidence"], 0):
            lowered.append(f"{rva} {b['confidence']} {b['tu'] or '-'} -> {a['confidence'] or 'none'} {a['tu'] or '-'}")
    orphaned = sorted(f"{rva} {a['confidence']} {a['tu']}" for rva, a in after.items()
                      if a["tu"] and a["tu"].lower() in gone and a["confidence"] in ("approved", "proposed"))
    if not lowered and not orphaned:
        return None
    return ("this move would cost the map approvals (rebuilt in memory after it): "
            + "; ".join(([f"{len(lowered)} lowered: " + ", ".join(lowered[:4])] if lowered else [])
                        + ([f"{len(orphaned)} placed in a path it deletes: " + ", ".join(orphaned[:4])]
                           if orphaned else []))
            + " (move the group's files together)")[:600]


@marks_half_applied
def apply(tu, accepted, text, root=ROOT, carry=None):
    gone = [f for f in accepted if f != tu]
    if carry and carry.hatch:
        # hatch_counters --update rewrites the register from the whole tree
        others = dirty_others(root, set(accepted) | {tu})
        if others:
            raise NothingWritten("tu_skeleton: the hatch register is rewritten from the whole tree; commit or stash "
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
    g.add_argument("--emit-move", metavar="FILE[,FILE...]",
                   help="repoint the files' deleting-destructor rows approved for --for TU, which the TU emits "
                        "byte-exact, as one transaction")
    g.add_argument("--recover-emit", action="store_true",
                   help="undo every --emit-move a killed run left (its journal under build/tu_skeleton/emit-journal)")
    g.add_argument("--shatter", metavar="FILE",
                   help="carve a mixed FILE into every TU its rows are approved for, verified together, and delete it")
    g.add_argument("--merge-all", action="store_true",
                   help="merge every queued TU (tools/merge_all.py): parallel worktrees, a decision queue")
    ap.add_argument("--for", dest="for_tu", metavar="TU", help="with --split: the destination TU (omit to list)")
    ap.add_argument("--prepared", metavar="PATH=TEXT", action="append",
                    help="with --split: the TU's whole final text (a file), written with the carve in one transaction; "
                         "with --emit-move: the whole final text of the TU or of a listed file (repeatable)")
    ap.add_argument("--rva", help="with --emit-move: only these rows (comma-separated hex); all must move")
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
    elif a.recover_emit:
        restored, busy, errors = recover_emit()
        for subject in restored:
            print(f"restored: {subject}")
        for subject in busy:
            print(f"still running, left alone: {subject}")
        for error in errors:
            print(f"error: {error}")
        return 1 if errors else 0
    elif a.emit_move:
        if not a.for_tu:
            ap.error("--emit-move takes --for TU")
        rvas = [x for x in (a.rva or "").split(",") if x.strip()] or None
        prepared = {}
        for item in a.prepared or []:
            target, sep, source = item.partition("=")
            if not sep or not target or not source:
                ap.error("--prepared takes PATH=TEXT")
            prepared[target.replace("\\", "/")] = Path(source).read_bytes().decode("utf-8-sig").replace("\r\n", "\n")
        files = [f.strip() for f in a.emit_move.split(",") if f.strip()]
        rep = emit_move(files[0] if len(files) == 1 else files, a.for_tu, rvas, a.dry_run, claim=not a.no_claim,
                        prepared=prepared)
        for k, val in rep.items():
            print(f"{k}: {val}")
        return 0 if rep.get("subject") or (a.dry_run and rep.get("moved")) else 2
    elif a.shatter:
        rep = shatter(a.shatter, a.dry_run, claim=not a.no_claim)
        for k, val in rep.items():
            print(f"{k}: {val}")
        return 0 if rep.get("subject") or (a.dry_run and rep.get("verified")) else 2
    elif a.split:
        if not a.for_tu:
            for tu, rows in sorted(breakdown(a.split).items(), key=lambda kv: -len(kv[1])):
                print(f"{len(rows):5d} rows  {tu or '(no approved TU)'}"
                      f"{'' if not tu or (ROOT / tu).exists() else '  (no file yet)'}")
            return 0
        prepared = None
        if a.prepared:
            target, sep, source = a.prepared[0].partition("=")
            if (len(a.prepared) > 1 or not sep
                    or target.replace("\\", "/").lower() != a.for_tu.replace("\\", "/").lower()):
                ap.error("--prepared takes one TU=TEXT for the --for TU")
            prepared = Path(source).read_bytes().decode("utf-8-sig").replace("\r\n", "\n")
        rep = split(a.split, a.for_tu, a.dry_run, claim=not a.no_claim, prepared=prepared)
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
    try:
        sys.exit(main())
    except tu_map.NoZhTree as error:     # --plan, --merge, --split and --queue read the map
        sys.exit(f"tu_skeleton: {error}")
