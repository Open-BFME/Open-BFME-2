// cl: /O1 /DNDEBUG /MD /GX
//
// ??0LargeGroupBonusUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004900B1, 143 bytes. Behavior-side ctor (rowed instance factory
// 0x24D407 news 0x2C with this pinned 2-arg ctor as its sole raw caller
// at 0x24D42E).
//
// Shape follows the AutoPickUpUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, the
// object pointer homed in edi with an eax-homed int zero (sequential
// lifetimes keep pressure low), the three derived vtable installs, a
// TheGameLogic field (+0x40) copied to +0x24, and a GetGameLogicRandomValue
// call (rowed int twin 0x233FF4 over lo/hi/file/line with the TU __FILE__
// literal and line 0x6B) feeding the setWakeFrame tail (protected IAEX
// Object-uint spelling resolves via the existing pin at 0x44DF71). Row
// supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

struct LargeGroupBonusUpdateModuleData
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

class LargeGroupBonusUpdate : public UpdateModule
{
public:
	LargeGroupBonusUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned char m_28;
	unsigned char m_29;
	unsigned char m_2A;
};

// ??0LargeGroupBonusUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004900B1
LargeGroupBonusUpdate::LargeGroupBonusUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)0x00BE2B78;
	Object *obj = m_object;
	int zero = 0;
	m_28 = zero;
	m_2A = zero;
	m_vtable = (const void *)0x00C4D124;
	m_secondary0C = (const void *)0x00C4D068;
	m_secondary10 = (const void *)0x00C4D058;
	m_20 = (const void *)0x00C4D04C;
	m_24 = TheGameLogic->m_40;
	m_29 = zero;
	const LargeGroupBonusUpdateModuleData *data = (const LargeGroupBonusUpdateModuleData *)m_moduleData;
	int hi = data->m_08;
	setWakeFrame(obj, GetGameLogicRandomValue(1, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\LargeGroupBonusUpdate.cpp", 0x6B));
}
