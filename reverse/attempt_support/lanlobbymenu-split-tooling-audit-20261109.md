# Tooling compatibility audit: GameModePreferences.cpp split, 2026-11-09

Run once over the complete outgoing batch before pushing, per AGENTS.md
("Publication") and `docs/consolidation.md` ("Tooling compatibility audit before
pushing").

## Audited range

`origin/master..HEAD` after fetching:

    Split 6 rows of GameModePreferences.cpp into LanLobbyMenu.cpp

    A  Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu.cpp
    M  Code/GameEngine/Source/Common/GameModePreferences.cpp
    M  Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu_Rva0050CF3C.cpp
    M  docs/doxygen/sources.cfg
    M  reverse/functions.csv
    M  reverse/tu_map.csv

`git diff --name-status --find-renames` reports **one addition and no deletions
or renames**. This is the first split of the lane to create a TU file rather than
move rows between two existing ones: `LanLobbyMenu.cpp` did not exist, and
`--split` composed it (`docs/consolidation.md`, the split lane, step 5: "into the
existing TU file as seed, or as a new TU file"). No path left the tree, so, as
with the `HordeContain.cpp` split, nothing that keys by a deleted donor can go
stale.

Six rows moved: `0x0044D2AC` (`LANPreferences::loadFromIniFile`, `by=S`),
`0x0044D2F5` (`LANPreferences::LANPreferences`, `by=Z`) and the four EH funclets
that ride with them (`0x0078986D`, `0x0078987F`, `0x00789865`, `0x00789877`, all
`by=P` off those two parents).

## Remaining references to the rows' old home, classified

| where | classification |
| --- | --- |
| `reverse/functions.csv`, `reverse/tu_map.csv` | repointed by the split to `LanLobbyMenu.cpp` (6 rows each). Correct. |
| `docs/doxygen/sources.cfg:1260` | the new path, added by the split's own repointing. Correct. |
| `.../Menus/MapSelectMenu_Rva0050CF3C.cpp:17-20` | **updated in this batch.** Its target-fact comment said the map setter, write, user name *and* the LANPreferences ctor were "rowed in GameModePreferences.cpp". Only `0x0044D2F5` moved, so the clause was split rather than redirected wholesale; the other three addresses stay where they were. Comment only, and the file re-verified 1/1. |
| `Code/GameEngine/Include/Common/GameModePreferences.h:7`, `.../GameModePreferencesUserName.cpp:148` | mention `0x0044D2F5` by address with no source path. Unaffected. |
| `reverse/re_attempts.log:38576-38577,72432-72433` | the four landed rows' attempt records, naming the old path. Historical evidence, and AGENTS.md forbids hand-editing this log. Left as written. |
| `reverse/data_xrefs.tsv:10549-10550` | keyed by data address with the referencing code RVAs, no source path. Unaffected. |
| `docs/doxygen/api/w2_string_encoding.dox:36`, `.../LANPreferences_usesSystemMapDir.cpp:8`, `.../AptLanLobby.cpp:1072`, `.../LANChatHistory.cpp:5` | prose naming Zero Hour's `LanLobbyMenu.cpp` as a reference, and a `.wnd` resource string in `Shell.cpp:915`. Donor facts and data, not paths into our tree. Unaffected. |

A search of `tools/`, `.githooks/`, `.github/` and `docs/` for
`GameModePreferences.cpp` returns **no active consumer**, so nothing outside the
ledger and the doxygen list had to be repointed. `tools/tests/fixtures/structural_queue.csv`
names `?LanLobbyMenuUpdate@@...` and `?LanLobbyMenuInit@@...` by symbol and RVA,
not by path, and neither symbol is in this batch.

## Other checks

- `./build.sh LanLobbyMenu.cpp GameModePreferences.cpp`: **57/57 matched** across
  both files, 18 funclet pins verified past renumbered `$L` labels, 26 string
  literals + 13 empty-string refs, 5 named imports.
- `./build.sh MapSelectMenu_Rva0050CF3C.cpp` after the comment edit: 1/1 matched.
- `tools/find_declared_unmatched.py` on both split files: "All defined functions
  are already matched."
- The dry run reported `alone: 6/6 carved rows match beside the TU under its
  flags`, `residual_keeps: 51`, `refused_rows: {}`, `copies: []`, `externs: []`,
  `data_moved: []`, `hatches_move: False`, and the application reused that
  composition (`plan_reused: True`).
- The split's own `link_guard` compared the residual and the destination before
  writing; `link_batch_audit` runs once in the pre-push hook.
- `carried: {}` -- no unit key moved, so no `Verifier-Change:` trailer was
  printed or needed. No baseline line added; no hatch moved.

## Note for the next seat

`GameModePreferences.cpp`'s own TU can now be merged (3 donor files), but as with
`HordeContain.cpp` the merge will refuse until a published census includes this
split: the link guard judges the destination against the last census, which still
expects the old file to define these rows. Publish the split, then take the merge.
