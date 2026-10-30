# Player canonical header: adoption blocked by held units (2026-10-30, halilkkaya-cls3)

Header: `Code/GameEngine/Include/Common/PlayerBFME2.h` with its bases
`Code/GameEngine/Source/Common/Rva002B0F3CIface.h` and `Rva00380200.h`
(commit "Write Player's canonical header from retail evidence; adoption
pending"; its message holds the retail evidence). Not registered yet, and no
unit includes it.

## Lane trials (`header_adopt_lane.py run --class Player --header ...`)

| master | units | pass | refused by |
|---|---|---|---|
| ab249dd2c4 (2026-10-30 00:08) | 674 | 312 (first draft 294) | 44 held passing units |
| ab249dd2c4 (00:24, final header) | 674 | 319 | 28 held passing units |
| 7bdf3de426 (14:45, no --apply) | 666 | 316 | 10 held passing units, up to 3.7 h left; `class:Player` itself refused because `class:Object` (object-retail) locks `RTS/Player.cpp` and `RTS/PlayerBattlePlanBonuses.cpp` |

Failures at 7bdf3de426: 257 name a Player member the header lacks (their own
field spellings: index, m_54, m_side, m_money, m_name58, ...), 63 use such a
field unqualified, 10 change bytes or a data/callee identity, the rest single
cases. Passing units by approved TU (00:24 run): ScriptActions.cpp 22,
Object.cpp 18, Player.cpp 18, InGameUI.cpp 8, AIStates.cpp 8,
ScriptConditions.cpp 8.

link_check baseline over the 313 previewable passing units at 7bdf3de426
(census 2c21184e84): 309 link, LINKED 378,761 -> 370,007 before any change.

## Finish

1. `python3 tools/claims.py claim class:Player` (needs `class:Object` free).
2. Append to `reverse/canonical_classes.csv`:
   `Player,Code/GameEngine/Include/Common/PlayerBFME2.h,hand-written: ctor 2B0F3C stores BBB554 at +0 and BE2B78 at +4 and builds Rva00380200 (ctor 380523) at +8 then BFDF3C/BFDF30/BFDF18 (Snapshot then Rva002B0F3CIface then Rva00380200); sizeof 0x758 from PlayerList 2A7FBF; members from the 146 ledger rows; data offsets from Player::init 2AF729; opaque elsewhere`
3. `python3 tools/header_adopt_lane.py run --class Player --header Code/GameEngine/Include/Common/PlayerBFME2.h --jobs 12 --apply`
   when no passing unit is held (it applies all or nothing).
4. `./build.sh` the adopted units, `link_check` them against the baseline,
   scoped DIR32, commit header row + units + `reverse/header_queue.tsv`.
   Do not commit `reverse/class_contracts/Player.json`: a sampled contract
   says bases [] and size 56, which the ctor contradicts.

## Leads that would raise the pass rate (target facts first)

- `isPlayerActive` (9 failing units). Retail: 0x002AA223 returns byte +0x33A
  (rowed `Player::isPlayerObserver`), 0x002AA22A returns byte +0x734, and
  0x002AA231 returns `!+0x33A && !+0x734`. Zero Hour's Player.cpp defines
  isPlayerObserver, isPlayerDead and isPlayerActive consecutively with exactly
  these bodies (donor fact). The ledger spells 0x002AA22A
  `Rva002AA22AByteField::get` and 0x002AA231 `BfmeMemberRV::bfmeAskRV`, while
  its `Player::isPlayerDead` row at 0x0028A7D8 reads +0x448. A naming-lane
  rename (docs/naming.md) would let the header declare both out of line.
- `Player::getDefaultTeam` row 0x0046F7E4 reads +0x160; setDefaultTeam
  0x002ABC7E stores the team at +0x2EC. Its identity is doubtful.
- `Player::DoXfer` row 0x002B1522 is spelled non-virtual (Q) but fills
  Snapshot's slot 3; PlayerDoXfer.cpp stays queued until it is renamed.
- `m_playerTeamPrototypes` / `getPlayerTeams` (12 units): an STLport
  `list<TeamPrototype *>` at +0x32C (the dtor walks it); `m_money` / `getMoney`
  (about 20 units): a Snapshot-derived Money at +0x90 (ctor stores table
  0x00BE1AA0 there). Both need shared type headers before Player can expose
  them; the AsciiString members at +0x4C and +0x58 likewise.
- Tooling: `run --all` drops held units and queues them ("held by X during run
  --all; retry when released"), but `run --class X --apply` refuses outright,
  so a class with 600+ units rarely finds a window on a busy fleet. Parity for
  `run --class` is a tooling decision, not taken here.
