### LINK-030: ZH-header units emit a wrong `BitFlags<116>::clear` ahead of the rowed copy

Status: provider repair verified / awaiting census. Updated: 2026-10-30;
original open inspection: 9f93879fe9 (2026-10-26, index 47e030bafc), retained below.
Evidence / affected units: `BitFlagsClear.cpp` (14 B, row 0x00666E80) fails `selected` on
`?clear@?$BitFlags@$0HE@@@QAEXXZ`. The index has four copies: `DumbProjectileBehavior.cpp`,
`Player.cpp` and `WeaponSet.cpp` (all `wrong`, first in link order) and `BitFlagsClear.cpp`
(`retail`). The wrong copies are `jmp ?reset@?$bitset@$0HE@@_STL@@...`, whose reset calls
`memset`; retail's is four inline dword stores.
Completed: trial (reverted, no commit) of a decl-only `template <> void BitFlags<116>::clear();`
in `WeaponSet.cpp`: after `PreRTS.h` it hits C2908 (already instantiated: ZH `KindOf.h`'s
inline `CLEAR_KINDOFMASK`/`SET_ALL_KINDOFMASK_BITS` call `clear()`, and `DisabledTypes.h`,
`ObjectStatusTypes.h` do the same); placed before `PreRTS.h` with `Lib/Basetype.h`,
`Common/STLTypedefs.h` and `Common/BitFlags.h`, it fails C2084 (`<new>` placement new/delete
defined twice).
Remaining / next check: the declaration must land between `BitFlags.h` and `KindOf.h` inside
`PreRTS.h`, i.e. a TU-scoped shim of the sweep `PreRTS.h` (or a shared decision for all three
units), then re-verify each unit's rowed callers still call 0x00666E80.
Clearance: pending.
Census confirmation: not claimed.

**Current-provider recheck (2026-10-26, inspected `896af216804e`):** `BitFlagsClear.cpp`, `DumbProjectileBehavior.cpp`, `Player.cpp` and `WeaponSet.cpp` were checked together against d1f046749a. The row owner still loses its reset copy and sees a wrong selected clear copy. No new source trial or shared-header edit is applied. The previously documented include-order/shared-view prerequisite remains; a future repair must preserve every provider and consumer row. Raw evidence: `build/link-worker-20261026-w2/all-cohort-before.log`, `all-cohort-after.log` and `provider-paths.log`. No clearance or census claim.

**2026-10-30 prerequisite repair (base `c647a75e55`, index `12b9e7a7c0`):**
DumbProjectileBehavior and WeaponSet declare the shared clear before PreRTS,
with its array-placement guard selected before the early BitFlags include.
This resolves the earlier C2908/C2084 trial boundary without a shared-header
edit. Each object loses only its wrong 5-byte clear and 20-byte reset copies;
all retained raw bodies stay identical, with four reset-to-clear relocations.
The original diagnostic line arguments are preserved with `#line`.
Normal build passes 4/4 rows; strict preparation passes 5/5 including the
unchanged clear owner. Preview remains 0/3 LINKS, 0 -> 0 authored linked bytes:
Player's wrong clear/reset copies remain and that scope is held by another
worker. Its early declaration and four-provider verification are still needed.
The staged audit is INCONCLUSIVE on the older index and missing current
`Common/0CreateAHeroManager21FE49.cpp` consumer receipt; full consumer/loss
checks and scheduled-census confirmation remain open. Carry both edited
objects, Player, the clear owner and affected consumers into the next census.
No clearance, debt retirement or census gain is claimed.
[Object comparison and remaining work](../../reverse/attempt_support/bitflags-clear-declarations-20261030-codex5.md).

**2026-10-30 final provider repair (Player scope now available):** Player
declares the kept clear before first instantiation. Preserve the original
Windows-before-BaseType TRUE/FALSE types, array-placement guard, PreRTS line58
and existing bitset test specializations. A negative include-order control
changes isPlayableSide's bool code; the final ordering restores it exactly.
All eleven Player rows pass; its 412 retained external raw bodies are
identical. Only three reset-to-clear relocations change; the wrong 5-byte
clear and 20-byte reset definitions disappear with no new definition.
The unchanged held DumbProjectileBehavior/WeaponSet sources are verified in
fresh private objects, without editing their sources or shared caches.
All18 cohort rows pass and both clear/reset blockers disappear from all four
units. The 14-byte clear owner newly predicts LINKS (0 -> 14 B); the other
three clients retain their independent obstacles. This clears the stated
provider scope only, awaiting census; no headline gain is claimed.
The broader audit remains qualified by the old index and missing consumer
receipts. CreateAHero's23 rows now prepare successfully; the latest prior
audit stops at AIBuildable instead. Evidence:
`reverse/attempt_support/player-bitflags-clear-link-20261030/`.
