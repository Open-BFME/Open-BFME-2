// cl: /O1 /DNDEBUG /MD /GX
//
// ??0SlaveWatcherBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004845CB, 93 bytes. Behavior-side ctor (rowed instance factory
// 0x24C625 news 0xA4 with this pinned 2-arg ctor as its sole raw caller
// at 0x24C64F; poolkey rowed at 0x48462E pushes the SlaveWatcherBehavior
// literal).
//
// Shape follows the StructureCollapseUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, the three derived vtable installs, a clear80 call into the
// 0x80 member at +0x24 (rowed Rva001EAE6FHelper 0x1EAE6F), an and-zero at
// +0x20, and the setWakeFrame tail (protected IAEX Object-uint spelling
// resolves via the existing pin at 0x44DF71). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
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

class SlaveWatcherBehavior : public UpdateModule
{
public:
	SlaveWatcherBehavior(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	Rva001EAE6FHelper m_24;
};

// ??0SlaveWatcherBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x004845CB
SlaveWatcherBehavior::SlaveWatcherBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_vtable = (const void *)0x00C4A264;
	m_secondary0C = (const void *)0x00BEFF90;
	m_secondary10 = (const void *)0x00C4A258;
	m_24.clear80();
	m_20 &= 0;
	setWakeFrame(m_object, 1);
}
