// cl: /O1 /DNDEBUG /MD /GX
//
// ??0AutoPickUpUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00495D31,
// 121 bytes. Behavior-side ctor (rowed instance factory 0x24E061 news
// 0x2C with this pinned 2-arg ctor as its sole raw caller at 0x24E088).
//
// Shape follows the AutoHealBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, the
// module data pointer homed in eax with an ecx-homed int zero (sequential
// lifetimes keep pressure low), early __FILE__-literal pushes, the three
// derived vtable installs, zeros at +0x24/+0x28/+0x29, and a
// GetGameLogicRandomValue accumulation into +0x24 (rowed int twin
// 0x233FF4 over lo/hi/file/line with the TU __FILE__ literal and line
// 0x83). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

struct AutoPickUpUpdateModuleData
{
	unsigned char m_pad00[8];
	Int m_08;
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

class AutoPickUpUpdate : public UpdateModule
{
public:
	AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned char m_28;
	unsigned char m_29;
};

// ??0AutoPickUpUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00495D31
AutoPickUpUpdate::AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)0x00C4EF80;
	const AutoPickUpUpdateModuleData *data = (const AutoPickUpUpdateModuleData *)m_moduleData;
	int zero = 0;
	m_vtable = (const void *)0x00C4F06C;
	m_secondary0C = (const void *)0x00C4EFB0;
	m_secondary10 = (const void *)0x00C4EFA0;
	m_20 = (const void *)0x00C4EF90;
	m_24 = zero;
	m_28 = zero;
	m_29 = zero;
	m_24 += GetGameLogicRandomValue(0, data->m_08, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AutoPickUpUpdate.cpp", 0x83);
}
