# Consolidation shard 1 follow-up trials (2026-11-04)

The read-only allocator listed 72 destinations at `--limit 100000`. Each TU
below passed `--check-tu`; its parent-scoped consolidation planner was current,
`tu_skeleton.py --plan` was inspected, and `find_declared_unmatched.py` passed.
Each single `--merge TU --dry-run` accepted no donor and reported
`blocked: no verified merge of two or more donors`. No sources, ledgers or
claims were changed. The LinkGuard census-linked the destination and relevant
donors where listed; no merge was applied around a refusal. Manual repair is
outside this mechanical lane.

- `AudioLoopUpgrade.cpp`: `AudioLoopUpgradeUpdate.cpp` has undeclared `update`
  (C2509/C2039); `AudioLoopUpgradeLoadPostProcess.cpp` has duplicate
  `StringBase` (C2953) and undeclared `loadPostProcess`; implementation and
  Xfer donors lack the `UpgradeMux` base (C2504/C2614). Planner recommends
  reconciling `ALU_Iface4`, `AudioLoopUpgrade` and its module-data view.
- `HordeMeleeAmoeba.cpp`: the setUnit donor and game-logic Xfer fail STL
  `vector::resize` explicit-instantiation checks (C3190); another donor has a
  negative subscript (C2118), the family dtor has an undeclared
  `EmitVtableTag` constructor (C2511), and another donor duplicates allocator
  and vector templates (C2953). `stlport_sort_rva00588195.cpp` is refused by
  LinkGuard: merged selection changes the retail `copy_backward` COMDAT.
- `SynchronizeGroupOrder.cpp`: slot donor defines a compiler-generated
  constructor (C2600); dtor and Xfer compositions see an abstract class
  (C2259), and Xfer is undeclared (C2509). Planner recommends class-view
  reconciliation.
- `CashHackSpecialPower.cpp`: action composition duplicates `UnicodeString`
  and `Coord2D` (C2011); module-data ctor duplicates a body (C2084); module-data
  dtor composition duplicates `ModuleData` and `Overridable` (C2011). Planner
  recommends reconciling `CashHackSpecialPower`.
- `CurseSpecialPower.cpp`: the ctor donor is refused by LinkGuard because the
  merged object selects duplicate `??_7CurseSpecialPower@@6B@` COMDAT.
- `BuildableHeroListUpgrade.cpp`: ctor donor defines an undeclared
  `Thing *, const ModuleData *` constructor (C2511); planner recommends
  reconciling `BuildableHeroListUpgrade`.
- `PartitionManager.cpp`: rejected donors require conflicting or absent views:
  `CDELeading` declaration syntax, duplicate `AsciiString`, duplicate
  `PartitionData` and missing members, private `CellAndObjectIntersection`
  access, and duplicate `friend_updateCellsTouched` declaration. Planner
  identifies seven class views for reconciliation.
- `BfmeItemKA.cpp`: `GameSubTitle.cpp` duplicates `StringBase` and lacks
  `m_count`; `GameSubTitleDraw.cpp` lacks `rva002600DC` and `m_startFrame`;
  two STL sweep donors fail byte verification. Planner identifies three subtitle
  views for reconciliation.
- `StdioStreambufBase.cpp`: the default narrow streambuf donor duplicates
  `char_traits`/`fpos` templates (C2953); two narrow streambuf donors conflict
  on `_STL::locale` and `facet` (C2011/C2039).
- `VideoPlayer.cpp`: three class donors duplicate `SubsystemInterface` and
  lack `Rva00689180`/other class members; the element dtor donor cannot convert
  `void *` to `Rva00688980 *` (C2440). Planner identifies three view groups.
- `PlayerList.cpp`: donors conflict on `SubsystemInterface`, lack `Int` and
  class members (`getUnknown3AC`, `DoXfer`, `m_playerCount`), and have an
  invalid `PlayerList` member initializer. Planner identifies seven view
  groups.
- `GameLogicDispatch.cpp`: clear-game-data composition has syntax errors at
  `VS`; another donor duplicates `SubsystemInterface` and related shell types.
- `PolygonTrigger.cpp`: two constructor-related donors see incomplete
  `PolygonTrigger`/missing `addPolygonTrigger`; the permuted donor has a
  negative subscript and missing member `rva00330AA6`. Planner identifies four
  class/struct views.
- `GSConfig.cpp`: a donor fails matching `_STL::allocator::deallocate`
  (C2244); another lacks `_STL::set::insert` (C2039); the vslot donor fails
  byte verification. Planner identifies three `Rva0054F434` view groups.

Existing allocated dry-run blockers and completed merges remain in
`siegedeploy-consolidation-20261104.md`; in particular, do not retry unchanged
entries recorded there. Remaining candidates from the 72-entry allocated
listing were not tested in this session and require fresh allocation checks and
their own narrow planner runs.

## Preserved handoff notes from the prior file version

- `Code/Libraries/Source/Lua/lapi.c`: the allocated check, scoped planner,
  destination plan and guarded dry run completed. Neither proposed record-lookup
  donor was accepted: both had no baseline match. LinkGuard reports all three
  objects census-linked. No source edits or claims.
- `Code/GameEngine/Source/GameLogic/System/RankInfo.cpp`: the allocated check,
  scoped planner, destination plan and guarded dry run completed. No donor was
  accepted. LinkGuard refused the destination composition because it creates a
  duplicate selected `?theRankBlockParse@@3UBlockParse@@A`; `RankInfoParse.cpp`
  also failed bytes, and the planner requires `Overridable` adoption first.
  Census-linked units are listed in the tool report. No source edits or claims.

The `W3DFloorDraw.cpp` accepted-donor trial was restored after staged identity
and data shadow checks reproduced the existing blocker recorded in
`w3dfloordraw-merge-identity-audit-blocker-20261104.md`; all 32 owned claims
were released. Do not retry without resolving that prerequisite.
