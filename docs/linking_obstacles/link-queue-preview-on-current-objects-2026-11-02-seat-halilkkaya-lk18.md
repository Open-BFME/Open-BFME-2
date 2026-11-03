### Link queue preview on current objects (2026-11-02, seat halilkkaya-lk18)

`next_work.py --tier link --ranked` (census 06:54, `357ce2a88f`) serves ten units. Checked on current
objects, with each unit's current sibling definers of the losing names included, seven units **LINK**:
- AutoPickUpUpdate.cpp 2,013 B (with AutoPickUpUpdateDtor.cpp);
- LivingWorldLogicDtorRva002B964F.cpp 717 B (with LivingWorldLogicCtorBfme.cpp);
- LivingWorldBuilding.cpp 1,124 B (with Rva004E0D67Dtor.cpp);
- RelationMapXfer.cpp 654 B;
- ScriptActions_doNamedEnterNamed.cpp 91 B;
- ReplenishUnitsBehavior.cpp 1,050 B (with ReplenishUnitsBehaviorDtor.cpp);
- MonitorConditionUpdate.cpp 334 B (with FamilyDeletingDtors_muse-2c79.cpp).

A single-path `link_check` still reports their sibling COMDATs as "differs from the first copy". That
comes from the stale census-index copies, not from current objects.

Still blocked:
- Rva000FDCD7Get.cpp (26 B): the address-named data global `g_00DB5BD4` (data lane).
- MapCacheAddMap.cpp and MapCacheLoadUserMapsBFME2.cpp (2,389 B): MapUtil.cpp's duplicate Zero Hour
  `addMap` (LINK-177 item 3). retail addMap 0x00304E64 is approved for MapUtil.cpp, but
  `tu_skeleton.py --merge MapUtil.cpp` is blocked: "TU path exists and holds rows of another TU
  (split it first)"; for example, 0x00181770 is approved for dx8fvf.cpp.
- DebugDestructorThunk.cpp, RtcStack.cpp and Rva008312E0StringReplace.cpp: LINK-175 records each one.

No repair, and no census confirmation is claimed.
