// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Ported from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/Line2D.cpp); the function bodies are verbatim.
//
// BFME 2 spells Coord2D as a class (retail exports
// ??0LineSegment2D@@QAE@ABVCoord2D@@0@Z and
// ?ClosestPointOnLineSegment@@YA?AVCoord2D@@ABULineSegment2D@@ABV1@@Z), and
// the three length() calls in ShortestDistancePointToSegment2D 0x0025F916 go
// to the Coord2D::length COMDAT 0x00003755 (row in coord2d.cpp). So this unit uses the
// canonical Coord2D header instead of Zero Hour's struct from Lib/BaseType.h,
// and its Coord2D signatures carry the class spelling (PAV/PBV) that callers
// such as the AIGroup formation move 0x00372571 link against. ICoord2D,
// IRegion2D and Coord3D stay structs (ClipLine2D and the Coord3D overloads keep
// their PAU/PBU spellings). The few Zero Hour declarations the bodies need
// (Bool/Int/Real, sqr, the Line2D.h prototypes with their default argument) are
// restated here instead of pulling in PreRTS.h.
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

// FILE: Line2D.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, January 2002
// Desc:   Some helpful 2D stuff
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>

// Coord2D::length is an inline function in BFME 2 (coord2d.cpp defines it
// inline; retail keeps one 53-byte COMDAT at 0x00003755, which that unit's row
// owns). Its body has to be visible here: ShortestDistancePointToSegment2D
// homes segment, segAB and intersectSegment in one slot ([ebp-8]), which cl
// only does when it can see that length() keeps no pointer to its object. The
// copy this unit emits is byte-identical to the retail COMDAT.
inline float Coord2D::length() const
{
	return (float)sqrt(x * x + y * y);
}

typedef bool Bool;
typedef int Int;
typedef float Real;

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif

template <typename NUM>
inline NUM sqr(NUM x)
{
	return x*x;
}

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;					// bounds of 2D rectangular region
};

// GameClient/Line2D.h prototypes
extern Bool ClipLine2D( ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2,
												IRegion2D *clipRegion );
extern Bool IntersectLine2D( const Coord2D *a, const Coord2D *b,
															const Coord2D *c, const Coord2D *d,
															Coord2D *intersection = NULL);
extern Bool PointInsideRect2D( const Coord2D *bl, const Coord2D *tl,
															 const Coord2D *br, const Coord2D *tr,
															 const Coord2D *inputPoint);
extern Bool Coord3DInsideRect2D( const Coord3D *inputPoint, const Coord2D *tl, const Coord2D *br );
extern void ScaleRect2D( Coord2D *tl, Coord2D *br, Real scaleFactor );
extern Bool PointInsideRect3D( const Coord3D *bl, const Coord3D *tl,
															 const Coord3D *br, const Coord3D *tr,
															 const Coord3D *inputPoint);
extern Bool PointInsideArea2D( const Coord2D *ptToTest,
															 const Coord2D *area,
															 Int numPointsInArea);
extern Bool PointInsideArea2D( const Coord3D *ptToTest,
															 const Coord3D *area,
															 Int numPointsInArea);
extern void ShortestDistancePointToSegment2D( const Coord2D *a, const Coord2D *b, const Coord2D *pt,
																						 Real *outDistance, Coord2D *outPosition, Real *outU );

// PRIVATE ////////////////////////////////////////////////////////////////////////////////////////
#define CLIP_LEFT   0x01
#define CLIP_RIGHT  0x02
#define CLIP_BOTTOM 0x04
#define CLIP_TOP	  0x08

// PUBLIC /////////////////////////////////////////////////////////////////////////////////////////


// STATIC /////////////////////////////////////////////////////////////////////////////////////////
const static Coord2D reallyFarPoint = { 1000000.0, 1000000.0 };

//-------------------------------------------------------------------------------------------------
/** Clip a line to the region provided.  The source line runs from p1 to p2, and is clipped
	* using the clipRegion.  The resulting line goes from c1 to c2
	*
	* Return values: 
	*				TRUE  - Line is visible
	*				FALSE - Line is not visible
	*/
//-------------------------------------------------------------------------------------------------
Bool ClipLine2D( ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2,
								 IRegion2D *clipRegion )
{
	Int x1, y1, x2, y2;
	Int clipLeft;
	Int clipRight;
	Int clipTop;
	Int clipBottom;
	Int clipCode1;
	Int clipCode2;
	Int diff;

	// Use clip window that includes bottom right pixel
	clipLeft = clipRegion->lo.x;
	clipRight = clipRegion->hi.x;
	clipTop = clipRegion->lo.y;
	clipBottom = clipRegion->hi.y;
/*
	clipLeft = gfxCurrentContext->clipRect1.left;
	clipRight = gfxCurrentContext->clipRect1.right;
	clipTop = gfxCurrentContext->clipRect1.top;
	clipBottom = gfxCurrentContext->clipRect1.bottom;

	x1 = *px1;
	y1 = *py1;
	x2 = *px2;
	y2 = *py2;
*/

	x1 = p1->x;
	y1 = p1->y;
	x2 = p2->x;
	y2 = p2->y;
		
	// Test first point
	clipCode1 = 0;

	if (x1 < clipLeft)
		clipCode1 = CLIP_LEFT;
	else
	if (x1 > clipRight)
		clipCode1 = CLIP_RIGHT;

	if (y1 < clipTop)
		clipCode1 |= CLIP_TOP;
	else
	if (y1 > clipBottom)
		clipCode1 |= CLIP_BOTTOM;


	// Test second point
	clipCode2 = 0;

	if (x2 < clipLeft)
		clipCode2 = CLIP_LEFT;
	else
	if (x2 > clipRight)
		clipCode2 = CLIP_RIGHT;

	if (y2 < clipTop)
		clipCode2 |= CLIP_TOP;
	else
	if (y2 > clipBottom)
		clipCode2 |= CLIP_BOTTOM;


	// Both points inside window?
	if ((clipCode1 | clipCode2) == 0)
	{

		*c1 = *p1;
		*c2 = *p2;
		return TRUE;

	}  // end if

	// Both points outside window?
	if (clipCode1 & clipCode2)
		return FALSE;

	// First point outside window?
	if (clipCode1)
	{
		if (clipCode1 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x1 += (x2 - x1) * (clipTop - y1) / diff;
			y1 = clipTop;
		}
		else
		if (clipCode1 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x1 += (x2 - x1) * (clipBottom - y1) / diff;
			y1 = clipBottom;
		}

		if (x1 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y1 += (y2 - y1) * (clipRight - x1) / diff;
			x1 = clipRight;
		}
		else
		if (x1 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y1 += (y2 - y1) * (clipLeft - x1) / diff;
			x1 = clipLeft;
		}
	}

	// Second point outside window?
	if (clipCode2)
	{
		if (clipCode2 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x2 += (x2 - x1) * (clipTop - y2) / diff;
			y2 = clipTop;
		}
		else
		if (clipCode2 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return FALSE;
			x2 += (x2 - x1) * (clipBottom - y2) / diff;
			y2 = clipBottom;
		}

		if (x2 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y2 += (y2 - y1) * (clipRight - x2) / diff;
			x2 = clipRight;
		}
		else
		if (x2 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return FALSE;
			y2 += (y2 - y1) * (clipLeft - x2) / diff;
			x2 = clipLeft;
		}
	}

  c1->x = x1;
	c1->y = y1;
	c2->x = x2;
	c2->y = y2;

/*
	*px1 = x1;
	*py1 = y1;
	*px2 = x2;
	*py2 = y2;
*/

	// Line is visible
	return (x1 >= clipLeft && x1 <= clipRight &&
		    y1 >= clipTop && y1 <= clipBottom &&
			x2 >= clipLeft && x2 <= clipRight &&
			y2 >= clipTop && y2 <= clipBottom);

}  // end ClipLine2D


// This solution uses the 
// http://www.faqs.org/faqs/graphics/algorithms-faq/ 
// Subject 1.03
Bool IntersectLine2D( const Coord2D *a, const Coord2D *b, 
										   const Coord2D *c, const Coord2D *d, 
											 Coord2D *intersection)
{
	if (!a || !b || !c || !d) {
		// sanity. Lines that do not have endpoints do not intersect.
		return false;
	}

	Real r, s, denom;

	denom = ((b->x - a->x) * (d->y - c->y) - (b->y - a->y) * (d->x - c->x));
	if (denom == 0) {
		// the lines are parallel.
		return false;
	}

	r = ((a->y - c->y) * (d->x - c->x) - (a->x - c->x) * (d->y - c->y) ) / denom;
	s = ((a->y - c->y) * (b->x - a->x) - (a->x - c->x) * (b->y - a->y) ) / denom;

	if (0 <= r && r <= 1 && 0 <= s && s <= 1) {
		// The lines intersect.
		if (intersection) {
			intersection->x = a->x + r * (b->x - a->x);
			intersection->y = a->y + r * (b->y - a->y);
		}

		return true;
	}

	return false;
}

// determines whether a point lies within a rectangle. Doesnt' determine whether the shape is
// actually a rectangle or not.
Bool PointInsideRect2D(const Coord2D *bl, const Coord2D *tl, const Coord2D *br, const Coord2D *tr, 
											 const Coord2D *inputPoint)
{
	if (!(bl && br && tl && tr && inputPoint)) {
		return FALSE;
	}

	Real uVal;
	// we're actually only interested in if the U value is (0,1)
	ShortestDistancePointToSegment2D(bl, tl, inputPoint, NULL, NULL, &uVal);
	if (uVal <= 0.0f || uVal >= 1.0f) {
		return false;
	}

	ShortestDistancePointToSegment2D(bl, br, inputPoint, NULL, NULL, &uVal);

	return (uVal > 0.0f && uVal < 1.0f);
}

// convenience. Just prunes out the Z coordinate for a call to PointInsideRect2D
Bool PointInsideRect3D(const Coord3D *bl, const Coord3D *tl, const Coord3D *br, const Coord3D *tr,
											 const Coord3D *inputPoint)
{
	Coord2D bl2d, tl2d, br2d, tr2d, pt;
	bl2d.x = bl->x;
	bl2d.y = bl->y;
	tl2d.x = tl->x;
	tl2d.y = tl->y;
	br2d.x = br->x;
	br2d.y = br->y;
	tr2d.x = tr->x;
	tr2d.y = tr->y;

	pt.x = inputPoint->x;
	pt.y = inputPoint->y;

	return PointInsideRect2D(&bl2d, &br2d, &tl2d, &tr2d, &pt);
}


// This function uses even-odd winding to determine whether a point is inside an area.
Bool PointInsideArea2D(const Coord2D *ptToTest, const Coord2D *area, const Int numPointsInArea)
{
	int numIntersections = 0;
	for (int i = 0; i < numPointsInArea; ++i) {
		if (IntersectLine2D(ptToTest, &reallyFarPoint, &area[i], &area[(i + 1) % numPointsInArea])) {
			++numIntersections;
		}
	}
	return (numIntersections % 2 == 1);
}

// This function uses even-odd winding to determine whether a point is inside an area.
Bool PointInsideArea2D( const Coord3D *ptToTest, const Coord3D *area, Int numPointsInArea)
{
	int numIntersections = 0;
	Coord2D pt2D, area2D1, area2D2;
	pt2D.x = ptToTest->x;
	pt2D.y = ptToTest->y;

	for (int i = 0; i < numPointsInArea; ++i) {
		area2D1.x = area[i].x;
		area2D1.y = area[i].y;
		area2D2.x = area[(i + 1) % numPointsInArea].x;
		area2D2.y = area[(i + 1) % numPointsInArea].y;
		if (IntersectLine2D(&pt2D, &reallyFarPoint, &area2D1, &area2D2)) {
			++numIntersections;
		}
	}
	if ((numIntersections % 2) == 1)
		return true;
	return false;
}

///< Checks if a point is inside a perfect rectangle (top left and bottom right)
Bool Coord3DInsideRect2D( const Coord3D *inputPoint, const Coord2D *tl, const Coord2D *br )
{
	if( inputPoint->x >= tl->x && inputPoint->x <= br->x )
	{
		if( inputPoint->y >= tl->y && inputPoint->y <= br->y )
		{
			return TRUE;
		}
	}
	return FALSE;
}

///< Scales a rect by a factor either growing or shrinking it.
void ScaleRect2D( Coord2D *tl, Coord2D *br, Real scaleFactor )
{
	scaleFactor = scaleFactor-1.0f; // We are starting with tl,br, so scaling it by 1 means adding 0 to it.

	Real deltaWidth = (br->x - tl->x) * scaleFactor * 0.5f;
	Real deltaHeight = (br->y - tl->y) * scaleFactor * 0.5f;

	tl->x -= deltaWidth;
	tl->y -= deltaHeight;

	br->x += deltaWidth;
	br->y += deltaHeight;
}


// Solution taken from http://astronomy.swin.edu.au/~pbourke/geometry/pointline/
void ShortestDistancePointToSegment2D( const Coord2D *a, const Coord2D *b, const Coord2D *pt,
																			 Real *outDistance, Coord2D *outPosition, Real *outU )
{
	if (!a || !b || !pt) {
		return;
	}

	if (a->x == b->x && a->y == b->y) {
		// special case, its simply pt to pt.
		Coord2D segment;
		segment.x = pt->x - a->x;
		segment.y = pt->y - a->y;
		if (outDistance) {		
			(*outDistance) = segment.length();
		}

		if (outPosition) {
			(*outPosition).x = a->x;
			(*outPosition).y = a->y;
		}

		if (outU) {
			(*outU) = 0.5;
		}
		return;
	}

	Coord2D segAB;
	segAB.x = b->x - a->x;
	segAB.y = b->y - a->y;

	// General case
	Real u = ((pt->x - a->x) * (b->x - a->x) + (pt->y - a->y) * (b->y - a->y)) /
					 sqr(segAB.length());

	Coord2D intersectSegment;

	intersectSegment.x = a->x + u * (b->x - a->x);
	intersectSegment.y = a->y + u * (b->y - a->y);


	if (outPosition) {
		(*outPosition) = intersectSegment;
	}

	if (outDistance) {
		(*outDistance) = intersectSegment.length();
	}
	
	if (outU) {
		(*outU) = u;
	}

}

// Clean BF1 9cbfb551fe Common/Rva00433740IndexedFloat.cpp semantic donor, normal O1/SSE/G7.
// Native 0025FB7A..0025FB85 has its own complete RET boundary and establishes
// receiver24 indexed FLD, RET4. Original owner and full array bound remain
// unresolved; this separate address-owned view models only observed accesses.
class Rva0025FB7AArray {
public: float getValue(unsigned int index) const;
private: unsigned char unknown[0x24]; float values[1];
};
float Rva0025FB7AArray::getValue(unsigned int index) const { return values[index]; }
