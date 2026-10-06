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

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
};

class WorkerStateMachine : public StateMachine
{
public:
	WorkerStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
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
	virtual void dozerSlot0() = 0;
};

class SupplyTruckAIInterface
{
public:
	virtual void supplyTruckSlot0() = 0;
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
