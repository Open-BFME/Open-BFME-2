// cl: /MD
// ?update@AIGuardState@@UAE?AW4StateReturnType@@XZ @0x00341DFC 38B: AIGuardState slot 6.
// If m_20==0 return -2 else set m_machine+0x38 to 1 then call m_20 slot 0x10 then clear m_machine+0x38 and return result.
// Precedent State m_machine plus Snapshot slot shape.
// Vtable 0x00C11740 slot 6. That vtable is AIGuardState's: its slot-2 name
// getter returns "AIGuardState" and slots 4/8 are the rowed
// AIGuardState::onEnter/isAttack. WorldBuilder's AIGuardState::update (vtable
// lead) has the same shape: no guard machine -> STATE_FAILURE, else raise the
// machine flag at +0x38, run the guard machine's slot 0x10, lower the flag.
class StateMachine;
class Snapshot;
enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
class M20
{
public:
	virtual ~M20();
	virtual void p1();
	virtual void p2();
	virtual void p3();
	virtual StateReturnType v4();
};
struct Mach
{
	char m_pad00[0x38];
	bool m_38;
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	Mach *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
class AIGuardState : public State
{
public:
	virtual StateReturnType update();
private:
	M20 *m_20;
};
StateReturnType AIGuardState::update()
{
	if (m_20 == 0)
		return STATE_FAILURE;
	m_machine->m_38 = true;
	StateReturnType r = m_20->v4();
	m_machine->m_38 = false;
	return r;
}
