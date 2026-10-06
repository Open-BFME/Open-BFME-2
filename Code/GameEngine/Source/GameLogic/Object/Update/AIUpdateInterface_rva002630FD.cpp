// cl: /DNDEBUG /MD
//
// ?rva002630FD@AIUpdateInterface@@MAEXH@Z, retail 0x002630FD, 54 bytes.
// Vtable slot 84 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// if state machine at +0x30 current id is 0x2D skip else clear via slot 0x14
// store int at +0x48 then setState 0x2D via slot 0x20. No direct callees.

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
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void clear();
	virtual void s6();
	virtual void s7();
	virtual int setState(int id);
	MiniState *m_currentState;
	int getCurrentStateID() const { return m_currentState ? m_currentState->getID() : 0xF423F; }
};

class AIUpdateInterface
{
	char m_pad00[0x30 - 4];
	MiniMachine *m_machine;
	char m_pad34[0x48 - 0x34];
	int m_field48;
protected:
	virtual void rva002630FD(int val);
};

void AIUpdateInterface::rva002630FD(int val)
{
	if (m_machine->getCurrentStateID() == 0x2D)
		return;
	m_machine->clear();
	m_field48 = val;
	m_machine->setState(0x2D);
}
