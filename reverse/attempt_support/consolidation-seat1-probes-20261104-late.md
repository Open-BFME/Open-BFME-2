# Consolidation seat 1 late-session probes — 2026-11-04

Both destinations passed the allocator's `--check-tu`, and their scoped
`name_lane.py consolidate` snapshots passed `--check` before planning and the
merge dry run. No claims, source changes, splits, or ledger changes were made.

## BuddyThread

`Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp` had 142
approved rows, 8 donor files, 11 mixed files, and no statically refused rows.
The dry run accepted no donors. LinkGuard rejected the seed itself because the
merged object no longer defines census-referenced
`?rva00550B4C@Rva00550B4C@@QAEXXZ`. It also rejected `GetNickForMessage.cpp`
because the merged object loses `endThread`, `getLocalProfileID`, and
`isConnected` providers. Other donors failed on duplicate STL template
definitions or bytes. Do not split these mixed sources to work around the
LinkGuard refusal; its report enumerated seven affected census-linked sources.

## GameInfo

`Code/GameEngine/Source/GameNetwork/GameInfo.cpp` had 164 approved rows, 4 donor
files, 8 mixed files, and no statically refused rows. The dry run accepted no
donors. `GameSlotIsPlayer.cpp` duplicates `SLOT_OPEN` and `SLOT_CLOSED`;
`GameInfoReset.cpp` defines a compiler-generated special member absent from the
class declaration; `GameInfoDtor.cpp` needs `GameInfo::m_C8` and related view
members. Reconcile the `GameInfo`, `GameSlot`, and enum views before retrying.
LinkGuard reported census-linked `GameInfo.cpp`, `GameInfoDtor.cpp`,
`GameInfoReset.cpp`, and `GameSlotIsPlayer.cpp`.

## Remaining shard work

The full allocator listing contained 94 shard 1 destinations. At this session's
start, a basename scan of seat-1 handoffs found six unheld candidates with no
prior mention: `LivingWorld.cpp`, `BuddyThread.cpp`, `HotKey.cpp`, `GameInfo.cpp`,
`GameWindow.cpp`, and `StrategicInGameUI.cpp`. BuddyThread and GameInfo are now
recorded above. Continue with the remaining four and any newly eligible
destinations after rechecking the current allocator; do not retry these two
without changed inputs. No mixed split was applied. No matched rows were
removed or newly preserved, and source-file reduction remains zero.
