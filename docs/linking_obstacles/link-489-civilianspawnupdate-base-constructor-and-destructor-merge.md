### LINK-489: CivilianSpawnUpdate base constructor and destructor block consolidation
Status: Blocked. Updated: 2026-11-05; inspected revision: fcae9526ac.
Affected: CivilianSpawnUpdate.cpp, CivilianSpawnUpdateCtorThunk.cpp and CivilianSpawnUpdateModuleDataDtor.cpp; guarded merge accepts no donors.
Remaining / next check: reconcile the selected ModuleData default-constructor COMDAT before canonical-base adoption, then align constructor field/enum views and the destructor novtable/EH contract without losing bytes or bindings.
Completed: owning acceptance retires the two already-adopted AI header queue rows; all source experiments restored.
Clearance: restored controls pass 21/21 function rows, one data row and 3/3 LINKS (1,154 bytes retained); no merge or census gain claimed. [Trials, acceptance and checks](../../reverse/attempt_support/civilian-spawn-consolidation-20261105.md).
