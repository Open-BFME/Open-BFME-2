// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// AIIdleState::update and its private doInitIdleState, BFME 2 versions of
// Zero Hour's AIStates.cpp bodies. The class is the ledger's Rva0033FE65
// (constructor 0x0033FE65, onEnter 0x00346FD0); its vtable 0x00811E08 names
// it through the slot-2 getter 0x0033FE9D ("AIIdleState"). Layout from that
// constructor: m_initialSleepOffset +0x20, a countdown +0x22,
// m_shouldLookForTargets +0x24 and m_inited +0x25.
//
//  - AIIdleState::doInitIdleState, retail 0x0034405D (219 bytes; called
//    first by update, as in Zero Hour). Runs once per m_inited. The goal snap
//    needs the AI idle and doing ground movement (AI slots 110 and 137); an
//    object with status 0x26 also needs its container's AI idle. A non-zero
//    position goes to the pinned Object::rva0028ACEE with the rowed layer
//    getter rva0028B511. Then AI slot 136 (setLocomotorGoalNone) and the
//    rowed setCurrentVictim(NULL).
//  - AIIdleState::update, retail 0x0035389E (455 bytes; slot 6). BFME 2
//    additions run before Zero Hour's body:
//      - A current weapon whose rowed rva002C9586 frame-window check holds
//        keeps the state.
//      - Unless status 0x3A or AI +0x34 is set, every fifth update fails
//        the state when the owner has its StancesBehavior module (rowed key
//        0x0045EE2C) and the machine has state 0x4E (rowed hasState).
//    The sleep base is the per-TU initializer global g_00E01E04 (two
//    seconds of logic frames). While looking for targets:
//      - status 0x49 hunts (rowed aiHunt);
//      - status 0x26 with the weapon template byte +0x125 set just waits;
//      - then the Zero Hour repulsor, crate and mood-target checks.
//    BFME 2 tests disabled types 2, 4 and 8 and marks AI +0x3C7 after the
//    mood attack.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_26 = 0x26,
	OBJECT_STATUS_BFME_3A = 0x3A,
	OBJECT_STATUS_BFME_49 = 0x49
};

enum DisabledType
{
	DISABLED_BFME_2 = 2,
	DISABLED_BFME_4 = 4,
	DISABLED_BFME_8 = 8
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum MoodMatrixAction
{
	MM_Action_Idle = 0
};

enum
{
	MAA_Affect_Range_IgnoreAll = 0x10
};

enum
{
	NO_MAX_SHOTS_LIMIT = 0x7fffffff
};

enum
{
	AI_MOVE_AWAY_FROM_REPULSORS = 0x28,
	AI_BFME_STATE_4E = 0x4E
};

// The StancesBehavior module key (rowed 0x0045EE2C).
NameKeyType Rva0045EE2CGet();

class Module;

// Weapon template view: the rowed byte getter reads +0x125.
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	Bool rva002C9586();
	const Rva002C9400ByteField *getTemplate() const { return m_template; }
private:
	unsigned char m_pad00[0x04];
	const Rva002C9400ByteField *m_template; // +0x04
};

template <int N> class AIIdleAISlots : public AIIdleAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIIdleAISlots<0>
{
};

class Object;

class AICommandInterface
{
public:
	void aiHunt(CommandSourceType cmdSource);
	void aiMoveToObject(Object *obj, CommandSourceType cmdSource);
	void rva0026C2D9(Object *victim, int maxShotsToFire, CommandSourceType cmdSource);
};

class AIUpdateInterface : public AIIdleAISlots<110>
{
public:
	virtual Bool isIdle() const = 0; // slot 110
	virtual void slot111() = 0; virtual void slot112() = 0; virtual void slot113() = 0;
	virtual void slot114() = 0; virtual void slot115() = 0; virtual void slot116() = 0;
	virtual void slot117() = 0; virtual void slot118() = 0; virtual void slot119() = 0;
	virtual void slot120() = 0; virtual void slot121() = 0; virtual void slot122() = 0;
	virtual void slot123() = 0; virtual void slot124() = 0; virtual void slot125() = 0;
	virtual void slot126() = 0; virtual void slot127() = 0; virtual void slot128() = 0;
	virtual void slot129() = 0; virtual void slot130() = 0; virtual void slot131() = 0;
	virtual void slot132() = 0; virtual void slot133() = 0; virtual void slot134() = 0;
	virtual void slot135() = 0;
	virtual void setLocomotorGoalNone() = 0; // slot 136
	virtual Bool isDoingGroundMovement() const = 0; // slot 137

	Object *checkForCrateToPickup();
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void setCurrentVictim(const Object *victim);

	void aiHunt(CommandSourceType cmdSource) { m_commands.aiHunt(cmdSource); }
	void aiMoveToObject(Object *obj, CommandSourceType cmdSource) { m_commands.aiMoveToObject(obj, cmdSource); }
	void aiAttackObject(Object *victim, int maxShotsToFire, CommandSourceType cmdSource)
	{
		m_commands.rva0026C2D9(victim, maxShotsToFire, cmdSource);
	}
	int getBfme34() const { return m_bfme34; }
	UnsignedInt getNextMoodCheckTime() const { return m_nextMoodCheckTime; }
	void setBfmeFlag3C7(Bool b) { m_bfmeFlag3C7 = b; }

private:
	unsigned char m_pad004[0x20 - 0x04];
	AICommandInterface m_commands; // +0x20
	unsigned char m_pad021[0x34 - 0x21];
	int m_bfme34; // +0x34
	unsigned char m_pad038[0x21C - 0x38];
	UnsignedInt m_nextMoodCheckTime; // +0x21C
	unsigned char m_pad220[0x3C7 - 0x220];
	Bool m_bfmeFlag3C7; // +0x3C7
};

class ThingTemplate
{
public:
	Bool testBfmeKind10D() const { return (m_bfmeKind10D & 0x20) != 0; }
private:
	unsigned char m_pad000[0x10D];
	unsigned char m_bfmeKind10D; // +0x10D
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	Bool isDisabledByType(DisabledType type) const { return (m_disabledMask & (1U << type)) != 0; }
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
	Bool testStatus(ObjectStatusTypes bit) const;
	Module *findModule(NameKeyType key) const;
	Real getVisionRange() const;
	int rva0028B511() const;
	void rva0028ACEE(const Coord3D *pos, int layer);
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x1C8 - 0x44];
	UnsignedInt m_disabledMask; // +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
};

class AI
{
public:
	Object *findClosestRepulsor(const Object *obj, Real range);
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_00E01E04;

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(int newStateID); // slot 8
	Object *getOwner() const { return m_owner; }
	Bool isLocked() const { return m_locked; }
	Bool hasState(int id);
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x38 - 0x18];
	Bool m_locked; // +0x38
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
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
private:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

class AIIdleState : public State
{
public:
	virtual StateReturnType update();
private:
	void doInitIdleState();

	UnsignedShort m_initialSleepOffset; // +0x20
	UnsignedShort m_stancesCountdown; // +0x22
	Bool m_shouldLookForTargets; // +0x24
	Bool m_inited; // +0x25
};

void AIIdleState::doInitIdleState()
{
	if (!m_inited)
		return;

	m_inited = false;

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	Bool containerIdle = true;
	if (obj->testStatus(OBJECT_STATUS_BFME_26))
	{
		containerIdle = false;
		Object *container = obj->getContainedBy();
		if (container && container->getAI())
			containerIdle = container->getAI()->isIdle();
	}
	if (ai->isIdle() && ai->isDoingGroundMovement() && containerIdle)
	{
		Coord3D goalPos;
		goalPos.x = obj->getPosition()->x;
		goalPos.y = obj->getPosition()->y;
		goalPos.z = obj->getPosition()->z;
		if (goalPos.x || goalPos.y || goalPos.z)
			obj->rva0028ACEE(&goalPos, obj->rva0028B511());
	}

	ai->setLocomotorGoalNone();
	ai->setCurrentVictim(0);
}
