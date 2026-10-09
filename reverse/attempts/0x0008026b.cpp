// ?rva0008026B@Rva0008026BStandingWaveQuery@@QAEXPAURva0008026BWaveInfo@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva0008026B@Rva0008026BStandingWaveQuery@@QAEXPAURva0008026BWaveInfo@@@Z,
// retail 0x0008026B..0x00080637 (972B), thiscall ret 4 (`this` unused); sole
// caller 0x00082EAA passes a query record built from a position.
//
// Finds the standing-wave edge nearest to the query position: the terrain
// height under it (TheTerrainRenderObject slot 145, zeroed when the cell query
// 0x0006B114 fails) gives the height above ground; below 100 it walks the
// AreaSet<StandingWaveArea> at +0x124 of the water object (0x00DE2000), skips
// areas whose +0xA0 word is zero, and keeps the segment whose midpoint is
// closest and within half its length plus 50. The record receives the
// segment's perpendicular (Vector2 rotated by -PI/2 and normalised), the
// 100 height limit, the half length, the midpoint and the ground height.
//
// Evidence (target): WorldBuilder twin 0x7405A0 inlines Vector3 operators and
// Length, Vector2::Rotate / Normalize / Length2, AreaSet<StandingWaveArea>
// const_iterator::getPtr and AreaPolygonBase::getPoint (asserts in vector3.h
// and vector2.h); retail calls the rowed cursor equality 0x0007E394, the rowed
// +0xA0 getter 0x0030C94A and WWMath::Inv_Sqrt 0x0004233A. Class, method and
// record names are descriptive; the original owner is not identified.

#include "Coord2D.h"
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

class WWMath
{
public:
	static __forceinline Real Sqrt(Real val)
	{
		Real retval;
		__asm {
			fld [val]
			fsqrt
			fstp [retval]
		}
		return retval;
	}
	static __forceinline Real Cos(Real val)
	{
		Real retval;
		__asm {
			fld [val]
			fcos
			fstp [retval]
		}
		return retval;
	}
	static __forceinline Real Sin(Real val)
	{
		Real retval;
		__asm {
			fld [val]
			fsin
			fstp [retval]
		}
		return retval;
	}
	static Real __fastcall Inv_Sqrt(Real a);
};

class Vector2
{
public:
	Real X;
	Real Y;

	__forceinline Vector2() {}
	__forceinline Vector2(const Vector2 &v) { X = v.X; Y = v.Y; }
	__forceinline Vector2(Real x, Real y) { X = x; Y = y; }
	__forceinline Vector2 &operator=(const Vector2 &v) { X = v[0]; Y = v[1]; return *this; }
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }

	__forceinline Real Length2() const { return (X * X + Y * Y); }

	__forceinline void Normalize()
	{
		Real len2 = Length2();
		if (len2 != 0.0f)
		{
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
		}
	}

	__forceinline void Rotate(Real theta)
	{
		Rotate(WWMath::Sin(theta), WWMath::Cos(theta));
	}

	__forceinline void Rotate(Real s, Real c)
	{
		Real new_x = X * c + Y * -s;
		Real new_y = X * s + Y * c;
		X = new_x;
		Y = new_y;
	}
};

__forceinline Vector2 operator-(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.X - b.X, a.Y - b.Y);
}

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline Vector3() {}
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }

	__forceinline Real Length() const { return WWMath::Sqrt(Length2()); }
	__forceinline Real Length2() const { return X * X + Y * Y + Z * Z; }
};

__forceinline Vector3 operator*(const Vector3 &a, Real k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

__forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

__forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class BaseHeightMapRenderObjClass
{
public:
	PAD_VIRTUALS10(v0) PAD_VIRTUALS10(v1) PAD_VIRTUALS10(v2) PAD_VIRTUALS10(v3) PAD_VIRTUALS10(v4)
	PAD_VIRTUALS10(v5) PAD_VIRTUALS10(v6) PAD_VIRTUALS10(v7) PAD_VIRTUALS10(v8) PAD_VIRTUALS10(v9)
	PAD_VIRTUALS10(w0) PAD_VIRTUALS10(w1) PAD_VIRTUALS10(w2) PAD_VIRTUALS10(w3)
	virtual void s140(); virtual void s141(); virtual void s142(); virtual void s143(); virtual void s144();
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal);	// slot 145
	bool rva0006B114(float x, float y);					// 0x0006B114
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// The +0xA0 word getter at 0x0030C94A (rowed under this spelling).
class Rva0030C94ADwordField
{
public:
	Int get() const;
};

class AreaPolygonBase
{
public:
	Int getNumPoints() const { return m_points_last - m_points_first; }
	const Coord2D *getPoint(Int i) const { return &m_points_first[i]; }
private:
	Coord2D *m_points_first;			// +0x00
	Coord2D *m_points_last;				// +0x04
};

class StandingWaveArea
{
public:
	Int isActive() const { return ((const Rva0030C94ADwordField *)this)->get(); }
	const AreaPolygonBase &getPolygon() const { return m_polygon; }
private:
	unsigned char m_pad00[0x38];
	AreaPolygonBase m_polygon;			// +0x38
};

template <class T> class AreaSet;

struct Rva0008026BAreaSlot
{
	Int key;
	StandingWaveArea *area;
};

template <class T> class AreaSet
{
public:
	class const_iterator
	{
	public:
		const_iterator(AreaSet *set, Int index) : m_set(set), m_index(index) {}
		const_iterator(const const_iterator &it) : m_set(it.m_set), m_index(it.m_index) {}
		T *getPtr() const { return m_set->m_first[m_index].area; }
		const_iterator operator++(int)
		{
			const_iterator old(*this);
			++m_index;
			return old;
		}
		bool operator!=(const const_iterator &it) const { return !(*this == it); }
		friend bool operator==(const const_iterator &a, const const_iterator &b)
		{
			return a.m_set == b.m_set && a.m_index == b.m_index;
		}
		AreaSet *m_set;
		Int m_index;
	};

	const_iterator begin() { return const_iterator(this, 0); }
	const_iterator end() { return const_iterator(this, m_last - m_first); }

	unsigned char m_pad00[0x14];
	Rva0008026BAreaSlot *m_first;			// +0x14
	Rva0008026BAreaSlot *m_last;			// +0x18
};


class Rva0008026BWaterObject
{
public:
	AreaSet<StandingWaveArea> *getStandingWaves() const { return m_standingWaves; }
private:
	unsigned char m_pad000[0x124];
	AreaSet<StandingWaveArea> *m_standingWaves;	// +0x124
};

extern void *W3DGCData00DE2000;

struct Rva0008026BWaveInfo
{
	Real x;						// +0x00 query position
	Real y;
	Real z;
	Real nearestX;					// +0x0C nearest segment midpoint
	Real nearestY;
	Real groundHeight;				// +0x14
	Int index;					// +0x18
	Real directionX;				// +0x1C perpendicular of the segment
	Real directionY;
	Real maxHeight;					// +0x24
	Real halfLength;				// +0x28
};

class Rva0008026BStandingWaveQuery
{
public:
	void rva0008026B(Rva0008026BWaveInfo *info);
};

void Rva0008026BStandingWaveQuery::rva0008026B(Rva0008026BWaveInfo *info)
{
	info->index = -1;

	Real groundHeight = TheTerrainRenderObject ? TheTerrainRenderObject->getHeightMapHeight(info->x, info->y, 0) : 0.0f;
	if (TheTerrainRenderObject && !TheTerrainRenderObject->rva0006B114(info->x, info->y))
		groundHeight = 0.0f;

	Real heightAbove = info->z - groundHeight;
	if (heightAbove < 0.0f)
		heightAbove = 0.0f;

	Vector2 direction(1.0f, 0.0f);
	Vector3 nearest(100000.0f, 100000.0f, info->z);
	Real nearestHalfLength = 0.0f;
	Real maxHeight = 100.0f;
	if (heightAbove < maxHeight)
	{
		Real nearestDist = 100000.0f;
		Vector2 segStart(0.0f, 0.0f);
		Vector2 segEnd(0.0f, 0.0f);
		AreaSet<StandingWaveArea> *areas = ((Rva0008026BWaterObject *)W3DGCData00DE2000)->getStandingWaves();
		for (AreaSet<StandingWaveArea>::const_iterator it = areas->begin(); it != areas->end(); it++)
		{
			StandingWaveArea *area = it.getPtr();
			if (!area->isActive())
				continue;
			Int numPoints = area->getPolygon().getNumPoints();
			if (numPoints < 2)
				continue;
			for (Int i = 0; i < numPoints - 1; ++i)
			{
				const Coord2D *p0 = area->getPolygon().getPoint(i);
				const Coord2D *p1 = area->getPolygon().getPoint(i + 1);
				Vector3 a(p0->x, p0->y, info->z);
				Vector3 b(p1->x, p1->y, info->z);
				Vector3 mid = (a + b) * 0.5f;
				Vector3 pos(info->x, info->y, info->z);
				Real dist = (pos - mid).Length();
				Real halfLength = 0.5f * (b - a).Length();
				if (halfLength + 50.0f > dist && dist < nearestDist)
				{
					nearestDist = dist;
					segStart = Vector2(p0->x, p0->y);
					segEnd = Vector2(p1->x, p1->y);
					nearest = mid;
					nearestHalfLength = halfLength;
				}
			}
		}
		if (nearestDist != 100000.0f)
		{
			direction = segEnd - segStart;
			direction.Rotate(-1.5707964f);
			direction.Normalize();
		}
	}

	info->directionX = direction.X;
	info->directionY = direction.Y;
	info->maxHeight = maxHeight;
	info->halfLength = nearestHalfLength;
	info->nearestX = nearest.X;
	info->nearestY = nearest.Y;
	info->groundHeight = groundHeight;
}
