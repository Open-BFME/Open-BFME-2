# Base evidence for 60 BFME2-specific classes, and one placeholder worth naming (2026-11-07)

121 registered classes record no bases in their contract while their canonical header
declares some. 60 of those have no Zero Hour reference at all, so the ZH probe fix
(d73d3dde8bd) cannot help them and only BFME2 evidence can. This is a read-only pass over
all 60, one reviewer per ten. Nothing was applied: no contract, header, source or ledger
row changed.

`evidence.json` holds every record. Of the 60: 41 produced real evidence (a base
constructor call, a vtable slot naming a base's method, or an upcast), 6 are size
arithmetic only, and 13 came back empty. 36 support the header's base clause, 8 contradict
it, 16 are undetermined. Confidence runs 10 high, 25 medium, 25 low - most of this is a
starting point for a reviewer, not a verdict.

## The one concrete, actionable finding: Rva0020E346 is RegionTurnObserverView

Separately from the reviewers, retail's own facts were checked across all 121. Only **six**
record vptr stores at more than one offset - the signature of a second polymorphic
subobject, which is the one base shape retail *can* see. All six carry a `bases_unproven`
fact, and that fact already names what it found:

| class | vptr offsets | base retail names |
|---|---|---|
| LivingWorldArmy | 0x0, 0x4 | `Rva0020E346` at 4 |
| LivingWorldBuilding | 0x0, 0x4 | `Rva0020E346` at 4 |
| LivingWorldBuildPlot | 0x0, 0x4 | `Rva0020E346` at 4 |
| LivingWorldBattle | 0x0, 0x4 | `Rva00575E4EBase2` at 4 |
| SidesList | 0x0, 0xc | `SubsystemInterface` at 0 |
| LivingWorldLogic | 0x0, 0xc, 0x10, 0x14, 0x18 | `SubsystemInterface` at 0 |

So these are not cases where retail saw nothing. Retail proved the shape and named the
subobject; the name is a placeholder, which `retail_bases` declines to adopt - correctly.

`Rva0020E346` can be named from rows that have already landed. Its own ledger row reads
"Small vtable ctor copy: vftable 0x00C62A20 stored and this returned (9B; a class whose
only state is its vtable); owner unrecovered so address-derived". The landed rows
`?BeginTurn@RegionTurnObserverView@@UAEXHH@Z` and `?EndTurn@RegionTurnObserverView@@UAEXHH@Z`
describe themselves as slots 0 and 1 of "native whole two-entry base table C62A20" and as
an "inherited empty callback" with an "empty two-int ABI". Same table, same empty-polymorphic
shape, and `RegionTurnObserverView` already has a header and five ledger rows.

Naming that one placeholder would let retail name the base for three contracts at once.
Independently, a reviewer found a prior blocked attempt (re_attempts.log line 80725)
recording retail vptr stores for the RegionTurnObserverView and Snapshot subobjects of
LivingWorldBuildPlot, which points the same way.

**One link is not reconciled and should be before anyone acts.** The EndTurn row's note
writes the build-plot secondary table as `C63528`, while LivingWorldBuildPlot's contract
records its +4 vptr as `0x863528`. Those differ by more than a typo's worth of digits in
the high byte, and I could not resolve which is right from the ledger alone.

## Reviewer findings worth carrying forward

Strongest confirmations, each resting on something other than the header:
- **LivingWorldBattle** - the ledger names its two tables outright,
  `??_7LivingWorldBattle@@6BSnapshot@@@` and `??_7LivingWorldBattle@@6BLivingWorldBattleListener@@@`,
  and `LivingWorldBattle_AddArmy.cpp:73` upcasts `this` to `LivingWorldBattleListener*`.
- **SphericalEmissionVelocityInfo** - `EmissionInfoCopyCtors.cpp:86` has an explicit
  `: EmissionVelocityInfo(that)`, with re_attempts.log:101066 recording the same for its
  Cylindrical and Outward siblings.
- **ArmySummaryEntry** - `ArmySummaryEntry.cpp:55` has `: CarryoverUnit()`.
- **TerrainCollisionModuleInfo** - `: Snapshot(that)` in its matched copy constructor.
- **GateOpenAndCloseBehaviorModuleData** - retail vtable slot 2 is `?GetSnapshotName@ModuleData@@`.

Contradictions and prior verdicts that outrank the header:
- **Rva005248D0**: re_attempts.log:25337 records "no supported inheritance explanation" and
  link-245 is still blocked. Do not treat its header clause as a target.
- **StancesBehavior**: `UpdateModule` is confirmed, but `Rva00330757Member` is a *member* at
  +0x20 in the constructor notes, not a base.
- **ArmySummary**: its +4 base is `Rva0040D8D6List` by header and by re_attempts.log:20532,
  but `Rva00330757Member` in a header comment and the private views - two recorded answers
  that disagree.
- **InGameHeroSelectInterface** and **InGameCommandButtonHelp**: "Impl" is a nested class,
  not a base. See the extraction caveat below.

## A correction to how the 121 was measured

The figure 121 is sound in substance - in every one of those classes the header has a base
clause and the contract has none. The *names* attributed to the clause are not uniformly
reliable: the extraction took bare identifiers out of the text, so 20 of the 121 are
suspect. It splits template and qualified bases into fragments (`std::map<AsciiString,
MapMetaData>` became `std`, `map`, `AsciiString`, `MapMetaData`; `_STL::list<Drawable>` and
`EA::Allocator::GeneralAllocator` likewise), it let the `private` keyword through because
only `public` was filtered, and it reads a nested forward declaration as a base. 101 of the
121 parse to names that are all known classes; the other 20 need their clause read by hand.
One of those 20, MapCache, was counted as a ZH disagreement in
`reverse/attempt_support/zh-probe-bases-20261107/` and is not one.

Reviewers also flagged, unprompted, that much of the retail detail they cite - dtor base
table restores, EH maps, vptr offsets - was taken from header comments rather than
re-derived from the image. Those items are labelled in `evidence.json` and should be
re-derived before anything lands on them.
