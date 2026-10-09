// ?rva0045CD6E@BezierProjectileBehavior@@UAE_NPAVObject@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /MD /EHsc /DNDEBUG /ICode/Libraries/Include
// ?rva0045CD6E@BezierProjectileBehavior@@UAE_NPAVObject@@@Z, retail
// 0x0045CD6E (222B): slot 3 of BezierProjectileBehavior's projectile
// interface vftable at +0x20 (BezierProjectileBehaviorDetonate.cpp), the
// bool(Object *other) collision callback in Zero Hour's
// projectileHandleCollision position; the name stays address-derived.
// Target facts (this = the +0x20 subobject):
//  - false while the flight path vector at +0x44/+0x48 (12-byte points) is
//    empty;
//  - hitting an object: 0x0045B9FB(other) on the behavior, then detonate
//    (0x0045C026) unless the module data's +0x18 flag is set, in which case
//    0x0045C812(other) runs for an object not already in the hit list at
//    +0x7C (the 34-byte list scan at 0x0045BB68);
//  - hitting the ground: the module data's first-impact (+0x9C, weapon +0xA4)
//    or later-bounce (+0xA0, weapon +0xA8) FX at the projectile position,
//    the weapon through TheWeaponStore (VA 0x00DFEFDC); then bounce again
//    (0x0045CC72(0)) while the bounce count +0x78 is below the data's +0x1C,
//    else detonate, or 0x0045C975(0) when +0x18 is set;
//  - true after any hit.
// The list scan's body is ICF-folded with BFME1's Bfme5Forty.cpp
// Gen_001EFD20::bfmeIsNew (0x0045BB68 row), the only spelling the REL32
// resolver knows for it, so this TU reaches it through that name.

#include "Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary);
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }

private:
	unsigned char m_unmodelled00[0x38];
	Coord3D m_pos; // +0x38
};

class WeaponTemplate;

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *tmpl, const Object *source, const Coord3D *pos);
};
extern WeaponStore *TheWeaponStore;

struct BezierProjectileBehaviorModuleData
{
	unsigned char m_unmodelled00[0x18];
	Bool m_18; // +0x18
	Int m_maxBounces; // +0x1C
	unsigned char m_unmodelled20[0x9C - 0x20];
	const FXList *m_groundHitFX; // +0x9C
	const FXList *m_bounceFX; // +0xA0
	const WeaponTemplate *m_groundHitWeapon; // +0xA4
	const WeaponTemplate *m_bounceWeapon; // +0xA8
};

class BfmeThingDI;

class Gen_001EFD20
{
public:
	Bool bfmeIsNew(const BfmeThingDI *thing) const;
};

class ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Bool rva0045CD6E(Object *other) = 0;
};

class BezierProjectileBehaviorBase
{
public:
	virtual ~BezierProjectileBehaviorBase();

protected:
	const BezierProjectileBehaviorModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_unmodelled0C[0x20 - 0x0C];
};

struct BezierPathPoint
{
	Real x;
	Real y;
	Real z;
};

class BezierProjectileBehavior : public BezierProjectileBehaviorBase, public ProjectileUpdateInterface
{
public:
	virtual Bool rva0045CD6E(Object *other);

	void rva0045B9FB(Object *other);
	void rva0045C026();
	void rva0045C812(const Object *other);
	void rva0045C975(Int arg);
	void rva0045CC72(Int arg);

	Bool isNotInHitList(const Object *other) const
	{
		return ((const Gen_001EFD20 *)this)->bfmeIsNew((const BfmeThingDI *)other);
	}

private:
	unsigned char m_unmodelled24[0x44 - 0x24];
	BezierPathPoint *m_pathBegin; // +0x44
	BezierPathPoint *m_pathEnd; // +0x48
	unsigned char m_unmodelled4C[0x78 - 0x4C];
	Int m_bounceCount; // +0x78
};

Bool BezierProjectileBehavior::rva0045CD6E( Object *other )
{
	if( !( (unsigned int)( m_pathEnd - m_pathBegin ) > 0 ) )
		return false;

	Object *obj = m_object;
	const BezierProjectileBehaviorModuleData *d = m_moduleData;

	if( other != 0 )
	{
		rva0045B9FB( other );
		if( !d->m_18 )
			rva0045C026();
		else if( isNotInHitList( other ) )
			rva0045C812( other );
		return true;
	}

	const WeaponTemplate *weapon;
	if( m_bounceCount == 0 )
	{
		FXList::doFXPos( d->m_groundHitFX, obj->getPosition(), 0, 0.0f, 0 );
		weapon = d->m_groundHitWeapon;
	}
	else
	{
		FXList::doFXPos( d->m_bounceFX, obj->getPosition(), 0, 0.0f, 0 );
		weapon = d->m_bounceWeapon;
	}
	if( weapon )
		TheWeaponStore->createAndFireTempWeapon( weapon, obj, obj->getPosition() );

	if( m_bounceCount < d->m_maxBounces )
		rva0045CC72( 0 );
	else if( !d->m_18 )
		rva0045C026();
	else
		rva0045C975( 0 );

	return true;
}
