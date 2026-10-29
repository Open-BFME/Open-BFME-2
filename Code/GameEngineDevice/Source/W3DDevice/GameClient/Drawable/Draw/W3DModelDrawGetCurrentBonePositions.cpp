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
	__declspec(dllimport) __forceinline Matrix3D(const Matrix3D &m)
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
	__forceinline void mul(const Matrix3D &matrix3D, const Matrix3D &B)
	{
		Real firstRowComponent, tmp2, tmp3;

		firstRowComponent = B.Row[0].X;
		tmp2 = B.Row[1].X;
		tmp3 = B.Row[2].X;

		this->Row[0].X = submul(matrix3D.Row[0], firstRowComponent, tmp2, tmp3);
		this->Row[1].X = submul(matrix3D.Row[1], firstRowComponent, tmp2, tmp3);
		this->Row[2].X = submul(matrix3D.Row[2], firstRowComponent, tmp2, tmp3);

		firstRowComponent = B.Row[0].Y;
		tmp2 = B.Row[1].Y;
		tmp3 = B.Row[2].Y;

		this->Row[0].Y = submul(matrix3D.Row[0], firstRowComponent, tmp2, tmp3);
		this->Row[1].Y = submul(matrix3D.Row[1], firstRowComponent, tmp2, tmp3);
		this->Row[2].Y = submul(matrix3D.Row[2], firstRowComponent, tmp2, tmp3);

		firstRowComponent = B.Row[0].Z;
		tmp2 = B.Row[1].Z;
		tmp3 = B.Row[2].Z;

		this->Row[0].Z = submul(matrix3D.Row[0], firstRowComponent, tmp2, tmp3);
		this->Row[1].Z = submul(matrix3D.Row[1], firstRowComponent, tmp2, tmp3);
		this->Row[2].Z = submul(matrix3D.Row[2], firstRowComponent, tmp2, tmp3);

		firstRowComponent = B.Row[0].W;
		tmp2 = B.Row[1].W;
		tmp3 = B.Row[2].W;

		this->Row[0].W = submul(matrix3D.Row[0], firstRowComponent, tmp2, tmp3) + matrix3D.Row[0].W;
		this->Row[1].W = submul(matrix3D.Row[1], firstRowComponent, tmp2, tmp3) + matrix3D.Row[1].W;
		this->Row[2].W = submul(matrix3D.Row[2], firstRowComponent, tmp2, tmp3) + matrix3D.Row[2].W;
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

// 0x000B51DA support. The 16-byte state copied by the rowed 0x00078AE3:
// bit fields 0..2 / 3..29 / 30 and words +4/+8/+C (bit 31 preserved); the
// rowed 0x000B4653 returns its looked-up entry. Original names unasserted.
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;
struct CreateAHeroManagerView { char m_pad000[0x184]; bool m_at184; };
class Rva000B4653 { public: void *rva000B4653(int index); };
class Rva00078AE3
{
public:
	unsigned int m_count : 3;
	unsigned int m_middle : 27;
	unsigned int m_flag30 : 1;
	unsigned int m_reserved31 : 1;
	unsigned int m_word4;
	unsigned int m_word8;
	unsigned int m_wordC;
	Rva00078AE3 &rva00078AE3(const Rva00078AE3 *other);
	__forceinline bool same(const Rva00078AE3 &other) const
	{
		if (m_count != other.m_count)
			return false;
		if (((Rva000B4653 *)this)->rva000B4653(0) != ((Rva000B4653 *)&other)->rva000B4653(0))
			return false;
		if (bool(m_flag30) != bool(other.m_flag30))
			return false;
		return true;
	}
	__forceinline Rva00078AE3(unsigned int key)
	{
		m_count = 0; m_middle = 0; m_flag30 = 0; m_word4 = 0; m_word8 = 0; m_wordC = 0;
		if (key & 0xFFFFFF) {
			m_count = 1; m_middle = 0; m_flag30 = 0; m_word4 = key; m_word8 = 0; m_wordC = 0;
		}
	}
};

// Primary vtable slots read by 0x000B51DA: +0xC4 (slot 49) and +0x100 (slot 64).
class W3DModelDrawBase
{
public:
	virtual void base00();
	virtual void base01();
	virtual void base02();
	virtual void base03();
	virtual void base04();
	virtual void base05();
	virtual void base06();
	virtual void base07();
	virtual void base08();
	virtual void base09();
	virtual void base10();
	virtual void base11();
	virtual void base12();
	virtual void base13();
	virtual void base14();
	virtual void base15();
	virtual void base16();
	virtual void base17();
	virtual void base18();
	virtual void base19();
	virtual void base20();
	virtual void base21();
	virtual void base22();
	virtual void base23();
	virtual void base24();
	virtual void base25();
	virtual void base26();
	virtual void base27();
	virtual void base28();
	virtual void base29();
	virtual void base30();
	virtual void base31();
	virtual void base32();
	virtual void base33();
	virtual void base34();
	virtual void base35();
	virtual void base36();
	virtual void base37();
	virtual void base38();
	virtual void base39();
	virtual void base40();
	virtual void base41();
	virtual void base42();
	virtual void base43();
	virtual void base44();
	virtual void base45();
	virtual void base46();
	virtual void base47();
	virtual void base48();
	virtual int base49();
	virtual void base50();
	virtual void base51();
	virtual void base52();
	virtual void base53();
	virtual void base54();
	virtual void base55();
	virtual void base56();
	virtual void base57();
	virtual void base58();
	virtual void base59();
	virtual void base60();
	virtual void base61();
	virtual void base62();
	virtual void base63();
	virtual void base64(unsigned int first, unsigned int zero, unsigned int last);

protected:
	struct ModuleDataView { char m_pad00[0x68]; bool m_at68; };
	struct ThingTemplateView { char m_pad00[0x11C]; unsigned int m_flags11C; };
	struct ObjectView { char m_pad00[4]; ThingTemplateView *m_template; };
	struct DrawableView { char m_pad00[0xFC]; ObjectView *m_object; };
	ModuleDataView *m_moduleData;		// +0x04
	DrawableView *m_drawable;			// +0x08
};

class W3DModelDrawInterface
{
public:
	virtual void i00();
	virtual void i01();
	virtual void i02();
	virtual void i03();
	virtual Int getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;	// slot 4

	virtual void i05();
	virtual void i06();
	virtual void i07();
	virtual void i08();
	virtual void i09();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual void i16();
	virtual void i17();
	virtual void i18();
	virtual void i19();
	virtual void i20();
	virtual void rva000B51DA(unsigned int key) = 0;	// slot 21 (0x007CBBCC)
};

class W3DModelDraw : public W3DModelDrawBase, public W3DModelDrawInterface
{
public:
	virtual Int getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;
	virtual void rva000B51DA(unsigned int key);

private:
	unsigned int m_at10;				// +0x10
	unsigned int m_at14;				// +0x14, first word handed to slot 64 (cleared)
	unsigned int m_at18;				// +0x18, last word handed to slot 64
	unsigned int m_at1C[3];				// +0x1C
	Rva00078AE3 m_state;				// +0x28, compact 16-byte condition state
	char m_pad038[0x50 - 0x38];
	RenderObjClass *m_renderObject;		// +0x50
};

Int W3DModelDraw::getCurrentBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const
{
	const int MAX_BONE_GET = 64;
	static Matrix3D scratchTransforms[MAX_BONE_GET];

	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;

	if (transforms == 0)
		transforms = scratchTransforms;

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

// ?rva000B51DA@W3DModelDraw@@UAEXI@Z, retail 0x000B51DA..0x000B52CD (243B),
// thiscall RET 4 on the draw interface (+0x0C): slot 21 of 0x007CBB78 (also
// 0x007CBF08 / 0x007CC598). Target facts: when module data +0x68 is set it
// builds the new 16-byte state from the key (count 1 / word +4 when the low
// 24 bits are non-zero), sets bit 30 when the drawable's object template has
// flag 0x40000000 and TheCreateAHeroManager +0x184 is set, and if the state
// at +0x28 differs (count bits, 0x000B4653 entry, bit 30) copies it through
// 0x00078AE3; then, when primary slot 49 answers non-zero, clears +0x14 and
// calls slot 64 (old +0x14, 0, +0x18). ZH's model-condition state update is
// only a semantic lead; the method name stays address-derived.
void W3DModelDraw::rva000B51DA(unsigned int key)
{
	if (!m_moduleData->m_at68)
		return;
	Rva00078AE3 next(key);
	DrawableView *draw = m_drawable;
	ObjectView *object = draw ? draw->m_object : 0;
	if (object && (object->m_template->m_flags11C & 0x40000000) && ((CreateAHeroManagerView *)TheCreateAHeroManager)->m_at184)
		next.m_flag30 = 1;
	Rva00078AE3 *current = &m_state;
	if (current->same(next))
		return;
	current->rva00078AE3(&next);
	if (base49()) {
		unsigned int first = m_at14, last = m_at18;
		m_at14 = 0;
		base64(first, 0, last);
	}
}
