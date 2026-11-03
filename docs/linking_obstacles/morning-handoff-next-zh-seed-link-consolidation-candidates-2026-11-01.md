### Morning handoff: next ZH-seed link/consolidation candidates (2026-11-01, halilkkaya-cx-o1)

State: the SupplyWarehouseDockUpdate stack (12 native-view/merge commits
plus the DockUpdateModuleData provider fix above) is verified at base
`8aed0a4001`. Only analysis was done on the candidates below; nothing is
started in source.

1. **BoneFXDamage** (290 B, seed `Object/Damage/BoneFXDamage.cpp` is a ZH
   port; class and file claimable 2026-11-01, `class:DamageModule` held by
   StarkillerHDX, so use the canonical header only). Blockers: U
   `DamageModule::crc/xfer/loadPostProcess` (the seed's present-unmatched ZH
   crc/xfer/loadPostProcess/dtor bodies call them), and the seed's inline ZH
   `??0DamageModule` copy differs from the rowed 0x004B9704
   (`DamageModuleCtor.cpp`). Target facts: ctor 0x004B979C calls 0x004B9704,
   then installs 0x008598B4/+0, 0x008597F8/+0C, 0x008597E8/+10. Primary
   slots: [0] `??_GRva004B96E5` (`Rva004B96CCDerived.cpp`, so ~BoneFXDamage
   is the placeholder Rva004B96E5; candidate `rename.py class --fold`),
   [1] folded loadPostProcess 0x00497805, [2] `GetSnapshotName@BoneFXDamage`,
   [3] folded xfer 0x0045CE8C, [4] static pool key 0x004B9757 (the
   static-to-virtual `getModuleNameKey` fix, as for the warehouse), [5]
   `onObjectCreated`; +10 slot 2 is `onBodyDamageStateChange`. No merge is
   possible: `BoneFXDamagePoolKey.cpp` is refused (rows not approved) and the
   seed is the only eligible file.
2. **CrateSystem TU** (ZH seed; six eligible donors, all linking;
   `CrateCreationEntryList.cpp` is mixed and does not link, 377 B). A dry run
   at `d385efd253` accepts no donor: `CrateSystemLifetime.cpp` fails on ZH
   `Science.h` (`Overridable` undefined, adopt_first `Overridable`), and
   `tu_views.py` must reconcile `CrateTemplate` and
   `BfmeStringRecord000B757D` first. Prior blocks: re_attempts
   `??1CrateTemplate` 0x0035CCCA and `??4CrateTemplate` 0x0035CE52. The crate
   list blockers are names retail rows under placeholders:
   `_S_merge<crateCreationEntry>` is pinned to 0x00288874, rowed as
   `_S_merge<Rva00288874Record>` (`ExperienceLevelSystem.cpp`), and the
   `_List_base` allocator ctor is pinned to 0x00288978, rowed as
   `BfmePod264` (`stlport_pod_list_bodies.cpp`). Unresolved `operator<`
   follows from the unit's own wrong `_S_merge` copy. This needs the
   placeholder-into-existing-name decision (LINK-063/LINK-175).
3. **ProductionPrerequisite TU** (429 + 183 B, ZH-header seed, five
   eligible donors). The blockers are wrong STL `vector<PrereqUnitRec>`
   copies, ZH `AsciiString::freeBytes/set`, and the
   `__imp_?allocate/deallocate@__new_alloc` imports from the STLport 4.6
   move. This overlaps the shared-name seat and the STLport lane.
4. **Held, skipped:** BridgeScaffoldBehavior (its U `??_7Rva00458402` tables;
   0x00458402 is the dtor right after its ctor 0x0045831C, a fold candidate,
   but `class:Rva00458402` and `Rva0024A797Grandchildren.cpp` are held),
   StructureTopple/QueueProductionExit/SupplyTruckAI/SpecialPowerModule and
   most other UpdateModule children (StarkillerHDX).

Method note: cohort previews missed the lost provider above. Before a seed
replacement, A/B the full touched-consumer set: `link_check` in a base
worktree (`worktree_setup.py create`, copy a fetched index, `--update-index`)
against the tip, then diff per unit. The exact-base `link_batch_audit.py`
cannot conclude while most consumers lack strict receipts.

- `DieModule.cpp` (19 B; LINK-175's `scanIndexList`/`s_bitNameList` unit): both blockers came
  from Zero Hour's DieMuxData field table, which reached `BitFlags<45>::parse` through
  `ObjectStatusMaskType::parseFromINI`. Retail's table (0x00C5FFA0, returned by the
  `getFieldParse` twin 0x004CE52E) is different: DeathTypes, ExemptStatus, RequiredStatus,
  DamageAmountRequired, MinKillerAngle, MaxKillerAngle at +0/+4/+0x14/+0x24/+0x28/+0x2C (BFME2's
  DieMuxData, DieMuxDataInit.cpp), parsed by rowed `INI::parseDeathTypeFlags` 0x00338D91,
  `?parseFromINI@Rva003B1017@@...` 0x003B1327, `INI::parseReal` 0x0002EFC0 and
  `INI::parseAngleReal` 0x0002F0D5. The unit now carries retail's table; the
  `_Base_bitset<2>::_S_maskbit` row 0x004D051E (no retail caller) it emitted only through
  that template is kept by an explicit instantiation. link_check: 0 -> 19 B LINKS; the 95
  census objects touching a dropped definition: 85 link, the other 10 did not link before.
  Remaining: retail's DieMuxData rows (init, isDieApplicable) sit in `DieMuxDataInit.cpp`
  while the approved TU is `DieModule.cpp` (consolidation).
- Shared-blocker names (LINK-175), traced on current objects:
  - `?scanIndexList@INI@@SAHPBDPBQBD@Z`: BFME2's is a thiscall member,
    `?scanIndexList@INI@@QAEHPBDPBQBD@Z` 0x0002BD39 (INI.cpp). Only Zero Hour code compiled
    against Zero Hour's `INI.h` spells the static form, all of it unrowed: `BitFlags<N>::parse`
    instances in WeaponSet.cpp (<17>), ThingTemplate.cpp (<11>), DieModule.cpp (<45>, fixed
    above) and `BitFlags<38>/<45>::parseSingleBitFromINI` plus a non-COMDAT body in Weapon.cpp.
    No definer should be added (the calling conventions differ); each unit needs its retail
    table/parsers or the unrowed bodies dropped.
  - `?set@UnicodeString@@QAEXABV1@@Z`: BFME2's UnicodeString is a `StringBase<unsigned short>`
    subclass; the copy set is exported `?set@?$StringBase@G@@QAEXABV1@@Z` 0x00037150 and
    retail inlines `UnicodeString::operator=`. All references (MapUtil, SkirmishGameOptionsMenu,
    LanGameOptionsMenu, WOLBuddyOverlay, WOLGameSetupMenu) come from unrowed Zero Hour bodies
    and Zero Hour's inline `operator=`. Route: `/Ireference/shims/bfme2_ascii_common` (maps
    `Common/UnicodeString.h` to BFME2's class) where the rowed bodies still match, and dropping
    the unrowed bodies; the five units have 12-47 other blockers of the same kind.
  - `AudioEventRTS` `??0/??1/??4`: retail's AudioEventRTS is the 136-byte
    `BfmeAudioEventPrefix136` (ctors 0x002D97D6..., virtual dtor 0x002D9A43 rowed as
    `??1BfmeStringTailRecord144@@UAE@XZ`, operator= 0x002D9A31 as `??4Rva002D9893`). Nearly all
    references are unrowed Zero Hour bodies. Two rows reach the names only through wrong-identity
    pins: `??1?$pair@VAsciiString@@VAudioEventRTS@@@_STL@@QAE@XZ` 0x002A12E1 (ThingTemplate.cpp)
    destroys its +4 member with the `_List_base` dtor 0x004EC395 (symbols.csv pins
    `??1AudioEventRTS@@UAE@XZ` there), so retail's pair holds a list, not an AudioEventRTS; and
    `??4DynamicAudioEventRTS@@QAEAAV0@ABV0@@Z` 0x00200BC0 (ThingFactory.cpp) assigns its +4
    member with `StringBase<char>::set` 0x000366F0 (pin `??4AudioEventRTS...` there), so that
    member is an AsciiString. Both identities need a naming decision before the units can drop
    the AudioEventRTS spelling; neither unit is near linking (ThingTemplate 16, ThingFactory 13
    blockers).
- Handoff for the next seat (checked on current objects, not landed):
  - `RegionDetailsStructuresIconCtor.cpp` (217 B; 3 U): the Icon dtor is rowed as
    `??1Rva005E278E@@UAE@XZ` 0x005E278E (+ `??_G` 0x005E283B), the same split as
    GlobalWeatherSystem, but NEW is nested (`StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon`)
    and `class --fold` handles global classes only. The two base dtors the ctor's unwind
    reaches are ICF-folded vptr restores: `??1IconMouseObserver@@QAE@XZ` -> 0x005E211F
    (table 0x00C77E7C), `??1LivingWorldBuildPlotObserver@@QAE@XZ` -> 0x00238D97 (table
    0x00BED658); both are twin candidates (`add_match --icf-owner`) once the Icon dtor resolves.
  - `T1Base005F3750Ctor.cpp` (176 B): T1Base's table 0x00C1D3F4 slot 0 is `??_GRva003ABA36`
    0x003AE8D5, calling `??1Rva003ABA36@@UAE@XZ` 0x003ABA36 (22 B). That dtor's first +0
    store is the base table 0x00BBB554 (an empty-bodied dtor stores no own vptr), so
    `class --fold Rva003ABA36 --into T1Base_005F3750` refuses on the own-table rule; also
    the copy ctor 0x003AE7B8 installs other tables. Needs identity work first.
  - `Rva00066A9ABody.cpp` (371 B): `g_Va00DB43A4`/`g_Va00DB43AC` (0x009B43A4/0x009B43AC,
    unowned, read only by `W3DShaderManager::init` 0x00077F80) are Zero Hour's
    `MasterShaderList`/`MasterFilterList`; linking needs those arrays and their shader/filter
    lists defined (data lane).
  - `reverse/data_ledger.csv` is stale (it predates rows such as 0x00318588); it is tool-written
    and protected, and `rename.py` says it is regenerated by `tools/data_ledger.py` in a
    Verifier-Change commit. Not regenerated here; `class --fold` no longer depends on it.
  - Held, not touched: `FamilyDeletingDtors_muse-cd13.cpp` (28 B; class
    DeflectSpecialPowerModuleData held by StarkillerHDX).
