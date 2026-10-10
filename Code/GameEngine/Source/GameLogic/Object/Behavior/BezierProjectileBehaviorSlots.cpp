// cl: /DNDEBUG /MD
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
// ?projectileLaunchAtObjectOrPosition@BezierProjectileBehavior@@UAEXPAVObject@@PBUCoord3D@@0HHPBURva0045B936Arg@@PAVRva002CBA7C@@PBVMatrix3D@@@Z,
// retail 0x0045B936, 197 bytes: +0x20 slot 0, the shape of ZH
// MissileAIUpdate::projectileLaunchAtObjectOrPosition plus a transform
// argument: stores the launcher ID (+0x28) and bonus condition (+0x74), the
// victim ID (+0x38), arg 6's +4 (+0x3C) and the helper (+0x40), places the
// projectile by the transform or the pinned cdecl 0x002CA753 (whose
// null-launcher destroyObject opening is ZH positionProjectileForLaunch),
// copies the launcher's (else its own) position to +0x2C, runs primary slot
// 13 (0x0045BB8A) on the victim, then sets condition bit 4*32+26 and status 5.

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

enum ObjectStatusTypes
{
	OBJECT_STATUS_5 = 5
};

class Matrix3D;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[20];
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mx);
};

class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028AE6D();
	ObjectID getID() const { return m_id; }
	unsigned int getWeaponBonusCondition() const { return m_380; }
	const Coord3D *getPosition() const { return &m_position; }
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x380 - 0x15C];
	unsigned int m_380; // +0x380
	unsigned char m_pad384[0x438 - 0x384];
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
	bool rva002CBA7C(Object *launcher, Object *owner, Object *victim, ObjectID victimID);
};

void positionProjectileForLaunch(Object *projectile, const Object *launcher, int wslot, int specificBarrelToUse);

struct Rva0045B936Arg
{
	int m_00;
	int m_04;
};

struct BezierPathPoint
{
	int a[3];
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void gap1();
	virtual void gap2();
	virtual void gap3();
	virtual void gap4();
	virtual void gap5();
	virtual void gap6();
	virtual void gap7();
	virtual void gap8();
	virtual void gap9();
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void rva0045BB8A(Object *victim, const Coord3D *victimPos) = 0;
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
	virtual void projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx) = 0;
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
	virtual void projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx);
private:
	ObjectID m_28; // +0x28 launcher
	Coord3D m_2C; // +0x2C launch position
	ObjectID m_38; // +0x38 victim
	int m_3C;
	Rva002CBA7C *m_helper; // +0x40
	BezierPathPoint *m_pathBegin; // +0x44
	BezierPathPoint *m_pathEnd; // +0x48
	BezierPathPoint *m_pathCap;
	unsigned char m_pad50[0x74 - 0x50];
	unsigned int m_74; // +0x74 launcher bonus condition
	int m_78; // +0x78
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
	ObjectID extra = m_38;
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

// ?projectileLaunchAtObjectOrPosition@BezierProjectileBehavior@@UAEXPAVObject@@PBUCoord3D@@0HHPBURva0045B936Arg@@PAVRva002CBA7C@@PBVMatrix3D@@@Z @0x0045B936
void BezierProjectileBehavior::projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
	int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx)
{
	m_28 = launcher ? launcher->getID() : INVALID_ID;
	m_74 = launcher ? launcher->getWeaponBonusCondition() : 0;
	m_38 = victim ? victim->getID() : INVALID_ID;
	m_3C = arg6->m_04;
	m_78 = 0;
	m_helper = helper;
	Object *obj = m_object;
	if (mtx)
		obj->setTransformMatrix(mtx);
	else
		positionProjectileForLaunch(obj, launcher, wslot, specificBarrel);
	m_2C = launcher ? *launcher->getPosition() : *obj->getPosition();
	rva0045BB8A(victim, victimPos);
	obj->setModelConditionBit(4 * 32 + 26);
	obj->setStatus(OBJECT_STATUS_5, true);
}

// Clean donor: Open-BFME-1 575ba2b0, BezierProjectileBehaviorModuleDataCtorThunk.cpp.
// Native45B4F1..45B5E3 is the complete242B constructor; the next17B body is
// the separately rowed buildFieldParse. BFME2 widens both curve members to
// the existing28B constructor24C7B3 and adds the fields afterAC. Float widths
// below follow native MOVSS stores; unexplained fields retain offset names.
// This is the existing shared table alias used by Aim/Physics module data;
// this unit adds neither an alias definition nor a guessed virtual contract.
extern "C" const void *const vtbl_00C4ED70[];

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

class BezierProjectileBehaviorModuleData
{
public:
	BezierProjectileBehaviorModuleData();
private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_firstHeight, m_secondHeight, m_firstPercentIndent, m_secondPercentIndent;
	bool m_killInsteadOfDestroy, m_flag19;
	unsigned int m_effectFrame;
	float m_value20, m_value24, m_value28, m_value2C, m_value30, m_value34;
	unsigned int m_value38, m_value3C, m_value40, m_value44;
	bool m_flag48, m_enabled, m_objectFire;
	unsigned int m_value4C;
	Rva0024C7B3Member m_firstCurve, m_secondCurve;
	unsigned int m_value88;
	float m_value8C;
	bool m_flag90;
	float m_minCurveFraction, m_maxCurveFraction;
	void *m_effect9C, *m_effectA0, *m_effectA4, *m_effectA8;
	int m_invalidAC;
	float m_valueB0;
	bool m_flagB4;
	void *m_valueB8;
	int m_invalidBC;
	float m_valueC0;
};

BezierProjectileBehaviorModuleData::BezierProjectileBehaviorModuleData()
	: m_vtable(vtbl_00C4ED70), m_firstHeight(0), m_secondHeight(0),
	  m_firstPercentIndent(0), m_secondPercentIndent(0),
	  m_killInsteadOfDestroy(false), m_flag19(false), m_effectFrame(0),
	  m_value20(0), m_value24(0), m_value28(0), m_value2C(0), m_value30(0), m_value34(0),
	  m_value38(0), m_value3C(0), m_value40(0), m_value44(0),
	  m_flag48(false), m_enabled(true), m_objectFire(false), m_value4C(0)
{
	m_value88 = 0;
	m_value8C = 0.0f;
	m_flag90 = false;
	m_minCurveFraction = 0.33f;
	m_maxCurveFraction = 0.66f;
	m_effect9C = 0;
	m_effectA0 = 0;
	m_effectA4 = 0;
	m_effectA8 = 0;
	m_invalidAC = -1;
	m_valueB0 = 0.0f;
	m_flagB4 = true;
	m_valueB8 = 0;
	m_invalidBC = -1;
	m_valueC0 = 0.0f;
}
