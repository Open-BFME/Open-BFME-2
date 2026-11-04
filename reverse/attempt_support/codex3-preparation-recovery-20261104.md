# Preserved batch recovery and publication dependency

Recovered the eleven commits retained at
`refs/runner/preparation/1793814691412889396` (`6c1a7129e7`). The preparation
record names no stash. The first rebase conflict was in the AptPlayer header
queue: upstream had already removed three of the five accepted rows. Keep
those upstream removals and the two remaining removals in this batch.

A later rebase onto newer upstream conflicted at the damage-callback transfer.
Keep upstream's removal of the adjacent CreateObjectDie queue row, and transfer
the DamageFilteredCreateObjectDieDamageSlots Player key to its surviving TU.
No source reconstruction or register retirement was added during recovery.
All eleven commits remain; neither rebase skipped a commit. The conflict index,
tracked working tree and untracked-file inventory were clear after each rebase.
The backup ref remains available.

## Complete-range checks

`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` passed twice. The first
run verified 265/265 function rows across eleven sources, 75 literals plus one
empty-string reference, 20 float literals, four named imports and 24 exact EH
graphs. The second run reused all eleven source receipts and retained 265
verified rows, 24 exact EH graphs, passing DIR32 and converged-data checks.
`check_csv.py` passed after both conflict resolutions. No real-link, census,
runtime or image-ownership result is claimed.

The second hook's link-batch audit remains INCONCLUSIVE: index `2f0cb97f52`
predates base `a1e9318a03`; ten source objects lack current receipts, first
VslotSmallBodiesAJ_Rva00034D00.cpp. Existing attempt evidence retains the
unverified consumer scope. This is not broader link clearance.

The combined old-donor search across active tools, hooks, workflows, source,
doxygen inputs and path-keyed debt/data/owner registers still finds only the
two merge-provenance comments. No active consumer needs repointing.

## Publisher prefix dependency

At 18:05:52 UTC the fleet publisher refused a three-commit prefix of the old
`775612c999` bundle. Its status records three `refusedKeys` and eleven
`pendingKeys`. That prefix creates LINK-243 before the final preserved commit
renames this seat's entry to its reserved LINK-254. The prefix correctly fails
the duplicate-ID check; the complete outgoing range passes
`python3 tools/obstacle_ids.py --range origin/master HEAD`.

Keep the ID repair with the adoption when publishing this recovery. The runner's
documented retry selection tests all pending commits after a follow-up repair
commit; this recovery handoff makes the complete batch a fresh candidate.
No published commit is amended, reworded, squashed or dropped, no LINK ID is
allocated again, and no verifier is changed or bypassed.
