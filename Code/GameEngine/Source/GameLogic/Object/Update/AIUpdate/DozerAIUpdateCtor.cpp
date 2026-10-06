// cl: /DNDEBUG /MD /GX
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
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned int ObjectID;

#define FALSE false
#define INVALID_ID 0

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
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
	void defineState(StateID id, struct State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = 0);
protected:
	unsigned char m_pad04[0x3C - 0x04]; // operator new size 0x3C
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
protected:
	unsigned char m_pad04[0x20 - 0x04];
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

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

class DozerAIInterface
{
public:
	virtual void slot0() = 0;
};

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
	virtual void slot0();
private:
	enum { DOZER_NUM_TASKS = 3 };
	enum { DOZER_NUM_DOCK_POINTS = 3 };
	enum { DOZER_SELECT_BUILD_DOCK_LOCATION = 0 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

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

void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}
