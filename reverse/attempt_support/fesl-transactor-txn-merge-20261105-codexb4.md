# FESL transactor TXN consolidation, 2026-11-05

Inspected base: `6e23e07ab6`; declaration prerequisite: `3c9aa707de`.
The approved destination is `Code/Libraries/Source/Fesl/transactor.cpp`.
`tu_skeleton.py --plan` rebuilt the stale map in memory: the TXN handler at
`0x00665C30` is an F anchor in this TU. The planner report under
`build/consolidation/fesl-codexb4` identified the flag override and pragma
context; its unresolved placement hints were not used as approval.

The baseline merge accepted no donor because the private transactor views
omitted one another's members. The prerequisite shares the timeout and TXN
declarations, preserving the reference count at +0x14, watermark at +0x18,
context at +0x20 and hub at +0x24. This uses the two existing source views and
compiler layouts, not a claim about the original class name.

`tu_skeleton.py --merge` then accepted the existing TU and
`Code/GameEngine/Source/GameNetwork/Rva007F96C0Txn.cpp`. It deleted the latter
and repointed its one ledger row. Result: one fewer source file, seven matched
rows retained (489 bytes), no new matched or linked bytes claimed.

Verification:

- Before and after the declaration reconciliation, the scoped build passed
  7/7 rows across the two sources; declared-unmatched passed.
- After merging, the scoped build passed 7/7 rows in the destination, all six
  string references and the import/float checks; declared-unmatched passed.
- `check_csv.py` passed: 99,456 function rows, 9,322 symbols, 2,268 data rows.
- The merge link guard compared the census-linked destination and all three
  candidate donors. No formerly linking unit was lost.
- Current-object `link_check.py` reports the destination LINKS with 489 bytes,
  lookup donor LINKS with 71, and reassembly donor LINKS with 413. Index:
  census 2026-11-05 05:17 at `c95fcfcfcd`. These are previews, not a new census;
  the destination's increase from 256 includes the removed donor's 233 bytes.

Debt and path-consumer audit:

- No data/code-identity baseline, hatch, header queue or Microsoft-header queue
  entry names the absorbed source. No aliases or pins were removed or added.
- The merge transfers its flag override to the destination, summing the two
  existing row/default-loss counts to 2/2. This is a transfer, not retirement.
- `ms_header_audit.py scan --write-queue` refreshed the destination and removed
  path: zero local Microsoft names and no queue change. No header adoption
  acceptance is applicable to either source.
- Searched the absorbed path/basename across tools, hooks, workflows, source,
  docs and reverse registries. Remaining mentions are the historical census's
  `reverse/link_status.csv` and the generated provenance comment in the TU;
  preserve both. Functions, TU source column and flag register point to the
  destination. No data/body-owner or fold-proof entry requires repointing.
- The outgoing range before this merge contains no other source-path move;
  this audit covers the complete pending path-change batch. No hard-coded
  tooling/configuration/include consumer needs updating.

Remaining consolidation prerequisites: the lookup donor still needs its
record array/count view reconciled; reassembly needs the slot/handler/hub
views reconciled. Both remain in their original files and link in the preview.
The TU's pre-existing shadow duplicate-definition findings remain unchanged;
this pass retires no identity debt. A future census must confirm linking.
