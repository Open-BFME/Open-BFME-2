# ScriptEngine.cpp merge: why no donor joins yet, 2026-11-04

Scope: `tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp`
(49 candidate donors, 404 rows). Dry run before and after this pass: 0 accepted.

Done: `tools/tu_views.py` wrote 11 shared views (commit "Reconcile eleven
ScriptEngine.cpp TU class views"); 9 plans were restored because they did not
compile with their block (XferVersion, Rva002075F3, Rva00207630, Rva0020766D,
Rva002076AA, Rva002076E7Map, Rva00207724, Rva00207761, Rva0020779EMap).

The wall is the canonical classes. `tu_views` refuses to write 14 of them
because they have a registered header: ScriptEngine, XferException,
NoCaseTreeValue4, Player, ScriptList, SidesInfo, ScriptActions, Script,
ObjectTypes, AttackPriorityInfo, GlobalData, LivingWorldLogic and two more
(`build/se_views.log` from `tu_views.py TU --dry-run`). The TU and about 60
ScriptEngine files hold private `class ScriptEngine` copies.

How it fails, measured with the composed text:

- With a donor's spelling of ScriptEngine kept, the merge emits it at the
  donor's position, after the seed's `extern ScriptEngine *TheScriptEngine;`
  (~20 donors fail at that line, C2143), and after the seed's use of
  Rva002075F3 as a base (C2504).
- With the seed's spelling kept, each donor's method is missing (C2039
  getActionTemplate, setSequentialTimer, enableScript, addObjectToCache, ...).
  The canonical header already declares those methods with their RVAs.
- `Code/GameEngine/Include/GameLogic/ScriptEngine.h` leaves +0x10..+0x1A4E0
  opaque, while the TU's view names fields there (m_sequentialScripts +0x10,
  m_breezeInfo +0x17604, m_callingTeam +0x1A110, m_currentPlayer +0x1A130,
  fade state +0x1A138..+0x1A158, m_flagKeys +0x1A264). Adoption needs those
  fields in the canonical header first: a shared-header edit (full gate).
- Other donor-specific walls: ObjectTypesClass.h and Team.h `#error` under the
  TU's BFME_SNAPSHOT_CAPITALIZED_SLOTS (ScriptEngine_sequentialCleanup,
  ScriptEngineExecuteScript, ScriptEngineCheckConditionsForTeamNames);
  FXBoneInfoVectorErase.cpp is an STLport 4.6 unit against the TU's STLport.

Next step: header lane for ScriptEngine (`header_adopt_lane.py`), adding the
TU's proved fields to the canonical header, then adopting it in the TU and its
donors; only after that does the merge have a chance.
