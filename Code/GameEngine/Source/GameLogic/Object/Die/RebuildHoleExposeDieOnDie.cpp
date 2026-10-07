// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?onDie@RebuildHoleExposeDie@@UAEXPBVDamageInfo@@@Z, retail 0x004867FE,
// 434 bytes: slot 0 of the +0x10 DieModuleInterface table 0x00C4AE50 the
// rowed RebuildHoleExposeDie ctor (0x00486768) stores, between the rowed
// deleting dtor 0x004867DD and the module data's 0x004869B0. Zero Hour's
// GameLogic/Object/Die/RebuildHoleExposeDie.cpp onDie (reference/open-bfme-1/
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/...) in the same order:
// isDieApplicable, the neutral/active/under-construction gate, newObject of
// the HoleName template, position, orientation, geometry, script name,
// pathfind map, hole max health, the rebuild-hole interface's
// startRebuildProcess and the TransferAttackers loop.
//
// BFME 2 deltas, read from retail:
// - newObject takes a zeroed 16-byte create mask by address and a false bool;
//   the team is the inline Object +0x304 read; findTemplate takes the
//   module data's HoleName AsciiString (+0x38).
// - Before adding the hole the dying object is removed from the pathfind map.
// - setMaxHealth (body slot 22) takes a second argument, 0.
// - When the object has a spawn behavior, the hole interface's slot 4 takes
//   that interface's slot 11 byte (a Bool getter) before startRebuildProcess.
// - FadeInTimeSeconds (+0x40) > 0 fades the hole's drawable in over that
//   many logic frames (the frame-rate int g_009BA4E8 times the seconds).
#include "../../../Common/GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include <string.h>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

extern int g_009BA4E8;

enum MaxHealthChangeType
{
	SAME_CURRENTHEALTH = 0
};

class Team;
class ThingTemplate;
class DamageInfo;
class ModuleData;
class Thing;
struct BfmeCopyElementA;

struct Coord3D;

class Player
{
public:
	Bool isPlayerActive() const;	// 0x002AA231
};

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return m_neutralPlayer; }

private:
	unsigned char m_pad00[0x18];
	Player *m_neutralPlayer;	// +0x18
};
extern PlayerList *ThePlayerList;

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }

	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;

template <int N> class RebuildHoleBodySlots : public RebuildHoleBodySlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class RebuildHoleBodySlots<0>
{
};

// BodyModuleInterface (Object +0x254): slot 22 setMaxHealth.
class BodyModuleInterface : public RebuildHoleBodySlots<22>
{
public:
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType) = 0;
};

// SpawnBehaviorInterface table 0x00C425AC: slot 11 is a byte getter.
class SpawnBehaviorInterface : public RebuildHoleBodySlots<11>
{
public:
	virtual Bool getSlot11Flag() = 0;
};

// The RebuildHoleBehavior +0x24 interface table 0x00C49A50: slot 0
// startRebuildProcess (0x004835B4), slot 4 a byte setter.
class RebuildHoleBehaviorInterface
{
public:
	virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID) = 0;
	virtual ObjectID getSpawnerID() = 0;
	virtual ObjectID getReconstructedBuildingID() = 0;
	virtual const ThingTemplate *getRebuildTemplate() const = 0;
	virtual void setSlot4Flag(Bool flag) = 0;
};

class RebuildHoleBehavior
{
public:
	static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *obj);
};

class AIUpdateInterface
{
public:
	void transferAttack(ObjectID fromID, ObjectID toID);
};

class Drawable
{
public:
	void fadeIn(UnsignedInt frames);
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	Drawable *getDrawable() const;	// 0x005508E2
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	void rva0029895A(BfmeCopyElementA *geom);	// 0x0029895A, setGeometryInfo

	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return (const Coord3D *)m_pos; }
	Real getOrientation() const { return m_orientation; }
	ObjectID getID() const { return m_id; }
	const AsciiString &getName() const { return m_name; }
	Object *getNextObject() const { return m_next; }
	Bool testStatusUnderConstruction() const { return (m_status >> 2) & 1; }
	BfmeCopyElementA *getGeometryInfo() { return (BfmeCopyElementA *)m_geometryInfo; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Real m_pos[3];	// +0x38
	Real m_orientation;	// +0x44
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id;	// +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name;	// +0x88
	Object *m_next;	// +0x8C
	unsigned char m_pad090[0x94 - 0x90];
	unsigned int m_status;	// +0x94
	unsigned char m_pad098[0xA8 - 0x98];
	unsigned char m_geometryInfo[0x14];	// +0xA8
	unsigned char m_pad0BC[0x254 - 0xBC];
	BodyModuleInterface *m_body;	// +0x254
	AIUpdateInterface *m_ai;	// +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team;	// +0x304
};

class ScriptEngine
{
public:
	void rva00357960(const AsciiString &name, Object *obj);	// 0x00357960, transferObjectName
};
extern ScriptEngine *TheScriptEngine;

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
	void AddObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

extern GameLogic *TheGameLogic;

class RebuildHoleExposeDieModuleData
{
public:
	unsigned char m_dieModuleData[0x38];	// DieModuleData
	AsciiString m_holeName;	// +0x38
	Real m_holeMaxHealth;	// +0x3C
	Real m_fadeInTimeSeconds;	// +0x40
	Bool m_transferAttackers;	// +0x44
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieModule : public ObjectModule, public BehaviorModuleInterface, public DieModuleInterface
{
protected:
	Bool isDieApplicable(const DamageInfo *damageInfo) const;
};

class RebuildHoleExposeDie : public DieModule
{
public:
	virtual void onDie(const DamageInfo *damageInfo);

private:
	const RebuildHoleExposeDieModuleData *getRebuildHoleExposeDieModuleData() const
	{
		return (const RebuildHoleExposeDieModuleData *)getModuleData();
	}
};

// ?onDie@RebuildHoleExposeDie@@UAEXPBVDamageInfo@@@Z
void RebuildHoleExposeDie::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;

	const RebuildHoleExposeDieModuleData *modData = getRebuildHoleExposeDieModuleData();
	Object *us = getObject();

	//
	// if we are being constructed from either the first time or from a hole reconstruction
	// we do not "spawn" a hole object
	//
	if (us->getControllingPlayer() != ThePlayerList->getNeutralPlayer()
		&& us->getControllingPlayer()->isPlayerActive()
		&& !us->testStatusUnderConstruction())
	{
		Object *hole;
		CreateMask mask;

		// create the hole
		hole = TheThingFactory->newObject(TheThingFactory->findTemplate(modData->m_holeName),
			us->getTeam(), &mask, false);

		// put the hole at our position and angle
		hole->setPosition(us->getPosition());
		hole->setOrientation(us->getOrientation());

		// keep our extents for the rebuilding process
		hole->rva0029895A(us->getGeometryInfo());

		// transfer the building's name to the hole
		TheScriptEngine->rva00357960(us->getName(), hole);

		TheAI->pathfinder()->RemoveObjectFromPathfindMap(us);
		TheAI->pathfinder()->AddObjectToPathfindMap(hole);

		// set the health of the hole to that defined by our data
		BodyModuleInterface *body = hole->getBodyModule();
		body->setMaxHealth(modData->m_holeMaxHealth, SAME_CURRENTHEALTH);

		// set the information in the hole about what to build
		RebuildHoleBehaviorInterface *rhbi = RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject(hole);

		// start the rebuild process
		if (rhbi)
		{
			SpawnBehaviorInterface *spawn = us->getSpawnBehaviorInterface();
			if (spawn)
				rhbi->setSlot4Flag(spawn->getSlot11Flag());
			rhbi->startRebuildProcess(us->getTemplate(), us->getID());
		}

		if (modData->m_transferAttackers)
		{
			for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
			{
				AIUpdateInterface *ai = obj->getAI();
				if (!ai)
					continue;

				ai->transferAttack(us->getID(), hole->getID());
			}
		}

		if (modData->m_fadeInTimeSeconds > 0.0f)
			hole->getDrawable()->fadeIn(g_009BA4E8 * modData->m_fadeInTimeSeconds);
	}
}
