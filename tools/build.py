#!/usr/bin/env python3
import bisect
import concurrent.futures
import csv
import functools
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import threading
from pathlib import Path

import flag_defaults
import stlport_folds
from coffar import RELOC_WIDTH, read_archive
from gen_case_shims import ensure_case_shims
from portable_lock import lock, unlock


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "manifest.json"
EXE = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "files" / "game.dat"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
BUILD_DIR = ROOT / "build" / "match"
PATCH_DIR = ROOT / "build" / "patch"


LIB_SUFFIX = ".lib"
# A row whose bytes are compared with every relocation site masked out is only
# as good as the bytes that remain. Below this many concrete bytes the
# comparison proves nothing, so the row is not evidence and the gate says so.
MIN_LIB_CONCRETE = 8


def resolved(path):
    # Path.resolve() can hand back a Windows extended-length \\?\ path once the
    # tree gets deep enough (Code/gen_small/*.cpp under a long checkout dir on
    # Python 3.14). ROOT never carries that prefix, so relative_to() rejects the
    # result and the gate dies in its last phase. Strip it back off.
    out = Path(path).resolve()
    text = str(out)
    return Path(text[4:]) if text.startswith("\\\\?\\") else out


def obj_path(source, member=None):
    # Namespace objs by the source's repo-relative path, not its bare stem:
    # same-basename sources in different tree dirs must not collide.
    # Encode uppercase as ^x because wine resolves paths case-insensitively:
    # INI.cpp and ini.cpp would otherwise overwrite each other's obj.
    rel = resolved(source).relative_to(ROOT)
    stem = "_".join(rel.with_suffix("").parts)
    if member is not None:
        # One .lib holds hundreds of members and a row names exactly one, so the
        # obj is per (source, member) — keying on the source alone would give
        # 2,000 rows spanning 136 members a single shared output path.
        stem += "_" + member_stem(member)
    encoded = "".join(("^" + c.lower()) if c.isupper() else c for c in stem)
    return BUILD_DIR / (encoded + ".obj")


def member_stem(member):
    """Filename part of an archive member name (`obj\\i386\\d3dx9tex.obj`)."""
    return re.split(r"[\\/]", member)[-1].removesuffix(".obj")


def ledger_member(row):
    """The archive member a .lib-sourced row's bytes come from."""
    match = re.search(r"(?:^|;)member=([^;]+)", row.get("notes", ""))
    if match is None:
        raise SystemExit(
            f"{row['name']}: source {row['source']} is a static library but the row "
            "has no `member=` note naming the object its bytes come from")
    return match.group(1)


def row_object(row):
    """The object file holding this row's code: a compiled TU, or a lib member."""
    source = ROOT / row["source"]
    if source.suffix.lower() == LIB_SUFFIX:
        return obj_path(source, ledger_member(row))
    return obj_path(source)


def require_row_object(row):
    """row_object, but a missing object is fatal rather than skipped.

    The string-ref and DIR32 verifiers used to `continue` past an absent obj
    while still reporting "0 unverified/skipped", so a whole source's rows could
    drop out of both checks and leave the summary line saying everything passed.
    """
    obj = row_object(row)
    if not obj.exists():
        raise SystemExit(
            f"{row['name']} ({row['source']}): object {obj.relative_to(ROOT)} is missing, "
            "so this row cannot be verified. Run the full ./build.sh, which builds it.")
    return obj


def extract_lib_members(rows):
    """Unpack every archive member the given rows name into the build dir.

    A member is a verbatim COFF object, so extracting it verbatim is all a
    .lib-sourced row needs: from here it goes through the same symbol lookup,
    relocation read and byte comparison as a compiled translation unit.
    """
    wanted = {}
    for row in rows:
        source = ROOT / row["source"]
        if source.suffix.lower() == LIB_SUFFIX:
            wanted.setdefault(source, set()).add(ledger_member(row))
    for source, names in sorted(wanted.items()):
        if not source.exists():
            raise SystemExit(f"functions.csv references missing static library: "
                             f"{source.relative_to(ROOT)}")
        members = dict(read_archive(source))
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        for name in sorted(names):
            if name not in members:
                raise SystemExit(
                    f"{source.relative_to(ROOT)}: no member named {name!r} — a row's "
                    "`member=` note does not match any object in the archive")
            output = obj_path(source, name)
            body = members[name]
            if not output.exists() or output.read_bytes() != body:
                output.write_bytes(body)
    if wanted:
        print(f"Lib members: {sum(len(n) for n in wanted.values())} extracted from "
              f"{len(wanted)} archive(s)")
NOOP_EXE = PATCH_DIR / "game.noop.dat"
# Open-BFME-1 restructured its tree: Code/ -> game/, reference/ ->
# inputs/reference/, build/toolchains/ -> inputs/toolchains/, baselines/ ->
# inputs/baselines/, vendor/ -> inputs/vendor/. Every path this repo reaches
# into the submodule with goes through bfme1_subtree(), which probes both
# spellings, so a clone pinned to either submodule commit resolves the same
# logical subtree and nothing has to be set by hand.
BFME1_ROOT = ROOT / "reference" / "open-bfme-1"
_BFME1_LAYOUTS = {
    # logical name: (current upstream spelling, legacy spelling)
    "reference": ("inputs/reference", "reference"),
    "toolchains": ("inputs/toolchains", "build/toolchains"),
    "baselines": ("inputs/baselines", "baselines"),
    "vendor": ("inputs/vendor", "vendor"),
    "game": ("game", "Code"),
    "ledger": ("targets/game/reverse", "reverse"),
}


def bfme1_subtree(kind):
    """Relative posix path of one logical open-bfme-1 subtree, layout-agnostic.

    Returns the first spelling that exists, else the current upstream one, so
    a "missing submodule" message names where the tree belongs today rather
    than the location upstream retired.
    """
    candidates = _BFME1_LAYOUTS[kind]
    for relative in candidates:
        if (BFME1_ROOT / relative).exists():
            return relative
    return candidates[0]


def bfme1_path(kind, *parts):
    """Absolute path inside one logical open-bfme-1 subtree."""
    return BFME1_ROOT.joinpath(bfme1_subtree(kind), *parts)


# The MSVC 7.1 toolchain ships in the Open-BFME-1 submodule; this repo does not
# duplicate it. A missing path here means `git submodule update --init`.
DEFAULT_VC71_ROOT = bfme1_path(
    "toolchains", "vs2003", "Program Files", "Microsoft Visual Studio .NET 2003")
_WINE_PATH_CACHE = {}
_WINE_PATH_LOCK = threading.Lock()


def u16(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def hash_file(path, algorithm):
    digest = hashlib.new(algorithm)
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def verify_baseline():
    with MANIFEST.open("r", encoding="utf-8") as handle:
        manifest = json.load(handle)

    baseline_dir = MANIFEST.parent
    verified = 0

    for entry in manifest["files"]:
        path = baseline_dir / entry["path"]
        if not path.exists():
            raise SystemExit(f"missing baseline file: {path}")

        size = path.stat().st_size
        if size != entry["size"]:
            raise SystemExit(f"{entry['path']}: size {size} != {entry['size']}")

        sha256 = hash_file(path, "sha256")
        if sha256 != entry["sha256"]:
            raise SystemExit(f"{entry['path']}: sha256 mismatch")

        md5 = hash_file(path, "md5")
        if md5 != entry["md5"]:
            raise SystemExit(f"{entry['path']}: md5 mismatch")

        verified += 1

    print(f"Baseline: OK {verified} file(s) ({manifest['id']})")


def pe_sections(data):
    pe_offset = u32(data, 0x3C)
    coff = pe_offset + 4
    section_count = u16(data, coff + 2)
    optional_size = u16(data, coff + 16)
    section_table = coff + 20 + optional_size

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace").strip()
        virtual_size = u32(data, offset + 8)
        virtual_address = u32(data, offset + 12)
        raw_size = u32(data, offset + 16)
        raw_pointer = u32(data, offset + 20)
        sections.append(
            {
                "name": name,
                "rva": virtual_address,
                "size": max(virtual_size, raw_size),
                "virtual_size": virtual_size,
                "raw_size": raw_size,
                "raw_pointer": raw_pointer,
            }
        )
    return sections


def rva_to_file_offset(sections, rva):
    for section in sections:
        start = section["rva"]
        end = start + section["size"]
        if start <= rva < end:
            if rva - start >= section["raw_size"]:
                raise ValueError(f"RVA 0x{rva:08X} is zero-filled PE data, not a file offset")
            return section["raw_pointer"] + (rva - start)
    raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")


@functools.lru_cache(maxsize=1)
def exe_image():
    """The retail image and its section table, read once per process.

    The baseline is md5-verified and never rewritten during a run, so this is the
    same bytes every call. It used to be re-read per call: next_work.py asks for
    4,008 candidate bodies and spent 13 of its 14 seconds re-reading the same
    13 MB file and re-parsing the same section table.
    """
    data = EXE.read_bytes()
    return data, pe_sections(data)


# The comparison prints exactly `size` bytes of the compiled body, so a compiled
# length equal to the target length is the printer's doing and not a finding: ask
# for 900 bytes of a 631-byte target and it prints 900. Three banked partials were
# recorded citing an "exact length match" that was this artefact. When you want the
# real size of what cl emitted, read the COMDAT size locate.py reports.
def read_pe_bytes(data, sections, rva, size):
    """Read loaded section bytes, including the loader's zero-filled tail.

    PE VirtualSize can exceed SizeOfRawData. Those bytes have no file offset;
    reading beyond the raw section instead picks unrelated following file data.
    See https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#section-table-section-headers
    """
    if rva < 0 or size < 0 or rva + size > 0x100000000:
        raise ValueError("Invalid PE32 byte range")
    result = bytearray()
    while size:
        section = next((s for s in sections if s["rva"] <= rva < s["rva"] + s["size"]), None)
        if section is None:
            raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")
        relative = rva - section["rva"]
        count = min(size, section["size"] - relative)
        backed = min(count, max(0, section["raw_size"] - relative))
        if backed:
            offset = section["raw_pointer"] + relative
            contents = data[offset : offset + backed]
            if len(contents) != backed:
                raise ValueError(f"PE section {section['name']} has truncated raw data")
            result.extend(contents)
        result.extend(b"\0" * (count - backed))
        rva += count
        size -= count
    return bytes(result)


def read_target_bytes(rva, size):
    data, sections = exe_image()
    return read_pe_bytes(data, sections, rva, size)


def coff_name(data, symbol_offset, string_table):
    short_name = data[symbol_offset : symbol_offset + 8]
    if short_name[:4] == b"\0\0\0\0":
        string_offset = u32(short_name, 4)
        end = string_table.index(b"\0", string_offset)
        return string_table[string_offset:end].decode("ascii", errors="replace")
    return short_name.rstrip(b"\0").decode("ascii", errors="replace")


# A COFF symbol's SectionNumber is int16, so a symbol living in section 0x8000
# or beyond reads back negative and every `section > 0` test below rejects it as
# undefined. A 250-instantiation generated TU needed 44,768 COMDATs and lost 56
# rows to exactly that, diagnosed only as "symbol not found in object".
COFF_SECTION_CEILING = 0x7FFF


def read_object_symbols(data):
    symbol_table = u32(data, 8)
    symbol_count = u32(data, 12)
    string_table = data[symbol_table + symbol_count * 18 :]
    symbols = []
    index = 0
    while index < symbol_count:
        offset = symbol_table + index * 18
        name = coff_name(data, offset, string_table)
        value = u32(data, offset + 8)
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        aux_count = data[offset + 17]
        symbols.append({"name": name, "value": value, "section": section_number,
                        "storage": data[offset + 16], "aux": aux_count,
                        "type": u16(data, offset + 14)})
        for _ in range(aux_count):
            index += 1
            offset = symbol_table + index * 18
            symbols.append({"name": "", "value": 0, "section": 0, "aux": 0})
        index += 1
    return symbols


@functools.lru_cache(maxsize=256)
def _object_layout(path_str, mtime_ns, size):
    """Parsed COFF layout, keyed by (path, mtime, size) so a recompile misses.

    The gate reads the SAME multi-MB object once per ledger row; with generated
    claims putting hundreds of rows on one TU, re-reading and re-parsing per row
    came to dominate full-gate wall time (91k rows over ~4k objects). One parse
    per object version is behavior-identical."""
    data = Path(path_str).read_bytes()
    section_count = u16(data, 2)
    section_table = 20

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        sections.append(
            {
                "name": data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace"),
                "raw_size": u32(data, offset + 16),
                "raw_pointer": u32(data, offset + 20),
                "reloc_count": u16(data, offset + 32),
                "reloc_pointer": u32(data, offset + 24),
                "characteristics": u32(data, offset + 36),
            }
        )

    return data, sections, read_object_symbols(data)


def defined_code_symbols(path):
    """Names defined in COFF sections containing executable code, not data."""
    stat = path.stat()
    _, sections, symbols = _object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    return {s["name"] for s in symbols if s["section"] > 0 and
            sections[s["section"] - 1]["characteristics"] & 0x20}


def read_object_symbol_bytes(path, symbol_name, expected_size=None, *, code_only=False,
                             detail=False):
    """Bytes from the symbol to its section end, plus (offset, type, name) relocs.

    detail=True adds a third value: the section number, the symbol's value, the
    parsed symbol table and, per relocation, the INDEX of the symbol it binds.
    Names alone cannot say which `$L` label or which `.text` a jump-table entry
    targets: both repeat across sections of one object."""
    stat = path.stat()
    data, sections, symbols = _object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    resolved_name = symbol_name
    if not any(s["name"] == symbol_name and s["section"] > 0 for s in symbols):
        # MSVC hashes the absolute source path into anonymous-namespace names,
        # so the same function gets a different ?A0x........ token in each
        # clone/worktree. Accept only one otherwise-identical defined symbol.
        normalized = re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", symbol_name)
        candidates = [s["name"] for s in symbols if s["section"] > 0 and
                      re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", s["name"]) == normalized]
        if len(candidates) == 1:
            resolved_name = candidates[0]
        # Compiler-generated dynamic-initializer ordinals change when globals
        # differ between the BFME and ZH translation units.  Resolve a stale
        # retail ordinal only when size identifies one initializer uniquely.
        elif expected_size is not None and re.fullmatch(r"_\$E\d+", symbol_name):
            candidates = []
            for candidate in symbols:
                if candidate["section"] <= 0 or not re.fullmatch(r"_\$E\d+", candidate["name"]):
                    continue
                section = sections[candidate["section"] - 1]
                start = section["raw_pointer"] + candidate["value"]
                end = section["raw_pointer"] + section["raw_size"]
                if len(data[start:end].rstrip(b"\xcc")) == expected_size:
                    candidates.append(candidate["name"])
            if len(candidates) == 1:
                resolved_name = candidates[0]
    index = 0
    while index < len(symbols):
        symbol = symbols[index]
        # the same name can appear as a sectionless entry (e.g. weak external)
        # before its real definition; keep scanning for the defined one
        if symbol["name"] == resolved_name and symbol["section"] > 0:
            section = sections[symbol["section"] - 1]
            if code_only and not section["characteristics"] & 0x20:
                raise SystemExit(
                    f"{symbol_name}: function claim names non-code COFF section "
                    f"{section['name']} in {path.name}. Static data is not a function "
                    "even when relocation masking makes its bytes match .text.")
            value = symbol["value"]
            start = section["raw_pointer"] + value
            end = section["raw_pointer"] + section["raw_size"]
            bytes_data = data[start:end]

            relocs = []
            reloc_symbols = []
            for r in range(section["reloc_count"]):
                ro = section["reloc_pointer"] + r * 10
                rva = u32(data, ro)
                sym_idx = u32(data, ro + 4)
                rtype = u16(data, ro + 8)
                if value <= rva < value + len(bytes_data):
                    relocs.append((rva - value, rtype, symbols[sym_idx]["name"]))
                    reloc_symbols.append(sym_idx)

            if detail:
                return bytes_data, relocs, {
                    "section": symbol["section"], "value": value, "symbols": symbols,
                    "section_size": section["raw_size"], "reloc_symbols": reloc_symbols}
            return bytes_data, relocs

        index += 1

    if len(sections) > COFF_SECTION_CEILING:
        raise ValueError(
            f"symbol not found in object: {symbol_name} — {path.name} carries "
            f"{len(sections)} sections and a COFF section number is int16, so every symbol "
            f"past section {COFF_SECTION_CEILING} reads negative and is invisible to any "
            "reader. Split the batch that produced this TU: its limit is a section budget, "
            "not a row count.")
    raise ValueError(f"symbol not found in object: {symbol_name}")


def notes_tokens(row):
    """The `;`-separated tokens of a row's notes. Markers are whole tokens: a
    substring test let any note that merely MENTIONED `gen-alias` switch on
    relocation masking for its row."""
    return {token.strip() for token in (row.get("notes") or "").split(";")}


def is_alias_row(row):
    """A row that claims a REAL name for bytes compiled under another symbol.

    `object-symbol=` is legitimate build plumbing for funclet labels, dynamic
    initializer ordinals, anonymous-namespace hashes and placeholder names
    that disclaim identity. What remains binds a callee name to someone
    else's body, and every caller of that name then resolves through it."""
    match = re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes") or "")
    if not match:
        return False
    symbol, name = match.group(1).strip(), row["name"]
    if symbol == name or re.fullmatch(r"\$L\d+|_\$E\d+", symbol):
        return False
    if CLONE_LOCAL_RE.sub("", symbol) == CLONE_LOCAL_RE.sub("", name):
        return False
    # The ledger writes dup_ placeholders in either hex case; DUP_ALIAS_RE is
    # shared with older checks and only knows lowercase.
    return not (DUP_ALIAS_RE.match(name) or DUP_ALIAS_ANYCASE_RE.match(name)
                or GEN_PLACEHOLDER_RE.search(name))


def ledger_object_symbol(row):
    """Return an explicit TU-local object symbol alias from the notes column."""
    match = re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes", ""))
    return match.group(1) if match else row["name"]


def vc71_root():
    root = Path(os.environ.get("VC71_ROOT", DEFAULT_VC71_ROOT))
    compiler = root / "Vc7" / "bin" / "cl.exe"
    if not compiler.exists():
        raise SystemExit(
            "MSVC 7.1 cl.exe not found. Set VC71_ROOT to a Visual Studio .NET 2003 "
            f"install root, or place it at {DEFAULT_VC71_ROOT.relative_to(ROOT)}."
        )
    return root


def wine_path(path):
    key = str(path)
    if os.name == "nt":
        return key
    with _WINE_PATH_LOCK:
        cached = _WINE_PATH_CACHE.get(key)
        if cached is not None:
            return cached
        winepath = shutil.which("winepath")
        if winepath is None:
            raise SystemExit("winepath not found. Install Wine to run MSVC 7.1 on this host.")
        converted = subprocess.check_output([winepath, "-w", key], text=True).strip()
        _WINE_PATH_CACHE[key] = converted
        return converted


def stlport_include_dir():
    """Directory of STLport 4.5.3 headers, or None. The game linked STLport, so
    files using std:: containers must compile against it to byte-match (MSVC's own
    STL emits different code). Prefer a vendored copy; fall back to an env var."""
    candidates = [ROOT / "vendor" / "stlport"]
    env_root = os.environ.get("STLPORT_ROOT")
    if env_root:
        candidates.append(Path(env_root))
    for path in candidates:
        if (path / "list").exists():
            return path
    return None


# The vendored Zero Hour tree. Its whole value is being unmodified upstream, so
# its files carry neither the `// stlport` marker nor a `// cl:` line that a
# Code/ source uses to declare its build settings; a row sourced from here gets
# its flags from the path instead. Both settings below are what the 420-TU sweep
# compiled and matched with.
ZH_REFERENCE_ROOT = bfme1_path("reference", "CnC_Generals_Zero_Hour", "GeneralsMD", "Code")
# The base game beside it. BFME forked the SAGE engine before Zero Hour did, so
# where the expansion's copy of a translation unit drifted, the base game's copy
# is the one whose bodies still compile byte-true.
GENERALS_REFERENCE_ROOT = bfme1_path("reference", "CnC_Generals_Zero_Hour", "Generals", "Code")
_ZH_INCLUDE_PARTS = (
    "GameEngine/Include", "GameEngine/Source", "Libraries/Include",
    "Libraries/Source", "Libraries/Source/Compression",
    "Libraries/Source/WWVegas", "Libraries/Source/WWVegas/WWLib",
    "GameEngineDevice/Include", "Libraries/Source/WWVegas/WW3D2",
    "Libraries/Source/WWVegas/WWMath", "Libraries/Source/WWVegas/WWDebug",
    "Libraries/Source/WWVegas/WWSaveLoad", "Main",
)


def _reference_include_dirs(*roots):
    return ["-I" + directory for directory in ["reference/shims/sweep"] + [
        f"{root.relative_to(ROOT).as_posix()}/{part}"
        for root in roots for part in _ZH_INCLUDE_PARTS
    ]]


_ZH_BASE_FLAGS = ["-DNDEBUG", "-DWIN32", "-D_WINDOWS", "-MD", "-EHsc"]
_ZH_FLAGS = _ZH_BASE_FLAGS + _reference_include_dirs(ZH_REFERENCE_ROOT)
# Base-game headers win; the Zero Hour tail is on the path only because
# reference/shims/sweep was written against the expansion and includes headers
# (Common/ObjectStatusTypes.h) the base game never shipped.
_GENERALS_FLAGS = _ZH_BASE_FLAGS + _reference_include_dirs(
    GENERALS_REFERENCE_ROOT, ZH_REFERENCE_ROOT)


def zh_reference_source(source):
    """`source` relative to whichever vendored SAGE tree holds it, or None."""
    if source is None:
        return None
    for root in (ZH_REFERENCE_ROOT, GENERALS_REFERENCE_ROOT):
        try:
            return resolved(source).relative_to(root).as_posix()
        except ValueError:
            continue
    return None


def source_needs_stlport(source):
    """A source declares it needs STLport with a `// stlport` line near the top.
    STLport shadows standard headers (<cmath>, <cstring>, ...), so it must be
    opt-in per file — never on the global include path for STL-free matched files.

    This used to read only the first 2048 bytes looking for that line, the same
    fixed-window trap `source_extra_flags` below guards against for `// cl:`: a
    long leading comment block (e.g. a source with a long `// cl:` include-path
    line above its `// stlport` line) can push the marker past the window, and
    the file then silently builds without STLport with no error. Read the whole
    file instead — these are small text sources, so the cost is negligible."""
    if source is None:
        return False
    relative = zh_reference_source(source)
    if relative is not None:
        # The sweep's split over 420 vendored TUs, with no exceptions either way:
        # the WWVegas libraries match against MSVC's own STL, and every GameEngine
        # TU needs STLport (which took their compile rate from 29% to 94.6%).
        return not relative.startswith("Libraries/Source/WWVegas/")
    try:
        with Path(source).open("r", encoding="utf-8", errors="replace") as handle:
            head = handle.read()
    except OSError:
        return False
    return "// stlport" in head


def compiler_environment(root, source=None):
    env = os.environ.copy()
    bin_dir = root / "Vc7" / "bin"
    ide_dir = root / "Common7" / "IDE"
    base_dir = root.parents[1]

    stlport = stlport_include_dir() if source_needs_stlport(source) else None

    if os.name == "nt":
        include = str(root / "Vc7" / "include")
        if stlport:
            include = str(stlport) + os.pathsep + include
        env["INCLUDE"] = include
        env["LIB"] = str(root / "Vc7" / "lib")
        # MSVC 7.1 runtime DLLs (msvcp71.dll) live in the toolchain root, not
        # bin/ or Common7/IDE/. Add base_dir so the compiler back-ends load.
        env["PATH"] = os.pathsep.join([str(bin_dir), str(ide_dir), str(base_dir), env.get("PATH", "")])
        return env

    include = wine_path(root / "Vc7" / "include")
    if stlport:
        include = wine_path(stlport) + ";" + include
    env["INCLUDE"] = include
    env["LIB"] = wine_path(root / "Vc7" / "lib")
    env["WINEPATH"] = ";".join(
        path
        for path in [wine_path(bin_dir), wine_path(ide_dir), wine_path(base_dir), env.get("WINEPATH", "")]
        if path
    )
    return env


def _current_bfme1_include_flag(flag, source=None):
    """Resolve Open-BFME-1 ``// cl: /I...`` paths from either checkout layout.

    BFME2 sources already name the submodule explicitly. A BFME1 donor compiled
    in BFME2 carries paths relative to the donor checkout (``/Igame/...`` or
    ``/Iinputs/reference/...``), so prefix those only when the source itself is
    inside the submodule. Never reinterpret a BFME2-local ``/Igame/...`` path.
    """
    prefix = "-I" if flag.startswith("-I") else "/I" if flag.startswith("/I") else None
    if prefix is None:
        return flag
    include = flag[len(prefix):]
    root = "reference/open-bfme-1/"
    in_donor = False
    if source is not None:
        try:
            resolved(source).relative_to(resolved(BFME1_ROOT))
            in_donor = True
        except ValueError:
            pass

    relative = include[len(root):] if include.startswith(root) else include
    if not include.startswith(root) and not in_donor:
        return flag

    layouts = (
        ("game/", "game"), ("Code/", "game"),
        ("inputs/reference/", "reference"), ("reference/", "reference"),
        ("inputs/toolchains/", "toolchains"), ("build/toolchains/", "toolchains"),
        ("inputs/baselines/", "baselines"), ("baselines/", "baselines"),
        ("inputs/vendor/", "vendor"), ("vendor/", "vendor"),
    )
    for spelling, kind in layouts:
        if relative.startswith(spelling):
            mapped = bfme1_subtree(kind) + "/" + relative[len(spelling):]
            return prefix + root + mapped
    if in_donor:
        if ":" in relative or relative.startswith(("/", "\\")):
            return flag
        # These directives are relative to the BFME1 checkout root. Preserve
        # their subpath under the submodule so the compiler resolves that tree.
        return prefix + root + relative
    return flag


def _source_flag_tokens(text):
    """Keep bare flags unchanged; accept quoted /I paths as one operand."""
    tokens = []
    cursor = 0
    while cursor < len(text):
        if text[cursor].isspace():
            cursor += 1
            continue
        match = re.match(r"\S+", text[cursor:])
        token = match.group(0)
        end = cursor + len(token)
        if token.startswith(("/I", "-I")):
            operand = cursor + 2
            if token in ("/I", "-I"):
                while operand < len(text) and text[operand].isspace():
                    operand += 1
            if operand < len(text) and text[operand] == '"':
                close = text.find('"', operand + 1)
                if close < 0:
                    raise SystemExit("cl flags: unterminated quoted /I include path")
                if close == operand + 1:
                    raise SystemExit("cl flags: empty quoted /I include path")
                if close + 1 < len(text) and not text[close + 1].isspace():
                    raise SystemExit("cl flags: trailing characters after quoted /I include path")
                tokens.append(token[:2] + text[operand + 1:close])
                cursor = close + 1
                continue
            if '"' in token:
                raise SystemExit("cl flags: malformed quoted /I include path")
        tokens.append(token)
        cursor = end
    return tokens


def source_extra_flags(source):
    # A source that needs different compiler flags (e.g. /EHsc for functions the
    # original built with exception handling) declares them in its first lines:
    #   // cl: /EHsc
    # A UTF-8 BOM lands in front of the very first line, so `// cl:` on line 1
    # stops matching and the file silently compiles with the base flags instead.
    # That is invisible in the output -- the build just quietly ignores the
    # directive -- and it costs whole sessions to spot, so strip it here rather
    # than relying on every editor to write BOM-free files. Windows PowerShell's
    # `Set-Content -Encoding UTF8` writes one by default.
    #
    # The same silent-ignore trap exists by length, not just by BOM: this used
    # to read only the first 2048 bytes looking for the `// cl:` line, so a
    # source whose directive sits behind a long leading comment block (e.g. a
    # long include-path line) never matches and quietly gets the base flags.
    # Read the whole file instead -- these are small text sources, so the cost
    # is negligible.
    if zh_reference_source(source) is not None:
        try:
            resolved(source).relative_to(GENERALS_REFERENCE_ROOT)
        except ValueError:
            return _ZH_FLAGS
        return _GENERALS_FLAGS
    with source.open("r", encoding="utf-8-sig", errors="replace") as handle:
        for line in handle.read().splitlines():
            if line.startswith("// cl:"):
                # Use '-' style options so MSYS/Cygwin shells don't rewrite
                # leading '/' arguments as Windows paths.
                flags = [f.replace("/", "-", 1) if f.startswith("/") else f
                         for f in _source_flag_tokens(line[len("// cl:") :])]
                return flag_defaults.apply(
                    source, [_current_bfme1_include_flag(flag, source) for flag in flags])
    # The region decides /O, /arch and /G for Code/ sources (tools/flag_defaults.py).
    return flag_defaults.apply(source, [])


def compiler_command(source, output):
    root = vc71_root()
    source_arg = source.relative_to(ROOT).as_posix()
    output_arg = output.relative_to(ROOT).as_posix()

    command = []
    if os.name != "nt":
        wine = shutil.which("wine")
        if wine is None:
            raise SystemExit("wine not found. Install Wine to run MSVC 7.1 on this host.")
        command.append(wine)

    if source.suffix.lower() == LIB_SUFFIX:
        raise SystemExit(f"{source.relative_to(ROOT)}: a static library is not compiled — "
                         "its rows read an archive member (see extract_lib_members)")

    if source.suffix.lower() == ".asm":
        # Pure MASM for bodies C++ cannot emit (e.g. SEH array-ctor prologues).
        assembler = root / "Vc7" / "bin" / "ml.exe"
        command += [
            str(assembler),
            "-nologo",
            "-c",
            "-Cx",
            f"-Fo{output_arg}",
            source_arg,
        ]
        return command, compiler_environment(root, source)

    compiler = root / "Vc7" / "bin" / "cl.exe"
    command += [
        str(compiler),
        "-nologo",
        "-c",
        "-O2",
        "-GR-",
        "-EHsc-",
    ]
    command += source_extra_flags(source)
    command += [
        f"-Fo{output_arg}",
        source_arg,
    ]
    return command, compiler_environment(root, source)


def _host_path(text):
    # cl.exe under wine prints /showIncludes paths as Z:\home\... — map to host.
    path = text.strip().replace("\\", "/")
    if len(path) >= 2 and path[0] in "zZ" and path[1] == ":":
        path = path[2:] or "/"
    if not path.startswith("/"):
        path = str(ROOT / path)
    return os.path.normpath(path)


_CASEDIR_MEMO = {}


def _case_resolve(path):
    """Map a wine-reported path to the real on-disk path. Wine resolves
    case-insensitively and cl prints the REQUESTED casing (lowercased prefixes,
    'Basetype.h' for BaseType.h), so exact lookup fails on Linux. The repo bans
    case-colliding names, so per-component lowercase matching is unambiguous.
    Returns None when nothing matches."""
    if os.path.exists(path):
        return path
    current = "/"
    for part in path.split("/"):
        if not part:
            continue
        candidate = os.path.join(current, part)
        if os.path.exists(candidate):
            current = candidate
            continue
        listing = _CASEDIR_MEMO.get(current)
        if listing is None:
            try:
                listing = {name.lower(): name for name in os.listdir(current)}
            except OSError:
                return None
            _CASEDIR_MEMO[current] = listing
        real = listing.get(part.lower())
        if real is None:
            return None
        current = os.path.join(current, real)
    return current


# Include search inventory (ported from Open-BFME-1's tools/build.py).
#
# Hashing the headers /showIncludes reported proves their bytes, not that the
# compiler would still pick them: a header added to an earlier search
# directory shadows a recorded one without changing a recorded byte. A
# census-grade receipt (compile_is_current(strict=True)) therefore also
# fingerprints the listing of every directory an include could resolve in.
# The ordinary gate keeps its dependency-hash receipt (strict=False), which
# never computed this; only a compile asked for an inventory
# (compile_source(inventory=True), link_census --build) records one.

def _include_search_roots(source, command, env):
    if env.get("CL") or env.get("_CL_"):
        return None  # These implicit compiler options may add include roots.
    roots = {Path(source).parent}
    reported = {p for p in env.get("INCLUDE", "").split(";") if p}
    args = iter(command)
    for arg in args:
        if arg in ("-I", "/I"):
            path = next(args, None)
            if not path:
                return None
            reported.add(path)
        elif arg.startswith(("-I", "/I")) and len(arg) > 2:
            reported.add(arg[2:])
    for raw in reported:
        host = _host_path(raw)
        resolved_path = _case_resolve(host) if host is not None else None
        if resolved_path is None and host is not None and os.name == "nt":
            resolved_path = host
        if resolved_path is None and host is not None:
            # A search directory that does not exist (yet): it stays a root,
            # and _directory_inventory watches for its creation in any casing
            # (Open-BFME-1 refuses such a TU outright on POSIX hosts).
            resolved_path = os.path.normpath(host)
        if resolved_path is None:
            return None
        roots.add(Path(resolved_path))
    if source_needs_stlport(source):
        # STLport's native-header macros expand to <../include/HEADER>
        # (_STLP_NATIVE_INCLUDE_PATH in stl/_config.h), so a root R adds
        # exactly one searched directory: R/../include.
        roots.update(root.parent / "include" for root in tuple(roots))
    roots = {Path(_case_resolve(str(root)) or root) for root in roots}
    return sorted(roots, key=str)


# Build outputs, Git state and unrelated nested worktrees change independently
# of compiler inputs. Skip them only when walking a whole checkout. A header
# that could resolve through a skipped directory refuses a reusable receipt;
# explicitly searched directories still get their own complete inventory.
_UNWATCHED_ROOT_DIRS = ("build", ".git", ".claude")


def _unwatched_tops():
    return {ROOT.resolve(), BFME1_ROOT.resolve()}


def _directory_inventory(root):
    def fail(error):
        raise error

    directories = []
    root = Path(root)
    top = root.resolve() in _unwatched_tops()
    if not os.path.lexists(root) and _case_resolve(str(root)) is None:
        # The compiler finds nothing here, and a directory created here later
        # (in any casing: Wine resolves case-insensitively) changes this
        # digest, so absence is a reusable inventory entry.
        return _absence(root)
    if not root.is_dir():
        return None
    try:
        for directory, subdirs, files in os.walk(root, onerror=fail):
            if any(os.path.islink(os.path.join(directory, name)) for name in subdirs):
                return None  # os.walk would miss additions below a symlink.
            if top and Path(directory).resolve() == root.resolve():
                subdirs[:] = [name for name in subdirs if name not in _UNWATCHED_ROOT_DIRS]
            subdirs.sort()
            # Accepted TUs cannot include .cpp, so sibling source additions do not affect them.
            directories.append((_root_key(Path(directory)), subdirs[:],
                                sorted(name for name in files if not name.lower().endswith(".cpp"))))
    except OSError:
        return None
    return hashlib.sha256(json.dumps(directories).encode()).hexdigest()


def _absence(root):
    """The inventory of a search directory that does not exist. It appears
    exactly when a name equal, ignoring case, to its first missing component
    appears in its deepest existing ancestor, so only that name is watched.
    Walking the ancestor's whole tree instead (the previous rule) made the
    receipt depend on every unrelated file in it: a missing
    /ICode/Libraries/Source/WWVegas/Wwutil watched all of WWVegas, and a
    missing directory under build/ would watch what every compile writes."""
    current, missing = Path(os.path.abspath(root)), None
    while _case_resolve(str(current)) is None:
        if current == current.parent:
            return None
        missing, current = current.name, current.parent
    if missing is None:
        return None  # it exists after all; let the caller walk it
    try:
        names = sorted(name for name in os.listdir(_case_resolve(str(current))) if name.lower() == missing.lower())
    except OSError:
        return None
    return "absent:" + json.dumps([_root_key(current), missing.lower(), names])


def _inventory_for_roots(roots, cache=None):
    parts = []
    for root in roots:
        root = Path(root)
        # WindowsPath equality folds case, but directory inventories retain
        # spelling. Reuse only the digest for this exact root spelling.
        digest = cache.get(str(root)) if cache is not None else None
        if digest is None:
            digest = _directory_inventory(root)
            if cache is not None and digest is not None:
                cache[str(root)] = digest
        if digest is None:
            return None
        parts.append((_root_key(root), digest))
    return hashlib.sha256(json.dumps(parts).encode()).hexdigest()


def _inventory_cache_still_current(cache):
    return all(_directory_inventory(root) == digest for root, digest in cache.items())


def search_inventory(source, command, env, *, inventory_cache=None):
    """Fingerprint every directory where an include could take precedence.

    Hashing only /showIncludes dependencies misses a new header in an earlier
    search directory. A missing or unreadable directory cannot prove reuse.
    """
    roots = _include_search_roots(source, command, env)
    return _inventory_for_roots(roots, inventory_cache) if roots is not None else None


def _root_key(root):
    try:
        return Path(root).relative_to(ROOT).as_posix()
    except ValueError:
        return str(root)


def cache_path_is_valid(path):
    if not isinstance(path, str) or not path or "\0" in path:
        return False
    try:
        os.fsencode(path)
    except UnicodeError:
        return False
    return True


_STLPORT_NATIVE_INCLUDE = re.compile(
    r"^_STLP_NATIVE_(?:C_HEADER|CPP_C_HEADER|CPP_RUNTIME_HEADER|HEADER|OLD_STREAMS_HEADER)\(([^)]*)\)$")
# A literal ends at its line (splices are joined first): an apostrophe in #error or
# #pragma text must not pair with a later quote and turn a string's "/*" into a comment.
_COMMENT_OR_LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|/\*[\s\S]*?\*/|//[^\n]*')
_INCLUDE_DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*include\b[ \t]*(.+)$", re.MULTILINE)


def _directive_text(path):
    try:
        text = Path(path).read_text(encoding="utf-8-sig", errors="replace")
    except OSError:
        return None
    if "??/" in text:
        return None  # A trigraph can splice a directive across lines.
    text = re.sub(r"\\\r?\n", "", text)
    return _COMMENT_OR_LITERAL.sub(
        lambda match: ("".join("\n" if char == "\n" else " " for char in match.group())
                       if match.group().startswith("/") else match.group()), text)


def _stlport_roots():
    return [Path(p) for p in (ROOT / "vendor" / "stlport", stlport_include_dir()) if p is not None]


def _include_escapes_search_roots(path, stlport, roots=None, anchored=None):
    """True when an include in PATH may resolve outside the inventoried roots.
    A quoted include is searched first in its includer's own directory, so one
    that resolves there cannot be shadowed by a header added anywhere else;
    such targets are added to ANCHORED (they need no enclosing search root)."""
    text = _directive_text(path)
    if text is None:
        return True
    skipped = [Path(root).resolve() / name for root in (roots or [])
               if Path(root).resolve() in _unwatched_tops()
               for name in _UNWATCHED_ROOT_DIRS]
    for match in _INCLUDE_DIRECTIVE.finditer(text):
        operand = match.group(1).strip()
        native = _STLPORT_NATIVE_INCLUDE.fullmatch(operand)
        if (stlport and any(Path(path).is_relative_to(root) for root in _stlport_roots())
                and native and re.fullmatch(r"[\w./\\-]+", native.group(1))
                and not native.group(1).lower().endswith(".cpp")
                and ".." not in native.group(1).replace("\\", "/").split("/")):
            continue
        if not operand or operand[0] not in ('"', '<'):
            return True  # Macro-expanded includes have unknown search paths.
        end = operand.find('"' if operand[0] == '"' else '>', 1)
        if end < 0 or operand[1:end].lower().endswith(".cpp"):
            return True
        include = operand[1:end].replace("\\", "/")
        if skipped:
            candidates = [Path(root) / include for root in roots]
            if operand[0] == '"':
                candidates.insert(0, Path(path).parent / include)
            try:
                if any(candidate.resolve().is_relative_to(directory)
                       for candidate in candidates for directory in skipped):
                    # Refuse even an absent earlier candidate: it could later
                    # shadow an unchanged dependency found in another root.
                    return True
            except (OSError, RuntimeError):
                return True
        if operand[0] == '"' and anchored is not None:
            try:
                local = (Path(path).parent / include).resolve(strict=True)
            except (OSError, RuntimeError):
                local = None
            if local is not None and local.is_file():
                anchored.add(local)
                continue
        if ".." in include.split("/"):
            if roots is None:
                return True
            candidates = [Path(root) / include for root in roots]
            if operand[0] == '"':
                candidates.insert(0, Path(path).parent / include)
            root_paths = [Path(root).resolve() for root in roots]
            found = False
            for candidate in candidates:
                try:
                    # cl under Wine resolves every path component without
                    # regard to case, including literal ../ includes. Keep
                    # the existing coverage check after resolving its spelling:
                    # an include outside the inventoried roots still refuses.
                    spelling = _case_resolve(str(candidate))
                    if spelling is None:
                        continue
                    target = Path(spelling).resolve(strict=True)
                except (OSError, RuntimeError):
                    continue
                if not target.is_file():
                    continue
                found = True
                if not any(target.is_relative_to(root) for root in root_paths):
                    return True
            if not found:
                return True
    return False


def _legacy_header_free(source, command, env):
    if env.get("CL") or env.get("_CL_"):
        return False
    if any(arg.lower().startswith(("-fi", "/fi", "-yu", "/yu", "-yc", "/yc", "@"))
           for arg in command):
        return False
    text = _directive_text(source)
    if text is None:
        return False
    return re.search(r"^[ \t]*#[ \t]*(?:include|import|using)\b", text, re.MULTILINE) is None


def _inventory_problems(source, command, env, dep_paths, inventory_before):
    """Why this compile's include search cannot be proven, or []."""
    problems = []
    roots = _include_search_roots(source, command, env)
    if roots is None:
        return ["(include search roots unknown: CL/_CL_ or an unresolvable /I)"], None, None
    walked = {Path(root).resolve(): Path(root).resolve() in _unwatched_tops() for root in roots}

    def covered(path):
        target = Path(path).resolve()
        for root, top in walked.items():
            if not target.is_relative_to(root):
                continue
            if top and any(target.is_relative_to(root / name) for name in _UNWATCHED_ROOT_DIRS):
                continue  # this whole-checkout root skips generated/state trees
            return True
        return False

    anchored = set()
    if any(_include_escapes_search_roots(path, source_needs_stlport(source), roots, anchored)
           for path in [Path(source), *dep_paths]):
        problems.append("(macro or parent-traversing include has unknown search roots)")
    if any(not covered(path) and Path(path).resolve() not in anchored for path in dep_paths):
        problems.append("(an included header lies outside the inventoried search roots)")
    if any(Path(path).suffix.lower() == ".cpp" for path in dep_paths):
        problems.append("(.cpp includes are outside the directory inventory)")
    inventory = _inventory_for_roots(roots)
    if inventory_before is None or inventory != inventory_before:
        problems.append("(include search directories changed during compile or are unreadable)")
    return problems, roots, inventory


_HASH_MEMO = {}


def _hash_file(path):
    # The memo is keyed on the file's full identity (device, inode, size,
    # mtime and ctime: any write moves ctime), and a file that changes while
    # it is read hashes to None: a concurrent writer cannot produce a receipt.
    try:
        stat = os.stat(path)
        stamp = (stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns)
        cached = _HASH_MEMO.get(path)
        if cached and cached[0] == stamp:
            return cached[1]
        digest = hashlib.md5(Path(path).read_bytes()).hexdigest()
        after = os.stat(path)
        if stamp != (after.st_dev, after.st_ino, after.st_size, after.st_mtime_ns, after.st_ctime_ns):
            return None
    except (OSError, ValueError):
        return None
    _HASH_MEMO[path] = (stamp, digest)
    return digest


def _deps_sidecar(output):
    return output.with_suffix(".deps.json")


def _portable(text):
    # Normalize ROOT-dependent path spellings (host and wine forms) so
    # fingerprints and sidecars stay valid across checkouts of the same tree —
    # a worktree seeded with the main clone's warm cache starts warm.
    if os.name != "nt":
        text = text.replace(wine_path(ROOT), "@ROOT@")
    return text.replace(str(ROOT), "@ROOT@")


def _cmd_fingerprint(command, env):
    payload = [[_portable(part) for part in command], _portable(env.get("INCLUDE", ""))]
    return hashlib.md5(json.dumps(payload).encode()).hexdigest()


def _write_deps_sidecar(source, output, fingerprint, stdout_text, is_cl,
                        command=None, env=None, inventory_before=None, retry_dirs=None):
    """Record the compile's exact inputs so compile_is_current can prove reuse.
    Uncacheable situations (unparseable include note, .asm with an include
    directive) fail LOUD and write no sidecar — that TU then always recompiles,
    visibly, instead of silently reusing a possibly-stale obj.

    `retry_dirs` not None asks for a census-grade (version 2) receipt: the
    include search inventory taken before the compile (`inventory_before`)
    must still hold after it and cover every included header. When it cannot,
    the sidecar stays the ordinary one, which compile_is_current(strict=True)
    does not accept."""
    deps = {}
    dep_paths = []
    problems = []
    if is_cl:
        for line in stdout_text.splitlines():
            if not line.startswith("Note: including file:"):
                continue
            host = _case_resolve(_host_path(line[len("Note: including file:"):]))
            if host is None:
                problems.append(line.strip()[:120])
                continue
            rel = os.path.relpath(host, ROOT)
            key = host if rel.startswith("..") else rel
            if key in deps:
                continue
            digest = _hash_file(host)
            if digest is None:
                problems.append(host)
            else:
                deps[key] = digest
                dep_paths.append(Path(host))
        if not deps:
            # A TU with no #include genuinely has no notes — empty deps is
            # correct there. Notes missing DESPITE includes is the broken case.
            text = source.read_text(encoding="utf-8", errors="replace")
            if re.search(r"^\s*#\s*include\b", text, re.MULTILINE):
                problems.append("(cl produced no include notes despite #include lines)")
    else:
        head = source.read_text(encoding="utf-8", errors="replace")
        if re.search(r"^\s*include\s", head, re.IGNORECASE | re.MULTILINE):
            problems.append("(.asm uses an include directive; deps unknown)")
    if problems:
        print(f"deps-cache: not caching {source.relative_to(ROOT)} — {problems[:3]}",
              file=sys.stderr)
        _deps_sidecar(output).unlink(missing_ok=True)
        return
    payload = {"cmd": fingerprint, "source": _hash_file(str(source)), "deps": deps}
    if retry_dirs is not None:
        if is_cl:
            unproven, roots, inventory = _inventory_problems(source, command, env, dep_paths, inventory_before)
        else:
            unproven, roots, inventory = [], [], None
        if unproven:
            print(f"deps-cache: no include inventory for {source.relative_to(ROOT)} — {unproven[:3]}",
                  file=sys.stderr)
        else:
            payload.update({"version": 2, "inventory": inventory, "retry_dirs": list(retry_dirs),
                            "search_roots": [_root_key(root) for root in roots]})
    tmp = _deps_sidecar(output).with_suffix(".tmp")
    tmp.write_text(json.dumps(payload))
    tmp.replace(_deps_sidecar(output))


def compile_is_current(source, output, *, strict=False, inventory_cache=None):
    """Sound obj reuse: True iff the obj exists and the source, compile command,
    and EVERY header recorded by /showIncludes at compile time are byte-identical.
    This is what makes skipping a TU in the full gate safe — the old behavior
    (recompile everything / trust BUILD_RECOMPILE_ONLY blindly) either burned
    ~17 min per gate or could re-verify a stale obj after a header edit.

    strict (link_census): Open-BFME-1's receipt. The include search directories
    must also be unchanged since the compile (a header added to an earlier
    directory shadows a recorded one), so only a version-2 sidecar with an
    inventory proves a TU that includes anything; a header-free TU's ordinary
    sidecar still does."""
    sidecar = _deps_sidecar(output)
    if not output.exists() or not sidecar.exists():
        return False
    try:
        meta = json.loads(sidecar.read_text())
    except (OSError, ValueError):
        return False
    if not isinstance(meta, dict) or not isinstance(meta.get("deps", {}), dict):
        return False
    command, env = compiler_command(source, output)
    if meta.get("cmd") != _cmd_fingerprint(command, env):
        return False
    if meta.get("source") != _hash_file(str(source)):
        return False
    for dep, digest in meta.get("deps", {}).items():
        if not cache_path_is_valid(dep):
            return False
        path = dep if os.path.isabs(dep) else str(ROOT / dep)
        if _hash_file(path) != digest:
            return False
    if not strict:
        return True
    is_cl = source.suffix.lower() != ".asm"
    if meta.get("version") not in (None, 2):
        return False
    if meta.get("version") is None:
        if not is_cl:
            try:
                text = source.read_text(encoding="utf-8", errors="replace")
            except OSError:
                return False
            # An assembler source with no include directive has no search path.
            return re.search(r"^\s*include\s", text, re.IGNORECASE | re.MULTILINE) is None
        return meta.get("deps") == {} and _legacy_header_free(source, command, env)
    retry_dirs = meta.get("retry_dirs", [])
    if not isinstance(retry_dirs, list) or not all(isinstance(path, str) for path in retry_dirs):
        return False
    if retry_dirs:
        current = [d.relative_to(ROOT).as_posix() for d in _SWEEP_INCLUDE_DIRS if d.exists()]
        if retry_dirs != current:
            return False
        env = dict(env)
        env["INCLUDE"] = env["INCLUDE"] + ";" + ";".join(wine_path(ROOT / d) for d in retry_dirs)
        command = list(command) + [f"-I{wine_path(ROOT / d)}" for d in retry_dirs]
    if not is_cl:
        return True
    inventory = search_inventory(source, command, env, inventory_cache=inventory_cache)
    return inventory is not None and meta.get("inventory") == inventory


def format_bytes(data):
    return " ".join(f"{byte:02x}" for byte in data)


def load_all_function_rows():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def load_function_rows():
    return [row for row in load_all_function_rows() if row["status"] == "matched"]


def is_scaffold_row(row):
    """True for a machine byte-dump row: it pins bytes and a boundary only.

    A gen-dump row claims no identity and no source, so every "is this address
    still open work?" question must answer yes over it. Tools that treat the
    ledger's address set as "done" go blind across the whole dump pass
    otherwise -- reverse/reloc_names.csv is REGENERATED by the full gate, so a
    dump row swallowing an address silently deletes a recovered name.
    """
    return row.get("notes", "").lstrip().startswith("gen-dump")


def load_claim_rows(*, counting_dumps, matched_only):
    """Ledger rows for a claim question; `counting_dumps` says WHICH question.

    Two questions get conflated, and the conflation is a bug that has landed
    four separate times. "Is this ground spoken for?" is an over-claim guard and
    a dump does count: counting_dumps=True. "Do we have source for this?" is a
    work finder and a dump does not: counting_dumps=False, which is
    is_scaffold_row's rule and the only correct one. Answering by source path
    instead hides the 349 gen-dump rows that live outside Code/gen_asm/.

    matched_only mirrors check_csv's overlap rule: an unmatched row is a
    hypothesis about an address, not proof the ground is spoken for.

    Neither argument is defaulted, and both are keyword-only, because a default
    is exactly how the wrong answer reached tool number four in silence.
    """
    rows = load_all_function_rows()
    if matched_only:
        rows = [row for row in rows if row["status"] == "matched"]
    if not counting_dumps:
        rows = [row for row in rows if not is_scaffold_row(row)]
    return rows


def follow_thunk(data, sections, rva, low, high):
    """The body an incremental-link thunk stands for, or rva when it is not one.

    The .text bound is what tells a thunk from a coincidence. Any byte can be
    0xE9 -- 0xA5E88E is the tail of a `mov` immediate inside a d3dx9 body -- and
    reading the four bytes after one as a displacement then yields an arbitrary
    address. Unbounded, that address is not merely wrong but unmappable: it
    reached new_starts.py's boundary scan as RVA -0x2AD9506D and crashed it.
    """
    offset = rva_to_file_offset(sections, rva)
    if data[offset] != 0xE9:
        return rva
    body = rva + 5 + struct.unpack_from("<i", data, offset + 1)[0]
    return body if low <= body < high else rva


def build_call_thunks():
    # Intra-module calls don't target a function's body directly -- they go through
    # the incremental-link thunk table, a block of 5-byte `jmp body` entries near the
    # start of .text. Map each body to its (lowest-addressed = ILT) thunk so that a
    # call to a matched function resolves to the address the original code called.
    data = EXE.read_bytes()
    text = next(section for section in pe_sections(data) if section["name"] == ".text")
    lo, size, raw = text["rva"], text["size"], text["raw_pointer"]
    body_to_thunks = {}
    pos, end = raw, raw + size - 5
    while True:
        pos = data.find(b"\xe9", pos, end)
        if pos == -1:
            break
        thunk_rva = (pos - raw) + lo
        target = thunk_rva + 5 + struct.unpack_from("<i", data, pos + 1)[0]
        if lo <= target < lo + size:
            # incremental linking creates one thunk block per re-link; a body can
            # have several thunks and different call sites use different ones
            body_to_thunks.setdefault(target, []).append(thunk_rva)
        pos += 1
    return body_to_thunks


def load_symbol_map():
    # Candidate addresses for resolving relative calls (REL32), most-likely first.
    # Incremental linking makes the callee encoding site-specific: objs linked
    # earlier call a matched function through its incremental-link thunk, objs
    # re-linked in place call the body directly. Both are legitimate, so a matched
    # function maps to [thunk, body] and the comparison picks whichever the target
    # actually used; anything else still fails the byte comparison loudly.
    # reverse/symbols.csv holds callees we do not own source for yet (CRT helpers
    # like __ftol2) at their exact call-target address, plus specific incremental-
    # link thunks build_call_thunks does not auto-discover. It is ADDITIVE: each
    # pinned address becomes one more candidate, so a matched name and a hand-pinned
    # thunk for the same name coexist and each call site picks whichever it encodes.
    thunks = build_call_thunks()
    symbol_map = {}
    for row in load_all_function_rows():
        # An alias row that is not in the reviewed register is no evidence for
        # its name: admitting it made "rename a row via object-symbol=" a way
        # to resolve any caller's wrong callee (tools/pin_admission.py).
        if is_alias_row(row) and not gate_baselined("alias-row", row):
            continue
        body = int(row["target_rva"], 16)
        symbol_map[row["name"]] = thunks.get(body, []) + [body]
    if SYMBOLS.exists():
        # Membership sets mirroring the candidate lists, built only for the names
        # symbols.csv actually pins: `candidate not in candidates` is a linear
        # scan of a list that reaches 9,155 entries, and cost 2.72s of this
        # function's 3.09s. Building all 160k up front would just move the cost.
        # The lists stay lists, in append order — the resolver seeds from
        # candidates[0], stops at the first displacement that reproduces retail,
        # and reports the last one on failure.
        members = {}
        with SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                address = int(row["address"], 16)
                name = row["name"]
                candidates = symbol_map.setdefault(name, [])
                seen = members.get(name)
                if seen is None:
                    seen = members[name] = set(candidates)
                # a pinned body gets its incremental-link thunks too, same as a
                # ledger row: call sites encode the thunk, not the body
                for candidate in thunks.get(address, []) + [address]:
                    if candidate not in seen:
                        seen.add(candidate)
                        candidates.append(candidate)
    return symbol_map


# Sweep environment include dirs (header-only). Added on a *retry* when a source
# fails to open an include that only exists under the GeneralsMD/reference tree
# (e.g. the sweep-shim windows.h, or NetworkDefs.h pulled in by it). Off the
# default path so they never change codegen for the 10k+ already-matched sources.
_SWEEP_INCLUDE_DIRS = [
    ROOT / "reference" / "shims" / "sweep",
    ZH_REFERENCE_ROOT,
    ZH_REFERENCE_ROOT / "Include",
]


# Content-addressed object store, shared by every worktree of this repository
# (it lives in the git common directory). A compile stores its object and
# sidecar under its portable command fingerprint and source hash; a later
# compile of the same inputs, in any worktree or after switching commits,
# restores them instead of running cl.exe, but only when compile_is_current
# accepts the restored pair, so the store can never serve a stale object.
# BFME_OBJSTORE=off disables it.
OBJSTORE_KEEP = 4  # entries per (command, source) key: header variants


@functools.lru_cache(maxsize=1)
def _objstore_root():
    if os.environ.get("BFME_OBJSTORE", "on") == "off":
        return None
    common = subprocess.run(["git", "-C", str(ROOT), "rev-parse", "--git-common-dir"],
                            capture_output=True, text=True).stdout.strip()
    if not common:
        return None
    return (ROOT / common).resolve() / "bfme-objstore"


def _objstore_dir(source, fingerprint):
    store = _objstore_root()
    if store is None:
        return None
    rel = source.resolve().relative_to(ROOT).as_posix() if source.resolve().is_relative_to(ROOT) else str(source)
    key = hashlib.sha256(f"{fingerprint}\0{_hash_file(str(source))}\0{rel}".encode()).hexdigest()
    return store / key[:2] / key


def _restore_object(source, output, fingerprint):
    entry_dir = _objstore_dir(source, fingerprint)
    if entry_dir is None or not entry_dir.is_dir():
        return False
    for obj in sorted(entry_dir.glob("*.obj"), key=lambda p: p.stat().st_mtime, reverse=True):
        meta = obj.with_suffix(".deps.json")
        if not meta.exists():
            continue
        output.parent.mkdir(parents=True, exist_ok=True)
        for src, dst in ((obj, output), (meta, _deps_sidecar(output))):
            tmp = dst.with_name(dst.name + ".restore")
            shutil.copyfile(src, tmp)  # a fresh inode: never shared with the store
            os.replace(tmp, dst)
        if compile_is_current(source, output):
            os.utime(obj)
            return True
        _deps_sidecar(output).unlink(missing_ok=True)
        output.unlink(missing_ok=True)
    return False


def _store_object(source, output, fingerprint):
    entry_dir = _objstore_dir(source, fingerprint)
    sidecar = _deps_sidecar(output)
    if entry_dir is None or not output.exists() or not sidecar.exists():
        return
    try:
        entry_dir.mkdir(parents=True, exist_ok=True)
        name = hashlib.sha256(sidecar.read_bytes()).hexdigest()[:16]
        for src, dst in ((output, entry_dir / f"{name}.obj"), (sidecar, entry_dir / f"{name}.deps.json")):
            tmp = dst.with_name(dst.name + f".{os.getpid()}.tmp")
            shutil.copyfile(src, tmp)
            os.replace(tmp, dst)
        entries = sorted(entry_dir.glob("*.obj"), key=lambda p: p.stat().st_mtime, reverse=True)
        for old in entries[OBJSTORE_KEEP:]:
            old.with_suffix(".deps.json").unlink(missing_ok=True)
            old.unlink(missing_ok=True)
    except OSError:
        pass  # the store is an accelerator; a failure only costs a recompile


def _sidecar_version(output):
    try:
        return json.loads(_deps_sidecar(output).read_text()).get("version")
    except (OSError, ValueError, AttributeError):
        return None


def try_compile_source(source, output, *, input_proof=None, inventory=False):
    """Compile `source` to `output`. Return (ok, filtered_output, returncode).

    `inventory` (link_census --build) records Open-BFME-1's include search
    inventory in the sidecar, and `input_proof` (census_receipts.Receipts)
    witnesses the compile's actual inputs for a TU whose sidecar cannot carry
    that proof; either asks for a census-grade receipt. The sidecar of the
    previous compile is dropped first, so a failed compile never leaves it able
    to bless the old object.
    """
    output.parent.mkdir(parents=True, exist_ok=True)
    inventory = inventory or input_proof is not None
    if inventory:
        _deps_sidecar(output).unlink(missing_ok=True)
    command, env = compiler_command(source, output)
    is_cl = source.suffix.lower() != ".asm"
    # Fingerprint the BASE command: the sweep-include retry below is a
    # deterministic function of these same inputs, so cache validity holds.
    fingerprint = _cmd_fingerprint(command, env)
    inventory_before = search_inventory(source, command, env) if inventory and is_cl else None
    retry_dirs = [] if inventory else None
    if not inventory and _restore_object(source, output, fingerprint):
        return True, "", 0
    filtered, code = "", 1
    # input_proof's preprocessor snapshots cost two `cl -E` runs per TU, and
    # the receipt they back is discarded whenever the sidecar comes out census
    # grade (version 2), which an include inventory usually achieves. So take
    # them only without an inventory, or on the one recompile below for a TU
    # whose inventory-backed sidecar did not reach version 2.
    proof_retry = inventory_before is None
    for attempt in range(4):  # one more than before, for that recompile
        before = (input_proof.before(source, output, command, env)
                  if input_proof and proof_retry else None)
        result = subprocess.run(
            command + (["-showIncludes"] if is_cl else []),
            cwd=ROOT,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
        )
        stdout = result.stdout or ""
        filtered = "\n".join(l for l in stdout.splitlines() if not l.startswith("Note: including file:"))
        code = result.returncode
        if code == 0:
            _write_deps_sidecar(source, output, fingerprint, stdout, is_cl,
                                command, env, inventory_before, retry_dirs)
            if input_proof and not proof_retry and _sidecar_version(output) != 2:
                proof_retry = True  # recompile once, witnessed by snapshots
                continue
            if input_proof:
                input_proof.after(source, output, command, env, before, stdout)
            _store_object(source, output, fingerprint)
            return True, filtered, 0
        # Retry once with the sweep include dirs on the path (header resolution
        # only — never affects codegen of already-matched sources).
        if attempt == 0 and any(d.exists() for d in _SWEEP_INCLUDE_DIRS):
            missing = any("Cannot open include file" in l for l in stdout.splitlines())
            if missing:
                env = dict(env)
                extra = ";".join(wine_path(d) for d in _SWEEP_INCLUDE_DIRS if d.exists())
                env["INCLUDE"] = env["INCLUDE"] + ";" + extra
                command = list(command) + [f"-I{wine_path(d)}" for d in _SWEEP_INCLUDE_DIRS if d.exists()]
                if inventory:
                    retry_dirs = [d.relative_to(ROOT).as_posix() for d in _SWEEP_INCLUDE_DIRS if d.exists()]
                    inventory_before = search_inventory(source, command, env) if is_cl else None
                continue
        transient = (not stdout.strip()
                     or "Application could not be started" in stdout
                     or "ShellExecuteEx failed" in stdout)
        if not transient or attempt >= 2:
            return False, filtered, code
        print(f"retrying transient Wine launch failure for "
              f"{source.relative_to(ROOT)} ({attempt + 2}/3)", file=sys.stderr)
    return False, filtered, code


def compile_source(source, output, *, input_proof=None, inventory=False):
    ok, text, code = try_compile_source(source, output, input_proof=input_proof, inventory=inventory)
    if ok:
        return
    print(f"compile failed: {source.relative_to(ROOT)}", file=sys.stderr)
    if text:
        print(text)
    raise SystemExit(code)


def is_funclet_row(row, object_symbol):
    """True for a gen-funclet row pinned to a compiler-local $L label."""
    return bool("gen-funclet" in (row.get("notes") or "")
                and re.fullmatch(r"\$L\d+", object_symbol))


def holds_funclet(body, relocs, target):
    """True if `body` starts with this row's funclet.

    Pre-link, every relocation site holds an addend rather than the address the
    linker wrote, so those bytes are masked out of both sides -- the same
    comparison compile_function makes, one step earlier and without the pins.
    """
    size = len(target)
    if len(body) < size:
        return False
    left, right = bytearray(body[:size]), bytearray(target)
    for offset, _rtype, _sym in relocs:
        if offset + 4 <= size:
            left[offset:offset + 4] = right[offset:offset + 4] = b"\0\0\0\0"
    return left == right


def funclet_candidates(path, row, target):
    """Every $L body in the claimed parent's group that IS this row's funclet.

    An SEH funclet has no name of its own, so those rows pin it to the
    compiler-local label its parent's COMDAT happened to receive. Those numbers
    are per-compilation ordinals: they shift whenever ANY unrelated edit to the
    TU changes how many labels precede them, and the pin then names a DIFFERENT
    body -- which is why nothing may trust one it has not just checked. When
    this was written 184 of the ledger's 20,045 funclet pins had already been
    renumbered off their body.

    Identity comes from evidence instead: inside the section that also holds
    __ehhandler$<parent> -- the parent's own funclet group -- the $L symbols
    whose bytes equal retail at this row's address. The caller decides, and only
    a unique answer may be used; a group of look-alikes has to fail loudly.
    """
    parent = re.search(r"(?:^|;)parent=([^;]+)", row.get("notes", ""))
    if not parent:
        return []
    stat = path.stat()
    data, sections, symbols = _object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    handler = f"__ehhandler${parent.group(1)}"
    group = [s["section"] for s in symbols
             if s["name"] == handler and s["section"] > 0]
    if not group:
        return []
    hits = []
    for symbol in symbols:
        if symbol["section"] != group[0] or not re.fullmatch(r"\$L\d+", symbol["name"]):
            continue
        try:
            body, relocs = read_object_symbol_bytes(path, symbol["name"], len(target))
        except ValueError:
            continue
        if holds_funclet(body, relocs, target):
            hits.append(symbol["name"])
    if len(hits) > 1:
        # Masking a call can make two different destructors look identical.
        # Use the already-established callee addresses before reporting an
        # ambiguity; candidates that still tie remain ambiguous.
        symbol_map = load_symbol_map()
        rva = int(row["target_rva"], 16)
        exact = []
        for name in hits:
            body, relocs = read_object_symbol_bytes(path, name, len(target))
            calls = [(offset, symbol) for offset, kind, symbol in relocs
                     if kind == 0x0014 and offset < len(target)]
            if all(offset + 4 <= len(target) and any(
                    struct.pack("<i", address - (rva + offset + 4))
                    == target[offset:offset + 4]
                    for address in symbol_map.get(symbol, ()))
                   for offset, symbol in calls):
                exact.append(name)
        hits = exact
    return hits


def read_funclet(row, object_symbol, output, target):
    """The bytes of a gen-funclet row's body, and a note when the pin was stale.

    Returns (bytes, relocs, note). The $L pin is a hint that has to earn its
    keep: the moment it does not hold this funclet, the body is re-identified
    from the parent's group (see funclet_candidates) or the row goes red with
    what it actually compiled. Nothing is ever picked from a field of two.
    """
    try:
        compiled, relocs = read_object_symbol_bytes(output, object_symbol, len(target), code_only=True)
    except ValueError as missing:
        compiled, relocs, gone = None, None, missing
    else:
        if holds_funclet(compiled, relocs, target):
            return compiled, relocs, None
        gone = None

    hits = funclet_candidates(output, row, target)
    if len(hits) > 1:
        raise SystemExit(
            f"{row['name']} ({row['source']}): {object_symbol} does not hold this funclet "
            f"and {len(hits)} bodies in the parent's group match it equally "
            f"({', '.join(hits)}). Byte evidence cannot tell them apart, so the gate will "
            "not pick one — the row needs a body it can name on its own.")
    if hits:
        compiled, relocs = read_object_symbol_bytes(output, hits[0], len(target), code_only=True)
        return compiled, relocs, (
            f"{object_symbol} was renumbered by an edit to this TU; the body is {hits[0]} "
            "in the object built now (stale ledger pin, not a byte mismatch)")
    if gone is not None:
        raise gone
    return compiled, relocs, (
        f"{object_symbol} no longer holds this funclet and nothing in the parent's group "
        "does either, so this is the body that label names now")


def compile_function(row, symbol_map, output):
    target_rva = int(row["target_rva"], 16)
    target_size = int(row["target_size"])
    target = read_target_bytes(target_rva, target_size)
    object_symbol = ledger_object_symbol(row)
    note = None
    if is_funclet_row(row, object_symbol):
        compiled, relocs, note = read_funclet(row, object_symbol, output, target)
    else:
        compiled, relocs = read_object_symbol_bytes(output, object_symbol, target_size, code_only=True)

    # A lib member is pre-link code: every relocation site still holds an addend
    # rather than the address the linker wrote, and its callees are
    # library-internal symbols no ledger row gives an address for, so none of
    # them can be resolved the way a compiled TU's are. Mask them all instead
    # and compare only the bytes in between; `concrete` reports how many that
    # leaves, because a comparison over too few bytes is not evidence.
    #
    # A gen-alias row (the ICF-twin dup_ convention: same body claimed at a
    # second address under an alias name) needs the same masking, but only as a
    # FALLBACK, never as a mode. Its object code is the original claim's
    # compiled TU, so every relocation site's symbol is known -- but the
    # candidate list load_symbol_map builds for that symbol covers only the
    # original claim's address and ITS thunks, not a sibling ICF fold of the
    # callee that this second address's own thunk chain routes through. Which
    # fold the twin encodes is exactly the position-dependent fact a twin's
    # rel32 legitimately differs on, so strict resolution cannot see it.
    #
    # Masking gen-alias rows UNCONDITIONALLY is wrong, and measurably so: it
    # drags them under the MIN_LIB_CONCRETE floor, and the 4-to-7-byte alias
    # rows that make up most of the 9600 already in the ledger have fewer than
    # eight non-relocation bytes by construction. Doing that failed 528 of
    # GameAudio.cpp's 3279 rows, a file that gates 3278/3278 without it. So try
    # strict first and keep it when it proves the row; fall back to masking only
    # for a row strict cannot prove. An ordinary conversion never takes the
    # fallback, and keeps full strictness.
    lib_member = (ROOT / row["source"]).suffix.lower() == LIB_SUFFIX
    gen_alias = "gen-alias" in notes_tokens(row)
    verified_folds = set()

    def resolve(masked):
        resolved = bytearray(compiled[:target_size])
        unresolved = []
        covered = bytearray(target_size)
        for offset, rtype, sym_name in relocs:
            if offset >= target_size:
                continue  # reloc belongs to a later function sharing the COMDAT section
            if masked:
                width = min(RELOC_WIDTH.get(rtype, 4), target_size - offset)
                resolved[offset : offset + width] = target[offset : offset + width]
                covered[offset : offset + width] = b"\1" * width
            elif rtype == 0x0006:  # IMAGE_REL_I386_DIR32
                resolved[offset : offset + 4] = target[offset : offset + 4]
            elif rtype == 0x0014:  # IMAGE_REL_I386_REL32
                # `resolved` is a bytearray, so assigning four bytes at
                # target_size-1..-3 EXTENDS it instead of failing: the row compiles
                # longer than it claims, clobbers its own last bytes on the way, and
                # surfaces as two hex dumps of different lengths naming neither the
                # extent nor this site. A call displacement cannot end after the
                # function does, so what is wrong here is the boundary, not the
                # write -- clipping would only make a wrong boundary compare equal.
                if offset + 4 > target_size:
                    raise SystemExit(
                        f"{row['name']} ({row['source']}): REL32 site at offset {offset} "
                        f"(0x{offset:x}) for {sym_name} needs {offset + 4} bytes but the row "
                        f"claims target_size {target_size}. The row's extent is wrong: raise "
                        "it to the real end of the function. This displacement is part of "
                        "this body, not of whatever follows it.")
                if sym_name in symbol_map:
                    next_address = target_rva + offset + 4
                    candidates = symbol_map[sym_name]
                    displacement = struct.pack("<i", candidates[0] - next_address)
                    for target_address in candidates[1:]:
                        if target[offset : offset + 4] == displacement:
                            break
                        displacement = struct.pack("<i", target_address - next_address)
                    resolved[offset : offset + 4] = displacement
                else:
                    called = (target_rva + offset + 4
                              + struct.unpack_from("<i", target, offset)[0]) & 0xFFFFFFFF
                    # A fold proves the named callee's entry, not an interior
                    # target encoded by a COFF addend. Only direct calls/jumps
                    # with zero addends may use this proof.
                    proof = None
                    if (offset >= 1 and compiled[offset - 1] in (0xE8, 0xE9)
                            and compiled[offset:offset + 4] == b"\0" * 4):
                        proof = stlport_folds.prove(
                            sys.modules[__name__], sym_name, called, output, symbol_map)
                    if proof is None:
                        unresolved.append(sym_name)
                    else:
                        verified_folds.update(proof)
                        resolved[offset:offset + 4] = struct.pack(
                            "<i", called - target_rva - offset - 4)

        return resolved, unresolved, covered

    resolved, unresolved, covered = resolve(lib_member)
    masked = lib_member
    if gen_alias and not lib_member and bytes(resolved) != target:
        alt_resolved, alt_unresolved, alt_covered = resolve(True)
        # The mask is admitted only where it hides a call to a TWIN of the
        # named callee: the retail target must have the named body's bytes
        # and the same resolved call/jump targets. Masking anything else
        # accepted a call to any function at all.
        if bytes(alt_resolved) == target and (
                gate_baselined("genalias", row)
                or not masked_call_problems(target, target_rva, relocs, resolved, symbol_map)):
            resolved, unresolved, covered = alt_resolved, alt_unresolved, alt_covered
            masked = True

    return {
        "name": row["name"],
        "target_rva": target_rva,
        "target": target,
        "bytes": bytes(resolved),
        "source": row["source"],
        "unresolved": unresolved,
        "relocs": relocs,
        "masked": masked,
        "concrete": target_size - sum(covered),
        "note": note,
        "verified_folds": verified_folds,
    }


REL32 = 0x0014
DIR32 = 0x0006
IMAGE_BASE = 0x400000


@functools.lru_cache(maxsize=1)
def _ledger_bodies():
    bodies = {}
    for row in load_all_function_rows():
        bodies.setdefault(row["name"], []).append((int(row["target_rva"], 16),
                                                    int(row["target_size"])))
    return bodies


def _rel32_window(data, at):
    """Start of the rel32 operand covering data[at], or None."""
    for start in range(max(at - 3, 1), at + 1):
        if data[start - 1] in (0xE8, 0xE9):
            return start
        if start >= 2 and data[start - 2] == 0x0F and 0x80 <= data[start - 1] <= 0x8F:
            return start
    return None


def retail_twins(a, b, size):
    """True when retail's bodies at a and b are the same code: equal bytes,
    and every differing byte inside a call/jump displacement that resolves to
    the SAME absolute target from both places."""
    try:
        da, db = read_target_bytes(a, size), read_target_bytes(b, size)
    except ValueError:
        return False
    i = 0
    while i < size:
        if da[i] == db[i]:
            i += 1
            continue
        start = _rel32_window(da, i)
        if (start is None or start != _rel32_window(db, i) or start + 4 > size
                or da[start - 1] != db[start - 1]):
            return False
        to_a = a + start + 4 + struct.unpack_from("<i", da, start)[0]
        to_b = b + start + 4 + struct.unpack_from("<i", db, start)[0]
        if to_a & 0xFFFFFFFF != to_b & 0xFFFFFFFF:
            return False
        i = start + 4
    return True


def masked_call_problems(target, target_rva, relocs, strict, symbol_map):
    """Call sites a gen-alias mask would hide that are NOT a twin of their callee."""
    bodies = _ledger_bodies()
    problems = []
    for offset, rtype, name in relocs:
        if rtype != REL32 or offset + 4 > len(target):
            continue
        if strict[offset:offset + 4] == target[offset:offset + 4]:
            continue
        called = (target_rva + offset + 4 + struct.unpack_from("<i", target, offset)[0]) & 0xFFFFFFFF
        named = bodies.get(name, [])
        if not any(retail_twins(called, body, size) for body, size in named):
            problems.append(f"+0x{offset:x} calls 0x{called:08X}, not a twin of {name}")
    return problems


@functools.lru_cache(maxsize=256)
def _function_starts(path_str, mtime_ns, size):
    """Per code section, the sorted offsets at which a function symbol starts."""
    _, _, symbols = _object_layout(path_str, mtime_ns, size)
    starts = {}
    for symbol in symbols:
        if (symbol["section"] > 0 and symbol["name"] and not symbol["name"].startswith("$")
                and (symbol.get("type") == 0x20 or symbol.get("storage") == 2)):
            starts.setdefault(symbol["section"], []).append(symbol["value"])
    for values in starts.values():
        values.sort()
    return starts


def body_extent_problems(row, patch, symbol_map, output, row_starts):
    """What the byte compare of the claimed extent cannot see. Returns
    [(check, message)] for:

    ltable    -- a same-section DIR32 (switch jump-table entry, `mov r, offset
                 $L`) whose retail value is not this row's own label: the
                 compare copies every DIR32 from retail, so a swapped case
                 mapping matched byte for byte. A same-section FUNCTION (a C
                 file's static callback) is bound by name instead.
    tail      -- compiled code/data past the row's extent that differs from
                 retail. Only bytes inside the extent were ever compared.
    truncated -- the compiled function continues past the extent, retail
                 agrees, and no other row claims those bytes: the row is a
                 prefix of the function it compiled.
    """
    rva = patch["target_rva"]
    size = len(patch["target"])
    body, relocs, info = read_object_symbol_bytes(
        output, ledger_object_symbol(row), size, code_only=True, detail=True)
    stat = output.stat()
    section, value = info["section"], info["value"]
    starts = _function_starts(str(output), stat.st_mtime_ns, stat.st_size).get(section, [])
    index = bisect.bisect_right(starts, value)
    end = starts[index] if index < len(starts) else info["section_size"]
    func = body[:end - value].rstrip(b"\xcc")
    problems = []
    try:
        retail = read_target_bytes(rva, max(len(func), size))
    except ValueError:
        retail = patch["target"]
        problems.append(("tail", f"compiled body is {len(func)} bytes; retail past the "
                                 f"{size}-byte extent is unreadable"))
    resolved = bytearray(func)
    for k, (offset, rtype, name) in enumerate(relocs):
        if offset >= len(func):
            continue
        if offset + 4 > len(retail):
            continue
        symbol = info["symbols"][info["reloc_symbols"][k]]
        if rtype == DIR32 and symbol["section"] == section:
            addend = u32(body, offset)
            got = u32(retail, offset)
            if not name.startswith("$") and (symbol.get("type") == 0x20
                                             or symbol.get("storage") == 2):
                address = (got - addend - IMAGE_BASE) & 0xFFFFFFFF
                if address not in symbol_map.get(name, ()):
                    problems.append(("ltable", f"+0x{offset:x} function pointer {name}: "
                                               f"retail 0x{address:08X} is not that function"))
            else:
                want = (IMAGE_BASE + rva + symbol["value"] + addend - value) & 0xFFFFFFFF
                if got != want:
                    problems.append(("ltable", f"+0x{offset:x} jump-table entry: compiled label "
                                               f"0x{want - IMAGE_BASE:08X}, retail 0x{got - IMAGE_BASE:08X}"))
            resolved[offset:offset + 4] = retail[offset:offset + 4]
        elif offset >= size:
            width = RELOC_WIDTH.get(rtype, 4)
            if rtype == REL32 and name in symbol_map:
                following = rva + offset + 4
                for candidate in symbol_map[name]:
                    displacement = struct.pack("<i", candidate - following)
                    if displacement == retail[offset:offset + 4]:
                        break
                resolved[offset:offset + 4] = displacement
            elif rtype != REL32:
                resolved[offset:offset + width] = retail[offset:offset + width]
    if len(func) > size:
        tail = len(func) - size
        if bytes(resolved[size:]) != retail[size:len(func)]:
            first = next(i for i in range(size, len(func)) if resolved[i] != retail[i])
            problems.append(("tail", f"compiled body continues {tail} byte(s) past the "
                                     f"{size}-byte extent and differs from retail at +0x{first:x}"))
        else:
            index = bisect.bisect_right(row_starts, rva)
            if index >= len(row_starts) or row_starts[index] >= rva + len(func):
                problems.append(("truncated", f"compiled body is {len(func)} bytes and retail "
                                              f"agrees, but the row claims {size}: raise its extent"))
    return problems


GHIDRA_FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
# MSVC hashes the absolute source path into anonymous-namespace symbols, so the
# same function carries a different token in every clone. Naming a retail
# address after one would churn this file on each contributor's gate.
CLONE_LOCAL_RE = re.compile(r"\?A0x[0-9A-Fa-f]{8}")
# tools/gen_dump.py mints Gen_t_/Gen_dtor_ classes for the machine-generated
# funclet TUs, and tools/gen_uw.py mints the whole Gen_uw* family (Gen_uw_,
# Gen_uwm_, Gen_uwh<pad>_, Gen_uws<size>_, Gen_uwt_, Gen_uwp_, Gen_uw_new).
# Those names are this project's own bookkeeping, not identity recovered from
# retail, and they outnumber the recovered names roughly two to one. Published
# marked so the queue can tell a real class and signature from a placeholder
# that only looks like one. Every generator that mints a name has to be listed
# here: the Gen_uw* family was invisible to this pattern for one phase and 15 of
# its pins were published as recovered identity.
GEN_PLACEHOLDER_RE = re.compile(
    r"Gen_(?:t|dtorv?)_[0-9a-f]{8}|Gen_uw[a-z]*\d*_"
    # The conversion lanes also mint ADDRESS-DERIVED names whose whole point
    # is to DISCLAIM identity: Gen<RVA>, gen<RVA>, Gen_<rva>, Rva<RVA>Thing.
    # Without this arm 2061 such names were being written into
    # reverse/reloc_names.csv as identity=real -- the precise opposite of
    # what the naming convention asserts. Eight hex digits with no ninth
    # keeps it from matching an ordinary identifier that merely starts "Gen".
    r"|(?:Gen|gen|Rva|rva)_?[0-9A-Fa-f]{8}(?![0-9A-Fa-f])")
# tools/zh_sweep.py names a row ?dup_<rva>@@YAXXZ when the bytes are proven by a
# Zero Hour twin but the identity is not: the twin is one member of an ICF fold
# and the reference TU's COMDAT it compiled is recorded in object-symbol= only
# as the build directive it is. Such a row claims an address without naming it.
DUP_ALIAS_RE = re.compile(r"^\?dup_[0-9a-f]{8}@@YAXXZ$")
DUP_ALIAS_ANYCASE_RE = re.compile(r"^\?dup_[0-9A-Fa-f]{8}@@YAXXZ$")
# Ghidra's own default names always bake the function's address into the
# label -- FUN_<va>, LAB_<va>, SUB_<va>, DAT_<va>, PTR_<va>, switchD_<va>,
# joined_r0x<va>, Unwind@<va>, Catch@<va> (confirmed against the committed
# inventory: 39,076 FUN_, 23,354 Unwind@, 81 Catch@ rows all embed their own
# RVA plus the 0x400000 image base as lowercase hex). Require a known
# Ghidra prefix as well as the address so a real name containing that address
# is not mistaken for a placeholder. thunk_FUN_ is the one
# exception: it names a thunk stub after its call TARGET's address, not its
# own, so it is matched by literal prefix instead (199 rows, verified against
# the same inventory; no real ledger/pin name uses this or the @-suffixed
# prefixes above, so the literal check cannot shadow a genuine identity).
_GHIDRA_ADDRESS_PREFIXES = (
    "fun_", "lab_", "sub_", "dat_", "ptr_", "switchd_", "joined_r0x",
    "unwind@", "catch@",
)
_GHIDRA_THUNK_PREFIX = "thunk_fun_"


def is_ghidra_autoname(name, rva):
    """True when a ghidra_functions.csv name is Ghidra's own placeholder.

    A narrower `startswith("FUN_")` check missed the 23,634 Unwind@/Catch@/
    thunk_FUN_ rows the committed inventory already carries -- SEH funclet
    and thunk labels that are exactly as identity-free as FUN_ but do not
    start with it. select_reloc_names used the narrow check to decide an
    address has no independent Ghidra opinion yet; against those rows it was
    silently wrong, over-trusting a label that names nothing.
    """
    lower = name.lower()
    if lower.startswith(_GHIDRA_THUNK_PREFIX):
        return True
    return lower.startswith(_GHIDRA_ADDRESS_PREFIXES) and f"{rva + 0x400000:08x}" in lower


def harvest_reloc_names(patches):
    """Name retail functions from the call sites of rows proven byte-true.

    A byte-true row's compiled bytes ARE the retail bytes, so each REL32
    relocation sits exactly where retail encodes that call's displacement and
    the relocation carries the callee's mangled name. The callee is therefore
    decoded from the RETAIL bytes, gated on the byte in front of the
    displacement being the call opcode: asking compile_function's resolver
    instead would only ever return callees already listed in symbols.csv, which
    is no new identity at all.

    The decoded address is usually not the body. Intra-module calls go through
    an incremental-link thunk, so a lone `jmp` at the target is followed to the
    body it stands for.

    A ?dup_<rva> row does not contribute. Its bytes are retail's, but the
    relocation SYMBOLS are the Zero Hour TU's names for the Zero Hour functions
    an arbitrary fold member calls -- and where BFME folded a different set,
    that name is simply wrong here. Two landed twins of ZH's
    GadgetSliderSetDisabled*ThumbColor named 0x00479040 winSetDisabledColor,
    colliding with the ?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z that six
    BFME call sites had recovered, and select_reloc_names dropped the address
    rather than guess. A row that admits it is not an identity cannot lend its
    callee names to an identity harvest.

    Returns {body rva: {"names": set, "sources": set, "sites": int}}.
    """
    data, sections = exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    thunks = {}

    def follow(rva):
        if rva not in thunks:
            thunks[rva] = follow_thunk(data, sections, rva, low, high)
        return thunks[rva]

    named = {}
    for patch in patches:
        if DUP_ALIAS_RE.match(patch["name"]):
            continue
        target = patch["target"]
        for offset, rtype, symbol in patch["relocs"]:
            if rtype != REL32 or offset < 1 or offset + 4 > len(target):
                continue
            if target[offset - 1] != 0xE8:
                continue
            callee = (patch["target_rva"] + offset + 4
                      + struct.unpack_from("<i", target, offset)[0])
            if not low <= callee < high:
                continue
            entry = named.setdefault(follow(callee),
                                     {"names": set(), "sources": set(), "sites": 0})
            entry["names"].add(symbol)
            entry["sources"].add(patch["source"])
            entry["sites"] += 1
    return named


def select_reloc_names(named):
    """Keep only harvested names that identify one unclaimed anonymous function.

    Both filters are load-bearing. Identical-code folding gives one address
    several legitimate names, and a shared address that acquires two of them is
    a contradiction the arity gate cannot see, so an address named more than one
    way is dropped rather than guessed at. Addresses the ledger already claims,
    or that Ghidra already names, are not new identity.

    "Claims" means NAMES, not covers. A gen-dump row pins bytes under a
    synthetic name and a ?dup_<rva> row pins them under a Zero Hour twin whose
    identity it explicitly disclaims; both leave the address anonymous, and
    both would otherwise swallow the one piece of evidence that could name it
    -- the recovered ?findCommandSet@ControlBar@@... at 0x4A0340 survived only
    because a human went looking after the line vanished. A reverse/symbols.csv
    pin is a claim the same way: it is a human's identity assertion for that
    address, just not yet backed by a compiling body, so it counts too.
    """
    inventory = {}
    with GHIDRA_FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            inventory[int(row["rva"], 16)] = (int(row["size"]), row["name"])
    claimed = {int(row["target_rva"], 16) for row in load_all_function_rows()
               if not is_scaffold_row(row) and not DUP_ALIAS_RE.match(row["name"])}
    if SYMBOLS.exists():
        with SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                try:
                    claimed.add(int(row["address"], 16))
                except ValueError:
                    pass

    selected = []
    for rva, entry in sorted(named.items()):
        if len(entry["names"]) != 1:
            continue
        name = next(iter(entry["names"]))
        if CLONE_LOCAL_RE.search(name):
            continue
        known = inventory.get(rva)
        if known is None or rva in claimed or not is_ghidra_autoname(known[1], rva):
            continue
        selected.append({
            "name": name,
            "target_rva": f"0x{rva:08X}",
            "target_size": str(known[0]),
            "source": min(entry["sources"]),
            "notes": (f"reloc-derived;call-sites={entry['sites']};identity="
                      + ("generated" if GEN_PLACEHOLDER_RE.search(name)
                         else "real")),
        })
    return selected


def write_reloc_names(patches):
    """Regenerate reverse/reloc_names.csv from this gate's byte-true rows.

    Regenerated, never appended: it is derived output, and a row that stops
    being re-derivable must stop being published. There is deliberately no
    status column — what is byte-verified here is the naming evidence, not the
    named function's body, and no derived file gets to imply otherwise.
    """
    selected = select_reloc_names(harvest_reloc_names(patches))
    with RELOC_NAMES.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(
            handle, ["name", "target_rva", "target_size", "source", "notes"],
            lineterminator="\n")
        writer.writeheader()
        writer.writerows(selected)
    real = sum(1 for row in selected if row["notes"].endswith("identity=real"))
    print(f"Reloc names: {len(selected)} anonymous function(s) named from "
          f"byte-true call sites ({real} recovered identity, "
          f"{len(selected) - real} generated placeholder) -> "
          f"{RELOC_NAMES.relative_to(ROOT)}")
    return selected


def _pool_size():
    return max(1, min(int(os.environ.get("BUILD_POOL", "1")), os.cpu_count() or 1))


def _stale_chunk(pairs, strict=False):
    cache = {}
    stale = [source for source, output in pairs
             if not compile_is_current(source, output, strict=strict, inventory_cache=cache)]
    if strict and not _inventory_cache_still_current(cache):
        raise SystemExit("include search directories changed during cache selection; rerun build")
    return stale


def _strict_stale_chunk(pairs):
    return _stale_chunk(pairs, strict=True)


def stale_sources(sources, source_outputs, workers=1, *, strict=False):
    """Sources whose object is not provably current (compile_is_current).

    Hashing every source and recorded header is CPU-bound Python (Open-BFME-1
    measured ~5.5 minutes on one core for 21,000 TUs). With BUILD_POOL > 1 the
    check is split across that many processes; the answer is the same set.
    """
    pairs = [(source, source_outputs[source]) for source in sources]
    chunk = _strict_stale_chunk if strict else _stale_chunk
    if workers <= 1 or len(pairs) < 200:
        return chunk(pairs)
    with concurrent.futures.ProcessPoolExecutor(workers) as pool:
        return [source for part in pool.map(chunk, [pairs[i::workers] for i in range(workers)])
                for source in part]


def compile_rows(rows, sources, *, input_proof=None, strict=False):
    """Compile every source whose object is not current; return {source: object}.
    The compile phase of verify_functions, callable on its own (link_census).
    `strict` (link_census --build): currency is compile_is_current(strict=True)
    and every compile records its include search inventory; `input_proof`
    witnesses each compile's inputs (census_receipts)."""
    extract_lib_members(rows)
    sources = [s for s in sources if s.suffix.lower() != LIB_SUFFIX]
    source_outputs = {s: obj_path(s) for s in sources}
    if len(set(source_outputs.values())) != len(source_outputs):
        raise SystemExit("obj stem collision between sources; refusing parallel compile")
    # wine cl.exe instances are independent processes; compile is the wall-clock
    # hog (byte comparison below is pure reads), so parallelize only this phase
    # Incremental mode (BUILD_RECOMPILE_ONLY="a.cpp;b.cpp"): reuse existing .obj
    # files for every source NOT listed - valid only when the caller proves the
    # unlisted sources and all headers are identical to the previous verified
    # build in this same tree (the fleet verifier does, via git diff). A missing
    # .obj is compiled regardless; never silently reused when absent.
    recompile_only = os.environ.get("BUILD_RECOMPILE_ONLY")
    if recompile_only is not None:
        wanted = {w for w in recompile_only.split(";") if w}
        to_compile = [s for s in sources
                      if str(s.relative_to(ROOT)) in wanted or not source_outputs[s].exists()]
        print(f"Incremental compile: {len(to_compile)} of {len(sources)} source(s)")
    else:
        # Sound dep-cache: skip every TU whose obj provably matches its current
        # source + flags + recorded headers (see compile_is_current). A TU with
        # no sidecar (first gate after this change, or flagged uncacheable)
        # recompiles. This is what turns a header-edit gate from ~17 min of
        # recompile-the-world into seconds-per-actual-includer.
        to_compile = stale_sources(sources, source_outputs, _pool_size(), strict=strict)
        cached = len(sources) - len(to_compile)
        if cached:
            print(f"Compile: {len(to_compile)} of {len(sources)} TU(s) "
                  f"(deps-cache: {cached} current)")
    # BUILD_POOL controls compile parallelism. Default 1: a single build.py call
    # (a worker verifying its own 1-2 files, or the fleet's per-task fast verify)
    # must NOT fork an 8-way wine pool - dozens of concurrent callers would then
    # oversubscribe the cores into a stall. Only the full-suite periodic audit,
    # which runs alone, sets BUILD_POOL=8 to compile all 260+ TUs in parallel.
    pool_size = _pool_size()
    # Host-wide wine/cl mutex: concurrent FULL builds thrash each other (and wine
    # cl fails at high concurrency), so a full build (>8 TUs) takes the lock
    # EXCLUSIVELY and they serialize against each other. Small per-file verifies
    # take NO lock: they must never wait behind a sibling clone's full gate — that
    # stall serialized every worker to a crawl. A full build compiles one cl.exe
    # at a time here (BUILD_POOL=1), so unlocked per-file verifies running
    # alongside it stay within the core count.
    lock_dir = Path.home() / ".cache"
    lock_dir.mkdir(parents=True, exist_ok=True)
    exclusive = len(to_compile) > 8
    lock_file = None
    if exclusive:
        lock_file = (lock_dir / "open-bfme-build.lock").open("a")
        lock(lock_file, exclusive=True,
             wait_notice="waiting for build lock (another clone is running a full build)...")
    try:
        proof = {"input_proof": input_proof, "inventory": True} if strict or input_proof is not None else {}
        if pool_size == 1 or len(to_compile) <= 1:
            for s in to_compile:
                compile_source(s, source_outputs[s], **proof)
        else:
            with concurrent.futures.ThreadPoolExecutor(pool_size) as pool:
                futures = {pool.submit(compile_source, s, source_outputs[s], **proof): s for s in to_compile}
                for future in concurrent.futures.as_completed(futures):
                    future.result()
    finally:
        if lock_file is not None:
            unlock(lock_file)
            lock_file.close()
    return source_outputs


def verify_functions(only=None):
    rows = load_function_rows()
    if only:
        rows = [row for row in rows if any(sel in row["source"] or sel in row["name"] for sel in only)]
        if not rows:
            raise SystemExit("no functions match: " + ", ".join(only))
    total = len(rows)
    symbol_map = load_symbol_map()

    sources = []
    seen = set()
    for row in rows:
        source = ROOT / row["source"]
        if source not in seen:
            seen.add(source)
            sources.append(source)
    missing = [s for s in sources if not s.exists()]
    if missing:
        raise SystemExit("functions.csv references missing source file(s): "
                         + ", ".join(str(m) for m in missing)
                         + " - a commit added rows without adding the file")
    # Split by kind BEFORE anything reaches the compiler: a .lib is a build
    # input to read, not a translation unit, and cl.exe would choke on it.
    source_outputs = compile_rows(rows, sources)

    failures = 0
    patches = []
    renumbered = []
    row_starts = sorted({int(row["target_rva"], 16) for row in load_all_function_rows()})
    for row in rows:
        try:
            patch = compile_function(row, symbol_map, row_object(row))
        except ValueError as unreadable:
            # A row whose body cannot be read is a RED row, not a dead gate.
            # read_funclet raises exactly this when a funclet pin names no label
            # in the object and cannot be re-identified from its parent's group
            # (a renumbered pin with no parent= is the measured case), and
            # read_object_symbol_bytes raises it for any row whose symbol the
            # object no longer emits. Letting it escape aborts the whole gate on a
            # traceback before a single FAIL is printed, which is how one stale
            # pin hid every other row's verdict and blocked unrelated commits.
            # The row still counts as a failure, so the gate still exits non-zero:
            # only the reporting changes, never the verdict.
            failures += 1
            print(f"  FAIL {row['name']} ({row['source']})")
            print(f"    unverifiable: {unreadable}")
            continue
        target = patch["target"]
        compiled = patch["bytes"]

        thin = patch["masked"] and patch["concrete"] < MIN_LIB_CONCRETE
        if compiled == target and not thin:
            extent = []
            if (ROOT / row["source"]).suffix.lower() != LIB_SUFFIX and not is_funclet_row(
                    row, ledger_object_symbol(row)):
                extent = [(check, message) for check, message in
                          body_extent_problems(row, patch, symbol_map, row_object(row), row_starts)
                          if not gate_baselined(check, row)]
            if extent:
                failures += 1
                print(f"  FAIL {row['name']} ({row['source']})")
                for check, message in extent[:6]:
                    print(f"    {check}: {message}")
                continue
            patches.append(patch)
            if patch["note"]:
                renumbered.append(f"{row['name']} ({row['source']}): {patch['note']}")
            continue

        failures += 1
        print(f"  FAIL {row['name']} ({row['source']})")
        if patch["note"]:
            print(f"    {patch['note']}")
        if thin and compiled == target:
            print(f"    only {patch['concrete']} of {len(target)} byte(s) lie outside a "
                  "relocation site; a masked comparison this thin proves nothing")
            continue
        if patch["unresolved"]:
            calls = ", ".join(sorted(set(patch["unresolved"])))
            print(f"    unresolved call(s): {calls} (add to reverse/symbols.csv)")
        print(f"    target:   {format_bytes(target)}")
        print(f"    compiled: {format_bytes(compiled)}")

    if renumbered:
        # Green, but on a pin the ledger got wrong: say so every time, or the
        # only record of a rotting pin is the day it lands on a look-alike.
        print(f"Funclet pins: {len(renumbered)} row(s) verified past a renumbered $L label")
        for line in renumbered[:5]:
            print(f"    {line}")

    verified_folds = set().union(*(patch["verified_folds"] for patch in patches)) if patches else set()
    if verified_folds:
        print(f"STLport folds: {len(verified_folds)} complete emitted constructor(s) "
              "verified against retail owners and resolved callees")

    if failures:
        print(f"Functions: FAIL {failures}/{total}")
        print(f"{failures} function(s) failed byte comparison")
        raise SystemExit(1)

    source_count = len({row["source"] for row in rows})
    if total == 1:
        row = rows[0]
        print(f"Functions: OK 1/1 matched")
        print(f"  {row['name']} ({row['source']})")
    else:
        print(f"Functions: OK {total}/{total} matched across {source_count} source file(s)")

    # Only a full gate may rewrite the derived file: a scoped run proves a
    # handful of rows and would silently publish that handful as the whole set.
    if not only:
        write_reloc_names(patches)

    return patches


def patch_exe(patches, output):
    output.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(EXE, output)

    data = bytearray(output.read_bytes())
    sections = pe_sections(data)
    ranges = []
    for patch in sorted(patches, key=lambda entry: entry["target_rva"]):
        offset = rva_to_file_offset(sections, patch["target_rva"])
        end = offset + len(patch["bytes"])
        if data[offset:end] != patch["target"]:
            raise SystemExit(f"{patch['name']}: target bytes changed before patching")
        if ranges and offset < ranges[-1][1]:
            # ICF alias group: a previous patch wrote byte-identical code to this
            # exact range (folded COMDATs share one address). Re-applying is a no-op.
            if offset == ranges[-1][0] and end == ranges[-1][1] and patch["bytes"] == data[offset:end]:
                continue
            raise SystemExit(f"{patch['name']}: patch overlaps previous patch")
        ranges.append((offset, end))
        data[offset:end] = patch["bytes"]

    output.write_bytes(data)
    return output


def verify_noop_patch(patches):
    patch_exe(patches, NOOP_EXE)

    original_sha256 = hash_file(EXE, "sha256")
    patched_sha256 = hash_file(NOOP_EXE, "sha256")

    if patched_sha256 != original_sha256:
        raise SystemExit(
            f"No-op patch: FAIL {NOOP_EXE.relative_to(ROOT)} sha256 {patched_sha256} != {original_sha256}"
        )
    print(f"No-op patch: OK {NOOP_EXE.relative_to(ROOT)}")


# Keyed, shrink-only debt register for gate checks that went live with rows
# already red: one line per (check, retail address, ledger name). A key excuses
# exactly that row from exactly that check. tools/gate_baseline.py refuses any
# commit that adds a line, so the file can only shrink.
GATE_BASELINE = ROOT / "reverse" / "gate_baseline.txt"


def gate_baseline_key(check, row):
    return f"{check} 0x{int(row['target_rva'], 16):08X} {row['name']}"


@functools.lru_cache(maxsize=4)
def _gate_baseline(path_str, mtime_ns):
    path = Path(path_str)
    if not mtime_ns or not path.exists():
        return frozenset()
    return frozenset(line.strip() for line in path.read_text(encoding="utf-8").splitlines()
                     if line.strip() and not line.startswith("#"))


def gate_baselined(check, row):
    try:
        mtime = GATE_BASELINE.stat().st_mtime_ns
    except OSError:
        mtime = 0
    return gate_baseline_key(check, row) in _gate_baseline(str(GATE_BASELINE), mtime)


def string_literal_bytes(symbol, section_bytes):
    """MSVC's literal length includes its terminator, but excludes COFF padding.

    A digit encodes lengths 1..10; A..P digits encode a hexadecimal length
    terminated by @. The length is in bytes for both narrow and UTF-16 strings.
    Preserve embedded/trailing NULs instead of rstrip-ing away evidence.
    Ported from Open-BFME-1 0223827f8c.
    """
    match = re.match(r"\?\?_C@_([01])([0-9]|[A-P]+@)", symbol)
    if not match:
        raise ValueError("unrecognized MSVC string-literal length")
    width = 2 if match[1] == "1" else 1
    encoded = match[2]
    length = int(encoded) + 1 if encoded.isdigit() else 0
    if not encoded.isdigit():
        for digit in encoded[:-1]:
            length = length * 16 + ord(digit) - ord("A")
    if length < width or length % width or length > len(section_bytes):
        raise ValueError("invalid or truncated MSVC string literal")
    value = section_bytes[:length]
    if value[-width:] != b"\0" * width:
        raise ValueError("MSVC string literal has no complete terminator")
    return value


def verify_string_refs(rows):
    """Independently VERIFY (not mask) every DIR32 relocation that points at a string literal:
    read the address the compiled code references, and confirm the string AT that address in the
    binary byte-equals the compiled literal. Self-verifying (no pins) — catches source/binary string
    discrepancies that compile_function's DIR32 masking otherwise hides (e.g. "%S" vs "%ls",
    "ParticleSystemInfo" vs "FXParticleSystemInfo"). Reuses the objs already built by verify_functions."""
    exe = EXE.read_bytes()
    pe = pe_sections(exe)
    mismatches = []
    checked = 0
    empty_ok = 0
    for row in rows:
        obj = require_row_object(row)
        target_rva = int(row["target_rva"], 16)
        target_size = int(row["target_size"])
        target = read_target_bytes(target_rva, target_size)
        try:
            if is_funclet_row(row, ledger_object_symbol(row)):
                fn_bytes, relocs, _ = read_funclet(
                    row, ledger_object_symbol(row), obj, target)
            else:
                fn_bytes, relocs = read_object_symbol_bytes(
                    obj, ledger_object_symbol(row), target_size)
        except ValueError:
            continue
        for offset, rtype, sym in relocs:
            if rtype != 0x0006 or offset + 4 > target_size or not sym.startswith("??_C@"):
                continue
            # No silent skip: a string reference we cannot verify is a hole in the guarantee, so a
            # genuine extraction/RVA failure is surfaced as a mismatch (fail loudly), not swallowed.
            try:
                cs, _ = read_object_symbol_bytes(obj, sym)
                str_rva = struct.unpack_from("<I", target, offset)[0] - 0x400000
            except (ValueError, struct.error) as exc:
                mismatches.append((row, f"<unverifiable {sym[:24]}: {exc}>".encode(), b""))
                continue
            # DIR32 relocs carry an addend (pre-link value at the site): pooled string reuse
            # references symbol+addend (e.g. "DBGHELP.DLL"+4 == "ELP.DLL"), so the referenced
            # literal is content[addend:], and the binary holds it at str_rva == sym_rva+addend.
            addend = struct.unpack_from("<i", fn_bytes, offset)[0] if offset + 4 <= len(fn_bytes) else 0
            # The literal ENDS where its terminator is: comparing only the
            # characters before it let any prefix of the retail string pass
            # ("Default" for retail "Default ", L"000" for L"00000000.sav").
            try:
                literal = string_literal_bytes(sym, cs)
            except ValueError as exc:
                mismatches.append((row, f"<unverifiable {sym[:24]}: {exc}>".encode(), b""))
                continue
            if not 0 <= addend < len(literal):
                mismatches.append((row, f"<invalid literal addend {addend}>".encode(), b""))
                continue
            content = literal[addend:]
            try:
                actual = read_pe_bytes(exe, pe, str_rva, len(content))
            except ValueError as exc:
                mismatches.append((row, f"<unverifiable {sym[:24]}: {exc}>".encode(), b""))
                continue
            if actual != content:
                mismatches.append((row, content, actual))
            elif not content.strip(b"\0"):
                empty_ok += 1
            else:
                checked += 1
    known = [m for m in mismatches if gate_baselined("strnul", m[0])]
    mismatches = [m for m in mismatches if not gate_baselined("strnul", m[0])]
    if mismatches:
        print(f"String-ref verify: FAIL {len(mismatches)} mismatch(es) (source string != binary string)")
        for row, src_s, bin_s in mismatches[:12]:
            print(f"    {row['name']}: source={src_s!r} binary={bin_s!r}")
        raise SystemExit(1)
    print(f"String-ref verify: OK ({checked} literals + {empty_ok} empty-string refs verified, "
          f"{len(known)} baselined, 0 unverified/skipped)")


REAL_LITERAL_RE = re.compile(r"__real@(?:[0-9a-fA-F]{8}|[0-9a-fA-F]{16})$")


def verify_float_refs(rows):
    """Verify compiler float/double literals independently of DIR32 patching.

    A copied pointer can make a source return 1.0f while retail loads 0.0f.
    Compare the object's literal bits at the referenced retail address, even
    if only one function uses that symbol. Equal literals may legitimately
    reside at several addresses because the linker need not pool them.
    """
    checked, mismatches = 0, []
    for row in rows:
        obj = require_row_object(row)
        size = int(row["target_size"])
        target = read_target_bytes(int(row["target_rva"], 16), size)
        try:
            if is_funclet_row(row, ledger_object_symbol(row)):
                body, relocs, _ = read_funclet(row, ledger_object_symbol(row), obj, target)
            else:
                body, relocs = read_object_symbol_bytes(obj, ledger_object_symbol(row), size)
        except ValueError as exc:
            mismatches.append((row["name"], "<body>", f"unverifiable: {exc}"))
            continue
        for offset, kind, symbol in relocs:
            if kind != 0x0006 or not REAL_LITERAL_RE.fullmatch(symbol) or offset + 4 > size:
                continue
            width = len(symbol.split("@", 1)[1]) // 2
            try:
                literal, _ = read_object_symbol_bytes(obj, symbol)
                if len(literal) < width:
                    raise ValueError("truncated compiler literal")
                address = struct.unpack_from("<I", target, offset)[0]
                addend = struct.unpack_from("<I", body, offset)[0]
                rva = ((address - addend) & 0xFFFFFFFF) - 0x400000
                actual = read_target_bytes(rva, width)
                expected = literal[:width]
                if actual != expected:
                    mismatches.append((row["name"], symbol,
                                       f"source={expected.hex()} retail={actual.hex()} at RVA 0x{rva:08X}"))
                else:
                    checked += 1
            except (ValueError, struct.error) as exc:
                mismatches.append((row["name"], symbol, f"unverifiable: {exc}"))
    if mismatches:
        print(f"Float-ref verify: FAIL {len(mismatches)} mismatch(es)")
        for name, symbol, detail in mismatches[:12]:
            print(f"    {name}: {symbol} {detail}")
        raise SystemExit(1)
    print(f"Float-ref verify: OK ({checked} compiler literals verified)")


def verify_import_refs(rows):
    """Check imported call/data identities independently of copied DIR32s.

    A unique byte match can still call GlobalFree where the source names
    InterlockedIncrement. Read the PE's own import directory, then require
    the source's COFF import name at each referenced IAT slot. No address
    pin, function-name alias, or ordinal-only guess can satisfy this check.
    """
    from pe_imports import coff_import_names, read_imports

    try:
        imports = read_imports(EXE.read_bytes())
    except ValueError as exc:
        raise SystemExit(f"Import-ref verify: FAIL unreadable PE imports: {exc}")
    checked, mismatches = 0, []
    for row in rows:
        obj = require_row_object(row)
        size = int(row["target_size"])
        target = read_target_bytes(int(row["target_rva"], 16), size)
        symbol = ledger_object_symbol(row)
        try:
            if is_funclet_row(row, symbol):
                body, relocs, _ = read_funclet(row, symbol, obj, target)
            else:
                body, relocs = read_object_symbol_bytes(obj, symbol, size)
        except ValueError as exc:
            mismatches.append((row["name"], "<body>", f"unverifiable: {exc}"))
            continue
        for offset, kind, symbol in relocs:
            if kind != 0x0006 or not symbol.startswith("__imp_") or offset + 4 > size:
                continue
            try:
                address = struct.unpack_from("<I", target, offset)[0]
                addend = struct.unpack_from("<I", body, offset)[0]
                slot = (address - addend) & 0xFFFFFFFF
                entry = imports.get(slot)
                if entry is not None and entry.name in coff_import_names(symbol):
                    checked += 1
                    continue
                actual = (f"{entry.dll}!{entry.name or ('ordinal ' + str(entry.ordinal))}"
                          if entry is not None else "not a declared IAT slot")
                mismatches.append((row["name"], symbol, f"0x{slot:08X}: {actual}"))
            except struct.error as exc:
                mismatches.append((row["name"], symbol, f"unverifiable: {exc}"))
    if mismatches:
        print(f"Import-ref verify: FAIL {len(mismatches)} mismatch(es)")
        for name, symbol, detail in mismatches[:20]:
            print(f"    {name}: {symbol} {detail}")
        raise SystemExit(1)
    print(f"Import-ref verify: OK ({checked} named imports verified)")


def verify_dir32_consistency(rows):
    """Regression gate for the non-string DIR32s (globals/vtables/func-addrs) build.py masks. A symbol
    has one address, so every reference must resolve to the same base once the addend is subtracted
    (base = binary_addr - compiled_addend). A symbol with >1 base is a candidate hidden discrepancy.
    Whitelist (reverse/dir32_consistency_whitelist.txt) holds the CURRENT known-legitimate cases
    (double-linked TUs CRC32_Table/_COLLISION_EPSILON; the investigated FX ctor/dtor vtable artifacts).
    Hand-written only: an absent whitelist is a hard failure listing the candidates, never an
    auto-written free pass, and any NEW inconsistency FAILS."""
    from collections import defaultdict
    whitelist_path = ROOT / "reverse" / "dir32_consistency_whitelist.txt"
    sym2base = defaultdict(set)
    static_symbols = {}
    for row in rows:
        obj = require_row_object(row)
        trva, tsz = int(row["target_rva"], 16), int(row["target_size"])
        target = read_target_bytes(trva, tsz)
        try:
            if is_funclet_row(row, ledger_object_symbol(row)):
                body, relocs, _ = read_funclet(row, ledger_object_symbol(row), obj, target)
            else:
                body, relocs = read_object_symbol_bytes(
                    obj, ledger_object_symbol(row), tsz)
        except ValueError:
            continue
        for off, rtype, sym in relocs:
            if rtype != 0x0006 or off + 4 > tsz or off + 4 > len(body) or sym.startswith("??_C@"):
                continue
            # Compiler-local labels ($L1234 funclets, $T294 funcinfo, $SG strings)
            # are TU-scoped: object-symbol= rows alias ONE anchor TU's label onto
            # thousands of retail instances by design, so "one symbol, one
            # address" only holds for external symbols. Locals add no detection
            # power for double-linked TUs (those always expose externals too).
            if re.fullmatch(r"\$[A-Za-z]+\d+", sym):
                continue
            # __ehhandler$<mangled> is the same case one step out: the compiler
            # emits one per TU alongside the COMDAT it guards, and retail does
            # not fold COMDATs, so a template instantiation claimed at N retail
            # addresses legitimately resolves its handler to N stub addresses.
            if sym.startswith("__ehhandler$"):
                continue
            # The literal verifier checks their actual bits independently.
            # Distinct copies of the same constant need not share an address.
            if REAL_LITERAL_RE.fullmatch(sym):
                continue
            if obj not in static_symbols:
                stat = obj.stat()
                _, _, symbols = _object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
                static_symbols[obj] = {s["name"] for s in symbols
                                       if s.get("storage") == 3 and s["section"] > 0}
            # IMAGE_SYM_CLASS_STATIC data belongs to its translation unit.
            # Header-local constants can share a spelling in different objects;
            # their addresses must agree only within the same source file.
            identity = f"{row['source']}::{sym}" if sym in static_symbols[obj] else sym
            final = struct.unpack_from("<I", target, off)[0]
            addend = struct.unpack_from("<I", body, off)[0]
            sym2base[identity].add((final - addend) & 0xFFFFFFFF)
    inconsistent = sorted(s for s, b in sym2base.items() if len(b) > 1)
    # Duplicate IAT entries can independently declare the exact same import.
    # This is PE metadata evidence, not an address whitelist: both the DLL and
    # export must agree, and the export must match the source's COFF spelling.
    import_duplicates = set()
    if any(s.startswith("__imp_") for s in inconsistent):
        from pe_imports import read_imports, same_named_import_slots
        try:
            imports = read_imports(EXE.read_bytes())
        except ValueError as exc:
            raise SystemExit(f"DIR32 consistency: unreadable PE imports: {exc}")
        import_duplicates = {s for s in inconsistent
                             if same_named_import_slots(s, sym2base[s], imports)}
        inconsistent = [s for s in inconsistent if s not in import_duplicates]
    if not whitelist_path.exists():
        # NOT self-seeding. Auto-writing this file is how 18 entries got in
        # without a human ever reading them, 8 of them hiding placements this
        # very check had proved wrong (dropped in 25801f359). A missing
        # whitelist is a missing review, and a missing review is a failure.
        raise SystemExit(
            f"DIR32 consistency: {whitelist_path.relative_to(ROOT)} is missing. This check does NOT "
            f"seed itself — an auto-written whitelist is an unreviewed free pass. The {len(inconsistent)} "
            "currently inconsistent symbol(s) are listed below; READ them, confirm each is a legitimate "
            "doubly-linked TU or investigated vtable artifact, and commit the file by hand:\n"
            + "".join("    " + s + "\n" for s in inconsistent))
    whitelist = {l.strip() for l in whitelist_path.read_text().splitlines() if l.strip() and not l.startswith("#")}
    new = [s for s in inconsistent if s not in whitelist]
    if new:
        print(f"DIR32 consistency: FAIL {len(new)} NEW inconsistent symbol(s) (candidate hidden bug — same symbol, multiple addresses)")
        for s in new[:12]:
            print(f"    {s}: bases {[hex(b) for b in sorted(sym2base[s])]}")
        raise SystemExit(1)
    print(f"DIR32 consistency: OK ({len(sym2base)} symbols; {len(inconsistent)} whitelisted, "
          f"{len(import_duplicates)} PE-verified duplicate import(s), 0 new)")


UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(?:present-unmatched|absent-from-retail)\b", re.MULTILINE
)

UNCLAIMED_WHITELIST = ROOT / "reverse" / "unclaimed_sources_whitelist.txt"


def load_unclaimed_sources():
    """Repo-relative paths parked in reverse/unclaimed_sources_whitelist.txt.

    One path per line; blank lines and `#` comments are ignored. Same format as
    `tools/find_declared_unmatched.py` reads. A missing file yields the empty
    set — nothing is exempt unless a human wrote the line.
    """
    if not UNCLAIMED_WHITELIST.exists():
        return set()
    return {
        line.strip()
        for line in UNCLAIMED_WHITELIST.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }


def verify_source_claims(only=None):
    """Progress is matched rows, nothing else: every .cpp under Code/ must own at
    least one byte-verified matched row, and no marker may contradict the ledger
    (a symbol both matched and marked unmatched is a stale annotation lying about
    state).

    The single exception is `reverse/unclaimed_sources_whitelist.txt`: a
    versioned, reviewable register for a split-out body whose bytes master
    already claims under its canonical TU (the duplicate ledger row was
    retracted and the body file was deliberately left in place). It is not a
    general hatch — the file carries a written reason per source, and a body
    nothing has ever byte-verified belongs there only in that exact shape.
    Removing the old blanket exemption is why game_engine_init.cpp and five
    others were deleted.

    With `only`, checks just the sources those selectors name. The delta path runs
    it that way so a zero-row source or a stale marker fails for whoever adds it.
    Left to the full gate alone, it lands on delta verification and then blocks
    every header or shim commit tree-wide until someone else cleans it up."""
    matched_by_source = {}
    matched_sources = {}
    for row in load_function_rows():
        matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
        matched_sources.setdefault(row["name"], set()).add(row["source"])

    whitelisted = load_unclaimed_sources()
    problems = []
    sources = sorted((ROOT / "Code").rglob("*.cpp"))
    if only:
        sources = [p for p in sources
                   if any(sel in p.relative_to(ROOT).as_posix() for sel in only)]
    for path in sources:
        rel = path.relative_to(ROOT).as_posix()
        text = path.read_text(encoding="utf-8", errors="replace")
        for label in UNMATCHED_MARKER_RE.findall(text):
            # a marker on a symbol matched from ANOTHER file is correct bookkeeping
            # (e.g. the ZH copy of a function landed via an asm-whale scaffold);
            # matched from THIS file, the marker is a stale lie about its state
            if rel in matched_sources.get(label, ()):
                problems.append(
                    f"{rel}: {label} is byte-verified matched from this file but still "
                    f"carries an unmatched marker (stale annotation)"
                )
        if matched_by_source.get(rel, 0) == 0 and rel not in whitelisted:
            problems.append(
                f"{rel}: ZERO matched rows — source presence is not progress. "
                f"Byte-match at least one function, delete the file, or park it in "
                f"reverse/unclaimed_sources_whitelist.txt with a written reason "
                f"(reserved for a split-out body master already owns under another TU)."
            )

    if problems:
        print(f"Source claims: FAIL ({len(problems)} problem(s))")
        for problem in problems[:20]:
            print(f"    {problem}")
        raise SystemExit(1)
    scope = "scoped" if only else "all"
    print(f"Source claims: OK ({len(sources)} sources, {scope} byte-verified)")


def main(only=None):
    # Sources include some sweep headers under two case spellings; only the
    # canonical one is committed (case-only-colliding paths break Windows/macOS
    # checkout). Regenerate the alternate spelling here before any compile.
    ensure_case_shims()
    if only:
        # Fast path: compile and byte-compare only the matching sources/functions
        # (a few seconds), skipping the baseline hash and no-op patch. Use this to
        # iterate; run with no arguments for the full check before committing.
        #
        # Claims first: verify_functions exits with "no functions match" when the
        # selector names a source that owns no rows, which is exactly the case the
        # zero-row check exists to catch, so it has to run before that exit.
        verify_source_claims(only)
        verify_functions(only)
        # String-ref verify scoped to the same rows: function bytes alone cannot
        # tell identical-twin stubs apart (their string pointer is a masked
        # DIR32) — three wrong-twin claims survived per-file verification and
        # reached master before the full gate caught them.
        rows = [row for row in load_function_rows()
                if any(sel in row["source"] or sel in row["name"] for sel in only)]
        verify_string_refs(rows)
        verify_float_refs(rows)
        verify_import_refs(rows)
        return
    print("Full verification")
    # Identity, not bytes: verify_functions proves each row's bytes, and a
    # symbols.csv pin that names the WRONG body still reproduces them (that is
    # how the ControlBar and GameWindow misidentifications passed a green gate).
    # 3.4s on a >10min gate, reading only the retail image and the ledgers, so
    # it needs no cached artifact and no compile output -- imported here rather
    # than at module scope because pin_consistency imports this module.
    import pin_consistency
    # Same reason, for module identity: ModuleFactory's addModule registrations
    # name every factory, and a misnamed factory/ctor/proc still byte-matches.
    import check_module_registry

    # EVERY check reports, then the gate exits ONCE. Exiting at the first
    # failure makes each late check hostage to every earlier one: a live DIR32
    # red sat four statements ahead of the pin guard, so the guard built to
    # catch what a green gate cannot had itself never run on master -- and a
    # report of "only the pre-existing DIR32 red" reads identically whether the
    # later checks passed or never executed. Ordering is not a safety property;
    # running is.
    failed = []

    def run(label, check):
        """Run one check, recording rather than propagating its SystemExit.

        Only SystemExit is caught, and only a failing code: a check that dies
        any other way is a bug in the gate itself and must still crash loudly.
        """
        try:
            return check()
        except SystemExit as exc:
            if not exc.code:
                raise
            if not isinstance(exc.code, int):
                print(f"{label}: FAIL {exc.code}")
            failed.append(label)
            return None

    run("baseline", verify_baseline)
    patches = run("functions", verify_functions)
    rows = load_function_rows()
    run("string-refs", lambda: verify_string_refs(rows))
    run("float-refs", lambda: verify_float_refs(rows))
    run("import-refs", lambda: verify_import_refs(rows))
    run("dir32 consistency", lambda: verify_dir32_consistency(rows))
    run("pin consistency", pin_consistency.verify)
    run("module registry", check_module_registry.verify)
    run("source claims", verify_source_claims)
    if patches is None:
        # The no-op patch needs the compiled patch set, so a failed
        # verify_functions leaves it unrunnable. Say that out loud and stay red
        # rather than skipping it into a green summary.
        print("No-op patch: FAIL not run — verify_functions did not produce a patch set")
        failed.append("no-op patch (unrunnable)")
    else:
        run("no-op patch", lambda: verify_noop_patch(patches))

    if failed:
        print(f"\nFULL GATE: FAIL — {len(failed)} red: " + ", ".join(failed))
        raise SystemExit(1)
    print("\nFULL GATE: OK — every check green")


if __name__ == "__main__":
    main(sys.argv[1:])
