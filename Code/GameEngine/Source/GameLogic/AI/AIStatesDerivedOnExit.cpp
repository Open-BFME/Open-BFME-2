// cl: /O1 /DNDEBUG /MD /G7
//
// Derived AI state onExit overrides chaining to the rowed
// AIInternalMoveToState::onExit 0x003473A4, transferred from Zero Hour
// AIStates.cpp. Each class is identified by its vtable's slot-2 name getter
// (the state's own name literal) and the matching ZH body.
// AIAttackMoveToState::onExit, retail 0x0034A011 (28 bytes): slot 5 of vtable
// 0x00C13548 (name getter 0x00345CFA, AIAttackMoveToState; the same class as
// the placeholder rows Rva00345CAB); m_attackMoveMachine at +0x54 is set to
// AI_IDLE through StateMachine virtual slot 8, then the inherited
// AIMoveToState::onExit (not overridden, so the base 0x003473A4).
// AIFollowWaypointPathState::onExit, retail 0x0034A0D7 (46 bytes): slot 5 of
// vtable 0x00C12930 (name getter 0x00342BF6); base onExit, then clears the
// current locomotor's precise-z flag (bit 3 of Locomotor+0x44, the ZH
// PRECISE_Z_POS position; AI+0x1F0 is the current locomotor). BFME2 drops the
// ZH setUltraAccurate(false) call.
// AIAttackFollowWaypointPathState::onEnter/onExit/update, retail 0x0034F1C4 (29
// bytes), 0x0034A19F (28 bytes) and 0x0035426B (340 bytes): slots 4/5/6 of
// vtable 0x00C13638 (name getter AIAttackFollowWaypointPathState, a class BFME1
// rows by ctor, dtor and update); m_attackFollowMachine at +0x68 (BFME1 +0x6C)
// is cleared and set to AI_IDLE before the base onEnter (pinned 0x0034ED7B,
// tail jump), and set to AI_IDLE before the base onExit, as Zero Hour
// AIAttackMoveToState does with its attack-move machine. Machine slots 4/5/8/14
// are update/clear/setState/setGoalObject. Update checks attack-follow machine
// idle, clears model-condition flags, picks up crates or victim mood targets,
// optionally repaths with desync log, and chains to base update 0x00353F13.
// AIFollowWaypointPathStateAndEvacuate::onEnter/onExit, retail 0x0034F004 (23
// bytes) and 0x0034A105 (28 bytes): slots 4/5 of vtable 0x00C12998 (name getter
// AIFollowWaypointPathStateAndEvacuate); onEnter calls Rva0033FA64Do(owner)
// before base onEnter (0x0034ED7B); onExit calls base onExit (0x0034A0D7)
// before Rva0033FA79Do(owner). Its update, retail 0x003541F4 (119 bytes,
// slot 6), runs the base update (pinned 0x00353F13) and then succeeds once
// the point of the AI's path (+0x140) at the owner's +0xB8 distance fails
// the pinned pathfinder cell test 0x002E996E, handing the owner and machine
// to the pinned evacuate helper 0x003532BF (with false) on success, as the
// AIMoveToAndEvacuateState update in AIStatesEvacuate.cpp does.
// AIFollowWaypointPathState::update, retail 0x00353F13 (737 bytes): slot 6 of
// vtable 0x00C12930, the base update the two derived updates above chain to.
// Zero Hour's AIStates.cpp body with BFME 2's changes: Path::appendNode takes
// a third argument (0x7FFFFFFF), the pathfinder's updateGoal is the rowed
// Object::rva0028ACEE on the owner, and both repaths log critter desync 36
// and 37 before computePath. The state's fields (+0x58 sleep frames, +0x5C
// current and +0x60 prior waypoint, +0x64 append-goal, +0x65 move-as-group,
// +0x66 follow-path flag) and the AI's (+0x20 command interface, +0x28/+0x2C
// waypoint ids, +0x1CC locomotor set, +0x3B1 waiting-for-path, slot 137
// isDoingGroundMovement) are read from this body; the skirmish fudge factor is
// TAiData +0x58.
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
typedef bool Bool;
typedef unsigned int StateID;
enum
{
	AI_IDLE = 0
};
class Locomotor
{
public:
	enum LocoFlag
	{
		PRECISE_Z_POS = 3
	};
	void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
private:
	void setFlag(LocoFlag f, bool b)
	{
		if (b)
			m_flags |= (1 << f);
		else
			m_flags &= ~(1 << f);
	}
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
template <int N> class AIDeadStateAISlots : public AIDeadStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIDeadStateAISlots<0>
{
};
class Object;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line length (rowed 0x00003571) that AIFollowWaypointPathState::update calls; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
};
enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};
enum MoodMatrixAction
{
	MM_Action_Move = 1
};
enum
{
	MAA_Action_To_AttackMove = 0x04
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
enum
{
	NO_MAX_SHOTS_LIMIT = 0x7FFFFFFF
};
class Waypoint
{
public:
	UnsignedInt getID() const { return m_id; }
	const Coord3D *getLocation() const { return &m_location; }
private:
	unsigned char m_pad00[4];
	UnsignedInt m_id; // +0x04
	unsigned char m_pad08[0x0C - 0x08];
	Coord3D m_location; // +0x0C
};
class AIGroup
{
public:
	Bool getCenter(Coord3D *center);
};
// The rowed group member count runs on the AIGroup (address-derived name).
class Rva0036E346
{
public:
	Int rva0036E346();
};
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *aiGroup);
	const Waypoint *getCurrentWaypoint() { return m_currentWaypoint; }
	void setCurrentWaypoint(const Waypoint *way) { m_currentWaypoint = way; }
private:
	unsigned char m_pad00[0x6C];
	const Waypoint *m_currentWaypoint; // +0x6C
};
class Player
{
public:
	Bool isSkirmishAIPlayer();
};
class LocomotorSet;
// What the path's 0x003642DF returns by value (16 bytes): a node and a
// position (as in AIUpdateInterfacePrivateCommands.cpp). Unnamed.
struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};
class Path
{
public:
	Rva003642DFResult rva003642DF(float dist);
	// Zero Hour's appendNode with a BFME 2 third argument.
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int bfmeArg);
};
class Pathfinder
{
public:
	bool IsBuildRestrictedCell(const Coord3D *pos, bool flagA, bool flagB, int layer);
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest,
		const Coord3D *groupDest);
};
struct TAiData
{
	unsigned char m_pad00[0x58];
	Real m_skirmishGroupFudgeValue; // +0x58
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const TAiData *getAiData() { return m_aiData; }
	AIGroup *createGroup();
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;
// The AI's command interface (+0x20) entries for the attack-follow commands.
class Rva00352F9D
{
public:
	void rva00352F9D(const void *way, int maxShots, CommandSourceType cmdSource);
};
class Rva00352F2FOpaque
{
public:
	void invoke(const Waypoint *way, int maxShots, CommandSourceType cmdSource);
};
class AIUpdateInterface : public AIDeadStateAISlots<136>
{
public:
	virtual void setLocomotorGoalNone() = 0; // slot 136
	virtual Bool isDoingGroundMovement() const = 0; // slot 137
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	Object *checkForCrateToPickup();
	Object *getNextMoodTarget(Bool calm, Bool alwaysAttack);
	Path *getPath() const { return m_path; }
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void aiAttackFollowWaypointPath(const Waypoint *way, Int maxShotsToFire, CommandSourceType cmdSource)
	{
		((Rva00352F2FOpaque *)m_commandInterface)->invoke(way, maxShotsToFire, cmdSource);
	}
	void aiAttackFollowWaypointPathAsTeam(const Waypoint *way, Int maxShotsToFire, CommandSourceType cmdSource)
	{
		((Rva00352F9D *)m_commandInterface)->rva00352F9D(way, maxShotsToFire, cmdSource);
	}
	Bool isWaitingForPath() const { return m_isWaitingForPath; }
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_locomotorSet; }
	void setPriorWaypointID(UnsignedInt id) { m_priorWaypointID = id; }
	void setCurrentWaypointID(UnsignedInt id) { m_currentWaypointID = id; }
	void setCompletedWaypoint(const Waypoint *way);
	// Zero Hour's friend_startingMove.
	void rva00262ACE();
private:
	unsigned char m_pad004[0x20 - 4];
	unsigned char m_commandInterface[0x28 - 0x20]; // +0x20
	UnsignedInt m_priorWaypointID; // +0x28
	UnsignedInt m_currentWaypointID; // +0x2C
	unsigned char m_pad030[0x140 - 0x30];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x1CC - 0x144];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B1 - (0x1F0 + sizeof(Locomotor *))];
	Bool m_isWaitingForPath; // +0x3B1
	unsigned char m_pad3B2[0x3C7 - 0x3B2];
public:
	Bool m_flag3C7; // +0x3C7
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	// Zero Hour's Pathfinder::updateGoal for this object (goal, layer).
	void rva0028ACEE(int goalPos, int layer);
	float getBfmeRealB8() const { return m_bfmeRealB8; }
	unsigned char m_pad000[0xB8];
	float m_bfmeRealB8; // +0xB8
	unsigned char m_pad0BC[0x10C - 0xBC];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
};
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);
class Object0033FA79;
void Rva0033FA79Do(const Object0033FA79 *obj);
class StateMachine;
void rva003532BF(Object *owner, StateMachine *machine, bool flag);
class State;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType updateStateMachine();
	virtual void clear();
	virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(Object *object);
	Object *getOwner() const { return m_owner; }
	void setGoalPosition(const Coord3D *pos);
	Bool isInIdleState() const;
private:
	State *m_currentState; // +0x4
	unsigned char m_pad08[0x14 - 8];
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
	virtual void slot07();
	virtual Bool isIdle() const;
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual void computePath();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateMachine *getMachine() const { return m_machine; }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
// ?isInIdleState@StateMachine@@ present-unmatched
inline Bool StateMachine::isInIdleState() const
{
	return m_currentState ? m_currentState->isIdle() : true;
}
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Bool getAdjustsDestination() const;
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x30 - 0x2C];
	Int m_goalLayer; // +0x30 (PathfindLayerEnum)
	unsigned char m_pad34[0x4C - 0x34];
};
class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
void AIMoveToState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
}
class AIAttackMoveToState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad4C[0x54 - 0x4C];
	StateMachine *m_attackMoveMachine; // +0x54
};
void AIAttackMoveToState::onExit(StateExitType status)
{
	m_attackMoveMachine->setState(AI_IDLE);
	AIMoveToState::onExit(status);
}
class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	void computeGoal(Bool useGroupOffsets);
	const Waypoint *getNextWaypoint();
protected:
	unsigned char m_pad4C[0x58 - 0x4C];
	Int m_framesSleeping; // +0x58
	const Waypoint *m_currentWaypoint; // +0x5C
	const Waypoint *m_priorWaypoint; // +0x60
	Bool m_appendGoalPosition; // +0x64
	Bool m_moveAsGroup; // +0x65
	Bool m_isFollowWaypointPathState; // +0x66
};
void AIFollowWaypointPathState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	// turn off precision-z-pos when we exit, just in case.
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai && ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);
}
class AIAttackFollowWaypointPathState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	StateMachine *m_attackFollowMachine; // +0x68
};
StateReturnType AIAttackFollowWaypointPathState::onEnter()
{
	m_attackFollowMachine->clear();
	m_attackFollowMachine->setState(AI_IDLE);
	return AIFollowWaypointPathState::onEnter();
}
void AIAttackFollowWaypointPathState::onExit(StateExitType status)
{
	m_attackFollowMachine->setState(AI_IDLE);
	AIFollowWaypointPathState::onExit(status);
}
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, text);
	}
}

StateReturnType AIAttackFollowWaypointPathState::update()
{
	Object *owner = m_machine->getOwner();
	AIUpdateInterface *ai = owner->getAI();

	Bool forceRetarget = false;
	Bool shouldRepath = false;
	Object *victim = 0;

	if (!m_attackFollowMachine->isInIdleState())
	{
		ai->setLocomotorGoalNone();

		clearModelConditionBit(owner, 61);
		clearModelConditionBit(owner, 156);

		m_attackFollowMachine->updateStateMachine();

		if (m_attackFollowMachine == 0 || !m_attackFollowMachine->isInIdleState())
			return STATE_CONTINUE;

		forceRetarget = true;
		shouldRepath = true;
	}

	if (m_attackFollowMachine->isInIdleState())
	{
		Object *crate = ai->checkForCrateToPickup();
		if (crate != 0)
		{
			m_attackFollowMachine->setGoalObject(crate);
			m_attackFollowMachine->setState(0x27);
			return STATE_CONTINUE;
		}

		victim = ai->getNextMoodTarget(!forceRetarget, false);
		if (victim != 0)
		{
			m_attackFollowMachine->setGoalObject(victim);
			m_attackFollowMachine->setState(0x0a);
			ai->m_flag3C7 = true;
			return STATE_CONTINUE;
		}
	}

	if (shouldRepath)
	{
		computeGoal(m_moveAsGroup);

		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log != 0)
				fprintf(log, "CritterDesync: ComputePath38");
		}

		computePath();
	}

	return AIFollowWaypointPathState::update();
}

class AIFollowWaypointPathStateAndEvacuate : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
StateReturnType AIFollowWaypointPathStateAndEvacuate::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIFollowWaypointPathState::onEnter();
}
void AIFollowWaypointPathStateAndEvacuate::onExit(StateExitType status)
{
	AIFollowWaypointPathState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}
StateReturnType AIFollowWaypointPathStateAndEvacuate::update()
{
	StateReturnType status = AIFollowWaypointPathState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8());
		if (!TheAI->pathfinder()->IsBuildRestrictedCell(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	if (status == STATE_SUCCESS)
		rva003532BF(owner, getMachine(), false);
	return status;
}

StateReturnType AIFollowWaypointPathState::update()
{
	if (m_framesSleeping > 0)
	{
		m_framesSleeping--;
		return STATE_CONTINUE;
	}
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	getMachine()->setGoalPosition(m_currentWaypoint->getLocation());

	UnsignedInt adjustment = ai->getMoodMatrixActionAdjustment(MM_Action_Move);
	if (m_isFollowWaypointPathState && (adjustment & MAA_Action_To_AttackMove))
	{
		if (m_moveAsGroup)
			ai->aiAttackFollowWaypointPathAsTeam(m_currentWaypoint, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
		else
			ai->aiAttackFollowWaypointPath(m_currentWaypoint, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
	}

	if (m_appendGoalPosition)
	{
		Path *thePath = ai->getPath();
		if (!ai->isWaitingForPath() && ai->getPath())
		{
			thePath->rva002655E3(&m_goalPosition, LAYER_GROUND, 0x7FFFFFFF);
			m_appendGoalPosition = false;
		}
	}
	if (m_moveAsGroup && m_currentWaypoint != obj->getTeam()->getCurrentWaypoint())
	{
		m_priorWaypoint = m_currentWaypoint;
		m_currentWaypoint = obj->getTeam()->getCurrentWaypoint();
		if (m_currentWaypoint == 0)
			return STATE_SUCCESS;
		computeGoal(false);
		if (getAdjustsDestination() && ai->isDoingGroundMovement())
		{
			if (!TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(), &m_goalPosition, 0))
				return STATE_FAILURE;
		}
		ai->rva00262ACE();
		critterDesyncLog("CritterDesync: ComputePath36");
		computePath();
		if (getAdjustsDestination())
			obj->rva0028ACEE((int)&m_goalPosition, m_goalLayer);
	}

	StateReturnType status = AIInternalMoveToState::update();

	if (m_moveAsGroup)
	{
		if (obj->getControllingPlayer()->isSkirmishAIPlayer())
		{
			Team *team = obj->getTeam();
			AIGroup *group = TheAI->createGroup();
			team->getTeamAsAIGroup(group);

			Coord3D pos;
			group->getCenter(&pos);

			pos.x -= m_goalPosition.x;
			pos.y -= m_goalPosition.y;
			pos.z = 0;

			Int numInGroup = ((Rva0036E346 *)group)->rva0036E346();
			if (pos.length() <= (numInGroup * TheAI->getAiData()->m_skirmishGroupFudgeValue))
				status = STATE_SUCCESS;
		}
	}

	if (status != STATE_CONTINUE)
	{
		m_currentWaypoint = getNextWaypoint();

		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		if (m_priorWaypoint)
			ai->setPriorWaypointID(m_priorWaypoint->getID());
		if (m_currentWaypoint)
			ai->setCurrentWaypointID(m_currentWaypoint->getID());

		if (m_currentWaypoint == 0)
		{
			ai->setCompletedWaypoint(m_priorWaypoint);
			return STATE_SUCCESS;
		}
		if (m_moveAsGroup)
			obj->getTeam()->setCurrentWaypoint(m_currentWaypoint);

		computeGoal(false);
		if (getAdjustsDestination() && ai->isDoingGroundMovement())
		{
			if (!TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(), &m_goalPosition, 0))
				return STATE_FAILURE;
		}
		ai->rva00262ACE();
		critterDesyncLog("CritterDesync: ComputePath37");
		computePath();
		if (getAdjustsDestination())
			obj->rva0028ACEE((int)&m_goalPosition, m_goalLayer);

		return STATE_CONTINUE;
	}
	return status;
}
