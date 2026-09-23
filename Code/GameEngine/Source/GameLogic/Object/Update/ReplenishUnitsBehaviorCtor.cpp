// cl: /O1 /DNDEBUG /MD /GX
//
// ??0ReplenishUnitsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00484227, 154 bytes. Behavior-side ctor (rowed instance factory
// 0x24C599 news 0x28 with this pinned 2-arg ctor as its sole raw caller
// at 0x24C5C0).
//
// Shape follows the RadiateFearUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, an UpgradeMux member at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), the
// object pointer homed early, the three derived vtable installs, a vtable
// overwrite of the member, and a conditional wake frame — the module data
// flag at +0x138 selects a GetGameLogicRandomValue call (rowed int twin
// 0x233FF4 over lo/hi/file/line with the TU __FILE__ literal and line
// 0x74) versus the never-wake literal, tail-merged into one setWakeFrame
// tail (protected IAEX Object-uint spelling resolves via the existing pin
// at 0x44DF71). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

struct ReplenishUnitsModuleData
{
	unsigned char m_pad00[0x134];
	Int m_134;
	bool m_138;
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

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class ReplenishUnitsBehavior : public UpdateModule
{
public:
	ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData);

private:
	UpgradeMux m_20;
};

// ??0ReplenishUnitsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00484227
ReplenishUnitsBehavior::ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_20()
{
	Object *obj = m_object;
	m_vtable = (const void *)0x00C4A034;
	m_secondary0C = (const void *)0x00C49F78;
	m_secondary10 = (const void *)0x00C49F68;
	*(void **)&m_20 = (void *)0x00C49F20;
	if (((const ReplenishUnitsModuleData *)m_moduleData)->m_138)
	{
		m_20.giveSelfUpgrade();
		int hi = ((const ReplenishUnitsModuleData *)m_moduleData)->m_134;
		setWakeFrame(obj, GetGameLogicRandomValue(1, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\ReplenishUnitsBehavior.cpp", 0x74));
	}
	else
	{
		setWakeFrame(obj, 0x3FFFFFFF);
	}
}
