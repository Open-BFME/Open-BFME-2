// ?rva0045CD6E@BezierProjectileBehaviorProjectile@@UAE_NPAVObject@@@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0045CD6E, 222B: a BezierProjectileBehavior member entered through
// the projectile interface at +0x20 (ret 4), the collision handler shaped
// like Zero Hour's DumbProjectileBehavior::projectileHandleCollision. Target
// evidence: it returns false while the flight-point vector at +0x44 (12-byte
// entries) is empty; with another object it notes the hit (0x0045B9FB) and
// either detonates (0x0045C026) when module data +0x18 is clear or, when
// 0x0045BB68 accepts the object, fires at it (0x0045C812). Without one it
// plays the ground FX (module data +0x9C/+0xA0, chosen by the count at +0x78)
// at the object position, fires the matching temp weapon (+0xA4/+0xA8)
// through WeaponStore::createAndFireTempWeapon, then either continues
// (0x0045CC72) while the count is below module data +0x1C, detonates, or
// finishes (0x0045C975). Slot name not established: address-derived.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;

class Matrix3D;
class WeaponTemplate;
class BfmeThingDI;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx = 0, const Real primarySpeed = 0.0f,
		const Coord3D *secondary = 0);
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

class Gen_001EFD20
{
public:
	bool bfmeIsNew(const BfmeThingDI *thing) const;
};

struct BezierProjectileBehaviorModuleData
{
	unsigned char m_pad00[0x18];
	bool m_detonateOnContact;
	Int m_maxBounces;
	unsigned char m_pad20[0x9C - 0x20];
	const FXList *m_groundFX;
	const FXList *m_bounceFX;
	const WeaponTemplate *m_groundWeapon;
	const WeaponTemplate *m_bounceWeapon;
};

struct Rva0045CD6EPoint
{
	Real x;
	Real y;
	Real z;
};

class ProjectileUpdateInterface
{
public:
	virtual bool rva0045CD6E( Object *other ) = 0;
};

class BezierProjectileBehavior
{
public:
	virtual ~BezierProjectileBehavior();
	void rva0045B9FB( Object *other );
	void rva0045C026();
	void rva0045C812( const Object *other );
	void rva0045CC72( Int unused );
	void rva0045C975( Int unused );

	const BezierProjectileBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class BezierProjectileBehaviorProjectile : public BezierProjectileBehavior, public ProjectileUpdateInterface
{
public:
	virtual bool rva0045CD6E( Object *other );

	unsigned char m_pad24[0x44 - 0x24];
	Rva0045CD6EPoint *m_pointsBegin;
	Rva0045CD6EPoint *m_pointsEnd;
	Rva0045CD6EPoint *m_pointsCapacity;
	unsigned char m_pad50[0x78 - 0x50];
	Int m_bounceCount;
};

bool BezierProjectileBehaviorProjectile::rva0045CD6E( Object *other )
{
	if( !( (unsigned int)( m_pointsEnd - m_pointsBegin ) > 0 ) )
		return false;

	Object *obj = m_object;
	const BezierProjectileBehaviorModuleData *d = m_moduleData;

	if( other != 0 )
	{
		rva0045B9FB( other );
		if( !d->m_detonateOnContact )
			rva0045C026();
		else if( ((Gen_001EFD20 *)(BezierProjectileBehavior *)this)->bfmeIsNew( (const BfmeThingDI *)other ) )
			rva0045C812( other );
	}
	else
	{
		const WeaponTemplate *weapon;
		if( m_bounceCount == 0 )
		{
			FXList::doFXPos( d->m_groundFX, obj->getPosition() );
			weapon = d->m_groundWeapon;
		}
		else
		{
			FXList::doFXPos( d->m_bounceFX, obj->getPosition() );
			weapon = d->m_bounceWeapon;
		}
		if( weapon )
			TheWeaponStore->createAndFireTempWeapon( weapon, obj, obj->getPosition() );

		if( m_bounceCount < d->m_maxBounces )
			rva0045CC72( 0 );
		else if( !d->m_detonateOnContact )
			rva0045C026();
		else
			rva0045C975( 0 );
	}
	return true;
}
