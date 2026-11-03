// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B3D1@AreaPolygonBase@@QAEXXZ, retail 0x0030B3D1..0x0030B5AF (478 B,
// RET 0): AreaPolygonBase's bounds refresh. WorldBuilder's twin 0x00BF6BA0
// (AreaPolygon code with MathCoord2D.h's inline Coord2D GetLengthSqrd /
// GetLength / Normalize asserts) gives the statement shapes: the point
// bounds, the half-extent radius (+0x20), then for every edge the squared
// distance of the centre to its end point, the edge's normalized projection
// (which only its sqrt survives in release, because the minimum is taken of
// the centre offset again) and finally sqrt(min) - 0.1 clamped at zero
// (+0x1C) and the dirty flag cleared (+0x24). Layout is shared with the
// rowed AreaPolygonBase siblings (point vector at +0, bounds +0x0C..+0x18).
// The method's original name is not established: the linker name stays
// address-derived. Callees: MathCoord2D's out-of-line operator- 0x001040AE
// and the CRT sqrt 0x0062921C.
#include <vector>
#include <math.h>
#include <float.h>
#include "../../../Libraries/Include/Lib/Region2D.h"

class MathCoord2D
{
public:
	MathCoord2D() {}
	// Keep inline copies without emitting a competing standalone constructor.
	__declspec(dllimport) __forceinline MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float initialX, float initialY) : x(initialX), y(initialY) {}
	~MathCoord2D() {}
	float Dot(const MathCoord2D &otherVector) const { return y * otherVector.y + x * otherVector.x; }
	MathCoord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	MathCoord2D &operator+=(const MathCoord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthSqrd() const { return y * y + x * x; }
	__forceinline float GetLength() const { return (float)sqrt(GetLengthSqrd()); }
	__forceinline void Normalize() { float inverseLength = 1.0f / GetLength(); x *= inverseLength; y *= inverseLength; }
	float x;
	float y;
};
MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right);

#include "../../Include/Common/AreaPolygonBase.h"

void AreaPolygonBase::rva0030B3D1()
{
	m_bounds.lo.x = m_bounds.lo.y = FLT_MAX;
	m_bounds.hi.x = m_bounds.hi.y = -FLT_MAX;

	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator end = (const MathCoord2D *)m_points.end();
	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator it;
	for (it = (const MathCoord2D *)m_points.begin(); it != end; ++it)
	{
		if (it->x < m_bounds.lo.x)
			m_bounds.lo.x = it->x;
		if (it->y < m_bounds.lo.y)
			m_bounds.lo.y = it->y;
		if (it->x > m_bounds.hi.x)
			m_bounds.hi.x = it->x;
		if (it->y > m_bounds.hi.y)
			m_bounds.hi.y = it->y;
	}

	float halfWidth = (m_bounds.hi.x - m_bounds.lo.x) / 2.0f;
	float halfHeight = (m_bounds.hi.y - m_bounds.lo.y) / 2.0f;
	m_radius = sqrt(halfHeight * halfHeight + halfWidth * halfWidth);

	float minimumDistanceSquared = FLT_MAX;
	MathCoord2D center((m_bounds.lo.x + m_bounds.hi.x) * 0.5f, (m_bounds.lo.y + m_bounds.hi.y) * 0.5f);
	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator prev = (const MathCoord2D *)m_points.end() - 1;
	for (it = (const MathCoord2D *)m_points.begin(); it != end; prev = it, ++it)
	{
		MathCoord2D toCenter = center - *it;
		float distanceSquared = toCenter.GetLengthSqrd();
		if (distanceSquared < minimumDistanceSquared)
			minimumDistanceSquared = distanceSquared;

		MathCoord2D edge(prev->x - it->x, prev->y - it->y);
		edge.Normalize();
		float projectionDistance = edge.Dot(toCenter);
		edge *= projectionDistance;
		edge += *it;

		distanceSquared = toCenter.GetLengthSqrd();
		if (distanceSquared < minimumDistanceSquared)
			minimumDistanceSquared = distanceSquared;
	}

	m_innerRadius = sqrt(minimumDistanceSquared) - 0.1f;
	if (m_innerRadius < 0.0f)
		m_innerRadius = 0.0f;
	m_dirty = false;
}
