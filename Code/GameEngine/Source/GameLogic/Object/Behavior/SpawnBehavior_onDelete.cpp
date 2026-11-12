// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?onDelete@SpawnBehavior@@UAEXXZ, retail 0x0045F75D, 88 bytes. Slot 8
// (offset 0x20) of vtable 0x008426AC (class of rowed dtor
// ??1SpawnBehavior@@UAE@XZ at 0x0045F6D3 in SpawnBehaviorDtor.cpp).
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Behavior/
// SpawnBehavior.cpp:107) with the BFME2 layout plus the setProducer(null)
// delta: when the ModuleData at +0x04 has m_spawnedRequireSpawner at +0x18,
// iterates m_spawnIDs at primary +0x4C, resolves each through TheGameLogic
// (0x9FE78C) findObjectByID (rowed 0x49DC5), clears its producer through
// the rowed 0x28AFD2 setProducer(null), then destroys it through the rowed
// 0x242C09 destroyObject when its +0x438 bit0 is clear (inline
// isEffectivelyDead). Primary-this view: UpdateModule base size 0x20 plus
// four empty interfaces at +0x20..+0x2C plus UpgradeMux at +0x30 size 8
// plus ptr+3 ints at +0x38..+0x44 plus two lists at +0x48/+0x4C (ctor
// 0x0045F581 news 0x64). ZH donor SpawnBehavior::onDelete proves the
// find-plus-destroy loop shape.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

#include "../../../Common/GameLogicObjectLookupView.h"

class Thing;
class ModuleData;
class ThingTemplate;

#include "../object.h"

#include "../../../../Include/GameLogic/Module/SpawnBehaviorModuleData.h"


extern GameLogic *TheGameLogic;



#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"



class SpawnBehaviorInterface
{
public:
	virtual void spawnAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieAnchor();
};

class DamageModuleInterface
{
public:
	virtual void damageAnchor();
};

#include "../../../../Include/Common/SpawnExtraBase.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	virtual void onDelete();

private:
	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
};

void SpawnBehavior::onDelete()
{
	const SpawnBehaviorModuleData *modData = reinterpret_cast<const SpawnBehaviorModuleData *>(getModuleData());
	if (modData->m_spawnedRequireSpawner)
	{
		for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it._M_node != m_spawnIDs.end()._M_node; )
		{
			Object *obj = TheGameLogic->findObjectByID(*it);
			if (obj)
				obj->setProducer(NULL);
			++it;
			if (obj && (obj->m_privateStatus & 1) == 0)
				TheGameLogic->destroyObject(obj);
		}
	}
}
