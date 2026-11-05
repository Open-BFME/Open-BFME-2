### LINK-368: BuildableHeroListUpgrade ctor needs UpgradeModule slot providers
Status: Blocked. Updated: 2026-11-04; inspected revision: 3fb65a79b9.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Upgrade/BuildableHeroListUpgradeCtor.cpp` (0x004B8332, census-linked 49 B) byte-matches on the canonical `UpgradeModule.h`, but its emitted tables leave `?vslot07@UpgradeModule@@UBE_NXZ` (0x00460AE2, rowed as placeholder `Rva00460AE2ByteChase32Field::get`) and `?processUpgradeRemoval@UpgradeModule@@MAEXXZ` (fold onto 0x00460AD3) unresolved (LINKED 49 -> 0); this blocks the `BuildableHeroListUpgrade.cpp` tu-merge. [Trial](../../reverse/attempt_support/buildable-hero-ctor-canonical-upgrademodule-20261104/README.md).
Completed: none; the explicit-store ctor stays.
Remaining / next check: provide both names (see LINK-218, LINK-246 for the same family), then re-apply the canonical ctor, `tu_views.py` and the merge guard.
Progress 2026-11-05: `UpgradeModule::vslot07` and `processUpgradeRemoval` now have fold rows in `VslotSmallBodiesU.cpp`. Not re-checked on the canonical ctor; remaining: re-apply after a census records them. `?crc@UpgradeModule` was listed in the merged TU only, and still needs `BFME_SNAPSHOT_NAME_SLOT`.
Progress 2026-11-05: with the providers in census 2026-11-05 15:19, the canonical ctor plus BFME_SNAPSHOT_NAME_SLOT in the seed passed the merge link guard and merged into BuildableHeroListUpgrade.cpp (4/4). Not confirmed by a later census or the real link.
Clearance: pending (awaiting census confirmation).
Census confirmation: not claimed.
