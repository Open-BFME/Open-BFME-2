# matpass.cpp consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/` — completed with no missing inputs; `tools/name_lane.py consolidate --check build/consolidation` passed.
- `python3 tools/tu_skeleton.py --plan Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp` — 14 approved rows, 6 pull donors, no mixed or refused files.
- `python3 tools/tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp --dry-run` — 0 accepted donors. `MaterialPassClassDestructor.cpp` and `MaterialPassInstallMaterials.cpp` each lose two rows under the carried empty override; `Rva0013EEB0Cluster.cpp` and `Rva0013EF40Siblings.cpp` have no baseline match; `MaterialPassClassCtorThunk.cpp` hits C2011 duplicate `RefCountClass` and C2084 duplicate destructor. The tool recommends `MaterialPassClass`, `RefCountClass`, `DX8Wrapper` and `RenderStateStruct` header adoption for the affected donors. LinkGuard lists all six donor objects and the destination as census-linked; no merged composition passed it.

No source, ledger or claim changed. The row mismatches, donor class/header conflicts and duplicate RefCountClass definition need owner-side reconciliation before another merge attempt.
