// cl: /DNDEBUG /MD /GX
//
// Zero Hour's WorkerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// WorkerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@WorkerAIUpdate@@AAEXXZ, retail 0x004A9ED5, 218 bytes. As in
// ZH: without a worker machine, make one (0x3C bytes, plain operator new;
// pinned ctor 0x004A9D79) and, where missing, the dozer (pinned 0x00488DAB)
// and supply truck (pinned 0x004A7010) machines, entering each one's default
// state (machine vslot 7) and the worker machine's last. The three machine
// pointers are the rowed dtor 0x004A9A12's +0x4C0/+0x4C4/+0x4C8.
//
// ??0WorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AA3AB,
// 339 bytes. Target evidence: the body runs the pinned AIUpdateInterface
// ctor 0x0026E9BD and the implicit ctors of the three all-_purecall
// interfaces at +0x3E4/+0x3E8/+0x3EC, stores the final vtables (0x00854190
// primary, slot 0 the rowed ??_GWorkerAIUpdate 0x004A9EB9) and builds the
// 3x3 dock point array at +0x40C through __ehvec_ctor with an empty
// out-of-line element ctor/dtor (ICF-folded 0x0047A6A9/0x000B3FD0; the
// dtor's BfmeWorkerDockPoint). As in ZH it clears the rebuild flag and the
// dozer machine, the tasks (+0x3F0) and dock points, sets the current task
// to DOZER_TASK_INVALID and the build sub-task to
// DOZER_SELECT_BUILD_DOCK_LOCATION, clears the supply truck machine, the box
// count, both force flags and the worker machine, then creates the
// machines. Member roles past the dock points follow ZH's order (sub-task,
// box count, preferred dock, the three flags, the machines); new in BFME 2:
// +0x4A0, the +0x4A8 point, the +0x4B4 flag and +0x4CC (set to 1, where ZH
// copied its supplies-depleted voice). The preferred dock is zeroed first.
//
// ??0WorkerStateMachine@@QAE@PAVObject@@@Z, retail 0x004A9D79, 169 bytes. As
// in ZH: the StateMachine base (rowed 0x004D79E1; name key 0xF80D13C5, flag
// false; vtable 0x00854058, the rowed Rva004A9964 dtor's), then ActAsDozer
// (rowed ctor 0x004A992A) with asDozerConditions (retail .rdata 0x00854410)
// and ActAsSupplyTruck (rowed ctor 0x004A9947) with asTruckConditions
// (0x008543F8), plain operator new of 0x20 bytes each.
//
// The two condition tests, ZH's supplyTruckSubMachineWantsToEnter (retail
// 0x004A9975, 70 bytes) and supplyTruckSubMachineReadyToLeave (0x004A99BB,
// 59), and WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy (0x004A98D6, 62)
// that the second calls: the machine owner's AI (Object +0x258), its AI
// state (the rowed getCurrentStateID 0x00262FC3) and forced-wanting flag
// (the supply truck interface at +0x3E8, vslot 12, reading +0x4BC); BFME 2
// also accepts AI state 47 besides AI_DOCK. The brain test reads the worker
// and supply truck machines' current state ids (+0x04 state, its +0x04 id).
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
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

class StateMachine;

struct State
{
public:
	virtual ~State();
	StateID getID() const { return m_ID; }
	StateMachine *getMachine() const { return m_machine; }
protected:
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

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
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
	Object *getOwner() const { return m_owner; }
protected:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18]; // operator new size 0x3C
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z; the key is
// taken as one dword, as in the dozer machine's TU.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};

// ZH's ActAsDozerState (rowed ctor 0x004A992A).
class Rva004A992A : public State
{
public:
	Rva004A992A(StateMachine *machine);
};

// ZH's ActAsSupplyTruckState (rowed ctor 0x004A9947).
class Rva004A9947 : public State
{
public:
	Rva004A9947(StateMachine *machine);
};

enum
{
	AS_DOZER = 0,
	AS_SUPPLY_TRUCK
};

class WorkerStateMachine : public Rva004D759C
{
public:
	WorkerStateMachine(Object *owner);
	virtual ~WorkerStateMachine();

	static Bool supplyTruckSubMachineWantsToEnter(State *thisState, void *userData);
	static Bool supplyTruckSubMachineReadyToLeave(State *thisState, void *userData);
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
};

enum
{
	ST_IDLE = 0,
	ST_BUSY
};

class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
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
	Int getCurrentStateID() const;
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

enum AIStateType
{
	AI_DOCK = 14, // ZH's numbering (AI_IDLE 0 .. AI_DEAD 13)
	AI_STATE_47 = 47 // BFME 2's second supply state
};

class DozerAIInterface
{
public:
	virtual void dozerSlot0() = 0;
};

class SupplyTruckAIInterface
{
public:
	virtual void supplyTruckSlot0() = 0;
	virtual void st01() = 0; virtual void st02() = 0; virtual void st03() = 0; virtual void st04() = 0;
	virtual void st05() = 0; virtual void st06() = 0; virtual void st07() = 0; virtual void st08() = 0;
	virtual void st09() = 0; virtual void st10() = 0; virtual void st11() = 0;
	virtual Bool isForcedIntoWantingState() const = 0; // vslot 12 (+0x30)
};

class WorkerAIInterface3EC
{
public:
	virtual void workerSlot0() = 0;
};

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The dock point element: an out-of-line empty ctor and dtor (retail's
// __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and 0x000B3FD0).
struct BfmeWorkerDockPoint
{
	BfmeWorkerDockPoint();
	~BfmeWorkerDockPoint();
	Bool valid;
	Coord3D location;
};

class WorkerAIUpdate : public AIUpdateInterface, public DozerAIInterface, public SupplyTruckAIInterface, public WorkerAIInterface3EC
{
public:
	WorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void dozerSlot0();
	virtual void supplyTruckSlot0();
	virtual void workerSlot0();
	virtual Bool isForcedIntoWantingState() const;
	Bool isSupplyTruckBrainActiveAndBusy();
protected:
	virtual ~WorkerAIUpdate();
private:
	enum { DOZER_NUM_TASKS = 3 };
	enum { DOZER_NUM_DOCK_POINTS = 3 };
	enum { DOZER_TASK_INVALID = -1 };
	enum { DOZER_SELECT_BUILD_DOCK_LOCATION = 0 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

	DozerTaskInfo m_task[DOZER_NUM_TASKS]; // +0x3F0
	Int m_currentTask; // +0x408
	BfmeWorkerDockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS]; // +0x40C
	Int m_buildSubTask; // +0x49C
	Int m_4A0; // +0x4A0
	Int m_numberBoxes; // +0x4A4
	Coord3D m_4A8; // +0x4A8
	Bool m_4B4; // +0x4B4
	ObjectID m_preferredDock; // +0x4B8
	Bool m_forcePending; // +0x4BC
	Bool m_isRebuild; // +0x4BD
	Bool m_forcedBusyPending; // +0x4BE
	WorkerStateMachine *m_workerMachine; // +0x4C0
	DozerPrimaryStateMachine *m_dozerMachine; // +0x4C4
	SupplyTruckStateMachine *m_supplyTruckStateMachine; // +0x4C8
	Int m_4CC; // +0x4CC
};

WorkerAIUpdate::WorkerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
	m_preferredDock = INVALID_ID;
	m_isRebuild = FALSE;
	m_dozerMachine = 0;
	for (Int i = 0; i < DOZER_NUM_TASKS; i++)
	{
		m_task[i].m_targetObjectID = INVALID_ID;
		m_task[i].m_taskOrderFrame = 0;
		for (Int j = 0; j < DOZER_NUM_DOCK_POINTS; j++)
		{
			m_dockPoint[i][j].valid = FALSE;
			zeroCoord(m_dockPoint[i][j].location);
		}
	}
	m_currentTask = DOZER_TASK_INVALID;
	m_buildSubTask = DOZER_SELECT_BUILD_DOCK_LOCATION;

	m_supplyTruckStateMachine = 0;
	m_numberBoxes = 0;
	zeroCoord(m_4A8);
	m_4B4 = FALSE;
	m_4A0 = 0;
	m_forcePending = FALSE;
	m_forcedBusyPending = FALSE;

	m_workerMachine = 0;
	m_4CC = 1;

	createMachines();
}

void WorkerAIUpdate::createMachines()
{
	if (m_workerMachine == 0)
	{
		m_workerMachine = new WorkerStateMachine(getObject());

		if (m_dozerMachine == 0)
		{
			m_dozerMachine = new DozerPrimaryStateMachine(getObject());
			m_dozerMachine->initDefaultState();
		}

		if (m_supplyTruckStateMachine == 0)
		{
			m_supplyTruckStateMachine = new SupplyTruckStateMachine(getObject());
			m_supplyTruckStateMachine->initDefaultState();
		}

		m_workerMachine->initDefaultState();
	}
}

WorkerStateMachine::WorkerStateMachine(Object *owner) : Rva004D759C(owner, 0xF80D13C5, false)
{
	static const StateConditionInfo asDozerConditions[] =
	{
		{ supplyTruckSubMachineWantsToEnter, AS_SUPPLY_TRUCK, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo asTruckConditions[] =
	{
		{ supplyTruckSubMachineReadyToLeave, AS_DOZER, 0 },
		{ 0, 0, 0 } // keep last
	};

	// order matters: first state is the default state.
	defineState(AS_DOZER, new Rva004A992A(this), INVALID_STATE_ID, INVALID_STATE_ID, asDozerConditions);
	defineState(AS_SUPPLY_TRUCK, new Rva004A9947(this), INVALID_STATE_ID, INVALID_STATE_ID, asTruckConditions);
}

Bool WorkerStateMachine::supplyTruckSubMachineWantsToEnter(State *thisState, void *userData)
{
	Object *owner = thisState->getMachine()->getOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate *)owner->getAIUpdateInterface();
	if (!update)
	{
		return false;
	}
	Int masterState = update->getCurrentStateID();

	// If I detect a Supply force message, or if I have been put straight in
	// dock, then the worker master part of me wants to switch to the Supply
	// sub-brain.
	return update->isForcedIntoWantingState() || (masterState == AI_DOCK) || (masterState == AI_STATE_47);
}

Bool WorkerStateMachine::supplyTruckSubMachineReadyToLeave(State *thisState, void *userData)
{
	Object *owner = thisState->getMachine()->getOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate *)owner->getAIUpdateInterface();
	if (!update)
	{
		return false;
	}

	// It isn't ready to leave if it is on its way in. Active and Busy means
	// it isn't doing anything Supply related.
	return !supplyTruckSubMachineWantsToEnter(thisState, 0) && update->isSupplyTruckBrainActiveAndBusy();
}

Bool WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy()
{
	return (m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK)
		&& (m_supplyTruckStateMachine->getCurrentStateID() == ST_BUSY);
}
