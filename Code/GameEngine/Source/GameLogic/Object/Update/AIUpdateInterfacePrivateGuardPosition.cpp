// cl: /DNDEBUG /MD
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

// ?privateGuardPosition@AIUpdateInterface@@MAEXPBUCoord3D@@W4GuardMode@@W4CommandSourceType@@@Z
// 0x00264BC2 249B: AIUpdateInterface guard order. Checks testStatus 0x26,
// isMobile and KINDOF_PROJECTILE, sets guard target 0x50/0x54 to LOCATION,
// clips to playable area via TheTerrainLogic when cmdSource is player, stores
// position +0x58, guardMode +0x4C, clear via slot 0x14 and setState 0x10 via
// slot 0x20. Vtable slot 63 of DeployStyle/Siege/Supply/Transport/Wander/
// HordeWorker AIUpdates. Sibling privateGuardObject 0x00264D0E slot 64 shares
// guards, target logic, clear and state. ZH donor AIUpdate.cpp
// privateGuardPosition supplies position/clip/state shape.
#include "../../../../Include/Common/ScalarTypes.h"




enum ObjectStatusTypes
{
	BFME_OBJECT_STATUS_26 = 0x26
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_LOCATION = 0,
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_NONE = 4
};

enum
{
	BFME_AI_GUARD = 0x10
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../Libraries/Include/Lib/Region3D.h"

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isMobile() const;
};


#include "../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

void AIUpdateInterface::privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource)
{
	Object *obj = m_object;
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (((unsigned char)(m_object->m_template->m_kindof[KINDOF_PROJECTILE >> 5] >> (KINDOF_PROJECTILE & 24)) & (1 << (KINDOF_PROJECTILE & 7))) != 0)
		return;
	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_LOCATION;
	else
		m_guardTargetType[0] = GUARDTARGET_LOCATION;
	Coord3D adjPos;
	adjPos.x = pos->x;
	adjPos.y = pos->y;
	adjPos.z = pos->z;
	if (cmdSource == CMD_FROM_PLAYER) {
		Region3D r;
		TheTerrainLogic->getExtent(&r);
		if (!r.isInRegionNoZ(&adjPos))
			adjPos = TheTerrainLogic->findClosestEdgePoint(&adjPos);
	}
	m_locationToGuard = adjPos;
	m_guardMode = guardMode;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}
