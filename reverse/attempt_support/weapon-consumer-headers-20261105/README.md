# Weapon consumer header adoption, 2026-11-05

Inspected source: `d918144991734c055edf217c70261f4f9387e6f1`.
Provider index: local census `2026-11-05 15:19 at f44cbcf5b0`, refreshed with
`python3 tools/link_check.py --fetch-index` before the pass.

Six private Weapon declarations are replaced by the existing canonical
`Code/GameEngine/Include/GameLogic/Weapon.h`. The consumers cast stored integer
IDs to ObjectID at lookup calls, use the canonical fields at +4/+8/+18/+5C,
and retain the original const-Object attack-range overload explicitly. The
opaque WeaponTemplate byte-field view is retained by casting m_template at
its use. These are target offsets and existing call identities, not donor
layout claims. The shared header is unchanged.

## Scope

- `Code/GameEngine/Source/GameLogic/Object/Weapon_getRemainingAmmo.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Weapon_prepareProjectileStreamForFiring.cpp`
- `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderAttackView.cpp`
- `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderFootprintAttackRangeQuery.cpp`
- `Code/GameEngine/Source/GameLogic/Pathfinder/rva002F14F9Rva002F14F9Farm.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherAnimationDebuggingInfo.cpp`

## Verification

- `find_declared_unmatched.py --fail` passed before and after the edits.
- `./build.sh` over these six sources passes 19/19 functions, two data rows,
  eight funclet pins, all string/float/import references; see [build.log](build.log).
- Original objects were saved after the passing baseline build. Comparing
  `class_cleanup.runtime_graph` before/after with `same_runtime` passes for
  all six, including non-debug section bytes, external definitions, weak
  defaults and relocation bindings. No definition is removed or added; see
  [object-comparison.json](object-comparison.json). The removed private class
  declarations contained no inline definitions. This preserves their link-wide
  provider behavior as well as their rowed bodies.
- One `header_adopt_lane.py accept --class Weapon` invocation over the whole
  six-source batch passes and retires six queue rows. Its current-input link
  preview guard preserves each unit's census-linked bytes; see [accept.log](accept.log).

This is header/debt cleanup. No new census gain, real-link or runtime result is
claimed. Other Weapon queue rows remain outside this accepted scope.
