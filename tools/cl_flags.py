"""The compiler flags a `// cl:` line may carry: one list for the hooks and the build.

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

So only the flag families this repository's sources used on 2026-11-07 pass, each of
them code-generation or language only: Code/, the banked attempts under reverse/, the
generators in tools/ and the Open-BFME-1 donors (every token was surveyed). No token
may hold `@` or a quote. A /I or /FI path must stay inside the checkout: relative, no
`..`, no drive or root, and (given the roots) resolving, links followed, inside the
checkout or Open-BFME-1. Anything else, prose included, is refused; a new flag is a
reviewed edit to this list.

The environment can carry flags too: cl.exe and clang-cl read CL and _CL_, ml.exe ML and
_ML_, link.exe LINK and _LINK_, clang CCC_OVERRIDE_OPTIONS and its include path variables,
and #using searches LIBPATH. build.compiler_environment drops OPTION_ENV (in any case:
Windows programs look names up case-insensitively).

A `// cl:` directive is a line to build.py (str.splitlines, which also breaks at \\v \\f
\\x1c-\\x1e U+0085 U+2028 U+2029 and a lone \\r) but a line to git and the gate only at
\\n. directive_split() refuses a source whose two readings of its `// cl:` lines differ.
"""
import os
import re

OPTION_ENV = frozenset(["CL", "_CL_", "ML", "_ML_", "LINK", "_LINK_", "LIBPATH", "CCC_OVERRIDE_OPTIONS",
                        "CPATH", "C_INCLUDE_PATH", "CPLUS_INCLUDE_PATH", "OBJC_INCLUDE_PATH"])
MARK = "// cl:"


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


def outside(path, roots=None):
    """Why an include path leaves the checkout, or None. `roots`: the directories it may resolve
    into (links followed), relative to the first, the compiler's working directory."""
    if not path:
        return "is empty"
    if '"' in path or "@" in path:
        return "holds a quote or @"
    path = path.replace("\\", "/")
    if path.startswith("/") or re.match(r"[A-Za-z]:", path):
        return "is absolute"
    if ".." in path.split("/"):
        return "climbs out with .."
    if roots:
        target = os.path.realpath(os.path.join(roots[0], path))
        if not any(target == root or target.startswith(root.rstrip(os.sep) + os.sep)
                   for root in (os.path.realpath(r) for r in roots)):
            return "resolves outside the checkout"
    return None


def problems(tokens, roots=None):
    """[(token, reason)] for each `// cl:` token (build._source_flag_tokens') a source may not carry."""
    found = []
    index = 0
    while index < len(tokens):
        token = tokens[index]
        flag = "-" + token[1:] if token.startswith("/") else token
        if flag in ("-I", "-FI"):                     # the operand is the next token
            index += 1
            operand = tokens[index] if index < len(tokens) else ""
            why = outside(operand, roots)
            if why:
                found.append((f"{token} {operand}".strip(), f"include path {why}"))
        elif PATH_FLAG.match(flag):
            why = outside(PATH_FLAG.match(flag).group(2), roots)
            if why:
                found.append((token, f"include path {why}"))
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
