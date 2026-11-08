// cl: /DNDEBUG /MD
//
// AIMoveAndDeleteState::update, retail 0x0034A02D (158 bytes): slot 6 of
// vtable 0x00C12C88, whose slot-2 name getter returns AIMoveAndDeleteState;
// the Zero Hour AIStates.cpp update (effectively-dead check, locomotor
// allow-invalid-position on, one-time append of the ground-snapped goal to the
// AI path, pinned base update 0x00347460, destroy the owner when it ends).
// BFME2 layout (target evidence): private status +0x438, AI +0x258 with path
// +0x140, current locomotor +0x1F0 (flags +0x44) and waiting-for-path +0x3B1;
// goal +0x20 and append flag +0x4C; getGroundHeight is TerrainLogic vslot 6;
// appendNode is the rowed Path::appendNode with flags 0x7FFFFFFF.
typedef bool Bool;
typedef float Real;
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/GameLogic/PathfindPath.h"
#include "../../../Include/GameLogic/LocomotorClass.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../Object/object.h"
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	Bool m_appendGoalPosition; // +0x4C
};
StateReturnType AIMoveAndDeleteState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
	{
		return STATE_FAILURE;
	}
	// do movement
	AIUpdateInterface *ai = obj->getAI();
	if (ai->getCurLocomotor())
	{
		ai->getCurLocomotor()->setAllowInvalidPosition(true);
	}
	if (m_appendGoalPosition)
	{
		Path *thePath = ai->getPath();
		if (!ai->isWaitingForPath() && ai->getPath())
		{
			m_goalPosition.z = TheTerrainLogic->getGroundHeight(m_goalPosition.x, m_goalPosition.y);
			thePath->appendNode(&m_goalPosition, LAYER_GROUND);
			m_appendGoalPosition = false; // just did it.
		}
	}
	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		TheGameLogic->destroyObject(obj);
	}
	return status;
}
