// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include
// stlport
//
// BoneFXUpdate::update and the per-bone FX helpers (BFME 2), from the
// Generals Zero Hour BoneFXUpdate.cpp.
//
// Target facts. update is reached through the UpdateModuleInterface at +0x10
// (slot 31 of the vftable block at 0x0084B0E8, between the module data's
// slots and getDisabledTypesToProcess). The ZH-port unit BoneFXUpdate.cpp
// builds without this region's flags and keeps its copy present-unmatched.
// Layout (full object): next FX / OCL / particle-system frames
// [4 body states][8 bones] at +0x2C / +0xAC / +0x12C, bone positions at
// +0x1AC / +0x32C / +0x4AC, current body state +0x62C and the active flag
// +0x634 (initTimes 0x0048750B sets the frames; the rowed xfer 0x00487C75
// transfers them). The module data keeps 0x24-byte FX / OCL /
// particle-system entries at +0xC / +0x490 / +0x914, each with its target at
// +0x20; the FX / OCL / particle-system damage-type masks sit just before
// each array (+8 / +0x48C / +0x910), one bit per damage type (bit type-1).
// GameLogic's frame is at +0x40. resolveBoneLocations is primary vtable slot
// 13 (0x00487634); the body module's getLastDamageInfo is its slot 15 and
// the damage type is at +0x10 of the info. BFME 2's createParticleSystem
// returns the 12-byte particle-system handle (see SlavedUpdateRepair.cpp).
#include <vector>
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define TRUE 1
#define FALSE 0

class ModuleData;
class Object;
class ParticleSystemTemplate;
class Matrix3D;

enum DamageType
{
	DAMAGE_EXPLOSION = 1
};

typedef UnsignedInt DamageTypeFlags;

inline Bool getDamageTypeFlag(DamageTypeFlags flags, DamageType dt)
{
	return (flags & (1 << (dt - 1))) != 0;
}

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = NULL,
		Real primarySpeed = 0.0f, const Coord3D *secondary = NULL);
};

class ObjectCreationList
{
public:
	void create(void *primaryObj, void *primary, void *secondary, Int lifetimeFrames);
	static void create(const ObjectCreationList *ocl, Object *primaryObj, const Coord3D *primary, const Coord3D *secondary)
	{
		if (ocl)
			((ObjectCreationList *)ocl)->create(primaryObj, (void *)primary, (void *)secondary, 0);
	}
};

struct DamageInfoInput
{
	char m_unknown00[0x10];
	DamageType m_damageType; // +0x10
};

struct DamageInfo
{
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual void b05(); virtual void b06(); virtual void b07(); virtual void b08(); virtual void b09();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
	virtual const DamageInfo *getLastDamageInfo() const; // slot 15
};

// Drawable 0x00270260 (rowed under a placeholder name): hidden when either
// of the bytes +0x43D / +0x43E is set.
class Rva00270260
{
public:
	bool rva00270260();
};

class Drawable
{
public:
	Bool isDrawableEffectivelyHidden() const { return ((Rva00270260 *)this)->rva00270260(); }
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	char m_unknown00[0x254];
	BodyModuleInterface *m_body; // +0x254
};

// The particle system's setters, rowed under placeholder names: position copy
// 0x001F3899, attached object ID (+0xB4, from the object's +0x74) 0x001F3C43
// and the stopped byte (+0x1A3) 0x001F3852.
struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};
class Rva001F3852ByteOneSetter
{
public:
	void enable();
};

class ParticleSystem
{
public:
	ParticleSystemID getSystemID() const { return m_systemID; }
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}
	void stop() { ((Rva001F3852ByteOneSetter *)this)->enable(); }

private:
	char m_unknown00[0xA8];
	ParticleSystemID m_systemID; // +0xA8
};
ParticleSystem *Make001FCBD7();

// The 12-byte handle: the out-of-line unlink is 0x0004CBC0, which the handle's
// destructor calls only for a live system.
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum BodyDamageType
{
	BODY_PRISTINE = 0
};

enum
{
	BODYDAMAGETYPE_COUNT = 4,
	BONE_FX_MAX_BONES = 8
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

struct BaseBoneListInfo
{
	char m_unknown00[0x20];
};

struct BoneFXListInfo : public BaseBoneListInfo
{
	const FXList *fx; // +0x20
};

struct BoneOCLInfo : public BaseBoneListInfo
{
	const ObjectCreationList *ocl; // +0x20
};

struct BoneParticleSystemInfo : public BaseBoneListInfo
{
	const ParticleSystemTemplate *particleSysTemplate; // +0x20
};

class BoneFXUpdateModuleData
{
public:
	char m_unknown00[0x08];
	DamageTypeFlags m_damageFXTypes; // +8
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0xC
	DamageTypeFlags m_damageOCLTypes; // +0x48C
	BoneOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x490
	DamageTypeFlags m_damageParticleTypes; // +0x910
	BoneParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x914
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class BoneFXUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	const BoneFXUpdateModuleData *getBoneFXUpdateModuleData() const
	{
		return (const BoneFXUpdateModuleData *)m_moduleData;
	}

	// Primary vtable slots 1..12 (slot 0 is BehaviorModuleBase's).
	virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
	virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08();
	virtual void p09(); virtual void p10(); virtual void p11(); virtual void p12();
	virtual void resolveBoneLocations(); // slot 13

	void initTimes();
	void doFXListAtBone(const FXList *fxList, const Coord3D *bonePosition);
	void doOCLAtBone(const ObjectCreationList *ocl, const Coord3D *bonePosition);
	void doParticleSystemAtBone(const ParticleSystemTemplate *particleSystemTemplate, const Coord3D *bonePosition);
	void computeNextClientFXTime(const BaseBoneListInfo *info, Int &nextFrame);
	void computeNextLogicFXTime(const BaseBoneListInfo *info, Int &nextFrame);

private:
	_STL::vector<ParticleSystemID> m_particleSystemIDs; // +0x20
	Int m_nextFXFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x2C
	Int m_nextOCLFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0xAC
	Int m_nextParticleSystemFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x12C
	Coord3D m_FXBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x1AC
	Coord3D m_OCLBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x32C
	Coord3D m_PSBonePositions[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES]; // +0x4AC
	BodyDamageType m_curBodyState; // +0x62C
	Bool m_bonesResolved[BODYDAMAGETYPE_COUNT]; // +0x630
	Bool m_active; // +0x634
};

// ?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x00487DEE 332B
UpdateSleepTime BoneFXUpdate::update( void )
{
/// @todo srj use SLEEPY_UPDATE here
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	Int now = TheGameLogic->getFrame();

	if (m_active == FALSE) {
		initTimes();
		m_active = TRUE;
	}

	for (Int i = 0; i < BONE_FX_MAX_BONES; ++i) {
		//Check to see if its time to fire off any cool stuff.
		if ((m_nextFXFrame[m_curBodyState][i] != -1) && (m_nextFXFrame[m_curBodyState][i] <= now)) {
			doFXListAtBone(d->m_fxList[m_curBodyState][i].fx, &(m_FXBonePositions[m_curBodyState][i]));
			computeNextLogicFXTime(&(d->m_fxList[m_curBodyState][i]), m_nextFXFrame[m_curBodyState][i]);
		}
		if ((m_nextOCLFrame[m_curBodyState][i] != -1) && (m_nextOCLFrame[m_curBodyState][i] <= now)) {
			doOCLAtBone(d->m_OCL[m_curBodyState][i].ocl, &(m_OCLBonePositions[m_curBodyState][i]));
			computeNextLogicFXTime(&(d->m_OCL[m_curBodyState][i]), m_nextOCLFrame[m_curBodyState][i]);
		}
		if ((m_nextParticleSystemFrame[m_curBodyState][i] != -1) && (m_nextParticleSystemFrame[m_curBodyState][i] <= now)) {
			doParticleSystemAtBone(d->m_particleSystem[m_curBodyState][i].particleSysTemplate, &(m_PSBonePositions[m_curBodyState][i]));
			computeNextClientFXTime(&(d->m_particleSystem[m_curBodyState][i]), m_nextParticleSystemFrame[m_curBodyState][i]);
		}
	}
	return UPDATE_SLEEP_NONE;
}

// ?doFXListAtBone@BoneFXUpdate@@IAEXPBVFXList@@PBUCoord3D@@@Z @0x0048740D 115B
void BoneFXUpdate::doFXListAtBone(const FXList *fxList, const Coord3D *bonePosition)
{
	if (m_bonesResolved[m_curBodyState] == FALSE) {
		resolveBoneLocations();
	}

	// if we are restricted by the damage type executing effect, bail out of here
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	if( lastDamageInfo && getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) == FALSE )
		return;

	// the bonePosition variable will have been made right by the call to
	// resolveBoneLocations.  Either that or it was correct to begin with.
	Object *building = getObject();

	// Convert the bone's position relative to the origin of the building to the current
	// bone position in the world.
	Coord3D newPos;
	building->convertBonePosToWorldPos(bonePosition, NULL, &newPos, NULL);

	// execute the fx list at the calculated bone position.
	FXList::doFXPos(fxList, &newPos, NULL);
}

// ?doOCLAtBone@BoneFXUpdate@@IAEXPBVObjectCreationList@@PBUCoord3D@@@Z @0x00487480 116B
void BoneFXUpdate::doOCLAtBone(const ObjectCreationList *ocl, const Coord3D *bonePosition)
{
	if (m_bonesResolved[m_curBodyState] == FALSE) {
		resolveBoneLocations();
	}

	// if we are restricted by the damage type executing effect, bail out of here
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	if( lastDamageInfo && getDamageTypeFlag( d->m_damageOCLTypes, lastDamageInfo->in.m_damageType ) == FALSE )
		return;

	// the bonePosition variable will have been made right by the call to
	// resolveBoneLocations.  Either that or it was correct to begin with.
	Object *building = getObject();

	Coord3D newPos;
	building->convertBonePosToWorldPos(bonePosition, NULL, &newPos, NULL);

	ObjectCreationList::create( ocl, building, &newPos, NULL );

}

// ?doParticleSystemAtBone@BoneFXUpdate@@IAEXPBVParticleSystemTemplate@@PBUCoord3D@@@Z @0x00487B7D 248B
void BoneFXUpdate::doParticleSystemAtBone(const ParticleSystemTemplate *particleSystemTemplate, const Coord3D *bonePosition)
{
	if (m_bonesResolved[m_curBodyState] == FALSE) {
		resolveBoneLocations();
	}

	// if we are restricted by the damage type executing effect, bail out of here
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	if( lastDamageInfo && getDamageTypeFlag( d->m_damageParticleTypes, lastDamageInfo->in.m_damageType ) == FALSE )
		return;

	Object *building = getObject();

	BfmeParticleSystemHandle psys = TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
	if (psys)
	{
		m_particleSystemIDs.push_back(psys->getSystemID());
		psys->setPosition(bonePosition);
		psys->attachToObject(building);
		Drawable *drawable = building->getDrawable();
		if (drawable && drawable->isDrawableEffectivelyHidden())
		{
			psys->stop();
		}
	}
}
