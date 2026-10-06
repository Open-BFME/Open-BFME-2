// cl: /DNDEBUG /MD /GX
//
// ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00460AEC,
// 91 bytes. Behavior-side base ctor (abstract: no instance factory; identity
// via the rowed RadarUpgrade behavior ctor 0x4B478E whose BFME1 donor calls
// UpgradeModule::UpgradeModule at this site, plus the four vtable slots
// +0/+0xC/+0x10/+0x18 documented by the SubObjectsUpgrade TU which derives
// from this base).
//
// Shape: single-state EH over the rowed BehaviorModule base 0x253330 (the
// base carries the declared-only dtor that arms the single state with zero
// emitted code; the UpgradeMux member at +0x10 has no dtor) plus explicit
// stores in retail order (Defector precedent: no virtuals declared anywhere
// so no vtable is emitted here; the first +0x18 store is volatile so the
// later overwrite does not dead-store-eliminate it).

extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00C57328[];  // folded, 41 classes; via ??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C57328=??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@")
extern "C" const void *const vtbl_00C58790[];  // folded, 55 classes; via ??_7AODHordeContain@@6BIface2C@@@
#pragma comment(linker, "/alternatename:_vtbl_00C58790=??_7AODHordeContain@@6BIface2C@@@")

extern "C" const void *const vtbl_00C42720[];  // ??_7UpgradeModule@@6BUpgradeMux@@@
#pragma comment(linker, "/alternatename:_vtbl_00C42720=??_7UpgradeModule@@6BUpgradeMux@@@")

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	~BehaviorModule();

private:
	unsigned char m_data[0x10];
};

class UpgradeMux
{
public:
	UpgradeMux();

private:
	void *m_vtable;
	unsigned int m_executed;
};

class UpgradeModule : public BehaviorModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

private:
	UpgradeMux m_mux;
	void *m_18;
};

// ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x00460AEC
UpgradeModule::UpgradeModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData), m_mux()
{
	*(void * volatile *)&m_18 = (void *)((unsigned int)vtbl_00BE2B78);
	*(void **)&m_mux = (void *)((unsigned int)vtbl_00C42720);
	*(void **)this = (void *)0x00C42768;
	*(void **)((char *)this + 0xC) = (void *)((unsigned int)vtbl_00C57328);
	m_18 = (void *)((unsigned int)vtbl_00C58790);
}
