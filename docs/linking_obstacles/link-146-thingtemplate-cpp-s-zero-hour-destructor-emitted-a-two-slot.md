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
