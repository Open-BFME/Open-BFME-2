# AptMpClans unwind owner repair

Inspected base: `996e138889`. Claim: `0x0079C65F` and the destination file.

`check_csv.py` found the eight-byte `$L1457` row at `0x0079C65F` pointing
to the deleted `AptMpClansRva0057FA1C.cpp`. Merge `bd20921ccb` moved its
parent, handler and sibling cleanup to `AptMpClans.cpp`. The later-rebased
funclet cohort `5eb461cefd` retained this row's old source. This is a stale
owner reference, not an uncovered body or a new conversion.

The parent is `?rva0057FA1C@AptMpClans@@QAEXVUnicodeString@@@Z`, retail
`0x0057FA1C`, 148 bytes. A TU map rebuilt in memory from the current inputs
approves that parent in
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMpClans.cpp`.
The shared-FuncInfo cleanup has no independent TU-map assignment; its exact
parent graph supplies the ownership proof. The existing handler row selects
this parent among the shared retail frames, as the original cohort documented.
No map or source file is changed.

The current object's parent EH graph is EXACT. `verified_funclet_locations`
binds `$L60380` to `0x0079C65F` and `$L60381` to sibling `0x0079C667`.
Only the existing row's source field is corrected, preserving its logical
compiler label, extent and parent notes. The byte gate resolves renumbered
labels through the verified EH graph.

Checks:

- Normal build: 28/28 function rows, 12 string literals and one named import.
- EH verifier: six graphs EXACT, no baseline findings or missing objects.
- Declared-unmatched check: all defined functions already matched.
- `link_check.py --prepare-current`: strict reusable receipt for the destination.
- Ordinary link preview: destination absent from census index `d92e7e6635`;
  no current linking verdict or census gain is claimed.
- Staged-tree link batch audit: INCONCLUSIVE. The index predates the base,
  and affected consumer `Common/AIHarvestPrepareSiteState.cpp` lacks a
  current receipt. Carry the repaired owner and affected consumers into the
  next scheduled census; external consumer coverage remains unverified.

Source text, external symbols, pins, registers and emitted objects are unchanged.
The existing sibling cleanup and handler already use the destination. No
active tools, hooks or configuration need a path update for this row-only repair;
the deleted donor's provenance comments and historical evidence remain intact.
The moved cleanup and its parent should be included in the next normal census.

Initial global CSV validation also found the independent `0x0079F984`
AptOnlineHome owner reference. Another worker holds that address; it is outside
this repair's scope. The attempted normal commit is refused by the global
CSV hook on that remaining reference. No hook was bypassed and no commit was
created. Keep this verified repair staged until the independent owner repair
lands, then rerun CSV validation and the normal commit/publication command.
The hook also reports two shadow-only STL list-helper identity divergences;
the source and object are unchanged by this owner-reference correction.


## Preparation recovery

The recovery rebase onto `49d65e3bea` retained all 22 checkout commits.
Conflicts were independent additions to the shared linking register and
header queue; both additions were retained. No commit was skipped.

Applying saved stash `858fb3cc52c8a87350072bae5e06d5a3e5dda06f` with
`--index` refused changed context without restoring edits. A normal stash
apply then restored this handoff and the linking-register addition; their
independent register additions were reconciled. The saved ledger edit is
already present upstream in `db7cbb506c` (Repair funclet owners after Apt
consolidations), along with the independent `0x0079F984` repair. It is not
reintroduced. Current `check_csv.py` passes all 98,945 rows; the AptMpClans
frozen-file check also passes. The stash has no untracked payload, and the
checkout has no untracked files. The retained stash and backup ref
`refs/runner/preparation/1793214701576350271` remain available.

The complete outgoing source-path audit was repeated after recovery across
`49d65e3bea..8e9f0c8cb8`: six absorbed files, five destination TUs, no directory
moves. Combined full-path and basename searches, including tracked queues,
JSON configuration, tools, hooks, workflows, includes and build configuration,
find only provenance comments, historical census/log/handoff rows, append-only
naming evidence and TU-map naming evidence. No active path consumer needs an
update. Existing composition handoffs retain the provider/consumer and register
checks; the normal push gate must verify the recovered outgoing range before
publication. The first dry-run refused the restored, uncommitted documentation;
this evidence is committed before retrying. No gate is bypassed.
