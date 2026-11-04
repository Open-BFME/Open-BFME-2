# SubtitleWindow TU approval: original shared-code TU still unknown

Inspected `7835790240`; no source or ownership changes.

`tools/tu_skeleton.py --plan Code/GameEngine/Source/Common/SubTitleWindow.cpp`
rebuilds the stale map in memory and reports zero approved rows. The current
map proposes 21 rows, from `0x000453F5` through `0x00045837`, with
`noncontiguous` evidence. The two SubTitleWindow naming hints bracket
`0x00045708`, whose independent Z/S evidence names `WW3D2/render2d.cpp`.

Target facts: the 28-byte scalar deleting destructor at `0x000453F5` calls
the rowed SubTitleWindow destructor `0x00260A3C`. The 22-byte query at
`0x00045837` reads the record-vector span and state documented by the canonical
SubTitleWindow header. Commit `09903a0966` adopted that header in both owners;
their identities are consistent with the current source and ledger.

Structural inference: their `Common/SubTitleWindow.cpp` destination is an N
hint derived from the current source directory and class name. That does not
prove the original TU of these early shared-code bodies. The independently
approved later `GameClient/SubTitleWindow.cpp` constructor/destructor group
does not establish ownership of the early bodies either. The consolidation
planner has no packet approving the Common destination.

Next check: obtain an independent original-TU anchor for the early range, or
prove a particular interleaved row's current identity wrong. Do not rename
correct owners or move rows to the later GameClient TU merely to clear the
noncontiguous verdict. The committed map was not regenerated.
