#!/usr/bin/env python3
"""Which ledger-backed sources can a header change reach?

Both hooks ran the 40-60 minute full gate for ANY header or shim change, even a
header nothing includes, which made the shared-header work that a linked build
needs (one real header per class instead of private copies) the most expensive
edit in the repository. This bounds the change instead: it walks the #include
graph upward from each changed header and prints the sources that can reach it,
so the hook byte-verifies those and nothing else.

The graph is read from the snapshot being verified -- the index for --staged,
the NEW commit for --range -- never from the working tree, so an unstaged or
uncommitted edit cannot change what is selected.

Under-counting would let a broken TU through, so every doubt widens the set:
  - includes match on file NAME (case-insensitive), never on resolved path, so
    same-named variants in other folders all count;
  - any file a scanned file #includes by name is scanned too, whatever its
    suffix (a .def or .tbl that includes a header carries that edge);
  - a file with a macro include (`#include MACRO`) is treated as including
    every file, changed non-headers included; a `// cl: /FI<name>` forced
    include counts as an include;
  - a directive the line scan cannot read with certainty (a line splice, a
    comment around it, a trigraph, a BOM, a binary-looking file) is re-read
    whole with splices joined and comments blanked; one that still cannot be
    parsed (a malformed operand, UTF-16 text, #pragma include_alias) exits 2;
  - the graph is read from #include text, so a deleted or renamed header's
    includers are still found;
  - a changed .cpp, .c or table that a scanned file #includes by name compiles
    inside that file, so it reaches its includers like a header does;
  - a vendored tree (vendor/) is not scanned, so its change is bounded by
    evidence instead (vendored_dependents): the units whose compile receipt
    (build/match/*.deps.json, written from /showIncludes) lists a changed file;
    every unit without a receipt current at the snapshot; and, for an added,
    deleted or tool-read file (which can change what resolves without changing
    a recorded byte), every unit that records any file of that package or
    whose text opts into it (a build.py marker, the package's name, a macro
    include). A brand-new package nothing opts into reaches no unit;
  - an STLport directory under Code/ is ordinary game source: the graph bounds it;
  - toolchain, BFME 1 pointer, STLport overlay code, vendored binary and
    compiler-profile changes, or a set larger than --limit sources, exit 2: the
    caller runs the full gate.

  python3 tools/header_dependents.py --staged           # pre-commit
  python3 tools/header_dependents.py --range OLD NEW    # pre-push
exit 0 = the sources to verify, one per line (possibly none); exit 2 = run the
full gate (reason on stderr).
"""
import argparse
import csv
import hashlib
import io
import json
import os
import re
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
HEADER_SUFFIXES = (".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c", ".cc", ".cxx", ".cp", ".c++")
SCANNED_ROOTS = ("Code/", "reference/")
FULL_GATE_ROOTS = ("build/toolchains/", "reference/open-bfme-1")
# Code that decides, for every unit, whether it compiles against a generated
# include tree (stlport_overlay.selected runs in build.compiler_environment).
FULL_GATE_TOOLS = ("tools/stlport_overlay.py",)
VENDOR = "vendor/"
# Vendored files a tool other than the preprocessor consumes: archives the
# ledger and the link read, and compilers (tools/compiler_profiles.py runs
# vendor/<profile>/bin/ or compiler.zip). No include receipt bounds them.
BINARY_SUFFIXES = (".lib", ".obj", ".a", ".exe", ".dll", ".zip", ".pdb")
# The text a unit carries to put a vendored package on its include path
# (tools/build.py compiler_environment/compiler_command, tools/stlport_overlay.py),
# matched case-insensitively as a substring, so `// stlport` also finds
# `// stlport46`. Every package also counts any mention of its own name (a
# `// cl: /Ivendor/<name>` line, a relative #include path). Keep in step with
# build.py: tools/tests/test_header_dependents.py checks every package it names.
OPT_IN = {
    "stlport": ("// stlport",),
    "stlport-4.6": ("// stlport46",),
    "stlport-4.6-bfme": ("// stlport46",),
    "dxsdk-aug2005": ("// dxsdk",),
}
# build.py compiles every vendored Zero Hour/Generals unit (reference/open-bfme-1)
# against vendor/stlport by path, with no marker.
PATH_OPT_IN = {"stlport": ("reference/open-bfme-1/",)}
# Packages a tool checks file by file against a manifest or patches into a
# generated tree (build.py verify_dxsdk, stlport_overlay.py verify_tree and
# materialize): every file of them is a tool input, recorded or not.
MANIFEST_PACKAGES = ("stlport-4.6", "stlport-4.6-bfme", "dxsdk-aug2005")
IGNORED_ROOTS = ("mods/",)
LEDGER = "reverse/functions.csv"
DATA_ROWS = "reverse/data_rows.csv"
DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*(?:include|import)\b[ \t]*(.*)$", re.M)
MACRO = re.compile(r"[A-Za-z_]\w*")
FORCED = re.compile(r"[-/]FI[ \t]*\"?([^\s\"]+)")
CL_LINE = re.compile(r"//[ \t]*cl:(.*)$", re.M)
# A line the per-line scan cannot trust: a spliced directive head or include, a
# comment before or inside a directive, a trigraph, an include alias.
DOUBT = re.compile(r"^[ \t]*#[ \t]*\w*[ \t]*\\\s*$|^[ \t]*#[ \t]*(?:include|import)\b.*\\\s*$"
                   r"|\*/[ \t]*#|#[ \t]*/\*|\?\?[=/]|include_alias")
# Lines git grep hands to DIRECTIVE, CL_LINE and DOUBT: one PCRE alternation (0.3 s over
# the tree); git without PCRE takes the ERE pair, whose spliced-head pattern is slow
# alongside the others and so runs apart as a file listing.
GREP_PCRE = r"#\s*(?:include|import)|//\s*cl:|\?\?[=/]|\*/\s*#|#\s*/\*|include_alias|^\s*#\s*\w*\s*\\\s*$"
GREP_ERE = ("#[[:space:]]*(include|import)", "//[[:space:]]*cl:", "\\?\\?[=/]",
            "\\*/[[:space:]]*#", "#[[:space:]]*/\\*", "include_alias")
GREP_ERE_SPLICED_HEAD = "^[[:space:]]*#[[:space:]]*[A-Za-z0-9_]*[[:space:]]*\\\\[[:space:]]*$"
TRIGRAPHS = {"=": "#", "/": "\\", "'": "^", "(": "[", ")": "]", "!": "|", "<": "{", ">": "}", "-": "~"}
# Literals end at a newline, as the compiler's do, so a stray quote cannot hide a comment.
COMMENT_OR_LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?|/\*[\s\S]*?(?:\*/|\Z)|//[^\n]*')
PRAGMA_ALIAS = re.compile(r"^[ \t]*#[ \t]*pragma\b.*\binclude_alias\b", re.M)


class Widen(Exception):
    """The include graph cannot be bounded with certainty: run the full gate."""


def git(*args):
    result = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                            encoding="utf-8", errors="replace")
    if result.returncode:
        raise SystemExit(f"header_dependents: git {' '.join(args[:2])} failed: {result.stderr.strip()}")
    return result.stdout


def changed(args):
    return [path for _, path in changed_status(args)]


def changed_status(args):
    """[(status letter, path)] of the change, renames split into delete + add."""
    if args.staged:
        out = git("diff", "--cached", "--name-status", "-z", "--no-renames", "--diff-filter=ACMRTD")
    else:
        out = git("diff", "--name-status", "-z", "--no-renames", args.range[0], args.range[1])
    fields = [f for f in out.split("\0") if f]
    return [(status[:1], path) for status, path in zip(fields[::2], fields[1::2])]


def snapshot(args):
    """None for the index, else the NEW commit's full SHA."""
    if args.staged:
        return None
    return git("rev-parse", "--verify", "--quiet", f"{args.range[1]}^{{commit}}").strip()


def is_wide(path):
    return path.lower().endswith(HEADER_SUFFIXES) or path.startswith(("reference/shims/", "build/toolchains/"))


def name(path):
    return path.replace("\\", "/").rsplit("/", 1)[-1].lower()


def grep(snap, *args, check=True):
    """git grep over the snapshot's scanned roots: [(path, text after the NUL)], or None
    when it fails and `check` is off."""
    cmd = ["git", "-c", "grep.lineNumber=false", "-c", "grep.column=false", "-c", "color.grep=never",
           "-c", "submodule.recurse=false", "grep", "-z", *args,
           *(["--cached"] if snap is None else [snap]), "--", *SCANNED_ROOTS]
    result = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, encoding="utf-8", errors="replace",
                            env={**os.environ, "LC_ALL": "C"})
    if result.returncode not in (0, 1):
        if not check:
            return None
        raise SystemExit(f"header_dependents: git grep failed: {result.stderr.strip()}")
    prefix = "" if snap is None else f"{snap}:"
    records = []
    for record in result.stdout.split("\n") if "-l" not in args else result.stdout.split("\0"):
        if not record:
            continue
        path, _, text = record.partition("\0")
        records.append((path[len(prefix):] if path.startswith(prefix) else path, text))
    return records


def blobs(snap, paths):
    """{path: bytes} for the snapshot's copy of each path."""
    spec = ":" if snap is None else f"{snap}:"
    result = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                            input="".join(f"{spec}{p}\n" for p in paths).encode("utf-8"))
    if result.returncode:
        raise SystemExit(f"header_dependents: git cat-file failed: {result.stderr.decode(errors='replace').strip()}")
    out, pos, found = result.stdout, 0, {}
    for path in paths:
        end = out.index(b"\n", pos)
        header = out[pos:end].split()
        pos = end + 1
        if len(header) != 3:
            raise Widen(f"{path} is unreadable in the snapshot")
        size = int(header[2])
        found[path] = out[pos:pos + size]
        pos += size + 1
    return found


# STLport's native-header macros (stl/_config.h): _STLP_NATIVE_HEADER(vector) is
# _STLP_MAKE_HEADER(_STLP_NATIVE_INCLUDE_PATH, vector), i.e. <../include/vector>:
# it names exactly the file its argument names. Read as a macro include, every
# unit using it (thread.cpp, EvaVectorABI.h) reached every changed source, so it
# joined every push's scope. A scanned file that defines one of these macros
# itself turns this reading off (scan sets STLP_NATIVE_FIXED).
STLP_NATIVE = re.compile(r"_STLP_NATIVE_(?:C_HEADER|CPP_C_HEADER|CPP_RUNTIME_HEADER|HEADER|OLD_STREAMS_HEADER)"
                         r"[ \t]*\([ \t]*([^()\s]+)[ \t]*\)[ \t]*$")
STLP_NATIVE_FIXED = True


def operand_target(operand, path):
    """('name', literal) or ('macro', None) for one #include operand, else Widen."""
    operand = operand.strip()
    native = STLP_NATIVE.match(operand) if STLP_NATIVE_FIXED else None
    if native:
        return "name", native.group(1)
    for open_, close in (('"', '"'), ("<", ">")):
        if operand.startswith(open_):
            end = operand.find(close, 1)
            if end > 1:
                return "name", operand[1:end]
            raise Widen(f"{path}: unparseable #include {operand!r}")
    if MACRO.match(operand):
        return "macro", None
    raise Widen(f"{path}: unparseable #include {operand!r}")


def forced_names(text):
    return {name(forced) for line in CL_LINE.findall(text) for forced in FORCED.findall(line)}


def read_whole(path, data):
    """(included names, has a macro include) from a whole file, splices joined and comments blanked."""
    if data[:2] in (b"\xff\xfe", b"\xfe\xff") or data.count(b"\0") * 4 > len(data):
        raise Widen(f"{path} looks like UTF-16/32 text")
    text = data.decode("latin-1")
    text = text[3:] if text.startswith("\xef\xbb\xbf") else text
    names, macro = forced_names(text), False
    text = re.sub(r"\?\?([=/'()!<>-])", lambda m: TRIGRAPHS[m.group(1)], text)
    # MSVC splices only backslash-newline; also read backslash-blanks-newline as a
    # splice, and keep the union: a spurious edge only widens the set.
    for spliced in {re.sub(r"\\\r?\n", "", text), re.sub(r"\\[ \t\f\v]*\r?\n", "", text)}:
        body = COMMENT_OR_LITERAL.sub(
            lambda m: re.sub(r"[^\n]", " ", m.group()) if m.group().startswith("/") else m.group(), spliced)
        if PRAGMA_ALIAS.search(body):
            raise Widen(f"{path} has #pragma include_alias")
        for operand in DIRECTIVE.findall(body):
            kind, literal = operand_target(operand, path)
            if kind == "macro":
                macro = True
            else:
                names.add(name(literal))
    return names, macro


def scan(snap):
    """({scanned path: {included name}}, {scanned paths with a macro include}) at the snapshot.

    One git grep reads every include-like line; only the few files it cannot
    read with certainty are fetched whole."""
    global STLP_NATIVE_FIXED
    edges, macro, doubt = defaultdict(set), set(), set()
    STLP_NATIVE_FIXED = not grep(snap, "-l", "-I", "-E", "-e", "define[[:space:]]+_STLP_NATIVE_[A-Z_]*HEADER")
    lines = grep(snap, "-I", "-P", "-e", GREP_PCRE, check=False)
    if lines is None:
        lines = grep(snap, "-I", "-E", *(arg for p in GREP_ERE for arg in ("-e", p)))
        doubt |= {p for p, _ in grep(snap, "-l", "-I", "-E", "-e", GREP_ERE_SPLICED_HEAD)}
    for path, line in lines:
        if DOUBT.search(line):
            doubt.add(path)
        directive = DIRECTIVE.match(line.lstrip("\ufeff"))
        if directive:
            try:
                kind, literal = operand_target(directive.group(1), path)
            except Widen:
                doubt.add(path)
            else:
                if kind == "macro":
                    macro.add(path)
                else:
                    edges[path].add(name(literal))
        edges[path] |= forced_names(line)
    # git grep -I skips files it takes for binary: read those whole as well
    everything = {p for p, _ in grep(snap, "-l", "-e", "")}
    doubt |= everything - {p for p, _ in grep(snap, "-l", "-I", "-e", "")}
    names = set().union(*edges.values())

    def scanned(path):
        return path.lower().endswith(HEADER_SUFFIXES + SOURCE_SUFFIXES) or name(path) in names

    pending = sorted(p for p in doubt if scanned(p))
    while pending:
        for path, data in blobs(snap, pending).items():
            found, has_macro = read_whole(path, data)
            edges[path] |= found
            names |= found
            if has_macro:
                macro.add(path)
        doubt -= set(pending)
        pending = sorted(p for p in doubt if scanned(p))
    edges = {p: e for p, e in edges.items() if scanned(p)}
    return edges, {p for p in macro if scanned(p)}


def ledger_sources(snap):
    """Sources the byte gate verifies, from the snapshot: those of function rows and
    of data rows (reverse/data_rows.csv) -- a data-only unit owns no function row,
    yet its initializers are byte-verified like any claimed source, and a header it
    includes reaches them."""
    spec = ":" if snap is None else f"{snap}:"
    out = {row[4] for row in csv.reader(io.StringIO(git("show", f"{spec}{LEDGER}"), newline=""))
           if len(row) > 4}
    if listed(snap, DATA_ROWS):       # present: a failed read raises, and the hooks widen
        out |= {row["source"] for row in csv.DictReader(io.StringIO(git("show", f"{spec}{DATA_ROWS}"), newline=""))
                if row.get("source")}
    return out


def listed(snap, path):
    """Whether the snapshot (the index, or commit `snap`) holds `path`, from the
    listing of its directory rather than its blob: only a clean listing without
    it proves absence, so an unreadable ledger is never mistaken for a missing
    one (git() raises). The same name in another case is refused: Windows builds
    read it as `path` while git's exact lookup would miss it."""
    # the whole snapshot, not one directory: a variant parent (Reverse/) hides from
    # a listing of reverse/ exactly as a variant name hides from an exact lookup
    entries = git("ls-files", "--stage", "-z") if snap is None else git("ls-tree", "-r", "-z", snap)
    names = {entry.split("\t", 1)[1] for entry in entries.split("\0") if "\t" in entry}
    if path in names:
        return True
    if any(name.lower() == path.lower() for name in names):
        raise SystemExit(f"header_dependents: {path} is tracked under another case; rename it to {path}")
    return False


def graph(edges):
    """{included name: {including path}}."""
    includers = defaultdict(set)
    for path, included in edges.items():
        for literal in included:
            includers[literal].add(path)
    return includers


def dependents(headers, includers, macro):
    """Every scanned file that can reach one of `headers` (names), transitively."""
    frontier = {name(h) for h in headers}
    seen_names, reached = set(), set()
    macro_spread = False
    while frontier:
        current = frontier.pop()
        if current in seen_names:
            continue
        seen_names.add(current)
        users = set(includers.get(current, ()))
        if not macro_spread:
            # a macro include could name any file, so it may reach this one
            users |= macro
            macro_spread = True
        for path in users:
            if path in reached:
                continue
            reached.add(path)
            frontier.add(name(path))  # a source can be #included as well
    return reached


def package(path):
    """The vendored package (vendor/<name>/) holding `path`."""
    return path[len(VENDOR):].split("/", 1)[0]


def compiler_package(snaps, name):
    """Whether vendor/<name>/ is a compiler profile at any of `snaps` (None: the index)."""
    for snap in snaps:
        for probe in (f"{VENDOR}{name}/bin", f"{VENDOR}{name}/compiler.zip"):
            listing = (git("ls-files", "--", probe) if snap is None
                       else git("ls-tree", "--name-only", snap, "--", probe))
            if listing.strip():
                return True
    return False


def norm(path):
    return path.replace("\\", "/").lower()


def receipt_path(source):
    """build.py's obj_path(source) with .deps.json: build/match/<parts joined by _,
    capitals as ^x>.deps.json. A receipt it does not find counts as missing."""
    stem = "_".join(Path(source).with_suffix("").parts)
    encoded = "".join(("^" + c.lower()) if c.isupper() else c for c in stem)
    return ROOT / "build" / "match" / (encoded + ".deps.json")


def dirty_paths(args):
    """Tracked paths whose working-tree bytes differ from the snapshot (lowercased):
    a receipt hashed from them says nothing about the snapshot."""
    if args.staged:
        out = git("diff", "--name-only", "-z", "--no-renames")
    else:
        out = git("diff", "--name-only", "-z", "--no-renames", args.range[1])
    return {norm(p) for p in out.split("\0") if p}


def receipts(sources, dirty):
    """{source: (current, [recorded include paths, lowercased])}: current is False
    when the unit has no compile receipt current at the snapshot (missing,
    unreadable, written for another source, or any recorded input now differs or
    is dirty); the paths of a receipt that is readable but stale still show which
    files some compile included."""
    memo = {}

    def digest(path):
        if path not in memo:
            try:
                memo[path] = hashlib.md5(Path(path).read_bytes()).hexdigest()
            except OSError:
                memo[path] = None
        return memo[path]

    def one(source):
        try:
            meta = json.loads(receipt_path(source).read_text(encoding="utf-8"))
        except (OSError, ValueError):
            return False, []
        deps = meta.get("deps") if isinstance(meta, dict) else None
        if not isinstance(deps, dict) or meta.get("path") != source:
            return False, []
        if not all(isinstance(dep, str) and dep and "\0" not in dep for dep in deps):
            return False, []
        listed = [norm(dep) for dep in deps]
        current = (norm(source) not in dirty and meta.get("source") is not None
                   and meta.get("source") == digest(str(ROOT / source)))
        for dep, recorded in deps.items() if current else ():
            absolute = os.path.isabs(dep)
            if ((not absolute and norm(dep) in dirty) or recorded is None
                    or digest(dep if absolute else str(ROOT / dep)) != recorded):
                current = False
                break
        return current, listed

    ordered = sorted(sources)
    with ThreadPoolExecutor(8) as pool:
        return dict(zip(ordered, pool.map(one, ordered)))


def mentions(snap, needles):
    """Scanned files whose text holds any of `needles` (case-insensitive)."""
    args = ["-l", "-i", "-F"]
    for needle in sorted(needles):
        args += ["-e", needle]
    return {p for p, _ in grep(snap, *args)}


def tool_named(snap, basenames):
    """The `basenames` (lowercased) some non-test tools/*.py at the snapshot spells."""
    if not basenames:
        return set()
    spec = [] if snap is None else [snap]
    args = ["git", "-c", "submodule.recurse=false", "grep", "-h", "-o", "-i", "-F"]
    for base_name in sorted(basenames):
        args += ["-e", base_name]
    result = subprocess.run([*args, *(["--cached"] if snap is None else spec), "--", "tools/*.py",
                             ":(exclude)tools/tests/*"], cwd=ROOT, capture_output=True, text=True,
                            encoding="utf-8", errors="replace")
    if result.returncode not in (0, 1):
        raise SystemExit(f"header_dependents: git grep failed: {result.stderr.strip()}")
    return {line.strip().lower() for line in result.stdout.splitlines() if line.strip()}


def vendored_dependents(args, snap, changes, rows, edges, macro):
    """Ledger sources a change to vendored files can reach, from evidence: every
    unit without a receipt current at the snapshot, every unit whose receipt
    lists a changed file, and, for a package with a change no receipt bounds (a
    file added or deleted, which can change what an include resolves to, or one
    no unit records, which a tool rather than the preprocessor reads), every unit
    recording any file of that package or opting into it. Binaries and compiler
    profiles widen."""
    for _, path in changes:
        if path.lower().endswith(BINARY_SUFFIXES):
            raise Widen(f"{path} is a vendored binary")
    snaps = [snap, "HEAD"] if args.staged else [snap, args.range[0]]
    for package_name in sorted({package(p) for _, p in changes}):
        if compiler_package(snaps, package_name):
            raise Widen(f"{VENDOR}{package_name}/ is a compiler profile")
    compiled = [s for s in rows if s.lower().endswith((".c", ".cpp", ".asm"))]
    recorded = receipts(compiled, dirty_paths(args))
    reached = {s for s, (current, _) in recorded.items() if not current}
    changed_paths = {norm(p) for _, p in changes}
    listed_anywhere = set().union(*(set(listed) for _, listed in recorded.values()))
    # A modified file no compile recorded is read by a tool if by anything: a
    # manifest package's, or one a tool names (vendor/stlport/list). Otherwise
    # (a README) it can change no unit: units without a receipt are reached above.
    unlisted = [p for status, p in changes if status == "M" and norm(p) not in listed_anywhere]
    named = tool_named(snap, {p.rsplit("/", 1)[-1] for p in unlisted})
    wide = {package(p) for status, p in changes if status != "M"}
    wide |= {package(p) for p in unlisted
             if package(p) in MANIFEST_PACKAGES or p.rsplit("/", 1)[-1].lower() in named}
    prefixes = tuple(norm(f"{VENDOR}{n}/") for n in wide)
    for source, (_, listed) in recorded.items():
        if any(key in changed_paths or (prefixes and key.startswith(prefixes)) for key in listed):
            reached.add(source)
    if wide:
        needles = {needle.lower() for n in wide for needle in (n,) + OPT_IN.get(n, ())}
        opted = mentions(snap, needles)
        # a macro include could spell any path, so it opts into every package
        opted |= dependents(opted, graph(edges), macro) if opted else set(macro)
        reached |= {p for p in opted if p in rows}
        by_path = tuple(prefix for n in wide for prefix in PATH_OPT_IN.get(n, ()))
        if by_path:
            reached |= {s for s in rows if s.startswith(by_path)}
    return reached


def select(args):
    statuses = [(st, p) for st, p in changed_status(args) if not p.startswith(IGNORED_ROOTS)]
    blocked = [p for _, p in statuses if p.startswith(FULL_GATE_ROOTS) or p in FULL_GATE_TOOLS]
    if blocked:
        raise Widen(f"{blocked[0]} is toolchain/BFME 1 pointer/STLport overlay")
    vendored = [(st, p) for st, p in statuses if p.startswith(VENDOR)]
    paths = [p for _, p in statuses if not p.startswith(VENDOR)]
    wide = [p for p in paths if is_wide(p)]
    others = [p for p in paths if not is_wide(p) and p.startswith(("Code/", "reference/"))]
    if not wide and not others and not vendored:
        return 0, [], 0, 0
    snap = snapshot(args)
    edges, macro = scan(snap)
    names = set().union(*edges.values())
    # a macro include may name any changed file, whatever its suffix
    included = [p for p in others if macro or name(p) in names]
    roots = wide + included
    if not roots and not vendored:
        return 0, [], 0, 0
    rows = ledger_sources(snap)
    reached = dependents(roots, graph(edges), macro) if roots else set()
    if vendored:
        reached |= vendored_dependents(args, snap, vendored, rows, edges, macro)
    # a changed file that is itself a ledger source (a shim .cpp) is verified too
    sources = sorted({p for p in reached if p in rows} | {p for p in wide if p in rows})
    return len(wide), sources, len(included), len(vendored)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    ap.add_argument("--limit", type=int, default=2000,
                    help="more dependent sources than this runs the full gate instead (default 2000)")
    args = ap.parse_args(argv)
    sys.stdout.reconfigure(newline="\n")  # the hooks read this with mapfile
    try:
        wide, sources, included, vendored = select(args)
    except Widen as why:
        print(f"header_dependents: {why}: full gate", file=sys.stderr)
        return 2
    if not wide and not included and not vendored:
        return 0
    if len(sources) > args.limit:
        print(f"header_dependents: {len(sources):,} dependent sources exceed --limit {args.limit:,}: full gate",
              file=sys.stderr)
        return 2
    print(f"header_dependents: {wide} changed header(s), {included} included file(s) and "
          f"{vendored} vendored file(s) reach {len(sources):,} ledger source(s)",
          file=sys.stderr)
    for path in sources:
        print(path)
    return 0


if __name__ == "__main__":
    sys.exit(main())
