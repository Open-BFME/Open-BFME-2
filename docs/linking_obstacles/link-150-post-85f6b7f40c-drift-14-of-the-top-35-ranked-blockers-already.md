### LINK-150: post-85f6b7f40c drift — 14 of the top 35 ranked blockers already link (2026-10-29, seat dd-11)

Status: informational; no repair. At 36cc3221c3, checked against the published
index 2026-10-29 15:08 at 85f6b7f40c, `tools/link_rank.py --top 45` gives 35
units; `link_check.py --paths-from` on those 35 reports 14 LINKS (5,604 B) and
21 still not linking. The picker keeps serving the 14 because the census
predates their repairs, so re-run link_check before diagnosing any of them:

- LINK-140 consumers (all confirmed in this seat's paired-current check):
  NarrowStringRecordCopyBFME2.cpp 850, stlport_narrow_stringbuf_overflow_setbuf.cpp
  567, stlport_narrow_ostringstream_dtor.cpp 429, PeerThreadStats_PackStatKey.cpp
  295, stlport_narrow_ios_imbue.cpp 275, stlport_wide_ios_imbue.cpp 238,
  WWDownload/urlBuilder.cpp 868. Paired-current with the provider, PeerThread.cpp
  (18,622) and WWDownload/registry.cpp (1,907) link too: 21,672 B total.
- LINK-149/LINK-145 destructor duplicates: RebuildHoleExposeDie.cpp 670.
- Other post-census repairs: GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp 518,
  TeamTemplateInfoDtor.cpp 236, StringScalarVectorCopyBFME2.cpp 213,
  Rva001F9524Concat.cpp 160, stlport_map_int_pod16_subscript.cpp 149,
  Rva00056da2Finish.cpp 136.

The 21 that still do not link, by first blocker: `duplicate` destructor copies
whose counterpart file is LINK-149's in-flight repair (Rva0026E836Derived.cpp,
TailJumpWrappers5B.cpp); `unresolved` unrowed class destructors (Scripts.cpp,
RegionDetailsStructuresIconCtor.cpp, T1Base005F3750Ctor.cpp,
GlobalWeatherSystemCtorDeferred.cpp, MultiplayerSettingsCtor.cpp,
Rva006DE1A0Finish.cpp, BfmeConv881O1.cpp); `unresolved` address-named globals
(Rva00066A9ABody.cpp); non-retail COMDAT copies (Rva008314E0StringReplace.cpp,
StlSweepW4Rva00584405.cpp, Rva007B7280Siblings.cpp, Rva00566695Assign.cpp,
ProductionPrerequisiteRecVectorInsertOverflow.cpp); vtable-first differences
(EmotionTrackerUpdateCtor.cpp, FireWeaponWhenDeadBehavior.cpp); the 4.6 facets
unit's duplicate `_Locale_*` workers (stlport_LocaleMbtowc.c,
stlport_LocaleStrcmp.c, LINK-139's family); and W3DPropDraw.cpp,
BfmeResetTextureRef.cpp. `MultiplayerSettingsCtor.cpp` has the clearest model
error: its class derives from the canonical SubsystemInterface (virtual
destructor) while retail's `??1MultiplayerSettings@@QAE@XZ` is non-virtual at
0x00381293, rowed in MultiplayerSettingsDtor.cpp.
