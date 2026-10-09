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
     the default) refuses; enforce may never go back to shadow. Rule 5, a
     deleted register and a wrong first register are refused in both modes.
     In shadow, findings the commit adds get a framed, counted banner (and
     --note-file, which the pre-commit hook repeats last); findings HEAD
     already carries are tagged [already in HEAD] and listed briefly.
  7. Reseed, shadow only. A register left in shadow drifts: commits it never
     refused grew the tree past it, so every touched file reports growth that
     commit did not make. `--reseed` rewrites the whole register from the tree
     (no allow= stamps, mode kept) and is refused once the register says
     `# mode: enforce`: an enforced register is never re-derived from the
     tree it judges. The gate takes a staged register that raises lines as a
     reseed only when it equals the staged tree exactly (one full scan, as for
     the first register); anything short of that is judged line by line as
     before. The commit carries `Verifier-Change: hatch-reseed <why>`
     (tools/protected_paths.py asks for a trailer on any baseline edit).

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
  python3 tools/hatch_counters.py --write-baseline      first baseline only (refuses if one exists)
  python3 tools/hatch_counters.py --reseed              rewrite a SHADOW register from the tree (rule 7)
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
else:                                                       # Open-BFME-2
    BASELINE = "reverse/hatch_baseline.tsv"
    SOURCE_ROOTS = ("Code/", "reference/shims/")
    PIN_FILE = re.compile(r"^reverse/symbols\.csv$")
    LEDGER_FILE = re.compile(r"^reverse/functions\.csv$")
    INVENTORY_DIR = "reverse/retail_inventory/"

CODE_EXT = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".inl")
FREEZE_WINDOW = 24 * 3600
FREEZE_MIN = 5
LIFT = re.compile(r"^Verifier-Change:[ \t]*hatch-freeze-lift[ \t]+(\S+)", re.MULTILINE)

HATCHES = ("selectany", "alternatename", "pin", "object_symbol", "address_global",
           "class_gate_allow", "present_unmatched", "pragma_optimize", "emit", "asm_bytes")

SELECTANY = re.compile(r"__declspec\s*\(\s*selectany\s*\)")
ALTNAME = re.compile(r"/alternatename:([^=\s\"]+)=([^\s\"]+)", re.IGNORECASE)
PRAGMA_OPT = re.compile(r"^\s*#\s*pragma\s+optimize\s*\(([^)]*)\)")
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
            elif not pin and len(cells) >= 7 and "object-symbol=" in cells[6]:
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
        code = _strip_comment(line)
        if "__" in code or "#" in code or "/" in code:
            if SELECTANY.search(code):
                out[("selectany", path, " ".join(code.split())[:160])] += 1
            for m in ALTNAME.finditer(code):
                out[("alternatename", path, m.group(1))] += 1
            m = PRAGMA_OPT.match(code)
            if m:
                out[("pragma_optimize", path, "".join(m.group(1).split()))] += 1
            n = len(EMIT.findall(code))
            if n:
                out[("emit", path, "*")] += n
        if "g_" in code:
            for m in ADDR_GLOBAL.finditer(code):
                out[("address_global", path, m.group(0))] += 1
    return out


OBJECT_SYMBOL = re.compile(r"object-symbol=([^;\s]*)")


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
        elif not pin and len(cells) >= 7 and "object-symbol=" in cells[6]:
            alias = OBJECT_SYMBOL.search(cells[6]).group(1)
            out[("object_symbol", path, _addr(cells[2]))]["%s -> %s" % (cells[0].strip(), alias)] += 1
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
STATE = {"mode": "enforce"}
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
    `# mode: shadow`; `hard` (inventory edits, a deleted or downgraded register) always fail."""
    hard = []
    errors, warnings = _check_staged(hard)
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
    if STATE["mode"] == "shadow" and any(MODE.search(t or "") and mode_of(t) == "enforce" for t in parent_texts.values()):
        hard.append("%s: '# mode: enforce' may not go back to shadow" % BASELINE)
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
    if (STATE["mode"] == "shadow" and BASELINE in changed and raised and not any(k in allow1 for k in raised)
            and b1 == dict(tree_scan(index=True))):
        # A shadow reseed (rule 7): lines were raised, none by a tool allowance (those stamp
        # allow=, and must not pay for a full scan), and the register is exactly the staged
        # tree, so no file holds more than it grants and there is nothing to report.
        print("hatch_counters: %s reseeded from the staged tree (shadow): %s"
              % (BASELINE, " ".join("%s=%d" % kv for kv in sorted(totals(b1).items()))), file=sys.stderr)
        return errors, warnings
    lowered =sorted({k[1] for k in set(b0) | set(b1) if b1.get(k, 0) < b0.get(k, 0)})
    paths = sorted(set(touched) | set(lowered))
    texts = read_blobs([":" + p for p in paths])
    actual = collections.Counter()
    for p in paths:
        if texts[":" + p] is not None:
            actual.update(scan(p, texts[":" + p]))
    seen = {k for k in actual} | {k for k in b1 if k[1] in set(paths)}
    over = {}
    for key in sorted(seen):
        if key[1] not in set(paths):
            continue
        a, g = actual.get(key, 0), b1.get(key, 0)
        if a > g:
            over[key] = (a, g)
        elif a < g and key[1] in set(touched):
            warnings.append("%s: %s in %s is down to %d (register says %d)" % (key[0], key[2], key[1], a, g))
    if over:
        # A shadow register drifts (rule 7): HEAD may already carry more than it grants, and
        # every commit touching that file reports it again. Tag those so the occurrences
        # this commit adds stand out (main()); enforcement judges both alike.
        head_texts = read_blobs(["HEAD:" + p for p in sorted({k[1] for k in over})])
        head_actual = collections.Counter()
        for spec, text in head_texts.items():
            if text is not None:
                head_actual.update(scan(spec[len("HEAD:"):], text))
        for key in sorted(over):
            a, g = over[key]
            msg = "%s +%d in %s: %s (register grants %d)" % (key[0], a - g, key[1], key[2], g)
            if a - g <= max(0, head_actual.get(key, 0) - b0.get(key, 0)):
                msg += INHERITED
            errors.append(msg)
    # growth of the register itself
    tok0, tok1 = by_token(b0), by_token(b1)
    grown = sorted(k for k in b1 if b1[k] > b0.get(k, 0) and tok1[(k[0], k[2])] > tok0.get((k[0], k[2]), 0))
    if grown:
        blobs = index_blob_ids(sorted({k[1] for k in grown}))
        need_freeze = set()
        for key in grown:
            if allow1.get(key) and allow1[key] == blobs.get(key[1]):
                need_freeze.add(key[0])
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
    allow_paths = {p.replace("\\", "/") for p in allow_paths}
    tok_old, tok_new = by_token(old), by_token(new)
    grown = sorted(k for k in new if new[k] > old.get(k, 0) and tok_new[(k[0], k[2])] > tok_old.get((k[0], k[2]), 0))
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


def reseed():
    """Rule 7: rewrite a shadow register from the tree. Refused when enforced or absent."""
    old_text = (ROOT / BASELINE).read_text(encoding="utf-8") if (ROOT / BASELINE).exists() else None
    if old_text is None:
        sys.exit("hatch_counters: no register yet; --write-baseline creates the first one")
    if mode_of(old_text) != "shadow":
        sys.exit("hatch_counters: %s is enforced; an enforced register only shrinks (--update) "
                 "or grows by --allow, it is never reseeded" % BASELINE)
    old, _ = parse(old_text)
    new = tree_scan()
    write(new, mode="shadow")
    raised = sum(1 for k in new if new[k] > old.get(k, 0))
    lowered = sum(1 for k in old if new.get(k, 0) < old[k])
    t0, t1 = totals(old), totals(new)
    for hatch in HATCHES:
        print("%-18s %7d -> %7d" % (hatch, t0[hatch], t1[hatch]))
    print("reseeded %s: %d line(s) raised or added, %d lowered or removed; commit it with "
          "'Verifier-Change: hatch-reseed <why>'" % (BASELINE, raised, lowered))


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
    ap.add_argument("--reason")
    ap.add_argument("--tokens", nargs="+", help="--admit only: admit just these tokens")
    ap.add_argument("--note-file", metavar="PATH",
                    help="--staged only: also write the shadow-mode banner to PATH (the pre-commit "
                         "hook repeats it as its last output); left untouched when there is none")
    ap.add_argument("--mode", choices=("shadow", "enforce"), default="enforce",
                    help="--write-baseline only: start in shadow (report, never refuse)")
    args = ap.parse_args(argv)
    if args.note_file and not args.staged:
        ap.error("--note-file goes with --staged")
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
        errors += hard
        for w in warnings[:20]:
            print("hatch_counters: note: " + w + " -- `tools/hatch_counters.py --update` tightens it",
                  file=sys.stderr)
        for e in errors:
            print("  " + e, file=sys.stderr)
        if errors:
            print("hatch_counters: escape hatches grew (%.2fs). Remove the new occurrence(s); a real "
                  "need is admitted only by `python3 tools/hatch_counters.py --allow PATH --reason TEXT`."
                  % (time.time() - t), file=sys.stderr)
            return 1
        return 0
    if args.report:
        report()
        return 0
    if args.write_baseline:
        if (ROOT / BASELINE).exists():
            sys.exit("hatch_counters: %s exists; use --update (shrink/move) or --allow" % BASELINE)
        write(tree_scan(), mode=args.mode)
        return 0
    if args.reseed:
        reseed()
        return 0
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
