# Mixed-file splits, dd-26 pass (2026-10-29/30)

Scope: priority 1 of `build/fleet/merge_map/REPORT.md` — carve rows out of mixed
files into their `tu_map`-approved TU, one mixed file per item. Selection came
from `merge_map.csv` (measured at `95c5a79`), filtered against `claims.py list`
and the current tree, then screened with
`python3 tools/tu_skeleton.py --split FILE --for TU --dry-run`.

## Landed

- `HealCrateCollideExecute.cpp` -> `ShroudCrateCollide.cpp`: carved `0x004BCB26`
  (3 rows), residual keeps 3, both sides `6/6` byte-verified, `link_guard: split`
  clean, `find_declared_unmatched` clean. Commit "Split 3 rows of
  HealCrateCollideExecute.cpp into ShroudCrateCollide.cpp".

## Near misses (rows verified; blocked at the merge verifier)

### 1. `StateCtor.cpp` -> `StateMachine.cpp` (5 rows, residual keeps 1)

`5/5 carved rows match beside the TU under its flags`. Two blockers, in order:

- **C2511 `State::State(StateMachine *,unsigned int)` : overloaded member
  function not found in 'State'.** The TU's own `class State` has no such ctor;
  the donor's class definition is dropped as a redefinition. Reconciling the
  donor view to the TU view fixes it: declare
  `State(StateMachine *machine, unsigned int hash);` in the TU's class and spell
  the donor's `+0x10`/`+0x14` members as the TU's
  `const StateConditionInfo *m_transitionsFirst; int m_transitionsCount;`.
  `./build.sh StateCtor.cpp StateMachine.cpp` then reports
  `Functions: OK 17/17 matched across 2 source file(s)` and the carve re-verifies
  5/5 rows alone.
- **Link guard, still blocking:** `moved selected COMDAT
  ??0Rva004D7476@@QAE@PAVStateMachine@@@Z lacks matching private/weak-free
  context` (and `??0Rva004D74C7`). The derived `State` ctors move with their
  vtables while the residual keeps the base `State` row. The reconciliation was
  reverted; no source change landed.

### 2. `Rva00404781Method.cpp` -> `VictorySystem.cpp` (1 row, residual keeps 3)

`1/1 carved rows match beside the TU`. Merge compile: `error C2065: 'm_a' :
undeclared identifier` (and `m_b`). `class Rva00404781` is used by the carved
row `0x00404CF5` **and** by the residual rows `0x00404781`/`0x0040475C`, so the
class stays in the residual and the destination TU (which has no such class)
gets a body whose type is not there. The carry rules cover helpers, file-scope
objects and externs, not a type shared by both sides.

### 3. `DynamicPortalBehaviourSlots.cpp` -> `DynamicPortalBehaviour.cpp` (4 rows, residual keeps 1)

`4/4 carved rows match beside the TU`. Merge compile: `error C2653:
'DynamicPortalBehaviour' : is not a class or namespace name` — the same
shared-type shape: the donor's private `class DynamicPortalBehaviour : public
UpgradeModule` is dropped as a redefinition of the TU's class, leaving the moved
member definitions classless.

### 4. `TransitionStyleSlotsBfme2.cpp` -> `GameWindowTransitionsStyles.cpp` (8 rows, residual keeps 3)

`8/8 carved rows match beside the TU`. Merge compile: `error C2084: function
'Color GameMakeColor(UnsignedByte,UnsignedByte,UnsignedByte,UnsignedByte)'
already has a body` — the carve copies the four GUI helpers
(`GameMakeColor`, `drawFillRect`, `drawOpenRect`, `drawImage`) into a TU that
already defines them. The copy rule needs to prefer the destination's existing
definition when the signatures agree.

## Stale merge map

The map's `mixed` column is a 2026-10-29 `95c5a79` snapshot. Eleven of the
carves below returned `blocked: no row of that file is approved for that TU`,
i.e. the row has since been repointed: `MpGameSetupSlots.cpp`,
`AptMpGameSetupRefreshMapList.cpp`, `ObjectTypesCtor.cpp`,
`Rva0041AD08Read.cpp`, `AptSaveLoadSavePrompt.cpp`, `Rva00136794Dtor.cpp`,
`PathfinderPosGoalManager.cpp`, `Rva00785140HandleDestructor.cpp`,
`Rva0057A2B0Dtor.cpp`, `ConnectionManager_processAck.cpp`,
`Rva0059FC9FFind.cpp`. Re-derive ownership with `tu_skeleton.py --split FILE`
before spending a dry run.

## Refusal tally over ~60 dry runs

| class | n | representative |
|---|---|---|
| residual loses matched rows | 15 | `BfmeApplyTextureRef_Apply.cpp` -> texture.cpp (0x00075412); `AIClosestEnemySearch.cpp`, `AIAreaEnemySearch.cpp`, `AIClosestObjectQueries.cpp` and `LargeGroupBonusUpdateUpdate.cpp` (all 0x0049C38A); `Rva005CBB0AWrap.cpp` (0x002BEF29); `Create_Render_Obj.cpp` (0x0017098D); `Rva00112259.cpp` (0x00042F8C); `Rva0035A9C1Dtor.cpp` (0x0007FAB3); `AttributeModifierPoolUpdateXfer.cpp` (0x0029D7C2); `DynamicPortalBehaviourCreateWaypoints.cpp` (0x0021983A); `ScriptConditions_evaluateNamedUnit.cpp` (0x0006DFF1); `GameLODApplyPreset.cpp` and `W3DTerrainBackgroundDoPartialUpdate.cpp` (0x00042F8C / 0x000ABD19) |
| no row approved for that TU (stale map) | 11 | see above |
| `namespace`/`extern "C"` block defines something | 6 | `fxshadersetup.cpp` -> FXShaderSetup.cpp (14 rows); `partitionmanager_impl.cpp` -> PartitionManagerImpl.cpp (8 rows); `parseSpellIndex_Thunk.cpp` -> AptSpellStore.cpp (12 rows); `Rva00404D70Init.cpp` -> VictorySystem.cpp; `FormationBuildRow.cpp` -> LightSubPoint.cpp; `MultiplayerColorMapOperator.cpp` -> MultiplayerSettings.cpp |
| `hatch_counters` rule 3 | 6 | `BfmeConv937.cpp` -> texture.cpp (the `/alternatename` pragma is kept by both sides); `Rva00515Wrappers.cpp` -> AptMainMenu.cpp (`g_Va00DD1538`); `GlobalFlagClearers_E033xx.cpp` -> AptMpGameSetup.cpp (`g_Va00E03350`); `FamilyTailDtors1DBAC3.cpp` -> GameWindowTransitionsStyles.cpp (`TheMappedImageCollection`); `Rva005173F8Dtor.cpp` and `Rva005BA593Dtor.cpp` -> AptOnline/AptOnlineQuickMatch |
| no definition spells its name | 5 | `MultiplayerColorTreeDtor.cpp`, `FamilyVectorDtors_CodexSep26.cpp`, `FlightDeckInfoVectorInsertOverflow.cpp`, `DynamicPortalBehaviourModuleDataDtor.cpp` (sweep-emitted deleting dtors) |
| merge compile (donor view / helper copy) | 4 | items 2-4 above and `StateCtor`'s first rejection |
| link guard (moved COMDAT) | 1 | item 1 |
| `flag_bound` | 1 | `AptMainMenuUpdate.cpp` -> AptMainMenu.cpp: `0x00515C64` and `0x007952FA` match only under the file's own flags |
| TU holds unplaced rows | 1 | `Rva00729300BitPlanes.cpp` -> W3DTerrainBackground.cpp (3 unplaced rows in the TU path) |

## Operational notes for the next seat

- In a sandbox, `--split` must run with `--no-claim`: the tool's own claim push
  fails there (no credentials) and it reports every key as
  `held by another worker`. Claim on the PC first, then `--no-claim` in the
  sandbox.
- Claim the *funclets* too (`__ehhandler$...`, `Unwind@...` rows of the donor),
  not just the body rows: the tool wants every moved RVA.
- New-TU carves (the TU path does not exist yet) are the highest-yield shape
  left: no seed reconciliation. `ShroudCrateCollide.cpp` landed that way; the
  other new-TU candidates were refused for their own reasons or held by other
  seats (`LANGameInfo.cpp` dd-27, `ModelConditionSoundSelectorClientBehavior.cpp`
  dd-28).
- `./build.sh` and `find_declared_unmatched.py` on both sides are quick; the
  expensive part is the tool's own dry run (2-15 min per candidate).

## What to do next on this lane

- Fix the helper-copy rule (item 4) and the shared-type rule (items 2 and 3):
  each is one tool change in `tools/tu_skeleton.py`'s carry analysis and makes
  several carves land at once.
- Item 1 needs a link-guard decision, not a source fix: the reconciliation is
  proven (build 17/17, 5/5 rows) and is one edit away if the guard can accept
  moving the vtables with their ctors.
- Skip sweep files that emit bodies from macros (`Family*Dtors*`,
  `Opaque*Dtors*`, `Vslot*`, `Disp*`): their rows have no spelling definition,
  and the residual usually loses a flag-bound row.
