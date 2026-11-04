# Consolidation seat 1 session probes — 2026-11-04

Rebased shard 1/5 is still current; the complete allocator listing contains 100
unheld TUs. Existing continuation, reassessment, tail, repeat, and current-probe
handoffs cover prior candidates. This session took only read-only plans and dry
runs. No claims, merges, splits, source changes, or ledger changes were applied.

Fresh candidates each passed `consolidation_queue.py --check-tu`; each narrow
`name_lane.py consolidate --under ...` snapshot passed `--check` before plan and
dry-run:

| Destination | Mechanical blocker |
|---|---|
| `VeterancyCrateCollide.cpp` | Only donor lacks the target constructor declaration (`C2511`); both target and donor are census-linked. Reconcile `CrateCollide` / `VeterancyCrateCollide` views. |
| `FellBeastSwoopPower.cpp` | Constructor donor lacks its target overload (`C2511`); target and donor census-linked. Reconcile the `FellBeastSwoopPower` view. |
| `FlammableUpdate.cpp` | Dtor donor hits absent `TreeKey00242F5E::boneName`; two other donors fail bytes. Reconcile views; all affected sources census-linked. |
| `RadiateFearUpdate.cpp` | Update donor lacks `getModuleNameKey`; module-data dtor fails bytes. Reconcile `RadiateFearUpdate`; all sources census-linked. |
| `AnimationAsset.cpp` | `HAnimPrototypeOwnerCtor.cpp` duplicates `RefCountPtr`; `Rva0014D078LoadAnim.cpp` has five rows routed elsewhere. Both merge sources census-linked. |
| `LivingWorldAIArmyMover.cpp` | `DefendHomeTerritory` donor requires undeclared `BfmePod20`; both merge sources census-linked. |
| `AISkirmishPlayer.cpp` | Ctor donor has `PlayerList::Player` declaration error; other donor defines undeclared compiler-generated dtor. Reconcile `AISkirmishPlayer`; affected sources census-linked. |
| `ObjectTypes.cpp` | Constructor donor defines a compiler-generated constructor absent from the class view; both sources census-linked. |
| `SkirmishAI.cpp` | Dtor donor causes duplicate `_STL::_Rb_tree` explicit specialization; affected sources census-linked. |
| `VideoPlayer.cpp` | Donors fail duplicate `SubsystemInterface`, missing target members, or pointer conversion; all affected sources census-linked. |
| `HordeGarrisonContain.cpp` | Ctor donor needs missing `m_9E0`; 14 class/interface views need reconciliation; both merge sources census-linked. |
| `W3DRadar.cpp` | `Rva0004EFE9Ctor.cpp` duplicates `_STL::_Nonconst_traits`; another source has 21 rows routed elsewhere. Both merge sources census-linked. |

Mixed-file split trials:

- `ConstIntGetters4.cpp` -> `AISkirmishPlayer.cpp`: carved `0x004EF417`
  matches alone; destination still lacks `Object::getNextObject` and
  `Object::isKindOfCommandCenter`. LinkGuard blocked the combined composition.
- `SubsystemNameGetters4.cpp` -> `ObjectTypes.cpp`: carved `0x00376A19`
  matches alone; destination lacks `ObjectTypes::canBuildAny`. LinkGuard blocked
  the combined composition.
- `AnimationAsset.cpp` has no mixed files. Other fresh destinations above had
  mixed files listed in their plans; no split was applied. These and the
  unprobed allocated destinations remain for the next seat pass.

No task was claimed, so nothing needed releasing. No reduction or matched-row
preservation is claimed. Remaining prerequisites are class/view/header/compiler
repairs outside this seat, plus dry runs for the remaining allocated candidates
and their mixed routes.
