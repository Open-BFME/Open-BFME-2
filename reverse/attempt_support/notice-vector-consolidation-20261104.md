# Notice vector consolidation prerequisite

Inspected `dc72351a4a`; prerequisite published as `34278a141e`.

`tu_skeleton --merge Code/GameEngine/Source/Common/Bfme/IngameNoticeDisplay.cpp
--dry-run` originally rejected `Rva004E5A78Method.cpp` with C2995: both
fragments specialize `vector<void *>::begin/end`, with different template
spellings. The existing class views already agree (`tu_views`).

The prerequisite shares the four existing inline accessors in the local
`IngameNoticeDisplayVector.h`, included before use. No class, function, global,
pin or alias identity changes. `./build.sh` verifies all 26 rows across both
sources, `find_declared_unmatched` passes, EH verifies all three parents EXACT,
and the commit hook reports zero code/data identity findings. Strict reusable
provider receipts were prepared for both sources. The dry run then accepts
both fragments and preserves its census-linked guard scope.

Applying the merge writes nothing: it cannot claim the shared ICF row
`0x0007FAB3`, held by `yasinschroeder-claudeb` as verified pending publication.
Do not override that claim. Retry the ordinary merge after it settles; it can
remove one source and transfer the destructor, handler, unwind action and
folded vector destructor row. No source-count or census gain is claimed here.

The planner's alternate Water.cpp route is an unapproved donor hint, not
placement proof. The merge uses the current TU map rebuilt in memory. The
mixed constructor and GUI files stay outside this merge. Existing aliases and
all protected debt remain intact.
