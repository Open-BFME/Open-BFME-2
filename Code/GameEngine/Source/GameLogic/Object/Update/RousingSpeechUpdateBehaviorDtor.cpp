char g_00C54FD8;
char g_00C54FE8;

// cl: /DNDEBUG /MD /GX-
//
// ??1RousingSpeechUpdate@@UAE@XZ, retail 0x004ACE96, 60 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched (adding a dtor decl
// there would perturb it), so the class is re-declared here with the ctor
// declared-only and only the dtor defined.
//
// Shape mirrors the ctor: explicit 4 vtable installs plus the canonical
// freelist-node member at +0x88. Its implicit destructor calls the existing
// 0x268902 owner after reset, before the base-dtor tail call.
//
// LEVERS (probe-proven): (1) base dtor declared VIRTUAL (true UAE spelling,
// shares vfptr so base stays at +0; non-virtual base pushes to +4 with a
// this-adjust). (2) NO explicit base call (explicit doubles with the
// implicit one). (3) /GX- (retail dtor is frameless with no EH prologue;
// /GX adds cookie+frame+states).

extern "C" const void *const __identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C4D640 (11 classes), by its data-ledger name
extern "C" const void *const vtbl_00C552A4[];  // folded, 6 classes; via ??_7GiveOrRestoreUpgradeSpecialPower@@6BDamageModuleInterface@@@

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
private:
	char m_pad[0x88 - 4];
};

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

class RousingSpeechUpdate : public Rva0044EF5E
{
public:
	RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~RousingSpeechUpdate();
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
	float m_94;
	float m_98;
};

// ??1RousingSpeechUpdate@@UAE@XZ @0x004ACE96
RousingSpeechUpdate::~RousingSpeechUpdate()
{
	*(const void **)this = (const void *)(unsigned int)&g_00C54FE8;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)(unsigned int)&g_00C54FD8;
	*(const void **)((char *)this + 0x20) = (const void *)((unsigned int)vtbl_00C552A4);
	m_88.reset();
}
