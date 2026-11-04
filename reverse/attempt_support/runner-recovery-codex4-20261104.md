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
