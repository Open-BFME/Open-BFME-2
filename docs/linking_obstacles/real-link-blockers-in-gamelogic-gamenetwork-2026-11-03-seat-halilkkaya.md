### Real-link blockers in GameLogic/GameNetwork (2026-11-03, seat halilkkaya-lk19)

From `reverse/exit_link_blockers.tsv` (real link at `96cfeda7ba`; 234 errors, 214 names in this slice).

- **FlightDeckBehavior.cpp, 49 names: repaired.** BFME 2 has no FlightDeckBehavior (no module string
  in game.dat, no native row). The Zero Hour port's out-of-line destructor emitted Zero Hour's
  FlightDeckBehavior and AIUpdateInterface vtables, whose 49 slots nothing defines. The unit now holds
  only its two retail rows: ExitInterface's base `getNaturalRallyPoint` (0x004624A7) out of line against
  canonical `ExitInterface.h`, and the runway-element `_Destroy` thunk (0x0008A64A) by explicit
  instantiation over the element view `FlightDeckBehaviorRunwayInfoDestructor.cpp` already uses. 2/2
  exact; scoped DIR32 OK; `link_check`: FlightDeckBehavior.cpp does not link -> LINKS (35 B); the
  consumers of its removed COMDATs (SupplyTruck/Dozer AIUpdate ctors) are unchanged (every removed
  definition referenced elsewhere has another definer). One present-unmatched hatch removed.
- **DeliverPayloadAIUpdate.cpp, 19 names: blocked on one consumer.** BFME 2 has no
  DeliverPayloadAIUpdate (no module string). Reduced to its one row (the 14-byte getter 0x000D1AB3,
  kept by an extern pointer anchor as in HackInternetAIUpdate.cpp), it builds 1/1 and links (0 -> 14 B),
  but `InGameUISuperweapons.cpp` (1,264 B, LINKS) then loses `??0RadiusDecalTemplate@@QAE@ABV0@@Z`:
  its view declares the copy constructor and only this unit's Zero Hour code emits one (no row).
  Joint `link_check`: LINKS -> does not link, so reverted. Prerequisite: give InGameUISuperweapons
  its own RadiusDecalTemplate copy (retail's) or a provider in its TU (GameClient). The reduced
  text is banked in `reverse/attempt_support/real-link-gamelogic-20261103-lk19/`.
- **HelicopterSlowDeathUpdate.cpp, 16 names: repaired (seat halilkkaya-lk20, real link at
  `d0b9cc5d27`).** Its one row `?isDieApplicable@SlowDeathBehavior@@...` 0x0045D49E is approved for
  `SlowDeathBehavior.cpp`, but that unit's native seed no longer emits it (`add_match
  --replace-existing` there: symbol not found; reverted). Re_attempts 86778 has the older layout trial.
  The 16 names were not the row: they came from the unrowed Zero Hour bodies (AudioEventRTS, Drawable,
  PhysicsBehavior, EjectPilotDie, and the Zero Hour `~SlowDeathBehavior`/`crc`/`loadPostProcess`). The
  unit now defines only the row, as an ordinary out-of-line override over canonical `UpdateModule.h`,
  `DieModuleInterface.h` and `SlowDeathBehaviorModuleData.h` plus a three-slot slow-death interface at
  +0x24 (retail table 0x00C42020 slot 2 = 0x0045D49E), no vtable emitted. 1/1 exact; scoped DIR32 OK;
  `link_check` 0 -> 22 B LINKS; orphan scan over 22,374 `build/match` objects: 725 names gone, 0
  referenced without another definer; the index shows Heli as the only object touching the row's name
  and no shared COMDAT where it was the kept copy. Eight present-unmatched hatches removed. The row
  still sits outside its approved TU; moving it into `SlowDeathBehavior.cpp` is now a plain rehome of
  this definition.
- **RailedTransportDockUpdate.cpp, 11 names: needs a definer first.** Its row
  `?getRailedTransportDockUpdateInterface@RailedTransportDockUpdate@@...` 0x004B01D9 (approved for
  SpecialDisguiseUpdate.cpp; `lea eax,[ecx-0Ch]; add ecx,7Ch; neg; sbb; and; ret`, a null-checked
  cast from the +0xC base to a base at +0x88) is an inline virtual emitted only through this unit's
  vtable, and `ModuleUpdateDtors.cpp`'s spelled table 0x00C562E4 references it. Dropping the
  destructor needs that getter defined under its real class first.
- **RadarUpdateConstructor.cpp / BattlePlanUpdateConstructor.cpp, 1 name each
  (`?crc@UpdateModule@@MAEXPAVXfer@@@Z`):** retail slot 2 of their primary tables (0x00C51A0C,
  0x00C4FBAC) is each class's own name getter, rowed as placeholders `?name@Rva004A0C27Named@@QBEPBDXZ`
  and `?name@Rva0049795ANamed@@QBEPBDXZ`. `#define BFME_SNAPSHOT_NAME_SLOT` alone would bind slot 2 to
  `UpdateModule::GetSnapshotName`, not retail's; rename those rows to the classes' `GetSnapshotName`
  and declare the override in each view.
