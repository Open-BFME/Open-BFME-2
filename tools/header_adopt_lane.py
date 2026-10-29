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
  3. tournament 2-4 header variants (data only, + user default ctor, + the
                views' non-special methods) are each gated against every unit;
                the variant with the most passes is frozen. Byte-equivalent is
                not retail-true: the contract, not the tournament, fixes layout.
  4. codemod    strip the unit's view (and its dependency views, e.g.
                StringBase with AsciiString), #include the header where the
                view stood, and rename the unit's ledger rows when its view
                spelled the other class-key (`U`/`V` mangling).
  5. gate       tools/build.py (BFME2) / build.sh (BFME1) on that one unit,
                in parallel. A batch gate stops at the first compile error.
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
    python3 tools/header_adopt_lane.py gate-cost --header PATH
    python3 tools/header_adopt_lane.py closure-diff BEFORE.csv AFTER.csv
"""
import argparse
import collections
import concurrent.futures as cf
import csv
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
NON_CODE = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?', re.S)


# ---------------------------------------------------------------- source surgery

def masked(text):
    return NON_CODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)


def body_span(text, name):
    """(start, end, key) of the namespace-scope definition of `name`, with a
    `template <...>` line above it and the closing `;` and newline; None if absent."""
    code = masked(text)
    for found, start, index, key in class_layouts.class_body_spans(text, include_templates=True):
        if found != name:
            continue
        tail = re.match(r"[ \t]*;[ \t]*\r?\n?", code[index:])
        if not tail:
            continue
        return start, index + tail.end(), key
    return None


def swap(text, names, include):
    """Text with every view of `names` removed and `include` where the first stood."""
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
    out = text[:first] + f'#include "{include}"\n' + text[first:]
    return out.replace("\0", "")


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
    """The majority declaration among `spellings` (Counter of text), or None on a tie.

    Votes are on the signature with purity; an inline body beats a bare
    declaration of the same signature (units that inline it need the body)."""
    votes = collections.Counter()
    for text, count in spellings.items():
        votes[declaration_key(text)] += count
    top = votes.most_common(2)
    if not top or (len(top) > 1 and top[0][1] == top[1][1]):
        return None
    winners = {t: n for t, n in spellings.items() if declaration_key(t) == top[0][0]}
    best = max(winners, key=lambda t: ("{" in t, winners[t], -len(t)))
    return best if best.endswith(("}", ";")) else best + ";"


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


def slot_declarations(contract, sources, read=None, known=None):
    """([own slot declaration, emit order], [override declaration], [problem]) for the contract's vslots.

    Own slots are the ones the contract decided (a derived contract holds only
    its introductions); a base's slots are never re-emitted, and a view's
    virtual whose name a registered base header declares is an override,
    spelled by majority like an own slot."""
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
            problems.append(f"slot{slot} {member}: " + ("no view spells it" if not spellings else "spellings tie"))
            continue
        decided[slot] = (want[0], rename_destructor(text, short) if want[0] == "~" else text)
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


def generate(contract, variant, methods, header=None, slots=None):
    name, key = contract["class"], contract["key"]
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
    for field in contract["fields"]:
        if field["kind"] == "VPTR":
            continue
        lines.append(f"    {spelled(field['type'], field['name'])};")
    if "ctor" in variant:
        lines.append(f"    {name}() {{}}")
    if "copy" in variant.split("+"):
        # an out-of-line copy constructor: retail calls one (a matched ??0X@@QAE@ABU0@@Z row)
        lines.append(f"    {name}(const {name} &that);")
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
        members = list(methods.values())
        members.sort(key=lambda m: 1 if re.match(r"^\s*(?:\w+\s+)*~\w*\s*\(", m) else 0)
        for member in members:
            lines.append("    " + member.replace("\n", "\n    "))
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


def ledger_renames(source, name, want_key):
    """[(old, new)] for the unit's row names that mangle the other class-key."""
    have, other = ("U", "V") if want_key == "struct" else ("V", "U")
    scope = class_contract.mangled_scope(name)
    pattern = re.compile(other + re.escape(scope) + r"@@")
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        return [(r["name"], pattern.sub(have + scope + "@@", r["name"])) for r in csv.DictReader(handle)
                if r["source"] == source and pattern.search(r["name"])]


def rewrite_ledger(renames):
    if not renames:
        return
    table = dict(renames)
    text = LEDGER.read_text(encoding="utf-8")
    lines = text.splitlines(keepends=True)
    for i, line in enumerate(lines):
        first = line.split(",", 1)[0]
        if first in table:
            lines[i] = table[first] + line[len(first):]
    LEDGER.write_text("".join(lines), encoding="utf-8", newline="")


def try_unit(source, strip, header, key):
    """(source, None | why, new text, renames). Restores the unit before returning."""
    path = ROOT / source
    original = path.read_bytes()
    text = original.decode("latin-1")
    span = body_span(text, strip[0])
    view_key = span[2] if span else key
    swapped = swap(text, strip, include_spelling(source, header))
    if swapped is None:
        return source, "no private view found", None, []
    renames = ledger_renames(source, strip[0], key) if view_key != key else []
    if renames:
        return source, f"class-key {view_key}: {len(renames)} ledger rename(s) needed", swapped, renames
    try:
        path.write_bytes(swapped.encode("latin-1"))
        why = gate_one(source)
    finally:
        path.write_bytes(original)
    return source, why, swapped, renames


def try_renamed(items, jobs):
    """Units whose view spelled the other class-key: rename their ledger rows and gate,
    serially in one ledger state (the ledger is shared by all of them)."""
    results = {}
    if not items:
        return results
    backup = LEDGER.read_bytes()
    try:
        rewrite_ledger([r for _, _, _, renames in items for r in renames])
        originals = {s: (ROOT / s).read_bytes() for s, _, _, _ in items}
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


def tournament(name, contract, sources, header, variants, jobs, fixed_header=False):
    strip = [name] + STRIP_WITH.get(name, [])
    nested = {f["kind"][2:] for f in contract["fields"] if f["kind"].startswith("S:")} & set(registered())
    methods = view_methods(name, sources, nested) if not fixed_header else {}
    slots = None
    if not fixed_header and contract.get("vslots"):
        own, overrides, _ = slot_declarations(contract, sources)
        slots = (own, overrides)
    results = {}
    keep = (ROOT / header).read_bytes() if (ROOT / header).exists() else None
    for variant in variants:
        if not fixed_header:
            (ROOT / header).parent.mkdir(parents=True, exist_ok=True)
            (ROOT / header).write_text(generate(contract, variant, methods, header, slots), encoding="utf-8",
                                       newline="\n")
        started = time.time()
        with cf.ThreadPoolExecutor(jobs) as pool:
            got = list(pool.map(lambda s: try_unit(s, strip, header, contract["key"]), sources))
        renamed = [g for g in got if g[3]]
        fixed = try_renamed(renamed, jobs)
        verdicts = {s: (fixed[s] if s in fixed else why) for s, why, _, _ in got}
        results[variant] = {"verdicts": verdicts, "texts": {s: t for s, _, t, _ in got},
                            "renames": {s: r for s, _, _, r in got if r}, "seconds": time.time() - started,
                            "header": (ROOT / header).read_text(encoding="utf-8") if (ROOT / header).exists() else ""}
        passes = sum(v is None for v in verdicts.values())
        print(f"  variant {variant:<14} {passes}/{len(sources)} pass  ({results[variant]['seconds']:.0f}s)", flush=True)
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
    if not (ROOT / "tools" / "link_check.py").exists():
        return {s: None for s in sources}
    done = subprocess.run([sys.executable, "tools/link_check.py", *sources], cwd=ROOT, capture_output=True,
                          text=True, errors="replace", env=dict(os.environ, MSYS_NO_PATHCONV="1"))
    if done.returncode not in (0, 1):
        return {s: None for s in sources}
    out = done.stdout + done.stderr
    results = {}
    for source in sources:
        normalized = (ROOT / source).resolve().relative_to(ROOT.resolve()).as_posix()
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


def includes_header(source, header):
    """Does `source` really #include `header`: a directive outside comments and `#if 0`
    branches whose spelling resolves beside the source to that file, or is a path
    suffix of it no other tracked header shares? A basename in a comment, or a
    same-named header elsewhere, is not it."""
    text = without_disabled(COMMENTS.sub(lambda m: re.sub(r"[^\n]", " ", m.group()),
                                         (ROOT / source).read_text(encoding="latin-1")))
    header = header.replace("\\", "/")
    want = (ROOT / header).resolve()
    others = None
    for spelled in INCLUDE.findall(text):
        spelled = spelled.strip().replace("\\", "/")
        if ((ROOT / source).parent / spelled).resolve() == want:
            return True
        tail = "/" + spelled.lstrip("./")
        if ("/" + header).endswith(tail):
            if others is None:
                others = tracked_headers()
            if not [p for p in others if ("/" + p).endswith(tail) and p != header]:
                return True
    return False


def verdict(name, source, header=None, gate=None):
    """[problems] of one unit's adoption of `name`'s canonical header ([] = adopted)."""
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
                for companion in companions)):
        problems.append(f"does not #include {header}")
    why = (gate or gate_one)(source)
    if why:
        problems.append(why)
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
    bad, done = 0, set()
    for source in sources:
        problems = verdict(name, source, header, gate)
        print(f"  {'PASS' if not problems else 'FAIL'} {source}" + ("" if not problems else ": " + "; ".join(problems)))
        bad |= bool(problems)
        if not problems:
            done.add((name, source))
    retired = retire_rows(done)
    if retired:
        print(f"  retired {retired} row(s) from {QUEUE.relative_to(ROOT).as_posix()}; commit it with the adoption")
    return bad


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
    variants = args.variants.split(",") if not fixed else ["registered"]
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
        if held:
            print(f"  refusing to apply: {len(held)} file(s) another worker holds: " + "; ".join(
                f"{key} ({who})" for key, who in held[:8]) + (" ..." if len(held) > 8 else ""))
            return 3
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
DECIDABLE = ("undecided", "slot-undeclarable", "no-destination", "no-unit-adopts", "link-regression",
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
    wanted, out = set(names), {n: {n} for n in names}
    sources = sorted({r["source"] for r in rows if r["source"].lower().endswith((".cpp", ".c"))
                      and not r["source"].startswith(class_contract.GENERATED)})
    for source in sources:
        try:
            text = (ROOT / source).read_text(encoding="latin-1")
        except OSError:
            continue
        for name in set(class_layouts.class_bodies(text)) & wanted:
            out[name].add(source)
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
    p = sub.add_parser("accept")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--header")
    p.add_argument("files", nargs="+")
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
    if args.cmd == "gate-cost":
        gate_cost(args.header, args.jobs)
        return 0
    return closure_diff(args.before, args.after)


if __name__ == "__main__":
    sys.exit(main())
