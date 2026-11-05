# BooleanBitmapSet consolidation, 2026-11-05

Destination: `Code/GameEngine/Source/Common/BooleanBitmapSet.cpp`.
Inspected source revision: `df3e58aa88`; fetched origin through `18020d3616`.

## Placement and result

The Common-source `name_lane.py consolidate` packet was checked current before
applying the merge. It supplies investigation leads, not original-path proof.
`tu_skeleton.py` rebuilt the stale TU map in memory and accepted the existing
provisional BooleanBitmapSet assignment. The WorldBuilder pathfinder hint and
the BFME 1 bounds-check donor remain leads; neither proves the original owner
or names of the two moved methods.

The supported merge absorbed `Common/Rva00531132.cpp`, moving both its rows
(0x00531132, 77 bytes; 0x0053117F, 23 bytes) and deleting one source file.
The destination now owns 14 matched rows totaling 575 bytes. Only two source
cells changed in each of `functions.csv` and `tu_map.csv`; the committed map
was not regenerated. Existing method names, integer views and donor-evidence
comments are preserved.

Three approved rows remain in mixed files: DoEnum in
`GameLogic/Pathfinder/PathfindZoneManagerXfer.cpp`, 0x00531101 in
`Common/GapBodiesSeat1C.cpp`, and 0x00531121 in `Common/GapBodiesGE28.cpp`.
Those files were untouched. Recovering their other TU ownership and performing
verified splits remain prerequisites for further consolidation here.

## Verification

- `./build.sh` and the supported strict-receipt preparation: 14/14 exact;
  string, float and import checks pass.
- Frozen-file check: every defined function is matched. TU-ownership and
  staged whitespace checks pass. `check_csv.py` preserves 99,463 function,
  9,316 symbol and 2,268 data-row entries.
- Code identity: zero new findings in shadow. Data identity: zero findings;
  the enforced converged check judges all 11 addresses with no second name.
- EH verification: no EH-bearing rows and no missing object.
- The merge's link guard accepted both previously census-linked units with
  the donor removed. With a strict current destination receipt, `link_check`
  predicts LINKS for 575 bytes against the 2026-11-05 05:17 index at
  `c95fcfcfcd`. Its displayed 475-to-575 change is the destination absorbing
  the donor's existing 100 bytes, not a gain in census-linked coverage.

## Registers and path consumers

The outgoing path audit covers the inherited AIEconomyBuilder merge
(`8ad61b7f4b..df3e58aa88`) and this staged merge, against the fetched origin
above. Its three absorbed paths are `Common/Rva004EA420Init.cpp`,
`GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderDoXferFarmLibrary.cpp`
and `Common/Rva00531132.cpp`. Combined basename searches across tracked tools,
hooks, workflows, sources, configuration, documentation and registers found
no active consumer of those deleted filenames. Remaining mentions are source
provenance comments, historical attempt evidence/logs and the recorded census
`link_status.csv` snapshot. They remain intentionally.

No identity, data, header, Microsoft-header or hatch debt is keyed to the new
donor. The existing CarryoverUnit header-queue dependency on BooleanBitmapSet
remains at its current path. No debt is retired, no alias pragma is removed,
and all active moved rows resolve to the tracked destination. The inherited
AIEconomyBuilder register transfer retains its existing audit and trailer.

## Wider binding check still needs census confirmation

The batch audit used the staged tree, fork base `8ad61b7f4b`, and the older
`c95fcfcfcd` census index. Its first pass lacked current receipts for
`Common/Rva005312BEClear.cpp`, the inherited AIEconomyBuilder destination and
`GameLogic/SkirmishAI/SkirmishAIManager.cpp`. After claiming those scopes,
bounded `link_check.py --prepare-current` verified all 39 rows and supplied
strict reusable receipts without source edits or census publication.

The justified second pass returned exit 2: INCONCLUSIVE baseline, then
`affected consumer lacks current receipt:
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. It stopped before
the final selected-provider/lost-byte verdict. The scoped merge guard and
575-byte preview pass, but wider current consumer bindings remain unverified.
Carry this batch and that consumer into the next scheduled census/current
receipt audit under LINK-001; no real-link or census gain is claimed.
