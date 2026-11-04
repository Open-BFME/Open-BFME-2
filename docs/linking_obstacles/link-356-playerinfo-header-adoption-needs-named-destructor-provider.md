### LINK-356: PlayerInfo header adoption needs the named destructor provider
Status: Blocked for two consumers; eight other adoptions verified. Updated: 2026-11-04; inspected revision: `58e50cfbe4c4`.
Completed: eight private PlayerInfo views replaced by the existing header; 265 retained matched rows verify and acceptance retired their eight header-queue rows while preserving census-linked bytes.
Remaining / next check: recover the existing 0x001EF50E destructor provider's real identity (`??1Rva001EF50E@@QAE@XZ` currently), then retry AptMessengerOnlineResponse.cpp and AptOnlineQuickMatchOptions_OnMatched.cpp; their byte-exact trials were restored because `??1PlayerInfo@@QAE@XZ` was unresolved (2,359 and 3,106 census-linked bytes lost in preview).
Evidence: [scope, current-input verification and trial diagnostics](../../reverse/attempt_support/playerinfo-header-adoption-20261104-codexb4.md).
Census confirmation: no new measurement or linked-byte increase claimed; remaining PlayerInfo consumers are outside the verified scope.
