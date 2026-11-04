# NameKeyGenerator consumer headers, 2026-11-04

Source baseline: `465b7dc3f84ed06b5025e3a7d9cd39d1f0c5e870`.
The header picker claimed `class:NameKeyGenerator` and selected eight consumers.
All eight passed `find_declared_unmatched.py` before editing. The existing
canonical header was used unchanged; no names, target layouts or TU assignments
were inferred or added.

## Accepted subset

| Source | Change | Byte gate |
| --- | --- | --- |
| `Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAIManager.cpp` | Replace its private NameKeyGenerator declaration with the canonical include. | 6/6 rows |
| `Code/GameEngine/Source/GameLogic/System/DelayedExperienceLevelGrantSystem.cpp` | Replace the subsystem shim include with NameKeyGenerator.h before the base is defined, and remove the private NameKeyGenerator declaration. | 15/15 rows |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp` | Put the existing BFME2 ASCII include directory ahead of donor WWLib, and replace the private NameKeyGenerator declaration with the canonical include. | 18/18 rows |

The delayed-experience trial initially collided with the shim's complete
SubsystemInterface definition. Including the canonical header at the old base
include site supplies its existing full-slot base contract and removes that
collision. W3DLaserDraw initially collided with donor StringBase; changing include
precedence selects the existing BFME2 string definition consistently. Its
`BFME_ASCII_DTOR_DECL` contract is retained. These are include/interface changes;
none changes a function body or adds an alias or hatch.

Each final source passed `./build.sh`, including the normal literal/import gates
and parent-EH verification for renumbered funclets. Final frozen-file checks
report all defined functions already matched. Owning
`header_adopt_lane.py accept --class NameKeyGenerator <source>` passed separately
for all three and retired exactly their three rows from `reverse/header_queue.tsv`.

`link_check.py` against the 2026-11-04 20:47 census at `f12552d0a7` reused current
dependency receipts and reports all three LINKS: SkirmishAIManager 515 -> 515 B,
DelayedExperienceLevelGrantSystem 899 -> 899 B, W3DLaserDraw 542 -> 542 B.
The measured preview scope remains 1,956 -> 1,956 B. This is preservation, not
a census or real-link gain. LINK-177's W3DLaserDraw shared-table consolidation
contract remains a separate prerequisite.

Batch audit limit: `link_check.py --prepare-current` byte-verified the same
39/39 rows and produced strict reusable receipts for all three providers,
without changing the census/index/status. The staged-tree `link_batch_audit.py`
against source baseline `465b7dc3f8` remains INCONCLUSIVE: its index is at
`f12552d0a7`, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. No global consumer-clearance claim follows from the three clean
per-file previews. Carry this consumer and these provider changes into the next
census. An earlier comparison to the moving origin/master included unrelated
upstream changes and stopped on missing receipts; the baseline-scoped audit
above isolates this repair. No extra unowned sources were compiled.

## Remaining selected consumers

The automatic adoption trial restored each failed file; no attempted body is
left in Code. These are trial diagnostics, not demonstrated game-link failures.

| Source (basename) | Diagnostic / next useful check |
| --- | --- |
| `AiOrdersManager.cpp` | C2039: canonical NameKeyGenerator has no KeyToBucketMap. Reconcile the source's container references with the canonical header's deliberately opaque reverse-index storage; do not invent a container identity. |
| `ExperienceLevelSystem.cpp` | C2039: ExperienceLevelStore has no m_reloadLevelLists. Reconcile that existing class/member declaration before repeating this adoption. |
| `GameLogicInit.cpp` | Field-renaming preflight cannot map SubsystemInterface::m_04 (+4, four bytes) to a canonical field of the same extent. Reconcile the base view before another broad include attempt. |
| `StagingRoomGameInfo.cpp` | Layout preflight compile failed C1083. The short adopter diagnostic does not identify the missing include; capture the complete layout compile diagnostic before choosing a source edit. |
| `MilesAudioManager.cpp` | The adopter reports AudioEventsReloaded does not compile; its stored diagnostic is truncated. Capture the complete diagnostic before assigning a cause or retrying. |

The five header debt rows remain. No workaround, header edit or retirement was
made for them. The opaque-buffer TU evidence is a separate handoff in
`opaquerefbuffer-tu-approval-20261104-codexb.md`.
