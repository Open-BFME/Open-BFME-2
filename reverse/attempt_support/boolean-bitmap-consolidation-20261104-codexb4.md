# BooleanBitmapSet field-initializer consolidation

Base before merge: `6804530759`. The supported `tu_skeleton.py --merge`
absorbs `Code/GameEngine/Source/Common/Rva00531196Finish.cpp` into its
current-map approved, provisional TU, `Code/GameEngine/Source/Common/BooleanBitmapSet.cpp`.
The provisional grouping does not prove the retail filename or the initializer's
original owning type. Source files decrease by one; matched coverage is retained.

Prerequisite: the separate CRT declaration commit replaces the donor's
void-return memset declaration with `<string.h>` and `#pragma function(memset)`.
Its 159-byte row remains exact; `ms_header_audit.py scan ... --write-queue`
clears the donor's single conflicting ABI queue row. Ordinary link preview
preserves its 159 linking bytes. No data/identity/header key is retired by this
merge.

Verification of composition:

- Initial Common consolidation planner packet supplies investigation context;
  routing approval comes from the map rebuilt in memory by tu_skeleton.
- Dry run and application accept the seed and field initializer (12 rows).
  Rva00531132.cpp is rejected for bytes and left unchanged; the three mixed
  files remain separate. No rejected source edit is retained.
- Final `./build.sh` passes all 12 rows; string, float and named-import checks
  pass. `find_declared_unmatched.py` and `check_csv.py` pass.
- The merge link guard accepts all three census-linked participants.
  Current ordinary preview against the 2026-11-04 20:47 census at f12552d0a7
  predicts BooleanBitmapSet LINKS 316 -> 475 bytes and unchanged Rva00531132
  LINKS 100 -> 100. The extra 159 bytes moved from the deleted donor; this
  is preserved coverage, not a new census gain or a real-link measurement.
- Existing `cell` and `bridge` names travel through name_basis; the original
  semantic roles of the packed fields and remaining byte temporaries stay unknown.

The path-consumer audit covers both deletions in the whole outgoing range
(origin/master through the staged merge): Rva004EE15BFwd.cpp ->
LivingWorldScoreKeeper.cpp (previous audit in
scorekeeper-transfer-consolidation-20261104-codexb4.md), and
Rva00531196Finish.cpp -> BooleanBitmapSet.cpp. Combined searches find no active
hard-coded consumer in tools, hooks, workflows, source/header includes or
configuration. The tool repoints functions.csv, tu_map.csv's source column
(without regenerating the map) and two name_basis source cells. Active data,
body-owner, flag, debt, hatch and header registries have no deleted-source key.
The destination's mentions in another class's pending dependency diagnostic
remain valid. A scoped Microsoft-header rescan finds the merged TU clean.
Historical name votes/agreement rows, link_status.csv and attempt artifacts,
and the source provenance comment intentionally retain old paths. No pins,
linker aliases or hatches are removed. Diff whitespace checks pass.

Remaining work: investigate Rva00531132's composition byte mismatch before
absorbing it; the mixed donors still require independent approved splits.
