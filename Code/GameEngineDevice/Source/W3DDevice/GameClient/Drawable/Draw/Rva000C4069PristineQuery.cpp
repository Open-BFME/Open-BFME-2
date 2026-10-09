// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BF1 clean W3DModelDrawGetPristineBonePositionsForConditionState donor
// rev9cbfb551 preserves the seven-argument query and missing-bone fallback.
// The three containing secondary tables belong to Scripted/Quadruped/Supply
// objects. That proves table association; it does not distinguish an inherited
// base implementation from a Scripted override. Keep an address-derived
// owner until the declaring class is independently established.
// Native C4069..C433A721B independently proves ObjectDrawInterface this+0C,
// current state at whole14, render object50, drawable-owned bones364,
// static64-matrix scratch and optional bone-index output. Drawable27274D
// dispatches the same seven-argument method through interface slot0C.
// Template selection B4B23 is independently bounded202B; the existing
// B4BED subset-state provider176B and C3886 validator114B remain owned.
// BBDDF74B is the corrected thiscall pristine-bone lookup owned by its unit.
// Native byte-copy assignments require the WWMath row assignments visible
// and forced inline; CRT sprintf/tolower remain imported as in retail.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class ModelConditionFlags;

class Vector3
{
public:
	Real X, Y, Z;
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
};

class Vector4
{
public:
	Real X, Y, Z, W;
	Vector4() {}
	Vector4(const Vector4 &other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}
	__forceinline Vector4 &operator=(const Vector4 &other)
	{
		X = other.X; Y = other.Y; Z = other.Z; W = other.W;
		return *this;
	}
	void Set(Real x, Real y, Real z, Real w)
	{
		X = x; Y = y; Z = z; W = w;
	}
};

#include "Coord3D.h"

class Matrix3D
{
public:
	__forceinline Matrix3D() {}											///< 0x000458EF
	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		Row[0] = other.Row[0];
		Row[1] = other.Row[1];
		Row[2] = other.Row[2];
		return *this;
	}

	Vector3 Get_Translation() const
	{
		return Vector3(Row[0].W, Row[1].W, Row[2].W);
	}

	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	Vector4 Row[3];
};

class RenderObjClass;
class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	UnsignedByte m_unmodelled00[0x8];
	Matrix3D m_transform;
};

class AsciiString;
struct Rva00774AA0DrawableBones;

class Drawable
{
public:
	const Real getScale() const;
	const Object *getObject() const { return m_object; }

	UnsignedByte m_unmodelled000[0xfc];
	Object *m_object;									///< +0xFC
	UnsignedByte m_unmodelled100[0x264];
	const Rva00774AA0DrawableBones *m_rva2F0Bones;		///< target +0x364
};

class Rva000BBDDF {public:void*rva000BBDDF(int,int*)const;};
class Rva000B4BED {public:void*rva000B4BED(const void*);};
class Rva000B4B23 {public:void*rva000B4B23(const ModelConditionFlags&);};
struct Rva000C3886Range;struct Rva000C3886Obj;
class Rva000C3886 {public:void rva000C3886(void*,float,Rva000C3886Range*,Rva000C3886Obj*,void*);};
struct ModelConditionInfo {
 const Matrix3D*findPristineBone(NameKeyType key,Int*index)const{
  return (const Matrix3D*)((const Rva000BBDDF*)this)->rva000BBDDF((int)key,index);
 }
};
class W3DModelDrawModuleData {public:
 const ModelConditionInfo*findBestInfo(const ModelConditionFlags&c)const{return (const ModelConditionInfo*)((Rva000B4B23*)this)->rva000B4B23(c);}
 const ModelConditionInfo*rva00765DC0(const ModelConditionFlags&c)const{return (const ModelConditionInfo*)((Rva000B4BED*)this)->rva000B4BED(&c);}
 UnsignedByte m_unmodelled00[0x30];_STL::vector<AsciiString>m_extraPublicBones;
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class DrawModule
{
public:
	virtual void drawModuleSlot00();
	const W3DModelDrawModuleData *getModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }

	const W3DModelDrawModuleData *m_moduleData;		///< +0x04
	Drawable *m_drawable;								///< +0x08
};

class ObjectDrawInterface
{
public:
	virtual void objectDrawSlot00() const = 0;
	virtual void objectDrawSlot01() const = 0;
	virtual void objectDrawSlot02() const = 0;
	virtual Int rva000C4069(const ModelConditionFlags &condition,
		const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *boneIndices) const = 0;
};

class Rva000C4069 : public DrawModule, public ObjectDrawInterface
{
public:
	virtual void objectDrawSlot00() const;
	virtual void objectDrawSlot01() const;
	virtual void objectDrawSlot02() const;
	virtual Int rva000C4069(const ModelConditionFlags &condition,
		const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *boneIndices) const;

	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return getModuleData(); }
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return getW3DModelDrawModuleData()->findBestInfo(c);
	}

	UnsignedByte m_unmodelled10[4];
 const ModelConditionInfo *m_curState;				///< target +0x14
	UnsignedByte m_unmodelled14[0x38];
	RenderObjClass *m_renderObject;						///< target +0x50
};

Int Rva000C4069::rva000C4069(
	const ModelConditionFlags &condition,
	const char *boneNamePrefix,
	Int startIndex,
	Coord3D *positions,
	Matrix3D *transforms,
	Int maxBones,
	Int *boneIndices
) const
{
	const ModelConditionInfo *stateToUse = findBestInfo(condition);
	if (!stateToUse)
		return 0;

	const ModelConditionInfo *boneState = getW3DModelDrawModuleData()->rva00765DC0(condition);
	RenderObjClass *robj = stateToUse == m_curState ? m_renderObject : NULL;
	const Rva00774AA0DrawableBones *drawBones = getDrawable()->m_rva2F0Bones;
	((Rva000C3886*)stateToUse)->rva000C3886(robj,getDrawable()->getScale(),(Rva000C3886Range*)&getW3DModelDrawModuleData()->m_extraPublicBones,(Rva000C3886Obj*)boneState,(void*)drawBones);

	const int MAX_BONE_GET = 64;
	static Matrix3D tmpMtx[MAX_BONE_GET];

	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;

	if (transforms == NULL)
		transforms = tmpMtx;

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

		for (char *c = buffer; c && *c; ++c)
		{
			*c = tolower(*c);
		}

		const Matrix3D *mtx = (const Matrix3D*)((const Rva000BBDDF*)boneState)->rva000BBDDF(NAMEKEY(buffer), NULL);
		if (mtx)
		{
			transforms[posCount] = *mtx;
			if (boneIndices)
				boneIndices[posCount] = i;
		}
		else
		{
			if (boneIndices)
				boneIndices[posCount] = 0;
			const Object *obj = getDrawable()->getObject();
			if (obj)
				transforms[posCount] = *obj->getTransformMatrix();
			else
				transforms[posCount].Make_Identity();
			break;
		}

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
