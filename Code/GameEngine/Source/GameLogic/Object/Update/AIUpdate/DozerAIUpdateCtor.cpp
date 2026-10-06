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

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
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
	enum { DOZER_TASK_INVALID = -1 };
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

void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}
