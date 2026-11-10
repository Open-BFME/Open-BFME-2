### LINK-169: Object primary-table views omit native overrides (2026-11-01, codex bce2)

Status: Open. Source base `8c6bd6ae65d`, preview index `0d24c60eef`. ObjectDestructor.cpp passes 17/17 rows and its data row, but its private Thing view emits a one-slot primary table instead of native 7FC300/32B. Fresh ObjectConstructor.cpp passes 49/49 and emits eight slots through canonical Thing, yet slots1/2 return null rather than native this, and slot5 is __purecall rather than native292D49; slot0/6 also retain Thing defaults. Matching that current provider or merely swapping the destructor to Thing.h would not prove native correctness. Reconcile actual Object overrides and existing callback/deleting-wrapper providers with both whole parent/EH graphs and secondary tables retained. No production edit, queue retirement or census gain is made; current destructor preview stays blocked. [Native slots, current relocations and controls](../../reverse/attempt_support/object-primary-table-20261101-bce2/README.md).
Update (2026-11-01, seat halilkkaya-lk11): cause and partial repair. The census
loss (linked at `5d5cf41adf`, not at `ee981931dc`) came from `4fffb37e92`, which moved
ObjectConstructor.cpp (first in link order) onto canonical `thing.h` while
ObjectDestructor.cpp kept its private one-slot Thing; `??_7Object@@6BThing@@@` has no
retail address in the index, so the first-copy rule applied. ObjectDestructor.cpp now
includes `thing.h` too (private Thing removed, `getTemplate` casts the canonical
`m_template` to its KindOf view; header queue row retired by `header_adopt_lane.py
accept --class Thing`). Both copies now emit the same eight-slot table. `./build.sh`
17/17 rows and the data row; scoped DIR32 OK (66 rows, both units); `link_check`
ObjectDestructor.cpp 0 -> 972 B, ObjectConstructor.cpp 3,606 B unchanged, Thing-COMDAT
peers ThingConstructor, Thing, DrawableConstructor/Destructor unchanged (3,147 B).
This is parity, not native correctness: both copies still carry Thing's defaults in
slots 0/1/2/5/6. Remaining prerequisite (needs `class:Object`, held by StarkillerHDX's
Object header seat at 15:40 UTC): declare in both views (or the coming canonical
Object header) the native overrides `calculateHeightAboveTerrain() const` (rowed,
0x0028B569), inline `asObjectMeth() { return this; }` and its const twin (slots 1/2,
folded 0x0047A6A9) and `reactToTransformChange` (rowed MAE spelling, 0x00292D49);
slot 6 (0x0028B193, rowed non-virtual `?rva0028B193@Object@@QAEXXZ`) also needs
Thing's `vslot6` respelled in `thing.h` plus a `rename.py function --virtual`.
Change both units together so the copies stay equal.
Update (2026-11-10, ancalgonn-swarm-class-object): primary slots 1/2 and the
table spellings. Slots 0 and 5 were already declared in both views (`fb8f466d29`).
ObjectConstructor.cpp and ObjectDestructor.cpp now both declare
`asObjectMeth() { return this; }` and its const twin, as `object.h` does; retail's
slots 1 and 2 hold the shared `8b c1 c3` body 0x0047A6A9, so both overrides are
rowed there as verified ICF folds (`add_match --icf-owner ??0RealRange@@QAE@XZ`,
fold-proof region.cpp). ObjectDestructor.cpp now spells the +0x64 base and the
virtual base as ObjectConstructor.cpp does (`BfmeCtor001B3A20` over
`BfmeCtorFirstBase001B3A20` and virtual `BfmeCtorVirtualBase001B3A20`, the data
ledger's first names at 0x007FC2D8 and 0x007FC27C), so
`??_7Object@@6BRva00BFC2D8Base@@@` and `??_7Object@@6BRva00BFC27CVirtualBase@@@` are no
longer emitted. Both objects now emit the same six tables slot for slot. `./build.sh`
72/72 rows plus the data row; `link_check` LINKS 3,681 and 972 bytes, unchanged.
Still open: slot 6. Overriding Thing's `vslot6` needs the row's identifier changed
(`?rva0028B193@Object@@QAEXXZ` to `vslot6`), which `rename.py` accepts only with an
inferred `agree:` record, then `function --virtual --access protected`; `--virtual`
alone keeps the identifier and would add a ninth slot instead. The four secondary
tables (0x007FC2D8 6 slots, 5 missing; 0x007FC2B8 8, 7 missing; 0x007FC290 10, 9
missing; 0x007FC27C 5, 4 missing: 25 wrong of 29) still emit only slot 0 each and
stay bridged.
Update (2026-11-10, ancalgonn-swarm-class-object): secondary tables, declarations
only. Both lifetime units now declare the +0x64 base's six slots as the registered
ObjectShroudClient spells them, and the +0x70 base's slot 1; Object declares its
already-rowed overrides rva002941EA, ShroudGetValueRangeAndMask, ShroudHideIfFogged
(0x007FC2D8 slots 3-5) and rva0028C08D (0x007FC290 slot 1). No row renamed. Emitted
tables: 0x007FC2D8 six slots with 3-5 equal to retail and 1-2 `__purecall` (retail:
the empty 0x000B3FD0 and getGhostObject 0x00290EFE, still rowed under placeholder
Rva00290EFE); 0x007FC290 two of ten slots, both equal to retail. Wrong secondary slots
25 -> 21. `./build.sh` 74/74 and the data row; `link_check` 3,684 and 972 bytes. Not
taken: renaming the +0x6C/+0x70 bases to Rva005EEE6B/Rva0028AB0D. Both base tables
(0x007FBC9C, 8 slots; 0x007FBCBC, 10 slots) are all `__purecall`, so the 9-byte
constructors 0x005EEE6B/0x0028AB0D that store them can be any same-length pure
interface's (the ledger names 3 and 5 classes there), and the rename made
ObjectConstructor.cpp duplicate RvaSmallVtableCtors.cpp's base constructors and tables
(`link_check` 3,681 -> 0); reverted.
Update (2026-11-10, ancalgonn-swarm-class-object): Object.cpp's Object view now has
retail's bases (Thing via thing.h, Snapshot, the +0x64 interface with its virtual base,
+0x6C, +0x70), spelled as the lifetime units spell them, replacing the pads over
+0x00..+0x74. This is the prerequisite for moving the secondary-table bodies (all approved
for Object.cpp) into Object: an override in a secondary interface compiles with `this` at
that subobject. 98/98 rows and the data row; `link_check` 7,026 bytes unchanged, lifetime
units unchanged. Section by section against the parent-built object the only new symbol is
the vector constructor iterator `??_H@YGXPAXIHP6EPAX0@Z@Z`, equal to retail 0x00001423
(34 bytes, no relocations) and already emitted by both lifetime units (Matrix3DData.h's
`Vector4 Row[3]`); no vftable, vbtable, thunk or other inline body is emitted.
Update (2026-11-10, ancalgonn-swarm-class-object): 0x007FC2D8 slot 1. Object overrides the
+0x64 interface's empty slot (`protected: virtual void opaqueSlot1() {}`) in both lifetime units;
the 1-byte `c3` is rowed at the shared empty body 0x000B3FD0 as a verified fold (owner
??1Region2D@@QAE@XZ, region.cpp; fold_proof.py on both objects). Wrong secondary slots 21 -> 20.
Update (2026-11-10, ancalgonn-swarm-class-object): the twins. Retail's 0x007FC2B8 slots 3/4 both
hold 0x00299C74 and 0x007FC290 slots 2/3 both hold 0x00299C78 (`lea eax,[ecx-0x6C|0x70]; ret`, the
Object seen from that interface). rename.py --to-class refuses a body in two slots of a class's own
tables, so each pair is a const/non-const override pair (`rva00299C74`, `rva00299C78`) in both
lifetime units, rowed as four verified folds onto the placeholder rows at those addresses
(fold_proof.py on both objects). The const member takes the lower slot, as VC7.1 lays an overload
group out. +0x6C slots 1-2 stay __purecall until 0x00299CBE / 0x00299CC2 move. Wrong secondary
slots 20 -> 16.
Update (2026-11-10, ancalgonn-swarm-class-object): +0x6C slots 5-7 and +0x70 slots 4, 6, 7.
0x00299C7C (`mov eax,[esp+4]; mov [ecx+0x45C],eax; ret 4`) and 0x00042272 (`mov eax,[ecx+0x45C]; ret`)
each fill one slot of both interfaces, setting/reading Object+0x4C8 through +0x6C and Object+0x4CC
through +0x70: two functions per body, named after address and slot (`rva00299C7C_6Cs5`,
`rva00299C7C_70s6`, `rva00042272_6Cs6`, `rva00042272_70s7`). 0x005801F2 (`mov eax,[ecx+4]; ret`) reads
Object+0x74 through +0x70 (`rva005801F2`). All five are verified folds (fold_proof.py on both objects)
onto the rows already at those addresses; PartitionGetPlayerIndex (+0x6C slot 7) is declared only.
+0x70 slot 5 stays __purecall until the --to-class of 0x0028E84A/0x0028C0E3/0x0028E868. Wrong
secondary slots 16 -> 10.
