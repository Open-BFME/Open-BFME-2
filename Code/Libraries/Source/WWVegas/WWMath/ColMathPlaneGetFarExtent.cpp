// ?get_far_extent@@YAXABVVector3@@0PAV1@@Z
// cl: /O2 /G7 /MD /arch:SSE /Oy- /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
//
// Shared Vector3 view: bfme2_vector3; donor34f59164f6 supplies dependencies.
// The real out-of-line provider needs no artificial emission wrapper.
// get_far_extent, retail 0x0007B5C8, 112 bytes: the colmathplane.h helper that
// picks the extent corner farthest along a plane normal, emitted out of line in
// BFME2 and called from the AABTree culling code.
//
// Retail copies the positive X extent through the x87 stack (fld/fstp) while Y
// and Z are plain dword moves; carrying X through a double temporary is what
// reproduces that, with the negated arms staying SSE.

#include "vector3.h"

__forceinline bool Fast_Is_Float_Positive(const float &val)
{
	return !((*reinterpret_cast<const int *>(&val) & 0x80000000) != 0);
}

// inline as in colmathplane.h: the AABTree/mesh culling units emit their own select-any copies.
inline void __cdecl get_far_extent(const Vector3 &normal, const Vector3 &extent, Vector3 *posfarpt)
{
	if (Fast_Is_Float_Positive(normal.X))
	{
		double x = extent.X;
		posfarpt->X = x;
	}
	else
		posfarpt->X = -extent.X;

	if (Fast_Is_Float_Positive(normal.Y))
		posfarpt->Y = extent.Y;
	else
		posfarpt->Y = -extent.Y;

	if (Fast_Is_Float_Positive(normal.Z))
		posfarpt->Z = extent.Z;
	else
		posfarpt->Z = -extent.Z;
}

// Header inline that other units emit as select-any copies, which a plain
// definition here collided with. The anchor keeps this unit's copy for its
// row; it is not retail data.
void (__cdecl *_bfmeInlineAnchor_ColMathPlaneGetFarExtent)(const Vector3 &, const Vector3 &, Vector3 *) = &get_far_extent;
