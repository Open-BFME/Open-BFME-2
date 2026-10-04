// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// WeaponFireSpecialAbilityUpdate slot 8 of its +0x20 interface table
// 0x00C4E05C (installed by the ctors 0x00492590 and 0x0049274A), retail
// 0x004929D1 (161 bytes), so `this` is that subobject (the Object at -0x18,
// the Weapon at +0x68). No Weapon: false. A null target position goes
// straight to the SpecialAbilityUpdate +0x20 slot-8 base 0x0044EDA6;
// otherwise the position must lie no nearer than the Weapon's minimum range
// (0x002C957E) by the Object's shrunken distance 0x002C97E8 and, when bit 2
// of the Object template's +0x108 byte is set, within its attack range less
// 2.5 (0x002C9BF8), before the base decides. Named by the base's address,
// like GiveUpgradeUpdateSlot8.cpp.
typedef bool Bool;
typedef float Real;
struct Coord3D
{
	Real x, y, z;
};
struct Rva004929D1Template
{
	unsigned char m_pad000[0x108];
	unsigned char m_108; // +0x108
};
class Object
{
public:
	Real rva002C97E8(const Coord3D *from, const Coord3D *to) const;
	unsigned char m_pad000[0x04];
	const Rva004929D1Template *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_38; // +0x38
};
class Weapon
{
public:
	Real rva002C957E() const;
	Real getAttackRange(const Object *source) const;
};
class ModuleData;
class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};
class SpecialPowerUpdateInterface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual Bool rva0044EDA6(int value);
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual Bool rva0044EDA6(int value);
};
class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool rva0044EDA6(int value);
private:
	unsigned char m_pad24[0x88 - 0x24];
	Weapon *m_88; // +0x88
};
Bool WeaponFireSpecialAbilityUpdate::rva0044EDA6(int value)
{
	Weapon *weapon = m_88;
	if (weapon == 0)
		return false;
	if (value == 0)
		return SpecialAbilityUpdate::rva0044EDA6(value);
	Object *obj = m_object;
	if (obj == 0)
		return false;
	const Coord3D *pos = (const Coord3D *)value;
	Real minRange = weapon->rva002C957E();
	if (obj->rva002C97E8(&obj->m_38, pos) < minRange * minRange)
		return false;
	if (obj->m_template->m_108 & 4)
	{
		Real range = m_88->getAttackRange(obj);
		range -= 2.5f;
		if (obj->rva002C97E8(&obj->m_38, pos) > range * range)
			return false;
	}
	return SpecialAbilityUpdate::rva0044EDA6(value);
}
