# GameInfo composition prerequisite trial, 2026-11-05

Inspected revision: `1a5cb9ab51`. The current in-memory TU map gives
GameInfo.cpp 164 approved rows; three whole-file donor candidates hold ten
rows. Eight mixed sources remain outside this attempt. The GameNetwork
consolidation planner was reviewed; its committed-map assignments are stale,
so the merge used its freshly rebuilt map and did not write tu_map.csv.

The initial merge dry run accepts no donor:

- GameSlotIsPlayer.cpp repeats the SLOT_* enum from GameInfoSlotView.h.
- GameInfoReset.cpp needs a constructor declaration and a compatible complete
  GameInfo view; the seed's shorter private view cannot define its constructor.
- GameInfoDtor.cpp needs owned member m_C8 and the Version/string teardown
  layout, absent from the seed's shorter view.

A reversible trial moved only SLOT_PLAYER=6 into isPlayer's function scope.
`./build.sh GameSlotIsPlayer.cpp` remains exact for its sole 45-byte row;
string, float, import and declared-unmatched checks pass. The second dry run
then exposes the next independent prerequisite: canonical GameSlot from
GameInfo.h conflicts with GameInfoSlotView.h, and choosing the canonical
GameInfo spelling loses the seed's BfmeNetAddress m_localIP member. Its full
bounded diagnostics are in [enum-local-trial.log](enum-local-trial.log).
The source trial was reverted: fixing just the enum does not permit a merge.
No source, ledger, header, register or file-count change is retained.

Before ending the attempt, ordinary current-object link previews report LINKS
for the unchanged seed (2,869 authored bytes) and the trial donor (45), using
index 112a456a2c / 2026-11-05 15:52. These are preservation diagnostics, not a
new census or real-link result. Declared-unmatched checks pass for all four
original inputs. tu_views dry-run refuses GameInfo as canonical-header lane
work rather than writing a new private view.

Next: reconcile the seed's GameSlot/private-view and GameInfo/BfmeNetAddress
representations against GameInfo.h, including the Version member lifecycle,
then byte-verify those changes independently before retrying composition.
Do not retry the unchanged merge or downgrade the already adopted donor to a
new private class. The existing GameInfo and GameSlot header-queue rows remain.
