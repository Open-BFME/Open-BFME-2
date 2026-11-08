// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// platformsdk
// stlport
//
// AIStateMachine::AIStateMachine, retail 0x00351C48 (3805 bytes; pinned by
// makeStateMachine 0x00262513, which passes the name key 0x4A9A0E38).
// Zero Hour's AIStateMachine constructor (AIStates.cpp) through the matched
// BFME1 donor AIStateMachineConstructor.cpp: the goal path, waypoint, squad,
// target object, goal position and temporary state are cleared, then every
// AI state is registered with its BFME 2 ID and success/failure IDs. BFME 2
// builds the base from the rowed StateMachine constructor 0x004D79E1 with a
// name key (its unsigned spelling is pinned), creates the 75 states with
// plain operator new and constructs each through its rowed constructor; the
// classes below are constructor/size views named as those rows are.
#include <windows.h>
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
class Object;
class Waypoint;
class Squad;
class AttackExitConditionsInterface;
struct StateConditionInfo;
#include "../../../Include/Common/StateMachineClass.h"
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}
// The 12-byte POD erase at retail 0x2A133B is the rowed Gen_p12pod copy.
// Coord3D erase also has a distinct retail owner at 0x81A24; clear the
// same three-pointer vector representation through the required POD twin.
struct Gen_p12pod { int a[3]; };
// Retail frees the goal path's storage through free (0x00030830): the
// constructor's cleanup reaches the shared 14-byte destructor at 0x0007FAB3,
// not STLport's node allocator.
namespace _STL {
template <> inline
void allocator<Gen_p12pod>::deallocate(Gen_p12pod *__p, size_t) const
{ if (__p != 0) ::free((void *)__p); }
}

class AIStateMachine : public StateMachine
{
public:
	AIStateMachine(Object *owner, UnsignedInt nameKey);
	virtual ~AIStateMachine();
private:
	_STL::vector<Gen_p12pod> m_goalPath;	// +0x3C
	Waypoint *m_goalWaypoint;			// +0x48
	Squad *m_goalSquad;					// +0x4C
	State *m_temporaryState;			// +0x50
	UnsignedInt m_temporaryStateFrameEnd;	// +0x54
	UnsignedInt m_goalObjectID;			// +0x58
	Coord3D m_goalPosition;				// +0x5C
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType resetToDefaultState();
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType setState(unsigned int);
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType updateStateMachine();
public:
	// retail vftable slot: the rowed override
	virtual void clear();
};
typedef char AIStateMachineSize[sizeof(AIStateMachine) == 0x68 ? 1 : -1];
class Rva0033FE65
{
public:
	Rva0033FE65(StateMachine *machine, int a0);
private:
	unsigned char m_pad00[0x28];
};
class Rva0034005D
{
public:
	Rva0034005D(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class Rva003400CE
{
public:
	Rva003400CE(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class Rva00342826
{
public:
	Rva00342826(StateMachine *machine);
private:
	unsigned char m_pad00[0x4C];
};
class Rva00342843
{
public:
	Rva00342843(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class Rva00342892
{
public:
	Rva00342892(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class AIWanderInPlaceState
{
public:
	AIWanderInPlaceState(StateMachine *machine);
private:
	unsigned char m_pad00[0x60];
};
class Rva00342CFC
{
public:
	Rva00342CFC(StateMachine *machine);
private:
	unsigned char m_pad00[0x5C];
};
class AIAttackMoveToState
{
public:
	AIAttackMoveToState(StateMachine *machine);
private:
	unsigned char m_pad00[0x70];
};
class AIAttackFollowWaypointPathState
{
public:
	AIAttackFollowWaypointPathState(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x6C];
};
class Rva00342BAE
{
public:
	Rva00342BAE(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x68];
};
class Rva00342C47
{
public:
	Rva00342C47(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x68];
};
class AIFollowWaypointPathExactState
{
public:
	AIFollowWaypointPathExactState(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x54];
};
class AIFollowPathState
{
public:
	AIFollowPathState(StateMachine *machine, UnsignedInt a0);
private:
	unsigned char m_pad00[0x58];
};
class AIFollowPathAsTeamState
{
public:
	AIFollowPathAsTeamState(StateMachine *machine, Bool a0, UnsignedInt a1);
private:
	unsigned char m_pad00[0x68];
};
class AIMoveAndEvacuateState
{
public:
	AIMoveAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad00[0x58];
};
class AIMoveAndDeleteState
{
public:
	AIMoveAndDeleteState(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class Rva0033F41A
{
public:
	Rva0033F41A(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class AIAttackState
{
public:
	AIAttackState(StateMachine *machine, Bool a0, Bool a1, Bool a2, AttackExitConditionsInterface * a3);
private:
	unsigned char m_pad00[0x50];
};
class Rva0033F2FD
{
public:
	Rva0033F2FD(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva0033FC42
{
public:
	Rva0033FC42(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class AIAttackSquadState
{
public:
	AIAttackSquadState(StateMachine *machine, int a0);
private:
	unsigned char m_pad00[0x28];
};
class Rva00342C97
{
public:
	Rva00342C97(StateMachine *machine);
private:
	unsigned char m_pad00[0x70];
};
class Rva00342D19
{
public:
	Rva00342D19(StateMachine *machine);
private:
	unsigned char m_pad00[0x70];
};
class Rva003428AF
{
public:
	Rva003428AF(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class Rva003428CC
{
public:
	Rva003428CC(StateMachine *machine);
private:
	unsigned char m_pad00[0x5C];
};
class Rva0033F7C8
{
public:
	Rva0033F7C8(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva00340391
{
public:
	Rva00340391(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class AIMoveAwayAndCowerState
{
public:
	AIMoveAwayAndCowerState(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class AIBackAwayAndCowerState
{
public:
	AIBackAwayAndCowerState(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class Rva0033F51D
{
public:
	Rva0033F51D(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class AIDockState
{
public:
	AIDockState(StateMachine *machine);
private:
	unsigned char m_pad00[0x28];
};
class AIHarvestState
{
public:
	AIHarvestState(StateMachine *machine);
private:
	unsigned char m_pad00[0x28];
};
class Rva00342EAC
{
public:
	Rva00342EAC(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class AICombineState
{
public:
	AICombineState(StateMachine *machine);
private:
	unsigned char m_pad00[0x4C];
};
class AIEnterAndAttackState
{
public:
	AIEnterAndAttackState(StateMachine *machine);
private:
	unsigned char m_pad00[0x54];
};
class Rva0033F64E
{
public:
	Rva0033F64E(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x28];
};
class Rva0033F67C
{
public:
	Rva0033F67C(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x28];
};
class Rva0033F596
{
public:
	Rva0033F596(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva0033F5B9
{
public:
	Rva0033F5B9(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x24];
};
class Rva0033F5E3
{
public:
	Rva0033F5E3(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x24];
};
class AIGoingIdleState
{
public:
	AIGoingIdleState(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class AIGuardState
{
public:
	AIGuardState(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class AIGuardRetaliateState
{
public:
	AIGuardRetaliateState(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class AITunnelNetworkGuardState
{
public:
	AITunnelNetworkGuardState(StateMachine *machine);
private:
	unsigned char m_pad00[0x24];
};
class AIHuntState
{
public:
	AIHuntState(StateMachine *machine);
private:
	unsigned char m_pad00[0x28];
};
class AIAttackAreaState
{
public:
	AIAttackAreaState(StateMachine *machine);
private:
	unsigned char m_pad00[0x28];
};
class Rva00342FCD
{
public:
	Rva00342FCD(StateMachine *machine, int a0);
private:
	unsigned char m_pad00[0x30];
};
class Rva00342B87
{
public:
	Rva00342B87(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class Rva0033F320
{
public:
	Rva0033F320(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva0033F80E
{
public:
	Rva0033F80E(StateMachine *machine);
private:
	unsigned char m_pad00[0x2C];
};
class AIMoveToPositionAndDieState
{
public:
	AIMoveToPositionAndDieState(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class Rva00346CDD
{
public:
	Rva00346CDD(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class AIMoveToAndEvacuateState
{
public:
	AIMoveToAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class AIAttackMoveToAndEvacuateState
{
public:
	AIAttackMoveToAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class AIFollowPathAndEvacuateState
{
public:
	AIFollowPathAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad00[0x58];
};
class Rva0033F69E
{
public:
	Rva0033F69E(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x28];
};
class Rva0033F605
{
public:
	Rva0033F605(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad00[0x24];
};
class Rva00342619
{
public:
	Rva00342619(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class AIMoveForBoarding
{
public:
	AIMoveForBoarding(StateMachine *machine);
private:
	unsigned char m_pad00[0x50];
};
class Rva003426AB
{
public:
	Rva003426AB(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva0033F7EB
{
public:
	Rva0033F7EB(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};

AIStateMachine::AIStateMachine(Object *owner, UnsignedInt nameKey) : StateMachine(owner, nameKey, false)
{
	m_goalPath.clear();
	m_goalWaypoint = NULL;
	m_goalSquad = NULL;
	m_goalObjectID = 0;
	zeroCoord3D(m_goalPosition);
	m_temporaryState = NULL;
	m_temporaryStateFrameEnd = 0;

	// order matters: first state is the default state.
	defineState( 0, (State *)new Rva0033FE65( this, 0 ), 0, 78 );
	defineState( 1, (State *)new Rva0034005D( this ), 78, 78 );
	defineState( 63, (State *)new Rva003400CE( this ), 78, 78 );
	defineState( 26, (State *)new Rva00342826( this ), 78, 78 );
	defineState( 27, (State *)new Rva00342843( this ), 0, 0 );
	defineState( 40, (State *)new Rva00342892( this ), 41, 41 );
	defineState( 41, (State *)new AIWanderInPlaceState( this ), 40, 40 );
	defineState( 74, (State *)new Rva00342CFC( this ), 0, 0 );
	defineState( 33, (State *)new AIAttackMoveToState( this ), 78, 78 );
	defineState( 35, (State *)new AIAttackFollowWaypointPathState( this, true ), 0, 0 );
	defineState( 34, (State *)new AIAttackFollowWaypointPathState( this, false ), 0, 0 );
	defineState( 2, (State *)new Rva00342BAE( this, true ), 0, 0 );
	defineState( 3, (State *)new Rva00342BAE( this, false ), 0, 0 );
	defineState( 73, (State *)new Rva00342C47( this, false ), 0, 0 );
	defineState( 4, (State *)new AIFollowWaypointPathExactState( this, true ), 0, 0 );
	defineState( 5, (State *)new AIFollowWaypointPathExactState( this, false ), 0, 0 );
	defineState( 6, (State *)new AIFollowPathState( this, 0x8a091ff3u ), 0, 0 );
	defineState( 54, (State *)new AIFollowPathAsTeamState( this, false, 0x757afbb5u ), 0, 0 );
	defineState( 61, (State *)new AIFollowPathAsTeamState( this, true, 0x757afbb5u ), 0, 0 );
	defineState( 7, (State *)new AIFollowPathState( this, 0x8a091ff3u ), 0, 0 );
	defineState( 28, (State *)new AIMoveAndEvacuateState( this ), 0, 0 );
	defineState( 29, (State *)new AIMoveAndEvacuateState( this ), 30, 30 );
	defineState( 30, (State *)new AIMoveAndDeleteState( this ), 0, 0 );
	defineState( 8, (State *)new Rva0033F41A( this ), 0, 0 );
	defineState( 9, (State *)new AIAttackState( this, false, false, false, NULL ), 0, 0 );
	defineState( 10, (State *)new Rva0033F2FD( this ), 50, 50 );
	defineState( 50, (State *)new AIAttackState( this, false, true, false, NULL ), 0, 0 );
	defineState( 11, (State *)new Rva0033F2FD( this ), 51, 51 );
	defineState( 51, (State *)new AIAttackState( this, false, true, true, NULL ), 0, 0 );
	defineState( 43, (State *)new Rva0033FC42( this ), 0, 0 );
	defineState( 12, (State *)new AIAttackState( this, true, true, false, NULL ), 0, 0 );
	defineState( 23, (State *)new AIAttackSquadState( this, 0 ), 0, 0 );
	defineState( 18, (State *)new Rva00342C97( this ), 0, 40 );
	defineState( 19, (State *)new Rva00342D19( this ), 0, 40 );
	defineState( 20, (State *)new Rva003428AF( this ), 21, 0 );
	defineState( 21, (State *)new Rva003428CC( this ), 0, 0 );
	defineState( 48, (State *)new Rva0033F7C8( this ), 0, 0 );
	defineState( 57, (State *)new Rva00340391( this ), 0, 0 );
	defineState( 22, (State *)new AIMoveAwayAndCowerState( this ), 48, 0 );
	defineState( 32, (State *)new AIBackAwayAndCowerState( this ), 0, 0 );
	defineState( 13, (State *)new Rva0033F51D( this ), 0, 0 );
	defineState( 14, (State *)new AIDockState( this ), 0, 0 );
	defineState( 47, (State *)new AIHarvestState( this ), 0, 0 );
	defineState( 15, (State *)new Rva00342EAC( this ), 0, 0 );
	defineState( 60, (State *)new AICombineState( this ), 0, 0 );
	defineState( 49, (State *)new AIEnterAndAttackState( this ), 10, 10 );
	defineState( 38, (State *)new Rva0033F64E( this, false ), 0, 0 );
	defineState( 66, (State *)new Rva0033F67C( this, false ), 0, 0 );
	defineState( 52, (State *)new Rva0033F596( this ), 0, 0 );
	defineState( 53, (State *)new Rva0033F5B9( this, false ), 0, 0 );
	defineState( 65, (State *)new Rva0033F5E3( this, false ), 0, 0 );
	defineState( 75, (State *)new Rva0033F5B9( this, true ), 0, 0 );
	defineState( 78, (State *)new AIGoingIdleState( this ), 16, 0 );
	defineState( 16, (State *)new AIGuardState( this ), 0, 0 );
	defineState( 62, (State *)new AIGuardRetaliateState( this ), 0, 0 );
	defineState( 24, (State *)new AITunnelNetworkGuardState( this ), 0, 0 );
	defineState( 17, (State *)new AIHuntState( this ), 0, 0 );
	defineState( 31, (State *)new AIAttackAreaState( this ), 0, 0 );
	defineState( 36, (State *)new Rva00342FCD( this, 1 ), 0, 0 );
	defineState( 37, (State *)new Rva00342FCD( this, 0 ), 0, 0 );
	defineState( 59, (State *)new Rva00342FCD( this, 2 ), 0, 0 );
	defineState( 39, (State *)new Rva00342B87( this ), 0, 0 );
	defineState( 42, (State *)new Rva0033F320( this ), 0, 0 );
	defineState( 45, (State *)new Rva0033F80E( this ), 0, 0 );
	defineState( 55, (State *)new AIMoveToPositionAndDieState( this ), 0, 0 );
	defineState( 56, (State *)new Rva00346CDD( this ), 0, 0 );
	defineState( 64, (State *)new AIMoveToAndEvacuateState( this ), 0, 0 );
	defineState( 77, (State *)new AIAttackMoveToAndEvacuateState( this ), 0, 0 );
	defineState( 67, (State *)new AIFollowPathAndEvacuateState( this ), 0, 0 );
	defineState( 68, (State *)new Rva0033F69E( this, false ), 6, 0 );
	defineState( 69, (State *)new Rva0033F605( this, false ), 6, 0 );
	defineState( 70, (State *)new Rva00342619( this ), 71, 0 );
	defineState( 71, (State *)new AIMoveForBoarding( this ), 70, 0 );
	defineState( 72, (State *)new Rva003426AB( this ), 0, 0 );
	defineState( 58, (State *)new Rva0033F7EB( this ), 0, 0 );
}
