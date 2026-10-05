#!/usr/bin/env python3
"""Group unclaimed retail bodies into families that ONE conversion can pay for.

A family is a set of addresses whose bodies are the same function differing
only in constants. Converting one member proves the shape; the rest land in a
single add_match_batch pass. The whole question is what "the same" means, and
this tool offers four progressively looser normal forms:

  --exact   raw bytes. Finds only families with no relocations and no varying
            field at all.

  --disp    REL32 branch displacements zeroed. A call to a FIXED target encodes
            a DIFFERENT displacement from every address, so exact grouping
            structurally cannot see relocation-bearing families -- every member
            is its own singleton. When this was first measured, on a much
            earlier ledger, masking took the queue from 11 families and 51 rows
            to 161 families and 1,614 rows.

  --operand (default) every immediate AND displacement field zeroed, using
            capstone byte offsets so opcodes, modrm register selection and
            instruction lengths stay intact. `sub ecx,0x58` and `sub ecx,0x08`
            are one shape with one varying axis, but they are not byte-identical
            and --disp leaves each a singleton -- masking displacements does not
            mask IMMEDIATES.

  --mnemonic  the mnemonic sequence alone; operands, REGISTERS and instruction
            lengths all discarded. Merges families that --operand splits purely
            on which register the allocator picked, which is a difference the
            source usually does not contain.

Measured at 31cb443bf over the 7,183 bodies then passing the filters below:

              mode        families    rows    remaining singletons
              --exact          162     348                   6,731
              --disp           384   1,017                   6,062
              --operand        727   3,280                   3,799

and at 35930fea2, once --operand had been worked down to a flat queue whose
largest family held 13 members, --mnemonic restored a workable head (60, 35,
24, 23, 22 ...): 1,481 rows against 869 at --min-members 3.

Looser grouping trades precision for reach and WILL produce false families. An
immediate can be load-bearing in the source -- a 0 and a 1 need different C++ --
and under --mnemonic two members may differ in source outright, since `mov/mov/
ret` says almost nothing. That is acceptable and not a defect, but the looser
the mode the less a proven member says about its siblings: treat a --mnemonic
family as a HYPOTHESIS to look at, never as a claim. This decides only what is
worth LOOKING at; the byte gate still decides every member individually.

FILTERS, each of which exists because omitting it cost a run:
  * only unclaimed Code/gen_asm/ dump rows -- gen_small and gen_uw own theirs;
  * drop rows whose address carries a REAL (not address-derived) symbols.csv
    pin: those are tgrid territory;
  * drop ghidra=Unwind@ rows: compiler unwind residue, not function bodies;
  * require the byte AFTER the row to be 0xCC, so a PREFIX of a longer function
    cannot pass as a whole one;
  * require the body to end in a ret or a jmp, which excludes padding-terminated
    dead code;
  * EXCLUDE PREVIOUSLY-ATTEMPTED ADDRESSES ONLY AFTER GROUPING. Excluding them
    first splits a partially-attempted family into two apparently distinct
    groups -- that is exactly how 0x001EEAE0 and 0x001F35C0 were reported as
    two families of 6 and 7 when they were one family of 7;
  * drop a whole family if any member carries a `refuted` or `blocked` verdict:
    a refutation refutes the SHAPE, so the siblings are dead too;
  * drop bodies that call _atexit -- their source needs a function-local static
    of class type, and MSVC numbers those destructor helpers `_$E<n>` PER
    TRANSLATION UNIT, so the second such TU in the image always collides with
    the first on a name-global consistency check. See
    registers_a_local_static(); it has cost three landings so far.

Usage:
  python3 tools/family_scan.py [--exact|--disp|--operand|--mnemonic]
                              [--min-size 8] [--max-size 160] [--out FILE]
                              [--wide]

SCOPE. By default this scans only Code/gen_asm/ ledger rows, the one pool
whose boundaries the dump pass cut at int3 padding with a return-or-jump
terminal. The Ghidra inventory's function starts are a second, weaker source
of boundary leads -- inventory-derived heuristic leads, not proven boundaries
-- and the default scan never consults them, which is why a ledger with
almost no gen_asm rows reports almost no families.

  --wide additionally scans Ghidra-inventory function starts whose whole
  extent the ledger does not already overlap at any status. This is OPT-IN
  because an inventory start carries NO identity: the FUN_ address it names
  holds no source and no name, so a --wide family is a conversion lead, never
  a row. Do not turn these bodies into functions.csv rows without the normal
  per-body identity evidence (symbols, xrefs, string anchors) AND per-body
  extent verification through the byte gate.

  A --wide body must pass everything the default pool passes -- real-pin,
  Unwind, _atexit, refuted-shape and attempted-member exclusions -- PLUS the
  heuristic-lead checks on the inventory extent itself: the extent decodes
  end to end, the FINAL DECODED instruction (not the final byte) is a ret or
  jmp, no decoded int3 run hides inside the body, and the end has same-source
  corroboration -- either int3 padding follows (as for dump rows) or the next
  byte is itself an inventory start, i.e. the inventory abuts the next
  function against this one with no padding between them. An abutting next
  start is same-source corroboration, NOT independent proof: it comes from
  the same inventory that proposed the extent, and Ghidra splits CAN end one
  extent exactly where the next start sits, so a prefix of a longer function
  can land on another start and adjacency alone cannot rule that out. The
  --wide checks are no stricter than the dump-row checks and prove nothing
  about identity or extent on their own. Measured on 3,000 offered extents,
  ~98% abutted code (overwhelmingly prologue bytes: 55, B8, 56, 8B) -- an
  observed same-source rate, not a guarantee, recorded only to explain why
  requiring padding would blind the path to nearly the whole pool.
  Raw gaps between inventory starts are never candidates: every --wide body
  starts where the inventory says a function starts.
"""
import argparse
import bisect
import collections
import csv
import io
import re
import sys
from pathlib import Path

from boundary_validator import MIN_PAD_RUN

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build

ROOT = Path(__file__).resolve().parent.parent
ADDRESS_DERIVED = re.compile(
    r"Gen_?[0-9A-Fa-f]{8}|gen_?[0-9A-Fa-f]{8}|Rva_?[0-9A-Fa-f]{8}|\?[bdj]_", re.I)


def mask_disp(body):
    """Zero the 4-byte displacement of every E8/E9 near branch."""
    out = bytearray(body)
    i = 0
    while i < len(out) - 4:
        if out[i] in (0xE8, 0xE9):
            out[i + 1:i + 5] = b"\0" * 4
            i += 5
        else:
            i += 1
    return bytes(out)


def mask_operands(body, md):
    """Zero every immediate and displacement field. None if it does not decode
    cleanly end to end -- a body we cannot decode is one we cannot group."""
    out = bytearray(body)
    covered = 0
    for insn in md.disasm(body, 0):
        enc = insn.encoding
        if enc.imm_size:
            lo = insn.address + enc.imm_offset
            out[lo:lo + enc.imm_size] = b"\0" * enc.imm_size
        if enc.disp_size:
            lo = insn.address + enc.disp_offset
            out[lo:lo + enc.disp_size] = b"\0" * enc.disp_size
        covered += insn.size
    return bytes(out) if covered == len(body) else None


def mask_mnemonics(body, md):
    """The MNEMONIC SEQUENCE alone -- operands, registers and lengths discarded.

    One step looser again than --operand. Two bodies share this form iff they
    perform the same operations in the same order, whatever registers the
    allocator happened to pick and whatever the constants were. It merges
    families that --operand splits purely on register choice, which is a
    difference the SOURCE usually does not contain.

    This is the loosest form offered and by far the most false-positive prone:
    `mov/mov/ret` says almost nothing. Treat a family found only here as a
    HYPOTHESIS to look at, never as a claim -- and note that a proven member
    gives less leverage over its siblings than in the tighter modes, because the
    siblings may genuinely differ in source.
    """
    names, covered = [], 0
    for insn in md.disasm(body, 0):
        names.append(insn.mnemonic)
        covered += insn.size
    return ("\n".join(names)).encode("utf-8") if covered == len(body) else None


def ends_in_return_or_jump(body, md):
    """Check the final decoded instruction, not its last operand byte.

    `ret 4` ends in 0x00, and direct jumps end in their displacement, so the
    default scan's last-byte test cannot see them; conversely an immediate
    ending in 0xC3 is not a return. Require complete decoding: padding after
    a truncated instruction is not proof. Used by the --wide path, where the
    inventory extent -- not a hand-cut dump row -- is the boundary claim.
    This is a candidate filter, not a replacement for identity proof.
    """
    last = None
    covered = 0
    for insn in md.disasm(body, 0):
        last = insn
        covered += insn.size
    return (last is not None and covered == len(body)
            and last.mnemonic in ("ret", "jmp"))


def has_interior_pad_run(body, md, run=MIN_PAD_RUN):
    """True if a decoded int3 run sits inside the body with code after it.

    Decode-aware: only 0xCC bytes that decode as int3 instructions count, so
    an immediate or displacement such as mov eax,0xCCCCCCxx is NOT padding.
    A body spanning padding into a second function is two boundaries, not
    one, so the inventory extent it was served under is stale and the body is
    not a candidate. Threshold is boundary_validator.MIN_PAD_RUN.

    Undecodable bodies are refused by the separate terminal check.
    """
    try:
        insns = list(md.disasm(body, 0))
    except Exception:
        return False
    if not insns or sum(i.size for i in insns) != len(body):
        return False
    run_len = 0
    run_end = 0
    for insn in insns:
        is_pad = (insn.size == 1 and insn.bytes == b"\xcc"
                  and insn.mnemonic == "int3")
        if is_pad:
            run_len += 1
            run_end = insn.address + 1
        else:
            if run_len >= run and run_end < len(body):
                return True
            run_len = 0
    return run_len >= run and run_end < len(body)


def load_real_pins():
    pins = set()
    with io.open(ROOT / "reverse" / "symbols.csv", encoding="utf-8",
                 errors="replace") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) < 2 or ADDRESS_DERIVED.search(row[0]):
                continue
            try:
                pins.add(int(row[1], 16))
            except ValueError:
                pass
    return pins


DEAD_VERDICTS = ("refuted", "blocked")


def load_attempted():
    """Two sets, because a prior attempt means two different things.

    `seen` is every address the log mentions. Dropping those members but KEEPING
    the family is right after a `converted` verdict: the siblings that did not
    land are still worth doing, and dropping the family instead would hide them.

    `dead` is addresses whose row carried a `refuted` or `blocked` verdict. There
    the whole family is finished, because a family is ONE function and a
    refutation refutes the shape, not the address. Keeping it alive re-queues the
    same shape under a NEW ANCHOR as soon as the logged members are skipped --
    which is exactly what happened: three families totalling 36 rows resurfaced
    at the top of the queue, one of them the local-static guard shape that had
    already been backed out TWICE, and all three were confirmed byte-identical in
    normal form to the shapes they re-anchored from.
    """
    seen, dead = set(), set()
    with io.open(ROOT / "reverse" / "re_attempts.log", encoding="utf-8",
                 errors="replace") as fh:
        for line in fh:
            fields = line.split("\t")
            verdict = fields[3].strip().lower() if len(fields) > 3 else ""
            addresses = {int(m.group(1), 16)
                         for m in re.finditer(r"0x([0-9A-Fa-f]{8})", line)}
            seen |= addresses
            if verdict in DEAD_VERDICTS:
                dead |= addresses
    return seen, dead


ATEXIT_RVA = 0x006291F8          # BFME2 _atexit, per reverse/symbols.csv


def registers_a_local_static(body, rva):
    """True if the body calls _atexit -- i.e. its source needs a function-local
    static of class type.

    Such a TU is currently UNCONVERTIBLE, and not for any reason visible in its
    bytes. MSVC names the destructor helper for each function-local static
    `_$E<n>`, numbered sequentially FROM THE START OF THE TRANSLATION UNIT, so
    the second such TU in the image reuses _$E4, _$E6, _$E12 ... and
    verify_dir32_consistency -- which is keyed on symbol NAME across the whole
    image -- reports them as one symbol at several addresses.

    This has now cost three separate landings (19 rows, then 7, then 6), and the
    first two times it was recorded as a property of the SHAPE, which is why the
    refuted-family exclusion above could not catch the third: those were local
    static GUARDS and the third was local static INITIALISERS, a different
    mnemonic sequence and a different normal form. TWO COLLIDING TUs NEED NOT
    SHARE A SINGLE BYTE, so the filter has to key on the CONSTRUCT, and the call
    to _atexit is what makes the construct visible from the outside.

    Remove this filter once verify_dir32_consistency scopes compiler-local
    symbols per-TU, or once the _$E family is whitelisted with that reasoning.
    """
    for i in range(len(body) - 4):
        if body[i] == 0xE8:
            target = rva + i + 5 + int.from_bytes(body[i + 1:i + 5], "little", signed=True)
            if target == ATEXIT_RVA:
                return True
    return False


def candidates(min_size, max_size, real_pins):
    with io.open(ROOT / "reverse" / "functions.csv", encoding="utf-8") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) != 7:
                continue
            name, _, rva_s, size_s, src, _, notes = row
            if not src.startswith("Code/gen_asm/"):
                continue
            size = int(size_s)
            if not (min_size <= size <= max_size) or "Unwind@" in notes:
                continue
            rva = int(rva_s, 16)
            if rva not in real_pins:
                yield name, rva, size


def iter_ghidra_rows():
    """Stream (rva, size, name) for every well-formed inventory row.

    Narrow-filtering generator: retains nothing. Callers apply size/source
    filters and retain only eligible candidate records (see
    load_wide_inventory), per the repo rule against loading the inventory
    wholesale.
    """
    with io.open(ROOT / "reverse" / "ghidra_functions.csv", encoding="utf-8",
                 errors="replace") as fh:
        for row in csv.DictReader(fh):
            try:
                rva, size = int(row["rva"], 16), int(row["size"])
            except (KeyError, ValueError, TypeError):
                continue
            yield rva, size, row.get("name", "") or ""


def load_wide_inventory(min_size, max_size):
    """Two streaming passes; retains only eligible leads + corroboration.

    Pass 1 streams the inventory with the narrow size filter and retains only
    in-range, positive-size candidate records, counting total rows offered.
    Pass 2 re-streams and retains only the candidate END addresses that are
    themselves inventory starts (abutment corroboration). The abutting-start
    set is same-source corroboration, not independent proof -- see SCOPE.
    Returns (candidates, total_rows, corroborated_ends).
    """
    candidates, total, ends = {}, 0, set()
    for rva, size, name in iter_ghidra_rows():
        total += 1
        if size <= 0 or not (min_size <= size <= max_size):
            continue
        candidates[rva] = (size, name)
        ends.add(rva + size)
    corroborated = set()
    if ends:
        for rva, _size, _name in iter_ghidra_rows():
            if rva in ends:
                corroborated.add(rva)
                if len(corroborated) == len(ends):
                    break
    return candidates, total, corroborated


def iter_ledger_intervals():
    """Stream (rva, size) for every ledger row with a parseable target.

    Narrow-filtering generator: retains nothing. Malformed or empty sizes
    fall back to 1 byte so a start-equality claim still excludes; a zero-size
    row must never read as covering nothing.
    """
    with io.open(ROOT / "reverse" / "functions.csv", encoding="utf-8",
                 errors="replace") as fh:
        for row in csv.DictReader(fh):
            try:
                rva = int(row["target_rva"], 16)
            except (KeyError, ValueError, TypeError):
                continue
            try:
                size = int(row["target_size"])
            except (KeyError, ValueError, TypeError):
                size = 1
            if size <= 0:
                size = 1
            yield rva, size


def ledger_overlapped_starts(candidates):
    """Candidate starts whose whole extent overlaps a ledger interval.

    Streams the ledger once with narrow filtering to the candidate windows:
    retains only the sorted candidate windows and the overlapped-start marks,
    never the whole ledger. Overlap mirrors BoundaryValidator.check_end
    (spans-function-start): [rva, rva+size) vs [l, l+ls), adjacency allowed.
    """
    if not candidates:
        return set()
    starts = sorted(candidates)
    ends = {s: s + candidates[s][0] for s in starts}
    cmax = max(candidates[s][0] for s in starts)
    overlapped = set()
    for lva, lsize in iter_ledger_intervals():
        lend = lva + lsize
        # Any overlapping candidate starts inside (lva - cmax, lend);
        # adjacency (== on either edge) is allowed, hence strict < both ways.
        lo = bisect.bisect_right(starts, lva - cmax)
        hi = bisect.bisect_left(starts, lend)
        for s in starts[lo:hi]:
            if s not in overlapped and lva < ends[s]:
                overlapped.add(s)
        if len(overlapped) == len(starts):
            break
    return overlapped


def wide_candidates(min_size, max_size, real_pins, claimed, inventory):
    """Inventory starts free of ledger overlap, in size range.

    `claimed` is the overlapped/excluded start set the caller computed by
    streaming the ledger against THESE candidate windows (see
    ledger_overlapped_starts) -- never a wholesale ledger load. A candidate
    is yielded only when its whole [rva, rva+size) avoids every ledger
    interval; adjacency (candidate end == ledger start or vice versa) is
    allowed. Yields (name, rva, size). The name is a provenance label only
    -- a FUN_ address carries no identity, and several inventory names are
    guesses -- so grouping must never treat a shared name as a shared
    function. Real pins stay excluded (tgrid territory) and Unwind residue
    stays excluded (compiler output, not function bodies), exactly as on the
    default path. Raw gaps are never yielded: membership requires an
    inventory start.
    """
    excluded = set(claimed or ())
    for rva, (size, name) in inventory.items():
        if not (min_size <= size <= max_size):
            continue
        if rva in excluded or rva in real_pins:
            continue
        if "Unwind" in (name or ""):
            continue
        yield name or ("FUN_%08X" % rva), rva, size


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--exact", action="store_const", dest="mode", const="exact")
    g.add_argument("--disp", action="store_const", dest="mode", const="disp")
    g.add_argument("--operand", action="store_const", dest="mode", const="operand")
    g.add_argument("--mnemonic", action="store_const", dest="mode", const="mnemonic")
    ap.add_argument("--min-members", type=int, default=2)
    ap.add_argument("--min-size", type=int, default=8)
    ap.add_argument("--max-size", type=int, default=160)
    ap.add_argument("--out", type=Path)
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--wide", action="store_true",
                    help="also scan Ghidra-inventory starts the ledger never "
                         "claimed: boundaries without identities (see SCOPE)")
    ap.set_defaults(mode="operand")
    args = ap.parse_args()

    md = None
    if args.mode in ("operand", "mnemonic") or args.wide:
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True

    real_pins = load_real_pins()
    attempted, dead = load_attempted()

    work = [(name, rva, size, False)
            for name, rva, size
            in candidates(args.min_size, args.max_size, real_pins)]
    wide_total = wide_offered = 0
    corroborated = set()
    if args.wide:
        # Two streaming passes retain only in-range leads plus the end
        # addresses the same inventory corroborates; one ledger pass retains
        # only candidate starts overlapped by a ledger interval. Nothing here
        # retains either whole table.
        inventory, wide_total, corroborated = load_wide_inventory(
            args.min_size, args.max_size)
        overlapped = ledger_overlapped_starts(inventory)
        wide = list(wide_candidates(args.min_size, args.max_size,
                                    real_pins, overlapped, inventory))
        wide_offered = len(wide)
        work.extend((name, rva, size, True) for name, rva, size in wide)

    groups = collections.defaultdict(list)
    scanned = undecoded = local_statics = wide_pad = wide_unproven = 0
    starts = set(corroborated) if args.wide else set()
    for name, rva, size, from_wide in work:
        try:
            window = build.read_target_bytes(rva, size + 1)
        except Exception:
            continue
        if len(window) != size + 1:
            continue
        if not from_wide and window[size] != 0xCC:
            continue                       # must END at padding
        body = window[:size]
        if from_wide:
            # The inventory extent is a heuristic lead, checked no harder
            # than a hand-cut dump row: a stale extent spanning a decoded
            # int3 run into the next function, one ending in a byte that
            # merely LOOKS like a return, or one whose end has same-source
            # corroboration from NEITHER padding NOR an abutting next start,
            # is not a candidate. Corroboration is not proof (Ghidra splits
            # can abut exactly), so per-body extent verification still applies
            # at conversion time.
            if window[size] != 0xCC and (rva + size) not in starts:
                wide_unproven += 1
                continue
            if has_interior_pad_run(body, md):
                wide_pad += 1
                continue
            if not ends_in_return_or_jump(body, md):
                undecoded += 1
                continue
        elif body[-1] not in (0xC3, 0xC2, 0xE9, 0xEB) and body[-2:-1] != b"\xff":
            continue                       # must end in a ret or a jmp
        if registers_a_local_static(body, rva):
            local_statics += 1
            continue
        scanned += 1
        if args.mode == "exact":
            key = body
        elif args.mode == "disp":
            key = mask_disp(body)
        elif args.mode == "operand":
            key = mask_operands(body, md)
            if key is None:
                undecoded += 1
                continue
        else:
            key = mask_mnemonics(body, md)
            if key is None:
                undecoded += 1
                continue
        groups[key].append((rva, size, name))

    families = []
    refuted = 0
    for key, members in groups.items():
        if len(members) < args.min_members:
            continue
        # A refutation refutes the SHAPE, so one dead member kills the family.
        if any(m[0] in dead for m in members):
            refuted += 1
            continue
        fresh = [m for m in members if m[0] not in attempted]   # AFTER grouping
        if fresh:
            families.append((len(members), len(fresh), key, members, fresh))
    families.sort(reverse=True, key=lambda f: f[1])
    singletons = sum(1 for m in groups.values()
                     if len(m) == 1 and m[0][0] not in attempted)

    if args.wide:
        print("wide pool: %d inventory rows scanned, %d heuristic leads "
              "offered (ledger-overlap-free, pin-free, Unwind-free, in range)"
              % (wide_total, wide_offered))
        print("wide extents refused as stale (decoded interior int3 run): %d"
              % wide_pad)
        print("wide extents refused as uncorroborated ends: %d" % wide_unproven)
    print("mode=%s  bodies scanned: %d%s" % (
        args.mode, scanned,
        "  (undecodable, skipped: %d)" % undecoded if undecoded else ""))
    print("families >= %d with unattempted members: %d"
          % (args.min_members, len(families)))
    print("unattempted rows reachable: %d" % sum(f[1] for f in families))
    print("families dropped as refuted/blocked shapes: %d" % refuted)
    print("bodies skipped as function-local-static TUs: %d" % local_statics)
    print("unattempted singletons (regex-sweep territory): %d" % singletons)

    if args.out:
        with io.open(args.out, "w", encoding="utf-8") as out:
            for total, fresh_n, key, members, fresh in families:
                out.write("=== %d members (%d unattempted), %dB, anchor 0x%08X\n"
                          "normal: %s\nmembers: %s\n\n"
                          % (total, fresh_n, members[0][1], fresh[0][0],
                             key.hex() if args.mode != "mnemonic"
                             else key.decode("utf-8").replace(chr(10), " "),
                             " ".join("0x%08X" % a for a, _, _ in fresh)))
        print("written: %s" % args.out)

    print("\nTOP %d:" % args.top)
    for total, fresh_n, _, members, fresh in families[:args.top]:
        print("  0x%08X  %3dB  %4d fresh / %4d total"
              % (fresh[0][0], members[0][1], fresh_n, total))


if __name__ == "__main__":
    main()
