# LANGameInfo destructor consolidation

Base: `99ee6cbacd`; prerequisite: `264804151f`.

`tu_skeleton.py --merge Code/GameEngine/Source/GameNetwork/LANGameInfo.cpp`
absorbs `Code/GameEngine/Source/Common/Rva00447B0EDtor.cpp`: one fewer source
file, four rows moved, 17 matched rows in the resulting TU. This changes no
matched coverage and claims no census improvement.

## Evidence and prerequisites

The committed map is stale; the merge rebuilt assignments in memory. The
destructor at 0x00447B0E and its three EH rows are approved for LANGameInfo.cpp.
The committed map changes only those four source columns, not assignments.
The initial dry run accepted no donor. Removing the explicit LANGameSlot
destructor declaration lets the existing TU emit the implicit destructor,
matching the donor's existing declaration and retail's destructor shape.
The prerequisite passed all 13 existing rows and a clean link preview.

The supported planner surveyed GameNetwork before application. Its
LANGameInfo packet identifies partial routing, compiler-setting and duplicate
type prerequisites; it grants no placement approval. `tu_views.py --dry-run`
reports incompatible LANGameInfo bases and a LANGameSlot field under another
view's base. Remaining donors still require those class/header repairs;
Rva00447B58Assign also conflicts with the seed's private GameInfo layout.
Mixed and unapproved donors were left intact. No linking-obstacle entry names
this target, and the accepted merge introduces no unresolved link obstacle.

## Verification

- [Merge report](merge.txt): 17 rows accepted; the merge's link guard preserves
  all seven previously census-linked scoped units.
- [Byte verification](bytes.txt): 17/17 rows exact, including the moved
  destructor and EH rows; string, float and import checks pass.
- [EH verification](eh.txt): all three parents with EH data are EXACT.
- [Link preview](link.txt): resulting TU links cleanly against the published
  census index (2026-11-03 20:03, 8661f15284). The source's credited bytes move
  from 476 to 550 because it now owns the destructor; this is not a global
  linking gain or a new census.
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py`: OK, 99,431 function rows unchanged.
- `data_check.py`: zero findings; converged enforcement: zero second names
  and zero unjudged rows for the 11 converged addresses.

## Path and debt audit before publication

Audited `origin/master` through the staged merge, including already handed-off
commits `99ee6cbacd` and `264804151f`. The only source removal in that range is
Rva00447B0EDtor.cpp. A combined tracked-path/basename/helper search covered
tools, hooks, workflows, Code, shared shims, reverse registers and docs.
No active tool, include, configuration or directory-derived consumer names
the removed file. Remaining references are provenance comments, historical
attempts, historical naming diagnostics and the last census's link_status row.
The census records remain historical measurements.

The merge repoints all four function rows and map source columns. Its two
header-queue rows (GameSlot and LANPlayer) transfer to LANGameInfo.cpp; debt
is preserved, not retired. There are no donor keys in the data or code-identity
registers, gate baseline, hatch baseline, flag overrides, Microsoft-header
queue, data ledger or STLport trial registry. No aliases or pins change.

## Existing destination keys and commit accounting

The first commit attempt passed pre-commit, then commit-msg refused the two
vanished-source header keys. `_debt_transferred` computes added `(class, source)`
pairs, so it does not recognize a transfer when the destination already had
the same class queued. Both destination classes were queued before this merge;
the tool preserved the transferred rows, including their four source RVAs.
This is recorded as `false-reject repair_queue.py verify-missing` through
`re_log.py`. No verifier is changed here.

The commit uses the documented vanished-source `Debt-Retired` trailer for each
old key to explain its disappearance from the old source. Despite the trailer
name, both classes' destination debt remains in header_queue.tsv; neither is
claimed adopted or retired. No function is tombstoned: all four moved rows
remain matched in LANGameInfo.cpp.
