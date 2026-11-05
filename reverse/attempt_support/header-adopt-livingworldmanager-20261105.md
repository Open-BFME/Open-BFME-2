# LivingWorldManager header adoption, 2026-11-05 (handoff)

Landed: eight units adopt `Code/GameEngine/Include/GameLogic/LivingWorldManager.h`
(SetUpRegionEffectsManager, Rva004FF28ECtor, StrategicInGameUI planning-phase
ctor, LivingWorldCampaignManager, W3DDisplaySmallSlots, CreateSound,
GameLogic/System/LivingWorld/LivingWorldManager.cpp, StagingRoomGameInfo).
The header now models +0x204 (`Rva00056F61 m_sounds`), +0x22C
(`OpaqueRefElement4 sound22c`) and +0x230 (`int owner230`).

## Remaining rows and what each needs

- `GameClient/LivingWorldManager.cpp`: three 0x14-byte `Rva000427195` tables at
  +0x26C/+0x280/+0x294. Adding them to the header (with `#include
  "Rva000427195.h"`) rebuilds every consumer byte-exact except
  `GameClient/Rva00213A85.cpp`, which keeps a private `Rva000427195` and
  `Rva000411084` (C2011). Fix, tested: include the canonical
  `GameClient/Rva000411084.h` and `GameLogic/Rva000427195.h`, rename
  `iterator.m_node` to `m_current`, and size the pad as
  `m_padToState[0x2C0 - 0x218]` (the private table was an empty 1-byte class,
  so `[0xBB]` only placed +0x2C0 by accident) -> 8/8 match, all 42 consumers
  687/687. Not landed: `class:Rva000427195` was held by another seat. Do that
  unit first, then the header fields and this unit.
- `XferObjects`: +0x204 is now `m_sounds` (use `m_sounds` and
  `m_sounds.m_numElements`); still needs +0x24C, a pointer vector
  (`_STL::vector<Rva003FD789 *>` there, `PtrVector` in the dtor unit).
- `Cleanup` (+0x3C, +0x48, +0x264, +0x2A8 vector, +0x2C0 bool),
  `CreateBeaconObject` (+0x14 data 0x150 bytes, hash_map +0x218),
  `DoomSetup` (scalars inside +0x14..+0x1BC), `Rva002BEDCAMovementDuration`
  (floats at +0x1D0..+0x1DC), `INIBfmeBlockParsers_Rva00210F64Parse`
  (+0x14 block of 0x1B0 bytes plus a bool at +0x1C4): all view the 0x1F0-byte
  +0x14 subobject (`Rva00212ED3` in the dtor unit) differently; they need one
  canonical nested type for it.
- `LivingWorldObjectParser`: a hand-stubbed `map` template at +0x2B4; needs a
  real STLport map member.
- `LivingWorldManagerDtor`: the whole member list with destructible types
  (earlier blocks: pinned dtor 0x002115C5 handoff, re_attempts 38423).

Inference, not landed: `Rva00213A85` (0x00213A0E..0x00213C30) uses the +0x204
table and +0x2C0 state from inside LivingWorldManager's address range, so it is
likely LivingWorldManager itself.
