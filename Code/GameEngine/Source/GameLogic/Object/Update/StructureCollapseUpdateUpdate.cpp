// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?getCollapseHeight@StructureCollapseUpdate@@IBEMXZ, retail 0x004A438B, 94 bytes.
// ?update@StructureCollapseUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004A46BF, 1011 bytes.
// ?beginStructureCollapse@StructureCollapseUpdate@@IAEXPBVDamageInfo@@@Z, retail 0x004A459B, 211 bytes.
//
// update: the Zero Hour StructureCollapseUpdate::update (reference
// CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/
// Update/StructureCollapseUpdate.cpp), with the BFME 2 changes measured from
// retail:
// - the standing state returns UPDATE_SLEEP_FOREVER without the debug crash;
// - the collapsing state no longer shudders the instance matrix: it moves the
//   object itself to the collapse origin cached at +0x38 (written by
//   beginStructureCollapse, as BFME 1 does) plus a logic-random shudder and
//   the current height, through Thing::setPosition (0x0030AA80);
// - the end of the collapse is tested against the collapse height getter
//   below, and a new ALMOST_FINAL phase fires below 70% of it (the BFME 2
//   phase names table 0x00DCBC8C reads INITIAL, DELAY, BURST, ALMOST_FINAL,
//   FINAL);
// - the done state calls the BFME 2 doCollapseDoneStuff (0x004A44B1, rowed
//   under its address name; it also destroys the object when the module data
//   says so), clears model conditions 0x43, 0x44, 0x45 and 5 through the
//   pinned Object mask clear 0x001E42F2 and sets condition 59 (+0x110 bit 27,
//   POST_RUBBLE in the model condition names table 0x00DBAA98)
//   with the rowed notifier 0x0028AE6D, and its matrix reset passes
//   preservePrevious true to the two-argument setInstanceMatrix (0x002711C6).
// The random calls carry the retail file string 0x00C52680 and its line
// numbers (0xCA, 0xD8, 0xEE, 0xF7, 0x100), reproduced with #line as
// StructureCollapseUpdate.cpp does for its own call.
//
// beginStructureCollapse: Zero Hour's, with two BFME 2 changes. It caches the
// object's position at +0x38 before the collapse-delay roll (module data
// +0x38/+0x3C, line 141). And when the object carries model condition 334
// (DESTROYED_WHILST_BEING_CONSTRUCTED in the names table, tested through the
// Object bit test 0x0006F039 under its pinned address name) the collapse
// starts already sunk: the current height becomes minus the collapse height
// times the unbuilt fraction (1 - construction percent at Object+0x280 *
// 0.01), and the object is moved there through the rowed two-argument Object
// position call 0x0029660C. It ends with UpdateModule::setWakeFrame
// (0x0044DF71). Its caller is the rowed onDie (0x004A466E).
//
// getCollapseHeight: the collapse depth; BFME 1 has the same-name getter
// (game/GameEngine/Source/GameLogic/Object/Update/
// StructureCollapseGetCollapseHeight.cpp) as a plain maximum. BFME 2's module
// data (parse table 0x00C52790) adds DestroyObjectWhenDone (+0xF4) and
// CollapseHeight (+0xF8): the template geometry's height only raises the
// depth when the object is destroyed at the end. The name is donor naming.
//
// `this` of update is the UpdateModuleInterface at +0x10 (the module data is
// at this-0xC and the object at this-8); the DieModuleInterface is at +0x20.

#include "matrix3d.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

#define GameClientRandomValueReal(lo, hi) GetGameClientRandomValueReal((lo), (hi), __FILE__, __LINE__)
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), __FILE__, __LINE__)
#define GameLogicRandomValueReal(lo, hi) GetGameLogicRandomValueReal((lo), (hi), __FILE__, __LINE__)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum StructureCollapsePhaseType
{
	SCPHASE_INITIAL = 0,
	SCPHASE_DELAY,
	SCPHASE_BURST,
	SCPHASE_ALMOST_FINAL,
	SCPHASE_FINAL,

	SC_PHASE_COUNT
};

enum StructureCollapseStateType
{
	COLLAPSESTATE_STANDING = 0,
	COLLAPSESTATE_WAITINGFORCOLLAPSESTART,
	COLLAPSESTATE_COLLAPSING,
	COLLAPSESTATE_DONE
};

enum ModelConditionFlagType
{
	MODELCONDITION_POST_RUBBLE = 1 * 32 + 27,
	MODELCONDITION_DESTROYED_WHILST_BEING_CONSTRUCTED = 334
};

// The 0x4C-byte model condition mask with four bits set (0x0028F5C6).
struct Rva0028F5C6
{
	Rva0028F5C6(Int unused, Int b1, Int b2, Int b3, Int b4);

	UnsignedInt m_bits[19];
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class ThingTemplate
{
public:
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }

private:
	unsigned char m_pad000[0xA0];
	GeometryInfo m_geometryInfo; // +0xA0
};

class Drawable
{
public:
	const Matrix3D *getInstanceMatrix() const { return &m_instance; }
	void setInstanceMatrix(const Matrix3D *instance, Bool preservePrevious);

private:
	unsigned char m_pad000[0x1A0];
	Matrix3D m_instance; // +0x1A0
};

class BodyModuleInterface
{
public:
#define BODY_SLOT(n) virtual void slot##n();
	BODY_SLOT(00) BODY_SLOT(01) BODY_SLOT(02) BODY_SLOT(03) BODY_SLOT(04)
	BODY_SLOT(05) BODY_SLOT(06) BODY_SLOT(07) BODY_SLOT(08) BODY_SLOT(09)
#undef BODY_SLOT
	virtual void updateBodyParticleSystems(); // slot 0x28
};

class ModelConditionFlags
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}

private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	Drawable *getDrawable() const;

private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	Coord3D m_cachedPos; // +0x38
	Real m_cachedAngle; // +0x44
};

class Object : public Thing
{
public:
	void rva001E42F2(const int *clear);
	void rva0028AE6D();
	Bool rva0006F039(Int bit) const;
	void teleportTo(const Coord3D *pos, Bool preserve);

	Bool testModelConditionFlag(ModelConditionFlagType mc) const { return rva0006F039(mc); }
	Real getConstructionPercent() const { return m_constructionPercent; }

	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}

	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	unsigned char m_pad048[0x10C - 0x48];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
	unsigned char m_pad258[0x280 - 0x258];
	Real m_constructionPercent; // +0x280
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad000[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char m_pad000[0xC4];
	Real m_gravity; // +0xC4
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class ModuleData;
class DamageInfo;

class StructureCollapseUpdateModuleData
{
public:
	unsigned char m_pad000[0x38];
	UnsignedInt m_minCollapseDelay; // +0x38
	UnsignedInt m_maxCollapseDelay; // +0x3C
	UnsignedInt m_minBurstDelay; // +0x40
	UnsignedInt m_maxBurstDelay; // +0x44
	Int m_bigBurstFrequency; // +0x48
	Real m_collapseDamping; // +0x4C
	Real m_maxShudder; // +0x50
	unsigned char m_pad054[0xF4 - 0x54];
	Bool m_destroyObjectWhenDone; // +0xF4
	Real m_collapseHeight; // +0xF8
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
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

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

// BFME 2's doCollapseDoneStuff, rowed under its address name.
class Rva004A44B1
{
public:
	void rva004A44B1();
};

class StructureCollapseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	void beginStructureCollapse(const DamageInfo *damageInfo);
	Real getCollapseHeight() const;
	void doPhaseStuff(StructureCollapsePhaseType scphase, const Coord3D *target);
	void doCollapseDoneStuff() { ((Rva004A44B1 *)this)->rva004A44B1(); }

	const StructureCollapseUpdateModuleData *getStructureCollapseUpdateModuleData() const
	{
		return (const StructureCollapseUpdateModuleData *)getModuleData();
	}

private:
	UnsignedInt m_collapseFrame; // +0x24
	UnsignedInt m_burstFrame; // +0x28
	StructureCollapseStateType m_collapseState; // +0x2C
	Real m_collapseVelocity; // +0x30
	Real m_currentHeight; // +0x34
	Coord3D m_collapsePosition; // +0x38
};

// ?getCollapseHeight@StructureCollapseUpdate@@IBEMXZ
Real StructureCollapseUpdate::getCollapseHeight() const
{
	const StructureCollapseUpdateModuleData *d = getStructureCollapseUpdateModuleData();
	if (d->m_destroyObjectWhenDone)
		return max(d->m_collapseHeight, getObject()->getTemplate()->getTemplateGeometryInfo().getMaxHeightAbovePosition());
	return d->m_collapseHeight;
}

// ?update@StructureCollapseUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime StructureCollapseUpdate::update( void )
{
	const StructureCollapseUpdateModuleData *d = getStructureCollapseUpdateModuleData();

	if (m_collapseState == COLLAPSESTATE_STANDING)
	{
		return UPDATE_SLEEP_FOREVER;
	}

	// We are in the dramatic pause between when the building has lost all its hit points and
	// when it starts toppling over.
	if (m_collapseState == COLLAPSESTATE_WAITINGFORCOLLAPSESTART)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		Object *building = getObject();

		const Coord3D *currentPosition = building->getPosition();
		Vector3 shudder;
#line 202 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\StructureCollapseUpdate.cpp"
		shudder.Set(GameClientRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), GameClientRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), 0);

		const Matrix3D *instMatrix = building->getDrawable()->getInstanceMatrix();
		Matrix3D newInstMatrix;
		newInstMatrix = *instMatrix;
		newInstMatrix.Set_Translation(shudder);

		building->getDrawable()->setInstanceMatrix(&newInstMatrix, true);

		if (now >= m_collapseFrame)
		{
			m_collapseState = COLLAPSESTATE_COLLAPSING;
			doPhaseStuff(SCPHASE_BURST, currentPosition);
			// This has to use a game logic random value since the bursts can spawn debris, and debris is sync'd.
#line 216
			m_burstFrame = now + GameLogicRandomValue(d->m_minBurstDelay, d->m_maxBurstDelay);
		}
	}

	// The building is in the process of falling over.
	if (m_collapseState == COLLAPSESTATE_COLLAPSING)
	{
		Object *building = getObject();
		UnsignedInt now = TheGameLogic->getFrame();
		m_currentHeight -= m_collapseVelocity;
		m_collapseVelocity -= TheGlobalData->m_gravity * (1.0 - d->m_collapseDamping);

		Vector3 shudder;
#line 238
		shudder.Set(GameLogicRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), GameLogicRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), m_currentHeight);

		Coord3D newPos;
		newPos.x = m_collapsePosition.x + shudder.X;
		newPos.y = m_collapsePosition.y + shudder.Y;
		newPos.z = m_collapsePosition.z + shudder.Z;
		building->setPosition(&newPos);

		if (now >= m_burstFrame)
		{
#line 247
			if (GameLogicRandomValue(1, d->m_bigBurstFrequency) == 1)
			{
				doPhaseStuff(SCPHASE_BURST, building->getPosition());
			}
			else
			{
				doPhaseStuff(SCPHASE_DELAY, building->getPosition());
			}
			// This has to use a game logic random value since the bursts can spawn debris, and debris is sync'd.
#line 256
			m_burstFrame += GameLogicRandomValue(d->m_minBurstDelay, d->m_maxBurstDelay);
		}

		Real collapseHeight = getCollapseHeight();
		if ((m_currentHeight + collapseHeight) <= 0)
		{
			m_collapseState = COLLAPSESTATE_DONE;
			doPhaseStuff(SCPHASE_FINAL, building->getPosition());
			Drawable *drawable = building->getDrawable();

			doCollapseDoneStuff();

			building->rva001E42F2((const int *)&Rva0028F5C6(0, 0x43, 0x44, 0x45, 5));
			building->setModelConditionState(MODELCONDITION_POST_RUBBLE);
			building->setOrientation(building->getOrientation());

			// Need to update body particle systems, now
			BodyModuleInterface *body = building->getBodyModule();
			body->updateBodyParticleSystems();

			Vector3 shudder;
			shudder.Set(0, 0, 0);
			const Matrix3D *instMatrix = building->getDrawable()->getInstanceMatrix();
			Matrix3D newInstMatrix;
			newInstMatrix = *instMatrix;
			newInstMatrix.Set_Translation(shudder);
			drawable->setInstanceMatrix(&newInstMatrix, true);

			return UPDATE_SLEEP_FOREVER;
		}
		else if ((m_currentHeight + collapseHeight * 0.7f) <= 0)
		{
			doPhaseStuff(SCPHASE_ALMOST_FINAL, building->getPosition());

			BodyModuleInterface *body = building->getBodyModule();
			body->updateBodyParticleSystems();
		}
	}

	return UPDATE_SLEEP_NONE;
}

// ?beginStructureCollapse@StructureCollapseUpdate@@IAEXPBVDamageInfo@@@Z
void StructureCollapseUpdate::beginStructureCollapse(const DamageInfo *damageInfo)
{
	const StructureCollapseUpdateModuleData *d = getStructureCollapseUpdateModuleData();

	Object *building = getObject();
	m_collapsePosition = *building->getPosition();
	UnsignedInt now = TheGameLogic->getFrame();
	// This has to use a game logic random value since the bursts can spawn debris, and debris is sync'd.
#line 141 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\StructureCollapseUpdate.cpp"
	m_collapseFrame = now + GameLogicRandomValue(d->m_minCollapseDelay, d->m_maxCollapseDelay);

	doPhaseStuff(SCPHASE_INITIAL, building->getPosition());

	m_collapseState = COLLAPSESTATE_WAITINGFORCOLLAPSESTART;
	m_currentHeight = 0.0f;

	if (building->testModelConditionFlag(MODELCONDITION_DESTROYED_WHILST_BEING_CONSTRUCTED))
	{
		// Only the unbuilt part is left to collapse.
		Real percent = building->getConstructionPercent();
		m_currentHeight = -(getCollapseHeight() * (1.0f - percent * 0.01f));

		Coord3D pos;
		const Coord3D *base = &m_collapsePosition;
		pos.x = base->x;
		pos.y = base->y;
		pos.z = base->z + m_currentHeight;
		building->teleportTo(&pos, false);
	}

	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
