### LINK-065: Zero Hour port units still define ZH bodies that BFME 2 rows elsewhere or lacks

**Status: Repair landed / awaiting census (DamageFX.cpp). Updated: 2026-10-26; inspected revision: 6533919013.**

- **Evidence / affected units:** `Code/GameEngine/Source/Common/DamageFX.cpp` (126 B, 3 rows: the
  DamageFX hashtable `clear`, `DFX::DFX`, `DFX::clear`) was ported verbatim from Zero Hour. Its
  unrowed ZH bodies held it out: `parseCommonStuff` and the four `DamageFX::parse*` (duplicates of
  rows in `DamageFXParseCommon.cpp`, calling static `INI::scanReal`/`scanIndexList` and
  `BitFlags<38>::s_bitNameList`, which BFME 2 does not provide), the veterancy-indexed
  `getDamageFXThrottleTime`/`getDamageFXList`/`doDamageFX` (BFME 2's versions take no veterancy and
  are rowed as 0x003605D5, 0x003605E3, 0x003608DF; unresolved `Object::getVeterancyLevel`), a
  wrong_selected `DamageFXStore::findDamageFX` (retail's symbol 0x00360966 is the
  `ArmorStore::findArmorTemplate` body) and its own `~hashtable` copy. Same cause as mesh.cpp's
  b57c128806 repair.
- **Completed:** 6533919013 removes those bodies (with four present-unmatched markers) and makes the
  hashtable destructor declaration-only so the retail /GX copy 0x0016DEE0 is kept. 3/3 rows exact;
  link_check (index d1f046749a) LINKS 0 -> 126 B; DamageFXParseCommon, Rva0033962FFinish,
  ArmorStoreCtor, Rva0016DEE0Cluster, ActiveBody, DamageFXRva003605AF, DamageFXHashSubscript,
  DamageFX_pairConstruct, DamageFX_hashtableNewNode and GameEngineInit still link.
  WW3D/WWLib ports, same test (2026-10-26, K1): `WW3D2/decalsys.cpp` (042fe08592, 0 -> 39 B)
  and `WWLib/wwfont.cpp` (2b3be7808e, 0 -> 33 B). Each carried one row (an empty
  `LogicalDecalClass` ctor; the header inline `TPoint2D<int>(int,int)`) beside Zero Hour bodies
  with no row anywhere in functions.csv (DecalSystemClass/DecalGeneratorClass/pool methods;
  WWFontClass) whose callees (ProjectorClass, `MatrixMapperClass::Set_Texture_Transform(Matrix4,float)`;
  `TRect<int>` members) have no BFME 2 provider. The link index showed no other object referencing
  a symbol only those units defined, so the bodies, their `??_H` anchors and `#pragma optimize`
  blocks went (39 present-unmatched markers, 6 pragma lines). `texproject.cpp` is the same case
  (one row, inline `MaterialPassClass::Set_Cull_Volume` 0x003B23A5, extern pointer anchor
  byte-verified 1/1 and LINKS 0 -> 10 B in preview) but is file-claimed by another seat; left for them.
- **Assault transport port cleanup (2026-10-26, parent `8738ddb103`):**
  [the paired current-object check](../../reverse/attempt_support/assault-transport-port-cleanup-20261026.md)
  removes ten obsolete unrowed definitions from `AssaultTransportAIUpdate.cpp`,
  the unrelated free sleep helper and the unused array anchor. Both retained
  rows remain exact (75 bytes); ten unmatched exemptions and two optimization
  occurrences retire through the hatch tool. The unit loses its two command
  COMDAT blockers and previews LINKS, 0 -> 75 bytes against index `5ce093a71a`.
  Eight adjacent units remain LINKS in the paired ten-object preview.
  `Rva0026E836Derived.cpp` retains its three unresolved secondary-interface
  methods and two address findings in both cases. Scope cleared: this port
  unit's ordinary preview only; wider closure and census confirmation pending.
- **Rva0026E836Derived cleared (2026-10-27):** the three unresolved
  secondary-interface methods and both address findings are gone. The six
  `Rva…` dtor classes are renamed to their module classes. Each dtor stores the
  root vftable of the rowed ctor of the same class: Animal, AssaultTransport,
  Siege, Horde, Transport and Wander `AIUpdate`. The secondaries are modelled
  as real bases (update +0x10, aiDoCommand +0x20, onCollide +0x24, the +0x3E4
  interfaces). 0x0048F7A7 becomes `AssaultTransportAIUpdate::aiDoCommand`. Its
  `B2` base must carry a vptr, or MSVC places the `M3` subobject at +0x10
  instead of +0x20. 0x0047EC5F becomes AnimalAIUpdate's +0x3E4 slot.
  `Rva0049A64B` → `HordeAIUpdate` is carried through the Horde ctor, the
  worker dtor and the dock-interface unit. link_check (index `bf3dd31211`,
  seven objects refreshed): Derived 0 -> 428 B, `AssaultTransportAIUpdate.cpp`
  0 -> 75 B, and the Dispatch, Disp32 getters, Horde ctor, Horde worker dtor
  and `Rva0049A64BRva0049A8FA.cpp` units still link (1,149 B). Census
  confirmation awaiting.
- **W3DDisplayString seed prerequisite (2026-10-26, inspected `71f28db691`):**
  [the native-layout handoff](../../reverse/attempt_support/w3d-displaystring-consolidation-20261026.md)
  replaces its BFME 1 include stack with BFME 2 declarations before consolidation.
  The seed's three rows remain exact and ordinary preview preserves its existing
  146 authored bytes; no new conflicting COMDAT is emitted. All six candidates
  already preview LINKS for 1,577 authored bytes. The initial merge failed on
  incompatible string/class declarations, not missing rows. Constructor/destructor
  field/virtual names remain a separate reconciliation prerequisite; no linking
  gain or census confirmation is claimed.
- **GameLOD port seed cleanup (2026-10-28, parent `3215f31ebe`):**
  [the bounded provider audit](../../reverse/attempt_support/gamelod-port-seed-cleanup-20261028.md)
  removes thirteen unrowed port definitions and their existing unmatched
  exemptions from `Common/GameLOD.cpp`. Seven rows remain exact (572 bytes),
  all 95 retained COMDAT providers are identical, and data/identity checks
  pass. The former OptionsMenu consumer has already removed its callbacks;
  its rebuilt row is exact and references none of the removed names. Both
  providers have strict current receipts. Ordinary preview preserves LINKS
  572 -> 572 bytes against `73061d9452`; the previous Shell blocker is absent.
  No linking gain or full merge is claimed. The index lacks consumer provenance
  and `touches` (LINK-017), so wider removed-provider closure awaits census.
  Hatch-register tightening is blocked by two pre-existing WWLib vector alias
  keys; no aliases are admitted and no registered debt retirement is claimed.
  The retained static parser/table and private declarations remain prerequisites.
- **MaterialPass seed cleanup (2026-11-05):** removed three unrowed pointer-signature accessors and their exemptions; 3/3 rows and all retained COMDATs unchanged, ordinary preview LINKS 72 -> 72 B. [Provider/consumer evidence and remaining merge prerequisites](../../reverse/attempt_support/matpass-port-cleanup-20261105-codex5.md).
- **Remaining / next check:** other ZH-port units (header comment "Ported verbatim from the
  Generals Zero Hour reference") whose U blockers are ZH-only callees: list each defined body,
  check whether its BFME 2 counterpart is rowed under another name or absent, and drop the ZH copy
  rather than providing the ZH callee. `hatch_baseline.tsv` can be tightened for the four removed
  DamageFX.cpp markers with `hatch_counters.py --update`.
- **Clearance:** current-object preview of DamageFX.cpp only.
- **Census confirmation:** awaiting.
