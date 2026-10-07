// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
//
// ?createSpawn@SpawnBehavior@@AAE_NXZ, retail 0x0045FA57, 676 bytes.
// Identity: the three direct callers 0x00460482, 0x00460557 and 0x00460578
// sit in the SpawnBehavior update and initial-burst bodies that follow this
// one, it is the body between the rowed canAnySlavesAttack 0x0045F99E and
// onSpawnDeath 0x0045FCFB, and it follows Zero Hour's createSpawn statement
// for statement (exit door reservation, template name cycling, setProducer,
// the SlavedUpdate onEnslave walk, the spawn ID list and the budding exit).
// Donor: BFME 1's SpawnBehaviorCreateSpawn.cpp (retail 0x0020C3B0) for the
// command point gate and the player onUnitCreated call. BFME2 deltas read from
// retail: orphan reclaiming is gone, so the door is never unreserved; the
// command point gate reads module data +0x19 and the template's +0x618 cost
// against the player's +0x60 holder; newObject takes a zeroed 16-byte create
// mask by pointer and a bool; module data +0x172 makes the new spawn's AI
// ignore its spawner as an obstacle; a new spawn with a drawable is hidden
// when the spawner is fogged for the local player and fades in over module
// data +0x16C milliseconds (0.03 frames per millisecond); the budding host
// is the nearest spawn by the pinned Object distance helper 0x002615E3.
// Layout (primary this): module data +0x04, object +0x08, spawn template
// +0x38, one-shot countdown +0x3C, spawn IDs +0x4C, spawn count +0x54,
// initial burst countdown +0x5C, template name iterator +0x60. Object: team
// +0x304, behavior modules +0x244, AI +0x258, ID +0x74, producer ID +0x78,
// position +0x38; ThePlayerList's local player at +0x10 with its index at
// +0x54; KINDOF_STRUCTURE is bit 7 of the template's +0x108 mask.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#include <string.h>

#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1
};

enum CellShroudStatus
{
	OBJECTSHROUD_FOGGED = 3
};

class Object;
class Team;

class ThingTemplate
{
public:
	Int getCommandPoints() const { return m_commandPoints; }
	Bool isStructure() const { return (m_kindOf[0] & 0x80) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x618 - 0x108];
	Int m_commandPoints;
};

// The 16-byte status mask newObject reads through a pointer.
struct CreateMask
{
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, Bool unused);
};
extern ThingFactory *TheThingFactory;

class Rva002A7461
{
public:
	Int rva002A7548(Int which);
};

class Player
{
public:
	Rva002A7461 *commandPoints() { return &m_commandPoints; }
	Int getPlayerIndex() const { return m_playerIndex; }
	void onUnitCreated(Object *factory, Object *unit);

private:
	unsigned char m_pad00[0x54];
	Int m_playerIndex;
	unsigned char m_pad58[0x60 - 0x58];
	Rva002A7461 m_commandPoints;
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	unsigned char m_pad00[0x10];
	Player *m_local;
};
extern PlayerList *ThePlayerList;

class ExitInterface
{
public:
	virtual Bool isExitBusy() const;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject);
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
	virtual void exitObjectByBudding(Object *newObj, Object *budHost);
	virtual void unreserveDoorForExit(ExitDoorType exitDoor);
};

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const;
	virtual void onEnslave(const Object *slaver);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
#define BMI_SLOT(n) virtual void behaviorModuleInterfaceSlot##n();
	BMI_SLOT(00) BMI_SLOT(01) BMI_SLOT(02) BMI_SLOT(03) BMI_SLOT(04) BMI_SLOT(05)
	BMI_SLOT(06) BMI_SLOT(07) BMI_SLOT(08) BMI_SLOT(09) BMI_SLOT(10) BMI_SLOT(11)
	BMI_SLOT(12) BMI_SLOT(13) BMI_SLOT(14) BMI_SLOT(15) BMI_SLOT(16) BMI_SLOT(17)
	BMI_SLOT(18) BMI_SLOT(19) BMI_SLOT(20) BMI_SLOT(21) BMI_SLOT(22) BMI_SLOT(23)
	BMI_SLOT(24) BMI_SLOT(25)
#undef BMI_SLOT
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Drawable
{
public:
	void setFullyObscuredByShroud(Bool fullyObscured);
	void fadeIn(UnsignedInt frames);
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf_Structure() const { return getTemplate()->isStructure(); }
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	ObjectID getProducerID() const { return m_producerID; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }

	ExitInterface *getObjectExitInterface() const;
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	void setProducer(Object *obj);
	Real rva002615E3(const Coord3D *pos) const;

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	ObjectID m_producerID;
	unsigned char m_pad7c[0x244 - 0x7c];
	BehaviorModule **m_behaviors;
	unsigned char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25c[0x304 - 0x25c];
	Team *m_team;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x14];
	Bool m_isOneShotData;
	Bool m_canReclaimOrphans;
	Bool m_aggregateHealth;
	Bool m_exitByBudding;
	Bool m_spawnedRequireSpawner;
	Bool m_checkCommandPoints;
	unsigned char m_pad1a[0x20 - 0x1a];
	_STL::vector<AsciiString> m_spawnTemplateNameData;
	unsigned char m_pad2c[0x16c - 0x2c];
	UnsignedInt m_fadeInTime;
	unsigned char m_pad170[2];
	Bool m_spawnIgnoresSpawner;
};

class SpawnBehavior
{
private:
	Bool createSpawn();

	Object *getObject() const { return m_object; }
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }

	void *m_vptr;
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x38 - 0x0c];
	const ThingTemplate *m_spawnTemplate;
	Int m_oneShotCountdown;
	unsigned char m_pad40[0x4c - 0x40];
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_pad50[0x54 - 0x50];
	UnsignedInt m_spawnCount;
	unsigned char m_pad58[0x5c - 0x58];
	UnsignedInt m_initialBurstCountdown;
	_STL::vector<AsciiString>::const_iterator m_templateNameIterator;
};

enum
{
	NONE_SPAWNED_YET = 0xffffffff
};

// ?createSpawn@SpawnBehavior@@AAE_NXZ
Bool SpawnBehavior::createSpawn()
{
	Object *parent = getObject();
	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();

	ExitInterface *exitInterface = parent->getObjectExitInterface();
	if (exitInterface == NULL)
		return false;

	ExitDoorType exitDoor = exitInterface->reserveDoorForExit(NULL, NULL);
	if (exitDoor == DOOR_NONE_AVAILABLE)
		return false;

	m_spawnTemplate = TheThingFactory->findTemplate(*m_templateNameIterator);
	if (md->m_checkCommandPoints && m_spawnTemplate)
	{
		Player *controllingPlayer = parent->getControllingPlayer();
		if (controllingPlayer && controllingPlayer->commandPoints())
		{
			if (controllingPlayer->commandPoints()->rva002A7548(1) < m_spawnTemplate->getCommandPoints())
				return false;
		}
	}

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Object *newSpawn = TheThingFactory->newObject(m_spawnTemplate, parent->getTeam(), &mask, false);

	// Count this unit towards our score.
	newSpawn->getControllingPlayer()->onUnitCreated(parent, newSpawn);

	if (md->m_spawnIgnoresSpawner && newSpawn->getAI())
		newSpawn->getAI()->ignoreObstacle(parent);

	if (newSpawn->getDrawable())
	{
		if (parent->getShroudStatusForPlayer(ThePlayerList->m_local->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
			newSpawn->getDrawable()->setFullyObscuredByShroud(true);
		newSpawn->getDrawable()->fadeIn(md->m_fadeInTime * 0.03f);
	}

	++m_templateNameIterator;
	if (m_templateNameIterator == md->m_spawnTemplateNameData.end())
		m_templateNameIterator = md->m_spawnTemplateNameData.begin();

	newSpawn->setProducer(parent);

	// If they have a SlavedUpdate, then I have to tell them who their daddy is from now on.
	for (BehaviorModule **update = newSpawn->getBehaviorModules(); *update; ++update)
	{
		SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
		if (sdu != NULL)
		{
			sdu->onEnslave(parent);
			break;
		}
	}

	m_spawnIDs.push_back(newSpawn->getID());

	if (md->m_exitByBudding)
	{
		Bool barracksExitSuccess = false;

		if (m_initialBurstCountdown > 0)
		{
			Object *barracks = TheGameLogic->findObjectByID(parent->getProducerID());
			if (barracks && barracks->isKindOf_Structure())
			{
				ExitInterface *barracksExitInterface = barracks->getObjectExitInterface();
				if (barracksExitInterface)
				{
					ExitDoorType barracksDoor = barracksExitInterface->reserveDoorForExit(NULL, NULL);
					barracksExitInterface->exitObjectViaDoor(newSpawn, barracksDoor);
					newSpawn->setProducer(parent); // let parents producer exit him, but he thinks it was me
					--m_initialBurstCountdown;
					barracksExitSuccess = true;
				}
			}
		}

		if (!barracksExitSuccess)
		{
			// find the closest spawn to the nexus...
			Object *budHost = NULL;
			Object *curSpawn = NULL;
			Real tapeMeasure = 99999;
			Real closest = 999999.9f; // 1000 * 1000
			for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
			{
				curSpawn = TheGameLogic->findObjectByID(*iter);
				if (curSpawn)
				{
					if (curSpawn == newSpawn)
						continue;

					tapeMeasure = curSpawn->rva002615E3(parent->getPosition());
					if (tapeMeasure < closest)
					{
						closest = tapeMeasure;
						budHost = curSpawn;
					}
				}
			}
			exitInterface->exitObjectByBudding(newSpawn, budHost); // also handles the NULL pointer okay
		}
	}
	else
	{
		exitInterface->exitObjectViaDoor(newSpawn, exitDoor);
	}

	if (md->m_isOneShotData)
		m_oneShotCountdown--;

	if (m_spawnCount == NONE_SPAWNED_YET)
		m_spawnCount = 1;
	else
		++m_spawnCount;

	return true;
}
