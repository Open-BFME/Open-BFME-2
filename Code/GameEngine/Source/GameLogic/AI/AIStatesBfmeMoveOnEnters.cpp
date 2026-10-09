// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AI move-state overrides: four adjacent onEnter bodies, retail
// 0x0034C994-0x0034CBAB, and the update/onExit bodies 0x00347B3D-0x00347C38.
//
// Donors: Zero Hour AIStates.cpp AIMoveOutOfTheWayState::onEnter (0x0034C994,
// CritterDesync string 6), AIMoveAndTightenState::onEnter (0x0034C9ED, string
// 7) and AIMoveAwayFromRepulsorsState::onEnter (0x0034CAF6, string 11, slot 4
// of the vtable at 0x00C12538 that the constructor 0x00342892 installs);
// BFME1's Rva00173B90State_onEnter.cpp for 0x0034CA53 (string 9, slot 4 of
// the vtable at 0x00C12580 installed by the constructor 0x003428AF, so its
// class takes that constructor row's placeholder name). BFME2 target facts:
// each setAdjustsDestination writes its CritterDesync log line first; the
// pathfinder's removeGoal is the owner's 0x0028AD32; the panicking model
// condition is bit 77 (word +0x114 of the bits at +0x10C, then 0x0028AE6D);
// the goal-object state also fails without an owner. Layout as in
// AIEnterStateOnEnter.cpp; m_okToRepathTimes +0x4C, m_checkForPath +0x50.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

enum LocomotorSetType
{
	LOCOMOTORSET_PANIC = 4
};

enum
{
	MODELCONDITION_PANICKING = 77
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

class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
};

class Path
{
public:
	PathNode *getLastNode() const { return m_pathTail; }
private:
	char m_pad00[8];
	PathNode *m_pathTail; // +0x08
};

class AIUpdateInterface
{
public:
#define X1_V(n) virtual void slot##n();
#define X1_V10(n) X1_V(n##0) X1_V(n##1) X1_V(n##2) X1_V(n##3) X1_V(n##4) X1_V(n##5) X1_V(n##6) X1_V(n##7) X1_V(n##8) X1_V(n##9)
	X1_V10(0) X1_V10(1) X1_V10(2) X1_V10(3) X1_V10(4) X1_V10(5) X1_V10(6)
	X1_V10(7) X1_V10(8) X1_V10(9) X1_V10(10) X1_V10(11) X1_V10(12) X1_V10(13)
	X1_V(140) X1_V(141)
#undef X1_V10
#undef X1_V
	virtual Bool chooseLocomotorSet(LocomotorSetType wst);

	Path *getPath() { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	void requestApproachPath(Coord3D *destination);
	void requestSafePath(ObjectID repulsor);
private:
	char m_pad004[0x140 - 0x04];
	Path *m_path; // +0x140
	char m_pad144[0x3B1 - 0x144];
	Bool m_waitingForPath; // +0x3B1
};

class ModelConditionFlags
{
public:
	UnsignedInt test(Int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(Int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(Int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	Real getVisionRange() const;
	void rva0028AE6D();
	void rva0028AD32();
	__forceinline void setModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	char m_pad000[0x74];
	ObjectID m_id; // +0x74
	char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_conditionBits; // +0x10C
	char m_pad158[0x258 - (0x10C + sizeof(ModelConditionFlags))];
	AIUpdateInterface *m_ai; // +0x258
};

class AI
{
public:
	Object *findClosestRepulsor(const Object *me, Real range);
};
extern AI *TheAI;

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class AIMoveOutOfTheWayState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

class AIMoveAndTightenState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	Int m_okToRepathTimes; // +0x4C
	Bool m_checkForPath; // +0x50
};

class Rva003428AF : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	Int m_okToRepathTimes; // +0x4C
	Bool m_checkForPath; // +0x50
};

class AIMoveAwayFromRepulsorsState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Int m_okToRepathTimes; // +0x4C
	Bool m_checkForPath; // +0x50
};

StateReturnType AIMoveOutOfTheWayState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 6");
	setAdjustsDestination(true);
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	if (ai->getPath() == 0)
	{
		// Must have existing path.
		return STATE_FAILURE;
	}
	m_goalPosition = *ai->getPath()->getLastNode()->getPosition();
	return AIInternalMoveToState::onEnter();
}

StateReturnType AIMoveAndTightenState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 7");
	setAdjustsDestination(false);
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	m_okToRepathTimes = 1;
	m_checkForPath = true;
	obj->rva0028AD32();
	m_goalPosition = *getMachineGoalPosition();
	ai->requestApproachPath(&m_goalPosition);
	return AIInternalMoveToState::onEnter();
}

StateReturnType Rva003428AF::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 9");
	setAdjustsDestination(false);
	Object *obj = getMachineOwner();
	Object *enemy = getMachineGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!enemy || !ai || !obj)
		return STATE_FAILURE;

	ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
	obj->setModelConditionState(MODELCONDITION_PANICKING);
	m_okToRepathTimes = 1;
	m_checkForPath = true;
	obj->rva0028AD32();
	ai->requestSafePath(enemy->getID());
	return AIInternalMoveToState::onEnter();
}

StateReturnType AIMoveAwayFromRepulsorsState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 11");
	setAdjustsDestination(false);
	Object *obj = getMachineOwner();
	Object *enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!enemy || !ai || !obj)
		return STATE_FAILURE;

	ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
	obj->setModelConditionState(MODELCONDITION_PANICKING);
	m_okToRepathTimes = 1;
	m_checkForPath = true;
	obj->rva0028AD32();
	ai->requestSafePath(enemy->getID());
	return AIInternalMoveToState::onEnter();
}

StateReturnType Rva003428AF::update()
{
	if (m_checkForPath)
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		Path *thePath = ai->getPath();
		if (thePath && !ai->isWaitingForPath())
		{
			m_goalPosition = *thePath->getLastNode()->getPosition();
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 10");
			setAdjustsDestination(false);
			m_checkForPath = false;
		}
	}
	return AIInternalMoveToState::update();
}

void AIMoveAwayFromRepulsorsState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *obj = getMachineOwner();
	if (obj)
		obj->clearModelConditionState(MODELCONDITION_PANICKING);
}

StateReturnType AIMoveAwayFromRepulsorsState::update()
{
	if (m_checkForPath)
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		Path *thePath = ai->getPath();
		if (thePath && !ai->isWaitingForPath())
		{
			m_goalPosition = *thePath->getLastNode()->getPosition();
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 12");
			setAdjustsDestination(false);
			m_checkForPath = false;
		}
	}
	return AIInternalMoveToState::update();
}
