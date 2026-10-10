// ?rva002814EF@TerrainLogic@@QAE_NPBUCoord3D@@0PAU2@@Z
// partial score=0.93 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// ?rva002814EF@TerrainLogic@@QAE_NPBUCoord3D@@0PAU2@@Z
// retail 0x002814EF..0x0028170E (543 bytes), thiscall RET 0xC.
//
// TerrainLogic: where the segment p0..p1 meets a water area's surface.
// Called on TheTerrainLogic from 0x0008E032.  WorldBuilder twin 0x00C4A4F0
// (unnamed; AreaSet<WaterArea>::iterator) gives the statements: walk the
// water areas registered at +0x50 (eight-byte entries at +0x14, the area's
// shape through its virtual base at vbtable +0x18/+4, as the sibling
// rva0028170E 0x0028170E reads them), build the horizontal plane through
// the shape's point (rowed 0x0027C208) at the shape's height (vslot 8),
// intersect the segment with it (rowed PlaneClass::Compute_Intersection),
// put the point at p0 + (p1 - p0) * t and accept it when TerrainLogic
// vslot 0x4C (the water test) passes for it and the shape contains it
// (rowed 0x0030D111).  Otherwise out is zeroed and the result is false.
// The iterator equality goes through the rowed 29-byte two-word provider
// 0x0007E394 under its existing pair spelling, as in the sibling.  The
// original method name is not recovered.
//
// NEAR (banked): size matches (543); 20 instructions differ, all in the
// sub/scale/add block where cl hoists the x scale ahead of the z subtract
// while retail hoists the y scale.  Two probing tweaks are left in: the
// plane point takes (center.y, center.x) (retail sums y+x for the folded
// 0*x + 0*y of the plane distance; the natural (x, y) gives x+y) and the
// scale runs x z y (the order that scored best of all 216 statement
// orders; none was exact).  Inline Coord3D-style member helpers and a
// set(x, y, z) form did not change the schedule.

#define __PLACEMENT_VEC_NEW_INLINE
#include <utility>
#include <vector>
#include "Coord2D.h"
#include "Coord3D.h"
#include "wwmath.h"
#include "vector3.h"
#include "plane.h"

typedef float Real;
typedef bool Bool;

struct Rva0007E394Element
{
	unsigned opaque;
	bool operator<(const Rva0007E394Element &) const;
	bool operator==(const Rva0007E394Element &) const;
};

class Rva0027C208
{
public:
	void *rva0027C208(void *out);
};

class Rva0030D111Shape
{
public:
	virtual int count();
	virtual void point();
	virtual int height();
};
bool Rva0030D111Contains(Rva0030D111Shape *shape, const Coord2D *point);

struct Rva002814EFArea
{
	char m_pad00[0x18];
	int *m_baseOffsets;			// +0x18, vbtable

	Rva0030D111Shape *shape()
	{
		return reinterpret_cast<Rva0030D111Shape *>(reinterpret_cast<char *>(this) + 0x18 + m_baseOffsets[1]);
	}
};

struct Rva002814EFEntry
{
	unsigned m_key;
	Rva002814EFArea *m_area;
};

struct Rva002814EFIterator
{
	void *m_set;
	int m_index;

	Rva002814EFIterator(void *set, int index) : m_set(set), m_index(index) {}
};

struct Rva002814EFSet
{
	char m_pad00[0x14];
	_STL::vector<Rva002814EFEntry> m_entries;	// +0x14

	Rva002814EFIterator begin() { return Rva002814EFIterator(this, 0); }
	Rva002814EFIterator end() { return Rva002814EFIterator(this, m_entries.size()); }
};

typedef _STL::pair<const unsigned, Rva0007E394Element *> Rva002814EFEqualityWords;

static __forceinline bool Rva002814EFEqual(const Rva002814EFIterator &a, const Rva002814EFIterator &b)
{
	return *reinterpret_cast<const Rva002814EFEqualityWords *>(&a) == *reinterpret_cast<const Rva002814EFEqualityWords *>(&b);
}

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ, void *handle);

	Bool rva002814EF(const Coord3D *p0, const Coord3D *p1, Coord3D *out);

	char m_pad04[0x50 - 0x04];
	Rva002814EFSet *m_waterAreas;		// +0x50
};

Bool TerrainLogic::rva002814EF(const Coord3D *p0, const Coord3D *p1, Coord3D *out)
{
	for (Rva002814EFIterator it = m_waterAreas->begin(); !Rva002814EFEqual(it, m_waterAreas->end()); ++it.m_index)
	{
		Rva002814EFArea *area = reinterpret_cast<Rva002814EFSet *>(it.m_set)->m_entries[it.m_index].m_area;
		Coord2D center;
		((Rva0027C208 *)area->shape())->rva0027C208(&center);
		Vector3 point(center.y, center.x, (Real)area->shape()->height());
		PlaneClass plane(Vector3(0.0f, 0.0f, 1.0f), point);
		Real t = 0.0f;
		if (plane.Compute_Intersection(Vector3(p0->x, p0->y, p0->z), Vector3(p1->x, p1->y, p1->z), &t))
		{
			*out = *p1;
			out->x -= p0->x;
			out->y -= p0->y;
			out->z -= p0->z;
			out->x *= t;
			out->z *= t;
			out->y *= t;
			out->x += p0->x;
			out->y += p0->y;
			out->z += p0->z;
			if (isUnderwater(out->x, out->y, &out->z, 0, 0))
			{
				Rva0030D111Shape *shape = area->shape();
				Coord2D at;
				at.x = out->x;
				at.y = out->y;
				if (Rva0030D111Contains(shape, &at))
					return true;
			}
		}
	}
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
	return false;
}
