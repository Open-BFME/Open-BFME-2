// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?action@RepairDockUpdate@@UAE_NPAVObject@@0@Z, retail 0x004A12B6 (201 bytes,
// RET 8). RepairDockUpdate::action (Zero Hour's body, BFME 2 layout), slot 12
// of the DockUpdateInterface vtable 0x00851C30 at +0x20 of the update, so it is
// compiled with that subobject this (module data at this-0x1C, owner at
// this-0x18, last repaired docker id at the update's +0x88 and the per-frame
// heal at +0x8C, the fields the rowed ctor clears and xfer 0x004A1255 saves): a null docker is refused; for a new docker the health to add
// per frame becomes (max - health) / data+0x10 (body slots 6 and 4: max and
// current health); at full health the last docker is cleared and the dock
// finishes (false); otherwise a 0x7C DamageInfo (constructor 0x00263895: damage
// type 7 healing at +0x10, death type 1 at +0x1C, amount +0x20, source id +0x08)
// heals the docker through body slot 1 and a drone, if given, up to its max
// health.
#include "RepairDockUpdateView.h"

class DamageInfoInput
{
public:
	char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	char m_pad0C[0x10 - 0x0C];
	int m_damageType; // +0x10
	char m_pad14[0x1C - 0x14];
	int m_deathType; // +0x1C
	float m_amount; // +0x20
};

class DamageInfo
{
public:
	DamageInfo();
	DamageInfoInput in;
	char m_pad24[0x7C - 0x24];
};

class Rva00263895Member
{
public:
	Rva00263895Member();
	DamageInfoInput in;
	char m_pad24[0x7C - 0x24];
};

enum
{
	DAMAGE_HEALING = 7,
	DEATH_NONE = 1
};

#include "../../../../Include/GameLogic/Module/BodyModule.h"

class Object
{
public:
	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	char m_pad00[0x74];
	ObjectID m_id; // +0x74
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
};

bool RepairDockUpdate::action(Object *docker, Object *drone)
{
	if (docker == 0)
		return false;

	const RepairDockUpdateModuleData *modData = getRepairDockUpdateModuleData();
	BodyModuleInterface *body = docker->getBodyModule();

	if (m_lastRepair == 0)
	{
		m_lastRepair = docker->getID();
		m_healthToAddPerFrame = (body->getMaxHealth() - body->getHealth()) / modData->m_framesForFullHeal;
	}

	if (body->getHealth() >= body->getMaxHealth())
	{
		m_lastRepair = INVALID_ID;
		return false;
	}

	Rva00263895Member healingInfo;
	healingInfo.in.m_amount = m_healthToAddPerFrame;
	healingInfo.in.m_sourceID = m_object->getID();
	healingInfo.in.m_damageType = DAMAGE_HEALING;
	healingInfo.in.m_deathType = DEATH_NONE;
	body->attemptHealing((DamageInfo *)&healingInfo);
	if (drone)
	{
		body = drone->getBodyModule();
		healingInfo.in.m_amount = body->getMaxHealth();
		body->attemptHealing((DamageInfo *)&healingInfo);
	}

	return true;
}
