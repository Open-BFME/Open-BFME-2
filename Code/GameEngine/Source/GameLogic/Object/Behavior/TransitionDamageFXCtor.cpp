// cl: /O1 /DNDEBUG /MD
// stlport
//
// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BA3EA,
// 71 bytes. TransitionDamageFX ctor over the rowed DamageModule base
// (0x4B9704, thing plus data). The TU-local DamageModule models the donor
// multiple inheritance (primary 0x0C plus two pure interface words, 0x14
// total) so the derived vtable group lands at ([esi], +0x0C, +0x10) ahead of
// the implicit vector member init; the _STL::vector<int> member at +0xD4
// builds through the folded Vector_base at 0x211E58 (existing H-spelling pin;
// the element type is unproven and int is selected to reuse it, the 29B body
// is T-independent). The clear array at +0x14 drains through the
// for-loop-over-ints idiom (rep stosd with lea-before-xor setup,
// DynamicPortalBehaviour precedent).
//
// The rowed instance factory 0x250D4F (sole caller, ModuleFactory
// registration literal) proves the class. Row supersedes the ctor pin.

#include <vector>

class Thing;
class ModuleData;

// Primary base chain of the rowed DamageModule: vptr plus module data plus
// object (0x0C) with the two interface words following (0x14 total).
class DamageModuleBase
{
public:
	DamageModuleBase(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageModuleBase();

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class DamageModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class DamageModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class DamageModule : public DamageModuleBase,
		     public DamageModuleInterface1,
		     public DamageModuleInterface2
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
};

class TransitionDamageFX : public DamageModule
{
public:
	TransitionDamageFX(Thing *thing, const ModuleData *moduleData);

private:
	int m_clear[0x30]; // +0x14
	_STL::vector<int> m_fxIds; // +0xD4
};

// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z @0x4BA3EA
TransitionDamageFX::TransitionDamageFX(Thing *thing, const ModuleData *moduleData)
	: DamageModule(thing, moduleData)
{
	for (int i = 0; i < 0x30; ++i)
		m_clear[i] = 0;
}
