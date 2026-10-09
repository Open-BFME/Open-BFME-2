#!/usr/bin/env python3
"""Report new address-named globals for retail data that already has a usable name (SHADOW).

WHY. The per-function byte gate masks DIR32 (global) relocations, so a body
matches whatever it calls a global. Agents therefore invent one per address --
g_Va00BBB8D8, g_00DFE758, g_Rva0107301CEmptyString -- and the tree grows a
second, third, ninth name for one retail global: reverse/data_ledger.csv binds
TheWritableGlobalData, g_00DFE758, g_Va009FE758 and six more to 0x009FE758.
Each extra name is a separate definition the link has to reconcile.

WHAT. Code/ C/C++ sources a change touches whose added lines hold a 6-hex run.
The complete old and new file contents are lexed once each, as a compiler's
first phases see them: CRLF read as LF, backslash-newline line splices joined
(a `//` comment continued that way, a `/` spliced onto the `/` that starts the
next line, an identifier split across lines), then comments, raw strings R"d(...)d", string and character
literals blanked. A code token of the new file that is not one of the old file
is new; it is judged when it matches tools/hatch_counters.py's
`address_global` hatch (g_...Va/Rva/DAT_<hex>), the bare g_<hex> form, or is
an address-invented name (data_ledger.py's rule) the data ledger already binds.
So a name only mentioned in a comment -- even on a line added inside an
existing /* ... */ -- is not reported, and an old comment mentioning a name
does not hide a newly declared one. Each (file, name) is reported once, at the
original line of its first use in code. Known limits: inactive preprocessor
branches (#if 0) are read as code, and trigraphs (??/ as a backslash) are not
translated; MSVC 7.1-era sources here rarely use either.

ADDRESS. A name the data ledger already binds resolves to where it is bound.
Otherwise its hex run is read as a VA (image base 0x400000; tools/name_globals.py's
reading of an address >= 0x400000) and then as an RVA -- first for `Rva` names --
and the first reading that is an exact data-ledger address wins. A name that
resolves to no ledger address is counted as unresolved ("not checked"), not
reported.

WHAT IT IS INSTEAD. The other names the ledger binds at that address, by what
the source can do with them, first match wins:
  literal   a compiler literal (??_C@ string, __real@ float, __xmm@): use the
            literal itself -- 0x007BB8D8 is __real@3f800000, the float 1.0f
  vtable    a vtable or RTTI symbol (??_7, ??_8, ??_R, __TI, __CT): reached
            through its class, not an extern name
  owner     an external, non-invented name: extern it or include its header
            (imports count: declared by their header)
Not usable, so never suggested: TU-local statics (name@source in the ledger,
and function-local statics such as ?TheNullChr@?1??str@...) and provisional
`bfme` recovered-role guesses (g_bfmeDefaultBU). An address with only those
is counted, not listed.

COST. tools/shadow_budget.py bounds the run ($BFME_SHADOW_BUDGET_S, default
10 s, --budget): every git child waits at most the budget left and is killed
past it; the tool then prints "partial: budget ... exceeded after N of M
file(s)" with what it found and exits 0. Blobs are read 16 files to one `git
cat-file --batch`, and each is lexed once (was: one regex scan of the old blob
per candidate, 54.7 s for 500 names against a 3.23 MB file).

REPORT ONLY. --shadow (the hook) always exits 0; without it, exit 1 on a finding.

  python3 tools/invented_names.py --staged [--shadow]        the commit hook
  python3 tools/invented_names.py --commit REV               one commit against its parent
  python3 tools/invented_names.py --range BASE TIP           every commit in BASE..TIP
  python3 tools/invented_names.py --backtest N [--ref REF]   last N non-merge commits touching Code/
"""
import argparse
import bisect
import collections
import csv
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from hatch_counters import ADDR_GLOBAL  # noqa: E402  (the address_global hatch)
from shadow_budget import GIT, Budget, BudgetExceeded, seconds  # noqa: E402

IMAGE_BASE = 0x400000
SOURCE_ROOT = "Code/"
EXTENSIONS = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".inl")
PATHSPECS = tuple(f"{SOURCE_ROOT}*{ext}" for ext in EXTENSIONS)
LEDGER = "reverse/data_ledger.csv"
SEP = "\x1f"

# Copied from tools/data_ledger.py (which imports the build machinery: too slow
# for a hook); tools/tests/test_invented_names.py keeps the two identical.
INVENTED = re.compile(r"(?:^|[a-z_]|Va|Rva|At)(?=[0-9A-F]*[0-9])[0-9A-F]{6,8}(?![0-9A-F])")
LITERALS = ("??_C@", "__real@", "__xmm@")
VTABLE_RTTI = ("??_7", "??_8", "??_R", "__TI", "__CT")
# Rva005F5C77Base0: an address label whose hex run runs on into a word that
# starts with a hex letter, which INVENTED's end anchor misses
LABELLED = re.compile(r"(?:Rva|RVA|rva|Va|VA|DAT_)(?=[0-9A-F]{0,7}[0-9])[0-9A-F]{6,8}")
# g_00DFE758: the bare form the address_global hatch does not count
BARE = re.compile(r"(?<![A-Za-z0-9_])g_(?=[0-9A-Fa-f]{0,7}[0-9])[0-9A-Fa-f]{6,8}\w*")
# the hex run a name encodes and the label before it: upper-case hex as in
# INVENTED, then any case after an explicit label
ENCODED = (re.compile(r"(Rva|RVA|rva|Va|VA|va|DAT_?|g_|At|[a-z_])((?=[0-9A-F]{0,7}[0-9])[0-9A-F]{6,8})"),
           re.compile(r"(Rva|RVA|rva|Va|VA|va|DAT_?|g_)((?=[0-9A-Fa-f]{0,7}[0-9])[0-9A-Fa-f]{6,8})"))
HEX_RUN = re.compile(r"[0-9A-Fa-f]{6}")
SPLICE = re.compile(r"\\\n")
# what is not code once line splices are removed: raw strings R"d( ... )d" (with any
# encoding prefix), // comments, /* */ comments (an unterminated one runs to the end),
# string and character literals (an unterminated one ends at its line)
NON_CODE = re.compile(r'(?<![A-Za-z0-9_])(?:u8|[uUL])?R"(?P<d>[^ ()\\\t\v\f\n"]{0,16})\(.*?\)(?P=d)"'
                      r'|//[^\n]*'
                      r'|/\*.*?(?:\*/|\Z)'
                      r'|"(?:[^"\\\n]|\\.)*"?'
                      r"|'(?:[^'\\\n]|\\.)*'?", re.S)
NOT_NEWLINE = re.compile(r"[^\n]")
WORD = re.compile(r"[A-Za-z_]\w*|\d\w*")         # numbers too, so 0x00DFE758 is no identifier
CHUNK = 16                                        # files whose blobs one `git cat-file` reads
LOCAL_STATIC = re.compile(r"^\?\w+@\?\d")         # ?TheNullChr@?1??str@AsciiString@@QBEPBDXZ@4DB
GUESS = re.compile(r"^(?:[gs]_)?_?[Bb]fme(?=[A-Z0-9_])")    # a `bfme` recovered-role name

Finding = collections.namedtuple("Finding", "sha path line name rva kind shown how")


def identifier(symbol):
    """The source identifier of a decorated or C symbol (data_ledger.identifier)."""
    found = re.match(r"^\?(\w+)@", symbol)
    if found:
        return found.group(1)
    return symbol[1:] if symbol.startswith("_") else symbol


def invented(name):
    return bool(INVENTED.search(name) or LABELLED.search(name) or ADDR_GLOBAL.search(name)
                or BARE.search(name))


def classify(symbol, source):
    """What source can do with another name at the address: literal | vtable | owner |
    static | guess, or None for an address-invented name (no alternative at all)."""
    if symbol.startswith(LITERALS):
        return "literal"
    if invented(identifier(symbol)):
        return None
    if symbol.startswith(VTABLE_RTTI):
        return "vtable"
    if symbol.startswith("__imp_"):
        return "owner"
    if source or LOCAL_STATIC.match(symbol):
        return "static"
    if GUESS.match(identifier(symbol)):
        return "guess"
    return "owner"


# ---------------------------------------------------------------- the data ledger

class Ledger:
    """reverse/data_ledger.csv: {rva: (canonical, [(symbol, static source or None)])} and,
    per identifier, the addresses the tree binds it to."""

    def __init__(self, path):
        self.rows, self.bound = {}, collections.defaultdict(set)
        with open(path, newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                try:
                    rva = int(row["address"], 16)
                except (KeyError, ValueError):
                    continue
                names = []
                for cell in (row.get("names") or row.get("name") or "").split(";"):
                    symbol, _, source = cell.rpartition("@")
                    if "/" in source and symbol:
                        names.append((symbol, source))
                    elif cell:
                        names.append((cell, None))
                self.rows[rva] = (row.get("name", ""), names)
                for symbol, _source in names:
                    self.bound[identifier(symbol)].add(rva)

    def decode(self, name):
        """The ledger address a name's hex run spells (VA first, RVA first for `Rva`), or None."""
        found = ENCODED[0].search(name) or ENCODED[1].search(name)
        if not found:
            return None
        label, value = found.group(1), int(found.group(2), 16)
        readings = [value, value - IMAGE_BASE] if label.lower() == "rva" else [value - IMAGE_BASE, value]
        return next((rva for rva in readings if rva in self.rows), None)

    def resolve(self, name):
        """[(rva, how)] for an address-invented name: where the ledger binds it, else where
        its hex run points. `how` is "decoded" when the hex run alone gives that address
        (a brand-new name resolves the same way), else "bound"."""
        spelled = self.decode(name)
        if name in self.bound:
            return [(rva, "decoded" if rva == spelled else "bound") for rva in sorted(self.bound[name])]
        return [] if spelled is None else [(spelled, "decoded")]

    def instead(self, rva):
        """(kind, [shown]) of what to use at `rva`: the first of literal, vtable, owner that
        the ledger has there, or ("unusable", ...) when it holds only TU-local statics and
        provisional guesses, or (None, []) when it holds no other name at all."""
        canonical, names = self.rows.get(rva, ("", []))
        by_kind = collections.defaultdict(list)
        for symbol, source in sorted(names, key=lambda n: (n[0] != canonical, n[0], n[1] or "")):
            kind = classify(symbol, source)
            if kind is None:
                continue
            shown = literal_text(symbol) if kind == "literal" else display(symbol)
            if kind in ("static", "guess"):
                kind, shown = "unusable", shown + (" (static, %s)" % source.rsplit("/", 1)[-1] if source
                                                   else " (static)" if LOCAL_STATIC.match(symbol)
                                                   else " (provisional guess)")
            if shown not in by_kind[kind]:
                by_kind[kind].append(shown)
        for kind in ("literal", "vtable", "owner", "unusable"):
            if by_kind[kind]:
                return kind, by_kind[kind]
        return None, []


def display(symbol):
    vtable = re.match(r"^\?\?_7(\w+(?:@\w+)*)@@6", symbol)
    if vtable:
        return "::".join(reversed(vtable.group(1).split("@"))) + "::`vftable'"
    if symbol.startswith(("??", "__imp_", "__TI", "__CT")):
        return symbol
    return identifier(symbol)


# MSVC's ??_C@ encoding: ?0..?9 stand for these, ?$XY for byte 16*X+Y (A=0)
SPECIAL = ",/\\:. \n\t'-"


def literal_text(symbol):
    """`the float literal 1.0f (__real@3f800000)` and the like."""
    real = re.fullmatch(r"__real@([0-9a-fA-F]{8}|[0-9a-fA-F]{16})", symbol)
    if real:
        bits = bytes.fromhex(real.group(1))
        fmt, suffix, kind = (">f", "f", "float") if len(bits) == 4 else (">d", "", "double")
        value = struct.unpack(fmt, bits)[0]
        for digits in range(1, 18):
            text = "%.*g" % (digits, value)
            if struct.pack(fmt, float(text)) == bits:
                break
        if re.fullmatch(r"-?\d+", text):
            text += ".0"
        return f"the {kind} literal {text}{suffix} ({symbol})"
    string = re.fullmatch(r"\?\?_C@_([01])([0-9]|[A-P]+@)[A-P]+@(.*)@", symbol)
    if string:
        wide, length, body = string.group(1) == "1", string.group(2), string.group(3)
        size = int(length) + 1 if length.isdigit() else int("".join("%x" % (ord(c) - 65) for c in length[:-1]), 16)
        data, i = bytearray(), 0
        while i < len(body):
            c = body[i]
            if c == "?" and body[i + 1:i + 2] == "$" and i + 3 < len(body):
                data.append((ord(body[i + 2]) - 65) * 16 + ord(body[i + 3]) - 65)
                i += 4
            elif c == "?" and i + 1 < len(body) and body[i + 1].isdigit():
                data.append(ord(SPECIAL[int(body[i + 1])]))
                i += 2
            elif c == "?" and i + 1 < len(body) and body[i + 1].isalpha():
                data.append((0xE1 if body[i + 1].islower() else 0xC1) + ord(body[i + 1].lower()) - 97)
                i += 2
            else:
                data.append(ord(c) & 0xFF)
                i += 1
        whole = len(data) >= size
        text = data.decode("utf-16-le", "replace") if wide else data.decode("latin-1")
        text = text[:-1] if whole and text.endswith("\0") else text
        shown = "".join({"\\": "\\\\", '"': '\\"', "\n": "\\n", "\t": "\\t"}.get(ch, ch) if " " <= ch or ch in "\n\t"
                        else "\\x%02x" % ord(ch) for ch in text)
        return (f"the {'wide ' if wide else ''}string literal {'L' if wide else ''}\"{shown}"
                f"{'' if whole else '...'}\" ({symbol})")
    return f"a compiler literal ({symbol})"


# ---------------------------------------------------------------- the diff

def parse_patch(text):
    """[(commit, parent, [(old path or None, new path, [(line number, text)])])] from
    `git log -p -U0 --format=SEP%H SEP%P` or `git diff -U0` (commit None)."""
    commits, files = [], None
    current = None
    header = False
    old = new = None
    lineno = 0
    for line in text.splitlines():
        if line.startswith(SEP):
            sha, _, parents = line[1:].partition(SEP)
            files = []
            commits.append((sha.strip(), (parents.split() or [None])[0], files))
            current, header = None, False
            continue
        if files is None:
            files = []
            commits.append((None, None, files))
        if line.startswith("diff --git "):
            header, current, old, new = True, None, None, None
        elif header:
            if line.startswith("--- "):
                old = line[6:] if line.startswith("--- a/") else None
            elif line.startswith("+++ "):
                new = line[6:] if line.startswith("+++ b/") else None
                if new:
                    current = (old, new, [])
                    files.append(current)
            elif line.startswith("@@"):
                header = False
                lineno = _hunk_start(line)
        elif line.startswith("@@"):
            lineno = _hunk_start(line)
        elif current is not None and line.startswith("+"):
            current[2].append((lineno, line[1:].rstrip("\r")))
            lineno += 1
    return commits


def _hunk_start(line):
    found = re.match(r"^@@ -\S+ \+(\d+)", line)
    return int(found.group(1)) if found else 0


def address_named(token, ledger_names):
    """A token this tool judges: the address_global hatch, the bare g_<hex> form, or an
    address-invented name the data ledger already binds."""
    return bool(ADDR_GLOBAL.fullmatch(token) or BARE.fullmatch(token)
                or ((INVENTED.search(token) or LABELLED.search(token)) and token in ledger_names()))


def splice(text):
    """(text with CRLF as LF and every backslash-newline line splice removed, the offsets in
    that text where a splice was), as translation phases 1-2 do before tokenizing."""
    text = text.replace("\r\n", "\n")
    parts, offsets, last, size = [], [], 0, 0
    for match in SPLICE.finditer(text):
        parts.append(text[last:match.start()])
        size += match.start() - last
        offsets.append(size)
        last = match.end()
    parts.append(text[last:])
    return "".join(parts), offsets


def code_tokens(text):
    """(code, splice offsets, {identifier holding a 6-hex run: offset of its first use}):
    `code` is the spliced text with comments and literals blanked to spaces, offsets
    unchanged, so an original line is code.count("\\n", 0, at) + splices before it + 1."""
    spliced, offsets = splice(text)
    code = NON_CODE.sub(lambda m: NOT_NEWLINE.sub(" ", m.group(0)), spliced)
    first = {}
    for match in WORD.finditer(code):
        token = match.group(0)
        if token[0].isdigit() or token in first or not HEX_RUN.search(token):
            continue
        first[token] = match.start()
    return code, offsets, first


def read_blobs(budget, specs):
    """{spec: text} through one `git cat-file --batch` inside the budget ("" when missing)."""
    specs = list(dict.fromkeys(s for s in specs if s))
    if not specs:
        return {}
    code, out, err = budget.run([*GIT, "cat-file", "--batch"], input="".join(s + "\n" for s in specs).encode())
    if code:
        raise RuntimeError("git cat-file --batch: " + err.decode("utf-8", "replace").strip())
    got, at = {}, 0
    for spec in specs:
        end = out.index(b"\n", at)
        head, at = out[at:end].split(), end + 1
        if len(head) < 3 or head[-1] == b"missing":
            got[spec] = ""
            continue
        size = int(head[2])
        got[spec] = out[at:at + size].decode("utf-8", "replace")
        at += size + 1
    return got


class Progress:
    """What a run has done so far: a budget overrun reports it as it stands."""

    def __init__(self):
        self.files = self.done = 0
        self.stats = collections.Counter()
        self.unresolved = []
        self.found = []


def findings(commits, ledger_loader, specs, budget, progress=None):
    """[Finding] (also kept in progress.found). `specs(sha, parent, old, new)` gives the
    (old, new) blob specs of a file; `progress` counts files, new candidates, resolved
    ones, those with nothing usable instead, and keeps the unresolved names."""
    progress = progress if progress is not None else Progress()
    out = progress.found
    ledger = {}

    def load():
        if "x" not in ledger:
            ledger["x"] = ledger_loader()
            budget.check()
        return ledger["x"]

    def ledger_names():
        got = load()
        return got.bound if got is not None else {}

    files = [(sha, parent, f) for sha, parent, fs in commits for f in fs
             if f[1].startswith(SOURCE_ROOT) and f[1].lower().endswith(EXTENSIONS)]
    progress.files = len(files)
    for start in range(0, len(files), CHUNK):
        budget.check()
        chunk = files[start:start + CHUNK]
        todo = []
        for sha, parent, (old, new, added) in chunk:
            # only a file whose added lines (spliced) hold a 6-hex run can gain such a name
            if HEX_RUN.search(splice("\n".join(text for _lineno, text in added))[0]) and load() is not None:
                todo.append((sha, new, *specs(sha, parent, old, new)))
        blobs = read_blobs(budget, [spec for item in todo for spec in item[2:]])
        for sha, new, old_spec, new_spec in todo:
            budget.check()
            code, offsets, now = code_tokens(blobs.get(new_spec, ""))
            before = code_tokens(blobs[old_spec])[2] if old_spec else {}
            led = load()
            fresh = sorted((offset, name) for name, offset in now.items()
                           if name not in before and address_named(name, ledger_names))
            newlines, at = 0, 0
            for offset, name in fresh:
                newlines, at = newlines + code.count("\n", at, offset), offset
                lineno = newlines + bisect.bisect_right(offsets, offset) + 1
                progress.stats["new"] += 1
                places = led.resolve(name)
                progress.stats["resolved"] += bool(places)
                if not places:
                    progress.unresolved.append(name)
                for rva, how in places:
                    kind, shown = led.instead(rva)
                    if kind == "unusable":
                        progress.stats["unusable"] += 1
                    elif kind:
                        out.append(Finding(sha, new, lineno, name, rva, kind, shown, how))
        progress.done += len(chunk)
    return out


def message(f, limit=4):
    shown = ", ".join(f.shown[:limit]) + (" (+%d more)" % (len(f.shown) - limit) if len(f.shown) > limit else "")
    head = "%s:%d invents %s for 0x%08X" % (f.path, f.line, f.name, f.rva)
    if f.kind == "literal":
        return f"{head}, which is {f.shown[0]}: use the literal"
    if f.kind == "vtable":
        return f"{head}, which is {shown}: reach it through its class, not an extern name"
    return f"{head}; the tree already calls it {shown}: extern it or include its header"


ADVICE = {
    "owner": "Use the existing name (extern it, or include the header that declares it) instead of "
             "inventing one per address.",
    "literal": "Write the literal itself (1.0f, \"\"): the compiler emits the same reference to its pooled "
               "constant, and no global is needed.",
    "vtable": "A vtable or RTTI address is the class's: declare the class with its virtual functions and let "
              "its constructor store the vtable, instead of naming the address.",
}


# ---------------------------------------------------------------- drivers

def git(budget, *args, ok=(0,)):
    code, out, err = budget.run([*GIT, *args])
    if code not in ok:
        raise RuntimeError("git %s: %s" % (" ".join(args[:3]), err.decode("utf-8", "replace").strip()))
    return out.decode("utf-8", "replace")


def root(budget):
    return Path(git(budget, "rev-parse", "--show-toplevel").strip())


def ledger_loader(path):
    def load():
        return Ledger(path) if Path(path).exists() else None
    return load


def staged(budget, ledger_path, progress):
    text = git(budget, "diff", "--cached", "-M", "-U0", "--no-color", "--no-ext-diff", "--no-textconv",
               "--diff-filter=ACMR", "--", *PATHSPECS)
    head = "HEAD" if git(budget, "rev-parse", "-q", "--verify", "HEAD^{commit}", ok=(0, 1)).strip() else None

    def specs(_sha, _parent, old, new):
        return (f"{head}:{old}" if (old and head) else None), f":{new}"
    return findings(parse_patch(text), ledger_loader(ledger_path), specs, budget, progress)


def in_history(sha, parent, old, new):
    return (f"{parent}:{old}" if (old and parent) else None), f"{sha}:{new}"


def log_patch(budget, *rev_args):
    return parse_patch(git(budget, "log", "--no-merges", "-M", "-p", "-U0", "--no-color", "--no-ext-diff",
                           "--no-textconv", "--diff-filter=ACMR", "--format=" + SEP + "%H" + SEP + "%P",
                           *rev_args, "--", *PATHSPECS))


def emit(found, progress, shadow, elapsed, examples=None, partial=None):
    tag = "invented_names (shadow, never refuses)" if shadow else "invented_names"
    unresolved = list(dict.fromkeys(progress.unresolved))
    if not (found or unresolved or partial):
        return 0
    say = lambda text: print(text, file=sys.stderr)  # noqa: E731
    if partial:
        say(f"{tag}: {partial}")
    if found:
        say(f"{tag}: {len(found)} new address-named global(s) for retail data that already has a usable "
            f"name, or is a literal or vtable ({elapsed:.2f}s)")
        for f in found[:examples]:
            say("  " + message(f))
        if examples is not None and len(found) > examples:
            say(f"  ... and {len(found) - examples} more")
        for kind in ("owner", "literal", "vtable"):
            if any(f.kind == kind for f in found):
                say("  " + ADVICE[kind])
    elif not partial:
        say(f"{tag}: no new address-named global with a usable name instead, but not all were checked "
            f"({elapsed:.2f}s)")
    if found and progress.stats["unusable"]:
        say(f"  ({progress.stats['unusable']} more at addresses whose only other names are TU-local statics "
            "or provisional guesses: nothing usable to suggest; not listed)")
    if unresolved:
        shown = ", ".join(unresolved[:3]) + (" ..." if len(unresolved) > 3 else "")
        say(f"  not checked: {len(unresolved)} new address-named global(s) whose name spells no data-ledger "
            f"address ({shown}): unresolved")
    return 0 if (shadow or partial) else int(bool(found))


def backtest(budget, n, ref, ledger_path, examples):
    commits = log_patch(budget, "-n", str(n), ref)
    progress = Progress()
    found = findings(commits, ledger_loader(ledger_path), in_history, budget, progress)
    revs = [c[0] for c in commits]
    by_commit = collections.OrderedDict()
    for f in found:
        by_commit.setdefault(f.sha, []).append(f)
    names = collections.Counter(f.name for f in found)
    kinds = collections.Counter(f.kind for f in found)
    print(f"backtest: {len(revs)} non-merge commit(s) touching {SOURCE_ROOT} C/C++ on {ref} "
          f"({revs[-1][:10] if revs else '-'}..{revs[0][:10] if revs else '-'})")
    print(f"  would report: {len(by_commit)} commit(s) "
          f"({100.0 * len(by_commit) / max(len(revs), 1):.1f}%), {len(found)} finding(s), "
          f"{len(names)} distinct name(s), {budget.elapsed():.1f}s")
    print(f"  new address-named tokens added: {progress.stats['new']}; at a data-ledger address: "
          f"{progress.stats['resolved']}; with a usable name instead: {len(found)} (owner {kinds['owner']}, "
          f"literal {kinds['literal']}, vtable {kinds['vtable']}); only statics or guesses there: "
          f"{progress.stats['unusable']}")
    # A "bound" finding needed today's ledger binding (which the commit itself may
    # have created); a "decoded" one is found from the name alone, as live.
    decoded = [f for f in found if f.how == "decoded"]
    print(f"  found from the name alone: {len({f.sha for f in decoded})} commit(s), {len(decoded)} "
          f"finding(s); only through today's ledger binding: "
          f"{len({f.sha for f in found if f.how == 'bound'})} commit(s), {len(found) - len(decoded)} finding(s)")
    for sha, items in list(by_commit.items())[:examples]:
        subject = git(budget, "log", "-1", "--format=%s", sha).strip()
        print(f"  {sha[:10]} {subject[:90]}")
        for f in items[:3]:
            print("      " + message(f))
        if len(items) > 3:
            print(f"      ... and {len(items) - 3} more")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--commit", metavar="REV")
    mode.add_argument("--range", nargs=2, metavar=("BASE", "TIP"))
    mode.add_argument("--backtest", type=int, metavar="N")
    ap.add_argument("--ref", default="origin/master", help="--backtest: the history to replay")
    ap.add_argument("--shadow", action="store_true", help="report, never refuse (exit 0)")
    ap.add_argument("--ledger", help="data ledger (default: %s in the work tree)" % LEDGER)
    ap.add_argument("--examples", type=int, default=20)
    ap.add_argument("--budget", type=float, default=None,
                    help="wall-clock seconds (default $BFME_SHADOW_BUDGET_S or 10; 0 = none; "
                         "--backtest: none unless given)")
    a = ap.parse_args(argv)
    limit = (a.budget if a.budget and a.budget > 0 else None) if a.backtest else seconds(a.budget)
    budget = Budget(limit)
    progress = Progress()
    partial = None
    try:
        ledger_path = a.ledger or str(root(budget) / LEDGER)
        if a.backtest:
            return backtest(budget, a.backtest, a.ref, ledger_path, a.examples)
        if a.staged:
            staged(budget, ledger_path, progress)
        elif a.commit:
            findings(log_patch(budget, "--no-walk", a.commit), ledger_loader(ledger_path),
                     in_history, budget, progress)
        else:
            findings(log_patch(budget, f"{a.range[0]}..{a.range[1]}"), ledger_loader(ledger_path),
                     in_history, budget, progress)
    except BudgetExceeded:
        partial = (f"partial: budget of {budget.limit:g}s exceeded after {progress.done} of "
                   f"{progress.files if progress.files else '?'} file(s)")
    except (RuntimeError, OSError, ValueError, csv.Error) as exc:
        print(f"invented_names: could not run: {exc}", file=sys.stderr)
        return 0 if a.shadow else 2
    return emit(progress.found, progress, a.shadow, budget.elapsed(), a.examples, partial)


if __name__ == "__main__":
    sys.exit(main())
