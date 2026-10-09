// cl: /DNDEBUG /MD /EHsc
// ??0Rva0034316A@@QAE@PAVObject@@HI@Z @0x0034316A 481B.
// Name is a scalar hash: factory 34B1E9 pushes an immediate key, with no
// string construction or destruction. Keep the established host-word view.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// Rva004D759C from (owner, name, false), stores vtable g_00C11AC0, then
// defines seven states via the rowed StateMachine::defineState. Each state
// is a new-expression into a dead param slot ([ebp+0x10], then [ebp+0xC]
// after the int param dies), null-checked once, with the post-call eax
// feeding defineState directly (B952-family courtesy-eax shape, no reload).
// The 0xE1 word and the zero CSE into esi/ebx; blocks 2 and 5 pass the
// branchless (x ? x+0x20 : 0) selector for the int-typed state ctors.
class Object;
struct State;
struct StateConditionInfo;

class StateMachine
{
public:
	void defineState(unsigned int id, State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions);
};

class Rva004D759C
{
public:
	Rva004D759C(Object *owner, unsigned int name, bool flag);
	virtual ~Rva004D759C();
};

class Rva00342A96
{
public:
	Rva00342A96(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x64 - 4];
};

class Rva00342AD6
{
public:
	Rva00342AD6(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x68 - 4];
};

class Rva00342B1A
{
public:
	Rva00342B1A(StateMachine *machine, int val);
private:
	void *m_vtbl;
	char m_pad[0x78 - 4];
};

class Rva0033F627
{
public:
	Rva0033F627(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x24 - 4];
};

class Rva0033F3B6
{
public:
	Rva0033F3B6(StateMachine *machine, bool arg0, bool arg1);
private:
	void *m_vtbl;
	char m_pad[0x24 - 4];
};

class Rva0033F483
{
public:
	Rva0033F483(StateMachine *machine, int arg0);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

class Rva0033F43D
{
public:
	Rva0033F43D(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

extern const void *const g_00C11AC0[];

class Rva0034316A : public Rva004D759C
{
public:
	Rva0034316A(Object *owner, int x, unsigned int name);
};

Rva0034316A::Rva0034316A(Object *owner, int x, unsigned int name)
	: Rva004D759C(owner, name, false)
{
	*(const void **)this = g_00C11AC0;
	Rva00342A96 *s0 = new Rva00342A96((StateMachine *)this);
	((StateMachine *)this)->defineState(0xE1, (State *)s0, 0xE2, 0x270F, (const StateConditionInfo *)0);
	Rva00342AD6 *s1 = new Rva00342AD6((StateMachine *)this);
	((StateMachine *)this)->defineState(0xE9, (State *)s1, 0xE2, 0x270F, (const StateConditionInfo *)0);
	Rva00342B1A *s2 = new Rva00342B1A((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0xE2, (State *)s2, 0xE6, 0xE5, (const StateConditionInfo *)0);
	Rva0033F627 *s3 = new Rva0033F627((StateMachine *)this);
	((StateMachine *)this)->defineState(0xE5, (State *)s3, 0xE1, 0x270F, (const StateConditionInfo *)0);
	Rva0033F3B6 *s4 = new Rva0033F3B6((StateMachine *)this, true, false);
	((StateMachine *)this)->defineState(0xE6, (State *)s4, 0xE7, 0xE1, (const StateConditionInfo *)0);
	Rva0033F483 *s5 = new Rva0033F483((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0xE7, (State *)s5, 0xE8, 0xE1, (const StateConditionInfo *)0);
	Rva0033F43D *s6 = new Rva0033F43D((StateMachine *)this);
	((StateMachine *)this)->defineState(0xE8, (State *)s6, 0xE1, 0xE1, (const StateConditionInfo *)0);
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11AC0@@3QBQBXB=??_7Rva0034316A@@6B@")
