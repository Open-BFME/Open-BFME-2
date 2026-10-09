// ?onEnter@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AIAttackApproachTargetState::onEnter, retail 0x0034CD3A (783 bytes): slot 4
// of vtable 0x00C12610 (slot-2 name getter "AIAttackApproachTargetState";
// slots 5/6 are the rowed onExit 0x0034894C and update 0x003488AF), with the
// AIStates.cpp helpers it calls:
//
//  - rva003430A3 0x003430A3 (123 bytes): the attack line-of-sight test. True
//    unless the owner's template has kind byte +0x10F mask 8 or byte +0x122
//    mask 0x40, the weapon's template is neither the +0x2C9400 byte-field
//    kind nor a contact weapon (pinned WeaponTemplate::isContactWeapon), and
//    the stack line-of-sight partition filter (vtable 0x00C07150, rowed
//    Rva002619C1Filter::allow) refuses the victim. Also called outside this
//    unit (0x0046C7A4), so it is external cdecl.
//  - rva00343FB0 0x00343FB0 (173 bytes): static, owner in ESI. False for an
//    immobile owner (kind byte +0x108 mask 4) or one whose outermost
//    container is; otherwise BFME1's rva0016B010 (contact/field weapon,
//    non-human player, no AI, state 0x3E, AI slot 143 != 2, AI byte +0x3C1,
//    owner byte +0x249). Not yet exact (forward pin in symbols.csv): retail
//    walks the containers with a retested loop (while (c && c->next)) yet
//    keeps the owner in ESI; every retested-loop shape tried here makes cl
//    choose EDI, which also moves onEnter's registers. The break-loop shape
//    below keeps the retail ESI convention (onEnter exact) but drops the
//    retest; bank reverse/attempts/0x00343fb0.cpp has the retail-shaped body.
//  - canPursue 0x00344635 (276 bytes): static, owner in ESI, victim in EDI,
//    weapon on the stack; Zero Hour's canPursue as BFME1 shaped it (status
//    0x26 with a container, crush test, weapon too-close test 0x002C9AFE,
//    locomotor speed 0x002627E8 against the victim's 0x0028AC7D).
//
// onEnter is Zero Hour's with BFME 2 target facts: the owner position is
// saved at +0x58; a destroyed goal fails; status 0x44 or AI byte +0x3CC
// takes a direct fire/fail exit through AI::rva002FE193 and the
// line-of-sight test (else the machine's slot 14 clears the goal); a victim
// rowed Rva0034311ECheck fails; the view-blocked test is rva003430A3;
// the guard-retaliate block is rva00343FB0; an AI module flag +0x24 with
// layer >= 17 and no quick path, or a non-moving owner (Object::rva002907A1,
// locomotor 0x001E46E1 speed < 0.1), waits two seconds (+0x68, flag +0x71).
// Donors: Zero Hour AIStates.cpp, BFME1 AIAttackApproachTargetState_onEnter.cpp.
//
// AIAttackApproachTargetState00C12678::onEnter 0x0034D049 (383 bytes, slot 4
// of vtable 0x00C12678): the same body for the BFME 2 position-approach
// variant -- no victim branch, the weapon range test against the machine's
// goal position, owner position at +0x4C, timestamp +0x58, wait frame +0x5C
// and wait flag +0x62; its computePath 0x00340546 (221 bytes, slot 17,
// ComputePath10/20) is the goal-position half of Zero Hour's with the waiting
// byte refreshed from the AI after requestAttackPath. The goal pointer is read
// before the timestamp store
// (retail keeps the negated frame rate in ECX across the argument pushes).
//
// AIAttackPursueTargetState (vtable 0x00C12730): onEnter 0x0034D345 (349
// bytes, slot 4) and computePath 0x00345246 (333 bytes, slot 17), Zero Hour's
// bodies with BFME 2's status 0x44 / AI byte +0x3CC direct exit (as in the
// approach onEnter), the AI slot 143 == 2 command-source test with owner byte
// +0x249, CritterDesync 27/13 and 12/26, the AI blocked-frames count +0x16C,
// path +0x140 and waiting byte +0x3B1, and the static isSamePosition and
// canPursue register helpers of this unit.
//
// AIAttackFireDuringApproachState (vtable 0x00C12798, BFME only; layout from
// the rowed xfer 0x0034081A): onEnter 0x0034D4A2 (277 bytes, CritterDesync
// 28/16/29) remembers the victim ID +0x64 and its position +0x50 and fails on
// the victim physics flag pair (pinned 0x00390533); computePath 0x00350497
// (468 bytes, ComputePath15) refinds the victim by ID, then asks the
// pathfinder's engagement-spot search (pinned 0x002F23A6) and
// requestApproachPath, with the 'masiwar' debug traces gated on TheGameLogic
// +0x1B4. The machine pointer is a local there (retail reuses it after
// findObjectByID).
//
// AIAttackMeleeSquishState (vtable 0x00C12868): onEnter 0x0034D886 (261
// bytes, CritterDesync 33/22) needs template byte +0x5FD, no status 0x44 or
// AI +0x3CC, a live goal without the physics flag pair and the owner's crush
// test (Object::rva0029493F, 2) before it paths, then sets status 0x1C. Its
// FAILURE and SUCCESS returns trail the body in that order, which only the
// nested form below reproduces.
//
// AIAttackMeleeEngageState::onEnter 0x0034DC05 (540 bytes, slot 4 of vtable
// 0x00C12150, CritterDesync 35/27/36): BFME1's AIAttackMeleeEngageState_onEnter
// donor with BFME 2's fields -- the private fire state (new, constructor
// 0x0033F483) at +0x4C, timestamp +0x54, victim position +0x58, retry frame
// +0x6C and flag +0x70, weapon slot +0x74; the victim fails on the physics
// flag pair, Object +0x438 bit 0 or status 0x32; in range, the owner's
// pathfinder goal (Object::rva0028ACEE, GetGoalPosition) is written to the AI
// final position +0x180 with byte +0x3B0 cleared and status 0x1C set.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum WhichTurretType
{
	TURRET_INVALID = -1
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum KindOfType
{
	KINDOF_CE = 0xCE
};
enum MoodMatrixAction
{
	MM_Action_Attack = 2
};
enum WeaponStatus
{
	READY_TO_FIRE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0D = 0x0D,
	OBJECT_STATUS_1C = 0x1C,
	OBJECT_STATUS_26 = 0x26,
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_33 = 0x33,
	OBJECT_STATUS_41 = 0x41,
	OBJECT_STATUS_44 = 0x44,
	OBJECT_STATUS_52 = 0x52
};

class Object;
class Weapon;

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

extern const int g_009BA4E4;
#define LOGICFRAMES_PER_SECOND g_009BA4E4

extern GameLogic *TheGameLogic;

class TAiData
{
public:
	unsigned char m_pad00[0x4C];
	Real m_alertRangeModifier; // +0x4C
	Real m_aggressiveRangeModifier; // +0x50
	unsigned char m_pad54[0x8C - 0x54];
	Bool m_aiCrushesInfantry; // +0x8C
};

class Rva002C9B80Owner;

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *obj, const Coord3D *objPos, const Object *target, const Coord3D *targetPos);
	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
};

class AI
{
public:
	static Bool rva002FE193(Object *owner, Object *nemesis);
	Pathfinder *pathfinder() { return m_pathfinder; }
	const TAiData *getAiData() { return m_aiData; }
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

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
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};

// Locomotor speed for an object (0x001E46E1), rowed under this name.
class Rva001E46E1
{
public:
	Real rva001E46E1(Object *obj);
};

// AI current-locomotor speed (0x002627E8), rowed under this name.
class Rva002627E8
{
public:
	Real rva002627E8() const;
};

class AIUpdateModuleData
{
public:
	unsigned char m_pad00[0x20];
	Real m_20; // +0x20
	Bool m_24; // +0x24
};

enum MoodMatrixParameters
{
	MM_Controller_Player = 0x00000001,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200,
	MM_Mood_Normal = 0x00000400,
	MM_Mood_Alert = 0x00000800,
	MM_Mood_Aggressive = 0x00001000,
	MM_Mood_Bitmask = (MM_Mood_Sleep | MM_Mood_Passive | MM_Mood_Normal | MM_Mood_Alert | MM_Mood_Aggressive)
};

template <int N> class AIApproachAISlots : public AIApproachAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIApproachAISlots<0>
{
};

class AIUpdateInterface : public AIApproachAISlots<136>
{
public:
	virtual void slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142() = 0;
	virtual Int slot143() = 0;
	virtual void notifyVictimIsDead() = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	Int rva00260DED() const;
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Bool isQuickPathAvailable(const Coord3D *destination) const;
	Real getCurLocomotorSpeed() const { return ((const Rva002627E8 *)this)->rva002627E8(); }
	void setCurrentVictim(const Object *victim);
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void requestAttackPath(ObjectID victimID, const Coord3D *victimPos);
	void destroyPath();
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void rva00262B0F(Int value);
	Bool isMoving() const;
	void requestApproachPath(Coord3D *destination);
	void *getPath() const { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	Bool isBlockedAndStuck() const { return m_blockedFrames > 0; }
	UnsignedInt getMoodMatrixValue() const;
	Bool isAttackPath() const { return m_3b2; }
private:
	const AIUpdateModuleData *m_moduleData; // +0x04
	unsigned char m_pad008[0x140 - 0x08];
	void *m_path; // +0x140
	unsigned char m_pad144[0x16C - 0x144];
public:
	Int m_blockedFrames; // +0x16C
	unsigned char m_pad170[0x180 - 0x170];
	Coord3D m_finalPosition; // +0x180
	unsigned char m_pad18C[0x1CC - 0x18C];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
private:
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B0 - 0x1F4];
public:
	Bool m_3b0; // +0x3B0
private:
	Bool m_waitingForPath; // +0x3B1
	Bool m_3b2; // +0x3B2
	unsigned char m_pad3B3[0x3C1 - 0x3B3];
public:
	Bool m_3c1; // +0x3C1
	unsigned char m_pad3C2[0x3C7 - 0x3C2];
	Bool m_3c7; // +0x3C7
	unsigned char m_pad3C8[0x3CC - 0x3C8];
	Bool m_3cc; // +0x3CC
};

class ThingTemplate
{
public:
	Bool isKindOfImmobile() const { return (m_kindOf[0] & 4) != 0; }
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 2) != 0; }
	UnsignedInt kindOfWord(Int i) const { return ((const UnsignedInt *)m_kindOf)[i]; }
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[0x14]; // +0x108
	unsigned char m_pad11C[0x122 - 0x11C];
	unsigned char m_122; // +0x122
	unsigned char m_pad123[0x5FD - 0x123];
	Bool m_5fd; // +0x5FD
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const Coord3D *getUnitDirectionVector2D() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class TeamPrototype
{
public:
	unsigned char m_pad00[0x216];
	Bool m_216; // +0x216
};

class Team
{
public:
	Object *getTeamTargetObject();
	void rva0039D84A(Object *target);
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};

class Player
{
public:
	unsigned char m_pad00[0x5C];
	Int m_playerType; // +0x5C
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	Object *getOutermostContainer()
	{
		Object *container = m_containedBy;
		while (container && container->m_containedBy)
			container = container->m_containedBy;
		return container;
	}
	Bool isInImmobileContainer()
	{
		Object *container = getOutermostContainer();
		return container && container->isKindOfImmobile();
	}
	Bool isKindOfImmobile() const { return getTemplate()->isKindOfImmobile(); }
	Bool isKindOfProjectile() const { return getTemplate()->isKindOfProjectile(); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	Player *getControllingPlayer() const;
	Int rva0028B511() const;
	Bool rva002907A1();
	Bool isSignificantlyAboveTerrain() const;
	Bool rva0029493F(Object *other, Int test);
	Real rva0028AC7D() const;
	Bool rva002943B2(const Player *player);
	void rva0028ACDC(const Coord3D *pos);
	void setStatus(ObjectStatusTypes bit, Bool set);
	Bool isKindOf(KindOfType t) const;
	void preFireCurrentWeapon(const Object *victim, const Coord3D *pos);
	void rva0028ACEE(const Coord3D *pos, Int layer);
	Bool GetGoalPosition(Coord3D *pos) const;
	void *rva0029439D();
	ObjectID getID() const { return (ObjectID)m_id; }
	unsigned char m_pad044[0x74 - 0x44];
	Int m_id; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	Real m_geometryRadiusB8; // +0xB8
	unsigned char m_pad0BC[0x249 - 0xBC];
	Bool m_249; // +0x249
	unsigned char m_pad24A[0x258 - 0x24A];
	AIUpdateInterface *m_ai; // +0x258
	void *m_physics; // +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	UnsignedInt m_438; // +0x438
};

Bool rva00344EB2Gate(Object *obj, Thing *other);

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Rva002C9407ByteField
{
public:
	unsigned char get() const;
};
class Rva002C940EByteField
{
public:
	unsigned char get() const;
};

class WeaponTemplate
{
public:
	Bool isContactWeapon() const;
	unsigned char m_pad00[0x16B];
	Bool m_16b; // +0x16B
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;
	char isWithinAttackRange(Object *source, void *pos, Real extra, Int flag) const;
	Bool rva002C9AFE(const Object *source, const void *target) const;
	WeaponStatus getStatus() const;
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};

class Rva002C9B80Owner
{
public:
	Bool isWithinAttackRange(Object *source, const Coord3D *sourcePos, Object *victim, const Coord3D *victimPos, Real extra, Bool flag);
};

// The line-of-sight partition filter (vtable 0x00C07150).
class Rva002619C1FilterBase
{
public:
	Rva002619C1FilterBase() : m_zero(0) {}
	Int m_zero;
};

class Rva002619C1Filter : public Rva002619C1FilterBase
{
public:
	Rva002619C1Filter(Object *owner) : m_owner(owner) {}
	virtual ~Rva002619C1Filter() {}
	virtual Bool allow(Object *other);

	Object *m_owner;
};

template <int N> class StateMachineSlots : public StateMachineSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class StateMachineSlots<0>
{
};

class StateMachine : public StateMachineSlots<14>
{
public:
	virtual void setGoalObject(const Object *obj);
	void setGoalPosition(const Coord3D *pos);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

// StateMachine::isGoalObjectDestroyed (0x004D7ADD), rowed under this name.
class TurretStateMachine
{
public:
	Bool rva004D7ADD();
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
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
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
	Bool m_waitingForPath; // +0x49
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	StateReturnType updateInternal();
	Coord3D m_prevVictimPos; // +0x4C
	Coord3D m_ownerPosition; // +0x58
	Int m_approachTimestamp; // +0x64
	UnsignedInt m_waitFrame; // +0x68
	Bool m_follow; // +0x6C
	Bool m_isAttackingObject; // +0x6D
	Bool m_stopIfInRange; // +0x6E
	Bool m_isInitialApproach; // +0x6F
	Bool m_isForceAttacking; // +0x70
	Bool m_waiting; // +0x71
};

// The BFME 2 approach variant of vtable 0x00C12678 (rowed onExit/update in
// AIAttackApproachTargetStateOnExit.cpp, constructor 0x00342978).
class AIAttackApproachTargetState00C12678 : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	Coord3D m_ownerPosition; // +0x4C
	Int m_approachTimestamp; // +0x58
	UnsignedInt m_waitFrame; // +0x5C
	Bool m_stopIfInRange; // +0x60
	Bool m_isInitialApproach; // +0x61
	Bool m_waiting; // +0x62
};

// AIAttackPursueTargetState, vtable 0x00C12730 (constructor 0x003429B9;
// rowed updateInternal 0x0034939E).
class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	Coord3D m_prevVictimPos; // +0x4C
	UnsignedInt m_approachTimestamp; // +0x58
	Bool m_follow; // +0x5C
	Bool m_isAttackingObject; // +0x5D
	Bool m_stopIfInRange; // +0x5E
	Bool m_isInitialApproach; // +0x5F
	Bool m_isForceAttacking; // +0x60
};

// AIAttackFireDuringApproachState, vtable 0x00C12798 (rowed xfer 0x0034081A).
class AIAttackFireDuringApproachState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	UnsignedInt m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	ObjectID m_victimID; // +0x64
	Bool m_68; // +0x68
};

// The pathfinder's melee engagement-spot search (0x002F23A6), pinned under
// this name.
class Rva002F23A6
{
public:
	Bool rva002F23A6(Object *source, int weapon, int locomotorSet, Coord3D *goalPos,
		Object *victim);
};

// TheGameLogic's BFME debug level (+0x1B4), private padding in the shared
// GameLogic view.
static __forceinline Int gameLogicDebugLevel()
{
	return *(const Int *)((const char *)TheGameLogic + 0x1B4);
}

static __forceinline void debugTrace(const char *text)
{
	void *log = theLogicRandomLogFile;
	if (log != 0)
		fprintf(log, text);
}

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};

// The object behind Object::rva0029439D; its slot 68 yields the object a
// melee squish should really target.
class Rva0029439DView : public VirtualSlots<68>
{
public:
	virtual Object *slot68();
};

// AIAttackMeleeSquishState, vtable 0x00C12868 (rowed xfer 0x00340A92, onExit
// 0x003497C7).
class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	UnsignedInt m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	Bool m_64; // +0x64
};

// AIAttackFireWeaponState, vtable 0x00C111F8.
class AIAttackFireWeaponState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	void *m_att; // +0x1C
	Int m_20; // +0x20
	Bool m_waitOddFrame; // +0x24
};

// The melee engage state's private fire state (constructor 0x0033F483).
class Rva0033F483
{
public:
	Rva0033F483(StateMachine *machine, Int weaponSlot);
	unsigned char m_pad00[0x28];
};

// AIAttackMeleeEngageState, vtable 0x00C12150 (computePath 0x003457AC rowed in
// AIStatesBfmeComputePath.cpp).
class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	Rva0033F483 *m_fireState; // +0x4C
	Int m_50; // +0x50
	UnsignedInt m_approachTimestamp; // +0x54
	Coord3D m_prevVictimPos; // +0x58
	unsigned char m_pad64[0x6C - 0x64];
	UnsignedInt m_retryFrame; // +0x6C
	Bool m_retryPending; // +0x70
	Bool m_noEngagementSpot; // +0x71
	unsigned char m_pad72[0x74 - 0x72];
	Int m_weaponSlot; // +0x74
};

// Physics flag-pair check (0x00390533), pinned under this name.
class Rva00390533
{
public:
	Bool rva00390533();
};

Bool Rva0034311ECheck(Object *obj);

Bool rva003430A3(Object *source, Object *victim, Weapon *weapon)
{
	if (weapon && victim && !((const Rva002C9400ByteField *)weapon->getTemplate())->get() &&
		!weapon->getTemplate()->isContactWeapon() &&
		((source->getTemplate()->m_kindOf[7] & 8) || (source->getTemplate()->m_122 & 0x40)))
	{
		Rva002619C1Filter filter(source);
		if (!filter.allow(victim))
			return false;
	}
	return true;
}

// ?rva00343FB0@@YA_NPAVObject@@@Z present-unmatched
static Bool rva00343FB0(Object *obj)
{
	if (obj->isKindOfImmobile())
		return false;
	Object *container = obj->getContainedBy();
	while (container)
	{
		Object *outer = container->getContainedBy();
		if (!outer)
			break;
		container = outer;
	}
	if (container && container->isKindOfImmobile())
		return false;

	Weapon *weapon = obj->getCurrentWeapon();
	if (weapon && (((const Rva002C9400ByteField *)weapon->getTemplate())->get() ||
			((const Rva002C9407ByteField *)weapon->getTemplate())->get()))
		return true;
	if (obj->getControllingPlayer()->m_playerType)
		return true;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return true;
	if (ai->rva00260DED() == 0x3e || ai->slot143() != 2 || ai->m_3c1 || obj->m_249)
		return true;
	return false;
}

// Rowed at 0x0033FA8E from AIAttackApproachTargetState_computePath_Bfme.cpp;
// VC7.1 passes its three pointers in registers, so callers only match with a
// definition in the same unit.
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

static Bool canPursue(Object *source, Weapon *weapon, Object *victim)
{
	if (!victim->m_physics)
		return false;
	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return false;
	AIUpdateInterface *ai = source->getAI();
	if (!ai)
		return false;

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (source->getControllingPlayer() &&
			source->getControllingPlayer()->m_playerType == 1 &&
			source->rva0029493F(victim, 2))
		{
			return true;
		}
	}

	if (weapon->rva002C9AFE(source, victim))
		return false;

	Real ourMaxSpeed = source->getAI()->getCurLocomotorSpeed();
	Real victimSpeed = victim->rva0028AC7D();
	if (victimSpeed >= ourMaxSpeed)
		return false;
	if (victimSpeed < ourMaxSpeed * 0.1f)
		return false;
	Real dx = victim->getPosition()->x - source->getPosition()->x;
	Real dy = victim->getPosition()->y - source->getPosition()->y;
	const Coord3D *victimDirection = victim->getUnitDirectionVector2D();
	Coord3D victimDirectionVector;
	victimDirectionVector.x = victimDirection->x;
	victimDirectionVector.y = victimDirection->y;
	if (dx * victimDirectionVector.x + dy * victimDirectionVector.y < 0)
		return false;
	return true;
}

StateReturnType AIAttackApproachTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	if (source->isKindOfProjectile())
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	m_ownerPosition = *source->getPosition();

	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_FAILURE;

	m_waiting = false;
	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();

	if (source->testStatus(OBJECT_STATUS_44) || ai->m_3cc)
	{
		if (weapon && victim && AI::rva002FE193(source, victim) &&
			rva003430A3(source, victim, weapon))
			return STATE_SUCCESS;
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	m_prevVictimPos.x = 0.0f;
	m_prevVictimPos.y = 0.0f;
	m_prevVictimPos.z = 0.0f;
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;

	if (victim)
	{
		if (!weapon)
			return STATE_FAILURE;
		if (Rva0034311ECheck(victim))
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		{
			Bool viewBlocked = false;
			if (ai->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
				viewBlocked = !rva003430A3(source, victim, weapon);
			if (!viewBlocked)
				return STATE_SUCCESS;
		}
		if (!rva00343FB0(source))
			return STATE_FAILURE;
		if (canPursue(source, weapon, victim))
			return STATE_SUCCESS;
		if (ai->getAIUpdateModuleData()->m_24 && source->rva0028B511() >= 17 &&
			!ai->isQuickPathAvailable(victim->getPosition()))
		{
			m_waiting = true;
			m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
			return STATE_CONTINUE;
		}
	}
	else
	{
		if (!weapon || !weapon->getTemplate()->m_16b)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange(source, (void *)getMachineGoalPosition(), 0.0f, 1))
			return STATE_SUCCESS;
		if (!rva00343FB0(source))
			return STATE_FAILURE;
	}

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->rva002907A1())
		mobile = false;
	if (((Rva001E46E1 *)ai->getCurLocomotor())->rva001E46E1(source) < 0.1f)
		mobile = false;
	if (!mobile)
	{
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			ai->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			ai->setTurretTargetPosition(tur, getMachineGoalPosition());
	}

	if (computePath() == false)
		return STATE_FAILURE;
	if (m_waiting)
		return STATE_CONTINUE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackApproachTargetState00C12678::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	if (source->isKindOfProjectile())
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	m_ownerPosition = *source->getPosition();
	m_waiting = false;
	Weapon *weapon = source->getCurrentWeapon();
	const Coord3D *goalPos = getMachineGoalPosition();
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;
	if (weapon->isWithinAttackRange(source, (void *)goalPos, 0.0f, 1))
		return STATE_SUCCESS;
	if (!rva00343FB0(source))
		return STATE_FAILURE;

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->rva002907A1())
		mobile = false;
	if (((Rva001E46E1 *)ai->getCurLocomotor())->rva001E46E1(source) < 0.1f)
		mobile = false;
	if (!mobile)
	{
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
		ai->setTurretTargetPosition(tur, getMachineGoalPosition());

	if (computePath() == false)
		return STATE_FAILURE;
	if (m_waiting)
		return STATE_CONTINUE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackPursueTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	if (source->isKindOfProjectile())
		return STATE_SUCCESS;
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;
	if (!m_isAttackingObject)
		return STATE_SUCCESS;

	if (source->testStatus(OBJECT_STATUS_44) || ai->m_3cc)
	{
		if (AI::rva002FE193(source, getMachineGoalObject()))
			return STATE_SUCCESS;
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 27");
	setAdjustsDestination(false);
	if (source->getControllingPlayer()->m_playerType == 0)
	{
		if (ai->slot143() == 2 && !source->m_249)
			return STATE_SUCCESS;
	}

	m_prevVictimPos.x = 0.0f;
	m_prevVictimPos.y = 0.0f;
	m_prevVictimPos.z = 0.0f;
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;

	Object *victim = getMachineGoalObject();
	if (!victim)
		return STATE_SUCCESS;
	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (!canPursue(source, weapon, victim))
		return STATE_SUCCESS;

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return STATE_SUCCESS;
	ai->setTurretTargetObject(tur, victim, m_isForceAttacking);

	critterDesyncLog("CritterDesync: ComputePath13");
	if (computePath() == false)
		return STATE_SUCCESS;
	return AIInternalMoveToState::onEnter();
}

Bool AIAttackPursueTargetState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath12");
	Bool forceRepath = false;
	if (getMachineOwner()->rva002907A1() == false)
		return false;
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai->isBlockedAndStuck())
		return false;
	if (m_waitingForPath)
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	if (getMachineGoalObject())
	{
		Object *source = getMachineOwner();
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos,
				getMachineGoalObject()->getPosition()))
			return true;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;
		if (!canPursue(source, weapon, getMachineGoalObject()))
			return false;
		Object *victim = getMachineGoalObject();
		m_prevVictimPos = *victim->getPosition();
		critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 26");
		setAdjustsDestination(true);
		m_goalPosition = m_prevVictimPos;
		ai->requestPath(&m_goalPosition, false);
		m_waitingForPath = ai->isWaitingForPath();
		m_stopIfInRange = false;
		return true;
	}
	return false;
}

Bool AIAttackApproachTargetState00C12678::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath10");
	Bool forceRepath = false;
	if (getMachineOwner()->rva002907A1() == false)
		return false;
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (m_waitingForPath)
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 20");
	setAdjustsDestination(true);
	m_stopIfInRange = false;
	m_goalPosition = *getMachineGoalPosition();
	if (!forceRepath)
		return true;
	ai->requestAttackPath(INVALID_OBJECT_ID, &m_goalPosition);
	m_waitingForPath = ai->isWaitingForPath();
	return true;
}

StateReturnType AIAttackFireDuringApproachState::onEnter()
{
	Object *source = getMachineOwner();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_FAILURE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 28");
	setAdjustsDestination(false);
	m_approachTimestamp = 0;
	Object *victim = getMachineGoalObject();
	if (victim)
	{
		m_victimID = victim->getID();
		if (victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533())
			return STATE_FAILURE;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
			return STATE_SUCCESS;

		m_prevVictimPos = *victim->getPosition();
		source->m_ai->destroyPath();
		critterDesyncLog("CritterDesync: ComputePath16");
		if (computePath() == false)
			return STATE_SUCCESS;
		StateReturnType ret = AIInternalMoveToState::onEnter();
		critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 29");
		setAdjustsDestination(true);
		return ret;
	}
	return STATE_FAILURE;
}

Bool AIAttackFireDuringApproachState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath15");
	Bool forceRepath = false;
	StateMachine *machine = getMachine();
	AIUpdateInterface *ai = machine->getOwner()->getAI();
	if (ai->isBlockedAndStuck())
		return false;
	if (m_waitingForPath && ai->isWaitingForPath())
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	Object *victim = TheGameLogic->findObjectByID(m_victimID);
	if (victim)
	{
		Object *source = machine->getOwner();
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos, victim->getPosition()))
			return true;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;
		m_prevVictimPos = *victim->getPosition();
		if (gameLogicDebugLevel() > 0 && !forceRepath)
			debugTrace("masiwar called by AIAttackFireDuringApproachState::computePath [1]");
		if (!forceRepath && ((Rva002C9B80Owner *)weapon)->isWithinAttackRange(source, &m_goalPosition,
				victim, &m_prevVictimPos, 0.0f, true))
			return true;
		m_goalPosition = m_prevVictimPos;
		if (gameLogicDebugLevel() > 0)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "AIAttackFireDuringApproachState::computePath will call FindMeleeEngagmentLocation with m_goalPosition=%f,%f",
					(double)m_goalPosition.x, (double)m_goalPosition.y);
		}
		((Rva002F23A6 *)TheAI->pathfinder())->rva002F23A6(source, (int)weapon,
			(int)&ai->m_locomotorSet, &m_goalPosition, victim);
		source->rva0028ACDC(&m_goalPosition);
		ai->requestApproachPath(&m_goalPosition);
		m_waitingForPath = ai->isWaitingForPath();
		return true;
	}
	return false;
}

StateReturnType AIAttackMeleeSquishState::onEnter()
{
	StateMachine *machine = getMachine();
	Object *source = machine->getOwner();
	if (!source->testStatus(OBJECT_STATUS_44) && !source->m_ai->m_3cc && source->getTemplate()->m_5fd)
	{
		if (!((TurretStateMachine *)machine)->rva004D7ADD())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 33");
			setAdjustsDestination(false);
			m_approachTimestamp = 0;
			Object *victim = getMachineGoalObject();
			if (victim && !(victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()))
			{
				if (!source->rva0029493F(victim, 2))
					return STATE_SUCCESS;
				m_prevVictimPos = *victim->getPosition();
				source->m_ai->destroyPath();
				critterDesyncLog("CritterDesync: ComputePath22");
				if (computePath() == false)
					return STATE_SUCCESS;
				source->setStatus(OBJECT_STATUS_1C, true);
				return AIInternalMoveToState::onEnter();
			}
		}
		return STATE_FAILURE;
	}
	return STATE_SUCCESS;
}

StateReturnType AIAttackMeleeEngageState::onEnter()
{
	Object *source = getMachineOwner();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;

	if (!m_fireState)
		m_fireState = new Rva0033F483(getMachine(), m_weaponSlot);
	m_50 = -1;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 35");
	setAdjustsDestination(false);
	m_approachTimestamp = 0;
	m_retryPending = false;
	m_retryFrame = 0;

	AIUpdateInterface *ai = source->m_ai;
	Object *victim = getMachineGoalObject();
	if (!victim || (victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()) ||
		(victim->m_438 & 1) || victim->testStatus(OBJECT_STATUS_32))
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;

	if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
	{
		Coord3D pos;
		pos.x = source->getPosition()->x;
		pos.y = source->getPosition()->y;
		pos.z = source->getPosition()->z;
		source->rva0028ACEE(&pos, source->rva0028B511());
		if (source->GetGoalPosition(&pos))
		{
			ai->m_finalPosition = pos;
			ai->m_3b0 = false;
		}
		source->setStatus(OBJECT_STATUS_1C, true);
		return STATE_SUCCESS;
	}

	m_prevVictimPos = *victim->getPosition();
	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
	{
		source->setStatus(OBJECT_STATUS_1C, false);
		return STATE_FAILURE;
	}

	ai->destroyPath();
	critterDesyncLog("CritterDesync: ComputePath27");
	if (computePath() == false)
		return STATE_FAILURE;
	if (m_retryPending)
		return STATE_CONTINUE;

	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 36");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackFireWeaponState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	m_waitOddFrame = false;
	obj->setStatus(OBJECT_STATUS_52, false);
	if ((ai->getMoodMatrixActionAdjustment(MM_Action_Attack) & 1) == 0)
		return STATE_FAILURE;

	Object *victim = getMachineGoalObject();
	if (victim)
	{
		if (!obj->testStatus(OBJECT_STATUS_41) && !obj->isKindOf(KINDOF_CE) &&
			!(victim->getTemplate()->m_kindOf[6] & 0x80) && !(victim->getTemplate()->m_kindOf[0x13] & 8) &&
			!(victim->getTemplate()->m_kindOf[0xB] & 0x40) &&
			victim->getControllingPlayer() == obj->getControllingPlayer())
		{
			ai->rva00262B0F(0);
			getMachine()->setGoalObject(0);
			return STATE_FAILURE;
		}
		if ((victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()) ||
			(!(obj->getTemplate()->kindOfWord(3) & 0x2000) && (victim->getTemplate()->kindOfWord(3) & 0x2000)))
		{
			getMachine()->setGoalObject(0);
			return STATE_FAILURE;
		}
	}

	Weapon *weapon = obj->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (!obj->isKindOfImmobile() && !((const Rva002C940EByteField *)weapon->getTemplate())->get() &&
		!((const Rva002C9400ByteField *)weapon->getTemplate())->get() && ai->isMoving())
		return STATE_FAILURE;

	Bool inRange;
	if (victim)
	{
		Team *team = obj->m_team;
		if (team->m_proto->m_216 && !team->getTeamTargetObject())
			team->rva0039D84A(victim);
		inRange = weapon->isWithinAttackRange((const Object *)obj, victim, 0.0f, 1);
	}
	else
	{
		inRange = weapon->isWithinAttackRange(obj, (void *)getMachineGoalPosition(), 0.0f, 1) != 0;
	}
	if (!inRange)
		return STATE_FAILURE;
	if (victim)
	{
		if (Rva0034311ECheck(victim))
			return STATE_FAILURE;
		if (!victim->isSignificantlyAboveTerrain() && ai->isDoingGroundMovement() &&
			!rva003430A3(obj, victim, weapon))
			return STATE_FAILURE;
	}

	if (weapon->getStatus() != READY_TO_FIRE)
		return STATE_SUCCESS;
	if (obj->testStatus(OBJECT_STATUS_26) && (TheGameLogic->getFrame() & 1))
	{
		m_waitOddFrame = true;
		return STATE_CONTINUE;
	}
	obj->setStatus(OBJECT_STATUS_0D, true);
	obj->preFireCurrentWeapon(getMachineGoalObject(), getMachineGoalPosition());
	if (weapon->getTemplate()->m_16b && victim)
		getMachine()->setGoalPosition(victim->getPosition());
	return STATE_CONTINUE;
}
