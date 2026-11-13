# Citadel slaughter-horde data: real inherited virtual interface

Target: CitadelSlaughterHordeContainModuleData table RVA 0x00848E40. The native
table has 31 slots, not the former one-slot compiler view. Slots 1..30 equal
HordeGarrisonContainModuleData's native table at RVA 0x007F4328; slot 0 is the
Citadel deleting destructor at 0x004811CA. The rowed Slaughter data constructor
0x0048104D calls HordeGarrison's constructor 0x0047A251. Factories prove sizes
0xD4 for HordeGarrison, 0xEC for Slaughter, and 0x110 for Citadel. These target
facts establish the existing shared base and the remaining +0xD4..+0xEB storage.
No donor name or unknown field semantics were inferred.

The primary Citadel TU now includes the canonical HordeGarrison data header before
Drawable selects its distinct capitalized Snapshot view. Its private Slaughter
view derives from that base and retains only its own 24 bytes of opaque storage,
with the existing out-of-line constructor/destructor/parser declarations. The
Citadel member declarations and all body implementations remain unchanged.

./build.sh passes all 18 matched rows. EH verify reports three exact graphs.
The emitted table is 124 bytes and all 31 positive slot bindings match native
rows, including the compiler weak deleting-destructor default. Its other 571
COMDAT fingerprints remain identical; the 28 additional canonical inline helpers
match their existing rowed retail bodies byte for byte with no relocations. The
companion JSON preserves every target pointer, added helper and native check.
Scoped link_check preserves 682/682 census-linked bytes against old aa7acf764d;
this preview does not establish whole-game closure or authoritative retirement.

The data ledger and vtable bridge queue remain untouched. Only the next published
real-link receipt may establish that this target no longer needs its bridge.
