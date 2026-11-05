# GameWindow draw-data consolidation, 2026-11-05

Scope: `GameWindowFields.cpp` into the approved retail TU
`Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp`. Prerequisite
`a1f3f4ecdf` adopts canonical GameWindow in the donor and retires its one
GameWindow header-queue row through `header_adopt_lane.py accept`.

Target evidence: the twelve existing ledger bodies prove the instance-ID store
at GameWindow +0x34, three nine-element draw-data arrays at WinInstanceData
+0x18/+0x84/+0xF0, and the edit-data pointer at GameWindow +0x214. Field names
already used by the matched donor were retained; these offsets and byte checks
do not establish an external donor path as a BFME 2 source path. The canonical
WinInstanceData size remains 0x1A8. No new recovered function or name is claimed.

`name_lane.py consolidate --under Code/GameEngine/Source/GameClient/GUI/`
was refreshed at a1f3f4ecdf; its original-path alternatives and mixed-source
blockers were reviewed. `tu_skeleton.py --merge ... --dry-run`, then `--merge`,
rebuilt current TU assignments in memory and accepted the seed and Fields.
The committed TU map changes only twelve source-path cells. Twelve function
rows move, one source file disappears, and all existing coverage is retained.
The merge planner reports 88 approved rows; the build verifies 89 ledger rows,
including the seed's existing coverage outside that approved-plan count.

Checks:

- Prerequisite: Fields 12/12 exact; shared-header commit hook checked all 245
  dependent sources (2,617 + 1,401 code rows), with no failed byte/data checks.
- Merged TU: `./build.sh .../GameWindow.cpp` 89/89 exact, including six
  renumbered funclet labels checked through parent EH data; strings, floats
  and import references pass. `eh_verify.py` reports three EXACT, zero failures.
- `find_declared_unmatched.py` passes before and after; its existing inline
  declaration note remains. `check_csv.py` and `git diff --cached --check` pass.
- Staged TU ownership shadow check passes; code identity checks 89 rows with
  zero new findings. Data check has zero findings; converged check covers
  eleven addresses, zero second names and zero unjudged references.
- Ordinary link previews against census 2026-11-05 05:17 (c95fcfcfcd): before,
  seed 3,214 and Fields 356 bytes both LINKS; after, seed 3,570 bytes LINKS.
  The two rejected donors remain LINKS at 190 and 248 bytes. This preserves
  prospective coverage; it is not a new census or real-link measurement.
- The merger's provider/consumer and selected-COMDAT link guard passes.
  Existing linker aliases remain; no link-wide alias is removed.

Debt and queue audit: Fields has no data/identity debt keys to retire.
Its header row was accepted in the prerequisite, not deleted by the merge.
The merger refreshes destination header/MS-header queues; existing seed
GameWindowManager/View prerequisites remain. One counted historical
present-unmatched comment token transfers through `hatch_counters --update`
from Fields to the seed, total unchanged. No debt retirement is claimed for it.

Tooling compatibility audit covers origin/master through a1f3f4ecdf plus this
staged merge: the only removed path is Fields. Searches of tools, hooks,
workflows, source/header includes, build/configuration files, documentation,
and active path registers find no active old-path consumer requiring changes.
Functions and TU-map owners are repointed by the merger; header/MS-header,
data, identity, hatch and body-owner registers have no stale Fields key.
Remaining old-path mentions are provenance/caller comments in GameWindow and
GadgetButtonImageHelpers, the frozen GameWindow class contract's original
layout/header-widening evidence, historical attempt evidence, and the census
link-status snapshot. They retain their historical meaning. Header adoption
gets current source candidates from its live census, not those frozen evidence
paths. No directory is removed and directory-derived source discovery remains
valid. Generated merge/compiler receipts were refreshed for the final TU.

Remaining merge prerequisites (unchanged donors, not linking regressions):
`GameWindowWinSetInstanceData_Rva0031495c.cpp` needs its UnicodeString include
and Coord3D collision reconciled, and canonical WinInstanceData text fields;
`GameWindow_winSetText.cpp` needs its canonical GameWindow method declarations
and UnicodeString ABI reconciled. The merge refuses both at compilation.
Other mixed-source candidates require separate approved splits/adoptions.

Publication accounting: the outgoing bundle's net header-debt check sees Fields
already absent after the merge, so it cannot rerun acceptance on the old path.
The prerequisite's owning-lane acceptance and full dependent-source verification
precede that deletion; all twelve rows now verify in the approved TU. A follow-up
per-key `Debt-Retired: GameWindow <old source> ...` trailer records this vanished
source case, as allowed by the debt rules. No ledger row is deleted or tombstoned.
