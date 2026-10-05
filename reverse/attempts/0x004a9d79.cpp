// ??0Rva004A9D79@@QAE@PAVObject@@@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /MD /EHsc
// ??0Rva004A9D79@@QAE@PAVObject@@@Z retail 0x004A9D79 (169B).
// class-gate: allow AsciiString retail 0x004A9D79 pushes hash 0xF80D13C5 as POD with no ctor/dtor calls, shared header adds releaseBuffer ctor/dtor.
// StateMachine-family ctor: base Rva004D759C 0x004D79E1 with hash 0xF80D13C5,
// vtable 0x00854058, then two single-arg State children Rva004A992A and
// Rva004A9947 via new plus defineState 0x004D7B0F with cond globals.
// Evidence: caller 0x004A9F08 in 0x004A9ED5, new 0x20, ret 4 with mov eax edi
// proving ctor, ids 0/1 success and failure 0xF423F, same prolog as 0x004885DE.

class Object;
class StateMachine;

class AsciiString
{
public:
	AsciiString(void *p) { m_data = p; }
	void *m_data;
};

struct StateConditionInfo
{
	void *test;
	unsigned int toStateID;
	void *userData;
};

class StateMachine
{
public:
	void defineState(unsigned int id, struct State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions);
};

struct State
{
public:
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
};

class Rva004D759C
{
public:
	Rva004D759C(Object *owner, AsciiString name, bool flag);
	virtual ~Rva004D759C();
};

class Rva004A992A : public State
{
public:
	Rva004A992A(StateMachine *machine);
};

class Rva004A9947 : public State
{
public:
	Rva004A9947(StateMachine *machine);
};

extern const StateConditionInfo g_00C54410[];
extern const StateConditionInfo g_00C543F8[];

class Rva004A9D79 : public Rva004D759C
{
public:
	Rva004A9D79(Object *owner);
};

// ??0Rva004A9D79@@QAE@PAVObject@@@Z present-unmatched
Rva004A9D79::Rva004A9D79(Object *owner)
	: Rva004D759C(owner, AsciiString((void *)0xF80D13C5), false)
{
	StateMachine *machine = (StateMachine *)this;
	State *s0 = new Rva004A992A(machine);
	((StateMachine *)this)->defineState(0, s0, 0xF423F, 0xF423F, g_00C54410);
	State *s1 = new Rva004A9947(machine);
	((StateMachine *)this)->defineState(1, s1, 0xF423F, 0xF423F, g_00C543F8);
}
