# LivingWorldRegionManager header adoption, 2026-11-04

Inspected revision: `3fb56d4ce7`. Seat: `yasinschroeder-codex3`.

The default picker served TU approval for
`Code/Libraries/Source/WWVegas/WWLib/LivingWorldRegionManager.cpp`, citing
42 proposed rows in 31 sources. The committed TU map is stale. The supported
planner (`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WWLib/`)
and `tu_skeleton.py` rebuilt current assignments in memory; no regenerated
map is committed. Current plan for the WWLib path has 24 approved funclet/EH
rows and one donor. The game-path TU has 88 approved rows, but its merge dry
run refuses because its existing source holds rows assigned to another TU.

## Applied prerequisite repair

Two sources now include the existing canonical
`Code/GameEngine/Include/GameLogic/LivingWorldRegionManager.h` instead of
privately defining the class:

- `LivingWorldRegionManagerPendingBattleLookup.cpp`: six rows at
  0x0020E501/60, 0x0020E53D/66, 0x0020E57F/60, 0x0020E5BB/66,
  0x0020E5FD/66 and 0x0020E6C0/22 (340 bytes).
- `LivingWorldRegionManagerCompleteBattle.cpp`: 0x0020FB8B/132.

Paths above are relative to
`Code/GameEngine/Source/GameLogic/System/LivingWorld/`.
The former vector views now cast the canonical raw storage at +0x14 and +0x20
back to the consumer's existing element types; the selected key uses the
canonical +0x10 field. Template specializations and link declarations remain.
No shared header, function identity, ledger extent or source path changes.

Target facts: the pre-existing canonical header documents the native accesses
and three vector headers. This repair preserves the consumer-specific template
identities; it does not establish an original vector element name.
A trial caching the lookup vector in a local reference changed alias analysis
and hoisted loop bounds, failing byte checks. Re-deriving the cast per access
preserves retail's loads. That failed trial is not retained.

## Verification

- Before and after: `./build.sh` with both source paths passes all 7/7 rows,
  string, float and import checks.
- `find_declared_unmatched.py` with both paths: all defined functions matched.
- `header_adopt_lane.py accept --class LivingWorldRegionManager` with both
  paths: PASS/PASS, retired exactly two rows from `reverse/header_queue.tsv`.
- `link_check.py --fetch-index`: published index at `a62ac1c10b`,
  2026-11-04 07:28; 18,288 objects imported into the object store.
- `link_check.py` with both paths: 2/2 link cleanly; lookup 340 -> 340,
  completion 132 -> 132, combined 472 -> 472 bytes. This is a preview,
  not a new census, real game link or runtime claim.

## Remaining source recovery boundary

Current in-memory map reports eight game-TU rows with other assignments:

| RVA | Current destination | Confidence |
| --- | --- | --- |
| 0x0020E4BC | game LivingWorldRegionBonusRule.cpp | proposed, noncontiguous |
| 0x0020F143 | game LivingWorldRegionBonusRule.cpp | proposed, noncontiguous |
| 0x0020F34E | WWLib LivingWorldRegionManager.cpp | proposed, noncontiguous |
| 0x00210AB8 | game LivingWorldRegionBonusRule.cpp | proposed, noncontiguous |
| 0x0076D56A | WWLib LivingWorldRegionManager.cpp | approved, parent 0x0020F34E |
| 0x0076D572 | WWLib LivingWorldRegionManager.cpp | approved, parent 0x0020F34E |
| 0x0076D86A | game LivingWorldRegionBonusRule.cpp | approved, parent 0x00210AB8 |
| 0x0076D874 | game LivingWorldRegionBonusRule.cpp | approved, parent 0x00210AB8 |

`LivingWorldRegionBonusRule`'s naming hints at 0x0020F143 and 0x00210AB8
conflict with their WorldBuilder path hint naming the manager TU. These are
leads, not proof that either assignment should be overridden. Resolve the
parent-body ownership/name evidence before moving their funclets; proposed
body assignments do not authorize a split. Other canonical-header adoption
prerequisites remain in the main manager, validation and transfer consumers.
No TU-approval increase, merge or linked-byte gain is claimed here.
