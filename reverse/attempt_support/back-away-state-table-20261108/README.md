# State lifecycle/table prerequisite, 2026-11-08

The selected 0x00810EE0 table had a strong one-byte stand-in in
Rva0033F33DCtor.cpp and a separate one-slot compiler table in
Rva0033F33DDtor.cpp. Both native lifecycle rows install VA 0x00C10EE0.
The constructor calls the canonical State constructor at 0x004D73FC;
the destructor's base teardown at 0x0049B47C is already rowed as State.
Together with the measured 0x20-byte base and 17-slot table, this supports
replacing the private WindModuleInfo view with the shared State header.
The seven-byte teardown fold alone would not establish that identity.

The constructor now lets C++ install its table and uses a pointer for its
measured +0x20 member. Both units declare the existing virtual destructor
and xfer override. The destructor keeps its existing member-release body.
No row, pin, alias, compiler flag, source path or shared header changes.
The unused old-char declaration and its strong definition disappear.

Public build.sh passes all three lifecycle rows (33/75/28-byte extents).
Strict preparation passes all 129 rows and four data rows across eight
supporting sources; all four EH graphs are exact. Frozen-source and paired
new-variant checks pass. All original executable COMDAT bodies, flags and
policies remain equal, with only the proved char-to-table and
WindModuleInfo-to-State relocation names normalized. The constructor's
additional deleting wrapper is identical to the existing destructor owner
and independently matches its native row. Twelve inherited State defaults
per unit are complete native byte twins of the existing empty, false and
STATE_CONTINUE bodies; no derived lifecycle implementation is invented.

Both compiler table copies now have identical 68-byte/17-slot facts.
Fresh, exact constructor and destructor operands at 0x0033F354 and
0x003401F7 independently bind their compiler name to VA 0x00C10EE0.
Bounded replay removes the single strong-definition refusal; the same
one bridge/17 slots remain. Slot 3 now references the existing native xfer.
Slots 2/4/5/6 still require the getter/class and readable lifecycle names
to be reconciled. The literal getter identifies AIBackAwayAndCowerState,
but no class rename or complete-table recovery is claimed here.

The eight-source preview conserves LINKS/4,207 bytes against index
c885072a48 (2026-11-08 19:18). No outside live Code source spells the old
char. The index's aggregate reference graph shows only the constructor
edge; it lacks per-object provenance, so this is not a complete current
consumer/image audit. The WindModuleInfo header-queue key is retained:
adopting the correct State base does not constitute Wind header adoption.
Its queue identity and the four derived slots remain follow-up work.
The current TU map only proposes a destination; no consolidation is
approved or performed. No image, bridge-retirement or runtime gain claimed.

The first direct-symbol declaration trials either failed MSVC's own-class
vftable type check or emitted an unintended implicit destructor/table.
Those trials were private; none was applied. Normal C++ lifecycle emission
is the verified repair. Detailed facts are in final-proof.json; local
replay is build/back-away-table-binding-20261108/verify.py.

Published as 60858c3763 on the first attempt, 27.9 seconds. Required
byte/EH/data/scoped-DIR32 checks pass. The broader audit is INCONCLUSIVE:
index c885072a48 versus outgoing base bc96d415a731023f4fa3962b6a1506589221623a;
unchanged Common/Rva00340BDCDtor.cpp lacks a current receipt. Carry that
consumer into the next census/image check; this publication does not
establish full link closure.
