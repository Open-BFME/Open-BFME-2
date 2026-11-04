# Consolidation shard 0/5 follow-up — 2026-11-04

Continuation after the prior shard handoff. The pending documentation handoff
commit was present in the clean checkout; the current source tree had no
preserved trial edits or active claims. The full allocator listing had
`W3DGameClient.cpp` and `matpass.cpp` unheld, and each passed its current
allocation check before its trial.

- `W3DGameClient.cpp`: no donor accepted. The seed itself failed every merged
  flag set at `cpudetect.h(171)` (`C2146`, missing `;` before
  `Get_Processor_Ticks_Per_Second`); other donors need `W3DGameClient` and
  `Rva004C743` members. LinkGuard reported the seed and relevant donors as
  census-linked. No apply or claim.
- `matpass.cpp`: no donor accepted. `MaterialPassClassDestructor.cpp` and
  `MaterialPassInstallMaterials.cpp` each lost two baseline rows under the
  carried empty flag override; `Rva0013EEB0Cluster.cpp` and
  `Rva0013EF40Siblings.cpp` had no baseline match; the ctor donor needs
  additional `MaterialPassClass` fields. No apply or claim.
- `InheritUpgradeCreate.cpp`: no donor accepted. Constructor, xfer and
  onBuildComplete donors require missing class members; the module-data ctor
  needs its special member declared in the class. The planner recommends
  reconciling `InheritUpgradeCreate` and `InheritUpgradeCreateModuleData`
  views. No apply or claim.

All three dry runs were left unchanged. Next untried candidate in the allocated
shard listing is `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp`;
recheck allocation and generate a fresh scoped name-lane report before
planning it. Do not repeat these failures unless their named prerequisites
change.
