### LINK-668: a generated canonical header drops an override of an indirect base's virtual, so its vtable-emitting unit installs `__purecall`
Status: Open (one instance; needs a header_adopt_lane fix or a maintainer's regeneration). Updated: 2026-11-13
(seat halilkkaya-rg1); base `d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Symptom.** MonitorConditionUpdate.cpp: census 2026-11-13 01:15 (`e5da954ea6`) "yes", 334 B; census 04:18
(`6e37424cf7`) "no". link_check: comdat `??_7MonitorConditionUpdate@@6BObjectModule@@@` "differs from the first
copy in link order (no retail address)".

**Cause (target facts and object facts).** "Register canonical MonitorConditionUpdate in 3 units" (`cca32fa5dd2`,
StarkillerHDX) replaced FamilyDeletingDtors_muse-2c79.cpp's private view with the generated
`Common/MonitorConditionUpdate.h`. The view declared `virtual NameKeyType getModuleNameKey() const;` ("so both
units emit one primary table"); the header declares `~MonitorConditionUpdate`, `update` and `xfer` only. The unit
still emits the class's tables through its `MonitorConditionUpdate(EmitVtableTag *)` scaffold, which it needs for
the rowed `??_GMonitorConditionUpdate@@UAEPAXI@Z` (0x00491750). Its ObjectModule table now has `__purecall` at
slot 4. MonitorConditionUpdate.cpp's copy has `?getModuleNameKey@MonitorConditionUpdate@@UBE?AW4NameKeyType@@XZ`,
as retail table 0x0084DAD8 does (slot 4 = 0x00491667). The two copies differ only there. FamilyDeletingDtors comes
first in link order, so MonitorConditionUpdate.cpp loses. The contract itself records the retail slot
(`retail_vtables["0x84dad8"]["4"]`).

**Why the generator dropped it (inference from the code, not tested).** `header_adopt_lane.slot_declarations`
counts a view's virtual as an override only when `base_slot_signatures` finds its signature. That function reads
only the registered headers of the contract's direct `bases` (here `GameLogic/Module/UpdateModule.h`), not their
own bases. `getModuleNameKey` is declared in `Common/Module.h` (Module <- ObjectModule <- BehaviorModule <-
UpdateModule), so it is neither an override nor one of the contract's own slots, and it is silently left out.
`update` and `xfer` survive because UpdateModule.h declares them.

**Fix (not applied).** No unit-local repair exists: the header is generated (never hand-edited), a private view of
a registered class is refused, and 0x00491750 has no approved TU in `reverse/tu_map.csv` (displaced), so its row
cannot move to MonitorConditionUpdate.cpp, which emits an identical `??_G`. The repair is in the tool:
`base_slot_signatures` should follow each base's registered contract `bases` transitively. Then regenerate this
header so it declares `virtual NameKeyType getModuleNameKey() const;` (the old view's spelling; `NameKeyType` needs
the header's include). Expected result: FamilyDeletingDtors' table equals MonitorConditionUpdate.cpp's and
retail's, and MonitorConditionUpdate.cpp links again (+334 B). Check the other generated headers whose classes
derive from a module base the same way: FXListDieConstructor.cpp's `??_7FXListDie@@6BObjectModule@@@` has
`__purecall` at slots 1-4 (not measured as a census loss).

**2026-11-13, later.** The tool fix was not attempted: `file:tools/header_adopt_lane.py` is claimed by
`ancalgonn-swarm-toollane2` (claims.py dry-run: held).
