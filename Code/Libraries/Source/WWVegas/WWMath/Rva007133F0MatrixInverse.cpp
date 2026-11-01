// cl: /O2 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x007133F0 (332B, ret 4), between Matrix3D::Get_Inverse (0x00713290,
// matrix3d_inverse.cpp) and Matrix3D::Multiply (0x00713540): a Matrix3D
// inverse taken through the 4x4 Gauss-Jordan Matrix4::Inverse. Donor:
// Open-BFME-1 09f941a50d game/Libraries/Source/WWVegas/WWMath/Rva008D7C20.cpp
// (BFME1 0x008D7C20, before its Multiply), same body. Target evidence: the
// Matrix4(const Matrix3D &) widening (three rows plus 0,0,0,1) inlined, then a
// thiscall with an explicit output pointer to 0x00715EB0, then the first three
// result rows copied element by element into the out-parameter. Unlike BFME1,
// which inlines the header's __forceinline Gauss-Jordan Inverse here, BFME2
// calls it out of line: the 2071-byte body at 0x00715EB0 inside matrix4.cpp's
// retail range is that Inverse (pivot search with WWMath::Fabs masking, row
// swaps, reciprocal row scale, elimination), so this TU declares Inverse in a
// TU-scoped Matrix4 view (as Rva00715E90Cluster.cpp does) instead of taking
// the header's inline definition. Class and method names are address-derived;
// the original name is unproven in both games.

#include "Vector4Data.h"
static __forceinline void copyVector4(Vector4 &row, const Vector4 &other)
{ row.X=other.X; row.Y=other.Y; row.Z=other.Z; row.W=other.W; }

class Matrix3D
{
public:
	Vector4 Row[3];
};

class Matrix4
{
public:
	__forceinline Matrix4() {}
	__declspec(dllimport) __forceinline void Init(const Matrix3D &m)
	{
		copyVector4(Row[0], m.Row[0]); copyVector4(Row[1], m.Row[1]); copyVector4(Row[2], m.Row[2]); Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	void Inverse(Matrix4 *out) const;
	Vector4 Row[4];
};

class Rva007133F0MatrixInverse : public Matrix3D
{
public:
	void inverse(Matrix3D &out) const;
};

void Rva007133F0MatrixInverse::inverse(Matrix3D &out) const
{
	Matrix4 mat;
	mat.Init(*this);
	Matrix4 result;
	mat.Inverse(&result);
	out.Row[0].X = result.Row[0].X;
	out.Row[0].Y = result.Row[0].Y;
	out.Row[0].Z = result.Row[0].Z;
	out.Row[0].W = result.Row[0].W;
	out.Row[1].X = result.Row[1].X;
	out.Row[1].Y = result.Row[1].Y;
	out.Row[1].Z = result.Row[1].Z;
	out.Row[1].W = result.Row[1].W;
	out.Row[2].X = result.Row[2].X;
	out.Row[2].Y = result.Row[2].Y;
	out.Row[2].Z = result.Row[2].Z;
	out.Row[2].W = result.Row[2].W;
}
