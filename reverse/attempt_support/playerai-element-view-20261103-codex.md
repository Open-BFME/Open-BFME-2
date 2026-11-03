# PlayerAI copy-element view reconciliation, 2026-11-03

Inspected source base: `0862a0d89c`; verified declaration repair:
`eca76cef5b`. Scope: `Code/GameEngine/Source/GameLogic/System/PlayerAITypeSet.cpp`
and `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00215696AssignTwin.cpp`.

The default picker served consolidation of PlayerAITypeSet.cpp. The supported
consolidation planner was run under `Code/GameEngine/Source/GameLogic/System/`;
it flagged macro/pragma context, include resolution, internal linkage, the
existing hatch register and an unledgered definition in the destination.
The TU map is stale; the merge tool rebuilt its approval map in memory. No map
was committed or assignment asserted by hand.

The first guarded merge dry run rejected all four candidate donors. For the
assignment donor, compilation failed because the destination's private
`Rva00215696Element` view exposed only `char bytes[16]`, whereas the assignment
body accesses `text` and `names`. The existing provider represents these as
`AsciiString` and `vector<AsciiString>`. Its row is the 33-byte assignment at
0x00215530; the destination owns the 47-byte copy loop at 0x00215696. These
existing reconstructed spellings are retained; no original class/member name
or donor source path is claimed.

The repair gives the caller the provider's two members, retaining its method
declarations. The view follows the declaration-only vector specializations:
placing its inline destructor earlier instantiated the vector destructor before
the specialization and failed C2908. That failed ordering was corrected before
the successful build and commit.

Verification of the repair:

- `./build.sh Code/GameEngine/Source/GameLogic/System/PlayerAITypeSet.cpp`:
  15/15 function rows and the one data row pass, including all three EH graphs
  in the commit hook.
- `find_declared_unmatched.py` passes. Its note about one existing unclaimed
  definition is unchanged; the existing present-unmatched marker is retained.
- Paired `link_check.py` against census 2026-11-03 20:03, revision
  `8661f15284`: destination LINKS 591 -> 591 bytes, assignment donor LINKS
  33 -> 33 bytes. This is a preview, not a new census measurement.
- Commit hooks pass with zero new code-identity and data findings. No pin,
  alias, hatch, ledger row or source path changed.

The subsequent `tu_skeleton.py --merge ... --dry-run` accepts the destination
and assignment donor together, preserving all 16 function rows and passing the
census-linked merge guard. The parser remains a compile rejection over its
private views; the allocation/copy and fill-insert donors remain byte
rejections. The mixed StringVectorRecordCopyBFME2.cpp and
StlportMapForwardersSeat8.cpp sources stay outside this merge.

Application wrote nothing: the tool could not acquire 0x0007FAB3 in its complete
candidate scope. At the application check the claim belonged to
`codex-01a1071d-root-recovery-oct11` for RespawnUpdate.cpp, with about 3.6 hours
remaining. The successful dry run is not a landed file reduction.

Next: after that claim is released, refresh the consolidation planner, rerun
the guarded dry run and apply through `tu_skeleton.py`. Then verify the merged
source, audit path consumers and publish before attempting further donor view
reconciliation. No linkage obstacle entry changed: the existing LINK-002
record-family repairs are retained and this blocker is claim contention.
