### LINK-666: oldname dllimports bind imports msvcr71 lacks, so no image loads
Status: Repair landed / awaiting verification (two units). Updated: 2026-11-13 (seat halilkkaya-bt2); inspected revision:
`c737388172f`.

Evidence / affected units:
- `Code/GameEngine/Source/GameNetwork/GameSpy/peer/peerOperationsListGroupRooms.c` (`_piConnectConnectCallback`
  0x006A00D0) called `strcmpi`, and `Code/Libraries/Source/assetmanager/Rva00622290CollectKeys.cpp`
  (`?LoadAsset@AssetManagerImpl@@QAEXPAVRva009EF0D0Element@@@Z` 0x00623600) called `strnicmp` twice. VC 7.1's
  `string.h` declares these compatibility names `_CRTIMP`, so under `/MD` the objects referenced `__imp__strcmpi`
  and `__imp__strnicmp`.
- Target facts: retail's calls at 0x006A0121, 0x0062370A and 0x0062371F are `call [IAT]` through
  `msvcr71.dll!_strcmpi` and `msvcr71.dll!_strnicmp`. Retail imports no `strcmpi` or `strnicmp`. `msvcr71.dll`
  (the copy shipped with the game) exports `_strcmpi` and `_strnicmp` but not `strcmpi` or `strnicmp`. VC 7.1's
  `msvcrt.lib` has import members only for `__strcmpi` and `__strnicmp` (`__imp___strcmpi`, `__imp___strnicmp`), so
  the toolchain itself never resolves the oldname dllimport spellings.
- Why the bytes still matched: a `call [m32]` is the same bytes whichever import symbol its DIR32 names, and the
  import-ref check accepts either spelling of the same retail slot.
- Why the exit link still produced an image: `link_cycle.import_def_entries` looks `__imp__strcmpi`'s rest
  (`_strcmpi`) up in retail's import table, finds msvcr71's `_strcmpi`, then writes the entry without the leading
  underscore (`strcmpi`) into the generated `imp_msvcr71.def`. The `rest in retail_imports` shortcut exists for
  mss32's decorated `_AIL_x@N` exports; for msvcr71 it yields an import by a name the DLL does not have. The CI
  diagnostic image at `89957033708` imports `msvcr71.dll!strcmpi` and `!strnicmp` (pefile over its import table:
  218 msvcr71 names against retail's 215; the other extra, `strcpy`, is exported), and the Windows loader refuses
  any image with an import its DLL lacks (`STATUS_ENTRYPOINT_NOT_FOUND`, 0xC0000139) before the first instruction
  of the game runs. Inference, not measured: Wine binds an import its DLL lacks to a stub that fails only when
  called, and neither call runs during a boot (the GameSpy connect callback is online-only; LoadAsset's two calls sit
  in a debug-report branch), which would explain why srv1's images boot.
- Scope check over every kept object at `c737388172f` (the exit link's own `import_def_entries` on the current
  `build/match` population, each generated entry checked against the DLL's export table): only these two msvcr71
  names fail. The mss32 entries are undecorated later by `undecorate_stdcall_imports` and appear in retail's
  table as imported.

Completed: "Call retail's _strcmpi and _strnicmp imports, not the oldname dllimports" (this commit). Each call now
names the function retail imports. Bytes identical in both objects (165 and 2,780 bytes), one/two relocations per
row now name `__imp___strcmpi` / `__imp___strnicmp`; `./build.sh` of each file 23/23 and 14/14 exact; `link_check`
LINKS, 3,670 -> 3,670 and 3,183 -> 3,183 bytes. After the change the same scope check finds no msvcr71 entry the
DLL does not export.

Remaining / next check: the next real-link and diagnostic image should import only names their DLLs export (compare
the image's import table with each DLL's export table). Tooling lead (tools/ not edited): `import_def_entries`
should take the `rest in retail_imports` shortcut only for `link_cycle.DECORATED_EXPORT_DLLS`, so a future
oldname dllimport is reported as a missing import (unresolved in the real link) instead of an import the DLL
lacks. A scratch replay of that rule over `__imp__strcmpi`, `__imp___strcmpi`, `__imp__strnicmp`,
`__imp__AIL_startup@0`, `__imp__GetVersion@0`, `__imp__ntohl@4` and `__imp__strcpy` keeps every entry the current
rule makes except `strcmpi` and `strnicmp`, which become missing (`strcpy` stays with `msvcrt.lib` either way).

Clearance: pending the next image built from a revision with this commit.
Census confirmation: not claimed (the census links under `/FORCE` and never loads an image).
