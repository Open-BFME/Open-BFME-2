### LINK-623: Wrong globals in the real link's image report

Status: Open. Updated: 2026-11-07 (seat halilkkaya-lk42); inspected: `image_report.json` of real link `1d41894d2a`
(2026-11-06 20:05 UTC), tree at `88ce76fc444`.

Numbered LINK-622 in this seat's first commits (`911b7e9cef7` .. `47f1c3c62ff`); origin took that ID first for
another entry, so this one is LINK-623.

Evidence / affected units: the `globals` section of `tools/image_report.py` over the kept objects. Every address below is
a retail RVA unless marked VA; retail bytes are `game.dat`'s.

#### The nine named rows

- `contents_differ`, both report artifacts, no image defect. `_vtbl_00C5D608` (`ElvenWoodSpecialPower.cpp`): retail's
  table is 31 code pointers, then the float -99999.9 (`f3 4f c3 c7`) and "BurnRate". Ours has the same 31 slots, then 4
  bytes of 8-byte alignment padding before the next hand-built array, `_vtbl_00C5D468`. The ledger records the address as
  kind `global` with a 248-byte gap, so the report compares 128 bytes instead of the vtable's length. `_Rva012C4C24`
  (`Y4CommTickIdle.c`): the 57-byte format string is equal; retail's next string, "SRP", starts at +60, while ours pads
  to +64. The lasting fix for the first is the class's real vtable (ModuleData.h already declares its 31 slots), header
  lane work.
- `ours_zero_retail_not`, **repaired**: `g_Va00DD828C`, `g_Va00DD8314` and `g_Va00DD83B4` (`Rva007B6880Thunks.cpp`) are
  objects of vptr-only classes (`Rva006655B0`, `Rva006680E0`, `Rva00669510`). MSVC folded the inline constructor into
  the static data, so retail's `.data` holds the table address at load and the initializer only registers the destructor
  stub (0x007B9B90 and its siblings, the only other writers). Ours were zero, so the getters in `ConstIntGetters.cpp`
  (0x006655E0 and its siblings) returned objects with a null vptr. Each now holds the address of its table (the existing
  `_vtbl_00CE3168`-style names) as static data; compared with retail: equal.
- `constructed_undersized`: `g_Va00E06634` (16 bytes) and `g_Va00E02FF8` (20 bytes) **repaired**, recorded in
  `globals-constructed-into-storage-smaller-than-retail-2026-11-04.md`. `g_Va00DFF0C4` and `g_00E02EAC` are false alarms,
  re-read against retail: `UnicodeString`'s constructor 0x00326BE6 writes only +0 (`8b c1 83 20 00 c3`), and `Region2D`'s
  0x00004C06 writes +0..+0xC; the gaps of 12 and 20 are padding or unreferenced neighbours.

#### No object defines it, and retail's data is not zero (483)

The counter counts ledger rows of kind `global` for which no kept object defines any of the row's names as an external
data symbol, and whose retail bytes are not all zero. Read against the kept objects at `88ce76fc444` (the same 17,967
objects; the count reproduces at 483):

| Class | Rows | What it means |
|---|---:|---|
| Defined as a TU-local static | 296 | The object holds the data under a static symbol (`_MIN_OMEGA`, `__Stl_tenpow`, `_default_dayname`, ...). `scan_objects` reads external symbols only, so it neither finds them nor compares their bytes. Present in the image, contents unchecked. |
| Neither defined nor referenced | 183 | No kept object names them. The names come from `reverse/data_ledger.csv`, which is stale (a regeneration changes about 27,000 lines). For 118 of them `reverse/data_rows.csv` has a row at the same address under another name, which `data_ledger.load()` prefers but `image_report.py` (reading the CSV itself) does not; the subtitle table below was counted for the same reason. Not an image defect by itself. |
| Referenced, never defined | 4 | Resolved by `/alternatename` or COMMON storage, which the report cannot see. Read one by one, below. |

The four:

- `_vtbl_00BD4688` (`DynamicVectorBfmeHandleCtor.cpp`) and `_vtbl_00C4D5A0` (`ArrowStormUpdateModuleDataCtor.cpp`):
  `/alternatename` to the compiler's `??_7` of the same class. Hatches, but the right table.
- `?Rva0081D7C0FieldParseTable@@3QBUFieldParse@@B` (VA 0x00CE43B0), read by `parseSubtitle` in `SubtitleEntry.cpp`:
  **a wrong global, repaired.** A link-cycle repair (`d36a83efbfa`) aliased it to the string literal `"0"`
  (`??_C@_01GBGANLPD@0?$AA@`), so `INI::initFromINI` read the subtitle fields from the bytes of `"0"` and what follows
  it. Retail's table is five 16-byte entries (FontName, FontPitch, SubTitleType, SubTitle, LineTable) and a null
  terminator, and the tree already defines it byte-verified: the data row `?g_00CE43B0@@3QBUFieldParse@@B` in
  `INIThinFieldParsers2.cpp`. `parseSubtitle` now names that owner and the alias is gone (one `/alternatename` fewer).
  The ledger row lists only the old name, which is why the report counted it.
- `_static_qr2_rec` (0x009DB710, 280 bytes, `GameSpy/qr2/qr2.c`): retail initializes the first word to `INVALID_SOCKET`
  (`ff ff ff ff`, the rest zero); ours was a zero COMMON definition, because the carrier's initializer is commented out.
  **Repaired:** `qr2.c` restores `= {INVALID_SOCKET}` (marked in place and in `GameSpy/PROVENANCE.txt`); the object is
  now 280 bytes of `.data` followed by `current_rec`, as in retail. `qr2.c` did not link before or after (an unrelated
  `qr2_create_socket` COMDAT).

#### TU-local tables the report cannot compare

The 296 static-defined rows (397 against a regenerated ledger with data rows applied) were compared by hand with a
one-off script: each static the ledger keys to its own source (`name@source`), bytes outside relocations against retail's.
Before the repairs below, 251 agreed and 66 differed. Most of the 66 are the dummy-vptr statics LINK-514 already lists (`s_vtable`, `s_secondary*`,
`*VTableAnchor`). The rest are wrong data:

- `ObjectCreationList.cpp`'s three OCL nugget tables were one null entry each (placeholders from the byte-matching phase,
  `f484f94159e`), so every field of every `ObjectCreationList` block in the INI would be an unknown token.
  **Repaired:** retail's 40 common, 17 object and 5 debris entries, with BFME 2's 19 disposition names (0x009B92F8; ours
  had Zero Hour's 9 and no terminator) and BFME 2's 16 shadow names (0x009B9298; the Zero Hour header's list has 7).
  A script compared every token, parser, user-data pointer and offset with retail: all equal.
- **Repaired, the same pattern** (zero, no relocations, where retail has a table): `audioLODFieldParseTable`
  (`INIParseAudioLODDefinition.cpp`, 3 entries at 0x007E34B8), `s_statusBitsTable`
  (`UpgradeModuleDataGetterBuildFieldParse.cpp`, 2 at 0x00857984), `s_chinookFieldTable` (`DetachableRiderBody.cpp`, 3 at
  0x0085BECC; retail's ends with a 4-byte null token where the next table starts, ours with a whole null entry),
  `s_table0050AD97` (`Rva0050AD97BuildFieldParse.cpp`, 4 at 0x00864B60, with that unit's 24-name `TheDeathNames` copy at
  0x009D0FA0) and `s_extraFieldTable` (`FXListDieModuleDataBuildFieldParse.cpp`, 2 at 0x00864C08). Each compared with
  retail by the same script: all equal.
- **Repaired:** `TheBFMEStaticGameLODFieldParseTable` (`GameLOD.cpp`, the table `INI::parseStaticGameLODDefinition`
  passes for the 16-byte element at manager + 0x1c8) held Zero Hour's 19 static-LOD fields with offsets up to +0x2c.
  Retail's table at 0x007E3478 is MinimumFPS, ParticleSkipMask, DebrisSkipMask and SlowDeathScale, and it has no null
  entry: it runs on into the three AudioLOD entries, as `g_007E3308` in the same file already reproduces. Ours now holds
  those seven entries and a null one; the script compares all 128 bytes with retail: equal. The 16-byte element and
  this field set are Zero Hour's dynamic LOD, so the parser's name may be the static one's; not changed here.
- **Repaired:** `StrategicHUD.cpp`'s `s_table` (0x0086F030), which `SetPhaseTitleString` searches for the game-text
  key of a phase, held invented placeholders (`{0,"A"}`, `{1,"B"}`, `{2,"C"}`). Retail's: phases 0, 2 and 4 with
  `APT:TacticalPhaseTitle`, `APT:BattlePhaseTitle` and `APT:RetreatPhaseTitle`. Compared with retail: equal.
- **Repaired:** the glow, ring and fire effect statics (`Drawable_Rva00309fb3.cpp`, `Drawable_Rva00309ffd.cpp`,
  `Drawable_Rva0030a040.cpp`), which their INI blocks start from, were zero; retail's `.data` holds defaults
  (GlowDiameter 17, GlowTextureWidth 256, Scale 4.0, Blend 0.7, colors 1.0, TextureRepeatCount 5.0, ...). They now
  start from retail's bytes; compared with retail: equal. Retail's ring and fire statics differ from what the matched
  initializer `RingEffect::rva00309E85` writes (its first and third `m_unknown28` triples are zero), so the statics
  are written from the image, not from that function.
- **Repaired, initial values:** `AXIS_ROTATION` (`camerashakesystem_shaker.cpp`, 0x009B4068) is 80 degrees about each
  axis in BFME 2, not Zero Hour's 7.5/15/5; `animationDisableOverride` (`W3DGhostObjectScene.cpp`, 0x009B4014) carries
  the id 0x01234567 the renderer checks, as `W3DTankDraw.cpp`'s layout has it (ours was 16 zero bytes);
  `detailAlphaShader` (`W3DBibBuffer.cpp`, 0x009B5370) is 0x000198B7, Zero Hour's SC_ALPHA_DETAIL with primary
  gradient 6 instead of GRADIENT_MODULATE; and `g_Rva012C3BC4` (`Y4FeslBuddyRequests.cpp`, 0x009D831C), the PROT
  value of the FESL CONN request, points at `"2"` (ours was null). Each compared with retail: equal.

A second pass checked every relocation in those statics against retail's word (code by ledger RVA, literals by
content, data by ledger address): 1,454 agree, 89 have targets the ledgers do not place, and 7 disagree.

- **Repaired:** `AptTimeLine.cpp`'s `s_statusQueries` (0x008671A0) listed the six `TimeLine:` extern-handler names in
  reverse. The registration loop passes the index as the query id, so every query was bound to another query's
  answer. Retail's order starts with ScreenMode; compared with retail: equal.
- Open, STLport (left to that lane): `_Null_messages` in `stlport_classic_locale.cpp` (0x009DEB24) holds a vptr where
  retail's load-time word is 0.
- Harmless: `BoredUpdate.cpp`'s `s_boredUpdateFile` and `StealthDetectorUpdateCtor.cpp`'s `s_file` are the file names
  passed to `GetGameLogicRandomValue`'s debug arguments; retail's are full `C:\projects\bfme2patch103\...` paths.

#### One address, several names (23)

Two definitions for one retail datum link as two objects: one side writes, the other reads its own copy. Read
against retail and the readers:

- 0x00A1835C: **repaired.** `Rva006FB960Cluster.cpp` defined `g_bfmeFrameStackAtE1835C = 0` for the Apt frame stack
  that `AptScriptFunction.cpp` defines as `AptScriptFunctionBase::spFrameStack` and the interpreter sets. Retail's
  `Rva006FBE80::find2` (0x006FBE80, `8b 35 5c 83 e1 00`) reads that one pointer, so ours always took the scope fallback
  and never saw a script frame's variables. It now declares the owner as `Rva006FBED0Cluster.cpp` does.
- 0x009E1F24: **repaired.** `W3DShaderManager.cpp` defined both `W3DShaders[2]`, which init (0x000F5B43) fills, and
  `g_00DE1F24[1]`, which only `setShader` (0x00075655) read. Retail's `setShader` indexes 0x00DE1F24, so ours never
  reached a shader's `set` and always returned 0. It now reads `W3DShaders` through the same volatile view.
- 0x00A0312C: **repaired.** `AIGameTeam.cpp` defined `ArmorStore *g_00E0312C = 0` and `AIGameTeam::addPlayer`
  (0x004E9823, `8b 0d 2c 31 e0 00`) called through it, while `GameEngine::init` stores the subsystem it creates in
  `TheArmyDefinitionManager` (`ArmyDefinitionManager.cpp`). Ours called the armor lookup on a null receiver for every AI
  player a skirmish adds. It now reads `TheArmyDefinitionManager`, as `SkirmishAIManager.cpp` does.

Leads read but not changed here (this counter now belongs to the duplicates lane):

- 0x009EBE0C and 0x009EBE24: `Rva000F1A32Ctor.cpp` defines both as `DynamicVectorClass<TCBSpline3DClass::TCBClass>`
  objects with their own compiler initializers, read by the shadow code (`W3DShadowGeometryMesh.cpp`,
  `W3DVolumetricShadow.cpp`), while `Rva007ABEF3ArgCtorInits.cpp` defines `g_Va00DEBE0C`/`g_Va00DEBE24` as 4-byte
  `unsigned` and retail's initializers there construct a 24-byte `DynamicVectorClass` into each (the regex behind
  `constructed_undersized` misses the `KeyVector::DynamicVectorClass` spelling). Their atexit thunks are in
  `Rva007B6880Thunks.cpp`. One object per address needs those three units to agree on one name and one 24-byte storage.
- 0x00A032E8: `GameLogic.cpp` defines `UnicodeString g_Va00E032E8` and writes it; `Rva007ABBB3CtorInits.cpp` defines
  the `unsigned` of the same name that `AptSaveLoadCallbacks.cpp` reads and retail's 0x007B0625 constructs.
- 0x009B5F88: `ConstGlobalGetters2.cpp`'s `G00DB5F88 = 1` (read by `meshmdlio.cpp`, written by `GapBodiesGE25.cpp`) is
  `WW3D::PrelitMode` (`ww3d.cpp`, also 1, set by `W3DDisplayInit.cpp`).
- 0x009FE490: the atexit thunk in `Rva007B6A00AtexitThunks.cpp` clears `g_Va00DFE490` (a data row) instead of
  `ArmySummaryDescription.cpp`'s `g_00DFE490`; exit only.

Remaining / next check: regenerate `reverse/data_ledger.csv` (a separate decision; LINK-619 measured the same staleness)
and re-read the 483; against a regeneration with data rows applied, every one is a TU-local static, an `/alternatename`
or the CRT's `___xc_a`. `image_report.py` could compare TU-local statics (the ledger keys them `name@source`) and read
`data_ledger.load()` instead of the CSV; this pass's comparisons were one-off scripts. The open rows of
`globals-constructed-into-storage-smaller-than-retail-2026-11-04.md` (`g_Va00E06634`'s +8 and +0xC, the second
`g_00E02FF8`) need real names first.

Clearance: pending. Census confirmation: not claimed.
