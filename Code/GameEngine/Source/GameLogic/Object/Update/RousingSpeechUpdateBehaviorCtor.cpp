// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0RousingSpeechUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004ACF76,
// 135 bytes. Behavior-side ctor (poolkey rowed; ModuleData ctor rowed;
// rowed friend factory 0x24F551 news 0x9C with this ctor as its sole raw
// caller; pin at 0x4ACF76 superseded by the row).
//
// Shape follows the ArrowStormUpdate behavior precedent over the opaque
// Rva0044EF5E base: declared-only base dtor for the single EH state plus
// explicit derived vtable installs plus freelist-node member at +0x88 via
// pinned 0x29FB3B init with the shared ebp+0xF context idiom plus pool reset
// via 0x26549E alias pin. Tail is direct and-imm plus mov-byte plus two
// float zero stores (movss pair over one xorps). Zero new pins (all callees
// rowed/pinned).

extern "C" const void *const __identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C4D640 (11 classes), by its data-ledger name
extern "C" const void *const vtbl_00C552A4[];  // folded, 6 classes; via ??_7GiveOrRestoreUpgradeSpecialPower@@6BDamageModuleInterface@@@

extern char g_00C54FD8;
extern char g_00C54FE8;

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

class RousingSpeechUpdate : public Rva0044EF5E
{
public:
	RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData);
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
	float m_94;
	float m_98;
};

// ??0RousingSpeechUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004ACF76
RousingSpeechUpdate::RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData) :
	Rva0044EF5E(thing, moduleData)
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	void *context = (void *)((char *)&moduleData + 3);
	*(const void **)this = (const void *)(unsigned int)&g_00C54FE8;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)(unsigned int)&g_00C54FD8;
	*(const void **)((char *)this + 0x20) = (const void *)((unsigned int)vtbl_00C552A4);
	member->init(context);
	m_8C &= 0;
	m_90 = 0;
	m_94 = 0.0f;
	m_98 = 0.0f;
	member->reset();
}
