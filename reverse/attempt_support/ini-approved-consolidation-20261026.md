# INI approved-TU consolidation

Inspected base: `80732a72b7`, 2026-10-26. The official BFME 1 reference is
`f633d0e97a`; its EA/donor paths are leads, not BFME 2 placement proof.

The served TU was `Code/GameEngine/Source/Common/INI/INI.cpp`. The source,
all eighteen prospective donors, the original-path packet and prior attempts
were read. `name_lane.py consolidate --under Code/GameEngine/Source/Common/INI/`
produced the packet in `build/consolidation/codex-ini-20261026`.
The persisted TU map was stale; `tu_skeleton.py` rebuilt approvals in memory.
Only approved whole donors were moved. No mixed file was split and no
regenerated TU map was committed.

## Separate prerequisite cleanups

- `0019e318cb` removes the unused `_strcat` alternatename from the ASCII reader.
  Its actual body calls `_mbscat`; all three rows and its EH graph stay exact.
  `hatch_counters.py --update` removes one alias occurrence.
- `80732a72b7` corrects the error helper's obsolete const-pointer comment and
  removes its stale unmatched marker. The real `INI*` spelling owns the
  144-byte body at `0x0002C237..0x0002C2C7` and three EH rows, 170 bytes total.
  All four rows and its EH graph stay exact. The owning tool removes one marker.

## Applied merge

The final tool run accepted the existing TU plus these six complete donors:

| Donor basename | Moved rows | Matched bytes |
|---|---:|---:|
| `INISeparatorGetters.cpp` | 4 | 28 |
| `INI_ctor.cpp` | 3 | 192 |
| `INI_getNextAsciiString.cpp` | 3 | 268 |
| `INI_parseBitString8.cpp` | 1 | 62 |
| `INI_parsePositiveNonZeroReal.cpp` | 1 | 83 |
| `INI_parseRGBColor.cpp` | 1 | 165 |

The resulting TU has **52 rows / 3,837 matched bytes**. This moves thirteen
existing rows (798 bytes), rather than recovering new bytes. The first dry run
had also accepted the error-helper file; after the prerequisite cleanups the
final composition rejected that donor's class view. It remains separately owned.

The tool repointed thirteen function rows, ten existing TU-map source fields
and two data-ledger references (the existing bit-string throw-info anchor and
the reader's static buffer). Two inherited `-O1 -arch:SSE` overrides were
transferred to one TU entry, retaining both original row/loss counts.
This is a transfer, not an override retirement or data-ownership gain.
No code/data debt key belonged to an absorbed donor. No absorbed donor had a
canonical-header queue row. The Microsoft-header queue was refreshed by the
merge's owning routine; a separate fresh scan reproduces its destination row
exactly, with all unrelated queue entries preserved.

The first apply exited because the Windows checkout had CRLF in `tu_map.csv`.
Its only partial mutation, thirteen function-row repoints, was restored.
Local map/data/header-queue files were normalized to LF only after proving
their resulting bytes equal the HEAD blobs. The clean rerun completed normally.
No verifier or Git setting was changed.

## Verification and limits

- Before: normal build 56/56 across the eight-source comparison cohort.
  After: normal build 52/52 in the merged TU; the four-row error helper remains
  unchanged. Frozen-file and `check_csv.py` checks pass.
- The current two-source cohort has eight EXACT EH graphs, none baselined.
- Before/after identity scans agree: 175 references, comprising 146 owner,
  nineteen generated alias, eight EH and two certified-fold bindings;
  zero wrong bindings. Data checks report zero findings before and after.
- Before the move, ordinary preview against index `763dc8759f`
  (2026-10-26 00:54) accepts all eight files for 3,894 authored nonpadding bytes.
  INI's prior repair is already present in that baseline; no gain is assigned
  to this consolidation.
- After the move, ordinary preview retains six duplicate and four selected
  findings for the absorbed constructor, getters table and parsers. The
  remaining error helper is clean at 154 authored bytes. The ordinary preview
  is not a fresh census and does not establish post-merge closure. Preserve this
  qualification until current-provider/batch evidence or a census resolves it.
  Read-only index review identifies the six retired donor objects behind the
  duplicates. The four selected findings choose merged INI object 576, while
  `selection.owners` still names only donor objects 636, 640, 645 and 647.
  Ordinary `refresh()` does not retire those objects or transfer the owners.
  This explains the diagnostics without certifying complete current closure.

Logs are under `build/codex-cleanup-20261025/iteration18-*`: `before-build`,
`merged-build`, `identity-before/after` (including TSV snapshots),
`data-before/after`, `eh-after`, `link-before/after`, `merge-lf` and `ms-refresh`.
No LINKED, NOT OURS, full-image or runtime improvement is claimed.

## Remaining composition prerequisites

The final tool leaves twelve whole donors and fourteen mixed files untouched:

- `INI_getNextTokenOrNull`: private `StringBase`, `AsciiString` and vector views
  conflict with the seed's headers; its AsciiString header adoption is queued.
- `INI_readLine` and `INI_parseAsciiStringVectorAppend`: private STL allocator
  and vector definitions conflict with STLport.
- `INI_loadDirectory` and `INI_initFromINIMulti`: the reported trial still
  encounters allocator/vector redefinitions. Reconcile against the new seed
  before treating the first compiler diagnostic as an independent root cause.
- `INI_scanLookupList`: its local exception construction requires a default
  constructor absent from the seed's `INIException` declaration.
- `Rva0002BF4AClear`: its offset-named INI fields/methods do not compose with
  the seed's member view.
- `Rva0002C237Get` and `INI_parseAsciiString`: the rejected composition loses
  the separator getter declarations needed by the emission table.
- `INI_mixerFieldEdit`, `INIParseLineBFME2` and `INI_loadWithParse`: composition
  compiles but does not preserve all matched bytes. No nonmatching source was
  retained and no compiler-flag cause is asserted without a focused trial.

These are merge prerequisites, not missing retail bodies or matching
regressions. Their files and existing rows remain intact for the next pass.
