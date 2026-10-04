// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0AITNGuardAttackAggressorState@@QAE@PAVStateMachine@@@Z @0x00545E80 44B
// AITNGuardAttackAggressorState ctor: State(machine, 0x33E96013), vtable
// 0x00C6A298, exitConditions vtable 0x00C6A13C at +0x20 with giveUpFrame 0
// at +0x24, m_attackState 0 at +0x28. Sibling of AITNGuardInnerState ctor
// 0x00545D50 (same file family, same State hash pattern, same barrier to
// pin the derived vptr store ahead of the body stores).
// Evidence: pinned State hash ctor 0x004D73FC, vtable slot 5 onExit
// 0x00545CF7 slot 6 update 0x0054684E, caller 0x00546172, hash 0x33E96013.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
class StateMachine
{
public:
	virtual ~StateMachine();
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};
struct TunnelNetworkExitConditions
{
	const void *m_vptr;
	UnsignedInt m_attackGiveUpFrame; // +0x04 (state +0x24)
};
extern const void *const g_00C6A13C[];
class AITNGuardAttackAggressorState : public State
{
public:
	AITNGuardAttackAggressorState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	void *m_attackState; // +0x28
};

AITNGuardAttackAggressorState::AITNGuardAttackAggressorState(StateMachine *machine)
	: State(machine, 0x33E96013u)
{
	_ReadWriteBarrier();
	m_exitConditions.m_attackGiveUpFrame = 0;
	m_exitConditions.m_vptr = g_00C6A13C;
	_ReadWriteBarrier();
	m_attackState = 0;
}
