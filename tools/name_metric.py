"""BFME1's declared-name metric, applied to tracked Code/ sources.

Declaration parsing and placeholder rules ported from Open-BFME-1's
name_lane.py and readability_metric.py at 7c4d488c5b. Generated dumps are
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
DECL = re.compile(r"^[ \t]*(?:class|struct)[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
ENUM = re.compile(r"^[ \t]*enum[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
BRACE = re.compile(r"[{}]")
PREPROCESSOR = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
LOCAL = re.compile(r"(?:^|[;{}(])\s*(?:(?:const|static|unsigned|signed|struct|class)\s+)*"
                   r"([A-Za-z_][\w:]*)[\s*&]+([A-Za-z_]\w*)\s*(?=[=;\[,)])")
FUNC = re.compile(r"^[ \t]*(?:[A-Za-z_][\w:<>,*& \t]*?[\s*&])?((?:[A-Za-z_]\w*::)*)(~?[A-Za-z_]\w*)[ \t]*"
                  r"\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*(?:const\s*)?(?::[^;{]*)?\{", re.M)
ADDRESSED = re.compile(r"(?:d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]{4,8}\b"
                       r"|Rva[0-9A-Fa-f]{6,8}\b|gen[0-9A-Fa-f]{6,8}\b|Gen_?[0-9A-Fa-f]{3,8}\b"
                       r"|Rva[0-9A-Fa-f]{4,8}(?-i:[A-Z])|Gen_?[0-9A-Fa-f]{6,8}(?-i:[A-Z])", re.I)
OFFSET = re.compile(r"(?:m_)?[a-z][A-Za-z]*?_?(?:0x)?(?=[0-9a-fA-F]*\d)[0-9a-fA-F]{2,}")
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
                or HEXRUN.search(word) or (OFFSET.fullmatch(word) and not PAD.match(word)) or OPAQUE.fullmatch(word))


def weak(kind, name):
    return placeholder(name) or (kind in ("param", "local") and bool(WEAK_LOCAL.fullmatch(name)))


def strip(text):
    return NONCODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


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


def members(body):
    while True:
        flat = re.sub(r"\{[^{}]*\}", ";", body)
        if flat == body:
            break
        body = flat
    for stmt in re.sub(r"\b(?:public|private|protected)\s*:", ";", body).split(";"):
        if "(" in stmt or re.match(r"\s*(?:typedef|friend|using|enum|class|struct)\b", stmt):
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
        if "(" in stmt or re.match(r"\s*(?:typedef|using|class|struct|enum|union|namespace|template|friend)\b", stmt):
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
