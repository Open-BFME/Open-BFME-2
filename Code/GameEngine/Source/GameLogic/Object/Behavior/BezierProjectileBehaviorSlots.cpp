// cl: /O1 /DNDEBUG /MD
//
// BezierProjectileBehavior overrides on the two interface vtables its ctor
// (installs 0x00C41E04 +0, 0x00C53570 +0x0C, 0x00C41DF8 +0x10, see the matched
// dtor 0x0045BF6E) puts at +0x20 (0x00C41DE0, the projectile interface) and
// +0x24 (0x00C41DC8). Each is compiled with its subobject this. Names are by
// address. Layout from the dtor and the BFME 1 donor
// BezierProjectileBehavior_handle.cpp: m_object +0x08, the launcher ID at
// +0x28 (slot 2 of 0x00C41DE0 is the shared [this+8] getter 0x0030F45F),
// +0x38 passed through, the launch helper at +0x40 and the 12-byte path vector
// at +0x44.
//
// ?rva0045BF06@BezierProjectileBehavior@@UAE_NPAVObject@@@Z, retail
// 0x0045BF06, 104 bytes: +0x20 slot 4; false on an empty path, no helper, or
// a victim of KindOf bit 13 or dead (Object +0x438 bit 0); otherwise the
// helper 0x002CBA7C with the launcher found by ID, the owner, the victim and
// +0x38. Close to the donor's handle(), without its status test.
// ?rva0045BF06@BezierProjectileBehavior@@W3AE_NPAVObject@@@Z, retail
// 0x0045C01E, 8 bytes: +0x24 slot 1, the this-4 adjustor thunk to it
// (emitted with the vftables in BezierProjectileBehaviorDtor.cpp).
// ?rva0045B4C0@BezierProjectileBehavior@@UAEXPAVObject@@HH@Z, retail
// 0x0045B4C0, 34 bytes: +0x24 slot 0; +0x20 slot 3 (0x0045CD6E) on the victim
// when +0x20 slot 4 accepts it.
// ?rva0045B4E2@BezierProjectileBehavior@@UAEXH@Z, retail 0x0045B4E2, 15
// bytes: +0x20 slot 5; kills the owner (damage type 8, death type 0).

class ModuleData;

enum ObjectID
{
	INVALID_ID = 0
};

enum DamageType
{
	DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x114];
	unsigned int m_kindOf[4]; // +0x114
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x438 - 0x08];
	unsigned char m_438; // +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Rva002CBA7C
{
public:
	bool rva002CBA7C(Object *launcher, Object *owner, Object *victim, void *extra);
};

struct BezierPathPoint
{
	int a[3];
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual void f10(); };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva0045BF06Iface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual ObjectID getLauncherID() const = 0;
	virtual bool rva0045CD6E(Object *victim) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
	virtual void rva0045B4E2(int unused) = 0;
};

class Rva0045B4C0Iface
{
public:
	virtual void rva0045B4C0(Object *victim, int a2, int a3) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
};

class BezierProjectileBehavior : public UpdateModule, public Rva0045BF06Iface, public Rva0045B4C0Iface
{
public:
	virtual bool rva0045BF06(Object *victim);
	virtual void rva0045B4C0(Object *victim, int a2, int a3);
	virtual void rva0045B4E2(int unused);
private:
	ObjectID m_28;
	unsigned char m_pad2C[0x38 - 0x2C];
	void *m_38; // +0x38
	int m_3C;
	Rva002CBA7C *m_helper; // +0x40
	BezierPathPoint *m_pathBegin; // +0x44
	BezierPathPoint *m_pathEnd; // +0x48
	BezierPathPoint *m_pathCap;
};

// ?rva0045BF06@BezierProjectileBehavior@@UAE_NPAVObject@@@Z @0x0045BF06
bool BezierProjectileBehavior::rva0045BF06(Object *victim)
{
	if ((unsigned int)(m_pathEnd - m_pathBegin) <= 0)
		return false;
	if (m_helper == 0)
		return false;
	if (victim)
	{
		if (victim->isKindOf(13) != 0)
			return false;
		if (victim->isEffectivelyDead())
			return false;
	}
	Object *launcher = TheGameLogic->findObjectByID(getLauncherID());
	Object *owner = m_object;
	void *extra = m_38;
	return m_helper->rva002CBA7C(launcher, owner, victim, extra);
}

// ?rva0045B4C0@BezierProjectileBehavior@@UAEXPAVObject@@HH@Z @0x0045B4C0
void BezierProjectileBehavior::rva0045B4C0(Object *victim, int, int)
{
	if (rva0045BF06(victim))
		rva0045CD6E(victim);
}

// ?rva0045B4E2@BezierProjectileBehavior@@UAEXH@Z @0x0045B4E2
void BezierProjectileBehavior::rva0045B4E2(int)
{
	m_object->kill(DAMAGE_TYPE_8, DEATH_NORMAL);
}
