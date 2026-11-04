# SpecialDisguiseUpdate destructor consolidation, 2026-11-04

Base: `0bd35bbdc2` (the separately verified module-data declaration repair).
The supported planner ran under GameLogic/Object/Update with no missing inputs;
its alternative source-path hints are not TU approval. The merger rebuilt the
current TU assignments in memory and approved the destructor and its three EH
rows for `Code/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdate.cpp`.

## Change and verification

The original seed's opaque module-data view could not compose with the donor.
The prerequisite adopted the donor's existing polymorphic 0xC8 base and two
AsciiString members at D0/D4, retaining its address-derived base spelling.
This is target-layout evidence from an already matched destructor, not proof
of the base's original class name. No new donor identity is asserted.

`tu_skeleton.py --merge` absorbed SpecialDisguiseUpdateModuleDataDtor.cpp and
kept all 20 matched rows. Source files decrease by one. Exactly four source
cells in functions.csv and four source cells in tu_map.csv were repointed;
TU assignments were not regenerated in the committed map.

- Final `./build.sh` passes 20/20, with two string literals and four floating
  literals verified. Six renumbered funclet labels are verified against parent
  EH data, including the two moved unwind rows.
- `eh_verify.py`: EXACT 3/3, no missing objects or baseline exceptions.
- `find_declared_unmatched.py`, `check_csv.py`, and staged TU ownership pass.
- Staged code identity: 20 rows, zero new findings (shadow mode).
- Data identity retains the same three seed findings reported before the move:
  DRAWABLE_FRAMES_PER_FLASH duplicate-def and wrong-name at A03D7C, and the
  getModuleNameKey function-local static wrong-name at A03D78. No donor data
  key disappears. Converged data check: 11 addresses, zero second names and
  zero unjudged rows.
- The merger's census-linked guard passes for all four candidate units. It
  replaces absorbed providers in link order and checks resolution, duplicates,
  selected COMDATs, aliases and outside-consumer losses against census evidence.
  The current-object preview is LINKS, 1,159 -> 1,259 bytes, against the
  2026-11-04 17:56 census at 8c757ea0db. The extra 100 bytes belonged to the
  absorbed donor already; this is no new census or real-link gain.

## Debt and complete pending-path audit

Audited origin/master `7037ac3142` through the prerequisite `0bd35bbdc2`, plus
this staged merge. The pending path changes are Rva00091DC4Forward.cpp and
Rva00092024Clear.cpp into W3DTerrainVisual.cpp, SiegeDockingBehaviorDockPoints.cpp
into SiegeDockingBehavior.cpp, and this destructor into SpecialDisguiseUpdate.cpp.
Combined case-insensitive basename searches covered the repository, including
tools, hooks, workflows, source includes, root build/config files and registers
(excluding build scratch, the reference checkout and historical attempt-support).
There are no active path consumers requiring an update. Remaining references
are source provenance comments, historical link_status census rows, naming
votes/agreements/meanings and re_attempts records. Earlier path moves retain
their detailed audits in w3dterrain-merge-20261104/README.md and
siegedocking-dockpoints-consolidation-20261104-codex.md.

The absorbed destructor owns no gate, data, identity, header, Microsoft-header,
hatch, flag, deleted-row, body-owner or name-basis keys. The seed's existing
header-queue entries are preserved. The merger transferred header debt and
refreshed Microsoft-header occurrences using their owning tools; neither queue
needed a change. No debt is retired, no alias is removed, and no hatch count
changes. Active source ownership now resolves to the surviving TU.

## Remaining prerequisites

SpecialDisguiseUpdateModuleDataCtor.cpp still fails C2600 (constructor absent
from the seed declaration); SpecialDisguiseUpdateCtor.cpp fails C2511 (missing
constructor signature). Their base construction and class views need separate
reconciliation before another merge. Both sources and mixed-file owners remain
unchanged. The inspected destructor has no parameters or local bindings to
rename. Existing linking obstacles for interface storage and real-link module
blockers were reviewed; this move changes neither their next steps nor status.
