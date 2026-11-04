# FlammableUpdate merge prerequisites, 2026-11-04

Inspected revision: `4797c3abff`. The supported consolidation planner was
regenerated under `Code/GameEngine/Source/GameLogic/Object/Update/`.
Its placement hints are not merge approval; `tu_skeleton.py` rebuilt the stale
TU map in memory and used its current approved rows.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdate.cpp --dry-run`
accepted no donor. The current candidate set has three donors, rather than the
older nine-donor attempt: `FlammableUpdateDtor.cpp` fails on `boneName` after
composition selects canonical `TreeKey00242F5E`; `CameraMarkerVecErase.cpp`
and `stlport_copy_camera_marker.cpp` fail bytes. All four units are census-linked
according to the merge guard. Five mixed files remain outside the merge.

Tested the earlier frame-pointer hypothesis by adding `/Oy-` to the seed's
compiler flags and running its normal scoped `./build.sh`. This is insufficient:
it loses getModuleNameKey, the ModuleData deleting destructor, uninitialized-copy,
uninitialized-fill, Rva0048CACC and the ModuleData constructor, plus the exact
parent location for `$L310`. The compiler changes ESP-relative accesses to an
EBP frame in several bodies; the constructor also introduces an unresolved
vector-base constructor call. No pragma, override, pin or alias was added.

The trial was restored immediately. A normal rebuild passes all 31/31 seed
rows, its existing funclet locations, STLport fold, string, float and import
checks. The source diff is empty. No source, ledger or debt key moves.

The canonical TreeKey class claim is held by another worker, so no consumer
adoption was attempted. Next: reconcile the destructor's pointer/string view
with the existing unsigned/string canonical header under an available claim,
verify its normal bytes and EH graph, then retry composition. The camera
helpers still need a source/codegen explanation that preserves the seed;
TU-wide `/Oy-` is now a measured rejected hypothesis. No merge, debt retirement,
linking gain, census update or runtime test is claimed.
