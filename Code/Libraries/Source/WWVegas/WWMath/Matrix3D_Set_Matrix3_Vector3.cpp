// cl: /MD
//
// Matrix3D::Set(const Matrix3 &, const Vector3 &), retail 0x00711E70, 118 bytes.
// Dedicated TU so matrix3d.cpp's other matched bodies stay untouched.

class Vector3
{
public:
	float operator[](int i) const { return (&X)[i]; }

	float X;
	float Y;
	float Z;
};

#include "Vector4Data.h"

class Matrix3
{
public:
	__declspec(dllimport) __forceinline const Vector3 &operator[](int i) const { return Row[i]; }

	Vector3 Row[3];
};

class Matrix3D
{
public:
	void Set(const Matrix3 &rot, const Vector3 &pos);

	Vector4 Row[3];
};

void Matrix3D::Set(const Matrix3 &rot, const Vector3 &pos)
{
	// Capture a row's four input values before writing, as the native inline Set does.
	{
		const float w = pos[0];
		const float z = rot[0][2];
		const float y = rot[0][1];
		const float x = rot[0][0];
		Row[0].X = x;
		Row[0].Y = y;
		Row[0].Z = z;
		Row[0].W = w;
	}
	{
		const float w = pos[1];
		const float z = rot[1][2];
		const float y = rot[1][1];
		const float x = rot[1][0];
		Row[1].X = x;
		Row[1].Y = y;
		Row[1].Z = z;
		Row[1].W = w;
	}
	{
		const float w = pos[2];
		const float z = rot[2][2];
		const float y = rot[2][1];
		const float x = rot[2][0];
		Row[2].X = x;
		Row[2].Y = y;
		Row[2].Z = z;
		Row[2].W = w;
	}
}
