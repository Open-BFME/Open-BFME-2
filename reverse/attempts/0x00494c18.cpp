// ?update@WeaponModeSpecialPowerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.95 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// WeaponModeSpecialPowerUpdate::update, retail 0x00494C18 (105 bytes): slot
// 0 of the class's +0x10 update-module interface table 0x00C4E988, so `this`
// is that subobject (module data at -0x0C, Object at -0x08). Ends the weapon
// mode: weapon lock 2 released, every weapon-set flag the module data lists
// at +0x24 (0x68 of them) cleared on the Object, the data's +0x18 name, when
// set, handed to Object 0x0028EB42 (the pinned removal twin of
// rva0028EA91), the active byte (+0x38) cleared and the executed flag of the
// upgrade mux at +0x24 cleared (its slot 9); then the module sleeps forever.
typedef bool Bool;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum WeaponLockType
{
	WEAPON_LOCK_BFME_2 = 2
};
enum WeaponSetType
{
	WEAPONSET_NONE = 0,
	WEAPONSET_COUNT = 0x68
};
class StringBase;
class AsciiString
{
public:
	Bool isEmpty() const;
private:
	void *m_data;
};
class Object
{
public:
	void releaseWeaponLock(WeaponLockType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void rva0028EB42(const AsciiString &name);
};
template <int N> class BitFlags
{
public:
	__forceinline Bool test(unsigned int i) const { return (m_bits[i >> 5] & (1 << (i & 0x1f))) != 0; }
private:
	unsigned int m_bits[(N + 31) / 32];
};
struct WeaponModeSpecialPowerUpdateModuleData
{
	unsigned char m_pad00[0x18];
	AsciiString m_name;			// +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	BitFlags<WEAPONSET_COUNT> m_weaponSetFlags;	// +0x24
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned char m_pad14[0x24 - 0x14];
};
class UpgradeMux
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08();
	virtual void setUpgradeExecuted(Bool executed);
};
class WeaponModeSpecialPowerUpdate : public UpdateModule, public UpgradeMux
{
public:
	virtual UpdateSleepTime update();
	const WeaponModeSpecialPowerUpdateModuleData *getData() const
	{
		return (const WeaponModeSpecialPowerUpdateModuleData *)m_moduleData;
	}
private:
	unsigned char m_pad28[0x38 - 0x28];
	Bool m_active;			// +0x38
};
UpdateSleepTime WeaponModeSpecialPowerUpdate::update()
{
	Object *obj = m_object;
	obj->releaseWeaponLock(WEAPON_LOCK_BFME_2);
	for (int i = 0; i < WEAPONSET_COUNT; ++i)
	{
		if (getData()->m_weaponSetFlags.test(i))
			obj->clearWeaponSetFlag((WeaponSetType)i);
	}
	const AsciiString &name = getData()->m_name;
	if (!name.isEmpty())
		obj->rva0028EB42(name);
	m_active = false;
	setUpgradeExecuted(false);
	return UPDATE_SLEEP_FOREVER;
}
