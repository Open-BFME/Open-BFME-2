// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX-
// State::friend_checkForTransitions, retail 0x004D7148..0x004D722A (226 B,
// RET 4). Identity: the ledger's prior name for this address and its twin
// friend_checkForSleepTransitions 0x004D722A right after it (target evidence).
// Body follows the BFME1 donor (game/GameEngine/Source/Common/StateMachine.cpp)
// with BFME 2 deltas read from retail: success/failure ids at +0x08/+0x0C, the
// transition table as begin pointer and count at +0x10/+0x14, the machine at
// +0x18 read once ahead of the switch, and the function-static recursion
// counter at .data 0x00E043F8. As in the sleep twin, one result slot with a
// single exit gives retail's register roles; layout names are donor-carried.
typedef int Int;
typedef int StateID;
typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

enum
{
	MACHINE_DONE_STATE_ID = 999998
};

class StateMachine
{
public:
	StateReturnType internalSetState(StateID id);
};

class State;

typedef Bool (*StateTransFuncPtr)(State *state, void *userData);

struct StateConditionInfo
{
	StateTransFuncPtr test;		// +0x00
	StateID toStateID;			// +0x04
	void *userData;				// +0x08
};

class State
{
public:
	StateReturnType friend_checkForTransitions(StateReturnType status);

private:
	char m_pad00[0x08];
	StateID m_successStateID;			// +0x08
	StateID m_failureStateID;			// +0x0C
	const StateConditionInfo *m_transitionsFirst;	// +0x10
	Int m_transitionsCount;				// +0x14
	StateMachine *m_machine;			// +0x18
};

StateReturnType State::friend_checkForTransitions(StateReturnType status)
{
	static Int checkfortransitionsnum = 0;
	StateReturnType result;
	++checkfortransitionsnum;
	if (checkfortransitionsnum >= 20)
		result = STATE_FAILURE;
	else
	{
		result = STATE_CONTINUE;
		StateMachine *machine = m_machine;
		switch (status)
		{
		case STATE_SUCCESS:
			if (m_successStateID == EXIT_MACHINE_WITH_SUCCESS)
			{
				machine->internalSetState(MACHINE_DONE_STATE_ID);
				result = STATE_SUCCESS;
			}
			else if (m_successStateID == EXIT_MACHINE_WITH_FAILURE)
			{
				machine->internalSetState(MACHINE_DONE_STATE_ID);
				result = STATE_FAILURE;
			}
			else
				result = machine->internalSetState(m_successStateID);
			break;
		case STATE_FAILURE:
			if (m_failureStateID == EXIT_MACHINE_WITH_SUCCESS)
			{
				machine->internalSetState(MACHINE_DONE_STATE_ID);
				result = STATE_SUCCESS;
			}
			else if (m_failureStateID == EXIT_MACHINE_WITH_FAILURE)
			{
				machine->internalSetState(MACHINE_DONE_STATE_ID);
				result = STATE_FAILURE;
			}
			else
				result = machine->internalSetState(m_failureStateID);
			break;
		case STATE_CONTINUE:
		{
			Int n = m_transitionsCount;
			if (n != 0)
			{
				const StateConditionInfo *it = m_transitionsFirst;
				do
				{
					if (it->test(this, it->userData))
					{
						if (it->toStateID == EXIT_MACHINE_WITH_SUCCESS)
							result = STATE_SUCCESS;
						else if (it->toStateID == EXIT_MACHINE_WITH_FAILURE)
							result = STATE_FAILURE;
						else
							result = machine->internalSetState(it->toStateID);
						break;
					}
					++it;
				} while (--n);
			}
			break;
		}
		}
	}
	--checkfortransitionsnum;
	return result;
}
