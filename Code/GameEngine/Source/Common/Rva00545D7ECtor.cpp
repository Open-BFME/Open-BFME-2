// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0Rva00545D7E@@QAE@PAVStateMachine@@@Z @ 0x00545D7E 44B
// State-derived ctor: State(machine, 0xCDECC1F9), vtable 0x00C6A198,
// exitConditions vtable 0x00C6A13C at +0x20 with +0x24 zero and +0x28 zero.
// Evidence: sibling AITNGuardAttackAggressorState ctor pattern; callee pin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC; caller 0x00546108.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
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
	StateID m_ID;
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine;
};
struct Rva00545D7EExitConditions
{
	const void *m_vptr;
	UnsignedInt m_04;
};
extern const void *const g_00C6A198[];
extern const void *const g_00C6A13C[];
class Rva00545D7E : public State
{
public:
	Rva00545D7E(StateMachine *machine);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Rva00545D7EExitConditions m_exit;
	void *m_28;
};
Rva00545D7E::Rva00545D7E(StateMachine *machine)
	: State(machine, 0xCDECC1F9u)
{
	_ReadWriteBarrier();
	m_exit.m_04 = 0;
	m_exit.m_vptr = g_00C6A13C;
	_ReadWriteBarrier();
	m_28 = 0;
}
