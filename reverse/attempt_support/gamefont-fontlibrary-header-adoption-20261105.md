# GameFont consolidation prerequisite: canonical FontLibrary adoption

Inspected revision: `0084010ea0`; 2026-11-05.

The picker claimed GameFont.cpp and its four eligible FontLibrary donors.
The GUI consolidation planner reported the original-path evidence, mixed
owners and declaration prerequisites. Both the initial merge dry run and
the existing view reconciler accepted no donors. The reconciler leaves the
registered FontLibrary/GameFont classes to their header lane and reports
Rva002186EB's fake vtable overlapping its seed's canonical base.

## Applied prerequisite

GameFont.cpp, FontLibraryFindRecord.cpp and
FontLibraryParseDefaultSettings.cpp now include the existing canonical
GameClient/FontLibrary.h instead of defining private FontLibrary bodies.
The header remains unchanged. Its documented storage at +0x14/+0x20 is
accessed through the same local map/tree types used before this edit.
Those casts preserve the existing template identities; they do not establish
new original names or recover the complete map types.

The parser's map cast must stay in its subscript expression: a separate
local map reference moved `add ecx, 14h` before the argument push and failed
the byte check. The final inline expression matches retail.

## Verification

- Normal scoped builds before and after: 68/68 function rows exact
  (58 GameFont, five lookup, five parser); parser data row also passes.
- Declared-unmatched check passes all three sources. GameFont's existing
  absent-from-retail definition remains reported as an informational note.
- `header_adopt_lane.py accept --class FontLibrary` passes each of the
  three sources and retires exactly their three header-queue rows.
- Combined ordinary link preview: all three LINKS; 4,278 -> 4,278 authored
  bytes, against census 2026-11-05 05:17 at `c95fcfcfcd`. Per source:
  GameFont 3,491, lookup 441, parser 346. The seed's unreferenced COMDAT
  diagnostics remain informational. This is a prediction preserving existing
  coverage, not a new census or real-link result.
- `check_csv.py` and `git diff --check` pass. No source paths, ledger owners,
  pins, aliases, hatch counts or shared headers change.

## Remaining consolidation work

The final normal `tu_skeleton.py --merge .../GameFont.cpp --dry-run`
still accepts no donors:

- FontLibraryFindRecord.cpp now compiles in the composition but fails bytes.
  Next: identify the specific differing rows and compiler context; the dry
  run alone does not prove which flag or code shape causes the mismatch.
- FontLibraryParseDefaultSettings.cpp advances past the missing FontLibrary
  method declaration, then fails on private Rva002186EB::sizes and its
  incompatible container interface. Reconcile the Rva002186EB views first.
- FontLibraryCtor.cpp and FontLibraryFontList.cpp retain duplicate private
  STL declarations and their unadopted member-lifetime views. Their remaining
  header-queue rows are preserved; constructor/destructor storage adaptation
  needs separate byte and EH evidence.

No source-file reduction, merge acceptance, link gain or runtime clearance
is claimed. The original mixed owners remain outside this batch.
