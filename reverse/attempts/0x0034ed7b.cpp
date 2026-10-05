// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9938 date=2026-10-05
// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.989 date=2026-10-05
// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.989214175654854 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
//
// AIWanderState::onEnter, retail 0x0034F1E1 (278 bytes): slot 4 of the
// vtable whose slot-2 name getter returns AIWanderState. Ported from Zero
// Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference); the class model is
// shared with the banked AIWanderInPlaceState attempt (same unit, same
// REAL_TO_INT_FLOOR shape).
// BFME2 layout (target evidence): machine goal waypoint +0x48; state
// m_groupOffset +0x4C, m_currentWaypoint +0x5C, m_priorWaypoint +0x60,
// m_waitFrames +0x68, m_timer +0x6C; locomotor template wander width factor
// +0xF0. PATHFIND_CELL_SIZE is applied as an Int before the float
// conversion. Callees: the pinned AIFollowWaypointPathState::computeGoal,
// AIInternalMoveToState::onEnter, AIFollowWaypointPathState::
// calcExtraPathDistance (pinned at 0x00340FCD: it walks up to five waypoints
// from m_currentWaypoint, as Zero Hour's does) and the pinned
// AIUpdateInterface::setPathExtraDistance.
// AIFollowWaypointPathState::onEnter, retail 0x0034ED7B (649 bytes): slot 4
// of vtable 0x00C12930, independently named by its slot-2 getter at 0x00342BF6;
// the attack-follow and evacuate slot-4 bodies both tail-call this RVA. The
// common body is Zero Hour's AIStates.cpp. Target-specific evidence is the
// cached group-offset test at owner+0x410 with floats at +0x414/+0x418, the
// CritterDesync 54/55 logs, and the position/layer forwarder at 0x0028ACEE.
// The meaning of the cached owner fields is inferred; their offsets and uses
// are read directly from the retail body.
// AIWanderState::update, retail 0x0034A1BB (360 bytes): slot 6 of the same
// vtable, Zero Hour's body plus BFME 2's additions (target evidence): it
// first sets model-condition bit 4*32+2 on the owner (Object +0x11C bit 2,
// with the rowed notifier Object::rva0028AE6D) when not yet set, and logs
// "CritterDesync: ComputePath39" through the debug log globals before the
// state's computePath (vslot 17). Callees pinned from the call sites:
// Object::getVisionRange 0x0028DDE0, AI::findClosestRepulsor 0x002FDC9A,
// AIFollowWaypointPathState::getNextWaypoint 0x00340F7C (Zero Hour's: random
// link of m_currentWaypoint, m_priorWaypoint, goal position).
// AIFollowWaypointPathState::getNextWaypoint, retail 0x00340F7C (67 bytes),
// is Zero Hour's ALLOW_BACKTRACK body over a local copy of m_currentWaypoint
// read after the random draw (random link, prior waypoint, goal
// position through the pinned StateMachine::setGoalPosition 0x00262224);
// calcExtraPathDistance, retail 0x00340FCD (110 bytes), is Zero Hour's body
// over the rowed Coord2D::length 0x00003755.
// AIPanicState::onEnter, retail 0x0034F505 (293 bytes), and update, retail
// 0x0034A38E (333 bytes): slots 4 and 6 of the vtable whose slot-2 name getter
// returns AIPanicState; Zero Hour's bodies on the same layout, with
// MODELCONDITION_PANICKING at bit 2*32+13 (Object +0x114 mask 0x2000) and
// BFME 2's "CritterDesync: ComputePath40" log before computePath.
typedef bool Bool;
#define NULL 0
#define FAST_AS_POSSIBLE 999999.0f
enum ModelConditionFlagType
{
	MODELCONDITION_PANICKING = 2 * 32 + 13,
	MODELCONDITION_BFME_130 = 4 * 32 + 2
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
typedef float Real;
typedef int Int;
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
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_WANDER = 3
};
struct Coord3D
{
	Real x, y, z;
};
#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

extern "C" __declspec(dllimport) double __cdecl floor(double);
static __forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}
static __forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AISTATES_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp"

class LocomotorTemplate
{
public:
	Real getWanderWidthFactor() const { return m_wanderWidthFactor; }
	Real getWanderAboutPointRadius() const { return m_wanderAboutPointRadius; }
private:
	unsigned char m_pad00[0xF0];
	Real m_wanderWidthFactor; // +0xF0
	unsigned char m_padF4[0xF8 - 0xF4];
	Real m_wanderAboutPointRadius; // +0xF8
};
class Locomotor
{
public:
	Real getWanderWidthFactor() const { return m_template->getWanderWidthFactor(); }
	Real getWanderAboutPointRadius() const { return m_template->getWanderAboutPointRadius(); }
	void setUsePreciseZPos(Bool use)
	{
		if (use)
			m_flags |= 8;
		else
			m_flags &= ~8;
	}
private:
	unsigned char m_pad00[0x04];
	const LocomotorTemplate *m_template; // +0x04
	unsigned char m_pad08[0x44 - 0x08];
	unsigned int m_flags; // +0x44
};
class Waypoint;
class LocomotorSet;
class RadarObject;
class Team;
class Pathfinder;
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
// isDoingGroundMovement is vslot 137 (+0x224); chooseLocomotorSet is vslot
// 142 (+0x238).
class AIUpdateInterface : public AIUpdateSlots<137>
{
public:
    virtual Bool isDoingGroundMovement() const;
    virtual void slot138() = 0;
    virtual void slot139() = 0;
    virtual void slot140() = 0;
    virtual void slot141() = 0;
    virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
    Locomotor *getCurLocomotor() { return m_curLocomotor; }
    RadarObject *rva002630F5();
    void setDesiredSpeed(Real speed);
    void setPathExtraDistance(Real dist);
    void setCompletedWaypoint(const Waypoint *wp);
    const LocomotorSet &getLocomotorSet() const
    {
        return *reinterpret_cast<const LocomotorSet *>(reinterpret_cast<const char *>(this) + 0x1CC);
    }
private:
    unsigned char m_pad004[0x1CC - 0x04];
    unsigned char m_pad1CC[0x1F0 - 0x1CC];
    Locomotor *m_curLocomotor; // +0x1F0
    unsigned char m_pad1F4[0x3C7 - 0x1F4];
public:
    Bool m_flag3C7; // +0x3C7
};
class ThingTemplate
{
public:
    Bool isKindOfCanBeRepulsed() const { return (m_kindOf[1] & 0x20) != 0; }
    Bool isKindOfProjectile() const { return (m_projectileKindFlags & 0x02) != 0; }
private:
    unsigned char m_pad00[0x10B];
    unsigned char m_projectileKindFlags; // +0x10B, retail test at 0x0034EFE5
    unsigned char m_kindOf[4]; // +0x10C (CAN_BE_REPULSED: byte +0x10D mask 0x20)
};
class Team
{
public:
    void setCurrentWaypoint(const Waypoint *waypoint) { m_currentWaypoint = waypoint; }
    const Waypoint *getCurrentWaypoint() const { return m_currentWaypoint; }
private:
    unsigned char m_pad00[0x6C];
    const Waypoint *m_currentWaypoint; // +0x6C
};
class Object
{
public:
    const Coord3D *getPosition() const { return &m_position; }
    unsigned int getID() const { return m_id; }
    AIUpdateInterface *getAI() { return m_ai; }
    Team *getTeam() { return m_team; }
    Bool isKindOfCanBeRepulsed() const { return m_template->isKindOfCanBeRepulsed(); }
    Bool isKindOfProjectile() const { return m_template->isKindOfProjectile(); }
    Real getVisionRange() const;
    void rva0028AE6D();
    void rva0028ACEE(const Coord3D *position, int layer);
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	unsigned int m_id; // +0x74
	unsigned char m_pad78[0x10C - 0x78];
    ModelConditionFlags m_modelConditionFlags; // +0x10C
    unsigned char m_pad158[0x258 - 0x158];
    AIUpdateInterface *m_ai; // +0x258
public:
    unsigned char m_pad25C[0x304 - 0x25C];
    Team *m_team; // +0x304
    unsigned char m_pad308[0x410 - 0x308];
    unsigned int m_bfmeGroupOffsetPresent410; // target-observed dword +0x410
    Real m_bfmeGroupOffsetX414; // target-observed float +0x414
    Real m_bfmeGroupOffsetY418; // target-observed float +0x418
};
class AI
{
public:
    Object *findClosestRepulsor(const Object *me, Real range);
    Pathfinder *pathfinder() { return m_pathfinder; }
private:
    unsigned char m_pad00[0x10];
    Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
class Pathfinder
{
public:
    Bool adjustDestination(Object *object, const LocomotorSet &locomotorSet,
        Coord3D *destination, const Coord3D *other = 0);
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	void setGoalPosition(const Coord3D *pos);
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class AIStateMachine : public StateMachine
{
public:
	const Waypoint *getGoalWaypoint() { return m_goalWaypoint; }
private:
	unsigned char m_pad18[0x48 - 0x18];
	const Waypoint *m_goalWaypoint; // +0x48
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
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
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
	virtual Bool computePath();
protected:
    void setAdjustsDestination(Bool value) { m_adjustDestination = value; }
    Bool getAdjustsDestination() const;
    unsigned char m_pad1C[0x20 - 0x1C];
    Coord3D m_goalPosition; // +0x20
    unsigned int m_bfmeStateValue2C; // opaque target field
    Int m_goalLayer; // +0x30, passed to Object::rva0028ACEE
    unsigned char m_pad34[0x48 - 0x34];
    Bool m_adjustDestination; // +0x48
    unsigned char m_pad49[0x4C - 0x49];
};
struct Coord2D
{
	Real x, y;
	Real length() const;
};
// Waypoint (target evidence): location +0x0C, link count +0x4C; getLink is
// the rowed out-of-line 0x00085404.
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	Int getNumLinks() const { return m_numLinks; }
	Waypoint *getLink(Int ndx) const;
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_location; // +0x0C
	unsigned char m_pad18[0x4C - 0x18];
	Int m_numLinks; // +0x4C
};
class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
    virtual StateReturnType onEnter();
    void computeGoal(Bool useGroupOffsets);
    Real calcExtraPathDistance(void);
    const Waypoint *getNextWaypoint(void);
    Bool hasNextWaypoint(void) { return m_currentWaypoint->getNumLinks() > 0; }
protected:
    Coord2D m_groupOffset; // +0x4C
    Real m_angle; // +0x54
    Int m_framesSleeping; // +0x58
    const Waypoint *m_currentWaypoint; // +0x5C
    const Waypoint *m_priorWaypoint; // +0x60
    Bool m_appendGoalPosition; // +0x64
    Bool m_moveAsGroup; // +0x65
    Bool m_isFollowWaypointPathState; // +0x66
};
class AIGroup
{
public:
    Real getSpeed();
    Bool getCenter(Coord3D *center);
};
extern "C" double sqrt(double);

// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ present-unmatched
StateReturnType AIFollowWaypointPathState::onEnter()
{
    m_appendGoalPosition = false;
    m_priorWaypoint = NULL;
    m_currentWaypoint = ((AIStateMachine *)getMachine())->getGoalWaypoint();
    AIUpdateInterface *ai = getMachineOwner()->getAI();

    if (m_currentWaypoint == NULL && !m_moveAsGroup)
        return STATE_FAILURE;

    getMachine()->setGoalPosition(m_currentWaypoint->getLocation());

    m_framesSleeping = 0;
    m_groupOffset.x = m_groupOffset.y = 0;
    volatile Coord2D &groupOffset = m_groupOffset;

    Object *obj = getMachineOwner();
    Real speed = FAST_AS_POSSIBLE;
    if (m_moveAsGroup && m_currentWaypoint)
    {
        obj->getTeam()->setCurrentWaypoint(m_currentWaypoint);
        if (obj->m_bfmeGroupOffsetPresent410)
        {
            struct CachedGroupOffsetWords
            {
                Int x;
                Int y;
            } cachedGroupOffset;
            cachedGroupOffset.x = *(Int *)&obj->m_bfmeGroupOffsetX414;
            cachedGroupOffset.y = *(Int *)&obj->m_bfmeGroupOffsetY418;
            groupOffset.x = *(Real *)&cachedGroupOffset.x;
            groupOffset.y = *(Real *)&cachedGroupOffset.y;
        }
        else
        {
            AIGroup *group = (AIGroup *)ai->rva002630F5();
            if (group)
            {
                speed = group->getSpeed();
                Coord3D center;
                group->getCenter(&center);
                groupOffset.x = obj->getPosition()->x - center.x;
                groupOffset.y = obj->getPosition()->y - center.y;
                Real offsetX = m_groupOffset.x;
                Real offsetY = m_groupOffset.y;
                Real length = sqrt(offsetY * offsetY + offsetX * offsetX);
                if (150.0f < length)
                {
                    Real scale = 150.0f / length;
                    m_groupOffset.x = m_groupOffset.x * scale;
                    m_groupOffset.y = m_groupOffset.y * scale;
                }
            }
        }
    }
    if (m_currentWaypoint == NULL && m_moveAsGroup)
        m_currentWaypoint = obj->getTeam()->getCurrentWaypoint();

    computeGoal(m_moveAsGroup);
    StateReturnType ret = AIInternalMoveToState::onEnter();

    ai->setDesiredSpeed(speed);
    ai->setPathExtraDistance(calcExtraPathDistance());
    if (hasNextWaypoint())
    {
        if (g_00E03745)
        {
            FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
            if (log != NULL)
                fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 54");
        }
        setAdjustsDestination(false);
    }
    else
    {
        if (g_00E03745)
        {
            if (g_00DFEFF0 != 0)
                fprintf((FprintfTarget *)g_00DFEFF0,
                    "CritterDesync: setAdjustDestination(ai->isDoingGroundMovement()=%s) 55",
                    ai->isDoingGroundMovement() ? "TRUE" : "FALSE");
        }
        setAdjustsDestination(ai->isDoingGroundMovement());
        if (getAdjustsDestination())
        {
            if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(), ai->getLocomotorSet(),
                &m_goalPosition, 0))
                return STATE_FAILURE;
            getMachineOwner()->rva0028ACEE(&m_goalPosition, m_goalLayer);
        }
        if (obj->isKindOfProjectile())
        {
            if (ai && ai->getCurLocomotor())
                ai->getCurLocomotor()->setUsePreciseZPos(true);
        }
    }
    return ret;
}

class AIWanderState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
    Int m_waitFrames; // +0x68
	Int m_timer; // +0x6C
};

class AIPanicState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
    Int m_waitFrames; // +0x68
	Int m_timer; // +0x6C
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIWanderState::onEnter()
{
	m_currentWaypoint = ((AIStateMachine *)getMachine())->getGoalWaypoint();

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	m_priorWaypoint = NULL;
	if (m_currentWaypoint == NULL || ai==NULL)
		return STATE_FAILURE;
	m_groupOffset.x = m_groupOffset.y = 0;
	Locomotor* curLoco = ai->getCurLocomotor();
	if (curLoco && curLoco->getWanderWidthFactor() > 0.0f) {
		Int delta = REAL_TO_INT_FLOOR(curLoco->getWanderWidthFactor()+0.5f);
		if (delta<1) delta = 1;
		m_groupOffset.x = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10579)*PATHFIND_CELL_SIZE;
		m_groupOffset.y = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10580)*PATHFIND_CELL_SIZE;
	}
	m_timer = 0;
	m_waitFrames = 10 + (getMachineOwner()->getID() & 0x7);
	// set initial movement goal
	computeGoal(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	ai->setPathExtraDistance(calcExtraPathDistance());
	return ret;
}

//----------------------------------------------------------------------------------------------------------
StateReturnType AIWanderState::update()
{
	// do movement
	Object *obj = getMachineOwner();
	obj->setModelConditionState(MODELCONDITION_BFME_130);
	StateReturnType status = AIInternalMoveToState::update();
	if (obj->isKindOfCanBeRepulsed()) {
		m_timer--;
		if (m_timer<0) {
			m_timer = m_waitFrames;
			Object* enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
			if (enemy) {
				return STATE_FAILURE;
			}
		}
	}
	// if move to has finished, move to next point on waypoint path
	if (status != STATE_CONTINUE)
	{
		AIUpdateInterface *ai = obj->getAI();

		m_currentWaypoint = getNextWaypoint();
		// if there are no links from this waypoint, we're done
		if (m_currentWaypoint == NULL)	{
			/// Trigger "end of waypoint path" scripts (jba)
			ai->setCompletedWaypoint(m_priorWaypoint);
			
			return STATE_SUCCESS;
		}

		Locomotor* curLoco = ai->getCurLocomotor();
		if (curLoco && curLoco->getWanderWidthFactor() > 0.0f) {
			Int delta = REAL_TO_INT_FLOOR(curLoco->getWanderWidthFactor()+0.5f);
			if (delta<1) delta = 1;
			m_groupOffset.x = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10630)*PATHFIND_CELL_SIZE;
			m_groupOffset.y = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10631)*PATHFIND_CELL_SIZE;
		}
		computeGoal(false);
		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log)
				fprintf(log, "CritterDesync: ComputePath39");
		}
		computePath();
		return STATE_CONTINUE;
	}
	// Never leave this state until told to.
	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------------------
StateReturnType AIPanicState::onEnter()
{
	m_currentWaypoint = ((AIStateMachine *)getMachine())->getGoalWaypoint();

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	if (m_currentWaypoint == NULL)
		return STATE_FAILURE;
	// set initial movement goal
	Locomotor* curLoco = ai->getCurLocomotor();
	if (curLoco && curLoco->getWanderWidthFactor() > 0.0f) {
		Int delta = REAL_TO_INT_FLOOR(curLoco->getWanderWidthFactor()+0.5f);
		if (delta<1) delta = 1;
		m_groupOffset.x = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10797)*PATHFIND_CELL_SIZE;
		m_groupOffset.y = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10798)*PATHFIND_CELL_SIZE;
	}
	computeGoal(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();

	m_timer = 0;
	m_waitFrames = 10 + (getMachineOwner()->getID() & 0x7);
	// Update the extra path distance.   AIInternalMoveToState::onEnter resets it.
	ai->setPathExtraDistance(calcExtraPathDistance());
	if (obj)
	{
		obj->setModelConditionState(MODELCONDITION_PANICKING);
	}

	return ret;
}

//----------------------------------------------------------------------------------------------------------
StateReturnType AIPanicState::update()
{
	// do movement
	StateReturnType status = AIInternalMoveToState::update();

	Object *obj = getMachineOwner();
	if (obj->isKindOfCanBeRepulsed()) {
		m_timer--;
		if (m_timer<0) {
			m_timer = m_waitFrames;
			Object* enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
			if (enemy) {
				return STATE_FAILURE;
			}
		}
	}

	// if move to has finished, move to next point on waypoint path
	if (status == STATE_SUCCESS)
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();

		m_currentWaypoint = getNextWaypoint();
		// if there are no links from this waypoint, we're done
		if (m_currentWaypoint == NULL)	{
			/// Trigger "end of waypoint path" scripts (jba)
			ai->setCompletedWaypoint(m_priorWaypoint);
			
			return STATE_SUCCESS;
		}
		Locomotor* curLoco = ai->getCurLocomotor();
		if (curLoco && curLoco->getWanderWidthFactor() > 0.0f) {
			Int delta = REAL_TO_INT_FLOOR(curLoco->getWanderWidthFactor()+0.5f);
			if (delta<1) delta = 1;
			m_groupOffset.x = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10851)*PATHFIND_CELL_SIZE;
			m_groupOffset.y = GetGameLogicRandomValue(-delta, delta, AISTATES_FILE, 10852)*PATHFIND_CELL_SIZE;
		}
		computeGoal(false);
		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log)
				fprintf(log, "CritterDesync: ComputePath40");
		}
		computePath();
		return STATE_CONTINUE;
	}
	// Never leave this state until told to.
	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------------------
const Waypoint * AIFollowWaypointPathState::getNextWaypoint(void)
{
	Int linkCount = m_currentWaypoint->getNumLinks();
	Int which = GetGameLogicRandomValue( 0, linkCount-1, AISTATES_FILE, 9814 );
	const Waypoint *curWay = m_currentWaypoint;
	const Waypoint *nextWay = curWay->getLink( which );
	m_priorWaypoint = curWay;

	getMachine()->setGoalPosition(curWay->getLocation());// THANKS, JOHN
	return nextWay;
}

//----------------------------------------------------------------------------------------------------------
Real AIFollowWaypointPathState::calcExtraPathDistance(void)
{
	Real extra = PATHFIND_CELL_SIZE_F/10.0f;
	const Waypoint *curWay = m_currentWaypoint;
	Int limit = 5; // just look ahead 5, in case of circular paths.  jba
	while (curWay && limit>0) {
		limit--;
		Int linkCount = curWay->getNumLinks();
		if (linkCount == 0) return extra;
		Int which = 0;
		const Waypoint *nextWay = curWay->getLink( which );
		Coord2D delta;
		delta.x = nextWay->getLocation()->x - curWay->getLocation()->x;
		delta.y = nextWay->getLocation()->y - curWay->getLocation()->y;
		extra += delta.length();
		curWay = nextWay;
	}
	return extra;
}
