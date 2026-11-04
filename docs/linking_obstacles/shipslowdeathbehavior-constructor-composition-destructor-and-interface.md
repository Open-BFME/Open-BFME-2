### ShipSlowDeathBehavior constructor composition: destructor and interface providers

Status: Blocked on complete virtual interfaces (destructor identity cleared 2026-11-04).
Updated 2026-10-29; inspected `5eb27ead8e`, index `85f6b7f40c` (15:08).
A real shared-view constructor preserves 9/9 paired rows after correcting
ModuleData's class key. Explicit destructor declarations remove a wrong
implicit UpdateModule destructor, but the constructor then references the
unprovided ShipSlowDeathBehavior destructor and BehaviorModuleInterface::slot0;
ordinary preview loses its 74 authored bytes. The 13-slot primary table and
secondary interfaces need reconciliation with the existing placeholder-owned
destructors at 0x0045EA3F/0x0045ED2F and base 0x0045D39E before composition.
All source trials are restored; 9/9 rows and paired LINKS 907 -> 907 bytes
are reverified. No source move, debt retirement or census gain is claimed.
[Exact trial, verification and next prerequisite](../../reverse/attempt_support/ship-slow-death-constructor-20261029/README.md).

**2026-11-04 (claude-opus-5-5, `70631aa5a7`): destructor identity cleared.**
`rename.py class --fold Rva0045EA3F --into ShipSlowDeathBehavior` renamed
0x0045EA3F/0x0045ED2F to `??1ShipSlowDeathBehavior@@UAE@XZ` and
`??_GShipSlowDeathBehavior@@UAEPAXI@Z`. Target facts: constructor 0x0045E9AA
stores 0x00C423FC at +0, slot 0 is 0x0045ED2F, which calls 0x0045EA3F, whose
first +0 store reinstalls 0x00C423FC. The fold's own check passed against the
shared-view trial object; only the fold landed (15/15, link_check 1,114 -> 1,114).
With the trial patch re-applied on top of the fold, the constructor's only
unresolved name is `?slot0@BehaviorModuleInterface@@UAEXXZ` (74 -> 0 linked).

Still open, and the reason the patch must not land: the view declares one
BehaviorModuleInterface slot where retail's +0x0C table 0x00C42DA8 has the
canonical 47 (`Include/GameLogic/Module/BehaviorModule.h`). Retail overrides
in it: slots 0-6, 8, 10-22 and 24+ are the folded return-0 body 0x000D43D0;
slot 7 is 0x004543A9 and slot 9 is 0x002533D3 (both `lea eax,[ecx-0xC]`
this-adjusting getters, the getDie/getUpdate pattern); slot 23 is 0x003730FC
(same shape). The other tables are 0x00C423E0 (+0x24: beginSlowDeath,
getProbabilityModifier, isDieApplicable, 0x0050B5C6), 0x00C423F0 (+0x10:
update, getDisabledTypesToProcess, 0x0044DF8D), 0x00C42030 (+0x20, folded with
SlowDeathBehavior's: onDie first) and the 13-slot primary 0x00C423FC.
Resolving `slot0` alone would emit a truncated table the constructor then
installs. Next step: adopt the canonical ObjectModule/BehaviorModule/UpdateModule
headers in `ShipSlowDeathBehaviorView.h` with SlowDeathBehavior's overrides at
those slots, keeping 9/9. The base destructor 0x0045D39E restores
SlowDeathBehavior's 0x00C42040 (its constructor 0x0045D4B4 installs it), but
`class --fold Rva0045D39E` needs SlowDeathBehaviorCtor.cpp to emit a named
0x00C42040 table first; it stores tables by data-ledger name today.
