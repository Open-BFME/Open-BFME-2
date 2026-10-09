#!/usr/bin/env python3
"""Open-BFME-1's tools/reloc_ledger.py: only the part tools/data_rows.py reads.

data_rows.py verifies a data row against retail's image and the row's object
through four helpers of Open-BFME-1's typed relocation ledger: the retail
image by VA (Image), a COFF object reader (parse_coff), the size a mangled
data name declares (mangled_scalar_size) and a CSV reader (read_csv_rows).
They are copied here verbatim, under the same module and names, so
data_rows.py stays Open-BFME-1's file. The typed relocation ledger itself (the
rest of that tool: compiler, dump-analysis, structure, vtable and use-proven
rows, the data item partition) is not ported; a port of it replaces this file.
"""
import bisect
import csv
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

DIR32, DIR32NB, REL32 = 0x0006, 0x0007, 0x0014
CNT_CODE, UNINIT, LNK_INFO, LNK_REMOVE, COMDAT_FLAG, DISCARDABLE = 0x20, 0x80, 0x200, 0x800, 0x1000, 0x02000000
NRELOC_OVFL = 0x01000000
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
DATA_SECTIONS = (".rdata", ".data", ".idata", "STLPORT_")


# --------------------------------------------------------------------------- retail image

class Image:
    """Retail's sections by VA; the virtual-only tail of a section reads as zero."""

    def __init__(self, data=None):
        data = data if data is not None else build.EXE.read_bytes()
        self.data = data
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        count = struct.unpack_from("<H", data, pe + 6)[0]
        optional = struct.unpack_from("<H", data, pe + 20)[0]
        self.base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
        self.size = struct.unpack_from("<I", data, pe + 24 + 56)[0]
        dirs = pe + 24 + 96
        self.directories = [struct.unpack_from("<II", data, dirs + 8 * i) for i in range(16)]
        self.sections = []
        for i in range(count):
            o = pe + 24 + optional + 40 * i
            name = data[o:o + 8].rstrip(b"\0").decode("latin-1").strip()
            vsize, rva, rsize, rptr = struct.unpack_from("<IIII", data, o + 8)
            self.sections.append({"name": name, "va": self.base + rva, "end": self.base + rva + max(vsize, rsize),
                                  "raw_end": self.base + rva + min(vsize, rsize) if vsize else self.base + rva + rsize,
                                  "raw": rptr})
        self._starts = [s["va"] for s in self.sections]
        self.by_name = {s["name"]: s for s in self.sections}

    def section(self, va):
        i = bisect.bisect_right(self._starts, va) - 1
        if i >= 0 and va < self.sections[i]["end"]:
            return self.sections[i]["name"] or "?"
        return "header" if self.base <= va < self.base + self.size else None

    def in_image(self, va):
        return self.base + 0x1000 <= va < self.base + self.size

    def read(self, va, size):
        i = bisect.bisect_right(self._starts, va) - 1
        if i < 0 or va + size > self.sections[i]["end"]:
            return None
        s = self.sections[i]
        out = bytearray(size)
        raw_n = max(0, min(va + size, s["raw_end"]) - va)
        if raw_n:
            off = s["raw"] + va - s["va"]
            out[:raw_n] = self.data[off:off + raw_n]
        return bytes(out)

    def u32(self, va):
        raw = self.read(va, 4)
        return struct.unpack("<I", raw)[0] if raw else None

    def is_data(self, va):
        return self.section(va) in DATA_SECTIONS


# --------------------------------------------------------------------------- COFF

def parse_coff(data):
    """(sections, symbols): sections[n-1] = dict; symbols[index] = dict (aux records skipped)."""
    nsec, _, symtab, nsym, optional = struct.unpack_from("<HIIIH", data, 2)
    strings = symtab + 18 * nsym
    sections = []
    for i in range(nsec):
        o = 20 + optional + 40 * i
        raw_name = data[o:o + 8]
        if raw_name[:1] == b"/":
            idx = int(raw_name[1:].rstrip(b"\0"))
            name = data[strings + idx:data.index(b"\0", strings + idx)].decode("latin-1")
        else:
            name = raw_name.rstrip(b"\0").decode("latin-1")
        size, ptr, relptr = struct.unpack_from("<III", data, o + 16)
        nrel = struct.unpack_from("<H", data, o + 32)[0]
        flags = struct.unpack_from("<I", data, o + 36)[0]
        first = 0
        if flags & NRELOC_OVFL and nrel == 0xFFFF:
            # the real count (this entry included) is the first entry's address field
            nrel, first = struct.unpack_from("<I", data, relptr)[0], 1
        relocs = [struct.unpack_from("<IIH", data, relptr + 10 * r) for r in range(first, nrel)]
        sections.append({"number": i + 1, "name": name, "size": size, "flags": flags,
                         "body": data[ptr:ptr + size] if ptr and not flags & UNINIT else None,
                         "relocs": relocs, "align": (flags >> 20) & 0xF})
    symbols = {}
    index = 0
    while index < nsym:
        rec = data[symtab + 18 * index:symtab + 18 * index + 18]
        if rec[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", rec, 4)[0]
            name = data[strings + off:data.index(b"\0", strings + off)].decode("latin-1")
        else:
            name = rec[:8].rstrip(b"\0").decode("latin-1")
        value, section, typ, storage, aux = struct.unpack_from("<IhHBB", rec, 8)
        symbols[index] = {"index": index, "name": name, "value": value, "section": section, "type": typ,
                          "storage": storage}
        index += 1 + aux
    return sections, symbols


# --------------------------------------------------------------------------- names and types

SCALAR = {"H": 4, "I": 4, "J": 4, "K": 4, "M": 4, "F": 2, "G": 2, "D": 1, "C": 1, "E": 1, "N": 8, "O": 8,
          "_N": 1, "_J": 8, "_K": 8, "_W": 2}
MANGLED_DATA = re.compile(r"^(\?[^@?][^@]*@(?:[^@]+@)*@)([23])(.+)$")


def mangled_identity(name):
    """(qualified name, storage+type code) of a mangled global/static data name, or None."""
    m = MANGLED_DATA.match(name)
    return (m.group(1), m.group(2) + m.group(3)) if m else None


def mangled_scalar_size(name):
    """Bytes a mangled data name declares when its type is an arithmetic scalar or
    enum, else None. P/Q (pointer OR array: `T x[]` mangles like `T* x`) and
    class types declare no size a name alone can bound."""
    ident = mangled_identity(name)
    if ident is None:
        return None
    t = ident[1][1:]
    if t.startswith("W4"):
        return 4
    return SCALAR.get(t[:2] if t.startswith("_") else t[:1])


def read_csv_rows(path):
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))
