// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX-
// State::friend_checkForSleepTransitions, retail 0x004D722A..0x004D729D (115 B,
// RET 4). Identity: the symbols.csv pin and the WorldBuilder twin in EA's
// StateMachine.cpp (target evidence). Body follows the BFME1 donor
// (game/GameEngine/Source/Common/StateMachine.cpp) with BFME 2 deltas read from
// retail: the transition table is a begin pointer and count at +0x10/+0x14
// (counted down once, not re-read per iteration), the machine is at +0x18 and
// the function-static recursion counter is .data 0x00E043FC. The single result
// slot with one exit and the machine read ahead of the exit-id compares are
// what give retail's EBX/EBP/ESI/EDI roles; layout names are donor-carried.
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
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);

private:
	char m_pad00[0x10];
	const StateConditionInfo *m_transitionsFirst;	// +0x10
	Int m_transitionsCount;				// +0x14
	StateMachine *m_machine;			// +0x18
};

StateReturnType State::friend_checkForSleepTransitions(StateReturnType status)
{
	static Int checkfortransitionsnum = 0;
	StateReturnType result;
	++checkfortransitionsnum;
	if (checkfortransitionsnum >= 20)
		result = STATE_FAILURE;
	else
	{
		result = status;
		Int n = m_transitionsCount;
		if (n != 0)
		{
			const StateConditionInfo *it = m_transitionsFirst;
			do
			{
				if (it->test(this, it->userData))
				{
					StateMachine *machine = m_machine;
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
	}
	--checkfortransitionsnum;
	return result;
}
