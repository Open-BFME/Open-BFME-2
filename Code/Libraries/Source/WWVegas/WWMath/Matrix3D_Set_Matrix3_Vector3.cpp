// cl: /O2 /arch:SSE2 /MD
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

class Vector4
{
public:
	void Set(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3
{
public:
	const Vector3 &operator[](int i) const { return Row[i]; }

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
	Row[0].Set(rot[0][0], rot[0][1], rot[0][2], pos[0]);
	Row[1].Set(rot[1][0], rot[1][1], rot[1][2], pos[1]);
	Row[2].Set(rot[2][0], rot[2][1], rot[2][2], pos[2]);
}
