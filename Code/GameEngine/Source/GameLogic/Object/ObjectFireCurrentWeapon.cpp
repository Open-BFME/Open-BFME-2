// cl: /O1 /DNDEBUG /MD
// ?fireCurrentWeapon@Object@@QAEXPAV1@H@Z, retail 0x00291873 (163 bytes).
// Identity (target): WorldBuilder's debug Object.cpp:3438 body
// Object::fireCurrentWeapon ("hey, we are firing but have no firing
// tracker. this is wrong.") calls, in retail's order,
// Object::setWeaponLock, Weapon::getStatus, Object::testStatus, the two
// Weapon fire wrappers (0x002CE74B, 0x002CE6C5), the firing tracker's
// 0x004DEECB and Object::releaseWeaponLock.
// Donor (Zero Hour Object::fireCurrentWeapon(Object *)): no target, no
// shot; fire the current weapon when READY_TO_FIRE, tell the firing tracker
// (+0x240), release the temporary lock, and clear the undetected-defector
// bit (0x02 of the private status at +0x438). BFME 2 deltas (target): a
// second argument handed to the fire wrapper and the tracker; a temporary
// lock on the current slot first when the weapon template's +0x16F flag is
// set; status 0x25 selects the other fire wrapper; and the lock is released
// when the template's +0x78 value is -1 rather than on reload.
//
// ?fireCurrentWeapon@Object@@QAEXPBUCoord3D@@@Z, retail 0x00291916 (145 bytes),
// the position overload, follows it in retail. Identity (target): the
// rowed caller 0x0034BFFF hands it the address of a Coord3D member, and the
// body is the sibling's shape over Weapon::fireWeapon(source, pos, NULL)
// (0x002CE6E8) instead of the object wrappers. Donor (Zero Hour
// Object::fireCurrentWeapon(const Coord3D *)): fire when READY_TO_FIRE,
// tell the tracker, release the temporary lock on reload, clear the
// defector bit. BFME 2 deltas (target): status 0x25 skips the shot, and the
// same +0x16F temporary lock; the tracker gets (weapon, 0, pos, 0).
// Layout (target): WeaponSet at +0x330 with its weapons at +0x338 and the
// current slot at +0x350; Weapon::m_template +0x04.
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_37 = 0x25
};

struct Coord3D;

enum ObjectPrivateStatusBits
{
	UNDETECTED_DEFECTOR = 0x02
};

class Object;

class WeaponTemplate
{
public:
	bool getLocksSlotWhenFiring() const { return m_flag16F; }
	int getValue78() const { return m_value78; }

private:
	unsigned char m_pad000[0x78];
	int m_value78; // +0x78
	unsigned char m_pad07C[0x16F - 0x7C];
	bool m_flag16F; // +0x16F
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	const WeaponTemplate *getTemplate() const { return m_template; }
	bool fireWeapon(const Object *source, const Coord3D *pos, int *reAcquire);
	bool rva002CE74B(const Object *source, const Object *target);
	bool rva002CE6C5(const Object *source, int fireParam, const Object *target, int *out);

private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};

class FiringTracker
{
public:
	void rva004DEECB(Weapon *weapon, int fireParam, int a, int b);
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

class Object
{
public:
	void fireCurrentWeapon(Object *target, int fireParam);
	void fireCurrentWeapon(const Coord3D *pos);
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void releaseWeaponLock(WeaponLockType lockType);
	bool testStatus(ObjectStatusTypes bit) const;
	void friend_setUndetectedDefector(bool status)
	{
		if (status)
			m_privateStatus |= UNDETECTED_DEFECTOR;
		else
			m_privateStatus &= ~UNDETECTED_DEFECTOR;
	}

private:
	unsigned char m_pad000[0x240];
	FiringTracker *m_firingTracker; // +0x240
	unsigned char m_pad244[0x330 - 0x244];
	WeaponSet m_weaponSet; // +0x330
	unsigned char m_pad354[0x438 - 0x354];
	unsigned char m_privateStatus; // +0x438
};

void Object::fireCurrentWeapon(Object *target, int fireParam)
{
	if (target == 0)
		return;

	Weapon *weapon = m_weaponSet.getCurWeapon();
	if (weapon)
	{
		if (weapon->getTemplate()->getLocksSlotWhenFiring())
			setWeaponLock(m_weaponSet.getCurWeaponSlot(), LOCKED_TEMPORARILY);
		if (weapon->getStatus() == READY_TO_FIRE)
		{
			if (testStatus(OBJECT_STATUS_37))
				weapon->rva002CE74B(this, target);
			else
				weapon->rva002CE6C5(this, fireParam, target, 0);
			if (m_firingTracker)
				m_firingTracker->rva004DEECB(weapon, fireParam, 0, 0);
			if (weapon->getTemplate()->getValue78() == -1)
				releaseWeaponLock(LOCKED_TEMPORARILY);
			friend_setUndetectedDefector(false);
		}
	}
}

void Object::fireCurrentWeapon(const Coord3D *pos)
{
	if (pos == 0)
		return;
	if (testStatus(OBJECT_STATUS_37))
		return;

	Weapon *weapon = m_weaponSet.getCurWeapon();
	if (weapon)
	{
		if (weapon->getTemplate()->getLocksSlotWhenFiring())
			setWeaponLock(m_weaponSet.getCurWeaponSlot(), LOCKED_TEMPORARILY);
		if (weapon->getStatus() == READY_TO_FIRE)
		{
			bool reloaded = weapon->fireWeapon(this, pos, 0);
			if (m_firingTracker)
				m_firingTracker->rva004DEECB(weapon, 0, (int)pos, 0);
			if (reloaded)
				releaseWeaponLock(LOCKED_TEMPORARILY);
			friend_setUndetectedDefector(false);
		}
	}
}
