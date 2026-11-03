# TerrainResourceManager.cpp merge: class views, 2026-11-03

Scope: `tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/System/TerrainResourceManager.cpp`
and its six rejected donors (Rva0035A1D8Clear, Rva0035A9C1Dtor, Rva00359E13Ctor,
TerrainResourceManagerCellClaim, TerrainResourceManagerClaimRva00359E93,
TerrainResourceManagerDoXfer). Earlier pass: [codex handoff](terrain-listener-consolidation-20261101-codex.md).

Done: `tools/tu_views.py` applied Rva00359835, Rva00481FAFFloatSlot, BfmePod8,
Rva00359BE8List and Rva00359E04Owner ("Reconcile five TerrainResourceManager TU
class views"). Six sources build at 55/55; nine renumbered funclet labels are relabeled.
The merge dry run still accepts 0 donors.

Remaining conflicts (from target facts in the sources; none of them is resolved):

- TerrainResourceManager: the seed uses a non-polymorphic pad view (`pad00[0x14]`,
  `Entry00359D42 *m_list` +0x14, `originX1C/originY20`, `ResourceCell *cells40`).
  DoXfer declares `virtual DoXfer`, `list<BfmePod12>` +0x14, `Region3D` +0x1C and
  `Rva0035A18D *cells` +0x40. Unifying them needs one cell type and one
  list-node view, with the seed's raw node walk kept byte-exact.
- ResourceCell (seed `first/last/capacity/state`; CellClaim's `values`), and
  Rva0035A18D (seed +0 `string`; Rva0035A9C1Dtor +0 `vector<BfmePod8>`) are views
  of that one cell type.
- Rva0035A238Argument: `key74 -> key` collides with an existing `key` in ClaimRva00359E93.
- Rva0035ABC0: the plan does not compile in DoXfer (the tool reverted it).
- Rva00359E13Ctor: `extern "C" __identifier("??_7Snapshot@@6B@")` collides (C2373)
  with the canonical Snapshot class, which the seed (via BuffManager.h, AIPathfind.h,
  PlayerList.h) and Rva0035A9C1Dtor include without `BFME_SNAPSHOT_CONSTRUCTOR_ONLY`.
  Retail's constructor stores no Snapshot vptr, so the destructor units' inline
  canonical Snapshot base would add a store. This is a structural inference and
  has not been compiled.
