# BattlePlanUpdate Player-view prerequisite

2026-10-29; source base `e4cdc1ce6442`; claim owner
`yasinschroeder-codexb4`.

The default picker selected the approved BattlePlanUpdate.cpp TU and eight
whole-file donors. The earlier pool-key composition remains intact. The current
supported merge dry run accepts no donors; this is cleanup of existing private
views, not recovery of an unrowed body or a linking regression.

The naming planner ran under GameLogic/Object/Update; its original-path evidence,
alternatives and blockers were reviewed. The merger rebuilds current placement
in memory. No regenerated TU map or path move is committed. The initial
`./build.sh` checks all nine claimed sources: 30/30 functions, three string
literals and seven float literals pass.

`tu_views.py --class Player` identifies compatible partial views in the seed,
SetBattlePlan and createVisionObject. Its compiler layout check retains `index`
at +0x54 and `m_team` at +0x2EC, with extent 0x2F0. These are reconstruction
layout facts from the existing sources and compiler, not a recovered retail
class definition. The combined declaration includes the two already declared
methods, changeBattlePlan and iterateObjects, without adding definitions.

The first application rolls back because the seed declares BattlePlanStatus
after Player. Moving the existing enum before Player, and supplying that enum
in createVisionObject, lets the supported tool apply the same Player block to
all three files and byte-verify each. Function bodies remain unchanged.

## Verification

- Final strict `link_check.py --prepare-current` passes for all three providers:
  20/20 functions, three strings, five floats, and the parent-verified funclets.
  An earlier preparation overlapped the merge probe's temporary source files
  and correctly refused moving inputs. The final preparation runs after the
  probe exits and writes three current strict receipts.
- Before/after COFF comparison preserves all 31 external COMDAT fingerprints
  (bytes and relocation identities) and all 83 external symbol records,
  including defined/undefined roles. Per source: 24/52, 6/22 and 1/9.
- The ordinary link preview against index `85f6b7f40c` retains LINKS for all
  three units: 1,548, 732 and 157 authored bytes, respectively (2,437 total).
- Frozen-body and canonical-class checks pass. Converged data checking covers
  11 addresses with no second names or unjudged rows. Microsoft-header scan
  finds no local Microsoft declarations in these sources.
- The staged-tree batch audit is INCONCLUSIVE: index `85f6b7f40c` predates
  the source base and an affected consumer,
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`, lacks a current
  receipt. Carry that consumer and these three providers into the next normal
  census. The ordinary preview and unchanged object facts establish only the
  bounded provider result above.

## Remaining composition work

The post-reconciliation supported merge still accepts no donors. Its generated
declaration ordering exposes BattlePlanStatus before its definition in the
command-option and plan-setting combinations, and Player before its declaration
in the vision combination. Other rejected donors still need constructor,
destructor and onObjectCreated member declarations and Xfer/BitFlags syntax
reconciliation. The tool also reports conflicting ModuleData class keys,
AudioManager slot names, Object interfaces, module base clauses and overlapping
bonus views. Thing requires its canonical-header lane in the seed and vision
source. The five mixed sources are unchanged.

This removes one private-view discrepancy, not all prerequisites. Do not retry
the same full merge without addressing those recorded blockers. No ledger,
debt-register or hatch count changes; no source-file reduction, census-linked
gain or image-ownership result is claimed. Complete provider/consumer closure
must be confirmed in the next scheduled census.

## Preserved targets handoff during preparation recovery

The shared targets document was claimed by another worker at recovery. Its
upstream content is retained; the original handoff is preserved here:

BattlePlanUpdate Player views (2026-10-29, base `e4cdc1ce6442`): three private
views now agree, retaining 20/20 rows, all 31 COMDAT fingerprints and the
2,437-byte LINKS preview. Strict current receipts pass. The supported merge
still needs declaration ordering, module interfaces and canonical Thing header
work; no source move or census gain occurs. Carry the affected providers and
consumers into the next scheduled census.
The older-index batch audit lacks a current 0CreateAHeroManager21FE49.cpp
consumer receipt, leaving broader closure unverified.
[Evidence and remaining prerequisites](battleplan-player-views-20261029-codexb4.md).
