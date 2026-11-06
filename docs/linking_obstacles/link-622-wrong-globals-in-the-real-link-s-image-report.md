### LINK-622: Wrong globals in the real link's image report

Status: Open. Updated: 2026-11-07 (seat halilkkaya-lk42); inspected: `image_report.json` of real link `1d41894d2a`
(2026-11-06 20:05 UTC), tree at `88ce76fc444`.

Evidence / affected units: the `globals` section of `tools/image_report.py` over the kept objects. Every address below is
a retail RVA unless marked VA; retail bytes are `game.dat`'s.

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

Remaining / next check: regenerate `reverse/data_ledger.csv` (a separate decision; LINK-619 measured the same staleness)
and re-read this counter; most of the 183 should then name their current owners.

Clearance: pending. Census confirmation: not claimed.
