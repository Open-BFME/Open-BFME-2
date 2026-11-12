// cl: /Ireference/shims/bfmefrustum /Ireference/shims/bfmerendobj /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
/*
**	Command & Conquer Generals(tm)
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

// Vector3's inlines compile with the unit's own settings, as retail's copies do.
#include "vector3.h"
#include "../../../../../reference/shims/bfmefrustum/plane.h"
inline void PlaneClass::Set(const Vector3 & point1, const Vector3 & point2, const Vector3 & point3) 
{
#ifdef ALLOW_TEMPORARIES
	N = Vector3::Cross_Product((point2 - point1), (point3 - point1));
#else
	Vector3::Cross_Product((point2 - point1), (point3 - point1), &N);
#endif
	if (N != Vector3(0.0f, 0.0f, 0.0f)) {
		// Points are not colinear. Normalize N and calculate D.
		N.Normalize();
		D = Vector3::Dot_Product(N, point1);
	} else {
		// They are colinear - return default plane (constructors can't fail).
		N = Vector3(0.0f, 0.0f, 1.0f);
		D = 0.0f;
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
static void (PlaneClass::*const _bfmeInlineAnchor0_Set)(const Vector3 & point1, const Vector3 & point2, const Vector3 & point3) = &PlaneClass::Set;
