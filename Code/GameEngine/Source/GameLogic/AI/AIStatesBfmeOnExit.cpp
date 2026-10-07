// cl: /DNDEBUG /MD
//
// onEnter/onExit/update overrides of BFME 2 states, each named by its
// vtable's slot-2 name getter (the state's own name literal):
//
//  - AIFollowPathAsTeamState::onExit, retail 0x00349E15 (95 bytes): slot 5
//    of 0x00C121E8. Sets the team machine at +0x5C (when present) to state 0
//    through StateMachine slot 8, then Zero Hour's AIFollowPathState::onExit
//    tail on the AIInternalMoveToState base (0x003473A4): path-through-units
//    off, precise-z off, the pinned AIUpdateInterface::setDesiredSpeed with
//    999999.0 (FAST_AS_POSSIBLE, .rdata 0x00C10DE0) and goal path index -1.
//  - AIChargeTargetState::onExit, retail 0x0034BEC3 (93 bytes): slot 5 of
//    0x00C130A8. With an owner and its AI: clears model-condition bit 132
//    (word +0x11C of the bits at +0x10C, notifying through the rowed
//    Object::rva0028AE6D), calls AI slot 142 with 0, releases the weapon
//    lock (pinned Object::releaseWeaponLock, LOCKED_TEMPORARILY), clears the
//    machine byte +0x3A and runs the base onExit.
//  - AIChargeTargetState::update, retail 0x0034FE6E (336 bytes): slot 6 of
//    0x00C130A8, BFME 1's AIChargeTargetState_update.cpp with BFME 2
//    offsets. Kind 0x84 (the pinned isKindOf) replaces the donor's
//    condition tests and Object::rva0028AD32 its pathfinder removeGoal;
//    a hit sets condition bit 132 (the bit onExit clears). The other
//    helpers it calls with this in ECX are pinned by address.
//  - AIChargeTargetState::rva0034BF20, retail 0x0034BF20 (223 bytes): the
//    donor's rva0016FD30. True when the goal is within the current
//    weapon's range (template getter 0x0049CB57) and the relative angle to
//    it is under the template's +0x2C aim delta, floored at 0.035 (.rdata
//    0x00C13B5C).
//  - AIChargeTargetState::rva00346925, retail 0x00346925 (208 bytes): the
//    donor's rva0016F4F0 (BFME 1 kept it a dump). Paths to a point 50.0
//    past the victim along the source-to-victim direction (rowed
//    Coord3D::Normalize, result unused), after clearing the machine's goal
//    object (slot 14) and Object::rva0028AD32. The ZH Coord3D scale/add
//    inlines give retail's batched multiplies.
//  - AIAttackMeleeHordeApproachTargetState::onExit, retail 0x0034921C (161
//    bytes): slot 5 of 0x00C126C0, whose slot-2 getter names the class.
//    Donor: Open-BFME-1 AIAttackMeleeHordeApproachTargetState_onExit.cpp.
//    Clears the +0x5D initial-approach flag after the base onExit; unless
//    the owner's +0x94 flag is set, clears status 0x4B, restores full speed,
//    drops the ignored obstacle and, for ground movement (AI slot 137),
//    snaps the owner onto the +0x20 goal position when within sqrt(12.5).
//  - AIMoveToPositionAndEnterState::onEnter, retail 0x00350020 (198
//    bytes): slot 4 of 0x00C136A0. Donor: Open-BFME-1
//    AIMoveToPositionAndEnterState_onEnter.cpp. Takes the goal's contain
//    slot-87 enter position as the +0x20 goal; BFME 2 adds the pinned
//    Pathfinder::adjustDestination for goal templates with kind byte +0x11F
//    mask 0x80. After the base onEnter, an owner with a +0x410 group pointer
//    moves at its AIGroup's speed (rowed AIUpdateInterface::rva002630F5).
//  - AIMoveToPositionAndEnterState::update, retail 0x00354945 (369
//    bytes): slot 6 of 0x00C136A0; the base call is the pinned
//    AIMoveToState::update 0x00353A65, so the class derives from
//    AIMoveToState. Donor: Open-BFME-1 AIStates.cpp (canEnterObject
//    refusal, then aiEnter on success, rowed here as
//    AICommandInterface::rva0026C347). BFME 2 additions: a goal controlled
//    by another player that holds occupants (contain slot 69) and lies
//    within 200 of an owner with status 0x5D gets contain slot 32 with the
//    owner's command source, and keeps the state running; a goal whose
//    template has kind byte +0x11F bit 0x80 continues in AI states
//    0x46/0x47 and otherwise fails unless it is in state 0 and the pinned
//    Pathfinder::getClosestPointOnLand finds land.
//  - AIEnterState::update, retail 0x0035455A (419 bytes): slot 6 of
//    0x00C12E90, base call the pinned AIInternalMoveToState::update. Donors:
//    Open-BFME-1 AIStates.cpp and Zero Hour AIStates.cpp. Fails without a
//    goal or when an airborne-contained goal is out of reach. It tracks the
//    goal's contain slot-86 position (else the goal position), sets the AI
//    goal object and, when canEnterObject refuses, attacks an enemy goal
//    (rowed AICommandInterface::rva0026C2D9) or fails. A held owner
//    succeeds. After a finished move it forces the unit into the contain
//    (slot 39, Zero Hour addToContain) when within the goal's +0xB8
//    radius or past the +0x50 frame.
//  - AIEnterAndAttackState::update, retail 0x003546FD (385 bytes): slot 6
//    of 0x00C12F40 (slot-2 name getter AIEnterAndAttackState). Donor:
//    Open-BFME-1 AIStates.cpp AIEnterAndAttackState::update. Same callees
//    as AIEnterState::update, but it always tracks the goal position; after
//    a successful move it continues while an airborne goal is above a
//    grounded owner, else forces the unit into the contain (slot 39) when
//    within the goal's +0xB8 radius.
//  - AIEnterAndAttackState::onEnter, retail 0x0034FD0D (259 bytes): slot 4
//    of 0x00C12F40. Shape of the BFME 1 / Zero Hour AIEnterState::onEnter:
//    clears +0x4C, records the owner AI's pinned getCurrentVictim id at
//    +0x50 (the rowed xfer saves both ObjectIDs), fails without a goal or
//    when canEnterObject refuses, announces the unit to the goal's contain
//    (slot 17, Zero Hour onObjectWantsToEnterOrExit) and records the goal
//    id, then ignores the goal as an obstacle, allows invalid locomotor
//    positions and logs critter desync 59 before the base onEnter.
//  - AIMoveToPositionAndDieState::update, retail 0x003513C9 (214 bytes):
//    slot 6 of 0x00C12CE8. Zero Hour AIMoveAndDeleteState::update: fails
//    for an effectively dead owner (+0x438 bit 0), allows invalid locomotor
//    positions and appends the ground-snapped goal once (+0x4C) to an
//    existing path when not waiting for one (AI +0x3B1), through the rowed
//    Path append with BFME 2's extra 0x7fffffff. When the move ends, BFME 2
//    kills the owner (rowed Object::kill(8, 0)) instead of destroying it,
//    first reporting it to the last damage source (pinned 0x00294D61).
//  - AIMoveToPositionAndEnterState::onExit, retail 0x0034C035 (99 bytes):
//    slot 5 of 0x00C136A0. When the owner has object status 0x4E, clears it
//    and status 3, and for a template with kind byte +0x115 mask 0x20 also
//    clears status 3 through the pinned Object::rva00346C53; then clears
//    status 0x5D and runs the base onExit.
//  - AIAttackMeleeEngageState::onExit, retail 0x00349D26 (103 bytes): slot 5
//    of 0x00C12150. Nothing for an owner with byte +0x94 bit 0; otherwise
//    full speed (setDesiredSpeed FAST_AS_POSSIBLE), clears status 0x4B
//    through rva00346C53 and setStatus unless status 0x26 is set, then the
//    base onExit.
//  - AIAttackPositionAimAtTargetState::onExit, retail 0x0034A809 (104
//    bytes): slot 5 of 0x00C11068. AI slot 136 when both flags +0x20/+0x21
//    are set; AI slot 142 with 0 when the template real +0x53C is below
//    360.0 (.rdata 0x00BC6254); clears status 0x19. No base call.
//  - AIMoveAwayAndCowerState::onEnter, retail 0x0034CBAB (85 bytes): slot 4
//    of 0x00C12FF0. Fails (-2) without a goal object (the pinned
//    StateMachine::getGoalObject) or AI; else AI slot 142 with 4, +0x4C = 1,
//    +0x50 = true, the pinned AI member 0x00263EA2 with the goal's id (+0x74)
//    and the pinned AIInternalMoveToState::onEnter as a tail call.
//  - AIFaceDirectionState::update, retail 0x003425BF (90 bytes): slot 6 of
//    0x00C12378. Within PI/10 (.rdata 0x00C123D4) of the +0x20 angle
//    (rowed normalizeAngle of the difference to the owner's orientation
//    +0x44) it sets the orientation (rowed Thing::setOrientation) and
//    succeeds; otherwise it turns through AI slot 135
//    (setLocomotorGoalOrientation) and continues.
//  - AIPrepareForBoarding::onEnter, retail 0x0034263C (111 bytes): slot 4 of
//    0x00C123D8. Asks the pathfinder (TheAI +0x10, pinned 0x002EE7EE) for a
//    destination from the owner's position, takes and clears the machine
//    goal object (slot 14); fails when a destination was found but the goal
//    is missing or the pinned path test 0x002F477E from the goal accepts it,
//    else succeeds.
//  - AIPrepareForBoarding::update, retail 0x00354C6B (66 bytes): slot 6 of
//    0x00C123D8 (a start missing from the Ghidra inventory). When the same
//    pathfinder query finds a destination, idles the AI from CMD_FROM_AI
//    (rowed AICommandInterface::aiIdle on the AI's +0x20 command interface)
//    and fails; otherwise succeeds.
//  - AIMoveAndTightenState::update, retail 0x00347AE8 (85 bytes): slot 6 of
//    0x00C124D8. While +0x50 is set and the AI has a path (+0x140) and its
//    +0x3B1 is clear: CritterDesync log line, setAdjustsDestination(true)
//    (+0x48), +0x50 cleared; then the pinned AIInternalMoveToState::update.
//  - AICombineState::onEnter, retail 0x0034FCAC (97 bytes): slot 4 of
//    0x00C12EE8. Returns the pinned state helper 0x0034612C's result when
//    nonzero; else slot 24 of the rowed Object::rva0028C197 interface when
//    its bool slot 136 holds, a CritterDesync log line,
//    setAdjustsDestination(false) and the base onEnter.
//  - AIRotateFiringarc::update, retail 0x0034274A (95 bytes): slot 6 of
//    0x00C12438. Fails without an AI; copies the owner's orientation to its
//    +0x1C0 real and succeeds once it is within 0.01 (.rdata 0x00BCF628) of
//    the machine goal position's x (the rowed normalizeAngle, CRT fabs).
//  - AIBusyState::onEnter, retail 0x00346017 (76 bytes): slot 4 of
//    0x00C10E48. Fails when the AI's mood-matrix adjustment for action 2
//    (pinned 0x00264FF8) has bit 0, there is a goal object and the owner
//    cannot pick a weapon for it (pinned Object::chooseBestWeaponForTarget
//    with criteria 5 and the AI's slot-143 last command source); else
//    succeeds.
//
// Layout and callees as in AIFollowPathStateOnExit.cpp and
// AIStatesDerivedOnExit.cpp; the meaning of the status, condition and kind
// bits is not recovered.

typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
typedef unsigned int StateID;
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3 = 3,
	OBJECT_STATUS_BFME_19 = 0x19,
	OBJECT_STATUS_BFME_26 = 0x26,
	OBJECT_STATUS_BFME_4B = 0x4B,
	OBJECT_STATUS_BFME_4E = 0x4E,
	OBJECT_STATUS_BFME_5D = 0x5D
};
#include "../../Common/GameLogicObjectLookupView.h"
enum
{
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
struct Coord3D;
class Object;

class LocomotorSet;
class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest,
		const Coord3D *groupDest);
	Bool getClosestPointOnLand(const Coord3D *pos, Object *obj, Coord3D *dest);
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int flag);
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

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum MoodMatrixAction
{
	MM_ACTION_BFME_2 = 2
};
enum WeaponChoiceCriteria
{
	WEAPON_CHOICE_BFME_5 = 5
};

enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	READY_TO_FIRE = 0
};
enum KindOfType
{
	KINDOF_BFME_84 = 0x84
};

class WeaponTemplate
{
public:
	Real rva0049CB57() const;
	Real getAimDelta() const { return m_aimDelta; }
private:
	unsigned char m_pad00[0x2C];
	Real m_aimDelta; // +0x2C
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	WeaponStatus computeStatus(Bool *valid) const;
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};
#define FAST_AS_POSSIBLE 999999.0f

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
	void setAllowInvalidPosition(Bool b)
	{
		if (b)
			m_flags |= (1 << ALLOW_INVALID_POSITION);
		else
			m_flags &= ~(1 << ALLOW_INVALID_POSITION);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};

template <int N> class AIStateAISlots : public AIStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIStateAISlots<0>
{
};
template <class Base, int N> class AIStateGapSlots : public AIStateGapSlots<Base, N - 1>
{
public:
	virtual void tailGap(char (*)[N]) = 0;
};
template <class Base> class AIStateGapSlots<Base, 0> : public Base
{
};
// Pure gap slots From+1..To after Base's last slot From; numbering the
// signature by slot keeps successive fills distinct.
template <class Base, int From, int To> class AIStateSlotFill : public AIStateSlotFill<Base, From, To - 1>
{
public:
	virtual void fill(char (*)[To]) = 0;
};
template <class Base, int From> class AIStateSlotFill<Base, From, From> : public Base
{
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};
class Path
{
public:
	// Rowed tail append; BFME 2 adds a trailing int to Zero Hour's appendNode.
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int bfmeLimit);
};
class TerrainLogic : public AIStateAISlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
};
extern TerrainLogic *TheTerrainLogic;
struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
};
class BodyModuleInterface : public AIStateAISlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};
enum DamageType
{
	DAMAGE_BFME_8 = 8
};
enum DeathType
{
	DEATH_NORMAL = 0
};

// The interface Object::rva0028C197 returns (opaque): slot 24 and the bool
// slot 136 are the two AICombineState::onEnter calls.
class Rva0028C197ResultHead : public AIStateAISlots<24>
{
public:
	virtual void rva0034FCDCSlot24() = 0;
};
class Rva0028C197Result : public AIStateGapSlots<Rva0028C197ResultHead, 111>
{
public:
	virtual Bool rva0034FCCESlot136() = 0;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void rva0026C347(Object *obj, CommandSourceType cmdSource);
	void rva0026C2D9(Object *victim, int maxShotsToFire, CommandSourceType cmdSource);
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CanAttackResult
{
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

enum Relationship
{
	ENEMIES = 0
};

class ActionManager
{
public:
	CanAttackResult getCanAttackObject(const Object *obj, const Object *objectToAttack,
		CommandSourceType commandSource, AbleToAttackType attackType);
};

class BFMEActionManager : public ActionManager
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource,
		CanEnterType mode, int passThrough, Bool *outFlag);
};
extern BFMEActionManager *TheActionManager;
extern GameLogic *TheGameLogic;

class RadarObject;
class Player;
class AIGroup
{
public:
	Real getSpeed();
};

class AIUpdateInterface : public AIStateAISlots<135>
{
public:
	virtual void setLocomotorGoalOrientation(Real angle) = 0;
	virtual void rva0034A82DSlot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void rva0034BEF9Slot142(int value) = 0;
	virtual CommandSourceType getLastCommandSource() const = 0;
	void rva00263EA2(ObjectID id);
	void ignoreObstacle(const Object *obj);
	Object *getCurrentVictim() const;
	unsigned int getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void friend_setCurrentGoalPathIndex(int index) { m_currentGoalPathIndex = index; }
	void setDesiredSpeed(Real speed);
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	RadarObject *rva002630F5();
	int rva00260DED() const;
	void friend_setGoalObject(Object *obj);
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_locomotorSet; }
	Path *getPath() const { return m_path; }
	Bool getBfmeFlag3B1() const { return m_bfmeFlag3B1; }
private:
	unsigned char m_pad004[0x20 - 0x04];
public:
	AICommandInterface m_commands; // +0x20 (rowed aiIdle's this)
private:
	unsigned char m_pad021[0x140 - 0x21];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x194 - 0x144];
	int m_currentGoalPathIndex; // +0x194
	unsigned char m_pad198[0x1CC - 0x198];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B1 - 0x1F4];
	Bool m_bfmeFlag3B1; // +0x3B1
	unsigned char m_pad3B2[0x3BA - 0x3B2];
	Bool m_canPathThroughUnits; // +0x3BA
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class ThingTemplate
{
public:
	Bool testKindByte115() const { return (m_kindOf[1] & 0x20) != 0; }
	Bool testKindByte11F() const { return (m_kindOf[11] & 0x80) != 0; }
	Real getBfmeReal53C() const { return m_bfmeReal53C; }
private:
	unsigned char m_pad00[0x114];
	unsigned char m_kindOf[12]; // +0x114
	unsigned char m_pad120[0x53C - 0x120];
	Real m_bfmeReal53C; // +0x53C
};

Real normalizeAngle(Real angle);
extern "C" float __cdecl fabs(double); // CRT fabs; x87 result compared as float (as in AIFaceStateUpdate.cpp)

struct Coord3D
{
	Real x, y, z;
	Real Normalize();
	void scale(Real scale) { x *= scale; y *= scale; z *= scale; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	Real length() const;
};

// The contain module's slot 87 hands back the position an entering unit
// walks to (BFME 1 donor: slot 82, its GetContainedObjectPosition typedef);
// slot 86 is the donor's slot-81 getContainedObjectPosition, which
// AIEnterState reads (the same +5 shift). Slot 69
// is the contain count with one zero argument (as in
// ScriptConditions_evaluateIsBuildingEmpty.cpp); slot 32 takes a command
// source and has no evidenced name; slot 39 is the Zero Hour addToContain
// that AIEnterState::update forces an arrived unit into; slot 17 is the Zero
// Hour onObjectWantsToEnterOrExit that AIEnterAndAttackState::onEnter
// announces the entering unit with.
enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0
};
class ContainModuleSlot17 : public AIStateAISlots<17>
{
public:
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants) = 0;
};
class ContainModuleSlot32 : public AIStateSlotFill<ContainModuleSlot17, 17, 31>
{
public:
	virtual void slot32(CommandSourceType cmdSource) = 0;
};
class ContainModuleSlot39 : public AIStateSlotFill<ContainModuleSlot32, 32, 38>
{
public:
	virtual void addToContain(Object *obj) = 0;
};
class ContainModuleSlot69 : public AIStateSlotFill<ContainModuleSlot39, 39, 68>
{
public:
	virtual int getContainCount(int extra) const = 0;
};
class ContainModuleInterface : public AIStateSlotFill<ContainModuleSlot69, 69, 85>
{
public:
	virtual const Coord3D *getContainedObjectPosition() const = 0;
	virtual const Coord3D *getEnterPosition() = 0;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	void setOrientation(Real angle);
	void setPosition(const Coord3D *pos);
	Bool isAboveTerrain() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }
	void *getBfme410() const { return m_bfme410; }
	Bool testBfmeFlag94() const { return (m_bfmeFlags94 & 1) != 0; }
	void setBfmeAngle1C0(Real angle) { m_bfmeAngle1C0 = angle; }
	Bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	Bool isDisabledHeld() const { return (m_disabledMask & 8) != 0; }
	Object *getContainedBy() const { return m_containedBy; }
	void setStatus(ObjectStatusTypes status, Bool set);
	void rva00346C53(ObjectStatusTypes status, Bool set);
	void releaseWeaponLock(WeaponLockType lockType);
	Bool isKindOf(KindOfType t) const;
	Real GetRelativeAngle(const Coord3D *pos) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void rva0028AD32();
	void rva0028AE6D();
	void *rva0028C197() const;
	Bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	void kill(DamageType damageType, DeathType deathType);
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x94 - 0x78];
	unsigned char m_bfmeFlags94; // +0x94
	unsigned char m_pad095[0xB8 - 0x95];
	Real m_boundingCircleRadius; // +0xB8 (geometry info)
	unsigned char m_pad0BC[0x10C - 0xBC];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x1C0 - (0x10C + sizeof(Rva0010CBits))];
	Real m_bfmeAngle1C0; // +0x1C0
	unsigned char m_pad1C4[0x1C8 - 0x1C4];
	unsigned char m_disabledMask; // +0x1C8 (bit 3: DISABLED_HELD)
	unsigned char m_pad1C9[0x250 - 0x1C9];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x410 - 0x278];
	void *m_bfme410; // +0x410
	unsigned char m_pad414[0x438 - 0x414];
	unsigned char m_privateStatus; // +0x438 (bit 0: effectively dead)
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void rva0034BF11ClearByte3A() { m_bfmeFlag3A = false; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
	unsigned char m_pad30[0x3A - 0x30];
	Bool m_bfmeFlag3A; // +0x3A
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
	StateReturnType rva0034612C();
protected:
	void setAdjustsDestination(Bool b) { m_adjustDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad4C[0x5C - 0x4C];
	StateMachine *m_teamMachine; // +0x5C
};

void AIFollowPathAsTeamState::onExit(StateExitType status)
{
	if (m_teamMachine)
		m_teamMachine->setState(0);

	AIInternalMoveToState::onExit(status);

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai)
		return;
	ai->setCanPathThroughUnits(false);
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);
	ai->setDesiredSpeed(FAST_AS_POSSIBLE);
	ai->friend_setCurrentGoalPathIndex(-1);
}

class AIChargeTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	Bool rva003468F5();
	Bool rva0034BF20();
	void rva00346925(Object *source, Object *victim, AIUpdateInterface *ai);
	void rva0034BFFF(Object *source);
	Bool m_bfmeFlag4C; // +0x4C
	int m_bfmeValue50; // +0x50
};

void AIChargeTargetState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return;
	owner->clearModelConditionBit(132);
	ai->rva0034BEF9Slot142(0);
	owner->releaseWeaponLock(LOCKED_TEMPORARILY);
	getMachine()->rva0034BF11ClearByte3A();
	AIInternalMoveToState::onExit(status);
}

StateReturnType AIChargeTargetState::update()
{
	Object *source = getMachineOwner();
	Object *victim = getMachine()->getGoalObject();
	AIUpdateInterface *ai = source->getAI();
	if (ai && (victim || source->isKindOf(KINDOF_BFME_84)) && m_bfmeValue50 > 0)
	{
		if (victim && rva003468F5() && !source->isKindOf(KINDOF_BFME_84))
		{
			source->rva0028AD32();
			Coord3D goalPosition;
			goalPosition.x = victim->getPosition()->x;
			goalPosition.y = victim->getPosition()->y;
			goalPosition.z = victim->getPosition()->z;
			m_goalPosition = goalPosition;
			setAdjustsDestination(false);
			ai->requestPath(&goalPosition, true);
		}
		WeaponSlotType slot = PRIMARY_WEAPON;
		const Weapon *weapon = source->getCurrentWeapon(&slot);
		if (weapon)
		{
			if (victim && rva0034BF20() && !source->isKindOf(KINDOF_BFME_84)
				&& weapon->computeStatus(0) == READY_TO_FIRE)
			{
				rva00346925(source, victim, ai);
				source->setModelConditionBit(132);
				ai->rva0034BEF9Slot142(4);
				rva0034BFFF(source);
			}
			if (m_bfmeFlag4C)
				return (StateReturnType)STATE_SUCCESS;
			return AIInternalMoveToState::update();
		}
	}
	return (StateReturnType)STATE_FAILURE;
}

Bool AIChargeTargetState::rva0034BF20()
{
	Object *source = getMachineOwner();
	Object *victim = getMachine()->getGoalObject();
	if (!source || !victim)
		return false;

	const Weapon *weapon = source->getCurrentWeapon(0);
	if (!weapon)
		return false;

	const Coord3D *victimPosition = victim->getPosition();
	Coord3D delta;
	delta.x = source->getPosition()->x;
	delta.y = source->getPosition()->y;
	delta.z = source->getPosition()->z;
	delta.x -= victimPosition->x;
	delta.y -= victimPosition->y;
	delta.z -= victimPosition->z;
	Real range = weapon->getTemplate()->rva0049CB57();
	if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z < range * range)
	{
		Real angleThreshold = weapon->getTemplate()->getAimDelta();
		if (angleThreshold < 0.035f)
			angleThreshold = 0.035f;
		if (source->GetRelativeAngle(victimPosition) < angleThreshold)
			return true;
	}
	return false;
}

void AIChargeTargetState::rva00346925(Object *source, Object *victim, AIUpdateInterface *ai)
{
	if (!victim)
		return;
	Coord3D dir;
	dir.x = victim->getPosition()->x;
	dir.y = victim->getPosition()->y;
	dir.z = victim->getPosition()->z;
	dir.x -= source->getPosition()->x;
	dir.y -= source->getPosition()->y;
	dir.z -= source->getPosition()->z;
	dir.Normalize();
	dir.scale(50.0f);
	dir.add(victim->getPosition());
	getMachine()->setGoalObject(0);
	source->rva0028AD32();
	setAdjustsDestination(false);
	m_goalPosition = dir;
	ai->requestPath(&dir, true);
}

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	Real m_bfmeReal4C; // +0x4C
	Real m_bfmeReal50; // +0x50
	Real m_bfmeReal54; // +0x54
	int m_bfmeFrame58; // +0x58
	Bool m_successOnPathFailure; // +0x5C
	Bool m_isInitialApproach; // +0x5D
};

void AIAttackMeleeHordeApproachTargetState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	m_isInitialApproach = false;
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (owner->testBfmeFlag94())
		return;

	owner->rva00346C53(OBJECT_STATUS_BFME_4B, false);
	if (ai)
	{
		ai->setDesiredSpeed(FAST_AS_POSSIBLE);
		ai->ignoreObstacle(0);
		if (ai->isDoingGroundMovement())
		{
			Real dx = m_goalPosition.x - owner->getPosition()->x;
			Real dy = m_goalPosition.y - owner->getPosition()->y;
			if (dx * dx + dy * dy < 12.5f)
				owner->setPosition(&m_goalPosition);
		}
	}
}

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

class AIMoveToPositionAndEnterState : public AIMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

StateReturnType AIMoveToPositionAndEnterState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 61");
	setAdjustsDestination(false);
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	Object *goal = getMachine()->getGoalObject();
	m_goalPosition = *goal->getContain()->getEnterPosition();
	if (goal->getTemplate()->testKindByte11F())
		TheAI->pathfinder()->adjustDestination(owner, ai->getLocomotorSet(), &m_goalPosition, 0);

	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (owner->getBfme410())
	{
		AIGroup *group = (AIGroup *)ai->rva002630F5();
		if (group)
			ai->setDesiredSpeed(group->getSpeed());
	}
	return ret;
}

StateReturnType AIMoveToPositionAndEnterState::update()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (owner->getAI() && !TheActionManager->canEnterObject(owner, goal,
			owner->getAI()->getLastCommandSource(), CHECK_CAPACITY, 1, 0))
		return (StateReturnType)STATE_FAILURE;

	AIUpdateInterface *ai = owner->getAI();
	int count = goal->getContain()->getContainCount(0);
	Bool otherPlayer = goal->getControllingPlayer() != owner->getControllingPlayer();
	if (otherPlayer && owner->testStatus(OBJECT_STATUS_BFME_5D) && count > 0)
	{
		Coord3D delta;
		delta.x = goal->getPosition()->x;
		delta.y = goal->getPosition()->y;
		delta.z = goal->getPosition()->z;
		delta.x -= owner->getPosition()->x;
		delta.y -= owner->getPosition()->y;
		delta.z -= owner->getPosition()->z;
		if (delta.length() < 200.0f)
			goal->getContain()->slot32(ai->getLastCommandSource());
	}

	StateReturnType ret = AIMoveToState::update();
	if (goal->getTemplate()->testKindByte11F())
	{
		int state = goal->getAI()->rva00260DED();
		if (state == 0x46 || state == 0x47)
			return STATE_CONTINUE;
		Coord3D landPos;
		Bool onLand = TheAI->pathfinder()->getClosestPointOnLand(goal->getPosition(), goal, &landPos);
		if (state != 0 || !onLand)
			return (StateReturnType)STATE_FAILURE;
	}
	if (otherPlayer && count > 0)
		return STATE_CONTINUE;
	if (ret == STATE_SUCCESS)
		ai->m_commands.rva0026C347(goal, ai->getLastCommandSource());
	return ret;
}

void AIMoveToPositionAndEnterState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (owner && owner->testStatus(OBJECT_STATUS_BFME_4E))
	{
		owner->setStatus(OBJECT_STATUS_BFME_4E, false);
		owner->setStatus(OBJECT_STATUS_BFME_3, false);
		if (owner->getTemplate()->testKindByte115())
			owner->rva00346C53(OBJECT_STATUS_BFME_3, false);
	}
	owner->setStatus(OBJECT_STATUS_BFME_5D, false);
	AIInternalMoveToState::onExit(status);
}

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeEngageState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (owner->testBfmeFlag94())
		return;
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
		ai->setDesiredSpeed(FAST_AS_POSSIBLE);
	if (!owner->testStatus(OBJECT_STATUS_BFME_26))
	{
		getMachineOwner()->rva00346C53(OBJECT_STATUS_BFME_4B, false);
		getMachineOwner()->setStatus(OBJECT_STATUS_BFME_4B, false);
	}
	AIInternalMoveToState::onExit(status);
}

class AIAttackPositionAimAtTargetState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_bfmeFlag20; // +0x20
	Bool m_bfmeFlag21; // +0x21
};

void AIAttackPositionAimAtTargetState::onExit(StateExitType status)
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (m_bfmeFlag20 && ai && m_bfmeFlag21)
		ai->rva0034A82DSlot136();
	if (ai && getMachineOwner()->getTemplate()->getBfmeReal53C() < 360.0f)
		ai->rva0034BEF9Slot142(0);
	getMachineOwner()->setStatus(OBJECT_STATUS_BFME_19, false);
}

class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	int m_entryToClear; // +0x4C
	unsigned int m_enterFrame; // +0x50
};

StateReturnType AIEnterState::update()
{
	Object *obj = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (goal)
	{
		if (goal->getContainedBy() != 0 && goal->isAboveTerrain() && !obj->isAboveTerrain())
			return (StateReturnType)STATE_FAILURE;

		ContainModuleInterface *contain = goal->getContain();
		if (contain)
			m_goalPosition = *contain->getContainedObjectPosition();
		else
			m_goalPosition = *goal->getPosition();

		obj->getAI()->friend_setGoalObject(goal);
		if (!TheActionManager->canEnterObject(obj, goal, obj->getAI()->getLastCommandSource(),
				CHECK_CAPACITY, 0, 0))
		{
			if (obj->getRelationship(goal) == ENEMIES && obj->getAI())
			{
				CanAttackResult result = TheActionManager->getCanAttackObject(obj, goal,
					obj->getAI()->getLastCommandSource(), ATTACK_NEW_TARGET);
				if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
				{
					AIUpdateInterface *ai = obj->getAI();
					ai->m_commands.rva0026C2D9(goal, 0x7fffffff, ai->getLastCommandSource());
					return STATE_CONTINUE;
				}
			}
			return (StateReturnType)STATE_FAILURE;
		}

		if (getMachineOwner()->isDisabledHeld())
			return (StateReturnType)STATE_SUCCESS;
	}
	else
	{
		return (StateReturnType)STATE_FAILURE;
	}

	StateReturnType code = AIInternalMoveToState::update();
	if (code != STATE_CONTINUE)
	{
		ContainModuleInterface *contain = goal->getContain();
		if (contain)
		{
			const Coord3D *pos = contain->getContainedObjectPosition();
			Real dx = obj->getPosition()->x - pos->x;
			Real dy = obj->getPosition()->y - pos->y;
			Real radius = goal->getBoundingCircleRadius();
			if (dx * dx + dy * dy < radius * radius || TheGameLogic->getFrame() > m_enterFrame)
			{
				contain->addToContain(obj);
				code = (StateReturnType)STATE_SUCCESS;
			}
		}
	}
	return code;
}

class AIEnterAndAttackState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	ObjectID m_entryToClear; // +0x4C
	ObjectID m_victimID; // +0x50
};

StateReturnType AIEnterAndAttackState::onEnter()
{
	m_entryToClear = INVALID_OBJECT_ID;
	Object *obj = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = obj->getAI();
	Object *victim = ai->getCurrentVictim();
	if (victim)
		m_victimID = victim->getID();
	else
		m_victimID = INVALID_OBJECT_ID;
	if (goal)
	{
		if (!TheActionManager->canEnterObject(obj, goal, obj->getAI()->getLastCommandSource(),
				CHECK_CAPACITY, 0, 0))
			return (StateReturnType)STATE_FAILURE;

		ContainModuleInterface *contain = goal->getContain();
		if (contain)
		{
			m_goalPosition = *contain->getContainedObjectPosition();
			contain->onObjectWantsToEnterOrExit(obj, WANTS_TO_ENTER);
			m_entryToClear = goal->getID();
		}
		else
		{
			m_goalPosition = *goal->getPosition();
		}
	}
	else
	{
		return (StateReturnType)STATE_FAILURE;
	}

	ai->ignoreObstacle(getMachine()->getGoalObject());
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setAllowInvalidPosition(true);
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 59");
	setAdjustsDestination(false);
	return AIInternalMoveToState::onEnter();
}

StateReturnType AIEnterAndAttackState::update()
{
	Object *obj = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (goal)
	{
		if (goal->getContainedBy() != 0 && goal->isAboveTerrain() && !obj->isAboveTerrain())
			return (StateReturnType)STATE_FAILURE;

		m_goalPosition = *goal->getPosition();
		obj->getAI()->friend_setGoalObject(goal);
		if (!TheActionManager->canEnterObject(obj, goal, obj->getAI()->getLastCommandSource(),
				CHECK_CAPACITY, 0, 0))
		{
			if (obj->getRelationship(goal) == ENEMIES && obj->getAI())
			{
				CanAttackResult result = TheActionManager->getCanAttackObject(obj, goal,
					obj->getAI()->getLastCommandSource(), ATTACK_NEW_TARGET);
				if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
				{
					AIUpdateInterface *ai = obj->getAI();
					ai->m_commands.rva0026C2D9(goal, 0x7fffffff, ai->getLastCommandSource());
					return STATE_CONTINUE;
				}
			}
			return (StateReturnType)STATE_FAILURE;
		}

		if (getMachineOwner()->isDisabledHeld())
			return (StateReturnType)STATE_SUCCESS;
	}
	else
	{
		return (StateReturnType)STATE_FAILURE;
	}

	StateReturnType code = AIInternalMoveToState::update();
	if (code == STATE_SUCCESS && goal->isAboveTerrain() && !obj->isAboveTerrain())
		code = STATE_CONTINUE;
	if (code == STATE_SUCCESS)
	{
		Real dx = obj->getPosition()->x - goal->getPosition()->x;
		Real dy = obj->getPosition()->y - goal->getPosition()->y;
		Real radius = goal->getBoundingCircleRadius();
		if (dx * dx + dy * dy < radius * radius)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
				contain->addToContain(obj);
		}
	}
	return code;
}

// The pinned killer notification SpawnBehavior::onSpawnDeath also makes
// (BFME 1 donor: killer->report(owner, 1)); its identity is unproven.
class Rva00294D61
{
public:
	void report(Object *victim, int count);
};

class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	Bool m_appendGoalPosition; // +0x4C
};

StateReturnType AIMoveToPositionAndDieState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
		return (StateReturnType)STATE_FAILURE;

	AIUpdateInterface *ai = obj->getAI();
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setAllowInvalidPosition(true);
	if (m_appendGoalPosition)
	{
		Path *thePath = ai->getPath();
		if (!ai->getBfmeFlag3B1() && ai->getPath())
		{
			m_goalPosition.z = TheTerrainLogic->getGroundHeight(m_goalPosition.x, m_goalPosition.y, 0);
			thePath->rva002655E3(&m_goalPosition, LAYER_GROUND, 0x7fffffff);
			m_appendGoalPosition = false;
		}
	}
	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		Object *killer = TheGameLogic->findObjectByID(obj->getBodyModule()->getLastDamageInfo()
			? obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID : INVALID_OBJECT_ID);
		if (killer)
			((Rva00294D61 *)killer)->report(obj, 1);
		obj->kill(DAMAGE_BFME_8, DEATH_NORMAL);
	}
	return status;
}

class AIMoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	int m_bfmeValue4C; // +0x4C
	Bool m_bfmeFlag50; // +0x50
};

StateReturnType AIMoveAwayAndCowerState::onEnter()
{
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!goal || !ai)
		return (StateReturnType)STATE_FAILURE;
	ai->rva0034BEF9Slot142(4);
	m_bfmeValue4C = 1;
	m_bfmeFlag50 = true;
	ai->rva00263EA2(goal->getID());
	return AIInternalMoveToState::onEnter();
}

class AIFaceDirectionState : public State
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Real m_angle; // +0x20
};

StateReturnType AIFaceDirectionState::update()
{
	Object *owner = getMachineOwner();
	Real angle = m_angle;
	Real delta = normalizeAngle(angle - owner->getOrientation());
	if (delta < 0.31415927f)
	{
		owner->setOrientation(m_angle);
		return (StateReturnType)STATE_SUCCESS;
	}
	owner->getAI()->setLocomotorGoalOrientation(m_angle);
	return STATE_CONTINUE;
}

class AIPrepareForBoarding : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};

StateReturnType AIPrepareForBoarding::onEnter()
{
	Object *owner = getMachineOwner();
	Coord3D dest;
	Bool found = TheAI->pathfinder()->getClosestPointOnLand(owner->getPosition(), owner, &dest);
	Object *goal = getMachine()->getGoalObject();
	getMachine()->setGoalObject(0);
	if (found)
	{
		if (!goal)
			return (StateReturnType)STATE_FAILURE;
		if (TheAI->pathfinder()->QuickDoesPathExist(goal, goal->getPosition(), &dest, 0))
			return (StateReturnType)STATE_FAILURE;
	}
	return (StateReturnType)STATE_SUCCESS;
}

StateReturnType AIPrepareForBoarding::update()
{
	Object *owner = getMachineOwner();
	Coord3D dest;
	if (TheAI->pathfinder()->getClosestPointOnLand(owner->getPosition(), owner, &dest))
	{
		owner->getAI()->m_commands.aiIdle(CMD_FROM_AI);
		return (StateReturnType)STATE_FAILURE;
	}
	return (StateReturnType)STATE_SUCCESS;
}

class AIMoveAndTightenState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad4C[0x50 - 0x4C];
	Bool m_bfmeFlag50; // +0x50
};

StateReturnType AIMoveAndTightenState::update()
{
	if (m_bfmeFlag50)
	{
		AIUpdateInterface *ai = getMachineOwner()->getAI();
		if (ai->getPath() && !ai->getBfmeFlag3B1())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 8");
			setAdjustsDestination(true);
			m_bfmeFlag50 = false;
		}
	}
	return AIInternalMoveToState::update();
}

class AICombineState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AICombineState::onEnter()
{
	StateReturnType ret = rva0034612C();
	if (ret != STATE_CONTINUE)
		return ret;
	Rva0028C197Result *result = (Rva0028C197Result *)getMachineOwner()->rva0028C197();
	if (result && result->rva0034FCCESlot136())
		result->rva0034FCDCSlot24();
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 58");
	setAdjustsDestination(false);
	return AIInternalMoveToState::onEnter();
}

class AIRotateFiringarc : public State
{
public:
	virtual StateReturnType update();
};

StateReturnType AIRotateFiringarc::update()
{
	if (!getMachineOwner()->getAI())
		return (StateReturnType)STATE_FAILURE;
	getMachineOwner()->setBfmeAngle1C0(getMachineOwner()->getOrientation());
	Real orientation = getMachineOwner()->getOrientation();
	Real goalAngle = getMachine()->getGoalPosition()->x;
	Real delta = normalizeAngle(orientation - goalAngle);
	if (fabs(delta) < 0.01f)
		return (StateReturnType)STATE_SUCCESS;
	return STATE_CONTINUE;
}

class AIBusyState : public State
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIBusyState::onEnter()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = owner->getAI();
	if ((ai->getMoodMatrixActionAdjustment(MM_ACTION_BFME_2) & 1) && goal
		&& !owner->chooseBestWeaponForTarget(goal, WEAPON_CHOICE_BFME_5, ai->getLastCommandSource()))
		return (StateReturnType)STATE_FAILURE;
	return (StateReturnType)STATE_SUCCESS;
}
