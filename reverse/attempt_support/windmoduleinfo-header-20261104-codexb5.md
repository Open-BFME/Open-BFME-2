# WindModuleInfo canonical-header adoption

Inspected revision: `2579fb163c`. Date: 2026-11-04. Worker: yasinschroeder-codexb5.

## Completed scope

The three native FX providers now include the existing canonical
`Code/GameEngine/Include/GameClient/WindModuleInfo.h` outside their namespaces:

- `Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003A53C4Finish.cpp`
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003A547EXfer.cpp`

Member references follow the header's existing offset names. The constructor
provider retains its inline destructor and empty post-load callback as out-of-class
definitions. FXParticleSystem.cpp retains its inline destructor and now defines
the assignment the shared header declares, preserving its existing memberwise
provider and pointer-to-member anchor. No header, ledger identity, pin, alias or
source path changed.

The scripted adoption was tried first and restored its failed trials. It left
compact constructor fields unmapped; explicit namespace-correct includes and
field mapping pass. The unchanged transfer unit passed all three code rows and
two data rows as a control before the manual replacement.

## Verification

`./build.sh` passed all 382 distinct function rows across the three sources
(373 in FXParticleSystem.cpp and nine in the two smaller providers), all three
data rows, and the string, float and import reference checks. The ledger also
contains an alias row, so its main-unit row count is 374.

`find_declared_unmatched.py` passes all three sources after the edits; its note
about five unclaimed definitions in FXParticleSystem.cpp also occurs before the
edits. `git diff --check` passes.

`header_adopt_lane.py accept --class WindModuleInfo` passed all three sources
and retired exactly their three rows from `reverse/header_queue.tsv`; a second
acceptance after final source cleanup also passed.

Current-input link preview against census 2026-11-04 16:16, revision
`2f0cb97f52`:

| Source | Result | LINKED before / after |
| --- | --- | --- |
| Rva003A53C4Finish.cpp | LINKS | 284 / 284 |
| Rva003A547EXfer.cpp | LINKS | 272 / 272 |
| FXParticleSystem.cpp | LINKS | 5,650 / 5,650 |
| Total | 3 of 3 link cleanly | 6,206 / 6,206 |

This is a preservation preview, not a new census or a real-link measurement.

## Remaining queue scope

Eight Common sources remain unchanged and queued. Their private declarations
are not the native 0x48-byte wind payload described by the canonical header:

- Rva002BAEAB.cpp uses a twelve-byte polymorphic member. LINK-161 already
  documents its delayed-spline Snapshot identity problem.
- Rva0033F33DDtor.cpp, Rva0034149BDtor.cpp, Rva0034159ADtor.cpp,
  Rva00341796Dtor.cpp, Rva003418EAMethod.cpp, Rva00341E70Dtor.cpp and
  Rva00341E70VSlot.cpp use a 0x20-byte state-like base with ID, success/failure
  IDs, transitions, machine pointer and tail flag. The queue's wind header
  cannot replace this layout. These declarations are evidence of an identity
  mismatch, not proof of the original base's name.

Next: establish those bases from native class/vtable evidence, reconcile their
provider and consumer identities, then use the header lane's verdict to retire
only passing rows. Do not substitute the wind payload or hand-delete the queue.
