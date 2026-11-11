#!/usr/bin/env python3
"""The canonical-header lane: one header per class, adopted unit by unit.

WHY. Hundreds of units declare their own private copy of the same class
(Coord3D, AsciiString, Object). Each copy byte-matches its own unit and
blocks the link: inline members are COMDATs that differ between units, and
members one copy omits are unresolved. The fix is one evidenced header per
class and every unit including it. Research 11 measured that true layout
conflicts are rare (0-17%) and spelling divergence near 100%, so the lane is
mechanical: generate, swap, prove each unit with the byte gate, queue the rest.

PIPELINE (per class, in DEPENDENCY_ORDER):
  1. contract   tools/class_contract.py decides the ABI (rule order bytes ->
                retail access -> retail vtable -> ZH -> majority; ties queue).
  2. header     generated from the contract, or the class's registered header.
                Every variant declares every member function and static
                member the views declare (special_declarations, reading
                declaration_records); views that disagree on one hold the
                class.
  3. tournament 2-4 header variants (data only, + user default ctor, + the
                views' non-special methods) are each gated against every unit;
                the variant with the most passes is frozen. Byte-equivalent is
                not retail-true: the contract, not the tournament, fixes layout.
  4. codemod    strip the unit's view (and its dependency views, e.g.
                StringBase with AsciiString), #include the header where the
                view stood, rename the unit's references to its private field
                names to the header's (field_renames: one offset and size is
                one field), and rename the unit's ledger rows when its view
                spelled the other class-key (`U`/`V` mangling).
  5. gate       tools/build.py (BFME2) / build.sh (BFME1) on the cohort;
                split a failed cohort to retain individual failure diagnostics.
  6. queue      every unit that does not pass gets an item with its first
                diagnostic and the acceptance command below.

ACCEPTANCE (the queue item's pass test, `accept`): the unit has no private
body for the class, includes the header (or its evidenced constructor companion),
every ledger row in it still byte-matches, and link_check predicts no loss of
its census-linked bytes (an explicit per-unit result is required); a batch additionally
compares link_cycle's closed_strict rows before/after (`closure-diff`).

GATE COST. Changing a registered header re-verifies only its dependents
(tools/header_dependents.py, wired into pre-commit); `gate-cost` measures it.

    python3 tools/header_adopt_lane.py order
    python3 tools/header_adopt_lane.py run --class Coord3D --header PATH --generate --sample 60 --apply
    python3 tools/header_adopt_lane.py accept --class Coord3D FILE...
    python3 tools/header_adopt_lane.py adopt --class Object --header PATH [--apply] FILE...
    python3 tools/header_adopt_lane.py gate-cost --header PATH
    python3 tools/header_adopt_lane.py closure-diff BEFORE.csv AFTER.csv
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import hashlib
import io
import json
import os
import random
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_contract  # noqa: E402
import class_layouts  # noqa: E402
import wb_gold  # noqa: E402

BFME2 = (ROOT / "reverse" / "functions.csv").exists()
REVERSE = class_contract.REVERSE
LEDGER = class_contract.LEDGER
QUEUE = REVERSE / "header_queue.tsv"
REGISTRY = REVERSE / "canonical_classes.csv"
SCRATCH = ROOT / "build" / "header_lane"

# Adopt in this order: a header can only be adopted once the types it uses
# have one definition (research 11, section 5).
DEPENDENCY_ORDER = [
    ("typedefs", ["Bool", "Real", "Int", "UnsignedInt"]),
    ("value types", ["Coord2D", "Coord3D", "ICoord2D", "ICoord3D", "Region2D", "Region3D", "IRegion2D", "RGBColor"]),
    ("string base", ["StringBase"]),
    ("strings", ["AsciiString", "UnicodeString"]),
    ("snapshot", ["Snapshot"]),
    ("xfer", ["Xfer"]),
    ("thing", ["Thing"]),
    ("object", ["Object"]),
]
# Views of these are stripped together with the class (the header brings them in).
STRIP_WITH = {"AsciiString": ["StringBase"], "UnicodeString": ["StringBase"]}
IDENT_CHAR = re.compile(r"[\w$]")
SPLICE = re.compile(r"\\\r?\n")
RAW_STRING = re.compile(r'(?<![\w$])(?:u8|[LuU])?R"([^ ()\\\t\v\f\r\n"]{0,16})\(')


# ---------------------------------------------------------------- source surgery

def spliced_identifiers(text):
    """Identifiers a line splice joins: `other_\\\nm_flags` is one token, not two."""
    out = set()
    for m in SPLICE.finditer(text):
        before, after = m.start(), m.end()
        if not before or after >= len(text):
            continue
        if not (IDENT_CHAR.match(text[before - 1]) and IDENT_CHAR.match(text[after])):
            continue
        start, end = before, after
        while start and IDENT_CHAR.match(text[start - 1]):
            start -= 1
        while end < len(text) and IDENT_CHAR.match(text[end]):
            end += 1
        out.add(SPLICE.sub("", text[start:end]))
    return out


def masked(text, keep_literals=False):
    """`text` with comments and literals blanked, one character per input character so
    positions still line up. A line splice joins its lines: a continued `//` comment is one
    comment, and an identifier a splice splits is one token (blanked whole, so a rename can
    never reach half of it). Raw strings, including the ones holding a quote, are blanked
    whole. `keep_literals` keeps string and character literals (an `#include` names a file)."""
    out = list(text)
    i, n = 0, len(text)

    def blank(a, b):
        for k in range(a, b):
            if out[k] not in "\r\n":
                out[k] = " "

    for m in SPLICE.finditer(text):
        before, after = m.start(), m.end()
        if before and after < n and IDENT_CHAR.match(text[before - 1]) and IDENT_CHAR.match(text[after]):
            start, end = before, after
            while start and IDENT_CHAR.match(text[start - 1]):
                start -= 1
            while end < n and IDENT_CHAR.match(text[end]):
                end += 1
            blank(start, end)
    while i < n:
        ch = text[i]
        if ch == "/" and text.startswith("//", i):
            j = i + 2
            while j < n:
                if text[j] == "\n":
                    break
                if text[j] == "\\" and text.startswith("\n", j + 1):
                    j += 2
                    continue
                if text[j] == "\\" and text.startswith("\r\n", j + 1):
                    j += 3
                    continue
                j += 1
            blank(i, j)
            i = j
            continue
        if ch == "/" and text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            blank(i, j)
            i = j
            continue
        raw = RAW_STRING.match(text, i)
        if raw:
            close = ")" + raw.group(1) + '"'
            j = text.find(close, raw.end())
            j = n if j < 0 else j + len(close)
            if not keep_literals:
                blank(i, j)
            i = j
            continue
        if ch in "\"'":
            j = i + 1
            while j < n:
                if text[j] == "\\" and j + 1 < n:
                    j += 2
                    continue
                if text[j] == ch:
                    j += 1
                    break
                if text[j] == "\n":
                    break
                j += 1
            if not keep_literals:
                blank(i, j)
            i = j
            continue
        if ch == "\\" and text.startswith("\n", i + 1):
            out[i] = " "
            i += 2
            continue
        if ch == "\\" and text.startswith("\r\n", i + 1):
            out[i] = " "
            i += 3
            continue
        i += 1
    return "".join(out)


def body_span(text, name):
    """(start, end, key) of the namespace-scope definition of `name`, with a
    `template <...>` line above it and the closing `;` and newline; None if absent."""
    code = masked(text)
    for found, start, index, key in class_layouts.class_body_spans(text, include_templates=True):
        if found != name:
            continue
        tail = re.match(r"[ \t\r\n\v\f]*;[ \t]*\r?\n?", code[index:])
        if not tail:
            continue
        return start, index + tail.end(), key
    return None


def swap(text, names, include):
    """Text with every view of `names` removed and `include` where the first stood."""
    swapped = swap_at(text, names, include)
    return swapped and swapped[0]


def swap_at(text, names, include):
    """(swap's text, the offset just past the inserted #include line), or None."""
    spans = []
    for name in names:
        span = body_span(text, name)
        while span:
            spans.append(span[:2])
            text = text[:span[0]] + "\0" * (span[1] - span[0]) + text[span[1]:]
            span = body_span(text, name)
    if not spans:
        return None
    first = min(s for s, _ in spans)
    line = f'#include "{include}"\n'
    out = text[:first] + line + text[first:]
    return out.replace("\0", ""), first + len(line)        # no view starts before `first`


# ---------------------------------------------------------------- field renames
# A unit's private view names its fields its own way; the canonical header names them
# once. Swapping the view out leaves the unit's code spelling the private names, so the
# swap renames them: a private field and the header's field at one offset and size (in
# the class or one of its non-virtual bases) are one field. Only references proven to be
# members of the adopting class are rewritten (scoped_rename); a unit with any other
# occurrence of an old name is refused: code inside an inactive #if is never compiled,
# so no byte check would catch a wrong rename there.

PROBE_FN = "header_adopt_lane_layout_probe"


TOOLCHAIN_MARKERS = ("// platformsdk", "// dxsdk", "// stlport46", "// stlport")


def lost_markers(text, kept):
    """The toolchain marker lines `text` carries that `kept` does not. build.py and
    stlport_overlay read these from anywhere in the file to choose include directories, so a
    marker standing below the unit's view is cut away with the body and the probe would
    compile without the PlatformSDK, DirectX or STLport headers -- C1083 on <windows.h> for a
    unit whose `// platformsdk` line sits further down."""
    out = []
    for marker in TOOLCHAIN_MARKERS:
        found = re.compile(r"(?m)^" + re.escape(marker) + r"[ \t]*$")
        if found.search(text) and not found.search(kept):
            out.append(marker)
    return out


def probe_text(text, strip, include):
    """The unit cut just past where its first view stood, the header included there, any
    toolchain marker the cut dropped, and a function that makes the compiler lay every
    stripped class out. The cut code spells the private field names the header lacks; the
    code before the view cannot reach the members."""
    swapped = swap_at(text, strip, include)
    if swapped is None:
        return None
    out, cut = swapped
    kept = out[:cut]
    params = ", ".join(f"{c} *p{i}" for i, c in enumerate(strip))
    sizes = " + ".join(f"(int)sizeof(*p{i})" for i in range(len(strip)))
    markers = "".join(f"{marker}\n" for marker in lost_markers(text, kept))
    return kept + markers + f"\nint {PROBE_FN}({params}) {{ return {sizes}; }}\n"


def compile_text(source, text):
    """{class: layout} for `text` compiled as `source` (its flags and include paths); None is
    the unit as it stands. Restores the unit. The probe is never served from class_layouts'
    cache: its text names only the header, and under Wine the cache records the headers'
    paths as missing, so a header edit would not invalidate it."""
    path = ROOT / source
    original = path.read_bytes()
    if text is None or text.encode("latin-1") == original:
        return class_layouts.compile_layouts(source)
    try:
        path.write_bytes(text.encode("latin-1"))
        return class_layouts.compile_layouts(source, use_cache=False)
    finally:
        path.write_bytes(original)


def flat_fields(name, layouts, base=0, seen=()):
    """{(offset, size): [(field, cvtype, declaring class), ...]} for `name`'s data members
    and those of its non-virtual bases, at their offsets in `name` (a virtual base has no
    fixed offset). Every candidate is kept: union members share an offset and size."""
    lay = layouts.get(name) or {}
    out = {}
    for base_name, offset in lay.get("bases", []):
        if offset >= 0 and base_name not in seen:
            for key, found in flat_fields(base_name, layouts, base + offset, seen + (name,)).items():
                out.setdefault(key, []).extend(found)
    for offset, field, cvtype, size in lay.get("fields", []):
        out.setdefault((base + offset, size), []).append((field, cvtype, name))
    return out


VPTR_SIZE = 4                                           # 32-bit target


def vptr_offsets(name, layouts, base=0, seen=()):
    """The offsets in `name` the compiler fills with a vftable pointer: its own, where it
    introduces one, and one per non-virtual base that introduces one, at that base's offset.
    A flat private view of a polymorphic class spells these out as pointer members because the
    view itself declares no virtual function; the canonical header declares the virtuals and
    the compiler supplies the pointers, so no canonical field carries those offsets."""
    lay = layouts.get(name) or {}
    out = {base} if lay.get("vfptr") else set()
    for base_name, offset in lay.get("bases", []):
        if offset >= 0 and base_name not in seen:
            out |= vptr_offsets(base_name, layouts, base + offset, seen + (name,))
    return out


def read_path(path):
    try:
        return Path(path).read_text(encoding="latin-1")
    except OSError:
        return None


def read_source(source):
    return read_path(ROOT / source)


def header_comment_splice(text):
    """Find line-comment splices that change which physical text is code."""
    # Translation phase 2 precedes comment recognition, including when a splice
    # forms the two slashes. Keep offsets so the diagnostic names the real line.
    logical, offsets = [], []
    i = 0
    while i < len(text):
        splice = SPLICE.match(text, i)
        if splice:
            i = splice.end()
        else:
            logical.append(text[i])
            offsets.append(i)
            i += 1
    original = text
    text = "".join(logical)
    i, n = 0, len(text)
    while i < n:
        if text.startswith("//", i):
            end = text.find("\n", i)
            end = n if end < 0 else end
            original_end = offsets[end] if end < n else len(original)
            splices = list(SPLICE.finditer(original, offsets[i], original_end))
            # A chain of independently commented physical lines has the same
            # visible tokens before and after splicing (STLport uses this for
            # commented-out #if conditions). Every continuation must already
            # start a line comment; a splice forming // itself remains unsafe.
            if splices and (not original.startswith("//", offsets[i]) or any(
                    not re.match(r"[ \t]*//", original[splice.end():])
                    for splice in splices)):
                return offsets[i]
            i = end + 1
        elif text.startswith("/*", i):
            end = text.find("*/", i + 2)
            i = n if end < 0 else end + 2
        elif (raw := RAW_STRING.match(text, i)):
            close = ")" + raw.group(1) + '"'
            end = text.find(close, raw.end())
            i = n if end < 0 else end + len(close)
        elif text[i] in "\"'":
            quote = text[i]
            i += 1
            while i < n:
                if text[i] == "\\" and i + 1 < n:
                    i += 2
                elif text[i] == quote:
                    i += 1
                    break
                else:
                    i += 1
        else:
            i += 1
    return None


def include_guarded(code):
    directives = list(re.finditer(r'(?m)^[ \t]*#[ \t]*([A-Za-z_]\w*)\b([^\n]*)', code))
    if len(directives) < 3:
        return False
    first, define = directives[:2]
    macro = first.group(2).strip()
    if (first.group(1) != "ifndef" or not re.fullmatch(r"[A-Za-z_]\w*", macro)
            or define.group(1) != "define" or define.group(2).strip() != macro
            or code[:first.start()].strip()):
        return False
    depth = 0
    for directive in directives:
        op = directive.group(1)
        if op in ("if", "ifdef", "ifndef"):
            depth += 1
        elif op == "endif":
            depth -= 1
            if depth == 0:
                return directive is directives[-1] and not code[directive.end():].strip()
        elif depth == 1 and op in ("else", "elif"):
            return False
    return False


def include_walk(source, text, include_roots=(), cache=None):
    """Scan the complete quoted include closure once, refusing unorderable cycles."""
    start = (ROOT / source).resolve()
    cache = {} if cache is None else cache
    seen, active, out = set(), set(), []
    graph, guards, invalidated = {}, {}, set()
    unknown_macro_stack = False
    stack = [(start, text, False)]
    while stack:
        path, body, leaving = stack.pop()
        if leaving:
            active.remove(path)
            continue
        if path in active:
            # Inspect the complete graph below: a guarded intermediate header
            # can terminate this cycle even when its repeated entry is unguarded.
            continue
        if path in seen:
            continue
        seen.add(path)
        active.add(path)
        stack.append((path, None, True))
        if body is None:
            return out, f"{path}: include cannot be read"
        out.append((str(path), body))
        code = masked(body)
        if include_guarded(code):
            guards[path] = re.search(r'(?m)^[ \t]*#[ \t]*ifndef[ \t]+([A-Za-z_]\w*)', code).group(1)
        # A guard is a barrier only while its macro stays defined. Treat resets
        # anywhere in the closure conservatively, including spliced directives
        # and compiler macro-stack operations; do not evaluate conditions.
        phase_two = SPLICE.sub("", body)
        spliced = masked(phase_two)
        invalidated.update(re.findall(
            r'(?m)^[ \t\f\v\r]*(?:#|%:)[ \t\f\v\r]*undef[ \t\f\v\r]+([A-Za-z_]\w*)', spliced))
        literal_code = masked(phase_two, keep_literals=True)
        for operation in re.finditer(r'\bpop_macro\b', spliced):
            arguments = re.match(r'\s*\(([^)]*)\)', literal_code[operation.end():])
            name = (re.fullmatch(r'\s*"([A-Za-z_]\w*)"\s*', arguments.group(1))
                    if arguments else None)
            if name:
                invalidated.add(name.group(1))
            else:
                unknown_macro_stack = True
        problem = re.search(r"\?\?[=/'()!<>-]", body)
        position = problem.start() if problem else header_comment_splice(body)
        if position is not None:
            line = body.count("\n", 0, position) + 1
            return out, f"{path}:{line}: trigraph or continued line comment in include input"
        children = []
        for m in re.finditer(r'(?m)^[ \t]*#[ \t]*include[ \t]*([<"])([^>"\n]+)[>"]', masked(body, keep_literals=True)):
            angle, name = m.group(1) == "<", m.group(2)
            candidates = [(base / name).resolve() for base in (path.parent, ROOT, ROOT / "Code", *include_roots)]
            if os.name != "nt":
                import build
                candidates = [Path(resolved).resolve() for p in candidates
                              if (resolved := build._case_resolve(str(p))) is not None]
            targets = list(dict.fromkeys(p for p in candidates if p.is_file()))
            if angle:
                children.extend(targets)
                continue
            if not targets:
                return out, f"{path}: unresolved include {name}"
            children.append(targets[0])
        graph[path] = children
        for target in reversed(children):
            if target not in cache:
                cache[target] = read_path(target)
            stack.append((target, cache[target], False))
    barriers = (set() if unknown_macro_stack else
                {path for path, macro in guards.items() if macro not in invalidated})
    # Removing stable guard vertices must leave an acyclic graph. Checking only
    # DFS back-edges can miss an unguarded alternate cycle through a seen node.
    colors = {}
    for first in graph:
        if first in barriers or colors.get(first):
            continue
        pending = [(first, False)]
        while pending:
            node, leaving = pending.pop()
            if leaving:
                colors[node] = 2
                continue
            if node in barriers or colors.get(node) == 2:
                continue
            if colors.get(node) == 1:
                return out, f"{node}: include cycle cannot be ordered"
            colors[node] = 1
            pending.append((node, True))
            pending.extend((child, False) for child in reversed(graph[node]))
    return out, None


def include_problem(source, text, include_roots=(), cache=None):
    return include_walk(source, text, include_roots, cache)[1]


def include_sources(source, text=None, include_roots=(), cache=None):
    if text is None:
        text = read_source(source)
    return include_walk(source, text, include_roots, cache)[0][1:]


def conditional_hierarchy(texts, classes, names):
    """Refuse conditional hierarchy declarations mentioning a rename name."""
    for path, text in texts:
        code = masked(text)
        directives = list(re.finditer(r"(?m)^[ \t]*#[ \t]*(if|ifdef|ifndef|endif|else|elif|define)\b([^\n]*)", code))
        stack, regions = [], []
        for directive in directives:
            op = directive.group(1)
            if op in ("if", "ifdef", "ifndef"):
                stack.append(directive)
            elif op == "endif" and stack:
                regions.append((stack.pop(), directive))
        # Recognize a complete outer guard only when it wraps all code and
        # defines the same macro immediately after the opening directive.
        guard = None
        guard_code = re.sub(r'(?m)^[ \t]*#[ \t]*pragma[ \t]+once\b[^\n]*', '', code)
        if directives and len(directives) >= 3 and include_guarded(guard_code):
            first, define, last = directives[0], directives[1], directives[-1]
            macro = first.group(2).strip()
            if (first.group(1) == "ifndef" and re.fullmatch(r"[A-Za-z_]\w*", macro)
                    and define.group(1) == "define" and define.group(2).strip() == macro
                    and last.group(1) == "endif"
                    and not re.sub(r"(?m)^[ \t]*#[ \t]*pragma[ \t]+once\b[^\n]*", "", code[:first.start()]).strip()
                    and not code[last.end():].strip()
                    and any(a is first and b is last for a, b in regions)):
                guard = first
        spans = [(start, end) for name, start, end, _ in class_layouts.class_body_spans(text)
                 if name in classes]
        for opening, closing in regions:
            if opening is guard:
                continue
            for start, end in spans:
                a, b = max(start, opening.end()), min(end, closing.start())
                if a >= b:
                    continue
                region = re.sub(r"(?m)^[ \t]*#.*$", "", code[a:b])
                for name in names:
                    if re.search(r"\b" + re.escape(name) + r"\b", region):
                        return f"{path}: conditional declaration involving {name} in class hierarchy"

    return None


def header_sources(header, include_roots=(), cache=None):
    """[(path, text)] for the canonical header and its quoted includes, or None when the
    header itself cannot be read."""
    text = read_source(header)
    if text is None:
        return None
    return [(header, text)] + include_sources(header, text, include_roots, cache)


def hierarchy(name, layouts):
    """`name` and its bases: a name any of them declares can hide a field of that name."""
    out, stack = [], [name]
    while stack:
        cls = stack.pop()
        if cls in out:
            continue
        out.append(cls)
        for base, _offset in (layouts.get(cls) or {}).get("bases", []):
            stack.append(base)
    return out


def class_scope(body):
    """`body` with every nested brace block blanked: only the declarations in the class
    body's own scope remain. A method body and a nested class's members drop out, while a
    nested class's head stays."""
    out, depth = list(body), 0
    for i, ch in enumerate(body):
        if ch == "{":
            depth += 1
            if depth > 1:
                out[i] = " "
        elif ch == "}":
            if depth > 1:
                out[i] = " "
            depth -= 1
        elif depth > 1 and ch not in "\r\n":
            out[i] = " "
    return "".join(out)


def header_hiding(texts, classes):
    """{identifier: [why]} for the nested types, typedefs, using aliases and enumerators the
    bodies of `classes` declare in `texts`: each hides a data field of that name."""
    out = collections.defaultdict(list)
    for _path, text in texts:
        code = masked(text)
        for name, start, end, _key in class_layouts.class_body_spans(text):
            if name not in classes:
                continue
            open_ = code.find("{", start)
            if open_ < 0:
                continue
            body = code[open_ + 1:end - 1]
            for m in re.finditer(r"\benum\b[^{};]*\{([^{}]*)\}", body):
                for ident in re.findall(r"[A-Za-z_]\w*", m.group(1)):
                    out[ident].append(f"an enumerator of {name}")
            flat = class_scope(body)
            for m in re.finditer(r"\b(?:class|struct|union|enum)\s+(?:__declspec\([^)]*\)\s*)*([A-Za-z_]\w*)", flat):
                out[m.group(1)].append(f"a nested type of {name}")
            for m in re.finditer(r"\btypedef\b([^;]*);", flat):
                alias = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*$", m.group(1))
                if alias:
                    out[alias.group(1)].append(f"a typedef of {name}")
            for m in re.finditer(r"\busing\s+([A-Za-z_]\w*)\s*=", flat):
                out[m.group(1)].append(f"a using-alias of {name}")
    return out


def hiding(name, layouts, texts=()):
    """{identifier: [why]} for every declaration in `name`'s hierarchy that can hide a field
    of that name: a static, a method, a nested type, a typedef, a using alias or an
    enumerator. Plain data fields are not here: flat_fields owns them."""
    out = collections.defaultdict(list)
    family = set(hierarchy(name, layouts))
    for cls in family:
        lay = layouts.get(cls) or {}
        for found in lay.get("statics", []):
            out[found].append(f"a static member of {cls}")
        for found in lay.get("methods", []):
            out[found].append(f"a method of {cls}")
    for ident, why in header_hiding(texts, family).items():
        out[ident].extend(why)
    return out


def block_end(code, open_):
    """The index of the `}` matching the `{` at `open_`, or the end of the text."""
    depth = 0
    for i in range(open_, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if not depth:
                return i
    return len(code)


def name_shadow(sources, name):
    """Why an unqualified `name` is not proven to be the adopting class in these sources, or
    None: a typedef, a using alias or a namespace-scoped type of that name is another type."""
    for where, text in sources:
        code = masked(text)
        if re.search(r"\btypedef\b[^;{}]*\b" + re.escape(name) + r"\s*;", code):
            return f"{where}: a typedef declares `{name}`; the unqualified name is not proven the adopting class"
        if re.search(r"\busing\s+" + re.escape(name) + r"\s*=", code):
            return f"{where}: a using-alias declares `{name}`; the unqualified name is not proven the adopting class"
        for m in re.finditer(r"\bnamespace\b[^{;]*\{", code):
            body = code[m.end():block_end(code, m.end() - 1)]
            if re.search(r"\b(?:class|struct|union|enum)\s+(?:__declspec\([^)]*\)\s*)*"
                         + re.escape(name) + r"\b", body):
                return (f"{where}: a namespace declares a type `{name}`; the unqualified name is not "
                        "proven the adopting class")
    return None


def macro_shadow(sources, mappings, text):
    """Why a `#define` in the unit or an include makes a rename unsafe, or None: a macro that
    names a receiver, an old or new field, or the class itself rewrites the tokens around it."""
    olds = {old for m in mappings.values() for old in m}
    news = {new for m in mappings.values() for new in m.values()}
    code = masked(text)
    receivers = {m.group(1) for old in olds
                 for m in re.finditer(r"([A-Za-z_]\w*)\s*(?:->|\.)\s*" + re.escape(old) + r"\b", code)}
    watched = olds | news | set(mappings) | receivers
    for where, body in sources:
        for m in re.finditer(r"(?m)^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)", masked(body)):
            if m.group(1) in watched:
                return (f"{where}: `#define {m.group(1)}` names a receiver, field or class this rename "
                        "depends on")
    return None


def field_renames(source, text, strip, include, compile=None, header=None):
    """({class: {private field: canonical field}}, None) for the unit's views of the
    `strip` classes, or (None, why) when a private field has no canonical field of its
    offset and size, several canonical fields share that offset and size (a union) and
    none carries the private name, the canonical name is declared by another class of the
    hierarchy or hidden by a static, method, nested type, typedef, using alias or enumerator
    there (the unqualified name would select that), the two disagree on what the field is, a
    rename is unsafe in the unit (tu_views.rename_problem), or the unit or an include shadows
    the class's name or defines a macro the rename depends on. A pointer-sized field at an
    offset the canonical class fills with a vftable pointer (vptr_offsets) is not one of those:
    it has no canonical field by construction and needs no counterpart. `compile(source, text)` gives
    {class: layout} (text None: the unit as it stands); `header` is the canonical header,
    whose class bodies prove the new names hide nothing (refused when it cannot be read)."""
    import tu_views
    compile = compile or compile_text
    try:
        every = compile(source, None)
    except RuntimeError as exc:
        return None, f"the unit's layout: {exc}"
    views = []
    for name in strip:
        lay = every.get(name)
        if not lay or lay.get("fwd") or not lay.get("fields") or not body_span(text, name):
            continue                                    # no view, or nothing in the unit lays it out
        try:
            view = tu_views.View(source, text, name, lay, every)
        except tu_views.Refused as exc:
            return None, str(exc)
        own = [m.name for m in view.members if m.kind == "data" and not tu_views.is_pad(m, view)]
        if own:
            views.append((view, own))
    if not views:
        return {}, None
    # Use the same compiler include roots for validation and name collection.
    import build
    flags_line = next((line[6:] for line in text.splitlines() if line.startswith("// cl:")), "")
    flags = build._source_flag_tokens(flags_line)
    import stlport_overlay
    flags = stlport_overlay.include_dirs(source, flags)
    include_roots = []
    for i, flag in enumerate(flags):
        if flag in ("/I", "-I") and i + 1 < len(flags):
            include_roots.append(ROOT / flags[i + 1])
        elif flag.startswith(("/I", "-I")) and len(flag) > 2:
            include_roots.append(ROOT / flag[2:])
    # The compiler searches its implicit INCLUDE directories as well as /I.
    toolchain = Path(os.environ.get("VC71_ROOT", build.DEFAULT_VC71_ROOT))
    include_roots.append(toolchain / "Vc7" / "include")
    if re.search(r"(?m)^// platformsdk[ \t]*$", text):
        include_roots.append(toolchain / "Vc7" / "PlatformSDK" / "Include")
    if re.search(r"(?m)^// dxsdk[ \t]*$", text):
        include_roots.append(build.DXSDK_DIR / "Include")
    if "// stlport" in text:
        if re.search(r"(?m)^// stlport46[ \t]*$", text):
            include_roots.extend([stlport_overlay.TREE / "stlport", stlport_overlay.TREE / "base"])
        else:
            stlport = build.stlport_include_dir()
            if stlport:
                include_roots.append(stlport)
        include_roots.extend(root.parent / "include" for root in tuple(include_roots))
    include_cache = {}
    canonical = []
    if header:
        canonical = header_sources(header, include_roots, include_cache)
        if canonical is None:
            return None, f"the canonical header {header} cannot be read; no proof of its names"
    try:
        laid = compile(source, probe_text(text, strip, include))
    except RuntimeError as exc:
        return None, f"the header's layout: {exc}"
    mappings = {}
    for view, own in views:
        name = view.cls
        fields = flat_fields(name, laid)
        if not fields:
            return None, f"{include}: the probe laid out no field of {name}"
        declared = collections.defaultdict(set)         # canonical field -> classes declaring it
        for found in fields.values():
            for field, _, owner in found:
                declared[field].add(owner)
        hides = hiding(name, laid, canonical)
        table = tu_views.field_table(view)
        vptrs = vptr_offsets(name, laid)
        mine = {}
        for old in own:
            offset, size, cvtype = table[old]
            found = fields.get((offset, size), [])
            if not found:
                # A pointer the canonical class gets from the compiler: the view's member goes
                # away with the view and there is no canonical field to rename it to. A body
                # that reads one then fails to compile, which the compile step answers; this
                # check only decides whether the two layouts can be spoken about.
                if size == VPTR_SIZE and offset in vptrs:
                    continue
                return None, (f"{name}::{old} (+0x{offset:X}, {size} bytes) has no canonical field "
                              "of that offset and size")
            same = [f for f in found if f[0] == old]
            if not same and len(found) > 1:
                return None, (f"{name}::{old} (+0x{offset:X}, {size} bytes) could be any of "
                              + ", ".join(f"{o}::{f}" for f, _, o in found) + " (a union); not resolved")
            new, want, owner = (same or found)[0]
            if len(declared[new]) > 1:
                return None, (f"{name}::{old} -> {new}: {new} is declared by "
                              + ", ".join(sorted(declared[new])) + "; the unqualified name is hidden or shadowed")
            if new in hides:
                return None, (f"{name}::{old} -> {new}: {new} is {hides[new][0]} in the hierarchy; "
                              "the unqualified name would select it")
            if not tu_views.cv_compatible(cvtype, want):
                return None, f"{name}::{old} (+0x{offset:X}) is {cvtype}; the canonical {owner}::{new} is {want}"
            if new != old:
                mine[old] = new
        why = tu_views.rename_problem(view, mine)
        if why:
            return None, why
        if mine:
            mappings[name] = mine
    if mappings:
        if header:
            why = include_problem(header, read_source(header), include_roots=include_roots, cache=include_cache)
            if why:
                return None, why
            family = {cls for name in mappings for cls in hierarchy(name, laid)}
            rename_names = {token for mapping in mappings.values() for pair in mapping.items() for token in pair}
            why = conditional_hierarchy(canonical, family, rename_names)
            if why:
                return None, why
        why = include_problem(source, text, include_roots=include_roots, cache=include_cache)
        if why:
            return None, why
        sources = [(source, text)] + include_sources(source, text, include_roots, include_cache) + canonical
        for name in mappings:
            why = name_shadow(sources, name)
            if why:
                return None, why
        why = macro_shadow(sources, mappings, text)
        if why:
            return None, why
    return mappings, None


# -- scoped renaming: a reference is rewritten only when its class is proven
STATEMENT_WORDS = {"return", "delete", "else", "case", "goto", "sizeof", "new", "throw", "typedef",
                   "operator", "using", "namespace", "public", "private", "protected", "virtual",
                   "static", "extern", "inline", "friend", "template", "do", "if", "while", "for",
                   "switch", "catch", "break", "continue", "default", "const_cast", "static_cast",
                   "dynamic_cast", "reinterpret_cast", "this", "true", "false", "asm", "try",
                   "noexcept", "decltype", "alignof", "alignas", "export", "mutable", "explicit",
                   "register", "return"}
TYPE_WORDS = {"void", "int", "float", "double", "char", "short", "long", "unsigned", "signed", "bool",
              "const", "volatile", "struct", "class", "union", "enum", "wchar_t", "__int8", "__int16",
              "__int32", "__int64", "typename", "auto"}


def decl_type_before(code, at):
    """The type `code` spells just before `at` when `at` starts a declarator, else None (a
    use). The spelling is kept: `OtherNS::Object` and `Box<Other>` are not `Object`.
    Qualifiers, pointers and references are dropped."""
    i, parts, has_type = at, [], False
    while i:
        j = i
        while j and code[j - 1] in " \t\r\n":
            j -= 1
        if not j:
            break
        ch = code[j - 1]
        if ch == ">":                                   # a template-id: Box<Other>
            depth, k = 0, j
            while k:
                k -= 1
                if code[k] == ">":
                    depth += 1
                elif code[k] == "<":
                    depth -= 1
                    if not depth:
                        break
            if depth:
                break
            name = re.search(r"([A-Za-z_]\w*)\s*$", code[:k])
            if not name:
                break
            parts.append(code[k:j].strip())
            parts.append(name.group(1))
            i, has_type = name.start(), True
            continue
        word = re.search(r"([A-Za-z_]\w*)$", code[:j])
        if word:
            if word.group(1) in STATEMENT_WORDS:
                break
            parts.append(word.group(1))
            i = word.start()
            has_type = True
            continue
        if j >= 2 and code.startswith("::", j - 2):
            parts.append("::")
            i = j - 2
            continue
        if ch in "*&":
            i = j - 1
            continue
        break
    if not has_type:
        return None
    spelled = ""
    for part in reversed(parts):
        if part == "::":
            spelled += "::"
        elif part.startswith("<"):
            spelled += part
        else:
            spelled += ("" if not spelled or spelled.endswith("::") else " ") + part
    return re.sub(r"^(?:(?:const|volatile|struct|class|enum|union|typename|unsigned|signed|long|short)\s+)+",
                  "", spelled)


def declaration_types(code, ident):
    """{type} the masked code declares `ident` with, in any form: a variable, a parameter, a
    field, a function's return type, a direct initialisation (`Other p(1)`), a template-id.
    Only declarations count; a use adds nothing."""
    types = set()
    for m in re.finditer(r"(?<![\w$])" + re.escape(ident) + r"(?![\w$])", code):
        at = m.start()
        if at and (code[at - 1] == "." or code[max(0, at - 2):at] in ("->", "::")):
            continue
        spelled = decl_type_before(code, at)
        if spelled:
            types.add(spelled)
    return types


def starts_declaration(code, at):
    """Whether the qualified name at `at` heads a definition: what precedes it is nothing, a
    block or statement end, or a type, never an operator or a call."""
    j = at
    while j and code[j - 1] in " \t\r\n":
        j -= 1
    if not j or code[j - 1] in ";}{:":
        return True
    word = re.search(r"([A-Za-z_]\w*)$", code[:j])
    return bool(word) and (word.group(1) in TYPE_WORDS or word.group(1) not in STATEMENT_WORDS)


def member_spans(code, classes):
    """[(start, end, class)]: the out-of-line member function definitions of `classes` in the
    masked unit, from the qualified name through the closing brace (initializer list
    included). A call that happens to spell `Class::name(` is not a definition."""
    spans = []
    for cls in classes:
        for m in re.finditer(r"\b" + re.escape(cls) + r"\s*::\s*~?[A-Za-z_]\w*\s*\(", code):
            if not starts_declaration(code, m.start()):
                continue
            depth, i = 0, m.end() - 1
            while i < len(code):                        # the parameter list
                depth += (code[i] == "(") - (code[i] == ")")
                i += 1
                if not depth:
                    break
            j = i
            while j < len(code) and code[j] not in "{;":
                j += 1
            if j >= len(code) or code[j] != "{":
                continue                                # a declaration or a call
            depth, k = 0, j
            while k < len(code):
                depth += (code[k] == "{") - (code[k] == "}")
                k += 1
                if not depth:
                    break
            spans.append((m.start(), k, cls))
    return spans


NESTED_SCOPE = re.compile(r"(?:\b(?:class|struct|union)\b[^{;]*[^)\s]"
                          r"|\[[^\]]*\]\s*(?:\([^()]*\))?\s*(?:mutable\s*)?)$")


def unsafe_scope(code, start, at):
    """Whether `at`, inside the span beginning at `start`, lies in a nested class, struct,
    union or lambda body: there `this` and a bare name are not the member function's class."""
    depth, i = [], code.find("{", start)
    while 0 <= i < at:
        if code[i] == "{":
            prev = max(code.rfind(ch, 0, i) for ch in ";{}")
            depth.append(bool(NESTED_SCOPE.search(code[prev + 1:i].rstrip())))
        elif code[i] == "}":
            if depth:
                depth.pop()
        i += 1
    return any(depth)


def in_capture_list(code, at):
    """Whether `at` is inside a `[...]` that introduces a lambda (a subscript is not one)."""
    depth, i = 0, at
    while i:
        i -= 1
        if code[i] == "]":
            depth += 1
        elif code[i] == "[":
            if not depth:
                before = code[:i].rstrip()
                if not before:
                    return True
                if before[-1] in ")]":
                    return False
                word = re.search(r"([A-Za-z_]\w*)$", before)
                return word.group(1) in STATEMENT_WORDS if word else before[-1] not in "0123456789"
            depth -= 1
    return False


def object_class(code, end, here):
    """The class of the object expression ending at `end` (just before its `->` or `.`):
    `this` in a member function, an identifier or a call every declaration of which spells
    exactly one type; None for anything else (chains, indexing, casts, several declared
    types, a qualified or template type, which is not the adopting class's own name)."""
    i = end
    while i and code[i - 1] in " \t\r\n":
        i -= 1
    call = bool(i) and code[i - 1] == ")"
    if call:
        depth, j = 0, i
        while j:
            j -= 1
            depth += (code[j] == ")") - (code[j] == "(")
            if not depth:
                break
        i = j
    name = re.search(r"([A-Za-z_]\w*)\s*$", code[:i])
    if not name:
        return None
    if name.group(1) == "this" and not call:
        return here
    if code[:name.start()].rstrip().endswith(("->", ".", "::")):
        return None                                     # a chained or qualified expression
    types = declaration_types(code, name.group(1))
    return next(iter(types)) if len(types) == 1 else None


def declared_class(code, name):
    """Whether the masked code declares `name` a class or struct (a forward declaration
    counts): only then is a member of that name proven not the adopting class's."""
    return bool(re.search(r"\b(?:class|struct)\s+(?:__declspec\([^)]*\)\s*)*" + re.escape(name) + r"\b", code))


def scoped_rename(text, mappings):
    """(text with every reference to a renamed field rewritten, None), or (None, why) when an
    occurrence of an old name is not proven to be a member of a class it is renamed in, or of
    a class unrelated to them. Proven: `this->x` or a bare `x` inside an out-of-line member
    function of the class (where nothing declares x locally), `p->x` / `o.x` / `f()->x` where
    every declaration of p, o or f in the file spells exactly the class, and `Class::x`.
    A nested class or lambda, a capture list, a macro, a splice, a local, or any other
    spelling of the type refuses the unit."""
    olds = {old for m in mappings.values() for old in m}
    if not olds:
        return text, None
    if re.search(r"\\\r?\n|\?\?[=/'()!<>-]", text):
        return None, "line splice or trigraph in unit"
    spliced = spliced_identifiers(text) & olds
    if spliced:
        return None, f"`{sorted(spliced)[0]}` is split by a line splice; not proven a member"
    code = masked(text)
    spans = member_spans(code, list(mappings))
    for cls in mappings:
        if re.search(r"\b[A-Za-z_]\w*\s*::\s*" + re.escape(cls) + r"\s*::", code):
            return None, f"qualified member definition or reference of {cls}"
    # Conservatively refuse every comma-containing statement mentioning a receiver.
    receivers = set(re.findall(r"\b([A-Za-z_]\w*)\s*(?:->|\.)\s*(?:" + "|".join(map(re.escape, olds)) + r")\b", code))
    for receiver in receivers:
        for statement in re.split(r"[;{}]", code):
            if "," in statement and re.search(r"\b" + re.escape(receiver) + r"\b", statement):
                return None, f"{receiver} occurs in a comma declaration or expression"
    derived = re.compile(r"\b(?:class|struct)\s+(\w+)\s*:[^{;]*\b(?:" + "|".join(map(re.escape, mappings)) + r")\b")
    heirs = {m.group(1) for m in derived.finditer(code)}
    pat = re.compile(r"(?<![\w$])(" + "|".join(re.escape(o) for o in sorted(olds, key=len, reverse=True))
                     + r")(?![\w$])")
    out, last = [], 0
    for m in pat.finditer(code):
        old, at = m.group(1), m.start()
        where = f"{old} at line {code.count(chr(10), 0, at) + 1}"
        line = code[code.rfind("\n", 0, at) + 1:at]
        if line.lstrip().startswith("#"):
            return None, f"{where} is in a preprocessor line; not proven a member"
        if in_capture_list(code, at):
            return None, f"{where} is in a lambda capture list; not proven a member"
        inside = next((sp for sp in spans if sp[0] <= at < sp[1]), None)
        here = inside[2] if inside else None
        if inside and unsafe_scope(code, inside[0], at):
            return None, (f"{where} is inside a nested class or lambda in a {here} member function; "
                          "not proven a member")
        before = code[:at].rstrip()
        if before.endswith("->") or (before.endswith(".") and not before.endswith("..")):
            cls = object_class(code, len(before) - (2 if before.endswith("->") else 1), here)
        elif before.endswith("::"):
            q = re.search(r"((?:[A-Za-z_]\w*\s*::\s*)*[A-Za-z_]\w*)\s*$", before[:-2])
            cls = re.sub(r"\s+", "", q.group(1)) if q else None
        elif inside and not declaration_types(code[inside[0]:inside[1]], old):
            cls = here
        else:
            cls = None
        if cls is None:
            return None, (f"{where} is not proven a member of " + "/".join(sorted(mappings))
                          + "; refusing rather than guessing")
        if cls not in mappings:
            if cls in heirs:
                return None, f"{where}: {cls} derives from " + "/".join(sorted(mappings)) + "; not resolved"
            if not declared_class(code, cls):
                return None, (f"{where} is reached through `{cls}`, which the unit does not declare a "
                              "class; not proven a member of another class")
        new = mappings.get(cls, {}).get(old)
        if new:
            out.append(text[last:at])
            out.append(new)
            last = m.end()
    out.append(text[last:])
    return "".join(out), None


def include_spelling(source, header):
    return os.path.relpath(ROOT / header, (ROOT / source).parent).replace("\\", "/")


# ---------------------------------------------------------------- header generation

def split_members(body):
    out, current, depth = [], "", 0
    index = 0
    while index < len(body):
        char = body[index]
        current += char
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                out.append(current.strip())
                current = ""
                while index + 1 < len(body) and body[index + 1] in " \t\r\n;":
                    index += 1
        elif char == ";" and depth == 0:
            out.append(current.strip())
            current = ""
        index += 1
    return [m for m in out + [current.strip()] if m]


def signature(member, name):
    head = member.split("{")[0]
    head = re.sub(r"\s+", " ", re.sub(r"^(public|private|protected)\s*:\s*", "", head)).strip(" ;")
    head = re.sub(r"\b(inline|__forceinline)\s+", "", head)
    head = re.sub(r"\s*([*&,()])\s*", r"\1", head)
    head = re.sub(r"(\w[*&]?)\s+\w+([,)=])", r"\1\2", head)
    head = re.sub(r"([*&])\w+([,)=])", r"\1\2", head)   # `T *name`: step 3 ate the space
    head = re.sub(r"\(void\)", "()", head)     # f(void) and f() are one member (C2535 otherwise)
    return re.sub(r"\)\s*:.*$", ")", head)


# The ZH typedef layer, spelled out so the header does not depend on the
# unit's own typedefs (Bool is `int` in some units: C2371 otherwise).
TYPEDEFS = {"Real": "float", "Bool": "bool", "Int": "int", "UnsignedInt": "unsigned int",
            "Short": "short", "UnsignedShort": "unsigned short", "Byte": "char", "UnsignedByte": "unsigned char",
            "TRUE": "true", "FALSE": "false"}
PRIMITIVE_WORDS = set("void int float double char short long unsigned signed bool const return if else this "
                      "operator inline sqrtf sqrt fabs fabsf static_cast".split())


def view_methods(name, sources, known=()):
    """{signature: text} of the non-special inline methods the views declare.

    A method may name the types in `known` (the member aggregates whose
    canonical headers the generated header includes) and no other class.

    One method spelled several ways keeps its most common spelling; the
    tournament and the per-unit gate decide whether that spelling is
    byte-equivalent for each unit."""
    seen = collections.defaultdict(collections.Counter)
    special = re.compile(r"^\s*(?:__declspec\(\w+\)\s*)*(?:(?:__forceinline|inline)\s+)?~?"
                         + re.escape(name.split("::")[-1]) + r"\s*\(")
    for source in sources:
        text = (ROOT / source).read_text(encoding="latin-1")
        span = body_span(text, name)
        if not span:
            continue
        code = re.sub(r"//[^\n]*|/\*.*?\*/", "", text[span[0]:span[1]], flags=re.S)
        inner = code[code.index("{") + 1:code.rindex("}")]
        for member in split_members(inner):
            member = re.sub(r"^(public|private|protected)\s*:\s*", "", member).strip()
            if "(" not in member or special.match(member) or re.match(r"(typedef|friend|enum)", member):
                continue
            for typedef, spelling in TYPEDEFS.items():
                member = re.sub(r"\b%s\b" % typedef, spelling, member)
            words = set(re.findall(r"[A-Za-z_]\w*", member)) - PRIMITIVE_WORDS - {name} - set(known)
            # A hump-underscore word (Delete_This, Add_Ref, Release_Ref) is an
            # identifier a view names, not a type the header lacks: WWLib method
            # identifiers spell that way and their true types never appear in
            # the declaration. Over-keeping is safe — the per-unit byte
            # tournament rejects any spelling that is not byte-equivalent.
            hump_id = re.compile(r"^[A-Z][A-Za-z0-9]*(?:_[A-Z][A-Za-z0-9]*)+$")
            if any(w[0].isupper() and not hump_id.match(w) for w in words):
                continue                      # needs a type the header does not declare
            seen[signature(member, name)][member] += 1
    # an inline body beats a bare declaration: units that inline the method need it
    return {sig: max(spellings, key=lambda m: ("{" in m, spellings[m])) for sig, spellings in seen.items()}


# ---------------------------------------------------------------- special members
#
# A destructor, constructor or copy assignment that the views declare must be in
# the header. The byte gate cannot see one dropped: a unit that destroys an
# instance compiles the implicit destructor and calls it at the same place, so
# its rows match, but it now emits `??1C@@` as a COMDAT ANY copy. Beside
# retail's out-of-line definition (COMDAT NODUPLICATES) the link stops on
# LNK2005 (P137); beside an inline one (COMDAT ANY) the linker may keep the
# implicit body, which does not do what the views' body does. `??0` and `??4`
# carry the same risk. Views that disagree on a special member hold the class.
#
# Every other member declaration is carried the same way, in every variant: a
# dropped one is not always a compile error either. A dropped `operator<` or
# `operator==` (I6, Rva002A9706Element) lets a comparison fall to a conversion
# or a free operator; a dropped named method lets a call fall to a base's. The
# one definition of a member declaration is declaration_records, which the
# header lane's lost-declaration scan reads too.

ACCESS_LABEL = re.compile(r"^\s*(public|private|protected)\s*:(?!:)\s*")
SPECIAL_QUALIFIERS = re.compile(r"^(?:(?:__declspec\(\w+\)|__forceinline|inline|explicit)\s+)*")
# Roles with an implicit counterpart: dropping one of these is what the byte gate cannot see.
IMPLICIT_ROLES = ("dtor", "default", "copy", "assign")
LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'')
CV_WORDS = ("const", "volatile")


def outside_literals(text, change):
    """`text` with `change` applied to every stretch outside its string and character literals."""
    out, last = [], 0
    for found in LITERAL.finditer(text):
        out += [change(text[last:found.start()]), found.group()]
        last = found.end()
    return "".join(out + [change(text[last:])])


def spell_typedefs(text):
    """`text` with the ZH typedef layer spelled out (TYPEDEFS)."""
    for typedef, spelling in TYPEDEFS.items():
        text = re.sub(r"\b%s\b" % typedef, spelling, text)
    return text


def top_level_spans(shape, start, end, raw=None):
    """(start, end) of each top-level member of `shape[start:end]`, split as split_members
    splits; `shape` has its literals and comments blanked (masked), `raw` is the text it
    masks (for a directive's line continuations). A preprocessor line outside every brace
    is a member of its own, continuation lines included (it has no `;` to end it, so it once
    swallowed the member after it); a declaration it interrupts goes with it."""
    out, begin, depth, index = [], start, 0, start
    while index < end:
        if depth == 0 and (index == start or shape[index - 1] == "\n"):
            first = index
            while first < end and shape[first] in " \t":
                first += 1
            if first < end and shape[first] == "#":
                stop = first
                while True:
                    stop = shape.find("\n", stop)
                    stop = end if stop < 0 or stop > end else stop
                    tail = raw[max(start, stop - 2):stop] if raw is not None else ""
                    if stop < end and tail.rstrip("\r").endswith("\\"):
                        stop += 1                # a continued line: masked() blanked its backslash
                        continue
                    break
                out.append((begin if shape[begin:index].strip() else first, stop))
                begin = index = stop
                continue
        char = shape[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0 and re.match(r"\s*(?:(?:public|private|protected)\s*:\s*)*(?:typedef\s+)?"
                                       r"(?:class|struct|union|enum)\b", shape[begin:index]):
                pass                             # a type's definition runs to its `;` (`struct {...} s;`)
            elif depth == 0:
                out.append((begin, index + 1))
                while index + 1 < end and shape[index + 1] in " \t\r\n;":
                    index += 1
                begin = index + 1
        elif char == ";" and depth == 0:
            out.append((begin, index + 1))
            begin = index + 1
        index += 1
    out.append((begin, end))
    return [(a, b) for a, b in out if shape[a:b].strip()]


def class_members(text, name):
    """[(access, member)] of the top-level members the view of `name` in `text` declares,
    comments blanked and literals kept, each with the access label in force; None when
    `text` has no body. Braces and semicolons inside literals and comments split nothing."""
    span = body_span(text, name)
    if not span:
        return None
    raw = text[span[0]:span[1]]
    code, shape = masked(raw, keep_literals=True), masked(raw)
    if "{" not in shape:
        return None
    access = "public" if span[2] in ("struct", "union") else "private"
    out = []
    for start, end in top_level_spans(shape, shape.index("{") + 1, shape.rindex("}"), raw):
        member = code[start:end].strip()
        label = ACCESS_LABEL.match(member)
        while label:
            access, member = label.group(1), member[label.end():]
            label = ACCESS_LABEL.match(member)
        if member.strip():
            out.append((access, member.strip()))
    return out


def param_list(text):
    """The raw parameters of the first parenthesized list of `text` ([] for `()` and `(void)`)."""
    inner = text[text.index("(") + 1:]
    depth, out, current = 1, [], ""
    for char in inner:
        depth += char == "("
        depth -= char == ")"
        if depth == 0:
            break
        if char == "," and depth == 1:
            out.append(current)
            current = ""
        else:
            current += char
    out.append(current)
    return [] if [p.strip() for p in out] in ([""], ["void"]) else [p.strip() for p in out]


def param_key(param, top=True):
    """One parameter's type as the compiler sees it: qualifiers kept, names dropped, an array
    adjusted to a pointer and top-level `const`/`volatile` ignored (`f(int)` and `f(const int)`
    are one function): `X const &o` -> `const X&`, `int a[4]` -> `int*`, `const int n` -> `int`,
    `void (*fn)(int x)` -> `void(*)(int)`, `void (C::*pm)(int)` -> `void(C::*)(int)`, `int (*p)[4]`
    -> `int(*)[4]` (a pointer to array is no array). A parenthesized declarator it cannot read
    keys as `?` and its text, which holds the member's class (declaration_records: `complex`)."""
    param = re.sub(r"=.*$", "", param, flags=re.S)
    param = re.sub(r"\b(struct|class|enum)\b", "", param).strip()
    if param == "...":
        return "..."
    pointer = pointer_declarator(param)
    if pointer:                                  # its own cv is top-level (ignored); names go, inner ones too
        declarator = " ".join(filter(None, [(pointer["calling"] or "").strip(),
                                            re.sub(r"\s+", "", pointer["scope"] + pointer["star"])]))
        base = param_key(pointer["base"], False)
        rest = pointer["rest"]
        if rest.startswith("["):
            bounds, dims = re.sub(r"\s+", "", pointer["bounds"]), re.sub(r"\s+", "", rest)
            return f"{base}({declarator}{bounds}){dims}"
        close = rest.rindex(")")
        inner = ",".join(param_key(p) for p in param_list(rest[:close + 1]))
        return f"{base}({declarator})({inner}){' '.join(rest[close + 1:].split())}"
    if "(" in param:
        return "?" + " ".join(param.split())
    array = re.match(r"^([^\[]*?)\s*\[[^\]]*\](.*)$", param, flags=re.S)
    if array:                                    # an array parameter is a pointer to its element
        return param_key(array.group(1), False) + "*" + re.sub(r"\s+", "", array.group(2))
    tokens = re.findall(r"[A-Za-z_]\w*(?:\s*::\s*[A-Za-z_]\w*)*(?:\s*<[^()]*?>)?|[*&()\[\],]|\d+", param)
    tokens = [re.sub(r"\s+", "", t) for t in tokens]
    types = [t for t in tokens if re.match(r"[A-Za-z_]", t) and t not in CV_WORDS]
    if len(types) > 1 and re.match(r"[A-Za-z_]", tokens[-1]) and tokens[-1] not in CV_WORDS \
            and tokens[-1] not in ("int", "char", "short", "long", "double", "float"):
        tokens = tokens[:-1]                     # the parameter's name
    if len(tokens) > 1 and tokens[1] in CV_WORDS and tokens[0] not in CV_WORDS:
        tokens[0], tokens[1] = tokens[1], tokens[0]
    if top:                                      # top-level cv: after the last `*`/`&`, or on a plain type
        last = max((i for i, t in enumerate(tokens) if t in ("*", "&")), default=-1)
        tokens = [t for i, t in enumerate(tokens) if not (t in CV_WORDS and i > last)]
    return re.sub(r" ?([*&()\[\],]) ?", r"\1", " ".join(tokens))


def special_role(member, short):
    """The special-member role of a declaration (`dtor`, `default`, `copy`, `ctor`, `assign`,
    `operator=`), `virtual` for a virtual one, or None for any other member. A constructor
    callable with no argument is the default one; one whose first parameter is `X&` and the
    rest defaulted is a copy constructor."""
    head = re.sub(r"\)\s*:.*$", ")", member.split("{")[0], flags=re.S)
    head = SPECIAL_QUALIFIERS.sub("", head.strip())
    if re.match(r"virtual\b", head):
        return "virtual" if re.search(r"(~\s*%s|\boperator\s*=)\s*\(" % re.escape(short), head) else None
    if re.match(r"~\s*%s\s*\(" % re.escape(short), head):
        return "dtor"
    if re.match(r"%s\s*\(" % re.escape(short), head):
        params = param_list(head)
        if all("=" in p for p in params):
            return "default"
        first = param_types(f"({params[0]})")
        return "copy" if first == [short + "&"] and all("=" in p for p in params[1:]) else "ctor"
    if re.search(r"\boperator\s*=\s*\(", head):
        copy = param_types(head[head.index("operator"):]) in ([short + "&"], [short])   # X& or by value
        return "assign" if copy else "operator="
    return None


TEMPLATE_HEAD = re.compile(r"^template\s*<")
CALLING = r"(?:__(?:cdecl|stdcall|fastcall|thiscall)\s*)?"
# `(*name)(...)`, `(C::*name)(...)` or `(*name)[n]`: a pointer data member, not a function
POINTER_DATA = re.compile(r"^[^(]*\(\s*" + CALLING + r"(?:[A-Za-z_]\w*\s*::\s*)*[*&]\s*(?:(?:const|volatile)\s+)*"
                          r"[A-Za-z_]\w*\s*(?:\[[^\]]*\]\s*)*\)\s*[(\[]")
# a declarator that starts with `(*`: a function returning a pointer to function or array
PAREN_DECLARATOR = re.compile(r"^[^(]*\(\s*" + CALLING + r"(?:[A-Za-z_]\w*\s*::\s*)*[*&]")
# The parts of a parenthesized pointer declarator, `base (calling scope::* cv name[bounds]) rest`:
# `void (*volatile cb)(int)`, `void (C::*pm)()`, `int (*p)[4]`; `rest` is the parameter list or bounds.
POINTER_DECLARATOR = re.compile(
    r"^(?P<base>[^(]*?)\(\s*(?P<calling>__(?:cdecl|stdcall|fastcall|thiscall)\s*)?"
    r"(?P<scope>(?:[A-Za-z_]\w*\s*::\s*)*)(?P<star>[*&])\s*(?P<cv>(?:(?:const|volatile)\b\s*)*)"
    r"(?P<name>[A-Za-z_]\w*)?\s*(?P<bounds>(?:\[[^\]]*\]\s*)*)\)\s*(?P<rest>[(\[].*?)\s*;?\s*$", re.S)


def pointer_declarator(text):
    """POINTER_DECLARATOR's match for `text` when its `rest` is one parameter list (and cv) or
    array bounds, else None (a pointer to a function returning a pointer is not read)."""
    found = POINTER_DECLARATOR.match(text.strip())
    if not found:
        return None
    rest = found["rest"]
    if rest.startswith("["):
        return found if re.fullmatch(r"(?:\[[^\]]*\]\s*)+", rest) else None
    depth = 0
    for close, char in enumerate(rest):
        depth += {"(": 1, ")": -1}.get(char, 0)
        if depth == 0:
            break
    return found if re.fullmatch(r"(?:\s*(?:const|volatile)\b)*\s*", rest[close + 1:]) else None
OPERATOR_SYMBOL = re.compile(r"\boperator\b\s*(?:\(\s*\)|\[\s*\]|[^\w\s(]+)")
# Roles the generator never carries: a view declaring one holds the class.
UNCARRIED = {"nested": "a nested declaration", "directive": "a preprocessor line",
             "list": "a declaration of several members", "complex": "a declarator the generator does not parse",
             "macro": "a macro's use"}
BUILTIN_WORDS = {"void", "bool", "char", "short", "int", "long", "float", "double", "wchar_t", "__int64",
                 "unsigned", "signed"}
# what may stand before a built-in type word in a declaration (anything else is a macro's use)
SPECIFIER_WORDS = BUILTIN_WORDS | {"const", "volatile", "mutable", "static", "inline", "__forceinline", "virtual",
                                   "explicit", "friend", "typedef", "extern", "register", "struct", "class",
                                   "union", "enum", "typename"}


def template_head(text):
    """(`template <...>` prefix, the rest) of a declaration; ("", text) without one."""
    if not TEMPLATE_HEAD.match(text):
        return "", text
    depth, index = 0, text.index("<")
    for index in range(index, len(text)):
        depth += {"<": 1, ">": -1}.get(text[index], 0)
        if depth == 0:
            break
    return text[:index + 1], text[index + 1:].strip()


def declaration_head(member, literals=False):
    """A member's declaration without its body or constructor initializers; its literals' contents
    blanked to `""` unless `literals` (a default `'a'` and one `'b'` must not compare equal). The
    body and initializers are found with literals masked, so a `{` or `:` in one cuts nothing."""
    shape = masked(member)
    cut = shape.find("{")
    member, shape = (member[:cut], shape[:cut]) if cut >= 0 else (member, shape)
    init = re.search(r"\)\s*:(?!:)", shape)
    if init:
        member = member[:init.start() + 1]
    return (member if literals else LITERAL.sub('""', member)).strip()


def top_level(text):
    """`text`, the same length, with literals, an operator's own symbol (`<`, `()`, `[]`) and
    everything inside (), [] and {} (and a template's <> at the top) blanked, the brackets
    kept: what is left is the declaration's top level."""
    code = OPERATOR_SYMBOL.sub(lambda m: "operator" + " " * (len(m.group()) - 8), masked(text))
    pairs = {"(": ")", "[": "]", "{": "}", "<": ">"}
    out, stack = [], []
    for char in code:
        while stack and stack[-1] == "<" and char in ")]}":
            stack.pop()                          # a stray `<` (a comparison) closes with its brackets
        if stack and char == pairs[stack[-1]]:
            stack.pop()
            out.append(" " if stack else char)
        elif char in "([{" or (char == "<" and all(s == "<" for s in stack)):
            out.append(" " if stack else char)
            stack.append(char)
        else:
            out.append(" " if stack else char)
    return "".join(out)


def call_span(rest):
    """(name start, `(`, `)`) of a function declarator's name and parameter list in `rest`
    (no template prefix), by the top level; None without one."""
    top = re.sub(r"__declspec\s*\(\s*\)", lambda m: " " * len(m.group()), top_level(rest))
    paren = top.find("(")
    close = top.find(")", paren + 1) if paren >= 0 else -1
    if close < 0:
        return None
    before = top[:paren]
    operator = list(re.finditer(r"\boperator\b", before))
    if operator:
        start = operator[-1].start()
    else:
        found = re.search(r"~?\s*[A-Za-z_]\w*\s*$", before)
        if not found:
            return None
        start = found.start()
    return start, paren, close


def template_names(prefix):
    """(canonical prefix, [parameter names]) of a `template <...>` prefix: `template<class
    T, int N>` -> (`template<class,int>`, [T, N]), so renamed parameters are one template."""
    if not prefix:
        return "", []
    inner = prefix[prefix.index("<") + 1:prefix.rindex(">")]
    kinds, names = [], []
    for part in param_list("(" + inner + ")"):
        part = re.sub(r"=.*$", "", part, flags=re.S).strip()
        found = re.search(r"([A-Za-z_]\w*)\s*$", part)
        if found and len(part.split()) > 1:
            names.append(found.group(1))
            part = part[:found.start()]
        kinds.append(re.sub(r"\btypename\b", "class", " ".join(part.split())))
    return f"template<{','.join(kinds)}>", names


def type_names(specifiers):
    """The type names among a declaration's specifiers: identifiers (scoped ones as one) that are
    no keyword, built-in type or compiler keyword (`__declspec`, `__forceinline`, `__cdecl`)."""
    names = []
    for token in re.findall(r"[A-Za-z_]\w*(?:\s*::\s*[A-Za-z_]\w*)*", specifiers):
        token = re.sub(r"\s+", "", token)
        if not token.startswith("__") and token not in SPECIFIER_WORDS:
            names.append(token)
    return names


def member_role(member, short):
    """What one class member declares: a special role (special_role), `virtual` for a virtual
    function, `method` for any other member function (named, operator, conversion operator,
    `operator()`, `operator[]`, template, static), `static` for a static data member (`static`
    anywhere among its specifiers), `friend class` for a befriended class, `friend` for a
    befriended function, `nested` for a nested type, typedef, enum, using-declaration or other
    friend, `directive` for a member a preprocessor line runs into, `list` for a declaration of
    several functions or static members (`void f(), g();`), `complex` for a function declarator
    the generator does not parse (one returning a pointer to function or array), or None for a
    non-static data member, pointer data member or anonymous union or struct (layout, which the
    contract decides). Parentheses inside an array bound or an initializer make no function."""
    if re.search(r"^[ \t]*#", member, flags=re.M):
        return "directive"
    head = SPECIAL_QUALIFIERS.sub("", declaration_head(member))
    prefix, rest = template_head(head)
    if re.match(r"(?:class|struct|union)\s*$", rest) or re.match(r"(?:struct|union)\s*$", head):
        return None                              # an anonymous union or struct: layout
    if re.match(r"friend\s+(?:class|struct|union)\s+[A-Za-z_][\w:]*\s*;?$", rest):
        return "friend class"
    if re.match(r"friend\b", rest):
        return "friend" if call_span(rest[6:].strip()) and not POINTER_DATA.match(rest[6:].strip()) else "nested"
    if re.match(r"(?:typedef|using)\b", rest):
        return "nested"
    if re.match(r"(?:class|struct|union|enum)\b", rest) and ("{" in LITERAL.sub("", member)
                                                             or re.match(r"\w+\s+\w+\s*;?$", rest)):
        return "nested"
    if prefix and not re.search(r"\(", rest):
        return "nested"                          # a member class template's declaration
    rest = re.sub(r"^(?:class|struct|union|enum)\s+", "", rest)
    top = top_level(rest)                        # an operator's own `=` is blanked: any `=` left starts
    equals = top.find("=")                       # an initializer or `= 0`
    declarator = top[:equals] if equals >= 0 else top
    is_static = bool(re.search(r"\bstatic\b", declarator))
    has_call = "(" in declarator
    if re.fullmatch(r"\s*[A-Za-z_]\w*\s*;?\s*", rest):
        return "macro"                           # a lone name: an object-like macro's use
    words = re.findall(r"[A-Za-z_]\w*", declarator)
    builtin = [i for i, w in enumerate(words) if w in BUILTIN_WORDS]
    if not has_call and builtin and builtin[0] > 0 and words[builtin[0] - 1] not in SPECIFIER_WORDS:
        return "macro"                           # `PADDING int m_a`: a macro's use runs into a field
    span = call_span(rest) if has_call and not POINTER_DATA.match(rest) else None
    if span and "," in top:
        return "list"                            # `void f(), g();`: several declarators, no macro
    if span:
        tail = top_level(rest)[span[2] + 1:].split("=")[0]   # call_span's positions: the same length
        if set(re.findall(r"[A-Za-z_]\w*", tail)) - {"const", "volatile", "throw"}:
            return "macro"                       # `GLUE(X) int m_a`: a macro's use runs into a member
    # Two type names before the declarator (`DECLARE_MEMBERS C *m`, `GLUE Foo f()`): a declaration
    # names one type, so the other is a macro's use running into it.
    if span:
        specifiers = top[:span[0]]
    else:
        first = declarator.split(",")[0]
        start = DECLARATOR_START.search(first) or FIELD_NAME.search(first)
        specifiers = first[:start.start()] if start else first
    if len(type_names(specifiers)) >= 2:
        return "macro"
    if has_call and POINTER_DATA.match(rest):
        has_call = False                         # a pointer to function or array: data
    elif has_call and PAREN_DECLARATOR.match(rest):
        return "complex"
    if (has_call or is_static) and "," in top:  # a top-level comma, before or after an initializer
        return "list"
    role = special_role(member, short)
    if role is not None:
        return role
    if has_call:
        return "virtual" if re.search(r"\bvirtual\b", declarator.split("(")[0]) else "method"
    return "static" if is_static else None


def method_key(member, name):
    """A member function's key across spellings: its template parameter kinds (parameters
    renamed T0, T1 ...), its name (`operator<`, `operator()`, `operator const char*` included),
    its parameters' types (param_key) and its cv-qualifiers; parameter names, defaults,
    `static`, `inline` and the return type are no part of it (two overloads cannot differ only
    there)."""
    head = SPECIAL_QUALIFIERS.sub("", declaration_head(member))
    prefix, rest = template_head(head)
    prefix, names = template_names(prefix)
    span = call_span(rest)
    if not span:
        return signature(member, name)
    start, paren, close = span
    spelled = " ".join(rest[start:paren].split())
    if spelled.startswith("operator"):
        token = spelled[8:].strip().replace(" *", "*").replace(" &", "&")
        if re.match(r"(?:new|delete)\b", token):
            what = "operator " + token.replace(" ", "")           # `operator new[]`
        elif re.match(r"[A-Za-z_]", token):
            what = "operator " + token                            # a conversion: `operator const char*`
        else:
            what = "operator" + token.replace(" ", "")            # `operator<`, `operator()`, `operator[]`
    else:
        what = spelled.replace(" ", "")
    params = ",".join(param_key(p) for p in param_list(rest[paren:close + 1]))
    qualifiers = " ".join(re.findall(r"\b(?:const|volatile)\b", rest[close + 1:]))
    body = f"{what}({params}){qualifiers}"
    if names:                                    # one pass: a parameter named T1 cannot be renamed twice
        rename = {old: f"T{index}" for index, old in enumerate(names)}
        body = re.sub(r"\b(%s)\b" % "|".join(map(re.escape, names)), lambda m: rename[m.group(1)], body)
    return prefix + body


def declaration_identity(text, key):
    """What two spellings of one member (one key) must also share: everything before its
    name (return type, `static`, `explicit`: `int f()` and `bool f()` mangle apart), its
    default arguments (a call that omits one takes it) and everything after its parameter list
    or, for a static data member, after its name (`= 0`, `throw()`, array bounds, initializer);
    without `inline`, `__forceinline`, `__declspec(...)`, parameter names or whitespace. A literal
    counts by its content (`'a'` and `'b'` differ), standing in as a digest so its commas and
    parentheses split nothing."""
    head = declaration_head(text, literals=True)
    head = LITERAL.sub(lambda m: '"' + hashlib.sha256(m.group().encode()).hexdigest()[:16] + '"', head)
    head = re.sub(r"^(?:\s*(?:__declspec\(\w+\)|__forceinline|inline)\s+)*", "", head)
    _, rest = template_head(re.sub(r"^\s*friend\s+", "", head))     # `explicit` stays: it is identity
    tidy = lambda s: re.sub(r"\s*([*&,()\[\]=])\s*", r"\1", " ".join(s.split())).strip()  # noqa: E731
    if key.startswith("static "):
        declared = re.sub(r"\bstatic\b", " ", rest)
        equals = top_level(declared).find("=")
        initializer = declared[equals + 1:] if equals >= 0 else ""
        declared = declared[:equals] if equals >= 0 else declared
        pointer = pointer_declarator(declared)
        if pointer:                              # `static void (*const cb)(int x)`: its type, its own cv
            return "|".join(["static", param_key(declared, False), " ".join(pointer["cv"].split()),
                             tidy(initializer).rstrip(";")])
        found = list(re.finditer(r"\b%s\b" % re.escape(key[7:]), rest))
        if not found:
            return tidy(rest)
        before, after, defaults = rest[:found[-1].start()], rest[found[-1].end():], []
    elif key.startswith("friend ") and "(" not in key:
        return tidy(rest)
    else:
        span = call_span(rest)
        if not span:
            return tidy(rest)
        start, paren, close = span
        before, after = rest[:start], rest[close + 1:]
        defaults = [p.split("=", 1)[1] if "=" in p else "" for p in param_list(rest[paren:close + 1])]
    before = re.sub(r"__declspec\(\w+\)|\b(?:inline|__forceinline|friend)\b", " ", before)
    return "|".join([tidy(before), ",".join(tidy(d) for d in defaults), tidy(after).rstrip(";")])


def static_key(member):
    """A static data member's key: `static ` and its name (the last name before its array
    bounds and initializer)."""
    head = declaration_head(member)
    top = top_level(head)
    equals = top.find("=")
    head = head[:equals] if equals >= 0 else head
    pointer = pointer_declarator(re.sub(r"\bstatic\b", " ", head))
    if pointer and pointer["name"]:              # `static void (*cb)(int x)`: its name is in the parentheses
        return "static " + pointer["name"]
    found = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*;?\s*$", head, flags=re.S)
    return "static " + (found.group(1) if found else re.sub(r"\s+", " ", member))


def declaration_records(text, name):
    """[{access, role, key, inline, pure, text}] of every member the view of `name` in `text`
    declares except its non-static data members (layout), or None when `text` has no body.

    The one definition of a member declaration: header generation (special_declarations)
    and the header lane's lost-declaration scan read it alike. `key` names the member across
    spellings (member_key), `inline` is whether it has a body, `pure` whether it ends `= 0`."""
    short = name.split("::")[-1]
    members = class_members(text, name)
    if members is None:
        return None
    out = []
    for access, member in members:
        role = member_role(member, short)
        if role is None:
            continue
        spelled_member = outside_literals(member, spell_typedefs)
        head = re.sub(r"\s+", " ", declaration_head(spelled_member))
        if role == "static":
            key = static_key(spelled_member)
        elif role == "friend class":
            key = head.rstrip(" ;")                  # `friend struct X`
        elif role in UNCARRIED:                  # by its whole text: a nested type's body is part of it
            key = f"{role} {' '.join(masked(spelled_member, keep_literals=True).split())}".rstrip(" ;")
        elif role == "friend":
            key = "friend " + method_key(re.sub(r"^\s*friend\s+", "", spelled_member), name)
        else:
            key = member_key(spelled_member, name)
        if "(?" in key or ",?" in key:           # a parameter declarator param_key cannot read
            role, key = "complex", f"complex {' '.join(masked(spelled_member, keep_literals=True).split())}".rstrip(" ;")
        out.append({"access": access, "role": role, "key": key, "inline": "{" in LITERAL.sub("", member),
                    "pure": bool(re.search(r"=\s*0\s*;?\s*$", declaration_head(member))),
                    "text": spelled_member})
    return out


# where a data member's first declarator starts: a `(` (a pointer to function or array) or a
# `*`/`&` (with a member pointer's `C::` before it)
DECLARATOR_START = re.compile(r"\(|(?:[A-Za-z_]\w*\s*::\s*)*[*&]")
FIELD_NAME = re.compile(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?::\s*[^:;,]+)?\s*;?\s*$")


def field_declarator(specifiers, declarator):
    """(name, qualifiers, shape) of one data member declarator under its shared `specifiers`;
    name None when it cannot be read. `qualifiers`: `mutable`, `const@k`/`volatile@k` (k the
    `*`/`&` before it: `char *const p` -> const@1), `const@ret`/`volatile@ret` for a function
    pointer's return type. `shape`: the declarator's pointers and bounds, names gone."""
    words = re.findall(r"[A-Za-z_]\w*", masked(specifiers))
    qualifiers = {"mutable"} if "mutable" in words else set()
    if declarator.lstrip().startswith("("):
        pointer = pointer_declarator(specifiers + declarator)
        if not pointer or not pointer["name"]:   # every qualifier it carries, specifiers' too, unplaced
            found = re.findall(r"\b(?:const|volatile)\b", masked(specifiers + declarator))
            return None, qualifiers | {f"{w}@?" for w in found}, ""
        function = pointer["rest"].startswith("(")
        qualifiers |= {f"{w}@{'ret' if function else 0}" for w in words if w in CV_WORDS}
        qualifiers |= {f"{w}@1" for w in pointer["cv"].split()}
        shape = param_key(specifiers + declarator, False)
        return pointer["name"], qualifiers, shape
    qualifiers |= {f"{w}@0" for w in words if w in CV_WORDS}
    stars = 0
    for token in re.findall(r"[A-Za-z_]\w*|::\s*\*|[*&]", top_level(declarator)):
        if token in ("*", "&") or token.endswith("*"):
            stars += 1
        elif token in CV_WORDS:
            qualifiers.add(f"{token}@{stars}")
    found = FIELD_NAME.search(top_level(declarator))
    if not found:
        return None, qualifiers, ""
    shape = re.sub(r"\s+", "", declarator[:found.start(1)]) + re.sub(r"\s+", "", declarator[found.end(1):]).rstrip(";")
    return found.group(1), qualifiers, re.sub(r"\b(?:const|volatile)\b", "", shape)


def data_member_fields(member, short):
    """[{name, qualifiers, shape, text}] of one data member: each declarator of a list (`float x,
    y, z;`) with the shared specifiers, an anonymous union's or struct's fields one by one, a
    member of an unnamed struct type (`struct { int a; } s;`) by its own name."""
    shape_text = masked(member)
    if "{" in shape_text:                        # an anonymous union or struct, or an unnamed type's member
        open_ = shape_text.index("{")
        close = len(shape_text) - 1 - shape_text[::-1].index("}")
        after = member[close + 1:].strip().rstrip(";").strip()
        if after:
            out = []
            for piece in split_top_commas(after):
                name, qualifiers, shape = field_declarator(member[:open_] + " ", piece)
                out.append({"name": name, "qualifiers": qualifiers, "shape": shape, "text": member})
            return out
        inner = member[open_ + 1:close]
        out = []
        for start, end in top_level_spans(masked(inner), 0, len(inner), inner):
            part = ACCESS_LABEL.sub("", inner[start:end].strip()).strip()
            if part and member_role(part, short) is None:
                out += data_member_fields(part, short)
        return out
    head = declaration_head(member).strip()
    pieces = split_top_commas(head)
    pointer = pointer_declarator(pieces[0])
    found = DECLARATOR_START.search(top_level(pieces[0]))
    if pointer and pointer["name"]:              # `const char *(*get)(int)`: the declarator is the `(`
        cut = len(pointer["base"])
    elif found:
        cut = found.start()
    else:
        name = FIELD_NAME.search(top_level(pieces[0]))
        cut = name.start() if name else len(pieces[0])
    specifiers = pieces[0][:cut]
    out = []
    for declarator in [pieces[0][cut:]] + pieces[1:]:
        name, qualifiers, shape = field_declarator(specifiers, declarator)
        out.append({"name": name, "qualifiers": qualifiers, "shape": shape, "text": member})
    return out


def split_top_commas(text):
    """`text` split at its top-level commas (none inside (), [], {}, <>, or a literal)."""
    top, out, last = top_level(text), [], 0
    for index, char in enumerate(top):
        if char == ",":
            out.append(text[last:index])
            last = index + 1
    return out + [text[last:]]


def field_records(text, name):
    """[{name, qualifiers, shape, text}] of the non-static data members the view of `name` in
    `text` declares, one per declarator (data_member_fields), or None when `text` has no body.
    `qualifiers` is field_declarator's; a parameter's qualifiers in a pointer to function are
    no field's. `name` is None only where a declarator cannot be read (its qualifiers, `@?`, are
    still reported, and field_qualifiers holds the class on any)."""
    short = name.split("::")[-1]
    members = class_members(text, name)
    if members is None:
        return None
    out = []
    for _, member in members:
        if member_role(member, short) is None:
            out += data_member_fields(member, short)
    return out


def qualified_spelling(field, qualifiers):
    """The contract field's declaration with `qualifiers` (field_records' form) applied."""
    text = spelled(field["type"], field["name"])
    lead = (["mutable"] if "mutable" in qualifiers else []) + [w for w in CV_WORDS if f"{w}@0" in qualifiers]
    parts = text.split("*")
    for k in range(1, len(parts)):
        cv = [w for w in CV_WORDS if f"{w}@{k}" in qualifiers]
        if cv:
            parts[k] = " " + " ".join(cv) + " " + parts[k].lstrip()
    return " ".join(lead + ["*".join(parts)])


def field_qualifiers(contract, views):
    """({contract field name: qualifiers}, [problem]) from the views' fields ({source:
    field_records}). A field's qualifiers are carried when every view that names it agrees;
    views that disagree, a qualified field no contract field is named after, or qualifiers
    beyond the field's pointer depth hold the class: the contract's types carry none, so a
    dropped `volatile` (CountBase's m_count) or `const` would change the class unseen."""
    fields = {f["name"]: f for f in contract.get("fields", ()) if f.get("kind") != "VPTR"}
    seen, problems = collections.defaultdict(dict), []
    for source, records in sorted(views.items()):
        for record in records:
            what = " ".join(record["text"].split())[:80]
            if record["name"] is None:
                if record["qualifiers"]:
                    problems.append(f"field {what}: qualified ({', '.join(sorted(record['qualifiers']))}) in "
                                    f"{source}, in a declarator the generator cannot read")
            elif record["name"] in fields:
                seen[record["name"]][source] = frozenset(record["qualifiers"])
            elif record["qualifiers"]:
                problems.append(f"field {what}: qualified ({', '.join(sorted(record['qualifiers']))}) in {source}, "
                                f"and no contract field is named after it")
    out = {}
    for field_name, by_source in sorted(seen.items()):
        if len(set(by_source.values())) > 1:
            shown = "; ".join(f"{s}: {', '.join(sorted(q)) or 'none'}" for s, q in sorted(by_source.items()))
            problems.append(f"field {field_name}: qualifiers differ ({shown})")
            continue
        qualifiers = next(iter(by_source.values()))
        stars = fields[field_name]["type"].count("*")
        depths = [q.split("@")[1] for q in qualifiers if q != "mutable"]
        # a function pointer's return type (@ret) has no spelling in the contract's type
        if any(not depth.isdigit() or int(depth) > stars for depth in depths):
            problems.append(f"field {field_name}: qualified beyond its contract type {fields[field_name]['type']!r}")
            continue
        if qualifiers:
            out[field_name] = qualifiers
    return out, problems


def member_key(member, name):
    """What one member is known by across its spellings: `~` for the destructor, a
    constructor or `operator=` by its parameter types with their qualifiers (`const X &o`
    and `X const&` are one, `X&` another), any other member function by method_key."""
    short = name.split("::")[-1]
    head = SPECIAL_QUALIFIERS.sub("", re.sub(r"^(?:(?:__forceinline|inline)\s+)?virtual\s+", "",
                                             SPECIAL_QUALIFIERS.sub("", declaration_head(member))))
    if re.match(r"~\s*[A-Za-z_]\w*\s*\(", head):
        return "~"
    if re.match(r"%s\s*\(" % re.escape(short), head):
        return f"{short}({','.join(param_key(p) for p in param_list(head))})"
    assign = re.search(r"\boperator\s*=\s*\(", head)
    if assign:
        return f"operator=({','.join(param_key(p) for p in param_list(head[assign.start():]))})"
    return method_key(member, name)


def _matched_index():
    """{`?member@Scope@@` prefix: [name]} of the matched ledger rows, read once per ledger state."""
    try:
        stat = LEDGER.stat()
        state = (stat.st_mtime_ns, stat.st_size)
    except OSError:
        return {}
    if _matched_index.cache[0] != state:
        index = collections.defaultdict(list)
        for row in class_contract.ledger_rows():
            if "@@" in row["name"]:
                index[row["name"][:row["name"].index("@@") + 2]].append(row["name"])
        _matched_index.cache = (state, index)
    return _matched_index.cache[1]


_matched_index.cache = (None, {})


def ledger_defines(name, role, index=None):
    """Whether a matched ledger row defines `name`'s special member `role`.

    MSVC spells the class in a copy constructor's or assignment's parameter by
    back-reference to the names of its own scope (`ABV0@@` for `X`, `ABV01@@` for
    `A::X`); a copy assignment may take it by value (`V0@@`)."""
    scopes = name.split("::")
    prefix = {"dtor": "??1", "default": "??0", "copy": "??0", "assign": "??4"}[role]
    names = (_matched_index() if index is None else index).get(f"{prefix}{'@'.join(reversed(scopes))}@@", ())
    if role == "default":
        return any(n.endswith("@XZ") for n in names)
    if role in ("copy", "assign"):
        refs = "".join(str(i) for i in range(len(scopes)))
        by = "A[AB]" if role == "copy" else "(?:A[AB])?"
        return any(re.search(r"@%s[UV]%s@@Z$" % (by, refs), n) for n in names)
    return bool(names)


def pure_contradicted(name, member, args, index=None):
    """Whether a matched row defines the virtual `name::member` a view spells pure.

    Only a row whose identity is plain counts: a slot with no parameters, and the one
    row of that name, virtual (`U`, `M`, `E` after the scope) and taking none (`XZ`).
    With parameters an unrowed pure overload could share the name and arity, so no
    contradiction is reported. A pure destructor is never contradicted: C++ requires
    its definition."""
    if args:
        return False
    scope = "@".join(reversed(name.split("::")))
    prefix = f"?{member}@{scope}@@"
    rows = (_matched_index() if index is None else index).get(prefix, ())
    if len(rows) != 1 or rows[0][len(prefix):len(prefix) + 1] not in ("U", "M", "E"):
        return False
    return rows[0].endswith("XZ")


def special_declarations(name, sources, read=None, known=(), slotted=(), index=None):
    """([{role, access, text, sig}] member declarations to carry, [problem]).

    Every member declaration_records reports is carried, in every variant, with the
    views' access: one declared without a body in its most common spelling, one with an
    inline body only when every view that declares it spells the same body. That is the
    special members (destructor, constructors, `operator=`) and every other member
    function (operators, conversion operators, `operator()`, `operator[]`, templates,
    statics) and static data member. A virtual one belongs to the slot declarations;
    `slotted` names the members those already emit (`~` for the destructor).

    The class is held (a problem) when the views disagree on a member: one declares it
    out of line and another inline, virtual or with other access, or inline bodies
    differ; when one names a type or default argument the header does not declare; when
    a view declares a nested type, typedef, enum, using-declaration or friend (the
    generator carries none); or, for a member with an implicit counterpart (destructor,
    default and copy constructor, copy assignment), when another view's body omits it
    and no matched ledger row defines it. No member is ever left out: another overload,
    a base's member or an implicit one could take its calls without a unit failing to
    compile."""
    short = name.split("::")[-1]
    read = read or (lambda s: (ROOT / s).read_text(encoding="latin-1"))
    hump_id = re.compile(r"^[A-Z][A-Za-z0-9]*(?:_[A-Z][A-Za-z0-9]*)+$")
    views = {}
    for source in sources:
        try:
            records = declaration_records(read(source), name)
        except OSError:
            continue
        if records is None:
            continue
        found = collections.defaultdict(list)
        for record in records:
            norm = outside_literals(record["text"], lambda part: re.sub(r"\s+", " ", part)).strip()
            found[record["key"]].append((record["role"], record["access"], record["inline"], norm, record["text"]))
        views[source] = found
    out, problems = [], []
    keys = sorted({k for found in views.values() for k, decls in found.items()
                   if any(role != "virtual" for role, _, _, _, _ in decls)})
    for key in keys:
        if key in slotted:
            continue                  # the slot declarations emit it as a virtual
        decls = [(source, d) for source, found in views.items() for d in found.get(key, ())]
        role = next(r for _, (r, _, _, _, _) in decls if r != "virtual")
        own = [(s, d) for s, d in decls if d[0] != "virtual"]
        outline = [(s, d) for s, d in own if not d[2]]
        inline = [(s, d) for s, d in own if d[2]]
        what = (outline or inline)[0][1][3].split("{")[0].rstrip(" ;")
        label = "special" if role in IMPLICIT_ROLES + ("ctor", "operator=") else "member"
        virtual = sorted({s for s, d in decls if d[0] == "virtual"})
        # a friend declaration's access label means nothing: it is declared public
        accesses = collections.Counter("public" if role.startswith("friend") else d[1] for _, d in own)
        omitted = sorted(s for s, found in views.items() if key not in found)
        if role in UNCARRIED:
            problems.append(f"member {what}: {UNCARRIED[role]} in {own[0][0]}, which the generator does not carry")
            continue
        if outline and inline:
            problems.append(f"{label} {what}: out of line in {outline[0][0]}, inline in {inline[0][0]}")
            continue
        if virtual:
            problems.append(f"{label} {what}: virtual in {virtual[0]} only, not in {own[0][0]}")
            continue
        if len(accesses) > 1:
            problems.append(f"{label} {what}: access disagrees ({', '.join(sorted(accesses))})")
            continue
        identity = declaration_identity(outline[0][1][3], key) if outline else None
        differ = [s for s, d in outline if declaration_identity(d[3], key) != identity]
        if differ:
            problems.append(f"{label} {what}: declarations differ ({outline[0][0]}, {differ[0]})")
            continue
        if inline and len({d[3] for _, d in inline}) > 1:
            problems.append(f"{label} {what}: inline bodies differ ({inline[0][0]}, "
                            f"{next(s for s, d in inline if d[3] != inline[0][1][3])})")
            continue
        if role in IMPLICIT_ROLES and omitted and not ledger_defines(name, role, index=index):
            problems.append(f"special {what}: declared in {own[0][0]}, omitted by {omitted[0]} "
                            f"and no matched row defines it")
            continue
        if outline:
            text = collections.Counter(d[3] for _, d in outline).most_common(1)[0][0]
        else:
            text = inline[0][1][4].strip()
        bare = LITERAL.sub(" ", text)
        prefix, _ = template_head(SPECIAL_QUALIFIERS.sub("", declaration_head(text)))
        # its own name and template parameters name no type the header lacks; an operator's
        # name is only `operator` (a conversion operator's type must be declared)
        name_part = re.sub(r"^(?:friend\s+)?(?:template<[^>]*>)?", "", key.split("(")[0])
        own_names = ({"operator"} if name_part.startswith("operator") else
                     set(re.findall(r"[A-Za-z_]\w*", name_part))) | set(
            re.findall(r"\b(?:class|typename)\s+([A-Za-z_]\w*)", prefix))
        words = set(re.findall(r"[A-Za-z_]\w*", bare)) - PRIMITIVE_WORDS - {name, short} - set(known) - own_names
        # an inline body may call a hump-underscore method (Release_Ref), as view_methods allows
        if any(w[0].isupper() and not (inline and hump_id.match(w)) for w in words) or \
                re.search(r"=\s*(?!(?:true|false)\b)[A-Za-z_]", bare.split("{")[0].split("(", 1)[-1]):
            problems.append(f"{label} {what}: names a type or default argument the header does not declare")
            continue
        out.append({"role": role, "access": next(iter(accesses)), "sig": key,
                    "text": text if text.endswith((";", "}")) else text + ";"})
    return out, problems


def special_members(name, contract, sources, known=None):
    """special_declarations for a contract: the members its slot declarations emit are theirs.
    `known` defaults to what the header includes for every variant: its member aggregates'
    registered headers (the tournament's `nested`), so the gate and the tournament agree.
    The fields' agreed qualifiers (field_qualifiers) ride along as `qualifier` entries, which
    generate applies to the contract's fields; their problems hold the class like the rest."""
    if known is None:
        known = {f["kind"][2:] for f in contract.get("fields", ()) if f["kind"].startswith("S:")} & set(registered())
    slotted = set()
    if contract.get("vslots"):
        own, overrides, _ = slot_declarations(contract, sources)
        slotted = {member_key(text, name) for text in own + overrides}
    carried, problems = special_declarations(name, sources, known=known, slotted=slotted)
    views = {}
    for source in sources:
        try:
            records = field_records((ROOT / source).read_text(encoding="latin-1"), name)
        except OSError:
            continue
        if records is not None:
            views[source] = records
    qualifiers, field_problems = field_qualifiers(contract, views)
    carried += [{"role": "qualifier", "access": None, "sig": f"qualifier {field}", "text": "", "field": field,
                 "qualifiers": sorted(found)} for field, found in sorted(qualifiers.items())]
    return carried, problems + field_problems


# ---------------------------------------------------------------- virtual slots
#
# A polymorphic class's layout includes its vtable, so the header must declare
# every slot the contract decided, in slot order. The contract names each slot
# (CodeView `name(args)`); the declaration text (return type, parameters,
# const, pure, an inline body) comes from the views that voted for it, by
# majority of signature. A slot no view spells, a tie, or a gap in the slot
# run refuses generation: a header that guessed a slot would shift every slot
# after it.

VIRTUAL_NAME = re.compile(r"(~?[A-Za-z_]\w*)\s*\(")


def arg_count(text):
    """Parameters in the first parenthesized list of `text` (`()` and `(void)` are 0)."""
    depth, args, seen = 0, 0, ""
    for char in text:
        if char == "(":
            depth += 1
            if depth == 1:
                continue
        elif char == ")":
            depth -= 1
            if depth == 0:
                break
        if depth == 1 and char == ",":
            args += 1
        if depth >= 1:
            seen += char
    return 0 if seen.strip() in ("", "void") else args + 1


def has_base_clause(text, name):
    """Whether the view of `name` in `text` spells a base clause."""
    span = body_span(text, name)
    if not span:
        return False
    head = masked(text[span[0]:span[1]]).split("{")[0]
    return bool(re.search(r"(?<!:):(?!:)", head))


def virtual_members(text, name):
    """[(member name, argument count, declaration)] of the virtuals a view of `name` declares.

    A destructor is named `~` (CodeView calls its slot __vecDelDtor)."""
    span = body_span(text, name)
    if not span:
        return []
    code = re.sub(r"//[^\n]*|/\*.*?\*/", "", text[span[0]:span[1]], flags=re.S)
    if "{" not in code:
        return []
    inner = code[code.index("{") + 1:code.rindex("}")]
    out = []
    for member in split_members(inner):
        member = re.sub(r"^(?:(?:public|private|protected)\s*:\s*)+", "", member).strip()
        if not re.match(r"virtual\b", member):
            continue
        found = VIRTUAL_NAME.search(member.split("{")[0])
        if not found:
            continue
        member_name = "~" if found.group(1).startswith("~") else found.group(1)
        out.append((member_name, 0 if member_name == "~" else arg_count(member[found.end() - 1:]),
                    re.sub(r"\s+", " ", member).strip()))
    return out


def slot_key(member):
    """(name, argument count) of a contract slot member such as `xfer(Xfer*)` or `__vecDelDtor(uint)`."""
    found = VIRTUAL_NAME.match(member)
    if not found:
        return None, 0
    name = found.group(1)
    if name.startswith("~") or name in ("__vecDelDtor", "__delDtor"):
        return "~", 0
    return name, arg_count(member[found.end() - 1:])


PARAM_SPELL = {"unsignedint": "uint", "unsignedshort": "ushort", "unsignedchar": "uchar", "unsignedlong": "ulong",
               "unsigned": "uint", "__int64": "int64", "unsigned__int64": "uint64", "wchar_t": "wchar"}


def param_types(text):
    """Normalized parameter types of the first parenthesized list (`Xfer *x` -> `Xfer*`)."""
    inner = text[text.index("(") + 1:]
    depth, out, current = 1, [], ""
    for char in inner:
        depth += char == "("
        depth -= char == ")"
        if depth == 0:
            break
        if char == "," and depth == 1:
            out.append(current)
            current = ""
        else:
            current += char
    out.append(current)
    types = []
    for param in out:
        param = re.sub(r"=.*$", "", param)
        param = re.sub(r"\b(const|struct|class|enum|volatile)\b", "", param).strip()
        param = re.sub(r"\s*([*&])\s*", r"\1 ", param).strip()
        words = param.split()
        if len(words) > 1 and re.match(r"^[A-Za-z_]\w*$", words[-1]) and not words[-1].endswith(("*", "&")):
            words = words[:-1]                       # the parameter's name
        spelled = "".join(words)
        types.append(PARAM_SPELL.get(spelled, spelled))
    return [] if types in ([""], ["void"]) else types


def matching(found, want, member):
    """The declarations in one view's `found` that spell contract slot `member`.

    Name and parameter count select; when one view declares several such
    overloads, the parameter types must also agree with the contract's."""
    hits = [text for n, args, text in found if (n, args) == want]
    if len(hits) > 1 and want[0] != "~":
        exact = [t for t in hits if param_types(t.split("{")[0]) == param_types(member)]
        hits = exact if len(exact) == 1 else []
    return hits


def declaration_key(text):
    head = text.split("{")[0].rstrip(" ;")
    pure = bool(re.search(r"=\s*0\s*$", head))
    return signature(re.sub(r"\s*=\s*0\s*$", "", head), ""), pure


def pick_declaration(spellings):
    """The majority declaration among `spellings` (Counter of text), or None on a tie or
    when its views contradict each other's purity.

    Votes are on the signature. Purity is not voted: a view that spells `= 0` says the
    member has no body, and a view that omits it only left the specifier out (dropping
    it leaves an undefined virtual the link stubs), so the slot is pure when any view of
    the winning signature spells it pure; one that also gives it an inline body
    contradicts that. An inline body beats a bare declaration of the same signature
    (units that inline it need the body)."""
    votes = collections.Counter()
    for text, count in spellings.items():
        votes[declaration_key(text)[0]] += count
    top = votes.most_common(2)
    if not top or (len(top) > 1 and top[0][1] == top[1][1]):
        return None
    winners = {t: n for t, n in spellings.items() if declaration_key(t)[0] == top[0][0]}
    pure = {t: n for t, n in winners.items() if declaration_key(t)[1]}
    if pure and any("{" in t for t in winners):
        return None
    best = max(pure or winners, key=lambda t: ("{" in t, winners[t], -len(t)))
    return best if best.endswith(("}", ";")) else best + ";"


def slot_conflict(spellings):
    """Why pick_declaration refused `spellings`: a tie, or a pure spelling beside an inline body."""
    votes = collections.Counter()
    for text, count in spellings.items():
        votes[declaration_key(text)[0]] += count
    top = votes.most_common(2)
    if len(top) > 1 and top[0][1] == top[1][1]:
        return "spellings tie"
    return "pure in one view, an inline body in another"


def base_slot_names(contract, known=None):
    """Virtual member names the contract's registered base headers declare (their overridable slots)."""
    known = registered() if known is None else known
    names = set()
    for base in contract.get("bases", []):
        path = known.get(base_identity(base))
        if not path or not (ROOT / path).exists():
            continue
        text = masked((ROOT / path).read_text(encoding="latin-1"))
        for found in re.finditer(r"\bvirtual\b[^;{}]*?(~?[A-Za-z_]\w*)\s*\(", text):
            names.add("~" if found.group(1).startswith("~") else found.group(1))
    return names


def rename_destructor(text, short):
    return re.sub(r"~\s*[A-Za-z_]\w*", "~" + short, text, count=1)


def slot_declarations(contract, sources, read=None, known=None, index=None):
    """([own slot declaration, emit order], [override declaration], [problem]) for the contract's vslots.

    Own slots are the ones the contract decided (a derived contract holds only
    its introductions); a base's slots are never re-emitted, and a view's
    virtual whose name a registered base header declares is an override,
    spelled by majority like an own slot. A pure own slot that a matched
    ledger row unambiguously defines (pure_contradicted; `index`:
    _matched_index's shape) is a problem."""
    name = contract["class"]
    short = name.split("::")[-1]
    read = read or (lambda s: (ROOT / s).read_text(encoding="latin-1"))
    slots = {int(k): v["member"] for k, v in (contract.get("vslots") or {}).items()}
    problems = [f"{q['attribute']} undecided" for q in contract.get("queue", []) if q["attribute"].startswith("slot")]
    views, derived = {}, set()
    for source in sources:
        try:
            text = read(source)
        except OSError:
            continue
        views[source] = virtual_members(text, name)
        if has_base_clause(text, name):
            derived.add(source)
    if slots:
        start = (contract.get("evidence", {}).get("inherited", {}).get("inherited_slots", 0)
                 if contract.get("bases") else 0)
        start = min(start, min(slots))
        problems += [f"slot{k} undecided" for k in range(start, max(slots) + 1)
                     if k not in slots and f"slot{k} undecided" not in problems]
    decided = {}
    for slot, member in sorted(slots.items()):
        want = slot_key(member)
        spellings = collections.Counter(text for found in views.values() for text in matching(found, want, member))
        text = pick_declaration(spellings)
        if text is None:
            problems.append(f"slot{slot} {member}: " + ("no view spells it" if not spellings
                                                        else slot_conflict(spellings)))
            continue
        if declaration_key(text)[1] and want[0] != "~" and pure_contradicted(name, want[0], want[1], index):
            problems.append(f"slot{slot} {member}: pure in a view, but a matched row defines it")
            continue
        decided[slot] =(want[0], rename_destructor(text, short) if want[0] == "~" else text)
    # MSVC lays an overload group out at its first declaration in REVERSE
    # declaration order (tools/class_layouts.py, "THE TRAP"): emit each run of
    # same-name slots reversed. A name split across non-adjacent slots cannot
    # be declared at all.
    runs = []
    for slot in sorted(decided):
        member_name = decided[slot][0]
        if runs and runs[-1][0] == member_name and runs[-1][1][-1] == slot - 1:
            runs[-1][1].append(slot)
            continue
        if any(r[0] == member_name for r in runs):
            problems.append(f"slot{slot} {member_name}: overloads in non-adjacent slots")
        runs.append((member_name, [slot]))
    order = [decided[s][1] for _, run in runs for s in reversed(run)]
    own = {n for n, _ in decided.values()}
    overrides = []
    # Only a view that spells a base clause declares an override; a view that
    # copied the base's slots into the class re-declares them, never overrides.
    for member_name in sorted(base_slot_names(contract, known) - own):
        spellings = collections.Counter(text for source, found in views.items() if source in derived
                                        for n, _, text in found if n == member_name)
        text = pick_declaration(spellings) if spellings else None
        if text is not None:
            overrides.append(rename_destructor(text, short) if member_name == "~" else text)
    return order, overrides, problems


SPELL = {"uint": "unsigned int", "ushort": "unsigned short", "uchar": "unsigned char", "ulong": "unsigned long",
         "int64": "__int64", "uint64": "unsigned __int64", "wchar": "wchar_t", "int8": "signed char",
         "uint8": "unsigned char"}


def spelled(type_name, field):
    stem = type_name.rstrip("*")
    stars = type_name[len(stem):]
    array = re.match(r"(.+)\[(\d+)\]$", stem)
    if array:
        return f"{SPELL.get(array.group(1), array.group(1))} {field}[{array.group(2)}]"
    return f"{SPELL.get(stem, stem)} {stars}{field}"


def base_identity(base):
    """The class a base spelling names: CodeView spells virtual inheritance `virtual B`."""
    return re.sub(r"^(?:(?:virtual|public|protected|private)\s+)+", "", base).strip()


def unheadered_bases(contract):
    """The contract's bases with no registered canonical header: the class cannot be generated yet."""
    known = registered()
    return [b for b in contract.get("bases", []) if base_identity(b) not in known]


def nested_includes(contract, header, slots=None):
    """`#include` lines for the canonical headers of the contract's bases, member aggregates
    and the registered classes its slot declarations name (`const Coord3D *` needs Coord3D's
    class-key, which only its header fixes)."""
    lines, known = [], registered()
    wanted = [base_identity(b) for b in contract.get("bases", [])]
    wanted += [f["kind"][2:] for f in contract["fields"] if f["kind"].startswith("S:")]
    for text in (slots[0] + slots[1]) if slots else []:
        wanted += [w for w in re.findall(r"[A-Za-z_]\w*", text.split("{")[0])
                   if w in known and w != contract["class"]]
    for type_name in wanted:
        if type_name not in known:
            continue
        spelling = os.path.relpath(ROOT / known[type_name], (ROOT / header).parent) if header else known[type_name]
        line = f'#include "{Path(spelling).as_posix()}"'
        if line not in lines:
            lines.append(line)
    return lines + [""] if lines else []


def generate(contract, variant, methods, header=None, slots=None, special=()):
    """The header text of `variant`. `special` (special_declarations) is declared in every
    variant: a dropped special member is a link fault the byte gate cannot see."""
    name, key = contract["class"], contract["key"]
    roles = {s["role"] for s in special}
    guard = re.sub(r"\W", "_", f"CANONICAL_{name}_H").upper()
    lines = [f"// {name}: canonical layout, generated by tools/header_adopt_lane.py from",
             f"// {class_contract.contract_path(name).relative_to(ROOT).as_posix()}"
             f" (variant {variant}). Edit the contract, not this file.",
             f"// sizeof {contract['size']} ({contract['size_by']}); class-key {key} ({contract['key_by']}).",
             f"#ifndef {guard}", f"#define {guard}", ""]
    # `includes`: also include the registered headers of the classes the slot
    # declarations name. It fixes their class-key, so it is a variant: units
    # whose rows mangle a private view's other key fail with it.
    lines += nested_includes(contract, header, slots if "includes" in variant.split("+") else None)
    bases = ", ".join(f"public {b}" for b in contract["bases"])
    lines.append(f"{key} {name}" + (f" : {bases}" if bases else "") + " {")
    if key == "class":
        lines.append("public:")
    qualifiers = {s["field"]: s["qualifiers"] for s in special if s["role"] == "qualifier"}
    for field in contract["fields"]:
        if field["kind"] == "VPTR":
            continue
        lines.append(f"    {qualified_spelling(field, qualifiers.get(field['name'], ()))};")
    if "ctor" in variant and "default" not in roles:
        lines.append(f"    {name}() {{}}")
    if "copy" in variant.split("+") and "copy" not in roles:
        # an out-of-line copy constructor: retail calls one (a matched ??0X@@QAE@ABU0@@Z row)
        lines.append(f"    {name}(const {name} &that);")
    def member_lines(found):
        return ["    " + s["text"].replace("\n", "\n    ") for s in found]

    lines += member_lines(s for s in special if s["access"] == "public" and s["role"] != "dtor")
    if slots is not None:
        # The vtable is layout: every variant declares the decided slots in
        # slot order, then the overrides of the bases' slots the views spell.
        # The view methods then contribute no virtual of their own.
        own, overrides = slots
        for member in own + overrides:
            lines.append("    " + member)
        methods = {k: v for k, v in methods.items() if not re.match(r"\s*virtual\b", v)}
    if "methods" in variant:
        # A leading destructor would put the delete-dtor in earlier vtable
        # slots: every non-destructor method must precede it.
        carried = {s["sig"] for s in special}
        members = [v for v in methods.values() if member_key(v, name) not in carried]
        members.sort(key=lambda m: 1 if re.match(r"^\s*(?:\w+\s+)*~\w*\s*\(", m) else 0)
        for member in members:
            lines.append("    " + member.replace("\n", "\n    "))
    # The destructor stays last among the public members; other access follows under its label.
    lines += member_lines(s for s in special if s["access"] == "public" and s["role"] == "dtor")
    for access in ("protected", "private"):
        held = member_lines(s for s in special if s["access"] == access)
        lines += [f"{access}:"] + held if held else []
    lines += ["};", "", f"#endif // {guard}", ""]
    return "\n".join(lines)


# ---------------------------------------------------------------- the gate

def gate_one(source):
    """None when every row of `source` byte-matches, else the first diagnostic."""
    if BFME2:
        command = [sys.executable, "tools/build.py", source]
        env = dict(os.environ, MSYS_NO_PATHCONV="1")
    else:
        # through bash, as adopt_header.py does; build.sh needs MSYS path conversion
        import bash_path
        command = [bash_path.bash(), str(ROOT / "build.sh"), source]
        env = {k: v for k, v in bash_path.env().items() if k != "MSYS_NO_PATHCONV"}
    done = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, errors="replace", env=env)
    out = done.stdout + done.stderr
    if done.returncode == 0 and "Functions: OK" in out:
        return None
    return next((line.strip()[:200] for line in out.splitlines()
                 if re.search(r"error C\d+|Functions: FAIL|compile failed|MISMATCH|FAIL", line)),
                f"gate exited {done.returncode}")


def gate_many(sources, _depth=0):
    """One ordinary scoped build per bounded cohort; isolate failures by bisection.

    A successful build verifies the union of the same rows/local checks as separate
    builds. Never infer which source failed from a diagnostic mentioning its name.
    Keep link admission separate: it must see all changed objects together.
    """
    sources = list(dict.fromkeys(sources))
    if not sources:
        return {}
    if len(sources) == 1 or not BFME2:
        return {s: gate_one(s) for s in sources}
    # Leave ample room for the interpreter, tool path and Windows quoting.
    chunks, chunk, size = [], [], 0
    for source in sources:
        cost = len(source) + 3
        if chunk and size + cost > 6000:
            chunks.append(chunk)
            chunk, size = [], 0
        chunk.append(source)
        size += cost
    chunks.append(chunk)
    if len(chunks) > 1:
        return {s: why for group in chunks for s, why in gate_many(group).items()}
    done = subprocess.run([sys.executable, "tools/build.py", *sources], cwd=ROOT, capture_output=True,
                          text=True, errors="replace", env=dict(os.environ, MSYS_NO_PATHCONV="1"))
    if done.returncode == 0 and "Functions: OK" in done.stdout:
        return dict.fromkeys(sources)
    # Sparse failures benefit from bisection; a wholly broken variant must not
    # pay for a complete binary tree of failing process launches as well as all
    # singleton checks. Two levels cap that overhead at seven group launches.
    if len(sources) <= 4 or _depth >= 2:
        return {s: gate_one(s) for s in sources}
    middle = len(sources) // 2
    return {**gate_many(sources[:middle], _depth + 1), **gate_many(sources[middle:], _depth + 1)}


class _ClassKeyParser(wb_gold._Parser):
    """Resolve type-key positions, retaining the name table's exact identities.

    The WB parser supplies the ten-entry, deduplicated name tables and nested
    template contexts. Template identities use their source spans, not WB's
    display names (which omit arguments). This also lets a second parse prove
    every resolved identity unchanged after editing only the key characters.
    """

    def __init__(self, text):
        super().__init__(text)
        self.records = []
        self.memo_shape = []
        self.argument_types = []
        self.argument_refs = []
        self.symbol_depth = 0
        self.after_local = False

    def memorize(self, key, name):
        before = [k for k, _ in self.names]
        value = ("name", name) if isinstance(name, str) else name
        super().memorize(key, value)
        self.memo_shape.append((len(before), len(self.names),
                                before.index(key) if key in before else -1))

    def unqualified_name(self):
        if self.peek().isdigit():
            if self.after_local:
                # Whether a local scope piece enters the outer table is not
                # proven here; a reference that could depend on it refuses.
                raise wb_gold.DemangleError("name back-reference after a local scope")
            index = int(self.take())
            if index >= len(self.names):
                raise wb_gold.DemangleError("name back-reference out of range")
            return self.names[index][1]
        if self.peek(2) == "?$":
            start = self.i
            key, _ = self.template_name()
            value = ("template", start, self.i)
        elif self.peek() == "?":
            return ("special", self.special_name())
        else:
            key = self.simple_name()
            value = ("name", key)
        self.memorize(key, value)
        return next((v for k, v in self.names if k == key), value)

    def scope(self):
        # A numbered local scope, '?<number>?<encoded symbol>': the enclosing
        # function's own decorated name, with its own name and argument
        # tables (1,741 of the ledger's 1,833 such names embed a function
        # row's exact name, 150 of them with back-references). Only the
        # anonymous namespace '?A0x...' and template names stay with WB.
        if self.peek() != "?" or self.peek(2) == "?$" or self.peek(3) == "?A0":
            return super().scope()
        self.i += 1
        self.number()
        self.expect("?")
        nested = _ClassKeyParser(self.s)
        nested.i = self.i
        nested.encoded_symbol()
        self.records.extend(nested.records)
        self.memo_shape.append(("local", tuple(nested.memo_shape), tuple(nested.argument_types),
                                tuple(nested.argument_refs)))
        self.i = nested.i
        self.after_local = True
        return ("local",)

    def type(self):
        start = self.i
        if self.peek().isdigit():
            raise wb_gold.DemangleError("type reference outside a parameter list")
        if self.peek() in ("U", "V", "T"):
            key = self.take()
            self.records.append((start, key, tuple(self.qualified_name())))
            return
        return super().type()

    def encoded_symbol(self):
        self.symbol_depth += 1
        if self.symbol_depth != 1:
            raise wb_gold.DemangleError("nested encoded symbol not supported")
        self.expect("?")
        if self.peek(2) == "?$":
            # A function-template identifier does not enter the enclosing
            # name table. Its arguments use template_name's local table.
            self.template_name()
        else:
            self.unqualified_name()
        self.scopes()
        code = self.take()
        if code in "01234":
            self.type()
            self.storage_cv()
        elif code in "67":
            self.storage_cv()
            if self.peek() != "@":
                self.qualified_name()
            else:
                self.i += 1
        elif code in "YZCDKLSTABEFIJMNQRUV":
            self.function_signature(code)
        elif code in "GHOPWX":
            # An adjustor thunk: the this-adjustment, then a member signature.
            self.number()
            self.function_signature("Q")
        else:
            raise wb_gold.DemangleError("unsupported function/header class")

    def throw_spec(self):
        self.expect("Z")

    def arg_list(self):
        # Parameter-type references have a separate, non-deduplicated table.
        # Nested function types SHARE it, including those in return types.
        # Only completed multi-character parameters enter it; returns do not.
        if self.peek() == "X":
            self.i += 1
            return
        while self.peek() not in ("@", "Z"):
            if not self.peek():
                raise wb_gold.DemangleError("unterminated argument list")
            start = self.i
            if self.peek().isdigit():
                index = int(self.take())
                if index >= len(self.argument_types):
                    raise wb_gold.DemangleError("argument-type back-reference out of range")
                self.argument_refs.append((start, index, self.argument_types[index]))
            else:
                self.type()
                if self.i - start > 1 and len(self.argument_types) < 10:
                    self.argument_types.append((start, self.i))
        self.i += 1


def _parse_class_keys(symbol):
    import rename
    rename.fragments(symbol)  # Full supported grammar, including trailing input.
    prefix = next((p for p in rename.FUNCLET_PREFIXES if symbol.startswith(p)), "")
    text = symbol[len(prefix):]
    if prefix:
        text = re.sub(r"\$[0-9]+$", "", text)
    parser = _ClassKeyParser(text)
    parser.encoded_symbol()
    if parser.i != len(text):
        raise wb_gold.DemangleError("unconsumed signature")
    return parser, len(prefix)


def rekey_symbol(symbol, scope, other, allow_mixed=False):
    """Change only U/V TYPE keys resolving to this exact plain qualified scope.

    Never change a backreference digit. Unknown grammar, mixed target keys or
    changed name-table/identity structure refuse the whole unit. Byte, EH,
    data and provider/caller verification are still required by the lane.
    `allow_mixed` (the class-key migration only, toward the key retail's
    exports decide) rewrites a name that already spells both keys, since the
    result spells one.
    """
    import rename
    parts = scope.split("@")
    if other not in ("U", "V") or not all(rename.IDENT.fullmatch(p) for p in parts):
        raise ValueError("class-key rewrite needs a plain qualified scope and U/V key")
    if parts[0] + "@" not in symbol:
        return symbol
    if not symbol.startswith(("?", "__ehhandler$?", "__unwindfunclet$?")):
        rename.fragments(symbol)  # A plain C name has no class-key positions.
        return symbol
    target = tuple(("name", p) for p in reversed(parts))
    parser, offset = _parse_class_keys(symbol)
    have = "V" if other == "U" else "U"
    kinds = {key for _, key, name in parser.records if name == target}
    if other in kinds and kinds - {other} and not allow_mixed:
        raise ValueError("mixed existing keys for the same target")
    out = list(symbol)
    expected = []
    for position, key, name in parser.records:
        if key == other and name == target:
            out[position + offset] = have
            key = have
        expected.append((position, key, name))
    result = "".join(out)
    checked, _ = _parse_class_keys(result)
    if (parser.memo_shape != checked.memo_shape or expected != checked.records
            or parser.argument_types != checked.argument_types or parser.argument_refs != checked.argument_refs):
        raise ValueError("class-key rewrite changed name-table or resolved type identities")
    return result


def _key_renames(rows, scope, other):
    """Plan the entire unit, refusing it if any relevant name is unsupported."""
    import rename
    renames, blocked = [], []
    for row in rows:
        old = row["name"]
        try:
            new = rekey_symbol(old, scope, other)
        except (rename.Unparsed, wb_gold.DemangleError, ValueError):
            blocked.append(old)
            continue
        if new != old:
            renames.append((old, new))
    return ([], blocked) if blocked else (renames, [])


def key_backref_names(rows, scope, other):
    """Unsupported relevant row names; resolved name backreferences are safe."""
    return _key_renames(rows, scope, other)[1]


def key_metadata_blockers(items):
    """Refuse renames the lane's name-column-only writer cannot carry safely.

    A later full key-migration transaction must own pins, funclet parents,
    body-owner identities and other embedded names together. Resolving a
    backreference is not permission to leave that metadata on the old name.
    Discovery is read-only and batched before preparing or writing a unit.
    """
    owners = collections.defaultdict(set)
    targets = collections.defaultdict(set)
    for source, _, _, renames in items:
        for old, new in renames:
            owners[old].add(source)
            targets[new].add(source)
    if not owners or not BFME2:
        return {}
    pattern = re.compile("|".join(re.escape(n) for n in sorted(owners, key=len, reverse=True)))
    hits = collections.defaultdict(set)

    def inspect(text, label):
        for match in pattern.finditer(text):
            for source in owners[match.group()]:
                hits[source].add(label)

    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            inspect(row.get("notes", ""), "functions.csv notes")
            if row["name"] not in owners:
                inspect(row["name"], "functions.csv unplanned row family")
            if row["name"] in targets and row["name"] not in owners:
                for source in targets[row["name"]]:
                    hits[source].add("functions.csv existing target name")
    for filename in ("symbols.csv", "data_rows.csv", "body_owners.csv", "data_converged.csv",
                     "gate_baseline.txt", "code_identity_baseline.tsv", "header_queue.tsv",
                     "hatch_baseline.tsv", "data_check_baseline.txt", "flag_overrides.csv"):
        path = ROOT / "reverse" / filename
        if path.is_file():
            inspect(path.read_text(encoding="utf-8-sig"), filename)
    path = ROOT / "reverse/deleted_rows.csv"
    if path.is_file():
        with path.open(newline="", encoding="utf-8-sig") as handle:
            for row in csv.DictReader(handle):
                if row.get("name") in targets:
                    for source in targets[row["name"]]:
                        hits[source].add("deleted_rows.csv target tombstone")
    return {s: "class-key metadata requires a coordinated name transaction: " + ", ".join(sorted(labels))
            for s, labels in hits.items()}


# ---------------------------------------------------------------- class-key migration
#
# A registered class whose canonical header spells the wrong class-key (LINK-018:
# retail's exports spell Coord3D `V`, the header `struct`) changes in ONE
# transaction: the contract's key, the generated header, every declaration and
# view in Code/, every mangled name in the ledgers and registers that spells the
# class, and the dup_defs baseline's keys. All or nothing: before any write it
# refuses a key retail's exports do not decide, a name in an identity position the
# parser cannot resolve, a respelled name that would own a second address or land
# on a tombstone, a converged data name, and any touched path whose claim this
# worker does not hold. A hatch token the respelling changes (an /alternatename in
# a source) is carried by tools/hatch_counters.py --update under its rule 11.
# Shims under reference/shims/ that declare the class change with it. The before-state goes in rename.py's journal
# (`rename.py recover` restores a killed run). Nothing is verified here: the
# rebuilt objects must differ only by the respelled names (the evidence kit takes
# the plan's map as its declared exception), and reverse/data_ledger.csv is
# regenerated from them by tools/data_ledger.py, never edited.

REKEY_TOKEN = re.compile(r"(?:__ehhandler\$|__unwindfunclet\$)?\?[A-Za-z0-9_?@$]+")
# Ledger columns whose value IS an identity: an unresolvable name there refuses.
REKEY_NAME_COLUMNS = {"reverse/functions.csv": "name", "reverse/symbols.csv": "name",
                      "reverse/data_rows.csv": "name", "reverse/deleted_rows.csv": "name",
                      "reverse/stlport_trial.csv": "name"}
REKEY_NOTE_KEYS = re.compile(r"\b(?:parent|parents|icf-owner|dup-of|object-symbol|fold-proof)=([^\s;,]+)")
REKEY_IDENTITY_FILES = ("reverse/place_denylist.txt",)
REKEY_PROSE_FILES = ()
REKEY_LEFT_ALONE = ("reverse/data_ledger.csv (regenerate with tools/data_ledger.py after the rebuild)",
                    "reverse/name_basis.csv's existing records (carry records are appended), name_agreed.csv, "
                    "name_votes.csv, name_vote_sources.csv (history)",
                    "reverse/re_attempts.log, reverse/attempts/, reverse/attempt_support/ (evidence)",
                    "reverse/vtable_bridge_queue.tsv, reverse/exit_link_blockers.tsv (the real link writes them)",
                    "reverse/name_tiers.csv (allowed_symbols.py --tiers owns it; the tiers are checked unchanged)",
                    "reverse/header_queue.tsv (a debt register; its spellings are failure prose)",
                    "tools/tests/fixtures/")
REKEY_CODE_SUFFIXES = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
REKEY_MARKER = re.compile(r"absent-from-retail|present-unmatched|tu-skeleton:")
# A unit can compile the class from a donor header the rekey never edits (one under reference/,
# outside reference/shims/), directly or through other headers, and then keeps the old key after
# the flip whatever its own text says (LINK-018: W3DRopeDraw.cpp names no Coord3D yet reaches the
# Zero Hour Lib/BaseType.h through "Common/Thing.h"). The plan reads which files each ledger unit
# compiled from build.py's own receipt (the .deps.json next to its object, from the compiler's
# include notes), and only from a receipt build.compile_is_current accepts and that names this
# source and this object; every direct include must resolve, by full path through the compiler's
# own roots, to a file the receipt lists. Anything it cannot prove refuses the plan.
REKEY_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^">\n]+)[">]', re.MULTILINE)
REKEY_ANY_INCLUDE = re.compile(r"^[ \t]*#[ \t]*include\b", re.MULTILINE)
REKEY_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.DOTALL)
REKEY_UNIT_SUFFIXES = (".cpp", ".c", ".cc", ".cxx")
_REKEY_INVENTORY_CACHE = {}                       # build.search_inventory's cache, one per scan


def _rekey_units(root):
    """The compile units the ledger builds: C and C++ sources of reverse/functions.csv and data_rows.csv."""
    units = set()
    for rel in ("reverse/functions.csv", "reverse/data_rows.csv"):
        path = Path(root) / rel
        if path.is_file():
            with path.open(newline="", encoding="utf-8") as handle:
                units |= {r["source"] for r in csv.DictReader(handle)
                          if (r.get("source") or "").endswith(REKEY_UNIT_SUFFIXES)}
    return sorted(u for u in units if (Path(root) / u).is_file())


def _rekey_receipt_gaps(root, rel, deps, roots, forced, find):
    """Why DEPS (a receipt's dependency map) does not prove REL's includes, or None.

    Every map entry must be a plain path inside the repository. Every direct include of the unit's own
    text (comments removed) and every forced include must resolve, by full path in the compiler's search
    order (the unit's directory first for a quoted or forced include, then ROOTS), to a file the map
    lists. FIND(path) is the existing file a path names (case-resolved) or None. An #include this cannot
    read (a macro name), one that resolves to no file, and one whose file the map does not list all
    count: a receipt that cannot prove its closure proves nothing."""
    base = os.path.normpath(str(root))
    listed = set()
    for key in deps:
        k = key.replace("\\", "/")
        if not k or os.path.isabs(k) or re.match(r"^[A-Za-z]:", k) or any(s in ("", ".", "..") for s in k.split("/")):
            return f"its receipt lists {key!r}, which is not a plain path inside the repository"
        listed.add(os.path.normpath(os.path.join(base, k)).lower())
    code = REKEY_COMMENT.sub("", (Path(base) / rel).read_text(encoding="utf-8", errors="replace"))
    found = REKEY_INCLUDE.findall(code)
    if len(found) != len(REKEY_ANY_INCLUDE.findall(code)):
        return "it has an #include this check cannot read (a macro name)"
    unit_dir = os.path.dirname(os.path.join(base, rel))
    for quote, include in [('"', f) for f in forced] + found:
        dirs = ([unit_dir] if quote == '"' else []) + list(roots)
        hit = next((h for h in (find(os.path.normpath(os.path.join(d, include.strip()))) for d in dirs) if h), None)
        if hit is None:
            return f"{include!r} resolves to no file through its directory and the compiler's roots"
        if os.path.normpath(hit).lower() not in listed:
            return f"{include!r} resolves to {os.path.relpath(hit, base)}, which its receipt does not list"
    return None


def _rekey_unit_receipt(root, rel):
    """(dependency paths relative to the repository, None) when REL's object is current and its receipt
    proves its includes; (None, why) otherwise. Only this repository's own build can be read."""
    if Path(root).resolve() != ROOT.resolve():
        return None, "there is no build of this tree to read"
    import build
    source = ROOT / rel
    obj = Path(build.obj_path(source))
    sidecar = obj.with_suffix(".deps.json")
    if not obj.is_file() or not sidecar.is_file():
        return None, "it has no object and dependency receipt"
    try:
        meta = json.loads(sidecar.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None, "its dependency receipt is unreadable"
    if not isinstance(meta, dict) or not isinstance(meta.get("deps"), dict):
        return None, "its dependency receipt has no dependency map"
    if meta.get("path") != build._root_key(source):
        return None, f"its receipt describes {meta.get('path')}, not this source"
    if meta.get("object") != hashlib.md5(obj.read_bytes()).hexdigest():
        return None, "its receipt describes another object than the one on disk (stale)"
    # strict: the census-grade proof. The include search directories, retry roots included, must still be
    # what the compile saw (a header added ahead of a recorded one anywhere in the closure), so only a
    # version-2 receipt with its inventory proves a unit that includes anything.
    if not build.compile_is_current(source, obj, strict=True, inventory_cache=_REKEY_INVENTORY_CACHE):
        return None, ("its object is not proven current: the source, the compile command, a dependency or an "
                      "include search directory changed since it was built, or its receipt has no inventory")
    if meta.get("version") != 2 and meta["deps"]:
        return None, "its receipt is not census-grade (version 2) yet lists dependencies"
    # The compiler's own search order: the -I roots in command-line order, then INCLUDE in order, with the
    # receipt's retry roots appended to both, as build.py's retry and compile_is_current append them. Not
    # _include_search_roots or the receipt's search_roots: that is a sorted set, and it holds the unit's
    # directory, which only a quoted include searches (first).
    command, env = build.compiler_command(source, obj)
    flags, forced, tokens = [], [], iter(command)
    for token in tokens:
        if token in ("-I", "/I"):
            flags.append(next(tokens, ""))
        elif token[:1] in "-/" and token[1:3] == "FI":
            forced.append(token[3:] or next(tokens, ""))
        elif token[:1] in "-/" and token[1:2] == "I":
            flags.append(token[2:])
    retry = [str(ROOT / d) for d in (meta.get("retry_dirs") or [])] if meta.get("version") == 2 else []
    include = [r for r in env.get("INCLUDE", "").split(";") if r]
    roots = []
    for raw in flags + retry + include + retry:
        host = build._host_path(raw)
        path = host if host is not None else raw
        roots.append(os.path.normpath(path if os.path.isabs(path) else os.path.join(str(ROOT), path)))
    why = _rekey_receipt_gaps(ROOT, rel, meta["deps"], roots, forced, build._case_resolve)
    if why:
        return None, why
    return sorted(k.replace("\\", "/") for k in meta["deps"]), None


def _rekey_unit_object(root, rel, name, key):
    """The old-key spellings of NAME in REL's object (empty: none). The receipt has bound the object."""
    import build
    obj = Path(build.obj_path(ROOT / rel))
    return scan_old_key(name, key, [obj]).get(str(obj), [])


def _rekey_donor_units(root, name, key):
    """({unit: (donor definitions, old-key spellings)}, {unit: why unverified}) over the ledger's units.

    A unit whose receipt does not prove what it compiled is unverified; one whose dependencies include a
    file under reference/ (outside reference/shims/) defining NAME is listed with its object's old-key
    spellings of NAME (empty: harmless as built)."""
    defines = re.compile(r"\b(?:struct|class)\s+" + re.escape(name) + r"\b\s*(?::[^;{]*)?\{")
    defines_at, donor_units, unverified, verified = {}, {}, {}, []
    _REKEY_INVENTORY_CACHE.clear()
    for rel in _rekey_units(root):
        deps, why = _rekey_unit_receipt(root, rel)
        if why:
            unverified[rel] = why
            continue
        verified.append(rel)
        donors = []
        for dep in deps:
            if dep.startswith("reference/") and not dep.startswith("reference/shims/"):
                if dep not in defines_at:
                    try:
                        defines_at[dep] = bool(defines.search((Path(root) / dep).read_text(encoding="utf-8",
                                                                                           errors="replace")))
                    except OSError:
                        defines_at[dep] = True          # unreadable: assume the worst
                if defines_at[dep]:
                    donors.append(dep)
        if donors:
            donor_units[rel] = (donors, _rekey_unit_object(root, rel, name, key))
    # The strict checks share one inventory cache: a search directory that changed after a unit warmed it
    # would pass every later cached check. Re-take the cached directories; any change voids the scan.
    if _REKEY_INVENTORY_CACHE:
        import build
        if not build._inventory_cache_still_current(_REKEY_INVENTORY_CACHE):
            for rel in verified:
                unverified[rel] = ("an include search directory changed during the scan, so no cached strict "
                                   "check proves anything; run the plan again")
            donor_units = {}
    return donor_units, unverified

class RekeyRefused(Exception):
    """The migration cannot be applied whole; nothing was written."""


def _rekey_relevant(token, name):
    """Could `token` spell the class `name` as a type or scope? Over-inclusive by design:
    a false hit only parses to itself, a parse failure on one refuses."""
    return re.search(r"(?:^|[@?0-9UVT]|\?_[A-Z0-9])" + re.escape(name) + "@", token) is not None


def _rekey_changes(token, rekeyer):
    """True when `token` spells the class with the old key, or cannot be resolved (so might)."""
    if not _rekey_relevant(token, rekeyer.name):
        return False
    try:
        return rekey_symbol(token, rekeyer.scope, rekeyer.other, allow_mixed=True) != token
    except Exception:
        return True


def _register_hatch_tokens(text, rekeyer):
    """Hatch register tokens the respelling changes. A present_unmatched token is stored with its
    leading '?' stripped (hatch_counters.scan), so it is read with the '?' restored."""
    out = set()
    for line in text.splitlines():
        cells = line.split("\t")
        if line.startswith("#") or len(cells) < 4:
            continue
        token = cells[2]
        forms = [token] if token.startswith("?") else ["?" + token, "??" + token]
        if any(_rekey_changes(form, rekeyer) for form in forms if _rekey_relevant(form, rekeyer.name)):
            out.add(token)
    return sorted(out)


def _split_tokens(text):
    """Mangled tokens in `text` with their spans; `A=B` alias pairs split at '='."""
    for match in REKEY_TOKEN.finditer(text):
        yield match.start(), match.group()


class _Rekeyer:
    def __init__(self, name, other):
        self.name, self.other = name, other
        self.scope = class_contract.mangled_scope(name)
        self.mapping, self.refused, self.prose_left = {}, {}, {}
        self.other_scope = []

    def one(self, token, where, identity):
        """The respelling of one token, recording a failure as a refusal (identity) or a leftover."""
        if not _rekey_relevant(token, self.name):
            return token
        try:
            new = rekey_symbol(token, self.scope, self.other, allow_mixed=True)
        except Exception as err:  # the parser's every failure: rename.Unparsed, DemangleError, ValueError
            (self.refused if identity else self.prose_left).setdefault(token, f"{where}: {err}")
            return token
        if new != token:
            self.mapping[token] = new
        return new

    def text(self, text, where, identity):
        out, last = [], 0
        for start, token in _split_tokens(text):
            new = self.one(token, where, identity)
            if new != token:
                out.append(text[last:start])
                out.append(new)
                last = start + len(token)
        out.append(text[last:])
        return "".join(out)


def _lex(text):
    """[(kind, start, end)] of a C/C++ text: 'code', 'comment' or 'string' (char literals too)."""
    out, i, n, start = [], 0, len(text), 0
    while i < n:
        c, d = text[i], text[i:i + 2]
        if d in ("//", "/*") or c in "\"'":
            if start < i:
                out.append(("code", start, i))
            if d == "//":
                end = text.find("\n", i)
                end = n if end < 0 else end
                out.append(("comment", i, end))
            elif d == "/*":
                end = text.find("*/", i + 2)
                end = n if end < 0 else end + 2
                out.append(("comment", i, end))
            else:
                j = i + 1
                while j < n and text[j] != c and text[j] != "\n":
                    j += 2 if text[j] == "\\" else 1
                end = min(j + 1, n)
                out.append(("string", i, end))
            i = start = end
        else:
            i += 1
    if start < n:
        out.append(("code", start, n))
    return out


def _brace_scopes(text, code_mask, rel):
    """[(position, scope stack)] at each brace or semicolon of the code; a stack entry is
    'namespace', 'linkage' (extern "C" { }), 'class', 'enum', 'block' (a function body, an
    initializer, a statement) or 'unknown': a brace after an identifier this cannot classify
    (`OPEN {` where a macro may expand OPEN to `namespace Other`). An unknown block is never
    file scope. RekeyRefused when the braces do not balance (a macro or #if can hide one),
    since then no declaration's scope is known."""
    events, stack, start = [], [], 0
    for i, c in enumerate(text):
        if not code_mask[i] or c not in ";{}":
            continue
        if c == "{":
            head = "".join(ch for ch, m in zip(text[start:i], code_mask[start:i]) if m)
            raw = " ".join(text[start:i].split())
            if re.search(r"\bnamespace\b\s*\w*\s*$", head):
                stack.append("namespace")
            elif re.search(r'\bextern\s*"C(?:\+\+)?"\s*$', raw):
                stack.append("linkage")
            elif re.search(r"\benum\b[^;{}()]*$", head):
                stack.append("enum")
            elif re.search(r"\b(?:class|struct|union)\b[^;{}()]*$", head):
                stack.append("class")
            elif (re.search(r"\b[A-Za-z_]\w*\s*$", head)
                  and not re.search(r"(?:\)|\b(?:else|do|try|const|volatile|throw))\s*$", head)):
                stack.append("unknown")
            else:
                stack.append("block")
        elif c == "}":
            if not stack:
                raise RekeyRefused(f"{rel}: unbalanced braces; no declaration's scope can be resolved")
            stack.pop()
        start = i + 1
        events.append((i, tuple(stack)))
    if stack:
        raise RekeyRefused(f"{rel}: unbalanced braces; no declaration's scope can be resolved")
    return events


def _pp_directives(text, code_mask):
    """[(start, end, directive, body)] of the preprocessor lines (a `#` that is code at the start
    of a line, joined over backslash continuations)."""
    out = []
    for m in re.finditer(r"(?m)^[ \t]*#", text):
        hash_at = m.end() - 1
        if not code_mask[hash_at]:
            continue
        end = hash_at
        while True:
            nl = text.find("\n", end)
            if nl < 0:
                end = len(text)
                break
            if text[max(0, nl - 2):nl].rstrip("\r").endswith("\\"):
                end = nl + 1
                continue
            end = nl
            break
        line = text[hash_at + 1:end]
        word = re.match(r"[ \t]*(\w*)", line)
        out.append((m.start(), end, word.group(1), line[word.end():]))
    return out


def _braces(text, mask, start, end):
    """'{' minus '}' among the code characters MASK keeps in text[start:end]."""
    return sum(1 if text[i] == "{" else -1 for i in range(start, end) if mask[i] and text[i] in "{}")


def _preprocessor_scope_refusal(text, code_mask, scope_mask, directives, last, rel):
    """Why preprocessing before LAST (the last declaration or use of the class) can change
    which scope it is in, or None. Conditions are never evaluated and macros never expanded:
    a conditional branch whose braces do not balance within it, or a macro whose replacement's
    braces do not balance and that is used before LAST, refuses the file. A balanced macro
    cannot leave a scope open around later text, whatever keywords it holds; one that expands
    to a scope head with no brace (`#define OPEN namespace Other`) leaves its literal brace to
    the tracker, which classes that block as unknown, never file scope."""
    stack, line_of = [], lambda pos: text.count("\n", 0, pos) + 1
    for start, end, word, _ in directives:
        if word in ("if", "ifdef", "ifndef"):
            stack.append(end)
        elif word in ("elif", "else", "endif"):
            if not stack:
                return f"{rel}: #{word} at line {line_of(start)} has no #if"
            branch = stack.pop()
            if branch < last and _braces(text, scope_mask, branch, start):
                return (f"{rel}: braces do not balance inside the conditional branch ending at line "
                        f"{line_of(start)}, before the declaration; its scope cannot be resolved")
            if word != "endif":
                stack.append(end)
    if stack:
        return f"{rel}: an #if is never closed; no declaration's scope can be resolved"
    for start, end, word, body in directives:
        if word != "define" or start >= last:
            continue
        macro = re.match(r"\s*(\w+)(\([^)]*\))?(.*)", body, re.S)
        if not macro:
            continue
        replacement = macro.group(3)
        if replacement.count("{") == replacement.count("}"):
            continue
        for use in re.finditer(r"\b" + re.escape(macro.group(1)) + r"\b", text[:last]):
            if scope_mask[use.start()]:
                return (f"{rel}: macro {macro.group(1)} (line {line_of(start)}) has unbalanced braces and is used "
                        f"at line {line_of(use.start())}, before the declaration; its scope cannot be resolved")
    return None


def _scope_at(events, position):
    """The scope stack in force at POSITION, without the transparent linkage blocks."""
    import bisect
    k = bisect.bisect_left(events, (position, ())) - 1
    return tuple(s for s in (events[k][1] if k >= 0 else ()) if s != "linkage")


def _rekey_source(text, rel, name, key, rekeyer):
    """(new text, [declaration edits]) for one Code/ file; RekeyRefused on a shape it cannot carry."""
    old_kw = "struct" if key == "class" else "class"
    spans = _lex(text)
    code_mask = [False] * len(text)
    for kind, a, b in spans:
        if kind == "code":
            code_mask[a:b] = [True] * (b - a)
    edits = []        # (start, end, replacement)
    decls = []
    for kind, a, b in spans:
        piece = text[a:b]
        if kind == "string":
            new = rekeyer.text(piece, rel, identity=True)
        elif kind == "comment":
            new = rekeyer.text(piece, rel, identity=bool(REKEY_MARKER.search(piece)))
        else:
            new = piece
        if new != piece:
            edits.append((a, b, new))
    # Only the global class changes. A declaration or definition of NAME inside a namespace,
    # class or function body is another class (N::NAME, Outer::NAME, a local class): it is
    # left as written and reported. An elaborated use (`const struct NAME *p`) names the
    # global class only when no namespace encloses it and the file declares no other NAME;
    # otherwise it is ambiguous and refuses.
    # Braces on preprocessor lines are no scope by themselves; the checks below refuse the
    # file when preprocessing could move a declaration into or out of one.
    directives = _pp_directives(text, code_mask)
    scope_mask = list(code_mask)
    for start, end, _, _ in directives:
        scope_mask[start:end] = [False] * (end - start)
    scopes = _brace_scopes(text, scope_mask, rel)
    found = []
    for match in re.finditer(r"\b" + old_kw + r"(\s+)" + re.escape(name) + r"\b", text):
        if not code_mask[match.start()]:
            continue
        j = match.end()
        while j < len(text) and (text[j].isspace() or not code_mask[j]):
            j += 1
        nxt = text[j:j + 2]
        friend = re.search(r"\bfriend\s*$", text[max(0, match.start() - 40):match.start()])
        declares = not friend and (nxt[:1] in ("{", ";") or (nxt[:1] == ":" and nxt != "::"))
        if not scope_mask[match.start()]:
            raise RekeyRefused(f"{rel}: `{old_kw} {name}` inside a preprocessor directive at line "
                               f"{text.count(chr(10), 0, match.start()) + 1}; its scope cannot be resolved")
        found.append((match, j, nxt, declares, _scope_at(scopes, match.start())))
    if found:
        why = _preprocessor_scope_refusal(text, code_mask, scope_mask, directives,
                                          max(m.start() for m, *_ in found), rel)
        if why:
            raise RekeyRefused(why)
    other_scope = [m for m, _, _, declares, scope in found if declares and scope]
    for match, j, nxt, declares, scope in found:
        if declares and scope:
            rekeyer.other_scope.append(f"{rel}: {old_kw} {name} inside {'/'.join(scope)} (another class; left)")
            continue
        if not declares and scope and ("namespace" in scope or "unknown" in scope or other_scope):
            raise RekeyRefused(f"{rel}: `{old_kw} {name}` inside {'/'.join(scope)} cannot be resolved to the "
                               f"global class (a namespace or an unclassified block encloses it, or the file "
                               f"declares another {name})")
        replacement = key + match.group(1) + name
        if nxt[:1] in ("{", ":") and nxt != "::":
            brace = j
            if nxt[:1] == ":":
                end = text.find("{", j)
                bases = text[j + 1:end].strip() if end > 0 else ""
                if end < 0 or "," in bases or not re.fullmatch(r"(?:(public|protected|private)\s+)?[\w:]+", bases):
                    raise RekeyRefused(f"{rel}: {old_kw} {name} has a base clause this writer cannot carry: {bases!r}")
                if key == "class" and not bases.startswith(("public", "protected", "private")):
                    edits.append((j, end, ": public " + bases + " "))
                brace = end
            line_end = text.find("\n", brace)
            rest = text[brace + 1:line_end if line_end >= 0 else len(text)].strip()
            access = "public:" if key == "class" else ""
            if access:
                eol = "\r\n" if text[brace + 1:brace + 3] == "\r\n" else "\n"
                edits.append((brace, brace + 1, "{ " + access if rest else "{" + eol + access))
            decls.append("definition")
        else:
            decls.append("declaration")
        edits.append((match.start(), match.end(), replacement))
    edits.sort()
    for (a1, b1, _), (a2, _b2, _) in zip(edits, edits[1:]):
        if a2 < b1:
            raise RekeyRefused(f"{rel}: overlapping edits at {a1}..{b1} and {a2}")
    out, last = [], 0
    for a, b, new in edits:
        out.append(text[last:a])
        out.append(new)
        last = b
    out.append(text[last:])
    return "".join(out), decls


def _csv_rewrite(raw, rel, rekeyer):
    """Respell tokens in a ledger CSV/TSV in place, byte for byte elsewhere. A token that is
    a row's identity (its name column, or a notes `parent=`/`icf-owner=`... value) refuses
    when unresolvable; any other (prose) token is rewritten if it resolves, else left."""
    text = raw.decode("utf-8-sig")
    delimiter = "\t" if rel.endswith(".tsv") else ","
    column = REKEY_NAME_COLUMNS.get(rel)
    identities = set()
    for row in csv.DictReader(io.StringIO(text), delimiter=delimiter):
        if column and row.get(column):
            identities.add(row[column])
        for value in row.values():
            if value and "=" in value:
                for m in REKEY_NOTE_KEYS.finditer(value):
                    identities.update(_t for _s, _t in _split_tokens(m.group(1)))
    out, last = [], 0
    for start, token in _split_tokens(text):
        new = rekeyer.one(token, rel, identity=token in identities)
        if new != token:
            out += [text[last:start], new]
            last = start + len(token)
    out.append(text[last:])
    new = "".join(out)
    if new == text:
        return raw
    bom = bytes((0xEF, 0xBB, 0xBF))
    return (bom if raw.startswith(bom) else b"") + new.encode("utf-8")


def _addresses(rows, name_col, address_col):
    out = collections.defaultdict(set)
    for row in rows:
        value = (row.get(address_col) or "").strip()
        if value:
            out[row[name_col]].add(int(value, 16))
    return out


def plan_class_key(name, key, root=None):
    """The whole migration as {rel: new bytes} plus its report; RekeyRefused before any write."""
    root = Path(root or ROOT)
    other = "U" if key == "class" else "V"
    registry = {r["class"]: r for r in csv.DictReader(io.StringIO(
        (root / "reverse/canonical_classes.csv").read_text(encoding="utf-8")))}
    if name not in registry:
        raise RekeyRefused(f"{name} is not a registered class")
    header = registry[name]["header"]
    contract_rel = f"reverse/class_contracts/{name}.json"
    contract = json.loads((root / contract_rel).read_text(encoding="utf-8"))
    exported = class_contract.export_key(name)
    if set(exported) != {key}:
        raise RekeyRefused(f"retail's exports decide {dict(exported) or 'nothing'} for {name}, not {key} alone")
    if contract["key"] == key:
        raise RekeyRefused(f"{contract_rel} already says {key}")
    rekeyer = _Rekeyer(name, other)
    hatch_tokens = []
    files = subprocess.run(["git", "-C", str(root), "ls-files", "-z", "Code", "reverse", "reference/shims"],
                           capture_output=True, check=True).stdout.decode("utf-8").split("\0")
    after, decls, refusals = {}, collections.Counter(), []
    for rel in files:
        if not rel:
            continue
        path = root / rel
        if rel.startswith(("Code/", "reference/shims/")):
            # A shim edit runs the full gate; the header's own dependents already do.
            if rel.startswith(("Code/gen_asm/", "Code/gen_small/uw_gen_")) or "/vendor/" in rel:
                # never edited here: refuse only when it spells NAME with the old key (a comment
                # that mentions the class is no spelling)
                hits = [t for _, t in _split_tokens(path.read_text(encoding="utf-8", errors="replace"))
                        if _rekey_changes(t, rekeyer)]
                if hits:
                    refusals.append(f"{rel}: a generated or vendored file spells {name} with the old key "
                                    f"({hits[0][:90]}); its owner tool must change it")
                continue
            if not rel.endswith(REKEY_CODE_SUFFIXES):
                continue
            raw = path.read_bytes()
            if name.encode() not in raw:
                continue
            text = raw.decode("utf-8", errors="surrogateescape")
            try:
                new, kinds = _rekey_source(text, rel, name, key, rekeyer)
            except RekeyRefused as err:
                refusals.append(str(err))
                continue
            decls.update(kinds)
            if new != text:
                after[rel] = new.encode("utf-8", errors="surrogateescape")
            continue
        raw = path.read_bytes() if path.is_file() else b""
        if name.encode() not in raw:
            continue
        if rel in REKEY_NAME_COLUMNS:
            new = _csv_rewrite(raw, rel, rekeyer)
        elif rel in REKEY_IDENTITY_FILES or rel in REKEY_PROSE_FILES:
            new = rekeyer.text(raw.decode("utf-8"), rel, identity=rel in REKEY_IDENTITY_FILES).encode("utf-8")
        elif rel.startswith("reverse/class_contracts/") and rel.endswith(".json") and rel != contract_rel:
            new = rekeyer.text(raw.decode("utf-8"), rel, identity=False).encode("utf-8")
        elif rel == "reverse/hatch_baseline.tsv":
            # Written by hatch_counters --update after the sources (rule 11), never here.
            hatch_tokens = _register_hatch_tokens(raw.decode("utf-8"), rekeyer)
            continue
        elif rel == "reverse/data_converged.csv":
            hits = [t for _, t in _split_tokens(raw.decode("utf-8")) if _rekey_changes(t, rekeyer)]
            if hits:
                refusals.append(f"{rel}: converged names are never renamed ({hits[0][:90]})")
            continue
        else:
            continue
        if new != raw:
            after[rel] = new
    # dup_defs baseline: keys respelled through dup_defs' own total-keeping writer.
    import dup_defs
    base_rel = "reverse/dup_defs_baseline.tsv"
    base_raw = (root / base_rel).read_bytes()
    base_map = {}
    for _, token in _split_tokens(base_raw.decode("utf-8")):
        new = rekeyer.one(token, base_rel, identity=True)
        if new != token:
            base_map[token] = new
    if base_map:
        try:
            after[base_rel] = dup_defs.rekey_baseline_text(base_raw.decode("utf-8"), base_map).encode("utf-8")
        except ValueError as err:
            refusals.append(f"{base_rel}: {err}")
    # The contract and its generated header line.
    # The contract changes by text, not re-serialized: only its key, its rule, and the
    # mangled names in it (its method declarations name their rows).
    old_key = contract["key"]
    ctext = (root / contract_rel).read_bytes().decode("utf-8")
    fields = re.compile(r'(\n "key": )"' + old_key + r'",(\r?\n "key_by": )"' + re.escape(contract["key_by"]) + '",')
    if len(fields.findall(ctext)) != 1:
        refusals.append(f"{contract_rel}: no single top-level key/key_by pair to respell")
    else:
        ctext = fields.sub(lambda m: f'{m.group(1)}"{key}",{m.group(2)}"exports",', ctext)
        after[contract_rel] = rekeyer.text(ctext, contract_rel, identity=True).encode("utf-8")
        if json.loads(after[contract_rel])["key"] != key:
            refusals.append(f"{contract_rel}: the respelled contract does not parse to key {key}")
    head = after.get(header, (root / header).read_bytes()).decode("utf-8")
    line = re.compile(r"(// sizeof [^\n]*; class-key )" + old_key + r" \([^)\n]*\)\.")
    if len(line.findall(head)) != 1:
        refusals.append(f"{header}: no single generated class-key line to respell")
    else:
        after[header] = line.sub(lambda m: m.group(1) + f"{key} (exports).", head).encode("utf-8")
    refusals += [f"unresolvable identity {t[:110]} ({why})" for t, why in sorted(rekeyer.refused.items())]
    refusals += _rekey_collisions(root, after, rekeyer.mapping)
    donor_units, unverified = _rekey_donor_units(root, name, key)
    for rel, why in sorted(unverified.items()):
        refusals.append(f"unverified: {rel}: {why}; rebuild it so its receipt shows whether it compiles a donor {name}")
    for rel, (donors, spelled) in sorted(donor_units.items()):
        if spelled:
            refusals.append(f"donor {name}: {rel} compiles {name} from {donors[0]}, which the rekey cannot edit, "
                            f"and its object spells the old key ({len(spelled)} name(s), e.g. {spelled[0][:90]}); "
                            f"move it to {header} or a TU-scoped shim first")
    if refusals:
        raise RekeyRefused("\n".join(refusals))
    after = _drop_redundant_pins(root, after, rekeyer.mapping)
    donors = sorted(donor_units)
    after = _carry_and_tiers(root, after, rekeyer, f"{name} {old_key} -> {key}")
    return after, {"class": name, "key": key, "from": old_key, "header": header, "files": sorted(after),
                   "mapping": rekeyer.mapping, "declarations": dict(decls),
                   "export_tier_gains": getattr(rekeyer, "export_gains", []),
                   "other_scope_declarations": rekeyer.other_scope,
                   "shims": sorted(r for r in after if r.startswith("reference/shims/")),
                   "hatch_tokens": hatch_tokens,
                   "donor_header_units": donors,
                   "prose_left": rekeyer.prose_left, "left_alone": REKEY_LEFT_ALONE}


def _ledger_dicts(root, after, rel):
    raw = after.get(rel) or ((root / rel).read_bytes() if (root / rel).is_file() else b"")
    return list(csv.DictReader(io.StringIO(raw.decode("utf-8-sig"))))


def _rekey_collisions(root, after, mapping):
    """Respelled names that would name more than one address (rows, pins and data rows
    together; the byte gate accepts a pin as an extra candidate, a real link gives a name one
    body, so an old spelling that already had two addresses refuses too), or land on a
    tombstone."""
    sides = (("reverse/functions.csv", "name", "target_rva"), ("reverse/symbols.csv", "name", "address"),
             ("reverse/data_rows.csv", "name", "address"))
    before, later = collections.defaultdict(set), collections.defaultdict(set)
    for rel, col, at in sides:
        for n, rvas in _addresses(_ledger_dicts(root, {}, rel), col, at).items():
            before[n] |= rvas
        for n, rvas in _addresses(_ledger_dicts(root, after, rel), col, at).items():
            later[n] |= rvas
    out = []
    for new in sorted(set(mapping.values())):
        if len(later.get(new, ())) > 1:
            olds = sorted(o for o, n in mapping.items() if n == new)
            out.append(f"collision: {new[:110]} would name "
                       f"{', '.join(f'0x{r:08X}' for r in sorted(later[new]))} (from {olds[0][:80]})")
    tomb_before = {r["name"] for r in _ledger_dicts(root, {}, "reverse/deleted_rows.csv")}
    live_before = set(before)
    for new in sorted(set(mapping.values()) & tomb_before):
        if new in later and new not in live_before:
            out.append(f"tombstone: {new[:110]} is in reverse/deleted_rows.csv")
    return out


def _drop_redundant_pins(root, after, mapping):
    """A pin the respelling makes equal to a row's own name at the same address is dropped
    (only those: an older redundant pin is not this migration's to remove)."""
    rel = "reverse/symbols.csv"
    respelled = set(mapping.values())
    rows = _addresses(_ledger_dicts(root, after, "reverse/functions.csv"), "name", "target_rva")
    raw = (after.get(rel) or (root / rel).read_bytes()).decode("utf-8-sig")
    lines = raw.splitlines(keepends=True)
    keep, seen, dropped = [lines[0]], set(), 0
    for line, rec in zip(lines[1:], csv.DictReader(io.StringIO(raw))):
        at = int(rec["address"], 16) if rec["address"].strip() else None
        if rec["name"] in respelled and (at in rows.get(rec["name"], ()) or (rec["name"], at) in seen):
            dropped += 1
            continue
        seen.add((rec["name"], at))
        keep.append(line)
    return {**after, rel: "".join(keep).encode("utf-8")} if dropped else after


def _carry_and_tiers(root, after, rekeyer, subject):
    """name_basis.csv binds a name's tier by its spelling, so every record whose spelling
    the migration changes gets an appended `carry` record (rename.py's own mechanism,
    never an edit of history). The tiers tools/allowed_symbols.py derives must then be
    today's, respelled: any other tier change refuses. reverse/name_tiers.csv itself is
    left to its owner (`allowed_symbols.py --tiers`), since the gate checks it only when
    staged and the committed file may already lag the tool."""
    import allowed_symbols
    import rename
    import tempfile
    ctx = rename.Context(root, object_scan=False)
    lines = []
    for spelling, row in rename.current_records(ctx).items():
        if spelling in rekeyer.mapping:
            lines.append(rename.csv_line(["carry", spelling, rekeyer.mapping[spelling], row.get("basis", ""),
                                          f"class-key respelled by {subject} (retail exports)",
                                          row.get("source", ""), row.get("rva", "")]))
    basis_rel = "reverse/name_basis.csv"
    if lines:
        after = {**after, basis_rel: rename.appended(ctx.read(basis_rel), lines, header=rename.NAME_BASIS_HEADER)}

    def tiers(files):
        # The rows `allowed_symbols.py --tiers` reads (link_census.ledger): matched, with an address.
        rows = [r for r in _ledger_dicts(root, files, "reverse/functions.csv")
                if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")]
        with tempfile.TemporaryDirectory() as tmp:
            basis = Path(tmp) / "name_basis.csv"
            basis.write_bytes(files.get(basis_rel) or ctx.read(basis_rel) or b"")
            return allowed_symbols.tiers_text(rows, allowed_symbols.Bases(basis))

    expected = rekeyer.text(tiers({}), "tiers (before)", identity=False)
    generated = tiers(after)
    lost = sorted(set(expected.splitlines()) - set(generated.splitlines()))
    gained = sorted(set(generated.splitlines()) - set(expected.splitlines()))
    # A respelled name that now IS retail's export gains that evidence; nothing else may move.
    other = [g for g in gained if not g.endswith(",evidence,export")]
    if lost or other:
        raise RekeyRefused(f"name tiers: the respelling changes tiers beyond the names: "
                           f"{len(lost)} line(s) lost (e.g. {lost[:2]}), {len(other)} gained (e.g. {other[:2]})")
    rekeyer.export_gains = [g for g in gained if g not in other]
    return after


def _rekey_claims(root, rels, name):
    """Touched paths (and the class) this worker does not hold, failing closed."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return []
    import claims
    me = claims.owner(root)
    held = claims.active(root)
    wanted = [("class:" + name, claims.class_key(name))] + [("file:" + r, claims.file_key(r)) for r in rels]
    return [label for label, k in wanted if (held.get(k) or {}).get("owner") != me]


def _report_path(report):
    """REPORT as a Path that is safe to write: under build/ (untracked scratch) or outside the
    repository, never a tracked file. RekeyRefused otherwise, before anything is written. The
    check is lexical on the resolved path (symlinks followed); it was not verified on a
    case-insensitive mount."""
    path = Path(report).resolve()
    inside = path == ROOT.resolve() or ROOT.resolve() in path.parents
    if inside and (ROOT / "build").resolve() not in path.parents:
        raise RekeyRefused(f"--report {report}: write reports under build/ or outside the repository")
    if inside and subprocess.run(["git", "-C", str(ROOT), "ls-files", "--error-unmatch", "--", str(path)],
                                 capture_output=True).returncode == 0:
        raise RekeyRefused(f"--report {report} is a tracked file")
    return path


def apply_class_key(name, key, dry_run=False, report=None):
    """Plan and (unless DRY_RUN) apply the migration. Not a round trip: the reverse key is
    refused while retail's exports decide this one, and the inserted `public:` lines stay; a
    second run refuses (the contract already says KEY). A run killed by a signal or power
    loss leaves rename.py's journal: `python3 tools/rename.py recover` restores the tree."""
    import rename
    report_path = _report_path(report) if report else None
    ctx = rename.Context(ROOT, object_scan=False)
    rename.refuse_pending_journal(ctx)
    after, summary = plan_class_key(name, key)
    hatches = "reverse/hatch_baseline.tsv"
    written = sorted([*after, *([hatches] if summary["hatch_tokens"] else [])])
    summary["written"] = written
    if report_path:
        report_path.parent.mkdir(parents=True, exist_ok=True)
        report_path.write_text(json.dumps(summary, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    print(f"class-key {name}: {summary['from']} -> {key}: {len(after)} file(s), "
          f"{len(summary['mapping'])} name(s) respelled, declarations {summary['declarations']}, "
          f"{len(summary['prose_left'])} prose token(s) left as written")
    for shim in summary["shims"]:
        print(f"  shim rewritten: {shim}")
    for line in summary["other_scope_declarations"]:
        print(f"  left: {line}")
    if summary["hatch_tokens"]:
        print(f"  {len(summary['hatch_tokens'])} hatch token(s) respelled; hatch_counters --update moves their lines (rule 11)")
    if summary["donor_header_units"]:
        print(f"  {len(summary['donor_header_units'])} unit(s) reach a donor {name}; their objects spell no old key "
              f"(harmless as built): {', '.join(summary['donor_header_units'][:8])}")
    if dry_run:
        return 0
    missing = _rekey_claims(ROOT, written, name)
    if missing:
        raise RekeyRefused(f"{len(missing)} claim(s) not held by this worker, e.g. {', '.join(missing[:5])}")
    plan = rename.Plan(kind="class-key", old=f"{name} {summary['from']}", new=f"{name} {key}",
                       basis="exports", evidence="reverse/exports.csv", source=summary["header"], rva=0)
    plan.before = {rel: ctx.read(rel) for rel in written}
    journal = rename.write_journal(ctx, plan)
    try:
        for rel, data in after.items():
            ctx.path(rel).write_bytes(data)
        if summary["hatch_tokens"]:
            # rule 11 moves each respelled hatch token's register line and lists it; any
            # other growth exits nonzero and everything above is restored
            import hatch_counters
            hatch_counters.update()
    except BaseException:
        rename.restore(ctx, plan.before)
        journal.unlink()
        raise
    journal.unlink()
    return 0


def scan_old_key(name, key, objects):
    """{object: [old-key or unresolvable names]} over OBJECTS (paths): every mangled token in an
    object's bytes (symbol table, .drectve directives, debug records) that still spells NAME
    with the other key, or spells NAME and cannot be resolved. A missing object is a finding:
    the flip is complete only when every rebuilt object is read and none spells the old key."""
    other = "U" if key == "class" else "V"
    scope = class_contract.mangled_scope(name)
    found = {}
    for obj in objects:
        path = Path(obj)
        if not path.is_file():
            found[str(obj)] = ["(object missing)"]
            continue
        bad = set()
        for match in REKEY_TOKEN.finditer(path.read_bytes().decode("latin-1")):
            token = match.group()
            if not _rekey_relevant(token, name):
                continue
            try:
                if rekey_symbol(token, scope, other, allow_mixed=True) != token:
                    bad.add(token)
            except Exception:
                bad.add(token + "  (unresolvable)")
        if bad:
            found[str(obj)] = sorted(bad)
    return found


def rekey_scan(name, key, sources_from=None):
    """The flip's completion check over the objects of the ledger's matched sources (or the
    sources listed one per line in SOURCES_FROM): exit 1 and list them when any object is
    missing or still spells NAME with the old key. It reads the objects as they are and does
    not establish that they are fresh: the trial must rebuild them first."""
    import build
    if sources_from:
        sources = [s for s in Path(sources_from).read_text(encoding="utf-8").split() if s]
    else:
        with LEDGER.open(newline="", encoding="utf-8") as handle:
            sources = sorted({r["source"] for r in csv.DictReader(handle) if r.get("status") == "matched"})
    objects = [build.obj_path(ROOT / s) for s in sources]
    found = scan_old_key(name, key, objects)
    for obj, names in sorted(found.items()):
        print(f"{obj}: {len(names)} old-key name(s), e.g. {names[0][:150]}")
    print(f"rekey-scan {name} -> {key}: {len(objects)} object(s), {len(found)} with an old-key spelling or missing")
    return 1 if found else 0


def key_backref_blockers(sources, name, key):
    """{source: why} for units a class-key change cannot rename, read in one ledger pass."""
    _, other = ("U", "V") if key == "struct" else ("V", "U")
    scope = class_contract.mangled_scope(name)
    rows = collections.defaultdict(list)
    wanted = set(sources)
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["source"] in wanted:
                rows[row["source"]].append(row)
    blockers = {}
    for source in sources:
        blocked = key_backref_names(rows.get(source, []), scope, other)
        if blocked:
            blockers[source] = (f"class-key: {len(blocked)} row(s) cannot be safely resolved "
                                f"for a type-key rewrite: "
                                f"{', '.join(sorted(blocked)[:3])}")
    return blockers


def ledger_renames(source, name, want_key):
    """([(old, new)], why) for the unit's row names that mangle the other class-key."""
    _, other = ("U", "V") if want_key == "struct" else ("V", "U")
    scope = class_contract.mangled_scope(name)
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        rows = [r for r in csv.DictReader(handle) if r["source"] == source]
    renames, blocked = _key_renames(rows, scope, other)
    if blocked:
        return [], (f"{len(blocked)} row(s) cannot be safely resolved for a class-key rewrite: "
                    f"{', '.join(sorted(blocked)[:3])}")
    metadata = key_metadata_blockers([(source, None, None, renames)])
    if metadata:
        return [], metadata[source]
    return renames, None


def rewrite_ledger(renames):
    if not renames:
        return
    blocked = key_metadata_blockers([("ledger rewrite", None, None, renames)])
    if blocked:
        raise ValueError(blocked["ledger rewrite"])
    import ledger_io
    table = dict(renames)
    records = []
    for payload, terminator in ledger_io.split_records(LEDGER.read_bytes()):
        fields = ledger_io.fields(payload)
        if fields and fields[0] in table:
            old, new = fields[0].encode("utf-8"), table[fields[0]].encode("utf-8")
            if payload.startswith(old + b","):
                payload = new + payload[len(old):]
            elif payload.startswith(b'"' + old + b'",'):
                payload = b'"' + new + payload[len(old) + 1:]
            else:
                raise ValueError("unsupported CSV name spelling; ledger left unchanged")
        records.append(payload + terminator)
    LEDGER.write_bytes(b"".join(records))


FIELD_RENAMES = {}     # source -> {Class::private field: canonical field} of its last swap, for reports


def prospective_renames(sources, name, key):
    """Find class-key row changes without compiling/probing or writing a unit."""
    changed = set()
    for source in sources:
        span = body_span((ROOT / source).read_text(encoding="latin-1"), name)
        if span and span[2] != key:
            changed.add(source)
    if not changed:
        return []
    scope = class_contract.mangled_scope(name)
    _, other = ("U", "V") if key == "struct" else ("V", "U")
    per_source = collections.defaultdict(list)
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["source"] in changed:
                per_source[row["source"]].append(row)
    names = {}
    for source, rows in per_source.items():
        renames, blocked = _key_renames(rows, scope, other)
        if renames and not blocked:
            names[source] = renames
    return [(s, None, None, renames) for s, renames in names.items()]


def adoption_dependencies(items, rows=None, new_rows=None):
    """Read-only provider -> {lost name: consumers} for a coordinated adoption.

    Use the hook's resolver and current-object/source-text rules. Discovery is
    shared across all renames, includes data-only consumers, and never claims or
    edits a dependent. No symbol changes means no repository-wide scan.
    """
    renames = {old: new for _, _, _, names in items for old, new in names}
    if not renames or not BFME2:
        return {}
    import name_dependents as nd
    if rows is None:
        with LEDGER.open(newline="", encoding="utf-8") as handle:
            rows = list(csv.DictReader(handle))
    if new_rows is None:
        new_rows = [{**r, "name": renames.get(r["name"], r["name"])} for r in rows]
    with (ROOT / "reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        pins = list(csv.DictReader(handle))
    with (ROOT / "reverse/data_rows.csv").open(newline="", encoding="utf-8") as handle:
        data = list(csv.DictReader(handle))
    lost_calls = nd.lost_names(nd.call_targets(rows, pins), nd.call_targets(new_rows, pins))
    lost_data = nd.lost_names(nd.data_targets(rows, data), nd.data_targets(new_rows, data))
    references = {}
    lost = set(lost_calls) | set(lost_data)
    if lost:
        # A retained address pin can keep byte resolution working while the C++
        # provider's old linker name still disappears. Include provider-home
        # losses in the same scan, for both code and data-only consumers.
        data_objects = nd._data_row_objects(data)
        objects = nd._row_objects(rows)
        for source, paths in data_objects.items():
            objects.setdefault(source, []).extend(p for p in paths if p not in objects[source])
        references = nd.dependents_by_name(lost, objects, ROOT)
    plan = {}
    for source, _, _, names in items:
        for old, _ in names:
            if references.get(old, set()) - {source}:
                plan.setdefault(source, {})[old] = sorted(references[old] - {source})
    return plan


def dependency_blockers(plan, candidates):
    """Reject incomplete connected provider/caller groups, keeping unrelated work.

    An included caller must not survive when its renamed provider fails either.
    The same plan is reused after byte failures, held files and link refusals.
    """
    candidates = set(candidates)
    graph = collections.defaultdict(set)
    for provider, names in plan.items():
        for callers in names.values():
            for caller in callers:
                graph[provider].add(caller)
                graph[caller].add(provider)
    blocked, seen = {}, set()
    for source in graph:
        if source in seen:
            continue
        component, pending = set(), [source]
        while pending:
            node = pending.pop()
            if node in component:
                continue
            component.add(node)
            pending.extend(graph[node] - component)
        seen.update(component)
        missing = component - candidates
        if missing:
            why = ("symbol dependencies: coordinated adoption also requires " + ", ".join(sorted(missing))
                   + "; reconcile these callers/providers in the same verified batch")
            blocked.update(dict.fromkeys(component & candidates, why))
    return blocked


def acceptance_dependencies(sources):
    """Discover already-applied row renames too, before accepting/retiring debt."""
    if not BFME2 or not (ROOT / "reverse/functions.csv").is_file():
        return {}
    import name_dependents as nd
    raw = nd.git_bytes("HEAD:reverse/functions.csv", ROOT)
    if raw is None:
        raise RuntimeError("cannot read HEAD's function ledger")
    current_raw = LEDGER.read_bytes()
    if current_raw == raw:
        return {}  # Ordinary header-only adoption: no CSV parse or caller scan.
    before = nd.csv_dicts(raw.decode("utf-8-sig"))
    after = nd.csv_dicts(current_raw.decode("utf-8-sig"))
    old, current = collections.defaultdict(set), collections.defaultdict(set)
    wanted = set(sources)
    for rows, target in ((before, old), (after, current)):
        for row in rows:
            if row.get("status") == "matched" and row["source"] in wanted:
                target[row["source"], row["target_rva"]].add(row["name"])
    renamed = collections.defaultdict(list)
    for key, names in old.items():
        new_name = next(iter(sorted(current[key] - names)), "")
        renamed[key[0]].extend((prior, new_name) for prior in sorted(names - current[key]))
    items = [(s, None, None, names) for s, names in renamed.items() if names]
    return adoption_dependencies(items, before, after)


def prepare_unit(source, strip, header, key):
    """Prepare a swap without writing source/ledger files or running the byte gate."""
    path = ROOT / source
    original = path.read_bytes()
    text = original.decode("latin-1")
    span = body_span(text, strip[0])
    view_key = span[2] if span else key
    include = include_spelling(source, header)
    swapped = swap(text, strip, include)
    if swapped is None:
        return source, "no private view found", None, []
    fields, why = field_renames(source, text, strip, include, header=header)
    if why:
        return source, f"field renames: {why}", None, []
    if fields:
        swapped, why = scoped_rename(swapped, fields)
        if why:
            return source, f"field renames: {why}", None, []
        FIELD_RENAMES[source] = {f"{cls}::{old}": new for cls, m in fields.items() for old, new in m.items()}
    renames, why = ledger_renames(source, strip[0], key) if view_key != key else ([], None)
    if why:
        return source, f"class-key {view_key}: {why}", None, []
    if renames:
        return source, f"class-key {view_key}: {len(renames)} ledger rename(s) needed", swapped, renames
    return source, None, swapped, []


def try_unit(source, strip, header, key):
    """Prepare and verify one swap, restoring the source before returning."""
    result = prepare_unit(source, strip, header, key)
    _, why, swapped, renames = result
    if why:
        return result
    path = ROOT / source
    original = path.read_bytes()
    try:
        path.write_bytes(swapped.encode("latin-1"))
        why = gate_one(source)
    finally:
        path.write_bytes(original)
    return source, why, swapped, renames


def try_units(sources, strip, header, key, jobs=1, dependency_plan=None):
    """Trial a whole variant in one source/ledger state, always restoring both.

    Preparation errors remain per-file failures. Byte failures are isolated by
    gate_many; class-key renames share one temporary ledger instead of races.
    """
    sources = list(dict.fromkeys(sources))
    if not BFME2:
        with cf.ThreadPoolExecutor(jobs) as pool:
            got = list(pool.map(lambda s: try_unit(s, strip, header, key), sources))
        fixed = try_renamed([g for g in got if g[3]], jobs)
        return [(s, fixed.get(s, why), text, renames) for s, why, text, renames in got]
    try:
        prospective = prospective_renames(sources, strip[0], key)
        plan = adoption_dependencies(prospective)
    except (Exception, SystemExit) as exc:
        return [(s, f"symbol dependency discovery unavailable: {exc}", None, []) for s in sources]
    early = {**key_backref_blockers(sources, strip[0], key), **key_metadata_blockers(prospective),
             **dependency_blockers(plan, sources)}
    pending = [s for s in sources if s not in early]
    with cf.ThreadPoolExecutor(jobs) as pool:
        prepared = dict(zip(pending, pool.map(lambda s: prepare_unit(s, strip, header, key), pending)))
    got = [prepared[s] if s in prepared else (s, early[s], None, []) for s in sources]
    ready = [g for g in got if g[2] is not None and (g[1] is None or g[3])]
    try:
        predicted = {(s, old, new) for s, _, _, names in prospective for old, new in names}
        actual = {(s, old, new) for s, _, _, names in ready for old, new in names}
        if actual - predicted:
            # Recheck if preparation found an additional row change; a caller or
            # custom preparer must never bypass discovery by adding it late.
            for s, names in adoption_dependencies(ready).items():
                plan.setdefault(s, {}).update(names)
    except (Exception, SystemExit) as exc:
        why = f"symbol dependency discovery unavailable: {exc}"
        eligible = {g[0] for g in ready}
        return [(s, why if s in eligible else reason, text, names) for s, reason, text, names in got]
    if dependency_plan is not None:
        dependency_plan.update(plan)
    blocked = dependency_blockers(plan, [g[0] for g in ready])
    statuses = {s: why for s, why, _, _ in got}
    statuses.update(blocked)
    ready = [g for g in ready if g[0] not in blocked]
    originals = {s: (ROOT / s).read_bytes() for s, _, _, _ in ready}
    renames = [r for _, _, _, names in ready for r in names]
    backup = LEDGER.read_bytes() if renames else None
    try:
        active = list(ready)
        while active:
            if backup is not None:
                LEDGER.write_bytes(backup)
            active_renames = [r for _, _, _, names in active for r in names]
            rewrite_ledger(active_renames)
            for source, _, text, _ in active:
                (ROOT / source).write_bytes(text.encode("latin-1"))
            verdicts = gate_many([s for s, _, _, _ in active])
            statuses.update(verdicts)
            passed = {s for s, why in verdicts.items() if why is None}
            dropped = dependency_blockers(plan, passed)
            statuses.update(dropped)
            kept = [g for g in active if g[0] in passed and g[0] not in dropped]
            removed_renames = any(g[3] for g in active if g not in kept)
            for s, _, _, _ in active:
                if s not in passed or s in dropped:
                    (ROOT / s).write_bytes(originals[s])
            if not dropped and not removed_renames:
                break
            active = kept  # Reverify survivors if the temporary resolver changed.
        return [(s, statuses[s], text, names)
                for s, _, text, names in got]
    finally:
        for source, original in originals.items():
            (ROOT / source).write_bytes(original)
        if backup is not None:
            LEDGER.write_bytes(backup)


def try_renamed(items, jobs):
    """Units whose view spelled the other class-key: rename their ledger rows and gate,
    serially in one ledger state (the ledger is shared by all of them)."""
    results = {}
    if not items:
        return results
    backup = LEDGER.read_bytes()
    originals = {s: (ROOT / s).read_bytes() for s, _, _, _ in items}
    try:
        rewrite_ledger([r for _, _, _, renames in items for r in renames])
        for source, _, text, _ in items:
            (ROOT / source).write_bytes(text.encode("latin-1"))
        with cf.ThreadPoolExecutor(jobs) as pool:
            for source, why in zip([i[0] for i in items], pool.map(gate_one, [i[0] for i in items])):
                results[source] = why
    finally:
        for source, data in originals.items():
            (ROOT / source).write_bytes(data)
        LEDGER.write_bytes(backup)
    return results


def header_classes(header, seen=None):
    """Classes a header in the tree defines, with the headers it `#include "..."`s (transitively).

    Adopting a header replaces every private view of a class it brings in: a unit that
    keeps its own copy of a base the header also defines fails with C2011."""
    seen = set() if seen is None else seen
    path = (ROOT / header).resolve()
    if path in seen or not path.is_file():
        return []
    seen.add(path)
    text = path.read_text(encoding="latin-1")
    out = list(dict.fromkeys(class_layouts.class_bodies(text)))
    for include in INCLUDE.findall(COMMENTS.sub("", text)):
        target = (path.parent / include).resolve()
        try:
            rel = target.relative_to(ROOT.resolve()).as_posix()
        except ValueError:
            continue
        out += [c for c in header_classes(rel, seen) if c not in out]
    return out


def tournament(name, contract, sources, header, variants, jobs, fixed_header=False):
    strip = [name] + STRIP_WITH.get(name, [])
    known = registered()
    brought = header_classes(header) if fixed_header else [
        c for b in contract.get("bases", []) if base_identity(b) in known
        for c in header_classes(known[base_identity(b)])]
    strip += [c for c in brought if c not in strip]
    nested = {f["kind"][2:] for f in contract["fields"] if f["kind"].startswith("S:")} & set(registered())
    methods = view_methods(name, sources, nested) if not fixed_header else {}
    slots = None
    if not fixed_header and contract.get("vslots"):
        own, overrides, _ = slot_declarations(contract, sources)
        slots = (own, overrides)
    special = special_members(name, contract, sources, nested)[0] if not fixed_header else []
    results = {}
    keep = (ROOT / header).read_bytes() if (ROOT / header).exists() else None
    try:
        for variant in variants:
            if not fixed_header:
                (ROOT / header).parent.mkdir(parents=True, exist_ok=True)
                (ROOT / header).write_text(generate(contract, variant, methods, header, slots, special),
                                           encoding="utf-8", newline="\n")
            started = time.time()
            dependencies = {}
            got = try_units(sources, strip, header, contract["key"], jobs, dependency_plan=dependencies)
            verdicts = {s: why for s, why, _, _ in got}
            results[variant] = {"verdicts": verdicts, "texts": {s: t for s, _, t, _ in got},
                                "renames": {s: r for s, _, _, r in got if r}, "dependencies": dependencies,
                                "seconds": time.time() - started,
                                "header": (ROOT / header).read_text(encoding="utf-8") if (ROOT / header).exists() else ""}
            passes = sum(v is None for v in verdicts.values())
            print(f"  variant {variant:<14} {passes}/{len(sources)} pass  ({results[variant]['seconds']:.0f}s)", flush=True)
    finally:
        if not fixed_header:
            if keep is None:
                (ROOT / header).unlink(missing_ok=True)
            else:
                (ROOT / header).write_bytes(keep)
    return results


# ---------------------------------------------------------------- queue + acceptance

def failure_class(why):
    """Research 11's taxonomy, by first diagnostic."""
    code = re.search(r"error (C\d+)", why)
    if code:
        return code.group(1) + (" missing member" if code.group(1) in ("C2039", "C2661", "C2660") else "")
    if why.startswith("class-key"):
        return "class-key rename"
    if "FAIL" in why:
        return "bytes/callee identity"
    return why.split(":")[0][:40]


def acceptance_command(name, source):
    return f"python3 tools/header_adopt_lane.py accept --class {name} {source}"


def transfer_sources(gone, destination, queue=QUEUE):
    """Carry every absorbed source's adoption debt to its new TU, without retiring it.

    Keep individual rows and their original diagnostics/RVAs, even when several
    donors owe the same class adoption. Only `accept` can retire that debt.
    """
    queue = Path(queue)
    if not queue.exists():
        return 0
    with queue.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        cols, rows = reader.fieldnames, list(reader)
    gone, changed = set(gone), 0
    for row in rows:
        if row["source"] in gone:
            row["source"] = destination
            row["acceptance"] = acceptance_command(row["class"], destination)
            changed += 1
    if changed:
        tmp = queue.with_suffix(".tsv.tmp")
        with tmp.open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
        os.replace(tmp, queue)
    return changed


def write_queue(name, header, failures):
    rows = []
    if QUEUE.exists():
        with QUEUE.open(newline="", encoding="utf-8") as handle:
            rows = [r for r in csv.DictReader(handle, delimiter="\t") if r["class"] != name]
    rvas = collections.defaultdict(list)
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for r in csv.DictReader(handle):
            rvas[r["source"]].append(r["target_rva"])
    for source, why in sorted(failures.items()):
        rows.append({"class": name, "source": source, "retail_rvas": " ".join(sorted(rvas[source])[:4]),
                     "header": header, "failure": re.sub(r"\s+", " ", why)[:160], "retry_budget": "3",
                     "acceptance": acceptance_command(name, source)})
    cols = ["class", "source", "retail_rvas", "header", "failure", "retry_budget", "acceptance"]
    with QUEUE.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(rows, key=lambda r: (r["class"], r["source"])))


def registered():
    if not REGISTRY.exists():
        return {}
    with REGISTRY.open(newline="", encoding="utf-8") as handle:
        return {r["class"]: r["header"] for r in csv.DictReader(handle) if r.get("class")}


def register(name, header, note):
    if name in registered():
        return
    exists = REGISTRY.exists()
    with REGISTRY.open("a", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, lineterminator="\n")
        if not exists:
            writer.writerow(["class", "header", "notes"])
        writer.writerow([name, header, note])


def link_ok(sources):
    """Whether each ordinary preview preserves its census-linked bytes.

    A previously blocked unit may remain blocked (0 -> 0). Missing evidence,
    including a source merely mentioned in a compile error, is no verdict.
    This preview is a retirement guard, never a new census measurement.
    """
    if not sources:
        return {}
    if not (ROOT / "tools" / "link_check.py").exists():
        return {s: None for s in sources}
    done = subprocess.run([sys.executable, "tools/link_check.py", *sources], cwd=ROOT, capture_output=True,
                          text=True, errors="replace", env=dict(os.environ, MSYS_NO_PATHCONV="1"))
    if done.returncode not in (0, 1):
        return {s: None for s in sources}
    out = done.stdout + done.stderr
    normalize = lambda source: (ROOT / source).resolve().relative_to(ROOT.resolve()).as_posix()
    outside = re.search(r"^link_check: not in census [^\n]*?\(the next census measures it\): (.+)$", out, re.M)
    if outside:
        # link_check refuses the whole run when one unit is outside the census; that
        # unit has no verdict, and the others are judged as a run without it would be.
        outside = {name.strip() for name in outside.group(1).split(", ")}
        rest = [s for s in sources if normalize(s) not in outside]
        results = dict.fromkeys(sources, None)
        if rest and len(rest) < len(sources):
            results.update(link_ok(rest))
        return results
    results = {}
    for source in sources:
        normalized = normalize(source)
        matches = re.findall(r"^" + re.escape(normalized)
                             + r": (?:LINKS|does not link)  LINKED ([0-9]+(?:,[0-9]{3})*)"
                             + r" -> ([0-9]+(?:,[0-9]{3})*) bytes \(census [^\n]+\)$",
                             out, re.M)
        if len(matches) != 1:
            results[source] = None
        else:
            before, after = (int(n.replace(",", "")) for n in matches[0])
            results[source] = after >= before
    return results


COMMENTS = re.compile(r"//[^\n]*|/\*.*?(?:\*/|\Z)", re.S)
INCLUDE = re.compile(r"^[ \t]*#[ \t]*include[ \t]*[<\"]([^>\"\n]+)[>\"]", re.M)
DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*(\w+)(.*)$")

# These existing companions provide coordinate views needed by matched units.
# See each companion's evidence and docs/recipes.md. They take
# the canonical include guard instead of including the POD declaration. Keep
# exact class/header pairs: a filename suffix or a copied guard proves nothing.
HEADER_COMPANIONS = {
    ("Coord2D", "Code/Libraries/Include/Lib/Coord2D.h"):
        ("Code/Libraries/Include/Lib/Coord2DCtorView.h",),
    ("Coord3D", "Code/Libraries/Include/Lib/Coord3D.h"):
        ("Code/Libraries/Include/Lib/Coord3DCtorView.h",
         "Code/Libraries/Include/Lib/Coord3DDerivedView.h",
         "Code/Libraries/Include/Lib/Coord3DInline.h"),
}


def without_disabled(text):
    """`text` with every line of an `#if 0` branch blanked (its #else/#elif branch is
    kept): an #include there is never compiled."""
    out, depth, dead = [], 0, None              # dead: the depth of the #if 0 being skipped
    for line in text.split("\n"):
        m = DIRECTIVE.match(line)
        word = m[1] if m else ""
        if word in ("if", "ifdef", "ifndef"):
            depth += 1
            if dead is None and word == "if" and m[2].strip() in ("0", "(0)", "false"):
                dead = depth
        elif word in ("else", "elif") and dead == depth:
            dead = None
            line = ""
        elif word == "endif":
            if dead == depth:
                dead = None
                line = ""
            depth -= 1
        out.append("" if dead is not None else line)
    return "\n".join(out)


def tracked_headers():
    got = subprocess.run(["git", "ls-files", "-z", "--", "*.h", "*.hpp", "*.inl"], cwd=ROOT, capture_output=True)
    return [p.decode("utf-8", "replace") for p in got.stdout.split(b"\0") if p]


def compiler_include_target(source, spelled, quoted):
    """Resolve a direct include in compiler search order, or leave it unproved.

    This only builds the ordinary command; it never compiles into the match cache.
    Implicit CL options can change that order, so they cannot supply this proof.
    """
    import build
    try:
        path = ROOT / source
        command, env = build.compiler_command(path, build.obj_path(path))
        if env.get("CL") or env.get("_CL_"):
            return None
        roots = [path.parent] if quoted else []
        args = iter(command)
        for arg in args:
            if arg in ("/I", "-I"):
                root = next(args, None)
                if not root:
                    return None
            elif arg.startswith(("/I", "-I")) and len(arg) > 2:
                root = arg[2:]
            else:
                continue
            roots.append(root)
        if not any(arg.lower() in ("/x", "-x") for arg in command):
            roots.extend(root for root in env.get("INCLUDE", "").split(";") if root)
        for root in roots:
            raw = str(root)
            if os.name != "nt" and re.match(r"^[a-yA-Y]:", raw):
                return None                          # no proven host mapping for this drive
            host = build._host_path(raw)
            resolved = build._case_resolve(str(Path(host) / spelled)) if host else None
            if resolved and Path(resolved).is_file():
                return Path(resolved).resolve()
    except (OSError, RuntimeError, ValueError, SystemExit):
        return None
    return None


def includes_header(source, header):
    """Does `source` really #include `header`: a directive outside comments and `#if 0`
    branches whose spelling resolves beside the source to that file, or is a path
    suffix of it no other tracked header shares? An ambiguous suffix additionally
    needs the actual compiler search order to select this header. A basename in
    a comment, or a same-named header elsewhere, is not it."""
    text = without_disabled(COMMENTS.sub(lambda m: re.sub(r"[^\n]", " ", m.group()),
                                         (ROOT / source).read_text(encoding="latin-1")))
    header = header.replace("\\", "/")
    want = (ROOT / header).resolve()
    others = None
    directives = re.finditer(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^>"\n]+)[>"]', text, re.M)
    for directive in directives:
        quoted = directive.group(1) == '"'
        spelled = directive.group(2)
        spelled = spelled.strip().replace("\\", "/")
        beside = ((ROOT / source).parent / spelled).resolve()
        if quoted and beside.is_file():
            if beside == want:
                return True
            continue                                  # the adjacent header shadows every /I
        tail = "/" + spelled.lstrip("./")
        if ("/" + header).endswith(tail):
            if others is None:
                others = tracked_headers()
            if not [p for p in others if ("/" + p).endswith(tail) and p != header]:
                return True
            if compiler_include_target(source, spelled, quoted) == want:
                return True
    return False


def queued_text(name, source):
    """`source` as it stood in the commit that last added its (name, source) queue row
    (later commits may have retired it), or None when history shows neither."""
    try:
        rel, key = QUEUE.relative_to(ROOT).as_posix(), f"{name}\t{source}\t"
    except ValueError:                                          # a queue outside the repository
        return None
    log = subprocess.run(["git", "log", "--format=%H", "-S" + key, "--", rel],
                         cwd=ROOT, capture_output=True, text=True)
    for commit in (log.stdout.split() if log.returncode == 0 else ()):
        queue = subprocess.run(["git", "show", f"{commit}:{rel}"], cwd=ROOT, capture_output=True, text=True)
        if queue.returncode or not any(line.startswith(key) for line in queue.stdout.splitlines()):
            continue                                            # this commit removed the row
        text = subprocess.run(["git", "show", f"{commit}:{source}"], cwd=ROOT, capture_output=True)
        return text.stdout.decode("latin-1") if text.returncode == 0 else None
    return None


def misclassified(name, source, queued=None, layouts=None):
    """Was the (name, source) row a discovery error, owing no include? Only when the unit
    declared no namespace-scope body of `name` in the commit that queued it (so no view
    renamed since can pass) and its compiled types hold no global `name`, not even a
    forward reference (it never uses the class). Any missing evidence is a no."""
    old = (queued or queued_text)(name, source)
    if old is None or name in class_layouts.class_bodies(old):
        return False
    try:
        found = (layouts or class_layouts.compile_layouts)(source)
    except (OSError, RuntimeError):
        return False
    return name not in found


def adoption_problems(name, source, header=None, gate=None):
    """[problems] of one unit's adoption of `name`'s canonical header ([] = adopted, or
    a proven misclassified row: see misclassified)."""
    header = header or registered().get(name)
    if not (ROOT / source).exists():
        return [f"{source} does not exist"]
    if not header or not (ROOT / header).exists():
        return [f"{name}'s canonical header {header or '(unregistered)'} does not exist"]
    problems = []
    if name in class_layouts.class_bodies((ROOT / source).read_text(encoding="latin-1")):
        problems.append("still declares a private body")
    companions = HEADER_COMPANIONS.get((name, header), ())
    if not (includes_header(source, header) or
            any((ROOT / companion).is_file() and includes_header(source, companion)
                for companion in companions) or
            (not problems and misclassified(name, source))):
        problems.append(f"does not #include {header}")
    why = (gate or gate_one)(source)
    if why:
        problems.append(why)
    return problems


def verdict(name, source, header=None, gate=None):
    """Structural, byte and link verdict for one adoption (legacy single-unit API)."""
    problems = adoption_problems(name, source, header, gate)
    if not problems:
        linked = link_ok([source])[source]
        if linked is False:
            problems.append("link_check predicts a loss of census-linked bytes")
        elif linked is None:
            problems.append("link_check produced no usable per-unit verdict")
    return problems


def retire_rows(done):
    """Remove the (class, source) rows in `done` from the queue, atomically; the count."""
    if not done or not QUEUE.exists():
        return 0
    with QUEUE.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        cols, rows = reader.fieldnames, list(reader)
    kept = [r for r in rows if (r["class"], r["source"]) not in done]
    tmp = QUEUE.with_suffix(".tsv.tmp")
    with tmp.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(kept)
    os.replace(tmp, QUEUE)
    return len(rows) - len(kept)


def accept(name, sources, header=None, gate=None):
    """Judge each unit (verdict) and retire every passing unit's queue row: the row
    leaves only on this verdict, never by a hand deletion."""
    sources = list(dict.fromkeys(sources))
    try:
        dependencies = acceptance_dependencies(sources)
        blocked = dependency_blockers(dependencies, sources)
    except (Exception, SystemExit) as exc:
        blocked = dict.fromkeys(sources, f"symbol dependency discovery unavailable: {exc}")
    if blocked:
        for source, why in blocked.items():
            print(f"  FAIL {source}: {why}")
        remaining = [s for s in sources if s not in blocked]
        if remaining:
            accept(name, remaining, header, gate)
        return 1
    judged = None
    if len(sources) > 1:
        builds = {s: gate(s) for s in sources} if gate else gate_many(sources)
        judged = {s: adoption_problems(name, s, header, lambda s: builds[s]) for s in sources}
        # Refresh every byte-passing object together, including structurally rejected
        # ones: they may still provide symbols to an accepted member of the cohort.
        linked = link_ok([s for s in sources if builds[s] is None])
        for source, problems in judged.items():
            if not problems:
                if linked.get(source) is False:
                    problems.append("link_check predicts a loss of census-linked bytes")
                elif linked.get(source) is not True:
                    problems.append("link_check produced no usable per-unit verdict")
        accepted = [s for s, problems in judged.items() if not problems]
        for source, why in dependency_blockers(dependencies, accepted).items():
            judged[source].append(why)
    bad, done = 0, set()
    for source in sources:
        problems = judged[source] if judged is not None else verdict(name, source, header, gate)
        print(f"  {'PASS' if not problems else 'FAIL'} {source}" + ("" if not problems else ": " + "; ".join(problems)))
        bad |= bool(problems)
        if not problems:
            done.add((name, source))
    retired = retire_rows(done)
    if retired:
        print(f"  retired {retired} row(s) from {QUEUE.relative_to(ROOT).as_posix()}; commit it with the adoption")
    return bad


def adopt(name, header, sources, apply=False, jobs=1):
    """Adopt `header` in the given units without registering `name`: staged adoption for a
    class whose merge donors still mostly carry private views (registering would make
    class_gate refuse their merges). Each unit is swapped as the tournament swaps it, field
    renames included, and must byte-match; --apply writes the passing units (and the ledger
    rows a class-key change renames). Claim the units first (docs/claims.md). Returns the
    number of units that fail."""
    if not (ROOT / header).is_file():
        raise SystemExit(f"{header}: no such header")
    span = body_span((ROOT / header).read_text(encoding="latin-1"), name)
    if not span:
        raise SystemExit(f"{header} does not define {name}")
    strip = [name] + STRIP_WITH.get(name, [])
    strip += [c for c in header_classes(header) if c not in strip]
    got = try_units(sources, strip, header, span[2], jobs)
    failed = 0
    for source, why, text, renames in got:
        fields = FIELD_RENAMES.get(source, {})
        print(f"  {'PASS' if why is None else 'FAIL'} {source}" + (f": {why}" if why else "")
              + (" (fields: " + ", ".join(f"{a} -> {b}" for a, b in sorted(fields.items())) + ")" if fields else ""))
        failed += why is not None
        if why is None and apply:
            (ROOT / source).write_bytes(text.encode("latin-1"))
            rewrite_ledger(renames)
    return failed


def closure_diff(before, after):
    def closed(path):
        with open(path, newline="", encoding="utf-8") as handle:
            return {(r["name"], r["retail_rva"]): r["closed_strict"] == "1" for r in csv.DictReader(handle)}
    old, new = closed(before), closed(after)
    lost = sorted(k for k, v in old.items() if v and not new.get(k))
    gained = sorted(k for k, v in new.items() if v and not old.get(k))
    print(f"closed_strict: {sum(old.values())} -> {sum(new.values())}; lost {len(lost)}, gained {len(gained)}")
    for name, rva in lost[:50]:
        print(f"  LOST {rva} {name}")
    return 1 if lost else 0


def gate_cost(header, jobs):
    """Dependents of `header` and the wall time to re-verify them in parallel."""
    sys.path.insert(0, str(ROOT / "tools"))
    import header_dependents as H
    edges, macro = H.scan(None)
    rows = H.ledger_sources(None)
    reached = H.dependents([header], H.graph(edges), macro)
    sources = sorted(p for p in reached if p in rows)
    # The way the pre-commit hook does it: one scoped build per ~24,000-character
    # chunk of paths, BUILD_POOL compiles in parallel inside each.
    started, red, chunk = time.time(), [], []
    chunks = []
    for source in sources:
        if chunk and sum(len(p) + 3 for p in chunk) + len(source) > 24000:
            chunks.append(chunk)
            chunk = []
        chunk.append(source)
    if chunk:
        chunks.append(chunk)
    for paths in chunks:
        if BFME2:
            command, env = [sys.executable, "tools/build.py", *paths], dict(os.environ, MSYS_NO_PATHCONV="1")
        else:
            import bash_path
            command = [bash_path.bash(), str(ROOT / "build.sh"), *paths]
            env = {k: v for k, v in bash_path.env().items() if k != "MSYS_NO_PATHCONV"}
        env["BUILD_POOL"] = str(jobs)
        done = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, errors="replace", env=env)
        if done.returncode:
            red.append(f"chunk of {len(paths)} exited {done.returncode}: "
                       + next((l for l in (done.stdout + done.stderr).splitlines() if "FAIL" in l or "error" in l), ""))
    seconds = time.time() - started
    print(f"{header}: {len(sources)} dependent ledger sources; scoped gate {seconds:.0f}s "
          f"(BUILD_POOL={jobs}, {len(chunks)} chunk(s)); {len(red)} red chunk(s)")
    for line in red[:20]:
        print(f"  {line[:200]}")
    return {"header": header, "dependents": len(sources), "seconds": round(seconds, 1), "jobs": jobs, "red": red}


# ---------------------------------------------------------------- driver

def run(args):
    name = args.name
    header = args.header or registered().get(name)
    if not header:
        raise SystemExit(f"{name}: no header given or registered")
    fixed = not args.generate
    sources = class_contract.census(name)
    if args.sample and len(sources) > args.sample:
        sources = sorted(random.Random(args.seed).sample(sources, args.sample))
    print(f"{name}: {len(sources)} units, header {header} ({'registered' if fixed else 'generated'})", flush=True)
    contract_path = class_contract.contract_path(name)
    if contract_path.exists():
        contract = json.loads(contract_path.read_text(encoding="utf-8"))
    else:
        contract = class_contract.decide(name, sources=sources, jobs=args.jobs)
        contract_path.parent.mkdir(parents=True, exist_ok=True)
        contract_path.write_text(json.dumps({k: v for k, v in contract.items() if k != "sources"}, indent=1,
                                            sort_keys=True) + "\n", encoding="utf-8")
    if contract["queue"] and not fixed:
        print(f"  contract has {len(contract['queue'])} undecided attribute(s); refusing to generate: "
              f"{[q['attribute'] for q in contract['queue']]}")
        return 2
    missing = unheadered_bases(contract) if not fixed else []
    if missing:
        print(f"  contract names base(s) with no canonical header; adopt them first: {missing}")
        return 2
    if not fixed and contract.get("vslots"):
        _, _, problems = slot_declarations(contract, sources)
        if problems:
            print(f"  {len(problems)} virtual slot(s) cannot be declared; refusing to generate: {problems}")
            return 2
    if not fixed:
        _, problems = special_members(name, contract, sources)
        if problems:
            print(f"  {len(problems)} special member(s) the views disagree on; refusing to generate: {problems}")
            return 2
    variants =args.variants.split(",") if not fixed else ["registered"]
    results = tournament(name, contract, sources, header, variants, args.jobs, fixed_header=fixed)
    winner = max(variants, key=lambda v: (sum(x is None for x in results[v]["verdicts"].values()), -variants.index(v)))
    best = results[winner]
    passed = sorted(s for s, v in best["verdicts"].items() if v is None)
    failed = {s: v for s, v in best["verdicts"].items() if v is not None}
    print(f"{name}: winner {winner}: {len(passed)}/{len(sources)} pass "
          f"({100 * len(passed) / max(1, len(sources)):.0f}%), {len(failed)} queued")
    reasons = collections.Counter(failure_class(v) for v in failed.values())
    print("  failures:", dict(reasons.most_common(8)))
    summary = {"class": name, "header": header, "units": len(sources), "winner": winner,
               "variants": {v: sum(x is None for x in r["verdicts"].values()) for v, r in results.items()},
               "seconds": {v: round(r["seconds"], 1) for v, r in results.items()}, "passed": passed,
               "failed": failed, "reasons": dict(reasons)}
    SCRATCH.mkdir(parents=True, exist_ok=True)
    (SCRATCH / f"{class_contract.portable_component(name)}.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    if args.apply:
        # The picker claims only the class, its header and the merge donors; the units
        # rewritten here are claimed now, right before they change, and refused if held.
        held = claim_rewrites(name, ([] if fixed else [header]) + passed)
        if held and getattr(args, "skip_held", False):
            # Opt-in: queue the held units and apply the rest. The claim is atomic, so
            # each retry claims the reduced set; a unit taken meanwhile is queued too.
            for _ in range(3):
                if not held or any(path == header or path.startswith("(") for path, _ in held):
                    break      # the header itself (or an unavailable claim service) still refuses
                for path, who in held:
                    if path in passed:
                        passed.remove(path)
                        failed[path] = f"held by {who} during run; retry when released"
                held = claim_rewrites(name, ([] if fixed else [header]) + passed)
        if held:
            print(f"  refusing to apply: {len(held)} file(s) another worker holds: " + "; ".join(
                f"{key} ({who})" for key, who in held[:8]) + (" ..." if len(held) > 8 else ""))
            return 3
        blocked = dependency_blockers(best.get("dependencies", {}), passed)
        failed.update(blocked)
        passed = [s for s in passed if s not in blocked]
        if not fixed:
            (ROOT / header).parent.mkdir(parents=True, exist_ok=True)
            (ROOT / header).write_text(best["header"], encoding="utf-8", newline="\n")
            register(name, header, f"generated by header_adopt_lane from class_contracts/{contract_path.name}; "
                     f"variant {winner}; {len(passed)}/{len(sources)} sampled units adopt")
        else:
            register(name, header, f"existing header; contract class_contracts/{contract_path.name}; "
                     f"{len(passed)}/{len(sources)} sampled units adopt")
        for source in passed:
            (ROOT / source).write_bytes(best["texts"][source].encode("latin-1"))
        renamed = [r for s in passed for r in best["renames"].get(s, [])]
        rewrite_ledger(renamed)
        if renamed:
            # The hook verifies against the working-tree ledger, so units committed
            # without these renames would pass and leave HEAD inconsistent.
            print(f"  {len(renamed)} ledger row(s) renamed to the canonical class-key: commit "
                  f"{LEDGER.relative_to(ROOT).as_posix()} in the same commit as their units")
        write_queue(name, header, failed)
        print(f"  applied: {len(passed)} units rewritten, {len(failed)} queued in {QUEUE.relative_to(ROOT).as_posix()}")
        print(f"  after the apply commit is pushed: python3 tools/header_adopt_lane.py release --class {name}")
    return 0


def rewrite_claims_path(name):
    return SCRATCH / f"{class_contract.portable_component(name)}.claims"


def claim_rewrites(name, files):
    """Claim `file:` keys for the files `run --apply` is about to rewrite: [] when all are
    ours (recorded for `release`), else [(path, holder)] after giving back what this call won."""
    import claims
    keys = [f"file:{f}" for f in sorted(set(files))]
    if not keys:
        return []
    try:
        result = claims.claim(keys, note=f"header_adopt_lane apply {name}", root=ROOT, atomic_only=True)
    except claims.ClaimsUnavailable as exc:
        return [("(claims unavailable)", str(exc))]
    if result.refused:
        prior = set(getattr(result, "prior", ()))
        won = [k for k in result.claimed if k not in prior]
        if won:
            claims.release(won, root=ROOT)
        names = {claims.key_of(k): k[len("file:"):] for k in keys}
        owners = {}
        try:
            for records in claims._blocking_records(ROOT):
                owners.update({k: info.get("owner", "?") for k, info in records.items()})
        except claims.ClaimsUnavailable:
            pass
        return [(names.get(k, str(k)), owners.get(k, "another worker")) for k in result.refused]
    SCRATCH.mkdir(parents=True, exist_ok=True)
    rewrite_claims_path(name).write_text("\n".join(keys) + "\n", encoding="utf-8")
    return []


def release_rewrites(name):
    """Release the file claims `run --apply` took for `name` (after its commit is pushed)."""
    import claims
    path = rewrite_claims_path(name)
    if not path.exists():
        print(f"{name}: no apply-time claims recorded ({path.relative_to(ROOT).as_posix()})")
        return 0
    keys = [k for k in path.read_text(encoding="utf-8").split() if k]
    done = claims.release(keys, root=ROOT)
    print(f"{name}: released {len(done)} of {len(keys)} apply-time file claim(s)")
    if len(done) == len(keys):
        path.unlink()
    return 0 if len(done) == len(keys) else 1


# ---------------------------------------------------------------- merge blockers
#
# tu_skeleton --merge rejects a donor that does not compile beside the seed, and
# the commonest cause is two private views of one class in one approved TU that
# tools/tu_views.py cannot reconcile (different bases, a hand-written vtable
# member, a vfptr in one view only, another class-key or declspec) or a private
# copy of a class that already has a canonical header. One canonical header per
# class is the fix, so the lane serves first the classes whose header unblocks
# the most merge donors. The test is textual (tu_views' shared_classes plus each
# view's head), so it is cheap; tu_views --dry-run gives the compiled verdict.

MERGE_KINDS = ("canonical-copy", "base", "fake-vtable", "vfptr", "vslot", "key/declspec")
FIRST_VIRTUAL = re.compile(r"\bvirtual\b[^;{}()]*?(~?[A-Za-z_]\w*)\s*\(")
FAKE_VTABLE = re.compile(r"\b(?:m_vtable|m_vtbl|m_vfptr|m_vptr|vtable|vfptr|vptr|_vptr)\b")
VIEW_HEAD = re.compile(r"(?:class|struct)\s+((?:__declspec\([^)]*\)\s*)*)[A-Za-z_]\w*\s*(?::(?!:)([^{]*))?\{$")
BASE_NAME = re.compile(r"(?:\b(?:public|protected|private|virtual)\s+)*([A-Za-z_]\w*)\s*(?:<[^>]*>)?\s*$")


def view_signatures(text):
    """{class: (key, declspecs, base clause, fake vtable member, declares virtuals, first virtual)}
    for every namespace-scope body in `text` (a class declared twice keeps its first body)."""
    code = masked(text)
    out = {}
    for name, start, end, key in class_layouts.class_body_spans(text):
        if "::" in name or name in out:
            continue
        brace = code.find("{", start)
        head = " ".join(code[start:brace + 1].split())
        found = VIEW_HEAD.search(head)
        body = code[brace + 1:end - 1]
        out[name] = (key, " ".join((found.group(1) or "").split()) if found else "",
                     " ".join((found.group(2) or "").split()) if found else "?",
                     bool(FAKE_VTABLE.search(body)), bool(re.search(r"\bvirtual\b", body)),
                     (m.group(1) if (m := FIRST_VIRTUAL.search(body)) else ""))
    return out


def base_names(clause):
    while re.search(r"<[^<>]*>", clause):                       # template arguments hold commas
        clause = re.sub(r"<[^<>]*>", "", clause)
    return [m.group(1) for part in clause.split(",") if (m := BASE_NAME.search(part.strip()))]


def disagreement(sigs, canonical):
    """Why views `sigs` (one per file) of one class block a merge, or None when tu_views can
    reconcile them (one head, one vfptr shape, one slot 0): the first of MERGE_KINDS that
    applies. Textual, so a proxy: tu_views --dry-run gives the compiled verdict."""
    if canonical:
        return "canonical-copy"
    vals = set(sigs)
    if len(vals) < 2:
        return None
    if len({v[2] for v in vals}) > 1:
        return "base"
    if any(v[3] for v in vals):
        return "fake-vtable"
    if len({v[4] for v in vals}) > 1:
        return "vfptr"
    if not next(iter(vals))[2] and len({v[5] for v in vals}) > 1:   # no base: the first virtual is slot 0
        return "vslot"
    if len({(v[0], v[1]) for v in vals}) > 1:
        return "key/declspec"
    return None


def tu_blockers(files, sigs, canon):
    """{class: (kind, [files])} for the classes two or more of `files` declare privately whose
    views block the merge; `sigs` is {file: view_signatures(text)}."""
    seen = collections.defaultdict(list)
    for f in files:
        for name in sigs.get(f, {}):
            seen[name].append(f)
    out = {}
    for name, fs in seen.items():
        if len(fs) < 2:
            continue
        kind = disagreement([sigs[f][name] for f in fs], name in canon)
        if kind:
            out[name] = (kind, sorted(fs))
    return out


def merge_rank(blockers, canon, order=DEPENDENCY_ORDER):
    """[(class, score, own)] most merge donors unblocked first. `own` is the donor count
    the class's own views block; `score` is the largest `own` of the class and of every
    class that needs it first: the bases its views name (transitively) and the earlier
    stages of DEPENDENCY_ORDER. A prerequisite therefore never ranks below what depends
    on it, and at one score comes first. Only classes that block a merge themselves rank: a base name one view invents
    (and the typedef stage) is no header-lane item."""
    own = {c: d["donors"] for c, d in blockers.items()}
    needs = collections.defaultdict(set)                          # class -> classes it needs first
    for c, d in blockers.items():
        needs[c].update(b for b in d.get("bases", ()) if b != c)
    stages = [names for _, names in order]
    for i, names in enumerate(stages):
        for later in stages[i + 1:]:
            for c in later:
                needs[c].update(names)
    score, needed_by = dict(own), collections.Counter()
    for c in sorted(own):
        stack, seen = [c], {c}
        while stack:
            for b in sorted(needs.get(stack.pop(), ())):
                if b not in seen:
                    seen.add(b)
                    stack.append(b)
                    if b in own:
                        score[b] = max(score[b], own[c])
                        needed_by[b] += 1
    # at one score, what more classes need comes first (a prerequisite before its dependents)
    return sorted(((c, s, own[c]) for c, s in score.items() if s), key=lambda r: (-r[1], -needed_by[r[0]], -r[2], r[0]))


def _git(*args, strip=True):
    got = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, errors="replace")
    if got.returncode:
        return None
    return got.stdout.strip() if strip else got.stdout


def porcelain_paths(status):
    """[(code, path)] from `git status --porcelain -z`: a rename or copy carries its source as a
    second NUL field, and both paths are inputs."""
    fields, out, i = status.split("\0"), [], 0
    while i < len(fields):
        entry = fields[i]
        i += 1
        if len(entry) < 4:
            continue
        code = entry[:2]
        out.append((code, entry[3:]))
        if "R" in code or "C" in code:
            if i < len(fields) and fields[i]:
                out.append((code, fields[i]))
            i += 1
    return out


def merge_inputs():
    """(HEAD, dirty fingerprint) or None when git cannot say. The fingerprint is "" for a clean
    tree, else a digest of every dirty Code/ or reverse/ path with its content and of every
    submodule off its pin: the merge queue (tu_map rebuilt from the reference trees when stale),
    the views and the registry are a pure function of those."""
    head = _git("rev-parse", "HEAD")
    status = _git("status", "--porcelain", "-z", "--untracked-files=all", "--", "Code", "reverse", strip=False)
    if not head or status is None:
        return None
    parts = [f"{code} {path} {class_layouts.file_sha(ROOT / path)}" for code, path in porcelain_paths(status)]
    for line in (_git("config", "-f", ".gitmodules", "--get-regexp", r"\.path$") or "").split("\n"):
        path = line.split(" ", 1)[-1].strip()    # `git submodule status` costs seconds; this, two calls
        if path:
            want, got = _git("rev-parse", f"HEAD:{path}"), _git("-C", path, "rev-parse", "HEAD")
            if want != got:
                parts.append(f"pin {path} {got}")
    if not parts:
        return head, ""
    return head, class_layouts.sha("\n".join(sorted(parts)).encode())[:16]


def compute_merge_blockers(queue=None, donors_of=None, read=None, canon=None):
    """{class: {donors, rows, tus, kinds, bases, files, virtual}} over the merge queue
    (tu_skeleton.queue); `virtual` when a blocking view declares a virtual or a vtable member.
    donors_of(tu) -> {file: rows}; read(file) -> text; both injectable for tests."""
    import tu_skeleton
    if queue is None:
        queue = tu_skeleton.queue(root=ROOT)
    donors_of = donors_of or (lambda tu: tu_skeleton.donors(tu, tu_skeleton.skeleton(tu))[0])
    read = read or (lambda f: (ROOT / f).read_text(encoding="latin-1"))
    canon = registered() if canon is None else canon
    sig_cache, out = {}, {}
    for entry in queue:
        tu = entry["tu"]
        don = donors_of(tu)
        for f in don:
            if f not in sig_cache:
                try:
                    sig_cache[f] = view_signatures(read(f))
                except OSError:
                    sig_cache[f] = {}
        for name, (kind, fs) in tu_blockers(sorted(don), sig_cache, canon).items():
            d = out.setdefault(name, {"donors": 0, "rows": 0, "tus": [], "kinds": {}, "bases": set(),
                                      "files": [], "virtual": False})
            d["donors"] += len(fs)
            d["rows"] += sum(len(don[f]) for f in fs)
            d["tus"].append(tu)
            d["kinds"][kind] = d["kinds"].get(kind, 0) + 1
            d["files"].extend(fs)
            for f in fs:
                d["bases"].update(base_names(sig_cache[f][name][2]))
                d["virtual"] = d["virtual"] or sig_cache[f][name][3] or sig_cache[f][name][4]
    for d in out.values():
        d["bases"] = sorted(d["bases"])
        d["tus"] = sorted(d["tus"])
        d["files"] = sorted(set(d["files"]))
    return out


# Official BFME header trees a canonical header's path is taken from: BFME 1's own game tree
# first, then Zero Hour's (both mirror Code/ from their root).
REFERENCE_HEADER_TREES = (("bfme1", "reference/open-bfme-1/game"),
                          ("zh", "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"))


def reference_header_index(trees=REFERENCE_HEADER_TREES, root=None):
    """{tree label: {class: [header paths relative to the tree]}} for every namespace-scope body."""
    root = Path(root or ROOT)
    out = {}
    for label, tree in trees:
        index = collections.defaultdict(list)
        base = root / tree
        for path in sorted(base.rglob("*.h")) if base.is_dir() else ():
            try:
                text = path.read_text(encoding="latin-1")
            except OSError:
                continue
            for name in dict.fromkeys(class_layouts.class_bodies(text)):
                index[name].append(path.relative_to(base).as_posix())
        out[label] = dict(index)
    return out


def header_destination(name, index, exists=None):
    """{header, evidence} for `name`: the one official header (BFME 1, else ZH) that defines it,
    at the same path under Code/; else {header: None, why}. An ambiguous or occupied path is
    refused, never guessed: choose from the evidence and pass --header PATH to `run`."""
    exists = exists or (lambda p: (ROOT / p).exists())
    for label, tree in REFERENCE_HEADER_TREES:
        found = index.get(label, {}).get(name, [])
        note = ""
        if len(found) > 1:
            # Several headers define a body: the one named for the class is its home (BFME 1's
            # object.h holds `class Object : public Thing`; ObjectStatusBits.h a padded view of
            # it). Exactly one such header decides; none or several stay ambiguous.
            named = [f for f in found if Path(f).stem.lower() == name.split("::")[-1].lower()]
            if len(named) != 1:
                return {"header": None, "why": f"{label} defines {name} in {len(found)} headers: "
                        + ", ".join(found[:4])}
            note = f"; the header named for the class, over {', '.join(f for f in found if f != named[0])[:200]}"
            found = named
        if found:
            header = "Code/" + found[0]
            if exists(header):
                return {"header": None, "why": f"{header} ({label}: {tree}/{found[0]}) already exists; generating "
                                               "would overwrite it"}
            return {"header": header, "evidence": f"{label}: {tree}/{found[0]}{note}"}
    return {"header": None, "why": f"neither BFME 1 nor ZH defines {name} in a header"}


MERGE_DEST_CLASSES = 60     # header-less classes ranked first get a header destination
MERGE_CACHE_HOURS = 12      # a ranking from an ancestor of HEAD this recent is reused (it only orders work)
MERGE_LOCK_SECONDS = 3600   # a refresh lock older than this is stale (its process died)
MERGE_PAYLOAD_VERSION = 3   # bump when the payload's shape changes: older entries are misses


def merge_cache_dir():
    """The shared, content-addressed picker cache (repair_queue.cache_dir()): every worktree of
    the clone shares one compute."""
    import repair_queue
    return repair_queue.cache_dir() / "merge_blockers"


def _write_json(path, value):
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        tmp = path.with_suffix(f".{os.getpid()}.tmp")
        tmp.write_text(json.dumps(value, sort_keys=True), encoding="utf-8")
        os.replace(tmp, path)
    except OSError:
        pass


def reference_headers():
    """reference_header_index(), cached by the BFME 1 submodule pin."""
    pin = _git("rev-parse", "HEAD:reference/open-bfme-1") or "none"
    path = merge_cache_dir() / f"reference_headers_{pin}.json"
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        index = reference_header_index()
        if all(index.values()):     # a checkout without the reference trees must not cache an empty index
            _write_json(path, index)
        return index


def compute_merge_payload():
    """{classes, destinations} for the current tree: the ranking and, for the MERGE_DEST_CLASSES
    header-less classes ranked first, where each one's canonical header goes."""
    classes = compute_merge_blockers()
    canon = registered()
    top = [c for c, _, _ in merge_rank(classes, canon) if c not in canon][:MERGE_DEST_CLASSES]
    index = reference_headers()
    return {"classes": classes, "destinations": {c: header_destination(c, index) for c in top}}


def _entry_name(head, fingerprint):
    return f"{head}+{fingerprint or 'clean'}.json"


def cached_merge_payload(inputs, directory=None):
    """The payload stored for `inputs` = (head, fingerprint), else the newest one stored in the
    last MERGE_CACHE_HOURS for an ancestor of HEAD with the same fingerprint (clean matches clean
    only), else None."""
    if inputs is None:
        return None
    directory = directory or merge_cache_dir()
    head, fingerprint = inputs
    try:
        exact = json.loads((directory / _entry_name(head, fingerprint)).read_text(encoding="utf-8"))
        if exact.get("version") == MERGE_PAYLOAD_VERSION:
            return exact["payload"]
    except (OSError, ValueError, KeyError):
        pass
    suffix = "+" + (fingerprint or "clean") + ".json"
    try:
        entries = sorted((p for p in directory.glob("*" + suffix) if p.name.endswith(suffix)),
                         key=lambda p: (p.stat().st_mtime, p.name), reverse=True)
    except OSError:
        return None
    for path in entries[:20]:
        try:
            cached = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if (cached.get("fingerprint") == fingerprint and cached.get("version") == MERGE_PAYLOAD_VERSION
                and time.time() - cached.get("time", 0) < MERGE_CACHE_HOURS * 3600
                and _git("merge-base", "--is-ancestor", cached.get("head", ""), head) is not None):
            return cached["payload"]
    return None


def store_merge_payload(inputs, payload, directory=None):
    if inputs is None:
        return
    head, fingerprint = inputs
    _write_json((directory or merge_cache_dir()) / _entry_name(head, fingerprint),
                {"head": head, "fingerprint": fingerprint, "time": int(time.time()),
                 "version": MERGE_PAYLOAD_VERSION, "payload": payload})


def merge_payload(refresh=False):
    """The payload for this tree, computed synchronously on a miss (`order --merges`, the
    background refresh); refresh recomputes. A ranking orders work only."""
    inputs = merge_inputs()
    payload = None if refresh else cached_merge_payload(inputs)
    if payload is None:
        payload = compute_merge_payload()
        store_merge_payload(inputs, payload)
    return payload


def merge_blockers(refresh=False):
    return merge_payload(refresh)["classes"]


def refresh_allowed():
    """No detached refresh in CI, under pytest, or when BFME_NO_MERGE_REFRESH is set."""
    return not any(os.environ.get(v) for v in ("CI", "PYTEST_CURRENT_TEST", "BFME_NO_MERGE_REFRESH"))


def start_refresh(directory=None, spawn=None):
    """Start one detached `refresh-merges` unless a refresh holds the lock (any seat of the clone;
    a lock older than MERGE_LOCK_SECONDS is stale and taken over). Returns what happened."""
    if not refresh_allowed():
        return "no background refresh here (CI, pytest or BFME_NO_MERGE_REFRESH)"
    directory = directory or merge_cache_dir()
    lock = directory / "refresh.lock"
    try:
        directory.mkdir(parents=True, exist_ok=True)
        if lock.exists() and time.time() - lock.stat().st_mtime > MERGE_LOCK_SECONDS:
            lock.unlink()
        fd = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
    except FileExistsError:
        return "a background refresh is already running"
    except OSError as exc:
        return f"no background refresh ({exc})"
    with os.fdopen(fd, "w") as handle:
        handle.write(f"{os.getpid()} {int(time.time())}\n")
    command = [sys.executable, str(Path(__file__).resolve()), "refresh-merges", "--lock", str(lock)]
    try:
        (spawn or _spawn_detached)(command)
    except OSError as exc:
        lock.unlink(missing_ok=True)
        return f"no background refresh ({exc})"
    return "a background refresh started (header_adopt_lane.py refresh-merges)"


def _spawn_detached(command):
    flags = {}
    if os.name == "nt":
        flags["creationflags"] = subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP
    else:
        flags["start_new_session"] = True
    subprocess.Popen(command, cwd=ROOT, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                     stderr=subprocess.DEVNULL, close_fds=True, **flags)


def merge_payload_nonblocking():
    """(payload or None, note) for the picker, which never computes: on a miss it starts one
    background refresh and the caller ranks by DEPENDENCY_ORDER alone."""
    payload = cached_merge_payload(merge_inputs())
    if payload is not None:
        return payload, ""
    return None, "merge ranking not cached for this tree, DEPENDENCY_ORDER only; " + start_refresh()


def print_merge_order(limit, refresh=False):
    canon, blockers = registered(), merge_blockers(refresh)
    contracts = {p.stem for p in class_contract.CONTRACTS.glob("*.json")} if class_contract.CONTRACTS.exists() else set()
    print(f"classes by merge donors unblocked ({len(blockers)} block a queued merge; cache {merge_cache_dir()}):")
    print(f"  {'class':<32} {'score':>5} {'own':>5} {'rows':>5} {'TUs':>4}  header/contract  kinds")
    for c, score, own in merge_rank(blockers, canon)[:limit]:
        d = blockers.get(c, {})
        state = ("header" if c in canon else "-") + "/" + (
            "contract" if class_contract.portable_component(c) in contracts else "-")
        kinds = " ".join(f"{k}:{n}" for k, n in sorted(d.get("kinds", {}).items()))
        print(f"  {c:<32} {score:5} {own:5} {d.get('rows', 0):5} {len(d.get('tus', ())):4}  {state:<15}  {kinds}")



# ---------------------------------------------------------------- bulk mode (run --all)
#
# One pass over the establish classes `order --merges` ranks, doing mechanically what
# an agent did per class: contract -> generate (every variant, `includes` among them)
# -> trial apply -> link check -> one commit per class. Whatever the pipeline cannot
# decide is recorded, with the evidence, in the decision queue (DECISIONS), which the
# header tier serves to seats as "decide <attribute> of <class>" items ranked by the
# merge donors the class's header unblocks. The pass never guesses: an undecided
# contract attribute, a slot no view can declare, a base without a header, a missing
# destination, a held claim or a unit whose link would regress all become records.

DECISIONS = REVERSE / "header_decisions.jsonl"
BULK_STATE = SCRATCH / "run_all_state.json"
BULK_DONE = ("adopted", "queued")     # --resume skips these; "claimed", "waiting" and errors are retried
TRANSIENT_KINDS = ("claimed", "base-unheadered")   # blockers that clear on their own, not a settled decision
# Kinds a seat can act on; the picker serves these. `claimed` is transient (the holder
# is working on it) and `base-unheadered` is served through the base's own record.
DECIDABLE = ("undecided", "slot-undeclarable", "special-undeclarable", "no-destination", "no-unit-adopts", "link-regression",
             "commit-refused", "error")


def plan_order(ranked, blockers, canon):
    """The classes to try, in rank order, a class never before a ranked base it names.

    `ranked` is merge_rank's [(class, score, own)]. A registered class is done; a
    ranked base is pulled ahead of the class that needs it (merge_rank already ranks
    a prerequisite no lower, so this only fixes ties and cycles' order)."""
    names = [c for c, _, _ in ranked if c not in canon]
    known = set(names)
    out, placed = [], set()

    def place(name, stack):
        if name in placed or name in stack:
            return
        stack.add(name)
        for base in sorted(blockers.get(name, {}).get("bases", ())):
            base = base_identity(base)
            if base in known and base != name:
                place(base, stack)
        placed.add(name)
        out.append(name)

    for name in names:
        place(name, set())
    return out


def held_elsewhere(keys):
    """{key: owner} for the claim keys (`class:X`, `file:P`) another worker holds."""
    import claims
    wanted = {claims.key_of(k): k for k in keys}
    out = {}
    try:
        for records in claims._blocking_records(ROOT):
            for key, info in records.items():
                if key in wanted:
                    out[wanted[key]] = info.get("owner", "another worker")
    except claims.ClaimsUnavailable as exc:
        return {k: f"claims unavailable: {exc}" for k in keys}
    return out


def claim_class(name):
    """Claim `class:NAME` for the pass: None when won, else the holder."""
    import claims
    key = f"class:{name}"
    try:
        result = claims.claim([key], note="header_adopt_lane run --all", root=ROOT, atomic_only=True)
    except claims.ClaimsUnavailable as exc:
        return f"claims unavailable: {exc}"
    if result.refused:
        return held_elsewhere([key]).get(key, "another worker")
    return None


def decision(name, kind, detail, attributes=(), **evidence):
    """One decision-queue record: what blocks `name`, the competing evidence, and how to resume."""
    return {"class": name, "kind": kind, "detail": detail, "attributes": list(attributes),
            "resume": f"python3 tools/header_adopt_lane.py run --all --only {name}", **evidence}


def contract_decisions(contract):
    """[{attribute, candidates, why}] for every attribute the contract leaves undecided."""
    return [{"attribute": q.get("attribute"), "candidates": q.get("candidates", {}),
             **({"why": q["why"]} if q.get("why") else {})} for q in contract.get("queue", ())]


def write_decisions(records, path=None, canon=None):
    """Merge `records` ({class: record}) into the decision queue, drop classes now registered,
    rank by merge donors unblocked (then class), and write it as JSON lines."""
    path = Path(path or DECISIONS)
    canon = registered() if canon is None else canon
    current = {}
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            if line.strip():
                row = json.loads(line)
                current[row["class"]] = row
    current.update(records)
    rows = [r for c, r in current.items() if c not in canon and r is not None]
    rows.sort(key=lambda r: (-int(r.get("merge_donors", 0)), r["class"]))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(json.dumps(r, sort_keys=True) + "\n" for r in rows), encoding="utf-8", newline="\n")
    return rows


def read_decisions(path=None):
    path = Path(path or DECISIONS)
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]


def load_state(path=None):
    path = Path(path or BULK_STATE)
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return {}


def save_state(state, path=None):
    path = Path(path or BULK_STATE)
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(state, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, path)


def busy_lock_keys():
    """Lock keys of every claim another seat holds (claims.busy_keys: a class or RVA claim covers its files)."""
    import claims
    try:
        return set(claims.busy_keys(ROOT))
    except Exception:  # noqa: BLE001 - no origin: claim_class and claim_rewrites still refuse at claim time
        return set()


def busy_files(paths, busy):
    """The `paths` whose file lock another seat's claim covers."""
    if not busy:
        return set()
    import claims
    return {p for p in paths if claims.key_of(f"file:{p}") in busy}


def bulk_prepare(name, ctx):
    """Everything up to the tournament for one class: {"record": decision} when it cannot be
    generated, else {"contract", "sources", "header", "results", "winner"}. Writes nothing to
    the tree except the tournament's own temporary swaps, which it restores."""
    info = ctx["info"].get(name, {})
    donors = {"merge_donors": info.get("score", 0), "own_donors": info.get("own", 0),
              "tus": len(info.get("tus", ()))}
    if ctx["dry_run"]:
        holder = held_elsewhere([f"class:{name}"]).get(f"class:{name}")
    else:
        holder = claim_class(name)
    if holder:
        return {"record": decision(name, "claimed", f"class:{name} is held by {holder}", holder=holder, **donors)}
    dest = ctx["destination"](name)
    if not dest.get("header"):
        return {"record": decision(name, "no-destination", dest.get("why", "no header destination"),
                                   command=f"python3 tools/header_adopt_lane.py dest --class {name}", **donors)}
    header = dest["header"]
    busy = ctx["busy"]() if callable(ctx.get("busy")) else (ctx.get("busy") or set())
    if busy_files([header], busy):       # the tournament writes the header before claim_rewrites runs
        return {"record": decision(name, "claimed", f"its header {header} is held by another seat",
                                   holder="another seat", **donors)}
    sources = class_contract.census(name, ctx["rows"])
    if ctx["sample"] and len(sources) > ctx["sample"]:
        sources = sorted(random.Random(ctx["seed"]).sample(sources, ctx["sample"]))
    if not sources:
        return {"record": decision(name, "no-unit-adopts", "the census finds no private view", header=header, **donors)}
    held = held_elsewhere([f"file:{s}" for s in sources])
    held.update({f"file:{s}": "another seat (a claim on its rows or class)"
                 for s in busy_files(sources, busy) if f"file:{s}" not in held})
    if held and not ctx["dry_run"]:
        sources = [s for s in sources if f"file:{s}" not in held]
    path = class_contract.contract_path(name)
    if path.exists():
        contract = json.loads(path.read_text(encoding="utf-8"))
    else:
        contract = class_contract.decide(name, sources=sources, jobs=ctx["unit_jobs"])
    contract_rel = (path.relative_to(ROOT).as_posix() if path.exists()
                    else f"not written yet: python3 tools/class_contract.py --class {name} --write")
    evidence = dict(donors, header=header, contract=contract_rel, units=len(sources),
                    **({"held_units": sorted(held.items())[:20]} if held else {}))
    undecided = contract_decisions(contract)
    if undecided:
        first = undecided[0]
        return {"record": decision(name, "undecided",
                                   f"decide {first['attribute']} of {name}" + (f" (+{len(undecided) - 1} more)"
                                                                                if len(undecided) > 1 else ""),
                                   undecided, **evidence), "contract": contract}
    missing = unheadered_bases(contract)
    if missing:
        return {"record": decision(name, "base-unheadered", f"adopt the base header(s) first: {', '.join(missing)}",
                                   bases=missing, **evidence), "contract": contract}
    if contract.get("vslots"):
        _, _, problems = slot_declarations(contract, sources)
        if problems:
            return {"record": decision(name, "slot-undeclarable", f"{len(problems)} slot(s) cannot be declared: "
                                       + "; ".join(problems[:3]),
                                       [{"attribute": p.split()[0], "why": p} for p in problems], **evidence),
                    "contract": contract}
    _, problems = special_members(name, contract, sources)
    if problems:
        return {"record": decision(name, "special-undeclarable", f"{len(problems)} special member(s) the views "
                                   "disagree on: " + "; ".join(problems[:3]),
                                   [{"attribute": "special", "why": p} for p in problems], **evidence),
                "contract": contract}
    if ctx["dry_run"]:
        return {"would": {"class": name, "header": header, "units": len(sources), "contract": contract_rel},
                "contract": contract}
    held_header = claim_rewrites(name, [header])
    if held_header:
        return {"record": decision(name, "claimed", f"its header {header} is held by {held_header[0][1]}",
                                   holder=held_header[0][1], **evidence)}
    results = tournament(name, contract, sources, header, ctx["variants"], ctx["unit_jobs"])
    winner = max(ctx["variants"],
                 key=lambda v: (sum(x is None for x in results[v]["verdicts"].values()), -ctx["variants"].index(v)))
    return {"contract": contract, "sources": sources, "header": header, "results": results, "winner": winner,
            "evidence": evidence, "held": {k.split(":", 1)[1]: w for k, w in held.items()}}


def bulk_land(name, prepared, ctx):
    """Trial-apply the winning variant, drop every unit whose link would regress, then
    register, queue and commit the class. ("adopted", None, commit) or ("queued", record, None)."""
    best, header = prepared["results"][prepared["winner"]], prepared["header"]
    evidence = prepared["evidence"]
    passed = sorted(s for s, v in best["verdicts"].items() if v is None)
    failed = {s: v for s, v in best["verdicts"].items() if v is not None}
    blocked = dependency_blockers(best.get("dependencies", {}), passed)
    failed.update(blocked)
    passed = [s for s in passed if s not in blocked]
    if not passed:
        release_rewrites(name)      # the header claim bulk_prepare took
        reasons = collections.Counter(failure_class(v) for v in failed.values())
        return "queued", decision(name, "no-unit-adopts", f"no unit adopts in any variant ({dict(reasons)})",
                                  failures=dict(sorted(failed.items())[:10]), **evidence), None
    held = claim_rewrites(name, [header] + passed)
    if held:
        release_rewrites(name)      # the header claim bulk_prepare took
        return "queued", decision(name, "claimed", f"{len(held)} unit(s) are held: "
                                  + "; ".join(f"{k} ({w})" for k, w in held[:4]), holder=held[0][1], **evidence), None
    originals = {s: (ROOT / s).read_bytes() for s in passed}
    header_path = ROOT / header
    header_before = header_path.read_bytes() if header_path.exists() else None
    header_path.parent.mkdir(parents=True, exist_ok=True)
    header_path.write_text(best["header"], encoding="utf-8", newline="\n")
    for source in passed:
        (ROOT / source).write_bytes(best["texts"][source].encode("latin-1"))
    verdicts = ctx["link_check"](passed)
    kept = [s for s in passed if verdicts.get(s) is True]
    dropped = {s: ("link regression: the census-linked unit would stop linking with the header"
                   if verdicts.get(s) is False else "link unverified: link_check gave no verdict")
               for s in passed if verdicts.get(s) is not True}
    blocked = dependency_blockers(best.get("dependencies", {}), kept)
    dropped.update(blocked)
    kept = [s for s in kept if s not in blocked]
    for source in dropped:
        (ROOT / source).write_bytes(originals[source])
    if not kept:
        if header_before is None:
            header_path.unlink()
        else:
            header_path.write_bytes(header_before)
        release_rewrites(name)
        return "queued", decision(name, "link-regression", f"every adopting unit would lose its link "
                                  f"({len(dropped)} unit(s))", units_dropped=dict(sorted(dropped.items())[:20]),
                                  **evidence), None
    contract_path = class_contract.contract_path(name)
    if not contract_path.exists():
        contract_path.parent.mkdir(parents=True, exist_ok=True)
        contract_path.write_text(json.dumps({k: v for k, v in prepared["contract"].items() if k != "sources"},
                                            indent=1, sort_keys=True) + "\n", encoding="utf-8")
    register(name, header, f"generated by header_adopt_lane run --all from class_contracts/{contract_path.name}; "
             f"variant {prepared['winner']}; {len(kept)}/{len(prepared['sources'])} units adopt")
    renamed = [r for s in kept for r in best["renames"].get(s, [])]
    rewrite_ledger(renamed)
    write_queue(name, header, {**failed, **dropped, **{s: f"held by {w} during run --all; retry when released"
                                                        for s, w in prepared.get("held", {}).items()}})
    reasons = collections.Counter(failure_class(v) for v in failed.values())
    message = (f"Generate and adopt the canonical {name} header in {len(kept)} units\n\n"
               f"header_adopt_lane.py run --all: {contract_path.relative_to(ROOT).as_posix()}, variant "
               f"{prepared['winner']}, header {header}. {len(kept)}/{len(prepared['sources'])} units adopt and "
               f"byte-match; {len(failed)} queued ({', '.join(f'{k} {n}' for k, n in reasons.most_common(6)) or '-'})"
               + (f"; {len(dropped)} dropped by the link check" if dropped else "") + ".\n"
               + "".join(f"\n{t}" for t in ctx["trailers"]) + ("\n" if ctx["trailers"] else ""))
    paths = [header, contract_path.relative_to(ROOT).as_posix(), REGISTRY.relative_to(ROOT).as_posix(),
             QUEUE.relative_to(ROOT).as_posix()] + kept + ([LEDGER.relative_to(ROOT).as_posix()] if renamed else [])
    ok, sha, tail = ctx["commit"](paths, message)
    if not ok:
        ctx["undo"](paths, header if header_before is None else None)
        release_rewrites(name)
        return "queued", decision(name, "commit-refused", "the pre-commit hook refused the class's commit",
                                  hook_tail=tail[-1500:], **evidence), None
    record = None
    if dropped:
        record = decision(name, "link-regression", f"{len(dropped)} unit(s) dropped by the link check; "
                          f"{len(kept)} adopted", units_dropped=dict(sorted(dropped.items())[:20]), **evidence)
    return "adopted", record, sha


def git_commit(paths, message):
    """Stage exactly `paths` and commit through the repository's hooks: (ok, sha, output tail)."""
    git = ["git", "-c", "core.hooksPath=.githooks"]
    present = [p for p in paths if (ROOT / p).exists() or _git("ls-files", "--", p)]
    add = subprocess.run(git + ["add", "--", *present], cwd=ROOT, capture_output=True, text=True, errors="replace")
    if add.returncode:
        return False, None, add.stdout + add.stderr
    done = subprocess.run(git + ["commit", "-q", "-F", "-"], cwd=ROOT, input=message, capture_output=True,
                          text=True, errors="replace")
    if done.returncode:
        return False, None, done.stdout + done.stderr
    return True, _git("rev-parse", "HEAD"), done.stdout[-500:]


def git_undo(paths, new_header=None):
    """Put `paths` back to HEAD after a refused commit (index and tree); remove a new header."""
    subprocess.run(["git", "reset", "-q", "--", *paths], cwd=ROOT, capture_output=True)
    tracked = [p for p in paths if _git("ls-files", "--", p)]
    if tracked:
        subprocess.run(["git", "checkout", "--", *tracked], cwd=ROOT, capture_output=True)
    for p in paths:
        if p not in tracked and (ROOT / p).exists() and (p == new_header or p.startswith("reverse/class_contracts/")):
            (ROOT / p).unlink()


def git_unstage(paths):
    """Take `paths` out of the index, keeping their contents."""
    subprocess.run(["git", "reset", "-q", "--", *paths], cwd=ROOT, capture_output=True)


def bulk_guard():
    """Nothing staged and nothing uncommitted under Code/ or reverse/: a class commit would take
    unrelated edits along, and a refused one restores its paths to HEAD."""
    staged = _git("diff", "--cached", "--name-only") or ""
    dirty = _git("status", "--porcelain", "--", "Code", "reverse") or ""
    return (staged + "\n" + dirty).strip()


def census_index(rows, names):
    """{class: {sources}} for `names` in one read of every authored ledger source
    (class_contract.census's sources, class_layouts.class_bodies' views)."""
    import class_inventory
    wanted, out = set(names), {n: {n} for n in names}
    sources = sorted({r["source"] for r in rows if r["source"].lower().endswith((".cpp", ".c"))
                      and not r["source"].startswith(class_contract.GENERATED)})
    inventory = class_inventory.inventory(sources, ROOT, wanted)
    for name, found in inventory.items():
        out[name].update(found)
    return out


def bulk_batches(order, files, needs, jobs):
    """Batches of up to `jobs` classes that share no file, a class never batched with
    (or before) a class it needs that is still pending."""
    pending, out = list(order), []
    while pending:
        batch, used, waiting = [], set(), set()
        for name in list(pending):
            if len(batch) >= jobs:
                break
            blocked = needs.get(name, set()) & (set(pending) - {name})
            if blocked & (waiting | set(batch)) or any(order.index(b) < order.index(name) for b in blocked):
                waiting.add(name)
                continue
            if files.get(name, set()) & used:
                waiting.add(name)
                continue
            batch.append(name)
            used |= files.get(name, set())
        if not batch:                      # a dependency cycle: take the first as it stands
            batch = [pending[0]]
        for name in batch:
            pending.remove(name)
        out.append(batch)
    return out


def run_all(args, ctx=None):
    """`run --all`: one bulk pass. Returns 0, or 2 when the shared files carry unrelated edits."""
    started = time.time()
    canon = registered()
    if ctx is None:
        if not args.dry_run and bulk_guard():
            print("run --all: the index or Code/ or reverse/ has uncommitted edits; commit or set them aside "
                  "first (class commits would include them, a refused commit restores its paths to HEAD)")
            return 2
        blockers = merge_blockers()
        ranked = merge_rank(blockers, canon)
        index = reference_headers()
        ctx = {"blockers": blockers, "ranked": ranked, "rows": class_contract.ledger_rows(),
               "destination": lambda n: header_destination(n, index), "link_check": link_ok,
               "commit": git_commit, "undo": git_undo, "busy": busy_lock_keys}
    ctx.setdefault("dry_run", args.dry_run)
    ctx.setdefault("sample", args.sample)
    ctx.setdefault("seed", args.seed)
    ctx.setdefault("unit_jobs", args.unit_jobs)
    ctx.setdefault("variants", args.variants.split(","))
    ctx.setdefault("trailers", list(args.trailer or ()))
    ctx.setdefault("state_path", BULK_STATE)
    ctx.setdefault("decisions_path", SCRATCH / "decision_queue.dry.jsonl" if args.dry_run else DECISIONS)
    blockers, ranked = ctx["blockers"], ctx["ranked"]
    ctx["info"] = {c: dict(blockers.get(c, {}), score=s, own=o) for c, s, o in ranked}
    order = plan_order(ranked, blockers, canon)
    if args.only:
        order = [c for c in order if c in set(args.only)] + [c for c in args.only if c not in order and c not in canon]
    state = load_state(ctx["state_path"])
    if args.resume:
        order = [c for c in order if state.get(c, {}).get("status") not in BULK_DONE]
    if args.limit:
        order = order[:args.limit]
    if args.jobs > 1:     # every tournament rewrites and restores reverse/functions.csv (try_renamed)
        print("run --all: --jobs runs one class at a time: concurrent tournaments would share "
              "reverse/functions.csv", flush=True)
        args.jobs = 1
    files = census_index(ctx["rows"], order) if args.jobs > 1 else {c: {c} for c in order}
    needs = {c: {base_identity(b) for b in blockers.get(c, {}).get("bases", ())} & set(order) for c in order}
    print(f"run --all: {len(order)} class(es) to try ({'dry run' if ctx['dry_run'] else 'apply'}, "
          f"jobs {args.jobs}, budget {args.budget_min or '-'} min)", flush=True)
    records, tally = {}, collections.Counter()
    for batch in bulk_batches(order, files, needs, max(1, args.jobs)):
        if args.budget_min and time.time() - started > args.budget_min * 60:
            print(f"run --all: budget of {args.budget_min} min spent; resume with --resume", flush=True)
            break
        with cf.ThreadPoolExecutor(max(1, min(args.jobs, len(batch)))) as pool:
            futures = {name: pool.submit(bulk_prepare, name, ctx) for name in batch}
        for name in batch:                 # land in rank order, one commit at a time
            try:
                prepared = futures[name].result()
                if "record" in prepared:
                    status, record, sha = "queued", prepared["record"], None
                elif "would" in prepared:
                    status, record, sha = "would-generate", None, None
                else:
                    status, record, sha = bulk_land(name, prepared, ctx)
            except Exception as exc:  # noqa: BLE001 - one class's failure is a record, not the pass's end
                status, record, sha = "error", decision(name, "error", f"{type(exc).__name__}: {exc}"[:500]), None
            if status == "queued" and record and record["kind"] in TRANSIENT_KINDS:
                status = "claimed" if record["kind"] == "claimed" else "waiting"   # --resume retries both
            records[name] = record
            tally[status] += 1
            state[name] = {"status": status, "at": int(time.time()), **({"commit": sha} if sha else {}),
                           **({"kind": record["kind"]} if record else {})}
            if not ctx["dry_run"]:
                save_state(state, ctx["state_path"])
            line = f"  {name:<32} {status:<15}"
            if record:
                line += f" {record['kind']}: {record['detail'][:120]}"
            if sha:
                line += f" {sha[:10]}"
            print(line, flush=True)
    for name, rec in records.items():
        if rec is not None:
            rec.setdefault("merge_donors", ctx["info"].get(name, {}).get("score", 0))
    adopted = {n for n, s in state.items() if s.get("status") == "adopted"} if not ctx["dry_run"] else set()
    queue_path = Path(ctx["decisions_path"])
    before = queue_path.read_text(encoding="utf-8") if queue_path.exists() else None
    rows = write_decisions(records, ctx["decisions_path"], canon=set(canon) | adopted)
    if not ctx["dry_run"] and queue_path.read_text(encoding="utf-8") != before:
        ok, _, tail = ctx["commit"]([queue_path.relative_to(ROOT).as_posix()],
                                    f"Record {len(rows)} header decision(s) from run --all\n")
        if not ok:
            ctx.get("unstage", git_unstage)([queue_path.relative_to(ROOT).as_posix()])
            print(f"run --all: the hooks refused committing {queue_path.name}; it is left unstaged with this "
                  f"pass's records: fix the cause, then commit it (git add + commit) before --resume: "
                  f"{(tail or '')[-300:]}", flush=True)
            return 1
    print(f"run --all: {dict(tally)}; {len(rows)} record(s) in {Path(ctx['decisions_path']).as_posix()}"
          + ("" if ctx["dry_run"] else "; push, then `header_adopt_lane.py release --class X` for each adopted "
                                       "class and `claims.py release class:X`"), flush=True)
    return 0


def print_destination(name):
    """Where `run --generate` should write `name`'s header, with the evidence, or why not."""
    dest = header_destination(name, reference_headers())
    if dest["header"]:
        print(f"{name}: --header {dest['header']}  ({dest['evidence']})")
        return 0
    print(f"{name}: no destination: {dest['why']}; choose an official BFME path and pass --header PATH")
    return 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("order")
    p.add_argument("--merges", type=int, nargs="?", const=30, metavar="N",
                   help="rank classes by merge donors their canonical header unblocks (top N, default 30)")
    p.add_argument("--refresh", action="store_true", help="recompute the merge-blocker cache")
    p = sub.add_parser("release", help="release the file claims `run --apply` took for a class")
    p.add_argument("--class", dest="name", required=True)
    p = sub.add_parser("dest", help="the official header path for a class's canonical header")
    p.add_argument("--class", dest="name", required=True)
    p = sub.add_parser("refresh-merges", help=argparse.SUPPRESS)   # the picker's detached refresh
    p.add_argument("--lock", required=True)
    p = sub.add_parser("run")
    p.add_argument("--class", dest="name")
    p.add_argument("--all", action="store_true",
                   help="bulk pass over the establish classes in `order --merges` rank (decisions it cannot make "
                        "go to reverse/header_decisions.jsonl)")
    p.add_argument("--only", nargs="+", metavar="CLASS", help="--all: just these classes")
    p.add_argument("--resume", action="store_true", help="--all: skip classes a previous pass adopted or queued")
    p.add_argument("--budget-min", type=float, help="--all: start no class after this many minutes")
    p.add_argument("--limit", type=int, help="--all: try at most N classes")
    p.add_argument("--dry-run", action="store_true", help="--all: decide and report; claim, write and commit nothing")
    p.add_argument("--unit-jobs", type=int, default=max(2, (os.cpu_count() or 4) // 2),
                   help="--all: parallel unit gates inside one class")
    p.add_argument("--trailer", action="append", help="--all: a trailer line for each class commit")
    p.add_argument("--header")
    p.add_argument("--generate", action="store_true", help="generate the header from the contract (tournament)")
    p.add_argument("--variants", default="data,data+ctor,data+methods,data+includes",
                   help="tokens joined by +: data, ctor (inline default ctor), copy (out-of-line copy ctor), methods, includes (headers of registered classes the slots name)")
    p.add_argument("--sample", type=int)
    p.add_argument("--seed", type=int, default=20261006)
    p.add_argument("--jobs", type=int, help="parallel unit gates (one class); with --all, classes run side by side "
                                            "(default 1)")
    p.add_argument("--apply", action="store_true")
    p.add_argument("--skip-held", action="store_true", dest="skip_held",
                   help="--apply: queue the units another worker holds and apply the rest, "
                        "instead of refusing the whole class (a held header still refuses)")
    p = sub.add_parser("accept")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--header")
    p.add_argument("files", nargs="+")
    p = sub.add_parser("adopt", help="adopt a header in named units without registering the class")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--header", required=True)
    p.add_argument("--apply", action="store_true", help="write the units that byte-match")
    p.add_argument("--jobs", type=int, default=1)
    p.add_argument("files", nargs="+")
    p = sub.add_parser("rekey", help="change a registered class's class-key everywhere, in one transaction",
                       description="Change a registered class's class-key everywhere, in one transaction. Not a "
                                   "round trip (the reverse key is refused while retail's exports decide this one; "
                                   "inserted public: lines stay); a second run refuses. A run killed by a signal or "
                                   "power loss leaves rename.py's journal: run `python3 tools/rename.py recover`. "
                                   "The flip is complete only when the rebuilt objects spell no old-key name.")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--key", choices=("class", "struct"), required=True)
    p.add_argument("--dry-run", action="store_true", help="plan and report; write nothing")
    p.add_argument("--report", help="write the plan (respelling map, leftovers) here as JSON: under build/ or "
                                    "outside the repository, never a tracked file")
    p = sub.add_parser("rekey-scan", help="the flip's completion check: no rebuilt object spells the old key")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--key", choices=("class", "struct"), required=True, help="the NEW key")
    p.add_argument("--sources-from", help="sources to check, one per line (default: every matched ledger source); "
                                          "the objects must be freshly rebuilt, which this does not check")
    p = sub.add_parser("gate-cost")
    p.add_argument("--header", required=True)
    p.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) // 2))
    p = sub.add_parser("closure-diff")
    p.add_argument("before")
    p.add_argument("after")
    args = parser.parse_args(argv)
    if args.cmd == "order":
        if args.merges:
            print_merge_order(args.merges, args.refresh)
            return 0
        canon = registered()
        for stage, names in DEPENDENCY_ORDER:
            print(f"{stage}:")
            for name in names:
                print(f"  {name:<14} {len(class_contract.census(name)):5} private views  {canon.get(name, '-')}")
        return 0
    if args.cmd == "release":
        return release_rewrites(args.name)
    if args.cmd == "dest":
        return print_destination(args.name)
    if args.cmd == "refresh-merges":
        try:
            merge_payload(refresh=True)
        finally:
            Path(args.lock).unlink(missing_ok=True)
        return 0
    if args.cmd == "run":
        if args.all:
            args.jobs = args.jobs or 1
            return run_all(args)
        if not args.name:
            parser.error("run needs --class NAME or --all")
        args.jobs = args.jobs or max(2, (os.cpu_count() or 4) // 2)
        return run(args)
    if args.cmd == "accept":
        return accept(args.name, args.files, args.header)
    if args.cmd == "adopt":
        return 1 if adopt(args.name, args.header, args.files, args.apply, args.jobs) else 0
    if args.cmd == "rekey":
        try:
            return apply_class_key(args.name, args.key, args.dry_run, args.report)
        except RekeyRefused as err:
            print(f"class-key {args.name}: REFUSED, nothing written:\n{err}", file=sys.stderr)
            return 2
    if args.cmd == "rekey-scan":
        return rekey_scan(args.name, args.key, args.sources_from)
    if args.cmd == "gate-cost":
        gate_cost(args.header, args.jobs)
        return 0
    return closure_diff(args.before, args.after)


if __name__ == "__main__":
    sys.exit(main())
