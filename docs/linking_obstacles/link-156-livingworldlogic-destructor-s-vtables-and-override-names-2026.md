### LINK-156: LivingWorldLogic destructor's vtables and override names (2026-10-30, open)

`LivingWorldLogicDtorRva002B964F.cpp` (717 B) lost three COMDAT vtables to
`LivingWorldLogicCtorBfme.cpp`'s copies (line 1634 above, and the table row
for this unit). Its view now has the ctor's shapes: the
`subsystem_bfme2` 14-slot SubsystemInterface, the name-slot Snapshot, and the
overrides `init reset update loadPostProcess GetSnapshotName xfer event1_1`.
Retail tables 0x00BFE2A4..0x00BFE2E4 hold the slots, which the rowed ctor
0x002B93B3 installs. 42/42 rows byte-verify, and `link_check` no longer
reports comdat losers. Two slot providers were renamed to their override
names, with tombstones in `reverse/deleted_rows.csv`:
- 0x002B2535 → `LivingWorldLogic::reset` (SubsystemInterface table 0x00BFE2E4, slot 9);
- 0x002B64C7 → `LivingWorldLogic::event1_1(int)` (building-observer table
  0x00BFE2C4 at +0x10, slot 1; WB OnDestroyingBuilding). This also renames its
  `__ehhandler$` row and the `$L4362` funclet `parent=`.

Both providers link (`link_check`: 57 B and 250 B).

Remaining prerequisite: `?update@LivingWorldLogic@@UAEXXZ`. Row 0x002BD9B4 and
its `__ehhandler$` 0x0077699F still carry the non-virtual `QAE` spelling, and
`LivingWorldLogic.cpp` declares `void update();` (around line 690). Making that
declaration virtual means adding the matching base and override slots to that
view, renaming both rows and adding a tombstone. That file was claimed by
another seat (claudec3) during this pass, so it was left alone.
2026-10-31 (Noro420): `rename.py function --rva 0x002BD9B4 --virtual` respelled
both rows `UAE` on retail table 0x00BFE2E4 slot 10 (installed by ctor 0x002B93B3),
with tombstones; the declaration in `LivingWorldLogic.cpp` became virtual without
any other view change. The rename's build verified 13,081/13,081 rows; `link_check`:
LivingWorldLogicDtorRva002B964F.cpp 0 -> 717 B (LINKS), LivingWorldLogic.cpp
20,081 -> 20,092 B (LINKS). The update prerequisite is cleared; census
confirmation is pending.
`LivingWorldLogicCtorBfme.cpp` also needs event4_0, event5_0 and event5_2:
0x002BA82B OnRegionChangedOwnership, `rva002BA3F2@LivingWorldLogic` and
0x002B2A95. Those need the region and player observer bases reconciled with
`LivingWorldObservers.h`. Census confirmation is pending.
2026-10-31 (Noro420): the ctor view now declares two of the overrides under
their rowed names: `OnRegionChangedOwnership(LivingWorldRegion*,int,int)`
(region table 0x00BFE2B4 slot 0 = 0x002BA82B) and
`rva002BA3F2(const Rva002E0687*)` (player table 0x00BFE2A4 slot 0). The build
verifies 26/26 rows, and `link_check` drops from 3 unresolved names to 1. The
last one, `event5_2`, is player table slot 2 = 0x002B2A95. That row is the
non-virtual `Rva002B2A95Callback::rva002B2A95` in `Rva002B2A95EvaEvent.cpp`.
`rename.py function` changes only the identifier, so the row first needs a
code-identity class merge into `LivingWorldLogic`, then `--virtual`.
2026-11-01 (halilkkaya-lk11): regression found. `LivingWorldLogicDtorRva002B964F.cpp`
(717 B; linked in census `5d5cf41adf`, not since `ee981931dc`) loses
`??_7LivingWorldLogic@@6BSubsystemInterface@@@` again, to the ctor's copy. The cause is the
ctor-view change above (`f711525822`): `LivingWorldObservers.h` names slot 0 of the region and
player observers `event4_0(int,int,int)` and `event5_0(Rva004EF2ABArg*)`, so
`OnRegionChangedOwnership(LivingWorldRegion*,int,int)` and `rva002BA3F2(const Rva002E0687*)`
override nothing. The compiler appends them to the primary table (16 slots, against retail's 14
at 0x00BFE2E4 and the dtor's 14), and the region/player tables' slot 0 still name the base no-ops
`?event4_0@LivingWorldRegionObserver@@...` and `?event5_0@LivingWorldPlayerObserver@@...` (COFF
dump of the current ctor object). The unresolved count fell from 3 to 1 only because those slots
now bind the wrong, base-default bodies. Fix (ctor file held by StarkillerHDX at 15:40 UTC, not
attempted): either drop the two appended virtuals from the ctor view, which brings back the 14-slot
primary table so the dtor links, or give the observer bases slot-0 names matching the rowed
overrides. The second needs `LivingWorldScoreKeeper::event4_0/event5_0` renamed and retyped with
them (identity work). Copying the two wrong slots into the dtor view would only spread the defect.
re_attempts verdict on 0x002B964F.
2026-11-02 (halilkkaya-lk15, base `1765dc430d`): first fix applied. The ctor view no longer declares
`OnRegionChangedOwnership` and `rva002BA3F2` (a comment records why), so its primary table is the
retail 14 slots again; the region/player slot 0 still bind the base no-ops exactly as before
(no change there). `./build.sh` 26/26 rows (one funclet label renumbered, parent EH data verified);
scoped DIR32 OK (20 symbols, ctor plus dtor); the only objects touching `??_7LivingWorldLogic@@`
names are the two units and OpaqueScalarDeletingDtorsB05.cpp; `link_check`:
LivingWorldLogicDtorRva002B964F 0 -> 717 B, OpaqueScalarDeletingDtorsB05 748, LivingWorldLogic.cpp
20,092, LivingWorldLogicPlayerObserverRva002BA3F2 1,278 and Common/LivingWorldLogic.cpp 380 B
unchanged LINKS. LivingWorldLogicCtorBfme's blocker, `event5_2` (player slot 2 =
0x002B2A95, the non-virtual `Rva002B2A95Callback::rva002B2A95` row), was resolved by dropping
the undeclared virtual override so slot 2 binds the base default: `LivingWorldLogicCtorBfme.cpp`
now LINKS 0 -> 815 B cleanly (cohort total 24,030 B). Remaining: the observer bases' slot names
(identity), then the overrides return.


2026-11-13 (merge-climb retry after class_gate fixes 4783bc7256e, 62293cb43e1,
and 0d695d658a1; base `a518c2c963fd`): the official composer absorbs
28 approved donors into `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp`.
`./build.sh` verifies 212/212 matched rows with zero row identities lost;
CSV and frozen-source checks pass. LinkGuard and ProviderGuard admit the
composition using freshly fetched index SHA-256 `d1d043b3a395600da212d61d693c571e8fa570dddb3c1f42741984890ef3c324`
(meta `50ce6f90bb`, census `50ce6f90bb`).
This is partial source consolidation, not a new census or full-image/runtime
result; historical evidence and unrelated prerequisites remain in force.
The separate constructor/destructor and observer-identity work above is not
cleared by these source moves.
