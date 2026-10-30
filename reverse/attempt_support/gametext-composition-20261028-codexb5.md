# GameText composition investigation

At base `b4358c8a12a5`, the default picker claimed the GameText destination and ten whole-file donors. The consolidation catalogue reports duplicate private views, differing compiler settings, mixed or incomplete routing, and a stale committed TU map; its grouping is an investigation hint, not placement approval. The supported merge tool rebuilds the map when needed.

`tu_views.py` tried reconciling the private views and ran the supported merge dry run before and after. Both trials accepted zero donors. The tool's verified `Rva002E6451` and `StringLookUp` view changes did not make a donor mergeable and were restored. Its GameTextTable trial failed one of 31 rows and renumbered EH labels; its Rva002E5791 trial failed to compile; GameTextManager has conflicting base clauses. The other donor failures included missing fields or declarations, duplicate `StringBase` definitions, and byte mismatches in the find and sort donors. No source change or merge is retained.

Next investigate the GameTextManager base/interface and member declarations against the target ABI, and separately the table and string template contexts, before repeating composition. The catalogue's placement warnings must also be reviewed; no new source-file or link gain is claimed.

## Update 2026-10-30 (after the 7-file merge bd28601b65)

The supported dry run at 9bf10df619 still accepts zero of the four remaining donors:

* `Rva002E5791Dtor.cpp`: composes and byte-matches once the seed defines
  `BFME_STRINGBASE_PUBLIC_DTOR` before its first string header (9bf10df619;
  seed 34/34 and both data rows unchanged). The link guard then refuses it
  because the merged GameText.cpp has no census object yet (the 04:25 census at
  6fe1089c24 predates bd28601b65). Retry after the next census.
* `GameTextCreate.cpp`: C2440, because the seed's GameTextManager derives directly from
  SubsystemInterface. Target facts: vtable 0x00804E90 has GameTextManager's
  (0x00804FA8) 22 slots, with purecall wherever the manager overrides, and the
  manager's destructor 0x002E66F2 stores it before calling ~SubsystemInterface
  0x001B4E74. The constructor 0x002E63AA stores only 0x00804FA8 after the
  SubsystemInterface base constructor 0x001B4E63. The intermediate store is
  absent, consistent with a dead-store-eliminated inline base constructor.
  0x00804E90's owner is the placeholder class `Rva002E55D8`
  (GameEngineDeletingBaseDerived.cpp and GameTextManager.cpp's
  `Rva002E66F2Mid` view). Its agreed name `GameTextInterface`
  (`reverse/name_agreed.csv` nl-99bc35368af6) is blocked by the many private
  `GameTextInterface` views (`name_lane.py reconcile --key
  'Code/GameEngine/Source/Common/GameEngineDeletingBaseDerived.cpp|class||Rva002E55D8'`).
  The seed needs that class as GameTextManager's base before this donor can
  compose; `canonical:zh` is refused because no Zero Hour body places there.
* `Rva002E6451Find.cpp` (`/O1 /Oi`) and `stlport_sort_stringlookup.cpp` (`/GX-`):
  bytes, from their own compiler settings; unchanged.
