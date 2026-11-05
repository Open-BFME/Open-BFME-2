# FESL blobservice: diagnostic header accepted; merge remains blocked

Inspected revision: `aa9fa2e00ffed28944ce224dfa91c1e102271ab9`.
Scope: `Code/Libraries/Source/Fesl/blobservice.cpp` and its three clean donors.

## Accepted change

The TU's private four-slot `Rva007EB810Diag` declaration is replaced by
`Code/GameEngine/Include/GameNetwork/Rva007EB810Diag.h`. Its documented target
table places the cdecl variadic `log(unsigned int, const char *, ...)` in slot 2;
the private view called that slot `assertValue(void *, const char *)`.
`BlobService::fetchContent` reaches this call only when `content == 0`, so the
explicit unsigned conversion passes a zero buffer requirement. The format
literal remains `--- out of memory\n`. The canonical slot-3 `fail` result is
ignored, as before. No shared header, provider, symbol or compiler flag changed.

Verification:

- `./build.sh Code/Libraries/Source/Fesl/blobservice.cpp`: 21/21 matched;
  string checks pass (four literals and one empty-string reference), imports
  and floating-point checks pass.
- `find_declared_unmatched.py`: all defined functions already matched; the
  existing note reports 21 matched rows and two unclaimed definitions.
- `header_adopt_lane.py accept --class Rva007EB810Diag
  Code/Libraries/Source/Fesl/blobservice.cpp`: PASS; owning tool retires one
  row from `reverse/header_queue.tsv`.
- `link_check.py Code/Libraries/Source/Fesl/blobservice.cpp`: LINKS,
  1,029 -> 1,029 census-linked bytes, using the 2026-11-05 05:17 census
  at `c95fcfcfcd`. This is a current-object preview, not a new census.

## Consolidation investigation

The supported planner ran under `Code/Libraries/Source/Fesl/`; it found no
additional routing evidence. `tu_skeleton.py --plan` rebuilds the stale map
in memory: 26 approved rows, four clean files including the seed, eight mixed
files, zero refused files. No map or source-path move is committed.

The baseline dry run accepted zero of three donors:

- `Rva007F05A0BlobCursor.cpp`: C2039, `m_blobId` absent from the seed view.
- `V2FeslBlobRecordPopulate.cpp`: C2511, populated constructor absent from
  the seed view.
- `Rva007F1220BlobWriter.cpp`: byte mismatch.

`tu_views.py --dry-run` identifies the underlying record conflict: seed
`m_008` occupies +8..+12 while donor `m_blobId` occupies +8..+16. The seed
also has separately named volatile words and embedded FeslString objects;
the other views use 64-bit IDs and Date objects. Matching storage extents
alone would not establish their identities or a safe unified declaration.

For the writer, a tested hypothesis was that visible message accessor bodies
changed its call context. Marking `reset`, `addInt` and `addString` noinline
preserved all 21 seed rows and its 1,029 linked bytes, but the merge still
rejected the writer. A further trial replaced `/MD` with `/GS`, retaining
`/DNDEBUG /EHs-c-`: the seed still matched 21/21. A scratch composition through
`tu_skeleton.Verifier` restored the writer's security-cookie shape and static
CRT calls but still differed in scheduling and loop padding. Removing the
remaining seed flags lost its scalar-deleting destructor row at 0x0065D810
(the compiled body called the derived destructor instead of installing the
retail vptr and calling the base). These are trial observations, not a proof
that one compiler option or inlining alone explains the remaining difference.

All compiler/declaration trials were restored before the accepted header edit.
No failed reconstruction remains in Code/, no debt is retired for the merge,
and no donor is deleted. Next: establish one byte-preserving BlobRecord view,
or resolve the writer's remaining caller context while preserving the seed's
deleting-destructor shape. Do not repeat the unchanged bulk merge first.
