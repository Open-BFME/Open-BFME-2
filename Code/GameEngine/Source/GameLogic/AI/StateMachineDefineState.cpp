// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// ?defineState@StateMachine@@QAEXIPAVState@@IIPBUStateConditionInfo@@@Z at retail 0x004D7B0F (97B).
// StateMachine::defineState: map id->state at +0x08 then State ids at +0x04/+0x08/+0x0C
// then transitions via rowed State::rva004D7127 0x004D7127 then default 999999 at +0x1C
// then terminal flag at State+0x1C when id==success==failure.
// Evidence: BFME1 donor StateMachine.cpp defineState verbatim minus debug plus BFME2
// transitions-array setter; 40+ callers at 0x003431CA 0x00343204 0x003433FA; layout from
// StateMachineGoal.cpp (+0x08 map +0x1C default) and StateCtor.cpp (+0x04/+0x08/+0x0C/+0x1C).
// The State map's tree helpers are retail's bfmealloc bodies: insert_unique 0x004D795B
// (the _BFME_RETAIL_TREE_INSERT_LAYOUT begin() path), _M_insert 0x004D9C49 and the
// 34-byte node creator 0x00382B7F, each shared by ICF with other unsigned-key maps.
#include <map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }

typedef unsigned int UnsignedInt;
typedef unsigned int StateID;
typedef int Int;
typedef bool Bool;

enum { INVALID_STATE_ID = 999999 };

#include "../../../Include/Common/StateConditionInfo.h"

class StateMachine;

class State
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	int m_id; // +0x04 (after vptr at +0x00)
	int m_successStateID; // +0x08
	int m_failureStateID; // +0x0C
	const StateConditionInfo *m_transitionsFirst; // +0x10
	int m_transitionsCount; // +0x14
	StateMachine *m_machine; // +0x18
	bool m_tail1C; // +0x1C

	void rva004D7127(const StateConditionInfo *conditions);
};

class StateMachine
{
public:
	unsigned char m_pad00[0x04];
	void *m_currentState; // +0x04
	_STL::map<StateID, State *> m_stateMap; // +0x08
	unsigned char m_pad14[0x18 - 0x14];
	UnsignedInt m_sleepTill; // +0x18
	StateID m_defaultStateID; // +0x1C
	int m_goalObjectID; // +0x20
	unsigned char m_pad24[0x38 - 0x24];
	bool m_locked; // +0x38
	bool m_defaultStateInited; // +0x39

	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions);
};

void StateMachine::defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions)
{
	m_stateMap.insert(_STL::map<StateID, State *>::value_type(id, state));
	state->m_id = id;
	state->m_successStateID = successID;
	state->m_failureStateID = failureID;
	state->rva004D7127(conditions);
	if (m_defaultStateID == INVALID_STATE_ID)
		m_defaultStateID = id;
	if (id == successID && id == failureID)
		state->m_tail1C = true;
}
