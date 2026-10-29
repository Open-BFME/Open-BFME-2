// FILE: Matrix3DData.h ///////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Matrix3D storage (WWMath), in BFME 1's WWMath directory
//         (`dest`); not named matrix3d.h, which WWMath headers include by that name.
//
// Facts: class_contracts/Matrix3D.json over 149 views decides sizeof 48 (Zero
// Hour, 138 views) and class-key class (bytes); retail stores three rows of
// four floats (Thing::Thing builds the three rows of its +0x08 transform
// through the vector constructor iterator 0x00001423). Zero Hour's matrix3d.h
// holds them as `Vector4 Row[3]`; the views split between that spelling and
// float arrays, so the contract queues the leaf fields and this header takes
// Zero Hour's. Only the storage and the empty default constructor are
// declared: the inline methods' codegen differs between units (the link
// shims under reference/shims/*matrix3d* exist for that), so they stay with
// the units that spell them until each is proved. Row is public here (Zero
// Hour: protected); a data member's access changes no symbol.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_MATRIX3D_H_
#define __BFME2_MATRIX3D_H_

#include "Vector4Data.h"

class Matrix3D
{
public:
	Matrix3D( void ) { }

	Vector4 Row[3];
};

#endif // __BFME2_MATRIX3D_H_
