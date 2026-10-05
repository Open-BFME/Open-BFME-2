// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /EHsc
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
class AIUpdateInterface
{
public:
	Real getLocomotorDistanceToGoal();
	ObjectID getCrateID() const { return m_crateCreated; }
private:
	unsigned char m_pad00[0x238];
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
private:
	unsigned char m_pad00[0x18];
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
private:
	unsigned char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
	const PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
	unsigned char m_pad61[0x68 - 0x61];
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
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x4C - 0x1C];
};
class AIGuardReturnState : public AIInternalMoveToState
{
public:
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

StateReturnType AIGuardAttackAggressorState::onEnter( void )
{
	if (m_bfmeRestart)
	{
		m_bfmeRestart = false;
		return onEnter();
	}
	Object *obj = getMachineOwner();
	ObjectID nemID = INVALID_ID;

	if (obj->getBodyModule() && obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID) {
		nemID = obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID;
		getGuardMachine()->setNemesisID(nemID);
	}

	GameLogic *logic = TheGameLogic;
	Object *nemesis = logic->findObjectByID(getGuardMachine()->getNemesisID());
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}

	m_exitConditions.m_attackGiveUpFrame = logic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | 
																						 ExitConditions::ATTACK_ExitIfNoUnitFound);

	m_attackState = new AIAttackState(getMachine(), true, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

StateReturnType AIGuardInnerState::onEnter( void )
{
	AIGuardMachine *guard = getGuardMachine();
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->rva0039E5B9(&pos);
	else
		pos = *getGuardMachine()->getPositionToGuard();
	Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}
	m_exitConditions.m_center = pos;
	Real range = AIGuardMachine::getStdGuardRange(getMachineOwner());
	m_exitConditions.m_radiusSqr = range * range;
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfOutsideRadius | 
																							ExitConditions::ATTACK_ExitIfNoUnitFound);
	const PolygonTrigger *area = getGuardMachine()->getAreaToGuard();
	if (area) 
	{
		m_exitConditions.m_radiusSqr = area->getShape()->getRadius() * area->getShape()->getRadius();
		area->getCenterPoint(&m_exitConditions.m_center);
	}

	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);

	m_attackState->getMachine()->setGoalObject(nemesis);
	m_bfmeDeadline = TheGameLogic->getFrame() + 3*LOGICFRAMES_PER_SECOND;

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

StateReturnType AIGuardInnerState::update( void )
{
	if (m_bfmeRestart)
	{
		m_bfmeRestart = false;
		return onEnter();
	}
	if (m_attackState == NULL)
		return STATE_SUCCESS;

	// if the position has moved (IE we're guarding an object), move with it.
	AIGuardMachine *guard = getGuardMachine();
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	if (targetToGuard)
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}
	else if (teamToGuard)
	{
		teamToGuard->rva0039E5B9(&m_exitConditions.m_center);
	}

	StateReturnType ret = m_attackState->update();
	Object *goal = m_attackState->getMachine()->getGoalObject();
	if (goal == NULL || goal->testBfme438Bit0())
	{
		if (getGuardMachine()->lookForInnerTarget())
		{
			onExit(EXIT_NORMAL);
			return onEnter();
		}
	}
	if (goal && goal->getTemplate()->isKindOfBfme108Bit7() && TheGameLogic->getFrame() >= m_bfmeDeadline)
	{
		const Weapon *weapon = getMachine()->getOwner()->getCurrentWeapon();
		if (weapon && weapon->computeStatus() != WEAPON_STATUS_BFME_4)
		{
			m_bfmeDeadline = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND;
			if (getGuardMachine()->lookForInnerTarget())
			{
				onExit(EXIT_NORMAL);
				return onEnter();
			}
		}
	}
	return ret;
}

StateReturnType AIGuardOuterState::onEnter( void )
{
	if (getGuardMachine()->getGuardMode() == GUARDMODE_GUARD_WITHOUT_PURSUIT)
	{
		// "patrol" mode does not follow targets outside the guard area.
		return STATE_SUCCESS;
	}

	AIGuardMachine *guard = getGuardMachine();
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->rva0039E5B9(&pos);
	else
		pos = *getGuardMachine()->getPositionToGuard();

	AIGuardMachine *machine = getGuardMachine();
	Object* nemesis = TheGameLogic->findObjectByID(machine->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}
	Object *obj = machine->getOwner();
	if (obj->rva0028B511() != 1 && !AI::rva002FE193(obj, nemesis))
	{
		return STATE_SUCCESS;
	}

	Real range = TheAI->getAdjustedVisionRangeForObject(obj, AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD);

	const PolygonTrigger *area = getGuardMachine()->getAreaToGuard();
	if (area) 
	{
		if (getGuardMachine()->hasBfmeAreaCenter())
			pos = *getGuardMachine()->getBfmeAreaCenter();
		else
			area->getCenterPoint(&pos);
	}
	m_exitConditions.m_center = pos;
	m_exitConditions.m_radiusSqr = range * range;
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | 
																								ExitConditions::ATTACK_ExitIfOutsideRadius | 
																								ExitConditions::ATTACK_ExitIfNoUnitFound);

	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);

	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

StateReturnType AIGuardAttackAggressorState::update( void )
{
	if (m_attackState==NULL) return STATE_SUCCESS;
	// if the position has moved (IE we're guarding an object), move with it.
	AIGuardMachine *guard = getGuardMachine();
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	if (targetToGuard)
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}
	else if (teamToGuard)
	{
		teamToGuard->rva0039E5B9(&m_exitConditions.m_center);
	}

	return m_attackState->update();
}

void AIGuardAttackAggressorState::onExit( StateExitType status )
{
	Object *obj = getMachineOwner();
	if (m_attackState)
	{
		m_attackState->onExit(status);
		::delete m_attackState;
		m_attackState = NULL;
	}

	if (obj->getTeam())
	{
		obj->getTeam()->setTeamTargetObject(NULL); // clear the target.
	}
}

void AIGuardOuterState::onExit( StateExitType status )
{
	if (m_attackState)
	{
		m_attackState->onExit(status);
		::delete m_attackState;
		m_attackState = NULL;
	}
}

/*static*/ Real AIGuardMachine::getStdGuardRange(const Object* obj)
{
	Real visionRange = TheAI->getAdjustedVisionRangeForObject(obj,
		AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD | AI_VISIONFACTOR_GUARDINNER);

	return visionRange;
}

StateReturnType AIGuardReturnState::update( void )
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	if (ai && ai->getLocomotorDistanceToGoal() < AIGuardMachine::getStdGuardRange(obj))
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (now >= m_nextReturnScanTime)
		{
			m_nextReturnScanTime = now + TheAI->getAiData()->m_guardEnemyReturnScanRate;
			if (getGuardMachine()->lookForInnerTarget())
				return STATE_FAILURE; // early termination because we found a target.
		}
	}

	// Just let the return movement finish.
	return AIInternalMoveToState::update();
}

StateReturnType AIGuardIdleState::onEnter( void )
{
	// first time thru, use a random amount so that everyone doesn't scan on the same frame,
	// to avoid "spikes".
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyScanRate, AIGUARD_FILE, 1013);

	return STATE_CONTINUE;
}

StateReturnType AIGuardIdleState::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return STATE_SLEEP(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	AIGuardMachine *guard = getGuardMachine();
	Object *owner = guard->getOwner();
	AIUpdateInterface *ai = owner->getAI();
	// Check to see if we have created a crate we need to pick up.
	if (ai->getCrateID() != INVALID_ID)
	{
		guard->setState(AI_GUARD_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	// if anyone is in the inner area, return success.
	if (guard->lookForInnerTarget())
	{
		return STATE_SUCCESS;	// Transitions to AIGuardInnerState.
	}

	// See if the object (or team) we are guarding moved.
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	if (targetToGuard || teamToGuard)
	{
		Coord3D pos;
		if (targetToGuard)
			pos = *targetToGuard->getPosition();
		else
			teamToGuard->rva0039E5B9(&pos);
		Real delta = m_guardeePos.x-pos.x;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE; // goes to AIGuardReturnState.
		}
		delta = m_guardeePos.y-pos.y;
		if (delta*delta > 4*PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F) {
			m_guardeePos = pos;
			return STATE_FAILURE; // goes to AIGuardReturnState.
		}
	}
	return STATE_SLEEP(m_nextEnemyScanTime - now);
}
