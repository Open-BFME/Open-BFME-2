### LINK-612: AICommandInterface subobject consumers header adoption
Status: Cleared for four consumers only. Updated: 2026-11-05; inspected revision: `69671f0adef`.
Completed / clearance: HeroModeSpecialAbilityUpdate, Rva00495801, TeleportToCasterSpecialPower and AIStructureCreepTactic adopt AIUpdate.h; 80/80 rows match, all 289 COMDATs and external definitions survive, four ordinary LINKS preserve 5,942 bytes, and one owning-tool acceptance retires four queue rows. [Evidence and remaining cohort prerequisites](../../reverse/attempt_support/aicommand-subobjects-header-20261105-codex2/README.md).
Remaining / next check: the other 13 selected consumers retain their queues; reconcile their embedded subobjects, missing canonical methods and field/preprocessing prerequisites before retrying. No shared-header edit is needed for the cleared consumers.
Census confirmation: awaiting; no new real-link or runtime result claimed.
