// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?computeQuickPath@AIUpdateInterface@@QAE_NPBUCoord3D@@@Z, retail 0x00265C5B
// (432 bytes, RET 4). Zero Hour's AIUpdateInterface::computeQuickPath with
// BFME 2's changes: the existing path is kept when its last node (no
// optimized successor) lies within 0.5 of the destination; aircraft that are
// not projectiles (template kind +0x109 bit 4, +0x10B bit 1) take the rowed
// Pathfinder::GetAircraftPath; others get a plain new Path (operator new 0x28,
// rowed constructor 0x00363DC8) with the destination and the owner's
// position at the destination's height prepended (Path 0x00265596, third
// argument 0x7FFFFFFF), shown when TheWritableGlobalData +0x9B8 is 1. Either
// path is then run through the pinned Path 0x00365E98 with the owner, its 2D
// direction and the +0x14 value of the owner's 0x0028AC4E entry; the
// timestamp (+0x160), AI slot 131, the blocked frame count (+0x16C) and the
// blocked flag (+0x3B8) follow.

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;
extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/PathNode.h"

#include "../../../../Include/GameLogic/PathfindPath.h"

struct Rva002EDEABArg;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

struct Rva0028AC4EValue
{
	unsigned char m_pad00[0x14];
	Int m_14; // +0x14
};

struct Rva0028AC4EEntry
{
	unsigned char m_pad00[0x04];
	const Rva0028AC4EValue *m_value; // +0x04
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x14]; // +0x108
};

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Int rva0028B511() const; // the layer
	Bool isKindOfAircraft() const { return (m_template->m_kindOf[1] & 0x10) != 0; }
	Bool isKindOfProjectile() const { return (m_template->m_kindOf[3] & 2) != 0; }
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

Bool AIUpdateInterface::computeQuickPath(const Coord3D *destination)
{
	Object *obj = getObject();
	const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
	if (m_path)
	{
		PathNode *closeNode = m_path->getLastNode();
		if (closeNode && closeNode->getNextOptimized() == 0)
		{
			Real dxSqr = destination->x - closeNode->getPosition()->x;
			dxSqr *= dxSqr;
			Real dySqr = destination->y - closeNode->getPosition()->y;
			dySqr *= dySqr;
			Real dzSqr = destination->z - closeNode->getPosition()->z;
			dzSqr *= dzSqr;
			if (dxSqr + dySqr + dzSqr < 0.25f)
				return true;
		}
	}
	destroyPath();
	if (obj->isKindOfAircraft() && !obj->isKindOfProjectile())
	{
		m_path = TheAI->pathfinder()->GetAircraftPath(getObject(), destination);
	}
	else
	{
		m_path = new Path;
		m_path->prependNode(destination, LAYER_GROUND, 0x7FFFFFFF);
		Coord3D pos;
		pos.x = getObject()->getPosition()->x;
		pos.y = getObject()->getPosition()->y;
		pos.z = destination->z;
		m_path->prependNode(&pos, (PathfindLayerEnum)getObject()->rva0028B511(), 0x7FFFFFFF);
		if (TheWritableGlobalData->field09B8 == 1)
			TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	}
	Coord3D direction;
	obj->getUnitDirectionVector2D(direction);
	m_path->rva00365E98(obj, &direction, entry->m_value->m_14, false);
	m_pathTimestamp = TheGameLogic->getFrame();
	setLocomotorGoalPositionOnPath();
	m_blockedFrames = 0;
	m_field3B8 = false;
	return true;
}
