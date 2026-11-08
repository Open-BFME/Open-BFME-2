// ?onEnter@AIAttackMeleeApproachState@@UAE?AW4StateReturnType@@XZ
// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?onEnter@AIAttackMeleeApproachState@@UAE?AW4StateReturnType@@XZ retail
// 0x0034D5B7 (719 bytes). Slot 4 of vtable 0x00C12800, whose slot-2 name
// getter 0x00342AD0 returns "AIAttackMeleeApproachState" and whose slot 3 is
// the rowed AIAttackMeleeApproachState::xfer 0x0034087C (constructor
// 0x00342A96). Structure follows the WorldBuilder twin 0x00E14360 and the
// sibling melee/approach onEnters in AIAttackApproachTargetStateOnEnter.cpp:
// a destroyed goal fails; a goal the owner's controlling player may not
// attack (Object::rva002943B2) clears the goal and fails; status 0x44 or AI
// byte +0x3CC takes the direct fire/fail exit through AI::rva002FE193 and the
// weapon range test; otherwise CritterDesync 31 clears +0x4C and the adjust
// flag; a crushable goal (Object::rva0029493F 2) with rva0028CECF switches the
// machine to state 0xE9; the physics flag pair (rva00390533) or the
// Rva0034311ECheck victim test fail; in weapon range succeeds; the victim
// position goes to +0x50 and a 2D distance under TheAI data +0x90 plus +0x94
// succeeds (before and after destroyPath); status 0x26 with a container
// fails; then CritterDesync 19 computePath (slot 17) and the
// AIInternalMoveToState onEnter with CritterDesync 32 restoring the flag.

#include "Coord3D.h"

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
enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26,
	OBJECT_STATUS_44 = 0x44
};

class Object;
class Player;

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
// This is the game append helper at RVA 0x002CEC42, not CRT stdio.
// Share the existing provider's opaque parameter and void return type.
struct FprintfTarget;
extern "C" void __cdecl fprintf(FprintfTarget *target, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf((FprintfTarget *)log, text);
	}
}

class TAiData
{
public:
	unsigned char m_pad00[0x90];
	// Target performs this read before +0x94 after length() in both checks.
	// The volatile access view enforces that observed order; it is not a
	// claim that the donor declared its storage volatile.
	volatile Real m_meleeApproachTolerance; // +0x90
	Real m_meleeApproachDist; // +0x94
};

#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../Common/Thing/thing.h"

#include "../../../Include/GameLogic/Weapon.h"

class Object : public Thing
{
public:
	Bool rva0028CECF();	// 0x0028CECF owner test (rowed ?rva0028CECF@Object@@QAE_NXZ)
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	Player *getControllingPlayer() const;
	Bool rva0029493F(Object *other, Int test);
	Bool rva002943B2(const Player *player);
	unsigned char m_pad060[0x258 - 0x60];
	AIUpdateInterface *m_ai; // +0x258
	void *m_physics; // +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy; // +0x274
};


// Physics flag-pair check (0x00390533), pinned under this name.
class Rva00390533
{
public:
	Bool rva00390533();
};

Bool Rva0034311ECheck(Object *obj);

static __forceinline void coordSet(Coord3D *dest, const Coord3D *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

static __forceinline void coordSub(Coord3D *dest, const Coord3D *src)
{
	dest->x -= src->x;
	dest->y -= src->y;
	dest->z -= src->z;
}

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
	virtual StateReturnType setState(Int newStateID);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Bool isGoalObjectDestroyed() const;
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
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObjectRV() const { return ((TurretStateMachine *)m_machine)->getGoalObject(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	void setAdjustsDestination(Bool adjusts) { m_adjustsDestination = adjusts; }
	unsigned char m_pad1C[0x48 - 0x1C];
	Bool m_adjustsDestination; // +0x48
	Bool m_waitingForPath; // +0x49
};

struct MeleeCoordCopy:Coord3D{__forceinline MeleeCoordCopy(float X,float Y,float Z){x=X;y=Y;z=Z;}__forceinline MeleeCoordCopy(const Coord3D&p){x=p.x;y=p.y;z=p.z;} __forceinline void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}};
class AIAttackMeleeApproachState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	__forceinline Bool isCloseToVictim(const Object*source)const{MeleeCoordCopy raw(*source->getPosition());raw.sub(&m_50);float dx=raw.x,dy=raw.y;const TAiData*data=TheAI->getAiData();MeleeCoordCopy delta(dx,dy,0.0f);return delta.length()<data->m_meleeApproachTolerance+data->m_meleeApproachDist;}
	Int m_4C; // +0x4C
	Coord3D m_50; // +0x50
	Int m_5C; // +0x5C
	Int m_60; // +0x60
};

// ?onEnter@AIAttackMeleeApproachState@@UAE?AW4StateReturnType@@XZ @ 0x0034D5B7
StateReturnType AIAttackMeleeApproachState::onEnter()
{
	Object *source = getMachineOwner();
	if (getMachine()->isGoalObjectDestroyed())
		return STATE_FAILURE;

	Object *victim = getMachineGoalObjectRV();
	if (victim && victim->rva002943B2(source->getControllingPlayer()))
	{
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	if (source->testStatus(OBJECT_STATUS_44) || source->m_ai->m_field3CC)
	{
		if (AI::rva002FE193(source, victim))
		{
			if (source->m_ai->m_field3CC)
			{
				Weapon *weapon = source->getCurrentWeapon();
				if (!weapon || !weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
				{
					getMachine()->setGoalObject(0);
					return STATE_FAILURE;
				}
			}
			return STATE_SUCCESS;
		}
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 31");
	m_4C = 0;
	setAdjustsDestination(false);
	if (!victim)
		return STATE_FAILURE;

	if (source->rva0029493F(victim, 2) && source->rva0028CECF())
	{
		getMachine()->setState(0xE9);
		return STATE_CONTINUE;
	}

	if (victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533())
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (Rva0034311ECheck(victim))
		return STATE_FAILURE;
	if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		return STATE_SUCCESS;

	m_50 = *victim->getPosition();
	if (!source->rva0029493F(victim, 2))
	{
		if (isCloseToVictim(source))
			return STATE_SUCCESS;
	}

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	source->m_ai->destroyPath();
	m_50 = *victim->getPosition();
	if (isCloseToVictim(source))
		return STATE_SUCCESS;

	critterDesyncLog("CritterDesync: ComputePath19");
	if (computePath() == false)
		return STATE_SUCCESS;

	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 32");
	setAdjustsDestination(true);
	return ret;
}
