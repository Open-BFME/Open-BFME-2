# Retire 20 verified AIUpdateInterface header queue entries

Base: `a31785a66f2fbd1b89c5bbc2271d9876fc6ddde8`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 26 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/Common/Rva004A0670Copy.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/EvacuateGarrisonSpecialPowerSlot19.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003C8E2BExit.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003C8C6EDo.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_orderSlavesToGoIdle.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_orderSlavesToAttackTarget.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedAttackTeam.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeMeleeAmoebaAttackUnit.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 2 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFaceNamed.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_orderSlavesToAttackPosition.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterface_privateGuardRetaliate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedAttackAreaForSeconds.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedAttackArea.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuardForFramecount.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003C7914.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_wakeUpNow.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/AI/AIMoveAndEvacuateStateUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedAttackFollowWaypoints.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamFaceNamed.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateRva0049862B.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
