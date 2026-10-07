// cl: /O1 /arch:SSE /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??1Rva004D759C@@UAE@XZ, 0x004D759C, 139 bytes.
// Identity: the matched ctor uses vtable 0x00C60740; derived dtor callers tail-jump here.
// State cleanup semantics follow the Zero Hour StateMachine donor; target member offsets come from Rva004D759CCtor.cpp.
#include <map>
#include "Common/Snapshot.h"

class State
{
public:
	virtual void *deleteInstance(int flags);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void onExit(int reason);
};

struct Rva004D755FRecord
{
	State *state;
};

class Rva004D759C : public Snapshot
{
public:
	virtual void crc(Xfer *) {}
	virtual void loadPostProcess() {}
	virtual void xfer(Xfer *) {}
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual ~Rva004D759C();

	void *m_currentState;
	_STL::map<int, Rva004D755FRecord> m_stateMap;
	char m_ownerAndPad[8];
	int m_defaultStateID;
};

Rva004D759C::~Rva004D759C()
{
	if (m_currentState)
		((State *)m_currentState)->onExit(1);

	_STL::map<int, Rva004D755FRecord>::iterator i;
	for (i = m_stateMap.begin(); i != m_stateMap.end(); ++i)
	{
		State *state = (*i).second.state;
		if (state)
			::operator delete(state->deleteInstance(0));
	}
	m_stateMap.clear();
	m_currentState = 0;
	m_defaultStateID = 999999;
}
