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
