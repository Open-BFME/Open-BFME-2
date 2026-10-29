#!/usr/bin/env python3
"""Which original source file (TU) each retail function and data range came from.

The ledger records where a body sits in THIS tree, which is mostly one file per
function. Retail was linked from real translation units, and a TU's functions
sit next to each other in .text in the order the linker took the objects. This
tool recovers that structure from evidence and writes it to `tu_map.csv` next to
the ledger, so the skeleton generator (tools/tu_skeleton.py) and the ownership
invariant (tools/tu_ownership.py) work from one table instead of a guess each.

Signals, strongest first (one letter each in the `by` and `evidence` columns):

  F  the function references a `__FILE__` string naming a .cpp (assert/debug
     paths survive in retail); the string IS the TU.
  Z  `Class::method(` is defined in that file of the Zero Hour reference (an
     out-of-line definition at file scope: balanced parameters, then a body
     `{`; a call such as `Base::f(x);` or a data initializer is not one). A
     copy constructor needs ZH's own `Class::Class(const Class &` definition:
     another constructor of the class does not place it, because one ZH never
     defines is MSVC's implicit COMDAT, emitted wherever a copy is made
     (`implicit_copy()`), and it carries no S or N either. A member written inside
     a class that a ZH .cpp itself defines (ObjectCreationList.cpp's nuggets,
     FXList.cpp's, hlod.cpp's ProxyRecordClass) is defined in that file too: no
     other unit can see the class, so the body is emitted only there. It counts
     when exactly one .cpp writes it and no out-of-line definition exists.
  S  every ZH definition of `Class::` sits in one .cpp: the class's site.
     A Z or S that names a file of ZH's Tools/ programs (WorldBuilder, the 3ds Max
     exporter's pluglib, Autorun, ...) anchors nothing: those files were never linked
     into the game, so their TU is neither anchored nor provisional. pluglib defines
     Matrix3/Matrix4, the names ZH's own WWMath gives Matrix3x3/Matrix4x4, and five
     Matrix4 rows were approved into Code/Tools/WW3D/pluglib/matrix4.cpp. The hint
     itself is kept, so the rows still group as before.
  N  naming convention `<dir>/<Class>.cpp` (ModuleData suffix stripped); used
     only inside the address cluster an F/Z/S anchor or a run of N rows forms.
  U  the row's own naming hint (N, never F/Z/S) names a small TU whose rows
     interleave with an anchored TU's, so the two are one file (several
     classes in one .cpp) and the row takes the anchored TU's name.
  W  a WorldBuilder lead (reverse/wb_name_leads.csv, tools/wb_match.py) pairs the
     function with a WorldBuilder function whose own strings name a .cpp of BFME 2's
     tree (`C:/Projects/bfme2/Code/...`). W never names a TU by itself: it anchors
     a TU (as F/Z/S do) only where it names the very path a row's own hint gives,
     and only once `--validate` shows it agreeing with F (the game's own strings)
     at >= 99%. Where W and Z/S differ it is BFME 2's reorganised tree against
     Zero Hour's (Pathfinder/pathfinder*.cpp vs AI/AIPathfind.cpp), so Z/S are not
     its test. A lead never anchors the row whose name it supplied (the row's notes
     cite WorldBuilder, or it took the lead's class after the lead was cut): that
     row's hint is the lead's path again, so the TU needs an independent anchor.
  L  a vendored library built from upstream's own files, one TU each (UPSTREAM_TU_LIBS:
     GameSpy, Lua, zlib, LZHL; a `vendored=<lib>-<ver>` ledger tag marks the file): a
     function that exactly one whole upstream file of its library defines is in that
     file. Header-inline "vendored" code (ATL, GDI+, strsafe, the CRT splits, STLport) is
     emitted as COMDATs wherever it was used and never names a TU; a file carved out of
     an upstream file (liolib_bfme1.c from liolib.c) is not one either. F/Z/S never reach
     library code, so L's gate is retail order instead: each L row held out, the nearest
     rows below and above that carry their own F, Z, S or L must name its file
     (`l_score`, GAP apart at most); L anchors only while that holds at >= 99% on >= 100
     rows, and `--validate` prints it. Owner decision 2026-10-28 (an alternative gate for
     byte-verified upstream files): at d71e8bb289, 892 L rows in 55 files, 785/785
     held-out rows agree, none carries F/Z/S of its own; +923 approved code rows (891 L,
     26 C, 6 U), 601 -> 656 TUs, no approved row lost or retargeted.
  C  address contiguity: the nearest assigned rows on both sides agree and are
     within 0x3000 bytes (retail object order keeps a TU contiguous).
  K  placeholder-class propagation (`??1Rva...` follows its `??_GRva...`).
  X  data: every function that references the item is assigned to one TU.
  E/V/I/R/P  retail-structural layouts (tools/tu_evidence.py): funclet order,
     vftable layout, initializer order, .rdata order and funclet parentage. Each
     reaches only a row nothing above reaches, and only once tu_evidence.PROMOTED
     lists it (a Verifier-Change commit recording `tu_evidence.py --validate` at
     >= 99% held-out precision); until then it only proposes, in that tool's own
     report and lane (`next_work.py --tier tu-evidence`), never in this map.

The `evidence` column keeps each row's own pre-clustering F/Z/S/N values, so a
row's TU can always be checked against what its own name and strings say.

Class name alone is not a TU key: repo-wide only 42% of rows agree between Z and
N, and header-inline bodies (??_G, friend_new*, *ModuleData ctors) are emitted as
COMDATs in whichever TU used them first. A naming hint outside its TU's main
address cluster is therefore `displaced`, never assigned.

Clusters are merged (U) only when at most one of them is anchored by F/Z/S/W. Two
TUs that F/Z/S name differently are two files; when their rows interleave, both
are noncontiguous and nothing in them is approved. A row's own F/Z/S anchor is
never renamed by a merge, and a row whose TU contradicts its own F (or, without
F, both its Z and S) is never approved: it is marked `contradicted`.

Unconverted functions are mapped too. Every function start in
ghidra_functions.csv without a ledger row is a `code-unledgered` row with an
empty `source`; generated placeholder rows (gen_small, gen_asm) keep their
ledger source but carry no usable name. Neither has a name to read, so only the
name-free signals reach them: F (the body pushes a `__FILE__` path) and C (it
sits in a run bracketed by one TU). That is the routing table for new work:
tools/tu_ownership.py (A2/A3) and `tools/repair_queue.py dest` read the TU of
an address through `tu_at()` before anything is converted there. The EH
funclets linked after all of .text (`.text$x`, about a third of Ghidra's
functions) have neither signal and stay unmapped.

Every known code body is written, with or without a TU (`confidence` empty for
a body no signal reaches), so the map carries the extents `tu_at()` needs:

  * an address with a row gets that row, whatever its confidence;
  * an address inside a known body inherits that body's TU and confidence (a
    displaced or unassigned body stays so: nothing approves its interior);
  * an address in no known body is padding or an undiscovered body. Padding
    (retail 0xCC) gets no answer. Otherwise C from its brackets applies, and is
    approved only on boundary evidence: the retail image shows the address is
    the first non-padding byte after the body below it, i.e. where an
    unsplit function would start. Without the image it is at most proposed.

Confidence:
  approved  the TU's main cluster holds at least one F/Z/S/L/W anchor, the row is
            assigned by F/Z/S/L/N/U or bracketed (C) by approved rows, its own
            F/Z/S do not contradict the TU, and no row that could be approved
            for a different TU sits inside the TU's address span (a TU that is
            not contiguous in retail is not trusted). A row "could be approved"
            when its TU is anchored and it is assigned by F/Z/S/L/N/U/C; a K row,
            or a row of a TU no F/Z/S anchors (a naming hint for a class this
            repo named, alone), never can, so it does not break its host's
            span. A TU's span is the extent of its own F/Z/S/L/N/U rows (every
            row that could be approved for it lies within): a K row emitted
            far from its class's TU does not stretch it, and neither does an
            island (`islands()`: at most ISLAND rows of one TU, none F, Z or L, between
            longer runs of one other TU; a header COMDAT emitted in the host's
            object or a row named for the wrong class): it breaks no span and
            is itself never approved. A run of C rows is
            approved exactly when the two rows that bracket the whole run are.
            Provisional names (PROVISIONAL, `provisional()`): a TU nothing
            anchors is approved as well when grouping alone holds it together:
            at least PROV_MIN N/U rows, no row that could be approved for another
            TU (an anchored one or another such candidate) inside its span, and
            no overlap with an anchored TU's span. Its rows, and the C/P/E/X rows
            that follow them, carry the evidence token `provisional`: a merge
            moves them, but the TU path is only the naming hint, so rename.py and
            rename_files.py never take it for a proven file name (`canonical_tu`).
            Owner decision 2026-10-28, conditional on >= 99%: a 5-fold hold-out
            of the 601 F/Z/S/W-anchored TUs (every F/Z/S/L/W naming a held-out
            TU stripped and the map rebuilt) put 13,655/13,655 provisionally
            approved rows in a group whose other rows share their TU (N 4,522,
            P 4,829, C 3,091, U 1,211, E 2), 0 of 484 groups mixing TUs; on the
            rows with their own F/Z/S, independent of the grouping, 4,627/4,627.
            25 of the 427 TUs recovered split into 2-19 groups (a recall cost:
            several provisional files for one TU, never one file for two). At
            1155a9f61c: +11,860 approved code rows in 517 provisional TUs.
  proposed  assigned, but by N/K only, by brackets that are not approved, in a
            non-contiguous span, or contradicted. The queue for investigation.
  displaced a naming hint sat outside its TU's cluster (COMDAT pile).
  (empty)   a known body no signal reaches; it has no TU.

The output is a pure function of the ledger, ghidra_functions.csv,
string_xrefs.tsv, data_xrefs.tsv, the vendored files L reads and the ZH tree:
rerunning on unchanged inputs writes the same bytes. Never edit tu_map.csv by
hand; regenerate it. Writing it also writes `tu_map.inputs.sha256`
(sha256sum-like, line endings normalised): the hashes of those inputs (the
vendored files as one `vendored-upstream:Code` hash), of this tool and of the
map, and the ZH tree's identity -- its git tree id (and commit) in a clean
default checkout, else a hash of its .cpp files -- which `--check-fresh`
compares in about a second.

Usage:
  python3 tools/tu_map.py                write tu_map.csv (+ fingerprint), print a summary
  python3 tools/tu_map.py --check        exit 1 when tu_map.csv differs from a rebuild
  python3 tools/tu_map.py --check-fresh  exit 1 when an input changed since tu_map.csv was written
  python3 tools/tu_map.py --holdout RULE   held-out purity of an approval rule (tools/tu_holdout.py)
  python3 tools/tu_map.py --validate REV score approved predictions against independent evidence:
                                         each approved row's own F/Z/S, and the F/Z/S of rows
                                         landed since REV at addresses a map built from REV's
                                         ledger routed
  python3 tools/tu_map.py --dir PREFIX   summary for one directory's rows
  --zh DIR                               the ZH GeneralsMD/Code tree (default: the Open-BFME-1
                                         submodule's); must hold GameEngine/
"""
import argparse
import bisect
import collections
import csv
import hashlib
import io
import itertools
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAP = 0x3000          # max distance between bracketing anchors (C)
UNION_SPAN = 0x2000   # clusters this small that interleave are one TU
PAD = 0xCC            # MSVC fills between functions with int3
COLUMNS = ["rva", "size", "kind", "tu", "confidence", "by", "evidence", "source"]
APPROVABLE = {"F", "Z", "S", "L", "N", "U"}
SPAN_BREAKERS = APPROVABLE | {"C"}
WB_LEADS = "wb_name_leads.csv"
W_GATE, W_MIN = 0.99, 20  # W anchors only while it agrees with F on >= W_MIN rows at >= W_GATE
L_GATE, L_MIN = 0.99, 100  # L anchors only while retail order agrees with it on >= L_MIN held-out rows
FINGERPRINTED = ("functions.csv", "ghidra_functions.csv", "string_xrefs.tsv", "data_xrefs.tsv", WB_LEADS)


class Layout:
    """Where this repo keeps its ledger, sources, reference tree and retail image."""

    def __init__(self, root, zh=None):
        self.root = Path(root)
        if (self.root / "targets/game/reverse/functions.csv").exists():
            self.reverse = "targets/game/reverse"   # Open-BFME-1
            self.src = "game/"
            self.zh = self.root / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
            self.image = self.root / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
        else:
            self.reverse = "reverse"                # Open-BFME-2
            self.src = "Code/"
            self.zh = self.root / ("reference/open-bfme-1/inputs/reference/"
                                   "CnC_Generals_Zero_Hour/GeneralsMD/Code")
            self.image = self.root / "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
        self.zh_custom = bool(zh)
        if zh:
            self.zh = Path(zh)

    def zh_problem(self):
        """Why self.zh is not a ZH GeneralsMD/Code tree, or None."""
        if not self.zh.is_dir():
            return f"no ZH tree at {self.zh} (initialise the submodule or pass --zh GeneralsMD/Code)"
        if not (self.zh / "GameEngine").is_dir():
            return f"{self.zh} is not a ZH GeneralsMD/Code tree (no GameEngine/ in it)"
        return None

    def path(self, name):
        return self.root / self.reverse / name

    @property
    def out(self):
        return self.path("tu_map.csv")

    @property
    def fingerprint(self):
        return self.path("tu_map.inputs.sha256")


def read_csv(path):
    if not path.exists():
        return []
    return list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8", errors="replace"), newline="")))


CTOR = re.compile(r"^\?\?(_G|_E|0|1)([A-Za-z_]\w*)@@")
METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
PLACEHOLDER = re.compile(r"^(Rva|rva|Gen|gen|Sub|sub|FUN_)[0-9A-Fa-f_]")
COMDAT = re.compile(r"^\?\?_[GE]|^\?friend_new|^\?\?[01]\w*ModuleData@@")
# A copy constructor, `X::X(const X &)` (private, protected or public).
COPY_CTOR = re.compile(r"^\?\?0([A-Za-z_]\w*)@@[AIQ]AE@ABV0@@Z$")
# Its out-of-line definition in a ZH .cpp (comments and literals blanked first).
COPY_DEF = re.compile(r"\b([A-Za-z_]\w*)\s*::\s*\1\s*\(\s*const\s+\1\s*&")
# Comments and literals, so a commented-out or quoted `X::y(` is never read as code.
CPP_NOISE = re.compile(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.S)
# An out-of-line definition opens at file scope: column 0, no statement keyword, no
# assignment or call before `Class::method`, then its `(` (on that line or a later one).
ZH_HEAD = re.compile(r"^(?!(?:return|else|if|while|for|do|switch|case|delete|new|throw|goto)\b)(?=[A-Za-z_])"
                     r"[^;(){}=\n]*?\b([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*)(?=\s*(?:\(|$))")
PUNCT = re.compile(r"[(){};]")


def demangle(name):
    m = CTOR.match(name)
    if m:
        return m.group(2), {"0": m.group(2), "1": "~" + m.group(2)}.get(m.group(1), "?" + m.group(1))
    m = METHOD.match(name)
    if m:
        return m.group(2), m.group(1)
    return None, name


def _blank(m):
    """A comment becomes spaces (its line breaks kept); a literal keeps its quotes, not its text."""
    text = m.group(0)
    if text[0] in "\"'":
        return text[0] + " " * (len(text) - 2) + text[-1]
    return re.sub(r"[^\n]", " ", text)


def zh_definitions(text):
    """(class, method) of each out-of-line definition in one ZH .cpp, in file order.

    A definition is a ZH_HEAD head, a balanced parameter list and then -- past `const`,
    `throw(...)` or a constructor's initializer list -- a body `{`. A `;` first makes it
    a call (`Base::f(` over several lines), a declaration or a data initializer
    (`BezierSegment::s_bezBasisMatrix( ... );`); a `}` first, a fragment."""
    code = CPP_NOISE.sub(_blank, text)     # same length and line breaks as `text`
    at = 0
    for raw, line in zip(text.split("\n"), code.split("\n")):
        start, at = at, at + len(line) + 1
        lead = len(line) - len(line.lstrip()) if raw.startswith("/") else 0   # `/*static*/ void X::f(`
        m = ZH_HEAD.match(line[lead:])
        if not m:
            continue
        i = start + lead + m.end()
        while i < len(code) and code[i].isspace():
            i += 1
        if i >= len(code) or code[i] != "(":
            continue
        depth = 0
        for tok in PUNCT.finditer(code, i):
            c = tok.group()
            if c in "()":
                depth += 1 if c == "(" else -1
            else:                          # the first brace or `;` decides, inside parentheses or not
                if c == "{" and depth == 0:
                    yield m.group(1), m.group(2)
                break


class Paths:
    """Map a reference path onto this tree's spelling (case-insensitive)."""

    def __init__(self, layout, sources):
        self.layout = layout
        self.dirs = {}
        for s in sorted(sources):
            parts = s.split("/")
            for i in range(1, len(parts)):
                self.dirs.setdefault("/".join(parts[:i]).lower(), "/".join(parts[:i]))
        self.files = {s.lower(): s for s in sorted(sources)}

    def repo(self, code_rel):
        """`GameEngine/Source/X/Y.cpp` (relative to a Code/ root) -> repo path."""
        rel = (self.layout.src + code_rel.replace("\\", "/").lstrip("/"))
        if rel.lower() in self.files:
            return self.files[rel.lower()]
        parts = rel.split("/")
        for i in range(len(parts) - 1, 0, -1):
            hit = self.dirs.get("/".join(parts[:i]).lower())
            if hit:
                return hit + "/" + "/".join(parts[i:])
        return rel


def _zh_cached(layout, kind, compute):
    """compute() once per git-identified ZH tree and version of this tool (the shared picker
    cache, tools/picker_cache.py): the ZH tree moves only with the submodule pin, the ledger
    every commit. A dirty, custom or missing tree is computed directly."""
    try:
        import picker_cache
    except ImportError:
        return compute()
    if not picker_cache.enabled():
        return compute()
    ident, _ = zh_identity(layout)
    if not ident.startswith("git:"):
        return compute()
    return picker_cache.keyed(kind, [ident, _digest(Path(__file__).resolve())], compute)


def zh_scan(layout):
    """[[path relative to the ZH tree, a Tools/ file, its zh_definitions, its
    class_inline_members (none for a Tools/ file), the classes COPY_DEF finds]] per ZH .cpp
    in walk order; an unreadable file carries None for the three lists. zh_index's per-file
    part, cached per ZH tree."""
    def scan():
        out = []
        for dp, dn, fn in sorted(os.walk(layout.zh)):
            dn.sort()
            tool = Path(dp).relative_to(layout.zh).parts[:1] == ("Tools",)
            for f in sorted(fn):
                if not f.lower().endswith(".cpp"):
                    continue
                p = Path(dp) / f
                zrel = p.relative_to(layout.zh).as_posix()
                try:
                    text = p.read_text(encoding="latin-1")
                except OSError:
                    out.append([zrel, tool, None, None, None])
                    continue
                out.append([zrel, tool, [list(d) for d in zh_definitions(text)],
                            [] if tool else [list(d) for d in class_inline_members(text)],
                            [m.group(1) for m in COPY_DEF.finditer(CPP_NOISE.sub(_blank, text))]])
        return out
    return _zh_cached(layout, "tu_map-zh-scan", scan)


def zh_index(layout, paths, header_classes=frozenset()):
    """({(class, method): file}, {class: its one site file}, classes whose copy
    constructor a ZH .cpp defines out of line, the files of ZH's Tools/ programs).
    A member written inside a class body in a game .cpp is that file's definition
    when no other .cpp writes the same (class, member) and no ZH header defines a class
    of that name (`header_classes`); such a class counts each .cpp that writes it as a
    site."""
    meth, sites, copies, tools = {}, collections.defaultdict(set), set(), set()
    local = collections.defaultdict(set)     # (class, member) written inside a class a .cpp defines
    game = collections.defaultdict(set)      # (class, member) -> game .cpp files defining it out of line
    if not layout.zh.exists():
        return meth, {}, copies, tools
    for zrel, tool, defs, inline, copied in zh_scan(layout):
        rel = paths.repo(zrel)
        if tool:
            tools.add(rel)
        if defs is None:                     # unreadable
            continue
        for c, m in defs:
            meth.setdefault((c, m), rel)
            sites[c].add(rel)
            if not tool:
                game[(c, m)].add(rel)
        for c, m in inline:
            local[(c, m)].add(rel)
        copies.update(copied)
    for key, rels in game.items():           # overloads one per file: no file is the definition
        if len(rels) > 1:
            del meth[key]
        else:
            meth[key] = next(iter(rels))     # a game file wins over a Tools/ copy
    for (c, m), rels in local.items():
        if c in header_classes:              # a header's class of that name (WWLib's Pipe, not netserv.cpp's)
            continue
        if len(rels) == 1 and (c, m) not in meth:
            meth[(c, m)] = next(iter(rels))
        sites[c].update(rels)
    return meth, {c: next(iter(v)) for c, v in sites.items() if len(v) == 1}, copies, tools


def implicit_copy(name, cls, meth, zmeth, zsite, copies):
    """True for a copy constructor of a class ZH knows (it defines a constructor of the
    class or has a site) but whose copy form no ZH .cpp defines: MSVC wrote it, and emits
    it as a COMDAT in whichever unit makes a copy (LANAPI's for ??0LANGameSlot@@QAE@ABV0@@Z
    at 0x0044B27F), not in the file defining another constructor. Like a header-inline
    body it gets no Z, S or N."""
    return bool(cls and COPY_CTOR.match(name) and cls not in copies
                and ((cls, meth) in zmeth or cls in zsite))


# `class X ... {` and, inside it, the name that opens a member head: the first
# `name(` whose parameter list is followed only by const, throw(...), an
# initializer list or nothing before the body.
CLASS_HEAD = re.compile(r"\b(?:class|struct)\s+(?:__declspec\s*\([^)]*\)\s*)?([A-Za-z_]\w*)\s*(?::[^;{}]*)?\{")
MEMBER_NAME = re.compile(r"(~?[A-Za-z_]\w*)\s*\(")
MEMBER_TAIL = re.compile(r"\s*(?:const\b\s*)?(?:throw\s*\([^)]*\)\s*)?(?::.*)?$", re.S)
# MSVC's function-class code after a member's `@@`: private/protected/public virtual.
VIRTUAL_CODES = "EFMNUV"


def _member_name(head):
    """The member a class-body head defines (`virtual void f(int) const`, `X(int a) : B(a)`),
    or None for anything else (a macro call, a nested type, an access label alone)."""
    for m in MEMBER_NAME.finditer(head):
        depth, i = 0, m.end() - 1
        while i < len(head):
            depth += {"(": 1, ")": -1}.get(head[i], 0)
            if depth == 0:
                break
            i += 1
        if depth == 0 and MEMBER_TAIL.match(head, i + 1):
            return m.group(1)
    return None


def class_inline_members(text):
    """(class, member) of each member whose body is written inside its class."""
    code = CPP_NOISE.sub(_blank, text)
    for m in CLASS_HEAD.finditer(code):
        cls, depth, head = m.group(1), 0, m.end()
        for i in range(m.end(), len(code)):
            c = code[i]
            if c == "{":
                if depth == 0:
                    name = _member_name(re.sub(r"\b(?:public|protected|private)\s*:", " ", code[head:i]))
                    if name:
                        yield cls, name
                depth += 1
            elif c == "}":
                if depth == 0:
                    break
                depth -= 1
                if depth == 0:
                    head = i + 1
            elif c == ";" and depth == 0:
                head = i + 1


# A function-like `#define NAME(params) body`, continuation lines included.
MACRO_DEF = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)\(([^)]*)\)((?:[^\n]*\\\r?\n)*[^\n]*)", re.M)
MACRO_CONT = re.compile(r"\\\r?\n")


def header_macros(texts):
    """{name: (params, body)} of the function-like macros in `texts` whose body defines a
    function (holds balanced `{}`) or invokes such a macro: MAKE_STANDARD_MODULE_MACRO,
    MEMORY_POOL_GLUE and the like write member bodies into every class that invokes
    them. A body with unbalanced braces (a BEGIN_/END_ pair) is never expanded. First
    definition wins."""
    defs = {}
    for text in texts:
        for m in MACRO_DEF.finditer(text):
            body = MACRO_CONT.sub(" ", m.group(3))
            if m.group(1) not in defs and body.count("{") == body.count("}"):
                defs[m.group(1)] = ([p.strip() for p in m.group(2).split(",") if p.strip()], body)
    out = {k: v for k, v in defs.items() if "{" in v[1]}
    grew = True
    while grew:
        grew = False
        for k, v in defs.items():
            if k not in out and any(re.search(r"\b" + re.escape(n) + r"\s*\(", v[1]) for n in out):
                out[k] = v
                grew = True
    return out


def _macro_args(text, i):
    """(arguments, end) of the invocation whose `(` precedes `i`, or (None, i) when unbalanced."""
    depth, args, start = 1, [], i
    while i < len(text):
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if not depth:
                args.append(text[start:i].strip())
                return args, i + 1
        elif c == "," and depth == 1:
            args.append(text[start:i].strip())
            start = i + 1
        i += 1
    return None, i


def expand_macros(text, macros, depth=3):
    """`text` with #define lines blanked and each invocation of `macros` replaced by its
    body (arguments substituted, `#p` stringised, `##` pasted), `depth` levels deep, so
    class_inline_members sees the members a macro writes into a class."""
    text = MACRO_DEF.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)
    if not macros:
        return text
    call = re.compile(r"\b(" + "|".join(sorted(map(re.escape, macros))) + r")\s*\(")
    for _ in range(depth):
        out, at = [], 0
        for m in call.finditer(text):
            if m.start() < at:
                continue
            args, end = _macro_args(text, m.end())
            if args is None:
                break
            params, body = macros[m.group(1)]
            sub = dict(zip(params, args))
            body = re.sub(r"(?<!#)#\s*([A-Za-z_]\w*)",
                          lambda t: f'"{sub[t.group(1)]}"' if t.group(1) in sub else t.group(0), body)
            body = re.sub(r"\b[A-Za-z_]\w*\b", lambda t: sub.get(t.group(0), t.group(0)), body)
            out += [text[at:m.start()], re.sub(r"\s*##\s*", "", body)]
            at = end
        if not out:
            break
        text = "".join(out) + text[at:]
    return text


def zh_header_members(layout):
    """{(class, member)} whose ZH body sits in a header: written inside the class (by hand
    or by a ZH header macro such as MAKE_STANDARD_MODULE_MACRO), or as an `inline X::y(`
    definition at header scope. A class whose body a header writes also gives
    (class, None), so zh_index can tell a header's class from a .cpp's local one."""
    if not layout.zh.exists():
        return set()
    return {tuple(m) for m in _zh_cached(layout, "tu_map-zh-header-members",
                                          lambda: sorted(_zh_header_members(layout), key=repr))}


def _zh_header_members(layout):
    out = set()
    texts = []
    for dp, dn, fn in sorted(os.walk(layout.zh)):
        dn.sort()
        for f in sorted(fn):
            if not f.lower().endswith((".h", ".hpp")):
                continue
            try:
                texts.append((Path(dp) / f).read_text(encoding="latin-1"))
            except OSError:
                continue
    macros = header_macros(texts)
    for text in texts:
        out.update(zh_definitions(text))
        out.update(class_inline_members(expand_macros(text, macros)))
        out.update((m.group(1), None) for m in CLASS_HEAD.finditer(CPP_NOISE.sub(_blank, text)))
    return out


def header_comdat(name, cls, meth, z, header_members):
    """A constructor or virtual member ZH defines only in a header is a select-any COMDAT:
    MSVC emits it in whichever unit first needs it out of line (a derived constructor's
    call, a vftable), not in its class's .cpp, so the class site (S) does not place it."""
    if z or (cls, meth) not in header_members:
        return False
    if name.startswith("??0"):
        return True
    m = CTOR.match(name) or METHOD.match(name)
    return bool(m) and name[m.end():m.end() + 1] in VIRTUAL_CODES


def beside_own_site(rva, site, z_anchors, z_rvas):
    """An inline virtual whose class site has an out-of-line (Z) row within GAP of it,
    with no other file's Z row in between: the class's own code, and so its vftable
    and this COMDAT, sit there, so the class site still places it. A same-site anchor
    across another file's anchor is contested (adjacent TUs interleaving within GAP)."""
    if not site:
        return False
    i = bisect.bisect_left(z_rvas, rva)
    # only the nearest Z row on each side counts: any other file's row is nearer, the
    # anchor is contested
    return any(0 <= j < len(z_anchors) and abs(z_anchors[j][0] - rva) <= GAP
               and z_anchors[j][1] == site for j in (i - 1, i))


def file_strings(layout, paths, owner):
    out = {}
    path = layout.path("string_xrefs.tsv")
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        text, _, refs = line.rpartition("\t")
        m = re.search(r"[\\/]Code[\\/](.+\.(?:cpp|c))$", text, re.I)
        if not m or not refs.startswith("0x"):
            continue
        tu = paths.repo(m.group(1))
        for ref in refs.split(","):
            try:
                o = owner(int(ref, 16))
            except ValueError:
                continue
            if o is not None:
                out.setdefault(o, tu)
    return out


# A ledger note citing a WorldBuilder lead (`WB15D2AF0 names ...`, `named from WorldBuilder`).
WB_CITED = re.compile(r"\bWB[0-9A-Fa-f]{6,}\b|WorldBuilder|wb_name_leads|\bWB lead", re.I)


def wb_class(name):
    """The class of a `Class::method` (a lead's wb_name or its snapshot name), or None."""
    return name.rpartition("::")[0] or None if name and "::" in name else None


def wb_self(lead, row):
    """True when `row`'s naming is the lead's own: its ledger notes cite a WorldBuilder lead,
    or it now carries the lead's class where the lead's snapshot (tools/wb_match.py's
    current_name; none for an UNROWED body) had another. Such a row's N hint is the lead's
    path again, so the lead cannot corroborate it."""
    if WB_CITED.search(row.get("notes") or ""):
        return True
    cls = wb_class(lead.get("wb_name"))
    before = None if lead.get("current_kind") == "UNROWED" else wb_class(lead.get("current_name"))
    return bool(cls and row.get("cls") == cls and before != cls)


def wb_files(layout, paths):
    """{rva: (TU, lead)} from WB_LEADS: the .cpp/.c whose path a WorldBuilder function's own strings
    name (BFME 2's tree, `C:\\Projects\\bfme2\\Code\\...`), for the game function
    tools/wb_match.py paired it with. Headers name no TU."""
    out = {}
    for r in read_csv(layout.path(WB_LEADS)):
        m = re.search(r"[\\/]Code[\\/](.+\.(?:cpp|c))$", r.get("wb_file") or "", re.I)
        try:
            rva = int(r.get("target_rva") or "", 16)
        except ValueError:
            continue
        if m:
            out.setdefault(rva, (paths.repo(m.group(1)), r))
    return out


def w_score(rows):
    """(rows with both W and F, of them agreeing): W's test against the game's own strings."""
    both = [r for r in rows if r["W"] and r["F"]]
    return len(both), sum(1 for r in both if same(r["W"], r["F"]))


def w_passes(rows):
    n, ok = w_score(rows)
    return n >= W_MIN and ok >= W_GATE * n


# ---------------------------------------------------------------- vendored upstream TUs (L)
# Libraries built from upstream's own files, one retail TU per file. A library vendored as
# headers (ATL, GDI+, strsafe, the CRT splits, STLport) is emitted as COMDATs in whichever
# object used it, so its files name no TU and it is not listed here.
UPSTREAM_TU_LIBS = ("gamespy", "lua", "zlib", "lzhl")
VENDORED_TAG = re.compile(r"\bvendored=([a-z0-9]+)-")
NAMED_FILE = re.compile(r"(?<![\w.])([A-Za-z_]\w*\.(?:c|cpp))(?!\w)", re.I)
# A function head at file scope: column 0, no statement keyword, the name right before `(`.
C_HEAD = re.compile(r"^(?!(?:return|else|if|while|for|do|switch|case|goto|sizeof|typedef|struct|union|enum)\b)"
                    r"(?=[A-Za-z_])[^;(){}=\n#:\"]*?\b([A-Za-z_]\w*)(?=\s*(?:\(|$))")
FREE_CXX = re.compile(r"^\?([A-Za-z_]\w*)@@[YZ]")
C_SYMBOL = re.compile(r"^[_@]([A-Za-z_]\w*?)(?:@\d+)?$")


def c_definitions(text):
    """Names of the functions a C or C++ file defines: `name` for a file-scope function whose
    balanced parameter list is followed by its body, directly (ANSI) or after `;`-terminated
    parameter declarations (K&R, zlib 1.1.4's style), and `Class::method` for zh_definitions'
    out-of-line members. A prototype (`;` right after the list) defines nothing."""
    code = CPP_NOISE.sub(_blank, text)
    out = {f"{c}::{m}" for c, m in zh_definitions(text)}
    at = 0
    for line in code.split("\n"):
        start, at = at, at + len(line) + 1
        m = C_HEAD.match(line)
        if not m:
            continue
        i, depth = start + m.end(), 0
        while i < len(code) and code[i].isspace():     # GameSpy's `GPResult gpiFoo` / `(` on the next line
            i += 1
        if i >= len(code) or code[i] != "(":
            continue
        while i < len(code):
            if code[i] == "(":
                depth += 1
            elif code[i] == ")":
                depth -= 1
                if not depth:
                    break
            elif code[i] in ";{}":
                break
            i += 1
        body = code.find("{", i) if not depth and i < len(code) else -1
        decls = code[i + 1:body].strip() if body >= 0 else ";"
        if not decls or (decls[0] not in ";," and decls.endswith(";") and not re.search(r"[{}=]", decls)):
            out.add(m.group(1))
    return out


def c_symbol(name):
    """The source spelling of a ledger symbol: `f` for a C name (`_f`, `_f@8`, `@f@8`) or a
    free C++ function (`?f@@YA...`), `Class::method` for a member; else None."""
    m = FREE_CXX.match(name)
    if m:
        return m.group(1)
    cls, meth = demangle(name)
    if cls:
        return f"{cls}::{meth}"
    m = C_SYMBOL.match(name)
    return m.group(1) if m else None


def upstream_candidates(layout, ledger):
    """{source: library} of the .c/.cpp files a ledger row tags `vendored=<lib>-<ver>` with a
    library of UPSTREAM_TU_LIBS (`upstream_files` decides which of them are whole files)."""
    out = {}
    for r in ledger:
        s = r.get("source") or ""
        m = VENDORED_TAG.search(r.get("notes") or "")
        if m and m.group(1) in UPSTREAM_TU_LIBS and s.startswith(layout.src) and s.lower().endswith((".c", ".cpp")):
            out.setdefault(s, m.group(1))
    return out


def upstream_files(layout, ledger):
    """{source: (library, names it defines)} of the vendored files that are whole upstream
    files, each its own retail TU. A file carved out of one (`liolib_bfme1.c` from
    `liolib.c`, `peerCallbacksFinished.c` from `peerCallbacks.c`) is not: its stem extends the
    stem of a ledger source beside it and its text never names the file itself, where a
    whole file's own banner does (`$Id: lapi.c,v`, `/* deflate.c -- `, `gp.c`)."""
    stems = collections.defaultdict(set)
    for r in ledger:
        d, b = os.path.split((r.get("source") or "").lower())
        if b.endswith((".c", ".cpp")):
            stems[d].add(os.path.splitext(b)[0])
    candidates = upstream_candidates(layout, ledger)
    # The parent file on disk counts too: a parent whose rows left the ledger (or a
    # ledger that never rowed it) must not turn its carve-out into a whole file.
    for d in sorted({os.path.split(s)[0] for s in candidates}):
        stems[d.lower()] |= set(upstream_siblings(layout, d))
    out = {}
    for s, lib in sorted(candidates.items()):
        try:
            text = (layout.root / s).read_text(encoding="latin-1")
        except OSError:
            continue
        d, b = os.path.split(s.lower())
        stem = os.path.splitext(b)[0]
        carved = any(x != stem and stem.startswith(x) for x in stems[d])
        if not carved or b in {m.group(1).lower() for m in NAMED_FILE.finditer(text)}:
            out[s] = (lib, c_definitions(text))
    return out


def upstream_siblings(layout, d):
    """Lower-cased stems of the .c/.cpp files in directory `d` (a repo path) on disk."""
    try:
        names = os.listdir(layout.root / d)
    except OSError:
        return []
    return sorted(os.path.splitext(n.lower())[0] for n in names if n.lower().endswith((".c", ".cpp")))


def upstream_tus(files):
    """{(library, symbol): source} for the symbols exactly one whole upstream file of their
    library defines."""
    seen = collections.defaultdict(set)
    for s, (lib, names) in files.items():
        for n in names:
            seen[(lib, n)].add(s)
    return {k: next(iter(v)) for k, v in seen.items() if len(v) == 1}


def l_score(rows):
    """(held-out L rows retail order predicts, of them agreeing): each row with an L candidate
    (`Lcand`, before the gate), its own evidence set aside, is predicted by the nearest rows
    below and above that carry their own F, Z, S or L, when both name one TU within GAP (a
    TU is contiguous in retail .text)."""
    seq = [(r["rva"], r["F"] or r["Z"] or r["S"] or r["Lcand"], r["Lcand"]) for r in rows
           if r["F"] or r["Z"] or r["S"] or r["Lcand"]]
    n = ok = 0
    for (lo, a, _), (rva, _, own), (hi, b, _) in zip(seq, seq[1:], seq[2:]):
        if own and same(a, b) and hi - lo <= GAP:
            n += 1
            ok += same(own, a)
    return n, ok


def l_passes(rows):
    n, ok = l_score(rows)
    return n >= L_MIN and ok >= L_GATE * n


def same(a, b):
    return bool(a and b and a.lower() == b.lower())


def contradicts(tu, f=None, z=None, s=None):
    """Does a row's own pre-clustering evidence name a TU other than `tu`? F is the TU
    itself; without F, a row is contradicted only when neither its Z nor its S is `tu`."""
    if not tu:
        return False
    if f:
        return not same(f, tu)
    hard = [x for x in (z, s) if x]
    return bool(hard) and not any(same(x, tu) for x in hard)


def anchors(evidence):
    """{"F": tu, "Z": tu, "S": tu, "N": tu} from a tu_map.csv `evidence` cell."""
    out = {}
    for token in (evidence or "").split():
        k, eq, v = token.partition("=")
        if eq and k in ("F", "Z", "S", "N") and k not in out:
            out[k] = v
    return out


C_SPAN = re.compile(r"\bC=0x([0-9A-Fa-f]+)\.\.0x([0-9A-Fa-f]+)")


def disputed(m, t):
    """The F/Z/S anchor that contradicts the TU of `t` (a tu_at answer from load() map `m`):
    its own (its host body's, for an interior address) or that of any row its C evidence
    brackets on, followed through a run. None when no anchor does. A map built by these
    rules approves nothing disputed; an older map can."""
    seen, todo = set(), [t]
    while todo:
        r = todo.pop()
        ev = anchors(r["evidence"])
        if contradicts(t["tu"], ev.get("F"), ev.get("Z"), ev.get("S")):
            return f"{r['rva']} " + " ".join(f"{k}={ev[k]}" for k in "FZS" if ev.get(k))
        for span in C_SPAN.finditer(r["evidence"]):
            for x in span.groups():
                if int(x, 16) not in seen:
                    seen.add(int(x, 16))
                    todo.extend(q for q in m.get(int(x, 16), ()) if q["kind"].startswith("code"))
    return None


def approved_tu(m, t):
    """The file a row at the address of `t` (a tu_at answer from load() map `m`) belongs in,
    or None: t's TU when t is approved and no F/Z/S anchor disputes it. The one predicate
    tu_ownership (A2/A3) holds a row to and repair_queue dest routes a new row by."""
    if t and t["confidence"] == "approved" and t["tu"] and not disputed(m, t):
        return t["tu"]
    return None


def evidence_rows(layout, ledger=None):
    """Every known code body -- ledger rows, then Ghidra function starts the ledger lacks --
    with its own pre-clustering evidence (F, Z, S, N). `ledger` (rows of a functions.csv)
    defaults to the working tree's."""
    ledger = read_csv(layout.path("functions.csv")) if ledger is None else ledger
    rows, seen = [], set()
    for r in ledger:
        if "gen-alias" in (r.get("notes") or "") or not (r.get("target_rva") or "").startswith("0x"):
            continue
        try:
            rva = int(r["target_rva"], 16)
        except ValueError:
            continue
        if rva in seen:
            continue                       # one identity per address; first row wins
        seen.add(rva)
        try:
            size = int(r["target_size"])
        except (TypeError, ValueError):
            size = 0
        rows.append(dict(rva=rva, size=size, kind="code", name=r["name"], source=r["source"],
                         notes=r.get("notes") or ""))
    for g in read_csv(layout.path("ghidra_functions.csv")):
        try:
            rva = int(g["rva"], 16)
        except (KeyError, ValueError):
            continue
        if rva not in seen and rva >= 0x1000:
            seen.add(rva)
            rows.append(dict(rva=rva, size=int(g.get("size") or 0), kind="code-unledgered", name="", source=""))
    rows.sort(key=lambda r: r["rva"])
    starts = [r["rva"] for r in rows]

    def owner(rva):
        i = bisect.bisect_right(starts, rva) - 1
        if i >= 0 and rva < starts[i] + max(rows[i]["size"], 1):
            return starts[i]
        return None

    paths = Paths(layout, {r["source"] for r in rows if r["source"]})
    zhead = zh_header_members(layout)
    zmeth, zsite, zcopy, ztools = zh_index(layout, paths, {c for c, _ in zhead})
    F = file_strings(layout, paths, owner)
    W = wb_files(layout, paths)
    upstream = upstream_files(layout, ledger)
    defined = upstream_tus(upstream)
    for r in rows:
        r["cls"], r["meth"] = demangle(r["name"]) if r["name"] else (None, None)
        r["F"] = F.get(r["rva"])
        r["W"], lead = W.get(r["rva"], (None, None))
        r["Wself"] = bool(lead and wb_self(lead, r))
        r["implicit"] = implicit_copy(r["name"], r["cls"], r["meth"], zmeth, zsite, zcopy)
        r["Z"] = zmeth.get((r["cls"], r["meth"])) if r["cls"] and not r["implicit"] else None
        lib = upstream.get(r["source"], (None,))[0]
        r["Lcand"] = r["source"] if lib and defined.get((lib, c_symbol(r["name"]))) == r["source"] else None
    z_anchors = sorted((r["rva"], r["Z"]) for r in rows if r["Z"])   # out-of-line ZH definitions
    z_rvas = [a for a, _ in z_anchors]
    for r in rows:
        cls = r["cls"]
        inline = header_comdat(r["name"], cls, r["meth"], r["Z"], zhead) if cls else False
        if inline and not r["name"].startswith("??0") and beside_own_site(r["rva"], zsite.get(cls),
                                                                             z_anchors, z_rvas):
            inline = False
        inline = inline or r["implicit"]
        r["S"] = zsite.get(cls) if cls and not COMDAT.match(r["name"]) and not inline else None
        base = re.sub(r"ModuleData$", "", cls or "")
        r["N"] = (os.path.dirname(r["source"]) + "/" + base + ".cpp") if base and r["source"] \
            and not PLACEHOLDER.match(base) and not inline else None
    use_l = l_passes(rows)
    for r in rows:
        r["L"] = r["Lcand"] if use_l else None
        r["hard"] = r["F"] or r["Z"] or r["S"] or r["L"]
        r["hint"] = r["hard"] or r["N"]
        r["tool"] = bool(r["hard"]) and r["hard"] in ztools
        r["C"] = r["K"] = None
    return rows


def build(layout, ledger=None):
    rows = evidence_rows(layout, ledger)

    # Main address cluster per hinted TU; hints outside it are displaced COMDATs.
    by_hint = collections.defaultdict(list)
    for r in rows:
        if r["hint"]:
            by_hint[r["hint"].lower()].append(r)
    main, anchored = {}, set()
    use_w = w_passes(rows)
    for key, members in by_hint.items():
        clusters = [[members[0]]]
        for a, b in zip(members, members[1:]):
            if b["rva"] - a["rva"] > GAP:
                clusters.append([])
            clusters[-1].append(b)
        best = max(clusters, key=lambda c: (sum(1 for x in c if x["hard"]),
                                            sum(1 for x in c if not COMDAT.match(x["name"])), len(c)))
        if not any(x["hard"] or not COMDAT.match(x["name"]) for x in best):
            continue
        # an anchor: a row's own F/Z/S, or a WorldBuilder lead naming this very path (W) on a
        # row whose naming did not come from that lead (else the lead confirms itself)
        if any(x["hard"] and x["hard"].lower() == key or use_w and same(x["W"], key) and not x["Wself"]
               for x in best) and not any(x["tool"] for x in members):
            anchored.add(key)
        for x in best:
            main[id(x)] = key
    for r in rows:
        key = r["hint"].lower() if r["hint"] else None
        r["A"] = r["hint"] if (r["F"] or (key and main.get(id(r)) == key)) else None
        r["disp"] = bool(r["hint"] and not r["A"])

    # TUs whose small clusters interleave are one TU (one file, several classes) --
    # unless both are anchored: two TUs F/Z/S name differently are two files, and
    # interleaving makes both noncontiguous instead of renaming one into the other.
    span = {}
    for r in rows:
        if r["A"]:
            k = r["A"].lower()
            lo, hi = span.get(k, (r["rva"], r["rva"]))
            span[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    parent = {k: k for k in span}

    def find(k):
        while parent[k] != k:
            k = parent[k]
        return k
    order = sorted(span, key=lambda k: (span[k][0], k))
    torn = contested(order, span, anchored)
    for i, a in enumerate(order):
        for b in order[i + 1:]:
            if span[b][0] > span[a][1]:
                break
            if span[a][1] - span[a][0] > UNION_SPAN or span[b][1] - span[b][0] > UNION_SPAN:
                continue
            if a in torn or b in torn:
                continue
            ra, rb = find(a), find(b)
            if ra == rb or (ra in anchored and rb in anchored):
                continue
            keep, drop = (ra, rb) if (ra in anchored or rb not in anchored) else (rb, ra)
            parent[drop] = keep
    for r in rows:
        if r["A"] and not r["hard"]:        # a row's own F/Z/S anchor is never renamed by a merge
            r["A"] = spelled[find(r["A"].lower())]

    # Contiguity (C) and placeholder-class propagation (K), iterated.
    for _ in range(3):
        last = None
        prev = {}
        for r in rows:
            prev[id(r)] = last
            if r["A"]:
                last = r
        nxt = None
        for r in reversed(rows):
            a = prev[id(r)]
            if not r["A"] and not r["disp"] and a and nxt and a["A"] == nxt["A"] \
                    and nxt["rva"] - a["rva"] <= GAP:
                r["A"] = r["C"] = a["A"]
                r["Cvia"] = (a, nxt)
            if r["A"]:
                nxt = r
        votes = collections.defaultdict(collections.Counter)
        for r in rows:
            if r["A"] and r["cls"]:
                votes[r["cls"]][r["A"]] += 1
        for r in rows:
            if not r["A"] and not r["disp"] and r["cls"] and PLACEHOLDER.match(r["cls"]) \
                    and len(votes.get(r["cls"], ())) == 1:
                r["A"] = r["K"] = next(iter(votes[r["cls"]]))

    # Classification from the row's own evidence; U when its naming hint was merged.
    for r in rows:
        a = r["A"]
        r["by"] = ("F" if same(r["F"], a) else "Z" if same(r["Z"], a) else "S" if same(r["S"], a) else
                   "L" if same(r["L"], a) else "C" if r["C"] else "K" if r["K"] else "N" if same(r["N"], a) else "U" if a else "")
        r["contra"] = contradicts(a, r["F"], r["Z"], r["S"])

    # Confidence. Retail object order: a TU must be contiguous in .text. Its span is the
    # extent of the rows that could be approved for it (F/Z/S/L/N/U; a C row inside them
    # needs approved brackets, so it lies within): a K row is never approved, and one
    # emitted far away must not stretch the span over other TUs' rows.
    assigned = [r for r in rows if r["A"]]
    roots = {find(k) for k in anchored if k in parent}
    island = islands(assigned, roots)
    lo_hi = {}
    for r in assigned:
        if r["by"] not in APPROVABLE or id(r) in island:
            continue
        k = r["A"].lower()
        lo, hi = lo_hi.get(k, (r["rva"], r["rva"]))
        lo_hi[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    idx = [r["rva"] for r in assigned]
    # Only a row that could be approved contradicts a span: one of an anchored TU,
    # assigned by F/Z/S/L/N/U/C. A K row or an unanchored TU's naming hint never can.
    broken = set()
    for k, (lo, hi) in lo_hi.items():
        i, j = bisect.bisect_left(idx, lo), bisect.bisect_right(idx, hi)
        if any(x["A"].lower() != k and x["A"].lower() in roots and x["by"] in SPAN_BREAKERS
               and id(x) not in island for x in assigned[i:j]):
            broken.add(k)
    prov, island_p = provisional(assigned, roots, lo_hi) if PROVISIONAL else (set(), set())
    for r in rows:
        k = r["A"].lower() if r["A"] else None
        if not k:
            r["conf"] = "displaced" if r["disp"] else ""
            continue
        isle = island_p if k in prov else island
        ok = ((k in roots and k not in broken or k in prov) and r["by"] in APPROVABLE and not r["contra"]
              and id(r) not in isle)
        r["conf"] = "approved" if ok else "proposed"
        r["island"] = id(r) in isle
        r["prov"] = k in prov
    # C rows inherit approval only from two approved brackets. Within a run the
    # upper bracket is the next C row up, so walk down from the top until the
    # whole run resolves to its two ends (a fixed pass count left long runs
    # half-approved).
    changed = True
    while changed:
        changed = False
        for r in reversed(rows):
            if r["by"] == "C" and r["conf"] == "proposed" and not r["island"]:
                a, b = r["Cvia"]
                if a["conf"] == b["conf"] == "approved" and r["A"].lower() not in broken:
                    r["conf"] = "approved"
                    changed = True

    out = []
    for r in rows:
        ev = []
        for s in "FZSLNW":
            if r[s]:
                ev.append(f"{s}={r[s]}")
        if r["C"]:
            a, b = r["Cvia"]
            ev.append(f"C=0x{a['rva']:08X}..0x{b['rva']:08X}")
        if r["K"]:
            ev.append(f"K={r['cls']}")
        if r["A"] and r["A"].lower() in broken:
            ev.append("noncontiguous")
        if r.get("island"):
            ev.append("island")
        if r["contra"]:
            ev.append("contradicted")
        if r.get("prov") and r["conf"] == "approved":
            ev.append(PROV_TOKEN)
        out.append({"rva": f"0x{r['rva']:08X}", "size": r["size"], "kind": r["kind"],
                    "tu": r["A"] or "", "confidence": r["conf"], "by": r["by"] or "-",
                    "evidence": " ".join(ev), "source": r["source"]})
    out.extend(data_rows(layout, rows))
    out.sort(key=lambda d: (int(d["rva"], 16), d["kind"]))
    return _evidence().apply(layout, out)


ISLAND = 2
PROVISIONAL = True    # approve unanchored TUs under a provisional name (provisional())
PROV_MIN = 2          # approvable (N/U) rows a provisional TU needs
PROV_TOKEN = "provisional"


def provisional(assigned, roots, lo_hi):
    """(TU keys approved under a provisional name, their island rows). A TU no F/Z/S/L/W
    anchors, grouped by its rows' naming hints (N/U) alone, is approved for merging when it
    holds at least PROV_MIN such rows, no row that could be approved for another TU -- an
    anchored one's or another candidate's, islands aside -- sits inside its span, and its
    span overlaps no anchored TU's. Its name is the naming hint, still unproven: its rows
    carry PROV_TOKEN, so the naming lanes and the counts can tell them apart."""
    tool = {r["A"].lower() for r in assigned if r["tool"]}
    cand = {k for k in lo_hi if k not in roots and k not in tool}
    both = roots | cand
    island_p = islands(assigned, both)
    span, count = {}, collections.Counter()
    for r in assigned:
        k = r["A"].lower()
        if k in cand and r["by"] in APPROVABLE and id(r) not in island_p:
            lo, hi = span.get(k, (r["rva"], r["rva"]))
            span[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
            count[k] += 1
    anchored = sorted(v for k, v in lo_hi.items() if k in roots)
    starts = [lo for lo, _ in anchored]
    reach = list(itertools.accumulate((hi for _, hi in anchored), max))
    idx = [r["rva"] for r in assigned]
    out = set()
    for k, (lo, hi) in span.items():
        if count[k] < PROV_MIN:
            continue
        i, j = bisect.bisect_left(idx, lo), bisect.bisect_right(idx, hi)
        if any(x["A"].lower() != k and x["A"].lower() in both and x["by"] in SPAN_BREAKERS
               and id(x) not in island_p for x in assigned[i:j]):
            continue
        a = bisect.bisect_right(starts, hi) - 1          # anchored spans starting at or before hi
        if a >= 0 and reach[a] >= lo:                    # one of them reaches into [lo, hi]
            continue
        out.add(k)
    return out, island_p


def provisional_name(row):
    """True when a tu_map row (or tu_at answer) is approved under a provisional name: a
    merge may move it, but its TU path is no evidence of the file's name."""
    return row.get("confidence") == "approved" and PROV_TOKEN in (row.get("evidence") or "").split()


def canonical_tu(row):
    """True when a tu_map row is approved under a name its evidence proves (not provisional):
    the only kind of approval rename.py and rename_files.py read as a canonical file name."""
    return row.get("confidence") == "approved" and not provisional_name(row)


def contested(order, span, anchored):
    """Unanchored TU keys whose span interleaves with two or more anchored TUs' spans (each
    small enough to merge, UNION_SPAN) and also reaches past all of them. Interleaving says
    the hinted class shares a file with one of them, not which, and the U merge would take
    whichever starts first, stretching it across the other: MonsterDockUpdate's own run
    0x004A137F..0x004A17C1 follows RepairDockUpdate, but one row at 0x004A0E47 inside
    SupplyCenterDockUpdate's merged the whole class into SupplyCenterDockUpdate.cpp, whose
    span then covered RepairDockUpdate; AIHarvestPrepareSiteState (0x00544AB3..0x00544FC6)
    likewise stretched AIDock.cpp across AIHarvest.cpp's __FILE__ row 0x00544C62. Such a TU
    merges with neither and stays its own unanchored TU, which breaks no span. A hinted TU
    whose rows all lie within its anchored neighbours' extent (header-inline LZBuffer rows
    between Lz.cpp's and Huff.cpp's) still merges: there islands() judges each row."""
    small = [k for k in order if span[k][1] - span[k][0] <= UNION_SPAN]
    out = set()
    for k in small:
        if k in anchored:
            continue
        lo, hi = span[k]
        near = [span[a] for a in small if a in anchored and span[a][0] <= hi and span[a][1] >= lo]
        if len(near) >= 2 and (lo < min(a for a, _ in near) or hi > max(b for _, b in near)):
            out.add(k)
    return out


def islands(assigned, roots):
    """ids of the rows of island runs. In address order, the rows that could break a span
    (an anchored TU's, by F/Z/S/L/N/U/C) form runs of one TU each; a run of at most ISLAND
    rows, none of them F, shorter than the runs of one other TU on both sides of it, is
    an island: a header body emitted as a COMDAT in the host's object, or a row this repo
    named for the wrong class. It neither breaks the host's span nor counts in its own.
    A run holding an F, Z or L row (an out-of-line definition in its own TU) is never an
    island: naming around it must not override it."""
    seq = [r for r in assigned if r["A"].lower() in roots and r["by"] in SPAN_BREAKERS]
    runs = [list(g) for _, g in itertools.groupby(seq, key=lambda r: r["A"].lower())]
    out = set()
    for a, run, b in zip(runs, runs[1:], runs[2:]):
        if (len(run) <= ISLAND and len(run) < min(len(a), len(b)) and a[0]["A"].lower() == b[0]["A"].lower()
                and not any(x["by"] in ("F", "Z", "L") for x in run)):
            out.update(id(x) for x in run)
    return out


def _evidence():
    """tools/tu_evidence.py, imported late: it imports this module."""
    here = str(Path(__file__).resolve().parent)
    if here not in sys.path:
        sys.path.insert(0, here)
    import tu_evidence
    return tu_evidence


def data_rows(layout, rows):
    """A data item belongs to the TU every one of its referencing functions is in."""
    path = layout.path("data_xrefs.tsv")
    if not path.exists():
        return []
    starts = [r["rva"] for r in rows]
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    out = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines()[1:]:
        f = line.split("\t")
        if len(f) < 8 or not f[0].startswith("0x"):
            continue
        tus, confs, prov = set(), set(), False
        for c in filter(None, f[7].split(",")):
            i = bisect.bisect_right(starts, int(c, 16)) - 1
            r = rows[i] if i >= 0 else None
            if not r or not r["A"] or int(c, 16) >= r["rva"] + max(r["size"], 1):
                tus.add(None)
                continue
            tus.add(r["A"].lower())
            confs.add(r["conf"])
            prov = prov or bool(r.get("prov"))
        if len(tus) != 1 or None in tus:
            continue
        tu = spelled[next(iter(tus))]
        approved = confs == {"approved"}
        out.append({"rva": f[0], "size": f[2], "kind": "data:" + f[1], "tu": tu,
                    "confidence": "approved" if approved else "proposed", "by": "X",
                    "evidence": f"X={len(f[7].split(','))}refs" + (f" {PROV_TOKEN}" if approved and prov else ""),
                    "source": ""})
    return out


def render(out):
    buf = io.StringIO()
    w = csv.DictWriter(buf, COLUMNS, lineterminator="\n")
    w.writeheader()
    w.writerows(out)
    return buf.getvalue()


def load(root=ROOT):
    """rva -> list of tu_map rows (code first). Empty when no map exists."""
    m = collections.defaultdict(list)
    for r in read_csv(Layout(root).out):
        m[int(r["rva"], 16)].append(r)
    return m


# ---------------------------------------------------------------- routing an address
class Image:
    """Retail bytes by RVA through the PE section table, read on first use."""

    def __init__(self, path):
        self.path, self._data, self._secs = Path(path), None, []

    @classmethod
    def open(cls, path):
        """An Image, or None when the file is absent (tu_at then never claims a boundary)."""
        return cls(path) if path is not None and Path(path).is_file() else None

    def read(self, rva, n):
        if self._data is None:
            data = self.path.read_bytes()
            pe = struct.unpack_from("<I", data, 0x3C)[0]
            table = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
            for i in range(struct.unpack_from("<H", data, pe + 6)[0]):
                vsize, va, rsize, raw = struct.unpack_from("<IIII", data, table + 40 * i + 8)
                self._secs.append((va, min(vsize, rsize), raw))
            self._data = data
        for va, size, raw in self._secs:
            if va <= rva and rva + n <= va + size:
                return self._data[raw + rva - va:raw + rva - va + n]
        return None


def _int(value):
    try:
        return int(value or 0)
    except ValueError:
        return 0


class Index:
    """tu_at's view of a load() map: the assigned code rows (C brackets) and the extent of
    every known body (code rows of any confidence, a body with no TU included)."""

    def __init__(self, m, image=None):
        got = sorted(((rva, r) for rva, rs in m.items() for r in rs
                      if r["kind"].startswith("code") and r["tu"] and r["confidence"] in ("approved", "proposed")),
                     key=lambda x: x[0])
        self.starts, self.rows = [x[0] for x in got], [x[1] for x in got]
        size = {}
        for rva, rs in m.items():
            for r in rs:
                if r["kind"].startswith("code"):
                    size[rva] = max(size.get(rva, 1), _int(r.get("size")))
        self.lo = sorted(size)
        self.hi = [s + size[s] for s in self.lo]
        self.reach = list(itertools.accumulate(self.hi, max))   # furthest end of any body starting at or before
        self.image = image

    def host(self, rva):
        """Start of the latest-starting known body that contains RVA, or None."""
        i = bisect.bisect_right(self.lo, rva) - 1
        while i >= 0 and self.reach[i] > rva:
            if self.hi[i] > rva:
                return self.lo[i]
            i -= 1
        return None

    def gap(self, rva):
        """For an RVA in no known body: "padding", "start" (the first non-padding byte after the
        body below it, where an unsplit function begins), "inside" (past such a start), or None
        when the image cannot say."""
        i = bisect.bisect_right(self.lo, rva) - 1
        if self.image is None or i < 0 or self.reach[i] > rva:
            return None
        floor = self.reach[i]
        got = self.image.read(floor, rva - floor + 1)
        if not got:
            return None
        if got[-1] == PAD:
            return "padding"
        return "start" if all(b == PAD for b in got[:-1]) else "inside"


def code_index(m, image=None):
    """tu_at's index of a load() map; pass Image.open(Layout(root).image) for boundary evidence."""
    return Index(m, image)


def tu_at(m, rva, index=None):
    """The code row of `m` (a load() map) for RVA, or None.

    An address the map has a code row for gets that row, whatever its confidence
    (empty for a known body no signal reaches). An address inside a known body
    inherits that body's TU and confidence: nothing approves the interior of a
    displaced, proposed or unassigned body. An address in no known body gets no
    answer when the retail image shows padding; otherwise C on the same terms as
    an unledgered function (the nearest assigned code rows below and above name
    one TU and start within GAP of each other), approved only when both brackets
    are and the image shows the address starts right after the body below it.
    """
    for r in m.get(rva, ()):
        if r["kind"].startswith("code"):
            return r
    index = code_index(m) if index is None else index
    host = index.host(rva)
    if host is not None:
        r = next(r for r in m[host] if r["kind"].startswith("code"))
        return {"rva": f"0x{rva:08X}", "size": "", "kind": "code-interior", "tu": r["tu"],
                "confidence": r["confidence"], "by": r["by"],
                "evidence": f"inside 0x{host:08X} {r['evidence']}".rstrip(), "source": ""}
    starts, rows = index.starts, index.rows
    i = bisect.bisect_left(starts, rva)
    if i == 0 or i >= len(starts):
        return None
    lo, hi, a, b = starts[i - 1], starts[i], rows[i - 1], rows[i]
    if a["tu"].lower() != b["tu"].lower() or hi - lo > GAP:
        return None
    gap = index.gap(rva)
    if gap == "padding":
        return None
    conf = "approved" if gap == "start" and a["confidence"] == b["confidence"] == "approved" else "proposed"
    prov = conf == "approved" and (provisional_name(a) or provisional_name(b))
    return {"rva": f"0x{rva:08X}", "size": "", "kind": "code-inferred", "tu": a["tu"], "confidence": conf,
            "by": "C", "evidence": f"C=0x{lo:08X}..0x{hi:08X} gap={gap or 'unread'}" + (f" {PROV_TOKEN}" if prov else ""),
            "source": ""}


# ---------------------------------------------------------------- freshness
def _digest(path):
    try:
        return hashlib.sha256(path.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
    except OSError:
        return "missing"


ZH_KEY = "zh:GeneralsMD/Code"
L_KEY = "vendored-upstream:Code"


def upstream_digest(layout):
    """sha256 over the path and CRLF-normalised text of every file `upstream_files` reads (L)."""
    h = hashlib.sha256()
    candidates = sorted(upstream_candidates(layout, read_csv(layout.path("functions.csv"))))
    for s in candidates:
        p = layout.root / s
        text = p.read_bytes().replace(b"\r\n", b"\n") if p.is_file() else b"missing"
        h.update(s.encode() + b"\0" + text + b"\0")
    for d in sorted({os.path.split(s)[0] for s in candidates}):   # upstream_files' carve-out test
        h.update(d.encode() + b"\0" + "\0".join(upstream_siblings(layout, d)).encode() + b"\0")
    return h.hexdigest()


def _git(cwd, *args):
    # a hook's GIT_DIR/GIT_INDEX_FILE would point every call at the outer repository
    env = {k: v for k, v in os.environ.items()
           if k not in ("GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR", "GIT_PREFIX")}
    try:
        got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, env=env)
    except OSError:
        return None
    return got.stdout.strip() if got.returncode == 0 else None


def zh_identity(layout, kind=None):
    """(digest, note) of the ZH tree the map reads. `git:<tree id>` -- content-addressed, so
    equal wherever the same files are checked out -- for the default tree in a clean checkout
    (untracked files count as dirt), noting the commit; else, or for a custom --zh, or when
    `kind` is "sha256", `sha256:` over the relative path and CRLF-normalised bytes of every
    .cpp zh_index and .h zh_header_members read. `kind` "git" tries the tree id for a custom
    --zh too."""
    zh = layout.zh
    if not zh.is_dir():
        return "missing", "no ZH tree"
    commit = _git(zh, "rev-parse", "HEAD")
    if commit and kind != "sha256" and (kind == "git" or not layout.zh_custom):
        tree = _git(zh, "rev-parse", "HEAD:./")
        if tree and _git(zh, "--no-optional-locks", "status", "--porcelain", "--untracked-files=all", "--", ".") == "":
            return f"git:{tree}", f"commit {commit}"
    h = hashlib.sha256()
    for dp, dn, fn in sorted(os.walk(zh)):
        dn.sort()
        for f in sorted(fn):
            if f.lower().endswith((".cpp", ".h", ".hpp")):
                p = Path(dp) / f
                h.update(p.relative_to(zh).as_posix().encode() + b"\0")
                h.update(p.read_bytes().replace(b"\r\n", b"\n") + b"\0")
    why = "custom --zh" if layout.zh_custom else "dirty or untracked checkout"
    return f"sha256:{h.hexdigest()}", (f"commit {commit}, " if commit else "") + why


def fingerprint(layout, zh_kind=None):
    """sha256sum-like lines for the map's inputs (the ZH tree's as zh_identity), this tool
    and the map itself; `#` lines are notes, never compared."""
    out = ["# inputs of tu_map.csv as tools/tu_map.py wrote it; `tu_map.py --check-fresh` compares them"]
    for p in [layout.path(n) for n in FINGERPRINTED]:
        out.append(f"{_digest(p)}  {p.resolve().relative_to(layout.root.resolve()).as_posix()}")
    if _evidence().PROMOTED:                 # a promoted layout signal reads the retail image
        out.append(f"{_digest(layout.image)}  {layout.image.resolve().relative_to(layout.root.resolve()).as_posix()}")
    out.append(f"{upstream_digest(layout)}  {L_KEY}")
    digest, note = zh_identity(layout, zh_kind)
    out.append(f"{digest}  {ZH_KEY}")
    out.append(f"# {ZH_KEY}: {note}")
    for p in (Path(__file__).resolve(), Path(__file__).resolve().with_name("tu_evidence.py"), layout.out):
        try:
            name = p.resolve().relative_to(layout.root.resolve()).as_posix()
        except ValueError:
            name = "tools/" + p.name
        out.append(f"{_digest(p)}  {name}")
    return "\n".join(out) + "\n"


def _parse_fingerprint(text):
    return {name: digest for digest, _, name in (line.partition("  ") for line in text.splitlines()
                                                 if not line.startswith("#")) if name}


def current_rows(layout):
    """(rows with every value a string, stale): tu_map.csv when it was written from the
    current inputs (stale is []), else build() from them (stale: check_fresh's list). A
    rebuild is kept in the shared picker cache (tools/picker_cache.py) under the inputs'
    fingerprint -- the inputs and tool digests check_fresh compares -- so every worktree of
    the clone with the same inputs (a picker, a merge worker mid-merge) reads it back."""
    have = layout.fingerprint.read_text(encoding="utf-8") if layout.fingerprint.exists() else ""
    old = _parse_fingerprint(have) if have.strip() else {}
    new = _parse_fingerprint(fingerprint(layout, old.get(ZH_KEY, "").partition(":")[0] or None))
    stale = ([name for name in new if old.get(name) != new[name]] if old
             else [layout.fingerprint.relative_to(layout.root).as_posix()])
    if not stale:
        return [{k: str(v) for k, v in r.items()} for r in read_csv(layout.out)], stale

    def rebuild():
        return [{k: str(v) for k, v in r.items()} for r in build(layout)]
    try:
        import picker_cache
    except ImportError:
        return rebuild(), stale
    key = [layout.reverse, sorted(new.items())]
    return picker_cache.keyed("tu_map-build", key, rebuild), stale


def check_fresh(layout):
    """[] when tu_map.csv was written from the current inputs, else the inputs that changed
    (or the missing fingerprint's own name). The ZH tree is identified the way it was
    recorded (git tree id or content hash), so a worktree's --zh copy and the submodule
    compare equal when their files are."""
    have = layout.fingerprint.read_text(encoding="utf-8") if layout.fingerprint.exists() else ""
    if not have.strip():
        return [layout.fingerprint.relative_to(layout.root).as_posix()]
    old = _parse_fingerprint(have)
    new = _parse_fingerprint(fingerprint(layout, old.get(ZH_KEY, "").partition(":")[0] or None))
    return [name for name in new if old.get(name) != new[name]]


# ---------------------------------------------------------------- validation
def _ledger_at(layout, rev):
    text = subprocess.run(["git", "show", f"{rev}:{layout.reverse}/functions.csv"], cwd=layout.root,
                          capture_output=True, check=True).stdout.decode("utf-8", "replace")
    return list(csv.DictReader(io.StringIO(text, newline="")))


def _named(row):
    return bool(row["name"] and row["cls"] and not PLACEHOLDER.match(row["cls"])
                and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", row["source"]))


def self_check(out):
    """(approved code rows, those whose own pre-clustering F/Z/S name another TU) of a map."""
    n = bad = 0
    for r in out:
        if r["kind"].startswith("code") and r["confidence"] == "approved":
            n += 1
            ev = anchors(r["evidence"])
            bad += contradicts(r["tu"], ev.get("F"), ev.get("Z"), ev.get("S"))
    return n, bad


def validate(layout, rev, predict=None, lookup=None):
    """Score routing predictions made from REV's ledger against independent evidence: the
    F/Z/S of rows that landed since REV (a real name at an address REV's ledger had no row
    for). `predict(ledger) -> rows` and `lookup(map, rva, index)` default to this module's
    build and tu_at; a caller can pass another revision's to score it the same way."""
    predict = predict or (lambda led: build(layout, led))
    lookup = lookup or (lambda m, rva, ix: tu_at(m, rva, ix))
    then = _ledger_at(layout, rev)
    had = {int(r["target_rva"], 16) for r in then if (r.get("target_rva") or "").startswith("0x")}
    now = [r for r in evidence_rows(layout) if r["kind"] == "code" and r["rva"] not in had and _named(r)
           and (r["F"] or r["Z"] or r["S"])]
    m = collections.defaultdict(list)
    for r in predict(then):
        m[int(r["rva"], 16)].append(r)
    index = code_index(m, Image.open(layout.image))
    tally = collections.defaultdict(lambda: [0, 0])
    misses = []
    for r in now:
        t = lookup(m, r["rva"], index)
        if not t or t["confidence"] not in ("approved", "proposed") or not t["tu"]:
            continue
        bad = contradicts(t["tu"], r["F"], r["Z"], r["S"])
        key = (t["confidence"], t["by"], {"code-inferred": "gap", "code-interior": "interior"}.get(t["kind"], "row"))
        tally[key][0] += 1
        tally[key][1] += bad
        if bad and t["confidence"] == "approved":
            misses.append((r["rva"], r["name"], t["tu"], r["F"] or r["Z"] or r["S"]))
    return len(now), dict(tally), misses


def report_validation(layout, rev, out=None):
    n, bad = self_check(read_csv(layout.out) if out is None else out)
    print(f"self-check: {bad} of {n} approved code rows in {layout.out.name} have their own F/Z/S "
          f"naming another TU")
    rows = evidence_rows(layout)
    n, ok = w_score(rows)
    print(f"W (WorldBuilder lead path) against the row's own F: {ok}/{n} agree "
          f"({100 * ok / n:.1f}%); anchors {'on' if n >= W_MIN and ok >= W_GATE * n else 'OFF'} "
          f"(gate {W_GATE:.0%}, at least {W_MIN} rows)" if n else "W: no row has both W and F; anchors OFF")
    n, ok = l_score(rows)
    print(f"L (vendored upstream file) held out against retail order: {ok}/{n} agree "
          f"({100 * ok / n:.1f}%); anchors {'on' if l_passes(rows) else 'OFF'} "
          f"(gate {L_GATE:.0%}, at least {L_MIN} rows); {sum(1 for r in rows if r['L'])} L rows"
          if n else "L: retail order predicts no L row; anchors OFF")
    landed, tally, misses = validate(layout, rev)
    print(f"landed since {rev}: {landed} named rows with F/Z/S evidence at addresses its ledger had no row for")
    for conf in ("approved", "proposed"):
        rows = {k: v for k, v in tally.items() if k[0] == conf}
        tot = sum(v[0] for v in rows.values())
        dis = sum(v[1] for v in rows.values())
        rate = f"{100 * dis / tot:.1f}%" if tot else "-"
        print(f"  {conf}: {dis}/{tot} disagree ({rate})  " +
              "  ".join(f"{b}/{via}={v[1]}/{v[0]}" for (_, b, via), v in sorted(rows.items())))
    for rva, name, tu, want in misses[:20]:
        print(f"    0x{rva:08X} {name[:60]}: routed {tu}, evidence {want}")
    return 0


def summary(out, prefix=None):
    rows = [r for r in out if not prefix or r["source"].startswith(prefix)]
    conf = collections.Counter((r["kind"].split(":")[0], r["confidence"] or "none") for r in rows)
    by = collections.Counter(r["by"] for r in rows if r["confidence"] == "approved")
    tus = collections.Counter(r["tu"] for r in rows if r["confidence"] == "approved")
    prov = [r for r in rows if r["kind"].startswith("code") and provisional_name(r)]
    print(f"rows {len(rows)}  " + "  ".join(f"{k[0]}/{k[1]}={v}" for k, v in sorted(conf.items())))
    print("approved by " + " ".join(f"{k}={v}" for k, v in sorted(by.items())))
    print(f"approved TUs {len(tus)} (with >=2 rows: {sum(1 for v in tus.values() if v > 1)}); "
          f"{len({r['tu'].lower() for r in prov})} of them under a provisional name ({len(prov)} code rows)")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--check", action="store_true", help="exit 1 when tu_map.csv differs from a rebuild")
    g.add_argument("--check-fresh", action="store_true",
                   help="exit 1 when an input changed since tu_map.csv was written (hashes only)")
    g.add_argument("--validate", metavar="REV", help="score predictions from REV's ledger against landed rows")
    g.add_argument("--dir", help="summarise rows whose current source starts with this prefix")
    g.add_argument("--holdout", metavar="RULE",
                   help="held-out purity of an approval rule (tools/tu_holdout.py): p-groups, prov-min-1, "
                        "brackets, interleave, k-only")
    ap.add_argument("--folds", type=int, default=5, help="with --holdout: folds")
    ap.add_argument("--json", help="with --holdout: write the report here")
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--zh", type=Path, help="ZH GeneralsMD/Code tree (default: the Open-BFME-1 submodule's)")
    a = ap.parse_args(argv)
    layout = Layout(a.root, a.zh)
    if a.check_fresh:
        stale = check_fresh(layout)
        if stale:
            print(f"tu_map: {layout.out.relative_to(layout.root).as_posix()} is stale (changed or missing: "
                  f"{', '.join(stale)}); run python3 tools/tu_map.py", file=sys.stderr)
            return 1
        return 0
    problem = layout.zh_problem()
    if problem:
        print(f"tu_map: {problem}; Z and S evidence would be empty", file=sys.stderr)
        return 2
    if a.validate:
        return report_validation(layout, a.validate)
    if a.holdout:
        import tu_holdout
        return tu_holdout.main(a.holdout, a.folds, a.json, layout)
    out = build(layout)
    text = render(out)
    if a.check:
        cur = layout.out.read_text(encoding="utf-8") if layout.out.exists() else ""
        if cur != text:
            print(f"tu_map: {layout.out.relative_to(layout.root).as_posix()} is stale; "
                  "run python3 tools/tu_map.py", file=sys.stderr)
            return 1
        return 0
    if not a.dir:
        layout.out.write_text(text, encoding="utf-8", newline="")
        layout.fingerprint.write_text(fingerprint(layout), encoding="utf-8", newline="")
    summary(out, a.dir)
    return 0


if __name__ == "__main__":
    sys.exit(main())
