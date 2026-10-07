// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/shims/bfme2_ascii
//
// ?rva004A54CE@@YAXHHQAH@Z, retail 0x004A54CE, 67 bytes.
// ?doPhaseStuff@StructureToppleUpdate@@IAEXW4StructureTopplePhaseType@@PBUCoord3D@@@Z, retail 0x004A584B, 114 bytes.
// ?doDamageLine@StructureToppleUpdate@@IAEXPAVObject@@PBVWeaponTemplate@@MMMM@Z, retail 0x004A5947, 450 bytes.
// ?applyCrushingDamage@StructureToppleUpdate@@IAEXM@Z, retail 0x004A5EAC, 406 bytes.
// ?doToppleStartFX@StructureToppleUpdate@@IAEXPAVObject@@PBVDamageInfo@@@Z, retail 0x004A5B09, 88 bytes.
// ?doAngleFX@StructureToppleUpdate@@IAEXMM@Z, retail 0x004A57DB, 112 bytes.
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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum StructureTopplePhaseType
{
	STPHASE_INITIAL = 0,
	STPHASE_DELAY,
	STPHASE_FINAL,

	ST_PHASE_COUNT
};

enum
{
	MAX_IDX = 32
};

class Matrix3D;
class WeaponTemplate;

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
	virtual void slot28();
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

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
	unsigned char m_pad048[0xCC - 0x48];
	GeometryInfo m_geometryInfo; // +0xCC
	unsigned char m_pad0d4[0x254 - 0xD4];
	BodyModuleInterface *m_body; // +0x254
};

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
	unsigned char m_pad000[0x4C];
	UnsignedInt m_damageFXTypes; // +0x4C
	const FXList *m_toppleStartFXList; // +0x50
	unsigned char m_pad054[0x60 - 0x54];
	const FXList *m_crushingFXList; // +0x60
	AsciiString m_crushingWeaponName; // +0x64
	unsigned char m_pad068[0x70 - 0x68];
	OCLVec m_ocls[ST_PHASE_COUNT]; // +0x70
	Int m_oclCount[ST_PHASE_COUNT]; // +0x94
	unsigned char m_pad0a0[0xAC - 0xA0];
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
	void doDamageLine(Object *building, const WeaponTemplate *wt, Real jcos, Real jsin, Real facingWidth, Real toppleAngle);
	void doPhaseStuff(StructureTopplePhaseType stphase, const Coord3D *target);

	const StructureToppleUpdateModuleData *getStructureToppleUpdateModuleData() const
	{
		return (const StructureToppleUpdateModuleData *)getModuleData();
	}

	UnsignedInt m_toppleFrame; // +0x24
	Coord2D m_toppleDirection; // +0x28
	Int m_toppleState; // +0x30
	Real m_toppleVelocity; // +0x34
	Real m_accumulatedAngle; // +0x38
	Real m_structuralIntegrity; // +0x3C
	Real m_lastCrushedLocation; // +0x40
	Int m_nextBurstFrame; // +0x44
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
