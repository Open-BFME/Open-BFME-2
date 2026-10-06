// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0TerrainResourceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0048209B, 125 bytes. Behavior-side ctor (rowed instance factory
// 0x24C26C with this pinned 2-arg ctor as its sole raw caller at
// 0x24C293).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20/+0x24 slot pair via sourced-before
// address-take, the setWakeFrame arg pushes hoisted above the stores (no
// intervening call), the three derived vtable installs, immediate false
// and true bytes at +0x28/+0x29, one float zero at +0x2C via an xmm0-homed
// fzero local (/arch:SSE emits retail xorps+movss), and the setWakeFrame
// tail (protected IAEX Object-uint spelling resolves via the existing pin
// at 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C42B60[];  // folded, 3 classes; via ??_7FakePathfindPortalBehaviour@@6BMiBase1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C42B60=??_7FakePathfindPortalBehaviour@@6BMiBase1@@@")
extern "C" const void *const vtbl_00C4EF80[];  // folded, 7 classes; via ??_7ContainIface34@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4EF80=??_7ContainIface34@@6B@")

extern "C" const void *const vtbl_00C493E8[];  // ??_7Rva00481F82@@6BRva00481F82_S4@@@
#pragma comment(linker, "/alternatename:_vtbl_00C493E8=??_7Rva00481F82@@6BRva00481F82_S4@@@")
extern "C" const void *const vtbl_00C493F8[];  // ??_7Rva00481F82@@6BRva00481F82_S3@@@
#pragma comment(linker, "/alternatename:_vtbl_00C493F8=??_7Rva00481F82@@6BRva00481F82_S3@@@")
extern "C" const void *const vtbl_00C493FC[];  // ??_7Rva00481F82@@6BRva00481F82_S2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C493FC=??_7Rva00481F82@@6BRva00481F82_S2@@@")
extern "C" const void *const vtbl_00C49408[];  // ??_7Rva00481F82@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00C49408=??_7Rva00481F82@@6BRva0024A797@@@")
extern "C" const void *const vtbl_00C1C780[];  // folded, 49 classes; via ??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

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

class TerrainResourceBehavior : public UpdateModule
{
public:
	TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	const void *m_24;
	bool m_28;
	bool m_29;
	float m_2C;
};

// ??0TerrainResourceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048209B
TerrainResourceBehavior::TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_20;
	int *slot24 = (int *)&m_24;
	*slot20 = (int)((unsigned int)vtbl_00C1C780);
	*slot24 = (int)((unsigned int)vtbl_00C4EF80);
	m_vtable = (const void *)((unsigned int)vtbl_00C49408);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C42B60);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C493FC);
	m_20 = (const void *)((unsigned int)vtbl_00C493F8);
	m_24 = (const void *)((unsigned int)vtbl_00C493E8);
	m_28 = false;
	m_29 = true;
	m_2C = fzero;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
