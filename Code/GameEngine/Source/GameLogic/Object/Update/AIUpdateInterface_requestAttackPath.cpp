// cl: /DNDEBUG /MD
//
// ?requestAttackPath@AIUpdateInterface@@QAEXW4ObjectID@@PBUCoord3D@@@Z
// retail 0x00263A39, 250 bytes.
//
// BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// AIUpdateInterface::requestAttackPath. Retail differences read off the body:
// log via g_00E03745 plus theLogicRandomLogFile with _fprintf row 0x002CEC42,
// destination +0x148 victim +0x144 flags +0x3B2/+0x3B4/+0x3B5, repath guard
// frame-2 via TheGameLogic+0x40, quick path uses Path at +0x140 plus int at
// +0x16C with setQueueForPathTime(BfmeLogicFramesPerSecond) or 2x plus destroyPath plus
// slot 0x220 setLocomotorGoalNone, else waitingForPath +0x3B1 plus
// g_Va009FF0F8 pathfinder queueForPath. Evidence: donor plus CritterDesync
// requestAttackPath1 string plus rowed callees 0x002CEC42 0x0026282A
// 0x00262A8A 0x002EBD31 plus callers 0x0034060F 0x0034829D 0x00348341.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// Retail calls the game's direct fprintf wrapper rather than the CRT import.
#define _CRTIMP
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)

extern unsigned char g_00E03745;
extern "C" FILE *theLogicRandomLogFile;

extern int BfmeLogicFramesPerSecond;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../../Common/GameLogicObjectLookupView.h"

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_pad00[0x74];
	ObjectID m_id;
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern class AI *TheAI;

class Path;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::requestAttackPath(ObjectID victimID, const Coord3D *victimPos)
{
	if (g_00E03745)
	{
		FILE *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, "CritterDesync: requestAttackPath1-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
				m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
				victimPos->x, victimPos->y, victimPos->z);
	}

	m_requestedDestination = *victimPos;
	m_requestedVictimID = victimID;
	m_field3B2 = true;
	m_field3B4 = false;
	m_field3B5 = false;

	if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
	{
		if (m_path != 0 && m_blockedFrames > 0)
		{
			setQueueForPathTime(LogicFramesPerSecond);
			return;
		}
		setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
		destroyPath();
		setLocomotorGoalNone();
		return;
	}

	m_field3B1 = true;
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}
