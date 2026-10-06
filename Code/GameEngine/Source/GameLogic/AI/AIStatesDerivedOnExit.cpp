// cl: /O1 /DNDEBUG /MD /G7
//
// Derived AI state onExit overrides chaining to the rowed
// AIInternalMoveToState::onExit 0x003473A4, transferred from Zero Hour
// AIStates.cpp. Each class is identified by its vtable's slot-2 name getter
// (the state's own name literal) and the matching ZH body.
// AIAttackMoveToState::onExit, retail 0x0034A011 (28 bytes): slot 5 of vtable
// 0x00C13548 (name getter 0x00345CFA, AIAttackMoveToState; the same class as
// the placeholder rows Rva00345CAB); m_attackMoveMachine at +0x54 is set to
// AI_IDLE through StateMachine virtual slot 8, then the inherited
// AIMoveToState::onExit (not overridden, so the base 0x003473A4).
// AIFollowWaypointPathState::onExit, retail 0x0034A0D7 (46 bytes): slot 5 of
// vtable 0x00C12930 (name getter 0x00342BF6); base onExit, then clears the
// current locomotor's precise-z flag (bit 3 of Locomotor+0x44, the ZH
// PRECISE_Z_POS position; AI+0x1F0 is the current locomotor). BFME2 drops the
// ZH setUltraAccurate(false) call.
// AIAttackFollowWaypointPathState::onEnter/onExit/update, retail 0x0034F1C4 (29
// bytes), 0x0034A19F (28 bytes) and 0x0035426B (340 bytes): slots 4/5/6 of
// vtable 0x00C13638 (name getter AIAttackFollowWaypointPathState, a class BFME1
// rows by ctor, dtor and update); m_attackFollowMachine at +0x68 (BFME1 +0x6C)
// is cleared and set to AI_IDLE before the base onEnter (pinned 0x0034ED7B,
// tail jump), and set to AI_IDLE before the base onExit, as Zero Hour
// AIAttackMoveToState does with its attack-move machine. Machine slots 4/5/8/14
// are update/clear/setState/setGoalObject. Update checks attack-follow machine
// idle, clears model-condition flags, picks up crates or victim mood targets,
// optionally repaths with desync log, and chains to base update 0x00353F13.
// AIFollowWaypointPathStateAndEvacuate::onEnter/onExit, retail 0x0034F004 (23
// bytes) and 0x0034A105 (28 bytes): slots 4/5 of vtable 0x00C12998 (name getter
// AIFollowWaypointPathStateAndEvacuate); onEnter calls Rva0033FA64Do(owner)
// before base onEnter (0x0034ED7B); onExit calls base onExit (0x0034A0D7)
// before Rva0033FA79Do(owner). Its update, retail 0x003541F4 (119 bytes,
// slot 6), runs the base update (pinned 0x00353F13) and then succeeds once
// the point of the AI's path (+0x140) at the owner's +0xB8 distance fails
// the pinned pathfinder cell test 0x002E996E, handing the owner and machine
// to the pinned evacuate helper 0x003532BF (with false) on success, as the
// AIMoveToAndEvacuateState update in AIStatesEvacuate.cpp does.
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
typedef bool Bool;
typedef unsigned int StateID;
enum
{
	AI_IDLE = 0
};
class Locomotor
{
public:
	enum LocoFlag
	{
		PRECISE_Z_POS = 3
	};
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
template <int N> class AIDeadStateAISlots : public AIDeadStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIDeadStateAISlots<0>
{
};
class Object;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// What the path's 0x003642DF returns by value (16 bytes): a node and a
// position (as in AIUpdateInterfacePrivateCommands.cpp). Unnamed.
struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};
class Path
{
public:
	Rva003642DFResult rva003642DF(float dist);
};
class Pathfinder
{
public:
	bool IsBuildRestrictedCell(const Coord3D *pos, bool flagA, bool flagB, int layer);
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
class AIUpdateInterface : public AIDeadStateAISlots<136>
{
public:
	virtual void setLocomotorGoalNone() = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	Object *checkForCrateToPickup();
	Object *getNextMoodTarget(Bool calm, Bool alwaysAttack);
	Path *getPath() const { return m_path; }
private:
	unsigned char m_pad004[0x140 - 4];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x1F0 - 0x144];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3C7 - (0x1F0 + sizeof(Locomotor *))];
public:
	Bool m_flag3C7; // +0x3C7
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	void rva0028AE6D();
	float getBfmeRealB8() const { return m_bfmeRealB8; }
	unsigned char m_pad000[0xB8];
	float m_bfmeRealB8; // +0xB8
	unsigned char m_pad0BC[0x10C - 0xBC];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
};
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);
class Object0033FA79;
void Rva0033FA79Do(const Object0033FA79 *obj);
class StateMachine;
void rva003532BF(Object *owner, StateMachine *machine, bool flag);
class State;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType updateStateMachine();
	virtual void clear();
	virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(Object *object);
	Object *getOwner() const { return m_owner; }
	Bool isInIdleState() const;
private:
	State *m_currentState; // +0x4
	unsigned char m_pad08[0x14 - 8];
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
	virtual StateReturnType update();
	virtual void slot07();
	virtual Bool isIdle() const;
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual void computePath();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateMachine *getMachine() const { return m_machine; }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
// ?isInIdleState@StateMachine@@ present-unmatched
inline Bool StateMachine::isInIdleState() const
{
	return m_currentState ? m_currentState->isIdle() : true;
}
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};
class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
void AIMoveToState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
}
class AIAttackMoveToState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x54 - 0x1C];
	StateMachine *m_attackMoveMachine; // +0x54
};
void AIAttackMoveToState::onExit(StateExitType status)
{
	m_attackMoveMachine->setState(AI_IDLE);
	AIMoveToState::onExit(status);
}
class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	void computeGoal(Bool useGroupOffsets);
protected:
	unsigned char m_pad1C[0x65 - 0x1C];
	Bool m_moveAsGroup; // +0x65
};
void AIFollowWaypointPathState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	// turn off precision-z-pos when we exit, just in case.
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai && ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);
}
class AIAttackFollowWaypointPathState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	StateMachine *m_attackFollowMachine; // +0x68
};
StateReturnType AIAttackFollowWaypointPathState::onEnter()
{
	m_attackFollowMachine->clear();
	m_attackFollowMachine->setState(AI_IDLE);
	return AIFollowWaypointPathState::onEnter();
}
void AIAttackFollowWaypointPathState::onExit(StateExitType status)
{
	m_attackFollowMachine->setState(AI_IDLE);
	AIFollowWaypointPathState::onExit(status);
}
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);

StateReturnType AIAttackFollowWaypointPathState::update()
{
	Object *owner = m_machine->getOwner();
	AIUpdateInterface *ai = owner->getAI();

	Bool forceRetarget = false;
	Bool shouldRepath = false;
	Object *victim = 0;

	if (!m_attackFollowMachine->isInIdleState())
	{
		ai->setLocomotorGoalNone();

		clearModelConditionBit(owner, 61);
		clearModelConditionBit(owner, 156);

		m_attackFollowMachine->updateStateMachine();

		if (m_attackFollowMachine == 0 || !m_attackFollowMachine->isInIdleState())
			return STATE_CONTINUE;

		forceRetarget = true;
		shouldRepath = true;
	}

	if (m_attackFollowMachine->isInIdleState())
	{
		Object *crate = ai->checkForCrateToPickup();
		if (crate != 0)
		{
			m_attackFollowMachine->setGoalObject(crate);
			m_attackFollowMachine->setState(0x27);
			return STATE_CONTINUE;
		}

		victim = ai->getNextMoodTarget(!forceRetarget, false);
		if (victim != 0)
		{
			m_attackFollowMachine->setGoalObject(victim);
			m_attackFollowMachine->setState(0x0a);
			ai->m_flag3C7 = true;
			return STATE_CONTINUE;
		}
	}

	if (shouldRepath)
	{
		computeGoal(m_moveAsGroup);

		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log != 0)
				fprintf(log, "CritterDesync: ComputePath38");
		}

		computePath();
	}

	return AIFollowWaypointPathState::update();
}

class AIFollowWaypointPathStateAndEvacuate : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
StateReturnType AIFollowWaypointPathStateAndEvacuate::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIFollowWaypointPathState::onEnter();
}
void AIFollowWaypointPathStateAndEvacuate::onExit(StateExitType status)
{
	AIFollowWaypointPathState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}
StateReturnType AIFollowWaypointPathStateAndEvacuate::update()
{
	StateReturnType status = AIFollowWaypointPathState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8());
		if (!TheAI->pathfinder()->IsBuildRestrictedCell(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	if (status == STATE_SUCCESS)
		rva003532BF(owner, getMachine(), false);
	return status;
}
