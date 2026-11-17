# MeshGeometryClass header cohort: bounded result

The picker served 15 queued consumers. Two already used the canonical
geometry declaration through `MeshModelClass.h` but lacked a direct include:
`MeshClassCastRay.cpp` and `MeshClassCollision.cpp`. Adding the direct
`MeshGeometryClass.h` include preserves all 11 rows. The owning
`header_adopt_lane.py accept` passes both and retires only their two entries.

The other 13 consumers remain queued and unchanged. The command
`header_adopt_lane.py run --class MeshGeometryClass --dry-run` did not
complete, so it supplies no cohort pass or failure count:

- The trial layout compile for `MeshLoadContextAddLegacyMaterial.cpp`
  consumed about eight minutes of CPU in MSVC 7.1 under Wine without
  returning. Its specific compiler process was terminated.
- The later byte-gate compile for `ScriptConditionsPlayerUnitCounts.cpp`
  similarly kept consuming CPU without returning. The parent trial was
  interrupted and its compiler terminated. The tool's `finally` blocks
  restored all temporary source changes; the remaining tree diff was
  checked before making the two direct-include changes.

No compiler result was accepted for either interrupted trial, and no
queue entry for those 13 units was removed. Their existing queue diagnostics
remain the starting points: differing member/array views and imported
RefCount/Vector declarations need per-unit reconciliation. Reproduce the
problem on the supported compiler host before diagnosing the CPU loops
as a source defect or checker defect. Do not treat the interrupted dry run
as a successful adoption or a false reject.
