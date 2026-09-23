// cl: /O1 /DNDEBUG /MD /GX
//
// ??0DamageFieldUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004912A9,
// 81 bytes. Behavior-side ctor (poolkey rowed; ModuleData ctor rowed).
//
// Shape follows the ArrowStormUpdate behavior precedent over the pinned
// FireWeaponUpdate base: opaque base with declared-only dtor for the single
// EH state plus explicit derived vtable installs plus freelist-node member
// at +0x2C via pinned 0x29FB3B init with the shared ebp+0xF context idiom.
// Zero new pins (all callees rowed/pinned).

class Thing;
class ModuleData;

class FireWeaponUpdate
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	~FireWeaponUpdate();
private:
	char m_pad[0x2C];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class DamageFieldUpdate : public FireWeaponUpdate
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
	*(const void **)this = (const void *)0x00C4D970;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00BEFF90;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4D964;
	member->init(context);
}
