# AIGateUpdate Snapshot selection and stale adoption debt

Base: `48e8ebf76c`; 2026-11-05, seat codexb5.

The approved-TU merge dry run accepts no donor. The seed reads ObjectModule.h
before BehaviorModule.h/UpdateModule.h can select BFME2's Snapshot name slot.
Adding the existing BFME_SNAPSHOT_NAME_SLOT selector before that first include
removes the merged destructor's unresolved UpdateModule::crc reference. It does
not yet clear the separate AIGateUpdate primary-vtable mismatch.

Verification: the normal builder preserves 8/8 seed rows (13/13 across the
seed/constructor/destructor baseline); current-object preview preserves all
three units, 522 -> 522 authored bytes. Declared-unmatched check passes.
`header_adopt_lane.py accept --class UpdateModule` passes for those three
sources and retires their three stale header_queue.tsv rows through the owner.
No source paths moved, pins or aliases changed, or census/ownership gain claimed.

Logs here record the before/after builds, previews, owner verdict, final merge
dry run and class-view planner. The planner cannot reconcile the trigger's
inherited +4 module data view automatically; its class/struct ModuleData views
also disagree. Constructor field spellings differ from the seed. Remaining
merge prerequisite: reconcile AIGateUpdate's primary vtable declarations across
constructor and destructor before combining the destructor with the seed.
