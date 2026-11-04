### LINK-137: console cleanup identity repair changes interface COMDAT selection

Status: Blocked on the DebugIOInterface/DebugIOCon provider cohort.
Updated: 2026-10-29; inspected revision: 29c5ceda1f; index: 840db2d676.
A real-base declaration fixes the constructor unwind binding at 0x0075CEA0
and preserves 4/4 rows plus exact EH, but loses the unit's 476 preview-linked
bytes through interface vtable and scalar-deleting-destructor conflicts.
An inline native-cleanup bridge in both units fails the 85-byte destructor;
the constructor-only bridge keeps 9/9 rows but still loses COMDAT selection.
All trial source and register edits are restored. The identity key remains.
Reconcile native interface slots, the complete provider views and frame
contexts before retrying. No clearance or census gain is claimed.
[Controls, rejected patches and remaining prerequisite](../../reverse/attempt_support/debug-console-identity-20261029-round3.md).

2026-11-04: Moving the existing console frame pragma before _pch.h preserves 6/6 rows and the 958-byte link preview; the merge now rejects only DebugIOCon vtable copies. Next reconcile its native slot-2 predicate/member ABI and seven-slot provider views; identity debt and census clearance remain pending. [Evidence](../../reverse/attempt_support/debug-console-frame-context-20261104-codexb.md).

Naming-review publication (2026-10-29, `b1399e7439`, base `d99d2428cb`):
the two inferred BfmeNodeZK member renames preserve 20/20 owner rows; the push
gate verifies 58/58 rows across three affected sources. The link audit remains
**UNVERIFIED**: provider index `73061d9452` predates that base, and three source
objects lack current receipts (first:
`Code/GameEngine/Source/Common/BfmeOwnerZKRelink.cpp`). Carry this publication's
affected consumer scope into the next normal census. Native byte verification
does not establish current link bindings; no linking gain or clearance is claimed.

Recovery verification of the preserved seventeen-commit batch (2026-10-28,
base `696149099c`, checked tip `6f76860438`): the dry-run push gate passes
229 function rows, three data rows and fifteen EH graphs. Its link audit is
still INCONCLUSIVE against index `41c28839bf`: six affected objects lack current
receipts, first `GameClient/Eva.cpp`. Carry this consumer scope and the saved
FireWeaponUpdate/ScriptEngine moves and declaration/data repairs into the next
scheduled census. No measured linking gain is claimed.
[Recovery, conflict resolutions and complete path audit](../../reverse/attempt_support/preparation-recovery-20261028-codex.md).
