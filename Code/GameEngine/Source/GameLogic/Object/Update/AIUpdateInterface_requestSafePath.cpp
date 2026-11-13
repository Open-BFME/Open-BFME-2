// cl: /DNDEBUG /MD
//
// ?requestSafePath@AIUpdateInterface@@QAEXW4ObjectID@@@Z
// retail 0x00263EA2, 261 bytes.
//
// BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// AIUpdateInterface::requestSafePath. Retail differences read off the body:
// repulsor current +0x18c prev +0x190, victim +0x144 cleared final +0x3B3
// attack +0x3B2 approach +0x3B4 safe +0x3B5, repath guard frame-2 via
// TheGameLogic+0x40, quick path uses setQueueForPathTime 2x BfmeLogicFramesPerSecond
// plus destroyPath, else waitingForPath +0x3B1 plus CritterDesync logs via
// g_00E03745 plus theLogicRandomLogFile with _fprintf row 0x002CEC42,
// destination +0x148 from object pos +0x38 plus g_Va009FF0F8 pathfinder
// queueForPath. Evidence: donor plus CritterDesync requestSafePath strings
// plus rowed callees 0x0026282A 0x00262A8A 0x002CEC42 0x002EBD31.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
// Retail calls the game's _fprintf thunk (0x002CEC42) through REL32, so
// read <stdio.h> without dllimport.
#define _CRTIMP
#include <stdio.h>
#undef _CRTIMP

extern int BfmeLogicFramesPerSecond;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../../Common/GameLogicObjectLookupView.h"

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D &getPosition() const { return m_position; }
private:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern class AI *TheAI;

class Path;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::requestSafePath(ObjectID repulsor)
{
	if (repulsor != m_repulsorID)
		m_prevRepulsorID = m_repulsorID;
	m_repulsorID = repulsor;
	m_field3B3 = false;
	m_field3B2 = false;
	m_requestedVictimID = INVALID_OBJECT_ID;
	m_field3B4 = false;
	m_field3B5 = true;

	if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
	{
		setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
		destroyPath();
		return;
	}

	m_field3B1 = true;
	if (g_00E03745)
	{
		FILE *log = (FILE *)theLogicRandomLogFile;
		if (log != 0)
		{
			fprintf(log, "CritterDesync: requestSafePath 'I don't believe this line accomplishes anything' ");
			FILE *log2 = (FILE *)theLogicRandomLogFile;
			if (log2 != 0)
				fprintf(log2, "-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
					m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
					getObject()->getPosition().x, getObject()->getPosition().y, getObject()->getPosition().z);
		}
	}

	m_requestedDestination = getObject()->getPosition();
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}
