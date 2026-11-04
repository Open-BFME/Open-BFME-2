# LANAPI header adoption, 2026-11-04 (claudeb)

Inspected revision: 2aae37e39b. Census index 2026-11-04 05:53 at 5a13f2cd61.
Scope: three units adopt Code/GameEngine/Include/GameNetwork/LANAPI.h by hand;
no automatic cohort rerun.

## Changes

- LANAPI.h gains two non-virtual member declarations that the ledger already
  rows under exactly these mangled names: `Rva004495A2(LANMessage *, unsigned
  int)` at 0x004495A2 (defined in LANAPI.cpp) and `rva00581641(LANMessage *,
  const BfmeNetAddress *)` at 0x00581641. Declarations only: no layout, vtable,
  identity, pin, alias or flag change.
- LANAPIGetMyName.cpp: the automatic mapper refused the inherited `m_name`
  ambiguity; inside a LANAPI member `m_name` resolves to LANAPI::m_name (+0x14)
  as the private view did.
- LANAPIReset.cpp: private prefix replaced; reset calls the shared
  Rva004495A2 declaration.
- LANAPIRva00581641.cpp: slot 54 is the header's AmIHost (int), tested on its
  low byte; slot 61 is rva00248E2F(bool), fed from the file's message view whose
  +0x40 byte is now typed bool (retail pushes the raw byte). m_currentGame is
  read through the file's LANGame layout view per access (retail reloads +0x44).

## Checks

- find_declared_unmatched: all defined functions matched, before and after.
- ./build.sh: GetMyName 1/1, Reset 6/6 (two funclets resolved via parent EH),
  Rva00581641 1/1; the 12 other LANAPI.h includers still match.
- eh_verify: 1 graph EXACT (Reset), 0 not exact.
- header_adopt_lane.py accept --class LANAPI: PASS for all three; retired 3 rows.
- link_check: 3/3 LINKS, LINKED 421 -> 421 bytes (prediction, not a census gain).

## Still open

LANAPIRva00449693.cpp and LANAPIOnGameStartTimer.cpp call native slot 64,
which the header keeps as private `_bfme_lan64` ("uncallable native +48
address getter"); naming it is an identity change that needs its own evidence.
LANAPI.cpp carries private BfmeNetAddress/GameInfo views besides the m_name
ambiguity, so the header cannot be included until those reconcile.

## Second batch (ValidateGameInfo)

- LANAPI.h declares the rowed protected `ValidateGameInfo(LANGameInfo *)`
  (`?ValidateGameInfo@LANAPI@@IAE_NPAVLANGameInfo@@@Z`, 0x00449969) and
  `friend class AptLanLobby`, which both callers' private views already used.
- AptLanLobbyGetValidSelectedGameInfo.cpp and AptLanLobbyMPOwnerValidatGameInfo.cpp
  include the header: 1/1 and 1/1 matched; all 17 LANAPI.h includers still
  match; accept PASS retires 2 rows; link_check LINKED 95 -> 95 bytes.
- BfmeAptScreenLanLobbySetOption.cpp (0x00444240) cannot use the header's
  RequestAccept(bool): the compiled call normalises the int argument
  (`83 7c 24 04 00 .. 0f 95 c2 52`) where retail pushes it raw
  (`ff 74 24 04`). File restored; logged as blocked in re_attempts.log.

## Third batch (no header change)

- LivingWorldLogicRva002B89E1.cpp: private `slotA4` is the header's slot 41
  `rva00249B08(LivingWorldBattle *)` (rowed 0x00249B08). 1/1 matched.
- AptLanLobbyDestructor.cpp: private `void *deleteObject(int)` was slot 0 called
  with flag 0 and its return passed to `::operator delete`; that is MSVC's code
  for `::delete TheLAN;` on a polymorphic class, now spelled so. The include
  guard needs BfmeAptWindowManager.h before LANAPI.h's short
  SubsystemInterface, so that include moved up. 38/38 matched, EH 2 EXACT.
- accept PASS retires 2 rows; link_check LINKED 1,767 -> 1,767 bytes.

## Batch 4: AptMessengerLan.cpp (2026-11-04)

- Replaced the private `LanSlots` template and LANAPI view with LANAPI.h (window manager header first).
- `TheLAN->slotE0()` -> `(GameInfo *)TheLAN->GetMyGame()`.
- build.sh: 5/5 matched; eh_verify EXACT 1; find_declared_unmatched clean.
- link_check: LINKED 266 -> 266 bytes. header_adopt_lane accept retired 1 row.

## Batch 5: slots 59/64 named; ChatWindowsLan, OnGameStartTimer, RequestGameStart (2026-11-04)

Target facts: vtable VA 0x00C3E680 slot 59 holds 0x001DB0A8 (`8B 41 0C C3`,
returns +0x0C, m_lobbyPlayers; the interface table 0x00C3E588 has _purecall
there) and slot 64 holds 0x0053B8E5 (`8D 41 48 C3`, returns &+0x48,
m_localAddress). Both bodies are ICF folds already rowed under other owners.
Names are inferred from the consumer units' spelling (ChatWindowsLan's
GetLobbyPlayers, LANAPI.cpp/LANAPIhandlers.cpp's getLocalAddress); no donor
proves them. LANAPI.h declares them inline like slots 51/56; slot 58 stays
private.

- LANAPILobbyMenuForwarders.cpp already included the header: accept PASS.
- ChatWindowsLan.cpp adopts LANAPI.h, LANPlayerClass.h and BfmeNetAddress.h
  (GameText.h first). Retail pushes the address as two whole dwords
  (`ff 77 04`, `ff 37`); the canonical word port would zero-extend, so the
  call reads the two dwords. 14/14 matched.
- LANAPIOnGameStartTimer.cpp, LANAPIRva00449693.cpp: slot 64 is getLocalAddress;
  slots 42/43 are OnGameStart/OnWOTRGameStart. 6/6 matched.
- All 20 earlier LANAPI.h includers rebuilt: 156/156 matched.
- eh_verify: 5 EXACT. find_declared_unmatched clean.
- accept PASS: LANAPI x4, BfmeNetAddress x1, LANPlayer x1 (6 rows retired).
- link_check: 3/3 LINKS, LINKED 1,323 -> 1,323 bytes (prediction).

## Batch 6 (2026-11-04)

LANAPI.h now declares the rowed non-virtual handlers rva005816E3 (0x005816E3),
rva00582EB0 (0x00582EB0), handleSetAccept (0x005815EA) and the protected
removeGame (0x00449913, `IAE` in the ledger). Declarations only: no layout or
vtable change.

- LANAPIRva005816E3.cpp, LANAPI_handleSetAccept.cpp: slot 46 is
  OnGameOptionsPacked(const BfmeNetAddress &, int, const void *, int), slot 38
  OnAccept(const BfmeNetAddress *, bool). The message's +0x40 field is read as a
  bool (ZH's isAccepted), so no normalisation is emitted. LANGame stays a
  local view reached through m_currentGame. 2/2 matched.
- LANAPIRva00582EB0.cpp: slots 37/42/43/46/61 are OnPlayerLeave, OnGameStart,
  OnWOTRGameStart, OnGameOptionsPacked and rva00248E2F. 3/3 matched (EH funclet
  verified past its renumbered label).
- LANAPI_OnPlayerJoin.cpp: slot 64 is getLocalAddress, slot 26
  RequestGameOptionsPacked(true, &zero). 1/1 matched.
- ConnectionManager_sendFile.cpp and ConnectionManager_sendFileAnnounce.cpp:
  retail zeroes the OnChat address record between the argument pushes
  (`89 5d e8 66 89 5d ec`), which is a constructed temporary. The canonical
  BfmeNetAddress has no ctor. A named local zeroed before the call
  mis-orders the stores. `&BfmeNetAddress()` value-initialises with `stos` and
  shifts the frame. A TU-local `ZeroNetAddress : BfmeNetAddress` with an inline
  zeroing ctor matches. 12/12 matched.
- Blocked: LANAPI_OnAccept.cpp calls the out-of-line empty
  `?validate@?$StringBase@G@@ABEXXZ` (0x000B3FD0), and the shim string_base.h
  defines validate() inline. Any unit including LANAPI.h (unicode_string.h)
  loses that call. This needs a per-unit switch in the shim, like
  BFME_STRINGBASE_PUBLIC_DTOR.
- All 29 LANAPI.h includers rebuilt: 194/194 matched. eh_verify EXACT on
  every touched unit. link_check: every touched unit LINKS with bytes kept
  (373 + 202 + 800 B).
- accept PASS: LANAPI x6, BfmeNetAddress x2 (8 rows retired).
