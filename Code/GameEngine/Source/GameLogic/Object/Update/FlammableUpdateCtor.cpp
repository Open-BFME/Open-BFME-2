// cl: /DNDEBUG /MD /GX
//
// ??0FlammableUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048C64F,
// 138 bytes. Behavior-side ctor (rowed instance factory 0x24D030 news
// 0x50 with this pinned 2-arg ctor as its sole raw caller at 0x24D057).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// eax-homed int zero, the setWakeFrame arg pushes mid-body, the three
// derived vtable installs, and a module-data field (+0x1C) copied to
// +0x38 ahead of the setWakeFrame tail (protected IAEX Object-uint
// spelling resolves via the existing pin at 0x44DF71). Row supersedes the
// ctor pin.

extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00C49800[];  // folded, 4 classes; via ??_7FlammableUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00C49800=??_7FlammableUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C4C3BC[];  // ??_7FlammableUpdate@@6BDamageModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4C3BC=??_7FlammableUpdate@@6BDamageModuleInterface@@@")
extern "C" const void *const vtbl_00C4C3C8[];  // ??_7FlammableUpdate@@6BUpdateModule@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4C3C8=??_7FlammableUpdate@@6BUpdateModule@@@")
extern "C" const void *const vtbl_00C4C3D4[];  // ??_7FlammableUpdate@@6BBehaviorModuleBase@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4C3D4=??_7FlammableUpdate@@6BBehaviorModuleBase@@@")

class Thing;
class ModuleData;
class Object;

struct FlammableUpdateModuleData
{
	unsigned char m_pad00[0x1C];
	int m_1C;
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

class FlammableUpdate : public UpdateModule
{
public:
	FlammableUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned int m_44;
	unsigned int m_48;
	unsigned char m_4C;
};

// ??0FlammableUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048C64F
FlammableUpdate::FlammableUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)((unsigned int)vtbl_00BE2B78);
	int zero = 0;
	m_24 = zero;
	m_28 = zero;
	m_2C = zero;
	m_30 = zero;
	m_34 = zero;
	m_3C = zero;
	m_40 = zero;
	m_44 = zero;
	m_48 = zero;
	m_4C = zero;
	const FlammableUpdateModuleData *data = (const FlammableUpdateModuleData *)m_moduleData;
	m_vtable = (const void *)((unsigned int)vtbl_00C4C3D4);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C49800);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C4C3C8);
	m_20 = (const void *)((unsigned int)vtbl_00C4C3BC);
	m_38 = data->m_1C;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
