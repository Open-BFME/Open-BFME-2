// ?rva0036AA74@Rva0036AA74Owner@@QAEHXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /EHsc
//
// ?rva0036AA74@Rva0036AA74Owner@@QAEHXZ @0x0036AA74 315B
// Guard-state onEnter in the AIGuardAttackAggressorState family (same
// +0x20/+0x3C/+0x40 member trio: exit conditions, attack state, restart
// flag): with the restart flag set, clear it and return onEnter(); else
// run the body-module nemesis lookup (owner +0x254 module, vslot 15
// getLastDamageInfo, source id +8) into the machine nemesis id (+0x68),
// resolve it via TheGameLogic (kept in a local), take f as 8.0f over the
// TAiData chase-frames int value, build the give-up frame from f plus the
// current frame via __ftol2 with conditions 6 (expired|nounit), then place
// a 0x50 AIAttackState (rowed ctor, machine, true, true, false, over the
// conditions) and return -1/0 from its onEnter result after pushing the
// goal object through its machine. Reuses the proven AIGuardStates views
// (State, StateMachine slot 0x38 setGoalObject, ExitConditions,
// BodyModuleInterface, DamageInfo, TAiData offsets).

typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt TeamID;
typedef bool Bool;
#define NULL 0

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	STATE_EXIT_CONTINUE = 0
};

typedef UnsignedInt StateID;

struct Coord3D
{
	Real x, y, z;
};

class Object;

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
	unsigned char m_pad18[0x68 - 0x18];
	ObjectID m_nemesisToAttack; // +0x68
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
	int m_conditionsToConsider; // +0x04
	Coord3D m_center; // +0x08
	Real m_radiusSqr; // +0x14
	UnsignedInt m_attackGiveUpFrame; // +0x18
};

class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, bool follow, bool attackingObject, bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	unsigned char m_pad1C[0x50 - 0x1C]; // sizeof(AIAttackState) 0x50 (the operator new size)
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
};

class BodyModuleInterface : public VSlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};

class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	unsigned char m_pad00[0x254];
	BodyModuleInterface *m_body; // +0x254
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

extern GameLogic *TheGameLogic;

struct TAiData
{
	unsigned char m_pad00[0x3C];
	UnsignedInt m_guardChaseUnitFrames; // +0x3C
	UnsignedInt m_guardEnemyScanRate; // +0x40
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};

extern AI *TheAI;

class Rva0036AA74Owner : public State
{
public:
	int rva0036AA74();

private:
	unsigned char m_pad1C[0x20 - 0x1C];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
};

// ?rva0036AA74@Rva0036AA74Owner@@QAEHXZ, retail 0x0036AA74, 315 bytes.
int Rva0036AA74Owner::rva0036AA74()
{
	if (m_bfmeRestart) {
		m_bfmeRestart = false;
		return onEnter();
	}
	GameLogic *logic;
	Object *ownerObj = m_machine->getOwner();
	if (ownerObj->getBodyModule() != NULL && ownerObj->getBodyModule()->getLastDamageInfo()->in.m_sourceID)
		((AIGuardMachine *)m_machine)->m_nemesisToAttack = ownerObj->getBodyModule()->getLastDamageInfo()->in.m_sourceID;
	logic = TheGameLogic;
	Object *obj = logic->findObjectByID(((AIGuardMachine *)m_machine)->m_nemesisToAttack);
	if (obj == NULL)
		return -1;
	float f = (8.0f > (float)*(volatile UnsignedInt *)&TheAI->m_aiData->m_guardChaseUnitFrames) ? 8.0f : (float)*(volatile UnsignedInt *)&TheAI->m_aiData->m_guardChaseUnitFrames;
	m_exitConditions.m_attackGiveUpFrame = (int)(f + (float)logic->getFrame());
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | ExitConditions::ATTACK_ExitIfNoUnitFound);
	m_attackState = new AIAttackState(m_machine, true, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(obj);
	return m_attackState->onEnter() ? -1 : 0;
}
