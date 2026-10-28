# SiegeDeployHorde module-data consolidation, 2026-10-28

Seat: yasinschroeder-codexb4. Inspected base: `e0716e4d37`.
Destination: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp`.
Absorbed source: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPowerModuleDataDtor.cpp`.

## Routing and prerequisite

The scoped `name_lane.py consolidate` report was regenerated after the
prerequisite and upstream rebase. It supplies no verified retail path for
these rows; its stale-map placements remain unresolved context. The supported
TU planner rebuilds current assignments in memory and approves this group
provisionally from its naming cluster. This groups the rows; it does not
prove the original retail filename. The committed map changes only the moved
row's source cell, without regenerated assignments.

The first supported dry run accepted no donor. Compiler-layout planning
reported incompatible base clauses among seven behavior-class views, an
opaque buffer beneath AIUpdateModuleData's vfptr, and a class/struct mismatch
for the module-data view in the initiate source. Prerequisite `49b99c2be7`
reconciles just the seed and module-data destructor: both declare the existing
virtual destructors, the base's vfptr plus 0x14 bytes occupy 0x18 bytes, and
the flag remains at +0x18. The destructor donor already uses novtable; applying
that contract to the constructor view suppresses a surplus derived-vptr store
while preserving its explicit retail store. Both compiler layouts now agree
(base 0x18, derived 0x1C). No function body changed in the prerequisite.

The next supported dry run and applied merge accept only the seed and that
destructor donor. One source file is removed and all six destination rows
remain exact, including the moved five-byte destructor at 0x004C64E9.

## Verification and bindings

Normal builds and strict provider preparation pass all six rows, the parse
table and the pool-name literal before and after composition. The pool getter's
EH graph is EXACT; the frozen-file check finds no unrowed definitions. Staged
TU ownership and Microsoft-header checks pass. Code identity reports six rows
and no new findings; scoped data checking reports no findings.

Original and reconciled objects were saved under
`build/siegedeployhorde-before-codexb4/`. Each prerequisite object retains its
external symbol facts and COMDAT byte-and-symbolic-relocation digests. The
composed object retains the original pair's union of seven external definitions,
eleven external dependencies and six distinct COMDAT digests. No external
provider or dependency is added or removed and no COMDAT implementation changes.
The merge guard accepts the census-linked inputs and composition. Ordinary
preview reports LINKS for 133 authored bytes, against the seed's former 128;
the five-byte difference moves existing coverage and is not a census gain.

Neither absorbed-source code/data-identity keys nor header queue keys exist.
The merge refreshes header queues and runs the hatch update; neither queue nor
the hatch register changes. The seed's data-ledger owners stay intact, and no
fold-proof source names the removed donor. No register debt is retired.

## Complete pending-batch path audit

Audited `origin/master` at `e0716e4d37` through staged source tree
`31abd522f3038e08afb9e38130fe177bf7ecdeec`, including all earlier pending commits.
The six absorbed paths are Common/AnimationSoundTree.cpp,
Common/AreaPolygonBase_reserve.cpp, Common/Rva0014CE67Ctor.cpp,
Common/Thing/Rva001D9A00Finish.cpp,
Common/U4GlobalGuardedNotifies_Rva004ca223.cpp and this module-data destructor.
Destinations are the existing AnimationSoundClientBehavior, AreaPolygonBase,
AnimationAsset, INIAudioEventInfo and SiegeDeployHordeSpecialPower TUs.
No directory moves.

One combined full-path and basename search finds no active tool, hook,
workflow, source include, build configuration or source-registry consumer
requiring repair. Remaining mentions are origin comments, historical
census/log/handoff entries, append-only naming provenance/votes, and TU-map
naming evidence. The constructor naming agreements already have stale outcomes.
These historical paths are retained; active ledger source cells name current
owners. Earlier handoffs cover the other pending moves' bindings and registers.
All new ledger owners are tracked. Whitespace checks pass.

The outgoing link audit is INCONCLUSIVE: index `d92e7e6635` predates the base,
and four source objects lack current receipts (first:
Common/INI/INIAudioEventInfo.cpp). Carry all pending moved providers and their
affected consumers, including that TU and this composition, into the next
scheduled census. Broader selected-consumer coverage remains unverified.
No census, smoke, nightly or ownership run was started; no measured linked-byte
or image-ownership improvement is claimed.

## Remaining prerequisites

Six whole-file behavior donors remain: constructor, vector setter, destructor,
transfer, update and initiate. Their views disagree on the root base hierarchy,
secondary interfaces, available methods and member storage. The constructor
uses WeaponModeSpecialPowerUpdateBase, the destructor four secondary bases,
transfer Rva00589079, update a primary plus two interfaces, and initiate
UpdateModule plus SpecialPowerUpdateInterface. Reconcile those surfaces from
retail layout and vtable evidence before attempting their bodies together;
adding declarations alone cannot settle their incompatible layouts. The
initiate file also spells module data as a struct. No rejected donor was edited.
The one approved getter in mixed Common/ConstIntGetters4.cpp stays separate;
this merge never splits mixed files. Regenerate the planner after the applied
source/ledger move before choosing more consolidation work.
