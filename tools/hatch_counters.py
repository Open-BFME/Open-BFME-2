#!/usr/bin/env python3
"""Escape-hatch counters: a keyed, shrink-only register of every way around the byte gate.

Each hatch below lets a row match without the source saying what retail's
source said: a selectany definition, a hand `/alternatename`, a symbols.csv
pin, an `object-symbol=` alias row, a global named after its address, a
`class-gate: allow`, a `present-unmatched` marker, a `#pragma optimize`, an
`__emit` line, a `db` byte in an .asm dump. None is wrong on its own; growth
of any of them is how a fleet routes around a check it cannot pass.

The baseline (BASELINE below) has one line per occurrence key:

    hatch <TAB> path <TAB> token <TAB> count [<TAB> allow=<blob>]

RULES (the commit gate, --staged):
  1. A staged file may not hold more occurrences of a key than the staged
     baseline grants it.
  2. A baseline line may only shrink by hand. A lower count is re-verified:
     the staged file must really hold no more than that.
  3. A baseline line may grow only (a) as a move, when the hatch+token total
     over the whole baseline does not grow (a renamed file, a function moved
     between units; `--update` writes it), or (b) through a tool-written
     allowance, `--allow PATH --reason TEXT`, whose allow=<blob> is the git
     blob of the staged file it describes.
  4. Anomaly freeze: if a hatch's baseline total would exceed twice its total
     24 h ago (and by at least FREEZE_MIN), allowances for that hatch are
     refused until a commit carrying the trailer
         Verifier-Change: hatch-freeze-lift <hatch|all> <reason>
     lands; the lift commit's total becomes the new reference.
  5. The retail inventories (tools/retail_inventory.py) are tool-owned: a
     staged change to them is regenerated and must match byte for byte.
  6. A register line `# mode: shadow` reports rule 1-4 findings without
     refusing (the 48 h shadow before enforcement). `# mode: enforce` (also
     the default: a register with no mode line is enforced) refuses; enforce
     may never go back to shadow, and a mode line, once the parent has one,
     may not be dropped. Rule 5, a deleted register, a downgrade and a wrong
     first register are refused in both modes; a downgrade is judged as
     enforced.
     In shadow, findings the commit adds get a framed, counted banner (and
     --note-file, which the pre-commit hook repeats last); findings HEAD
     already carries are tagged [already in HEAD] and listed briefly.
     Enforced, a commit is refused for what IT adds: an excess HEAD already
     carried over HEAD's register (an unverified commit, a register line a
     rebase merged low) is reported as inherited and not refused, so one
     seat's drift never blocks the next seat that touches the file. Lowering
     a line below what the file carries is still refused (rule 2).
  7. Reseed, shadow only. A register left in shadow drifts: commits it never
     refused grew the tree past it, so every touched file reports growth that
     commit did not make. `--reseed` rewrites the whole register from the
     staged tree (no allow= stamps; `--mode enforce` also flips it, else the
     mode is kept) and is refused once the register says `# mode: enforce`:
     an enforced register is never re-derived from the tree it judges. The
     gate takes a staged register that raises lines as a reseed only while
     the parent's register is in shadow and the staged one equals the staged
     tree exactly (one full scan, as for the first register); anything short
     of that is judged line by line as before. So the reseed and the flip land
     as ONE commit, carrying `Verifier-Change: hatch-reseed <why>`
     (tools/protected_paths.py asks for a trailer on any baseline edit).
  8. Respellable hatches. An /alternatename, a present-unmatched marker and a
     selectany line are keyed by a token a rename respells (a mangled name, a
     label, a declaration). Once the code-identity register
     (CODE_IDENTITY below) is enforced at HEAD and in the commit, so that
     code_identity_gate judges each added /alternatename, the unit judged for
     those is the file: its count of that hatch may not rise, and a token
     traded for another at the same count is a respelling, noted, not refused.
     Until then they are judged per token like every other hatch (a pin and an
     alias row per address). A register line moved to another file (rule 3a)
     and a respelling each consume an old occurrence, once: every net increase
     needs an admission.
  9. object-symbol= naming a compiler label (`$L<n>` funclet, `_$E<n>`
     dynamic initializer), the row's own name or an anonymous-namespace
     respelling of it is no hatch: it is the only way to address a body with
     no source-level name, and every funclet landing writes one. Nor is a
     ?dup_<rva> row (the name is minted per address and nothing calls it).
     Any other row binding a name to another symbol counts, a Gen_/Rva<RVA>
     placeholder name included (build.is_alias_row excuses those, but they
     are link names this tree calls).
 10. Address-named globals rebound to the data ledger's owner. An
     address_global token the data ledger (DATA_LEDGER, as HEAD has it)
     records as an alias spelling at an address, traded in the same file for
     that address's owner spelling (`extern int g_Va00E09FA4` ->
     `extern T *g_Va0130A588`, the fix data_check's wrong-name finding asks
     for), is a respelling: each alias occurrence explains one owner
     occurrence, once, and never the other way round. Any other new
     address-named token still needs an admission. A data_rows.csv row
     (DATA_ROWS) names the owner at its address, as data_check reads it.

Usage:
  python3 tools/hatch_counters.py --staged              the commit gate
  python3 tools/hatch_counters.py --report              per-hatch totals (HEAD baseline vs tree)
  python3 tools/hatch_counters.py --update              rewrite the baseline from the tree;
                                                        shrinks and moves only
  python3 tools/hatch_counters.py --allow PATH... --reason TEXT
                                                        also admit growth in PATHs (tool allowance)
  python3 tools/hatch_counters.py --admit PATH --reason TEXT [--tokens T...]
                                                        the same for one file, scoped: rescans
                                                        only PATH (what tools call)

Tools that write a hatch after checking it call admit() themselves (BFME2:
pin_admission.py --add, add_match.py --pin; BFME1: add_match.py for a verified
row whose object-symbol= names a compiler label), so a checked, tool-written
hatch passes and a hand-written one is refused once the register is enforced.
admit() records each admission (the occurrences it saw, the allow= stamps it wrote)
in the worktree's git dir until HEAD moves, so admissions accumulate across calls in
one working change whatever edits the file in between, while a register line typed
by hand (any stamp) or a pin renamed or added at an admitted address stays refused;
ungranted() then proves the register grants what the tool wrote.
  python3 tools/hatch_counters.py --restamp PATH        after editing PATH since a tool admitted a hatch
                                                        in it: re-stamp those admissions (nothing new)
  python3 tools/hatch_counters.py --write-baseline      first baseline only (refuses if one exists)
  python3 tools/hatch_counters.py --reseed [--mode enforce]
                                                        rewrite a SHADOW register from the staged
                                                        tree (rule 7); --mode enforce is the flip
"""
import argparse
import collections
import csv
import io
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(os.environ.get("HATCH_ROOT") or Path(__file__).resolve().parent.parent)

if (ROOT / "targets" / "game" / "reverse").is_dir():      # Open-BFME-1
    BASELINE = "targets/game/reverse/hatch_baseline.tsv"
    SOURCE_ROOTS = ("game/", "worldbuilder/")
    PIN_FILE = re.compile(r"^targets/[^/]+/reverse/symbols\.csv$")
    LEDGER_FILE = re.compile(r"^targets/[^/]+/reverse/functions\.csv$")
    INVENTORY_DIR = "targets/game/reverse/retail_inventory/"
    CODE_IDENTITY = "targets/game/reverse/code_identity_baseline.tsv"
    DATA_LEDGER = "targets/game/reverse/data_ledger.csv"
    DATA_ROWS = "targets/game/reverse/data_rows.csv"
else:                                                       # Open-BFME-2
    BASELINE = "reverse/hatch_baseline.tsv"
    SOURCE_ROOTS = ("Code/", "reference/shims/")
    PIN_FILE = re.compile(r"^reverse/symbols\.csv$")
    LEDGER_FILE = re.compile(r"^reverse/functions\.csv$")
    INVENTORY_DIR = "reverse/retail_inventory/"
    CODE_IDENTITY = "reverse/code_identity_baseline.tsv"
    DATA_LEDGER = "reverse/data_ledger.csv"
    DATA_ROWS = "reverse/data_rows.csv"

CODE_EXT = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".inl")
FREEZE_WINDOW = 24 * 3600
FREEZE_MIN = 5
LIFT = re.compile(r"^Verifier-Change:[ \t]*hatch-freeze-lift[ \t]+(\S+)", re.MULTILINE)

HATCHES = ("selectany", "alternatename", "pin", "object_symbol", "address_global",
           "class_gate_allow", "present_unmatched", "pragma_optimize", "emit", "asm_bytes")
# rule 8: judged per file, not per token (a rename respells the token, not the count), once
# the code-identity register is enforced (STATE["respellable"]; per token until then)
RESPELLABLE = frozenset(("alternatename", "present_unmatched", "selectany"))
# rule 9: object-symbol= naming one of these is the compiler's own name for the body
COMPILER_LABEL = re.compile(r"\$L\d+|_\$E\d+")

SELECTANY = re.compile(r"__declspec\s*\(\s*selectany\s*\)")
ALTNAME = re.compile(r"[/-]alternatename:([^=\s\"]+)=([^\s\"]+)", re.IGNORECASE)
PRAGMA_OPT = re.compile(r"(?:^\s*#\s*pragma\s+|\b__pragma\s*\(\s*)optimize\s*\(([^)]*)\)")
EMIT = re.compile(r"\b__emit\b")
ADDR_GLOBAL = re.compile(r"(?<![A-Za-z0-9_])g_\w*?(?:Va|VA|Rva|RVA|DAT_?)[0-9A-Fa-f]{6,8}\w*")
CLASS_ALLOW = re.compile(r"class-gate:\s*allow\s+(\S+)")
PRESENT = re.compile(r"(\S+)\s+present-unmatched\b")
DB = re.compile(r"^\s*(?:[A-Za-z_$?@][\w$?@]*\s+)?db\s+(.+)$", re.IGNORECASE)


def git(*args, binary=False, check=False):
    got = subprocess.run(["git", *args], cwd=ROOT, capture_output=True)
    if check and got.returncode:
        sys.exit("hatch_counters: git %s failed: %s" % (" ".join(args), got.stderr.decode(errors="replace")))
    return got.stdout if binary else got.stdout.decode("utf-8", "replace")


def relevant(path):
    if PIN_FILE.match(path) or LEDGER_FILE.match(path):
        return True
    return path.startswith(SOURCE_ROOTS) and path.lower().endswith(CODE_EXT + (".asm",))


def _strip_comment(line):
    i = line.find("//")
    return line if i < 0 else line[:i]


def join_linker_literals(line):
    """Apply C++ adjacent-string concatenation on pragma comment(linker) lines."""
    if re.search(r"#\s*pragma\s+comment\s*\(\s*linker\b", line):
        literal = r'"(?:\\.|[^"\\])*"'
        line = re.sub(literal + r'(?:[ \t]*' + literal + r')+',
                      lambda m: '"' + ''.join(s[1:-1] for s in re.findall(literal, m[0])) + '"', line)
    return line


def _db_bytes(arg):
    n = 0
    for item in re.findall(r"'[^']*'|\"[^\"]*\"|[^,]+", arg.split(";", 1)[0]):
        item = item.strip()
        if not item:
            continue
        n += len(item) - 2 if item[0] in "'\"" else 1
    return n


def _addr(cell):
    try:
        return "0x%08X" % int(cell.strip(), 16)
    except ValueError:
        return cell.strip()


OBJECT_SYMBOL = re.compile(r"(?:^|;)\s*object-symbol=([^;]+)")            # build.is_alias_row's


def alias_of(cells):
    """The object-symbol= alias of a functions.csv row when it is a hatch (rule 9), else None."""
    m = OBJECT_SYMBOL.search(cells[6]) if len(cells) >= 7 else None
    if not m:
        return None
    alias, name = m.group(1).strip(), cells[0]
    # Build plumbing (build.is_alias_row, mirrored import-free for the hook; test_hatch_counters
    # pins the two together): a compiler label, the row's own name or an anonymous-namespace
    # respelling of it, and a ?dup_<rva> row, whose minted name nothing calls (zh_sweep,
    # obj_sweep and wave_accounting write those without admit()). build also excuses a name
    # with a Gen_/Rva<RVA> placeholder in it; those are link names this tree calls
    # (BfmeAptValue006DCD20::rva006DCF60), so binding one to another symbol stays a hatch.
    if COMPILER_LABEL.fullmatch(alias) or CLONE_LOCAL.sub("", alias) == CLONE_LOCAL.sub("", name):
        return None
    dup = DUP_PLACEHOLDER.fullmatch(name)
    if dup:
        try:
            if int(dup[1], 16) == int(cells[2], 16):
                return None
        except (ValueError, IndexError):
            pass
    return alias


CLONE_LOCAL = re.compile(r"\?A0x[0-9A-Fa-f]{8}")                       # build.CLONE_LOCAL_RE
DUP_PLACEHOLDER = re.compile(r"^\?dup_([0-9A-Fa-f]{8})@@YAXXZ$")       # build.DUP_ALIAS_ANYCASE_RE


def scan(path, text):
    """Counter of (hatch, path, token) for one file's text."""
    out = collections.Counter()
    if PIN_FILE.match(path) or LEDGER_FILE.match(path):
        pin = bool(PIN_FILE.match(path))
        rows = csv.reader(io.StringIO(text))
        next(rows, None)
        for cells in rows:
            # keyed by address: a rename is not a new hatch (name gates judge names)
            if pin and len(cells) >= 2:
                out[("pin", path, _addr(cells[1]))] += 1
            elif not pin and alias_of(cells) is not None:
                out[("object_symbol", path, _addr(cells[2]))] += 1
        return out
    if path.lower().endswith(".asm"):
        total = 0
        for line in text.splitlines():
            m = DB.match(line.split(";", 1)[0] if "'" not in line else line)
            if m:
                total += _db_bytes(m.group(1))
        if total:
            out[("asm_bytes", path, "*")] = total
        return out
    for line in text.splitlines():
        m = CLASS_ALLOW.search(line)
        if m:
            out[("class_gate_allow", path, m.group(1))] += 1
        for m in PRESENT.finditer(line):
            out[("present_unmatched", path, m.group(1).lstrip("/?") or "?")] += 1
        code = join_linker_literals(_strip_comment(line))
        if "__" in code or "#" in code or "/" in code:
            if SELECTANY.search(code):
                out[("selectany", path, " ".join(code.split())[:160])] += 1
            for m in ALTNAME.finditer(code):
                out[("alternatename", path, m.group(1))] += 1
            for m in PRAGMA_OPT.finditer(code):
                out[("pragma_optimize", path, "".join(m.group(1).split()))] += 1
            n = len(EMIT.findall(code))
            if n:
                out[("emit", path, "*")] += n
        if "g_" in code:
            for m in ADDR_GLOBAL.finditer(code):
                out[("address_global", path, m.group(0))] += 1
    return out


def occurrences(path, text):
    """{key: Counter(detail)}: scan()'s occurrences with what each one is beyond its key (the
    counts add up to scan()'s). A pin is keyed by its address alone, so its detail is the name
    it pins; an object-symbol= row's is its name and alias. Every other hatch's token already
    says what it is. admit() keeps an earlier admission for the details it saw, so a pin renamed
    or added at an admitted address is not one it admitted."""
    if not (PIN_FILE.match(path) or LEDGER_FILE.match(path)):
        return {key: collections.Counter({key[2]: n}) for key, n in scan(path, text).items()}
    pin = bool(PIN_FILE.match(path))
    out = collections.defaultdict(collections.Counter)
    rows = csv.reader(io.StringIO(text))
    next(rows, None)
    for cells in rows:
        if pin and len(cells) >= 2:
            out[("pin", path, _addr(cells[1]))][cells[0].strip()] += 1
        elif not pin and alias_of(cells) is not None:
            out[("object_symbol", path, _addr(cells[2]))]["%s -> %s" % (cells[0].strip(), alias_of(cells))] += 1
    return dict(out)


# ---------------------------------------------------------------- baseline io

def parse(text):
    """{key: count}, {key: allow-blob}. Duplicate keys (a union merge) keep the lowest count."""
    counts, allow = {}, {}
    for line in text.splitlines():
        if not line or line.startswith("#"):
            continue
        cells = line.split("\t")
        if len(cells) < 4 or cells[0] not in HATCHES:
            continue
        key = (cells[0], cells[1], cells[2])
        try:
            n = int(cells[3])
        except ValueError:
            continue
        counts[key] = min(n, counts.get(key, n))
        if len(cells) > 4 and cells[4].startswith("allow="):
            allow[key] = cells[4][6:]
    return counts, allow


MODE = re.compile(r"^# mode: (shadow|enforce)[ \t]*$", re.MULTILINE)
STATE = {"mode": "enforce", "respellable": frozenset(), "ledger_spec": "HEAD:", "ledger_respell": None}
CI_MODE = re.compile(r"^# mode:(.*)$", re.MULTILINE)


def code_identity_enforced(texts):
    """True when every TEXT is a code-identity register whose mode is enforce, read as
    code_identity_gate.read_register reads it (its last `# mode:` line; none is shadow)."""
    return bool(texts) and all(text is not None and [m.strip() for m in CI_MODE.findall(text)][-1:] == ["enforce"]
                               for text in texts)


def set_respellable(specs):
    """Rule 8: the respellable hatches are judged per file only while the code-identity register
    at every git object spec in SPECS is enforced; otherwise per token."""
    texts = read_blobs(["%s%s" % (spec, CODE_IDENTITY) for spec in specs])
    STATE["respellable"] = RESPELLABLE if code_identity_enforced(list(texts.values())) else frozenset()


def _ledger_ident(name):
    """The identifier a data_ledger.csv name spells (`?g_Va0130A588@@3PAV...@@A` -> g_Va0130A588)."""
    name = name.strip()
    if name.startswith("?"):
        return name[1:].split("@", 1)[0]
    return name


def _csv_dicts(text):
    rows = csv.reader(io.StringIO(text or ""))
    head = next(rows, None) or []
    return [dict(zip(head, cells)) for cells in rows if len(cells) == len(head)]


def ledger_respellings():
    """Rule 10: {owner: {alias, ...}} for the address-named globals of the data ledger at
    STATE["ledger_spec"] (HEAD's, so a commit cannot widen its own grant), with a data_rows.csv
    row's name replacing the cached ledger name at its address, as data_check reads the ledger
    (data_ledger.with_verified_owners; mirrored import-free for the hook). A consumer that
    rebinds an alias spelling the ledger records at an address (`extern int g_Va00E09FA4`) to
    that address's owner (`extern T *g_Va0130A588`) adds no global and keeps its file's
    occurrences: an alias occurrence in the same file explains one owner occurrence, and
    never the other way round. Read once per run, only when an address_global key grew."""
    if STATE["ledger_respell"] is None:
        specs = [STATE["ledger_spec"] + DATA_LEDGER, STATE["ledger_spec"] + DATA_ROWS]
        texts = read_blobs(specs)
        at = {}                                    # address -> [owner, {names}]
        for row in _csv_dicts(texts[specs[0]]):
            try:
                address = int(row.get("address", ""), 16)
            except ValueError:
                continue
            names = {n for n in row.get("names", "").split(";") if n.strip()} | {row.get("name", "")}
            at[address] = [row.get("name", ""), names]
        for row in _csv_dicts(texts[specs[1]]):
            try:
                address = int(row.get("address", ""), 16)
            except ValueError:
                continue
            if row.get("address_kind") == "va":
                address -= 0x400000
            entry = at.setdefault(address, ["", set()])
            entry[1].add(row.get("name", ""))
            entry[0] = row.get("name", "")
        out = collections.defaultdict(set)
        for owner_name, names in at.values():
            owner = _ledger_ident(owner_name)
            if not ADDR_GLOBAL.fullmatch(owner):
                continue
            for alias in {_ledger_ident(n) for n in names if n.strip()}:
                if alias != owner and ADDR_GLOBAL.fullmatch(alias):
                    out[owner].add(alias)
        STATE["ledger_respell"] = {k: frozenset(v) for k, v in out.items()}
    return STATE["ledger_respell"]


INHERITED = " [already in HEAD]"   # a finding HEAD's own file and register carry too


def mode_of(text):
    """`# mode: shadow` reports growth without refusing it (the 48 h shadow); the default and
    `# mode: enforce` refuse. Shadow -> enforce is one line; enforce -> shadow is refused."""
    m = MODE.search(text or "")
    return m.group(1) if m else "enforce"


def render(counts, allow=None, mode="enforce"):
    allow = allow or {}
    out = ["# Escape-hatch register, shrink-only. Written by tools/hatch_counters.py; you may lower or",
           "# delete lines by hand (re-verified), never raise or add them. hatch\tpath\ttoken\tcount",
           "# mode: %s" % mode]
    for key in sorted(counts):
        if counts[key] <= 0:
            continue
        line = "%s\t%s\t%s\t%d" % (key + (counts[key],))
        if key in allow:
            line += "\tallow=" + allow[key]
        out.append(line)
    return "\n".join(out) + "\n"


def totals(counts):
    t = collections.Counter()
    for (hatch, _, _), n in counts.items():
        t[hatch] += n
    return t


def by_token(counts):
    t = collections.Counter()
    for (hatch, _, token), n in counts.items():
        t[(hatch, token)] += n
    return t


def unit_of(key):
    """What the gate judges a key as (rule 8): the file for a respellable hatch, else the key."""
    return (key[0], key[1], None) if key[0] in STATE["respellable"] else key


def by_unit(counts):
    t = collections.Counter()
    for key, n in counts.items():
        t[unit_of(key)] += n
    return t


def register_growth(old, new, admitted=()):
    """Keys NEW grants more than OLD that no old occurrence explains. An old occurrence explains
    one new occurrence, at most: its own key, a move (same hatch and token in another file: a
    renamed file, a function moved between units) or a respelling (rule 8: same hatch and file,
    for a respellable hatch). So a move and a respelling cannot both spend one occurrence, and
    every net increase is left over. An ADMITTED key (a valid tool allowance) explains its own
    raise. A maximum matching: each key first keeps what it had, then augmenting paths reassign."""
    def links(key):
        hatch, path, token = key
        out = by_tok.get((hatch, token), [])
        if hatch in STATE["respellable"]:
            return out + by_path.get((hatch, path), [])
        if hatch == "address_global":              # rule 10: an alias rebound to its owner
            aliases = ledger_respellings().get(token, ())
            if aliases:
                return out + [k for k in by_path.get((hatch, path), []) if k[2] in aliases]
        return out
    supply = {k: n for k, n in old.items() if n > 0}
    by_tok, by_path = collections.defaultdict(list), collections.defaultdict(list)
    for k in supply:
        by_tok[(k[0], k[2])].append(k)
        by_path[(k[0], k[1])].append(k)
    flow = collections.defaultdict(int)            # (old key, new key) -> occurrences explained
    fed = collections.defaultdict(list)            # old key -> new keys it explains
    need = {}
    for k, n in new.items():
        want = min(n, old.get(k, 0)) if k in admitted else n
        own = min(want, supply.get(k, 0))
        if own:
            flow[(k, k)] = own
            fed[k].append(k)
            supply[k] -= own
        if want > own:
            need[k] = want - own
    for k in sorted(need):
        while need[k]:
            # backward search: new key -> an old key linked to it -> a new key that old key explains
            prev, queue, found = {k: None}, [k], None
            while queue and found is None:
                j = queue.pop(0)
                for i in links(j):
                    if ("o", i) in prev:
                        continue
                    prev[("o", i)] = j
                    if supply[i]:
                        found = i
                        break
                    for j2 in fed[i]:
                        if j2 not in prev and flow[(i, j2)]:
                            prev[j2] = i
                            queue.append(j2)
            if found is None:
                break
            path, i = [], found                    # [(old, new)]: each old key takes over the new key
            while True:
                j = prev[("o", i)]
                path.append((i, j))
                if prev[j] is None:
                    break
                i = prev[j]                        # j's explainer so far moves on down the path
            delta = min([need[k], supply[found]] + [flow[(prev[j], j)] for _, j in path if prev[j] is not None])
            supply[found] -= delta
            for i, j in path:
                if not flow[(i, j)]:
                    fed[i].append(j)
                flow[(i, j)] += delta
                if prev[j] is not None:
                    flow[(prev[j], j)] -= delta
            need[k] -= delta
    return sorted(k for k, n in need.items() if n)


def read_blobs(specs):
    """{spec: text or None} through one `git cat-file --batch`."""
    if not specs:
        return {}
    data = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                          input=("\n".join(specs) + "\n").encode()).stdout
    out, pos = {}, 0
    for spec in specs:
        nl = data.index(b"\n", pos)
        head = data[pos:nl].split()
        pos = nl + 1
        if len(head) < 3 or head[1] != b"blob":
            out[spec] = None
            continue
        size = int(head[2])
        out[spec] = data[pos:pos + size].decode("utf-8", "replace")
        pos += size + 1
    return out


def index_blob_ids(paths):
    out = {}
    if not paths:
        return out
    for line in git("ls-files", "-s", "--", *paths).splitlines():
        meta, _, path = line.partition("\t")
        out[path] = meta.split()[1]
    return out


def tree_scan(index=False):
    """Occurrences over every tracked relevant file, read from the work tree (or, with
    INDEX, from the staged blobs: what the commit being judged will hold)."""
    counts = collections.Counter()
    paths = [p for p in git("ls-files", "-z").split("\0") if p and relevant(p)]
    if index:
        texts = read_blobs([":" + p for p in paths])
        for path in paths:
            if texts[":" + path] is not None:
                counts.update(scan(path, texts[":" + path]))
        return counts
    for path in paths:
        try:
            text = (ROOT / path).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        counts.update(scan(path, text))
    return counts


# ---------------------------------------------------------------- freeze

def _commit_at_or_before(when, tip="HEAD"):
    return git("rev-list", "-1", "--first-parent", "--before=%d" % when, tip).strip() or None


def reference_totals(now=None):
    """{hatch: total} the freeze compares against: the baseline 24 h ago, or at the latest
    commit since then that lifted the freeze for that hatch. {} when there is no history."""
    now = now or int(os.environ.get("HATCH_NOW") or time.time())
    ref = _commit_at_or_before(now - FREEZE_WINDOW)
    if not ref:
        return {}
    texts = read_blobs(["%s:%s" % (ref, BASELINE)])
    base = texts["%s:%s" % (ref, BASELINE)]
    if base is None:
        return {}
    ref_totals = dict(totals(parse(base)[0]))
    for hatch in HATCHES:
        ref_totals.setdefault(hatch, 0)
    lifts = git("log", "--first-parent", "--format=%H%x00%B%x01", "%s..HEAD" % ref)
    lifted = {}
    for entry in lifts.split("\x01"):           # newest first
        sha, _, body = entry.strip().partition("\x00")
        for m in LIFT.finditer(body):
            for hatch in (HATCHES if m.group(1) == "all" else (m.group(1),)):
                lifted.setdefault(hatch, sha)
    for hatch, sha in lifted.items():
        text = read_blobs(["%s:%s" % (sha, BASELINE)])["%s:%s" % (sha, BASELINE)]
        if text is not None:
            ref_totals[hatch] = totals(parse(text)[0]).get(hatch, 0)
    return ref_totals


def frozen(hatch, new_total, ref_totals):
    old = ref_totals.get(hatch)
    return old is not None and new_total > 2 * old and new_total - old >= FREEZE_MIN


# ---------------------------------------------------------------- the gate

def check_staged():
    """(errors, warnings, hard): `errors` are reported only while the register is in
    `# mode: shadow`; `hard` (inventory edits, a deleted or downgraded register) always fail.
    Enforced, a finding HEAD already carried (rule 6) is a warning, not an error."""
    hard = []
    errors, warnings = _check_staged(hard)
    if STATE["mode"] == "enforce":
        warnings += ["inherited, not refused: " + e for e in errors if e.endswith(INHERITED)]
        errors = [e for e in errors if not e.endswith(INHERITED)]
    return errors, warnings, hard


def _check_staged(hard):
    errors, warnings = [], []
    changed = git("diff", "--cached", "--name-only", "--no-renames", "-z").split("\0")
    inv = [p for p in changed if p.startswith(INVENTORY_DIR)]
    if inv:
        hard += check_inventory(inv)
    touched = [p for p in changed if relevant(p)]
    if not touched and BASELINE not in changed:
        return errors, warnings                     # nothing this gate reads was staged
    staged_base = read_blobs([":" + BASELINE])[":" + BASELINE]
    STATE["mode"] = mode_of(staged_base)
    set_respellable(["HEAD:", ":"])
    parents = ["HEAD"]
    merge_head = git("rev-parse", "-q", "--verify", "MERGE_HEAD").strip()
    if merge_head:
        parents.append(merge_head)
    if BASELINE in changed or merge_head:
        parent_texts = read_blobs(["%s:%s" % (p, BASELINE) for p in parents])
    else:                                           # register untouched: it is its own parent
        parent_texts = {"HEAD": staged_base}
    introduced = all(t is None for t in parent_texts.values())
    if staged_base is None:
        if not introduced:
            hard.append("%s deleted; the register may shrink line by line, never disappear" % BASELINE)
        return errors, warnings                     # register not introduced yet
    # A parent with no mode line is enforced (mode_of's default), so deleting the line and then
    # adding `# mode: shadow` is a downgrade too; and once the parent has a line, it stays.
    parents_present = [t for t in parent_texts.values() if t is not None]
    if STATE["mode"] == "shadow" and any(mode_of(t) == "enforce" for t in parents_present):
        hard.append("%s: '# mode: enforce' may not go back to shadow" % BASELINE)
        STATE["mode"] = "enforce"                   # judged as the parent says
    if not MODE.search(staged_base) and any(MODE.search(t) for t in parents_present):
        hard.append("%s: the '# mode:' line may not be removed (a register with none reads as "
                    "enforce, and its next commit could then claim shadow)" % BASELINE)
        STATE["mode"] = "enforce"
    if BASELINE not in changed and not merge_head:
        # Only the touched files' lines matter: filter before parsing the 40k-line register.
        want = set(touched)
        staged_base = "\n".join(l for l in staged_base.splitlines() if l.split("\t", 2)[1:2] and
                                l.split("\t", 2)[1] in want)
        parent_texts = {"HEAD": staged_base}
    b1, allow1 = parse(staged_base)
    if introduced:
        # The commit that introduces the register must record the tree exactly (one full scan, once).
        if b1 != dict(tree_scan()):
            hard.append("%s does not match the tree; write it with --write-baseline" % BASELINE)
        return errors, warnings
    b0 = {}
    for text in parent_texts.values():
        for key, n in parse(text or "")[0].items():
            b0[key] = max(n, b0.get(key, 0))
    raised = [k for k, n in b1.items() if n > b0.get(k, 0)]
    parent_shadow = all(mode_of(t) == "shadow" for t in parent_texts.values() if t is not None)
    if (parent_shadow and BASELINE in changed and raised and not any(k in allow1 for k in raised)
            and not _adds_occurrences(touched) and b1 == dict(tree_scan(index=True))):
        # A reseed (rule 7): the parent register is in shadow, lines were raised, none by a
        # tool allowance (those stamp allow=, and must not pay for a full scan), and the
        # register is exactly the staged tree, so no file holds more than it grants and there
        # is nothing to report. A staged `# mode: enforce` makes this commit the flip.
        print("hatch_counters: %s reseeded from the staged tree (%s): %s"
              % (BASELINE, "shadow -> ENFORCE" if STATE["mode"] == "enforce" else "shadow",
                 " ".join("%s=%d" % kv for kv in sorted(totals(b1).items()))), file=sys.stderr)
        return errors, warnings
    lowered = sorted({k[1] for k in set(b0) | set(b1) if b1.get(k, 0) < b0.get(k, 0)})
    paths = sorted(set(touched) | set(lowered))
    pathset, touchedset = set(paths), set(touched)
    texts = read_blobs([":" + p for p in paths])
    actual = collections.Counter()
    for p in paths:
        if texts[":" + p] is not None:
            actual.update(scan(p, texts[":" + p]))
    seen = {k for k in actual} | {k for k in b1 if k[1] in pathset}
    # rule 8: a respellable hatch is judged by its file total, any other by its key
    units = collections.defaultdict(list)
    for key in sorted(seen):
        if key[1] in pathset:
            units[unit_of(key)].append(key)
    over = {}
    for unit, keys in sorted(units.items(), key=lambda kv: (kv[0][0], kv[0][1], kv[0][2] or "")):
        a = sum(actual.get(k, 0) for k in keys)
        g = sum(b1.get(k, 0) for k in keys)
        if a > g:
            over[unit] = (a, g, [k for k in keys if actual.get(k, 0) > b1.get(k, 0)])
        elif unit[1] in touchedset:
            if a < g:
                warnings.append("%s: %s in %s is down to %d (register says %d)"
                                % (unit[0], unit[2] or "all tokens", unit[1], a, g))
            respelled = [k[2] for k in keys if actual.get(k, 0) > b1.get(k, 0)]
            if respelled:
                warnings.append("%s in %s respelled (%s), file count unchanged"
                                % (unit[0], unit[1], ", ".join(respelled[:5])))
    if over:
        # A shadow register drifts (rule 7), and so can an enforced one (a commit that skipped
        # the hook, a register line a rebase merged low): HEAD may already carry more than it
        # grants. Tag those [already in HEAD]: shadow lists them apart from what the commit
        # adds, enforcement reports them as inherited and refuses only what the commit adds.
        head_texts = read_blobs(["HEAD:" + p for p in sorted({u[1] for u in over})])
        head_actual = collections.Counter()
        for spec, text in head_texts.items():
            if text is not None:
                head_actual.update(scan(spec[len("HEAD:"):], text))
        head_units, b0_units = by_unit(head_actual), by_unit(b0)
        for unit in sorted(over, key=lambda u: (u[0], u[1], u[2] or "")):
            a, g, keys = over[unit]
            what = unit[2] if unit[2] is not None else ", ".join(k[2] for k in keys) or "?"
            msg = "%s +%d in %s: %s (register grants %d)" % (unit[0], a - g, unit[1], what, g)
            inherited = max(0, head_units.get(unit, 0) - b0_units.get(unit, 0))
            if a - g <= inherited:
                errors.append(msg + INHERITED)
            elif inherited:          # the part HEAD carried is not this commit's; the rest is
                errors.append("%s +%d in %s: %s (register grants %d; HEAD already carried %d more)"
                              % (unit[0], a - g - inherited, unit[1], what, g, inherited))
            else:
                errors.append(msg)
    # credited repair: a hatch whose register total this commit lowers (a move or a respelling
    # lowers one line and raises another, and is no credit)
    t0, t1 = totals(b0), totals(b1)
    for hatch in HATCHES:
        if t1[hatch] < t0[hatch] and not any(u[0] == hatch for u in over):
            warnings.append("credited: %s register total %d -> %d (-%d)"
                            % (hatch, t0[hatch], t1[hatch], t0[hatch] - t1[hatch]))
    # growth of the register itself
    grown = register_growth(b0, b1)
    if grown:
        stamped = [k for k in b1 if b1[k] > b0.get(k, 0) and allow1.get(k)]
        blobs = index_blob_ids(sorted({k[1] for k in stamped}))
        admitted = {k for k in stamped if allow1[k] == blobs.get(k[1])}
        # what is left once every valid allowance explains its own raise; the freeze judges the
        # hatches an allowance was needed for
        need_freeze = {k[0] for k in admitted} & {k[0] for k in grown}
        for key in register_growth(b0, b1, admitted):
            if allow1.get(key):
                errors.append("register line raised by hand, or admitted before %s last changed: %s %s %s "
                              "%d -> %d (its allow= is not the staged blob; `python3 tools/hatch_counters.py "
                              "--restamp %s` re-stamps what tools admitted in this working change)"
                              % (key[1], key[0], key[1], key[2], b0.get(key, 0), b1[key], key[1]))
            else:
                errors.append("register line raised by hand: %s %s %s %d -> %d (only "
                              "`tools/hatch_counters.py --allow` may raise a line)"
                              % (key[0], key[1], key[2], b0.get(key, 0), b1[key]))
        if need_freeze:
            ref = reference_totals()
            t1 = totals(b1)
            for hatch in sorted(need_freeze):
                if frozen(hatch, t1[hatch], ref):
                    errors.append("hatch '%s' is FROZEN: register total %d is more than twice its "
                                  "24 h reference %d; no new allowances until a commit with "
                                  "'Verifier-Change: hatch-freeze-lift %s <reason>' lands"
                                  % (hatch, t1[hatch], ref[hatch], hatch))
    return errors, warnings


def _adds_occurrences(paths):
    """True when a staged PATH carries more of some hatch unit than HEAD's PATH: a reseed
    records the tree as it stands, so the commit carrying it may not add to that tree."""
    if not paths:
        return False
    texts = read_blobs([":" + p for p in paths] + ["HEAD:" + p for p in paths])
    staged, head = collections.Counter(), collections.Counter()
    for p in paths:
        if texts[":" + p] is not None:
            staged.update(scan(p, texts[":" + p]))
        if texts["HEAD:" + p] is not None:
            head.update(scan(p, texts["HEAD:" + p]))
    head_units = by_unit(head)
    return any(n > head_units.get(u, 0) for u, n in by_unit(staged).items())


def check_inventory(paths):
    sys.path.insert(0, str(ROOT / "tools"))
    try:
        import retail_inventory
    except ImportError as exc:
        return ["retail inventory changed but tools/retail_inventory.py is unavailable: %s" % exc]
    return retail_inventory.verify_staged(paths)


# ---------------------------------------------------------------- writers

def write(counts, allow=None, mode="enforce"):
    (ROOT / BASELINE).parent.mkdir(parents=True, exist_ok=True)
    (ROOT / BASELINE).write_text(render(counts, allow, mode), encoding="utf-8", newline="\n")


def update(allow_paths=(), reason=None):
    old_text = (ROOT / BASELINE).read_text(encoding="utf-8") if (ROOT / BASELINE).exists() else None
    if old_text is None:
        sys.exit("hatch_counters: no register yet; --write-baseline creates the first one")
    old, _ = parse(old_text)
    new = tree_scan()
    set_respellable(["HEAD:"])
    allow_paths = {p.replace("\\", "/") for p in allow_paths}
    grown = register_growth(old, new)
    refused = [k for k in grown if k[1] not in allow_paths]
    if refused:
        for k in refused[:40]:
            print("  %s +%d in %s: %s" % (k[0], new[k] - old.get(k, 0), k[1], k[2]), file=sys.stderr)
        sys.exit("hatch_counters: %d occurrence key(s) grew; remove them, or admit them with "
                 "--allow PATH --reason TEXT" % len(refused))
    allow = {}
    if grown:
        if not reason or len(reason.strip()) < 8:
            sys.exit("hatch_counters: --allow needs --reason (8+ chars)")
        ref = reference_totals()
        t_new = totals(new)
        for hatch in sorted({k[0] for k in grown}):
            if frozen(hatch, t_new[hatch], ref):
                sys.exit("hatch_counters: hatch '%s' is frozen (total %d vs 24 h reference %d)"
                         % (hatch, t_new[hatch], ref[hatch]))
        ids = {}
        for p in sorted({k[1] for k in grown}):
            ids[p] = git("hash-object", "--", p).strip()
        for k in grown:
            allow[k] = ids[k[1]]
            print("allowed: %s +%d in %s: %s -- %s" % (k[0], new[k] - old.get(k, 0), k[1], k[2], reason))
    write(new, allow, mode_of(old_text))
    t0, t1 = totals(old), totals(new)
    for hatch in HATCHES:
        if t0[hatch] != t1[hatch]:
            print("%-18s %7d -> %7d" % (hatch, t0[hatch], t1[hatch]))


def reseed(mode=None):
    """Rule 7: rewrite a shadow register from the staged tree, in MODE (None: keep shadow;
    'enforce': the flip). Refused when the register, or HEAD's, is enforced or absent, and
    when a tracked file this register reads differs from the index (the gate compares the
    register with the staged tree, so that is the tree it is written from)."""
    old_text = (ROOT / BASELINE).read_text(encoding="utf-8") if (ROOT / BASELINE).exists() else None
    if old_text is None:
        sys.exit("hatch_counters: no register yet; --write-baseline creates the first one")
    head_text = read_blobs(["HEAD:" + BASELINE])["HEAD:" + BASELINE]
    if mode_of(old_text) != "shadow" or (head_text is not None and mode_of(head_text) != "shadow"):
        sys.exit("hatch_counters: %s is enforced; an enforced register only shrinks (--update) "
                 "or grows by --admit/--allow, it is never reseeded" % BASELINE)
    unstaged = [p for p in git("diff", "--name-only", "-z").split("\0") if p and relevant(p)]
    if unstaged:
        sys.exit("hatch_counters: --reseed writes the register from the index, and %d file(s) it reads "
                 "differ from it (%s%s): stage or revert them first"
                 % (len(unstaged), ", ".join(unstaged[:5]), ", ..." if len(unstaged) > 5 else ""))
    old, _ = parse(old_text)
    new = tree_scan(index=True)
    mode = mode or "shadow"
    write(new, mode=mode)
    raised = sum(1 for k in new if new[k] > old.get(k, 0))
    lowered = sum(1 for k in old if new.get(k, 0) < old[k])
    t0, t1 = totals(old), totals(new)
    for hatch in HATCHES:
        print("%-18s %7d -> %7d" % (hatch, t0[hatch], t1[hatch]))
    print("reseeded %s (mode %s): %d line(s) raised or added, %d lowered or removed; commit it, "
          "alone, with 'Verifier-Change: hatch-reseed <why>'" % (BASELINE, mode, raised, lowered))


def blob_id(path, data):
    """The blob id DATA (bytes) would be staged as at PATH: git applies the path's
    eol/autocrlf filters, so the id agrees with `git add` on any checkout."""
    return subprocess.run(["git", "hash-object", "--stdin", "--path=" + path], cwd=ROOT,
                          input=data, capture_output=True).stdout.decode().strip()


def _key_of(line):
    cells = line.split("\t")
    return (cells[0], cells[1], cells[2]) if len(cells) >= 4 and cells[0] in HATCHES else None


def _head_grants(path):
    """{key: count} HEAD's register grants PATH (the lowest of a duplicated line)."""
    head = {}
    for line in (read_blobs(["HEAD:" + BASELINE])["HEAD:" + BASELINE] or "").splitlines():
        key = _key_of(line)
        if key and key[1] == path:
            try:
                n = int(line.split("\t")[3])
            except ValueError:
                continue
            head[key] = min(n, head.get(key, n))
    return head


def _path_lines(text, path):
    """{key: (count, allow-stamp or None)}: PATH's lines in register TEXT, the lowest count of a
    duplicated line (as parse() reads it)."""
    out = {}
    for line in (text or "").splitlines():
        key = _key_of(line)
        if key is None or key[1] != path:
            continue
        cells = line.split("\t")
        try:
            n = int(cells[3])
        except ValueError:
            continue
        stamp = cells[4][6:] if len(cells) > 4 and cells[4].startswith("allow=") else None
        if key not in out or n < out[key][0]:
            out[key] = (n, stamp)
    return out


# ---------------------------------------------------------------- tool admissions of a working change
#
# The gate trusts a raised line only while its allow= names the staged file's blob, so any edit of
# the file after a tool admitted a hatch makes that grant stale, and an allow= stamp alone cannot say
# who wrote the line: a stamp copied from a neighbouring line, or a forged one, looks the same. So
# admit() records what it granted -- per raised key, the occurrences the file carried (a pin's name,
# not just its address) and the allow= stamps it wrote for the key -- in the worktree's git dir,
# scoped to HEAD (a commit or a checkout starts a new working change). An earlier grant is kept only
# from that record: a raised line whose allow= is a stamp the tools wrote for that key, for the
# occurrences that admission saw which the file still carries.

ADMISSIONS = "hatch-admissions.json"


def _head():
    return git("rev-parse", "-q", "--verify", "HEAD").strip()


def _record_file():
    rel = git("rev-parse", "--git-path", ADMISSIONS).strip()
    return ROOT / rel if rel else None


def _no_record():
    return {"stamps": [], "keys": {}}


def _read_record(head):
    """{path: {"stamps": [blob, ...], "keys": {key: {"details": Counter, "first": i, "last": j}}}}:
    the admissions recorded on HEAD (stamps[first..last] are the allow= stamps written for the key);
    {} when there are none, they were made on another HEAD, or the record does not parse."""
    try:
        data = json.loads(_record_file().read_text(encoding="utf-8"))
        if data["head"] != head:
            return {}
        out = {}
        for path, rec in data["paths"].items():
            keys = {}
            for name, entry in rec["keys"].items():
                hatch, token = name.split("\t", 1)
                keys[(hatch, path, token)] = {
                    "details": collections.Counter({str(d): int(n) for d, n in entry["details"].items()}),
                    "first": int(entry["first"]), "last": int(entry["last"])}
            out[path] = {"stamps": [str(s) for s in rec["stamps"]], "keys": keys}
        return out
    except (AttributeError, KeyError, OSError, TypeError, ValueError):
        return {}


def _write_record(head, record):
    target = _record_file()
    if target is None:
        return
    paths = {}
    for path, rec in sorted(record.items()):
        if not rec["keys"]:
            continue
        first = min(entry["first"] for entry in rec["keys"].values())    # drop stamps no key can name
        paths[path] = {"stamps": rec["stamps"][first:],
                       "keys": {"%s\t%s" % (key[0], key[2]): {"details": dict(sorted(entry["details"].items())),
                                                              "first": entry["first"] - first,
                                                              "last": entry["last"] - first}
                                for key, entry in sorted(rec["keys"].items())}}
    scratch = target.with_name(target.name + ".tmp")
    try:
        scratch.write_text(json.dumps({"head": head, "paths": paths}, indent=1, sort_keys=True) + "\n",
                           encoding="utf-8")
        os.replace(scratch, target)
    except OSError as exc:
        print("hatch_counters: WARNING: admissions not recorded in %s (%s): an edit of the file "
              "before the next admit() will cost them" % (target, exc), file=sys.stderr)


def _earlier_grant(entry, stamps, carried, head_count, line, details):
    """What a register LINE (count, stamp) of a key PATH carries CARRIED times (DETAILS) still
    grants from ENTRY, the key's recorded admission (None: there is none): the occurrences that
    admission saw which the file still carries, capped at the line and the file -- but only when
    the line stands above HEAD's count and its stamp is one the tools wrote for this key. Otherwise
    HEAD_COUNT, all that HEAD's register grants."""
    count, stamp = line
    if entry is None or count <= head_count or stamp not in stamps[entry["first"]:entry["last"] + 1]:
        return head_count
    return max(head_count, min(carried, count, sum((details & entry["details"]).values())))


def _say(lines, what, limit):
    for line in lines[:limit]:
        print(line, file=sys.stderr)
    if len(lines) > limit:
        print("hatch_counters: ... and %d more %s" % (len(lines) - limit, what), file=sys.stderr)


def admit(path, reason, tokens=None, before=None, now=None):
    """Scoped tool allowance for one file: {"admitted": [keys], "kept": [keys], "refused": [keys]}.

    Rescans only PATH and rewrites only PATH's register lines (no tree scan; the
    register is filtered as text). Each of PATH's lines is recomputed from what PATH
    carries now, against HEAD's register:

      - a key PATH carries no more often than HEAD grants is written at PATH's count;
      - a grown key whose token is in TOKENS (None: every grown key) is admitted at
        PATH's count, and the admission is recorded (ADMISSIONS above) ("admitted");
      - a grown key whose raised line the gate grants as it stands -- its allow= names
        PATH's blob now, or BEFORE, the blob PATH had just before the calling tool's
        edit -- keeps that line, capped at PATH's count ("kept");
      - a grown key whose raised line a recorded admission of this working change wrote
        (its allow= is one of the stamps the tools wrote for that key) keeps the
        occurrences that admission saw which PATH still carries, capped at the line
        ("kept");
      - anything else is written at HEAD's count, as is what a kept key carries past its
        grant ("refused"), so the gate names it.

    Every raised line is stamped allow=<blob of PATH as it is now>. So admissions
    accumulate across tool calls in one working change whatever else edits PATH in
    between (re-stamping only allowances that named BEFORE reset every earlier admission
    after any other edit: 319 pin lines at 171 addresses across four commits, each
    reported admitted); no grant exceeds what PATH carries; and a register line typed by
    hand -- whatever its stamp, copied or forged -- or a pin renamed or added at an
    admitted address is still refused. Kept lines, and raised lines lowered, are reported
    on stderr. A frozen hatch exits."""
    path = path.replace("\\", "/")
    if not reason or len(reason.strip()) < 8:
        sys.exit("hatch_counters: admit needs a reason (8+ chars)")
    base = ROOT / BASELINE
    if not base.exists():
        return {"admitted": [], "kept": [], "refused": []}  # no register yet: nothing to admit into
    data = (ROOT / path).read_bytes() if (ROOT / path).exists() else b""
    blob = blob_id(path, data)
    found = occurrences(path, data.decode("utf-8", "replace"))
    head = _head_grants(path)
    text = base.read_text(encoding="utf-8")
    old = _path_lines(text, path)
    head_sha = _head()
    record = _read_record(head_sha)
    rec = record.get(path, _no_record())
    index = len(rec["stamps"])                      # this call's stamp, once appended
    header, keep, recorded = [], [], {}
    for line in text.splitlines():
        key = _key_of(line)
        if key is None:
            header.append(line)
        elif key[1] != path:
            keep.append((key, line))
    tokens = None if tokens is None else {str(t) for t in tokens}
    accept = {blob, before} - {None}
    admitted, kept, refused, said, lowered = [], [], [], [], []
    for key in sorted(found):
        details = found[key]
        n, h = sum(details.values()), head.get(key, 0)
        entry = rec["keys"].get(key)
        if n <= h:
            keep.append((key, "%s\t%s\t%s\t%d" % (key + (n,))))
            continue
        if tokens is None or key[2] in tokens:
            admitted.append(key)
            keep.append((key, "%s\t%s\t%s\t%d\tallow=%s" % (key + (n, blob))))
            recorded[key] = {"details": details, "first": entry["first"] if entry else index, "last": index}
            continue
        line = old.get(key, (0, None))
        if line[0] > h and line[1] in accept:
            grant = min(n, line[0])                 # the gate grants it as it stands
        else:
            grant = _earlier_grant(entry, rec["stamps"], n, h, line, details)
        if grant > h:
            kept.append(key)
            keep.append((key, "%s\t%s\t%s\t%d\tallow=%s" % (key + (grant, blob))))
            if entry:
                recorded[key] = dict(entry, last=index)
            said.append("hatch_counters: kept %s in %s: %s at %d (admitted earlier in this working "
                        "change; re-stamped)" % (key + (grant,)))
        elif h:
            keep.append((key, "%s\t%s\t%s\t%d" % (key + (h,))))
        if grant < n:
            refused.append(key)
        if max(grant, h) < min(line[0], n):         # a raised line lowered below what the file carries
            lowered.append("hatch_counters: NOT KEPT %s in %s: %s: register line %d -> %d (the file carries "
                           "%d; no tool admission of this working change grants more)"
                           % (key + (line[0], max(grant, h), n)))
    if admitted or kept:
        ref = reference_totals(now)
        for hatch in sorted({k[0] for k in admitted + kept}):
            total = sum(int(line.split("\t")[3]) for k, line in keep if k[0] == hatch)
            if frozen(hatch, total, ref):
                sys.exit("hatch_counters: hatch '%s' is frozen (total %d vs 24 h reference %d)"
                         % (hatch, total, ref[hatch]))
    keep.sort(key=lambda item: item[0])
    base.write_text("\n".join(header + [line for _, line in keep]) + "\n", encoding="utf-8", newline="\n")
    record[path] = {"stamps": rec["stamps"] + [blob], "keys": recorded}
    _write_record(head_sha, record)
    for key in admitted:
        print("hatch_counters: admitted %s in %s: %s -- %s" % (key + (reason,)), file=sys.stderr)
    _say(lowered, "register line(s) lowered", 20)
    _say(said, "earlier admission(s) kept", 10)
    return {"admitted": admitted, "kept": kept, "refused": refused}


def ungranted(path, data=None, register=None, earlier=False):
    """{key: (carried, granted)} for each key PATH carries more often than the register
    grants it, judged as the commit gate judges a staged PATH and register against HEAD: a
    line above HEAD's count grants only while its allow= names PATH's blob. DATA (bytes)
    defaults to PATH on disk and REGISTER (text) to the working register; {} when there is
    no register. Independent of admit(): tools call it after admit() to prove the register
    really grants what they wrote. EARLIER also grants what the next admit() keeps from a
    recorded admission of this working change whose stamp an edit since made stale: what a
    tool compares against before its own edit."""
    path = path.replace("\\", "/")
    if register is None:
        base = ROOT / BASELINE
        if not base.exists():
            return {}
        register = base.read_text(encoding="utf-8")
    if data is None:
        data = (ROOT / path).read_bytes() if (ROOT / path).exists() else b""
    blob = blob_id(path, data)
    head = _head_grants(path)
    lines = _path_lines(register, path)
    rec = _read_record(_head()).get(path, _no_record()) if earlier else _no_record()
    out = {}
    for key, details in occurrences(path, data.decode("utf-8", "replace")).items():
        n, h = sum(details.values()), head.get(key, 0)
        line = lines.get(key, (0, None))
        granted = line[0]
        if granted > h and line[1] != blob:         # stale, typed or forged: the gate refuses it
            granted = _earlier_grant(rec["keys"].get(key), rec["stamps"], n, h, line, details)
        if n > granted:
            out[key] = (n, granted)
    return out


INHERITED_SHOWN = 10    # shadow findings HEAD already carries, listed before a count
NOTE_SHOWN = 20         # findings the hook's closing repeat lists
ADDED = re.compile(r"^(\w+) \+(\d+) in ")


def shadow_banner(findings, limit=None):
    """The shadow-mode report for findings this commit adds. Shadow does not refuse them,
    so a one-line note scrolled past under the build output: 319 pin lines at 171
    addresses went in unadmitted across four commits that way. This one is framed and
    counted."""
    per_hatch, other = collections.Counter(), 0
    for finding in findings:
        m = ADDED.match(finding)
        if m:
            per_hatch[m.group(1)] += int(m.group(2))
        else:
            other += 1                              # a register line raised by hand, a freeze
    parts = ["%s +%d" % kv for kv in sorted(per_hatch.items())]
    if other:
        parts.append("%d register finding(s)" % other)
    rule = "!" * 78
    out = [rule,
           "hatch_counters: THIS COMMIT ADDS UNADMITTED ESCAPE HATCHES (%s)" % ", ".join(parts),
           "  The register is in shadow mode, so the commit is NOT refused; enforcement refuses",
           "  every line below. Nothing admitted them: remove them, or admit a checked one",
           "  through its tool (pins: `tools/pin_admission.py --add`; otherwise",
           "  `tools/hatch_counters.py --allow PATH --reason TEXT`).",
           ""]
    shown = findings if limit is None else findings[:limit]
    out += ["  SHADOW (not enforced): " + f for f in shown]
    if len(findings) > len(shown):
        out.append("  ... and %d more (the hatch step above lists all)" % (len(findings) - len(shown)))
    out.append(rule)
    return "\n".join(out) + "\n"


ADMIT = ("`python3 tools/hatch_counters.py --admit PATH --tokens TOKEN --reason \"<why>\"`, staged with "
         "the register, and a `Verifier-Change: hatch-admit <why>` trailer")
REMEDY = {
    "pin": "never type a pin: `python3 tools/pin_admission.py --add NAME 0xRVA` (or `tools/add_match.py "
           "... --pin NAME=0xRVA`) checks it and admits it.",
    "object_symbol": "an object-symbol= alias row binds a real name to another symbol's bytes and is refused "
                     "(pin_admission). Name the row after the symbol it compiles, or row the owner.",
    "alternatename": "a vftable or global literal: `python3 tools/name_globals.py PATH` writes and admits it. "
                     "Any other alias must be exactly what `python3 tools/allowed_symbols.py --alternatenames` "
                     "emits (code_identity_gate refuses any other); admit that one with " + ADMIT + ".",
    "address_global": "use the global reverse/data_ledger.csv names for that address (`python3 "
                      "tools/name_globals.py PATH` rewrites literals); an address-named global is not admitted.",
    "present_unmatched": "row the body (`tools/add_match.py`); a marker is honest only for a known, unpinned "
                         "body, and is then admitted with " + ADMIT + ".",
    "class_gate_allow": "include the class's canonical header (reverse/canonical_classes.csv) instead of a "
                        "private view; a waiver is a class-reconciliation decision, not an edit.",
    "pragma_optimize": "only for a proven codegen blocker (docs/recipes.md): " + ADMIT + ".",
    "emit": "__emit is a lift, not a conversion (conversion_gate): write the body as C++.",
    "asm_bytes": "raw db bytes are a lift: write the body as C++ or MASM instructions.",
    "selectany": "a selectany definition hides a duplicate: define the datum once, in its owner; else " + ADMIT + ".",
}


def enforce_report(errors, elapsed):
    """The refusal: what this commit adds, then what to do about each hatch it names."""
    hatches = sorted(h for h in REMEDY if any(re.search(r"(?<!\w)%s(?!\w)" % h, e) for e in errors))
    rule = "=" * 78
    out = [rule, "hatch_counters: REFUSED (%.2fs): escape hatches grew -- this commit adds what the "
                 "register (%s, enforced) does not grant:" % (elapsed, BASELINE)]
    out += ["  " + e for e in errors]
    out += ["", "What to do. Removing an occurrence is always allowed (and credited once "
                "`python3 tools/hatch_counters.py --update` lowers the register). To keep one:"]
    out += ["  %s: %s" % (h, REMEDY[h]) for h in hatches]
    if any("raised by hand:" in e for e in errors):
        out.append("  register lines: never edit reverse/hatch_baseline.tsv up by hand; restore it "
                   "(`git checkout HEAD -- %s`) and let the tools above write it." % BASELINE)
    out.append("  Not yours? An excess HEAD already carried is reported as inherited and never refused; "
               "if the gate refuses correct work, record it: `python3 tools/re_log.py record <symbol> "
               "<rva> <size> blocked \"false-reject hatch_counters: <evidence> t=<min> model=<model>\"`.")
    out.append(rule)
    return "\n".join(out) + "\n"


def report():
    head =read_blobs(["HEAD:" + BASELINE])["HEAD:" + BASELINE]
    b = totals(parse(head or "")[0])
    t = totals(tree_scan())
    print("%-18s %10s %10s" % ("hatch", "register", "tree"))
    for hatch in HATCHES:
        print("%-18s %10d %10d" % (hatch, b[hatch], t[hatch]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--report", action="store_true")
    g.add_argument("--update", action="store_true")
    g.add_argument("--allow", nargs="+", metavar="PATH")
    g.add_argument("--write-baseline", action="store_true")
    g.add_argument("--admit", metavar="PATH")
    g.add_argument("--reseed", action="store_true", help="rewrite a shadow register from the tree")
    g.add_argument("--restamp", metavar="PATH",
                   help="re-stamp PATH's lines that tools admitted earlier in this working change, after "
                        "an edit made their allow= stale; admits nothing new")
    ap.add_argument("--reason")
    ap.add_argument("--tokens", nargs="+", help="--admit only: admit just these tokens")
    ap.add_argument("--note-file", metavar="PATH",
                    help="--staged only: also write the shadow-mode banner to PATH (the pre-commit "
                         "hook repeats it as its last output); left untouched when there is none")
    ap.add_argument("--mode", choices=("shadow", "enforce"),
                    help="--write-baseline: the first register's mode (default enforce); --reseed: "
                         "the reseeded register's (default: keep shadow; enforce is the flip)")
    args = ap.parse_args(argv)
    if args.note_file and not args.staged:
        ap.error("--note-file goes with --staged")
    if args.mode and not (args.write_baseline or args.reseed):
        ap.error("--mode goes with --write-baseline or --reseed")
    if args.staged:
        t = time.time()
        errors, warnings, hard = check_staged()
        if errors and STATE["mode"] == "shadow":
            inherited = [e for e in errors if e.endswith(INHERITED)]
            for e in inherited[:INHERITED_SHOWN]:
                print("hatch_counters: SHADOW (not enforced): " + e, file=sys.stderr)
            if len(inherited) > INHERITED_SHOWN:
                print("hatch_counters: SHADOW (not enforced): ... and %d more finding(s) HEAD already "
                      "carries" % (len(inherited) - INHERITED_SHOWN), file=sys.stderr)
            added = [e for e in errors if not e.endswith(INHERITED)]
            if added:
                banner = shadow_banner(added)
                print(banner, end="", file=sys.stderr)
                if args.note_file:
                    Path(args.note_file).write_text(shadow_banner(added, limit=NOTE_SHOWN), encoding="utf-8")
            errors = []
        for w in warnings[:20]:
            tail = " -- `tools/hatch_counters.py --update` tightens it" if " is down to " in w else ""
            print("hatch_counters: note: " + w + tail, file=sys.stderr)
        if len(warnings) > 20:
            print("hatch_counters: note: ... and %d more" % (len(warnings) - 20), file=sys.stderr)
        if errors:                                  # enforced: what this commit adds
            print(enforce_report(errors, time.time() - t), end="", file=sys.stderr)
        for e in hard:
            print("  " + e, file=sys.stderr)
        if errors or hard:
            if hard and not errors:
                print("hatch_counters: refused (%.2fs): see above." % (time.time() - t), file=sys.stderr)
            return 1
        return 0
    if args.report:
        report()
        return 0
    if args.write_baseline:
        if (ROOT / BASELINE).exists():
            sys.exit("hatch_counters: %s exists; use --update (shrink/move) or --allow" % BASELINE)
        write(tree_scan(), mode=args.mode or "enforce")
        return 0
    if args.reseed:
        reseed(args.mode)
        return 0
    if args.restamp:
        got = admit(args.restamp, "restamp: tool admissions of this working change", tokens=())
        for key in got["refused"]:
            print("hatch_counters: NOT re-stamped (no tool admitted it in this working change): "
                  "%s in %s: %s" % key, file=sys.stderr)
        return 1 if got["refused"] else 0
    if args.admit:
        got = admit(args.admit, args.reason, args.tokens)
        for key in got["refused"]:
            print("hatch_counters: NOT admitted (token not in --tokens, no earlier admission of this "
                  "working change covers it): %s in %s: %s" % key, file=sys.stderr)
        return 1 if got["refused"] else 0
    update(args.allow or (), args.reason)
    return 0


if __name__ == "__main__":
    sys.exit(main())
