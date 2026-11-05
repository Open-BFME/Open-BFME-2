# Common StateMachine consumers: four header debts retired

Inspected revision: `932f0d8acd3b` (2026-11-05).

`AIStateMachine_setTemporaryState.cpp` now includes canonical State,
StateMachine and AIStateMachine declarations. Existing slot-4/5 dispatch uses
onEnter/onExit with EXIT_RESET/EXIT_NORMAL; temporary-state fields use their
canonical names. Object +0x258 remains an explicitly cast local prefix view;
no new claim about that object's complete layout or callback name is made.
`VslotSmallBodiesAJ.cpp` replaces its StateMachine declaration and duplicated
state enums with StateMachineClass.h. Shared headers are unchanged.

Verification on the final sources:

- `./build.sh` for both complete sources: 83/83 rows exact, including three
  renumbered funclets verified through parent EH data; string, float and import
  checks pass. `find_declared_unmatched.py` passes for both files.
- `header_adopt_lane.py accept --class StateMachine` over both files retires
  two rows together. Separate class-cohort accepts for State and AIStateMachine
  in the temporary-state unit retire one row each. Four queue rows removed
  exclusively through the owning tool.
- `link_check.py` current-object preview: both units LINKS, preserving
  150 + 1,069 = 1,219 linked bytes against index `112a456a2c`, 2026-11-05 15:52.
- Before/after complete COFF symbol inventories from `object_symbols` have
  identical definition sets, reference sets and alternatename maps in both
  objects. Thus no provider or link-wide alias is removed by this adoption.
  No ledger row, pin, source path or hatch changes.

The initially served BoneFXDamage blocker was already repaired (LINK-113).
The published index remains older than the local one, so its recorded provider
prerequisite is unchanged; no duplicate repair or new handoff is claimed.
Broader StateMachine private-layout and enum conflicts remain outside this
verified pair. No census, real-link, runtime or headline linking gain is claimed.
