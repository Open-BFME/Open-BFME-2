# SidesList consolidation attempt, 2026-11-04 (codexb4)

Inspected revision: `95cde072d3`. Census index: `a62ac1c10b`, 2026-11-04 07:28.
No game source, ledger, debt register or TU map was changed by this attempt.

## Verification and scope

- `check_csv.py`: PASS (99,440 functions, 9,336 symbols, 2,269 data rows).
- Required planner: `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Map/`; its snapshot freshness check passed after the trial removed its temporary source.
- `find_declared_unmatched.py`: PASS for the seed and all 45 candidate donors.
- `./build.sh Code/GameEngine/Source/GameLogic/Map/SidesList.cpp`: 59/59 PASS, including EH funclets and string/float/import checks. Original verified object SHA-256: `7093d8d2f250c5cbfdbf389f8297fc6bee4f2cb1e99b842ad94caad07934253a`.
- `tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Map/SidesList.cpp --dry-run`: exit 0 after approximately 38 minutes. The tool rebuilt the stale committed map in memory (454 approved rows), kept the seed and accepted `Common/Rva0032AF56Destroy.cpp` and `GameLogic/Map/Rva0019B780Lookup_Rva0032d0b5.cpp`. Its reported score is 58; the three sources hold 62 ledger rows altogether, including shared addresses and EH rows. The tool checked byte preservation and census link dependencies. Other donors remain separate.
- The accepted lookup donor carries two `/alternatename` entries. The plan transfers both through the hatch register; none was removed or called dead.
- Actual application exited 2 before editing: `held by another worker: 0x0007FAB3, 0x000B3FD0`. Do not force or bypass those claims. The dry-run plan is cached locally under `build/tu_skeleton/plans/`; a later application must reverify it and claim its complete scope normally.

## Rejected linked donor

`Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_vector_pod128.cpp` was rejected by the link guard:

```text
links at the census; the merged object would not:
comdat ??1?$pair@$$CBHV?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@@_STL@@QAE@XZ (retail)
```

This is a rejected composition, not a regression in the unchanged donor. Before adding it to SidesList, reconcile the emitted `pair<const int, vector<BfmePod128> >` destructor with the retail copy and its vector/allocator context. Recheck its own rows and affected consumers. Census confirmation is not claimed.

## Other prerequisites and audit preparation

The remaining donors predominantly fail composition on private/canonical class collisions (Coord2D/Coord3D, Dict, DataChunk, SubsystemInterface), Snapshot surface requirements, incompatible TeamsInfoRec declarations, or private STL declarations. `Common/Rva0032B610Compare.cpp` fails byte verification under the selected composition. The original classes and bodies were left intact; these are cleanup prerequisites, not missing retail coverage.

`tu_views.py --dry-run` identified conflicting BfmeE8 field spellings, parser base destructor declarations, Rva0032989F inheritance, Rva00196D90Element constructors, BfmeThingUBB fields and TeamsInfoRec layout. No view was automatically reconciled; matching storage size alone does not establish type identity.

The preliminary path search covered the 46 paths and donor basenames across tools, hooks, workflows and Code. No active tool/workflow consumer was found. Three header comments refer to other rejected donors. The source/JSON search found no include of a donor source; those hits were not exhaustively classified because no move was applied. Because nothing moved, no outgoing source-path audit or debt transfer was needed. A future merge must audit its actual outgoing range immediately before publication.

Next step: wait for the two RVA leases to clear, then rerun the supported planner freshness check and ordinary merge application. Keep the rejected STL donor out until its destructor prerequisite is repaired.
