### Census 2c21184e84 unlinked-unit sweep: remaining single/dual blockers (2026-10-30, seat halilkkaya-lk8)

Status: informational handoff; no repair in this entry. `link_check --paths-from`
over the 182 census-unlinked units with current objects (index 2026-10-30 10:11
at 12b9e7a7c0): 10 already link post-census (9,283 B: the LINK-152/153/154
repairs and LINK-156), before LINK-157/158. Checked and left, with the cause:
- Placeholder class rowed for a real class (`rename.py class` refuses a merge
  into an existing class name, as in LINK-063): `LivingWorld/LivingWorldBuilding.cpp`
  (1,112 B) needs `??1LivingWorldBuilding@@UAE@XZ`, rowed as `??1Rva004E0D67@@UAE@XZ`
  (0x004E0D67; its `??_G` 0x004E0E5C is slot 0 of table 0x00C61618, which the
  LivingWorldBuilding ctor 0x004E119C stores); its `LoadPostProcess` slot 1 is the
  shared empty 0x000B3FD0. `LivingWorldManagerCtor.cpp` (363 B): table 0x00BE5234
  slot 0 is `??_GRva00214405@@UAEPAXI@Z` (0x002146B8), and four member ctor/dtor
  names resolve only through pins (0x0033C432, 0x00213E11 twice, 0x00210CC5).
- `MultiplayerSettingsCtor.cpp` (159 B): the QAE -> UAE respell above. Added
  evidence: retail 0x00381293 restores no vptr, the mark of an implicit
  destructor (as `??1DamageNugget@@UAE@XZ` 0x00508684), and Zero Hour's
  MultiplayerSettings declares none, so retail's TU emitted it beside the ctor
  and `??_G` (0x003811D8, 0x00381277, 0x00381293 are consecutive).
- `FireWeaponWhenDeadBehavior.cpp` (209 B) now has two blockers. (1) Its
  `??_7FireWeaponWhenDeadBehavior@@6BObjectModule@@@` (canonical ObjectModule)
  differs from `Rva00589079Derived.cpp`'s five-slot private view, the first copy.
  The unit includes `GameClient/BuffManager.h`, which defines
  `BFME_SNAPSHOT_CAPITALIZED_SLOTS`, so its lowercase loadPostProcess/s02/xfer
  become new slots 10-12 and slots 1-3 stay `__purecall`. Retail 0x008497B4 has
  13 slots: `??_G`, loadPostProcess 0x00482C39, getter 0x00482E4B, xfer
  0x00482BDB, getModuleNameKey 0x00482E51, four empty 0x000B3FD0, the `ret 8`
  onCapture 0x0050B238, two 0x004D43D0 and getUpdatePhase 0x0022C4CB. Both
  units need that one shape (donor on canonical ObjectModule, unit without the
  capitalized-slot define, or the TU merge). (2) `?update@UpdateModuleInterface@@UAEXXZ`
  is unresolved since `6e9a7c16cc` removed PartTheHeavensUpdate.cpp's link-wide
  alternatename that had served this unit's interface table too.
- `GameSpy/Thread/BuddyThreadClassCtor.cpp` (230 B): its `_STLP_alloc_proxy<char*>::allocate`
  copy is referenced only by `.debug$F`, so the import-inline specialization of
  `4bc55a5889` applies; not tried because a TU seat holds the file.
- Pin-only unresolved names (a pin steers the byte gate but defines nothing at
  link; rebind each to the row at its address, as LINK-158 did). Leads among
  unlinked units: `ConnectionManager.cpp` (map insert/lower_bound pins
  0x004D272E/0x0046A9AB), `MapUtil.cpp` (Dict::getType 0x0031317C,
  getWaypointName 0x0030D748, UnicodeString::set 0x00037150),
  `Rva0020EE29Clear.cpp` (six), the StlSweepW4 element families whose copy
  ctor/dtor pins land on real record rows (`StlSweepW4Rva001EBEAB.cpp` on
  CarryoverUnit 0x001EB79E/0x0037DEE4, `StlSweepW4Rva003F53DA.cpp` on ArmySummary
  0x0040E96D/0x0040E499), and `??1AudioEventRTS@@UAE@XZ` (0x004EC395, a folded
  `_List_base` dtor row) in ten units. Most of these units also hold other blockers.
