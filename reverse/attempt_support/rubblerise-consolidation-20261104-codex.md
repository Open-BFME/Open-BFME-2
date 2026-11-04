# RubbleRiseUpdate consolidation prerequisite

Inspected revision: `9059101e9f`, 2026-11-04. Scope: the approved
`Code/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdate.cpp` TU and
its constructor donor. This is source cleanup, not a lost-row repair.

## Completed cleanup

Replaced the seed's private `DieModuleInterface` definition with its registered
canonical header. Both definitions have the same single pure `onDie` slot.
`header_adopt_lane.py accept --class DieModuleInterface` passes for the seed;
there was no corresponding header-queue row to retire.

`./build.sh` passes all eight seed rows, nine string references and two float
references. The restored constructor passes both rows. Frozen-file checks pass.
The two-source `link_check.py` preview retains LINKS for both units: 1,523 and
150 authored bytes, respectively (index census 2026-11-04 20:47 at `f12552d0a7`).
This preview is not a new census or real-link measurement.

## Constructor prerequisite

`tu_skeleton.py --merge .../RubbleRiseUpdate.cpp --dry-run` cannot compose the
constructor donor: the seed has no constructor declaration, and its canonical
`UpdateModule` plus `DieModuleInterface` bases differ from the donor's private
flat `UpdateModule` and explicit secondary-vptr field. `tu_views.py --dry-run`
also reports the incompatible `RubbleRiseUpdate` base clauses.

A trial declaring the constructor in the seed and using canonical bases in the
donor fails byte verification: compiler-generated derived-vptr stores are
emitted in addition to the existing manual stores. The trial was reverted;
no nonmatching reconstruction, new pin or vtable alias remains in `Code/`.
Do not repeat that header substitution without resolving how the real class
emits the retail vptr sequence. The destructor/vtable owner is still named
`Rva004A4C19`; byte identity does not itself authorize renaming its tables.

The same raw base view explains the existing LINK-095 funclet prerequisite:
`uw_0078ddc4` calls declared-only `??1UpdateModule@@QAE@XZ`, whereas the canonical
base destructor is virtual (`UAE`). No funclet was repointed and no alias was
added to mask that ABI difference.

## Mixed-donor split lead

The read-only `tu_skeleton.py --split .../StructureCollapseUpdate.cpp --for
.../RubbleRiseUpdate.cpp --dry-run` carves `doRubbleDoneStuff` at `0x004A4DBE`
and its two EH rows. Those three rows verify alone under the destination's
flags, but composition fails in inherited `reference/shims/sweep/snmp.h`
declarations (`AsnCounter64`, C2146). The residual retains three rows.
No split was applied. Reconcile the donor's include/declaration dependencies
in a separately claimed and verified change before retrying composition.

The primary merge remains blocked; no source-file reduction or linked-byte
gain is claimed. Next work is constructor class/vptr reconciliation or the
mixed donor's include cleanup, followed by the supported merge/split checks.
