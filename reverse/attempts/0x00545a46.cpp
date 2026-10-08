// ?update@AIGuardRetaliateAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.99 date=2026-10-09
// ?update@AIGuardRetaliateAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.8 date=2026-10-04
// cl: /G7 /O1 /DNDEBUG /MD /arch:SSE
//
// AIGuardRetaliate state bodies ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIGuardRetaliate.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Vtables are named by
// their slot-2 name getters:
//  - AIGuardRetaliateReturnState::onEnter, retail 0x005452CB (200 bytes): slot
//    4 of 0x00C69F38. ZH's randomised return scan (line 248 of BFME 2's
//    AIGuardRetaliate.cpp) and the goal from the machine's position to guard
//    (+0x3C), the ground-movement adjustDestination (pinned), then
//    setAdjustsDestination(true) with its CritterDesync log before the base
//    onEnter. BFME 2 also resets the owner's +0x250 module: its vslot 31
//    result, if any, gets vslot 5 with 0.
//  - AIGuardRetaliateReturnState::update, retail 0x0054574D (221 bytes): slot
//    6 of 0x00C69F38. ZH's return scan through the retaliate machine's
//    lookForInnerTarget (pinned 0x005455E3) before the base update; BFME 2
//    first fails over to its last attacker (owner body vslot 18) when that
//    object is not flagged (+0x438 bit 0), is an enemy (rowed
//    getRelationship), the owner can attack (rowed isAbleToAttack) and the
//    pinned getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, attacker,
//    CMD_FROM_AI) allows it, redirecting through the rowed
//    Object::rva002931F5 for status 0x26 as AIGuardRetaliateState::onEnter
//    does, and storing it as the machine's nemesis (+0x48).
//  - AIGuardRetaliateAttackAggressorState::update, retail 0x00545A46 (265
//    bytes): slot 6 of 0x00C69FA0. Zero Hour only runs the attack sub-state;
//    BFME 2 first drops a flagged (+0x438 bit 0) nemesis or machine goal, and
//    with no goal takes the nemesis or else the helper's pick (below) as the
//    AI's goal object (rowed AIUpdateInterface::rva00262B0F, pinned as
//    friend_setGoalObject), the machine's nemesis and goal; it succeeds once
//    its exit conditions (vslot 0, called through the interface) hold or
//    there is no attack sub-state; while the owner has status 0x1C, or its
//    +0x250 module's controller (vslot 31) reports the nemesis through
//    vslots 88 or 138, it extends the give-up frame (+0x38) to four seconds
//    out; then the attack sub-state's update.
//  - AIGuardRetaliateAttackAggressorState::rva0054582A, retail 0x0054582A
//    (80 bytes): that helper. The object with id +0x40 (BFME 2 field), if it
//    exists and has a +0x250 controller, picks an object around the owner's
//    position (controller vslot 18 with (0, &pos, 0.0f, 0, 0)).
// Layout (target evidence): state goal +0x20, adjusts-destination +0x48,
// m_nextReturnScanTime +0x4C; TAiData m_guardEnemyReturnScanRate +0x44.
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
#define NULL 0
enum ObjectID
{
	INVALID_ID = 0
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING,
	ATTACKRESULT_POSSIBLE
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_1C = 0x1C,
	OBJECT_STATUS_BFME_26 = 0x26
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
class LocomotorSet;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
// isDoingGroundMovement is AIUpdateInterface vslot 137 (+0x224).
class AIUpdateInterface : public VSlots<137>
{
public:
	virtual Bool isDoingGroundMovement(void) const = 0;
	void friend_setGoalObject(Object *obj);
	const LocomotorSet &getLocomotorSet(void) const { return *(const LocomotorSet *)m_locomotorSet; }
private:
	unsigned char m_pad004[0x1CC - 0x04];
	unsigned char m_locomotorSet[4]; // +0x1CC
};
class Object;
struct Coord3D;
// The +0x250 module controller (module vslot 31): reset vslot 5, pick vslot 18,
// target tests vslots 88 and 138 (identities not established).
class Rva00545355Target : public VSlots<5>
{
public:
	virtual void bfmeReset(int value) = 0;
	virtual void gap006() = 0;
	virtual void gap007() = 0;
	virtual void gap008() = 0;
	virtual void gap009() = 0;
	virtual void gap010() = 0;
	virtual void gap011() = 0;
	virtual void gap012() = 0;
	virtual void gap013() = 0;
	virtual void gap014() = 0;
	virtual void gap015() = 0;
	virtual void gap016() = 0;
	virtual void gap017() = 0;
	virtual Object *bfmePick(int a, const Coord3D *pos, float radius, int b, int c) = 0;
	virtual void gap019() = 0;
	virtual void gap020() = 0;
	virtual void gap021() = 0;
	virtual void gap022() = 0;
	virtual void gap023() = 0;
	virtual void gap024() = 0;
	virtual void gap025() = 0;
	virtual void gap026() = 0;
	virtual void gap027() = 0;
	virtual void gap028() = 0;
	virtual void gap029() = 0;
	virtual void gap030() = 0;
	virtual void gap031() = 0;
	virtual void gap032() = 0;
	virtual void gap033() = 0;
	virtual void gap034() = 0;
	virtual void gap035() = 0;
	virtual void gap036() = 0;
	virtual void gap037() = 0;
	virtual void gap038() = 0;
	virtual void gap039() = 0;
	virtual void gap040() = 0;
	virtual void gap041() = 0;
	virtual void gap042() = 0;
	virtual void gap043() = 0;
	virtual void gap044() = 0;
	virtual void gap045() = 0;
	virtual void gap046() = 0;
	virtual void gap047() = 0;
	virtual void gap048() = 0;
	virtual void gap049() = 0;
	virtual void gap050() = 0;
	virtual void gap051() = 0;
	virtual void gap052() = 0;
	virtual void gap053() = 0;
	virtual void gap054() = 0;
	virtual void gap055() = 0;
	virtual void gap056() = 0;
	virtual void gap057() = 0;
	virtual void gap058() = 0;
	virtual void gap059() = 0;
	virtual void gap060() = 0;
	virtual void gap061() = 0;
	virtual void gap062() = 0;
	virtual void gap063() = 0;
	virtual void gap064() = 0;
	virtual void gap065() = 0;
	virtual void gap066() = 0;
	virtual void gap067() = 0;
	virtual void gap068() = 0;
	virtual void gap069() = 0;
	virtual void gap070() = 0;
	virtual void gap071() = 0;
	virtual void gap072() = 0;
	virtual void gap073() = 0;
	virtual void gap074() = 0;
	virtual void gap075() = 0;
	virtual void gap076() = 0;
	virtual void gap077() = 0;
	virtual void gap078() = 0;
	virtual void gap079() = 0;
	virtual void gap080() = 0;
	virtual void gap081() = 0;
	virtual void gap082() = 0;
	virtual void gap083() = 0;
	virtual void gap084() = 0;
	virtual void gap085() = 0;
	virtual void gap086() = 0;
	virtual void gap087() = 0;
	virtual Bool bfmeIsTarget(const Object *obj) = 0;
	virtual void gap089() = 0;
	virtual void gap090() = 0;
	virtual void gap091() = 0;
	virtual void gap092() = 0;
	virtual void gap093() = 0;
	virtual void gap094() = 0;
	virtual void gap095() = 0;
	virtual void gap096() = 0;
	virtual void gap097() = 0;
	virtual void gap098() = 0;
	virtual void gap099() = 0;
	virtual void gap100() = 0;
	virtual void gap101() = 0;
	virtual void gap102() = 0;
	virtual void gap103() = 0;
	virtual void gap104() = 0;
	virtual void gap105() = 0;
	virtual void gap106() = 0;
	virtual void gap107() = 0;
	virtual void gap108() = 0;
	virtual void gap109() = 0;
	virtual void gap110() = 0;
	virtual void gap111() = 0;
	virtual void gap112() = 0;
	virtual void gap113() = 0;
	virtual void gap114() = 0;
	virtual void gap115() = 0;
	virtual void gap116() = 0;
	virtual void gap117() = 0;
	virtual void gap118() = 0;
	virtual void gap119() = 0;
	virtual void gap120() = 0;
	virtual void gap121() = 0;
	virtual void gap122() = 0;
	virtual void gap123() = 0;
	virtual void gap124() = 0;
	virtual void gap125() = 0;
	virtual void gap126() = 0;
	virtual void gap127() = 0;
	virtual void gap128() = 0;
	virtual void gap129() = 0;
	virtual void gap130() = 0;
	virtual void gap131() = 0;
	virtual void gap132() = 0;
	virtual void gap133() = 0;
	virtual void gap134() = 0;
	virtual void gap135() = 0;
	virtual void gap136() = 0;
	virtual void gap137() = 0;
	virtual int bfmeTargetID(int id) = 0;
};
class Rva00545355Module : public VSlots<31>
{
public:
	virtual Rva00545355Target *bfmeTarget() = 0;
};
class BodyModuleInterface : public VSlots<18>
{
public:
	virtual ObjectID getClearableLastAttacker() const = 0;
};
class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Bool testBfme438Bit0() const { return (m_bfme438 & 1) != 0; }
	Relationship getRelationship(const Object *that) const;
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType commandSource) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Object *rva002931F5(Bool flag);
	AIUpdateInterface *getAI() { return m_ai; }
	Rva00545355Module *getBfme250() { return m_bfme250; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x250 - 0x78];
	Rva00545355Module *m_bfme250; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_bfme438; // +0x438
};
class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = NULL);
};
struct TAiData
{
	unsigned char m_pad00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate; // +0x44
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
extern const int g_009BA4E4;
#define LOGICFRAMES_PER_SECOND g_009BA4E4
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AIGUARDRETALIATE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Ai\\AIGuardRetaliate.cpp"
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AIGuardRetaliateMachine : public StateMachine
{
public:
	const Coord3D *getPositionToGuard(void) const { return &m_positionToGuard; }
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
	ObjectID getNemesisID() const { return m_nemesisToAttack; }
	Bool lookForInnerTarget(void);
private:
	unsigned char m_pad18[0x3C - 0x18];
	Coord3D m_positionToGuard; // +0x3C
	ObjectID m_nemesisToAttack; // +0x48
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
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
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};
class AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	AIGuardRetaliateMachine *getGuardMachine() { return (AIGuardRetaliateMachine *)getMachine(); }
	UnsignedInt m_nextReturnScanTime; // +0x4C
};

//--------------------------------------------------------------------------------------
StateReturnType AIGuardRetaliateReturnState::onEnter( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, AIGUARDRETALIATE_FILE, 248);

	m_goalPosition = *getGuardMachine()->getPositionToGuard();

	AIUpdateInterface *ai = getMachineOwner()->getAI(); 
	if (ai && ai->isDoingGroundMovement()) 
	{
		TheAI->pathfinder()->adjustDestination(getMachineOwner(), ai->getLocomotorSet(), &m_goalPosition);
	}
	Rva00545355Module *module = getMachineOwner()->getBfme250();
	if (module)
	{
		Rva00545355Target *target = module->bfmeTarget();
		if (target)
			target->bfmeReset(0);
	}
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log)
			fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 4");
	}
	setAdjustsDestination(true);
	return AIInternalMoveToState::onEnter();
}

//--------------------------------------------------------------------------------------
StateReturnType AIGuardRetaliateReturnState::update( void )
{
	Object *owner = getMachineOwner();
	BodyModuleInterface *body = owner ? owner->getBodyModule() : NULL;
	if (owner && body)
	{
		Object *attacker = TheGameLogic->findObjectByID(body->getClearableLastAttacker());
		if (attacker && !attacker->testBfme438Bit0() && owner->getRelationship(attacker) == ENEMIES && owner->isAbleToAttack())
		{
			CanAttackResult result = owner->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, attacker, CMD_FROM_AI);
			if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
			{
				if (attacker->testStatus(OBJECT_STATUS_BFME_26) && attacker->rva002931F5(false))
					attacker = attacker->rva002931F5(false);
				getGuardMachine()->setNemesisID(attacker->getID());
				return STATE_FAILURE;
			}
		}
	}

	UnsignedInt now = TheGameLogic->getFrame();
	if (now >= m_nextReturnScanTime)
	{
		m_nextReturnScanTime = now + TheAI->getAiData()->m_guardEnemyReturnScanRate;
		if (getGuardMachine()->lookForInnerTarget()) 
			return STATE_FAILURE; // early termination because we found a target.
	}

	// Just let the return movement finish.
	return AIInternalMoveToState::update();
}

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
class ExitConditions : public AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const;
	int m_conditionsToConsider; // +0x04 (state +0x24)
	Coord3D m_center; // +0x08
	Real m_radiusSqr; // +0x14
	UnsignedInt m_attackGiveUpFrame; // +0x18 (state +0x38)
};
class AIGuardRetaliateAttackAggressorState : public State
{
public:
	virtual StateReturnType update();
	Object *rva0054582A();
private:
	AIGuardRetaliateMachine *getGuardMachine() { return (AIGuardRetaliateMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	ExitConditions m_exitConditions; // +0x20
	State *m_attackState; // +0x3C
	ObjectID m_bfme40; // +0x40
};

//--------------------------------------------------------------------------------------
Object *AIGuardRetaliateAttackAggressorState::rva0054582A()
{
	if (m_bfme40 == INVALID_ID)
		return NULL;
	Object *source = TheGameLogic->findObjectByID(m_bfme40);
	if (source == NULL)
		return NULL;
	Object *owner = getMachineOwner();
	Rva00545355Module *module = source->getBfme250();
	if (module == NULL)
		return NULL;
	Rva00545355Target *controller = module->bfmeTarget();
	if (controller)
		return controller->bfmePick(0, owner->getPosition(), 0.0f, 0, 0);
	return NULL;
}

//--------------------------------------------------------------------------------------
StateReturnType AIGuardRetaliateAttackAggressorState::update( void )
{
	AIGuardRetaliateMachine *machine = getGuardMachine();
	Object *nemesis = TheGameLogic->findObjectByID(machine->getNemesisID());
	if (nemesis && nemesis->testBfme438Bit0())
		nemesis = NULL;
	Object *goal = machine->getGoalObject();
	if (goal && goal->testBfme438Bit0())
		goal = NULL;
	Object *owner = getMachineOwner();
	if (goal == NULL)
	{
		if (nemesis == NULL)
		{
			nemesis = rva0054582A();
			if (nemesis == NULL)
				return STATE_SUCCESS;
		}
		owner->getAI()->friend_setGoalObject(nemesis);
		getGuardMachine()->setNemesisID(nemesis->getID());
		getMachine()->setGoalObject(nemesis);
	}
	AttackExitConditionsInterface *conditions = &m_exitConditions;
	if (conditions->shouldExit(getMachine()))
		return STATE_SUCCESS;
	if (m_attackState == NULL)
		return STATE_SUCCESS;

	Bool extend = owner->testStatus(OBJECT_STATUS_BFME_1C);
	Rva00545355Module *module = owner->getBfme250();
	if (module)
	{
		Rva00545355Target *controller = module->bfmeTarget();
		if (controller && nemesis)
		{
			if (controller->bfmeIsTarget(nemesis))
				extend = true;
			int reportedID = controller->bfmeTargetID(nemesis->getID());
			if (reportedID == nemesis->getID())
				extend = true;
		}
	}
	if (extend)
	{
		UnsignedInt giveUp = TheGameLogic->getFrame() + 4*LOGICFRAMES_PER_SECOND;
		if (m_exitConditions.m_attackGiveUpFrame < giveUp)
			m_exitConditions.m_attackGiveUpFrame = giveUp;
	}
	return m_attackState->update();
}
