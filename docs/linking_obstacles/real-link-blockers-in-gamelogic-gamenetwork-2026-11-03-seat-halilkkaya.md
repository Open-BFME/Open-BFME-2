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

#### Seat halilkkaya-lk20 follow-up (2026-11-03, real link at `d0b9cc5d27`)

Method for every repair below: list the names the unit's object defines, check in the census index
(23b85ddde5) that no other object references any of them without another definer, delete the unrowed
Zero Hour bodies, keep every row (a member-pointer anchor where a header inline row lost its only
emitter), then rebuild, compare the old and new objects' undefined sets, run the orphan scan over all
22,374 `build/match` objects and `link_check` the unit's siblings. Each commit body has the receipts.

- **ConnectionManager.cpp, 42 names: 40 repaired.** 51 unrowed Zero Hour methods dropped (retail's
  are rowed in the `ConnectionManager_*.cpp` units); 33 rows, TheDisconnectMenu and the map anchors
  kept. Orphans 0; the 38 sibling units LINKS unchanged. **Remaining 2:**
  `Rva004D272EMapHintInsert::insert` and `Rva0046A9ABMapLowerBound::lower_bound`, the pinned adapters
  the operator[] row 0x004D2941 calls (the recorded 4D2941 identity prerequisite; see
  `connectionmanager-remaining-type-ownership-cohort-handoff-2026-11-03.md`).
- **Weapon.cpp, 24 names: repaired.** Zero Hour field table, fireWeaponTemplate, privateFireWeapon,
  fireWeapon, the copy constructor (Zero Hour Weapon vtable) and two line-of-sight overloads dropped;
  `setLeechRangeActive` (0x002D95FE, no approved TU) kept by an anchor. `link_check` 0 -> 217 B LINKS.
- **WeaponSet.cpp, 6 names: repaired.** Three Zero Hour WeaponSet methods dropped; the
  parseWeaponTemplateSet table's "Conditions" entry now points at retail's 0x002C8C06
  (`Rva002C8C06Parse`), per retail table 0x00C00A90, instead of Zero Hour's BitFlags parser (static
  `INI::scanIndexList`). The rest of that table still differs from retail's (OnlyAgainst,
  OnlyInCondition, ReadyStatusSharedWithinSet, DefaultWeaponChoiceCritera are missing). The census still
  blocks the unit on its `??_7WeaponSet` copy.
- **StealthUpdate.cpp, 18 names: repaired**, together with SpawnBehavior.cpp's unrowed
  `areAllSlavesStealthed`, the only outside caller of `allowedToStealth` (SpawnBehavior.obj emits no
  vtable). `getPlayerNightColor` (0x00509D29, no approved TU) kept by an anchor. `link_check`
  0 -> 16 B LINKS.
- **BuddyThread_Unresolved.cpp, 5 names: 2 repaired.** Retail table 0x00C6B014 follows Zero Hour's slot
  order. Slot 3 `isThreadRunning` (0x00550609) and slot 5 `isConnecting` (0x003889E8) are folded with
  GameSpyPeerMessageQueue's rowed bodies and are now ICF twin rows (fold-proof=PeerThread.cpp).
  **Remaining 3, renames needed:** slot 2 `endThread` is 0x00550B4C (placeholder
  `?rva00550B4C@Rva00550B4C@@QAEXXZ`, BuddyThread.cpp); slot 4 `isConnected` is 0x00550618
  (`mov al,[thread+0x52]`) and slot 10 `getLocalProfileID` is 0x00550626 (`mov eax,[thread+0x54]`),
  both placeholders in Common/VslotSmallBodiesAM.cpp. Each needs the owner row renamed with a naming
  basis; a second name on the address is not allowed.
- **Checked, not repaired:**
  - DumbProjectileBehavior.cpp (10) and JetAIUpdate.cpp (9): still parked as LINK-072 records.
    DumbProjectile's row `UpdateModule::getUpdatePhase` (0x0022C4CB, displaced) is a virtual inline that
    78 objects emit; it cannot be anchored and has no approved unit to move to.
  - BodyModuleCtor.cpp (2): the canonical `BodyModuleClass.h` declares `getBody` and `vslot12`, and
    nothing defines them. Retail BodyModule tables: behavior-interface 0x00C5AD78 slot 0 is 0x002533D3,
    the null-checked `+0x10` cast folded with `getDie@DieModule` and `getUpdate@UpdateModule`; primary
    0x00C5AE68 slot 12 is 0x0050B5C6 (`mov al,1; ret`, placeholder `Rva0050B5C6`). The fix is two ICF
    twin rows defined in BodyModuleCtor.cpp, but both RVAs are claimed by StarkillerHDX@fleet
    (class:AIUpdateInterface/LocomotorSet), so they were left alone.
  - BoneFXDamage.cpp (3) and LockWeaponCreate.cpp (2): the rowed constructors emit Zero Hour vtables
    (DamageModule crc/xfer/loadPostProcess; LockWeaponCreate onBuildComplete/xfer). Each needs the retail
    table's slot owners named first.
  - EvacuateDamageCtorModuleFactoryBody.cpp (1) and BFMENetwork.cpp (7): their rowed constructors call
    names that are only pins onto other rows (`??1PB_DeepBase` to 0x0002CCC3; `??0BFMENetworkState` to
    0x00007850) or that have no provider. These are identity work, not body drops.
  - AIUpdate.cpp (5): the file is claimed by another worker.
  - RadarUpdateConstructor.cpp: its getter row 0x004A0C27 is in Common/ModuleNameGetters3.cpp (Codex's
    slice).
- **Update, same seat, later on 2026-11-03.** The three remaining GameSpyBuddyMessageQueue slots are
  repaired with the new `rename.py function --to-class` (f85f1a2f75; docs/naming.md):
  - endThread (0x00550B4C, BuddyThread.cpp);
  - isConnected (0x00550618) and getLocalProfileID (0x00550626), both in Common/VslotSmallBodiesAM.cpp.

  All five Buddy names now resolve in a joint `link_check`. BattlePlanUpdateConstructor.cpp and
  RadarUpdateConstructor.cpp were not attempted:
  - `class:BattlePlanUpdate`, 0x004A0C27 and ModuleNameGetters3.cpp are claimed by StarkillerHDX@fleet.
  - Each also needs installer-view work first. The dry run shows the compiled tables disagree with
    retail outside slot 2 (the ctor unit's `??_7BattlePlanUpdate@@6BObjectModule@@@`: 6 slots agree,
    4 differ; `??_7RadarUpdate@@6BObjectModule@@@`: 7 agree, 3 differ). The to-class slot check
    requires those slots to agree before it accepts the move.

#### Seat halilkkaya-lk21 follow-up (2026-11-04, real link at `4272054b98`, census index `8661f15284`)

**Repaired: 23 names.** Every drop below had an orphan scan, and every COMDAT the object held first
in link order had a joint `link_check` over all of its definers and referrers (91 units, 0 LINKS ->
not linking).

- **BodyModuleCtor.cpp, 2 names (82cbff63b5).**
  - `getBody` is retail BI-table 0x00C5AD78 slot 0 = 0x002533D3. `vslot12` is primary 0x00C5AE68
    slot 12 = 0x0050B5C6.
  - Both are defined in the ctor unit and rowed as ICF twins (fold-proof CreateObjectDie.cpp /
    VtableConstantPredicates.cpp).
  - The StarkillerHDX claims on both RVAs had expired.
- **DeliverPayloadAIUpdate.cpp, 19 names (a220f68d19).**
  - lk19's banked reduced text is now live.
  - InGameUISuperweapons.cpp no longer declares RadiusDecalTemplate's copy ctor out of line. Its
    private view now derives from canonical `Common/BfmeStringRecord000B94D2.h` plus the canonical
    tail fields, so the compiler generates the copy where the hash_map node construction needs it.
  - Retail's copy is 0x0029E067, reached through operator[] 0x002A3FAF -> pair 0x0029FB63. It is
    still rowed under the placeholders `Rva0029E067` / `Rva002A3FAFRecord`. Renaming that owner to
    `??0RadiusDecalTemplate@@QAE@ABV0@@Z` is open naming work.
  - `header_adopt_lane accept --class BfmeStringRecord000B94D2` for InGameUISuperweapons was refused
    before this landed: the census still had DeliverPayload's copy first. Retry it after the next
    census.
  - Locomotor::setFlag's kept copy is now AIFollowPathStateMethods' retail one. The five units
    fa51ed6f74 protected all still LINK.
- **SpectreGunshipUpdate.cpp, 2 names (1197d32fab).**
  - The ZH `initiateIntentToDoSpecialPower` is gone. It also emitted the census's one wrong
    `Locomotor::setFlag` copy.
  - The protected inline row `setLogicalStatus` (0x00238D83) is kept by a derived struct's static
    member call (absent-from-retail). A member-pointer constant became a .CRT$XCU dynamic
    initializer for this multiply-derived class.
  - Unit 0 -> 10 B LINKS.
- Hatch register -4 present_unmatched (8efc5bbe6b).

**Checked, not repaired (what each needs):**

- **BoneFXDamage.cpp (3) and LockWeaponCreate.cpp (2):** the retail primary tables carry BFME 2's
  slot order, not Zero Hour's.
  - BoneFXDamage 0x00C598B4:
    - slot 1 loadPostProcess 0x00497805, placeholder `Rva00497805`;
    - slot 3 xfer 0x0045CE8C, placeholder `Rva0045CE8C`;
    - no crc slot.
  - LockWeaponCreate 0x00C592FC:
    - slot 1 is the same 0x00497805;
    - slot 3 xfer 0x004851E3.
  - BFME 2's DamageModule (0x00C598E4) has no crc slot either. Its loadPostProcess is 0x0058B03E
    and its xfer 0x004CE56D (`Rva004CE56D`). No object defines `?xfer@` / `?loadPostProcess@` /
    `?crc@DamageModule@@`.
  - 0x00497805 sits in both an unrelated DamageModule-derived table and a CreateModule-derived one,
    so `--to-class` refuses it as a fold. Its owning base (or fold proof) comes first. Then each
    unit's view needs retail's slot order (header lane) before its ZH crc/xfer bodies can go.
- **RailedTransportDockUpdate.cpp (11):** 0x004B01D9 has one reference in the image: slot 3 of
  table VA 0x00C562D8.
  - That table is installed by ToggleMountedSpecialAbilityUpdate's ctor (0x004ADAB5), by
    SpecialDisguiseUpdate's ctor (0x004B0292) and by two ModuleUpdateDtors.cpp dtors.
  - Both ctors store it at +0xC, which is BehaviorModuleInterface. Each stores its own different
    table at +0x20. Slot 9 of the shared table is getUpdate 0x002533D3.
  - The two classes get one table either because it is their common base's or because the linker
    folded two identical copies.
  - Canonical `BehaviorModule.h` names slot 3 `getCreate`. The body returns complete-object +0x88
    (`lea eax,[ecx-0Ch]; add ecx,7Ch`, null-checked). So the honest name is probably that
    class's `getCreate`, not RailedTransportDockUpdate's ZH getter. This is inference: no ctor here
    was seen to install a table at +0x88.
  - The row's class is not a placeholder, so `rename.py function --to-class` cannot move it. That
    class, and evidence for its +0x88 interface, must be settled before the Railed dtor/vtable can
    go.
- **EvacuateDamageCtorModuleFactoryBody.cpp (1):** retail `~EvacuateDamage` 0x0002CD7B calls
  0x0002CCC3 as its base dtor.
  - That address is rowed as a STLport hashtable dtor in INI.cpp. `??1PB_DeepBase@@UAE@XZ` is only
    a pin there.
  - The EH funclet 0x0078F58B jumps to 0x004B96CC (`??1DamageModule` pin, row `Rva004B96CC`).
  - The base's real identity (and whether 0x0002CCC3 is a fold) is open.
- **DumbProjectileBehavior (10), JetAIUpdate (9):** still parked under LINK-072.
  - 0x0022C4CB has no approved unit.
  - 0x0004C91A is still `proposed`.
- **AIUpdate.cpp (5):** the file is free, but `class:AIUpdateInterface` is held by StarkillerHDX.
- **BFMENetwork (7), ConnectionManager's last 2, BattlePlan/Radar crc:** no change from the
  sections above. Identity work is still required, and class:BattlePlanUpdate was still held.
