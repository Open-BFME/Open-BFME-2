// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva002657CE@AIUpdateInterface@@QAEXXZ, retail 0x002657CE..0x0026594F (385B),
// thiscall, EH.
//
// Rebuilds the AI's path from the state machine's goal path: the old path is
// deleted (rowed ~Path 0x00364A89 and operator delete), a new 0x28-byte Path
// (rowed ctor 0x00363DC8) starts at the object's position on the ground layer
// (rowed appendNode 0x002655E3 with the 0x7FFFFFFF third argument), is
// prepared for the current locomotor's surfaces (pinned 0x00364551), then
// takes every goal path position (pinned AIStateMachine::getGoalPathPosition
// 0x00346FA5 over the 12-byte goal vector at +0x3C/+0x40 of the state machine
// at +0x30) on the layer TerrainLogic::getLayerForDestination 0x002802FE
// picks. With TheGlobalData +0x9B8 == 1 the path becomes the pathfinder's
// debug path (rowed SetDebugPath 0x002EDEAB). The path is finished along the
// object's 2D facing (rowed Thing::getUnitDirectionVector2D 0x0030A2A2, pinned
// 0x00365E98), the path timestamp +0x160 takes the logic frame, this's slot
// 131 runs and +0x16C is cleared.
//
// Evidence (target): the body follows setPathFromWaypoint 0x0026569F
// (AIUpdateInterface_setPathFromWaypoint.cpp: same object +0x08, m_path
// +0x140, Path node calls and TheAI pathfinder +0x10); the current locomotor
// is +0x1F0 with its template at +0x04 (surfaces +0x14). No direct caller or
// WorldBuilder name was found; the method name stays address-derived.

#include "Coord3D.h"

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

#include "../../../../Include/GameLogic/PathfindPath.h"

#include <new>

#include "../../../Common/Thing/thing.h"

#include "../object.h"

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

struct Rva002EDEABArg;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// STLport vector<Coord3D> view of the goal path.
struct GoalPathVector
{
	Int size() const { return _M_finish - _M_start; }
	Coord3D *_M_start;
	Coord3D *_M_finish;
	Coord3D *_M_end_of_storage;
};

// Rowed goal-path accessor 0x00346FA5 (its pin names AIStateMachine::getGoalPathPosition).
#include "../../../../Include/Common/Rva00346FA5.h"

class AIStateMachine
{
public:
	const Coord3D *getGoalPathPosition(Int i) const;
	Int getNumGoalPathPositions() const { return m_goalPath.size(); }
private:
	unsigned char m_pad00[0x3C];
	GoalPathVector m_goalPath;				// +0x3C
};

#include "../../../../Include/GameLogic/LocomotorTemplate.h"

#include "../../../../Include/GameLogic/LocomotorClass.h"


#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva002657CE()
{
	Object *obj = getObject();
	Locomotor *locomotor = m_curLocomotor;
	if (m_path)
	{
		delete m_path;
		m_path = 0;
	}
	m_path = new Path;
	m_path->appendNode(obj->getPosition(), LAYER_GROUND, 0x7FFFFFFF);
	m_path->rva00364551(obj, locomotor->m_template->m_surfaces, false, 0);
	for (Int i = 0; i < m_stateMachine->getNumGoalPathPositions(); i++)
	{
		Coord3D pos;
		const Coord3D *goal = (const Coord3D *)((const Rva00346FA5 *)m_stateMachine)->rva00346FA5(i);
		pos.x = goal->x;
		pos.y = goal->y;
		pos.z = goal->z;
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &pos);
		m_path->appendNode(&pos, layer, 0x7FFFFFFF);
	}
	if (TheWritableGlobalData->field09B8 == 1)
		TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	Coord3D dir;
	obj->getUnitDirectionVector2D(dir);
	m_path->rva00365E98(obj, &dir, locomotor->m_template->m_surfaces, false);
	m_pathTimestamp = TheGameLogic->getFrame();
	setLocomotorGoalPositionOnPath();
	m_blockedFrames = 0;
}
