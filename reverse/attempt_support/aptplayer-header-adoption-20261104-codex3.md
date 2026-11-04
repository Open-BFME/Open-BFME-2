# AptPlayer consumer header adoption

Inspected base: `4ee23edebd`. Link preview index: `f6d845ecd4`, published
2026-11-04 13:15. No census or runtime result is claimed.

`InGameNotificationType.cpp` now includes the existing `AptPlayerClass.h`
instead of declaring sixteen virtual slots privately. The header's slot 15
returns the neutral incomplete `ScalePair` type. This consumer retains its
existing two-float `AptScale` view and casts the returned pointer before reading
the two floats; no original name or broader layout is inferred.

Verification:

- `header_adopt_lane.py adopt --class AptPlayer --header
  Code/Libraries/Source/Apt/AptPlayerClass.h --apply` passes for this unit.
- `./build.sh Code/GameEngine/Source/GameClient/GUI/InGame/InGameNotificationType.cpp`:
  11/11 matched, including the parent handler and three renumbered funclet
  labels verified through their EH data. The declared-unmatched check passes.
- `header_adopt_lane.py accept --class AptPlayer` passes and retires the unit's
  queue row. It also passes for four queued consumers that already include the
  header: `AptParameterParsing.cpp`, `AptSpellStore.cpp`,
  `AptMainMenuCallbacks.cpp`, and `AptMainMenuCallbacks_ExitGame.cpp`.
  The tool retires those four rows without source changes. Acceptance checks
  current byte verification, canonical-header use and link preservation.

Five header-queue rows are retired through the owning tool. Other AptPlayer
queue entries remain; their container layouts, nested records and include
conflicts were not changed. The canonical header is unchanged.
