# Rva0020453CHolderBase vtable bridge (0x007E39F4): handoff

Queue item: vtable-bridge `??_7Rva0020453CHolderBase@@6B@` at 0x007E39F4 (13 slots).
Three units emit the table under three names: `Rva0020453CHolderBase`
(ScriptEngine.cpp), `Rva0020453CHolder` (ScriptEngine_dtor.cpp) and
`Rva00203EFD` (GameClient/System/Rva00204316.cpp).

## Target facts (game.dat 1.06)

- Ctor 0x00203EFD (`??0Rva00203EFD@@QAE@XZ`): `and [eax+4],0; mov [eax],0xBE39F4;
  mov byte [eax+8],0`. Dtor 0x00204C16 (`??1Rva0020453CHolderBase@@QAE@XZ`):
  `mov [ecx],0xBE39F4; jmp 0x0060453C` (release). Both install the same table,
  so `Rva00203EFD` and `Rva0020453CHolderBase` are one class. It has no
  deleting-dtor slot, and the dtor is non-virtual.
- Slots and their current rows:

| slot | target | row |
|---|---|---|
| 0 | 0x204316 | `?rva00204316@Rva00204316@@QAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z` |
| 1 | 0x204386 | `?Rva00204386Get@@YGPAVParticleSystemTemplate@@PBD@Z` (free, stdcall) |
| 2 | 0x204C21 | `?rva00204C21@Rva00204C21@@QAEXPBD@Z` |
| 3 | 0x206DA4 | `?Rva00206DA4Enumerate@@YGXPAVRva002082F1Visitor@@@Z` (free, stdcall) |
| 4 | 0x2082F1 | `?Rva002082F1Enumerate@@YGXPAVRva002082F1Visitor@@@Z` (free, stdcall) |
| 5 | 0x203665 | `?rva00203665@Rva00203665@@QAEHXZ` |
| 6 | 0x2043F5 | `?Rva002043F5Get@@YGPAVParticleSystemTemplate@@PBD@Z` (free, stdcall) |
| 7 | 0x204C68 | `?rva00204C68@Rva0020453CHolderBase@@QAEXXZ` (non-virtual) |
| 8 | 0x20443D | `?rva0020443D@Rva0020453CHolderBase@@UAEXPBD@Z` |
| 9 | 0x2044C7 | `?rva002044C7@Rva0020453CHolderBase@@UAEXPBDABV...@Z` |
| 10 | 0x20CEC7 | `?_writeOutINI@@YAXXZ` (free, cdecl) |
| 11 | 0x203671 | `?rva00203671@Rva00203671@@QAEXH@Z` |
| 12 | 0x204C78 | `?rva00204C78@Rva00204C78@@QAEXPBD@Z` |

## Inference (not proven)

The slot bodies match ZH's free particle-editor callbacks in ScriptEngine.cpp
(`_writeOutINI`, `_appendAllParticleSystems`, `_getNewCurrentParticleSystem`,
...). In ZH these are function pointers handed to the DebugWindow DLL;
ScriptEngine_dtor.cpp calls the holder `TheDebugWindowHolder`. BFME2 seems to
have made them virtual members of one interface implementation. The free-stdcall
rows match because those bodies never read `this`.

## Why it is not landed

- `rename.py class --fold Rva00203EFD --into Rva0020453CHolderBase` refuses: the
  table is also named for `Rva0020453CHolder`, a third name.
- `class --fold Rva0020453CHolder --into Rva0020453CHolderBase` refuses: the
  class has no ctor/dtor rows, because it is a codegen-only derived view that
  keeps ~ScriptEngine's delete inline.
- Slots 1, 3, 4, 6 and 10 are free-function rows. `function --to-class` moves
  only placeholder-class members, and free placeholders only as
  `GetSnapshotName`. `_writeOutINI` is a real ZH name. No tool path makes them
  virtual members, so the table keeps unresolved slots and stays bridged.

## Next step

1. Drop the `Rva0020453CHolder` view in ScriptEngine_dtor.cpp, keeping its
   bytes, so the table has two names. Then fold `Rva00203EFD` into the holder
   class.
2. Use `function --to-class` with `--also` to move slots 0, 2, 5, 11 and 12,
   keeping their placeholder identifiers, plus `--virtual` for slot 7.
3. A tooling seat adds a free-function-to-virtual-member move for the stdcall
   and cdecl slot rows. Real names come from the name lane.
