# Checkout preparation recovery, 2026-11-04

Recovered preparation backup `refs/runner/preparation/1793755557865579870`
(original tip `27ad66f5dd1351d40f870aaf2ae17399246906c4`). The preparation
record named no stash or resync stash; no staged, unstaged or untracked work
remains unaccounted for. Existing unrelated stashes and the backup ref remain.

The stopped rebase conflicted in AptGC.cpp, AptScalarClearPoolsBFME2.cpp and
header_queue.tsv. Upstream `903bf47bee` already contains the scalar/base header
adoption, collector slot changes, free-list fields and queue retirements.
Comparing the two source stages showed only include placement differences.
Retaining upstream's files and queue preserves that work without restoring
obsolete debt rows. The saved verification notes remain tracked. The rebase
continued through all nine saved commits without aborting or skipping a commit.

The first publication dry run rejected three obstacle ID collisions with
upstream. A new commit assigns this checkout's entries LINK-189, LINK-190 and
LINK-191; their remaining text is unchanged. No published commit was amended.
`/opt/runner/publish --now` subsequently printed `publish: pushed`. The ten
recovered/follow-up commits are upstream through `37aae5e5f3`.

## Checks

- `python3 tools/check_csv.py`: OK, 99,433 function rows, 9,341 symbol rows,
  2,269 data rows.
- `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run`: exit 0,
  PRE-PUSH OK; 111/111 matched functions across nine sources, two verified data
  rows, seven EXACT EH graphs, DIR32 checks passed, no converged-data second
  names or unjudged rows. Pin, gate and EH baselines passed.
- Fresh `./build.sh Code/Libraries/Source/Apt/AptGC.cpp
  Code/Libraries/Source/Apt/AptValue/AptScalarClearPoolsBFME2.cpp`: 4/4 matched,
  three string literals verified; source, float and import checks passed.
- `git diff --check` and conflict-index checks passed.

## Link verification still required

The successful dry-run gate's link batch audit was **INCONCLUSIVE**, not clean:
its index was `8661f15284`, while the outgoing base was `8d5fb2d90184`.
All nine changed source objects lacked accepted current receipts (the first
reported was StateMachineDtor.cpp). It returned before establishing full
selected-provider and consumer-binding clearance. Carry these sources into
the next normally scheduled census; no linked-byte or runtime gain is claimed:

- Common/StateMachineDtor.cpp and StateMachineXfer.cpp
- Common/VslotSmallBodiesAI.cpp and VslotSmallBodiesAI_Rva0057709A.cpp
- Common/W3DAptComponentView3D.cpp
- GameClient/Drawable/Update/RadarMarkerClientUpdateSlot12.cpp
- GameLogic/AI/AerialPathfinder.cpp
- GameLogic/Object/Update/RadarMarkerClientUpdate.cpp
- GameLogic/ScriptEngine/ScriptActionsFireSpecialPowerAtPosition.cpp

All paths above are relative to Code/GameEngine/Source/. The two Apt files
retained from upstream are outside this outgoing nine-source batch.

The source-path audit covered the sole source move, Rva00789900Init.cpp into
Common/W3DAptComponentView3D.cpp. No active old-path consumer remains in tools,
hooks, workflows, source/header includes or the function/TU/debt/header
registers. The surviving TU provenance comment, historical census row and
older attempt notes intentionally retain the old path. The donor has no
protected debt keys; no alias was removed during recovery.
