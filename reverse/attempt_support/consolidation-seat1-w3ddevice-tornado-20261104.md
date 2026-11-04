# W3DDevice W3DTornadoDraw allocated trial (2026-11-04)

Destination: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTornadoDraw.cpp` (allocation check passed). A fresh `Draw`-scoped consolidation report passed `--check`; the plan had 13 approved rows, three donor files and one mixed file. `find_declared_unmatched.py` passed.

`tu_skeleton.py --merge <TU> --dry-run` accepted no donors. The Xfer donor fails because `xfer` is not declared in `W3DTornadoDraw`; the module-data destructor fails byte verification. The mixed `W3DDrawModuleDeletingDtors.cpp` was left untouched. LinkGuard listed the destination and both clean donors as census-linked; the tool reported no verified merge of two or more donors and recommended reconciling `RadiusDecal`, `W3DTornadoDraw` and `W3DTornadoDrawModuleData`. No claims or source/ledger changes were made. Manual view or byte repairs are outside this mechanical lane.

An unnecessary dry-run confirmation was also made for `LocomotorSetUpgrade.cpp`, despite the existing 2026-11-03 record. It repeated the same LinkGuard unresolved symbols (`GetSnapshotName@UpgradeModule`, `isSubObjectsUpgrade@UpgradeMux`, `loadPostProcess@UpgradeModule`); no claims or changes resulted.
