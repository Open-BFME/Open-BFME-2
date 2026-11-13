// cl: /DNDEBUG /MD
//
// AIFollowPathState::onEnter, retail 0x0034DEF8 (396 bytes), and update,
// retail 0x0034E084 (643 bytes): slots 4 and 6 of vtable 0x00C12BC8, whose
// slot-2 name getter returns AIFollowPathState. Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). BFME 2 drops ZH's
// formation-group speed block, and each setAdjustsDestination carries its own
// CritterDesync log line under the global log flag.
// Callees: the goal-path lookups go through the AI's state machine (+0x30) to
// the pinned AIStateMachine::getGoalPathPosition 0x00346FA5 (ZH bounds check
// over the +0x3C Coord3D vector), and setPathExtraDistance is the pinned
// out-of-line Real setter 0x002633F3. The AI's friend_getGoalPathPosition
// reads m_stateMachine directly (through the getStateMachine accessor the
// scheduler loads the index before the machine and retail does not).
// update: Zero Hour's body without ignoreObstacleID; friend_startingMove is
// the rowed opaque AIUpdateInterface::rva00262ACE; the final-segment
// destination adjust is the pinned Pathfinder::adjustDestination (TheAI +0x10,
// locomotor set at AI +0x1CC), after which BFME 2 hands the goal to an owner
// member (pinned opaque Object::rva0028ACDC, forwarding to the helper at
// +0xA4) in place of Zero Hour's pathfinder updateGoal; isDoingGroundMovement
// is AI vslot 137; three CritterDesync log lines (42, 43 with TRUE/FALSE
// arguments, ComputePath32). m_adjustFinalOverride +0x51, m_retryCount +0x54.
// Layout: AI +0x258 with goal path index +0x194, current locomotor +0x1F0
// (flags +0x44, PRECISE_Z_POS bit 3) and can-path-through-units +0x3BA;
// state id +4 (AI_FOLLOW_EXITPRODUCTION_PATH 7), goal +0x20,
// adjusts-destination +0x48, m_index +0x4C, m_adjustFinal +0x50; the
// PROJECTILE kind bit is the owner template's byte +0x10B mask 0x02.
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
// platformsdk
#include <windows.h>
#undef near
#undef far
#define PATHFIND_CELL_SIZE_F 10.0f
inline Real sqr(Real x) { return x * x; }
enum
{
	AI_FOLLOW_EXITPRODUCTION_PATH = 7
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct FprintfTarget
{
	char m_pad[4];
};
// Retail calls the game's _fprintf thunk through REL32, so read <stdio.h>
// without dllimport.
#define _CRTIMP
#include <stdio.h>
#undef _CRTIMP
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
#define CRITTER_LOG(msg) \
	if (g_00E03745) \
	{ \
		FILE *log = (FILE *)theLogicRandomLogFile; \
		if (log) \
			fprintf msg; \
	}
#include "../../../Include/GameLogic/LocomotorClass.h"
#include "../../../Include/GameLogic/AIStateMachineClass.h"
#include "../../../Include/Common/Rva00346FA5.h"
class LocomotorSet;
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
// isDoingGroundMovement is AIUpdateInterface vslot 137 (+0x224).
class AIUpdateInterface : public AIUpdateSlots<137>
{
public:
	virtual Bool isDoingGroundMovement(void) const = 0;
	__declspec(dllimport) __forceinline const LocomotorSet &getLocomotorSet(void) const { return *(const LocomotorSet *)m_locomotorSet; }
	void rva00262ACE(); // friend_startingMove
	AIStateMachine *getStateMachine() const { return m_stateMachine; }
	const Coord3D *friend_getGoalPathPosition(Int index) const { return (const Coord3D *)((const Rva00346FA5 *)m_stateMachine)->rva00346FA5(index); }
	void friend_setCurrentGoalPathIndex(Int index) { m_currentGoalPathIndex = index; }
	__declspec(dllimport) __forceinline void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void setPathExtraDistance(Real dist);
private:
	unsigned char m_pad004[0x30 - 0x04];
	AIStateMachine *m_stateMachine; // +0x30
	unsigned char m_pad034[0x194 - 0x34];
	Int m_currentGoalPathIndex; // +0x194
	unsigned char m_pad198[0x1CC - 0x198];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3BA - 0x1F4];
	Bool m_canPathThroughUnits; // +0x3BA
};
#include "../../../Include/Common/ThingTemplate.h"
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	void rva0028ACDC(int goal);
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isKindOfProjectile() const { return (((unsigned char)(m_template->m_kindof[0] >> 24) & 0x02) != 0); }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;


class AIFollowPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustDestinations = b; }
private:
	Int m_index; // +0x4C
	Bool m_adjustFinal; // +0x50
	Bool m_adjustFinalOverride; // +0x51
	unsigned char m_pad52[0x54 - 0x52];
	Int m_retryCount; // +0x54
};

StateReturnType AIFollowPathState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_index = 0;
	const Coord3D *pos = ai->friend_getGoalPathPosition( 0 );

	if (pos == NULL)
		return STATE_FAILURE;

	// set initial movement goal
	m_goalPosition = *pos;
	const Coord3D *nextPos = ai->friend_getGoalPathPosition( 1 );
	m_adjustFinal = true;

	//Assign this value to the AIUpdateInterface so object's can access this value while
	//determine which waypoints to plot in the waypoint renderer.
	ai->friend_setCurrentGoalPathIndex( 0 );

	if (m_id == AI_FOLLOW_EXITPRODUCTION_PATH) {
		ai->setCanPathThroughUnits(true);
		CRITTER_LOG((log, "CritterDesync: setAdjustDestination(FALSE) 39"));
		m_adjustDestinations = false;
		m_adjustFinal = true;
	}
	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (nextPos)
	{
		Coord2D delta;
		delta.x = nextPos->x - pos->x;
		delta.y = nextPos->y - pos->y;
		Real offset = delta.length();
		const Coord3D *followingPos = ai->friend_getGoalPathPosition( m_index+2 );
		if (followingPos) offset += 4*PATHFIND_CELL_SIZE_F;
		ai->setPathExtraDistance(offset);
		// We are in the middle of a path, so don't set the final goal location yet.
		CRITTER_LOG((log, "CritterDesync: setAdjustDestination(FALSE) 40"));
		m_adjustDestinations = false;
	}
	else
	{
		CRITTER_LOG((log, "CritterDesync: setAdjustDestination(m_adjustFinal=%s) 41", m_adjustFinal ? "TRUE" : "FALSE"));
		m_adjustDestinations = m_adjustFinal;
		ai->setPathExtraDistance(0);

		// urg. hacky. if we are a projectile on the last segment, turn on precise z-pos.
		if (obj->isKindOfProjectile())
		{
			if (ai && ai->getCurLocomotor())
				ai->getCurLocomotor()->setUsePreciseZPos(true);
		}
	}
	return ret;
}

//----------------------------------------------------------------------------------------------------------
StateReturnType AIFollowPathState::update()
{
	getMachine()->setGoalPosition(&m_goalPosition);
	// do movement
	StateReturnType status = AIInternalMoveToState::update();
	// if move to has finished, move to next point on path
	if (status == STATE_SUCCESS || status == STATE_FAILURE)
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		if (status == STATE_FAILURE && m_retryCount>0) { 
			// If we failed, & haven't reached retry limit, try again.  jba.
			m_retryCount--;
		}	else {
			++m_index;
		}
		const Coord3D *pos = ai->friend_getGoalPathPosition( m_index );

		Bool tooClose=true;
		while (pos && tooClose) {
			Real dx = pos->x - obj->getPosition()->x;
			Real dy = pos->y - obj->getPosition()->y;
			tooClose = false;
			if (sqr(dx) + sqr(dy) < sqr(PATHFIND_CELL_SIZE_F)) {
				tooClose = true;
			}
			if (tooClose) {
				m_index++;
				pos = ai->friend_getGoalPathPosition(m_index);
			}
		}
		

		//Assign this value to the AIUpdateInterface so object's can access this value while
		//determine which waypoints to plot in the waypoint renderer.
		ai->friend_setCurrentGoalPathIndex( m_index ); 
		if (pos == NULL)
		{
			// reached the end of the path
			return STATE_SUCCESS;
		}

		ai->rva00262ACE(); // friend_startingMove
		// set next movement goal
		m_goalPosition = *pos;
 		const Coord3D *nextPos = ai->friend_getGoalPathPosition( m_index+1 );

 		if (nextPos) 
		{
			Coord2D delta;
			delta.x = nextPos->x - pos->x;
			delta.y = nextPos->y - pos->y;
			Real offset = delta.length();
 			const Coord3D *followingPos = ai->friend_getGoalPathPosition( m_index+2 );
			if (followingPos) offset += 4*PATHFIND_CELL_SIZE_F;
			ai->setPathExtraDistance(offset);
			// We are in the middle of a path, so don't set the final goal location yet.
			CRITTER_LOG((log, "CritterDesync: setAdjustDestination(FALSE) 42"));
			m_adjustDestinations = false;
		} 
		else 
		{
			CRITTER_LOG(((FILE *)theLogicRandomLogFile, "CritterDesync: setAdjustDestination(m_adjustFinal=%s && (m_adjustFinalOverride=%s || ai->isDoingGroundMovement()=%s) 43",
				m_adjustFinal ? "TRUE" : "FALSE", m_adjustFinalOverride ? "TRUE" : "FALSE", ai->isDoingGroundMovement() ? "TRUE" : "FALSE"));
			setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ai->isDoingGroundMovement()));
			if (getAdjustsDestination()) 
			{
				if (!TheAI->pathfinder()->AdjustDestination(getMachineOwner(), ai->getLocomotorSet(), &m_goalPosition)) {
					return STATE_FAILURE;
				}
				getMachineOwner()->rva0028ACDC((int)&m_goalPosition);
			}

			// urg. hacky. if we are a projectile on the last segment, turn on precise z-pos.
			if (obj->isKindOfProjectile())
			{
				if (ai && ai->getCurLocomotor())
					ai->getCurLocomotor()->setUsePreciseZPos(true);
			}
		}
		CRITTER_LOG((log, "CritterDesync: ComputePath32"));
		computePath();
		return STATE_CONTINUE;
	}

	return status;
}
