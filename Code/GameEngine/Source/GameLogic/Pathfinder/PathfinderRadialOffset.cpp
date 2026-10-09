// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Semantic donor: BF1 f98983a7d3 AIPathfind.cpp computeNormalRadialOffset
// and circleClipsTallBuilding, with ZH pathfinding as the underlying guide.
// Native BF2 002E7A62..002E7B02 RET and callers 002E9BE5/002F3392 prove
// the offset helper's purpose, scalar position +38 and radius +B8. WB names
// the helper ComputeNormalRadialOffset and caller CircleClipsTallBuilding;
// retain neutral ABI spellings because exact source signatures remain inferred.
// Static C++ lets cl choose the measured EAX/ECX/EBX plus two-stack-arg ABI.
// Scalar position copy through canonical Coord3D makes all160 helper bytes exact.
// The normalize leaf's native no-throw callgraph supports helper throw();
// without it the caller has an extra EH state store after the second temporary.
// Native caller292 RET20 independently measures two kind66 filter temporaries
// and first-object/success lifetime. Its four-arg partition query and 28-byte
// masks use established providers; inline destruction resets base BC26E0.
typedef float Real;
#include "Coord3D.h"
struct Rva002E7A62Position : Coord3D
{
	Rva002E7A62Position(const Coord3D &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
	}
};
class Object
{
  public:
	unsigned char pad[0x38];
	Coord3D position;
	unsigned char pad44[0xB8 - 0x44];
	float radius;
	const Coord3D *getPosition() const
	{
		return &position;
	}
	float getRadius() const
	{
		return radius;
	}
};
static void Rva002E7A62Offset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius) throw()
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Rva002E7A62Position objPos(*obj->getPosition());
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real crossProduct = dx * objDy - dy * objDx;
	Coord3D fromToNormal;
	fromToNormal.z = 0;
	if (crossProduct > 0)
	{
		fromToNormal.x = dy;
		fromToNormal.y = -dx;
	}
	else
	{
		fromToNormal.x = -dy;
		fromToNormal.y = dx;
	}
	fromToNormal.normalize();
	insert = *obj->getPosition();
	insert.x += fromToNormal.x * radius;
	insert.y += fromToNormal.y * radius;
}

class BfmeFixedStorage0004543D
{
	unsigned char bytes[28];
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int, int) throw();
	unsigned int bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];
class Rva000421C8
{
  public:
	Rva000421C8() : next(0)
	{
	}
	virtual ~Rva000421C8()
	{
	}
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *next;
};
class Rva0004584D : public Rva000421C8
{
  public:
	Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
	virtual bool allow(Object *);
	BfmeFixedStorage0004543D a, b;
};
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
class Pathfinder
{
  public:
	bool rva002E9BE5(const Coord3D *, const Coord3D *, float, unsigned int, Coord3D *);
};
bool Pathfinder::rva002E9BE5(const Coord3D *from, const Coord3D *to, float circleRadius, unsigned int ignoreBuilding,
							 Coord3D *adjustTo)
{
	Object *tallBuilding =
		ThePartitionManager->getClosestObject(to, circleRadius, 1,
											  &Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 66),
														   *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype));
	if (tallBuilding)
	{
		float radius = tallBuilding->getRadius() + 20.0f;
		Rva002E7A62Offset(*from, *adjustTo, *to, tallBuilding, circleRadius + radius);
		Object *otherTallBuilding = ThePartitionManager->getClosestObject(
			adjustTo, circleRadius, 1,
			&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 66),
						 *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype));
		if (otherTallBuilding && otherTallBuilding != tallBuilding)
		{
			radius = otherTallBuilding->getRadius() + 20.0f;
			Rva002E7A62Position tmpTo(*adjustTo);
			Rva002E7A62Offset(*from, *adjustTo, tmpTo, otherTallBuilding, circleRadius + radius);
		}
		return true;
	}
	return false;
}
