// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??1DamageFieldUpdate@@UAE@XZ, retail 0x0049122C, 49 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched, so the class is
// re-declared here with the ctor declared-only and only the dtor defined.
//
// Shape follows the RousingSpeechUpdate dtor precedent: explicit 3 vtable
// installs plus freelist-node member at +0x2C via pinned reset plus
// pool-free via 0x268902 pin plus implicit FireWeaponUpdate base-dtor tail
// call. One new pin (??1FireWeaponUpdate@@UAE@XZ @0x48BD11, EH dtor body).

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
	*(const void **)this = (const void *)0x00C4D970;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00BEFF90;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4D964;
	member->reset();
	((PoolMember *)member)->Rva00268902();
}
