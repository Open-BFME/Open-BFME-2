"""The compiler flags a `// cl:` line may carry: one list for the hooks and the build.

cl.exe does what its flags say. /B1, /B2 and /Bx swap in another compiler pass or
preprocessor DLL; /Fa /FA /Fo /Fd /Fe /Fm /FR /Fr /Fp /Fx write files wherever they point
(Wine maps / as Z:, so anywhere the user can write); /Yc /Yu /YX read and write
precompiled headers; @file reads more flags from a file; /link hands options to the
linker; /clang: passes its operand to clang-cl, whose -fplugin= and -Xclang -load load
code. A commit carrying one of these runs code or writes files on every seat, worker and
runner that builds it. conversion_gate.py (Rule F) refuses an added line with one, and
build.source_extra_flags refuses to compile a source with one.

So only the flag families this repository's sources used on 2026-11-07 pass, each of
them code-generation or language only: Code/, the banked attempts under reverse/, the
generators in tools/ and the Open-BFME-1 donors (every token was surveyed). A /I or /FI
path must stay inside the checkout: relative, no `..`, no drive or root. Anything else,
prose included, is refused; a new flag is a reviewed edit to this list.
"""
import re


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


def outside(path):
    """Why an include path leaves the checkout, or None."""
    path = path.replace("\\", "/")
    if not path:
        return "is empty"
    if path.startswith("/") or re.match(r"[A-Za-z]:", path) or path.startswith("//"):
        return "is absolute"
    if ".." in path.split("/"):
        return "climbs out with .."
    return None


def problems(tokens, paths=True):
    """[(token, reason)] for each `// cl:` token (build._source_flag_tokens') a source may not carry.
    paths=False skips /I and /FI operands, for a flag list whose paths were checked as written and
    then rewritten (build._current_bfme1_include_flag)."""
    found = []
    index = 0
    while index < len(tokens):
        token = tokens[index]
        flag = "-" + token[1:] if token.startswith("/") else token
        if flag in ("-I", "-FI"):                     # the operand is the next token
            index += 1
            operand = tokens[index] if index < len(tokens) else ""
            why = outside(operand) if paths else None
            if why:
                found.append((f"{token} {operand}".strip(), f"include path {why}"))
        elif PATH_FLAG.match(flag):
            why = outside(PATH_FLAG.match(flag).group(2)) if paths else None
            if why:
                found.append((token, f"include path {why}"))
        elif not ALLOWED.match(flag):
            if DANGEROUS.match(flag):
                found.append((token, "loads code or writes files"))
            elif flag.startswith("-"):
                found.append((token, "is not a flag this repository's sources use"))
            else:
                found.append((token, "is not a flag"))
        index += 1
    return found


def describe(found):
    return "; ".join(f"{token!r} {reason}" for token, reason in found)
