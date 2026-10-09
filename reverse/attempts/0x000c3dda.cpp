// ?getProjectileLaunchOffset@W3DModelDraw@@UBE_NABVModelConditionFlags@@W4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@4@Z
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BF1 clean W3DModelDrawGetPristineBonePositionsForConditionState donor
// rev9cbfb551 preserves the seven-argument query and missing-bone fallback.
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
#include "ascii_string.h"
#include <math.h>
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
	Vector3(Real x, Real y, Real z) {X=x;Y=y;Z=z;}
 __forceinline Vector3(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;}
 __forceinline Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return*this;}
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

 __forceinline float Get_X_Translation()const{return Row[0].W;}
 __forceinline float Get_Y_Translation()const{return Row[1].W;}
 __forceinline float Get_Z_Translation()const{return Row[2].W;}
 __forceinline void Pre_Rotate_Z(float theta){
 float tmp1,tmp2,c,s;c=(float)cos(theta);s=(float)sin(theta);
 tmp1=Row[0].X;tmp2=Row[1].X;Row[0].X=(float)(c*tmp1-s*tmp2);Row[1].X=(float)(s*tmp1+c*tmp2);
 tmp1=Row[0].Y;tmp2=Row[1].Y;Row[0].Y=(float)(c*tmp1-s*tmp2);Row[1].Y=(float)(s*tmp1+c*tmp2);
 tmp1=Row[0].Z;tmp2=Row[1].Z;Row[0].Z=(float)(c*tmp1-s*tmp2);Row[1].Z=(float)(s*tmp1+c*tmp2);
 tmp1=Row[0].W;tmp2=Row[1].W;Row[0].W=(float)(c*tmp1-s*tmp2);Row[1].W=(float)(s*tmp1+c*tmp2);
 }
 __forceinline void Adjust_Translation(const Vector3&v){Row[0].W+=v.X;Row[1].W+=v.Y;Row[2].W+=v.Z;}
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

enum WeaponSlotType {WEAPONSLOT_PRIMARY=0};
enum WhichTurretType {TURRET_INVALID=-1};
struct Rva00774AA0DrawableBones;

class Drawable
{
public:
	const Real getScale() const;
 float getOrientation()const{return orientation;}
 Int getPristineBonePositions(const char*,Int,Coord3D*,Matrix3D*,Int,Int)const;
	const Object *getObject() const { return m_object; }

	UnsignedByte m_unmodelled000[0x44];float orientation;UnsignedByte pad48[0xFC-0x48];
	Object *m_object;									///< +0xFC
	UnsignedByte m_unmodelled100[0x264];
	const Rva00774AA0DrawableBones *m_rva2F0Bones;		///< target +0x364
};

class Rva000BBDDF {public:void*rva000BBDDF(int,int*)const;};
class Rva000B4BED {public:void*rva000B4BED(const void*);};
class Rva000B4B23 {public:void*rva000B4B23(const ModelConditionFlags&);};
struct Rva000C3886Range;struct Rva000C3886Obj;
class Rva000C3886 {public:void rva000C3886(void*,float,Rva000C3886Range*,Rva000C3886Obj*,void*);};
struct WeaponBarrelInfo {unsigned bones[3];Matrix3D m_projectileOffsetMtx;};
struct ModelConditionInfo {
 char opaque00[0xAC];_STL::vector<WeaponBarrelInfo>m_weaponBarrelInfoVec[3];
 const Matrix3D*findPristineBone(NameKeyType key,Int*index)const{
  return (const Matrix3D*)((const Rva000BBDDF*)this)->rva000BBDDF((int)key,index);
 }
};
class W3DModelDrawModuleData {public:
 const ModelConditionInfo*findBestInfo(const ModelConditionFlags&c)const{return (const ModelConditionInfo*)((Rva000B4B23*)this)->rva000B4B23(c);}
 const ModelConditionInfo*rva00765DC0(const ModelConditionFlags&c)const{return (const ModelConditionInfo*)((Rva000B4BED*)this)->rva000B4BED(&c);}
 UnsignedByte m_unmodelled00[0x30];_STL::vector<AsciiString>m_extraPublicBones;unsigned field3C;AsciiString m_attachToDrawableBone;
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
	virtual bool getProjectileLaunchOffset(const ModelConditionFlags&,WeaponSlotType,Int,Matrix3D*,WhichTurretType,Coord3D*,Coord3D*)const=0;
	virtual Int getPristineBonePositionsForConditionState(const ModelConditionFlags &condition,
		const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *boneIndices) const = 0;
};

class W3DModelDraw : public DrawModule, public ObjectDrawInterface
{
public:
	virtual void objectDrawSlot00() const;
	virtual void objectDrawSlot01() const;
	virtual bool getProjectileLaunchOffset(const ModelConditionFlags&,WeaponSlotType,Int,Matrix3D*,WhichTurretType,Coord3D*,Coord3D*)const;
	virtual Int getPristineBonePositionsForConditionState(const ModelConditionFlags &condition,
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

bool W3DModelDraw::getProjectileLaunchOffset(const ModelConditionFlags&condition,WeaponSlotType wslot,Int specificBarrelToUse,Matrix3D*launchPos,WhichTurretType tur,Coord3D*turretRotPos,Coord3D*turretPitchPos)const{
 const ModelConditionInfo*stateToUse=findBestInfo(condition);
 const ModelConditionInfo*boneState=getW3DModelDrawModuleData()->rva00765DC0(condition);
 if(!stateToUse)return false;
 const W3DModelDrawModuleData*d=getW3DModelDrawModuleData();
 ((Rva000C3886*)stateToUse)->rva000C3886(0,getDrawable()->getScale(),(Rva000C3886Range*)&d->m_extraPublicBones,(Rva000C3886Obj*)boneState,(void*)getDrawable()->m_rva2F0Bones);
 Coord3D techOffset;techOffset.x=0;techOffset.y=0;techOffset.z=0;Matrix3D pivot;
 if(!d->m_attachToDrawableBone.isEmpty()&&getDrawable()->getPristineBonePositions(d->m_attachToDrawableBone.str(),0,0,&pivot,1,0)==1){
  pivot.Pre_Rotate_Z(getDrawable()->getOrientation());techOffset.x=pivot.Get_X_Translation();techOffset.y=pivot.Get_Y_Translation();techOffset.z=pivot.Get_Z_Translation();
 }
 const _STL::vector<WeaponBarrelInfo>&wbvec=boneState->m_weaponBarrelInfoVec[wslot];
 if(wbvec.empty())launchPos=0;
 else{
  if(specificBarrelToUse<0||specificBarrelToUse>=wbvec.size())specificBarrelToUse=0;
  if(launchPos){*launchPos=wbvec[specificBarrelToUse].m_projectileOffsetMtx;launchPos->Adjust_Translation(Vector3(techOffset.x,techOffset.y,techOffset.z));}
 }
 if(turretRotPos){turretRotPos->x=0;turretRotPos->y=0;turretRotPos->z=0;}if(turretPitchPos){turretPitchPos->x=0;turretPitchPos->y=0;turretPitchPos->z=0;}if(launchPos)return true;return false;
}
