// cl: /O2 /G7 /MD /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// Quaternion-plus-translation array transforms, retail 0x00168C40 (373B) and
// 0x00168DC0 (358B): the next two bodies after the Matrix3D array transforms
// at 0x00168980 and 0x00168AD0 (BFME1 Matrix3D_Rotate_Vector.cpp /
// Matrix3D_Transform_Vector.cpp), each between int3 runs and ending ret 12.
// BFME1 has no counterpart at the matching position.
//
// Target evidence: this holds a quaternion X,Y,Z,W at +0x0..+0xC and a
// translation at +0x10..+0x18. Both loop over 12-byte-stride input and output
// arrays (count tested before the loop, decremented at its foot); every
// output coordinate is the WWMath quat.h Rotate_Vector expansion in the
// negation-free spelling BFME2's out-of-line Quaternion::Rotate_Vector copies
// use (0x0015F6D0, QuaternionRotateVector.cpp). 0x00168C40 adds the
// translation to each coordinate before storing it, 0x00168DC0 does not.
// Neither body has a direct caller or a data reference, so the class and method
// names are address-derived; the layout is the quaternion+translation pivot
// transform BFME2 keeps in place of a Matrix3D (HLod pivots, +0x30/+0x40).

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body instead of the /O2 one, which loses at link time.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
#pragma auto_inline(off)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma auto_inline(on)
#pragma optimize("", on)

#include "vector3.h"

class Rva00168C40QuatTransform
{
public:
	void transform_vectors(const Vector3 *in, Vector3 *out, int count) const;
	void rotate_vectors(const Vector3 *in, Vector3 *out, int count) const;

private:
	void Transform_Vector(const Vector3 &vec, Vector3 *result) const
	{
		float x = Rotation.W*vec.X + (Rotation.Y*vec.Z - vec.Y*Rotation.Z);
		float y = Rotation.W*vec.Y - (Rotation.X*vec.Z - vec.X*Rotation.Z);
		float z = Rotation.W*vec.Z + (Rotation.X*vec.Y - vec.X*Rotation.Y);
		float w = -(Rotation.X*vec.X + Rotation.Y*vec.Y + Rotation.Z*vec.Z);

		result->X = Rotation.W*x - w*Rotation.X + (Rotation.Y*z - y*Rotation.Z) + Translation.X;
		result->Y = Rotation.W*y - w*Rotation.Y - (Rotation.X*z - x*Rotation.Z) + Translation.Y;
		result->Z = Rotation.W*z - w*Rotation.Z + (Rotation.X*y - Rotation.Y*x) + Translation.Z;
	}

	void Rotate_Vector(const Vector3 &vec, Vector3 *result) const
	{
		float x = Rotation.W*vec.X + (Rotation.Y*vec.Z - vec.Y*Rotation.Z);
		float y = Rotation.W*vec.Y - (Rotation.X*vec.Z - vec.X*Rotation.Z);
		float z = Rotation.W*vec.Z + (Rotation.X*vec.Y - vec.X*Rotation.Y);
		float w = -(Rotation.X*vec.X + Rotation.Y*vec.Y + Rotation.Z*vec.Z);

		result->X = Rotation.W*x - w*Rotation.X + (Rotation.Y*z - y*Rotation.Z);
		result->Y = Rotation.W*y - w*Rotation.Y - (Rotation.X*z - x*Rotation.Z);
		result->Z = Rotation.W*z - w*Rotation.Z + (Rotation.X*y - Rotation.Y*x);
	}

	// Only the target-proven rotation components are used here. Including
	// quat.h also emits an unused, nonretail array-construction helper through
	// its matrix headers; this storage view needs no Quaternion operations.
	struct { float X, Y, Z, W; } Rotation;
	Vector3 Translation;
};

void Rva00168C40QuatTransform::transform_vectors(const Vector3 *in, Vector3 *out, int count) const
{
	while (count--)
	{
		Transform_Vector(*in, out);
		++in;
		++out;
	}
}

void Rva00168C40QuatTransform::rotate_vectors(const Vector3 *in, Vector3 *out, int count) const
{
	while (count--)
	{
		Rotate_Vector(*in, out);
		++in;
		++out;
	}
}
