# Player initializer CRT declaration cleanup boundary

Base: `89295774ff`. Scope:
`Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp`, especially
`Player::initFromDict` at RVA `0x002AFCDF`, retail size 2,762 bytes.

The Microsoft-header auditor classifies the local `free` and `memset`
prototypes as identical to `stdlib.h` and `string.h`. That static comparison
does not establish that deleting the redundant declarations preserves this
compiler's output.

Trials, with the existing compiler flags and no ledger changes:

1. Add `stdlib.h` and `string.h` after `hash_map`; delete both local prototypes.
   The initializer's COMDAT grows from 2,762 to 2,764 bytes. The other 51 of
   52 COMDAT byte-and-relocation digests and sizes remain identical, as do
   the exclusive, undefined and weak external sets. The byte gate also
   cannot distinguish allocation-cleanup funclets `$L10513` and `$L10512`
   for the row currently named `$L10490`.
2. Delete both prototypes without adding includes. The byte gate and the
   same ambiguous-funclet check fail.
3. Delete only `memset`. The byte gate fails, and `$L10515` / `$L10514`
   are ambiguous for that funclet row.
4. Delete only `free`. The byte gate fails, and `$L10517` / `$L10516`
   are ambiguous for that funclet row.

The latter three trials used `BFME_OBJSTORE=off ./build.sh` to distinguish
compiler sensitivity from an object-store artifact. Their emitted section
sizes were not separately saved. The follow-up log entry qualifies the
initial entry's overly broad size statement. These failures do not prove a
cache defect or a wrong CRT ABI.

All source edits were reverted. The original source again verifies 31/31
rows, its data row, six nonempty string references and one empty-string
reference. `eh_verify.py` reports four EXACT EH graphs, with zero baseline
exceptions. The Microsoft-header queue entry remains unchanged. No row,
funclet binding, hatch, compiler flag or shared header was changed.

A future attempt needs a concrete explanation for this initializer's
compiler-shape sensitivity; repeating a plain include replacement or deletion
has already been tested. No nonmatching reconstruction remains in `Code/`.
