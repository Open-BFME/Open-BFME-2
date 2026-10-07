// ?update@AIAttackMeleeSquishState@@UAE?AW4StateReturnType@@XZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// AIAttackMeleeSquishState::update, retail 0x0034D98B (629 bytes): slot 6 of
// the AIAttackMeleeSquishState vtable 0x00C12868 (rowed onExit 0x003497C7 in
// slot 5, constructor 0x00342AD6, xfer 0x00340A92). BFME 2 only; there is no
// Zero Hour or Open-BFME-1 donor, so the body is read from retail. Fields
// after AIInternalMoveToState (0x4C bytes) follow the rowed xfer; +0x64 is the
// re-acquire flag.
//
// Each update sets the AI path extra distance to 50, then:
//  - an owner in a contain (not the rowed 0x0028CECF case) whose slot-31
//    interface accepts the goal (slot 85) stops (AI slot 136) and succeeds;
//  - a destroyed, dead or status-0x32 goal clears the extra distance and,
//    once per flag, re-acquires the closest enemy within the AI data's
//    +0x94 range (qualifier 2, the AI's attack info) that passes the pinned
//    0x0029493F check ("ComputePath23"), then runs the base update;
//  - otherwise the goal must pass the 0x0029493F check (else success) and
//    must not have status 0x33 or pass the rowed Object::rva002943B2 for the
//    owner's player (else failure). It becomes the victim, the path is
//    recomputed ("ComputePath24") and the base update runs. When it stops,
//    an owner whose template has kind byte +0x11A bit 7 chases a live goal
//    to its position ("ComputePath25"), raising status 0x1C and re-entering
//    the base state. A continuing move mirrors the 0x0028CECF result into
//    status 0x1C.

typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_1C = 0x1C,
	OBJECT_STATUS_BFME_32 = 0x32,
	OBJECT_STATUS_BFME_33 = 0x33
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

template <int N> class AISquishSlots : public AISquishSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AISquishSlots<0>
{
};

class Object;
class Player;
class AttackPriorityInfo;
class PartitionFilter;

class AIUpdateInterface : public AISquishSlots<136>
{
public:
	virtual void setLocomotorGoalNone() = 0; // slot 136

	void setPathExtraDistance(Real dist);
	void destroyPath();
	void setCurrentVictim(const Object *victim);
	const AttackPriorityInfo *getAttackInfo() const { return m_attackInfo; }
private:
	unsigned char m_pad004[0x70 - 0x04];
	const AttackPriorityInfo *m_attackInfo; // +0x70
};

// The contain's slot-31 interface; slot 85 accepts the goal.
class AISquishContainTarget : public AISquishSlots<85>
{
public:
	virtual Bool slot85(Object *goal) = 0;
};

class ContainModuleInterface : public AISquishSlots<31>
{
public:
	virtual AISquishContainTarget *slot31() = 0;
};

class ThingTemplate
{
public:
	Bool testKind11A() const { return (m_kind11A & 0x80) != 0; }
private:
	unsigned char m_pad000[0x11A];
	unsigned char m_kind11A; // +0x11A
};

// Pinned owner checks, named after their addresses.
class Rva0028CECFOwner
{
public:
	Bool rva0028CECF();
};

class Rva0029493F
{
public:
	Bool rva0029493F(int target, int mode);
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *player);

	Bool rva0028CECF() { return ((Rva0028CECFOwner *)this)->rva0028CECF(); }
	Bool rva0029493F(Object *target, int mode) { return ((Rva0029493F *)this)->rva0029493F((int)target, mode); }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x250 - 0x44];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus; // +0x438 (bit 0: effectively dead)
};

struct TAiData
{
	unsigned char m_pad00[0x94];
	Real m_bfmeRange94; // +0x94
};

class AI
{
public:
	Object *findClosestEnemy(const Object *me, Real range, unsigned int qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int bfmeArg);
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};

extern AI *TheAI;

// The rowed goal test (Zero Hour's StateMachine::isGoalObjectDestroyed) is
// named under the turret machine.
class TurretStateMachine
{
public:
	Bool rva004D7ADD();
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj); // slot 14

	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	Bool isGoalObjectDestroyed() { return ((TurretStateMachine *)this)->rva004D7ADD(); }
private:
	unsigned char m_pad04[0x14 - 0x04];
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
	virtual void slot05();
	virtual StateReturnType update();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
protected:
	virtual Bool computePath(); // slot 17
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
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x4C - 0x2C];
};

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad4C[0x64 - 0x4C];
	Bool m_bfmeFlag64; // +0x64
};

StateReturnType AIAttackMeleeSquishState::update()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	ai->setPathExtraDistance(50.0f);
	Object *goal = getMachine()->getGoalObject();

	if (owner->getContain() && !owner->rva0028CECF())
	{
		AISquishContainTarget *target = owner->getContain()->slot31();
		if (target && target->slot85(goal))
		{
			ai->setLocomotorGoalNone();
			return STATE_SUCCESS;
		}
	}

	if (getMachine()->isGoalObjectDestroyed() ||
		(goal && (goal->isEffectivelyDead() || goal->testStatus(OBJECT_STATUS_BFME_32))))
	{
		ai->setPathExtraDistance(0.0f);
		if (m_bfmeFlag64 && owner->rva0028CECF())
		{
			m_bfmeFlag64 = false;
			Object *victim = TheAI->findClosestEnemy(owner, TheAI->getAiData()->m_bfmeRange94, 2,
				ai->getAttackInfo(), 0, 0);
			if (victim && owner->rva0029493F(victim, 2))
			{
				getMachine()->setGoalObject(victim);
				critterDesyncLog("CritterDesync: ComputePath23");
				if (!computePath())
					return STATE_FAILURE;
				m_bfmeFlag64 = true;
			}
		}
		return AIInternalMoveToState::update();
	}

	StateReturnType ret = STATE_FAILURE;
	if (goal)
	{
		if (!owner->rva0029493F(goal, 2))
			return STATE_SUCCESS;
		if (goal->testStatus(OBJECT_STATUS_BFME_33) || goal->rva002943B2(owner->getControllingPlayer()))
			return STATE_FAILURE;
		ai->setCurrentVictim(goal);
		critterDesyncLog("CritterDesync: ComputePath24");
		if (!computePath())
			return STATE_FAILURE;
		ret = AIInternalMoveToState::update();
		if (ret != STATE_CONTINUE)
		{
			if (!goal->isEffectivelyDead() && owner->getTemplate()->testKind11A())
			{
				m_goalPosition = *goal->getPosition();
				owner->getAI()->destroyPath();
				critterDesyncLog("CritterDesync: ComputePath25");
				if (computePath())
				{
					owner->setStatus(OBJECT_STATUS_BFME_1C, true);
					return AIInternalMoveToState::onEnter();
				}
			}
			return STATE_SUCCESS;
		}
	}
	Bool contained = owner->rva0028CECF();
	owner->setStatus(OBJECT_STATUS_BFME_1C, contained);
	return ret;
}
