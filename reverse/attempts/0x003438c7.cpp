// ??0Rva003438C7@@QAE@PAVObject@@HVAsciiString@@@Z
// partial score=0.6 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0Rva003438C7@@QAE@PAVObject@@HVAsciiString@@@Z @0x003438C7 419B.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// Rva004D759C from (owner, name, 0), stores vtable g_00C11C90, defines three
// states, redefines the third, then defines one of three flag-gated states
// sharing a merged define tail. New-expressions into dead param slots with
// post-call eax feeding rowed defineState directly. The 0x259/0x270F/0xC131A0
// words CSE into ebx/esi/edi; single-use words stay immediate; the tail
// conditions pointer rides as a retail-pinned address.
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

class Rva0033F3EF
{
public:
	Rva0033F3EF(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x24 - 4];
};

class Rva0033F4B1
{
public:
	Rva0033F4B1(StateMachine *machine, int arg0);
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

class Rva004D74AC
{
public:
	Rva004D74AC(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class Rva004D7491
{
public:
	Rva004D7491(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class Rva00342978
{
public:
	Rva00342978(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x64 - 4];
};

struct Rva003438C7Flags
{
	volatile char m_pad[0x110];
};

extern const void *const g_00C11C90[];

class Rva003438C7 : public Rva004D759C
{
public:
	Rva003438C7(Object *owner, int x, AsciiString name);
};

Rva003438C7::Rva003438C7(Object *owner, int x, AsciiString name)
	: Rva004D759C(owner, name, false)
{
	*(const void **)this = g_00C11C90;
	Rva0033F3EF *s0 = new Rva0033F3EF((StateMachine *)this);
	((StateMachine *)this)->defineState(0x259, (State *)s0, 0x25A, 0x270F, (const StateConditionInfo *)0xC131A0);
	Rva0033F4B1 *s1 = new Rva0033F4B1((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0x25A, (State *)s1, 0x25B, 0x258, (const StateConditionInfo *)0xC131A0);
	Rva0033F43D *s2 = new Rva0033F43D((StateMachine *)this);
	((StateMachine *)this)->defineState(0x25B, (State *)s2, 0x259, 0x270F, 0);
	Rva003438C7Flags *gf = *(Rva003438C7Flags **)((char *)owner + 4);
	if (((gf->m_pad[0x108] & 4) == 0)) {
		if ((((gf->m_pad[0x10F] & 2) != 0) && ((gf->m_pad[0x108] & 8) != 0))) {
			Rva004D74AC *sy = new Rva004D74AC((StateMachine *)this);
			((StateMachine *)this)->defineState(0x258, (State *)sy, 0x270F, 0x270F, (const StateConditionInfo *)0xC13188);
		} else {
			Rva00342978 *sz = new Rva00342978((StateMachine *)this);
			((StateMachine *)this)->defineState(0x258, (State *)sz, 0x259, 0x270F, (const StateConditionInfo *)0);
		}
	} else {
		Rva004D7491 *sx = new Rva004D7491((StateMachine *)this);
		((StateMachine *)this)->defineState(0x258, (State *)sx, 0x270F, 0x270F, (const StateConditionInfo *)0);
	}
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11C90@@3QBQBXB=??_7Rva003438C7@@6B@")
