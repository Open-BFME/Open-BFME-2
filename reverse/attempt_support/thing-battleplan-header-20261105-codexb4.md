# Thing adoption: battle-plan bonuses and WoTR tactic

Inspected base: `f820e131ec`, 2026-11-05, seat `codexb4`.

`PlayerBattlePlanBonuses.cpp` replaces its empty private Thing declaration with
the canonical `Thing/thing.h`. Its Object view previously owned the vptr and
template pointer itself; canonical Thing owns the first 0x60 bytes. Removing
those duplicate fields and starting Object padding at 0x60 retains the retail
producer ID (+0x78), body (+0x254), and weapon condition (+0x380) offsets. The
existing getTemplate now reads the inherited template pointer at +4.

`Rva005AB125Tactic.cpp` already includes the canonical header and adjusts its
Object padding for that base. It needs no source change; its queued diagnostic
predates the current source. This is stale header debt, not lost coverage.

Verification:

- `find_declared_unmatched.py PlayerBattlePlanBonuses.cpp` passes before and
  after the change; all defined functions are matched.
- `./build.sh Code/GameEngine/Source/Common/RTS/PlayerBattlePlanBonuses.cpp`:
  7/7 matched rows, float references pass, parent EH data verifies the renamed
  compiler funclet label at 0x007759F0.
- `header_adopt_lane.py accept --class Thing` passes separately for both
  sources and retires their two rows from `reverse/header_queue.tsv` itself.
- Ordinary `link_check.py` over both sources: battle-plan bonuses
  694 -> 694 B; tactic 352 -> 352 B. Index census: 2026-11-05 05:17 at
  `c95fcfcfcd`. Both objects are dependency-current. This is a preview preserving
  1,046 census-linked bytes, not a new census or real-link measurement.

An automatic Module_AsObject.cpp adoption trial reproduced its queued duplicate
AsObject definition diagnostic and restored the source. It remains unchanged
and queued; no claim of adopting that unit or clearing the Thing family is made.
