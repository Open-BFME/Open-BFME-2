// cl: /Ireference/shims/bfmerendobj /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// Matrix3D transform class, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/matrix3d.cpp). Only the functions located in
// the binary are defined here; Multiply and Lerp are omitted because the retail
// build's inlining/codegen for them drifted from this source (see report).

// Preserve native inlined CRT adapters without competing external copies.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include "../../../../../reference/shims/bfme_matrix3d_link/vector4.h"
#include "../../../../../reference/shims/bfme_matrix3d_link/matrix3d.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "matrix3d.h"

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "vector3.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"
#include "D3dx8math.h"

// Keep the compiler-generated assignment member in this scalar TU after
// Multiply moved to its dedicated SSE TU.
typedef Matrix3D & (Matrix3D::*Matrix3DAssign)(const Matrix3D &);
Matrix3DAssign g_matrix3dAssign = &Matrix3D::operator=;

// some static matrices which are sometimes useful
const Matrix3D Matrix3D::Identity
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D Matrix3D::RotateX90
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0,
	0.0,	1.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateX180
(
	1.0,	0.0,	0.0,	0.0,
	0.0, -1.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0
);

const Matrix3D Matrix3D::RotateX270
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0,
	0.0, -1.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateY90
(
	0.0,	0.0,	1.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
  -1.0,	0.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateY180
(
  -1.0,	0.0,	0.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0
);

const Matrix3D Matrix3D::RotateY270
(
	0.0,	0.0, -1.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	1.0,	0.0,	0.0,	0.0
);

const Matrix3D	Matrix3D::RotateZ90
(
	0.0, -1.0,	0.0,	0.0,
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D Matrix3D::RotateZ180
(
  -1.0,	0.0,	0.0,	0.0,
	0.0, -1.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D	Matrix3D::RotateZ270
(
	0.0,	1.0,	0.0,	0.0,
  -1.0,	0.0,	0.0,	0.0,
 	0.0,	0.0,	1.0,	0.0
);


inline void Matrix3D::Set(const Matrix3 & rot,const Vector3 & pos)
{
	Row[0].Set( rot[0][0], rot[0][1], rot[0][2], pos[0]);
	Row[1].Set( rot[1][0], rot[1][1], rot[1][2], pos[1]);
	Row[2].Set( rot[2][0], rot[2][1], rot[2][2], pos[2]);
}


void Matrix3D::Set_Rotation(const Matrix3 & matrix3)
{
	Row[0][0] = matrix3[0][0];
	Row[0][1] = matrix3[0][1];
	Row[0][2] = matrix3[0][2];

	Row[1][0] = matrix3[1][0];
	Row[1][1] = matrix3[1][1];
	Row[1][2] = matrix3[1][2];

	Row[2][0] = matrix3[2][0];
	Row[2][1] = matrix3[2][1];
	Row[2][2] = matrix3[2][2];
}


float Matrix3D::Get_X_Rotation(void) const
{
	return (WWMath::Atan2(Row[2][1], Row[1][1]));
}


float Matrix3D::Get_Y_Rotation(void) const
{
	return (WWMath::Atan2(Row[0][2], Row[2][2]));
}


float Matrix3D::Get_Z_Rotation(void) const
{
	return (WWMath::Atan2(Row[1][0], Row[0][0]));
}




inline Vector3 Matrix3D::Inverse_Rotate_Vector(const Vector3 &vect) const
{
	return Vector3(
		(Row[0][0]*vect[0] + Row[1][0]*vect[1] + Row[2][0]*vect[2]),
		(Row[0][1]*vect[0] + Row[1][1]*vect[1] + Row[2][1]*vect[2]),
		(Row[0][2]*vect[0] + Row[1][2]*vect[1] + Row[2][2]*vect[2])
	);
}


// Create a matrix given a position and a direction (x axis will point in direction)
// Make sure you pass in UNITIZED direction!!!









// Emission anchor (LINK-DUP): the 10 duplicate Matrix3D bodies above are now
// inline, so the compiler discards them (nothing in this TU calls them) and with
// them their only intra-TU users of four helpers this TU owns rows for
// (Vector3::Dot_Product, Vector4(float,float,float,float),
// Vector3::Length2). This anchor keeps those three emitting; its own bytes are unclaimed.
// The Vector3(float,float,float) copy this TU used to emit lost to retail's,
// so this TU no longer constructs one (retail's copy serves every caller).
// ?Matrix3DHelperAnchor present-unmatched
void Matrix3DHelperAnchor(Vector3 &a, Vector3 &b, Vector4 &vector4)
{
	float d = Vector3::Dot_Product(a, b);
	float l = a.Length2();
	vector4 = Vector4(d, l, 0.0f, 1.0f);
}
