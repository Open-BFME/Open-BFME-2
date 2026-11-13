#!/usr/bin/env python3
"""Exact layout of every private class view, read from the compiler.

WHY. Deciding whether a unit's private copy of a class is the canonical
class needs its real layout: field offsets and sizes, base offsets, sizeof
and the virtual slots with their argument types. Regex over the class body
cannot give that (inline padding arrays, typedef'd members, bases declared
elsewhere), and cl 13.10 has no /d1reportSingleClassLayout. What it does have
is CodeView: compiling the unit with its own flags plus -Z7 puts every type it
saw into .debug$T, and that record is the compiler's own answer.

THE TRAP. VC7.1 CodeView gives every introducing overload of one name the
same vbaseoff (the group's highest slot), and lays the group out in reverse
declaration order. Taking the CodeView offset at face value names the wrong
slot for every overload but the last. `--probe` compiles a toy class and
compares the slots read here with the offsets the compiler encodes in its
own vcall thunks (??_9@$B<n>AE); it must agree before any slot evidence is
trusted.

CACHE. Objects go to build/class_layouts/. An entry is reused when the
command line, the source and every header /showIncludes listed for it hash
the same (the same receipt rule build.py uses); the parsed layouts are keyed
by the digest of the object's .debug$T section, so two inputs that compile
to the same type stream share one parse.

    python3 tools/class_layouts.py FILE...              all private views, JSON
    python3 tools/class_layouts.py --class Coord3D FILE  one class
    python3 tools/class_layouts.py --probe               slot-order self-check
"""
import argparse
import hashlib
import importlib.util
import json
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CACHE = ROOT / "build" / "class_layouts"
PARSER_HASH = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()[:16]

# Scope is checked below; indentation alone cannot distinguish private views
# from nested records (GeneralAllocator::Snapshot is not ::Snapshot).
HEAD = re.compile(r"^[ \t]*(?P<template>template\s*<[^;{}]*>\s*)?"
                  r"(?P<key>class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)?"
                  r"(?P<name>[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)\s*(?::(?!:)[^{;]*)?\{", re.M)
NON_CODE = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?', re.S)
NAMESPACE = re.compile(r"\bnamespace\s*(?:[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)?\s*\{")
LINKAGE = re.compile(r'\bextern\s+"C(?:\+\+)?"\s*\{')

PRIM = {0x03: ("void", 0), 0x10: ("char", 1), 0x20: ("uchar", 1), 0x70: ("char", 1), 0x68: ("int8", 1),
        0x69: ("uint8", 1), 0x11: ("short", 2), 0x21: ("ushort", 2), 0x72: ("short", 2), 0x73: ("ushort", 2),
        0x12: ("long", 4), 0x22: ("ulong", 4), 0x74: ("int", 4), 0x75: ("uint", 4), 0x13: ("int64", 8),
        0x23: ("uint64", 8), 0x76: ("int64", 8), 0x77: ("uint64", 8), 0x40: ("float", 4), 0x41: ("double", 8),
        0x42: ("ldouble", 8), 0x30: ("bool", 1), 0x71: ("wchar", 2), 0x31: ("bool16", 2), 0x32: ("bool32", 4)}
# LF_CLASS/LF_STRUCTURE in the 16-bit-name (_ST) and zero-terminated forms.
CLASS_KINDS = {0x1004: True, 0x1005: True, 0x1504: False, 0x1505: False}
# The VC7.1 overload rule (see THE TRAP). Off reproduces the naive reading;
# tools/tests/test_class_layouts.py uses that as the probe's positive control.
REVERSED_GROUPS = True


def build_module():
    spec = importlib.util.spec_from_file_location("repo_build", ROOT / "tools" / "build.py")
    module = importlib.util.module_from_spec(spec)
    sys.path.insert(0, str(ROOT / "tools"))
    spec.loader.exec_module(module)
    return module


# ---------------------------------------------------------------- CodeView

def coff_sections(data):
    count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
    offset = 20 + optional
    for _ in range(count):
        name = data[offset:offset + 8].rstrip(b"\0")
        size, pointer = struct.unpack_from("<I", data, offset + 16)[0], struct.unpack_from("<I", data, offset + 20)[0]
        yield name, data[pointer:pointer + size]
        offset += 40


def coff_symbols(data):
    """Names in the COFF symbol table (aux records skipped)."""
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    index = 0
    while index < count:
        entry = table + 18 * index
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            name = data[start:data.index(b"\0", start)]
        else:
            name = raw.rstrip(b"\0")
        yield name.decode("latin-1")
        index += 1 + data[entry + 17]


def numeric(blob, pos):
    value = struct.unpack_from("<H", blob, pos)[0]
    if value < 0x8000:
        return value, pos + 2
    fmt, size = {0x8000: ("<b", 1), 0x8001: ("<h", 2), 0x8002: ("<H", 2), 0x8003: ("<i", 4),
                 0x8004: ("<I", 4), 0x8009: ("<q", 8), 0x800A: ("<Q", 8)}[value]
    return struct.unpack_from(fmt, blob, pos + 2)[0], pos + 2 + size


def name_at(blob, pos, pascal):
    if pascal:
        length = blob[pos]
        return blob[pos + 1:pos + 1 + length].decode("latin-1"), pos + 1 + length
    end = blob.index(b"\0", pos)
    return blob[pos:end].decode("latin-1"), end + 1


class TypeStream:
    def __init__(self, stream):
        if struct.unpack_from("<I", stream, 0)[0] not in (1, 2, 4):
            raise ValueError("not a CodeView type stream")
        self.records, pos, index = {}, 4, 0x1000
        while pos + 4 <= len(stream):
            length, kind = struct.unpack_from("<HH", stream, pos)
            self.records[index] = (kind, stream[pos + 4:pos + 2 + length])
            pos += 2 + length
            index += 1
        self.complete_sizes = {}
        for kind, blob in self.records.values():
            if kind not in CLASS_KINDS or struct.unpack_from("<H", blob, 2)[0] & 0x80:
                continue
            size, pos = numeric(blob, 16)
            name, _ = name_at(blob, pos, CLASS_KINDS[kind])
            key = (kind in (0x1004, 0x1504), name)
            self.complete_sizes.setdefault(key, set()).add(size)

    def name(self, ti):
        if ti < 0x1000:
            return PRIM.get(ti & 0xFF, ("p%x" % (ti & 0xFF), 0))[0] + ("*" if (ti >> 8) & 7 else "")
        kind, blob = self.records.get(ti, (0, b""))
        if kind in CLASS_KINDS:
            _, pos = numeric(blob, 16)
            return name_at(blob, pos, CLASS_KINDS[kind])[0]
        if kind == 0x1002:
            return self.name(struct.unpack_from("<I", blob, 0)[0]) + "*"
        if kind == 0x1001:
            return self.name(struct.unpack_from("<I", blob, 0)[0])
        if kind in (0x1003, 0x1503):
            return "%s[%d]" % (self.name(struct.unpack_from("<I", blob, 0)[0]), numeric(blob, 8)[0])
        if kind in (0x1007, 0x1507):
            return "enum"
        return "bitfield" if kind == 0x1205 else "k%x" % kind

    def size(self, ti):
        if ti < 0x1000:
            return 4 if (ti >> 8) & 7 else PRIM.get(ti & 0xFF, ("", 0))[1]
        kind, blob = self.records.get(ti, (0, b""))
        if kind == 0x1002 or kind in (0x1007, 0x1507):
            return 4
        if kind == 0x1001:
            return self.size(struct.unpack_from("<I", blob, 0)[0])
        if kind in (0x1003, 0x1503):
            return numeric(blob, 8)[0]
        if kind in CLASS_KINDS:
            size, pos = numeric(blob, 16)
            if struct.unpack_from("<H", blob, 2)[0] & 0x80:
                name, _ = name_at(blob, pos, CLASS_KINDS[kind])
                sizes = self.complete_sizes.get((kind in (0x1004, 0x1504), name), set())
                return next(iter(sizes)) if len(sizes) == 1 else 0
            return size
        return 0

    def signature(self, ti):
        kind, blob = self.records.get(ti, (0, b""))
        if kind != 0x1009:
            return "(?)"
        arglist = struct.unpack_from("<I", blob, 16)[0]
        akind, ablob = self.records.get(arglist, (0, b""))
        args = []
        if akind == 0x1201:
            count = struct.unpack_from("<I", ablob, 0)[0]
            args = [self.name(struct.unpack_from("<I", ablob, 4 + 4 * i)[0]) for i in range(count)]
        return "(" + ",".join(args) + ")"

    def fields(self, ti, out):
        _, blob = self.records[ti]
        pos = 0
        while pos < len(blob):
            while pos < len(blob) and blob[pos] >= 0xF0:
                pos += 1
            if pos + 2 > len(blob):
                break
            sub = struct.unpack_from("<H", blob, pos)[0]
            pos += 2
            if sub == 0x1400:                                   # base class
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                offset, pos = numeric(blob, pos + 6)
                out["bases"].append([self.name(index), offset])
            elif sub in (0x1401, 0x1402):                       # virtual base
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                _, pos = numeric(blob, pos + 10)
                _, pos = numeric(blob, pos)
                out["bases"].append(["virtual " + self.name(index), -1])
            elif sub in (0x1405, 0x150D):                       # data member
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                offset, pos = numeric(blob, pos + 6)
                name, pos = name_at(blob, pos, sub == 0x1405)
                out["fields"].append([offset, name, self.name(index), self.size(index)])
            elif sub in (0x1406, 0x150E):                       # static member
                name, pos = name_at(blob, pos + 6, sub == 0x1406)
                out["statics"].append(name)
            elif sub in (0x1407, 0x150F):                       # overloaded method
                _, methodlist = struct.unpack_from("<HI", blob, pos)
                name, pos = name_at(blob, pos + 6, sub == 0x1407)
                out["methods"].add(name)
                _, mblob = self.records[methodlist]
                q, groups = 0, {}
                while q < len(mblob):
                    attr, _, ty = struct.unpack_from("<HHI", mblob, q)
                    q += 8
                    prop = (attr >> 2) & 7
                    if prop in (4, 6):                          # introducing virtual
                        groups.setdefault(struct.unpack_from("<I", mblob, q)[0], []).append(name + self.signature(ty))
                        q += 4
                    if prop in (1, 4, 5, 6):
                        out["virtual"].add(name)
                # Every intro overload carries the group's HIGHEST slot; the
                # list runs in reverse declaration order, which is the order the
                # compiler assigns slots in (checked by --probe).
                for top, members in groups.items():
                    for i, member in enumerate(members):
                        slot = top - 4 * (len(members) - 1) + 4 * i if REVERSED_GROUPS else top
                        out["vslots"].setdefault(slot, member)
            elif sub in (0x140B, 0x1511):                       # single method
                attr, index = struct.unpack_from("<HI", blob, pos)
                pos += 6
                prop, slot = (attr >> 2) & 7, None
                if prop in (4, 6):
                    slot = struct.unpack_from("<I", blob, pos)[0]
                    pos += 4
                name, pos = name_at(blob, pos, sub == 0x140B)
                out["methods"].add(name)
                if slot is not None:
                    out["vslots"][slot] = name + self.signature(index)
                if prop in (1, 4, 5, 6):
                    out["virtual"].add(name)
            elif sub in (0x1408, 0x1510, 0x140D, 0x1512):       # nested type / static method alias
                _, pos = name_at(blob, pos + 6, sub in (0x1408, 0x140D))
            elif sub == 0x1409:                                 # vfptr
                out["vfptr"] = True
                pos += 6
            elif sub in (0x1404, 0x140A):                       # continuation / vfunc tab
                if sub == 0x1404:
                    self.fields(struct.unpack_from("<I", blob, pos + 2)[0], out)
                pos += 6
            elif sub in (0x1403, 0x150C):
                _, pos = name_at(blob, pos + 6, sub == 0x1403)
            elif sub in (0x0403, 0x1502):                       # enumerator
                _, pos = numeric(blob, pos + 2)
                _, pos = name_at(blob, pos, sub == 0x0403)
            else:
                out["unparsed"] = sub
                break

    def classes(self):
        found = {}
        for ti, (kind, blob) in self.records.items():
            if kind not in CLASS_KINDS:
                continue
            _, prop, fieldlist = struct.unpack_from("<HHI", blob, 0)
            size, pos = numeric(blob, 16)
            name, _ = name_at(blob, pos, CLASS_KINDS[kind])
            if prop & 0x80:                                     # forward reference
                found.setdefault(name, {"fwd": True})
                continue
            out = {"fwd": False, "key": "class" if kind in (0x1004, 0x1504) else "struct", "size": size,
                   "bases": [], "fields": [], "statics": [], "methods": set(), "virtual": set(),
                   "vslots": {}, "vfptr": False}
            if fieldlist:
                self.fields(fieldlist, out)
            out["methods"], out["virtual"] = sorted(out["methods"]), sorted(out["virtual"])
            out["vslots"] = {str(k // 4): v for k, v in sorted(out["vslots"].items())}
            prior = found.get(name)
            if prior is not None and not prior.get("fwd") and _shape(prior) != _shape(out):
                # two complete classes of one name in one stream: which one a use means is unknown,
                # so the name reads as unparsed and every fail-closed reader refuses it
                found[name] = dict(prior, unparsed=f"conflicting complete records named {name}")
                continue
            if prior is not None and prior.get("unparsed"):
                continue
            found[name] = out
        return found


def _shape(layout):
    """What two complete records of one name must agree on to be one class."""
    return (layout.get("size"), layout.get("vfptr"), [tuple(b) for b in layout.get("bases", [])],
            [tuple(f) for f in layout.get("fields", [])], sorted((layout.get("vslots") or {}).items()))


def type_stream(obj_bytes):
    return b"".join(data for name, data in coff_sections(obj_bytes) if name == b".debug$T")


# ---------------------------------------------------------------- compile + cache

def class_body_spans(text, include_templates=False):
    """(name, start, end, key) for namespace-scope bodies, in source order.

    End is just after the closing brace. Comments and literals retain their
    offsets but cannot open or close scopes. Nested and local types are not
    standalone private views, even when their heads start in column zero.
    Explicitly qualified heads retain their full spelling.
    """
    code = NON_CODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)
    heads = {m.end() - 1: m for m in HEAD.finditer(code)}
    namespaces = {m.end() - 1 for m in NAMESPACE.finditer(code)}
    # Linkage specifications do not create a C++ scope. Check the masked
    # prefix too, so an apparent extern block inside a comment is ignored.
    namespaces.update(m.end() - 1 for m in LINKAGE.finditer(text)
                      if code[m.start():m.start() + 6] == "extern")
    stack, found = [], []
    for brace in re.finditer(r"[{}]", code):
        pos = brace.start()
        if brace.group() == "{":
            head = heads.get(pos)
            if any(not namespace for namespace, _ in stack):
                head = None
            stack.append((pos in namespaces, head))
        elif stack:
            _, head = stack.pop()
            if head and (include_templates or not head.group("template")):
                found.append((head.group("name"), head.start(), pos + 1, head.group("key")))
    return sorted(found, key=lambda span: span[1])


def class_bodies(text):
    """Names of classes `text` declares a namespace-scope body for (private views)."""
    return [name for name, _, _, _ in class_body_spans(text)]


# The scope-aware reader below is opt-in. class_body_spans and class_bodies keep
# their spelling-only behaviour, which class_views, progress.py and private_views
# depend on; this reader is for registered-key decisions (class templates). It
# fails closed: text it cannot read with certainty gives None, never a partial list.
IDENT = r"[A-Za-z_]\w*"
CLASS_KEY = re.compile(r"\b(?P<key>class|struct)\b")
DECLSPEC = re.compile(r"__declspec\s*\(")
NAMESPACE_HEAD = re.compile(r"\bnamespace\s*(?P<name>" + IDENT + r"(?:\s*::\s*" + IDENT + r")*)?\s*\{")
TEMPLATE_MEMBER = re.compile(r"\btemplate\s*<")
ACCESS = re.compile(r"^(?:\s*(?:public|protected|private)\s*:)+")
OTHER_SCOPE = re.compile(r"^(?:typedef\s+)?(?:enum|union)\b[^;{}()]*$")
FUNCTION_HEAD = re.compile(r"\)\s*(?:const\b\s*)?(?:volatile\b\s*)?(?:throw\s*\([^;{}]*\)\s*)?(?::[^;{}]*)?$")
KNOWN_SCOPE = "scope"


class Ambiguous(Exception):
    """The reader cannot prove what a brace or head is."""


def _masked(text):
    """`text` with comments and literals blanked, offsets kept."""
    return NON_CODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)


def _ambiguous(text, code):
    """Constructs that can manufacture or hide scope: the refusals moved_bodies uses."""
    return bool(re.search(r'(?:u8|u|U|L)?R"|<%|%>|<:|:>|\\\r?\n', text)
                or re.search(r"\?\?[=/'()!<>-]", text)
                or re.search(r"^[ \t\f\v]*(?:#|%:)(?![ \t]*(?:include|pragma)\b)", code, re.M))


def _without_includes(code):
    """`code` with #include and #pragma lines blanked: neither can open or close a scope."""
    return re.sub(r"^[ \t]*#[ \t]*(?:include|pragma)\b[^\n]*", lambda m: " " * len(m.group()), code, flags=re.M)


def _skip_space(code, pos):
    while pos < len(code) and code[pos].isspace():
        pos += 1
    return pos


def _angle_end(code, pos):
    """Index just after the `>` closing the `<` at code[pos]; parentheses hide `<`/`>`; None if
    a `;`, `{` or `}` comes first."""
    angle = paren = 0
    for i in range(pos, len(code)):
        char = code[i]
        if char == "(":
            paren += 1
        elif char == ")":
            paren -= 1
            if paren < 0:
                return None
        elif paren:
            continue
        elif char == "<":
            angle += 1
        elif char == ">":
            angle -= 1
            if angle == 0:
                return i + 1
        elif char in ";{}":
            return None
    return None


def _brace_end(code, pos):
    """Index just after the `}` closing the `{` at code[pos], or None."""
    depth = 0
    for i in range(pos, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return i + 1
    return None


def _paren_end(code, pos):
    depth = 0
    for i in range(pos, len(code)):
        if code[i] == "(":
            depth += 1
        elif code[i] == ")":
            depth -= 1
            if depth == 0:
                return i + 1
    return None


def _template_prefix(code, pos):
    """True when the class key at `pos` follows `template <...>` (parameters may hold parenthesised
    comparisons, defaults with nested templates, and template template parameters)."""
    i = pos - 1
    while i >= 0 and code[i].isspace():
        i -= 1
    if i < 0 or code[i] != ">":
        return False
    angle = paren = 0
    while i >= 0:
        char = code[i]
        if char == ")":
            paren += 1
        elif char == "(":
            paren -= 1
        elif paren:
            pass
        elif char == ">":
            angle += 1
        elif char == "<":
            angle -= 1
            if angle == 0:
                break
        elif char in ";{}":
            return False
        i -= 1
    if i < 0:
        return False
    return re.search(r"\btemplate\s*$", code[:i]) is not None


def _qualified_name(code, pos):
    """(spelling, args, end) of `A::B<args>::C<args>` at pos: the spelling keeps inner argument
    lists, `args` is the last component's list (None when it has none), whitespace collapsed."""
    parts, args = [], None
    while True:
        name = re.compile(IDENT).match(code, pos)
        if not name:
            return None
        pos = _skip_space(code, name.end())
        piece, args = name.group(), None
        if pos < len(code) and code[pos] == "<":
            end = _angle_end(code, pos)
            if end is None:
                raise Ambiguous("unbalanced template argument list")
            args = re.sub(r"\s*([<>,])\s*", r"\1", " ".join(code[pos + 1:end - 1].split()))
            piece += "<" + args + ">"
            pos = _skip_space(code, end)
        parts.append(piece)
        if code[pos:pos + 2] == "::":
            pos = _skip_space(code, pos + 2)
            continue
        if args is not None:
            parts[-1] = name.group()             # the last component's list is `args`, not spelling
        return "::".join(parts), args, pos


def _class_head(code, match):
    """(name, args, brace) when this class key opens a class body; (None, None, brace) for an
    anonymous one; None when it opens no body (a declaration, friend or elaborated type)."""
    pos = _skip_space(code, match.end())
    while True:
        declspec = DECLSPEC.match(code, pos)
        if not declspec:
            break
        end = _paren_end(code, declspec.end() - 1)
        if end is None:
            raise Ambiguous("unbalanced __declspec")
        pos = _skip_space(code, end)
    if pos < len(code) and code[pos] == "{":
        return None, None, pos
    head = _qualified_name(code, pos)
    if head is None:
        return None
    name, args, pos = head
    if pos < len(code) and code[pos] == ":" and code[pos:pos + 2] != "::":
        paren = 0
        for i in range(pos + 1, len(code)):
            char = code[i]
            if char == "(":
                paren += 1
            elif char == ")":
                paren -= 1
            elif char in ";}" and not paren:
                return None
            elif char == "{" and not paren:
                pos = i
                break
        else:
            return None
    if pos >= len(code) or code[pos] != "{":
        return None
    return re.sub(r"\s+", "", name), args, pos


def _typedef_name(code, start, close):
    """The declarator of `typedef struct { ... } NAME;`; None for an anonymous non-typedef body."""
    if not re.search(r"\btypedef\s*$", code[:start]):
        return None
    after = re.compile(r"\s*(" + IDENT + r")\s*[;,\[]").match(code, close)
    if not after:
        raise Ambiguous("typedef of an anonymous class without a plain declarator")
    return after.group(1)


def _proven_brace(statement, owner=None):
    """A `{` that opens no class or namespace: an initializer, an enum/union body or a function
    body with a type, a qualified name or an operator before its parameter list (in a class,
    also `owner`'s own constructor or destructor)."""
    statement = ACCESS.sub("", statement).strip()
    if statement.endswith("=") or statement.endswith(","):
        return "initializer"
    # A template prefix is no evidence of a return type: strip and validate every
    # `template <...>` first, so `template <class T> MACRO(X) {` stays unproven.
    while True:
        prefix = re.match(r"template\s*<", statement)
        if not prefix:
            break
        end = _angle_end(statement, prefix.end() - 1)
        if end is None:
            return None
        statement = statement[end:].strip()
    if OTHER_SCOPE.match(statement):
        return "other"
    tail = FUNCTION_HEAD.search(statement)
    if not tail:
        return None
    # The text before the parameter list: find the `(` that opens it.
    depth, open_at = 0, None
    for i in range(tail.start(), -1, -1):
        if statement[i] == ")":
            depth += 1
        elif statement[i] == "(":
            depth -= 1
            if depth == 0:
                open_at = i
                break
    if open_at is None:
        return None
    before = statement[:open_at].strip()
    if re.search(r"(?:::|\boperator\b)", before):
        return "function"
    if owner and re.fullmatch(r"(?:(?:inline|explicit|virtual|__forceinline)\s+)*~?\s*" + re.escape(owner), before):
        return "function"
    tokens = re.findall(r"[A-Za-z_]\w*|[*&]", before)
    return "function" if len(tokens) >= 2 else None


def class_identities(text):
    """[(qualified, name, args, is_template, start, end, key)] for every class body outside a
    function body, in source order; None when the text cannot be read with certainty.

    Opt-in and scope-tracked: namespaces and enclosing classes are part of `qualified`
    (`(anonymous)` for an unnamed namespace), so a member template Outer::X is not FX::X.
    `args` is a specialization's argument list (None for a primary). Every brace at namespace or
    class scope must be a class, namespace, linkage, enum or union body, an initializer, or a
    function body with a provable head; anything else (a macro-generated scope) gives None.
    Declarations, explicit instantiations and uses define no body and are absent.
    """
    code = _masked(text)
    if _ambiguous(text, code):
        return None
    code = _without_includes(code)
    try:
        heads = {}
        for match in CLASS_KEY.finditer(code):
            head = _class_head(code, match)
            if head:
                name, args, brace = head
                heads[brace] = (name, args, _template_prefix(code, match.start()), match.start(),
                                match.group("key"))
        namespaces = {m.end() - 1: m for m in NAMESPACE_HEAD.finditer(code)}
        linkage = {m.end() - 1 for m in LINKAGE.finditer(text) if code[m.start():m.start() + 6] == "extern"}
        stack, found, boundary = [], [], 0
        for token in re.finditer(r"[{};]", code):
            pos, char = token.start(), token.group()
            known = all(frame[0] is not None for frame in stack)
            if char == "{":
                head, namespace = heads.get(pos), namespaces.get(pos)
                if namespace:
                    path = tuple(re.sub(r"\s+", "", namespace.group("name") or "(anonymous)").split("::"))
                elif head and head[0] is not None:
                    path = tuple(head[0].split("::"))
                elif head:
                    path = ("(anonymous class)",)
                elif pos in linkage:
                    path = ()
                elif not known:
                    path = None                  # nested in a function or initializer: not ours
                else:
                    owner = next((frame[1][0].split("::")[-1].split("<")[0] for frame in reversed(stack)
                                  if frame[1] and frame[1][0]), None)
                    kind = _proven_brace(code[boundary:pos], owner)
                    if kind is None:
                        return None              # a brace this reader cannot name
                    path = None if kind in ("function", "initializer") else (KNOWN_SCOPE,)
                scope = tuple(part for frame in stack for part in (frame[0] or ()) if part != KNOWN_SCOPE)
                stack.append((path, head if known else None, scope))
            elif char == "}":
                if not stack:
                    return None
                _path, head, scope = stack.pop()
                if head:
                    name, args, is_template, start, key = head
                    if name is None:
                        name = _typedef_name(code, start, pos + 1)
                    if name is not None:
                        qualified = "::".join(scope + tuple(name.split("::")))
                        found.append((qualified, name, args, is_template, start, pos + 1, key))
            boundary = token.end()
    except Ambiguous:
        return None
    if stack:
        return None
    return sorted(found, key=lambda item: item[4])


def template_member_definitions(text, name):
    """[(start, end)] of out-of-class definitions of class template `name`'s members and static
    data (`template <...> ... name<...>::member` followed by `(`, `=`, `;` or `[`, up to its
    closing `}` or `;`); None when the text is ambiguous or a definition does not close. `name`
    is the class's own (unqualified) name."""
    code = _masked(text)
    if _ambiguous(text, code):
        return None
    code = _without_includes(code)
    depth = 0
    for char in code:
        depth += char == "{"
        depth -= char == "}"
        if depth < 0:
            return None
    if depth:
        return None
    owner = re.compile(r"\b" + re.escape(name) + r"\s*<")
    member = re.compile(r"\s*::\s*(?:~\s*" + IDENT + r"|operator\b[^(;{}]*|" + IDENT + r")\s*(?=[(=;\[])")
    found = []
    for match in TEMPLATE_MEMBER.finditer(code):
        end = _angle_end(code, match.end() - 1)
        if end is None:
            continue
        stop = len(code)
        for char in "{;=":
            at = code.find(char, end)
            if at != -1:
                stop = min(stop, at)
        head = close = None
        for candidate in owner.finditer(code, end, stop):
            after = _angle_end(code, candidate.end() - 1)
            if after is not None and member.match(code, after):
                head, close = candidate, member.match(code, after).end()
                break
        if head is None:
            continue
        if re.search(r"\b(?:class|struct)\b", code[end:head.start()]):
            continue                              # a class head or a member class, not a definition
        i, paren = close, 0
        while i < len(code):
            char = code[i]
            if char in "([":
                paren += 1
            elif char in ")]":
                paren -= 1
            elif char == ";" and paren == 0:
                found.append((match.start(), i + 1))
                break
            elif char == "{" and paren == 0:
                body_end = _brace_end(code, i)
                if body_end is None:
                    return None
                after = _skip_space(code, body_end)
                if after < len(code) and code[after] == ";":     # a braced static initializer
                    body_end = after + 1
                found.append((match.start(), body_end))
                break
            elif char == "}":
                return None
            i += 1
        else:
            return None                           # a definition that never closes
    return found


def sha(data):
    return hashlib.sha256(data).hexdigest()


def file_sha(path):
    try:
        return sha(Path(path).read_bytes())
    except OSError:
        return "missing"


def include_path(name):
    """A header as cl's /showIncludes names it, as this host can read it. Under Wine (any host
    but Windows) drive Z: is the root and a backslash separates (`Z:\\home\\...\\string.h`,
    `reference/shims/bfme2_ascii\\ascii_string.h`); a relative name is the compiler's working
    directory's, ROOT. Another drive stays unreadable here."""
    name = name.strip()
    if os.name != "nt":
        name = name.replace("\\", "/")
        if re.match(r"[Zz]:/", name):
            name = name[2:]
    path = Path(name)
    return path if path.is_absolute() else ROOT / path


def headers_unchanged(headers):
    """Whether every header a cached compile included still holds the bytes it held. One that
    cannot be read now, or could not be read then ("missing"), is no proof: the entry is not
    reused (a header edited from 4 to 8 bytes must not keep its stale layout)."""
    return all(digest != "missing" and file_sha(include_path(name)) == digest for name, digest in headers.items())


def parsed_path(digest):
    # Parsed evidence depends on the reader as well as the compiler's bytes.
    return CACHE / (f"types_{digest}_{PARSER_HASH}.json")


def compile_layouts(source, builder=None, use_cache=True, extra_flags=()):
    """{class: layout} for every class in the unit's type stream; raises on compile error."""
    builder = builder or build_module()
    source = (ROOT / source).resolve()
    rel = source.relative_to(ROOT).as_posix()
    stem = re.sub(r"[^\w.-]", "_", rel)
    CACHE.mkdir(parents=True, exist_ok=True)
    obj, meta = CACHE / (stem + ".obj"), CACHE / (stem + ".json")
    command, env = builder.compiler_command(source, ROOT / "build" / "_class_layouts.obj")
    command = [a for a in command if not a.startswith(("-Fo", "/Fo"))]
    command[-1:-1] = [*extra_flags, "-Fo" + obj.relative_to(ROOT).as_posix(), "-Z7", "-showIncludes"]
    key = sha("\0".join(command).encode() + source.read_bytes())
    if use_cache and REVERSED_GROUPS and meta.exists():
        cached = json.loads(meta.read_text(encoding="utf-8"))
        if cached.get("key") == key and headers_unchanged(cached["headers"]):
            parsed = parsed_path(cached["types"])
            if parsed.exists():
                return json.loads(parsed.read_text(encoding="utf-8"))
            if obj.exists():
                stream = type_stream(obj.read_bytes())
                if sha(stream) == cached["types"]:
                    result = TypeStream(stream).classes() if stream else {}
                    parsed.write_text(json.dumps(result), encoding="utf-8")
                    return result
    done = subprocess.run(command, cwd=ROOT, env=env, capture_output=True, text=True, errors="replace")
    if done.returncode:
        # Each error keeps its own text, not just its code. A bare "C1083" cannot say which
        # include was missing, and for a probe this message is all that reaches the caller --
        # header_queue.tsv rows record it verbatim and are the next worker's only account.
        found = re.findall(r"error (C\d+)([^\n]*)", done.stdout + done.stderr)
        errors = [code + rest[:160] for code, rest in found]
        raise RuntimeError(f"{rel}: compile failed: " + ("; ".join(errors[:3]) or (done.stdout + done.stderr)[-400:]))
    headers = {}
    for line in done.stdout.splitlines():
        found = re.match(r"Note: including file:\s*(.+)$", line)
        if found:
            path = found.group(1).strip()
            headers[path] = file_sha(include_path(path))
    stream = type_stream(obj.read_bytes())
    digest = sha(stream)
    parsed = parsed_path(digest)
    if use_cache and REVERSED_GROUPS and parsed.exists():
        result = json.loads(parsed.read_text(encoding="utf-8"))
    else:
        result = TypeStream(stream).classes() if stream else {}
        if REVERSED_GROUPS:                     # never cache the control's naive parse
            parsed.write_text(json.dumps(result), encoding="utf-8")
    meta.write_text(json.dumps({"key": key, "headers": headers, "types": digest}), encoding="utf-8")
    return result


def private_views(source, builder=None, only=None, use_cache=True):
    """{class: layout} for the classes the unit itself declares (plus their bases)."""
    text = (ROOT / source).read_text(encoding="latin-1")
    declared = [c for c in class_bodies(text) if not only or c in only]
    if not declared:
        return {}
    every = compile_layouts(source, builder, use_cache)
    out = {}
    for name in declared:
        layout = every.get(name)
        if layout is None:
            continue
        out[name] = layout
        for base, _ in layout.get("bases", []):
            if base in every and base not in out:
                out[base] = dict(every[base], base_only=True)
    return out


# ---------------------------------------------------------------- the slot-order probe

PROBE = """\
class Probe {
public:
    virtual ~Probe();
    virtual int f(int);
    virtual int f(float);
    virtual int f(char *);
    virtual void g();
    virtual int h(short);
    virtual int h(double);
};
int (Probe::*probe_f_int)(int) = &Probe::f;
int (Probe::*probe_f_float)(float) = &Probe::f;
int (Probe::*probe_f_char)(char *) = &Probe::f;
void (Probe::*probe_g)() = &Probe::g;
int (Probe::*probe_h_short)(short) = &Probe::h;
int (Probe::*probe_h_double)(double) = &Probe::h;
"""


def mangled_number(text):
    """MSVC encoded number: 0-9 -> 1-10, else hex digits A-P terminated by '@'."""
    if text[0].isdigit():
        return int(text[0]) + 1, text[1:]
    end = text.index("@")
    value = 0
    for char in text[:end]:
        value = value * 16 + (ord(char) - ord("A"))
    return value, text[end + 1:]


def run_probe(builder=None):
    """[(slot, CodeView name, thunk-proved name)] and whether they all agree."""
    builder = builder or build_module()
    CACHE.mkdir(parents=True, exist_ok=True)
    source = CACHE / "slot_probe.cpp"
    source.write_text(PROBE, encoding="utf-8")
    layout = compile_layouts(source.relative_to(ROOT), builder, use_cache=False)["Probe"]
    obj = CACHE / ("build_class_layouts_slot_probe.cpp.obj")
    data = obj.read_bytes()
    thunks = {}
    for name in coff_symbols(data):
        found = re.match(r"\?\?_9@\$B(.+?)AE$", name)
        if found:
            thunks[mangled_number(found.group(1))[0] // 4] = name
    # Which overload each thunk serves: the data symbol initialised with it.
    relocs = probe_initialisers(data)
    proved = {slot: relocs.get(thunk) for slot, thunk in thunks.items()}
    rows, ok = [], bool(proved)
    for slot, member in sorted(proved.items()):
        cv = layout["vslots"].get(str(slot), "")
        rows.append((slot, cv, member))
        ok &= cv == member
    return rows, ok


def probe_initialisers(data):
    """{thunk symbol: 'f(int)'-style member} from the .data relocations of the probe."""
    names = list(coff_symbols_indexed(data))
    out = {}
    table = struct.unpack_from("<I", data, 8)[0]
    count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
    spell = {"probe_f_int": "f(int)", "probe_f_float": "f(float)", "probe_f_char": "f(char*)",
             "probe_g": "g()", "probe_h_short": "h(short)", "probe_h_double": "h(double)"}
    symbols_at = {}
    for index, name, value, section in names:
        for key, member in spell.items():
            if re.match(r"\?" + key + "@@", name):
                symbols_at[(section, value)] = member
    for number in range(count):
        header = 20 + optional + 40 * number
        relocs, nrel = struct.unpack_from("<I", data, header + 24)[0], struct.unpack_from("<H", data, header + 32)[0]
        for r in range(nrel):
            vaddr, symbol, _ = struct.unpack_from("<IIH", data, relocs + 10 * r)
            target = next((n for i, n, _, _ in names if i == symbol), "")
            member = symbols_at.get((number + 1, vaddr))
            if member and target.startswith("??_9"):
                out[target] = member
    del table
    return out


def coff_symbols_indexed(data):
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    index = 0
    while index < count:
        entry = table + 18 * index
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            name = data[start:data.index(b"\0", start)]
        else:
            name = raw.rstrip(b"\0")
        value, section = struct.unpack_from("<Ih", data, entry + 8)
        yield index, name.decode("latin-1"), value, section
        index += 1 + data[entry + 17]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("files", nargs="*")
    parser.add_argument("--class", dest="names", action="append")
    parser.add_argument("--no-cache", action="store_true")
    parser.add_argument("--probe", action="store_true")
    args = parser.parse_args(argv)
    builder = build_module()
    if args.probe:
        rows, ok = run_probe(builder)
        for slot, cv, proved in rows:
            print(f"  slot {slot}: codeview {cv:<14} thunk {proved}")
        print("slot order: " + ("OK" if ok else "MISMATCH (do not trust CodeView slot evidence)"))
        return 0 if ok else 1
    out, bad = {}, 0
    for path in args.files:
        try:
            out[path] = private_views(path, builder, set(args.names or ()), not args.no_cache)
        except RuntimeError as exc:
            out[path] = {"error": str(exc)}
            bad = 1
    json.dump(out, sys.stdout, indent=1, sort_keys=True)
    print()
    return bad


if __name__ == "__main__":
    sys.exit(main())
