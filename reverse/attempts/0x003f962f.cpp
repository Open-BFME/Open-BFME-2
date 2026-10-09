// ?rva003F962F@LivingWorldEyeTower@@AAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// ?rva003F962F@LivingWorldEyeTower@@AAEXXZ retail 0x003F962F..0x003F99DC 941B.
// Aims the two eye-tower render hosts from the eye position (+0x24) at the
// target position (+0x30). Pitch is atan2(-dz and the horizontal length)
// applied with an inlined Matrix3::Rotate_Y on an identity Matrix3; yaw is
// atan2(dx and -dy) minus pi/2 turned into an inlined
// Create_Z_Rotation_Matrix3; Matrix3::Multiply(rz and pitch) is handed to the
// host at +0x18. The second host (+0x20) gets pitch atan2(dz and length)
// on Matrix3::Identity and the yaw turned a further pi.
// Sole caller processFrame 0x003F99DC. The two host calls go to 0x003F935A
// with ECX=this reloaded before each push sequence so that helper is a
// LivingWorldEyeTower member with an unused receiver (its only callers are
// the two calls here).
// Callees: Coord3D::length 0x00003571; _atan2f 0x000422CD; sin/cos import
// thunks 0x00629216/0x0062920A; Matrix3::Multiply 0x00716D40.
// Data: Matrix3::Identity 0x009DDBF8 (nine floats 1 0 0 0 1 0 0 0 1).
// NEAR: full length and frame match; only the first inlined Rotate_Y
// picks addss xmm1,xmm0 where retail has addss xmm0,xmm1 (register tie)
// for its three row[i][2] sums. The second Rotate_Y matches.
// The helper call needs 0x003F935A renamed to a thiscall member
// (?rva003F935A@LivingWorldEyeTower@@AAEXPAVU4Target0060C2C0@@PAX@Z).
#include "Coord3D.h"

#include <math.h>
extern "C" float __cdecl atan2f(float y, float x);

class Rva003F962FVector3
{
public:
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline const float &operator[](int i) const { return (&X)[i]; }
	__forceinline Rva003F962FVector3 &operator=(const Rva003F962FVector3 &v)
	{
		X = v.X; Y = v.Y; Z = v.Z;
		return *this;
	}
	__forceinline void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X, Y, Z;
};

class Matrix3
{
public:
	__forceinline Matrix3() {}
	__forceinline Matrix3(const Matrix3 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2];
	}
	__forceinline explicit Matrix3(bool identity)
	{
		if (identity)
		{
			Row[0].Set(1.0, 0.0, 0.0);
			Row[1].Set(0.0, 1.0, 0.0);
			Row[2].Set(0.0, 0.0, 1.0);
		}
	}
	__forceinline Rva003F962FVector3 &operator[](int i) { return Row[i]; }
	__forceinline const Rva003F962FVector3 &operator[](int i) const { return Row[i]; }
	__forceinline Matrix3 &operator=(const Matrix3 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2];
		return *this;
	}
	__forceinline void Rotate_Y(float theta)
	{
		Rotate_Y(sinf(theta), cosf(theta));
	}
	__forceinline void Rotate_Y(float s, float c)
	{
		float tmp1, tmp2;

		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	static void Multiply(const Matrix3 &a, const Matrix3 &b, Matrix3 *res);
	static const Matrix3 Identity;
protected:
	Rva003F962FVector3 Row[3];
};

__forceinline Matrix3 Create_Z_Rotation_Matrix3(float s, float c)
{
	Matrix3 mat;

	mat[0][0] = c;
	mat[0][1] = -s;
	mat[0][2] = 0.0f;

	mat[1][0] = s;
	mat[1][1] = c;
	mat[1][2] = 0.0f;

	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = 1.0f;

	return mat;
}

__forceinline Matrix3 Create_Z_Rotation_Matrix3(float rad)
{
	return Create_Z_Rotation_Matrix3(sinf(rad), cosf(rad));
}

class U4Target0060C2C0;

__forceinline void rva003F962FCopy(Coord3D &d, const Coord3D &s)
{
	d.x = s.x;
	d.y = s.y;
	d.z = s.z;
}

class LivingWorldEyeTower
{
private:
	void rva003F962F();
	void rva003F935A(U4Target0060C2C0 *target, void *payload);
	char m_pad00[0x18];
	U4Target0060C2C0 *m_firstHost;
	char m_pad1C[4];
	U4Target0060C2C0 *m_secondHost;
	Coord3D m_eye;
	Coord3D m_target;
};

void LivingWorldEyeTower::rva003F962F()
{
	float z;
	float len;
	{
		Coord3D dir;
		rva003F962FCopy(dir, m_eye);
		dir.x -= m_target.x;
		dir.y -= m_target.y;
		dir.z -= m_target.z;
		z = dir.z;
		dir.z = 0.0f;
		len = dir.length();
	}
	float pitch = atan2f(-z, len);
	Matrix3 m(true);
	m.Rotate_Y(pitch);
	float yaw;
	{
		Coord3D delta = m_eye;
		delta.x -= m_target.x;
		delta.y -= m_target.y;
		delta.z -= m_target.z;
		yaw = atan2f(delta.x, -delta.y);
	}
	yaw -= 1.5707964f;
	Matrix3 rz = Create_Z_Rotation_Matrix3(yaw);
	Matrix3 res;
	Matrix3::Multiply(rz, m, &res);
	rva003F935A(m_firstHost, &res);
	pitch = atan2f(z, len);
	m = Matrix3::Identity;
	m.Rotate_Y(pitch);
	yaw -= 3.1415927f;
	rz = Create_Z_Rotation_Matrix3(yaw);
	Matrix3::Multiply(rz, m, &res);
	rva003F935A(m_secondHost, &res);
}
