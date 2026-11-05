### Module-view C2039 merges: the one-line recipe is exhausted (2026-10-30, dd-32)

At base `a5c01ba2ba`, 62 approved TUs whose donor refusals name C2039 were run
through `tools/tu_views.py TU --dry-run` and a fresh
`tools/tu_skeleton.py --merge TU --dry-run` (the small-donor set of the
2026-10-29 merge map; the map itself is stale for this class of refusal).

Result: after the 2026-10-29 batches (`052be997ad`, `994ae1ced0`, `0ed602c54f`,
`2674d49106`) a refusal is no longer a single missing member. Every sampled TU
now fails on a *view hierarchy* disagreement, which `tu_views` reports as
CONFLICT and skips: the base clause differs (module ctor/dtor donors spell
`BehaviorModule`/`UpdateModule` by hand while Xfer donors include
`Include/Common/ObjectModule.h`), a declspec differs, or two views fill one
virtual slot differently. The merge keeps one spelling per type - the longest -
so a seed's minimal view usually loses, and the seed's own bodies then fail
(`'m_layout' : undeclared identifier` once AptLoadScreen's Init donor spelling
won over the seed's).

Sampled CONFLICTs (all with their donors present on master): EntEnragedUpdate,
PassiveAreaEffectBehavior, PickupStuffUpdate, PillageModule, WallHubBehavior,
GarrisonObjectGroupOrder (all: base clause), SynchronizeGroupOrder (fields
overlap at +0x18), GameLogicDispatch (GlobalData view), W3DGameFont (private
STLport template copies). Single-donor TUs in the same set cannot merge at all
(`blocked: no verified merge of two or more donors`): BoneFXDamage,
LockWeaponCreate, SupplyWarehouseCreate, FunctionLexicon.

2026-11-04 SynchronizeGroupOrder: member views now agree at +0x18/+0x24 (14/14 byte-matched; donor link predictions 259 -> 259); merge remains blocked on inheritance/virtual contracts and the constructor vtable provider. [Evidence and next check](../attempt_support/synchronize-group-order-container-20261104.md).

Two concrete hand reconciles, both verified and both still short of a merge:

- **AttackObjectGroupOrder** (16 approved rows, donors Ctor + Xfer, 3 mixed
  satellites). The TU's `slot03` is retail slot 3 =
  `?xfer@AttackObjectGroupOrder@@UAEXPAVXfer@@@Z` (vtable 0x0086A420; the Xfer
  donor's header names slot 3). Renaming `slot03` to `xfer(Xfer *)` and renaming
  the Xfer donor's `m_18`/`m_1c`/`m_20` to the seed's
  `m_targetID`/`m_b1C`/`m_pos` byte-verifies (TU 5/5, Xfer 1/1) and clears the
  C2039. The next refusal is structural: the donor calls `GroupOrder::xfer`, so
  the seed needs `GroupOrder` as a polymorphic base; the ctor donor spells
  GroupOrder non-polymorphic and declares
  `extern "C" const void *const __identifier("??_7AttackObjectGroupOrder@@6B@")[]`,
  which collides with the class's implicit vftable (C2373) even with
  `__declspec(novtable)` - and a polymorphic base renames that vftable to
  `??_7AttackObjectGroupOrder@@6BGroupOrder@@@`. Blocked on the "Module base
  chain" entry below; GarrisonObjectGroupOrder, SynchronizeGroupOrder and
  ChangeStanceGroupOrder have the same shape.
  2026-11-04: retired the seed's two stale AI-interface header rows through passing adoption verdicts; hierarchy/vftable merge blocker remains ([verification](../../reverse/attempt_support/attackobjectgrouporder-header-debt-20261104-codex.md)).
  2026-11-05: transfer donor merged through tu_skeleton (one fewer source, 6/6 rows; composition guard and local link previews pass). Constructor vtable conflict remains; full-batch audit awaits a newer census/current CreateAHero consumer receipt ([evidence](../../reverse/attempt_support/attackobjectgrouporder-xfer-20261105-codexb4.md)).
- **AptLoadScreen** (55 rows, picker item). `tu_views.py` applies and verifies
  four shared views (Rva00355D66, AptMapPreview, BfmeAptWindowManager,
  GameSpyStagingRoom) and reverts Rva0057E3DB (its funclet is not exact). The
  merge still refuses: AptLoadScreen's base clause differs (the Init donor
  spells no base) and the Init donor defines five virtuals while the seed
  deliberately declares only the destructor so its emitted vftable stays the
  ctor unit's COMDAT (retail 0x00C3D50C has six slots). Unblocking needs the
  full six-slot spelling in all three files, judged by the link guard.
- **PickupStuffUpdate**: base-clause CONFLICT cleared for five donors
  (2026-10-30, `bca81dd8bc` plus the merge after it). The seed now includes
  `Include/GameLogic/Module/BehaviorModule.h` and spells the full
  `UpdateModule : BehaviorModule, UpdateModuleInterface` chain, a
  `Snapshot`-based module data class with named fields, and an `Object` view
  with `m_ai` at +0x258. The donors were renamed onto the seed's names
  (`m_lastScanFrame`, `m_scanIntervalSeconds`, `m_ai`, `Thing` -> `Object`).
  `tu_skeleton.py --merge` absorbed the Xfer, Rva00491DD3, Scan, Update and
  moveToStuff donors (TU 16/16 matched). The ctor donor's hand vptr stores
  turned out to be unnecessary. Over the seed's views, the plain
  `: UpdateModule(thing, moduleData) { m_lastScanFrame = 0; m_20 = false; }`
  byte-matches, and `link_check.py` reports LINKS 50 -> 50. It is merged
  too (TU 17/17). Still refused: `PickupStuffUpdateModuleDataCtor.cpp`
  (C2600, an `EmptyBase` and vtable-as-data spelling, plus a `novtable` seed
  view of the module data class).
- **MonitorConditionUpdate** (2026-10-30, `77de164a30` plus the merge after
  it). The same ctor recipe works. Over the seed's views, plus a declared ctor
  and an out-of-line `virtual ~MonitorConditionUpdate()`, the body
  `: UpdateModule(thing, moduleData) {}` byte-matches 1/1 and LINKS 45 -> 45.
  Without the dtor declaration, the ctor unit emits a COMDAT `??1` that is not
  retail's. The Dtor donor is merged (TU 11/11, LINKS 152 -> 289), and its
  unreferenced `/alternatename` was dropped. The ctor donor still waits:
  the link guard refuses it ("a file without a census object would place the
  merged unit earlier") until a census taken after the 09:52 Xfer merge
  places the seed at 0x4915C6. Also refused:
  `ModelConditionSpecialAbilityUpdateModuleDataCtor.cpp` (C2600, the seed's
  module data view declares no ctor) and `MonitorConditionUpdateUpdate.cpp`
  (bytes).
- **PillageModule** (2026-10-30, `b6945d1b9b`, `e6b5903f49`). The Xfer donor is
  merged. `PillageModuleCtor.cpp` calls base `??0Rva00588FFA` while xfer
  calls `Rva00589051::xfer`, which are two placeholder names for one base class.
  Unifying them is naming-lane work and has to come before that donor can
  merge. `PillageModuleRva00484FE2.cpp` compiles `/O1 /G7 /arch:SSE` against a
  flat +0x10 subobject view.
  **2026-11-04 consolidation recheck:** current allocation still accepts no
  donor: the ctor view lacks its constructor and the `/O1` donor hits the
  `GeometryInfo` slot contract. Splitting the mixed getter/destructor files is
  refused by LinkGuard because the destination would move selected string,
  destructor and vftable COMDATs without private/weak-free context. Exact trial
  evidence: [seat 1 continuation](../attempt_support/consolidation-seat1-trials-20261104.md).
- **GiantBirdSlowDeathBehavior** (2026-10-30, not committed). The rewritten
  ctor byte-matches 1/1 over the seed's views, plus declared `SlowDeathBehavior`
  and `GiantBirdSlowDeathBehavior` ctors. It does not link: the seed's placeholder
  slots `?dieSlot@DieModuleInterface` and
  `?unknownBehaviorSlot@BehaviorInterface` are unresolved, and an implicit
  `??1UpdateModule` COMDAT is emitted. The data ledger owns the class's
  vftables (0x842E64/0x842DA8/0x842D98/0x842D88) as
  `??_7Rva00461EEB@@6B...`, and `Rva0045D39EDerived.cpp`'s dtor 0x461EEB
  installs the same set. `Rva00461EEB` therefore looks like
  GiantBirdSlowDeathBehavior (and `Rva0045D39E` like SlowDeathBehavior), but
  that is vtable evidence, a hint only. `rename.py class` refuses folding it
  into the existing name. The class identity has to land first.

Reproduce: `python3 tools/tu_views.py <TU> --dry-run`, then
`python3 tools/tu_skeleton.py --merge <TU> --dry-run`.
