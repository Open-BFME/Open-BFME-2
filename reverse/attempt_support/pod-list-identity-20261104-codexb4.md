# POD list identity retirement: current-object prerequisite

Inspected `4addfa9b0c`, 2026-11-04. Scope:
`Code/Libraries/Source/WWVegas/WWLib/stlport_pod_list_bodies.cpp`, selected
`_M_create_node<BfmePod60>` at 0x004E548D.

The source already inlines the Pod60/72/124 `_Construct` adapters into calls
to the rowed element-owner specializations. No source change was necessary.
`./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_pod_list_bodies.cpp`
passed all 42 rows, string/float/import checks and two STLport constructor folds.

`repair_queue.py retire identity` refused without changing the register:

- 186 ledger objects were missing, so kept-copy identity was unknown.
- Five referenced-provider objects were not proven current; the example was
  `Code/GameEngine/Source/Common/StringRecordCopyBFME2.cpp`.
- New findings included the Pod196 unwind action `$L11039` calling its
  `_List_base` destructor at 0x004EC395, and Pod32 `_M_insert_dispatch` and
  `push_back` binding `insert` at 0x000BC180.

The latter family is also recorded in the earlier 0x000BB6CC / 0x000BCE1C
attempts. Next: rebuild the missing/stale provider cohort, establish the kept
Pod32 insert/node-creator and Pod196 destructor copies against retail, then
rerun the owning retirement tool. No debt was retired; no linking or census
gain is claimed. The scope and RVA claims were released.
