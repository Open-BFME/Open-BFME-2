# StateMachine header adoption (2026-11-05, codexb2)

Base: `6156dcf7a7df46896338f57de9118e59c27a067c`. Claimed `class:StateMachine` and the
Common/AttackPositionHordeStateMachine.cpp file scope.

Five units now include the existing Common/StateMachineClass.h instead of
private StateMachine declarations:

- `Code/GameEngine/Source/Common/AttackPositionHordeStateMachine.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AttackPositionHordeStateMachine.cpp`
- `Code/GameEngine/Source/GameLogic/AI/BackAwayAndCowerStateMachine.cpp`
- `Code/GameEngine/Source/GameLogic/AI/Rva003435FBStates.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateGuardObject.cpp`

The units retain 16 matched rows / 1,100 bytes. No paths, row identities,
shared headers, pins or aliases change. The supported
`header_adopt_lane.py accept --class StateMachine` pass test accepts all five
and retires their five header-queue entries itself.

## Byte and link evidence

- The automatic adoption trial tested the picker's 25 units; three byte-passed.
  The retained automatic units are BackAwayAndCowerStateMachine,
  Rva003435FBStates and AttackPositionHordeStateMachine (the latter needs the
  paired destructor adoption below).
- The guard-object unit's local enum StateID conflicts with the canonical
  unsigned typedef. Keeping its one guard-state constant in an anonymous enum
  permits canonical adoption; the 115-byte body still matches.
- The Common AttackPositionHorde destructor reads the Object pointer at +0x14.
  The canonical header identifies this base field as m_owner. Removing the
  derived padding/pointer view and using m_owner preserves both its 77-byte
  destructor and 28-byte deleting destructor (`./build.sh`, 2/2).
- Frozen-source checks pass for all five; `check_csv.py` and `git diff --check`
  pass. Final acceptance byte-verifies every unit.

A fresh-provider preview before the paired destructor repair
(`link_check.py --refresh`, 811.2 seconds) restored/recompiled 11,374 stale
ledger objects, refreshed 15 other rebuilt providers, and preserved
BackAwayAndCower 223 -> 223 B and Rva003435FBStates 296 -> 296 B. The constructor
alone lost AttackPositionHorde's 305 B to a differing COMDAT table.

Adopting its destructor too initially preserved the destructor's 105 B but
still lost the constructor. In that source, object.h selected Snapshot before
StateMachineClass.h could select BFME_SNAPSHOT_NAME_SLOT. The shim's default
crc slot and the later GetSnapshotName declaration therefore produced a
changed table surface. Including StateMachineClass.h before object.h fixes the
per-unit slot selection; no shim change is required.

Final current-object preview (`link_check.py` with all five sources, 5.2s):

| Unit | Census-linked bytes | Predicted bytes |
| --- | ---: | ---: |
| Common/AttackPositionHordeStateMachine | 105 | 105 |
| AI/AttackPositionHordeStateMachine | 305 | 305 |
| AI/BackAwayAndCowerStateMachine | 223 | 223 |
| AI/Rva003435FBStates | 296 | 296 |
| Update/AIUpdateInterfacePrivateGuardObject | 115 | 115 |
| Total | 1,044 | 1,044 |

Census index: 2026-11-05 05:17 at c95fcfcfcd. These are predictions for the
listed units, not a new census or proof of retail vtable/runtime correctness.
The ledger total includes funclets not charged by that census preview.

## Remaining work

The other automatic trials are restored. The AIUpdateInterfacePrivateCommands
retry is also restored: after reconciling StateID, the tool refuses its
28-byte StateMachine::m_unmodelled_08 view against the canonical layout.
Other served units remain blocked on enum/type collisions, abstract State
views, unproven field ownership, the state-map view, private helpers or
constructor code generation. Existing LINK-177 items outside this five-unit
scope remain open. Local full logs: build/state-header-adopt.log,
build/state-header-link.log, build/state-header-final-link2.log and
build/state-header-final-accept.log.
