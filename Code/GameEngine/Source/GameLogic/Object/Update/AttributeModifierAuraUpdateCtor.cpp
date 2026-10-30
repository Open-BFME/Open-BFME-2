// cl: /DNDEBUG /MD /GX
//
// ??0AttributeModifierAuraUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0049B560, 118 bytes. Behavior-side ctor (rowed instance factory
// 0x24E624 news 0x28 with this pinned 2-arg ctor as its sole raw caller
// at 0x24E64B).
//
// Shape follows the RadiateFearUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, an UpgradeMux member at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), the
// setWakeFrame arg pushes above the stores (no intervening call), the
// three derived vtable installs, a vtable overwrite of the member, the
// setWakeFrame tail (protected IAEX Object-uint spelling resolves via the
// existing pin at 0x44DF71), and a conditional self-upgrade on the module
// data flag at +0x138 (rowed giveSelfUpgrade 0x45230C). Row supersedes the
// ctor pin.

extern "C" const void *const __identifier("??_7AttributeModifierAuraUpdate@@6BObjectModule@@@")[];  // vftable 0x00C50D2C, as the dtor unit names it after its canonical ObjectModule base

extern "C" const void *const __identifier("??_7AttributeModifierAuraUpdate@@6BUpdateModuleInterface@@@")[];  // vftable 0x00C50D20

extern "C" const void *const __identifier("??_7AttributeModifierAuraUpdate@@6B@")[];  // vftable 0x00C50CD8

extern "C" const void *const __identifier("??_7AttributeModifierAuraUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C49F78 (3 classes), by its data-ledger name

class Thing;
class ModuleData;
class Object;

struct AttributeModifierAuraUpdateModuleData
{
	unsigned char m_pad00[0x138];
	bool m_startsActive;
};

class UpgradeMux
{
public:
	UpgradeMux();
	void giveSelfUpgrade();

private:
	void *m_vtable;
	unsigned int m_executed;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class AttributeModifierAuraUpdate : public UpdateModule
{
public:
	AttributeModifierAuraUpdate(Thing *thing, const ModuleData *moduleData);

private:
	UpgradeMux m_20;
};

// ??0AttributeModifierAuraUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049B560
AttributeModifierAuraUpdate::AttributeModifierAuraUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_20()
{
	m_vtable = (const void *)((unsigned int)__identifier("??_7AttributeModifierAuraUpdate@@6BObjectModule@@@"));
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7AttributeModifierAuraUpdate@@6BBehaviorModuleInterface@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7AttributeModifierAuraUpdate@@6BUpdateModuleInterface@@@"));
	*(void **)&m_20 = (void *)((unsigned int)__identifier("??_7AttributeModifierAuraUpdate@@6B@"));
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	const AttributeModifierAuraUpdateModuleData *data = (const AttributeModifierAuraUpdateModuleData *)m_moduleData;
	if (data->m_startsActive)
		m_20.giveSelfUpgrade();
}
