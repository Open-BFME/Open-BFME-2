# DamageNugget.cpp TU merge: blocked on slot names

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/DamageNugget.cpp
--dry-run` accepts none of its four donors (`Made002CC5E1Rva00507991.cpp`,
`Made002CC5E1Rva00507A04.cpp`, `DamageNugget_generateDamageInfo.cpp`,
`Made002CC5E1Rva005084FC.cpp`). `tu_views.py --dry-run` reports the
`DamageNugget` conflict "virtual slot 14 differs", a misplaced `Object` view in
`generateDamageInfo` (`module04` at +0x4 under the bases), and pending adoption
of `Code/GameEngine/Include/GameLogic/Module/Rva00507823.h`.

## Retail facts (target bytes)

- The base table `0x00864010` has 14 slots: `0x00507807` (`??_G`),
  `0x005075D6`, `0x0050774A`, `0x0050B238` x2, `__purecall` x3,
  `0x00507877`, `0x0050B238`, `0x000D43D0` x2, `0x0047A699` x2.
- The `DamageNugget` table `0x00864048` has 15 slots:

  | Slot | RVA | Ledger row |
  |---|---|---|
  | 0 | `0x00508668` | `??_G` |
  | 1 | `0x005086CE` | `rva005086CE`, rowed `QAE` (non-virtual) |
  | 2 | `0x00507943` | `rva00507943` |
  | 3 | `0x0050797D` | `rva0050797D` |
  | 4 | `0x00507A04` | `v4` |
  | 5 | `0x00507991` | `rva00507991` |
  | 6 | `0x00507D84` | `doEffectPosition`, rowed `QAE` |
  | 7 | `0x0050B5C6` | shared |
  | 8 | `0x00507877` | inherited |
  | 9 | `0x0050B238` | inherited |
  | 10 | `0x0047A6A9` | shared ICF |
  | 11 | `0x000D43D0` | inherited |
  | 12, 13 | `0x0047A699` | inherited |
  | 14 | `0x005084FC` | `rva005084FC`, rowed `QAE` |

## Why the views cannot be unified mechanically

Every body except slot 14 overrides a base slot. In C++ an override must reuse
the base's name and signature. The canonical header names those slots
`rva005075D6`, `vslot02`..`vslot06`. The ledger spells the overrides
`rva005086CE`, `rva00507943`, `rva0050797D`, `v4`, `rva00507991` and
`doEffectPosition`, with different parameter types. So under the canonical base,
the overrides become new virtuals at slot 14 and above, and calls such as
`rva0050797D` → `v4` (vtable +0x10) and `rva00507991` → `v1`/`v6`/`v14` no
longer hit retail's slots.

`Made002CC5E1Rva00507991.cpp` works today only because its private base view
declares a destructor alone, which flattens all 15 slots into `DamageNugget`.
`Made002CC5E1Rva00507A04.cpp` already uses the canonical header, so its `v1`
lands at slot 14. That is the conflict `tu_views` reports.

## Ways forward (naming-lane work, `docs/naming.md`)

1. Give each override and its base slot one spelling: either rename the
   canonical header's slots to the recovered names, or respell the
   `DamageNugget` rows to the base names through `rename.py`. Then every
   `Rva00507823` subclass in the header's 37 consumers must be checked, and
   the `QAE` rows at slots 1, 6 and 14 need virtual (`UAE`) spellings.
2. Next, adopt the canonical header in the seed and in
   `Made002CC5E1Rva00507991.cpp`, unify the `Object` views (also
   `Rva005084FCModuleView` and `Rva2225E0Filter`), and rerun the merge
   dry run.
