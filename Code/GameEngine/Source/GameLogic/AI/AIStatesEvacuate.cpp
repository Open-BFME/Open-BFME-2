// cl: /O1 /DNDEBUG /MD /arch:SSE
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

class Object;

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
protected:
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
};

class AIMoveToAndEvacuateState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIMoveToAndEvacuateState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}

class AIMoveForBoarding : public AIMoveToAndEvacuateState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIMoveForBoarding::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIMoveToState::onEnter();
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
