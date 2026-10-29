#!/usr/bin/env python3
"""Microsoft headers as the only source of CRT, Windows SDK and MS STL definitions.

Every struct, typedef, enum, prototype, dllimport declaration, macro or inline
function a source or shim writes for itself, when a Microsoft header of the
toolchain already declares it, should come from that header instead. This tool:

  index   builds an index of every name the Microsoft headers declare, with
          file:line. Authoritative entries come from `cl /E` output of
          kitchen-sink translation units (C++ and C) parsed by the declaration
          parser below; every header is also parsed raw (all #if branches,
          macros expanded) for coverage; macro values are probed through cl.
          `--root LABEL=DIR` (or MS_HEADER_EXTRA_ROOTS) adds a header root, for
          example the DirectX SDK's Include. `--validate` checks known names.
  scan    finds local definitions and declarations of indexed names in tracked
          files under Code/, reference/shims/ and vendor/stlport/, compares each
          with the real definition (layout, calling convention, dllimport,
          linkage, values) under the unit's configuration (`// cl:` defines,
          /MD, its own and its included headers' macros), follows the project
          headers the file includes, and classifies every file:
            drop-in candidate
                         the local copies equal the real ones as far as static
                         analysis can tell, the real ones are active under the
                         unit's configuration and no included project header
                         collides: include the real header, delete them, and
                         prove with ./build.sh: byte gate is the authority
            adapt        source-level differences only (member or parameter
                         spellings, pointee types), copies not provable under
                         the unit's configuration, unresolved includes or an
                         included header that redefines a type: edit then include
            unverified   a local body (inline function, macro) not proven
                         identical to the real one: prove it per body first
            conflicting  a difference that can change bytes (layout, calling
                         convention, dllimport, values) or C++ symbol names;
                         a CRT dllimport difference carries a note: verify
                         the callee per body, never blanket-replace
            shim         the whole file is a stand-in for a Microsoft header
            failed       the analysis did not finish (per-file timeout,
                         recursion): unknown, never clean
          Configuration macros (NOMINMAX, UNICODE, _WIN32_WINNT ...) are
          inputs to the headers and never removable.
          `--write-queue` writes reverse/ms_header_queue.tsv, one row per file;
          per-occurrence detail goes to build/ms_header_audit/occurrences.tsv.
  show    prints every occurrence in one file with the real definition's site.
  next    serves queue rows (a picker: `--class drop-in-candidate`, `--limit N`).
  check   refuses NEW local Microsoft-header definitions: `--staged` compares
          each staged file with HEAD's copy (its rename source when it moved),
          and refuses a file whose analysis does not finish (a hook's call);
          `check(paths)` is the same from Python.

Scratch and caches live under build/ms_header_audit/ (never the main
checkout's build/ when run from a worktree: everything is relative to ROOT).
"""
from __future__ import annotations

import argparse
import bisect
import collections
import concurrent.futures
import hashlib
import os
import pickle
import re
import subprocess
import sys
import tempfile
import time
import warnings
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TOOL_VERSION = 14
CACHE_DIR = ROOT / "build" / "ms_header_audit"
QUEUE = ROOT / "reverse" / "ms_header_queue.tsv"
OCCURRENCES = CACHE_DIR / "occurrences.tsv"
DEFAULT_VC71 = (ROOT / "reference" / "open-bfme-1" / "inputs" / "toolchains" / "vs2003"
                / "Program Files" / "Microsoft Visual Studio .NET 2003")

SCAN_PREFIXES = ("Code/", "reference/shims/", "vendor/stlport/")
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inl", ".inc"}
HEADER_SUFFIXES = {".h", ".hh", ".hpp", ".hxx", ".inl", ""}


# seconds one file's analysis (its include closure included) may take; past
# it the file's result is an explicit failure, never an empty occurrence list
FILE_TIMEOUT = float(os.environ.get("MS_HEADER_FILE_TIMEOUT", "60"))


class AnalysisIncomplete(Exception):
    """A file's analysis ran out of time: its result is unknown."""


_DEADLINE = [None, 0]  # monotonic deadline, tick counter


def _tick():
    _DEADLINE[1] += 1
    if _DEADLINE[1] & 1023 == 0 and _DEADLINE[0] is not None and time.monotonic() > _DEADLINE[0]:
        raise AnalysisIncomplete("timeout")


def vc71_root():
    return Path(os.environ.get("VC71_ROOT", DEFAULT_VC71))


def default_roots():
    vc = vc71_root()
    return [("Vc7/include", vc / "Vc7" / "include"),
            ("Vc7/PlatformSDK/Include", vc / "Vc7" / "PlatformSDK" / "Include")]


def parse_root_args(values):
    roots = []
    for value in values or []:
        label, sep, path = value.partition("=")
        if not sep:
            path, label = value, Path(value).name
        roots.append((label, Path(path) if Path(path).is_absolute() else ROOT / path))
    env = os.environ.get("MS_HEADER_EXTRA_ROOTS")
    if env:
        for part in env.split(os.pathsep):
            if part:
                roots.extend(parse_root_args([part]))
    return roots


# --------------------------------------------------------------------------
# Tokenizer
# --------------------------------------------------------------------------

_SKIP = re.compile(r"(?:[ \t\r\f\v]+|//[^\n]*|/\*.*?\*/|\\\r?\n)+", re.S)
_TOK = re.compile(r"""(?P<I>[A-Za-z_$][A-Za-z0-9_$]*)
                     |(?P<N>\.?[0-9](?:[eEpP][+-]|[A-Za-z0-9_.])*)
                     |(?P<S>L?"(?:\\.|[^"\\\n])*")
                     |(?P<C>L?'(?:\\.|[^'\\\n])*')
                     |(?P<P>::|\.\.\.|->|\#\#|[^\s])""", re.S | re.X)
_DIRECTIVE = re.compile(r"(?:/\*.*?\*/|//[^\n]*|\\\r?\n|[^\n])*", re.S)
_LINE_DIRECTIVE = re.compile(r'#\s*(?:line\s+)?(\d+)\s+"((?:\\.|[^"\\])*)"')


class Toks:
    """Parallel token arrays: S text, K kind (I N S C P D), L line, F file id."""
    __slots__ = ("S", "K", "L", "F", "files")

    def __init__(self):
        self.S, self.K, self.L, self.F = [], [], [], []
        self.files = []

    def add(self, kind, text, line, fid):
        self.K.append(kind)
        self.S.append(text)
        self.L.append(line)
        self.F.append(fid)


def tokenize(text, line_directives=False, toks=None, fid=0):
    """Tokens of C/C++ text. Directives become one D token each; with
    `line_directives`, `#line N "file"` switch the file id instead."""
    toks = toks or Toks()
    if not toks.files:
        toks.files.append("")
    file_ids = {name: index for index, name in enumerate(toks.files)}
    pos, n, line, delta, bol = 0, len(text), 1, 0, True
    skip_match, tok_match = _SKIP.match, _TOK.match
    while pos < n:
        _tick()
        m = skip_match(text, pos)
        if m:
            seg = m.group()
            if "\n" in seg:
                line += seg.count("\n")
                bol = True
            pos = m.end()
            continue
        ch = text[pos]
        if ch == "\n":
            line += 1
            pos += 1
            bol = True
            continue
        if ch == "#" and bol:
            m = _DIRECTIVE.match(text, pos)
            directive = m.group()
            pos = m.end()
            if line_directives:
                lm = _LINE_DIRECTIVE.match(directive)
                if lm:
                    name = lm.group(2).replace("\\\\", "\\")
                    if name not in file_ids:
                        file_ids[name] = len(toks.files)
                        toks.files.append(name)
                    fid = file_ids[name]
                    delta = int(lm.group(1)) - (line + 1)
                    line += directive.count("\n")
                    continue
            toks.add("D", directive, line + delta, fid)
            line += directive.count("\n")
            continue
        m = tok_match(text, pos)
        toks.add(m.lastgroup, m.group(), line + delta, fid)
        pos = m.end()
        bol = False
    return toks


# --------------------------------------------------------------------------
# Directives: macros, conditionals, packing
# --------------------------------------------------------------------------

_DEFINE = re.compile(r"#\s*define\s+([A-Za-z_]\w*)(\([^)]*\))?(.*)", re.S)
_COMMENTS = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


def directive_words(text):
    body = _COMMENTS.sub(" ", text).replace("\\\r\n", " ").replace("\\\n", " ")
    m = re.match(r"#\s*(\w*)\s*(.*)", body, re.S)
    return (m.group(1), m.group(2).strip()) if m else ("", "")


def parse_define(text):
    body = _COMMENTS.sub(" ", text).replace("\\\r\n", " ").replace("\\\n", " ")
    m = _DEFINE.match(body)
    if not m:
        return None
    params = None
    if m.group(2) is not None:
        params = tuple(p.strip() for p in m.group(2)[1:-1].split(",") if p.strip())
    rep = tokenize(m.group(3))
    return m.group(1), params, tuple(zip(rep.K, rep.S))


def pack_directive(text):
    """`#pragma pack(...)` as ('push', N|None) / ('pop', None) / ('set', N|None)."""
    kind, rest = directive_words(text)
    if kind != "pragma":
        return None
    m = re.match(r"pack\s*\((.*)\)", rest)
    if not m:
        return None
    args = [a.strip() for a in m.group(1).split(",") if a.strip()]
    nums = [int(a) for a in args if a.isdigit()]
    if args and args[0] == "push":
        return ("push", nums[0] if nums else None)
    if args and args[0] == "pop":
        return ("pop", None)
    return ("set", nums[0] if nums else None)


_GUARD_EXPR = re.compile(r"!\s*defined\s*\(?\s*(\w+)\s*\)?")


def _expr_idents(expr):
    toks = tokenize(expr)
    return {s for k, s in zip(toks.K, toks.S) if k == "I" and s != "defined"}


def guard_inputs(toks):
    """Names a header's conditionals test to select definitions: every
    identifier an #if/#elif expression or an #ifdef/#ifndef group reads,
    except a group whose first branch #defines the tested name itself (an
    include guard, `_SIZE_T_DEFINED`, `#ifndef TRUE / #define TRUE 1`). A
    local definition of one changes what the headers declare after it."""
    out = set()
    stack = []  # [tested names, guard name, guard defined in first branch, branch]
    for kind, s in zip(toks.K, toks.S):
        if kind != "D":
            continue
        word, rest = directive_words(s)
        if word in ("ifdef", "ifndef"):
            name = rest.split()[0] if rest.split() else ""
            stack.append([{name}, name, False, 0])
        elif word == "if":
            m = _GUARD_EXPR.fullmatch(rest.strip()) or re.fullmatch(r"defined\s*\(?\s*(\w+)\s*\)?", rest.strip())
            stack.append([_expr_idents(rest), m.group(1) if m else None, False, 0])
        elif word in ("elif", "else") and stack:
            stack[-1][3] += 1
            if word == "elif":
                out |= _expr_idents(rest)
        elif word == "endif" and stack:
            names, guard, defined, _ = stack.pop()
            out |= names if not (guard and defined) else names - {guard}
        elif word == "define" and stack:
            # nested too: `#ifndef NULL / #ifdef __cplusplus / #define NULL 0`
            name = rest.split("(")[0].split()[0] if rest.split() else ""
            for frame in stack:
                if frame[3] == 0 and name == frame[1]:
                    frame[2] = True
    for names, guard, defined, _ in stack:  # unterminated groups
        out |= names
    return out - FIXED_IDENTS


_INT_LIT = re.compile(r"(0[xX][0-9a-fA-F]+|[0-9]+)[uUlL]*$")


def eval_int(tokens):
    """Integer value of a constant expression's tokens, or None."""
    parts = []
    for t in tokens:
        m = _INT_LIT.match(t)
        if m:
            lit = m.group(1)
            parts.append(str(int(lit, 16) if lit[:2] in ("0x", "0X")
                             else int(lit, 8) if len(lit) > 1 and lit[0] == "0" else int(lit)))
        elif t in ("+", "-", "*", "/", "%", "(", ")", "<", ">", "=", "!", "&", "|", "^", "~", "?", ":"):
            parts.append(t)
        elif t in ("<<", ">>", "==", "!=", "<=", ">=", "&&", "||"):
            parts.append(t)
        else:
            return None
    expr = " ".join(parts)
    expr = re.sub(r"(?<![=!<>])!(?!=)", " not ", expr)
    expr = expr.replace("& &", "and").replace("| |", "or").replace("&&", " and ").replace("||", " or ")
    expr = re.sub(r"(?<![<>=!])= =", "==", expr).replace("< <", "<<").replace("> >", ">>")
    expr = re.sub(r"(?<![<>=!])= ?=", "==", expr).replace("! =", "!=").replace("< =", "<=").replace("> =", ">=")
    expr = expr.replace("/", "//") if "?" not in expr else expr
    if "?" in expr:
        return None
    try:
        with warnings.catch_warnings():  # "1 (2)" warns before it fails
            warnings.simplefilter("ignore", SyntaxWarning)
            value = eval(expr, {"__builtins__": {}}, {})  # noqa: S307 - digits/operators only
    except Exception:
        return None
    if isinstance(value, bool):
        value = int(value)
    return value if isinstance(value, int) else None


# predefined for every unit of one language: a nested #if on these alone
# selects nothing a unit's configuration could change
FIXED_IDENTS = {"__cplusplus", "_MSC_VER", "_MSC_FULL_VER", "_M_IX86", "_WIN32", "__STDC__",
                "_INTEGRAL_MAX_BITS", "_MSC_EXTENSIONS"}


def preprocess(toks, defines=None, evaluate=True, maybe=None, info=None):
    """Drop inactive #if regions (only `#if 0` regions when not `evaluate`),
    collect #define/#undef and includes, and turn `#pragma pack` and
    pshpack/poppack includes into P-tokens the parser reads.

    Conditions evaluate tri-state (cond_value): one that does not reduce to
    an integer, or one that tests a name in `maybe` (macros an include may
    define) after the first #include, is uncertain. The C reading (undefined
    is 0) picks the branch; `info`, when given, receives "hard" [(line, expr)]
    for uncertain groups whose outcome can change other code, "soft"
    [(line, name)] for the `#ifndef X / #define X / #endif` default idiom,
    and "assumed": names taken as undefined after an #include.

    Returns (Toks of active code, macros {name: [(params, body, line)]},
    includes [(line, name, angled)])."""
    defines = dict(defines or {})
    info = info if info is not None else {}
    hard, soft, assumed = info.setdefault("hard", []), info.setdefault("soft", []), info.setdefault("assumed", set())
    out = Toks()
    out.files = toks.files
    macros = collections.defaultdict(list)
    includes = []
    stack = []  # (active, taken, parent_active)
    frames = []  # per group: [uncertain, guard name, other content, line, expr]
    seen_include = False
    active = True

    def evaluate_cond(word, rest):
        """(value, uncertain) of an active conditional under `defines`."""
        if word in ("ifdef", "ifndef"):
            name = rest.split()[0] if rest.split() else ""
            present = name in defines
            idents, value = ({name} if not present else set()), (present if word == "ifdef" else not present)
        else:
            v = cond_value(rest, defines)
            if v is None:
                return False, True
            idents = {x for x in _expr_idents(rest) if x not in defines}
            value = v
        if not seen_include:
            return value, False
        assumed.update(idents)
        return value, bool(maybe is not None and any(x in maybe for x in idents))

    for i in range(len(toks.S)):
        kind = toks.K[i]
        if kind != "D":
            if frames:
                for f in frames:
                    f[2] = True
            if active:
                out.add(kind, toks.S[i], toks.L[i], toks.F[i])
            continue
        text = toks.S[i]
        word, rest = directive_words(text)
        if frames and word not in ("if", "ifdef", "ifndef", "elif", "else", "endif"):
            name = rest.split("(")[0].split()[0] if word in ("define", "undef") and rest.split() else None
            for f in frames:
                if name is None or name != f[1]:
                    f[2] = True
        if word in ("if", "ifdef", "ifndef"):
            nested = {rest.split()[0]} if word != "if" and rest.split() else _expr_idents(rest)
            for f in frames:
                if not nested <= FIXED_IDENTS | {f[1]}:
                    f[2] = True
            guard = (rest.split()[0] if rest.split() else None) if word == "ifndef" else None
            if word == "if":
                m = _GUARD_EXPR.fullmatch(rest.strip())
                guard = m.group(1) if m else None
            frames.append([False, guard, False, toks.L[i], f"#{word} {rest}"])
            if not active:
                stack.append((False, True, False))
                continue
            if not evaluate:
                cond = not re.fullmatch(r"0+", rest.strip()) if word == "if" else True
            else:
                cond, frames[-1][0] = evaluate_cond(word, rest)
            stack.append((cond, cond, True))
            active = cond
        elif word in ("elif", "else"):
            if frames and word == "elif" and not _expr_idents(rest) <= FIXED_IDENTS | {frames[-1][1]}:
                frames[-1][2] = True
            if not stack:
                continue
            was, taken, parent = stack.pop()
            if not parent:
                stack.append((False, True, False))
                active = False
                continue
            if not evaluate:
                cond = True
                if word == "elif" and re.fullmatch(r"0+", rest.strip()):
                    cond = False
                stack.append((cond, True, True))
                active = cond
                continue
            cond = not taken
            if cond and word == "elif":
                cond, uncertain = evaluate_cond("if", rest)
                if uncertain and frames:
                    frames[-1][0] = True
                    frames[-1][1] = None  # an #elif outcome is no default idiom
            stack.append((cond, taken or cond, True))
            active = cond
        elif word == "endif":
            if stack:
                stack.pop()
            if frames:
                f = frames.pop()
                if f[0]:
                    if f[1] and not f[2]:
                        soft.append((f[3], f[1]))
                    else:
                        hard.append((f[3], f[4]))
                if frames and f[0]:
                    frames[-1][2] = True
            active = all(entry[0] for entry in stack)
        elif not active:
            continue
        elif word == "define":
            parsed = parse_define(text)
            if parsed:
                name, params, body = parsed
                macros[name].append((params, body, toks.L[i]))
                if params is None:
                    defines[name] = " ".join(s for _, s in body)
                else:
                    defines.setdefault(name, "")
        elif word == "undef":
            name = rest.split()[0] if rest.split() else ""
            defines.pop(name, None)
        elif word == "include":
            seen_include = True
            m = re.match(r'[<"]([^>"]+)[>"]', rest)
            if m:
                header = m.group(1).replace("\\", "/")
                includes.append((toks.L[i], header, rest.startswith("<")))
                base = header.rsplit("/", 1)[-1].lower()
                pm = re.fullmatch(r"pshpack(\d+)\.h", base)
                if pm:
                    out.add("D", f"#pragma pack(push, {pm.group(1)})", toks.L[i], toks.F[i])
                elif base == "poppack.h":
                    out.add("D", "#pragma pack(pop)", toks.L[i], toks.F[i])
        elif word == "pragma":
            if pack_directive(text):
                out.add("D", text, toks.L[i], toks.F[i])
    return out, dict(macros), includes


# --------------------------------------------------------------------------
# Macro expansion
# --------------------------------------------------------------------------

def _collect_args(S, i, end):
    """Arguments of a macro call whose '(' is at S[i]: (args, index after ')')."""
    depth, args, cur = 0, [], []
    j = i + 1
    while j < end:
        s = S[j]
        if s in ("(", "[", "{"):
            depth += 1
        elif s in (")", "]", "}"):
            if depth == 0:
                args.append(cur)
                return args, j + 1
            depth -= 1
        elif s == "," and depth == 0:
            args.append(cur)
            cur = []
            j += 1
            continue
        cur.append(j)
        j += 1
    return None, i + 1


def expand(toks, lookup, max_steps=200000):
    """Toks with macros replaced. `lookup(name, in_ms_body)` gives
    (params, body[(kind, text)], is_ms) or None. Nested expansions keep the
    line and file of the token they replace."""
    out = Toks()
    out.files = toks.files
    work = list(zip(toks.K, toks.S, toks.L, toks.F, [frozenset()] * len(toks.S), [False] * len(toks.S)))
    work.reverse()
    steps = 0
    while work:
        _tick()
        kind, text, line, fid, hide, in_ms = work.pop()
        if kind == "I" and text not in hide and steps < max_steps:
            m = lookup(text, in_ms)
            if m:
                params, body, is_ms = m
                if params is None:
                    steps += 1
                    rep = [(k, s, line, fid, hide | {text}, is_ms) for k, s in _paste(list(body))]
                    work.extend(reversed(rep))
                    continue
                # function-like: need '(' next
                if work and work[-1][1] == "(":
                    flat = [work.pop()]
                    depth = 1
                    while work and depth:
                        item = work.pop()
                        flat.append(item)
                        if item[1] in ("(", "[", "{"):
                            depth += 1
                        elif item[1] in (")", "]", "}"):
                            depth -= 1
                    if depth:
                        work.extend(reversed(flat))
                    else:
                        steps += 1
                        S = [f[1] for f in flat]
                        args, _ = _collect_args(S, 0, len(S))
                        args = [[(flat[j][0], flat[j][1]) for j in arg] for arg in (args or [])]
                        rep = _substitute(params, body, args)
                        work.extend(reversed([(k, s, line, fid, hide | {text}, is_ms) for k, s in rep]))
                        continue
        out.add(kind, text, line, fid)
    return out


def _paste(body):
    out = []
    i = 0
    while i < len(body):
        if body[i][1] == "##" and out and i + 1 < len(body):
            prev = out.pop()
            glued = prev[1] + body[i + 1][1]
            out.append(("I" if re.fullmatch(r"\w+", glued) else prev[0], glued))
            i += 2
            continue
        out.append(body[i])
        i += 1
    return out


def _substitute(params, body, args):
    params = list(params)
    variadic = params and params[-1] == "..."
    index = {p: k for k, p in enumerate(params)}
    if variadic:
        index["__VA_ARGS__"] = len(params) - 1
    out = []
    body = list(body)
    i = 0
    while i < len(body):
        kind, text = body[i]
        if text == "#" and i + 1 < len(body) and body[i + 1][1] in index:
            k = index[body[i + 1][1]]
            arg = args[k] if k < len(args) else []
            out.append(("S", '"' + " ".join(s for _, s in arg) + '"'))
            i += 2
            continue
        if kind == "I" and text in index:
            k = index[text]
            if variadic and k == len(params) - 1:
                arg = []
                for n, extra in enumerate(args[k:]):
                    if n:
                        arg.append(("P", ","))
                    arg.extend(extra)
            else:
                arg = args[k] if k < len(args) else []
            out.extend(arg)
            i += 1
            continue
        out.append((kind, text))
        i += 1
    return _paste(out)


# --------------------------------------------------------------------------
# Declaration parser
# --------------------------------------------------------------------------

CLASS_KEYS = {"struct", "class", "union", "enum"}
CALLCONV = {"__stdcall": "__stdcall", "_stdcall": "__stdcall", "__cdecl": "__cdecl", "_cdecl": "__cdecl",
            "__fastcall": "__fastcall", "_fastcall": "__fastcall", "__thiscall": "__thiscall",
            "__pascal": "__stdcall", "_pascal": "__stdcall", "__clrcall": "__clrcall"}
STORAGE = {"extern", "static", "inline", "__inline", "_inline", "__forceinline", "register", "auto",
           "virtual", "friend", "mutable", "explicit", "typedef", "_W64", "__w64", "__ptr32", "__ptr64",
           "__unaligned", "_unaligned", "__restrict", "__sptr", "__uptr", "__nogc", "__gc", "__value",
           "__abstract", "__sealed", "__interface"}
BUILTIN = {"signed", "unsigned", "short", "long", "int", "char", "__int8", "__int16", "__int32", "__int64",
           "float", "double", "bool", "void", "wchar_t", "__wchar_t", "const", "volatile"}
KEYWORDS = BUILTIN | CLASS_KEYS | set(CALLCONV) | STORAGE | {
    "operator", "template", "typename", "namespace", "using", "return", "if", "else", "for", "while",
    "do", "switch", "case", "default", "sizeof", "new", "delete", "throw", "try", "catch", "public",
    "private", "protected", "this", "true", "false", "goto", "break", "continue", "asm", "__asm",
    "__declspec", "_declspec", "__pragma", "static_cast", "const_cast", "reinterpret_cast",
    "dynamic_cast", "typeid", "__alignof", "__uuidof", "__if_exists", "__if_not_exists", "__event",
    "__hook", "__unhook", "__raise", "__super", "__identifier", "__based", "__try", "__except",
    "__finally", "__leave"}
_ATTRISH = re.compile(r"(?:__declspec|_declspec|__pragma|DECLSPEC_\w+|[A-Z][A-Z0-9_]{2,})$")


def _match_table(S):
    """match[i] = index of the bracket closing the one opened at i (or the
    reverse), -1 when unmatched."""
    match = [-1] * len(S)
    stack = []
    pairs = {")": "(", "]": "[", "}": "{"}
    for i, s in enumerate(S):
        if s in ("(", "[", "{"):
            stack.append(i)
        elif s in pairs:
            want = pairs[s]
            k = len(stack) - 1
            while k >= 0 and S[stack[k]] != want:
                k -= 1
            if k < 0:
                continue
            j = stack[k]
            del stack[k:]
            match[i], match[j] = j, i
    return match


def _strip_attrs(seq):
    """Remove __declspec(...)-style groups from a token list; returns
    (tokens, attribute texts)."""
    out, attrs = [], []
    i, n = 0, len(seq)
    while i < n:
        s = seq[i]
        if s in ("__declspec", "_declspec", "__pragma") and i + 1 < n and seq[i + 1] == "(":
            j = _close(seq, i + 1)
            attrs.append(" ".join(seq[i + 2:j]))
            i = j + 1
            continue
        if (_ATTRISH.match(s) and i + 1 < n and seq[i + 1] == "(" and s not in KEYWORDS):
            j = _close(seq, i + 1)
            nxt = seq[j + 1] if j + 1 < n else ""
            if nxt and (re.match(r"[A-Za-z_]", nxt) and nxt not in ("const", "throw", "volatile")):
                attrs.append(s + "(" + " ".join(seq[i + 2:j]) + ")")
                i = j + 1
                continue
        out.append(s)
        i += 1
    return out, attrs


def _close(seq, i):
    depth = 0
    for j in range(i, len(seq)):
        if seq[j] in ("(", "[", "{"):
            depth += 1
        elif seq[j] in (")", "]", "}"):
            depth -= 1
            if depth == 0:
                return j
    return len(seq) - 1


def _split_top(seq, sep=","):
    parts, cur, depth, angle = [], [], 0, 0
    for k, s in enumerate(seq):
        if s in ("(", "[", "{"):
            depth += 1
        elif s in (")", "]", "}"):
            depth -= 1
        elif s == "<" and depth == 0 and k and re.match(r"\w", seq[k - 1]) and seq[k - 1] not in KEYWORDS:
            angle += 1
        elif s == ">" and depth == 0 and angle:
            angle -= 1
        elif s == sep and depth == 0 and angle == 0:
            parts.append(cur)
            cur = []
            continue
        cur.append(s)
    parts.append(cur)
    return parts


def _is_ident(s):
    return bool(s) and (s[0].isalpha() or s[0] in "_$") and s not in KEYWORDS


def find_declarator(seq):
    """(name, type tokens without the name, function?, params, after) for one
    declaration's tokens with attributes already stripped. name is None for an
    abstract declarator."""
    n = len(seq)
    # operator names
    if "operator" in seq:
        k = seq.index("operator")
        if k + 2 < n and seq[k + 1] == "(" and seq[k + 2] == ")":
            p = k + 3
        else:
            p = k + 1
            while p < n and seq[p] != "(":
                p += 1
        if p < n and seq[p] == "(":
            words = seq[k + 1:p]
            name = "operator" + ((" " + " ".join(words)) if words and re.match(r"\w", words[0])
                                 else "".join(words))
            q = _close(seq, p)
            start = k
            while start >= 2 and seq[start - 1] == "::" and _is_ident(seq[start - 2]):
                start -= 2
            qual = "".join(seq[start:k]) if start < k else ""
            return qual + name, seq[:start] + seq[q + 1:], True, seq[p + 1:q], seq[q + 1:]
    i = 0
    while i < n:
        s = seq[i]
        if s == "(":
            j = _close(seq, i)
            inner = [t for t in seq[i + 1:j] if t not in CALLCONV]
            prev = seq[i - 1] if i else None
            nested = bool(inner) and (inner[0] in ("*", "&", "^") or
                                      (len(inner) > 2 and inner[1] == "::" and "*" in inner))
            if not nested and prev is not None and _is_ident(prev):
                start = i - 1
                if start >= 1 and seq[start - 1] == "~":
                    start -= 1
                while start >= 2 and seq[start - 1] == "::" and (_is_ident(seq[start - 2]) or seq[start - 2] == ">"):
                    if seq[start - 2] == ">":
                        depth, k = 0, start - 2
                        while k >= 0:
                            if seq[k] == ">":
                                depth += 1
                            elif seq[k] == "<":
                                depth -= 1
                                if depth == 0:
                                    break
                            k -= 1
                        start = k - 1 if k >= 1 else 0
                    else:
                        start -= 2
                name = "".join(seq[start:i])
                return name, seq[:start] + seq[j + 1:], True, seq[i + 1:j], seq[j + 1:]
            if nested or prev is None or not _is_ident(prev):
                idents = [k for k in range(i + 1, j) if _is_ident(seq[k])]
                if idents:
                    k = idents[-1]
                    rest = seq[:k] + seq[k + 1:]
                    return seq[k], rest, False, None, seq[j + 1:]
                i = j + 1
                continue
        if s in ("[", "="):
            break
        i += 1
    # plain: the last identifier before '[' / '=' / end
    stop = i
    for k in range(stop - 1, -1, -1):
        if _is_ident(seq[k]) and not (k and seq[k - 1] in CLASS_KEYS):
            if k and seq[k - 1] == "::":
                return None, seq, False, None, []
            return seq[k], seq[:k] + seq[k + 1:stop], False, None, seq[stop:]
    return None, seq[:stop], False, None, seq[stop:]


def split_params(params):
    """[(type tokens, name)] of a parameter list; ('...',) marks variadic."""
    if params is None:
        return None, False
    seq = [p for p in params]
    if not seq or seq == ["void"]:
        return [], False
    out, variadic = [], False
    for part in _split_top(seq):
        if not part:
            continue
        if part == ["..."]:
            variadic = True
            continue
        part, _ = _strip_attrs(part)
        if "=" in part:
            part = part[:part.index("=")]
        name, rest, func, sub, after = find_declarator(part)
        if name is None:
            rest = part
        elif len([t for t in part if t not in ("const", "volatile")]) == 1:
            rest = part  # a lone identifier is a type name
        elif func:  # function-typed parameter -> pointer
            rest = part
        if "[" in rest:
            k = rest.index("[")
            rest = rest[:k] + ["*"]
        out.append(rest)
    return out, variadic


class Decl:
    __slots__ = ("name", "kind", "line", "fid", "linkage", "tmpl", "d")

    def __init__(self, name, kind, line, fid, linkage, tmpl, d):
        self.name, self.kind, self.line, self.fid = name, kind, line, fid
        self.linkage, self.tmpl, self.d = linkage, tmpl, d

    def __repr__(self):
        return f"Decl({self.name!r}, {self.kind}, line {self.line})"


class Parser:
    def __init__(self, toks, lang="cpp", default_pack=8):
        self.t = toks
        self.S = toks.S
        self.n = len(toks.S)
        self.match = _match_table(toks.S)
        self.lang = lang
        self.decls = []
        self.pack = default_pack
        self.pack_stack = []
        self.default_pack = default_pack

    # -- helpers ----------------------------------------------------------
    def pragma(self, i):
        p = pack_directive(self.S[i])
        if not p:
            return
        op, value = p
        if op == "push":
            self.pack_stack.append(self.pack)
            if value:
                self.pack = value
        elif op == "pop":
            self.pack = self.pack_stack.pop() if self.pack_stack else self.default_pack
        else:
            self.pack = value or self.default_pack

    def emit(self, name, kind, i, ns, linkage, tmpl, d):
        if not name:
            return
        q = "::".join(ns + [name]) if ns else name
        self.decls.append(Decl(q, kind, self.t.L[i], self.t.F[i], linkage, tmpl, d))

    def group_end(self, i):
        j = self.match[i]
        return j if j > i else i

    # -- scopes -----------------------------------------------------------
    def parse(self):
        i = 0
        while i < self.n:
            i = self.scope(i, [], "C++" if self.lang == "cpp" else "C", top=True)
        return self.decls

    def scope(self, i, ns, linkage, top=False):
        S, K, n = self.S, self.t.K, self.n
        while i < n:
            _tick()
            s = S[i]
            if K[i] == "D":
                self.pragma(i)
                i += 1
                continue
            if s == "}":
                return i + 1
            if s == ";":
                i += 1
                continue
            if s == "extern" and i + 1 < n and K[i + 1] == "S" and S[i + 1] in ('"C"', '"C++"'):
                link = "C" if S[i + 1] == '"C"' else "C++"
                if i + 2 < n and S[i + 2] == "{":
                    i = self.scope(i + 3, ns, link)
                    continue
                i = self.declaration(i + 2, ns, link, False)
                continue
            if s == "namespace":
                j = i + 1
                name = []
                while j < n and S[j] not in ("{", ";", "="):
                    name.append(S[j])
                    j += 1
                if j < n and S[j] == "{":
                    i = self.scope(j + 1, ns + ["".join(name) or "(anon)"], linkage)
                else:
                    while j < n and S[j] != ";":
                        j += 1
                    i = j + 1
                continue
            if s in ("using", "static_assert"):
                while i < n and S[i] != ";":
                    i = self.group_end(i) + 1 if S[i] in ("(", "{", "[") else i + 1
                i += 1
                continue
            if s in ("__pragma", "__if_exists", "__if_not_exists") and i + 1 < n and S[i + 1] == "(":
                i = self.group_end(i + 1) + 1
                if s != "__pragma" and i < n and S[i] == "{":
                    i = self.group_end(i) + 1
                continue
            if s == "template":
                j = i + 1
                if j < n and S[j] == "<":
                    explicit = j + 1 < n and S[j + 1] == ">"
                    j = self.skip_angles(j)
                    i = self.declaration(j, ns, linkage, True, record=not explicit)
                else:  # explicit instantiation
                    while j < n and S[j] != ";":
                        j += 1
                    i = j + 1
                continue
            i = self.declaration(i, ns, linkage, False)
        return i

    def skip_angles(self, i):
        S, n = self.S, self.n
        depth = 0
        while i < n:
            s = S[i]
            if s == "<":
                depth += 1
            elif s == ">":
                depth -= 1
                if depth == 0:
                    return i + 1
            elif s in ("(", "["):
                i = self.group_end(i)
            elif s in (";", "{", "}"):
                return i
            i += 1
        return i

    def declaration(self, i, ns, linkage, tmpl, record=True):
        S, K, n = self.S, self.t.K, self.n
        start = i
        head = []
        seen_eq = False
        while i < n:
            s = S[i]
            if K[i] == "D":
                self.pragma(i)
                i += 1
                continue
            if s == ";":
                if record:
                    self.simple(head, start, ns, linkage, tmpl)
                return i + 1
            if s == "}":
                return i  # stray: let the scope close
            if s == "{":
                if seen_eq or (head and head[-1] in ("=", ",") and seen_eq):
                    j = self.group_end(i)
                    head.extend(["{", "}"])
                    i = j + 1
                    continue
                return self.body(head, start, i, ns, linkage, tmpl, record)
            if s in ("(", "["):
                j = self.group_end(i)
                if j == i:
                    head.append(s)
                    i += 1
                    continue
                head.extend(S[i:j + 1])
                i = j + 1
                continue
            if s == "=":
                seen_eq = True
            head.append(s)
            i += 1
        return i

    def class_spec(self, head):
        """(key index, key, tag, bases) when `head` (tokens before '{') is a
        class-specifier, else None."""
        seq, _ = _strip_attrs(head)
        for k, s in enumerate(seq):
            if s in CLASS_KEYS:
                rest = seq[k + 1:]
                if "(" in rest:
                    return None
                if any(t in ("=",) for t in seq[:k]):
                    return None
                tag = None
                bases = []
                if rest:
                    m = rest.index(":") if ":" in rest else len(rest)
                    name_toks = [t for t in rest[:m] if t not in ("final", "sealed")]
                    tag = "".join(name_toks) or None
                    if m < len(rest):
                        bases = [[t for t in b if t not in ("public", "private", "protected", "virtual")]
                                 for b in _split_top(rest[m + 1:])]
                return k, s, tag, bases
            if s in ("(",):
                return None
        return None

    def body(self, head, start, i, ns, linkage, tmpl, record):
        S, n = self.S, self.n
        end = self.group_end(i)
        if end == i:
            return i + 1
        spec = self.class_spec(head)
        if spec:
            k, key, tag, bases = spec
            stripped, attrs = _strip_attrs(head)
            if key == "enum":
                members = self.enumerators(i + 1, end)
            else:
                members = self.members(i + 1, end, ns + [tag] if tag else ns)
            pack = self.pack
            j = end + 1
            tail = []
            while j < n and S[j] != ";":
                if S[j] == "{" or S[j] == "(":
                    jj = self.group_end(j)
                    tail.extend(S[j:jj + 1])
                    j = jj + 1
                    continue
                if S[j] == "}":
                    break
                tail.append(S[j])
                j += 1
            is_typedef = "typedef" in stripped[:stripped.index(key)] if key in stripped else False
            declarators = []
            if tail:
                for part in _split_top(tail):
                    if "=" in part:
                        part = part[:part.index("=")]
                    name, rest, func, params, after = find_declarator(part)
                    if name:
                        declarators.append((name, rest))
            anon = tag is None
            if anon and declarators:
                tag = "<anon:%s>" % declarators[0][0]
            uuid = next((a for a in attrs if a.startswith("uuid")), None)
            align = next((re.sub(r"\s+", "", a) for a in attrs if re.match(r"align\b", a)), None)
            detail = {"key": key, "members": members, "pack": pack, "bases": bases, "anon": anon,
                      "uuid": uuid}
            if align:
                detail["align"] = align
            if record and tag:
                kind = "enum" if key == "enum" else key
                self.emit(tag, kind, start, ns, linkage, tmpl, detail)
                if key == "enum":
                    for ename, value in members:
                        self.emit(ename, "enumerator", start, ns, linkage, False,
                                  {"value": value, "enum": tag})
            if record:
                for name, rest in declarators:
                    type_toks = [key, tag or "?"] + [t for t in rest if t not in ("typedef",)]
                    if is_typedef:
                        self.emit(name, "typedef", start, ns, linkage, tmpl,
                                  {"type": type_toks, "tag": tag})
                    else:
                        self.emit(name, "var", start, ns, linkage, tmpl,
                                  {"type": type_toks, "dllimport": any("dllimport" in a for a in attrs)})
            return j + 1 if j < n and S[j] == ";" else j
        # function definition?
        seq, attrs = _strip_attrs(head)
        if seq and seq[0] == "extern" and False:
            pass
        name, rest, func, params, after = find_declarator(seq)
        if func and name and record:
            self.emit_function(name, rest, params, attrs, start, ns, linkage, tmpl,
                               body=self.body_hash(i, end, params))
        j = end + 1
        return j

    def body_hash(self, i, end, params):
        """Digest of a function body's tokens S[i..end], parameters renamed to
        their positions: two bodies are proven identical only when equal."""
        rename = {}
        for k, part in enumerate(_split_top(list(params or []))):
            name = find_declarator(_strip_attrs(part)[0])[0] if part else None
            if name and _is_ident(name):
                rename[name] = f"__MSA_P{k}__"
        text = " ".join(rename.get(s, s) for s in self.S[i:end + 1])
        return hashlib.sha1(text.encode("latin-1", "replace")).hexdigest()

    def emit_function(self, name, rest, params, attrs, i, ns, linkage, tmpl, body=False):
        cc = None
        ret = []
        for t in rest:
            if t in CALLCONV:
                cc = cc or CALLCONV[t]
                continue
            if t in ("const", "throw") and ret is None:
                break
            ret.append(t)
        # trailing qualifiers after the parameter list belong to rest's tail
        flags = set(t for t in rest if t in STORAGE)
        ptypes, variadic = split_params(params)
        ret_clean = [t for t in ret if t not in STORAGE]
        # The exception contract is not part of the return type, but /EHsc
        # uses it even for extern-C declarations when deciding unwind cleanup.
        throws = None
        if "throw" in ret_clean:
            k = ret_clean.index("throw")
            if k + 1 < len(ret_clean) and ret_clean[k + 1] == "(":
                throws = ret_clean[k + 2:_close(ret_clean, k + 1)]
            ret_clean = ret_clean[:k]
        detail = {"ret": ret_clean, "params": ptypes, "variadic": variadic, "cc": cc,
                  "throws": throws,
                  "dllimport": any("dllimport" in a for a in attrs), "body": body,
                  "inline": bool(flags & {"inline", "__inline", "_inline", "__forceinline"}),
                  "static": "static" in flags}
        if "::" in name and not name.startswith("operator"):
            return  # out-of-line member definition
        self.emit(name, "function", i, ns, linkage, tmpl, detail)

    def simple(self, head, start, ns, linkage, tmpl):
        if not head:
            return
        seq, attrs = _strip_attrs(head)
        if not seq:
            return
        if seq[0] == "extern" and len(seq) > 1 and seq[1] in ('"C"', '"C++"'):
            linkage = "C" if seq[1] == '"C"' else "C++"
            seq = seq[2:]
        if not seq:
            return
        if seq[0] in ("using", "namespace", "asm", "__asm", "friend", "return"):
            return
        # forward declaration: [typedef?] key Name ;
        if len(seq) >= 2 and seq[0] in CLASS_KEYS and all(_is_ident(t) or t == "::" for t in seq[1:]) \
                and "typedef" not in seq:
            self.emit("".join(seq[1:]), "fwd", start, ns, linkage, tmpl, {"key": seq[0]})
            return
        is_typedef = "typedef" in seq
        if is_typedef:
            seq = [t for t in seq if t != "typedef"]
        parts = _split_top(seq)
        first = parts[0]
        name, rest, func, params, after = find_declarator(first)
        if name is None:
            return
        spec_len = self._spec_len(first, name)
        spec = first[:spec_len]
        for index, part in enumerate(parts):
            if index:
                part = spec + part
                name, rest, func, params, after = find_declarator(part)
                if name is None:
                    continue
            if "=" in rest:
                rest = rest[:rest.index("=")]
            if is_typedef:
                self.emit(name, "typedef", start, ns, linkage, tmpl, {"type": rest})
            elif func:
                self.emit_function(name, rest, params, attrs, start, ns, linkage, tmpl)
            else:
                if not rest:
                    continue  # a macro invocation statement such as FOO(x);
                cc = next((CALLCONV[t] for t in rest if t in CALLCONV), None)
                self.emit(name, "var", start, ns, linkage, tmpl,
                          {"type": [t for t in rest if t not in ("extern", "static")],
                           "dllimport": any("dllimport" in a for a in attrs), "cc": cc})

    @staticmethod
    def _spec_len(seq, name):
        for k, t in enumerate(seq):
            if t in ("*", "&", "(") or t == name:
                return k
        return len(seq)

    def enumerators(self, i, end):
        out = []
        cur = []
        S = self.S
        while i < end:
            if self.t.K[i] == "D":
                i += 1
                continue
            s = S[i]
            if s in ("(", "[", "{"):
                j = self.group_end(i)
                cur.extend(S[i:j + 1])
                i = j + 1
                continue
            if s == ",":
                self._enumerator(cur, out)
                cur = []
            else:
                cur.append(s)
            i += 1
        self._enumerator(cur, out)
        return out

    @staticmethod
    def _enumerator(cur, out):
        if not cur or not _is_ident(cur[0]):
            return
        value = cur[2:] if len(cur) > 2 and cur[1] == "=" else None
        out.append((cur[0], value))

    def members(self, i, end, ns):
        S, K = self.S, self.t.K
        out = []
        head = []
        while i < end:
            s = S[i]
            if K[i] == "D":
                self.pragma(i)
                i += 1
                continue
            if s in ("public", "private", "protected") and i + 1 < end and S[i + 1] == ":":
                i += 2
                continue
            if s == ";":
                if head:
                    self.member(head, out)
                head = []
                i += 1
                continue
            if s == "{":
                j = self.group_end(i)
                spec = self.class_spec(head) if head else None
                if spec:
                    k, key, tag, bases = spec
                    if key == "enum":
                        sub = self.enumerators(i + 1, j)
                        group = ("enum", tag, sub)
                    else:
                        group = ("group", key, self.members(i + 1, j, ns), tag)
                    i = j + 1
                    tail = []
                    while i < end and S[i] != ";":
                        tail.append(S[i])
                        i += 1
                    if key != "enum":
                        names = [find_declarator(p)[0] for p in _split_top(tail)] if tail else []
                        names = [x for x in names if x]
                        if tag is None or names:  # anonymous member or declared member
                            out.append(("g", group, names, key, self.pack))
                    head = []
                    i += 1
                    continue
                # inline member function body
                if head:
                    self.member(head, out, has_body=True)
                head = []
                i = j + 1
                continue
            if s in ("(", "["):
                j = self.group_end(i)
                head.extend(S[i:j + 1])
                i = j + 1
                continue
            head.append(s)
            i += 1
        if head:
            self.member(head, out)
        return out

    def member(self, head, out, has_body=False):
        seq, attrs = _strip_attrs(head)
        if not seq or seq[0] in ("typedef", "friend", "using", "template", "enum", "static_assert"):
            return
        if seq[0] in CLASS_KEYS and len(seq) <= 3 and "(" not in seq:
            return  # nested forward declaration
        if ":" in seq and "(" not in seq:
            k = seq.index(":")
            if k + 1 < len(seq) and seq[k + 1] != ":":
                bits = seq[k + 1:]
                seq = seq[:k]
            else:
                bits = None
        else:
            bits = None
        parts = _split_top(seq)
        name, rest, func, params, after = find_declarator(parts[0])
        if func:
            if name is None:
                return
            flags = set(seq)
            pure = "=" in (after or []) and "0" in (after or [])
            cc = next((CALLCONV[t] for t in rest if t in CALLCONV), None)
            ptypes, variadic = split_params(params)
            out.append(("m", name, "virtual" in flags, pure, [t for t in rest if t not in STORAGE and t not in CALLCONV],
                        ptypes, cc, "static" in flags))
            return
        if "static" in seq:
            return
        spec = parts[0][:self._spec_len(parts[0], name)] if name else parts[0]
        for index, part in enumerate(parts):
            if index:
                part = spec + part
                name, rest, func, params, after = find_declarator(part)
            if name is None:
                continue
            if "=" in rest:
                rest = rest[:rest.index("=")]
            out.append(("f", name, rest, " ".join(bits) if bits else None))


def parse_text(text, lang="cpp", defines=None, evaluate=True, lookup_ms=None, default_pack=8, maybe=None,
               info=None):
    """Parse one local file: returns (decls, local macros, includes); `maybe`
    and `info` as in preprocess."""
    toks = tokenize(text)
    active, macros, includes = preprocess(toks, defines, evaluate, maybe, info)
    local = {name: defs[-1] for name, defs in macros.items()}

    def lookup(name, in_ms):
        d = local.get(name)
        if d is not None:
            return d[0], d[1], False
        if lookup_ms is not None:
            return lookup_ms(name, in_ms)
        return None

    expanded = expand(active, lookup)
    decls = Parser(expanded, lang, default_pack).parse()
    return decls, macros, includes


# --------------------------------------------------------------------------
# Index
# --------------------------------------------------------------------------

CORE_PSDK = [
    "windows.h", "winsock.h", "objbase.h", "ole2.h", "oleauto.h", "olectl.h", "ocidl.h", "unknwn.h",
    "mmsystem.h", "mmreg.h", "msacm.h", "vfw.h", "shlobj.h", "shellapi.h", "shlwapi.h", "commctrl.h",
    "commdlg.h", "wininet.h", "urlmon.h", "imm.h", "tlhelp32.h", "dbghelp.h", "psapi.h", "setupapi.h",
    "wincrypt.h", "winioctl.h", "winver.h", "winnls.h", "winreg.h", "lmcons.h", "lmerr.h", "rpc.h",
    "richedit.h", "process.h", "snmp.h", "ddeml.h", "dlgs.h", "imagehlp.h", "mapi.h", "mmddk.h",
    "gdiplus.h", "msxml.h", "servprov.h", "strmif.h", "uuids.h", "control.h", "ks.h", "ksmedia.h",
    "wtypes.h", "basetsd.h", "intshcut.h", "winuser.h", "lzexpand.h", "nb30.h", "winperf.h",
    "winspool.h", "prsht.h", "oaidl.h", "objidl.h", "propidl.h", "comcat.h", "docobj.h", "exdisp.h",
    "mshtml.h", "rasdlg.h", "ras.h", "raserror.h", "sensapi.h", "userenv.h", "winefs.h", "winscard.h",
    "winsvc.h", "aclapi.h", "accctrl.h", "sddl.h", "security.h", "ntsecapi.h", "wintrust.h", "softpub.h",
    "mscat.h", "dsound.h", "dbt.h", "devguid.h", "hidsdi.h", "shfolder.h", "sfc.h", "mswsock.h",
    "iphlpapi.h", "ipexport.h", "icmpapi.h", "imagehlp.h", "winnetwk.h", "lm.h", "msi.h", "wmistr.h",
    "evntrace.h", "pdh.h", "powrprof.h", "regstr.h", "cpl.h", "sapi.h", "wbemidl.h", "msctf.h", "oleacc.h",
    "uxtheme.h", "tmschema.h", "rpcdce.h", "rpcndr.h",
]
WINSOCK2 = ["winsock2.h", "ws2tcpip.h", "mswsock.h", "wspiapi.h", "iphlpapi.h", "ws2spi.h", "qos.h",
            "wsipx.h", "wsnwlink.h", "nspapi.h", "svcguid.h", "mstcpip.h", "ws2atm.h"]
CRT_SKIP = {"danim.h", "adoguidpool.h", "jetoledb.h", "d3drmvis.h", "_vcclrit.h", "gcroot.h", "vcclr.h",
            "wmiatlprov.h", "dbgautoattach.h", "dtbase.h", "invkprxy.h", "srv.h", "penwin.h",
            "tvout.h", "use_ansi.h", "listing.inc", "oledbjvs.inc", "dvec.h", "fvec.h", "ivec.h",
            "comdefsp.h", "mm3dnow.h", "emmintrin.h", "xmmintrin.h", "mmintrin.h"}
# headers whose declarations win over earlier copies: operator new/delete
# and the placement forms belong to <new>, not to <crtdbg.h> or <xmemory>
HOME_HEADERS = {"new"}
CRT_FIRST = ["stddef.h", "stdio.h", "stdlib.h", "string.h", "time.h", "stdarg.h", "ctype.h", "wchar.h",
             "math.h", "memory.h", "malloc.h", "io.h", "process.h"]
STL_PUBLIC = {"xstring": "string", "xtree": "map", "xutility": "utility", "xmemory": "memory",
              "xlocale": "locale", "xiosbase": "ios", "xhash": "hash_map", "xdebug": "vector",
              "xstddef": "cstddef", "xlocinfo": "locale", "xlocnum": "locale", "xloctime": "locale",
              "xlocmon": "locale", "xlocmes": "locale", "xcomplex": "complex", "yvals.h": "cstddef",
              "use_ansi.h": "cstddef", "xmath.h": "cmath", "ymath.h": "cmath", "xlocinfo.h": "locale"}


def root_headers(roots):
    """[(label, abs path)] of every header under the roots."""
    out = []
    for label, root in roots:
        if not root.is_dir():
            continue
        for path in sorted(root.rglob("*")):
            if not path.is_file():
                continue
            suffix = path.suffix.lower()
            if suffix not in HEADER_SUFFIXES:
                continue
            if suffix == "" and path.stat().st_size > 4_000_000:
                continue
            out.append((f"{label}/{path.relative_to(root).as_posix()}", path))
    return out


def index_key(roots):
    h = hashlib.sha1(f"v{TOOL_VERSION}".encode())
    for label, path in root_headers(roots):
        st = path.stat()
        h.update(f"{label}\0{st.st_size}\0{st.st_mtime_ns}\n".encode())
    return h.hexdigest()[:16]


def _cl_env(roots):
    vc = vc71_root()
    if os.name != "nt":
        from build import compiler_environment, wine_path
        env = compiler_environment(vc)
        env["INCLUDE"] = ";".join(wine_path(p) for _, p in roots)
        return env
    env = os.environ.copy()
    env["INCLUDE"] = ";".join(str(p) for _, p in roots)
    env["PATH"] = os.pathsep.join([str(vc / "Vc7" / "bin"), str(vc / "Common7" / "IDE"),
                                   str(vc.parents[1]), env.get("PATH", "")])
    return env


def run_cl_e(lines, roots, lang="cpp", workdir=None):
    """(ok, stdout, stderr) of `cl /E` on a temporary unit made of `lines`."""
    vc = vc71_root()
    cl = vc / "Vc7" / "bin" / "cl.exe"
    command = [str(cl)]
    if os.name != "nt":
        command = ["wine"] + command
    workdir = workdir or CACHE_DIR
    workdir.mkdir(parents=True, exist_ok=True)
    fd, name = tempfile.mkstemp(suffix=".cpp" if lang == "cpp" else ".c", dir=workdir)
    with os.fdopen(fd, "w") as handle:
        handle.write("\n".join(lines) + "\n")
    try:
        if os.name != "nt":
            from build import wine_path
            name_arg = wine_path(name)
        else:
            name_arg = name
        result = subprocess.run(command + ["-nologo", "-E", "-MD", "-EHsc", "-DWIN32", "-D_WINDOWS",
                                           "-TP" if lang == "cpp" else "-TC", name_arg],
                                env=_cl_env(roots), capture_output=True, text=True, errors="replace")
    finally:
        os.unlink(name)
    errors = [ln for ln in result.stderr.splitlines() if re.search(r"\b(fatal )?error [CD]\d+", ln)]
    return result.returncode == 0 and not errors, result.stdout, result.stderr


def fit_headers(prefix, candidates, roots, lang):
    """The candidates, in order, that preprocess together after `prefix`."""
    accepted = list(candidates)

    def lines(hs):
        return prefix + [f"#include <{h}>" for h in hs]

    ok, out, err = run_cl_e(lines(accepted), roots, lang)
    while not ok and accepted:
        lo, hi = 0, len(accepted)
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if run_cl_e(lines(accepted[:mid]), roots, lang)[0]:
                lo = mid
            else:
                hi = mid
        dropped = accepted.pop(hi - 1)
        print(f"ms_header_audit: kitchen sink ({lang}) drops <{dropped}>", file=sys.stderr)
        ok, out, err = run_cl_e(lines(accepted), roots, lang)
    if not ok:
        raise SystemExit(f"ms_header_audit: kitchen sink prefix does not preprocess:\n{err[-2000:]}")
    return accepted, out


def _label_for(path_text, roots):
    norm = path_text.replace("\\", "/").lower()
    for label, root in roots:
        paths = [str(root)]
        if os.name != "nt":
            from build import wine_path
            paths.append(wine_path(root))
        for path in paths:
            prefix = path.replace("\\", "/").lower().rstrip("/") + "/"
            if norm.startswith(prefix):
                return f"{label}/{path_text.replace(chr(92), '/')[len(prefix):]}"
    return None


def _canonical_label(label, by_lower):
    return by_lower.get(label.lower(), label)


def build_index(roots, jobs=4, verbose=True):
    t0 = __import__("time").time()
    headers = root_headers(roots)
    by_lower = {label.lower(): label for label, _ in headers}
    log = (lambda msg: print(f"ms_header_audit: {msg} ({__import__('time').time() - t0:.0f}s)",
                             file=sys.stderr)) if verbose else (lambda msg: None)

    # 1. raw macro definitions (first definition per name)
    raw_macros = {}
    raw_macro_sites = collections.defaultdict(list)
    config_inputs = set()
    for label, path in headers:
        text = path.read_text(encoding="latin-1")
        toks = tokenize(text)
        config_inputs |= guard_inputs(toks)
        for i, kind in enumerate(toks.K):
            if kind == "D" and re.match(r"#\s*define\b", toks.S[i]):
                parsed = parse_define(toks.S[i])
                if parsed:
                    name, params, body = parsed
                    raw_macro_sites[name].append((label, toks.L[i], params, body))
                    raw_macros.setdefault(name, (params, body))
    log(f"{len(headers)} headers, {len(raw_macros)} macro names")

    # 2. kitchen-sink units
    crt = [label.split("/", 2)[2] for label, _ in headers if label.startswith(roots[0][0] + "/")
           and "/" not in label.split("/", 2)[2] and label.rsplit("/", 1)[-1].lower() not in CRT_SKIP]
    crt_c = [h for h in crt if h.endswith(".h")]
    crt_stl = [h for h in crt if not h.endswith(".h")]
    psdk_names = {label.rsplit("/", 1)[-1].lower(): label.split("/", 2)[-1]
                  for label, _ in headers if label.startswith(roots[1][0] + "/")} if len(roots) > 1 else {}
    core = [psdk_names[h.lower()].split("Include/", 1)[-1] for h in CORE_PSDK if h.lower() in psdk_names]
    core = list(dict.fromkeys(core))
    extras = []
    for label, root in roots[2:]:
        extras += [lab[len(label) + 1:] for lab, _ in headers if lab.startswith(label + "/")]
    # canonical homes first: the first definition of a guarded duplicate
    # (_iobuf, size_t, wchar_t ...) is the site the index reports
    crt_c = sorted(crt_c, key=lambda h: CRT_FIRST.index(h.lower()) if h.lower() in CRT_FIRST else len(CRT_FIRST))
    crt_c = crt_c + ["sys/stat.h", "sys/types.h", "sys/timeb.h", "sys/utime.h", "sys/locking.h"]
    units = {
        "cpp": (["#include <windows.h>"], crt_c + crt_stl + core + extras, "cpp"),
        "ws2": (["#define WIN32_LEAN_AND_MEAN", "#include <windows.h>"], WINSOCK2, "cpp"),
        "c": (["#include <windows.h>"], crt_c + core, "c"),
    }
    cache = CACHE_DIR / "units"
    cache.mkdir(parents=True, exist_ok=True)
    outputs = {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:
        futures = {name: pool.submit(fit_headers, prefix, cands, roots, lang)
                   for name, (prefix, cands, lang) in units.items()}
        for name, future in futures.items():
            outputs[name] = future.result()
    log("kitchen sinks: " + ", ".join(f"{k}={len(v[0])} headers" for k, v in outputs.items()))

    # 3. macro probe: the active value of every macro after the cpp/c units
    active_macros = {}
    for unit in ("cpp", "c"):
        accepted = outputs[unit][0]
        prefix, _, lang = units[unit]
        lines = prefix + [f"#include <{h}>" for h in accepted]
        names = sorted(raw_macros)
        for k, name in enumerate(names):
            params = raw_macros[name][0]
            lines.append(f"#ifdef {name}")
            if params is None:
                lines.append(f"__MSA_PROBE_{k}__ {name} __MSA_END__")
            else:
                args = ",".join("__MSA_VA__" if p == "..." else f"__MSA_P{j}__" for j, p in enumerate(params))
                lines.append(f"__MSA_PROBE_{k}__ {name}({args}) __MSA_END__")
            lines.append("#endif")
        ok, out, err = run_cl_e(lines, roots, lang)
        table = {}
        for m in re.finditer(r"__MSA_PROBE_(\d+)__ (.*?) ?__MSA_END__", out):
            name = names[int(m.group(1))]
            body = m.group(2).strip()
            params = raw_macros[name][0]
            table[name] = (params, body)
        active_macros[unit] = table
    log(f"macro probe: {len(active_macros['cpp'])} active (C++), {len(active_macros['c'])} (C)")

    def ms_lookup_factory(unit):
        table = active_macros.get(unit, {})
        cache_tokens = {}

        def lookup(name, in_ms):
            if name in cache_tokens:
                return cache_tokens[name]
            got = None
            if name in table:
                params, body = table[name]
                if params is None:
                    rep = tokenize(body)
                    got = (None, tuple(zip(rep.K, rep.S)), True)
                else:
                    raw = raw_macros.get(name)
                    if raw:
                        got = (raw[0], raw[1], True)
            elif name in raw_macros:
                raw = raw_macros[name]
                got = (raw[0], raw[1], True)
            cache_tokens[name] = got
            return got
        return lookup

    # 4. parse kitchen-sink outputs
    entries = collections.defaultdict(list)
    seen = set()
    parents = {}
    direct = set()
    core_files = set()
    core_order = {}
    for unit in ("cpp", "ws2", "c"):
        accepted, out = outputs[unit]
        lang = units[unit][2]
        toks = tokenize(out, line_directives=True)
        labels = [_label_for(f, roots) if f else None for f in toks.files]
        labels = [_canonical_label(lab, by_lower) if lab else None for lab in labels]
        core_files.update(lab for lab in labels if lab)
        for lab in labels:
            if lab:
                core_order.setdefault(lab, len(core_order))
        if unit == "cpp":
            _include_graph(out, roots, by_lower, parents, direct)
        for d in Parser(toks, lang).parse():
            label = labels[d.fid] if d.fid < len(labels) else None
            if not label:
                continue
            key = (d.name, d.kind, label, d.line, lang)
            if key in seen:
                continue
            seen.add(key)
            entries[d.name].append({"k": d.kind, "f": label, "l": d.line, "lang": lang, "pp": True,
                                    "link": d.linkage, "tmpl": d.tmpl, "d": d.d})
    log(f"preprocessed declarations: {sum(len(v) for v in entries.values())}")

    # 5. raw parse of every header (coverage for names outside the units)
    # keyed by the unqualified name: a sub-header parsed raw (GdiPlusHeaders.h)
    # has lost the namespace its parent opened, so its `Image` is `Gdiplus::Image`
    pp_sites = {(name.rsplit("::", 1)[-1], e["f"]) for name, es in entries.items() for e in es}
    jobs_list = [(label, str(path)) for label, path in headers]
    raw_results = []
    lookup_cpp = ms_lookup_factory("cpp")
    for label, path in jobs_list:
        try:
            text = Path(path).read_text(encoding="latin-1")
            decls, _, _ = parse_text(text, "cpp", evaluate=False, lookup_ms=lookup_cpp)
        except RecursionError:
            continue
        for d in decls:
            if (d.name.rsplit("::", 1)[-1], label) in pp_sites:
                continue
            raw_results.append((d.name, {"k": d.kind, "f": label, "l": d.line, "lang": "raw", "pp": False,
                                         "link": d.linkage, "tmpl": d.tmpl, "d": d.d}))
    for name, entry in raw_results:
        entries[name].append(entry)
    log(f"raw declarations added: {len(raw_results)}")

    # 6. macros
    for name, sites in raw_macro_sites.items():
        for label, line, params, body in sites:
            entries[name].append({"k": "macro", "f": label, "l": line, "lang": "raw", "pp": False,
                                  "link": None, "tmpl": False,
                                  "d": {"params": params, "body": " ".join(s for _, s in body),
                                        "active": {u: active_macros[u].get(name, (None, None))[1]
                                                   for u in active_macros}}})

    public = {}
    for label, _ in headers:
        public[label] = _public_header(label, parents, direct, roots)
    index = {"version": TOOL_VERSION, "roots": [(lab, str(p)) for lab, p in roots],
             "entries": dict(entries), "core": sorted(core_files), "core_order": core_order, "public": public,
             "units": {k: v[0] for k, v in outputs.items()},
             "active_macros": active_macros, "raw_macros": raw_macros, "config_inputs": config_inputs}
    log(f"index: {len(entries)} names")
    return index


def _include_graph(out, roots, by_lower, parents, direct):
    stack = []
    for m in re.finditer(r'^#line \d+ "((?:\\.|[^"\\])*)"', out, re.M):
        name = m.group(1).replace("\\\\", "\\")
        label = _label_for(name, roots)
        label = _canonical_label(label, by_lower) if label else "<unit>"
        if label in stack:
            del stack[stack.index(label) + 1:]
            continue
        if stack and label not in parents:
            parents[label] = stack[-1]
            if stack[-1] == "<unit>":
                direct.add(label)
        stack.append(label)


def _public_header(label, parents, direct, roots):
    """The header a source should include to get `label`'s declarations."""
    rel = label.split("/", 2)[-1] if label.startswith("Vc7/") else label.split("/", 1)[-1]
    if label.startswith("Vc7/PlatformSDK/Include/"):
        rel = label[len("Vc7/PlatformSDK/Include/"):]
    elif label.startswith("Vc7/include/"):
        rel = label[len("Vc7/include/"):]
    base = rel.rsplit("/", 1)[-1]
    if base.lower() in STL_PUBLIC or base in STL_PUBLIC:
        return STL_PUBLIC.get(base, STL_PUBLIC.get(base.lower()))
    if label.startswith("Vc7/include/") and "/" not in rel:
        return rel  # a CRT or standard C++ header is public itself: <new>, not the <algorithm> that pulled it in
    node, chain = label, []
    while node in parents and node not in direct:
        node = parents[node]
        chain.append(node)
        if len(chain) > 64:
            break
    if label in direct or node == label:
        return rel
    if node.lower().endswith("/windows.h"):
        return "windows.h"
    if node in direct:
        top = node.split("Include/", 1)[-1] if "PlatformSDK" in node else node.split("include/", 1)[-1]
        return top
    return rel


def load_index(roots=None, rebuild=False, jobs=4):
    roots = roots or default_roots()
    key = index_key(roots)
    path = CACHE_DIR / f"index-{key}.pickle"
    if path.exists() and not rebuild:
        with path.open("rb") as handle:
            index = pickle.load(handle)
        if "config_inputs" in index:
            return index
        # an index from before config inputs were recorded: add them
        index["config_inputs"] = set()
        for _, hpath in root_headers(roots):
            index["config_inputs"] |= guard_inputs(tokenize(hpath.read_text(encoding="latin-1")))
    else:
        index = build_index(roots, jobs)
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(".tmp")
    with tmp.open("wb") as handle:
        pickle.dump(index, handle, protocol=pickle.HIGHEST_PROTOCOL)
    os.replace(tmp, path)
    for stale in CACHE_DIR.glob("index-*.pickle"):  # earlier tool versions or header sets
        if stale != path:
            stale.unlink(missing_ok=True)
    return index


VALIDATE = [("GUID", "typedef"), ("_GUID", "struct"), ("RECT", "typedef"), ("tagRECT", "struct"),
            ("CRITICAL_SECTION", "typedef"), ("CreateFileA", "function"), ("strlen", "function"),
            ("_iobuf", "struct"), ("FILE", "typedef"), ("WINAPI", "macro"), ("HRESULT", "typedef"),
            ("std::vector", "class"), ("std::basic_string", "class"), ("std::allocator", "class"),
            ("timeGetTime", "function"), ("IUnknown", "struct"), ("MAX_PATH", "macro"),
            ("InterlockedIncrement", "function"), ("size_t", "typedef"), ("std::pair", "struct"),
            ("COINIT_MULTITHREADED", "enumerator"), ("sockaddr_in", "struct"), ("htonl", "function")]


def site_rank(index, e, lang="cpp"):
    """Sort key of an index entry as the real definition's site: preprocessed
    before raw, the unit's language, headers the kitchen sinks reach (windows.h
    and the CRT) before stray SDK headers that redefine a name (WINAPI in
    appmgmt.h, MAX_PATH in MAPIWin.h), public headers before internal ones,
    then include order (windef.h's WINAPI before WinCrypt.h's fallback)."""
    order = index.get("core_order", {})
    return (not e["pp"], e["lang"] != lang and e["pp"], e["f"].rsplit("/", 1)[-1] not in HOME_HEADERS,
            e["f"] not in order,
            index["public"].get(e["f"], "") == "", order.get(e["f"], 0))


def best_site(index, es, lang="cpp"):
    return min(es, key=lambda e: site_rank(index, e, lang)) if es else None


def validate(index):
    bad = 0
    for name, kind in VALIDATE:
        es = [e for e in index["entries"].get(name, []) if e["k"] == kind]
        pp = [e for e in es if e["pp"]]
        best = best_site(index, es)
        where = f"{best['f']}:{best['l']}" if best else "MISSING"
        if not best:
            bad += 1
        print(f"  {name:<26} {kind:<10} {where}{'' if pp or not es else '  (raw only)'}")
    return bad


# --------------------------------------------------------------------------
# Canonical types and comparison
# --------------------------------------------------------------------------

_BUILTIN_RUN = BUILTIN


def _norm_run(words):
    cv = [w for w in ("const", "volatile") if w in words]
    rest = [w for w in words if w not in ("const", "volatile")]
    if not rest:
        return cv
    uns = "unsigned" in rest
    sgn = "signed" in rest
    if "char" in rest or "__int8" in rest:
        base = "unsigned char" if uns else ("signed char" if sgn else "char")
    elif "short" in rest or "__int16" in rest:
        base = "unsigned short" if uns else "short"
    elif rest.count("long") >= 2 or "__int64" in rest:
        base = "unsigned __int64" if uns else "__int64"
    elif "double" in rest:
        base = "double"
    elif "long" in rest:
        base = "unsigned long" if uns else "long"
    elif "int" in rest or "__int32" in rest or uns or sgn:
        base = "unsigned int" if uns else "int"
    elif "__wchar_t" in rest or "wchar_t" in rest:
        base = "wchar_t"
    else:
        base = " ".join(rest)
    return cv + base.split()


class TypeCtx:
    """Typedef and tag resolution: local declarations first, then the index."""

    def __init__(self, index, lang="cpp", local=None):
        self.index = index
        self.lang = lang
        self.local_typedefs = {}
        self.local_tags = {}
        for d in local or []:
            if d.kind == "typedef":
                self.local_typedefs.setdefault(d.name, d.d["type"])
            elif d.kind in ("struct", "class", "union") and d.d.get("members") is not None:
                self.local_tags.setdefault(d.name, d)
            elif d.kind == "enum":
                self.local_tags.setdefault(d.name, d)
        self._cache = {}

    def best(self, name, kinds):
        es = [e for e in self.index["entries"].get(name, ()) if e["k"] in kinds]
        if not es:
            return None
        lang = "c" if self.lang == "c" else "cpp"
        for pred in (lambda e: e["pp"] and e["lang"] == lang, lambda e: e["pp"], lambda e: True):
            for e in es:
                if pred(e):
                    return e
        return None

    def typedef(self, name, local_first=True):
        if local_first and name in self.local_typedefs:
            return self.local_typedefs[name]
        e = self.best(name, ("typedef",))
        return e["d"]["type"] if e else None

    def tag(self, name):
        if name in self.local_tags:
            d = self.local_tags[name]
            return {"k": d.kind, "d": d.d}
        e = self.best(name, ("struct", "class", "union", "enum"))
        if e and e["k"] != "enum" and not e["d"].get("members") and len(e["d"].get("members", [])) == 0:
            # prefer a complete definition
            for cand in self.index["entries"].get(name, ()):
                if cand["k"] == e["k"] and cand["d"].get("members"):
                    return cand
        return e

    def canon(self, toks, depth=0, local_first=True, active=frozenset()):
        """Canonical tokens; `active` holds the typedefs being expanded, so a
        self-referencing one (junk parsed as `typedef ... EOF EOF ...`) stays
        a name instead of expanding exponentially."""
        _tick()
        out = []
        run = []
        i = 0
        toks = list(toks)
        while i < len(toks):
            t = toks[i]
            if t in STORAGE or t in ("typename",):
                i += 1
                continue
            if t in CALLCONV:
                if run:
                    out.extend(_norm_run(run))
                    run = []
                out.append(CALLCONV[t])
                i += 1
                continue
            if t in _BUILTIN_RUN:
                run.append(t)
                i += 1
                continue
            if run:
                out.extend(_norm_run(run))
                run = []
            if t in CLASS_KEYS:
                if i + 1 < len(toks):
                    out.append(self._tag_name(toks[i + 1]))
                    i += 2
                    continue
                i += 1
                continue
            if _is_ident(t) and depth < 24 and t not in active and not (i + 1 < len(toks) and toks[i + 1] == "::") \
                    and not (i and toks[i - 1] == "::"):
                td = self.typedef(t, local_first)
                if td is not None and td != [t]:
                    sub = self.canon(td, depth + 1, local_first, active | {t})
                    out.extend(sub)
                    i += 1
                    continue
                if t == "wchar_t":
                    out.append("unsigned short")
                    i += 1
                    continue
            out.append(t)
            i += 1
        if run:
            out.extend(_norm_run(run))
        # move cv that ends up after a base type: "char const" -> "const char"
        return tuple(_fix_cv(out))

    def _tag_name(self, name):
        return name

    # ABI ----------------------------------------------------------------
    def abi(self, ctoks, depth=0):
        toks = [t for t in ctoks if t not in ("const", "volatile")]
        if not toks:
            return ("?",)
        if "(" in toks or "*" in toks or "&" in toks:
            # pointer or function pointer; a bare function type is a pointer as a param
            return ("p",)
        if "[" in toks:
            k = toks.index("[")
            elem = self.abi(toks[:k], depth)
            dims = 1
            for m in re.finditer(r"\[([^\]]*)\]", " ".join(toks[k:])):
                v = eval_int(m.group(1).split())
                dims *= v if v is not None else 1
            return ("a", elem, dims)
        base = " ".join(toks)
        b = _ABI_BUILTIN.get(base)
        if b:
            return b
        if len(toks) == 1 and depth < 12:
            tag = self.tag(toks[0])
            if tag:
                if tag["k"] == "enum":
                    return ("i", 4, "s")
                lay = self.layout(tag, depth + 1)
                if lay:
                    return ("s", lay[0], lay[1], lay[2])
        return ("?", base)

    def size_align(self, cls):
        k = cls[0]
        if k == "p":
            return 4, 4
        if k in ("i", "f"):
            return cls[1], cls[1]
        if k == "v":
            return 0, 1
        if k == "a":
            s, a = self.size_align(cls[1])
            return (None if s is None else s * cls[2]), a
        if k == "s":
            return cls[1], cls[2]
        return None, None

    def layout(self, tag, depth=0):
        d = tag["d"]
        key = id(d)
        if key in self._cache:
            return self._cache[key]
        self._cache[key] = None
        members = d.get("members") or []
        is_union = d.get("key") == "union"
        pack = d.get("pack") or 8
        result = self._layout_members(members, is_union, pack, depth, bases=d.get("bases") or [])
        self._cache[key] = result
        return result

    def _layout_members(self, members, is_union, pack, depth, bases=()):
        offset, size_max, max_align = 0, 0, 1
        flat = []
        has_virtual = any(m[0] == "m" and m[2] for m in members)
        for base in bases:
            btag = self.tag("".join(base)) if base else None
            if btag:
                lay = self.layout(btag, depth + 1)
                if lay is None:
                    return None
                flat.extend(lay[2])
                offset = lay[0]
                max_align = max(max_align, lay[1])
                if any(f[1] == ("vptr",) for f in lay[2]):
                    has_virtual = False
        if has_virtual:
            flat.append((0, ("vptr",)))
            offset, max_align = 4, 4
        bit_unit = None  # (size, bits used)
        for m in members:
            if m[0] == "m":
                continue
            if m[0] == "g":
                _, group, names, key, gpack = m
                sub = self._layout_members(group[2], key == "union", gpack or pack, depth + 1)
                if sub is None:
                    return None
                size, align, gflat = sub
                bit_unit = None
                align = min(align, pack)
                if not is_union:
                    offset = -(-offset // align) * align
                base_off = 0 if is_union else offset
                flat.extend((base_off + o, c) for o, c in gflat)
                if is_union:
                    size_max = max(size_max, size)
                else:
                    offset += size
                max_align = max(max_align, align)
                continue
            _, name, ttoks, bits = m
            cls = self.abi(self.canon(ttoks), depth + 1)
            size, align = self.size_align(cls)
            if size is None:
                return None
            align = min(align or 1, pack)
            if bits is not None:
                nbits = eval_int(bits.split())
                if bit_unit and bit_unit[0] == size and nbits is not None and bit_unit[1] + nbits <= size * 8 \
                        and not is_union:
                    bit_unit = (size, bit_unit[1] + nbits)
                    flat.append((bit_unit[2], ("bits", cls, nbits)) if len(bit_unit) > 2 else (offset, ("bits", cls, nbits)))
                    continue
                if not is_union:
                    offset = -(-offset // align) * align
                flat.append((0 if is_union else offset, ("bits", cls, nbits)))
                bit_unit = (size, nbits or 0)
                if is_union:
                    size_max = max(size_max, size)
                else:
                    offset += size
                max_align = max(max_align, align)
                continue
            bit_unit = None
            if not is_union:
                offset = -(-offset // align) * align
            leaf = cls if cls[0] != "s" else ("s", cls[1])
            flat.append((0 if is_union else offset, leaf))
            if cls[0] == "s":
                flat.extend(((0 if is_union else offset) + o, c) for o, c in cls[3])
            if is_union:
                size_max = max(size_max, size)
            else:
                offset += size
            max_align = max(max_align, align)
        total = size_max if is_union else offset
        total = -(-total // max_align) * max_align if total else (1 if self.lang == "cpp" else 0)
        return total, max_align, tuple(flat)


def _fix_cv(out):
    res = []
    for t in out:
        if t in ("const", "volatile") and res and res[-1] not in ("*", "&", "(", ",") and res[-1] not in ("const", "volatile"):
            # "T const" -> "const T" when T is a single base type
            k = len(res) - 1
            while k > 0 and res[k - 1] in ("unsigned", "signed", "short", "long"):
                k -= 1
            res.insert(k, t)
            continue
        res.append(t)
    return res


_ABI_BUILTIN = {
    "char": ("i", 1, "s"), "signed char": ("i", 1, "s"), "unsigned char": ("i", 1, "u"),
    "short": ("i", 2, "s"), "unsigned short": ("i", 2, "u"), "wchar_t": ("i", 2, "u"),
    "int": ("i", 4, "s"), "long": ("i", 4, "s"), "unsigned int": ("i", 4, "u"), "unsigned long": ("i", 4, "u"),
    "__int64": ("i", 8, "s"), "unsigned __int64": ("i", 8, "u"), "float": ("f", 4), "double": ("f", 8),
    "bool": ("i", 1, "u"), "void": ("v",),
}

# config: a configuration macro (NOMINMAX, UNICODE ...), an input to the
# headers that is never removable; unverified: a definition with a body (an
# inline function, a macro) not proven identical to the real one
SEVERITY = {"config": -3, "impl": -2, "collision": -1, "fwd": 0, "same": 0, "source": 1, "unknown": 2,
            "unverified": 3, "mangle": 4, "abi": 5}
# severities that never make a file removable work (and never count as a
# definition check() refuses)
NOT_DEFINITIONS = ("config", "impl", "collision", "fwd")

# macros that configure the Microsoft headers rather than define their API
CONFIG_MACROS = {
    "UNICODE", "_UNICODE", "_MBCS", "_SBCS", "STRICT", "NO_STRICT", "NOMINMAX", "WIN32_LEAN_AND_MEAN",
    "VC_EXTRALEAN", "WIN32_EXTRA_LEAN", "_WIN32_WINNT", "WINVER", "_WIN32_WINDOWS", "_WIN32_IE",
    "NTDDI_VERSION", "_WIN32_DCOM", "INC_OLE1", "INC_OLE2", "OEMRESOURCE", "_CRT_SECURE_NO_DEPRECATE",
    "_CRT_NONSTDC_NO_DEPRECATE", "_USE_32BIT_TIME_T", "_USE_MATH_DEFINES", "_POSIX_", "_DLL", "_MT",
    "_DEBUG", "NDEBUG", "WIN32", "_WINDOWS", "_CONSOLE", "_AFXDLL", "_ATL_STATIC_REGISTRY", "INITGUID",
    "COBJMACROS", "CINTERFACE", "DIRECTINPUT_VERSION", "DIRECT3D_VERSION", "DIRECTSOUND_VERSION",
    "DIRECTDRAW_VERSION", "_WINSOCKAPI_", "_WINSOCK2API_", "MMNODRV", "MMNOSOUND", "MMNOWAVE", "MMNOMIDI",
    "MMNOAUX", "MMNOMIXER", "MMNOTIMER", "MMNOJOY", "MMNOMCI", "MMNOMMIO", "MMNOMMSYSTEM",
    # windows.h's NOxxx switches
    "NOGDICAPMASKS", "NOVIRTUALKEYCODES", "NOWINMESSAGES", "NOWINSTYLES", "NOSYSMETRICS", "NOMENUS",
    "NOICONS", "NOKEYSTATES", "NOSYSCOMMANDS", "NORASTEROPS", "NOSHOWWINDOW", "NOATOM", "NOCLIPBOARD",
    "NOCOLOR", "NOCTLMGR", "NODRAWTEXT", "NOGDI", "NOKERNEL", "NOUSER", "NONLS", "NOMB", "NOMEMMGR",
    "NOMETAFILE", "NOMSG", "NOOPENFILE", "NOSCROLL", "NOSERVICE", "NOSOUND", "NOTEXTMETRIC", "NOWH",
    "NOWINOFFSETS", "NOCOMM", "NOKANJI", "NOHELP", "NOPROFILER", "NODEFERWINDOWPOS", "NOMCX", "NOCRYPT",
    "NOIME", "NOIMAGE", "NOTAPE", "NORPC", "NOPROXYSTUB", "NOMDI", "NOSYSPARAMSINFO",
    # defaults a unit overrides before the headers: _CRTIMP (dllimport or not,
    # TerrainResourceManagerGridRva0035A2DC.cpp restores it over /D_CRTIMP=),
    # the placement new/delete guards <new> tests
    "_CRTIMP", "_CRTIMP2", "__PLACEMENT_NEW_INLINE", "__PLACEMENT_VEC_NEW_INLINE", "DECLSPEC_IMPORT",
}


def is_config(index, name):
    """A macro the headers read to select definitions: the fixed list, or one
    a header tests with `#ifndef X` / `#if !defined(X)` around anything but
    its own default value (index "config_inputs", guard_inputs)."""
    return name in CONFIG_MACROS or name in index.get("config_inputs", ())


# a /MD unit's prototype of a CRT function without dllimport is no copy to
# replace blindly: sampled `free` callers call the game's allocator wrapper
# (VA 0x430830), not CRT free's IAT entry (0xBBA6E8)
VERIFY_CALLEE = ("do not blanket-replace: verify the callee per body (sampled free callers call the game "
                 "allocator wrapper at VA 0x430830, not CRT free's IAT entry 0xBBA6E8)")


def _join(toks):
    return " ".join(toks)


class Comparer:
    def __init__(self, index, lang, local_decls, file_md=True, local_macros=None):
        self.index = index
        self.lang = lang
        self.ctx = TypeCtx(index, lang, local_decls)
        self.real = TypeCtx(index, lang, None)
        self.file_md = file_md
        self.local_macros = local_macros or {}

    def entries(self, name):
        return self.index["entries"].get(name, ())

    def compare(self, d):
        """(severity, reason, entry) of local declaration `d` against the
        index, or None when the name is not a Microsoft one (or only an
        unrelated overload/collision)."""
        es = list(self.entries(d.name))
        if not es:
            return None
        kind = d.kind
        if kind == "fwd":
            match = [e for e in es if e["k"] in ("struct", "class", "union", "fwd", "typedef")]
            return ("fwd", "forward declaration", self.pick(match)) if match else None
        if kind == "function":
            return self.compare_function(d, es)
        if kind == "typedef":
            return self.compare_typedef(d, es)
        if kind in ("struct", "class", "union"):
            return self.compare_struct(d, es)
        if kind == "enum":
            return self.compare_enum(d, es)
        if kind == "enumerator":
            return self.compare_value(d, es)
        if kind == "var":
            return self.compare_var(d, es)
        return None

    def pick(self, es):
        return best_site(self.index, es, "c" if self.lang == "c" else "cpp")

    def ordered(self, es):
        lang = "c" if self.lang == "c" else "cpp"
        return sorted(es, key=lambda e: site_rank(self.index, e, lang))

    # functions --------------------------------------------------------------
    def fn_sig(self, detail, ctx, crt_entry=False):
        params = detail["params"] or []
        ptypes = [ctx.canon(p) for p in params]
        pabi = [ctx.abi(p) for p in ptypes]
        ret = ctx.canon(detail["ret"])
        stack = 0
        for a in pabi:
            s, _ = ctx.size_align(a) if a[0] != "a" else (4, 4)
            stack += -(-(s or 4) // 4) * 4
        dll = detail.get("dllimport", False)
        return {"cc": detail.get("cc") or "__cdecl", "ret": ret, "ret_abi": ctx.abi(ret) if ret else ("i", 4, "s"),
                "ptypes": ptypes, "pabi": pabi, "stack": stack, "variadic": detail.get("variadic", False),
                "dll": dll, "n": len(params), "throws": detail.get("throws")}

    def compare_function(self, d, es):
        fns = [e for e in es if e["k"] == "function"]
        if not fns:
            macro = [e for e in es if e["k"] == "macro"]
            if macro and (d.linkage == "C" or d.d.get("dllimport")):
                return ("unknown", "the real header makes this name a macro", self.pick(macro))
            return None
        local = self.fn_sig(d.d, self.ctx)
        body = d.d.get("body")
        if body:
            inline_real = [e for e in fns if e["d"].get("body")]
            if not inline_real:
                if any(not e["d"].get("body") for e in fns):
                    best = self.pick(fns)
                    return ("impl", "implementation of a function the real header declares", best)
                return None
            # a signature match says nothing about the body: only token-equal
            # bodies (parameters renamed) are the same definition
            proven = [e for e in inline_real if e["d"]["body"] == body]
            if not proven:
                res = self._signature_best(d, local, inline_real)
                if res is None:
                    return None
                return ("unverified", "inline body not proven identical to the real header's"
                        + ("" if res[0] == "same" else f" ({res[1]})"), res[2]) \
                    if SEVERITY[res[0]] < SEVERITY["unverified"] else res
            res = self._signature_best(d, local, proven)
            return ("same", "identical inline body", res[2]) if res and res[0] == "same" else res
        return self._signature_best(d, local, fns)

    def _signature_best(self, d, local, fns):
        best = None
        for e in self.ordered(fns):
            real = self.fn_sig(e["d"], self.real)
            crt = e["f"].startswith("Vc7/include/")
            if crt:
                real["dll"] = real["dll"] and self.file_md
            sev, why = self._fn_diff(d, local, e, real)
            if best is None or SEVERITY[sev] < SEVERITY[best[0]]:
                best = (sev, why, e)
            if sev == "same":
                break
        # an unrelated C++ overload (operator+ on AsciiString against the
        # templates in <xcomplex>, sqrt(float) against sqrt(double)): C++
        # linkage and no real non-template overload with the same parameter
        # types. dllimport does not make a game's operator a SIMD overload;
        # keep the existing conservative treatment of named functions and
        # allocation operators, whose malformed declarations need reporting.
        overload_operator = d.name.startswith("operator") and not d.name.startswith(
            ("operator new", "operator delete"))
        if best and best[0] != "same" and d.linkage == "C++" \
                and (not d.d.get("dllimport") or overload_operator) \
                and not any(self._same_params(local, e) for e in fns):
            return None
        return best

    def _same_params(self, local, e):
        if e["tmpl"]:
            return False
        real = self.fn_sig(e["d"], self.real)
        if real["n"] != local["n"]:
            return False
        # C++ overloads differ by type, even at one ABI: const AsciiString & is
        # not I8vec16 &, and the game's CloseWindow(const char *) is not
        # CloseWindow(HWND)
        return local["ptypes"] == real["ptypes"]

    def _fn_diff(self, d, local, e, real):
        reasons = []
        sev = "same"

        def worse(s, why):
            nonlocal sev
            reasons.append(why)
            if SEVERITY[s] > SEVERITY[sev]:
                sev = s
        if local["cc"] != real["cc"]:
            worse("abi", f"calling convention {local['cc']} vs {real['cc']}")
        if local["variadic"] != real["variadic"]:
            worse("abi", "variadic differs")
        if self.lang == "cpp" and local["throws"] != real["throws"]:
            def contract(spec):
                return "unspecified" if spec is None else "throw(" + _join(spec) + ")"
            worse("abi", f"exception specification {contract(local['throws'])} vs {contract(real['throws'])}; "
                  "may change unwind cleanup")
        if local["n"] != real["n"]:
            worse("abi", f"{local['n']} parameters vs {real['n']}")
        else:
            for k, (a, b) in enumerate(zip(local["pabi"], real["pabi"])):
                if a != b and not (a[0] == "?" or b[0] == "?"):
                    worse("abi", f"parameter {k + 1} {_join(local['ptypes'][k])} vs {_join(real['ptypes'][k])}")
                elif local["ptypes"][k] != real["ptypes"][k]:
                    if a[0] == "?" or b[0] == "?":
                        worse("unknown", f"parameter {k + 1} {_join(local['ptypes'][k])} vs {_join(real['ptypes'][k])}")
                    else:
                        worse("mangle" if d.linkage == "C++" and e["link"] != "C" else "source",
                              f"parameter {k + 1} spelled {_join(local['ptypes'][k])} vs {_join(real['ptypes'][k])}")
        if local["ret_abi"] != real["ret_abi"] and local["ret_abi"][0] != "?" and real["ret_abi"][0] != "?":
            worse("abi", f"returns {_join(local['ret'])} vs {_join(real['ret'])}")
        elif local["ret"] != real["ret"]:
            worse("source" if local["ret_abi"] == real["ret_abi"] else "unknown",
                  f"return spelled {_join(local['ret'])} vs {_join(real['ret'])}")
        if local["dll"] != real["dll"]:
            worse("abi", ("dllimport locally, none in the real header" + ("" if self.file_md else " (unit lacks /MD)"))
                  if local["dll"] else "real header declares dllimport"
                  + (f"; {VERIFY_CALLEE}" if e["f"].startswith("Vc7/include/") else ""))
        if d.linkage != (e["link"] or "C++") and self.lang == "cpp":
            worse("mangle", f"{d.linkage} linkage vs {e['link']}")
        return sev, "; ".join(reasons) or "identical"

    # typedefs ---------------------------------------------------------------
    def compare_typedef(self, d, es):
        tds = [e for e in es if e["k"] == "typedef"]
        local = self.ctx.canon(d.d["type"])
        if not tds:
            other = [e for e in es if e["k"] in ("struct", "class", "union", "macro")]
            if other:
                e = self.pick(other)
                if e["k"] == "macro":
                    return ("source", "the real header makes this name a macro", e)
                if d.d.get("tag") and d.d["tag"] == d.name:
                    return self.compare_struct_detail(d, e, local_name=d.name)
                return ("unknown", f"typedef here, {e['k']} in the real header", e)
            return None
        best = None
        for e in self.ordered(tds):
            real = self.real.canon(e["d"]["type"])
            sev, why = self._type_diff(local, real)
            if sev != "abi" and d.d.get("tag") and e["d"].get("tag") and not d.d["tag"].startswith("<anon") \
                    and not e["d"]["tag"].startswith("<anon") and d.d["tag"] != e["d"]["tag"]:
                if SEVERITY["mangle"] > SEVERITY[sev]:
                    sev, why = "mangle", f"tag {d.d['tag']} vs {e['d']['tag']}"
            if local and local[0].startswith("<anon") or (d.d.get("tag") or "").startswith("<anon"):
                # anonymous struct typedef: compare the bodies
                tag = self.ctx.tag(d.d.get("tag") or "")
                rtag_name = e["d"].get("tag")
                if tag and rtag_name:
                    rtag = self.real.tag(rtag_name)
                    if rtag and "enum" in (tag["k"], rtag["k"]):
                        lv = self._enum_values(tag["d"]["members"]) if tag["k"] == "enum" else None
                        rv = self._enum_values(rtag["d"]["members"]) if rtag["k"] == "enum" else None
                        sev, why = (("same", "identical") if lv == rv else ("abi", "enumerator values differ")) \
                            if lv is not None and rv is not None else ("unknown", "enum vs struct")
                    elif rtag:
                        sev2, why2 = self._struct_diff(tag["d"], rtag["d"])
                        sev, why = (sev2, why2) if sev2 != "same" else ("mangle", f"anonymous struct vs {rtag_name}")
            if best is None or SEVERITY[sev] < SEVERITY[best[0]]:
                best = (sev, why, e)
            if sev == "same":
                break
        return best

    def _type_diff(self, local, real):
        if local == real:
            return "same", "identical"
        la, ra = self.ctx.abi(local), self.real.abi(real)
        if la[0] == "?" or ra[0] == "?":
            if la == ra:
                return "same", "identical"
            return "unknown", f"{_join(local)} vs {_join(real)}"
        if la != ra:
            return "abi", f"{_join(local)} vs {_join(real)}"
        return "mangle", f"spelled {_join(local)} vs {_join(real)}"

    # structs ----------------------------------------------------------------
    def compare_struct(self, d, es):
        if d.d.get("members") is None:
            return None
        structs = [e for e in es if e["k"] in ("struct", "class", "union") and e["d"].get("members") is not None]
        if not structs:
            tds = [e for e in es if e["k"] == "typedef"]
            for e in self.ordered(tds):
                tag = e["d"].get("tag") or (e["d"]["type"][1] if len(e["d"]["type"]) == 2 and e["d"]["type"][0] in CLASS_KEYS else None)
                rtag = self.real.tag(tag) if tag else None
                if rtag:
                    if self._collision(d.d, rtag["d"]):
                        return ("collision", "unrelated type with a Microsoft name", e)
                    sev, why, _ = self.compare_struct_detail(d, rtag, local_name=d.name)
                    if SEVERITY[sev] < SEVERITY["mangle"]:
                        sev, why = "mangle", f"struct {d.name} vs typedef of {tag}" + ("" if why == "identical" else "; " + why)
                    return sev, why, e
            if tds:
                # `struct CRITICAL_SECTION {...}` beside the real
                # `typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;`
                return ("collision", f"{d.kind} here, a typedef of another type in the real header",
                        self.pick(tds))
            return None
        best = None
        for e in self.ordered(structs):
            res = self.compare_struct_detail(d, e)
            if best is None or SEVERITY[res[0]] < SEVERITY[best[0]]:
                best = res
            if res[0] == "same":
                break
        if best and best[0] != "same" and self._collision(d.d, best[2]["d"]):
            return ("collision", "unrelated type with a Microsoft name", best[2])
        return best

    def _collision(self, local, real):
        ln = {m[1] for m in local.get("members", []) if m[0] in ("f", "m")}
        rn = {m[1] for m in real.get("members", []) if m[0] in ("f", "m")}
        if not ln or not rn:
            return False
        return len(ln & rn) * 2 < min(len(ln), len(rn))

    def compare_struct_detail(self, d, e, local_name=None):
        if isinstance(d, Decl):
            ld = d.d if d.kind != "typedef" else (self.ctx.tag(d.d.get("tag") or "") or {"d": {}})["d"]
        else:
            ld = d
        sev, why = self._struct_diff(ld, e["d"])
        return sev, why, e

    def _struct_diff(self, ld, rd):
        lm, rm = ld.get("members") or [], rd.get("members") or []
        if not rm and lm:
            return "unknown", "real definition has no parsed members"
        lf = [m for m in lm if m[0] != "m"]
        rf = [m for m in rm if m[0] != "m"]
        lv = [m[1] for m in lm if m[0] == "m" and m[2]]
        rv = [m[1] for m in rm if m[0] == "m" and m[2]]
        reasons = []
        sev = "same"
        if lv != rv:
            if lv or rv:
                return "abi", f"virtual methods {lv[:4]} vs {rv[:4]}"
        if ld.get("align") != rd.get("align"):
            # __declspec(align) is not modelled: the layout is not established
            return "unknown", f"__declspec({ld.get('align') or 'no align'}) vs __declspec({rd.get('align') or 'no align'})"
        lpack, rpack = ld.get("pack") or 8, rd.get("pack") or 8
        llay = self.ctx._layout_members(lm, ld.get("key") == "union", lpack, 0, ld.get("bases") or [])
        rlay = self.real._layout_members(rm, rd.get("key") == "union", rpack, 0, rd.get("bases") or [])
        if llay is None or rlay is None:
            # identical text is the same layout only under the same packing
            same_text = [self._mtext(m, self.ctx) for m in lf] == [self._mtext(m, self.real) for m in rf]
            return ("same", "identical") if same_text and lpack == rpack else \
                ("unknown", "layout not computable" + (f" (pack {lpack} vs {rpack})" if same_text else ""))
        if llay[0] != rlay[0]:
            return "abi", f"size {llay[0]} vs {rlay[0]}"
        if llay[1] != rlay[1]:
            # same size and offsets, different alignment (#pragma pack(1)
            # around an all-int struct tm): containing types and stack slots move
            return "abi", f"alignment {llay[1]} vs {rlay[1]}"
        if llay[2] != rlay[2]:
            return "abi", "member layout differs"
        lnames = [m[1] for m in lf if m[0] == "f"]
        rnames = [m[1] for m in rf if m[0] == "f"]
        if lnames != rnames:
            sev = "source"
            reasons.append("member names differ")
        if [self._mtext(m, self.ctx) for m in lf] != [self._mtext(m, self.real) for m in rf] and sev == "same":
            sev = "source"
            reasons.append("member types spelled differently")
        lm_names = [m[1] for m in lm if m[0] == "m" and not m[2]]
        return sev, "; ".join(reasons) or "identical"

    def _mtext(self, m, ctx):
        if m[0] == "f":
            return (m[1], ctx.canon(m[2]), m[3])
        if m[0] == "g":
            return ("g", m[3], tuple(self._mtext(x, ctx) for x in m[1][2] if x[0] != "m"))
        return m

    # enums, values, vars, macros ---------------------------------------------
    def compare_enum(self, d, es):
        enums = [e for e in es if e["k"] == "enum"]
        if not enums:
            return None
        e = self.pick(enums)
        lv = self._enum_values(d.d["members"])
        rv = self._enum_values(e["d"]["members"])
        if lv == rv:
            return "same", "identical", e
        if dict(lv).items() <= dict(rv).items() or set(dict(lv)) & set(dict(rv)):
            common = set(dict(lv)) & set(dict(rv))
            if all(dict(lv)[k] == dict(rv)[k] for k in common):
                return "source", "enumerator sets differ", e
            return "abi", "enumerator values differ", e
        return "collision", "unrelated enum with a Microsoft name", e

    @staticmethod
    def _enum_values(members):
        out, cur, env = [], -1, {}
        for name, value in members:
            if value is None:
                cur = cur + 1 if cur is not None else None
            else:
                toks = [str(env.get(t, t)) for t in value]
                cur = eval_int(toks)
            env[name] = cur
            out.append((name, cur))
        return out

    def real_macro_value(self, e):
        active = e["d"].get("active") or {}
        unit = "c" if self.lang == "c" else "cpp"
        return active.get(unit) if active.get(unit) is not None else e["d"]["body"]

    def compare_value(self, d, es):
        """Enumerator (or const) against the real enumerator or macro."""
        value = d.d.get("value")
        lval = eval_int(value) if value else None
        for e in es:
            if e["k"] == "enumerator":
                rval = e["d"].get("value")
                rv = eval_int(rval) if rval else None
                if lval is not None and lval == rv:
                    return "same", "identical", e
        macros = [e for e in es if e["k"] == "macro" and e["d"]["params"] is None]
        if macros:
            e = self.pick([m for m in macros if self.real_macro_value(m) is not None] or macros)
            rv = eval_int(tokenize(self.real_macro_value(e) or "").S)
            if lval is not None and rv is not None:
                if lval == rv:
                    return "source", "enumerator here, macro in the real header", e
                return "abi", f"value {lval} vs {rv}", e
            return "unknown", "enumerator here, macro in the real header", e
        enums = [e for e in es if e["k"] == "enumerator"]
        if enums:
            return "abi" if lval is not None else "unknown", "value differs", self.pick(enums)
        return None

    def compare_var(self, d, es):
        vs = [e for e in es if e["k"] == "var"]
        if not vs:
            if any(e["k"] == "macro" for e in es):
                return "unknown", "variable here, macro in the real header", self.pick([e for e in es if e["k"] == "macro"])
            return None
        e = self.pick(vs)
        sev, why = self._type_diff(self.ctx.canon(d.d["type"]), self.real.canon(e["d"]["type"]))
        if d.d.get("dllimport") != e["d"].get("dllimport"):
            sev, why = "abi", "dllimport differs"
        if sev == "mangle" and d.linkage == "C":
            sev = "source"
        return sev, why, e

    def compare_macro(self, name, params, body_tokens, line):
        es = [e for e in self.entries(name)]
        if not es:
            return None
        macros = [e for e in es if e["k"] == "macro"]
        if is_config(self.index, name):
            return "config", "configuration macro: an input to the headers, never removable", \
                self.pick(macros or es)
        if not macros:
            kinds = {e["k"] for e in es}
            if kinds <= {"function"}:
                return "source", "macro here, function in the real header", self.pick(es)
            return "unknown", f"macro here, {sorted(kinds)[0]} in the real header", self.pick(es)
        local_text = self._macro_text(params, body_tokens)
        if local_text is None:
            return "unverified", "macro body could not be expanded", self.pick(macros)
        best = None
        for e in sorted(macros, key=lambda e: (self.real_macro_value(e) is None,
                                               site_rank(self.index, e, "c" if self.lang == "c" else "cpp"))):
            real = self.real_macro_value(e)
            if (params is None) != (e["d"]["params"] is None):
                sev, why = "unknown", "object-like vs function-like"
            elif real is None:
                # the site's text only: scan_text keeps "same" only when the
                # site is active under the unit's configuration
                sev, why = ("same", "identical") if local_text == _norm_space(e["d"]["body"]) else \
                    ("unknown", "real macro inactive in the default configuration")
            else:
                real_n = self._real_text(real, e["d"]["params"])
                if local_text == real_n:
                    sev, why = "same", "identical"
                else:
                    lv, rv = eval_int(local_text.split()), eval_int(real_n.split())
                    if lv is not None and rv is not None:
                        sev, why = ("same", "identical value") if lv == rv else ("abi", f"value {lv} vs {rv}")
                    elif self._canon_text(local_text) == self._canon_text(real_n):
                        sev, why = "same", "identical after typedef resolution"
                    else:
                        sev, why = "unknown", f"'{local_text[:60]}' vs '{real_n[:60]}'"
            if best is None or SEVERITY[sev] < SEVERITY[best[0]]:
                best = (sev, why, e)
            if best[0] == "same":
                break
        if best and best[0] == "unknown" and body_tokens:
            best = ("unverified", f"macro body not proven identical ({best[1]})", best[2])
        return best

    def _macro_text(self, params, body):
        """The local body, expanded with the file's other macros and the
        Microsoft ones, parameters renamed to the probe's placeholders."""
        rename = {}
        if params:
            for j, p in enumerate(params):
                rename[p] = "__MSA_VA__" if p == "..." else f"__MSA_P{j}__"
            rename["__VA_ARGS__"] = "__MSA_VA__"
        toks = Toks()
        for k, s in body:
            toks.add(k, rename.get(s, s), 0, 0)
        local = {n: defs[-1] for n, defs in self.local_macros.items()}
        unit = "c" if self.lang == "c" else "cpp"
        table = self.index["active_macros"].get(unit, {})
        raw = self.index["raw_macros"]

        def lookup(name, in_ms):
            if name in local:
                return local[name][0], local[name][1], False
            if name in table and table[name][0] is None:
                rep = tokenize(table[name][1])
                return None, tuple(zip(rep.K, rep.S)), True
            if name in raw:
                return raw[name][0], raw[name][1], True
            return None
        try:
            out = expand(toks, lookup, max_steps=2000)
        except RecursionError:
            return None  # unexpandable: never equal to a real body
        return _norm_space(" ".join(out.S))

    def _real_text(self, real, params):
        return _norm_space(" ".join(tokenize(real).S))

    def _canon_text(self, text):
        toks = text.split()
        return " ".join(self.real.canon(toks))


def _norm_space(text):
    text = " ".join(text.split())
    return text.replace("( ", "(").replace(" )", ")")


# --------------------------------------------------------------------------
# Configuration: is a real definition active under the unit's defines?
# --------------------------------------------------------------------------

# what the kitchen sinks were preprocessed with (run_cl_e: -MD -EHsc -DWIN32
# -D_WINDOWS) on top of the compiler's own predefinitions
SINK_PREDEFINED = {"_WIN32": "1", "_M_IX86": "600", "_MSC_VER": "1310", "_MSC_FULL_VER": "13103077",
                   "_INTEGRAL_MAX_BITS": "64", "_MSC_EXTENSIONS": "1", "_DLL": "1", "_MT": "1",
                   "_CPPUNWIND": "1", "WIN32": "1", "_WINDOWS": "1"}


def _macro_int(name, defines, depth=0):
    """Integer value of identifier `name` in an #if under `defines`: 0 when
    undefined (as in C), None when it does not reduce to an integer."""
    if name not in defines:
        return 0
    if depth > 8:
        return None
    toks = tokenize(defines[name] or "")
    if not toks.S:
        return None
    out = []
    for kind, s in zip(toks.K, toks.S):
        if kind == "I":
            v = _macro_int(s, defines, depth + 1)
            if v is None:
                return None
            out.append(str(v))
        else:
            out.append(s)
    return eval_int(out)


def cond_value(expr, defines):
    """True/False of an #if expression under `defines` ({name: value}), None
    when it does not evaluate."""
    toks = tokenize(expr)
    S, K = toks.S, toks.K
    out, i = [], 0
    while i < len(S):
        s = S[i]
        if s == "defined":
            if i + 1 < len(S) and S[i + 1] == "(":
                name, i = (S[i + 2] if i + 2 < len(S) else ""), i + 4
            else:
                name, i = (S[i + 1] if i + 1 < len(S) else ""), i + 2
            out.append("1" if name in defines else "0")
            continue
        if K[i] == "I":
            v = _macro_int(s, defines)
            if v is None:
                return None
            out.append(str(v))
        else:
            out.append(s)
        i += 1
    v = eval_int(out)
    return None if v is None else bool(v)


class _Frame:
    """One #if group: its branch expressions so far; `guard` when its first
    branch is `#ifndef X` / `#if !defined(X)` and defines X (an include
    guard, `_SIZE_T_DEFINED`), which holds whenever the definition matters."""
    __slots__ = ("exprs", "guard_name", "guard")

    def __init__(self, expr, guard_name):
        self.exprs = [expr]
        self.guard_name = guard_name
        self.guard = False


def directive_regions(text):
    """(lines, chains): chains[k] holds the (frame, branch) pairs enclosing
    the code after the conditional directive on lines[k]."""
    toks = tokenize(text)
    lines, chains, stack = [0], [()], []
    for kind, s, line in zip(toks.K, toks.S, toks.L):
        if kind != "D":
            continue
        word, rest = directive_words(s)
        if word in ("if", "ifdef", "ifndef"):
            name = rest.split()[0] if rest.split() else ""
            if word == "ifdef":
                frame = _Frame(f"defined({name})", None)
            elif word == "ifndef":
                frame = _Frame(f"!defined({name})", name)
            else:
                m = re.fullmatch(r"!\s*defined\s*\(?\s*(\w+)\s*\)?", rest)
                frame = _Frame(rest, m.group(1) if m else None)
            stack.append([frame, 0])
        elif word in ("elif", "else") and stack:
            frame = stack[-1][0]
            frame.exprs.append(rest if word == "elif" else None)
            stack[-1][1] = len(frame.exprs) - 1
        elif word == "endif" and stack:
            stack.pop()
        elif word == "define":
            name = rest.split("(")[0].split()[0] if rest.split() else ""
            for frame, branch in stack:
                if branch == 0 and frame.guard_name == name:
                    frame.guard = True
            continue
        else:
            continue
        lines.append(line)
        chains.append(tuple((f, b) for f, b in stack))
    return lines, chains


def chain_value(chain, defines):
    """True when every enclosing branch holds under `defines`, False when one
    fails, None when one does not evaluate."""
    unknown = False
    for frame, branch in chain:
        if frame.guard and branch == 0:
            continue
        for k in range(branch + 1):
            expr = frame.exprs[k]
            if expr is None:
                continue
            v = cond_value(expr, defines)
            if v is None:
                unknown = True
            elif v != (k == branch):
                return False
    return None if unknown else True


def chain_idents(chain):
    out = set()
    for frame, branch in chain:
        if frame.guard and branch == 0:
            continue
        for expr in frame.exprs[:branch + 1]:
            if expr:
                toks = tokenize(expr)
                out.update(s for k, s in zip(toks.K, toks.S) if k == "I" and s != "defined")
    return out


_REGIONS = {}


def header_regions(index, label):
    """directive_regions of the Microsoft header `label`, or None when it
    cannot be read (an index's precomputed `config_regions` win)."""
    pre = index.get("config_regions")
    if pre is not None and label in pre:
        return pre[label]
    if label in _REGIONS:
        return _REGIONS[label]
    got = None
    for root_label, root in index.get("roots", []):
        if label.startswith(root_label + "/"):
            path = Path(root) / label[len(root_label) + 1:]
            try:
                got = directive_regions(path.read_text(encoding="latin-1"))
            except OSError:
                got = None
            break
    _REGIONS[label] = got
    return got


# macros whose per-unit effect the comparer models itself (crt_dll)
TEXT_MODELLED = {"_CRTIMP"}
_DECL_TEXT = {}
_HEADER_LINES = {}


def _header_lines(index, label):
    # lines, not tokens: a worker holding every header's tokens runs out of memory
    if label in _HEADER_LINES:
        return _HEADER_LINES[label]
    text = None
    pre = index.get("header_text")
    if pre is not None and label in pre:
        text = pre[label]
    else:
        for root_label, root in index.get("roots", []):
            if label.startswith(root_label + "/"):
                try:
                    text = (Path(root) / label[len(root_label) + 1:]).read_text(encoding="latin-1")
                except OSError:
                    text = None
                break
    got = text.split("\n") if text is not None else None
    _HEADER_LINES[label] = got
    return got


def _decl_window(lines, e, start):
    """(identifiers, ended) of the text from line `start` (0-based) on."""
    out, depth = set(), 0
    window = 64
    while True:
        end = min(len(lines), e["l"] - 1 + window)
        toks = tokenize("\n".join(lines[start:end]))
        out, depth = set(), 0
        first = e["l"] - start  # e's line in the window's numbering
        for kind, s, line in zip(toks.K, toks.S, toks.L):
            if kind == "D":
                out |= _expr_idents(directive_words(s)[1])
                if e["k"] == "macro" and line >= first:
                    return out, True
                continue
            if kind == "I":
                out.add(s)
            if line < first or e["k"] == "macro":
                continue
            if s in ("{", "(", "["):
                depth += 1
            elif s in ("}", ")", "]"):
                depth -= 1
            elif s == ";" and depth <= 0:
                return out, True
        if end >= len(lines) or window >= 4096:
            return out, False
        window *= 4


def decl_idents(index, e, before=3):
    """Identifiers of the real declaration's source text at e's site: from a
    few lines before it to the `;` (a macro: the #define) that ends it, the
    conditionals inside included. None when the header cannot be read or the
    end is not found."""
    key = (e["f"], e["l"])
    if key in _DECL_TEXT:
        return _DECL_TEXT[key]
    lines = _header_lines(index, e["f"])
    got = None
    if lines is not None and 0 < e["l"] <= len(lines):
        out, ended = _decl_window(lines, e, max(e["l"] - 1 - before, 0))
        got = out - {"defined"} if ended else None
    _DECL_TEXT[key] = got
    return got


def site_chain(index, e):
    regions = header_regions(index, e["f"])
    if regions is None:
        return None
    lines, chains = regions
    k = bisect.bisect_left(lines, e["l"]) - 1
    return chains[max(k, 0)]


class UnitConfig:
    """A unit's configuration against the one the index was preprocessed
    with: `delta` names the macros whose definition differs."""

    def __init__(self, index, lang, tu_defines, local_defines, removed=()):
        self.index = index
        self.unit = "c" if lang == "c" else "cpp"
        base = {name: (body if params is None else "")
                for name, (params, body) in index.get("active_macros", {}).get(self.unit, {}).items()}
        self.sink = dict(base, **SINK_PREDEFINED)
        if self.unit == "cpp":
            self.sink["__cplusplus"] = "199711"
        self.tu = {k: v for k, v in base.items()}
        self.tu.update(tu_defines)
        for name in removed:  # /U
            self.tu.pop(name, None)
        self.tu.update(local_defines)
        self.delta = {k for k in set(self.sink) | set(self.tu)
                      if _norm_space(self.sink.get(k, "\0")) != _norm_space(self.tu.get(k, "\0"))}
        # a predefined setting the unit lacks (-DWIN32, /MD, /EHsc)
        for k in SINK_PREDEFINED:
            if k not in tu_defines and k not in local_defines:
                self.tu.pop(k, None)
                self.delta.add(k)
        self._dep = {}

    def depends(self, ident, depth=0):
        """Whether #if identifier `ident` can differ under the unit: it is in
        the delta, or a macro whose definitions sit under such a condition."""
        if ident in self.delta:
            return True
        if ident in FIXED_IDENTS:
            # predefined by the compiler (a /U lands in the delta): a header's
            # `#define _WIN32` under `#ifdef WIN32` changes nothing
            return False
        if ident in self._dep:
            return self._dep[ident]
        self._dep[ident] = False  # cycle guard
        got = False
        if depth < 6:
            for e in self.index["entries"].get(ident, ()):
                if e["k"] != "macro":
                    continue
                chain = site_chain(self.index, e)
                if chain is None or any(self.depends(x, depth + 1) for x in chain_idents(chain)):
                    got = True
                    break
        self._dep[ident] = got
        return got

    def trusted(self, e):
        """True when the real definition `e` holds under the unit's
        configuration, False when it is inactive there, None when unknown."""
        chain = site_chain(self.index, e)
        active = e["pp"] or (e["k"] == "macro" and (e["d"].get("active") or {}).get(self.unit) is not None)
        if active:
            if not self.delta:
                return True
            if chain is None:
                return None
            if not any(self.depends(x) for x in chain_idents(chain)):
                return self._text_trusted(e)
        elif chain is None:
            return None
        got = chain_value(chain, self.tu)
        return self._text_trusted(e) if got else got

    def _text_trusted(self, e):
        """The index expanded `e` under the kitchen-sink configuration: its
        text holds for the unit only when no macro it uses (DECLARE_HANDLE,
        whose STRICT form /DNO_STRICT turns off) and no conditional inside it
        can differ there. None (unknown) otherwise; this is no re-derivation
        under the unit's flags, so it never claims more than the sink proves.
        _CRTIMP is exempt: the comparer models its dllimport per unit."""
        if not self.delta:
            return True
        idents = decl_idents(self.index, e)
        if idents is None:
            return None
        if any(self.depends(x) for x in idents - TEXT_MODELLED):
            return None
        return True

    def describe(self, e, limit=4):
        """The conditions that decide `e` under the unit."""
        chain = site_chain(self.index, e)
        if chain is None:
            return f"{e['f']} unreadable"
        names = sorted(x for x in chain_idents(chain) if self.depends(x)) or sorted(chain_idents(chain))
        return ", ".join(names[:limit]) or "no condition evaluated"


# --------------------------------------------------------------------------
# Include closure: the project headers a unit includes
# --------------------------------------------------------------------------

_INCLUDE_FLAG = re.compile(r'(?:^|\s)[-/]I\s*"?([^\s"]+)"?')


def include_dirs(flags):
    out = []
    for m in _INCLUDE_FLAG.finditer(flags):
        p = Path(m.group(1))
        out.append(p if p.is_absolute() else ROOT / p)
    return out


def _rel(path):
    try:
        return Path(os.path.normpath(path)).relative_to(ROOT).as_posix()
    except ValueError:
        return None


def resolve_include(header, angled, includer_dirs, idirs, index, stlport):
    """('local', repo path) | ('ms', None) | ('vendor', None) | ('missing', None)
    for one #include, searched as cl does: the includers' directories (quoted
    only), then -I, then INCLUDE (STLport, the Microsoft roots)."""
    dirs = ([] if angled else list(includer_dirs)) + list(idirs)
    for d in dirs:
        cand = Path(d) / header
        if cand.is_file():
            rel = _rel(cand)
            if rel is None:
                return "ms", None
            return ("vendor", None) if rel.startswith("vendor/") else ("local", rel)
    if stlport:
        cand = ROOT / "vendor" / "stlport" / "stlport" / header
        if cand.is_file():
            return "vendor", None
    for _, root in index.get("roots", []):
        if (Path(root) / header).is_file():
            return "ms", None
    if header.rsplit("/", 1)[-1].lower() in ms_header_basenames(index):
        return "ms", None
    return "missing", None


_HEADER_SCANS = {}


def _closure_blockers(hpath, hres, index):
    """What an included project header's own definitions mean for a unit
    that would include the real header: differences, identical types and
    bodies (a redefinition once the real header comes in), shims."""
    out = []
    if hres.get("error"):
        return [(hpath, 0, "", "include", "unknown", f"analysis of the included header failed ({hres['error']})")]
    cls = classify(hpath, hres, index)[0]
    reach = index.get("core_order", {})
    for o in hres["occ"]:
        line, name, kind, sev = o[0], o[1], o[2], o[3]
        if sev == "collision" and o[6] in reach:
            out.append((hpath, line, name, kind, "mangle",
                        f"included {hpath}:{line} defines its own {kind} {name}; with the real header "
                        f"({o[5]}) it is a redefinition: rename it first"))
            continue
        if sev in NOT_DEFINITIONS:
            continue
        if sev == "same":
            if kind in ("struct", "class", "union", "enum") or o[4] == "identical inline body":
                out.append((hpath, line, name, kind, "source",
                            f"{kind} {name} is defined in included {hpath}:{line}; with the real header "
                            f"it is a redefinition: migrate that header first"))
            continue
        out.append((hpath, line, name, kind, sev, f"included {hpath}:{line} defines {kind} {name} ({o[4]})"))
    if cls == "shim":
        out.append((hpath, 0, "", "include", "unknown", f"included {hpath} stands in for a Microsoft header"))
    return out


def include_closure(path, includes, flags, text, index):
    """(blockers, local defines) of the project headers `path` reaches."""
    idirs = include_dirs(flags)
    stlport = bool(re.search(r"^// stlport[ \t]*$", text[:20000], re.M))
    blockers, macros = [], {}
    seen = {path}
    work = [(path, includes, [(ROOT / path).parent])]
    while work:
        _tick()
        cur, incs, chain_dirs = work.pop()
        for line, header, angled in incs:
            kind, rel = resolve_include(header, angled, chain_dirs, idirs, index, stlport)
            if kind == "missing":
                blockers.append((cur, line, header, "include", "unknown",
                                 f"unresolved include {'<' if angled else chr(34)}{header}"
                                 f"{'>' if angled else chr(34)} at {cur}:{line}: its definitions are unchecked"))
                continue
            if kind != "local" or rel in seen:
                continue
            seen.add(rel)
            hres = _HEADER_SCANS.get(rel)
            if hres is None:
                try:
                    htext = (ROOT / rel).read_text(encoding="latin-1")
                except OSError:
                    htext = ""
                hres = scan_text(rel, htext, index, closure=False)
                _HEADER_SCANS[rel] = hres
            blockers.extend(_closure_blockers(rel, hres, index))
            for name, value in hres.get("defines", {}).items():
                macros.setdefault(name, value)
            work.append((rel, hres.get("includes", []), [(ROOT / rel).parent] + chain_dirs))
    return blockers, macros


# --------------------------------------------------------------------------
# Scan
# --------------------------------------------------------------------------

_CL_LINE = re.compile(r"^//\s*cl:(.*)$", re.M)


def file_flags(text):
    flags = " ".join(m.group(1) for m in _CL_LINE.finditer(text[:20000]))
    return flags


def file_undefs(flags):
    """/U NAME: a predefinition or an earlier /D the unit removes (cl applies
    /U after every /D)."""
    return {m.group(1) for m in re.finditer(r"(?:^|\s)[-/]U\s*\"?([A-Za-z_]\w*)", flags)}


def file_defines(text, lang, path):
    flags = file_flags(text)
    defines = {"_WIN32": "1", "_M_IX86": "600", "_MSC_VER": "1310", "_MSC_FULL_VER": "13103077",
               "_INTEGRAL_MAX_BITS": "64", "_MSC_EXTENSIONS": "1"}
    if lang == "cpp":
        defines["__cplusplus"] = "199711"
    md = bool(re.search(r"[-/]MDd?\b", flags)) or path.startswith("vendor/")
    if md:
        defines["_DLL"] = "1"
        defines["_MT"] = "1"
    if re.search(r"[-/]MTd?\b", flags):
        defines["_MT"] = "1"
    if re.search(r"[-/]M[DTL]d\b", flags):
        defines["_DEBUG"] = "1"
    if re.search(r"[-/]EH[sa]", flags):
        defines["_CPPUNWIND"] = "1"
    if re.search(r"[-/]GR\b(?!-)", flags):
        defines["_CPPRTTI"] = "1"
    for m in re.finditer(r"[-/]D\s*\"?([A-Za-z_]\w*)(?:=([^\s\"]*))?", flags):
        defines[m.group(1)] = m.group(2) if m.group(2) is not None else "1"
    for name in file_undefs(flags):
        defines.pop(name, None)
    pm = re.search(r"[-/]Zp(\d+)", flags)
    pack = int(pm.group(1)) if pm else 8
    return defines, md, pack, flags


def scanned_path(path):
    if not path.startswith(SCAN_PREFIXES):
        return False
    if path.startswith("Code/gen_asm/"):
        return False
    suffix = os.path.splitext(path)[1].lower()
    if path.startswith("vendor/stlport/"):
        # extensionless standard headers (vector, map ...), not the build
        # scripts under config/ or the READMEs
        return suffix in SOURCE_SUFFIXES or (suffix == "" and "/config/" not in path
                                             and not path.rsplit("/", 1)[-1].isupper()
                                             and "README" not in path)
    return suffix in SOURCE_SUFFIXES


def tracked_files():
    out = subprocess.run(["git", "ls-files", "-z", "--", *SCAN_PREFIXES], cwd=ROOT,
                         capture_output=True).stdout.decode("utf-8", "surrogateescape")
    return [p for p in out.split("\0") if p and scanned_path(p)]


_WORKER = {}


def _worker_init(index_path):
    with open(index_path, "rb") as handle:
        index = pickle.load(handle)
    _WORKER["index"] = index
    _WORKER["lookup"] = {"cpp": _ms_lookup(index, "cpp"), "c": _ms_lookup(index, "c")}


def _ms_lookup(index, unit):
    table = index["active_macros"].get(unit, {})
    raw = index["raw_macros"]
    cache = {}
    names = index["entries"]

    def expandable(name, in_ms):
        if in_ms:
            return True
        if name == "interface":
            return True
        return bool(re.fullmatch(r"[A-Z_][A-Z0-9_]*", name)) and not name.startswith("__MSA")

    def lookup(name, in_ms):
        key = (name, in_ms)
        if key in cache:
            return cache[key]
        got = None
        if expandable(name, in_ms):
            if name in table:
                params, body = table[name]
                if params is None:
                    rep = tokenize(body)
                    got = (None, tuple(zip(rep.K, rep.S)), True)
                elif name in raw:
                    got = (raw[name][0], raw[name][1], True)
            elif name in raw and not in_ms:
                got = None  # inactive in the default configuration
            elif name in raw:
                got = (raw[name][0], raw[name][1], True)
            if got is not None and not in_ms:
                kinds = got[1]
                # value macros (numbers, strings) never expand in local code:
                # a local `enum { MAX_PATH = 260 }` must keep its name
                if any(k in ("N", "S", "C") for k, _ in kinds):
                    got = None
        cache[key] = got
        return got
    return lookup


def scan_text(path, text, index, lookup=None, closure=True, timeout=None):
    """Occurrences of Microsoft names a file defines or declares locally:
    [(line, name, kind, severity, reason, real site, entry)] plus file facts.

    With `closure`, the project headers the file includes are scanned too:
    their differences and redefinitions land in "closure", their macros in
    the configuration "same" is checked under. An analysis that runs past
    `timeout` seconds (FILE_TIMEOUT) or recurses too deep returns "error"
    and no verdict: callers treat it as unknown, never as clean."""
    suffix = os.path.splitext(path)[1].lower()
    lang = "c" if suffix == ".c" else "cpp"
    defines, md, pack, flags = file_defines(text, lang, path)
    outer = _DEADLINE[0] is None
    if outer:
        _DEADLINE[0] = time.monotonic() + (FILE_TIMEOUT if timeout is None else timeout)
    try:
        return _scan_text(path, text, index, lookup or _ms_lookup(index, lang), closure,
                          lang, defines, md, pack, flags)
    except (RecursionError, AnalysisIncomplete) as exc:
        if not outer:
            raise  # an included header's scan: the unit fails, the header is not cached
        reason = "timeout" if isinstance(exc, AnalysisIncomplete) else "recursion"
        return {"error": reason, "occ": [], "closure": [], "includes": [], "defines": {}, "md": md,
                "flags": flags, "lang": lang, "ndecl": 0}
    finally:
        if outer:
            _DEADLINE[0] = None


def _scan_text(path, text, index, lookup, closure, lang, defines, md, pack, flags):
    # the unit's own conditionals evaluate tri-state (cond_value); one that
    # does not reduce, or tests a macro an include may define, is unresolved
    info = {}
    decls, macros, includes = parse_text(text, lang, defines, True, lookup, pack,
                                         maybe=index.get("raw_macros", {}), info=info)
    local_defines = {name: (" ".join(s for _, s in defs[-1][1]) if defs[-1][0] is None else "")
                     for name, defs in macros.items()}
    blockers, closure_defines = include_closure(path, includes, flags, text, index) if closure else ([], {})
    unresolved = [f"line {line}: {expr}" for line, expr in info.get("hard", ())]
    unresolved += [f"{name} (an included project header defines it)"
                   for name in sorted(info.get("assumed", set()) & set(closure_defines))]
    config = UnitConfig(index, lang, defines, dict(closure_defines, **local_defines), file_undefs(flags))
    entries = index["entries"]
    # the real CRT prototypes import only when _CRTIMP stays dllimport: /MD
    # without a `-D_CRTIMP=` or a local `#define _CRTIMP` that empties it
    crt_dll = md
    if "_CRTIMP" in macros:
        crt_dll = "dllimport" in " ".join(s for _, s in macros["_CRTIMP"][0][1])
    elif "_CRTIMP" in defines:
        crt_dll = "dllimport" in (defines["_CRTIMP"] or "")
    comparer = Comparer(index, lang, decls, crt_dll, macros)
    reach = index.get("core_order", {})

    def under_config(sev, why, e):
        # identical text proves nothing when the real definition sits in a
        # branch the unit's configuration does not take
        if sev != "same" or not e:
            return sev, why
        if unresolved:
            return "unknown", f"identical text, but this unit's conditionals do not resolve " \
                              f"({'; '.join(unresolved[:2])})"
        ok = config.trusted(e)
        if ok is True:
            return sev, why
        state = "inactive" if ok is False else "not verifiable"
        return "unknown", f"identical text, but the real definition is {state} under this unit's " \
                          f"configuration ({config.describe(e)})"

    occ = []
    for d in decls:
        if d.name not in entries:
            continue
        res = comparer.compare(d)
        if res is None:
            continue
        sev, why, e = res
        if e and sev not in ("same", "fwd", "impl") and d.kind in ("struct", "class", "union", "typedef", "enum") \
                and e["f"] not in reach:
            # a game type that differs from one only a header outside windows.h's
            # and the CRT's reach declares (Parameter in adoint.h)
            sev, why = "collision", f"differs from a type only {e['f'].rsplit('/', 1)[-1]} declares ({why})"
        sev, why = under_config(sev, why, e)
        occ.append((d.line, d.name, d.kind, sev, why, f"{e['f']}:{e['l']}" if e else "", e["f"] if e else ""))
    for name, defs in macros.items():
        if name not in entries:
            continue
        for params, body, line in defs:
            res = comparer.compare_macro(name, params, body, line)
            if res is None:
                continue
            sev, why, e = res
            sev, why = under_config(sev, why, e)
            occ.append((line, name, "macro", sev, why, f"{e['f']}:{e['l']}", e["f"]))
    if unresolved:
        # the C reading dropped branches it could not decide: what they define
        # is unknown too, never absent
        seen = {(o[0], o[1]) for o in occ}
        why = f"in a branch this unit's conditionals do not resolve ({'; '.join(unresolved[:2])})"
        all_decls, all_macros, _ = parse_text(text, lang, defines, False, lookup, pack)
        for d in all_decls:
            if d.name not in entries or (d.line, d.name) in seen:
                continue
            res = comparer.compare(d)
            if res is not None:
                e = res[2]
                sev = res[0] if res[0] in NOT_DEFINITIONS else "unknown"
                occ.append((d.line, d.name, d.kind, sev, why, f"{e['f']}:{e['l']}" if e else "",
                            e["f"] if e else ""))
        for name, defs in all_macros.items():
            for params, body, line in defs:
                if name not in entries or (line, name) in seen:
                    continue
                res = comparer.compare_macro(name, params, body, line)
                if res is not None:
                    e = res[2]
                    sev = res[0] if res[0] in NOT_DEFINITIONS else "unknown"
                    occ.append((line, name, "macro", sev, why, f"{e['f']}:{e['l']}", e["f"]))
    occ.sort()
    return {"occ": occ, "closure": blockers, "includes": includes, "defines": local_defines, "md": md,
            "flags": flags, "lang": lang, "ndecl": len(decls) + sum(len(v) for v in macros.values())}


def _scan_one(path):
    try:
        text = (ROOT / path).read_text(encoding="latin-1")
    except OSError:
        return path, None
    index = _WORKER["index"]
    lang = "c" if path.lower().endswith(".c") else "cpp"
    try:
        # scan_text bounds the file (closure included) by FILE_TIMEOUT
        return path, scan_text(path, text, index, _WORKER["lookup"][lang])
    except Exception as exc:  # report, never hide
        _DEADLINE[0] = None
        return path, {"error": f"{type(exc).__name__}: {exc}", "occ": [], "closure": [], "includes": [],
                      "defines": {}, "md": False, "flags": "", "lang": lang, "ndecl": 0}


def index_path_for(roots):
    return CACHE_DIR / f"index-{index_key(roots)}.pickle"


def scan_files(paths, roots, jobs):
    load_index(roots)
    ipath = index_path_for(roots)
    results = {}
    if jobs <= 1:
        _worker_init(ipath)
        for p in paths:
            results[p] = _scan_one(p)[1]
        return results
    with concurrent.futures.ProcessPoolExecutor(max_workers=jobs, initializer=_worker_init,
                                                initargs=(str(ipath),)) as pool:
        for path, res in pool.map(_scan_one, paths, chunksize=32):
            results[path] = res
    return results


def ms_header_basenames(index):
    got = index.get("_basenames")
    if got is None:
        names = list(index["public"]) + [h for h in index["public"].values() if h]
        got = index["_basenames"] = {name.rsplit("/", 1)[-1].lower() for name in names}
    return got


# static analysis ranks work; it proves nothing about bytes
DROP_IN = "drop-in candidate"
PROVE = "prove with ./build.sh: byte gate is the authority"


def class_arg(value):
    """A --class value: `drop-in`, `drop-in-candidate` name the drop-in candidates."""
    return DROP_IN if value in ("drop-in", "drop-in-candidate") else value


def classify(path, res, index):
    """(class, worst severity, counts) for one scanned file: a drop-in
    candidate only when
    every local copy is proven identical under the unit's configuration and
    nothing the unit includes would collide with the real header."""
    counts = collections.Counter(o[3] for o in res["occ"])
    if res.get("error"):
        return "failed", "error", counts
    # forward declarations alone (`class Image;`) never queue a file
    occ = [o for o in res["occ"] if o[3] not in NOT_DEFINITIONS]
    if not occ:
        return None, None, counts
    # a game type sharing a name windows.h or the CRT defines stays, and makes
    # including the real header a redefinition until it is renamed
    reach = index.get("core_order", {})
    clashes = ["mangle" for o in res["occ"] if o[3] == "collision" and o[6] in reach]
    worst = max([o[3] for o in occ] + [b[4] for b in res.get("closure", ())] + clashes, key=SEVERITY.get)
    base = path.rsplit("/", 1)[-1].lower()
    ms_names = ms_header_basenames(index)
    real_defs = len(occ)
    shim = False
    if path.startswith("reference/shims/") and base in ms_names:
        shim = True
    elif path.lower().endswith((".h", ".hpp", ".inl")) and real_defs >= 10 and real_defs * 2 >= max(res["ndecl"], 1):
        shim = True
    if shim:
        return "shim", worst, counts
    if SEVERITY[worst] >= SEVERITY["mangle"]:
        return "conflicting", worst, counts
    if worst == "unverified":
        return "unverified", worst, counts
    if SEVERITY[worst] >= SEVERITY["source"]:
        return "adapt", worst, counts
    return DROP_IN, worst, counts


def owner_of(path):
    if path.startswith("Code/gen_small/"):
        return "tool:gen_small"
    if path.startswith("vendor/"):
        return "vendored"
    if path.startswith("reference/shims/"):
        return "shim"
    return "hand"


def suggested_headers(res, index):
    pub = index["public"]
    out = collections.Counter()
    for o in res["occ"]:
        if o[3] in ("collision",):
            continue
        label = o[6]
        if label:
            out[pub.get(label, label.rsplit("/", 1)[-1])] += 1
    return [h for h, _ in out.most_common()]


def needs_psdk(headers, index):
    crt = {label[len("Vc7/include/"):].lower() for label in index["public"] if label.startswith("Vc7/include/")}
    crt |= set(STL_PUBLIC.values())
    return any(h.lower() not in crt for h in headers)


COUNTED = ("same", "source", "unknown", "unverified", "mangle", "abi", "fwd", "impl", "collision", "config")
QUEUE_HEADER = ["file", "class", "worst", "defs", *COUNTED, "headers", "platformsdk", "md", "owner",
                "closure", "note", "names"]
CLASS_ORDER = {DROP_IN: 0, "adapt": 1, "unverified": 2, "conflicting": 3, "shim": 4, "failed": 5}
CLASSES = tuple(CLASS_ORDER)


def file_note(res):
    """Advice the class alone does not carry."""
    if res.get("error"):
        return f"analysis incomplete ({res['error']}): unknown, fix the tool or the file"
    if any(VERIFY_CALLEE in o[4] for o in res["occ"]):
        return VERIFY_CALLEE
    return ""


def closure_summary(res, limit=3):
    blockers = res.get("closure", ())
    if not blockers:
        return ""
    parts = [f"{b[0]}:{b[1]} {b[2] or b[3]}({b[4]})" for b in blockers[:limit]]
    return f"{len(blockers)}: " + "; ".join(parts)


def write_queue(results, index, queue=QUEUE, occurrences=OCCURRENCES):
    rows = []
    occ_lines = ["file\tline\tname\tkind\tseverity\treal\treason"]
    for path in sorted(results):
        res = results[path]
        if not res or not (res["occ"] or res.get("error")):
            continue
        for o in res["occ"]:
            occ_lines.append(f"{path}\t{o[0]}\t{o[1]}\t{o[2]}\t{o[3]}\t{o[5]}\t{o[4]}")
        for b in res.get("closure", ()):
            occ_lines.append(f"{path}\t\t{b[2]}\tvia-include\t{b[4]}\t{b[0]}:{b[1]}\t{b[5]}")
        cls, worst, counts = classify(path, res, index)
        if cls is None:
            continue
        headers = suggested_headers(res, index)
        names = []
        for o in sorted(res["occ"], key=lambda o: -SEVERITY[o[3]]):
            if o[3] in NOT_DEFINITIONS:
                continue
            names.append(f"{o[1]}:{o[3]}")
        defs = sum(counts[k] for k in ("same", "source", "unknown", "unverified", "mangle", "abi", "fwd"))
        rows.append([path, cls, worst, str(defs)] + [str(counts[k]) for k in COUNTED] +
                    [",".join(f"<{h}>" for h in headers[:6]), "yes" if needs_psdk(headers, index) else "no",
                     "yes" if res["md"] else "no", owner_of(path), closure_summary(res),
                     file_note(res) or (PROVE if cls == DROP_IN else ""),
                     ",".join(dict.fromkeys(names))[:600]])
    owner = QUEUE_HEADER.index("owner")
    rows.sort(key=lambda r: (CLASS_ORDER[r[1]], r[owner] != "hand", -int(r[3]), r[0]))
    queue.parent.mkdir(parents=True, exist_ok=True)
    with queue.open("w", newline="\n") as handle:
        handle.write("\t".join(QUEUE_HEADER) + "\n")
        for r in rows:
            handle.write("\t".join(r) + "\n")
    occurrences.parent.mkdir(parents=True, exist_ok=True)
    occurrences.write_text("\n".join(occ_lines) + "\n", newline="\n")
    return rows


def refresh_queue(results, index, removed=(), queue=QUEUE, occurrences=OCCURRENCES):
    """Rescan a changed scope without dropping unrelated queued debt.

    Consolidation must classify the resulting TU, rather than renaming several
    donor rows to duplicate destination rows or retaining vanished paths.
    Unaffected records (including their existing evidence) stay byte-for-byte.
    Returns whether the tracked queue changed; occurrences are a local cache.
    """
    affected = set(results) | set(removed)

    def merge(path, fresh):
        if not path.exists():
            return fresh
        old = path.read_bytes().splitlines(keepends=True)
        new = fresh.splitlines(keepends=True)
        if not old or old[0].rstrip(b"\r\n") != new[0].rstrip(b"\r\n"):
            raise ValueError(f"unexpected Microsoft-header report header: {path}")
        kept = [line for line in old[1:]
                if line.split(b"\t", 1)[0].decode("utf-8") not in affected]
        return old[0] + b"".join(kept + new[1:])

    with tempfile.TemporaryDirectory(prefix="ms-header-refresh-") as tmp:
        fresh_queue, fresh_occ = Path(tmp) / "queue.tsv", Path(tmp) / "occurrences.tsv"
        write_queue(results, index, queue=fresh_queue, occurrences=fresh_occ)
        queue_raw = merge(queue, fresh_queue.read_bytes())
        occ_raw = merge(occurrences, fresh_occ.read_bytes())
    changed = not queue.exists() or queue.read_bytes() != queue_raw
    queue.parent.mkdir(parents=True, exist_ok=True)
    queue.write_bytes(queue_raw)
    occurrences.parent.mkdir(parents=True, exist_ok=True)
    occurrences.write_bytes(occ_raw)
    return changed


def summarize(results, index, rows=None):
    files = collections.Counter()
    occ = collections.Counter()
    kinds = collections.Counter()
    by_name = collections.Counter()
    dll_files = set()
    errors = [p for p, r in results.items() if r and r.get("error")]
    for path, res in results.items():
        if not res:
            continue
        cls, worst, counts = classify(path, res, index)
        if cls:
            files[cls] += 1
        for o in res["occ"]:
            occ[o[3]] += 1
            if o[3] not in NOT_DEFINITIONS:
                kinds[o[2]] += 1
                by_name[o[1]] += 1
            if o[2] == "function" and o[3] not in ("impl", "collision"):
                dll_files.add(path)
    print(f"scanned {len(results)} files; {sum(files.values())} define or declare Microsoft names locally")
    for cls in CLASSES:
        print(f"  {cls:<12} {files[cls]}")
    callee = sum(1 for r in results.values() if r and VERIFY_CALLEE in file_note(r))
    print(f"files whose CRT dllimport conflicts need the callee verified per body: {callee}")
    print("occurrences by severity: " + ", ".join(f"{k}={v}" for k, v in occ.most_common()))
    print("occurrences by kind:     " + ", ".join(f"{k}={v}" for k, v in kinds.most_common()))
    print(f"files with local Microsoft prototypes: {len(dll_files)}")
    print("most copied names: " + ", ".join(f"{n}={c}" for n, c in by_name.most_common(25)))
    if errors:
        print(f"{len(errors)} files failed analysis (class failed, unknown): {errors[:5]}")


# --------------------------------------------------------------------------
# check(): the pre-commit gate
# --------------------------------------------------------------------------

def git_blob(spec):
    result = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return None
    return result.stdout.decode("latin-1")


def _definition_keys(path, text, index, timeout=None):
    # forward declarations and configuration macros define nothing
    res = scan_text(path, text, index, closure=False, timeout=timeout)
    keys = collections.Counter()
    for o in res["occ"]:
        if o[3] in NOT_DEFINITIONS:
            continue
        keys[(o[1], o[2])] += 1
    return keys, res


def check(paths, *, read_new=None, read_old=None, index=None, roots=None, renames=None, timeout=None):
    """Problems (strings) for local Microsoft-header definitions `paths` add.

    `read_new(path)` gives the text to vet (default: the staged blob),
    `read_old(path)` the previous text (default: HEAD's blob; None for a new
    file), asked for the rename source in `renames` ({new path: old path},
    from `git diff --cached -M`) when the file moved. A definition counts as
    new when its (name, kind) occurs more often than in the previous text, so
    moving or reformatting one is admitted. A file whose analysis does not
    finish (timeout, recursion) is refused: unknown is never clean."""
    renames = renames or {}
    read_new = read_new or (lambda p: git_blob(f":{p}"))
    read_old = read_old or (lambda p: git_blob(f"HEAD:{p}"))
    index = index or load_index(roots)
    problems = []
    for path in paths:
        if not scanned_path(path):
            continue
        new = read_new(path)
        if new is None:
            continue
        now, res = _definition_keys(path, new, index, timeout)
        if res.get("error"):
            problems.append(f"{path}: analysis incomplete ({res['error']}); its Microsoft-header "
                            f"definitions are unknown, so the file is refused")
            continue
        if not now:
            continue
        source = renames.get(path, path)
        old = read_old(source)
        before = collections.Counter()
        if old:
            before, old_res = _definition_keys(source, old, index, timeout)
            if old_res.get("error"):
                problems.append(f"{path}: analysis of the previous text {source} incomplete "
                                f"({old_res['error']}); cannot tell new definitions from old, refused")
                continue
        added = now - before
        for (name, kind), count in sorted(added.items()):
            sites = [o for o in res["occ"] if o[1] == name and o[2] == kind]
            o = sites[-1]
            header = index["public"].get(o[6], o[6])
            problems.append(f"{path}:{o[0]}: local {kind} {name} ({o[3]}: {o[4]}); "
                            f"include <{header}> instead (real: {o[5]})")
    return problems


def parse_name_status(out):
    """(paths, {new: old}) of `git diff --name-status -z -M` output."""
    fields = out.split("\0")
    paths, renames = [], {}
    i = 0
    while i < len(fields) and fields[i]:
        status = fields[i]
        if status[:1] in ("R", "C"):
            old, new = fields[i + 1], fields[i + 2]
            if status[0] == "R":
                renames[new] = old
            paths.append(new)
            i += 3
        else:
            paths.append(fields[i + 1])
            i += 2
    return [p for p in paths if scanned_path(p)], renames


def staged_changes():
    # no pathspec: a rename from outside the scanned prefixes still maps
    out = subprocess.run(["git", "diff", "--cached", "--name-status", "-z", "-M", "--diff-filter=ACMR"],
                         cwd=ROOT, capture_output=True).stdout.decode("utf-8", "surrogateescape")
    return parse_name_status(out)


def staged_paths():
    return staged_changes()[0]


# --------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------

def read_queue(queue=None):
    queue = queue or QUEUE
    if not queue.exists():
        return []
    lines = queue.read_text().splitlines()
    head = lines[0].split("\t")
    return [dict(zip(head, ln.split("\t"))) for ln in lines[1:] if ln]


def main(argv=None):
    global FILE_TIMEOUT
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = parser.add_subparsers(dest="cmd", required=True)
    p_index = sub.add_parser("index", help="build (or reuse) the Microsoft header index")
    p_index.add_argument("--rebuild", action="store_true")
    p_index.add_argument("--validate", action="store_true")
    p_index.add_argument("--lookup", nargs="*", default=[], help="print the index entries for names")
    p_scan = sub.add_parser("scan", help="scan tracked sources and shims")
    p_scan.add_argument("paths", nargs="*")
    p_scan.add_argument("--write-queue", action="store_true")
    p_show = sub.add_parser("show", help="every occurrence in the given files")
    p_show.add_argument("paths", nargs="+")
    p_next = sub.add_parser("next", help="serve queue rows")
    p_next.add_argument("--class", dest="cls", default=None, type=class_arg, choices=CLASSES)
    p_next.add_argument("--owner", default="hand")
    p_next.add_argument("--limit", type=int, default=10)
    p_check = sub.add_parser("check", help="refuse new local Microsoft-header definitions")
    p_check.add_argument("paths", nargs="*")
    p_check.add_argument("--staged", action="store_true")
    for p in (p_index, p_scan, p_show, p_check):
        p.add_argument("--root", action="append", default=[], metavar="LABEL=DIR",
                       help="an extra Microsoft header root (e.g. the DirectX SDK Include)")
    for p in (p_scan, p_show, p_check):
        p.add_argument("--timeout", type=float, default=None,
                       help=f"seconds per file (default MS_HEADER_FILE_TIMEOUT or {FILE_TIMEOUT:g})")
    for p in (p_scan,):
        p.add_argument("--jobs", type=int, default=int(os.environ.get("BUILD_POOL", "4")))
    args = parser.parse_args(argv)

    if args.cmd == "next":
        if args.cls == DROP_IN or args.cls is None:
            print(f"ms_header_audit: {DROP_IN} rows are static analysis only: {PROVE}", file=sys.stderr)
        rows = [r for r in read_queue() if (args.cls is None or r["class"] == args.cls)
                and (args.owner == "any" or r["owner"] == args.owner)]
        for r in rows[:args.limit]:
            print(f"{r['file']}\t{r['class']}\t{r['defs']} defs\t{r['headers']}"
                  f"{'  // platformsdk' if r['platformsdk'] == 'yes' else ''}"
                  f"{'  NOTE: ' + r['note'] if r.get('note') else ''}")
        return 0

    if getattr(args, "timeout", None) is not None:
        FILE_TIMEOUT = args.timeout
        os.environ["MS_HEADER_FILE_TIMEOUT"] = str(args.timeout)  # pool workers
    roots = default_roots() + parse_root_args(args.root)
    if args.cmd == "index":
        index = load_index(roots, rebuild=args.rebuild)
        print(f"index: {len(index['entries'])} names from {len(index['public'])} headers; "
              f"units: " + ", ".join(f"{k}={len(v)}" for k, v in index["units"].items()))
        for name in args.lookup:
            for e in index["entries"].get(name, []):
                print(f"  {name}: {e['k']} {e['f']}:{e['l']} lang={e['lang']} pp={e['pp']} link={e['link']}")
        if args.validate:
            return 1 if validate(index) else 0
        return 0
    if args.cmd == "check":
        paths, renames = staged_changes() if args.staged else (args.paths, {})
        if not paths:
            return 0
        if args.staged:
            problems = check(paths, roots=roots, renames=renames)
        else:
            problems = check(paths, read_new=lambda p: (ROOT / p).read_text(encoding="latin-1")
                             if (ROOT / p).exists() else None, roots=roots)
        for line in problems:
            print(f"ms_header_audit: {line}", file=sys.stderr)
        if problems:
            print("ms_header_audit: definitions from Microsoft headers must come from the headers "
                  "(the toolchain's Vc7/include, Vc7/PlatformSDK/Include; `// platformsdk` puts the SDK "
                  "on a unit's path)", file=sys.stderr)
        return 1 if problems else 0
    if args.cmd == "show":
        index = load_index(roots)
        for path in args.paths:
            text = (ROOT / path).read_text(encoding="latin-1")
            res = scan_text(path, text, index)
            cls, worst, counts = classify(path, res, index)
            print(f"{path}: {cls or 'clean'}; /MD={'yes' if res['md'] else 'no'}; "
                  f"headers {suggested_headers(res, index)}")
            if file_note(res):
                print(f"  NOTE: {file_note(res)}")
            if cls == DROP_IN:
                print(f"  {PROVE}")
            for o in res["occ"]:
                print(f"  {path}:{o[0]}\t{o[2]:<10} {o[1]:<28} {o[3]:<9} {o[5]}  ({o[4]})")
            for b in res.get("closure", ()):
                print(f"  {b[0]}:{b[1]}\tvia-include {b[2] or b[3]:<28} {b[4]:<9} ({b[5]})")
        return 0
    if args.cmd == "scan":
        paths = args.paths or tracked_files()
        index = load_index(roots)
        results = scan_files(paths, roots, args.jobs)
        rows = write_queue(results, index) if args.write_queue else None
        summarize(results, index, rows)
        if rows is not None:
            print(f"wrote {QUEUE.relative_to(ROOT)} ({len(rows)} files) and "
                  f"{OCCURRENCES.relative_to(ROOT)}")
        return 0
    return 2


if __name__ == "__main__":
    sys.exit(main())
