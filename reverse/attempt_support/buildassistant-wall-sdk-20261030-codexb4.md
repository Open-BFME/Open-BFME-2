# BuildAssistant wall-placement SDK constants

Inspected base: `0ec9813085c476cc6e12fe3231142d46393bbf73`, 2026-10-30.

`Common/System/BuildAssistantWallLocations.cpp` locally defined `FALSE` and
`TRUE`. The owning Microsoft-header auditor identifies both as identical to
the Platform SDK's WinDef.h definitions. The unit now opts into that SDK and
includes `<windows.h>` before its other headers, with `WIN32_LEAN_AND_MEAN`
and `NOMINMAX`. The two local definitions are removed. No API call, class
view, body identity or source path changes.

The old queue record listed three definitions, including an already absent
local `NULL`. The owning `ms_header_audit.scan_files` and `refresh_queue`
remove only this file's record. The fresh scan has no local copied definition;
its one local occurrence is the supported `NOMINMAX` configuration input.
The 208 include-closure findings remain, including WWLib's allocation and
visualc layers and declarations in the included SDK graph. This is local
queue cleanup, not full header-closure clearance. The scan receipt is scratch
`build/walllocations-msheaders-codexb4/scan.json`.

Verification:

- Before and after `./build.sh` pass all five function rows, three funclet
  bindings and nine float literals. Declared-unmatched checks pass.
- `link_check.py --prepare-current` passes with a strict reusable receipt.
- `eh_verify.py` reports EXACT 1, no baseline exception.
- All 59 external COMDAT fingerprints are identical before/after, using
  `link_census._comdat_sections`. The complete `object_symbols` result also
  stays identical: 59 definitions, 35 references, two weak bindings and seven
  alternate bindings. No COMDAT is added or removed.
- Ordinary preview retains LINKS and 2,218 authored bytes against the index
  at `12b9e7a7c0` (2026-10-30 10:11 UTC).
- The staged-tree batch audit is INCONCLUSIVE: the index predates the base
  and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Full consumer selection/loss verification remains open; carry the
  wall-placement provider and affected consumers into the next scheduled
  census. No census gain or runtime claim is made.

Earlier selections were inspected without source edits and released:
MapUtil's supply/tech data keys are already fixed but retirement still needs
the documented dimension-ownership/codegen reconciliation (LINK-005).
UserInputTranslator's sole proposed main-code placement has only name and
WorldBuilder hints; the fresh consolidation packet supplies no target TU
approval. No new inference or unchanged source trial was recorded as progress.
