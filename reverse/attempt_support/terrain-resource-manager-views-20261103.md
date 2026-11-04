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

## 2026-11-04: all six donors merged

Landed as two merges (48 rows, then 60 rows), each after one verified
reconciliation commit per file. `TerrainResourceManager.cpp` builds 60/60 and
`find_declared_unmatched.py` is clean.

What settled each conflict (target facts first, then the spelling chosen):

- Rva0035A18D / ResourceCell: DoXfer's cell access and resize 0x0035ABC0 prove a
  16-byte `vector<BfmePod8>` plus state. Every view now spells that one class;
  the seed's raw `first/last/capacity` and `CellClaimant` views are gone.
- CRT bindings: retail calls floor/ceil through the imports (`ff 15`) but
  frees through the game's static `_free` 0x00030830 with extern "C" calls kept
  throwing. The TU now builds with `/D_CRTIMP=` and the base `/EHs /EHc-`, and
  wraps only `<math.h>` in dllimport (TextFile.cpp's pattern).
- Snapshot in the ctor (0x00359E13): retail's constructor stores no Snapshot
  vptr; the destructor (0x0035A9C1) does. The ctor keeps its novtable stand-in;
  its unwind destructor now runs the canonical `Snapshot::~Snapshot` body
  instead of declaring `??_7Snapshot@@6B@`, which cl refuses (C2373) beside the
  class. Structural inference: retail likely saw the base store dead under LTCG.
- TerrainResourceManager: the seed's pad view became DoXfer's layout (vptr,
  `list<BfmePod12>` +0x14, radius +0x18, `Region3D` +0x1C, dimensions, cell
  size, `Rva0035A18D *` +0x40). enumerateRegisteredClaimants walks the list
  with a cached end iterator; bytes unchanged.
- Rva0035A238Argument: the donor's `getKey()` getter is needed (dropping it
  shortens rva00359E93 by one byte). The seed forward-declares the struct so the
  merge can keep the donor's definition, and its present-unmatched marker
  travelled with the merge.

Still open (identity, not layout): Rva00359E13, Rva0035A9C1, Rva0035A1D8,
Rva0035A2DC, Rva0035A292, Rva0035A238, Rva0035A8D7 and Rva00359E04Owner are
all views of TerrainResourceManager (same +0x14/+0x1C/+0x40 layout; ctor and
dtor install vtable 0x00C153E0). `??1Rva00359BE8List@@QAE@XZ` sits at
0x0007FAB3, the canonical `Rva00330757Member` destructor, so those two names
are one class. Folding them into TerrainResourceManager methods is naming-lane
work (`tools/rename.py`).

Tool note: the first merge wrote the donor's `_ReadWriteBarrier` declaration and
`#pragma intrinsic` after the TU's last `#include`; a later re-composition of
the merged TU then hoisted the pragma above the declaration and lost
rva0035A1D8's row. Keeping both lines above the includes avoids it.

Link batch audit at the first push: INCONCLUSIVE (3 source objects without
current receipts, first `Common/TailJumpWrappers5B.cpp`, a mixed satellite of
this TU). Carry to the next census.
