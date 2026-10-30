# GameLogic registerObject module-header adoption

Base: `3d899e6ebe` (after pulling `a008e74ce9`). Source:
`Code/GameEngine/Source/GameLogic/System/GameLogicRegisterObject.cpp`.
Claimed `class:ObjectModule`, the source file, and `0x00242AE9`.

## Target facts

The existing row owns `GameLogic::registerObject` at `0x00242AE9`, 203 bytes.
Its source already documents the update-interface call at secondary slot 9,
the interface-to-module adjustment of -0x10, the primary phase call at +0x30,
and next-frame/index/phase fields at +0x14/+0x18/+0x1C. The registered
ObjectModule header has ten primary slots and size 0x0C. The existing
BehaviorModule header extends that primary table to twelve slots, adds the
secondary interface at +0x0C, and places getUpdate at secondary slot 9.
The ledger owns `?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ`
at `0x0022C4CB` and records primary slot 12.

## Change and inference

Include the existing ObjectModule and BehaviorModule headers and remove the
three private ObjectModule/BehaviorModuleInterface/BehaviorModule definitions.
Declare the protected const enum-returning getUpdatePhase on UpdateModule,
with GameLogic as a friend. Its inherited primary table now supplies the
first twelve slots, instead of pretending they all belong to ObjectModule.
This preserves the existing interface adjustment and data offsets. No shared
header, ledger identity, pin, flag, source path or hatch is changed.

The earlier ObjectModule adoption failures (re_attempts.log) tried removing
the private base without supplying these derived slots. The separate queued
GameLogic adoption still needs its object-list tail, phase/sleeping vectors
and addObjectToLookupTable in the canonical GameLogic header; it remains open.
No donor path or complete recovered class layout is claimed.

## Verification and limits

- `./build.sh Code/GameEngine/Source/GameLogic/System/GameLogicRegisterObject.cpp`:
  1/1 rows exact, before and after, including the final method signature.
- `find_declared_unmatched.py` reports all defined functions already matched.
- All five external COMDAT fingerprints (bytes and relocation identities)
  are identical before/after. No external definition is added or removed;
  sorted external/weak symbol records are identical too.
- The owning `header_adopt_lane.py accept --class ObjectModule` passes and
  retires exactly one header queue row.
- Strict `link_check.py --prepare-current` verifies the source with a reusable
  receipt. No census/index/status update is performed.
- Ordinary preview against census index `85f6b7f40c` retains LINKS,
  203 -> 203 authored bytes. No census gain is claimed.
- The staged-tree batch audit is INCONCLUSIVE: the index predates the base
  and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Carry that consumer and this provider into the next scheduled
  census; complete consumer selection/loss verification remains open.

Scratch object snapshots and comparison: `build/codex-register-object/`.
