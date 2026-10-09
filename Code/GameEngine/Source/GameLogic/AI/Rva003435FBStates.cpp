// cl: /DNDEBUG /MD /EHsc
// ??0Rva003435FB@@QAE@PAVObject@@HI@Z @0x003435FB 296B.
// Name is a scalar hash: factory 34B1E9 pushes an immediate key, with no
// string construction or destruction. Keep the established host-word view.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// Rva004D759C from (owner, name, false), stores vtable g_00C11B70, then four
// new-expression state blocks into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). The 0x12D word
// CSEs into esi; zero stays in ebx; the int-typed state takes the branchless
// (x ? x+0x20 : 0) selector.
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

class Rva00342A50
{
public:
	Rva00342A50(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x6C - 4];
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

extern const void *const g_00C11B70[];

class Rva003435FB : public Rva004D759C
{
public:
	Rva003435FB(Object *owner, int x, unsigned int name);
};

Rva003435FB::Rva003435FB(Object *owner, int x, unsigned int name)
	: Rva004D759C(owner, name, false)
{
	*(const void **)this = g_00C11B70;
	Rva00342A50 *s0 = new Rva00342A50((StateMachine *)this);
	((StateMachine *)this)->defineState(0x12D, (State *)s0, 0x12E, 0x270F, (const StateConditionInfo *)0);
	Rva0033F3B6 *s1 = new Rva0033F3B6((StateMachine *)this, true, false);
	((StateMachine *)this)->defineState(0x12E, (State *)s1, 0x12F, 0x12D, (const StateConditionInfo *)0);
	Rva0033F483 *s2 = new Rva0033F483((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0x12F, (State *)s2, 0x130, 0x12D, (const StateConditionInfo *)0);
	Rva0033F43D *s3 = new Rva0033F43D((StateMachine *)this);
	((StateMachine *)this)->defineState(0x130, (State *)s3, 0x12D, 0x12D, (const StateConditionInfo *)0);
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11B70@@3QBQBXB=??_7Rva003435FB@@6B@")
