# Consolidation seat 1 continuation — 2026-11-04

The branch was rebased onto current `origin/master`; the inherited PlayerAITypeSet
work is present upstream. No source or ledger edits, claims, or merge trials were
left by this continuation. Every candidate below was an allocated, unheld shard
1 TU and passed `consolidation_queue.py --check-tu`. Its scoped
`name_lane.py consolidate` report passed `--check` before the TU plan and dry run.

## Additional TU trials

- `RunOffMapBehavior.cpp`: no donor accepted. Constructor and slot donors need
  the `RunOffMapBehavior` view reconciled. The mixed `ConstIntGetters4.cpp` split
  was refused by LinkGuard for the selected RunOffMapBehavior string COMDAT;
  the `BehaviorModuleDataBuildFieldParse.cpp` split was refused for link-clean
  regressions and a new duplicate field-parse symbol. The third mixed source had
  no row approved for this TU.
- `debug_io_con.cpp`: both destructor and constructor donors were refused by
  LinkGuard; the merged object loses the selected `DebugIOInterface` COMDAT and
  breaks another unit's `DebugIOCon` vtable.
- `AptAnimData.cpp`: `AptAnimDataRenderData.cpp` fails on missing `map` and
  `findSlot` declarations; the donor and TU are census-linked.
- `BfmeDfe6e4.cpp`: `Watchdog.cpp` and `WatchdogDtor.cpp` fail on the current
  `Watchdog`/mutex views; all three sources are census-linked.
- `AiOrdersManager.cpp`: patrol donor fails on the `Rva0054840A::ObjectID`
  self-reference and missing member; target and donor are census-linked.
- `lapi.c`: two common record-lookup donors have no baseline match; all involved
  sources are census-linked.
- `FireWeaponWhenDamagedBehavior.cpp`: Xfer and update donors hit duplicate
  `Weapon`/`Object` class declarations; class/view reconciliation is required.
- `AudioLoopUpgrade.cpp`: update, load-post-process, upgrade-implementation
  and Xfer donors need class/view repairs (`update` declaration, `StringBase`,
  or `UpgradeMux`); all five sources are census-linked.
- `AptArray.cpp`: the destructor donor needs `AptArray` private fields and the
  helper donor needs the `Rva006D6470Owner` base view. The Apt cluster split
  failed compile prerequisites; the AptArray constructor split is refused for
  escape-hatch growth. The `AptValueArrayAt.cpp` split trial was tool-accepted,
  but it stands alone and enables no accepted merge, so it was not applied.

No candidate passed the tool's requirement for a verified merge of two or more
donors. These are handoffs for TU view, provider, or LinkGuard prerequisites;
this seat made no manual repairs. The preceding shard trials and their evidence
remain in `consolidation-seat1-tail-20261104.md`.

Additional probes from the current shard reassessment are recorded in
`consolidation-seat1-reassessment-20261104.md`.

Current-shard allocator probes and exact compile/LinkGuard blockers are recorded
in `consolidation-seat1-current-probes-20261104.md`.

This session’s follow-on candidate and mixed-file trials are recorded in
`consolidation-seat1-session-20261104.md`.
