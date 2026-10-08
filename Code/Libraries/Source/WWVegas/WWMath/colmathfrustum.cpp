// cl: /Ireference/shims/bfmerendobj /G7 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWMath/colmathfrustum.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWMath                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwmath/colmathfrustum.cpp                    $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 3/29/00 5:40p                                               $*
 *                                                                                             *
 *                    $Revision:: 7                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#define COLMATHPLANE_H // use the source-local inline expressions below
#include "colmath.h"
#include "colmathinlines.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "frustum.h"
#include "wwdebug.h"

// BFME1@34f59164f6 supplies the plane-overlap expressions below.
// Keep the already-inlined math local: only the existing native providers
// own out-of-line get_far_extent (0x0007B5C8) and Plane/Point (0x0007B638).
// ?bfmeNativeFarExtentInline absent-from-retail
static __forceinline void bfmeNativeFarExtentInline(const Vector3 & normal,const Vector3 & extent,Vector3 * posfarpt)
{
	if (WWMath::Fast_Is_Float_Positive(normal.X)) {
		posfarpt->X = extent.X;
	} else {
		posfarpt->X = -extent.X;
	}

	if (WWMath::Fast_Is_Float_Positive(normal.Y)) {
		posfarpt->Y = extent.Y;
	} else {
		posfarpt->Y = -extent.Y;
	}

	if (WWMath::Fast_Is_Float_Positive(normal.Z)) {
		posfarpt->Z = extent.Z;
	} else {
		posfarpt->Z = -extent.Z;
	}
}
// ?bfmeNativePlanePointInline absent-from-retail
static __forceinline CollisionMath::OverlapType
bfmeNativePlanePointInline(const PlaneClass & plane,const Vector3 & point,const float & epsilon)
{
	float delta = Vector3::Dot_Product(point,plane.N) - plane.D;
	if (delta > epsilon) {
		return CollisionMath::POS;
	}
	if (delta < -epsilon) {
		return CollisionMath::NEG;
	}
	return CollisionMath::ON;
}


// ?bfmeNativePlaneBoxInline absent-from-retail
static __forceinline CollisionMath::OverlapType
bfmeNativePlaneBoxInline(const PlaneClass & plane,const AABoxClass & box,const float & epsilon)
{
	// First, we determine the the near and far points of the box in the
	// direction of the plane normal
	Vector3 posfarpt;
	Vector3 negfarpt;

	bfmeNativeFarExtentInline(plane.N,box.Extent,&posfarpt);

	negfarpt = -posfarpt;
	posfarpt += box.Center;
	negfarpt += box.Center;
	if (bfmeNativePlanePointInline(plane,negfarpt,epsilon) == CollisionMath::POS) {
		return CollisionMath::POS;
	}
	if (bfmeNativePlanePointInline(plane,posfarpt,epsilon) == CollisionMath::NEG) {
		return CollisionMath::NEG;
	}
	return CollisionMath::BOTH;
}

// TODO: Most of these overlap functions actually do not catch all cases of when
// the primitive is outside of the frustum...


// Frustum functions
CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const Vector3 & point)
{
	int mask = 0;
	
	for (int i = 0; i < 6; i++) {
		int result = bfmeNativePlanePointInline(frustum.Planes[i],point,COINCIDENCE_EPSILON);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const TriClass & tri)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],tri);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const SphereClass & sphere)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],sphere);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const AABoxClass & box)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = bfmeNativePlaneBoxInline(frustum.Planes[i],box,COINCIDENCE_EPSILON);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}


CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const OBBoxClass & box)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],box);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}


CollisionMath::OverlapType	
CollisionMath::Overlap_Test(const FrustumClass & frustum,const OBBoxClass & box,int & planes_passed)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {

		int plane_bit = (1<<i);

		// only check this plane if we have to	
		if ((planes_passed & plane_bit) == 0) {
			
			int result = CollisionMath::Overlap_Test(frustum.Planes[i],box);
			if (result == OUTSIDE) {
				return OUTSIDE;
			} else if (result == INSIDE) {
				planes_passed |= plane_bit;
			}
			mask |= result;

		} else {
		
			mask |= INSIDE;

		}
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

