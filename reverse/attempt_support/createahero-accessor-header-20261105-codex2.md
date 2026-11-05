# CreateAHeroManager leaf accessor adoption

Inspected base: `72234bf59f` (game source unchanged from `a3018887a1`).
Date: 2026-11-05. Claim owner: `yasinschroeder-codex2`.

## Retained changes

Two complete one-function units now include the existing canonical
`Code/GameEngine/Include/GameLogic/CreateAHeroManager.h` and no longer declare
private copies of the manager:

| Source under `Code/GameEngine/Source/Common/` | Row | Bytes |
| --- | --- | ---: |
| `CreateAHeroManagerHeroList.cpp` | `rva0021F797`, `0x0021F797` | 16 |
| `CreateAHeroManager_GetDefaultHero.cpp` | `GetDefaultHero`, `0x0021A6C8` | 96 |

Both functions cast canonical `field174` storage to the existing `Rva0040A3F9`
view. The manager header's constructor evidence places its owned pointer
storage at +0x174, and `Common/Rva0040A3F9.h` records the native pointer-range
and indexed-lookup evidence. This changes neither member offsets nor helper
identities. No shared header, row identity, source path, pin or alias changes.

## Verification and debt

- Initial `check_csv.py` passes: 99,474 function rows.
- `find_declared_unmatched.py` passes before and after the edits.
- Normal `./build.sh` verifies all three original accessor units before trial.
  The first edited three-unit build verifies these two functions; only the
  separate bling-binder trial fails.
- `header_adopt_lane.py accept --class CreateAHeroManager` on the two retained
  sources prints PASS for both and retires exactly their two header-queue rows.
  No queue rows were edited by hand.
- Ordinary combined `link_check.py` reports both LINKS, retaining 112 -> 112
  unique bytes against the published index `f44cbcf5b0`, 2026-11-05 15:19.
  This is a preview, not a new census or real-link result.
- The restored bling-binder source passes its normal build, 1/1.

## Remaining cohort prerequisites

The served 25-source automatic adoption trial retains no edits. Its refusals
split into opaque canonical storage versus typed member views, missing nested
class definitions, incompatible StringBase/includes, and existing source-layout
probe failures. The existing header remains unchanged. The two small manual
adoptions above resolve only their own queue entries; the other 38 entries
remain queued.

`CreateAHeroManager_GetBlingBinder.cpp` was also tried manually. Casting
`field168` to its existing `Vec20` view makes MSVC hoist a base-address LEA.
Reading start/finish through the canonical scalar storage instead produces a
44-byte body versus retail's 46 bytes: start is cached in ESI, the division
uses ECX, and ESI is restored at the end instead of immediately after the
division. The trial's raw byte-sequence similarity is 0.711111, not a
byte-verification result. Its Code source was restored and reverified.
The commit hook correctly refused a generic `reverse/attempts/` stash because
this address already has matched real C++; the stash was deleted as instructed,
and the partial verdict retracted in favor of a blocked adoption verdict. No
nonmatching trial source is retained. A future attempt needs a source expression
that preserves native register lifetime and member reloads without changing
the canonical class or adding compiler-control hatches.

No source consolidation or linked-byte gain is claimed. Header debt falls by
two; the scoped acceptance gate is the retirement evidence.
