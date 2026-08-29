"""COFF archive (.lib) reader for ledger rows whose bytes come from a library.

A `.lib` is an `!<arch>` archive whose members are verbatim COFF objects, so a
member extracted from one feeds the same symbol/relocation reader that a
freshly compiled .obj does — see build.py's extract_lib_members.
"""
import struct

# i386 relocation types and the width of the field they patch. A lib member is
# pre-link: every one of these sites holds an addend rather than the address the
# linker later wrote, so a byte comparison against retail has to skip them.
RELOC_WIDTH = {
    0x0006: 4,  # DIR32
    0x0007: 4,  # DIR32NB
    0x000A: 2,  # SECTION
    0x000B: 4,  # SECREL
    0x000C: 4,  # SECREL7
    0x0014: 4,  # REL32
}


def read_archive(path):
    """Return [(member_name, member_bytes)] for every non-linker member."""
    data = open(path, "rb").read()
    if data[:8] != b"!<arch>\n":
        raise ValueError(f"{path}: not an ar archive")
    offset = 8
    longnames = b""
    members = []
    while offset + 60 <= len(data):
        header = data[offset:offset + 60]
        if header[58:60] != b"`\n":
            break
        name = header[0:16].decode("latin1").rstrip()
        try:
            size = int(header[48:58].decode("latin1").strip())
        except ValueError:
            break
        body = data[offset + 60:offset + 60 + size]
        offset += 60 + size + (size & 1)  # members are 2-byte aligned
        if name in ("/", "/ "):
            continue  # linker symbol index
        if name == "//":
            longnames = body
            continue
        if name.startswith("/"):
            # a name too long for the 16-byte field is an offset into //
            start = int(name[1:])
            name = longnames[start:longnames.index(b"\0", start)].decode("latin1")
        members.append((name.rstrip("/"), body))
    return members
