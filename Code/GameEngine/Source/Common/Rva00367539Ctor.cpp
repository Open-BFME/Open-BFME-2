// cl: /MD
// ??0GiantBirdNormalFlightState@@QAE@PAVStateMachine@@_N1@Z @0x00367539 43B
// (was Rva00367539: vtable 0x00C17300's slots 4-6 are the rowed
// GiantBirdNormalFlightState onEnter/onExit/update bodies)
// State-derived ctor hash 0x815D9F7C vtable 0x00817300 plus bool at +0x20
// plus bool at +0x21. Evidence: callers 8 unclaimed sites; rowed State
// base 0x004D73FC via I twin ??0State@@QAE@PAVStateMachine@@I@Z; precedent
// Rva00367647Ctor.cpp (State hash plus bool) and Rva0033F6DA hash-plus-vtable.
class StateMachine;

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
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};

// Rva00367539_vftable: matched references place it at VA 0xc17300 (retail .rdata value 7).
extern "C" char Rva00367539_vftable = 7;

class __declspec(novtable) GiantBirdNormalFlightState : public State
{
public:
	GiantBirdNormalFlightState(StateMachine *machine, bool b1, bool b2);
private:
	bool m_20;
	bool m_21;
};

GiantBirdNormalFlightState::GiantBirdNormalFlightState(StateMachine *machine, bool b1, bool b2) : State(machine, 0x815D9F7Cu)
{
	m_20 = b1;
	m_21 = b2;
	*reinterpret_cast<char **>(this) = &Rva00367539_vftable;
}
