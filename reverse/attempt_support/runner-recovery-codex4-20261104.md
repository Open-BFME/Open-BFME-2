# Preserved batch recovery, 2026-11-04

The preparation record names backup `refs/runner/preparation/1793797051180540653`
(original tip `631368c5d2`) and no stash or resyncStash. Its six commits are
preserved as `ed72a58fd2` through `4b298c9854` on `127419f3a4`;
the index and working tree were clean, with no active rebase or untracked files.
The only tree differences between backup and restored tip are upstream changes
to `tools/image_report.py` and `tools/tests/test_image_report.py`; no saved
checkout edits need reapplying. The backup and all older stashes are retained.

The first recovery dry run confirmed the recorded obstacle-ID refusal:
LINK-232 now also names upstream's IME entry, and LINK-233 now also names
upstream's Vector3 entry. Preserve those upstream IDs and assign this batch's
ClickReactionBehavior entry LINK-234 and VertexMaterialClass entry LINK-235.
Only their headings and filenames change, plus the material evidence's ID
reference. Repository searches found no consumers of the former filenames.
The bodies, pending scope and original evidence of both entries are preserved.

No game sources or debt registers are changed by this recovery fix. The full
outgoing hook is checked with `BFME_PUSH_SPACING_S=0 python3 tools/push.py
--dry-run` before `/opt/runner/publish --now`; runner finish records its result.
Local transient logs are `build/runner-recovery-dry-run.log` (initial refusal)
and `build/runner-recovery-final-dry-run.log` (repaired batch).

The successful dry run rebased onto `d67c09ebed`: 97/97 rows across seven
sources, 17 exact EH checks, and PRE-PUSH OK. Its link audit is INCONCLUSIVE:
the index is at `a62ac1c10b` and six sources lack current receipts. This is
unverified linking, not a clearance or a census gain.

The rebase preserved upstream BuddyDefs.cpp and PeerThreadPushStatsBfme.cpp
adoptions (589ee6aa39 and d3c623e79e); RequestBuddyAddRva004178C1.cpp was also
already adopted upstream (d3c623e79e). The saved GameSpy commit retains only
StagingRoomGameInfo.cpp and stlport_list_00416a5d_bounded.cpp plus its evidence.

After the seven-commit handover, upstream `9e671822ba` took LINK-234 and
LINK-235 for the vector-copy and Horde entries. A new follow-up commit leaves
the handed-over commits intact and assigns ClickReactionBehavior LINK-236 and
VertexMaterialClass LINK-237, updating the same material evidence reference.
Repository searches again find no consumers of the two former filenames.
