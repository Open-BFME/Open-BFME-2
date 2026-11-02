# Canonical channel-close method name

Base: `03720d5b88` (code inherited from `46da0a1d23`). Model: GPT-6.
Existing row: RVA `0x0060C8CD`, 45 bytes, `Common/Gen009D6DD0.cpp`.
Normal `rename.py function` changes `bfmeClose` to `Close` and rewrites all
eleven referencing source files, recording the canonical basis and tombstone.
No class, layout, signature, source path, pin or hatch changes.

WorldBuilder `0x0165CA40` asserts `XferSave::Close` at xfer_save.cpp:67;
the unique pairing scores 6. The retail body and WorldBuilder body both
test channel +4, conditionally write the four-byte END tag `0x454E44` through
virtual slot +0x10 according to flag +8, then clear channel +4. Debug-only
block-stack diagnostics are absent from retail. This proves the method name;
the receiver remains `Gen009D6DD0` pending separate class reconciliation.

All eleven sources pass the frozen-file check. Normal rename reserves the
scope before editing and finishes its complete verification successfully:

- 1,464/1,464 rows; 19 data rows; 15 emitted constructor folds.
- 420 literals, 61 empty-string references, 99 floats and 229 imports.
- Existing renumbered cleanup labels are resolved through their parent EH data.
- Normal ledger, identity, data, pin and dependency checks pass.

The bounded `link_check.py --paths-from` preview against published index
`984a4cdc4d` (2026-11-02 08:35) reports 11/11 linkable and retains
136,945 -> 136,945 bytes. Unreferenced COMDAT diagnostics remain non-blocking.
This does not establish whole-image consumer selection or census credit.
The publication audit still decides its broader affected scope.

`rename.log`, `preview.log`, `wb.log` and `sources.txt` preserve the scoped
receipts. No new matched bytes or measured linking gain is claimed.

`t=8 model=gpt-6 lane=R budget=30m`

## Post-rebase publication check

Code tip `6d5d88854b70f0b5b19537a2fa35551c14d8dfe6` is based on
`c48f42754c8456af12e73b3f50468f970fbe02fe`. The pull/rebase succeeded and
changed none of the eleven sources. Worktree preparation and CSV checks pass;
`rename.py check` finds one rename and zero problems. Header dependency check
returns 0.

The initial outgoing audit reports ten missing current source receipts.
Supported `link_check.py --prepare-current` explicitly prepares these eleven
reserved providers, verifies all 1,464 rows, 19 data rows and 15 constructor
folds, and writes strict reusable receipts without changing census status.

The renewed audit still returns 2 INCONCLUSIVE: index `984a4cdc4d` predates
the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. That unowned consumer was not rebuilt. Carry the eleven-source
provider/consumer scope into the next scheduled census. This is not a proved
loss or whole-consumer clearance. The obstacle register retains that boundary.

Additional receipts: `strict-current.log`, `batch-audit-before.log`,
`batch-audit-current.log`, `range-check.log` and `header-check.log`.
