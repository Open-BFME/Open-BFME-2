// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Rva00343367::Rva00343367, retail 0x00343367 (632 bytes; called from
// 0x0034B1E9): Zero Hour's AttackStateMachine constructor shape (owner,
// attack state, name, follow, attackingObject, forceAttacking). BFME 2
// target facts: the rowed StateMachine constructor 0x004D79E1 with the name
// key; an owner whose template has kind byte +0x116 bit 0x80 and whose
// current weapon's template byte getter (rowed 0x002C9400) is set gets the
// squish chain (200 squish, 201 0x003429B9, 203 0x0033F364, 204 0x0033F38B);
// otherwise squish, approach (attackingObject only), 205 0x0033F460, the
// fire state 0x0033F483 on the attack state's +0x20 interface, and 203.
// States come from plain operator new and their rowed constructors.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
#define NULL 0
class Object;

struct StateConditionInfo
{
	void *m_test;
	StateID m_toStateID;
	void *m_userData;
};
struct State
{
public:
	virtual ~State();
};
class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Weapon
{
public:
	unsigned char m_pad00[0x04];
	Rva002C9400ByteField *m_template; // +0x04
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
struct ObjectTemplateBytes
{
	unsigned char m_pad000[0x116];
	unsigned char m_kind116; // +0x116
};
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	unsigned char m_pad00[0x04];
	const ObjectTemplateBytes *m_template; // +0x04
};
// The attack state handed in; its +0x20 base is the fire state's interface.
class Rva00343367AttackHead
{
public:
	virtual void v00();
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva00343367AttackInterface
{
public:
	virtual void v00();
};
class Rva00343367Attack : public Rva00343367AttackHead, public Rva00343367AttackInterface
{
};
class AIAttackMeleeSquishState : public State
{
public:
	AIAttackMeleeSquishState(StateMachine *machine);
private:
	unsigned char m_pad04[0x68 - 0x04];
};
class Rva003429B9 : public State
{
public:
	Rva003429B9(StateMachine *machine);
private:
	unsigned char m_pad04[0x60 - 0x04];
};
class Rva0033F364 : public State
{
public:
	Rva0033F364(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F38B : public State
{
public:
	Rva0033F38B(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class AIAttackApproachTargetState : public State
{
public:
	AIAttackApproachTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad04[0x74 - 0x04];
};
class Rva0033F460 : public State
{
public:
	Rva0033F460(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int attackInterface);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva00343367 : public Rva004D759C
{
public:
	Rva00343367(Object *obj, Rva00343367Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking);
	virtual ~Rva00343367();
};

Rva00343367::Rva00343367(Object *obj, Rva00343367Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking) : Rva004D759C(obj, nameKey, false)
{
	const Weapon *weapon;
	if ((obj->m_template->m_kind116 & 0x80) && (weapon = obj->getCurrentWeapon(NULL)) != NULL && weapon->m_template->get())
	{
		defineState( 200, new AIAttackMeleeSquishState( this ), 201, 9999 );
		defineState( 201, new Rva003429B9( this ), 203, 9999 );
		defineState( 203, new Rva0033F364( this ), 9998, 204 );
		defineState( 204, new Rva0033F38B( this ), 9998, 201 );
	}
	else
	{
		defineState( 200, new AIAttackMeleeSquishState( this ), 201, 9999 );
		defineState( 201, new AIAttackApproachTargetState( this, false, attackingObject, false ), 202, 205 );
		defineState( 205, new Rva0033F460( this ), 9999, 9999 );
		defineState( 202, new Rva0033F483( this, (int)static_cast<Rva00343367AttackInterface *>(att) ), 203, 201 );
		defineState( 203, new Rva0033F460( this ), 201, 201 );
	}
}
