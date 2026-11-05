# Toggle-mounted TU: Thing adoption and remaining lifetime barrier

Date: 2026-11-05. Inspected revision: `f0ec19b359`.
Worker: `yasinschroeder-codex5`; model: `gpt-6.1-sol`.

## Verified cleanup

`ToggleMountedSpecialAbilityUpdate.cpp` now explicitly includes the canonical
`Code/GameEngine/Source/Common/Thing/thing.h`. The TU already gets that definition
through Drawable.h; its only local Thing declaration is a forward declaration.
The direct include satisfies the header lane's dependency requirement.

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdate.cpp`:
  18/18 matched rows; four funclet labels verified against parent EH data;
  two string and two floating literals verified.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class Thing` for this TU: PASS; exactly one
  header-queue row retired by the owning tool.
- Current-object `link_check.py`: LINKS, 1,559 authored bytes unchanged, using
  the census index from 2026-11-05 05:17 at `c95fcfcfcd`.

This is header debt reduction only. No source paths or function rows moved;
no new linked-byte headline or real-link result is claimed.

## Consolidation evidence and trials

The subsystem planner completed for `Code/GameEngine/Source/GameLogic/Object/Update/`.
Its WorldBuilder Object/SpecialPower path alternative is donor evidence, not
permission to move the TU. The committed TU map is stale; tu_skeleton rebuilt
assignments in memory. Its current plan has 21 approved rows and two unmixed
remaining donors (ModuleData constructor and deleting destructor). The instance
constructor discussed in the older LINK-251 evidence is already in the TU.
The mixed Lerp and ModuleUpdateDtors sources remain outside this trial.

A current unmodified merge dry-run accepts neither donor. The constructor fails
C2600: the selected ModuleData view does not declare its constructor. The
ModuleData declarations also disagree on base identity, member lifetime and
`novtable`; `tu_views --dry-run` reports the declspec conflict.

Two bounded tests isolated the deleting-destructor barrier:

1. Add `__declspec(noinline)` to the destination ModuleData destructor.
   The destination still passes 18/18 rows, but merge dry-run still accepts no
   donors. A scratch composition through `tu_skeleton.compose` and its isolated
   `Verifier` matches all 18 destination rows and lacks the required external
   `??_GToggleMountedSpecialAbilityUpdateModuleData@@UAEPAXI@Z`. Thus the generic
   `bytes` rejection in this composition is a missing deleting-destructor body,
   not evidence that inlining changed that body's instructions.
2. Also remove `novtable` from the destination ModuleData declaration.
   The normal build fails its destructor at RVA `0x004AE10B`: after the first
   17 bytes it emits an extra six-byte `mov [esi], <vtable>` store before the
   retail `lea ecx,[esi+0xD4]`. Retail has no such store. The other destination
   rows pass, but this is not a matching reconstruction.

Both experiments were reverted. No noinline annotation, changed class lifetime
view or failed composition remains in Code/. No escape hatch was added or
removed, and no alias was changed.

Next work must reconcile the constructor/deleting-destructor emission with the
retail destructor's missing vptr store and its existing EH cleanup ownership.
Merely preventing destructor inlining does not resolve it. The constructor's
canonical base/raw-storage view must also be reconciled before merging it.
The consolidation remains blocked; census and real-link confirmation are outside
this pass.
