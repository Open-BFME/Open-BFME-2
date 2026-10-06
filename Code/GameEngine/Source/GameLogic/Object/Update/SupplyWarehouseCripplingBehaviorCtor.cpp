// cl: /DNDEBUG /MD /GX
//
// ??0SupplyWarehouseCripplingBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00483A8B, 105 bytes. Behavior-side ctor (rowed instance
// factory 0x24C484 news 0x2C with this pinned 2-arg ctor as its sole raw
// caller at 0x24C4AB).
//
// Shape follows the OneRingPenaltyUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// eax-homed int zero, the setWakeFrame arg pushes hoisted above the
// stores (no intervening call), the three derived vtable installs, zeros
// at +0x24/+0x28, and the setWakeFrame tail (protected IAEX Object-uint
// spelling resolves via the existing pin at 0x44DF71). Row supersedes the
// ctor pin.

extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00C49800[];  // folded, 4 classes; via ??_7FlammableUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00C49800=??_7FlammableUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C49AAC[];  // ??_7Rva004839D3@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C49AAC=??_7Rva004839D3@@6B@")
extern "C" const void *const vtbl_00C49AB8[];  // ??_7Rva004839D3@@6BRva0024A797_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C49AB8=??_7Rva004839D3@@6BRva0024A797_B2@@@")
extern "C" const void *const vtbl_00C49AC8[];  // ??_7Rva004839D3@@6BRva0024A797_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C49AC8=??_7Rva004839D3@@6BRva0024A797_Root@@@")

class Thing;
class ModuleData;
class Object;

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

class SupplyWarehouseCripplingBehavior : public UpdateModule
{
public:
	SupplyWarehouseCripplingBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
};

// ??0SupplyWarehouseCripplingBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00483A8B
SupplyWarehouseCripplingBehavior::SupplyWarehouseCripplingBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)((unsigned int)vtbl_00BE2B78);
	int zero = 0;
	m_vtable = (const void *)((unsigned int)vtbl_00C49AC8);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C49800);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C49AB8);
	m_20 = (const void *)((unsigned int)vtbl_00C49AAC);
	m_24 = zero;
	m_28 = zero;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
