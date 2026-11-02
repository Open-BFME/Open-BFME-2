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
