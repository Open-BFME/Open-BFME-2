### LINK-443: W3DLightDraw donors do not compile against the seed's class views
Status: Blocked. Updated: 2026-11-05; inspected revision: 463674729a.
Evidence / affected units: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp` and its Draw, module-data, transform and pool-key donors; [allocated consolidation dry run](../../reverse/attempt_support/w3d-light-draw-consolidation-20261105-codex.md).
Completed: allocation, scoped planner and TU plan passed; dry run accepted no donors due missing `DrawModule`/member declarations and a module-data vftable redefinition. LinkGuard lists the destination and five affected donors as census-linked.
Remaining / next check: reconcile the donor class views and required headers; rerun the supported merge and affected provider/consumer checks.
Clearance: pending; no composed object or consumer-binding verification was possible.
Census confirmation: not claimed.
