#!/usr/bin/env python3
"""The data ledger: reverse/data_rows.csv, globals a Code/ source owns.

functions.csv owns code. A translation unit that defines only data (ZH's
Common/Language.cpp is one line: `LanguageID OurLanguage = LANGUAGE_ID_US;`)
had no way to own anything, so its honest owner could not exist in Code/.
A data row claims one retail address range for one compiled symbol:

  name          the COFF symbol the source's object defines (mangled)
  address       hex, with address_kind `va` or `rva` -- never implied
  size          bytes, PROVEN from the object (below) or refused
  section       the retail section holding the range (.data, .rdata, ...)
  source        the Code/ .c/.cpp that defines it
  status        matched
  evidence      why this source is the owner (a verdict, a reference)
  model         who landed it

Integrity (check_csv, no compiler): the header, an explicit address kind, a
size, the section containing the whole range, one owner per address, no two
ranges overlapping, one row per name, a tracked source.

Verification (build.py, per source and in the full gate), per row:
  size      sizeof(the symbol) as the compiler evaluates it in a probe TU
            that #includes the source under its own build command (so
            namespaces, typedefs, packing and array bounds resolve exactly as
            in the build), agreeing with the mangled scalar type when there is
            one, and no larger than the symbol's allocation extent (to the next
            symbol or the section end, padding included), which alone proves
            nothing; a COMMON symbol's own size. Two compiler-emitted names
            no probe can spell are sized by their own COMDAT section, only in
            the one shape MSVC 7.1 gives them: a function-local static, and a
            vftable (`??_7<class>@@6B...@`, alone in a read-only COMDAT data
            section, every 4-byte slot a relocated pointer; BFME 2 is built
            without RTTI, so no locator precedes it); otherwise refused.
  bytes     initialised: equal to retail over the extent outside relocation
            fields, and every relocation's target (symbol + in-place addend)
            equal to retail's pointer there, the target's address coming from
            the ledgers (functions.csv object symbols, data_rows, dir32 names,
            symbols.csv pins; a function's ILT stub counts for its body). A
            function target takes only a code address. A data target takes a
            non-executable address or its own explicit matched data-row home,
            including data stored in retail .text; that home is not a function.
            Pins and untyped DIR32 names grant no such exemption. A compiler string literal (??_C@...) has no ledger name:
            it is placed by content, as build.verify_string_refs places one
            for code -- retail's pointer must land outside code on the
            literal's own bytes from the addend through its terminator. A pin is read for the target's kind (pin_readings): for
            a function, only as an RVA that lands in code (pin_admission's
            form); for data, as whichever reading lands in data, and a pin
            with two such readings places nothing. DIR32 holds the target's
            VA, DIR32NB its RVA.
            A TU-local data object (a file-scope `static`, which MSVC 7.1
            names `_name` with static storage, or a function-local one's
            `?name` mangling)
            has no ledger name either: header statics such as Zero Hour's
            DEFINE_*_NAMES lists give every including TU its own copy, at its
            own retail address. It is placed by content too, against this
            row's own object: retail's pointer (less the addend) must land in
            data on the static's compiler-proven extent, overlapping no data
            row (a ledger-owned global is never a TU-local copy), holding the
            static's bytes outside relocation fields, with each of its own
            relocations placed by these same rules. Any other relocation to a
            TU-local symbol (a static function, a `$`/`.` or `??_` compiler
            name, a zero-filled static) cannot be placed and fails.
            A weak external (a vftable slot's `??_E` deleting destructor) is
            placed by its own name when the ledgers give it a home, else by its
            default (the IMAGE_WEAK_EXTERN TagIndex, MSVC's `??_G`), which is
            what link.exe binds when no object defines the weak name.
            uninitialised (.bss / COMMON): retail holds zeros over the extent.
            Each symbol is checked alone at its own address: MSVC 7.1 lays a
            TU's zero-filled globals out by name, so no TU-internal order is
            assumed.

  python3 tools/data_rows.py --admit-agreed ID --symbol COFF --model MODEL
  python3 tools/data_rows.py --check            # integrity only
  python3 tools/data_rows.py --verify [SOURCE]  # compile + verify (all rows, or one source's)

Ported from Open-BFME-1's tools/data_rows.py; its paths are set once below
(REVERSE, SOURCE_ROOT). Fixed here since the port (review of cd1336610f): pin
readings (pin_readings, Resolver), the DIR32NB stub comparison in verify_row,
and check() no longer reads retail's image for a ledger with no rows. This
repository has no dir32_addresses.csv, so no dir32 name places a relocation
target until one exists.
"""
import argparse
import csv
import io
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# BFME 2's layout: Open-BFME-1 has targets/game/reverse/ and game/ here.
REVERSE = ROOT / "reverse"
SOURCE_ROOT = "Code/"
DATA_ROWS = REVERSE / "data_rows.csv"
SYMBOLS = REVERSE / "symbols.csv"
DIR32_ADDRESSES = REVERSE / "dir32_addresses.csv"  # Open-BFME-1: build.DIR32_ADDRESSES
HEADER = "name,address,address_kind,size,section,source,status,evidence,model"
FIELDS = HEADER.split(",")
IMAGE_BASE = 0x400000
DIR32, DIR32NB = 0x0006, 0x0007
EXTERNAL, STATIC = 2, 3
WEAK_EXTERNAL = 105  # IMAGE_SYM_CLASS_WEAK_EXTERNAL: a vftable slot's ??_E, defaulting to ??_G
UNINIT = 0x80
EXECUTABLE = 0x20000000 | 0x00000020  # IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE
DTYPE_FUNCTION = 2  # COFF symbol type: (type >> 4) & 3 == 2 is a function (MSVC writes 0x20)
SOURCE_SUFFIXES = (".c", ".cpp")


def parse(raw):
    """[(line, dict)] of the ledger's records; raises ValueError on a bad header."""
    text = raw.decode("utf-8", errors="replace")
    records = list(csv.reader(io.StringIO(text)))
    if not records or ",".join(records[0]) != HEADER:
        raise ValueError(f"data_rows.csv: bad header (expected '{HEADER}')")
    out = []
    for line, record in enumerate(records[1:], start=2):
        if not record or record == [""]:
            continue
        out.append((line, dict(zip(FIELDS, record)) if len(record) == len(FIELDS) else {"_fields": len(record)}))
    return out


def va_of(row):
    """The row's VA: its address read the way address_kind says."""
    address = int(row["address"], 16)
    return address if row["address_kind"] == "va" else IMAGE_BASE + address


def retail_sections(exe=None):
    """[(name, va, end, characteristics)] from retail's PE header (no image load)."""
    if exe is None:
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        exe = build.EXE
    with open(exe, "rb") as handle:
        head = handle.read(4096)
    pe = struct.unpack_from("<I", head, 0x3C)[0]
    count, optional = struct.unpack_from("<H", head, pe + 6)[0], struct.unpack_from("<H", head, pe + 20)[0]
    base = struct.unpack_from("<I", head, pe + 52)[0]
    out = []
    for k in range(count):
        o = pe + 24 + optional + 40 * k
        name = head[o:o + 8].rstrip(b"\0").decode("latin-1").strip()
        vsize, rva, rsize = struct.unpack_from("<III", head, o + 8)
        characteristics = struct.unpack_from("<I", head, o + 36)[0]
        out.append((name, base + rva, base + rva + max(vsize, rsize), characteristics))
    return out


def section_kind(sections, va):
    """'code' where `va` lies in an executable section of `sections` (retail_sections'
    4-tuples), 'data' in any other section, None outside them all."""
    for _, start, end, characteristics in sections:
        if start <= va < end:
            return "code" if characteristics & EXECUTABLE else "data"
    return None


def pin_readings(value, sections, function=None):
    """({VA}, None) a symbols.csv pin address stands for as a function (True),
    as data (False) or as either (None), or (set(), why) when it is ambiguous.

    A function's address is code, and a function pin is an RVA: pin_admission
    admits a pin only as an in-image RVA in code. So a function resolves by the
    RVA reading alone, when it lands in code: 0x00401010 is RVA 0x00401010,
    never VA 0x00401010 (7,192 pins had both readings in retail .text on
    2026-10-09). A VA reading that lands in code proves nothing: the data pin
    _bfmeVftSF at 0x00816778 has one (RVA 0x00416778). A function pin written
    as a VA is rewritten to its RVA on evidence (tools/legacy_va_pins.py), not
    guessed here.
    Data pins were written as RVAs or as VAs (link_cycle.pin_matches), so
    whichever reading lands in data counts; when both do, the pin is ambiguous
    and places nothing (fail closed)."""
    readings = (("RVA", IMAGE_BASE + value), ("VA", value))
    kinds = [(how, va, section_kind(sections, va)) for how, va in readings]
    if function is None:
        code, _ = pin_readings(value, sections, True)
        data, why = pin_readings(value, sections, False)
        return code | data, why
    if function:
        return ({IMAGE_BASE + value} if kinds[0][2] == "code" else set()), None
    data = [(how, va) for how, va, kind in kinds if kind == "data"]
    if len(data) > 1:
        return set(), (f"pin 0x{value:08X} is ambiguous: as an RVA and as a VA it is data, "
                       f"at 0x{data[0][1]:08X} and at 0x{data[1][1]:08X}")
    return {va for _, va in data}, None


def check(raw, problems, sources_ok=None, sections=None):
    """Integrity problems appended to `problems`; returns the row count."""
    try:
        records = parse(raw)
    except ValueError as exc:
        problems.append(str(exc))
        return 0
    if raw and not raw.endswith(b"\n"):
        problems.append("data_rows.csv: the last row has no line ending")
    if not records:
        return 0  # header and framing only: nothing to place, so retail's image is not read
    sections = retail_sections() if sections is None else sections
    spans, names, starts = [], {}, {}
    for line, row in records:
        where = f"data_rows.csv line {line}"
        if "_fields" in row:
            problems.append(f"{where}: {row['_fields']} fields, expected {len(FIELDS)}")
            continue
        name = row["name"]
        if not name:
            problems.append(f"{where}: empty name")
            continue
        where += f" ({name})"
        if row["address_kind"] not in ("va", "rva"):
            problems.append(f"{where}: address_kind must be `va` or `rva`, not '{row['address_kind']}'")
            continue
        if not re.fullmatch(r"0x[0-9A-Fa-f]{1,8}", row["address"]):
            problems.append(f"{where}: bad address '{row['address']}' (0x + at most 8 hex digits)")
            continue
        if not row["size"].isdigit() or int(row["size"]) <= 0:
            problems.append(f"{where}: size must be a positive integer, not '{row['size']}'")
            continue
        if row["status"] != "matched":
            problems.append(f"{where}: status must be `matched`, not '{row['status']}'")
        if not row["source"].startswith(SOURCE_ROOT) or not row["source"].endswith(SOURCE_SUFFIXES):
            problems.append(f"{where}: source must be a {SOURCE_ROOT} .c/.cpp file, not '{row['source']}'")
        elif sources_ok is not None and row["source"] not in sources_ok:
            problems.append(f"{where}: source {row['source']} is not tracked")
        if not row["evidence"].strip():
            problems.append(f"{where}: empty evidence")
        if not row["model"].strip():
            problems.append(f"{where}: empty model (who landed it)")
        va, size = va_of(row), int(row["size"])
        home = [s for s in sections if s[1] <= va and va + size <= s[2]]
        if not home:
            problems.append(f"{where}: 0x{va:08X}+{size} lies in no single retail section")
        elif home[0][0] != row["section"]:
            problems.append(f"{where}: 0x{va:08X} is in {home[0][0]}, the row says '{row['section']}'")
        if name in names:
            problems.append(f"{where}: {name} already owned at line {names[name]}; one row per name")
        names.setdefault(name, line)
        if va in starts:
            problems.append(f"{where}: 0x{va:08X} already owned by line {starts[va]}; one owner per address")
        starts.setdefault(va, line)
        spans.append((va, va + size, line, name))
    spans.sort()
    for (a0, a1, l0, n0), (b0, b1, l1, n1) in zip(spans, spans[1:]):
        if b0 < a1 and a0 != b0:
            problems.append(f"data_rows.csv lines {l0} and {l1}: {n0} 0x{a0:08X}+{a1 - a0} overlaps "
                            f"{n1} 0x{b0:08X}+{b1 - b0}")
    return len(records)


def load(path=None):
    """The ledger's rows; `path` defaults to DATA_ROWS as it is NOW (read at call
    time, so a test or tool that points DATA_ROWS elsewhere is honoured)."""
    path = DATA_ROWS if path is None else path
    if not Path(path).exists():
        return []
    return [row for _, row in parse(Path(path).read_bytes()) if "_fields" not in row]


# --------------------------------------------------------------------------- verification

def _tools():
    sys.path.insert(0, str(ROOT / "tools"))
    import build
    import reloc_ledger
    return build, reloc_ledger


def cpp_name(symbol):
    """The expression naming a data symbol in its own TU: `x` for a C `_x`,
    `::A::B::x` for global, public, or protected data. Protected static data
    is probed from a derived access scope; private members remain refused."""
    return _cpp_data_access(symbol)[0]


def _data_scopes(text, pos):
    """Decode identifier scopes and templates with literal integral/type arguments.
    Backreferences and local or anonymous scopes remain unsupported."""
    primitive = {"D": "char", "E": "unsigned char", "F": "short", "G": "unsigned short",
                 "H": "int", "I": "unsigned int", "J": "long", "K": "unsigned long",
                 "M": "float", "N": "double", "_N": "bool", "_W": "wchar_t"}
    scopes = []
    while text[pos] != "@":
        if text.startswith("?$", pos):
            match = re.match(r"\?\$(\w+)@", text[pos:])
            if not match:
                raise ValueError("unsupported template name")
            pos += len(match.group(0))
            args = []
            while text[pos] != "@":
                if text.startswith("$0", pos):
                    pos += 2
                    negative = text[pos] == "?"
                    pos += int(negative)
                    if text[pos].isdigit():
                        value = int(text[pos]) + 1
                        pos += 1
                    else:
                        end = text.index("@", pos)
                        digits = text[pos:end]
                        if not digits or not re.fullmatch(r"[A-P]+", digits):
                            raise ValueError("unsupported integral argument")
                        value = int("".join(f"{ord(c) - ord('A'):x}" for c in digits), 16)
                        pos = end + 1
                    args.append(str(-value if negative else value))
                elif text[pos] in "UV":
                    nested, pos = _data_scopes(text, pos + 1)
                    args.append("::" + "::".join(reversed(nested)))
                else:
                    code = text[pos:pos + 2] if text[pos] == "_" else text[pos]
                    if code not in primitive:
                        raise ValueError("unsupported type argument")
                    args.append(primitive[code])
                    pos += len(code)
            scopes.append(match.group(1) + "<" + ", ".join(args) + " >")
            pos += 1
        else:
            match = re.match(r"[A-Za-z_]\w*@", text[pos:])
            if not match:
                raise ValueError("unsupported scope")
            scopes.append(match.group(0)[:-1])
            pos += len(match.group(0))
    return scopes, pos + 1


def _cpp_data_access(symbol, *, allow_private=False):
    """(expression, declaring class, protected) for supported data names.

    MSVC access digits 1/2/3 are protected/public/global. A private member is
    available only to compiler probes, through the source's explicit friendship
    with DataRowPrivateProbe. No derived scope can widen private access."""
    if not symbol.startswith("?"):
        expression = symbol[1:] if symbol.startswith("_") else None
        return expression, None, False
    m = re.match(r"^\?(\w+)@", symbol)
    if not m:
        return None, None, False
    try:
        scopes, pos = _data_scopes(symbol, len(m.group(0)))
    except (ValueError, IndexError):
        return None, None, False
    access = symbol[pos:pos + 1]
    if access not in (("0", "1", "2", "3") if allow_private else ("1", "2", "3")):
        return None, None, False
    protected = "private" if access == "0" else access == "1"
    if protected and not scopes:
        return None, None, False
    expression = "::" + "::".join(list(reversed(scopes)) + [m.group(1)])
    owner = "::" + "::".join(reversed(scopes)) if scopes else None
    return expression, owner, protected


def _access_probe(source, symbol, tag, owner, access, value, member):
    """A compiler access scope; private access requires an explicit source friend.

    The probe defines its own template, so a source-defined impostor causes a
    redefinition error. The existing macro guards cover the helper name too.
    Source declarations, access specifiers, and build flags are never rewritten.
    """
    if access == "private":
        helper = "DataRowPrivateProbe"
        scope = (f"template<class T> struct {helper} {{ enum {{ {member} = {value} }}; }};\n")
        # The owner can itself be a template specialization. VC7.1 reads >> as a shift.
        return helper, scope, f"{helper}< {owner} >::{member}"
    if access:
        helper = _protected_probe_name(source, symbol, tag)
        scope = f"class {helper} : public {owner} {{ public: enum {{ {member} = {value} }}; }};\n"
        return helper, scope, f"{helper}::{member}"
    return None, "", value


def _protected_probe_name(source, symbol, tag):
    import zlib
    key = f"{Path(source)}:{symbol}:{tag}".encode()
    return f"data_row_protected_access_{zlib.crc32(key):08x}"


def _probe_include(source, probe):
    """The #include spelling of `source` for a probe TU at `probe`: relative to
    the probe's directory. MSVC 7.1 reads #include paths in the ANSI code page,
    so an absolute path through a non-ASCII checkout directory names no file;
    the in-repository part of the path stays ASCII."""
    import os
    return Path(os.path.relpath(source.resolve(), probe.parent.resolve())).as_posix()


def compiled_size(source, symbol):
    """(bytes, how) = sizeof(the symbol) as MSVC 7.1 evaluates it in a probe TU
    that #includes `source` and is compiled with `source`'s own build command;
    (None, why) when it cannot be named or the probe does not compile."""
    import subprocess
    build, rl = _tools()
    expression, owner, protected = _cpp_data_access(symbol, allow_private=True)
    if expression is None:
        return None, f"{symbol} cannot be named from its TU"
    import zlib
    source = Path(source) if Path(source).is_absolute() else ROOT / source
    try:
        source.resolve().relative_to(ROOT.resolve())
    except ValueError:
        return None, f"{source} is outside the repository: no build command"
    probe_dir = ROOT / "build" / "data_rows" / "probe"
    probe_dir.mkdir(parents=True, exist_ok=True)
    stem = f"{source.stem}_{zlib.crc32((str(source) + symbol).encode()):08x}"
    probe = probe_dir / (stem + source.suffix)
    obj = probe.with_suffix(".obj")
    linkage = 'extern "C" ' if source.suffix.lower() != ".c" else ""
    helper, access_scope, size_expression = _access_probe(
        source, symbol, "size", owner, protected, f"sizeof({expression})", "size_value")
    # a macro named like the symbol, a scope of it or the probe's own variable
    # would make sizeof measure something else: refuse (#error) instead
    tokens = set(re.findall(r"[A-Za-z_]\w*", expression)) | {"data_row_sizeof"}
    if helper:
        tokens.add(helper)
    guards = "".join(f"#ifdef {token}\n#error data_row_probe: {token} is a macro here\n#endif\n"
                     for token in sorted(tokens))
    probe.write_text(f'#include "{_probe_include(source, probe)}"\n' + guards + access_scope
                     + f"{linkage}const unsigned int data_row_sizeof = {size_expression};\n", encoding="utf-8")
    command, env = build.compiler_command(source, obj)
    command[-1] = probe.relative_to(ROOT).as_posix()
    if obj.exists():
        obj.unlink()
    code, text = build.run_confined(command, env, obj)      # include confinement, as for a build compile
    if code or not obj.exists():
        return None, f"the sizeof probe does not compile: {text.strip()[-300:]}"
    sections, symbols = rl.parse_coff(obj.read_bytes())
    found = [x for x in symbols.values() if x["name"] == "_data_row_sizeof" and x["section"] > 0]
    body = sections[found[0]["section"] - 1]["body"] if found else None
    if not found or body is None:
        return None, "the sizeof probe emitted no value"
    how = f"sizeof({expression}) under the build's flags"
    if helper:
        how += f" via {'friend' if protected == 'private' else 'derived'} access scope {helper}"
    return struct.unpack_from("<I", body, found[0]["value"])[0], how


ARRAY_PROBE = """template<class T, int N> char (&drp_n(T (&)[N]))[2];
char (&drp_n(...))[1];
"""
ARITHMETIC_PROBE = "".join(f"char (&drp_k(const volatile {t} *))[2];\n" for t in (
    "char", "signed char", "unsigned char", "short", "unsigned short", "int", "unsigned int", "long",
    "unsigned long", "__int64", "unsigned __int64", "float", "double", "long double", "bool")) \
    + "char (&drp_k(...))[1];\n"


def _type_probe(source, symbol, tag, preamble, value):
    """Compile a probe TU (#include `source`, its own build command) holding
    `preamble` and `extern "C" const unsigned data_row_kind = <value>`; the value, or (None, why)."""
    import subprocess
    import zlib
    build, rl = _tools()
    expression, owner, protected = _cpp_data_access(symbol, allow_private=True)
    if expression is None:
        return None, f"{symbol} cannot be named from its TU"
    probe_dir = ROOT / "build" / "data_rows" / "probe"
    probe_dir.mkdir(parents=True, exist_ok=True)
    probe = probe_dir / f"{source.stem}_{zlib.crc32((str(source) + symbol).encode()):08x}_{tag}{source.suffix}"
    obj = probe.with_suffix(".obj")
    helper, access_scope, kind_expression = _access_probe(
        source, symbol, tag, owner, protected, value, "kind_value")
    tokens = set(re.findall(r"[A-Za-z_]\w*", expression)) | {"data_row_kind", "drp_n", "drp_k"}
    if helper:
        tokens.add(helper)
    guards = "".join(f"#ifdef {token}\n#error data_row_probe: {token} is a macro here\n#endif\n"
                     for token in sorted(tokens))
    probe.write_text(f'#include "{_probe_include(source, probe)}"\n' + guards + preamble + access_scope
                     + f'extern "C" const unsigned int data_row_kind = {kind_expression};\n', encoding="utf-8")
    command, env = build.compiler_command(source, obj)
    command[-1] = probe.relative_to(ROOT).as_posix()
    if obj.exists():
        obj.unlink()
    code, text = build.run_confined(command, env, obj)      # include confinement, as for a build compile
    if code or not obj.exists():
        return None, f"the type probe does not compile: {text.strip()[-300:]}"
    sections, symbols = rl.parse_coff(obj.read_bytes())
    found = [x for x in symbols.values() if x["name"] == "_data_row_kind" and x["section"] > 0]
    body = sections[found[0]["section"] - 1]["body"] if found else None
    if not found or body is None:
        return None, "the type probe emitted no value"
    how = f"via {'friend' if protected == 'private' else 'derived'} access scope {helper}" if helper else ""
    return struct.unpack_from("<I", body, found[0]["value"])[0], how


def compiled_arithmetic(source, symbol):
    """(True/False/None, how): whether the compiler, in probe TUs that #include
    `source` under its own build command, types the symbol as a built-in
    arithmetic scalar (integer, character, bool, floating) or a one-dimensional
    array of one. A pointer (`int *p`), an enum, a class, a multi-dimensional
    array and anything a probe cannot name or compile are not proven numbers."""
    expression, _, _ = _cpp_data_access(symbol, allow_private=True)
    if expression is None:
        return None, f"{symbol} cannot be named from its TU"
    source = Path(source) if Path(source).is_absolute() else ROOT / source
    if source.suffix.lower() == ".c":
        return None, "a C source: the type probe needs C++ overloading"
    try:
        source.resolve().relative_to(ROOT.resolve())
    except ValueError:
        return None, f"{source} is outside the repository: no build command"
    is_array, why = _type_probe(source, symbol, "array", ARRAY_PROBE, f"sizeof(drp_n({expression})) - 1")
    if is_array is None:
        return None, why
    form = expression if is_array else f"&{expression}"  # an array decays to its element pointer
    kind, why = _type_probe(source, symbol, "kind", ARITHMETIC_PROBE, f"sizeof(drp_k({form})) - 1")
    if kind is None:
        return None, why
    arithmetic = kind == 1
    shape = "array element" if is_array else "scalar"
    return arithmetic, (f"the compiler types {expression} as {'an arithmetic' if arithmetic else 'a non-arithmetic'}"
                        f" {shape}")


# ?name@?<block>??<function>@4<type>: the block number is one digit (1-10)
# or hex letters ended by `@` (`?is_init@?1??Get@...`, `?d@?BC@??f@@...`)
LOCAL_STATIC = re.compile(r"^\?\w+@\?(?:\d|\w+@)\?\?")
IMAGE_SCN_LNK_COMDAT = 0x1000


def _local_static_size(sec, symbols, sym):
    """(bytes, how) for a function-local static, which no probe TU can name:
    MSVC 7.1 gives one its own COMDAT section and emits exactly sizeof(it)
    there (a 3-byte struct, 1-, 6- and 9-byte arrays and a double get
    sections of 3, 1, 6, 9 and 8 bytes; alignment lives in the section
    flags, not in padding). Only that shape is accepted: the static at offset
    0 of a COMDAT section that defines no other named symbol. Else None."""
    if not LOCAL_STATIC.match(sym["name"]) or not sec["flags"] & IMAGE_SCN_LNK_COMDAT or sym["value"]:
        return None
    others = [s for s in symbols.values() if s["section"] == sym["section"] and s is not sym
              and s["name"] and not s["name"].startswith(".")]
    if others:
        return None
    return sec["size"], "the function-local static's own COMDAT section size"


# ??_7<class>@@6B@ (or 6B<base path>@ for a secondary table): a compiler-emitted vftable
VFTABLE = re.compile(r"^\?\?_7.+@6B.*@$")
IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_WRITE = 0x40, 0x80000000


PUBLIC_TEMPLATE_POINTER_REFERENCE = re.compile(r"^\?\w+@\?\$\w+@.+@@2ABQBDB$")


def _template_pointer_reference_size(sections, symbols, sym, x86):
    """Size a public template static of type const char *const &.

    VC7.1 gives these dynamically initialized x86 references a four-byte slot.
    Prove it from the isolated COMDAT or the compiler's exact startup store.
    """
    sec = sections[sym["section"] - 1]
    flags = sec["flags"]
    needed = IMAGE_SCN_MEM_WRITE | UNINIT
    if (not PUBLIC_TEMPLATE_POINTER_REFERENCE.fullmatch(sym["name"])
            or sym["storage"] != EXTERNAL or sym["type"] != 0 or sec["name"] != ".bss"
            or flags & needed != needed or flags & (EXECUTABLE | IMAGE_SCN_CNT_INITIALIZED_DATA)
            or sec["body"] is not None or sec["relocs"]):
        return None
    neighbors = [s for s in symbols.values() if s is not sym and s["section"] == sym["section"]
                 and s["name"] and not s["name"].startswith(".")]
    if flags & IMAGE_SCN_LNK_COMDAT:
        if not neighbors and not sym["value"] and sec["size"] == 4:
            return 4, "the x86 template pointer reference's own COMDAT section"
    elif (x86 and sym["value"] % 4 == 0
          and not any(sym["value"] <= s["value"] < sym["value"] + 4 for s in neighbors)
          and _has_pointer_reference_initializer(sections, symbols, sym["index"])):
        return 4, "the x86 template pointer reference's compiler startup store"
    return None


def _has_pointer_reference_initializer(sections, symbols, index):
    """Find exactly one .CRT$XCU entry for a direct dword store to this symbol."""
    stores = 0
    for crt in sections:
        if crt["name"] != ".CRT$XCU" or crt["body"] is None:
            continue
        for offset, target, kind in crt["relocs"]:
            thunk = symbols.get(target)
            if (kind != DIR32 or offset % 4 or crt["body"][offset:offset + 4] != bytes(4)
                    or thunk is None or not 0 < thunk["section"] <= len(sections)
                    or thunk["value"] or thunk["type"] != 0x20 or thunk["storage"] != STATIC
                    or not re.fullmatch(r"_\$E\d+", thunk["name"])):
                continue
            code = sections[thunk["section"] - 1]
            relocs = code["relocs"]
            # mov dword ptr [reference], offset referent; ret
            if (code["name"] != ".text$yc" or not code["flags"] & EXECUTABLE
                    or code["body"] != b"\xc7\x05" + bytes(8) + b"\xc3"
                    or len(relocs) != 2 or relocs[0] != (2, index, DIR32)
                    or relocs[1][0::2] != (6, DIR32)):
                continue
            referent = symbols.get(relocs[1][1])
            if (referent is not None and referent["storage"] == EXTERNAL and referent["type"] == 0
                    and re.fullmatch(r"\?[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@3QBDB", referent["name"])):
                stores += 1
    return stores == 1


def _vftable_size(sec, symbols, sym):
    """(bytes, how) for a vftable, which no probe TU can name: BFME 2 is built
    without RTTI (no ??_R4 locator precedes any table), and MSVC 7.1 then emits
    each vftable at offset 0 of its own read-only COMDAT data section, one
    relocated 4-byte pointer per slot (`__purecall` for a pure slot) and nothing
    else. Only that shape is accepted: an external ??_7 name at offset 0 of an
    initialised, non-writable, non-executable COMDAT section that defines no
    other named symbol, whose every 4-byte word, and nothing else, carries a
    relocation. Else None."""
    flags = sec["flags"]
    if (not VFTABLE.match(sym["name"]) or sym["storage"] != EXTERNAL or sym["value"]
            or not flags & IMAGE_SCN_LNK_COMDAT or not flags & IMAGE_SCN_CNT_INITIALIZED_DATA
            or flags & (EXECUTABLE | IMAGE_SCN_MEM_WRITE | UNINIT)
            or sec["body"] is None or not sec["size"] or sec["size"] % 4):
        return None
    others = [s for s in symbols.values() if s["section"] == sym["section"] and s is not sym
              and s["name"] and not s["name"].startswith(".")]
    if others:
        return None
    if sorted(w for w, _, _ in sec["relocs"]) != list(range(0, sec["size"], 4)):
        return None
    return sec["size"], "the vftable's own COMDAT section size"


def weak_default(data, index, symbols):
    """The default symbol of weak external `index` in COFF `data` (the
    IMAGE_WEAK_EXTERN aux record's TagIndex), or None when it has no aux record."""
    table, count = struct.unpack_from("<II", data, 8)
    if not 0 <= index < count - 1 or data[table + 18 * index + 17] < 1:
        return None
    return symbols.get(struct.unpack_from("<I", data, table + 18 * (index + 1))[0])


def symbol_size(sections, symbols, sym, source=None, sizer=compiled_size, *, x86=False):
    """(proven sizes, what proves them) for a defined or COMMON data symbol.

    The allocation extent (to the next symbol or the section end) includes
    alignment padding, so it only BOUNDS the size. The size is what the compiler
    itself says: sizeof(symbol) in a probe TU compiled with the source's own
    command (`sizer`), which resolves namespaces, typedefs, packing and array
    bounds as the real build does; it must fit the extent and agree with the
    mangled scalar type when there is one. A COMMON symbol carries its own size.
    Anything else is refused."""
    _, rl = _tools()
    if sym["section"] == 0:  # COMMON: the value is the size
        return {sym["value"]}, "COMMON symbol size"
    sec = sections[sym["section"] - 1]
    later = sorted({s["value"] for s in symbols.values() if s["section"] == sym["section"]
                    and s["storage"] in (EXTERNAL, STATIC) and s["name"] and not s["name"].startswith(".")
                    and s["value"] > sym["value"]})
    extent = (later[0] if later else sec["size"]) - sym["value"]
    if source is None:
        return set(), f"no source to evaluate sizeof in (allocation extent {extent} is not a size)"
    size, how = sizer(source, sym["name"])
    if size is None:
        size, how = (_local_static_size(sec, symbols, sym) or _vftable_size(sec, symbols, sym)
                     or _template_pointer_reference_size(sections, symbols, sym, x86)
                     or (None, how))
    if size is None:
        return set(), how
    scalar = rl.mangled_scalar_size(sym["name"])
    if scalar is not None and scalar != size:
        return set(), f"{how} gives {size} but the mangled type declares {scalar}"
    if size > extent:
        return set(), f"{how} gives {size}, larger than the allocation extent {extent}"
    return {size}, f"{how} = {size} (allocation extent {extent})"


class Resolver:
    """Retail VAs a relocation target name may take, from the ledgers only."""

    def __init__(self, data_rows, sections=None):
        build, rl = _tools()
        self.sections = retail_sections() if sections is None else sections
        self.homes = {}      # name -> VAs from the ledger rows
        self.data_homes = {}  # explicit data ownership, independent of section permissions
        self.pins = {}       # name -> raw symbols.csv addresses, read per target kind
        self.ambiguous = {}  # name -> [why]: pins that place no data address
        for row in build.load_function_rows():
            if row["target_rva"].startswith("0x"):
                va = IMAGE_BASE + int(row["target_rva"], 16)
                for key in {row["name"], build.ledger_object_symbol(row)}:
                    self.homes.setdefault(key, set()).add(va)
        self.spans = []      # (start, end, name): every data row's range, which no TU-local copy may claim
        for row in data_rows:
            va, size = va_of(row), int(row["size"])
            self.homes.setdefault(row["name"], set()).add(va)
            self.spans.append((va, va + max(size, 1), row["name"]))
            if (row["status"] == "matched" and size > 0
                    and any(section == row["section"] and start <= va and va + size <= end
                            for section, start, end, _ in self.sections)):
                self.data_homes.setdefault(row["name"], set()).add(va)
        # absent here: a name it would place has fewer homes, so its relocation fails
        for row in rl.read_csv_rows(DIR32_ADDRESSES) if DIR32_ADDRESSES.exists() else ():
            self.homes.setdefault(row["name"], set()).add(int(row["va"], 16))
        with SYMBOLS.open(newline="", encoding="utf-8") as handle:
            for row in csv.reader(handle):
                if len(row) >= 2 and row[1].startswith("0x"):
                    value = int(row[1], 16)
                    self.pins.setdefault(row[0], []).append(value)
                    why = pin_readings(value, self.sections, False)[1]
                    if why:
                        self.ambiguous.setdefault(row[0], []).append(why)

    def __call__(self, name, function=None):
        """`name`'s homes, with explicit data rows overriding section permissions.

        Other homes and pins still require the requested section kind.
        """
        homes = set(self.homes.get(name, ()))
        if function is not None:
            want = "code" if function else "data"
            homes = {va for va in homes if section_kind(self.sections, va) == want}
        for value in self.pins.get(name, ()):
            homes |= pin_readings(value, self.sections, function)[0]
        if function is False:
            homes |= self.data_homes.get(name, set())
        elif function is True:
            homes -= self.data_homes.get(name, set())
        return homes


def string_literal_problem(build, sections, target, addend, actual, img):
    """None when retail's pointer `actual` lands on the compiled string literal
    `target` (+addend), else why not. The ledgers name no string literal, so its
    address is proven by content: the object's own literal bytes, whose length
    the mangled name encodes, must be retail's bytes there through the
    terminator (a prefix or a longer string is refused), outside code."""
    name = target["name"]
    sec = sections[target["section"] - 1] if 0 < target["section"] <= len(sections) else None
    if sec is None or sec["body"] is None:
        return f"string literal {name} is not defined with bytes in this object"
    try:
        literal = build.string_literal_bytes(name, sec["body"][target["value"]:])
    except ValueError as exc:
        return f"string literal {name}: {exc}"
    if not 0 <= addend < len(literal):
        return f"string literal {name}: addend {addend:#x} is outside its {len(literal)} bytes"
    where = img.section(actual)
    if where in (None, "header") or section_kind(
            [(s["name"], s["va"], s["end"], c) for s, c in zip(img.sections, _characteristics(img))],
            actual) != "data":
        return f"retail points at 0x{actual:08X}, which is not data, for string literal {name}"
    content = literal[addend:]
    retail = img.read(actual, len(content))
    if retail != content:
        return (f"retail holds {retail!r} at 0x{actual:08X}, string literal {name}"
                f"+{addend:#x} is {content!r}")
    return None


def _characteristics(img):
    """Each of `img`'s sections' characteristics, read from its own PE header."""
    data = img.data
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    optional = struct.unpack_from("<H", data, pe + 20)[0]
    return [struct.unpack_from("<I", data, pe + 24 + optional + 40 * k + 36)[0]
            for k in range(len(img.sections))]


def verify_row(row, img, resolve, compile=True, sizer=compiled_size):
    """(ok, message) for one data row against its source's current object."""
    build, rl = _tools()
    source = ROOT / row["source"]
    if not source.is_file():
        return False, f"source {row['source']} is missing"
    obj = build.obj_path(source)
    if compile and not build.compile_is_current(source, obj):
        ok, text, _ = build.try_compile_source(source, obj)
        if not ok:
            return False, f"{row['source']} does not compile: {(text or '').strip()[-300:]}"
    if not obj.exists():
        return False, f"object {obj.name} missing"
    data = obj.read_bytes()
    sections, symbols = rl.parse_coff(data)
    found = [s for s in symbols.values() if s["name"] == row["name"] and s["storage"] == EXTERNAL
             and (s["section"] > 0 or s["value"] > 0)]
    if len(found) != 1:
        return False, f"{row['name']} is not defined once in {obj.name}"
    sym = found[0]
    size = int(row["size"])
    sizes, why = symbol_size(sections, symbols, sym, source, sizer, x86=data[:2] == b"\x4c\x01")
    if size not in sizes:
        return False, f"size {size} unproven: {why} gives {sorted(sizes)}"
    va = va_of(row)
    if img.section(va) != row["section"] or img.section(va + size - 1) != row["section"]:
        return False, f"0x{va:08X}+{size} is not inside retail {row['section']}"
    retail = img.read(va, size)
    sec = sections[sym["section"] - 1] if sym["section"] > 0 else None
    if sec is None or sec["body"] is None:
        # zero-filled: this symbol alone, at its own address (no TU order assumed)
        if any(retail):
            return False, f"uninitialised {row['name']} but retail holds non-zero bytes at 0x{va:08X}"
        return True, f"zero-filled {size} B at 0x{va:08X} ({why})"
    lo = sym["value"]
    body = sec["body"][lo:lo + size]
    relocs = [(w, i, k) for w, i, k in sec["relocs"] if lo - 3 <= w < lo + size]
    if any(w < lo or w + 4 > lo + size for w, _, _ in relocs):
        return False, "a relocation field straddles the symbol's extent"
    masked = bytearray(body)
    for w, _, _ in relocs:
        masked[w - lo:w - lo + 4] = retail[w - lo:w - lo + 4]
    if bytes(masked) != retail:
        diff = next(i for i in range(size) if masked[i] != retail[i])
        return False, f"initializer differs from retail at +{diff:#x}"
    problem = _relocation_problem(data, sections, symbols, sec, lo, relocs, va, retail, img, resolve,
                                  source, sizer, {})
    if problem:
        return False, problem
    return True, f"{size} B at 0x{va:08X} equal to retail, {len(relocs)} relocation(s) on target ({why})"


# a static object's own name: MSVC 7.1 spells a file-scope static `_TheShadowNames` (a C
# name, also in C++) and a function-local one `?d@?BC@??f@@YAHH@Z@4PAHA`; never a `??_`
# compiler name, a `$SG`/`.` label or a `__real@`-style constant
TU_LOCAL_DATA = re.compile(r"^(?:\?[A-Za-z_]|_[A-Za-z_][A-Za-z0-9_]*$)")


def _relocation_problem(data, sections, symbols, sec, lo, relocs, va, retail, img, resolve, source, sizer, placed):
    """None when each relocation in `relocs` (fields of object section `sec` in a
    symbol at offset `lo`, which sits at retail `va` over `retail`'s bytes) lands
    on its target in retail; else why not. `placed` {name: VA} holds the TU-local
    objects already being placed by content on this path."""
    build, _ = _tools()
    for w, index, kind in relocs:
        target = symbols.get(index)
        site = va + w - lo
        value = struct.unpack_from("<I", retail, w - lo)[0]
        if target is None or kind not in (DIR32, DIR32NB):
            return f"+{w - lo:#x}: unsupported relocation type {kind:#x}"
        default = weak_default(data, index, symbols) if target["storage"] == WEAK_EXTERNAL else None
        addend = struct.unpack_from("<i", sec["body"], w)[0]
        function = (target["type"] >> 4) & 3 == DTYPE_FUNCTION
        if target["storage"] != EXTERNAL and (default is None or default["storage"] != EXTERNAL):
            if target["storage"] != STATIC or function or not TU_LOCAL_DATA.match(target["name"]):
                return f"+{w - lo:#x}: relocation to TU-local {target['name']} cannot be placed"
            pointed = value if kind == DIR32 else (value + IMAGE_BASE) & 0xFFFFFFFF
            problem = _tu_local_problem(data, sections, symbols, target, addend, pointed, img, resolve,
                                        source, sizer, placed)
            if problem:
                return f"+{w - lo:#x} (0x{site:08X}): {problem}"
            continue
        if default is not None and not resolve(target["name"], function):
            # no ledger home for the weak name: link.exe binds its default
            target, function = default, (default["type"] >> 4) & 3 == DTYPE_FUNCTION
        if target["name"].startswith("??_C@") and not function:
            pointed = value if kind == DIR32 else (value + IMAGE_BASE) & 0xFFFFFFFF
            problem = string_literal_problem(build, sections, target, addend, pointed, img)
            if problem:
                return f"+{w - lo:#x} (0x{site:08X}): {problem}"
            continue
        want = {(home + addend) & 0xFFFFFFFF for home in resolve(target["name"], function)}  # VAs
        if not want:
            ambiguity = "; ".join(getattr(resolve, "ambiguous", {}).get(target["name"], ()))
            return (f"+{w - lo:#x}: {target['name']} has no retail address in the ledgers "
                    f"(as {'code' if function else 'data'})" + (f": {ambiguity}" if ambiguity else ""))
        # DIR32 holds the target's VA, DIR32NB its RVA: compare VAs, the stub's target included
        actual = value if kind == DIR32 else (value + IMAGE_BASE) & 0xFFFFFFFF
        head = img.read(actual, 5) if function and img.section(actual) == ".text" else None
        stub = (actual + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF if head and head[0] == 0xE9 else None
        if actual not in want and stub not in want:
            return (f"+{w - lo:#x} (0x{site:08X}): retail points at 0x{actual:08X}, "
                    f"{target['name']}+{addend:#x} is " + ", ".join(f"0x{x:08X}" for x in sorted(want)))
    return None


def _tu_local_problem(data, sections, symbols, target, addend, pointed, img, resolve, source, sizer, placed):
    """None when retail's pointer `pointed` addresses the TU-local data object
    `target` (+`addend`) of this object, placed by content; else why not.

    No ledger can name a static: header statics give every including TU its own
    copy at its own address, all under one name. So the copy is placed as a
    string literal is: at retail's pointer less the addend, inside one data
    section, over the compiler-proven sizeof(static), overlapping no data row,
    retail must hold the static's bytes outside relocation fields, and each of
    the static's own relocations must land by these rules in turn."""
    name = target["name"]
    base = (pointed - addend) & 0xFFFFFFFF
    if name in placed:  # a static reached again on its own path: one copy, one address
        return None if placed[name] == base else (
            f"TU-local {name} is placed at 0x{placed[name]:08X} and at 0x{base:08X}")
    sec = sections[target["section"] - 1] if 0 < target["section"] <= len(sections) else None
    if sec is None or sec["body"] is None:
        return f"relocation to TU-local {name} cannot be placed: it has no initialised bytes in this object"
    sizes, why = symbol_size(sections, symbols, target, source, sizer)
    if len(sizes) != 1:
        return f"relocation to TU-local {name} cannot be placed: size unproven ({why})"
    size = next(iter(sizes))
    if not 0 <= addend < size:
        return f"TU-local {name}: addend {addend:#x} is outside its {size} bytes"
    where = img.section(base)
    kinds = [(s["name"], s["va"], s["end"], c) for s, c in zip(img.sections, _characteristics(img))]
    if (where in (None, "header") or section_kind(kinds, base) != "data"
            or img.section(base + size - 1) != where):
        return f"retail points at 0x{pointed:08X}, which is not {size} B of data, for TU-local {name}"
    for start, end, owner in getattr(resolve, "spans", ()):
        if start < base + size and base < end:
            return (f"TU-local {name} at 0x{base:08X}+{size} overlaps data row {owner} "
                    f"0x{start:08X}+{end - start}: a ledger-owned global is no TU-local copy")
    lo = target["value"]
    body = sec["body"][lo:lo + size]
    retail = img.read(base, size)
    relocs = [(w, i, k) for w, i, k in sec["relocs"] if lo - 3 <= w < lo + size]
    if len(body) != size or any(w < lo or w + 4 > lo + size for w, _, _ in relocs):
        return f"TU-local {name}: its bytes or a relocation field leave its {size}-byte extent"
    masked = bytearray(body)
    for w, _, _ in relocs:
        masked[w - lo:w - lo + 4] = retail[w - lo:w - lo + 4]
    if bytes(masked) != retail:
        diff = next(i for i in range(size) if masked[i] != retail[i])
        return f"retail at 0x{base:08X} differs from TU-local {name} at +{diff:#x}"
    problem = _relocation_problem(data, sections, symbols, sec, lo, relocs, base, retail, img, resolve,
                                  source, sizer, {**placed, name: base})
    return f"TU-local {name} at 0x{base:08X}: {problem}" if problem else None


def _compiled_source_groups(rows, object_path):
    """Serialize every provider/probe writer that can share an output path.

    Canonical source aliases and provider-object names can collide. Probe names
    use a CRC32 and Wine treats their paths case-insensitively, so even distinct
    providers must share a scheduling group when any probe stem collides.
    """
    import zlib

    parents, owners, providers = {}, {}, []

    def find(key):
        while parents[key] != key:
            parents[key] = parents[parents[key]]
            key = parents[key]
        return key

    objects = {}
    for index, row in enumerate(rows):
        source = ROOT / row["source"]
        provider = str(source.resolve()).casefold()
        parents.setdefault(provider, provider)
        providers.append(provider)
        if source not in objects:
            objects[source] = str(object_path(source).resolve()).casefold()
        stem = f"{source.stem}_{zlib.crc32((str(source) + row['name']).encode()):08x}"
        resources = [("object", objects[source])] + [
            ("probe", (stem + suffix + ".obj").casefold())
            for suffix in ("", "_array", "_kind")]
        for resource in resources:
            previous = owners.setdefault(resource, provider)
            left, right = find(previous), find(provider)
            if left != right:
                parents[right] = left
    groups = {}
    for index, row in enumerate(rows):
        groups.setdefault(find(providers[index]), []).append((index, row))
    return list(groups.values())


def verify(rows=None, sources=None, compile=True, log=print):
    """Verify data rows (all, or those of `sources`); SystemExit(1) on any failure."""
    build, rl = _tools()
    every = load()
    rows = every if rows is None else rows
    if sources is not None:
        wanted = {Path(s).as_posix().removeprefix("source:") for s in sources}
        rows = [r for r in rows if r["source"] in wanted]
    if not rows:
        return 0
    img, resolve = rl.Image(), Resolver(every)
    # Probe paths are keyed by source and symbol. Keep every source's rows
    # sequential so repeated symbols cannot overwrite each other's probes.
    # Independent providers may compile concurrently. A scheduling group owns
    # every possibly shared provider/probe output, including CRC32 collisions.
    groups = {}
    for index, row in enumerate(rows):
        groups.setdefault(row["source"], []).append((index, row))
    workers = min(build._pool_size(), len(groups))
    if compile and workers > 1:
        compiled_groups = _compiled_source_groups(rows, build.obj_path)
        groups = dict(enumerate(compiled_groups))
        workers = min(workers, len(groups))
    if workers > 1:
        from concurrent.futures import ThreadPoolExecutor

        def check_group(group):
            return [(index, verify_row(row, img, resolve, compile)) for index, row in group]

        results = [None] * len(rows)
        with ThreadPoolExecutor(workers) as pool:
            for checked in pool.map(check_group, sorted(groups.values(), key=len, reverse=True)):
                for index, result in checked:
                    results[index] = result
    else:
        results = (verify_row(row, img, resolve, compile) for row in rows)
    failed = 0
    for row, (ok, message) in zip(rows, results):
        if not ok:
            failed += 1
            log(f"    {row['name']} ({row['source']}): {message}")
    if failed:
        log(f"Data rows: FAIL {failed} of {len(rows)}")
        raise SystemExit(1)
    log(f"Data rows: OK ({len(rows)} row(s) byte-verified)")
    return len(rows)



def _admission_definitions(base, current, candidates):
    """Only inserted file-scope literal aggregates; no expressions or directives."""
    import difflib
    import name_metric
    import rename
    before, after = base.decode('utf-8').splitlines(True), current.decode('utf-8').splitlines(True)
    added = []
    for tag, i, j, a, b in difflib.SequenceMatcher(None, before, after, autojunk=False).get_opcodes():
        if tag == 'equal':
            continue
        if tag != 'insert':
            raise rename.Refusal('unrowed admission allows added definitions only; resolved lines changed or removed')
        prefix = name_metric.strip(''.join(before[:i]))
        if prefix.count('{') != prefix.count('}') or (i and before[i - 1].rstrip().endswith('\\')):
            raise rename.Refusal('unrowed definitions must be added at file scope')
        block = ''.join(after[a:b])
        if re.search(r'\\\r?\n', block):
            raise rename.Refusal('line splicing is forbidden in added definitions')
        added.append(block)
    # Tokenize comments separately so comment delimiters inside character
    # literals cannot conceal executable tokens. Strings/macros/calls refuse.
    token = re.compile(r"(?P<comment>//[^\n]*|/\*[\s\S]*?\*/)|(?P<space>\s+)|"
                       r"(?P<char>'(?:\\.|[^'\\\r\n])+')|"
                       r"(?P<number>(?:0[xX][0-9a-fA-F]+|\d+)(?:[uUlL]*))|"
                       r"(?P<word>[A-Za-z_]\w*)|(?P<punct>::|[{}=;,*+\-])")
    found = []
    for block in added:
        tokens, pos = [], 0
        while pos < len(block):
            m = token.match(block, pos)
            if not m:
                raise rename.Refusal('unsupported added text in unrowed definition')
            if m.lastgroup not in ('comment', 'space'):
                tokens.append((m.lastgroup, m.group()))
            pos = m.end()
        pos = 0
        while pos < len(tokens):
            matches = []
            for name, (request, approval) in candidates.items():
                head = re.findall(r'\w+|::|\*', request['type']) + [name, '=', '{']
                if [v for _, v in tokens[pos:pos + len(head)]] == head:
                    matches.append((name, len(head)))
            if len(matches) != 1:
                raise rename.Refusal('added definition must use exactly an agreed symbol and its registered type')
            name, length = matches[0]
            if name in found:
                raise rename.Refusal('duplicate added definition')
            pos += length
            depth = 1
            while pos < len(tokens) and depth:
                kind, value = tokens[pos]
                if value == '{': depth += 1
                elif value == '}': depth -= 1
                elif kind not in ('number', 'char') and value not in (',', '+', '-'):
                    raise rename.Refusal('unrowed initializer must contain literals only')
                pos += 1
            if depth or pos == len(tokens) or tokens[pos][1] != ';':
                raise rename.Refusal('incomplete unrowed aggregate definition')
            pos += 1
            found.append(name)
    return found


def _unrowed_resolution_view(lane, approval, request):
    """Admission-only source view, anchored to the committed resolution bytes."""
    import hashlib
    import subprocess
    import name_lane
    import name_agreement
    import rename
    source = request['source']
    base = None
    revisions = ['--all']
    seen = set()
    while True:
        commits = lane.git('log', '-1', *revisions, '--format=%H', '-G', approval['id'], '--', name_lane.AGREED).splitlines()
        if not commits:
            break
        commit = commits[0]
        if commit in seen:
            break
        seen.add(commit)
        revisions = [commit + '^@']
        result = subprocess.run(['git', 'show', f'{commit}:{source}'], cwd=lane.root, capture_output=True)
        if result.returncode:
            continue
        sha = hashlib.sha256(result.stdout).hexdigest()
        rid = 'nr-' + hashlib.sha256(f"{approval['key']}|{approval['new']}|{sha}".encode()).hexdigest()[:24]
        if rid == approval['id']:
            base = result.stdout
            break
    if base is None:
        raise rename.Refusal('cannot recover the exact committed source for this unrowed resolution')
    candidates = {}
    for row in lane.state().values():
        if row['status'] not in ('agreed', 'landed') or not name_lane.unrowed_key(row['key']):
            continue
        req = name_lane.request_for_key(lane, row['key'])
        if req and req['source'] == source:
            if row['new'] in candidates:
                raise rename.Refusal('ambiguous agreed data identifier')
            candidates[row['new']] = (req, row)
    original = lane.ctx
    class AdmissionView(rename.Context):
        def read(self, rel):
            return original.read(rel)

        def resolution_source_sha(self, rel):
            if rel == source:
                _admission_definitions(base, self.read(rel), candidates)
                return hashlib.sha256(base).hexdigest()
            return super().resolution_source_sha(rel)
    view = AdmissionView(lane.root, object_scan=False)
    def check(row, req):
        rename.check_agreement(view, 'global', 'agree:' + row['id'], {row['old']}, {row['new']}, int(req['rva'], 16))
        if row['id'].startswith('nr-'):
            votes = [v for v in lane.votes() if v['worker'] != req['registrant']]
            problems = name_agreement.verify_resolution(votes, lane.agreed_rows(), lane.resolutions(),
                         row['key'], row['new'], view.resolution_source_sha(source))
            if problems:
                raise rename.Refusal('unrowed resolution excludes the registrant: ' + '; '.join(problems))
        else:
            name_lane.check_unrowed_agreement(lane, row)
    found = _admission_definitions(base, original.read(source), candidates)
    if approval['new'] not in found:
        raise rename.Refusal('the agreed definition must be added before admission')
    for name in found:
        req, row = candidates[name]
        check(row, req)
    return view, [(candidates[name][0], candidates[name][1]) for name in found], check


def with_row(raw, row):
    """`raw` plus one appended row, leaving every existing byte alone.

    Never re-serialise the ledger to add a line. A csv.DictWriter pass over
    every row rewrites each field with MINIMAL quoting, and 287 of the 2,363
    committed rows carry evidence quoted more widely than that, so an admit
    adding one line produced a 288-line diff: it hid the real change from
    review and clobbered any row a concurrent worker had appended in the
    meantime (re_attempts.log:101649). This is the primitive admit_agreed
    already used for NAME_BASIS.
    """
    import rename          # deferred like every other use in this module
    return rename.appended(raw, [rename.csv_line([row[field] for field in FIELDS])],
                           header=','.join(FIELDS))


def admit_agreed(record_id, symbol, model):
    """Admit an agreed unrowed global through the ordinary retail verifier.

    The caller defines and byte-builds the real symbol first. No placeholder,
    raw-byte initializer, compiler flag or hatch is generated by this command.
    Metadata uses rename's journal/rollback and the ordinary claim fencing.
    """
    import name_lane
    import name_metric
    import rename
    import hatch_counters
    lane = name_lane.Lane(ROOT, rename.Context(ROOT, object_scan=False))
    approvals = [r for r in lane.state().values() if r['id'] == record_id]
    if len(approvals) != 1 or approvals[0]['status'] != 'agreed':
        raise rename.Refusal('admission needs a current, agreed unrowed global naming record')
    approval = approvals[0]
    key = approval['key']
    request = name_lane.request_for_key(lane, key) if name_lane.unrowed_key(key) else None
    if request is None:
        raise rename.Refusal('agreement does not identify a registered unrowed data request')
    section = name_lane.check_unrowed(lane, request)
    new = approval['new']
    rename.check_new_identifier(new, 'global', 'inferred')
    if (name_metric.placeholder(new) or hatch_counters.ADDR_GLOBAL.fullmatch(new)
            or data_identifier(symbol) != new):
        raise rename.Refusal('symbol must spell the agreed, non-address-derived global identifier')
    rva = int(request['rva'], 16)
    evidence = 'agree:' + record_id
    additions, resolution_check = [], None
    if record_id.startswith('nr-'):
        lane.ctx, additions, resolution_check = _unrowed_resolution_view(lane, approval, request)
    rename.check_agreement(lane.ctx, 'global', evidence, {approval['old']}, {new}, rva)
    if (any(r.get('name') == symbol for r in lane.ctx.dicts(rename.DATA_ROWS))
            or any(r.get('name') == symbol for r in lane.ctx.rows())
            or any(p.get('name') == symbol for p in lane.ctx.pins())):
        raise rename.Refusal(f'{symbol} already names a data row, function or pin')
    clash = rename.shared_identifier(lane.ctx, new, re.compile(r'(?!)'))
    if clash:
        raise rename.Refusal(f'{new} already spells {clash}')
    for owned in lane.ctx.dicts('reverse/data_converged.csv'):
        other = owned.get('name', '')
        if other in (symbol, new) or data_identifier(other) == new or new in (rename.fragments_text(other) or ()):
            raise rename.Refusal(f'{new} already names a converged global: {other}')
    if resolution_check:
        resolution_check(approval, request)
    else:
        name_lane.check_unrowed_agreement(lane, approval)
    source = request['source']
    if not model.strip():
        raise rename.Refusal('model is required')
    row = dict(name=symbol, address=request['rva'], address_kind='rva', size=request['size'],
               section=section, source=source, status='matched', evidence=evidence, model=model)
    raw = with_row(lane.ctx.read(rename.DATA_ROWS), row)
    problems = []
    tracked = set(lane.git('ls-files', '--', 'Code').splitlines())
    check(raw, problems, sources_ok=tracked)
    if problems:
        raise rename.Refusal('; '.join(problems))
    plan = rename.Plan('global', approval['old'], symbol, 'inferred', evidence, source, rva)
    plan.edit(lane.ctx, rename.DATA_ROWS, raw)
    plan.edit(lane.ctx, rename.NAME_BASIS, rename.appended(lane.ctx.read(rename.NAME_BASIS), [rename.csv_line(
        ['global', approval['old'], symbol, 'inferred', evidence, source, request['rva']])], header=rename.NAME_BASIS_HEADER))
    landed = {**approval, 'status': 'landed', 'detail': 'data_rows.admit_agreed: retail bytes, relocations and size verified'}
    line = io.StringIO(); writer = csv.DictWriter(line, name_lane.AGREED_COLUMNS, lineterminator='\n')
    writer.writerow(landed)
    plan.edit(lane.ctx, name_lane.AGREED, rename.appended(lane.ctx.read(name_lane.AGREED), [line.getvalue().encode()],
                                                       header=','.join(name_lane.AGREED_COLUMNS)))
    plan.verify = [source]
    # The ordinary checks use a private git index. Include the caller's already
    # written definition and naming inputs in that view, without changing them.
    for path in (source, name_lane.DATA_REQUESTS, name_lane.VOTES, name_lane.MEANINGS, name_lane.RESOLUTIONS):
        content = lane.ctx.read(path)
        if content is not None:
            plan.edit(lane.ctx, path, content)
    held = rename.take_claims([f'file:{source}', rva], True, root=ROOT)
    try:
        def verify_admission(ctx, sources):
            build, rl = _tools()
            obj = build.obj_path(ROOT / source)
            if not build.compile_is_current(ROOT / source, obj):
                raise rename.Refusal('build the source first: admission requires a current compiler receipt')
            snapshot = ((ROOT / source).read_bytes(), obj.read_bytes())
            # Uses the existing sizeof/allocation, retail-byte and relocation
            # checks, including a home for self-references in this candidate.
            extra_rows = []
            symbols = rl.parse_coff(obj.read_bytes())[1]
            for q, a in additions:
                matches = [s['name'] for s in symbols.values() if s['section'] > 0
                           and s['storage'] == EXTERNAL and data_identifier(s['name']) == a['new']]
                if len(matches) != 1:
                    raise rename.Refusal('added definition needs one external object symbol')
                va, extent = IMAGE_BASE + int(q['rva'], 16), int(q['size'])
                homes = [s[0] for s in retail_sections() if s[1] <= va and va + extent <= s[2]
                         and not s[3] & EXECUTABLE]
                if len(homes) != 1:
                    raise rename.Refusal('added definition does not fit one retail data section')
                extra_rows.append(dict(name=matches[0], address=q['rva'], address_kind='rva', size=q['size'],
                                       section=homes[0], source=source, status='matched',
                                       evidence='agree:' + a['id'], model=model))
            resolve = Resolver([r for r in existing if r['name'] not in {x['name'] for x in extra_rows}] + extra_rows +
                               ([] if any(x['name'] == row['name'] for x in extra_rows) else [row]))
            for extra in extra_rows:
                ok, why = verify_row(extra, rl.Image(), resolve, compile=False, sizer=compiled_size)
                if not ok:
                    raise rename.Refusal('added data definition refused: ' + why)
            ok, why = verify_row(row, rl.Image(), resolve, compile=False, sizer=compiled_size)
            if not ok:
                raise rename.Refusal('data admission refused: ' + why)
            if snapshot != ((ROOT / source).read_bytes(), obj.read_bytes()):
                raise rename.Refusal('source/object changed during data admission')
            rename.check_agreement(ctx, 'global', evidence, {approval['old']}, {new}, rva)
            if resolution_check:
                for q, a in additions:
                    resolution_check(a, q)
            else:
                name_lane.check_unrowed_agreement(lane, approval)
            print('data_rows: ' + why)
            return True
        rename.apply_rename(plan, ctx=lane.ctx, verify=verify_admission, checks=rename.ledger_checks, claimed=held)
    except BaseException:
        held.release(ROOT)
        raise
    print(f'data_rows: admitted {symbol} at {request["rva"]}; basis inferred, {evidence}; no hatch added')
    print('Stage ' + ', '.join(sorted(plan.after)))
    print(f'After pushing: python3 tools/claims.py release file:{source} 0x{rva:08X}')
    return row


def data_identifier(symbol):
    match = re.match(r'^\?([A-Za-z_]\w*)@@3', symbol)
    if match:
        return match.group(1)
    # C external spelling, not a local/static or an arbitrary decorated alias.
    match = re.fullmatch(r'_([A-Za-z_]\w*)', symbol)
    return match.group(1) if match else None

def pointer_evidence_index(img, root):
    """Small address/extent index streamed from ledgers, never a pointer oracle."""
    import bisect
    entities = {}
    defined_starts = set()
    def add(start, size, name, kind):
        if size <= 0:
            return  # no extent: linker markers (including ___ImageBase) are not entities
        entities.setdefault(start, []).append(dict(start=start, size=size, name=name, kind=kind))
    for filename in ("data_rows.csv", "data_ledger.csv", "data_converged.csv", "functions.csv"):
        path = Path(root) / "reverse" / filename
        if not path.exists():
            continue
        with path.open(newline="", encoding="utf-8") as f:
            for r in csv.DictReader(f):
                if filename == "functions.csv":
                    add(img.base + int(r["target_rva"],16), int(r["target_size"] or 0), r["name"], "function")
                else:
                    value = int(r["address"],16)
                    if filename in ("data_ledger.csv", "data_converged.csv") or r.get("address_kind") == "rva":
                        value += img.base
                    size=int(r.get("size") or 0)
                    kind=r.get("kind","data")
                    if filename == "data_rows.csv":
                        defined_starts.add(value)
                    elif filename == "data_ledger.csv":
                        # Inventory spans often run to the next named row, across
                        # unrelated objects. Prefer verified defined extents.
                        if value in defined_starts:
                            continue
                        if kind in ("string","wstring"):
                            width=2 if kind=="wstring" else 1
                            raw=img.read(value,size) if size>0 else None
                            end=next((at+width for at in range(0,len(raw)-width+1,width)
                                if raw[at:at+width]==bytes(width)),None) if raw else None
                            if end is None:
                                continue
                            size=end
                        elif kind=="float":
                            literal=re.fullmatch(r"__real@([0-9a-fA-F]{8}|[0-9a-fA-F]{16})",r["name"])
                            size=len(literal[1])//2 if literal else size if size in (4,8) else 0
                    add(value, size, r["name"], kind)
    starts = sorted(entities)
    ends, owners, best, owner = [], [], -1, None
    for start in starts:
        for e in entities[start]:
            if start + e["size"] > best:
                best, owner = start + e["size"], e
        ends.append(best); owners.append(owner)
    def classify(value):
        section = next((sec for sec in img.sections if sec["va"] <= value < sec["end"]), None)
        if section is None:
            return "B", "outside_retail_sections", []
        if value in entities:
            return "A", "entity_start", entities[value]
        n = bisect.bisect_right(starts,value)-1
        if n >= 0 and ends[n] > value:
            return "B", "entity_interior", [owners[n]]
        if section["name"] in (".rdata", ".data") and img.read(value-1,1) == b"\0":
            raw = img.read(value, min(4096,section["end"]-value))
            end = raw.find(b"\0")
            if end >= 2 and all(32 <= b < 127 for b in raw[:end]):
                return "A", "retail_string_start", [dict(name=raw[:end].decode("ascii"), start=value, size=end+1, kind="string")]
        return "B", "unmapped_image_address", []
    return classify


def data_pointer_evidence(row, body, relocations, img, classify):
    """Report-only evidence from bytes and COFF fields, not retail .reloc.
    relocations are row-relative (offset, COFF type); only DIR32 is an absolute
    pointer fixup. Other/partial relocation fields are excluded, not passed.
    """
    size, va = int(row["size"]), va_of(row)
    counts = dict(aligned_words=0, byte_differences=0, relocation_overlap=0, trailing_bytes_not_scanned=size%4)
    retail = img.read(va,size)
    if len(body) != size or len(retail) != size:
        return dict(counts=dict(extent_unanalyzed=1), findings=[])
    result = []
    for off in range(0,size-3,4):
        counts["aligned_words"] += 1
        overlap = [(at,kind) for at,kind in relocations if off-3 <= at < off+4]
        if overlap:
            counts["relocation_overlap"] += 1
            continue
        if body[off:off+4] != retail[off:off+4]:
            counts["byte_differences"] += 1
            continue
        value=struct.unpack_from("<I",retail,off)[0]
        if not any(sec["va"] <= value < sec["end"] for sec in img.sections):
            continue
        tier,reason,owners=classify(value)
        result.append(dict(tier=tier,reason=reason,offset=off,retail_value=hex(value),object_value=hex(value),entities=owners))
    for off,kind in relocations:
        if kind != DIR32 or off < 0 or off+4 > size:
            counts["unsupported_or_straddling_relocation"] = counts.get("unsupported_or_straddling_relocation",0)+1
            continue
        value=struct.unpack_from("<I",retail,off)[0]
        if not any(sec["va"] <= value < sec["end"] for sec in img.sections):
            result.append(dict(tier="B",reason="object_relocation_to_implausible_retail_va",offset=off,
                retail_value=hex(value),object_value=hex(struct.unpack_from("<I",body,off)[0]),entities=[]))
    before_a=sum(d["tier"]=="A" for d in result)
    before_b=sum(d["tier"]=="B" for d in result)
    if before_b > before_a:
        counts["coherence_demoted"] = before_a
        for d in result:
            if d["tier"]=="A":
                d.update(original_tier="A",original_reason=d["reason"],tier="B",reason="row_coherence_demoted",
                         row_tier_a_before=before_a,row_tier_b_before=before_b)
    return dict(counts=counts,findings=result)


def defined_data_pointer_report(manifest, img, root):
    """Inspect frozen objects without compiling or changing verification results."""
    import hashlib, collections, json
    build,rl=_tools()
    classify=pointer_evidence_index(img,root)
    manifest=Path(manifest)
    entries=json.loads(manifest.read_text())
    by_source=collections.defaultdict(list)
    for entry in entries:
        by_source[entry.get("source","").replace("\\","/")].append(entry)
    parsed={}; findings=[]; counts=collections.Counter()
    rows=load(Path(root)/"reverse/data_rows.csv")
    # Converged has no extents. Cover a name there only through a defined data row;
    # inventory extents alone never assert that we define a global.
    for row in rows:
        counts["rows_considered"]+=1
        definitions=[]
        for entry in by_source.get(row["source"],[]):
            path=manifest.parent/entry["path"].replace("\\","/")
            if path not in parsed:
                raw=path.read_bytes()
                if hashlib.sha256(raw).hexdigest()!=entry["sha256"]:
                    raise ValueError("object manifest hash mismatch")
                parsed[path]=rl.parse_coff(raw)
            sections,symbols=parsed[path]
            for sym in symbols.values():
                if sym["name"]==row["name"] and sym["section"]>0 and sym["storage"]==EXTERNAL:
                    definitions.append((entry,sections,symbols,sym))
        if len(definitions)!=1:
            counts["rows_object_definition_unresolved"]+=1
            continue
        entry,sections,symbols,sym=definitions[0]
        sec=sections[sym["section"]-1];lo=sym["value"];size=int(row["size"])
        body=sec["body"]
        if body is None:
            body=bytes(sec["size"])
        if lo+size>len(body):
            counts["rows_object_extent_unanalyzed"]+=1
            continue
        relocs=[(off-lo,kind) for off,_index,kind in sec["relocs"] if lo-3<=off<lo+size]
        result=data_pointer_evidence(row,body[lo:lo+size],relocs,img,classify)
        counts.update(result["counts"]);counts["rows_analyzed"]+=1
        for d in result["findings"]:
            d.update(row=row["name"],source=row["source"],retail_rva=hex(va_of(row)-img.base),
                     symbol=row["name"],field_retail_rva=hex(va_of(row)-img.base+d["offset"]),
                     size=size,object=entry.get("provider",Path(entry["path"]).name))
            if d["reason"]=="object_relocation_to_implausible_retail_va":
                fields=[(index,kind) for off,index,kind in sec["relocs"] if off-lo==d["offset"]]
                d["relocation_targets"]=[symbols[index]["name"] for index,_kind in fields]
                d["object_value_kind"]="COFF addend"
            findings.append(d)
    counts["tier_a"]=sum(d["tier"]=="A" for d in findings)
    counts["tier_b"]=sum(d["tier"]=="B" for d in findings)
    counts["rows_tier_a"]=len({d["row"] for d in findings if d["tier"]=="A"})
    counts["rows_tier_b"]=len({d["row"] for d in findings if d["tier"]=="B"})
    unbounded=[]
    converged = Path(root)/"reverse/data_converged.csv"
    if converged.exists():
        with converged.open(newline="",encoding="utf-8") as f:
            names={r["name"] for r in csv.DictReader(f)}
        covered={r["name"] for r in rows}
        unbounded=sorted(names-covered)
        counts["converged_names_without_data_row_extent"] = len(unbounded)
    ledger_hashes={}
    for filename in ("data_rows.csv","data_ledger.csv","data_converged.csv","functions.csv"):
        path=Path(root)/"reverse"/filename
        if path.exists():
            h=hashlib.sha256()
            with path.open("rb") as f:
                for block in iter(lambda:f.read(65536),b""):
                    h.update(block)
            ledger_hashes[filename]=h.hexdigest()
    return dict(mode="report-only",counts=dict(counts),findings=findings,converged_without_extents=unbounded,
        inputs=dict(manifest_sha256=hashlib.sha256(manifest.read_bytes()).hexdigest(),
            retail_sha256=hashlib.sha256(img.data).hexdigest(),ledger_hashes=ledger_hashes,
            detector_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()),
        limitations=["No retail relocation oracle exists; tiers are address evidence, not runtime proof.",
            "Forward scan uses four-byte words relative to the row start; unaligned fields without object fixups are unscanned.",
            "Manifest must bind the intended objects; no compilation or build-refusal wiring.",
            "Converged rows without data_rows extents are not analyzed."])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--check", action="store_true", help="integrity only")
    ap.add_argument("--verify", nargs="*", metavar="SOURCE", help="compile and verify (all rows, or these sources)")
    ap.add_argument('--admit-agreed', metavar='ID', help='admit a blind-agreed unrowed global from its current object')
    ap.add_argument('--symbol', help='exact COFF external defined by the source')
    ap.add_argument('--model', help='model/account label for the admitted data row')
    ap.add_argument("--pointer-report", metavar="OBJECT_MANIFEST", help="report tiered pointer evidence from frozen objects; never compile/refuse rows")
    ap.add_argument("--pointer-ledgers",type=Path,default=ROOT,help="repository root containing frozen reverse ledgers for pointer report")
    ap.add_argument("--report-out", type=Path, default=Path("build/data_pointer_report.json"))
    args = ap.parse_args(argv)
    if args.pointer_report:
        import json
        _build,rl=_tools()
        report=defined_data_pointer_report(args.pointer_report,rl.Image(),args.pointer_ledgers)
        args.report_out.parent.mkdir(parents=True,exist_ok=True)
        args.report_out.write_text(json.dumps(report,indent=2)+"\n")
        print(json.dumps(report["counts"],indent=2))
        return 0
    if args.admit_agreed:
        import rename
        if not args.symbol or not args.model or args.check or args.verify is not None:
            ap.error('--admit-agreed needs --symbol and --model, without --check/--verify')
        try:
            admit_agreed(args.admit_agreed, args.symbol, args.model)
        except (rename.Refusal, OSError, ValueError) as exc:
            print('data_rows: REFUSED: ' + str(exc))
            return 1
        return 0
    problems = []
    n = check(DATA_ROWS.read_bytes(), problems) if DATA_ROWS.exists() else 0
    for p in problems:
        print(p)
    if problems:
        return 1
    print(f"data_rows: {n} row(s), integrity OK")
    if args.verify is not None:
        verify(sources=args.verify or None)
    return 0


if __name__ == "__main__":
    sys.exit(main())
