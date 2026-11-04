# Fake portal update TU consolidation, 2026-11-04

Base: `37442af86e` (the separately verified receiver-view reconciliation).
Owner: `yasinschroeder-codex`.

`tools/tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/Object/Behavior/FakePathfindPortalBehaviour.cpp`
absorbed `FakePathfindPortalBehaviourUpdate.cpp`, removing one source file.
It moved the existing 118-byte update row at RVA `0x00461DC7`; no new body or
coverage was claimed. Both the dry run and application accepted the seed and
update donor, rejected none, and retained 12 matched rows. The application
reused the verified plan and its census-linked guard for both input units.

## Placement and scope

The refreshed planner snapshot was
`build/consolidation/codex-fakeportal-final`. It classified the seed and update
donor as whole-file candidates. The original-path occurrence at
`worldbuilder.exe:offset=0x01AD7C78` is a World Builder lead, not proof of a
BFME 2 source path. The merge tool rebuilt the stale TU map in memory and
accepted the current approved assignment. Only the existing source column of
the update row was repointed in the committed map; no map regeneration or
approval change is included.

The mixed destructor and common getter donors remain untouched. Canonical AI
and UpdateModule adoption remain separate prerequisites; their existing header
queue entries stay on the seed. The receiver reconciliation preserves the
update interface at +0x10 and the frameless constructor's explicit table stores.
No additional private canonical class was introduced.

## Verification

- `./build.sh` on the final TU: 12/12 functions matched, one data row verified,
  one string literal and one floating literal verified. The existing `$L310`
  funclet was renumbered to `$L5720`; parent EH data still places it at
  `0x0078A994`.
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py`: OK, 99,452 functions, 9,326 symbols, 2,268 data rows.
- `link_check.py` on the final TU: LINKS, 1,050 bytes. Before consolidation the
  current seed and donor both linked, with 932 + 118 = 1,050 bytes. The tool's
  per-file 932 -> 1,050 display reflects the move, not a census gain. Its census
  reference is `3fbce7bcb2`, 2026-11-04 22:01.

## Consolidation and tooling audit

Audited `origin/master` through `37442af86e` plus the staged merge. The only
removed source path is the update donor; its destination directory is unchanged.
The merge tool repointed the function ledger and TU-map source column. The
donor has no gate, data, identity, header or hatch register entries to transfer
or retire. Existing seed data ownership and header debt remain unchanged.

Searched the removed basename/path across tracked tools, hooks, workflows,
source/includes, configuration, registries and documentation. Remaining
references are the merged TU's `from` provenance comment and the published
`reverse/link_status.csv` census snapshot. Historical attempt evidence is
retained. No active consumer needs a path update, and no directory, include
resolution or per-file compiler override changes. The final TU was verified at
its destination path, rather than relying on the deleted donor's receipt.

The merge preserves external callees and class declarations from the verified
reconciliation; both input units were covered by the merge link guard, and the
final current-object link prediction passes. No alias, pin, hatch or protected
debt entry was removed. Clear local/parameter names are retained; unsupported
member roles remain address/offset names. No independent linking obstacle was
introduced or cleared by this source-file reduction.
