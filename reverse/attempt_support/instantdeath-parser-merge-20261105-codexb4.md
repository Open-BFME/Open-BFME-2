# InstantDeathBehavior parser merge refusal, 2026-11-05

Inspected base `7a2219e8cf`; prerequisite `b68a6b7959` was handed to the fleet
publisher. No merge or source-file reduction is published by this attempt.
The prerequisite's vector views and admitted constructor fold remain in place;
see [their evidence](instantdeath-parser-vectors-20261105-codexb4.md).

## Composition and refusal

The supported `tu_skeleton.py --merge` rebuilds the stale map in memory and
accepts the seed plus `InstantDeathBehaviorParsers.cpp` and
`InstantDeathBehaviorParsers_Rva0045D2F6Parse.cpp`. It writes 19 rows to the
seed, deletes two donors, repoints 11 ledger sources/fold proofs and seven
existing TU-map source cells. It does not regenerate the committed map.

The written candidate passes `./build.sh` 19/19; all three parent EH graphs
are EXACT, including all three renumbered funclets. The staged code-identity
check reports zero new findings, and normal/converged data checks report
zero findings across 11 converged addresses. The merged link preview LINKS
787 accounted bytes against census `2026-11-05 05:17`, revision `c95fcfcfcd`.
These comprise the three sources' previous 758 bytes plus the already-covered
29-byte constructor fold; they are not a census linking gain.

`tu_ownership.py --staged` then exits 1:

```text
A2 0x002DFCF6
?_M_insert_overflow@?$vector@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@@IAEXPAPBVObjectCreationList@@ABQBV3@ABU__true_type@2@I_N@Z
moved to InstantDeathBehavior.cpp; approved TU is
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildingTemplate.cpp (C)
```

This row already existed in the parser donor as a verified 140-byte compiler-
emitted ICF twin with `fold-proof` pointing to that donor. The composed copy
continues to byte-verify; it is not a new body or unique coverage claim. A2
uses the shared address's TU assignment without judging that fold proof.
Recorded as `false-reject tu_ownership A2` for tooling review. No gate, map
approval, alias note or admission rule was changed to bypass the refusal.
The entire five-path merge was restored to `b68a6b7959`, including both
deleted sources, ledger and map.

## Consolidation audit boundary

- No seed/donor keys existed in the gate, code-identity or data-check debt
  baselines. The seed's owned field table and pool-key/guard data entries stayed
  at their existing source. There was no debt retirement.
- The merge's owning tool refreshed header and Microsoft-header queues with
  no changes. The two OnDie header-queue entries remain untouched.
- The batch path search found no active tool, hook, workflow or source include
  requiring either deleted parser path. Remaining references were origin
  comments, INISoundRefList's historical evidence comment, a historical proposal
  patch, the measured link-status snapshot, and historical attempt logs.
- The explicit batch provider audit exited 2, INCONCLUSIVE: working-tree
  compiler/identity inputs differ from the proposed tree. Two pre-existing AI
  source edits were deliberately preserved outside this work. Thus the
  whole-batch provider audit is not clearance; retain this scope for the next
  census/current-input audit after a permitted merge.
- The merge link guard preserved the five census-linked units in its scoped
  candidate checks. This and the link preview do not replace a real link or
  a census receipt. No nightly, smoke, link cycle or real-link run was started.

## Next work

Review the ownership gate's treatment of an already-proven compiler-emitted
ICF twin before retrying this exact merge. Do not hand-add `gen-alias`, change
the TU map, or suppress the helper merely to pass A2. The recorded false reject
should be reproduced and any verifier fix independently tested and published
before the source move.

Separately, OnDie still needs the module-data FX view and canonical
AIUpdateInterface / Rva0036CA00Str adoptions; the module-data destructor still
differs in composition. Neither rejected source was edited.
