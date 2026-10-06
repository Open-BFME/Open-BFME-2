// cl: /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0Rva00343A86@@QAE@PAVObject@@HVAsciiString@@@Z @0x00343A86 295B.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// Rva004D759C from (owner, name, 0), stores vtable g_00C11A86, then four
// new-expression state blocks into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). The zero lives in
// esi and is recycled into 0x2BC; 0x2C0/0x2BE trade through ebx; the 0x270F
// pair rides transient ecx.
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

class Rva00342978
{
public:
	Rva00342978(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x64 - 4];
};

class Rva0033F460
{
public:
	Rva0033F460(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class Rva0033F4B1
{
public:
	Rva0033F4B1(StateMachine *machine, int arg0);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

extern const void *const g_00C11A86[];

class Rva00343A86 : public Rva004D759C
{
public:
	Rva00343A86(Object *owner, int x, AsciiString name);
};

Rva00343A86::Rva00343A86(Object *owner, int x, AsciiString name)
	: Rva004D759C(owner, name, false)
{
	*(const void **)this = g_00C11A86;
	Rva00342978 *s0 = new Rva00342978((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2BC, (State *)s0, 0x2BD, 0x2C0, (const StateConditionInfo *)0);
	Rva0033F460 *s1 = new Rva0033F460((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2C0, (State *)s1, 0x270F, 0x270F, (const StateConditionInfo *)0);
	Rva0033F4B1 *s2 = new Rva0033F4B1((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0x2BD, (State *)s2, 0x2BE, 0x2BC, (const StateConditionInfo *)0);
	Rva0033F460 *s3 = new Rva0033F460((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2BE, (State *)s3, 0x2BC, 0x2BC, (const StateConditionInfo *)0);
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11A86@@3QBQBXB=??_7Rva00343A86@@6B@")
