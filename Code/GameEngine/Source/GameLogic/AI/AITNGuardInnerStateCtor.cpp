// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0AITNGuardInnerState@@QAE@PAVStateMachine@@@Z @0x00545D50 40B
// AITNGuardInnerState ctor: State(machine, 0xD405C261), vtable 0x00C6A140,
// exitConditions vtable 0x00C6A13C at +0x20 with giveUpFrame 0 at +0x24.
// Prev/next neighbours live in AITNGuardStates.cpp (same dir, // cl: /O1
// /DNDEBUG /MD /arch:SSE /EHsc); this unit uses the precedent
// AIStatesSmallUpdates.cpp flags (no /EHsc, same 40B ctor shape) plus a
// compiler barrier to pin the derived vptr store ahead of the body stores.
// Evidence: pinned State hash ctor 0x004D73FC, vtable slot 5 onExit 0x00545BB7,
// caller 0x005460D0, hash 0xD405C261.
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
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
struct TunnelNetworkExitConditions
{
	const void *m_vptr;
	UnsignedInt m_attackGiveUpFrame; // +0x04 (state +0x24)
};
extern const void *const g_00C6A13C[];
class AITNGuardMachine;
class AITNGuardInnerState : public State
{
public:
	AITNGuardInnerState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	Bool m_scanForEnemy; // +0x28
	void *m_attackState; // +0x2C
};

AITNGuardInnerState::AITNGuardInnerState(StateMachine *machine)
	: State(machine, 0xD405C261u)
{
	_ReadWriteBarrier();
	m_exitConditions.m_attackGiveUpFrame = 0;
	m_exitConditions.m_vptr = g_00C6A13C;
}
