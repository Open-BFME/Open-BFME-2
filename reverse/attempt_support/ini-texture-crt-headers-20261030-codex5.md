# Texture diagnostics CRT header cleanup

Base: `e0de66604e`. Scope: the existing
`Code/GameEngine/Source/Common/INIStatsRecordTextures.cpp` unit, claimed as
`file:Code/GameEngine/Source/Common/INIStatsRecordTextures.cpp`.

The Microsoft-header queue identified five handwritten stdio declarations
using `void *` in place of the CRT's `FILE *`. The unit now includes
`<stdio.h>` and uses `FILE *` for its local stream. Removing the local
`/D_CRTIMP=` override lets the existing `/MD` configuration supply the same
DLL-import declarations through the CRT header. No source paths, names,
class layouts, function rows, pins or shared headers change.

## Verification

- Frozen-file checks pass before and after. Supported baseline and final
  `./build.sh` runs both pass all five existing rows: the 435-byte parent at
  `0x0050C9EF`, its 10-byte handler at `0x007945C7`, and the three 8-byte
  unwind bodies at `0x007945AF`, `0x007945B7` and `0x007945BF`.
- Both builds verify two nonempty string references, the empty string and
  six imports. `eh_verify.py` reports one EXACT parent graph. Header-induced
  compiler-label renumbering preserves all three unwind placements through
  that graph; no ledger object-symbol edits are needed.
- Before/after COFF comparison through `link_census.comdat_bodies` preserves
  all 16 external COMDAT names, relocation-aware digests and sizes.
  `link_census.object_symbols` is also identical: 16 defined, 23 referenced,
  one weak, seven alternates and no include directives. In particular, the
  `__imp__` references for fopen, fclose, fseek, ftell and fread are unchanged.
- The owning Microsoft-header auditor finds no local or include-closure
  occurrences and classifies the unit clean. Its `refresh_queue` API removes
  exactly this unit's queue row, retiring five conflicting declarations.
- `link_check.py --fetch-index` retains the published 2026-10-30 10:11 index
  at `12b9e7a7c0`. Strict current-object preparation passes. Both census-only
  and ordinary previews retain LINKS, 435 -> 435 authored bytes. These are
  predictive checks; no census or linked-byte gain is claimed.
- The scoped staged `link_batch_audit.py` returns INCONCLUSIVE (exit 2):
  its index predates the outgoing base, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Full consumer selection/loss verification remains open. Carry the
  unit and affected consumers into the next scheduled census, as recorded
  in `docs/linking_obstacles.md`.

The object comparison establishes unchanged emitted code and bindings; it
does not establish a recovered source identity for the address-named parent.
