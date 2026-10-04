// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// Object::getLargestWeaponRange, retail 0x0028AE13 (90 bytes): Zero Hour's
// body unchanged except that BFME 2 walks six weapon slots. Target facts:
// the weapon set is at Object +0x330 (this+0x330 into the pinned
// WeaponSet::getWeaponInWeaponSlot, 0x002C7469), each weapon's range comes
// from the rowed Weapon::getAttackRange (0x002C9BF8) and the running best
// starts at -1.0f (0x00BBB9AC). Retail compares with fcompi, which MSVC 7.1
// emits only under /arch:SSE.
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};
class Object;
class Weapon
{
public:
	float getAttackRange(const Object *source) const;
};
class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};
class Object
{
public:
	float getLargestWeaponRange() const;
private:
	unsigned char m_pad000[0x330];
	WeaponSet m_weaponSet;		// +0x330
};
float Object::getLargestWeaponRange() const
{
	float retVal = -1;
	for (int i = PRIMARY_WEAPON; i < WEAPONSLOT_COUNT; ++i) {
		Weapon *weapon = m_weaponSet.getWeaponInWeaponSlot((WeaponSlotType)i);
		if (!weapon) {
			continue;
		}

		float tmpVal = weapon->getAttackRange(this);
		if (tmpVal > retVal) {
			retVal = tmpVal;
		}
	}
	return retVal;
}
