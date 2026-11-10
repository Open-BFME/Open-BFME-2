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
