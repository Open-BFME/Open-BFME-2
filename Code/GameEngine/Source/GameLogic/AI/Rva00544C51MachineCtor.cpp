// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Rva00544C51::Rva00544C51, retail 0x544ed4: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the name key 0x3e69bbc3
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

class Rva00544EB1
{
public:
	Rva00544EB1(StateMachine *machine);
private:
	unsigned char m_pad00[0x4C];
};
class AIHarvestPrepareSiteState
{
public:
	AIHarvestPrepareSiteState(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class Rva00544C2A
{
public:
	Rva00544C2A(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class Rva00544C51 : public StateMachine
{
public:
	Rva00544C51(Object *owner);
	virtual ~Rva00544C51();

};

Rva00544C51::Rva00544C51(Object *owner) : StateMachine(owner, 0x3e69bbc3u, false)
{

	// order matters: first state is the default state.
	defineState( 0, (State *)new Rva00544EB1( this ), 1, 9999 );
	defineState( 1, (State *)new AIHarvestPrepareSiteState( this ), 2, 0 );
	defineState( 2, (State *)new Rva00544C2A( this ), 9998, 9999 );
}
