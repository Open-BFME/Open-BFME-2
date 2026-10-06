// cl: /DNDEBUG /MD
//
// ?rva00260DED@AIUpdateInterface@@QBEHXZ, retail 0x00260DED, 20 bytes.
// AI state-machine current-ID getter: machine at +0x30, current state at
// machine+0x04, state id at state+0x04, INVALID 999999 (0xF423F) fallback.
// Evidence: donor StateMachine.h getCurrentStateID inline with
// INVALID_STATE_ID 999999; sibling AIUpdateInterface_rva002630FD proves
// AI+0x30 machine and +0x04/+0x04 chase; callers compare result to AIStateType
// values (0x21 FACE_OBJECT at 0x00261546/0x0026D404, 0x2A EXIT_INSTANTLY at
// 0x0026D114, 0x13 PANIC inline at 0x0026D003, 0x3E at 0x0034402F).

enum { INVALID_STATE_ID = 999999 };

class MiniState
{
public:
	virtual void s0();
	int m_id;
	int getID() const { return m_id; }
};

class MiniMachine
{
public:
	virtual void s0();
	MiniState *m_currentState;
	int getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	MiniMachine *m_machine;
public:
	int rva00260DED() const;
};

int AIUpdateInterface::rva00260DED() const
{
	return m_machine->getCurrentStateID();
}
