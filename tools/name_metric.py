"""BFME1's declared-name metric, applied to tracked Code/ sources.

Declaration parsing and placeholder rules ported from Open-BFME-1's
name_lane.py and readability_metric.py at 7c4d488c5b, with the offset rule
tightened (see `offset`): tools/rename.py shares this definition, and an
inferred rename may replace only what it calls a placeholder, so a real name
read as an offset (parseCoord3D, dwReserved1) would be open to replacement. Generated dumps are
excluded; globals count once across extern declarations. This measures
non-placeholder spelling, not proof of an original EA identity.
"""
import collections
import functools
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GENERATED = ("Code/gen_asm/", "Code/gen_small/")
NONCODE = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
WORD = re.compile(r"\b[A-Za-z_]\w*\b")
# A named union is a type with data members, like a class or a struct. It was
# left out, so its tag and its fields were counted nowhere - and while `union`
# was also missing from members()' old skip list, that only counted the tag, in
# the wrong category, and never the fields.
DECL = re.compile(r"^[ \t]*(?:class|struct|union)[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
ENUM = re.compile(r"^[ \t]*enum[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
BRACE = re.compile(r"[{}]")
# A directive runs over its backslash-newline continuations; in a CRLF file the backslash is followed
# by CR LF. A blank between the backslash and the line end is not read as a continuation here: a
# scan that blanks directives would blank real code if cl did not continue over it (rename.py's
# macro screen, which only widens what it refuses, does read it as one).
LINE_CONTINUATION = r"\\\r?\n"
PREPROCESSOR = re.compile(r"^[ \t]*#(?:[^\n]*" + LINE_CONTINUATION + r")*[^\n]*", re.M)
LOCAL = re.compile(r"(?:^|[;{}(])\s*(?:(?:const|static|unsigned|signed|struct|class)\s+)*"
                   r"([A-Za-z_][\w:]*)[\s*&]+([A-Za-z_]\w*)\s*(?=[=;\[,)])")
FUNC = re.compile(r"^[ \t]*(?:[A-Za-z_][\w:<>,*& \t]*?[\s*&])?((?:[A-Za-z_]\w*::)*)(~?[A-Za-z_]\w*)[ \t]*"
                  r"\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*(?:const\s*)?(?::[^;{]*)?\{", re.M)
ADDRESSED = re.compile(r"(?:d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]{4,8}\b"
                       r"|Rva[0-9A-Fa-f]{6,8}\b|gen[0-9A-Fa-f]{6,8}\b|Gen_?[0-9A-Fa-f]{3,8}\b"
                       r"|Rva[0-9A-Fa-f]{4,8}(?-i:[A-Z])|Gen_?[0-9A-Fa-f]{6,8}(?-i:[A-Z])", re.I)
# An offset-derived name: m_ (or s_/g_) and nothing but hex (m_0C, m_B0,
# m_64), a field-style prefix and hex (field_1C, unk14, off_20, m_var0), or a
# lower-case word then an offset tail of two or more hex characters that starts
# with a digit, or with an upper-case hex letter right after a lower-case one
# (m_p10, slot20, m_value_84, m_valueC4, m_field_0x20). A one-digit tail
# (data2, word1), a dimension or bit-width suffix (parseCoord3D, getInt64,
# crc32, vec3d, sha256) and a *Reserved<n> field (dwReserved1) are real names:
# BFME1's rule read any two-hex-character tail with a digit -- the 'd3D' of
# parseCoord3D, the 'd1' of dwReserved1 -- as an offset.
OFFSET_HEX = r"(?:0x)?(?=[0-9a-fA-F]*\d)[0-9a-fA-F]+"
OFFSET_FIELD = re.compile(r"[msg]_" + OFFSET_HEX + r"|(?:[msg]_)?(?:field|unk|unknown|off|offset|var|dword|word"
                          r"|byte|ptr)_?" + OFFSET_HEX)
OFFSET_TAIL = re.compile(r"(?:m_)?[a-z][A-Za-z]*?_?((?:0x)?(?:\d[0-9a-fA-F]*|(?<=[a-z])[A-F][0-9A-F]*))")
WIDTH = re.compile(r"(?:0x)?(?:8|16|32|64|128|256|[234][dD])")
RESERVED = re.compile(r"\w*[Rr]eserved\d*")


def offset(word):
    """True for an offset-derived name (see OFFSET_FIELD and OFFSET_TAIL)."""
    if RESERVED.fullmatch(word):
        return False
    if OFFSET_FIELD.fullmatch(word):
        return True
    match = OFFSET_TAIL.fullmatch(word)
    if not match or not re.search(r"\d", match.group(1)):
        return False
    tail = match.group(1)[2:] if match.group(1).startswith("0x") else match.group(1)
    return len(tail) >= 2 and not WIDTH.fullmatch(tail)


OPAQUE = re.compile(r"[a-z]{1,2}Var\d+|local_[0-9a-fA-F]+|param_\d+|(?:in|extraout)_[A-Z]{2,3}|[av]\d{1,2}")
HEXRUN = re.compile(r"(?i)(?=(?:[0-9a-f]*\d){3})[0-9a-f]{6,8}")
WEAK_LOCAL = re.compile(r"(?i)[a-hl-z]|(?:tmp|temp)\w*|arg(?:ument)?\d*|[a-z]{1,2}\d+")
PAD = re.compile(r"(?:m_)?_?(?:pad|padding|gap|unused|reserved|filler|spare)", re.I)
KEYWORDS = set("""alignas alignof asm auto bool break case catch char class const const_cast continue default delete do
double dynamic_cast else enum explicit export extern false float for friend goto if inline int long mutable namespace new
operator private protected public register reinterpret_cast return short signed sizeof static static_cast struct switch
template this throw true typedef typeid typename union unsigned using virtual void volatile wchar_t while NULL
__cdecl __stdcall __thiscall __fastcall __declspec __int64 __asm""".split())


@functools.lru_cache(maxsize=None)
def placeholder(word):
    return bool(ADDRESSED.fullmatch(word) or re.search(r"(?i)(^|_)bfme", word) or re.search(r"[0-9A-F]{6,8}", word)
                or HEXRUN.search(word) or (offset(word) and not PAD.match(word)) or OPAQUE.fullmatch(word))


def weak(kind, name):
    return placeholder(name) or (kind in ("param", "local") and bool(WEAK_LOCAL.fullmatch(name)))


def strip(text):
    # cl splices backslash-newlines before it removes comments, so a block comment inside a continued
    # #define (`/* \` ... `*/ \`) leaves the directive continued; keep each line-ending backslash (and
    # its CR) when blanking, or PREPROCESSOR stops at the comment and the macro's tail reads as code.
    return NONCODE.sub(lambda m: re.sub(r"(\\\r?(?=\n))|[^\n]", lambda c: c.group(1) or " ", m.group(0)), text)


def close(code, brace):
    depth = 0
    for m in BRACE.finditer(code, brace):
        depth += 1 if m.group() == "{" else -1
        if depth == 0:
            return m.start()
    return len(code)


def functions_in(code):
    out, seen = [], collections.Counter()
    for m in FUNC.finditer(code):
        if m.group(2) in KEYWORDS:
            continue
        scope = m.group(1) + m.group(2)
        seen[scope] += 1
        out.append((scope + (f"#{seen[scope]}" if seen[scope] > 1 else ""), m.start(), close(code, m.end() - 1) + 1, m.group(3)))
    return out


# `class Object *obj;` declares a member, not a nested type: the keyword is an
# elaborated type specifier. Skipping every statement that opens with one cost
# real names - a member written that way was counted nowhere, and
# rename.py's reference_declarers, which reads this to show that a word is a
# genuine name in the reference trees, could not see it either.
ELABORATED = re.compile(r"^(\s*)(?:class|struct|union|enum)\s+([A-Za-z_]\w*)\b(.*)$", re.S)
# A declarator after the type name: a pointer or reference, or one plain name,
# possibly an array. `: public Base` is a base clause and `final` is not a name.
DECLARATOR = re.compile(r"[*&]|^\s*[A-Za-z_]\w*\s*(?:\[[^\]]*\])?\s*$", re.S)
NOT_A_NAME = {"final", "sealed", "abstract"}


def unelaborate(stmt):
    """`class Object *obj` -> `Object *obj`, so the declarator reader sees it.
    None for a nested type, a forward declaration or a base clause: braces are
    flattened before this runs, so those have no declarator left to find."""
    m = ELABORATED.match(stmt)
    if not m:
        return stmt
    rest = m.group(3)
    if not DECLARATOR.search(rest) or rest.strip() in NOT_A_NAME:
        return None
    return m.group(1) + m.group(2) + rest


def members(body):
    while True:
        flat = re.sub(r"\{[^{}]*\}", ";", body)
        if flat == body:
            break
        body = flat
    for stmt in re.sub(r"\b(?:public|private|protected)\s*:", ";", body).split(";"):
        if "(" in stmt or re.match(r"\s*(?:typedef|friend|using)\b", stmt):
            continue
        stmt = unelaborate(stmt)
        if stmt is None:
            continue
        for d in stmt.split(","):
            m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?::\s*\w+\s*)?$", d.strip())
            if m:
                yield m.group(1)


def param_names(params):
    for p in params.split(","):
        ids = [t for t in WORD.findall(p.split("=")[0]) if t not in KEYWORDS]
        if len(ids) >= 2:
            yield ids[-1]


def local_names(body):
    statements = {"return", "delete", "goto", "throw", "case", "new", "else", "do", "typedef", "using", "sizeof"}
    return [m.group(2) for m in LOCAL.finditer(body) if m.group(1) not in statements and m.group(2) not in KEYWORDS]


def global_names(code):
    code, top, depth, last = PREPROCESSOR.sub("", code), [], 0, 0
    for m in BRACE.finditer(code):
        if m.group() == "{":
            depth += 1
            if depth == 1:
                top.append(code[last:m.start()])
        elif depth:
            depth -= 1
            if depth == 0:
                last = m.end()
                top.append(";")
    top.append(code[last:] if depth == 0 else "")
    for stmt in "".join(top).split(";"):
        if "(" in stmt or re.match(r"\s*(?:typedef|using|namespace|template|friend)\b", stmt):
            continue
        stmt = unelaborate(stmt)          # `class Object *g_obj;` is a global, as above
        if stmt is None:
            continue
        ids = [t for t in WORD.findall(stmt.split("=")[0].split("[")[0]) if t not in KEYWORDS]
        if len(ids) >= 2 or (ids and re.search(r"\b(?:int|char|bool|float|double|long|short|unsigned|void)\b", stmt)):
            yield ids[-1]


def declared(rel, text):
    code = strip(text)
    out = [("file", Path(rel).stem)]
    for m in DECL.finditer(code):
        out.append(("type", m.group(1)))
        out += [("member", n) for n in members(code[m.end():close(code, m.end() - 1)]) if not PAD.match(n)]
    out += [("type", m.group(1)) for m in ENUM.finditer(code)]
    for scope, start, end, params in functions_in(code):
        out.append(("function", scope.split("#")[0].split("::")[-1]))
        out += [("param", n) for n in param_names(params)]
        out += [("local", n) for n in local_names(code[code.find("{", start):end])]
    return out + [("global", n) for n in global_names(code)]


def readable():
    paths = subprocess.run(["git", "ls-files", "-z", "--", "Code"], cwd=ROOT,
                           capture_output=True, text=True, check=True).stdout.split("\0")
    total, placeholders, globals_seen = 0, 0, set()
    for rel in paths:
        if not rel.endswith((".cpp", ".c", ".h", ".inl")) or rel.startswith(GENERATED):
            continue
        for kind, name in declared(rel, (ROOT / rel).read_text(encoding="utf-8", errors="replace")):
            if kind == "global":
                if name in globals_seen:
                    continue
                globals_seen.add(name)
            total += 1
            placeholders += bool(weak(kind, name))
    if not total:
        raise ValueError("No declared names found in tracked Code/ sources")
    return total, placeholders
