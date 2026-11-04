### LINK-193: LANAPI private views block canonical header adoption
Status: Open. Updated: 2026-11-03; inspected revision: dff5a2c3ed.
Completed: OnNameChange.cpp adopts LANAPI.h using the existing slot-33 declaration; 3/3 rows byte-exact, EH EXACT, owning acceptance retires one debt row, ordinary preview LINKS 58 -> 58 B.
Remaining / next check: 24 other trial units need private-layout reconciliation, caller-visible declarations or include prerequisites; fix one evidenced constraint before retrying that unit.
Evidence: [cohort diagnostics and accepted scope](../../reverse/attempt_support/lanapi-header-adoption-20261103-codexb.md).
Clearance: OnNameChange adoption only; broader class scope remains open. Census confirmation: awaiting; no headline gain claimed.

2026-11-04: LANGameInfoParseGameOptionsString.cpp adopts LANAPI.h with the native low-byte AmIHost check; 7/7 rows and EH remain exact, acceptance retires one header row, ordinary preview LINKS 607 -> 607 B. Six newly tried callers still need view/declaration reconciliation: [evidence](../../reverse/attempt_support/lan-options-header-20261104-codexb5.md).

2026-11-04: LANPlayer_copy.cpp and LANGameInfo.cpp adopt LANPlayerClass.h and BfmeNetAddress.h (rows exact, 5 header rows retired); LANAPI.cpp, LANAPIhandlers.cpp and ChatWindowsLan.cpp still wait on BfmeNetAddress's base/constructors and a record constructor that likely takes the address by value: [evidence](../../reverse/attempt_support/lanplayer-header-adoption-20261104-claudec2.md).

2026-11-04: GetMyName, Reset and Rva00581641 adopt LANAPI.h (header declares the rowed Rva004495A2/rva00581641 helpers); 3 rows retired, LINKS 421 -> 421 B. Slot-64 callers still wait on a named `_bfme_lan64`: [evidence](../../reverse/attempt_support/lanapi-header-adoption-20261104-claudeb.md).
2026-11-04: AptLanLobby GetValidSelectedGameInfo and MPOwnerValidatGameInfo adopt it via the protected ValidateGameInfo plus `friend class AptLanLobby`; 2 rows retired, LINKS 95 -> 95 B. SetOption: retail passes slot 19 an unnormalised int, the header has RequestAccept(bool).
2026-11-04: LivingWorldLogicRva002B89E1 (slot 41 rva00249B08) and AptLanLobbyDestructor (`::delete TheLAN`, window-manager include first) adopt it too; 2 rows retired, LINKS 1,767 -> 1,767 B.
2026-11-04: LANAPI.h names slot 59 GetLobbyPlayers and slot 64 getLocalAddress (inline folded getters); ChatWindowsLan, OnGameStartTimer, Rva00449693 and LobbyMenuForwarders adopt it; 6 rows retired, LINKS 1,323 -> 1,323 B.
2026-11-04: Rva005816E3, Rva00582EB0, handleSetAccept, OnPlayerJoin and ConnectionManager sendFile/sendFileAnnounce adopt it (TU-local zeroing `ZeroNetAddress` temporary); 8 rows retired, LINKS kept. OnAccept waits on an out-of-line StringBase<G>::validate switch in string_base.h.
2026-11-04: MapSelectMenu_Rva0050CF3C, LANGameInfo (link_check +74 B) and Recorder adopt it; 5 rows retired. The vtable emitters (ctor/dtor) match but unlink: LANAPIInterface slots 2-8/11-13 and `_bfme_lan58`/`_bfme_lan62` have no providers. MapSelectMenu.cpp: shim include clash.

2026-11-04: LANAPI.cpp and LANAPIhandlers.cpp adopt LANPlayerClass.h and BfmeNetAddress.h; 124/124 rows exact, 4 header rows retired, ordinary preview LINKS 14,705 -> 14,705 B. The address base/constructor prerequisite is cleared for these two consumers: [evidence](../../reverse/attempt_support/lanplayer-address-header-20261104-codexb.md).

2026-11-04: GameInfo.cpp and GameSlotApparent.cpp adopt BfmeNetAddress.h with address-specific field accesses; 137/137 rows exact, 2 header rows retired, ordinary preview LINKS 9,876 -> 9,876 B ([evidence](../../reverse/attempt_support/gameinfo-netaddress-header-20261104-codex.md)); other class prerequisites remain unchanged.
