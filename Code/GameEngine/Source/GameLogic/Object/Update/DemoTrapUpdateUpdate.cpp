// cl: /DNDEBUG /MD /EHsc
// ?update@DemoTrapUpdate@@UAE?AW4UpdateSleepTime@@XZ 0x00495ABA 360B
// DemoTrapUpdate::update via ZH DemoTrapUpdate.cpp update plus BFME1
// game/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp wide-result
// shape. ModuleData offsets (+0x28/+0x2c/+0x34/+0x38/+0x3d/+0x3e/+0x0c) and
// DemoTrapUpdate members (+0x20/+0x24) match rowed DemoTrapUpdateModuleDataCtor
// and DemoTrapUpdateConstructor. Detonate helper is rowed 0x00495A2B.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectStatusTypes
{
	STATUS_UNDER_CONSTRUCTION = 2,
	STATUS_SOLD = 0x13
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum Relationship
{
	RELATIONSHIP_ENEMIES = 0
};
template <int N>
class BitFlags
{
public:
	unsigned int m_bits[7];
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Weapon
{
public:
	unsigned char m_pad00[0x0c];
	WeaponSlotType m_slot;
};
class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
	bool isAboveTerrain() const;
};
class Object : public Thing
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Relationship getRelationship(const Object *other) const;
	unsigned char m_pad00[0x38];
	Coord3D m_pos38;
	unsigned char m_pad44[0x438 - 0x44];
	unsigned char m_dead438;
};
class Rva000CBA20Point
{
public:
	float x;
	float y;
};
#include "../../../Common/RTS/XYDistanceCallView.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;
class Rva00495A2B
{
public:
	void rva00495A2B();
};
class DemoTrapUpdateModuleData
{
public:
	void *m_vtable;
	unsigned int m_unused04;
	void *m_detonationWeapon;
	BitFlags<69> m_ignoreKindOf;
	int m_manualModeWeaponSlot;
	int m_detonationWeaponSlot;
	int m_proximityModeWeaponSlot;
	float m_triggerDetonationRange;
	int m_scanFrames;
	bool m_defaultsToProximityMode;
	bool m_friendlyDetonation;
	bool m_detonateWhenKilled;
};
class DemoTrapUpdate
{
public:
	virtual UpdateSleepTime update();
	const DemoTrapUpdateModuleData *getDemoTrapUpdateModuleData() const
	{
		return *(const DemoTrapUpdateModuleData **)((const char *)this - 0x0c);
	}
	Object *getObject() const
	{
		return *(Object **)((const char *)this - 0x08);
	}
private:
	unsigned char m_pad00[0x0c];
	int m_nextScanFrames;
	bool m_detonated;
};
UpdateSleepTime DemoTrapUpdate::update()
{
	register DemoTrapUpdate *self = this;
	const DemoTrapUpdateModuleData *data = self->getDemoTrapUpdateModuleData();
	if (self->m_detonated)
		return UPDATE_SLEEP_NONE;
	Object *me = self->getObject();
	if (me->testStatus(STATUS_UNDER_CONSTRUCTION))
		return UPDATE_SLEEP_NONE;
	if (me->testStatus(STATUS_SOLD))
		return UPDATE_SLEEP_NONE;
	if ((me->m_dead438 & 1) != 0)
	{
		if (!data->m_detonateWhenKilled)
			return UPDATE_SLEEP_NONE;
		((Rva00495A2B *)((char *)self - 0x10))->rva00495A2B();
		return UPDATE_SLEEP_NONE;
	}
	const Weapon *weapon = me->getCurrentWeapon(0);
	WeaponSlotType weaponSlot = weapon->m_slot;
	if (weaponSlot == data->m_detonationWeaponSlot)
	{
		((Rva00495A2B *)((char *)self - 0x10))->rva00495A2B();
		return UPDATE_SLEEP_NONE;
	}
	if (self->m_nextScanFrames > 0)
	{
		--self->m_nextScanFrames;
		return UPDATE_SLEEP_NONE;
	}
	if (weaponSlot == data->m_manualModeWeaponSlot)
		return UPDATE_SLEEP_NONE;
	self->m_nextScanFrames = data->m_scanFrames;
	bool shallDetonate = false;
	BfmeWideResult iterator = ThePartitionManager->rva006255D0(&me->m_pos38, data->m_triggerDetonationRange, 0, 0);
	for (Object *other = iterator.next(); other; other = iterator.next())
	{
		if (other->isAnyKindOf(data->m_ignoreKindOf))
			continue;
		if ((other->m_dead438 & 1) != 0)
			continue;
		if (self->getObject()->getRelationship(other) != RELATIONSHIP_ENEMIES)
		{
			if (!data->m_friendlyDetonation)
				return UPDATE_SLEEP_NONE;
			continue;
		}
		if (other->isAboveTerrain())
			continue;
		float dist = ((Rva000CBA20 *)me)->distSq((const Rva000CBA20Point *)&other->m_pos38);
		if (dist <= data->m_triggerDetonationRange * data->m_triggerDetonationRange)
		{
			shallDetonate = true;
			if (data->m_friendlyDetonation)
				break;
		}
	}
	if (shallDetonate)
		((Rva00495A2B *)((char *)self - 0x10))->rva00495A2B();
	return UPDATE_SLEEP_NONE;
}
