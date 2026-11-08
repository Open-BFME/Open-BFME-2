// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?requestMeleeApproachPath@AIUpdateInterface@@QAE_NPBUCoord3D@@_N@Z
// retail 0x00263C06, 668 bytes (ret 8).
//
// Identity: WorldBuilder AIUpdate.cpp AIUpdateInterface::requestMeleeApproachPath
// (wb 0x00E39180; callees Coord3D::length/normalize, getLayerForDestination,
// Pathfinder::AdjustToMeleeDestination, Object 0x0028ACDC, queueForPath,
// setQueueForPathTime, destroyPath) plus the CritterDesync
// requestMeleeApproachPath1 string referenced only from this body. The tail is
// the sibling requestApproachPath 0x00263B33.
//
// Target evidence: unless the bool argument is set the offset from the goal
// to the object is clamped to the AI data float at +0x94 and added to the goal,
// which is abandoned when its layer height (TheTerrainLogic vtable +0x1C)
// differs from the goal's by more than 10 (fabs through the msvcr71 import);
// Pathfinder 0x002ED7F7 (pinned from this call) then adjusts it for the object with the
// locomotor set at +0x1CC; a destination closer than 20 to the object refuses
// the path.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// Coord3D uses the canonical three-float layout.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include <math.h>

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

extern int BfmeLogicFramesPerSecond;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../../Common/GameLogicObjectLookupView.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	void rva0028ACDC(Int pos);
private:
	char m_pad00[0x38];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

class LocomotorSet;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/TAiData.h"
#include "../../../../Include/GameLogic/AI.h"

class Path;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

Bool AIUpdateInterface::requestMeleeApproachPath(const Coord3D *destination, Bool exact)
{
	const Coord3D *position = getObject()->getPosition();
	Coord3D objPos = {position->x, position->y, position->z};
	Coord3D delta;
	delta.x = objPos.x - destination->x;
	delta.y = objPos.y - destination->y;
	delta.z = 0.0f;

	if (!exact && delta.length() > TheAI->getAiData()->m_meleeApproachDist)
	{
		delta.normalize();
		const TAiData *data = TheAI->getAiData();
		delta.x *= data->m_meleeApproachDist;
		delta.y *= data->m_meleeApproachDist;
	}

	Coord3D dest = {destination->x, destination->y, destination->z};
	if (!exact)
	{
		dest.x += delta.x;
		dest.y += delta.y;
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(getObject(), destination);
		Real heightDelta = fabs(TheTerrainLogic->getLayerHeight(dest.x, dest.y, layer) - TheTerrainLogic->getLayerHeight(destination->x, destination->y, layer));
		if (heightDelta > 10.0f)
			dest = *destination;
	}

	if (TheAI->pathfinder()->adjustToMeleeDestination(getObject(), m_locomotorSet, &dest))
	{
		getObject()->rva0028ACDC((Int)&dest);
		delta = objPos;
		delta.x -= dest.x;
		delta.y -= dest.y;
		delta.z = 0.0f;
		if (!(delta.length() < 20.0f))
		{
			if (g_00E03745)
			{
				void *log = theLogicRandomLogFile;
				if (log != 0)
					fprintf(log, "CritterDesync: requestMeleeApproachPath1 -- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
						m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
						dest.x, dest.y, dest.z);
			}

			m_requestedDestination = dest;
			m_requestedVictimID = INVALID_OBJECT_ID;
			m_field3B3 = true;
			m_field3B2 = false;
			m_field3B4 = true;
			m_field3B5 = false;

			if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
			{
				setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
				destroyPath();
				return true;
			}

			m_field3B1 = true;
			TheAI->pathfinder()->queueForPath(getObject()->getID());
			return true;
		}
	}
	return false;
}
