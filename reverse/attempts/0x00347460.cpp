// ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
// partial score=0.995 date=2026-10-07
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
// AIAttackMoveToState::update, retail 0x00353C8B (648 bytes): slot 6 of
// vtable 0x00C13548. Zero Hour's update without the jet reload check and
// without the locomotor/MOVING reset: an active attack-move machine first
// adopts the state machine's goal object (and a null machine continues),
// and an idle one picks up crates or a mood target (setting the AI's
// +0x3C7 flag). BFME 2 then re-reads the goal object id (+0x6C) or position
// (+0x60) recorded by onEnter (AIStatesMoreExits.cpp): a vanished goal
// object succeeds, and a goal that moved more than 5 (GetLengthEstimate)
// from the machine's goal is handed back to the machine and forces a repath.
// The retry tail is Zero Hour's (80-unit close enough, sleep three
// LOGICFRAMES_PER_SECOND, the BFME 2 int global g_00DBA4E4); forceRepath
// writes the path goal (+0x34) and the path timestamp (+0x44).
// AIMoveToState::update, retail 0x00353A65 (450 bytes): slot 6 of vtable
// 0x00C11EB8, the base update AIAttackMoveToState::update calls. Zero Hour's
// body without the RIDER8 debug hook and without the physics test: a
// move-to state (+0x4C) whose mood adjusts to attack-move issues the
// pinned attack-move command (0x00295A0F) on the AI's command interface;
// a goal object's position (raised for projectiles by half its geometry's
// pinned max height, Object +0xA8) is led by the rowed speed accessor
// Object::rva0028AC7D and the pinned direction getter 0x0030A8EE unless the
// goal is immobile. KindOf bits are the template's (+4) dword at +0x108
// (PROJECTILE bit 25, IMMOBILE bit 2).
// AIInternalMoveToState::update, retail 0x00347460 (1273 bytes): slot 6 of
// the move-to vtables, the base update the move states above call (pinned).
// Shaped after Open-BFME-1's matched BFME 1 body (AIInternalMoveToStateUpdate
// 00172E70.cpp): no blocked-and-stuck repath, the cliff test, the curLoco
// close-enough MOVING clear, one arrival flag for the close-enough and
// preferred-height (Locomotor +0x40) tests, a 40-unit ground check and the
// AI's +0x160 reset. BFME 2 additions read from retail: a turn to the goal
// angle (+0x2C) while +0x4B is set (normalizeAngle within PI/10 sets the
// orientation and succeeds, else AI slot 135 turns), status 0x31 fails, a
// blocked count (+0x16C) above zero leaves the conditions alone, a moving
// locomotor template's +0x150 byte keeps the cliff conditions, the owner's
// rowed Object::rva0028F4BC module is poked (0, 1, 0, 1) when its +0x3C is
// set, AI state 0x47 scales the repath delay by the int at 0x009BFA3C and
// repaths only past the float at 0x009BFA38, and an arrival hands the
// machine's goal angle (+0x30, FLT_MAX when unset) to the turn.
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
class LocomotorTemplate
{
public:
	unsigned char m_pad000[0x150];
	bool m_bfmeFlag150; // +0x150
};
typedef float Real;
// The rowed 4-byte float getter 0x0008BB38 (fld [ecx+0x40]).
class Rva0008BB38FloatField
{
public:
	Real get() const;
};
class Locomotor
{
public:
	enum LocoFlag
	{
		MOVING_BACKWARDS = 7,
		PRECISE_Z_POS = 3
	};
	void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	const LocomotorTemplate *getTemplate() const { return m_template; }
	Real getCloseEnoughDist() const { return m_closeEnoughDist; }
	Real getPreferredHeight() const { return ((const Rva0008BB38FloatField *)this)->get(); }
	bool isMovingBackwards() const { return ((m_flags >> MOVING_BACKWARDS) & 1) != 0; }
private:
	void setFlag(LocoFlag f, bool b)
	{
		if (b)
			m_flags |= (1 << f);
		else
			m_flags &= ~(1 << f);
	}
	unsigned char m_pad00[0x04];
	const LocomotorTemplate *m_template; // +0x04
	unsigned char m_pad08[0x3C - 0x08];
	Real m_closeEnoughDist; // +0x3C
	Real m_preferredHeight; // +0x40
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
#include "../../Common/GameLogicObjectLookupView.h"
typedef int Int;
typedef unsigned int UnsignedInt;
// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line length (rowed 0x00003571) and GetLengthEstimate (rowed 0x00003ACE) that the updates below call; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
	Real GetLengthEstimate() const;
};
extern GameLogic *TheGameLogic;
extern int g_00DBA4E4; // LOGICFRAMES_PER_SECOND
#define LOGICFRAMES_PER_SECOND g_00DBA4E4
#define FLT_MAX 3.402823466e+38F
Real normalizeAngle(Real angle);
// The two .data tunables AIInternalMoveToState::update reads for AI state
// 0x47: a repath-delay scale (10) and a repath distance (200.0).
extern Int TheBfmeState47RepathDelayScale;
extern Real TheBfmeState47RepathDistance;
enum
{
	AI_BFME_STATE_47 = 0x47
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_31 = 0x31
};
enum ModelConditionFlagType
{
	MODELCONDITION_MOVING = 0x3D,
	MODELCONDITION_CLIMBING = 0x67,
	MODELCONDITION_RAPPELLING = 0x69
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
enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_PROJECTILE = 25
};
enum
{
	AI_ATTACK_OBJECT = 0x0A,
	AI_PICK_UP_CRATE = 0x27
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
class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	PathfindLayerEnum getLayer() const { return m_layer; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
	PathfindLayerEnum m_layer; // +0x18
};
class Path
{
public:
	PathNode *getLastNode() const { return m_pathTail; }
	Rva003642DFResult rva003642DF(float dist);
	// Zero Hour's appendNode with a BFME 2 third argument.
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int bfmeArg);
private:
	unsigned char m_pad00[0x08];
	PathNode *m_pathTail; // +0x08
};
class Pathfinder
{
public:
	bool IsBuildRestrictedCell(const Coord3D *pos, bool flagA, bool flagB, int layer);
	// (position, layer) as the rowed name's two ints.
	bool IsCliffCell(int pos, int layer);
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
class AICommandInterface
{
public:
	void rva00295A0F(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
};
class Rva00352F2FOpaque
{
public:
	void invoke(const Waypoint *way, int maxShots, CommandSourceType cmdSource);
};
class Rva001E46E1
{
public:
	Real rva001E46E1(Object *obj);
};
class AIUpdateInterface : public AIDeadStateAISlots<131>
{
public:
	virtual void setLocomotorGoalPositionOnPath() = 0; // slot 131
	virtual void slot132() = 0;
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void setLocomotorGoalOrientation(Real angle) = 0; // slot 135
	virtual void setLocomotorGoalNone() = 0; // slot 136
	virtual Bool isDoingGroundMovement() const = 0; // slot 137
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	Object *checkForCrateToPickup();
	Object *getNextMoodTarget(Bool calm, Bool alwaysAttack);
	Path *getPath() const { return m_path; }
	Bool canComputeQuickPath();
	Real getLocomotorDistanceToGoal();
	Int rva00260DED() const;
	Bool getRetryPath() const { return m_retryPath; }
	Int getNumFramesBlocked() const { return m_numFramesBlocked; }
	Real getPathExtraDistance() const { return m_pathExtraDistance; }
	void clearBfme160() { m_bfme160 = 0; }
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void aiAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
	{
		((AICommandInterface *)m_commandInterface)->rva00295A0F(pos, maxShotsToFire, cmdSource);
	}
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
	// Zero Hour's friend_startingMove and friend_endingMove.
	void rva00262ACE();
	void rva00262AEA();
	void friend_setLastCommandSource(CommandSourceType source) { m_lastCommandSource = source; }
private:
	unsigned char m_pad004[0x20 - 4];
	unsigned char m_commandInterface[0x28 - 0x20]; // +0x20
	UnsignedInt m_priorWaypointID; // +0x28
	UnsignedInt m_currentWaypointID; // +0x2C
	unsigned char m_pad030[0x48 - 0x30];
	CommandSourceType m_lastCommandSource; // +0x48
	unsigned char m_pad04C[0x140 - 0x4C];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x160 - 0x144];
	UnsignedInt m_bfme160; // +0x160
	unsigned char m_pad164[0x168 - 0x164];
	Real m_pathExtraDistance; // +0x168
	Int m_numFramesBlocked; // +0x16C
	unsigned char m_pad170[0x1CC - 0x170];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B1 - (0x1F0 + sizeof(Locomotor *))];
	Bool m_isWaitingForPath; // +0x3B1
	unsigned char m_pad3B2[0x3C0 - 0x3B2];
	Bool m_retryPath; // +0x3C0
	unsigned char m_pad3C1[0x3C7 - 0x3C1];
public:
	Bool m_flag3C7; // +0x3C7
};
class Rva0010CBits
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[19];
};
class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 0x1f)); }
private:
	unsigned char m_pad00[0x108];
	unsigned int m_kindOf[1]; // +0x108
};
class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};
class Thing
{
public:
	void rva0030A8EE(Coord3D *dir) const;
	void setOrientation(Real angle);
};
class Rva00373EC6
{
public:
	void rva0037446E(int a, int b, int c, int d);
	unsigned char m_pad00[0x3C];
	int m_bfme3C; // +0x3C
};
class Object
{
public:
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)m_geometryInfo; }
	Real rva0028AC7D() const;
	void getUnitDirectionVector3D(Coord3D &dir) const { ((const Thing *)this)->rva0030A8EE(&dir); }
	Real getOrientation() const { return m_orientation; }
	void setOrientation(Real angle) { ((Thing *)this)->setOrientation(angle); }
	Bool testStatus(ObjectStatusTypes bit) const;
	// Zero Hour's Pathfinder::removeGoal and getLayer for this object.
	void rva0028AD32();
	int rva0028B511() const;
	Rva00373EC6 *rva0028F4BC();
	__forceinline void clearModelConditionState(ModelConditionFlagType bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	// Zero Hour's Pathfinder::updateGoal for this object (goal, layer).
	void rva0028ACEE(int goalPos, int layer);
	float getBfmeRealB8() const { return m_bfmeRealB8; }
	const Coord3D *getPosition() const { return &m_position; }
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
	unsigned char m_pad048[0xA8 - 0x48];
	unsigned char m_geometryInfo[0xB8 - 0xA8]; // +0xA8
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
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void setGoalPosition(const Coord3D *pos);
	Bool isInIdleState() const;
private:
	State *m_currentState; // +0x4
	unsigned char m_pad08[0x14 - 8];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
public:
	Real m_goalAngle; // +0x30 (FLT_MAX when unset)
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
	virtual Bool computePath();
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
	void forceRepath()
	{
		m_pathGoalPosition.x = m_pathGoalPosition.y = m_pathGoalPosition.z = -100.0f;
		m_pathTimestamp = -LOGICFRAMES_PER_SECOND;
	}
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	Real m_goalAngle; // +0x2C
	Int m_goalLayer; // +0x30 (PathfindLayerEnum)
	Coord3D m_pathGoalPosition; // +0x34
	unsigned char m_pad40[0x44 - 0x40];
	UnsignedInt m_pathTimestamp; // +0x44
	Bool m_adjustsDestination; // +0x48
	Bool m_waitingForPath; // +0x49
	Bool m_tryOneMoreRepath; // +0x4A
	Bool m_turningToGoalAngle; // +0x4B
};
class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Bool m_isMoveTo; // +0x4C
};
void AIMoveToState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
}
class AIAttackMoveToState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	CommandSourceType m_commandSrc; // +0x50
	StateMachine *m_attackMoveMachine; // +0x54
	UnsignedInt m_frameToSleepUntil; // +0x58
	Int m_retryCount; // +0x5C
	Coord3D m_bfmeGoalPosition60; // +0x60
	ObjectID m_bfmeGoalObjectID6C; // +0x6C
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

StateReturnType AIAttackMoveToState::update()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();

	Bool forceRetargetThisFrame = false;
	Bool shouldRepathThisFrame = false;

	if (!m_attackMoveMachine->isInIdleState())
	{
		Object *goalObj = getMachine()->getGoalObject();
		if (goalObj && goalObj != m_attackMoveMachine->getGoalObject())
			m_attackMoveMachine->setGoalObject(goalObj);
		m_attackMoveMachine->updateStateMachine();

		if (m_attackMoveMachine == 0 || !m_attackMoveMachine->isInIdleState())
			return STATE_CONTINUE;
		forceRetargetThisFrame = true;
		shouldRepathThisFrame = true;
		ai->friend_setLastCommandSource(m_commandSrc);
	}

	if (m_attackMoveMachine->isInIdleState())
	{
		Object *crate = ai->checkForCrateToPickup();
		if (crate)
		{
			m_attackMoveMachine->setGoalObject(crate);
			m_attackMoveMachine->setState(AI_PICK_UP_CRATE);
			return STATE_CONTINUE;
		}

		Object *nextObjectToAttack = ai->getNextMoodTarget(!forceRetargetThisFrame, false);
		if (nextObjectToAttack != 0)
		{
			ai->rva00262AEA();
			m_attackMoveMachine->setGoalObject(nextObjectToAttack);
			m_attackMoveMachine->setState(AI_ATTACK_OBJECT);
			ai->friend_setLastCommandSource(CMD_FROM_AI);
			ai->m_flag3C7 = true;
			return STATE_CONTINUE;
		}
	}

	const Coord3D *machinePos = getMachine()->getGoalPosition();
	Coord3D machineGoal;
	machineGoal.x = machinePos->x;
	machineGoal.y = machinePos->y;
	machineGoal.z = machinePos->z;
	ObjectID goalID = m_bfmeGoalObjectID6C;
	Object *goalObj = TheGameLogic->findObjectByID(goalID);
	const Coord3D *goalPos;
	if (goalObj)
		goalPos = goalObj->getPosition();
	else if (goalID != INVALID_OBJECT_ID)
		return STATE_SUCCESS;
	else
		goalPos = &m_bfmeGoalPosition60;
	Coord3D delta = *goalPos;
	delta.x -= machineGoal.x;
	delta.y -= machineGoal.y;
	delta.z -= machineGoal.z;
	if (delta.GetLengthEstimate() > 5.0f)
	{
		if (goalObj)
			getMachine()->setGoalObject(goalObj);
		else
			getMachine()->setGoalPosition(&m_bfmeGoalPosition60);
		shouldRepathThisFrame = true;
	}

	if (m_frameToSleepUntil > TheGameLogic->getFrame())
		return STATE_CONTINUE;
	else if (m_frameToSleepUntil == TheGameLogic->getFrame())
		shouldRepathThisFrame = true;

	if (shouldRepathThisFrame)
	{
		AIMoveToState::onEnter();
		forceRepath();
	}

	StateReturnType ret = AIMoveToState::update();
	if (ret != STATE_CONTINUE)
	{
		if (m_retryCount < 1)
			return ret;
		Real dx = owner->getPosition()->x - m_pathGoalPosition.x;
		Real dy = owner->getPosition()->y - m_pathGoalPosition.y;
		Real distSqr = dx * dx + dy * dy;
		if (distSqr < 80.0f * 80.0f)
			return ret;

		ret = STATE_CONTINUE;
		m_retryCount--;
		m_frameToSleepUntil = TheGameLogic->getFrame() + 3 * LOGICFRAMES_PER_SECOND;
	}
	return ret;
}

StateReturnType AIMoveToState::update()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();

	UnsignedInt adjustment = ai->getMoodMatrixActionAdjustment(MM_Action_Move);
	if (m_isMoveTo && (adjustment & MAA_Action_To_AttackMove))
		ai->aiAttackMoveToPosition(&m_goalPosition, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);

	Object *goalObj = getMachine()->getGoalObject();
	Object *obj = getMachineOwner();
	if (goalObj)
	{
		m_goalPosition = *goalObj->getPosition();
		Bool isMissile = obj->isKindOf(KINDOF_PROJECTILE);
		if (isMissile)
		{
			Real halfHeight = getMachine()->getGoalObject()->getGeometryInfo().getMaxHeightAbovePosition() / 2.0f;
			m_goalPosition.z += halfHeight;
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta > 0)
				m_goalPosition.z += zDelta;
		}
		if (isMissile && !goalObj->isKindOf(KINDOF_IMMOBILE))
		{
			const Coord3D *objPos = obj->getPosition();
			Coord3D ourPos;
			ourPos.x = objPos->x;
			ourPos.y = objPos->y;
			ourPos.z = objPos->z;
			Coord3D delta;
			delta.x = m_goalPosition.x - ourPos.x;
			delta.y = m_goalPosition.y - ourPos.y;
			delta.z = m_goalPosition.z - ourPos.z;
			Real mySpeed = obj->rva0028AC7D();
			Real goalSpeed = goalObj->rva0028AC7D();
			if (mySpeed < 5.0f)
				mySpeed = 5.0f;
			Real leadDistance = (0.5 * delta.length()) * goalSpeed / mySpeed;
			Coord3D dir;
			goalObj->getUnitDirectionVector3D(dir);
			m_goalPosition.x += dir.x * leadDistance;
			m_goalPosition.y += dir.y * leadDistance;
			m_goalPosition.z += dir.z * leadDistance;
		}
	}
	else
	{
		if (obj->isKindOf(KINDOF_PROJECTILE))
		{
			m_goalPosition = *getMachine()->getGoalPosition();
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta > 0)
				m_goalPosition.z += zDelta;
		}
	}

	return AIInternalMoveToState::update();
}

// ?isSamePosition@@YA_NPBUCoord3D@@00@Z present-unmatched
// AIStates.cpp's static helper (rowed at 0x0033FA8E from the computePath
// unit); defined here too so VC7.1 gives the call its private register
// convention (current goal in eax, previous in ecx, position in edx).
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

StateReturnType AIInternalMoveToState::update()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	if (m_turningToGoalAngle)
	{
		Real angle = obj->getOrientation();
		Real goalAngle = m_goalAngle;
		if (normalizeAngle(goalAngle - angle) < 0.31415927f)
		{
			obj->setOrientation(m_goalAngle);
			return STATE_SUCCESS;
		}
		ai->setLocomotorGoalOrientation(m_goalAngle);
		return STATE_CONTINUE;
	}

	if (obj->testStatus(OBJECT_STATUS_BFME_31))
		return STATE_FAILURE;

	Path *thePath = ai->getPath();
	if (m_waitingForPath)
	{
		m_pathTimestamp = TheGameLogic->getFrame();
		if (ai->isWaitingForPath())
			return STATE_CONTINUE;
		if (thePath == 0)
			return STATE_FAILURE;
		m_waitingForPath = false;
		m_pathGoalPosition = m_goalPosition;
		if (getAdjustsDestination())
			obj->rva0028ACEE((int)thePath->getLastNode()->getPosition(), thePath->getLastNode()->getLayer());
		else
			obj->rva0028AD32();
		if (!ai->getRetryPath())
			m_tryOneMoreRepath = false;
	}

	Bool forceRecompute = false;
	if (thePath == 0)
		forceRecompute = true;

	if (ai->canComputeQuickPath())
	{
		if (obj->isKindOf(KINDOF_PROJECTILE))
		{
			m_pathTimestamp = 0;
			forceRecompute = true;
		}
	}

	if (thePath != 0)
		ai->setLocomotorGoalPositionOnPath();

	Real onPathDistToGoal = ai->getLocomotorDistanceToGoal();
	Locomotor *curLoco = ai->getCurLocomotor();
	if (curLoco && !(onPathDistToGoal >= curLoco->getCloseEnoughDist()))
	{
		obj->clearModelConditionState(MODELCONDITION_MOVING);
	}
	else
	{
		ModelConditionFlagType setConditionFlag = MODELCONDITION_MOVING;
		Pathfinder *pathfinder = TheAI->pathfinder();
		if (pathfinder->IsCliffCell((int)obj->getPosition(), obj->rva0028B511()))
		{
			if (ai->getCurLocomotor() && ai->getCurLocomotor()->isMovingBackwards())
			{
				setConditionFlag = MODELCONDITION_RAPPELLING;
				obj->clearModelConditionState(MODELCONDITION_CLIMBING);
			}
			else
			{
				setConditionFlag = MODELCONDITION_CLIMBING;
				obj->clearModelConditionState(MODELCONDITION_RAPPELLING);
			}
		}
		if (ai->getNumFramesBlocked() <= 0)
		{
			if (setConditionFlag == MODELCONDITION_MOVING)
			{
				Locomotor *loco = obj->getAI()->getCurLocomotor();
				if (loco && !loco->getTemplate()->m_bfmeFlag150)
				{
					obj->clearModelConditionState(MODELCONDITION_CLIMBING);
					obj->clearModelConditionState(MODELCONDITION_RAPPELLING);
				}
			}
			if (curLoco && ((Rva001E46E1 *)curLoco)->rva001E46E1(obj) == 0.0f)
				obj->clearModelConditionState(MODELCONDITION_MOVING);
			else
				obj->setModelConditionState(MODELCONDITION_MOVING);
			if (setConditionFlag != MODELCONDITION_MOVING)
			{
				obj->setModelConditionState(setConditionFlag);
				Rva00373EC6 *module = obj->rva0028F4BC();
				if (module && module->m_bfme3C)
					module->rva0037446E(0, 1, 0, 1);
			}
		}
	}

	Bool isState47 = obj->getAI()->rva00260DED() == AI_BFME_STATE_47;
	Int repathFrames = LOGICFRAMES_PER_SECOND;
	if (isState47)
		repathFrames *= TheBfmeState47RepathDelayScale;
	if (forceRecompute || TheGameLogic->getFrame() - m_pathTimestamp > (UnsignedInt)repathFrames)
	{
		if (forceRecompute || !isSamePosition(obj->getPosition(), &m_pathGoalPosition, &m_goalPosition))
		{
			Coord3D delta;
			delta.x = obj->getPosition()->x;
			delta.y = obj->getPosition()->y;
			delta.z = obj->getPosition()->z;
			delta.x -= m_goalPosition.x;
			delta.y -= m_goalPosition.y;
			delta.z -= m_goalPosition.z;
			Real dist = delta.length();
			if (!isState47 || dist > TheBfmeState47RepathDistance)
			{
				critterDesyncLog("CritterDesync: ComputePath2");
				if (!computePath())
					return STATE_FAILURE;
				if (ai->getPath() == 0)
					return STATE_CONTINUE;
				ai->setLocomotorGoalPositionOnPath();
			}
		}
	}

	onPathDistToGoal = ai->getLocomotorDistanceToGoal();
	Locomotor *loco = ai->getCurLocomotor();
	Bool closeEnough = false;
	if (loco != 0)
	{
		if (onPathDistToGoal < loco->getCloseEnoughDist())
			closeEnough = true;
		Real extraDistance = ai->getPathExtraDistance();
		if (loco->getPreferredHeight() < extraDistance)
		{
			Real preferredHeight = loco->getPreferredHeight();
			if (preferredHeight + preferredHeight > onPathDistToGoal)
				closeEnough = true;
		}
	}
	if (closeEnough)
	{
		if (ai->isDoingGroundMovement())
		{
			Coord3D goalPos;
			goalPos.x = m_goalPosition.x;
			goalPos.y = m_goalPosition.y;
			if (ai->getPath()->getLastNode())
				goalPos = *ai->getPath()->getLastNode()->getPosition();
			Coord3D delta;
			delta.x = obj->getPosition()->x - goalPos.x;
			delta.y = obj->getPosition()->y - goalPos.y;
			delta.z = 0;
			if (delta.length() > 40.0f)
				return STATE_CONTINUE;
		}
		if (getAdjustsDestination())
			ai->setLocomotorGoalNone();
		ai->clearBfme160();
		if (getMachine()->m_goalAngle != FLT_MAX)
		{
			m_goalAngle = getMachine()->m_goalAngle;
			m_turningToGoalAngle = true;
			ai->setLocomotorGoalOrientation(m_goalAngle);
			return STATE_CONTINUE;
		}
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
