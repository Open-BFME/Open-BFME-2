// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?getCurrentBonePositions@W3DModelDraw@@UBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z
// retail 0x000B52CD..0x000B5746 (1145 bytes) thiscall RET 0x14.
//
// Zero Hour / BFME 1 W3DModelDraw::getCurrentBonePositions (Open-BFME-1's
// matched W3DModelDraw.cpp body, BFME's static 64-matrix scratch with its own
// guard; in BFME 2 the inverse is not rescaled by the drawable). Target
// facts: slot 4 of the draw-interface vtable 0x007CBB78 (absolute references
// 0x007CBB88 0x007CBF08 0x007CC598), so `this` is the interface subobject at
// +0x0C and m_renderObject reads at +0x44 (W3DModelDraw +0x50); the static
// array 0x00DEA310 (guard 0x00DEAF10) is built per matrix through the rowed
// eh vector constructor iterator 0x00001423 over the folded empty Vector4
// constructor; the render object's transform at +0x18 behind slot +0x50
// (Validate_Transform), rowed Matrix3D::Get_Orthogonal_Inverse 0x00312A30,
// bone index / transform slots +0xC8 / +0xCC (the latter returns a Matrix3D
// by value), _strcpy and the "%s%02d" sprintf; preMul and the copy shapes
// follow WWMath (float copy constructor, row-wise assignment).
#include <string.h>
#include <stdio.h>
#include "Coord3D.h"

typedef int Int;
typedef float Real;

class Vector4
{
public:
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	Real X, Y, Z, W;
};

class Vector3
{
public:
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X, Y, Z;
};

static __forceinline Real submul(const Vector4 &row, Real tmp1, Real tmp2, Real tmp3)
{
	return row.X * tmp1 + row.Y * tmp2 + row.Z * tmp3;
}

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0].X = m.Row[0].X; Row[0].Y = m.Row[0].Y; Row[0].Z = m.Row[0].Z; Row[0].W = m.Row[0].W;
		Row[1].X = m.Row[1].X; Row[1].Y = m.Row[1].Y; Row[1].Z = m.Row[1].Z; Row[1].W = m.Row[1].W;
		Row[2].X = m.Row[2].X; Row[2].Y = m.Row[2].Y; Row[2].Z = m.Row[2].Z; Row[2].W = m.Row[2].W;
	}
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}

	void Get_Orthogonal_Inverse(Matrix3D &set_inverse) const;

	// does "this = A * B"
	__forceinline void mul(const Matrix3D &A, const Matrix3D &B)
	{
		Real tmp1, tmp2, tmp3;

		tmp1 = B.Row[0].X;
		tmp2 = B.Row[1].X;
		tmp3 = B.Row[2].X;

		this->Row[0].X = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].X = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].X = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].Y;
		tmp2 = B.Row[1].Y;
		tmp3 = B.Row[2].Y;

		this->Row[0].Y = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].Y = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].Y = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].Z;
		tmp2 = B.Row[1].Z;
		tmp3 = B.Row[2].Z;

		this->Row[0].Z = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].Z = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].Z = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].W;
		tmp2 = B.Row[1].W;
		tmp3 = B.Row[2].W;

		this->Row[0].W = submul(A.Row[0], tmp1, tmp2, tmp3) + A.Row[0].W;
		this->Row[1].W = submul(A.Row[1], tmp1, tmp2, tmp3) + A.Row[1].W;
		this->Row[2].W = submul(A.Row[2], tmp1, tmp2, tmp3) + A.Row[2].W;
	}

	// does "this = that * this"
	__forceinline void preMul(const Matrix3D &that)
	{
		this->mul(that, *this);
	}

	Vector3 Get_Translation() const { return Vector3(Row[0].W, Row[1].W, Row[2].W); }

	Vector4 Row[3];
};

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass
{
public:
	RENDEROBJ_SLOT(00) RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03)
	RENDEROBJ_SLOT(04) RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07)
	RENDEROBJ_SLOT(08) RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11)
	RENDEROBJ_SLOT(12) RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15)
	RENDEROBJ_SLOT(16) RENDEROBJ_SLOT(17) RENDEROBJ_SLOT(18) RENDEROBJ_SLOT(19)
	virtual void Validate_Transform() const;							// +0x50
	RENDEROBJ_SLOT(21) RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23)
	RENDEROBJ_SLOT(24) RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27)
	RENDEROBJ_SLOT(28) RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31)
	RENDEROBJ_SLOT(32) RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35)
	RENDEROBJ_SLOT(36) RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39)
	RENDEROBJ_SLOT(40) RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43)
	RENDEROBJ_SLOT(44) RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47)
	RENDEROBJ_SLOT(48) RENDEROBJ_SLOT(49)
	virtual int Get_Bone_Index(const char *bonename);					// +0xC8
	virtual Matrix3D Get_Bone_Transform(int boneindex);					// +0xCC

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return Transform;
	}

private:
	char m_pad004[0x18 - 0x04];
	Matrix3D Transform;													// +0x18
};

class W3DModelDrawBase
{
public:
	virtual void base00();

protected:
	void *m_moduleData;					// +0x04
	void *m_drawable;					// +0x08
};

class W3DModelDrawInterface
{
public:
	virtual void i00();
	virtual void i01();
	virtual void i02();
	virtual void i03();
	virtual Int getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;	// slot 4
};

class W3DModelDraw : public W3DModelDrawBase, public W3DModelDrawInterface
{
public:
	virtual Int getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;

private:
	char m_pad010[0x50 - 0x10];
	RenderObjClass *m_renderObject;		// +0x50
};

Int W3DModelDraw::getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const
{
	const int MAX_BONE_GET = 64;
	static Matrix3D tmpMtx[MAX_BONE_GET];

	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;

	if (transforms == 0)
		transforms = tmpMtx;

	if (!m_renderObject)
		return 0;

	Matrix3D originalTransform = m_renderObject->Get_Transform();
	Matrix3D inverse;
	originalTransform.Get_Orthogonal_Inverse(inverse);

	Int posCount = 0;
	Int endIndex = (startIndex == 0) ? 0 : 99;
	char buffer[256];
	Int i;
	for (i = startIndex; i <= endIndex; ++i)
	{
		if (i == 0)
			strcpy(buffer, boneNamePrefix);
		else
			sprintf(buffer, "%s%02d", boneNamePrefix, i);

		Int boneIndex = m_renderObject->Get_Bone_Index(buffer);
		if (boneIndex == 0)
			break;

		transforms[posCount] = m_renderObject->Get_Bone_Transform(boneIndex);
		transforms[posCount].preMul(inverse);

		++posCount;
		if (posCount >= maxBones)
			break;
	}

	if (positions && transforms)
	{
		for (i = 0; i < posCount; ++i)
		{
			Vector3 pos = transforms[i].Get_Translation();
			positions[i].x = pos.X;
			positions[i].y = pos.Y;
			positions[i].z = pos.Z;
		}
	}

	return posCount;
}
