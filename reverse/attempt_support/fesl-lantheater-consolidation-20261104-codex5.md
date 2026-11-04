# LAN theater consolidation, 2026-11-04

Scope: merge three fragments into
`Code/Libraries/Source/Fesl/gamebrowser/lantheateremulator.cpp` using
`tools/tu_skeleton.py --merge`. Four rows (682 bytes) move; the destination
retains all 15 matched rows (2,702 bytes). Source-file count falls by three.

| Absorbed source | Moved RVA(s) |
| --- | --- |
| `Code/GameEngine/Source/Common/Bfme5EightySeven.cpp` | `0x00674DB0` |
| `Code/GameEngine/Source/GameNetwork/Y4FeslSubTest.cpp` | `0x00675590` |
| `Code/GameEngine/Source/GameNetwork/Rva008097D0LanTheaterRemove.cpp` | `0x006755F0`, `0x006756D0` |

## Placement and provenance

Started with `name_lane.py consolidate --under
Code/Libraries/Source/Fesl/gamebrowser/` and inspected `tu_views.py --dry-run`.
The planner reported a stale committed map. The merge tool rebuilt the map in
memory, found 37 approved rows, and accepted only the seed and these three
donors. Its plan classified the moved rows as C, U, C and F, respectively.
Six other donors failed composition and were left intact; eleven mixed sources
and the unapproved `Y4FeslLanGameCtor.cpp` donor were not absorbed.

The committed map retains older provisional `BfmeThingUNC.cpp` assignments;
`tu_ownership.py --staged --shadow` therefore reports three A2 findings. The
merge uses the rebuilt approvals as supported by `docs/consolidation.md`.
Only the four source columns are repointed in the committed map; no regenerated
map is included. Retail's FESL SDK `__FILE__` string anchors this unit. Its
external build root is not evidence of a BFME 2 repository source directory.
Existing BFME 1 donor comments remain donor evidence.

## Protected records and path audit

Audited the three old paths and basenames across active tooling, hooks,
workflows, includes, configuration, documentation and reverse registers before
publication. No active path consumer requires an update. Remaining references
are destination provenance comments, historical `name_votes.csv` votes,
`link_status.csv` census data and a historical attempt patch; these stay intact.
The merge engine repointed the functions ledger and source columns in the map.

No donor/destination keys occur in the data or code-identity registers or the
header/MS-header queues. The engine refreshed affected queue reports without
changes. Flag-override keys for the three donors were transferred into the
destination's existing record (rows/default_lost 5/5 to 9/9); no debt retirement
is claimed. The existing `??1Gen00809750@@UAE@XZ` alternatename and its hatch key
move unchanged to the destination; the destination's existing alias remains.
No link-wide alias is removed. Unrelated hatch baseline entries are preserved.

## Verification

- `./build.sh Code/Libraries/Source/Fesl/gamebrowser/lantheateremulator.cpp`:
  15/15 exact; source claims OK; 41 string literals verified.
- `find_declared_unmatched.py`: clean before composition for every absorbed
  source and the seed; clean on the destination after composition.
- `check_csv.py`: OK, 99,433 function rows.
- `data_check.py`: one source, zero findings; no second data symbol introduced.
- `eh_verify.py`: zero EH-data rows, no missing object or nonexact result.
- Merge guard: passes against the 2026-11-04 02:25 census at `5a13f2cd61`;
  it checks the composition's providers, consumers and selected COMDATs.
- `link_check.py` on the current destination: LINKS, 2,020 to 2,702 own bytes.
  The increase is transferred donor coverage, not an increase in census LINKED.

The remaining donors require private-view/include reconciliation. Their failed
trials were discarded by the merge engine. No game link or smoke run is claimed.
