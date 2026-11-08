// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// platformsdk
//
// AIGuardRetaliateMachine::AIGuardRetaliateMachine, retail 0x0054551F (196
// bytes; pinned under this name). Zero Hour's AIGuardRetaliate.cpp machine:
// the nemesis is cleared and the guard position zeroed, then the attack-
// aggressor and return states are registered, the return state with the
// aggressor-check condition table. BFME 2 builds the base from the rowed
// StateMachine constructor 0x004D79E1 with the name key 0xD5DFA9B7 and
// creates the states with plain operator new and their rowed constructors.
#include <windows.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
class Object;
#include "../../../Include/Common/StateConditionInfo.h"
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
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
class AIGuardRetaliateAttackAggressorState
{
public:
	AIGuardRetaliateAttackAggressorState(StateMachine *machine);
private:
	unsigned char m_pad00[0x44];
};
class AIGuardRetaliateReturnState
{
public:
	AIGuardRetaliateReturnState(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class AIGuardRetaliateMachine : public StateMachine
{
public:
	AIGuardRetaliateMachine(Object *owner);
	virtual ~AIGuardRetaliateMachine();
private:
	Coord3D m_positionToGuard;		// +0x3C
	ObjectID m_nemesisToAttack;		// +0x48
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};
// Zero Hour's checkForAggressor condition. BFME 2's body answers false and
// retail folds it into the shared xor al,al / ret at 0x0047A699 (ICF twin
// of the rowed Xfer::IsCRC); file-static in ZH, address-named here.
Bool rva0047A699(State *thisState, void *userData)
{
	return false;
}

AIGuardRetaliateMachine::AIGuardRetaliateMachine(Object *owner) : StateMachine(owner, 0xd5dfa9b7u, false), m_nemesisToAttack(0)
{
	static const StateConditionInfo attackAggressors[] =
	{
		{ rva0047A699, AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	zeroCoord3D(m_positionToGuard);

	// order matters: first state is the default state.
	defineState( AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, (State *)new AIGuardRetaliateAttackAggressorState( this ), AI_GUARD_RETALIATE_RETURN, AI_GUARD_RETALIATE_RETURN );
	defineState( AI_GUARD_RETALIATE_RETURN, (State *)new AIGuardRetaliateReturnState( this ), EXIT_MACHINE_WITH_SUCCESS, AI_GUARD_RETALIATE_ATTACK_AGGRESSOR, attackAggressors );
}
