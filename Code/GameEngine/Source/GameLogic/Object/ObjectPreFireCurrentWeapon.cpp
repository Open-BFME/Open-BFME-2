// cl: /O1 /DNDEBUG /MD
// ?preFireCurrentWeapon@Object@@QAEXPBV1@PBUCoord3D@@@Z, retail 0x002919A7
// (229 bytes).
// Identity (target): WorldBuilder's debug Object.cpp:3497 body
// Object::preFireCurrentWeapon calls, in retail's order,
// Object::setWeaponLock, Object::testStatus, the model-condition mask
// builder (0x000B6253), the Object condition call 0x001E42F2, the
// drawable's 0x00274176 and Weapon::preFireWeapon (WB-named, 0x002CDC3D).
// Donor (Zero Hour Object::preFireCurrentWeapon): the current weapon's
// preFireWeapon(this, victim). BFME 2 deltas (target): a target position
// argument; a temporary lock on the current slot when the weapon template's
// +0x16F flag is set; the last target's position and id (or the given
// position and no id) kept at +0x38C/+0x398; preFire only once the weapon
// can fire next frame (TheGameLogic frame +0x40 plus one against the
// weapon's +0x18 frame), after a model-condition update on the drawable
// (+0x84) unless status 0x4B; then the undetected-defector bit (0x02 at
// +0x438) is cleared as in fireCurrentWeapon.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_75 = 0x4B
};

enum ObjectPrivateStatusBits
{
	UNDETECTED_DEFECTOR = 0x02
};

class Object;

extern GameLogic *TheGameLogic;

class WeaponTemplate
{
public:
	bool getLocksSlotWhenFiring() const { return m_flag16F; }

private:
	unsigned char m_pad000[0x16F];
	bool m_flag16F; // +0x16F
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	unsigned int getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }
	void preFireWeapon(const Object *source, const Object *victim, const Coord3D *pos);

private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	unsigned int m_whenWeCanFireAgain; // +0x18
};

class WeaponSet
{
public:
	Weapon *getCurWeapon() const { return m_weapons[m_curWeapon]; }
	WeaponSlotType getCurWeaponSlot() const { return m_curWeapon; }

private:
	unsigned char m_pad00[0x08];
	Weapon *m_weapons[6]; // +0x08
	WeaponSlotType m_curWeapon; // +0x20
};

// The 0x4C-byte condition mask and its builder (memset then five bits).
class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int a, unsigned int b0, unsigned int b1, unsigned int b2,
		unsigned int b3, unsigned int b4);

private:
	unsigned char m_bits[0x4C];
};

class Drawable
{
public:
	void rva00274176(bool b);
};

class Object
{
public:
	void preFireCurrentWeapon(const Object *victim, const Coord3D *pos);
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	bool testStatus(ObjectStatusTypes bit) const;
	void rva001E42F2(const int *mask);
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	void friend_setUndetectedDefector(bool status)
	{
		if (status)
			m_privateStatus |= UNDETECTED_DEFECTOR;
		else
			m_privateStatus &= ~UNDETECTED_DEFECTOR;
	}

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x84 - 0x78];
	Drawable *m_drawable; // +0x84
	unsigned char m_pad088[0x330 - 0x88];
	WeaponSet m_weaponSet; // +0x330
	unsigned char m_pad354[0x38C - 0x354];
	Coord3D m_lastTargetPos; // +0x38C
	ObjectID m_lastTargetID; // +0x398
	unsigned char m_pad39C[0x438 - 0x39C];
	unsigned char m_privateStatus; // +0x438
};

void Object::preFireCurrentWeapon(const Object *victim, const Coord3D *pos)
{
	Weapon *weapon = m_weaponSet.getCurWeapon();
	if (weapon && weapon->getTemplate()->getLocksSlotWhenFiring())
		setWeaponLock(m_weaponSet.getCurWeaponSlot(), LOCKED_TEMPORARILY);

	if (victim)
	{
		m_lastTargetPos = *victim->getPosition();
		m_lastTargetID = victim->getID();
	}
	else if (pos)
	{
		m_lastTargetPos = *pos;
		m_lastTargetID = INVALID_OBJECT_ID;
	}

	if (weapon && TheGameLogic->getFrame() + 1 >= weapon->getPossibleNextShotFrame())
	{
		if (m_drawable && !testStatus(OBJECT_STATUS_75))
		{
			Rva000B6253 mask;
			rva001E42F2((const int *)mask.rva000B6253(0, 0x2A, 0x30, 0x36, 0x21C, 0x21D));
			m_drawable->rva00274176(false);
		}
		weapon->preFireWeapon(this, victim, pos);
		friend_setUndetectedDefector(false);
	}
}
