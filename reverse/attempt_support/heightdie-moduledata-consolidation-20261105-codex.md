# HeightDieUpdate module-data consolidation

Result: one fewer source file under `Code/`. The approved 44-byte constructor
at `0x0048FC75` now lives in `HeightDieUpdate.cpp`; all nine matched rows are
retained. This moves existing coverage and does not claim a census gain.

Prerequisite `40bad6f3f2` made `HeightDieUpdateModuleDataCtor.cpp` use the shared
partial `HeightDieUpdateView.h` declaration. The explicit vtable pointer and
untouched `+4` word preserve the measured layout; this does not recover the
complete retail class hierarchy. Both affected objects had identical non-debug
runtime graphs before and after that change, including relocations, providers,
weak defaults and COMDAT selection. Both link previews passed (822 bytes total).

`tu_skeleton.py --merge` accepted the receiver and module-data constructor,
repointed the function ledger and the existing TU-map source cell, and removed
the donor. It rebuilt current TU approval in memory; no regenerated map was
committed. Its census-linked guard covered the receiver and both ctor donors.

Verification of the composed receiver:

- `./build.sh`: 9/9 rows exact; string, float and import references pass.
- `eh_verify.py`: both EH-bearing rows EXACT, no baseline or missing objects.
- `find_declared_unmatched.py`: all defined functions matched.
- `check_csv.py`: passes; the destination source is tracked.
- `code_identity_gate.py --staged`: nine rows, zero new findings (shadow).
- `data_check.py`: zero findings; converged check judges 11 addresses with zero
  second names or unjudged rows.
- Object comparison against the pre-change receiver and donor: the union of
  15 code definitions, three external data definitions and two TU-local data
  definitions is unchanged. All 18 external COMDAT bodies (bytes and relocation
  digests), 27 undefined externals and the weak alias are unchanged. No provider
  or consumer binding is removed by composition.
- `link_check.py`: LINKS, receiver 778 -> 822 bytes against census
  `2026-11-05 15:19` / `f44cbcf5b0`. The extra 44 bytes were already linked in
  the removed donor. This is a preview, not a new census measurement.

Debt and path-consumer audit: checked the complete pending range from common
base `ab9158f361` through prerequisite `40bad6f3f2`, plus this staged merge,
after fetching `origin/master` at `10b5d79f48`. The donor deletion is the only
source-path move in that batch. A tracked-tree search for its basename/path
found no active tooling, hook, workflow, include or build/config consumer.
Remaining mentions are the composed source's provenance comment, historical
attempt evidence and the unchanged census snapshot `reverse/link_status.csv`.
The active function ledger and TU-map source cell point to the receiver.
The merge tool refreshed the header and MS-header reports without changes.
The donor has no code-identity, data-check, gate or hatch baseline keys to
transfer or retire. Existing receiver/ctor header debt and the receiver's
pool-key data ownership remain unchanged; no debt retirement is claimed.

Remaining work is unchanged from the earlier consolidation evidence:
`HeightDieUpdateCtor.cpp` needs hierarchy reconciliation (C2511 with the current
receiver view); field-parse and deleting-destructor rows remain in mixed owners
`ModuleDataBuildFieldParse.cpp` and `Common/Rva0024A797Derived.cpp`. No linking
obstacle entry changed in this pass.
