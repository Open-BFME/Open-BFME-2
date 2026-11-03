# LANAPI header adoption, 2026-11-03

Inspected source revision: `dff5a2c3ed`.
Census preview index: `8661f15284`, 2026-11-03 20:03 UTC; fetched with
`python3 tools/link_check.py --fetch-index` (local index already identical).

## Completed scope

`Code/GameEngine/Source/GameNetwork/LANAPIOnNameChange.cpp` includes the existing
`Code/GameEngine/Include/GameNetwork/LANAPI.h` instead of a private class.
Its opaque no-argument slot-33 dispatch uses the shared declaration
`rva00248E87()`. The ledger already owns that declaration at RVA 0x00248E87
in LANAPILobbyMenuForwarders.cpp and identifies it as native slot 33.
This is reuse of an existing placeholder identity, not recovery of its meaning.
No shared header, function identity, compiler flag, alias or pin changed.

Verification:

- `./build.sh Code/GameEngine/Source/GameNetwork/LANAPIOnNameChange.cpp`:
  3/3 matched; parent 0x0024952E, handler 0x00771A54, funclet 0x00771A4C.
  The verifier resolves the renumbered funclet label through parent EH data.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `eh_verify.py`: 1 EH graph EXACT, 0 not exact, 0 baselined, 0 missing objects.
- `header_adopt_lane.py accept --class LANAPI` for the source: PASS; the tool
  retired exactly one header_queue.tsv row.
- Ordinary `link_check.py` preview: LINKS, LINKED 58 -> 58 authored bytes.
  This preserves the scope's census-linked bytes; it is not a new census gain.

## Automatic cohort trial and remaining prerequisites

The default picker claimed the first 25 LANAPI queue sources. Every source
passed find_declared_unmatched before the trial. `header_adopt_lane.py adopt
--class LANAPI --header Code/GameEngine/Include/GameNetwork/LANAPI.h --apply
--jobs 4` accepted 0/25 automatically and restored its trial source changes.
OnNameChange was then repaired as above. The other 24 remain unchanged.

Distinct diagnostics, grouped by the next investigation:

- BfmeNetAddress private `port` is 4 bytes at +4, while the canonical member
  has a different size: Recorder.cpp, ChatWindowsLan.cpp.
- Private LANAPI padding has no canonical offset/size counterpart:
  MapSelectMenu_Rva0050CF3C.cpp, LANAPICallbacks.cpp,
  LANAPILobbyMenuForwarders.cpp, LANAPIRva00449693.cpp.
- LANAPI and SubsystemInterface both declare `m_name`, so automatic unqualified
  field mapping refuses ambiguity: LANAPI.cpp, LANAPIGetMyName.cpp.
- Canonical-layout trial reports C2011 (inspect the repeated declaration before
  changing anything): MapSelectMenu.cpp, LANAPICompleteDestructor.cpp,
  LANAPIConstructor.cpp.
- Caller-visible methods absent from the header: AptLanLobbyDestructor.cpp
  (`deleteObject`), AptLanLobbyGetValidSelectedGameInfo.cpp and
  AptLanLobbyMPOwnerValidatGameInfo.cpp (`ValidateGameInfo`),
  BfmeAptScreenLanLobbySetOption.cpp (`v19`), LivingWorldLogicRva002B89E1.cpp
  (`slotA4`), LANAPIOnGameStartTimer.cpp (`getLocalIP`), LANAPIReset.cpp
  (`Rva004495A2`), LANAPIRva00581641.cpp (`rva00581641`).
- Field rename `m_ip` -> `ip` collides with an existing binding:
  ConnectionManager_sendFile.cpp, ConnectionManager_sendFileAnnounce.cpp.
- Include prerequisites: AptMessengerLan.cpp requires BfmeAptWindowManager
  ordering; BfmeAptScreenLanLobby.cpp requires GameText before the short
  Subsystem header. AptLanLobby.cpp's input scan refuses a trigraph/continued
  line comment in vendor/stlport/config/stl_dec_vms.h:50.

Next work should choose one caller with an evidenced existing declaration or
reconcile one private layout in its own verified change, then retry that unit.
Do not rerun this whole unchanged cohort. No TU merge or class-wide closure is
claimed, and no alternate-name alias was removed.
