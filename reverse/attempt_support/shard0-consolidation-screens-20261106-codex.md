# Shard 0/5 consolidation screens (2026-11-06)

Each TU below passed `consolidation_queue.py --check-tu`, was planned after a
fresh parent-scoped `name_lane.py consolidate` run and passing snapshot check,
and was tested with guarded `tu_skeleton.py --merge ... --dry-run`. Every dry
run accepted zero donors. No merge was applied and no claims were acquired.

## `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineStats.cpp`

The plan has 75 approved rows, two donor files, and one mixed file. Dry run
exited 2 because `Code/GameEngine/Source/Common/Rva005BEA22Dtor.cpp` fails byte
verification. The seed's first adoption list includes `LivingWorldPlayer`,
`Player`, and `Rva00045411BitSet`. LinkGuard lists the seed and dtor donor as
census-linked.

## `Code/Libraries/Source/Apt/AptDate.cpp`

The plan has 84 approved rows, two donor files, and one mixed file. Dry run
exited 2 because `AptDateLookup.cpp` uses `objectMemberLookup` absent from the
destination `AptDate` view (C2039/C2270). The tool requests reconciling
`AptDate` and `AptDateNativeCache` views. LinkGuard lists the seed and lookup
donor as census-linked.

## `Code/GameEngine/Source/Common/Glo012F1024Item.cpp`

The plan has 140 approved rows, four donor files, fourteen mixed files, and one
refused file (`Rva00566695Assign.cpp`, one row not approved for this TU). Dry
run exited 2 with no accepted donors. `PAVectorEraseRangeFamily003AF.cpp`,
`Rva00565898Erase.cpp`, and `Rva0056644EOverflow.cpp` each failed byte
verification. LinkGuard lists the seed and the latter two donors as
census-linked. Do not split mixed sources to work around the refusal; the split
lane requires its own accepted guarded trial.

## `Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp`

The plan has 91 approved rows, three donor files, and ten mixed files. Dry run
exited 2 with no accepted donors. `Rva001171B0Cluster.cpp` hits MSVC internal
compiler error C1001 in `WW3DClass.h`; `Rva00118660Render.cpp` has duplicate
`RenderingMethodStackType` and `RenderInfoClass` declarations. LinkGuard lists
the seed and both donors as census-linked. Header/compiler repairs are outside
this mechanical lane.

No source, ledger, map, or claim changes were made. The errors above are current
prerequisites for other contributors; continue with another allocated TU
instead of repeating these unchanged trials.
