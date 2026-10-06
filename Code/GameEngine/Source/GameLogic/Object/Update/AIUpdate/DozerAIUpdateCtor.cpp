// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// Zero Hour's DozerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// DozerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@DozerAIUpdate@@AAEXXZ, retail 0x00488EFC, 86 bytes. Called
// by the ctor 0x004894F5 and by construct 0x00488F52 (which first stores its
// isRebuild argument at +0x40C, ZH's m_isRebuild); +0x400 is the machine
// pointer both test. As in ZH: without a machine, make a
// DozerPrimaryStateMachine (0x3C bytes, plain operator new; ctor 0x00488DAB
// defines the dozer states) for the object and enter its default state
// (machine vslot 7, initDefaultState).
//
// ??0DozerPrimaryStateMachine@@QAE@PAVObject@@@Z, retail 0x00488DAB, 309
// bytes. As in ZH: the StateMachine base (rowed 0x004D79E1; name key
// 0x3EA7DE5F, flag false; vtable 0x0084B668) and the five dozer states in
// ZH's order: idle (rowed ctor 0x004886C7) with the idle conditions table
// (retail .rdata 0x0084B808: three tests, states 1-3, then a terminator;
// the tests 0x0048899D/0x004889E8/0x00488A34 are ZH's is*MostImportant),
// the build, repair and fortify action states (rowed ctor 0x00488883 with
// tasks 0-2) and going home (rowed ctor 0x0048896B), every success and
// failure id idle except the idle state's INVALID_STATE_ID.
//
// The idle conditions, retail 0x0048899D (75 bytes), 0x004889E8 (76) and
// 0x00488A34 (77), ZH's isBuildMostImportant, isRepairMostImportant and
// isFortifyMostImportant in table order: the machine owner's AI (Object
// +0x258), its dozer interface (AI vslot 93) and idleness (vslot 110),
// then whether the most recent command (dozer vslot 5) is the state's
// task. Their State parameter is spelled struct, as the rowed defineState.
//
// ??0DozerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004894F5,
// 239 bytes. Target evidence: the body runs the pinned AIUpdateInterface
// ctor 0x0026E9BD and the implicit ctor of the all-_purecall interface at
// +0x3E4 (vtable 0x0084B788), stores the final vtables (0x0084B848 primary)
// and builds the 3x3 dock point array at +0x410 through __ehvec_ctor with an
// empty out-of-line element ctor/dtor (ICF-folded 0x0047A6A9/0x000B3FD0).
// As in ZH it clears the three tasks (+0x3E8, 8 bytes each) and every dock
// point (valid flag and zeroed location), sets the current task to
// DOZER_TASK_INVALID (+0x404), the build sub-task (+0x4A0) to
// DOZER_SELECT_BUILD_DOCK_LOCATION and the machine pointer to NULL, then
// creates the machines. New in BFME 2: +0x4A4 is zeroed in the init list,
// the +0x40C flag (construct 0x00488F52's isRebuild) is cleared and +0x408
// is set to 1.
//
// ?onDelete@DozerAIUpdate@@UAEXXZ, retail 0x00489CA1, 104 bytes (primary vslot 8; the
// dozer interface's slot 0 reaches it through its this-adjusting entry). As
// in ZH: cancel every pending task (dozer interface vslots 6 and 13), then
// clear MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED (Object +0x114 bit 5,
// notifying through the rowed 0x0028AE6D on change) on each task's target
// (+0x3E8 ids, the rowed GameLogic::findObjectByID). New in BFME 2: it ends
// with the dozer interface's finishBuildingSound (vslot 24, tail call).
//
// ?findGoodBuildOrRepairPositionAndTarget@DozerAIUpdate@@IAEPAVObject@@PAV2@0AAUCoord3D@@@Z,
// retail 0x00489913, 244 bytes. ZH's static
// DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget as a member, the
// Worker twin 0x004AABB4 without its docking-trace lines: for a bridge
// (kind-of bit 22 on the template, Thing +0x04 then +0x108) it picks the
// reachable tower (bridge interface vslot 1, four towers, the pinned
// isPathAvailable) whose position (the pinned findGoodBuildOrRepairPosition
// 0x00489039) is nearest, else it finds the target's position.
//
// ?newTask@DozerAIUpdate@@UAEXW4DozerTask@@PAVObject@@@Z, retail 0x00489A07,
// 666 bytes (dozer interface vslot 12, so its this is the +0x3E4
// interface). Donor: BFME 1's DozerAIUpdateNewTaskBfme.cpp over ZH's
// DozerAIUpdate::newTask: for a build or repair task it cancels a pending one
// (vslots 6 and 13), finds the position and target (rowed 0x00489913), sets
// the builder (rowed 0x0028AFE7) for builds and fills the three dock points,
// the end point pushed 50 units out from the target along the normalized 2D
// offset (rowed Coord3D::normalize 0x000035B6; the offset in its own block,
// as in the donor, keeps its scaled components in registers); then it
// records the target id and frame (TheGameLogic +0x40) and resets the dozer
// machine (vslot 6). The DockingDesync(DOZER) diagnostics are the Worker
// twin's (0x004AADB1), under the same two switches. Unlike the Worker, BFME 2
// adds nothing here.
#include "ascii_string.h"

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line normalize (rowed 0x000035B6) that newTask calls; same three floats
struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define FALSE false
#define TRUE true

struct _iobuf;
typedef struct _iobuf FILE;

extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

// BFME's logic random log file (data ledger 0x00DFEFF0).
extern "C" FILE *theLogicRandomLogFile;

// BFME 1's docking diagnostics switches (0x00DCBF44 and 0x00E03CA8).
extern bool g_bfmeDockingDesyncLog;
extern bool g_bfmeDockingTraceActive;

enum ObjectID
{
	INVALID_ID = 0
};

class Thing;
class ModuleData;
class Object;

enum StateReturnType
{
	STATE_CONTINUE,
	STATE_SUCCESS,
	STATE_FAILURE
};

typedef UnsignedInt StateID;
enum { INVALID_STATE_ID = 999999 };

class State;
struct StateConditionInfo
{
	Bool (*test)(State *thisState, void *userData);
	StateID toStateID;
	void *userData;
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void resetToDefaultState(); // vslot 6
	virtual StateReturnType initDefaultState();
	void defineState(StateID id, struct State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = 0);
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18]; // operator new size 0x3C
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z. Every
// caller passes the name as one dword, and only a scalar parameter gives
// retail's push of the immediate key, so this view takes the key as one.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};

struct State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

// ZH's DozerPrimaryIdleState (rowed ctor 0x004886C7).
class Rva004886C7 : public State
{
public:
	Rva004886C7(StateMachine *machine);
private:
	unsigned char m_pad20[0x2C - 0x20];
};

// ZH's DozerActionState (machine, task) (rowed ctor 0x00488883).
class Rva00488D5C : public State
{
public:
	Rva00488D5C(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

// ZH's DozerPrimaryGoingHomeState (rowed ctor 0x0048896B).
class Rva0048896B : public State
{
public:
	Rva0048896B(StateMachine *machine);
};

enum DozerTask
{
	DOZER_TASK_INVALID = -1,
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY
};

enum
{
	DOZER_PRIMARY_IDLE = 0,
	DOZER_PRIMARY_BUILD,
	DOZER_PRIMARY_REPAIR,
	DOZER_PRIMARY_FORTIFY,
	DOZER_PRIMARY_GO_HOME
};

class DozerPrimaryStateMachine : public Rva004D759C
{
public:
	DozerPrimaryStateMachine(Object *owner);
	virtual ~DozerPrimaryStateMachine();

	static Bool isBuildMostImportant(State *thisState, void *userData);
	static Bool isRepairMostImportant(State *thisState, void *userData);
	static Bool isFortifyMostImportant(State *thisState, void *userData);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class DozerAIInterface
{
public:
	virtual void onDelete() = 0; // vslot 0
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual DozerTask getMostRecentCommand() = 0; // vslot 5
	virtual Bool isTaskPending(DozerTask task) = 0; // vslot 6
	virtual void slot7() = 0; virtual void slot8() = 0; virtual void slot9() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void newTask(DozerTask task, Object *target) = 0; // vslot 12
	virtual void cancelTask(DozerTask task) = 0; // vslot 13
	virtual void slot14() = 0; virtual void slot15() = 0; virtual void slot16() = 0;
	virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void finishBuildingSound() = 0; // vslot 24
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	// Primary vtable slots 1-92 (slot 0 is the destructor).
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void onDelete(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
	virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
	virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69(); virtual void v70();
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80();
	virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89(); virtual void v90();
	virtual void v91(); virtual void v92();
	virtual DozerAIInterface *getDozerAIInterface(); // vslot 93 (+0x174)
	virtual void v94(); virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99(); virtual void v100();
	virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108(); virtual void v109();
	virtual Bool isIdle() const; // vslot 110 (+0x1B8)
	Bool isPathAvailable(const Coord3D *destination) const;
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

enum ModelConditionFlagType
{
	MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED = 69 // +0x114 bit 5
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

enum KindOfType
{
	KINDOF_BRIDGE = 22
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
private:
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x108 - 0x68];
	UnsignedInt m_kindOf[4]; // +0x108
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	void rva0028AFE7(Object *builder);
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	void rva0028AE6D();
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_MAX_TOWERS = 4
};

class BridgeBehaviorInterface
{
public:
	virtual void slot0();
	virtual ObjectID getTowerID(BridgeTowerType type); // vslot 1
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

inline Real sqr(Real x)
{
	return x * x;
}

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The dock point element: an out-of-line empty ctor and dtor (retail's
// __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and 0x000B3FD0).
struct Rva004894F5DockPoint
{
	Rva004894F5DockPoint();
	~Rva004894F5DockPoint();
	Bool valid;
	Coord3D location;
};

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	DozerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DozerAIUpdate();
	virtual void onDelete();
	virtual void newTask(DozerTask task, Object *target);
private:
	enum { DOZER_NUM_TASKS = 3 };
	enum { DOZER_NUM_DOCK_POINTS = 3 };
	enum { DOZER_DOCK_POINT_START = 0, DOZER_DOCK_POINT_ACTION, DOZER_DOCK_POINT_END };
	enum { DOZER_SELECT_BUILD_DOCK_LOCATION = 0 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

protected:
	Bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
	Object *findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut);

private:
	DozerTaskInfo m_task[DOZER_NUM_TASKS]; // +0x3E8
	DozerPrimaryStateMachine *m_dozerMachine; // +0x400
	Int m_currentTask; // +0x404
	Int m_408; // +0x408
	Bool m_isRebuild; // +0x40C
	Rva004894F5DockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS]; // +0x410
	Int m_buildSubTask; // +0x4A0
	Int m_4A4; // +0x4A4
};

DozerAIUpdate::DozerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData),
	  m_4A4(0)
{
	Int i, j;

	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		m_task[i].m_targetObjectID = INVALID_ID;
		m_task[i].m_taskOrderFrame = 0;

		for (j = 0; j < DOZER_NUM_DOCK_POINTS; j++)
		{
			m_dockPoint[i][j].valid = FALSE;
			zeroCoord(m_dockPoint[i][j].location);
		}
	}
	m_currentTask = DOZER_TASK_INVALID;
	m_buildSubTask = DOZER_SELECT_BUILD_DOCK_LOCATION;
	m_dozerMachine = 0;
	m_isRebuild = FALSE;
	m_408 = 1;

	createMachines();
}

DozerPrimaryStateMachine::DozerPrimaryStateMachine(Object *owner) : Rva004D759C(owner, 0x3EA7DE5F, false)
{
	static const StateConditionInfo idleConditions[] =
	{
		{ isBuildMostImportant, DOZER_PRIMARY_BUILD, 0 },
		{ isRepairMostImportant, DOZER_PRIMARY_REPAIR, 0 },
		{ isFortifyMostImportant, DOZER_PRIMARY_FORTIFY, 0 },
		{ 0, 0, 0 } // keep last
	};

	// order matters: first state is the default state.
	defineState(DOZER_PRIMARY_IDLE, new Rva004886C7(this), INVALID_STATE_ID, INVALID_STATE_ID, idleConditions);
	defineState(DOZER_PRIMARY_BUILD, new Rva00488D5C(this, DOZER_TASK_BUILD), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_REPAIR, new Rva00488D5C(this, DOZER_TASK_REPAIR), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_FORTIFY, new Rva00488D5C(this, DOZER_TASK_FORTIFY), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_GO_HOME, new Rva0048896B(this), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
}

Bool DozerPrimaryStateMachine::isBuildMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_BUILD;
}

Bool DozerPrimaryStateMachine::isRepairMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_REPAIR;
}

Bool DozerPrimaryStateMachine::isFortifyMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_FORTIFY;
}

void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}

void DozerAIUpdate::onDelete(void)
{
	Int i;

	// cancel any of the tasks we had queued up
	for (i = DOZER_TASK_FIRST; i < DOZER_NUM_TASKS; ++i)
	{
		if (isTaskPending((DozerTask)i))
			cancelTask((DozerTask)i);
	}

	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		Object *goalObject = TheGameLogic->findObjectByID(m_task[i].m_targetObjectID);
		if (goalObject != 0)
		{
			goalObject->clearModelConditionState(MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED);
		}
	}

	finishBuildingSound();
}

Object *DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut)
{
	if (target->isKindOf(KINDOF_BRIDGE))
	{
		BridgeBehaviorInterface *bridgeInterface = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
		if (bridgeInterface)
		{
			// pick the reachable tower position closest to us
			AIUpdateInterface *ai = me->getAIUpdateInterface();
			Real closestDistSq = 1e10f;
			Object *closestTower = 0;
			for (Int i = 0; i < BRIDGE_MAX_TOWERS; ++i)
			{
				Object *tower = TheGameLogic->findObjectByID(bridgeInterface->getTowerID((BridgeTowerType)i));
				if (tower)
				{
					Coord3D pos;
					if (findGoodBuildOrRepairPosition(me, tower, pos) && ai->isPathAvailable(&pos))
					{
						Real distSq = sqr(me->getPosition()->x - pos.x) + sqr(me->getPosition()->y - pos.y);
						if (distSq < closestDistSq)
						{
							positionOut = pos;
							closestDistSq = distSq;
							closestTower = tower;
						}
					}
				}
			}
			return closestTower;
		}
	}

	findGoodBuildOrRepairPosition(me, target, positionOut);
	return target;
}

void DozerAIUpdate::newTask(DozerTask task, Object *target)
{
	// sanity
	if (target == 0)
		return;

	//
	// special check for the build task, we should never be given more than one of them ...
	// for the other tasks we just forget what we were doing and the new target takes
	// precedence for the task
	//
	if (task == DOZER_TASK_BUILD || task == DOZER_TASK_REPAIR)
	{
		// handle getting two tasks
		if (isTaskPending(task) == TRUE)
			cancelTask(task);

		// get our object
		Object *me = getObject();

		Coord3D position;
		if (g_bfmeDockingDesyncLog)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) BEGIN: Object %s(%d) with target %s(%d) at %g,%g,%g",
					me->getTemplate()->getName().str(), me->getID(),
					target->getTemplate()->getName().str(), target->getID(),
					me->getPosition()->x, me->getPosition()->y, me->getPosition()->z);
			g_bfmeDockingTraceActive = true;
		}

		target = findGoodBuildOrRepairPositionAndTarget(me, target, position);
		if (target == 0)
		{
			if (g_bfmeDockingDesyncLog)
			{
				if (theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) END: Object %s(%d) with no target found docking position %g,%g,%g",
						me->getTemplate()->getName().str(), me->getID(),
						position.x, position.y, position.z);
				g_bfmeDockingTraceActive = false;
			}
			return; // could happen for some bridges
		}

		if (g_bfmeDockingDesyncLog)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) END: Object %s(%d) with target %s(%d) found docking position %g,%g,%g",
					me->getTemplate()->getName().str(), me->getID(),
					target->getTemplate()->getName().str(), target->getID(),
					position.x, position.y, position.z);
			g_bfmeDockingTraceActive = false;
		}

		//
		// for building, we say that even "thinking" about building or rebuilding an object
		// sets us as the current builder of that object
		//
		if (task == DOZER_TASK_BUILD)
			target->rva0028AFE7(me);

		m_dockPoint[task][DOZER_DOCK_POINT_START].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_START].location = position;
		m_dockPoint[task][DOZER_DOCK_POINT_ACTION].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_ACTION].location = position;

		// the end point is pushed out from the target
		{
			Coord3D offset;
			offset.x = position.x - target->getPosition()->x;
			offset.y = position.y - target->getPosition()->y;
			offset.z = 0.0f;
			offset.normalize();
			offset.x *= 50.0f;
			offset.y *= 50.0f;
			offset.z *= 50.0f;
			position.x += offset.x;
			position.y += offset.y;
			position.z += offset.z;
		}

		m_dockPoint[task][DOZER_DOCK_POINT_END].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_END].location = position;
	}

	// set the new task target and the frame in which we got this order
	m_task[task].m_targetObjectID = target->getID();
	m_task[task].m_taskOrderFrame = TheGameLogic->getFrame();

	// reset the dozer behavior so that it can re-evluate which task to continue working on
	m_dozerMachine->resetToDefaultState();
}
