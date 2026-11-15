#!/usr/bin/env python3
"""List functions defined in source files that are not yet in functions.csv."""

import csv
import argparse
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = ROOT / "src"
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
DATA_ROWS_CSV = ROOT / "reverse" / "data_rows.csv"
CLAIMS_WHITELIST = ROOT / "reverse" / "unclaimed_sources_whitelist.txt"

# `// <label> present-unmatched` / `// <label> absent-from-retail` definition markers
UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(present-unmatched|absent-from-retail)\b", re.MULTILINE
)

# Ignore punctuation inside comments and literals while finding the end of a
# signature. The retail compiler predates C++ raw string literals.
SIGNATURE_TOKEN_RE = re.compile(
    r'''//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|[(){};]'''
)


def is_declaration_or_call(text, after_open_paren):
    """Exclude prototypes and calls with an enclosing expression parenthesis.

    Keep ambiguous/incomplete signatures as definition candidates: this only
    excludes a prototype when its terminating semicolon is actually seen.
    A closing parenthesis beyond the balanced parameter list belongs to an
    enclosing expression, such as a wrapped if condition, never a definition.
    """
    depth = 1
    for match in SIGNATURE_TOKEN_RE.finditer(text, after_open_paren):
        token = match.group()
        if token == "(":
            depth += 1
        elif token == ")" and depth:
            depth -= 1
        elif depth == 0:
            if token in (";", ")"):
                return True
            if token == "{":
                return False
    return False


def load_claims_whitelist():
    if not CLAIMS_WHITELIST.exists():
        return set()
    return {
        line.strip()
        for line in CLAIMS_WHITELIST.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }

# MSVC operator mangling codes for common operators.
OPERATOR_CODES = {
    "operator=": "??4",
    "operator==": "??8",
    "operator!=": "??9",
    "operator<": "??M",
    "operator<=": "??N",
    "operator>": "??O",
    "operator>=": "??P",
    "operator+": "??H",
    "operator-": "??G",
    "operator*": "??D",
    "operator/": "??K",
    "operator+=": "??Y",
    "operator-=": "??Z",
    "operator*=": "??X",
    "operator/=": "??_0",
    "operator<<": "??6",
    "operator>>": "??5",
    "operator[]": "??A",
    "operator()": "??R",
    "operator++": "??E",
    "operator--": "??F",
    "operator~": "??1",  # destructor is also ??1; handled separately
}


def git_show(path: Path):
    result = subprocess.run(
        ["git", "show", f":{path.as_posix()}"],
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
    )
    if result.returncode != 0:
        return None
    return result.stdout


def read_function_names(path: Path, staged: bool):
    text = git_show(path.relative_to(ROOT)) if staged else None
    if text is None:
        text = path.read_text(encoding="utf-8")
    declared = set()
    matched = set()
    matched_by_source = {}
    matched_sources = {}
    for row in csv.DictReader(text.splitlines()):
        declared.add(row["name"])
        if row["status"] == "matched":
            matched.add(row["name"])
            matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
            matched_sources.setdefault(row["name"], set()).add(row["source"])
    return declared, matched, matched_by_source, matched_sources


def read_data_row_sources(path: Path, staged: bool):
    """Sources of matched data_rows.csv rows (one entry per row), staged or on disk
    (Open-BFME-1's data-only TU handling)."""
    text = git_show(path.relative_to(ROOT)) if staged else (
        path.read_text(encoding="utf-8") if path.exists() else None)
    if not text:
        return []
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import data_rows
    return [row["source"] for _, row in data_rows.parse(text.encode("utf-8"))
            if row.get("status") == "matched"]


def mangle_method(class_name: str, method_name: str) -> str:
    """Return a rough MSVC mangled-name substring to search for.

    Constructors use ??0, destructors use ??1, operator= uses ??4,
    and ordinary methods use ?name@Class@Namespace@@.
    class_name may be qualified (e.g. "FXParticleSystem::ButterflyDrawModuleInfo").
    """
    parts = class_name.split("::")
    if method_name == parts[-1]:
        prefix = "??0"
    elif method_name == f"~{parts[-1]}":
        prefix = "??1"
    elif method_name in OPERATOR_CODES:
        prefix = OPERATOR_CODES[method_name]
    else:
        prefix = f"?{method_name}"
    mangled_class = "@".join(reversed(parts))
    # Constructors, destructors and operators attach directly to the class name;
    # ordinary methods are separated from the class by an @.
    if prefix.startswith("?") and not prefix.startswith("??"):
        return f"{prefix}@{mangled_class}@@"
    return f"{prefix}{mangled_class}@@"


def find_defined_functions(text: str, *, inline_candidates=None, definition_counts=None):
    # Match definitions like:
    #   ReturnType ClassName::methodName(
    #   Namespace::ClassName::methodName(
    #   ClassName::ClassName(
    #   ClassName::~ClassName(
    definition_pattern = re.compile(
        r"^[\w:&*~\s]*?((?:\w+::)*\w+)::(operator[\s=\+\-\*/\[\]\(\)<>!]+|\~?\w+)\s*\(",
        re.MULTILINE,
    )
    namespace_pattern = re.compile(r"\bnamespace\s+(\w+)\s*\{")

    results = set()
    symbol_comment = None
    # Stack of (namespace_name, brace_depth_at_open). Anonymous namespaces use "".
    namespace_stack = []
    brace_depth = 0

    in_macro = False
    # splitlines() breaks on a LONE carriage return as well as on CRLF, so a
    # file written with doubled carriage returns (CR CR LF -- what a text-mode
    # write over content that already ended in CRLF produces) yields a PHANTOM
    # EMPTY LINE after every real one. An empty line does not end in a
    # backslash, so it silently clears in_macro and the remainder of the macro
    # body is then read as ordinary code. Fourteen such files made this checker
    # report a class called NAME and fail a commit. Normalise first: the parse
    # below cares about lines, not about how they were terminated.
    normalized = text.replace("\r\n", "\n").replace("\r", "\n")
    specifier_text = re.sub(
        r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"',
        lambda m: re.sub(r"[^\n]", " ", m.group()), normalized
    ) if inline_candidates is not None else ""
    next_line_offset = 0
    for line in normalized.split("\n"):
        line_offset = next_line_offset
        next_line_offset += len(line) + 1
        stripped = line.strip()
        # A function definition written inside a #define body is not a
        # definition -- it is macro text, and the identifiers in it are
        # parameters. FunctorBindConstructors.cpp generates 82 constructors from
        # one macro whose body reads `NAME::NAME( ... )`, and this checker read
        # that literally and failed the commit for a class called NAME. Track
        # backslash continuations and skip the whole macro body; the functions
        # the macro EXPANDS to are declared in the ledger under their real names.
        was_macro = in_macro
        if stripped.startswith("#define"):
            in_macro = line.rstrip().endswith("\\")
        elif in_macro:
            in_macro = line.rstrip().endswith("\\")
        if was_macro or stripped.startswith("#define"):
            continue
        # A MEMBER-INITIALISER LIST is not a definition. A constructor written
        #     Derived::Derived(const Derived &other)
        #         : std::exception(other)
        # puts `std::exception(other)` on its own line, which matches the same
        # Qualified::name( shape a definition has -- so the checker reported a
        # function called `std::exception` and failed the commit. Initialiser
        # entries always begin with the ':' that opens the list or the ',' that
        # continues it, and a real definition never starts a line with either.
        if stripped.startswith((":", ",")) and not stripped.startswith("::"):
            continue
        if stripped.startswith("// ?"):
            # Only a real ANNOTATION may bind to the next definition. Two forms
            # exist in this tree: a bare mangled name (3305 of them), and a name
            # followed by present-unmatched / absent-from-retail (11104). A third
            # thing also starts with "// ?" -- ordinary PROSE that happens to open
            # with a mangled name, 109 of those, e.g.
            #   // ??_GCrateTemplate 0x0037A2F0 -> 0x0002FC70 -> 0x00379EC0.
            # Binding prose to the following definition made this checker report
            # CrateTemplate::~CrateTemplate as undeclared when its row exists and
            # matches, failing a commit for a correctly declared destructor. Prose
            # is now ignored rather than captured, and the pending annotation is
            # cleared so a stale one cannot leak past it.
            candidate = stripped[3:].strip()
            parts = candidate.split()
            # `// ?<mangled>,` -- a ledger row's name pasted with its trailing
            # separator -- names the same symbol; the comma is not part of it.
            if parts and parts[0].endswith(","):
                parts[0] = parts[0].rstrip(",")
                candidate = " ".join(parts)
            # A vftable is data, never the following function's annotation.
            # Consolidation can lift a trailing vftable comment off an extern
            # declaration. Clear pending markers too: data cannot excuse a body.
            if parts and parts[0].startswith("??_7"):
                symbol_comment = None
            elif len(parts) == 1 or (len(parts) >= 2 and parts[1] in
                                   ("present-unmatched", "absent-from-retail")):
                symbol_comment = candidate
            else:
                symbol_comment = None
            continue
        is_namespace_line = (stripped.startswith("namespace ") or stripped.startswith("namespace\t")
                             or stripped.startswith("namespace {")
                             or re.match(r'extern\s+"C(?:\+\+)?"\s*\{', stripped) is not None)
        # Brace depth of the innermost namespace (or extern "C" block) this line
        # sits in. An out-of-class Qualified::name definition only ever appears
        # at that depth; deeper means inside a function or class body.
        floor = namespace_stack[-1][1] if namespace_stack else 0
        in_block = brace_depth > floor

        open_count = line.count("{")
        close_count = line.count("}")

        if is_namespace_line:
            match = namespace_pattern.search(line)
            ns_name = match.group(1) if match else ""
            # The namespace opens at the next unmatched brace depth.
            namespace_stack.append((ns_name, brace_depth + 1))

        brace_depth += open_count - close_count

        # Close any namespaces whose opening brace has now been matched.
        while namespace_stack and namespace_stack[-1][1] > brace_depth:
            namespace_stack.pop()

        # Inspect the complete signature: prototypes can span lines, and a
        # definition's first line can end with a semicolon inside a comment.
        match = definition_pattern.match(line)
        if match and is_declaration_or_call(normalized, line_offset + match.end()):
            match = None
            symbol_comment = None
        # A call wrapped across lines -- `Bar::call(a,` inside a body -- ends in
        # ',' like a wrapped definition signature does. Brace counting alone
        # cannot tell them apart (braces in strings and #if branches skew it, and
        # trusting it hid real definitions in W3DRoadBuffer.cpp), so a line is
        # read as a call only when it is also indented: every out-of-class
        # definition in this tree starts its signature in column 0.
        if match and stripped.endswith(",") and in_block and line[:1] in (" ", "\t"):
            match = None
            symbol_comment = None  # a marker written over the call named the call
        if match:
            class_name = match.group(1)
            method_name = match.group(2)
            if method_name.startswith("operator"):
                # normalize "operator ()" / "operator() " to "operator()"
                method_name = "operator" + re.sub(r"\s+", "", method_name[len("operator"):])
            if namespace_stack and "::" not in class_name:
                # Filter out anonymous namespace entries.
                ns_parts = [ns for ns, _ in namespace_stack if ns]
                class_name = "::".join(ns_parts + [class_name])
            definition = (class_name, method_name, symbol_comment)
            results.add(definition)
            if definition_counts is not None:
                key = (class_name, method_name)
                definition_counts[key] = definition_counts.get(key, 0) + 1
            if inline_candidates is not None:
                # MSVC's dllimport/forceinline specializations may have no
                # separate body at all. Keep them in the ordinary inventory;
                # only a current object can prove that they were inline-only.
                end = line_offset + match.start(1)
                prefix = specifier_text[max(0, end - 1024):end]
                if re.search(
                        r'\btemplate\s*<\s*>\s*__declspec\s*\(\s*dllimport\s*\)'
                        r'\s*__forceinline\s+[\w\s:&*<>,]*\Z', prefix):
                    inline_candidates.add(definition)
            symbol_comment = None
    return results


def inline_type_identifiers(text, class_name):
    """Necessary record names for a narrowly understood typedef specialization.

    These are exclusion witnesses, not a mangler: sharing every name does not
    prove equality. Unknown/ambiguous aliases and dependent types yield no
    witness, so the object check remains conservative.
    """
    code = re.sub(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"', ' ', text)
    aliases = {}
    for match in re.finditer(r'\btypedef\s+([\w\s:*<>,]+?)\s+(\w+)\s*;', code):
        aliases.setdefault(match[2], []).append(match[1])
    expanded = {}

    def expand(name, active=()):
        if name in expanded:
            return expanded[name]
        if name in active or len(active) > 20 or len(aliases.get(name, [])) != 1:
            raise ValueError("unresolved typedef")
        expression = aliases[name][0]
        expression = re.sub(r'\b\w+\b', lambda m: (
            expand(m[0], (*active, name)) if m[0] in aliases else m[0]), expression)
        if "::value_type" in expression:
            # STLport 4.6 _hash_map.h: hash_map<K,V,...>::value_type is
            # pair<const K,V>. No general dependent-member inference is safe.
            match = re.fullmatch(r'\s*_STL::hash_map\s*<(.*)>\s*::value_type\s*', expression,
                                 re.DOTALL)
            if not match:
                raise ValueError("unknown dependent type")
            args, start, depth = [], 0, 0
            for i, char in enumerate(match[1]):
                if char == '<':
                    depth += 1
                elif char == '>':
                    depth -= 1
                elif char == ',' and depth == 0:
                    args.append(match[1][start:i])
                    start = i + 1
            args.append(match[1][start:])
            if depth != 0 or len(args) < 2:
                raise ValueError("incomplete hash_map type")
            expression = f'_STL::pair<const {args[0]}, {args[1]}>'
        if (re.search(r'>\s*::|\b(?!_STL\b|rts\b)\w+\s*::', expression)
                or len(expression) > 20000):
            raise ValueError("unknown dependent type")
        expanded[name] = expression
        return expression

    try:
        expression = expand(class_name.split("::")[-1])
    except ValueError:
        return set()
    records = set(re.findall(r'\b(?:class|struct|enum)\s+(\w+)\s*[;:{]', code))
    return records & set(re.findall(r'\b\w+\b', expression))


def inline_only_definitions(source, text, candidates):
    """Prove absence of both emitted bodies and imports, never trust inline syntax.

    The receipt must cover the exact inspected text, flags, headers and include
    search inventory. In staged mode a different working copy cannot supply the
    proof. Search by method name across all class spellings: the source may use
    a typedef, whereas COFF always names the underlying specialization.
    """
    if not candidates or source.read_text(encoding="utf-8") != text:
        return set()
    import build
    import json
    import struct
    obj = build.obj_path(source)
    try:
        if not build.compile_is_current(source, obj, strict=True):
            return set()
        before = obj.stat()
        names = [symbol["name"] for symbol in build.read_object_symbols(obj.read_bytes())]
        required_by_definition = {d: inline_type_identifiers(text, d[0]) for d in candidates}
        # A raw source identifier is no witness if preprocessing could rename
        # it. Check all recorded headers and command-line definitions too.
        if any(required_by_definition.values()):
            meta = json.loads(obj.with_suffix(".deps.json").read_text())
            dependencies = [Path(p) if os.path.isabs(p) else ROOT / p for p in meta["deps"]]
            macros = set()
            for path in [source, *dependencies]:
                contents = path.read_text(encoding="utf-8", errors="replace")
                contents = re.sub(r'(?:\\|\?\?/)[\r]?\n', '', contents)
                macros.update(re.findall(r'^\s*#\s*define\s+(\w+)',
                                         contents, re.MULTILINE))
            command, _ = build.compiler_command(source, obj)
            macros.update(m[1] for arg in command
                          if (m := re.match(r'[-/]D([A-Za-z_]\w*)', arg)))
            required_by_definition = {d: required - macros
                                      for d, required in required_by_definition.items()}
        if obj.stat() != before or not build.compile_is_current(source, obj, strict=True):
            return set()
    except (OSError, ValueError, KeyError, struct.error):
        return set()
    proved = set()
    for definition in candidates:
        cls, method, _ = definition
        if not re.fullmatch(r"[A-Za-z_]\w*", method) or method == cls.split("::")[-1]:
            continue
        required = required_by_definition[definition]
        if not any(f"?{method}@" in name and all(record in name for record in required)
                   for name in names):
            proved.add(definition)
    return proved


def folded_lifetime_definitions(source, text, candidates, counts, staged=False):
    """Recognize pinned lifetime bodies only after the complete ICF proof.

    A pin is an address candidate, never evidence. Reuse admission's byte,
    relocation, identity and associative-EH proof against this current object.
    The inventory does not resolve overload signatures, so ambiguous source
    definitions or emitted overloads cannot borrow each other's proof.
    """
    candidates = {d for d in candidates if counts.get(d[:2]) == 1
                  and d[1] in (d[0].split("::")[-1], "~" + d[0].split("::")[-1])}
    if not candidates:
        return set()
    import build
    import pin_admission
    import struct
    proved = set()
    try:
        if source.read_text(encoding="utf-8") != text:
            return set()
        # The prover reads working-tree ledgers. They must be the very ledgers
        # being committed, not unstaged pins or rows supplying hidden evidence.
        paths = (FUNCTIONS_CSV, ROOT / "reverse/symbols.csv")
        ledger_texts = [p.read_text(encoding="utf-8-sig") for p in paths]
        if staged and any(git_show(p.relative_to(ROOT)) != contents
                          for p, contents in zip(paths, ledger_texts)):
            return set()
        rows, pins = [list(csv.DictReader(contents.splitlines())) for contents in ledger_texts]
        obj = build.obj_path(source)
        if not build.compile_is_current(source, obj, strict=True):
            # Ordinary build receipts do not include the search inventory.
            # Ask the official compile path to establish it, never promote an
            # ordinary receipt or infer currency from a successful compile.
            build.compile_rows([r for r in rows if r.get("source") == source.relative_to(ROOT).as_posix()],
                               [source], strict=True)
        if not build.compile_is_current(source, obj, strict=True):
            return set()
        before = obj.read_bytes()
        symbols = build.read_object_symbols(before)
        symbol_map = None
        for definition in candidates:
            cls, method, annotation = definition
            prefix = mangle_method(cls, method)
            emitted = [s["name"] for s in symbols if s["name"].startswith(prefix)
                       and s["section"] > 0 and s["storage"] == 2]
            if len(emitted) != 1 or (annotation and annotation != emitted[0]):
                continue
            name = emitted[0]
            addresses = {int(p["address"], 16) for p in pins if p["name"] == name}
            if len(addresses) != 1:
                continue
            if symbol_map is None:
                symbol_map = build.load_symbol_map()
            receipt = {}
            problems = pin_admission.fold_proof_problems(
                {"name": name, "notes": "fold-proof=" + source.relative_to(ROOT).as_posix()},
                next(iter(addresses)), rows, lambda: symbol_map, pins=pins,
                receipt=receipt, allow_weak=False)
            if (not problems and Path(receipt.get("output", "")).resolve() == obj.resolve()
                    and receipt.get("bindings", {}).get(name) == next(iter(addresses))):
                proved.add(definition[:2])
        if (obj.read_bytes() != before or source.read_text(encoding="utf-8") != text
                or not build.compile_is_current(source, obj, strict=True)
                or any(p.read_text(encoding="utf-8-sig") != contents
                       for p, contents in zip(paths, ledger_texts))):
            return set()
    except (OSError, ValueError, KeyError, IndexError, struct.error, SystemExit):
        return set()
    return proved


def inventory_code(text):
    """Remove comments/literals without moving directive or definition offsets."""
    return re.sub(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda m: re.sub(r'[^\r\n]', ' ', m[0]), text)


def mask_modern_branches(text):
    """Only the positive, standalone modern guard is known; all else stays visible.

    This is candidate selection, NOT proof that the macro was undefined. Malformed
    or spliced input is kept in full. Ordinary #if 0/debug/unknown branches retain
    the inventory's existing policy.
    """
    if re.search(r'\\\r?\n|\?\?/', text):
        return text
    stack, result = [], []
    code_lines = inventory_code(text).splitlines(keepends=True)
    lines = text.splitlines(keepends=True)
    for line, code in zip(lines, code_lines):
        directive = re.match(r'^\s*#\s*(\w+)\b(.*)', code)
        hidden = any(stack)
        if directive:
            kind, condition = directive[1], directive[2].strip()
            if kind in ('if', 'ifdef', 'ifndef'):
                stack.append((kind == 'ifdef' and condition == 'BFME2_MODERN') or
                             (kind == 'if' and re.fullmatch(
                                 r'defined\s*\(\s*BFME2_MODERN\s*\)', condition) is not None))
            elif kind in ('else', 'elif'):
                if not stack:
                    return text
                stack[-1] = False
            elif kind == 'endif':
                if not stack:
                    return text
                stack.pop()
        result.append(re.sub(r'[^\r\n]', ' ', line) if hidden else line)
    return text if stack else ''.join(result)


def modern_only_definitions(source, text):
    """Exclude modern-only bodies only with current reference COFF evidence.

    Never trust a guard alone. The exact source, headers and include inventory
    must be current, the guard/type/method names must not be macros, and the
    reference object must contain neither definitions nor references of the class.
    Ambiguity leaves the ordinary inventory refusal intact.
    """
    masked = mask_modern_branches(text)
    # Masking may attach an earlier symbol comment to the next reference body.
    # Annotation changes are not evidence that a definition disappeared.
    reference_names = {(cls, method) for cls, method, _ in find_defined_functions(masked)}
    candidates = {d for d in find_defined_functions(text) if d[:2] not in reference_names}
    candidates = {d for d in candidates if re.fullmatch(r'[A-Za-z_]\w*', d[0])}
    if not candidates or source.read_text(encoding='utf-8') != text:
        return set()
    if os.environ.get('CL') or os.environ.get('_CL_'):
        return set()
    import build
    import json
    import struct
    obj = build.obj_path(source)
    try:
        if not build.compile_is_current(source, obj, strict=True):
            return set()
        object_data = obj.read_bytes()
        names = [s['name'] for s in build.read_object_symbols(object_data)]
        meta = json.loads(obj.with_suffix('.deps.json').read_text())
        dependencies = [Path(p) if os.path.isabs(p) else ROOT / p for p in meta['deps']]
        macros = set()
        for path in [source, *dependencies]:
            contents = path.read_text(encoding='utf-8', errors='replace')
            contents = re.sub(r'(?:\\|\?\?/)[\r]?\n', '', contents)
            macros.update(re.findall(r'^\s*#\s*define\s+(\w+)',
                                     inventory_code(contents), re.MULTILINE))
        command, _ = build.compiler_command(source, obj)
        for i, arg in enumerate(command):
            arg = str(arg).replace('"', '')
            if arg.startswith('@'):
                return set()  # Extra response-file definitions are not witnessed here.
            if arg in ('/D', '-D') and i + 1 < len(command):
                arg += str(command[i + 1]).replace('"', '')
            match = re.match(r'[-/]D([A-Za-z_]\w*)', arg)
            if match:
                macros.add(match[1])
        if ('BFME2_MODERN' in macros or obj.read_bytes() != object_data or
                not build.compile_is_current(source, obj, strict=True)):
            return set()
    except (OSError, ValueError, KeyError, struct.error):
        return set()
    return {d for d in candidates if not ({d[0], d[1].lstrip('~')} & macros)
            and not any(d[0] in name for name in names)}


def read_path_list(name):
    """Paths listed in file `name` ('-': stdin), NUL-separated if it holds a NUL, else one per line."""
    data = sys.stdin.buffer.read() if name == "-" else Path(name).read_bytes()
    if b"\0" in data:
        entries = data.split(b"\0")
    else:
        entries = [line.rstrip(b"\r") for line in data.split(b"\n")]
    return [os.fsdecode(entry) for entry in entries if entry]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="*", help="source files to inspect; defaults to every src/*.cpp")
    parser.add_argument("--fail", action="store_true", help="exit non-zero when unmatched functions are found")
    parser.add_argument("--staged", action="store_true", help="read paths from the git index")
    parser.add_argument("--paths-from", metavar="FILE",
                        help="also inspect the NUL- or newline-separated paths in FILE ('-': stdin); "
                             "the pre-commit hook passes its list this way because Windows caps a "
                             "command line at 32,767 characters")
    args = parser.parse_args()
    if args.paths_from:
        args.paths += read_path_list(args.paths_from)

    declared, matched, matched_by_source, matched_sources = read_function_names(FUNCTIONS_CSV, args.staged)
    whitelist = load_claims_whitelist()
    # a data-only TU owns its globals in data_rows.csv (tools/data_rows.py, byte-verified by the gate)
    for source in read_data_row_sources(DATA_ROWS_CSV, args.staged):
        matched_by_source[source] = matched_by_source.get(source, 0) + 1

    unmatched = []
    violations = []
    # An empty --paths-from list inspects nothing, never the default tree.
    source_paths = ([ROOT / path for path in args.paths] if args.paths or args.paths_from
                    else sorted(SRC_DIR.rglob("*.cpp")))
    staged_text = {}
    if args.staged:
        # One `git show` per file: 1,500 staged sources took minutes one at a time.
        # Fetch concurrently; everything below still runs in the given order.
        rel_paths = [p.relative_to(ROOT) for p in source_paths if p.suffix == ".cpp"]
        with ThreadPoolExecutor(max_workers=min(8, os.cpu_count() or 1)) as pool:
            staged_text = dict(zip(rel_paths, pool.map(git_show, rel_paths)))
    for source_path in source_paths:
        if source_path.suffix != ".cpp":
            continue
        rel_path = source_path.relative_to(ROOT)
        if args.staged:
            text = staged_text[rel_path]
            if text is None:
                continue
        else:
            text = source_path.read_text(encoding="utf-8")

        # Claims gate: a source file with ZERO byte-verified rows is not progress —
        # a wall of present-unmatched markers must not be committable as if it were.
        marker_labels = UNMATCHED_MARKER_RE.findall(text)
        file_matched = matched_by_source.get(rel_path.as_posix(), 0)
        if file_matched == 0 and rel_path.as_posix() not in whitelist:
            violations.append(
                f"{rel_path}: ZERO matched functions.csv / data_rows.csv rows — match at least one "
                f"function before committing this file, or whitelist it with a reason "
                f"(reverse/unclaimed_sources_whitelist.txt)"
            )
        own_names = {n for n, srcs in matched_sources.items()
                     if rel_path.as_posix() in srcs}
        label_counts = {}
        for label, _m in marker_labels:
            label_counts[label] = label_counts.get(label, 0) + 1
        for label, marker in marker_labels:
            # matched from ANOTHER file is correct bookkeeping (asm-whale scaffolds
            # claim symbols the verbatim ZH copy also defines); matched from THIS
            # file means the marker is stale
            if rel_path.as_posix() not in matched_sources.get(label, ()):
                # An abbreviated label -- `??0OutputStream@@` standing in for
                # `??0OutputStream@DebugIOFlat@@AAE@PBDI@Z` -- never equals a
                # ledger name, so the exact test above cannot fire. Every stale
                # marker in this tree is of that form, which is exactly why this
                # check had never reported one. Resolve by prefix instead, but
                # only when the answer is unambiguous: one marker carrying the
                # label, and one matched row it could mean. Overloads share an
                # abbreviated label -- ?isPlayer@GameSlot@@ appears three times
                # in GameInfo.cpp -- and claiming one says nothing about the
                # others, so a count mismatch is not evidence about any of them.
                key = label[:-2] if label.endswith("@@") else label
                cand = [n for n in own_names if n.startswith(key + "@")]
                if len(cand) != 1 or label_counts[label] != 1:
                    continue
                label = cand[0]
            if rel_path.as_posix() in matched_sources.get(label, ()):
                violations.append(
                    f"{rel_path}: {label} is matched in functions.csv from this file but "
                    f"still marked {marker} (stale annotation — remove the marker)"
                )
        if args.paths and marker_labels:
            print(
                f"note: {rel_path}: {file_matched} matched row(s), "
                f"{len(marker_labels)} unclaimed definition(s)"
            )

        inline_candidates = set()
        definition_counts = {}
        definitions = find_defined_functions(text, inline_candidates=inline_candidates,
                                             definition_counts=definition_counts)
        inline_only = inline_only_definitions(source_path, text, inline_candidates)
        unmatched_start = len(unmatched)
        modern_only = modern_only_definitions(source_path, text)
        for class_name, method_name, symbol_name in definitions:
            if (class_name, method_name, symbol_name) in inline_only | modern_only:
                continue
            if symbol_name:
                # `// ?<mangled> absent-from-retail` marks a definition kept only to
                # force emission/instantiation of other matched functions; the retail
                # binary dead-stripped it, so there is no address for a CSV row.
                parts = symbol_name.split()
                if len(parts) >= 2 and parts[1] in ("absent-from-retail", "present-unmatched"):
                    # absent-from-retail: definition kept only to force emission of
                    # matched siblings; the retail binary dead-stripped it.
                    # present-unmatched: the function exists in retail but its bytes
                    # or address are not yet pinned; kept because trimming it would
                    # change inlining of matched functions in this TU.
                    continue
                if symbol_name in declared:
                    continue
                unmatched.append((rel_path, class_name, method_name))
                continue

            needle = mangle_method(class_name, method_name)
            # The namespace tracker below loses its stack in very large files, so
            # class_name can arrive unqualified for a symbol whose real decorated
            # name carries a namespace: ??4EmissionVolumeInfo@FXParticleSystem@@
            # against a needle of ??4EmissionVolumeInfo@@. Trimming one '@' off
            # the terminator lets the qualified form match, and cannot widen the
            # class itself -- the trailing '@' still has to follow it exactly.
            open_needle = needle[:-1]
            # Constructors/destructors match a prefix; ordinary methods match a substring.
            if needle.startswith("??0") or needle.startswith("??1"):
                if any(name.startswith(open_needle) for name in matched):
                    continue
            else:
                if any(open_needle in name for name in matched):
                    continue
            unmatched.append((rel_path, class_name, method_name))

        pending = {(cls, method) for _, cls, method in unmatched[unmatched_start:]}
        folds = folded_lifetime_definitions(
            source_path, text, {d for d in definitions if d[:2] in pending},
            definition_counts, staged=args.staged)
        unmatched[unmatched_start:] = [entry for entry in unmatched[unmatched_start:]
                                      if entry[1:] not in folds]

    if violations:
        for violation in violations:
            print(violation)
    if not unmatched and not violations:
        print("All defined functions are already matched.")
        return

    for rel_path, class_name, method_name in unmatched:
        print(f"{rel_path}: {class_name}::{method_name}")
    if args.fail:
        sys.exit(1)


if __name__ == "__main__":
    main()
