### LINK-321: GameSlot empty-base views shift derived storage
Status: Cleared for the three named consumers. Updated: 2026-11-04; inspected revision: 987170dc1a.
Completed: LANGameInfoSlots.cpp, LANGameSlotIsLocalPlayer.cpp and NATUpdateBfme.cpp adopt GameInfo.h with corrected derived padding/address storage; 29/29 function rows exact, three header-queue rows retired.
Evidence / clearance: [scoped repair and checks](../../reverse/attempt_support/gameslot-base-adoption-20261104-codexb.md); ordinary preview LINKS 3,610 -> 3,610 B against census f12552d0a7.
Remaining / next check: other queued GameSlot consumers retain their individual prerequisites; reconcile their recorded member/layout constraints before another trial.
Census confirmation: awaiting; no linking headline gain claimed.
