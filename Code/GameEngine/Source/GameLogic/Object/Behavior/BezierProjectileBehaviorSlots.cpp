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

#include "../../../Common/GameLogicObjectLookupView.h"

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

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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

class GeometryInfo
{
public:
	bool CollidesWith(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mx);
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
	friend class BezierProjectileBehavior;
public:
	void kill(DamageType damageType, DeathType deathType);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028AE6D();
	ObjectID getID() const { return m_id; }
	unsigned int getWeaponBonusCondition() const { return m_380; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getWeaponBonusCondition copy loses to the first-in-order copy. No flags touched.
	unsigned int bfme_getWeaponBonusCondition_a1a45() const { return m_380; }
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
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isKindOf copy loses to the first-in-order copy. No flags touched.
	__forceinline unsigned int bfme_isKindOf_68ffe(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44, target collision-step accesses
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x380 - 0x15C];
	unsigned int m_380; // +0x380
	unsigned char m_pad384[0x438 - 0x384];
	unsigned char m_438; // +0x438
};

// Target uses an embedded GeometryInfo at +0xA8; its full size is not
// established here. This accessor preserves that offset without inventing it.
static __forceinline GeometryInfo *collisionGeometry(Object *object)
{
	return (GeometryInfo *)((char *)object + 0xA8);
}

// Scalar coordinate storage reproduces the native copies and SSE operations.
// This adapter is a local compiler-shape view, not an original class identity.
struct Rva0045B9FBPoint : Coord3D
{
	Rva0045B9FBPoint(const Coord3D &r) { x = r.x; y = r.y; z = r.z; }
	~Rva0045B9FBPoint() {}
	void sub(const Coord3D &r) { x -= r.x; y -= r.y; z -= r.z; }
	void add(const Coord3D &r) { x += r.x; y += r.y; z += r.z; }
	void scale(float k) { x *= k; y *= k; z *= k; }
};

extern GameLogic *TheGameLogic;

// LINK: 0x002CBA7C is rowed as WeaponTemplate::shouldProjectileCollideWith (WeaponTemplateShouldProjectileCollideWith.cpp)
// and 0x002CA753 as Weapon::positionProjectileForLaunch (Weapon_positionProjectileForLaunch_Rva002CA753.cpp).
enum WeaponSlotType { BFME_WEAPON_SLOT_0 };
class Rva002CBA7C;
class WeaponTemplate
{
public:
	bool shouldProjectileCollideWith(const Object *launcher, const Object *owner, const Object *victim, ObjectID victimID) const;
};

#include "../../../../Include/GameLogic/Weapon.h"

struct Rva0045B936Arg
{
	int m_00;
	int m_04;
};

// Target path elements are three floats at offsets 0/4/8.
// Coord3D supplies those accessed fields; the original container type is unknown.
typedef Coord3D BezierPathPoint;

// The three-pointer layout and 12-byte element stride are target facts;
// the accessor shape is supported by the BFME 1 path-vector donor.
struct BezierPathSpan
{
	BezierPathPoint *first, *last, *limit;
	unsigned int size() const { return last - first; }
	BezierPathPoint *begin() const { return first; }
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
	void rva0045B9FB(Object *other);
	virtual bool rva0045BF06(Object *victim);
	virtual void rva0045B4C0(Object *victim, int a2, int a3);
	virtual void rva0045B4E2(int unused);
	virtual void projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx);
private:
	ObjectID m_28; // +0x28 launcher
	Coord3D m_launchPosition; // +0x2C launch position
	ObjectID m_38; // +0x38 victim
	int m_3C;
	Rva002CBA7C *m_helper; // +0x40
	BezierPathSpan m_path; // +0x44, end +0x48, capacity +0x4C
	unsigned char m_pad50[0x70 - 0x50];
	int m_70; // +0x70 path cursor
	unsigned int m_74; // +0x74 launcher bonus condition
	int m_78; // +0x78
};

// ?rva0045BF06@BezierProjectileBehavior@@UAE_NPAVObject@@@Z @0x0045BF06
bool BezierProjectileBehavior::rva0045BF06(Object *victim)
{
	if ((unsigned int)(m_path.last - m_path.first) <= 0)
		return false;
	if (m_helper == 0)
		return false;
	if (victim)
	{
		if (victim->bfme_isKindOf_68ffe(13) != 0)
			return false;
		// Native BF06 checks byte +0x438 bit 0 directly; it is not the
		// independently owned Object::isEffectivelyDead operation.
		if ((victim->m_438 & 1) != 0)
			return false;
	}
	Object *launcher = TheGameLogic->findObjectByID(getLauncherID());
	Object *owner = m_object;
	ObjectID extra = m_38;
	return ((const WeaponTemplate *)m_helper)->shouldProjectileCollideWith(launcher, owner, victim, extra);
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
	m_28 = launcher ? launcher->getID() : INVALID_OBJECT_ID;
	m_74 = launcher ? launcher->bfme_getWeaponBonusCondition_a1a45() : 0;
	m_38 = victim ? victim->getID() : INVALID_OBJECT_ID;
	m_3C = arg6->m_04;
	m_78 = 0;
	m_helper = helper;
	Object *obj = m_object;
	if (mtx)
		obj->setTransformMatrix(mtx);
	else
		Weapon::positionProjectileForLaunch(obj, launcher, (WeaponSlotType)wslot, specificBarrel);
	m_launchPosition = launcher ? *launcher->getPosition() : *obj->getPosition();
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
extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];

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
	: m_vtable(__identifier("??_7ObjectHelperModuleData@@6B@")), m_firstHeight(0), m_secondHeight(0),
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

// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z @0x0045B9FB
// 336 bytes. Primary caller 0x0045CD6E and WB counterpart 0x011816A0
// establish the collision-step relationship. BFME 1's matched Bezier caller
// (donor cee35b7d8) supports that relationship, not the unknown method name.
void BezierProjectileBehavior::rva0045B9FB(Object *other)
{
	if (!other)
		return;
	int idx = m_path.size() - 1 < (unsigned int)m_70 ? m_path.size() - 1 : m_70;
	Object *obj = m_object;
	Rva0045B9FBPoint cur(obj->m_position);
	BezierPathPoint *bezierPathPoint = m_path.begin() + (idx - 1 < 0 ? 0 : idx - 1);
	Rva0045B9FBPoint delta(*bezierPathPoint);
	delta.sub(cur);
	delta.scale(0.1f);
	float angle = obj->m_orientation;
	GeometryInfo *geom = collisionGeometry(obj);
	int i = 0;
	bool collision = true;
	while (collision && i++ <= 12)
	{
		cur.add(delta);
		collision = geom->CollidesWith(cur, angle, *collisionGeometry(other),
			other->m_position, other->m_orientation);
	}
	cur.sub(delta);
	obj->setPosition(&cur);
}
