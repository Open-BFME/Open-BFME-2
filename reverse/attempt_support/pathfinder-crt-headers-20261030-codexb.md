# Pathfinder CRT header declarations

Base: `5b3d2ce4c47ac3a16d6fc1809103ddc3f4d39160`. The Microsoft-header
picker claimed `Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`.

The unit takes `fabs` and `floor` from `<math.h>`, `memset` from its existing
`<cstring>`, and `fprintf`/`FILE` from `<stdio.h>`. A scoped supported
`_CRTIMP` configuration preserves the direct `_fprintf` binding and restores
the imported configuration for other headers. The invented log-file forward
declaration and casts are replaced with the CRT type. No shared header,
source path, function/data row, pin or runtime behavior changes.

Target/object facts: the original object references `_fprintf` directly and
`__imp__floor` through the IAT; `_floorf` is storage-class 3 (local). Its STL
storage references `?Rva00030830FreeAllocation@@YAXPAX@Z`. These are existing
binding facts, not new name or donor-layout claims. No donor repair is used.

Verification:

- Normal builds before and after pass 120/120 function rows and one owned data
  row, 126 string literals plus four empty-string refs, 94 floating literals
  and 18 named imports. The frozen-source check passes.
- All 580 external COMDAT fingerprints and sizes, 782 external symbol records
  (names, defined/undefined status, storage class and offsets), and relocation
  reference roots/edges are identical before and after.
- All 14 EH graphs are EXACT. Existing funclet rows verify through their
  parent graphs despite compiler-label renumbering.
- Strict current preparation passes and records a reusable provider receipt.
  Ordinary preview retains LINKS, 50,353 -> 50,353 authored bytes, against
  index `12b9e7a7c0` (2026-10-30 10:11). The index fetch confirms that is also
  the available published index.
- The owning Microsoft-header scanner refreshes only this source's queue
  record: five actionable local definitions become two (`free` and `floorf`).
  Four handwritten CRT declarations are removed; the existing local `floorf`
  is now counted in the refreshed record. This is partial cleanup, not queue
  or class/header closure.
- The allocator macro must retain the game free route above. The static
  `floorf` declaration preserves the existing LINK-133 repair documented in
  `docs/linking_obstacles.md` (Pathfinder consumer subset); removing it would
  expose the header helper again. Neither is replaced blindly with a CRT
  binding. Existing class and generated-unwind prerequisites remain separate.
- The staged-tree batch audit exits 2, INCONCLUSIVE: the index predates the
  outgoing base, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Full affected-consumer selection/loss checks remain unverified.
  Carry this provider and wider consumers into the next scheduled census.
  No measured linking or image-ownership gain is claimed.

Scratch evidence: `build/pathfinder-msheaders-codexb/` contains original
source/object, final build and preparation logs, comparison facts, EH results,
ordinary previews and staged-tree batch-audit output. The original build log
is `build/pathfinder-msheaders-before.log`.
