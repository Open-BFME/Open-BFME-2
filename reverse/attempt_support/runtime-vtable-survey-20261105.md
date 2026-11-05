# Runtime vtable survey: the `??_7` copies the link keeps, against retail (2026-11-05, seat halilkkaya-rt-o1)

Functions byte-match, but the vftables our objects emit can still differ from retail's. link.exe
keeps one COMDAT copy of each `??_7` (the first in link order) and silently drops the rest, so a
placeholder or Zero Hour-shaped private class view can put a short table, a wrong slot or
`__purecall` into the image even when every unit "links". This survey measures that, table by
table, for the copy the link keeps.

- Data: [`runtime-vtable-survey-20261105.tsv`](runtime-vtable-survey-20261105.tsv) (every kept
  table at risk T1-T5, one row each, ranked).
- Reproduce: [`runtime-vtable-survey-20261105.py`](runtime-vtable-survey-20261105.py), from the
  repository root after `./build.sh` and `python3 tools/link_check.py --fetch-index`:
  `python3 reverse/attempt_support/runtime-vtable-survey-20261105.py OUT.tsv [--full ALL.tsv]`
  (about 40 s; reads objects and the retail image, compiles and writes nothing else).
- Measured at `e5e17e246f` (FULL GATE green in this worktree), census index `c95fcfcfcd` (used only
  for the `referenced` set).
- Obstacle register: [LINK-514](../../docs/linking_obstacles/link-514-runtime-vtable-survey.md).

## Method

1. **Kept copy.** `link_census.objects(ledger())` gives the census's link order over the current
   tree's objects; every object's external COMDAT `??_7` symbols are read with
   `link_census._comdat_sections`. The first definer is the copy link.exe keeps (the census index
   records 0 selection exceptions to that rule).
2. **Retail address**, by evidence:
   - `code`: `name_globals.load_index()`, the DIR32 sites in matched rows (the ctor/dtor vptr
     stores) that byte-match retail. The retail word there is the table that code installs. This
     is target fact, not a ledger label. 5,654 tables (1 more is ambiguous).
   - `ledger`: a `reverse/data_ledger.csv` `kind=vtable` row whose `name`/`names` lists the
     symbol, only when no code site exists (14 tables; 1 more is ambiguous).
   - Otherwise there is no retail address (746 tables). With the 2 ambiguous ones, 748 tables are `NO-RETAIL-ADDRESS`, risk T6.
3. **Retail extent.** The smallest of: the data-ledger row size, `tools/vftable_map.py`'s
   installed run, and the run of `.text` pointers up to the next table start. A table start is
   any address a retail `mov dword ptr [m], imm32` (C7 /0, every addressing form) stores, any
   ledger vtable row, or any code-proven table. Adjacent tables can still merge when nothing in
   retail installs the second one, so a `short_by` count is an upper bound.
4. **Per slot**, our relocation's name is resolved the way `link_census.RetailTruth` judges a
   COMDAT: ledger rows (never an `icf-owner=` over-claim), pins and routes, ILT stubs followed. A
   weak `??_E` falls back to its default `??_G`, and a referent the object defines itself is
   judged in place (`_defined_at`).
   - `eq`: the name lands on retail's word.
   - `purecall`: ours is `__purecall` (0x0003B810) and retail's is another body.
   - `equiv`: the name lands elsewhere, but both reach the same body through E9 tail jumps, or
     both are short, identical, branch-free bodies.
   - `wrong`: the name lands on another single-claim body.
   - `unknown`: the name has no address, or only an over-claimed (shared) one, so nothing can be
     judged.
5. **Table.** `short_by` = retail slots − ours (calls past our end read whatever follows in
   `.rdata`). `long_by` = ours − retail. `better_copy` names a later copy with more `eq` slots,
   which the link discards.

## Ranking

- `severity`:
  - `crash`: any `purecall` slot or `short_by` > 0;
  - `misbehave`: any `wrong` slot;
  - `unproven`: `unknown` slots only;
  - `benign`: `equiv`/`long` only;
  - `ok`;
  - `unjudged`: no retail address.
- `context`, a heuristic:
  - `saveload`: a Snapshot slot 0-4 (`crc`/`xfer`/`loadPostProcess`) is not `eq`, or the class is
    `Xfer*`/`Snapshot*`/`GameState*`;
  - `boot`: a known subsystem class or a `SubsystemInterface` table, or the class's home source
    under Common/, Main/, Win32Device, W3DDevice/Common, WWVegas, GameClient/System and similar;
  - `menu`: GameClient/GUI, Shell, Apt;
  - `skirmish`: GameLogic, the rest of GameClient, W3DDevice/GameClient;
  - `other`: network, LivingWorld, tools;
  - `unnamed`: `Rva`/`Base`/`Iface`/`Opaque` placeholder classes, whose use is unknown.
  The class's home source is a `Code/` source named after the class, else the kept unit.
- `risk`:
  - T1: crash on boot, menu or save/load;
  - T2: crash in a skirmish class;
  - T3: misbehaviour on those paths;
  - T4: crash or misbehaviour in `other`/`unnamed`;
  - T5: unproven or benign;
  - T6: never referenced by kept code (`/OPT:REF` drops it), or unjudged;
  - T7: equal to retail.

  The TSV holds T1-T5. Per-slot `detail` (first three non-`eq` slots, then a count) appears for
  T1-T3 only.

## Totals (6,416 kept `??_7` tables)

| risk | tables | | severity | tables |
|---|---:|---|---|---:|
| T1 crash, boot/menu/save-load | 852 (boot 305, menu 64, save/load 483) | | crash | 3,442 |
| T2 crash, skirmish | 707 | | misbehave | 136 |
| T3 misbehave | 90 | | unproven | 750 |
| T4 other/unnamed | 1,923 | | benign | 10 |
| T5 unproven/benign | 759 | | ok | 1,330 |
| T6 unreferenced/unjudged | 757 | | unjudged | 748 |
| T7 equal to retail | 1,328 | | | |

First-failing verdicts:
- PURECALL 822;
- WRONG 352;
- SHORT 2,404;
- UNKNOWN 656;
- LONG 98;
- EQUIV 6;
- OK 1,330;
- NO-RETAIL-ADDRESS 748.

Slots in referenced tables:
- 23,714 equal;
- 3,241 `__purecall` where retail has a body;
- 908 wrong;
- 40,230 retail slots that the kept copy lacks.

There are 372 tables with `__purecall` at slot 1 (the BehaviorModule-family `loadPostProcess` slot
that lk28 found). In 10 tables a later copy is closer to retail than the kept one (`better_copy`):
DrawModule, 6 special-power ModuleData tables, GeometryUpgradeModuleData, GameSpyStagingRoom and
one placeholder. Everywhere else every copy is equally wrong, so link order is not the cause. The
class views are.

## Top risks (rank, kept unit, ours/retail slots)

- **Boot**:
  - `??_7W3DDisplay@@6B@`: W3DDisplayDtor.cpp, 1/101 (the display is created at startup).
  - `??_7AudioManager@@6BSubsystemInterface@@@`: S2DualVptrDerivedCtors.cpp, 14/105.
  - `??_7InGameUI@@6BSubsystemInterface@@@`: InGameUICtor.cpp, 7/120.
  - `??_7Display@@6B@`: BfmeStrVM0Dtor.cpp, 69/100.
  - `??_7LightClass@@6BRefCountClass@@@`: 6/130.
  - `??_7BFMECRCWriter@@6B@`: 5/39.
  - `??_7GameMessageList@@6B@`: MessageStreamListCtors.cpp, 3/18, slots 1-2 wrong.
- **Save/load and CRC**:
  - `??_7XferSave@@6B@`: BfmeConv881O1.cpp, 1/39.
  - `??_7XferMD5CRC@@6B@`: XferMD5CRC.cpp, 2/39. Game-logic CRCs run through this class, so it bears
    directly on the retail-CRC bar.
  - The AIUpdate family's ObjectModule tables: Siege, Transport, Wander, AssaultTransport,
    GiantBird, Worker and AIUpdateInterface, 12-16/154 with Snapshot slots 1/3 wrong or pure.
  - About 25 `*ModuleData@@6B@` tables with 4/31 slots, slots 1-3 `__purecall`.
- **Menu**: the Apt screens (`AptSkirmish`, `AptLanLobby`, `AptPlayer`, `AptOnlineCustomMatch`,
  ...), 1/14-23, all kept from destructor units.
- **Skirmish**: `??_7HordeContain@@6BHordeContainInterface@@@` 155/155 with 151 pure;
  `GarrisonContain` 73 and `TunnelContain` 65 pure. Every module's `BehaviorModuleInterface`
  table is 47/47 pure for CallHelpOnDamage, CostModifierUpgrade, HitReactionBehavior,
  ObjectSMCHelper (every object carries one), RebuildHoleExposeDie and UpgradeBehaviorBaseView.
  The `BodyModuleInterface` tables are 43/43 pure for ActiveBody, OathbreakerBody and RespawnBody.

## Caveats

- `context` is a path and name heuristic; no runtime trace backs it.
- A table that only a destructor installs is live only during destruction. The survey does not
  tell ctor-installed tables from dtor-installed ones, so dtor-unit 1-slot tables (most of the
  `unnamed` T4 rows) may rank too high.
- `short_by` is an upper bound wherever two retail tables sit back to back and nothing installs
  the second.
- `unknown` slots are not judged. Most are `??_E`/placeholder names with no ledger address, or a
  slot whose expected address is over-claimed by several rows.
- No census rule changes. This is measurement, not a gate.
