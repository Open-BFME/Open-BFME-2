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
Duplicate declarations are emitted once; a type that two donors spell
differently gets one spelling (first, else longest) and the byte check decides
whether that was safe. A donor that also holds rows of another TU is never
split here ("mixed"): it stays a satellite and is reported.

Applying a merge writes the TU file (`// cl:` line chosen from the donors' own
flag sets by the same verification), repoints every ledger row of each absorbed
donor at it, deletes the absorbed donors and stages the result. The commit hook
then byte-verifies it again; this tool never commits.

The map is the one tu_map.py builds from the current inputs: when the committed
tu_map.csv is stale (tu_map.py --check-fresh) it is rebuilt in memory, never
written, so a merge never carries a regenerated map and two merges never
conflict over it.

A donor is refused, not absorbed, when deleting it is not mechanical: it is
untracked, vendored, keyed in a protected path-keyed register (a
Verifier-Change commit re-keys those), #included by another file, or expands
__FILE__ (its path reaches its bytes). These are tools/rename_files.py's
refusals, read from the same tree.

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


# ---------------------------------------------------------------- chunking
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
                    break
                j = k + 1
            lead = text[start:text.rfind("\n", 0, i) + 1]
            if lead.strip():
                out.append(("tail", lead))
            out.append(("pp", text[i:k].rstrip()))
            i = start = min(k + 1, n)
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
                aggregate = re.match(r"^(template\s*<[^>]*>\s*)?(typedef\s+)?(class|struct|enum|union)\b", body) \
                    and not re.search(r"\)\s*(const)?\s*$", head.strip())
                if not aggregate:
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


def strip(t):
    t = re.sub(r"/\*.*?\*/", " ", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


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
    if "map" not in _CACHE:
        stale = tu_map.check_fresh(LAYOUT)
        rows = tu_map.build(LAYOUT) if stale else tu_map.read_csv(LAYOUT.out)
        _CACHE["map"] = [{k: str(v) for k, v in r.items()} for r in rows]
        _CACHE["stale"] = stale
    return _CACHE["map"]


def tree():
    """rename_files' refusal reader (tracked files, protected keys, includes)."""
    if "tree" not in _CACHE:
        _CACHE["tree"] = rename_files.Tree(rename.Context(ROOT, object_scan=False))
    return _CACHE["tree"]


# rename_files.Tree reasons that do not apply to absorbing a donor: its name is
# not kept either way, and its rows keep theirs.
NOT_REFUSALS = ("an approved retail TU path", "recorded canonical")


def refusal(f, rows):
    why = tree().refusal(f, rows)
    return None if why is None or why.startswith(NOT_REFUSALS) else why


def skeleton(tu):
    """Approved rows of `tu` in retail order, each with its ledger row (or None)."""
    m = map_rows()
    want = [r for r in m if r["tu"].lower() == tu.lower() and r["confidence"] == "approved"
            and r["kind"].startswith("code")]
    led = {}
    for r in ledger_rows():
        if "gen-alias" not in (r["notes"] or "") and r["target_rva"].startswith("0x"):
            led.setdefault(int(r["target_rva"], 16), r)
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
        # an EH funclet is emitted with its parent and lives where the parent lives
        foreign = [r for r in own if (home.get(m.group(1)) if (m := FUNCLET.match(r["name"])) and m.group(1) in home
                                      else assigned.get(int(r["target_rva"], 16))) != tu.lower()]
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


# ---------------------------------------------------------------- compose
# Redefinitions cl reports when two donors (or a donor and a header another
# donor includes) both declare one type: the later, donor-local copy is dropped
# and the byte check decides whether the surviving spelling was safe.
REDEFINED = re.compile(r"error C2011: '([A-Za-z_]\w*)' : '(?:struct|class|enum|union)' type redefinition"
                       r"|error C2371: '([A-Za-z_]\w*)' : redefinition; different basic types"
                       r"|error C2365: '([A-Za-z_]\w*)' : redefinition; previous definition was")


def redefined(errors):
    return {next(g for g in m.groups() if g) for e in errors for m in [REDEFINED.search(e)] if m}


def compose(tu, sk, files, texts, flags, strategy, drop=frozenset(), drop_all=frozenset()):
    """Declarations first (donor order, one spelling each), then bodies in retail order.

    `files` is in donor order with the seed first. A type two donors spell
    differently is emitted once, from the donor whose spelling is chosen and at
    that donor's own position, so whatever it depends on is already declared.
    """
    parsed = {f: chunks("\n".join(l for l in texts[f].lstrip("\ufeff").splitlines()
                                  if not l.startswith("// cl:") and l.strip() != "// stlport") + "\n")
              for f in files}
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
    pps, decls, seen = [], [], set()
    for f in files:
        for kind, c in parsed[f]:
            if kind == "pp":
                if c.strip() not in pps:
                    pps.append(c.strip())
            elif kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and (k[1] in drop_all or (k[1] in drop and f != files[0])):
                    continue   # cl saw it defined earlier: the seed's copy, else a header (includes come first)
                if k[0] in ("type", "typedef") and k[1] in drop and k not in seen:
                    seen.add(k)    # the seed's own spelling, whichever spelling the strategy chose
                    decls.append(c.strip("\n"))
                    continue
                if k in seen or (k in chosen and chosen[k][1] != f):
                    continue
                seen.add(k)
                decls.append((chosen[k][0] if k in chosen else c).strip("\n"))
    body, done, bodies = [], set(), set()
    for t, led in sk:
        f = led["source"] if led else None
        if f in files:
            if f in done:
                continue
            done.add(f)
            body.append(f"// ---- from {f}")
            for kind, c in parsed[f]:
                if kind == "def" and norm(c) not in bodies:
                    bodies.add(norm(c))
                    body.append(c.strip("\n"))
                elif kind == "tail":
                    body.append(c.strip("\n"))
            continue
        name = (led or {}).get("name") or "(unledgered)"
        why = (f"matched in {f} (not merged yet)" if led and led["status"] == "matched"
               else "unmatched, no code, never credited")
        body.append(f"{MARK} {t['rva']} {t['size']}B {name} -- {why}")
    for f in files:   # a donor none of whose rows is approved here (cannot happen today)
        if f not in done:
            body.extend(c.strip("\n") for kind, c in parsed[f] if kind == "def")
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
    is in flag_overrides.csv, and compiles with region defaults off."""

    def __init__(self, tu):
        import build as B
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
        if self.tu_rel in fd.overrides():
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
        lines = text.split("\n")
        at = next((i for i, l in enumerate(lines) if l.startswith("// cl:")), None)
        own = lines[at][len("// cl:"):].split() if at is not None else []
        keep = [t for t in own if not fd.MANAGED.match(t.replace("/", "-", 1) if t.startswith("/") else t)]
        line = "// cl: " + " ".join(["/" + t[1:] for t in fd.region_tokens(region)] + keep)
        if at is None:
            lines.insert(0, line)
        else:
            lines[at] = line
        return "\n".join(lines)

    def matched(self, text, rows):
        text = self.effective(text, rows)
        key = hashlib.sha1(text.encode()).hexdigest()[:16]
        if key not in self.cache:
            src = self.tu.parent / f".{self.tu.stem}.{key}.tu_skeleton.cpp"
            obj = self.tmp / f"{key}.obj"
            src.write_text(text, encoding="utf-8", newline="")
            try:
                with contextlib.redirect_stdout(io.StringIO()), self.fd.forced_mode("current"):
                    ok, msg, _ = self.B.try_compile_source(src, obj)
            finally:
                src.unlink()
            self.cache[key] = obj if ok else None
            if not ok:
                self.all_errors = [l.strip() for l in (msg or "").splitlines() if " error " in l]
                self.errors = self.all_errors[:3]
        obj, out = self.cache[key], set()
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


def merge(tu, dry_run=False, log=print, claim=True):
    sk = skeleton(tu)
    don, mixed, refused = donors(tu, sk)
    report = {"tu": tu, "approved": len(sk), "mixed": mixed, "refused": refused, "accepted": [], "rejected": {}}
    if tu in mixed or ((ROOT / tu).exists() and tu not in don):
        report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
        return report
    if len(don) < 2 and not (len(don) == 1 and tu not in don):
        report["blocked"] = "fewer than two donors"
        return report
    if claim and not dry_run:
        held = claim_scope(tu, don)
        if held:
            report["blocked"] = "held by another worker: " + ", ".join(held[:5])
            return report
        report = _merge(tu, sk, don, report, dry_run)
        if "blocked" in report:   # nothing was written: give the scope back
            claims.release(claim_keys(tu, don))
        return report
    return _merge(tu, sk, don, report, dry_run)


def _merge(tu, sk, don, report, dry_run, texts=None, applier=None):
    v = Verifier(tu)
    texts = dict(texts or {})
    for f in don:
        if f not in texts:
            texts[f] = (ROOT / f).read_text(encoding="utf-8-sig", errors="replace")
    base = {}
    for f in don:
        got = v.matched(texts[f], don[f])
        base[f] = got or set()
    good = [f for f in don if base[f]]
    if tu in don and tu not in good:
        report["rejected"] = {f: "no baseline match" for f in don if f not in good}
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
    incs = []
    for f in good:
        for x in flags_of(texts[f]):
            if x.lower().startswith(("/i", "-i")) and x not in incs:
                incs.append(x)
    flag_sets = [list(k) + incs for k, _ in weight.most_common()]

    def attempt(files, flags):
        best = None
        need = set().union(*(base[f] for f in files))
        rows = [r for f in files for r in don[f]]
        for st in ("union-first", "union-longest", "first", "longest"):
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
                return text
            best = best or ("compile" if got is None else "bytes")
        return best

    def greedy(order, flags):
        acc, rej = [], {}
        for f in order:
            res = attempt(acc + [f], flags)
            if res in ("compile", "bytes"):
                rej[f] = res + ("" if res == "bytes" else ": " + " | ".join(v.errors)[:300])
            else:
                acc.append(f)
        return acc, rej

    first = {f: min(int(r["target_rva"], 16) for r in don[f]) for f in good}
    orders = [sorted(good, key=first.get), sorted(good, key=lambda f: (-len(base[f]), first[f])),
              sorted(good, key=lambda f: (-len(texts[f]), first[f]))]
    if tu in good:   # an existing file at the TU path is always the seed
        orders = [[tu] + [f for f in o if f != tu] for o in orders]
    best = None
    for flags in flag_sets[:3]:
        for o in orders:
            acc, rej = greedy(o, flags)
            score = sum(len(base[f]) for f in acc)
            if (tu in good and tu not in acc):
                continue
            if best is None or score > best[0]:
                best = (score, acc, rej, flags)
    report["rejected"].update({f: "no baseline match" for f in don if f not in good})
    if not best or len(best[1]) < 2 and not (len(best[1]) == 1 and best[1][0] != tu):
        report["rejected"].update(best[2] if best else {})
        report["blocked"] = "no verified merge of two or more donors"
        return report
    score, acc, rej, flags = best
    text = attempt(acc, flags)
    report.update(accepted=acc, flags=flags, rows=score)
    report["rejected"].update(rej)
    if dry_run:
        report["text"] = text
        return report
    moved = (applier or apply)(tu, acc, text)
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
    args = [set(re.findall(r"[A-Za-z_]\w*", MACRO_LINE.match(c).group(2))) if k == "macro" else None
            for _, _, c, k in spans]
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
    h = re.sub(r"__declspec\s*\([^)]*\)", " ", norm(head))
    return "=" in h and not re.search(r"\)\s*(?:const\s*)?$", h.split("=")[0].strip()) \
        and not re.match(r"^(?:template\s*<[^>]*>\s*)?(?:typedef\s+)?(?:class|struct|enum|union)\b", h)


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
            if not rest or (re.match(r"^(template\s*<[^>]*>\s*)?(typedef\s+)?(class|struct|enum|union)\b", rest)
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
DATA_PREFIX = re.compile(r"^(?:extern|typedef|using|template|friend|class|struct|enum|union|static_assert|namespace)\b")


def data_decls(text):
    """[(start, end, text, ident, internal)] of file-scope object definitions
    among the `;`-terminated chunks (`int g = 0;`, `static int s;`, `Foo *p;`):
    a definition, so it may live in one file only. Prototypes, externs,
    typedefs and type declarations are declarations and may be repeated."""
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
        if paren and not re.search(r"\(\s*\*\s*[A-Za-z_]\w*\s*\)", s[:eq if eq >= 0 else len(s)]):
            continue            # a prototype (or a function-pointer declarator, which is data)
        declarator = s[:eq] if eq >= 0 else s[:-1]
        m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", declarator.strip()) \
            or re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", declarator)
        if not m or m.group(1) in ("return", "goto", "break", "continue"):
            continue
        tokens = declarator.split()
        internal = tokens[0] == "static" or ("const" in tokens[:-1] and "*" not in declarator and "&" not in declarator)
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
            extern_lines.append((b, f"extern {decl};"))
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


PARENT_NOTE = re.compile(r"parent=([^;\s]+)")
DELETING = re.compile(r"^\?\?_[GE]((?:\?\$)?[A-Za-z_]\w*@)")


def companions(rows, parents):
    """Rows that are emitted with a parent in `parents` and live where it lives:
    EH funclets by name (`__ehhandler$X`), generated funclets (`gen-funclet;
    parent=X` in notes) and the deleting destructors of a carved destructor."""
    dtors = {m.group(1) for p in parents if (m := re.match(r"^\?\?1((?:\?\$)?[A-Za-z_]\w*@)", p))}
    out = []
    for r in rows:
        if r["name"] in parents:
            continue
        m = FUNCLET.match(r["name"])
        if m and m.group(1) in parents:
            out.append(r)
            continue
        m = PARENT_NOTE.search(r["notes"] or "")
        if m and m.group(1) in parents:
            out.append(r)
            continue
        m = DELETING.match(r["name"])
        if m and m.group(1) in dtors:
            out.append(r)
    return out


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
    out = collections.defaultdict(list)
    for r in rows:
        m = FUNCLET.match(r["name"])
        tu = home[m.group(1)] if m and m.group(1) in home else home[r["name"]]
        out[tu].append(r)
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
    text0 = (ROOT / path).read_text(encoding="utf-8-sig", errors="replace")
    if "__FILE__" in strip(text0):          # rename_files reports only its first reason
        report["blocked"] = "file cannot be carved: expands __FILE__ (the path reaches its bytes)"
        return report
    inc = included_by(path)
    if inc:
        report["blocked"] = "file cannot be carved: #included by " + ", ".join(inc[:3])
        return report
    groups = breakdown(path)
    tu = next((k for k in groups if k.lower() == tu.lower()), tu)
    tu_rows = [r for r in groups.get(tu, []) if not FUNCLET.match(r["name"])]
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
        got = Verifier(path).matched(residual, keep) if keep else set()
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
        elsewhere = collections.Counter((assigned.get(int(r["target_rva"], 16)) or "(unplaced)").split("/")[-1]
                                        for r in own if assigned.get(int(r["target_rva"], 16)) != tu.lower())
        if elsewhere:
            report["blocked"] = ("TU path exists and holds rows the map does not place there (split it first): "
                                 + ", ".join(f"{k} {n}" for k, n in elsewhere.most_common()))
            return report
        don[tu] = own
    report.update(approved=len(sk), accepted=[], rejected={})
    texts = {path: donor_text}

    def applier(tu_, acc, text_):
        return apply_split(tu_, text_, path, residual, [r["target_rva"] for r in carved], report["hatches_move"],
                           data_moved=cv.data_moved)

    if claim and not dry_run:
        held = claim_scope(tu, {path: carved})
        if held:
            report["blocked"] = "held by another worker: " + ", ".join(held[:5])
            return report
        report = _merge(tu, sk, don, report, dry_run, texts=texts, applier=applier)
        if "blocked" in report:
            claims.release(claim_keys(tu, {path: carved}))
    else:
        report = _merge(tu, sk, don, report, dry_run, texts=texts, applier=applier)
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


# ---------------------------------------------------------------- apply
def claim_keys(tu, don):
    keys = [f"file:{tu}"] + [f"file:{f}" for f in sorted(don) if f != tu]
    return keys + sorted({r["target_rva"] for rows in don.values() for r in rows})


def claim_scope(tu, don, root=ROOT):
    """Claim the TU, its donors and their rows; [] or the keys another worker holds."""
    keys = claim_keys(tu, don)
    try:
        res = claims.claim(keys, note=f"tu_skeleton {tu}", root=root)
    except claims.ClaimsUnavailable as e:
        return [f"(claims unavailable: {e})"]
    if res.refused:
        names = {claims.key_of(k): k for k in keys}
        return [str(names.get(k, k)) for k in res.refused]
    return []


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


def repoint_all(root, gone, tu):
    """Point every path-keyed column (rename.PATH_COLUMNS) and the doxygen
    INPUT list from the absorbed donors at the TU. Returns {file: records}."""
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
    cfg = Path(root) / rename.SOURCES_CFG
    if cfg.exists():
        raw, n = repoint_sources_cfg(cfg.read_bytes(), set(gone), tu)
        if n:
            cfg.write_bytes(raw)
            moved[rename.SOURCES_CFG] = n
    return moved


def apply(tu, accepted, text, root=ROOT):
    gone = [f for f in accepted if f != tu]
    moved = repoint_all(root, gone, tu)
    (Path(root) / tu).write_text(text, encoding="utf-8", newline="\n")
    if gone:
        subprocess.run(["git", "rm", "-q", "--", *gone], cwd=root, check=True)
    subprocess.run(["git", "add", "--", tu, *moved], cwd=root, check=True)
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


def queue(under="", limit=None, root=ROOT):
    """Approved TUs a merge can shrink, most files removed first.

    `removes` is an upper bound: the merge verifies every donor and keeps only
    those that compile together without losing a matched row."""
    by_tu = collections.defaultdict(list)
    for r in map_rows():
        if r["confidence"] == "approved" and r["kind"].startswith("code") and r["tu"]:
            by_tu[r["tu"]].append(r)
    try:
        held = set().union(*(set(rec) for rec in claims._blocking_records(root)))
    except Exception:   # no origin: nothing is known to be held
        held = set()
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
                    "mixed": len(mixed), "refused": len(refused), "held": bool(keys & held)})
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
    ap.add_argument("--for", dest="for_tu", metavar="TU", help="with --split: the destination TU (omit to list)")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--no-claim", action="store_true", help="merge without claiming (fixtures, private trees)")
    ap.add_argument("--under", default="")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--json")
    a = ap.parse_args(argv)
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
            print(f"{k}: {val}")
        if text and a.dry_run:
            print(text)
        return 0 if rep.get("accepted") else 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
