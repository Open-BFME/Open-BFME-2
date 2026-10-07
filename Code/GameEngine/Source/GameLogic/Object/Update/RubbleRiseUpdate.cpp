// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?rva004A4C3F@@YAXHHQAH@Z, retail 0x004A4C3F, 67 bytes.
// ?doPhaseStuff@RubbleRiseUpdate@@IAEXW4RubbleRisePhaseType@@PBUCoord3D@@@Z, retail 0x004A4E1E, 203 bytes.
//
// Donor: BFME 1's matched RubbleRiseUpdate.cpp (buildNonDupRandomIndexList and
// doPhaseStuff), reference/open-bfme-1/game/GameEngine/Source/GameLogic/
// Object/Update/RubbleRiseUpdate.cpp, over Zero Hour's
// StructureCollapseUpdate::doPhaseStuff. Target facts:
// - 0x004A4C3F is RubbleRiseUpdate.cpp's static copy of
//   buildNonDupRandomIndexList: its GetGameLogicRandomValue call pushes the
//   RubbleRiseUpdate.cpp file string 0x00C528A0 and line 272, and only
//   doPhaseStuff calls it. The ledger already gives the name to
//   StructureCollapseUpdate's copy (0x004A425C), so this one keeps its
//   address name. As a static it takes range in eax and the list in ebx,
//   which survives only next to its caller. inList is the shared 0x004A423A.
// - Module data (parse table 0x00C52960): per-phase OCL and FX lists at
//   +0x58/+0x88 and their counts at +0xB8/+0xC8. The phase names table
//   0x00DCBCE0 reads INITIAL, DELAY, BURST, FINAL.
// - doPhaseStuff fires every FX of the chosen indices without a null check
//   and creates the non-null OCLs with the module's object, as
//   StructureCollapseUpdate's (0x004A43E9) does.
// RubbleRiseUpdate::update (0x004A4F72) is banked in reverse/attempts.

#include "matrix3d.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), __FILE__, __LINE__)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum RubbleRisePhaseType
{
	RRPHASE_INITIAL = 0,
	RRPHASE_DELAY,
	RRPHASE_BURST,
	RRPHASE_FINAL,

	RR_PHASE_COUNT
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

class ModuleData;

class RubbleRiseUpdateModuleData
{
public:
	unsigned char m_pad000[0x58];
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

class RubbleRiseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	void doPhaseStuff(RubbleRisePhaseType rrphase, const Coord3D *target);

	const RubbleRiseUpdateModuleData *getRubbleRiseUpdateModuleData() const
	{
		return (const RubbleRiseUpdateModuleData *)getModuleData();
	}
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
