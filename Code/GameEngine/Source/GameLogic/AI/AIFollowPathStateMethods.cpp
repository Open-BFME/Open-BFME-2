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
#define NULL 0
#define PATHFIND_CELL_SIZE_F 10.0f
inline Real sqr(Real x) { return x * x; }
enum
{
	AI_FOLLOW_EXITPRODUCTION_PATH = 7
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
struct Coord3D
{
	Real x, y, z;
};
struct Coord2D
{
	Real x, y;
	Real length() const;
};
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
#define CRITTER_LOG(msg) \
	if (g_00E03745) \
	{ \
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0; \
		if (log) \
			fprintf msg; \
	}
class Locomotor
{
public:
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS
	};
	void setUsePreciseZPos(Bool b)
	{
		if (b)
			m_flags |= (1 << PRECISE_Z_POS);
		else
			m_flags &= ~(1 << PRECISE_Z_POS);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
class AIStateMachine
{
public:
	const Coord3D *getGoalPathPosition(Int i) const;
};
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
	const LocomotorSet &getLocomotorSet(void) const { return *(const LocomotorSet *)m_locomotorSet; }
	void rva00262ACE(); // friend_startingMove
	AIStateMachine *getStateMachine() const { return m_stateMachine; }
	const Coord3D *friend_getGoalPathPosition(Int index) const { return m_stateMachine->getGoalPathPosition(index); }
	void friend_setCurrentGoalPathIndex(Int index) { m_currentGoalPathIndex = index; }
	void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
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
class ThingTemplate
{
public:
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 0x02) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108 (PROJECTILE: byte +0x10B mask 0x02)
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	void rva0028ACDC(int goal);
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isKindOfProjectile() const { return m_template->isKindOfProjectile(); }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};
class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = NULL);
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	void setGoalPosition(const Coord3D *pos);
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	StateID getID() const { return m_ID; }
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
protected:
	virtual Bool computePath();
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	Bool getAdjustsDestination() const;
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};
class AIFollowPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
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

	if (getID() == AI_FOLLOW_EXITPRODUCTION_PATH) {
		ai->setCanPathThroughUnits(true);
		CRITTER_LOG((log, "CritterDesync: setAdjustDestination(FALSE) 39"));
		m_adjustsDestination = false;
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
		m_adjustsDestination = false;
	}
	else
	{
		CRITTER_LOG((log, "CritterDesync: setAdjustDestination(m_adjustFinal=%s) 41", m_adjustFinal ? "TRUE" : "FALSE"));
		m_adjustsDestination = m_adjustFinal;
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
			setAdjustsDestination(false);
		} 
		else 
		{
			CRITTER_LOG(((FprintfTarget *)g_00DFEFF0, "CritterDesync: setAdjustDestination(m_adjustFinal=%s && (m_adjustFinalOverride=%s || ai->isDoingGroundMovement()=%s) 43",
				m_adjustFinal ? "TRUE" : "FALSE", m_adjustFinalOverride ? "TRUE" : "FALSE", ai->isDoingGroundMovement() ? "TRUE" : "FALSE"));
			setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ai->isDoingGroundMovement()));
			if (getAdjustsDestination()) 
			{
				if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(), ai->getLocomotorSet(), &m_goalPosition)) {
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
