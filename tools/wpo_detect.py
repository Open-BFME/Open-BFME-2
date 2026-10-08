#!/usr/bin/env python3
"""Flag bodies tied to private register calling conventions plain C++ rarely reproduces.

MSVC gives a file-static function whose every caller it can see a private
convention: arguments arrive in eax, edx, ebx, esi or edi instead of on the
stack, and the callers load those registers just before the call. Separate
translation units, a different caller set or a missing inline decision all
lose it, so such bodies and their callers are expensive to land and are often
recorded `blocked` in reverse/re_attempts.log for exactly this reason.

For one game.dat function this reports:

  self    registers the body reads on entry before writing them, beyond what
          a standard convention passes (ecx for thiscall, ecx+edx for
          fastcall); ebp is ignored (EH funclets read the parent's frame)
  callee  each direct callee that does the same, with the registers its
          callers load right before the call ("likely unreproducible:
          <callee> reads <regs>")

Compiler and CRT helpers that take register arguments by design
(__EH_prolog, _chkstk/_alloca_probe, _ftol, MASM and vendored library
bodies) are skipped. Results are cached per RVA under build/wpo_detect/.
Advice only: a same-TU static with its real caller sometimes does reproduce
the convention (see the landed 0x0027900B), so this ranks work, never
refuses it.

    python3 tools/wpo_detect.py <rva|ledger name> [--json]
    python3 tools/wpo_detect.py --calibrate 400 [--seed 7]
"""
import argparse
import json
import os
import pickle
import random
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import retail_body as rb

VERSION = 1
CACHE = rb.ROOT / "build" / "wpo_detect" / "cache.json"
RE_ATTEMPTS = rb.ROOT / "reverse" / "re_attempts.log"
STANDARD = {"ecx"}
IGNORED = {"ebp"}
# Helpers that take register arguments by design.
HELPERS = {
    0x00629188: "__EH_prolog", 0x00629000: "__chkstk", 0x00628FA4: "__SEH_prolog",
    0x00628FDF: "__SEH_epilog", 0x00629228: "__ftol2", 0x00629BAB: "@__security_check_cookie@4",
}
HELPER_SOURCES = re.compile(r"^(?:vendor/|Code/masm_dumps/)|\.asm$|\.lib$")
LOOKBACK = 8
MAX_BODY = 60000
REG_WORD = r"(?:eax|ebx|esi|edi|edx)"
BLOCKED_REASON = re.compile(
    r"(?:custom|private|static|register|reg|nonstandard|ecx|eax|esi|edi|ebx|edx|stack|abi)"
    r"[- ](?:\w+[- ]){0,3}convention|no (?:standard|msvc) convention|convention no msvc"
    r"|regpass|register[- ]passed|(?:register|reg) (?:args|params|inputs|arguments)"
    r"|live[- ]in\b|live[- ]on[- ]entry|arrives in " + REG_WORD + r"|uses incoming " + REG_WORD +
    r"|(?:argument|object) in " + REG_WORD + r"\b", re.I)


# ----------------------------------------------------------------- ledger

def _ledger_sources():
    """{rva: source} for ledger rows, cached against functions.csv's mtime."""
    path = rb.CACHE_DIR / "ledger_sources.pkl"
    stamp = os.stat(rb.FUNCTIONS_CSV).st_mtime_ns
    if path.exists():
        try:
            with open(path, "rb") as fh:
                cached = pickle.load(fh)
            if cached.get("stamp") == stamp:
                return cached["sources"]
        except (OSError, pickle.UnpicklingError, EOFError):
            pass
    import csv
    sources = {}
    with open(rb.FUNCTIONS_CSV, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            try:
                sources.setdefault(int(row["target_rva"], 16), row["source"])
            except (ValueError, TypeError):
                continue
    rb.CACHE_DIR.mkdir(parents=True, exist_ok=True)
    with open(path, "wb") as fh:
        pickle.dump({"stamp": stamp, "sources": sources}, fh, protocol=pickle.HIGHEST_PROTOCOL)
    return sources


_SOURCES = None


def is_helper(rva):
    global _SOURCES
    if rva in HELPERS:
        return True
    if _SOURCES is None:
        _SOURCES = _ledger_sources()
    return bool(HELPER_SOURCES.search(_SOURCES.get(rva, "")))


# --------------------------------------------------------------- analysis

def nonstandard(live):
    """Registers live on entry that no standard convention passes."""
    allowed = set(STANDARD)
    if "ecx" in live:
        allowed.add("edx")          # __fastcall: ecx, edx
    return {reg: at for reg, at in live.items() if reg not in allowed and reg not in IGNORED}


_LIVE = {}


def entry_regs(rva):
    """{reg: first read rva} beyond the standard conventions, for a body."""
    if rva in _LIVE:
        return _LIVE[rva]
    size = rb.function_size(rva)
    result = {}
    if size and size <= MAX_BODY:
        insns = rb.disasm(rva, size)
        result = nonstandard(rb.live_in(insns, rb.table_targets(insns, rva, size)))
    _LIVE[rva] = result
    return result


def set_before(insns, index, regs):
    """Registers in regs that the caller writes in the few instructions before
    the call at insns[index] (stopping at an earlier call)."""
    found = set()
    for back in reversed(insns[max(0, index - LOOKBACK):index]):
        if back.mnem == "call":
            break
        for reg in back.writes:
            if reg in regs:
                found.add(reg)
    return found


def analyse(rva, size, data=None):
    """{"self": {reg: hexrva}, "callees": [{callee, regs, set_by_caller, at}]}.
    data: the body's bytes (tests); default game.dat."""
    insns = rb.disasm(rva, size, data=data)
    live = rb.live_in(insns, rb.table_targets(insns, rva, size, data=data))
    self_regs = nonstandard(live)
    callees = []
    seen = set()
    for i, insn in enumerate(insns):
        if insn.mnem not in ("call", "jmp") or insn.target is None:
            continue
        if rva <= insn.target < rva + size:
            continue
        target = rb.follow_jumps(insn.target) if data is None else insn.target
        if target in seen or is_helper(target):
            continue
        regs = entry_regs(target)
        if not regs:
            continue
        seen.add(target)
        loaded = set_before(insns, i, set(regs))
        callees.append({"callee": f"0x{target:08X}", "regs": sorted(regs),
                        "set_by_caller": sorted(loaded), "at": f"0x{insn.rva:08X}",
                        "tail": insn.mnem == "jmp"})
    return {"self": {reg: f"0x{at:08X}" for reg, at in sorted(self_regs.items())},
            "callees": callees}


def verdict(result):
    """'likely' when a register-passed call is visible, 'possible' when only
    the callee side is, None when the body looks standard."""
    if result["self"] or any(c["set_by_caller"] for c in result["callees"]):
        return "likely"
    if result["callees"]:
        return "possible"
    return None


def summary(result):
    """One line for queues, or None."""
    level = verdict(result)
    if level is None:
        return None
    parts = []
    if result["self"]:
        parts.append(f"body reads {','.join(result['self'])} on entry")
    for callee in result["callees"]:
        if callee["set_by_caller"] or level == "possible":
            parts.append(f"{callee['callee']} reads {','.join(callee['regs'])}")
    head = "likely unreproducible" if level == "likely" else "possibly unreproducible"
    return f"{head}: {'; '.join(parts[:3])}{' ...' if len(parts) > 3 else ''}"


# ------------------------------------------------------------------ cache

def _stamp():
    return [VERSION, os.stat(rb.GD_EXE).st_mtime_ns, os.stat(rb._gd_functions()).st_mtime_ns]


class Cache:
    """Per-RVA results under build/wpo_detect/cache.json, dropped when
    game.dat, the function index or this tool's VERSION change."""

    def __init__(self, path=CACHE):
        self.path = path
        self.stamp = _stamp()
        self.entries = {}
        self.dirty = False
        try:
            data = json.loads(path.read_text())
            if data.get("stamp") == self.stamp:
                self.entries = data.get("entries", {})
        except (OSError, ValueError):
            pass

    def get(self, rva, size=None):
        key = f"0x{rva:08X}"
        if key in self.entries:
            return self.entries[key]
        if size is None:
            size = rb.function_size(rva)
        if not size or size > MAX_BODY:
            result = {"self": {}, "callees": []}
        else:
            result = analyse(rva, size)
        self.entries[key] = result
        self.dirty = True
        return result

    def save(self):
        if not self.dirty:
            return
        self.path.parent.mkdir(parents=True, exist_ok=True)
        tmp = self.path.with_suffix(".tmp")
        tmp.write_text(json.dumps({"stamp": self.stamp, "entries": self.entries}))
        tmp.replace(self.path)
        self.dirty = False


_CACHE = None


def _cache():
    """The shared Cache, or None when game.dat or the function index cannot be
    read (then there is no advice, and still no error for the caller)."""
    global _CACHE
    if _CACHE is None:
        try:
            _CACHE = Cache()
        except OSError:
            _CACHE = False
    return _CACHE or None


def warning(rva, size=None):
    """Cached one-line warning for rva, or None. Never raises on a bad body."""
    cache = _cache()
    if cache is None:
        return None
    try:
        return summary(cache.get(rva, size))
    except Exception:  # advice must never break a queue
        return None


def is_cached(rva):
    cache = _cache()
    return cache is None or f"0x{rva:08X}" in cache.entries


def save_cache():
    if _CACHE:
        try:
            _CACHE.save()
        except OSError:
            pass


# ------------------------------------------------------------ calibration

def blocked_rvas(path=RE_ATTEMPTS):
    """RVAs recorded blocked/partial/attempted for a register-convention reason."""
    out = {}
    try:
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return out
    for line in lines:
        parts = line.split("\t")
        if len(parts) < 5 or parts[3] not in ("blocked", "partial", "attempted"):
            continue
        if BLOCKED_REASON.search(parts[4]):
            try:
                out[int(parts[1], 16)] = parts[4][:90]
            except ValueError:
                continue
    return out


def calibrate(n, seed, out=sys.stdout):
    blocked = blocked_rvas()
    hits = {"likely": 0, "possible": 0, None: 0}
    missed = []
    for rva, why in sorted(blocked.items()):
        size = rb.function_size(rva) or (rb.containing(rva) or (None, None))[1]
        if not size:
            continue
        level = verdict(analyse(rva, size))
        hits[level] += 1
        if level is None:
            missed.append((rva, why))
    total = sum(hits.values())
    print(f"re_attempts.log: {total} bodies logged for a register-convention reason", file=out)
    print(f"  likely {hits['likely']}  possible {hits['possible']}  silent {hits[None]}  "
          f"recall(likely) {hits['likely'] / max(total, 1):.2f}  "
          f"recall(any) {(hits['likely'] + hits['possible']) / max(total, 1):.2f}", file=out)
    for rva, why in missed[:6]:
        print(f"    silent 0x{rva:08X}: {why}", file=out)
    rows = [(int(r["target_rva"], 16), int(r["target_size"])) for r in rb.stream_matched()
            if r["source"].startswith("Code/") and not r["source"].startswith(("Code/gen_", "Code/masm"))
            and r["source"].endswith((".cpp", ".c"))]
    random.Random(seed).shuffle(rows)
    rows = rows[:n]
    levels = {"likely": [], "possible": [], None: []}
    for rva, size in rows:
        try:
            result = analyse(rva, size)
        except Exception as exc:
            print(f"skip 0x{rva:08X}: {exc}", file=sys.stderr)
            continue
        levels[verdict(result)].append((rva, summary(result)))
    count = sum(len(v) for v in levels.values())
    print(f"matched rows (seed {seed}): {count}; flagged likely {len(levels['likely'])} "
          f"({len(levels['likely']) / max(count, 1):.1%}), possible {len(levels['possible'])} "
          f"({len(levels['possible']) / max(count, 1):.1%})", file=out)
    for rva, line in levels["likely"][:8]:
        print(f"    0x{rva:08X}: {line}", file=out)
    return hits, levels


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", nargs="?", help="game.dat rva or ledger name")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--calibrate", type=int, metavar="N")
    parser.add_argument("--seed", type=int, default=7)
    args = parser.parse_args(argv)
    if args.calibrate:
        calibrate(args.calibrate, args.seed)
        return
    if not args.target:
        parser.error("target required")
    rva, row = rb.resolve_target(args.target)
    rva, size = rb.body_bounds(rva, row)
    result = analyse(rva, size)
    if args.json:
        print(json.dumps(dict(result, rva=f"0x{rva:08X}", verdict=verdict(result),
                              summary=summary(result)), indent=2))
        return
    print(f"wpo_detect 0x{rva:08X} ({size} bytes) {(row or {}).get('name', '(no ledger row)')}")
    if result["self"]:
        regs = ", ".join(f"{reg} (first read {at})" for reg, at in result["self"].items())
        print(f"  self:   reads {regs} before writing: a private register convention")
    for callee in result["callees"]:
        loaded = ", ".join(callee["set_by_caller"]) or "none of them right before the call"
        kind = "tail-jumps to" if callee["tail"] else "calls"
        print(f"  callee: {kind} {callee['callee']} at {callee['at']}, which reads "
              f"{', '.join(callee['regs'])} on entry; caller loads {loaded}")
    print(f"  => {summary(result) or 'standard conventions only'}")


if __name__ == "__main__":
    main()
