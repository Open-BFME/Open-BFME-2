### LINK-489: CivilianSpawnUpdate base constructor and destructor block consolidation
Status: Blocked. Updated: 2026-11-05; inspected revision: fcae9526ac.
Affected: CivilianSpawnUpdate.cpp, CivilianSpawnUpdateCtorThunk.cpp and CivilianSpawnUpdateModuleDataDtor.cpp; guarded merge accepts no donors.
Remaining / next check: reconcile the selected ModuleData default-constructor COMDAT before canonical-base adoption, then align constructor field/enum views and the destructor novtable/EH contract without losing bytes or bindings.
Completed: owning acceptance retires the two already-adopted AI header queue rows; all source experiments restored.
Clearance: restored controls pass 21/21 function rows, one data row and 3/3 LINKS (1,154 bytes retained); no merge or census gain claimed. [Trials, acceptance and checks](../../reverse/attempt_support/civilian-spawn-consolidation-20261105.md).


2026-11-17, inspected9dcb0c7478c: a new native canonical-base candidate emits
no ModuleData constructor/default table, expands the target848530 to31slots/124B,
and preserves all42old external text definitions. Moving delay+8 into the derived
class first is runtime-identical. However owning preparation refuses the unused
base word+4's void-pointer versus canonical enum kind. No candidate is admitted;
all source changes restored. Separate unused-scalar field-ownership proof is
required before normal15row+1data/EH/current-link checks and real bridge verification.
The earlier novtable/destructor merge remains blocked independently.
[Refusal and native evidence](../../reverse/attempt_support/civilian-moduledata-scalar-proof-20261117-root20.md).
