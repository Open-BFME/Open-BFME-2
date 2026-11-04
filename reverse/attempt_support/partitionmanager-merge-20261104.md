# PartitionManager.cpp TU merge, 2026-11-04 (claude2)

Target facts: `reverse/tu_map.csv` approves `Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp`
for the donors below. `tu_skeleton.py --merge --dry-run` (tree after commit "Align 3
PartitionManager donors ...") accepted 9 donors: BfmeConv1570, BfmeConv1572,
Bfme5CeilCellExtent, Rva00739BE0, Rva00739AF0Siblings, Rva00739CA0, Rva00739D90Siblings,
ShroudVariantCircle008F9BB0, BfmeConv583.

Seed edits carried in the merge commit:

- `<math.h>` under `_CRTIMP = __declspec(dllimport)` ahead of PreRTS.h (TerrainLogic.cpp's
  recipe), so donors' `dllimport floor/ceil` declarations no longer give C2375. Adding `/MD`
  to the seed instead needs `/D_STLP_USE_STATIC_LIB`, which changes the
  `_STLP_alloc_proxy<HorzLine>::deallocate` COMDAT, and the link guard refuses that.
- `Gen_008F7CD0::rva0073CE90` declared.
- `BfmeThingCDE` widened to the union of the donors' views. Field names follow the seed.

## Donors still rejected (next steps)

| donor | wall | next step |
|---|---|---|
| BfmeThingCDEDestructor.cpp, Rva008F7B00Get.cpp, ShroudManagerDataDoSmallFill.cpp | `reference/shims/bfme2_ascii/ascii_string.h` redefines `AsciiString` from PreRTS.h. They include it directly or through ShroudManagerClass.h → SubsystemInterface.h | Move ShroudManagerClass.h / SubsystemInterface.h off the shim and onto the real AsciiString (a header-lane change), then re-run the dry-run. |
| PartitionData_maybePrepend.cpp, ObjectFields.cpp | include `Include/GameLogic/PartitionData.h`, which redefines the seed's `PartitionData` | Adopt the canonical PartitionData header in the seed through the header lane (adopt_first). |
| PartitionDataShroudStatus.cpp | private `CellAndObjectIntersection` view: in the seed's ZH class, `m_cell` is private | Read the field through a seed accessor, or move the seed to the donor's layout. |
| PartitionData_friendUpdateCellsTouched.cpp | C2761: the donor redeclares `friend_updateCellsTouched` | Drop the donor's redeclaration once the PartitionData view is shared. |

Logs from the dry-runs are in `build/pm_dry*.log` (scratch, untracked).
