// cl: /DNDEBUG /MD /GX
//
// ??0AutoHealBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00452592,
// 189 bytes. Behavior-side ctor (rowed instance factory 0x24A8DC news
// 0x38 with this pinned 2-arg ctor as its sole raw caller at 0x24A903).
//
// Shape follows the ReplenishUnitsBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, an UpgradeMux member at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), a
// two-phase +0x28 slot via sourced-before address-take, an and-zero at
// +0x2C, a module-data byte (+0x119) copied to +0x30, an and-zero at
// +0x34, and a conditional wake frame — the module data flag at +0x118
// selects a GetGameLogicRandomValue call (rowed int twin 0x233FF4 over
// lo/hi/file/line with the TU __FILE__ literal and line 0x9D) versus the
// never-wake literal, tail-merged into one setWakeFrame tail (protected
// IAEX Object-uint spelling resolves via the existing pin at 0x44DF71).
// Row supersedes the ctor pin.

extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00C495A0[];  // folded, 2 classes; via ??_7FireWeaponWhenDamagedBehavior@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00C495A0=??_7FireWeaponWhenDamagedBehavior@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C3FC78[];  // ??_7Rva0045232D@@6BRva0045232D_E2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C3FC78=??_7Rva0045232D@@6BRva0045232D_E2@@@")
extern "C" const void *const vtbl_00C3FC88[];  // ??_7Rva0045232D@@6BRva0045232D_E1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C3FC88=??_7Rva0045232D@@6BRva0045232D_E1@@@")
extern "C" const void *const vtbl_00C3FCD0[];  // ??_7Rva0045232D@@6BRva0024A797_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C3FCD0=??_7Rva0045232D@@6BRva0024A797_B2@@@")
extern "C" const void *const vtbl_00C3FCDC[];  // ??_7Rva0045232D@@6BRva0024A797_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C3FCDC=??_7Rva0045232D@@6BRva0024A797_Root@@@")

class Thing;
class ModuleData;
class Object;

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

struct AutoHealBehaviorModuleData
{
	unsigned char m_pad00[0x118];
	bool m_118;
	unsigned char m_119;
	Int m_11C;
	Int m_120;
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

class AutoHealBehavior : public UpdateModule
{
public:
	AutoHealBehavior(Thing *thing, const ModuleData *moduleData);

private:
	UpgradeMux m_20;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned char m_30;
	unsigned int m_34;
};

// ??0AutoHealBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00452592
AutoHealBehavior::AutoHealBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_20()
{
	int *slot28 = (int *)&m_28;
	*slot28 = (int)((unsigned int)vtbl_00BE2B78);
	const AutoHealBehaviorModuleData *data = (const AutoHealBehaviorModuleData *)m_moduleData;
	m_2C &= 0;
	m_vtable = (const void *)((unsigned int)vtbl_00C3FCDC);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C495A0);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C3FCD0);
	*(void **)&m_20 = (void *)((unsigned int)vtbl_00C3FC88);
	m_28 = (unsigned int)((unsigned int)vtbl_00C3FC78);
	m_30 = data->m_119;
	m_34 &= 0;
	if (data->m_118)
	{
		m_20.giveSelfUpgrade();
		int hi = ((const AutoHealBehaviorModuleData *)m_moduleData)->m_120;
		Object *obj = m_object;
		setWakeFrame(obj, (UpdateSleepTime)(GetGameLogicRandomValue(1, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\AutoHealBehavior.cpp", 0x9D)));
	}
	else
	{
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
	}
}
