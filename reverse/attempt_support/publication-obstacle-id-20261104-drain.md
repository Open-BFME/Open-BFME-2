# BuildingBehavior publication ID collision repair

The fleet publisher refused the outgoing batch because LINK-237 also heads
upstream's RefCountClass/RenderObj entry. After `git pull --rebase origin master`,
the register's maximum ID is LINK-239. Move only the local BuildingBehavior
entry to LINK-240, retaining its blocked status and existing technical evidence.

This follow-up preserves all delivered commits. The old publication notes
remain historical evidence. `python3 tools/check_csv.py` passes (99,442 function
rows); the outgoing hook and runner handover supply publication verification.

## Outgoing verification after the rebase

The first dry-run passed the ID check but refused the identity retirement:
24 participating provider sources lacked current compiler evidence. Normal
`./build.sh` verification of those sources passed 835/835 function rows,
16 data rows, 108 string literals, 17 empty-string references, 78 compiler
literals and seven named imports. No source, debt register or alias was
changed to excuse the refusal.

`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` then exited zero at
`3f31539b0c`, based on `1620af5a9d`. The owning-tool outgoing retirement verdict
passed, as did 50/50 changed function rows, scoped DIR32, all nine EH rows
and converged data checks. This was a dry-run; its "landed" message does not
claim actual publication. The batch link audit remains INCONCLUSIVE because
five since-index sources lack current receipts (first Common/GapBodiesGE31.cpp),
matching the scope already recorded in the Connection consolidation handoff.
No census, full-image link or runtime clearance is claimed.

The final active-tool/include path search across tools, hooks, workflows and
Code for both absorbed donors and the replaced obstacle path found only
historical source comments, consistent with the existing batch path audit.
