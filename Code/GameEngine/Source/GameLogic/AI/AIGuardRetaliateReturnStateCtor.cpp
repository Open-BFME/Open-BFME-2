// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0AIGuardRetaliateReturnState@@QAE@PAVStateMachine@@@Z @0x005453BB 33B
// AIGuardRetaliateReturnState ctor: AIInternalMoveToState(machine,
// 0xC784A170), vtable 0x00C69F38, m_nextReturnScanTime 0 at +0x4C.
// Sibling of the landed AITNGuard ctors (same State-hash ctor shape with
// the base hash passed through); no barrier (retail keeps the body and
// ahead of the derived vptr store). Layout copied from
// AIGuardRetaliateStates.cpp (goal +0x20, adjusts +0x48, nextScan +0x4C).
// Evidence: pinned AIInternalMoveToState ctor 0x0033F279, vtable slots 4/6
// onEnter 0x005452CB update 0x0054574D, caller 0x005455AF, hash 0xC784A170.
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class StateMachine
{
public:
	virtual ~StateMachine();
};
class State
{
public:
	virtual ~State();
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};
class AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
	AIGuardRetaliateReturnState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	UnsignedInt m_nextReturnScanTime; // +0x4C
};

AIGuardRetaliateReturnState::AIGuardRetaliateReturnState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xC784A170u)
{
	m_nextReturnScanTime = 0;
}
