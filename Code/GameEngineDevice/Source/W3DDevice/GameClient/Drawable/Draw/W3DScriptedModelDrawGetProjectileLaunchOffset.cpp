// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// ?getProjectileLaunchOffset@W3DScriptedModelDraw@@UBE_NABVModelConditionFlags@@W4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@4@Z
// retail 0x000C3DDA..0x000C4069 (655 bytes).
// WorldBuilder twin 0x9363D0 is W3DScriptedModelDraw::getProjectileLaunchOffset
// (W3DScriptedModelDraw.cpp assert line 6795 "specificBarrelToUse should now
// always be explicit"). Three retail vftables hold 0x4C3DDA in the
// ObjectDrawInterface (this+0C) table. Same callees as the sibling
// getPristineBonePositionsForConditionState (0x000C4069): findBestInfo B4B23
// and the bone-state provider B4BED then the C3886 validator with a NULL
// render object. BFME2 drops the Zero Hour turret handling: the turret outputs
// are only zeroed. The attach-to-drawable bone offset is the pristine bone
// matrix pre-rotated about Z by the drawable orientation (WWMath
// In_Place_Pre_Rotate_Z unrolled over four columns). Barrel records are 0x3C
// bytes with the projectile offset matrix at +0C; the per-slot vectors start
// at state +AC.
#include "ascii_string.h"
#include "Coord3D.h"
#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#define NULL 0

enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WhichTurretType { TURRET_INVALID = -1 };

class ModelConditionFlags;

class Vector3
{
public:
	Real X, Y, Z;
	__forceinline Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
};

class Vector4
{
public:
	Real X, Y, Z, W;
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
	__forceinline Vector4 &operator=(const Vector4 &other)
	{
		X = other.X; Y = other.Y; Z = other.Z; W = other.W;
		return *this;
	}
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	__forceinline Real Get_X_Translation() const { return Row[0][3]; }
	__forceinline Real Get_Y_Translation() const { return Row[1][3]; }
	__forceinline Real Get_Z_Translation() const { return Row[2][3]; }
	__forceinline void Adjust_Translation(const Vector3 &t)
	{
		Row[0][3] += t[0];
		Row[1][3] += t[1];
		Row[2][3] += t[2];
	}
	__forceinline void Pre_Rotate_Z(Real theta)
	{
		float tmp1,tmp2;
		float c,s;

		c = cosf(theta);
		s = sinf(theta);

		// Retail ranks the first column's c*tmp1 product as a direct read of
		// pivot+0 (fld tmp1 then fmul c); the subscripted read loads c first.
		tmp1 = Row[0].X; tmp2 = Row[1][0];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][0] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[0][1]; tmp2 = Row[1][1];
		Row[0][1] = (float)(c*tmp1 - s*tmp2);
		Row[1][1] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[0][2]; tmp2 = Row[1][2];
		Row[0][2] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[0][3]; tmp2 = Row[1][3];
		Row[0][3] = (float)(c*tmp1 - s*tmp2);
		Row[1][3] = (float)(s*tmp1 + c*tmp2);
	}
	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		Row[0] = other.Row[0];
		Row[1] = other.Row[1];
		Row[2] = other.Row[2];
		return *this;
	}

	Vector4 Row[3];
};

struct WeaponBarrelInfo
{
	Int m_recoilBone;
	Int m_fxBone;
	Int m_muzzleFlashBone;
	Matrix3D m_projectileOffsetMtx;
};

struct WeaponBarrelInfoVec
{
	WeaponBarrelInfo *_M_start;
	WeaponBarrelInfo *_M_finish;
	WeaponBarrelInfo *_M_end_of_storage;
	__forceinline bool empty() const { return _M_start == _M_finish; }
	__forceinline unsigned int size() const { return _M_finish - _M_start; }
	__forceinline const WeaponBarrelInfo &operator[](unsigned int i) const { return _M_start[i]; }
};

struct Rva000C3886Range;
struct Rva000C3886Obj;
class Rva000C3886 { public: void rva000C3886(void *, float, Rva000C3886Range *, Rva000C3886Obj *, void *); };
class Rva000B4BED { public: void *rva000B4BED(const void *); };
class Rva000B4B23 { public: void *rva000B4B23(const ModelConditionFlags &); };

struct ModelConditionInfo
{
	UnsignedByte m_unmodelled00[0xac];
	WeaponBarrelInfoVec m_weaponBarrelInfoVec[1];		///< +0xAC
};

class W3DModelDrawModuleData
{
public:
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return (const ModelConditionInfo *)((Rva000B4B23 *)this)->rva000B4B23(c);
	}
	const ModelConditionInfo *rva00765DC0(const ModelConditionFlags &c) const
	{
		return (const ModelConditionInfo *)((Rva000B4BED *)this)->rva000B4BED(&c);
	}

	UnsignedByte m_unmodelled00[0x30];
	UnsignedByte m_extraPublicBones[0x10];				///< +0x30
	AsciiString m_attachToDrawableBone;					///< +0x40
};

class Drawable
{
public:
	const Real getScale() const;
	Real getOrientation() const { return m_orientation; }
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions,
		Matrix3D *transforms, Int maxBones, Int unk) const;

	UnsignedByte m_unmodelled000[0x44];
	Real m_orientation;									///< +0x44
	UnsignedByte m_unmodelled048[0x31c];
	void *m_bones;										///< +0x364
};

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
	virtual Bool getProjectileLaunchOffset(const ModelConditionFlags &condition, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D *launchPos, WhichTurretType tur, Coord3D *turretRotPos,
		Coord3D *turretPitchPos) const = 0;
};

class W3DScriptedModelDraw : public DrawModule, public ObjectDrawInterface
{
public:
	virtual Bool getProjectileLaunchOffset(const ModelConditionFlags &condition, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D *launchPos, WhichTurretType tur, Coord3D *turretRotPos,
		Coord3D *turretPitchPos) const;

	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return getModuleData(); }
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return getW3DModelDrawModuleData()->findBestInfo(c);
	}
};

Bool W3DScriptedModelDraw::getProjectileLaunchOffset(
	const ModelConditionFlags &condition,
	WeaponSlotType wslot,
	Int specificBarrelToUse,
	Matrix3D *launchPos,
	WhichTurretType tur,
	Coord3D *turretRotPos,
	Coord3D *turretPitchPos
) const
{
	const ModelConditionInfo *stateToUse = findBestInfo(condition);
	const ModelConditionInfo *boneState = getW3DModelDrawModuleData()->rva00765DC0(condition);
	if (!stateToUse)
		return false;

	const W3DModelDrawModuleData *d = getW3DModelDrawModuleData();
	((Rva000C3886 *)stateToUse)->rva000C3886(NULL, getDrawable()->getScale(),
		(Rva000C3886Range *)&d->m_extraPublicBones, (Rva000C3886Obj *)boneState, getDrawable()->m_bones);

	Coord3D techOffset;
	techOffset.x = 0.0f;
	techOffset.y = 0.0f;
	techOffset.z = 0.0f;
	Matrix3D pivot;
	if (!((const StringBase<char> *)&d->m_attachToDrawableBone)->isEmpty() &&
		getDrawable()->getPristineBonePositions(d->m_attachToDrawableBone.str(), 0, NULL, &pivot, 1, 0) == 1)
	{
		pivot.Pre_Rotate_Z(getDrawable()->getOrientation());
		techOffset.x = pivot.Get_X_Translation();
		techOffset.y = pivot.Get_Y_Translation();
		techOffset.z = pivot.Get_Z_Translation();
	}

	const WeaponBarrelInfoVec &wbvec = boneState->m_weaponBarrelInfoVec[wslot];
	if (wbvec.empty())
	{
		launchPos = NULL;
	}
	else
	{
		if (specificBarrelToUse < 0 || specificBarrelToUse >= wbvec.size())
			specificBarrelToUse = 0;

		if (launchPos)
		{
			*launchPos = wbvec[specificBarrelToUse].m_projectileOffsetMtx;
			launchPos->Adjust_Translation(Vector3(techOffset.x, techOffset.y, techOffset.z));
		}
	}

	if (turretRotPos)
	{
		turretRotPos->x = 0.0f;
		turretRotPos->y = 0.0f;
		turretRotPos->z = 0.0f;
	}
	if (turretPitchPos)
	{
		turretPitchPos->x = 0.0f;
		turretPitchPos->y = 0.0f;
		turretPitchPos->z = 0.0f;
	}

	return launchPos ? true : false;
}
