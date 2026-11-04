# FESL LAN theater finder consolidation, 2026-11-04

Inspected tree: `143e6bb861`, on `origin/master` `c47a9a9257`.
`next_work.py --claim` selected the LAN theater TU and its six candidate donors.
The consolidation planner was run for `Code/Libraries/Source/Fesl/gamebrowser/`;
its committed map was stale, so the merge tool rebuilt assignments in memory.
The current plan places RVA `0x00674F10` in `lantheateremulator.cpp` by approved
contiguity (`C`). The committed map received only the moved row's source rekey,
not a regenerated set of assignments.

## Applied scope

`tu_skeleton.py --merge` absorbed
`Code/GameEngine/Source/GameNetwork/Rva00809010Finder.cpp` into
`Code/Libraries/Source/Fesl/gamebrowser/lantheateremulator.cpp`: one fewer source
file, 16 retained matched rows, no new body or recovered identity.
The finder body, symbol, signature and address are unchanged. Its link-wide
`Rva00809010Find` alternatename directive travels with the body; no alias is
retired. The existing flag override is carried to the TU and its row counts
are summed; hatch totals are kept by the merge tool.

The view reconciliation pass applied no changes. Five other clean donors still
fail composition, including missing `Rva00809500Entry` declarations and the
undefined `Rva007E86B0Base` base. Private-view conflicts also remain: incompatible
base clauses, BfmeC994's explicit vptr versus inheritance, `GetterWord` versus
`int`, 4-byte versus 32-byte entry views, and overlapping Gen0080AB50 fields.
Mixed donors and the unapproved LAN-game constructor stay in place. Their next
step is a separately verified declaration/layout repair, not an unchecked merge.

## Verification

- `./build.sh` on the final TU: **16/16 exact**, 42 string literals verified;
  no skipped string references. `find_declared_unmatched.py`: all definitions
  matched. `check_csv.py`: OK, unchanged 99,450 ledger rows.
- `tu_ownership.py --staged`, case-collision check and staged whitespace check:
  pass. Code identity: 16 rows, zero new findings (shadow mode).
- Data identity: zero findings; converged check judges 11 addresses, zero second
  names and zero unjudged rows. EH: no affected row has EH data or lacks an object.
- `link_check.py --fetch-index` fetched the published index dated
  **2026-11-04 20:47**, measured at `f12552d0a7`.
- Current TU preview: LINKS, 2,702 -> 2,761 own bytes. This is the moved 59-byte
  finder joining the existing TU, not a census headline increase.
- Four direct finder consumers also preview LINKS, preserving 1,579 bytes:
  `Rva0080AA80LanTheater.cpp` (212), `Rva0080A3C0FeslDispatcher.cpp` (1,047),
  `Y4FeslEcnlNotify.cpp` (110), `Y4FeslFavGameAddress_notify.cpp` (210).
  `link_check.py --new-variants` on the final TU passes.

## Batch path and register audit

Audited the outgoing range from `c47a9a9257` through `143e6bb861` plus this staged
merge. The earlier pending header-adoption commit contains no source-path move;
the finder absorption is the complete path-change set. Searches for the old
path and basename across tools, hooks, workflows, source/includes, docs and
registers found no active hard-coded path consumer needing repair. The retained
`// from` comment is provenance; `reverse/link_status.csv` is historical census
output and must await its owning measurement. The BFME 1 reference's separate
paths remain donor facts.

Neither donor nor destination has code-identity, data-check, header-queue or
Microsoft-header debt keys. The merge refreshed the destination's header and
Microsoft-header reports with no queue change. Function and TU-map source
columns, flag override and hatch ownership were repointed together. No data row
or fold proof names the deleted source. Existing includes still resolve under
the final TU; ordinary byte and identity checks judge the final object.
Obstacle-register searches for the TU, donors and finder symbols found no entry
whose linking prerequisite changed. This pass finds no new linking obstacle.
No nightly, real-link, boot or game smoke run was started.
