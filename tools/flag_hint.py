#!/usr/bin/env python3
"""Predict compiler flags from byte tells in a retail body, and diff the source.

Reads one game.dat function (ledger extent, else gd_functions.jsonl) and looks
for code-generation tells that only some flag sets produce, each with the
offset of the instruction that shows it:

  sse         xmm-register arithmetic                        => /arch:SSE
  cmov        cmovcc                                         => /arch:SSE
  gs_cookie   call to @__security_check_cookie@4             => /GS
  eh_frame    C++ EH frame (inline fs:[0] link or __EH_prolog,
              handler stub `mov eax, FuncInfo; jmp`)         => /EHsc (or /GX)
  eh_prolog   frame set up by calling __EH_prolog             => /O1 (or /Os)
  eh_inline   EH frame linked inline instead                 => not /O1
  add_one     `add/sub reg, 1` (P4 tuning avoids inc/dec)    => /G7
  add_one_mem `add/sub [mem], 1`                             => /G7
  imul_small  `imul r, r, k` for a small k (level*12)        => /G7
              (/arch:SSE2 tunes like /G7, and /Od also emits add 1)

Disabled by calibration (shown with --all-tells): sse2 and fcomi (never seen),
ebp_frame (=> /Oy-, 16%), this_spill (=> /Od, 13%), byte_push (`mov r8; push
r32` => /G7, 76%), inc_dec (=> not /G7, 28%).

The flags compared are the ones tools/build.py really passes for the row's
source (retail_body.build_flags): its `// cl:` line with the region's codegen
flags applied by tools/flag_defaults.py, which decides /O, /arch and /G for
most Code/ units whatever the line says.

Every tell was calibrated against matched rows whose sources' flags are known
(`--calibrate N`): precision is how often a body showing the tell comes from a
source that has the flag. Tells under 90% precision are disabled and never
printed unless --all-tells is given; rerun the calibration after codegen
lessons change and update CALIBRATION below.

The diff against those flags is advice only: a matched row can carry a flag
its bytes do not need, and a tell's absence proves nothing. A flag the region
already gives is fixed by the region, not by the `// cl:` line; a different
one needs a recorded override (tools/flag_defaults.py propose).

    python3 tools/flag_hint.py <rva|ledger name> [--source FILE] [--all-tells] [--json]
    python3 tools/flag_hint.py --calibrate 400 [--seed 7]
"""
import argparse
import json
import random
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import retail_body as rb

SECURITY_CHECK_COOKIE = 0x00629BAB
EH_PROLOG = 0x00629188
SEH_PROLOG = 0x00628FA4
CHKSTK = 0x00629000

# (tell, flag group a source must carry for the tell to be "right", direction)
# direction "+" suggests adding the flag; "-" suggests the source should NOT
# carry it.
TELLS = {
    "sse": ("/arch:SSE", "+"),
    "sse2": ("/arch:SSE2", "+"),
    "fcomi": ("/arch:SSE", "+"),
    "cmov": ("/arch:SSE", "+"),
    "gs_cookie": ("/GS", "+"),
    "eh_frame": ("/EHsc", "+"),
    "eh_prolog": ("/O1", "+"),
    "eh_inline": ("/O1", "-"),
    "ebp_frame": ("/Oy-", "+"),
    "this_spill": ("/Od", "+"),
    "byte_push": ("/G7", "+"),
    "add_one": ("/G7", "+"),
    "add_one_mem": ("/G7", "+"),
    "imul_small": ("/G7", "+"),
    "inc_dec": ("/G7", "-"),
}
# Measured by `--calibrate` (see the commit that last changed this table):
# tell -> (precision, fires, sample size). Tells below MIN_PRECISION are
# disabled. Rerun and update when the tells or the ledger move materially.
MIN_PRECISION = 0.90
CALIBRATION = {          # --calibrate 6000 --seed 11, 2026-10-08, build flags
    "sse": (0.99, 382, 6000),
    "cmov": (1.00, 13, 6000),
    "gs_cookie": (1.00, 25, 6000),
    "eh_frame": (0.95, 925, 6000),
    "eh_prolog": (1.00, 825, 6000),
    "eh_inline": (1.00, 100, 6000),
    "add_one": (1.00, 108, 6000),
    "add_one_mem": (1.00, 43, 6000),
    "imul_small": (0.93, 105, 6000),
    # disabled: under MIN_PRECISION, or never seen in the sample
    "ebp_frame": (0.16, 894, 6000),
    "this_spill": (0.13, 186, 6000),
    "byte_push": (0.76, 25, 6000),
    "inc_dec": (0.28, 640, 6000),
    "sse2": (None, 0, 6000),
    "fcomi": (None, 0, 6000),
}
DISABLED = {tell for tell, (prec, _, _) in CALIBRATION.items()
            if prec is None or prec < MIN_PRECISION}


def flag_holds(flag, eff):
    """Whether effective flags eff carry the flag group a tell points at."""
    if flag == "/arch:SSE":
        return eff["arch"] in ("SSE", "SSE2")
    if flag == "/arch:SSE2":
        return eff["arch"] == "SSE2"
    if flag == "/GS":
        return eff["GS"]
    if flag == "/EHsc":
        return eff["EH"] is not None
    if flag == "/O1":
        return eff["opt"] == "/O1" or eff.get("favor", "").lower() == "/os"
    if flag == "/Oy-":
        return eff["Oy-"] or eff["opt"] == "/Od"
    if flag == "/Od":
        return eff["opt"] == "/Od"
    if flag == "/G7":
        # P4 tuning: /arch:SSE2 tunes like /G7, and /Od never uses inc/dec.
        return eff["G7"] or eff["arch"] == "SSE2" or eff["opt"] == "/Od"
    raise ValueError(flag)


# ------------------------------------------------------------------- tells

def _handler_is_cxx(handler):
    """A C++ EH handler stub is `mov eax, FuncInfo; jmp __CxxFrameHandler`."""
    if handler is None or not rb.in_text(handler):
        return False
    raw = rb.read_bytes(handler, 10)
    return len(raw) == 10 and raw[0] == 0xB8 and raw[5] == 0xE9


def find_tells(insns, rva, handler_is_cxx=_handler_is_cxx):
    """[(tell, insn rva, text)] for one body's instructions."""
    out = []
    seen = set()

    def add(tell, insn, text=None):
        if tell in seen:
            return
        seen.add(tell)
        out.append((tell, insn.rva, text or f"{insn.mnem} {insn.ops}".strip()))

    calls = {insn.target for insn in insns if insn.mnem == "call"}
    has_fs = any("fs:[0]" in insn.ops for insn in insns)
    eh = seh = False
    for i, insn in enumerate(insns):
        prev = insns[i - 1] if i else None
        if insn.mnem == "call" and insn.target == EH_PROLOG and prev is not None \
                and prev.mnem == "mov" and prev.ops.startswith("eax, 0x") \
                and handler_is_cxx(prev.imm - rb.IMAGE_BASE if prev.imm else None):
            eh = True
            add("eh_frame", insn, f"{prev.mnem} {prev.ops}; call __EH_prolog")
            add("eh_prolog", insn, "call __EH_prolog")
        if insn.mnem == "call" and insn.target == SEH_PROLOG:
            seh = True
        if insn.mnem == "push" and insn.imm is not None and has_fs and i + 1 < len(insns) \
                and insns[i - 1].mnem == "push" and insns[i - 1].imm == -1 if i else False:
            handler = insn.imm - rb.IMAGE_BASE
            if handler_is_cxx(handler):
                eh = True
                add("eh_frame", insn, f"push -1; push {insn.ops}; fs:[0] link")
                add("eh_inline", insn, "EH frame linked inline, not via __EH_prolog")
            else:
                seh = True
    for i, insn in enumerate(insns):
        m, ops = insn.mnem, insn.ops
        if "xmm" in ops:
            add("sse", insn)
            if m.endswith(("sd", "pd")) and m not in ("movsd",) or m.startswith(("cvtsd", "cvttsd", "cvtsi2sd", "cvtss2sd")) \
                    or (m == "movsd" and "xmm" in ops):
                add("sse2", insn)
        if m in ("fcomip", "fucomip", "fcomi", "fucomi"):
            add("fcomi", insn)
        if m.startswith("cmov"):
            add("cmov", insn)
        if m == "call" and insn.target == SECURITY_CHECK_COOKIE:
            add("gs_cookie", insn, "call @__security_check_cookie@4")
        if m == "mov" and ops.startswith("dword ptr [ebp - ") and ops.endswith("], ecx") \
                and i < 12:
            add("this_spill", insn)
        parts = ops.split(", ")
        if m in ("add", "sub") and len(parts) == 2 and parts[1] in ("1", "-1", "0xffffffff"):
            add("add_one" if parts[0] in rb.GPRS else "add_one_mem", insn)
        if m in ("inc", "dec") and ops in rb.GPRS:
            add("inc_dec", insn)
        if m == "imul" and ops.count(",") == 2 and insn.imm is not None and 2 < abs(insn.imm) <= 64:
            add("imul_small", insn)
        if m == "mov" and ops[:2] in ("al", "bl", "cl", "dl") and ops[2:4] == ", ":
            full = rb.REG_PARTS[ops[:2]][0]
            for nxt in insns[i + 1:i + 4]:
                if nxt.mnem == "push" and nxt.ops == full:
                    add("byte_push", insn, f"{m} {ops} ... push {full}")
                    break
                if full in nxt.writes:
                    break
    if len(insns) >= 2 and insns[0].mnem == "push" and insns[0].ops == "ebp" \
            and insns[1].mnem == "mov" and insns[1].ops == "ebp, esp" \
            and not (eh or seh or has_fs or CHKSTK in calls):
        add("ebp_frame", insns[0], "push ebp; mov ebp, esp")
    return out


def body_tells(rva, size):
    insns = rb.disasm(rva, size)
    return find_tells(insns, rva)


# -------------------------------------------------------------------- diff

def diff_lines(tells, tokens, all_tells=False):
    """Advice lines comparing tells against the source's effective flags."""
    eff = rb.effective_flags(tokens or [])
    by_flag = defaultdict(list)
    for tell, at, _ in tells:
        if tell in DISABLED and not all_tells:
            continue
        flag, direction = TELLS[tell]
        by_flag[(flag, direction)].append(f"{tell}@0x{at:X}")
    lines = []
    for (flag, direction), evidence in sorted(by_flag.items()):
        has = flag_holds(flag, eff)
        why = ", ".join(evidence)
        if direction == "+":
            mark = "=" if has else "+"
            verb = "source has it" if has else "source lacks it: try adding"
            if has and flag == "/G7" and not eff["G7"]:
                verb = "source covers it (/arch:SSE2 or /Od)"
        else:
            mark = "-" if has else "="
            verb = "source carries it: try removing" if has else "source agrees (absent)"
        lines.append(f"  {mark} {flag:<10} {verb}  [{why}]")
    return lines


def report(target, source=None, all_tells=False, as_json=False):
    rva, row = rb.resolve_target(target)
    rva, size = rb.body_bounds(rva, row)
    tells = body_tells(rva, size)
    source = source or (row or {}).get("source")
    tokens = rb.build_flags(rb.ROOT / source) if source else None
    shown = [t for t in tells if all_tells or t[0] not in DISABLED]
    if as_json:
        return json.dumps({
            "rva": f"0x{rva:08X}", "size": size, "row": (row or {}).get("name"),
            "source": source, "cl": tokens,
            "tells": [{"tell": t, "offset": f"0x{a - rva:X}", "rva": f"0x{a:08X}",
                       "evidence": e, "flag": TELLS[t][0], "direction": TELLS[t][1],
                       "precision": CALIBRATION.get(t, (None,))[0]} for t, a, e in shown],
            "diff": diff_lines(tells, tokens, all_tells) if tokens is not None else [],
        }, indent=2)
    out = [f"flag_hint 0x{rva:08X} ({size} bytes) {(row or {}).get('name', '(no ledger row)')}"]
    if source:
        out.append(f"  source: {source}  builds with: {rb.describe_flags(tokens) if tokens is not None else '(unreadable)'}")
    if not shown:
        out.append("  no calibrated tells in this body (absence proves nothing)")
    for tell, at, evidence in shown:
        flag, direction = TELLS[tell]
        prec = CALIBRATION.get(tell)
        quality = f"p={prec[0]:.2f}" if prec else "uncalibrated"
        off = "disabled " if tell in DISABLED else ""
        out.append(f"  +0x{at - rva:04X} {tell:<10} {direction}{flag:<10} {quality} {off}{evidence}")
    if tokens is not None and shown:
        out.append("  diff vs the flags build.py passes (advice, never a gate):")
        out.extend(diff_lines(tells, tokens, all_tells))
    return "\n".join(out)


# ------------------------------------------------------------- calibration

def calibration_rows(n, seed):
    """A seeded sample of matched rows from real C/C++ sources with known flags."""
    rows = []
    for row in rb.stream_matched():
        source = row["source"]
        if not source.startswith("Code/") or source.startswith(("Code/gen_", "Code/masm_dumps")):
            continue
        if not source.endswith((".cpp", ".c")):
            continue
        rows.append((row["target_rva"], row["target_size"], source))
    rng = random.Random(seed)
    rng.shuffle(rows)
    return rows[:n]


def calibrate(n, seed, out=sys.stdout):
    fires = Counter()
    right = Counter()
    has_flag = Counter()
    found_flag = Counter()
    flags_of = {}
    sample = calibration_rows(n, seed)
    for rva_text, size_text, source in sample:
        if source not in flags_of:
            flags_of[source] = rb.effective_flags(rb.build_flags(rb.ROOT / source) or [])
        eff = flags_of[source]
        try:
            tells = {t for t, _, _ in body_tells(int(rva_text, 16), int(size_text))}
        except Exception as exc:  # a body capstone cannot walk is skipped, not fatal
            print(f"skip {rva_text}: {exc}", file=sys.stderr)
            continue
        for tell, (flag, direction) in TELLS.items():
            holds = flag_holds(flag, eff)
            want = holds if direction == "+" else not holds
            if want:
                has_flag[tell] += 1
            if tell in tells:
                fires[tell] += 1
                if want:
                    right[tell] += 1
                    found_flag[tell] += 1
    print(f"calibration over {len(sample)} matched rows (seed {seed})", file=out)
    print(f"  {'tell':<11}{'flag':<12}{'fires':>6}{'prec':>7}{'recall':>8}  verdict", file=out)
    result = {}
    for tell, (flag, direction) in TELLS.items():
        prec = right[tell] / fires[tell] if fires[tell] else None
        recall = found_flag[tell] / has_flag[tell] if has_flag[tell] else None
        verdict = ("keep" if prec is not None and prec >= MIN_PRECISION and fires[tell] >= 5
                   else "drop")
        result[tell] = (prec, fires[tell], recall, verdict)
        print(f"  {tell:<11}{direction + flag:<12}{fires[tell]:>6}"
              f"{'' if prec is None else f'{prec:.2f}':>7}"
              f"{'' if recall is None else f'{recall:.2f}':>8}  {verdict}", file=out)
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", nargs="?", help="game.dat rva or ledger name")
    parser.add_argument("--source", help="compare against the flags this file builds with (default: the row's source)")
    parser.add_argument("--all-tells", action="store_true", help="also show tells disabled by calibration")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--calibrate", type=int, metavar="N", help="measure each tell over N matched rows")
    parser.add_argument("--seed", type=int, default=7)
    args = parser.parse_args(argv)
    if args.calibrate:
        calibrate(args.calibrate, args.seed)
        return
    if not args.target:
        parser.error("target required")
    print(report(args.target, args.source, args.all_tells, args.json))


if __name__ == "__main__":
    main()
