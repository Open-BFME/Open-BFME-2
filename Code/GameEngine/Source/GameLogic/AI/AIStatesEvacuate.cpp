// cl: /DNDEBUG /MD
//
// The evacuate AI states' enter/exit overrides. Each class is identified by
// its vtable's slot-2 name getter (the state's own name literal):
//
//   0x00C12D50 "AIMoveToAndEvacuateState" (getter 0x00342E11): slot 4
//     onEnter 0x003500E6 (banked near miss, not here), slot 5 onExit
//     0x0034C098 (28 B), slot 6 update 0x00354AB6 (not here). The same
//     three slots fill 0x00C12DB8 "AIAttackMoveToAndEvacuateState" (getter 0x00342E2F), which therefore
//     overrides none of them.
//   0x00C13108 "AIMoveForBoarding" (getter 0x0034308F): slot 4 onEnter
//     0x00350164 (23 B); slot 5 is the same onExit 0x0034C098.
//   0x00C12E28 "AIFollowPathAndEvacuateState" (getter 0x00342E52): slot 4
//     onEnter 0x0035014D (23 B), slot 5 onExit 0x0034C0B4 (28 B).
//
// Target evidence: the enter overrides call Rva0033FA64Do (0x0033FA64) on the
// machine owner before the base onEnter (the pinned AIMoveToState::onEnter
// 0x0034C7BD, or the rowed AIFollowPathState::onEnter 0x0034DEF8, as a tail
// jump); the exit overrides call the base onExit (the rowed
// AIInternalMoveToState::onExit 0x003473A4 directly, or
// AIFollowPathState::onExit 0x00349D92) and then Rva0033FA79Do (0x0033FA79)
// on the owner, as the matched AIFollowWaypointPathStateAndEvacuate pair
// does. The class derivations are inferred from the shared slots and the
// base calls.
//
// The two update slots, AIMoveToAndEvacuateState 0x00354AB6 (142 B) and
// AIMoveForBoarding 0x00354CAD (96 B), run the pinned AIMoveToState::update
// (0x00353A65) and then succeed once the point of the AI's path (+0x140) at
// the owner's +0xB8 distance (times 0.9 for the evacuate state) fails the
// pathfinder's cell test 0x002E996E; on success the evacuate state also
// hands the owner and machine to the helper 0x003532BF with its slot-18
// Bool. Callees pinned by address.

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

struct Coord3D
{
	float x, y, z;
};

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
	bool rva002E996E(const Coord3D *pos, bool flagA, bool flagB, int layer);
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

class AIUpdateInterface
{
public:
	Path *getPath() const { return m_path; }
private:
	unsigned char m_pad000[0x140];
	Path *m_path; // +0x140
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	float getBfmeRealB8() const { return m_bfmeRealB8; }
private:
	unsigned char m_pad000[0xB8];
	float m_bfmeRealB8; // +0xB8
	unsigned char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine;
void rva003532BF(Object *owner, StateMachine *machine, bool flag);

class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);
class Object0033FA79;
void Rva0033FA79Do(const Object0033FA79 *obj);

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
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
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual bool rva00354B2ESlot18();
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

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

class AIMoveToAndEvacuateState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

void AIMoveToAndEvacuateState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}

StateReturnType AIMoveToAndEvacuateState::update()
{
	StateReturnType status = AIMoveToState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8() * 0.9f);
		if (!TheAI->pathfinder()->rva002E996E(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	if (status == STATE_SUCCESS)
		rva003532BF(owner, getMachine(), rva00354B2ESlot18());
	return status;
}

class AIMoveForBoarding : public AIMoveToAndEvacuateState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};

StateReturnType AIMoveForBoarding::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIMoveToState::onEnter();
}

StateReturnType AIMoveForBoarding::update()
{
	StateReturnType status = AIMoveToState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8());
		if (!TheAI->pathfinder()->rva002E996E(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	return status;
}

class AIFollowPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

class AIFollowPathAndEvacuateState : public AIFollowPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

StateReturnType AIFollowPathAndEvacuateState::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIFollowPathState::onEnter();
}

void AIFollowPathAndEvacuateState::onExit(StateExitType status)
{
	AIFollowPathState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}
