### LINK-230: Quick-match private views block remaining TU composition
Status: Open. Updated: 2026-11-05; inspected revision: 84e8439352.
Completed: adopted canonical LadderPref in AptOnlineQuickMatch.cpp and its two queued recent-ladder/map consumers (48/48 rows match; 3 header debts retired; combined preview preserves 3,185 linked bytes); reconciled readiness views and member-pointer ABI, then merged the readiness fragment into approved AptOnlineQuickMatch.cpp; 39/39 rows match and the merge link guard passes.
2026-11-05: adopted canonical GameText.h, OptionPreferences.h, UserPreferences.h and QuickMatchPreferencesClass.h in the seed (6 header debts retired), then merged Rva005BA6EEPopulate.cpp and QuickMatchPopulateSideComboBoxRva005BB3A1.cpp (48/48 rows match).
Then reconciled AptOnlineQuickMatchConstructor.cpp with the seed (canonical preference, FunctorBinding and Image headers; seed's holder and AptOnline view; seed flags; 4 header debts retired) and merged it (61/61 rows match).
Then adopted GameText.h, PlayerInfo.h, NameKeyGenerator.h, GameSpyStagingRoom.h, AptMessengerOnline.h and MapCache.h in AptOnlineQuickMatchOptions_OnMatched.cpp (3 header debts retired), gave the seed the correct GameSpyGameSlot pad (+0x1AC..0x1D0) and the donor's Rva005A6D47 destroy(unsigned) view, and merged it (97/97 rows match).
Remaining / next check: LadderPrefCopy.cpp rejects on bytes; GameSlot (include cycle), GameSlotConnectInfo (no 2-argument ctor in the canonical header) and PlayerTemplate header rows stay on the seed; mixed files still require approved splits.
Evidence: [composition checks and path/debt audit](../../reverse/attempt_support/quickmatch-ready-consolidation-20261104.md).
Clearance: readiness composition verified locally; remaining donor compositions remain open. Census confirmation: not claimed.
LadderPref adoption evidence: [three-unit byte, debt and link checks](../../reverse/attempt_support/ladderpref-header-adoption-20261104.md).
