# AutoHealBehavior PoolKey consolidation

Prerequisite: `806d41c5b1` replaces the seed's imported legacy declarations with
canonical UpdateModule/UpgradeMux bases (see the companion canonical-seed report).
The supported planner snapshot passed its currency check before application.
`tu_skeleton.py --merge` now absorbs AutoHealBehaviorPoolKey.cpp into the approved
Behavior/AutoHealBehavior.cpp TU: one source file removed, all nine rows retained.
The constructor, Xfer, reset, pulse and PlayerScan donors remain in place.

## Verification

- Frozen-file check passes; normal build verifies 9/9 code rows and the pool-name
  literal. The static guard's compiler label changes from $L306 to $L1904;
  parent EH placement verifies the original 0x00789c2b row. EH graph: EXACT 1/1.
- CSV integrity passes with 99,455 function rows. No row or coverage is added.
- Shadow data check has zero findings. The tool transfers exactly two
  data-ledger owners (0x00a033d4 key and 0x00a033d8 guard), preserving names,
  addresses, sizes and counts. No debt key is retired. Header/ms-header refresh
  produces no queue diff; neither donor nor seed has data/identity/hatch keys.
- The TU map is only repointed for the three moved source cells; assignments,
  confidence and evidence are unchanged. It is not regenerated.
- The census seed+PoolKey COMDAT union has 551 names; all ten retained definitions
  have identical digests, with no added definitions. The earlier seed cleanup
  removes 541 definitions: 540 retain equal-digest census providers, and the
  unique module-data getter has no other census consumer. No weak aliases change.
- The merge guard preserves the census-linked units. Ordinary scoped preview
  reports LINKS for all 236 authored bytes in the combined TU (167 seed + 69
  parent); EH rows are separately checked. This is preserved coverage, not a
  census gain or a real game link. The wider batch audit is recorded separately.

## Combined outgoing path-consumer audit

Audited the pending ProductionQueueHordeContainXfer.cpp absorption and this
AutoHealBehaviorPoolKey.cpp absorption together, including the seed prerequisite.
Searched donor basenames and full paths through tools, hooks, workflows, Code,
docs, reverse registers, reference shims and root build/config files. No active
hard-coded include, picker, build list or tool consumer requires an update.
Ledger and TU-map owners are repointed by the merge tool. Remaining old paths
are destination provenance comments, deleted-row explanations, historical
attempt evidence/logs and the last measured link_status.csv; those remain honest
history. Doxygen has no PoolKey source entry and already names the production
queue destination. The earlier production-queue audit remains applicable.

Remaining prerequisites: reset/Xfer/pulse need declarations and canonical-layout
member reconciliation; the constructor conflicts with the damage-interface
vftable declaration; PlayerScan has Coord2D/Coord3D include conflicts and its
remaining ContainModuleInterface/GeometryInfo/ThingTemplate header debt. Mixed
helper files were not split. Reconcile each donor separately before retrying.

## Wider outgoing batch audit

For range `73cb536e06..c475e7da48`, prepared strict reusable receipts through
`link_check.py --prepare-current` for both changed destination TUs: 26/26 rows
and literals pass. The subsequent `link_batch_audit.py` result is INCONCLUSIVE:
the index is at c95fcfcfcd, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. The audit did not reach a complete consumer verdict. Carry that wider
closure into the next census; the clean scoped preview and COMDAT comparison
above do not establish a clean full batch or a real-link gain.
