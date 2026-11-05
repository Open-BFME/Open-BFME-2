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
  2026-11-04: removing the obsolete three-slot destructor clears this seed's vtable blocker in the current-object preview (65 B); native providers retain linking, census confirmation pending. [Evidence and remaining TU prerequisites](../../reverse/attempt_support/weaponset-obsolete-destructor-20261104-codex3.md).
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

#### Seat halilkkaya-lk22 follow-up (2026-11-04, real link 41813987742 at `612abfbebb`, census index `a62ac1c10b`)

**Repaired: 14 names (AIUpdate 5, BFMENetwork 5, ThingFactory 4).** Each drop had an orphan scan (existing objects against the census index); every
COMDAT a changed object held first had a `link_check` over all its definers and referrers.

- **AIUpdate.cpp, 5/5.** The unrowed Zero Hour `getTurretTargetObject(WhichTurretType, Bool)`,
  `needToRotate` and `privateAttackMoveToPosition` are gone (4 names). The last one,
  `?crc@UpdateModule@@MAEXPAVXfer@@@Z`, went with the Zero Hour crc chain: `AIUpdateInterface::crc`,
  `WorkerAIUpdate::crc` and `DozerAIUpdate::crc` were dropped together. BFME 2's module tables have no crc
  slot, and neither Worker nor Dozer emits its own class vtable. Two rowed header inlines that lost their only
  user, `OVERRIDE<LocomotorTemplate>::operator->` 0x0035C95F and `Weapon::setMaxShotCount` 0x00661D50, are
  kept by member-pointer anchors. The unit now has 0 unresolved names. The census still counts it as
  not linking because of two non-retail STLport COMDAT bodies. The 8 consumer units still LINK.
- **BFMENetwork.cpp, 5/5; the unit now LINKS (0 -> 173 B).**
  - `rename.py class --fold Rva00557CCC --into BFMENetwork`: the destructor 0x00557CCC and the constructor
    0x00558EC1 install one table, 0x00C6B318. The unused QAE pin was dropped first.
  - The queue members hold one deque each, and +0x90 is `_STL::set<Rva00558D6BElement>` (ctor row
    0x00558D6B). The implicit destructors are emitted as the 5-byte jumps retail has at
    0x00557CBD/CC2/CC7. The invented `BFMENetworkAllocate` payload list was a misread of the set's
    tree header.
  - Pin `??0BFMENetworkPayloadList` dropped.
  - Open: respell the placeholder rows 0x00557CBD/CC2/CC7 (`Rva00557CBD::rva00557CBD` etc. in
    StlportConstructFamilyW3G15.cpp) as `??1BFMENetworkQueue`, `??1BFMENetworkQueue1` and the set
    destructor. Then uw_00799498/A3/D2 can move into BFMENetwork.cpp (LINK-095).
- **ThingFactory.cpp, 4 of 6** (LINK-182 has the detail): the Zero Hour `newObject` and the
  LOAD_TEST_ASSETS branch of `findTemplateInternal` are gone.

**Checked, not repaired:**

- **BoneFXDamage.cpp (3):** no object defines `DamageModule::xfer` or `DamageModule::loadPostProcess`.
  - `DamageModule::xfer` is retail 0x004CE56D, placeholder `Rva004CE56D::xfer`. That body is in 5 retail
    module tables, so `--to-class` refuses it. It calls `BehaviorModule::xfer`, which is rowed non-virtual
    (`QAE`) at 0x004C9C7D, while canonical `BehaviorModule.h` declares no xfer.
  - `DamageModule::loadPostProcess` is the 0x0058B03E fold. That RVA is claimed by StarkillerHDX
    (class:UpdateModule).
  - The crc name needs the unit on canonical `DamageModuleClass.h`.
  - Prerequisites, in order: ICF twin rows for both base bodies, then the unit's view in retail slot order.
- **LockWeaponCreate.cpp (2):** the unit emits a Zero Hour-order table, bound by three `/alternatename`
  hatches.
  - Retail 0x00C592FC: slot 1 is 0x00497805 (a fold in 60 tables), slot 2 the name getter 0x004B8C38
    (placeholder free function), slot 3 0x004851E3 (a fold in 8 tables).
  - Its destructor 0x004B8C3E is placeholder `Rva004B8C3E`. Folding that placeholder into
    LockWeaponCreate would collide with the unit's Zero Hour destructor until the view changes.
  - Needs canonical `CreateModuleClass.h` adoption plus ICF twin rows.
- **ConnectionManager.cpp (2):** 0x0046A9AB is the shared ushort-key `_M_lower_bound`.
  - Every ushort map `operator[]` calls 0x0046A9AB (callers_of: 5 callers), and it is rowed as
    `<ushort,uchar>`.
  - The `<ushort,AsciiString>` `_M_lower_bound` row sits at the byte-identical 0x00156680, which has no
    direct caller.
  - 0x004D272E is the hint-insert fold, rowed as `map<int,Rva004D272ERecord>::insert`.
  - Settle 0x00156680's identity first, then add ICF twin rows for the two FileCommandMap names at
    0x0046A9AB and 0x004D272E, and drop the adapters.

#### Seat halilkkaya-lk23 follow-up (2026-11-04, real link 41825144174 at `efbd3f2cb2`)

- **LockWeaponCreate.cpp (2): unchanged.**
  - With `8a94b4fdd4`, `rename.py class --fold Rva004B8C3E --into LockWeaponCreate` plans on vftable
    0x00C592FC: the destructor's first store, named `??_7LockWeaponCreate@@6BObjectModule@@@` in
    data_ledger.csv.
  - Not applied. It resolves no name, and the rows would read `UAE`, while Zero Hour's destructor is
    protected (`MAE`).
  - `function --to-class LockWeaponCreate` refuses `onBuildComplete` (0x004B8CC9) because the Zero
    Hour view compiles no table matching 0x00C592EC. It refuses `xfer` (0x004851E3) because the body is
    shared by AnnounceBirthAndDeathBehavior, SupplyCenterCreate and SupplyWarehouseCreate.
  - The canonical `CreateModuleClass.h` view in retail slot order still comes first.
- **ConnectionManager.cpp (2): 0x00156680 is unreferenced.** The whole retail image holds no rel32
  call or jmp to it and no absolute VA 0x00556680.
  - It sits in the WW3D2 template-COMDAT area, beside `map<ushort,AsciiString>::_M_find` (0x001559C0).
  - 0x0046A9AB has 5 rel32 callers. One is this operator[], at 0x004D2957.
  - The `<ushort,AsciiString>` name at 0x00156680 is therefore unproven. That identity decision still
    comes before the ICF twin rows.

#### Seat halilkkaya-lk25 follow-up (2026-11-04, real link 41841709801 at `9c227365cd`)

- **LockWeaponCreate.cpp (2): not attempted.** It hits the same blocker as `CreateModuleXfer.cpp`
  (`81c3965951`). This unit defines the constructor, so `--to-class onBuildComplete` needs every
  emitted table to match 0x00C592FC/0x00C592EC. That needs the full canonical
  CreateModule/BehaviorModule vtable class, starting with BehaviorModule.h's base xfer. The sibling
  ctor units carry the same placeholder name getters (ConstIntGetters4.cpp). Recorded in
  re_attempts.log.
- **ConnectionManager.cpp (2): new evidence on 0x00156680's identity; no source change.**
  - Why the two bodies did not fold: 0x00156680 is in a 16-byte-aligned, int3-padded run, the
    WW3D2 font code. 0x0046A9AB is unpadded /O1 code. The 39 bytes are identical, so the
    sections' different alignment is the likely reason ICF kept both.
  - Its neighbours are FontCharsClass's map, not an AsciiString map:
    - the ledger spells `_M_find` 0x001559C0 and `find` 0x00156F80 as `<ushort,AsciiString>`;
    - `_M_find` is called by `FontCharsClass::Get_Char_Data` 0x00158520 (and by the unreferenced
      `find`);
    - Get_Char_Data reads the node's value at +0x14 as a `FontCharsClassCharDataStruct const *`
      and tests it against 0 and -1;
    - so that tree is FontCharsClass's ushort -> char-data map at this+0x450.
  - Conclusion: the `<ushort,AsciiString>` spellings of 0x001559C0, 0x00156F80 and the
    unreferenced 0x00156680 are this TU's anchor placeholders. That is a structural inference.
    The exact value spelling is unproven: const or not, and struct or class
    (FontCharsClassGetCharData.cpp aliases both).
  - The same run holds the whole family under mixed spellings, all rowed in ConnectionManager.cpp:
    `<ushort,int>` operator[] 0x00157DD0 (its one caller is `FontCharsClass::Store_Thai_GDI_Glyph`
    0x00157FF0), `_M_insert`/`insert_unique` 0x00157130/0x001571E0/0x00157520, `map::insert`
    0x00157AD0, and `<ushort,AsciiString>` `lower_bound` 0x001574F0, `_M_lower_bound` 0x00156680,
    `find` 0x00156F80 and `_M_find` 0x001559C0. Several of them have no caller at all, so this run
    keeps unreferenced instantiations. BFME 1's view (donor lead only,
    `FontCharsClass_Get_Char_Data_BFME.cpp`) holds `const FontCharsClassCharDataStruct *` values.
  - Next, in this order:
    1. Prove the value type from the map's insert/subscript in the FontCharsClass store path.
    2. Rename that family.
    3. Add `_M_lower_bound<ushort,AsciiString>` as an ICF twin at 0x0046A9AB
       (`fold-proof=`).
    4. Let operator[] reach it through plain STLport and drop the `Rva0046A9ABMapLowerBound` pin.
  - The insert half stays blocked on 0x0016E310
    (`reverse/attempt_support/connectionmanager-filecommandmap-chain-20261103/README.md`).

#### Seat claudeb follow-up (2026-11-04): ConnectionManager.cpp's 2 names repaired without the identity steps

- operator[] 0x004D2941 now reaches both helpers under their current row names, by method 5 of
  `rows-that-do-not-need-their-class-2026-11-04.md`. `lower_bound` goes through the
  `FileMaskMap` (`map<ushort,uchar>`) view, so it calls the 0x0046A9AB `_M_lower_bound` row. The hint
  insert goes through `map<int,Rva004D272ERecord>`, so it calls the 0x004D272E row. Both stay
  declared only.
- The two adapter pins are dropped (pin register 9331 -> 9329). 32/32 rows byte-match.
- ConnectionManager.obj leaves only those two names undefined, which link_check resolves. Its
  "does not link" now comes only from the anchor's `<ushort,AsciiString>` COMDAT selection, as
  before.
- The FontCharsClass identity and 0x0016E310 steps above are still open for naming. They no
  longer block the real link.

#### Seat claudec follow-up (2026-11-05): LockWeaponCreate.cpp's next step is ~CreateModule's identity

- 0x004B8CDE (`Rva004B8CDE`) is `~CreateModule`. A canonical view needs it and six other provider names first. `rename.py class --fold` refuses it (recorded as a false reject). Order of work: `reverse/attempt_support/004b8c0e-lockweaponcreate-canonical-view-20261105.md`.

#### Seat halilkkaya-lk28 follow-up (2026-11-05, real link 42035295927 at `dbde7dbe3b`)

- **BoneFXDamage.cpp (3): 1 repaired, `?loadPostProcess@DamageModule@@MAEXXZ`.**
  - It is an ICF twin row at 0x0058B03E, defined in DamageModule.cpp as Zero Hour's base call.
    Retail DamageModule table 0x00C598E4 slot 1 is `jmp 0x000B3FD0`, BehaviorModule's empty
    loadPostProcess.
  - Canonical `BehaviorModule.h` now declares `loadPostProcess`, but only for units that define
    `BFME_BEHAVIORMODULE_LOADPOSTPROCESS`.
  - Declared for every includer, it rebinds slot 1 of 56 tables in 48 units from `__purecall` to
    BehaviorModule's body. All 856 includers stayed byte-exact and the 48 units still LINK.
    Retail holds that body at slot 1 in none of the 56: 32 reach it through tail jumps
    (0x00497805, 0x0058B03E, 0x00483CEF), and 24 run real bodies (SpecialPowerModule 0x00493B1E,
    ActiveBody 0x004BF40F, AIUpdateInterface 0x002686A4, TerrainResourceBehavior,
    DynamicPortalBehaviour). It stays opt-in until each family declares its own override.
  - Opt-in form: no `??_7` and no other COMDAT changed across the 856 objects. DamageModule.cpp
    LINKS 6 -> 11 B.
  - Measurements and the full class list:
    `reverse/attempt_support/behaviormodule-snapshot-slots-20261105-lk28.md`.
- **BoneFXDamage.cpp: `xfer@DamageModule` still blocked.** Its twin at 0x004CE56D calls
  BehaviorModule::xfer.
  - The ledger spells that row `QAE` (0x004C9C7D) behind an `/alternatename`; a canonical call is
    `MAE`. The byte verifier resolves only ledger names, and a pin would be a second name.
  - First the 12 private views that call the `QAE` name move to `MAE` (listed in the handoff).
    Then rename the row, drop the hatch, and declare `xfer` in `BehaviorModule.h`.
- **BoneFXDamage.cpp: `crc@DamageModule` still blocked.** BFME 2 has no crc slot, so the name
  goes only when the unit leaves the Zero Hour view for `DamageModuleClass.h` in retail's slot order.
  - Needs the twins 0x0045CE8C (xfer) and 0x00497805 (loadPostProcess).
  - Needs `Rva004B96E5` folded into BoneFXDamage as its destructor.
  - Needs canonical Object and BoneFXUpdate views for the two rowed callbacks.
- **LockWeaponCreate.cpp (2): not attempted.** `class:LockWeaponCreate` and the file are claimed
  by yasinschroeder-claudec.

#### Seat halilkkaya-lk30 follow-up (2026-11-05): the `xfer@DamageModule` respell chain

- **Still blocked: `xfer@DamageModule` and `crc@DamageModule`.** Neither name resolved this pass.
  The `xfer` work mapped the respell chain and cleared two of its tool obstacles.
- **Which spelling (target and donor facts).** The census index (c95fcfcfcd) has 8 objects
  referencing `?xfer@BehaviorModule@@MAEXPAVXfer@@@Z`. They are the Zero Hour units' unrowed
  bodies. 13 objects reference the `QAE` row spelling and none references `UAE`. Snapshot,
  `DamageModuleClass.h` and `UpgradeModule.h` declare the slot protected, so the row's target
  spelling is `MAE`. `rename.py function --virtual` gives only `UAE` (it changes Q to U), so `MAE`
  still needs an access option in the tool.
- **The cascade is real.** Three units declare a derived `xfer` non-virtual over a private
  BehaviorModule view: UpdateModule.cpp, GateOpenAndCloseBehaviorXfer.cpp and
  SpawnBehaviorXfer.cpp. CastleMemberBehaviorCtor.cpp does the same. Once the base turns
  virtual, those derived declarations become overrides, so these rows respell first:
  - `?xfer@UpdateModule@@QAEXPAVXfer@@@Z` (0x0044DF9F). Its spelling is `UAE`: retail table
    0x00BF004C slot 3, and canonical `UpdateModule.h` declares it public (148 census objects
    reference `UAE`).
  - `?xfer@CastleMemberBehavior@@QAEXPAVXfer@@@Z` (0x003957C6): retail table 0x00C1A22C slot 3.
- **Cleared:**
  - A dead pin at 0x0044DF9F, `?handle@Gen002B2080@@QAEXPAVFlagPairTarget@@@Z`, made `rename.py`
    refuse the address as a shared body. It is now removed (pin register -1).
  - `rename.py --virtual` refused units whose UpdateModule view sits in an included `*View.h`:
    BridgeScaffoldBehavior, DynamicShroudClearingRangeUpdate, LargeGroupAudioUpdate and
    RadarUpdate. A header the respell rewrites now covers its includers. The fix has tests.
- **UpdateModule::xfer trial: 300 of 303 rows exact, restored.**
  - Setup:
    - The `UAE` twin pin was removed in the same change.
    - `--prepared UpdateModule.cpp`: the BehaviorModule view declares `virtual ~BehaviorModule()`,
      so the vptr is the base's. The pad goes from 0x14 to 0x10, and the self-referential
      `UAE=QAE` `/alternatename` is dropped.
  - Remaining failures:
    - DynamicShroudClearingRangeUpdate::xfer (0x0048B505) is declared non-virtual in its view
      header. Couple its respell in `run_batch`.
    - Rva0047F94C::xfer (0x0047F94C) is a placeholder with the same non-virtual declaration.
    - MineshaftPortalBehaviour::DoXfer calls `((UpdateModule *)this)->xfer(xfer)` unqualified,
      which is now a vtable call. Prepare it as `->UpdateModule::xfer(xfer)`.
- **CastleMemberBehavior:** CastleMemberBehaviorCtor.cpp's view keeps an explicit `m_vtable`
  member for the ctor's hand-ordered table stores. Any virtual adds a real vptr and shifts every
  field, so the view must be reshaped before the respell can verify.
- **Order left:**
  1. UpdateModule::xfer, with the three fixes above.
  2. CastleMemberBehavior::xfer.
  3. A `--virtual` access option for `MAE`.
  4. BehaviorModule::xfer to `MAE`. Its 13 views get `protected: virtual`. Non-derived callers,
     Rva004CE56DXfer.cpp and Rva00493009Xfer.cpp, need a qualified call through a derived view.
     BehaviorModuleXfer.cpp's ObjectModule view needs a vptr, or the ObjectModule::xfer call
     gains a +4 `this` adjustment. Then drop `MAE=QAE`.
  5. An opt-in `xfer` in `BehaviorModule.h`.
  6. The DamageModule::xfer twin at 0x004CE56D. Fold-proof: `Rva004CE56DXfer.cpp`.

#### Seat halilkkaya-lk31 follow-up (2026-11-05): `xfer@DamageModule` resolved; the respell chain landed

- **Repaired: `?xfer@DamageModule@@MAEXPAVXfer@@@Z` (BoneFXDamage.cpp, 2 of 3).** DamageModule.cpp
  defines Zero Hour's `DamageModule::xfer` (Version1, then `BehaviorModule::xfer`). It is rowed as an
  ICF twin at 0x004CE56D, fold-proof `Rva004CE56DXfer.cpp`; its COMDAT digest equals the
  placeholder's. Canonical `BehaviorModule.h` declares `xfer` (protected virtual) only for units that
  define `BFME_BEHAVIORMODULE_XFER`, following lk28's loadPostProcess opt-in. link_check:
  DamageModule.cpp LINKS 6 -> 38 B. BoneFXDamage.cpp now lists only `crc@DamageModule` and its
  `??0DamageModule` COMDAT note.
- **The chain, one verified commit per step:**
  1. 7e6d3ff7e32: `rename.py function --virtual --access public|protected|private` (tests, Verifier-Change).
     The plain respell keeps the row's access (Q -> U). `--access protected` gives MAE and wraps each
     in-class declaration as `protected: virtual ...`, restoring the previous access after it.
  2. 60d20c27cf0: `?xfer@CastleMemberBehavior@@QAE` -> `MAE` (0x003957C6, retail 0x00C1A22C slot 3). The view
     in CastleMemberBehaviorCtor.cpp was reshaped first:
     - BehaviorModule's view gains a virtual destructor, so the vptr is real;
     - the class is `__declspec(novtable)`, and the ctor keeps its hand stores in retail's order
       through `*(const void **)this`.
     Bytes are identical and no ??_7 is emitted.
  3. fce76cc0204: UpdateModule::xfer (0x0044DF9F) and DynamicShroudClearingRangeUpdate::xfer (0x0048B505)
     `QAE` -> `UAE`, one run_batch over 18 sources, 303/303 exact:
     - the UAE twin pin and UpdateModule.cpp's `UAE=QAE` alternatename are gone;
     - `MAE=UAE` stays for the 4 MAE consumers (AssistedTargetingUpdate, FireSpreadUpdate,
       FloatUpdate, SlavedUpdate);
     - prepared: MineshaftPortalBehaviour's DoXfer qualifies its base call. Rva0047F94C no longer
       derives from its UpdateModule view (see below);
     - PassiveAreaEffectBehavior, StancesBehavior and DynamicShroudClearingRangeUpdateView.h declare
       retail's two Snapshot slots ahead of xfer as pure placeholders. Without them, the new base
       virtual takes slot 1.
  4. debd7c7bbdc: BehaviorModule::xfer (0x004C9C7D) `QAE` -> `MAE` over 13 sources, 36/36 exact. BehaviorModuleXfer.cpp's
     `MAE=QAE` alternatename is gone, and its ObjectModule view has a vptr (virtual destructor).
     Rva00493009 derives from its BehaviorModule view. Rva004CE56D is the view's friend: it calls
     `((BehaviorModule *)this)->BehaviorModule::xfer`.
  5. The DamageModule::xfer twin above (6b562c44a73).
- **Vtables (every changed `??_7` diffed slot by slot against retail's installed table):**
  - DynamicShroudClearingRangeUpdate (0x0084BEBC) and StancesBehavior (0x008424DC) each go from 0 to
    2 retail-equal slots: xfer is now slot 3 and getModuleNameKey slot 4.
  - Neutral, no slot equal before or after:
    - InvisibilityUpdate: its view puts the Snapshot slots after a 10-slot placeholder run, and
      slots 12-14 rotate into retail's relative order;
    - Rva0037343B (MineshaftPortalBehaviour.cpp): its view has a placeholder at slot 0, and the
      table gains slot 2 = UpdateModule::xfer.
  - Every other table is unchanged.
  - Fixing the two neutral tables needs those views put into retail's Snapshot order: dtor,
    loadPostProcess, GetSnapshotName, xfer, getModuleNameKey.
- **Left:**
  - `crc@DamageModule`, unchanged from lk28's entry.
  - The fold placeholders `?xfer@Rva0047F94C@@QAE` and `?xfer@Rva004CE56D@@QAE` stay non-virtual:
    - Rva0047F94C is slot 3 of CivilianSpawnUpdate's 0x00C48418 and of BannerCarrierUpdate's
      0x00C4F838;
    - Rva004CE56D is slot 3 of DamageModule, DieModule and other module tables;
    - `--virtual` refuses both for lack of class evidence, and `--to-class` refuses folds.
    Naming the fold's owner (approved TU: CivilianSpawnUpdate.cpp, and DieModule.cpp) is the next
    identity step.
  - The 4 `MAE` UpdateModule::xfer consumers can move to the canonical `UAE` spelling, and then
    `MAE=UAE` goes.
- **Tool facts for the next seat:**
  - rename.py's class scan does not see a body whose head is `class __declspec(novtable) X`. A
    prepared source then declares the virtual itself.
  - A prepared source must leave the declaration the respell rewrites non-virtual. If it is already
    `virtual`, the tool sees nothing to rewrite and refuses the unit as "undeclared".
  - run_batch `source_edits` take `.cpp` only. A view header with one includer was edited on disk
    before the batch, so the transaction staged and verified it.

#### Seat halilkkaya-lk32 follow-up (2026-11-05): `crc@DamageModule` resolved; BoneFXDamage.cpp on canonical views

- **Repaired: `?crc@DamageModule@@MAEXPAVXfer@@@Z` (BoneFXDamage.cpp, 3 of 3).** The unit no longer
  compiles against Zero Hour headers. It includes canonical `DamageModuleClass.h` (Snapshot with
  GetSnapshotName in slot 2) and the draft `object.h`, and declares a TU-local BoneFXDamage in retail's
  slot order. Zero Hour's `BoneFXDamage::crc` has no BFME2 counterpart and is gone, so nothing
  references `DamageModule::crc`. link_check: BoneFXDamage.cpp does not link -> LINKS 0 -> 322 B.
- **Steps, each verified:**
  1. `rename.py class --fold Rva004B96E5 --into BoneFXDamage`: the destructor 0x004B96E5 and its
     deleting destructor 0x004B97C6 (Rva004B96CCDerived.cpp) are BoneFXDamage's. Evidence: the
     destructor's first +0 store installs 0x00C598B4, which the rowed ctor 0x004B979C installs too.
  2. ICF twin rows in BoneFXDamage.cpp: `loadPostProcess` at 0x00497805 (`jmp` DamageModule's
     0x0058B03E; fold-proof BattlePlanUpdate.cpp) and `xfer` at 0x0045CE8C (Version1, then
     DamageModule's 0x004CE56D; fold-proof Rva0045CE8CXfer.cpp).
  3. The canonical rewrite: ctor, onObjectCreated, onBodyDamageStateChange, both EH handlers and both
     funclets stay exact (9/9). The funclet labels renumbered (`$L46026` -> `$L3686`, `$L46047` ->
     `$L3704`); build.py verifies them through the parent's EH data. Four `present-unmatched` hatches
     are gone (dtor, crc, xfer, loadPostProcess).
- **Vtables, slot by slot against retail:**
  - `??_7BoneFXDamage@@6BObjectModule@@@` (0x00C598B4): 14 slots with 1 retail-equal -> 12 slots
    with 11 equal. The one unknown is slot 4, getModuleNameKey (next item).
  - `??_7BoneFXDamage@@6BBehaviorModuleInterface@@@` (0x00C597F8): 34 slots with 6 equal -> 47 slots
    with 43 equal.
  - `??_7BoneFXDamage@@6B@` (0x00C597E8): unchanged.
  - The unit stops emitting the Zero Hour copies of BehaviorModule's, BehaviorModuleInterface's and
    DamageModuleInterface's tables. Other objects keep identical copies of those, and nothing else
    touched the Zero Hour DamageModule tables, `??1DamageModule@@MAE@XZ` or `??0DamageModule`'s
    second COMDAT variant (the census's `??0DamageModule` COMDAT note is gone with it).
- **Left for BoneFXDamage:** getModuleNameKey is still an unrowed inline body, the same COMDAT the
  Zero Hour build emitted (digest d40f9a747e27). Retail's 0x004B9757 is rowed under the static
  placeholder `?rva004B9757@BoneFXDamage@@SA?AW4NameKeyType@@XZ` (BoneFXDamagePoolKey.cpp).
  Respelling that row to `?getModuleNameKey@BoneFXDamage@@UBE?AW4NameKeyType@@XZ` and moving it
  into BoneFXDamage.cpp would turn slot 4 retail-equal. `rename.py --virtual` changes only Q to U,
  so it cannot respell a static.
