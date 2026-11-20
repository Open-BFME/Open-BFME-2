# Refused early-forward cleanup trials

All rejected edits are restored and count zero tasks. Original native, candidate native, full raw type-graph and complete runtime refusals remain refused. No native check, flag, baseline, pin, alias, EH register or compiler input is weakened.

|Consumer|Group|Observed refusal|
|---|---|---|
|Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB05.cpp|early_forward|Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB05.cpp: compile failed: C2061: syntax error : identifier 'Coord3DBase'; C2805: binary 'operator ==' has too few parameters|
|Code/GameEngine/Source/Common/TacticalAI_updateInterestZones.cpp|early_forward|Code/GameEngine/Source/Common/TacticalAI_updateInterestZones.cpp: compile failed: C2061: syntax error : identifier 'Coord3DBase'; C2805: binary 'operator ==' has too few parameters|
|Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva0020A7C9.cpp|early_forward|Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva0020A7C9.cpp: compile failed: C2143: syntax error : missing ';' before '*'; C2501: 'Rva0020A227Element::Object' : missing storage-class or type specifiers; C2501: 'Rva0020A227Element::obj' : missing storage-class or type specifiers|
|Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/TacticalAI.cpp|early_forward|Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/TacticalAI.cpp: compile failed: C2061: syntax error : identifier 'Coord3DBase'; C2805: binary 'operator ==' has too few parameters|
