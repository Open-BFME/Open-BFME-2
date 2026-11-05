# LivingWorldCampaignManager header adoption (2026-11-05)

Inspected base: `4b347686ad1fc89307c84e1838401326691cef50`.
Scope: the five LivingWorldCampaignManager rows served from
`reverse/header_queue.tsv` (all private views remaining in that class queue).

## Change and evidence

Use the existing canonical header
`Code/GameEngine/Include/Common/LivingWorldCampaignManager.h` in:

- `Code/GameEngine/Source/Common/Rva002B47B1Get.cpp`
- `Code/GameEngine/Source/Common/Rva003B8BAALookup.cpp`
- `Code/GameEngine/Source/Common/Rva003B92B9Filter.cpp`
- `Code/GameEngine/Source/Common/Rva003B930DFilter.cpp`
- `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignManager.cpp`

Target facts: the canonical header documents the retail +0x10 index,
+0x14/+0x18/+0x1C vector storage, and +0x2C/+0x2D flags. Its pointer
storage remains untyped. Consumers cast the pointer entries or vector storage
to their existing element views. No donor identity or new layout is inferred.
TheCampaignManager retains its existing ledger symbol and sole definition.
No header, ledger identity, compiler flags, source paths or hatches change.

The automatic adopter could not reconcile the 12-byte vector fields with the
canonical pointer fields, and its getter trial failed data-row verification.
Manual adoption preserves that global's original forward-declared type.
For the two filters, a local reference to the typed vector changed register
allocation and load order; direct casts at each use match the retail bodies.
The canonical name lookup's nothrow declaration preserves the matched callers.

## Verification

- `find_declared_unmatched.py` on all five sources: all defined functions matched,
  before and after the edit.
- `./build.sh` on the getter: 1/1 function and 1/1 data row byte-verified.
- `./build.sh` on the other four sources: 18/20 functions initially matched;
  the final direct-cast filter trial passed all three rows in those two units.
  The later acceptance command byte-verifies the complete final cohort.
- `header_adopt_lane.py accept --class LivingWorldCampaignManager` with all five
  sources: PASS for every source; retired exactly five header queue rows.
  This performs the owning lane's structural, byte and link-preservation checks.
- `link_check.py` with all five final sources: 5/5 link cleanly;
  census-linked bytes preserved at 1,173 -> 1,173 (individual scopes:
  18, 129, 84, 132, 810). Index: census 2026-11-05 05:17 at `c95fcfcfcd`.
- `git diff --check`: clean.

This is header debt retirement, not new linked coverage or a new census.
The separate LivingWorldRegionManager queue row in the campaign-manager TU
remains outstanding and is outside this class adoption.
