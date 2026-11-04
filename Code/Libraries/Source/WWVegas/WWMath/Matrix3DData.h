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
// Zero Hour's. Members follow Zero Hour's matrix3d.h unless their comment says
// otherwise, each proved byte-exact in every adopting unit that uses it; inline
// bodies are forced (Zero Hour's WWINLINE) so call sites inline them as
// retail's do. Members that need Vector3 or sinf/cosf stay with the units:
// this header includes only Vector4Data.h. Row is public here (Zero Hour:
// protected); a data member's access changes no symbol.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// WWMath's matrix3d.h guard: a unit that includes the full WWMath header keeps it
// (same layout), and this storage view then adds nothing.
#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector4Data.h"

class Matrix3D
{
public:
	__forceinline Matrix3D( void ) { }

	// Retail also keeps an out-of-line copy (0x0004C91A).
	__forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }

	// Retail also keeps out-of-line copies (0x0006645C, 0x0006336E); retail's call
	// sites inline both, which the implicit members are not at /O1.
	__forceinline Matrix3D(const Matrix3D & m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}

	__forceinline Matrix3D & operator = (const Matrix3D & m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}

	// Inlined through Vector4::Set.
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	// Retail also keeps an out-of-line copy of the non-const one (0x0007DE8E).
	__forceinline Vector4 & operator [] (int i) { return Row[i]; }
	__forceinline const Vector4 & operator [] (int i) const { return Row[i]; }

	__forceinline float Get_X_Translation(void) const { return Row[0][3]; }
	__forceinline float Get_Y_Translation(void) const { return Row[1][3]; }
	__forceinline float Get_Z_Translation(void) const { return Row[2][3]; }

	// Inline in Zero Hour; the adopting unit calls retail's out-of-line copy (0x00481FAF).
	void Set_Z_Translation(float z);

	// Out of line in Zero Hour and retail (WWMath matrix3d.cpp, 0x00712020).
	float Get_Z_Rotation(void) const;

	// Out of line in Zero Hour and retail (0x00713290, 0x00712A30).
	void Get_Inverse(Matrix3D & set_inverse) const;
	void Get_Orthogonal_Inverse(Matrix3D & set_inverse) const;

	// Uniform scale of the three axes; retail also keeps an out-of-line copy (0x00074643).
	__forceinline void Scale(float scale)
	{
		Row[0][0] *= scale;
		Row[1][0] *= scale;
		Row[2][0] *= scale;
		Row[0][1] *= scale;
		Row[1][1] *= scale;
		Row[2][1] *= scale;
		Row[0][2] *= scale;
		Row[1][2] *= scale;
		Row[2][2] *= scale;
	}

	// Out of line in Zero Hour and retail (0x00713AB0).
	static void Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result);

	// Defined in WWMath matrix3d.cpp (data row 0x00DDD9D0); not in Zero Hour's header.
	static const Matrix3D Identity;

	Vector4 Row[3];
};

#endif // MATRIX3D_H
