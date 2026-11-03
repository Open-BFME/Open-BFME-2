// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// Keep MSVC math.h float overloads local; matched operations already inline.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")
// stlport
// Keep the MSVC float overloads local; the matched operations still inline.
#define inline static inline
#include <math.h>
#undef inline
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "prerts.h"
#include "coord.h"
#include "bezier_segment.h"
#include "bez_fwd_iterator.h"

#include "d3dx8math.h"
// bfme link decl-only begin
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int); }
// bfme link decl-only end

// Declaration-only: the rowed vector<Coord3D> members are bound, this TU emits no per-flag copy.
namespace _STL {
template <> void vector<Coord3D, allocator<Coord3D> >::_M_fill_insert(Coord3D*, size_t, const Coord3D&);
template <> void vector<Coord3D, allocator<Coord3D> >::_M_insert_overflow(Coord3D*, const Coord3D&, const __false_type&, size_t, bool);
template <> void vector<Coord3D, allocator<Coord3D> >::resize(size_t);
}

// vector<Coord3D>::erase is one shared STLport instantiation in retail
// (0x002A133B: this getSegmentPoints' clear at 0x0055A800, vector<Coord3D>::
// resize 0x000CA2F3 and AIStateMachine's ctor/clear all call it). These flags
// would compile a different copy that comes early in link order, so clear()
// and resize() here use the shared instantiation instead of emitting one.
template <> Coord3D *std::vector<Coord3D>::erase( Coord3D *first, Coord3D *last );

//-------------------------------------------------------------------------------------------------
// ?BezierSegment::BezierSegment present-unmatched
BezierSegment::BezierSegment()
{ 
	for(int i=0; i < 4; i++)
		m_controlPoints[i].zero();
}

//-------------------------------------------------------------------------------------------------
// ?BezierSegment::BezierSegment present-unmatched
BezierSegment::BezierSegment(Real x0, Real y0, Real z0, 
														 Real x1, Real y1, Real z1, 
														 Real x2, Real y2, Real z2, 
														 Real x3, Real y3, Real z3)
{
	m_controlPoints[0].x = x0;
	m_controlPoints[0].y = y0;
	m_controlPoints[0].z = z0;

	m_controlPoints[1].x = x1;
	m_controlPoints[1].y = y1;
	m_controlPoints[1].z = z1;

	m_controlPoints[2].x = x2;
	m_controlPoints[2].y = y2;
	m_controlPoints[2].z = z2;

	m_controlPoints[3].x = x3;
	m_controlPoints[3].y = y3;
	m_controlPoints[3].z = z3;
}

// ?BezierSegment::BezierSegment present-unmatched
BezierSegment::BezierSegment(Real controlPointCoordinates[12])
{
	m_controlPoints[0].x = controlPointCoordinates[0];
	m_controlPoints[0].y = controlPointCoordinates[1];
	m_controlPoints[0].z = controlPointCoordinates[2];

	m_controlPoints[1].x = controlPointCoordinates[3];
	m_controlPoints[1].y = controlPointCoordinates[4];
	m_controlPoints[1].z = controlPointCoordinates[5];

	m_controlPoints[2].x = controlPointCoordinates[6];
	m_controlPoints[2].y = controlPointCoordinates[7];
	m_controlPoints[2].z = controlPointCoordinates[8];

	m_controlPoints[3].x = controlPointCoordinates[9];
	m_controlPoints[3].y = controlPointCoordinates[10];
	m_controlPoints[3].z = controlPointCoordinates[11];
}

// ?BezierSegment::BezierSegment present-unmatched
BezierSegment::BezierSegment(const Coord3D& cp0, const Coord3D& cp1, const Coord3D& cp2, const Coord3D& cp3)
{
	m_controlPoints[0] = cp0;
	m_controlPoints[1] = cp1;
	m_controlPoints[2] = cp2;
	m_controlPoints[3] = cp3;
}

// ?BezierSegment::BezierSegment present-unmatched
BezierSegment::BezierSegment(Coord3D controlPoints[4])
{
	m_controlPoints[0] = controlPoints[0];
	m_controlPoints[1] = controlPoints[1];
	m_controlPoints[2] = controlPoints[2];
	m_controlPoints[3] = controlPoints[3];
}


//-------------------------------------------------------------------------------------------------
// ?BezierSegment::evaluateBezSegmentAtT present-unmatched
void BezierSegment::evaluateBezSegmentAtT(Real tValue, Coord3D *outResult) const

{
	if (!outResult)
		return;

	D3DXVECTOR4	tVec(tValue * tValue * tValue, tValue * tValue, tValue, 1);

	D3DXVECTOR4 xCoords(m_controlPoints[0].x, m_controlPoints[1].x, m_controlPoints[2].x, m_controlPoints[3].x);
	D3DXVECTOR4 yCoords(m_controlPoints[0].y, m_controlPoints[1].y, m_controlPoints[2].y, m_controlPoints[3].y);
	D3DXVECTOR4 zCoords(m_controlPoints[0].z, m_controlPoints[1].z, m_controlPoints[2].z, m_controlPoints[3].z);

	D3DXVECTOR4 basisWeights;
	D3DXVec4Transform(&basisWeights, &tVec, &BezierSegment::s_bezBasisMatrix);
	
	outResult->x = D3DXVec4Dot(&xCoords, &basisWeights);
	outResult->y = D3DXVec4Dot(&yCoords, &basisWeights);
	outResult->z = D3DXVec4Dot(&zCoords, &basisWeights);
}

//-------------------------------------------------------------------------------------------------
// The imported getSegmentPoints body had no retail row and called five undefined
// donor BezFwdIterator methods. The target tessellator and iterator are already
// recovered separately in Rva0055A7DBTess.cpp and Rva005C76C0Ctor.cpp. Keep their
// established target views; do not emit an unsupported second donor interface.

//-------------------------------------------------------------------------------------------------
// This function isn't terribly fast. There are alternatives, and if this is too slow, we can 
// take a look at the other approximations.
// There is no known close-form solution to this problem.
// ?BezierSegment::getApproximateLength present-unmatched
Real BezierSegment::getApproximateLength(Real withinTolerance) const
{
	/*
		How this works:
		We can determine the approximate length of a bezier segment by 
		L0 = |(P0,P1)| + |(P1,P2)| + |(P2,P3)| 
		L1 = |(P0,P3)|
		
		The length of the segment is approximately 1/2 L0 + 1/2 L1

		P1__P2
		/		 \
	 P0----P3

		The error in this is L1 - L0. If the error is too much, then we subdivide the curve and 
		try again.
	*/

	Coord3D p0p1 = { m_controlPoints[1].x - m_controlPoints[0].x,
									 m_controlPoints[1].y - m_controlPoints[0].y,
									 m_controlPoints[1].z - m_controlPoints[0].z, };

	Coord3D p1p2 = { m_controlPoints[2].x - m_controlPoints[1].x,
									 m_controlPoints[2].y - m_controlPoints[1].y,
									 m_controlPoints[2].z - m_controlPoints[1].z, };

	Coord3D p2p3 = { m_controlPoints[3].x - m_controlPoints[2].x,
									 m_controlPoints[3].y - m_controlPoints[2].y,
									 m_controlPoints[3].z - m_controlPoints[2].z, };

	Coord3D p0p3 = { m_controlPoints[3].x - m_controlPoints[0].x,
									 m_controlPoints[3].y - m_controlPoints[0].y,
									 m_controlPoints[3].z - m_controlPoints[0].z, };

	Real chordLength = p0p3.length();
	Real controlPolygonLength = p0p1.length() + p1p2.length() + p2p3.length();

	if ((controlPolygonLength - chordLength) > withinTolerance) {
		BezierSegment firstHalf, seg2;
		splitSegmentAtT(0.5f, firstHalf, seg2);
		return (firstHalf.getApproximateLength(withinTolerance) + seg2.getApproximateLength(withinTolerance));
	}

	return (INT_TO_REAL(chordLength + controlPolygonLength) / 2.0f);
}

//-------------------------------------------------------------------------------------------------
// ?splitSegmentAtT@BezierSegment@@ present-unmatched
void BezierSegment::splitSegmentAtT(Real tValue, BezierSegment &outSeg1, BezierSegment &outSeg2) const
{
	// I think there are faster ways to do this. Could someone clue me in?

	Coord3D p0p1 = { m_controlPoints[1].x - m_controlPoints[0].x,
									 m_controlPoints[1].y - m_controlPoints[0].y,
									 m_controlPoints[1].z - m_controlPoints[0].z, };

	Coord3D p1p2 = { m_controlPoints[2].x - m_controlPoints[1].x,
									 m_controlPoints[2].y - m_controlPoints[1].y,
									 m_controlPoints[2].z - m_controlPoints[1].z, };

	Coord3D p2p3 = { m_controlPoints[3].x - m_controlPoints[2].x,
									 m_controlPoints[3].y - m_controlPoints[2].y,
									 m_controlPoints[3].z - m_controlPoints[2].z, };

	p0p1.scale(tValue);
	p1p2.scale(tValue);
	p2p3.scale(tValue);

	p0p1.add(&m_controlPoints[0]);
	p1p2.add(&m_controlPoints[1]);
	p2p3.add(&m_controlPoints[2]);

	Coord3D triLeft = { p1p2.x - p0p1.x, 
											p1p2.y - p0p1.y, 
											p1p2.z - p0p1.z, };

	Coord3D triRight = { p2p3.x - p1p2.x, 
											 p2p3.y - p1p2.y, 
											 p2p3.z - p1p2.z, };

	triLeft.scale(tValue);
	triRight.scale(tValue);

	triLeft.add(&p0p1);
	triRight.add(&p1p2);

	outSeg1.m_controlPoints[0] = m_controlPoints[0];
	outSeg1.m_controlPoints[1] = p0p1;
	outSeg1.m_controlPoints[2] = triLeft;
	evaluateBezSegmentAtT(tValue, &outSeg1.m_controlPoints[3]);

	outSeg2.m_controlPoints[0] = outSeg1.m_controlPoints[3];
	outSeg2.m_controlPoints[1] = triRight;
	outSeg2.m_controlPoints[2] = p2p3;
	outSeg2.m_controlPoints[3] = m_controlPoints[3];	
}

//-------------------------------------------------------------------------------------------------
// The Basis Matrix for a bezier segment
// ?BezierSegment::s_bezBasisMatrix present-unmatched
const D3DXMATRIX BezierSegment::s_bezBasisMatrix(
	-1.0f,  3.0f, -3.0f,  1.0f,
	 3.0f, -6.0f,  3.0f,  0.0f,
	-3.0f,  3.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,  0.0f
);
