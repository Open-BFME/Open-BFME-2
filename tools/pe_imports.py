"""Read PE32 import identities without inferring aliases from copied addresses."""
import struct
import re
from typing import NamedTuple


class ImportEntry(NamedTuple):
    dll: str
    name: str | None
    ordinal: int | None


def coff_import_names(symbol):
    """Export spellings supported by a 32-bit MSVC imported COFF name.

    Import libraries may publish the decorated name (Miles does) or the
    undecorated C name (Win32 does). C++ names retain their full identity;
    namespaces and CRT synonyms are never erased as linker decoration.
    """
    if not symbol.startswith("__imp_"):
        return set()
    name = symbol[len("__imp_"):]
    if not name:
        return set()
    names = {name}
    if name.startswith("_"):
        names.add(re.sub(r"@\d+$", "", name[1:]))
    elif re.fullmatch(r"@[^@]+@\d+", name):
        names.add(name[1:name.rfind("@")])
    return names


def read_imports(data):
    """Return absolute IAT-slot addresses mapped to declared import identities.

    Ordinal imports retain their ordinal but have no verified export name.
    Malformed, truncated, or bound-only lookup data fails closed with ValueError.
    This parser deliberately does not normalize DLL/export names or infer aliases.
    """
    def unpack(fmt, offset):
        size = struct.calcsize(fmt)
        if offset < 0 or offset + size > len(data):
            raise ValueError("truncated PE import metadata")
        return struct.unpack_from(fmt, data, offset)

    if data[:2] != b"MZ":
        raise ValueError("DOS MZ header required")
    pe, = unpack("<I", 0x3C)
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("PE signature required")
    section_count, = unpack("<H", pe + 6)
    optional_size, = unpack("<H", pe + 20)
    optional = pe + 24
    magic, = unpack("<H", optional)
    if magic != 0x10B or optional_size < 112:
        raise ValueError("PE32 optional header with import directory required")
    image_base, = unpack("<I", optional + 28)
    header_size, = unpack("<I", optional + 60)
    directory_count, = unpack("<I", optional + 92)
    if directory_count < 2:
        return {}
    imports_rva, imports_size = unpack("<II", optional + 104)
    if not imports_rva and not imports_size:
        return {}
    if not imports_rva or imports_size < 20:
        raise ValueError("invalid PE import directory extent")

    sections = []
    for index in range(section_count):
        header = optional + optional_size + index * 40
        virtual_address, raw_size, raw_pointer = unpack("<III", header + 12)
        sections.append((virtual_address, raw_size, raw_pointer))

    def location(rva, size=1):
        if 0 <= rva < header_size and rva + size <= header_size:
            offset, limit = rva, min(header_size, len(data))
        else:
            for address, raw_size, raw_pointer in sections:
                if address <= rva and rva + size <= address + raw_size:
                    offset = raw_pointer + rva - address
                    limit = min(raw_pointer + raw_size, len(data))
                    break
            else:
                raise ValueError(f"unmapped PE import RVA 0x{rva:X}")
        if offset < 0 or offset + size > limit:
            raise ValueError("PE import metadata extends beyond file-backed data")
        return offset, limit

    def string(rva):
        offset, limit = location(rva)
        end = data.find(b"\0", offset, limit)
        if end < 0:
            raise ValueError("unterminated PE import name")
        try:
            result = data[offset:end].decode("ascii")
        except UnicodeDecodeError as exc:
            raise ValueError("non-ASCII PE import name") from exc
        if not result:
            raise ValueError("empty PE import name")
        return result

    result = {}
    # Some retail linkers count only populated descriptors in Directory.Size.
    # Permit exactly one trailing null descriptor, never an extra live entry.
    for index in range(imports_size // 20 + 1):
        descriptor, _ = location(imports_rva + index * 20, 20)
        fields = unpack("<IIIII", descriptor)
        if not any(fields):
            return result
        if (index + 1) * 20 > imports_size:
            raise ValueError("unterminated PE import directory")
        original, _timestamp, _forwarder, dll_rva, first = fields
        if not first:
            raise ValueError("PE import descriptor has no IAT")
        dll = string(dll_rva)
        lookup = original or first
        for item in range(len(data) // 4):
            offset, _ = location(lookup + item * 4, 4)
            value, = unpack("<I", offset)
            if not value:
                break
            # Prove that the corresponding destination slot is file-backed too.
            location(first + item * 4, 4)
            entry = (ImportEntry(dll, None, value & 0xFFFF)
                     if value & 0x80000000
                     else ImportEntry(dll, string(value + 2), None))
            slot = image_base + first + item * 4
            if slot in result and result[slot] != entry:
                raise ValueError("conflicting identities for one PE IAT slot")
            result[slot] = entry
        else:
            raise ValueError("unterminated PE import lookup table")
    raise ValueError("unterminated PE import directory")


def named_thunk_import(body, imports):
    """Identify only a complete six-byte JMP [IAT] to a named import."""
    if len(body) != 6 or body[:2] != b"\xff\x25":
        return None
    slot, = struct.unpack_from("<I", body, 2)
    entry = imports.get(slot)
    return entry if entry is not None and entry.name is not None else None


def same_named_import_thunk(left, right, imports):
    """Allow different IAT slots only when both declare the exact DLL/export."""
    identity = named_thunk_import(left, imports)
    return identity is not None and identity == named_thunk_import(right, imports)


def same_named_import_slots(symbol, slots, imports):
    """Prove duplicate IAT slots declare one DLL/export and the COFF name.

    Retail can import fgetc twice from msvcr71.dll. Equal function names in
    different DLLs, ordinal imports, or undeclared slots are not this case.
    """
    names = coff_import_names(symbol)
    entries = [imports.get(slot) for slot in slots]
    if not names or not entries or entries[0] is None:
        return False
    first = entries[0]
    return first.name in names and all(entry == first for entry in entries)


def generated_import_scaffold(row, read_target, load_imports, read_source):
    """Prove a generator-owned six-byte import placeholder, never from a tag alone.

    Only gen_small's canonical ji_RVA record in imports_NNN.cpp qualifies.
    Its slot, DLL and export must agree with the complete retail JMP [IAT].
    This is compiler/linker scaffolding; no authored C++ body is exempted.
    Missing or invalid retail evidence keeps the ordinary admission rules.
    """
    try:
        raw_rva = row["target_rva"]
        rva = int(raw_rva, 16) if isinstance(raw_rva, str) else int(raw_rva)
        if not (0 <= rva <= 0xFFFFFFFF) or int(row["target_size"]) != 6:
            return False
        source_match = re.fullmatch(r"Code/gen_small/imports_([0-9]{3,})\.cpp",
                                    row.get("source", ""))
        if (row.get("status") != "matched"
                or row.get("name") != "?ji_%08x@@YAXXZ" % rva
                or source_match is None):
            return False
        tokens = row.get("notes", "").split(";")
        if len(tokens) != 5 or tokens[0] != "gen-import":
            return False
        fields = {}
        for token in tokens[1:]:
            key, value = token.split("=", 1)
            if key in fields or not value:
                return False
            fields[key] = value
        if (set(fields) != {"slot", "dll", "import", "target"}
                or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", fields["slot"])
                or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", fields["import"])):
            return False
        text = read_source(row["source"])
        if isinstance(text, bytes):
            text = text.decode("utf-8")
        lines = text.splitlines()
        header = [
            "// cl: /Oi-",
            None,
            "// Do not edit by hand; regenerate instead.",
            "//",
            "// Each ji_<rva> reproduces a retail six-byte named import thunk. The imported",
            "// declaration uses the export name found at the retail IAT slot so the import",
            "// reference gate verifies identity as well as the FF 25 + DIR32 instruction.",
        ]
        if len(lines) < len(header):
            return False
        for index, expected in enumerate(header):
            if expected is not None and lines[index] != expected:
                return False
        generated = re.fullmatch(
            r"// Generated by: python3 tools/gen_small.py gen-imports --batch ([0-9]+) --limit ([0-9]+)",
            lines[1])
        if (generated is None or int(generated[1]) != int(source_match[1])
                or int(generated[2]) <= 0):
            return False
        declaration = 'extern "C" __declspec(dllimport) void %s();' % fields["import"]
        wrapper = "void ji_%08x() { %s(); }" % (rva, fields["import"])
        if lines.count(declaration) != 1 or lines.count(wrapper) != 1:
            return False
        vocabulary = re.compile(
            r'(?:extern "C" __declspec\(dllimport\) void [A-Za-z_][A-Za-z0-9_]*\(\);'
            r'|void ji_[0-9a-f]{8}\(\) \{ [A-Za-z_][A-Za-z0-9_]*\(\); \}|)')
        if any(not vocabulary.fullmatch(line) for line in lines[len(header):]):
            return False
        body = read_target(rva, 6)
        if len(body) != 6 or body[:2] != b"\xff\x25":
            return False
        if struct.unpack_from("<I", body, 2)[0] != int(fields["slot"], 16):
            return False
        entry = named_thunk_import(body, load_imports())
        return entry == ImportEntry(fields["dll"], fields["import"], None)
    except (KeyError, ValueError, TypeError, OSError, struct.error):
        return False
