# W3DBuffDraw instance composition

Inspected base: `12088e72b6`. Scope: W3DBuffDraw.cpp and
W3DBuffDrawConstructor.cpp in
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/.
Both file scopes were claimed through the default picker.

The supported source-layout planner surveyed the draw subsystem. Its packets
leave these rows unresolved; its original-path catalogue does not prove their
home. The merge tool rebuilds the stale TU map in memory and approves the
provisional W3DBuffDraw TU, without regenerating the committed map. The mixed
name-getter and generated unwind owner stay outside this merge.

## Instance-view prerequisite

The original supported merge fails because the seed's private view has no
DrawModule base or constructor. tu_views independently reports that base-clause
conflict. Both files now spell the same derived view: canonical DrawModule,
constructor, existing virtual const getModuleNameKey, and the constructor's
existing byte at +0x0C. No new member name, pin or hatch is introduced.

Target facts: retail constructor RVA 0x000CEDE1 (32 bytes) calls DrawModule at
0x000B19A1, stores vftable VA 0x00BCD178, and clears byte +0x0C. Slot four of
that table is RVA 0x000CEE07, the existing getModuleNameKey row. Declaring the
override in the constructor view therefore replaces its incomplete purecall
slot with the retail binding. This does not recover the other partial vtable
entries or establish the complete retail interface. The previously compiled
constructor body, including its vtable relocation, still byte-matches.

Verification before committing the prerequisite:

- Ordinary build and strict reusable preparation verify 9/9 rows and the
  field-table data row. Frozen-file and class checks pass. Both EH graphs are
  EXACT. Converged data checks judge eleven addresses, with zero second names
  and zero unjudged rows.
- External COMDAT byte-and-relocation fingerprints: all fifteen seed copies
  and fifty-four of fifty-five constructor copies are unchanged. Only the
  constructor's W3DBuffDraw vtable changes, at slot four as established above.
  No definition is added or removed. The sole added undefined reference is
  getModuleNameKey, already defined in the seed. No alternate alias is removed.
- Census-only and current paired previews both retain 2/2 LINKS and 237
  authored bytes against index 5a13f2cd61 (2026-11-04 02:25 UTC). The
  new-variants check passes. These previews are not a new census measurement.
- The supported merge dry run now accepts both files and retains nine rows;
  the mixed getter and generated unwind file remain separate.

Scratch logs and before objects: build/w3dbuffdraw-20261104/.
A strict preparation attempted concurrently with the merge probe refused its
moving-input witness; serialized preparation passed. Data inspection attempted
while that compilation was replacing receipts was likewise rerun after it
finished and passed. Neither transient refusal was bypassed.

Compiler layouts agree: sizeof 0x10, DrawModule at zero and the existing bool
at +0x0C. The Microsoft-header owner reports both sources clean; neither
source has a class-header or Microsoft-header queue row or identity/hatch key.
No debt is retired.

The staged prerequisite batch audit is INCONCLUSIVE: the index predates this
base, and the affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. The paired current preview is clean, but full consumer
selection/loss verification remains open. Carry this consumer and the changed
vtable provider into the next scheduled census/current-receipt audit.

## Applied instance merge

Prerequisite a9a7ef2b9b was handed to the runner publisher before composition.
The supported planner was refreshed after that commit. tu_skeleton --merge
accepts both files and removes W3DBuffDrawConstructor.cpp. It repoints exactly
one function source and the corresponding existing TU-map source field; the
map is not regenerated on disk. This removes one source file and places one
additional code row in its approved provisional TU. The tool refreshes both
header queues; neither changes. No donor register key needs transfer or
retirement, and existing data owners remain in the destination.

Final ordinary build and strict reusable preparation verify all nine rows and
the field-table data row. The destination is tracked and frozen-file clean.
Both EH graphs remain EXACT. Converged data verification judges eleven
addresses with zero second names or unjudged rows. The before-object union
contains seventy external COMDATs, all retained in the merged object without
additions or removals. Sixty-nine fingerprints are unchanged; the sole
changed fingerprint is the already verified slot-four vtable prerequisite.

The current merged preview LINKS with 237 authored bytes against 5a13f2cd61.
Its printed 205 -> 237 change includes the removed constructor's 32 bytes;
the pre-merge paired scope already held 237 bytes. No census linking gain or
image-ownership change is claimed. The merge tool's current guard also
protects both previously census-linked inputs.

Tooling compatibility audit: fetched origin/master ea0d901129 and reviewed
its complete outgoing range through the staged merge (prerequisite tip
a9a7ef2b9b). The constructor absorption is the only pending path change.
A combined full-path/basename search covers tools, hidden hooks/workflows,
source/header includes, build inputs, ledgers, registers and documentation.
No active consumer needs an update. Surviving mentions are the historical
census status, source-provenance comment and attempt evidence. Function and
TU-map owners now resolve to the destination; data owners already did;
no stale fold proof or doxygen entry remains. Moved-source proof uses fresh
destination receipts. The header and Microsoft-header queues have no row for
either source, and the merge's owning refresh changes neither queue.

The complete outgoing staged audit remains INCONCLUSIVE on the older index
and four missing current source receipts, first Common/RTS/Team.cpp. The
isolated merge audit is INCONCLUSIVE on affected consumer
Common/0CreateAHeroManager21FE49.cpp's missing current receipt. These are
verification gaps, not a clean full consumer audit. Carry the merged provider,
retired constructor and affected consumers into the next scheduled
census/current-receipt audit. Remaining source prerequisites are the mixed
name getter and generated unwind owner; the instance inheritance prerequisite
is resolved for this composition scope.
