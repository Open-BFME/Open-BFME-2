// cl: /O1 /DNDEBUG /MD
//
// AIEnterState::onExit, retail 0x003510A5 (100 bytes): slot 5 of vtable
// 0x00C12E90, whose slot-2 name getter 0x00342ED1 returns AIEnterState; the
// body is the Zero Hour AIStates.cpp AIEnterState::onExit (base
// AIInternalMoveToState::onExit 0x003473A4, ignoreObstacle(NULL), locomotor
// allow-invalid-position off (bit 1 of Locomotor+0x44), then the contain of
// m_entryToClear (+0x4C) is told WANTS_NEITHER through Object+0x250 slot 17).
// Rva00351109::onExit, retail 0x00351109 (129 bytes): slot 5 of vtable
// 0x00C12F40 (unrowed ctor 0x00342F15); it passes the object found from +0x50
// to state machine virtual slot 14, then runs the same exit body inline, so the
// class derives from AIEnterState. Its name getter literal is not used as an
// identity; the placeholder is named by address.
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
#include "../../Common/GameLogicObjectLookupView.h"
enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};
class Object;
#include "../../../Include/GameLogic/Module/ContainModule.h"
class Locomotor
{
public:
	enum LocoFlag
	{
		ALLOW_INVALID_POSITION = 1,
		PRECISE_Z_POS = 3
	};
	__declspec(dllimport) __forceinline void setAllowInvalidPosition(bool allow) { setFlag(ALLOW_INVALID_POSITION, allow); }
	void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
private:
	void setFlag(LocoFlag f, bool b)
	{
		if (b)
			m_flags |= (1 << f);
		else
			m_flags &= ~(1 << f);
	}
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	unsigned char m_pad000[0x1F0];
	Locomotor *m_curLocomotor; // +0x1F0
};
class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x250];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};
extern GameLogic *TheGameLogic;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13();
	virtual void rva00351109Slot14(Object *obj);
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
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
	virtual void onExit(StateExitType status);
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};
class AIEnterState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	void exitEnterState(StateExitType status);
	unsigned char m_pad1C[0x4C - 0x1C];
	ObjectID m_entryToClear; // +0x4C
};
class Rva00351109 : public AIEnterState
{
public:
	virtual void onExit(StateExitType status);
private:
	ObjectID m_50; // +0x50
};
// ?AIEnterState::exitEnterState absent-from-retail
// (force-inlined into both onExit bodies; no out-of-line retail copy)
__forceinline void AIEnterState::exitEnterState(StateExitType status)
{
	Object *obj = getMachineOwner();
	AIInternalMoveToState::onExit(status);

	// tell the pathfinder to stop ignoring the object
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
	{
		ai->ignoreObstacle(0);
		if (ai->getCurLocomotor())
		{
			ai->getCurLocomotor()->setAllowInvalidPosition(false);
		}
	}

	// use this, rather than getMachineGoalObject, in case the goal
	// is killed while we were waiting...
	if (m_entryToClear != INVALID_OBJECT_ID)
	{
		Object *goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
			{
				contain->onObjectWantsToEnterOrExit(obj, WANTS_NEITHER);
			}
		}
	}
}
void AIEnterState::onExit(StateExitType status)
{
	exitEnterState(status);
}
void Rva00351109::onExit(StateExitType status)
{
	Object *target = TheGameLogic->findObjectByID(m_50);
	if (target)
		getMachine()->rva00351109Slot14(target);
	exitEnterState(status);
}
