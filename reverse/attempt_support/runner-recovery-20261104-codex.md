# Preserved checkout recovery, 2026-11-04

Recovered the twelve commits retained by
`refs/runner/preparation/1793803088533713008` (original tip `60b877f684`)
onto preparation upstream `11c8ab6c1e`. The only stopped conflict was in
`reverse/ms_header_queue.tsv`: retain upstream's AptActionInterpreter entry
and this batch's refreshed W3DShroud entry. The rebase completed without
skipping any commit. The preparation record names no stash or resync stash;
there were no untracked or uncommitted edits after the rebase. Other retained
stashes and the backup ref remain untouched.

The first push dry-run refused BuildingBehavior's identity retirement because
four participating provider objects were stale. Normal `./build.sh` verification
of W3DLaserDraw.cpp, BuildingBehavior.cpp, ScriptDtor.cpp and
ScriptWriteDataChunk.cpp passed all 60 rows, 25 funclet pins, 11 string literals
and one compiler literal. No source or register was changed to excuse this
refusal. `python3 tools/check_csv.py` passes (99,442 function rows), and
`python3 -m unittest discover -s tools/tests -p test_tu_skeleton.py` passes
all 181 tests.

`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` then passed at
`50c8793c67` against `11c8ab6c1e`: owning-tool debt checks, 50 row/30 witness
scoped DIR32 checks, nine exact EH rows and converged data checks passed.
The link audit remains INCONCLUSIVE at its existing five-object receipt
boundary (first GapBodiesGE31.cpp), already recorded in the Connection audit.
No census, image link or runtime clearance is claimed.

Rechecked active tools, hooks, workflows and Code for both absorbed donor
basenames and the obsolete LINK-231 BuildingBehavior entry path. Only
historical source comments remain. The current BuildingBehavior entry is
LINK-240; `obstacle_ids.py --range origin/master HEAD` passes.

The first runner publication returned its saved refusal for the original
candidate: an old LINK-231 collision, with status tip `60b877f684` and
refused base `8fa9fab472`. Current checks already pass the renamed entry.
This recovery receipt records the reconciled state and supplies a new
candidate without rewriting any previously handed-over commit. Publication
is retried through the runner; its final result is reported separately.
