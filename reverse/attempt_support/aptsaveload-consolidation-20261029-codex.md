# AptSaveLoad callback consolidation, 2026-10-29

Base: `33ac7de9d4`. The default claimed picker selected
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp`.
The supported `name_lane.py consolidate --under Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/`
planner and `tu_skeleton.py --merge` dry run preceded the applied merge.
The merger rebuilt TU assignments from current inputs in memory; the committed
map changes only three source columns, not assignments or approval evidence.
The original-path catalogue records `Code/GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptSaveLoad.cpp`.
BFME 1 path agreement is corroboration, not proof of this callback's name or ABI.

## Applied scope

Absorb `AptSaveLoadCallbackRva00434337.cpp` into the existing AptSaveLoad TU.
Repoint 0x00434337 (251 bytes), 0x00787BF2 (8), and 0x00787BFA (10).
The combined TU owns 19 matched rows; source files decrease by one. Existing
placeholder names and class views remain; this is source consolidation, not
new name recovery. The merger performed the composition and ledger repoints.

Preserve the seed's `/D_CRTIMP=` compiler definition. The merger's initial
flag selection omitted it: all rows still matched, but three list allocator
COMDATs changed and `_free` became `__imp__free`. Restoring the existing define
restores all original emitted helpers and bindings. No hatch is added.

## Verification and compatibility audit

Both original sources passed strict preparation before composition. The final
TU passes `./build.sh` and `link_check.py --prepare-current`: 19/19 rows,
11 string literals, and all renumbered funclets verified. `eh_verify.py` is
EXACT 2/2; `find_declared_unmatched.py` is clean. `data_check.py --converged`
checks 11 addresses with no second names and no unjudged rows. An overlapping
preparation invalidated the first data audit; the sequential repeat passes.
`check_csv.py` passes (98,944 function rows).

Saved pre-merge objects compared with the final verified object through
`link_census.object_facts`: the union of all 54 COMDAT byte/relocation
fingerprints, two strong definitions, 47 undefined bindings and one weak alias
is identical. Existing identity verdicts are retained, not declared repaired.
Ordinary link preview against index `85f6b7f40c` (2026-10-29 15:08) retains
1,463 authored bytes: original files 1,205 + 258, destination 1,463.
The affected save-prompt source was freshly prepared together with the final
TU (49/49 rows, 33 literals). The outgoing batch audit remains INCONCLUSIVE:
the index predates the outgoing base, and the affected
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` consumer lacks a
current receipt. Carry the provider and affected consumer scope into the next
scheduled census. No census improvement or consumer-wide closure is claimed.

The complete pending path batch is this one donor absorption. Searches of
active tools, hooks, workflows, Code, docs, root build/configuration consumers
and reverse registers find no active hard-coded donor consumer. Remaining
old-path mentions are the merger's provenance comments and append-only
`name_agreed.csv`, `name_basis.csv`, `name_votes.csv` history. Preserve them.
The merger repoints both active ledgers and refreshes header/MS-header reports;
no queue rows or protected code/data identity keys belong to either input.
No debt keys, baseline entries, pins or hatch counts are retired or increased.
Mixed sources and their queue/debt ownership remain unchanged. Include
resolution and source ownership are covered by the supported merger and
fresh final build; no old compiler receipt stands in for the moved rows.

## Remaining composition prerequisites

Eight approved donors remain unchanged after supported compile rejection:

- `AptSaveLoad_MultiplayerSaveGameDenied.cpp`: missing method/member declarations
  in the composed AptSaveLoad view.
- `AptSaveLoadRva0043448C.cpp`, `AptSaveLoadDeleteFile.cpp`, and
  `AptSaveLoadPromptAddFriend.cpp`: composed AptPlayer loses GetLevelIndex.
- `AptSaveLoad_SetDefaultFileName.cpp`: GameWindow is not declared before a
  lifted prototype.
- `AptSaveLoadOnButtonSave.cpp` and `AptSaveLoadRva00435819.cpp`: GameState
  declaration/include order fails.
- `AptSaveLoadRva00435DE7Dtor.cpp`: GameWindow base and TreeHint view conflicts.

Reconcile each donor's views and verify it in a separate change before retrying
composition. The four mixed files (AptSaveLoadCallbacks, AptSaveLoadRva0043684C,
AptSaveLoadSavePrompt, and WWLib/stlport_tree_erase_00434E94) remain outside this
merge; approved row ownership alone does not permit absorbing their other rows.
