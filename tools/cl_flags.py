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


def asm_directives(text):
    """The MASM include and text-macro facilities in assembler `text` (case-insensitive): any of
    them can build an INCLUDE that ml.exe reads without listing it (x CATSTR <incl>,<ude>, then x
    <path>). Directives are matched where MASM honours them, in statement position (first word, or
    after one name), the @ functions anywhere and % at a line's start, so prose after `;` is not."""
    found = set()
    for line in text.replace("\r\n", "\n").replace("\r", "\n").split("\n"):
        statement = ASM_STATEMENT.match(line)
        if statement:
            found.add(statement.group(1).lower().replace(" ", ""))
        found.update(m.group(0).lower() for m in ASM_FUNCTION.finditer(line))
        if re.match(r"\s*%", line):
            found.add("%")
    return sorted(found)


ASM_DIRECTIVES = (r"include|includelib|catstr|substr|instr|sizestr|textequ|macro|forc|for|irpc|irp|repeat|rept|"
                  r"while|exitm|purge|comment")
ASM_STATEMENT = re.compile(rf"(?i)^\s*(?:[\w@?$.]+:?\s+)?((?:{ASM_DIRECTIVES})(?![\w@?$])|equ\s*<)")
ASM_FUNCTION = re.compile(r"(?i)@(?:catstr|substr|instr|sizestr)\b")


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
