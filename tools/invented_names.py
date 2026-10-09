#!/usr/bin/env python3
"""Report new address-named globals for retail data that already has a real name (SHADOW).

WHY. The per-function byte gate masks DIR32 (global) relocations, so a body
matches whatever it calls a global. Agents therefore invent one per address --
g_Va00BBB8D8, g_00DFE758, g_Rva0107301CEmptyString -- and the tree grows a
second, third, ninth name for one retail global: reverse/data_ledger.csv binds
TheWritableGlobalData, g_00DFE758, g_Va009FE758 and six more to 0x009FE758.
Each extra name is a separate definition the link has to reconcile.

WHAT. Added lines of Code/ C/C++ sources (`git diff -U0`), comments and string
literals removed. A token is address-invented when it matches
tools/hatch_counters.py's `address_global` hatch (g_...Va/Rva/DAT_<hex>), the
bare g_<hex> form, or is an address-invented name (data_ledger.py's rule) the
data ledger already binds. A token the file already held before the change is
not new and is skipped; each (file, name) is reported once, at its first added
line.

ADDRESS. A name the data ledger already binds resolves to where it is bound.
Otherwise its hex run is read as a VA (image base 0x400000; tools/name_globals.py's
reading of an address >= 0x400000) and then as an RVA -- first for `Rva` names --
and the first reading that is an exact data-ledger address wins. A name that
resolves to no ledger address is not reported.

REAL NAME. Any other name the ledger binds at that address that is not
address-invented and not a compiler literal (??_C@, __real@, __xmm@);
vtables, RTTI and imports count as real. TU-local statics are shown as
`name (static, file)`.

REPORT ONLY. --shadow (the hook) always exits 0; without it, exit 1 on a finding.

  python3 tools/invented_names.py --staged [--shadow]        the commit hook
  python3 tools/invented_names.py --commit REV               one commit against its parent
  python3 tools/invented_names.py --range BASE TIP           every commit in BASE..TIP
  python3 tools/invented_names.py --backtest N [--ref REF]   last N non-merge commits touching Code/
"""
import argparse
import collections
import csv
import re
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from hatch_counters import ADDR_GLOBAL  # noqa: E402  (the address_global hatch)

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
# Rva005F5C77Base0: an address label whose hex run runs on into a word that
# starts with a hex letter, which INVENTED's end anchor misses
LABELLED = re.compile(r"(?:Rva|RVA|rva|Va|VA|DAT_)(?=[0-9A-F]{0,7}[0-9])[0-9A-F]{6,8}")
# g_00DFE758: the bare form the address_global hatch does not count
BARE = re.compile(r"(?<![A-Za-z0-9_])g_(?=[0-9A-Fa-f]{0,7}[0-9])[0-9A-Fa-f]{6,8}\w*")
# the hex run a name encodes and the label before it: upper-case hex as in
# INVENTED, then any case after an explicit label
ENCODED = (re.compile(r"(Rva|RVA|rva|Va|VA|va|DAT_?|g_|At|[a-z_])((?=[0-9A-F]{0,7}[0-9])[0-9A-F]{6,8})"),
           re.compile(r"(Rva|RVA|rva|Va|VA|va|DAT_?|g_)((?=[0-9A-Fa-f]{0,7}[0-9])[0-9A-Fa-f]{6,8})"))
TOKEN = re.compile(r"(?<![A-Za-z0-9_])[A-Za-z_]\w*")
HEX_RUN = re.compile(r"[0-9A-Fa-f]{6}")
NON_CODE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?(?:\*/|$)|//.*$')
DOC_LINE = re.compile(r"^\s*\*(?:\s|/|$)")      # " * text": inside a block comment


def git(*args, binary=False, check=True):
    got = subprocess.run(["git", "-c", "core.quotePath=false", *args], capture_output=True)
    if check and got.returncode:
        raise RuntimeError("git %s: %s" % (" ".join(args[:3]), got.stderr.decode("utf-8", "replace").strip()))
    return got.stdout if binary else got.stdout.decode("utf-8", "replace")


def identifier(symbol):
    """The source identifier of a decorated or C symbol (data_ledger.identifier)."""
    found = re.match(r"^\?(\w+)@", symbol)
    if found:
        return found.group(1)
    return symbol[1:] if symbol.startswith("_") else symbol


def invented(name):
    return bool(INVENTED.search(name) or LABELLED.search(name) or ADDR_GLOBAL.search(name)
                or BARE.search(name))


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

    def real_names(self, rva):
        canonical, names = self.rows.get(rva, ("", []))
        out = []
        for symbol, source in sorted(names, key=lambda n: (n[0] != canonical, n[0], n[1] or "")):
            if symbol.startswith(LITERALS) or invented(identifier(symbol)):
                continue
            shown = display(symbol)
            if source:
                shown += " (static, %s)" % source.rsplit("/", 1)[-1]
            if shown not in out:
                out.append(shown)
        return out


def display(symbol):
    vtable = re.match(r"^\?\?_7(\w+(?:@\w+)*)@@6", symbol)
    if vtable:
        return "::".join(reversed(vtable.group(1).split("@"))) + "::`vftable'"
    if symbol.startswith(("??", "__imp_")):
        return symbol
    return identifier(symbol)


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


def candidates(added, ledger_names):
    """{name: first line number} of address-invented tokens on added code lines."""
    out = {}
    in_block = False
    for lineno, text in added:
        if in_block:
            if "*/" not in text:
                continue
            text, in_block = text.split("*/", 1)[1], False
        elif DOC_LINE.match(text):
            continue
        for found in NON_CODE.finditer(text):
            if found.group(0).startswith("/*") and not found.group(0).endswith("*/"):
                in_block = True
        code = NON_CODE.sub(" ", text)
        if not HEX_RUN.search(code):
            continue
        for match in TOKEN.finditer(code):
            token = match.group(0)
            if token in out or not HEX_RUN.search(token):
                continue
            if ADDR_GLOBAL.fullmatch(token) or BARE.fullmatch(token):
                out[token] = lineno
            elif (INVENTED.search(token) or LABELLED.search(token)) and token in ledger_names():
                out[token] = lineno     # an address-invented name the ledger already binds to data
    return out


class Blobs:
    """Old file contents through one `git cat-file --batch`."""

    def __init__(self):
        self.proc = None

    def get(self, spec):
        if self.proc is None:
            self.proc = subprocess.Popen(["git", "cat-file", "--batch"], stdin=subprocess.PIPE,
                                         stdout=subprocess.PIPE)
        self.proc.stdin.write(spec.encode("utf-8") + b"\n")
        self.proc.stdin.flush()
        head = self.proc.stdout.readline().split()
        if len(head) < 3 or head[-1] == b"missing":
            return ""
        size = int(head[2])
        data = self.proc.stdout.read(size)
        self.proc.stdout.read(1)
        return data.decode("utf-8", "replace")

    def close(self):
        if self.proc is not None:
            self.proc.stdin.close()
            self.proc.wait()


def findings(commits, ledger_loader, old_rev_of, stats=None):
    """[(commit, path, line, name, rva, real names, how resolved)]; `stats` (a Counter)
    also counts the new candidates and those that resolved to a ledger address."""
    out = []
    stats = collections.Counter() if stats is None else stats
    blobs = Blobs()
    ledger = {}

    def load():
        if "x" not in ledger:
            ledger["x"] = ledger_loader()
        return ledger["x"]

    def ledger_names():
        got = load()
        return got.bound if got is not None else {}

    try:
        for sha, parent, files in commits:
            for old, new, added in files:
                if not new.startswith(SOURCE_ROOT) or not new.lower().endswith(EXTENSIONS):
                    continue
                found = candidates(added, ledger_names)
                if not found:
                    continue
                rev = old_rev_of(sha, parent)
                before = blobs.get(f"{rev}:{old}") if (old and rev) else ""
                led = load()
                if led is None:
                    continue
                for name, lineno in sorted(found.items(), key=lambda kv: kv[1]):
                    if re.search(r"(?<![A-Za-z0-9_])%s(?![A-Za-z0-9_])" % re.escape(name), before):
                        continue
                    stats["new"] += 1
                    stats["resolved"] += bool(led.resolve(name))
                    for rva, how in led.resolve(name):
                        real = led.real_names(rva)
                        if real:
                            out.append((sha, new, lineno, name, rva, real, how))
    finally:
        blobs.close()
    return out


def message(path, lineno, name, rva, real, limit=4):
    shown = ", ".join(real[:limit]) + (" (+%d more)" % (len(real) - limit) if len(real) > limit else "")
    return "%s:%d invents %s for 0x%08X; the tree already calls it %s" % (path, lineno, name, rva, shown)


# ---------------------------------------------------------------- drivers

def root():
    return Path(git("rev-parse", "--show-toplevel").strip())


def ledger_loader(path):
    def load():
        return Ledger(path) if Path(path).exists() else None
    return load


def staged(ledger_path):
    text = git("diff", "--cached", "-M", "-U0", "--no-color", "--no-ext-diff", "--no-textconv",
               "--diff-filter=ACMR", "--", *PATHSPECS)
    head = "HEAD" if subprocess.run(["git", "rev-parse", "-q", "--verify", "HEAD^{commit}"],
                                    capture_output=True).returncode == 0 else None
    return findings(parse_patch(text), ledger_loader(ledger_path), lambda _sha, _parent: head)


def log_patch(*rev_args):
    return parse_patch(git("log", "--no-merges", "-M", "-p", "-U0", "--no-color", "--no-ext-diff",
                           "--no-textconv", "--diff-filter=ACMR", "--format=" + SEP + "%H" + SEP + "%P",
                           *rev_args, "--", *PATHSPECS))


def emit(found, shadow, elapsed, examples=None):
    if not found:
        return 0
    tag = "invented_names (shadow, never refuses)" if shadow else "invented_names"
    print(f"{tag}: {len(found)} new address-named global(s) where the data ledger already has a real "
          f"name ({elapsed:.2f}s)", file=sys.stderr)
    for _sha, path, lineno, name, rva, real, _how in found[:examples]:
        print("  " + message(path, lineno, name, rva, real), file=sys.stderr)
    if examples is not None and len(found) > examples:
        print(f"  ... and {len(found) - examples} more", file=sys.stderr)
    print("  Use the existing name (extern it, or include the header that declares it) instead of "
          "inventing one per address.", file=sys.stderr)
    return 0 if shadow else 1


def backtest(n, ref, ledger_path, examples):
    t0 = time.time()
    commits = log_patch("-n", str(n), ref)
    stats = collections.Counter()
    found = findings(commits, ledger_loader(ledger_path), lambda _sha, parent: parent, stats)
    revs = [c[0] for c in commits]
    by_commit = collections.OrderedDict()
    for f in found:
        by_commit.setdefault(f[0], []).append(f)
    names = collections.Counter(f[3] for f in found)
    print(f"backtest: {len(revs)} non-merge commit(s) touching {SOURCE_ROOT} C/C++ on {ref} "
          f"({revs[-1][:10] if revs else '-'}..{revs[0][:10] if revs else '-'})")
    print(f"  would report: {len(by_commit)} commit(s) "
          f"({100.0 * len(by_commit) / max(len(revs), 1):.1f}%), {len(found)} finding(s), "
          f"{len(names)} distinct name(s), {time.time() - t0:.1f}s")
    print(f"  new address-named tokens added: {stats['new']}; at a data-ledger address: "
          f"{stats['resolved']}; of those with a real name there: {len(found)}")
    # A "bound" finding needed today's ledger binding (which the commit itself may
    # have created); a "decoded" one is found from the name alone, as live.
    decoded = [f for f in found if f[6] == "decoded"]
    print(f"  found from the name alone: {len({f[0] for f in decoded})} commit(s), {len(decoded)} "
          f"finding(s); only through today's ledger binding: "
          f"{len({f[0] for f in found if f[6] == 'bound'})} commit(s), {len(found) - len(decoded)} finding(s)")
    for sha, items in list(by_commit.items())[:examples]:
        subject = git("log", "-1", "--format=%s", sha).strip()
        print(f"  {sha[:10]} {subject[:90]}")
        for _sha, path, lineno, name, rva, real, _how in items[:3]:
            print("      " + message(path, lineno, name, rva, real))
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
    a = ap.parse_args(argv)
    t0 = time.time()
    try:
        ledger_path = a.ledger or str(root() / LEDGER)
        if a.backtest:
            return backtest(a.backtest, a.ref, ledger_path, a.examples)
        if a.staged:
            found = staged(ledger_path)
        elif a.commit:
            found = findings(log_patch("--no-walk", a.commit), ledger_loader(ledger_path),
                             lambda _sha, parent: parent)
        else:
            found = findings(log_patch(f"{a.range[0]}..{a.range[1]}"), ledger_loader(ledger_path),
                             lambda _sha, parent: parent)
    except (RuntimeError, OSError, ValueError, csv.Error) as exc:
        print(f"invented_names: could not run: {exc}", file=sys.stderr)
        return 0 if a.shadow else 2
    return emit(found, a.shadow, time.time() - t0, a.examples)


if __name__ == "__main__":
    sys.exit(main())
