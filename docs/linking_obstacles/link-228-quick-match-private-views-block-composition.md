### LINK-230: Quick-match private views block remaining TU composition
Status: Open. Updated: 2026-11-05; inspected revision: 1038eba023.
Completed: adopted canonical LadderPref in AptOnlineQuickMatch.cpp and its two queued recent-ladder/map consumers (48/48 rows match; 3 header debts retired; combined preview preserves 3,185 linked bytes); reconciled readiness views and member-pointer ABI, then merged the readiness fragment into approved AptOnlineQuickMatch.cpp; 39/39 rows match and the merge link guard passes.
2026-11-05: adopted canonical GameText.h, OptionPreferences.h, UserPreferences.h and QuickMatchPreferencesClass.h in the seed (6 header debts retired), then merged Rva005BA6EEPopulate.cpp and QuickMatchPopulateSideComboBoxRva005BB3A1.cpp (48/48 rows match).
Then reconciled AptOnlineQuickMatchConstructor.cpp with the seed (canonical preference, FunctorBinding and Image headers; seed's holder and AptOnline view; seed flags; 4 header debts retired) and merged it (61/61 rows match).
Remaining / next check: AptOnlineQuickMatchOptions_OnMatched.cpp needs GameText.h (fetchFormat is canonical fetchPtr), PlayerInfo, GameSlot and GameSlotConnectInfo adoption, and needs PlayerInfo adoption and its GameSpyGameSlot view (+0x1AC..0x1D0) reconciled with the seed's (+0x1AC..0x338); LadderPrefCopy.cpp rejects on bytes; mixed files still require approved splits.
Evidence: [composition checks and path/debt audit](../../reverse/attempt_support/quickmatch-ready-consolidation-20261104.md).
Clearance: readiness composition verified locally; remaining donor compositions remain open. Census confirmation: not claimed.
LadderPref adoption evidence: [three-unit byte, debt and link checks](../../reverse/attempt_support/ladderpref-header-adoption-20261104.md).
