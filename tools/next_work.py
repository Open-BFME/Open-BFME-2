#!/usr/bin/env python3
"""Answer "what should I work on right now" with one validated candidate.

The default draws one candidate at random from the selected tier, weighted by
measured land rate for its size, so concurrent contributors still rarely
collide but no draw is worth merely the pool average. ``--ranked`` is the human/debug
view of the available queues. Live claims are fetched from origin; no compiling.

Byte matching of .text is complete, so the open work is Phase 2: linking, the
structural work the exit test needs (no stubs, retail's translation units) and
cleanup. Every default pick tries gate debt (R) first, then L, D, H, I and the
structural tiers P in an order drawn by weight (TIER_WEIGHTS, justified where it is
defined: link the largest share, every lane a guaranteed one), and
falls through to the next queue when one is empty or every item in it is claimed;
new matches come only after all of them. Queues are built lazily, only when the
order reaches them (debt_order, pick_debt). Each item carries a machine pass test
that is the owning tool's verdict on fresh evidence, never a hand deletion of a
baseline line; tools/repair_queue.py builds the queues and judges retirements.
A standing deferral (blocked, attempted) in reverse/re_attempts.log serves a debt
item only after the untried work of every debt queue; a recorded dead end drops it.

Sections, in priority order:
  0. Ledger health   tools/check_csv.py — a corrupt ledger aborts everything (exit 2)
  R. Repair       gate debt (reverse/gate_baseline.txt; tier C, diffexec, boot and
                  game smoke): the check, the row, and a pass test that deletes the
                  baseline line (--tier repair)
  L. Link repair  rows the last link cycle did not place or wire, else the committed
                  census's units that do not link, with the units changed since the
                  census re-predicted by tools/link_check.py (--tier link)
  D. Data identity  reverse/data_check_baseline.txt keys: a unit binds or defines a
                  second name for a data address (--tier data)
  H. Class header  reverse/header_queue.tsv units that have not adopted their
                  class's canonical header (--tier header)
  I. Code identity  reverse/code_identity_baseline.tsv keys: a reference binds a
                  symbol the link does not resolve to retail's body (--tier identity)
  P. Structural (repair_queue.STRUCTURAL_QUEUES; no register line retires, the pass
     test is the owning tool's verdict):
       stubs        symbols the last link cycle had to stub (its stubs.json, checked
                    against its receipt; skipped where no such output exists)
       consolidate  approved TUs a merge can shrink (tools/tu_skeleton.py --queue)
       tu-approval  TUs whose rows tu_map only proposes: evidence (real names,
                    resolved interleaving) approves them (docs/consolidation.md)
       tu-evidence  unmapped address runs holding sources no tu_map row places, with
                    the retail layout evidence tools/tu_evidence.py re-derives for them
       ms-headers   reverse/ms_header_queue.tsv (repair_queue.py ms-headers)
       dx           reverse/dx_migration_queue.tsv; --tier dx keeps its own view
       stlport      whole files to move onto STLport 4.6 (repair_queue.py stlport, from
                    reverse/stlport_trial.csv): opt in, knobs, ./build.sh, repoint
     Naming is not a default tier: --wb and tools/name_lane.py serve it on request.
  New matches (tiers 1-4, then the Zero Hour packets) appear only on regressions
  now; each is served only when its input file exists, and a tier whose input is
  absent is skipped with a one-line note, never an exit. They carry `dest`: the
  unit the row belongs in (address contiguity), never a fresh one-function file.
  1. Reloc-named  an unclaimed function whose mangled name a byte-true call proved
  2. Drift quick wins  immediate-only / imm+reg literal fixes from drift_report.csv
  3. Structural reconciliation  closest source-shape mismatches
  4. Ghidra-anchored absent  source literals identify an unclaimed retail function
     (--tier similar: unclaimed functions nearest to matched code in BFME1/BFME2,
      tools/similar.py; served on request only, never by the default pick)
  5. Rest of the ladder (pointer commands only, nothing computed)

--claim takes class-only refs for header reconciliation and divergent class
identities, and file refs for body edits. claims.lock_keys retains class-to-file
logical expansion, checked freshly after each push; header work need not reserve
hundreds of file refs. Body edits take their RVA and source lock atomically.
Queues skip work whose logical footprint meets another seat's live claims
(claims.busy_keys). A debt item's claim records its debt
lines and is released by settle once origin/master no longer holds them; file
locks go once no claim of their owner needs them.

  --tier wb (or --wb) serves WorldBuilder name leads instead: see wb_candidates.

Every served candidate carries tools/wpo_detect.py's warning when its body (or a
callee) uses a private register convention plain C++ rarely reproduces (`wpo:`
line, "wpo" in --json); likely-unreproducible ones sort to the end of their
queue and are drawn only when nothing else in the pool is left. Cached per RVA
under build/wpo_detect/.

WorldBuilder leads (reverse/wb_name_leads.csv, via tools/wb_context.py) annotate
every printed candidate with a `WB:` line and the `tools/wb_show.py <rva> --gd`
command. Ranking rule: inside every tier, a candidate whose address carries a
named WB lead scoring >= wb_context.HIGH_SCORE (4.0) has its selection weight
multiplied by wb_context.BOOST (1.5); ranked views keep their own order. The
packet tier also breaks landability ties toward packets whose Zero Hour name or
file agrees with the lead. A lead is identity evidence only, never a match.

Previously attempted candidates carry their standing verdict and full evidence
in `prior_attempt` in --json. Text output prints it before the start command,
including evidence paths; read it before repeating a failed trial.

Usage:
  python3 tools/next_work.py [--claim] [--tier link|data|header|identity|stubs|consolidate|tu-approval|tu-evidence|ms-headers|stlport|...]
  python3 tools/next_work.py --wb [--claim] [--ranked]
  python3 tools/next_work.py --ranked [--limit 10] [--json]

Exit codes: 0 ok, 1 bad inputs (a malformed report; an absent one is skipped),
2 ledger corrupt.
"""
import argparse
import ast
import bisect
import csv
import hashlib
import json
import os
import random
import re
import secrets
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import boundary_validator
import claims
import landability
import re_log
import wb_context
import yield_model

try:  # advisory annotation only; a queue never depends on it
    import wpo_detect
except ImportError:  # pragma: no cover
    wpo_detect = None

ROOT = Path(__file__).resolve().parents[1]
# drift_report.csv is the shared drift classification — it feeds the
# drift/structural/ghidra tiers. The ZH source-porting sweep beside it is not
# retired: tools/zh_sweep.py still writes work packets, and the `packet` tier
# below spends them.
DRIFT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"
PACKETS = ROOT / "reverse" / "zh_sweep" / "packets"
# The fenced block zh_sweep.py writes for each REL32 site, one line per callee.
PACKET_PINS = re.compile(r"## Callee pins[^\n]*\n+```\n(.*?)```", re.S)
GHIDRA_FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"
STRING_XREFS = ROOT / "reverse" / "string_xrefs.tsv"
ANCHORED = ROOT / "reverse" / "anchored_candidates.csv"
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
_SOURCE_INDEX = None
_SOURCE_TEXT = {}

POINTERS = [
    ("python3 tools/land_ambiguous.py",
     "land string-anchored exact-ambiguous drift copies"),
    ("python3 tools/list_naked_candidates.py Code",
     "choose one naked-asm function worth decompiling to C++"),
    ("python3 tools/next_work.py --wb",
     "serve bodies by WorldBuilder lead (original name + source file)"),
]

FIX_INSTRUCTIONS = """\
LEDGER CORRUPT — fix this before doing anything else:
  1. python3 tools/dedup_csv.py
  2. byte-verify any remaining conflicting claims: python3 tools/build.py <source>
     for each claimant — the row that fails verification is the wrong one; delete it
  3. re-run: python3 tools/check_csv.py"""


def check_ledger():
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "check_csv.py")],
                          cwd=ROOT, capture_output=True, text=True)
    if proc.returncode != 0:
        sys.stderr.write(proc.stdout + proc.stderr)
        print(FIX_INSTRUCTIONS, file=sys.stderr)
        raise SystemExit(2)
    return proc.stdout.strip()


# One line per new-match tier skipped because its input file is absent (main prints
# them; --json carries them as "skipped"). Matching is complete, so the generated,
# gitignored inputs of those tiers (drift_report.csv above all) are often absent:
# that skips the tier, it never ends the pick.
SKIPPED = []


def rel_path(path):
    """PATH relative to the checkout where it lies inside it."""
    try:
        return path.relative_to(ROOT).as_posix()
    except ValueError:
        return path.as_posix()


def missing_input(path, tier, regen):
    """True, recording a one-line note in SKIPPED, when TIER's input is absent."""
    if path.exists():
        return False
    note = f"{tier}: {rel_path(path)} absent, tier skipped (regenerate: {regen})"
    if note not in SKIPPED:
        SKIPPED.append(note)
    return True


def read_csv(path, regen):
    """(fieldnames, rows) of a tier's report. Callers check missing_input first; a
    report that is absent here was removed mid-run, and that is an input error."""
    if not path.exists():
        raise SystemExit(f"{path.relative_to(ROOT)} is missing — regenerate it: {regen}")
    with path.open(newline="") as fh:
        reader = csv.DictReader(fh)
        rows, header_dups = [], 0
        for row in reader:
            if row[reader.fieldnames[0]] == reader.fieldnames[0]:
                header_dups += 1  # union-merge damage: a second header line mid-file
                continue
            rows.append(row)
    if header_dups:
        print(f"warning: {path.relative_to(ROOT)} contains {header_dups} repeated "
              f"header line(s) (bad merge) — ignored", file=sys.stderr)
    return reader.fieldnames, rows


def to_int(value, base, what):
    try:
        return int(value, base) if base != 10 else int(value)
    except ValueError:
        raise SystemExit(f"{what}: bad value {value!r} — regenerate the report")


def drift_quick_wins():
    import build
    if missing_input(DRIFT, "harvest", "python3 tools/drift_classify.py"):
        return []
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    claimed = {int(row["target_rva"], 16)  # check_csv validated these
               for row in build.load_claim_rows(counting_dumps=False, matched_only=False)
               if row["target_rva"]}
    last = {}
    for row in rows:
        if row["class"] in ("immediate-only", "imm+reg"):
            last[row["function"]] = row
    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        if rva in claimed:
            continue
        rel = resolve_drift_source(row["source"], name)
        if rel is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        out.append({"function": name, "source": rel,
                    "drift_class": row["class"], "aligned_pct": int(row["aligned_pct"]),
                    "candidate_rva": row["candidate_rva"], "hint": row["hint"],
                    "command": f"python3 tools/build.py {rel}"})
    out.sort(key=lambda c: (-c["aligned_pct"], c["function"]))
    return out


def source_index():
    global _SOURCE_INDEX
    if _SOURCE_INDEX is None:
        _SOURCE_INDEX = {}
        for base in (ROOT / "Code", ROOT / "src"):
            if not base.exists():
                continue
            for path in sorted(base.rglob("*.cpp")):
                _SOURCE_INDEX.setdefault(path.name.casefold(), []).append(path)
    return _SOURCE_INDEX


def resolve_drift_source(basename, function=None):
    """drift_report source column is a bare basename; landed files live under
    Code/ (official tree layout); a few remainders sit under src/. Resolve
    case-insensitively because drift reports normalize names to lowercase.
    When duplicate basenames exist, the decorated-symbol marker is decisive."""
    hits = source_index().get(Path(basename).name.casefold(), [])
    if function and len(hits) > 1:
        marked = []
        for path in hits:
            text = _SOURCE_TEXT.setdefault(path, path.read_text(errors="replace"))
            if function + " present-unmatched" in text or function in text:
                marked.append(path)
        if marked:
            hits = marked
    return hits[0].relative_to(ROOT).as_posix() if hits else None


_GHIDRA_STARTS = None
_GHIDRA_SIZES = None


def _ghidra_sizes():
    """{function start rva: body size} from the inventory, cached. Empty on a
    fresh clone without the generated inventory, so correction silently no-ops."""
    global _GHIDRA_SIZES
    if _GHIDRA_SIZES is None:
        sizes = {}
        if GHIDRA_FUNCTIONS.exists():
            with GHIDRA_FUNCTIONS.open(newline="") as fh:
                for row in csv.DictReader(fh):
                    try:
                        sizes[int(row["rva"], 16)] = int(row["size"])
                    except (ValueError, KeyError, TypeError):
                        pass
        _GHIDRA_SIZES = sizes
    return _GHIDRA_SIZES


def _ghidra_starts():
    """(sorted-list, set) of ghidra function-start RVAs, cached."""
    global _GHIDRA_STARTS
    if _GHIDRA_STARTS is None:
        starts = set(_ghidra_sizes())
        _GHIDRA_STARTS = (sorted(starts), starts)
    return _GHIDRA_STARTS


def snap_rva(rva):
    """drift candidate_rva is an alignment vote, wrong ~99% of the time — it lands
    in int3 padding just before the real start, a few bytes into the SEH prologue,
    or (no leading 0xCC to skip) still inside the PRECEDING function's tail — e.g.
    `c4 10 c3 cc cc ...`, a couple of misdecoded bytes plus a real `ret` before the
    pad run, so the naive leading-0xCC scan never fires. Snap to the nearest ghidra
    function start, trying both directions and keeping whichever is closer.
    Returns (corrected_rva, note|None)."""
    ordered, starts = _ghidra_starts()
    if rva in starts:
        return rva, None
    if not ordered:
        # No Ghidra inventory (it is gitignored, so this is the fresh-clone case):
        # recover the boundary from the retail image instead of no-opping.
        return padding_snap(rva)
    try:
        import bisect
        import build
        data = build.read_target_bytes(rva, 16)
        off = 0
        while off < 15 and off < len(data) and data[off] == 0xCC:
            off += 1
        if off and (rva + off) in starts:
            return rva + off, f"drift-corrected +{off}B (skipped int3 pad)"
        candidates = []
        i = bisect.bisect_right(ordered, rva) - 1
        if 0 <= i < len(ordered) and 0 < rva - ordered[i] <= 48:
            d = rva - ordered[i]
            candidates.append((d, ordered[i], f"drift-corrected -{d}B (snapped to ghidra start)"))
        j = bisect.bisect_left(ordered, rva)
        if 0 <= j < len(ordered) and 0 < ordered[j] - rva <= 48:
            d = ordered[j] - rva
            candidates.append((d, ordered[j],
                                f"drift-corrected +{d}B (snapped to ghidra start, was in preceding fn's tail)"))
        if candidates:
            candidates.sort()
            return candidates[0][1], candidates[0][2]
    except Exception:
        pass
    return padding_snap(rva)


PAD_BYTES = (0xCC, 0x90)
SNAP_WINDOW = 64


def padding_snap(rva):
    """Ghidra-free fallback for the correction above.

    The Ghidra inventory is gitignored, so on a fresh clone `_ghidra_starts()` is
    empty and every drift vote keeps its raw rva — which the docstring above says
    is wrong ~99% of the time. MSVC pads between functions with int3, so the byte
    after a padding run is a real function start and the image alone is enough to
    recover one. Where no boundary is in range, say the candidate is interior
    rather than invent a start: that verdict is what saves the 30-60 minutes."""
    try:
        import build
        head = build.read_target_bytes(rva, SNAP_WINDOW)
        back = build.read_target_bytes(rva - SNAP_WINDOW, SNAP_WINDOW)
    except Exception:
        return rva, None
    if len(head) < 2 or len(back) < SNAP_WINDOW:
        return rva, None

    # The vote landed inside the pad run; the next real body starts after it.
    if head[0] in PAD_BYTES:
        off = 0
        while off < len(head) and head[off] in PAD_BYTES:
            off += 1
        if off < len(head):
            return rva + off, f"drift-corrected +{off}B (queued rva was int3 padding)"
        # A whole window of padding is still padding: saying so is what keeps the
        # interior filter below from serving the address anyway, which is how all
        # 76 int3-headed addresses in the live queue got there.
        return rva, (f"queued rva is int3 padding for at least {SNAP_WINDOW}B — "
                     f"no trustworthy boundary in range")

    # Otherwise the nearest preceding padding run ends on the real start. A lone
    # 0xCC/0x90 is often just an operand byte, so trust a single-byte run only
    # when it lands on MSVC's 16-byte function alignment.
    for distance in range(1, SNAP_WINDOW + 1):
        if back[SNAP_WINDOW - distance] not in PAD_BYTES:
            continue
        start = rva - distance + 1
        run = 0
        while (SNAP_WINDOW - distance - run) >= 0 and back[SNAP_WINDOW - distance - run] in PAD_BYTES:
            run += 1
        if run < 2 and start % 16:
            return rva, (f"lone 0x{back[SNAP_WINDOW - distance]:02X} {distance - 1}B back is an "
                         f"operand byte, not padding — no trustworthy boundary in {SNAP_WINDOW}B")
        if distance == 1:
            return rva, None  # already on a start
        return start, f"drift-corrected -{distance - 1}B (snapped to int3-delimited start)"

    return rva, f"no int3 boundary within {SNAP_WINDOW}B — candidate is function-interior"


def structural_candidates(claimed, claimed_names, claimed_ranges, big=False):
    """The manual-RE tier: drifted functions whose source exists but whose code
    shape differs (class structural / register-swap). Workflow: docs/structural.md."""
    if missing_input(DRIFT, "structural", "python3 tools/drift_classify.py"):
        return []
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {}
    for row in rows:
        if row["class"] in ("structural", "register-swap"):
            last[row["function"]] = row
    # Matched ranges never overlap (identical ICF ranges aside), so "strictly
    # inside any claimed range" is one bisect instead of a scan of ~90k rows
    # per candidate — the scan went quadratic as generated claims tripled the
    # ledger and put next_work minutes over its ten-second budget.
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        i = bisect.bisect_left(starts, point) - 1
        return i >= 0 and point < ranges[i][1]

    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        # candidate_rva is an alignment vote and wrong ~99% of the time; snap it to
        # the real ghidra start so the printed command is usable, and skip if either
        # the raw or corrected rva is already matched (the name filter catches the rest).
        crva, snap_note = snap_rva(rva)
        # A snap result that says the vote is inside a function (or cannot
        # establish a boundary) is not actionable work. Previously these rows
        # were still queued, making agents prove the queue's own warning right.
        if snap_note and ("function-interior" in snap_note
                          or "no trustworthy boundary" in snap_note):
            continue
        # Alignment votes frequently land a few bytes into an already verified
        # function.  A start-address-only check lets those stale rows through and
        # sends contributors on an impossible reconstruction.  Reject both raw
        # and corrected RVAs when either lies strictly inside a claimed range.
        inside_claim = inside_any(rva) or inside_any(crva)
        if rva in claimed or crva in claimed or name in claimed_names or inside_claim:
            continue
        source = resolve_drift_source(row["source"], name)
        if source is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        crva_hex = f"0x{crva:08X}"
        hint = row["hint"] + (f"; {snap_note}, verify the prologue" if snap_note else "")
        out.append({"function": name, "source": source, "drift_class": row["class"],
                    "aligned_pct": int(row["aligned_pct"]), "size": int(row["size"]),
                    "candidate_rva": crva_hex, "hint": hint,
                    "command": (f"python3 tools/explain_mismatch.py '{name}' "
                                f"--rva {crva_hex} --size {row['size']} "
                                f"--source {source}")})
    if big:
        # byte-yield mode: biggest functions first (still gated by alignment)
        out.sort(key=lambda c: (-c["size"],
                                -c["aligned_pct"], c["function"]))
    else:
        # highest alignment first (closest to matching), small before big at equal alignment
        out.sort(key=lambda c: (-c["aligned_pct"],
                                c["size"], c["function"]))
    return out


def marked_function_literals(text, name):
    """Return real C/C++ string literals from the function following its
    `present-unmatched` marker. A small lexer keeps braces and quoted text in
    comments from leaking literals out of adjacent functions."""
    marker = name + " present-unmatched"
    pos = text.find(marker)
    if pos < 0:
        return []
    i = text.find("\n", pos)
    if i < 0:
        return []
    i += 1
    depth = 0
    started = False
    literals = []
    while i < len(text):
        if not started and text.startswith("present-unmatched", i):
            return []
        if text.startswith("//", i):
            end = text.find("\n", i + 2)
            i = len(text) if end < 0 else end + 1
            continue
        if text.startswith("/*", i):
            end = text.find("*/", i + 2)
            i = len(text) if end < 0 else end + 2
            continue
        ch = text[i]
        if ch in ("'", '"'):
            quote = ch
            raw = []
            i += 1
            while i < len(text):
                ch = text[i]
                if ch == "\\" and i + 1 < len(text):
                    raw.extend((ch, text[i + 1]))
                    i += 2
                    continue
                i += 1
                if ch == quote:
                    break
                raw.append(ch)
            if quote == '"':
                try:
                    value = ast.literal_eval('"' + "".join(raw) + '"')
                except (SyntaxError, ValueError):
                    value = "".join(raw)
                if isinstance(value, str) and len(value) >= 5:
                    literals.append(value)
            continue
        if ch == "{":
            depth += 1
            started = True
        elif ch == "}" and started:
            depth -= 1
            if depth == 0:
                return literals
        i += 1
    return []


def read_string_xrefs():
    out = {}
    with STRING_XREFS.open(encoding="utf-8", errors="replace") as fh:
        for line in fh:
            literal, tab, rvas = line.rstrip("\n").partition("\t")
            if not tab:
                continue
            values = out.setdefault(literal, set())
            for value in rvas.split(","):
                if value:
                    values.add(int(value, 16))
    return out


def ghidra_absent_candidates(claimed, claimed_names):
    """Map ZH functions classified `absent` to BFME functions through rare
    string literals found inside the marked source body. Ghidra already gives
    each literal's referencing function RVA, exact boundary, and size."""
    if not GHIDRA_FUNCTIONS.exists() or not STRING_XREFS.exists():
        return [], ("Ghidra outputs unavailable — generate them per "
                    "tools/ghidra/README.md")
    if missing_input(DRIFT, "ghidra", "python3 tools/drift_classify.py"):
        return [], f"{rel_path(DRIFT)} absent — Ghidra tier skipped"

    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {row["function"]: row for row in rows if row["class"] == "absent"}
    functions = {}
    with GHIDRA_FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            functions[int(row["rva"], 16)] = row
    xrefs = read_string_xrefs()
    source_text = {}
    out = []
    for name, row in last.items():
        if name in claimed_names:
            continue
        hits = source_index().get(Path(row["source"]).name.casefold(), [])
        if not hits:
            continue
        source_rel = resolve_drift_source(row["source"], name)
        if source_rel is None:
            continue
        source_path = ROOT / source_rel
        text = source_text.setdefault(source_path, source_path.read_text(errors="replace"))
        literals = set(marked_function_literals(text, name))
        anchored = {}
        rarity = {}
        for literal in literals:
            refs = xrefs.get(literal, set())
            # Common UI words and format fragments create misleading cross-file
            # matches. Multiple rare literals remain useful and rank together.
            if not refs or len(refs) > 8:
                continue
            for rva in refs:
                if rva not in functions or rva in claimed:
                    continue
                anchored.setdefault(rva, set()).add(literal)
                rarity[rva] = rarity.get(rva, 0.0) + 1.0 / len(refs)
        viable = []
        source_size = int(row["size"])
        for rva, anchors in anchored.items():
            # One unique/two-way literal or two independent literals is enough
            # to justify a Ghidra inspection; weaker guesses stay hidden.
            if len(anchors) < 2 and rarity[rva] < 0.5:
                continue
            target_size = int(functions[rva]["size"])
            viable.append((rva, anchors, rarity[rva], target_size))
        if not viable:
            continue
        viable.sort(key=lambda c: (-len(c[1]), -c[2],
                                   abs(c[3] - source_size), c[3], c[0]))
        rva, anchors, anchor_score, target_size = viable[0]
        confidence = "high" if len(anchors) >= 2 and anchor_score >= 1.0 else "medium"
        source = source_path.relative_to(ROOT).as_posix()
        out.append({
            "function": name, "source": source, "source_size": source_size,
            "target_rva": f"0x{rva:08X}", "target_size": target_size,
            "ghidra_name": functions[rva]["name"], "confidence": confidence,
            "anchors": sorted(anchors), "anchor_score": round(anchor_score, 3),
            "alternates": len(viable) - 1,
            "command": (f"python3 tools/explain_mismatch.py '{name}' --rva 0x{rva:08X} "
                        f"--size {target_size} --source {source}"),
        })
    out.sort(key=lambda c: (c["confidence"] != "high",
                            -len(c["anchors"]), -c["anchor_score"], c["target_size"],
                            abs(c["target_size"] - c["source_size"]), c["function"]))
    return out, (f"{len(functions)} Ghidra functions + {len(xrefs)} string literals loaded")


def _candidate_rva(candidate):
    """The address this candidate would actually be worked at, as an int."""
    text = candidate.get("candidate_rva") or candidate.get("target_rva")
    try:
        return int(text, 16) if text else None
    except ValueError:
        return None


def annotate_stashes(candidates):
    """Hang the banked attempt on every candidate that has one.

    Done once here rather than at each output site, so the JSON, the ranked
    view and the selected view cannot disagree about what is banked.
    """
    for candidate in candidates:
        rva = _candidate_rva(candidate)
        found = re_log.stash_for(rva) if rva is not None else None
        if found:
            path, score = found
            candidate["stash"] = path.relative_to(ROOT).as_posix()
            candidate["score"] = score
    return candidates


def annotate_attempts(candidates):
    """Expose the candidate's own standing verdict, without changing selection.

    Boundary/void rules stay in re_log. In particular, a drift-corrected
    boundary must not acquire a verdict recorded only at its old address.
    Keep the full evidence: handoff paths often occur after a long trial note.
    """
    for candidate in candidates:
        candidate.pop("prior_attempt", None)
        symbol = candidate.get("function")
        if not symbol:
            continue
        rva = _candidate_rva(candidate)
        moved = "drift-corrected" in candidate.get("hint", "")
        status = re_log.standing_status(symbol, rva, boundary_moved=moved)
        if status is not None:
            candidate["prior_attempt"] = {
                "status": status,
                "evidence": re_log.standing_evidence(
                    symbol, rva, boundary_moved=moved) or "",
                "log": "reverse/re_attempts.log",
            }
    return candidates


def stash_line(candidate):
    """The one-line pointer at a banked body, or None. Printed beside `start:`."""
    if "stash" not in candidate:
        return None
    return (f"       stash: {candidate['stash']} (score {candidate['score']}) "
            f"— a previous attempt got this far; start from it")


def _print_stash(candidate):
    line = stash_line(candidate)
    if line:
        print(line)
    _print_wb(candidate)


def wb_lines(candidate):
    """The WorldBuilder lead for this candidate's address, as printable lines.

    Printed beside the stash pointer for every candidate in every tier, so a
    seat starts from WB's near-source debug body rather than from retail's
    optimised one. Empty when WB has no lead at this address.
    """
    rva = _candidate_rva(candidate)
    found = wb_context.lead(rva) if rva is not None else None
    if not found:
        return []
    return [f"       {wb_context.line(found)}",
            f"       wb_show: {wb_context.show_command(rva)}"]


def _print_wb(candidate):
    for line in wb_lines(candidate):
        print(line)
    _print_wpo(candidate)


def _print_wpo(candidate):
    if candidate.get("wpo"):
        print(f"       wpo: {candidate['wpo']} (tools/wpo_detect.py "
              f"{candidate.get('candidate_rva') or candidate.get('target_rva')})")


def unreproducible(candidate):
    """True when wpo_detect saw a register-passed call (served last)."""
    return str(candidate.get("wpo", "")).startswith("likely")


def annotate_wpo(candidates):
    """Hang wpo_detect's warning on each candidate and move the likely
    unreproducible ones to the end, keeping every candidate and the queue's
    own order otherwise. Cached per RVA under build/wpo_detect/."""
    if wpo_detect is None:
        return candidates
    fresh = [c for c in candidates
             if _candidate_rva(c) is not None and not wpo_detect.is_cached(_candidate_rva(c))]
    if len(fresh) > 200:
        print(f"wpo_detect: analysing {len(fresh)} uncached candidate(s) once "
              f"(cached under build/wpo_detect/)", file=sys.stderr)
    for candidate in candidates:
        rva = _candidate_rva(candidate)
        if rva is None:
            continue
        try:
            size = int(candidate.get("size") or candidate.get("target_size") or 0) or None
        except (TypeError, ValueError):
            size = None
        warning = wpo_detect.warning(rva, size)
        if warning:
            candidate["wpo"] = warning
    candidates.sort(key=unreproducible)
    return candidates


def annotate_wb(candidates):
    """Hang the WB lead on every candidate (for --json); never filters."""
    for candidate in candidates:
        rva = _candidate_rva(candidate)
        found = wb_context.lead(rva) if rva is not None else None
        if found:
            candidate["wb"] = {key: found[key] for key in
                               ("wb_name", "wb_path", "score", "evidence", "kind")}
            candidate["wb"]["show"] = wb_context.show_command(rva)
    return candidates


def _candidate_rva(candidate):
    """This candidate's boundary as an int, or None if it carries no address."""
    for key in ("candidate_rva", "target_rva"):
        text = candidate.get(key)
        if text:
            try:
                return int(str(text), 16)
            except ValueError:
                return None
    return None


def claim_targets(candidate):
    """What --claim takes for this candidate: its scopes (`class:NAME`, `file:PATH`:
    the item's `claim` list, set where the fix is wider than one body) when it names
    any, else its RVA; [] when it has neither."""
    if candidate.get("claim"):
        return list(candidate["claim"])
    rva = _candidate_rva(candidate)
    return [] if rva is None else [rva]


def claim_keys(candidate):
    """The claim keys this candidate's work names: the scopes it claims, its RVA, its
    own source file and the class it works on (an item's `class`). claims.lock_keys
    expands them to every file the work touches; two items collide exactly when
    their lock keys meet."""
    keys = {claims.key_of(scope) for scope in candidate.get("claim") or ()}
    source = candidate.get("source") or ""
    real = source if source and not source.startswith("(") else None
    # Reference packets name a donor source; their proposed target unit is the
    # file a worker edits. Fence it as well, including for unrowed addresses.
    destination = candidate.get("dest")
    if destination:
        keys.add(claims.file_key(destination))
    return keys | claims.work_keys(_candidate_rva(candidate), real, candidate.get("class"))


def busy_keys():
    """claims.busy_keys(): the lock keys of every live claim in all namespaces (the
    mirrored remote's RVAs included)."""
    return claims.busy_keys()


def without_busy(candidates, busy):
    """Keep every queue view consistent with live shared work claims: drop a candidate
    whose lock keys meet those of `busy` (claim keys)."""
    locked = claims.lock_keys(busy)
    return [candidate for candidate in candidates if not claims.lock_keys(claim_keys(candidate)) & locked]


def claim_note(label, candidate):
    """The claim's note: the label, plus `debt=` for every debt item that names its
    debt lines (debt_lines, else its baseline_line), which claims.settle_scopes
    releases once origin/master no longer holds them."""
    lines = candidate.get("debt_lines") or ([candidate["baseline_line"]] if candidate.get("baseline_line") else [])
    if lines and candidate.get("baseline"):
        return f"next_work {label} " + claims.debt_note({candidate["baseline"]: lines})
    return f"next_work {label}"


@claims.pick_snapshot()
def claim_choice(candidates, label):
    """Claim one draw (claim_targets) with every file its work touches (claims.acquire:
    create-only refs, all or nothing), trying another draw -- and dropping whatever
    collides with the refused keys -- when a peer holds any of them."""
    remaining = list(candidates)
    while remaining:
        candidate = weighted_choice(remaining)
        targets = claim_targets(candidate)
        if not targets:
            raise SystemExit("next_work: selected candidate has no claimable RVA or scope")
        keys = claim_keys(candidate)
        shown = ", ".join(claims.label(claims.key_of(t)) for t in targets)
        try:
            result = claims.acquire(targets, keys, note=claim_note(label, candidate))
        except claims.ClaimsUnavailable as error:
            if error.unclean:
                raise SystemExit(f"next_work: {error}; partial claims remain, refusing a new pick") from error
            if error.reachable:
                raise SystemExit(f"next_work: {error}; no work served") from error
            held = set(error.refused)
            if claims.lock_keys(held) & claims.lock_keys(keys):     # origin showed a peer holding it
                remaining = [c for c in without_busy(remaining, held) if c is not candidate]
                continue
            # AGENTS.md: the picker warns and serves the body unclaimed
            print(f"next_work: {error}; serving {shown} without a shared claim",
                  file=sys.stderr)
            return candidate, list(error.claimed)
        if not result.refused:
            return candidate, list(result.claimed)
        why = ("claim push refused by reachable origin" if getattr(result, "unconfirmed", ())
               else "held by another worker")
        print(f"next_work: {', '.join(claims.label(k) for k in result.refused)} {why}; "
              f"skipping {shown}", file=sys.stderr)
        # An unconfirmed push is no evidence of a peer owning the whole file.
        # Leave siblings eligible for their own acquisition attempt.
        held = set(result.refused) - set(getattr(result, "unconfirmed", ()))
        remaining = [c for c in without_busy(remaining, held) if c is not candidate]
    return None, []


def serve_dx(args):
    """--tier dx: a unit to move off the reference/shims DirectX stand-ins onto
    the SDK headers (`// dxsdk`). The work is per file, so --claim takes a
    file:PATH scope claim, moving to the next unit when a peer holds one."""
    import dx_migration
    if args.claim:
        claims.settle(defer=True)    # rides on the claim push
    for record in dx_migration.servable():
        scope = "file:" + record["source"]
        # `class` here is a migration classification, not a C++ class scope.
        candidate = {"source": record["source"], "function": record["source"], "claim": [scope]}
        if not apply_shard([candidate], args.shard):
            continue
        note = ""
        if args.claim:
            picked, acquired = claim_choice([candidate], "dx")
            if picked is None:
                continue
            if acquired:
                note = f"claim: {scope} held on origin"
        if args.json:
            print(json.dumps({"tier": "dx", "selection": record, "claim": note or None}, indent=2))
        else:
            if note:
                print(note)
            print(f"dx tier: {record['source']}  [{record['class']}] {record['matched_rows']} row(s)"
                  f"{'  edits: ' + record['edits'] if record['edits'] else ''}")
        return 0
    print("dx tier: nothing queued (python3 tools/dx_migration.py scan)")
    return 0


def _print_boundary_verdicts(candidate, limit=3):
    """Report the candidate's own verdict and findings under other names.

    One retail address carries several drifted names, and a verdict retires the
    name it names -- not the address. So the queue legitimately re-serves an
    address under the next name, and did so with no sign anybody had looked:
    0x0054C5D5 was recorded mis-anchored as deque<BfmeE8>::_M_range_check
    because the body builds a formatted exception message, then came back as
    deque<BfmeE8>::resize. Printing the earlier finding is not a filter -- "not
    A" is no proof of "not B" -- it just starts the next agent from the
    disassembly that was already paid for.
    """
    annotate_attempts([candidate])
    prior = candidate.get("prior_attempt")
    if prior:
        print(f"       prior attempt: {prior['status']} ({prior['log']})")
        if prior["evidence"]:
            print(f"         {' '.join(prior['evidence'].split())}")
        print("       Read the prior evidence before retrying; do not repeat "
              "unchanged failed trials.")
    rva = _candidate_rva(candidate)
    if rva is None:
        return
    found = re_log.verdicts_at(rva, exclude=candidate.get("function"))
    if not found:
        return
    print(f"       already investigated at this same address "
          f"({len(found)} verdict(s), evidence in reverse/re_attempts.log):")
    for symbol, status, evidence in found[:limit]:
        shown = " ".join(evidence.split())
        print(f"         {status} as {symbol}")
        if shown:
            print(f"           {shown}")
    if len(found) > limit:
        print(f"         ... and {len(found) - limit} more at this address")


def drop_logged(candidates):
    """Filter one queue, returning (kept, dropped_count). Never silent: main()
    reports the count so a shrunken queue is visibly explained, not mistaken
    for an exhausted tier.

    Only a BOUNDARY finding is terminal for automatic selection — workers must
    not rediscover a recorded dead end; --include-logged reopens it for humans.
    Such a verdict describes the boundary that agent actually examined, so it
    retires a candidate only while the boundary still matches: where the log
    records the RVA (5-field shape) that comparison is exact. Where it records
    none, there is no boundary to have moved and the verdict stands however
    the hint reads.

    An agent's deferral (blocked/attempted/abandoned) is never terminal: every
    retail byte still needs C++, so those candidates are kept and tagged
    `deferred_attempts` instead, which weighted_choice reads to serve them only
    once nothing untried is left. See tools/re_log.py."""
    kept, dropped = [], 0
    for candidate in candidates:
        moved = "drift-corrected" in candidate.get("hint", "")
        rva = _candidate_rva(candidate)
        if re_log.is_dead_end(candidate["function"], rva, boundary_moved=moved):
            dropped += 1
            continue
        if re_log.is_deferred(candidate["function"], rva, boundary_moved=moved):
            candidate["deferred_attempts"] = re_log.attempts(candidate["function"])
        kept.append(candidate)
    return kept, dropped


def structural_validator():
    """Boundary validator over the retail image and the Ghidra inventory."""
    import build
    return boundary_validator.BoundaryValidator(build.read_target_bytes,
                                                _ghidra_sizes())


_SYMBOL_MAP = None


def callee_resolves(symbol, address):
    """Would the byte gate resolve THIS name at THIS address?

    Asked of the symbol the candidate's reloc references, not of the address on
    its own: retail folds and duplicates bodies, so an address some other name
    covers is no evidence that this call site encodes where the ledger says.
    Live rather than the packet's generation-time mark, so a pin that landed
    after `zh_sweep.py packets` last ran cannot leave the body looking blocked.
    """
    global _SYMBOL_MAP
    if _SYMBOL_MAP is None:
        import build
        _SYMBOL_MAP = build.load_symbol_map()
    return address in _SYMBOL_MAP.get(symbol, ())


def collapse_and_validate(candidates, validator=None):
    """Serve one item per address, and only where the address is a boundary.

    `structural_candidates` dedupes by symbol name and never by address, so the
    same body is queued once per name that drifted onto it: 3,923 candidates
    over 1,200 addresses, one 40-byte body claimed by 1,231 names out of 409
    source files. Collapsing is also what makes the arity check pay -- a shared
    address keeps only the names whose stack cleanup its body can satisfy, and
    an address that keeps none is not work at all.

    The collapsed item keeps every scalar key a single candidate had, because
    shard_key, cluster_of and print_candidate all read them, and adds the full
    surviving name list, retail's own body size, and any size warning. `size`
    deliberately stays the compiled size: candidate_weight reads it, so writing
    the extent there would retune the selection weights as a side effect.

    Group order is the queue's own ranking, so the representative is the best
    candidate at that address under whichever order the caller asked for.
    Returns (items, meta); `validator` is injected by the replay tests.
    """
    groups = {}
    for candidate in candidates:
        rva = _candidate_rva(candidate)
        if rva is None:
            raise SystemExit(f"structural candidate {candidate['function']} carries no "
                             f"usable rva ({candidate.get('candidate_rva')!r}) — "
                             f"regenerate drift_report.csv")
        groups.setdefault(rva, []).append(candidate)
    if groups and validator is None:
        validator = structural_validator()

    kept, refuted, reasons = [], 0, {}
    for rva, group in groups.items():
        verdict = validator.validate([c["function"] for c in group], rva,
                                     group[0]["size"])
        refuted += len(verdict["refuted"])
        if verdict["reject"]:
            reasons[verdict["reject"]] = reasons.get(verdict["reject"], 0) + 1
            continue
        surviving = set(verdict["names"])
        group = [c for c in group if c["function"] in surviving]
        best = group[0]
        served = verdict["extent"] or best["size"]
        kept.append(dict(
            best,
            functions=[c["function"] for c in group],
            extent=verdict["extent"],
            warnings=verdict["warnings"],
            command=(f"python3 tools/explain_mismatch.py '{best['function']}' "
                     f"--rva {best['candidate_rva']} --size {served} "
                     f"--source {best['source']}")))
    meta = {"addresses": len(groups), "served": len(kept),
            "rejected": len(groups) - len(kept),
            "names": sum(len(item["functions"]) for item in kept),
            "refuted": refuted,
            "reasons": dict(sorted(reasons.items(), key=lambda item: -item[1]))}
    return kept, meta


def validator_note(meta):
    """One line for what the boundary validator removed, or None if it ran on
    nothing. Never silent: a queue that shrank by three quarters has to say so."""
    if not meta["addresses"]:
        return None
    return (f"boundary validator: {meta['served']} of {meta['addresses']} structural "
            f"address(es) survive ({meta['rejected']} are not a function boundary), "
            f"carrying {meta['names']} name(s) ({meta['refuted']} refuted by arity)")


def parse_shard(value):
    """Parse INDEX/COUNT using zero-based indexes."""
    try:
        index_text, count_text = value.split("/", 1)
        index, count = int(index_text), int(count_text)
    except (AttributeError, TypeError, ValueError):
        raise argparse.ArgumentTypeError("shard must be INDEX/COUNT, for example 0/3")
    if count <= 0 or index < 0 or index >= count:
        raise argparse.ArgumentTypeError(
            "shard requires COUNT > 0 and 0 <= INDEX < COUNT")
    return index, count


def shard_key(candidate):
    """Return a stable key independent of queue order and processes."""
    for field in ("target_rva", "candidate_rva"):
        value = candidate.get(field)
        if value:
            return int(value, 16)
    digest = hashlib.sha256(candidate["function"].encode("utf-8")).digest()
    return int.from_bytes(digest[:8], "big")


def apply_shard(candidates, shard):
    if shard is None:
        return candidates
    index, count = shard
    return [candidate for candidate in candidates
            if shard_key(candidate) % count == index]


def debt_rank_factor(candidate):
    """How much a debt queue's own ranking multiplies a draw: header units by their
    class's place in DEPENDENCY_ORDER (rank 0 of N weighs N, the last 1: a class is
    adopted once the types it uses have one definition), data keys by how many keys
    share their address (one declaration fix, repeated) and doubly for duplicate-def
    (a link blocker), link units by how few blockers they have left, stub groups by the
    stubs they close, merges by the files they remove, TU approvals by the files their
    proposed rows span, TU-evidence runs by the sources they hold, STLport files by the
    trial rows they move when the trial compiled the unit itself and saw no row of it
    fail (each capped at 16; a library lead or a file with a failed row weighs 1), and
    debt whose source vanished (a regression) first. 1 for anything else."""
    if candidate.get("check") == "vanished-source":
        return 16
    tier = candidate.get("tier")
    if tier == "header":
        return max(1, int(candidate.get("ranks", 1)) - int(candidate.get("rank", 0)))
    if tier == "data":
        return min(16, int(candidate.get("keys_at_address", 1))) * (2 if candidate.get("check") == "duplicate-def"
                                                                    else 1)
    if tier == "link" and "blockers" in candidate:
        return max(1, 8 - int(candidate["blockers"]))
    if tier in ("stubs", "consolidate", "tu-approval", "tu-evidence"):   # stubs closed, files a merge removes or could
        return max(1, min(16, int(candidate.get("count") or 1)))
    if tier == "stlport":
        clean = candidate.get("lead") == "unit" and not candidate.get("trial_fails")
        return max(1, min(16, int(candidate.get("count") or 1))) if clean else 1
    return 1


def candidate_weight(candidate):
    """Selection weight for one candidate: see tools/yield_model.weight.

    The queues already rank themselves and the selector used to throw that
    ranking away, so every draw was worth the pool average.

    A high-score named WorldBuilder lead (wb_context.is_high) multiplies the
    weight by wb_context.BOOST: knowing the body's original name and file is
    what the first hour of an unnamed body goes on. Modest on purpose -- it is
    identity evidence, not landing evidence -- so the measured size curve still
    dominates the draw. The similar tier keeps its resemblance order in the
    draw (score 1.0 keeps the full weight, 0.5 a quarter of it)."""
    weight = yield_model.weight(
        candidate.get("size") or candidate.get("target_size") or candidate.get("credit") or 1)
    weight *= debt_rank_factor(candidate)
    if "similarity" in candidate:
        weight = max(1, round(weight * candidate["similarity"] ** 2))
    rva = _candidate_rva(candidate)
    factor = wb_context.boost(wb_context.lead(rva)) if rva is not None else 1.0
    return max(1, int(round(weight * factor)))


def deferred_note(candidates):
    """One line about deferred candidates in the pool, or None.

    A deferral is served last, not hidden, so a pool that looks empty of fresh
    work must say so rather than silently drawing a body somebody already
    reverted once.
    """
    n = sum(1 for c in candidates if c.get("deferred_attempts"))
    if not n:
        return None
    return (f"re_attempts: {n} candidate(s) carry an earlier deferral and are "
            f"drawn only once untried work runs out")


def weighted_choice(candidates):
    """Draw one candidate with probability proportional to candidate_weight.

    Still random, so concurrent contributors still rarely collide — collision
    avoidance never required a flat distribution.

    Candidates carrying a deferral (an earlier agent hit a codegen wall and
    reverted) are drawn from only when nothing untried is left, rather than
    reweighted: tools/yield_model records what predicts landing and attempt
    count is not among the measured features, so biasing the fitted draw on it
    would be exactly the unmeasured weight that module warns against. Ordering
    is a scheduling rule and claims nothing about probability. It also lets the
    sibling effect do the work -- by the time the untried queue drains, the
    file's other bodies have landed, which is the condition under which the
    measured land rate more than doubles.
    """
    fresh = [c for c in candidates if not c.get("deferred_attempts")]
    if fresh:
        candidates = fresh
    else:
        candidates = sorted(candidates, key=lambda c: c["deferred_attempts"])
        fewest = candidates[0]["deferred_attempts"]
        candidates = [c for c in candidates if c["deferred_attempts"] == fewest]
    # Likely-unreproducible register conventions (wpo_detect) are served last
    # by the same scheduling rule, never dropped.
    clear = [c for c in candidates if not unreproducible(c)]
    if clear:
        candidates = clear
    weights = [candidate_weight(c) for c in candidates]
    cutoff = secrets.randbelow(sum(weights))
    for candidate, weight in zip(candidates, weights):
        cutoff -= weight
        if cutoff < 0:
            return candidate
    raise AssertionError("weighted_choice fell through its cumulative walk")


def anchored_candidates(claimed, claimed_names, claimed_ranges):
    """Unclaimed retail functions identified by a literal only they reference.

    The Ghidra tier anchors strings starting from a drift row, so it only ever
    reaches functions that already have a Zero Hour counterpart -- a finite
    input, now drained. tools/anchor_unclaimed.py runs the same evidence from
    the image side and caches the result here, because scanning 5,512 reference
    files does not fit this tool's ten-second budget.

    These carry an identity LEAD, not a name: the anchor says which ZH source
    the body came from, and recovering the symbol is the first part of the job.
    """
    if missing_input(ANCHORED, "anchored", "python3 tools/anchor_unclaimed.py"):
        return [], (f"{rel_path(ANCHORED)} not generated — "
                    f"run python3 tools/anchor_unclaimed.py")
    _, rows = read_csv(ANCHORED, "python3 tools/anchor_unclaimed.py")
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        index = bisect.bisect_left(starts, point) - 1
        return index >= 0 and point < ranges[index][1]

    out, stale = [], 0
    for row in rows:
        rva = to_int(row["target_rva"], 16,
                     f"anchored_candidates.csv target_rva for {row['ghidra_name']}")
        if rva in claimed or inside_any(rva):
            stale += 1          # landed since the cache was generated
            continue
        source = resolve_drift_source(row["zh_source"])
        out.append({
            "function": row["ghidra_name"],
            "source": source or f"(no Code/ file yet; ZH: {row['zh_source']})",
            "zh_source": row["zh_source"],
            "target_rva": row["target_rva"],
            "size": int(row["target_size"]),
            "confidence": row["confidence"],
            "alternates": int(row["alternates"]),
            "anchor": row["anchor"],
            "command": (f"python3 tools/decode_calls.py --rva {row['target_rva']} "
                        f"--size {row['target_size']}"),
        })
    out.sort(key=lambda c: (c["confidence"] != "high", -c["size"]))
    note = f"{len(out)} anchored candidate(s)"
    if stale:
        note += f"; {stale} already landed (regenerate with anchor_unclaimed.py)"
    return out, note


def reloc_named_candidates(claimed, claimed_ranges):
    """Unclaimed functions whose mangled name a byte-true call site proved.

    For an `identity=real` row this is the strongest identity the queue carries.
    Every other tier hands over a lead -- a shape that lines up, a literal only
    one function references -- and recovering the name is the first half of the
    job. Here the decorated name IS the evidence: it came out of the relocation
    of a call whose compiled bytes are retail's own, so the class, the signature
    and the stack cleanup are all known before the work starts. What remains is
    placing the body in the tree, and the caller that named it says where to
    look.

    `identity=generated` rows are the same evidence about a name this project
    minted itself for a machine-generated funclet, and they outnumber the
    recovered ones about two to one. They are NOT served here: nothing about a
    minted name tells a worker what the function is, and serving them anyway is
    how sessions ended as "log anonymous template" dead ends -- the sort put
    them last, but the weighted draw ignores the sort and landed on them almost
    half the time. Their bytes are already claimed as Code/gen_asm/ dumps, so
    the convert lane serves them with the byte evidence attached instead.
    """
    if missing_input(RELOC_NAMES, "named", "./build.sh"):
        return [], f"{rel_path(RELOC_NAMES)} absent — reloc-named tier skipped"
    _, rows = read_csv(RELOC_NAMES, "./build.sh")
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        index = bisect.bisect_left(starts, point) - 1
        return index >= 0 and point < ranges[index][1]

    out, stale, minted = [], 0, 0
    for row in rows:
        rva = to_int(row["target_rva"], 16,
                     f"reloc_names.csv target_rva for {row['name']}")
        if rva in claimed or inside_any(rva):
            stale += 1          # landed since the last full gate regenerated it
            continue
        if row["notes"].endswith("identity=generated"):
            minted += 1         # a name we invented proves nothing; convert lane
            continue
        out.append({
            "function": row["name"],
            "source": row["source"],
            "target_rva": row["target_rva"],
            "size": int(row["target_size"]),
            "notes": row["notes"],
            "command": (f"python3 tools/decode_calls.py --rva {row['target_rva']} "
                        f"--size {row['target_size']}"),
        })
    out.sort(key=lambda candidate: -candidate["size"])
    note = f"{len(out)} reloc-named candidate(s), recovered identity only"
    if minted:
        note += (f"; {minted} minted-name rows withheld "
                 f"(their bytes are served by the convert lane)")
    if stale:
        note += f"; {stale} already landed (regenerated by the next full gate)"
    return out, note


def packet_candidates(claimed):
    """Unclaimed bodies tools/zh_sweep.py wrote a Zero Hour work packet for.

    A packet carries EA's own source for the body, its name, and how closely it
    already aligns with the retail bytes -- the strongest start any tier here
    offers. They sit at addresses no other tier reaches, so without this they
    are served by nothing: 148 of the first 150 written were never worked.

    Each is also scored on the deficits that actually predicted failure --
    boundary, callee provenance, compiler shape -- because package alignment
    does not: 0x00203E47 aligned at 92% and burned three seats. The score is
    carried so tools/landability.band can serve the best band first, and so the
    selection JSON says what a draw was worth.
    """
    if missing_input(PACKETS, "packet", "python3 tools/zh_sweep.py packets"):
        return []
    validator = structural_validator()
    out = []
    for path in sorted(PACKETS.glob("*.md")):
        try:
            rva = int(path.stem, 16)
        except ValueError:
            continue
        if rva in claimed:
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        size = re.search(r"- (\d+) bytes", text)
        aligned = re.search(r"agrees on ([\d.]+)%", text)
        lead = re.search(r"- `([^`]+)`\n\s+in `([^`]+)`", text)
        pins = PACKET_PINS.search(text)
        function = lead.group(1) if lead else "(see packet)"
        served = int(size.group(1)) if size else 0
        start_ok, start_why = validator.check_start(rva)
        out.append({
            "target_rva": f"0x{rva:08X}",
            "size": served,
            "aligned_pct": aligned.group(1) if aligned else "?",
            "function": function,
            "source": lead.group(2) if lead else str(path.relative_to(ROOT)),
            "packet": str(path.relative_to(ROOT)),
            "landability": landability.verdict(
                function, served, start_ok, start_why, pins.group(1) if pins else "",
                resolves=callee_resolves),
        })
    # A packet whose Zero Hour name (or file) agrees with the WorldBuilder lead
    # at the same address has two independent identity witnesses; within one
    # landability rank it goes first. Never across ranks: the lead says nothing
    # about boundary or callee provenance, which is what the rank measures.
    for candidate in out:
        candidate["wb_agree"] = wb_context.agreement(
            wb_context.lead(int(candidate["target_rva"], 16)),
            name=candidate["function"], source=candidate["source"])
    out.sort(key=lambda c: (c["landability"]["rank"],
                            wb_context.AGREE_RANK[c["wb_agree"]], -c["size"]))
    return out


# Ledger kinds (as tools/wb_match.py classified them) whose row still lacks a
# real identity: a gen-* placeholder, a real class with an invented method name,
# or a symbols.csv pin with no source. A WB name is exactly what these need.
WB_ROWED_KINDS = ("PLACEHOLDER", "PARTIAL", "PIN_ONLY")
WB_BANDS = {0: "rowed, needs its name", 1: "unrowed, WB names its file"}
WB_NO_FILE = "(WB file unknown)"


def wb_real_rvas(rows):
    """Addresses a matched row already holds under a REAL (non-invented) name.

    reverse/wb_name_leads.csv is a snapshot; this is the live check that a
    lead's address has not been named since it was written. Uses wb_gold's
    classifier, the one wb_match.py used to write the snapshot's kinds.
    """
    import wb_gold
    real = set()
    for row in rows:
        if row.get("status") != "matched" or not row.get("target_rva"):
            continue
        try:
            info = wb_gold.describe(row["name"], row.get("source", ""))
        except Exception:  # DemangleError: outside the demangler's subset
            continue
        if info and info["kind"] == "REAL":
            real.add(int(row["target_rva"], 16))
    return real


def wb_candidates(sourced_ranges, real_rvas, sizes, leads=None):
    """Bodies served by WorldBuilder lead, best-evidenced band first.

    Band 0: rows whose identity is still invented (PLACEHOLDER / PARTIAL /
    PIN_ONLY) and whose lead carries a WB function name -- recovering the name
    and writing the real C++ is the work, and wb_show prints the debug body.
    Band 1: functions nothing rows yet (UNROWED) whose lead names a WB source
    file; the name may still be unknown.

    Within a band candidates are grouped by WB file, then class, then address,
    so the ranked view reads as files to drain. `sourced_ranges` are ledger
    rows with source (not gen dumps): an UNROWED lead inside one is stale.
    `real_rvas` (wb_real_rvas) retires any lead whose address is named since.
    `sizes` maps rva -> body size (ledger extent, else the Ghidra inventory).
    """
    leads = wb_context.leads() if leads is None else leads
    ranges = sorted(sourced_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        index = bisect.bisect_right(starts, point) - 1
        return index >= 0 and ranges[index][0] <= point < ranges[index][1]

    out = []
    for rva, lead in leads.items():
        if rva in real_rvas:
            continue
        if lead["kind"] in WB_ROWED_KINDS and lead["wb_name"]:
            band = 0
        elif lead["kind"] == "UNROWED" and lead["wb_path"]:
            if inside_any(rva):
                continue
            band = 1
        else:
            continue
        name = lead["wb_name"] or lead["current_name"] or f"sub_{rva:08X}"
        out.append({
            "target_rva": f"0x{rva:08X}",
            "size": sizes.get(rva, 0),
            "function": name,
            "current_name": lead["current_name"],
            "kind": lead["kind"],
            "band": band,
            "source": lead["wb_path"] or WB_NO_FILE,
            "wb_class": lead["wb_class"],
            "wb_score": lead["score"],
            "evidence": lead["evidence"],
            "command": wb_context.show_command(rva),
        })
    out.sort(key=lambda c: (c["band"], c["source"] == WB_NO_FILE,
                            c["source"].casefold(), c["wb_class"],
                            int(c["target_rva"], 16)))
    return out


def wb_band(candidates):
    """(the best non-empty band, how many candidates the other bands hold)."""
    for band in sorted(WB_BANDS):
        served = [c for c in candidates if c["band"] == band]
        if served:
            return served, len(candidates) - len(served)
    return [], 0


def wb_local_source(candidate):
    """Where this WB file's bodies live in Code/, as a short note.

    The exact basename when Code/ has it; otherwise the split units this repo
    carved from it (ScriptActions.cpp -> ScriptActionsRva003BB6C0.cpp, ...),
    matched as basename prefix followed by a non-lowercase character.
    """
    if candidate["source"] == WB_NO_FILE:
        return "unknown (WB recorded no file)"
    base = candidate["source"].rsplit("/", 1)[-1]
    if not base.casefold().endswith((".cpp", ".c")):
        return f"{base} is a header: an inline body, defined with its class there"
    hits = source_index().get(base.casefold(), [])
    if hits:
        return hits[0].relative_to(ROOT).as_posix()
    stem = base.rsplit(".", 1)[0]
    split = sorted(path for name, paths in source_index().items()
                   if name.startswith(stem.casefold()) for path in paths
                   if len(path.stem) > len(stem) and not path.stem[len(stem)].islower()
                   and path.stem[:len(stem)].casefold() == stem.casefold())
    if split:
        first = split[0].relative_to(ROOT).as_posix()
        more = f" (+{len(split) - 1} more)" if len(split) > 1 else ""
        return f"no {base} yet; split unit(s) {first}{more}"
    return f"no {base} in Code/ yet"


def similar_candidates(claimed, claimed_ranges):
    """Unclaimed functions ranked by similarity to matched code (tools/similar.py).

    The lead is a matched neighbour's source: the body that taught the layout,
    inlined helper or idiom this one most likely needs. Like the anchored tier it
    carries no identity -- recovering the name is part of the job."""
    import similar
    out = []
    for c in similar.served_queue(claimed, claimed_ranges):
        best = c["neighbours"][0]
        out.append(dict(c, lead=f"{best['game']} {best['rva']} {best['name']}"))
    return out


# The default pick, every turn: wrong code already counted as progress first (gate
# debt, then what the link cannot place), then the identity and header debt that keeps
# units from linking, and only then new matches, which appear only on regressions now.
DEFAULT_ORDER = ("repair", "link", "data", "header", "identity",
                 "packet", "named", "harvest", "structural", "ghidra", "anchored")
EMPTY_LABEL = "default order"
DEBT_LABELS = ("gate-debt repair", "link-cycle repair", "data-identity debt", "class-header adoption",
               "code-identity debt", "link-stub closure", "TU consolidation", "TU approval", "TU evidence",
               "Microsoft-header migration", "DirectX SDK migration", "STLport 4.6 migration")


def selected_queue(tier, drifts, structural, ghidra_absent, anchored, named,
                   packets=(), similar=(), repair=(), link=(), wb=(), data=(), header=(), identity=()):
    queues = {
        "repair": ("gate-debt repair", repair),
        "link": ("link-cycle repair", link),
        "data": ("data-identity debt", data),
        "header": ("class-header adoption", header),
        "identity": ("code-identity debt", identity),
        "packet": ("Zero Hour work packet", packets),
        "named": ("reloc-named unclaimed function", named),
        "harvest": ("drift quick win", drifts),
        "structural": ("structural reconciliation", structural),
        "ghidra": ("Ghidra-anchored absent function", ghidra_absent),
        "anchored": ("string-anchored unclaimed function", anchored),
        "wb": ("WorldBuilder lead", wb),
        "similar": ("similar to matched code", similar),
    }
    if tier:
        return queues[tier]
    for name in DEFAULT_ORDER:
        label, candidates = queues[name]
        if candidates:
            return label, candidates
    return EMPTY_LABEL, []


DEBT_TIERS = ("repair", "link", "data", "header", "identity",
              "stubs", "consolidate", "tu-approval", "tu-evidence", "ms-headers", "dx", "stlport")
STRUCTURAL_TIERS = DEBT_TIERS[5:]          # repair_queue.STRUCTURAL_QUEUES
TIER_LABELS = dict(zip(DEBT_TIERS, DEBT_LABELS))
# Shares of the default pick among the queues after gate debt (always first: it is wrong
# code already counted as progress, and usually empty); they sum to 100. Every queue is
# a fallthrough, so a share only decides which queue a seat tries FIRST. The evidence
# (2026-10-25) and the reasoning behind each number:
#   * The old split (link 50, header 20, data 20, identity 10) gave the Phase 2 exit
#     test's structural work no default capacity: in the 48 h before, 1,060 commits
#     were naming and 67 were TU merges; Code/ grew from 23,278 to 23,292 files in a
#     week; 15,529 of 91,361 tu_map rows were approved and 22,045 proposed; and the
#     strict whole-program link still needed 1,810 stubs.
#   link 26        the census's LINKED/LINKING is the headline figure: still the largest
#                  share, but no longer half of every seat.
#   stubs 12       the exit test is a link with no stubs; 1,810 stubbed symbols, about
#                  1,580 of them class members (one class claim closes a group).
#   header 15      one definition per class is a prerequisite of both linking and
#                  merging (a rejected merge donor is usually a private class view);
#                  728 queued units.
#   consolidate 20 tu_skeleton --queue: 346 approved TUs a merge can shrink (2026-10-27,
#                  after the tu_map coverage work; 31 when this was 7), ~5,400 donor files.
#                  At 7 the fleet merged ~7 files an hour against ~85 commits; Code/ file
#                  count is the source-recovery figure, so it takes the second-largest share.
#                  Taken from link 4, stubs 3, data 2 and one each from the small tiers.
#   tu-approval 4  16,858 proposed code rows in ~1,640 TUs: approval feeds the merge queue.
#   tu-evidence 3  8,398 sources (2026-10-25) no tu_map row places at all, in unmapped
#                  address runs; the retail layouts (tools/tu_evidence.py) reach few of
#                  them, so a seat finds the anchor. Taken from tu-approval's 8.
#   data 8         2,229 data-identity keys, a link prerequisite (one name per datum),
#                  cut from 20 to 10, then 8, to pay for the structural tiers.
#   identity 4     844 code-identity keys, reported in shadow; halved from 10.
#   ms-headers 4   3,421 audited files (972 left 2026-10-28); mechanical, byte-gated,
#                  file-local.
#   dx 1           33 servable units when this was 4, none on 2026-10-28: a seat that
#                  draws it falls straight through. 1 keeps it tried early if the scan
#                  serves units again; the other 3 went to stlport.
#   stlport 3      repair_queue.py stlport (2026-10-28): 532 files, 1,504 trial rows,
#                  101,072 B that matched retail under STLport 4.6, of the 5,755
#                  `// stlport` units still compiled against 4.5.3 (retail linked 4.6).
#                  Mechanical, file-local and byte-gated like ms-headers, with about half
#                  its files, so a little less. Taken from dx.
# Naming is not a default tier (it never was): --wb and tools/name_lane.py serve it on
# request. BFME_TIER_WEIGHTS="link=30,stubs=15,..." overrides any subset; a tier at 0 is
# still tried, last.
TIER_WEIGHTS = {"link": 26, "stubs": 12, "header": 15, "consolidate": 20, "tu-approval": 4, "tu-evidence": 3,
                "data": 8, "identity": 4, "ms-headers": 4, "dx": 1, "stlport": 3}
BUILT = []                  # debt queues this run built, in order (lazy: tests read it)
_DEBT = {}


def tier_weights():
    weights = dict(TIER_WEIGHTS)
    for part in filter(None, os.environ.get("BFME_TIER_WEIGHTS", "").split(",")):
        name, _, value = part.partition("=")
        if name.strip() in weights and value.strip().isdigit():
            weights[name.strip()] = int(value)
    return weights


def debt_order(rng=None):
    """The queues in the order this pick tries them: repair, then every other queue of
    DEBT_TIERS (link, data, header, identity and the structural tiers) drawn without
    replacement by tier_weights() (a queue at weight 0 is still tried, last). Every
    queue after the first is a fallthrough: taken when the ones before it are empty or
    every item in them is claimed."""
    rng = rng or random.SystemRandom()
    weights = tier_weights()
    left = [name for name in DEBT_TIERS[1:] if weights.get(name, 0) > 0]
    order = ["repair"]
    while left:
        total = sum(weights[name] for name in left)
        cut = rng.uniform(0, total)
        for name in left:
            cut -= weights[name]
            if cut <= 0:
                break
        order.append(name)
        left.remove(name)
    return order + [name for name in DEBT_TIERS[1:] if name not in order]


def build_debt(name):
    """(items, note) of one debt queue, built at most once per run (BUILT records it).
    An absent input file skips the queue with a note (SKIPPED), never an exit."""
    if name not in _DEBT:
        BUILT.append(name)
        if name == "repair":
            _DEBT[name] = (repair_queue.all_repair_items(), "")
        elif name == "link":
            _DEBT[name] = repair_queue.link_items()
        elif name in STRUCTURAL_TIERS:             # each builder skips itself with a note
            _DEBT[name] = repair_queue.STRUCTURAL_QUEUES[name]()
            if not _DEBT[name][0] and "skipped" in _DEBT[name][1]:
                SKIPPED.append(f"{name}: {_DEBT[name][1]}")
        else:
            path, builder = repair_queue.DEBT_QUEUES[name]
            _DEBT[name] = builder()
            if not (repair_queue.ROOT / path).exists():
                SKIPPED.append(_DEBT[name][1])
    return _DEBT[name]


def prepare_debt(items, busy, args):
    """(pool, suppressed): one debt queue as the draw sees it -- live claims fenced out,
    sharded, a recorded dead end dropped and a standing deferral (blocked, attempted,
    abandoned) tagged `deferred_attempts`, so weighted_choice serves it only once
    nothing untried is left -- exactly as the new-match tiers are."""
    pool = apply_shard(without_busy(items, busy), args.shard)
    suppressed = 0
    if not args.include_logged:
        pool, suppressed = drop_logged(pool)
    annotate_attempts(pool)
    return pool, suppressed


def pick_debt(order, args, busy):
    """Draw from the first queue of ORDER that yields an untried candidate (claimed,
    with --claim), building each queue only when reached; only once every queue's
    untried work is empty or claimed, the deferred items (a standing blocked or
    attempted verdict) in the same order. Returns a dict: name, label, pool,
    candidate, acquired, tried (queues passed over: empty, all claimed or only
    deferred), suppressed."""
    tried, suppressed, deferred = [], 0, []
    for name in order:
        items, _ = build_debt(name)
        pool, dropped = prepare_debt(items, busy, args)
        suppressed += dropped
        fresh = [c for c in pool if not c.get("deferred_attempts")]
        if len(fresh) < len(pool):
            deferred.append((name, pool))
        if fresh:
            got = draw_debt(name, fresh, pool, args, tried, suppressed)
            if got:
                return got
        tried.append(name)
    for name, pool in deferred:
        got = draw_debt(name, pool, pool, args, tried, suppressed)
        if got:
            return got
    return {"name": None, "label": EMPTY_LABEL, "pool": [], "candidate": None, "acquired": [], "tried": tried,
            "suppressed": suppressed}


def draw_debt(name, draw, pool, args, tried, suppressed):
    """One draw (claimed, with --claim) from DRAW, a part of queue NAME's POOL; None
    when every candidate in it was claimed by a peer."""
    label = TIER_LABELS[name]
    candidate, acquired = claim_choice(draw, label) if args.claim else (weighted_choice(draw), [])
    if candidate is None:
        return None
    return {"name": name, "label": label, "pool": pool, "candidate": candidate, "acquired": acquired,
            "tried": list(tried), "suppressed": suppressed}


def scope_release_note(candidate, acquired):
    """How a scope claim without a `debt=` note ends: by hand, after the push."""
    scopes = [t for t in claim_targets(candidate) if isinstance(t, str)]
    if not acquired or not scopes or "debt=" in claim_note("", candidate):
        return None
    return ("claim: scope claims of link-cycle and structural work are not settled automatically; after your push run "
            f"python3 tools/claims.py release {' '.join(scopes)}")


def emit_debt(args, ledger, picked):
    """Print (or --json) the debt pick and what it passed over."""
    candidate, label, pool = picked["candidate"], picked["label"], picked["pool"]
    meta = {"pool": len(pool), "suppressed_logged": picked["suppressed"],
            "deferred_pool": sum(1 for c in pool if c.get("deferred_attempts")),
            "tiers_built": list(BUILT), "tiers_passed_over": picked["tried"],
            "shard": None if args.shard is None else {"index": args.shard[0], "count": args.shard[1]}}
    if args.json:
        if args.claim:
            meta["claimed"] = bool(picked["acquired"])
        print(json.dumps({"ledger": ledger, "tier": label, "skipped": SKIPPED,
                          "selection": candidate, "selection_meta": meta}, indent=2))
        return
    print(ledger)
    for line in SKIPPED:
        print(f"skipped {line}")
    if picked["tried"]:
        print("passed over (empty or every item claimed): " + ", ".join(TIER_LABELS[n] for n in picked["tried"]))
    if picked["suppressed"]:
        print(f"re_attempts: {picked['suppressed']} item(s) hidden as recorded dead ends (--include-logged to show)")
    note = deferred_note(pool)
    if note:
        print(note)
    if candidate is None:
        print(f"\nNo {TIER_LABELS.get(args.tier, label)} candidates remain.")
        return
    if picked["acquired"]:
        scopes = {claims.key_of(t): t for t in claim_targets(candidate) if isinstance(t, str)}
        print(f"claim: {', '.join(scopes.get(key) or claims.label(key) for key in picked['acquired'])} held on "
              "origin; release it if work is abandoned")
        hint = scope_release_note(candidate, picked["acquired"])
        if hint:
            print(hint)
    print()
    print_candidate(label, candidate, meta, pool)


def cluster_of(candidate, candidates):
    """Every queued candidate sharing this candidate's source file.

    The file is the real unit of work here, not the function. `./build.sh <file>`
    verifies a whole translation unit at once, a shared-header edit pays the
    host-wide gate once for the file rather than once per function, and the
    class layout an agent recovers to land one body is exactly what the next
    body in that file needs.

    It shows up in the outcomes: over the 1,000 commits ending 2038d3a0d, a
    drift candidate whose file saw no other row land had a 19.5% land rate;
    where ten or more siblings landed together it was 46.5%. Serving one
    function per session throws that away and hands the file to another agent.
    """
    same = [c for c in candidates if c["source"] == candidate["source"]]
    same.sort(key=lambda c: -yield_model.land_rate(
        c.get("size") or c.get("target_size") or 1))
    return same


def print_cluster(candidate, candidates, buildable=True):
    siblings = cluster_of(candidate, candidates)
    if len(siblings) < 2:
        return
    total = sum(c.get("size") or c.get("target_size") or 0 for c in siblings)
    print(f"\n  == the rest of {candidate['source']} ({len(siblings)} queued, "
          f"{total:,}B) ==")
    if buildable:
        print("  Take the whole file, not just the row above: recover the layout once, "
              f"verify siblings together with one `./build.sh {candidate['source']}`, "
              "commit each body separately.")
    else:  # a WB file path, not a Code/ unit: nothing for build.sh to take yet
        print("  Take the whole WB file, not just the row above: its class layout and "
              "callee names carry over; land each body into its Code/ home separately.")
    for sibling in siblings[:12]:
        size = sibling.get("size") or sibling.get("target_size") or 0
        marker = "->" if sibling is candidate else "  "
        print(f"   {marker} {size:>5}B  "
              f"{int(100 * yield_model.land_rate(size)):>2}% land  "
              f"{sibling['function'][:88]}"
              + ("  [wpo: likely unreproducible]" if unreproducible(sibling) else ""))
    if len(siblings) > 12:
        print(f"      ... and {len(siblings) - 12} more in this file")
    print("  If a shared header is involved, edit every dependent body first and "
          "pay the full gate once.")


def print_wb_candidate(candidate, indent="  "):
    """One WB-tier candidate: name, address, file, and what to run first."""
    now = (f"  (ledger: {candidate['kind']} {candidate['current_name']})"
           if candidate["current_name"] else f"  ({candidate['kind']})")
    print(f"{indent}{candidate['size']:>5}B  {candidate['function']}{now}")
    print(f"       {candidate['target_rva']}  WB file: {candidate['source']}"
          + (f"  class {candidate['wb_class']}" if candidate["wb_class"] else ""))
    print(f"       local source: {wb_local_source(candidate)}")
    line = stash_line(candidate)
    if line:
        print(line)
    for line in wb_lines(candidate)[:1]:
        print(line)
    _print_wpo(candidate)
    _print_boundary_verdicts(candidate)
    print(f"       start: {candidate['command']}")


def print_packet_candidate(candidate):
    print(f"  {candidate['size']:>5}B  {candidate['function']}")
    print(f"       {candidate['target_rva']} — Zero Hour's own body for this "
          f"address already agrees on {candidate['aligned_pct']}% of the "
          f"non-relocation bytes")
    if candidate.get("landability"):
        print(f"       landability: {landability.line(candidate['landability'])}")
    _print_stash(candidate)
    _print_boundary_verdicts(candidate)
    print(f"       start: read {candidate['packet']}, port {candidate['source']}")


def print_candidate(label, candidate, meta, candidates=()):
    print(f"== selected work: {label} (drawn from {meta['pool']}) ==")
    if label in DEBT_LABELS:
        what = candidate.get("check") or ("placed, not self-strict" if candidate.get("placed") else "not placed")
        print(f"  {candidate['size']:>5}B  {what}  {candidate['function']}")
        print(f"       {candidate.get('target_rva') or candidate.get('address') or '(no address)'} "
              f"in {candidate['source']}")
        print(f"       why: {candidate['why']}")
        if candidate.get("claim"):
            print(f"       scope: {' '.join(candidate['claim'])} (what --claim takes)")
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate.get('start') or 'fix it in ' + candidate['source']}; done when the pass "
              "test passes:")
        print(f"       pass test: {candidate['pass_test']}")
        if candidate.get("tier") in ("data", "header", "identity"):
            print("       done: only when the owning tool's verdict on fresh objects passes and retires the line "
                  f"from {candidate.get('baseline')} itself; the pre-commit hook refuses a commit that deletes "
                  "a line without that verdict (repair_queue.py verify-removed)")
        elif candidate.get("credit_note"):          # a structural tier: no register line, no bytes
            print(f"       credit: {candidate['credit_note']} (structural work: no register line retires; the "
                  "pass test is the owning tool's verdict)")
        else:
            print(f"       credit: {candidate['credit']:,} bytes (a repair counts: progress_v2 gate debt / "
                  "link series)")
        return
    if candidate.get("dest_basis"):
        print(f"  goes in: {candidate.get('dest') or '(no unit yet)'}  <- {candidate['dest_basis']}")
    if label == "WorldBuilder lead":
        print_wb_candidate(candidate)
        if candidate["kind"] in ("PLACEHOLDER", "PARTIAL"):
            print("       name it: write real C++ at its home, then "
                  "tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>")
        elif candidate["kind"] == "PIN_ONLY":
            print("       pinned but unrowed: write real C++ at its home, then "
                  "tools/add_match.py <real-name> <rva> <size> <source>")
        print_cluster(candidate, candidates, buildable=False)
        return
    if label == "Zero Hour work packet":
        print_packet_candidate(candidate)
        return
    if label == "reloc-named unclaimed function":
        print(f"  {candidate['size']:>5}B  {candidate['function']}")
        print(f"       {candidate['target_rva']} ({candidate['notes']}) — named by a "
              f"byte-true call in {candidate['source']}")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate['command']}")
        # No file cluster here: the whole point of this tier is that the body
        # has no source file yet, so there is no translation unit to drain and
        # nothing for `./build.sh <file>` to verify. The caller is a locality
        # hint, not the work.
        siblings = [c for c in candidates if c["source"] == candidate["source"]]
        if len(siblings) > 1:
            print(f"       {len(siblings) - 1} other unclaimed function(s) named "
                  f"by calls in that same file")
        return
    if label == "drift quick win":
        print(f"  {candidate['aligned_pct']:>3}% {candidate['drift_class']:<14} "
              f"{candidate['function']}")
        print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
              f"hint: {candidate['hint']}")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       fix the literal in source, then byte-verify: {candidate['command']}")
    elif label == "structural reconciliation":
        print(f"  {candidate['aligned_pct']:>3}% {candidate['size']:>5}B "
              f"{candidate['function']}")
        print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
              f"hint: {candidate['hint']}")
        for warning in candidate.get("warnings", ()):
            print(f"       warning: {warning}")
        shared = len(candidate.get("functions", ())) - 1
        if shared > 0:
            print(f"       {shared} other drifted name(s) claim this same address; "
                  f"the body decides which one it is")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate['command']}")
    elif label == "similar to matched code":
        print(f"  {candidate['similarity']:.3f} {candidate['size']:>5}B "
              f"{candidate['function']}  (anonymous — recovering the name is step 1)")
        print(f"       {candidate['target_rva']} resembles matched {candidate['lead']}")
        for lead in candidate["neighbours"]:
            print(f"         {lead['score']:.3f} {lead['game']} {lead['rva']} {lead['source']}")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate['command']}")
    elif label == "string-anchored unclaimed function":
        print(f"  {candidate['confidence']:<6} {candidate['size']:>5}B "
              f"{candidate['function']}  (anonymous — recovering the name is step 1)")
        print(f"       {candidate['target_rva']} anchored by {candidate['anchor']!r}")
        print(f"       that literal appears in ZH {candidate['zh_source']}"
              + (f" (+{candidate['alternates']} other file(s))"
                 if candidate['alternates'] else ""))
        print(f"       local source: {candidate['source']}")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate['command']}")
    else:
        anchors = ", ".join(repr(value) for value in candidate["anchors"][:3])
        print(f"  {candidate['confidence']:<6} {candidate['target_size']:>5}B "
              f"{candidate['function']}")
        print(f"       {candidate['source']} -> {candidate['target_rva']} "
              f"{candidate['ghidra_name']} ({len(candidate['anchors'])} anchor(s): "
              f"{anchors}; {candidate['alternates']} alternate(s))")
        _print_stash(candidate)
        _print_boundary_verdicts(candidate)
        print(f"       start: {candidate['command']}")
    print_cluster(candidate, candidates)


def print_ranked(args, ledger, drifts, structural, ghidra_meta, ghidra_absent,
                 suppressed=0, named=(), named_note="", structural_meta=None, wb=(),
                 packets=()):
    print("== 0. ledger health ==")
    print(f"  {ledger}")
    if suppressed:
        print(f"  re_attempts: {suppressed} candidate(s) hidden as already "
              f"investigated (--include-logged to show)")
    if args.tier == "wb":
        print_ranked_wb(args, wb)
        return
    if structural_meta and validator_note(structural_meta):
        print(f"  {validator_note(structural_meta)}")

    if args.tier in (None, "packet"):
        print(f"\n== P. Zero Hour work packets ({len(packets)}) ==")
        for candidate in packets[:args.limit]:
            print_packet_candidate(candidate)
        if args.tier == "packet":
            return

    if args.tier in (None, "named"):
        print(f"\n== 1. reloc-named unclaimed functions ({len(named)}) ==")
        print(f"  {named_note}")
        for candidate in named[:args.limit]:
            print(f"  {candidate['size']:>5}B  {candidate['function']}")
            print(f"       {candidate['target_rva']} named by a call in "
                  f"{candidate['source']} ({candidate['notes']})")
            _print_stash(candidate)
            _print_boundary_verdicts(candidate)
            print(f"       start: {candidate['command']}")

    if args.tier in (None, "harvest"):
        print(f"\n== 2. drift quick wins: literal-only diffs ({len(drifts)}) ==")
        for candidate in drifts[:args.limit]:
            print(f"  {candidate['aligned_pct']:>3}% {candidate['drift_class']:<14} "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            _print_wb(candidate)
            _print_boundary_verdicts(candidate)
            print("       fix the literal in source, then byte-verify: "
                  f"{candidate['command']}")

    if args.tier in (None, "structural"):
        shown = structural[:args.limit]
        print(f"\n== 3. structural reconciliation — manual RE ({len(structural)} "
              f"address(es); workflow: docs/structural.md) ==")
        for candidate in shown:
            shared = len(candidate.get("functions", ())) - 1
            print(f"  {candidate['aligned_pct']:>3}% {candidate['size']:>5}B "
                  f"{candidate['function']}"
                  + (f"  (+{shared} name(s) at this address)" if shared > 0 else ""))
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            _print_stash(candidate)
            _print_boundary_verdicts(candidate)
            print(f"       start: {candidate['command']}")

    if args.tier in (None, "ghidra"):
        shown = ghidra_absent[:args.limit]
        print(f"\n== 4. Ghidra-anchored absent functions ({len(ghidra_absent)}; "
              f"workflow: docs/structural.md) ==")
        print(f"  {ghidra_meta}")
        for candidate in shown:
            anchors = ", ".join(repr(value) for value in candidate["anchors"][:3])
            print(f"  {candidate['confidence']:<6} {candidate['target_size']:>5}B "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} -> {candidate['target_rva']} "
                  f"{candidate['ghidra_name']} ({len(candidate['anchors'])} anchor(s): "
                  f"{anchors}; {candidate['alternates']} alternate(s))")
            _print_stash(candidate)
            _print_boundary_verdicts(candidate)
            print(f"       start: {candidate['command']}")

    if args.tier in ("named", "structural", "ghidra"):
        return
    print("\n== 5. rest of the ladder ==")
    for command, why in POINTERS:
        print(f"  {command:<55} # {why}")


def print_ranked_wb(args, wb):
    """The WB tier, band by band, grouped by WB file (limit = files per band)."""
    for band, title in sorted(WB_BANDS.items()):
        members = [c for c in wb if c["band"] == band]
        files = {}
        for candidate in members:
            files.setdefault(candidate["source"], []).append(candidate)
        print(f"\n== WB band {band}: {title} ({len(members)} bodies in "
              f"{len(files)} WB file(s)) ==")
        for source, group in list(files.items())[:args.limit]:
            total = sum(c["size"] for c in group)
            print(f"\n  -- {source} ({len(group)} bodies, {total:,}B) --")
            for candidate in group[:args.limit]:
                print_wb_candidate(candidate, indent="  ")
            if len(group) > args.limit:
                print(f"      ... and {len(group) - args.limit} more in this file")


def wb_sizes(rows):
    """{rva: size}: the ledger's own extent where a row has one, else Ghidra's."""
    sizes = dict(_ghidra_sizes())
    for row in rows:
        if row.get("target_rva") and row.get("target_size"):
            try:
                sizes[int(row["target_rva"], 16)] = int(row["target_size"])
            except ValueError:
                pass
    return sizes


@claims.pick_snapshot()
def main():
    import build
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, default=10,
                    help="max items per section with --ranked (default 10)")
    ap.add_argument("--json", action="store_true",
                    help="machine-readable selected item (or full queues with --ranked)")
    ap.add_argument("--ranked", action="store_true",
                    help="show complete ranked queues for humans/debugging")
    ap.add_argument("--claim", action="store_true",
                    help="claim the selected item on origin before serving it (its class:/file: scope where it "
                         "names one, else its RVA); retry a raced selection")
    ap.add_argument("--tier",
                    choices=("repair", "link", "data", "header", "identity", "stubs", "consolidate",
                             "tu-approval", "tu-evidence", "ms-headers", "packet", "named", "harvest",
                             "structural", "ghidra", "anchored", "similar", "wb", "dx", "stlport"),
                    help="choose from only this task lane")
    ap.add_argument("--wb", action="store_const", const="wb", dest="tier",
                    help="shorthand for --tier wb: serve bodies by WorldBuilder name lead")
    ap.add_argument("--shard", type=parse_shard, metavar="INDEX/COUNT",
                    help="stable zero-based partition for concurrent workers")
    ap.add_argument("--big", action="store_true",
                    help="sort structural candidates by size (byte yield) instead of alignment")
    ap.add_argument("--include-logged", action="store_true",
                    help="keep candidates already recorded no-match in "
                         "reverse/re_attempts.log (they are dropped by default)")
    args = ap.parse_args()
    if args.claim and args.ranked:
        ap.error("--claim selects one candidate; omit --ranked")
    ledger = check_ledger()  # exit 2 happens in there; nothing below matters if red
    if args.tier == "dx":
        return serve_dx(args)
    global repair_queue
    import repair_queue  # after the health check: a corrupt ledger exits first
    # The debt queues first, lazily: each is built only when the weighted order reaches
    # it, and the new-match tiers below are computed only when every debt queue is empty
    # or claimed. --ranked builds everything (a human view).
    settled, debt_suppressed = False, 0
    if not args.ranked and (args.tier is None or args.tier in DEBT_TIERS):
        if args.claim:
            claims.settle(defer=True)    # rides on the claim push; release this checkout's landings (and finished scopes) origin/master holds
            settled = True
        picked = pick_debt(debt_order() if args.tier is None else [args.tier], args, busy_keys())
        if picked["candidate"] is not None or args.tier is not None:
            emit_debt(args, ledger, picked)
            return
        debt_suppressed = picked["suppressed"]
    # A new-match tier is computed only for the default pick or its own --tier, and
    # skips itself (missing_input) when its input is absent: --tier link never reads
    # the drift report.
    drifts = drift_quick_wins() if args.tier in (None, "harvest") else []
    # Every tier below asks "is this address still open work?", and a gen-dump
    # row answers yes: it pins retail's bytes and holds no source. That rule
    # lives in build.load_claim_rows and nowhere else -- deriving it here a
    # second time is how the queue went blind across the whole dump pass.
    claimed, claimed_names, claimed_ranges = set(), set(), []
    for row in build.load_claim_rows(counting_dumps=False, matched_only=False):
        if row["target_rva"]:
            start = int(row["target_rva"], 16)
            claimed.add(start)
            claimed_names.add(row["name"])
            if row.get("target_size"):
                claimed_ranges.append((start, start + int(row["target_size"])))
    structural = (structural_candidates(claimed, claimed_names, claimed_ranges,
                                        big=args.big)
                  if args.tier in (None, "structural") else [])
    if args.tier in (None, "named"):
        named, named_note = reloc_named_candidates(claimed, claimed_ranges)
    else:
        named, named_note = [], "reloc-named tier not requested"
    if args.tier in (None, "anchored"):
        anchored, anchored_note = anchored_candidates(
            claimed, claimed_names, claimed_ranges)
    else:
        anchored, anchored_note = [], "anchored tier not requested"
    similar_q = (similar_candidates(claimed, claimed_ranges)
                 if args.tier == "similar" else [])
    if args.tier in (None, "ghidra"):
        ghidra_absent, ghidra_meta = ghidra_absent_candidates(
            claimed, claimed_names)
    else:
        ghidra_absent, ghidra_meta = [], "Ghidra tier not requested"

    wb, wb_aside = [], 0
    if args.tier == "wb":
        every_row = build.load_claim_rows(counting_dumps=True, matched_only=False)
        wb = wb_candidates(claimed_ranges, wb_real_rvas(every_row), wb_sizes(every_row))

    # A `no-match` row is a finished investigation, not a pending task; serving
    # one again is pure rework. ~20% of the structural queue is in that state.
    suppressed = 0
    if not args.include_logged:
        named, dropped_named = drop_logged(named)
        drifts, dropped_drift = drop_logged(drifts)
        structural, dropped_structural = drop_logged(structural)
        ghidra_absent, dropped_ghidra = drop_logged(ghidra_absent)
        anchored, dropped_anchored = drop_logged(anchored)
        wb, dropped_wb = drop_logged(wb)
        similar_q, dropped_similar = drop_logged(similar_q)
        suppressed = (dropped_named + dropped_drift + dropped_structural
                      + dropped_ghidra + dropped_anchored + dropped_wb + dropped_similar)

    # Debt queues here only for --ranked; the pick drew from them above.
    # The structural queues are built for --ranked only on their own --tier: the merge
    # queue alone rebuilds the TU map and scans every donor's refusals (tens of seconds).
    shown = {name: build_debt(name) if args.ranked and args.tier == name
             or args.ranked and args.tier is None and name not in STRUCTURAL_TIERS
             else ([], f"not built in the full view: python3 tools/next_work.py --ranked --tier {name}"
                   if args.ranked and name in STRUCTURAL_TIERS else "")
             for name in DEBT_TIERS}
    busy = busy_keys()
    debt, debt_notes = {}, {}
    for name, (items, queue_note) in shown.items():
        debt[name], dropped = prepare_debt(items, busy, args) if items else ([], 0)
        debt_notes[name] = queue_note
        suppressed += dropped
    repair, link, link_note = debt.pop("repair"), debt.pop("link"), debt_notes["link"]
    named = without_busy(named, busy)
    drifts = without_busy(drifts, busy)
    structural = without_busy(structural, busy)
    ghidra_absent = without_busy(ghidra_absent, busy)
    anchored = without_busy(anchored, busy)
    wb = without_busy(wb, busy)
    similar_q = without_busy(similar_q, busy)

    # After the log filter, so one dead name cannot retire a whole address, and
    # before sharding, so every worker sees the same collapsed queue.
    structural, structural_meta = collapse_and_validate(structural)

    named = apply_shard(named, args.shard)
    drifts = apply_shard(drifts, args.shard)
    structural = apply_shard(structural, args.shard)
    ghidra_absent = apply_shard(ghidra_absent, args.shard)
    anchored = apply_shard(anchored, args.shard)
    wb = apply_shard(wb, args.shard)
    similar_q = apply_shard(similar_q, args.shard)
    for queue in (named, drifts, structural, ghidra_absent, anchored, wb, similar_q):
        annotate_attempts(queue)
        annotate_stashes(queue)
        annotate_wb(queue)
        annotate_wpo(queue)
    if wpo_detect is not None:
        wpo_detect.save_cache()
    for queue in (named, ghidra_absent, anchored):
        repair_queue.annotate_dest(queue)
    shard_meta = (None if args.shard is None else
                  {"index": args.shard[0], "count": args.shard[1]})

    # Ranked views show the full filtered queue, before the selection-only
    # landability band and default-tier preemption rules below.
    packets = (packet_candidates(claimed)
               if args.tier in (None, "packet") else [])
    packets = annotate_wpo(annotate_wb(without_busy(packets, busy)))
    annotate_attempts(packets)
    if wpo_detect is not None:
        wpo_detect.save_cache()
    repair_queue.annotate_dest(packets)
    # The packet tier carries its own boundary, so a logged verdict retires it
    # exactly as it does for every other lane. Without this the recommender
    # keeps serving packets already recorded not-convertible or no-boundary.
    if not args.include_logged:
        packets, dropped_packets = drop_logged(packets)
        suppressed += dropped_packets
    packets = apply_shard(packets, args.shard)

    if args.ranked and args.json:
        print(json.dumps({
            "ledger": ledger,
            "packets": packets,
            "named_meta": named_note, "reloc_named": named,
            "drift_quick_wins": drifts,
            "structural": structural,
            "ghidra_meta": ghidra_meta, "ghidra_absent": ghidra_absent,
            "anchored_meta": anchored_note, "anchored": anchored,
            "wb_leads": wb,
            "similar": similar_q,
            "repair": repair, "link_meta": link_note, "link": link,
            "data_identity_meta": debt_notes["data"], "data_identity": debt["data"],
            "class_header_meta": debt_notes["header"], "class_header": debt["header"],
            "code_identity_meta": debt_notes["identity"], "code_identity": debt["identity"],
            "structural_tiers": {name: {"meta": debt_notes[name], "items": debt[name]} for name in STRUCTURAL_TIERS},
            "structural_meta": structural_meta,
            "suppressed_logged": suppressed,
            "skipped": SKIPPED,
            "shard": shard_meta,
            "pointers": [cmd for cmd, _ in POINTERS],
        }, indent=2))
        return

    if args.ranked:
        for line in SKIPPED:
            print(f"skipped {line}")
        sections = (("repair", "R. gate-debt repairs", repair, ""), ("link", "L. link-cycle repairs", link, link_note),
                    ("data", "D. data-identity debt", debt["data"], debt_notes["data"]),
                    ("header", "H. class-header adoption", debt["header"], debt_notes["header"]),
                    ("identity", "I. code-identity debt", debt["identity"], debt_notes["identity"]),
                    *((name, f"P. {TIER_LABELS[name]}", debt[name], debt_notes[name]) for name in STRUCTURAL_TIERS))
        if args.tier in (None, *(name for name, _, _, _ in sections)):
            for name, title, queue, queue_note in sections:
                if args.tier not in (None, name):
                    continue
                print(f"== {title} ({len(queue)}) ==")
                if queue_note:
                    print(f"  {queue_note}")
                for candidate in queue[:args.limit]:
                    print(f"  {candidate['size']:>5}B {candidate.get('check', '')} "
                          f"{candidate.get('target_rva') or candidate.get('address', '')} "
                          f"{candidate['function'][:70]}  ({candidate['source']})"
                          + (f"  [claims {' '.join(candidate['claim'])}]" if candidate.get("claim") else ""))
                    _print_boundary_verdicts(candidate)
                    print(f"       pass test: {candidate['pass_test']}")
            print()
        print_ranked(args, ledger, drifts, structural, ghidra_meta,
                     ghidra_absent, suppressed, named, named_note, structural_meta, wb,
                     packets)
        return

    # The packet tier is the only one scored on landing evidence, so one band is
    # served at a time: a queue offering a `landable` body must not spend a seat
    # on an `unproven-boundary` one. See tools/landability.py.
    packets, set_aside = landability.band(packets)
    # ...and a band the inventory cannot place must not preempt the tiers that do
    # validate their addresses, or scoring the packets would make the default
    # pick worse than it was unscored. `--tier packet` still serves it.
    withheld = 0
    if args.tier is None and not landability.preempts(packets):
        withheld = len(packets)
        packets = []
    # One WB band at a time, like landability: a body that only needs its
    # name never waits behind an unrowed one.
    if args.tier == "wb":
        wb, wb_aside = wb_band(wb)
    label, candidates = selected_queue(args.tier, drifts, structural, ghidra_absent,
                                       anchored, named, packets, similar_q, repair=repair, link=link,
                                       wb=wb, data=debt["data"], header=debt["header"],
                                       identity=debt["identity"])
    if args.claim and not settled:
        claims.settle(defer=True)    # rides on the claim push; release this checkout's landings origin/master now holds
    suppressed += debt_suppressed
    candidate, acquired = (claim_choice(candidates, label) if args.claim else
                           (weighted_choice(candidates) if candidates else None, []))
    deferred = sum(1 for c in candidates if c.get("deferred_attempts"))
    meta = {"pool": len(candidates), "suppressed_logged": suppressed,
            "packets_set_aside": set_aside, "packets_withheld": withheld,
            "deferred_pool": deferred, "shard": shard_meta}
    if args.tier == "wb":
        meta["wb_set_aside"] = wb_aside
    if args.json:
        meta = dict(meta, cluster=[
            c["function"] for c in cluster_of(candidate, candidates)]) \
            if candidate else meta
        if args.claim:
            meta["claimed"] = bool(acquired)
        print(json.dumps({"ledger": ledger, "tier": label, "skipped": SKIPPED,
                          "selection": candidate, "selection_meta": meta}, indent=2))
        return
    print(ledger)
    for line in SKIPPED:
        print(f"skipped {line}")
    if suppressed:
        print(f"re_attempts: {suppressed} candidate(s) hidden as already "
              f"investigated (--include-logged to show)")
    if set_aside:
        print(f"landability: {set_aside} packet(s) set aside — serving the "
              f"best-evidenced band first")
    if withheld:
        print(f"landability: {withheld} packet(s) withheld from the default pick — "
              f"the inventory places none of them; use --tier packet to work one")
    if wb_aside:
        print(f"wb: {wb_aside} lead(s) in later bands set aside — serving bodies "
              f"that only need their name first")
    note = deferred_note(candidates)
    if note:
        print(note)
    if validator_note(structural_meta):
        print(validator_note(structural_meta))
    if candidate is None:
        if label == EMPTY_LABEL:
            print("\nNo candidates remain in the default order (repair, then link, stubs, class header, TU "
                  "approval and consolidation, data and code identity, Microsoft headers, DirectX, then new "
                  "matches).")
        else:
            print(f"\nNo {label} candidates remain.")
        print("Byte matching is complete: new matches appear only on regressions (./build.sh). "
              "Linking is the open work: python3 tools/link_rank.py")
        return
    if acquired:
        scopes = {claims.key_of(t): t for t in claim_targets(candidate) if isinstance(t, str)}
        print(f"claim: {', '.join(scopes.get(key) or claims.label(key) for key in acquired)} held on origin; "
              "release it if work is abandoned")
    print()
    print_candidate(label, candidate, meta, candidates)


if __name__ == "__main__":
    main()
