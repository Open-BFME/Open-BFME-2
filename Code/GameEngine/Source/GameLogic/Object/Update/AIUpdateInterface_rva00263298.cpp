// cl: /DNDEBUG /MD
//
// ?rva00263298@AIUpdateInterface@@QAEXXZ, retail 0x00263298, 27 bytes.
// AIUpdateInterface notifier: machine at +0x30, state ptr at +0x50 with id
// at +4, gate on +0x54 == -1, then rowed AIStateMachine::setTemporaryState(id, -2).
// Evidence: neighbours rva0026320D/rva002632B3 share +0x30 machine and
// +0x50 state layout; caller 0x004DCECE.

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };

class AIStateMachine
{
public:
	StateReturnType setTemporaryState(unsigned int state, int frameLimit);
};

class RetState
{
public:
	virtual void v00();
	int m_id;
};

class Machine
{
public:
	char m_pad00[0x50];
	RetState *m_state50;
	int m_field54;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	Machine *m_machine;
public:
	void rva00263298();
};

void AIUpdateInterface::rva00263298()
{
	Machine *machine = m_machine;
	RetState *state = machine->m_state50;
	if (!state)
		return;
	if (machine->m_field54 != -1)
		return;
	((AIStateMachine *)machine)->setTemporaryState(state->m_id, -2);
}
