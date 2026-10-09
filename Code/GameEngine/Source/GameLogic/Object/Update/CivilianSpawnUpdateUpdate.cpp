// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Source /DNDEBUG /MD /EHsc
//
// ?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ retail
// 0x0047FAFE..0x0047FDF7 (761 bytes).
//
// Identity:
// - WorldBuilder 0x011B3DE0 is CivilianSpawnUpdate::update
//   (CivilianSpawnUpdate.cpp). Retail's __FILE__ string is at VA 0x00C484C8.
// - The module data fields come from the rowed parse table 0x00C48478
//   (CivilianSpawnUpdateModuleDataCtor.cpp): SpawnDelayTime +0x08,
//   RunToFilter +0x0C, MaximumDistance +0x10, Civilian names +0x14.
// - m_spawnFrame +0x20 comes from the rowed ctor 0x0047F9D4.
//
// What the body does:
// - It picks a random civilian template (pinned ThingFactory::findTemplate)
//   and gathers candidate run-to objects in MaximumDistance through the
//   rowed partition iterator. The filters are not dead, not self, and
//   matches RunToFilter for the controlling player; their classes and
//   vtables are as in the rowed Rva004389AENearbyCheck.cpp.
// - It takes a random hit, creates the civilian in the owner's team with a
//   zeroed CreateMask, and places it half a bounding radius ahead of the
//   spawner.
// - Unless the civilian has no AI, it:
//   - sets locomotor set 4 (AI slot 142) and MODELCONDITION_PANICKING;
//   - aims half a radius ahead of the target;
//   - ignores the target as an obstacle;
//   - moves there with CMD_FROM_AI when the pinned QuickDoesPathExist allows,
//     or destroys the civilian otherwise.
// - It returns m_spawnFrame.
//
// Matching notes:
// - The first direction copy is member-wise and the second a struct
//   assignment, as retail.
// - The PANICKING bit is 2*32+13 of the flags at +0x10C, as in the rowed
//   AIWanderStateMethods.cpp.
#include <string.h>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/GameLogicObjectLookupView.h"
#include "Common/PartitionRangeQueryCallView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
enum ModelConditionFlagType
{
	MODELCONDITION_PANICKING = 2 * 32 + 13
};
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

class Player;
class Team;
class ThingTemplate;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BCECF0, allow 0x002614EC.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

struct BfmeWideResultStorage
{
	void *m_start;
	void *m_finish;
};

// The query result's hit vector holds 8-byte entries.
__forceinline Int CivilianSpawnHitCount(const BfmeWideResult &result)
{
	const BfmeWideResultStorage *hits = (const BfmeWideResultStorage *)result.m_value;
	return ((char *)hits->m_finish - (char *)hits->m_start) >> 3;
}

extern PartitionManager *ThePartitionManager;

struct CreateMask
{
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};
extern ThingFactory *TheThingFactory;

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) V10(9)
	V10(10) V10(11) V10(12) V10(13)
	V(140) V(141)
	virtual Bool chooseLocomotorSet(Int set);		// slot 142 (+0x238)
#undef V10
#undef V
	void ignoreObstacle(const Object *obj);
	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commandInterface;		// +0x20
};

class Pathfinder
{
public:
	void rva003E3BFB(ObjectID id);
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int flags);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;					// +0x10
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;

class CivilianSpawnModelConditionFlags
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	Real getBoundingRadius() const { return m_boundingRadius; }
	Team *getTeam() const { return m_team; }
	AIUpdateInterface *getAI() const { return m_ai; }
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	char m_pad000[0x38];
	Coord3D m_pos;								// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;								// +0x74
	char m_pad078[0xCC - 0x78];
	Real m_boundingRadius;						// +0xCC
	char m_pad0D0[0x10C - 0xD0];
	CivilianSpawnModelConditionFlags m_modelConditionFlags;	// +0x10C
	char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai;					// +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;								// +0x304
};
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

__forceinline void CivilianSpawnScale(Coord3D &c, Real s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

struct CivilianSpawnUpdateModuleData
{
	void *m_vtable;
	Int m_04;
	UnsignedInt m_spawnDelay;					// +0x08 SpawnDelayTime
	char m_runToFilter[4];						// +0x0C RunToFilter
	Int m_maximumDistance;						// +0x10 MaximumDistance
	AsciiString *m_civilianStart;				// +0x14 Civilian
	AsciiString *m_civilianFinish;			// +0x18
};

class CSU_DeepBase
{
public:
	virtual ~CSU_DeepBase();
protected:
	const CivilianSpawnUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;									// +0x08
};
class CSU_Iface1 { public: virtual void slot(); };
class CSU_Iface2 { public: virtual UpdateSleepTime update() = 0; };

class UpdateModule : public CSU_DeepBase, public CSU_Iface1, public CSU_Iface2
{
protected:
	Object *getObject() const { return m_object; }
	const CivilianSpawnUpdateModuleData *getCivilianSpawnUpdateModuleData() const { return m_moduleData; }
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class CivilianSpawnUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	UpdateSleepTime m_spawnFrame;						// +0x20
};

#define CIVILIAN_SPAWN_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\CivilianSpawnUpdate.cpp"

UpdateSleepTime CivilianSpawnUpdate::update()
{
	const CivilianSpawnUpdateModuleData *d = getCivilianSpawnUpdateModuleData();
	Object *obj = getObject();
	Int index = GetGameLogicRandomValue(0, (d->m_civilianFinish - d->m_civilianStart) - 1, CIVILIAN_SPAWN_FILE, 0x55);
	const ThingTemplate *unitTemplate = TheThingFactory->findTemplate(d->m_civilianStart[index]);
	if (!unitTemplate)
		return UPDATE_SLEEP_FOREVER;

	Rva0026119DFilter filterAlive;
	Rva002611BFFilter filterNotSelf(obj);
	Rva002614ECFilter filterObjects(&d->m_runToFilter, obj->getControllingPlayer(), true);
	filterAlive.link(&filterNotSelf);
	filterAlive.link(&filterObjects);
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), (Real)d->m_maximumDistance, 0, &filterAlive, 0);
	Int count = CivilianSpawnHitCount(iter);
	if (count == 0)
		return m_spawnFrame;

	UnsignedInt pick = GetGameLogicRandomValue(0, count - 1, CIVILIAN_SPAWN_FILE, 0x74);
	Object *runToObject = 0;
	for (UnsignedInt i = 0; i <= pick; ++i)
		runToObject = iter.next();

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Object *newObj = TheThingFactory->newObject(unitTemplate, getObject()->getTeam(), &mask, false);
	const Coord3D *dir = obj->getUnitDirectionVector2D();
	Coord3D pos;
	pos.x = dir->x;
	pos.y = dir->y;
	pos.z = dir->z;
	CivilianSpawnScale(pos, obj->getBoundingRadius() * 0.5);
	pos.x += obj->getPosition()->x;
	pos.y += obj->getPosition()->y;
	pos.z = obj->getPosition()->z;
	newObj->setPosition(&pos);

	AIUpdateInterface *ai = newObj->getAI();
	if (!ai)
		return UPDATE_SLEEP_FOREVER;
	ai->chooseLocomotorSet(4);
	newObj->setModelConditionState(MODELCONDITION_PANICKING);

	pos = *runToObject->getUnitDirectionVector2D();
	CivilianSpawnScale(pos, runToObject->getBoundingRadius() * 0.5);
	pos.x += runToObject->getPosition()->x;
	pos.y += runToObject->getPosition()->y;
	pos.z = runToObject->getPosition()->z;
	ai->ignoreObstacle(runToObject);
	TheAI->pathfinder()->rva003E3BFB(runToObject->getID());
	if (TheAI->pathfinder()->QuickDoesPathExist(newObj, newObj->getPosition(), &pos, 0))
		ai->m_commandInterface.aiMoveToPosition(&pos, CMD_FROM_AI);
	else
		TheGameLogic->destroyObject(newObj);
	TheAI->pathfinder()->rva003E3BFB(INVALID_OBJECT_ID);
	return m_spawnFrame;
}
