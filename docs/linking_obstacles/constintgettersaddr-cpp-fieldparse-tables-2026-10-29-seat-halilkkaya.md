## ConstIntGettersAddr.cpp FieldParse tables (2026-10-29, seat halilkkaya-fpt1)

Done (commits 0b5feb85bd, 16e7cdaec7, 7ed40a3467): 29 raw-int FieldParse tables became typed
`FieldParse` tables (field-name literal from `reverse/fieldparse_tables.tsv`, matched parser
named with `(FieldParseProc)&__identifier(..)`), with 28 byte-verified data rows. link_debt
addresses 1042 -> 349; link_check of the 18 previewable consumers unchanged.
Reusable rules: the decorated name of an array global carries its element type (`?X@@3QBHB`
vs `?X@@3QBUFieldParse@@B`), so every consumer's `extern const int X[]` must become
`extern const FieldParse X[]` with a complete `struct FieldParse` in the same commit;
link_check shows the old spelling as unresolved.

Remaining in the file (349 literals), not converted because a referenced symbol has no
defining object (do not invent one):
- userData name lists with no data row: 0xDB960C and 0xDBC284 (s_modelDrawFieldTable),
  0xC1B6D8 (s_fxpsSizeAngleTable), 0xDCD4D0/0xDCD550 (AODCrushCollideTable),
  0xDBB4C4/0xDBB4F0 (s_transportAiFieldTable, s_hordeContainFieldTable), 0xDBE6F0
  (s_radiusDecalFieldTable). Each needs a data row plus defining object first.
- Tables with no rows in fieldparse_tables.tsv (field names unknown without reading the
  image): s_animSoundFieldTable, s_moneyCrateFieldTable, s_assaultTransportFieldTable,
  s_hordeModelDrawFieldTable, s_crowdResponseFieldTable.
- The 14 getters returning image addresses (three Drawable statics have no definition).

Update (wt_x, same seat): s_moneyCrate, s_assaultTransport, s_crowdResponse and s_hordeContain are now
typed (field names read from retail with build.read_target_bytes, verified by data rows; hordeContain's
0xDBB4F0 userData is the owned TheLocomotorSetNames). link_debt 349 -> 260. Still open: s_animSound
(consumer AnimationSoundClientBehavior.cpp) and s_hordeModelDraw (W3DHordeModelDrawModuleDataParse.cpp)
were held by another worker; s_modelDraw (0xDB960C unnamed), s_fxpsSizeAngle (0xC1B6D8 only
address-named g_00C1B6D8), AODCrush (0xDCD4D0/0xDCD550), s_transportAi (0xDBB4C4) and s_radiusDecal
(0xDBE6F0) need a real-named, data-rowed list first. TheWeaponSlotTypeNames (0xDBC284) is owned but
s_modelDraw also needs 0xDB960C.

Update (2026-10-30, seat claudec3): s_animSound (AnimationSound -> rowed 0x004CA798, MaxUpdateRangeCap ->
parsePositiveNonZeroReal) and s_hordeModelDraw (LodOptions -> W3DModelDrawModuleData::parseLodOptions) are now
typed with data rows; both consumers spell `extern const FieldParse`. link_check at index 85f6b7f40c:
AnimationSoundClientBehavior.cpp LINKS 1,882 -> 1,958 B, W3DHordeModelDrawModuleDataParse.cpp LINKS 21 B;
ConstIntGettersAddr.cpp addresses 260 -> 254. Census confirmation pending. Still open: s_modelDraw,
s_fxpsSizeAngle, AODCrush, s_transportAi, s_radiusDecal (userData lists need real-named data rows) and the getters.

Update (2026-11-01, seat halilkkaya-ad-o1): blocked, banked in
reverse/attempt_support/constintgettersaddr-typed-fieldparse-20261101 (patch, generator, readme). The
last five raw tables (s_fxpsSizeAngle, s_modelDraw, AODCrush, s_transportAi, s_radiusDecal) can be
typed `FieldParse` tables with data rows: field names come from retail, every parser is the matched row
at its RVA, and the owned lists are named (0xDBC284 TheWeaponSlotTypeNames, 0xDBB4F0
TheLocomotorSetNames). Evidence at base e57b7de842, index 987ee56fdc:

- 6-source build: 57/57 functions, 39 data rows verified.
- Scoped DIR32 is OK.
- ConstIntGettersAddr.cpp addresses fall from 254 to 24.
- The five consumers and the 14 providers still LINK, with sizes unchanged.

Every one of the five tables has one userData list with no external real-named definition, and those
ten words stay as `(const void *)0x...` literals inside the typed entries. Those are integer-address
casts, real link debt, and the pre-commit `link_debt.py --staged` rightly refuses them (0 -> 10), even
though the census count drops by 230. The first `false-reject` log row was retracted (a `void` row, then
a plain `blocked` row). A `static` copy of a list does not help either: data_rows refuses a
relocation to a TU-local symbol. The ten words and what each needs:

- 0xC1B6D8 (Rotation): defined only as address-named `g_00C1B6D8` (FXParticleSystemModuleParsers.cpp, no
  data row). exports.csv names it `?RotationTypeNames@FXParticleSystem@@3QBQBDB`, but the data ledger's
  stale `?g_00C1B6D8@@3PAPBDA` size-560 entry already blocked a rebind once
  (rotation-table-link-blocked-20261014).
- 0xDB960C (MinLODRequired): only `g_00DB960C` in GameLOD.cpp, with no data row and no proven name.
- 0xDCD4D0/0xDCD550 (AODCrush, 6 words), 0xDBB4C4 (AutoAcquireEnemiesWhenIdle) and 0xDBE6F0 (Style):
  per-TU copies of Zero Hour's header `static` lists (TheDamageNames, TheDeathNames,
  TheAutoAcquireEnemiesNames, TheShadowNames under DEFINE_*_NAMES). Each of those names already belongs
  to another copy's data row, and data_rows allows one row per name.

The patch lands once the ten lists have real external names, each with a data row. The 14 `mov eax,imm32` getters are unchanged (see "Hard-coded
image addresses: name_globals has no candidates").

Update (2026-11-01, seat halilkkaya-ad-o1, later): 0xDBB4C4 is now named. Retail's list there is
YES/STEALTHED/NO/NOTWHILEATTACKING/ATTACK_BUILDINGS plus the null terminator, passed by
AutoAcquireEnemiesWhenIdle to parseBitString32. Zero Hour's AIUpdate.h spells this exact list
TheAutoAcquireEnemiesNames, and no data row held that name. It is defined once, external, in
ConstIntGettersAddr.cpp with a data row, and s_transportAiFieldTable is typed with a data row (both
userData lists named). link_check at index 987ee56fdc: ConstIntGettersAddr.cpp addresses 254 -> 214.
TransportAIUpdateModuleDataBuildFieldParse.cpp still LINKS 152 B. AIUpdate.cpp (ZH-donor, TU-local
`static` copy) was not linking at census and still does not, LINKED 0 B both before and after. The
other four tables of the banked patch still wait on 0xC1B6D8, 0xDB960C, 0xDCD4D0/0xDCD550 and 0xDBE6F0.

Update (2026-11-01, seat halilkkaya-ad-o1, last): 0xC1B6D8 is now named. The address-named
`g_00C1B6D8` is renamed to retail's export `?RotationTypeNames@FXParticleSystem@@3QBQBDB` (exports.csv
ordinal 1375) in FXParticleSystemModuleParsers.cpp and Rva0055FB37Write.cpp, with a new 28-byte data row.
s_fxpsSizeAngleTable is typed against it with a data row. data_check reports 0 findings: the stale
`?g_00C1B6D8@@3PAPBDA` data_ledger entry that blocked rotation-table-link-blocked-20261014 no longer
fires in shadow mode. link_check at index 987ee56fdc: ConstIntGettersAddr.cpp addresses 214 -> 195.
FXParticleSystemDefaultParsers (90 B), FXParticleSystemModuleParsers (512 B) and Rva0055FB37Write
(1,179 B) still LINK, sizes unchanged. Still open: s_modelDraw (0xDB960C), AODCrush (0xDCD4D0/0xDCD550),
s_radiusDecal (0xDBE6F0) and the 14 getters.

Update (2026-11-02, seat halilkkaya-ad-o2): AODCrushCollideTable and s_radiusDecalFieldTable are typed
with data rows. ConstIntGettersAddr.cpp addresses go from 195 to 130 (link_check at index 93c5672365).
- The blocker was a false reject in the data-row verifier, now fixed with regression tests in
  bba49993ac and d2a50c3098 (Verifier-Change). Retail holds identical TheDamageNames arrays at 12
  .data addresses, TheDeathNames at 6 and TheShadowNames at about 70. 0xDCD4D0/0xDCD550 are referenced
  only from AODCrushCollideTable and 0xDBE6F0 only from s_radiusDecalFieldTable, with no code xref.
  These are Zero Hour's DEFINE_*_NAMES header statics, one copy per including TU.
- data_rows.verify_row now places a relocation to a TU-local data object by content, as it places a
  string literal. MSVC 7.1 names a file static `_name`. Retail's pointer must land in data over the
  static's proven sizeof and overlap no data row. The bytes must match, and the static's own
  relocations must land too.
- ConstIntGettersAddr.cpp now defines `static` TheDamageNames/TheDeathNames/TheShadowNames copies.
  CollideModuleDataBuildFieldParse.cpp and RadiusDecal.cpp (now including the canonical FieldParse.h)
  spell `extern const FieldParse`.
- Verification: the 3-source build passes 45/45 functions and 39 data rows. find_declared_unmatched is
  clean, and scoped DIR32 is OK. RadiusDecal.cpp (2,415 B) and CollideModuleDataBuildFieldParse.cpp
  (88 B) still LINK. The parser providers INI.cpp, INI_parseFXList.cpp, INI_parseObjectCreationList.cpp
  and GameLogic/System/ObjectFilter.cpp still LINK (12,666 B), unchanged.
- Reusable rule: a per-TU header-static list is spelled `static` in its own unit. No external name is
  invented.

Morning handoff (130 literals left):
- s_modelDrawFieldTable (116 literals): the banked patch hunk applies once 0xDB960C has a real name.
  - Identity: the ModelLOD level-name array, 4 entries Low/Medium/High/UltraHigh with no null.
    Retail's options table at VA 0xDBD120 (OptionsMenu.cpp's BfmeEnumTable) pairs "ModelLOD" with
    0xDB960C and count 4. It pairs AnimationLOD with 0xDB961C/5, EffectsLOD 0xDB9630/5, ShadowLOD
    0xDB9660/5, TerrainLOD 0xDB9674/3, WaterLOD 0xDB9650/4, TextureQualityLOD 0xDB9680/3, ShaderLOD
    0xDB968C/4 and DecalLOD 0xDB9644/3.
  - The arrays are consecutive in GameLOD.cpp's .data. The last is CPUNames (0x9B96B8), whose null
    ends every parseIndexList scan.
  - No export, string, typeinfo or donor names the array, so a name needs the name lane's two blind
    agents.
  - GameLOD.cpp's `g_00DB960C[48]` (and g_00DB961C/9630/9644/9650/9660/968C) overlap each other. No
    data row can cover them: a 192-byte row at 0xDB960C would overlap the CPUNames row.
  - Honest fix: define the 11 short arrays in retail order (4, 5, 5, 3, 4, 5, 3, 3, 4, then
    bfmeStaticLODNames and Low/High) so MSVC lays them out in definition order, as retail does (still to be checked). Then name
    them through the lane and row each one.
  - GameLOD.cpp is held by StarkillerHDX@fleet's claims (2026-11-02 00:30).
  - Maintainer question: may a descriptive inferred name (for example ModelLODNames) land for these
    arrays without blind agreement, given the retail "ModelLOD" key pairing?
- The 14 getters stay blocked:
  - 0xDBD7DC/0xDBD860/0xDBD918 return the file statics `_s_glowEffectActive`/`_s_ringEffectActive`/
    `_s_fireEffectActive` (Drawable_Rva00309fb3/ffd/a040.cpp). A getter can name a static only in
    the static's own TU, and the getter RVAs have no approved TU.
  - 0x00544558 lands inside DX8MeshRendererClass::Init (0x144530, 73 B). It is likely a constant,
    not an address.
  - 0xE032DC is only the provisional `?g_Va00E032DC@@3IA` hatch.
  - 0xDC2884/0xDC2D10/0xDC4B60/0xDC34A4/0xDB4CF0/0xDB4CF8/0xDC2274/0xDC5170/0xC6D690 have no
    data_ledger entry.

Update (2026-11-05, seat halilkkaya-ha-o1, base d86761221d, census index c95fcfcfcd): 130 -> 11.
- s_modelDrawFieldTable (116 literals) is typed. The banked generator
  (reverse/attempt_support/constintgettersaddr-typed-fieldparse-20261101/convert_fp.py) ran against
  the current functions.csv. MinLODRequired's userData binds `g_00DB960C`, GameLOD.cpp's existing
  external definition at that address, which OptionsMenu.cpp's BfmeEnumTable already binds the same
  way. ProjectileBoneFeedbackEnabledSlots binds the rowed TheWeaponSlotTypeNames. No name was added,
  and none was renamed. The table still has no data row, as before: `g_00DB960C` has no ledger home,
  because a 192-byte row would overlap the CPUNames row. A scratch run of data_rows.verify_row with
  that one extra home (g_00DB960C = 0x00DB960C) passes, with 928 B equal to retail and 116
  relocations on target. Without the extra home, only that one relocation fails. The consumer
  W3DModelDrawModuleDataBuildFieldParse.cpp now spells `extern const FieldParse`. The real-name
  route above (11 short LOD arrays, named and rowed) still applies, and once it lands, this table
  can take its data row.
- Rva000A8F58Get/Rva000A8F5EGet return `g_aptHostStateStorage + 0x10` and `+ 0x18`. That is the
  rowed 32-byte Apt host state at 0x00DB4CE0 (AptDisplayStringBase.cpp, data row
  ?g_aptHostStateStorage@@3PAEA). tu_map approves both getters to that TU, so a later
  tu_skeleton merge can move them there.
- Rva000EF29AGet returns `'TEX'`: it was a false positive. 0x00544558 is a class id, not an address.
  The getter is slot 13 (+0x34) of six texture vtables (0x00BCEEF0, 0x00BD25D8, 0x00C03E48, ...).
  Retail 0x00531D99 (BfmeResetTextureRef::operator=) does `call [eax+34h]; cmp eax,544558h`, which
  BfmeResetTextureRefAssign.cpp spells `GetClassId() != 'TEX'`. The bytes are unchanged.
- Still open (11), unchanged:
  - 0xDBD7DC/0xDBD860/0xDBD918: the Drawable glow/ring/fire statics. tu_map approves no TU for
    the getters (re_attempts 0x00309E4B).
  - 0xE032DC: only the address-named hatch g_Va00E032DC (list<UnicodeString>), which this file may
    not add.
  - 0xC6D690: an unnamed LivingWorld FieldParse table whose four userData lists have undecided
    extents (re_attempts 0x0056B7DE).
  - 0xDC2274/0xDC2884/0xDC2D10/0xDC34A4/0xDC4B60/0xDC5170: the BigObf fallbacks' 0x38-byte key
    contexts (BigObfFallbacks.cpp's FallbackCtx). Each sits 0x38 below its g_ObfSlot (slot - 0x38)
    and holds nonzero retail keys. No object defines them, and defining one needs a name: the only
    available spelling is address-derived, which the hatch rules forbid adding.
  - re_attempts.log carries a 2026-11-05 `blocked` row for each of the six BigObf getters and for
    0x00433B18.
