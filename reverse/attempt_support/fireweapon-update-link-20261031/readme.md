# FireWeapon secondary Update contract

Base 941fe7fcbcfe; model GPT-6; lane=R; budget=30m. The body and both
source scopes were origin-confirmed before edits.

Target facts: constructor 0x00482D80 installs table 0x008496E8 at +0x10.
Its three slots are 0x00482BB9, 0x004DF396 and 0x0044DF8D. The first
body is already rowed as a nonvirtual int member of Rva00482BB9; its
count at interface+0x98 is the constructor's whole-object +0xA8 count.
At zero it calls the +0x28 Die interface with the +0x2C DamageInfo.
The UpdateSleepTime return type and slot roles follow the existing Update
interface contract, not the fact that an arbitrary name compiles.

Private Scorer tests of the actual FireWeaponWhenDeadBehavior virtual
member reproduce all 34 resolved native bytes at both candidate source
contexts. The other nine owner rows retain identical raw bytes and
relocations. Scratch explicitly preserves the Code defaults O1, arch:SSE,
G7; the first trial without those defaults was not representative. No
production flags, pins, hatches or shared build-cache objects are changed.

The old real claim must be retracted in its own reviewable commit before
add_match admits the correct owner/signature. This first commit removes
only that row/body and records its tombstone. It is not published alone.
The complete candidate and consumer are retained in private scratch for
readmission, without a source-path move. No new matched or linking bytes
are claimed by this intermediate retraction.


## Readmission and consumer repair

The matched member is readmitted with add_match in the **same owner source**,
VslotSmallBodiesE.cpp; no row is moved into an unapproved TU. The constructor
adopts the actual three-slot Update interface and its all-disabled mask override.
All three table targets are independently verified: real member 0x00482BB9,
complete resolved inline mask getter equal to 0x004DF396/26, and the existing
UpdateModule wake member at 0x0044DF8D. Both native vptr stores retain 0x008496E8.
The primary tables still agree on all thirteen native slots.

Rva00589079Derived.cpp's existing opaque secondary view now declares the real
virtual update slot, overridden by FireWeaponWhenDeadBehavior; its old f2 alias
is removed rather than redirected. This keeps the destructor's first-slot
provider correct and retires one counted alias through hatch_counters --update
(2,847 -> 2,846). Its pre-existing one-slot secondary view still lacks two slots:
**no full destructor secondary-view or class-hierarchy unification is claimed**.

The retraction commit's normal hook verifies 13,162 functions over its 687-source
scope. EH has 1,719 EXACT graphs and one pre-existing registered divergence.
This mandatory verification is separate from the ten-minute reconstruction.
The final direct scope passes 453/453 rows in seventeen sources, 314 literals,
one empty-string reference and eleven floating-point references; all seven
scoped EH graphs are EXACT. The changed caller pair separately passes 12/12;
the readmitted owner passes 10/10. No production flags or pins are added.

All seventeen ordinary previews LINKS against census index 7300bffea9.
Only the constructor's 0 -> 209-byte change is this repair; the other 32 bytes
of since-index growth in Deflect/WeaponMode are unrelated. VslotSmallBodiesE
retains its 622 bytes, the destructor its 311. This is bounded provider/linking
evidence, not measured census credit. No unique matched byte gain is claimed.
The next required checks are normal commit/push hooks and the outgoing-batch
consumer audit, followed by scheduled census confirmation. The destructor's
remaining secondary slots and approved-TU consolidation stay open.


## Outgoing batch audit after rebase

At outgoing base `22d24b8a3831`, neither the seventeen direct sources nor the
core build inputs changed since the verified repair base. The complete audit
of the three changed sources exits 2: its baseline is the older 7300bffea9
index and AIBuildable.cpp lacks a current local receipt. This remains an
**INCONCLUSIVE** wider consumer verdict, despite the full direct native and
link-preview proofs. No broader loss-free closure or census gain is asserted.
Carry this provider scope and that consumer into the next scheduled census.
Header-dependency classification exits 0. AGENTS.md was reread after its update;
the account's normal publisher and hooks remain the publication path.
