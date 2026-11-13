### LINK-663: a re-based scaffold view emits a short copy of the real class's vtable, which wins the COMDAT
Status: Repaired / awaiting census confirmation. Updated: 2026-11-12 (seat halilkkaya-lk105); base `54e2556eae9`,
census `4ba87ee6df` (index `5e2fc81a04`).

**Problem.** The OpaqueScalarDeletingDtors* units emit compiler-generated deleting destructors through a scaffold:
each declares a private view of the class with an `X(EmitVtableTag *)` constructor (absent from retail), so that
the unit emits `??_7X` and `??_GX`. The view only needs a virtual destructor, so it usually declares no other
slot. That is harmless while the view's table carries a name that no other unit emits. If an edit to the view's
bases renames its table to the real class's name, the scaffold's short copy and the real class's full copy become
the same COMDAT. The scaffold unit sorts first in link order, so its short copy wins. link_check then marks the unit
with the full table as a loser (`comdat ... differs from the first copy in link order`), and the image keeps the
short table.

**Instance.** "OpaqueScalarDeletingDtorsB12: adopt the registered parents for Rva0056AD19" (nleigh, before the
16:28 census) re-based B12's Rva0056AD19 scaffold from Rva0056AC26A/B to Rva0007DF07 + Rva0056AC26Base2. That
renamed its primary table from `...@@6BRva0056AC26A@@@` to `??_7Rva0056AD19@@6BRva0007DF07@@@`, which is also
the table of Rva0056AD19Dtor.cpp (`class Rva0056AD19 : public Rva0056AC26`). B12's copy held 1 slot; retail's
0x0086D1EC holds 5 (0x0056B0A3, 0x0047A699, 0x0047A69C, 0x000B3FD0, 0x000B3FD0). Rva0056AD19Dtor.cpp: census
2026-11-12 00:41 "yes", 312 B; census 16:28 "no".

**Repaired.** "Give B12's Rva0056AD19 scaffold the Rva0056AC26 base so its primary table has retail's five slots
again": the scaffold derives from the canonical Rva0056AC26 (whose registered parents are those two bases). Its tag
constructor passes a null owner. Both copies now hold the same five slots. "Give Rva0056AD19's primary table retail's
slot 1, the shared false body" then declares the `ac26Slot1` override in both views and rows it as the
0x0047A699 twin, so the table equals retail slot for slot. Measures: link_check 0 -> 315 B
(Rva0056AD19Dtor.cpp, 76 of 77 related units LINK, nothing lower); lk74_cmp 1 table off the bridge, nothing
newly bridged.

**Recipe.** A scaffold view whose table name equals the real class's must declare the same slots as the real
class. The simplest way is to derive from the same canonical base the real class uses. Before you change a scaffold
view's bases, list the `??_7` names its object defines and check the index for other definers of each name
(`link_index.pkl` `comdat`). Any name another unit also defines must keep that unit's slot list.

**Tooling lead (not edited).** link_check could report a `??_7` COMDAT whose copies differ in length even when the
losing unit is not among the checked units, and `header_adopt_lane` / `class_views` could refuse an edit after which
an object starts to define a `??_7` name that another object already defines with more slots.

### Regression 2026-11-13: two units emit Rva0056ACC5's Base2 table with different slot 12 (seat halilkkaya-rg1)

Base `d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Symptom.** Rva0056AC26Constructor.cpp: census 2026-11-13 01:15 (`e5da954ea6`) "yes", 352 B; census 04:18
(`6e37424cf7`) "no". link_check: comdat `??_7Rva0056ACC5@@6BRva0056AC26Base2@@@` "differs from the first copy in
link order (no retail address)".

**Cause.** "Migrate the Rva0056AC26 family onto the canonical Rva0056AC26 base" (`5968bf97836`, nleigh) made
Rva0056AC26Derived.cpp emit that table under its canonical name, with Rva0056ACC5's `slot12` override. Before, the
unit defined hand tables under `_B1` spellings, and only the constructor unit emitted the name. The constructor
unit's private Rva0056ACC5 view has no `slot12`, so its copy names `?slot12@Rva0056AC26Base2@@UAE_NH@Z` at slot
12. Derived.cpp's copy is the first, and the constructor unit's differs. Retail table 0x0086D0C0 slot 12 is
0x0056AB88, `?slot12@Rva0056ACC5@@UAE_NH@Z` (Disp8ByteFieldGetters.cpp). So Derived.cpp's copy is retail's.
`1e7badec2f8` fixed slot 2 of the same view the same way.

**Repair.** "Give the ACC5 ctor unit's view the slot12 override its Base2 table holds" adds
`virtual bool slot12(int);` to the constructor unit's view. Object diff: only that table's slot 12 changes
(`?slot12@Rva0056AC26Base2@@UAE_NH@Z` -> `?slot12@Rva0056ACC5@@UAE_NH@Z`); `./build.sh` 30/30 exact. link_check
over the four units that define or emit Rva0056ACC5 names (the constructor unit, Derived, Disp8ByteFieldGetters,
Rva0056AB35Method): 4/4 LINKS, LINKED 783 -> 1,135 B (the constructor unit 0 -> 352).
