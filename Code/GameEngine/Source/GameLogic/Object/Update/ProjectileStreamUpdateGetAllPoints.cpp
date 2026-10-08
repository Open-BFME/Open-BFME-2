// cl: /GX /Op /DNDEBUG /MD
// ?getAllPoints@ProjectileStreamUpdate@@QAEXPAVVector3@@PAH@Z retail
// 0x0033F090 143B, between considerDying (0x0033F06B) and update
// (0x0033F11F) in the unit's retail range.
//
// BFME 2 simplified Zero Hour's body: it no longer looks up the owner to
// skim the stream over a vehicle roof, and it reads each projectile's
// position through its Drawable (Object::getDrawable 0x005508E2, then
// BFME 2's own interpolating Drawable::getPosition 0x002763E6, which Zero
// Hour's header does not declare - hence the local views below). Fields as
// the unit's addProjectile reads them: the ID ring at +0x20, the next free
// index at +0x70 and the first valid index at +0x74.
//
// Built on the banked muse-02 body (0.95): /Op is what keeps all three
// coordinate copies in xmm registers (without it Y is copied through an
// integer register), and the X store is shared by both arms after the
// branch, as retail's tail-merged movss [edi-8] shows.

typedef int Int;
typedef float Real;

enum ObjectID
{
	INVALID_ID = -1
};

struct Coord3D
{
	Real x, y, z;
};

class Vector3
{
public:
	float X, Y, Z;
};

// Drawable::getPosition (0x002763E6) is rowed as BFMERopeDrawable::getPosition.
class Drawable;
class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Object
{
public:
	Drawable *getDrawable() const;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

enum
{
	MAX_PROJECTILE_STREAM = 20
};

class ProjectileStreamUpdate
{
public:
	void getAllPoints( Vector3 *points, Int *count );

private:
	char m_unrecovered00[ 0x20 ];
	ObjectID m_projectileIDs[ MAX_PROJECTILE_STREAM ];	///< 0x20
	Int m_nextFreeIndex;								///< 0x70
	Int m_firstValidIndex;								///< 0x74
};

void ProjectileStreamUpdate::getAllPoints( Vector3 *points, Int *count )
{
	Int pointCount = 0;
	Int pointIndex = m_firstValidIndex;
	Vector3 *out = points;

	while( pointIndex != m_nextFreeIndex )
	{
		// Holes in the middle get 0,0,0; the circular array unrolls into the flat one.
		Real x, y, z;
		Object *projectile = TheGameLogic->findObjectByID( m_projectileIDs[pointIndex] );
		if( projectile )
		{
			Drawable *draw = projectile->getDrawable();
			if( draw )
			{
				const Coord3D *pos = ((const BFMERopeDrawable *)draw)->getPosition();
				x = pos->x;
				y = pos->y;
				z = pos->z;
				out->Y = y;
				out->Z = z;
			}
			else
			{
				out->Y = 0;
				out->Z = 0;
				x = 0;
			}
		}
		else
		{
			out->Y = 0;
			out->Z = 0;
			x = 0;
		}

		pointIndex = (pointIndex + 1) % MAX_PROJECTILE_STREAM;
		pointCount++;
		out->X = x;
		++out;
	}

	*count = pointCount;
}
