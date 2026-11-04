// FILE: Matrix4Data.h ///////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Matrix4 storage (WWMath), in BFME 1's WWMath directory; not named
//         matrix4.h, which WWMath headers include by that name.
//
// Target facts (addresses are RVAs):
//  - No virtual functions, no base: sizeof 64, four rows of four floats. The out-of-line
//    default constructor 0x0007671F builds Row[4] through the vector constructor iterator
//    0x00001423 (count 4, size 0x10, element constructor 0x0047A6A9). Retail calls it from
//    /O1 code (0x000770BF, 0x00096881, 0x000A6EC6 and more) and inlines it elsewhere
//    (0x0014AB79); the ledger names its row ??0Rva0007671F@@QAE@XZ, which units reach
//    through their own class of that name.
//  - The ledger mangles the class as Matrix4 with class key class: DX8Wrapper's
//    ProjectionMatrix (0x009EDC30) and DeviceProjectionMatrix (0x009EDBF0) data rows,
//    Set_Transform (0x000A68A7), Get_Transform (0x000768FE) and 37 function rows in all. Only
//    matrix4x4.cpp's three rows (0x0006905B, 0x00181FC0, 0x00183B00) spell Matrix4x4,
//    from Zero Hour's header; units spell both names, hence the typedef.
//  - Out-of-line copies with no retail caller (call sites inline them): Matrix4(bool)
//    0x000A682E, Matrix4(const Matrix3D &) 0x0006A2CD, Matrix4(Vector4 x4) 0x0006A34E,
//    Transpose 0x0006A3D1, Make_Identity 0x00076735, Init(const Matrix3D &) 0x00068FEF.
//  - Called out of line: Multiply 0x00715550 (called at
//    0x0014EFFE), 0x007158F0 (at 0x0007C231) and 0x00715BC0 (at 0x00134AA1); Get_Inverse
//    0x00715E90 (at 0x0014AFCD); Inverse 0x00715EB0 (at 0x007134A4); operator==
//    0x007166D0 (at 0x007167CA); operator!= 0x007167C0 (at 0x0012D6E2).
// Donor (Zero Hour matrix4.h) facts: member names and the inline bodies, spelled as the
// units' byte-verified views spell them. Get_Inverse and Inverse(Matrix4 *) are BFME2's
// own signatures. Row is public here (Zero Hour: protected); a data member's access
// changes no symbol. Members that need Vector3 stay with the units.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// WWMath's matrix4.h guard: a unit that includes the full WWMath header keeps it
// (same layout), and this storage view then adds nothing.
#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector4Data.h"
#include "Matrix3DData.h"

class Matrix4
{
public:
	__forceinline Matrix4(void) {}

	__forceinline Matrix4(const Matrix4 & m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}

	__forceinline explicit Matrix4(bool identity) { if (identity) Make_Identity(); }

	__forceinline explicit Matrix4(const Matrix3D & m) { Init(m); }

	__forceinline explicit Matrix4(const Vector4 & r0, const Vector4 & r1, const Vector4 & r2, const Vector4 & r3)
	{
		Init(r0, r1, r2, r3);
	}

	__forceinline explicit Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
	{
		Row[0].Set(m11, m12, m13, m14);
		Row[1].Set(m21, m22, m23, m24);
		Row[2].Set(m31, m32, m33, m34);
		Row[3].Set(m41, m42, m43, m44);
	}

	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	__forceinline void Init(const Matrix3D & m)
	{
		Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	__forceinline void Init(const Vector4 & r0, const Vector4 & r1, const Vector4 & r2, const Vector4 & r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}

	__forceinline Vector4 & operator [] (int i) { return Row[i]; }
	__forceinline const Vector4 & operator [] (int i) const { return Row[i]; }

	__forceinline Matrix4 Transpose(void) const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}

	void Get_Inverse(Matrix4 & set_inverse) const;
	void Inverse(Matrix4 * set_inverse) const;

	__forceinline Matrix4 & operator = (const Matrix4 & m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this;
	}

	friend int operator == (const Matrix4 & a, const Matrix4 & b);
	friend int operator != (const Matrix4 & a, const Matrix4 & b);

	static void Multiply(const Matrix4 & A, const Matrix4 & B, Matrix4 * set_result);
	static void Multiply(const Matrix3D & A, const Matrix4 & B, Matrix4 * set_result);
	static void Multiply(const Matrix4 & A, const Matrix3D & B, Matrix4 * set_result);

	Vector4 Row[4];
};

typedef Matrix4 Matrix4x4;

#endif // MATRIX4_H
