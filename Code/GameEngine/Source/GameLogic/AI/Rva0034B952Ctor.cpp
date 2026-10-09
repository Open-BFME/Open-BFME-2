// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// Native factory0034BA20 pushes the opaque scalar key72383AF5 after new3C.
// It calls constructor0034B952 (206B): base4D79E1, vtableC122A0,
// three rowed state constructions and defineState IDs0A/27/00.
// Previous AsciiString by-value spelling was a legacy donor inference;
// the scalar name-key ABI is a native factory fact. Original class names unknown.
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
	Rva004D759C(Object *owner, unsigned int name, bool flag);
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
	Rva0034B952(Object *owner, unsigned int name);
private:unsigned char m_allocatedExtent[0x38];
};

Rva0034B952::Rva0034B952(Object *owner, unsigned int name)
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

class Rva0034BA20Owner {
public:Rva0034B952*createMachine();
private:unsigned char pad[0x14];Object*m_owner;
 Object*getOwner() const{return m_owner;}
};
Rva0034B952*Rva0034BA20Owner::createMachine(){
 return new Rva0034B952(getOwner(),0x72383AF5u);
}
