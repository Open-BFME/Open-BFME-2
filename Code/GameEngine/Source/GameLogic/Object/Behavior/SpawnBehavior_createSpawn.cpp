// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
#include "../../../Common/RTS/XYDistanceCallView.h"
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

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

#include "../../../Common/GameLogicObjectLookupView.h"

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

#include "../../../../Include/Common/ThingTemplate.h"
// The view's structure test reads kind-mask byte 0, bit 0x80 (+0x108).
static __forceinline Bool thingTemplateIsStructure(const ThingTemplate *tmpl)
{
	return (((const unsigned char *)tmpl->m_kindof)[0] & 0x80) != 0;
}
static __forceinline Int thingTemplateCommandPoints(const ThingTemplate *tmpl)
{
	return tmpl->m_commandPoints;
}

// The 16-byte status mask newObject reads through a pointer.
struct CreateMask
{
	unsigned int m_bits[4];
};

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID unused);
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

#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../../Include/GameLogic/Module/ExitInterface.h"

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const;
	virtual void onEnslave(const Object *slaver);
};

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameClient/Drawable.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf_Structure() const { return thingTemplateIsStructure(getTemplate()); }
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

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/SpawnBehaviorModuleData.h"

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
	if (md->m_respectCommandLimit && m_spawnTemplate)
	{
		Player *controllingPlayer = parent->getControllingPlayer();
		if (controllingPlayer && controllingPlayer->commandPoints())
		{
			if (controllingPlayer->commandPoints()->rva002A7548(1) < thingTemplateCommandPoints(m_spawnTemplate))
				return false;
		}
	}

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Object *newSpawn = TheThingFactory->newObject(m_spawnTemplate, parent->getTeam(), &mask, (ObjectID)0);

	// Count this unit towards our score.
	newSpawn->getControllingPlayer()->onUnitCreated(parent, newSpawn);

	if (md->m_spawnInsideBuilding && newSpawn->getAI())
		newSpawn->getAI()->ignoreObstacle(parent);

	if (newSpawn->getDrawable())
	{
		if (parent->getShroudStatusForPlayer(ThePlayerList->m_local->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
			newSpawn->getDrawable()->setFullyObscuredByShroud(true);
		newSpawn->getDrawable()->fadeIn(md->m_fadeInTime * 0.03f);
	}

	++m_templateNameIterator;
	if (m_templateNameIterator == reinterpret_cast<const _STL::vector<AsciiString> *>(md->m_storage20)->end())
		m_templateNameIterator = reinterpret_cast<const _STL::vector<AsciiString> *>(md->m_storage20)->begin();

	newSpawn->setProducer(parent);

	// If they have a SlavedUpdate, then I have to tell them who their daddy is from now on.
	for (BehaviorModule **update = newSpawn->getBehaviorModules(); *update; ++update)
	{
		SlavedUpdateInterface *sdu = static_cast<SlavedUpdateInterface *>(static_cast<BehaviorModuleInterface &>(**update).slot26());
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

					tapeMeasure = reinterpret_cast<Rva000CBA20 *>(curSpawn)->distSq(reinterpret_cast<const Rva000CBA20Point *>(parent->getPosition()));
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
// bfme link decl-only begin
namespace _STL { template <> _STL::_List_node<ObjectID> * list<ObjectID,_STL::allocator<ObjectID> >::_M_create_node(ObjectID const &); }
namespace _STL { template <> _STL::_List_node<ObjectID> * allocator<_STL::_List_node<ObjectID> >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> _STL::_List_iterator<ObjectID,_STL::_Nonconst_traits<ObjectID> > list<ObjectID,_STL::allocator<ObjectID> >::insert(_STL::_List_iterator<ObjectID,_STL::_Nonconst_traits<ObjectID> >,ObjectID const &); }
// bfme link decl-only end
