# AIStatBase consolidation, 2026-11-03

Source reconciliation: `a1f269d317`; batch base inspected: `a370ffa932`.
The earlier AIGameTeam helper reconciliation is `f70d3a2b26`.

## Applied scope and evidence

`tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/AIStatBase.cpp`
accepted AIStatBase.cpp and Rva005961D6Dtor.cpp, with no rejected donors.
It merged two files into one and retained all 11 matched rows. The current
in-memory TU map approved the destination (provisional grouping; the path is
not newly established as retail's original filename). Rva0025BFE3Derived.cpp
and Rva00596095Bits.cpp remain mixed donors and were not moved.

The prerequisite reconciliation uses the existing vector layout at +0x98
instead of a separate buffer-owner view. `/EHs /EHc-` preserves retail's
cleanup around `free`; `/EHsc` incorrectly removes that frame. This is target
byte/EH evidence, not proof of the element's semantic identity. Existing
address-derived class names and BfmeE16 spelling remain unchanged.

The merge changes only three source fields in each of functions.csv and
tu_map.csv: destructor 0x00596225, unwind funclet 0x0079D2CD and handler
0x0079D2D5. No map regeneration, new code row, pin, alias or hatch is included.

## Verification

- `./build.sh Code/GameEngine/Source/Common/AIStatBase.cpp`: 11/11 exact;
  string, float and import-reference checks pass. Both renamed compiler
  funclet labels resolve through their parents' exact EH data.
- `eh_verify.py`: EXACT 2, no missing object or nonexact graph.
- `find_declared_unmatched.py`: all definitions matched except the existing
  explicitly absent-from-retail anchor; exit 0.
- `check_csv.py`: OK, 99,431 functions, 9,343 symbols and 2,269 data rows.
- `tu_ownership.py --staged`: exit 0, no findings.
- `data_check.py`: zero shadow findings; converged enforcement checks 11
  addresses with zero second names or unjudged rows.
- The reconciliation hook already reported the existing duplicate-definition
  shadow finding for `?rva005962E7@Rva005962E7@@QAEXXZ`; this merge does not
  add or change that wrapper, or claim identity-debt retirement.
- The earlier AIGameTeam cohort was rechecked: 16/16 rows exact across its
  seed and destructor fragment. Its actual merge wrote nothing because
  0x0007FAB3 was held by another worker; its file scope was released.

## Path and register audit

Audited the complete local outgoing batch plus this staged merge. The only
removed source is Common/Rva005961D6Dtor.cpp, absorbed into AIStatBase.cpp.
Searches for its path/basename across tools, hooks, workflows, Code, docs and
reverse found no active hard-coded consumer requiring repair. Remaining
mentions are the TU's provenance comment, the preserved anchor's name/marker,
and the historical link_status.csv census row. They are intentional.

No source-keyed entries occur for these two files in the identity, data,
hatch, flag-override, header or MS-header queues, or data ledger/rows.
The existing body_owners.csv wrapper owner and doxygen AIStatBase input already
name the destination. No protected keys need transfer or retirement.
Relative includes retain their resolution; no shared header is edited.
Only source-column repoints are carried in tu_map.csv.

## Linking qualification and next check

Index: census 2026-11-03 20:03 at `8661f15284`.
Ordinary two-source preview before merging: AIStatBase LINKS 466 bytes and
destructor fragment LINKS 67 bytes. After merging: AIStatBase LINKS 533 bytes.
These are the same authored bytes, not new linking coverage.

The whole-batch staged-tree audit exits 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 8661f15284, outgoing base origin/master; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 3 source object(s) lack current receipts; first: Code/GameEngine/Source/Common/AIGameTeam.cpp
```

Normal byte/dependency receipts do not establish strict include-inventory
currency. Full-image provider selection and preservation of affected consumers
remain unverified. Carry AIStatBase, retired Rva005961D6Dtor, AIGameTeam and
SkirmishAITeamOwnedDtor, plus their indexed consumers, into the next scheduled
census/current-receipt audit. The publisher must also recheck incoming changes
after rebasing. No census, ownership or unique matched-byte gain is claimed;
the source-file reduction is one.
