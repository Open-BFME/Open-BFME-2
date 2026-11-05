// cl: /MD /DNDEBUG /D_CRTIMP=
//
// ?requestPath@AIUpdateInterface@@QAEXPAUCoord3D@@_N@Z
// retail 0x0026893F, 248 bytes (Ghidra FUN_0066893f).
//
// Donor: GeneralsMD AIUpdate.cpp AIUpdateInterface::requestPath. BFME 2
// differences, all read off the body: an immobile unit (no valid locomotor
// surfaces, +0x1DC) returns at once instead of asserting; the old and new
// destinations go to the "CritterDesync: requestPath1" log (the debug flag
// and FILE globals the AIWanderStateMethods.cpp logs use); the victim ID is
// reset before the flags; the repath guard compares against frame - 2 and
// only reschedules (no blocked-and-stuck reset); m_waitingForPath is set on
// the queueForPath path only. Layout: destination +0x148, victim +0x144,
// timestamp +0x160, flags +0x3B1..+0x3B5.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include <stdio.h>
extern unsigned char g_00E03745;
extern "C" FILE *theLogicRandomLogFile;

extern int BfmeLogicFramesPerSecond;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_AIR = 8
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::requestPath( Coord3D *destination, Bool isFinalGoal )
{
	if (m_locomotorSet.getValidSurfaces() == 0)
		return;

	if (g_00E03745)
	{
		FILE *log = theLogicRandomLogFile;
		if (log)
			fprintf(log, "CritterDesync: requestPath1-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
				m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
				destination->x, destination->y, destination->z);
	}

	m_requestedDestination = *destination;
	m_requestedVictimID = INVALID_OBJECT_ID;
	m_field3B3 = isFinalGoal;
	m_field3B2 = false;
	m_field3B4 = false;
	m_field3B5 = false;
	if (canComputeQuickPath()) {
		computeQuickPath(destination);
		return;
	}
	if (m_pathTimestamp > TheGameLogic->getFrame() - 2) {
		/* Requesting path very quickly.  Can cause a spin. */
		setQueueForPathTime(LogicFramesPerSecond);
		return;
	}
	m_field3B1 = true;
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}

// ?canComputeQuickPath@AIUpdateInterface@@QAE_NXZ @0x00262A64 38B (Ghidra
// FUN_00662a64), pinned from requestPath's call: Zero Hour's body unchanged,
// isDoingGroundMovement at vtable byte offset 0x224.
Bool AIUpdateInterface::canComputeQuickPath( void )
{
	/* Basically, if a unit is moving through the air, we can quick path.  jba. */
	Bool landBound = false;
	if (!(m_locomotorSet.getValidSurfaces() & LOCOMOTORSURFACE_AIR))
	{
		landBound = true;
	}

	Bool unitIsFlyingThroughTheAir = false;
	if (landBound) {
		unitIsFlyingThroughTheAir = false; // Land bound units never fly.
	}	else {
		if (!isDoingGroundMovement()) {
			// If it can fly, and it isn't moving on the ground, we're flying.
			unitIsFlyingThroughTheAir = true;
		}
	}
	return unitIsFlyingThroughTheAir;
}
