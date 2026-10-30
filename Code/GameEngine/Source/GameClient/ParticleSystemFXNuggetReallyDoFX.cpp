// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include /G7 /Oi- /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ParticleSystemFXNugget::reallyDoFX 2804B @0x001E19E8, named by WorldBuilder 0x00AD7910
// (FXList.cpp); called by doFXPos 0x001E19CE and doFXObj 0x001E24DC. Zero Hour's body plus
// BFME2's bone, aim, land/water and target options.
//
// Member names and offsets from the retail FieldParse table 0x00BDD428 (Name@0x148 Count@0x14C
// Offset@0x150 Radius@0x15C Height@0x168 InitialDelay@0x174 RotateX@0x180 RotateY@0x184
// RotateZ@0x188 OrientToObject@0x18C AttachToObject@0x18D AttachToBone@0x190
// CreateAtGroundHeight@0x194 Ricochet@0x195 CreateBoneOverride@0x198 TargetBoneOverride@0x19C
// CreateBoneAtTarget@0x1A0 TargetCoeff@0x1A4 SystemLife@0x1A8 UseTargetOffset@0x1AC
// SetTargetMatrix@0x1AD OnlyIfOnLand@0x1AE OnlyIfOnWater@0x1AF TargetOffset@0x1B0). Base
// 0x001DFEAA is a shared FXNugget-family base ctor. Vtable 0x00BDD908.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
protected:
	int m_nuggetType; // +4, nugget type id (BFME1 FXNugget::m_nuggetType)
	unsigned char m_pad[0x148 - 8];
};

// math.h's float overloads as static inline, so atan2(float, float) inlines down to _atan2.
#define inline static inline
#include <math.h>
#undef inline
#include "matrix3d.h"
#include "ascii_string.h"
class Object;
#pragma intrinsic(sqrt)

#include "Lib/Coord3D.h"

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM,
		GAUSSIAN,
		TRIANGULAR,
		LOW_BIAS,
		HIGH_BIAS
	};

	GameClientRandomVariable()
	{
		m_type = CONSTANT;
		m_low = 0.0f;
		m_high = 0.0f;
	}
	void setRange(float low, float high, DistributionType type);
	float getValue() const;
private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

class ParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	ParticleSystemFXNugget();
	void reallyDoFX(const Coord3D *primary, const Matrix3D *mtx, const Object *thingToAttachTo, const Object *secondary) const;
	virtual ~ParticleSystemFXNugget();
private:
	AsciiString m_name; // +0x148
	int m_count; // +0x14C
	Coord3D m_offset; // +0x150
	GameClientRandomVariable m_radius; // +0x15C
	GameClientRandomVariable m_height; // +0x168
	GameClientRandomVariable m_delay; // +0x174
	float m_rotateX; // +0x180
	float m_rotateY; // +0x184
	float m_rotateZ; // +0x188
	bool m_orientToObject; // +0x18C
	bool m_attachToObject; // +0x18D
	unsigned char m_pad18E[2]; // +0x18E
	AsciiString m_attachToBone; // +0x190
	bool m_createAtGroundHeight; // +0x194
	bool m_ricochet; // +0x195
	unsigned char m_pad196[2]; // +0x196
	AsciiString m_createBoneOverride; // +0x198
	AsciiString m_targetBoneOverride; // +0x19C
	bool m_createBoneAtTarget; // +0x1A0
	unsigned char m_pad1A1[3]; // +0x1A1
	float m_targetCoeff; // +0x1A4
	int m_systemLife; // +0x1A8
	bool m_useTargetOffset; // +0x1AC
	bool m_setTargetMatrix; // +0x1AD
	bool m_onlyIfOnLand; // +0x1AE
	bool m_onlyIfOnWater; // +0x1AF
	Coord3D m_targetOffset; // +0x1B0
};

#include "../../Include/GameClient/DrawableBFME2.h"
class Object { public: int rva0028B511() const; };
float GetGameClientRandomValueReal(float, float, char *, int);
struct Rva001F3899Arg; struct Rva001F38C1Arg; struct Rva001F3C43Arg;
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class Rva001F38C1Slot { public: void set(const Rva001F38C1Arg &); };
class Rva001F3C43Slot { public: void set(const Rva001F3C43Arg *); };
class Rva001F3C60Slot { public: void set(const AsciiString &); };

class ParticleSystem
{
public:
	void rotateLocalTransformX(float);
	void rotateLocalTransformY(float);
	void rotateLocalTransformZ(float);
	void destroy();
	char pad[0x120];
	unsigned int delay; // +0x120
	char pad124[4];
	int field128; // +0x128
	char pad12C[0x188 - 0x12C];
	Vector3 target; // +0x188
	bool targetValid; // +0x194
	__forceinline void setPosition(const Coord3D *p) { ((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)p); }
	__forceinline void setLocalTransform(const Matrix3D *matrix3D) { ((Rva001F38C1Slot *)this)->set(*(const Rva001F38C1Arg *)matrix3D); }
	__forceinline void attachToObject(const Object *object) { ((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)object); }
	__forceinline void setTarget(const Vector3 &p) { target = p; targetValid = true; }
};
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 { public: void rva0004CBC0() throw(); };

// 12-byte particle-system handle that createParticleSystem returns by value.
class BfmeParticleSystemHandle
{
public:
	__forceinline ~BfmeParticleSystemHandle() { if (system) ((RvaSmartPtr12 *)this)->rva0004CBC0(); }
	operator bool() const { return system != 0; }
	__forceinline ParticleSystem *operator->() const { return system ? system : Make001FCBD7(); }
	ParticleSystem *system;
	void *previous;
	void *next;
};
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
enum PathfindLayerEnum { LAYER_GROUND };
class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
	virtual float s07(float, float, PathfindLayerEnum, float *, bool);
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual bool s19(float, float, float *, float *, unsigned char *);
	PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder { public: int GetGroundLayer(const Coord3D *); };
struct RvaFxAi { char pad[0x10]; Pathfinder *path; };
class AI; extern AI *TheAI;
extern float g_parseDurationMsecScale;

// Zero Hour BaseType.h conversions; BFME2's ceil goes through the CRT.
static __forceinline float ConvertDurationFromMsecsToFrames(float msec) { return msec * g_parseDurationMsecScale; }
static __forceinline float fast_float_ceil(float f) { return (float)ceil((double)f); }
static __forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

static __forceinline const Coord3D *objectPos(const Object *object) { return (const Coord3D *)((const char *)object + 0x38); }
static __forceinline bool boneTransform(const Object *object, const AsciiString &name, Matrix3D &matrix3D) { return ((const Thing *)object)->getDrawable()->rva00272835((int)name.str(), (int)&matrix3D); }

// FXList.cpp's adjustVector (0x001F2EAB), select-any in both units: with its body visible,
// cl treats the offset passed to it as not escaping, which places the frame as retail does.
__declspec(noinline) inline void adjustVector(Coord3D *vec, const Matrix3D* mtx)
{
	if (mtx)
	{
		Vector3 vectmp;
		vectmp.X = vec->x;
		vectmp.Y = vec->y;
		vectmp.Z = vec->z;
		vectmp = mtx->Rotate_Vector(vectmp);
		*vec = *reinterpret_cast<const Coord3D *>(&vectmp);
	}
}

void ParticleSystemFXNugget::reallyDoFX(const Coord3D *primary, const Matrix3D *mtx, const Object *thingToAttachTo, const Object *secondary) const
{
	Vector3 offsetCopy = *(const Vector3 *)&m_offset; Vector3 &localOffset = offsetCopy;
	if (mtx) adjustVector((Coord3D *)&localOffset, mtx);
	const ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(m_name);
	if (particleSystemTemplate) for (int i = 0; i < m_count; ++i) {
		BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
		if (sys) {
			Coord3D newPosStorage = {0, 0, 0}; Coord3D &newPos = newPosStorage;
			float rad = m_radius.getValue();
			float angle = GetGameClientRandomValueReal(0, 6.28318530717958647692f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\FXList.cpp", 1698);
			bool needsHeight = true;
			if (!((const StringBase<char> *)&m_createBoneOverride)->isEmpty() && thingToAttachTo) {
				Matrix3D bm(true);
				if (m_createBoneAtTarget && secondary) boneTransform(secondary, m_createBoneOverride, bm);
				else boneTransform(thingToAttachTo, m_createBoneOverride, bm);
				Vector3 translation = bm.Get_Translation(); newPos = *(const Coord3D *)&translation; needsHeight = false;
			} else {
				newPos.x = rad * cos(angle) + primary->x + localOffset.X;
				newPos.y = rad * sin(angle) + primary->y + localOffset.Y;
			}
			if (m_createAtGroundHeight && TheTerrainLogic) {
				//old way:
				//newPos.z = TheTerrainLogic->getGrsoundHeight( newPos.x, newPos.y ) + 1;// The plus one prevents scissoring with terrain

				//new way: now we allow bridges in the GroundHeight.
				if (needsHeight) { PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, &newPos); newPos.z = TheTerrainLogic->s07(newPos.x, newPos.y, layer, 0, true); }
			}
			else if (needsHeight) newPos.z = m_height.getValue() + primary->z + localOffset.Z;
			if (m_orientToObject && mtx) {
				Matrix3D orientation = *mtx;
				if (m_setTargetMatrix && secondary) {
					const Coord3D *sp = objectPos(secondary);
					Vector3 deltaStorage = Vector3(-newPos.x, -newPos.y, -newPos.z) + Vector3(sp->x, sp->y, sp->z); Vector3 &delta = deltaStorage;
					float len = WWMath::Sqrt(delta.X * delta.X + delta.Y * delta.Y); float y = delta.Z + 10.0f; float angleToTarget = atan2(y, len);
					Matrix3D rotation(true); rotation.Rotate_Y(3.1415927f - angleToTarget); orientation.postMul(rotation);
				}
				sys->setLocalTransform(&orientation);
			}
			if (m_rotateX != 0) sys->rotateLocalTransformX(m_rotateX);
			if (m_rotateY != 0) sys->rotateLocalTransformY(m_rotateY);
			if (m_rotateZ != 0) sys->rotateLocalTransformZ(m_rotateZ);
			if (m_onlyIfOnLand) {
				bool water = TheTerrainLogic->s19(newPos.x, newPos.y, 0, 0, 0);
				if (water && TheAI && ((RvaFxAi *)TheAI)->path && ((RvaFxAi *)TheAI)->path->GetGroundLayer(&newPos) != 1) water = false;
				if (thingToAttachTo && thingToAttachTo->rva0028B511() != 1) water = false;
				if (water) { sys->destroy(); continue; }
			} else if (m_onlyIfOnWater) {
				bool water = TheTerrainLogic->s19(newPos.x, newPos.y, 0, 0, 0);
				if (water && TheAI && ((RvaFxAi *)TheAI)->path && ((RvaFxAi *)TheAI)->path->GetGroundLayer(&newPos) != 1) water = false;
				if (thingToAttachTo && thingToAttachTo->rva0028B511() != 1) water = false;
				if (!water) { sys->destroy(); continue; }
			}
			if (m_attachToObject && thingToAttachTo) sys->attachToObject(thingToAttachTo); else sys->setPosition(&newPos);
			if (!((const StringBase<char> *)&m_attachToBone)->isEmpty()) ((Rva001F3C60Slot *)sys.operator->())->set(m_attachToBone);
			if (!((const StringBase<char> *)&m_targetBoneOverride)->isEmpty() && secondary) {
				Matrix3D bm(true); Vector3 p;
				if (boneTransform(secondary, m_targetBoneOverride, bm)) { p.X = bm.Get_X_Translation(); p.Y = bm.Get_Y_Translation(); p.Z = bm.Get_Z_Translation(); }
				else { const Coord3D *sp = objectPos(secondary); p = Vector3(sp->x, sp->y, sp->z); }
				sys->setTarget(p);
			}
			if (m_useTargetOffset) { Vector3 p(m_targetOffset.x + newPos.x, m_targetOffset.y + newPos.y, m_targetOffset.z + newPos.z); sys->setTarget(p); }
			if (m_systemLife >= 0) { ParticleSystem *raw = sys.operator->(); int field = m_systemLife; raw->field128 = field; }
			float delayInMsec = m_delay.getValue();
			if (delayInMsec >= 0.0f) {
				unsigned int delayInFrames = REAL_TO_INT_CEIL(ConvertDurationFromMsecsToFrames(delayInMsec));
				sys->delay = delayInFrames;
			}
		}
	}
}
