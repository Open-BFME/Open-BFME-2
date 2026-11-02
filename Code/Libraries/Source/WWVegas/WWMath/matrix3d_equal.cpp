// cl: /DNDEBUG /MD /EHsc
//
// Matrix3D inequality: twelve float compares with early-out, the == core
// inlined into !=. Donor: the BFME1 reconstruction of the same upstream
// WWMath member (their retail 0x006F6E00, 83 bytes).

#include "Vector4Data.h"


#include "Matrix3DData.h"


__forceinline bool operator==(const Matrix3D &a, const Matrix3D &b)
{
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 4; ++column) {
			if ((&a.Row[row].X)[column] != (&b.Row[row].X)[column]) {
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const Matrix3D &a, const Matrix3D &b)
{
	return !(a == b);
}
