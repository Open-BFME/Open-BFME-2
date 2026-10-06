// cl: /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0Rva0034B952@@QAE@PAVObject@@VAsciiString@@@Z @0x0034B952 206B StateMachine ctor defining states 0xa 0x27 0x00 via rowed AIAttackState Rva00342B87 Rva0033FE65.
// Evidence: base 0x004D79E1 plus vtable g_00C122A0 plus defineState 0x004D7B0F rows; caller 0x0034BA20; prev/next share /O1 /DNDEBUG /MD.
class AsciiString
{
public:
	void *m_data;
};

class Object;
class AttackExitConditionsInterface;

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

class AIAttackState
{
public:
	AIAttackState(StateMachine *machine, bool follow, bool attackingObject, bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	void *m_vtbl;
	char m_pad[0x50 - 4];
};

class Rva00342B87
{
public:
	Rva00342B87(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x50 - 4];
};

class Rva0033FE65
{
public:
	Rva0033FE65(StateMachine *machine, int val);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

extern const void *const g_00C122A0[];

class Rva0034B952 : public Rva004D759C
{
public:
	Rva0034B952(Object *owner, AsciiString name);
};

Rva0034B952::Rva0034B952(Object *owner, AsciiString name)
	: Rva004D759C(owner, name, false)
{
	*(const void **)this = g_00C122A0;
	AIAttackState *s0 = new AIAttackState((StateMachine *)this, false, true, false, (AttackExitConditionsInterface *)0);
	((StateMachine *)this)->defineState(0xa, (State *)s0, 0, 0, (const StateConditionInfo *)0);
	Rva00342B87 *s1 = new Rva00342B87((StateMachine *)this);
	((StateMachine *)this)->defineState(0x27, (State *)s1, 0, 0, (const StateConditionInfo *)0);
	Rva0033FE65 *s2 = new Rva0033FE65((StateMachine *)this, 1);
	((StateMachine *)this)->defineState(0, (State *)s2, 0, 0, (const StateConditionInfo *)0);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C122A0@@3QBQBXB=??_7Rva0034144B@@6B@")
