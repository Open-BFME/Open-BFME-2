// ?onEnter@AIGuardReturnState@@UAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc
//
// The rest of the ZH AIGuard port -- every class below, and the sibling
// onEnter/update/onExit bodies -- lives in AIGuardStates.cpp, which already
// carries their ledger rows. Only this body is new, so it has its own TU rather
// than a second copy of the port.
//
// BLOCK LAYOUT (the whole delta the earlier bank could not close): retail puts
// the early STATE_SUCCESS return LAST. It jumps `ja 0x543DE9` forward over the
// entire main path, and the main path's own tail `jmp 0x543DEC` skips the
// success block, which is that jump's fallthrough. Writing
// `return STATE_SUCCESS` inside the `if (owner)` arm makes VC7 sink it inline as
// `jbe / or eax,-1 / jmp`, which is one byte short and threads every block
// differently. Naming the test in a Bool and guarding the main path with
// `if (!near) { ... return AIInternalMoveToState::onEnter(); }` followed by a
// trailing `return STATE_SUCCESS;` reproduces retail's shape exactly.
//
// AIGuard state bodies ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIGuard.cpp (GeneralsMD tree vendored under reference/open-bfme-1/inputs/
// reference). Vtables are named by their slot-2 name getters:
//  - AIGuardAttackAggressorState::onExit, retail 0x00542C87 (76 bytes): slot 5
//    of 0x00C69890 (AIGuardAttackAggressorState). The same body is slot 5 of
//    0x00C69780 (AIGuardInnerState) and 0x00C69FA0
//    (AIGuardRetaliateAttackAggressorState): BFME 2's inner state lost ZH's
//    enter-state branch, so the bodies fold. Only this one row claims it.
//  - AIGuardAttackAggressorState::update, retail 0x0054403B (90 bytes): slot 6
//    of 0x00C69890.
//  - AIGuardOuterState::onExit, retail 0x00542CD3 (51 bytes): slot 5 of
//    0x00C697D8 (AIGuardOuterState).
//  - AIGuardReturnState::update, retail 0x00543DF1 (108 bytes): slot 6 of
//    0x00C69830 (AIGuardReturnState). BFME 2 only runs ZH's return scan while
//    the locomotor distance to goal (pinned
//    AIUpdateInterface::getLocomotorDistanceToGoal 0x0026435E, the ZH
//    goal-type switch) is inside the standard guard range.
//  - AIGuardIdleState::update, retail 0x00543E5D (251 bytes): slot 6 of
//    0x00C696D0 (AIGuardIdleState); BFME 2 also checks a guarded team's
//    centre. AI crate id +0x238, AI_GUARD_GET_CRATE 5004 through the machine's
//    setState (vslot 8), m_nextEnemyScanTime +0x20, m_guardeePos +0x24.
//  - AIGuardIdleState::onEnter, retail 0x00542D88 (53 bytes): slot 4 of
//    0x00C696D0; ZH's randomised first scan (GameLogicRandomValue at AIGuard.cpp
//    line 1013 in BFME 2's tree).
//  - AIGuardAttackAggressorState::onEnter, retail 0x00543F58 (227 bytes): slot
//    4 of 0x00C69890. ZH's nemesis lookup (owner body module +0x254, vslot 15
//    getLastDamageInfo, source id +8; guard machine nemesis id +0x68) and the
//    new AIAttackState (rowed ctor 0x0034B0DD) over m_exitConditions; BFME 2
//    drops ZH's guard centre and radius (only the give-up frame from
//    TAiData +0x3C and conditions 6 = expired duration | no unit found), and
//    first restarts itself through its own onEnter slot while the +0x40 flag
//    is set (clearing it). Retail keeps TheGameLogic in a register across the
//    nemesis lookup, so the body reads it once into a local.
//  - AIGuardInnerState::onEnter, retail 0x0054379B (315 bytes): slot 4 of
//    0x00C69780 (AIGuardInnerState). BFME 2 drops ZH's enter-guard branch:
//    the centre is the guarded object's position, else the guarded team's
//    centre, else the machine's position to guard (+0x48); radius from the
//    standard guard range, or the area to guard (+0x44: the pinned
//    PolygonTrigger::getCenterPoint and the radius getter of its +8 shape,
//    pinned opaque 0x0030B719); conditions 5; then the attack sub-state and a
//    +0x44 deadline three seconds out (g_009BA4E4 frames per second).
//  - AIGuardInnerState::update, retail 0x005438D6 (284 bytes): slot 6 of
//    0x00C69780. ZH's centre follow and attack update; BFME 2 first restarts
//    through onEnter while the +0x40 flag is set, and re-targets (onExit, then
//    onEnter) when lookForInnerTarget succeeds while the attack goal is gone
//    or flagged (goal byte +0x438 bit 0), or, for a goal with template kind
//    byte +0x108 mask 0x80, once a second while the owner's current weapon
//    (rowed Object::getCurrentWeapon, Weapon::computeStatus) is not in
//    status 4.
//  - AIGuardOuterState::onEnter, retail 0x005439F2 (360 bytes): slot 4 of
//    0x00C697D8. ZH's body (no pursuit in GUARDMODE_GUARD_WITHOUT_PURSUIT,
//    guard mode at machine +0x6C; vision range with OWNERTYPE|MOOD) on the
//    BFME 2 centre (object, team, position); BFME 2 also gives up unless the
//    owner's rowed Object::rva0028B511 reads 1 or the static at 0x002FE193
//    (pinned opaque as AI::rva002FE193) accepts (owner, nemesis), takes a
//    cached area centre (machine +0x54, valid flag +0x60) before
//    getCenterPoint, and no longer widens the range to the area radius.
//  - AIGuardReturnState::onEnter, retail 0x00543CC4 (301 bytes): slot 4 of
//    0x00C69830. ZH's randomised return scan (AIGuard.cpp line 881) and the
//    ground-movement adjustDestination (pinned) before the base onEnter, with
//    setAdjustsDestination(true) and its CritterDesync log; BFME 2 takes the
//    goal from the machine's guard-centre getter (0x00543326, pinned opaque)
//    with the machine's +0x64 radius kept at state +0x2C, succeeds at once
//    when the owner is within 5 (Coord3D::GetLengthEstimate), and else
//    destroys the AI path and hands goal and radius to the machine's
//    setGoalPosition.
//  - AIGuardMachine::getStdGuardRange, retail 0x00542C2A (14 bytes): ZH's
//    static over AI::getAdjustedVisionRangeForObject (pinned 0x002FDD0A, static
//    as in ZH) with OWNERTYPE|MOOD|GUARDINNER.
// BFME2 layout (target evidence): attack sub-state +0x3C (deleted with a
// global-scope delete: vslot 0 with flag 0, then ::operator delete), exit
// conditions centre +0x28; the guard machine keeps the object-to-guard id at
// +0x3C and a team-to-guard id at +0x40 (BFME 2 addition: with no object the
// centre follows the team through the rowed Team::rva0039E5B9). Owner team
// +0x304; setTeamTargetObject is the rowed Team::rva0039D84A. TeamFactory's
// findTeamByID is the pinned 0x0039F761 (prototype walk as in Generals).
typedef bool Bool;
#define NULL 0
typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID
{
	INVALID_ID = 0
};
typedef UnsignedInt TeamID;
enum
{
	AI_VISIONFACTOR_OWNERTYPE = 0x01,
	AI_VISIONFACTOR_MOOD = 0x02,
	AI_VISIONFACTOR_GUARDINNER = 0x04
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
	Real GetLengthEstimate() const;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
};
class Object;
class AIUpdateInterface;
class Rva0030B719Shape
{
public:
	Real getRadius(void) const;
};
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCenter) const;
	const Rva0030B719Shape *getShape() const { return &m_shape; }
private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape; // +0x08
};
extern const int g_009BA4E4;
#define LOGICFRAMES_PER_SECOND g_009BA4E4
class Team
{
public:
	void rva0039D84A(Object *target);
	void setTeamTargetObject(Object *target) { rva0039D84A(target); }
	void rva0039E5B9(Coord3D *pos);
};
class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};
extern TeamFactory *TheTeamFactory;
struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class BodyModuleInterface : public VSlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};
class ThingTemplate
{
public:
	Bool isKindOfBfme108Bit7() const { return (m_kindOf[0] & 0x80) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	WEAPON_STATUS_BFME_4 = 4
};
class Weapon
{
public:
	WeaponStatus computeStatus(Bool *noAmmo = NULL) const;
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool testBfme438Bit0() const { return (m_bfme438 & 1) != 0; }
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = NULL) const;
	int rva0028B511() const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	const Coord3D *getPosition() const { return &m_position; }
	Team *getTeam() { return m_team; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x254 - 0x44];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_bfme438; // +0x438
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
class LocomotorSet;
class Pathfinder;
// isDoingGroundMovement is AIUpdateInterface vslot 137 (+0x224).
class AIUpdateInterface : public VSlots<137>
{
public:
	virtual Bool isDoingGroundMovement(void) const = 0;
	Real getLocomotorDistanceToGoal();
	ObjectID getCrateID() const { return m_crateCreated; }
	const LocomotorSet &getLocomotorSet(void) const { return *(const LocomotorSet *)m_locomotorSet; }
	void destroyPath(void);
private:
	unsigned char m_pad004[0x1CC - 0x04];
	unsigned char m_locomotorSet[0x238 - 0x1CC]; // +0x1CC
	ObjectID m_crateCreated; // +0x238
};
struct TAiData
{
	unsigned char m_pad00[0x3C];
	UnsignedInt m_guardChaseUnitFrames; // +0x3C
	UnsignedInt m_guardEnemyScanRate; // +0x40
	UnsignedInt m_guardEnemyReturnScanRate; // +0x44
};
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
	static Real getAdjustedVisionRangeForObject(const Object *object, int factorsToConsider);
	static Bool rva002FE193(Object *obj, Object *nemesis);
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;
typedef UnsignedInt StateID;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	void setGoalPosition(const Coord3D *pos, Real radius);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AIGuardMachine : public StateMachine
{
public:
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	Bool lookForInnerTarget(void);
	static Real getStdGuardRange(const Object *obj);
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
	ObjectID getNemesisID() const { return m_nemesisToAttack; }
	const PolygonTrigger *getAreaToGuard(void) const { return m_areaToGuard; }
	const Coord3D *getPositionToGuard(void) const { return &m_positionToGuard; }
	int getGuardMode() const { return m_guardMode; }
	Bool hasBfmeAreaCenter() const { return m_bfmeAreaCenterValid; }
	const Coord3D *getBfmeAreaCenter() const { return &m_bfmeAreaCenter; }
	Coord3D rva00543326() const;
	Real getBfmeGuardRadius() const { return m_bfmeGuardRadius; }
private:
	unsigned char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
	const PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
	unsigned char m_pad61[0x64 - 0x61];
	Real m_bfmeGuardRadius; // +0x64
	ObjectID m_nemesisToAttack; // +0x68
	int m_guardMode; // +0x6C
};
enum
{
	GUARDMODE_NORMAL = 0,
	GUARDMODE_GUARD_WITHOUT_PURSUIT = 1
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
	StateMachine *getMachine() const { return m_machine; }
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
class ExitConditions : public AttackExitConditionsInterface
{
public:
	enum ExitConditionsEnum
	{
		ATTACK_ExitIfOutsideRadius = 0x01,
		ATTACK_ExitIfExpiredDuration = 0x02,
		ATTACK_ExitIfNoUnitFound = 0x04
	};
	virtual Bool shouldExit(const StateMachine *machine) const;
	int m_conditionsToConsider; // +0x04 (state +0x24)
	Coord3D m_center; // +0x08 (state +0x28)
	Real m_radiusSqr; // +0x14
	UnsignedInt m_attackGiveUpFrame; // +0x18 (state +0x38)
};
class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	unsigned char m_pad1C[0x50 - 0x1C]; // sizeof(AIAttackState) 0x50 (the operator new size)
};
class AIGuardAttackAggressorState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
};
class AIGuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
	unsigned char m_pad41[0x44 - 0x41];
	UnsignedInt m_bfmeDeadline; // +0x44
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	Real m_bfmeGoalRadius; // +0x2C
	unsigned char m_pad30[0x48 - 0x30];
	Bool m_adjustsDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};
class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = NULL);
};
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
class AIGuardReturnState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	UnsignedInt m_nextReturnScanTime; // +0x4C
};
enum
{
	AI_GUARD_GET_CRATE = 5004
};
#define PATHFIND_CELL_SIZE_F 10.0f
#define STATE_SLEEP(n) ((StateReturnType)(n))
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AIGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIGuard.cpp"
class AIGuardIdleState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_nextEnemyScanTime; // +0x20
	Coord3D m_guardeePos; // +0x24
};
class AIGuardOuterState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
};

StateReturnType AIGuardReturnState::onEnter( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, AIGUARD_FILE, 881);

	m_goalPosition = getGuardMachine()->rva00543326();
	m_bfmeGoalRadius = getGuardMachine()->getBfmeGuardRadius();

	Object *owner = getMachineOwner();
	Bool near = false;
	if (owner)
	{
		Coord3D delta;
		delta.set(owner->getPosition());
		delta.sub(&m_goalPosition);
		near = (delta.GetLengthEstimate() < 5.0f);
	}
	if (!near)
	{
		AIUpdateInterface *ai = getMachineOwner()->getAI(); 
		if (ai)
		{
			if (ai->isDoingGroundMovement()) 
			{
				TheAI->pathfinder()->adjustDestination(getMachineOwner(), ai->getLocomotorSet(), &m_goalPosition);
			}
			ai->destroyPath();
		}
		getMachine()->setGoalPosition(&m_goalPosition, m_bfmeGoalRadius);
		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log)
				fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 3");
		}
		setAdjustsDestination(true);
		return AIInternalMoveToState::onEnter();
	}
	return STATE_SUCCESS;
}

// AIGuardReturnState::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp (0x00543DF1).

// AIGuardIdleState::onEnter is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp (0x00542D88).

// AIGuardIdleState::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp (0x00543E5D).
