// ??0Rva00343367@@QAE@PAVObject@@HVAsciiString@@HHH@Z
// partial score=0.9892 date=2026-10-06
// ??0Rva00343367@@QAE@PAVObject@@HVAsciiString@@HHH@Z
// partial score=0.978 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0Rva00343367@@QAE@PAVObject@@HVAsciiString@@HHH@Z @0x00343367 632B.
// StateMachine-family ctor (thiscall, six params): base-constructs the rowed
// Rva004D759C from (owner, name, false), stores vtable g_00C11B18, then either
// defines the guarded four states (owner flag 0x116 bit, live weapon, set
// byte) or the five fallback states, and always defines the common tail
// state. New-expressions into dead param slots with post-call eax feeding
// rowed defineState directly (B952-family shape). The 0xC9 word CSEs into
// esi; 0x270F/0xCB trade through edi; zero stays in ebx; this spills to
// [ebp-0x10] once edi is reused and reloads from there.
class AsciiString
{
public:
	void *m_data;
};

class Object;
class Weapon;
struct State;
struct StateConditionInfo;
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

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

struct Rva00343367Flags
{
	char m_pad[0x117];
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	char m_pad00[4];
	Rva002C9400ByteField *m_field4; // +0x4
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;

	char m_pad00[4];
	Rva00343367Flags *m_flags4; // +0x4
};

class Rva00342AD6
{
public:
	Rva00342AD6(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x68 - 4];
};

class Rva003429B9
{
public:
	Rva003429B9(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x60 - 4];
};

class Rva0033F364
{
public:
	Rva0033F364(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x24 - 4];
};

class Rva0033F38B
{
public:
	Rva0033F38B(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

class Rva0034290D
{
public:
	Rva0034290D(StateMachine *machine, int a, int b, int c);
private:
	void *m_vtbl;
	char m_pad[0x74 - 4];
};

class Rva0033F460
{
public:
	Rva0033F460(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class Rva0033F483
{
public:
	Rva0033F483(StateMachine *machine, int arg0);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

extern const void *const g_00C11B18[];

class Rva00343367 : public Rva004D759C
{
public:
	Rva00343367(Object *owner, int x, AsciiString name, int u1, int u2, int u3);
};

Rva00343367::Rva00343367(Object *owner, int x, AsciiString name, int u1, int u2, int u3)
	: Rva004D759C(owner, name, false)
{
	(void)u1;
	(void)u3;
	*(const void **)this = g_00C11B18;
	const Weapon *weapon = 0;
	if (((owner->m_flags4->m_pad[0x116] & 0x80) != 0)
		&& (weapon = owner->getCurrentWeapon(0)) != 0
		&& weapon->m_field4->get() != 0) {
		Rva00342AD6 *a = new Rva00342AD6((StateMachine *)this);
		((StateMachine *)this)->defineState(0xC8, (State *)a, 0xC9, 0x270F, (const StateConditionInfo *)0);
		Rva003429B9 *b = new Rva003429B9((StateMachine *)this);
		((StateMachine *)this)->defineState(0xC9, (State *)b, 0xCB, 0x270F, (const StateConditionInfo *)0);
		Rva0033F364 *c = new Rva0033F364((StateMachine *)this);
		((StateMachine *)this)->defineState(0xCB, (State *)c, 0x270E, 0xCC, (const StateConditionInfo *)0);
		Rva0033F38B *d = new Rva0033F38B((StateMachine *)this);
		((StateMachine *)this)->defineState(0xCC, (State *)d, 0x270E, 0xC9, (const StateConditionInfo *)0);
	} else {
		Rva00342AD6 *e = new Rva00342AD6((StateMachine *)this);
		((StateMachine *)this)->defineState(0xC8, (State *)e, 0xC9, 0x270F, (const StateConditionInfo *)0);
		Rva0034290D *f = new Rva0034290D((StateMachine *)this, 0, u2, 0);
		((StateMachine *)this)->defineState(0xC9, (State *)f, 0xCA, 0xCD, (const StateConditionInfo *)0);
		Rva0033F460 *g = new Rva0033F460((StateMachine *)this);
		((StateMachine *)this)->defineState(0xCD, (State *)g, 0x270F, 0x270F, (const StateConditionInfo *)0);
		Rva0033F483 *h = new Rva0033F483((StateMachine *)this, x != 0 ? x + 0x20 : 0);
		((StateMachine *)this)->defineState(0xCA, (State *)h, 0xCB, 0xC9, (const StateConditionInfo *)0);
	}
	Rva0033F460 *i = new Rva0033F460((StateMachine *)this);
	((StateMachine *)this)->defineState(0xCB, (State *)i, 0xC9, 0xC9, (const StateConditionInfo *)0);
}

// The global below is defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C11B18@@3QBQBXB=??_7Rva00343367@@6B@")
