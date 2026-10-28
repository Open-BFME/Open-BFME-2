#!/usr/bin/env python3
"""Report how much of game.dat we can rebuild from what the repository holds.

The README card and the Discord post (tools/readme_progress.py) draw their
figures from the functions here, so this prints the same figures: BYTE-MATCHED
("Byte match"), GAME CODE C++* (its parts are broken out as AUTHORED C++),
LINKING ("Builds normally") with STRICT BLOCKERS (its "problems
left"), then READABLE NAMES (worktree only),
SHORTCUTS, FILE LAYOUT and SHARED CLASSES, the last three counted from the start
of Phase 2 (PHASE2_START). BYTE-MATCHED ("rebuilt from source") is everything that rebuilds
to game.dat's exact bytes (authored and generated C++, vendored source,
attached prebuilt libraries, reviewed assembly and verified data in .text; dumps excluded), over
all non-padding .text bytes. Embedded data has its own lane, never authored
function-code credit. GAME CODE C++* includes authored and generated C++ plus
intentionally retained reviewed assembly over executable game code (excluding
libraries and embedded data). LINKING counts executable game code in clean
files, including generated C++ and assessed reviewed assembly, over the census
tree's executable game code. Both sides use the same snapshot. Historical
authored-only totals remain available when inclusive evidence is unavailable.
SOURCE FILES and TU-APPROVED, after them, track source recovery: Code/'s
file count against the retail translation units reverse/tu_map.csv names, and
the approved rows a merge may move. LINKED, under them, is linked own source (authored and vendored) in clean
files over all own source. Every figure counts 0xCC padding out, the way the
denominator does, so the breakdown under them adds up to them. Total exact, at
the end, uses the full .text and includes dumps: bounded coverage, not progress.

Every retail byte is counted once. Clean C++ ownership wins when it overlaps an
assembly-backed row (including ICF aliases), leaving "ASM-only" as actionable
porting debt. This reads the ledger but compiles nothing; build.sh is proof.

  python3 tools/progress.py                # HEAD vs worktree
  python3 tools/progress.py REF            # REF vs worktree
  python3 tools/progress.py REF1..REF2     # between two commits
  python3 tools/progress.py --details REF  # include ledger diagnostics
"""
import argparse
import csv
import re
import subprocess
import tempfile
from collections import Counter
from functools import lru_cache
from pathlib import Path

import build
from gaps import padding_split
from list_naked_candidates import NAKED_RE, block_bytes, symbol_comment

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"
CPP_SUFFIXES = {".c", ".cc", ".cpp", ".cxx"}
ASM_SUFFIXES = {".asm", ".s"}
# A prebuilt static library the game linked. On the code axis it counts with
# assembly, not with clean C++: nobody wrote or ported these bytes, they are
# matched against the shipped binary. On the identity axis vendor/ already
# routes it to the vendored lane.
LIB_SUFFIXES = {".lib"}
# Upstream libraries vendored into the tree. Reproducing their bytes is real
# code, but it is not recovering this game's identity, so they get their own
# lane instead of inflating the reverse-engineered figure. EA-authored
# libraries (EAC, DirtySock, debug) are the game and stay out of this list.
VENDORED_ROOTS = (
    "Code/Libraries/Source/DirectX/",
    "Code/Libraries/Source/CRT/VS2003/",
    "Code/Libraries/Source/Compression/LZHCompress/",
    "Code/Libraries/Source/Compression/ZLib/",
    "Code/Libraries/Source/JPEG/",
    "Code/Libraries/Source/LibPNG/",
    "Code/Libraries/Source/Lua/",
    "vendor/",
    # Microsoft's static CRT, read straight out of the tracked MSVC 7.1
    # toolchain rather than copied under vendor/. Same lane as vendor/d3dx9:
    # Microsoft compiled it, so it is not this game's identity.
    "build/toolchains/",
    # EA's Zero Hour source, compiled verbatim out of the pristine reference
    # tree the project is forbidden to modify. A row sourced here was not
    # written from this game's disassembly -- it is another game's source that
    # happens to compile to the same bytes -- so it belongs beside the other
    # upstreams rather than in the reverse-engineered figure. (EA-authored
    # libraries that BFME itself ships under Code/ are the game and stay out.)
    # Both submodule layouts are listed, not just the current one: these are
    # prefixes of ledger `source` values, so dropping the legacy spelling
    # would silently reclassify any row recorded before upstream's move.
    "reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/",
    "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/",
    "reference/open-bfme-1/inputs/toolchains/",
)
# GameSpy's SDK is the one vendored library that cannot be routed by directory:
# EA dropped its C sources straight into the game's own C++ directory, so
# GameSpy/gp/gp.c sits beside this project's GameSpy/GSConfig.cpp. Extension is
# the discriminator EA's layout leaves us -- every one of the 36 .c files under
# this root carries the SDK's own banner, every .cpp beside them is this game's,
# and Code/ holds no other .c outside VENDORED_ROOTS. Checked, not assumed:
#   find Code -name '*.c' | grep -v <the vendored roots>   ->  empty
VENDORED_C_ROOTS = ("Code/GameEngine/Source/GameNetwork/GameSpy/",)
# Files a generator writes: one body per retail funclet, thunk or template
# instance, with a synthetic name. Path and note are both checked so a
# generator cannot move the recovered figure by omitting its own marker.
GENERATED_ROOTS = ("Code/gen_small/", "Code/gen_asm/")
GEN_NOTE_RE = re.compile(r"(?:^|;)\s*gen-[a-z]|identity=generated\b")
# Provenance lanes, best evidence first. Overlapping claims on one byte resolve
# to the earliest lane, so the lanes partition Total exact with no double count.
# Explicitly reviewed, reconstructed assembly; never admit entire dump directories or
# all .asm files by extension. Admission needs documented machine-ABI/codegen
# evidence plus complete byte/relocation verification. This is metric credit only,
# not authored-C++ credit, permission to lift code, or a verification exemption.
REBUILT_ASM_SOURCES = frozenset({
    "Code/Libraries/Source/VP6/MmxIDct.asm",  # five clean-room MMX bodies
    "Code/masm_dumps/SecurityCookieCheck.asm",  # documented CRT assembly entry
    "Code/Libraries/Source/CRT/RuntimeRelativeDispatchCores.asm",  # verified return-PC/flags ABI
    "Code/Libraries/Source/CRT/RuntimeRelativeDispatchEntries.asm",  # proven paired core calls
    "Code/masm_dumps/VersionSignatureCheckPatched.asm",  # documented patched-target exception
})
SOURCE_LANES = ("authored", "vendored", "generated", "library", "data", "assembly", "dump")
EMIT_RE = re.compile(
    r"\b_{1,2}emit\s+(?:0x([0-9a-fA-F]{1,2})|([0-9a-fA-F]{1,3})h)\b",
    re.IGNORECASE,
)
ASM_BLOCK_RE = re.compile(r"^\s*__asm\b")
# Prefilter for sources worth scanning: naked bodies or emitted bytes. Plain
# "_emit" also hits "__emit"; a false hit only costs reading one extra file.
ASM_MARKER_GREP = r"__declspec[[:space:]]*\([[:space:]]*naked|_emit"


@lru_cache(maxsize=None)
def _functions_text(ref):
    """Return the whole ledger as text for one repository state."""
    if ref is None:
        return (ROOT / FUNCTIONS).read_text(encoding="utf-8")
    proc = subprocess.run(
        ["git", "show", f"{ref}:{FUNCTIONS}"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode != 0:
        raise SystemExit(f"cannot read {FUNCTIONS} at {ref}: {proc.stderr.strip()}")
    return proc.stdout


def matched_at(ref):
    """Return {(name, target_rva): (size, source)} for one repository state."""
    out = {}
    for row in csv.DictReader(_functions_text(ref).splitlines()):
        if row["status"] == "matched":
            out[(row["name"], row["target_rva"])] = (
                int(row["target_size"]), row["source"])
    return out


def notes_at(ref):
    """Return {(name, target_rva): notes} for the matched rows at one state."""
    return {
        (row["name"], row["target_rva"]): row["notes"]
        for row in csv.DictReader(_functions_text(ref).splitlines())
        if row["status"] == "matched"
    }


def retail_text():
    """Return (start RVA, byte size) using the build gate's PE parser/baseline."""
    sections = build.pe_sections(build.EXE.read_bytes())
    text = next((section for section in sections if section["name"] == ".text"), None)
    if text is None:
        raise SystemExit(f"{build.EXE}: no .text section")
    return text["rva"], text["size"]


def merge_intervals(intervals):
    """Return sorted, non-overlapping half-open intervals."""
    merged = []
    for start, end in sorted(intervals):
        if start >= end:
            continue
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
        else:
            merged.append((start, end))
    return merged


def interval_bytes(intervals):
    return sum(end - start for start, end in merge_intervals(intervals))


def source_kind(source):
    suffix = Path(source).suffix.lower()
    if suffix in CPP_SUFFIXES:
        return "cpp"
    if suffix in ASM_SUFFIXES or suffix in LIB_SUFFIXES:
        return "asm"
    raise SystemExit(
        f"matched source has unsupported suffix {suffix or '<none>'}: {source}")


def _is_naked_declaration(lines, index):
    """True for an explicit-instantiation declaration with no function body."""
    for line in lines[index:]:
        brace = line.find("{")
        semicolon = line.find(";")
        if semicolon >= 0 and (brace < 0 or semicolon < brace):
            return True
        if brace >= 0:
            return False
    return True


def _signature_identity(name):
    """Return a conservative source-level Class::method spelling, when simple."""
    special = re.match(r"^\?\?([014])([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if special:
        code, cls = special.groups()
        method = {"0": cls, "1": f"~{cls}", "4": "operator="}[code]
        return f"{cls}::{method}"
    normal = re.match(r"^\?([A-Za-z_][A-Za-z0-9_]*)@([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if normal:
        return f"{normal.group(2)}::{normal.group(1)}"
    c_name = re.match(r"^_([A-Za-z_][A-Za-z0-9_]*)$", name)
    return c_name.group(1) if c_name else None


@lru_cache(maxsize=None)
def scan_naked_bodies(text):
    """Return proven asm implementation evidence without treating a file as a unit.

    Triggers on __declspec(naked) bodies and on bare __asm blocks. A bare
    __asm block is evidence only when it emits raw bytes: mnemonic-only inline
    asm inside real C++ (the period cpuid idiom) stays C++, and 18 fleet lifts
    proved plain functions can smuggle a full __emit spray past a naked-only
    scan and inflate the C++ figure."""
    lines = text.splitlines()
    bodies = []
    last_end = -1
    for index, line in enumerate(lines):
        if index <= last_end:
            continue
        naked = bool(NAKED_RE.search(line)) and not _is_naked_declaration(lines, index)
        if not naked and not ASM_BLOCK_RE.match(line):
            continue
        _, end = block_bytes(lines, index)
        emitted = []
        for body_line in lines[index:end + 1]:
            for match in EMIT_RE.finditer(body_line):
                emitted.append(int(match.group(1) or match.group(2), 16))
        if not naked and not emitted:
            continue
        last_end = end
        declaration = []
        for declaration_line in lines[index:end + 1]:
            before_brace, brace, _ = declaration_line.partition("{")
            declaration.append(before_brace)
            if brace:
                break
        bodies.append({
            "symbol": symbol_comment(lines, index),
            "signature": " ".join(" ".join(declaration).split()),
            "emitted": bytes(emitted),
            "naked": naked,
        })
    return tuple(bodies)


def naked_cpp_rows(matched, source_texts, target_reader=build.read_target_bytes):
    """Return matched-row keys proven to be naked assembly inside C/C++ files."""
    rows_by_source = {}
    for key, value in matched.items():
        if Path(value[1]).suffix.lower() in CPP_SUFFIXES:
            rows_by_source.setdefault(value[1], []).append((key, value))

    naked = set()
    target_cache = {}
    for source, text in source_texts.items():
        rows = rows_by_source.get(source, [])
        bodies = scan_naked_bodies(text)
        if not rows or not bodies:
            continue
        # Name and signature evidence is only trusted from naked bodies: a
        # bare __asm spray sits inside an ordinary function whose declaration
        # matches its row by construction. Sprays interleave __emit bytes with
        # real mnemonics at relocated call sites, so full byte equality cannot
        # prove them either; the discriminator is emitted mass. The period
        # _emit idiom (cpuid) is a few bytes of a body, a lift is most of it.
        naked_bodies = [body for body in bodies if body["naked"]]
        symbols = {body["symbol"] for body in naked_bodies if body["symbol"]}
        emitted = {body["emitted"] for body in bodies if body["emitted"]}
        signatures = [body["signature"] for body in naked_bodies]
        spray_mass = sum(len(body["emitted"]) for body in bodies if not body["naked"])
        for key, (size, _) in rows:
            name, target_rva = key
            identity = _signature_identity(name)
            proven = name in symbols or (
                identity is not None and any(
                    re.search(rf"(?<![A-Za-z0-9_]){re.escape(identity)}\s*\(", signature)
                    for signature in signatures))
            if not proven and emitted:
                target_key = (int(target_rva, 16), size)
                if target_key not in target_cache:
                    target_cache[target_key] = target_reader(*target_key)
                proven = target_cache[target_key] in emitted
            if proven or (len(rows) == 1 and len(naked_bodies) == 1) or \
                    (len(rows) == 1 and spray_mass * 2 >= size):
                naked.add(key)
    return naked


def _batch_git_blobs(ref, paths, missing_ok=False):
    """{path: bytes} of `paths` at `ref`, through one git cat-file; a path the
    tree lacks is left out when `missing_ok`, else refused."""
    if not paths:
        return {}
    request = "".join(f"{ref}:{path}\n" for path in paths).encode()
    # Avoid a cycle where Git's reply pipe and the request pipe both fill.
    with tempfile.TemporaryFile() as source, tempfile.TemporaryFile() as output, \
            tempfile.TemporaryFile() as errors:
        source.write(request)
        source.seek(0)
        proc = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT,
                              stdin=source, stdout=output, stderr=errors)
        output.seek(0)
        errors.seek(0)
        proc = subprocess.CompletedProcess(proc.args, proc.returncode,
                                           output.read(), errors.read())
    if proc.returncode != 0:
        raise SystemExit(f"cannot read naked sources at {ref}: {proc.stderr.decode().strip()}")
    output = proc.stdout
    offset = 0
    texts = {}
    for path in paths:
        line_end = output.find(b"\n", offset)
        if line_end < 0:
            raise SystemExit(f"cannot read {path} at {ref}: malformed git cat-file output")
        header = output[offset:line_end].decode(errors="replace")
        offset = line_end + 1
        if missing_ok and header.endswith(" missing"):
            continue
        fields = header.rsplit(" ", 2)
        if len(fields) != 3 or fields[1] != "blob":
            raise SystemExit(f"cannot read {path} at {ref}: {header}")
        size = int(fields[2])
        texts[path] = output[offset:offset + size]
        offset += size + 1  # blob plus cat-file's separating newline
    return texts


def _batch_git_texts(ref, paths):
    return {path: blob.decode("utf-8", errors="replace") for path, blob in _batch_git_blobs(ref, paths).items()}


def naked_source_texts(matched, ref):
    """Read only matched C/C++ sources containing naked bodies at one state."""
    sources = {
        source for _, source in matched.values()
        if Path(source).suffix.lower() in CPP_SUFFIXES
    }
    if ref is None:
        grep = subprocess.run(
            ["git", "grep", "-l", "-E", ASM_MARKER_GREP, "--", "Code"],
            cwd=ROOT, capture_output=True, text=True,
        )
        if grep.returncode not in (0, 1):
            raise SystemExit(f"cannot scan worktree naked sources: {grep.stderr.strip()}")
        paths = set(grep.stdout.splitlines()) & sources
        tracked = set(subprocess.run(
            ["git", "ls-files", "-z", "--", "Code"], cwd=ROOT,
            capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        changed = set(subprocess.run(
            ["git", "diff", "--name-only", "-z", "HEAD", "--", "Code"],
            cwd=ROOT, capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        disk_paths = paths & (changed | (sources - tracked))
        for source in (changed & sources) | (sources - tracked):
            if not (ROOT / source).is_file():
                raise SystemExit(f"cannot read matched source {source}")
        texts = _batch_git_texts("HEAD", sorted(paths - disk_paths))
        for source in sources - tracked:
            text = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
            if NAKED_RE.search(text) or EMIT_RE.search(text):
                disk_paths.add(source)
        for source in disk_paths:
            texts[source] = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
        return texts

    proc = subprocess.run(
        ["git", "grep", "-l", "-E", ASM_MARKER_GREP, ref, "--", "Code"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode not in (0, 1):
        raise SystemExit(f"cannot scan naked sources at {ref}: {proc.stderr.strip()}")
    prefix = f"{ref}:"
    paths = []
    for line in proc.stdout.splitlines():
        path = line[len(prefix):] if line.startswith(prefix) else line.split(":", 1)[-1]
        if path in sources:
            paths.append(path)
    return _batch_git_texts(ref, sorted(paths))


def naked_cpp_rows_at(matched, ref):
    return naked_cpp_rows(matched, naked_source_texts(matched, ref))


def coverage(matched, text_start, text_size, naked_rows=(), text_data=()):
    """Return absolute .text coverage for C++, assembly and verified data."""
    text_end = text_start + text_size
    cpp = []
    asm = []
    naked_rows = set(naked_rows)
    for key, (size, source) in matched.items():
        _, target_rva = key
        kind = source_kind(source)
        if kind == "cpp" and key in naked_rows:
            kind = "asm"
        start = max(int(target_rva, 16), text_start)
        end = min(int(target_rva, 16) + size, text_end)
        if start >= end:
            continue
        (asm if kind == "asm" else cpp).append((start, end))

    cpp_bytes = interval_bytes(cpp)
    code_bytes = interval_bytes(cpp + asm)
    data = [(max(start, text_start), min(end, text_end)) for start, end, _ in text_data]
    exact_bytes = interval_bytes(cpp + asm + data)
    return {
        "cpp": cpp_bytes,
        "asm_only": code_bytes - cpp_bytes,
        "data_only": exact_bytes - code_bytes,
        "unmatched": text_size - exact_bytes,
        "exact": exact_bytes,
        "text": text_size,
    }


def source_lane(source, notes, naked):
    """Return the provenance lane for a matched row.

    Provenance asks who wrote the thing the bytes come out of. It is a
    different question from the code axis (which language) and it is the one
    the project is graded on, because only two of the code lanes are source
    anybody recovered.

      authored   C++ we wrote from the disassembly.
      vendored   upstream library source we compile (zlib, JPEG, Lua, STLport,
                 the MSVC CRT sources). Having zlib's source is having it.
      generated  C++ a generator wrote (Code/gen_small/): EH funclets,
                 small thunks, template grids.
      library    a prebuilt .lib we attach (d3dx9, CRT). It links, so it is a
                 real way to reach 1:1, but there is no source in the tree.
      assembly   explicitly reviewed reconstructed assembly, not C++ or a dump.
      dump       retail re-encoded: MASM `db` bodies and __emit sprays. These
                 fix an address and an extent and say nothing else.

    `generated` is the one arguable lane and it is deliberately NOT recovered.
    Those bodies compile from real constructs -- a tail call is a tail call,
    and the funclets fall out of MSVC's codegen rather than out of a hex dump
    -- so they are not scaffolding either, which is why they get a line of
    their own instead of being buried. They are excluded because a script
    writes them: 85,000 of the ledger's rows came from running tools/gen_uw.py
    once, and a headline a script can move is the exact failure this metric
    exists to prevent. The rule is the authorship of the source, not the
    provenance of the bytes: a human wrote it, or a program did. Flipping this
    means putting the generators under human review first, and `code: C++`
    below already reports authored and generated together for anyone who wants
    the everything-that-compiles number.
    """
    if Path(source).suffix.lower() in LIB_SUFFIXES:
        return "library"
    if (source_kind(source) == "asm" and source in REBUILT_ASM_SOURCES
            and not GEN_NOTE_RE.search(notes)):
        return "assembly"
    if naked or source_kind(source) == "asm":
        return "dump"
    if source.startswith(GENERATED_ROOTS) or GEN_NOTE_RE.search(notes):
        return "generated"
    if source.startswith(VENDORED_ROOTS):
        return "vendored"
    if source.startswith(VENDORED_C_ROOTS) and Path(source).suffix.lower() == ".c":
        return "vendored"
    return "authored"


def source_split(matched, notes, text_start, text_size, naked_rows=()):
    """Return .text bytes per provenance lane; the lanes sum to Total exact.

    An ICF alias claimed twice resolves to the earlier lane, the way clean C++
    wins an overlap on the code axis: the byte is credited to whichever claim
    says the most about it.
    """
    text_end = text_start + text_size
    naked_rows = set(naked_rows)
    lanes = {name: [] for name in SOURCE_LANES}
    for key, (size, source) in matched.items():
        start = max(int(key[1], 16), text_start)
        end = min(int(key[1], 16) + size, text_end)
        if start >= end:
            continue
        lane = source_lane(source, notes[key], key in naked_rows)
        lanes[lane].append((start, end))
    split, claimed = {}, []
    for name in SOURCE_LANES:
        before = interval_bytes(claimed)
        claimed += lanes[name]
        split[name] = interval_bytes(claimed) - before
    split["recovered"] = split["authored"] + split["vendored"]
    return split


def real_code_denominator(text_start, text_size):
    """Return (0xCC padding bytes, real code bytes) across the whole section.

    This is the denominator the porting effort is actually measured against:
    3.3 MB of the section is inter-function 0xCC filler that no one will ever
    port, including a single 982,242-byte block at 0xB028EE. Counted over the
    whole section rather than over unclaimed gaps so the denominator does not
    drift every time a function is matched.
    """
    return padding_split(build.read_target_bytes(text_start, text_size))


# Text widths for the README card and the progress site's SVGs, which declare
# FONT_STACK and nothing else: every face in it was measured. GLYPH_EM is each
# character's advance in thousandths of an em, rounded up: the widest of the
# five faces the SVGs draw with (weights 400, 600 and 700), read from the hmtx
# tables by a struct-only reader (2048 units an em):
#   Segoe UI 5.72          segoeui.ttf  704eada12961a27fd271f7d3b09e2066520e758390c1776744eff430fee30f6e
#   Segoe UI Semibold 5.72 seguisb.ttf  6c3fd894b19950b10c34bf64069ef821eaf2f58f959146306fee5b367472e501
#   Segoe UI Bold 5.72     segoeuib.ttf b169e636719880976a97e94e3b1cb3dbe5f4a38eabc037bf9f2a9165154c3ad2
#   Arial 7.06             arial.ttf    b3658eadae55e682b5f69eb64c439c1ecc8f196c0bb8d4756d145d13bc86476a
#   Arial Bold 7.06        arialbd.ttf  e8f4e3baf6cc35fed6fcce3a540e8b39e8f6cda1d22a28f2ec8f526fef7a43f5
# (Windows 11's copies; Arial has no 600, so 600 renders Arial Bold.) Arial's
# metric-compatible substitutes (Liberation Sans, Arimo) share its advances.
# Dropped from the stack: -apple-system, BlinkMacSystemFont and Helvetica (no
# upstream font file to measure; macOS and iOS ship Arial), and Noto Sans
# 2.008 (NotoSans-Regular.ttf b85c38ecea8a7cfb39c24e395a4007474fa5a4fc864f6ee3
# 3309eb4948d232d5), which is wider than both (I 0.339 em, | 0.551 em) and has
# no ▲ ▼ → ≈, so those would come from an unnamed fallback. The generic
# sans-serif is gone too. A viewer with neither face nor a substitute sees the
# user agent's default font, which no table bounds.
FONT_STACK = "'Segoe UI',Arial"
GLYPH_CHARS = (" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
               "abcdefghijklmnopqrstuvwxyz{|}~·▲▼–—→×≈")
GLYPH_EM = dict(zip(GLYPH_CHARS, map(int, """
    278 334 494 593 576 890 850 293 370 370 456 708 278 405 278 444 576 576 576 576 577 576 576 576 576 576
    334 334 708 708 708 611 1016 723 723 723 738 667 611 778 767 317 557 723 611 958 791 778 667 778 723 667
    611 724 667 1005 667 667 611 370 437 370 708 557 334 557 621 557 620 557 384 620 611 285 285 560 285 917
    611 612 621 620 398 557 390 611 557 798 557 557 500 390 327 390 708 334 990 990 557 1000 1000 708 709
    """.split()), strict=True))
# Every SVG text context turns kerning off (NO_KERN), but a renderer may ignore
# that, so text_width also adds KERN_EM: per adjacent pair of GLYPH_CHARS, the
# largest positive kerning over the same five faces, in thousandths of an em,
# rounded up, from the kern table (horizontal format 0 subtables, summed) and
# from GPOS PairPos formats 1 and 2 (first and second xAdvance) in every
# lookup of every 'kern' feature, read by the same struct-only reader; a
# renderer applies one table or the other, so each face counts the larger.
# The only other lookups under 'kern' are Arabic chained contexts whose inputs
# hold none of these glyphs. Pairs that only tighten are absent (0). A per-pair
# table rather than one worst-case allowance per gap: the worst pair, (j in
# Segoe UI (233 units, 0.114 em), would widen every gap of every line by 20%.
KERN_EM = {entry[:2]: int(entry[2:]) for entry in """
    (j114 A,34 A;34 AJ46 AZ30 C?12 EA15 EJ34 ET9 EV5 EW21 EX21 FT13 Ff9 K,30 K;30 K?12 KJ44 KT5 KV20 KW20
    KX25 KY20 KZ21 Kx15 LA30 LJ49 LZ29 PG5 PW20 R;41 RJ28 TT21 TV29 TW21 TY21 V?8 VT21 WT20 X,34 X.29 X;41
    XJ47 XT21 YT21 ZJ41 ZT21 [j114 cJ35 f)69 f*21 f:41 f;41 f?33 f]69 fb16 fh9 fk5 fl5 ft20 fv21 fw21 fx9
    fy21 f}41 gj23 jj18 k,41 k.41 k:41 k;41 kz8 qj50 r:41 r;41 rf25 rh3 ri4 rm3 rn3 rs7 rt29 ru3 rv41 rw41
    rx29 ry41 rz21 tx15 y"15 y'21 y?1 yf8 yt3 {j100
    """.split()}
NO_KERN = 'text-rendering="optimizeSpeed" kerning="0" style="font-kerning:none;font-feature-settings:\'kern\' 0"'


def text_width(text, size):
    """An upper bound on `text`'s width in px at `size` in FONT_STACK, at any
    weight the SVGs use, kerned or not (GLYPH_EM plus KERN_EM per adjacent
    pair); a character with no measured advance is an error, not a guess."""
    unknown = sorted(set(text) - GLYPH_EM.keys())
    if unknown:
        raise ValueError(f"No measured glyph advance for {unknown!r}: add it to GLYPH_EM")
    kern = sum(KERN_EM.get(text[i:i + 2], 0) for i in range(len(text) - 1))
    return size * (sum(GLYPH_EM[char] for char in text) + kern) / 1000


def percent(count, total):
    return 100.0 * count / total if total else 0.0


def format_delta(current, previous, total):
    byte_delta = current - previous
    return f"{byte_delta:+,} bytes, {percent(byte_delta, total):+.2f} pp"


def print_scorecard(ref1, label2, old_stats, new_stats):
    total = new_stats["text"]
    print(f"\nretail .text exact coverage {ref1} -> {label2} ({total:,} bytes)")
    rows = (
        ("C++ exact", "cpp"),
        ("ASM-only exact", "asm_only"),
        ("Data-only exact", "data_only"),
        ("Unmatched", "unmatched"),
        ("Total exact", "exact"),
    )
    for label, key in rows:
        value = new_stats[key]
        delta = format_delta(value, old_stats[key], total)
        print(f"  {label:<15} {value:>10,} bytes ({percent(value, total):6.2f}%)"
              f"  delta {delta}")


def rebuildable(split):
    """Bytes we can produce without consulting retail.

    The project is graded on one question: how much of game.dat can we
    rebuild from what we hold? A byte qualifies when its source of truth lives
    in this repo -- C++ someone wrote, upstream library source we compile, a
    deterministic generator we own, or a prebuilt .lib we attach. Who first
    authored it does not enter into it; nobody at EA hand-wrote the unwind
    funclets either, and a 1:1 build does not require us to hand-write d3dx9.

    Reviewed reconstructed assembly qualifies without increasing C++ credit.
    Verified data in .text qualifies separately from all function-code lanes.
    A byte-true dump is the one lane that fails the test: the source file
    contains retail's own bytes, so deleting game.dat would delete the
    thing we claim to hold. Dumps fix a boundary and say nothing else.
    """
    return (split["authored"] + split["vendored"] + split["generated"] + split["library"]
            + split.get("data", 0) + split.get("assembly", 0))


LINK_STATUS = "reverse/link_status.csv"
LINK_HISTORY = "reverse/link_census_history.csv"
# Source somebody recovered: C++ written from the disassembly and upstream
# library source. Generated C++ stays out, for the reason source_lane gives.
DECOMPILED_LANES = ("authored", "vendored")


def _text_at(ref, path):
    if ref is None:
        target = ROOT / path
        return target.read_text(encoding="utf-8") if target.exists() else None
    result = subprocess.run(["git", "show", f"{ref}:{path}"], cwd=ROOT, capture_output=True,
                            text=True, encoding="utf-8", errors="replace")
    return result.stdout if result.returncode == 0 else None


def text_data_at(ref):
    """Matched data-ledger extents in retail .text, at the requested state.

    Like function coverage, these are gate-verified ledger claims, not a new
    compile during reporting. Old commits without a data ledger contribute zero.
    Non-.text data never contributes to the code-section coverage denominator.
    """
    import data_rows
    raw = _text_at(ref, "reverse/data_rows.csv")
    if raw is None:
        return []
    try:
        rows = data_rows.parse(raw.encode("utf-8"))
        out = []
        for _, row in rows:
            if "_fields" in row:
                raise ValueError("malformed data row")
            if row["status"] != "matched" or row["section"] != ".text":
                continue
            if row["address_kind"] not in ("va", "rva") or int(row["size"]) <= 0:
                raise ValueError("invalid data address kind or size")
            start = data_rows.va_of(row) - data_rows.IMAGE_BASE
            out.append((start, start + int(row["size"]), row["source"]))
        return out
    except ValueError as exc:
        raise SystemExit(f"invalid data_rows.csv at {ref or 'worktree'}: {exc}") from exc


@lru_cache(maxsize=None)
def _text_image():
    start, size = retail_text()
    return start, build.read_target_bytes(start, size)


def real_split(matched, notes, text_start, text_size, naked_rows=(), keep=None, text_data=()):
    """source_split counted the way real_code_denominator counts: 0xCC bytes
    excluded, so numerator and denominator agree (source_split counts a row's
    0xCC bytes, about 0.16 pp of the headline). `keep(key, source)` filters rows."""
    image_start, image = _text_image()
    text_end = text_start + text_size
    naked_rows = set(naked_rows)
    lanes = {name: [] for name in SOURCE_LANES}
    # A function-only filter must never start crediting unrelated data.
    if keep is None:
        lanes["data"] = [(max(start, text_start), min(end, text_end))
                         for start, end, _ in text_data if max(start, text_start) < min(end, text_end)]
    for key, (size, source) in matched.items():
        if keep and not keep(key, source):
            continue
        start, end = max(int(key[1], 16), text_start), min(int(key[1], 16) + size, text_end)
        if start < end:
            lanes[source_lane(source, notes[key], key in naked_rows)].append((start, end))

    def real(intervals):
        return sum(end - start - image[start - image_start:end - image_start].count(0xCC)
                   for start, end in merge_intervals(intervals))
    split, claimed = {}, []
    for name in SOURCE_LANES:
        before = real(claimed)
        claimed += lanes[name]
        split[name] = real(claimed) - before
    return split


def decompiled(split):
    """Recovered source that compiles to retail's bytes, a function at a time."""
    return sum(split[lane] for lane in DECOMPILED_LANES)


def census_rows_at(ref):
    """Every census row that measured LINKED, in physical (append) order."""
    history = _text_at(ref, LINK_HISTORY)
    return [row for row in csv.DictReader(history.splitlines()) if row.get("linked_bytes")] if history else []


def census_at(ref):
    """The last link census that measured LINKED, as of one state, or None.

    LINKED is measured by tools/link_census.py on the tree it linked and stored
    in the history row (linked_bytes); it is not recomputed here, so it holds
    still between censuses instead of dropping with every edit since. The
    last physical row is the current one: rows are appended in order.
    """
    rows = census_rows_at(ref)
    return rows[-1] if rows else None


# The rules a census row was measured under (link_census.py's `rules`
# column). Rows from before the column are link_census.LEGACY_RULES.
LEGACY_CENSUS_RULES = "majority-0"


def census_rules(row):
    return ((row or {}).get("rules") or "").strip() or LEGACY_CENSUS_RULES


def census_prev_figure(row, field):
    """The row's *_prev_rule figure for `field` and the rules it was measured
    under, or (None, None)."""
    value = (row or {}).get(f"{field}_prev_rule")
    if not value:
        return None, None
    return int(value), ((row.get("prev_rules") or "").strip() or LEGACY_CENSUS_RULES)


def census_change(old, new, field, over_field, rows, denominator=None):
    """The change in one census figure from `old` to `new` (history rows),
    compared like for like when the census rules changed in between.

    Returns {"bytes", "pp"} for a same-rules change, plus "rule_changes" (a
    list of (row, before_rules, after_rules, before_pp, after_pp)) when one or
    more re-baseline rows lie in between: the change is then the sum of the
    changes within each rule, the re-baseline's prev_rule figure being the
    old rules' measurement of the same objects. None when no like-for-like
    comparison exists (a rule change without the previous rules' figures)."""
    def pair(row, value=None):
        over = int(row[over_field]) if over_field else denominator
        return (int(row[field]) if value is None else value), over
    if census_rules(old) == census_rules(new) and not _transitions(old, new, rows):
        (a, x), (b, y) = pair(old), pair(new)
        return {"bytes": b - a, "pp": percent(b, y) - percent(a, x), "rule_changes": []}
    changes = _transitions(old, new, rows)
    if not changes:
        return None
    total_bytes, total_pp, current, notes = 0, 0.0, old, []
    for row in changes:
        prev, prev_rules = census_prev_figure(row, field)
        if prev is None or prev_rules != census_rules(current):
            return None
        (a, x), (b, y) = pair(current), pair(row, prev)
        total_bytes += b - a
        total_pp += percent(b, y) - percent(a, x)
        (c, z) = pair(row)
        notes.append((row, prev_rules, census_rules(row), percent(b, y), percent(c, z)))
        current = row
    (a, x), (b, y) = pair(current), pair(new)
    return {"bytes": total_bytes + b - a, "pp": total_pp + percent(b, y) - percent(a, x), "rule_changes": notes}


def _transitions(old, new, rows):
    """The rows after `old`, up to and including `new`, whose rules differ
    from the row before them (re-baselines), in order."""
    keys = [(r.get("date"), r.get("commit")) for r in rows]
    try:
        start = keys.index((old.get("date"), old.get("commit")))
        end = keys.index((new.get("date"), new.get("commit")))
    except ValueError:
        return []
    return [rows[i] for i in range(start + 1, end + 1) if census_rules(rows[i]) != census_rules(rows[i - 1])]


def data_denominator():
    """Bytes of .rdata and .data: the tables, strings and globals."""
    return sum(s["size"] for s in build.pe_sections(build.EXE.read_bytes()) if s["name"] in (".rdata", ".data"))


def game_code(split, denominator):
    """The game's own code: all real code minus vendored library source and
    prebuilt libraries (readme_progress.game_code, the C++ and Linking bars)."""
    return denominator - split["vendored"] - split["library"]


GAME_CPP_RULES = "executable-cpp-and-reviewed-assembly-1"
GAME_CPP_ANNOTATION = "Includes generated C++ and intentionally retained assembly."


def game_executable(split, denominator):
    """Executable game code, excluding libraries and verified embedded data."""
    return game_code(split, denominator) - split.get("data", 0)


def game_represented(split):
    """Blue-bar coverage; provenance lanes still distinguish C++ from assembly."""
    return split["authored"] + split["generated"] + split.get("assembly", 0)


def game_cpp_breakdown(split, denominator):
    """The blue bar's parts, so assembly and generated code are never read as hand-written
    C++: `Of it: authored C++ 96.38%, generated C++ 3.56%, reviewed assembly 0.11% of
    executable game code.` The parts add up to the bar (game_represented); the bar and its
    definition (GAME_CPP_RULES) are unchanged."""
    game = game_executable(split, denominator)
    parts = (("authored C++", split["authored"]), ("generated C++", split["generated"]),
             ("reviewed assembly", split.get("assembly", 0)))
    return ("Of it: " + ", ".join(f"{name} {percent(value, game):.2f}%" for name, value in parts)
            + " of executable game code.")


LINK_COVERAGE_RULES = "executable-game-coverage-1"


def linked_game_coverage(matched, notes, naked, clean, text_start, text_size, data=()):
    """Intersect clean providers with a fixed global provenance partition."""
    lanes = {lane: [] for lane in SOURCE_LANES}
    clean_ranges = []
    for key, (size, source) in matched.items():
        a, b = max(text_start, int(key[1], 16)), min(text_start + text_size, int(key[1], 16) + size)
        if a >= b:
            continue
        lane = source_lane(source, notes[key], key in naked)
        lanes[lane].append((a, b))
        if source in clean and lane != "dump":
            clean_ranges.append((a, b))
    lanes['data'] = [(max(text_start, a), min(text_start + text_size, b))
                     for a, b, _ in data if max(text_start, a) < min(text_start + text_size, b)]
    clean_ranges = merge_intervals(clean_ranges)
    image_start, image = _text_image()

    def linked_real(ranges):
        total, j = 0, 0
        for a, b in merge_intervals(ranges):
            while j < len(clean_ranges) and clean_ranges[j][1] <= a:
                j += 1
            k = j
            while k < len(clean_ranges) and clean_ranges[k][0] < b:
                lo, hi = max(a, clean_ranges[k][0]), min(b, clean_ranges[k][1])
                if lo < hi:
                    total += hi - lo - image[lo-image_start:hi-image_start].count(0xCC)
                k += 1
        return total

    claimed, linked, previous = [], 0, 0
    for lane in SOURCE_LANES:
        claimed = merge_intervals(claimed + lanes[lane])
        current = linked_real(claimed)
        if lane in ('authored', 'generated', 'assembly'):
            linked += current - previous
        previous = current
    full = real_split(matched, notes, text_start, text_size, naked, text_data=data)
    _, denominator = real_code_denominator(text_start, text_size)
    return {'linked_game_executable': linked,
            'game_executable': game_executable(full, denominator),
            'link_coverage_rules': LINK_COVERAGE_RULES}


@lru_cache(maxsize=None)
def linking_coverage_at(ref):
    """New census fields, or a checked recalculation of its committed status.

    Never mix today's ledger with an older census. Old history is left intact.
    Missing or inconsistent historical evidence leaves the old display available.
    """
    census = census_at(ref)
    if not census:
        return None
    fields = ('linked_game_executable', 'game_executable', 'link_coverage_rules')
    if all(census.get(k) not in (None, '') for k in fields):
        return {k: int(census[k]) if k != 'link_coverage_rules' else census[k] for k in fields}
    if not census.get('commit') or not census.get('linked_authored'):
        return None
    state = ref or 'HEAD'
    report = subprocess.run(['git', 'log', '-1', '--format=%H', state, '--', LINK_STATUS],
                            cwd=ROOT, capture_output=True, text=True)
    report_ref = report.stdout.strip()
    if report.returncode or not report_ref:
        return None
    recorded = census_at(report_ref)
    if not recorded or any(recorded.get(k) != census.get(k) for k in ('commit', 'date', 'rules')):
        return None
    raw = _text_at(report_ref, LINK_STATUS)
    if not raw:
        return None
    clean = {r['source'] for r in csv.DictReader(raw.splitlines()) if r['linked'] == 'yes'}
    tree = census['commit']
    try:
        matched, notes = matched_at(tree), notes_at(tree)
        naked = naked_cpp_rows_at(matched, tree)
        start, size = retail_text()
        split = real_split(matched, notes, start, size, naked, keep=lambda key, source: source in clean)
        full = real_split(matched, notes, start, size, naked)
        _, total = real_code_denominator(start, size)
        if (split['authored'] != int(census['linked_authored'])
                or decompiled(split) != int(census['linked_bytes'])
                or game_code(full, total) != int(census['game_code'])):
            return None
        return linked_game_coverage(matched, notes, naked, clean, start, size, text_data_at(tree))
    except (SystemExit, ValueError, KeyError):
        return None


def _line(label, value, denominator, delta, note):
    return (f"{label:<14} {value:>12,.0f} bytes ({percent(value, denominator):6.2f}%)  {delta}  <- {note}")


def print_headline(padding, denominator, old_split, new_split, old_census, new_census, census_rows=(),
                   tool_rules=None):
    """The README card's and the daily Discord post's byte figures, computed
    the same way, then what they are made of. Every figure counts 0xCC out,
    so the lines below add up to the lines above. `tool_rules`: the rules
    tools/link_census.py measures under at the new state (census_tool_rules_at)."""
    matched, before = rebuildable(new_split), rebuildable(old_split)
    game, game_before = game_executable(new_split, denominator), game_executable(old_split, denominator)
    print(_line("BYTE-MATCHED", matched, denominator, f"delta {format_delta(matched, before, denominator)}",
                "rebuilt from source: rebuilds to game.dat's exact bytes"))
    print(_line("GAME CODE C++*", game_represented(new_split), game,
                f"delta {format_delta(game_represented(new_split), game_represented(old_split), game)}"
                if game == game_before else "delta n/a (the game's own code changed size)",
                f"executable game code ({game:,} bytes: libraries and embedded data excluded)"))
    print(f"               * {GAME_CPP_ANNOTATION} {game_cpp_breakdown(new_split, denominator)}")
    print(_line("AUTHORED C++", new_split["authored"], game,
                f"delta {format_delta(new_split['authored'], old_split['authored'], game)}"
                if game == game_before else "delta n/a (the game's own code changed size)",
                "hand-written C++ over executable game code (the authored share under the card's GAME CODE C++*)"))

    def census_line(label, field, over_field, note, over_total=None):
        """One census figure over its denominator: `over_field` names the
        census column holding it, or `over_total`/all code (fixed)."""
        def figure(census):
            if not census or not census.get(field) or (over_field and not census.get(over_field)):
                return None
            return int(census[field]), (int(census[over_field]) if over_field
                                        else (denominator if over_total is None else over_total))
        now = figure(new_census)
        if now is None:
            print(f"{label:<14} not measured  <- no census stored {field} yet (tools/link_census.py --history)")
            return
        # A range that starts before any census has nothing to compare with;
        # showing the whole figure as a gain would credit it to that range.
        was = figure(old_census)
        if not was:
            delta = f"delta n/a (no {label} figure stored at the start of the range)"
        else:
            # A change of census rules is not progress: compare within rules.
            change = (None if field == 'linked_game_executable' and
                      census_rules(old_census) != census_rules(new_census) else
                      census_change(old_census, new_census, field, over_field, list(census_rows) or
                                    [old_census, new_census],
                                    denominator if over_total is None else over_total))
            if change is None:
                delta = (f"delta n/a (census accounting changed: {census_rules(old_census)} -> "
                         f"{census_rules(new_census)}, no like-for-like figure)")
            else:
                delta = f"delta {change['bytes']:+,} bytes, {change['pp']:+.2f} pp"
                for row, before, after, at_before, at_after in change["rule_changes"]:
                    delta += (f" within rules; accounting changed {row['date'][:10]} ({before} -> {after}: "
                              f"{at_before:.2f}% -> {at_after:.2f}% on the same objects, not progress)")
        print(_line(label, now[0], now[1], delta, f"{note}, census {new_census['date']} at {new_census['commit']}"
                    f" ({census_rules(new_census)})"))
    if new_census and new_census.get('link_coverage_rules'):
        census_line('LINKING', 'linked_game_executable', 'game_executable',
                    'verified executable game code in link-clean units, including generated C++ and reviewed assembly')
    else:
        census_line("LINKING", "linked_authored", "game_code",
                    "legacy authored-only accounting (inclusive census evidence unavailable)")
    blockers = strict_blockers(new_census)
    if blockers:
        print(f"{'STRICT BLOCKERS':<15}{blockers['total']:>12,}  <- {blockers['unresolved']:,} unresolved names + "
              f"{blockers['addresses']:,} hard-coded addresses + {blockers['duplicates']:,} duplicate names, census "
              f"{new_census['date']} at {new_census['commit']} (the card's \"problems left\")")
    if new_census and tool_rules and tool_rules != census_rules(new_census):
        print(f"               {CENSUS_TOOL} now measures under {tool_rules}; this census used "
              f"{census_rules(new_census)}: being re-measured")
    print("               (BYTE-MATCHED, LINKING and STRICT BLOCKERS: the card's \"Does it work?\"; "
          "the same figures as the README card and the Discord post)")
    census_line("LINKED", "linked_bytes", None,
                "linked own source in files that link cleanly", over_total=decompiled(new_split))

    print(f"\nreal .text bytes = .text minus {padding:,} bytes of 0xCC padding = {denominator:,} bytes")
    print("  byte-matched, by where its source comes from:")
    for label, key in (("C++ we wrote", "authored"), ("vendored library source", "vendored"),
                       ("generator-written C++", "generated"), ("prebuilt .lib attached", "library"),
                       ("verified data in .text", "data"), ("reviewed assembly", "assembly")):
        print(f"    {label:<24} {new_split.get(key, 0):>10,} bytes ({percent(new_split.get(key, 0), denominator):6.2f}%)"
              f"  delta {format_delta(new_split.get(key, 0), old_split.get(key, 0), denominator)}")
    unclaimed = denominator - sum(new_split.get(lane, 0) for lane in SOURCE_LANES)
    print("  not byte-matched:")
    print(f"    {'still only retail bytes':<24} {new_split['dump']:>10,} bytes "
          f"({percent(new_split['dump'], denominator):6.2f}%)  <- dumps: a boundary, nothing more")
    print(f"    {'unclaimed':<24} {unclaimed:>10,} bytes ({percent(unclaimed, denominator):6.2f}%)"
          "  <- no boundary proven yet")
    own, own_before = decompiled(new_split), decompiled(old_split)
    print(f"  our own source (C++ we wrote + library source) {own:,} bytes ({percent(own, denominator):.2f}%)"
          f"  delta {format_delta(own, own_before, denominator)}")
    print(f"GAME DATA      no aggregate coverage metric  <- {data_denominator():,} bytes of .rdata/.data; individual data-ledger rows are verified")


TU_MAP = "reverse/tu_map.csv"
SOURCE_SUFFIXES = (".cpp", ".c", ".asm")


def source_files_at(ref):
    """Game and library source files under Code/ (.cpp, .c, .asm) at one state
    (None: the index, which is what the next commit holds)."""
    cmd = ["git", "ls-files", "Code"] if ref is None else ["git", "ls-tree", "-r", "--name-only", ref, "Code"]
    out = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True).stdout.splitlines()
    return {path for path in out if path.lower().endswith(SOURCE_SUFFIXES)}


def tu_map_rows_at(ref):
    """(tu_map rows, which map) at one state. The worktree (None) gets the map
    tu_skeleton merges by: the committed one while fresh, else a rebuild from the
    current inputs (tu_map.build, ~25 s). The committed map goes stale with every
    ledger commit (2026-10-28: 10,846 approved code rows committed, 29,908
    rebuilt), so a commit's own map is labelled as such."""
    if ref is None:
        import tu_map
        layout = tu_map.Layout(ROOT)
        if tu_map.check_fresh(layout):
            return [{k: str(v) for k, v in r.items()} for r in tu_map.build(layout)], "current inputs"
        return tu_map.read_csv(layout.out), "current inputs"
    text = _text_at(ref, TU_MAP)
    return (list(csv.DictReader(text.splitlines())) if text is not None else None), f"{TU_MAP} at {ref}"


def source_recovery_at(ref):
    """Source recovery: how many source files there are, how many retail TUs
    the map names, and how far the approved part reaches. A file is homed when
    every code row it holds is approved; it is at its TU when every such row's
    approved TU is the file itself."""
    files = source_files_at(ref)
    table, which = tu_map_rows_at(ref)
    if table is None:
        return {"files": len(files)}
    named, approved, provisional, rows = set(), set(), set(), {}
    total = approved_rows = provisional_rows = 0
    for row in table:
        if row["kind"] != "code":
            continue
        total += 1
        if row["tu"]:
            named.add(row["tu"].lower())
        if row["confidence"] == "approved":
            approved_rows += 1
            approved.add(row["tu"].lower())
            if "provisional" in (row.get("evidence") or "").split():   # tu_map.PROV_TOKEN
                provisional_rows += 1
                provisional.add(row["tu"].lower())
        if row["source"]:
            rows.setdefault(row["source"].lower(), []).append(row)
    homed = at_tu = 0
    for source, held in rows.items():
        if all(r["confidence"] == "approved" for r in held):
            homed += 1
            at_tu += all(r["tu"].lower() == source for r in held)
    return {"files": len(files), "tus": len(named), "approved_tus": len(approved), "rows": total,
            "approved_rows": approved_rows, "provisional_rows": provisional_rows,
            "provisional_tus": len(provisional), "homed": homed, "at_tu": at_tu, "map": which}


def print_source_recovery(old, new):
    """The source-recovery figure: from one file per function back to retail's
    translation units (docs/consolidation.md)."""
    delta = new["files"] - old["files"]
    if "tus" not in new:
        print(f"SOURCE FILES   {new['files']:>12,}  ({delta:+,} files)  <- no {TU_MAP} to measure against")
        return
    print(f"SOURCE FILES   {new['files']:>12,} files  ({delta:+,} files)  <- .cpp/.c/.asm under Code/; "
          f"target: the {new['tus']:,} TUs {TU_MAP} names, approved or proposed")
    # A commit's committed map and a rebuild from current inputs are not like for like.
    change = (f"({new['approved_rows'] - old['approved_rows']:+,} rows)"
              if "map" in old and old["map"].split(" at ")[0] == new["map"].split(" at ")[0]
              else f"(vs {old.get('map', 'no map')}: n/a)")
    print(f"TU-APPROVED    {new['approved_rows']:>12,} rows ({percent(new['approved_rows'], new['rows']):6.2f}%)  "
          f"{change}  <- code rows in an approved TU ({new['approved_tus']:,} of {new['tus']:,} TUs), "
          f"map from {new['map']}; only approved rows merge")
    if new.get("provisional_rows"):
        print(f"               {new['provisional_rows']:,} of them in {new['provisional_tus']:,} TUs approved under a "
              f"provisional name (grouping proven, file name not; tools/tu_map.py)")
    print(f"               {new['homed']:,} files hold only approved rows; {new['at_tu']:,} of them are "
          f"already their TU (tools/tu_skeleton.py --queue merges the rest)")


# The README card's "Is the source clean?" figures (tools/readme_progress.py).
# Three of them count from the start of Phase 2: commit PHASE2_START, where
# AGENTS.md pointed the fleet at linking and cleanup (2026-10-25). A CI checkout
# is shallow, so the counts at that commit are recorded here; phase2_baselines()
# recomputes them from the commit and tools/readme_progress.py --check-baselines
# compares the two.
PHASE2_START = "e041aec055"
PHASE2_DATE = "Oct 25"
PHASE2_HATCH_ITEMS = 32_858      # hatch_items_at(PHASE2_START)[0]
PHASE2_SOURCE_FILES = 23_488     # len(source_files_at(PHASE2_START))
PHASE2_CLASS_COPIES = 77_814     # class_copies_at(PHASE2_START)["extra"]
HATCHES = "reverse/hatch_baseline.tsv"
# Hatch kinds whose count is bytes, not occurrences: summing them with the
# others would weigh one raw `db` byte like one pin.
BYTE_HATCHES = frozenset({"asm_bytes"})
CANONICAL_CLASSES = "reverse/canonical_classes.csv"


def hatch_items_at(ref):
    """(escape-hatch items, asm bytes) the shrink-only register
    (tools/hatch_counters.py) records at one state; None without a register.
    Items sum every kind's occurrences except asm_bytes, reported apart."""
    text = _text_at(ref, HATCHES)
    if text is None:
        return None
    items = byte_count = 0
    for number, line in enumerate(text.splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        fields = line.split("\t")
        if len(fields) < 4 or not fields[3].isdigit():
            raise ValueError(f"{HATCHES} line {number}: no count")
        if fields[0] in BYTE_HATCHES:
            byte_count += int(fields[3])
        else:
            items += int(fields[3])
    return items, byte_count


def tu_target_at(ref):
    """The number of translation units the committed reverse/tu_map.csv names
    (code rows, approved or proposed) at one state: the map's estimate of how
    many source files retail was built from, not a proven count. None without
    a map. Read from the committed file so CI needs no Open-BFME-1 checkout to
    rebuild it (source_recovery_at's worktree figure rebuilds it)."""
    text = _text_at(ref, TU_MAP)
    if text is None:
        return None
    return len({row["tu"].lower() for row in csv.DictReader(text.splitlines())
                if row["kind"] == "code" and row["tu"]})


def _class_names(text):
    """Classes `text` declares a namespace-scope body for (tools/class_views.py's
    private views)."""
    import class_layouts
    return frozenset(class_layouts.class_bodies(text))


def _class_names_all(texts):
    """_class_names of each text, in order, on every core when there are many."""
    if len(texts) < 2000:
        return [_class_names(text) for text in texts]
    import concurrent.futures
    import os
    with concurrent.futures.ProcessPoolExecutor(max_workers=min(os.cpu_count() or 1, 16)) as pool:
        return list(pool.map(_class_names, texts, chunksize=200))


def class_view_sources(matched):
    """The units tools/class_views.py surveys: matched, hand-written C/C++ sources."""
    return sorted({source for _, source in matched.values()
                   if source.lower().endswith((".cpp", ".c")) and not source.startswith(GENERATED_ROOTS)})


def class_copies_at(ref, memo=None):
    """Duplicate private class copies at one state: {extra, copies, classes}.

    A private copy is a namespace-scope class or struct body a unit declares
    for itself (tools/class_views.py's survey: matched, hand-written .cpp/.c
    ledger sources). `extra` counts the copies beyond one definition per
    class: every copy of a class registered in reverse/canonical_classes.csv
    (its header is the one definition), and all but one copy of any other
    class. One definition per class leaves 0. `memo` ({digest: names}) lets
    two states share the parsing of identical files."""
    import hashlib
    memo = {} if memo is None else memo
    sources = class_view_sources(matched_at(ref))
    if ref is None:
        blobs = {}
        for source in sources:
            try:
                blobs[source] = (ROOT / source).read_bytes()
            except OSError:
                continue
    else:
        blobs = _batch_git_blobs(ref, sources, missing_ok=True)
    digests = {source: hashlib.sha1(blob).digest() for source, blob in blobs.items()}
    todo = {digest: blobs[source] for source, digest in digests.items() if digest not in memo}
    keys = list(todo)
    for digest, names in zip(keys, _class_names_all([todo[key].decode("latin-1") for key in keys])):
        memo[digest] = names
    units = Counter(name for source in blobs for name in memo[digests[source]])
    raw = _text_at(ref, CANONICAL_CLASSES)
    canonical = {row["class"] for row in csv.DictReader(raw.splitlines()) if row.get("class")} if raw else set()
    extra = sum(count if name in canonical else count - 1 for name, count in units.items())
    return {"extra": extra, "copies": sum(units.values()), "classes": len(units)}


def phase2_share(start, now, target=0):
    """How much of the way from `start` (the count at PHASE2_START) to
    `target` the count `now` has come, in percent. Below 0 when it grew."""
    return percent(start - now, start - target)


def phase2_baselines():
    """The PHASE2_* counts recomputed from PHASE2_START (needs that commit)."""
    return {"hatch_items": hatch_items_at(PHASE2_START)[0],
            "source_files": len(source_files_at(PHASE2_START)),
            "class_copies": class_copies_at(PHASE2_START)["extra"]}


# The census row's counts that stand between the tree and a link without
# shortcuts: names nothing defines, hard-coded image addresses, names two
# objects define. The census records no stub or pin count of its own.
STRICT_BLOCKER_FIELDS = ("unresolved", "addresses", "duplicates")


def strict_blockers(census):
    """{field: count, "total": sum} from one census history row; None when the
    row lacks any of STRICT_BLOCKER_FIELDS."""
    if not census or any(not str(census.get(field) or "").strip().isdigit() for field in STRICT_BLOCKER_FIELDS):
        return None
    counts = {field: int(census[field]) for field in STRICT_BLOCKER_FIELDS}
    return {**counts, "total": sum(counts.values())}


CENSUS_TOOL = "tools/link_census.py"
CENSUS_RULES_RE = re.compile(r'^RULES = "([^"]+)"', re.M)


def census_tool_rules_at(ref):
    """The rules tools/link_census.py measures under at one state (its RULES),
    or None when it cannot be read. When they differ from the newest census
    row's, that row predates a rule change and the next census re-measures."""
    text = _text_at(ref, CENSUS_TOOL)
    found = CENSUS_RULES_RE.search(text or "")
    return found.group(1) if found else None


def cleanup_figures_at(ref, memo=None):
    """The card's "Is the source clean?" counts at one state (names apart:
    tools/name_metric.py reads the worktree)."""
    hatches = hatch_items_at(ref)
    return {"hatch_items": hatches[0] if hatches else None, "asm_bytes": hatches[1] if hatches else None,
            "source_files": len(source_files_at(ref)), "tu_target": tu_target_at(ref),
            "class_copies": class_copies_at(ref, memo)["extra"]}


def print_cleanup(old, new, names=None):
    """The card's "Is the source clean?" figures other than hand-written code
    (print_headline's AUTHORED C++), then what each counts. A change is the
    count retired between the two states and its share in points."""
    def line(label, key, unit, start, target, note):
        share = phase2_share(start, new[key], target(new))
        same = old[key] is not None and target(old) == target(new)
        delta = (f"delta {old[key] - new[key]:+,} {unit}, {share - phase2_share(start, old[key], target(old)):+.2f} pp"
                 if same else "delta n/a")
        print(f"{label:<15}{share:>11.2f}%  {delta}  <- {note}")
    if names:
        total, placeholders = names       # name_metric.readable()
        readable = total - placeholders
        print(f"{'READABLE NAMES':<15}{percent(readable, total):>11.2f}%  delta n/a  <- {readable:,} of {total:,} "
              "declared names in the worktree are not placeholders (tools/name_metric.py)")
    if new["hatch_items"] is not None:
        line("SHORTCUTS", "hatch_items", "items", PHASE2_HATCH_ITEMS, lambda state: 0,
             f"escape-hatch items retired since {PHASE2_START}: {PHASE2_HATCH_ITEMS:,} then, "
             f"{new['hatch_items']:,} now in {HATCHES} (asm_bytes apart: {new['asm_bytes']:,} bytes)")
    if new["tu_target"] is not None:
        line("FILE LAYOUT", "source_files", "files", PHASE2_SOURCE_FILES, lambda state: state["tu_target"],
             f"(files at {PHASE2_START} - files now) / (files at {PHASE2_START} - TUs): ({PHASE2_SOURCE_FILES:,} - "
             f"{new['source_files']:,}) / ({PHASE2_SOURCE_FILES:,} - {new['tu_target']:,} TUs the committed "
             f"{TU_MAP} names, an estimate)")
    line("SHARED CLASSES", "class_copies", "copies", PHASE2_CLASS_COPIES, lambda state: 0,
         f"duplicate private class copies removed since {PHASE2_START}: {PHASE2_CLASS_COPIES:,} then, "
         f"{new['class_copies']:,} now (class_copies_at)")
    print("               (with AUTHORED C++ above: the card's \"Is the source clean?\" rows; "
          f"shortcuts, file layout and shared classes count from {PHASE2_DATE})")


def marker_delta(ref1, ref2):
    """Net present-unmatched/absent-from-retail markers added between states."""
    cmd = ["git", "diff", ref1] + ([ref2] if ref2 else []) + ["--", "Code"]
    # Original engine sources include legacy-encoded copyright comments. The
    # markers are ASCII, so undecodable comment bytes must not stop the audit.
    diff = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", check=True).stdout
    added = removed = 0
    for line in diff.splitlines():
        if line.startswith("+++") or line.startswith("---"):
            continue
        if "present-unmatched" in line or "absent-from-retail" in line:
            if line.startswith("+"):
                added += 1
            elif line.startswith("-"):
                removed += 1
    return added - removed


def area(source):
    parts = source.split("/")
    return "/".join(parts[:2]) if len(parts) > 1 else source


def asm_diagnostics(matched, naked_rows):
    naked_rows = set(naked_rows)
    sources = {
        source for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    }
    rows = sum(
        1 for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    )
    return rows, len(sources)


def print_details(ref1, ref2, old, new, old_naked=(), new_naked=()):
    added = {name: new[name] for name in new.keys() - old.keys()}
    removed = {name: old[name] for name in old.keys() - new.keys()}
    print("\nledger details (diagnostics, not unique-byte progress)")
    print(f"  matched rows:      {len(old):,} -> {len(new):,}"
          f"  (+{len(added):,}, -{len(removed):,})")
    print(f"  distinct RVAs:     {len({int(rva, 16) for _, rva in old}):,}"
          f" -> {len({int(rva, 16) for _, rva in new}):,}")
    old_asm_rows, old_asm_files = asm_diagnostics(old, old_naked)
    new_asm_rows, new_asm_files = asm_diagnostics(new, new_naked)
    print(f"  ASM-backed rows:   {old_asm_rows:,} -> {new_asm_rows:,}")
    print(f"  ASM-bearing files: {old_asm_files:,} -> {new_asm_files:,}")
    print(f"  unclaimed markers: {marker_delta(ref1, ref2):+d}")

    if added:
        by_area = Counter()
        by_file = Counter()
        for _, source in added.values():
            by_area[area(source)] += 1
            by_file[source] += 1
        print("  added by area: "
              + ", ".join(f"{name} +{count}" for name, count in by_area.most_common()))
        print("  top added files:")
        for source, count in by_file.most_common(10):
            print(f"    +{count:<4d} {source}")
    if removed:
        print("  removed rows:")
        for (name, _), (size, source) in sorted(removed.items())[:10]:
            print(f"    -{size:<5d} {source}  {name[:60]}")


def parse_range(value):
    if ".." in value:
        ref1, _, ref2 = value.partition("..")
        return ref1, ref2 or None
    return value, None


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("range", nargs="?", default="HEAD",
                        help="REF (vs worktree) or REF1..REF2")
    parser.add_argument("--details", action="store_true",
                        help="show row, RVA, marker, area, and file diagnostics")
    args = parser.parse_args()

    ref1, ref2 = parse_range(args.range)
    old = matched_at(ref1)
    new = matched_at(ref2)
    text_start, text_size = retail_text()
    old_naked = naked_cpp_rows_at(old, ref1)
    new_naked = naked_cpp_rows_at(new, ref2)
    old_data, new_data = text_data_at(ref1), text_data_at(ref2)
    old_stats = coverage(old, text_start, text_size, old_naked, old_data)
    new_stats = coverage(new, text_start, text_size, new_naked, new_data)
    label2 = ref2 or "worktree"

    padding, denominator = real_code_denominator(text_start, text_size)
    old_notes, new_notes = notes_at(ref1), notes_at(ref2)
    old_census, new_census = census_at(ref1), census_at(ref2)
    if old_census:
        old_census = dict(old_census, **(linking_coverage_at(ref1) or {}))
    if new_census:
        new_census = dict(new_census, **(linking_coverage_at(ref2) or {}))
    print_headline(padding, denominator, real_split(old, old_notes, text_start, text_size, old_naked, text_data=old_data),
                   real_split(new, new_notes, text_start, text_size, new_naked, text_data=new_data), old_census, new_census,
                   census_rows_at(ref2), census_tool_rules_at(ref2))
    print()
    memo = {}
    import name_metric
    print_cleanup(cleanup_figures_at(ref1, memo), cleanup_figures_at(ref2, memo),
                  name_metric.readable() if ref2 is None else None)
    print()
    print_source_recovery(source_recovery_at(ref1), source_recovery_at(ref2))
    print_scorecard(ref1, label2, old_stats, new_stats)
    if args.details:
        print_details(ref1, ref2, old, new, old_naked, new_naked)
    print("\nledger-derived; a clean build.sh run is the byte-match proof.")


if __name__ == "__main__":
    main()
