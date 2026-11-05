# CreateAHero accessor memset binding

Inspected revision: `f319f63d21` (2026-11-05).

## Target facts and repair

`reverse/exit_link_blockers.tsv` names
`Code/GameEngine/Source/Common/Rva00219B9EAccessor.cpp` with unresolved
`?ji_006291ae@@YAPAXPAXHI@Z`. The original object references that name and
contains an alias to `?ji_006291ae@@YAXXZ`; neither functions.csv nor
symbols.csv supplies the alias target. The typed legacy spelling is only a
symbol pin. The actual six-byte import thunk is now rowed as `_memset` at
RVA `0x006291AE` in `Code/Libraries/Source/CRT/Msvcr71ImportThunks.cpp`.
The thunk reads the real `__imp__memset` import pointer (retail IAT VA
`0x00BBA6C0`).

Include `<string.h>` and call `memset` at the two guarded fallback slots in
CreateAHeroClass::GetFactionMaskType and CreateAHeroManager::GetFactionMaskType.
The existing `/D_CRTIMP=` retains direct calls. Comparing original and final
object symbols shows exactly the old memset reference removed and `_memset`
added. No ledger or pin edits are needed.

The removed alias is link-wide: its exact spelling remains in both source and
compiled object for `Code/Libraries/Source/WWVegas/WWLib/Rva0051C0E7Ctor.cpp`.
This repair deliberately retains that other provider of the same alias. Removing
its final copy requires a separate all-object consumer audit or repair.
`hatch_counters.py --update` lowers alternatename occurrences 2,799 -> 2,798.
The existing class-header debt remains registered; this does not adopt its header.

## Verification

- Original and edited `./build.sh Code/GameEngine/Source/Common/Rva00219B9EAccessor.cpp`:
  91/91 rows exact, 13 string literals verified. Header-induced compiler label
  renumbering is verified through the parents' EH data (13 funclet rows).
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `link_check.py --prepare-current` for the accessor and CRT thunk provider:
  218/218 rows exact, 127 named imports verified; strict reusable receipts.
- `link_check.py` for the same two units: both LINKS, accessor 3,086 authored
  bytes and CRT provider 760 bytes, against index `c95fcfcfcd`,
  2026-11-05 05:17 UTC. The census already marked the accessor linked; this is
  a real-link spelling repair and hatch reduction, not a census gain.

No real link, nightly measurement or smoke run was started. The next scheduled
real link must confirm the accessor disappears from exit_link_blockers.tsv.
The separate Rva0051C0E7Ctor.cpp legacy reference remains outside this repair.
