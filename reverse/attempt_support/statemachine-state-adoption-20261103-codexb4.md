# StateMachine donor State adoption, 2026-11-03

Inspected revision: `906debe5b7`. Scope: the StateMachine.cpp consolidation
selected by `next_work.py --claim`, with six source-file claims.

## Completed prerequisite

`StateMachineDtor.cpp` and `StateMachineXfer.cpp` now include canonical
`Common/StateMachine.h` instead of defining private State classes.
The destructor includes Snapshot first to retain its existing crc-slot spelling;
adopting State alone must not add a fifth StateMachine vtable slot.
The transfer retains its signed map specialization and a signed inline accessor
over canonical `State::m_id`. Direct field expressions changed the inlined
current-state branch and stack slots; the small accessor restores exact bytes.
The transfer's existing link-wide XferObjectID alternatename remains intact.

Verification on the final source:

- `./build.sh` reports 6/6 exact rows for StateMachineDtor.cpp and 1/1 for
  StateMachineXfer.cpp. Renumbered destructor funclet labels resolve through the
  exact same-source parent EH graph.
- `eh_verify.py` reports EXACT 1/1 EH-bearing row, with no missing object or debt.
- `find_declared_unmatched.py` passes both sources.
- `header_adopt_lane.py accept --class State` retires both source queue rows.
- `link_check.py` preserves 171/171 and 535/535 bytes against the 2026-11-03
  20:03 census at `8661f15284`. This is a preview, not a new census measurement.
- `check_csv.py` passes: 99,430 function rows, 9,343 symbols, 2,269 data rows.

No source paths, ledger owners, shared headers, pins or data definitions move.

## Remaining consolidation blockers

The current-input `tu_skeleton.py --merge .../StateMachine.cpp --dry-run` accepts
none of the five donors. StateCtor and setGoalObject encounter canonical/private
State and StateMachine declaration conflicts; the destructor needs a typed state
map and onExit surface in the seed; Xfer needs its sleep/flag members and compatible
enumerators; defineState fails bytes in the seed's context. Seven mixed files stay
outside this merge. `tu_views.py --dry-run` delegates State and StateMachine to the
canonical-header lane and refuses the Object union because of the seed's bitfield.

A separate local trial replaced the destructor's private StateMachine with
StateMachineClass.h and cast its opaque field08 to the existing unsigned State
map. That trial failed bytes and funclet verification: the opaque canonical field
does not automatically destroy the tree, so removing the typed map member removes
its teardown and unwind cleanup. The trial was reverted; only State adoption
remains. A future full adoption must preserve map lifetime and unwind semantics,
not merely its layout. The seed also still needs its transition methods reconciled
with canonical State before these donors can consolidate. No merge or file-count
reduction is claimed.
