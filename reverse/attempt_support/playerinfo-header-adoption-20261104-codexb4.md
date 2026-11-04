# PlayerInfo header adoption, 2026-11-04 (codexb4)

Inspected source revision: `58e50cfbe4c4d90fe3504d400243bf8dc8bece80`.
Published census index: `3a95b274a2`, 2026-11-04 22:40 UTC, fetched with `link_check.py --fetch-index`.
Index SHA-256: `794a70c21bcb5471b1e2a811d380f9e4029f5c06432f7bec2dfe1c240d126256`.
Unchanged canonical header SHA-256: `1c90606f90a698bf1165590fa9a1c987f813451390936920670985dc31c410be`.

## Retained changes

Eight private definitions now include the existing canonical `PlayerInfo.h`. Only accesses to the replaced PlayerInfo fields were updated; unrelated classes retain their own field spellings. No source paths, ledger identities, headers, pins or aliases change.

| Source | Matched rows |
| --- | ---: |
| `Code/GameEngine/Source/Common/System/ArchiveDirInfoO1Copy3.cpp` | 1 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp` | 39 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchPlayerTooltip.cpp` | 18 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005D5F86ChatPlayerTooltip.cpp` | 14 |
| `Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoCtor.cpp` | 19 |
| `Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameOptions.cpp` | 18 |
| `Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp` | 81 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp` | 75 |

Total retained scope: 265 matched rows.

## Verification

- `find_declared_unmatched.py` passes before and after every retained edit.
- `./build.sh` passed the initial six-file cohort (128/128) and four-file cohort (193/193). After restoring both refused adoptions, all ten files passed again (321/321), including EH/funclets, string/float/import references and the existing STLport constructor fold. The retained eight files own 265 of those rows.
- `header_adopt_lane.py accept --class PlayerInfo` retired exactly eight rows from `reverse/header_queue.tsv`. After restoring the two refused files and rebuilding them, acceptance was rerun on the final eight files and passed for each.
- `check_csv.py` passes: 99,452 functions, 9,328 symbols, 2,268 data rows. `git diff --check` passes.
- The combined trial preview below preserves all eight retained units (22,397 census-linked bytes). The final-state acceptance confirms preservation after the two refused trials were restored. These are local preview results; no new census measurement or linked-byte increase is claimed.

Final eight-file acceptance output:

```text
PASS Code/GameEngine/Source/Common/System/ArchiveDirInfoO1Copy3.cpp
  PASS Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp
  PASS Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchPlayerTooltip.cpp
  PASS Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005D5F86ChatPlayerTooltip.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoCtor.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameOptions.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
  PASS Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp
```

## Refused trials and next step

`AptMessengerOnlineResponse.cpp` (20 rows) and `AptOnlineQuickMatchOptions_OnMatched.cpp` (36 rows) byte-matched after manual adoption but lost 2,359 and 3,106 census-linked bytes respectively in the ordinary combined preview: both need `??1PlayerInfo@@QAE@XZ`. Both source edits were restored; both header-debt rows remain. Their originals were rebuilt successfully. The two blocked verdicts were recorded through `re_log.py`.

Target/provider facts: the canonical header describes the 0x34-byte record and identifies destructor RVA 0x001EF50E. The existing 68-byte body is owned by `??1Rva001EF50E@@QAE@XZ` in `Code/GameEngine/Source/Common/RvaAsciiStringTripleDtors.cpp`. `reverse/symbols.csv` binds the PlayerInfo destructor name to that RVA for byte resolution, but that pin does not emit a COFF definition. The fresh-index preview reports the real destructor name unresolved. No lost body, missing coverage or new code recovery is claimed.

Next useful work: claim the existing destructor owner, inspect its current header/debt/provider consumers and naming evidence, then recover its real class/linker identity through the normal naming workflow. Verify existing rows and affected consumers before retrying either refused adoption. Do not introduce another alias or body.

The other seven selected queue entries were unchanged. Their automated preparation diagnostics concern partial/array layouts, field collisions or include-input parsing; no manual reconstruction was retained for them. This batch does not clear PlayerInfo adoption class-wide.

## Ten-file trial preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/System/ArchiveDirInfoO1Copy3.cpp: LINKS  LINKED 61 -> 61 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 61)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMessengerOnlineResponse.cpp: does not link  LINKED 2,359 -> 0 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 2,359)
  unresolved  ??1PlayerInfo@@QAE@XZ
  diagnostic  ?getCharAt@AsciiString@@QBEDH@Z  (codegen-like: 22 bytes against the majority copy's 5; unreferenced, not a blocker)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp: LINKS  LINKED 2,864 -> 2,864 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 2,864)
  diagnostic  ?deallocate@?$allocator@PAVMapMetaData@@@_STL@@QBEXPAPAVMapMetaData@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAPAVMapMetaData@@PAV1@V?$allocator@PAVMapMetaData@@@_STL@@@_STL@@QAEXPAPAVMapMetaData@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ??1?$_Vector_base@PAVMapMetaData@@V?$allocator@PAVMapMetaData@@@_STL@@@_STL@@QAE@XZ  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatchOptions_OnMatched.cpp: does not link  LINKED 3,106 -> 0 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 3,106)
  unresolved  ??1PlayerInfo@@QAE@XZ
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchPlayerTooltip.cpp: LINKS  LINKED 1,335 -> 1,335 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 1,335)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005D5F86ChatPlayerTooltip.cpp: LINKS  LINKED 871 -> 871 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 871)
Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoCtor.cpp: LINKS  LINKED 287 -> 287 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 287)
  diagnostic  ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VDetailedArchivedDirectoryInfo@@@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VDetailedArchivedDirectoryInfo@@@_STL@@@2@IPBX@Z  (codegen-like: 28 bytes against the majority copy's 33; unreferenced, not a blocker)
Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameOptions.cpp: LINKS  LINKED 1,663 -> 1,663 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 1,663)
Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp: LINKS  LINKED 6,143 -> 6,143 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 6,143)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp: LINKS  LINKED 9,173 -> 9,173 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 9,173)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAGGV?$allocator@G@_STL@@@_STL@@QAEXPAGI@Z  (codegen-like: 20 bytes against the majority copy's 18; unreferenced, not a blocker)
link_check: 8 of 10 link cleanly; LINKED 27,862 -> 22,397 bytes (32.5s)
```
