// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Target boundary: 0x000CA352..0x000CA72E; complete 988 bytes RET 8.
// WB 0x00916F60 names W3DQuadrupedDraw::getFootLocations; target slot 47
// and the W3DQuadrupedDraw factory/constructor family independently agree.
// The rowed constructor installs the draw-interface vptr at +0x0C; this
// entry reads module data at -8 and drawable at -4 relative to that subobject.
// The modeled primary prefix therefore has module data +4 and drawable +8.
// Matrix3D::preMul/mul is the donor semantic guide. The target's inlined
// products independently establish row storage and the multiplication path.
// The same-valued worldSpace predicate preserves frame/register allocation.
// An explicit second-row translation expression and a volatile read of
// A.Row[2].X in the X column preserve retail SSE operand scheduling without
// changing expression order. Removing either shape loses the match. The
// earlier bank donor revision was not recorded; retain that uncertainty.
#include "ascii_string.h"
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	void resize(unsigned int n);
	T &operator[](unsigned int n) { return *(_M_start + n); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > Coord3DVector;

class Vector4
{
public:
	Real X, Y, Z, W;
};

static __forceinline Real submul(const Vector4 &row, Real tmp1, Real tmp2, Real tmp3)
{
	return row.X * tmp1 + row.Y * tmp2 + row.Z * tmp3;
}

class Matrix3D
{
public:
	Vector4 Row[3];

	// does "this = A * B"
	__forceinline void mul(const Matrix3D &A, const Matrix3D &B)
	{
		Real tmp1, tmp2, tmp3;

		tmp1 = B.Row[0].X;
		tmp2 = B.Row[1].X;
		tmp3 = B.Row[2].X;

		this->Row[0].X = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].X = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].X = (*(const volatile Real*)&A.Row[2].X * tmp1 + A.Row[2].Y * tmp2 + A.Row[2].Z * tmp3);

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
		this->Row[1].W = (A.Row[1].X * tmp1 + A.Row[1].Y * tmp2 + A.Row[1].Z * tmp3) + A.Row[1].W;
		this->Row[2].W = submul(A.Row[2], tmp1, tmp2, tmp3) + A.Row[2].W;
	}

	// does "this = that * this"
	__forceinline void preMul(const Matrix3D &that)
	{
		this->mul(that, *this);
	}

	Real getX() const { return Row[0].W; }
	Real getY() const { return Row[1].W; }
	Real getZ() const { return Row[2].W; }
};

class ModelConditionFlags;

class Rva000CA352Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	unsigned char m_pad00[0x08];
	Matrix3D m_transform;				// +0x08
};

class Drawable
{
public:
	const ModelConditionFlags &getModelConditionFlags() const { return *(const ModelConditionFlags *)m_conditionFlags; }
	Rva000CA352Object *getObject1() const { return m_fc; }
private:
	unsigned char m_pad000[0xFC];
	Rva000CA352Object *m_fc;			// +0xFC
	unsigned char m_pad100[0x258 - 0x100];
	unsigned char m_conditionFlags[4];		// +0x258
};

class W3DQuadrupedDrawModuleData
{
public:
	unsigned char m_pad000[0x188];
	AsciiString m_footBones[4];			// +0x188
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class Rva000CA352DrawBase
{
public:
	virtual void base00();
protected:
	const W3DQuadrupedDrawModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;				// +0x08
};

class Rva000CA352DrawInterface
{
public:
	virtual void i00();
	virtual void i01();
	virtual void i02();
	virtual Int getPristineBonePositionsForConditionState(const ModelConditionFlags &condition, const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;	// slot 3
	virtual void i04();
	virtual Bool getCurrentWorldspaceClientBonePositions(const char *boneName, Matrix3D &transform) const;	// slot 5
	virtual void i06(); virtual void i07(); virtual void i08(); virtual void i09();
	PAD_VIRTUALS10(i1) PAD_VIRTUALS10(i2) PAD_VIRTUALS10(i3)
	virtual void i40(); virtual void i41(); virtual void i42(); virtual void i43(); virtual void i44();
	virtual void i45(); virtual void i46();
	virtual Bool getFootLocations(Coord3DVector &feet, Bool worldSpace);	// slot 47
};

class W3DQuadrupedDraw : public Rva000CA352DrawBase, public Rva000CA352DrawInterface
{
public:
	virtual Bool getFootLocations(Coord3DVector &feet, Bool worldSpace);
};

static __forceinline Bool boneNameEmpty(const AsciiString &name)
{
	return ((const StringBase<char> *)&name)->isEmpty();
}

Bool W3DQuadrupedDraw::getFootLocations(Coord3DVector &feet, Bool worldSpace)
{
	const W3DQuadrupedDrawModuleData *d = m_moduleData;
	if (!d)
		return false;
	if (boneNameEmpty(d->m_footBones[0]) && boneNameEmpty(d->m_footBones[1]))
		return false;
	if (boneNameEmpty(d->m_footBones[2]) && boneNameEmpty(d->m_footBones[3]))
		return false;

	const Matrix3D *xform = 0;
	Drawable *draw = 0;
	if ((this ? (worldSpace) : (worldSpace)))
	{
		draw = m_drawable;
		if (!draw)
			return false;
		Rva000CA352Object *obj = draw->getObject1();
		if (!obj)
			return false;
		xform = obj->getTransformMatrix();
		if (!xform)
			return false;
	}

	feet.resize(4);
	Bool found[4];
	Matrix3D mtx;
	for (Int i = 0; i < 4; i++)
	{
		if (boneNameEmpty(d->m_footBones[i]))
		{
			found[i] = false;
			continue;
		}
		if (worldSpace)
		{
			found[i] = getPristineBonePositionsForConditionState(draw->getModelConditionFlags(), d->m_footBones[i].str(), 0, 0, &mtx, 1, 0);
			mtx.preMul(*xform);
		}
		else
		{
			found[i] = getCurrentWorldspaceClientBonePositions(d->m_footBones[i].str(), mtx);
		}
		if (found[i])
		{
			feet[i].x = mtx.getX();
			feet[i].y = mtx.getY();
			feet[i].z = mtx.getZ();
		}
	}

	if (!found[0])
	{
		if (!found[1])
			return false;
		feet[0] = feet[1];
	}
	else if (!found[1])
	{
		feet[1] = feet[0];
	}
	if (!found[2])
	{
		if (!found[3])
			return false;
		feet[2] = feet[3];
	}
	else if (!found[3])
	{
		feet[3] = feet[2];
	}
	return true;
}
