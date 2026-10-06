// ?update@AIEnterState@@UAE?AW4StateReturnType@@XZ
// partial score=0.8337 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE
//
// ?update@AIEnterState@@UAE?AW4StateReturnType@@XZ @0x0035455A 419B: slot 6 of
// vtable 0x00812E90 (class of ??0Rva00342EAC ctor). Ported from BFME1
// GameEngine/Source/GameLogic/AI/AIStates.cpp AIEnterState::update and Zero
// Hour GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp with BFME2
// target evidence: goal-contained at +0x274, contain at +0x250, AI at +0x258,
// goal position +0x38, radius +0xB8, held bit 8 at +0x1C8, goalPosition +0x20,
// frame at +0x50 vs TheGameLogic+0x40, base AIInternalMoveToState::update
// 0x00347460, TurretStateMachine::getGoalObject 0x004D7726, isAboveTerrain
// 0x000B19E5, rva00262B0F 0x00262B0F, canEnter 0x0041C2D0, getRelationship
// 0x0028D156, getCanAttack 0x0041C6CF, rva0026C2D9 0x0026C2D9. Caller
// AITNGuardReturnState::update 0x00545C9E chains to this base update.
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
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
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class Thing
{
public:
	bool isAboveTerrain() const;
};
class AIUpdateInterface;
class GoalContain;
class Object
{
public:
	Relationship getRelationship(const Object *other) const;
	AIUpdateInterface *getAI() const { return m_ai; }
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0xB8 - 0x44];
	float m_radius; // +0xB8
	unsigned char m_padBC[0x1C8 - 0xBC];
	unsigned char m_heldByte; // +0x1C8 bit 3 is HELD
	unsigned char m_pad1C9[0x250 - 0x1C9];
	GoalContain *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
};
class GoalContainBase : public VSlots<39>
{
public:
	virtual void addToContain(Object *obj);
};
class GoalContain : public GoalContainBase
{
public:
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual void pad60();
	virtual void pad61();
	virtual void pad62();
	virtual void pad63();
	virtual void pad64();
	virtual void pad65();
	virtual void pad66();
	virtual void pad67();
	virtual void pad68();
	virtual void pad69();
	virtual void pad70();
	virtual void pad71();
	virtual void pad72();
	virtual void pad73();
	virtual void pad74();
	virtual void pad75();
	virtual void pad76();
	virtual void pad77();
	virtual void pad78();
	virtual void pad79();
	virtual void pad80();
	virtual void pad81();
	virtual void pad82();
	virtual void pad83();
	virtual void pad84();
	virtual void pad85();
	virtual const Coord3D *getContainedObjectPosition();
};
class AIUpdateInterface : public VSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource();
	void rva00262B0F(int val);
};
class AICommandInterface
{
public:
	void rva0026C2D9(Object *victim, int maxShots, CommandSourceType source);
};
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	Object *getOwner() const { return m_owner; }
private:
	Object *m_currentStatePad; // +0x4 (State* in real code)
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
};
class TurretStateMachine : public StateMachine
{
public:
	Object *getGoalObject();
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};
class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	int m_entryToClear; // +0x4C
	unsigned int m_frame50; // +0x50
};
class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class ActionManager
{
public:
	CanAttackResult getCanAttackObject(const Object *obj, const Object *goal, CommandSourceType source, AbleToAttackType type);
};
class BFMEActionManager : public ActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *goal, CommandSourceType source, CanEnterType type, int a, bool *b);
};
extern BFMEActionManager *g_00E030E8;
StateReturnType AIEnterState::update()
{
	Object *obj = m_machine->getOwner();
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goal)
	{
		if (goal->m_containedBy != 0 && ((const Thing *)goal)->isAboveTerrain() && !((const Thing *)obj)->isAboveTerrain())
			return STATE_FAILURE;
		GoalContain *contain = goal->m_contain;
		if (contain)
			m_goalPosition = *contain->getContainedObjectPosition();
		else
			m_goalPosition = goal->m_position;
		obj->getAI()->rva00262B0F((int)goal);
		if (!g_00E030E8->canEnterObject(obj, goal, obj->getAI()->getLastCommandSource(), CHECK_CAPACITY, 0, (bool *)0))
		{
			if (obj->getRelationship(goal) != ENEMIES)
				return STATE_FAILURE;
			AIUpdateInterface *ai2 = obj->getAI();
			if (ai2 == 0)
				return STATE_FAILURE;
			CanAttackResult result = g_00E030E8->getCanAttackObject(obj, goal, obj->getAI()->getLastCommandSource(), ATTACK_NEW_TARGET);
			if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
			{
				AIUpdateInterface *ai3 = obj->getAI();
				AICommandInterface *cmd = (AICommandInterface *)((char *)ai3 + 0x20);
				cmd->rva0026C2D9(goal, 0x7fffffff, ai3->getLastCommandSource());
				return STATE_CONTINUE;
			}
			return STATE_FAILURE;
		}
		Object *machineOwner = m_machine->getOwner();
		if ((machineOwner->m_heldByte & 8) != 0)
			return STATE_SUCCESS;
	}
	else
	{
		return STATE_FAILURE;
	}
	StateReturnType code = AIInternalMoveToState::update();
	if (code == STATE_CONTINUE)
		return code;
	GoalContain *contain2 = goal->m_contain;
	if (contain2 == 0)
		return code;
	const Coord3D *goalPos = contain2->getContainedObjectPosition();
	float dy = obj->m_position.y - goalPos->y;
	float dx = obj->m_position.x - goalPos->x;
	float radius = goal->m_radius;
	float distSq = dx * dx + dy * dy;
	float radSq = radius * radius;
	if (radSq > distSq || TheGameLogic->m_frame > m_frame50)
	{
		contain2->addToContain(obj);
		code = STATE_SUCCESS;
	}
	return code;
}
