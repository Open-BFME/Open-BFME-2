#!/usr/bin/env python3
"""Give the sources of one approved TU one shared spelling of each private class view.

WHY. tools/tu_skeleton.py --merge emits a type once when every donor spells it
the same, and otherwise keeps one spelling and lets the compiler and the byte
check judge it. Donors written one function at a time each declare their own
partial view of the classes they touch, under their own member names, so the
kept spelling usually lacks a member another donor reaches (C2039, C2511,
C2248) and the donor is rejected. Seats reconciled those views by hand
(docs/consolidation.md, "Workflow per TU", step 4). This tool does the
mechanical part for one TU; tools/header_adopt_lane.py remains the tree-wide
lane for classes with a canonical header.

WHAT, per class declared privately (a namespace-scope body) in two or more of
the TU's files, exactly as tu_skeleton's donors() selects them:

  1. Layouts come from the compiler (tools/class_layouts.py, CodeView -Z7):
     field offsets and sizes, bases, sizeof and the introducing virtual slots.
  2. Compatibility: fields at one offset and size are one field; padding a
     file never names in code is a gap. A view that stops at its last real
     field claims no sizeof and takes the largest; a file whose compiler lays
     no layout of the class out (nothing there uses it) is no evidence and only
     receives the block. A CONFLICT, reported with its evidence and skipped:
     fields that partition bytes differently or that views type as different
     things (a class by value against an int, float against int; pointers,
     same-size integers and enums, and a pointer held as an int agree), two
     views spelling out different
     sizes (padding past their last real field), different bases or class
     declspecs, a virtual slot two views fill differently, a real field under
     a vfptr, a member attribute that changes mangling (access, virtual,
     static, const, calling convention, return type, the class-key) on which
     the views disagree and the ledger's mangled names do not settle, two
     inline bodies of one method, an inline body in one view of a method
     another file defines out of line, one member name meaning two members,
     or a construct the source reader does not model (bitfields, anonymous
     unions, member templates, a definition inside #if).
  3. One superset view: fields in offset order with gaps as `char m_padXX[n]`,
     each named from the seed (the TU file, else the donor whose first row
     comes first in retail order) where it has the field, else from the first
     donor that does; the union of methods, nested types, statics and
     friends; introducing virtuals in the order of the view that declares the
     most slots. No name is invented. A typedef alias some file never names is
     spelled as the builtin type it stands for (typedefs change no layout, code
     or mangled name).
  4. Each file's definition is replaced by the identical block, preceded where
     that file needs them by `class X;` for classes the block's declarations
     name first (keyed as the compiler recorded them in the TU's files) and by
     the verbatim definition of a namespace-scope enum another TU file defines
     (VC7.1 cannot forward-declare an enum; the merge emits it once). The
     file's references to its own field names are renamed to the superset's, token
     by token outside comments and strings. A rename is refused (and the class
     skipped) when the new name already occurs in the file, or the old name is
     also a member of another class or a file-scope name there.
  5. Verification, one class at a time (bases first): the rewritten files'
     layouts are read again and must equal the plan, `./build.sh` must report
     every touched file exact (never build.compile_source or tools/build.py
     by hand; docs/matching.md, "The build cache trap"), and
     find_declared_unmatched must report nothing new. A class failing any of
     these is restored in all its files; classes reverted once are retried
     after the others land.

Classes registered in reverse/canonical_classes.csv are reported as
header-lane work (tools/header_adopt_lane.py) and never written: class_gate
refuses a new private copy of them.

Applying also runs `tu_skeleton.py --merge TU --dry-run` before and after and
reports the donors it accepts. The tool never commits and never claims: claim
`file:` for the TU's files first (docs/claims.md); it refuses files another
worker holds.

Usage:
  python3 tools/tu_views.py TU [--dry-run] [--class NAME ...] [--json FILE] [--no-merge-check]
"""
import argparse
import ast
import collections
import csv
import functools
import json
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import class_layouts  # noqa: E402
import header_adopt_lane as hal  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
CANONICAL = ROOT / "reverse" / "canonical_classes.csv"
ACCESS = re.compile(r"^(public|protected|private)\s*:(?!:)\s*")
PAD = re.compile(r"^(m_)?_?(pad|unk|gap|reserved|unused|before)", re.I)
# A padding member another class of the same file declares: `char m_pad[0x1C];`
PAD_DECL = re.compile(r"(?<![\w.>])(?!(?:return|throw|delete|case|goto|sizeof)\b)[A-Za-z_]\w*[\s*]+"
                      r"((?:m_)?_?(?:pad|unk|gap|reserved|unused|before)\w*)\s*(?:\[[^\];\n]*\]\s*)*;", re.I)
CALLCONV = ("__cdecl", "__stdcall", "__fastcall", "__thiscall")
TYPE_WORDS = set("const volatile unsigned signed int char short long float double bool void wchar_t __int64 "
                 "__int32 __int16 __int8 struct class enum union".split())
IDENT = re.compile(r"[A-Za-z_]\w*")
DECLSPEC = re.compile(r"__declspec\s*\((?:[^()]|\([^()]*\))*\)")
# MSVC member-function codes: the letter after `@@` gives (access, kind)
MEMBER_CODE = {}
for _letters, _access in (("ABCDEFGH", "private"), ("IJKLMNOP", "protected"), ("QRSTUVWX", "public")):
    for _i, _ch in enumerate(_letters):
        MEMBER_CODE[_ch] = (_access, ("plain", "plain", "static", "static", "virtual", "virtual",
                                      "thunk", "thunk")[_i])
CC_CODE = {"A": "__cdecl", "E": "__thiscall", "G": "__stdcall", "I": "__fastcall"}
SPECIAL = {"operator=": "?4", "operator==": "?8", "operator!=": "?9", "operator[]": "?A", "operator->": "?C",
           "operator()": "?R"}


class Refused(Exception):
    """A class the tool will not write; the message is the evidence."""


# ---------------------------------------------------------------- source reading
def no_comments(text):
    """`text` with comments blanked (same length); string literals kept."""
    return re.sub(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?',
                  lambda m: re.sub(r"[^\n]", " ", m.group()) if m.group().startswith("/") else m.group(),
                  text, flags=re.S)


@functools.lru_cache(maxsize=4096)
def head_re(name):
    return re.compile(r"^[ \t]*(template\s*<[^;{}]*>\s*)?(class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)*"
                      + re.escape(name) + r"\b\s*(?::(?!:)[^{;]*)?\{", re.M)


def class_span(text, name, code=None):
    """(start, end) of the one namespace-scope definition of `name`, from its head line
    to the closing `;` and newline. Raises Refused for a template, two definitions or
    a definition inside a preprocessor conditional; None when there is none."""
    code = code if code is not None else hal.masked(text)
    found = []
    for m in head_re(name).finditer(code):
        if depth_at(code, m.start()):
            continue
        if m.group(1):
            raise Refused(f"{name} is a template")
        depth, i = 1, m.end()
        while depth and i < len(code):
            depth += (code[i] == "{") - (code[i] == "}")
            i += 1
        tail = re.match(r"[ \t]*;[ \t]*\r?\n?", code[i:])
        if depth or not tail:
            raise Refused(f"{name}: unterminated definition")
        found.append((m.start(), i + tail.end()))
    if len(found) > 1:
        raise Refused(f"{name} is defined {len(found)} times in one file")
    if not found:
        return None
    opened = len(re.findall(r"(?m)^[ \t]*#[ \t]*if", code[:found[0][0]]))
    closed = len(re.findall(r"(?m)^[ \t]*#[ \t]*endif", code[:found[0][0]]))
    if opened != closed:
        raise Refused(f"{name} is defined inside a preprocessor conditional")
    return found[0]


def depth_at(code, pos):
    return code.count("{", 0, pos) - code.count("}", 0, pos)


def split_top(text, sep):
    """`text` split at `sep` outside (), [], <> and {}."""
    out, buf, depth = [], "", 0
    for ch in text:
        if ch in "([{<":
            depth += 1
        elif ch in ")]}>":
            depth -= 1
        if ch == sep and depth == 0:
            out.append(buf)
            buf = ""
        else:
            buf += ch
    out.append(buf)
    return out


def ws(text):
    return re.sub(r"\s+", " ", text).strip()


def type_norm(text, typedefs):
    """A parameter or return type, spelled canonically: typedefs resolved, elaborated
    keys and by-value const dropped, `unsigned` alone is `unsigned int`."""
    t = re.sub(r"\b(struct|class|enum|union)\s+", "", text)
    for _ in range(4):
        t = IDENT.sub(lambda m: typedefs.get(m.group(), m.group()), t)
    t = re.sub(r"\s*([*&])\s*", r"\1", ws(t))
    t = re.sub(r"\bunsigned(?!\s*(int|char|short|long|__int64)\b)", "unsigned int", t)
    t = re.sub(r"\bsigned\s+int\b", "int", t)
    t = re.sub(r"\blong\s+int\b", "long", t)
    t = re.sub(r"\bshort\s+int\b", "short", t)
    t = re.sub(r"^([\w ]*?\w)\s+const\b", r"const \1", t)       # `int const` is `const int`
    if not re.search(r"[*&]", t):
        t = re.sub(r"^const\s+", "", t)                           # by value: const is not the type's
    return re.sub(r"\*const$", "*", t)


def param_types(params, typedefs):
    p = ws(params)
    if p in ("", "void"):
        return ()
    out = []
    for part in split_top(p, ","):
        part = split_top(part, "=")[0].strip()                    # default argument
        if part == "...":
            out.append("...")
            continue
        arr = re.search(r"(\[[^\]]*\])+$", part)
        if arr:                                                   # `T a[4]` is `T *`
            part = part[:arr.start()].strip() + "*"
        words = IDENT.findall(part)
        last = re.search(r"([A-Za-z_]\w*)\s*$", part)
        if len(words) > 1 and last and last.group(1) not in TYPE_WORDS \
                and not re.search(r"::\s*" + last.group(1) + r"$", part):
            part = part[:last.start(1)]                           # the parameter's name
        out.append(type_norm(part, typedefs))
    return tuple(out)


def file_typedefs(text):
    """{alias: spelling} of the simple file-scope typedefs, over header_adopt_lane's layer."""
    out = {k: v for k, v in hal.TYPEDEFS.items() if k not in ("TRUE", "FALSE")}
    for m in re.finditer(r"^\s*typedef\s+([^;{}()]+?)\s+([A-Za-z_]\w*)\s*;", hal.masked(text), re.M):
        if ws(m.group(1)) != m.group(2):
            out[m.group(2)] = ws(m.group(1))
    return out


class Member:
    """One member of a class body as the source spells it."""

    def __init__(self, kind, access, text, **kw):
        self.kind, self.access, self.text = kind, access, text
        self.body, self.lead, self.tail, self.text_orig = None, [], "", None
        self.__dict__.update(kw)

    def __repr__(self):
        return f"Member({self.kind} {self.access} {self.text!r})"


def comment_text(text):
    """The words of one `// ...` or `/* ... */` comment."""
    t = text.strip()
    if t.startswith("//"):
        return t.lstrip("/").lstrip("<").strip()
    return re.sub(r"^/\*+|\*+/$", "", t).strip()


def members(body, cls, typedefs, orig=None):
    """[Member] of one class body (comments already blanked; `orig` is the same span
    with its comments, which ride with the member they precede or end the line of).
    Raises Refused on a construct this reader does not model."""
    orig = body if orig is None else orig
    code = hal.masked(body)
    pieces, start, depth, par, i, n = [], 0, 0, 0, 0, len(body)
    while i < n:
        c = code[i]
        if c == "(":
            par += 1
        elif c == ")":
            par -= 1
        elif c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and par == 0:
                j = i + 1
                semi = re.match(r"\s*;", code[j:])
                head = code[start:i]
                if not semi and re.match(r"\s*(?:(?:public|protected|private)\s*:\s*)*(struct|class|union|enum)\b",
                                         head) and re.match(r"\s*[A-Za-z_*&]", code[j:]):
                    raise Refused(f"nested type with a declarator: {ws(body[start:j])[:60]}")
                end = j + (semi.end() if semi else 0)
                pieces.append((start, end))
                start = i = end
                continue
        elif c == ";" and depth == 0 and par == 0:
            pieces.append((start, i + 1))
            start = i + 1
        elif c == ":" and depth == 0 and par == 0 and code[i + 1:i + 2] != ":" and code[i - 1:i] != ":" \
                and re.fullmatch(r"\s*(public|protected|private)\s*", code[start:i]):
            pieces.append((start, i + 1))
            start = i + 1
        i += 1
    if body[start:].strip():
        raise Refused(f"unterminated member: {ws(body[start:])[:60]}")
    out, access, last = [], None, None
    for s, e in pieces + [(start, len(body))]:
        c, o = body[s:e], orig[s:e]
        k = 0
        nl = c.find("\n")
        if nl >= 0 and not c[:nl].strip():           # the rest of the previous member's line
            if last is not None and o[:nl].strip():
                last.tail = comment_text(o[:nl])
            k = nl + 1
        lead = []
        while True:                                    # whole comment lines before the member
            nl = c.find("\n", k)
            if nl < 0 or c[k:nl].strip():
                break
            if o[k:nl].strip():
                lead.append(o[k:nl].strip())
            k = nl + 1
        p = c.strip()
        m = ACCESS.match(p)
        if m and not p[m.end():].strip():
            access = m.group(1)
            continue
        if not p or p == ";":
            continue
        got = member(p, access, cls, typedefs)
        got = got if isinstance(got, list) else [got]
        got[0].lead = lead
        if got[0].kind == "fn" and got[0].body and "\n" in p:
            got[0].text_orig = o[k:].strip()            # a multi-line inline body keeps its comments
        out.extend(got)
        last = got[-1]
    return out


def member(p, access, cls, typedefs):
    s = ws(p)
    if re.match(r"^template\b", s):
        raise Refused(f"member template: {s[:60]}")
    if re.match(r"^(union|struct|class)\s*\{", s):
        raise Refused(f"anonymous aggregate member: {s[:60]}")
    nested = re.match(r"^(typedef|friend|using)\b", s) or (
        re.match(r"^(enum|struct|class|union)\b", s)
        and ("{" in s or re.match(r"^(struct|class|union|enum)\s+[A-Za-z_]\w*\s*;$", s)))
    if nested:
        if s.startswith("typedef"):
            found = re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;?$", re.sub(r"\(.*\)\s*;?$", "", s))
            name = found[0] if found else s
        elif s.startswith(("friend", "using")):
            name = s
        else:
            words = [w for w in IDENT.findall(re.sub(r"\{.*", " ", s, flags=re.S)) if w != "__declspec"]
            name = words[1] if len(words) > 1 else s
        return Member("nested", access, p.rstrip(), name=name, key=("nested", name))
    fn = function(p, cls, typedefs)
    if fn:
        fn.access = access
        return fn
    if ":" in re.sub(r"::", "", s.split("[")[0]):
        raise Refused(f"bitfield: {s[:60]}")
    static = bool(re.match(r"^static\b", s))
    decl = re.sub(r"^static\s+", "", s.rstrip(";").strip())
    parts = split_top(decl, ",")
    m = re.match(r"^(?P<type>.*?)(?P<decl>[\s*&]*\b(?P<name>[A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*)$", parts[0], re.S)
    if not m or not m.group("type").strip():
        raise Refused(f"unreadable data member: {s[:60]}")
    base = m.group("type").strip()
    decls = [m.group("decl").strip()]
    for part in parts[1:]:
        d = re.match(r"^\s*(?P<decl>[\s*&]*\b[A-Za-z_]\w*\s*(?:\[[^\]]*\]\s*)*)$", part)
        if not d:
            raise Refused(f"unreadable declarator: {s[:60]}")
        decls.append(d.group("decl").strip())
    out = []
    for d in decls:
        name = IDENT.findall(re.sub(r"\[[^\]]*\]", "", d))[-1]
        kind = "static" if static else "data"
        out.append(Member(kind, access, f"{'static ' if static else ''}{base} {d};", name=name, base=base,
                          decl=d, key=(kind, name)))
    return out if len(out) > 1 else out[0]


def function(p, cls, typedefs):
    """A Member for a function declaration or inline definition, else None."""
    code = hal.masked(p)
    scan = DECLSPEC.sub(lambda m: " " * len(m.group()), code)
    scan = re.sub(r"\boperator\s*(?:\(\s*\)|[^\sA-Za-z_(]+)", lambda m: "#" * len(m.group()), scan)
    open_, depth = None, 0
    for i, ch in enumerate(scan):
        if ch == "{" or (ch == "=" and depth == 0):
            break
        if ch == "(" and depth == 0:
            open_ = i
            break
        depth += (ch in "<[") - (ch in ">]")
    if open_ is None:
        return None
    if re.match(r"\(\s*(?:[A-Za-z_]\w*\s*::\s*)*\*", scan[open_:]):
        return None                                                  # a pointer to function: data
    depth, close = 0, None
    for i in range(open_, len(scan)):
        depth += (scan[i] == "(") - (scan[i] == ")")
        if depth == 0:
            close = i
            break
    if close is None:
        raise Refused(f"unbalanced declaration: {ws(p)[:60]}")
    pre = p[:open_]
    nm = re.search(r"(~?\s*[A-Za-z_]\w*|operator\s*(?:\(\s*\)|[^\sA-Za-z_(][^\s(]*|\s+[A-Za-z_][\w\s*&]*?))\s*$",
                   pre)
    if not nm:
        raise Refused(f"unreadable function: {ws(p)[:60]}")
    raw = nm.group(1)
    name = ws(raw) if re.match(r"operator\s+[A-Za-z_]", raw) else re.sub(r"\s+", "", raw)
    prefix = pre[:nm.start()]
    after = p[close + 1:]
    b = hal.masked(after).find("{")
    post, body = (after[:b], after[b:].rstrip().rstrip(";").rstrip()) if b >= 0 else (after, None)
    post_s = ws(post).rstrip(";").strip()
    words = ws(prefix)
    virtual = bool(re.search(r"\bvirtual\b", words))
    static = bool(re.search(r"\bstatic\b", words))
    cc = next((c for c in CALLCONV if re.search(r"\b" + c + r"\b", words)), "")
    declspec = " ".join(sorted(re.findall(r"__declspec\s*\(\s*(dllimport|dllexport|noinline|naked)\s*\)", words)))
    ret = re.sub(r"\b(virtual|static|inline|__inline|__forceinline|explicit|" + "|".join(CALLCONV) + r")\b", " ",
                 DECLSPEC.sub(" ", words))
    special = name.lstrip("~") == cls.split("::")[-1] or name.startswith("operator ")
    params = param_types(p[open_ + 1:close], typedefs)
    cv = post_s.split("=")[0].split("throw")[0]
    return Member("fn", None, p.strip(), name=name, params=params, const=bool(re.search(r"\bconst\b", cv)),
                  volatile=bool(re.search(r"\bvolatile\b", cv)), virtual=virtual, static=static, cc=cc, declspec=declspec, body=body,
                  ret="" if special else type_norm(ret, typedefs), key=("fn", name, params))


class View:
    """One file's private view of one class: its source span, members and layout."""

    def __init__(self, path, text, cls, layout, every, inert=False):
        """`inert`: the compiler laid no layout of the class out for this file (nothing
        in it uses the class), so the view is evidence of nothing; it only receives the block."""
        self.path, self.cls, self.layout, self.every, self.inert = path, cls, layout, every, inert
        code = hal.masked(text)
        span = class_span(text, cls, code)
        if not span:
            raise Refused(f"{path}: no namespace-scope definition of {cls}")
        self.span = span
        src = no_comments(text)[span[0]:span[1]]
        msrc = hal.masked(src)
        open_, close = msrc.index("{"), msrc.rindex("}")
        self.head = ws(src[:open_])
        hm = re.match(r"^(class|struct)\s+((?:__declspec\([^)]*\)\s*)*)" + re.escape(cls) + r"\s*(?::(.*))?$",
                      self.head)
        if not hm:
            raise Refused(f"{path}: unreadable class head `{self.head[:60]}`")
        self.key, self.declspec, self.bases = hm.group(1), ws(hm.group(2) or ""), ws(hm.group(3) or "")
        self.typedefs = file_typedefs(text)
        self.members = [] if inert else members(src[open_ + 1:close], cls, self.typedefs,
                                                text[span[0]:span[1]][open_ + 1:close])
        default = "public" if self.key == "struct" else "private"
        cv_virtual = set(layout.get("virtual", []))
        for m in self.members:
            m.access = m.access or default
            m.src = path
            if m.kind == "fn" and m.name in cv_virtual:
                m.virtual = True
        rest = code[:span[0]] + " " * (span[1] - span[0]) + code[span[1]:]
        self.used = collections.Counter(IDENT.findall(rest))          # identifiers outside the class body
        # a padding name counts as used only outside other classes' padding declarations
        self.pad_used = collections.Counter(IDENT.findall(PAD_DECL.sub(";", rest)))
        self.code = code


# ---------------------------------------------------------------- the ledger
def ledger_rows():
    import tu_skeleton
    return tu_skeleton.ledger_rows()


def ledger_class_key(cls, rows):
    """'class' / 'struct' from the matched names that spell `cls` (`V` / `U`), else None;
    'both' when they disagree."""
    pat = re.compile(r"[A-D]([VU])" + re.escape(cls) + "@@")
    seen = {m.group(1) for r in rows for m in pat.finditer(r["name"])}
    return {frozenset("V"): "class", frozenset("U"): "struct", frozenset(): None}.get(frozenset(seen), "both")


def ledger_member_attrs(cls, name, rows):
    """{(access, kind, const, volatile, cc)} that the ledger's mangled names give member `name` of `cls`."""
    if name == cls:
        prefix = "??0" + cls + "@@"
    elif name == "~" + cls:
        prefix = "??1" + cls + "@@"
    elif name in SPECIAL:
        prefix = "?" + SPECIAL[name] + cls + "@@"
    else:
        prefix = "?" + name + "@" + cls + "@@"
    out = set()
    for r in rows:
        n = r["name"]
        if not n.startswith(prefix) or len(n) <= len(prefix) or n[len(prefix)] not in MEMBER_CODE:
            continue
        access, kind = MEMBER_CODE[n[len(prefix)]]
        if kind == "thunk":
            continue
        rest, const, volatile = n[len(prefix) + 1:], False, False
        if kind != "static" and rest:      # the this-pointer cv code: A, B const, C volatile, D both
            const, volatile, rest = rest[0] in "BD", rest[0] in "CD", rest[1:]
        out.add((access, kind, const, volatile, CC_CODE.get(rest[:1], "")))
    return out


# ---------------------------------------------------------------- reconcile
def is_pad(m, view):
    return m.kind == "data" and bool(PAD.match(m.name)) and not view.pad_used.get(m.name)


def field_table(view):
    """{name: (offset, size, cvtype)} for the view's own data members, from CodeView."""
    return {f[1]: (f[0], f[3], f[2]) for f in view.layout.get("fields", [])}


def fn_attr(m, attr):
    if attr == "cc":
        return m.cc or ("__cdecl" if m.static else "__thiscall")
    return getattr(m, attr)


def ledger_attr(entry, attr):
    access, kind, const, volatile, cc = entry
    return {"access": access, "virtual": kind == "virtual", "static": kind == "static", "const": const,
            "volatile": volatile, "cc": cc}[attr]


# Comments and literals; code_text keeps the literals (they are behaviour) and blanks comments.
NON_CODE = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?', re.S)


def code_text(text):
    return NON_CODE.sub(lambda m: m.group() if m.group()[:1] in "\"'" else " ", text)


def merge_fn(cls, a, b, ledger, overloaded=False):
    """The one spelling of a method two views declare, or Refused. `overloaded`: the views
    declare more than one parameter list under this name, so a ledger name matched by its
    prefix may be another overload's and is no evidence."""
    (ma, va), (mb, vb) = a, b
    if ma.body and mb.body and ws(code_text(ma.body)) != ws(code_text(mb.body)):
        raise Refused(f"{cls}::{ma.name}: two different inline bodies ({va.path}, {vb.path})")
    if ma.ret != mb.ret:
        raise Refused(f"{cls}::{ma.name}: return type `{ma.ret}` ({va.path}) vs `{mb.ret}` ({vb.path})")
    if ma.declspec != mb.declspec:
        raise Refused(f"{cls}::{ma.name}: __declspec `{ma.declspec}` ({va.path}) vs `{mb.declspec}` ({vb.path})")
    led = None
    pick, access = ma, ma.access
    for attr in ("virtual", "static", "const", "volatile", "cc", "access"):
        x, y = fn_attr(ma, attr), fn_attr(mb, attr)
        if x == y:
            continue
        if overloaded:
            raise Refused(f"{cls}::{ma.name}: {attr} differs ({va.path} `{x}`, {vb.path} `{y}`) on an overloaded "
                          "name; the ledger's names are not matched to one overload")
        led = ledger_member_attrs(cls, ma.name, ledger) if led is None else led
        want = {ledger_attr(e, attr) for e in led}
        if len(want) != 1:
            raise Refused(f"{cls}::{ma.name}: {attr} differs ({va.path} `{x}`, {vb.path} `{y}`) and the ledger's "
                          f"names {'disagree' if want else 'do not spell it'}")
        w = want.pop()
        if attr == "access":
            access = w
            continue
        if fn_attr(pick, attr) == w:
            continue
        if fn_attr(mb, attr) == w and all(fn_attr(mb, at) == fn_attr(pick, at)
                                          for at in ("virtual", "static", "const", "volatile", "cc") if at != attr):
            pick = mb
            continue
        raise Refused(f"{cls}::{ma.name}: no view spells the ledger's {attr} `{w}`")
    out = Member("fn", access, pick.text, **{k: v for k, v in pick.__dict__.items()
                                             if k not in ("kind", "access", "text")})
    if not out.body and (ma.body or mb.body):
        src = ma if ma.body else mb
        out.text, out.body, out.text_orig, out.src = src.text, src.body, src.text_orig, getattr(src, "src", None)
    return out


def merge_other(cls, a, b, ledger):
    (ma, va), (mb, vb) = a, b
    if ma.kind != mb.kind:
        raise Refused(f"{cls}: `{ws(ma.text)[:50]}` ({va.path}) and `{ws(mb.text)[:50]}` ({vb.path}) "
                      "share a name")
    if ws(ma.text) != ws(mb.text):
        raise Refused(f"{cls}: {va.path} `{ws(ma.text)[:60]}` vs {vb.path} `{ws(mb.text)[:60]}`")
    if ma.access != mb.access:
        if ma.kind == "static":
            raise Refused(f"{cls}::{ma.name}: {va.path} declares it {ma.access}, {vb.path} {mb.access} "
                          "(a static member's access is mangled)")
        return Member(ma.kind, "public", ma.text, **{k: v for k, v in ma.__dict__.items()
                                                     if k not in ("kind", "access", "text")})
    return ma


class Plan:
    def __init__(self, cls):
        self.cls, self.notes, self.renames, self.fields = cls, [], {}, []


def reconcile(cls, views, seed, ledger=()):
    """A Plan whose block every view becomes, or Refused with the evidence."""
    plan = Plan(cls)
    order = sorted(views, key=lambda v: (v.path != seed, views.index(v)))
    first = order[0]
    # -- the head: class-key, declspecs, bases
    keys = {v.key for v in views}
    lk = ledger_class_key(cls, ledger)
    if lk == "both":
        raise Refused(f"the ledger spells {cls} both `class` and `struct`")
    if len(keys) > 1 and not lk:
        raise Refused(f"class-key differs ({', '.join(f'{v.path}: {v.key}' for v in views)}) "
                      "and no matched name spells it")
    key = lk or first.key
    # A view with no bases, class declspec, vfptr or virtual method asserts nothing about
    # the head; it takes the head the other views agree on (its fields must still clear it).
    heads = [v for v in order if not head_free(v)] or order
    for attr, what in (("declspec", "declspec"), ("bases", "base clause")):
        if len({getattr(v, attr) for v in heads}) > 1:
            raise Refused(f"{what} differs: " + "; ".join(f"{v.path}: `{getattr(v, attr) or '-'}`" for v in heads))
    if len({json.dumps(v.layout.get("bases", [])) for v in heads}) > 1:
        raise Refused("bases differ: " + "; ".join(f"{v.path}: {v.layout.get('bases')}" for v in heads))
    if len(heads) < len(order) and (heads[0].bases or heads[0].declspec):
        plan.notes.append(f"{', '.join(v.path for v in order if v not in heads)} declare no base or virtual: "
                          f"they take `{ws(heads[0].declspec + ' ' + cls + (' : ' + heads[0].bases if heads[0].bases else ''))}`")
    vfptr = any(v.layout.get("vfptr") for v in views)
    start = own_start(heads[0], vfptr)
    # -- sizeof: a view stopping at its last real field claims no size; two views that
    # spell different sizes out (padding past their last real field) are a conflict
    size = max(v.layout["size"] for v in views)
    if any(v.layout["size"] != size and claims_size(v, start) for v in views):
        raise Refused("sizeof differs: " + ", ".join(
            f"{v.path} 0x{v.layout['size']:X}{' (spelled out)' if claims_size(v, start) else ''}" for v in views))
    if len({v.layout["size"] for v in views}) > 1:
        plan.notes.append("sizeof 0x%X from %s; %s stop at their last field" % (
            size, next(v.path for v in views if v.layout["size"] == size),
            ", ".join(f"{v.path} (0x{v.layout['size']:X})" for v in views if v.layout["size"] != size)))
    # -- virtual slots: none filled differently, one view holding them all
    slots = {}
    for v in order:
        for s, sig in v.layout.get("vslots", {}).items():
            if slots.setdefault(int(s), (sig, v.path))[0] != sig:
                raise Refused(f"virtual slot {s} differs: {slots[int(s)][1]} `{slots[int(s)][0]}`, {v.path} `{sig}`")
    vmax = max(order, key=lambda v: len(v.layout.get("vslots", {})))
    if len(vmax.layout.get("vslots", {})) != len(slots):
        raise Refused("no one view declares every virtual slot")
    # -- fields
    spans = {}                                              # (offset, size) -> [(view, member, cvtype)]
    for v in order:
        table = field_table(v)
        data = [m for m in v.members if m.kind == "data"]
        if sorted(m.name for m in data) != sorted(table):
            raise Refused(f"{v.path}: source data members {sorted(m.name for m in data)} are not CodeView's "
                          f"{sorted(table)}")
        for m in data:
            off, sz, cv = table[m.name]
            if sz <= 0 or cv == "bitfield" or re.match(r"k[0-9a-f]+$", cv):
                raise Refused(f"{v.path}: member {m.name} has a type the layout reader does not size ({cv})")
            if is_pad(m, v):
                continue
            if off < start:
                raise Refused(f"{v.path}: {m.name} at +0x{off:X} lies under the "
                              f"{'vfptr' if vfptr and not heads[0].layout.get('bases') else 'bases'} "
                              f"(own data starts at +0x{start:X})")
            spans.setdefault((off, sz), []).append((v, m, cv))
    ordered = sorted(spans)
    for (a, asz), (b, bsz) in zip(ordered, ordered[1:]):
        if b < a + asz:
            (va, ma, _), (vb, mb, _) = spans[(a, asz)][0], spans[(b, bsz)][0]
            raise Refused(f"fields overlap: {va.path} {ma.name} +0x{a:X}..0x{a + asz:X}, "
                          f"{vb.path} {mb.name} +0x{b:X}..0x{b + bsz:X}")
    named = {}
    for off, sz in ordered:
        owners = spans[(off, sz)]
        v, m, _ = owners[0]                                 # the seed's, else the first donor's
        if m.name in named:
            raise Refused(f"{m.name} names +0x{named[m.name]:X} and +0x{off:X} in different views")
        named[m.name] = off
        types = sorted({c for _, _, c in owners})
        clash = next(((a, b) for a in types for b in types if not cv_compatible(a, b)), None)
        if clash:
            raise Refused(f"+0x{off:X}: views disagree on what the field is ({clash[0]} vs {clash[1]}: "
                          + ", ".join(f"{ov.path} {om.name}" for ov, om, _ in owners) + ")")
        if len(types) > 1:
            plan.notes.append(f"+0x{off:X} {m.name}: CodeView types differ ({', '.join(types)}); "
                              f"{v.path}'s spelling kept, the byte check decides")
        access = {om.access for _, om, _ in owners}
        if len(access) > 1:
            plan.notes.append(f"+0x{off:X} {m.name}: declared {'/'.join(sorted(access))}; kept public")
            m = Member("data", "public", m.text, **{k: x for k, x in m.__dict__.items()
                                                     if k not in ("kind", "access", "text")})
        plan.fields.append((off, sz, m, v.path))
        for ov, om, _ in owners:
            if om.name != m.name:
                plan.renames.setdefault(ov.path, {})[om.name] = m.name
    # -- methods, statics, nested types (introducing virtuals by slot)
    entries, intro = collections.OrderedDict(), []
    lists = collections.defaultdict(set)        # parameter lists each method name is declared with
    for v in order:
        for m in v.members:
            if m.kind == "fn":
                lists[m.name].add(m.params)
    for v in order:
        own = collections.defaultdict(list)
        for s, sig in sorted(v.layout.get("vslots", {}).items(), key=lambda kv: int(kv[0])):
            name = sig.split("(")[0]
            own["~" + cls.split("::")[-1] if name == "__vecDelDtor" else name].append(int(s))
        nth = collections.Counter()
        dup = collections.Counter(m.key for m in v.members if m.kind == "fn")
        for m in v.members:
            if m.kind == "data":
                continue
            k = m.key
            if m.kind == "fn" and dup[k] > 1:
                k = k + (m.const,)                          # a const/non-const pair in one view
            if m.kind == "fn" and m.virtual and nth[m.name] < len(own.get(m.name, ())):
                k = ("slot", own[m.name][nth[m.name]])
                nth[m.name] += 1
                if v is vmax:
                    intro.append(k)
            if k in entries:
                merged = (merge_fn(cls, entries[k], (m, v), ledger, overloaded=len(lists[m.name]) > 1)
                          if m.kind == "fn" else merge_other(cls, entries[k], (m, v), ledger))
                entries[k] = (merged, entries[k][1])
            else:
                entries[k] = (m, v)
    names = collections.defaultdict(set)
    for k, (m, v) in entries.items():
        names[m.name].add(m.kind)
        if m.kind == "fn" and m.body:
            for w in views:
                if defines_out_of_line(w, cls, m.name):
                    raise Refused(f"{v.path} defines {cls}::{m.name} inline; {w.path} defines it out of line")
    for n in named:
        if n in names:
            raise Refused(f"{n} is a field in one view and a {'/'.join(sorted(names[n]))} member in another")
    for k, (m, v) in list(entries.items()):          # a donor's inline body speaks the superset's names
        mapping = plan.renames.get(getattr(m, "src", None) or v.path)
        if mapping and m.kind == "fn" and m.body:
            m = Member(m.kind, m.access, rename(m.text, mapping), **{a: b for a, b in m.__dict__.items()
                                                                     if a not in ("kind", "access", "text")})
            m.body = rename(m.body, mapping)
            m.text_orig = rename(m.text_orig, mapping) if m.text_orig else None
            entries[k] = (m, v)
    plan.entries, plan.intro, plan.size, plan.start, plan.vfptr = entries, intro, size, start, vfptr
    plan.empty = not any(m.kind == "data" for v in views for m in v.members)
    h = heads[0]
    plan.head = f"{key} {h.declspec + ' ' if h.declspec else ''}{cls}{' : ' + h.bases if h.bases else ''}"
    plan.vslots = {str(s): sig for s, (sig, _) in sorted(slots.items())}
    plan.block = render(plan)
    return plan


INTEGRAL = {"char", "uchar", "int8", "uint8", "short", "ushort", "long", "ulong", "int", "uint", "int64", "uint64",
            "bool", "bool16", "bool32", "wchar", "enum"}


def cv_compatible(a, b):
    """True when two CodeView field types of one offset and size can be one field:
    equal, both pointers, integers of one size (an enum is an integer), or a pointer
    and a 4-byte integer (views often hold a pointer as an int). A class by value
    against anything else, or floating point against an integer, is a disagreement
    about what the field is."""
    if a == b:
        return True
    arr = re.compile(r"^(.*)\[(\d+)\]$")
    ma, mb = arr.match(a), arr.match(b)
    if ma or mb:
        return bool(ma and mb) and cv_compatible(ma.group(1), mb.group(1))
    pa, pb = a.endswith("*"), b.endswith("*")
    if pa and pb:
        return True
    if pa or pb:
        return (b if pa else a) in ("int", "uint", "long", "ulong")
    return a in INTEGRAL and b in INTEGRAL


def claims_size(view, start):
    """True when the view spells its sizeof out: bytes past its last real field (a
    trailing pad), beyond what the alignment of its fields explains."""
    lay = view.layout
    if lay["size"] == 1 and not (lay.get("fields") or lay.get("bases") or lay.get("vfptr")):
        return False                   # an empty view: sizeof 1 is the language's, not a claim
    real = [f for f in view.layout.get("fields", [])
            if not (PAD.match(f[1]) and not view.pad_used.get(f[1]))]
    end = max([start] + [f[0] + f[3] for f in real])
    big = any(re.match(r"(double|int64|uint64)\b", f[2]) for f in real)
    align = 8 if big else 4 if (any(f[3] >= 4 for f in real) or start) else max([1] + [f[3] for f in real])
    return view.layout["size"] > (end + align - 1) // align * align


def head_free(view):
    """True when the view asserts nothing about the class head: no base, class declspec,
    vfptr, virtual slot or virtual method."""
    lay = view.layout
    return not (view.bases or view.declspec or lay.get("bases") or lay.get("vfptr") or lay.get("vslots")
                or lay.get("virtual") or any(m.kind == "fn" and m.virtual for m in view.members))


def own_start(view, vfptr):
    """Where the class's own data begins: past its bases, or past its own vfptr."""
    end = 0
    for base, off in view.layout.get("bases", []):
        b = view.every.get(base) or {}
        if off < 0 or not b.get("size") or b.get("fwd"):
            raise Refused(f"{view.path}: base {base} has no layout to size it")
        empty = b["size"] == 1 and not (b.get("fields") or b.get("bases") or b.get("vfptr"))
        end = max(end, off + (0 if empty else b["size"]))      # an empty base takes no bytes
    if vfptr and not view.layout.get("bases"):
        end = max(end, 4)
    return end


def defines_out_of_line(view, cls, name):
    outside = view.code[:view.span[0]] + " " * (view.span[1] - view.span[0]) + view.code[view.span[1]:]
    return bool(re.search(r"\b" + re.escape(cls) + r"\s*::\s*" + re.escape(name) + r"\s*\(", outside))


def render(plan):
    """The shared block: one text every file of the class carries verbatim."""
    lines, state = [plan.head, "{"], [None]

    def put(acc, text):
        if acc != state[0]:
            lines.append(f"{acc}:")
            state[0] = acc
        rows = text.strip().split("\n")
        rest = [r for r in rows[1:] if r.strip()]
        cut = min((len(r) - len(r.lstrip()) for r in rest), default=0)
        lines.append("\t" + rows[0].strip())
        for r in rows[1:]:
            lines.append(("\t" + r[cut:]).rstrip() if r.strip() else "")

    def member(m, text):
        for line in m.lead:                            # the chosen spelling's own comments ride along
            put(m.access, line)
        put(m.access, text + (f" // {m.tail}" if m.tail else ""))

    for kind in ("nested", "static", "fn"):
        for k, (m, _v) in plan.entries.items():
            if m.kind == kind and k[0] != "slot":
                member(m, spelled(m))
    for k in plan.intro:
        member(plan.entries[k][0], spelled(plan.entries[k][0]))
    at = plan.start
    for off, sz, m, _path in plan.fields:
        if off > at:
            put(state[0] or "public", f"char m_pad{at:02X}[0x{off - at:X}];")
        for line in m.lead:
            put(m.access, line)
        put(m.access, f"{m.base} {m.decl}; // +0x{off:02X}" + (f" {m.tail}" if m.tail else ""))
        at = off + sz
    if plan.size > at and not (plan.empty and plan.size == 1 and at == 0):
        put(state[0] or "public", f"char m_pad{at:02X}[0x{plan.size - at:X}];")
    lines.append("};")
    return "\n".join(lines) + "\n"


def spelled(m):
    if m.kind == "fn" and m.body:
        return (m.text_orig or m.text).strip()
    text = ws(m.text)
    return text if text.endswith((";", "}")) else text + ";"


# ---------------------------------------------------------------- rewrite
def rename(text, mapping, keep=None):
    """`text` with identifier tokens renamed per `mapping` outside comments, strings
    and #include lines. `keep` is a (start, end) span left untouched."""
    if not mapping:
        return text
    code = hal.masked(text)
    pat = re.compile(r"(?<![\w$])(" + "|".join(re.escape(k) for k in sorted(mapping, key=len, reverse=True))
                     + r")(?![\w$])")
    out, last = [], 0
    for m in pat.finditer(code):
        if keep and keep[0] <= m.start() < keep[1]:
            continue
        if re.match(r"\s*#\s*include\b", code[code.rfind("\n", 0, m.start()) + 1:m.start()]):
            continue
        out.append(text[last:m.start()])
        out.append(mapping[m.group(1)])
        last = m.end()
    out.append(text[last:])
    return "".join(out)


def rename_problem(view, mapping):
    """Why renaming `mapping` in this view's file is unsafe, or None."""
    body = IDENT.findall(view.code[view.span[0]:view.span[1]])
    outside = view.code[:view.span[0]] + "\n" + view.code[view.span[1]:]
    for old, new in sorted(mapping.items()):
        if view.used.get(new) or body.count(new):
            return f"{view.path}: renaming {old} -> {new} collides with an existing `{new}` there"
        for other, lay in view.every.items():
            if other == view.cls or not isinstance(lay, dict) or lay.get("fwd"):
                continue
            if any(f[1] == old for f in lay.get("fields", [])) or old in lay.get("methods", []) \
                    or old in lay.get("statics", []):
                return f"{view.path}: {old} is also a member of {other}; a token rename would reach it"
        if re.search(r"(?m)^[^\n{}]*\b(?:extern|static|typedef)\b[^\n]*\b" + re.escape(old) + r"\b", outside) or \
                re.search(r"(?m)^[ \t]*#[ \t]*define[ \t]+" + re.escape(old) + r"\b", outside):
            return f"{view.path}: {old} is also a file-scope name"
        # Any other appearance at file scope (a plain `int m_first;` global, an `extern "C"`
        # or parameter spelling): a token rename would reach a name that is not the field.
        for m in re.finditer(r"\b" + re.escape(old) + r"\b", view.code):
            if not view.span[0] <= m.start() < view.span[1] and not depth_at(view.code, m.start()):
                return f"{view.path}: {old} also appears at file scope; a token rename would reach it"
    return None


def rewrite(text, view, block, mapping, forward=()):
    """The file with its view of the class replaced by `block` (after the `forward`
    declarations it needs there) and its fields renamed."""
    s, e = view.span
    eol = "\r\n" if "\r\n" in text else "\n"
    lead = "".join(f.replace("\r\n", "\n") + "\n" for f in forward)
    new_block = (lead + block).replace("\n", eol)
    rest = text[e:]
    for line in forward:                    # a later copy of a declaration moved up is redundant
        if re.fullmatch(r"(class|struct) \w+;", line):
            code = hal.masked(rest)
            for m in reversed(list(re.finditer(r"(?m)^" + re.escape(line) + r"[ \t]*\r?\n", code))):
                if not depth_at(code, m.start()):
                    rest = rest[:m.start()] + rest[m.end():]
                    code = hal.masked(rest)
    return rename(text[:s] + new_block + rest, mapping, (s, s + len(new_block)))


KEYWORDS = set("""alignas asm auto bool break case catch char class const const_cast continue default delete do
double dynamic_cast else enum explicit extern false float for friend goto if inline int long mutable namespace
new operator private protected public register reinterpret_cast return short signed sizeof static static_cast
struct switch template this throw true try typedef typeid typename union unsigned using virtual void volatile
wchar_t while __int8 __int16 __int32 __int64 __cdecl __stdcall __fastcall __thiscall __declspec __forceinline
__inline dllimport dllexport novtable noinline naked NULL""".split())


def spell_aliases(block, views):
    """`block` with each typedef alias that some receiving file never mentions spelled as
    the builtin type it names (typedefs change no layout, code or mangled name). The
    spelling is a file's own `typedef`, else header_adopt_lane's ZH layer; an alias two
    files define differently, or one naming a non-builtin type, is left alone."""
    code = hal.masked(block)
    local = collections.defaultdict(set)
    for v in views:
        for m in re.finditer(r"^\s*typedef\s+([^;{}()]+?)\s+([A-Za-z_]\w*)\s*;", v.code, re.M):
            local[m.group(2)].add(ws(m.group(1)))
    spell = {}
    for name in dict.fromkeys(IDENT.findall(code)):
        known = local.get(name) or ({hal.TYPEDEFS[name]} if name in hal.TYPEDEFS else set())
        if len(known) != 1 or name in ("TRUE", "FALSE"):
            continue
        target = next(iter(known))
        if not set(target.split()) <= TYPE_WORDS:
            continue
        if any(not v.used.get(name) and not re.search(r"\b" + name + r"\b", v.code[v.span[0]:v.span[1]])
               for v in views):
            spell[name] = target
    if not spell:
        return block, {}
    out, last = [], 0
    for m in re.finditer(r"\b(" + "|".join(map(re.escape, spell)) + r")\b", code):
        out.append(block[last:m.start()] + spell[m.group(1)])
        last = m.end()
    return "".join(out) + block[last:], spell


def namespace_enums(texts):
    """{enum name: definition} of the namespace-scope enums the files define, where every
    file defining one spells it the same (comments dropped)."""
    seen = collections.defaultdict(set)
    for text in texts:
        code, src = hal.masked(text), no_comments(text)
        for m in re.finditer(r"^[ \t]*enum[ \t]+([A-Za-z_]\w*)\s*\{[^{}]*\}\s*;", code, re.M):
            if not depth_at(code, m.start()):
                seen[m.group(1)].add(src[m.start():m.end()].strip())
    return {n: next(iter(d)) for n, d in seen.items() if len({ws(x) for x in d}) == 1}


def needed_names(plan):
    """Identifiers the block's declarations name (inline bodies excluded)."""
    heads = []
    for m, _ in plan.entries.values():
        heads.append(m.text.split("{")[0] if m.kind == "fn" and m.body else m.text)
    heads += [m.base for _, _, m, _ in plan.fields]
    own = {plan.cls.split("::")[-1]} | {m.name for m, _ in plan.entries.values()} \
        | {m.name for _, _, m, _ in plan.fields}
    return [n for n in dict.fromkeys(IDENT.findall(hal.masked(" ".join(heads))))
            if n not in KEYWORDS and n not in own and n not in hal.TYPEDEFS]


def forward_declarations(plan, view, keys):
    """`class X;` lines the block needs in this view's file: classes its declarations
    name (bodies excluded) that the file does not name before the class, keyed as the
    compiler recorded them in the TU's files (`keys`: {name: 'class'|'struct'})."""
    out = []
    for name in needed_names(plan):
        if name not in keys or re.search(r"\b" + name + r"\b", view.code[:view.span[1]]):
            continue                    # declared (or at least named) before the block needs it
        out.append(f"{keys[name]} {name};")
    return out


def enum_copies(plan, view, enums):
    """Definitions of the namespace-scope enums the block names and this file never
    does: carried verbatim from the TU file that defines them (an enum cannot be
    forward-declared under VC7.1; the merge emits identical definitions once)."""
    return [enums[n] for n in needed_names(plan)
            if n in enums and not view.used.get(n) and not re.search(r"\b" + n + r"\b", view.code)]


FN_TYPEDEF = re.compile(r"^[ \t]*typedef[^;{}()]+\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\([^;{}()]*\)\s*;", re.M)


def builtin_spelling(decl):
    """`decl` with comments dropped, whitespace collapsed and header_adopt_lane's ZH
    aliases (Int, UnsignedInt, Bool, ...) spelled as the builtin types they name."""
    aliases = {k: v for k, v in hal.TYPEDEFS.items() if k not in ("TRUE", "FALSE")}
    return ws(re.sub(r"\b(" + "|".join(map(re.escape, aliases)) + r")\b",
                     lambda m: aliases[m.group(1)], no_comments(decl)))


def namespace_fn_typedefs(texts):
    """{name: definition} of the namespace-scope function-pointer typedefs the files
    define (`typedef void (*F)(GameWindow *, UnsignedInt);`), where every file defining
    one spells the same type once its ZH aliases are spelled out; the definition is
    first file's builtin spelling (whitespace around punctuation is no difference), so
    a receiving file needs none of the aliases."""
    seen = collections.defaultdict(dict)
    for text in texts:
        code = hal.masked(text)
        for m in FN_TYPEDEF.finditer(code):
            if not depth_at(code, m.start()):
                decl = builtin_spelling(text[m.start():m.end()].strip())
                seen[m.group(1)].setdefault(re.sub(r"\s*([,()*&;])\s*", r"\1", decl), decl)
    return {n: next(iter(d.values())) for n, d in seen.items() if len(d) == 1}


def typedef_copies(plan, view, typedefs, keys, before=()):
    """The function-pointer typedefs the block names and this file never does, each
    after `class X;` lines for the classes it names that the file does not name before
    the block (and `before`, the lines already going there, does not declare)."""
    out, have = [], set(before)
    for n in needed_names(plan):
        if n not in typedefs or re.search(r"\b" + n + r"\b", view.code):
            continue
        for name in dict.fromkeys(IDENT.findall(typedefs[n])):
            line = f"{keys[name]} {name};" if name in keys else None
            if line and line not in have and not re.search(r"\b" + name + r"\b", view.code[:view.span[0]]):
                out.append(line)
                have.add(line)
        out.append(typedefs[n])
    return out


# ---------------------------------------------------------------- the TU
def read_source(path):
    """The file's bytes as text, line endings untouched (CRLF stays CRLF)."""
    with open(path, encoding="latin-1", newline="") as fh:
        return fh.read()


def tu_files(tu):
    """(seed, [files]) exactly as tu_skeleton --merge sees them: the TU file when it
    is a donor, else the donor whose first row comes first in retail order."""
    import tu_skeleton
    don, _mixed, _refused = tu_skeleton.donors(tu, tu_skeleton.skeleton(tu))
    first = {f: min(int(r["target_rva"], 16) for r in rows) for f, rows in don.items()}
    files = sorted(don, key=lambda f: (f != tu, first[f], f))
    return (files[0] if files else None), files


def canonical(path=CANONICAL):
    if not Path(path).exists():
        return {}
    with Path(path).open(encoding="utf-8", newline="") as fh:
        return {r["class"]: r["header"] for r in csv.DictReader(fh)}


def file_classes(text):
    """The classes one file gives a namespace-scope body (a body class_span refuses counts:
    it is reported when the class is planned), first-seen order."""
    code = hal.masked(text)
    out = []
    for c in dict.fromkeys(class_layouts.class_bodies(text)):
        try:
            if "::" in c or not class_span(text, c, code):
                continue
        except Refused:
            pass                                           # reported when the class is planned
        out.append(c)
    return out


def shared_classes(files, texts):
    """{class: [files with a namespace-scope body]} for classes two or more files declare."""
    seen = collections.defaultdict(list)
    for f in files:
        for c in file_classes(texts[f]):
            seen[c].append(f)
    return {c: fs for c, fs in seen.items() if len(fs) >= 2}


_FILE_CLASSES = None


def _cached_file_classes(root, rel):
    """file_classes of ROOT/REL from the shared picker cache (by content; a picker run names a
    clean tracked file by its blob, unread), or None when the file cannot be read."""
    global _FILE_CLASSES
    import picker_cache
    if _FILE_CLASSES is None:
        here = Path(__file__).resolve()
        _FILE_CLASSES = picker_cache.FileMemo("tu_views-file-classes", [
            here, here.with_name("header_adopt_lane.py"), here.with_name("class_layouts.py")])
    key = picker_cache.blob_key(rel, root)
    if key is not None:
        return _FILE_CLASSES.get(key, lambda: file_classes(read_source(Path(root) / rel)))
    try:
        text = read_source(Path(root) / rel)
    except OSError:
        return None
    return _FILE_CLASSES.get(picker_cache.text_key(text), lambda: file_classes(text))


def shared_private(files, root=ROOT, canon=None):
    """Classes without a canonical header that two or more of `files` declare privately:
    the cheap, textual test tu_skeleton and the consolidate queue use to point here."""
    seen = collections.defaultdict(list)
    for f in files:
        try:
            classes = _cached_file_classes(root, f)
        except OSError:
            continue
        if classes is None:
            continue
        for c in classes:
            seen[c].append(f)
    canon = canonical() if canon is None else canon
    return sorted(c for c, fs in seen.items() if len(fs) >= 2 and c not in canon)


def dependency_order(classes, layouts):
    """Bases before the classes deriving from them, else first-seen order."""
    done, out = set(), []

    def visit(c, stack=()):
        if c in done or c in stack:
            return
        for lay in layouts.values():
            for base, _ in (lay.get(c) or {}).get("bases", []):
                if base in classes:
                    visit(base, stack + (c,))
        done.add(c)
        out.append(c)

    for c in classes:
        visit(c)
    return out


class Tool:
    """The reconcile run for one TU; `layouts`, `build`, `unmatched`, `held` and
    `ledger` are injectable for tests."""

    def __init__(self, tu, root=ROOT, layouts=None, build=None, unmatched=None, ledger=None, held=None,
                 canon=None, symbols=None):
        self.tu, self.root = tu, Path(root)
        self._layouts = layouts or (lambda f: class_layouts.compile_layouts(f))
        # injected layouts (tests) compile nothing, so they get no object to read either
        self.symbols = symbols or (external_symbols if layouts is None else (lambda f: frozenset()))
        self.build = build or build_files
        self.unmatched = unmatched or declared_unmatched
        self.held = held or held_by_others
        self._ledger = ledger
        self.canon = canonical() if canon is None else canon
        self.cache = {}

    @property
    def ledger(self):
        if self._ledger is None:
            self._ledger = ledger_rows()
        return self._ledger

    def layouts(self, f):
        if f not in self.cache:
            self.cache[f] = self._layouts(f)
        return self.cache[f]

    def read(self, f):
        return read_source(self.root / f)

    def write(self, f, text):
        with open(self.root / f, "w", encoding="latin-1", newline="") as fh:
            fh.write(text)

    def plan(self, cls, files, texts, seed):
        views, inert = [], []
        for f in files:
            lay = self.layouts(f).get(cls)
            if not lay or lay.get("fwd"):
                inert.append(View(f, texts[f], cls, {}, self.layouts(f), inert=True))
            else:
                views.append(View(f, texts[f], cls, lay, self.layouts(f)))
        if not views:
            raise Refused(f"no file's CodeView lays {cls} out (nothing uses it)")
        plan = reconcile(cls, views, seed, self.ledger)
        if inert:
            plan.notes.append("no code uses it in " + ", ".join(v.path for v in inert) + ": they take the block")
        views += inert
        for v in views:
            why = rename_problem(v, plan.renames.get(v.path, {}))
            if why:
                raise Refused(why)
        pads = re.findall(r"\bchar (m_pad[0-9A-F]{2,})\[", plan.block)
        clash = [p for p in pads if p in {m.name for _, _, m, _ in plan.fields}
                 or p in {m.name for m, _ in plan.entries.values()}]
        if clash:
            raise Refused(f"padding name {clash[0]} is already a member name")
        plan.views = views
        plan.block, spelled_as = spell_aliases(plan.block, views)
        if spelled_as:
            plan.notes.append("typedefs a file lacks, spelled out: " +
                              ", ".join(f"{a} -> {b}" for a, b in sorted(spelled_as.items())))
        keys = self.class_keys(files, texts, needed_names(plan))
        enums = namespace_enums(texts[f] for f in files)
        typedefs = namespace_fn_typedefs(texts[f] for f in files)
        keys = {**keys, **self.class_keys(files, texts, [n for t in typedefs.values() for n in IDENT.findall(t)])}
        plan.forward = {}
        for v in views:
            lead = enum_copies(plan, v, enums) + forward_declarations(plan, v, keys)
            plan.forward[v.path] = lead + typedef_copies(plan, v, typedefs, keys, lead)
        for f, lines in plan.forward.items():
            if lines:
                plan.notes.append(f"{f} gets " + " ".join(ws(ln.split("{")[0]) + ("{...};" if "{" in ln else "") for ln in lines))
        return plan

    def class_keys(self, files, texts=None, wanted=()):
        """{class: 'class'|'struct'} as the compiler recorded it for these files, else as
        the files spell it (`class X;`, a definition head), else as the ledger's mangled
        names spell it (`V`/`U`); a name these disagree on is left out."""
        seen = collections.defaultdict(set)
        for f in files:
            for name, lay in self.layouts(f).items():
                if isinstance(lay, dict) and lay.get("key") and "::" not in name and "<" not in name:
                    seen[name].add(lay["key"])
        spelled = collections.defaultdict(set)
        for text in (texts or {}).values():
            code = hal.masked(text)
            for m in re.finditer(r"\b(class|struct)\s+(?:__declspec\([^)]*\)\s*)*([A-Za-z_]\w*)\s*(?:;|\{|:(?!:))",
                                 code):
                spelled[m.group(2)].add(m.group(1))
        for name, keys in spelled.items():
            if name not in seen:
                seen[name] = keys
        for name in wanted:
            if name not in seen:
                lk = ledger_class_key(name, self.ledger)
                if lk in ("class", "struct"):
                    seen[name] = {lk}
        return {n: next(iter(k)) for n, k in seen.items() if len(k) == 1}

    def describe(self, cls, files, texts, seed):
        try:
            plan = self.plan(cls, files, texts, seed)
        except Refused as exc:
            return {"status": "conflict", "files": files, "evidence": str(exc)}, None
        return {"status": "plan", "files": files, "notes": plan.notes,
                "renames": {f: m for f, m in plan.renames.items() if m},
                "fields": [[f"0x{off:02X}", sz, m.name, path] for off, sz, m, path in plan.fields],
                "block": plan.block}, plan

    def run(self, dry_run=False, only=(), files=None, seed=None):
        report = {"tu": self.tu, "classes": {}, "canonical": {}, "applied": [], "failed": {}}
        if files is None:
            seed, files = tu_files(self.tu)
        report["seed"], report["files"] = seed, list(files)
        if len(files) < 2:
            report["blocked"] = "fewer than two files"
            return report
        texts = {f: self.read(f) for f in files}
        shared = shared_classes(files, texts)
        for c in list(shared):
            if c in self.canon:
                report["canonical"][c] = {"files": shared.pop(c), "header": self.canon[c],
                                          "action": f"python3 tools/header_adopt_lane.py accept --class {c} FILE..."}
        if only:
            shared = {c: fs for c, fs in shared.items() if c in only}
        try:
            order = dependency_order(list(shared), {f: self.layouts(f) for f in files})
        except RuntimeError as exc:
            report["blocked"] = f"layout read failed: {exc}"
            return report
        if dry_run:
            for c in order:
                report["classes"][c] = self.describe(c, shared[c], texts, seed)[0]
            return report
        held = self.held(files)
        if held:
            report["blocked"] = "held by another worker: " + ", ".join(held[:5])
            return report
        before = {f: self.unmatched([f]) for f in files}
        blocks = collections.defaultdict(list)             # file -> blocks already shared there
        retry = []
        for c in order:
            self.attempt(c, shared[c], texts, seed, before, blocks, report, retry)
        if report["applied"] and retry:                    # a later class's renames may have unblocked it
            for c in retry:
                self.attempt(c, shared[c], texts, seed, before, blocks, report, None)
        return report

    def attempt(self, c, files, texts, seed, before, blocks, report, retry):
        entry, plan = self.describe(c, files, texts, seed)
        report["classes"][c] = entry
        if not plan:
            return
        spelled = {ws(hal.masked(texts[v.path][v.span[0]:v.span[1]])) for v in plan.views}
        if len(spelled) == 1:                  # one spelling already: the merge emits it once
            entry["status"] = "already shared"
            return
        new = {v.path: rewrite(texts[v.path], v, plan.block, plan.renames.get(v.path, {}), plan.forward.get(v.path, ()))
               for v in plan.views}
        changed = sorted(f for f in new if new[f] != texts[f])
        if not changed:
            entry["status"] = "already shared"
            return
        for f in changed:
            lost = [b for b in blocks[f] if b not in new[f]]
            if lost:
                entry["status"], entry["why"] = "conflict", (f"{f}: its renames would change the shared view "
                                                             f"of {lost[0].split(chr(10))[0]}")
                return
        syms = {f: self.symbols(f) for f in changed}
        try:
            for f in changed:
                self.write(f, new[f])
            why = self.verify(plan, changed, before) or self.symbol_drift(changed, syms)
        except BaseException:     # an error or interrupt mid-apply: put every file back first
            for f in changed:
                self.write(f, texts[f])
                self.cache.pop(f, None)
            raise
        if why:
            for f in changed:
                self.write(f, texts[f])
                self.cache.pop(f, None)
            entry["status"], entry["why"] = "reverted", why
            report["failed"][c] = why
            if retry is not None:
                retry.append(c)
            return
        eol = {f: "\r\n" if "\r\n" in texts[f] else "\n" for f in changed}
        texts.update({f: new[f] for f in changed})
        for f in changed:
            blocks[f].append(plan.block.replace("\n", eol[f]))
        entry["status"], entry["files_changed"] = "applied", changed
        report["failed"].pop(c, None)
        report["applied"].append(c)

    def symbol_drift(self, changed, before):
        """None when every changed file's object defines and references exactly the
        external names it did before the rewrite, else why not. A field rename or a
        reconciled declaration changes no symbol; a changed one (a global the rename
        reached, another overload's access, a dropped volatile) can leave the bytes
        identical, because the byte gate masks relocation targets."""
        for f in changed:
            self.cache.pop(f, None)
            after = self.symbols(f)
            if after != before[f]:
                gone, new = sorted(before[f] - after), sorted(after - before[f])
                return (f"{f}: the rewrite changes the object's external symbols "
                        f"(lost {[n for n, _ in gone][:3]}, gained {[n for n, _ in new][:3]})")
        return None

    def verify(self, plan, changed, before):
        """None when every changed file keeps the planned layout, builds exact and
        declares nothing new unmatched; else why not."""
        want = {(off, m.name) for off, _sz, m, _ in plan.fields}
        inert = {v.path for v in plan.views if v.inert}
        for f in changed:
            self.cache.pop(f, None)
            try:
                lay = self.layouts(f).get(plan.cls) or {}
            except RuntimeError:              # build.sh names the error (the layout reader gives codes)
                return f"{f} does not compile with the block: " + self.build([f])[1]
            if f in inert and (not lay or lay.get("fwd")):
                continue                                   # still unused there: the build decides
            got = {(fl[0], fl[1]) for fl in lay.get("fields", [])}
            if not want <= got or lay.get("size") != plan.size or lay.get("vslots", {}) != plan.vslots:
                return (f"{f}: layout after the rewrite is not the plan (size 0x{lay.get('size', 0):X} vs "
                        f"0x{plan.size:X}, missing {sorted(want - got)[:3]}, vslots "
                        f"{'equal' if lay.get('vslots', {}) == plan.vslots else 'differ'})")
        ok, out = self.build(changed)
        if not ok:
            return "not exact: " + out
        for f in changed:
            new = set(self.unmatched([f])) - set(before.get(f, []))
            if new:
                return f"{f}: find_declared_unmatched now reports {sorted(new)[:3]}"
        return None


def bash():
    """A POSIX bash for ./build.sh: on Windows Git's, never WSL's System32 launcher."""
    if os.name != "nt":
        return "bash"
    found = shutil.which("bash")
    if found and "system32" not in found.lower():
        return found
    git = shutil.which("git")
    for rel in ("../bin/bash.exe", "../usr/bin/bash.exe", "../../bin/bash.exe", "../../usr/bin/bash.exe"):
        if git and (Path(git).parent / rel).resolve().exists():
            return str((Path(git).parent / rel).resolve())
    raise SystemExit("tu_views: no Git bash found to run ./build.sh")


def coff_externals(data):
    """{(name, defined)} of a COFF object's EXTERNAL and WEAK_EXTERNAL symbols."""
    table, count = struct.unpack_from("<II", data, 8)
    strings, out, index = table + 18 * count, set(), 0
    while index < count:
        entry = table + 18 * index
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            name = data[start:data.index(b"\0", start)]
        else:
            name = raw.rstrip(b"\0")
        section, storage = struct.unpack_from("<h", data, entry + 12)[0], data[entry + 16]
        if storage in (2, 105):                       # IMAGE_SYM_CLASS_EXTERNAL, WEAK_EXTERNAL
            out.add((name.decode("latin-1"), section > 0))
        index += 1 + data[entry + 17]
    return frozenset(out)


def external_symbols(f):
    """coff_externals of the object class_layouts compiled `f` to (its own flags, -Z7)."""
    class_layouts.compile_layouts(f)
    rel = (class_layouts.ROOT / f).resolve().relative_to(class_layouts.ROOT).as_posix()
    obj = class_layouts.CACHE / (re.sub(r"[^\w.-]", "_", rel) + ".obj")
    if not obj.exists():                              # a parse cached without its object
        class_layouts.compile_layouts(f, use_cache=False)
    return coff_externals(obj.read_bytes())


def build_files(files):
    """(exact, tail of the output) of `./build.sh FILES`, the sanctioned verifier."""
    done = subprocess.run([bash(), "./build.sh", *files], cwd=ROOT, capture_output=True, text=True,
                          errors="replace")
    tail = [ln.strip() for ln in (done.stdout + done.stderr).splitlines() if ln.strip()][-8:]
    return done.returncode == 0, " | ".join(tail)[-700:]


def declared_unmatched(files):
    done = subprocess.run([sys.executable, str(ROOT / "tools" / "find_declared_unmatched.py"), *files],
                          cwd=ROOT, capture_output=True, text=True, errors="replace")
    return [ln for ln in done.stdout.splitlines() if ln.strip() and not ln.startswith("All defined")]


def held_by_others(files):
    import claims
    try:
        got = claims.conflicts({claims.key_of(f"file:{f}") for f in files})
    except Exception as exc:          # no origin: tu_skeleton's rule, nothing is known to be held
        print(f"(claims unavailable: {exc})", file=sys.stderr)
        return []
    return [claims.label(k, info) for k, info in got.items()]


def merge_dry_run(tu):
    """(accepted, rejected) of `tu_skeleton.py --merge TU --dry-run`, in a fresh process."""
    done = subprocess.run([sys.executable, str(ROOT / "tools" / "tu_skeleton.py"), "--merge", tu, "--dry-run"],
                          cwd=ROOT, capture_output=True, text=True, errors="replace")
    acc = re.search(r"^accepted: (\[.*\])$", done.stdout, re.M)
    rej = re.search(r"^rejected: (\{.*\})$", done.stdout, re.M)
    return (ast.literal_eval(acc.group(1)) if acc else [], ast.literal_eval(rej.group(1)) if rej else {})


def print_report(rep, log=print):
    log(f"tu: {rep['tu']}")
    log(f"seed: {rep.get('seed')}  ({len(rep.get('files', []))} files)")
    for c, e in rep.get("canonical", {}).items():
        log(f"  {c}: canonical header {e['header']}: header-lane work, not written ({e['action']})")
    for c, e in rep.get("classes", {}).items():
        log(f"  {c}: {e['status']} ({len(e['files'])} files)")
        if e.get("evidence"):
            log(f"      CONFLICT: {e['evidence']}")
        if e.get("why"):
            log(f"      {'REVERTED' if e['status'] == 'reverted' else 'CONFLICT'}: {e['why']}")
        for n in e.get("notes", []):
            log(f"      note: {n}")
        for f, m in e.get("renames", {}).items():
            log(f"      rename in {f}: " + ", ".join(f"{a} -> {b}" for a, b in sorted(m.items())))
        if e["status"] == "plan":
            for ln in e["block"].rstrip().split("\n"):
                log("        | " + ln)
    for k in ("applied", "blocked"):
        if rep.get(k):
            log(f"{k}: {rep[k]}")
    if "merge_before" in rep:
        log(f"donors accepted by tu_skeleton --merge --dry-run: {len(rep['merge_before'])} -> "
            f"{len(rep['merge_after'])}")
        for f, why in sorted(rep.get("rejected_before", {}).items()):
            log(f"  rejected before {f}: {why[:200]}")
        for f, why in sorted(rep.get("still_rejected", {}).items()):
            log(f"  still rejected {f}: {why[:200]}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("tu")
    ap.add_argument("--dry-run", action="store_true", help="print the plan; write nothing")
    ap.add_argument("--class", dest="only", action="append", default=[], help="only this class (repeatable)")
    ap.add_argument("--json", help="also write the report as JSON here")
    ap.add_argument("--no-merge-check", action="store_true", help="skip the tu_skeleton dry-runs before and after")
    a = ap.parse_args(argv)
    check = not a.dry_run and not a.no_merge_check
    before = merge_dry_run(a.tu) if check else None
    rep = Tool(a.tu).run(dry_run=a.dry_run, only=set(a.only))
    if before is not None:
        rep["merge_before"], rep["rejected_before"] = before
        rep["merge_after"], rep["still_rejected"] = merge_dry_run(a.tu) if rep["applied"] else before
    print_report(rep)
    if a.json:
        Path(a.json).write_text(json.dumps(rep, indent=1) + "\n", encoding="utf-8")
    return 2 if rep.get("blocked") else 0


if __name__ == "__main__":
    sys.exit(main())
