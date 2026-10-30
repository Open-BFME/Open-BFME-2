// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Source/Common /Ireference/shims/bfme2_ascii
// Ends the active weapon mode and puts the module to sleep.

class Thing;
class ModuleData;
class Xfer;
class MultiIniFieldParse;
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
enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "ascii_string.h"
class Object
{
public:
	void releaseWeaponLock(WeaponLockType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void removeAttributeModifierFromPool(const AsciiString &name);
};
template <int N> class BitFlags
{
public:
	__forceinline Bool test(unsigned int i) const { return (m_bits[i >> 5] & (1 << (i & 0x1f))) != 0; }
private:
	unsigned int m_bits[(N + 31) / 32];
};
class WeaponModeSpecialPowerUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	unsigned char m_pad00[0x18];
	AsciiString m_name;			// +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	BitFlags<WEAPONSET_COUNT> m_weaponSetFlags;	// +0x24
};
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class Rva00589079_E1
{
public:
	virtual void fe();
};

class Rva00589079_E2
{
public:
	virtual void fe();
	virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08();
	virtual void setUpgradeExecuted(Bool executed);
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class WeaponModeSpecialPowerUpdate : public Rva00589079
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	const WeaponModeSpecialPowerUpdateModuleData *getData() const
	{
		return (const WeaponModeSpecialPowerUpdateModuleData *)m_moduleData;
	}

private:
	Bool m_38;
};

// WeaponModeSpecialPowerUpdate::update, retail 0x00494C18 (105 bytes): slot
// 0 of the class's +0x10 update-module interface table 0x00C4E988, so `this`
// is that subobject (module data at -0x0C, Object at -0x08). Ends the weapon
// mode: weapon lock 2 released, every weapon-set flag the module data lists
// at +0x24 (0x68 of them) cleared on the Object, the data's +0x18 name, when
// set, handed to Object 0x0028EB42 (the pinned removal twin of
// rva0028EA91), the active byte (+0x38) cleared and the executed flag of the
// upgrade mux at +0x24 cleared (its slot 9); then the module sleeps forever.
// Codegen: the module data pointer is a named local (not a reference to the
// name and not getData() twice), which keeps the Object pointer in EDI and the
// weapon-set index in EBX as retail does.
UpdateSleepTime WeaponModeSpecialPowerUpdate::update()
{
	Object *obj = m_object;
	obj->releaseWeaponLock(WEAPON_LOCK_BFME_2);
	for (int i = 0; i < WEAPONSET_COUNT; ++i)
	{
		if (getData()->m_weaponSetFlags.test(i))
			obj->clearWeaponSetFlag((WeaponSetType)i);
	}
	const WeaponModeSpecialPowerUpdateModuleData *data = getData();
	if (!data->m_name.isEmpty())
		obj->removeAttributeModifierFromPool(data->m_name);
	m_38 = false;
	setUpgradeExecuted(false);
	return UPDATE_SLEEP_FOREVER;
}
