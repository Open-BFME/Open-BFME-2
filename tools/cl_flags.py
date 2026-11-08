"""What a source may tell the compiler through its `// cl:` line: one policy for the hooks and the build.

cl.exe does what its flags say. /B1, /B2 and /Bx swap in another compiler pass or
preprocessor DLL; /Fa /FA /Fo /Fd /Fe /Fm /FR /Fr /Fp /Fx write files wherever they point
(Wine maps / as Z:, so anywhere the user can write); /Yc /Yu /YX read and write
precompiled headers; @file reads more flags from a file (clang-cl expands one even as an
option's argument); /link hands options to the linker; /clang: passes its operand to
clang-cl, whose -Xclang, -load, -plugin and -fplugin= load code. A commit carrying one of
these runs code or writes files on every seat, worker and runner that builds it.
conversion_gate.py (Rule F) refuses an added `// cl:` line with one, and
build.source_extra_flags refuses to compile any source with one: that is the backstop
for every source the gate does not judge (outside Code/, never added in a diff).

Two compiler-facing guarantees, neither a parser of paths:
  * Flags: only the flag families this repository's sources used on 2026-11-07 pass, each
    code-generation or language only (every token of Code/, the banked attempts, the
    generators and the Open-BFME-1 donors was surveyed). No token may hold `@` or a quote.
  * Include flag values: a /I or /FI operand must be one of the exact strings in
    reverse/cl_include_roots.txt (INCLUDE_ROOTS, written from master's sources by
    `python3 tools/cl_flags.py --write-include-roots`; adding one is a reviewed ledger
    change with a Verifier-Change trailer). An 8.3 name, a trailing dot, an alternate
    stream or another case is another string, so it is refused without being interpreted.
What the compiler then opens through #include, however a source spells or builds it, is
confined by build.try_compile_source from cl's own /showIncludes list (build.py, "include
confinement"); this module does not try to read paths.

The environment can carry flags too: cl.exe and clang-cl read CL and _CL_, ml.exe ML and
_ML_, link.exe LINK and _LINK_, clang CCC_OVERRIDE_OPTIONS and its include path variables,
and #using searches LIBPATH. build.compiler_environment drops OPTION_ENV (in any case:
Windows programs look names up case-insensitively).

A `// cl:` directive is a line to build.py (str.splitlines, which also breaks at \\v \\f
\\x1c-\\x1e U+0085 U+2028 U+2029 and a lone \\r) but a line to git and the gate only at
\\n. directive_split() refuses a source whose two readings of its `// cl:` lines differ.

  python3 tools/cl_flags.py --write-include-roots   # rewrite reverse/cl_include_roots.txt from the tree
"""
import os
import posixpath
import re
import sys
from pathlib import Path

OPTION_ENV = frozenset(["CL", "_CL_", "ML", "_ML_", "LINK", "_LINK_", "LIBPATH", "CCC_OVERRIDE_OPTIONS",
                        "CPATH", "C_INCLUDE_PATH", "CPLUS_INCLUDE_PATH", "OBJC_INCLUDE_PATH"])
MARK = "// cl:"
INCLUDE_ROOTS = "reverse/cl_include_roots.txt"


class Refused(ValueError):
    """A compile refused for its flags. A ValueError, not SystemExit: a sweep over thousands of
    donors (donor_sweep.sweep_one catches Exception) skips the one source; a gate still fails."""


ALLOWED = re.compile(r"""-(?:
      M[DT]                                         # runtime library
    | [DU][A-Za-z_]\S*                              # a macro, defined or undefined
    | O(?:[12dsxt]|[giyaw]-?|b[012]|p-?)            # optimisation
    | G(?:[567]|[XRSF]-?|[Zyz]|s\d*)                # code generation
    | EH(?:[sac]-?){1,3}                            # exception model
    | arch:(?:SSE2?|IA32)
    | Z(?:7|e|c:(?:wchar_t|forScope)-?)             # debug info in the object; language
    | vm[bgsmv] | vd[012]                           # member pointers; vtordisp
    | RTC(?:[suc1]|su)                              # run-time checks
    | T[PC] | hotpatch | QIfist | QI0f
    | d1Binl | d2inlS100 | d2Gmanaged               # internal switches, exactly these
    | clang:-(?:mllvm|mno-sse2?|mmmx|fno-math-errno|mfpmath=387
               |branch-folder-reorder-blocks=(?:true|false)
               |tail-dup-size=\d+|tail-dup-placement=(?:true|false)|tail-dup-placement-threshold=\d+)
)$""", re.X)
PATH_FLAG = re.compile(r"-(I|FI)(.*)$", re.S)
# Named in refusals: the flags that load code or write files (any flag not ALLOWED is refused).
DANGEROUS = re.compile(r"-(?:B|F[aAodemRrpxi]|Y|link$|clang:|P$|E$|EP$|clr|AI|FU|analyze|doc)|@")
SEPARATOR = re.compile("[\\v\\f\\x1c\\x1d\\x1e\\x85\\u2028\\u2029]|\\r(?!\\n)")


def include_value(operand):
    """The string a /I or /FI operand is compared as: backslashes written as slashes."""
    return operand.replace("\\", "/")


def outside(path):
    """Why an include path is not a plain relative path inside the checkout, or None (cheap,
    lexical: the value allowlist and build's include confinement are the guarantees)."""
    if not path:
        return "is empty"
    if '"' in path or "@" in path:
        return "holds a quote or @"
    path = include_value(path)
    if path.startswith("/") or re.match(r"[A-Za-z]:", path):
        return "is absolute"
    if ".." in path.split("/"):
        return "climbs out with .."
    return None


def _path_problem(operand, values):
    why = outside(operand)
    if why:
        return f"include path {why}"
    if values is not None and include_value(operand) not in values:
        return f"include path is not in {INCLUDE_ROOTS}"
    return None


def problems(tokens, include_values=None):
    """[(token, reason)] for each `// cl:` token (build._source_flag_tokens') a source may not carry.
    `include_values` (a set of include_value() strings) is the allowlist /I and /FI operands must
    be in; None checks them lexically only."""
    found = []
    index = 0
    while index < len(tokens):
        token = tokens[index]
        flag = "-" + token[1:] if token.startswith("/") else token
        if flag in ("-I", "-FI"):                     # the operand is the next token
            index += 1
            operand = tokens[index] if index < len(tokens) else ""
            why = _path_problem(operand, include_values)
            if why:
                found.append((f"{token} {operand}".strip(), why))
        elif PATH_FLAG.match(flag):
            why = _path_problem(PATH_FLAG.match(flag).group(2), include_values)
            if why:
                found.append((token, why))
        elif "@" in flag or '"' in flag:
            found.append((token, "holds @ (a response file) or a quote"))
        elif not ALLOWED.match(flag):
            if DANGEROUS.match(flag):
                found.append((token, "loads code or writes files"))
            elif flag.startswith("-"):
                found.append((token, "is not a flag this repository's sources use"))
            else:
                found.append((token, "is not a flag"))
        index += 1
    return found


def include_operands(tokens):
    """The include_value() of every /I and /FI operand among `tokens`."""
    values, index = [], 0
    while index < len(tokens):
        flag = "-" + tokens[index][1:] if tokens[index].startswith("/") else tokens[index]
        if flag in ("-I", "-FI"):
            index += 1
            if index < len(tokens):
                values.append(include_value(tokens[index]))
        elif PATH_FLAG.match(flag):
            values.append(include_value(PATH_FLAG.match(flag).group(2)))
        index += 1
    return values


OVERLAY = re.compile(r"^build/stlport46/[0-9a-f]{24}(?=/|$)")


def canonical_include(operand, root, toolchain):
    """A final command's /I or /FI operand as INCLUDE_ROOTS spells it. Tools add absolute operands
    (the SDKs, the retry directories, Wine paths): one under the toolchain becomes
    `{toolchain}/<rest>` (wherever VC71_ROOT points), one under the checkout its repo-relative
    path; stlport_overlay's directory (build/stlport46/<digest of committed inputs>) becomes
    `{overlay}`. Nothing is resolved: any other spelling stays itself and is not listed."""
    value = include_value(operand)
    host = None
    if re.match(r"[A-Za-z]:/", value) or value.startswith("/"):
        host = value[2:] if os.name != "nt" and value[:2] in ("Z:", "z:") else value
        host = posixpath.normpath(host.replace("\\", "/"))
    if host is not None:
        for base, prefix in ((toolchain, "{toolchain}"), (root, None)):
            base = posixpath.normpath(base.replace("\\", "/"))
            folded = (host.lower(), base.lower()) if os.name == "nt" else (host, base)
            if folded[0] == folded[1] or folded[0].startswith(folded[1] + "/"):
                rest = host[len(base):].lstrip("/")
                value = (f"{prefix}/{rest}" if rest else prefix) if prefix else (rest or ".")
                break
    return OVERLAY.sub("{overlay}", value)


def asm_refusals(source):
    """Why assembler `source` (bytes as read from disk, or text) falls outside the grammar build.py
    assembles; [] when it is inside. ml.exe lists no file it reads, so include confinement cannot see an
    INCLUDE, and MASM can build one from text macros, macros or a label run into a directive (x CATSTR
    <incl>,<ude>, then x <path>; label:include <path>). Rather than find those facilities, accept only
    what the tree's assembler sources use: every one is generated or dumped. The source must be printable
    ASCII; `;` starts a comment (no quotes are accepted, so always); a statement ending in `\\` or `,`
    continues on the next line. Each statement is an optional `label:` alone or before an instruction
    from ASM_MNEMONICS, or one of the directives in _asm_directive. Every word in an operand is a number,
    a word from ASM_OPERAND_WORDS or a name, and a name holds `_`, `?`, `$` or `@` (ASM_PLAIN_NAMES
    excepted), which no MASM keyword does. Widen a set only for a tracked source that needs it."""
    if isinstance(source, bytes):
        try:
            source = source.decode("ascii")
        except UnicodeDecodeError as error:
            return [f"byte {error.start}: not ASCII"]
    text = source.replace("\r\n", "\n")
    stray = ASM_STRAY.search(text)
    if stray:
        return [f"line {text.count(chr(10), 0, stray.start()) + 1}: character {stray.group()!r}"]
    refusals, statement, start = [], "", 0
    for number, line in enumerate(text.split("\n"), 1):
        code = line.split(";", 1)[0].strip()
        if statement:
            code = f"{statement} {code}".strip()
        else:
            start = number
        if code.endswith("\\"):
            statement = code[:-1].rstrip() or " "
            continue
        if code.endswith(","):
            statement = code
            continue
        statement = ""
        problem = code.strip() and _asm_statement(code.strip())
        if problem:
            refusals.append(f"line {start}: {code.strip()[:80]!r}: {problem}")
    if statement:
        refusals.append(f"line {start}: a continuation runs past the end")
    return refusals


def _asm_name(word):
    return bool(ASM_NAME.match(word)) and (bool(re.search(r"[_?$@]", word)) and word not in ("?", "$")
                                           or word.lower() in ASM_PLAIN_NAMES)


def _asm_operands(text):
    """Why operand `text` is outside the grammar, or None."""
    position = 0
    while position < len(text):
        token = ASM_TOKEN.match(text, position)
        if not token:
            return f"{text[position:].strip()[:20]!r} in an operand"
        word, digits = token.group("word"), token.group("number")
        if word and not (word.lower() in ASM_OPERAND_WORDS or _asm_name(word)):
            return f"the word {word!r} in an operand"
        if digits and not ASM_NUMBER.match(digits):
            return f"the number {digits!r}"
        position = token.end()
    return None


def _asm_statement(code):
    """Why one comment-free statement is outside the grammar, or None."""
    label = ASM_LABEL.match(code)
    if label:
        rest = code[label.end():].strip()
        if not _asm_name(label.group(1)):
            return f"the label {label.group(1)!r}"
        if not rest:
            return None
        if rest.split()[0].lower() not in ASM_MNEMONICS:
            return "a label may stand alone or before an instruction"
        return _asm_operands(rest[len(rest.split()[0]):])
    words = code.split()
    head = words[0].lower()
    if head in ASM_MNEMONICS:
        return _asm_operands(code[len(words[0]):])
    return _asm_directive(code, words, head)


def _asm_directive(code, words, head):
    second = words[1].lower() if len(words) > 1 else ""
    rest = code[len(words[0]):].strip()
    items = [item.strip() for item in rest.split(",")]
    if head in ASM_CPUS and len(words) == 1 or head == "even" and len(words) == 1:
        return None
    if head == ".model":
        return None if rest.lower() in ASM_MODELS else f".MODEL {rest}"
    if second in ("segment", "ends") and len(words) == 2:
        return None if head in ASM_SEGMENTS else f"the segment {words[0]!r}"
    if second in ("proc", "endp") and len(words) == 2:
        return None if _asm_name(words[0]) else f"the procedure name {words[0]!r}"
    if head == "public":
        return None if all(_asm_name(item) for item in items) else f"PUBLIC {rest}"
    if head in ("extrn", "extern"):
        typed = [item.split(":") for item in items]
        if all(len(pair) == 2 and _asm_name(pair[0].strip()) and pair[1].strip().lower() in ASM_EXTERN_TYPES
               for pair in typed):
            return None
        return f"{words[0]} {rest}"
    if head == "assume":
        pairs = [item.lower().replace(" ", "").split(":") for item in items]
        if all(len(pair) == 2 and pair[0] in ASM_ASSUME_REGISTERS and pair[1] == "nothing" for pair in pairs):
            return None
        return f"ASSUME {rest}"
    if head in ("align", "org"):
        return None if len(words) == 2 and ASM_NUMBER.match(words[1]) else f"{words[0]} {rest}"
    if head == "end":
        return None if len(words) == 1 or len(words) == 2 and _asm_name(words[1]) else f"END {rest}"
    if head == "option":
        return None if rest.lower() in ASM_OPTIONS else f"OPTION {rest}"
    if head in ASM_DATA:
        return _asm_operands(rest)
    if second in ASM_DATA:
        if not _asm_name(words[0]):
            return f"the data name {words[0]!r}"
        return _asm_operands(code[len(words[0]):].strip()[len(words[1]):])
    equate = ASM_EQUATE.match(code)
    if equate:
        if not _asm_name(equate.group("name")):
            return f"the equate name {equate.group('name')!r}"
        return None if ASM_NUMBER.match(equate.group("value")) else "an equate other than a number"
    return f"{words[0]!r} begins no statement in the grammar"


# The grammar's words. Each is used by a tracked assembler source (most are Code/gen_asm dumps of
# `db`; the rest hand-written MMX and x87 helpers); add one only with the source that needs it.
ASM_CPUS = frozenset({".386", ".486", ".586", ".686", ".mmx", ".xmm"})
ASM_MODELS = frozenset({"flat"})
ASM_SEGMENTS = frozenset({"_text"})
ASM_EXTERN_TYPES = frozenset({"proc", "dword", "word"})
ASM_ASSUME_REGISTERS = frozenset({"fs"})
ASM_DATA = frozenset({"db", "dw", "dd", "dq", "dt", "df", "byte", "word", "dword", "qword"})
ASM_OPTIONS = frozenset()     # OPTION <argument>: no tracked source uses one
ASM_MNEMONICS = frozenset("""
    adc add and call fild fistp fld fst fstp fsubp inc je jmp jne jns jz lea leave mov movq neg nop paddsw
    paddw pand pmulhw pmullw pop por psllq psraw psrlq psubsw psubw punpckhdq punpckhwd punpckldq punpcklwd
    push pxor ret sbb sub test xor""".split())
ASM_OPERAND_WORDS = frozenset("""
    eax ebx ecx edx esi edi ebp esp fs st byte word dword qword ptr near""".split()
    + [f"mm{n}" for n in range(8)]      # Code/Libraries/Source/VP6/MmxIDct.asm
    + ["bl"])                           # Code/masm_dumps/VersionSignatureCheckPatched.asm
# names with none of _ ? $ @, each checked to be no MASM keyword: ftol2.asm's labels
ASM_PLAIN_NAMES = frozenset({"done", "integral", "positive", "subtract"})
ASM_STRAY = re.compile(r"[^\t\n\x20-\x7e]")
ASM_NAME = re.compile(r"[A-Za-z_?$][\w?$@]*\Z")
ASM_NUMBER = re.compile(r"(?i)(?:\d+|\d[0-9a-f]*h)\Z")
ASM_LABEL = re.compile(r"([^\s:]+):(?!:)")
ASM_TOKEN = re.compile(r"\s*(?:(?i:st)\(\d\)|(?P<word>[A-Za-z_?$@][\w?$@]*)|(?P<number>\d\w*)|[,\[\]+\-:])\s*")
ASM_EQUATE = re.compile(r"(?i)(?P<name>[^\s=]+)\s*(?:=|\s+equ\s+)\s*-?(?P<value>\w+)\Z")


def parse_include_roots(text):
    """The values of an INCLUDE_ROOTS file: one per line, `#` comments and blank lines ignored."""
    return frozenset(line.rstrip("\r") for line in text.split("\n")
                     if line.strip() and not line.lstrip().startswith("#"))


def directive_split(text):
    """Why build.py (str.splitlines) and git (newlines) would read this source's `// cl:` lines
    differently, or None."""
    as_git = [line[:-1] if line.endswith("\r") else line for line in text.split("\n")]
    if [line for line in text.splitlines() if line.startswith(MARK)] != \
            [line for line in as_git if line.startswith(MARK)]:
        return "a `// cl:` line is split or joined by a line break other than a newline"
    if any(MARK in line and SEPARATOR.search(line) for line in as_git):
        return "a `// cl:` line holds a line break other than a newline"
    return None


def describe(found):
    return "; ".join(f"{token!r} {reason}" for token, reason in found)


# An early warning only (conversion_gate Rule F): the boundary for what the compiler reads is
# build.py's include confinement, from cl's own /showIncludes list. #import reads a type library
# (and writes .tlh/.tli files beside the object), #using an assembly, include_alias reroutes an
# #include. Master's sources use none of them.
TRIGRAPHS = {"??=": "#", "??/": "\\", "??'": "^", "??(": "[", "??)": "]", "??!": "|", "??<": "{",
             "??>": "}", "??-": "~"}
COMMENT_OR_LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|/\*[\s\S]*?\*/|//[^\n]*')
READ_DIRECTIVE = re.compile(r"^[^\S\n]*#[^\S\n]*(import|using)\b|^[^\S\n]*#[^\S\n]*pragma[^\S\n]+(include_alias)\b"
                            r"|\b__pragma[^\S\n]*\([^\S\n]*(include_alias)\b", re.M)


def read_directives(text):
    """The file-reading directives in source `text` (#import, #using, include_alias by #pragma or
    __pragma), found as the preprocessor finds them: trigraphs replaced, line splices joined,
    comments blanked (line breaks kept), any \\r taken as a line break."""
    for trigraph, char in TRIGRAPHS.items():
        text = text.replace(trigraph, char)
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    text = re.sub(r"\\\n", "", text)
    text = COMMENT_OR_LITERAL.sub(lambda m: m.group() if m.group()[0] in "\"'"
                                  else "".join("\n" if c == "\n" else " " for c in m.group()), text)
    found = []
    for match in READ_DIRECTIVE.finditer(text):
        name = next(group for group in match.groups() if group)
        found.append("#pragma include_alias" if name == "include_alias" else f"#{name}")
    return sorted(set(found))


def write_include_roots():
    """Write INCLUDE_ROOTS from every source build.py can compile: Code/ and the banked attempts
    (their `// cl:` lines as written, as build.source_extra_flags rewrites them, and every include
    operand of the final compiler_command, canonical_include's spelling) and the Open-BFME-1
    donors, with the include directories build.py adds itself. A source refused for anything
    else contributes nothing."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import subprocess
    import build
    import cl_flags              # build's copy: run as a script, this module is __main__
    values = set()
    build._include_values = lambda: None           # this run collects; it does not judge
    toolchain = str(build.vc71_root())
    probe = build.ROOT / "build" / "include_roots_probe.obj"   # named only, never written
    import link_census
    rows = link_census.ledger()
    sources = {source for source in link_census.compile_sources(rows)}      # every ledger unit
    for repo, paths in ((build.ROOT, ["Code", "reverse/attempts"]), (build.BFME1_ROOT, ["."])):
        listing = subprocess.run(["git", "-C", str(repo), "grep", "-l", "-I", "-z", "^// cl:", "--", *paths],
                                 capture_output=True, check=False).stdout
        sources.update(repo / name.decode("utf-8", "replace") for name in listing.split(b"\0") if name)
    for source in sorted(sources):
        if source.suffix.lower() not in (".cpp", ".c", ".cxx", ".cc"):
            continue
        text = source.read_text(encoding="utf-8-sig", errors="replace")
        line = next((line for line in text.splitlines() if line.startswith(MARK)), "")
        try:
            written = build._source_flag_tokens(line[len(MARK):])
            final = build.source_extra_flags(source)
            command, _env = build.compiler_command(source, probe)
        except (cl_flags.Refused, SystemExit, OSError, ValueError):
            continue
        values.update(include_operands(written))
        values.update(include_operands(final))
        values.update(canonical_include(operand, str(build.ROOT), toolchain)
                      for operand in include_operands(command))
    # What build.py adds on its own: the sweep-include retry and the vendored SAGE trees' flags.
    values.update(canonical_include(build.wine_path(d), str(build.ROOT), toolchain)
                  for d in build._SWEEP_INCLUDE_DIRS)
    values.update(include_operands(build._ZH_FLAGS) + include_operands(build._GENERALS_FLAGS))
    out = build.ROOT / INCLUDE_ROOTS
    out.write_text("# The /I and /FI values a `// cl:` line may name (tools/cl_flags.py): exact strings,\n"
                   "# backslashes as slashes. Written by `python3 tools/cl_flags.py --write-include-roots`;\n"
                   "# adding a value is a reviewed change with a Verifier-Change trailer.\n"
                   + "".join(value + "\n" for value in sorted(values)), encoding="utf-8", newline="\n")
    print(f"{INCLUDE_ROOTS}: {len(values)} values")


if __name__ == "__main__":
    if sys.argv[1:] == ["--write-include-roots"]:
        write_include_roots()
    else:
        raise SystemExit(__doc__.strip().splitlines()[-1].strip())
