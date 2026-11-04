# Consolidation shard 2 handoff — 2026-11-04, session 6

No source merge was accepted in this pass. The applied `W3DTornadoDraw.cpp`
trial built 6/6 rows, but the outgoing path audit found active ownership
comments in the sibling W3D device TU that still name the deleted destructor
file. The trial was restored and its two file claims and five RVA claims were
released. Repair those comments before retrying that destination.

Additional allocated dry-run blockers:

- `Made002CCC2D.cpp`: ctor is refused because the class view omits the
  compiler-generated special member declaration (`C2600`).
- `Squad.cpp`: donor accesses `Object::contain` and `Object::id`, absent from
  the seed view (`C2039`).
- `StatsReporter.cpp`: strategic-results donor needs `LivingWorldLogic::getFrame`
  and `rva004EE037`, absent from current views (`C2039`).
- `LightPointSystem.cpp`: donor duplicates STL allocator/vector templates
  (`C2953`). Both mixed splits were inspected: the `GapBodiesGE20.cpp` split
  fails on `perror` linkage (`C2375`); the other residual loses matched row
  `0x00421572`.
- `registry.cpp`: `RegistryDeleteValues.cpp` fails donor byte verification.
- `animobj.cpp`: donors conflict on `Get_Bone_Transform` return type (`C2556`)
  and require missing `Rva001A5460` / `_slave` declarations. Reconcile the class
  view before retrying.
- `FXShaderParameterSourceNamespaceWW3D.cpp`: donor fails byte verification.
  Its mixed-source split would grow the `MakeDesc` hatch count and is refused.
- `UnitCrateCollide.cpp`: ctor signature is absent from the class view
  (`C2511`). Both mixed rows were tested; LinkGuard refuses moving their
  selected COMDATs without matching private/weak-free context.
- `RadarUpdate.cpp`: ctor trial gets duplicate `BehaviorModuleInterface` and
  `BehaviorModule` definitions (`C2011`); its mixed donor has no row approved
  for this TU.
- `CivilianSpawnUpdate.cpp`: ctor thunk converts `int` to `UpdateSleepTime`
  (`C2440`); module-data destructor fails byte verification.
- `ClickReactionBehavior.cpp`: ctor donor gets duplicate `UpdateModule`
  (`C2011`). The mixed field-parse split compiles alone but needs missing
  `ClickReactionBehaviorModuleData::m_fieldParse`; the other mixed donor has
  no row approved for this TU.
- `GiveOrRestoreUpgradeSpecialPower.cpp`: module-data ctor needs missing
  `m_vtable`, and the class ctor has no default `SpecialAbilityUpdate`
  constructor (`C2065` / `C2512`). Splitting the mixed getter is refused by
  LinkGuard because its selected string COMDAT lacks matching private/weak-free
  context.
- `BaseUpgrade.cpp`: implementation donor conflicts with a repeated
  `StringBase` template definition (`C2953`).
- `MonitorConditionUpdate.cpp`: module-data ctor tries to define an undeclared
  compiler-generated special member (`C2600`); the update donor fails byte
  verification. Its getter split is refused by LinkGuard because the selected
  string COMDAT lacks matching private/weak-free context; the field-parse split
  fails because the module-data destructor declaration is absent (`C2600`).
- `CaveContain.cpp`: ctor view lacks `m_FC` and `m_104` (`C2065`); the dtor
  would regress a census-linked unit by losing
  `OpenContain::getApparentControllingPlayer`. The mixed name-getter split
  cannot compile because `CaveContain` is undeclared (`C2065`/`C2070`).
- `W3DWaterTracks.cpp`: render donor conflicts on `RealRange` (`C2011`); flush
  donor lacks `TextureClass` (`C2065`) and has an additional include conflict.
  LinkGuard reported all three source units census-linked; no donor was
  accepted.

The prior shard handoff records the first sampled candidates and their
prerequisites. Dry runs and split trials wrote no sources or ledgers; no claims
remain. No identity, header, link or debt retirement is claimed.

Further allocated trials in this pass (no source changes or claims):

- `Made002CCB67.cpp`: the ctor donor was rejected by LinkGuard because its
  move leaves three `Rva00507823` vslot symbols unresolved in the census-linked
  unit (`vslot01`, `vslot02`, `vslot03`).
- `Common/AISimpleExpansionTactic.cpp`: its pull donor lacks class members
  `startCreateNewBase` and `m_owner`. The `0x005AAAD6` mixed split failed byte
  verification; the `0x005AA9DB` split was refused by LinkGuard because the
  moved selected vftable COMDAT lacks matching private/weak-free context.
- `Object/Contain/AODHordeContain.cpp`: no donor was accepted. The onContaining,
  xfer and pool-key donors require absent class-view members; the large body
  requires `LocomotorSet`'s Snapshot prerequisites; dtor, allocator and vector
  donors fail bytes. Mixed trials: ConstIntGetters4 fails on missing
  `Object::m_geometry`; GapBodiesGE22 would grow an escape hatch; the
  `EmissionInfoCopyCtors.cpp` split passes, but no merge donor is accepted;
  HordeContain split fails on missing `ModuleFactoryHookAt00469B9F`.
- `ProductionSpeedBonus.cpp`: its slot donor fails because `BehaviorModule` is
  undefined in the seed view; class reconciliation is required.
- `StatusBitsUpgradeIfEldestKindof.cpp`: the slot donor's
  `rva004CE2B0` method is absent from the class view; reconciliation is
  required. No mixed split was applied.
- `DetachableRiderBody.cpp` was re-read and its dry-run repeated the already
  recorded ctor/field-parse acceptance and link/class-view blockers; no new
  donor became acceptable.

No TU merge, split, file reduction, matched-row movement, identity retirement or
link improvement is claimed. No live claims remain from this pass.
- `Object/GlowMaterial.cpp`: `Rva003628A6Free.cpp` fails because `HeaderHolder`
  lacks `operator->`. All five mixed files were inspected: SnapshotXfers rows
  match alone but their split composition fails on duplicate `Xfer::Version`;
  RvaTreeEraseRangeFamily would grow a hatch; both tree-family residual splits
  fail on `_errno` linkage and duplicate STL pair templates; the map donor has
  no spelled definition for its candidate row. No split is accepted for use
  with this destination.
- `GameClient/Drawable/Update/W3DTornadoDraw.cpp`: the dry run accepts the
  destructor donor, but `tu_views.py --dry-run` reports a conflicting
  `W3DTornadoDraw` base clause (`public Rva000B19A1` versus no base) between
  the destructor and radius donors. Manual class-view reconciliation is
  required; no merge was applied.
- `GameLogic/Object/Made002CCC2D.cpp`: its sole destructor donor is rejected
  because `Made002CCC2D::Made002CCC2D` is a compiler-generated constructor
  not declared in the seed class view (MSVC C2600). Manual class-view
  reconciliation is required; no merge was applied.
- `Common/StatsReporter.cpp`: the strategic-results donor fails because the
  seed view of `LivingWorldLogic` lacks `getFrame` and `rva004EE037` (MSVC
  C2039); several class views need reconciliation. No merge was applied.
- `GameLogic/Object/Collide/CrateCollide/UnitCrateCollide.cpp`: its constructor
  donor fails MSVC C2511 because the seed class lacks the matching declaration.
  Splits for `ConstIntGetters4.cpp` and `Rva004BC4FCDerived.cpp` carve the
  selected rows and match alone, but LinkGuard rejects both for selected
  COMDAT context loss. No merge or split was applied.
- `WWVegas/WW3D2/FXShaderParameterSourceNamespaceWW3D.cpp`: the destructor
  donor from `Common` fails byte verification. The mixed namespace split
  carves six matching rows, but is refused because copying `MakeDesc` and
  `g_Va00DEDA28` would grow a hatch. No merge or split was applied.
- `GameLogic/Object/Behavior/ClickReactionBehavior.cpp`: its ctor donor
  encounters a duplicate `UpdateModule` definition. The field-parse split
  matches alone but fails because the module-data view lacks `m_fieldParse`;
  `Rva0024A797Grandchildren.cpp` has no row approved for this TU. No change.
- `GameLogic/Object/Update/ProductionUpdate.cpp`: dry run accepts no donors.
  The queue donor needs undeclared `Rva0049D526` (MSVC C2065), the dtor donor
  needs an undeclared `getDisabledTypesToProcess` member (C2509), and the
  quantity-modifier parser has a conflicting STL specialization (C2908).
  Class reconciliation is also required; no merge was applied.
- `W3DDevice/GameClient/Shadow/W3DShadow.cpp`: no donor was accepted; merge
  trials hit a duplicate `StringBase` definition and missing class members.
  The `R2GuardedGlobalCalls` split lost selected COMDAT context, the toggle-list
  split lacks `ReAcquireResources` in its view, and the time-of-day split would
  grow a hatch. No merge or split was applied.
- `GameLogic/Object/SpecialPower/HordeDispatchSpecialPower.cpp`: its pool-key
  donor is missing `getModuleNameKey` from the class view (MSVC C2509); the
  mixed `Rva00493DEFDerived.cpp` has no row approved for this TU. No change.
- `GameLogic/Object/Update/SiegeAIUpdate.cpp`: its sole ctor-thunk donor is
  refused by LinkGuard because moving it leaves `AIUpdateInterface`'s
  `GetSnapshotName`, `vslot094` and `vslot095` unresolved. The destructor split
  matches alone but LinkGuard rejects the residual/destination composition
  (new unresolved `GetSnapshotName` and `vslot094`). No change.
- `GameLogic/Object/Update/DockUpdate/SupplyCenterDockUpdate.cpp`: its
  constructor donor needs canonical `BehaviorModule` reconciliation
  (`behaviorModuleAnchor` missing, C2039) and registered module/class views.
  The `ModuleDataBuildFieldParseChained.cpp` split for 0x004A0DAC matches alone
  and passes LinkGuard, but no merge donor is accepted; the getter split fails
  on missing `Object::m_conditionBits` (C2039), the destructor split has a
  compile failure, and the RailedTransport row has no spelled definition.
  Nothing applied.
- `GameLogic/Object/SpecialPower/GiveOrRestoreUpgradeSpecialPower.cpp`: both
  constructor donors fail seed-view compilation (`m_vtable` undeclared, C2065;
  `SpecialAbilityUpdate` lacks a default constructor, C2512). The mixed getter
  split is byte-exact alone but LinkGuard rejects its moved selected COMDAT
  `??_C@_0CB@LPGPLBGO@GiveOrRestoreUpgradeSpecialPower@` without private/weak-free
  context. No change.
- `W3DDevice/GameClient/W3DTaint.cpp`: no donor is accepted: the destructor
  has conflicting STL `set` specializations (C2908/C2766), the interpolation
  donor fails compilation, and the matrix-set donor fails bytes. Its mixed
  destructor split would grow a hatch. No change.
- `WWVegas/WW3D2/animobj.cpp`: `AnimatableGetBoneTransform.cpp` has
  incompatible `Get_Bone_Transform` return declarations (C2556); the other
  donor lacks `Animatable3DObjClass::Rva001A5460` and `_slave` declarations
  (C2039/C2065). Class-view reconciliation and donor repair are required.
- `WWVegas/WWLib/registry.cpp`: `RegistryDeleteValues.cpp` is rejected for
  byte mismatch; no mixed files or other accepted donors. No change.
- `GameClient/GUI/ChatWindowsInGame.cpp`: the `Rva005AFE86Ctor.cpp` donor
  collides on `Rva005AFE3F` vftable type (C2373) and ctor declaration (C2511).
  The one-row mixed split matches alone, but with no accepted merge it would
  only increase file count. No change.
- `GameClient/GUI/GUICallbacks/Apt/AptMpGameRules.cpp`: two donors duplicate
  `_STL::allocator` declarations (C2953/C2913); `GameClient.cpp` conflicts on
  `HMODULE`/`HINSTANCE` (C2371). Mixed split trials fail on duplicate
  `_STL::vector` (C2953), missing `Rva0057EE5C` class context (C2653/C2065), or
  no spelled definition for 0x0057ED87. No change.

These trials wrote no sources or ledgers and took no claims. No TU merge or
split landed; file reduction and matched-row movement remain zero.
- `GameLogic/AI/Squad.cpp`: its contained-members donor requires `Object::contain`
  and `Object::id`, which are absent from the TU class view (MSVC C2039).
  Manual class-view reconciliation is required; no merge was applied.
