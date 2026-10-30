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
