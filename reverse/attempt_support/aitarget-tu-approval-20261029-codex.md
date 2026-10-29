# AITarget TU approval investigation

Inspected revision: `8f350110e4`, 2026-10-29. The default picker claimed
`file:Code/GameEngine/Source/Common/AITarget.cpp`; the claim was released
after this investigation. No source, name, pin or TU-map change was made.

## Current target facts

The consolidation planner was run for `Code/GameEngine/Source/Common/`.
Its AITarget packet groups three files under the WorldBuilder path
`Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITargetChooser/AITarget.cpp`.
It reports mixed routing, compiler-context differences, duplicate private
views and data ownership prerequisites; this packet grants no placement.

`tu_skeleton.py --plan Code/GameEngine/Source/Common/AITarget.cpp` rebuilds
the stale map in memory and lists ten existing approved rows: seven bodies
at 0x002C590F..0x002C5D8B and three constructor EH rows. Their approval is
provisional. Direct inspection through `tu_map.current_rows` confirms the
picker's nine proposed rows remain proposed:

| RVAs | Current owner |
| --- | --- |
| 0x002C580F, 0x002C5887, 0x002CEF9B | Common/GapBodiesSeat1B.cpp |
| 0x002C5843, 0x002C589B, 0x002C58B3, 0x002C5DA6 | Common/Rva002C589BDtor.cpp |
| 0x002C585A | Common/Rva002C585AAdjust.cpp |
| 0x0050526D | Common/FamilyDeletingDtors8.cpp |

The game string-xref index has no AITarget.cpp path. The Zero Hour reference
has no AITarget source/header filename. The destination's declaration check
passes: all defined functions are already matched. Prior reset-function
failures in `re_attempts.log` are historical: its 92-byte body is now rowed
in Rva002C589BDtor.cpp. This is approval cleanup, not lost coverage.

## Donor evidence and remaining prerequisite

`name_evidence.py --kinds wb,zh,bfme1,string` grades both relevant class
proposals, Rva002C585A -> AITarget and Rva002C589B -> AITarget, as hints:
their pairing score is 1, below the canonical threshold of 4. No canonical
AITarget candidate is served. `wb_show.py 0x002C5C1F` shows the paired
WorldBuilder constructor at 0x00E873F0, an AITarget.cpp:48 assertion and
the AIThreatFinder formatting/allocation sequence. Those donor facts support
investigation; they do not establish a canonical target name or target TU.

The WB path also differs from the current Common destination, so that lead
cannot independently anchor the existing placement. Obtain independent
target path/name evidence before proposing a rename or wider approval.
Reconcile the private views and compiler contexts before any later merge.
The map was not regenerated on disk; no new TU approval, file reduction,
linking gain or census result is claimed.
