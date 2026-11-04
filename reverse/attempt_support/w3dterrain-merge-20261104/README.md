# W3DTerrainVisual bounded TU consolidation, 2026-11-04

Inspected base: `1e2125afaae297db81897cd518dffcc3689124da`.
Header prerequisites were independently verified and handed to the publisher in
`f15c898883` and `98cfad72f8` (four header-queue entries retired).
This merge is based on `98cfad72f8`.

`tu_skeleton.py --merge` absorbed `Rva00091DC4Forward.cpp` and
`Rva00092024Clear.cpp` into their approved
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp`.
Source files decrease by two. Six rows / 114 authored bytes remain exact.
All three pre-merge link previews pass (30 + 70 + 14 bytes); the merged
preview passes for the same 114 bytes. Index: 2026-11-04 17:56 at `8c757ea0db`.
This redistributes existing coverage; no new census or real-link gain is claimed.
The normal post-merge build and frozen-file check pass, as does check_csv.

## Ownership, debt and tooling audit

The tool repointed four functions.csv rows, five tu_map source columns and one
name_basis source column. No TU assignment was regenerated. The extra tu_map
source correction at 0x00091DFB points to its existing removeAllBibs owner.
No removed donor owns gate, header, data, identity, hatch, flag or deleted-row
keys. Header transfer and Microsoft-header refresh run inside tu_skeleton;
neither queue needed a change. No aliases, pins or other hatches were removed.

The pending path batch consists solely of these two absorbed donors. Combined
case-insensitive searches cover tools, hooks, workflows, Code and fetched
origin/master. Only generated historical donor comments remain in active
source. Existing name agreements/votes/meanings, link_status census output and
older attempt-support receipts retain their historical paths. The active
name_basis path was repointed. No directory is removed or changes meaning.

External COFF definitions compare before/after: 13 code and 544 data names,
no additions or losses, identical bytes and relocation names for every provider
(including selected inline COMDATs). Uninitialized .bss is compared as zeros.
The tool's census-linked guard passes and the current-object link preview passes.

Pre-existing header-adoption shadow findings were not retired: Matrix3D's
const operator[] has the same 12-byte body before/after and no relocations;
Init's existing g_00DFE7A8 declaration/reference is unchanged. The data and
identity baselines are untouched.

## Remaining work

The seed still pulls Zero Hour's class closure. Composition now specifically
rejects the canonically adopted Init/update sources at SubsystemInterface;
other donors reach Coord2D/Coord3D or RefCountClass redefinitions. Move the
seed off that closure before retrying those donors. Rva00091D61Finish also
fails bytes under the combined flags. Mixed sources were not split. The full
accepted/rejected matrix is in merge-apply.log; rejected sources are unchanged.

The fresh final-TU naming packet covered the two inspected forwarding methods.
A native child proposed valueSource/objectIDSource and the parent reviewed both.
Scoped preview/apply refused both because an unrelated included GameMemory.h
macro declares p (operator-delete macro parameter, lines 641/664/710/722/763).
No naming edits landed; the false rejection is recorded for the tooling lane.
