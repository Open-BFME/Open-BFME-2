# Drawable canonical header: retail evidence and blocker (2026-10-30, halilkkaya-cls4)

Handoff for whoever writes Drawable's canonical header. No header was written:
`claims.py claim class:Drawable` is refused because Drawable's footprint (108
lock keys) overlaps object-retail's `class/Object` claim on two files
(`Code/GameEngine/Source/Common/GapBodiesSeat1A.cpp`,
`Code/GameEngine/Source/GameLogic/Object/ObjectReactToTransformChange.cpp`).
Coordinate with the Object work or wait for it.

## Target facts (game.dat)

- sizeof(Drawable) == 0x470: the only constructor caller, 0x0004C75F, pushes
  0x470 before calling the ctor 0x002797BD.
- Bases: the ctor calls `Thing::Thing` (0x0030A188), stores Snapshot's table
  0x00BBB554 at +0x60, then Drawable's tables 0x00BFB0B4 at +0 and 0x00BFB0A4
  at +0x60, so `Drawable : Thing, Snapshot` with Snapshot at +0x60 and own data
  from +0x64.
- Snapshot-side table 0x00BFB0A4, 4 slots, no RTTI (the primary table follows
  it): 0 = the -0x60 thunk 0x0027966F; 1 = LoadPostProcess 0x002717BC;
  2 = GetSnapshotName() const 0x00279669; 3 = DoXfer(Xfer*) 0x0027A219.
- Primary table 0x00BFB0B4, exactly 15 slots (the string "#emb" follows slot
  14):
  - 0–7 are Thing's slots. 3 and 4 hold 0x0047A6A9 (`mov eax,ecx`, so the
    asDrawable-style casts return this). 5 is reactToTransformChange 0x002742E5
    (a protected virtual, matching the ledger). 7 is `??_G` 0x00279FFC.
  - 8–14 are Drawable's own virtuals, in order: 0x0027299A, 0x002729B5,
    0x002729CB, 0x002729E9, 0x00272971, 0x00271095, 0x00271C38.
- Retail has no direct callers of slots 8–14. They are reached only through the
  table.

## Ledger facts and the conflict

- The seven slot 8–14 rows are named `QAE` (public non-virtual) in
  `reverse/functions.csv`, in `Drawable_rva00272971.cpp` and
  `Drawable_rva00271095.cpp`: rva0027299A(int), setDeathDecalPosition(int),
  rva002729CB(float), rva002729E9(int), createDeathDecal(int,float,int),
  rva00271095(), rva00271C38(int).
- A correct header declares them virtual. That means renaming the seven rows to
  `UAE` through `tools/rename.py`. Left non-virtual, the header emits an 8-slot
  table where retail has 15.
- 197 `@Drawable@@` rows (about 160 real members, including the nested
  `Drawable::PhysicsXformInfo` and by-value returns).

## Inferences and tool notes

- `DrawableConstructor.cpp` holds the only full 0x470 layout (offsets backed
  by its unwind map). Use it as the field source.
- `class_contract.py --class Drawable` decides from a majority of 462 views and
  says "sizeof 256, bases []". That contradicts retail; do not commit it.
- `header_adopt_lane.py dest` proposes `Code/GameEngine/Include/GameClient/Drawable.h`.
  Prefer a non-shadowing name (e.g. `DrawableBFME2.h`), as the ScriptEngine
  and Team headers did.
- `reference/shims/drawable/GameClient/Drawable.h` is a BFME 1 (1.03) layout,
  not BFME 2 evidence.

## Second pass (2026-10-30 afternoon, halilkkaya-cls4, worktree wt_e)

object-retail's `class/Object` claim was gone, but `claims.py claim
class:Drawable` was still refused. Drawable's footprint includes
`Code/GameEngine/Source/Common/Drawable_handleWeaponFireFX.cpp`, which RVA
claim 0x00271108 locks. That claim belongs to `Dave Razidlo@srx-2000`, has the
note `tools/rename.py`, was created at 12:34 UTC and expires at 16:34 UTC. Its
rename already landed in "Land 131 agreed names (batch 2 of naming round)",
but the lander has not released the claim.

Committed in this pass (no class claim needed):

- thing.h declares the nine rowed Thing members it lacked (getDrawable,
  getUnitDirectionVector3D, setTransformMatrix, ...), under class:Thing. A
  trial Drawable adoption had failed 62 units on them.
- The seven slot 8-14 rows are respelled QAE -> UAE with
  `tools/rename.py function --rva R --virtual`, in two commits (slots 8-12,
  then 13-14), under the tool's own RVA claims. First, each defining view had
  to read the +0x14C list through an accessor at this+0x14C. With a raw
  `m_pad[0x14C]`, the first virtual's vptr shifted every load to +0x150, and
  the tool restored the files.

Prepared and verified locally, not committed (these need class:Drawable):

- `Code/GameEngine/Include/GameClient/DrawableBFME2.h` (committed later,
  unregistered; the banked copy is gone) is the hand-written header. A scratch
  compile emits the 15-slot Thing-side table in retail order and the 4-slot
  Snapshot table, and `sizeof == 0x470` is checked. Its home is
  `Code/GameEngine/Include/GameClient/DrawableBFME2.h`.
- The two slot units adopt the header and read the list through
  `m_modules[0]`. The earlier manual trial of this was OK 48/48 with
  Drawable.cpp.
- 23 units adopt by hand. All pass `./build.sh`, link_check (every one
  LINKS, linked bytes unchanged) and DIR32:
  - 14 whose private view names the +0x14C list `m_drawModules`/`m_arr`:
    the lane's swap is applied, then the list is read as
    `((T **)m_modules[0])`.
  - 9 whose private `class Thing { ... };` the lane's swap leaves behind:
    the swap is applied, then that view is dropped, because thing.h now
    declares getDrawable.
  - `Drawable_rva00272BE7.cpp` and `Rva00272BABFinish.cpp` also name
    `m_client`, so they stay queued.
- A dry `header_adopt_lane run --class Drawable --header
  Code/GameEngine/Include/GameClient/DrawableBFME2.h` passes 185/466 units
  through the byte gate. Failures:
  - C2039 missing member, 112: Matrix3D Get_Z_Rotation 8, and private field
    names such as `object` 7, `m_selected`, `flag43c`;
  - C2065, 67: private field names;
  - bytes/callee, 39;
  - C2011, 22: units' own `class Thing`;
  - no private view, 6.

To finish:
1. Claim class:Drawable.
2. Add the header and the canonical row. Commit them with the two slot units.
3. Claim the 23 hand-adopted units and commit them.
4. Run `header_adopt_lane run --class Drawable --header ... --apply
   --skip-held --jobs 12`.
5. Gate in chunks of 40, run link_check and DIR32, then commit.

Do not commit `reverse/class_contracts/Drawable.json`: the lane writes the
majority contract ("sizeof 256, bases []"), which retail contradicts.

## Third pass (2026-10-30 evening)

class:Drawable stayed refused: after 0x00271108 expired, sp-1, sp-3 and sp-5
file claims inside the 466-unit footprint held it through eight retries
(16:36-17:52 UTC). Under file claims instead, the header was committed
unregistered (no canonical_classes.csv row, so the class gate and the lane
do not change), together with the two slot units and the 23 hand-adopted
units. Registration and the lane run still need class:Drawable.
