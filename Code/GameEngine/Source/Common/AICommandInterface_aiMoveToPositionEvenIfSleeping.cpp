// cl: /EHs /MD
// ?aiMoveToPositionEvenIfSleeping@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x00394191 108B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x36 and src,
// m_pos 12B copy from param1, virtual slot 0 call, then inlined vector-free
// via rowed free 0x00030830. Recipe precedent Rva00352ECAAICommand.cpp 101B
// (same ctor plus slot 0 plus inlined RvaCoords free, flags /O1 /EHs /MD).
// Evidence: immediates 0x36 0x00351BD0 0x00030830; callers 0x00395286 0x0039A44B 0x004560DF.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_DUMMY_1 = 1
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/RvaCoords.h"

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	void *m_obj;
	void *m_otherObj;
	const void *m_team;
	RvaCoords m_coords;
	char m_tail[0xC0 - 0x2C];
};

#include "../../Include/GameLogic/Module/AIUpdate.h"

void AICommandInterface::aiMoveToPositionEvenIfSleeping(const Coord3D *destination, CommandSourceType commandSource)
{
	AICommandParms parms((AICommandType)0x36, commandSource);
	parms.m_pos = *destination;
	aiDoCommand(&parms);
}
