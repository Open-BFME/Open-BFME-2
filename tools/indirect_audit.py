"""Flag matched rows whose indirect calls go somewhere the source may not say.

A byte comparison cannot see where an indirect call goes. `call dword ptr
[X]` is ff 15 followed by a DIR32 that the comparison masks, so a source that
calls the wrong function through the wrong pointer still matches, and the
gate's DIR32 consistency check does not catch it either - that check asks
whether one symbol resolves to two addresses, and a wrong name used
consistently never does.

atlconv.cpp was matching 11 of 11 while modelling a call as GetACP() that
retail makes through a lazy code-page dispatcher at 0x00DA5E40.

This lists, for every matched row, the ff 15 sites whose target is NOT an
import slot. Those are calls through the image's own function pointers, and
a source that spells one as an imported API is wrong however well it
matches. Being on the list is not itself a fault: mem_ops.cpp is on it and
is right, because it models the game's pluggable allocator as the pointer it
is. What the list is for is that every row on it needs its source read once -
and a row that appears here NEW, after an edit, needs reading again.

An import slot is not proof of correctness either. It only means the shape is
the ordinary one.

Run from the repo root: python3 tools/indirect_audit.py [--all]
"""
import csv, pathlib, struct, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import build

BASE = 0x400000


def iat_slots(data):
    """Every FirstThunk slot the import descriptors actually declare.

    The IAT data-directory entry is empty in this image, so the range it names
    would flag every import as suspicious. Walking the descriptors is the
    reliable way to know which addresses are import slots.
    """
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    magic = struct.unpack_from("<H", data, pe + 24)[0]
    dd = pe + 24 + (96 if magic == 0x10B else 112)
    imp = struct.unpack_from("<II", data, dd + 8)[0]
    slots = set()
    off = imp
    while True:
        oft, _ts, _fc, _name, first = struct.unpack(
            "<IIIII", build.read_target_bytes(off, 20))
        if oft == 0 and first == 0:
            break
        thunk = oft or first
        i = 0
        while struct.unpack("<I", build.read_target_bytes(thunk + 4 * i, 4))[0]:
            slots.add(first + 4 * i)
            i += 1
        off += 20
    return slots


def main():
    show_all = "--all" in sys.argv
    data, _ = build.exe_image()
    slots = iat_slots(data)
    flagged = 0
    for row in csv.DictReader(open("reverse/functions.csv", newline="",
                                   encoding="utf-8-sig")):
        if row["status"] != "matched":
            continue
        source = row["source"] or ""
        if not source or "gen_asm" in source:
            continue
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        body = build.read_target_bytes(rva, size)
        hits = []
        for i in range(len(body) - 5):
            if body[i] == 0xFF and body[i + 1] == 0x15:
                slot = struct.unpack_from("<I", body, i + 2)[0] - BASE
                if show_all or slot not in slots:
                    hits.append((rva + i, slot, slot in slots))
        if hits:
            flagged += 1
            print(f"{rva:#010x} {row['name'][:64]}")
            print(f"     {source}")
            for at, slot, in_iat in hits:
                where = "IAT" if in_iat else "NOT in the IAT"
                print(f"     +{at - rva:#06x} call [{slot + BASE:#010x}]  {where}")
    print(f"{flagged} matched row(s) listed; the import descriptors "
          f"declare {len(slots)} slots")


if __name__ == "__main__":
    main()
