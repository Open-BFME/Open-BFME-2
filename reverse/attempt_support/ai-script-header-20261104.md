# AI script header debt, 2026-11-04

Inspected revision: `132c321fb8e08b1e2c5414a3cae34048ccacc957`.

Two remaining private AI views in the selected script cohort now use
`Code/GameEngine/Include/GameLogic/AI.h`:

- `ScriptActions_rva003C2166.cpp` also includes the registered `TAiData.h`.
  The existing AI pointer at +0x18 and recruitment radius at TAiData+0x5C
  map to `m_aiData` and `m_maxRecruitDistance`. The target access was already
  documented by the row's recovery; TAiData.h independently documents the
  retail MaxRecruitRadius FieldParse offset. No donor identity is inferred.
- `ScriptConditions.cpp` uses the header's `m_pathfinder` at +0x10 for its
  four path queries. The unrelated TeamEntry `m_10` remains unchanged.

The other 23 selected consumers already include the canonical AI header and
needed only the owning tool's current verdict to retire their stale queue rows.
No header, ledger, pin, source path or verifier changed.

## Verification

- Declared-unmatched check: all 25 selected sources pass before the attempt;
  both edited sources pass after it.
- `./build.sh` on the two edited sources: 150/150 function rows exact, one
  data row exact, 29 funclet rows verified through parent EH data; string,
  float and import reference checks pass.
- `header_adopt_lane.py accept --class AI` on the selected cohort retired
  23 rows, then accepted the two repaired sources and retired two more.
  PASS includes structural/header checks, byte verification and an ordinary
  per-unit link preview preserving census-linked bytes. A previously blocked
  unit may remain blocked; this is no claim that all 25 link or of a new
  census/headline gain. Class-wide closure remains outside this scope.

Owning-tool acceptance results (23 existing adoptions, then two repairs):

```text
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamAttackNamed.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamAttackTeam.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamCaptureNearestUnownedFactionUnit.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamEnterNamed.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamExitAll.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamHunt.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamIdleForFramecount.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_garrison.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BEB01.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF045.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF5FE.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF71E.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF7AC.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF813.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BF903.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C07C1.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C0849.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C1020.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C1F0A.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_teamCommandButtonOnNearest.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_updateTeamSetAttitude.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineEvaluateAndProgressAllSequentialScripts.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C2166.cpp
  PASS Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
```
