# GameLogicDispatch consolidation

The current approved TU plan has 36 rows. The owning merge trial accepted
zero of the two donor files. The rally-point donor remains mixed.

The update donor initially had 18 compiler diagnostics. The dispatcher
now shares Rva0023D2D8DwordClearer.h in place of the identical declaration
in LogicDispatch/owner_context.inc. Its 21 scoped rows and exact exception
graph passed the normal build and commit hook. The retry removed that one
redefinition. The update donor still has 17 diagnostics and could not merge.

The remaining conflicts join the dispatcher's Zero Hour and local include
graph with the donor's canonical Shell, SubsystemInterface and GlobalData
headers. Composition also drops the update donor's declaration carrying
m_94 and m_a8. Preserve their native receiver offsets and the exact +0xAC0
GlobalData accesses when unifying the include graph. The view reconciliation
dry run listed the three files and offered no edits.

The clearGameData donor has 33 diagnostics. The leading failures are
GameMessage and SubsystemInterface definitions, followed by conflicting
GlobalData and dependent types. A general VS macro change would leave these
conflicts in place. Its AudioManager, ControlBar and GameEngine views need
their own canonical reconciliation before merging.

No paths or ledger rows moved. The divergence logs are under
`build/root-resume-20261120/gamelogic-dispatch/` in the isolated r20
worktree.
