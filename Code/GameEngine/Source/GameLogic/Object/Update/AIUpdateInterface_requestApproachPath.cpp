// cl: /DNDEBUG /MD
//
// ?requestApproachPath@AIUpdateInterface@@QAEXPAUCoord3D@@@Z
// retail 0x00263B33, 211 bytes.
//
// BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// AIUpdateInterface::requestApproachPath. Retail differences read off the body:
// log via g_00E03745 plus theLogicRandomLogFile with _fprintf row 0x002CEC42,
// destination +0x148 victim +0x144 cleared final +0x3B3 attack +0x3B2 approach
// +0x3B4 safe +0x3B5, repath guard frame-2 via TheGameLogic+0x40, quick path
// uses setQueueForPathTime 2x BfmeLogicFramesPerSecond plus destroyPath, else waitingForPath
// +0x3B1 plus g_Va009FF0F8 pathfinder queueForPath. Evidence: donor plus
// CritterDesync requestApproachPath1 string plus rowed callees 0x002CEC42
// 0x0026282A 0x00262A8A 0x002EBD31 plus callers 0x0034CA43 0x00350651.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

extern int BfmeLogicFramesPerSecond;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern class AI *TheAI;

class Path;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::requestApproachPath(Coord3D *destination)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, "CritterDesync: requestApproachPath1 -- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
				m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
				destination->x, destination->y, destination->z);
	}

	m_requestedDestination = *destination;
	m_requestedVictimID = INVALID_OBJECT_ID;
	m_field3B3 = true;
	m_field3B2 = false;
	m_field3B4 = true;
	m_field3B5 = false;

	if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
	{
		setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
		destroyPath();
		return;
	}

	m_field3B1 = true;
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}
