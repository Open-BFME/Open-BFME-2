// cl: /MD /EHs
// ??1AIStateMachine@@UAE@XZ retail 0x003516F3 96B
// Own vptr C14CD0; under EH state 1 the object at +0x4C is deleted through
// its slot-0 deleting dtor with flag 0 and the global ??3@YAXPAX@Z (a
// global-scope delete) and cleared when non-null; under state 0 the buffer member at +0x3C
// runs its inline dtor (CRT free of its block); then the rowed base dtor
// ??1StateMachine@@UAE@XZ 0x004D759C runs.
// Identity: vtable 0x00C14CD0 is the one the rowed AIStateMachine
// constructor 0x00351C48 installs (store at 0x00351C75); its slot 0 is the
// scalar deleting dtor 0x00352B25 that calls this body, slot 2 0x00351753
// returns the name string "AIStateMachine" (0x00814D10) and slots 3-6 and 8
// are the rowed AIStateMachine xfer / updateStateMachine / clear /
// resetToDefaultState / setState. The member views stay address-named.

extern "C" void __cdecl free(void *block);

class StateMachine
{
public:
	virtual ~StateMachine();

private:
	unsigned char m_pad04[0x3C - 4];
};

class Rva003516F3Owned
{
public:
	virtual ~Rva003516F3Owned();
};

class Rva003516F3Buffer
{
public:
	~Rva003516F3Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data; // +0x00
};

class AIStateMachine : public StateMachine
{
public:
	virtual ~AIStateMachine();

private:
	Rva003516F3Buffer m_buffer; // +0x3C
	unsigned char m_pad40[0x4C - 0x40];
	Rva003516F3Owned *m_owned; // +0x4C
};

AIStateMachine::~AIStateMachine()
{
	if (m_owned)
	{
		::delete m_owned;
		m_owned = 0;
	}
}
