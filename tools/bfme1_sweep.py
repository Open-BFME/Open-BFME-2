#!/usr/bin/env python3
"""Find BFME 1 source files whose bodies are byte-identical in BFME 2's game.dat.

BFME 1 and BFME 2 are the same SAGE engine built with the same MSVC 7.1
toolchain, so a translation unit Open-BFME-1 already converted frequently emits
a function body that appears verbatim in game.dat. Open-BFME-1's ledger holds
tens of thousands of such bodies; this sweep finds the ones game.dat still has
no source for, and serves each donor FILE as a work packet, because copying the
file across is the whole conversion.

  scan      compare lotrbfme.exe against game.dat   -> build/bfme1_sweep/match.json
  ranked    the donor queue, best first
  packets   write one work packet per donor file    -> build/bfme1_sweep/packets/
  show      print one donor file's packet to stdout
  land      copy, pin, add_match and build one donor file (reverts on failure)

SCOPE: byte-exact transfers only. The BFME1-verbatim ports already in this
repo's history -- getBrightness (0x002E4A47), hasGotOnline, getRemainingAmmo --
are SOURCE-verbatim and byte-DIVERGENT: their BFME1 bodies are three to six
bytes longer and only 15-31 of ~90-105 bytes agree. No binary comparison can
find those, and this tool does not try; they belong to a compile-based sweep
like tools/zh_sweep.py. What is here is the population a copy alone lands.

Both images have a STRIPPED .reloc directory, so unlike zh_sweep.py -- which
reads DIR32/REL32 sites out of a COFF object's relocation table -- there is no
relocation table to read and the volatile bytes have to be derived from the
instruction stream:

  REL32   a four-byte field behind E8/E9 or 0F 80..0F 8F whose decoded target
          lands in .text in BOTH images
  DIR32   a four-byte dword whose value lands inside [ImageBase, +SizeOfImage)
          in BOTH images

One unexplained differing byte rejects a placement. The check on that rule is
the sweep's own output: 2,837 of its 4,331 unique placements land on an address
this repo had already matched independently, at exactly the claimed RVA and
size. Watch that number -- `scan` prints it and refuses the run if it falls --
because a drop means the mask or the explainer broke, not that the donors
moved. The remaining 1,443 placements, 161,585 bytes, are the queue.

A placement proves identical CODE, which is not identity. Two separate hazards
get their own tier rather than a footnote: a body the compiler folded inside
lotrbfme.exe carries several BFME1 names and picking one is a guess (T3), and a
DIR32 pointing at a different string literal on each side says the two bodies
are not the same function at all (T4).
"""
import argparse
import bisect
import csv
import json
import re
import shutil
import struct
import subprocess
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = build.ROOT
BFME1 = ROOT / "reference" / "open-bfme-1"
BFME1_EXE = BFME1 / "inputs" / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"
BFME1_LEDGER = BFME1 / "targets" / "game" / "reverse" / "functions.csv"
BFME2_LEDGER = ROOT / "reverse" / "functions.csv"
BFME2_SYMBOLS = ROOT / "reverse" / "symbols.csv"
BFME1_SYMBOLS = BFME1 / "targets" / "game" / "reverse" / "symbols.csv"
OUT_DIR = ROOT / "build" / "bfme1_sweep"
MATCH_JSON = OUT_DIR / "match.json"
# Scratch, not tracked. A packet is derived from match.json and the live
# ledger, `show` prints one in under a second, and rows land continuously --
# four hundred committed packets would be stale by the end of the day. `packets`
# exists for a fleet that wants them on disk, not for the repository.
PACKET_DIR = OUT_DIR / "packets"

# Under this a body is a stub whose bytes occur all over .text. zh_sweep.py uses
# 24 against compiled COMDATs; 16 is workable here because both sides come from
# a ledger row with a proven boundary, so a short body still has a real extent.
MIN_FUNC = 16
# A needle shorter than this matches so much of .text that every placement it
# proposes has to be re-rejected by the explainer, which is the slow half.
MIN_NEEDLE = 6
# How many BFME1 .text occurrences of a needle to count before concluding the
# donor body is ICF-folded. Two is the answer; the rest is for the packet.
FANOUT_CAP = 8
# How many windows one donor's needle may propose before the donor is called
# ambiguous and dropped. Reaching it means the needle is too common to identify
# anything; the sweep never reports a capped search as a unique placement.
PLACEMENT_CAP = 4096
# A DIR32 target only counts as string evidence when it really is one.
MIN_STRING = 3

# nbench/BYTEmark ships no permission grant of any kind -- see AGENTS.md, which
# refuses it on the merits. Its donors are found and scored like any other and
# then held out of the served queue.
REFUSED_PREFIXES = {
    "Code/Libraries/Source/Benchmark/":
        "nbench/BYTEmark carries no permission grant (AGENTS.md refuses it on the merits)",
}
# Permitted, but the sources may not be vendored here until the grant statement
# is mirrored into this repo. docs/matching.md has the scope.
FLAGGED_SUBSTRINGS = {
    "GameSpy": "GameSpy SDK is permitted but needs PROVENANCE.txt mirrored here first",
}

GEN_SOURCE_PREFIXES = ("Code/gen_small", "Code/gen_asm", "Code/masm_dumps",
                       "game/gen_small", "game/gen_asm", "game/masm_dumps")
# .githooks/pre-commit refuses a NEW source anywhere else under Code/. Wave 1
# landed Code/stlport/CodecvtWideNarrow.cpp clean and could not commit it.
PLACEMENT_ROOTS = ("Code/GameEngine/", "Code/GameEngineDevice/", "Code/Libraries/",
                   "Code/gen_small/", "Code/gen_asm/", "Code/masm_dumps/")
LIFT_RE = re.compile(r"__declspec\s*\(\s*naked\s*\)|__emit")
# Tiers that are held out of the served queue. Each one is a gate this repo's
# hooks enforce, found by landing a wave into it rather than by reading the hook.
HELD_COPY_TIERS = {"L", "P", "S"}
COPY_ORDER = {"A": 0, "B": 1, "C": 2, "D": 3, "S": 4, "P": 5, "L": 6}
INCLUDE_RE = re.compile(r'^\s*#\s*include\s*([<"])([^">]+)[">]', re.M)
CL_RE = re.compile(r"^// cl:(.*)$", re.M)


def bfme2_source_path(donor_source):
    """Map BFME 1's current ``game/`` tree into BFME 2's ``Code/`` tree."""
    if donor_source.startswith("game/"):
        return "Code/" + donor_source[len("game/"):]
    return donor_source


class Image:
    """One retail PE, with the reads this sweep needs and nothing else."""

    def __init__(self, path):
        self.path = path
        self.data = path.read_bytes()
        self.sections = build.pe_sections(self.data)
        optional = build.u32(self.data, 0x3C) + 4 + 20
        self.base = build.u32(self.data, optional + 28)
        self.image_size = build.u32(self.data, optional + 56)
        code = next(s for s in self.sections if s["name"].lower().startswith(".text"))
        self.text_rva = code["rva"]
        start = code["raw_pointer"]
        self.text = self.data[start : start + code["raw_size"]]

    def body(self, rva, size):
        try:
            return build.read_pe_bytes(self.data, self.sections, rva, size)
        except ValueError:
            return None

    def in_image(self, va):
        return self.base <= va < self.base + self.image_size

    def in_text(self, rva):
        return self.text_rva <= rva < self.text_rva + len(self.text)

    def cstring(self, va, limit=256):
        """The NUL-terminated printable string at a virtual address, or None."""
        try:
            offset = build.rva_to_file_offset(self.sections, va - self.base)
        except ValueError:
            return None
        end = self.data.find(b"\0", offset, offset + limit)
        if end < 0:
            return None
        text = self.data[offset:end]
        if len(text) < MIN_STRING or not all(32 <= byte < 127 or byte in (9, 10, 13) for byte in text):
            return None
        return text


def rel32_lands_in_text(body, field, rva, image):
    """Whether a candidate call/jmp displacement reaches this image's .text.

    An E8/E9 byte inside DATA is not an opcode: the immediate of
    `mov DWORD PTR [eax],0x0112e8b8`, an entry in a switch jump table, a
    character in a string. Claiming a rel32 there costs more than the bogus
    field itself -- it blocks the DIR32 window that really holds the
    relocation, and every later claim shifts with it, so a byte-identical body
    reads as a near miss. The target is the test: a call that leaves .text was
    never a call.

    Without an RVA the test cannot run and the claim stands, which is the
    behaviour every caller had before.
    """
    if rva is None:
        return True
    target = (rva + field + 4 + struct.unpack_from("<i", body, field)[0]) & 0xFFFFFFFF
    return image.in_text(target)


def volatile_fields(body, image, rva=None):
    """The relocation slots in a body, as {offset: kind}, by one forward walk.

    The REL32 pass runs first and steps over each field it claims, so a
    displacement byte that happens to read as E8 cannot open a second field
    inside the first, and -- given `rva` -- a displacement that lands outside
    .text does not open one at all. The DIR32 pass then fills the gaps: any
    four-byte window not already spoken for whose value is an address in this
    image.

    One walk, one set of field boundaries -- `volatile_mask` and `explain` both
    read this rather than each deciding for itself where a field starts. That
    matters: re-deriving the window around a differing byte lets a misaligned
    dword straddling an operand and the next opcode read as an address on both
    sides and explain away a difference that is really there.
    """
    size = len(body)
    fields = {}
    claimed = bytearray(size)
    index = 0
    while index < size:
        byte = body[index]
        if (byte in (0xE8, 0xE9) and index + 5 <= size
                and rel32_lands_in_text(body, index + 1, rva, image)):
            fields[index + 1] = "rel32"
            claimed[index + 1 : index + 5] = b"\1" * 4
            index += 5
            continue
        if (byte == 0x0F and index + 6 <= size and 0x80 <= body[index + 1] <= 0x8F
                and rel32_lands_in_text(body, index + 2, rva, image)):
            fields[index + 2] = "rel32"
            claimed[index + 2 : index + 6] = b"\1" * 4
            index += 6
            continue
        index += 1
    for index in range(max(0, size - 3)):
        if any(claimed[index : index + 4]):
            continue
        if image.in_image(struct.unpack_from("<I", body, index)[0]):
            fields[index] = "dir32"
            claimed[index : index + 4] = b"\1" * 4
    return fields


def mask_from(fields, size):
    """A byte mask over `size` bytes covering each four-byte field."""
    mask = bytearray(size)
    for offset in fields:
        mask[offset : offset + 4] = b"\1" * 4
    return bytes(mask)


def volatile_mask(body, image, rva=None):
    """Byte positions two different images cannot be expected to agree on."""
    return mask_from(volatile_fields(body, image, rva), len(body))


def clear_runs(mask):
    """(offset, length) of every unmasked run, longest first."""
    runs = []
    start = None
    for index, flagged in enumerate(mask):
        if not flagged and start is None:
            start = index
        elif flagged and start is not None:
            runs.append((start, index - start))
            start = None
    if start is not None:
        runs.append((start, len(mask) - start))
    return sorted(runs, key=lambda run: -run[1])


def occurrences(haystack, needle, cap=None):
    """Offsets of `needle`, stopping after `cap` of them.

    A truncated search must never be read as a unique placement -- that is the
    one error this sweep cannot make -- so callers treat "returned `cap`
    offsets" as *at least* `cap`, which is ambiguous, rather than as all of
    them. Uncapped is still available and is what the ICF fan-out count wants
    for small caps, but the main search caps: a six-byte needle of common
    opcodes occurs tens of thousands of times in eight megabytes of .text, and
    checking every one of those windows costs more than the donor is worth.
    """
    found = []
    position = haystack.find(needle)
    while position >= 0:
        found.append(position)
        if cap is not None and len(found) >= cap:
            break
        position = haystack.find(needle, position + 1)
    return found


def explain(donor, donor_fields, donor_runs, window, donor_rva, target_rva,
            donor_image, target_image):
    """Account for every differing byte as a relocation, or refuse the window.

    The donor's forward walk decides WHERE the fields are. It is anchored to an
    instruction stream the two bodies share, so it is the reliable half; the
    target only has to agree that the value sitting there is relocation-shaped
    -- inside the image for a DIR32, inside .text for a REL32.

    Deriving the map independently on both sides and requiring them to agree
    was too fragile to be right. The DIR32 pass claims any unclaimed four-byte
    window addressing the image, scanning forward, so a differing field VALUE
    shifts which windows get claimed and two otherwise-identical bodies end up
    disagreeing about where the fields are. Three bodies in
    LocaleCodePageQueries.c were rejected at 96-98% for one slot holding
    KERNEL32!GetLocaleInfoA on the donor side and kernel32!GetLocaleInfoA on
    the target side -- the same import, a textbook DIR32, refused because the
    target's walk never claimed that offset. Over 4,000 donors the change
    raises unique placements 523 -> 555 and free bytes 15,137 -> 18,348, and
    the CONTROL -- placements reproducing a boundary this repo matched
    independently -- rises 340 -> 360. More of what is already proven, not more
    noise: ambiguity stays flat at 366 -> 367.

    This is not the ad-hoc widening that was removed earlier. That one searched
    for SOME four-byte window around each differing byte, which let a misaligned
    dword straddling an operand and the next opcode read as an address on both
    sides. Field boundaries still come from one forward walk over real
    instruction boundaries; only the target's confirmation of a field is
    relaxed, and every byte outside those fields must still match exactly.

    The refusal is done first and in whole slices. Every byte outside a donor
    relocation field has to agree, and comparing those runs as slices is a
    memcmp per run rather than a Python loop per byte -- which is what this
    costs, because a short needle proposes hundreds of windows and nearly all
    of them die here.

    `donor_fields` and `donor_runs` are the same for every window of one donor,
    so they are derived once by the caller.

    Returns (unexplained, dir32, rel32). `dir32` entries are
    (offset, donor_va, target_va); `rel32` entries are
    (offset, donor_call_rva, target_call_rva).
    """
    for start, length in donor_runs:
        if donor[start : start + length] != window[start : start + length]:
            return 1, [], []

    dir32 = []
    rel32 = []
    unexplained = 0
    for offset, kind in donor_fields.items():
        donor_slot = donor[offset : offset + 4]
        target_slot = window[offset : offset + 4]
        if kind == "rel32":
            donor_call = (donor_rva + offset + 4 + struct.unpack("<i", donor_slot)[0]) & 0xFFFFFFFF
            target_call = (target_rva + offset + 4 + struct.unpack("<i", target_slot)[0]) & 0xFFFFFFFF
            if donor_image.in_text(donor_call) and target_image.in_text(target_call):
                rel32.append((offset, donor_call, target_call))
                continue
        else:
            donor_va = struct.unpack("<I", donor_slot)[0]
            target_va = struct.unpack("<I", target_slot)[0]
            if donor_image.in_image(donor_va) and target_image.in_image(target_va):
                dir32.append((offset, donor_va, target_va))
                continue
        # The value is not relocation-shaped on both sides, so the slot is
        # ordinary code again and has to match byte for byte like any other.
        unexplained += sum(1 for index in range(4) if donor_slot[index] != target_slot[index])
    return unexplained, sorted(dir32), sorted(rel32)


# ------------------------------------------------------------------ near misses
#
# A near candidate is an UNVERIFIED identity claim, which is why it never enters
# `ranked`: that queue's whole worth is the promise "copy it and it byte-matches".
# These are served separately, and nothing lands without add_match's byte check,
# so a wrong candidate costs an agent a look and never a bad match.

NEAR_ALIGN = 0.90       # below this the two bodies are not the same function
NEAR_MIN_FUNC = 24      # a near miss on a stub is noise whatever it scores
# A donor that survives in more places than this is a generic stub, not a body
# waiting for a tiebreak; recording its candidates would cost more than it pays.
AMBIGUOUS_CAP = 16
# The gate that separates a usable address prediction from a worthless one, and
# how far from the prediction a candidate may still sit. Both are measured, not
# chosen: see predict_bfme2.
ANCHOR_SLOPE = 16
ANCHOR_WINDOW = 64
# Classes worth an agent's time. drift_classify.py records the prior for the
# rest: register-swap is an "MSVC-regalloc wall; do NOT attempt in C++ (proven
# on the whales)", and structural is real reconstruction, not a copy and tweak.
NEAR_SERVED = ("immediate-only", "imm+reg")
REGISTER_RE = re.compile(r"\be[a-z]{2}\b|\b[abcd][lh]\b")


def agreed_fields(donor, donor_fields, window, donor_rva, target_rva,
                  donor_image, target_image):
    """The donor fields whose value is relocation-shaped on BOTH sides.

    Scoring a near miss against ALL donor fields hides real differences, because
    the DIR32 pass claims any four-byte window addressing the image and some of
    those straddle an opcode. `add ecx,0x120` is `81 C1 20 01 00 00`, and the
    window at the modrm byte reads 0x0120C181 -- an address in BFME 1. Mask that
    and the donor scores 100% against `add ecx,0x17c`, which is a struct field
    that moved: the one thing the near tier exists to find.

    A field the target does not accept is therefore not masked, and its bytes
    count as the difference they are.
    """
    agreed = {}
    for offset, kind in donor_fields.items():
        if kind == "rel32":
            donor_call = (donor_rva + offset + 4
                          + struct.unpack_from("<i", donor, offset)[0]) & 0xFFFFFFFF
            target_call = (target_rva + offset + 4
                           + struct.unpack_from("<i", window, offset)[0]) & 0xFFFFFFFF
            if donor_image.in_text(donor_call) and target_image.in_text(target_call):
                agreed[offset] = kind
        elif (donor_image.in_image(struct.unpack_from("<I", donor, offset)[0])
              and target_image.in_image(struct.unpack_from("<I", window, offset)[0])):
            agreed[offset] = kind
    return agreed


def alignment(donor, fields, window):
    """Fraction of the bytes outside `fields` that agree. Pass the AGREED fields."""
    mask = mask_from(fields, len(donor))
    comparable = [index for index in range(len(donor)) if not mask[index]]
    if not comparable:
        return 0.0
    return sum(1 for i in comparable if donor[i] == window[i]) / len(comparable)


def disassemble(blob, scratch):
    """Instruction list for a raw i386 blob, via drift_classify's backend.

    That module picks objdump and falls back to capstone, which is the
    behaviour to share. Its scratch file is not: it writes one fixed path under
    build/drift/ that it never creates, so two sweeps running at once would
    overwrite each other's blob. Point it at our own directory per call.
    """
    import drift_classify
    scratch.mkdir(parents=True, exist_ok=True)
    previous = drift_classify.SCRATCH
    drift_classify.SCRATCH = scratch
    try:
        return drift_classify.disasm(blob)
    finally:
        drift_classify.SCRATCH = previous


def classify_near(donor, window, donor_fields, scratch):
    """(class, hint) for a near miss, in drift_classify.py's vocabulary.

    Both sides are blanked at the DONOR's field offsets so a relocation is not
    read as a changed literal. Blanking shifts nothing, so the two blobs stay
    comparable instruction for instruction.
    """
    left = disassemble(mask_bytes(donor, donor_fields), scratch)
    right = disassemble(mask_bytes(window, donor_fields), scratch)
    if not left or not right:
        return "structural", "disassembly unavailable"
    if len(left) != len(right):
        return "structural", f"{len(left)} instruction(s) against {len(right)}"
    immediate = register = shape = 0
    example = ""
    for (left_mnem, left_norm, left_ops), (right_mnem, right_norm, right_ops) in zip(left, right):
        if left_mnem != right_mnem:
            shape += 1
        elif left_norm == right_norm and left_ops != right_ops:
            immediate += 1
            example = example or f"{left_mnem} {left_ops} vs {right_ops}"
        elif left_norm != right_norm:
            if REGISTER_RE.sub("R", left_norm) == REGISTER_RE.sub("R", right_norm):
                register += 1
                example = example or f"{left_mnem} {left_ops} vs {right_ops}"
            else:
                shape += 1
    if shape:
        return "structural", f"{shape} instruction(s) differ in shape"
    if immediate and not register:
        return "immediate-only", f"{immediate} literal(s): {example}"
    if register and not immediate:
        return "register-swap", f"{register} instruction(s): {example}"
    if immediate and register:
        return "imm+reg", f"{immediate} literal(s) / {register} register(s): {example}"
    # Identical once masked: every difference sat in a relocation slot the two
    # sides do not both accept. Not a code difference, and not this tier's work.
    return "reloc-value", "differences are confined to relocation slots"


def mask_bytes(body, fields):
    out = bytearray(body)
    for offset in fields:
        out[offset : offset + 4] = b"\0" * 4
    return bytes(out)


def ghidra_starts():
    """{rva: size} from the Ghidra inventory, or {} when it is absent."""
    path = ROOT / "reverse" / "ghidra_functions.csv"
    if not path.exists():
        return {}
    sizes = {}
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                sizes[int(row["rva"], 16)] = int(row["size"])
            except (KeyError, ValueError, TypeError):
                continue
    return sizes


class Boundaries:
    """Positive evidence that an address can start a function.

    Absence of evidence is not evidence: 61% of the bodies already landed are
    missing from the Ghidra inventory, so "unknown" is served nowhere but
    refuses nothing either -- it simply is not the corroboration a near miss
    needs. An address INTERIOR to a known function is positive evidence
    against, and is refused.
    """

    def __init__(self, sizes, image):
        self.sizes = sizes
        self.starts = sorted(sizes)
        self.image = image

    def evidence(self, rva):
        if rva in self.sizes:
            return "ghidra-start"
        offset = rva - self.image.text_rva
        if offset >= 3 and self.image.text[offset - 3 : offset] == b"\xcc\xcc\xcc":
            return "int3-padded"
        index = bisect.bisect_right(self.starts, rva) - 1
        if index >= 0 and rva < self.starts[index] + self.sizes[self.starts[index]]:
            return None                      # interior of a known function
        return "unknown"


def donor_rows(min_size):
    """Open-BFME-1's clean converted bodies: real C++ at a real Code/ path.

    gen_small/gen_asm/masm_dumps are byte-true placeholders, and a `gen-` or
    `vendored=` note says the same about a row whose path looks ordinary.
    Neither is a donor: copying one across moves a dump, not a conversion.
    """
    rows = []
    with BFME1_LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            source = row.get("source") or ""
            if not source.startswith(("Code/", "game/")) or source.startswith(GEN_SOURCE_PREFIXES):
                continue
            notes = row.get("notes") or ""
            if "gen-" in notes or "vendored=" in notes:
                continue
            try:
                rva = int(row["target_rva"], 16)
                size = int(row["target_size"])
            except (KeyError, ValueError, TypeError):
                continue
            if size < min_size:
                continue
            rows.append({"name": row["name"], "rva": rva, "size": size, "source": source})
    return rows


def ledger_claims(path):
    """Sorted (rva, size, name, source, notes), for interval lookup."""
    claims = []
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                rva = int(row["target_rva"], 16)
                size = int(row["target_size"])
            except (KeyError, ValueError, TypeError):
                continue
            claims.append((rva, size, row["name"], row.get("source") or "", row.get("notes") or ""))
    claims.sort()
    return claims


class Claims:
    def __init__(self, claims):
        self.claims = claims
        self.starts = [claim[0] for claim in claims]
        self.names = {claim[2] for claim in claims}
        # Where the build would resolve a call to each name. A placement whose
        # call site points somewhere else is not a pin candidate, it is a
        # disagreement about the callee.
        self.addresses = {claim[2]: claim[0] for claim in claims}
        # How far back a claim can start and still reach forward into a query.
        # Walking back only until the first non-overlapping row would miss a
        # long body that starts well before a short one and spans past it.
        self.reach = max((claim[1] for claim in claims), default=0)

    def covering(self, rva, size):
        """Any claim overlapping [rva, rva+size), or None."""
        index = bisect.bisect_right(self.starts, rva + size - 1) - 1
        while index >= 0 and self.starts[index] + self.reach > rva:
            start, extent = self.claims[index][0], self.claims[index][1]
            if start < rva + size and start + extent > rva:
                return self.claims[index]
            index -= 1
        return None


DLLIMPORT_RE = re.compile(
    r"__declspec\s*\(\s*dllimport\s*\)[^;{]*?(\w+)\s*\(", re.S)


def import_slots(image):
    """{IAT slot VA: ImportEntry} for one image, or {} if it has no imports."""
    from pe_imports import read_imports
    try:
        return read_imports(image.data)
    except ValueError:
        return {}


def source_dllimports(source):
    """Names the donor source declares with __declspec(dllimport)."""
    try:
        text = (BFME1 / source).read_text(encoding="utf-8", errors="replace")
    except OSError:
        return set()
    return set(DLLIMPORT_RE.findall(text))


def import_alias_note(source, imports):
    """Warn when the donor declares an import under a name of its own invention.

    build.verify_import_refs reads the import actually sitting at the slot the
    RETAIL body references and requires the source's COFF import name to match
    it. A donor that declares `t2_block_copy` for what game.dat reaches as
    msvcr71.dll!memmove emits __imp__t2_block_copy, and no pin can satisfy that
    check -- the fix is to declare it under the real name. This is invisible to
    the byte comparison, because each image holds a perfectly good DIR32 into
    its own IAT, so the body lands and then fails a later verifier. That cost a
    wave-1 body and an incorrect `needs an import pin` note in re_attempts.log.
    """
    from pe_imports import coff_import_names
    referenced = {entry.name for entry in imports if entry.name}
    if not referenced:
        return None
    declared = source_dllimports(source)
    if not declared:
        return None
    accepted = {name for symbol in (f"__imp_{d}" for d in declared)
                for name in coff_import_names(symbol)}
    accepted |= {f"_{d}" for d in declared} | declared
    if referenced & accepted:
        return None
    return (f"donor declares {', '.join(sorted(declared)[:3])} but the body reaches "
            f"{', '.join(sorted(referenced)[:3])}; rename the declaration to the real "
            "import or Import-ref verify refuses it (no pin can fix this)")


def bfme1_names_by_rva():
    """Every name Open-BFME-1 resolves at an address, ledger rows AND pins.

    The pins matter more than they look. A donor object references the callee
    name ITS OWN source declares, which is frequently not the ledger's name for
    the body -- that is exactly why Open-BFME-1 needed a pin for it. Its
    symbols.csv is therefore the list of names a BFME 2 build of the same file
    will ask for, and pinning anything else leaves ./build.sh printing an
    unresolved symbol nobody wrote. The pins also carry ILT thunk addresses,
    which is what a call site decodes to in the first place.
    """
    names = defaultdict(list)
    with BFME1_LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                names[int(row["target_rva"], 16)].append(row["name"])
            except (KeyError, ValueError, TypeError):
                continue
    if BFME1_SYMBOLS.exists():
        with BFME1_SYMBOLS.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                try:
                    address = int(row["address"], 16)
                except (KeyError, ValueError, TypeError):
                    continue
                if row["name"] not in names[address]:
                    names[address].append(row["name"])
    return names


def pinned_symbols():
    if not BFME2_SYMBOLS.exists():
        return {}
    pins = {}
    with BFME2_SYMBOLS.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                pins[row["name"]] = int(row["address"], 16)
            except (KeyError, ValueError, TypeError):
                continue
    return pins


def _header_index(root):
    """Every header basename under a tree, for the tier-B resolution check."""
    index = defaultdict(list)
    for path in (root / "Code").rglob("*.h"):
        index[path.name].append(path.relative_to(root).as_posix())
    return index


_BFME2_HEADERS = None


def bfme2_headers():
    global _BFME2_HEADERS
    if _BFME2_HEADERS is None:
        _BFME2_HEADERS = _header_index(ROOT)
    return _BFME2_HEADERS


def copy_tier(source):
    """How much work moving this donor file is, and why.

    L: the donor is itself a naked/__emit lift; the conversion gate refuses it.
    P: the destination is outside the roots the pre-commit hook allows.
    S: the donor defines functions the sweep never placed (set by group_files,
       which is where the sibling rows are known); the hook's
       find_declared_unmatched gate refuses a source with an undeclared
       definition, so the file cannot land whole.
    A: no project includes -- `cp` is the conversion.
    B: quotes project headers, which have to exist here too.
    C: its `// cl:` names vendored-tree include paths that are one level deeper
       in this repo (reference/open-bfme-1/reference/... not reference/...).
    D: the destination path is already taken, so the copy would clobber a body
       this repo owns; the donor needs a distinct TU name.
    """
    path = BFME1 / source
    target_source = bfme2_source_path(source)
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return "D", "donor file is missing from the submodule", "", False
    cl_match = CL_RE.search(text)
    cl_line = cl_match.group(1).strip() if cl_match else ""
    stlport = "// stlport" in text
    project = [name for quote, name in INCLUDE_RE.findall(text) if quote == '"']
    if LIFT_RE.search(text):
        return ("L", "donor carries a __declspec(naked)/__emit body: a lift, which the "
                "conversion gate refuses (AGENTS.md anti-lift policy)", cl_line, stlport)
    if not target_source.startswith(PLACEMENT_ROOTS):
        return ("P", f"{target_source.split('/')[1]}/ is not an allowed root for a new source "
                "(.githooks/pre-commit placement rule)", cl_line, stlport)
    if (ROOT / target_source).exists():
        return "D", f"{target_source} already exists in this repo", cl_line, stlport
    if "reference/CnC_Generals_Zero_Hour" in cl_line or "reference/shims" in cl_line:
        return "C", "// cl: include paths need the reference/open-bfme-1/ prefix", cl_line, stlport
    if project:
        # Naming which quoted headers this repo does not have yet is the whole
        # difference between "copy it" and "port a subsystem first".
        index = bfme2_headers()
        missing = sorted({name for name in project if Path(name).name not in index})
        if missing:
            note = (f"quotes {len(missing)} header(s) this repo does not have: "
                    + ", ".join(missing[:4]))
        else:
            note = f"quotes {len(set(project))} project header(s), all present here"
        return "B", note, cl_line, stlport
    return "A", "self-contained", cl_line, stlport


def policy(source):
    source = bfme2_source_path(source)
    for prefix, reason in REFUSED_PREFIXES.items():
        if source.startswith(prefix):
            return "refused", reason
    for needle, reason in FLAGGED_SUBSTRINGS.items():
        if needle in source:
            return "flagged", reason
    return "ok", ""


def do_scan(args):
    if not BFME1_EXE.exists():
        raise SystemExit(
            f"bfme1_sweep: {BFME1_EXE.relative_to(ROOT)} is missing — "
            "run `git submodule update --init reference/open-bfme-1`")
    build.verify_baseline()
    donor_image = Image(BFME1_EXE)
    target_image = Image(build.EXE)
    print(f"bfme1 .text 0x{donor_image.text_rva:08X} {len(donor_image.text)} bytes")
    print(f"bfme2 .text 0x{target_image.text_rva:08X} {len(target_image.text)} bytes")

    claims = Claims(ledger_claims(BFME2_LEDGER))
    bfme1_names = bfme1_names_by_rva()
    donor_iat = import_slots(donor_image)
    ghidra = ghidra_starts()
    boundaries = Boundaries(ghidra, target_image)
    rows = donor_rows(args.min_size)
    print(f"donors: {len(rows)} clean Open-BFME-1 bodies >= {args.min_size}B")

    tally = Counter()
    records = []
    near_records = []
    ambiguous_records = []
    started = time.monotonic()
    for position, row in enumerate(rows, 1):
        if position % 2000 == 0:
            elapsed = time.monotonic() - started
            print(f"  {position}/{len(rows)} donors, {tally['unique']} placed, "
                  f"{elapsed:.0f}s elapsed, ~{elapsed / position * (len(rows) - position):.0f}s left",
                  file=sys.stderr, flush=True)
        donor = donor_image.body(row["rva"], row["size"])
        if donor is None or len(donor) != row["size"]:
            tally["unreadable"] += 1
            continue
        donor_fields = volatile_fields(donor, donor_image, row["rva"])
        runs = clear_runs(mask_from(donor_fields, row["size"]))
        # Every byte outside a relocation field, as slices to memcmp per window,
        # longest first so the most discriminating comparison fails first.
        comparable = runs
        if not runs or runs[0][1] < MIN_NEEDLE:
            tally["no-needle"] += 1
            continue
        offset, length = runs[0]
        needle = donor[offset : offset + length]
        candidates = occurrences(target_image.text, needle, cap=PLACEMENT_CAP)
        if len(candidates) >= PLACEMENT_CAP:
            tally["needle-too-common"] += 1
            continue
        survivors = []
        for candidate in candidates:
            start = candidate - offset
            if start < 0 or start + row["size"] > len(target_image.text):
                continue
            target_rva = target_image.text_rva + start
            window = target_image.text[start : start + row["size"]]
            unexplained, dir32, rel32 = explain(
                donor, donor_fields, comparable, window, row["rva"], target_rva,
                donor_image, target_image)
            if unexplained == 0:
                survivors.append((target_rva, dir32, rel32))
                if len(survivors) > AMBIGUOUS_CAP:
                    break       # a stub, not a body one tiebreak away
        if not survivors:
            tally["no-placement"] += 1
            # A near miss is only worth scoring where the address could start a
            # function at all, so the boundary test -- a dict lookup -- runs
            # before the per-byte alignment. Most offsets in .text are interior
            # bytes, so this is what keeps the near pass affordable.
            if row["size"] >= NEAR_MIN_FUNC:
                best = None
                for candidate in candidates:
                    start = candidate - offset
                    if start < 0 or start + row["size"] > len(target_image.text):
                        continue
                    near_rva = target_image.text_rva + start
                    evidence = boundaries.evidence(near_rva)
                    if evidence not in ("ghidra-start", "int3-padded"):
                        continue
                    window = target_image.text[start : start + row["size"]]
                    agreed = agreed_fields(donor, donor_fields, window, row["rva"],
                                           near_rva, donor_image, target_image)
                    score = alignment(donor, agreed, window)
                    if best is None or score > best[0]:
                        best = (score, near_rva, evidence)
                if best is not None and best[0] >= NEAR_ALIGN:
                    score, near_rva, evidence = best
                    tally["near"] += 1
                    near_records.append({
                        "name": row["name"],
                        "source": row["source"],
                        "bfme1_rva": row["rva"],
                        "size": row["size"],
                        "bfme2_rva": near_rva,
                        "alignment": round(score, 4),
                        "boundary": evidence,
                        "ghidra_size": ghidra.get(near_rva),
                    })
            continue
        if len(survivors) > 1:
            tally["ambiguous"] += 1
            # Recorded, not dropped. Every one of these placements already
            # explained every byte; what the donor lacks is not evidence that
            # the code matches but evidence of WHICH copy it is, and the
            # address map resolves that from anchors rather than from bytes.
            if len(survivors) <= AMBIGUOUS_CAP:
                ambiguous_records.append({
                    "name": row["name"],
                    "source": row["source"],
                    "bfme1_rva": row["rva"],
                    "size": row["size"],
                    "candidates": [rva for rva, _, _ in survivors],
                })
            continue
        target_rva, dir32, rel32 = survivors[0]
        tally["unique"] += 1

        # Counted for the control figure only. Whether an address is free is
        # re-decided every time work is served -- rows land continuously, and a
        # cached verdict would send two agents at the same address.
        claim = claims.covering(target_rva, row["size"])
        if claim is not None:
            tally["claimed"] += 1
            tally["claimed-exact-boundary"] += int(claim[0] == target_rva and claim[1] == row["size"])
        else:
            tally["free"] += 1
            tally["free-bytes"] += row["size"]

        fanout = len(occurrences(donor_image.text, needle, cap=FANOUT_CAP))
        twins = []
        if fanout > 1:
            for position in occurrences(donor_image.text, needle, cap=FANOUT_CAP):
                twin_rva = donor_image.text_rva + position - offset
                twins.extend(bfme1_names.get(twin_rva, []))
            twins = sorted(set(twins))

        # Which imports this body reaches, by the donor's own IAT. The copied
        # source has to declare each one under a name the COFF import check
        # accepts; see import_alias_note.
        imports = [donor_iat[donor_va] for _, donor_va, _ in dir32 if donor_va in donor_iat]

        strings = []
        for slot, donor_va, target_va in dir32:
            donor_text = donor_image.cstring(donor_va)
            target_text = target_image.cstring(target_va)
            if donor_text is None and target_text is None:
                continue
            strings.append({
                "offset": slot,
                "bfme1": donor_text.decode("ascii", "replace") if donor_text else None,
                "bfme2": target_text.decode("ascii", "replace") if target_text else None,
                "agree": bool(donor_text) and donor_text == target_text,
            })

        # Every name the donor object might reference for this callee, not one
        # pick: a body that BFME 1 reached through an ILT thunk carries the
        # thunk's pinned name and the body's ledger name, and which one the
        # object asks for depends on how the donor source declared it.
        calls = []
        for slot, donor_call, target_call in rel32:
            calls.append({
                "offset": slot,
                "bfme1_target": donor_call,
                "bfme2_target": target_call,
                "bfme1_names": bfme1_names.get(donor_call, []),
            })

        records.append({
            "name": row["name"],
            "source": row["source"],
            "bfme1_rva": row["rva"],
            "size": row["size"],
            "bfme2_rva": target_rva,
            "fanout": fanout,
            "icf_twins": twins,
            "needle": length,
            "strings": strings,
            "calls": calls,
            "imports": sorted({entry.name for entry in imports if entry.name}),
        })

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    payload = {
        "min_size": args.min_size,
        "bfme1_exe": str(BFME1_EXE.relative_to(ROOT)),
        "bfme2_exe": str(build.EXE.relative_to(ROOT)),
        "tally": dict(tally),
        "records": records,
        "near": near_records,
        "ambiguous": ambiguous_records,
    }
    MATCH_JSON.write_text(json.dumps(payload, indent=1), encoding="utf-8")

    print()
    print(f"unique placements       {tally['unique']}")
    print(f"  on claimed ground     {tally['claimed']} "
          f"({tally['claimed-exact-boundary']} at exactly the claimed RVA+size)")
    print(f"  on free ground        {tally['free']}  ({tally['free-bytes']} bytes)")
    print(f"ambiguous (>1 place)    {tally['ambiguous']}")
    print(f"needle too common       {tally['needle-too-common']}")
    print(f"no placement            {tally['no-placement']}")
    print(f"  of those, near misses {tally['near']} "
          f"(>={int(NEAR_ALIGN * 100)}% aligned at a plausible boundary)")
    print(f"no usable needle        {tally['no-needle']}")
    control = tally["claimed-exact-boundary"]
    print()
    print(f"CONTROL: {control} placements reproduce a boundary this repo matched independently.")
    if control < args.control_floor:
        print(f"bfme1_sweep: CONTROL BELOW {args.control_floor} — the mask or the explainer "
              "has regressed; do not trust this run's free candidates.", file=sys.stderr)
        return 1
    print(f"wrote {MATCH_JSON.relative_to(ROOT)}")
    return 0


# ---------------------------------------------------------------- serving work

def load_matches():
    if not MATCH_JSON.exists():
        raise SystemExit("bfme1_sweep: no build/bfme1_sweep/match.json — run `scan` first")
    return json.loads(MATCH_JSON.read_text(encoding="utf-8"))


def body_tier(record, claims, pins):
    """T1 drop-in, T2 needs pins, T3 the name is an ICF guess, T4 do not serve.

    Returns (tier, reasons, pin_lines). The order of the checks is deliberate:
    a string conflict outranks everything, because it says the placement is not
    this function however clean the bytes look.
    """
    reasons = []
    conflict = [s for s in record["strings"] if s["bfme1"] and not s["agree"]]
    if conflict:
        reasons.append(f"DIR32 string differs: {conflict[0]['bfme1']!r} vs {conflict[0]['bfme2']!r}")
        return "T4", reasons, []
    claim = claims.covering(record["bfme2_rva"], record["size"])
    if claim is not None:
        reasons.append(f"0x{claim[0]:08X} is claimed by {claim[2]} ({claim[3]})")
        return "T4", reasons, []
    if record["name"] in claims.names:
        reasons.append("this repo already spends that name at another address")
        return "T4", reasons, []
    # Resolution is re-decided here rather than trusted from the scan: pins and
    # rows land continuously, and a four-minute scan would otherwise keep
    # serving a body as "needs a pin" that somebody already pinned.
    unnamed = [call for call in record["calls"] if not call["bfme1_names"]]
    if unnamed:
        reasons.append(f"{len(unnamed)} call site(s) with no name on the BFME1 side")
        return "T4", reasons, []
    # A callee this repo already places somewhere else is not a pin to paste
    # over: it says the two images disagree about what this call site calls,
    # which is evidence against the placement rather than work to do.
    needed = {}
    for call in record["calls"]:
        for name in call["bfme1_names"]:
            settled = claims.addresses.get(name, pins.get(name))
            if settled is None:
                needed[name] = call["bfme2_target"]
            elif settled != call["bfme2_target"]:
                reasons.append(f"this repo places {name} at 0x{settled:08X}, "
                               f"but the call site reaches 0x{call['bfme2_target']:08X}")
                return "T4", reasons, []
    pin_lines = sorted(needed.items())
    if record["fanout"] > 1:
        reasons.append(f"ICF-folded in lotrbfme.exe across {record['fanout']} addresses")
        return "T3", reasons, pin_lines
    if pin_lines:
        reasons.append(f"{len(pin_lines)} symbols.csv pin(s) needed")
        return "T2", reasons, pin_lines
    agree = sum(1 for s in record["strings"] if s["agree"])
    if agree:
        reasons.append(f"{agree} DIR32 string literal(s) agree")
    return "T1", reasons, []


def bfme1_siblings():
    """{source: {name}} -- every clean function Open-BFME-1 claims per source, any size.

    donor_rows() drops bodies under --min-size, and the scan drops ambiguous
    ones, but the pre-commit hook refuses a source that defines ANY function
    the ledger lacks. So the placed bodies are not the file's contents: a donor
    is only landable whole if everything it defines was placed.
    """
    siblings = defaultdict(set)
    with BFME1_LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            source = row.get("source") or ""
            if not source.startswith(("Code/", "game/")) or source.startswith(GEN_SOURCE_PREFIXES):
                continue
            notes = row.get("notes") or ""
            if "gen-" in notes or "vendored=" in notes:
                continue
            siblings[source].add(row["name"])
    return siblings


TIER_ORDER = {"T1": 0, "T2": 1, "T3": 2, "T4": 3}


def group_files(payload, include_refused=False, tiers=("T1", "T2", "T3"), include_held=False):
    claims = Claims(ledger_claims(BFME2_LEDGER))
    pins = pinned_symbols()
    siblings = bfme1_siblings()
    files = defaultdict(lambda: {"bodies": [], "held": []})
    for record in payload["records"]:
        tier, reasons, pin_lines = body_tier(record, claims, pins)
        record = dict(record, tier=tier, reasons=reasons, pins=pin_lines)
        bucket = files[record["source"]]
        (bucket["bodies"] if tier in tiers else bucket["held"]).append(record)

    served = []
    for source, bucket in files.items():
        if not bucket["bodies"]:
            continue
        verdict, reason = policy(source)
        if verdict == "refused" and not include_refused:
            continue
        tier, note, cl_line, stlport = copy_tier(source)
        placed = {record["name"] for record in bucket["bodies"] + bucket["held"]}
        unplaced = sorted(siblings.get(source, set()) - placed)
        if unplaced and tier in ("A", "B", "C"):
            tier = "S"
            note = (f"donor also defines {len(unplaced)} function(s) the sweep did not place "
                    f"(under {MIN_FUNC}B or ambiguous), so the hook's find_declared_unmatched "
                    f"gate refuses the file: {', '.join(unplaced[:2])}")
        if tier in HELD_COPY_TIERS and not include_held:
            continue
        from pe_imports import ImportEntry
        reached = [ImportEntry("", name, None)
                   for record in bucket["bodies"] for name in record.get("imports", ())]
        alias = import_alias_note(source, reached)
        bodies = sorted(bucket["bodies"], key=lambda r: (TIER_ORDER[r["tier"]], -r["size"]))
        served.append({
            "source": source,
            "copy_tier": tier,
            "copy_note": note,
            "cl": cl_line,
            "stlport": stlport,
            "policy": verdict,
            "policy_note": reason,
            "import_alias": alias,
            "bytes": sum(body["size"] for body in bodies),
            "best_tier": min(body["tier"] for body in bodies),
            "bodies": bodies,
            "held": bucket["held"],
        })
    served.sort(key=lambda entry: (TIER_ORDER[entry["best_tier"]],
                                   COPY_ORDER[entry["copy_tier"]],
                                   -entry["bytes"]))
    return served


def do_ranked(args):
    payload = load_matches()
    served = group_files(payload, include_refused=args.include_refused,
                         include_held=args.include_held or bool(args.copy_tier))
    if args.copy_tier:
        served = [entry for entry in served if entry["copy_tier"] in args.copy_tier]
    if args.tier:
        served = [entry for entry in served if entry["best_tier"] in args.tier]
    if args.json:
        print(json.dumps(served[: args.limit], indent=1))
        return 0
    total = sum(entry["bytes"] for entry in served)
    print(f"{len(served)} donor file(s), {total} bytes of unclaimed game.dat .text")
    print()
    print(f"{'bytes':>7}  {'fn':>3}  tier  copy  source")
    for entry in served[: args.limit]:
        flag = "!" if entry["policy"] != "ok" else " "
        print(f"{entry['bytes']:>7}  {len(entry['bodies']):>3}  {entry['best_tier']:>4}  "
              f"{entry['copy_tier']:>4}{flag} {entry['source']}")
    if len(served) > args.limit:
        print(f"... {len(served) - args.limit} more (--limit)")
    if served:
        print()
        print(f"next: python3 tools/bfme1_sweep.py show {served[0]['source']}")
    return 0


def packet_text(entry):
    source = entry["source"]
    target_source = bfme2_source_path(source)
    donor = f"reference/open-bfme-1/{source}"
    lines = []
    lines.append(f"# {source}")
    lines.append("")
    lines.append(f"{entry['best_tier']} · copy-tier {entry['copy_tier']} · "
                 f"{len(entry['bodies'])} bod{'y' if len(entry['bodies']) == 1 else 'ies'} · "
                 f"{entry['bytes']} bytes of unclaimed game.dat .text")
    lines.append("")
    lines.append(f"    donor   {donor}")
    lines.append(f"    dest    {target_source}")
    lines.append(f"    copy    {entry['copy_note']}")
    lines.append(f"    cl:     {entry['cl'] or '(none — build.py base flags)'}")
    lines.append(f"    stlport {'yes' if entry['stlport'] else 'no'}")
    if entry["policy"] != "ok":
        lines.append(f"    POLICY  {entry['policy'].upper()}: {entry['policy_note']}")
    if entry.get("import_alias"):
        lines.append(f"    IMPORT  {entry['import_alias']}")
    lines.append("")
    lines.append("These bodies are byte-identical between lotrbfme.exe and game.dat once")
    lines.append("relocation slots are set aside, so the donor file is expected to compile to")
    lines.append("retail bytes here unchanged. A failure is a finding: record it and move on.")
    lines.append("")
    lines.append("| BFME1 name | b1 RVA | size | b2 RVA | tier | evidence |")
    lines.append("|---|---|---|---|---|---|")
    for body in entry["bodies"]:
        evidence = "; ".join(body["reasons"]) or "clean transfer"
        lines.append(f"| `{body['name']}` | 0x{body['bfme1_rva']:08X} | {body['size']} | "
                     f"0x{body['bfme2_rva']:08X} | {body['tier']} | {evidence} |")
    lines.append("")

    pins = sorted({(name, address) for body in entry["bodies"]
                   for name, address in body["pins"]})
    icf = [body for body in entry["bodies"] if body["tier"] == "T3"]
    if icf:
        lines.append("## The name is a guess on these")
        lines.append("")
        lines.append("The compiler folded these bodies inside lotrbfme.exe, so several BFME1")
        lines.append("names share the bytes and the sweep cannot tell which one game.dat means.")
        lines.append("Read AGENTS.md on over-claiming before spending a name here.")
        lines.append("")
        for body in icf:
            twins = ", ".join(f"`{name}`" for name in body["icf_twins"][:8]) or "(unnamed)"
            lines.append(f"- 0x{body['bfme2_rva']:08X}: {twins}")
        lines.append("")

    lines.append("## Steps")
    lines.append("")
    lines.append("```sh")
    lines.append(f"mkdir -p {str(Path(target_source).parent)}")
    lines.append(f"cp {donor} \\")
    lines.append(f"   {target_source}")
    lines.append(f"git add -- {target_source}       # check_csv refuses an untracked ledger source")
    if entry["copy_tier"] == "C":
        lines.append("# then rewrite the `// cl:` -I paths: reference/CnC_Generals_Zero_Hour/...")
        lines.append("#                              -> reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/...")
    if entry["copy_tier"] == "D":
        lines.append("# the destination is occupied — give the donor a distinct TU name instead")
    lines.append("```")
    lines.append("")
    if pins:
        lines.append("Append to `reverse/symbols.csv` (LF only — the file is `merge=union` and a")
        lines.append("CRLF twin duplicates on the next rebase). Check each one first:")
        lines.append("")
        lines.append("```sh")
        for name, _ in pins:
            lines.append(f"python3 tools/pin_consistency.py --symbol '{name}'")
        lines.append("```")
        lines.append("")
        lines.append("```csv")
        for name, address in pins:
            lines.append(f"{name},0x{address:08X}")
        lines.append("```")
        lines.append("")
    else:
        lines.append("No new `reverse/symbols.csv` pin is needed: every call site this file emits")
        lines.append("already resolves through the ledger.")
        lines.append("")
    lines.append("```sh")
    for body in entry["bodies"]:
        lines.append(f"python3 tools/add_match.py '{body['name']}' 0x{body['bfme2_rva']:08X} "
                     f"{body['size']} {target_source} \\")
        lines.append(f"    --notes '{ledger_note(body)}'")
    lines.append(f"./build.sh {target_source}")
    lines.append("python3 tools/check_csv.py")
    if pins:
        lines.append("python3 tools/pin_consistency.py --check")
    lines.append("```")
    lines.append("")
    lines.append("On a refusal, revert your own work only and record the verdict:")
    lines.append("")
    lines.append("```sh")
    lines.append(f"git checkout -- reverse/functions.csv reverse/symbols.csv && rm -f {target_source}")
    first = entry["bodies"][0]
    lines.append(f"python3 tools/re_log.py record '{first['name']}' 0x{first['bfme2_rva']:08X} "
                 f"{first['size']} no-match 'bfme1_sweep donor <what cl did instead>'")
    lines.append("```")
    if entry["held"]:
        lines.append("")
        lines.append("## Not served from this file")
        lines.append("")
        for body in sorted(entry["held"], key=lambda r: -r["size"]):
            lines.append(f"- 0x{body['bfme2_rva']:08X} {body['size']}B `{body['name']}` — "
                         + ("; ".join(body["reasons"]) or "held"))
    lines.append("")
    return "\n".join(lines)


def ledger_note(body):
    """The notes column for one claim.

    No commas: functions.csv is raw comma-joined with no quoting, and
    add_match.py refuses a note carrying one rather than corrupt the ledger.
    """
    note = f"BFME1 byte-identical donor; b1 0x{body['bfme1_rva']:08X}"
    if body["tier"] == "T3":
        note += "; ICF-folded in BFME1 so the name is this sweep's pick among its twins"
    agree = sum(1 for entry in body["strings"] if entry["agree"])
    if agree:
        note += f"; {agree} DIR32 string literal(s) agree"
    return note


def packet_path(source):
    return PACKET_DIR / (re.sub(r"[^A-Za-z0-9]+", "_", source).strip("_") + ".md")


def do_packets(args):
    payload = load_matches()
    served = group_files(payload, include_refused=args.include_refused)
    PACKET_DIR.mkdir(parents=True, exist_ok=True)
    written = 0
    for entry in served[: args.limit]:
        path = packet_path(entry["source"])
        path.write_text(packet_text(entry), encoding="utf-8")
        written += 1
    print(f"wrote {written} packet(s) to {PACKET_DIR.relative_to(ROOT)}")
    return 0


def find_entry(served, source, near=()):
    """The served donor file named by `source`, or a refusal that says why not.

    A near candidate is deliberately not landable: it does not byte-match as
    copied, so `land` would only drive add_match into a refusal. Name that
    rather than reporting the file as unknown.
    """
    if near and not any(source in entry["source"] for entry in served):
        hit = next((entry for entry in near if source in entry["source"]), None)
        if hit is not None:
            raise SystemExit(
                f"bfme1_sweep: {hit['source']} is a NEAR candidate "
                f"({hit['klass']}, {hit['alignment'] * 100:.1f}% aligned), not a byte-exact "
                f"one.\n  It will not match as copied. See the diff:\n"
                f"  python3 tools/bfme1_sweep.py near --show '{hit['name']}'")
    exact = [entry for entry in served if entry["source"] == source]
    if exact:
        return exact[0]
    loose = [entry for entry in served if source in entry["source"]]
    if len(loose) == 1:
        return loose[0]
    if not loose:
        raise SystemExit(f"bfme1_sweep: no served donor file matches {source!r}")
    raise SystemExit("bfme1_sweep: ambiguous — " + ", ".join(entry["source"] for entry in loose[:8]))


def near_candidates(payload, include_held=False, limit=None):
    """Classify the recorded near misses and return the ones worth serving.

    Classification is done here rather than in `scan` because it shells out to a
    disassembler twice per candidate; the scan records placements and this pays
    for the reading, for as many as are asked for.
    """
    claims = Claims(ledger_claims(BFME2_LEDGER))
    donor_image = Image(BFME1_EXE)
    target_image = Image(build.EXE)
    scratch = OUT_DIR / "disasm"
    served = []
    for record in sorted(payload.get("near", ()), key=lambda r: -r["alignment"]):
        source = record["source"]
        if claims.covering(record["bfme2_rva"], record["size"]) is not None:
            continue                       # re-checked live, like the exact tier
        if record["name"] in claims.names:
            continue
        verdict, policy_note = policy(source)
        if verdict == "refused":
            continue
        tier, copy_note, cl_line, stlport = copy_tier(source)
        if tier in HELD_COPY_TIERS and not include_held:
            continue                       # a candidate the hooks will not commit is worthless
        donor = donor_image.body(record["bfme1_rva"], record["size"])
        if donor is None or len(donor) != record["size"]:
            continue
        start = record["bfme2_rva"] - target_image.text_rva
        window = target_image.text[start : start + record["size"]]
        if len(window) != record["size"]:
            continue
        fields = agreed_fields(donor,
                               volatile_fields(donor, donor_image, record["bfme1_rva"]),
                               window, record["bfme1_rva"], record["bfme2_rva"],
                               donor_image, target_image)
        kind, hint = classify_near(donor, window, fields, scratch)
        if kind not in NEAR_SERVED:
            continue
        served.append(dict(record, klass=kind, hint=hint, copy_tier=tier,
                           copy_note=copy_note, cl=cl_line, stlport=stlport,
                           policy=verdict, policy_note=policy_note,
                           donor=donor, window=window, fields=fields))
        if limit is not None and len(served) >= limit:
            break
    return served



# ------------------------------------------------------------- the address map

def anchor_pairs(payload):
    """Sorted (bfme1_rva, bfme2_rva) for every body the sweep placed uniquely.

    Only unique placements anchor. An ambiguous one is exactly the question
    being asked here, and a near miss is an unverified identity claim.
    """
    seen = {}
    for record in payload.get("records", ()):
        seen[record["bfme1_rva"]] = record["bfme2_rva"]
    return sorted(seen.items())


def predict_bfme2(b1, anchors, keys, slope_tolerance=ANCHOR_SLOPE):
    """Where a BFME 1 address should land in game.dat, or None to decline.

    The two images lay the same code out in the same order. Ordering the placed
    bodies by BFME 1 address puts 84% of them in ascending runs of five or more
    -- the longest is 248 -- and 76% of neighbouring pairs are spaced within 16
    bytes of each other in BOTH images. Between two anchors the map is affine,
    so interpolating is not an estimate but a reading.

    Across a region boundary it is worthless: BFME 2 dropped and reordered whole
    objects. Measured leave-one-out over 4,696 anchors, the error is 16 bytes at
    the median and 1.9 MB at the 90th percentile -- one distribution laid over
    another, not a long tail.

    The gate tells them apart, and it is checkable before the answer is used: if
    the bracketing anchors span the same distance in both images, everything
    between them transferred intact. At a 16-byte tolerance that covers 41% of
    placed bodies and predicts 99% of them to within 64 bytes, p99 11 bytes.
    Declining is the point -- a prediction offered everywhere would be wrong
    half the time.
    """
    index = bisect.bisect_left(keys, b1)
    if index == 0 or index >= len(anchors):
        return None
    lo_b1, lo_b2 = anchors[index - 1]
    hi_b1, hi_b2 = anchors[index]
    span1, span2 = hi_b1 - lo_b1, hi_b2 - lo_b2
    if span1 <= 0 or abs(span2 - span1) > slope_tolerance:
        return None
    return lo_b2 + round((b1 - lo_b1) * span2 / span1)


def resolve_ambiguous(payload, window=ANCHOR_WINDOW, include_claimed=False):
    """Ambiguous donors the address map picks a single candidate for.

    Every candidate here already explained every byte -- that is what made the
    donor ambiguous rather than unplaced. What is missing is not evidence that
    the code matches but evidence of WHICH copy this is, and that is positional,
    so it comes from the anchors instead of from more bytes.

    A resolution needs the winner inside the window AND the runner-up outside
    it. Two candidates equally close to the prediction is the same question over
    again, not an answer to it.
    """
    anchors = anchor_pairs(payload)
    keys = [b1 for b1, _ in anchors]
    claims = Claims(ledger_claims(BFME2_LEDGER))
    resolved = []
    for record in payload.get("ambiguous", ()):
        if record["name"] in claims.names:
            continue
        guess = predict_bfme2(record["bfme1_rva"], anchors, keys)
        if guess is None:
            continue
        free = [c for c in record["candidates"]
                if include_claimed or claims.covering(c, record["size"]) is None]
        if not free:
            continue
        ranked = sorted(free, key=lambda c: abs(c - guess))
        if abs(ranked[0] - guess) > window:
            continue
        if len(ranked) > 1 and abs(ranked[1] - guess) <= window:
            continue
        resolved.append(dict(record, bfme2_rva=ranked[0], predicted=guess,
                             error=abs(ranked[0] - guess),
                             candidate_count=len(record["candidates"])))
    return resolved


def do_ambiguous(args):
    payload = load_matches()
    pool = payload.get("ambiguous", ())
    if not pool:
        raise SystemExit("bfme1_sweep: no ambiguous records — re-run `scan`")
    resolved = resolve_ambiguous(payload, window=args.window)
    if args.json:
        print(json.dumps([{k: v for k, v in r.items() if k != "candidates"}
                          for r in resolved], indent=1))
        return 0
    pool_bytes = sum(r["size"] for r in pool)
    got = sum(r["size"] for r in resolved)
    print(f"{len(pool)} ambiguous donor(s), {pool_bytes:,}B recorded")
    print(f"{len(resolved)} resolved by the address map, {got:,}B "
          f"({got * 100.0 / max(pool_bytes, 1):.1f}% of the pool)\n")
    big = [r for r in resolved if r["size"] >= args.min_size]
    print(f" bytes  err  of  b2 rva      name")
    for record in sorted(big, key=lambda r: -r["size"])[:args.limit]:
        print(f"{record['size']:6d} {record['error']:4d} {record['candidate_count']:3d}  "
              f"0x{record['bfme2_rva']:08X}  {record['name'][:64]}")
    print(f"\n{len(big)} of them >= {args.min_size}B, "
          f"{sum(r['size'] for r in big):,}B")
    return 0


def near_packet(entry):
    source = entry["source"]
    target_source = bfme2_source_path(source)
    donor, window, fields = entry["donor"], entry["window"], entry["fields"]
    mask = mask_from(fields, len(donor))
    lines = [f"# {entry['name']}", ""]
    lines.append(f"NEAR MISS · {entry['klass']} · {entry['alignment'] * 100:.1f}% aligned · "
                 f"copy-tier {entry['copy_tier']}")
    lines.append("")
    lines.append("THIS WILL NOT BYTE-MATCH AS COPIED. The diff below is the work: the two")
    lines.append("bodies are the same function either side of a BFME 1 -> BFME 2 change.")
    lines.append("Copy the donor, apply the difference, and land it the normal way. Nothing")
    lines.append("is claimed until add_match byte-verifies it, so a wrong candidate costs a")
    lines.append("look and never a bad match.")
    lines.append("")
    lines.append(f"    donor    reference/open-bfme-1/{source}")
    lines.append(f"    dest     {target_source}")
    lines.append(f"    bfme1    0x{entry['bfme1_rva']:08X}  {entry['size']} bytes")
    lines.append(f"    bfme2    0x{entry['bfme2_rva']:08X}  [{entry['boundary']}]")
    if entry["ghidra_size"] is not None:
        agree = "same size" if entry["ghidra_size"] == entry["size"] else                 f"Ghidra says {entry['ghidra_size']} bytes -- boundary may be wrong"
        lines.append(f"    ghidra   {agree}")
    lines.append(f"    cl:      {entry['cl'] or '(none -- build.py base flags)'}")
    lines.append(f"    why      {entry['hint']}")
    if entry["copy_tier"] in HELD_COPY_TIERS:
        lines.append(f"    HELD     {entry['copy_note']}")
    lines.append("")
    lines.append("## Differing bytes (relocation slots excluded)")
    lines.append("")
    lines.append("| offset | bfme1 | game.dat |")
    lines.append("|---|---|---|")
    shown = 0
    for index in range(len(donor)):
        if mask[index] or donor[index] == window[index]:
            continue
        shown += 1
        if shown > 24:
            lines.append("| ... | | |")
            break
        lines.append(f"| +0x{index:03X} | {donor[index]:02X} | {window[index]:02X} |")
    lines.append("")
    lines.append("## Steps")
    lines.append("")
    lines.append("```sh")
    lines.append(f"mkdir -p {Path(target_source).parent}")
    lines.append(f"cp reference/open-bfme-1/{source} \\")
    lines.append(f"   {target_source}")
    lines.append(f"git add -- {target_source}")
    lines.append("# apply the difference above, then resolve the call sites:")
    lines.append(f"python3 tools/decode_calls.py '{entry['name']}' "
                 f"--rva 0x{entry['bfme2_rva']:08X} --source {target_source}")
    lines.append("# check each suggested pin, append it to reverse/symbols.csv (LF only), then:")
    lines.append(f"python3 tools/add_match.py '{entry['name']}' 0x{entry['bfme2_rva']:08X} "
                 f"{entry['size']} {target_source} \\")
    lines.append(f"    --notes 'BFME1 near-miss donor; b1 0x{entry['bfme1_rva']:08X}; "
                 f"{entry['klass']} drift'")
    lines.append("```")
    lines.append("")
    lines.append("If it will not come back, revert and record the verdict rather than leaving")
    lines.append("a nonmatching body in Code/:")
    lines.append("")
    lines.append("```sh")
    lines.append(f"git checkout -- reverse/ && rm -f {target_source}")
    lines.append(f"python3 tools/re_log.py record '{entry['name']}' 0x{entry['bfme2_rva']:08X} "
                 f"{entry['size']} partial 'bfme1_sweep near miss; <what is still wrong>' "
                 f"--stash <your .cpp> --score 0.9")
    lines.append("```")
    lines.append("")
    return "\n".join(lines)


def do_near(args):
    payload = load_matches()
    served = near_candidates(payload, include_held=args.include_held, limit=args.limit)
    if args.source:
        matches = [e for e in served if args.source in e["source"] or args.source == e["name"]]
        if not matches:
            raise SystemExit(f"bfme1_sweep: no served near candidate matches {args.source!r}")
        print(near_packet(matches[0]))
        return 0
    if args.json:
        print(json.dumps([{k: v for k, v in e.items()
                           if k not in ("donor", "window", "fields")} for e in served], indent=1))
        return 0
    total = sum(e["size"] for e in served)
    print(f"{len(served)} near candidate(s), {total} bytes, "
          f"classes served: {', '.join(NEAR_SERVED)}")
    print()
    print(f"{'align':>6}  {'bytes':>5}  {'class':<15} {'b2 rva':<10} source")
    for entry in served:
        print(f"{entry['alignment'] * 100:5.1f}%  {entry['size']:>5}  {entry['klass']:<15} "
              f"0x{entry['bfme2_rva']:08X} {entry['source']}")
    if served:
        print()
        print(f"next: python3 tools/bfme1_sweep.py near --show '{served[0]['name']}'")
    return 0


def do_show(args):
    served = group_files(load_matches(), include_refused=True, include_held=True)
    print(packet_text(find_entry(served, args.source)))
    return 0


def remove_rows(source):
    """Drop every ledger row claiming `source`, keeping the file's own terminators."""
    text = BFME2_LEDGER.read_bytes().decode("utf-8")
    kept = [row for row in text.split("\n") if f",{source}," not in row]
    BFME2_LEDGER.write_bytes("\n".join(kept).encode("utf-8"))


def do_land(args):
    """Copy one donor file, append its pins, claim its bodies, build.

    add_match.py already verifies each row and puts the ledger back when the
    row does not byte-match, so all this owns is the copy and the pin lines --
    and putting those back, which it does before it reports anything.
    """
    payload = load_matches()
    served = group_files(payload, include_refused=args.include_refused, include_held=True)
    entry = find_entry(served, args.source, near=near_candidates(payload, include_held=True))
    if entry["copy_tier"] in HELD_COPY_TIERS:
        raise SystemExit(f"bfme1_sweep: held (copy-tier {entry['copy_tier']}): {entry['copy_note']}")
    if entry.get("import_alias") and not args.ignore_import_alias:
        raise SystemExit(
            f"bfme1_sweep: {entry['import_alias']}\n"
            "  Fix the declaration in the copy, then land it by hand; "
            "--ignore-import-alias to try anyway.")
    wanted = ("T1", "T2", "T3") if args.allow_icf else ("T1", "T2")
    bodies = [body for body in entry["bodies"] if body["tier"] in wanted]
    if not bodies:
        raise SystemExit(f"bfme1_sweep: {entry['source']} has no T1/T2 body "
                         "(pass --allow-icf to land its ICF-named ones)")
    if entry["policy"] == "refused":
        raise SystemExit(f"bfme1_sweep: refused — {entry['policy_note']}")
    if entry["copy_tier"] == "D":
        raise SystemExit(f"bfme1_sweep: {entry['copy_note']} — land this one by hand "
                         "under a distinct TU name")

    source = entry["source"]
    donor = BFME1 / source
    target_source = bfme2_source_path(source)
    dest = ROOT / target_source
    pins = sorted({(name, address) for body in bodies for name, address in body["pins"]})

    print(f"donor  {donor.relative_to(ROOT)}")
    print(f"dest   {target_source}  (copy-tier {entry['copy_tier']}: {entry['copy_note']})")
    for name, address in pins:
        print(f"pin    {name},0x{address:08X}")
    for body in bodies:
        print(f"claim  0x{body['bfme2_rva']:08X} {body['size']:>5}B  {body['name']}")
    if args.dry_run:
        print("--dry-run: nothing written")
        return 0

    if dest.exists():
        raise SystemExit(f"bfme1_sweep: {source} already exists — landing would overwrite a "
                         "body this repo owns; resolve it by hand")
    symbols_before = BFME2_SYMBOLS.read_bytes() if BFME2_SYMBOLS.exists() else None
    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(donor, dest)
    # check_csv refuses a row whose source is untracked, so the copy is staged
    # as part of making it: an unstaged donor is a ledger error, not a file the
    # committer will notice later.
    subprocess.run(["git", "add", "--", target_source], cwd=ROOT, check=True)
    if pins:
        with BFME2_SYMBOLS.open("a", encoding="utf-8", newline="") as handle:
            for name, address in pins:
                handle.write(f"{name},0x{address:08X}\n")

    landed = []
    try:
        for body in bodies:
            command = [sys.executable, str(ROOT / "tools" / "add_match.py"), body["name"],
                       f"0x{body['bfme2_rva']:08X}", str(body["size"]), target_source,
                       "--notes", ledger_note(body)]
            result = subprocess.run(command, cwd=ROOT)
            if result.returncode != 0:
                raise RuntimeError(f"add_match refused {body['name']} at 0x{body['bfme2_rva']:08X}")
            landed.append(body)
    except (RuntimeError, KeyboardInterrupt) as error:
        print(f"bfme1_sweep: {error}", file=sys.stderr)
        if not landed:
            subprocess.run(["git", "rm", "--cached", "--quiet", "--", target_source], cwd=ROOT)
            dest.unlink(missing_ok=True)
            if symbols_before is not None:
                BFME2_SYMBOLS.write_bytes(symbols_before)
            print("bfme1_sweep: reverted the copy and the pins; the ledger was never written.",
                  file=sys.stderr)
        else:
            print(f"bfme1_sweep: {len(landed)} row(s) DID land and are verified — keep them, "
                  "and record the refusal for the rest:", file=sys.stderr)
            for body in bodies[len(landed):]:
                print(f"  python3 tools/re_log.py record '{body['name']}' "
                      f"0x{body['bfme2_rva']:08X} {body['size']} no-match "
                      "'bfme1_sweep donor: <what cl did instead>'", file=sys.stderr)
        return 1

    # The pre-commit hook refuses a source defining any function the ledger
    # lacks. Run its own check now, while the file is still ours to unwind,
    # rather than leave a staged file the commit will reject. The heuristic in
    # group_files predicts this; this is the ground truth.
    #
    # `--staged` reads the ledger from the git INDEX, and add_match only ever
    # writes the working tree. Without staging the ledger first the check judges
    # a file against a ledger that does not yet hold its rows and reports "ZERO
    # matched rows" for a body that just verified -- which wave 2 did seven times
    # in a row, unwinding good files. Stage it, then ask.
    subprocess.run(["git", "add", "--", "reverse/functions.csv"], cwd=ROOT, check=True)
    declared = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "find_declared_unmatched.py"), "--fail",
         "--staged", target_source], cwd=ROOT, capture_output=True, text=True)
    if declared.returncode != 0:
        remove_rows(target_source)
        subprocess.run(["git", "add", "--", "reverse/functions.csv"], cwd=ROOT, check=True)
        subprocess.run(["git", "rm", "--cached", "--quiet", "--", target_source], cwd=ROOT)
        dest.unlink(missing_ok=True)
        print(f"bfme1_sweep: {target_source} defines functions the ledger does not declare, which the "
              "pre-commit hook refuses. Rows and copy reverted (pins kept: they are additive "
              "and later files may resolve through them):", file=sys.stderr)
        print("\n".join(declared.stdout.splitlines()[:6]), file=sys.stderr)
        return 1
    # A pin is an additive candidate, and a wrong one still byte-matches -- the
    # gate proves nothing about it. This is the check AGENTS.md asks for, run
    # here so `land` cannot leave a fresh inconsistency behind unreported.
    if pins:
        check = subprocess.run([sys.executable, str(ROOT / "tools" / "pin_consistency.py"), "--check"],
                               cwd=ROOT)
        if check.returncode != 0:
            print("bfme1_sweep: the rows verified but pin_consistency --check now fails. The "
                  "pins this landed are suspect even though the bytes match; resolve them "
                  "before committing.", file=sys.stderr)
            return 1
    print(f"landed {len(landed)} row(s) from {source}")
    return 0


def drainable(entry, wanted):
    """Whether `land` would even try this file, without running it.

    Mirrors do_land's early refusals, so the drain loop reports a queue length
    that means something rather than counting files it is about to skip.
    """
    if entry["copy_tier"] in HELD_COPY_TIERS or entry["copy_tier"] == "D":
        return False
    if entry["policy"] == "refused" or entry.get("import_alias"):
        return False
    return any(body["tier"] in wanted for body in entry["bodies"])


def do_drain(args):
    """Land every donor the gates allow, one file at a time, and keep going.

    `land` is the unit of work and owns its own unwind, so all this adds is the
    loop and a verdict at the end. A refusal is data: it is counted and the next
    file is tried, because the queue refills from elsewhere -- rows landing in
    other lanes, a donor submodule bump, a matcher fix -- and a queue that stops
    at the first hard file is a queue nobody drains.

    Each file is landed through a fresh do_land, which re-reads the ledger. That
    matters: every row this loop lands changes what the next body_tier call
    decides, and a queue planned once up front goes stale after the first file.
    """
    wanted = ("T1", "T2", "T3") if args.allow_icf else ("T1", "T2")
    queue = [entry["source"] for entry in
             group_files(load_matches(), include_refused=False, include_held=False)
             if drainable(entry, wanted)]
    if args.limit:
        queue = queue[: args.limit]
    if not queue:
        print("bfme1_sweep: nothing to drain — the served queue is empty")
        return 0
    print(f"{len(queue)} donor file(s) to try\n")

    landed = skipped = failed = 0
    for position, source in enumerate(queue, 1):
        print(f"--- [{position}/{len(queue)}] {source}", flush=True)
        request = argparse.Namespace(
            source=source, allow_icf=args.allow_icf, include_refused=False,
            ignore_import_alias=False, dry_run=args.dry_run)
        try:
            code = do_land(request)
        except SystemExit as refusal:
            print(f"    skipped: {refusal}", flush=True)
            skipped += 1
            continue
        if code:
            failed += 1
        else:
            landed += 1
    if args.dry_run:
        print(f"\n--dry-run: {landed} file(s) would be tried, {skipped} skipped before it ran")
        return 0
    print(f"\ndrained: {landed} file(s) landed, {failed} refused by the build, "
          f"{skipped} skipped before it ran")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)

    scan = sub.add_parser("scan", help="compare the two retail images")
    scan.add_argument("--min-size", type=int, default=MIN_FUNC)
    # Measured 3,082 on 2026-09-18 against the 1.03/1.06 baselines, up from
    # 2,837 when explain() required both sides to derive the same field map.
    # The floor sits a few percent under it so ordinary ledger churn does not
    # trip it, and RAISE it when a re-measure comes in higher -- a floor that
    # never moves stops being a check.
    scan.add_argument("--control-floor", type=int, default=4100,
                      help="fail if fewer placements reproduce a boundary this repo already matched")
    scan.set_defaults(func=do_scan)

    ranked = sub.add_parser("ranked", help="the donor queue, best first")
    ranked.add_argument("--limit", type=int, default=40)
    ranked.add_argument("--json", action="store_true")
    ranked.add_argument("--tier", action="append", choices=["T1", "T2", "T3"])
    ranked.add_argument("--copy-tier", action="append", choices=sorted(COPY_ORDER))
    ranked.add_argument("--include-held", action="store_true",
                        help="also list donors held out by a commit gate (tiers L, P, S)")
    ranked.add_argument("--include-refused", action="store_true",
                        help="also list donors held out on licence grounds")
    ranked.set_defaults(func=do_ranked)

    packets = sub.add_parser("packets", help="write one work packet per donor file")
    packets.add_argument("--limit", type=int, default=200)
    packets.add_argument("--include-refused", action="store_true")
    packets.set_defaults(func=do_packets)

    show = sub.add_parser("show", help="print one donor file's packet")
    show.add_argument("source")
    show.set_defaults(func=do_show)

    drain = sub.add_parser("drain", help="land every served donor, one after another")
    drain.add_argument("--limit", type=int, default=0, help="stop after this many files")
    drain.add_argument("--allow-icf", action="store_true",
                       help="also land T3 bodies, whose name is an ICF guess")
    drain.add_argument("--dry-run", action="store_true")
    drain.set_defaults(func=do_drain)

    ambig = sub.add_parser("ambiguous",
                           help="ambiguous donors the BFME1->BFME2 address map resolves")
    ambig.add_argument("--window", type=int, default=ANCHOR_WINDOW)
    ambig.add_argument("--min-size", type=int, default=32)
    ambig.add_argument("--limit", type=int, default=25)
    ambig.add_argument("--json", action="store_true")
    ambig.set_defaults(func=do_ambiguous)

    near = sub.add_parser("near", help="donors that ALMOST match, for hand repair")
    near.add_argument("--show", dest="source", metavar="NAME_OR_PATH",
                      help="print one candidate's packet")
    near.add_argument("--limit", type=int, default=40)
    near.add_argument("--json", action="store_true")
    near.add_argument("--include-held", action="store_true")
    near.set_defaults(func=do_near)

    land = sub.add_parser("land", help="copy, pin, claim and build one donor file")
    land.add_argument("source")
    land.add_argument("--dry-run", action="store_true")
    land.add_argument("--allow-icf", action="store_true",
                      help="also land bodies whose name is an ICF guess")
    land.add_argument("--include-refused", action="store_true")
    land.add_argument("--ignore-import-alias", action="store_true",
                      help="land despite a suspected import-name alias")
    land.set_defaults(func=do_land)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
