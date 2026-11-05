// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
// platformsdk
//
// FireSpreadUpdate::update (BFME 2), from the Generals Zero Hour
// FireSpreadUpdate.cpp.
//
// Target facts. update is slot 0 of FireSpreadUpdate's UpdateModuleInterface
// vftable (0x0084BF84, right after PartitionFilterFlammable's 0x0084BF78). The
// ZH-port unit FireSpreadUpdate.cpp builds without this region's SSE flags and
// keeps its copy present-unmatched. The module data holds OCLEmbers at +8 and
// SpreadTryRange at +0x14 (field table 0x00C4C000). BFME 2 differences from
// ZH:
// - AFLAME is Object::testStatus(10).
// - BFME 2's partition filters chain through a next pointer, so the
//   flammable filter goes to getClosestObject alone.
// - When nothing flammable is in range and the AI data's +0xBC flag is set,
//   the TerrainLogic query 0x0027F108 at the object's position and the spread
//   range, resolved to an object by TerrainLogic 0x00283D70, is the candidate.
// - calcNextSpreadDelay is the rowed 0x0048B7D9.
#include "Lib/Coord3D.h"
#include <windows.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class ModuleData;
class Module;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#define UPDATE_SLEEP(x) ((UpdateSleepTime)(x))

enum ObjectStatusTypes
{
	OBJECT_STATUS_AFLAME = 10
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class FlammableUpdate
{
public:
	void tryToIgnite();
};

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }

protected:
	Module *findModule(NameKeyType key) const;
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
	static void create(ObjectCreationList *ocl, Object *primaryObj, Object *secondaryObj)
	{
		if (ocl)
			ocl->create(primaryObj, secondaryObj, 0);
	}
};

// Partition filters (see the BroadcastStealthUpdate.cpp view).
#include "../../../../Include/GameLogic/PartitionFilter.h"


// vftable 0x0084BF78 (allow 0x0048B6D5, rowed in FireSpreadUpdate.cpp).
class PartitionFilterFlammable : public Rva000421C8
{
public:
	PartitionFilterFlammable() {}
	virtual bool allow(Object *objOther);
};

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#include "../../../../Include/GameLogic/TerrainLogic.h"

// 0x0027F108, rowed as BfmeThingCME::rva0027F108 (BfmeConv624.cpp).
class BfmeThingCME
{
public:
	int rva0027F108(void *pos, Real radius, int flag, int unused);
};
extern TerrainLogic *TheTerrainLogic;

#include "../../../../Include/GameLogic/TAiData.h"
#include "../../../../Include/GameLogic/AI.h"

class FireSpreadUpdateModuleData
{
public:
	char m_unknown00[0x08];
	ObjectCreationList *m_oclEmbers; // +0x08
	UnsignedInt m_minSpreadTryDelayData; // +0x0C
	UnsignedInt m_maxSpreadTryDelayData; // +0x10
	Real m_spreadTryRange; // +0x14
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class FireSpreadUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	UnsignedInt calcNextSpreadDelay();	// 0x0048B7D9 (calcNextSpreadDelay)

protected:
	const FireSpreadUpdateModuleData *getFireSpreadUpdateModuleData() const
	{
		return (const FireSpreadUpdateModuleData *)m_moduleData;
	}
};

// ?update@FireSpreadUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048B7FD 315B
UpdateSleepTime FireSpreadUpdate::update( void )
{
	const FireSpreadUpdateModuleData* fireSpreadUpdateModuleData = getFireSpreadUpdateModuleData();
	Object* me = getObject();

	if( !me->testStatus( OBJECT_STATUS_AFLAME ) )
		return UPDATE_SLEEP_FOREVER;		// not on fire -- sleep forever
	{
		ObjectCreationList::create( fireSpreadUpdateModuleData->m_oclEmbers, me, NULL );

		if( fireSpreadUpdateModuleData->m_spreadTryRange != 0 )
		{
			// This will spread fire explicitly
			Object* objectToLight;
			{
				PartitionFilterFlammable fFilter;
				objectToLight = ThePartitionManager->getClosestObject(getObject()->getPosition(), fireSpreadUpdateModuleData->m_spreadTryRange, FROM_CENTER_3D, &fFilter);
			}
			if( objectToLight == NULL && TheAI->getAiData()->m_allowForestFires )
			{
				void *found = (void *)((BfmeThingCME *)TheTerrainLogic)->rva0027F108( (void *)me->getPosition(), fireSpreadUpdateModuleData->m_spreadTryRange, 1, 0 );
				if( found )
					objectToLight = TheTerrainLogic->rva00283D70( (const Coord3D *)found );
			}
			if( objectToLight )
			{
				static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
				FlammableUpdate* fu = (FlammableUpdate*)objectToLight->findUpdateModule(key_FlammableUpdate);
				if( fu )
					fu->tryToIgnite();
			}
		}

		return UPDATE_SLEEP(calcNextSpreadDelay());
	}
}
