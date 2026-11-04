# GiantBird main-unit header adoption, 2026-11-04

Base: `d9f279aecf` (collision donor header adoption).
Source: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp`.

Replace local BehaviorModule, UpdateModule, UpdateModuleInterface,
AICommandInterface, AIUpdateInterface, State and StateMachine declarations with
their existing canonical headers. No shared header, ledger identity or pin is
changed. The canonical AI base ends at +0x3E4; twelve opaque derived bytes keep
the stored command at +0x3F0. The state-machine accessor stays local to the
derived class. Use canonical fields for +0x34, +0x1F0 and +0x3E0, retain a cast
to the existing locomotor view for its +0xC0 access, and call the canonical
virtual doLocomotor (primary slot 149). StateMachine slot 14 is now spelled
setGoalObject. These are witnessed offsets/dispatches, not new layout or donor
name claims; canonical declarations supply the names.

Verification:
- AI/base-header trial and State/StateMachine-header trial each passed
  `./build.sh`: 18/18 matched. Three renumbered funclet labels were resolved by
  parent EH data; one complete STLport constructor fold verified. All 16 float
  literals and string/import checks passed.
- Final `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept` passed for all seven named classes above,
  retiring one queue row per class. Base headers are explicitly included as
  acceptance requires. No register row was hand-deleted.
- Final `link_check.py` predicts LINKS, LINKED 2,249 -> 2,249 bytes against the
  2026-11-03 20:03 census at `8661f15284`. No census/headline link gain claimed.

Consolidation remains separate. The initial dry run, started before these
source/header-queue edits, accepted no donors; its diagnostics are not a
current-input merge receipt. No path moved and no source file was deleted.
A final `tu_views.py --dry-run --no-merge-check` still identifies:
- GiantBirdAIUpdate base-clause differences in the opaque follow-path views;
- Object opaque storage conflicting with the seed's Thing base;
- ThingTemplateView byte +0x108 overlapping the seed's kind-of array;
- Rva0026AFDAMember constructor dllimport disagreement;
- remaining canonical AIStateMachine, PartitionFilter and AIUpdateInterface
  adoption work in other donors.

The next consolidation pass must reconcile those donor views and obtain a
fresh merge dry run. Existing protected debt remains with its original sources.
This batch removes nine header-queue entries including the preceding collision
repair, while preserving all 19 checked rows and predicted linked bytes.
