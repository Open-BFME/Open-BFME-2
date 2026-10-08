// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1StateMachine@@UAE@XZ, retail 0x004D759C (139B, EH frame).
// Zero Hour StateMachine::~StateMachine plus BFME2's reset tail: exit the
// current state with EXIT_RESET (vtable slot 5, argument 1), delete every
// state held in the map, clear the map, then null the current state and set
// the default state id to INVALID_STATE_ID (999999 = 0xF423F). Target
// evidence: the vptr store of vftable 0x00C60740 (the base of the 20
// derived machine vtables, see StateMachineRva004D750F.cpp), the map walk
// via _M_increment 0x00024250 over the +0x08 tree, the clear 0x004D751D and
// tree destructor 0x004D755F of the state map (StateID = unsigned int), and the
// Snapshot vptr 0x00BBB554 restored last. The scalar deleting destructor
// ??_GStateMachine (retail 0x004D7A59, 28B) is emitted here with the vftable.
#include <map>
#include "Common/Snapshot.h"

class State
{
public:
	virtual ~State();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void onExit(int status);	// slot 5
};

enum
{
	EXIT_RESET = 1,
	INVALID_STATE_ID = 999999
};

class StateMachine : public Snapshot
{
public:
	virtual ~StateMachine();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	State *m_currentState;				// +0x04
	_STL::map<unsigned int, State *> m_stateMap;	// +0x08
	int m_pad14[2];
	unsigned int m_defaultStateID;		// +0x1C
};

StateMachine::~StateMachine()
{
	if (m_currentState)
		m_currentState->onExit(EXIT_RESET);

	for (_STL::map<unsigned int, State *>::iterator i = m_stateMap.begin(); i != m_stateMap.end(); ++i)
	{
		if ((*i).second)
			::delete (*i).second;
	}
	m_stateMap.clear();
	m_currentState = 0;
	m_defaultStateID = INVALID_STATE_ID;
}
