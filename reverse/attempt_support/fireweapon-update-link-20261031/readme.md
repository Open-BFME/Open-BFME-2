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
