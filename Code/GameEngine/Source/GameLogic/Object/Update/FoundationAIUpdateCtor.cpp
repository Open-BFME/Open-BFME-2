// cl: /O1 /DNDEBUG /MD /GX
//
// ??0FoundationAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004551B3,
// 107 bytes. Behavior-side ctor (rowed instance factory 0x24AA26 news
// 0x30 with this pinned 2-arg ctor as a raw caller at 0x24AA4D; poolkey
// rowed at 0x455167 pushes the FoundationAIUpdate literal; a derived
// behavior ctor at 0x3983D4 shares the base call).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// and-zero at +0x28, a one-homed local (xor-plus-inc) feeding the
// setWakeFrame frame plus +0x24/+0x2C, the three derived vtable installs,
// and the setWakeFrame tail (protected IAEX Object-uint spelling resolves
// via the existing pin at 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00BFBC9C[];  // ??_7Rva005EEF2FBase0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFBC9C=??_7Rva005EEF2FBase0@@6B@")

extern "C" const void *const vtbl_00C1A690[];  // ??_7Rva00455050@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1A690=??_7Rva00455050@@6B@")
extern "C" const void *const vtbl_00C40538[];  // ??_7Rva00455050@@6BRva0024A797_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40538=??_7Rva00455050@@6BRva0024A797_B2@@@")
extern "C" const void *const vtbl_00C40548[];  // ??_7Rva00455050@@6BRva0024A797_Mid@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40548=??_7Rva00455050@@6BRva0024A797_Mid@@@")
extern "C" const void *const vtbl_00C40608[];  // ??_7Rva00455050@@6BRva0024A797_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40608=??_7Rva00455050@@6BRva0024A797_Root@@@")

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

class FoundationAIUpdate : public UpdateModule
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned char m_2C;
};

// ??0FoundationAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004551B3
FoundationAIUpdate::FoundationAIUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)((unsigned int)vtbl_00BFBC9C);
	m_28 &= 0;
	int one = 1;
	m_vtable = (const void *)((unsigned int)vtbl_00C40608);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C40548);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C40538);
	m_20 = (const void *)((unsigned int)vtbl_00C1A690);
	m_24 = one;
	m_2C = (unsigned char)one;
	setWakeFrame(m_object, (UpdateSleepTime)one);
}
