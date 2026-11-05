// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0ArrowStormUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004909D7,
// 129 bytes. Behavior-side ctor (rowed instance factory news 0x9C with this
// pinned 2-arg ctor as its sole raw caller; poolkey rowed).
//
// Shape: opaque Rva0044EF5E base (declared-only dtor arms the single EH
// state) plus explicit derived vtable installs plus freelist-node member at
// +0x88 via pinned 0x29FB3B init plus pool reset via 0x26549E alias pin plus
// zero tail. The init context is the address of the last byte of the
// incoming ModuleData slot (framework idiom, shared by all 6 callers).

extern "C" const void *const __identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C4D640 (11 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7GiveOrRestoreUpgradeSpecialPower@@6BRva0044EF5E@@@")[];  // folded vftable 0x00C4DEE8 (4 classes), by its data-ledger name

extern char g_00C4D61C;
extern char g_00C4D700;

class Thing;
class ModuleData;

// Retail's unwind of the base subobject calls the rowed
// ~SpecialAbilityUpdate 0x00451F45 (the dtor of the 0x0044EF5E base).
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	~Rva0044EF5E() { ((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::~SpecialAbilityUpdate(); }
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class ArrowStormUpdate : public Rva0044EF5E
{
public:
	ArrowStormUpdate(Thing *thing, const ModuleData *moduleData);
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	int m_90;
	int m_94;
	unsigned char m_98;
};

// ??0ArrowStormUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004909D7
ArrowStormUpdate::ArrowStormUpdate(Thing *thing, const ModuleData *moduleData) :
	Rva0044EF5E(thing, moduleData)
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	void *context = (void *)((char *)&moduleData + 3);
	*(const void **)this = (const void *)(unsigned int)&g_00C4D700;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)((unsigned int)__identifier("??_7GiveOrRestoreUpgradeSpecialPower@@6BRva0044EF5E@@@"));
	*(const void **)((char *)this + 0x20) = (const void *)(unsigned int)&g_00C4D61C;
	member->init(context);
	member->reset();
	m_8C = 0;
	m_90 = 0;
	m_94 = 0;
	m_98 = 0;
}
