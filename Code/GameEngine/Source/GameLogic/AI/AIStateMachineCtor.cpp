// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
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
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#define NULL 0
class Object;
class Waypoint;
class Squad;
class AttackExitConditionsInterface;
struct StateConditionInfo;
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
class AIStateMachine : public Rva004D759C
{
public:
	AIStateMachine(Object *owner, UnsignedInt nameKey);
	virtual ~AIStateMachine();
private:
	_STL::vector<Coord3D> m_goalPath;	// +0x3C
	Waypoint *m_goalWaypoint;			// +0x48
	Squad *m_goalSquad;					// +0x4C
	State *m_temporaryState;			// +0x50
	UnsignedInt m_temporaryStateFrameEnd;	// +0x54
	UnsignedInt m_goalObjectID;			// +0x58
	Coord3D m_goalPosition;				// +0x5C
};
typedef char AIStateMachineSize[sizeof(AIStateMachine) == 0x68 ? 1 : -1];
class Rva0033FE65 : public State
{
public:
	Rva0033FE65(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0034005D : public State
{
public:
	Rva0034005D(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva003400CE : public State
{
public:
	Rva003400CE(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class Rva00342826 : public State
{
public:
	Rva00342826(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva00342843 : public State
{
public:
	Rva00342843(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class Rva00342892 : public State
{
public:
	Rva00342892(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class AIWanderInPlaceState : public State
{
public:
	AIWanderInPlaceState(StateMachine *machine);
private:
	unsigned char m_pad04[0x60 - 0x04];
};
class Rva00342CFC : public State
{
public:
	Rva00342CFC(StateMachine *machine);
private:
	unsigned char m_pad04[0x5C - 0x04];
};
class AIAttackMoveToState : public State
{
public:
	AIAttackMoveToState(StateMachine *machine);
private:
	unsigned char m_pad04[0x70 - 0x04];
};
class AIAttackFollowWaypointPathState : public State
{
public:
	AIAttackFollowWaypointPathState(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x6C - 0x04];
};
class Rva00342BAE : public State
{
public:
	Rva00342BAE(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x68 - 0x04];
};
class Rva00342C47 : public State
{
public:
	Rva00342C47(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x68 - 0x04];
};
class AIFollowWaypointPathExactState : public State
{
public:
	AIFollowWaypointPathExactState(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class AIFollowPathState : public State
{
public:
	AIFollowPathState(StateMachine *machine, UnsignedInt a0);
private:
	unsigned char m_pad04[0x58 - 0x04];
};
class AIFollowPathAsTeamState : public State
{
public:
	AIFollowPathAsTeamState(StateMachine *machine, Bool a0, UnsignedInt a1);
private:
	unsigned char m_pad04[0x68 - 0x04];
};
class AIMoveAndEvacuateState : public State
{
public:
	AIMoveAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad04[0x58 - 0x04];
};
class AIMoveAndDeleteState : public State
{
public:
	AIMoveAndDeleteState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva0033F41A : public State
{
public:
	Rva0033F41A(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, Bool a0, Bool a1, Bool a2, AttackExitConditionsInterface * a3);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva0033F2FD : public State
{
public:
	Rva0033F2FD(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033FC42 : public State
{
public:
	Rva0033FC42(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F4DF : public State
{
public:
	Rva0033F4DF(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva00342C97 : public State
{
public:
	Rva00342C97(StateMachine *machine);
private:
	unsigned char m_pad04[0x70 - 0x04];
};
class Rva00342D19 : public State
{
public:
	Rva00342D19(StateMachine *machine);
private:
	unsigned char m_pad04[0x70 - 0x04];
};
class Rva003428AF : public State
{
public:
	Rva003428AF(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class Rva003428CC : public State
{
public:
	Rva003428CC(StateMachine *machine);
private:
	unsigned char m_pad04[0x5C - 0x04];
};
class Rva0033F7C8 : public State
{
public:
	Rva0033F7C8(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva00340391 : public State
{
public:
	Rva00340391(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class AIMoveAwayAndCowerState : public State
{
public:
	AIMoveAwayAndCowerState(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class Rva0033F33D : public State
{
public:
	Rva0033F33D(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F51D : public State
{
public:
	Rva0033F51D(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F540 : public State
{
public:
	Rva0033F540(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F56B : public State
{
public:
	Rva0033F56B(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva00342EAC : public State
{
public:
	Rva00342EAC(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class AICombineState : public State
{
public:
	AICombineState(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class AIEnterAndAttackState : public State
{
public:
	AIEnterAndAttackState(StateMachine *machine);
private:
	unsigned char m_pad04[0x54 - 0x04];
};
class Rva0033F64E : public State
{
public:
	Rva0033F64E(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F67C : public State
{
public:
	Rva0033F67C(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F596 : public State
{
public:
	Rva0033F596(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F5B9 : public State
{
public:
	Rva0033F5B9(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F5E3 : public State
{
public:
	Rva0033F5E3(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F701 : public State
{
public:
	Rva0033F701(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F6DA : public State
{
public:
	Rva0033F6DA(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F724 : public State
{
public:
	Rva0033F724(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F74B : public State
{
public:
	Rva0033F74B(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F772 : public State
{
public:
	Rva0033F772(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F79D : public State
{
public:
	Rva0033F79D(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva00342FCD : public State
{
public:
	Rva00342FCD(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x30 - 0x04];
};
class Rva00342B87 : public State
{
public:
	Rva00342B87(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva0033F320 : public State
{
public:
	Rva0033F320(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F80E : public State
{
public:
	Rva0033F80E(StateMachine *machine);
private:
	unsigned char m_pad04[0x2C - 0x04];
};
class AIMoveToPositionAndDieState : public State
{
public:
	AIMoveToPositionAndDieState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva00346CDD : public State
{
public:
	Rva00346CDD(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AIMoveToAndEvacuateState : public State
{
public:
	AIMoveToAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AIAttackMoveToAndEvacuateState : public State
{
public:
	AIAttackMoveToAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AIFollowPathAndEvacuateState : public State
{
public:
	AIFollowPathAndEvacuateState(StateMachine *machine);
private:
	unsigned char m_pad04[0x58 - 0x04];
};
class Rva0033F69E : public State
{
public:
	Rva0033F69E(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F605 : public State
{
public:
	Rva0033F605(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva00342619 : public State
{
public:
	Rva00342619(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class AIMoveForBoarding : public State
{
public:
	AIMoveForBoarding(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva003426AB : public State
{
public:
	Rva003426AB(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva0033F7EB : public State
{
public:
	Rva0033F7EB(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};

AIStateMachine::AIStateMachine(Object *owner, UnsignedInt nameKey) : Rva004D759C(owner, nameKey, false)
{
	m_goalPath.clear();
	m_goalWaypoint = NULL;
	m_goalSquad = NULL;
	m_goalObjectID = 0;
	zeroCoord3D(m_goalPosition);
	m_temporaryState = NULL;
	m_temporaryStateFrameEnd = 0;

	// order matters: first state is the default state.
	defineState( 0, new Rva0033FE65( this, 0 ), 0, 78 );
	defineState( 1, new Rva0034005D( this ), 78, 78 );
	defineState( 63, new Rva003400CE( this ), 78, 78 );
	defineState( 26, new Rva00342826( this ), 78, 78 );
	defineState( 27, new Rva00342843( this ), 0, 0 );
	defineState( 40, new Rva00342892( this ), 41, 41 );
	defineState( 41, new AIWanderInPlaceState( this ), 40, 40 );
	defineState( 74, new Rva00342CFC( this ), 0, 0 );
	defineState( 33, new AIAttackMoveToState( this ), 78, 78 );
	defineState( 35, new AIAttackFollowWaypointPathState( this, true ), 0, 0 );
	defineState( 34, new AIAttackFollowWaypointPathState( this, false ), 0, 0 );
	defineState( 2, new Rva00342BAE( this, true ), 0, 0 );
	defineState( 3, new Rva00342BAE( this, false ), 0, 0 );
	defineState( 73, new Rva00342C47( this, false ), 0, 0 );
	defineState( 4, new AIFollowWaypointPathExactState( this, true ), 0, 0 );
	defineState( 5, new AIFollowWaypointPathExactState( this, false ), 0, 0 );
	defineState( 6, new AIFollowPathState( this, 0x8a091ff3u ), 0, 0 );
	defineState( 54, new AIFollowPathAsTeamState( this, false, 0x757afbb5u ), 0, 0 );
	defineState( 61, new AIFollowPathAsTeamState( this, true, 0x757afbb5u ), 0, 0 );
	defineState( 7, new AIFollowPathState( this, 0x8a091ff3u ), 0, 0 );
	defineState( 28, new AIMoveAndEvacuateState( this ), 0, 0 );
	defineState( 29, new AIMoveAndEvacuateState( this ), 30, 30 );
	defineState( 30, new AIMoveAndDeleteState( this ), 0, 0 );
	defineState( 8, new Rva0033F41A( this ), 0, 0 );
	defineState( 9, new AIAttackState( this, false, false, false, NULL ), 0, 0 );
	defineState( 10, new Rva0033F2FD( this ), 50, 50 );
	defineState( 50, new AIAttackState( this, false, true, false, NULL ), 0, 0 );
	defineState( 11, new Rva0033F2FD( this ), 51, 51 );
	defineState( 51, new AIAttackState( this, false, true, true, NULL ), 0, 0 );
	defineState( 43, new Rva0033FC42( this ), 0, 0 );
	defineState( 12, new AIAttackState( this, true, true, false, NULL ), 0, 0 );
	defineState( 23, new Rva0033F4DF( this, 0 ), 0, 0 );
	defineState( 18, new Rva00342C97( this ), 0, 40 );
	defineState( 19, new Rva00342D19( this ), 0, 40 );
	defineState( 20, new Rva003428AF( this ), 21, 0 );
	defineState( 21, new Rva003428CC( this ), 0, 0 );
	defineState( 48, new Rva0033F7C8( this ), 0, 0 );
	defineState( 57, new Rva00340391( this ), 0, 0 );
	defineState( 22, new AIMoveAwayAndCowerState( this ), 48, 0 );
	defineState( 32, new Rva0033F33D( this ), 0, 0 );
	defineState( 13, new Rva0033F51D( this ), 0, 0 );
	defineState( 14, new Rva0033F540( this ), 0, 0 );
	defineState( 47, new Rva0033F56B( this ), 0, 0 );
	defineState( 15, new Rva00342EAC( this ), 0, 0 );
	defineState( 60, new AICombineState( this ), 0, 0 );
	defineState( 49, new AIEnterAndAttackState( this ), 10, 10 );
	defineState( 38, new Rva0033F64E( this, false ), 0, 0 );
	defineState( 66, new Rva0033F67C( this, false ), 0, 0 );
	defineState( 52, new Rva0033F596( this ), 0, 0 );
	defineState( 53, new Rva0033F5B9( this, false ), 0, 0 );
	defineState( 65, new Rva0033F5E3( this, false ), 0, 0 );
	defineState( 75, new Rva0033F5B9( this, true ), 0, 0 );
	defineState( 78, new Rva0033F701( this ), 16, 0 );
	defineState( 16, new Rva0033F6DA( this ), 0, 0 );
	defineState( 62, new Rva0033F724( this ), 0, 0 );
	defineState( 24, new Rva0033F74B( this ), 0, 0 );
	defineState( 17, new Rva0033F772( this ), 0, 0 );
	defineState( 31, new Rva0033F79D( this ), 0, 0 );
	defineState( 36, new Rva00342FCD( this, 1 ), 0, 0 );
	defineState( 37, new Rva00342FCD( this, 0 ), 0, 0 );
	defineState( 59, new Rva00342FCD( this, 2 ), 0, 0 );
	defineState( 39, new Rva00342B87( this ), 0, 0 );
	defineState( 42, new Rva0033F320( this ), 0, 0 );
	defineState( 45, new Rva0033F80E( this ), 0, 0 );
	defineState( 55, new AIMoveToPositionAndDieState( this ), 0, 0 );
	defineState( 56, new Rva00346CDD( this ), 0, 0 );
	defineState( 64, new AIMoveToAndEvacuateState( this ), 0, 0 );
	defineState( 77, new AIAttackMoveToAndEvacuateState( this ), 0, 0 );
	defineState( 67, new AIFollowPathAndEvacuateState( this ), 0, 0 );
	defineState( 68, new Rva0033F69E( this, false ), 6, 0 );
	defineState( 69, new Rva0033F605( this, false ), 6, 0 );
	defineState( 70, new Rva00342619( this ), 71, 0 );
	defineState( 71, new AIMoveForBoarding( this ), 70, 0 );
	defineState( 72, new Rva003426AB( this ), 0, 0 );
	defineState( 58, new Rva0033F7EB( this ), 0, 0 );
}
