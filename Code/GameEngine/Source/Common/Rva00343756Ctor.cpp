// cl: /O1 /MD /EHsc
// ??0Rva00343756@@QAE@PAVObject@@HVAsciiString@@@Z @0x00343756 198B
// class-gate: allow AsciiString retail pushes single dword for VAsciiString (0x00343756 base 0x004D79E1); shared header emits copy lea and breaks prolog
// Derived StateMachine ctor: base Rva004D759C with (owner, name, false),
// vtable, two states (500/501) via new 0x28/0x20 and defineState.
// Evidence: calls rowed base 0x004D79E1, new 0x0002FDA0, state ctors
// 0x0033F483/0x0033F43D, defineState 0x004D7B0F; vtable store; int arg at
// +0xC transformed to 0 or +0x20; ids 0x1F4/0x1F5/0x270F; cond 0x00C13164.

class Object;

class AsciiString
{
public:
	void *m_data;
};

struct StateConditionInfo
{
	void *test;
	unsigned int toStateID;
	void *userData;
};

struct State
{
	virtual ~State();
	char m_pad[0x20 - 4];
};

class StateMachine;

class Rva004D759C
{
public:
	Rva004D759C(Object *owner, AsciiString name, bool flag);
	virtual ~Rva004D759C();
};

class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int arg);

private:
	int m_20;
	int m_24;
};

class Rva0033F43D : public State
{
public:
	Rva0033F43D(StateMachine *machine);
};

class StateMachine
{
public:
	void defineState(unsigned int id, State *state, unsigned int successID,
		unsigned int failureID, const StateConditionInfo *conditions);
};

extern const StateConditionInfo g_00C13164[];
extern const void *const g_00C11BD0[];

class Rva00343756 : public Rva004D759C
{
public:
	Rva00343756(Object *owner, int val, AsciiString name);
};

extern void *__cdecl operator new(unsigned int size);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

Rva00343756::Rva00343756(Object *owner, int val, AsciiString name)
	: Rva004D759C(owner, name, false)
{
	State *s1 = new Rva0033F483((StateMachine *)(void *)this, val ? val + 0x20 : 0);
	((StateMachine *)(void *)this)->defineState(0x1F4, s1, 0x1F5, 0x270F, g_00C13164);
	State *s2 = new Rva0033F43D((StateMachine *)(void *)this);
	((StateMachine *)(void *)this)->defineState(0x1F5, s2, 0x1F4, 0x270F, g_00C13164);
}
