// cl: /O1 /DNDEBUG /MD /G7
// ?rva0034BE57@AIRampageState@@QAEXPAVObject@@@Z @0x0034BE57 108B
// Helper called by AIRampageState::update slot 6 (0x0034FE10) with the owner.
// Weapon-status gate on flag +0x20 (same bool as AIRampageState::onEnter
// 0x0034BD1B +0x20): needs current weapon via rowed getCurrentWeapon and its
// rowed getStatus; READY (0) with flag clear sets status 0xD and the flag,
// with flag set runs rowed rva0028FC8F plus pinned rva00291916 on +0x38;
// PRE_ATTACK (4) keeps the flag, status 5 clears it.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1,
	BETWEEN_FIRING_SHOTS = 2,
	RELOADING_CLIP = 3,
	PRE_ATTACK = 4,
	WEAPON_STATUS_5 = 5
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_D = 0x0D
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void rva0028FC8F();
	// Native 0x00291916, the verified position overload in ObjectFireCurrentWeapon.cpp.
	void fireCurrentWeapon(const Coord3D *position);
	void setStatus(ObjectStatusTypes status, bool set);
private:
	unsigned char m_pad00[0x38];
public:
	Coord3D m_pos; // +0x38
};

class AIRampageState
{
public:
	void rva0034BE57(Object *obj);
private:
	unsigned char m_pad00[0x20];
	bool m_flag20; // +0x20
};

void AIRampageState::rva0034BE57(Object *obj)
{
	WeaponSlotType slot = WEAPONSLOT_PRIMARY;
	const Weapon *weapon = obj->getCurrentWeapon(&slot);
	if (!weapon)
		return;
	WeaponStatus status = weapon->getStatus();
	if (m_flag20)
	{
		if (status == PRE_ATTACK)
			return;
		if (status == READY_TO_FIRE)
		{
			obj->rva0028FC8F();
			obj->fireCurrentWeapon(&obj->m_pos);
			return;
		}
		if (status != WEAPON_STATUS_5)
			return;
		m_flag20 = false;
		return;
	}
	if (status != READY_TO_FIRE)
		return;
	m_flag20 = true;
	obj->setStatus(OBJECT_STATUS_D, true);
}
