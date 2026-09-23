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

class Thing;
class ModuleData;
class Object;

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
	*slot20 = (int)0x00C1C780;
	*slot24 = (int)0x00C4EF80;
	m_vtable = (const void *)0x00C49408;
	m_secondary0C = (const void *)0x00C42B60;
	m_secondary10 = (const void *)0x00C493FC;
	m_20 = (const void *)0x00C493F8;
	m_24 = (const void *)0x00C493E8;
	m_28 = false;
	m_29 = true;
	m_2C = fzero;
	setWakeFrame(m_object, 1);
}
