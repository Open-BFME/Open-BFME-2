// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?updateInternal@AIAttackFireDuringApproachState@@AAE?AW4StateReturnType@@XZ
// retail 0x0035066B (597 bytes). The update slot of vtable 0x00C12798
// (AIAttackFireDuringApproachState; slot 4 is the rowed onEnter 0x0034D4A2)
// is 0x003508C0, a five-byte jmp here; the WorldBuilder twin of that slot
// (0x00E13C60) calls this body (twin 0x00E13700) and returns its result, so
// this returns StateReturnType (-2/-1/0 in EAX on every path), like Zero
// Hour's private updateInternal behind AIAttackApproachTargetState::update.
// Evidence (target): the victim is refound by the ID at +0x64 (else the goal
// object, else notifyVictimIsDead slot 144 and setCurrentVictim(0) fail); a
// 2D facing test (getUnitDirectionVector2D against the goal offset); status
// 0x1C within twice the radius +0xB8 (rva00263763) drops the path; the
// weapon status drives the fire flag +0x68 (fire inside radius squared via
// rva00262B0F rva0028FC8F fireCurrentWeapon; else preFireCurrentWeapon with
// status 0x0D); status 0x1C clears; status 0x33 or rva002943B2 fail; in range
// without a path succeeds; CritterDesync 17 computePath (slot 17) then
// AIInternalMoveToState::update (0x00347460) and the success retarget.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum WeaponStatus
{
	READY_TO_FIRE = 0,
	PRE_ATTACK = 4,
	WEAPON_STATUS_5 = 5
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0D = 0x0D,
	OBJECT_STATUS_1C = 0x1C,
	OBJECT_STATUS_33 = 0x33
};

class Player;

extern GameLogic *TheGameLogic;
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

static __forceinline void coordSet(Coord3D *a, const Coord3D *b)
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

static __forceinline void coordSub(Coord3D *a, const Coord3D *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AIUpdateInterface : public AIUpdateSlots<144>
{
public:
	virtual void notifyVictimIsDead() = 0;
	void setCurrentVictim(const Object *victim);
	void destroyPath();
	void rva00262B0F(int obj);
	void *getPath() const { return m_path; }
private:
	unsigned char m_pad004[0x140 - 0x04];
	void *m_path; // +0x140
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	const Coord3D *getUnitDirectionVector2D() const;
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *player);
	Real rva00263763(const void *other) const;
	void rva0028FC8F();
	void fireCurrentWeapon(Object *target, Int victimID);
	void preFireCurrentWeapon(const Object *victim, const Coord3D *pos);
	AIUpdateInterface *getAI() { return m_ai; }
	ObjectID getID() const { return (ObjectID)m_id; }
	Real getRadius() const { return m_radius; }
private:
	unsigned char m_pad044[0x74 - 0x44];
	Int m_id; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	Real m_radius; // +0xB8
	unsigned char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	virtual void slot00();
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
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};

// StateMachine::getGoalObject (0x004D7726), rowed under this name.
class TurretStateMachine
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
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void slot05();
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
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineGoalObject() const { return ((TurretStateMachine *)m_machine)->getGoalObject(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x4C - 0x1C];
};

class AIAttackFireDuringApproachState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();
	unsigned int m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	ObjectID m_victimID; // +0x64
	Bool m_firing; // +0x68
};

// ?updateInternal@AIAttackFireDuringApproachState@@AAE?AW4StateReturnType@@XZ @ 0x0035066B
StateReturnType AIAttackFireDuringApproachState::updateInternal()
{
	StateMachine *machine = getMachine();
	Object *source = machine->getOwner();
	AIUpdateInterface *ai = source->getAI();

	Object *victim = TheGameLogic->findObjectByID(m_victimID);
	Object *foundVictim = victim;
	if (victim == 0)
	{
		victim = ((TurretStateMachine *)machine)->getGoalObject();
		if (victim == 0)
		{
			ai->notifyVictimIsDead();
			ai->setCurrentVictim(0);
			return STATE_FAILURE;
		}
		m_victimID = victim->getID();
	}

	Object *goal = getMachineGoalObject();
	WeaponSlotType slot;
	Weapon *weapon = source->getCurrentWeapon(&slot);
	if (weapon == 0)
		return STATE_FAILURE;

	Bool facing = false;
	if (goal && goal != foundVictim)
	{
		Coord3D dir;
		coordSet(&dir, source->getUnitDirectionVector2D());
		Coord3D toGoal;
		coordSet(&toGoal, goal->getPosition());
		coordSub(&toGoal, source->getPosition());
		Real dot = dir.x * toGoal.x + dir.y * toGoal.y;
		if (dot > 0.0f)
			facing = true;
	}

	if (source->testStatus(OBJECT_STATUS_1C) && foundVictim)
	{
		Real radius = source->getRadius();
		if (source->rva00263763(foundVictim) < radius + radius)
			ai->destroyPath();
	}

	WeaponStatus status = weapon->getStatus();
	if (m_firing)
	{
		if (status == PRE_ATTACK)
		{
		}
		else if (status == READY_TO_FIRE && facing)
		{
			if (goal == foundVictim)
			{
				m_firing = false;
			}
			else
			{
				Real radius = source->getRadius();
				if (source->rva00263763(goal) < radius * radius)
				{
					ai->rva00262B0F((int)victim);
					source->rva0028FC8F();
					source->fireCurrentWeapon(goal, m_victimID);
				}
				else
				{
					m_firing = false;
				}
			}
		}
		else if (status == WEAPON_STATUS_5)
		{
			m_firing = false;
		}
	}
	else if (status == READY_TO_FIRE && goal != victim && facing)
	{
		m_firing = true;
		source->setStatus(OBJECT_STATUS_0D, true);
		source->preFireCurrentWeapon(goal, 0);
	}
	source->setStatus(OBJECT_STATUS_1C, false);

	if (victim->testStatus(OBJECT_STATUS_33))
		return STATE_FAILURE;
	if (victim->rva002943B2(source->getControllingPlayer()))
		return STATE_FAILURE;
	ai->setCurrentVictim(victim);
	if (ai->getPath() == 0 && weapon->isWithinAttackRange(source, victim, 0.0f, 1))
		return STATE_SUCCESS;

	critterDesyncLog("CritterDesync: ComputePath17");
	if (computePath() == false)
		return STATE_FAILURE;

	StateReturnType code = AIInternalMoveToState::update();
	if (code != STATE_CONTINUE)
	{
		if (code == STATE_SUCCESS && foundVictim)
		{
			getMachine()->setGoalObject(foundVictim);
			ai->rva00262B0F((int)foundVictim);
		}
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
