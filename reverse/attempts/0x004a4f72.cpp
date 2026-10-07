// ?update@RubbleRiseUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?rva004A4C3F@@YAXHHQAH@Z, retail 0x004A4C3F, 67 bytes.
// ?doPhaseStuff@RubbleRiseUpdate@@IAEXW4RubbleRisePhaseType@@PBUCoord3D@@@Z, retail 0x004A4E1E, 203 bytes.
// ?update@RubbleRiseUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004A4F72, 1101 bytes.
//
// Donor: BFME 1's matched RubbleRiseUpdate.cpp (buildNonDupRandomIndexList and
// doPhaseStuff) and RubbleRiseStep002A3B40.cpp (update), both under
// reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Update/.
// Target facts:
// - 0x004A4C3F is RubbleRiseUpdate.cpp's static copy of
//   buildNonDupRandomIndexList: its GetGameLogicRandomValue call pushes the
//   RubbleRiseUpdate.cpp file string 0x00C528A0 and line 272, and only
//   doPhaseStuff calls it. The ledger already gives the name to
//   StructureCollapseUpdate's copy (0x004A425C), so this one keeps its
//   address name. As a static it takes range in eax and the list in ebx,
//   which survives only next to its caller.
// - Module data (parse table 0x00C52960): burst delays +0x40/+0x44, big burst
//   frequency +0x48, damping +0x4C, maximum shudder +0x54; per-phase OCL and
//   FX lists at +0x58/+0x88 and their counts at +0xB8/+0xC8. The phase names
//   table 0x00DCBCE0 reads INITIAL, DELAY, BURST, FINAL.
// - Module state (ctor 0x004A4CC7): next burst frame +0x28, rise state +0x2C,
//   velocity +0x30, current height +0x34, rubble height +0x38, rise position
//   +0x3C. update's `this` is the UpdateModuleInterface at +0x10.
// - Object: model conditions at +0x10C (the rise starts on condition 59 and
//   ends by clearing it and setting 60, through the rowed notifier
//   0x0028AE6D), body module +0x254 with updateBodyParticleSystems in slot
//   0x28. The rubble height comes from TheTerrainLogic slot 0x1C with the
//   object's layer (rowed 0x0028B511).
// - The done call 0x004A4DBE is RubbleRiseUpdate's copy of the BoneFX stop;
//   the ledger rows it under StructureCollapseUpdate::doCollapseDoneStuff.
// The random calls carry the file string and the retail lines (0x9D, 0xAB,
// 0xC4, 0xCD, 0xD6) through #line.

#include "matrix3d.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

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

enum RubbleRisePhaseType
{
	RRPHASE_INITIAL = 0,
	RRPHASE_DELAY,
	RRPHASE_BURST,
	RRPHASE_FINAL,

	RR_PHASE_COUNT
};

enum RubbleRiseStateType
{
	RISESTATE_WAITING = 0,
	RISESTATE_RISING,
	RISESTATE_DONE
};

enum ModelConditionFlagType
{
	MODELCONDITION_RUBBLE_RISE_START = 1 * 32 + 27,
	MODELCONDITION_RUBBLE_RISE_DONE = 1 * 32 + 28
};

enum
{
	MAX_IDX = 32
};

class Object;
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary);
};

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

typedef PhaseList<FXList> FXVec;
typedef PhaseList<ObjectCreationList> OCLVec;

Bool inList(Int value, Int count, const Int idxList[]);

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
	Bool test(UnsignedInt bit) const
	{
		return ((m_words[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
	}
	UnsignedInt testMask(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(UnsignedInt bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}

private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	Drawable *getDrawable() const;

private:
	void *m_vptr;
	const void *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	Coord3D m_cachedPos; // +0x38
	Real m_cachedAngle; // +0x44
};

class Object : public Thing
{
public:
	Int rva0028B511() const;
	void rva0028AE6D();

	const ModelConditionFlags &getModelConditionFlags() const { return m_modelConditionFlags; }

	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.testMask(mc))
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.testMask(mc) == 0)
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

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(00) TERRAIN_SLOT(01) TERRAIN_SLOT(02) TERRAIN_SLOT(03)
	TERRAIN_SLOT(04) TERRAIN_SLOT(05) TERRAIN_SLOT(06)
#undef TERRAIN_SLOT
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal, Bool clip); // slot 0x1C
};
extern TerrainLogic *TheTerrainLogic;

class ModuleData;

class RubbleRiseUpdateModuleData
{
public:
	unsigned char m_pad000[0x40];
	UnsignedInt m_minBurstDelay; // +0x40
	UnsignedInt m_maxBurstDelay; // +0x44
	Int m_bigBurstFrequency; // +0x48
	Real m_rubbleRiseDamping; // +0x4C
	Real m_rubbleHeight; // +0x50
	Real m_maxShudder; // +0x54
	OCLVec m_ocls[RR_PHASE_COUNT]; // +0x58
	FXVec m_fxs[RR_PHASE_COUNT]; // +0x88
	Int m_oclCount[RR_PHASE_COUNT]; // +0xB8
	Int m_fxCount[RR_PHASE_COUNT]; // +0xC8
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

class RubbleRiseUpdate;

// 0x004A4DBE, rowed under this name (see above).
class StructureCollapseUpdate
{
	friend class RubbleRiseUpdate;

protected:
	void doCollapseDoneStuff();
};

class RubbleRiseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	void doPhaseStuff(RubbleRisePhaseType rrphase, const Coord3D *target);
	void doCollapseDoneStuff() { ((StructureCollapseUpdate *)this)->doCollapseDoneStuff(); }

	const RubbleRiseUpdateModuleData *getRubbleRiseUpdateModuleData() const
	{
		return (const RubbleRiseUpdateModuleData *)getModuleData();
	}

private:
	UnsignedInt m_unused24; // +0x24
	UnsignedInt m_nextBurstFrame; // +0x28
	RubbleRiseStateType m_riseState; // +0x2C
	Real m_riseVelocity; // +0x30
	Real m_currentHeight; // +0x34
	Real m_rubbleHeight; // +0x38
	Coord3D m_risePosition; // +0x3C
};

// ?rva004A4C3F@@YAXHHQAH@Z
static void rva004A4C3F(Int range, Int count, Int idxList[])
{
	for (Int i = 0; i < count; ++i)
	{
		Int idx;
		do
		{
#line 272 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\RubbleRiseUpdate.cpp"
			idx = GameLogicRandomValue(0, range-1);
		}
		while (inList(idx, i, idxList));
		idxList[i] = idx;
	}
}

// ?doPhaseStuff@RubbleRiseUpdate@@IAEXW4RubbleRisePhaseType@@PBUCoord3D@@@Z
void RubbleRiseUpdate::doPhaseStuff(RubbleRisePhaseType rrphase, const Coord3D *target)
{
	const RubbleRiseUpdateModuleData *d = getRubbleRiseUpdateModuleData();
	Int i, idx, count, listSize;
	Int idxList[MAX_IDX];

	listSize = d->m_fxs[rrphase].size();
	if (listSize > 0)
	{
		count = d->m_fxCount[rrphase];
		rva004A4C3F(listSize, count, idxList);
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const FXVec &v = d->m_fxs[rrphase];
			const FXList *fxl = v[idx];
			FXList::doFXPos(fxl, target, 0, 0.0f, 0);
		}
	}

	listSize = d->m_ocls[rrphase].size();
	if (listSize > 0)
	{
		count = d->m_oclCount[rrphase];
		rva004A4C3F(listSize, count, idxList);
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const OCLVec &v = d->m_ocls[rrphase];
			const ObjectCreationList *ocl = v[idx];
			if (ocl != 0)
				((ObjectCreationList *)ocl)->create(getObject(), (void *)target, 0, 0);
		}
	}
}

// ?update@RubbleRiseUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RubbleRiseUpdate::update()
{
	Object *obj = getObject();
	const RubbleRiseUpdateModuleData *d = getRubbleRiseUpdateModuleData();
	Drawable *drawable = obj->getDrawable();

	if (m_riseState == RISESTATE_WAITING && drawable && obj->getModelConditionFlags().test(MODELCONDITION_RUBBLE_RISE_START))
	{
		const Coord3D *pos = obj->getPosition();
		doPhaseStuff(RRPHASE_INITIAL, pos);
		m_riseState = RISESTATE_RISING;

		Vector3 shudder;
#line 157
		shudder.Set(GameClientRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), GameClientRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), 0);

		const Matrix3D *instMatrix = obj->getDrawable()->getInstanceMatrix();
		Matrix3D newInstMatrix;
		newInstMatrix = *instMatrix;
		newInstMatrix.Set_Translation(shudder);
		drawable->setInstanceMatrix(&newInstMatrix, true);

		m_riseState = RISESTATE_RISING;
		doPhaseStuff(RRPHASE_BURST, pos);

		UnsignedInt now = TheGameLogic->getFrame();
#line 171
		m_nextBurstFrame = now + GameLogicRandomValue(d->m_minBurstDelay, d->m_maxBurstDelay);
		m_riseVelocity = -TheGlobalData->m_gravity * (1.0 - d->m_rubbleRiseDamping) * 20.0;
		m_rubbleHeight = TheTerrainLogic->getLayerHeight(obj->getPosition()->x, obj->getPosition()->y, obj->rva0028B511(), 0, true);
		m_currentHeight = 0;
		m_risePosition = *pos;
	}

	if (m_riseState == RISESTATE_RISING && drawable)
	{
		UnsignedInt now = TheGameLogic->getFrame();

#line 196
		Vector3 shudder(GameLogicRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), GameLogicRandomValueReal(-(d->m_maxShudder), d->m_maxShudder), (m_currentHeight += m_riseVelocity));

		Coord3D newPos;
		newPos.x = shudder.X + m_risePosition.x;
		newPos.y = shudder.Y + m_risePosition.y;
		newPos.z = m_risePosition.z + shudder.Z;
		obj->setPosition(&newPos);

		if (now >= m_nextBurstFrame)
		{
#line 205
			if (GameLogicRandomValue(1, d->m_bigBurstFrequency) == 1)
			{
				doPhaseStuff(RRPHASE_BURST, obj->getPosition());
			}
			else
			{
				doPhaseStuff(RRPHASE_DELAY, obj->getPosition());
			}
#line 214
			m_nextBurstFrame += GameLogicRandomValue(d->m_minBurstDelay, d->m_maxBurstDelay);
		}

		if (m_currentHeight >= m_rubbleHeight - m_risePosition.z)
		{
			Coord3D finalPos;
			finalPos.x = m_risePosition.x;
			finalPos.y = m_risePosition.y;
			finalPos.z = m_rubbleHeight;
			obj->setPosition(&finalPos);
			m_riseState = RISESTATE_DONE;
			doPhaseStuff(RRPHASE_FINAL, obj->getPosition());

			doCollapseDoneStuff();

			obj->clearModelConditionState(MODELCONDITION_RUBBLE_RISE_START);
			obj->setModelConditionState(MODELCONDITION_RUBBLE_RISE_DONE);
			obj->setOrientation(obj->getOrientation());

			BodyModuleInterface *body = obj->getBodyModule();
			body->updateBodyParticleSystems();

			Vector3 shudder;
			shudder.Set(0, 0, 0);
			const Matrix3D *instMatrix = obj->getDrawable()->getInstanceMatrix();
			Matrix3D newInstMatrix;
			newInstMatrix = *instMatrix;
			newInstMatrix.Set_Translation(shudder);
			obj->getDrawable()->setInstanceMatrix(&newInstMatrix, true);

			return UPDATE_SLEEP_FOREVER;
		}
	}

	return UPDATE_SLEEP_NONE;
}
