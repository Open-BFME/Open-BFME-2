#!/usr/bin/env python3
"""Gold set of ledger identities for scoring WorldBuilder name transfer.

WorldBuilder (an internal BFME2 build) carries assertion strings that name
functions as "Class::method".  To measure a matcher that maps game.dat
functions onto those names we need, for every address the ledger already
rows, the name it carries in that same "Class::method" form and a verdict on
whether that name is a real identity or an invented placeholder:

    REAL         class and method both look like genuine source names
    PARTIAL      genuine class, placeholder method (?rva00267D65@AIUpdateInterface@@...)
    PLACEHOLDER  anything else (Rva00..., Gen_..., uw_..., BfmePod..., ...)

Pins from reverse/symbols.csv are weaker evidence: they are recorded per
address under "pins"/"pin_norms" and never change a ledger row's kind; an
address only a pin names gets "rowed": false.

The MSVC demangler below is deliberately focused: it recovers only the
qualified function name (scopes + unqualified name) and skips the type
grammar needed to get past template arguments.  Template arguments are
dropped ("vector<int>::push_back" -> "vector::push_back"), which is the form
the scorer compares in anyway.

Usage:
    python3 tools/wb_gold.py [--out build/wb/gold.jsonl] [--samples 20]

Each output line is one address: rva, va (rva + 0x400000), size, the best
row's name/class/method/kind/source, "names" (every demangled name rowed
there, ICF folds included), "norms" (REAL names in comparison form),
"entries" (per-row detail), "pins", "pin_norms" and "rowed".
"""
import argparse
import collections
import csv
import json
import random
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
SYMBOLS_CSV = ROOT / "reverse" / "symbols.csv"
DEFAULT_OUT = ROOT / "build" / "wb" / "gold.jsonl"
IMAGE_BASE = 0x400000

KINDS = ("REAL", "PARTIAL", "PLACEHOLDER")

# --------------------------------------------------------------------------
# MSVC demangling (qualified name only)
# --------------------------------------------------------------------------

OPERATORS = {
    "2": "operator new", "3": "operator delete", "4": "operator=",
    "5": "operator>>", "6": "operator<<", "7": "operator!", "8": "operator==",
    "9": "operator!=", "A": "operator[]", "B": "operator cast",
    "C": "operator->", "D": "operator*", "E": "operator++", "F": "operator--",
    "G": "operator-", "H": "operator+", "I": "operator&", "J": "operator->*",
    "K": "operator/", "L": "operator%", "M": "operator<", "N": "operator<=",
    "O": "operator>", "P": "operator>=", "Q": "operator,", "R": "operator()",
    "S": "operator~", "T": "operator^", "U": "operator|", "V": "operator&&",
    "W": "operator||", "X": "operator*=", "Y": "operator+=", "Z": "operator-=",
    "_0": "operator/=", "_1": "operator%=", "_2": "operator>>=",
    "_3": "operator<<=", "_4": "operator&=", "_5": "operator|=",
    "_6": "operator^=", "_7": "`vftable'", "_8": "`vbtable'",
    "_9": "`vcall'", "_B": "`local static guard'",
    "_D": "`vbase destructor'", "_E": "`vector deleting destructor'",
    "_F": "`default constructor closure'",
    "_G": "`scalar deleting destructor'",
    "_H": "`vector constructor iterator'",
    "_I": "`vector destructor iterator'",
    "_L": "`eh vector constructor iterator'",
    "_M": "`eh vector destructor iterator'",
    "_O": "`copy constructor closure'", "_U": "operator new[]",
    "_V": "operator delete[]", "__E": "`dynamic initializer'",
    "__F": "`dynamic atexit destructor'",
}
CTOR, DTOR = "?ctor", "?dtor"
SIMPLE_TYPES = set("CDEFGHIJKMNOXZ")
FREE_FUNCTION_CODES = set("YZ")
DYNAMIC_INIT = (OPERATORS["__E"], OPERATORS["__F"])


class DemangleError(ValueError):
    """The symbol uses grammar this focused demangler does not cover."""


class _Parser:
    """Cursor over one mangled symbol with MSVC's name back-reference table."""

    def __init__(self, text):
        self.s = text
        self.i = 0
        self.names = []

    def peek(self, n=1):
        return self.s[self.i:self.i + n]

    def take(self, n=1):
        out = self.s[self.i:self.i + n]
        if len(out) < n:
            raise DemangleError("truncated symbol")
        self.i += n
        return out

    def expect(self, text):
        if self.take(len(text)) != text:
            raise DemangleError(f"expected {text!r} at {self.i - len(text)}")

    def memorize(self, key, name):
        """Record a back-referenceable name; key is its mangled spelling."""
        if len(self.names) < 10 and key not in (k for k, _ in self.names):
            self.names.append((key, name))

    # -- names ----------------------------------------------------------

    def simple_name(self):
        end = self.s.find("@", self.i)
        if end < 0:
            raise DemangleError("unterminated name")
        name = self.s[self.i:end]
        self.i = end + 1
        return name

    def template_name(self):
        """'?$name@args@' -> (mangled spelling, 'name'); arguments dropped."""
        start = self.i
        self.expect("?$")
        outer = self.names
        self.names = []
        if self.peek() == "?":
            name = self.special_name()
        else:
            name = self.simple_name()
            self.memorize(name, name)
        self.template_args()
        self.names = outer
        return self.s[start:self.i], name

    def special_name(self):
        """'?0' ctor, '?1' dtor, '?4' operator=, '?_G', '?__E', ..."""
        self.expect("?")
        code = self.take()
        if code == "0":
            return CTOR
        if code == "1":
            return DTOR
        if code == "_":
            code += self.take()
            if code == "__":
                code += self.take()
        if code not in OPERATORS:
            raise DemangleError(f"unknown operator code {code!r}")
        return OPERATORS[code]

    def unqualified_name(self):
        c = self.peek()
        if c.isdigit():
            self.i += 1
            index = int(c)
            if index >= len(self.names):
                raise DemangleError("name back-reference out of range")
            return self.names[index][1]
        if self.peek(2) == "?$":
            key, name = self.template_name()
            self.memorize(key, name)
            return name
        if c == "?":
            return self.special_name()
        name = self.simple_name()
        self.memorize(name, name)
        return name

    def scope(self):
        if self.peek(2) == "?A":
            self.i += 2
            self.simple_name()
            return "`anonymous namespace'"
        if self.peek() == "?" and self.peek(2) != "?$":
            raise DemangleError("local or numbered scope")
        return self.unqualified_name()

    def scopes(self):
        """Scopes up to the terminating '@', returned outermost first."""
        out = []
        while self.peek() != "@":
            if not self.peek():
                raise DemangleError("unterminated scope list")
            out.append(self.scope())
        self.i += 1
        return out[::-1]

    def qualified_name(self):
        name = self.unqualified_name()
        return self.scopes() + [name]

    # -- types (parsed only to be skipped) ------------------------------

    def number(self):
        if self.peek() == "?":
            self.i += 1
        c = self.take()
        if c.isdigit():
            return int(c) + 1
        value = 0
        while c != "@":
            if not "A" <= c <= "P":
                raise DemangleError("bad number")
            value = value * 16 + ord(c) - ord("A")
            c = self.take()
        return value

    def template_args(self):
        while self.peek() != "@":
            if not self.peek():
                raise DemangleError("unterminated template arguments")
            self.template_arg()
        self.i += 1

    def template_arg(self):
        head = self.peek(3)
        if head in ("$$V", "$$Z"):
            self.i += 3
        elif head[:2] == "$0":
            self.i += 2
            self.number()
        elif head[:2] in ("$1", "$E", "$H", "$I", "$J"):
            self.i += 2
            self.encoded_symbol()
        elif head[:2] == "$2":
            self.i += 2
            self.number()
            self.number()
        elif head[:2] in ("$D", "$F", "$G", "$Q"):
            self.i += 2
            self.number()
        else:
            self.type()

    def encoded_symbol(self):
        """A symbol used as a template argument: '?name@scope@@<encoding>'."""
        self.expect("?")
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
        else:
            self.function_signature(code)

    def storage_cv(self):
        while self.peek() in ("E", "F", "I"):
            self.i += 1
        self.take()

    def type(self):
        c = self.take()
        if c.isdigit() or c in SIMPLE_TYPES:
            return
        if c == "_":
            self.take()
        elif c in "TUV":
            self.qualified_name()
        elif c == "W":
            self.take()
            self.qualified_name()
        elif c in "PQRSAB":
            self.pointee()
        elif c == "Y":
            for _ in range(self.number()):
                self.number()
            self.type()
        elif c == "?":
            self.storage_cv()
            self.type()
        elif c == "$":
            self.dollar_type()
        else:
            raise DemangleError(f"unknown type code {c!r}")

    def dollar_type(self):
        code = self.take(2)
        if code in ("$Q", "$R"):
            self.pointee()
        elif code == "$C":
            self.storage_cv()
            self.type()
        elif code == "$A":
            self.expect("6")
            self.function_type()
        elif code == "$B":
            self.type()
        elif code == "$T":
            return
        elif code == "$Y":
            self.qualified_name()
        else:
            raise DemangleError(f"unknown $-type ${code}")

    def pointee(self):
        while self.peek() in ("E", "F", "I"):
            self.i += 1
        cv = self.take()
        if cv == "6":
            self.function_type()
        elif cv == "8":
            self.qualified_name()
            self.storage_cv()
            self.function_type()
        elif cv in "QRSTUVWXYZ":
            self.qualified_name()
            self.type()
        elif cv in "ABCD":
            self.type()
        else:
            raise DemangleError(f"unknown pointee qualifier {cv!r}")

    def function_type(self):
        self.take()  # calling convention
        self.return_type()
        self.arg_list()
        self.throw_spec()

    def function_signature(self, code):
        """Signature after the function-class code (A..Z, $...)."""
        if code == "$":
            raise DemangleError("thunk symbols not supported")
        if code in "ABEFIJMNQRUV":
            self.storage_cv()
        self.function_type()

    def return_type(self):
        if self.peek() == "@":
            self.i += 1
        else:
            self.type()

    def arg_list(self):
        if self.peek() == "X":
            self.i += 1
            return
        while self.peek() not in ("@", "Z"):
            if not self.peek():
                raise DemangleError("unterminated argument list")
            self.type()
        self.i += 1

    def throw_spec(self):
        if self.peek() == "Z":
            self.i += 1
        elif self.peek(2) == "_E":
            self.i += 2


Demangled = collections.namedtuple(
    "Demangled", "scopes name is_member is_function")


def demangle(symbol):
    """Mangled MSVC symbol -> Demangled(scopes, name, is_member, is_function).

    scopes is outermost first, with template arguments dropped; ctor and
    dtor names are spelled out from the innermost scope.  Plain C names
    (`_inflate`, `uw_...`) come back unscoped, without the leading
    underscore, and are assumed to be functions.  Data symbols (variables,
    vftables) report is_function False.  Raises DemangleError on grammar
    outside this focused subset.
    """
    if not symbol.startswith("?"):
        bare = symbol[1:] if symbol.startswith("_") else symbol
        return Demangled([], bare.split("@", 1)[0], False, True)
    p = _Parser(symbol)
    p.expect("?")
    if p.peek(2) == "?$":
        key, name = p.template_name()
        p.memorize(key, name)
    elif p.peek() == "?":
        name = p.special_name()
    else:
        name = p.simple_name()
        p.memorize(name, name)
    scopes = p.scopes()
    code = p.peek()
    is_function = not code.isdigit()
    if name in DYNAMIC_INIT:
        target = qualified(scopes[:-1], scopes[-1])
        return Demangled([], f"{name[:-1]} for '{target}''", False, True)
    if name in (CTOR, DTOR):
        if not scopes:
            raise DemangleError("constructor without class")
        name = scopes[-1] if name == CTOR else "~" + scopes[-1]
    is_member = bool(scopes) and code not in FREE_FUNCTION_CODES
    return Demangled(scopes, name, is_member, is_function)


def qualified(scopes, name):
    return "::".join(scopes + [name])


# --------------------------------------------------------------------------
# Comparison form, shared with wb_score.py / wb_leads.py
# --------------------------------------------------------------------------

def strip_template_args(text):
    """Drop balanced <...> groups, leaving 'operator<' style names alone."""
    out, depth = [], 0
    for i, c in enumerate(text):
        if c == "<" and not text[:i].endswith("operator") \
                and not text[:i].endswith("operator<"):
            depth += 1
        elif c == ">" and depth:
            depth -= 1
        elif not depth:
            out.append(c)
    return "".join(out)


def normalize(name):
    """'ns::Outer<T>::Class<U>::method' -> 'Class::method' (last two parts)."""
    parts = [p.strip() for p in strip_template_args(name).split("::") if p]
    return "::".join(parts[-2:])


# --------------------------------------------------------------------------
# Placeholder classification
# --------------------------------------------------------------------------

# Address-derived or tool-invented identifiers, tested against one name
# component (class or method) with any leading '~' removed.  The ledger's
# placeholder vocabulary is open-ended, so these err towards PLACEHOLDER: a
# genuine name misfiled here only moves a row from the scoring set to the
# "new name" set, while an invented name filed as REAL would make a correct
# WorldBuilder name score as wrong.
PLACEHOLDER_PATTERNS = {
    "rva": r"_?[Rr]va?[0-9A-Fa-f]{5,}.*|Rva[A-Z].*",  # rva00267D65, RvaSmartPtr12
    "gen": r"[Gg]en(?:-|_uw|_[0-9A-Fa-f]{6}|[0-9A-F]{6}).*",  # Gen_0088A5D0 (not zlib gen_codes)
    "bfme": r"(?i:.*bfme).*",                      # BfmePod172, aiBfmeCommand35, BFME2...
    "unwind": r"uw_.*",
    "open2": r"Open2.*",                           # Open2Rec74A060, Open2Store9A2680
    "unknown": r"Unknown.*",                       # UnknownSlot6
    "zero_getter": r".*ZeroGetter",
    "hex_suffix": r".*_[0-9A-Fa-f]{6,}",           # dup_002C485, d_00884e50, Parse_25287D
    "hex_tail": r".*[a-z](?=[0-9A-F]*[0-9])[0-9A-F]{6}",  # Intermediate3AE6A9
    "digit_tail": r".*[a-z](?!(?:32|64)$)[0-9]{2,}",  # ListValue12, not adler32/Int64
    "address": r".*[0-9A-F]{8}.*",                 # g_00E06408, Sub005CD540Outer
}
PLACEHOLDER_COMPONENT = re.compile(
    "^(?:" + "|".join(PLACEHOLDER_PATTERNS.values()) + ")$")
GENERATED_SOURCE = re.compile(r"^Code/gen_")


def is_placeholder(component):
    return bool(PLACEHOLDER_COMPONENT.match(component.lstrip("~")))


def classify(cls, method, source=""):
    """REAL / PARTIAL / PLACEHOLDER for one demangled name."""
    if GENERATED_SOURCE.match(source):
        return "PLACEHOLDER"
    method_fake = is_placeholder(method)
    if not cls:
        return "PLACEHOLDER" if method_fake else "REAL"
    if is_placeholder(cls):
        return "PLACEHOLDER"
    return "PARTIAL" if method_fake else "REAL"


# --------------------------------------------------------------------------
# Gold set
# --------------------------------------------------------------------------

def ledger_rows(path=FUNCTIONS_CSV):
    """Stream matched ledger rows."""
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row["status"] == "matched" and row["target_rva"]:
                yield row


def pin_rows(path=SYMBOLS_CSV):
    """Stream symbols.csv pins (name, address)."""
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row["address"]:
                yield row


def describe(symbol, source=""):
    """Mangled function symbol -> name/class/method/kind dict.

    Returns None for data symbols; raises DemangleError when the symbol
    cannot be demangled.
    """
    d = demangle(symbol)
    if not d.is_function:
        return None
    cls = d.scopes[-1] if d.is_member else ""
    return {
        "symbol": symbol,
        "name": qualified(d.scopes, d.name),
        "norm": normalize(qualified([cls] if cls else [], d.name)),
        "class": cls,
        "method": d.name,
        "kind": classify(cls, d.name, source),
        "source": source,
    }


def new_record(rva):
    return {"rva": rva, "va": rva + IMAGE_BASE, "size": 0,
            "entries": [], "pins": []}


def build_gold(rows, pins):
    """Group ledger rows and pins by address.

    Returns ({rva: record}, [symbols that failed to demangle]).  Records
    whose address only a pin names have "rowed": false.
    """
    by_rva, failed = {}, []
    for row in rows:
        try:
            info = describe(row["name"], row["source"])
        except DemangleError:
            failed.append(row["name"])
            continue
        rva = int(row["target_rva"], 16)
        rec = by_rva.setdefault(rva, new_record(rva))
        rec["size"] = max(rec["size"], int(row["target_size"] or 0))
        rec["entries"].append(info)
    for pin in pins:
        try:
            info = describe(pin["name"])
        except DemangleError:
            failed.append(pin["name"])
            continue
        if info is not None:
            rva = int(pin["address"], 16)
            del info["source"]
            by_rva.setdefault(rva, new_record(rva))["pins"].append(info)
    for rec in by_rva.values():
        finalize(rec)
    return by_rva, failed


def finalize(rec):
    """Address-level name/kind from the best ledger row, else the best pin."""
    rank = {k: i for i, k in enumerate(KINDS)}
    for key in ("entries", "pins"):
        rec[key].sort(key=lambda e: rank[e["kind"]])
    rec["rowed"] = bool(rec["entries"])
    best = (rec["entries"] or rec["pins"])[0]
    for key in ("name", "class", "method", "kind"):
        rec[key] = best[key]
    rec["source"] = best.get("source", "")
    rec["names"] = list(dict.fromkeys(e["name"] for e in rec["entries"]))
    rec["norms"] = real_norms(rec["entries"])
    rec["pin_norms"] = real_norms(rec["pins"])


def real_norms(entries):
    return sorted({e["norm"] for e in entries if e["kind"] == "REAL"})


def load_gold(path=DEFAULT_OUT):
    """gold.jsonl -> {va: record}."""
    with open(path, encoding="utf-8") as fh:
        return {r["va"]: r for r in map(json.loads, fh)}


def report(gold, failed, samples, seed):
    rowed = [r for r in gold.values() if r["rowed"]]
    counts = collections.Counter(r["kind"] for r in rowed)
    rows = collections.Counter(e["kind"] for r in rowed for e in r["entries"])
    pinned = collections.Counter(r["kind"] for r in gold.values()
                                 if not r["rowed"])
    print(f"rowed addresses: {len(rowed)}  rows: {sum(rows.values())}  "
          f"pin-only addresses: {sum(pinned.values())}  "
          f"undemangled symbols: {len(failed)}")
    for kind in KINDS:
        print(f"  {kind:<12} addresses {counts[kind]:>6}  rows {rows[kind]:>6}"
              f"  pin-only {pinned[kind]:>5}")
    multi = sum(1 for r in rowed if len(r["names"]) > 1)
    print(f"  rowed addresses carrying several names (ICF folds): {multi}")
    rng = random.Random(seed)
    for kind in KINDS:
        pool = sorted((r for r in rowed if r["kind"] == kind),
                      key=lambda r: r["rva"])
        print(f"\n== {kind} samples ==")
        for r in rng.sample(pool, min(samples, len(pool))):
            print(f"  0x{r['rva']:08X} {r['size']:>5}  {r['name']}")
    if failed:
        print("\n== undemangled samples ==")
        for sym in rng.sample(failed, min(samples, len(failed))):
            print("  " + sym)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--csv", type=Path, default=FUNCTIONS_CSV)
    ap.add_argument("--symbols", type=Path, default=SYMBOLS_CSV)
    ap.add_argument("--out", type=Path, default=DEFAULT_OUT)
    ap.add_argument("--samples", type=int, default=20)
    ap.add_argument("--seed", type=int, default=0)
    args = ap.parse_args(argv)

    gold, failed = build_gold(ledger_rows(args.csv), pin_rows(args.symbols))
    args.out.parent.mkdir(parents=True, exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as fh:
        for rva in sorted(gold):
            fh.write(json.dumps(gold[rva], sort_keys=True) + "\n")
    report(gold, failed, args.samples, args.seed)
    print(f"\nwrote {args.out}")


if __name__ == "__main__":
    sys.exit(main())
