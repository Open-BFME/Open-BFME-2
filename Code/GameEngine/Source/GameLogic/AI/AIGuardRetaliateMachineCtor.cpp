// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AIGuardRetaliateMachine::AIGuardRetaliateMachine, retail 0x0054551F (196
// bytes; pinned under this name). Zero Hour's AIGuardRetaliate.cpp machine:
// the nemesis is cleared and the guard position zeroed, then the attack-
// aggressor and return states are registered, the return state with the
// aggressor-check condition table. BFME 2 builds the base from the rowed
// StateMachine constructor 0x004D79E1 with the name key 0xD5DFA9B7 and
// creates the states with plain operator new and their rowed constructors.
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
enum
{
	AI_GUARD_RETALIATE_RETURN = 5003,
	AI_GUARD_RETALIATE_ATTACK_AGGRESSOR = 5005,
	EXIT_MACHINE_WITH_SUCCESS = 9998
};
class AIGuardRetaliateAttackAggressorState : public State
{
public:
	AIGuardRetaliateAttackAggressorState(StateMachine *machine);
private:
	unsigned char m_pad04[0x44 - 0x04];
};
class AIGuardRetaliateReturnState : public State
{
public:
	AIGuardRetaliateReturnState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AIGuardRetaliateMachine : public Rva004D759C
{
public:
	AIGuardRetaliateMachine(Object *owner);
	virtual ~AIGuardRetaliateMachine();
private:
	Coord3D m_positionToGuard;		// +0x3C
	ObjectID m_nemesisToAttack;		// +0x48
};
// Zero Hour's checkForAggressor condition (rowed 0x0047A699, an ICF fold).
Bool rva0047A699(State *thisState, void *userData);

AIGuardRetaliateMachine::AIGuardRetaliateMachine(Object *owner) : Rva004D759C(owner, 0xd5dfa9b7u, false), m_nemesisToAttack(0)
{
	static const StateConditionInfo attackAggressors[] =
	{
		{ (void *)rva0047A699, AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	zeroCoord3D(m_positionToGuard);

	// order matters: first state is the default state.
	defineState( AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, new AIGuardRetaliateAttackAggressorState( this ), AI_GUARD_RETALIATE_RETURN, AI_GUARD_RETALIATE_RETURN );
	defineState( AI_GUARD_RETALIATE_RETURN, new AIGuardRetaliateReturnState( this ), EXIT_MACHINE_WITH_SUCCESS, AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, attackAggressors );
}
