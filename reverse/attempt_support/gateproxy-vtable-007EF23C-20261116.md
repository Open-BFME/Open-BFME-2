# GateProxyBehavior ProxyBaseD table 0x007EF23C

Served 2026-11-16 from `reverse/vtable_bridge_queue.tsv` (`??_7GateProxyBehavior@@6BProxyBaseD@@@`,
12 bytes, source `Code/GameEngine/Source/GameLogic/Object/Behavior/GateProxyBehaviorCtor.cpp`).

## Verdict

Blocked on the canonical UpdateModule/BehaviorModule class reconciliation, not a local slot edit.

`GateProxyBehaviorCtor.cpp` declares a placeholder MI chain
`GateOpenAndCloseBehavior : ProxyBaseA, ProxyBaseB, ProxyBaseC, ProxyBaseD` where `ProxyBaseD` has
only a virtual destructor, so the emitted +0x14 table holds a deleting destructor at slot 0. Retail's
three slots at 0x007EF23C are:

- 0x004A6563, 6-byte `mov eax, 3FFFFFFF; ret` update body (rowed as `?Rva004A6563Get@@YAHXZ` and as
  the AssistedTargetingUpdate/DefaultProductionExitUpdate ICF twins);
- 0x004A4580, 27-byte mask body (rowed as `?rva004A4580@Rva004A4580@@QAEPAXPAX@Z`);
- 0x0044DF8D, 18-byte `UpdateModuleInterface` slot 2 (rowed in `UpdateModuleSetWakeFrame.cpp`).

That is the `UpdateModuleInterface` trio (`update`, disabled-mask getter, `rva0044DF8D`) from the
canonical `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`, not a base with a virtual
destructor. The constructor's fourth base therefore has to become that interface (and the class
has to carry UpdateModule's real layout), which is the class recovery the `UpdateModule` header row
already tracks.

## Prerequisite evidence

`tools/header_adopt_lane.py run --class UpdateModule --dry-run` and
`--class BehaviorModuleInterface --dry-run` both report 0 passing units (23/23 and 23/23 fail;
bytes/callee identity, missing members and field renames). The bridge row's `source_slot_mismatches`
are the expected symptom of the missing interface, not a name that can be added to the placeholder.
No source change was made.
