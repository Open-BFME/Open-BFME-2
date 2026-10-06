// cl: /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0Rva00343838@@QAE@PAVObject@@HVAsciiString@@H@Z @0x00343838 115B.
// StateMachine-family ctor (thiscall, four params): base-constructs the rowed
// Rva004D759C from (owner, name, flag), stores vtable g_00C11C30, then one
// new-expression state block into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). Too few constants
// to keep ebx, so the zeros ride as immediates and the dead state reset
// takes whatever bl holds.
class AsciiString
{
public:
	void *m_data;
};

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
	Rva004D759C(Object *owner, AsciiString name, bool flag);
	virtual ~Rva004D759C();
};

class Rva00343042
{
public:
	Rva00343042(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x58 - 4];
};

extern const void *const g_00C11C30[];

class Rva00343838 : public Rva004D759C
{
public:
	Rva00343838(Object *owner, int u, AsciiString name, bool flag);
};

Rva00343838::Rva00343838(Object *owner, int u, AsciiString name, bool flag)
	: Rva004D759C(owner, name, flag)
{
	(void)u;
	*(const void **)this = g_00C11C30;
	Rva00343042 *s0 = new Rva00343042((StateMachine *)this);
	((StateMachine *)this)->defineState(0, (State *)s0, 0x270E, 0x270F, (const StateConditionInfo *)0);
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11C30@@3QBQBXB=??_7Rva00343838@@6B@")
