# 0x007EFE48 `??_7Rva004C9DC9Primary@@6B@` (blocked: class fold refused)

Unit: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`
(38/38 rows matched). Four tables are bridged because the unit uses private views.

Target facts (retail):
- 0x007EFE48 (VA 0xBEFE48) is the 19-slot table of canonical `Rva00252B68`
  (`Code/GameEngine/Include/Common/Rva00252B68.h`, `: DrawableModule : Module`).
- 0x00807E54 is the 11-slot DrawableModule table, the local `??_7Rva004C9FBF`.
- 0x0085EE80 `??_7AnimationSoundClientBehavior@@6BRva004C9DC9Primary@@@`: 19 slots =
  [0x4C9F45 ??_G, B3FD0, 0x4C9E19 GetSnapshotName, 0x4CBF58 xfer, 0x4C9EF3
  getModuleNameKey, B3FD0 x4, D43D0 x2, 0x4C9E1F (int,int,int), 0xCA841 (returns +0xC
  iface, null-guarded), D43D0 x4, B3FD0 x2]. We emit 3.
- 0x0085EED0 ModuleData table: 31 slots; we emit 1.
- Dtor 0x4C9DC9 stores 0xC5EE80 and 0xC5EE74 (+0xC), calls the sound-manager remove,
  then stores 0xBEFE48 inline and calls 0x49B47C. So `~Rva00252B68` is inline in
  retail, but the canonical header declares it out-of-line.

Local views to replace: `struct ModuleData` (line ~79; the rows mangle `class`),
`Rva0049B47C`, `Rva004C9DC9Primary`, `Rva004C9E33Iface`, `Rva004C9F61`,
`Rva004C9FBF`, and a local `class Rva00252B68 : Rva004C9FBF` that collides with the
canonical name.

Blocker: the copy-ctor rows `??0Rva004C9FBF@@QAE@ABV0@@Z` (0x4C9FBF, this unit) and
`??0Rva004C9F61@@QAE@ABV0@@Z` (0x4C9F61, V3PolyCopyCtors.cpp) must become DrawableModule
and Module copy ctors. `rename.py class --fold Rva004C9FBF --into DrawableModule`
refuses: "Rva004C9FBF names more than one class". Its dtor row at 0x49B47C installs
0xBBB554, while its copy ctor installs 0xC07E54.

Next: split the 0x49B47C dtor identity off Rva004C9FBF (it is `??1DrawableModule@@MAE@XZ`
in symbols.csv), then fold. Next, adopt `Rva00252B68.h` with overrides for
GetSnapshotName/xfer/getModuleNameKey/vslot11/vslot12, plus an inline
`~Rva00252B68` in the TU. Then add ICF twin rows only where the retail slots fold.
