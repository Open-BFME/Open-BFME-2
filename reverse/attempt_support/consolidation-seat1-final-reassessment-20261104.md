# Consolidation seat 1 final reassessment — 2026-11-04

The current allocated shard 1 listing contained 88 unheld destinations. The
prior seat handoffs already record outcomes for the other candidates; the only
destination absent from those blocker records was `StrategicHUD.cpp`. It passed
`consolidation_queue.py --check-tu`, and the scoped Common name-lane report
passed `--check` before the TU plan and dry run.

## StrategicHUD.cpp

The plan found 140 approved rows, 3 donors, 16 mixed files, and one donor
refused because six rows are not approved for the TU. The dry run accepted no
donors:

- `Rva00579AB7Dtor.cpp` fails compilation because `DelegateDesc` is undefined
  and `StatsDisplayImpl` has a duplicate constructor declaration.
- `Rva00579D96Setter.cpp` fails on a duplicate `StatsDisplayImpl` vftable and
  duplicate virtual method declaration.
- The report requires view reconciliation for `Rva005796B3`, `Rva00579E47`,
  `Rva005CB260`, and `Rva005CB265`; it reports no verified merge of two or more
  donors. LinkGuard identifies the destination and both donor TUs as
  census-linked.

Mixed-file trials were inspected before stopping. `RvaSmallVtableCtors.cpp`
routes one row to StrategicHUD; the split matches bytewise alone but LinkGuard
rejects its constructor, vftable, and deleting-destructor COMDAT context.
`Rva00579731Dtor.cpp` routes three carved rows, but the residual would lose
matched rows and one class row has no name-spelling definition. `GapBodiesS3A.cpp`
routes three byte-matching rows but fails compilation on a redefinition of
`StrategicHUD::HUD`. `AptImageKeySetters.cpp` routes one candidate; three rows
match alone, while the combined destination fails on a duplicate
`StatsDisplayImpl` vftable. None was applied.

Four other destinations tested after the prior handoff—`LivingWorld.cpp`,
`HotKey.cpp`, `GameWindow.cpp`, and `StrategicInGameUI.cpp`—also accepted no
donors. Their exact compile prerequisites and LinkGuard findings are in
`consolidation-seat1-late-session-20261104.md`. The accompanying split trials
were refused: `OwnedPointerResets.cpp` duplicates `StrategicInGameUI`,
`Rva002BF4F3.cpp` loses selected COMDAT private/weak-free context, and
`GameWindowManagerSendMsg.cpp` loses `GameWindowManager::VirtualE0` and
`Virtual94`.

Across this reassessment no merge or split was applied, no claims were taken,
and no matched rows or source paths changed. The full allocated listing and
prior seat handoffs were checked; remaining work depends on upstream class/view
reconciliation or the reported tool-guarded link prerequisites.
