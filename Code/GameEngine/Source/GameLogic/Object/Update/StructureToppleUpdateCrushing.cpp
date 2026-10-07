// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/shims/bfme2_ascii /GX
//
// ?rva004A54CE@@YAXHHQAH@Z, retail 0x004A54CE, 67 bytes.
// ?doPhaseStuff@StructureToppleUpdate@@IAEXW4StructureTopplePhaseType@@PBUCoord3D@@@Z, retail 0x004A584B, 114 bytes.
// ?doDamageLine@StructureToppleUpdate@@IAEXPAVObject@@PBVWeaponTemplate@@MMMM@Z, retail 0x004A5947, 450 bytes.
// ?applyCrushingDamage@StructureToppleUpdate@@IAEXM@Z, retail 0x004A5EAC, 406 bytes.
// ?doToppleStartFX@StructureToppleUpdate@@IAEXPAVObject@@PBVDamageInfo@@@Z, retail 0x004A5B09, 88 bytes.
// ?doAngleFX@StructureToppleUpdate@@IAEXMM@Z, retail 0x004A57DB, 112 bytes.
// ?doToppleDelayBurstFX@StructureToppleUpdate@@IAEXXZ, retail 0x004A5B61, 299 bytes.
// ?doToppleDoneStuff@StructureToppleUpdate@@IAEXXZ, retail 0x004A5628, 435 bytes.
// ?update@StructureToppleUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004A6042, 1065 bytes.
//
// Donor: Zero Hour's StructureToppleUpdate.cpp through BFME 1's matched
// bodies (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/
// Update/StructureToppleUpdate.cpp and StructureToppleUpdate_doDamageLine.cpp).
// Target facts:
// - 0x004A54CE is StructureToppleUpdate.cpp's static copy of
//   buildNonDupRandomIndexList: its GetGameLogicRandomValue call pushes the
//   StructureToppleUpdate.cpp file string 0x00C52A60 and line 536, and only
//   doPhaseStuff calls it. As in RubbleRiseUpdate.cpp the name stays with
//   StructureCollapseUpdate's copy and this one keeps its address name.
// - doPhaseStuff has only the OCL half: the per-phase OCL vectors sit at
//   module data +0x70 and their counts at +0x94 (three phases).
// - doDamageLine calls it with phase 2 (FINAL). It reads the last damage info
//   through the body module at Object+0x254 (vslot 0x3C) and tests its type
//   (+0x10) against the module data's FX-type bits at +0x4C before firing the
//   crushing FX at +0x60 through the static FXList::doFXPos with no null
//   check. The ground height is TheTerrainLogic's vslot 0x18.
// - applyCrushingDamage is called by the update with the building's angle to
//   the ground. It reads the orientation at Object+0x44, the geometry's major
//   and minor radii at Object+0xCC/+0xD0, the crushing weapon name at module
//   data +0x64, m_toppleDirection at +0x28, m_lastCrushedLocation at +0x40 and
//   m_buildingHeight at +0x54. Coord2D::toAngle (0x00005923) and
//   Coord3D::length (0x00003571) are the rowed out-of-line bodies.
// - doToppleStartFX and doAngleFX were rowed under address names
//   (Rva004A5B09, Rva004A54A8). They are Zero Hour's bodies unchanged: the
//   start FX list at module data +0x50, and the AngleFXInfo vector (angle,
//   FX list) at +0xAC, whose FX fire for each angle the update's step
//   (0x004A613B) passes.
// - doToppleDelayBurstFX is the call the update makes whenever the frame
//   reaches m_nextBurstFrame (+0x44) before re-rolling it, as in Zero Hour.
//   It fires the delay FX at +0x54 on m_delayBurstLocation (+0x48), then
//   walks the FXBoneInfo vector at +0xA0 (bone name, particle template):
//   BFME 2's createParticleSystem (0x001F5A6A) returns the 12-byte
//   BfmeParticleSystemHandle, whose dtor guard and null-system operator->
//   (Make001FCBD7) are the same as in SlavedUpdateRepair.cpp, and the
//   object's getDrawable is the pinned 0x005508E2. Its unwind is why the unit
//   builds with /GX.
// - doToppleDoneStuff is Zero Hour's: the static BoneFXUpdate name key
//   (string 0x00BF4FA8) through the NameKeyGenerator body at 0x00148E1A,
//   Object::findModule (0x0028B6D6), BoneFXUpdate::stopAllBoneFX
//   (0x00487A95), Thing::setOrientation (0x0030AB9D) and the Object
//   setTransformMatrix override pinned at 0x0028D412.
// - update is Zero Hour's with BFME 2's changes: no crash on the standing
//   state, the burst delay re-roll is a logic random (file string 0x00C52A60,
//   lines 230 and 279) and the topple acceleration factor is module data
//   +0x48 instead of a constant. While toppling it calls Thing's
//   setTransformMatrix (0x0030A2B7) directly, not the Object override.
//   Once flat it clears model-condition bit 5 and sets bit 60 through
//   Object's notifier 0x0028AE6D (Zero Hour's RUBBLE and POST_COLLAPSE on
//   the drawable) and calls the body module's slot 0x28, Zero Hour's
//   updateBodyParticleSystems.

#include "matrix3d.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define PI 3.14159265359f

Real Sin(Real x);
Real Cos(Real x);

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), __FILE__, __LINE__)

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line length (rowed 0x00003571) that applyCrushingDamage calls; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
};

// class-gate: allow Coord2D the canonical data-only header cannot declare BFME 2's out-of-line toAngle (rowed 0x00005923) that applyCrushingDamage calls; same two floats
class Coord2D
{
public:
	Real x;
	Real y;

	Real toAngle() const;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum StructureTopplePhaseType
{
	STPHASE_INITIAL = 0,
	STPHASE_DELAY,
	STPHASE_FINAL,

	ST_PHASE_COUNT
};

enum StructureToppleStateType
{
	TOPPLESTATE_STANDING = 0,
	TOPPLESTATE_WAITINGFORTOPPLESTART,
	TOPPLESTATE_TOPPLING,
	TOPPLESTATE_WAITINGFORDONE,
	TOPPLESTATE_DONE
};

enum
{
	MAX_IDX = 32
};

class Matrix3D;
class WeaponTemplate;
class Drawable;

class Object;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0, Real primarySpeed = 0.0f, const Coord3D *secondary = 0);
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = 0);
};

class Object;

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *tertiary, Int lifetimeFrames);
};

template <class T> class PhaseList
{
public:
	Int size() const { return m_finish - m_start; }
	const T *operator[](Int i) const { return m_start[i]; }

private:
	const T **m_start;
	const T **m_finish;
	const T **m_endOfStorage;
};

typedef PhaseList<ObjectCreationList> OCLVec;

struct FXBoneInfo
{
	AsciiString boneName;
	const class ParticleSystemTemplate *particleSystemTemplate;
};

struct AngleFXInfo
{
	Real angle;
	const FXList *fxList;
};

template <class T> class ConstVector
{
public:
	typedef const T *const_iterator;
	const_iterator begin() const { return m_start; }
	const_iterator end() const { return m_finish; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

Bool inList(Int value, Int count, const Int idxList[]);

class DamageInfoInput
{
public:
	unsigned char m_pad00[0x10];
	Int m_damageType; // +0x10
};

class DamageInfo
{
public:
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void updateBodyParticleSystems();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getMinorRadius() const { return m_minorRadius; }

private:
	Real m_majorRadius; // Object+0xCC
	Real m_minorRadius; // Object+0xD0
};

class Module;

// Zero Hour clears RUBBLE and sets POST_COLLAPSE once the building lies flat;
// BFME 2's bits for them are 5 and 60.
enum ModelConditionFlagType
{
	MODELCONDITION_RUBBLE = 5,
	MODELCONDITION_POST_COLLAPSE = 60
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	void setOrientation(Real angle);
	void setTransformMatrix(const Matrix3D *mx);

private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform; // +0x08
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
};

class Object : public Thing
{
public:
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Drawable *getDrawable() const;
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	void setTransformMatrix(const Matrix3D *mx);
	void rva0028AE6D();
	__forceinline void setModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) == 0)
		{
			m_modelConditionFlags.set(flag);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) != 0)
		{
			m_modelConditionFlags.clear(flag);
			rva0028AE6D();
		}
	}

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad048[0xCC - 0x48];
	GeometryInfo m_geometryInfo; // +0xCC
	unsigned char m_pad0d4[0x10C - 0xD4];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
};

// The particle system's position copy (0x001F3899) and attachToDrawable
// (0x001F3C20) are rowed under placeholder names.
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
class Rva0055A88BDwordField;
class Rva001F3C20Slot
{
public:
	void set(const Rva0055A88BDwordField *arg);
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToDrawable(const Drawable *draw)
	{
		((Rva001F3C20Slot *)this)->set((const Rva0055A88BDwordField *)draw);
	}
};
ParticleSystem *Make001FCBD7();

// The 12-byte handle: the out-of-line unlink is 0x0004CBC0, which the
// handle's destructor calls only for a live system.
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

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones, Int unused) const;
};

class BoneFXUpdate
{
public:
	void stopAllBoneFX();
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

extern TerrainLogic *TheTerrainLogic;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

inline Bool getDamageTypeFlag(UnsignedInt flags, Int damageType)
{
	return (flags & (1 << (damageType - 1))) != 0;
}

class ModuleData;

class StructureToppleUpdateModuleData
{
public:
	unsigned char m_pad000[0x40];
	Real m_structuralIntegrity; // +0x40
	Real m_structuralDecay; // +0x44
	Real m_toppleAccelerationFactor; // +0x48, a constant in Zero Hour
	UnsignedInt m_damageFXTypes; // +0x4C
	const FXList *m_toppleStartFXList; // +0x50
	const FXList *m_toppleDelayFXList; // +0x54
	unsigned char m_pad058[0x5C - 0x58];
	const FXList *m_toppleDoneFXList; // +0x5C
	const FXList *m_crushingFXList; // +0x60
	AsciiString m_crushingWeaponName; // +0x64
	Int m_minToppleBurstDelay; // +0x68
	Int m_maxToppleBurstDelay; // +0x6C
	OCLVec m_ocls[ST_PHASE_COUNT]; // +0x70
	Int m_oclCount[ST_PHASE_COUNT]; // +0x94
	ConstVector<FXBoneInfo> fxbones; // +0xA0
	ConstVector<AngleFXInfo> angleFX; // +0xAC
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceSlot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved; // +0x1C
};

class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceSlot();
};

class StructureToppleUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	void applyCrushingDamage(Real theta);
	void doToppleStartFX(Object *building, const DamageInfo *damageInfo);
	void doAngleFX(Real curAngle, Real newAngle);
	void doToppleDelayBurstFX();
	void doToppleDoneStuff();
	void doDamageLine(Object *building, const WeaponTemplate *wt, Real jcos, Real jsin, Real facingWidth, Real toppleAngle);
	void doPhaseStuff(StructureTopplePhaseType stphase, const Coord3D *target);

	const StructureToppleUpdateModuleData *getStructureToppleUpdateModuleData() const
	{
		return (const StructureToppleUpdateModuleData *)getModuleData();
	}

	UnsignedInt m_toppleFrame; // +0x24
	Coord2D m_toppleDirection; // +0x28
	StructureToppleStateType m_toppleState; // +0x30
	Real m_toppleVelocity; // +0x34
	Real m_accumulatedAngle; // +0x38
	Real m_structuralIntegrity; // +0x3C
	Real m_lastCrushedLocation; // +0x40
	UnsignedInt m_nextBurstFrame; // +0x44
	Coord3D m_delayBurstLocation; // +0x48
	Real m_buildingHeight; // +0x54
};

// ?rva004A54CE@@YAXHHQAH@Z
static void rva004A54CE(Int range, Int count, Int idxList[])
{
	for (Int i = 0; i < count; ++i)
	{
		Int idx;
		do
		{
#line 536 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			idx = GameLogicRandomValue(0, range-1);
		}
		while (inList(idx, i, idxList));
		idxList[i] = idx;
	}
}

// ?applyCrushingDamage@StructureToppleUpdate@@IAEXM@Z
// theta is the angle of the building with respect to the ground.
void StructureToppleUpdate::applyCrushingDamage(Real theta)
{
	static const Real THETA_CEILING = PI/6; // This weapon won't do any damage until theta is less than this value.
	static const Real WEAPON_SPACING_PERPENDICULAR = 25;	// The spacing between weapon firing locations,
																												// distance is perpendicular to the direction the
																												// building is falling in.

	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	if (theta > THETA_CEILING) {
		return;
	}

	Object *building = getObject();
	Real orientationAngle = building->getOrientation();
	Real toppleAngle = m_toppleDirection.toAngle();

	// Figure out the width of the projection of the boundary of the building along the topple direction.
	// Do this because the amount of ground that is affected will be different if the building falls
	// in different orientations.
	Real angle = orientationAngle - toppleAngle;
	Real minorComponent = building->getGeometryInfo().getMinorRadius() * Cos(angle);
	Real majorComponent = building->getGeometryInfo().getMajorRadius() * Sin(angle);

	Coord3D temp3D;
	temp3D.x = majorComponent;
	temp3D.y = minorComponent;
	temp3D.z = 0.0f;

	Real facingWidth = temp3D.length() / 2;

	// Get the crushing weapon.
	const WeaponTemplate* wt = TheWeaponStore->findWeaponTemplate(d->m_crushingWeaponName);
	if (wt == 0) {
		return;
	}

	// The furthest away from the base of the building to explode on.
	Real maxDistance = m_buildingHeight * (1.0 - Sin(theta));

	/*
	 * Fire explosions at regular intervals across the area that the building is currently
	 * crushing.  The explosions occur across the face and along the length of the building.
	 */
	Real j;
	Real jcos, jsin;
	for (j = m_lastCrushedLocation; j < maxDistance; j += WEAPON_SPACING_PERPENDICULAR) {
		jcos = j * Cos(toppleAngle);
		jsin = j * Sin(toppleAngle);
		doDamageLine(building, wt, jcos, jsin, facingWidth, toppleAngle);
	}

	jcos = maxDistance * Cos(toppleAngle);
	jsin = maxDistance * Sin(toppleAngle);
	doDamageLine(building, wt, jcos, jsin, facingWidth, toppleAngle);

	m_lastCrushedLocation = j;
}

// ?doDamageLine@StructureToppleUpdate@@IAEXPAVObject@@PBVWeaponTemplate@@MMMM@Z
void StructureToppleUpdate::doDamageLine(Object *building, const WeaponTemplate* wt, Real jcos, Real jsin, Real facingWidth, Real toppleAngle)
{
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	static const Real WEAPON_SPACING_PARALLEL = 25;				// The spacing between weapon firing locations,
																												// distance is parallel to the direction the building
																												// is falling in.

	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();

	Coord3D target;

	for (Real i = -facingWidth; i < facingWidth; i += WEAPON_SPACING_PARALLEL)
	{
		target.x = building->getPosition()->x + jcos + (i * Sin(toppleAngle));
		target.y = building->getPosition()->y + jsin + (i * Cos(toppleAngle));
		target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);

		TheWeaponStore->createAndFireTempWeapon(wt, building, &target);

		// do the crushing particle effects
		if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
			FXList::doFXPos(d->m_crushingFXList, &target);
	}

	// Make sure there are weapons fired and FX done on the edge of the building.
	target.x = building->getPosition()->x + jcos + (facingWidth * Sin(toppleAngle));
	target.y = building->getPosition()->y + jsin + (facingWidth * Cos(toppleAngle));
	target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);

	TheWeaponStore->createAndFireTempWeapon(wt, building, &target);

	// do the crushing particle effects
	if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
		FXList::doFXPos(d->m_crushingFXList, &target);

	// Do the flying debris for this line.
	target.x = building->getPosition()->x + jcos;
	target.y = building->getPosition()->y + jsin;
	target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);

	doPhaseStuff(STPHASE_FINAL, &target);
}

// ?doPhaseStuff@StructureToppleUpdate@@IAEXW4StructureTopplePhaseType@@PBUCoord3D@@@Z
void StructureToppleUpdate::doPhaseStuff(StructureTopplePhaseType stphase, const Coord3D *target)
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	Int i, idx, count, listSize;
	Int idxList[MAX_IDX];

	listSize = d->m_ocls[stphase].size();
	if (listSize > 0)
	{
		count = d->m_oclCount[stphase];
		rva004A54CE(listSize, count, idxList);
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const OCLVec& v = d->m_ocls[stphase];
			const ObjectCreationList* ocl = v[idx];
			if (ocl != 0)
				((ObjectCreationList *)ocl)->create(getObject(), (void *)target, 0, 0);
		}
	}
}

// ?doToppleStartFX@StructureToppleUpdate@@IAEXPAVObject@@PBVDamageInfo@@@Z
void StructureToppleUpdate::doToppleStartFX(Object *building, const DamageInfo *damageInfo)
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
		FXList::doFXPos(d->m_toppleStartFXList, building->getPosition());

	doPhaseStuff(STPHASE_INITIAL, building->getPosition());
}

// ?doAngleFX@StructureToppleUpdate@@IAEXMM@Z
void StructureToppleUpdate::doAngleFX(Real curAngle, Real newAngle)
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	for (ConstVector<AngleFXInfo>::const_iterator it = d->angleFX.begin(); it != d->angleFX.end(); ++it)
	{
		if ((it->angle > curAngle) && (it->angle <= newAngle))
		{
			if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
				FXList::doFXObj(it->fxList, getObject());
		}
	}

}

// ?doToppleDelayBurstFX@StructureToppleUpdate@@IAEXXZ
void StructureToppleUpdate::doToppleDelayBurstFX()
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
		FXList::doFXPos(d->m_toppleDelayFXList, &m_delayBurstLocation);

	Object *building = getObject();
	Drawable *drawable = building->getDrawable();

	if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
	{

		for (ConstVector<FXBoneInfo>::const_iterator it = d->fxbones.begin(); it != d->fxbones.end(); ++it)
		{
			BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(it->particleSystemTemplate, true);
			if (sys)
			{
				Coord3D pos;
				if (drawable->getPristineBonePositions(it->boneName.str(), 0, &pos, 0, 1, 0) == 1)
				{
					// got the bone position...
					sys->setPosition(&pos);

					// Attatch it to the object...
					sys->attachToDrawable(drawable);
				}
			}
		}
	}

	doPhaseStuff(STPHASE_DELAY, &m_delayBurstLocation);

}

// ?doToppleDoneStuff@StructureToppleUpdate@@IAEXXZ
void StructureToppleUpdate::doToppleDoneStuff()
{
	static NameKeyType key_BoneFXUpdate = NAMEKEY("BoneFXUpdate");
	BoneFXUpdate *bfxu = (BoneFXUpdate *)getObject()->findUpdateModule(key_BoneFXUpdate);
	if (bfxu != 0) {
		bfxu->stopAllBoneFX();
	}

	Object *building = getObject();

	Real origAngle = building->getOrientation();
	building->setOrientation(origAngle);

	Real toppleAngle = m_toppleDirection.toAngle();

	Matrix3D xfrm = *building->getTransformMatrix();
	xfrm.In_Place_Pre_Rotate_Z(toppleAngle-origAngle);
	building->setTransformMatrix(&xfrm);
}

// ?update@StructureToppleUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime StructureToppleUpdate::update( void )
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();

	if (m_toppleState == TOPPLESTATE_STANDING)
	{
		return UPDATE_SLEEP_FOREVER;
	}

	// get last damage info
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	// We are in the dramatic pause between when the building has lost all its hit points and
	// when it starts toppling over.
	if (m_toppleState == TOPPLESTATE_WAITINGFORTOPPLESTART) {
		UnsignedInt now = TheGameLogic->getFrame();
		if (now >= m_nextBurstFrame) {
			doToppleDelayBurstFX();
#line 230 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			m_nextBurstFrame = now + GameLogicRandomValue(d->m_minToppleBurstDelay, d->m_maxToppleBurstDelay);
		}

		if (now >= m_toppleFrame) {
			m_toppleState = TOPPLESTATE_TOPPLING;
			m_structuralIntegrity = d->m_structuralIntegrity;
		}
	}

	// The building is in the process of falling over.
	if (m_toppleState == TOPPLESTATE_TOPPLING) {
		UnsignedInt now = TheGameLogic->getFrame();
		Real toppleAcceleration = d->m_toppleAccelerationFactor * (Sin(m_accumulatedAngle) * (1.0 - m_structuralIntegrity));
		m_toppleVelocity += toppleAcceleration;

		// doesn't make sense to have a structural integrity less than zero.
		if (m_structuralIntegrity > 0.0f) {
			m_structuralIntegrity *= d->m_structuralDecay;
			if (m_structuralIntegrity < 0.0f) {
				m_structuralIntegrity = 0.0f;
			}
		}

		doAngleFX(m_accumulatedAngle, m_accumulatedAngle + m_toppleVelocity);

		m_accumulatedAngle += m_toppleVelocity;

		applyCrushingDamage(PI/2 - m_accumulatedAngle);

		if (m_accumulatedAngle >= PI/2) {
			m_toppleVelocity -= m_accumulatedAngle - PI/2;
			m_accumulatedAngle = PI/2;
			m_toppleState = TOPPLESTATE_WAITINGFORDONE;

			applyCrushingDamage(0.0f);
			doPhaseStuff(STPHASE_FINAL, getObject()->getPosition());

			if( lastDamageInfo == 0 || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
				FXList::doFXObj(d->m_toppleDoneFXList, getObject());

			m_toppleFrame = TheGameLogic->getFrame();
		}

		if (now >= m_nextBurstFrame) {
			doToppleDelayBurstFX();
#line 279 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			m_nextBurstFrame = now + GameLogicRandomValue(d->m_minToppleBurstDelay, d->m_maxToppleBurstDelay);
		}

		Object *building = getObject();
		Matrix3D xfrm = *building->getTransformMatrix();
		xfrm.In_Place_Pre_Rotate_X(-m_toppleVelocity * m_toppleDirection.y);
		xfrm.In_Place_Pre_Rotate_Y(m_toppleVelocity * m_toppleDirection.x);
		building->Thing::setTransformMatrix(&xfrm);
	}

	// The building is now flat on the ground and done with all the crushing and all that.
	if (m_toppleState == TOPPLESTATE_WAITINGFORDONE)
	{
		if (m_toppleFrame <= TheGameLogic->getFrame())
		{
			Object *building = getObject();
			building->clearModelConditionState(MODELCONDITION_RUBBLE);
			building->setModelConditionState(MODELCONDITION_POST_COLLAPSE);

			// Need to update body particle systems, now
			BodyModuleInterface *body = building->getBodyModule();
			body->updateBodyParticleSystems();

			doToppleDoneStuff();

			m_toppleState = TOPPLESTATE_DONE;

			return UPDATE_SLEEP_FOREVER;
		}
	}

	return UPDATE_SLEEP_NONE;
}
