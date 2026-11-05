# WoundArrowUpdate mechanical consolidation trial (2026-11-05)

The current allocated TU plan has 13 approved rows, three donors and two mixed
sources. `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
and `--check build/consolidation` passed. The merge dry run reported no
accepted donors and `blocked: no verified merge of two or more donors`.
`WoundArrowUpdateCtor.cpp` and `WoundArrowUpdateSlot17.cpp` fail because the
seed does not provide a compatible `SpecialAbilityUpdate` base/default
constructor view; reconciliation also names `AIUpdateInterfaceHead`, `Object`
and `WoundArrowUpdate`. LinkGuard recognizes the seed and both donors as
census-linked.

Mixed split checks:

- `ConstIntGetters4.cpp --for WoundArrowUpdate --dry-run` carved RVA
  `0x004C693D`; its 1/1 standalone bytes match, but combined compilation fails
  because the seed's `Object` view lacks `m_conditionBits`.
- `Rva00451F45Derived.cpp --for WoundArrowUpdate --dry-run` carved RVA
  `0x004C6943`; both bodies match, but LinkGuard refuses three selected COMDATs
  (`??1Rva004C6943@@UAE@XZ` and its two vftables) for lacking matching
  private/weak-free context.

No source was split or merged and no claims were taken. Next work requires the
class-view reconciliation and a safe COMDAT/link composition; do not repeat the
unchanged split trials.
