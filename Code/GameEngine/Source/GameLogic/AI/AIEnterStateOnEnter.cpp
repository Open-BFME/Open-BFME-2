// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIEnterState::onEnter, retail 0x0034FB77 (309 bytes).
//
// Identity: the existing pin. Donor: Zero Hour AIStates.cpp
// AIEnterState::onEnter (clear the entry to clear, fail without a goal or when
// the action manager refuses entry, take the goal position, tell the goal's
// contain we want to enter and remember it, ignore the goal as an obstacle,
// allow invalid locomotor positions, stop adjusting the destination, then
// AIInternalMoveToState::onEnter). BFME2 target facts: an entry timeout frame
// at +0x50 (TheGlobalData +0x1234 plus the current frame); the goal position
// comes from the contain's slot 0x158 when the goal has a contain, adjusted by
// the pathfinder (0x002FCFCF) for kind-of bit 191; BFME's canEnterObject
// takes the command source from AI slot 0x23C plus three zero arguments;
// setAdjustsDestination(false) writes the CritterDesync log line first.
// Layout as in AIEnterStateOnExit.cpp.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_FAILURE = -2
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

class Object;

class ContainModuleInterface
{
public:
#define X1_V(n) virtual void slot##n() = 0;
	X1_V(00) X1_V(01) X1_V(02) X1_V(03) X1_V(04) X1_V(05) X1_V(06) X1_V(07) X1_V(08) X1_V(09)
	X1_V(10) X1_V(11) X1_V(12) X1_V(13) X1_V(14) X1_V(15) X1_V(16)
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants) = 0;
	X1_V(18) X1_V(19) X1_V(20) X1_V(21) X1_V(22) X1_V(23) X1_V(24) X1_V(25) X1_V(26) X1_V(27) X1_V(28) X1_V(29)
	X1_V(30) X1_V(31) X1_V(32) X1_V(33) X1_V(34) X1_V(35) X1_V(36) X1_V(37) X1_V(38) X1_V(39)
	X1_V(40) X1_V(41) X1_V(42) X1_V(43) X1_V(44) X1_V(45) X1_V(46) X1_V(47) X1_V(48) X1_V(49)
	X1_V(50) X1_V(51) X1_V(52) X1_V(53) X1_V(54) X1_V(55) X1_V(56) X1_V(57) X1_V(58) X1_V(59)
	X1_V(60) X1_V(61) X1_V(62) X1_V(63) X1_V(64) X1_V(65) X1_V(66) X1_V(67) X1_V(68) X1_V(69)
	X1_V(70) X1_V(71) X1_V(72) X1_V(73) X1_V(74) X1_V(75) X1_V(76) X1_V(77) X1_V(78) X1_V(79)
	X1_V(80) X1_V(81) X1_V(82) X1_V(83) X1_V(84) X1_V(85)
#undef X1_V
	virtual const Coord3D *getEnterPosition() = 0;
};

class Locomotor
{
public:
	void setAllowInvalidPosition(Bool allow)
	{
		if (allow)
			m_flags |= 2;
		else
			m_flags &= ~2;
	}
	char m_pad[0x44];
	UnsignedInt m_flags; // +0x44
};

class LocomotorSet
{
public:
	char m_pad[4];
};

class AIUpdateInterface
{
public:
#define X1_V(n) virtual void slot##n();
#define X1_V10(n) X1_V(n##0) X1_V(n##1) X1_V(n##2) X1_V(n##3) X1_V(n##4) X1_V(n##5) X1_V(n##6) X1_V(n##7) X1_V(n##8) X1_V(n##9)
	X1_V10(0) X1_V10(1) X1_V10(2) X1_V10(3) X1_V10(4) X1_V10(5) X1_V10(6)
	X1_V10(7) X1_V10(8) X1_V10(9) X1_V10(10) X1_V10(11) X1_V10(12) X1_V10(13)
	X1_V(140) X1_V(141) X1_V(142)
#undef X1_V10
#undef X1_V
	virtual CommandSourceType getLastCommandSource();

	void ignoreObstacle(const Object *obj);
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	char m_pad004[0x1CC - 0x04];
	LocomotorSet m_locomotorSet; // +0x1CC
	char m_pad1D0[0x1F0 - 0x1D0];
	Locomotor *m_curLocomotor; // +0x1F0
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(UnsignedInt bit) const
	{
		return m_kindOf[bit >> 5] & (1U << (bit & 0x1f));
	}
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8];
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	char m_pad078[0x250 - 0x78];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest,
		const Coord3D *groupDest);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class BFMEActionManager
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, Bool a, Bool *b);
};
extern BFMEActionManager *TheActionManager;

class GlobalData
{
public:
	char m_pad[0x1234];
	UnsignedInt m_enterStateTimeoutFrames;
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

extern GameLogic *TheGameLogic;

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	__forceinline void setAdjustsDestination(Bool b)
	{
		critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 57");
		m_adjustsDestination = b;
	}
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:

	ObjectID m_entryToClear; // +0x4C
	UnsignedInt m_entryTimeoutFrame; // +0x50
};

enum
{
	KINDOF_BIT_191 = 191
};

StateReturnType AIEnterState::onEnter()
{
	m_entryToClear = INVALID_OBJECT_ID;
	m_entryTimeoutFrame = TheGlobalData->m_enterStateTimeoutFrames + TheGameLogic->getFrame();

	Object *obj = getMachineOwner();
	Object *goal = getMachineGoalObject();
	if (goal)
	{
		if (!TheActionManager->canEnterObject(obj, goal, obj->getAI()->getLastCommandSource(),
				CHECK_CAPACITY, false, 0))
			return STATE_FAILURE;

		ContainModuleInterface *contain = goal->getContain();
		if (contain)
		{
			m_goalPosition = *contain->getEnterPosition();
			if (goal->getTemplate()->isKindOf(KINDOF_BIT_191))
				TheAI->pathfinder()->adjustDestination(obj, obj->getAI()->m_locomotorSet,
					&m_goalPosition, 0);
			contain->onObjectWantsToEnterOrExit(obj, WANTS_TO_ENTER);
			m_entryToClear = goal->getID();
		}
		else
		{
			m_goalPosition = *goal->getPosition();
		}
	}
	else
	{
		return STATE_FAILURE;
	}

	// tell the pathfinder to ignore the enterable object
	AIUpdateInterface *ai = obj->getAI();
	ai->ignoreObstacle(getMachineGoalObject());
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setAllowInvalidPosition(true);

	setAdjustsDestination(false);
	return AIInternalMoveToState::onEnter();
}
