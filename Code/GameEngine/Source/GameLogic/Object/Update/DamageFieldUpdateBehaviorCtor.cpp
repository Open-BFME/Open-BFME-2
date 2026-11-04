// cl: /DNDEBUG /MD /GX
//
// ??0DamageFieldUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004912A9,
// 81 bytes. Behavior-side ctor (poolkey rowed; ModuleData ctor rowed).
//
// Shape follows the ArrowStormUpdate behavior precedent over the pinned
// FireWeaponUpdate base: opaque base with declared-only dtor for the single
// EH state plus explicit derived vtable installs plus freelist-node member
// at +0x2C via pinned 0x29FB3B init with the shared ebp+0xF context idiom.
// Zero new pins (all callees rowed/pinned).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (the data-ledger spelling ...@@6BBehaviorModuleOther@@@ has no definer)

extern char g_00C4D964;
extern char g_00C4D970;

class Thing;
class ModuleData;

class FireWeaponUpdate
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate(); // virtual, as rowed (0x0048BD11)
private:
	char m_pad[0x2C - 4];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset() throw();
};

class __declspec(novtable) DamageFieldUpdate : public FireWeaponUpdate
{
public:
	DamageFieldUpdate(Thing *thing, const ModuleData *moduleData);
private:
	Rva0029FB3BMember m_2C;
};

// ??0DamageFieldUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004912A9
DamageFieldUpdate::DamageFieldUpdate(Thing *thing, const ModuleData *moduleData) :
	FireWeaponUpdate(thing, moduleData)
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x2C);
	void *context = (void *)((char *)&moduleData + 3);
	*(const void **)this = (const void *)(unsigned int)&g_00C4D970;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)(unsigned int)&g_00C4D964;
	member->init(context);
}
