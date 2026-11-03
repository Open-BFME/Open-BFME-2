### RadarUpdate TU merge: canonical duplicates in its view header (2026-11-03)

`RadarUpdateConstructor.cpp` (53B) now adopts the canonical `UpdateModule` header
(`Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`) instead of a private view;
`header_adopt_lane.py adopt` maps its `m_field1C` to `UpdateModule::m_updateState`.
Verification: `build.sh` 1/1 matched, byte-exact, no new unmatched rows.
**Linking UNVERIFIED, not clean**: the pre-push `link_batch_audit` returned INCONCLUSIVE for
this object ("1 source object(s) lack current receipts", index at `70f7a5ae2a` behind the
outgoing base), so no link verdict is claimed and no census credit is taken. Carry it into the
next census.

The TU merge itself stays blocked. `tu_skeleton.py --merge RadarUpdate.cpp` moved from C2511
to C2011 `BehaviorModuleInterface`/`BehaviorModule` type redefinition once the donor took the
canonical header: `RadarUpdateView.h` privately declares `BehaviorModule`,
`BehaviorModuleInterface` and `UpdateModule`, all three registered in
`reverse/canonical_classes.csv`. `header_adopt_lane.py adopt` cannot retire them ("no private
view found") because the duplicates live in the header, not the unit, and it only rewrites
units. `RadarUpdate.cpp` is the header's only includer, so the scope is contained.

Dead end, do not retry: adopting canonical `ModelConditionFlags` in the seed to clear
`adopt_first` does **not** route around this — `?extendRadar@RadarUpdate@@QAEXXZ` stops
byte-matching when `ModelConditionFlags::m_words` replaces the view's `m_bits`.
Prerequisite: retire the three canonical duplicates from `RadarUpdateView.h` under byte
verification. Recorded in `reverse/re_attempts.log` at `0x004A0D0F`.

**2026-11-03 constructor installer repair:** 53B remains exact after selecting the native Snapshot name slot before inclusion and declaring the real Radar key/xfer/update/name overrides. Primary table is now13 slots (no fabricated anchors); ledger-resolved entries agree with retail, including actual Radar xfer/key and update facet. Three orphan empty methods and markers retire from Supply; its49B constructor and all64 remaining providers stay unchanged. Normal verification2/2, strict frozen checks pass. Current preview still leaves Radar unresolved on its own GetSnapshotName: the six-byte004A0C27 owner/file is independently claimed and unchanged. The supported to-class rename is the remaining name-slot prerequisite; no alias/pin substitute was added. TU merge/canonical view prerequisite above remains open. [Table, provider, orphan and outstanding census evidence](../../reverse/attempt_support/radar-constructor-native-table-20261103/README.md). Prior owning-pointer pusha76ab8d1cd audit was INCONCLUSIVE (index23b85ddde5/base2278a89146ddb57ac91d5e111f161306326780b2,1receipt gap, first Common/Rva0057702EClear.cpp); carry its source/consumer scope into the next scheduled census.
