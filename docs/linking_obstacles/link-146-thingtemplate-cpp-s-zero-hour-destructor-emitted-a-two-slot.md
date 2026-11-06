### LINK-146: ThingTemplate.cpp's Zero Hour destructor emitted a two-slot ThingTemplate vftable (2026-10-29, seat b1)

Status: repaired, pending census confirmation. The 85f6b7f40c census lists
ThingTemplateConstructor.cpp and Rva0033DDA1Dtor.cpp linked=no, each losing
`??_7ThingTemplate@@6B@`: ThingTemplate.cpp (Zero Hour header) was first in link
order with a two-slot copy (`??_EThingTemplate@@MAEPAXI@Z`,
`getObjectMemoryPool`), referenced only by its own `present-unmatched` empty
protected `~ThingTemplate`. Retail's vftable 0x00810C4C has one slot (the
canonical header's evidence). Repair: that destructor is gone (present_unmatched
-1); an `absent-from-retail` anchor destroys a ModuleInfo, the prerequisite
vector and the weapon-set finder so the unit still emits the three member
destructors it rows (23/23 exact). The unit no longer defines the vftable.
Preview: ThingTemplateConstructor.cpp 0 -> 1,881 B, Rva0033DDA1Dtor.cpp 0 -> 770 B.
ThingTemplate.cpp itself still does not link (unresolved AudioEventRTS, INI and
Player names from its ZH view; several wrong STL COMDATs), unchanged.

**2026-10-30 recheck, base `3134afceb4`, index `85f6b7f40c`:** the default
picker served the destructor from the historical unlinked census. Its normal
build verifies all 51 rows, including 44 EH funclets. A joint current-source
preview again reports LINKS for the destructor (770 authored bytes) and
constructor (1,881 bytes). ThingTemplate.cpp still reports ten unresolved
names and its existing conflicting STL copies. No source repair was needed;
the scoped fix above remains pending the next scheduled census.

**2026-11-03 unused donor subset:** remove nine unrowed methods without replacement helpers. Twenty-nine incidental definitions retire; all964 remaining provider payloads/bindings are identical. The published-index/current-object audit checks524 other objects and finds no outside dependency on any removed definition. Normal/private23/23 and allfive EH graphs EXACT; frozen check passes. Nine marker hatch keys retire through the owning counter. PreviewU9->U8 (s_objectFieldParseTable donor reference gone), whole unit still0 with its existing four losing/two wrong-kept COMDATs. CalcCost remains required by Player::canAffordBuild; getPerUnitSound by DeliverPayload. A private Armor-parser trim lost owned clear006E00A0, so that pair stays. Audio/list identity, FX insert and weapon matcher prerequisites remain. [Scope, fingerprints, consumer proof and pending prior audit](../../reverse/attempt_support/thing-template-donor-cleanup-20261103/README.md). No census/full-game clearance is claimed.

**2026-11-04 current unused sound-getter subset:** three formerly cached callers changed source since the earlier audit. Their normal refresh verifies7/7 and fresh actual routes contain none of the ten removed getter/static/find helpers; the saved touch union and broad all-cache exact-route audit find no other dependency. Remove that now-unused donor cluster: all23 rows/fiveEH and905 retained providers/properties stay identical, no additions; strict frozen passes. Owning hatch update retires precisely one getter marker. This supersedes only the earlier getter-retention prerequisite; calcCost, audio callback/owned emissions and other identity debt remain. Whole unit still unlinked. [Current consumer/row/provider/debt proof](../../reverse/attempt_support/thing-template-unused-sound-getter-20261104/README.md).

**Native audio-provider distinction (2026-11-04):** pair2A12E1 is a4B-list-mapped cleanup with an existing correct typed alias but two current old-name consumers. Insert358E9F belongs to HotKey's counted-handle map, not that list or an AudioEvent object. Current Record donor has the complete native node/construction closure; HotKey Value's instruction twin has wrong POD construction. Respect current approved InGameUI/HotKey destinations and migrate actual caller identities; no row replacement or alias was applied in this inspection. [Exact native/provider/consumer boundary](../../reverse/attempt_support/thing-template-native-audio-provider-boundary-20261104/review.md).

**2026-11-04 HotKey native-copy prerequisite repaired:** the existing Value insertion now reaches the complete native counted-copy closure: construct358CA0/45B (own EH EXACT), pair-copy358B43/34B, node358DA0/34B and insert358E9F/148B. All45 HotKey rows/eight owning EH graphs remain exact, strict frozen passes and the normal object matches the private winner across137 providers. Saved-index guard is clean and2,217 linking bytes are retained. The empty derived Value is only a bounded ABI view; original inheritance/pointee identity remains unknown. No row/alias/pin was changed; ThingTemplate real-name ownership and current callers still need separate repair. [Native, provider and normal proof](../../reverse/attempt_support/hotkey-native-copy-contract-20261104/README.md).

**2026-11-04 insertion identity retraction:** separately retract the disproven AudioEvent `_M_insert` row at358E9F/148B, tombstone it and preserve every other record. The native24-byte counted-handle node contradicts the AudioEvent120-byte node. Normal ThingTemplate control23/23 and retained22/22 verify with no Source change. Current-map destination is approved HotKey.cpp; ordinary real-body admission follows in its own commit. No old-name consumer is rebound. [Exact retraction plan and policy](../../reverse/attempt_support/hotkey-insertion-ownership-20261104/README.md).

**2026-11-04 insertion ownership restored:** ordinary admission now rows the exact148B Value insertion in approved HotKey.cpp after separate native45B construction/34B node ICF dependencies. One map source cell follows existing approval; one redundant Value pin retires, Record binding remains. Both mixed Source files are unchanged;72/72 normal rows, strict frozen, nine HotKey EH graphs and final guard pass. Scoped preview HotKey2217->2364 bytes (+147), Record retained184; official census unchanged. Existing Audio pair/list, FX/weapon identities and six unresolveds still block ThingTemplate. [Full final consumer/register/path audit and census gaps](../../reverse/attempt_support/hotkey-insertion-ownership-20261104/outgoing-audit.md).

**2026-11-04 AudioEvent pair duplicate retired (claudeb):** ThingTemplate.cpp's 0x002A12E1 `pair<AsciiString,AudioEventRTS>` dtor row and its two EH rows are tombstoned. The EH rows move to the list-valued owner in stlport_rb_tree_subscript_002a6a2d.cpp, and the three old-name consumers are migrated to that type. Retail-absent ZH parseMaxSimultaneous/parsePerUnitSounds are dropped (-2 markers). link_check: ThingTemplate unresolved 6 -> 1 (getProductionCostChangePercent); the other four units all link (stlport +10 B). FXList insert and weapon matcher identities remain. [Evidence](../../reverse/attempt_support/thing-template-audio-pair-retirement-20261104/README.md).

**Next step for the last unresolved (2026-11-04, claudeb):** `getProductionCostChangePercent` is referenced only by ThingTemplate.cpp's ZH `calcCostToBuild`, whose only consumer is Player.cpp's ZH `present-unmatched` `Player::canAffordBuild`. Index `5a13f2cd61` touches show no object other than Player.obj referencing `?canAffordBuild@Player@@QBE_NPBVThingTemplate@@@Z` (only its own `.debug$F`). Removing canAffordBuild and then calcCostToBuild (two markers) should leave ThingTemplate.cpp with no unresolved names. Player.cpp was claimed by another seat at the time.

**2026-11-04 unresolved name cleared (claudec3):** the Zero Hour `Player::canAffordBuild` and `ThingTemplate::calcCostToBuild` bodies are removed (present_unmatched -2), so no object references `getProductionCostChangePercent` any more. link_check: Player.cpp LINKS (0 -> 112 bytes). ThingTemplate.cpp still fails the census on two non-retail COMDATs, the FXList map `insert_unique` and the WeaponTemplateSet `findBestInfoSlow`. Confirm in the next real link.


2026-11-06 recovery review: the interrupted HotKeyMap application duplicates tree storage and introduces unresolved/incomplete helper declarations; it has no completed owning acceptance. No Code or debt change retained. Preserve the existing native-copy contract and establish a coherent shared view first. [Source inspection and disposition](../../reverse/attempt_support/hotkey-interrupted-adoption-recovery-20261106.md).
