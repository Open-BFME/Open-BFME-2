// cl: /DNDEBUG /MD /EHsc
//
// ??1RebuildHoleBehavior@@UAE@XZ, retail 0x0048353E, 118 bytes. Behavior-side
// destructor restoring the five MI vptrs (+0 0x849A74 +0x0C 0x849188 +0x10
// 0x849A68 +0x20 0x849A64 +0x24 0x849A50 DIR32) then the ZH worker cleanup
// (INVALID_OBJECT_ID-guarded TheGameLogic 0x9FE78C findObjectByID rowed 0x49DC5 plus
// destroyObject rowed 0x242C09 plus and-zero at +0x28) then the UpdateModule
// base dtor (pinned 0x24A797). Layout follows the rowed ctor TU 0x483271
// (UpdateModule base size 0x20 plus Die plus RebuildHole interfaces plus six
// words +0x28..+0x3C plus float +0x40 plus bool +0x44; factory 0x24C3FB news
// 0x48). Identity is the own vtable 0x849A74 plus slot 0 deleting dtor
// 0x483629 calling this body plus the RebuildHoleBehavior literal poolkey
// row. BFME1 donor RebuildHoleBehaviorDestructorThunk.cpp proves public
// virtual UAE; ZH RebuildHoleBehavior.cpp proves the find-plus-destroy shape.

class Thing;
class ModuleData;
class ThingTemplate;

#include "../../../Common/GameLogicObjectLookupView.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "../object.h"


extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/BehaviorModuleBase.h"

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/RebuildHoleBehaviorClass.h"



RebuildHoleBehavior::~RebuildHoleBehavior()
{
	if (m_workerID != INVALID_OBJECT_ID)
	{
		GameLogic *gameLogic = TheGameLogic;
		Object *worker = gameLogic->findObjectByID(m_workerID);
		if (worker)
		{
			gameLogic->destroyObject(worker);
			m_workerID = INVALID_OBJECT_ID;
		}
	}
}

// ?startRebuildProcess@RebuildHoleBehavior@@UAEXPBVThingTemplate@@W4ObjectID@@@Z @0x004835B4
void RebuildHoleBehavior::startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID)
{
	Object *spawner = TheGameLogic->findObjectByID(spawnerID);
	if (spawner)
		m_40 = spawner->m_324;
	m_rebuildTemplate = rebuild;
	m_spawnerObjectID = spawnerID;
	Object *worker = TheGameLogic->findObjectByID(m_workerID);
	newWorkerRespawnProcess(worker);
}

// ?loadPostProcess@RebuildHoleBehavior@@MAEXXZ: primary table 0x00C49A74
// slot 1 holds 0x00497805, the identical-code-folded `jmp` to
// UpdateModule::loadPostProcess (0x0058B03E) that every UpdateModule-family
// override without work of its own shares.
void RebuildHoleBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}
