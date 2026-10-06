// cl: /MD
// ?rva004D7127@State@@QAEXPBUStateConditionInfo@@@Z at retail 0x004D7127 (33B).
// State transitions array setter called by StateMachine::defineState 0x004D7B0F.
// Evidence: caller 0x004D7B0F stores id/success/failure then calls here with conditions;
// +0x10/+0x14 match StateCtor layout and friend_checkForTransitions 0x004D7148 count loop;
// stride 0xC matches StateConditionInfo (test/toState/userData) null-terminated.

class StateMachine;

struct StateConditionInfo
{
	void *test;
	int toStateID;
	void *userData;
};

class __declspec(novtable) State
{
public:
	virtual ~State();
	int m_id; // +0x04
	int m_successStateID; // +0x08
	int m_failureStateID; // +0x0C
	const StateConditionInfo *m_transitionsFirst; // +0x10
	int m_transitionsCount; // +0x14
	StateMachine *m_machine; // +0x18
	bool m_tail1C; // +0x1C

	void rva004D7127(const StateConditionInfo *conditions);
};

void State::rva004D7127(const StateConditionInfo *conditions)
{
	if (!conditions)
		return;
	if (!conditions->test)
		return;
	m_transitionsFirst = conditions;
	const StateConditionInfo *p = conditions;
	int n = 0;
	do {
		++p;
		++n;
	} while (p->test != 0);
	m_transitionsCount = n;
}
