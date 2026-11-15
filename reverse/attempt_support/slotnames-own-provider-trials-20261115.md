# Own virtual-provider trials, 2026-11-15 (slotnames)

Approval revision: `7ff1670043d`; parent `99e9b3de8e3`. No implementation change is claimed by this report. Slot votes are independently agreed, not canonical name evidence or symbol definitions.

## AIInternalMoveToState slot 2, own target 0x0033F2F7

Supported `rename.py function --rva 0x0033F2F7 --to-class AIInternalMoveToState --new ?GetSnapshotName@AIInternalMoveToState@@MBEPBDXZ --approval-base HEAD --no-claim --prepared ...` on private Boat, at the approval revision. Claims held on srv1 before the credential-free run. Prepared SubsystemNameGetters2.cpp uses the canonical class header and a real getter definition; AIDock.cpp respells its ten existing table references; the constructor unit declares the override and selects State's Snapshot name-slot surface before its other includes.

Baseline and attempted builds both verified **84/84 functions across three sources**, seven data rows, 44 string literals, zero string skips; nine EH label pins recovered through verified parent data. The rename then refused: constructor unit's `??_7AIInternalMoveToState@@6B@` has **15 agreeing slots, one differing** against retail table VA 0x00C10DE8. The tool restored every source and ledger edit; returned diff is empty. No matching-slot provider was admitted.

The default State slot 7 is a separate prerequisite: its inline bare RET differs from retail's byte+0x49 clear at 0x0033F2D7. This is a source/retail observation explaining a candidate for the single clash, not an independently saved rebuilt-object slot diagnostic. Canonical `_bfme_state_slot7` is a placeholder rejected by slot voting. Giving this derived override a real name also requires aligning its shared base slot, through the supported class/header naming route.

Saved on srv1: `~/bfme2-ops/swarm/wt/slotnames/build/boat-run/slotnames-20261115t043829/build/slotnames-ai-trial/{step0.log,step1.log,result.json,prepared0.cpp,prepared1.cpp,prepared2.cpp,changes.diff}`. Sandbox bx_qh35wrbf deleted by boat-run (confirmed True); execution reported 62 seconds. No game or real link was run.

## Scope limits and unchanged blockers

The same-class `--to-class` planner refuses Rva00507823's 0x005075D6 (and same situation at 0x0050774A), and DeployStyleAIUpdate's 0x0048E8F7: these already belong to their destination class. This route intentionally covers placeholder-owner moves, with a narrow same-class Snapshot getter exception. No rejection was bypassed or tool changed.

Folded targets are skipped: Rva00507823 slots 3/4/9 (0x0050B238), 10/11 (0x000D43D0), 12/13 (0x0047A699); DeployStyle slot1 (0x0049A7EE, WorkerAIUpdate/SupplyTruckAIUpdate rows) and 94/95 (0x000D43D0); TurretStateMachine slot3 (0x00306A9B). Different ledger class ownership alone is not proof of original inheritance or semantic identity.

ActiveBody and TurretStateMachine individual class claims were released by the header lane, but acquisition still fails due to its retained `class:TurretAI` footprint (confirmed by claims.conflicts). No edits were attempted there. ActiveBody also retains the documented native/emitted slot order mismatch (LINK-242 and r22 inventory).

Rva00355D66 remains explicitly parked: C14E5C slot1 is existing LoadScreen::update at 0x00355FF9, slot5 is folded 0x0050B5C6. Its six-slot Rva003560EDDtor.cpp adoption is not cleared.

No refused unit is yet re-adoptable on this evidence. Saved per-slot inventory: `~/bfme2-ops/swarm/sweeps/slotnames/slot-status.tsv`. Existing census direct-definition check found all 27 complete distinct packet symbols missing (saved-index evidence only); no current real-link or runtime clearance.


## DeployStyleAIUpdate own getter and idle predicate

At the same approval revision, baseline `DeployStyleAIUpdate.cpp` and `DeployStyleAIUpdateDtor.cpp` verified **32/32 functions**, four string literals and zero skipped string refs. Prepared main TU defines protected const GetSnapshotName (0x0048E8F1) and public const isIdle (0x0048E643). Supported `--to-class DeployStyleAIUpdate --new ?GetSnapshotName@DeployStyleAIUpdate@@MBEPBDXZ --also 0x0048E643=?isIdle@DeployStyleAIUpdate@@UBE_NXZ --approval-base HEAD --prepared ... --no-claim` refused before writing: the destructor's `??_7DeployStyleAIUpdate@@6BDBaseRoot@@@` has no slot 2. Thus no byte-match claim is made for either prepared Deploy body, and no repaired definition or table is claimed. The partial constructor view stores an external table; it cannot replace a matching emitted-table witness.

Saved `build/boat-run/slotnames-20261115t044114/build/slotnames-deploy-trial/{step0.log,step1.log,result.json,prepared.cpp,changes.diff}` on srv1. Diff size zero. Sandbox bx_zwqb4k2h deleted (confirmed True); execution 33 seconds. Both default sandboxes' usage is recorded by boat_swarm in its shared usage.jsonl. No real link or game run was attempted. Folded/missing inherited slots remain; re-adopting the destructor is not cleared by these three name approvals.
