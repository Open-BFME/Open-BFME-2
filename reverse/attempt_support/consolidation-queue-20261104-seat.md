# Mechanical consolidation shard handoff (2026-11-04)

Shard 1/5, selected from `/opt/runner/consolidation_queue.py --limit 100000`.
For each destination, the allocator check passed, the scoped consolidation
planner report passed `name_lane.py consolidate --check build/consolidation`,
and the normal `tu_skeleton.py --plan` / `--merge --dry-run` path preserved the
current sources. No source changes or claims were made. All candidates below
were rejected unchanged by the merge tool:

- `Code/GameEngine/Source/GameLogic/Object/Body/StructureBody.cpp`: no donor
  accepted. The destination's merged composition fails its census link check
  because `?rva004C09A1@Rva004C09A1@@QAEXPBURva004C09A1Object@@@Z` is duplicated;
  `StructureBodyCtor.cpp` also fails byte verification.
- `Code/GameEngine/Source/GameLogic/Object/Create/SupplyCenterCreate.cpp`: no
  donor accepted. `SupplyCenterCreateConstructor.cpp` fails C2511 because the
  destination class view lacks `SupplyCenterCreate(Thing *, const ModuleData *)`.
- `Code/GameEngine/Source/Common/BfmeThingSVA.cpp`: no donor accepted.
  `Rva00028B90Siblings.cpp` fails compilation with C2953, `_STL::basic_string`
  already defined, followed by C2955.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/AptAnimData.cpp`: no
  donor accepted. `AptAnimDataRenderData.cpp` fails compilation with C2065,
  `map` undeclared, and C2228 on `.findSlot`.
- `Code/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamage.cpp`: no donor
  accepted. `EvacuateDamageModuleDataDtor.cpp` fails with undeclared
  `EmitVtableTag`; `EvacuateDamageEvacuationSum.cpp` reports the STLport
  `__node_alloc::deallocate` specialization already instantiated.
- `Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp`: no donor
  accepted. `CreateCrateDieTestKillerType.cpp` fails with C2143 before `<` and
  C2904 because `BitFlags` is already used as a template name.
- `Code/GameEngine/Source/GameLogic/System/AiOrdersManager.cpp`: no donor
  accepted. `AiOrdersManagerPatrol.cpp` fails with C2460 because
  `Rva0054840A::ObjectID` uses `Rva0054840A` while it is being defined, followed
  by C2065 for `ObjectID`.
- `Code/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp`: no donor
  accepted. `GameLogic_clearGameData.cpp` fails at `VS` with C2059/C2146;
  `Rva00377064Update.cpp` fails with `SubsystemInterface` and `Shell` C2011
  redefinitions.
- `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAISupport/LivingWorldAIArmyMover.cpp`:
  no donor accepted. `LivingWorldAIArmyMoverDefendHomeTerritory.cpp` fails with
  C2065 because `BfmePod20` is undeclared in the destination view.
- `Code/GameEngine/Source/GameClient/VideoPlayer.cpp`: the earlier bounded
  destructor merge is no longer accepted by the current dry run. Donors now
  fail on `SubsystemInterface` C2011 redefinition, missing `Rva00689180`, or
  the `void *` to `Rva00688980 *` conversion in the element destructor. This
  follows the 2026-11-04 `VideoPlayer.cpp` source update; reconcile the changed
  views and rerun the provider/consumer audit before applying.

No accepted merge, build, or post-merge audit occurred. Source reduction is
zero. Prior unchanged blockers were skipped using `reverse/re_attempts.log` and
the corresponding `docs/linking_obstacles/` entries.
- `Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp`: left untouched. Three
  rows are held by another worker's `class:DX8Wrapper` claim (`0x00176C20`,
  `0x00176EE0`, `0x001772B0`); scoped `data_check.py` also reports an existing
  outside-baseline wrong-name finding for `__GUID_00000000_0000_0000_c000_000000000046`
  in the donor. No claims were taken and no merge was applied.
- `Code/GameEngine/Source/GameClient/BfmeItemKA.cpp`: no merge accepted.
  `GameSubTitle.cpp` fails C2953 (`StringBase` redefinition) and C2065
  (`m_count`); `GameSubTitleDraw.cpp` fails because `rva002600DC` is absent from
  the destination view and `m_startFrame` is undeclared. The STL sweep donors
  fail byte verification. Mixed split probes: `GapBodiesSeat1A.cpp` is refused
  because copying the helper grows an escape-hatch count; `StringRecordInlineCopyBFME2.cpp`
  has no definition spelling the target row's name; `stlport_construct_game_structs.cpp`
  can carve 0x0026061A but is refused because two data-ledger names are defined
  in both units. No files or claims changed.
- `Code/GameEngine/Source/Common/HordeAIUpdate.cpp`: no merge accepted.
  `HordeAIUpdateCtor.cpp` fails because `AIUpdateInterface` has no default
  constructor; split probes for `Rva0026E836Derived.cpp` fail on undeclared
  `m_extra03E4`, and for `HordeAIUpdatePrivateCommands.cpp` fail on private
  `Object::m_250` and missing `rva7C`. No merge or split applied.
- `Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/VeterancyCrateCollide.cpp`:
  no merge accepted; constructor donor lacks the destination overload (C2511).
  `ConstIntGetters4.cpp` split fails C2664 converting `unsigned char[4]` to
  `const AsciiString&`; `Rva004BC4FCDerived.cpp` split is link-guard refused
  because moved dtor and two vftable COMDATs lack matching private/weak-free
  context. No merge or split applied.
- `Code/GameEngine/Source/Common/StdioStreambufBase.cpp`: no merge accepted.
  Dry run rejected all four clean donors on duplicate STLport declarations or
  locale view conflicts and accepted none; LinkGuard lists the existing census
  linked units. The three mixed upstream STLport sources
  (`stlport_narrow_istream.cpp`, `stlport_wide_streambuf.cpp`,
  `stlport_wide_string.cpp`) were each inspected with `--split` and refused for
  being vendored sources. No source changes, claims, or splits applied.
- `Code/GameEngine/Source/GameLogic/Object/Update/ModelConditionSpecialAbilityUpdate.cpp`:
  no merge accepted. The `ModelConditionSpecialAbilityUpdateModuleDataDtor.cpp`
  donor fails byte verification. The only mixed source,
  `ModuleUpdateDtors.cpp`, was inspected and its split trial refused because no
  row in that file is approved for this destination TU. No changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/FellBeastSwoopPower.cpp`: no
  merge accepted. The ctor donor fails C2511 because the destination class view
  lacks the overload. A split of `ConstIntGetters4.cpp` carved row 0x004C6C56
  but failed destination compilation (`Object::m_conditionBits`); the
  `Rva00451F45Derived.cpp` split was LinkGuard-refused because moving the dtor
  and two vtable COMDATs lacks matching private/weak-free context. The
  `TailJumpWrappers5B.cpp` split of 0x004C6CC1 is exact and accepted, but its
  residual file remains and it does not unblock the ctor; left unapplied to
  avoid a split with no merge it enables. No source changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdate.cpp`:
  no merge accepted. Its constructor-thunk donor fails C2509 because the
  destination view does not declare `getModuleNameKey`; the tool requests class
  reconciliation. Mixed-source probes: `ConstIntGetters4.cpp` is LinkGuard
  refused for a selected string COMDAT without matching private/weak-free
  context; `OpaqueScalarDeletingDtors.cpp` cannot carve 0x00494A97 because no
  definition spells its name; `VslotSmallBodiesAI.cpp` can move 0x00494ABE
  exactly, but that split does not resolve the constructor view and leaves the
  source file, so it was not applied. No changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Update/DestroyEnvironmentUpdate.cpp`:
  no merge accepted. LinkGuard says the seed itself would regress two
  `DestroyEnvironmentUpdate` vtable COMDAT copies in other units; the Xfer donor
  also fails C2509 because the destination view lacks `xfer`. Split probes found
  no safe path: the getter split loses a selected string COMDAT under LinkGuard;
  `Rva004AC7C9FindModuleObject.cpp` split would strand matched row 0x004AC5F5;
  `ModuleDataBuildFieldParse.cpp` split fails C2600 because the destination
  class does not declare the constructor. No changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdate.cpp`: no
  merge accepted, matching the existing transfer-composition obstacle after the
  Xfer row had already moved into the destination. The ctor donor fails C2512
  because `SpecialAbilityUpdate` has no default constructor; the slot-17 donor
  fails on that base being undefined and missing `xfer`. Split probes: the
  getter in `ConstIntGetters4.cpp` fails on missing `Object::m_conditionBits`;
  `Rva00451F45Derived.cpp` is LinkGuard-refused for the moved dtor and two
  vtable COMDATs lacking matching private/weak-free context. No changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Update/RadiateFearUpdate.cpp`: the
  earlier accepted transfer donor is already absorbed; the remaining update
  donor fails C2509 because `getModuleNameKey` is absent from the class view,
  and the module-data destructor donor fails byte verification. The existing
  obstacle records the constructor/update view prerequisites. `Rva0024A797Grandchildren.cpp`
  contains no row approved for this TU; `UpgradeMuxSlotOverrides.cpp` splits
  two exact rows but fails on missing `RadiateFearUpdateModuleData::m_upgradeMuxData`.
  No changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehavior.cpp`:
  allocated check and consolidation planner passed; dry run accepted no donors.
  The Xfer donor fails on duplicate `Weapon`, and the update donor fails on
  duplicate `Object` and `Weapon` declarations in the destination composition.
  `ModuleNameGetters.cpp` was inspected as the mixed source; no split was
  applied. No source changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior.cpp`:
  allocated check and planner passed; dry run accepted no donors. Its ctor
  donor fails C2511 because the destination class view lacks the overload, and
  asks for class reconciliation. The mixed `ModuleDataBuildFieldParse.cpp`
  split carved row 0x00483A7A alone but failed composition with C2600 because
  the destination does not declare the compiler-generated constructor. No
  changes or claims.
- `Code/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdate.cpp`:
  allocated check and planner passed; no donors were accepted. Both constructor
  donors fail composition (module-data C2600 undeclared generated constructor;
  update ctor C2511 absent overload), and the module-data dtor fails bytes.
  Mixed probes: the name getter fails because `handlePackingProcessing` is
  absent from `SpecialAbilityUpdate`; the RailedTransport getter fails because
  `continuePreparation` is absent from that base; `ModuleUpdateDtors.cpp` has
  no row approved for this destination. No source changes or claims. Existing
  data identity findings remain separate prerequisites.
- `Code/GameEngine/Source/GameLogic/Object/Update/ThreatFinderUpdate.cpp`:
  allocated check and planner passed; dry run accepted no donors. The
  map-load donor fails on duplicate `StringBase` template declarations, while
  the dtor donor fails bytes. The only mixed getter split is exact alone but
  LinkGuard refuses it because the selected `ThreatFinderUpdate` string COMDAT
  lacks matching private/weak-free context. The separate header/data obstacle
  is already recorded. No source changes or claims.
- `Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp`:
  allocated check and planner passed; the only clean donor,
  `GeometryRecordVector.cpp`, fails byte verification, so no merge is
  available. Seven mixed files remain listed by the plan; no split was applied
  because it would not unblock this failed donor. No source changes or claims.
- `Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAI.cpp`: allocated
  check and planner passed; the only donor, `Rva002C6E4EDtor.cpp`, fails
  composition because the `_STL::_Rb_tree` specialization is already
  instantiated in the destination. Four mixed files are listed; no split was
  applied because it does not unblock this donor. No source changes or claims.
- `Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp`:
  allocated check and planner passed; no donors were accepted. The constructor
  donor fails because `_STL::_Nonconst_traits` is already defined in the
  destination; another nearby donor is refused because its 21 rows are not
  approved for this TU. Ten mixed files remain listed; no split was applied
  because it would not unblock the constructor donor. No source changes or
  claims.
- `Code/Libraries/Source/WWVegas/WW3D2/camera.cpp`: allocated check and
  planner passed; no donors were accepted. `CameraAdditionalTransformSetter.cpp`
  duplicates `ViewportClass` and `CameraClass` declarations in composition.
  The mixed `W3DScene.cpp` candidate row could not be carved because no
  definition spells its name. No source changes or claims.
- `Code/GameEngine/Source/GameLogic/SkirmishAI/AITeamBuilder/AITeamBuilder.cpp`:
  allocated check and planner passed; no donors were accepted. The ctor donor
  fails because a composed `_STL::set` cannot convert to `Rva002EE9B7 *` in
  this destination view. Three mixed sources remain listed; no split was
  applied because it would not unblock the ctor. No source changes or claims.
