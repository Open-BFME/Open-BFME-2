#!/usr/bin/env python3
"""Collapse the names the tree uses for one retail global onto the ledger's.

tools/data_ledger.py groups every data relocation of the matched code by the
retail address it reaches. Where one address carries several names, each name
links to its own copy and the link has two globals for retail's one: the
second copy's readers and writers never meet the first's (research 29: the
largest measured link lever). This codemod rewrites sources, one edit per
(file, name), and keeps an edit only when ./build's per-file gate still
matches every row of the file (tools/bulk_pass.py):

  rename    an extern global N bound only at address A, whose ledger name C at
            A has the identical decorated type: N -> C in each .c/.cpp that
            names it; N's `extern` lines become C's. A file that DEFINES N
            (or a TU-local static N) has the definition turned into C's
            `extern` declaration -- only after every other user of N was
            rewritten, and never when N's definition is the only initialized
            one (C's owner must define C, initialized if N was).
  string    an `extern const char N[]` bound at the address of a pooled string
            literal (??_C@) that the ledger binds to that one address only:
            N -> the literal's text, its extern line removed. A literal bound
            to several retail addresses is left alone: retail did not pool it,
            and the rewrite would only trade a duplicate for a split.
  cast      as rename, for a pointer global N whose pointee type differs
            from C's (a private class view: `Rva002A8F24 *g_00DFEEF8` at
            `TheGameLogic`): N -> `(*(T **)&C)` with N's own pointee type T,
            so every use keeps its type and only the symbol changes.
  float     the same for a `float`/`double` global standing at a __real@
            constant bound to one address only.
  dedupe    C itself defined by several TUs: each non-owner definition becomes
            C's `extern` declaration (C has no initializer there, or the owner
            initializes it too).

Skipped, and listed by `plan`: names declared in headers (a header edit
reaches TUs the per-file gate does not rebuild), names bound at several
addresses (one global for several retail ones), types the tool cannot
declare, unowned addresses.

  python3 tools/data_sweep.py plan [--kind K]
  python3 tools/data_sweep.py apply [--kind K] [--limit N] [--jobs J] [--commit-every 50]
"""
import argparse
import collections
import concurrent.futures
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import bulk_pass  # noqa: E402
import build  # noqa: E402
import data_ledger as dl  # noqa: E402
from name_globals import declare  # noqa: E402

NON_CODE = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|//[^\n]*|/\*.*?\*/', re.S)
SOURCES = (".c", ".cpp")


def mangled_type(symbol):
    found = re.match(r"^\?\w+@@3(.*)$", symbol)
    return found.group(1) if found else None


def code_spans(text):
    """[(start, end)] of the text outside comments and literals."""
    spans, at = [], 0
    for m in NON_CODE.finditer(text):
        spans.append((at, m.start()))
        at = m.end()
    spans.append((at, len(text)))
    return spans


def sub_code(text, pattern, repl):
    """pattern -> repl (taken literally) in code only."""
    if isinstance(repl, str):
        repl = (lambda value: lambda _m: value)(repl)
    out, at = [], 0
    for m in NON_CODE.finditer(text):
        out.append(pattern.sub(repl, text[at:m.start()]))
        out.append(m.group(0))
        at = m.end()
    out.append(pattern.sub(repl, text[at:]))
    return "".join(out)


def mentions(text, ident):
    pattern = re.compile(rf"(?<![\w$]){re.escape(ident)}(?![\w$])")
    return any(pattern.search(text, a, b) for a, b in code_spans(text))


def statements(text, ident):
    """File-scope statements (brace depth 0) naming `ident`: [(start, end, text)]."""
    masked = NON_CODE.sub(lambda m: " " * len(m.group(0)), text)
    pattern = re.compile(rf"(?<![\w$]){re.escape(ident)}(?![\w$])")
    out, depth, start = [], 0, 0
    for i, ch in enumerate(masked):
        if ch == "{":
            if depth == 0 and "=" not in masked[start:i]:   # a body, not an aggregate initializer
                start = i + 1
            depth += 1
        elif ch == "}":
            depth = max(0, depth - 1)
            if depth == 0:
                start = i + 1
        elif ch == ";" and depth == 0:
            if pattern.search(masked, start, i):
                out.append((start, i + 1, masked[start:i + 1]))
            start = i + 1
        elif ch == "\n" and depth == 0 and masked[start:i].lstrip().startswith("#"):
            start = i + 1
    return out


def is_extern(stmt):
    return re.match(r"\s*extern\b", stmt) is not None and '"C"' not in stmt[:20]


def is_function(stmt, ident):
    return re.search(rf"(?<![\w$]){re.escape(ident)}\s*\(", stmt) is not None


def comments(text):
    return sorted(m.group(0) for m in NON_CODE.finditer(text) if m.group(0)[:2] in ("//", "/*"))


def keep_comments(edit):
    """An edit that would drop or change a comment (a `// cl:` flag line among
    them) is refused: these rewrites touch code only."""
    def guarded(text):
        out = edit(text)
        return out if comments(out) == comments(text) else text
    return guarded


def rename_edit(old, new, decl_new, define_to_extern, expr=None):
    """text -> text: N -> C (or `expr`, a cast of C) in code; with
    define_to_extern, file-scope definitions of N (or the C they became) are
    replaced by C's extern declaration."""
    word = re.compile(rf"(?<![\w$]){re.escape(old)}(?![\w$])")

    def edit(text):
        nl = "\r\n" if "\r\n" in text else "\n"
        for start, end, stmt in reversed(statements(text, old)):
            if is_function(stmt, old):
                return text                               # a function of that name: not ours
            # the statement proper: `start` also covers the comments and blank
            # lines before it (blanked in `stmt`, same offsets); they stay
            core = start + len(stmt) - len(stmt.lstrip())
            if is_extern(stmt):
                if "," in stmt:
                    return text                           # a multi-declarator line: leave the file alone
                text = text[:core] + decl_new + text[end:]
            elif define_to_extern:
                if "," in stmt.split("=")[0] or "{" in stmt:
                    return text
                text = text[:core] + decl_new + text[end:]
            else:
                return text                               # a definition we were not cleared to drop
        text = sub_code(text, word, expr or new)
        if not re.search(rf"\bextern\b[^;]*(?<![\w$]){re.escape(new)}\s*;", NON_CODE.sub(" ", text)) \
                and not statements(text, new):
            at = dl_lead(text)
            text = text[:at] + decl_new + nl + text[at:]
        return dedupe_externs(text, decl_new)
    return keep_comments(edit)


def dl_lead(text):
    return re.match(r"(?:[ \t]*//[^\n]*\n|[ \t]*\r?\n|[ \t]*/\*.*?\*/[ \t]*\r?\n)*", text, re.S).end()


def dedupe_externs(text, decl):
    first = text.find(decl)
    if first < 0:
        return text
    head, tail = text[:first + len(decl)], text[first + len(decl):]
    return head + re.sub(rf"[ \t]*{re.escape(decl)}[ \t]*\r?\n", "", tail)


def literal_edit(old, literal):
    word = re.compile(rf"(?<![\w$]){re.escape(old)}(?![\w$])")

    def edit(text):
        for start, end, stmt in reversed(statements(text, old)):
            if not is_extern(stmt) or "," in stmt:
                return text                               # defined here, or shared declarator
            core = start + len(stmt) - len(stmt.lstrip())
            lo = text.rfind("\n", 0, core) + 1
            hi = text.find("\n", end)
            hi = len(text) if hi < 0 else hi + 1
            if text[lo:hi].strip() != text[core:end].strip():
                return text                               # shares its line with other code
            text = text[:lo] + text[hi:]
        return sub_code(text, word, literal)
    return keep_comments(edit)


def c_string(raw):
    out = []
    for b in raw:
        c = chr(b)
        if c in '"\\':
            out.append("\\" + c)
        elif 0x20 <= b < 0x7F:
            out.append(c)
        else:
            out.append("\\%03o" % b)
    return '"' + "".join(out) + '"'


def c_float(raw, double):
    value = struct.unpack("<d" if double else "<f", raw)[0]
    for digits in range(1, 18):
        text = f"{value:.{digits}g}"
        try:
            back = struct.pack("<d" if double else "<f", float(text))
        except OverflowError:
            continue
        if back == raw:
            break
    else:
        return None
    if not re.search(r"[.eEn]", text):
        text += ".0"
    if "n" in text:
        return None                                       # inf / nan
    text += "" if double else "f"
    return f"({text})" if text.startswith("-") else text


def retail_bytes(rva, size):
    try:
        return build.read_target_bytes(rva, size)
    except Exception:
        return None


def owner_initialized(defs, name, owner):
    return any(d[0] == owner and d[1] == dl.EXTERNAL and d[2] for d in defs.get(name, ()))


def plan(kinds=("rename", "cast", "string", "float", "dedupe")):
    """[(kind, label, files_using, files_defining, edit_users, edit_definers, new symbol)], skipped Counter."""
    bind, defs, _missing, refsrc = dl.collect()
    rows = {int(r["address"], 16): r for r in dl.ledger_rows(bind, defs)}
    where = collections.defaultdict(set)          # name -> bases
    for base, names in bind.items():
        for (name, local) in names:
            where[(name, local)].add(base)
    texts = {}
    tracked = subprocess.run(["git", "ls-files", "Code"], cwd=ROOT, capture_output=True, text=True).stdout.split("\n")

    def text_of(path):
        if path not in texts:
            with (ROOT / path).open(encoding="latin-1", newline="") as handle:
                texts[path] = handle.read()
        return texts[path]

    by_ident = collections.defaultdict(list)
    ident_re = re.compile(r"[A-Za-z_]\w{5,}")
    wanted = {dl.identifier(n) for base in bind for (n, _l) in bind[base]}
    for path in tracked:
        if not path.endswith((".c", ".cpp", ".h", ".hpp", ".inl", ".CPP")):
            continue
        try:
            found = set(ident_re.findall(text_of(path))) & wanted
        except OSError:
            continue
        for ident in found:
            by_ident[ident].append(path)

    out, skipped = [], collections.Counter()
    literal_bases = collections.defaultdict(set)
    for (name, local), bases in where.items():
        if dl.kind_of(name) in ("string", "float"):
            literal_bases[name] |= bases
    for base in sorted(bind):
        row = rows[base]
        names = bind[base]
        canon = row["name"]
        for (name, local) in sorted(names, key=lambda k: (k[0], k[1] or "")):
            if name == canon and local is None:
                continue
            if dl.kind_of(name) != "global":
                continue
            ident = dl.identifier(name)
            if where[(name, local)] != {base}:
                skipped["bound at several addresses"] += 1
                continue
            files = by_ident.get(ident, [])
            if any(not f.lower().endswith(SOURCES) for f in files):
                skipped["declared in a header"] += 1
                continue
            # only TUs whose matched code references N itself: one identifier
            # can name several symbols (TheGameLogic as GameLogic * and as a
            # private view), and a file using the canonical one needs no edit
            files = [f for f in files if f in refsrc.get(name, ()) and mentions(text_of(f), ident)]                 if local is None else [local]
            ndefs = [d for d in defs.get(name, ()) if (d[1] == dl.EXTERNAL) if local is None] if local is None \
                else [d for d in defs.get(name, ()) if d[0] == local and d[1] == dl.STATIC]
            definers = sorted({d[0] for d in ndefs})
            users = [f for f in files if f not in definers]
            mt = mangled_type(name)
            if row["kind"] == "global" and ("rename" in kinds or "cast" in kinds):
                if row["status"] == "unowned" or not row["source"]:
                    skipped["unowned address"] += 1
                    continue
                ct = mangled_type(canon)
                cast = None
                if ct is not None and mt is not None and mt != ct and "cast" in kinds and declare(canon)                         and declare(name) and ct[:2] in ("PA", "PB") and mt[:2] in ("PA", "PB"):
                    cast = f"(*({declare(name)[1].replace(' *', '')} **)&{dl.identifier(canon)})"
                    if mt[1] == "B":   # pointer to const
                        cast = f"(*(const {declare(name)[1].replace(' *', '')} **)&{dl.identifier(canon)})"
                elif ct is None or mt != ct or not declare(canon):
                    skipped["type differs / not declarable"] += 1
                    continue
                if any(d[2] for d in ndefs) and not owner_initialized(defs, canon, row["source"]):
                    skipped["would drop the only initializer"] += 1
                    continue
                decl = declare(canon)[4]
                cident = dl.identifier(canon)
                out.append(("cast" if cast else "rename", f"{ident}->{cident}@{base:#x}", users, definers,
                            rename_edit(ident, cident, decl, False, cast),
                            rename_edit(ident, cident, decl, True, cast), canon))
            elif row["kind"] == "string" and "string" in kinds and local is None:
                if literal_bases.get(canon) != {base} or mt not in ("QBDB", "PBDB"):
                    skipped["literal not pooled at one address / type"] += 1
                    continue
                raw = retail_bytes(base, 4096) or b""
                end = raw.find(b"\0")
                if end < 0:
                    skipped["unterminated literal"] += 1
                    continue
                out.append(("string", f"{ident}->{c_string(raw[:end])[:24]}@{base:#x}", files, [],
                            literal_edit(ident, c_string(raw[:end])), None, canon))
            elif row["kind"] == "float" and "float" in kinds and local is None:
                if literal_bases.get(canon) != {base} or mt not in ("MA", "MB", "NA", "NB"):
                    skipped["literal not pooled at one address / type"] += 1
                    continue
                double = mt.startswith("N")
                lit = c_float(retail_bytes(base, 8 if double else 4) or b"", double)
                if lit is None:
                    skipped["float not representable"] += 1
                    continue
                out.append(("float", f"{ident}->{lit}@{base:#x}", files, [], literal_edit(ident, lit), None, canon))
        # dedupe: the canonical name itself defined by several TUs
        if "dedupe" in kinds and row["kind"] == "global" and row["source"]:
            cdefs = sorted({d[0] for d in defs.get(canon, ()) if d[1] == dl.EXTERNAL} - {row["source"]})
            decl = declare(canon)
            if cdefs and decl and where[(canon, None)] == {base}:
                cident = dl.identifier(canon)
                if any(not f.lower().endswith(SOURCES) for f in by_ident.get(cident, ()) if f in cdefs):
                    continue
                safe = [f for f in cdefs if not any(d[0] == f and d[2] for d in defs[canon])
                        or owner_initialized(defs, canon, row["source"])]
                if safe:
                    out.append(("dedupe", f"{cident}@{base:#x}", [], safe, None,
                                rename_edit(cident, cident, decl[4], True), canon))
    return out, skipped


def object_names(source):
    obj = build.obj_path(ROOT / source)
    if not obj.exists():
        return None
    return {s["name"] for s in dl.layout(obj)[2]}


def gate_for(source, allowed):
    """The per-file gate, plus: the rebuilt object names no symbol beyond the
    original object's and the intended canonical names. Bytes alone cannot see
    a rename that landed inside an extern "C" block (`_TheAudio`) or a
    namespace: the code is identical and only the link would break."""
    before = object_names(source)

    def check(_source):
        done = subprocess.run([sys.executable, "tools/build.py", source], cwd=ROOT, capture_output=True, text=True)
        if done.returncode != 0 or "Functions: OK" not in done.stdout:
            return False
        after = object_names(source)
        return before is not None and after is not None and not (after - before - allowed)
    return check


def settle_all(edits_by_file, jobs, log, allowed):
    kept = {}
    with concurrent.futures.ThreadPoolExecutor(jobs) as pool:
        futures = {pool.submit(bulk_pass.settle, src, edits, gate_for(src, allowed)): src
                   for src, edits in edits_by_file.items()}
        for future in concurrent.futures.as_completed(futures):
            src = futures[future]
            labels = future.result()
            kept[src] = labels
            log(("OK " if labels else "REVERTED ") + src + " " + ",".join(sorted(labels or
                                                                               [l for l, _ in edits_by_file[src]])))
    return kept


def apply(items, jobs, log):
    """Two phases: users of each name, then (only for names whose every user
    holds) the files that define it. Returns {file: [labels]}."""
    users = collections.defaultdict(list)
    for kind, label, using, _defining, edit_u, _edit_d, _new in items:
        for f in using:
            if edit_u:
                users[f].append((label, edit_u))
    allowed = {it[6] for it in items if it[6]}
    done = settle_all(users, jobs, log, allowed)
    ok_labels = collections.Counter(l for labels in done.values() for l in labels)
    need = collections.Counter(l for f, edits in users.items() for l, _ in edits)
    definers = collections.defaultdict(list)
    for kind, label, using, defining, _edit_u, edit_d, _new in items:
        if edit_d and defining and ok_labels[label] == need[label]:
            for f in defining:
                definers[f].append((label, edit_d))
    done2 = settle_all(definers, jobs, log, allowed)
    merged = collections.defaultdict(list)
    for d in (done, done2):
        for f, labels in d.items():
            merged[f] += labels
    return {f: l for f, l in merged.items() if l}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("mode", choices=("plan", "apply"))
    parser.add_argument("--kind", action="append", choices=("rename", "cast", "string", "float", "dedupe"))
    parser.add_argument("--limit", type=int, default=0, help="at most N rewrites (in address order)")
    parser.add_argument("--skip", type=int, default=0, help="skip the first N rewrites")
    parser.add_argument("--jobs", type=int, default=6)
    args = parser.parse_args(argv)
    items, skipped = plan(tuple(args.kind or ("rename", "cast", "string", "float", "dedupe")))
    if args.kind and "rename" not in args.kind:
        items = [it for it in items if it[0] != "rename"]
    items = items[args.skip:]
    if args.limit:
        items = items[:args.limit]
    if args.mode == "plan":
        for kind, label, using, defining, _u, _d, _new in items:
            print(f"{kind}\t{label}\tusers={len(using)}\tdefiners={len(defining)}")
        print(f"data_sweep: {len(items)} rewrite(s); skipped {dict(skipped)}")
        print(f"files: {len({f for it in items for f in it[2] + it[3]})}")
        return 0
    changed = apply(items, args.jobs, lambda line: print(line, flush=True))
    print(f"data_sweep: {len(changed)} file(s) changed, {sum(map(len, changed.values()))} edit(s) kept")
    return 0


if __name__ == "__main__":
    sys.exit(main())
