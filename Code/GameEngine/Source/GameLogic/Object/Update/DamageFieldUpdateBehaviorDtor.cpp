char g_00C4D964;
char g_00C4D970;

// cl: /DNDEBUG /MD /GX-
//
// ??1DamageFieldUpdate@@UAE@XZ, retail 0x0049122C, 49 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched, so the class is
// re-declared here with the ctor declared-only and only the dtor defined.
//
// Shape follows the RousingSpeechUpdate dtor precedent: explicit 3 vtable
// installs plus freelist-node member at +0x2C via pinned reset plus
// pool-free via 0x268902 pin plus implicit FireWeaponUpdate base-dtor tail
// call. One new pin (??1FireWeaponUpdate@@UAE@XZ @0x48BD11, EH dtor body).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (data ledger: ...@@6BBehaviorModuleOther@@@)

class Thing;
class ModuleData;

class FireWeaponUpdate
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();
private:
	char m_pad[0x2C];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class PoolMember
{
public:
	void Rva00268902();
};

class DamageFieldUpdate : public FireWeaponUpdate
{
public:
	DamageFieldUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageFieldUpdate();
private:
	Rva0029FB3BMember m_2C;
};

// ??1DamageFieldUpdate@@UAE@XZ @0x0049122C
DamageFieldUpdate::~DamageFieldUpdate()
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x2C);
	*(const void **)this = (const void *)(unsigned int)&g_00C4D970;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)(unsigned int)&g_00C4D964;
	member->reset();
	((PoolMember *)member)->Rva00268902();
}
