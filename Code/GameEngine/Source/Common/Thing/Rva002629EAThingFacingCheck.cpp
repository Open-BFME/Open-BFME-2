// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?Rva002629EACheck@@YA_NPBVThing@@0@Z
// Retail 0x002629EA..0x00262A64 (122 bytes), static __cdecl bool helper.
//
// True when the summed 2D facing of two things points against the vector
// from the first to the second: dot(dirA + dirB, posB - posA) < 0. Its only
// caller is the 1258-byte object update at 0x0026CF11 (call at 0x0026D283
// with first argument edi and second ebx).
//
// Evidence: both calls go to the rowed Thing::getUnitDirectionVector2D
// (0x0030A25F); Thing's cached position x/y sit at +0x38/+0x3C (the donor
// Thing layout used by ThingGetUnitDirectionVector2D.cpp puts the angle at
// +0x44). The WorldBuilder twin 0x00E42520 (unnamed 269 bytes) copies both
// direction vectors member-wise into Coord3D locals then builds the sum and
// delta 2D vectors zero-initialised and assigned per component before the
// dot product test against 0.0f.
#include "Coord3D.h"

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	static float Dot_Product(const Vector2 &a, const Vector2 &b) { return a.X * b.X + a.Y * b.Y; }
	float X, Y;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	char m_pad[0x38];
	Coord3D m_cachedPos;
};

bool Rva002629EACheck(const Thing *a, const Thing *b)
{
	const Coord3D *d = a->getUnitDirectionVector2D();
	Coord3D dirA;
	dirA.x = d->x;
	dirA.y = d->y;
	dirA.z = d->z;
	const Coord3D *e = b->getUnitDirectionVector2D();
	Coord3D dirB;
	dirB.x = e->x;
	dirB.y = e->y;
	dirB.z = e->z;
	Vector2 sum(0.0f, 0.0f);
	sum.X = dirA.x + dirB.x;
	sum.Y = dirA.y + dirB.y;
	Vector2 delta(0.0f, 0.0f);
	delta.X = b->getPosition()->x - a->getPosition()->x;
	delta.Y = b->getPosition()->y - a->getPosition()->y;
	if (Vector2::Dot_Product(sum, delta) < 0.0f)
		return true;
	return false;
}
