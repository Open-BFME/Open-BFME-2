// cl: /DNDEBUG /MD
//
// INI::parseAIDataDefinition, retail 0x001D8E7A (5 bytes): Zero Hour's
// GameEngine/Source/Common/INI/INIAiData.cpp body unchanged, a tail jump to
// AI::parseAiDataDefinition (rowed at 0x002FFF72). Identity: the "AIData"
// BlockParse entry at 0x009B8938 (theAIDataBlockParse) holds this address in
// its parse slot.

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/GameLogic/AI.h"

void INI::parseAIDataDefinition(INI *ini)
{
	AI::parseAiDataDefinition(ini);
}
