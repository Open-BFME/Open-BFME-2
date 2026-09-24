// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
// partial score=0.7 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /GX-
//
// ?friend_checkForTransitions@State@@QAE?AW4StateReturnType@@?AW4StateReturnType@@@Z,
// retail 0x004D7148, 226 bytes. Dedicated TU for the State transition
// walkers: the normal walker with its own recursion guard.
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/
// StateMachine.cpp, State::friend_checkForTransitions): the twin static
// guards count normal and sleep recursion independently, the SUCCESS and
// FAILURE arms consult their stored ids against the machine-exit codes
// with a shared machine-done tail, and the CONTINUE arm walks the
// transition table calling each test until one fires. BFME2 deltas: the
// table is a begin pointer plus a count (not std::vector iterators), the
// ids live at +0x08/+0x0c, the table at +0x10/+0x14, the machine at +0x18.

typedef int Int;
typedef int StateID;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	MACHINE_DONE_STATE_ID = 999998,
	INVALID_STATE_ID = 999999
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

class StateMachine
{
public:
	StateReturnType internalSetState(StateID id);
};

typedef Bool (*StateTransFuncPtr)(class State *state, void *userData);

struct StateTransition
{
	StateTransFuncPtr test;
	StateID toState;
	void *userData;
};

class State
{
public:
	unsigned char m_pad00[0x08];
	StateID m_successStateID; // +0x08
	StateID m_failureStateID; // +0x0c
	StateTransition *m_transitions; // +0x10
	Int m_numTransitions; // +0x14
	StateMachine *m_machine; // +0x18

	StateReturnType friend_checkForTransitions(StateReturnType status);
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);
};

struct StIncrementer
{
	StIncrementer(Int &n) : m_num(n) { ++m_num; }
	~StIncrementer() { --m_num; }
	Int &m_num;
};

static Int s_checkForTransitionsNum = 0;

// ?friend_checkForTransitions@State@@QAE?AW4StateReturnType@@?AW4StateReturnType@@@Z
StateReturnType State::friend_checkForTransitions(StateReturnType status)
{
	StIncrementer inc(s_checkForTransitionsNum);
	if (s_checkForTransitionsNum >= 20)
		return STATE_FAILURE;

	StateMachine *machine = m_machine;
	StateReturnType result = STATE_CONTINUE;

	if (status == STATE_FAILURE) {
		StateID id = m_failureStateID;
		if (id == EXIT_MACHINE_WITH_SUCCESS) {
			machine->internalSetState(MACHINE_DONE_STATE_ID);
			return STATE_SUCCESS;
		} else if (id == EXIT_MACHINE_WITH_FAILURE) {
			machine->internalSetState(MACHINE_DONE_STATE_ID);
			return STATE_FAILURE;
		}
		return machine->internalSetState(id);
	} else if (status == STATE_SUCCESS) {
		StateID id = m_successStateID;
		if (id == EXIT_MACHINE_WITH_SUCCESS) {
			machine->internalSetState(MACHINE_DONE_STATE_ID);
			return STATE_SUCCESS;
		} else if (id == EXIT_MACHINE_WITH_FAILURE) {
			machine->internalSetState(MACHINE_DONE_STATE_ID);
			return STATE_FAILURE;
		}
		return machine->internalSetState(id);
	} else if (status != STATE_CONTINUE) {
		return result;
	}

	// check transition condition list
	StateTransition *trans = m_transitions;
	Int remaining = m_numTransitions;
	if (remaining == 0)
		return result;
	do {
		if (trans->test(this, trans->userData)) {
			StateID to = trans->toState;
			if (to == EXIT_MACHINE_WITH_SUCCESS)
				return STATE_SUCCESS;
			if (to == EXIT_MACHINE_WITH_FAILURE)
				return STATE_FAILURE;
			result = machine->internalSetState(to);
			return result;
		}
		trans++;
	} while (--remaining);

	return result;
}

static Int s_checkForSleepTransitionsNum = 0;

// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
StateReturnType State::friend_checkForSleepTransitions(StateReturnType status)
{
	StIncrementer inc(s_checkForSleepTransitionsNum);
	if (s_checkForSleepTransitionsNum >= 20)
		return STATE_FAILURE;

	StateReturnType result = status;

	// check transition condition list
	StateTransition *trans = m_transitions;
	Int remaining = m_numTransitions;
	if (remaining == 0)
		return result;
	do {
		if (trans->test(this, trans->userData)) {
			StateID to = trans->toState;
			if (to == EXIT_MACHINE_WITH_SUCCESS)
				result = STATE_SUCCESS;
			else if (to == EXIT_MACHINE_WITH_FAILURE)
				result = STATE_FAILURE;
			else
				result = m_machine->internalSetState(to);
			break;
		}
		trans++;
	} while (--remaining);

	return result;
}
