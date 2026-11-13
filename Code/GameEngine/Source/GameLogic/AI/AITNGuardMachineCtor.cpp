// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AITNGuardMachine::AITNGuardMachine, retail 0x546001: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the name key 0x91632a45
// (its unsigned spelling is pinned); each state comes from plain operator
// new and its rowed constructor, registered with the IDs and transitions
// read from the retail call sequence (Zero Hour's defineState pattern).
#include <stddef.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
class Object;
#include "../../../Include/Common/StateConditionInfo.h"
#include "../../../Include/Common/StateMachineClass.h"
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

class Rva00545DB0
{
public:
	Rva00545DB0(StateMachine *machine);
private:
	unsigned char m_pad00[0x58];
};
class Rva00545B4F
{
public:
	Rva00545B4F(StateMachine *machine);
private:
	unsigned char m_pad00[0x30];
};
#include "../../../Include/GameLogic/AITNGuard.h"
class Rva00545D7E
{
public:
	Rva00545D7E(StateMachine *machine);
private:
	unsigned char m_pad00[0x2C];
};
class Rva0036804F
{
public:
	Rva0036804F(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class AITNGuardAttackAggressorState
{
public:
	AITNGuardAttackAggressorState(StateMachine *machine);
private:
	unsigned char m_pad00[0x2C];
};
class AITNGuardMachine : public StateMachine
{
public:
	AITNGuardMachine(Object *owner);
	virtual ~AITNGuardMachine();
	Coord3D m_positionToGuard;	// +0x3C
	ObjectID m_nemesisToAttack;	// +0x48
	UnsignedInt m_4C;			// +0x4C
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x00545B8F
};
// condition 0x00545F10 (retail .rdata table entry)
Bool rva00545F10(State *thisState, void *userData);

AITNGuardMachine::AITNGuardMachine(Object *owner) : StateMachine(owner, 0x91632a45u, false)
{
	static const StateConditionInfo g_condC6A2FC[] =
	{
		{ rva00545F10, 5005, NULL },
		{ NULL, 0, NULL }	// keep last
	};
	m_nemesisToAttack = 0;
	m_4C = 0;
	zeroCoord3D(m_positionToGuard);
	// order matters: first state is the default state.
	defineState( 5003, (State *)new Rva00545DB0( this ), 5001, 5000, g_condC6A2FC );
	defineState( 5001, (State *)new Rva00545B4F( this ), 5000, 5003 );
	defineState( 5000, (State *)new AITNGuardInnerState( this ), 5002, 5002, g_condC6A2FC );
	defineState( 5002, (State *)new Rva00545D7E( this ), 5004, 5004 );
	defineState( 5004, (State *)new Rva0036804F( this ), 5003, 5003 );
	defineState( 5005, (State *)new AITNGuardAttackAggressorState( this ), 5003, 5003 );
}
