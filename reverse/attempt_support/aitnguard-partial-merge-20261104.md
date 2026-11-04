# AITNGuard partial TU merge — 2026-11-04

Allocated consolidation shard 0/5; `consolidation_queue.py --check-tu` returned
success for `Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`. After pulling
`a158dd8947`, the AI-scoped consolidation snapshot was regenerated and passed
`name_lane.py consolidate --check build/consolidation`.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`
accepted the seed plus three unchanged donors: `AITNGuardInnerStateCtor.cpp`,
`Rva00545D7ECtor.cpp`, and `AITNGuardAttackAggressorStateCtor.cpp`. It merged 12
approved rows, repointed three function/map rows and four header-queue rows,
and transferred hatch keys with totals kept. The normal commit hook then
refused the trial: `AITNGuard.cpp: declares its own
AITNGuardInnerState; include Code/GameEngine/Include/GameLogic/AITNGuard.h
instead (or // class-gate: allow ... for a proved codegen view)`; the private
class gate rejected it. This seat cannot make that source/header repair. The
source and ledger trial was restored, so no files were removed and no merge
commit was made. Complete accepted-file/RVA claims were released.

Before the hook refusal, verification showed: the merge LinkGuard checked the
census-linked seed and donors;
`./build.sh Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp` passed all 12/12
matched rows and three renumbered EH funclets; `find_declared_unmatched.py`
reported no unmatched definitions; `code_identity_gate.py --staged` reported
four shadow unreferenced-alternatename findings (not retired); `data_check.py
--staged` reported zero findings. The active-path search across tools, hooks,
workflows, source, docs, header queues and doxygen inputs found no consumer of
the three removed paths; remaining matches are provenance comments. The
pre-push `link_batch_audit.py` is still required to compare changed providers,
selected COMDATs and consumers for the complete outgoing batch.

Other unchanged rejects left in place: `AITNGuardXfer.cpp` needs the machine xfer
member declaration; `AITNGuardStates.cpp` and `AITNGuardReturnStateOnEnter.cpp`
fail at an unavailable `TheAI` type; `AITNGuardMachineCtor.cpp` needs the
constructor declaration. No identity debt, link gain or census change is
claimed. Next step for those donors is class/view reconciliation by another
lane, then a fresh allocated trial only after that prerequisite changes.
