#!/usr/bin/env python3
"""Does a static library's code appear in this image at all, and where?

`lib_window_sweep.py` answers a narrower question: inside the window an archive's
ALREADY-ATTACHED rows span, which members can be placed under the count-agreement
standard. That is the right standard for growing a library claim, and the wrong
one for starting it -- with no attached rows an archive has no window, so the
sweep reports nothing claimable no matter how much of the archive the image
holds. It says nothing about whether the archive matches at all.

This asks the blunt question instead. For every `.text` COMDAT in every member:
take the longest run of bytes carrying no relocation, and look for that run in
`.text`. A run found EXACTLY ONCE is a placement that needs no window to anchor
it -- the same masked-needle argument `locate.py` makes for a compiled source,
which is what seeds the first rows an archive ever gets.

  python3 tools/lib_probe.py vendor/comsupp/comsupp.lib
  python3 tools/lib_probe.py vendor/d3dx9/d3dx9.lib --csv build/wave_d3dx9.csv

A `--csv` wave goes to `tools/land_wave.py`, which proves each row through the
build gate before the ledger keeps it; a unique needle is evidence, not proof.

What this found when it was written (2026-09-12)
------------------------------------------------
  vendor/comsupp/comsupp.lib   5 unique placements, 2,392 B  -- attached
  Vc7/lib/libcmt.lib          20 unique placements, 3,111 B  -- not vendored here
  vendor/d3dx9/d3dx9.lib       0 unique placements, 2,201 spans absent
  vendor/dxerr9/dxerr9.lib     0 unique placements

The split is the finding. Both DirectX archives were vendored from the DirectX
9.0 SDK Update (Summer 2003) because that is what Open-BFME-1's `lotrbfme.exe`
links; BFME 2 ships three years later and links a LATER SDK, so none of their
spans appear in this image. `_DXGetErrorString9A@4` shows it exactly: retail's
copy sits at 0x0062B16A behind the pin `_bfmeDirectXErrorName@4`, and its search
tree opens on HRESULT 0x80093102 where the vendored archive's opens on
0x80096001 -- a different case set, i.e. a different build. Retail's copy also
carries a two-byte hot-patch pad (`mov edi,edi`) ahead of its frame setup, which
cl 13.10 has no flag to emit, so that body cannot be recovered as C++ either. It
needs the matching SDK, and the first HRESULT above is how to recognise it.

The compiler's own support libraries have no such problem: they are pinned to the
toolchain the image was built with, which this repo already holds.
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B

DIR32, REL32 = 0x0006, 0x0014
IMAGE_SECTION_CNT_CODE = 0x20


def object_sections(obj):
    """Section headers of a COFF object, plus its symbol-table geometry."""
    count = struct.unpack_from("<H", obj, 2)[0]
    symptr, nsyms = struct.unpack_from("<II", obj, 8)
    out = []
    for index in range(count):
        off = 20 + index * 40
        name = obj[off:off + 8].rstrip(b"\0").decode("latin-1")
        vsize, vaddr, rawsize, rawptr, relptr, lnptr, nrel, nln, flags = \
            struct.unpack_from("<IIIIIIHHI", obj, off + 8)
        out.append(dict(index=index + 1, name=name, rawsize=rawsize, rawptr=rawptr,
                        relptr=relptr, nrel=nrel, flags=flags))
    return out, symptr, nsyms, symptr + nsyms * 18


def external_symbols(obj, symptr, nsyms, strtab):
    """{section index: [external symbol names]} -- the names a row could carry."""
    out = {}
    index = 0
    while index < nsyms:
        entry = symptr + index * 18
        raw = obj[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", raw, 4)[0]
            end = obj.index(b"\0", strtab + offset)
            name = obj[strtab + offset:end].decode("latin-1")
        else:
            name = raw.rstrip(b"\0").decode("latin-1")
        value, section, _type, storage, aux = struct.unpack_from("<IhHBB", obj, entry + 8)
        if storage == 2 and section > 0:
            out.setdefault(section, []).append(name)
        index += 1 + aux
    return out


def longest_clean_run(body, relocation_offsets, minimum):
    """The longest relocation-free run in body, as (offset, bytes), or None.

    Masking is not enough on its own: a needle assembled from several fragments
    would match bytes that never sat next to each other. One contiguous run is
    the only shape whose single occurrence means what it looks like it means.
    """
    best = (0, b"")
    cursor = 0
    for hole in sorted(relocation_offsets) + [len(body)]:
        run = body[cursor:hole]
        if len(run) > len(best[1]):
            best = (cursor, run)
        cursor = hole + 4
    return best if len(best[1]) >= minimum else None


def relocation_offsets(obj, section):
    out = []
    for index in range(section["nrel"]):
        off = section["relptr"] + index * 10
        rva, symbol, kind = struct.unpack_from("<IIH", obj, off)
        if kind in (DIR32, REL32) and rva + 4 <= section["rawsize"]:
            out.append(rva)
    return out


def probe(archive, min_size):
    data, sections = B.exe_image()
    text = next(s for s in sections if s["name"].startswith(".text"))
    image = bytes(B.read_pe_bytes(data, sections, text["rva"], text["size"]))

    placements, multi, absent, skipped = [], 0, 0, 0
    for member, obj in sorted(dict(B.read_archive(archive)).items()):
        try:
            sections_obj, symptr, nsyms, strtab = object_sections(obj)
            names = external_symbols(obj, symptr, nsyms, strtab)
        except Exception:
            skipped += 1
            continue
        for section in sections_obj:
            if not (section["flags"] & IMAGE_SECTION_CNT_CODE):
                continue
            if section["rawsize"] < min_size:
                continue
            body = obj[section["rawptr"]:section["rawptr"] + section["rawsize"]]
            pick = longest_clean_run(body, relocation_offsets(obj, section), min_size)
            if pick is None:
                skipped += 1
                continue
            offset, run = pick
            first = image.find(run)
            if first < 0:
                absent += 1
                continue
            if image.find(run, first + 1) >= 0:
                multi += 1
                continue
            symbol = (names.get(section["index"]) or [None])[0]
            if symbol is None:
                skipped += 1
                continue
            placements.append((section["rawsize"], text["rva"] + first - offset,
                               member, symbol))
    placements.sort(reverse=True)
    return placements, multi, absent, skipped


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("archive", help="repo-relative path to a .lib")
    parser.add_argument("--min-size", type=int, default=48,
                        help="ignore COMDATs (and needles) shorter than this")
    parser.add_argument("--limit", type=int, default=40, help="rows to print")
    parser.add_argument("--csv", help="write a tools/land_wave.py wave here")
    parser.add_argument("--vendored", default=None,
                        help="the `vendored=` note tag; defaults to the archive's stem")
    args = parser.parse_args()

    archive = B.ROOT / args.archive
    placements, multi, absent, skipped = probe(archive, args.min_size)
    print(f"{args.archive}: unique {len(placements)}  multi {multi}  "
          f"absent {absent}  skipped {skipped}")
    print(f"bytes in unique placements: {sum(p[0] for p in placements):,}")
    for size, rva, member, symbol in placements[:args.limit]:
        print(f"  {size:7d} B  {rva:#010x}  {symbol[:70]:70s} {member}")

    if args.csv:
        tag = args.vendored or archive.stem
        out = Path(args.csv)
        out.parent.mkdir(parents=True, exist_ok=True)
        with out.open("w", newline="") as handle:
            handle.write("name,rva,size,source,notes\n")
            for size, rva, member, symbol in placements:
                handle.write(f"{symbol},{rva:#010X},{size},{args.archive},"
                             f"vendored={tag};member={member}\n")
        print(f"wrote {out} -- prove it with: python3 tools/land_wave.py {out}")


if __name__ == "__main__":
    main()
